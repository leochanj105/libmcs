# Goal 1: Fix nexttowardf ABI mismatch

## Function
`nexttowardf`

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathf/nexttowardf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s2/src/mathf.rs` (line ~2434)
- Rust export: `/home/leochanj/Desktop/libmcs/newexp/rust-s2/src/lib.rs` (line 194)

## Problem
**Wrong output.** `nexttowardf(0x1p+0, 0x8p-2)` should return `0x1.000002p+0` (step toward 2.0) but Rust returns `0x1.fffffep-1` (step away).

**Root cause:** ABI mismatch. The C function signature is `float nexttowardf(float x, long double y)`. On x86-64 Linux, `long double` is 80-bit and passed on the stack. The Rust export declares `y: f64` (64-bit, passed in XMM1), so Rust reads the wrong value for y.

This is the same bug that `nexttoward` (double version) had. It was fixed in round 2 by commenting out the `nexttoward` export in `lib.rs` (lines 99-101), letting the C implementation handle it.

## What Needs to Change
Remove or comment out the `nexttowardf` export in `lib.rs` line 194, matching the approach used for `nexttoward`. The C implementation will be used as the fallback.

## Success Criteria
- `nexttowardf(0x1p+0, 0x8p-2)` returns `0x1.000002p+0` (bitwise match with C)
- No `nexttowardf` symbol exported from the Rust library
