# Goal 3: Fix log1pf signed/unsigned comparison bug (MISMATCH)

## Function
`log1pf` — log(1 + x) for float

## Source Files
- **C source**: `/home/leochanj/Desktop/libmcs/libm/mathf/log1pf.c` (lines 15–109)
- **Rust source**: `/home/leochanj/Desktop/libmcs/newexp/rust-s1/src/mathf.rs` (lines 2099–2174)

## Problem
MISMATCH — wrong output for input `-0x1p+0` (-1.0f).
- Expected (C): `-inf`
- Actual (Rust): `-0x1p+1` (-2.0)

The C code at line 33: `if (!FLT_UWORD_IS_FINITE(hx))` where `hx` is `int32_t`. The macro `FLT_UWORD_IS_FINITE(x)` expands to `((x) < 0x7f800000)`. Since `hx` is signed and negative for x = -1.0 (hx = 0xBF800000 = -1065353216), the signed comparison `hx < 0x7f800000` is true, so `FLT_UWORD_IS_FINITE` returns true, and the early-return branch is NOT taken.

The Rust code at line 2111: `if !flt_uword_is_finite(hx as u32)` casts `hx` (i32) to `u32` before passing to the function. For hx = -1065353216, `hx as u32 = 0xBF800000 = 3229614080`. Since `3229614080 >= 0x7f800000`, `flt_uword_is_finite` returns false, so `!false = true` and the function enters the early-return path, returning `x + x = -2.0`.

## What Needs to Change
On Rust line 2111, change:
```rust
if !flt_uword_is_finite(hx as u32) { return x + x; }
```
to either:
```rust
if (hx & 0x7fffffff) >= 0x7f800000_i32 { return x + x; }
```
or equivalently:
```rust
if !flt_uword_is_finite(ax as u32) { return x + x; }
```
using `ax` (which is `hx & 0x7fffffff`, the absolute value) instead of `hx`. This matches what the C code actually checks — whether the magnitude is non-finite — since all negative values are finite (the sign bit doesn't affect finiteness).

## Success Criteria
- `log1pf(-0x1p+0)` returns `-inf` (bitwise matching C output)
- All other log1pf tests continue to pass with bitwise-identical output
