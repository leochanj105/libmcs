# Goal 2: Fix __ctansf infinite loop (TIMEOUT)

## Function
`__ctansf` — Taylor series for cosh(2y) - cos(2x), float version, used by `ctanf`

## Source Files
- **C source**: `/home/leochanj/Desktop/libmcs/libm/complexf/ctanf.c` (lines 9–49)
- **Rust source**: `/home/leochanj/Desktop/libmcs/newexp/rust-s1/src/complexf.rs` (lines 50–92)

## Problem
FAULT — TIMEOUT (infinite loop).

Same root cause as Goal 1 but for the float version. The C code uses `do { ... } while (fabsf(t / d) > MACHEPF)`. When `d` is 0.0, `t / d` is NaN, and `fabsf(NaN) > MACHEPF` is false in C — loop exits.

Rust uses `if (t / d).abs() <= MACHEPF { break; }`. `NaN <= MACHEPF` is false — loop never breaks.

## What Needs to Change
Change the Rust loop termination condition to match C's NaN semantics. Replace:
```rust
if (t / d).abs() <= MACHEPF {
    break;
}
```
with:
```rust
if !((t / d).abs() > MACHEPF) {
    break;
}
```

## Success Criteria
- `bridge_ctansf` no longer times out
- `__ctansf` tests that were MISSING now appear in Rust output
- All `__ctansf` / `ctanf` test outputs are bitwise identical to C (verified with %a hex float format)
