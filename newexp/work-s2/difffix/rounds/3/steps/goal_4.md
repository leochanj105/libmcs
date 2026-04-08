# Goal 4: Implement __fpclassifyd

## Function
`__fpclassifyd`

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/internal/fpclassifyd.c`
- Rust source: not implemented

## Problem
**Not implemented.** `__fpclassifyd` classifies a double-precision float (normal, subnormal, zero, infinite, NaN). The Rust test binary falls back to the C version. It needs a Rust implementation for completeness.

## What Needs to Change
Transpile `__fpclassifyd` from `/home/leochanj/Desktop/libmcs/libm/mathd/internal/fpclassifyd.c` into the Rust mathd module. Must return the same classification constants as the C version (matching the library's own FP_* enum values, not the system's).

## Success Criteria
- `__fpclassifyd` is implemented in Rust
- Returns bitwise-identical classification values to the C implementation for all FP classes (normal, subnormal, zero, inf, NaN)
