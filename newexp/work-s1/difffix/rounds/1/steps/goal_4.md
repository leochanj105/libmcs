# Goal 4: Fix acosh — wrong computation for normal inputs

## Functions
- acosh

## Source Files
- C: /home/leochanj/Desktop/libmcs/libm/mathd/acoshd.c
- Rust: /home/leochanj/Desktop/libmcs/newexp/rust-s1/src/mathd.rs

## Problem
acosh returns wrong values for normal inputs:
- acosh(2.0): C returns `0x1.5124271980434p+0`, Rust returns `0x1.62e42fefa39efp+0`
- acosh(1.5): C returns `0x1.ecc2caec5160ap-1`, Rust returns `0x1.9f323ecbf984cp-1`

Note: Rust's acosh(2.0) = `0x1.62e42fefa39efp+0` is actually ln(2)*2 ≈ 1.3863, while C's correct value is ≈ 1.3170. The formula acosh(x) = log(x + sqrt(x*x - 1)) should give ~1.3170 for x=2. This suggests the Rust implementation has a formula error or incorrect branch selection.

## What Needs to Change
1. Compare the Rust acosh implementation against the C source (acoshd.c)
2. Check the formula and branch conditions (typically: large x uses log(2x), medium x uses log(x+sqrt(x^2-1)), near-1 uses log1p)
3. Fix the Rust implementation to match C logic

## Success Criteria
- `acosh(0x1p+1)` returns `0x1.5124271980434p+0` (bitwise match)
- `acosh(0x1.8p+0)` returns `0x1.ecc2caec5160ap-1` (bitwise match)
