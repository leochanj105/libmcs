# Goal 5: Fix exp2 — wrong result for integer input

## Functions
- exp2

## Source Files
- C: /home/leochanj/Desktop/libmcs/libm/mathd/exp2d.c
- Rust: /home/leochanj/Desktop/libmcs/newexp/rust-s1/src/mathd.rs

## Problem
exp2(10.0) returns `0x1.b2d809254afbcp+11` (~3557.5) instead of `0x1p+10` (1024.0).

The result is ~3.5x too large. The C exp2 likely has a fast path for integer arguments (ldexp(1.0, n)) or a table-based approach. The Rust version appears to be computing incorrectly, possibly due to a wrong constant, table entry, or missing integer special case.

## What Needs to Change
1. Compare the Rust exp2 implementation against the C source (exp2d.c)
2. Check for integer-argument fast path
3. Check table constants and polynomial coefficients
4. Fix the Rust implementation to match C

## Success Criteria
- `exp2(0x1.4p+3)` returns `0x1p+10` (bitwise match, i.e., exp2(10) = 1024)
