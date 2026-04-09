# Goal 1: Fix __ctans / __ctansf — MISSING output

## Function
- `__ctans` (complex double)
- `__ctansf` (complex float)

## Source Files
- C: `/home/leochanj/Desktop/libmcs/libm/complexd/ctand.c` (__ctans)
- C: `/home/leochanj/Desktop/libmcs/libm/complexf/ctanf.c` (__ctansf)
- Rust: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexd.rs` (__ctans)
- Rust: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexf.rs` (__ctansf)

## Problem
MISSING: Rust produced no output for 4 __ctans tests and 4 __ctansf tests.
The bridge functions `bridge___ctans` and `bridge___ctansf` are not producing output,
meaning the functions are either not exported, not called correctly, or crash.

## What Needs to Change
Ensure the Rust `__ctans` and `__ctansf` functions are properly exported via
bridge functions and produce output for all test inputs. Check that the function
signatures match the C versions and that the bridge correctly marshals complex
number arguments and return values.

## Success Criteria
- All 4 __ctans test cases produce output matching C bitwise exactly
- All 4 __ctansf test cases produce output matching C bitwise exactly
- No crashes or missing output
