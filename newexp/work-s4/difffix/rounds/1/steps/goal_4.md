# Goal 4: Fix acosh — missing sqrt and addition in else branch

## Function
`acosh` (double-precision hyperbolic arc cosine)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/acoshd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s4/src/mathd.rs` (line 1385, function `acoshd`)

## Failure Type
MISMATCH — wrong output

## Symptom
```
C:    acosh 0x1p+1 = 0x1.5124271980434p+0
Rust: acosh 0x1p+1 = 0x1.62e42fefa39efp+0
```
Input `0x1p+1` = 2.0. The correct result is ~1.317, Rust gives ~1.387.

## Root Cause
For `1 < x <= 2` (the else branch), the C code computes:
```c
t = x - one;
return log1p(t + sqrt(2.0 * t + t * t));
```

But the Rust code is missing both the `sqrt` call and the `t +` term:
```rust
let t = x - ONE;
return (2.0 * t + t * t).ln_1p();  // BUG: missing sqrt() and t +
```

This computes `log1p(2t + t^2)` instead of `log1p(t + sqrt(2t + t^2))`.

## Fix
In `mathd.rs` at line 1412, change:
```rust
return (2.0 * t + t * t).ln_1p();
```
to:
```rust
return (t + (2.0 * t + t * t).sqrt()).ln_1p();
```

## Success Criteria
- `acosh 0x1p+1` produces `0x1.5124271980434p+0` (bitwise match with C)
- All other acosh tests continue to pass
