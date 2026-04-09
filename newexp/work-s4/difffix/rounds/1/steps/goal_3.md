# Goal 3: Fix nanf test failure (cascading from __fpclassifyf)

## Function
`nanf` (float NaN generator)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathf/nanf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s4/src/mathf.rs` (line 2390)

## Failure Type
MISMATCH — wrong output (cascading failure)

## Symptom
```
C:    nanf isnan=1
Rust: nanf isnan=0
```

## Root Cause
This is a **cascading failure** from Goal 2 (__fpclassifyf). The `nanf` function itself is correct — it returns `f32::from_bits(0x7FCF067D)` which is a valid NaN bit pattern.

The test checks: `__fpclassifyf(nanf("")) == FP_NAN` where `FP_NAN = 0`.

With the buggy `__fpclassifyf`, NaN returns `1` instead of `0` (FP_NAN), so the comparison `1 == 0` yields false (0).

## Fix
No change needed in `nanf` itself. Fixing `__fpclassifyf` (Goal 2) will resolve this test failure automatically.

## Success Criteria
- `nanf isnan=1` (matches C output)
- This is achieved by fixing __fpclassifyf to return `0` for NaN inputs
