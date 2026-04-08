/*
 * test_suite.c - Comprehensive test suite for libmcs
 *
 * Tests ALL public, internal extern, and bridged static functions.
 * All outputs are printed in %a hex float format for bitwise comparison.
 *
 * Compile with:
 *   gcc -I/home/leochanj/Desktop/libmcs/libm/include \
 *       test_suite.c test_bridge.c -L<libdir> -lmcs -lm
 */

#include <stdio.h>
#include <stdint.h>
#include "/home/leochanj/Desktop/libmcs/libm/include/math.h"
#include "/home/leochanj/Desktop/libmcs/libm/include/complex.h"

/*
 * The library's INFINITY/NAN macros use extern variables (__inff, nanf(""))
 * which are not constant expressions for static initializers.
 * Use GCC builtins instead for array initialization.
 */
#define INF_VAL  __builtin_inf()
#define NINF_VAL (-__builtin_inf())
#define NAN_VAL  __builtin_nan("")
#define INFF_VAL  __builtin_inff()
#define NINFF_VAL (-__builtin_inff())
#define NANF_VAL  __builtin_nanf("")

/* ========================================================================
 * Extern declarations for internal (non-static) library functions
 * ======================================================================== */
extern double  __sin(double x, double y, int iy);
extern double  __cos(double x, double y);
extern int32_t __rem_pio2(double x, double *y);
extern float   __sinf(float x, float y, int iy);
extern float   __cosf(float x, float y);
extern int32_t __rem_pio2f(float x, float *y);
extern double  __lgamma(double x, int *signgamp);
extern float   __lgammaf(float x, int *signgamp);
extern int     __fpclassifyd(double x);
extern int     __fpclassifyf(float x);
extern int     __signbitd(double x);
extern int     __signbitf(float x);
extern void    __ccoshsinh(double x, double *c, double *s);
extern void    __ccoshsinhf(float x, float *c, float *s);
extern double  __redupi(double x);
extern float   __redupif(float x);

/* ========================================================================
 * Extern declarations for bridge functions (from test_bridge.c)
 * ======================================================================== */
extern double bridge___tan(double x, double y, int iy);
extern float  bridge___tanf(float x, float y, int iy);
extern double bridge___ctans(double complex z);
extern float  bridge___ctansf(float complex z);
extern double bridge___sin_pi(double x);
extern float  bridge___sin_pif(float x);
extern int    bridge___rem_pio2_internal(double *x, double *y, int e0, int nx);
extern int    bridge___rem_pio2f_internal(float *x, float *y, int e0, int nx);

/* ========================================================================
 * Test value arrays
 * ======================================================================== */

/* Double precision test values */
static const double d_vals[] = {
    0.0, -0.0,
    0.5, -0.5, 1.0, -1.0, 2.0, -2.0,
    0.25, 0.75, 1.5, 3.0, 10.0, 100.0,
    1e-15, -1e-15,
    5e-324, -5e-324,                                    /* min subnormal */
    2.2250738585072014e-308, -2.2250738585072014e-308,  /* min normal */
    1.7976931348623157e+308, -1.7976931348623157e+308,  /* max */
    INF_VAL, NINF_VAL,
    NAN_VAL
};
#define N_DVALS (sizeof(d_vals)/sizeof(d_vals[0]))

/* Float precision test values */
static const float f_vals[] = {
    0.0f, -0.0f,
    0.5f, -0.5f, 1.0f, -1.0f, 2.0f, -2.0f,
    0.25f, 0.75f, 1.5f, 3.0f, 10.0f, 100.0f,
    1e-7f, -1e-7f,
    1.4e-45f, -1.4e-45f,                   /* min subnormal */
    1.17549435e-38f, -1.17549435e-38f,     /* min normal */
    3.40282347e+38f, -3.40282347e+38f,     /* max */
    INFF_VAL, NINFF_VAL,
    NANF_VAL
};
#define N_FVALS (sizeof(f_vals)/sizeof(f_vals[0]))

/* Double precision pairs for two-argument functions */
static const double d_pairs[][2] = {
    {0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}, {1.0, 1.0},
    {-1.0, 1.0}, {1.0, -1.0}, {-1.0, -1.0},
    {0.5, 2.0}, {2.0, 0.5}, {0.5, 0.5},
    {3.0, 4.0}, {10.0, 3.0},
    {0.0, -0.0}, {-0.0, 0.0}, {-0.0, -0.0},
    {INF_VAL, 0.0}, {0.0, INF_VAL}, {INF_VAL, INF_VAL},
    {NINF_VAL, 1.0}, {1.0, NINF_VAL}, {NINF_VAL, NINF_VAL},
    {NAN_VAL, 0.0}, {0.0, NAN_VAL}, {NAN_VAL, NAN_VAL}, {NAN_VAL, INF_VAL},
    {1e308, 1e308}, {5e-324, 5e-324},
    {1e-15, 1e-15}, {1e300, 1e-300},
};
#define N_DPAIRS (sizeof(d_pairs)/sizeof(d_pairs[0]))

