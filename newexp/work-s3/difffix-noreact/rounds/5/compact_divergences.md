# Compact Divergences — Round 5

8 test failures across 6 functions. 6 are regressions from round 4, 2 are pre-existing.

## Round 4 Regression Analysis

Round 4 made 3 changes:
1. **cacos/cacosf**: Changed `FRAC_PI_2 - tmp0.re` → `-(tmp0.re - FRAC_PI_2)` to fix NaN sign.
   - Fixed: cacos(nan,nan) NaN sign ✓
   - **Regressed**: cacos(1,0) now returns -0 instead of +0; cacos(inf,0) returns -nan instead of nan.
   - Root cause: the negation approach `-(a - b)` produces `-0` when `a == b` and flips NaN sign unconditionally.
2. **casinh/casinhf**: Added `if im.is_nan() { -im } else { im }` to flip NaN sign.
   - Fixed: casinh(nan,0) NaN sign ✓
   - **Regressed**: casinh(inf,1) now returns -nan instead of nan in im.
   - Root cause: blanket NaN negation flips sign for all NaN cases, not just the one that needed it.
3. **log1pf**: Changed `hx` → `ax` in finite check. This was a **good fix** (resolved log1pf(-1) = -inf). Keep it.

## Current Failures

### 1. cacos / cacosf — wrong sign in real part (REGRESSION + pre-existing NaN issue)
- `cacos(1+0i)`: C returns `(0x0p+0, 0x0p+0)`, Rust returns `(-0x0p+0, 0x0p+0)` — negative zero regression
- `cacos(inf+0i)`: C returns `(nan, inf)`, Rust returns `(-nan, inf)` — wrong NaN sign regression
- Pre-existing (masked by regression): `cacos(nan,nan)` NaN sign was wrong before round 4
- The `-(tmp0.re - FRAC_PI_2)` approach fixes NaN but introduces -0 and wrong NaN signs elsewhere.
- Need: revert to `FRAC_PI_2 - tmp0.re` and handle only the specific NaN sign case, or match C's NaN propagation behavior exactly.

### 2. casinh / casinhf — wrong NaN sign in imaginary part (REGRESSION)
- `casinh(inf+1i)`: C returns `(-nan, nan)`, Rust returns `(-nan, -nan)` — wrong NaN sign in im
- The `if im.is_nan() { -im } else { im }` hack fixed one input but broke another.
- C code is simply `w = CMPLX(cimag(tmp), -creal(tmp))` with no NaN special handling.
- The root cause is likely in casind/casinf returning NaN with different sign bits than C.
- Need: revert the NaN hack, investigate and fix the NaN sign propagation in casind/casinf.

### 3. logb — off-by-one for smallest subnormal (PRE-EXISTING)
- C: `logb(0x0.0000000000001p-1022) = -1074` / Rust: `-1075`
- Root cause: In the subnormal branch where `hx == 0`, the loop `while lx > 0 { ix -= 1; lx <<= 1; }` uses `lx` as `u32`. In C, `lx` is `int32_t` (signed), so `lx > 0` becomes false when MSB is set. In Rust u32, `lx > 0` stays true when MSB is set → one extra iteration → off by one.
- Fix: change loop condition to `while (lx as i32) > 0`.

### 4. modf — returns 0 instead of NaN for fractional part (PRE-EXISTING)
- C: `modf(nan) = nan, int nan` / Rust: `0x0p+0, int nan`
- Root cause: In the `j0 > 51` branch, C code does:
  ```c
  *iptr = x;
  if (isnan(x)) { return *iptr = x + x; }  // returns NaN, sets iptr to NaN
  return signed_zero;
  ```
  Rust code does:
  ```rust
  *iptr = if x.is_nan() { x + x } else { x };
  return f64::from_bits(sign_bits << 32);  // always returns signed zero!
  ```
  Rust sets *iptr correctly but ALWAYS returns signed zero. When x is NaN, it should return NaN instead.
- Fix: add early return for NaN case: `if x.is_nan() { *iptr = x + x; return *iptr; }`
