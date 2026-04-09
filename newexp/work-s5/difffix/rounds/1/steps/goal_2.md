# Goal 2: Fix acosh — incorrect computation

## Function
`acosh` (double precision)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/acoshd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s5/src/mathd.rs` (fn `acoshd` at line 1385)

## Problem
MISMATCH — Rust produces significantly wrong values for acosh, indicating an algorithmic error (not just a rounding issue):
- `acosh(2.0)`: C=`0x1.5124271980434p+0`, Rust=`0x1.62e42fefa39efp+0`
- `acosh(1.5)`: C=`0x1.ecc2caec5160ap-1`, Rust=`0x1.9f323ecbf984cp-1`
- `acosh(1.1)`: C=`0x1.c636c1a882f2cp-2`, Rust=`0x1.8663f793c46ccp-3`

The differences are large (not ULP-level), suggesting wrong formula or wrong branch logic.

## What Needs to Change
Compare the C `acoshd` implementation against the Rust `acoshd` function. Look for:
- Wrong formula (e.g., using `log(x + sqrt(x*x-1))` vs the C implementation's specific algorithm)
- Wrong branch thresholds
- Missing or incorrect special-case handling

## Success Criteria
- All 5 `acosh` test cases produce bitwise-exact matches with C output
