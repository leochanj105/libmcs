# Goal 1: Fix powd — p_h not updated when |z| > 0.5

## Function
`pow` (double-precision power function)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/powd.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s4/src/mathd.rs` (line 3504, function `powd`)

## Failure Type
MISMATCH — wrong output

## Symptom
```
C:    pow 0x1p+1 0x1.4p+3 = 0x1p+10
Rust: pow 0x1p+1 0x1.4p+3 = 0x1.b2d809254afbcp+11
```
pow(2.0, 10.0) should return 1024.0 but Rust returns ~3557.5.

## Root Cause
In the C code (powd.c:410), when `|z| > 0.5`, the variable `p_h` is updated in place:
```c
p_h -= t;
```

In the Rust code (mathd.rs:3683-3685), this mutation is lost. The code creates a
local copy `p_h2`, subtracts from it, then discards the result with `let _ = p_h2`:
```rust
let mut p_h2 = p_h;
p_h2 = p_h2 - t_var;
let _ = p_h2;
```

The original `p_h` is never modified, so the subsequent computation
`tt = p_l + p_h` (line 3688) uses the wrong value. This corrupts the final
exponentiation result.

## Fix
In `mathd.rs`, replace lines 3683-3685:
```rust
let mut p_h2 = p_h;
p_h2 = p_h2 - t_var;
let _ = p_h2;
```
with a direct mutation of `p_h`. Since `p_h` is currently immutable (bound by
`let`), it must be declared mutable earlier (or shadowed). The cleanest fix:

Change the `let p_h = y1 * t1;` binding (line 3657) to `let mut p_h = ...;`, then
replace the dead-code block with:
```rust
p_h -= t_var;
```

## Success Criteria
- `pow 0x1p+1 0x1.4p+3` produces `0x1p+10` (matches C output exactly)
- This also fixes `exp2` since `exp2d` calls `powd(2.0, x)`:
  `exp2 0x1.8p+1` must produce `0x1p+3` (matches C output exactly)
- All other pow and exp2 tests continue to pass
