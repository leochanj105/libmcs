/* test_suite.c — comprehensive test suite for libmcs */

#include <stdio.h>
#include <stdint.h>
#include <float.h>

#define __LIBMCS_WANT_COMPLEX
#define LIBMCS_WANT_COMPLEX

#include "/home/leochanj/Desktop/libmcs/libm/include/math.h"
#include "/home/leochanj/Desktop/libmcs/libm/include/complex.h"
#include "/home/leochanj/Desktop/libmcs/libm/include/fenv.h"

/* Extern declarations for non-static internal functions */
extern double __sin(double x, double y, int iy);
extern double __cos(double x, double y);
extern int32_t __rem_pio2(double x, double *y);
extern double __lgamma(double x, int *signgamp);

extern float __sinf(float x, float y, int iy);
extern float __cosf(float x, float y);
extern int32_t __rem_pio2f(float x, float *y);
extern float __lgammaf(float x, int *signgamp);

extern int __fpclassifyd(double x);
extern int __fpclassifyf(float x);
extern int __signbitd(double x);
extern int __signbitf(float x);

extern void __ccoshsinh(double x, double *c, double *s);
extern double __redupi(double x);

extern void __ccoshsinhf(float x, float *c, float *s);
extern float __redupif(float x);

extern int __signgam;

/* Extern declarations for bridge wrappers (static functions) */
extern double bridge___sin_pi(double x);
extern float bridge___sin_pif(float x);
extern int bridge___rem_pio2_internal(double *x, double *y, int e0, int nx);
extern int bridge___rem_pio2f_internal(float *x, float *y, int e0, int nx);
extern double bridge___ctans(double complex z);
extern float bridge___ctansf(float complex z);

/* ================================================================
 * Double-precision math functions
 * ================================================================ */

static void test_double_trig(void)
{
    printf("=== Double Trigonometric ===\n");

    double vals[] = {0.0, 0.5, 1.0, -1.0, M_PI/6, M_PI/4, M_PI/3, M_PI/2, M_PI, 2*M_PI, -M_PI/4, 1e-10, 1e10};
    int n = sizeof(vals)/sizeof(vals[0]);

    for (int i = 0; i < n; i++) {
        double x = vals[i];
        printf("acos %a = %a\n", x, acos(x));
        printf("asin %a = %a\n", x, asin(x));
        printf("atan %a = %a\n", x, atan(x));
        printf("cos %a = %a\n", x, cos(x));
        printf("sin %a = %a\n", x, sin(x));
        printf("tan %a = %a\n", x, tan(x));
    }

    double pairs[][2] = {{1.0, 0.0}, {0.0, 1.0}, {-1.0, -1.0}, {1.0, 1.0}, {0.0, 0.0}, {3.0, 4.0}, {-3.0, 4.0}};
    int np = sizeof(pairs)/sizeof(pairs[0]);
    for (int i = 0; i < np; i++) {
        printf("atan2 %a %a = %a\n", pairs[i][0], pairs[i][1], atan2(pairs[i][0], pairs[i][1]));
    }
}

static void test_double_hyper(void)
{
    printf("=== Double Hyperbolic ===\n");

    double vals[] = {0.0, 0.5, 1.0, -1.0, 2.0, -2.0, 0.1, 10.0, 1e-15};
    int n = sizeof(vals)/sizeof(vals[0]);

    for (int i = 0; i < n; i++) {
        double x = vals[i];
        printf("acosh %a = %a\n", x, acosh(x));
        printf("asinh %a = %a\n", x, asinh(x));
        printf("atanh %a = %a\n", x, atanh(x));
        printf("cosh %a = %a\n", x, cosh(x));
        printf("sinh %a = %a\n", x, sinh(x));
        printf("tanh %a = %a\n", x, tanh(x));
    }
}

static void test_double_explog(void)
{
    printf("=== Double Exponential/Logarithmic ===\n");

    double vals[] = {0.0, 0.5, 1.0, -1.0, 2.0, 10.0, 0.1, 1e-300, 1e300, -0.5};
    int n = sizeof(vals)/sizeof(vals[0]);

    for (int i = 0; i < n; i++) {
        double x = vals[i];
        printf("exp %a = %a\n", x, exp(x));
        printf("exp2 %a = %a\n", x, exp2(x));
        printf("expm1 %a = %a\n", x, expm1(x));
        printf("log %a = %a\n", x, log(x));
        printf("log10 %a = %a\n", x, log10(x));
        printf("log1p %a = %a\n", x, log1p(x));
        printf("log2 %a = %a\n", x, log2(x));
        printf("logb %a = %a\n", x, logb(x));
    }

    /* frexp */
    {
        double vals2[] = {0.0, 1.0, -1.0, 0.5, 2.0, 1024.0, 1e-300, 1e300};
        int n2 = sizeof(vals2)/sizeof(vals2[0]);
        for (int i = 0; i < n2; i++) {
            int exp_val;
            double r = frexp(vals2[i], &exp_val);
            printf("frexp %a = %a exp=%d\n", vals2[i], r, exp_val);
        }
    }

    /* ilogb */
    {
        double vals2[] = {0.0, 1.0, 2.0, 0.5, 1024.0, 1e-300, 1e300};
        int n2 = sizeof(vals2)/sizeof(vals2[0]);
        for (int i = 0; i < n2; i++) {
            printf("ilogb %a = %d\n", vals2[i], ilogb(vals2[i]));
        }
    }

    /* ldexp */
    {
        double bases[] = {1.0, 0.5, -1.0, 1e-300};
        int exps[] = {0, 1, -1, 10, -10, 100, -100};
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 7; j++) {
                printf("ldexp %a %d = %a\n", bases[i], exps[j], ldexp(bases[i], exps[j]));
            }
        }
    }

    /* modf */
    {
        double vals2[] = {0.0, 1.5, -1.5, 2.7, 1e10, -1e10, 0.1};
        int n2 = sizeof(vals2)/sizeof(vals2[0]);
        for (int i = 0; i < n2; i++) {
            double ipart;
            double r = modf(vals2[i], &ipart);
            printf("modf %a = %a ipart=%a\n", vals2[i], r, ipart);
        }
    }

    /* scalbn, scalbln */
    {
        double bases[] = {1.0, 0.5, -2.0};
        int exps[] = {0, 1, -1, 10, -10};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 5; j++) {
                printf("scalbn %a %d = %a\n", bases[i], exps[j], scalbn(bases[i], exps[j]));
                printf("scalbln %a %d = %a\n", bases[i], exps[j], scalbln(bases[i], (long)exps[j]));
            }
        }
    }
}

static void test_double_power(void)
{
    printf("=== Double Power/AbsVal ===\n");

    double vals[] = {0.0, 1.0, -1.0, 8.0, 27.0, 0.25, 2.0, 100.0, 1e-10, -8.0};
    int n = sizeof(vals)/sizeof(vals[0]);

    for (int i = 0; i < n; i++) {
        double x = vals[i];
        printf("cbrt %a = %a\n", x, cbrt(x));
        printf("fabs %a = %a\n", x, fabs(x));
        printf("sqrt %a = %a\n", x, sqrt(x));
    }

    /* hypot */
    {
        double pairs[][2] = {{3.0, 4.0}, {0.0, 0.0}, {1.0, 0.0}, {0.0, 1.0}, {-3.0, -4.0}, {1e300, 1e300}, {1e-300, 1e-300}};
        int np = sizeof(pairs)/sizeof(pairs[0]);
        for (int i = 0; i < np; i++) {
            printf("hypot %a %a = %a\n", pairs[i][0], pairs[i][1], hypot(pairs[i][0], pairs[i][1]));
        }
    }

    /* pow */
    {
        double pairs[][2] = {{2.0, 3.0}, {2.0, 0.5}, {2.0, -1.0}, {10.0, 2.0}, {0.0, 0.0}, {0.0, 1.0},
                             {1.0, 100.0}, {-1.0, 2.0}, {-1.0, 3.0}, {2.0, 0.0}, {2.0, 10.0}, {0.5, 0.5}};
        int np = sizeof(pairs)/sizeof(pairs[0]);
        for (int i = 0; i < np; i++) {
            printf("pow %a %a = %a\n", pairs[i][0], pairs[i][1], pow(pairs[i][0], pairs[i][1]));
        }
    }
}

