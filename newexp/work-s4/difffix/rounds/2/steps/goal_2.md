# Goal 2: Fix exp2d — inherits powd bug

## Function
`exp2` (double-precision base-2 exponential)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/exp2d.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s4/src/mathd.rs` (line 2119, function `exp2d`)

## Failure Type
MISMATCH — wrong output

## Symptom
```
C:    exp2 0x1.8p+1 = 0x1p+3
Rust: exp2 0x1.8p+1 = 0x1.fffee746db0fcp+5
```
exp2(3.0) should return 8.0 but Rust returns ~63.999.

## Root Cause
Both C and Rust implement `exp2` as `pow(2.0, x)`. The Rust `exp2d` (line 2119)
correctly delegates to `powd(2.0, x)`. The bug is entirely in `powd` — see Goal 1.

No changes are needed in `exp2d` itself.

## Fix
No code change in `exp2d`. This is fixed by Goal 1 (fixing `powd`).

## Success Criteria
- `exp2 0x1.8p+1` produces `0x1p+3` (matches C output exactly)
- All other exp2 tests continue to pass
- Depends on: Goal 1
