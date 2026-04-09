# Compact Divergences — Round 2

## Summary
- Tests passed: 440 / 441
- Tests failed: 1
- Mismatched functions: acosh

## Divergences

### 1. acosh — MISMATCH
- **Input:** `0x1p+1` (2.0)
- **C output:** `0x1.5124271980434p+0`
- **Rust output:** `0x1.62e42fefa39efp+0`
- **Root cause:** In the `1 < x < 2` branch (else clause), the Rust code is `log1pd(2.0 * t + t * t)` but should be `log1pd(t + sqrtd(2.0 * t + t * t))`. Missing `sqrt` call and missing `t +` before it.
- **C source:** `/home/leochanj/Desktop/libmcs/libm/mathd/acoshd.c:92` — `return log1p(t + sqrt(2.0 * t + t * t));`
- **Rust source:** `/home/leochanj/Desktop/libmcs/newexp/rust-s4/src/mathd.rs:1412` — `return log1pd(2.0 * t + t * t);`
