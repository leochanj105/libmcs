# Goal 1: Fix __fpclassifyf — wrong classification constants

## Function
`__fpclassifyf`

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathf/internal/fpclassifyf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s5/src/mathf.rs` (fn `__fpclassifyf` at line 3161)

## Problem
MISMATCH — Rust returns wrong classification values. The integer constants for each fp class are different from the C implementation:
- `zero`: C returns 2, Rust returns 0
- `inf`: C returns 1, Rust returns 3
- `subnorm`: C returns 3, Rust returns 2

The Rust code uses different numeric values for FP_ZERO, FP_INFINITE, FP_SUBNORMAL, etc. than the C code.

## What Needs to Change
Read the C source to find the exact constant values used for each classification (FP_NAN, FP_INFINITE, FP_ZERO, FP_SUBNORMAL, FP_NORMAL) and update the Rust `__fpclassifyf` function to return the same values.

## Success Criteria
- `__fpclassifyf zero` returns 2
- `__fpclassifyf inf` returns 1
- `__fpclassifyf subnorm` returns 3
- All 5 `__fpclassifyf` test cases match C output exactly
