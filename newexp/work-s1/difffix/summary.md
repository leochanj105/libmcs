# S1 Diff-Fix Results

## Outcome
**ALL 779 TESTS PASS** after 3 rounds.

## Per-Round Progression

| Round | Prev Fails | Fails | Passed | Goals | Cost |
|-------|-----------|-------|--------|-------|------|
| Baseline | — | 683 | 96 | — | — |
| R1 | 683 | 9 | 770 | 3 | $1.66 |
| R2 | 9 | 3 | 776 | 5 | $3.12 |
| R3 | 3 | 0 | 779 | 3 | $0.63 |
| **Total** | | | | **11** | **$5.42** |

## Per-Round Token Usage

| Round | Input | Output | Cache Read | Cache Create | Cost |
|-------|-------|--------|-----------|-------------|------|
| R1 | 40 | 20,240 | 987,365 | 101,754 | $1.66 |
| R2 | 89 | 86,328 | 2,684,733 | 210,299 | $3.12 |
| R3 | 29 | 8,432 | 473,751 | 48,156 | $0.63 |
| **Total** | **158** | **115,000** | **4,145,849** | **360,209** | **$5.42** |

## Round Details

### Round 1: 683 → 9 failures (3 goals)
- Fixed exp2d infinite recursion crash (LLVM optimizes `pow(2.0, x)` → `exp2(x)`)
- Fixed exp2f same issue (float version)
- Fixed acoshd formula bug (missing `sqrt` in else branch)
- These 3 fixes unblocked 154 missing functions / 674 tests

### Round 2: 9 → 3 failures (5 goals)
- Fixed remaining mismatches in cexpf, cpow, cproj, cprojf, exp2, log1pf, pow, sinf, tanf

### Round 3: 3 → 0 failures (3 goals)
- Fixed final 3 mismatches to achieve 100% pass rate

## Git Tags (in rust-s1/)
- `pre-round-1`, `post-round-1`
- `pre-round-2`, `post-round-2`
- `pre-round-3`, `post-round-3`

Use `git diff pre-round-N post-round-N` to see changes per round.

## Model
All AI calls used claude-sonnet-4-6 via `claude-sonnet` wrapper.
Analysis step uses ANALYSIS_CMD (defaults to claude/opus).
