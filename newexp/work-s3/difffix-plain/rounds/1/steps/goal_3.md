# Goal 3: Fix pow (double) — wrong values (likely exp2 dependency)

## Function
`pow` (double-precision)

## Source files
- C: /home/leochanj/Desktop/libmcs/libm/mathd/powd.c
- Rust: /home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathd.rs

## Problem
pow returns wrong results:
- pow(2, 10) = 0x1.b2d809254afbcp+11 (~3566.9, should be 0x1p+10 = 1024)
- pow(-2, 3) = -0x1.fffee746db0fcp+5 (~-63.998, should be -0x1p+3 = -8)

Note: pow(2,10) produces the exact same wrong value as exp2(10), strongly suggesting pow uses exp2 internally.

## What needs to change
1. Fix exp2 first (Goal 2) — this will likely fix pow(2,10)
2. If pow(-2,3) still fails after exp2 fix, check the negative base handling path in the pow implementation

## Success Criteria
- `pow 0x1p+1 0x1.4p+3` = `0x1p+10` (bitwise exact)
- `pow -0x1p+1 0x1.8p+1` = `-0x1p+3` (bitwise exact)
- All other pow tests continue to pass
