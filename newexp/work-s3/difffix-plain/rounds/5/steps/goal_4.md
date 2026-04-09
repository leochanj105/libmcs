# Goal 4: Fix casinhf (float) — wrong NaN sign in imaginary part

## Function
`casinhf` (complex arc hyperbolic sine, float precision)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/complexf/casinhf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexf.rs` (function `casinhf`)

## Problem
MISMATCH — Rust produces wrong sign on NaN in imaginary part (same pattern as casinh double):

- `casinhf(inf + 1.0i)`: C returns `-nan, nan` but Rust returns `-nan, -nan`
  - The imaginary part NaN has wrong sign: `-nan` instead of `nan`

## What Needs to Change
The Rust `casinhf` function needs to match the C implementation's NaN sign bit handling for the case where the real part is infinity. Compare the Rust implementation against the C source in `casinhf.c` to find where the imaginary part's NaN sign is being set incorrectly.

## Success Criteria
- `casinhf(inf + 1.0i)` returns `-nan, nan` (bitwise match with C, correct NaN sign bits)
