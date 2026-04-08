# Goal 5: Fix cpow

## Function
`cpow`

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/complexd/cpowd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s1/src/complexd.rs` (line 344, `pub fn cpowd`)

## Problem: MISMATCH
Input: `cpow(2+0i, 3+0i)`
- C output:    `cpow(0x1p+1+0x0p+0i ^ 0x1.8p+1+0x0p+0i) = 0x1p+3+0x0p+0i` (8+0i)
- Rust output: `cpow(0x1p+1+0x0p+0i ^ 0x1.8p+1+0x0p+0i) = 0x1.fffee746db0fcp+5+0x0p+0i` (~64+0i)

Identical error pattern to `pow` (goal 4): result is ~64 instead of 8. Since the imaginary parts are zero, this reduces to real `pow(2,3)`.

## Related Failures
Depends on `pow` (goal 4). cpow likely calls pow or cexp(y*clog(x)) internally. If cpow uses real pow for the real-only case, fixing pow fixes this. Otherwise, the same log/exp bug exists in the complex path.

## What Needs to Change
1. Check if cpow delegates to real pow for real-only inputs
2. If it uses `cexp(y * clog(x))`, check the clog and cexp implementations
3. The error magnitude matches pow exactly, so likely shares the same root cause

## Success Criteria
`cpow(0x1p+1+0x0p+0i, 0x1.8p+1+0x0p+0i)` must return exactly `0x1p+3+0x0p+0i` (8+0i, bitwise match with C).
