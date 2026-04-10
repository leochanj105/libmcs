# Goal 3: Fix `acosh` algorithm

## Function
`acosh` (double-precision inverse hyperbolic cosine)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/acoshd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s6/src/mathd.rs` (around line 1385, `acoshd`)

## Problem
MISMATCH — 5 test failures. Results are completely wrong, not just ULP errors.

```
C:    acosh 2.0 = 0x1.5124271980434p+0
Rust: acosh 2.0 = 0x1.62e42fefa39efp+0

C:    acosh 1.5 = 0x1.ecc2caec5160ap-1
Rust: acosh 1.5 = 0x1.9f323ecbf984cp-1

C:    acosh 1.1 = 0x1.c636c1a882f2cp-2
Rust: acosh 1.1 = 0x1.8663f793c46ccp-3
```

The errors are large (orders of magnitude off for small inputs), indicating an algorithm or formula bug — not a precision issue.

## What Needs to Change
Compare the Rust `acoshd` implementation against the C source step by step. The formula, branch conditions, or helper function calls are likely incorrect. Common issues: wrong formula for the near-1 branch, incorrect use of `log` vs `log1p`, or wrong threshold values.

## Success Criteria
- `acosh(2.0)` = `0x1.5124271980434p+0` (bitwise match)
- `acosh(1.5)` = `0x1.ecc2caec5160ap-1` (bitwise match)
- `acosh(1.1)` = `0x1.c636c1a882f2cp-2` (bitwise match)
- All 5 failing tests and all existing passing tests produce bitwise-exact matches