/* Float precision pairs */
static const float f_pairs[][2] = {
    {0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
    {-1.0f, 1.0f}, {1.0f, -1.0f}, {-1.0f, -1.0f},
    {0.5f, 2.0f}, {2.0f, 0.5f}, {0.5f, 0.5f},
    {3.0f, 4.0f}, {10.0f, 3.0f},
    {0.0f, -0.0f}, {-0.0f, 0.0f}, {-0.0f, -0.0f},
    {INFF_VAL, 0.0f}, {0.0f, INFF_VAL}, {INFF_VAL, INFF_VAL},
    {NINFF_VAL, 1.0f}, {1.0f, NINFF_VAL}, {NINFF_VAL, NINFF_VAL},
    {NANF_VAL, 0.0f}, {0.0f, NANF_VAL}, {NANF_VAL, NANF_VAL},
    {3.40282347e+38f, 3.40282347e+38f}, {1.4e-45f, 1.4e-45f},
};
#define N_FPAIRS (sizeof(f_pairs)/sizeof(f_pairs[0]))

/* Complex double test values */
static const double cd_re[] = {0.0, -0.0, 1.0, -1.0, 0.5, 0.25, INF_VAL, NINF_VAL, NAN_VAL, 1e-300, 1e300};
static const double cd_im[] = {0.0, -0.0, 1.0, -1.0, 0.5, 0.25, INF_VAL, NINF_VAL, NAN_VAL, 1e-300, 1e300};
#define N_CD_RE (sizeof(cd_re)/sizeof(cd_re[0]))
#define N_CD_IM (sizeof(cd_im)/sizeof(cd_im[0]))

/* Float complex test values */
static const float cf_re[] = {0.0f, -0.0f, 1.0f, -1.0f, 0.5f, 0.25f, INFF_VAL, NINFF_VAL, NANF_VAL, 1e-38f, 1e38f};
static const float cf_im[] = {0.0f, -0.0f, 1.0f, -1.0f, 0.5f, 0.25f, INFF_VAL, NINFF_VAL, NANF_VAL, 1e-38f, 1e38f};
#define N_CF_RE (sizeof(cf_re)/sizeof(cf_re[0]))
#define N_CF_IM (sizeof(cf_im)/sizeof(cf_im[0]))

/* Triple values for fma */
static const double d_triples[][3] = {
    {0.0, 0.0, 0.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0},
    {2.0, 3.0, 4.0}, {-1.0, 2.0, 3.0}, {0.5, 0.5, 0.5},
    {1e308, 2.0, 0.0}, {1e-308, 1e-308, 0.0},
    {INF_VAL, 1.0, 0.0}, {NAN_VAL, 1.0, 0.0}, {1.0, NAN_VAL, 0.0},
    {1.0, 1.0, NAN_VAL}, {INF_VAL, 0.0, 0.0},
    {1e308, 1e308, NINF_VAL},
};
#define N_DTRIPLES (sizeof(d_triples)/sizeof(d_triples[0]))

static const float f_triples[][3] = {
    {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f},
    {2.0f, 3.0f, 4.0f}, {-1.0f, 2.0f, 3.0f}, {0.5f, 0.5f, 0.5f},
    {1e38f, 2.0f, 0.0f}, {1e-38f, 1e-38f, 0.0f},
    {INFF_VAL, 1.0f, 0.0f}, {NANF_VAL, 1.0f, 0.0f}, {1.0f, NANF_VAL, 0.0f},
    {1.0f, 1.0f, NANF_VAL}, {INFF_VAL, 0.0f, 0.0f},
};
#define N_FTRIPLES (sizeof(f_triples)/sizeof(f_triples[0]))

/* Int-double pairs for jn, yn, ldexp, scalbn */
static const int id_ints[] = {0, 1, 2, 3, 5, 10, -1, -5};
#define N_IDINTS (sizeof(id_ints)/sizeof(id_ints[0]))

/* ========================================================================
 * Helper macros for test output
 * ======================================================================== */

/* Test double -> double function */
#define TEST_D1(fn) do { \
    for (size_t _i = 0; _i < N_DVALS; _i++) \
        printf(#fn " %a = %a\n", d_vals[_i], fn(d_vals[_i])); \
} while(0)

/* Test float -> float function */
#define TEST_F1(fn) do { \
    for (size_t _i = 0; _i < N_FVALS; _i++) \
        printf(#fn " %a = %a\n", (double)f_vals[_i], (double)fn(f_vals[_i])); \
} while(0)

/* Test (double, double) -> double function */
#define TEST_D2(fn) do { \
    for (size_t _i = 0; _i < N_DPAIRS; _i++) \
        printf(#fn " %a %a = %a\n", d_pairs[_i][0], d_pairs[_i][1], \
               fn(d_pairs[_i][0], d_pairs[_i][1])); \
} while(0)

/* Test (float, float) -> float function */
#define TEST_F2(fn) do { \
    for (size_t _i = 0; _i < N_FPAIRS; _i++) \
        printf(#fn " %a %a = %a\n", (double)f_pairs[_i][0], (double)f_pairs[_i][1], \
               (double)fn(f_pairs[_i][0], f_pairs[_i][1])); \
} while(0)

/* Test double -> int function */
#define TEST_D1I(fn) do { \
    for (size_t _i = 0; _i < N_DVALS; _i++) \
        printf(#fn " %a = %d\n", d_vals[_i], fn(d_vals[_i])); \
} while(0)

/* Test float -> int function */
#define TEST_F1I(fn) do { \
    for (size_t _i = 0; _i < N_FVALS; _i++) \
        printf(#fn " %a = %d\n", (double)f_vals[_i], fn(f_vals[_i])); \
} while(0)

/* Test double -> long function */
#define TEST_D1L(fn) do { \
    for (size_t _i = 0; _i < N_DVALS; _i++) \
        printf(#fn " %a = %ld\n", d_vals[_i], fn(d_vals[_i])); \
} while(0)

/* Test float -> long function */
#define TEST_F1L(fn) do { \
    for (size_t _i = 0; _i < N_FVALS; _i++) \
        printf(#fn " %a = %ld\n", (double)f_vals[_i], fn(f_vals[_i])); \
} while(0)

