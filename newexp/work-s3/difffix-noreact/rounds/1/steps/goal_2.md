# Goal 2: Fix exp2 (double) — wrong values

## Function
`exp2` (double-precision)

## Source files
- C: /home/leochanj/Desktop/libmcs/libm/mathd/exp2d.c
- Rust: /home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathd.rs

## Problem
exp2 returns wrong results:
- exp2(0x1.ff8p+9) = 0x1.ffffffffcf4p+1022 (should be 0x1p+1023)
- exp2(0x1.4p+3) = 0x1.b2d809254afbcp+11 (should be 0x1p+10, i.e. 1024)

exp2(10) returning ~3566.9 instead of 1024 indicates a fundamental computation error.

## What needs to change
Compare Rust exp2 against C exp2d.c. The algorithm for integer exponents and near-integer exponents is likely broken — possibly wrong polynomial coefficients, incorrect range reduction, or mishandled table lookup.

## Success Criteria
- `exp2 0x1.ff8p+9` = `0x1p+1023` (bitwise exact)
- `exp2 0x1.4p+3` = `0x1p+10` (bitwise exact)
- All other exp2 tests continue to pass
