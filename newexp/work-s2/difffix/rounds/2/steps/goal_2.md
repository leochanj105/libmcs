# Goal 2: Fix `lgamma` signgam output

## Function
- `lgamma` (double)

## Source Files
- C source: `/home/leochanj/Desktop/libmcs/libm/mathd/lgammad.c`
- Rust source: `/home/leochanj/Desktop/libmcs/newexp/rust-s2/src/mathd.rs` — `lgammad` at line 3334
- Rust wrapper: `/home/leochanj/Desktop/libmcs/newexp/rust-s2/src/lib.rs` — `lgamma` at line 71

## What's Wrong
**Wrong signgam value.** For `lgamma(-0.5)`, C sets `signgam = -1` but Rust sets `signgam = 0`. The return value of lgamma itself may be correct — the issue is with how `signgam` is communicated.

The Rust chain is:
1. `lgamma()` in lib.rs calls `mathd::lgammad(x)`
2. `lgammad()` calls `lgamma_r(x, &mut s)` then stores `s` in thread-local `SIGNGAM`
3. `lgamma()` reads `SIGNGAM` and writes it to the global `signgam`

## Failing Test
```
lgamma -0x1p-1:   C signgam=-1,   Rust signgam=0
```

## What Needs to Change
Check the `lgamma_r` implementation to verify it correctly sets the sign parameter to -1 for negative x values where Gamma(x) < 0. For x = -0.5, Gamma(-0.5) = -2*sqrt(pi) which is negative, so signgam must be -1. The bug is likely in `lgamma_r` not setting the sign output correctly, or initializing it to 0 instead of 1/-1.

## Success Criteria
- `lgamma(-0.5)` returns the correct value AND sets `signgam = -1` (bitwise exact match with C)
- All other currently-passing lgamma tests continue to pass
