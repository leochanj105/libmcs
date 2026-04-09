# Goal 5: Fix log1pf — completely wrong for negative inputs

## Function
`log1pf` (float precision)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathf/log1pf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s5/src/mathf.rs` (fn `log1pf` around line 2099)

## Problem
MISMATCH — 4 test cases, all involving negative inputs. The results are fundamentally wrong, not rounding errors:
1. `log1pf -1.0f`: C returns `-inf`, Rust returns `-0x1p+1` (-2.0)
2. `log1pf -2.0f`: C returns `nan`, Rust returns `-0x1p+2` (-4.0)
3. `log1pf -0.9f`: C returns `-0x1.26bb1ap+1`, Rust returns `-0x1.ccccccp+0`
4. `log1pf -0.5f`: C returns `-0x1.62e43p-1`, Rust returns `-0x1p+0` (-1.0)

Rust is not computing log(1+x) at all — it appears to be returning something like `2*x` or a simple linear function instead of the logarithm. The special cases (log(0)=-inf, log(negative)=nan) are also broken.

## What Needs to Change
Compare the Rust `log1pf` against the C source. The algorithm is likely fundamentally broken — possibly a missing branch, wrong formula, or the core computation was incorrectly transpiled. Check:
1. Special case handling for x=-1 (should return -inf) and x<-1 (should return NaN)
2. The main computation path for negative x values near -1

## Success Criteria
- `log1pf -1.0f` returns `-inf`
- `log1pf -2.0f` returns `nan`
- `log1pf -0.9f` returns `-0x1.26bb1ap+1`
- `log1pf -0.5f` returns `-0x1.62e43p-1`
- All log1pf test cases match C output exactly
