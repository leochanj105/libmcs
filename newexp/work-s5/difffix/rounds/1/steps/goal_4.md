# Goal 4: Fix cproj and cprojf — wrong handling of infinite inputs

## Functions
`cproj` (double), `cprojf` (float)

## Source Files
- C source (cproj): `/home/leochanj/Desktop/libmcs/libm/complexd/cprojd.c`
- C source (cprojf): `/home/leochanj/Desktop/libmcs/libm/complexf/cprojf.c`
- Rust source (cproj): `/home/leochanj/Desktop/libmcs/newexp/rust-s5/src/complexd.rs` (fn `cprojd` at line 122)
- Rust source (cprojf): `/home/leochanj/Desktop/libmcs/newexp/rust-s5/src/complexf.rs` (fn `cprojf` at line 120)

## Problem
MISMATCH — when either component is infinite, cproj/cprojf should return (inf, +0.0) or (inf, -0.0) with the sign of the imaginary part being copysign(0, imag). Rust does not correctly zero out the imaginary part:
- `cproj inf+1i`: C=`inf+0x0p+0i`, Rust=`inf+0x1p+0i` (imaginary not zeroed)
- `cproj inf-1i`: C=`inf+-0x0p+0i`, Rust=`inf+0x1p+0i` (imaginary not zeroed, sign wrong)
- `cproj 1+infi`: C=`inf+0x0p+0i`, Rust=`inf+infi` (imaginary not zeroed)
- `cprojf inff+1i`: C=`inf+0x0p+0i`, Rust=`inf+0x1p+0i`
- `cprojf inff-1i`: C=`inf+-0x0p+0i`, Rust=`inf+0x1p+0i`

## What Needs to Change
The Rust `cprojd` and `cprojf` functions must set the imaginary part to `copysign(0.0, imag(z))` when either real or imaginary component is infinite, matching the C implementation.

## Success Criteria
- All 3 `cproj` test cases match C output exactly
- All 2 `cprojf` test cases match C output exactly
