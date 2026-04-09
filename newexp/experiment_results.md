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
| S4 (old, with long double) | Function coverage feedback | 2 | 57,712 | 2,430,391 | 103,993 | 2.6M | $1.99 | 22.4m |
| S4 (new, corrected) | Function coverage feedback | 2 | 40,942 | 439,934 | 44,243 | 525K | $0.91 | 7.0m |
| S5 (old, with long double) | Branch coverage feedback (on S4) | 5 | 435,255 | 15,945,081 | 807,094 | 17.2M | $26.84 | 2.8h |
| S5 (new) | Branch coverage feedback (on S4) | 5 | — | — | — | $14.20 | ~80m |

### Test Counts and Coverage

186 functions are actually compiled in the C library (178 public + 8 static).
Long double wrapper functions (`acosl`, `sinl`, etc.) are behind a disabled
`#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS` and excluded from the function list.

Two branch coverage metrics:
- **OUR**: from `branch_coverage.py` using `llvm-cov export` branch entries,
  deduplicated. Each branch = 2 conditions (true/false). Covered = count > 0.
  Total: 1634 branches = 3268 conditions.
- **REPORT**: from `llvm-cov report` "Branches" column filtered to libm/ files.
  Total: 3226. Uses LLVM's internal counting (different from export entries).

| Scenario | Test Prints | Func Cov | OUR Branch Cov | OUR (cov/total) | REPORT Branch Cov | REPORT (cov/total) |
|----------|-------------|----------|---------------|-----------------|-------------------|-------------------|
| S1 | 779 | 170/186 (91%) | 54.8% | 1790/3268 | 59.2% | 1911/3226 |
| S2 | 508 | 186/186 (100%) | 43.4% | 1418/3268 | 47.0% | 1516/3226 |
| S3 | 998 | 174/186 (93%) | 66.1% | 2161/3268 | 71.4% | 2302/3226 |
| S4 | 371 | 186/186 (100%) | 41.6% | 1359/3268 | 45.3% | 1461/3226 |
| S5 | 2039 | 186/186 (100%) | 84.0% | 2744/3268 | 90.5% | 2921/3226 |

All measured with clang-21, llvm-cov-21, `-O0 -fno-builtin`, all .o linked directly.

Notes:
- S2's test_fenv crashes (segfault). Coverage measured with fenv test skipped.
- S4 has 100% function coverage but only 41.6% branch condition coverage.
- S5 builds on S4 with 5 rounds of branch coverage feedback (40.0% → 84.0%).
- S3's edge case prompt achieves 66.1% without any coverage feedback — better
  than S4 (41.6%) which uses function coverage feedback only.
- OUR metric is stricter than REPORT (different denominator and counting rules).
  Both show the same relative ordering: S5 > S3 > S1 > S2 > S4.

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

### S4 Results (default mode)

Fixer mode: separate analyze + fix. No regressions occurred.

Results stored in: `work-s4/difffix/`, `rust-s4/`

#### Per-Round Progression

| Round | Prev Fails | Fails | Passed | Pass Rate | Goals | Cost |
|-------|-----------|-------|--------|-----------|-------|------|
| Baseline | — | 5 | 436 | 98.9% | — | — |
| R1 | 5 | 1 | 440 | 99.8% | 4 | $0.88 |
| R2 | 1 | 0 | 441 | 100.0% | 1 | $0.36 |
| **Total** | | | | | **5** | **$1.24** |

#### Per-Round Token Usage

| Round | Input | Output | Cache Read | Cache Create | Cost |
|-------|-------|--------|-----------|-------------|------|
| R1 | 32 | 12,479 | 639,813 | 82,737 | $0.88 |
| R2 | 14 | 3,122 | 239,300 | 33,028 | $0.36 |
| **Total** | **46** | **15,601** | **879,113** | **115,765** | **$1.24** |

#### Remaining Failures: 0

### S1, S2, S5 Difffix

Not yet run with the corrected infrastructure (no C fallback, Rust bridge, O0).

## Difffix Cross-Scenario Summary

| Scenario | Tests | Baseline Fails | Final Fails | Rounds | Cost |
|----------|-------|---------------|-------------|--------|------|
| S3 | 1189 | 52 | 2 | 5 | $9.91 |
| S4 | 441 | 5 | 0 | 2 | $1.24 |
| S1 | 779 | — | — | — | — |
| S2 | 508 | — | — | — | — |
| S5 | 3875 | — | — | — | — |

## Configuration

- All AI calls: claude-sonnet-4-6
- Rust: opt-level = 0 (no LLVM optimization, prevents false infinite loops)
- C: clang-21, no optimization flags
- Rust test binary: linked without C fallback library
- Rust bridge: C-ABI wrappers for internal/static functions (test_bridge.rs)
- C bridge: test_bridge.c (wraps static functions for C binary)
- Timeout: 30s per test binary execution
- Difffix default behavior: rollback on regression + feed failed attempt's diff/failures
- REACT_MODE=0 (default): rollback + failed attempt feedback on regression
- REACT_MODE=1: additionally accumulate full ReAct history (all rounds' goals, diffs, results)

## File Layout

- `newexp/experiment_results.md` — this file
- `newexp/rust-baseline/` — pure transpilation output
- `newexp/rust-baseline-test/` — transpilation + test bridge (ready for difftest)
- `newexp/test_bridge.rs` — shared Rust bridge (test infrastructure)
- `newexp/test_bridge.c`, `test_bridge.h` — shared C bridge
- `newexp/work-s{1..5}/testgen/` — test generation results
- `newexp/work-s3/difffix-noreact/` — S3 difffix results (rollback+feedback mode)
- `newexp/work-s4/difffix/` — S4 difffix results (default mode)
- `newexp/rust-s4/` — S4 final Rust code (0 failures)
- `newexp/rust-s4-prefixbackup/` — S4 pre-difffix Rust code
- `newexp/work-s3/difffix-plain/` — S3 difffix round 5 plain mode
- `newexp/rust-s3-noreact/` — S3 final Rust code (rollback+feedback mode)
- `newexp/rust-s3-plain/` — S3 final Rust code (plain round 5)
