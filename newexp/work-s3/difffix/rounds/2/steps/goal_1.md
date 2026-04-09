# Goal 1: Fix cproj / cprojf — wrong imaginary part for infinity inputs

## Function
- `cproj` (complex double)
- `cprojf` (complex float)

## Source Files
- C: `/home/leochanj/Desktop/libmcs/libm/complexd/cprojd.c` (cproj)
- C: `/home/leochanj/Desktop/libmcs/libm/complexf/cprojf.c` (cprojf)
- Rust: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexd.rs` line ~122 (cprojd)
- Rust: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexf.rs` line ~120 (cprojf)

## Problem
MISMATCH: When either component is infinity, cproj should return (inf, copysign(0.0, imag)).
Instead, Rust returns (inf, inf) — it is not zeroing the imaginary part.

Failing tests (cproj):
- cproj (inf,-inf): C returns (inf,-0x0p+0), Rust returns (inf,inf)
- cproj (nan,inf): C returns (inf,0x0p+0), Rust returns (inf,inf)

Failing tests (cprojf):
- cprojf (inf,-inf): C returns (inf,-0x0p+0), Rust returns (inf,inf)
- cprojf (nan,inf): C returns (inf,0x0p+0), Rust returns (inf,inf)

## What Needs to Change
The Rust cproj/cprojf implementations must set the imaginary part to copysign(0.0, imag(z))
when either real or imaginary part is infinite, matching the C behavior per IEEE 754.

## Success Criteria
- cproj (inf,-inf) = (inf,-0x0p+0) — bitwise exact
- cproj (nan,inf) = (inf,0x0p+0) — bitwise exact
- cprojf (inf,-inf) = (inf,-0x0p+0) — bitwise exact
- cprojf (nan,inf) = (inf,0x0p+0) — bitwise exact
