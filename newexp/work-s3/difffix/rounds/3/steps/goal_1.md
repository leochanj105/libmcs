# Goal 1: Fix cacos / cacosf NaN sign propagation

## Function
cacos (double), cacosf (float)

## Source Files
- C (double): /home/leochanj/Desktop/libmcs/libm/complexd/cacosd.c
- C (float): /home/leochanj/Desktop/libmcs/libm/complexf/cacosf.c
- Rust (double): /home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexd.rs (fn cacosd, line ~278)
- Rust (float): /home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexf.rs (fn cacosf, line ~272)

## What's Wrong
Output mismatch — NaN sign differs.
- `cacos(inf, 0)`: C returns `(nan, inf)`, Rust returns `(-nan, inf)`
- `cacosf(inf, 0)`: same pattern

The real part should be NaN (positive NaN bit pattern), but Rust produces negative NaN.

## What Needs to Change
Compare the C cacosd/cacosf implementations with the Rust versions. The NaN generation or sign handling for the inf input special case needs to match the C behavior exactly. Likely the Rust code computes `acos(inf)` differently or applies a sign flip that shouldn't be there.

## Success Criteria
- `cacos(inf, 0)` returns `(nan, inf)` — real part has positive NaN sign bit
- `cacosf(inf, 0)` returns `(nan, inf)` — same
- All other cacos/cacosf test cases continue to pass