/* Test double -> long long function */
#define TEST_D1LL(fn) do { \
    for (size_t _i = 0; _i < N_DVALS; _i++) \
        printf(#fn " %a = %lld\n", d_vals[_i], fn(d_vals[_i])); \
} while(0)

/* Test float -> long long function */
#define TEST_F1LL(fn) do { \
    for (size_t _i = 0; _i < N_FVALS; _i++) \
        printf(#fn " %a = %lld\n", (double)f_vals[_i], fn(f_vals[_i])); \
} while(0)

/* Test (double, double, double) -> double function (fma) */
#define TEST_D3(fn) do { \
    for (size_t _i = 0; _i < N_DTRIPLES; _i++) \
        printf(#fn " %a %a %a = %a\n", d_triples[_i][0], d_triples[_i][1], \
               d_triples[_i][2], fn(d_triples[_i][0], d_triples[_i][1], d_triples[_i][2])); \
} while(0)

/* Test (float, float, float) -> float function (fmaf) */
#define TEST_F3(fn) do { \
    for (size_t _i = 0; _i < N_FTRIPLES; _i++) \
        printf(#fn " %a %a %a = %a\n", (double)f_triples[_i][0], (double)f_triples[_i][1], \
               (double)f_triples[_i][2], (double)fn(f_triples[_i][0], f_triples[_i][1], f_triples[_i][2])); \
} while(0)

/* Test complex double -> complex double function */
#define TEST_CD1(fn) do { \
    for (size_t _r = 0; _r < N_CD_RE; _r++) \
        for (size_t _c = 0; _c < N_CD_IM; _c++) { \
            double complex _z = CMPLX(cd_re[_r], cd_im[_c]); \
            double complex _w = fn(_z); \
            printf(#fn " %a %a = %a %a\n", creal(_z), cimag(_z), creal(_w), cimag(_w)); \
        } \
} while(0)

/* Test complex double -> double function */
#define TEST_CD1R(fn) do { \
    for (size_t _r = 0; _r < N_CD_RE; _r++) \
        for (size_t _c = 0; _c < N_CD_IM; _c++) { \
            double complex _z = CMPLX(cd_re[_r], cd_im[_c]); \
            printf(#fn " %a %a = %a\n", creal(_z), cimag(_z), fn(_z)); \
        } \
} while(0)

/* Test complex float -> complex float function */
#define TEST_CF1(fn) do { \
    for (size_t _r = 0; _r < N_CF_RE; _r++) \
        for (size_t _c = 0; _c < N_CF_IM; _c++) { \
            float complex _z = CMPLXF(cf_re[_r], cf_im[_c]); \
            float complex _w = fn(_z); \
            printf(#fn " %a %a = %a %a\n", (double)crealf(_z), (double)cimagf(_z), \
                   (double)crealf(_w), (double)cimagf(_w)); \
        } \
} while(0)

/* Test complex float -> float function */
#define TEST_CF1R(fn) do { \
    for (size_t _r = 0; _r < N_CF_RE; _r++) \
        for (size_t _c = 0; _c < N_CF_IM; _c++) { \
            float complex _z = CMPLXF(cf_re[_r], cf_im[_c]); \
            printf(#fn " %a %a = %a\n", (double)crealf(_z), (double)cimagf(_z), (double)fn(_z)); \
        } \
} while(0)

/* ========================================================================
 * Test functions
 * ======================================================================== */

void test_double_trig(void)
{
    TEST_D1(acos);
    TEST_D1(asin);
    TEST_D1(atan);
    TEST_D1(cos);
    TEST_D1(sin);
    TEST_D1(tan);
    TEST_D2(atan2);
}

void test_double_hyperbolic(void)
{
    TEST_D1(acosh);
    TEST_D1(asinh);
    TEST_D1(atanh);
    TEST_D1(cosh);
    TEST_D1(sinh);
    TEST_D1(tanh);
}

void test_double_explog(void)
{
    TEST_D1(exp);
    TEST_D1(exp2);
    TEST_D1(expm1);
    TEST_D1(log);
    TEST_D1(log10);
    TEST_D1(log1p);
    TEST_D1(log2);
    TEST_D1(logb);

    /* frexp: double frexp(double, int*) */
    for (size_t i = 0; i < N_DVALS; i++) {
        int exp_val;
        double r = frexp(d_vals[i], &exp_val);
        printf("frexp %a = %a exp=%d\n", d_vals[i], r, exp_val);
    }

    /* ilogb: int ilogb(double) */
    TEST_D1I(ilogb);

    /* ldexp: double ldexp(double, int) */
    for (size_t i = 0; i < N_DVALS; i++)
        for (size_t j = 0; j < N_IDINTS; j++)
            printf("ldexp %a %d = %a\n", d_vals[i], id_ints[j], ldexp(d_vals[i], id_ints[j]));

    /* modf: double modf(double, double*) */
    for (size_t i = 0; i < N_DVALS; i++) {
        double ipart;
        double r = modf(d_vals[i], &ipart);
        printf("modf %a = %a ipart=%a\n", d_vals[i], r, ipart);
    }

    /* scalbn: double scalbn(double, int) */
    for (size_t i = 0; i < N_DVALS; i++)
        for (size_t j = 0; j < N_IDINTS; j++)
            printf("scalbn %a %d = %a\n", d_vals[i], id_ints[j], scalbn(d_vals[i], id_ints[j]));

    /* scalbln: double scalbln(double, long) */
    for (size_t i = 0; i < N_DVALS; i++)
        for (size_t j = 0; j < N_IDINTS; j++)
            printf("scalbln %a %ld = %a\n", d_vals[i], (long)id_ints[j], scalbln(d_vals[i], (long)id_ints[j]));
}

