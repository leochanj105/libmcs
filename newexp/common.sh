#!/usr/bin/env bash
# common.sh — shared constants and helpers for all phase scripts.
# Source this from every phase script.

COMMON_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

export EXP_DIR="$COMMON_DIR"
export HARNESS_DIR="/home/leochanj/Desktop/progress_harness"
export LIBMCS="/home/leochanj/Desktop/libmcs/libm"
export C_SRC_DIRS="${LIBMCS}/mathd ${LIBMCS}/mathf ${LIBMCS}/common ${LIBMCS}/complexd ${LIBMCS}/complexf"
export C_INCLUDE_DIRS="${LIBMCS}/include"

SCENARIOS=(s1_naive s2_explicit s3_function s4_branch)

# ── API key check ──
if [ -z "${ANTHROPIC_API_KEY:-}" ]; then
    echo "ERROR: ANTHROPIC_API_KEY is not set." >&2
    echo "  export ANTHROPIC_API_KEY=\"sk-ant-...\"" >&2
    exit 1
fi

export CODE_GEN_CMD="${CODE_GEN_CMD:-claude}"
export ANALYSIS_CMD="${ANALYSIS_CMD:-claude}"

# ── Ensure CLAUDE.md + settings.json exist at HARNESS_DIR ──
# Claude CLI loads .claude/CLAUDE.md as system prompt and .claude/settings.json
# for permissions. We use a lightweight CLAUDE.md (just instructions, no source
# embedding) because the full source (~22K lines) exceeds Sonnet's 200K context.
# The AI reads source files from disk instead.
_ensure_claude_setup() {
    local claude_dir="${HARNESS_DIR}/.claude"
    mkdir -p "$claude_dir"

    # Lightweight CLAUDE.md — instructions only, no embedded source
    cat > "${claude_dir}/CLAUDE.md" <<'CLAUDEEOF'
# Project Context

## Library
Libmcs — a C math library (libm implementation). IEEE 754 compliant.

## Comparison rule
All outputs must be bitwise exact. Use %a hex float format. Zero tolerance.

## Source layout
- /home/leochanj/Desktop/libmcs/libm/mathd/       — double-precision functions
- /home/leochanj/Desktop/libmcs/libm/mathf/       — float-precision functions
- /home/leochanj/Desktop/libmcs/libm/complexd/    — complex double functions
- /home/leochanj/Desktop/libmcs/libm/complexf/    — complex float functions
- /home/leochanj/Desktop/libmcs/libm/common/      — shared utilities
- /home/leochanj/Desktop/libmcs/libm/include/     — headers (math.h, complex.h, fenv.h)
Each directory has an internal/ subdirectory with helper functions.
CLAUDEEOF

    # Settings.json — allow access to libmcs and experiment directories
    cat > "${claude_dir}/settings.json" <<SETTINGSEOF
{
  "permissions": {
    "allow": [
      "Read(./**)", "Write(./**)", "Edit(./**)", "Glob(./**)", "Grep(./**)", "Bash",
      "Read(//tmp/**)", "Write(//tmp/**)", "Edit(//tmp/**)",
      "Read(//home/leochanj/Desktop/libmcs/**)",
      "Glob(//home/leochanj/Desktop/libmcs/**)",
      "Grep(//home/leochanj/Desktop/libmcs/**)",
      "Write(//home/leochanj/Desktop/libmcs/newexp/**)",
      "Edit(//home/leochanj/Desktop/libmcs/newexp/**)"
    ],
    "deny": [
      "WebFetch", "WebSearch",
      "Read(//home/leochanj/Desktop/libmcs/testing/judger_v2/**)",
      "Glob(//home/leochanj/Desktop/libmcs/testing/judger_v2/**)",
      "Grep(//home/leochanj/Desktop/libmcs/testing/judger_v2/**)"
    ]
  }
}
SETTINGSEOF

    echo "  Generated CLAUDE.md (lightweight) + settings.json"
}
# Defer actual call until after function definitions

# ── Parse common flags ──
VERBOSE=""
ONLY_SCENARIO="all"
_common_parse_args() {
    while [ $# -gt 0 ]; do
        case "$1" in
            -v) VERBOSE="-v" ;;
            --scenario) ONLY_SCENARIO="$2"; shift ;;
            *) echo "Unknown option: $1"; exit 1 ;;
        esac
        shift
    done
}

should_run_scenario() {
    [ "$ONLY_SCENARIO" = "all" ] || [ "$ONLY_SCENARIO" = "$1" ]
}

short_name() {
    # s1_naive -> s1
    echo "${1%%_*}"
}

log() {
    echo ""
    echo "========================================"
    echo "$@"
    echo "========================================"
}

# ── Expand __RUST_DIR__ in a prompt file ──
expand_prompt() {
    local src="$1" dest="$2" rust_dir="$3"
    sed -e "s|__RUST_DIR__|${rust_dir}|g" "$src" > "$dest"
}

# Run the deferred setup now
_ensure_claude_setup

# ── Set up a scenario's workdir with expanded prompts ──
setup_scenario_workdir() {
    local scenario="$1"
    local short
    short=$(short_name "$scenario")
    local work_dir="${EXP_DIR}/work-${short}"
    local rust_dir="${EXP_DIR}/rust-${short}"

    mkdir -p "${work_dir}/prompts" "${work_dir}/testgen" "${work_dir}/diffgen" "${work_dir}/difffix"

    # Expand all prompts with scenario-specific RUST_DIR
    for prompt in testgen strategy difftest analyze fixer transpile; do
        local src="${EXP_DIR}/prompts/${prompt}.md"
        [ -f "$src" ] || continue
        expand_prompt "$src" "${work_dir}/prompts/${prompt}.md" "$rust_dir"
    done

    # Copy lightweight .claude/ from harness for prompt caching + permissions
    if [ ! -d "${work_dir}/.claude" ]; then
        cp -r "${HARNESS_DIR}/.claude" "${work_dir}/.claude"
    fi
}

# ── Copy baseline Rust to scenario directory ──
copy_rust_for_scenario() {
    local scenario="$1"
    local short
    short=$(short_name "$scenario")
    local rust_dest="${EXP_DIR}/rust-${short}"

    if [ -d "$rust_dest" ] && [ -f "${rust_dest}/Cargo.toml" ]; then
        echo "  ${rust_dest} already exists — skipping copy."
        return
    fi

    [ -d "${EXP_DIR}/rust-baseline" ] || { echo "ERROR: rust-baseline not found. Run 01_transpile.sh first." >&2; exit 1; }
    echo "  Copying rust-baseline -> rust-${short}..."
    cp -r "${EXP_DIR}/rust-baseline" "$rust_dest"
}

# ── Export scenario env vars (used by harness scripts) ──
export_scenario_env() {
    local scenario="$1"
    local short
    short=$(short_name "$scenario")
    local scenario_dir="${EXP_DIR}/scenarios/${scenario}"
    local work_dir="${EXP_DIR}/work-${short}"

    export PROJECT_DIR="$scenario_dir"
    export TEST_CASE_DIR="$LIBMCS"
    export RUST_DIR="${EXP_DIR}/rust-${short}"
    export WORK_DIR="$work_dir"
    export TESTGEN_WORKDIR="${work_dir}/testgen"
    export DIFFGEN_WORKDIR="${work_dir}/diffgen"
    export DIFFFIX_WORKDIR="${work_dir}/difffix"
    export EXPANDED_PROMPTS_DIR="${work_dir}/prompts"
    export C_SRC_DIRS C_INCLUDE_DIRS
    export CONFIGS_FILE=""
}
