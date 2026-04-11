# Judger V2 — C vs Rust Differential Report

**Date:** 2026-04-09 (all libraries rebuilt from source before testing)
**C library:** `build-x86_64-linux-gnu/bin/libm.a`
**Method:** Bitwise `%a` comparison, zero tolerance. Per-test fault isolation (SIGALRM 1s timeout for hangs, signal handlers for crashes).

## Overall Summary

| Source | Tests | Baseline | S1 | S2 | S3 | S4 | S5 | S6 |
|--------|------:|---------:|---:|---:|---:|---:|---:|---:|
| glibc (auto-libm-test-in) | 14,888 | 642 | 496 | 501 | 496 | 500 | 495 | 495 |
| glibc (libm-test-*.inc) | 3,704 | 775 | 325 | 351 | 317 | 377 | 317 | 317 |
| glibc (extra: misc/snan/signgam) | 136 | 77 | 32 | 0 | 0 | 19 | 19 | 19 |
| core-math WC (full) | 15,883,911 | 415,073 | 21,246 | 21,246 | 21,246 | 21,246 | 6,904 | 6,904 |
| **Total** | **15,902,639** | **416,567** | **22,099** | **22,098** | **22,059** | **22,142** | **7,735** | **7,735** |

## glibc extra (test-misc.c, test-signgam-main.c, test-snan.c derived) — 136 tests

Hand-curated tests extracted from glibc's standalone `.c` test files that
weren't covered by `auto-libm-test-in` or `libm-test-*.inc`:
- Classification macros (`fpclassify`, `isnan`, `isinf`, `isfinite`, `isnormal`, `signbit`) on special values
- `nextafter`/`nextafterf` equivalences at `±0 → ±inf` vs `±0 → ±1`
- Boundary traversals (`DBL_MIN → 0`, `DBL_TRUE_MIN → 0`, `DBL_MAX → INFINITY`)
- `modf`/`modff` and `frexp`/`frexpf` decomposition on special values
- `lgamma`/`lgammaf` side-effect on `__signgam` global

| Divergence category | Baseline | S1 | S2 | S3 | S4 | S5 | S6 |
|---------------------|---------:|---:|---:|---:|---:|---:|---:|
| fpclassify | 18 | 7 | 0 | 0 | 0 | 0 | 0 |
| lgamma signgam | 12 | 12 | 0 | 0 | 12 | 12 | 12 |
| lgammaf signgam | 7 | 7 | 0 | 0 | 7 | 7 | 7 |
| nextafter/nextafterf specials | 14 | 2 | 0 | 0 | 0 | 0 | 0 |
| signbit | 6 | 0 | 0 | 0 | 0 | 0 | 0 |
| isnan | 6 | 2 | 0 | 0 | 0 | 0 | 0 |
| isinf | 4 | 2 | 0 | 0 | 0 | 0 | 0 |
| isfinite | 4 | 0 | 0 | 0 | 0 | 0 | 0 |
| isnormal | 2 | 0 | 0 | 0 | 0 | 0 | 0 |
| modf/modff | 3 | 0 | 0 | 0 | 0 | 0 | 0 |
| frexp | 1 | 0 | 0 | 0 | 0 | 0 | 0 |

**Key finding:** S1–S6 are independent scenarios, each starting from the
same baseline Rust code and running its own transpilation-fix pipeline. S2
and S3's fix pipelines happened to catch and fix the `signgam` side effect;
S4/S5/S6's did not. All 19 remaining divergences in S5/S6 for this source
are `lgamma`/`lgammaf` leaving `__signgam = 0` instead of setting the
correct sign. The return values are correct — only the global side effect
is unfixed.

**Linking note:** The baseline Rust lib exports `__fpclassify`/`__signbit`
(wrong names) instead of libmcs's `__fpclassifyd`/`__signbitd`. Without
weak-symbol fallbacks in `compat_builtins.c`, the test wouldn't even link
against the baseline — which is itself a bug.

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

S1–S6 are **independent fix scenarios**, each starting from the same baseline
Rust code and running its own transpilation-fix pipeline. Differences between
them reflect which bugs each scenario's test generator + fixer happened to
catch, not cumulative improvements.

1. **Stale binaries invalidated prior results.** S3 and S5 had source changes not reflected in compiled binaries. After rebuild, numbers changed dramatically (e.g., S3 WC: 403,974 → 21,246; S5 WC: 406,028 → 6,904). Always rebuild before testing.

2. **S5 and S6 are tied for best overall** — 7,735 total divergences, down from 416,567 baseline (98.1% reduction).

3. **pow: massive fix** — 367,426 → 108 across S1–S6 (99.97% reduction). 108 remaining divergences are hard-to-round edge cases.

4. **exp2: fixed** — 17,467 → 3 across S1–S6 (99.98% reduction). Baseline had 33 infinite-loop timeouts, all eliminated.

5. **log10: only S5/S6 caught it** — 14,347 → 5. S1–S4 didn't fix this at all. The fix is a one-character change (adding parentheses for floating-point associativity) triggered by `log10(5.0)` appearing in S5's test suite.

6. **signgam: only S2/S3 caught it** — 19 divergences on `lgamma`/`lgammaf` in S1, S4–S6 because they don't set the `__signgam` global. S2/S3 correctly export and update it.

7. **Classification macros: only baseline/S1 miss these** — `fpclassify`, `isnan`, `isinf`, `signbit`, etc. Baseline exports wrong symbol names (`__fpclassify` instead of `__fpclassifyd`); S1 partially fixes it; S2–S6 fully fix it.

8. **log2: unfixed by any scenario** — 6,693 WC divergences across all versions. This is the largest remaining WC divergence.

9. **tgamma: unfixed by any scenario** — 447 glibc divergences across all versions. Never addressed.

10. **fmod/remainder family: partially fixed** — Reduced but still significant (~267 divergences in the .inc tests across all fix scenarios).

11. **No single scenario catches everything** — S2/S3 catch signgam but miss log10. S5/S6 catch log10 but miss signgam. A hypothetical "best combined" would be S3+S5's fixes (22,059 − 14,342 − 19 ≈ 7,698), still not zero.

## Remaining divergences in best version (S5 or S6): 7,735

| Category | Count | Functions |
|----------|------:|-----------|
| log2 WC | 6,693 | log2 |
| tgamma glibc | 447 | tgamma, tgammaf |
| fmod/rem glibc | 267 | fmod, fmodf, remainder, remainderf, remquo, remquof |
| pow WC | 108 | pow |
| powf WC | 67 | powf |
| rintf/nearbyintf | 28 | rintf, nearbyintf |
| lgamma/lgammaf signgam | 19 | lgamma, lgammaf (side effect only — return values correct) |
| cacosh glibc | 15 | cacosh, cacoshf |
| complex glibc | 14 | ctanf, ctanhf, ctanh, ctan, cexp, cexpf |
| fdim glibc | 16 | fdim, fdimf |
| acosh WC | 10 | acosh |
| misc WC | 18 | acos, asin, atanh, log, log1p, log10 |
| misc glibc | 33 | sin, sinf, cos, cosf, tan, tanf, nextafter |
