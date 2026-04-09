# Goal 1: Fix cacos/cacosf — revert round 4 regression + fix NaN sign

## Functions
- `cacosd` (double complex arc cosine)
- `cacosf` (float complex arc cosine)

## Source files
- C (double): `/home/leochanj/Desktop/libmcs/libm/complexd/cacosd.c`
- C (float): `/home/leochanj/Desktop/libmcs/libm/complexf/cacosf.c`
- Rust (double): `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexd.rs` (line ~278, `cacosd`)
- Rust (float): `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexf.rs` (line ~272, `cacosf`)

## What's wrong
Round 4 changed `FRAC_PI_2 - tmp0.re` to `-(tmp0.re - FRAC_PI_2)`. This introduced 2 regressions per function while fixing 1 issue:

| Input | C result | Rust (current) | Status |
|-------|----------|-----------------|--------|
| cacos(1+0i) | (0x0p+0, 0x0p+0) | (-0x0p+0, 0x0p+0) | **REGRESSION** — negative zero |
| cacos(inf+0i) | (nan, inf) | (-nan, inf) | **REGRESSION** — wrong NaN sign |
| cacos(nan+nan*i) | (-nan, nan) | (-nan, nan) | Fixed by round 4 (was failing before) |

The C code is simply: `tmp1 = M_PI_2 - creal(tmp0);`

On x86, `M_PI_2 - NaN` is computed as `M_PI_2 + (-NaN)`, which flips the NaN sign bit then propagates the NaN. So the result NaN has the OPPOSITE sign of the input NaN. Rust's `FRAC_PI_2 - NaN` may not replicate this — it tends to produce positive NaN regardless.

Before round 4 (with original `FRAC_PI_2 - tmp0.re`):
- cacos(1+0i): PASS (returns +0)
- cacos(inf+0i): PASS (returns nan)
- cacos(nan+nan*i): FAIL (returns nan, should be -nan)

## What needs to change

**Step 1:** Revert round 4's cacos change. Change back to `FRAC_PI_2 - tmp0.re`.

**Step 2:** Add NaN-specific handling that replicates C's x86 subtraction behavior. When `tmp0.re` is NaN, skip the subtraction and directly produce a NaN with the opposite sign bit:

```rust
// cacosd
let tmp1 = if tmp0.re.is_nan() {
    // Match C x86: M_PI_2 - NaN flips the NaN sign bit
    f64::from_bits(tmp0.re.to_bits() ^ 0x8000_0000_0000_0000)
} else {
    std::f64::consts::FRAC_PI_2 - tmp0.re
};
```

```rust
// cacosf
let tmp1 = if tmp0.re.is_nan() {
    f32::from_bits(tmp0.re.to_bits() ^ 0x8000_0000)
} else {
    std::f32::consts::FRAC_PI_2 - tmp0.re
};
```

This approach:
- For finite inputs (like 1+0i): uses normal subtraction → +0 ✓
- For NaN inputs: XOR flips sign bit, matching C's x86 behavior:
  - casin(nan,nan).re = +NaN → XOR → -NaN ✓ (C expects -nan)
  - casin(inf,0).re = -NaN → XOR → +NaN ✓ (C expects nan)

Also remove the round 4 comments about NaN sign propagation.

## Success Criteria
- `cacos(1+0i)` returns `(0x0p+0, 0x0p+0)` — positive zero (regression fixed)
- `cacos(inf+0i)` returns `(nan, inf)` — correct NaN sign (regression fixed)
- `cacos(nan+nan*i)` returns `(-nan, nan)` — NaN sign matches C (pre-existing fixed)
- Same for cacosf with float inputs
- All other cacos/cacosf test cases continue to pass
