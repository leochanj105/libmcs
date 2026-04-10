# Goal 3: Fix remainder — subnormal/subnormal returns nonzero instead of 0

## Function
`remainder` (calls Rust `mathd::remainderd`)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/remainderd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s6/src/mathd.rs` (`remainderd` at line 3717; `fmodd` at line 2472)

## Problem
MISMATCH — 1 test failure (carryover from Round 3 — was skipped).

```
C:    remainder 1e-320 5e-324 = 0x0p+0
Rust: remainder 1e-320 5e-324 = 0x0.00000000007d8p-1022
```

`5e-324 = 2^-1074` (the smallest positive subnormal) and `1e-320` is some
exact integer multiple `N · 2^-1074`. Therefore `1e-320 mod 5e-324 = 0` and
the IEEE remainder is `+0`. The Rust output `0x0.00000000007d8p-1022`
(= `2008 · 2^-1074`) is *not zero*, meaning the modulo step left ~2008 ULPs
of residue.

The C `remainder` (`remainderd.c:132-134`) reduces with the C `fmod`:

```c
if (hy <= 0x7fdfffff) {
    x = fmod(x, 2 * y);
}
```

The Rust `remainderd` (`mathd.rs:3730`) uses Rust's built-in `%`:

```rust
if hy <= 0x7fdfffff { x = x % (2.0 * y); }
```

For subnormal inputs `1e-320` and `2 · 5e-324 = 1e-323`, Rust's `%` operator
is leaving residue that the manually-ported C `fmod` would not. The pure-C
`fmod` algorithm in `mathd.rs::fmodd` (line 2472) handles subnormals by
shifting them up to a synthetic-normal representation before the bitwise
reduction loop, which Rust's `%` implementation does not necessarily do
identically (and on this platform it visibly does not).

`fmodd` is already a faithful port of the C `fmod` and is the right helper
to call here.

## What Needs to Change
In `remainderd` at `mathd.rs:3730`, replace the built-in modulo with a call
to the locally-defined `fmodd`, mirroring the C source exactly:

```rust
if hy <= 0x7fdfffff { x = fmodd(x, 2.0 * y); }
```

Do **not** modify `fmodd` itself; it is already the C-faithful port. Only
swap the operator for the function call. This makes the subnormal-reduction
path bitwise-identical to C's `fmod`.

After the swap, the rest of `remainderd` (the equality check, abs, halving,
sign restore) is already structurally identical to the C source and will
correctly recognize the now-zero residue.

Note: also consider checking `remquod` at `mathd.rs:3761` — it has the
same `x = x % (8.0 * y)` pattern and may be vulnerable to the same class
of subnormal residue, though it is not currently failing any test. Do not
change it unless it is needed to fix a regression.

## Success Criteria
- `remainder(1e-320, 5e-324)` returns exactly `+0.0` (encoded `0x0p+0`),
  bitwise-identical to C.
- The 1 remainder mismatch resolves.
- No regressions in any of the previously-passing remainder test cases
  (normal/normal, normal/subnormal, infinities, NaNs, equality, etc.).
- No regressions in fmod or remquo tests.
