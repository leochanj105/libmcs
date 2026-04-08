#!/usr/bin/env bash
set -euo pipefail

# run_difffix_loop.sh — diff-test-fix loop.
#
# Each round:
#   1. Generate compact divergence context (per-function C+Rust source)
#   2. Analysis (claude) → goal files
#   3. Git snapshot (pre-fix), then Fixer (claude) → apply fixes to Rust code
#   4. Re-test
#   5. Record stats + stall check
#
# Expects env vars:
#   DIFFGEN_WORKDIR, DIFFFIX_WORKDIR, RUST_DIR, TEST_CASE_DIR,
#   C_SRC_DIRS, C_INCLUDE_DIRS, EXPANDED_PROMPTS_DIR,
#   EXP_DIR, HARNESS_DIR, MAX_ROUNDS, STALL_LIMIT, MAX_GOALS

HARNESS="${HARNESS_DIR:?HARNESS_DIR not set}"
source "${HARNESS}/scripts/ai_runner.sh"

: "${MAX_ROUNDS:=5}"
: "${STALL_LIMIT:=2}"
: "${MAX_GOALS:=5}"

VERBOSE=""
[ "${1:-}" = "-v" ] && VERBOSE="-v"

DIFFGEN="${DIFFGEN_WORKDIR:?DIFFGEN_WORKDIR not set}"
OUTDIR="${DIFFFIX_WORKDIR:?DIFFFIX_WORKDIR not set}"

mkdir -p "$OUTDIR"

# Ensure .claude config exists in difffix and rust dirs for AI permissions
if [ -d "${HARNESS}/.claude" ]; then
    [ -d "${OUTDIR}/.claude" ] || cp -r "${HARNESS}/.claude" "${OUTDIR}/.claude"
    [ -d "${RUST_DIR}/.claude" ] || cp -r "${HARNESS}/.claude" "${RUST_DIR}/.claude"
fi

echo ""
echo "========================================"
echo "DIFF-FIX LOOP"
echo "========================================"
echo "RUST_DIR:     ${RUST_DIR}"
echo "MAX_ROUNDS:   ${MAX_ROUNDS}"
echo "MAX_GOALS:    ${MAX_GOALS}"
echo "STALL_LIMIT:  ${STALL_LIMIT}"
echo ""

# ── Git setup for Rust snapshots ──
_git_init_rust() {
    if [ ! -d "${RUST_DIR}/.git" ]; then
        echo "  Initializing git in ${RUST_DIR}..."
        (cd "${RUST_DIR}" && git init -q && git add -A && git commit -q -m "baseline: pre-difffix")
    fi
}

_git_snapshot() {
    local tag="$1"
    local msg="$2"
    (cd "${RUST_DIR}" && git add -A && git diff --cached --quiet || \
        (cd "${RUST_DIR}" && git add -A && git commit -q -m "${msg}"))
    (cd "${RUST_DIR}" && git tag -f "$tag" 2>/dev/null || true)
}

_git_rollback() {
    local tag="$1"
    echo "  Rolling back Rust to ${tag}..."
    (cd "${RUST_DIR}" && git checkout -q "$tag" -- . && git add -A && git commit -q -m "rollback to ${tag}" --allow-empty)
}

# ── Token cost extraction from stream-json output ──
extract_cost() {
    local outfile="$1"
    python3 -c "
import json, sys
total_in = total_out = cache_read = cache_create = 0
cost = 0.0
with open('$outfile') as f:
    for line in f:
        try: d = json.loads(line.strip())
        except: continue
        if d.get('type') == 'result':
            u = d.get('usage', {})
            total_in += u.get('input_tokens', 0)
            total_out += u.get('output_tokens', 0)
            cache_read += u.get('cache_read_input_tokens', 0)
            cache_create += u.get('cache_creation_input_tokens', 0)
            cost += d.get('total_cost_usd', 0)
print(f'{total_in}\t{total_out}\t{cache_read}\t{cache_create}\t{cost:.4f}')
" 2>/dev/null || printf '0\t0\t0\t0\t0.0000'
}

