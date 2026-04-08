# Goal 2: Fix tanf

## Function
`tanf`

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathf/tanf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s1/src/mathf.rs` (line 3082, `pub fn tanf`)

## Problem: MISMATCH
Input: `0x1.921fb6p+1` (float approximation of pi)
- C output:    `tanf(0x1.921fb6p+1) = 0x1.777a5cp-24`
- Rust output: `tanf(0x1.921fb6p+1) = 0x1.6bff7ap-16`

Same magnitude error as sinf — off by ~8 bits. The `tanf` function shares argument reduction logic with `sinf`. The Rust range reduction near pi produces an insufficiently precise reduced argument.

## Related Failures
Shares root cause with `sinf` (goal 1) and `cexpf` (goal 3). Fixing sinf's argument reduction will likely fix this too.

## What Needs to Change
Compare the Rust `tanf` implementation against the C version, focusing on:
1. The pi constants and range reduction logic
2. Whether tanf calls sinf/cosf internally or has its own reduction
3. Any shared kernel functions used for argument reduction

## Success Criteria
`tanf(0x1.921fb6p+1)` must return exactly `0x1.777a5cp-24` (bitwise match with C).
