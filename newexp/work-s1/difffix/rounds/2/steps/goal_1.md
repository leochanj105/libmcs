# Goal 1: Fix sinf

## Function
`sinf`

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathf/sinf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s1/src/mathf.rs` (line 2968, `pub fn sinf`)

## Problem: MISMATCH
Input: `0x1.921fb6p+1` (float approximation of pi)
- C output:    `sinf(0x1.921fb6p+1) = -0x1.777a5cp-24`
- Rust output: `sinf(0x1.921fb6p+1) = -0x1.6bff7ap-16`

The Rust result is off by ~8 orders of magnitude (2^-16 vs 2^-24). This indicates a precision error in the argument reduction step near pi. The value near pi requires careful cancellation; the Rust implementation likely has a flawed range reduction or uses insufficiently precise pi constants.

## Related Failures
This is likely the root cause for `tanf` (goal 2) and `cexpf` (goal 3) failures, since both depend on sinf-like computation near pi.

## What Needs to Change
Compare the Rust `sinf` implementation against the C version, focusing on:
1. The pi/2 constants used for argument reduction
2. The range reduction logic for inputs near multiples of pi
3. Any intermediate precision differences (e.g., using f32 where C uses double intermediates)

## Success Criteria
`sinf(0x1.921fb6p+1)` must return exactly `-0x1.777a5cp-24` (bitwise match with C).