void test_double_power(void)
{
    TEST_D1(cbrt);
    TEST_D1(fabs);
    TEST_D1(sqrt);
    TEST_D2(hypot);
    TEST_D2(pow);
}

void test_double_errorgamma(void)
{
    TEST_D1(erf);
    TEST_D1(erfc);

    /* lgamma: also reports signgam */
    for (size_t i = 0; i < N_DVALS; i++) {
        double r = lgamma(d_vals[i]);
        printf("lgamma %a = %a signgam=%d\n", d_vals[i], r, signgam);
    }

    TEST_D1(tgamma);
}

void test_double_nearestint(void)
{
    TEST_D1(ceil);
    TEST_D1(floor);
    TEST_D1(nearbyint);
    TEST_D1(rint);
    TEST_D1(round);
    TEST_D1(trunc);
    TEST_D1L(lrint);
    TEST_D1L(lround);
    TEST_D1LL(llrint);
    TEST_D1LL(llround);
}

void test_double_remainder(void)
{
    TEST_D2(fmod);
    TEST_D2(remainder);

    /* remquo: double remquo(double, double, int*) */
    for (size_t i = 0; i < N_DPAIRS; i++) {
        int quo;
        double r = remquo(d_pairs[i][0], d_pairs[i][1], &quo);
        printf("remquo %a %a = %a quo=%d\n", d_pairs[i][0], d_pairs[i][1], r, quo);
    }
}

void test_double_manipulation(void)
{
    TEST_D2(copysign);
    TEST_D2(nextafter);

    /* nan */
    printf("nan \"\" = %a\n", nan(""));
    printf("nan \"0\" = %a\n", nan("0"));
    printf("nan \"1\" = %a\n", nan("1"));
}

void test_double_maxmin(void)
{
    TEST_D2(fdim);
    TEST_D2(fmax);
    TEST_D2(fmin);
}

void test_double_fma(void)
{
    TEST_D3(fma);
}

void test_double_bessel(void)
{
    TEST_D1(j0);
    TEST_D1(j1);
    TEST_D1(y0);
    TEST_D1(y1);

    /* jn, yn: (int, double) -> double */
    for (size_t j = 0; j < N_IDINTS; j++)
        for (size_t i = 0; i < N_DVALS; i++)
            printf("jn %d %a = %a\n", id_ints[j], d_vals[i], jn(id_ints[j], d_vals[i]));

    for (size_t j = 0; j < N_IDINTS; j++)
        for (size_t i = 0; i < N_DVALS; i++)
            printf("yn %d %a = %a\n", id_ints[j], d_vals[i], yn(id_ints[j], d_vals[i]));
}

/* ========================================================================
 * Float precision tests
 * ======================================================================== */

void test_float_trig(void)
{
    TEST_F1(acosf);
    TEST_F1(asinf);
    TEST_F1(atanf);
    TEST_F1(cosf);
    TEST_F1(sinf);
    TEST_F1(tanf);
    TEST_F2(atan2f);
}

void test_float_hyperbolic(void)
{
    TEST_F1(acoshf);
    TEST_F1(asinhf);
    TEST_F1(atanhf);
    TEST_F1(coshf);
    TEST_F1(sinhf);
    TEST_F1(tanhf);
}

void test_float_explog(void)
{
    TEST_F1(expf);
    TEST_F1(exp2f);
    TEST_F1(expm1f);
    TEST_F1(logf);
    TEST_F1(log10f);
    TEST_F1(log1pf);
    TEST_F1(log2f);
    TEST_F1(logbf);

    /* frexpf */
    for (size_t i = 0; i < N_FVALS; i++) {
        int exp_val;
        float r = frexpf(f_vals[i], &exp_val);
        printf("frexpf %a = %a exp=%d\n", (double)f_vals[i], (double)r, exp_val);
    }

    TEST_F1I(ilogbf);

    /* ldexpf */
    for (size_t i = 0; i < N_FVALS; i++)
        for (size_t j = 0; j < N_IDINTS; j++)
            printf("ldexpf %a %d = %a\n", (double)f_vals[i], id_ints[j], (double)ldexpf(f_vals[i], id_ints[j]));

    /* modff */
    for (size_t i = 0; i < N_FVALS; i++) {
        float ipart;
        float r = modff(f_vals[i], &ipart);
        printf("modff %a = %a ipart=%a\n", (double)f_vals[i], (double)r, (double)ipart);
    }

    /* scalbnf */
    for (size_t i = 0; i < N_FVALS; i++)
        for (size_t j = 0; j < N_IDINTS; j++)
            printf("scalbnf %a %d = %a\n", (double)f_vals[i], id_ints[j], (double)scalbnf(f_vals[i], id_ints[j]));

    /* scalblnf */
    for (size_t i = 0; i < N_FVALS; i++)
        for (size_t j = 0; j < N_IDINTS; j++)
            printf("scalblnf %a %ld = %a\n", (double)f_vals[i], (long)id_ints[j], (double)scalblnf(f_vals[i], (long)id_ints[j]));
}

void test_float_power(void)
{
    TEST_F1(cbrtf);
    TEST_F1(fabsf);
    TEST_F1(sqrtf);
    TEST_F2(hypotf);
    TEST_F2(powf);
}

void test_float_errorgamma(void)
{
    TEST_F1(erff);
    TEST_F1(erfcf);

    /* lgammaf */
    for (size_t i = 0; i < N_FVALS; i++) {
        float r = lgammaf(f_vals[i]);
        printf("lgammaf %a = %a signgam=%d\n", (double)f_vals[i], (double)r, signgam);
    }

    TEST_F1(tgammaf);
}

