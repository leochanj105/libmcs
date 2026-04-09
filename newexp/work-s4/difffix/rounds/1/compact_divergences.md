# Compact Divergences — Round 1

## Summary
5 test mismatches across 4 functions. 436/441 tests pass.

## Divergences

### 1. __fpclassifyf (2 mismatches)
- **Type**: Wrong output — incorrect FP classification constants
- **C source**: `/home/leochanj/Desktop/libmcs/libm/mathf/internal/fpclassifyf.c`
- **Rust source**: `/home/leochanj/Desktop/libmcs/newexp/rust-s4/src/mathf.rs:3161`
- **Details**: Rust uses wrong values for FP_ZERO, FP_INFINITE, FP_NAN, FP_SUBNORMAL.
  System values: FP_ZERO=2, FP_INFINITE=1, FP_NAN=0, FP_NORMAL=4, FP_SUBNORMAL=3.
  Rust has: FP_ZERO=0, FP_INFINITE=3, FP_NAN=1, FP_NORMAL=4, FP_SUBNORMAL=2.
- **Failing inputs**:
  - `__fpclassifyf(0x0p+0)`: C=2(FP_ZERO), Rust=0
  - `__fpclassifyf(inf)`: C=1(FP_INFINITE), Rust=3

### 2. acosh (1 mismatch)
- **Type**: Wrong output — uses Rust std math instead of transpiled functions
- **C source**: `/home/leochanj/Desktop/libmcs/libm/mathd/acoshd.c`
- **Rust source**: `/home/leochanj/Desktop/libmcs/newexp/rust-s4/src/mathd.rs:1385`
- **Details**: Rust calls `.ln()`, `.sqrt()`, `.ln_1p()` (std library) instead of `logd()`, `sqrtd()`, `log1pd()` (transpiled libmcs). This produces different bit patterns.
- **Failing input**:
  - `acosh(0x1p+1)`: C=0x1.5124271980434p+0, Rust=0x1.62e42fefa39efp+0

### 3. exp2 (1 mismatch)
- **Type**: Wrong output — delegates to Rust std instead of transpiled pow
- **C source**: `/home/leochanj/Desktop/libmcs/libm/mathd/exp2d.c`
- **Rust source**: `/home/leochanj/Desktop/libmcs/newexp/rust-s4/src/mathd.rs:2119`
- **Details**: C `exp2` calls `pow(2.0, x)` (libmcs). Rust `exp2d` calls `(2.0f64).powf(x)` (std). Must call `powd(2.0, x)`.
- **Failing input**:
  - `exp2(0x1.4p+3)`: C=0x1p+10, Rust=0x1.b2d809254afbcp+11

### 4. pow (1 mismatch)
- **Type**: Wrong output — powd implementation bug
- **C source**: `/home/leochanj/Desktop/libmcs/libm/mathd/powd.c`
- **Rust source**: `/home/leochanj/Desktop/libmcs/newexp/rust-s4/src/mathd.rs:3504`
- **Details**: `powd(2.0, 10.0)` returns 0x1.b2d809254afbcp+11 (~3524) instead of 0x1p+10 (1024). The implementation has a computational bug.
- **Failing input**:
  - `pow(0x1p+1, 0x1.4p+3)`: C=0x1p+10, Rust=0x1.b2d809254afbcp+11

## Dependencies
- exp2 fix depends on pow fix (exp2 should call powd, and powd must be correct)
- acosh is independent
- __fpclassifyf is independent
