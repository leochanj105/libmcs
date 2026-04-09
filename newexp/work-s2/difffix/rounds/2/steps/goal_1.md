# Goal 1: Fix `powd` (fixes both `pow` and `exp2`)

## Functions
- `pow` (double)
- `exp2` (double) — delegates to `pow(2.0, x)` in both C and Rust

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/powd.c`
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/exp2d.c` (just calls `pow(2.0, x)`)
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s2/src/mathd.rs` — `powd` at line 3504, `exp2d` at line 2119

## What's Wrong
**Wrong output.** `pow(2, 10)` returns `0x1.b2d809254afbcp+11` (~3494) instead of `0x1p+10` (1024). The error is large — not a rounding issue but a computational bug in the `powd` implementation.

Since `exp2d` calls `powd(2.0, x)` (same as the C implementation), the `exp2(10)` failure is the same root cause.

## Failing Tests
```
pow 0x1p+1 0x1.4p+3:   C = 0x1p+10,              Rust = 0x1.b2d809254afbcp+11
exp2 0x1.4p+3:          C = 0x1p+10,              Rust = 0x1.b2d809254afbcp+11
```

## What Needs to Change
Compare the Rust `powd` implementation (mathd.rs:3504) line-by-line against the C `pow` in `powd.c`. The bug is likely in:
- The exponent extraction / integer detection logic
- The main computation path (log2 decomposition, polynomial evaluation, or reconstruction)
- Possible sign/cast error in bit manipulation (`i32` vs `u32` mismatch)

## Success Criteria
- `pow(2, 10)` returns `0x1p+10` (bitwise exact match with C)
- `exp2(10)` returns `0x1p+10` (bitwise exact match with C)
- All other currently-passing pow/exp2 tests continue to pass