void test_float_nearestint(void)
{
    TEST_F1(ceilf);
    TEST_F1(floorf);
    TEST_F1(nearbyintf);
    TEST_F1(rintf);
    TEST_F1(roundf);
    TEST_F1(truncf);
    TEST_F1L(lrintf);
    TEST_F1L(lroundf);
    TEST_F1LL(llrintf);
    TEST_F1LL(llroundf);
}

void test_float_remainder(void)
{
    TEST_F2(fmodf);
    TEST_F2(remainderf);

    /* remquof */
    for (size_t i = 0; i < N_FPAIRS; i++) {
        int quo;
        float r = remquof(f_pairs[i][0], f_pairs[i][1], &quo);
        printf("remquof %a %a = %a quo=%d\n", (double)f_pairs[i][0], (double)f_pairs[i][1], (double)r, quo);
    }
}

void test_float_manipulation(void)
{
    TEST_F2(copysignf);
    TEST_F2(nextafterf);

    /* nanf */
    printf("nanf \"\" = %a\n", (double)nanf(""));
    printf("nanf \"0\" = %a\n", (double)nanf("0"));
    printf("nanf \"1\" = %a\n", (double)nanf("1"));
}

void test_float_maxmin(void)
{
    TEST_F2(fdimf);
    TEST_F2(fmaxf);
    TEST_F2(fminf);
}

void test_float_fma(void)
{
    TEST_F3(fmaf);
}

/* ========================================================================
 * Complex double tests
 * ======================================================================== */

void test_complex_double(void)
{
    /* Trigonometric */
    TEST_CD1(cacos);
    TEST_CD1(casin);
    TEST_CD1(catan);
    TEST_CD1(ccos);
    TEST_CD1(csin);
    TEST_CD1(ctan);

    /* Hyperbolic */
    TEST_CD1(cacosh);
    TEST_CD1(casinh);
    TEST_CD1(catanh);
    TEST_CD1(ccosh);
    TEST_CD1(csinh);
    TEST_CD1(ctanh);

    /* Exp/Log */
    TEST_CD1(cexp);
    TEST_CD1(clog);

    /* Power/Abs */
    TEST_CD1R(cabs);
    TEST_CD1(csqrt);

    /* cpow: (dc, dc) -> dc */
    for (size_t r1 = 0; r1 < N_CD_RE; r1++)
        for (size_t c1 = 0; c1 < N_CD_IM; c1++) {
            double complex z1 = CMPLX(cd_re[r1], cd_im[c1]);
            /* Test a few specific powers */
            double complex powers[] = {CMPLX(2.0, 0.0), CMPLX(0.5, 0.0), CMPLX(0.0, 1.0), CMPLX(1.0, 1.0)};
            for (int p = 0; p < 4; p++) {
                double complex w = cpow(z1, powers[p]);
                printf("cpow %a %a %a %a = %a %a\n",
                       creal(z1), cimag(z1), creal(powers[p]), cimag(powers[p]),
                       creal(w), cimag(w));
            }
        }

    /* Manipulation */
    TEST_CD1R(carg);
    TEST_CD1R(cimag);
    TEST_CD1R(creal);
    TEST_CD1(conj);
    TEST_CD1(cproj);
}

/* ========================================================================
 * Complex float tests
 * ======================================================================== */

void test_complex_float(void)
{
    /* Trigonometric */
    TEST_CF1(cacosf);
    TEST_CF1(casinf);
    TEST_CF1(catanf);
    TEST_CF1(ccosf);
    TEST_CF1(csinf);
    TEST_CF1(ctanf);

    /* Hyperbolic */
    TEST_CF1(cacoshf);
    TEST_CF1(casinhf);
    TEST_CF1(catanhf);
    TEST_CF1(ccoshf);
    TEST_CF1(csinhf);
    TEST_CF1(ctanhf);

    /* Exp/Log */
    TEST_CF1(cexpf);
    TEST_CF1(clogf);

    /* Power/Abs */
    TEST_CF1R(cabsf);
    TEST_CF1(csqrtf);

    /* cpowf */
    for (size_t r1 = 0; r1 < N_CF_RE; r1++)
        for (size_t c1 = 0; c1 < N_CF_IM; c1++) {
            float complex z1 = CMPLXF(cf_re[r1], cf_im[c1]);
            float complex powers[] = {CMPLXF(2.0f, 0.0f), CMPLXF(0.5f, 0.0f), CMPLXF(0.0f, 1.0f), CMPLXF(1.0f, 1.0f)};
            for (int p = 0; p < 4; p++) {
                float complex w = cpowf(z1, powers[p]);
                printf("cpowf %a %a %a %a = %a %a\n",
                       (double)crealf(z1), (double)cimagf(z1),
                       (double)crealf(powers[p]), (double)cimagf(powers[p]),
                       (double)crealf(w), (double)cimagf(w));
            }
        }

    /* Manipulation */
    TEST_CF1R(cargf);
    TEST_CF1R(cimagf);
    TEST_CF1R(crealf);
    TEST_CF1(conjf);
    TEST_CF1(cprojf);
}

/* ========================================================================
 * Internal extern function tests
 * ======================================================================== */

