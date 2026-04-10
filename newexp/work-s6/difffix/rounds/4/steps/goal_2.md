# Goal 2: Fix rem_pio2 — NaN sign bit on infinite input

## Function
`rem_pio2` (test bridge calls into Rust `mathd::rem_pio2`)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/internal/trigd.c` (`__rem_pio2`, line 450)
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s6/src/mathd.rs` (`rem_pio2` at line 291)

## Problem
MISMATCH — 1 test failure (carryover from Round 3 — was skipped).

```
C:    rem_pio2 inf: n=0 y0=nan  y1=nan
Rust: rem_pio2 inf: n=0 y0=-nan y1=-nan
```

In the C `__rem_pio2`, the inf/NaN branch (`trigd.c:544-553`) distinguishes:

```c
if (ix >= 0x7ff00000) {     /* x is inf or NaN */
    if (isnan(x)) {
        y[1] = x - x;       /* NaN input → propagate via x-x */
        y[0] = y[1];
    } else {
        y[1] = __raise_invalid();  /* Inf input → raise + return positive NaN */
        y[0] = y[1];
    }
    return 0;
}
```

`__raise_invalid()` returns a *positive* qNaN (the IEEE default NaN, sign bit 0).

The Rust version at `mathd.rs:371-378` collapses both cases into one:

```rust
if ix >= 0x7ff00000 {
    let nan = x - x;
    y[0] = nan;
    y[1] = nan;
    return 0;
}
```

For `x = +inf`, `inf - inf = NaN` with the sign bit *set* on x86_64
(producing `-nan`), which is why Rust prints `-nan`. C's `__raise_invalid()`
side-steps this by producing a fresh positive NaN.

## What Needs to Change
In `mathd.rs:371-378`, split the branch like the C source: distinguish NaN
input (use `x - x` to propagate) from infinite input (return a positive NaN
explicitly). For example:

```rust
if ix >= 0x7ff00000 {
    let nan = if x.is_nan() {
        x - x
    } else {
        f64::NAN          // or: f64::from_bits(0x7ff8_0000_0000_0000)
    };
    y[0] = nan;
    y[1] = nan;
    return 0;
}
```

`f64::NAN` in Rust is the canonical positive qNaN (`0x7ff8_0000_0000_0000`),
which matches C's `__raise_invalid()` output.

## Success Criteria
- `rem_pio2(+inf)` produces `y[0] = nan`, `y[1] = nan`, `n = 0` where the NaN
  has the positive sign bit (printed as `nan`, not `-nan`).
- `rem_pio2(NaN)` continues to propagate the NaN as before.
- The 1 rem_pio2 mismatch resolves to bitwise-exact match with C output.
- No regressions on finite-input rem_pio2 tests.
