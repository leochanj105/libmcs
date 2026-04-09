# Goal 4: Fix catanh/catanhf — NaN sign in imaginary part

## Functions
`catanh` (double), `catanhf` (float)

## Source Files
- C sources: `/home/leochanj/Desktop/libmcs/libm/complexd/catanhd.c`, `/home/leochanj/Desktop/libmcs/libm/complexf/catanhf.c`
- Rust sources: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexd.rs` (~line 332), `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexf.rs` (~line 326)

## Problem
Wrong NaN sign in imaginary part. `catanh(nan, 0)` imaginary part: C returns `nan`, Rust returns `-nan`.

## What Needs to Change
Read the C source NaN-handling path in catanh/catanhf and ensure the Rust version produces the correct sign for the imaginary part when real input is NaN and imaginary input is zero.

## Success Criteria
- `catanh(nan, 0x0p+0)` returns `(nan, nan)` — bitwise match with C
- `catanhf(nan, 0x0p+0)` returns `(nan, nan)` — bitwise match with C
- All other catanh/catanhf test cases continue to pass
