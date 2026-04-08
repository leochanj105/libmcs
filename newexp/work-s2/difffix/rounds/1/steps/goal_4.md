# Goal 4: Export internal double trig kernel functions

## Functions
`__cos`, `__sin`, `__rem_pio2`

## C Source
/home/leochanj/Desktop/libmcs/libm/mathd/internal/trigd.c

## Rust Source
/home/leochanj/Desktop/libmcs/newexp/rust-s2/src/mathd.rs — internal functions (look for
kernel cos/sin/rem_pio2 implementations used by `cosd`, `sind`, etc.)

## Problem
The test harness calls `__cos`, `__sin`, and `__rem_pio2` directly to test the
internal kernel functions. These are not exported from the Rust binary with
`#[no_mangle]` — only the public `cos`, `sin` wrappers are exported.

Expected test outputs:
```
__cos 0x1p-1 0x0p+0 = 0x1.c1528065b7d5p-1
__cos 0x0p+0 0x0p+0 = 0x1p+0
__cos 0x1.921fb54442d18p-1 0x0p+0 = 0x1.6a09e667f3bcdp-1
__sin 0x1p-1 0x0p+0 0 = 0x1.eaee8744b05fp-2
__sin 0x0p+0 0x0p+0 0 = 0x0p+0
__sin 0x1.921fb54442d18p-1 0x0p+0 0 = 0x1.6a09e667f3bccp-1
__rem_pio2 0x1p+0 = 1 y=[-0x1.243f6a8885a31p-1, 0x1.cb3b399ep-55]
__rem_pio2 0x1.921fb54442d18p+1 = 2 y=[-0x1.1a62633145c07p-53, 0x1.f1976b7ed8fcp-109]
__rem_pio2 0x1.4p+3 = 6 y=[0x1.268380ccde2ddp-1, -0x1.3c9ca65p-55]
```

## What Needs to Change
Add `#[no_mangle] pub extern "C"` wrapper functions in lib.rs that export:
- `__cos(x: f64, y: f64) -> f64` — calls the internal cosine kernel
- `__sin(x: f64, y: f64, iy: i32) -> f64` — calls the internal sine kernel
- `__rem_pio2(x: f64, y: *mut f64) -> i32` — calls the internal pi/2 reduction

These must match the C ABI signatures exactly.

## Success Criteria
- All 9 test cases above produce bitwise-exact output matching C
