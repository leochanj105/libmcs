# Goal 4: Fix casinh / casinhf — NaN sign mismatch in imaginary part

## Function
- `casinh` (complex double)
- `casinhf` (complex float)

## Source Files
- C: `/home/leochanj/Desktop/libmcs/libm/complexd/casinhd.c`
- C: `/home/leochanj/Desktop/libmcs/libm/complexf/casinhf.c`
- Rust: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/lib.rs` (wrapper)

## Problem
MISMATCH on NaN input with zero imaginary:
- C:    `casinh (nan,0x0p+0) = -nan,nan`
- Rust: `casinh (nan,0x0p+0) = -nan,-nan`

The imaginary part should be `nan` (positive NaN) but Rust returns `-nan`
(NaN with sign bit set). Same for casinhf.

## What Needs to Change
Compare the Rust casinh/casinhf implementation against the C source for the
(NaN, 0) special case. The imaginary part's sign bit handling differs.

## Success Criteria
- `casinh(nan, 0)` returns `(-nan, nan)` — imaginary part has no sign bit
- `casinhf(nan, 0)` returns `(-nan, nan)` — imaginary part has no sign bit
- Bitwise exact match with C output
