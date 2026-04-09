# S3 Diff-Fix Results

## Outcome
**1187/1189 tests pass** after 5 rounds. 2 remaining failures (NaN sign bit).

## Per-Round Progression

| Round | Prev Fails | Fails | Passed | Pass Rate | Goals | Cost |
|-------|-----------|-------|--------|-----------|-------|------|
| Baseline | — | 52 | 1137 | 95.6% | — | — |
| R1 | 52 | 38 | 1151 | 96.8% | 5 | $4.52 |
| R2 | 38 | 31 | 1158 | 97.4% | 5 | $2.37 |
| R3 | 31 | 7 | 1182 | 99.4% | 5 | $1.46 |
| R4 | 7 | 8 | 1181 | 99.3% | 5 | $1.01 |
| R5 | 8 | 2 | 1187 | 99.8% | 5 | $0.55 |
| **Total** | | | | | **25** | **$9.91** |

Note: R4 regressed (7→8). No rollback — R5 received regression feedback
and fixed the regressions while preserving R4's good fixes (e.g. log1pf).

## Per-Round Token Usage

| Round | Input | Output | Cache Read | Cache Create | Cost |
|-------|-------|--------|-----------|-------------|------|
| R1 | 90 | 147,503 | 3,329,913 | 252,778 | $4.52 |
| R2 | 73 | 55,197 | 2,063,479 | 164,244 | $2.37 |
| R3 | 62 | 26,444 | 1,452,935 | 125,252 | $1.46 |
| R4 | 42 | 22,108 | 726,451 | 84,873 | $1.01 |
| R5 | 32 | 7,670 | 464,504 | 78,599 | $0.55 |
| **Total** | **299** | **258,922** | **8,037,282** | **705,746** | **$9.91** |

## Remaining Failures (2)

- `cacos(inf,0)`: C returns `(nan,inf)`, Rust returns `(-nan,inf)` — NaN sign bit
- `cacosf(inf,0)`: same issue, float version

## Configuration
- Rust opt-level = 0 (no LLVM optimization)
- No C fallback (pure Rust binary)
- Rust bridge for internal/static functions
- 30s timeout for hang detection
- No rollback on regression — regression feedback to next round instead

## Git Tags (in rust-s3/)
- `pre-round-1` through `pre-round-5`
- `post-round-1` through `post-round-5`
