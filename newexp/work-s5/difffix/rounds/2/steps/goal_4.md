# Goal 4: Fix log10 — 1-bit rounding error

## Function
`log10` (double precision, `log10d` in Rust)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/log10d.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s5/src/mathd.rs` (fn `log10d` around line 2946)

## Problem
MISMATCH — 1 test case with a 1-bit difference in the last digit:
- Input: `5.0`
- C output: `0x1.65df657b04301p-1`
- Rust output: `0x1.65df657b043p-1`

The last hex digit differs: C has `01` while Rust has `0` (trailing zero omitted, but the value `0x1.65df657b043p-1` vs `0x1.65df657b04301p-1` means Rust is off by 1 ULP in the low bits).

## What Needs to Change
Compare the Rust `log10d` implementation against the C source. Check constants, polynomial coefficients, and the final computation steps. A coefficient or constant may have been truncated during transpilation.

## Success Criteria
- `log10 5.0` returns `0x1.65df657b04301p-1` (bitwise match with C)
- All log10 test cases match C output exactly
