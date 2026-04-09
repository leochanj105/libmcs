# Goal 3: Fix exp2 — delegates to Rust std instead of transpiled powd

## Function
`exp2` (implemented as `exp2d`)

## Source Files
- **C source**: `/home/leochanj/Desktop/libmcs/libm/mathd/exp2d.c`
- **Rust source**: `/home/leochanj/Desktop/libmcs/newexp/rust-s4/src/mathd.rs:2119`

## Problem
The C `exp2` implementation is `return pow(2.0, x)`, which calls the libmcs `pow` function.
The Rust `exp2d` implementation is `(2.0f64).powf(x)`, which calls the Rust standard library `powf`.

This produces different results because std `powf` uses a different algorithm than the transpiled `powd`.

## Failing Tests
- `exp2(0x1.4p+3)`: C returns `0x1p+10` (1024.0), Rust returns `0x1.b2d809254afbcp+11`

## What Needs to Change
In `/home/leochanj/Desktop/libmcs/newexp/rust-s4/src/mathd.rs` at line 2119-2121, change:
```rust
pub fn exp2d(x: f64) -> f64 {
    (2.0f64).powf(x)
}
```
to:
```rust
pub fn exp2d(x: f64) -> f64 {
    powd(2.0, x)
}
```

**Note**: This fix depends on Goal 4 (powd must also be correct for this to produce correct results).

## Success Criteria
- `exp2(0x1.4p+3)` returns `0x1p+10` (bitwise match with C)
- All other exp2 test cases continue to pass
- Depends on Goal 4 being fixed first
