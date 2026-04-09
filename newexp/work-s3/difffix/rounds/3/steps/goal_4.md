# Goal 4: Fix logb — wrong result for subnormal input

## Function
- `logb` (double)

## Source Files
- C: `/home/leochanj/Desktop/libmcs/libm/mathd/logbd.c`
- Rust: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathd.rs`

## Problem
MISMATCH: logb(0x0.0000000000001p-1022) should return -0x1.0c8p+10 (i.e., -1096) but
Rust returns -0x1.0ccp+10 (i.e., -1100).

The input is the smallest subnormal double (2^-1074). logb returns the unbiased exponent,
so logb(2^-1074) = -1074. Wait — let me check: -0x1.0c8p+10 = -1096... Hmm, logb of
a subnormal should be floor(log2(|x|)). For 0x0.0000000000001p-1022, the value is 2^-1074,
so logb should return -1074. But the C result is -1096 which suggests a different subnormal.

The actual value 0x0.0000000000001p-1022 has the minimum subnormal significand (1 in last bit),
which is 2^-52 * 2^-1022 = 2^-1074. But -0x1.0c8p+10 = -(1 + 0x0c8/0x1000)*1024 = 
-(1 + 200/4096)*1024 = -(1.048828125)*1024 = -1074.0. Yes, -0x1.0c8p+10 = -1074.

And -0x1.0ccp+10 = -(1 + 0x0cc/0x1000)*1024 = -(1 + 204/4096)*1024 = -1074 - 4 = nope,
let me recalculate: 0x0cc = 204, 204/4096 = 0.04980..., so -(1.04980...)*1024 = -1075.0.
Actually 0x1.0ccp+10 = 0x10cc shifted = 4300/4 = 1075.0. Hmm. Let me just note the hex values.

Regardless, the Rust logb is returning the wrong exponent for this subnormal. The subnormal
handling likely has an off-by-one or incorrect bit-counting for leading zeros.

## What Needs to Change
Compare the Rust logb (logbd) subnormal handling against the C version. The C code normalizes
subnormals by multiplying by 2^54 (or similar) then subtracting the bias. The Rust version
likely has a wrong constant or off-by-one in the subnormal branch.

## Success Criteria
- logb 0x0.0000000000001p-1022 = -0x1.0c8p+10 — bitwise exact match with C
