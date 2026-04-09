# Goal 2: Fix ilogb — wrong results for zero and subnormals

## Function
`ilogb` (double precision, `ilogbd` in Rust)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/ilogbd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s5/src/mathd.rs` (fn `ilogbd` around line 2753)

## Problem
MISMATCH — 4 test cases produce wrong results:
1. `ilogb 0.0`: C returns `-2147483647` (FP_ILOGB0), Rust returns `-2147483648` (INT_MIN)
2. `ilogb 0x1p-1074`: C returns `-1074`, Rust returns `-1075`
3. `ilogb 0x1p-1073`: C returns `-1073`, Rust returns `-1074`
4. `ilogb 0x1p-1074` (2nd test): C returns `-1074`, Rust returns `-1075`

Two issues:
- The FP_ILOGB0 constant for zero input is wrong (off by 1)
- Subnormal exponent calculation is off by 1

## What Needs to Change
1. Fix the return value for zero input to match the C `FP_ILOGB0` value (`-2147483647`, not `-2147483648`)
2. Fix subnormal exponent extraction — the bit counting or bias is off by 1

## Success Criteria
- `ilogb 0.0` returns `-2147483647`
- `ilogb 0x1p-1074` returns `-1074`
- `ilogb 0x1p-1073` returns `-1073`
- All ilogb test cases match C output exactly
