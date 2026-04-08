# Compact Divergences — Round 3

## MISMATCH (1 test, 1 function)

| # | Function | Type | Detail |
|---|----------|------|--------|
| 1 | `nexttowardf` | wrong output | `nexttowardf(0x1p+0, 0x8p-2)` → C: `0x1.000002p+0`, Rust: `0x1.fffffep-1`. Steps away from target instead of toward it. Root cause: ABI mismatch — C passes `long double y` (80-bit, on stack) but Rust declares `y: f64` (64-bit, in XMM register), so Rust reads garbage for y. Same bug as `nexttoward` which was fixed in round 2 by removing the Rust export. |

## NOT IMPLEMENTED (3 functions)

| # | Function | C Source |
|---|----------|----------|
| 2 | `__ccoshsinh` | complexd/internal/ctrigd.c |
| 3 | `__ccoshsinhf` | complexf/internal/ctrigf.c |
| 4 | `__fpclassifyd` | mathd/internal/fpclassifyd.c |

## EXTRA (Rust-only, not in C)

5 extra fenv tests with NULL args — Rust stubs unconditionally return -1, producing output where C does not. Low priority; not a correctness issue for math functions.
