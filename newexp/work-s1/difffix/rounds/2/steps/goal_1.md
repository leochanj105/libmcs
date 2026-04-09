# Goal 1: Fix __ctans infinite loop (TIMEOUT)

## Function
`__ctans` — Taylor series for cosh(2y) - cos(2x), used by `ctan`

## Source Files
- **C source**: `/home/leochanj/Desktop/libmcs/libm/complexd/ctand.c` (lines 44–85)
- **Rust source**: `/home/leochanj/Desktop/libmcs/newexp/rust-s1/src/complexd.rs` (lines 52–94)

## Problem
FAULT — TIMEOUT (infinite loop).

The C code uses `do { ... } while (fabs(t / d) > MACHEP)`. When `d` is 0.0 (e.g., input z = 0+0i), `t / d` produces NaN. In C, `fabs(NaN) > MACHEP` evaluates to **false**, so the loop exits.

The Rust code uses `loop { ... if (t / d).abs() <= MACHEP { break; } }`. `NaN.abs() <= MACHEP` is **false**, so the loop never breaks — causing a timeout.

## What Needs to Change
Change the Rust loop termination condition to match C's `do-while` NaN semantics. Replace:
```rust
if (t / d).abs() <= MACHEP {
    break;
}
```
with:
```rust
if !((t / d).abs() > MACHEP) {
    break;
}
```

This ensures that NaN (from 0.0/0.0) causes the loop to exit, matching C behavior.

## Success Criteria
- `bridge_ctans` no longer times out
- `__ctans` tests that were MISSING now appear in Rust output
- All `__ctans` / `ctan` test outputs are bitwise identical to C (verified with %a hex float format)
