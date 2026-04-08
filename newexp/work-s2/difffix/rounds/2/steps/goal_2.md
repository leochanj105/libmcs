# Goal 2: Fix cproj imaginary part for infinite inputs

## Function
`cproj` (delegates to `cprojd`)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/complexd/cprojd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s2/src/complexd.rs` (line ~122)

## Problem
**Wrong output.** `cproj(inf+1i)` should project to `inf+0i` but Rust returns `inf+1i`. When either component is infinite, the C standard says cproj returns `INFINITY + copysign(0.0, cimag(z)) * I` — the imaginary part must be ±0, not the original value.

## What Needs to Change
The Rust `cprojd` function must zero the imaginary part (with correct sign) when the input has an infinite real or imaginary component, matching the C implementation.

## Success Criteria
- `cproj(inf+0x1p+0i)` returns `inf+0x0p+0i` (bitwise match with C)
