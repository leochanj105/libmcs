# Judger V2 — C vs Rust Differential Report

**Date:** 2026-04-09 (all libraries rebuilt from source before testing)
**C library:** `build-x86_64-linux-gnu/bin/libm.a`
**Method:** Bitwise `%a` comparison, zero tolerance. Per-test fault isolation (SIGALRM 1s timeout for hangs, signal handlers for crashes).

## Overall Summary

| Source | Tests | Baseline | S2 | S3 | S4 | S5 |
|--------|------:|---------:|---:|---:|---:|---:|
| glibc (auto-libm-test-in) | 14,888 | 642 | 501 | 496 | 500 | 495 |
| glibc (libm-test-*.inc) | 3,704 | 775 | 351 | 317 | 377 | 317 |
| core-math WC (full) | 15,883,911 | 415,073 | 21,246 | 21,246 | 21,246 | 6,904 |
| **Total** | **15,902,503** | **416,490** | **22,098** | **22,059** | **22,123** | **7,716** |

## glibc (auto-libm-test-in)

| Function | Baseline | S3 | S4 | S5 |
|----------|--------:|---:|---:|---:|
| tgammaf | 245 | 245 | 245 | 245 |
| tgamma | 202 | 202 | 202 | 202 |
| pow | 20 | 0 | 0 | 0 |
| cacoshf | 10 | 10 | 10 | 10 |
| exp2 | 33 | 0 | 0 | 0 |
| ctanf | 7 | 3 | 7 | 3 |
| sinf | 5 | 5 | 5 | 5 |
| cosf | 5 | 5 | 5 | 5 |
| cacosh | 5 | 5 | 5 | 5 |
| tanf | 4 | 4 | 4 | 4 |
| cexpf | 4 | 4 | 4 | 4 |
| ctanhf | 3 | 3 | 3 | 3 |
| ctanh | 2 | 2 | 2 | 2 |
| ctan | 2 | 2 | 2 | 2 |
| cpow | 2 | 0 | 0 | 0 |
| cexp | 2 | 2 | 2 | 2 |
| atan2f | 44 | 0 | 0 | 0 |
| atan2 | 44 | 0 | 0 | 0 |
| cargf | 10 | 0 | 0 | 0 |
| carg | 10 | 0 | 0 | 0 |
| casinhf | 9 | 0 | 0 | 0 |
| casinf | 6 | 0 | 0 | 0 |
| cacosf | 6 | 0 | 0 | 0 |
| casinh | 5 | 0 | 0 | 0 |
| casin | 3 | 0 | 0 | 0 |
| cacos | 3 | 0 | 0 | 0 |
| ccosf | 2 | 0 | 0 | 0 |
| atanf | 2 | 0 | 0 | 0 |
| atan | 2 | 0 | 0 | 0 |
| cpowf | 2 | 1 | 1 | 0 |
| tan | 1 | 1 | 1 | 1 |
| sin | 1 | 1 | 1 | 1 |
| cos | 1 | 1 | 1 | 1 |
| ccos | 1 | 0 | 0 | 0 |

## glibc (libm-test-*.inc)

| Function | Baseline | S3 | S4 | S5 |
|----------|--------:|---:|---:|---:|
| fmodf | 113 | 95 | 95 | 95 |
| remainderf | 68 | 50 | 50 | 50 |
| remquof | 62 | 44 | 44 | 44 |
| fmod | 60 | 40 | 40 | 40 |
| remainder | 40 | 22 | 22 | 22 |
| remquo | 34 | 16 | 16 | 16 |
| cprojf | 28 | 0 | 26 | 0 |
| cproj | 28 | 0 | 26 | 0 |
| fminf | 24 | 0 | 0 | 0 |
| fmin | 24 | 0 | 0 | 0 |
| fmaxf | 24 | 0 | 0 | 0 |
| fmax | 24 | 0 | 0 | 0 |
| nextafterf | 22 | 0 | 0 | 0 |
| nextafter | 22 | 6 | 6 | 6 |
| rintf | 16 | 14 | 14 | 14 |
| nearbyintf | 16 | 14 | 14 | 14 |
| ilogbf | 8 | 0 | 6 | 0 |
| copysignf | 8 | 0 | 0 | 0 |
| copysign | 8 | 0 | 0 | 0 |
| fdimf | 36 | 8 | 8 | 8 |
| fdim | 36 | 8 | 8 | 8 |
| ilogb | 4 | 0 | 2 | 0 |
| (27 functions) | 2 each | 0 each | 0 each | 0 each |

