# Compact Divergences — Round 2

38 mismatches across 17 functions.

| # | Function(s) | Category | Summary |
|---|-------------|----------|---------|
| 1 | acosh | Wrong output | acosh(2.0) returns 0x1.62e4… (ln(2)) instead of 0x1.5124… |
| 2 | cacos, cacosf | NaN sign | cacos(nan,nan) real part: C returns -nan, Rust returns nan |
| 3 | casinh, casinhf | NaN sign | casinh(nan,0) imag part: C returns nan, Rust returns -nan |
| 4 | catanh, catanhf | NaN sign | catanh(nan,0) imag part: C returns nan, Rust returns -nan |
| 5 | cproj, cprojf | Infinity projection | cproj(inf,-inf) imag should be -0, Rust returns inf; cproj(nan,inf) imag should be +0, Rust returns inf |
| 6 | fpclassifyf | Wrong constants | Classification enum values don't match C's FP_NAN=0, FP_INFINITE=1, FP_ZERO=2, etc. |
| 7 | ilogb, ilogbf | Zero/subnormal | ilogb(0) returns -2147483648 instead of -2147483647; ilogb(subnormal) off by one |
| 8 | lgamma, lgammaf | signgam | signgam always 0 instead of correct sign (+1/-1) |
| 9 | log1pf | Wrong output | log1pf(-1.0) returns -2.0 instead of -inf |
| 10 | logb | Subnormal | logb(smallest subnormal) returns -0x1.0ccp+10 (-1075) instead of -0x1.0c8p+10 (-1074) |
| 11 | modf | NaN handling | modf(nan) fractional part returns 0x0p+0 instead of nan |
