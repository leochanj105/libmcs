# Goal 2: Fix cpowf — wrong imaginary part (depends on sinf fix)

## Function
- `cpowf` (complex float)

## Source Files
- C: `/home/leochanj/Desktop/libmcs/libm/complexf/cpowf.c`
- Rust: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexf.rs`

## Problem
MISMATCH: cpowf((0,1),(2,0)) should return (-1, -0x1.777a5cp-24) but Rust returns (-1, -0x1.6bff7ap-16).

The imaginary part error (-0x1.6bff7ap-16 vs -0x1.777a5cp-24) is identical to the sinf error.
cpowf internally computes exp(w * log(z)), which involves sin/cos for the imaginary part.
This failure is almost certainly caused by the same sinf/__rem_pio2f bug.

## What Needs to Change
This will likely be fixed automatically once sinf (Goal 1) is fixed. After fixing sinf,
re-test cpowf. If it still fails, compare the Rust cpowf implementation against the C version
for any additional divergences.

## Success Criteria
- cpowf (0x0p+0,0x1p+0),(0x1p+1,0x0p+0) = -0x1p+0,-0x1.777a5cp-24 — bitwise exact match with C
