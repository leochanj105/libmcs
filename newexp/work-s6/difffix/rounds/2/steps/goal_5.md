# Goal 5: Fix log10 — last-bit precision error

## Function
`log10` (double precision, aliased from `log10d`)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/log10d.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s6/src/mathd.rs` (line ~2946)

## Problem
MISMATCH — 1 test failure.

`log10(5.0)` differs in the last bit of the mantissa.

Example:
- C:    `log10 5.0 = 0x1.65df657b04301p-1`
- Rust: `log10 5.0 = 0x1.65df657b043p-1`

The difference is `0x1.65df657b04301p-1` vs `0x1.65df657b04300p-1` — off by 1 ULP.

## What Needs to Change
Compare the Rust log10d implementation against the C log10d.c. Likely a constant is slightly off, or a compensation term (hi/lo splitting) is missing or incorrectly ordered. This is a 1-ULP error suggesting a minor coefficient or rounding issue.

## Success Criteria
- `log10(5.0)` returns exactly `0x1.65df657b04301p-1`.
- Bitwise-exact match with C output for all log10 test cases.
