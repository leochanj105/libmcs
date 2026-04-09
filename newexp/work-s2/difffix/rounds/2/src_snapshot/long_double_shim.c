/*
 * ABI shim for functions with long double parameters.
 *
 * On x86-64 Linux, `long double` (80-bit x87) is passed on the stack,
 * not in an XMM register. Rust's `extern "C"` with `f64` would incorrectly
 * read from XMM1 instead of the stack. This C shim receives the long double
 * with the correct ABI, casts it to double, and calls the Rust implementation.
 */

extern double __nexttoward_impl(double x, double y);
extern float  __nexttowardf_impl(float x, double y);

double nexttoward(double x, long double y)
{
    return __nexttoward_impl(x, (double) y);
}

float nexttowardf(float x, long double y)
{
    return __nexttowardf_impl(x, (double) y);
}
