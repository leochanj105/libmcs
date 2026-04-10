# Goal 5: Fix `cproj` infinity projection

## Function
`cproj` (complex double projection onto Riemann sphere)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/complexd/cprojd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s6/src/complexd.rs` (around line 122, `cprojd`)

## Problem
MISMATCH — 5 test failures. When either component is infinite, `cproj` should return `inf + 0i` (with the sign of the original imaginary part on the zero). The Rust version fails to zero out the imaginary part.

```
C:    cproj inf+1i   = inf+0x0p+0i
Rust: cproj inf+1i   = inf+0x1p+0i       (imag not zeroed)

C:    cproj inf-1i   = inf+-0x0p+0i
Rust: cproj inf-1i   = inf+0x1p+0i       (imag not zeroed, sign wrong)

C:    cproj 1+infi   = inf+0x0p+0i
Rust: cproj 1+infi   = inf+infi          (imag not zeroed)
```

## What Needs to Change
The Rust `cprojd` must detect when either real or imaginary part is infinite and return `INFINITY + copysign(0.0, imag)` per C99/IEEE 754. The current implementation appears to pass through the input unchanged when infinity is present.

## Success Criteria
- `cproj(inf+1i)` = `inf+0x0p+0i` (bitwise match)
- `cproj(inf-1i)` = `inf+-0x0p+0i` (bitwise match, signed zero)
- `cproj(1+infi)` = `inf+0x0p+0i` (bitwise match)
- All 5 failing tests pass with bitwise-exact match
