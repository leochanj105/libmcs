# Goal 1: Fix ctanf timeout (CRITICAL BLOCKER)

## Function
ctanf (complex tangent, float precision)

## Source Files
- C source: /home/leochanj/Desktop/libmcs/libm/complexf/ctanf.c
- Rust source: /home/leochanj/Desktop/libmcs/newexp/rust-s5/src/complexf.rs

## What's Wrong
The Rust test binary hangs (infinite loop or infinite recursion) when computing `ctanf(0.5-50i)`.
Last output before hang: `ctanf 0.5-50i = 0x0p+0+-nani`
This timeout blocks ~1000+ subsequent tests from running.

Additionally, `ctanf(pi/2+0.001i)` produces wrong real part:
- C:    `0x1.353d4p-4 + 0x1.f4000ap+9i`
- Rust: `-0x1.575216p+3 + 0x1.f4000ap+9i`

## What Needs to Change
1. Identify the infinite loop/recursion in ctanf for large imaginary inputs (|imag| >= 50)
2. Compare with C implementation — likely missing an early return or overflow guard for large imaginary parts
3. Fix the computation for inputs near pi/2 with small imaginary part

## Dependencies
ctanf may call __ctansf and __ccoshsinhf internally. Check those helpers too.
Also check __redupif which reduces the real part.

## Success Criteria
- `ctanf(0.5-50i)` completes without hanging and produces the correct result
- `ctanf(pi/2+0.001i)` matches C output bitwise: `0x1.353d4p-4+0x1.f4000ap+9i`
- All ctanf test cases pass
- The test binary no longer times out, allowing all subsequent tests to run
