# Compact Divergences — Round 4

7 mismatches across 7 functions. All are output mismatches (no compile errors, no panics, no missing).

| # | Function | Type | Input | C Output | Rust Output | Root Cause |
|---|----------|------|-------|----------|-------------|------------|
| 1 | cacos | mismatch | (nan,nan) | (-nan,nan) | (nan,nan) | Sign of real part NaN not preserved |
| 2 | cacosf | mismatch | (nan,nan) | (-nan,nan) | (nan,nan) | Sign of real part NaN not preserved (float variant) |
| 3 | casinh | mismatch | (nan,0x0p+0) | (-nan,nan) | (-nan,-nan) | Sign of imaginary part NaN incorrect |
| 4 | casinhf | mismatch | (nan,0x0p+0) | (-nan,nan) | (-nan,-nan) | Sign of imaginary part NaN incorrect (float variant) |
| 5 | log1pf | mismatch | -0x1p+0 (-1.0) | -inf | -0x1p+1 (-2.0) | log1p(-1) should return -inf, returns wrong value |
| 6 | logb | mismatch | 0x0.0000000000001p-1022 | -0x1.0c8p+10 (-1096) | -0x1.0ccp+10 (-1100) | Subnormal exponent extraction off by 4 |
| 7 | modf | mismatch | nan | (nan, int=nan) | (0x0p+0, int=nan) | Fractional part of NaN should be NaN, returns 0 |
