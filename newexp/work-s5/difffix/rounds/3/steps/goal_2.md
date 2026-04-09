# Goal 2: Fix modfd NaN return value

## Function
`modfd` (double-precision `modf`)

## Source files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/modfd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s5/src/mathd.rs` (line 3422)

## Problem
**Wrong output** — Rust returns 0 instead of NaN for NaN input:

```
C:    modf nan = nan
Rust: modf nan = 0x0p+0
```

## Root cause
In the C code (lines 97-105), the `j0 > 51` branch handles both infinity and NaN. For NaN, it returns early via `return *iptr = x + x` (which is NaN). For non-NaN (infinity), it falls through to return ±0.

In the Rust code (lines 3442-3444):
```rust
} else if j0 > 51 {
    *iptr = if x.is_nan() { x + x } else { x };
    return f64::from_bits(sign_bits << 32);  // always returns ±0
}
```

The Rust code correctly sets `*iptr` to NaN for NaN input, but unconditionally returns `±0` as the fractional part. For NaN, the C code returns NaN as the fractional part — not ±0.

## What needs to change
In `mathd.rs` at line ~3442, restructure the `j0 > 51` branch to return NaN when the input is NaN:

```rust
} else if j0 > 51 {
    if x.is_nan() {
        *iptr = x + x;
        return *iptr;
    }
    *iptr = x;
    return f64::from_bits(sign_bits << 32);
}
```

## Success Criteria
- `modf(NaN)` returns `NaN` as the fractional part — matching C output
- `modf(±Inf)` continues to return `±0` as the fractional part
- All other modf tests continue to pass
