# S2 Diff-Fix Results

## Outcome
**ALL 458 TESTS PASS** after 3 rounds.

## Per-Round Progression

| Round | Prev Fails | Fails | Passed | Pass Rate | Goals | Cost |
|-------|-----------|-------|--------|-----------|-------|------|
| Baseline | — | 405 | 53 | 11.6% | — | — |
| R1 | 405 | 10 | 448 | 97.8% | 5 | $2.20 |
| R2 | 10 | 1 | 457 | 99.8% | 5 | $3.55 |
| R3 | 1 | 0 | 458 | 100.0% | 4 | $1.35 |
| **Total** | | | | | **14** | **$7.09** |

## Per-Round Token Usage

| Round | Input | Output | Cache Read | Cache Create | Cost |
|-------|-------|--------|-----------|-------------|------|
| R1 | 66 | 33,190 | 2,029,830 | 145,795 | $2.20 |
| R2 | 121 | 76,196 | 4,794,469 | 204,147 | $3.55 |
| R3 | 58 | 18,073 | 1,302,338 | 91,106 | $1.35 |
| **Total** | **245** | **127,459** | **8,126,637** | **441,048** | **$7.09** |

## Git Tags (in rust-s2/)
- `pre-round-1`, `post-round-1`
- `pre-round-2`, `post-round-2`
- `pre-round-3`, `post-round-3`

## Model
All AI calls used claude-sonnet-4-6.
