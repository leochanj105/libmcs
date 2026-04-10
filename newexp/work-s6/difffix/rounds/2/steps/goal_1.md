# Goal 1: Fix cprojf — imaginary part not zeroed for infinite inputs

## Function
`cprojf`

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/complexf/cprojf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s6/src/complexf.rs` (line ~120)

## Problem
MISMATCH — 4 test failures.

When the input has an infinite real part, `cprojf` should return `inf + 0i` (with the sign of the imaginary part being copysign(0, imag(z))). The Rust version preserves the original imaginary part (`0x1p+0i`) instead of replacing it with `+/-0`.

Example:
- C:    `cprojf inff+1i = inf+0x0p+0i`
- Rust: `cprojf inff+1i = inf+0x1p+0i`

## What Needs to Change
The Rust `cprojf` must set the imaginary part to `copysign(0.0, imag(z))` when the input is infinite, matching the C implementation.

## Success Criteria
- `cprojf(inf+1i)` returns `inf+0i`
- `cprojf(inf-1i)` returns `inf-0i`
- All 4 cprojf mismatches resolve to bitwise-exact match with C output.
