# Goal 2: Fix cprojf — copysign argument order

## Function
`cprojf`

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/complexf/cprojf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s1/src/complexf.rs` (line 124)

## Failure Type
MISMATCH — wrong output

## Observed Behavior
- Input: `inf+0x1p+0i`
- C output: `inf+0x0p+0i` (imaginary part becomes +0.0)
- Rust output: `inf+0x1p+0i` (imaginary part stays 1.0)

## Root Cause
Same bug as cprojd. The `copysign` arguments are reversed.

C code: `copysignf(0.0f, cimagf(z))` — returns 0.0 with the sign of `z.im`.
Rust code: `z.im.copysign(0.0_f32)` — returns `z.im` with the sign of 0.0 (i.e., `|z.im|`).

## Fix
Change line 128 in `complexf.rs`:
```rust
// FROM:
im: z.im.copysign(0.0_f32),
// TO:
im: 0.0_f32.copysign(z.im),
```

## Success Criteria
- `cprojf inf+0x1p+0i` returns `inf+0x0p+0i` (bitwise match with C)
- All other cprojf test cases continue to pass
