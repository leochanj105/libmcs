# Goal 2: Fix acosh — uses Rust std math instead of transpiled functions

## Function
`acosh` (implemented as `acoshd`)

## Source Files
- **C source**: `/home/leochanj/Desktop/libmcs/libm/mathd/acoshd.c`
- **Rust source**: `/home/leochanj/Desktop/libmcs/newexp/rust-s4/src/mathd.rs:1385`

## Problem
The Rust `acoshd` implementation calls Rust standard library math methods (`.ln()`, `.sqrt()`, `.ln_1p()`) instead of the transpiled libmcs functions (`logd()`, `sqrtd()`, `log1pd()`). This produces different bit patterns because the std implementations use different algorithms.

Specific lines with wrong calls (in `acoshd`):
- Line 1403: `x.ln()` should be `logd(x)`
- Line 1409: `(t - ONE).sqrt()` should be `sqrtd(t - ONE)`
- Line 1409: `(...).ln()` should be `logd(...)`
- Line 1412: `(...).ln_1p()` should be `log1pd(...)`

## Failing Tests
- `acosh(0x1p+1)`: C returns `0x1.5124271980434p+0`, Rust returns `0x1.62e42fefa39efp+0`

## What Needs to Change
In `/home/leochanj/Desktop/libmcs/newexp/rust-s4/src/mathd.rs`, function `acoshd`:
1. Replace `.ln()` calls with `logd()`
2. Replace `.sqrt()` calls with `sqrtd()`
3. Replace `.ln_1p()` calls with `log1pd()`

## Success Criteria
- `acosh(0x1p+1)` returns `0x1.5124271980434p+0` (bitwise match with C)
- All other acosh test cases continue to pass
