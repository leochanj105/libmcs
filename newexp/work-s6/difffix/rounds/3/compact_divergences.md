# Compact Divergences — Round 3

35 mismatches across 7 functions.

| # | Function | Type | Mismatches | Summary |
|---|----------|------|------------|---------|
| 1 | exp2 | MISMATCH | 1 | exp2(3.0) returns ~63.99 instead of 8 (still broken from R2) |
| 2 | log1pf | MISMATCH | 9 | Completely wrong for negative inputs; log1pf(-1)=-2 instead of -inf |
| 3 | logb | MISMATCH | 2 | Subnormal exponent off by 1 |
| 4 | modf | MISMATCH | 1 | modf(nan) returns 0 instead of nan |
| 5 | pow | MISMATCH | 20 | Widespread errors: pow(2,10)=wrong, pow(2,1000)=wrong, etc. |
| 6 | rem_pio2 | MISMATCH | 1 | rem_pio2(inf) returns -nan instead of nan (NaN sign bit) |
| 7 | remainder | MISMATCH | 1 | remainder(1e-320, 5e-324) returns nonzero subnormal instead of 0 |
