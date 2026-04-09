# Goal 1: Fix sinf / tanf / cexpf — float trig kernel precision

## Functions
- sinf, tanf, cexpf

## Source Files
- C: /home/leochanj/Desktop/libmcs/libm/mathf/sinf.c, /home/leochanj/Desktop/libmcs/libm/mathf/tanf.c, /home/leochanj/Desktop/libmcs/libm/complexf/cexpf.c
- C internal: /home/leochanj/Desktop/libmcs/libm/mathf/internal/trigf.c (__rem_pio2f, __sinf, __cosf)
- Rust: /home/leochanj/Desktop/libmcs/newexp/rust-s1/src/mathf.rs, /home/leochanj/Desktop/libmcs/newexp/rust-s1/src/complexf.rs

## Problem
sinf and tanf produce wrong results at input `0x1.921fb6p+1` (float representation of pi).
- sinf: C returns `-0x1.777a5cp-24`, Rust returns `-0x1.6bff7ap-16` (~256x larger error)
- tanf: C returns `0x1.777a5cp-24`, Rust returns `0x1.6bff7ap-16`
- cexpf: imaginary part wrong because it uses sinf internally

The error magnitude difference (~2^8) suggests the float argument reduction (__rem_pio2f) or the polynomial kernel (__sinf/__cosf) has a bug in the Rust transpilation. The reduction step near multiples of pi/2 is critical for precision.

## What Needs to Change
1. Compare __rem_pio2f / __rem_pio2f_internal in Rust vs C — check constants, intermediate precision, and rounding
2. Compare __sinf / __cosf polynomial kernels — check coefficients and evaluation order
3. Fix the Rust implementation to match C bitwise

## Success Criteria
- `sinf(0x1.921fb6p+1)` returns `-0x1.777a5cp-24` (bitwise match)
- `tanf(0x1.921fb6p+1)` returns `0x1.777a5cp-24` (bitwise match)
- `cexpf(0x0p+0+0x1.921fb6p+1i)` returns `-0x1p+0+-0x1.777a5cp-24i` (bitwise match)
