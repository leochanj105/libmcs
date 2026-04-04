# libmcs C-to-Rust Transpilation Experiment

Comparison of two transpilation runs using the same diff-test-fix loop,
differing only in testgen coverage guidance.

---

## Directory Structure

```
experiment/
├── README.md                        — this file
├── comparison_report.md             — full analysis with concrete examples
│
├── function_coverage/               — Run 1: function-level coverage guidance
│   ├── results/
│   │   ├── default_test_results.txt — SDD+Newlib C-vs-Rust divergences (737 total)
│   │   ├── coremath_results.txt     — coremath_repo check_special results (recovered from git)
│   │   ├── newlib_diff_report.txt   — diff between two newlib runs
│   │   └── newlib_regressions.txt   — individual newlib FAIL lines
│   └── NOTE: Rust source not preserved — overwritten by fresh transpile
│
└── branch_coverage/                 — Run 2: LLVM branch coverage guidance (83.8%)
    ├── test_suite.c                 — generated test suite (3409 tests, branch-guided)
    ├── fix_journal.md               — what the fix loop did each round
    ├── rust_source/
    │   ├── rust_before_fixes.tar.gz — fresh transpile before any fix rounds
    │   ├── rust_before_fixes.meta
    │   ├── rust_after_fixes.tar.gz  — after round 1 (round 2 = current rust-libmcs/)
    │   └── rust_after_fixes.meta
    └── results/
        ├── bitwise_diff_report.txt  — SDD+Newlib C-vs-Rust summary (32 total)
        ├── sdd_bitwise_diff.txt     — SDD line-by-line diffs (32, all -nan vs nan)
        ├── newlib_bitwise_diff.txt  — Newlib diffs (empty: 0 divergences)
        └── coremath_results.txt     — coremath_repo check_special results
```

---

## Key Results — C vs Rust Bitwise Divergences

| Test Suite | Cases | Function coverage | Branch coverage | Delta |
|---|---|---|---|---|
| SDD | 364 | 32 (-nan vs nan) | 32 (-nan vs nan) | 0 |
| Newlib | 15,349 | **705** (real 1-ULP errors) | **0** | **-705** |
| CoreMath (deterministic) | 2,982 | n/a (old Rust gone) | 316 (-nan vs nan) | — |
| **Real math errors** | | **705** | **0** | **-705** |

All remaining divergences in branch_coverage are `-nan` vs `nan` sign-bit differences
on out-of-domain inputs — present in both runs, not real math errors.

---

## What is/isn't preserved

| Artifact | Preserved? | Location |
|---|---|---|
| Old Rust source (function-coverage) | **NO** — overwritten by fresh transpile | — |
| Old test suite (168 tests) | **NO** — overwritten by testgen | — |
| Old coremath results | YES — recovered from git | function_coverage/results/coremath_results.txt |
| Old SDD+Newlib results | YES | function_coverage/results/default_test_results.txt |
| New Rust source (current) | YES | rust-libmcs/ (live) |
| New Rust before fixes | YES | branch_coverage/rust_source/rust_before_fixes.tar.gz |
| New test suite (3409 tests) | YES | branch_coverage/test_suite.c |
| New test results | YES | branch_coverage/results/ |
