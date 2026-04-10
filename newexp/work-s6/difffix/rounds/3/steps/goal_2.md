# Goal 2: Fix log1pf — completely wrong for negative inputs

## Function
`log1pf`

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathf/log1pf.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s6/src/mathf.rs` (`log1pf` at line 2099)

## Problem
MISMATCH — 9 test failures.

```
C:    log1pf -1.0f  = -inf
Rust: log1pf -1.0f  = -0x1p+1            (-2)
C:    log1pf -2.0f  = nan
Rust: log1pf -2.0f  = -0x1p+2            (-4)
C:    log1pf -0.9f  = -0x1.26bb1ap+1     (~-2.30)
Rust: log1pf -0.9f  = -0x1.ccccccp+0     (~-1.80)
... (6 more)
```

The Rust output for negative `x` looks like simply `2*x`, i.e. some early-exit
or special-case branch returns `x + x` (or fails to enter the actual log
computation). The function is not detecting `x == -1` (should be `-inf`),
not detecting `x < -1` (should be `nan`), and not actually evaluating
`log(1+x)` for valid negative inputs.

## What Needs to Change
Inspect the Rust `log1pf` against the C version. Likely issues:
- A special-case `if (x == 0)` style branch that incorrectly returns `x+x` for
  ordinary negative values. The C code uses `if (k == 0) { ... return x; }`
  only when `|x|` is near zero — make sure the threshold check matches.
- Missing handling of the `hx == 0xbf800000` (i.e. `x == -1.0f`) case that
  should return `-inf` (and raise divide-by-zero).
- Missing `hx > 0xbf800000` range check that should produce `(x-x)/(x-x)` (NaN)
  for `x < -1`.
- The main polynomial / log computation path is being skipped entirely for
  negative inputs.

Port the missing branches from the C `log1pf` so all four code paths
(special-near-zero, x==-1, x<-1, ordinary) are present.

## Success Criteria
- `log1pf(-1.0f)` returns `-inf`.
- `log1pf(-2.0f)` returns `nan`.
- `log1pf(-0.9f)` returns `-0x1.26bb1ap+1` (bitwise exact).
- All 9 log1pf mismatches resolve to bitwise-exact match with C output.
