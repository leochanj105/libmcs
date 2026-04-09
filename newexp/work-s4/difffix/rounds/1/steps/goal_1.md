# Goal 1: Fix __cosf constant C1 (wrong hex value)

## Function
`__cosf` (internal cosine kernel for float)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathf/internal/trigf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s4/src/mathf.rs` (line 483, function `cosf_kern`)

## Failure Type
MISMATCH — wrong output

## Symptom
```
C:    __cosf 0x1p+0 0x0p+0 = 0x1.14a282p-1
Rust: __cosf 0x1p+0 0x0p+0 = 0x1.14a284p-1
```

## Root Cause
The constant C1 has the wrong hex bit pattern. The C code defines:
```c
C1 = 0xaaaaa5.0p-28f;  /* hex float 0x3D2AAAA5 */
```
But the Rust code uses:
```rust
let c1 = f32::from_bits(0x3D2AAAAA);  // WRONG — last nibble is A, should be 5
```
The comment even shows the wrong hex: `0x3D2AAAAA` vs the correct `0x3D2AAAA5`.

## Fix
In `mathf.rs` line 483, change:
```rust
let c1 = f32::from_bits(0x3D2AAAAA);
```
to:
```rust
let c1 = f32::from_bits(0x3D2AAAA5);
```

## Success Criteria
- `__cosf 0x1p+0 0x0p+0` produces `0x1.14a282p-1` (matches C output exactly)
- All other __cosf tests continue to pass
