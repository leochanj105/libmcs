# Goal 2: Fix casinh / casinhf NaN sign propagation

## Function
casinh (double), casinhf (float)

## Source Files
- C (double): /home/leochanj/Desktop/libmcs/libm/complexd/casinhd.c
- C (float): /home/leochanj/Desktop/libmcs/libm/complexf/casinhf.c
- Rust (double): /home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexd.rs (fn casinhd, line ~303)
- Rust (float): /home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexf.rs (fn casinhf, line ~297)

## What's Wrong
Output mismatch — imaginary part NaN sign differs.
- `casinh(inf, 1)`: C returns `(-nan, nan)`, Rust returns `(-nan, -nan)`
- `casinhf(inf, 1)`: same pattern

The imaginary part should be positive NaN, but Rust produces negative NaN.

## What Needs to Change
Compare the C casinhd/casinhf implementations with the Rust versions. The NaN handling for the case where real part is inf needs to produce positive NaN for the imaginary part, matching the C behavior.

## Success Criteria
- `casinh(inf, 1)` returns `(-nan, nan)` — imaginary part has positive NaN sign bit
- `casinhf(inf, 1)` returns `(-nan, nan)` — same
- All other casinh/casinhf test cases continue to pass
