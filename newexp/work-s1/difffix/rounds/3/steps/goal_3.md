# Goal 3: Fix log1pf — flt_uword_is_finite called with signed hx as u32

## Function
`log1pf`

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathf/log1pf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s1/src/mathf.rs` (line 2099)

## Failure Type
MISMATCH — wrong output

## Observed Behavior
- Input: `-0x1p+0` (i.e., -1.0)
- C output: `-inf` (correctly raises divide-by-zero)
- Rust output: `-0x1p+1` (i.e., -2.0, from `x + x`)

## Root Cause
At line 2111 in `mathf.rs`:
```rust
if !flt_uword_is_finite(hx as u32) { return x + x; }
```

`hx` is a signed i32. For x = -1.0, `hx = 0xbf800000` (negative as i32). Casting to u32 gives `0xbf800000 = 3212836864`, which is greater than `0x7f800000`, so `flt_uword_is_finite` returns false. Rust takes the early NaN/+Inf return path (`x + x = -2.0`) incorrectly.

In the C code, `FLT_UWORD_IS_FINITE(hx)` is `((hx) < 0x7f800000L)`. Since `hx` is a signed `int32_t` and negative, the signed comparison `negative < positive` is always true, so C correctly considers all negative-sign floats as finite and proceeds to the `-1.0` special case handler.

## Fix
Change line 2111 in `mathf.rs` to use `ax` (the absolute value, always non-negative) instead of `hx`:
```rust
// FROM:
if !flt_uword_is_finite(hx as u32) { return x + x; }
// TO:
if !flt_uword_is_finite(ax as u32) { return x + x; }
```

This matches the C semantics: `ax = hx & 0x7fffffff` strips the sign bit, so it is always a valid unsigned word for the finite/NaN checks. The `FLT_UWORD_IS_FINITE` macro name itself implies it expects an unsigned word (absolute value).

## Success Criteria
- `log1pf -0x1p+0` returns `-inf` (bitwise match with C)
- All other log1pf test cases continue to pass
