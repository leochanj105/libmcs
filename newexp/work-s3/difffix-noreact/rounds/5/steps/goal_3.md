# Goal 3: Fix logb off-by-one for smallest subnormal double

## Function
- `logbd` (double binary exponent)

## Source files
- C: `/home/leochanj/Desktop/libmcs/libm/mathd/logbd.c`
- Rust: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathd.rs` (line ~3103, `logbd`)

## What's wrong
| Input | C result | Rust result |
|-------|----------|-------------|
| logb(0x0.0000000000001p-1022) | -0x1.0c8p+10 (-1074) | -0x1.0ccp+10 (-1075) |

The input is `2^(-1074)`, the smallest positive subnormal double (bits = `0x0000000000000001`). Correct answer is -1074 but Rust returns -1075 (off by one).

## Root cause (confirmed)
In the subnormal branch where `hx == 0`, the Rust code is:
```rust
let mut ix = -1043i32;
while lx > 0 {
    ix -= 1;
    lx <<= 1;
}
return ix as f64;
```

The C code is:
```c
for (ix = -1043; lx > 0; lx <<= 1) {
    ix -= 1;
}
```

**Critical difference:** In C, `lx` is declared as `int32_t` (signed). The loop condition `lx > 0` uses signed comparison. When `lx` is shifted left until the MSB (sign bit) is set, `lx` becomes negative and `lx > 0` is false — the loop stops.

In Rust, `lx` is `u32` (unsigned). The condition `lx > 0` remains true even when the MSB is set (0x80000000u32 > 0 is true). The loop runs one extra iteration before `lx` overflows to 0.

Trace for input lx=1:
- C: 31 iterations (1→2→4→...→0x40000000→stop at 0x80000000 because signed negative). ix = -1043 - 31 = -1074. ✓
- Rust: 32 iterations (1→2→...→0x40000000→0x80000000→stop at 0 after overflow). ix = -1043 - 32 = -1075. ✗

## What needs to change
Change the loop condition from unsigned to signed comparison:

```rust
// Before:
while lx > 0 {
    ix -= 1;
    lx <<= 1;
}

// After:
while (lx as i32) > 0 {
    ix -= 1;
    lx <<= 1;
}
```

This matches C's signed `int32_t` comparison semantics.

## Success Criteria
- `logb(0x0.0000000000001p-1022)` returns `-0x1.0c8p+10` (-1074) matching C
- `logb(0)` still returns `-inf`
- `logb(1.0)` still returns `0`
- `logb(inf)` still returns `inf`
- `logb(nan)` still returns `nan`
- All other existing logb tests continue to pass
