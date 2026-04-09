# Goal 2: Fix exp2 — wrong results for specific inputs

## Function
- `exp2` (double)

## Source Files
- C: `/home/leochanj/Desktop/libmcs/libm/mathd/exp2d.c`
- Rust: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathd.rs` line ~2119 (exp2d)

## Problem
MISMATCH: exp2 produces incorrect results for two test inputs.

Failing tests:
- exp2(0x1.ff8p+9): C returns 0x1p+1023, Rust returns 0x1.ffffffffcf4p+1022
  (Input is 1023.0; result should be exactly 2^1023)
- exp2(0x1.4p+3): C returns 0x1p+10, Rust returns 0x1.b2d809254afbcp+11
  (Input is 10.0; result should be exactly 1024.0 = 2^10)

These are exact integer powers of 2 that should produce exact results.

## What Needs to Change
The Rust exp2d implementation has a computational error. Compare with the C source
to find where the calculation diverges. The function should return exact results
for integer inputs that are within range (ldexp(1.0, n) for integer n).

## Success Criteria
- exp2(0x1.ff8p+9) = 0x1p+1023 — bitwise exact
- exp2(0x1.4p+3) = 0x1p+10 — bitwise exact
