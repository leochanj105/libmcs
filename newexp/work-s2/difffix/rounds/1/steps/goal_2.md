# Goal 2: Fix __fpclassifyf enum values

## Function
__fpclassifyf

## Source files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathf/internal/fpclassifyf.c`
- C header: `/home/leochanj/Desktop/libmcs/libm/include/math.h` (lines 50-54)
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s2/src/mathf.rs` (lines 3161-3168)

## Problem
The Rust implementation uses wrong numeric values for the FP classification constants.

C library defines (math.h:50-54):
- FP_NAN = 0
- FP_INFINITE = 1
- FP_ZERO = 2
- FP_SUBNORMAL = 3
- FP_NORMAL = 4

Rust implementation uses:
- FP_ZERO = 0 (should be 2)
- FP_NAN = 1 (should be 0)
- FP_SUBNORMAL = 2 (should be 3)
- FP_INFINITE = 3 (should be 1)
- FP_NORMAL = 4 (correct)

## Failing tests
- `__fpclassifyf 0x0p+0` → C: 2 (FP_ZERO), Rust: 0
- `__fpclassifyf inf` → C: 1 (FP_INFINITE), Rust: 3
- `__fpclassifyf nan` → C: 0 (FP_NAN), Rust: 1
- Plus 1 more mismatch (likely FP_SUBNORMAL)

## What needs to change
Update return values in `mathf.rs:3161-3168` to match the C library's constants:
- `w == 0x00000000` → return 2 (FP_ZERO)
- `w >= 0x00800000 && w <= 0x7f7fffff` → return 4 (FP_NORMAL)
- `w <= 0x007fffff` → return 3 (FP_SUBNORMAL)
- `w == 0x7f800000` → return 1 (FP_INFINITE)
- default → return 0 (FP_NAN)

## Success Criteria
`__fpclassifyf` returns values matching the C library for all classification categories:
zero→2, normal→4, subnormal→3, infinite→1, NaN→0.
