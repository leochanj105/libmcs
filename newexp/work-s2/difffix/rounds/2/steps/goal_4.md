# Goal 4: Fix lgamma signgam output

## Function
`lgamma` (delegates to `lgammad`)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/lgammad.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s2/src/mathd.rs` (line ~3334)
- Also see: `lgamma_r` at mathd.rs line ~616

## Problem
**Wrong output.** `lgamma(-0.5)` sets `signgam = 0` in Rust but `signgam = -1` in C. The log-gamma value itself may be correct, but the sign indicator (the global `signgam` variable) is not being set properly for negative arguments.

## What Needs to Change
The Rust `lgammad` must correctly set the global `signgam` variable. For `x = -0.5`, gamma is negative so `signgam` must be `-1`. Check how `lgamma_r` computes the sign and how it's propagated to the global `signgam`.

## Success Criteria
- `lgamma(-0x1p-1)` sets `signgam = -1` (matching C output)