static void test_double_errgamma(void)
{
    printf("=== Double Error/Gamma ===\n");

    double vals[] = {0.0, 0.5, 1.0, -0.5, 2.0, -1.5, 3.0, 5.0, 10.0, 0.1, -0.1, 100.0, 1e-10};
    int n = sizeof(vals)/sizeof(vals[0]);

    for (int i = 0; i < n; i++) {
        double x = vals[i];
        printf("erf %a = %a\n", x, erf(x));
        printf("erfc %a = %a\n", x, erfc(x));
        printf("lgamma %a = %a\n", x, lgamma(x));
        printf("tgamma %a = %a\n", x, tgamma(x));
    }
}

static void test_double_nearest(void)
{
    printf("=== Double Nearest Integer ===\n");

    double vals[] = {0.0, 0.5, 1.5, 2.5, -0.5, -1.5, -2.5, 3.7, -3.7, 1e15, -1e15, 0.1, -0.1};
    int n = sizeof(vals)/sizeof(vals[0]);

    for (int i = 0; i < n; i++) {
        double x = vals[i];
        printf("ceil %a = %a\n", x, ceil(x));
        printf("floor %a = %a\n", x, floor(x));
        printf("nearbyint %a = %a\n", x, nearbyint(x));
        printf("rint %a = %a\n", x, rint(x));
        printf("lrint %a = %ld\n", x, lrint(x));
        printf("llrint %a = %lld\n", x, llrint(x));
        printf("round %a = %a\n", x, round(x));
        printf("lround %a = %ld\n", x, lround(x));
        printf("llround %a = %lld\n", x, llround(x));
        printf("trunc %a = %a\n", x, trunc(x));
    }
}

static void test_double_remainder(void)
{
    printf("=== Double Remainder ===\n");

    double pairs[][2] = {{5.0, 2.0}, {-5.0, 2.0}, {5.0, -2.0}, {10.0, 3.0}, {0.0, 1.0},
                         {7.5, 2.5}, {1.0, 0.3}, {-10.0, 3.0}};
    int np = sizeof(pairs)/sizeof(pairs[0]);

    for (int i = 0; i < np; i++) {
        printf("fmod %a %a = %a\n", pairs[i][0], pairs[i][1], fmod(pairs[i][0], pairs[i][1]));
        printf("remainder %a %a = %a\n", pairs[i][0], pairs[i][1], remainder(pairs[i][0], pairs[i][1]));

        int quo;
        double r = remquo(pairs[i][0], pairs[i][1], &quo);
        printf("remquo %a %a = %a quo=%d\n", pairs[i][0], pairs[i][1], r, quo);
    }
}

static void test_double_manip(void)
{
    printf("=== Double Manipulation ===\n");

    /* copysign */
    {
        double pairs[][2] = {{1.0, 1.0}, {1.0, -1.0}, {-1.0, 1.0}, {-1.0, -1.0}, {0.0, -1.0}, {0.0, 1.0}};
        int np = sizeof(pairs)/sizeof(pairs[0]);
        for (int i = 0; i < np; i++) {
            printf("copysign %a %a = %a\n", pairs[i][0], pairs[i][1], copysign(pairs[i][0], pairs[i][1]));
        }
    }

    /* nan */
    printf("nan \"\" = %a\n", nan(""));
    printf("nan \"1\" = %a\n", nan("1"));

    /* nextafter */
    {
        double pairs[][2] = {{0.0, 1.0}, {0.0, -1.0}, {1.0, 2.0}, {1.0, 0.0}, {-1.0, 0.0}, {DBL_MAX, HUGE_VAL}};
        int np = sizeof(pairs)/sizeof(pairs[0]);
        for (int i = 0; i < np; i++) {
            printf("nextafter %a %a = %a\n", pairs[i][0], pairs[i][1], nextafter(pairs[i][0], pairs[i][1]));
        }
    }
}

static void test_double_minmaxdim(void)
{
    printf("=== Double Min/Max/Dim ===\n");

    double pairs[][2] = {{1.0, 2.0}, {2.0, 1.0}, {-1.0, 1.0}, {0.0, 0.0}, {-3.0, -5.0}};
    int np = sizeof(pairs)/sizeof(pairs[0]);

    for (int i = 0; i < np; i++) {
        printf("fdim %a %a = %a\n", pairs[i][0], pairs[i][1], fdim(pairs[i][0], pairs[i][1]));
        printf("fmax %a %a = %a\n", pairs[i][0], pairs[i][1], fmax(pairs[i][0], pairs[i][1]));
        printf("fmin %a %a = %a\n", pairs[i][0], pairs[i][1], fmin(pairs[i][0], pairs[i][1]));
    }
}

static void test_double_fma(void)
{
    printf("=== Double FMA ===\n");

    double triples[][3] = {{2.0, 3.0, 4.0}, {1.0, 1.0, 1.0}, {-1.0, 2.0, 3.0},
                           {1e300, 1e300, 0.0}, {1e-300, 1e-300, 0.0}, {0.0, 0.0, 0.0}};
    int nt = sizeof(triples)/sizeof(triples[0]);

    for (int i = 0; i < nt; i++) {
        printf("fma %a %a %a = %a\n", triples[i][0], triples[i][1], triples[i][2],
               fma(triples[i][0], triples[i][1], triples[i][2]));
    }
}

static void test_double_bessel(void)
{
    printf("=== Double Bessel ===\n");

    double vals[] = {0.0, 0.5, 1.0, 2.0, 5.0, 10.0, 0.1, 50.0};
    int n = sizeof(vals)/sizeof(vals[0]);

    for (int i = 0; i < n; i++) {
        double x = vals[i];
        printf("j0 %a = %a\n", x, j0(x));
        printf("j1 %a = %a\n", x, j1(x));
        printf("y0 %a = %a\n", x, y0(x));
        printf("y1 %a = %a\n", x, y1(x));
    }

    /* jn, yn with various orders */
    {
        int orders[] = {0, 1, 2, 5, 10};
        double xvals[] = {1.0, 5.0, 10.0};
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 3; j++) {
                printf("jn %d %a = %a\n", orders[i], xvals[j], jn(orders[i], xvals[j]));
                printf("yn %d %a = %a\n", orders[i], xvals[j], yn(orders[i], xvals[j]));
            }
        }
    }
}

/* ================================================================
 * Float-precision math functions
 * ================================================================ */

static void test_float_trig(void)
{
    printf("=== Float Trigonometric ===\n");

    float vals[] = {0.0f, 0.5f, 1.0f, -1.0f, (float)(M_PI/6), (float)(M_PI/4), (float)(M_PI/3), (float)(M_PI/2), (float)M_PI, (float)(2*M_PI), -0.25f*3.14159265f, 1e-5f, 1e5f};
    int n = sizeof(vals)/sizeof(vals[0]);

    for (int i = 0; i < n; i++) {
        float x = vals[i];
        printf("acosf %a = %a\n", (double)x, (double)acosf(x));
        printf("asinf %a = %a\n", (double)x, (double)asinf(x));
        printf("atanf %a = %a\n", (double)x, (double)atanf(x));
        printf("cosf %a = %a\n", (double)x, (double)cosf(x));
        printf("sinf %a = %a\n", (double)x, (double)sinf(x));
        printf("tanf %a = %a\n", (double)x, (double)tanf(x));
    }

    float pairs[][2] = {{1.0f, 0.0f}, {0.0f, 1.0f}, {-1.0f, -1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f}, {3.0f, 4.0f}};
    int np = sizeof(pairs)/sizeof(pairs[0]);
    for (int i = 0; i < np; i++) {
        printf("atan2f %a %a = %a\n", (double)pairs[i][0], (double)pairs[i][1], (double)atan2f(pairs[i][0], pairs[i][1]));
    }
}

