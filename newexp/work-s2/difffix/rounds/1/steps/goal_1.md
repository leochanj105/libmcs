# Goal 1: Fix fenv stub functions

## Functions
feclearexcept, feraiseexcept, fegetround, fesetround, fetestexcept

## Source files
- C source: `/home/leochanj/Desktop/libmcs/libm/include/fenv.h` (fenv API)
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s2/src/lib.rs` (lines 17-27)

## Problem
All fenv functions are stubbed to unconditionally return -1 (indicating error). The C library
returns 0 for valid no-op calls like `feclearexcept(0)`, `fesetround(0)`, `fegetround()`, etc.

## Failing tests
- `feclearexcept(0)` → C: 0, Rust: -1
- `feraiseexcept(0)` → C: 0, Rust: -1
- `fegetround()` → C: 0, Rust: -1
- `fesetround(0)` → C: 0, Rust: -1
- `fetestexcept(0)` → C: 0, Rust: -1

## What needs to change
Implement minimal fenv semantics matching the C library behavior:
- `feclearexcept(excepts)`: return 0 (success) — no FPU exception state to clear in Rust
- `feraiseexcept(excepts)`: return 0 (success) — no-op is acceptable
- `fegetround()`: return 0 (FE_TONEAREST, the default rounding mode)
- `fesetround(rdir)`: return 0 if rdir == 0 (FE_TONEAREST), -1 otherwise
- `fetestexcept(excepts)`: return 0 (no exceptions set)

## Success Criteria
All 5 fenv tests produce output matching the C library:
- `feclearexcept(0) = 0`
- `feraiseexcept(0) = 0`
- `fegetround() = 0`
- `fesetround(0) = 0`
- `fetestexcept(0) = 0`
