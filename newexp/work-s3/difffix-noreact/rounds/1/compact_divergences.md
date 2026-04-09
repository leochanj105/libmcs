# Compact Divergences — Round 1

## RUNTIME: Infinite loop
- `__sin_pif` hangs after input 0.25 → TIMEOUT, cascades to missing `__ctans`/`__ctansf`

## MISSING (2 functions, 8 tests)
- `__ctans` (4 tests) — not reached due to timeout
- `__ctansf` (4 tests) — not reached due to timeout

## MISMATCH (21 functions, 44 tests)

| Function | Tests | Root cause |
|----------|-------|------------|
| exp2 | 2 | Wrong values: 2^1023 and 2^10 both wrong |
| pow | 2 | Uses exp2 internally; 2^10=3566.9 instead of 1024 |
| sinf | 1 | sin(pi)=-0x1.6bff7ap-16 instead of -0x1.777a5cp-24 |
| cpowf | 1 | Imaginary part wrong, likely sinf bug |
| acosh | 1 | acosh(2) completely wrong value |
| log1pf | 1 | log1pf(-1) = -2 instead of -inf |
| logb | 1 | logb(subnormal) off by 1: -1075 vs -1074 |
| modf | 1 | modf(NaN) returns 0 instead of NaN |
| fpclassifyf | 4 | Classification constants wrong (0/1/2/3 mapping) |
| ilogb | 3 | Zero returns INT_MIN instead of INT_MIN+1; subnormal off by 1 |
| ilogbf | 1 | Zero returns INT_MIN instead of INT_MIN+1 |
| lgamma | 10 | signgam always 0 instead of correct sign |
| lgammaf | 6 | signgam always 0 instead of correct sign |
| cproj | 2 | Infinite inputs: imaginary part wrong (should be copysign(0,imag)) |
| cprojf | 2 | Same as cproj |
| cacos | 1 | cacos(NaN,NaN) real part sign: nan vs -nan |
| cacosf | 1 | Same as cacos |
| casinh | 1 | casinh(NaN,0) imaginary sign: nan vs -nan |
| casinhf | 1 | Same as casinh |
| catanh | 1 | catanh(NaN,0) imaginary sign: nan vs -nan |
| catanhf | 1 | Same as catanh |

## Likely shared root causes
1. **exp2 bug** → affects exp2, pow
2. **sinf/trigf bug** → affects sinf, cpowf
3. **__sin_pif infinite loop** → affects __ctans, __ctansf (MISSING)
4. **lgamma signgam** → affects lgamma, lgammaf
5. **cproj infinity handling** → affects cproj, cprojf
6. **NaN sign propagation** → affects cacos/f, casinh/f, catanh/f
