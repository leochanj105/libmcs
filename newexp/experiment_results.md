# Experiment Results

## Testgen Token Usage (S1–S5)

| Scenario | Rounds | Output Tokens | Cache Read | Cache Create | Total Tokens | Cost |
|----------|--------|--------------|------------|-------------|-------------|------|
| S1 | 1 | 43,721 | 177,042 | 52,319 | 273K | $0.91 |
| S2 | 1 | 45,422 | 842,404 | 69,745 | 958K | $1.20 |
| S3 | 1 | 62,827 | 339,510 | 76,706 | 479K | $1.33 |
| S4 | 1 | 57,712 | 2,430,391 | 103,993 | 2.6M | $1.99 |
| S5 | 5 | 435,255 | 15,945,081 | 807,094 | 17.2M | $26.84 |

## Testgen Test Counts

| Scenario | Strategy | Test Prints | Lines |
|----------|----------|-------------|-------|
| S1 | Naive one-shot | 779 | 2,181 |
| S2 | Explicit boundary | 508 | 1,049 |
| S3 | Edge case | 998 | 2,150 |
| S4 | Function coverage (1 round) | 524 | 2,026 |
| S5 | Branch coverage (5 rounds on S4) | 3,875 | 8,718 |

## Difffix Results: S3 (with rollback feedback)

Configuration:
- Rust opt-level = 0 (no LLVM optimization)
- No C fallback (pure Rust binary, Rust bridge for internal functions)
- 30s timeout for hang detection
- Rounds 1-3: plain (no feedback)
- Round 4: regressed, rolled back
- Round 5: regression feedback (round 4 diff + failures)

### Per-Round Progression

| Round | Prev Fails | Fails | Passed | Pass Rate | Goals | Wall Clock | Cost |
|-------|-----------|-------|--------|-----------|-------|-----------|------|
| Baseline | — | 52 | 1137 | 95.6% | — | — | — |
| R1 | 52 | 38 | 1151 | 96.8% | 5 | 36.1m | $4.52 |
| R2 | 38 | 31 | 1158 | 97.4% | 5 | 15.7m | $2.37 |
| R3 | 31 | 7 | 1182 | 99.4% | 5 | 7.1m | $1.46 |
| R4 | 7 | 8 | 1181 | 99.3% | 5 | 9.2m | $1.01 |
| R5 | 7 | 2 | 1187 | 99.8% | 5 | 11.4m | $0.55 |
| **Total** | | | | | **25** | **79.5m** | **$9.91** |

Note: R4 regressed (7→8), was rolled back. R5 ran on R3's code with R4's
failed diff + failures as feedback. R5 achieved 7→2.

### Per-Round Token Usage

| Round | Input | Output | Cache Read | Cache Create | Cost |
|-------|-------|--------|-----------|-------------|------|
| R1 | 90 | 147,503 | 3,329,913 | 252,778 | $4.52 |
| R2 | 73 | 55,197 | 2,063,479 | 164,244 | $2.37 |
| R3 | 62 | 26,444 | 1,452,935 | 125,252 | $1.46 |
| R4 | 42 | 22,108 | 726,451 | 84,873 | $1.01 |
| R5 | 32 | 7,670 | 464,504 | 78,599 | $0.55 |
| **Total** | **299** | **258,922** | **8,037,282** | **705,746** | **$9.91** |

### Remaining Failures (2)

- `cacos(inf,0)`: NaN sign bit mismatch
- `cacosf(inf,0)`: same, float version

## Difffix Comparison: S3 Round 5 Modes

Same starting state (round 4, 8 failures). Only round 5 differs.

| Mode | Starting Fails | Final Fails | Cost |
|------|---------------|-------------|------|
| Plain (no feedback) | 8 | 5 | $0.55 |
| Rollback + regression feedback | 7 (rolled back to R3) | 2 | $0.55 |

Note: different starting states (8 vs 7) due to rollback. Not directly comparable.

## Timing Summary

| Phase | Scenario | Wall Clock | Cost |
|-------|----------|-----------|------|
| Transpile | — | 1.7h | $26.82 |
| Testgen | S1 | 6.8m | $0.91 |
| | S2 | 8.7m | $1.20 |
| | S3 | 10.2m | $1.33 |
| | S4 | 22.4m | $3.98 |
| | S5 | 2.8h | $26.84 |
| Difffix | S3 (5 rounds) | 79.5m | $9.91 |

## Configuration Notes

- All testgen/difffix use claude-sonnet-4-6
- Transpilation used claude-sonnet-4-6
- Rust compiled with opt-level = 0 (prevents LLVM optimization artifacts)
- C compiled with clang-21, no optimization flags
- Rust test binary linked without C fallback library
- Rust bridge provides C-ABI wrappers for internal/static functions
- 30s timeout for test binary execution
