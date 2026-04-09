# Goal 5: Fix lgamma / lgammaf signgam global variable

## Function
lgamma (double), lgammaf (float)

## Source Files
- C (double): /home/leochanj/Desktop/libmcs/libm/mathd/lgammad.c
- C (float): /home/leochanj/Desktop/libmcs/libm/mathf/lgammaf.c
- Rust wrappers: /home/leochanj/Desktop/libmcs/newexp/rust-s3/src/lib.rs (lgamma line ~71, lgammaf line ~156)
- Rust impl (double): /home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathd.rs (fn lgammad, line ~3334)
- Rust impl (float): /home/leochanj/Desktop/libmcs/newexp/rust-s3/src/mathf.rs (fn lgammaf, line ~1999)

## What's Wrong
Output mismatch — 10 lgamma + 6 lgammaf mismatches. The computed values are correct, but `signgam` is always 0 in Rust instead of the correct sign (+1 or -1).

Examples:
- `lgamma(1.0)`: value matches, but C signgam=1, Rust signgam=0
- `lgamma(-0.5)`: value matches, but C signgam=-1, Rust signgam=0

## What Needs to Change
The Rust lgamma/lgammaf wrapper functions in lib.rs need to properly set the `signgam` global variable. Check how the C code sets signgam (likely via a pointer parameter or global). The Rust implementation must export and set a `signgam` global that the test harness reads, or properly wire through the sign output from the internal implementation.

## Success Criteria
- All lgamma test cases: signgam matches C output (1 or -1, never 0)
- All lgammaf test cases: signgam matches C output
- Computed lgamma/lgammaf values remain unchanged (they already match)
