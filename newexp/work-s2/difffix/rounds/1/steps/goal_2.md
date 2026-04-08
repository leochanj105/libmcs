# Goal 2: Fix acoshd mismatch

## Function
`acoshd` (double-precision acosh)

## C Source
/home/leochanj/Desktop/libmcs/libm/mathd/acoshd.c (line 90-92)

## Rust Source
/home/leochanj/Desktop/libmcs/newexp/rust-s2/src/mathd.rs — `pub fn acoshd` (line ~1385)

## Problem
`acosh(0x1p+1)` returns `0x1.62e42fefa39efp+0` (Rust) but should return
`0x1.5124271980434p+0` (C). The Rust value is `ln(4)`, the correct value is
`ln(2 + sqrt(3))`.

Bug is in the `1 < x <= 2` branch (the else clause). The Rust code has:

```rust
let t = x - ONE;
return (2.0 * t + t * t).ln_1p();    // WRONG
```

The C code has:

```c
t = x - one;
return log1p(t + sqrt(2.0 * t + t * t));  // CORRECT
```

The Rust code is missing `t + sqrt(...)`. It computes `log1p(2t + t^2)` instead
of `log1p(t + sqrt(2t + t^2))`.

## What Needs to Change
Replace line ~1412 in mathd.rs:
```rust
return (2.0 * t + t * t).ln_1p();
```
with:
```rust
return (t + (2.0 * t + t * t).sqrt()).ln_1p();
```

## Success Criteria
- `acosh(0x1p+0) = 0x0p+0`
- `acosh(0x1p+1) = 0x1.5124271980434p+0`
- `acosh(0x1.4p+3) = 0x1.7f21ed1ce05d4p+1`
- All values bitwise-exact with C output
