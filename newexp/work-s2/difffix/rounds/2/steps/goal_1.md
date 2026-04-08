# Goal 1: Fix __fpclassifyf classification constants

## Function
`__fpclassifyf`

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathf/internal/fpclassifyf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s2/src/mathf.rs` (line ~3161)

## Problem
**Wrong output.** The Rust implementation returns incorrect FP classification constants. The C and Rust versions use different integer values for the classification categories:

| Input | C result | Rust result |
|-------|----------|-------------|
| `0x0p+0` (zero) | 2 | 0 |
| `inf` | 1 | 3 |
| `nan` | 0 | 1 |

The classification enum mapping is wrong — the Rust code likely uses a different set of constants than the C code expects.

## What Needs to Change
The Rust `__fpclassifyf` must return the same integer constants as the C version for each FP class (NaN=0, Inf=1, Zero=2, Subnormal=3, Normal=4 — verify against C source). Align the return values to match the C implementation exactly.

## Success Criteria
- `__fpclassifyf(0x0p+0)` returns `2`
- `__fpclassifyf(inf)` returns `1`
- `__fpclassifyf(nan)` returns `0`
- All 4 previously mismatched test cases produce bitwise-identical output to C
