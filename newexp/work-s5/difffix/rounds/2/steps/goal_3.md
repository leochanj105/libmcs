# Goal 3: Fix ilogbf — wrong result for zero input

## Function
`ilogbf` (float precision)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathf/ilogbf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s5/src/mathf.rs` (fn `ilogbf` around line 1971)

## Problem
MISMATCH — 1 test case:
- `ilogbf 0.0f`: C returns `-2147483647` (FP_ILOGB0), Rust returns `-2147483648` (INT_MIN)

The FP_ILOGB0 constant is wrong, same issue as the double version.

## What Needs to Change
Fix the return value for zero input to match the C `FP_ILOGB0` value (`-2147483647` instead of `-2147483648`).

## Success Criteria
- `ilogbf 0.0f` returns `-2147483647`
- All ilogbf test cases match C output exactly
