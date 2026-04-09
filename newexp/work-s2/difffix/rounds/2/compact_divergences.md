# Compact Divergences — Round 2

5 mismatches across 5 functions. 0 compile errors. 0 runtime panics. 0 missing.

## Mismatches

| # | Function | Type | Input | C Output | Rust Output | Root Cause Summary |
|---|----------|------|-------|----------|-------------|-------------------|
| 1 | `pow` | wrong output | `pow(0x1p+1, 0x1.4p+3)` = `pow(2, 10)` | `0x1p+10` (1024) | `0x1.b2d809254afbcp+11` (~3494) | Bug in `powd` computation; result is wildly wrong for an exact integer power |
| 2 | `exp2` | wrong output | `exp2(0x1.4p+3)` = `exp2(10)` | `0x1p+10` (1024) | `0x1.b2d809254afbcp+11` (~3494) | `exp2d` delegates to `powd(2.0, x)` — same as C; inherits `powd` bug |
| 3 | `lgamma` | wrong signgam | `lgamma(-0x1p-1)` = `lgamma(-0.5)` | `signgam=-1` | `signgam=0` | `signgam` global not set correctly; `lgamma_r` likely returns 0 instead of -1 for sign |
| 4 | `nexttoward` | wrong direction | `nexttoward(0x1p+0, 0x8p-2)` = `nexttoward(1.0, 2.0)` | `0x1.0000000000001p+0` (step up) | `0x1.fffffffffffffp-1` (step down) | `nexttowardd` delegates to `nextafterd`; direction logic bug in `nextafterd` |
| 5 | `nexttowardf` | wrong direction | `nexttowardf(0x1p+0, 0x8p-2)` = `nexttowardf(1.0, 2.0)` | `0x1.000002p+0` (step up) | `0x1.fffffep-1` (step down) | Direction comparison or bit manipulation bug in `nexttowardf` |

## Dependency Graph

- Fixing `powd` will fix both `pow` and `exp2` (2 goals → 1 root fix)
- `nexttoward` and `nexttowardf` are independent implementations
- `lgamma` signgam issue is independent
