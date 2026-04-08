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
3. For [static] functions, call them via the pre-built bridge wrappers (see below).

## Static functions

A pre-built test_bridge.c and test_bridge.h are provided in the working directory.
They expose these static functions as callable bridge wrappers:

    bridge___rem_pio2_internal(double *x, double *y, int e0, int nx)
    bridge___tan(double x, double y, int iy)
    bridge___sin_pi(double x)
    bridge___rem_pio2f_internal(float *x, float *y, int e0, int nx)
    bridge___tanf(float x, float y, int iy)
    bridge___ctans(double _Complex z)
    bridge___ctansf(float _Complex z)
    bridge___sin_pif(float x)

To use them, add `#include "test_bridge.h"` at the top of test_suite.c.
Do NOT generate or modify test_bridge.c or test_bridge.h.

## Rules
- Do NOT remove or modify existing test cases.
- All tests must be deterministic.
- Print all results in %a hex float format:
  printf("sin %a = %a\n", 0.5, sin(0.5));
- Include a main() that calls all test functions.
