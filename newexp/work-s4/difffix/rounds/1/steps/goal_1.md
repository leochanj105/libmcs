# Goal 1: Fix __fpclassifyf — wrong FP classification constants

## Function
`__fpclassifyf`

## Source Files
- **C source**: `/home/leochanj/Desktop/libmcs/libm/mathf/internal/fpclassifyf.c`
- **Rust source**: `/home/leochanj/Desktop/libmcs/newexp/rust-s4/src/mathf.rs:3161`

## Problem
The Rust implementation uses incorrect integer constants for FP classification categories.

The C code returns the platform `<math.h>` constants:
- `FP_ZERO = 2`
- `FP_INFINITE = 1`
- `FP_NAN = 0`
- `FP_NORMAL = 4`
- `FP_SUBNORMAL = 3`

The Rust code currently returns:
- `FP_ZERO = 0` (wrong, should be 2)
- `FP_INFINITE = 3` (wrong, should be 1)
- `FP_NAN = 1` (wrong, should be 0)
- `FP_NORMAL = 4` (correct)
- `FP_SUBNORMAL = 2` (wrong, should be 3)

## Failing Tests
- `__fpclassifyf(0x0p+0)`: C returns 2, Rust returns 0
- `__fpclassifyf(inf)`: C returns 1, Rust returns 3

## What Needs to Change
In `/home/leochanj/Desktop/libmcs/newexp/rust-s4/src/mathf.rs` at line 3161, update the return values:
- `0x00000000` (zero) → return `2` (was 0)
- `0x7f800000` (infinity) → return `1` (was 3)
- default (NaN) → return `0` (was 1)
- subnormal → return `3` (was 2)

## Success Criteria
- `__fpclassifyf(0x0p+0)` returns `2` (bitwise match with C)
- `__fpclassifyf(inf)` returns `1` (bitwise match with C)
- All other __fpclassifyf test cases continue to pass
