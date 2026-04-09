# Goal 2: Fix __fpclassifyf return values

## Function
`__fpclassifyf` (float classification)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathf/internal/fpclassifyf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s4/src/mathf.rs` (line 3161)

## Failure Type
MISMATCH — wrong output (2 direct mismatches + 1 cascading failure in nanf)

## Symptom
```
C:    __fpclassifyf zero = 2
Rust: __fpclassifyf zero = 0
C:    __fpclassifyf inf = 1
Rust: __fpclassifyf inf = 3
```
Also causes nanf test failure (see Goal 3).

## Root Cause
The Rust function returns hardcoded integer values that don't match the C library's `FP_*` constants defined in `libm/include/math.h`:
```c
#define FP_NAN        0
#define FP_INFINITE   1
#define FP_ZERO       2
#define FP_SUBNORMAL  3
#define FP_NORMAL     4
```

Current Rust code returns:
| Category   | Rust returns | C returns (correct) |
|------------|-------------|-------------------|
| ZERO       | 0           | 2 (FP_ZERO)      |
| NORMAL     | 4           | 4 (FP_NORMAL)    |
| SUBNORMAL  | 2           | 3 (FP_SUBNORMAL) |
| INFINITE   | 3           | 1 (FP_INFINITE)  |
| NAN        | 1           | 0 (FP_NAN)       |

## Fix
In `mathf.rs` at line 3161, change the return values to match:
```rust
pub fn __fpclassifyf(x: f32) -> i32 {
    let w = get_float_word(x) & 0x7fffffffu32;
    if w == 0x00000000u32 { return 2; }        // FP_ZERO
    if w >= 0x00800000u32 && w <= 0x7f7fffffu32 { return 4; } // FP_NORMAL
    if w <= 0x007fffffu32 { return 3; }        // FP_SUBNORMAL
    if w == 0x7f800000u32 { return 1; }        // FP_INFINITE
    0                                           // FP_NAN
}
```

## Success Criteria
- `__fpclassifyf zero` returns `2`
- `__fpclassifyf inf` returns `1`
- `__fpclassifyf normal` returns `4`
- `nanf isnan=1` (cascading fix — see Goal 3)
