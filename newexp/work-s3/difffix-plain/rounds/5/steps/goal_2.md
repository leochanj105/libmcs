# Goal 2: Fix cacosf (float) — wrong sign on zero and NaN

## Function
`cacosf` (complex arc cosine, float precision)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/complexf/cacosf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexf.rs` (function `cacosf`)

## Problem
MISMATCH — Rust produces wrong sign in two cases (same pattern as cacos double):

1. `cacosf(1.0 + 0.0i)`: C returns `0x0p+0, 0x0p+0` but Rust returns `-0x0p+0, 0x0p+0`
   - The real part has wrong sign: `-0x0p+0` instead of `0x0p+0`
2. `cacosf(inf + 0.0i)`: C returns `nan, inf` but Rust returns `-nan, inf`
   - The NaN has wrong sign bit

## What Needs to Change
The Rust `cacosf` function needs to match the C implementation's sign handling for edge cases:
- When the input is exactly `(1.0, 0.0)`, the real part of the result must be `+0.0`, not `-0.0`
- When the input is `(inf, 0.0)`, the NaN sign bit must match the C output

Compare the Rust implementation against the C source in `cacosf.c` to find where the sign is being flipped or lost.

## Success Criteria
- `cacosf(1.0 + 0.0i)` returns `0x0p+0, 0x0p+0` (bitwise match with C)
- `cacosf(inf + 0.0i)` returns `nan, inf` (bitwise match with C, same NaN sign bit)
