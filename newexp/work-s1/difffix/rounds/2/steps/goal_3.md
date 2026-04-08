# Goal 3: Fix cexpf

## Function
`cexpf`

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/complexf/cexpf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s1/src/complexf.rs` (line 136, `pub fn cexpf`)

## Problem: MISMATCH
Input: `0x0p+0 + 0x1.921fb6p+1i` (i*pi approx)
- C output:    `cexpf(0x0p+0+0x1.921fb6p+1i) = -0x1p+0 + -0x1.777a5cp-24i`
- Rust output: `cexpf(0x0p+0+0x1.921fb6p+1i) = -0x1p+0 + -0x1.6bff7ap-16i`

The real part is correct (-1), but the imaginary part (which is sin(pi_approx)) has the same error as sinf. `cexpf(iy) = cos(y) + i*sin(y)`, so the imaginary part is `sinf(0x1.921fb6p+1)`.

## Related Failures
Depends on `sinf` (goal 1). If sinf is fixed, cexpf should produce correct output automatically — unless cexpf has its own inline sin computation.

## What Needs to Change
1. Check if cexpf calls sinf/cosf or has inline trig computation
2. If it calls sinf, fixing sinf (goal 1) will fix this
3. If it has inline trig, apply the same pi-constant / range-reduction fix

## Success Criteria
`cexpf(0x0p+0+0x1.921fb6p+1i)` must return exactly `-0x1p+0 + -0x1.777a5cp-24i` (bitwise match with C).