# ── Stats file ──
STATS_FILE="${OUTDIR}/round_stats.tsv"
if [ ! -f "$STATS_FILE" ]; then
    printf "round\tprev_fails\tfails\tpassed\ttotal\tgoals\tin_tokens\tout_tokens\tcache_read\tcache_create\tcost_usd\tgit_tag\n" > "$STATS_FILE"
fi

# ── Helpers ──
parse_fail_count() {
    local report="$1"
    local tf ce
    tf=$(grep -m1 '^Tests failed:' "$report" 2>/dev/null | awk '{print $3}' || echo 0)
    ce=$(grep -m1 '^Configs with compile error:' "$report" 2>/dev/null | awk '{print $5}' || echo 0)
    echo $(( ${tf:-0} + ${ce:-0} ))
}

parse_pass_count() {
    local report="$1"
    grep -m1 '^Tests passed:' "$report" 2>/dev/null | awk '{print $3}' || echo 0
}

run_diff_tests() {
    local report_dest="$1"
    bash "${EXP_DIR}/run_difftest.sh" "$report_dest"
}

generate_compact_context() {
    local round_dir="$1"
    local c_out="${DIFFGEN}/c_output.txt"
    local r_out="${DIFFGEN}/r_output.txt"

    if [ -f "$c_out" ] && [ -f "$r_out" ]; then
        python3 "${EXP_DIR}/scripts/make_difffix_context.py" \
            "$c_out" "$r_out" "${RUST_DIR}/src" \
            --libm "${TEST_CASE_DIR}" --max-funcs "${MAX_GOALS}" \
            > "${round_dir}/compact_divergences.md" 2>/dev/null || true
        # Also place in OUTDIR so analysis prompt finds it
        cp "${round_dir}/compact_divergences.md" "${OUTDIR}/compact_divergences.md" 2>/dev/null || true
    fi
}

# ── Initialize git in Rust dir ──
_git_init_rust

# ── Baseline (round 0) ──
ROUND0="${OUTDIR}/rounds/0"
mkdir -p "$ROUND0"

if [ ! -f "${ROUND0}/.done" ]; then
    echo "--- Baseline: running differential tests ---"
    run_diff_tests "${ROUND0}/diff_report.txt" 2>&1 | tail -5 || true
    touch "${ROUND0}/.done"
fi

fail_total=$(parse_fail_count "${ROUND0}/diff_report.txt")
pass_total=$(parse_pass_count "${ROUND0}/diff_report.txt")
if [ "$fail_total" -eq 0 ]; then
    echo "ALL TESTS PASS — nothing to fix!"
    exit 0
fi
echo "Baseline: ${pass_total} passed, ${fail_total} failures"
total_tests=$((pass_total + fail_total))

# Record baseline in stats
if ! grep -q "^0	" "$STATS_FILE" 2>/dev/null; then
    printf "0\t-\t%s\t%s\t%s\t-\t-\t-\t-\t-\t-\tbaseline\n" \
        "$fail_total" "$pass_total" "$total_tests" >> "$STATS_FILE"
fi
echo ""

prev_fails="$fail_total"

