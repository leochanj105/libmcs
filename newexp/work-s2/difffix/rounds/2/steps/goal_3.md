# Goal 3: Fix exp2 computation

## Function
`exp2` (delegates to `exp2d`)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/exp2d.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s2/src/mathd.rs` (line ~2119)

## Problem
**Wrong output.** `exp2(10.0)` should return `1024.0` (`0x1p+10`) but Rust returns `0x1.b2d809254afbcp+11` (~3494.85). The result is completely wrong, suggesting an algorithm-level bug in the Rust transpilation — possibly a wrong constant, incorrect table lookup, or broken polynomial evaluation.

Note: `pow(2.0, 10.0)` shows the same wrong result, suggesting pow may delegate to exp2 or they share a broken code path.

## What Needs to Change
Compare the Rust `exp2d` implementation against the C `exp2d.c` line by line. Identify the transpilation error (wrong constant, sign error, missing step, etc.) and fix it to match C behavior exactly.

## Success Criteria
- `exp2(0x1.4p+3)` returns `0x1p+10` (bitwise match with C)
