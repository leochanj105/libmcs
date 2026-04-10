# Goal 1: Fix exp2 — exp2(3.0) returns wrong value

## Function
`exp2` (calls `mathd::exp2d`)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/exp2d.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s6/src/mathd.rs` (`exp2d` at line 2119)

## Problem
MISMATCH — 1 test failure (still broken after Round 2 fix attempt).

```
C:    exp2 0x1.8p+1 = 0x1p+3              (exp2(3.0) = 8)
Rust: exp2 0x1.8p+1 = 0x1.fffee746db0fcp+5 (~63.99)
```

The Rust `exp2d` is computing roughly `2^(2*x)` for `x=3`, indicating the
exponent argument is being doubled, the polynomial reduction is using the wrong
factor, or the integer/fractional split is misaligned. The result `~63.99` is
suspiciously close to `2^6 - eps`, suggesting a `2^(x+x)` style bug.

## What Needs to Change
Compare the C `exp2` against the Rust `exp2d` line-by-line. Look for:
- Wrong multiplier on the integer part recovery (e.g., `n` doubled).
- A misplaced bit-shift constant in the final `2^k` reconstruction.
- An incorrect call to a helper (e.g., passing `x*2` instead of `x` to a
  reduction routine).
Fix the Rust code so that the integer part of `x` is extracted exactly once
and the fractional polynomial is evaluated with the correct argument.

## Success Criteria
- `exp2(3.0)` returns exactly `0x1p+3` (`8.0`).
- All 1 exp2 mismatch resolves to bitwise-exact match with C output.
- No regressions in any other previously-passing exp2 test cases.