static void test_float_hyper(void)
{
    printf("=== Float Hyperbolic ===\n");

    float vals[] = {0.0f, 0.5f, 1.0f, -1.0f, 2.0f, -2.0f, 0.1f, 10.0f};
    int n = sizeof(vals)/sizeof(vals[0]);

    for (int i = 0; i < n; i++) {
        float x = vals[i];
        printf("acoshf %a = %a\n", (double)x, (double)acoshf(x));
        printf("asinhf %a = %a\n", (double)x, (double)asinhf(x));
        printf("atanhf %a = %a\n", (double)x, (double)atanhf(x));
        printf("coshf %a = %a\n", (double)x, (double)coshf(x));
        printf("sinhf %a = %a\n", (double)x, (double)sinhf(x));
        printf("tanhf %a = %a\n", (double)x, (double)tanhf(x));
    }
}

static void test_float_explog(void)
{
    printf("=== Float Exponential/Logarithmic ===\n");

    float vals[] = {0.0f, 0.5f, 1.0f, -1.0f, 2.0f, 10.0f, 0.1f, 1e-30f, 1e30f, -0.5f};
    int n = sizeof(vals)/sizeof(vals[0]);

    for (int i = 0; i < n; i++) {
        float x = vals[i];
        printf("expf %a = %a\n", (double)x, (double)expf(x));
        printf("exp2f %a = %a\n", (double)x, (double)exp2f(x));
        printf("expm1f %a = %a\n", (double)x, (double)expm1f(x));
        printf("logf %a = %a\n", (double)x, (double)logf(x));
        printf("log10f %a = %a\n", (double)x, (double)log10f(x));
        printf("log1pf %a = %a\n", (double)x, (double)log1pf(x));
        printf("log2f %a = %a\n", (double)x, (double)log2f(x));
        printf("logbf %a = %a\n", (double)x, (double)logbf(x));
    }

    /* frexpf */
    {
        float vals2[] = {0.0f, 1.0f, -1.0f, 0.5f, 2.0f, 1024.0f};
        int n2 = sizeof(vals2)/sizeof(vals2[0]);
        for (int i = 0; i < n2; i++) {
            int exp_val;
            float r = frexpf(vals2[i], &exp_val);
            printf("frexpf %a = %a exp=%d\n", (double)vals2[i], (double)r, exp_val);
        }
    }

    /* ilogbf */
    {
        float vals2[] = {0.0f, 1.0f, 2.0f, 0.5f, 1024.0f};
        int n2 = sizeof(vals2)/sizeof(vals2[0]);
        for (int i = 0; i < n2; i++) {
            printf("ilogbf %a = %d\n", (double)vals2[i], ilogbf(vals2[i]));
        }
    }

    /* ldexpf */
    {
        float bases[] = {1.0f, 0.5f, -1.0f};
        int exps[] = {0, 1, -1, 10, -10};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 5; j++) {
                printf("ldexpf %a %d = %a\n", (double)bases[i], exps[j], (double)ldexpf(bases[i], exps[j]));
            }
        }
    }

    /* modff */
    {
        float vals2[] = {0.0f, 1.5f, -1.5f, 2.7f};
        int n2 = sizeof(vals2)/sizeof(vals2[0]);
        for (int i = 0; i < n2; i++) {
            float ipart;
            float r = modff(vals2[i], &ipart);
            printf("modff %a = %a ipart=%a\n", (double)vals2[i], (double)r, (double)ipart);
        }
    }

    /* scalbnf, scalblnf */
    {
        float bases[] = {1.0f, 0.5f, -2.0f};
        int exps[] = {0, 1, -1, 10, -10};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 5; j++) {
                printf("scalbnf %a %d = %a\n", (double)bases[i], exps[j], (double)scalbnf(bases[i], exps[j]));
                printf("scalblnf %a %d = %a\n", (double)bases[i], exps[j], (double)scalblnf(bases[i], (long)exps[j]));
            }
        }
    }
}

static void test_float_power(void)
{
    printf("=== Float Power/AbsVal ===\n");

    float vals[] = {0.0f, 1.0f, -1.0f, 8.0f, 27.0f, 0.25f, 2.0f, 100.0f, -8.0f};
    int n = sizeof(vals)/sizeof(vals[0]);

    for (int i = 0; i < n; i++) {
        float x = vals[i];
        printf("cbrtf %a = %a\n", (double)x, (double)cbrtf(x));
        printf("fabsf %a = %a\n", (double)x, (double)fabsf(x));
        printf("sqrtf %a = %a\n", (double)x, (double)sqrtf(x));
    }

    /* hypotf */
    {
        float pairs[][2] = {{3.0f, 4.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}};
        int np = sizeof(pairs)/sizeof(pairs[0]);
        for (int i = 0; i < np; i++) {
            printf("hypotf %a %a = %a\n", (double)pairs[i][0], (double)pairs[i][1], (double)hypotf(pairs[i][0], pairs[i][1]));
        }
    }

    /* powf */
    {
        float pairs[][2] = {{2.0f, 3.0f}, {2.0f, 0.5f}, {2.0f, -1.0f}, {10.0f, 2.0f}, {0.0f, 0.0f}, {1.0f, 100.0f}};
        int np = sizeof(pairs)/sizeof(pairs[0]);
        for (int i = 0; i < np; i++) {
            printf("powf %a %a = %a\n", (double)pairs[i][0], (double)pairs[i][1], (double)powf(pairs[i][0], pairs[i][1]));
        }
    }
}

static void test_float_errgamma(void)
{
    printf("=== Float Error/Gamma ===\n");

    float vals[] = {0.0f, 0.5f, 1.0f, -0.5f, 2.0f, -1.5f, 3.0f, 5.0f, 10.0f, 0.1f};
    int n = sizeof(vals)/sizeof(vals[0]);

    for (int i = 0; i < n; i++) {
        float x = vals[i];
        printf("erff %a = %a\n", (double)x, (double)erff(x));
        printf("erfcf %a = %a\n", (double)x, (double)erfcf(x));
        printf("lgammaf %a = %a\n", (double)x, (double)lgammaf(x));
        printf("tgammaf %a = %a\n", (double)x, (double)tgammaf(x));
    }
}

static void test_float_nearest(void)
{
    printf("=== Float Nearest Integer ===\n");

    float vals[] = {0.0f, 0.5f, 1.5f, 2.5f, -0.5f, -1.5f, -2.5f, 3.7f, -3.7f, 0.1f, -0.1f};
    int n = sizeof(vals)/sizeof(vals[0]);

    for (int i = 0; i < n; i++) {
        float x = vals[i];
        printf("ceilf %a = %a\n", (double)x, (double)ceilf(x));
        printf("floorf %a = %a\n", (double)x, (double)floorf(x));
        printf("nearbyintf %a = %a\n", (double)x, (double)nearbyintf(x));
        printf("rintf %a = %a\n", (double)x, (double)rintf(x));
        printf("lrintf %a = %ld\n", (double)x, lrintf(x));
        printf("llrintf %a = %lld\n", (double)x, llrintf(x));
        printf("roundf %a = %a\n", (double)x, (double)roundf(x));
        printf("lroundf %a = %ld\n", (double)x, lroundf(x));
        printf("llroundf %a = %lld\n", (double)x, llroundf(x));
        printf("truncf %a = %a\n", (double)x, (double)truncf(x));
    }
}

static void test_float_remainder(void)
{
    printf("=== Float Remainder ===\n");

    float pairs[][2] = {{5.0f, 2.0f}, {-5.0f, 2.0f}, {5.0f, -2.0f}, {10.0f, 3.0f}, {0.0f, 1.0f}, {7.5f, 2.5f}};
    int np = sizeof(pairs)/sizeof(pairs[0]);

    for (int i = 0; i < np; i++) {
        printf("fmodf %a %a = %a\n", (double)pairs[i][0], (double)pairs[i][1], (double)fmodf(pairs[i][0], pairs[i][1]));
        printf("remainderf %a %a = %a\n", (double)pairs[i][0], (double)pairs[i][1], (double)remainderf(pairs[i][0], pairs[i][1]));

        int quo;
        float r = remquof(pairs[i][0], pairs[i][1], &quo);
        printf("remquof %a %a = %a quo=%d\n", (double)pairs[i][0], (double)pairs[i][1], (double)r, quo);
    }
}

