# Goal 4: Fix modf returning 0 instead of NaN for fractional part

## Function
- `modfd` (split double into integer and fractional parts)

## Source files
- C: `/home/leochanj/Desktop/libmcs/libm/mathd/modfd.c`
- Rust: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathd.rs` (line ~3422, `modfd`)

## What's wrong
| Input | C frac / C int | Rust frac / Rust int |
|-------|----------------|----------------------|
| modf(nan) | nan / nan | 0x0p+0 / nan |

The fractional part should be NaN but Rust returns +0.0. The integer part (*iptr) is correctly NaN.

## Root cause (confirmed)
The C code for the `j0 > 51` branch:
```c
if (_j0 > 51) {
    *iptr = x;
    if (isnan(x)) {
        return *iptr = x + x;   /* sets *iptr to NaN AND returns NaN */
    }
    INSERT_WORDS(x, _i0 & 0x80000000U, 0U);  /* return +-0 */
    return x;
}
```

The Rust code:
```rust
} else if j0 > 51 {
    *iptr = if x.is_nan() { x + x } else { x };
    return f64::from_bits(sign_bits << 32);   // ALWAYS returns signed zero!
}
```

The Rust translation is **structurally wrong**. It collapses the NaN branch into a single expression that only affects `*iptr`, but ALWAYS falls through to return signed zero. In C, the `if (isnan(x))` block has an early `return`, so NaN never reaches the signed-zero return.

## What needs to change
Restructure the `j0 > 51` branch to match C's control flow — early return for NaN:

```rust
} else if j0 > 51 {
    *iptr = x;
    if x.is_nan() {
        *iptr = x + x;
        return *iptr;
    }
    return f64::from_bits(sign_bits << 32);
}
```

This matches C exactly:
1. Set `*iptr = x`
2. If NaN: set `*iptr = x + x` (NaN) and return that NaN
3. Otherwise: return signed zero

## Success Criteria
- `modf(nan)` returns `(nan, int=nan)` matching C
- `modf(0)` still returns `(0, int=0)`
- `modf(inf)` still returns `(0, int=inf)`
- `modf(-inf)` still returns `(-0, int=-inf)`
- `modf(1.5)` still returns `(0.5, int=1.0)`
- All other existing modf tests continue to pass
