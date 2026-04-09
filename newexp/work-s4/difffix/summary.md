# S4 Diff-Fix Results

## Outcome
**ALL 441 TESTS PASS** after 2 rounds.

## Per-Round Progression

| Round | Prev Fails | Fails | Passed | Pass Rate | Goals | Cost |
|-------|-----------|-------|--------|-----------|-------|------|
| Baseline | — | 5 | 436 | 98.9% | — | — |
| R1 | 5 | 1 | 440 | 99.8% | 4 | $0.88 |
| R2 | 1 | 0 | 441 | 100.0% | 1 | $0.36 |
| **Total** | | | | | **5** | **$1.24** |

## Per-Round Token Usage

| Round | Input | Output | Cache Read | Cache Create | Cost |
|-------|-------|--------|-----------|-------------|------|
| R1 | 32 | 12,479 | 639,813 | 82,737 | $0.88 |
| R2 | 14 | 3,122 | 239,300 | 33,028 | $0.36 |
| **Total** | **46** | **15,601** | **879,113** | **115,765** | **$1.24** |

## Configuration
- REACT_MODE=0 (default: rollback on regression + failed attempt feedback)
- No regression occurred — all rounds improved
- Rust opt-level = 0, no C fallback, Rust bridge, 30s timeout
