# Goal 3: Fix logb — subnormal exponent off by 1

## Function
`logb` (calls `mathd::logbd`)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/logbd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s6/src/mathd.rs` (`logbd` at line 3103)

## Problem
MISMATCH — 2 test failures (subnormal inputs).

```
C:    logb 0x1p-1074 = -0x1.0c8p+10      (-1074)
Rust: logb 0x1p-1074 = -0x1.0ccp+10      (-1075)
C:    logb 0x1p-1073 = -0x1.0c4p+10      (-1073)
Rust: logb 0x1p-1073 = -0x1.0c8p+10      (-1074)
```

Rust `logb` is off by exactly 1 (too negative) for denormal inputs. The C
implementation normalizes the subnormal by counting leading zeros and computes
`-1022 - (leading_zero_count - 11)` (or equivalent), where `11` accounts for
the implicit-bit position in the significand. Rust likely uses a constant of
`12` (or starts the count from a different bit position), producing an
exponent one too low.

## What Needs to Change
In `logbd`'s subnormal branch in `/home/leochanj/Desktop/libmcs/newexp/rust-s6/src/mathd.rs`,
verify the bit-count constants against `/home/leochanj/Desktop/libmcs/libm/mathd/logbd.c`.
Fix the off-by-one in the leading-zero subtraction so that
`logb(0x1p-1074) == -1074` and `logb(0x1p-1073) == -1073`.

## Success Criteria
- `logb(0x1p-1074)` returns exactly `-1074.0` (encoded as `-0x1.0c8p+10`).
- `logb(0x1p-1073)` returns exactly `-1073.0` (encoded as `-0x1.0c4p+10`).
- All 2 logb mismatches resolve to bitwise-exact match with C output.
- No regressions on normal inputs.
