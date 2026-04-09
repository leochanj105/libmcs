# Compact Divergences — Round 1

16 test failures across 13 functions, grouped by root cause:

## 1. fenv stubs (5 failures)
- `feclearexcept(0)`, `feraiseexcept(0)`, `fegetround()`, `fesetround(0)`, `fetestexcept(0)`
- All return -1 (error) instead of 0 (success)
- Root cause: Rust stubs unconditionally return -1 in `lib.rs:17-27`

## 2. __fpclassifyf (4 failures)
- Wrong enum values: Rust uses FP_ZERO=0, FP_NAN=1, FP_SUBNORMAL=2, FP_INFINITE=3
- C library uses FP_NAN=0, FP_INFINITE=1, FP_ZERO=2, FP_SUBNORMAL=3, FP_NORMAL=4
- Root cause: `mathf.rs:3161-3168` hardcodes wrong classification constants

## 3. acosh (1 failure)
- acosh(2) → C: 0x1.5124271980434p+0, Rust: 0x1.62e42fefa39efp+0 (= ln(4) = 2·ln(2))
- Root cause: `mathd.rs:1412` missing `sqrt()` call — `(2t + t²).ln_1p()` instead of `(t + sqrt(2t + t²)).ln_1p()`

## 4. cproj (1 failure)
- cproj(inf+1i) → C: inf+0i, Rust: inf+1i
- Root cause: `complexd.rs:126` reversed copysign — `z.im.copysign(0.0)` gives |z.im| not 0.0

## 5. exp2 + pow (2 failures, shared root cause)
- exp2(10) and pow(2,10) both give 0x1.b2d809254afbcp+11 instead of 0x1p+10 (1024)
- pow root cause: `mathd.rs:3683-3685` computes `p_h2 = p_h - t_var` then discards it (`let _ = p_h2`)
  instead of updating p_h in-place as the C code does (`p_h -= t`)
- exp2 root cause: `mathd.rs:2120` uses `(2.0f64).powf(x)` instead of `powd(2.0, x)` to match C

## 6. lgamma signgam (1 failure)
- lgamma(-0.5) → C: signgam=-1, Rust: signgam=0
- Root cause: likely thread-local SIGNGAM mechanism or global `signgam` symbol linkage issue
  across FFI boundary

## 7. nexttoward + nexttowardf (2 failures)
- Both step in wrong direction (toward 0 instead of toward 2)
- nexttoward(1.0, 2.0) → C: 0x1.0000000000001p+0, Rust: 0x1.fffffffffffffp-1
- Root cause: C signature uses `long double y` (80-bit on x86-64) but Rust declares `y: f64` —
  ABI mismatch causes y to receive garbage value
