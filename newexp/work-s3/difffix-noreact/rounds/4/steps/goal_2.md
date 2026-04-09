# Goal 2: Fix cacosf NaN sign handling

## Function
`cacosf` (complex arc cosine, float precision)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/complexf/cacosf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexf.rs` (fn `cacosf`, ~line 272)

## Problem
**Wrong output.** When input is `(nan, nan)`, C returns `(-nan, nan)` but Rust returns `(nan, nan)`. The real part should be negative NaN (`-nan`), meaning the sign bit of the NaN must be set. Same root cause as cacos (goal_1) but in the float variant.

## What Needs to Change
The Rust `cacosf` implementation must preserve the sign of NaN in the real part of the result to match the C implementation. This is the float-precision analog of goal_1. Check how the C code computes the real part and ensure the Rust code applies the same arithmetic that sets the NaN sign bit.

## Success Criteria
- `cacosf(nan, nan)` returns `(-nan, nan)` — real part has sign bit set
- All other cacosf tests continue to pass
- Output is bitwise exact with C