static void test_float_manip(void)
{
    printf("=== Float Manipulation ===\n");

    float pairs[][2] = {{1.0f, 1.0f}, {1.0f, -1.0f}, {-1.0f, 1.0f}, {-1.0f, -1.0f}, {0.0f, -1.0f}};
    int np = sizeof(pairs)/sizeof(pairs[0]);
    for (int i = 0; i < np; i++) {
        printf("copysignf %a %a = %a\n", (double)pairs[i][0], (double)pairs[i][1], (double)copysignf(pairs[i][0], pairs[i][1]));
    }

    printf("nanf \"\" = %a\n", (double)nanf(""));
    printf("nanf \"1\" = %a\n", (double)nanf("1"));

    float na_pairs[][2] = {{0.0f, 1.0f}, {0.0f, -1.0f}, {1.0f, 2.0f}, {1.0f, 0.0f}};
    int np2 = sizeof(na_pairs)/sizeof(na_pairs[0]);
    for (int i = 0; i < np2; i++) {
        printf("nextafterf %a %a = %a\n", (double)na_pairs[i][0], (double)na_pairs[i][1], (double)nextafterf(na_pairs[i][0], na_pairs[i][1]));
    }
}

static void test_float_minmaxdim(void)
{
    printf("=== Float Min/Max/Dim ===\n");

    float pairs[][2] = {{1.0f, 2.0f}, {2.0f, 1.0f}, {-1.0f, 1.0f}, {0.0f, 0.0f}, {-3.0f, -5.0f}};
    int np = sizeof(pairs)/sizeof(pairs[0]);

    for (int i = 0; i < np; i++) {
        printf("fdimf %a %a = %a\n", (double)pairs[i][0], (double)pairs[i][1], (double)fdimf(pairs[i][0], pairs[i][1]));
        printf("fmaxf %a %a = %a\n", (double)pairs[i][0], (double)pairs[i][1], (double)fmaxf(pairs[i][0], pairs[i][1]));
        printf("fminf %a %a = %a\n", (double)pairs[i][0], (double)pairs[i][1], (double)fminf(pairs[i][0], pairs[i][1]));
    }
}

static void test_float_fma(void)
{
    printf("=== Float FMA ===\n");

    float triples[][3] = {{2.0f, 3.0f, 4.0f}, {1.0f, 1.0f, 1.0f}, {-1.0f, 2.0f, 3.0f}, {0.0f, 0.0f, 0.0f}};
    int nt = sizeof(triples)/sizeof(triples[0]);

    for (int i = 0; i < nt; i++) {
        printf("fmaf %a %a %a = %a\n", (double)triples[i][0], (double)triples[i][1], (double)triples[i][2],
               (double)fmaf(triples[i][0], triples[i][1], triples[i][2]));
    }
}

/* ================================================================
 * Complex double functions
 * ================================================================ */

static void test_complex_double(void)
{
    printf("=== Complex Double ===\n");

    double complex vals[] = {
        CMPLX(1.0, 0.0), CMPLX(0.0, 1.0), CMPLX(1.0, 1.0),
        CMPLX(-1.0, 0.0), CMPLX(0.0, -1.0), CMPLX(-1.0, -1.0),
        CMPLX(0.5, 0.5), CMPLX(2.0, 3.0), CMPLX(0.0, 0.0),
        CMPLX(0.1, 0.2), CMPLX(10.0, 10.0)
    };
    int n = sizeof(vals)/sizeof(vals[0]);

    for (int i = 0; i < n; i++) {
        double complex z = vals[i];
        double complex r;
        double re = creal(z), im = cimag(z);

        printf("creal (%a,%a) = %a\n", re, im, creal(z));
        printf("cimag (%a,%a) = %a\n", re, im, cimag(z));
        printf("cabs (%a,%a) = %a\n", re, im, cabs(z));
        printf("carg (%a,%a) = %a\n", re, im, carg(z));

        r = conj(z);
        printf("conj (%a,%a) = (%a,%a)\n", re, im, creal(r), cimag(r));

        r = cproj(z);
        printf("cproj (%a,%a) = (%a,%a)\n", re, im, creal(r), cimag(r));

        r = cacos(z);
        printf("cacos (%a,%a) = (%a,%a)\n", re, im, creal(r), cimag(r));

        r = casin(z);
        printf("casin (%a,%a) = (%a,%a)\n", re, im, creal(r), cimag(r));

        r = catan(z);
        printf("catan (%a,%a) = (%a,%a)\n", re, im, creal(r), cimag(r));

        r = ccos(z);
        printf("ccos (%a,%a) = (%a,%a)\n", re, im, creal(r), cimag(r));

        r = csin(z);
        printf("csin (%a,%a) = (%a,%a)\n", re, im, creal(r), cimag(r));

        r = ctan(z);
        printf("ctan (%a,%a) = (%a,%a)\n", re, im, creal(r), cimag(r));

        r = cacosh(z);
        printf("cacosh (%a,%a) = (%a,%a)\n", re, im, creal(r), cimag(r));

        r = casinh(z);
        printf("casinh (%a,%a) = (%a,%a)\n", re, im, creal(r), cimag(r));

        r = catanh(z);
        printf("catanh (%a,%a) = (%a,%a)\n", re, im, creal(r), cimag(r));

        r = ccosh(z);
        printf("ccosh (%a,%a) = (%a,%a)\n", re, im, creal(r), cimag(r));

        r = csinh(z);
        printf("csinh (%a,%a) = (%a,%a)\n", re, im, creal(r), cimag(r));

        r = ctanh(z);
        printf("ctanh (%a,%a) = (%a,%a)\n", re, im, creal(r), cimag(r));

        r = cexp(z);
        printf("cexp (%a,%a) = (%a,%a)\n", re, im, creal(r), cimag(r));

        r = clog(z);
        printf("clog (%a,%a) = (%a,%a)\n", re, im, creal(r), cimag(r));

        r = csqrt(z);
        printf("csqrt (%a,%a) = (%a,%a)\n", re, im, creal(r), cimag(r));
    }

    /* cpow with a few base/exponent combos */
    {
        double complex bases[] = {CMPLX(2.0, 0.0), CMPLX(1.0, 1.0), CMPLX(0.0, 1.0)};
        double complex exps[] = {CMPLX(2.0, 0.0), CMPLX(0.5, 0.0), CMPLX(0.0, 1.0)};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                double complex r = cpow(bases[i], exps[j]);
                printf("cpow (%a,%a) (%a,%a) = (%a,%a)\n",
                       creal(bases[i]), cimag(bases[i]),
                       creal(exps[j]), cimag(exps[j]),
                       creal(r), cimag(r));
            }
        }
    }
}

/* ================================================================
 * Complex float functions
 * ================================================================ */

