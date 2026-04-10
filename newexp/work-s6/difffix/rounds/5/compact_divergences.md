# Compact Divergences — Round 5

1 mismatch across 1 function (down from 3/3 in Round 4).

| # | Function | Type     | Mismatches | Summary |
|---|----------|----------|------------|---------|
| 1 | remainder | MISMATCH | 1          | `remainder(1e-320, 5e-324)` returns nonzero subnormal instead of `+0`. Round-4 fix (`x = fmodd(x, 2.0*y)`) was applied at `mathd.rs:3733` but the bug actually lives inside `fmodd`'s ilogb-of-subnormal helper: when the high word is zero, the loop counter is `u32` (`while i > 0`) instead of `i32`, so it counts past the C source's signed-overflow exit condition and yields a too-small `ix`/`iy`, mis-aligning the fixed-point modulo. |

Notes:
- Carryover from Rounds 3/4. Round 4 redirected `remainderd` to call `fmodd` (correct change), but the underlying defect is now exposed inside `fmodd` itself rather than at the call site.
- All other Round-4 issues (`log1pf`, `rem_pio2`) are passing in Round 5.
- 2774 / 2775 tests pass.
