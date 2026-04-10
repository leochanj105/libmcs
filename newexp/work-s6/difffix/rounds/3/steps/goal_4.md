# Goal 4: Fix modf — modf(nan) returns 0 instead of nan

## Function
`modf` (calls `mathd::modfd`)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/modfd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s6/src/mathd.rs` (`modfd` at line 3422)

## Problem
MISMATCH — 1 test failure.

```
C:    modf nan = nan
Rust: modf nan = 0x0p+0
```

The C `modf` falls through its big-exponent branch when given a NaN input
because the high-word check `j0 >= 52` is true for NaN, and the function
returns `x` unchanged (NaN) along with storing NaN into `*iptr`. The Rust
version is short-circuiting NaN to `0.0` instead, possibly through an
early `if x.is_nan()` branch that returns the wrong value, or because its
`j0 >= 52` branch zeros out the fractional part for all large exponents
without preserving NaN payload.

## What Needs to Change
Inspect Rust `modfd` for any explicit NaN handling. Either:
- Remove an incorrect `is_nan` early return, OR
- Make the `j0 >= 52` branch return `x` (preserving NaN bits) instead of
  zero when the exponent field indicates NaN/Inf.

The C reference simply does: `if (j0 >= 52) { *iptr = x; if (j0 == 0x400 && ((i0 & 0xfffff) | i1) != 0) return x; ... return x*zero; }` — note the explicit NaN test that returns `x` (the NaN). Port that logic.

## Success Criteria
- `modf(nan, &iptr)` returns `nan` and sets `iptr` to `nan`.
- All 1 modf mismatch resolves to bitwise-exact match with C output.
- No regressions on finite or infinite inputs.
