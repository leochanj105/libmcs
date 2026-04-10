# Goal 3: Fix ilogb — wrong results for zero and subnormals

## Function
`ilogb` (double precision, aliased from `ilogbd`)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/ilogbd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s6/src/mathd.rs` (line ~2753)

## Problem
MISMATCH — 4 test failures.

1. `ilogb(0.0)` returns `-2147483648` (INT_MIN) instead of `-2147483647` (INT_MIN+1 = FP_ILOGB0).
2. Subnormal inputs are off by 1: `ilogb(0x1p-1074)` returns `-1075` instead of `-1074`.

Examples:
- C:    `ilogb 0.0 = -2147483647`
- Rust: `ilogb 0.0 = -2147483648`
- C:    `ilogb 0x1p-1074 = -1074`
- Rust: `ilogb 0x1p-1074 = -1075`

## What Needs to Change
1. The zero case must return `FP_ILOGB0` which is `-2147483647` (0x80000001), not `INT_MIN` (-2147483648).
2. The subnormal exponent calculation is off by 1 — likely a fencepost error in counting leading zeros or adjusting the bias.

## Success Criteria
- `ilogb(0.0)` returns exactly `-2147483647`.
- `ilogb(0x1p-1074)` returns exactly `-1074`.
- `ilogb(0x1p-1073)` returns exactly `-1073`.
- All 4 ilogb mismatches resolve to bitwise-exact match with C output.
