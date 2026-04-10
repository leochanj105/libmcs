# Goal 2: Fix `__fpclassifyf` enum values

## Function
`__fpclassifyf` (internal float classification)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathf/internal/fpclassifyf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s6/src/mathf.rs` (around line 3161, `__fpclassifyf`)

## Problem
MISMATCH — 5 test failures. The Rust function returns different integer class codes than the C version.

```
C:    __fpclassifyf zero = 2       Rust: 0
C:    __fpclassifyf inf = 1        Rust: 3
C:    __fpclassifyf subnorm = 3    Rust: 2
```

The classification enum mapping is wrong — the Rust code uses different numeric values for FP_ZERO, FP_INFINITE, FP_SUBNORMAL, FP_NORMAL, and FP_NAN.

## What Needs to Change
Match the return values in Rust to the C library's classification constants:
- FP_INFINITE = 1
- FP_ZERO = 2
- FP_SUBNORMAL = 3
- FP_NORMAL = 4
- FP_NAN = 0 (verify from C source)

Read the C source to confirm the exact enum values and update the Rust implementation.

## Success Criteria
- `__fpclassifyf` returns identical integer class codes as C for: zero, inf, -inf, subnorm, normal, NaN
- All 5 failing tests pass with bitwise-exact match
