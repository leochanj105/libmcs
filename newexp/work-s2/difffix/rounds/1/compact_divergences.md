# Compact Divergences — Round 1

## Summary
- Tests passed: 53 / 458
- Tests failed: 405 (1 mismatch + 404 missing)
- Rust output: 57 lines vs C output: 502 lines

## Root Causes

### RC1: Binary crash at exp2d (CRITICAL)
The Rust test binary crashes when `exp2d` is called, killing all subsequent tests.
`exp2d` is implemented as `(2.0f64).powf(x)` which calls Rust's `f64::powf` →
system `pow()` → overridden `#[no_mangle] pow` → `powd()` → likely infinite
recursion / stack overflow.

**Impact:** 404 missing tests across 196 functions. Everything after `exp` in the
test order is lost.

### RC2: acosh mismatch
`acosh(0x1p+1)`: C returns `0x1.5124271980434p+0`, Rust returns `0x1.62e42fefa39efp+0`.
Rust value is `ln(4)` not `arccosh(2) = ln(2+sqrt(3))`. Bug in `acoshd`.

### RC3: fenv stubs return -1
feclearexcept(0), feraiseexcept(0), fegetround(), fesetround(0), fetestexcept(0)
all return 0 in C but -1 in Rust. Trivial no-op calls should succeed.

### RC4: Internal functions not exported
__cos, __sin, __rem_pio2, __cosf, __sinf, __rem_pio2f, __lgamma, __lgammaf,
__redupi, __redupif, __fpclassifyd, __signbitd, __fpclassifyf, __signbitf —
these internal functions are tested directly by the test harness but not exported
from the Rust binary.

### RC5: Bridge functions not exported
bridge___tan, bridge___tanf, bridge___sin_pi, bridge___sin_pif,
bridge___rem_pio2_internal, bridge___rem_pio2f_internal,
bridge___ctans, bridge___ctansf — test bridge wrappers not implemented in Rust.

### RC6: __ccoshsinh / __ccoshsinhf not implemented
Explicitly listed as not implemented in the diff report.

## Test Order (from C output)
1. Double Trig (acos, asin, atan, atan2, cos, sin, tan) — PASSED
2. Double Hyperbolic (acosh, asinh, atanh, cosh, sinh, tanh) — acosh MISMATCH, rest PASSED
3. Double Exp/Log (exp, exp2, ...) — exp PASSED, **exp2 CRASH**, rest MISSING
4. Everything after — MISSING (power, erf, gamma, int, remainder, manipulation,
   max/min, bessel, ALL float, ALL complex, bridge, internal, fenv)
