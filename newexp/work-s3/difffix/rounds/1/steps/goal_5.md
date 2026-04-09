# Goal 5: Fix catanh / catanhf — NaN sign mismatch in imaginary part

## Function
- `catanh` (complex double)
- `catanhf` (complex float)

## Source Files
- C: `/home/leochanj/Desktop/libmcs/libm/complexd/catanhd.c`
- C: `/home/leochanj/Desktop/libmcs/libm/complexf/catanhf.c`
- Rust: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/lib.rs` (wrapper)

## Problem
MISMATCH on NaN input with zero imaginary:
- C:    `catanh (nan,0x0p+0) = nan,nan`
- Rust: `catanh (nan,0x0p+0) = nan,-nan`

The imaginary part should be `nan` (no sign bit) but Rust returns `-nan`
(NaN with sign bit set). Same for catanhf.

## What Needs to Change
Compare the Rust catanh/catanhf implementation against the C source for the
(NaN, 0) special case. The imaginary part's sign bit handling differs.

## Success Criteria
- `catanh(nan, 0)` returns `(nan, nan)` — imaginary part has no sign bit
- `catanhf(nan, 0)` returns `(nan, nan)` — imaginary part has no sign bit
- Bitwise exact match with C output
