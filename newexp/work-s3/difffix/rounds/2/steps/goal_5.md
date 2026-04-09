# Goal 5: Fix cproj/cprojf — wrong infinity projection

## Functions
`cproj` (double), `cprojf` (float)

## Source Files
- C sources: `/home/leochanj/Desktop/libmcs/libm/complexd/cprojd.c`, `/home/leochanj/Desktop/libmcs/libm/complexf/cprojf.c`
- Rust sources: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexd.rs` (~line 122), `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/complexf.rs` (~line 120)

## Problem
Wrong imaginary part for infinity inputs. Per C standard, cproj should return (inf, copysign(0, imag)) when either component is infinite. Rust returns (inf, inf) instead.

Failing cases:
- `cproj(inf, -inf)`: expected `(inf, -0x0p+0)`, got `(inf, inf)`
- `cproj(nan, inf)`: expected `(inf, 0x0p+0)`, got `(inf, inf)`
- Same pattern for cprojf.

## What Needs to Change
The Rust implementation needs to detect when either real or imaginary part is infinite, and return `(INFINITY, copysign(0.0, imag))` in that case. Read the C source to confirm the exact logic.

## Success Criteria
- `cproj(inf, -inf)` returns `(inf, -0x0p+0)` — bitwise match with C
- `cproj(nan, inf)` returns `(inf, 0x0p+0)` — bitwise match with C
- `cprojf(inf, -inf)` returns `(inf, -0x0p+0)` — bitwise match with C
- `cprojf(nan, inf)` returns `(inf, 0x0p+0)` — bitwise match with C
- All other cproj/cprojf test cases continue to pass
