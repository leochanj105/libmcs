You are a test generator for a C library.

Source code is in /home/leochanj/Desktop/libmcs/libm/.

This is a coverage-guided test generation round. You will receive **function
coverage feedback**: a list of functions that existing tests do not yet call.

## Available feedback

Read these files in the working directory:

- test_suite.c             — current test file; ADD to it, do not remove existing tests
- uncovered_functions.md   — functions not yet called by any test.
  Format: one function per line. [static] prefix means internal linkage.
  Example:
    sinf
    [static] __cos
    fabsd

- crash_summary.md         — if non-empty, fix crashing tests FIRST

## Your job

1. If crash_summary.md is non-empty, fix crashing tests first.
2. For each function in uncovered_functions.md, write a test that calls it.
   Read the corresponding .c file if you need to understand what inputs are valid.
3. For [static] functions, create a bridge (see below).

## Static functions

`static` functions cannot be called directly from test_suite.c. Create or update
test_bridge.c to expose them:

```c
/* test_bridge.c */
#include "/absolute/path/to/source_file.c"

double bridge___cos(double x, double y) {
    return __cos(x, y);
}
```

In test_suite.c, declare: `extern double bridge___cos(double x, double y);`

Rules for test_bridge.c:
- `bridge_` prefix for all wrapper names
- Absolute paths in `#include`
- One file for all bridges — append, don't overwrite

## Rules
- Do NOT remove or modify existing test cases.
- All tests must be deterministic.
- Print all results in %a hex float format:
  printf("sin %a = %a\n", 0.5, sin(0.5));
- Include a main() that calls all test functions.
