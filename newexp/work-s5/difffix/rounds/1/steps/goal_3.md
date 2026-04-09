# Goal 3: Fix log1pf completely broken

## Function
log1pf (log(1+x), float precision)

## Source Files
- C source: /home/leochanj/Desktop/libmcs/libm/mathf/log1pf.c
- Rust source: /home/leochanj/Desktop/libmcs/newexp/rust-s5/src/mathf.rs

## What's Wrong
log1pf produces completely wrong results — it appears to not implement the log1p algorithm at all:

| Input | C result | Rust result |
|-------|----------|-------------|
| -2.0 | nan | -4.0 |
| -1.0 | -inf | -2.0 |
| -0.5 | -0x1.62e43p-1 | -1.0 |

The pattern suggests Rust may be computing `2*x` or `log(x)` instead of `log(1+x)`.
There are 6 mismatches total, plus 3 more hidden.

## What Needs to Change
The log1pf implementation needs to be compared line-by-line with the C source.
The core algorithm is likely completely wrong — possibly a mistranslation or the function body was replaced with something else during transpilation.

## Success Criteria
- log1pf(-1.0f) = -inf
- log1pf(-2.0f) = nan (with appropriate NaN handling)
- log1pf(-0.5f) = -0x1.62e43p-1
- log1pf(0.3f), log1pf(0.5f), log1pf(1.0f) all match C output bitwise
- All log1pf test cases pass
