# Goal 3: Fix log1pf — wrong result for log1pf(-1.0)

## Function
- `log1pf` (float)

## Source Files
- C: `/home/leochanj/Desktop/libmcs/libm/mathf/log1pf.c`
- Rust: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathf.rs`

## Problem
MISMATCH: log1pf(-1.0) should return -inf but Rust returns -0x1p+1 (i.e., -2.0).

log1p(x) = ln(1+x). When x = -1.0, the argument is 0 and ln(0) = -infinity.
The Rust implementation returns -2.0 instead, which means it is not handling the
x == -1.0 special case correctly. The C code likely has an explicit check for this case.

## What Needs to Change
The Rust log1pf must handle the special case where x == -1.0 by returning -infinity,
matching the C behavior. Check if the Rust code is missing the special-case branch or
if the condition is wrong.

## Success Criteria
- log1pf -0x1p+0 = -inf — bitwise exact match with C
