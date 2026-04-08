# Goal 3: Implement __ccoshsinh and __ccoshsinhf (not implemented)

## Functions
- `__ccoshsinh` (complex double internal helper)
- `__ccoshsinhf` (complex float internal helper)

## Source Files
- **C source**: `/home/leochanj/Desktop/libmcs/libm/complexd/internal/ctrigd.c` (__ccoshsinh)
- **C source**: `/home/leochanj/Desktop/libmcs/libm/complexf/internal/ctrigf.c` (__ccoshsinhf)
- **Rust source**: not implemented
- **Target Rust files**: `/home/leochanj/Desktop/libmcs/newexp/rust-s1/src/complexd.rs` and `complexf.rs`

## Problem
These two internal helper functions have no Rust implementation. The test binary currently falls back to the C versions, masking any divergence. They need native Rust implementations for the transpilation to be complete.

These helpers are used by complex trigonometric/hyperbolic functions (ccosh, csinh, ctanh, ccos, csin, ctan and their float variants). Without Rust implementations, the complex functions partially rely on C code.

## What Needs to Change
1. Read the C source files to understand the algorithm
2. Transpile `__ccoshsinh` into `complexd.rs`
3. Transpile `__ccoshsinhf` into `complexf.rs`
4. Export them from `lib.rs` with `#[no_mangle]` if the test binary calls them directly
5. Update complex trig/hyperbolic functions to call the Rust versions instead of the C fallback

## Success Criteria
- `__ccoshsinh` and `__ccoshsinhf` are implemented in Rust
- Complex trig/hyperbolic functions use the Rust implementations
- No C fallback is needed for these functions
- All complex function test cases that depend on these helpers produce bitwise-exact output matching C
