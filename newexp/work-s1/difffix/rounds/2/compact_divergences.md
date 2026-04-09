# Compact Divergences — Round 2

## Divergence 1: __ctans TIMEOUT
- **Function**: `__ctans` (complex double tangent helper)
- **Type**: FAULT — infinite loop / timeout
- **Root cause**: C `do { ... } while (fabs(t/d) > MACHEP)` exits when `t/d` is NaN (because NaN > X is false). Rust `loop { ... if (t/d).abs() <= MACHEP { break; } }` never breaks on NaN (NaN <= X is false).
- **When triggered**: When input z = 0+0i (or similar), d stays 0.0, producing 0.0/0.0 = NaN.

## Divergence 2: __ctansf TIMEOUT
- **Function**: `__ctansf` (complex float tangent helper)
- **Type**: FAULT — infinite loop / timeout
- **Root cause**: Same as Divergence 1 but for float version. Rust loop condition `(t/d).abs() <= MACHEPF` doesn't break on NaN.

## Divergence 3: log1pf MISMATCH
- **Function**: `log1pf`
- **Type**: MISMATCH — wrong output
- **Input**: `-0x1p+0` (i.e., -1.0f)
- **Expected (C)**: `-inf`
- **Actual (Rust)**: `-0x1p+1` (-2.0)
- **Root cause**: Rust line `if !flt_uword_is_finite(hx as u32)` casts signed i32 to u32 before comparison. For x=-1.0, hx=0xBF800000 (signed negative). Cast to u32 = 3229614080 which is > 0x7f800000, so `flt_uword_is_finite` returns false. The function incorrectly enters the NaN/+Inf early-return path, returning `x + x = -2.0`. In C, the macro compares hx as signed int32_t < 0x7f800000 (signed), which is true for negative hx.
