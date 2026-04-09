# Goal 4: Fix pow — powd implementation produces wrong results

## Function
`pow` (implemented as `powd`)

## Source Files
- **C source**: `/home/leochanj/Desktop/libmcs/libm/mathd/powd.c`
- **Rust source**: `/home/leochanj/Desktop/libmcs/newexp/rust-s4/src/mathd.rs:3504`

## Problem
The Rust `powd(x, y)` implementation produces incorrect results. For the test case `pow(2.0, 10.0)`, it returns `0x1.b2d809254afbcp+11` (~3524) instead of the correct `0x1p+10` (1024.0). This is a large numerical error indicating a bug in the core computation, not just a rounding difference.

The C `pow` implementation is a complex ~200-line function. The Rust transpilation likely has an error in the bit manipulation, constant values, or arithmetic logic.

## Failing Tests
- `pow(0x1p+1, 0x1.4p+3)` i.e. `pow(2.0, 10.0)`: C returns `0x1p+10` (1024.0), Rust returns `0x1.b2d809254afbcp+11`

## What Needs to Change
In `/home/leochanj/Desktop/libmcs/newexp/rust-s4/src/mathd.rs`, function `powd` starting at line 3504:
1. Carefully compare the Rust `powd` implementation against the C `pow` in `powd.c` line by line
2. Check all bit manipulation operations (EXTRACT_WORDS equivalents, SET_HIGH_WORD equivalents)
3. Check all constant values match the C source exactly
4. Check signed vs unsigned integer comparisons
5. Check that internal function calls (e.g., `sqrtd`, `logd`) use transpiled versions, not std
6. Fix all discrepancies found

## Success Criteria
- `pow(0x1p+1, 0x1.4p+3)` returns `0x1p+10` (bitwise match with C)
- All other pow test cases continue to pass
- After this fix, Goal 3 (exp2) should also produce correct results