# ── Determine starting round ──
start_round=1
for dir in "${OUTDIR}/rounds"/*/; do
    [ -d "$dir" ] || continue
    n=$(basename "$dir")
    [[ "$n" =~ ^[0-9]+$ ]] || continue
    [ "$n" -eq 0 ] && continue
    [ -f "${dir}/.done" ] && start_round=$((n + 1))
done

stall=0
[ -f "${OUTDIR}/stall_count" ] && stall=$(cat "${OUTDIR}/stall_count")

# ── Main loop ──
for round in $(seq "$start_round" "$MAX_ROUNDS"); do
    ROUND_DIR="${OUTDIR}/rounds/${round}"
    STEPS_DIR="${ROUND_DIR}/steps"
    mkdir -p "$ROUND_DIR" "$STEPS_DIR"

    round_in=0 round_out=0 round_cache_read=0 round_cache_create=0 round_cost="0.0000"
    round_goals=0

    echo ""
    echo "========================================"
    echo "DIFF-FIX ROUND ${round}/${MAX_ROUNDS}"
    echo "========================================"

    # Get the previous round's report
    PREV_REPORT="${OUTDIR}/rounds/$((round-1))/diff_report.txt"

    # ── Step 1: Generate compact context from latest diff ──
    if [ ! -f "${ROUND_DIR}/.step1_done" ]; then
        echo "--- Step 1: Generate compact divergence context ---"
        generate_compact_context "$ROUND_DIR"
        if [ -f "${ROUND_DIR}/compact_divergences.md" ]; then
            n_funcs=$(grep -c "^## " "${ROUND_DIR}/compact_divergences.md" 2>/dev/null || echo 0)
            echo "  ${n_funcs} diverging functions extracted"
        else
            echo "  No compact context (using full report)"
        fi
        touch "${ROUND_DIR}/.step1_done"
    fi

    # ── Step 2: Analysis → goal files ──
    if [ ! -f "${ROUND_DIR}/.step2_done" ]; then
        echo "--- Step 2: Analyzing failures ---"

        ANALYZE_PROMPT="Read the diff report and compact divergences, then generate fix goals.

Working directory: ${OUTDIR}
Diff report: ${PREV_REPORT}
Compact divergences: ${ROUND_DIR}/compact_divergences.md
Goal output directory: ${STEPS_DIR}/
Rust source: ${RUST_DIR}/
C source: ${TEST_CASE_DIR}/

$(cat "${EXPANDED_PROMPTS_DIR}/analyze.md")
"
        # cd into OUTDIR so Claude CLI picks up .claude/settings.json
        (cd "${OUTDIR}" && run_analysis "$ANALYZE_PROMPT" "${ROUND_DIR}/analysis_output" "$VERBOSE")

        # Count goals
        goal_count=$(ls -1 "${STEPS_DIR}"/goal_*.md 2>/dev/null | wc -l)
        echo "  Goals generated: ${goal_count}"

        if [ "$goal_count" -eq 0 ]; then
            echo "  No goals — stopping."
            break
        fi

        # Cap goals
        if [ "$goal_count" -gt "$MAX_GOALS" ]; then
            echo "  Capping to ${MAX_GOALS} goals"
            ls -1 "${STEPS_DIR}"/goal_*.md | sort -V | tail -n +$((MAX_GOALS + 1)) | while read -r f; do
                mv "$f" "${f}.skipped"
            done
        fi

        touch "${ROUND_DIR}/.step2_done"
    fi

    # ── Step 3: Git snapshot + Fix each goal ──
    if [ ! -f "${ROUND_DIR}/.step3_done" ]; then
        echo "--- Step 3: Snapshot & Fixing ---"

        # Git snapshot before fixes
        _git_snapshot "pre-round-${round}" "pre-round-${round}: before fixes"
        echo "  Git tag: pre-round-${round}"

        for goal_file in "${STEPS_DIR}"/goal_*.md; do
            [ -f "$goal_file" ] || continue
            goal_name=$(basename "$goal_file" .md)
            echo "  Fixing: ${goal_name}"

            FIX_PROMPT="Fix the Rust code based on this goal.

Working directory: ${RUST_DIR}
Goal: ${goal_file}
Rust source: ${RUST_DIR}/
C source: ${TEST_CASE_DIR}/

$(cat "${EXPANDED_PROMPTS_DIR}/fixer.md")

Goal content:
$(cat "$goal_file")
"
            # cd into RUST_DIR so Claude CLI picks up .claude/settings.json
            (cd "${RUST_DIR}" && run_codegen "$FIX_PROMPT" "${STEPS_DIR}/${goal_name}_fix_output" "$VERBOSE")
        done

        # Git snapshot after fixes
        _git_snapshot "post-round-${round}" "round-${round}: fixes applied"
        echo "  Git tag: post-round-${round}"

        touch "${ROUND_DIR}/.step3_done"
    fi

    # ── Step 4: Re-test ──
    if [ ! -f "${ROUND_DIR}/.step4_done" ]; then
        echo "--- Step 4: Re-testing ---"
        run_diff_tests "${ROUND_DIR}/diff_report.txt" 2>&1 | tail -5 || true
        touch "${ROUND_DIR}/.step4_done"
    fi

    fail_total=$(parse_fail_count "${ROUND_DIR}/diff_report.txt")
    pass_total=$(parse_pass_count "${ROUND_DIR}/diff_report.txt")
    echo "After round ${round}: ${pass_total} passed, ${fail_total} failures (was ${prev_fails})"

    # ── Collect token costs for this round ──
    round_goals=$(ls -1 "${STEPS_DIR}"/goal_*.md 2>/dev/null | wc -l)
    _sum_tokens() {
        local _in=0 _out=0 _cr=0 _cc=0 _cost="0"
        for outf in "$@"; do
            [ -f "$outf" ] || continue
            IFS=$'\t' read -r i o cr cc c <<< "$(extract_cost "$outf")"
            _in=$((_in + i)); _out=$((_out + o)); _cr=$((_cr + cr)); _cc=$((_cc + cc))
            _cost=$(python3 -c "print(f'{$_cost + $c:.4f}')" 2>/dev/null || echo "$_cost")
        done
        printf '%s\t%s\t%s\t%s\t%s' "$_in" "$_out" "$_cr" "$_cc" "$_cost"
    }
    all_outputs=("${ROUND_DIR}/analysis_output")
    for gf in "${STEPS_DIR}"/goal_*_fix_output; do
        [ -f "$gf" ] && all_outputs+=("$gf")
    done
    IFS=$'\t' read -r round_in round_out round_cache_read round_cache_create round_cost <<< "$(_sum_tokens "${all_outputs[@]}")"

    # Record stats
    if ! grep -q "^${round}	" "$STATS_FILE" 2>/dev/null; then
        printf "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\tpost-round-%s\n" \
            "$round" "$prev_fails" "$fail_total" "$pass_total" "$total_tests" \
            "$round_goals" "$round_in" "$round_out" "$round_cache_read" "$round_cache_create" \
            "$round_cost" "$round" >> "$STATS_FILE"
    fi

    [ "$fail_total" -eq 0 ] && { echo "ALL TESTS PASS!"; break; }

    # ── Step 5: Stall check (rollback if worse) ──
    if [ "$fail_total" -gt "$prev_fails" ]; then
        echo "  Round made things WORSE (${prev_fails} -> ${fail_total}). Rolling back."
        _git_rollback "pre-round-${round}"
        stall=$((stall + 1))
        echo "${stall}" > "${OUTDIR}/stall_count"
        echo "  Stall ${stall}/${STALL_LIMIT}"
        [ "$stall" -ge "$STALL_LIMIT" ] && { echo "Stalled."; break; }
        # Don't update prev_fails — we rolled back
    elif [ "$fail_total" -eq "$prev_fails" ]; then
        stall=$((stall + 1))
        echo "${stall}" > "${OUTDIR}/stall_count"
        echo "No progress (stall ${stall}/${STALL_LIMIT})"
        [ "$stall" -ge "$STALL_LIMIT" ] && { echo "Stalled."; break; }
    else
        stall=0
        echo "0" > "${OUTDIR}/stall_count"
    fi

    prev_fails="$fail_total"
    touch "${ROUND_DIR}/.done"
done

# ── Print summary ──
echo ""
echo "========================================"
echo "DIFF-FIX LOOP COMPLETE"
echo "========================================"
echo "Final: ${pass_total} passed, ${fail_total} failures"
echo ""
echo "Per-round stats: ${STATS_FILE}"
column -t -s $'\t' "$STATS_FILE" 2>/dev/null || cat "$STATS_FILE"
echo ""
echo "Git tags in ${RUST_DIR}:"
(cd "${RUST_DIR}" && git tag -l 'pre-round-*' -l 'post-round-*' -l 'baseline' | sort -V)
