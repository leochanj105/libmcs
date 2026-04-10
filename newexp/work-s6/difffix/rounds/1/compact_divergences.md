# Compact Divergences — Round 1

68 test failures across 18 functions.

| # | Function | Type | Failures | Root Cause Summary |
|---|----------|------|----------|--------------------|
| 1 | `__cosf` | mathf/internal | 1 | Trig kernel precision: last-bit error |
| 2 | `__fpclassifyf` | mathf/internal | 5 | Wrong enum values for FP classes |
| 3 | `acosh` | mathd | 5 | Algorithm bug: completely wrong results |
| 4 | `cosf` | mathf | 2 | Large-argument reduction error |
| 5 | `cproj` | complexd | 5 | Infinity projection: imaginary not zeroed |
| 6 | `cprojf` | complexf | 4 | Same as cproj but float version |
| 7 | `ctanf` | complexf | 4 | Precision errors in complex tangent |
| 8 | `exp2` | mathd | 1 | Wrong result for exact integer power (3.0) |
| 9 | `ilogb` | mathd | 4 | Off-by-one for subnormals; wrong FP_ILOGB0 |
| 10 | `ilogbf` | mathf | 1 | Wrong FP_ILOGB0 value |
| 11 | `log10` | mathd | 1 | Last-bit precision error |
| 12 | `log1pf` | mathf | 9 | Broken for negative args: no -inf, no NaN |
| 13 | `logb` | mathd | 2 | Off-by-one for subnormals |
| 14 | `modf` | mathd | 1 | NaN input returns 0 instead of NaN |
| 15 | `nanf` | mathf | 1 | Returns non-NaN value |
| 16 | `pow` | mathd | 20 | Major algorithm errors across many inputs |
| 17 | `rem_pio2` | mathd/internal | 1 | NaN sign differs for infinity input |
| 18 | `remainder` | mathd | 1 | Subnormal precision error |
