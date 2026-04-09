# Goal 1: Fix pow — wrong results for integer exponents

## Function
- `pow` (double, mapped as `powl` in tests)

## Source Files
- C: `/home/leochanj/Desktop/libmcs/libm/mathd/powd.c`
- Rust: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathd.rs` (fn powd, line 3521)

## Problem
MISMATCH: pow produces incorrect results for simple integer exponent cases.

Test case 1: pow(0x1p+1, 0x1.4p+3) i.e. pow(2.0, 10.0)
- C:    0x1p+10       (1024.0 — correct)
- Rust: 0x1.b2d809254afbcp+11  (~3478.8 — wrong)

Test case 2: pow(-0x1p+1, 0x1.8p+1) i.e. pow(-2.0, 3.0)
- C:    -0x1p+3       (-8.0 — correct)
- Rust: -0x1.fffee746db0fcp+5  (~-64.0 — wrong)

Both cases involve small integer bases and exponents where the exact result is representable
as a floating-point number. The Rust results are wildly off, suggesting a fundamental bug in
the pow algorithm — likely in the exponent computation path (exp2/log2 decomposition),
coefficient tables, or the special-case handling for integer exponents.

## What Needs to Change
Compare the Rust powd implementation against the C powd.c source. Look for:
1. Incorrect polynomial coefficients or lookup tables
2. Wrong bit manipulation in the exponent extraction
3. Missing or incorrect special-case path for integer exponents
4. Errors in the log2(x)*y or exp2() reconstruction steps

## Success Criteria
- pow 0x1p+1 0x1.4p+3 = 0x1p+10 — bitwise exact match with C
- pow -0x1p+1 0x1.8p+1 = -0x1p+3 — bitwise exact match with C
