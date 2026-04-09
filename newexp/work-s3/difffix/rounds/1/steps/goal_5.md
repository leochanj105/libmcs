# Goal 5: Fix cpowf — wrong imaginary part (likely sinf dependency)

## Function
`cpowf` (complex float power)

## Source files
- C: /home/leochanj/Desktop/libmcs/libm/complexf/cpowf.c
- Rust: /home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexf.rs

## Problem
cpowf((0+1i), (2+0i)) imaginary part: -0x1.6bff7ap-16 (Rust) vs -0x1.777a5cp-24 (C)

The wrong imaginary value (-0x1.6bff7ap-16) is identical to the wrong sinf result in Goal 4. cpowf likely calls sinf internally (via cexpf or direct computation), so fixing sinf should fix this.

## What needs to change
1. Fix sinf first (Goal 4) — this should resolve the cpowf mismatch
2. If mismatch persists after sinf fix, compare cpowf implementation against C original

## Success Criteria
- `cpowf (0x0p+0,0x1p+0),(0x1p+1,0x0p+0)` = `-0x1p+0,-0x1.777a5cp-24` (bitwise exact)
