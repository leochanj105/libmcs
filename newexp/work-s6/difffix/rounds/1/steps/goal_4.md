# Goal 4: Fix `cosf` large-argument reduction

## Function
`cosf` (single-precision cosine)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathf/cosf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s6/src/mathf.rs` (around line 1341, `cosf`)

## Problem
MISMATCH — 2 test failures. Large-argument results are very wrong.

```
C:    cosf 3*pi/2 = 0x1.99bc5cp-27
Rust: cosf 3*pi/2 = 0x1.1p-15

C:    cosf 7*pi/2 = 0x1.644588p-21
Rust: cosf 7*pi/2 = 0x1.3fff8cp-14
```

The errors grow with argument size, suggesting the argument reduction (pi/2 reduction) is inaccurate. This may be related to the `__cosf` kernel fix (Goal 1) and/or the `__rem_pio2f` reduction.

## What Needs to Change
Compare the Rust `cosf` implementation against C, focusing on:
1. Argument reduction path (`__rem_pio2f` or inline reduction)
2. Quadrant selection logic
3. How the kernel functions (`__cosf`, `__sinf`) are called based on reduction result

Note: Fixing Goal 1 (`__cosf` kernel) may partially help, but the magnitude of error here suggests argument reduction is the primary issue.

## Success Criteria
- `cosf(3*pi/2)` = `0x1.99bc5cp-27` (bitwise match)
- `cosf(7*pi/2)` = `0x1.644588p-21` (bitwise match)
- All other `cosf` tests continue to pass
