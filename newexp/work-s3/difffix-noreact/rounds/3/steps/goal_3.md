# Goal 3: Fix fpclassifyf classification constants

## Function
fpclassifyf (__fpclassifyf)

## Source Files
- C: /home/leochanj/Desktop/libmcs/libm/mathf/internal/fpclassifyf.c
- Rust: /home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathf.rs (fn __fpclassifyf, line ~3161)

## What's Wrong
Output mismatch — 4 tests return wrong classification values.
- `fpclassifyf(0)`: C=2, Rust=0
- `fpclassifyf(inf)`: C=1, Rust=3
- `fpclassifyf(nan)`: C=0, Rust=1
- Plus 1 more mismatch (likely subnormal)

The Rust implementation uses different numeric constants for the FP classification categories than the C library defines.

## What Needs to Change
Read the C fpclassifyf.c to find the correct constant values for each classification (FP_NAN, FP_INFINITE, FP_ZERO, FP_SUBNORMAL, FP_NORMAL). Update the Rust __fpclassifyf to return the same constants. The C library likely defines: FP_NAN=0, FP_INFINITE=1, FP_ZERO=2, FP_SUBNORMAL=3, FP_NORMAL=4 (or similar).

## Success Criteria
- `fpclassifyf(0)` returns 2 (matching C)
- `fpclassifyf(inf)` returns 1 (matching C)
- `fpclassifyf(nan)` returns 0 (matching C)
- All fpclassifyf classifications match the C output bitwise
