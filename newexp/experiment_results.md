# Experiment Results

## Phase 1: Transpilation

| Phase | Wall Clock | Cost |
|-------|-----------|------|
| C → Rust transpilation | 1.7h | $26.82 |

Model: claude-sonnet-4-6

## Phase 2: Test Generation (S1–S5)

### Token Usage

| Scenario | Strategy | Rounds | Output Tokens | Cache Read | Cache Create | Total Tokens | Cost | Wall Clock |
|----------|----------|--------|--------------|------------|-------------|-------------|------|-----------|
| S1 | Naive one-shot | 1 | 43,721 | 177,042 | 52,319 | 273K | $0.91 | 6.8m |
| S2 | Explicit boundary | 1 | 45,422 | 842,404 | 69,745 | 958K | $1.20 | 8.7m |
| S3 | Edge case | 1 | 62,827 | 339,510 | 76,706 | 479K | $1.33 | 10.2m |
| S4 | Function coverage feedback | 1 | 57,712 | 2,430,391 | 103,993 | 2.6M | $1.99 | 22.4m |
| S5 | Branch coverage feedback (on S4) | 5 | 435,255 | 15,945,081 | 807,094 | 17.2M | $26.84 | 2.8h |

### Test Counts

| Scenario | Test Prints | Lines |
|----------|-------------|-------|
| S1 | 779 | 2,181 |
| S2 | 508 | 1,049 |
| S3 | 998 | 2,150 |
| S4 | 524 | 2,026 |
| S5 | 3,875 | 8,718 |

## Phase 3: Diff-Fix

### S3 Results (rollback + regression feedback mode)

Fixer mode: separate analyze + fix. Rounds 1-3 plain. Round 4 regressed and
was rolled back. Round 5 received round 4's failed diff + failures as feedback
and ran on round 3's code.

Results stored in: `work-s3/difffix-noreact/`, `rust-s3-noreact/`

#### Per-Round Progression

| Round | Prev Fails | Fails | Passed | Pass Rate | Goals | Wall Clock | Cost |
|-------|-----------|-------|--------|-----------|-------|-----------|------|
| Baseline | — | 52 | 1137 | 95.6% | — | — | — |
| R1 | 52 | 38 | 1151 | 96.8% | 5 | 36.1m | $4.52 |
| R2 | 38 | 31 | 1158 | 97.4% | 5 | 15.7m | $2.37 |
| R3 | 31 | 7 | 1182 | 99.4% | 5 | 7.1m | $1.46 |
| R4 | 7 | 8 | 1181 | 99.3% | 5 | 9.2m | $1.01 |
| R5 | 7 | 2 | 1187 | 99.8% | 5 | 11.4m | $0.55 |
| **Total** | | | | | **25** | **79.5m** | **$9.91** |

#### Per-Round Token Usage

| Round | Input | Output | Cache Read | Cache Create | Cost |
|-------|-------|--------|-----------|-------------|------|
| R1 | 90 | 147,503 | 3,329,913 | 252,778 | $4.52 |
| R2 | 73 | 55,197 | 2,063,479 | 164,244 | $2.37 |
| R3 | 62 | 26,444 | 1,452,935 | 125,252 | $1.46 |
| R4 | 42 | 22,108 | 726,451 | 84,873 | $1.01 |
| R5 | 32 | 7,670 | 464,504 | 78,599 | $0.55 |
| **Total** | **299** | **258,922** | **8,037,282** | **705,746** | **$9.91** |

#### Remaining Failures (2)

- `cacos(inf,0)`: NaN sign bit mismatch (C returns `nan`, Rust returns `-nan`)
- `cacosf(inf,0)`: same, float version

### S3 Round 5 Mode Comparison

Starting from same rounds 1-4. Only round 5 differs.

| Mode | Code State | Starting Fails | Final Fails | Cost |
|------|-----------|---------------|-------------|------|
| Plain (REACT_MODE=0) | Round 4 code (8 fails) | 8 | 5 | ~$0.55 |
| Rollback + regression feedback | Round 3 code (7 fails) | 7 | 2 | $0.55 |

Note: not directly comparable — different starting code states due to rollback.
Results in: `work-s3/difffix-plain/`, `rust-s3-plain/` (plain mode)

### S1, S2, S4, S5 Difffix

Not yet run with the corrected infrastructure (no C fallback, Rust bridge, O0).

## Configuration

- All AI calls: claude-sonnet-4-6
- Rust: opt-level = 0 (no LLVM optimization, prevents false infinite loops)
- C: clang-21, no optimization flags
- Rust test binary: linked without C fallback library
- Rust bridge: C-ABI wrappers for internal/static functions (test_bridge.rs)
- C bridge: test_bridge.c (wraps static functions for C binary)
- Timeout: 30s per test binary execution
- Difffix fixer modes:
  - REACT_MODE=0: plain (previous round's report only)
  - REACT_MODE=1: regression feedback (diff + failures when regression occurs)
  - REACT_MODE=2: full ReAct (all rounds' goals, diffs, results accumulated)

## File Layout

- `newexp/experiment_results.md` — this file
- `newexp/rust-baseline/` — pure transpilation output
- `newexp/rust-baseline-test/` — transpilation + test bridge (ready for difftest)
- `newexp/test_bridge.rs` — shared Rust bridge (test infrastructure)
- `newexp/test_bridge.c`, `test_bridge.h` — shared C bridge
- `newexp/work-s{1..5}/testgen/` — test generation results
- `newexp/work-s3/difffix-noreact/` — S3 difffix results (rollback+feedback mode)
- `newexp/work-s3/difffix-plain/` — S3 difffix round 5 plain mode
- `newexp/rust-s3-noreact/` — S3 final Rust code (rollback+feedback mode)
- `newexp/rust-s3-plain/` — S3 final Rust code (plain round 5)
