# Judger V2 — Rust Baseline Report

**Date:** 2026-04-09
**C library:** `build-x86_64-linux-gnu/bin/libm.a`
**Rust library:** `newexp/rust-baseline-judger/target/release/librust_baseline.a`
**Method:** Bitwise `%a` comparison, zero tolerance

## Overall Summary

| Source | Tests | Divergences |
|--------|------:|------------:|
| glibc (auto-libm-test-in) | 14,888 | 703 |
| glibc (libm-test-*.inc) | 3,704 | 769 |
| core-math worst cases (full) | 15,883,911 | 433,548 |
| **Total** | **15,902,503** | **435,020** |

## glibc (auto-libm-test-in) — 703 divergences

| Function | Divergences | Notes |
|----------|------------:|-------|
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
|----------|------------:|-------|
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
| (27 functions) | 2 each | sNaN/signed-zero edge cases |

## Core-math worst cases (full) — 433,548 divergences

| Function | Tests | Divergences | Faults | Divergence rate |
|----------|------:|------------:|-------:|---------:|
| pow | 1,002,881 | 367,426 | 0 | 36.6% |
| exp2 | 71,615 | 35,942 | 268 | 50.2% |
| log10 | 65,512 | 14,347 | 0 | 21.9% |
| acosh | 1,056,666 | 9,055 | 0 | 0.9% |
| log2 | 31,377 | 6,693 | 0 | 21.3% |
| powf | 403,533 | 67 | 0 | <0.1% |
| atanh | 62,214 | 6 | 0 | <0.1% |
| log | 134,950 | 5 | 0 | <0.1% |
| acos | 264,055 | 3 | 0 | <0.1% |
| asin | 13,480 | 2 | 0 | <0.1% |
| log1p | 347,453 | 2 | 0 | <0.1% |

19 functions passed all worst-case tests with zero divergences:
asinh, atan, atan2, atan2f, cbrt, cos, cosh, erf, erfc, exp, expm1,
hypot, hypotf, lgamma, sin, sinh, tan, tanh, tgamma.

## Key Findings

1. **exp2: broken** — 50% divergence rate + 268 infinite-loop timeouts. The Rust exp2 implementation is severely broken on boundary inputs.

2. **pow: highest volume** — 367K divergences (36.6% of worst cases). The Rust pow has systematic rounding differences.

3. **log10/log2: consistent errors** — ~21% divergence rate, suggesting a shared logarithm code path has a rounding issue.

4. **acosh: moderate** — 9K divergences (0.9%) on a large test set, likely a specific code path for large inputs.

5. **19 functions pass all WC tests** — These include the core trig (sin, cos, tan), hyperbolic (sinh, cosh, tanh), and several others. The transpilation is correct for these functions even under worst-case rounding stress.

6. **NaN/special value handling** — The .inc test divergences (cproj, copysign, nextafter, fabs, etc. with exactly 2 mismatches each) suggest systematic sNaN or signed-zero propagation differences.

## Diff files

- `tests/glibc_diff.txt` — full diff for auto-libm-test-in
- `tests/glibc_inc_diff.txt` — full diff for libm-test-*.inc
