# Goal 3: Fix cosf and __cosf — wrong output for large arguments

## Functions
`cosf`, `__cosf`

## Source Files
- C source (cosf): `/home/leochanj/Desktop/libmcs/libm/mathf/cosf.c`
- C source (__cosf kernel): `/home/leochanj/Desktop/libmcs/libm/mathf/internal/trigf.c`
- Rust source (cosf): `/home/leochanj/Desktop/libmcs/newexp/rust-s5/src/mathf.rs` (fn `cosf` at line 1341)
- Rust source (__cosf kernel): `/home/leochanj/Desktop/libmcs/newexp/rust-s5/src/mathf.rs` (fn `cosf_kern` at line 479)

## Problem
MISMATCH — both `cosf` and `__cosf` produce wrong results:
- `__cosf 0x1p+0 0x0p+0`: C=`0x1.14a282p-1`, Rust=`0x1.14a284p-1` (1 ULP off in kernel)
- `cosf 3*pi/2`: C=`0x1.99bc5cp-27`, Rust=`0x1.1p-15` (grossly wrong — likely argument reduction issue)
- `cosf 7*pi/2`: C=`0x1.644588p-21`, Rust=`0x1.3fff8cp-14` (grossly wrong)

The kernel has a small error (1 ULP). The outer `cosf` has large errors for multiples of pi/2, suggesting broken argument reduction (`__rem_pio2f`).

## What Needs to Change
1. Compare the `cosf_kern` polynomial coefficients with the C `__cosf` kernel
2. Compare `cosf` argument reduction logic and `__rem_pio2f` / `__rem_pio2f_internal` with the C versions

## Success Criteria
- `__cosf 0x1p+0 0x0p+0` returns `0x1.14a282p-1`
- `cosf 3*pi/2` returns `0x1.99bc5cp-27`
- `cosf 7*pi/2` returns `0x1.644588p-21`
- All cosf/__cosf test cases match C output exactly
