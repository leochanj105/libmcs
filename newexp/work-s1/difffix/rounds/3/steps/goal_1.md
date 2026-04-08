# Goal 1: Fix cproj (cprojd) — copysign argument order

## Function
`cproj` (implemented as `cprojd`)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/complexd/cprojd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s1/src/complexd.rs` (line 126)

## Failure Type
MISMATCH — wrong output

## Observed Behavior
- Input: `inf+0x1p+0i`
- C output: `inf+0x0p+0i` (imaginary part becomes +0.0)
- Rust output: `inf+0x1p+0i` (imaginary part stays 1.0)

## Root Cause
The `copysign` arguments are reversed in the Rust code.

C code: `copysign(0.0, cimag(z))` — returns 0.0 with the sign of `z.im`.
Rust code: `z.im.copysign(0.0)` — returns `z.im` with the sign of 0.0 (i.e., `|z.im|`).

In Rust, `a.copysign(b)` returns the magnitude of `a` with the sign of `b`. So `z.im.copysign(0.0)` keeps the magnitude of `z.im`, which is wrong.

## Fix
Change line 130 in `complexd.rs`:
```rust
// FROM:
im: z.im.copysign(0.0),
// TO:
im: 0.0_f64.copysign(z.im),
```

## Success Criteria
- `cproj inf+0x1p+0i` returns `inf+0x0p+0i` (bitwise match with C)
- All other cproj test cases continue to pass
