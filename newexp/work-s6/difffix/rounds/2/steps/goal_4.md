# Goal 4: Fix ilogbf — wrong result for zero

## Function
`ilogbf` (float precision)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathf/ilogbf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s6/src/mathf.rs` (line ~1971)

## Problem
MISMATCH — 1 test failure.

`ilogbf(0.0f)` returns `-2147483648` (INT_MIN) instead of `-2147483647` (FP_ILOGB0).

Example:
- C:    `ilogbf 0.0f = -2147483647`
- Rust: `ilogbf 0.0f = -2147483648`

## What Needs to Change
The zero case must return `FP_ILOGB0` = `-2147483647` (0x80000001i32), not `i32::MIN` (-2147483648). Check the C source for the exact constant used and mirror it.

## Success Criteria
- `ilogbf(0.0f)` returns exactly `-2147483647`.
- Bitwise-exact match with C output for all ilogbf test cases.
