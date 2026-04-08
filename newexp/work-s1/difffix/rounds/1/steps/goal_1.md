# Goal 1: Fix acosh mismatch (wrong output)

## Function
`acosh` (double precision)

## Source Files
- **C source**: `/home/leochanj/Desktop/libmcs/libm/mathd/acoshd.c`
- **Rust source**: `/home/leochanj/Desktop/libmcs/newexp/rust-s1/src/mathd.rs` (line 1385, `acoshd`)

## Problem
The Rust `acoshd` function produces incorrect results for inputs in the range `1 < x <= 2`.

Mismatched outputs:
- `acosh(2.0)`: C = `0x1.5124271980434p+0`, Rust = `0x1.62e42fefa39efp+0`
- `acosh(1.5)`: C = `0x1.ecc2caec5160ap-1`, Rust = `0x1.9f323ecbf984cp-1`

## Root Cause
Transpilation bug in the `else` branch (for `1 < x < 2`).

**C code** (correct):
```c
t = x - one;
return log1p(t + sqrt(2.0 * t + t * t));
```

**Rust code** (incorrect):
```rust
let t = x - ONE;
return (2.0 * t + t * t).ln_1p();
```

The Rust code is missing `sqrt()` around `(2.0 * t + t * t)` and the `t +` addition before `ln_1p()`. It computes `log1p(2t + t²)` instead of the correct `log1p(t + sqrt(2t + t²))`.

## Fix Required
Change line 1412 in `mathd.rs` from:
```rust
return (2.0 * t + t * t).ln_1p();
```
to:
```rust
return (t + (2.0 * t + t * t).sqrt()).ln_1p();
```

## Success Criteria
- `acosh(2.0)` returns `0x1.5124271980434p+0` (bitwise match with C)
- `acosh(1.5)` returns `0x1.ecc2caec5160ap-1` (bitwise match with C)
- All 5 acosh test cases pass with bitwise-exact output matching C
