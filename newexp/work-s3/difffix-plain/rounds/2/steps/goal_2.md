# Goal 2: Fix cacos/cacosf — NaN sign in real part

## Functions
`cacos` (double), `cacosf` (float)

## Source Files
- C sources: `/home/leochanj/Desktop/libmcs/libm/complexd/cacosd.c`, `/home/leochanj/Desktop/libmcs/libm/complexf/cacosf.c`
- Rust sources: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexd.rs` (~line 278), `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexf.rs` (~line 272)

## Problem
Wrong NaN sign. `cacos(nan, nan)` real part: C returns `-nan`, Rust returns `nan`. The sign of the NaN in the real component is wrong.

## What Needs to Change
Read the C source NaN-handling path in cacos/cacosf and ensure the Rust version applies the same sign manipulation (likely a negation) to the real part when inputs are NaN.

## Success Criteria
- `cacos(nan, nan)` returns `(-nan, nan)` — bitwise match with C
- `cacosf(nan, nan)` returns `(-nan, nan)` — bitwise match with C
- All other cacos/cacosf test cases continue to pass
