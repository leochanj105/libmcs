# Goal 1: Fix `__cosf` kernel precision

## Function
`__cosf` (internal float cosine kernel)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathf/internal/trigf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s6/src/mathf.rs` (around line 479, `cosf_kern`)

## Problem
MISMATCH — 1 test failure. Last-bit precision error in the cosine kernel.

```
C:    __cosf 0x1p+0 0x0p+0 = 0x1.14a282p-1
Rust: __cosf 0x1p+0 0x0p+0 = 0x1.14a284p-1
```

The Rust kernel returns a value 1 ULP higher than the C reference.

## What Needs to Change
Compare the polynomial coefficients and arithmetic in the Rust `cosf_kern` against the C `__cosf`. Likely a coefficient is slightly off, or an intermediate computation uses a different rounding sequence.

## Success Criteria
- `__cosf(0x1p+0, 0x0p+0)` returns exactly `0x1.14a282p-1` (bitwise match with C)
- All other existing `__cosf` tests continue to pass
