# Goal 5: Export internal float trig kernel functions

## Functions
`__cosf`, `__sinf`, `__rem_pio2f`

## C Source
/home/leochanj/Desktop/libmcs/libm/mathf/internal/trigf.c

## Rust Source
/home/leochanj/Desktop/libmcs/newexp/rust-s2/src/mathf.rs — internal float kernel functions

## Problem
Same as Goal 4 but for float-precision. The test harness calls these directly.

Expected test outputs:
```
__cosf 0x1p-1 0x0p+0 = 0x1.c1528p-1
__cosf 0x0p+0 0x0p+0 = 0x1p+0
__sinf 0x1p-1 0x0p+0 0 = 0x1.eaee88p-2
__sinf 0x0p+0 0x0p+0 0 = 0x0p+0
__rem_pio2f 0x1p+0 = 1 y=[-0x1.243f6ap-1, -0x1.110cp-26]
__rem_pio2f 0x1.4p+3 = 6 y=[0x1.26838p-1, 0x1.99cp-26]
```

## What Needs to Change
Add `#[no_mangle] pub extern "C"` wrapper functions in lib.rs:
- `__cosf(x: f32, y: f32) -> f32`
- `__sinf(x: f32, y: f32, iy: i32) -> f32`
- `__rem_pio2f(x: f32, y: *mut f32) -> i32`

## Success Criteria
- All 6 test cases above produce bitwise-exact output matching C
