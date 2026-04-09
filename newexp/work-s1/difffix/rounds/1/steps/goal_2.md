# Goal 2: Fix pow / cpow — integer exponent case

## Functions
- pow, cpow

## Source Files
- C: /home/leochanj/Desktop/libmcs/libm/mathd/powd.c, /home/leochanj/Desktop/libmcs/libm/complexd/cpowd.c
- Rust: /home/leochanj/Desktop/libmcs/newexp/rust-s1/src/mathd.rs, /home/leochanj/Desktop/libmcs/newexp/rust-s1/src/complexd.rs

## Problem
pow(2.0, 3.0) returns `0x1.fffee746db0fcp+5` (~63.998) instead of `0x1p+3` (8.0).
cpow((2+0i), (3+0i)) has the same error — cpow delegates to exp/log/pow.

The result is ~8x too large and not even close, suggesting the Rust pow is computing via exp(y*log(x)) without the integer-exponent fast path that the C version uses, or the exp/log implementations themselves have large errors.

## What Needs to Change
1. Check if Rust pow has the integer-exponent special case (when y is a small integer, compute by repeated multiplication)
2. If the fast path exists, check that the condition to trigger it matches C
3. If it doesn't exist, port it from the C source
4. cpow should automatically be fixed once pow is correct

## Success Criteria
- `pow(0x1p+1, 0x1.8p+1)` returns `0x1p+3` (bitwise match)
- `cpow(0x1p+1+0x0p+0i, 0x1.8p+1+0x0p+0i)` returns `0x1p+3+0x0p+0i` (bitwise match)
