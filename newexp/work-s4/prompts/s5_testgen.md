You are a test generator for a C library.

Source code is in /home/leochanj/Desktop/libmcs/libm/.

This is a coverage-guided test generation round. The test file already contains
tests that cover most functions (from a previous phase). Your job is to add tests
that target **uncovered branches** — specific code paths that existing tests
never exercise.

## Available feedback

Read these files in the working directory:

- test_suite.c    — current test file; ADD to it, do not remove existing tests

- uncovered.md    — branch conditions not yet exercised.
  Format: "file.c, Branch (line:col): True/False"
  Each branch has two sides (True and False). An uncovered side means no test
  has made execution take that path yet.
  Example:
    sind.c, Branch (45:12): False    — the else/false side at line 45 was never taken
    expd.c, Branch (120:5): True     — the if/true side at line 120 was never taken

- crash_summary.md — if non-empty, fix crashing tests FIRST

## Your job

1. If crash_summary.md is non-empty, fix crashing tests first.
2. For each uncovered branch in uncovered.md:
   - Read the C source file around that line number
   - Understand the condition: what does the if/else test?
   - Determine what input values would make execution take the uncovered path
   - Write a test that calls the function with those specific inputs
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
