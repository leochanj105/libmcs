# Goal 3: Fix casinh/casinhf — NaN sign in imaginary part

## Functions
`casinh` (double), `casinhf` (float)

## Source Files
- C sources: `/home/leochanj/Desktop/libmcs/libm/complexd/casinhd.c`, `/home/leochanj/Desktop/libmcs/libm/complexf/casinhf.c`
- Rust sources: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexd.rs` (~line 301), `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexf.rs` (~line 295)

## Problem
Wrong NaN sign in imaginary part. `casinh(nan, 0)` imaginary part: C returns `nan`, Rust returns `-nan`.

## What Needs to Change
Read the C source NaN-handling path in casinh/casinhf and ensure the Rust version produces the correct sign for the imaginary part when real input is NaN and imaginary input is zero.

## Success Criteria
- `casinh(nan, 0x0p+0)` returns `(-nan, nan)` — bitwise match with C
- `casinhf(nan, 0x0p+0)` returns `(-nan, nan)` — bitwise match with C
- All other casinh/casinhf test cases continue to pass
