# Goal 1: Fix acosh mismatch

## Function
`acosh` (double precision, implemented as `acoshd` in Rust)

## Source Files
- **C source:** `/home/leochanj/Desktop/libmcs/libm/mathd/acoshd.c`
- **Rust source:** `/home/leochanj/Desktop/libmcs/newexp/rust-s4/src/mathd.rs` (line 1412)

## Problem
**MISMATCH** — Rust produces wrong output for `acosh(2.0)`.

- Input: `0x1p+1` (2.0)
- Expected (C): `0x1.5124271980434p+0`
- Got (Rust): `0x1.62e42fefa39efp+0`

## Root Cause
In the `1 < x < 2` branch (the final `else` clause), the Rust code reads:
```rust
return log1pd(2.0 * t + t * t);
```

But the C code reads:
```c
return log1p(t + sqrt(2.0 * t + t * t));
```

The Rust translation is missing:
1. The `sqrt()` call around `2.0 * t + t * t`
2. The `t +` term before the `sqrt` result

## Required Fix
Change line 1412 in `mathd.rs` from:
```rust
return log1pd(2.0 * t + t * t);
```
to:
```rust
return log1pd(t + sqrtd(2.0 * t + t * t));
```

## Success Criteria
- `acosh(0x1p+1)` must return `0x1.5124271980434p+0` (bitwise exact match with C)
- All 441 differential tests pass with zero mismatches
- No compile errors or runtime panics introduced
