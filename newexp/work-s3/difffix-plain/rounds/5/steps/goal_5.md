# Goal 5: Fix logb (double) — wrong result for subnormal input

## Function
`logb` (extract exponent as floating-point, double precision)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/logbd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathd.rs` (function `logbd`)

## Problem
MISMATCH — Rust returns wrong exponent for a subnormal input:

- `logb(0x0.0000000000001p-1022)`: C returns `-0x1.0c8p+10` (i.e., -1074) but Rust returns `-0x1.0ccp+10` (i.e., -1075)
  - Rust is off by 1 for the minimum subnormal double
  - `0x0.0000000000001p-1022` = 2^(-1074), so `logb` should return -1074
  - Rust returns -1075, which is incorrect

## What Needs to Change
The Rust `logbd` function has an off-by-one error in subnormal handling. The C implementation normalizes subnormals by counting leading zeros or shifting, and the Rust version likely has a fencepost error in this logic. Compare the bit-counting/normalization code against `logbd.c`.

## Success Criteria
- `logb(0x0.0000000000001p-1022)` returns `-0x1.0c8p+10` (-1074) (bitwise match with C)
