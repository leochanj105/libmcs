# Goal 5: Fix modf — wrong fractional part for NaN input

## Function
- `modf` (double)

## Source Files
- C: `/home/leochanj/Desktop/libmcs/libm/mathd/modfd.c`
- Rust: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathd.rs`

## Problem
MISMATCH: modf(nan) should return (nan, int=nan) but Rust returns (0x0p+0, int=nan).

The fractional part should be NaN when the input is NaN, but Rust returns 0.0 for the
fractional part. The integer part is correctly NaN. This indicates the NaN special case
is not handled correctly — the C code returns (NaN, NaN) for NaN input, but the Rust
code appears to fall through to normal processing which produces 0.0 for the fraction.

## What Needs to Change
The Rust modf (modfd) must return NaN for both the fractional and integer parts when
the input is NaN. Check if the Rust code is missing the NaN special-case check or if
the check exists but only sets the integer part.

## Success Criteria
- modf nan = nan int nan — both fractional and integer parts must be NaN, bitwise exact
