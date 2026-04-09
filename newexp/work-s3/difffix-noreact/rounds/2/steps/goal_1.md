# Goal 1: Fix acosh — wrong computation

## Function
`acosh` (double precision)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/acoshd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathd.rs` (function `acoshd`, ~line 1385)

## Problem
Wrong output. `acosh(2.0)` returns `0x1.62e42fefa39efp+0` (which is ln(2)) instead of the correct `0x1.5124271980434p+0`.

The Rust implementation computes the wrong value — likely using an incorrect formula. The correct value of acosh(2) ~ 1.3169578969248.  The Rust result 0x1.62e4... ~ 1.3862... which is ln(2) * 2 / some factor. The formula may have a bug in the mathematical expression.

## What Needs to Change
Read the C source and the Rust source, compare the acosh implementation logic, and fix the mathematical formula in the Rust version to match the C version exactly.

## Success Criteria
- `acosh(0x1p+1)` returns `0x1.5124271980434p+0` (bitwise match with C)
- All other acosh test cases continue to pass
