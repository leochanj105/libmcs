# Judger V2 — Rust Baseline Report

**Date:** 2026-04-09
**C library:** `build-x86_64-linux-gnu/bin/libm.a`
**Rust library:** `newexp/rust-baseline-judger/target/release/librust_baseline.a`
**Method:** Bitwise `%a` comparison, zero tolerance

## Summary

| Source | Tests | Divergences |
|--------|-------|-------------|
| glibc (auto-libm-test-in) | 14,888 | 703 |
| glibc (libm-test-*.inc) | 3,704 | 769 |
| **Total** | **18,592** | **1,472** |

Core-math worst-case tests not yet included.

## glibc (auto-libm-test-in) — 703 divergences

| Function | Divergences | Notes |
|----------|-------------|-------|
| tgammaf | 245 | |
| tgamma | 202 | |
| atan2f | 44 | |
| atan2 | 44 | |
| exp2 | 33 | All timeouts (infinite loop in Rust) |
| pow | 20 | |
| cargf | 10 | |
| carg | 10 | |
| cacoshf | 10 | |
| casinhf | 9 | |
| ctanf | 7 | |
| casinf | 6 | |
| cacosf | 6 | |
| sinf | 5 | |
| cosf | 5 | |
| casinh | 5 | |
| cacosh | 5 | |
| tanf | 4 | |
| cexpf | 4 | |
| ctanhf | 3 | |
| casin | 3 | |
| cacos | 3 | |
| ctanh | 2 | |
| ctan | 2 | |
| cpowf | 2 | |
| cpow | 2 | |
| cexp | 2 | |
| ccosf | 2 | |
| atanf | 2 | |
| atan | 2 | |
| tan | 1 | |
| sin | 1 | |
| cos | 1 | |
| ccos | 1 | |

## glibc (libm-test-*.inc) — 769 divergences

| Function | Divergences | Notes |
|----------|-------------|-------|
| fmodf | 113 | |
| remainderf | 68 | |
| remquof | 62 | |
| fmod | 60 | |
| remainder | 40 | |
| fdimf | 36 | |
| fdim | 36 | |
| remquo | 34 | |
| cprojf | 28 | |
| cproj | 28 | |
| fminf | 24 | |
| fmin | 24 | |
| fmaxf | 24 | |
| fmax | 24 | |
| nextafterf | 22 | |
| nextafter | 22 | |
| rintf | 16 | |
| nearbyintf | 16 | |
| ilogbf | 8 | |
| copysignf | 8 | |
| copysign | 8 | |
| ilogb | 4 | |
| truncf | 2 | |
| trunc | 2 | |
| scalbnf | 2 | |
| scalbn | 2 | |
| scalblnf | 2 | |
| scalbln | 2 | |
| roundf | 2 | |
| round | 2 | |
| rint | 2 | |
| nearbyint | 2 | |
| modff | 2 | |
| modf | 2 | |
| lroundf | 2 | |
| lround | 2 | |
| lrintf | 2 | |
| lrint | 2 | |
| logbf | 2 | |
| logb | 2 | |
| llroundf | 2 | |
| llround | 2 | |
| llrintf | 2 | |
| llrint | 2 | |
| frexpf | 2 | |
| frexp | 2 | |
| floorf | 2 | |
| floor | 2 | |
| fabsf | 2 | |
| fabs | 2 | |
| conjf | 2 | |
| conj | 2 | |
| ceilf | 2 | |
| ceil | 2 | |

## Observations

1. **exp2: infinite loop** — All 33 exp2 divergences are SIGALRM timeouts. The Rust `exp2` hangs on inputs near overflow/underflow boundaries. This is a correctness bug.

2. **tgamma/tgammaf: largest divergence** — 447 total mismatches. Gamma function edge cases differ between C and Rust implementations.

3. **Symmetric d/f divergences** — Most functions show the same divergence count for double and float variants (e.g., fmod=60, fmodf=113), suggesting the Rust transpilation has systematic issues, not random bit errors.

4. **NaN/special value handling** — Many inc-test divergences (cproj, copysign, nextafter, fabs, ceil, floor, etc.) show exactly 2 mismatches each, likely sNaN propagation or signed-zero handling differences.

5. **fmod family: high divergence** — fmod/fmodf/remainder/remquo together account for 377 divergences, suggesting the division/remainder algorithm differs.

## Diff files

- `tests/glibc_diff.txt` — full diff for auto-libm-test-in
- `tests/glibc_inc_diff.txt` — full diff for libm-test-*.inc