static void test_complex_float(void)
{
    printf("=== Complex Float ===\n");

    float complex vals[] = {
        CMPLXF(1.0f, 0.0f), CMPLXF(0.0f, 1.0f), CMPLXF(1.0f, 1.0f),
        CMPLXF(-1.0f, 0.0f), CMPLXF(0.0f, -1.0f), CMPLXF(-1.0f, -1.0f),
        CMPLXF(0.5f, 0.5f), CMPLXF(2.0f, 3.0f), CMPLXF(0.0f, 0.0f),
        CMPLXF(0.1f, 0.2f)
    };
    int n = sizeof(vals)/sizeof(vals[0]);

    for (int i = 0; i < n; i++) {
        float complex z = vals[i];
        float complex r;
        double re = (double)crealf(z), im = (double)cimagf(z);

        printf("crealf (%a,%a) = %a\n", re, im, (double)crealf(z));
        printf("cimagf (%a,%a) = %a\n", re, im, (double)cimagf(z));
        printf("cabsf (%a,%a) = %a\n", re, im, (double)cabsf(z));
        printf("cargf (%a,%a) = %a\n", re, im, (double)cargf(z));

        r = conjf(z);
        printf("conjf (%a,%a) = (%a,%a)\n", re, im, (double)crealf(r), (double)cimagf(r));

        r = cprojf(z);
        printf("cprojf (%a,%a) = (%a,%a)\n", re, im, (double)crealf(r), (double)cimagf(r));

        r = cacosf(z);
        printf("cacosf (%a,%a) = (%a,%a)\n", re, im, (double)crealf(r), (double)cimagf(r));

        r = casinf(z);
        printf("casinf (%a,%a) = (%a,%a)\n", re, im, (double)crealf(r), (double)cimagf(r));

        r = catanf(z);
        printf("catanf (%a,%a) = (%a,%a)\n", re, im, (double)crealf(r), (double)cimagf(r));

        r = ccosf(z);
        printf("ccosf (%a,%a) = (%a,%a)\n", re, im, (double)crealf(r), (double)cimagf(r));

        r = csinf(z);
        printf("csinf (%a,%a) = (%a,%a)\n", re, im, (double)crealf(r), (double)cimagf(r));

        r = ctanf(z);
        printf("ctanf (%a,%a) = (%a,%a)\n", re, im, (double)crealf(r), (double)cimagf(r));

        r = cacoshf(z);
        printf("cacoshf (%a,%a) = (%a,%a)\n", re, im, (double)crealf(r), (double)cimagf(r));

        r = casinhf(z);
        printf("casinhf (%a,%a) = (%a,%a)\n", re, im, (double)crealf(r), (double)cimagf(r));

        r = catanhf(z);
        printf("catanhf (%a,%a) = (%a,%a)\n", re, im, (double)crealf(r), (double)cimagf(r));

        r = ccoshf(z);
        printf("ccoshf (%a,%a) = (%a,%a)\n", re, im, (double)crealf(r), (double)cimagf(r));

        r = csinhf(z);
        printf("csinhf (%a,%a) = (%a,%a)\n", re, im, (double)crealf(r), (double)cimagf(r));

        r = ctanhf(z);
        printf("ctanhf (%a,%a) = (%a,%a)\n", re, im, (double)crealf(r), (double)cimagf(r));

        r = cexpf(z);
        printf("cexpf (%a,%a) = (%a,%a)\n", re, im, (double)crealf(r), (double)cimagf(r));

        r = clogf(z);
        printf("clogf (%a,%a) = (%a,%a)\n", re, im, (double)crealf(r), (double)cimagf(r));

        r = csqrtf(z);
        printf("csqrtf (%a,%a) = (%a,%a)\n", re, im, (double)crealf(r), (double)cimagf(r));
    }

    /* cpowf */
    {
        float complex bases[] = {CMPLXF(2.0f, 0.0f), CMPLXF(1.0f, 1.0f)};
        float complex exps[] = {CMPLXF(2.0f, 0.0f), CMPLXF(0.5f, 0.0f)};
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                float complex r = cpowf(bases[i], exps[j]);
                printf("cpowf (%a,%a) (%a,%a) = (%a,%a)\n",
                       (double)crealf(bases[i]), (double)cimagf(bases[i]),
                       (double)crealf(exps[j]), (double)cimagf(exps[j]),
                       (double)crealf(r), (double)cimagf(r));
            }
        }
    }
}

/* ================================================================
 * Internal functions (non-static, linked directly)
 * ================================================================ */

static void test_internal_double(void)
{
    printf("=== Internal Double ===\n");

    /* __fpclassifyd */
    {
        double vals[] = {0.0, -0.0, 1.0, -1.0, HUGE_VAL, -HUGE_VAL, 5e-324, -5e-324};
        int n = sizeof(vals)/sizeof(vals[0]);
        for (int i = 0; i < n; i++) {
            printf("__fpclassifyd %a = %d\n", vals[i], __fpclassifyd(vals[i]));
        }
        printf("__fpclassifyd NaN = %d\n", __fpclassifyd(nan("")));
    }

    /* __signbitd */
    {
        double vals[] = {0.0, -0.0, 1.0, -1.0, HUGE_VAL, -HUGE_VAL};
        int n = sizeof(vals)/sizeof(vals[0]);
        for (int i = 0; i < n; i++) {
            printf("__signbitd %a = %d\n", vals[i], __signbitd(vals[i]));
        }
    }

    /* __sin, __cos (inputs bounded to [-pi/4, pi/4]) */
    {
        double xvals[] = {0.0, 0.1, 0.5, 0.7, -0.1, -0.5, -0.7};
        int nx = sizeof(xvals)/sizeof(xvals[0]);
        for (int i = 0; i < nx; i++) {
            printf("__cos %a %a = %a\n", xvals[i], 0.0, __cos(xvals[i], 0.0));
            printf("__sin %a %a %d = %a\n", xvals[i], 0.0, 0, __sin(xvals[i], 0.0, 0));
            printf("__sin %a %a %d = %a\n", xvals[i], 0.0, 1, __sin(xvals[i], 0.0, 1));
        }
        /* with tail value */
        printf("__cos %a %a = %a\n", 0.5, 1e-18, __cos(0.5, 1e-18));
        printf("__sin %a %a %d = %a\n", 0.5, 1e-18, 1, __sin(0.5, 1e-18, 1));
    }

    /* __rem_pio2 */
    {
        double xvals[] = {0.0, 1.0, M_PI/2, M_PI, 2*M_PI, 10.0, 100.0, 1e6, -1.0, -M_PI};
        int nx = sizeof(xvals)/sizeof(xvals[0]);
        for (int i = 0; i < nx; i++) {
            double y[2];
            int32_t n = __rem_pio2(xvals[i], y);
            printf("__rem_pio2 %a = n=%d y0=%a y1=%a\n", xvals[i], n, y[0], y[1]);
        }
    }

    /* __lgamma */
    {
        double vals[] = {0.5, 1.0, 1.5, 2.0, 5.0, 10.0, -0.5, -1.5, 0.1, 100.0};
        int n = sizeof(vals)/sizeof(vals[0]);
        for (int i = 0; i < n; i++) {
            int sg;
            double r = __lgamma(vals[i], &sg);
            printf("__lgamma %a = %a signgam=%d\n", vals[i], r, sg);
        }
    }

    /* __ccoshsinh */
    {
        double xvals[] = {0.0, 0.5, 1.0, 2.0, -1.0, 0.1, 10.0};
        int nx = sizeof(xvals)/sizeof(xvals[0]);
        for (int i = 0; i < nx; i++) {
            double c, s;
            __ccoshsinh(xvals[i], &c, &s);
            printf("__ccoshsinh %a = c=%a s=%a\n", xvals[i], c, s);
        }
    }

    /* __redupi */
    {
        double xvals[] = {0.0, M_PI, 2*M_PI, -M_PI, 10.0, 100.0, -100.0};
        int nx = sizeof(xvals)/sizeof(xvals[0]);
        for (int i = 0; i < nx; i++) {
            printf("__redupi %a = %a\n", xvals[i], __redupi(xvals[i]));
        }
    }
}

