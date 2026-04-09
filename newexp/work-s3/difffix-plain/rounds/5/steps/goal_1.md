# Goal 1: Fix cacos (double) — wrong sign on zero and NaN

## Function
`cacos` (complex arc cosine, double precision)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/complexd/cacosd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexd.rs` (function `cacosd`)

## Problem
MISMATCH — Rust produces wrong sign in two cases:

1. `cacos(1.0 + 0.0i)`: C returns `0x0p+0, 0x0p+0` but Rust returns `-0x0p+0, 0x0p+0`
   - The real part has wrong sign: `-0x0p+0` instead of `0x0p+0`
2. `cacos(inf + 0.0i)`: C returns `nan, inf` but Rust returns `-nan, inf`
   - The NaN has wrong sign bit

## What Needs to Change
The Rust `cacosd` function needs to match the C implementation's sign handling for edge cases:
- When the input is exactly `(1.0, 0.0)`, the real part of the result must be `+0.0`, not `-0.0`
- When the input is `(inf, 0.0)`, the NaN sign bit must match the C output

Compare the Rust implementation against the C source in `cacosd.c` to find where the sign is being flipped or lost.

## Success Criteria
- `cacos(1.0 + 0.0i)` returns `0x0p+0, 0x0p+0` (bitwise match with C)
- `cacos(inf + 0.0i)` returns `nan, inf` (bitwise match with C, same NaN sign bit)
