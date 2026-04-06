# Cost Optimization Playbook for AI-Driven Harness

Lessons learned from the libmcs C-to-Rust transpilation experiment (Apr 2026).
All costs refer to Claude API via `claude` CLI with `--output-format stream-json`.

---

## Core Principle: Minimize Turns, Maximize Cache

Claude's cost = f(input tokens × turns). Two levers:
1. **Reduce turns** — every Read/Bash call is a turn that adds tool-call overhead
2. **Exploit prompt caching** — identical prefix tokens across turns (and possibly
   across sessions) are cached at ~10% cost

These two are related: if content is in CLAUDE.md (part of the prefix), it's loaded
for free after turn 1. If content is read via a tool call, it's a full-price turn.

---

## Trick 1: Preload Static Content via CLAUDE.md

**Problem:** Claude reads C source files one-by-one (50-90 Read/Bash turns per call),
inflating context to 1M+ tokens. A single strategy call cost $1.73 with 90 turns.

**How it works:** Claude Code auto-loads `.claude/CLAUDE.md` into the prompt prefix
at session start — zero tool turns. The content becomes part of the cacheable prefix,
so after turn 1, it's cached for all subsequent turns within the session.

**Implementation:**
- Generate once: concatenate all C source into `testgen/.claude/CLAUDE.md` and
  `rust/.claude/CLAUDE.md` (strip comments/blanks to save tokens)
- For libmcs: 187 .c files → 169KB stripped (~42K tokens)
- CLAUDE.md must be **immutable** — never modify it after generation (see Trick 2)

**Enforcement** (3 layers to prevent Claude from reading source files anyway):
1. *Prompt*: "C source is in CLAUDE.md. Do NOT Read .c files."
2. *settings.json deny rules*: block Read/Glob/Grep on `libm/**` paths
3. *OS-level chmod 000*: project claude wrapper locks C source dirs during AI calls,
   blocking Bash `cat`/`head`/`grep` bypass

**Savings:** Eliminates 50-90 turns → ~5 turns per call. $1.73 → ~$0.30.

---

## Trick 2: Keep CLAUDE.md Immutable, Use Separate File for Changing Content

**Problem:** If CLAUDE.md changes between invocations (e.g., appending Rust diffs),
the prompt prefix changes → **cache invalidation**. The entire 42K tokens are
reprocessed at full price instead of cache price.

**How prompt caching works:**
- Within a session: after turn 1 processes the prefix (system prompt + CLAUDE.md),
  turns 2-N read it from cache at ~10% cost. This is **guaranteed**.
- Across sessions: if the exact same prefix tokens are sent within the TTL window
  (~5 min), the next session MAY get a cache hit. This is **possible but not guaranteed**.
- Either way: modifying CLAUDE.md invalidates caching. Don't do it.

**Implementation:**
- CLAUDE.md = static C source (never modified after initial generation)
- `rust_changes.md` = separate file for Rust diffs (read via 1 Read tool call)
- `update_rust_context.sh` runs after each difftest round:
  1. Appends `git diff HEAD` to `rust/rust_changes.md` (NOT CLAUDE.md)
  2. Commits Rust changes so next round's diff is incremental (not cumulative)
- Fixer prompt says: "If rust_changes.md exists, read it FIRST"

**Cost model per fixer call:**
- CLAUDE.md (42K tokens): cached after turn 1 → turns 2+ read at ~10% cost
- rust_changes.md (1 Read call, ~2-10KB): ~1K tokens, negligible
- vs. before: 42K tokens reprocessed every turn if CLAUDE.md was modified

---

## Trick 3: Eliminate Redundant AI Analysis Steps

**Problem:** The `run_strategy.sh` step asks Claude to analyze every uncovered branch
by reading C source files. With CLAUDE.md preloading, this is now redundant — the
testgen call already has the source code and branch info in context.

**Implementation:** Pre-generate a mechanical `strategy.md` from `branches.md` +
`uncovered_functions.md` (no AI call). The testgen prompt + CLAUDE.md source code +
branch conditions provide enough context.

**Savings:** ~$1.50/round eliminated (was 90+ turns of source exploration).

---

## Trick 4: Batch AI Calls (Omnibus Pattern)

**Problem:** The original difffix loop made one AI call per failing test case. With
20 failures = 20 separate calls, each re-reading the same Rust files.

**Fix:** The omnibus approach sends all failure goals in a single prompt. The AI reads
relevant files once and fixes everything in one pass.

**Savings:** $1-2/round → $0.05-0.30/round.

---

## Trick 5: Use `cargo check --lib` Instead of `cargo build --release`

**Problem:** `cargo build --release` compiles and links (~30-60s). The fixer only needs
compilation errors — it doesn't need a binary.

**Fix:** Fixer prompt says "use `cargo check --lib`" (~3-10s). Fewer seconds per
iteration = fewer tokens on waiting/retrying.

---

## Trick 6: Fix Coverage Detection to Avoid Wasted Rounds

**Problem:** Broken coverage detection (func_cov rounds 2-5 reported 0 uncovered
functions) caused the loop to waste rounds with no useful feedback.

**Root causes and fixes:**
- `--whole-archive` on linker (prevents stripping uninstrumented symbols)
- `-fno-builtin` on compilation (prevents compiler inlining math as builtins)
- `|| true` on `llvm-cov export` pipeline (prevents pipefail crashes)
- `llvm-cov export` JSON + python3 for reliable function detection

---

## Trick 7: Prevent Concurrent Loop Instances

**Problem:** Two instances of `run_testgen_loop.sh` on the same directory raced on
`test_suite.c`, step markers, and the `rounds/current` symlink. Duplicate work +
corrupted state.

**Fix:** Check `ps aux | grep run_testgen` before launching. Kill stale processes.

---

## Trick 8: Minimize Monitoring Overhead

**Problem:** Checking subprocess status from the main Claude conversation costs tokens
per poll. Frequent "progress?" checks burn through context.

**Fix:** Use `stat -c "%s" output_file` or `tail -f` in a separate terminal.

---

## Cost Comparison: Before vs After

| Phase | Before (no preload, 90 turns) | After (CLAUDE.md + tricks) |
|---|---|---|
| Testgen round (strategy + testgen) | ~$3.00 (90+ turns) | ~$0.30 (~5 turns) |
| Difffix round (omnibus) | ~$0.50 | ~$0.30 (diffs in separate file) |
| Full experiment (4 testgen + 5 difffix) | ~$14.50 | ~$2.70 |

**~5x cost reduction** while keeping Sonnet quality.

---

## Checklist Before Launching an Experiment

1. [ ] `CODE_GEN_CMD=claude`, `ANALYSIS_CMD=claude`, `CLAUDE_MODEL=sonnet`
2. [ ] Static C source digest in `testgen/.claude/CLAUDE.md` and `rust/.claude/CLAUDE.md`
3. [ ] `settings.json` deny rules for `libm/**` and `build-x86_64-linux-gnu/**`
4. [ ] Project claude wrapper with `chmod 000` on C source dirs during AI calls
5. [ ] `update_rust_context.sh` writes to `rust_changes.md` (NOT CLAUDE.md)
6. [ ] `run_difftest.sh` calls `update_rust_context.sh` after each test run
7. [ ] Testgen prompt: "C source in CLAUDE.md, do NOT Read .c files"
8. [ ] Fixer prompt: "read rust_changes.md first" + "cargo check --lib"
9. [ ] No stale processes: `ps aux | grep run_testgen`
10. [ ] Coverage instrumentation: `--whole-archive` + `-fno-builtin`
