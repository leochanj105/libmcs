# Goal 1: Fix sinf — wrong result near pi

## Function
- `sinf` (float)

## Source Files
- C: `/home/leochanj/Desktop/libmcs/libm/mathf/sinf.c`
- C internal: `/home/leochanj/Desktop/libmcs/libm/mathf/internal/trigf.c` (__rem_pio2f, __sinf, __cosf)
- Rust: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathf.rs`

## Problem
MISMATCH: sinf(0x1.921fb6p+1) should return -0x1.777a5cp-24 but Rust returns -0x1.6bff7ap-16.

The input 0x1.921fb6p+1 is the float representation of pi. sin(pi) should be very close to zero.
The C result (-0x1.777a5cp-24 ~ -8.74e-8) is much more accurate than the Rust result
(-0x1.6bff7ap-16 ~ -2.14e-5), indicating a precision problem in the Rust argument reduction
(__rem_pio2f) or the polynomial evaluation (__sinf/__cosf).

## What Needs to Change
Compare the Rust sinf implementation and its internal helpers (__rem_pio2f_internal, __sinf, __cosf)
against the C originals. The argument reduction for values near multiples of pi/2 likely has
a precision bug — possibly wrong constants or a missing step in the range reduction.

## Success Criteria
- sinf 0x1.921fb6p+1 = -0x1.777a5cp-24 — bitwise exact match with C
