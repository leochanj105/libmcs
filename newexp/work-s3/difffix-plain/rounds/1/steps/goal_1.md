# Goal 1: Fix __sin_pif infinite loop (TIMEOUT)

## Function
`__sin_pif` (internal float helper)

## Source files
- C: /home/leochanj/Desktop/libmcs/libm/mathf/internal/gammaf.c
- Rust: /home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathf.rs

## Problem
The Rust `__sin_pif` function enters an infinite loop or infinite recursion. The test binary hangs after producing output for input 0.25. This also causes `__ctans` and `__ctansf` tests to be MISSING (never reached).

## What needs to change
Compare the Rust `__sin_pif` implementation against the C original in `gammaf.c`. Look for:
- Loops that don't terminate (while conditions that never become false)
- Recursive calls without proper base cases
- Off-by-one in loop bounds or reduction logic

## Success Criteria
- `__sin_pif` completes for all test inputs without hanging
- All `bridge___ctans` and `bridge___ctansf` tests produce output (no longer MISSING)
- Output values match C reference bitwise
