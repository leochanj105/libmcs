# Goal 5: Fix nexttoward direction

## Function
`nexttoward` (delegates to `nexttowardd`)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/nexttowardd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s2/src/mathd.rs` (line ~3502)

## Problem
**Wrong output.** `nexttoward(1.0, 2.0)` should step toward 2.0 (i.e., return the next representable double above 1.0 = `0x1.0000000000001p+0`), but Rust returns the next double below 1.0 (`0x1.fffffffffffffp-1`). The direction comparison is reversed.

## What Needs to Change
The Rust `nexttowardd` has an inverted comparison — it steps away from the target instead of toward it. Find and fix the reversed condition (likely a `<` vs `>` or wrong branch in the if/else).

## Success Criteria
- `nexttoward(0x1p+0, 0x8p-2)` returns `0x1.0000000000001p+0` (bitwise match with C)
