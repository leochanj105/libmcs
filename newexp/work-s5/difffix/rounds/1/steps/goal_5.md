# Goal 5: Fix ctanf — wrong real part for near-pi/2 arguments

## Function
`ctanf`

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/complexf/ctanf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s5/src/complexf.rs` (fn `ctanf` at line 241)

## Problem
MISMATCH — `ctanf` produces wrong real parts:
- `ctanf pi/2+0i`: C=`-0x1.5d1496p+24+0x0p+0i`, Rust=`-0x1.52685p+32+0x0p+0i` (real part magnitude off by ~256x)
- `ctanf near-pi/2`: C=`0x1.8de6bcp+12+0x1.09a042p-8i`, Rust=`0x1.728826p+12+0x1.09a042p-8i` (real part wrong, imaginary matches)

The imaginary parts are correct in the second case, suggesting the real-part computation has an error in the tangent calculation or argument reduction.

## What Needs to Change
Compare the Rust `ctanf` implementation against the C source. Check:
- The `__ctansf` helper and `__redupif` functions used internally
- Polynomial coefficients for the tangent computation
- Argument reduction logic

## Success Criteria
- `ctanf pi/2+0i` returns `-0x1.5d1496p+24+0x0p+0i`
- `ctanf near-pi/2` returns `0x1.8de6bcp+12+0x1.09a042p-8i`
- All ctanf test cases match C output exactly
