# Goal 1: Fix exp2 — wrong output for normal input

## Function
`exp2` (double precision, `exp2d` in Rust)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/exp2d.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s5/src/mathd.rs` (fn `exp2d` around line 2119)

## Problem
MISMATCH — Rust returns a completely wrong value for a normal input:
- Input: `0x1.8p+1` (3.0)
- C output: `0x1p+3` (8.0) — correct: 2^3 = 8
- Rust output: `0x1.fffee746db0fcp+5` (~63.99) — wildly incorrect

This is a fundamental computation error, not a rounding issue.

## What Needs to Change
Compare the Rust `exp2d` implementation against the C `exp2d.c` source. The algorithm or polynomial coefficients may have been incorrectly transcribed during transpilation. Check the reduction step, polynomial evaluation, and reconstruction.

## Success Criteria
- `exp2 0x1.8p+1` returns `0x1p+3` (bitwise match with C)
- All exp2 test cases match C output exactly
