# Goal 5: Fix pow — widespread incorrect results

## Function
`pow` (calls `mathd::powd`)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/powd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s6/src/mathd.rs` (`powd` at line 3504)

## Problem
MISMATCH — 20 test failures (the largest cluster).

```
C:    pow 0x1p+1 0x1.4p+3 = 0x1p+10               (pow(2,10)=1024 exact)
Rust: pow 0x1p+1 0x1.4p+3 = 0x1.b2d809254afbcp+11 (~6962)
C:    pow 2.0 1000.0  = 0x1p+1000
Rust: pow 2.0 1000.0  = 0x1.ffffffffbbp+999       (off in last bits)
C:    pow 2.0 -1000.0 = 0x1p-1000
Rust: pow 2.0 -1000.0 = 0x1.ffffffffbb4p-1001     (off in last bits)
... (17 more)
```

There are two distinct symptoms:
1. **Catastrophic for small integer exponents** (e.g. `pow(2,10)` is off by
   ~7x). This points at the fast integer-exponent path being broken — the
   "is `y` an integer" check, the integer extraction, or the `yisint` flag
   propagation may be wrong.
2. **Last-bit precision drift** for many large/normal cases (`2^1000`,
   `2^-1000`). This points at the high-precision log/exp polynomial in the
   main path losing accuracy — likely a constant or split-double trick was
   transpiled with the wrong constant or wrong rounding.

## What Needs to Change
Diff Rust `powd` line-by-line against the C reference. Specifically check:
- The `yisint` detection block (the C version inspects exponent bits of `y`).
- The big table of magic constants (`bp[]`, `dp_h[]`, `dp_l[]`, `L1..L6`,
  `P1..P5`, `lg2`, `lg2_h`, `lg2_l`, `cp`, `cp_h`, `cp_l`, `ivln2`, `ivln2_h`,
  `ivln2_l`, `two53`, etc.) — every single constant must be bit-for-bit
  identical to the C source.
- Any `(double)(int)` style cast that might have been transpiled with the
  wrong truncation semantics.
- The split-double `t1 = ...; t2 = v - (t1 - u)` reassociations — Rust may
  optimize these differently if `fma` or fast-math is in play. Use explicit
  `f64::from_bits` / `to_bits` masking where the C code does bit tricks.

## Success Criteria
- `pow(2.0, 10.0)` returns exactly `1024.0`.
- `pow(2.0, 1000.0)` returns exactly `0x1p+1000`.
- `pow(2.0, -1000.0)` returns exactly `0x1p-1000`.
- All 20 pow mismatches resolve to bitwise-exact match with C output.
- No regressions on the existing passing pow cases.
