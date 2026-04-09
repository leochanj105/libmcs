# Goal 3: Fix `nexttoward` direction logic

## Function
- `nexttoward` (double → double, with long-double-is-64bits)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/nexttowardd.c` (calls `nextafter(x, (double) y)`)
- C nextafter: `/home/leochanj/Desktop/libmcs/libm/mathd/nextafterd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s2/src/mathd.rs` — `nexttowardd` at line 3502 (calls `nextafterd`), `nextafterd` at line 3460

## What's Wrong
**Wrong direction.** `nexttoward(1.0, 2.0)` should step UP toward 2.0, returning `0x1.0000000000001p+0`. Rust returns `0x1.fffffffffffffp-1` (stepped DOWN, away from target).

The Rust `nexttowardd` delegates to `nextafterd`. The bug is in `nextafterd`'s direction comparison logic (lines 3477–3493). For x=1.0 (hx=0x3FF00000, lx=0) and y=2.0 (hy=0x40000000, ly=0), the code should take the increment path but appears to take the decrement path.

## Failing Test
```
nexttoward 0x1p+0 0x8p-2:   C = 0x1.0000000000001p+0,   Rust = 0x1.fffffffffffffp-1
```

## What Needs to Change
Compare `nextafterd` (mathd.rs:3460) against the C `nextafter` implementation in `nextafterd.c`. Focus on:
- The direction comparison: `hx > hy || (hx == hy && lx > ly)` — verify signed vs unsigned semantics match C
- The increment/decrement logic and which branch is taken for positive x stepping toward larger y
- Possible off-by-one or sign-extension issue in the `hx`/`hy` comparison

## Success Criteria
- `nexttoward(1.0, 2.0)` returns `0x1.0000000000001p+0` (bitwise exact match with C)
- `nextafter` tests (if any) still pass (shared implementation)
- All other currently-passing tests continue to pass
