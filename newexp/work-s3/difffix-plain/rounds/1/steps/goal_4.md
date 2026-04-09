# Goal 4: Fix sinf — wrong output near pi

## Function
`sinf` (float-precision)

## Source files
- C: /home/leochanj/Desktop/libmcs/libm/mathf/sinf.c (also internal/trigf.c for __sinf, __rem_pio2f)
- Rust: /home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathf.rs

## Problem
sinf(0x1.921fb6p+1) = -0x1.6bff7ap-16 (Rust) vs -0x1.777a5cp-24 (C)

The input 0x1.921fb6p+1 is pi (float). The C result is ~1e-7 (correct, near zero), but the Rust result is ~1e-5, off by a factor of ~256. This suggests either:
- __rem_pio2f range reduction is slightly wrong
- __sinf or __cosf polynomial evaluation has wrong coefficients
- The argument reduction for values near pi is mishandled

## What needs to change
Compare Rust sinf and its internal helpers (__rem_pio2f, __sinf, __cosf) against the C originals in sinf.c and internal/trigf.c. Focus on range reduction constants and polynomial coefficients.

## Success Criteria
- `sinf 0x1.921fb6p+1` = `-0x1.777a5cp-24` (bitwise exact)
- All other sinf tests continue to pass
