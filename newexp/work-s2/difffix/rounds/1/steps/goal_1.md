# Goal 1: Fix exp2d crash (critical — unblocks 196 functions)

## Function
`exp2d` (double-precision exp2)

## C Source
/home/leochanj/Desktop/libmcs/libm/mathd/exp2d.c

## Rust Source
/home/leochanj/Desktop/libmcs/newexp/rust-s2/src/mathd.rs — `pub fn exp2d` (line ~2119)

## Problem
The Rust test binary crashes when `exp2d` is called, killing ALL subsequent tests
(404 missing tests across 196 functions). The current implementation is:

```rust
pub fn exp2d(x: f64) -> f64 {
    (2.0f64).powf(x)
}
```

`f64::powf(x)` calls the system `pow()` function, which is overridden by the Rust
binary's `#[no_mangle] pub extern "C" fn pow(...)` → `mathd::powd()`. This creates
infinite recursion (powd likely calls exp2 or powf internally) → stack overflow.

## What Needs to Change
Replace the stub `(2.0f64).powf(x)` with a proper algorithmic implementation of
exp2, ported from the C source at `/home/leochanj/Desktop/libmcs/libm/mathd/exp2d.c`.
The implementation must not call any standard library math functions that are
overridden by `#[no_mangle]` exports (pow, exp, log, etc.) — use the local
`mathd::` versions instead.

## Success Criteria
- `exp2(0x0p+0) = 0x1p+0`
- `exp2(0x1p+0) = 0x1p+1`
- `exp2(-0x1p+0) = 0x1p-1`
- `exp2(0x1.4p+3) = 0x1p+10`
- All values bitwise-exact with C output (%a hex float format)
- No crash — the test binary continues past exp2 to all subsequent tests
