# Goal 5: Fix log1pf(-1.0) returning wrong value instead of -inf

## Function
`log1pf` (log(1+x), float precision)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathf/log1pf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathf.rs` (fn `log1pf`, ~line 2099)

## Problem
**Wrong output.** `log1pf(-1.0)` should return `-inf` (since log(0) = -infinity), but Rust returns `-0x1p+1` (-2.0). This is a critical math error — the pole at x=-1 is not handled correctly.

## What Needs to Change
The Rust `log1pf` must detect when `x == -1.0` (i.e., `1+x == 0`) and return negative infinity. The C code likely has an explicit check for this case. The Rust transpilation either lost this special case or has a bug in the branch condition.

## Success Criteria
- `log1pf(-0x1p+0)` returns `-inf`
- All other log1pf tests continue to pass
- Output is bitwise exact with C
