# Goal 4: Fix casinhf NaN sign in imaginary part

## Function
`casinhf` (complex arc hyperbolic sine, float precision)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/complexf/casinhf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexf.rs` (fn `casinhf`, ~line 295)

## Problem
**Wrong output.** When input is `(nan, 0x0p+0)`, C returns `(-nan, nan)` but Rust returns `(-nan, -nan)`. The imaginary part should be positive NaN, but Rust produces negative NaN. Same root cause as casinh (goal_3) but in the float variant.

## What Needs to Change
The Rust `casinhf` implementation must produce the correct sign on the imaginary part's NaN. This is the float-precision analog of goal_3. Check how the C code computes the imaginary part and replicate the same NaN sign behavior.

## Success Criteria
- `casinhf(nan, 0x0p+0)` returns `(-nan, nan)` — imaginary part has positive NaN
- All other casinhf tests continue to pass
- Output is bitwise exact with C