void test_internal_trig(void)
{
    /* __sin(x, y, iy): x+y in [-pi/4, pi/4], iy=0 or 1 */
    double sin_vals[] = {0.0, -0.0, 0.1, -0.1, 0.5, -0.5, 0.7, -0.7, 1e-15, -1e-15, 5e-324};
    for (size_t i = 0; i < sizeof(sin_vals)/sizeof(sin_vals[0]); i++) {
        printf("__sin %a %a %d = %a\n", sin_vals[i], 0.0, 0, __sin(sin_vals[i], 0.0, 0));
        printf("__sin %a %a %d = %a\n", sin_vals[i], 0.0, 1, __sin(sin_vals[i], 0.0, 1));
        printf("__sin %a %a %d = %a\n", sin_vals[i], 1e-20, 1, __sin(sin_vals[i], 1e-20, 1));
    }

    /* __cos(x, y): x+y in [-pi/4, pi/4] */
    for (size_t i = 0; i < sizeof(sin_vals)/sizeof(sin_vals[0]); i++) {
        printf("__cos %a %a = %a\n", sin_vals[i], 0.0, __cos(sin_vals[i], 0.0));
        printf("__cos %a %a = %a\n", sin_vals[i], 1e-20, __cos(sin_vals[i], 1e-20));
    }

    /* __rem_pio2(x, y): returns quadrant, y[0]+y[1] = remainder */
    double rem_vals[] = {0.0, 0.5, 1.0, 1.5707963267948966, 3.14159265358979,
                         6.28318530717959, 10.0, 100.0, 1e10, 1e15,
                         -0.5, -1.0, -3.14159265358979, -1e10};
    for (size_t i = 0; i < sizeof(rem_vals)/sizeof(rem_vals[0]); i++) {
        double y[2];
        int32_t n = __rem_pio2(rem_vals[i], y);
        printf("__rem_pio2 %a = %d %a %a\n", rem_vals[i], n, y[0], y[1]);
    }

    /* __sinf, __cosf, __rem_pio2f */
    float sinf_vals[] = {0.0f, -0.0f, 0.1f, -0.1f, 0.5f, -0.5f, 0.7f, -0.7f, 1e-7f, 1.4e-45f};
    for (size_t i = 0; i < sizeof(sinf_vals)/sizeof(sinf_vals[0]); i++) {
        printf("__sinf %a %a %d = %a\n", (double)sinf_vals[i], 0.0, 0, (double)__sinf(sinf_vals[i], 0.0f, 0));
        printf("__sinf %a %a %d = %a\n", (double)sinf_vals[i], 0.0, 1, (double)__sinf(sinf_vals[i], 0.0f, 1));
        printf("__cosf %a %a = %a\n", (double)sinf_vals[i], 0.0, (double)__cosf(sinf_vals[i], 0.0f));
    }

    float remf_vals[] = {0.0f, 0.5f, 1.0f, 1.5707963f, 3.1415927f, 10.0f, 100.0f, 1e5f, -1.0f, -10.0f};
    for (size_t i = 0; i < sizeof(remf_vals)/sizeof(remf_vals[0]); i++) {
        float y[2];
        int32_t n = __rem_pio2f(remf_vals[i], y);
        printf("__rem_pio2f %a = %d %a %a\n", (double)remf_vals[i], n, (double)y[0], (double)y[1]);
    }
}

void test_internal_gamma(void)
{
    /* __lgamma(x, signgamp) */
    double lgamma_vals[] = {0.5, 1.0, 1.5, 2.0, 3.0, 5.0, 10.0, 100.0,
                            -0.5, -1.5, -2.5, 0.0, -0.0,
                            1e-300, 5e-324, 1e308, INFINITY, -INFINITY, NAN};
    for (size_t i = 0; i < sizeof(lgamma_vals)/sizeof(lgamma_vals[0]); i++) {
        int sg;
        double r = __lgamma(lgamma_vals[i], &sg);
        printf("__lgamma %a = %a signgam=%d\n", lgamma_vals[i], r, sg);
    }

    /* __lgammaf(x, signgamp) */
    float lgammaf_vals[] = {0.5f, 1.0f, 1.5f, 2.0f, 3.0f, 5.0f, 10.0f, 100.0f,
                            -0.5f, -1.5f, -2.5f, 0.0f, -0.0f,
                            1e-38f, 1.4e-45f, 3.4e38f, INFINITY, -INFINITY, NAN};
    for (size_t i = 0; i < sizeof(lgammaf_vals)/sizeof(lgammaf_vals[0]); i++) {
        int sg;
        float r = __lgammaf(lgammaf_vals[i], &sg);
        printf("__lgammaf %a = %a signgam=%d\n", (double)lgammaf_vals[i], (double)r, sg);
    }
}

void test_internal_classify(void)
{
    /* __fpclassifyd */
    TEST_D1I(__fpclassifyd);

    /* __fpclassifyf */
    TEST_F1I(__fpclassifyf);

    /* __signbitd */
    TEST_D1I(__signbitd);

    /* __signbitf */
    TEST_F1I(__signbitf);
}

