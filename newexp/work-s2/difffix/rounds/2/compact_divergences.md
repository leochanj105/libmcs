# Compact Divergences — Round 2

## MISMATCH (10 tests, 7 functions)

| # | Function | Type | Detail |
|---|----------|------|--------|
| 1 | `__fpclassifyf` | wrong output | Returns wrong FP classification constants (4 mismatches). C: 2,1,0; Rust: 0,3,1 for zero/inf/nan. Classification enum values differ. |
| 2 | `cproj` | wrong output | `cproj(inf+1i)` → C: `inf+0i`, Rust: `inf+1i`. Imaginary part not zeroed for infinite input. |
| 3 | `exp2` | wrong output | `exp2(10.0)` → C: `1024.0`, Rust: `3494.85...`. Completely wrong result, likely algorithm bug. |
| 4 | `lgamma` | wrong output | `lgamma(-0.5)` signgam: C: `-1`, Rust: `0`. Sign of gamma not set correctly. |
| 5 | `nexttoward` | wrong output | `nexttoward(1.0, 2.0)` → C: next float above 1.0, Rust: next float below 1.0. Direction reversed. |
| 6 | `nexttowardf` | wrong output | `nexttowardf(1.0, 2.0)` → C: next float above 1.0, Rust: next float below 1.0. Direction reversed. |
| 7 | `pow` | wrong output | `pow(2.0, 10.0)` → C: `1024.0`, Rust: `3494.85...`. Same wrong result as exp2 — likely shares broken code path. |

## NOT IMPLEMENTED (3 functions)

| # | Function | C Source |
|---|----------|----------|
| 8 | `__ccoshsinh` | complexd/internal/ctrigd.c |
| 9 | `__ccoshsinhf` | complexf/internal/ctrigf.c |
| 10 | `__fpclassifyd` | mathd/internal/fpclassifyd.c |

## EXTRA (Rust-only, not in C)

5 extra fenv tests with NULL args — Rust adds NULL-guard tests not present in C. Low priority.
