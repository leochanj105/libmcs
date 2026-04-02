/* Consolidated core-math style tests: random inputs compared against MPFR reference.
 * Tests all libmcs double and float functions with configurable test count.
 *
 * Compile: gcc -O2 -o test_coremath test_coremath.c LIBM.a -lmpfr -lgmp -lm -fno-builtin
 * Run:     ./test_coremath [num_tests]    (default: 100000)
 */
#include <math.h>
#include <mpfr.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fenv.h>

static int total_tests = 0, total_pass = 0, total_fail = 0;
static int func_tested = 0, func_pass = 0, func_fail = 0;
static uint64_t rng_state = 0x12345678DEADBEEF;

static uint64_t xorshift64(void) {
    uint64_t x = rng_state;
    x ^= x << 13; x ^= x >> 7; x ^= x << 17;
    rng_state = x;
    return x;
}

static double random_double(void) {
    union { uint64_t u; double d; } u;
    u.u = xorshift64();
    return u.d;
}

static float random_float(void) {
    union { uint32_t u; float f; } u;
    u.u = (uint32_t)xorshift64();
    return u.f;
}

/* Compare double result vs MPFR, report ULP difference */
static int check_d(const char *name, double x, double got, mpfr_t ref_mp) {
    double ref = mpfr_get_d(ref_mp, MPFR_RNDN);
    total_tests++;
    if (isnan(got) && isnan(ref)) { total_pass++; return 0; }
    if (got == ref) { total_pass++; return 0; }
    /* Allow 1 ULP */
    int64_t gi, ri;
    memcpy(&gi, &got, 8); memcpy(&ri, &ref, 8);
    int64_t diff = gi - ri; if (diff < 0) diff = -diff;
    if (diff <= 1) { total_pass++; return 0; }
    total_fail++;
    return 1;
}

static int check_f(const char *name, float x, float got, mpfr_t ref_mp) {
    float ref = mpfr_get_flt(ref_mp, MPFR_RNDN);
    total_tests++;
    if (isnan(got) && isnan(ref)) { total_pass++; return 0; }
    if (got == ref) { total_pass++; return 0; }
    int32_t gi, ri;
    memcpy(&gi, &got, 4); memcpy(&ri, &ref, 4);
    int32_t diff = gi - ri; if (diff < 0) diff = -diff;
    if (diff <= 1) { total_pass++; return 0; }
    total_fail++;
    return 1;
}

/* ================================================================
 * Test macros for 1-arg and 2-arg functions
 * ================================================================ */

