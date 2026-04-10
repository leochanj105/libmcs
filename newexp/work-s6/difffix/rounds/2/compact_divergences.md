# Compact Divergences — Round 2

45 mismatches across 11 functions.

| # | Function | Type | Mismatches | Summary |
|---|----------|------|------------|---------|
| 1 | cprojf | MISMATCH | 4 | Imaginary part not zeroed for infinite inputs |
| 2 | exp2 | MISMATCH | 1 | exp2(3.0) returns wrong value (~63.99 instead of 8) |
| 3 | ilogb | MISMATCH | 4 | Wrong result for 0.0 (off by 1) and subnormals (off by 1) |
| 4 | ilogbf | MISMATCH | 1 | Wrong result for 0.0f (-2147483648 vs -2147483647) |
| 5 | log10 | MISMATCH | 1 | log10(5.0) last bit wrong (precision) |
| 6 | log1pf | MISMATCH | 9 | Completely wrong for negative inputs; log1pf(-1)=-2 instead of -inf |
| 7 | logb | MISMATCH | 2 | Subnormal exponent off by 1 |
| 8 | modf | MISMATCH | 1 | modf(nan) returns 0 instead of nan |
| 9 | pow | MISMATCH | 20 | Widespread errors: pow(2,10)=wrong, pow(2,1000)=wrong, etc. |
| 10 | rem_pio2 | MISMATCH | 1 | rem_pio2(inf) returns -nan instead of nan |
| 11 | remainder | MISMATCH | 1 | remainder(1e-320, 5e-324) nonzero instead of 0 |
