# Goal 1: Fix log1pf — 1 ULP error on log1pf(1.0000001f)

## Function
`log1pf`

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathf/log1pf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s6/src/mathf.rs` (`log1pf` at line 2099)

## Problem
MISMATCH — 1 test failure (down from 9 in Round 3).

```
C:    log1pf 1.0000001f = 0x1.62e432p-1
Rust: log1pf 1.0000001f = 0x1.62e43p-1
```

This is a 1 ULP difference. Tracing the C code for `x = 1.0000001f`:
- `hx = 0x3f800001`, `k != 0` branch is taken.
- `u = 1.0f + x = 2.0f` (exact), `k = 1`, `c = (1.0 - (u - x)) / u = 2^-24` (a
  small but **nonzero** correction term).
- `hu &= 0x007fffff` → `0`, branch `hu < 0x3504f7` taken, so `u = 1.0f`,
  `f = u - 1.0f = 0`, `hfsq = 0`.
- The `hu == 0 && f == 0` branch fires:

```c
if (hu == 0) {
    if (f == zero) {
        c += k * ln2_lo;
        return k * ln2_hi + c;     /* = k*LN2_HI + (c + k*LN2_LO) */
    }
```

The C version returns `k * ln2_hi + c + k * ln2_lo`, which **includes the
correction `c`** computed earlier (`= 2^-24`).

The Rust version at `mathf.rs:2159-2163`:

```rust
if hu == 0 {
    if f == 0.0f32 {
        let cp = k as f32 * LN2_LO;
        return k as f32 * LN2_HI + cp;
    }
```

returns `k * LN2_HI + k * LN2_LO`, **dropping the `c` term entirely**. The
missing `c = 2^-24` is exactly the 1 ULP that separates the two outputs.

## What Needs to Change
In `log1pf` at `mathf.rs:2159-2163`, add the existing local `c` to the early
return so it matches the C semantics. One direct port:

```rust
if hu == 0 {
    if f == 0.0f32 {
        let c2 = c + k as f32 * LN2_LO;
        return k as f32 * LN2_HI + c2;
    }
    ...
}
```

(equivalently, `return k as f32 * LN2_HI + (c + k as f32 * LN2_LO);`)

The `c` variable is already initialized in scope from the `k != 0` branch
above (lines 2132-2144), so no other change is needed.

## Success Criteria
- `log1pf(1.0000001f)` returns exactly `0x1.62e432p-1` (bitwise match with C).
- The 1 remaining log1pf mismatch resolves.
- No regressions in any of the 8 log1pf cases that passed in Round 3
  (negative inputs, NaN/Inf, subnormals, large positive values, etc.).