static void test_internal_float(void)
{
    printf("=== Internal Float ===\n");

    /* __fpclassifyf */
    {
        float vals[] = {0.0f, -0.0f, 1.0f, -1.0f, HUGE_VALF, -HUGE_VALF, 1e-45f, -1e-45f};
        int n = sizeof(vals)/sizeof(vals[0]);
        for (int i = 0; i < n; i++) {
            printf("__fpclassifyf %a = %d\n", (double)vals[i], __fpclassifyf(vals[i]));
        }
        printf("__fpclassifyf NaN = %d\n", __fpclassifyf(nanf("")));
    }

    /* __signbitf */
    {
        float vals[] = {0.0f, -0.0f, 1.0f, -1.0f, HUGE_VALF, -HUGE_VALF};
        int n = sizeof(vals)/sizeof(vals[0]);
        for (int i = 0; i < n; i++) {
            printf("__signbitf %a = %d\n", (double)vals[i], __signbitf(vals[i]));
        }
    }

    /* __sinf, __cosf (inputs bounded to [-pi/4, pi/4]) */
    {
        float xvals[] = {0.0f, 0.1f, 0.5f, 0.7f, -0.1f, -0.5f, -0.7f};
        int nx = sizeof(xvals)/sizeof(xvals[0]);
        for (int i = 0; i < nx; i++) {
            printf("__cosf %a %a = %a\n", (double)xvals[i], 0.0, (double)__cosf(xvals[i], 0.0f));
            printf("__sinf %a %a %d = %a\n", (double)xvals[i], 0.0, 0, (double)__sinf(xvals[i], 0.0f, 0));
            printf("__sinf %a %a %d = %a\n", (double)xvals[i], 0.0, 1, (double)__sinf(xvals[i], 0.0f, 1));
        }
    }

    /* __rem_pio2f */
    {
        float xvals[] = {0.0f, 1.0f, (float)(M_PI/2), (float)M_PI, (float)(2*M_PI), 10.0f, 100.0f, 1e6f, -1.0f};
        int nx = sizeof(xvals)/sizeof(xvals[0]);
        for (int i = 0; i < nx; i++) {
            float y[2];
            int32_t n = __rem_pio2f(xvals[i], y);
            printf("__rem_pio2f %a = n=%d y0=%a y1=%a\n", (double)xvals[i], n, (double)y[0], (double)y[1]);
        }
    }

    /* __lgammaf */
    {
        float vals[] = {0.5f, 1.0f, 1.5f, 2.0f, 5.0f, 10.0f, -0.5f, -1.5f, 0.1f};
        int n = sizeof(vals)/sizeof(vals[0]);
        for (int i = 0; i < n; i++) {
            int sg;
            float r = __lgammaf(vals[i], &sg);
            printf("__lgammaf %a = %a signgam=%d\n", (double)vals[i], (double)r, sg);
        }
    }

    /* __ccoshsinhf */
    {
        float xvals[] = {0.0f, 0.5f, 1.0f, 2.0f, -1.0f, 0.1f};
        int nx = sizeof(xvals)/sizeof(xvals[0]);
        for (int i = 0; i < nx; i++) {
            float c, s;
            __ccoshsinhf(xvals[i], &c, &s);
            printf("__ccoshsinhf %a = c=%a s=%a\n", (double)xvals[i], (double)c, (double)s);
        }
    }

    /* __redupif */
    {
        float xvals[] = {0.0f, (float)M_PI, (float)(2*M_PI), (float)(-M_PI), 10.0f, 100.0f};
        int nx = sizeof(xvals)/sizeof(xvals[0]);
        for (int i = 0; i < nx; i++) {
            printf("__redupif %a = %a\n", (double)xvals[i], (double)__redupif(xvals[i]));
        }
    }
}

/* ================================================================
 * Static internal functions (via bridge)
 * ================================================================ */

static void test_bridge_functions(void)
{
    printf("=== Bridge (Static Internal) Functions ===\n");

    /* bridge___sin_pi */
    {
        double vals[] = {-0.5, -1.0, -1.5, -2.0, -2.5, -3.0, -0.25, -0.1, -10.0, -100.0};
        int n = sizeof(vals)/sizeof(vals[0]);
        for (int i = 0; i < n; i++) {
            printf("bridge___sin_pi %a = %a\n", vals[i], bridge___sin_pi(vals[i]));
        }
    }

    /* bridge___sin_pif */
    {
        float vals[] = {-0.5f, -1.0f, -1.5f, -2.0f, -2.5f, -3.0f, -0.25f, -0.1f, -10.0f};
        int n = sizeof(vals)/sizeof(vals[0]);
        for (int i = 0; i < n; i++) {
            printf("bridge___sin_pif %a = %a\n", (double)vals[i], (double)bridge___sin_pif(vals[i]));
        }
    }

    /* bridge___rem_pio2_internal (double) */
    {
        /* Test with a decomposed large angle: x = 900000.0, e0 = ilogb(z)-23 */
        double tx[3] = {13750.0, 8192.0, 0.0};
        double y[2];
        int n = bridge___rem_pio2_internal(tx, y, -4, 2);
        printf("bridge___rem_pio2_internal [%a,%a] e0=-4 nx=2 = n=%d y0=%a y1=%a\n",
               tx[0], tx[1], n, y[0], y[1]);

        /* Simple case */
        double tx2[3] = {1.0, 0.0, 0.0};
        double y2[2];
        int n2 = bridge___rem_pio2_internal(tx2, y2, 1, 1);
        printf("bridge___rem_pio2_internal [%a] e0=1 nx=1 = n=%d y0=%a y1=%a\n",
               tx2[0], n2, y2[0], y2[1]);
    }

    /* bridge___rem_pio2f_internal (float) */
    {
        float tx[3] = {162.0f, 0.0f, 0.0f};
        float y[2];
        int n = bridge___rem_pio2f_internal(tx, y, 1, 1);
        printf("bridge___rem_pio2f_internal [%a] e0=1 nx=1 = n=%d y0=%a y1=%a\n",
               (double)tx[0], n, (double)y[0], (double)y[1]);
    }

    /* bridge___ctans */
    {
        double complex vals[] = {CMPLX(0.1, 0.1), CMPLX(0.5, 0.5), CMPLX(1.0, 0.5), CMPLX(0.0, 1.0)};
        int n = sizeof(vals)/sizeof(vals[0]);
        for (int i = 0; i < n; i++) {
            printf("bridge___ctans (%a,%a) = %a\n", creal(vals[i]), cimag(vals[i]), bridge___ctans(vals[i]));
        }
    }

    /* bridge___ctansf */
    {
        float complex vals[] = {CMPLXF(0.1f, 0.1f), CMPLXF(0.5f, 0.5f), CMPLXF(1.0f, 0.5f), CMPLXF(0.0f, 1.0f)};
        int n = sizeof(vals)/sizeof(vals[0]);
        for (int i = 0; i < n; i++) {
            printf("bridge___ctansf (%a,%a) = %a\n", (double)crealf(vals[i]), (double)cimagf(vals[i]), (double)bridge___ctansf(vals[i]));
        }
    }
}

/* ================================================================
 * Classification macros / signgam
 * ================================================================ */

static void test_classification(void)
{
    printf("=== Classification ===\n");

    double dvals[] = {0.0, -0.0, 1.0, -1.0, HUGE_VAL, -HUGE_VAL, 5e-324};
    int nd = sizeof(dvals)/sizeof(dvals[0]);
    double dnan = nan("");

    for (int i = 0; i < nd; i++) {
        printf("fpclassify(d) %a = %d\n", dvals[i], fpclassify(dvals[i]));
        printf("isfinite(d) %a = %d\n", dvals[i], isfinite(dvals[i]));
        printf("isinf(d) %a = %d\n", dvals[i], isinf(dvals[i]));
        printf("isnan(d) %a = %d\n", dvals[i], isnan(dvals[i]));
        printf("isnormal(d) %a = %d\n", dvals[i], isnormal(dvals[i]));
        printf("signbit(d) %a = %d\n", dvals[i], signbit(dvals[i]));
    }
    printf("isnan(d) NaN = %d\n", isnan(dnan));
    printf("fpclassify(d) NaN = %d\n", fpclassify(dnan));

    float fvals[] = {0.0f, -0.0f, 1.0f, -1.0f, HUGE_VALF, -HUGE_VALF, 1e-45f};
    int nf = sizeof(fvals)/sizeof(fvals[0]);
    float fnan = nanf("");

    for (int i = 0; i < nf; i++) {
        printf("fpclassify(f) %a = %d\n", (double)fvals[i], fpclassify(fvals[i]));
        printf("isfinite(f) %a = %d\n", (double)fvals[i], isfinite(fvals[i]));
        printf("isinf(f) %a = %d\n", (double)fvals[i], isinf(fvals[i]));
        printf("isnan(f) %a = %d\n", (double)fvals[i], isnan(fvals[i]));
        printf("isnormal(f) %a = %d\n", (double)fvals[i], isnormal(fvals[i]));
        printf("signbit(f) %a = %d\n", (double)fvals[i], signbit(fvals[i]));
    }
    printf("isnan(f) NaN = %d\n", isnan(fnan));
    printf("fpclassify(f) NaN = %d\n", fpclassify(fnan));

    /* signgam */
    lgamma(2.0);
    printf("signgam after lgamma(2.0) = %d\n", signgam);
    lgamma(-0.5);
    printf("signgam after lgamma(-0.5) = %d\n", signgam);
}

