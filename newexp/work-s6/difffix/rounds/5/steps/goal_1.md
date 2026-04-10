# Goal 1: Fix `fmodd` ilogb-of-subnormal loop — wrong loop-counter type breaks subnormal modulo

## Function
`fmodd` (called by `remainderd` via the Round-4 fix). The visible failure is in `remainder`, but the defect is inside `fmodd`.

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/fmodd.c` (reference; do **not** modify)
- C caller: `/home/leochanj/Desktop/libmcs/libm/mathd/remainderd.c` (reference)
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s6/src/mathd.rs`
  - `fmodd` definition: `mathd.rs:2475` (the buggy loops are at lines **2511–2517** and **2532–2538**)
  - `remainderd` definition: `mathd.rs:3720` (already calls `fmodd` correctly at line 3733; do not change)

## Problem
MISMATCH — 1 test failure (carryover from Rounds 3 and 4).

```
C:    remainder 1e-320 5e-324 = 0x0p+0
Rust: remainder 1e-320 5e-324 = 0x0.00000000007d8p-1022
```

`5e-324 == 2^-1074` (the smallest positive subnormal) and `1e-320` is an
exact integer multiple `N · 2^-1074`, so `1e-320 mod 5e-324 == 0` and the
IEEE remainder is `+0`. Round 4 already redirected `remainderd` to call
`fmodd` instead of Rust's built-in `%` operator, which was the right call
— but the test still fails because `fmodd` itself has a separate bug.

### Root cause: signed vs. unsigned loop counter

The C `fmod` (`fmodd.c:107`) declares the helper variable as
`int32_t i;`. Its ilogb-of-subnormal helper (`fmodd.c:142–151`) reads:

```c
if (hx == 0) {
    for (ix = -1043, i = lx; i > 0; i <<= 1) {
        ix -= 1;
    }
}
```

`i` is **signed**, so the loop exits as soon as the highest set bit shifts
into bit 31 (the sign bit) — that is exactly the “first significant bit
of `lx`” marker, which is the whole point of this `ilogb` estimate.

The Rust port at `mathd.rs:2510–2525` translated `lx` (a `u32`) directly
into `i` and kept it **unsigned**:

```rust
let mut ix: i32;
if (hx as u32) < 0x00100000 {
    if hx == 0 {
        ix = -1043;
        let mut i = lx;          // <-- u32, NOT i32
        while i > 0 {            // <-- unsigned compare; only stops at i == 0
            ix -= 1;
            i <<= 1;
        }
    } else {
        ix = -1022;
        let mut i = (hx as u32) << 11;
        while (i as i32) > 0 {   // <-- this branch is correctly signed
            ix -= 1;
            i <<= 1;
        }
    }
}
```

Because `i` is `u32`, the loop now keeps shifting until **every** set bit
has fallen off the top of the word, which is `(32 − position_of_lowest_set_bit)`
extra iterations beyond what C does. Each extra iteration decrements `ix`
by one too many. Result: `ix` is too small (too negative), so the later
subnormal-shift step (`mathd.rs:2553–2562`) over-shifts `hx`, the
fixed-point modulo loop (`mathd.rs:2577–2595`) leaves residue, and
`fmodd` returns a nonzero subnormal where C returns `+0`.

The same bug exists in the symmetric `iy` block at `mathd.rs:2531–2546`:

```rust
if hy == 0 {
    iy = -1043;
    let mut i = ly;       // <-- u32
    while i > 0 {         // <-- unsigned compare
        iy -= 1;
        i <<= 1;
    }
}
```

For the failing test specifically:

| value     | bits           | C `ix`/`iy` | Rust `ix`/`iy` |
|-----------|----------------|-------------|----------------|
| `1e-320`  | `lx ≈ 0x7E8`   | `-1064`     | `-1072` (off by 8) |
| `2·5e-324`| `ly = 0x2`     | `-1073`     | `-1074` (off by 1) |

Both `ix` and `iy` are wrong, the alignment shift is wrong, and the fixed-point
loop runs the wrong number of iterations, leaving the observed `0x7d8 · 2^-1074`
residue.

The other subnormal branch (`hx != 0`, `hx < 0x00100000`) at
`mathd.rs:2519–2524` already uses `(i as i32) > 0` and is correct — only
the `hx == 0` and `hy == 0` branches need fixing.

## What Needs to Change
In `mathd.rs::fmodd`, change the **two** unsigned-comparison loops to
match C's signed semantics. Either declare `i` as `i32` from the start,
or cast on the comparison; the latter is the smaller, more local change
and matches the style used for the sibling branch immediately below.

**Edit 1** — at `mathd.rs:2511–2517` (the `hx == 0` branch):

```rust
if hx == 0 {
    ix = -1043;
    let mut i = lx;
    while (i as i32) > 0 {   // was: while i > 0
        ix -= 1;
        i <<= 1;
    }
}
```

**Edit 2** — at `mathd.rs:2532–2538` (the `hy == 0` branch):

```rust
if hy == 0 {
    iy = -1043;
    let mut i = ly;
    while (i as i32) > 0 {   // was: while i > 0
        iy -= 1;
        i <<= 1;
    }
}
```

Do **not** modify `remainderd` — the Round-4 redirection to `fmodd` at
`mathd.rs:3733` is already correct and stays. Do **not** modify `remquod`
— it does not use this loop and is not failing any test.

After these two single-token edits, `fmodd`'s `ix` / `iy` for subnormal
inputs whose high word is zero will agree with the C source bit-for-bit,
the alignment shift and fixed-point loop will run the correct number of
iterations, and `remainder(1e-320, 5e-324)` will collapse to `+0`.

## Success Criteria
- `remainder(1e-320, 5e-324)` returns exactly `+0.0` (encoded `0x0p+0`),
  bitwise-identical to C.
- The 1 remaining `remainder` mismatch resolves; total mismatches go from
  1 → 0 (test count: 2775/2775 passing).
- No regressions in `remainder`, `fmod`, or `remquo` tests for any of:
  normal/normal, normal/subnormal, subnormal/normal, subnormal/subnormal,
  equal-magnitude, infinities, NaNs, signed zeros.
- `fmodd` continues to match C bit-for-bit on all currently-passing inputs
  (the change only narrows the loop-exit condition to match the C signed
  semantics; it can never make a previously-correct case incorrect).
