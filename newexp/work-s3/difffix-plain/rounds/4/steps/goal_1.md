# Goal 1: Fix cacos NaN sign handling

## Function
`cacos` (complex arc cosine, double precision)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/complexd/cacosd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexd.rs` (fn `cacosd`, ~line 278)
- Rust wrapper: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/lib.rs` (line 220)

## Problem
**Wrong output.** When input is `(nan, nan)`, C returns `(-nan, nan)` but Rust returns `(nan, nan)`. The real part should be negative NaN (`-nan`), meaning the sign bit of the NaN must be set.

## What Needs to Change
The Rust `cacosd` implementation must preserve the sign of NaN in the real part of the result to match the C implementation. Likely the C code uses `M_PI - ...` or a negation that produces `-nan` when the input is NaN, and the Rust transpilation lost this sign propagation. Check how the C code computes the real part and ensure the Rust code applies the same arithmetic that sets the NaN sign bit.

## Success Criteria
- `cacos(nan, nan)` returns `(-nan, nan)` — real part has sign bit set
- All other cacos tests continue to pass
- Output is bitwise exact with C
