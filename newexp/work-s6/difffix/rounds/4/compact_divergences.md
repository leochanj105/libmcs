# Compact Divergences — Round 4

3 mismatches across 3 functions (down from 35/7 in Round 3).

| # | Function | Type | Mismatches | Summary |
|---|----------|------|------------|---------|
| 1 | log1pf | MISMATCH | 1 | log1pf(1.0000001f) off by 1 ULP — missing `+c` correction term in zero-`f` branch |
| 2 | rem_pio2 | MISMATCH | 1 | rem_pio2(inf) returns -nan instead of nan (NaN sign bit) — carryover from R3 (skipped) |
| 3 | remainder | MISMATCH | 1 | remainder(1e-320, 5e-324) returns nonzero subnormal instead of 0 — carryover from R3 (skipped) |

Notes:
- All other Round-3 issues (exp2, log1pf negative inputs, logb subnormals, modf nan, pow, etc.) are now passing.
- log1pf had 9 mismatches in R3, fixed down to 1 ULP issue on a single positive-input case.
- rem_pio2 and remainder were skipped in R3 and remain unchanged.
