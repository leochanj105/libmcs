# Goal 3: Fix casinh NaN sign in imaginary part

## Function
`casinh` (complex arc hyperbolic sine, double precision)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/complexd/casinhd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexd.rs` (fn `casinhd`, ~line 301)
- Rust wrapper: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/lib.rs` (line 222)

## Problem
**Wrong output.** When input is `(nan, 0x0p+0)`, C returns `(-nan, nan)` but Rust returns `(-nan, -nan)`. The imaginary part should be positive NaN, but Rust produces negative NaN (sign bit set when it shouldn't be).

## What Needs to Change
The Rust `casinhd` implementation must produce the correct sign on the imaginary part's NaN. Check the C code's computation for the imaginary part when real=nan, imag=0. The sign bit of the NaN in the imaginary part must match the C output (positive NaN).

## Success Criteria
- `casinh(nan, 0x0p+0)` returns `(-nan, nan)` — imaginary part has positive NaN
- All other casinh tests continue to pass
- Output is bitwise exact with C
