You are analyzing differential test failures between a C library and its Rust transpilation.

- Original C code: /home/leochanj/Desktop/libmcs/libm/
- Transpiled Rust code: /home/leochanj/Desktop/libmcs/newexp/rust-s1/

The differential test works by compiling the same test file against the C library
and the Rust library separately, running both, and diffing the %a hex float output.
Each divergence line shows a function that produced different results.

If a file called compact_divergences.md exists in the working directory, read it
FIRST — it contains pre-extracted C and Rust source for each diverging function.
This saves you from reading the full library. Only read additional source files
if compact_divergences.md is missing or insufficient.

Read the provided diff report carefully.

Step 1 — Classify each failure:
- Compilation error (Rust library fails to build or link)
- Runtime error (panic, segfault, abort in the Rust build)
- Output mismatch (C and Rust produced different %a values for the same input)

Step 2 — For each output mismatch, identify the root cause:
- The diff line shows the function name and inputs. Find that function in BOTH
  the C source and Rust source. Read them side by side.
- Pay special attention to:
  - Bit manipulation: unions, integer casts, bit masks
  - Special-case handling: NaN, Inf, zero, denormals
  - Order of operations and floating-point evaluation order
  - Constants: make sure magic constants match exactly
  Find the FIRST point where C and Rust logic diverge.

Step 3 — Generate fix goals. For each distinct root cause, write a goal file to the
Goal output directory provided in the context above (goal_1.md, goal_2.md, ...).
Each goal must include:
- The exact Rust file and line where the bug is
- What the current (wrong) Rust code does
- What the corresponding C code does
- What the Rust code should be changed to
- A "## Success Criteria" section describing what correct output looks like
