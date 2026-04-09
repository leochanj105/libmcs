# Goal 4: Fix ilogb / ilogbf — wrong return for zero and subnormals

## Function
- `ilogb` (double)
- `ilogbf` (float)

## Source Files
- C: `/home/leochanj/Desktop/libmcs/libm/mathd/ilogbd.c` (ilogb)
- C: `/home/leochanj/Desktop/libmcs/libm/mathf/ilogbf.c` (ilogbf)
- Rust: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathd.rs` line ~2753 (ilogbd)
- Rust: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathf.rs` line ~1971 (ilogbf)

## Problem
MISMATCH: ilogb returns wrong values for zero and smallest subnormal.

Failing tests (ilogb):
- ilogb(0x0p+0): C returns -2147483647 (INT_MAX negated / FP_ILOGB0), Rust returns -2147483648 (INT_MIN)
- ilogb(-0x0p+0): C returns -2147483647, Rust returns -2147483648
- ilogb(0x0.0000000000001p-1022): C returns -1074, Rust returns -1075

Failing tests (ilogbf):
- ilogbf(0x0p+0): C returns -2147483647, Rust returns -2147483648

## What Needs to Change
The C library defines FP_ILOGB0 as -2147483647 (INT_MAX) not -2147483648 (INT_MIN).
The Rust code likely uses i32::MIN instead of the library's FP_ILOGB0 constant.
Also, the subnormal exponent calculation for ilogb is off by one.

## Success Criteria
- ilogb(0x0p+0) = -2147483647 — bitwise exact
- ilogb(-0x0p+0) = -2147483647 — bitwise exact
- ilogb(0x0.0000000000001p-1022) = -1074 — bitwise exact
- ilogbf(0x0p+0) = -2147483647 — bitwise exact
