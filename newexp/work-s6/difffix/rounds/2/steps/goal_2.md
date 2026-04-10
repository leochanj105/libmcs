# Goal 2: Fix exp2 — wrong result for exp2(3.0)

## Function
`exp2` (double precision, aliased from `exp2d`)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/exp2d.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s6/src/mathd.rs` (line ~2119)

## Problem
MISMATCH — 1 test failure.

`exp2(3.0)` should return `8.0` (`0x1p+3`) but the Rust version returns `~63.99` (`0x1.fffee746db0fcp+5`). This is a major computational error, not a precision issue — the result is completely wrong.

Example:
- C:    `exp2 0x1.8p+1 = 0x1p+3`  (i.e., exp2(3.0) = 8.0)
- Rust: `exp2 0x1.8p+1 = 0x1.fffee746db0fcp+5`  (≈63.99)

## What Needs to Change
The core algorithm in `exp2d` has a fundamental bug. Compare against the C source to find where the computation diverges. Likely a coefficient error, range reduction bug, or incorrect scaling step.

## Success Criteria
- `exp2(3.0)` returns exactly `0x1p+3` (8.0).
- Bitwise-exact match with C output for all exp2 test cases.
