# Goal 4: Fix exp2 and pow wrong computation

## Functions
- exp2 (2^x, double precision)
- pow (x^y, double precision)

## Source Files
- C source (exp2): /home/leochanj/Desktop/libmcs/libm/mathd/exp2d.c
- C source (pow): /home/leochanj/Desktop/libmcs/libm/mathd/powd.c
- Rust source: /home/leochanj/Desktop/libmcs/newexp/rust-s5/src/mathd.rs

## What's Wrong
Both functions produce very wrong results for basic inputs:

**exp2:**
- C: exp2(10) = 0x1p+10 (1024)
- Rust: exp2(10) = 0x1.b2d809254afbcp+11 (~3494)

**pow (6 mismatches):**
- C: pow(2, 10) = 0x1p+10 (1024) → Rust: 0x1.b2d809254afbcp+11 (~3494)
- C: pow(-2, 3) = -8 → Rust: -0x1.fffee746db0fcp+5 (~-64)
- C: pow(0.5, -2) = 4 → Rust: 0x1.fffffedd903acp+3 (~16)

The exp2 error and pow(2,10) error produce the SAME wrong value, confirming pow likely uses exp2 internally. The exp2 algorithm itself is broken.

## What Needs to Change
1. Fix exp2d — the core computation is wrong. Compare the Rust exp2d implementation with the C exp2d.c line by line.
2. Once exp2 is fixed, pow should also improve (but pow may have additional issues for negative base / integer exponent cases).
3. Check pow's handling of integer exponents separately.

## Success Criteria
- exp2(10) = 0x1p+10 (exactly 1024)
- pow(2, 10) = 0x1p+10
- pow(-2, 3) = -0x1p+3 (exactly -8)
- pow(0.5, -2) = 0x1p+2 (exactly 4)
- All exp2 and pow test cases match C output bitwise
