# Compact Divergences — Round 1

Generated: 2026-04-08

## RUNTIME: ctanf timeout (CRITICAL BLOCKER)

Rust binary hung at `ctanf 0.5-50i` — likely infinite loop/recursion.
This blocks ~1000+ tests that follow ctanf in test execution order.
All MISSING functions below may be caused by this hang.

## MISMATCHES (39 tests, 16 functions)

| # | Function | Type | Failing inputs | What's wrong |
|---|----------|------|----------------|-------------|
| 1 | __fpclassifyf | mismatch | 0, inf, nan, -0, -inf, snan | Wrong classification constants (e.g. C returns 2 for zero, Rust returns 0) |
| 2 | acosh | mismatch | 2.0, 1+epsilon | Wrong computation (e.g. acosh(2)=1.317 in C, 1.443 in Rust) |
| 3 | ctanf | mismatch | pi/2+0.001i | Wrong real part (C: 0x1.353d4p-4, Rust: -0x1.575216p+3) |
| 4 | exp2 | mismatch | 10 | exp2(10) should be 1024, Rust gives ~3494 |
| 5 | fmod | mismatch | 1e-320 % 5e-324 | Subnormal remainder wrong |
| 6 | ilogb | mismatch | 0, 5e-324, subnormals | Zero returns -2147483647 (C) vs -2147483648 (Rust); subnormal exponent off by 1 |
| 7 | ilogbf | mismatch | 0 | Zero returns -2147483647 (C) vs -2147483648 (Rust) |
| 8 | log1pf | mismatch | -2, -1, -0.5, 0.3, 0.5, 1.0 | Completely wrong — appears to not use log1p algorithm (e.g. log1pf(-1) should be -inf, gives -2) |
| 9 | logb | mismatch | 5e-324, -5e-324, D_SUBNORM | Subnormal exponent: C=-1074, Rust=-1075 |
| 10 | modf | mismatch | nan | modf(nan) fractional should be nan, Rust gives 0 |
| 11 | pow | mismatch | 2^10, (-2)^3, 0.5^(-2), others | Integer exponent cases very wrong (e.g. 2^10=1024 in C, ~3494 in Rust) |
| 12 | remainder | mismatch | 1e-300 % 1e-316 | Subnormal remainder wrong |
| 13 | remquo | mismatch | 1e-300 % 1e-316 | Subnormal remainder wrong, quotient 3 vs 0 |
| 14 | rintf | mismatch | 1.75 | rintf(1.75)=2 in C, 1 in Rust (wrong rounding mode) |
| 15 | sinf | mismatch | pi (0x1.91eb86p+1) | Small output difference — likely __rem_pio2f reduction error |
| 16 | tanf | mismatch | +/- pi (0x1.91eb86p+1) | Small output difference — same __rem_pio2f issue as sinf |

## MISSING (1253 tests, ~1036 function/input combos)

Most missing functions are likely blocked by ctanf timeout. Key categories:

- **Internal helpers**: __ccoshsinh(f), __lgamma(f), __redupif, __rem_pio2(f), __tan(f) — may not be exposed in Rust test bridge
- **Standard math (double)**: atan2, ceil, cos, erf, erfc, exp, expm1, floor, fmax, fmin, fmod, frexp, hypot, ilogb, j0, j1, jn, lgamma, log, log10, log1p, log2, modf, nextafter, pow, remainder, remquo, round, scalbn, sin, sqrt, tan, tgamma, trunc, y0, y1, yn
- **Standard math (float)**: atan2f, ceilf, cosf, erfcf, erff, expm1f, floorf, fmaxf, fminf, fmodf, frexpf, hypotf, ilogbf, lgammaf, llrintf, llroundf, log10f, log1pf, log2f, logf, lrintf, lroundf, modff, nextafterf, powf, remainderf, remquof, rintf, roundf, scalbnf, sinf, sqrtf, tanf, tgammaf, truncf
- **Complex**: ccos(f), csin(f), ctan, ctanf, ctans(f)

## PRIORITY ORDER

1. Fix ctanf timeout — unblocks ~1000 tests
2. Fix __fpclassifyf — wrong constants affect classification everywhere
3. Fix log1pf — completely broken algorithm
4. Fix exp2/pow — likely same root cause (exp2 used by pow)
5. Fix ilogb/ilogbf/logb — subnormal/zero constant issues
6. Fix fmod/remainder/remquo — subnormal handling
7. Fix modf, rintf, sinf/tanf — individual fixes
8. Fix acosh — wrong computation
9. Verify missing functions after ctanf fix