/* ================================================================
 * Special values / edge cases
 * ================================================================ */

static void test_special_values(void)
{
    printf("=== Special Values ===\n");

    double pinf = HUGE_VAL;
    double ninf = -HUGE_VAL;
    double dnan = nan("");
    double pzero = 0.0;
    double nzero = -0.0;
    double subnorm = 5e-324;

    /* Trig with special values */
    printf("sin +inf = %a\n", sin(pinf));
    printf("sin -inf = %a\n", sin(ninf));
    printf("sin NaN = %a\n", sin(dnan));
    printf("sin +0 = %a\n", sin(pzero));
    printf("sin -0 = %a\n", sin(nzero));
    printf("cos +inf = %a\n", cos(pinf));
    printf("cos NaN = %a\n", cos(dnan));
    printf("cos 0 = %a\n", cos(pzero));

    printf("tan +inf = %a\n", tan(pinf));
    printf("tan NaN = %a\n", tan(dnan));

    printf("asin 2 = %a\n", asin(2.0));
    printf("acos 2 = %a\n", acos(2.0));

    /* Exp/log with special values */
    printf("exp +inf = %a\n", exp(pinf));
    printf("exp -inf = %a\n", exp(ninf));
    printf("exp NaN = %a\n", exp(dnan));
    printf("log 0 = %a\n", log(pzero));
    printf("log -0 = %a\n", log(nzero));
    printf("log -1 = %a\n", log(-1.0));
    printf("log +inf = %a\n", log(pinf));
    printf("log NaN = %a\n", log(dnan));

    /* Power with special values */
    printf("sqrt -1 = %a\n", sqrt(-1.0));
    printf("sqrt +inf = %a\n", sqrt(pinf));
    printf("sqrt NaN = %a\n", sqrt(dnan));
    printf("pow 0 0 = %a\n", pow(0.0, 0.0));
    printf("pow 1 inf = %a\n", pow(1.0, pinf));
    printf("pow inf 0 = %a\n", pow(pinf, 0.0));
    printf("pow inf inf = %a\n", pow(pinf, pinf));

    /* Subnormal */
    printf("sin subnorm = %a\n", sin(subnorm));
    printf("cos subnorm = %a\n", cos(subnorm));
    printf("exp subnorm = %a\n", exp(subnorm));
    printf("log subnorm = %a\n", log(subnorm));
    printf("sqrt subnorm = %a\n", sqrt(subnorm));

    /* Float special values */
    float finf = HUGE_VALF;
    float fnan_val = nanf("");
    printf("sinf +inf = %a\n", (double)sinf(finf));
    printf("sinf NaN = %a\n", (double)sinf(fnan_val));
    printf("cosf +inf = %a\n", (double)cosf(finf));
    printf("expf +inf = %a\n", (double)expf(finf));
    printf("expf -inf = %a\n", (double)expf(-finf));
    printf("logf 0 = %a\n", (double)logf(0.0f));
    printf("sqrtf -1 = %a\n", (double)sqrtf(-1.0f));
}

/* ================================================================
 * Long double functions (aliases of double when long double is 64-bit)
 * ================================================================ */

static void test_long_double(void)
{
    printf("=== Long Double ===\n");

    /* Note: on this platform, long double may or may not be 64-bit.
       We test a representative sample. */
    long double vals[] = {0.0L, 0.5L, 1.0L, -1.0L, 2.0L, 10.0L};
    int n = sizeof(vals)/sizeof(vals[0]);

    for (int i = 0; i < n; i++) {
        long double x = vals[i];
        /* Print as double since %La may not be portable */
        printf("cosl %a = %a\n", (double)x, (double)cosl(x));
        printf("sinl %a = %a\n", (double)x, (double)sinl(x));
        printf("tanl %a = %a\n", (double)x, (double)tanl(x));
        printf("acosl %a = %a\n", (double)x, (double)acosl(x));
        printf("asinl %a = %a\n", (double)x, (double)asinl(x));
        printf("atanl %a = %a\n", (double)x, (double)atanl(x));
        printf("expl %a = %a\n", (double)x, (double)expl(x));
        printf("logl %a = %a\n", (double)x, (double)logl(x));
        printf("sqrtl %a = %a\n", (double)x, (double)sqrtl(x));
        printf("fabsl %a = %a\n", (double)x, (double)fabsl(x));
        printf("ceill %a = %a\n", (double)x, (double)ceill(x));
        printf("floorl %a = %a\n", (double)x, (double)floorl(x));
        printf("roundl %a = %a\n", (double)x, (double)roundl(x));
        printf("truncl %a = %a\n", (double)x, (double)truncl(x));
    }

    /* A few more long double functions */
    printf("atan2l %a %a = %a\n", 1.0, 1.0, (double)atan2l(1.0L, 1.0L));
    printf("powl %a %a = %a\n", 2.0, 3.0, (double)powl(2.0L, 3.0L));
    printf("fmodl %a %a = %a\n", 5.0, 2.0, (double)fmodl(5.0L, 2.0L));
    printf("hypotl %a %a = %a\n", 3.0, 4.0, (double)hypotl(3.0L, 4.0L));
    printf("cbrtl %a = %a\n", 27.0, (double)cbrtl(27.0L));
    printf("exp2l %a = %a\n", 10.0, (double)exp2l(10.0L));
    printf("log2l %a = %a\n", 1024.0, (double)log2l(1024.0L));
    printf("log10l %a = %a\n", 1000.0, (double)log10l(1000.0L));
    printf("erfl %a = %a\n", 1.0, (double)erfl(1.0L));
    printf("erfcl %a = %a\n", 1.0, (double)erfcl(1.0L));
    printf("lgammal %a = %a\n", 5.0, (double)lgammal(5.0L));
    printf("tgammal %a = %a\n", 5.0, (double)tgammal(5.0L));
    printf("coshl %a = %a\n", 1.0, (double)coshl(1.0L));
    printf("sinhl %a = %a\n", 1.0, (double)sinhl(1.0L));
    printf("tanhl %a = %a\n", 1.0, (double)tanhl(1.0L));
    printf("acoshl %a = %a\n", 2.0, (double)acoshl(2.0L));
    printf("asinhl %a = %a\n", 1.0, (double)asinhl(1.0L));
    printf("atanhl %a = %a\n", 0.5, (double)atanhl(0.5L));
    printf("expm1l %a = %a\n", 1.0, (double)expm1l(1.0L));
    printf("log1pl %a = %a\n", 1.0, (double)log1pl(1.0L));
    printf("logbl %a = %a\n", 1024.0, (double)logbl(1024.0L));
    printf("scalbnl %a %d = %a\n", 1.0, 10, (double)scalbnl(1.0L, 10));
    printf("scalblnl %a %d = %a\n", 1.0, 10, (double)scalblnl(1.0L, 10L));
    printf("nearbyintl %a = %a\n", 1.5, (double)nearbyintl(1.5L));
    printf("rintl %a = %a\n", 1.5, (double)rintl(1.5L));
    printf("lrintl %a = %ld\n", 1.5, lrintl(1.5L));
    printf("llrintl %a = %lld\n", 1.5, llrintl(1.5L));
    printf("lroundl %a = %ld\n", 1.5, lroundl(1.5L));
    printf("llroundl %a = %lld\n", 1.5, llroundl(1.5L));
    printf("remainderl %a %a = %a\n", 5.0, 2.0, (double)remainderl(5.0L, 2.0L));
    {
        int quo;
        long double r = remquol(5.0L, 2.0L, &quo);
        printf("remquol %a %a = %a quo=%d\n", 5.0, 2.0, (double)r, quo);
    }
    printf("copysignl %a %a = %a\n", 1.0, -1.0, (double)copysignl(1.0L, -1.0L));
    printf("nanl = %a\n", (double)nanl(""));
    printf("nextafterl %a %a = %a\n", 1.0, 2.0, (double)nextafterl(1.0L, 2.0L));
    printf("nexttoward %a %a = %a\n", 1.0, 2.0, nexttoward(1.0, 2.0L));
    printf("nexttowardf %a %a = %a\n", 1.0, 2.0, (double)nexttowardf(1.0f, 2.0L));
    printf("nexttowardl %a %a = %a\n", 1.0, 2.0, (double)nexttowardl(1.0L, 2.0L));
    printf("fdiml %a %a = %a\n", 5.0, 3.0, (double)fdiml(5.0L, 3.0L));
    printf("fmaxl %a %a = %a\n", 5.0, 3.0, (double)fmaxl(5.0L, 3.0L));
    printf("fminl %a %a = %a\n", 5.0, 3.0, (double)fminl(5.0L, 3.0L));
    printf("fmal %a %a %a = %a\n", 2.0, 3.0, 4.0, (double)fmal(2.0L, 3.0L, 4.0L));
    {
        int exp_val;
        long double r = frexpl(1024.0L, &exp_val);
        printf("frexpl %a = %a exp=%d\n", 1024.0, (double)r, exp_val);
    }
    printf("ilogbl %a = %d\n", 1024.0, ilogbl(1024.0L));
    printf("ldexpl %a %d = %a\n", 1.0, 10, (double)ldexpl(1.0L, 10));
    {
        long double ipart;
        long double r = modfl(2.7L, &ipart);
        printf("modfl %a = %a ipart=%a\n", 2.7, (double)r, (double)ipart);
    }
}

