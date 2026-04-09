# Goal 3: Fix cacos / cacosf — NaN sign mismatch

## Function
- `cacos` (complex double)
- `cacosf` (complex float)

## Source Files
- C: `/home/leochanj/Desktop/libmcs/libm/complexd/cacosd.c`
- C: `/home/leochanj/Desktop/libmcs/libm/complexf/cacosf.c`
- Rust: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/lib.rs` (wrapper)

## Problem
MISMATCH on NaN input:
- C:    `cacos (nan,nan) = -nan,nan`
- Rust: `cacos (nan,nan) = nan,nan`

The real part should be `-nan` but Rust returns `nan`. The sign bit of NaN
matters for bitwise exactness.

Same issue for cacosf.

## What Needs to Change
Compare the Rust cacos/cacosf NaN handling against the C source. The C code
likely negates or sets the sign bit of the real part NaN in a specific code path.
Ensure the Rust code preserves the same NaN sign bit behavior.

## Success Criteria
- `cacos(nan,nan)` returns `(-nan, nan)` — real part has sign bit set
- `cacosf(nan,nan)` returns `(-nan, nan)` — real part has sign bit set
- Bitwise exact match with C output
