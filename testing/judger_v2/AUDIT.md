# Judger V2 — Audit Document

## Overview

Two test sources compiled into bitwise-print C test files. Each test prints
`funcname input(s) = result` in `%a` hex-float format. Compile against C lib
and Rust lib separately, diff outputs for bitwise comparison.

## Source 1: GLIBC libm-test

- **Origin:** `glibc_repo/math/auto-libm-test-in` from https://sourceware.org/git/glibc.git
- **License:** LGPL 2.1+
- **Format:** One test per line: `funcname arg1 [arg2 ...]`
  - Symbolic constants: `inf`, `-inf`, `nan`, `min` (DBL_MIN), `min_subnorm`,
    `max` (DBL_MAX), `pi`, `pi/2`, `pi/4`, etc.
  - Hex floats: `0x1.fp+10`, `-0x0.ffffffp0`
  - Decimal: `0.5`, `2e-17`
- **No expected outputs used.** We only extract inputs and print computed results
  for C-vs-Rust diffing. The `auto-libm-test-out-*` files are not used.
- **Functions included:** Only functions that exist in libmcs (see gen_glibc_tests.py
  for the exact list). Functions not in libmcs (acospi, pown, compoundn, etc.) are skipped.
- **Generator:** `gen_glibc_tests.py`
- **Output:** `tests/test_glibc_bitwise.c`

