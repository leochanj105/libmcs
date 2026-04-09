# Goal 4: Fix ilogb / ilogbf FP_ILOGB0 and subnormal handling

## Function
ilogb (double), ilogbf (float)

## Source Files
- C (double): /home/leochanj/Desktop/libmcs/libm/mathd/ilogbd.c
- C (float): /home/leochanj/Desktop/libmcs/libm/mathf/ilogbf.c
- Rust (double): /home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathd.rs (fn ilogbd, line ~2753)
- Rust (float): /home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathf.rs (fn ilogbf, line ~1971)

## What's Wrong
Output mismatch:
- `ilogb(0)`: C returns -2147483647 (INT_MAX-based), Rust returns -2147483648 (INT_MIN)
- `ilogb(-0)`: same
- `ilogb(subnormal 0x0.0000000000001p-1022)`: C returns -1074, Rust returns -1075
- `ilogbf(0)`: C returns -2147483647, Rust returns -2147483648

Two issues:
1. FP_ILOGB0 constant: C uses -2147483647 (INT_MAX negated or INT_MIN+1), Rust uses INT_MIN
2. Subnormal exponent: off-by-one in the bit counting/normalization loop

## What Needs to Change
1. Update the FP_ILOGB0 return value in both ilogbd and ilogbf to return -2147483647 instead of -2147483648 for zero inputs.
2. Fix the subnormal exponent calculation in ilogbd — the normalization loop or initial exponent bias is off by one.

## Success Criteria
- `ilogb(0)` and `ilogb(-0)` return -2147483647
- `ilogbf(0)` returns -2147483647
- `ilogb(0x0.0000000000001p-1022)` returns -1074
- All other ilogb/ilogbf test cases continue to pass
