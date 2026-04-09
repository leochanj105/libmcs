# Goal 5: Fix exp2d to call powd instead of std powf

## Function
exp2 (exp2d)

## Source files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/exp2d.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s2/src/mathd.rs` (lines 2119-2121)

## Problem
The C implementation of exp2 is simply `pow(2.0, x)`, calling the libmcs pow. The Rust
implementation uses `(2.0f64).powf(x)` which calls the Rust standard library's powf, not the
transpiled powd. This produces different results because the two implementations differ.

C code (exp2d.c:65):
```c
return pow(2.0, x);
```

Rust code (mathd.rs:2120):
```rust
(2.0f64).powf(x)
```

## Failing test
- `exp2 0x1.4p+3` → C: 0x1p+10, Rust: 0x1.b2d809254afbcp+11

## What needs to change
Change `mathd.rs:2120` to call the transpiled `powd` function:
```rust
pub fn exp2d(x: f64) -> f64 {
    powd(2.0, x)
}
```

Note: This goal depends on Goal 8 (fixing powd) — once powd is correct, exp2d will also be correct.

## Success Criteria
`exp2(10.0)` returns `0x1p+10` (1024.0), bitwise matching the C output.
