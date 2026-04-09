# Goal 2: Fix acosh — wrong output

## Function
- `acosh` (double precision)

## Source Files
- C: `/home/leochanj/Desktop/libmcs/libm/mathd/acoshd.c`
- Rust: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/lib.rs` (wrapper), implementation in `mathd.rs`

## Problem
MISMATCH: acosh(2.0) returns wrong value.
- C:    `acosh 0x1p+1 = 0x1.5124271980434p+0`
- Rust: `acosh 0x1p+1 = 0x1.62e42fefa39efp+0`

The Rust value `0x1.62e42fefa39ef` is ln(2)*2 = 1.3862..., while the correct C
value `0x1.5124271980434` is acosh(2) = 1.3169... The Rust implementation is
computing the wrong formula.

## What Needs to Change
Compare the Rust implementation against the C source in `acoshd.c` and fix the
mathematical computation. The algorithm or formula used in Rust diverges from
the C version.

## Success Criteria
- `acosh(0x1p+1)` returns `0x1.5124271980434p+0` (bitwise exact match with C)