## Core-math worst cases (full)

| Function | Tests | Baseline | S3 | S4 | S5 |
|----------|------:|---------:|---:|---:|---:|
| pow | 1,002,881 | 367,426 | 108 | 108 | 108 |
| exp2 | 71,615 | 17,467 | 3 | 3 | 3 |
| log10 | 65,512 | 14,347 | 14,347 | 14,347 | 5 |
| acosh | 1,056,666 | 9,055 | 10 | 10 | 10 |
| log2 | 31,377 | 6,693 | 6,693 | 6,693 | 6,693 |
| powf | 403,533 | 67 | 67 | 67 | 67 |
| atanh | 62,214 | 6 | 6 | 6 | 6 |
| log | 134,950 | 5 | 5 | 5 | 5 |
| acos | 264,055 | 3 | 3 | 3 | 3 |
| asin | 13,480 | 2 | 2 | 2 | 2 |
| log1p | 347,453 | 2 | 2 | 2 | 2 |

19 functions pass all WC tests in all versions: asinh, atan, atan2, atan2f, cbrt, cos, cosh, erf, erfc, exp, expm1, hypot, hypotf, lgamma, sin, sinh, tan, tanh, tgamma.

## Key Findings

1. **Stale binaries invalidated prior results.** S3 and S5 had source changes not reflected in compiled binaries. After rebuild, numbers changed dramatically (e.g., S3 WC: 403,974 → 21,246; S5 WC: 406,028 → 6,904).

2. **S5 is the best overall** — 7,716 total divergences, down from 416,490 baseline (98.1% reduction).

3. **S3/S4 are nearly identical on WC** — Both at 21,246. S4 has more glibc divergences due to cproj and ilogb regressions not present in S3.

4. **pow: massive fix** — 367,426 → 108 across S3-S5 (99.97% reduction). 108 remaining divergences are hard-to-round edge cases.

5. **exp2: fixed** — 17,467 → 3 (99.98% reduction). Baseline had 33 infinite-loop timeouts, all eliminated.

6. **log10: S5 breakthrough** — 14,347 → 5. S3/S4 didn't fix this at all.

7. **log2: unfixed** — 6,693 across all versions. This is the largest remaining WC divergence.

8. **tgamma: unfixed** — 447 glibc divergences across all versions. Never addressed by any scenario.

9. **fmod/remainder family: partially fixed** — Reduced but still significant (S3/S5 both at 267 total from .inc tests).

10. **S4 regressions vs S3** — cproj (52 divergences), ilogb (8), ctanf (4 more). These were fixed in S3, broken in S4, re-fixed in S5.

## Remaining divergences in best version (S5): 7,716

| Category | Count | Functions |
|----------|------:|-----------|
| log2 WC | 6,693 | log2 |
| tgamma glibc | 447 | tgamma, tgammaf |
| fmod/rem glibc | 267 | fmod, fmodf, remainder, remainderf, remquo, remquof |
| pow WC | 108 | pow |
| powf WC | 67 | powf |
| rintf/nearbyintf | 28 | rintf, nearbyintf |
| cacosh glibc | 15 | cacosh, cacoshf |
| complex glibc | 14 | ctanf, ctanhf, ctanh, ctan, cexp, cexpf |
| fdim glibc | 16 | fdim, fdimf |
| acosh WC | 10 | acosh |
| misc WC | 18 | acos, asin, atanh, log, log1p, log10 |
| misc glibc | 33 | sin, sinf, cos, cosf, tan, tanf, nextafter |
