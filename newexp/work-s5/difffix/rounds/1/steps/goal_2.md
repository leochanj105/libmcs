# Goal 2: Fix __fpclassifyf wrong classification constants

## Function
__fpclassifyf (float classification)

## Source Files
- C source: /home/leochanj/Desktop/libmcs/libm/mathf/internal/fpclassifyf.c
- Rust source: /home/leochanj/Desktop/libmcs/newexp/rust-s5/src/mathf.rs (or internal module)

## What's Wrong
The Rust __fpclassifyf returns wrong classification values. The enum mapping is different from C:

| Input | C result | Rust result |
|-------|----------|-------------|
| 0x0p+0 (zero) | 2 | 0 |
| inf | 1 | 3 |
| nan | 0 | 1 |

Plus 3 more similar mismatches. The classification constants are permuted.

## What Needs to Change
Match the C library's FP classification constants exactly:
- NAN → 0
- INFINITE → 1
- ZERO → 2
- (check the C header for NORMAL, SUBNORMAL values too)

The Rust code likely uses different constant values (possibly from Rust's standard library or a different convention). Replace them with the exact values from the C libmcs headers.

## Success Criteria
- __fpclassifyf(0) returns 2
- __fpclassifyf(inf) returns 1
- __fpclassifyf(nan) returns 0
- All 6 __fpclassifyf test cases match C output bitwise
