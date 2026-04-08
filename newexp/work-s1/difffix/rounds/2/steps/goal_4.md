# Goal 4: Fix pow

## Function
`pow`

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/powd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s1/src/mathd.rs` (line 3504, `pub fn powd`)

## Problem: MISMATCH
Input: `pow(0x1p+1, 0x1.8p+1)` = `pow(2.0, 3.0)`
- C output:    `pow(2.0, 3.0) = 0x1p+3` (exactly 8.0)
- Rust output: `pow(2.0, 3.0) = 0x1.fffee746db0fcp+5` (approximately 63.999)

The Rust result is ~64 instead of 8. This is a major computational error — the result is off by a factor of 8 (2^3). This suggests a bug in the exponent computation, possibly computing `2^6` instead of `2^3`, or a broken special-case path for integer exponents.

## Related Failures
Same root cause likely affects `cpow` (goal 5), since cpow with zero imaginary parts reduces to pow.

## What Needs to Change
Compare the Rust `powd` implementation against the C version, focusing on:
1. The special-case handling for integer exponents
2. The log2/exp2 decomposition: `pow(x,y) = exp2(y * log2(x))`
3. Whether the exponent multiplication or log2 computation has an off-by-one or scaling error

## Success Criteria
`pow(0x1p+1, 0x1.8p+1)` must return exactly `0x1p+3` (8.0, bitwise match with C).
