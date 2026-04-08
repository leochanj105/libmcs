# Goal 3: Fix fenv stubs for trivial calls

## Function
`feclearexcept`, `feraiseexcept`, `fegetround`, `fesetround`, `fetestexcept`

## C Source
/home/leochanj/Desktop/libmcs/libm/include/fenv.h (or platform fenv implementation)

## Rust Source
/home/leochanj/Desktop/libmcs/newexp/rust-s2/src/lib.rs (lines 16-26)

## Problem
All fenv functions are stubbed to return `-1` (error). But the C tests call them
with argument `0` (no-op cases) and expect return value `0` (success):

```
feclearexcept(0) = 0
feraiseexcept(0) = 0
fegetround() = 0
fesetround(0) = 0
fetestexcept(0) = 0
```

## What Needs to Change
Update the fenv stubs in lib.rs to return `0` for trivial/no-op calls:

- `feclearexcept(0)` → return 0 (clearing no exceptions succeeds)
- `feraiseexcept(0)` → return 0 (raising no exceptions succeeds)
- `fegetround()` → return 0 (report round-to-nearest, which is the default)
- `fesetround(0)` → return 0 (setting round-to-nearest succeeds since it's already the mode)
- `fetestexcept(0)` → return 0 (no exceptions to test, result is 0)

A simple approach: return 0 for all calls with `excepts == 0`, return -1 otherwise.
For `fegetround()` and `fesetround(0)`, always return 0 (default rounding mode).

## Success Criteria
- `feclearexcept(0) = 0`
- `feraiseexcept(0) = 0`
- `fegetround() = 0`
- `fesetround(0) = 0`
- `fetestexcept(0) = 0`
