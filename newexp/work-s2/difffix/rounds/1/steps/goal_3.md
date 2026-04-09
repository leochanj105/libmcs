# Goal 3: Fix acosh missing sqrt in 1<x<=2 branch

## Function
acosh (acoshd)

## Source files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/acoshd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s2/src/mathd.rs` (lines 1385-1414)

## Problem
In the 1 < x <= 2 branch (else clause, line 1411-1412), the Rust code is missing a `sqrt()` call.

C code (acoshd.c:91-92):
```c
t = x - one;
return log1p(t + sqrt(2.0 * t + t * t));
```

Rust code (mathd.rs:1411-1412):
```rust
let t = x - ONE;
return (2.0 * t + t * t).ln_1p();  // MISSING sqrt!
```

The Rust computes `ln(1 + 2t + t²) = ln((1+t)²) = 2·ln(1+t)` which for x=2 gives 2·ln(2) = ln(4).
The correct formula is `ln(1 + t + √(2t + t²))`.

## Failing test
- `acosh 0x1p+1` → C: 0x1.5124271980434p+0, Rust: 0x1.62e42fefa39efp+0

## What needs to change
Fix `mathd.rs:1412` to include the sqrt:
```rust
return (t + (2.0 * t + t * t).sqrt()).ln_1p();
```
Use the Rust `sqrt()` method (which maps to the transpiled `sqrtd`), matching the C formula.

## Success Criteria
`acosh(2.0)` returns `0x1.5124271980434p+0`, bitwise matching the C output.