#define TEST_D1(fname, mpfr_fn, N) do { \
    int fails = 0; \
    mpfr_t mx, mr; mpfr_init2(mx, 200); mpfr_init2(mr, 200); \
    /* Special values */ \
    double specials[] = {0.0, -0.0, 1.0, -1.0, 0.5, -0.5, 2.0, -2.0, \
        1e-300, -1e-300, 1e300, -1e300, INFINITY, -INFINITY, NAN, \
        __DBL_MIN__, __DBL_MAX__, __DBL_EPSILON__, \
        0x1.fffffffffffffp+1023, 0x1p-1074, -0x1p-1074}; \
    for (int i = 0; i < (int)(sizeof(specials)/sizeof(specials[0])); i++) { \
        double x = specials[i]; \
        mpfr_set_d(mx, x, MPFR_RNDN); \
        mpfr_fn(mr, mx, MPFR_RNDN); \
        double got = fname(x); \
        fails += check_d(#fname, x, got, mr); \
    } \
    /* Random values */ \
    for (int i = 0; i < N; i++) { \
        double x = random_double(); \
        if (!isfinite(x)) continue; \
        mpfr_set_d(mx, x, MPFR_RNDN); \
        mpfr_fn(mr, mx, MPFR_RNDN); \
        double got = fname(x); \
        fails += check_d(#fname, x, got, mr); \
    } \
    func_tested++; \
    if (fails == 0) { func_pass++; printf("  %-20s PASS\n", #fname); } \
    else { func_fail++; printf("  %-20s FAIL (%d)\n", #fname, fails); } \
    mpfr_clear(mx); mpfr_clear(mr); \
} while(0)

#define TEST_F1(fname, mpfr_fn, N) do { \
    int fails = 0; \
    mpfr_t mx, mr; mpfr_init2(mx, 200); mpfr_init2(mr, 200); \
    float specials[] = {0.0f, -0.0f, 1.0f, -1.0f, 0.5f, -0.5f, 2.0f, -2.0f, \
        1e-38f, -1e-38f, 1e38f, -1e38f, INFINITY, -INFINITY, NAN, \
        __FLT_MIN__, __FLT_MAX__, __FLT_EPSILON__}; \
    for (int i = 0; i < (int)(sizeof(specials)/sizeof(specials[0])); i++) { \
        float x = specials[i]; \
        mpfr_set_flt(mx, x, MPFR_RNDN); \
        mpfr_fn(mr, mx, MPFR_RNDN); \
        float got = fname(x); \
        fails += check_f(#fname, x, got, mr); \
    } \
    for (int i = 0; i < N; i++) { \
        float x = random_float(); \
        if (!isfinite(x)) continue; \
        mpfr_set_flt(mx, x, MPFR_RNDN); \
        mpfr_fn(mr, mx, MPFR_RNDN); \
        float got = fname(x); \
        fails += check_f(#fname, x, got, mr); \
    } \
    func_tested++; \
    if (fails == 0) { func_pass++; printf("  %-20s PASS\n", #fname); } \
    else { func_fail++; printf("  %-20s FAIL (%d)\n", #fname, fails); } \
    mpfr_clear(mx); mpfr_clear(mr); \
} while(0)

#define TEST_D2(fname, mpfr_fn, N) do { \
    int fails = 0; \
    mpfr_t mx, my, mr; mpfr_init2(mx, 200); mpfr_init2(my, 200); mpfr_init2(mr, 200); \
    for (int i = 0; i < N; i++) { \
        double x = random_double(), y = random_double(); \
        if (!isfinite(x) || !isfinite(y)) continue; \
        mpfr_set_d(mx, x, MPFR_RNDN); mpfr_set_d(my, y, MPFR_RNDN); \
        mpfr_fn(mr, mx, my, MPFR_RNDN); \
        double got = fname(x, y); \
        fails += check_d(#fname, x, got, mr); \
    } \
    func_tested++; \
    if (fails == 0) { func_pass++; printf("  %-20s PASS\n", #fname); } \
    else { func_fail++; printf("  %-20s FAIL (%d)\n", #fname, fails); } \
    mpfr_clear(mx); mpfr_clear(my); mpfr_clear(mr); \
} while(0)

#define TEST_F2(fname, mpfr_fn, N) do { \
    int fails = 0; \
    mpfr_t mx, my, mr; mpfr_init2(mx, 200); mpfr_init2(my, 200); mpfr_init2(mr, 200); \
    for (int i = 0; i < N; i++) { \
        float x = random_float(), y = random_float(); \
        if (!isfinite(x) || !isfinite(y)) continue; \
        mpfr_set_flt(mx, x, MPFR_RNDN); mpfr_set_flt(my, y, MPFR_RNDN); \
        mpfr_fn(mr, mx, my, MPFR_RNDN); \
        float got = fname(x, y); \
        fails += check_f(#fname, x, got, mr); \
    } \
    func_tested++; \
    if (fails == 0) { func_pass++; printf("  %-20s PASS\n", #fname); } \
    else { func_fail++; printf("  %-20s FAIL (%d)\n", #fname, fails); } \
    mpfr_clear(mx); mpfr_clear(my); mpfr_clear(mr); \
} while(0)

int main(int argc, char **argv) {
    int N = 100000;
    if (argc > 1) N = atoi(argv[1]);

    printf("Core-Math MPFR Tests (%d random + specials per function)\n\n", N);

    /* Double precision (1-arg) */
    printf("--- Double precision ---\n");
    TEST_D1(acos,   mpfr_acos,   N);
    TEST_D1(acosh,  mpfr_acosh,  N);
    TEST_D1(asin,   mpfr_asin,   N);
    TEST_D1(asinh,  mpfr_asinh,  N);
    TEST_D1(atan,   mpfr_atan,   N);
    TEST_D1(atanh,  mpfr_atanh,  N);
    TEST_D1(cbrt,   mpfr_cbrt,   N);
    TEST_D1(cos,    mpfr_cos,    N);
    TEST_D1(cosh,   mpfr_cosh,   N);
    TEST_D1(erf,    mpfr_erf,    N);
    TEST_D1(erfc,   mpfr_erfc,   N);
    TEST_D1(exp,    mpfr_exp,    N);
    TEST_D1(exp2,   mpfr_exp2,   N);
    TEST_D1(expm1,  mpfr_expm1,  N);
    TEST_D1(log,    mpfr_log,    N);
    TEST_D1(log10,  mpfr_log10,  N);
    TEST_D1(log1p,  mpfr_log1p,  N);
    TEST_D1(log2,   mpfr_log2,   N);
    TEST_D1(sin,    mpfr_sin,    N);
    TEST_D1(sinh,   mpfr_sinh,   N);
    TEST_D1(sqrt,   mpfr_sqrt,   N);
    TEST_D1(tan,    mpfr_tan,    N);
    TEST_D1(tanh,   mpfr_tanh,   N);
    TEST_D1(tgamma, mpfr_gamma,  N);
    TEST_D1(lgamma, mpfr_lngamma, N);

    /* Double precision (2-arg) */
    TEST_D2(atan2,  mpfr_atan2,  N);
    TEST_D2(hypot,  mpfr_hypot,  N);
    TEST_D2(pow,    mpfr_pow,    N);
    TEST_D2(fmod,   mpfr_fmod,   N);

    printf("\n--- Single precision ---\n");
    TEST_F1(acosf,  mpfr_acos,   N);
    TEST_F1(acoshf, mpfr_acosh,  N);
    TEST_F1(asinf,  mpfr_asin,   N);
    TEST_F1(asinhf, mpfr_asinh,  N);
    TEST_F1(atanf,  mpfr_atan,   N);
    TEST_F1(atanhf, mpfr_atanh,  N);
    TEST_F1(cbrtf,  mpfr_cbrt,   N);
    TEST_F1(cosf,   mpfr_cos,    N);
    TEST_F1(coshf,  mpfr_cosh,   N);
    TEST_F1(erff,   mpfr_erf,    N);
    TEST_F1(erfcf,  mpfr_erfc,   N);
    TEST_F1(expf,   mpfr_exp,    N);
    TEST_F1(exp2f,  mpfr_exp2,   N);
    TEST_F1(expm1f, mpfr_expm1,  N);
    TEST_F1(logf,   mpfr_log,    N);
    TEST_F1(log10f, mpfr_log10,  N);
    TEST_F1(log1pf, mpfr_log1p,  N);
    TEST_F1(log2f,  mpfr_log2,   N);
    TEST_F1(sinf,   mpfr_sin,    N);
    TEST_F1(sinhf,  mpfr_sinh,   N);
    TEST_F1(sqrtf,  mpfr_sqrt,   N);
    TEST_F1(tanf,   mpfr_tan,    N);
    TEST_F1(tanhf,  mpfr_tanh,   N);
    TEST_F1(tgammaf, mpfr_gamma, N);
    TEST_F1(lgammaf, mpfr_lngamma, N);

    /* Float precision (2-arg) */
    TEST_F2(atan2f, mpfr_atan2,  N);
    TEST_F2(hypotf, mpfr_hypot,  N);
    TEST_F2(powf,   mpfr_pow,    N);
    TEST_F2(fmodf,  mpfr_fmod,   N);

    printf("\nCore-Math MPFR: %d funcs tested, %d pass, %d fail (%d/%d tests pass)\n",
           func_tested, func_pass, func_fail, total_pass, total_tests);
    return func_fail > 0 ? 1 : 0;
}
