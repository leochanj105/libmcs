# Goal 5: Fix lgamma / lgammaf — signgam always 0 instead of correct sign

## Function
- `lgamma` (double)
- `lgammaf` (float)

## Source Files
- C: `/home/leochanj/Desktop/libmcs/libm/mathd/lgammad.c` (lgamma)
- C: `/home/leochanj/Desktop/libmcs/libm/mathf/lgammaf.c` (lgammaf)
- Rust: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathd.rs` line ~3334 (lgammad)
- Rust: `/home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathf.rs` line ~1999 (lgammaf)

## Problem
MISMATCH: The lgamma/lgammaf return values are correct, but signgam is always 0
in Rust instead of the correct sign (+1 or -1).

Failing tests (lgamma, 10 mismatches):
- lgamma(1.0): C signgam=1, Rust signgam=0
- lgamma(2.0): C signgam=1, Rust signgam=0
- lgamma(0.5): C signgam=1, Rust signgam=0
- (7 more with same pattern)

Failing tests (lgammaf, 6 mismatches):
- lgammaf(1.0): C signgam=1, Rust signgam=0
- lgammaf(0.5): C signgam=1, Rust signgam=0
- lgammaf(inf): C signgam=1, Rust signgam=0
- (3 more)

## What Needs to Change
The Rust lgamma/lgammaf implementations are not setting the global signgam variable.
The C code writes to an external `signgam` global. The Rust bridge or implementation
must similarly update the signgam variable to +1 or -1 to match C behavior.

## Success Criteria
- All 10 lgamma test cases produce correct signgam values matching C exactly
- All 6 lgammaf test cases produce correct signgam values matching C exactly
- Return values remain correct (they already match)
