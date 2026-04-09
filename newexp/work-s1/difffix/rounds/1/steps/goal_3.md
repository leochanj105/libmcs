# Goal 3: Fix cproj / cprojf — infinity projection

## Functions
- cproj, cprojf

## Source Files
- C: /home/leochanj/Desktop/libmcs/libm/complexd/cprojd.c, /home/leochanj/Desktop/libmcs/libm/complexf/cprojf.c
- Rust: /home/leochanj/Desktop/libmcs/newexp/rust-s1/src/complexd.rs, /home/leochanj/Desktop/libmcs/newexp/rust-s1/src/complexf.rs

## Problem
cproj(inf + 1.0i) should return inf + 0.0i, but Rust returns inf + 1.0i.

Per C11 7.3.9.5: if either component is infinite, cproj returns INFINITY + copysign(0.0, cimag(z))i. The Rust implementation is not zeroing the imaginary part when the real part is infinite.

## What Needs to Change
1. In the Rust cproj implementation, add/fix the check: if real or imaginary part is infinite, return (INFINITY, copysign(0.0, imag))
2. Same fix for cprojf

## Success Criteria
- `cproj(inf+0x1p+0i)` returns `inf+0x0p+0i` (bitwise match)
- `cprojf(inf+0x1p+0i)` returns `inf+0x0p+0i` (bitwise match)
