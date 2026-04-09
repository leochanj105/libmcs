# Goal 1: Fix logbd subnormal exponent calculation (off-by-one)

## Function
`logbd` (double-precision `logb`)

## Source files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/logbd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s5/src/mathd.rs` (line 3103)

## Problem
**Wrong output** — Rust produces incorrect results for subnormal inputs:

```
C:    logb 0x1p-1074 = -0x1.0c8p+10   (-1074.0)
Rust: logb 0x1p-1074 = -0x1.0ccp+10   (-1075.0)
C:    logb 0x1p-1073 = -0x1.0c4p+10   (-1073.0)
Rust: logb 0x1p-1073 = -0x1.0c8p+10   (-1074.0)
```

Rust is off by -1 for subnormal inputs where `hx == 0`.

## Root cause
In the C code (line 76), `lx` is declared as `int32_t`. The loop `for (ix = -1043; lx > 0; lx <<= 1)` terminates when the sign bit is set (i.e., `lx` becomes negative as a signed integer).

In the Rust code (line 3106), `lx` is declared as `u32`. The loop `while lx > 0` does NOT terminate when the MSB is set — `0x80000000u32` is still `> 0`. It continues one more iteration until `lx` wraps to 0 via overflow, producing an extra decrement of `ix`.

## What needs to change
In `mathd.rs` at line ~3113, change the subnormal loop condition from:
```rust
while lx > 0 {
```
to:
```rust
while (lx as i32) > 0 {
```
This matches the C signed comparison semantics: the loop stops when the MSB (sign bit) is set.

## Success Criteria
- `logb(0x1p-1074)` returns `-0x1.0c8p+10` (i.e., -1074.0) — matching C output
- `logb(0x1p-1073)` returns `-0x1.0c4p+10` (i.e., -1073.0) — matching C output
- All other logb tests continue to pass
