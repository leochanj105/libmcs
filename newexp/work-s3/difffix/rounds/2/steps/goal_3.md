# Goal 3: Fix fpclassifyf — wrong classification values

## Function
- `fpclassifyf` (float classification via `__fpclassifyf`)

## Source Files
- C: `/home/leochanj/Desktop/libmcs/libm/mathf/internal/fpclassifyf.c`
- Rust: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathf.rs` line ~3161 (__fpclassifyf)

## Problem
MISMATCH: fpclassifyf returns wrong classification integer codes. The mapping
of FP class to integer is wrong in the Rust version.

Failing tests:
- fpclassifyf(0x0p+0): C returns 2, Rust returns 0
- fpclassifyf(inf): C returns 1, Rust returns 3
- fpclassifyf(nan): C returns 0, Rust returns 1
- (1 more mismatch not shown)

The C library uses: NaN=0, Inf=1, Zero=2, Subnormal=3, Normal=4 (or similar).
The Rust version uses different integer codes.

## What Needs to Change
Compare the classification constants in the Rust __fpclassifyf with the C version.
The return values for each floating-point class must match the C library's values exactly.
Check the #define or enum values used in the C code and replicate them in Rust.

## Success Criteria
- fpclassifyf(0x0p+0) = 2 — bitwise exact
- fpclassifyf(inf) = 1 — bitwise exact
- fpclassifyf(nan) = 0 — bitwise exact
- All 4 fpclassifyf test cases match C output exactly
