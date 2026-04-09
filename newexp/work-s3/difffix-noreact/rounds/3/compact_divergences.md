# Compact Divergences — Round 2 → Round 3

31 mismatches across 12 functions.

## 1. cacos / cacosf — NaN sign mismatch
- `cacos(inf, 0)`: C returns `nan,inf`, Rust returns `-nan,inf`
- `cacosf(inf, 0)`: same pattern
- Root cause: NaN sign propagation differs in complex acos

## 2. casinh / casinhf — NaN sign mismatch
- `casinh(inf, 1)`: C returns `-nan,nan`, Rust returns `-nan,-nan`
- `casinhf(inf, 1)`: same pattern
- Root cause: NaN sign propagation differs in complex asinh

## 3. fpclassifyf — wrong classification constants
- 4 mismatches: all classification values shifted
- C: zero=2, inf=1, nan=0, subnormal=3
- Rust: zero=0, inf=3, nan=1, subnormal=?
- Root cause: Rust uses different enum values than libmcs C constants

## 4. ilogb / ilogbf — FP_ILOGB0 value wrong
- `ilogb(0)`: C returns -2147483647, Rust returns -2147483648
- `ilogb(-0)`: same
- `ilogb(subnormal)`: C returns -1074, Rust returns -1075
- `ilogbf(0)`: C returns -2147483647, Rust returns -2147483648
- Root cause: FP_ILOGB0 constant differs; subnormal exponent off-by-one

## 5. lgamma / lgammaf — signgam not set
- All lgamma/lgammaf value outputs match, but signgam is always 0 in Rust vs correct values in C
- Root cause: Rust lgamma wrapper not writing to signgam global

## 6. log1pf — wrong result for -1
- `log1pf(-1)`: C returns `-inf`, Rust returns `-0x1p+1` (-2.0)
- Root cause: boundary case log1p(-1) = -inf not handled

## 7. logb — subnormal exponent wrong
- `logb(subnormal)`: C returns -1074, Rust returns -1075 (approximate hex values)
- Root cause: subnormal exponent calculation off-by-one (same root cause as ilogb)

## 8. modf — NaN fractional part wrong
- `modf(nan)`: C returns frac=nan, Rust returns frac=0
- Root cause: NaN not propagated to fractional return value
