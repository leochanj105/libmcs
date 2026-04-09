# Compact Divergences — Round 1

## TIMEOUT (2 functions)
| Function | C Source | Rust Source | Issue |
|----------|----------|-------------|-------|
| __ctans | complexd/ctand.c | src/complexd.rs | TIMEOUT in bridge_ctans |
| __ctansf | complexf/ctanf.c | src/complexf.rs | TIMEOUT in bridge_ctansf |

## MISMATCH (10 functions, 11 tests)

### Group A: Float trig kernel (sinf, tanf, cexpf)
All share input `0x1.921fb6p+1` (pi as float). sinf/tanf differ by ~256x; cexpf uses sinf internally.
| Function | Input | C Output | Rust Output |
|----------|-------|----------|-------------|
| sinf | 0x1.921fb6p+1 | -0x1.777a5cp-24 | -0x1.6bff7ap-16 |
| tanf | 0x1.921fb6p+1 | 0x1.777a5cp-24 | 0x1.6bff7ap-16 |
| cexpf | 0x0p+0+0x1.921fb6p+1i | -0x1p+0+-0x1.777a5cp-24i | -0x1p+0+-0x1.6bff7ap-16i |

### Group B: pow / cpow
Both compute 2^3 incorrectly (cpow likely delegates to pow/exp/log).
| Function | Input | C Output | Rust Output |
|----------|-------|----------|-------------|
| pow | 2.0 ^ 3.0 | 0x1p+3 (8.0) | 0x1.fffee746db0fcp+5 (~63.998) |
| cpow | (2+0i) ^ (3+0i) | 0x1p+3+0x0p+0i | 0x1.fffee746db0fcp+5+0x0p+0i |

### Group C: cproj / cprojf
Both fail to zero the imaginary part when real part is inf.
| Function | Input | C Output | Rust Output |
|----------|-------|----------|-------------|
| cproj | inf+1.0i | inf+0x0p+0i | inf+0x1p+0i |
| cprojf | inf+1.0i | inf+0x0p+0i | inf+0x1p+0i |

### Group D: acosh
Two mismatches — completely wrong values.
| Function | Input | C Output | Rust Output |
|----------|-------|----------|-------------|
| acosh | 0x1p+1 (2.0) | 0x1.5124271980434p+0 | 0x1.62e42fefa39efp+0 |
| acosh | 0x1.8p+0 (1.5) | 0x1.ecc2caec5160ap-1 | 0x1.9f323ecbf984cp-1 |

### Group E: exp2
exp2(10) returns wrong value.
| Function | Input | C Output | Rust Output |
|----------|-------|----------|-------------|
| exp2 | 0x1.4p+3 (10.0) | 0x1p+10 (1024.0) | 0x1.b2d809254afbcp+11 (~3557.5) |

### Group F: log1pf
log1pf(-1.0) should be -inf, returns -2.0.
| Function | Input | C Output | Rust Output |
|----------|-------|----------|-------------|
| log1pf | -0x1p+0 (-1.0) | -inf | -0x1p+1 (-2.0) |
