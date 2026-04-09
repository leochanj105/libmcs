# Goal 4: Fix cproj copysign argument order

## Function
cproj (cprojd)

## Source files
- C source: `/home/leochanj/Desktop/libmcs/libm/complexd/cprojd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s2/src/complexd.rs` (lines 122-131)

## Problem
The Rust code has reversed `copysign` arguments. When the input has an infinite component,
the imaginary part should be ±0 (zero with the sign of the original imaginary part).

Rust code (complexd.rs:126):
```rust
im: z.im.copysign(0.0),
```
Rust's `f64::copysign(self, sign)` returns the magnitude of `self` with the sign of `sign`.
So `z.im.copysign(0.0)` returns `|z.im|` with sign of `+0.0` = `|z.im|` ≈ 1.0. Wrong!

The correct code should be:
```rust
im: 0.0_f64.copysign(z.im),
```
This returns 0.0 with the sign of z.im, which matches the C `copysign(0.0, cimag(z))`.

## Failing test
- `cproj(inf+0x1p+0i)` → C: `inf+0x0p+0i`, Rust: `inf+0x1p+0i`

## What needs to change
In `complexd.rs:126`, swap the copysign receiver and argument:
```rust
// Before:
im: z.im.copysign(0.0),
// After:
im: 0.0_f64.copysign(z.im),
```

## Success Criteria
`cproj(inf+1.0i)` returns `inf+0.0i`, bitwise matching the C output.