void test_internal_complex(void)
{
    /* __ccoshsinh(x, &c, &s) */
    double ccosh_vals[] = {0.0, -0.0, 0.25, 0.5, 1.0, -1.0, 2.0, 10.0,
                           1e-15, 5e-324, 700.0, INFINITY, -INFINITY, NAN};
    for (size_t i = 0; i < sizeof(ccosh_vals)/sizeof(ccosh_vals[0]); i++) {
        double c, s;
        __ccoshsinh(ccosh_vals[i], &c, &s);
        printf("__ccoshsinh %a = c=%a s=%a\n", ccosh_vals[i], c, s);
    }

    /* __ccoshsinhf(x, &c, &s) */
    float ccoshf_vals[] = {0.0f, -0.0f, 0.25f, 0.5f, 1.0f, -1.0f, 2.0f, 10.0f,
                           1e-7f, 1.4e-45f, 80.0f, INFINITY, -INFINITY, NAN};
    for (size_t i = 0; i < sizeof(ccoshf_vals)/sizeof(ccoshf_vals[0]); i++) {
        float c, s;
        __ccoshsinhf(ccoshf_vals[i], &c, &s);
        printf("__ccoshsinhf %a = c=%a s=%a\n", (double)ccoshf_vals[i], (double)c, (double)s);
    }

    /* __redupi(x) */
    double redupi_vals[] = {0.0, -0.0, 1.0, -1.0, 3.14159265358979, -3.14159265358979,
                            6.28318530717959, 100.0, 1e10, 0.5, -0.5,
                            INFINITY, -INFINITY, NAN};
    for (size_t i = 0; i < sizeof(redupi_vals)/sizeof(redupi_vals[0]); i++)
        printf("__redupi %a = %a\n", redupi_vals[i], __redupi(redupi_vals[i]));

    /* __redupif(x) */
    float redupif_vals[] = {0.0f, -0.0f, 1.0f, -1.0f, 3.1415927f, -3.1415927f,
                            6.2831853f, 100.0f, 1e5f, 0.5f, -0.5f,
                            INFINITY, -INFINITY, NAN};
    for (size_t i = 0; i < sizeof(redupif_vals)/sizeof(redupif_vals[0]); i++)
        printf("__redupif %a = %a\n", (double)redupif_vals[i], (double)__redupif(redupif_vals[i]));
}

/* ========================================================================
 * Bridged static function tests
 * ======================================================================== */

void test_bridge_tan(void)
{
    /* bridge___tan(x, y, iy): x+y in [-pi/4, pi/4], iy=1 or -1 */
    double tan_x[] = {0.0, -0.0, 0.1, -0.1, 0.3, -0.3, 0.5, -0.5, 0.7, -0.7,
                      1e-15, -1e-15, 5e-324, -5e-324};
    for (size_t i = 0; i < sizeof(tan_x)/sizeof(tan_x[0]); i++) {
        printf("bridge___tan %a %a %d = %a\n", tan_x[i], 0.0, 1, bridge___tan(tan_x[i], 0.0, 1));
        printf("bridge___tan %a %a %d = %a\n", tan_x[i], 0.0, -1, bridge___tan(tan_x[i], 0.0, -1));
        printf("bridge___tan %a %a %d = %a\n", tan_x[i], 1e-20, 1, bridge___tan(tan_x[i], 1e-20, 1));
    }
}

void test_bridge_tanf(void)
{
    float tanf_x[] = {0.0f, -0.0f, 0.1f, -0.1f, 0.3f, -0.3f, 0.5f, -0.5f, 0.7f, -0.7f,
                      1e-7f, -1e-7f, 1.4e-45f, -1.4e-45f};
    for (size_t i = 0; i < sizeof(tanf_x)/sizeof(tanf_x[0]); i++) {
        printf("bridge___tanf %a %a %d = %a\n", (double)tanf_x[i], 0.0, 1, (double)bridge___tanf(tanf_x[i], 0.0f, 1));
        printf("bridge___tanf %a %a %d = %a\n", (double)tanf_x[i], 0.0, -1, (double)bridge___tanf(tanf_x[i], 0.0f, -1));
    }
}

void test_bridge_ctans(void)
{
    /* bridge___ctans(z): Taylor series for cosh(2*imag) - cos(2*real) for small |d| */
    for (size_t r = 0; r < N_CD_RE; r++)
        for (size_t c = 0; c < N_CD_IM; c++) {
            double complex z = CMPLX(cd_re[r], cd_im[c]);
            /* Only test for finite, small inputs where the Taylor series is used */
            if (creal(z) == creal(z) && cimag(z) == cimag(z) &&
                fabs(creal(z)) < 2.0 && fabs(cimag(z)) < 2.0) {
                printf("bridge___ctans %a %a = %a\n", creal(z), cimag(z), bridge___ctans(z));
            }
        }
}

void test_bridge_ctansf(void)
{
    for (size_t r = 0; r < N_CF_RE; r++)
        for (size_t c = 0; c < N_CF_IM; c++) {
            float complex z = CMPLXF(cf_re[r], cf_im[c]);
            if (crealf(z) == crealf(z) && cimagf(z) == cimagf(z) &&
                fabsf(crealf(z)) < 2.0f && fabsf(cimagf(z)) < 2.0f) {
                printf("bridge___ctansf %a %a = %a\n",
                       (double)crealf(z), (double)cimagf(z), (double)bridge___ctansf(z));
            }
        }
}

void test_bridge_sin_pi(void)
{
    /* bridge___sin_pi(x): computes sin(pi*x), called for x in [-2^52, -2^-70] */
    double sinpi_vals[] = {-0.5, -1.0, -1.5, -2.0, -2.5, -3.0, -0.25, -0.75,
                           -0.1, -0.9, -10.5, -100.5, -0.001, -1e-10, -1e-20};
    for (size_t i = 0; i < sizeof(sinpi_vals)/sizeof(sinpi_vals[0]); i++)
        printf("bridge___sin_pi %a = %a\n", sinpi_vals[i], bridge___sin_pi(sinpi_vals[i]));
}

void test_bridge_sin_pif(void)
{
    float sinpif_vals[] = {-0.5f, -1.0f, -1.5f, -2.0f, -2.5f, -3.0f, -0.25f, -0.75f,
                           -0.1f, -0.9f, -10.5f, -100.5f, -0.001f, -1e-5f};
    for (size_t i = 0; i < sizeof(sinpif_vals)/sizeof(sinpif_vals[0]); i++)
        printf("bridge___sin_pif %a = %a\n", (double)sinpif_vals[i], (double)bridge___sin_pif(sinpif_vals[i]));
}

