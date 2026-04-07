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

## Source 2: Core-math worst cases

- **Origin:** `coremath_repo/src/binary64/*/FUNC.wc` and `coremath_repo/src/binary32/*/FUNCf.wc`
  from https://gitlab.inria.fr/core-math/core-math.git (INRIA)
- **License:** Various (see core-math repo)
- **Format:** One hex float per line (unary), or `x,y` (binary like pow, atan2)
  - Comments with `#`, inline comments after values
  - Special entries: `+snan`, `+nan`, `+inf`, `+0` — skipped (not hex floats)
  - Some functions are symmetric (tanh, sinh, etc.) — we also test -x
- **Cap:** `MAX_PER_FUNC` inputs per function (configurable, currently uncapped/500)
- **Functions included:** 27 binary64 functions + 3 binary32 (atan2f, powf, hypotf)
  that map to libmcs functions. Functions not in libmcs (acospi, sincos, rsqrt, etc.) skipped.
- **Generator:** `gen_wc_tests.py`
- **Output:** `tests/test_wc_bitwise.c`

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
gcc -I$INCDIR tests/test_wc_bitwise.c $C_LIB -fno-builtin -lm -o test_wc_c

# Compile against Rust lib:
gcc -I$INCDIR tests/test_glibc_bitwise.c $RUST_LIB -fno-builtin -lm -lpthread -ldl -o test_glibc_r
gcc -I$INCDIR tests/test_wc_bitwise.c $RUST_LIB -fno-builtin -lm -lpthread -ldl -o test_wc_r

# Diff:
diff <(./test_glibc_c) <(./test_glibc_r)
diff <(./test_wc_c) <(./test_wc_r)
```

## Verification checklist
- [ ] gen_glibc_tests.py: every input line in auto-libm-test-in for supported functions produces a printf
- [ ] gen_wc_tests.py: every non-comment, non-special line in .wc files produces a printf
- [ ] Both test files compile cleanly against C libmcs with `gcc -Wall`
- [ ] Both test files compile cleanly against Rust lib
- [ ] Output line count matches expected test count
- [ ] No test accidentally calls system libm (verify with -fno-builtin + whole-archive linking)
