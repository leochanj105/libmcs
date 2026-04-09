# Goal 5: Fix ilogb, ilogbf, and logb subnormal/zero handling

## Functions
- ilogb (integer log base 2, double)
- ilogbf (integer log base 2, float)
- logb (log base 2 exponent, double)

## Source Files
- C source (ilogb): /home/leochanj/Desktop/libmcs/libm/mathd/ilogbd.c
- C source (ilogbf): /home/leochanj/Desktop/libmcs/libm/mathf/ilogbf.c
- C source (logb): /home/leochanj/Desktop/libmcs/libm/mathd/logbd.c
- Rust source (mathd): /home/leochanj/Desktop/libmcs/newexp/rust-s5/src/mathd.rs
- Rust source (mathf): /home/leochanj/Desktop/libmcs/newexp/rust-s5/src/mathf.rs

## What's Wrong

**ilogb (5 mismatches):**
- ilogb(0): C returns -2147483647 (INT_MAX negated = FP_ILOGB0), Rust returns -2147483648 (INT_MIN)
- ilogb(5e-324) and subnormals: C returns -1074, Rust returns -1075 (off by 1)

**ilogbf (1 mismatch):**
- ilogbf(0): C returns -2147483647, Rust returns -2147483648

**logb (3 mismatches):**
- logb(5e-324): C returns -1074.0, Rust returns -1075.0 (off by 1 for subnormals)

## What Needs to Change
1. **FP_ILOGB0 constant**: The C library defines FP_ILOGB0 as -2147483647 (INT_MAX negated). The Rust code uses -2147483648 (INT_MIN). Fix the zero case to return the correct constant.
2. **Subnormal exponent calculation**: The subnormal bit-counting loop is off by 1. The C code likely counts leading zeros differently. Compare the normalization loop in both implementations.

## Success Criteria
- ilogb(0) = -2147483647
- ilogbf(0) = -2147483647
- ilogb(5e-324) = -1074
- logb(5e-324) = -1074.0
- All ilogb, ilogbf, and logb test cases match C output bitwise
