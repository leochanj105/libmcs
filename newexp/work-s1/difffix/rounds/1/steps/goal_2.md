# Goal 2: Fix binary crash/exit after test_exp() — 153 functions blocked

## Functions Affected
All 153 functions that execute after `exp` in the test suite are missing from Rust output:

**Double-precision (47 functions):**
exp2, expm1, cbrt, ceil, copysign, erf, erfc, fabs, fdim, floor, fma, fmax, fmin, fmod, frexp, hypot, ilogb, j0, j1, jn, ldexp, lgamma, llrint, llround, log, log10, log1p, log2, logb, lrint, lround, modf, nearbyint, nextafter, pow, remainder, remquo, rint, round, scalbln, scalbn, sqrt, tgamma, trunc, y0, y1, yn

**Float-precision (55 functions):**
acosf, acoshf, asinf, asinhf, atan2f, atanf, atanhf, cbrtf, ceilf, copysignf, cosf, coshf, erfcf, erff, exp2f, expf, expm1f, fabsf, fdimf, floorf, fmaf, fmaxf, fminf, fmodf, frexpf, hypotf, ilogbf, ldexpf, lgammaf, llrintf, llroundf, log10f, log1pf, log2f, logbf, logf, lrintf, lroundf, modff, nearbyintf, nextafterf, powf, remainderf, remquof, rintf, roundf, scalblnf, scalbnf, sinf, sinhf, sqrtf, tanf, tanhf, tgammaf, truncf

**Complex double (22 functions):**
cabs, cacos, cacosh, casinh, carg, casin, catan, catanh, ccos, ccosh, cexp, cimag, clog, conj, cpow, cproj, creal, csin, csinh, csqrt, ctan, ctanh

**Complex float (22 functions):**
cabsf, cacosf, cacoshf, casinhf, cargf, casinf, catanf, catanhf, ccosf, ccoshf, cexpf, cimagf, clogf, conjf, cpowf, cprojf, crealf, csinf, csinhf, csqrtf, ctanf, ctanhf

**Internal functions (7):**
__ctans, __ctansf, __sin_pi, __sin_pif, __tan, __tanf, rem_pio2_internal, rem_pio2f_internal

## Source Files
- **C source**: various (see function location map)
- **Rust source**: `/home/leochanj/Desktop/libmcs/newexp/rust-s1/src/mathd.rs`, `mathf.rs`, `complexd.rs`, `complexf.rs`
- **Rust lib exports**: `/home/leochanj/Desktop/libmcs/newexp/rust-s1/src/lib.rs`
- **Test suite**: `/home/leochanj/Desktop/libmcs/newexp/work-s1/diffgen/difftest_suite.c`

## Problem
The Rust-linked test binary produces output for 14 functions (acos through exp), then stops silently — no output, no stderr, no crash message. The next function in execution order is `test_exp2()` at line 1981 of `difftest_suite.c`.

The Rust `exp2d` implementation (mathd.rs:2119) delegates to `(2.0f64).powf(x)`, which uses Rust's standard library `powf`. This calls the C `pow` symbol, which is also exported by the Rust library as `mathd::powd()`. This chain may cause infinite recursion, a stack overflow, or a silent abort.

## What Needs to Change
1. **Investigate**: Build and run the Rust-linked test binary to confirm the crash location. Check if `exp2d` using `(2.0f64).powf(x)` causes infinite recursion through the re-exported `pow` symbol.
2. **Fix `exp2d`**: Replace the `powf` delegation with a proper exp2 implementation matching the C `exp2d.c` logic, or at minimum ensure it doesn't cause a circular call through the `pow` export.
3. **Verify**: After fixing, all 153 previously-missing functions should produce output. Any new mismatches will be addressed in subsequent goals.

## Success Criteria
- The Rust-linked test binary runs to completion without crashing
- All 153 previously-missing functions produce output in the Rust test
- `exp2` test cases produce bitwise-exact output matching C
