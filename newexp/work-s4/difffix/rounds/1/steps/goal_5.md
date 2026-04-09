# Goal 5: Fix exp2 — calls stdlib powf instead of library's powd

## Function
`exp2` (double-precision base-2 exponential)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/exp2d.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s4/src/mathd.rs` (line 2119, function `exp2d`)

## Failure Type
MISMATCH — wrong output

## Symptom
```
C:    exp2 0x1.8p+1 = 0x1p+3
Rust: exp2 0x1.8p+1 = 0x1.fffee746db0fcp+5
```
Input `0x1.8p+1` = 3.0. Expected `2^3 = 8.0` (`0x1p+3`), Rust gives ~63.999.

## Root Cause
The C implementation delegates to its own `pow`:
```c
double exp2(double x) { return pow(2.0, x); }
```

The Rust code calls Rust's standard library `f64::powf` instead of the library's own `powd`:
```rust
pub fn exp2d(x: f64) -> f64 {
    (2.0f64).powf(x)  // BUG: calls stdlib, not library's powd
}
```

This means `exp2d` doesn't go through the library's `powd` function, which would produce correct results once Goal 6 is fixed. Additionally, even the stdlib `powf` is producing grossly wrong results here, suggesting an ABI or linking issue.

## Fix
In `mathd.rs` at line 2119, change:
```rust
pub fn exp2d(x: f64) -> f64 {
    (2.0f64).powf(x)
}
```
to:
```rust
pub fn exp2d(x: f64) -> f64 {
    powd(2.0, x)
}
```

**Note:** This fix depends on Goal 6 (powd fix) being applied first. Once powd is correct, exp2d will produce correct results.

## Success Criteria
- `exp2 0x1.8p+1` produces `0x1p+3` (bitwise match with C, i.e. exactly 8.0)
- All other exp2 tests continue to pass
