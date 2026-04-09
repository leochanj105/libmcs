# Goal 4: Fix `nexttowardf` direction logic

## Function
- `nexttowardf` (float x, long double y → float)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathf/nexttowardf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s2/src/mathf.rs` — `nexttowardf` at line 2434

## What's Wrong
**Wrong direction.** `nexttowardf(1.0f, 2.0)` should step UP toward 2.0, returning `0x1.000002p+0`. Rust returns `0x1.fffffep-1` (stepped DOWN, away from target).

The Rust implementation at mathf.rs:2434 has its own logic (does NOT delegate to nextafterf). The direction comparison `(x as f64) < y` and the corresponding bit increment/decrement should match the C version's `x < y` comparison, but the result direction is inverted.

## Failing Test
```
nexttowardf 0x1p+0 0x8p-2:   C = 0x1.000002p+0,   Rust = 0x1.fffffep-1
```

## What Needs to Change
Compare the Rust `nexttowardf` (mathf.rs:2434) against C `nexttowardf` (nexttowardf.c:14). Focus on:
- The direction comparison: C uses `x < y` (float promoted to long double), Rust uses `(x as f64) < y` — verify these are equivalent
- The sign check: C uses `signbit(x) != 0`, Rust uses `x.is_sign_negative()` — verify equivalence
- The bit increment/decrement paths — check if increment and decrement are swapped

## Success Criteria
- `nexttowardf(1.0, 2.0)` returns `0x1.000002p+0` (bitwise exact match with C)
- All other currently-passing nexttowardf tests continue to pass
