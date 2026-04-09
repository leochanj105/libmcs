# Goal 3: Fix casinh (double) — wrong NaN sign in imaginary part

## Function
`casinh` (complex arc hyperbolic sine, double precision)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/complexd/casinhd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexd.rs` (function `casinhd`)

## Problem
MISMATCH — Rust produces wrong sign on NaN in imaginary part:

- `casinh(inf + 1.0i)`: C returns `-nan, nan` but Rust returns `-nan, -nan`
  - The imaginary part NaN has wrong sign: `-nan` instead of `nan`

## What Needs to Change
The Rust `casinhd` function needs to match the C implementation's NaN sign bit handling for the case where the real part is infinity. Compare the Rust implementation against the C source in `casinhd.c` to find where the imaginary part's NaN sign is being set incorrectly.

## Success Criteria
- `casinh(inf + 1.0i)` returns `-nan, nan` (bitwise match with C, correct NaN sign bits)