void test_bridge_rem_pio2_internal(void)
{
    /* Test __rem_pio2_internal with a decomposed large angle.
     * For x = 1e15, we decompose into chunks as __rem_pio2 does internally. */
    {
        /* Decompose x = 1000000.0 */
        double x = 1000000.0;
        int32_t hx;
        union { double d; struct { uint32_t lsw; uint32_t msw; } parts; } u;
        u.d = x;
        hx = u.parts.msw & 0x7fffffff;
        int32_t e0 = (hx >> 20) - 1046;
        double z;
        u.parts.msw = hx - (e0 << 20);
        z = u.d;
        double tx[3];
        tx[0] = (double)((int32_t)(z));
        z = (z - tx[0]) * 16777216.0; /* two24 */
        tx[1] = (double)((int32_t)(z));
        z = (z - tx[1]) * 16777216.0;
        tx[2] = z;
        int nx = 3;
        if (tx[2] == 0.0) { nx = 2; if (tx[1] == 0.0) nx = 1; }

        double y[2];
        int n = bridge___rem_pio2_internal(tx, y, e0, nx);
        printf("bridge___rem_pio2_internal x=1000000.0 = %d %a %a\n", n, y[0], y[1]);
    }

    {
        /* Decompose x = 1e10 */
        double x = 1e10;
        int32_t hx;
        union { double d; struct { uint32_t lsw; uint32_t msw; } parts; } u;
        u.d = x;
        hx = u.parts.msw & 0x7fffffff;
        int32_t e0 = (hx >> 20) - 1046;
        double z;
        u.parts.msw = hx - (e0 << 20);
        z = u.d;
        double tx[3];
        tx[0] = (double)((int32_t)(z));
        z = (z - tx[0]) * 16777216.0;
        tx[1] = (double)((int32_t)(z));
        z = (z - tx[1]) * 16777216.0;
        tx[2] = z;
        int nx = 3;
        if (tx[2] == 0.0) { nx = 2; if (tx[1] == 0.0) nx = 1; }

        double y[2];
        int n = bridge___rem_pio2_internal(tx, y, e0, nx);
        printf("bridge___rem_pio2_internal x=1e10 = %d %a %a\n", n, y[0], y[1]);
    }
}

void test_bridge_rem_pio2f_internal(void)
{
    {
        /* Decompose x = 100000.0f */
        float x = 100000.0f;
        int32_t ix;
        union { float f; uint32_t w; } uf;
        uf.f = x;
        ix = uf.w & 0x7fffffff;
        int32_t e0 = (ix >> 23) - 134;
        float z;
        uf.w = ix - (e0 << 23);
        z = uf.f;
        float tx[3];
        tx[0] = (float)((int32_t)(z));
        z = (z - tx[0]) * 256.0f; /* two8 */
        tx[1] = (float)((int32_t)(z));
        z = (z - tx[1]) * 256.0f;
        tx[2] = z;
        int nx = 3;
        if (tx[2] == 0.0f) { nx = 2; if (tx[1] == 0.0f) nx = 1; }

        float y[2];
        int n = bridge___rem_pio2f_internal(tx, y, e0, nx);
        printf("bridge___rem_pio2f_internal x=100000.0f = %d %a %a\n", n, (double)y[0], (double)y[1]);
    }

    {
        /* Decompose x = 1e6f */
        float x = 1e6f;
        int32_t ix;
        union { float f; uint32_t w; } uf;
        uf.f = x;
        ix = uf.w & 0x7fffffff;
        int32_t e0 = (ix >> 23) - 134;
        float z;
        uf.w = ix - (e0 << 23);
        z = uf.f;
        float tx[3];
        tx[0] = (float)((int32_t)(z));
        z = (z - tx[0]) * 256.0f;
        tx[1] = (float)((int32_t)(z));
        z = (z - tx[1]) * 256.0f;
        tx[2] = z;
        int nx = 3;
        if (tx[2] == 0.0f) { nx = 2; if (tx[1] == 0.0f) nx = 1; }

        float y[2];
        int n = bridge___rem_pio2f_internal(tx, y, e0, nx);
        printf("bridge___rem_pio2f_internal x=1e6f = %d %a %a\n", n, (double)y[0], (double)y[1]);
    }
}

/* ========================================================================
 * Main
 * ======================================================================== */

int main(void)
{
    /* Double precision math functions */
    test_double_trig();
    test_double_hyperbolic();
    test_double_explog();
    test_double_power();
    test_double_errorgamma();
    test_double_nearestint();
    test_double_remainder();
    test_double_manipulation();
    test_double_maxmin();
    test_double_fma();
    test_double_bessel();

    /* Float precision math functions */
    test_float_trig();
    test_float_hyperbolic();
    test_float_explog();
    test_float_power();
    test_float_errorgamma();
    test_float_nearestint();
    test_float_remainder();
    test_float_manipulation();
    test_float_maxmin();
    test_float_fma();

    /* Complex double functions */
    test_complex_double();

    /* Complex float functions */
    test_complex_float();

    /* Internal extern functions */
    test_internal_trig();
    test_internal_gamma();
    test_internal_classify();
    test_internal_complex();

    /* Bridged static functions */
    test_bridge_tan();
    test_bridge_tanf();
    test_bridge_ctans();
    test_bridge_ctansf();
    test_bridge_sin_pi();
    test_bridge_sin_pif();
    test_bridge_rem_pio2_internal();
    test_bridge_rem_pio2f_internal();

    return 0;
}