/* ================================================================
 * Complex long double functions
 * ================================================================ */

static void test_complex_long_double(void)
{
    printf("=== Complex Long Double ===\n");

    long double complex vals[] = {
        CMPLXL(1.0L, 0.0L), CMPLXL(0.0L, 1.0L), CMPLXL(1.0L, 1.0L),
        CMPLXL(-1.0L, 0.0L), CMPLXL(0.5L, 0.5L)
    };
    int n = sizeof(vals)/sizeof(vals[0]);

    for (int i = 0; i < n; i++) {
        long double complex z = vals[i];
        long double complex r;
        double re = (double)creall(z), im = (double)cimagl(z);

        printf("creall (%a,%a) = %a\n", re, im, (double)creall(z));
        printf("cimagl (%a,%a) = %a\n", re, im, (double)cimagl(z));
        printf("cabsl (%a,%a) = %a\n", re, im, (double)cabsl(z));
        printf("cargl (%a,%a) = %a\n", re, im, (double)cargl(z));

        r = conjl(z);
        printf("conjl (%a,%a) = (%a,%a)\n", re, im, (double)creall(r), (double)cimagl(r));

        r = cprojl(z);
        printf("cprojl (%a,%a) = (%a,%a)\n", re, im, (double)creall(r), (double)cimagl(r));

        r = cacosl(z);
        printf("cacosl (%a,%a) = (%a,%a)\n", re, im, (double)creall(r), (double)cimagl(r));

        r = casinl(z);
        printf("casinl (%a,%a) = (%a,%a)\n", re, im, (double)creall(r), (double)cimagl(r));

        r = catanl(z);
        printf("catanl (%a,%a) = (%a,%a)\n", re, im, (double)creall(r), (double)cimagl(r));

        r = ccosl(z);
        printf("ccosl (%a,%a) = (%a,%a)\n", re, im, (double)creall(r), (double)cimagl(r));

        r = csinl(z);
        printf("csinl (%a,%a) = (%a,%a)\n", re, im, (double)creall(r), (double)cimagl(r));

        r = ctanl(z);
        printf("ctanl (%a,%a) = (%a,%a)\n", re, im, (double)creall(r), (double)cimagl(r));

        r = cacoshl(z);
        printf("cacoshl (%a,%a) = (%a,%a)\n", re, im, (double)creall(r), (double)cimagl(r));

        r = casinhl(z);
        printf("casinhl (%a,%a) = (%a,%a)\n", re, im, (double)creall(r), (double)cimagl(r));

        r = catanhl(z);
        printf("catanhl (%a,%a) = (%a,%a)\n", re, im, (double)creall(r), (double)cimagl(r));

        r = ccoshl(z);
        printf("ccoshl (%a,%a) = (%a,%a)\n", re, im, (double)creall(r), (double)cimagl(r));

        r = csinhl(z);
        printf("csinhl (%a,%a) = (%a,%a)\n", re, im, (double)creall(r), (double)cimagl(r));

        r = ctanhl(z);
        printf("ctanhl (%a,%a) = (%a,%a)\n", re, im, (double)creall(r), (double)cimagl(r));

        r = cexpl(z);
        printf("cexpl (%a,%a) = (%a,%a)\n", re, im, (double)creall(r), (double)cimagl(r));

        r = clogl(z);
        printf("clogl (%a,%a) = (%a,%a)\n", re, im, (double)creall(r), (double)cimagl(r));

        r = csqrtl(z);
        printf("csqrtl (%a,%a) = (%a,%a)\n", re, im, (double)creall(r), (double)cimagl(r));
    }

    /* cpowl */
    {
        long double complex base = CMPLXL(2.0L, 1.0L);
        long double complex exp_val = CMPLXL(2.0L, 0.0L);
        long double complex r = cpowl(base, exp_val);
        printf("cpowl (%a,%a) (%a,%a) = (%a,%a)\n",
               (double)creall(base), (double)cimagl(base),
               (double)creall(exp_val), (double)cimagl(exp_val),
               (double)creall(r), (double)cimagl(r));
    }
}

/* ================================================================
 * Fenv functions
 * ================================================================ */

static void test_fenv(void)
{
    printf("=== Floating-Point Environment ===\n");

    printf("fegetround = %d\n", fegetround());
    printf("fesetround FE_TONEAREST = %d\n", fesetround(0));

    printf("feclearexcept all = %d\n", feclearexcept(0x1f));
    printf("fetestexcept all = %d\n", fetestexcept(0x1f));
    printf("feraiseexcept FE_INVALID = %d\n", feraiseexcept(0x01));

    fexcept_t flag;
    printf("fegetexceptflag = %d\n", fegetexceptflag(&flag, 0x1f));
    printf("fesetexceptflag = %d\n", fesetexceptflag(&flag, 0x1f));

    fenv_t env;
    printf("fegetenv = %d\n", fegetenv(&env));
    printf("fesetenv = %d\n", fesetenv(&env));
    printf("feholdexcept = %d\n", feholdexcept(&env));
    printf("feupdateenv = %d\n", feupdateenv(&env));
}

/* ================================================================
 * main
 * ================================================================ */

int main(void)
{
    /* Double-precision */
    test_double_trig();
    test_double_hyper();
    test_double_explog();
    test_double_power();
    test_double_errgamma();
    test_double_nearest();
    test_double_remainder();
    test_double_manip();
    test_double_minmaxdim();
    test_double_fma();
    test_double_bessel();

    /* Float-precision */
    test_float_trig();
    test_float_hyper();
    test_float_explog();
    test_float_power();
    test_float_errgamma();
    test_float_nearest();
    test_float_remainder();
    test_float_manip();
    test_float_minmaxdim();
    test_float_fma();

    /* Complex double */
    test_complex_double();

    /* Complex float */
    test_complex_float();

    /* Internal functions (non-static) */
    test_internal_double();
    test_internal_float();

    /* Static internal functions via bridge */
    test_bridge_functions();

    /* Classification macros and signgam */
    test_classification();

    /* Special values / edge cases */
    test_special_values();

    /* Long double */
    test_long_double();

    /* Complex long double */
    test_complex_long_double();

    /* Fenv */
    test_fenv();

    printf("=== ALL TESTS COMPLETE ===\n");
    return 0;
}