### Porting notes
- Each line `funcname arg1 [arg2]` becomes a printf that calls the function and prints in %a
- Symbolic constants are mapped to C macros (#define'd in the header)
- Complex function args `re im` become `CMPLX(re, im)` calls
- Lines with unsupported syntax (flags, comments) are skipped
- jn/yn have integer first arg: `jn 3 1.5` → `jn(3, 1.5)`

## Source 2: GLIBC libm-test-*.inc (non-transcendental functions)

- **Origin:** `glibc_repo/math/libm-test-*.inc` files from the same glibc clone
- **License:** LGPL 2.1+
- **Format:** C struct initializers using TEST_xxx macros, e.g.:
  - `TEST_f_f (ceil, 0.0, 0.0, NO_INEXACT_EXCEPTION|ERRNO_UNCHANGED)`
  - `TEST_ff_f (copysign, 0, 4, 0, ...)`
  - `TEST_fi_f (scalbn, 0.8L, 4, 12.8L, ...)`
  - `TEST_c_c (conj, 0.0, 0.0, 0.0, minus_zero, ...)`
- **Why separate:** Functions like ceil, floor, fmod, copysign, etc. are NOT in
  `auto-libm-test-in` — they only exist in the `.inc` files with a different format.
- **Preprocessor handling:** Conditional blocks (`#if TEST_COND_binary32`,
  `#if MANT_DIG >= 64`, etc.) are evaluated for binary64 on 64-bit Linux.
- **Functions included (28):**
  - Rounding (6): ceil, floor, trunc, round, rint, nearbyint
  - Absolute/difference (2): fabs, fdim
  - Min/max (2): fmax, fmin
  - Division/remainder (3): fmod, remainder, remquo
  - Exponent manipulation (4): logb, ilogb, scalbn, scalbln
  - Sign/adjacent (3): copysign, nextafter, nexttoward
  - Decomposition (2): frexp, modf
  - Integer rounding (4): lrint, lround, llrint, llround
  - Complex (2): conj, cproj
- **Generator:** `gen_glibc_inc_tests.py`
- **Output:** `tests/test_glibc_inc_bitwise.c`

### Porting notes
- Each TEST_xxx macro line becomes a printf that calls the function and prints in %a
- Symbolic constants are mapped: `plus_infty`→`INFINITY`, `minus_zero`→`(-0.0)`,
  `min_value`→`DBL_MIN`, `max_value`→`DBL_MAX`, `lit_pi`→`M_PI`, etc.
- Integer-returning functions (ilogb, lrint, lround, llrint, llround) print with %d/%ld/%lld
- Functions with pointer output args (frexp, modf, remquo) print all outputs
- Complex functions (conj, cproj) use CMPLX() and print real/imag parts
- Expressions like `min_value / 2` are passed through as C expressions
- L suffixes (long double literals) are stripped for double-precision testing

## Source 3: Core-math worst cases

- **Origin:** `coremath_repo/src/binary64/*/FUNC.wc` and `coremath_repo/src/binary32/*/FUNCf.wc`
  from https://gitlab.inria.fr/core-math/core-math.git (INRIA)
- **License:** Various (see core-math repo)
- **Format:** One hex float per line (unary), or `x,y` (binary like pow, atan2)
  - Comments with `#`, inline comments after values
  - Special entries: `+snan`, `+nan`, `+inf`, `+0` — skipped (not hex floats)
  - Some functions are symmetric (tanh, sinh, etc.) — we also test -x
- **Cap:** None (all worst cases used).
- **Functions included:** 27 binary64 functions + 3 binary32 (atan2f, powf, hypotf)
  that map to libmcs functions. Functions not in libmcs (acospi, sincos, rsqrt, etc.) skipped.
- **Binary32 coverage:** Only 6 binary32 functions have .wc files (atan2f, atan2pif,
  compoundf, hypotf, lgammaf, powf). Of those, 3 map to libmcs (atan2f, hypotf, powf).
  lgammaf.wc exists but is empty. Most binary32 functions rely on exhaustive 2^32 testing
  in core-math's check infrastructure rather than worst-case files.
- **Generator:** `gen_wc_tests.py`
- **Output:** Per-function files in `tests/wc/` + `tests/wc_manifest.txt`

### Porting notes
- Each .wc line becomes a printf calling the function with that input
- Inline `# comments` are stripped before use
- For symmetric functions, both +x and -x are tested
- Binary functions (pow, atan2, hypot): entries are `x,y` pairs
- Float literals: bare integers get `.0f` suffix (e.g., `1` → `1.0f`)
- Special values mapped: `+inf`→`INFINITY`, `nan`→`NAN`, `+snan`→`__builtin_nans("")`, `+0`→`0.0`, etc.

## Running

```bash
# Compile against C lib:
gcc -I$INCDIR tests/test_glibc_bitwise.c $C_LIB -fno-builtin -lm -o test_glibc_c
gcc -I$INCDIR tests/test_glibc_inc_bitwise.c $C_LIB -fno-builtin -lm -o test_glibc_inc_c
gcc -I$INCDIR tests/wc/wc_sin.c $C_LIB -fno-builtin -lm -o test_wc_sin_c  # per-function

# Compile against Rust lib:
gcc -I$INCDIR tests/test_glibc_bitwise.c $RUST_LIB -fno-builtin -lm -lpthread -ldl -o test_glibc_r
gcc -I$INCDIR tests/test_glibc_inc_bitwise.c $RUST_LIB -fno-builtin -lm -lpthread -ldl -o test_glibc_inc_r
gcc -I$INCDIR tests/wc/wc_sin.c $RUST_LIB -fno-builtin -lm -lpthread -ldl -o test_wc_sin_r

# Diff:
diff <(./test_glibc_c) <(./test_glibc_r)
diff <(./test_glibc_inc_c) <(./test_glibc_inc_r)
diff <(./test_wc_sin_c) <(./test_wc_sin_r)
```

## Test coverage summary

| Source | Generator | Functions | Test cases |
|--------|-----------|-----------|------------|
| glibc auto-libm-test-in | gen_glibc_tests.py | 50 (transcendental + complex) | ~3,900 |
| glibc libm-test-*.inc | gen_glibc_inc_tests.py | 28 (rounding, manipulation, etc.) | ~1,900 |
| core-math .wc files | gen_wc_tests.py | 27 binary64 + 3 binary32 | ~16.3M |

### Functions NOT tested (implemented in libmcs but no external test data)

- **nan**: trivial constructor, no glibc test vectors
- **ldexp**: no .inc file in glibc (tested via scalbn, same underlying operation)
- **cimag/creal**: trivial accessors

### Functions NOT implemented in libmcs (excluded from all tests)

- clog10, sincos, acospi, asinpi, atanpi, cospi, sinpi, tanpi
- exp10, exp10m1, exp2m1, log10p1, log2p1
- rsqrt, rootn, pown, powr, compoundn

## Verification checklist
- [ ] gen_glibc_tests.py: every input line in auto-libm-test-in for supported functions produces a printf
- [ ] gen_glibc_inc_tests.py: every TEST_xxx line in .inc files for supported functions produces a printf
- [ ] gen_wc_tests.py: every non-comment, non-special line in .wc files produces a printf
- [ ] All three test files compile cleanly against C libmcs with `gcc -Wall`
- [ ] All three test files compile cleanly against Rust lib
- [ ] Output line count matches expected test count
- [ ] No test accidentally calls system libm (verify with -fno-builtin + whole-archive linking)
