/* test_suite.c — generated test suite for libmcs */
#include <stdio.h>
#include <stdint.h>
#include <complex.h>
#include "test_bridge.h"

/* Headers from the library */
#include "/home/leochanj/Desktop/libmcs/libm/include/math.h"
#include "/home/leochanj/Desktop/libmcs/libm/include/complex.h"

/* Declarations for non-static internal functions not in public headers */
extern double __cos(double x, double y);
extern double __sin(double x, double y, int iy);
extern int32_t __rem_pio2(double x, double *y);
extern float __cosf(float x, float y);
extern float __sinf(float x, float y, int iy);
extern int32_t __rem_pio2f(float x, float *y);
extern double __lgamma(double x, int *signgamp);
extern float __lgammaf(float x, int *signgamp);
extern double __redupi(double x);
extern float __redupif(float x);
extern void __ccoshsinh(double x, double *c, double *s);
extern void __ccoshsinhf(float x, float *c, float *s);

/* ------------------------------------------------------------------ */
/* Double trigonometric */
/* ------------------------------------------------------------------ */
static void test_acos(void)
{
    printf("acos %a = %a\n", 0.5, acos(0.5));
    printf("acos %a = %a\n", 1.0, acos(1.0));
    printf("acos %a = %a\n", -1.0, acos(-1.0));
    printf("acos %a = %a\n", 0.0, acos(0.0));
}

static void test_asin(void)
{
    printf("asin %a = %a\n", 0.5, asin(0.5));
    printf("asin %a = %a\n", 1.0, asin(1.0));
    printf("asin %a = %a\n", -1.0, asin(-1.0));
    printf("asin %a = %a\n", 0.0, asin(0.0));
}

static void test_atan(void)
{
    printf("atan %a = %a\n", 1.0, atan(1.0));
    printf("atan %a = %a\n", 0.0, atan(0.0));
    printf("atan %a = %a\n", -1.0, atan(-1.0));
}

static void test_atan2(void)
{
    printf("atan2 %a %a = %a\n", 1.0, 1.0, atan2(1.0, 1.0));
    printf("atan2 %a %a = %a\n", 0.0, 1.0, atan2(0.0, 1.0));
    printf("atan2 %a %a = %a\n", 1.0, 0.0, atan2(1.0, 0.0));
    printf("atan2 %a %a = %a\n", -1.0, -1.0, atan2(-1.0, -1.0));
}

static void test_cos(void)
{
    printf("cos %a = %a\n", 0.0, cos(0.0));
    printf("cos %a = %a\n", 1.0, cos(1.0));
    printf("cos %a = %a\n", M_PI, cos(M_PI));
}

static void test_sin(void)
{
    printf("sin %a = %a\n", 0.0, sin(0.0));
    printf("sin %a = %a\n", 1.0, sin(1.0));
    printf("sin %a = %a\n", M_PI_2, sin(M_PI_2));
}

static void test_tan(void)
{
    printf("tan %a = %a\n", 0.0, tan(0.0));
    printf("tan %a = %a\n", 1.0, tan(1.0));
    printf("tan %a = %a\n", -1.0, tan(-1.0));
}

/* ------------------------------------------------------------------ */
/* Double hyperbolic */
/* ------------------------------------------------------------------ */
static void test_acosh(void)
{
    printf("acosh %a = %a\n", 1.0, acosh(1.0));
    printf("acosh %a = %a\n", 2.0, acosh(2.0));
}

static void test_asinh(void)
{
    printf("asinh %a = %a\n", 0.0, asinh(0.0));
    printf("asinh %a = %a\n", 1.0, asinh(1.0));
    printf("asinh %a = %a\n", -1.0, asinh(-1.0));
}

static void test_atanh(void)
{
    printf("atanh %a = %a\n", 0.0, atanh(0.0));
    printf("atanh %a = %a\n", 0.5, atanh(0.5));
    printf("atanh %a = %a\n", -0.5, atanh(-0.5));
}

static void test_cosh(void)
{
    printf("cosh %a = %a\n", 0.0, cosh(0.0));
    printf("cosh %a = %a\n", 1.0, cosh(1.0));
    printf("cosh %a = %a\n", -1.0, cosh(-1.0));
}

static void test_sinh(void)
{
    printf("sinh %a = %a\n", 0.0, sinh(0.0));
    printf("sinh %a = %a\n", 1.0, sinh(1.0));
    printf("sinh %a = %a\n", -1.0, sinh(-1.0));
}

static void test_tanh(void)
{
    printf("tanh %a = %a\n", 0.0, tanh(0.0));
    printf("tanh %a = %a\n", 1.0, tanh(1.0));
    printf("tanh %a = %a\n", -1.0, tanh(-1.0));
}

/* ------------------------------------------------------------------ */
/* Double exponential and logarithmic */
/* ------------------------------------------------------------------ */
static void test_exp(void)
{
    printf("exp %a = %a\n", 0.0, exp(0.0));
    printf("exp %a = %a\n", 1.0, exp(1.0));
    printf("exp %a = %a\n", -1.0, exp(-1.0));
}

static void test_exp2(void)
{
    printf("exp2 %a = %a\n", 0.0, exp2(0.0));
    printf("exp2 %a = %a\n", 1.0, exp2(1.0));
    printf("exp2 %a = %a\n", 3.0, exp2(3.0));
}

static void test_expm1(void)
{
    printf("expm1 %a = %a\n", 0.0, expm1(0.0));
    printf("expm1 %a = %a\n", 1.0, expm1(1.0));
    printf("expm1 %a = %a\n", -1.0, expm1(-1.0));
}

static void test_frexp(void)
{
    int exp_val;
    double r = frexp(1.0, &exp_val);
    printf("frexp %a = %a exp=%d\n", 1.0, r, exp_val);
    r = frexp(0.5, &exp_val);
    printf("frexp %a = %a exp=%d\n", 0.5, r, exp_val);
    r = frexp(0.0, &exp_val);
    printf("frexp %a = %a exp=%d\n", 0.0, r, exp_val);
}

static void test_ilogb(void)
{
    printf("ilogb %a = %d\n", 1.0, ilogb(1.0));
    printf("ilogb %a = %d\n", 2.0, ilogb(2.0));
    printf("ilogb %a = %d\n", 0.5, ilogb(0.5));
}

static void test_ldexp(void)
{
    printf("ldexp %a %d = %a\n", 1.0, 2, ldexp(1.0, 2));
    printf("ldexp %a %d = %a\n", 0.5, 3, ldexp(0.5, 3));
    printf("ldexp %a %d = %a\n", 1.0, -1, ldexp(1.0, -1));
}

static void test_log(void)
{
    printf("log %a = %a\n", 1.0, log(1.0));
    printf("log %a = %a\n", M_E, log(M_E));
    printf("log %a = %a\n", 2.0, log(2.0));
}

static void test_log10(void)
{
    printf("log10 %a = %a\n", 1.0, log10(1.0));
    printf("log10 %a = %a\n", 10.0, log10(10.0));
    printf("log10 %a = %a\n", 100.0, log10(100.0));
}

static void test_log1p(void)
{
    printf("log1p %a = %a\n", 0.0, log1p(0.0));
    printf("log1p %a = %a\n", 1.0, log1p(1.0));
    printf("log1p %a = %a\n", -0.5, log1p(-0.5));
}

static void test_log2(void)
{
    printf("log2 %a = %a\n", 1.0, log2(1.0));
    printf("log2 %a = %a\n", 2.0, log2(2.0));
    printf("log2 %a = %a\n", 8.0, log2(8.0));
}

static void test_logb(void)
{
    printf("logb %a = %a\n", 1.0, logb(1.0));
    printf("logb %a = %a\n", 2.0, logb(2.0));
    printf("logb %a = %a\n", 0.5, logb(0.5));
}

static void test_modf(void)
{
    double int_part;
    double r = modf(3.75, &int_part);
    printf("modf %a = %a int=%a\n", 3.75, r, int_part);
    r = modf(-2.5, &int_part);
    printf("modf %a = %a int=%a\n", -2.5, r, int_part);
}

static void test_scalbn(void)
{
    printf("scalbn %a %d = %a\n", 1.0, 2, scalbn(1.0, 2));
    printf("scalbn %a %d = %a\n", 1.5, -1, scalbn(1.5, -1));
}

static void test_scalbln(void)
{
    printf("scalbln %a %ld = %a\n", 1.0, 2L, scalbln(1.0, 2L));
    printf("scalbln %a %ld = %a\n", 1.5, -1L, scalbln(1.5, -1L));
}

/* ------------------------------------------------------------------ */
/* Double power and absolute value */
/* ------------------------------------------------------------------ */
static void test_cbrt(void)
{
    printf("cbrt %a = %a\n", 8.0, cbrt(8.0));
    printf("cbrt %a = %a\n", -27.0, cbrt(-27.0));
    printf("cbrt %a = %a\n", 0.0, cbrt(0.0));
}

static void test_fabs(void)
{
    printf("fabs %a = %a\n", -1.5, fabs(-1.5));
    printf("fabs %a = %a\n", 1.5, fabs(1.5));
    printf("fabs %a = %a\n", 0.0, fabs(0.0));
}

static void test_hypot(void)
{
    printf("hypot %a %a = %a\n", 3.0, 4.0, hypot(3.0, 4.0));
    printf("hypot %a %a = %a\n", 1.0, 0.0, hypot(1.0, 0.0));
}

static void test_pow(void)
{
    printf("pow %a %a = %a\n", 2.0, 10.0, pow(2.0, 10.0));
    printf("pow %a %a = %a\n", 4.0, 0.5, pow(4.0, 0.5));
    printf("pow %a %a = %a\n", 1.0, 0.0, pow(1.0, 0.0));
}

static void test_sqrt(void)
{
    printf("sqrt %a = %a\n", 4.0, sqrt(4.0));
    printf("sqrt %a = %a\n", 2.0, sqrt(2.0));
    printf("sqrt %a = %a\n", 0.0, sqrt(0.0));
}

/* ------------------------------------------------------------------ */
/* Double error and gamma */
/* ------------------------------------------------------------------ */
static void test_erf(void)
{
    printf("erf %a = %a\n", 0.0, erf(0.0));
    printf("erf %a = %a\n", 1.0, erf(1.0));
    printf("erf %a = %a\n", -1.0, erf(-1.0));
}

static void test_erfc(void)
{
    printf("erfc %a = %a\n", 0.0, erfc(0.0));
    printf("erfc %a = %a\n", 1.0, erfc(1.0));
    printf("erfc %a = %a\n", -1.0, erfc(-1.0));
}

static void test_lgamma(void)
{
    printf("lgamma %a = %a\n", 1.0, lgamma(1.0));
    printf("lgamma %a = %a\n", 2.0, lgamma(2.0));
    printf("lgamma %a = %a\n", 0.5, lgamma(0.5));
}

static void test_tgamma(void)
{
    printf("tgamma %a = %a\n", 1.0, tgamma(1.0));
    printf("tgamma %a = %a\n", 2.0, tgamma(2.0));
    printf("tgamma %a = %a\n", 0.5, tgamma(0.5));
}

/* ------------------------------------------------------------------ */
/* Double nearest integer */
/* ------------------------------------------------------------------ */
static void test_ceil(void)
{
    printf("ceil %a = %a\n", 1.2, ceil(1.2));
    printf("ceil %a = %a\n", -1.2, ceil(-1.2));
    printf("ceil %a = %a\n", 2.0, ceil(2.0));
}

static void test_floor(void)
{
    printf("floor %a = %a\n", 1.7, floor(1.7));
    printf("floor %a = %a\n", -1.7, floor(-1.7));
    printf("floor %a = %a\n", 2.0, floor(2.0));
}

static void test_nearbyint(void)
{
    printf("nearbyint %a = %a\n", 1.5, nearbyint(1.5));
    printf("nearbyint %a = %a\n", 2.5, nearbyint(2.5));
    printf("nearbyint %a = %a\n", -1.5, nearbyint(-1.5));
}

static void test_rint(void)
{
    printf("rint %a = %a\n", 1.5, rint(1.5));
    printf("rint %a = %a\n", 2.5, rint(2.5));
    printf("rint %a = %a\n", -1.5, rint(-1.5));
}

static void test_lrint(void)
{
    printf("lrint %a = %ld\n", 1.5, lrint(1.5));
    printf("lrint %a = %ld\n", -1.5, lrint(-1.5));
}

static void test_llrint(void)
{
    printf("llrint %a = %lld\n", 1.5, llrint(1.5));
    printf("llrint %a = %lld\n", -1.5, llrint(-1.5));
}

static void test_round(void)
{
    printf("round %a = %a\n", 1.5, round(1.5));
    printf("round %a = %a\n", 2.5, round(2.5));
    printf("round %a = %a\n", -1.5, round(-1.5));
}

static void test_lround(void)
{
    printf("lround %a = %ld\n", 1.5, lround(1.5));
    printf("lround %a = %ld\n", -1.5, lround(-1.5));
}

static void test_llround(void)
{
    printf("llround %a = %lld\n", 1.5, llround(1.5));
    printf("llround %a = %lld\n", -1.5, llround(-1.5));
}

static void test_trunc(void)
{
    printf("trunc %a = %a\n", 1.7, trunc(1.7));
    printf("trunc %a = %a\n", -1.7, trunc(-1.7));
    printf("trunc %a = %a\n", 2.0, trunc(2.0));
}

/* ------------------------------------------------------------------ */
/* Double remainder */
/* ------------------------------------------------------------------ */
static void test_fmod(void)
{
    printf("fmod %a %a = %a\n", 5.1, 3.0, fmod(5.1, 3.0));
    printf("fmod %a %a = %a\n", -5.1, 3.0, fmod(-5.1, 3.0));
}

static void test_remainder(void)
{
    printf("remainder %a %a = %a\n", 5.1, 3.0, remainder(5.1, 3.0));
    printf("remainder %a %a = %a\n", -5.1, 3.0, remainder(-5.1, 3.0));
}

static void test_remquo(void)
{
    int quo;
    double r = remquo(5.1, 3.0, &quo);
    printf("remquo %a %a = %a quo=%d\n", 5.1, 3.0, r, quo);
    r = remquo(-5.1, 3.0, &quo);
    printf("remquo %a %a = %a quo=%d\n", -5.1, 3.0, r, quo);
}

/* ------------------------------------------------------------------ */
/* Double manipulation */
/* ------------------------------------------------------------------ */
static void test_copysign(void)
{
    printf("copysign %a %a = %a\n", 1.0, -1.0, copysign(1.0, -1.0));
    printf("copysign %a %a = %a\n", -1.0, 1.0, copysign(-1.0, 1.0));
}

static void test_nan(void)
{
    double r = nan("");
    printf("nan isnan=%d\n", __fpclassifyd(r) == FP_NAN);
}

static void test_nextafter(void)
{
    printf("nextafter %a %a = %a\n", 1.0, 2.0, nextafter(1.0, 2.0));
    printf("nextafter %a %a = %a\n", 1.0, 0.0, nextafter(1.0, 0.0));
}

/* ------------------------------------------------------------------ */
/* Double max/min/fdim */
/* ------------------------------------------------------------------ */
static void test_fdim(void)
{
    printf("fdim %a %a = %a\n", 3.0, 2.0, fdim(3.0, 2.0));
    printf("fdim %a %a = %a\n", 2.0, 3.0, fdim(2.0, 3.0));
}

static void test_fmax(void)
{
    printf("fmax %a %a = %a\n", 3.0, 2.0, fmax(3.0, 2.0));
    printf("fmax %a %a = %a\n", -1.0, 1.0, fmax(-1.0, 1.0));
}

static void test_fmin(void)
{
    printf("fmin %a %a = %a\n", 3.0, 2.0, fmin(3.0, 2.0));
    printf("fmin %a %a = %a\n", -1.0, 1.0, fmin(-1.0, 1.0));
}

/* ------------------------------------------------------------------ */
/* Double fma */
/* ------------------------------------------------------------------ */
static void test_fma(void)
{
    printf("fma %a %a %a = %a\n", 2.0, 3.0, 1.0, fma(2.0, 3.0, 1.0));
    printf("fma %a %a %a = %a\n", 1.0, 1.0, -1.0, fma(1.0, 1.0, -1.0));
}

/* ------------------------------------------------------------------ */
/* Double Bessel */
/* ------------------------------------------------------------------ */
static void test_j0(void)
{
    printf("j0 %a = %a\n", 0.0, j0(0.0));
    printf("j0 %a = %a\n", 1.0, j0(1.0));
}

static void test_j1(void)
{
    printf("j1 %a = %a\n", 0.0, j1(0.0));
    printf("j1 %a = %a\n", 1.0, j1(1.0));
}

static void test_jn(void)
{
    printf("jn %d %a = %a\n", 0, 1.0, jn(0, 1.0));
    printf("jn %d %a = %a\n", 1, 1.0, jn(1, 1.0));
    printf("jn %d %a = %a\n", 2, 1.0, jn(2, 1.0));
}

static void test_y0(void)
{
    printf("y0 %a = %a\n", 1.0, y0(1.0));
    printf("y0 %a = %a\n", 2.0, y0(2.0));
}

static void test_y1(void)
{
    printf("y1 %a = %a\n", 1.0, y1(1.0));
    printf("y1 %a = %a\n", 2.0, y1(2.0));
}

static void test_yn(void)
{
    printf("yn %d %a = %a\n", 0, 1.0, yn(0, 1.0));
    printf("yn %d %a = %a\n", 1, 1.0, yn(1, 1.0));
    printf("yn %d %a = %a\n", 2, 1.0, yn(2, 1.0));
}

/* ------------------------------------------------------------------ */
/* Float trigonometric */
/* ------------------------------------------------------------------ */
static void test_acosf(void)
{
    printf("acosf %a = %a\n", 0.5f, acosf(0.5f));
    printf("acosf %a = %a\n", 1.0f, acosf(1.0f));
    printf("acosf %a = %a\n", 0.0f, acosf(0.0f));
}

static void test_asinf(void)
{
    printf("asinf %a = %a\n", 0.5f, asinf(0.5f));
    printf("asinf %a = %a\n", 1.0f, asinf(1.0f));
    printf("asinf %a = %a\n", 0.0f, asinf(0.0f));
}

static void test_atanf(void)
{
    printf("atanf %a = %a\n", 1.0f, atanf(1.0f));
    printf("atanf %a = %a\n", 0.0f, atanf(0.0f));
}

static void test_atan2f(void)
{
    printf("atan2f %a %a = %a\n", 1.0f, 1.0f, atan2f(1.0f, 1.0f));
    printf("atan2f %a %a = %a\n", 0.0f, 1.0f, atan2f(0.0f, 1.0f));
}

static void test_cosf(void)
{
    printf("cosf %a = %a\n", 0.0f, cosf(0.0f));
    printf("cosf %a = %a\n", 1.0f, cosf(1.0f));
}

static void test_sinf(void)
{
    printf("sinf %a = %a\n", 0.0f, sinf(0.0f));
    printf("sinf %a = %a\n", 1.0f, sinf(1.0f));
}

static void test_tanf(void)
{
    printf("tanf %a = %a\n", 0.0f, tanf(0.0f));
    printf("tanf %a = %a\n", 1.0f, tanf(1.0f));
}

/* ------------------------------------------------------------------ */
/* Float hyperbolic */
/* ------------------------------------------------------------------ */
static void test_acoshf(void)
{
    printf("acoshf %a = %a\n", 1.0f, acoshf(1.0f));
    printf("acoshf %a = %a\n", 2.0f, acoshf(2.0f));
}

static void test_asinhf(void)
{
    printf("asinhf %a = %a\n", 0.0f, asinhf(0.0f));
    printf("asinhf %a = %a\n", 1.0f, asinhf(1.0f));
}

static void test_atanhf(void)
{
    printf("atanhf %a = %a\n", 0.0f, atanhf(0.0f));
    printf("atanhf %a = %a\n", 0.5f, atanhf(0.5f));
}

static void test_coshf(void)
{
    printf("coshf %a = %a\n", 0.0f, coshf(0.0f));
    printf("coshf %a = %a\n", 1.0f, coshf(1.0f));
}

static void test_sinhf(void)
{
    printf("sinhf %a = %a\n", 0.0f, sinhf(0.0f));
    printf("sinhf %a = %a\n", 1.0f, sinhf(1.0f));
}

static void test_tanhf(void)
{
    printf("tanhf %a = %a\n", 0.0f, tanhf(0.0f));
    printf("tanhf %a = %a\n", 1.0f, tanhf(1.0f));
}

/* ------------------------------------------------------------------ */
/* Float exponential and logarithmic */
/* ------------------------------------------------------------------ */
static void test_expf(void)
{
    printf("expf %a = %a\n", 0.0f, expf(0.0f));
    printf("expf %a = %a\n", 1.0f, expf(1.0f));
}

static void test_exp2f(void)
{
    printf("exp2f %a = %a\n", 0.0f, exp2f(0.0f));
    printf("exp2f %a = %a\n", 3.0f, exp2f(3.0f));
}

static void test_expm1f(void)
{
    printf("expm1f %a = %a\n", 0.0f, expm1f(0.0f));
    printf("expm1f %a = %a\n", 1.0f, expm1f(1.0f));
}

static void test_frexpf(void)
{
    int exp_val;
    float r = frexpf(1.0f, &exp_val);
    printf("frexpf %a = %a exp=%d\n", 1.0f, r, exp_val);
    r = frexpf(0.0f, &exp_val);
    printf("frexpf %a = %a exp=%d\n", 0.0f, r, exp_val);
}

static void test_ilogbf(void)
{
    printf("ilogbf %a = %d\n", 1.0f, ilogbf(1.0f));
    printf("ilogbf %a = %d\n", 2.0f, ilogbf(2.0f));
}

static void test_ldexpf(void)
{
    printf("ldexpf %a %d = %a\n", 1.0f, 2, ldexpf(1.0f, 2));
    printf("ldexpf %a %d = %a\n", 0.5f, 3, ldexpf(0.5f, 3));
}

static void test_logf(void)
{
    printf("logf %a = %a\n", 1.0f, logf(1.0f));
    printf("logf %a = %a\n", 2.0f, logf(2.0f));
}

static void test_log10f(void)
{
    printf("log10f %a = %a\n", 1.0f, log10f(1.0f));
    printf("log10f %a = %a\n", 10.0f, log10f(10.0f));
}

static void test_log1pf(void)
{
    printf("log1pf %a = %a\n", 0.0f, log1pf(0.0f));
    printf("log1pf %a = %a\n", 1.0f, log1pf(1.0f));
}

static void test_log2f(void)
{
    printf("log2f %a = %a\n", 1.0f, log2f(1.0f));
    printf("log2f %a = %a\n", 8.0f, log2f(8.0f));
}

static void test_logbf(void)
{
    printf("logbf %a = %a\n", 1.0f, logbf(1.0f));
    printf("logbf %a = %a\n", 2.0f, logbf(2.0f));
}

static void test_modff(void)
{
    float int_part;
    float r = modff(3.75f, &int_part);
    printf("modff %a = %a int=%a\n", 3.75f, r, int_part);
    r = modff(-2.5f, &int_part);
    printf("modff %a = %a int=%a\n", -2.5f, r, int_part);
}

static void test_scalbnf(void)
{
    printf("scalbnf %a %d = %a\n", 1.0f, 2, scalbnf(1.0f, 2));
    printf("scalbnf %a %d = %a\n", 1.5f, -1, scalbnf(1.5f, -1));
}

static void test_scalblnf(void)
{
    printf("scalblnf %a %ld = %a\n", 1.0f, 2L, scalblnf(1.0f, 2L));
    printf("scalblnf %a %ld = %a\n", 1.5f, -1L, scalblnf(1.5f, -1L));
}

/* ------------------------------------------------------------------ */
/* Float power and absolute value */
/* ------------------------------------------------------------------ */
static void test_cbrtf(void)
{
    printf("cbrtf %a = %a\n", 8.0f, cbrtf(8.0f));
    printf("cbrtf %a = %a\n", -27.0f, cbrtf(-27.0f));
}

static void test_fabsf(void)
{
    printf("fabsf %a = %a\n", -1.5f, fabsf(-1.5f));
    printf("fabsf %a = %a\n", 1.5f, fabsf(1.5f));
}

static void test_hypotf(void)
{
    printf("hypotf %a %a = %a\n", 3.0f, 4.0f, hypotf(3.0f, 4.0f));
}

static void test_powf(void)
{
    printf("powf %a %a = %a\n", 2.0f, 10.0f, powf(2.0f, 10.0f));
    printf("powf %a %a = %a\n", 4.0f, 0.5f, powf(4.0f, 0.5f));
}

static void test_sqrtf(void)
{
    printf("sqrtf %a = %a\n", 4.0f, sqrtf(4.0f));
    printf("sqrtf %a = %a\n", 2.0f, sqrtf(2.0f));
}

/* ------------------------------------------------------------------ */
/* Float error and gamma */
/* ------------------------------------------------------------------ */
static void test_erff(void)
{
    printf("erff %a = %a\n", 0.0f, erff(0.0f));
    printf("erff %a = %a\n", 1.0f, erff(1.0f));
}

static void test_erfcf(void)
{
    printf("erfcf %a = %a\n", 0.0f, erfcf(0.0f));
    printf("erfcf %a = %a\n", 1.0f, erfcf(1.0f));
}

static void test_lgammaf(void)
{
    printf("lgammaf %a = %a\n", 1.0f, lgammaf(1.0f));
    printf("lgammaf %a = %a\n", 2.0f, lgammaf(2.0f));
}

static void test_tgammaf(void)
{
    printf("tgammaf %a = %a\n", 1.0f, tgammaf(1.0f));
    printf("tgammaf %a = %a\n", 2.0f, tgammaf(2.0f));
}

/* ------------------------------------------------------------------ */
/* Float nearest integer */
/* ------------------------------------------------------------------ */
static void test_ceilf(void)
{
    printf("ceilf %a = %a\n", 1.2f, ceilf(1.2f));
    printf("ceilf %a = %a\n", -1.2f, ceilf(-1.2f));
}

static void test_floorf(void)
{
    printf("floorf %a = %a\n", 1.7f, floorf(1.7f));
    printf("floorf %a = %a\n", -1.7f, floorf(-1.7f));
}

static void test_nearbyintf(void)
{
    printf("nearbyintf %a = %a\n", 1.5f, nearbyintf(1.5f));
    printf("nearbyintf %a = %a\n", -1.5f, nearbyintf(-1.5f));
}

static void test_rintf(void)
{
    printf("rintf %a = %a\n", 1.5f, rintf(1.5f));
    printf("rintf %a = %a\n", -1.5f, rintf(-1.5f));
}

static void test_lrintf(void)
{
    printf("lrintf %a = %ld\n", 1.5f, lrintf(1.5f));
    printf("lrintf %a = %ld\n", -1.5f, lrintf(-1.5f));
}

static void test_llrintf(void)
{
    printf("llrintf %a = %lld\n", 1.5f, llrintf(1.5f));
    printf("llrintf %a = %lld\n", -1.5f, llrintf(-1.5f));
}

static void test_roundf(void)
{
    printf("roundf %a = %a\n", 1.5f, roundf(1.5f));
    printf("roundf %a = %a\n", -1.5f, roundf(-1.5f));
}

static void test_lroundf(void)
{
    printf("lroundf %a = %ld\n", 1.5f, lroundf(1.5f));
    printf("lroundf %a = %ld\n", -1.5f, lroundf(-1.5f));
}

static void test_llroundf(void)
{
    printf("llroundf %a = %lld\n", 1.5f, llroundf(1.5f));
    printf("llroundf %a = %lld\n", -1.5f, llroundf(-1.5f));
}

static void test_truncf(void)
{
    printf("truncf %a = %a\n", 1.7f, truncf(1.7f));
    printf("truncf %a = %a\n", -1.7f, truncf(-1.7f));
}

/* ------------------------------------------------------------------ */
/* Float remainder */
/* ------------------------------------------------------------------ */
static void test_fmodf(void)
{
    printf("fmodf %a %a = %a\n", 5.1f, 3.0f, fmodf(5.1f, 3.0f));
    printf("fmodf %a %a = %a\n", -5.1f, 3.0f, fmodf(-5.1f, 3.0f));
}

static void test_remainderf(void)
{
    printf("remainderf %a %a = %a\n", 5.1f, 3.0f, remainderf(5.1f, 3.0f));
    printf("remainderf %a %a = %a\n", -5.1f, 3.0f, remainderf(-5.1f, 3.0f));
}

static void test_remquof(void)
{
    int quo;
    float r = remquof(5.1f, 3.0f, &quo);
    printf("remquof %a %a = %a quo=%d\n", 5.1f, 3.0f, r, quo);
}

/* ------------------------------------------------------------------ */
/* Float manipulation */
/* ------------------------------------------------------------------ */
static void test_copysignf(void)
{
    printf("copysignf %a %a = %a\n", 1.0f, -1.0f, copysignf(1.0f, -1.0f));
    printf("copysignf %a %a = %a\n", -1.0f, 1.0f, copysignf(-1.0f, 1.0f));
}

static void test_nanf(void)
{
    float r = nanf("");
    printf("nanf isnan=%d\n", __fpclassifyf(r) == FP_NAN);
}

static void test_nextafterf(void)
{
    printf("nextafterf %a %a = %a\n", 1.0f, 2.0f, nextafterf(1.0f, 2.0f));
    printf("nextafterf %a %a = %a\n", 1.0f, 0.0f, nextafterf(1.0f, 0.0f));
}

/* ------------------------------------------------------------------ */
/* Float max/min/fdim */
/* ------------------------------------------------------------------ */
static void test_fdimf(void)
{
    printf("fdimf %a %a = %a\n", 3.0f, 2.0f, fdimf(3.0f, 2.0f));
    printf("fdimf %a %a = %a\n", 2.0f, 3.0f, fdimf(2.0f, 3.0f));
}

static void test_fmaxf(void)
{
    printf("fmaxf %a %a = %a\n", 3.0f, 2.0f, fmaxf(3.0f, 2.0f));
    printf("fmaxf %a %a = %a\n", -1.0f, 1.0f, fmaxf(-1.0f, 1.0f));
}

static void test_fminf(void)
{
    printf("fminf %a %a = %a\n", 3.0f, 2.0f, fminf(3.0f, 2.0f));
    printf("fminf %a %a = %a\n", -1.0f, 1.0f, fminf(-1.0f, 1.0f));
}

/* ------------------------------------------------------------------ */
/* Float fma */
/* ------------------------------------------------------------------ */
static void test_fmaf(void)
{
    printf("fmaf %a %a %a = %a\n", 2.0f, 3.0f, 1.0f, fmaf(2.0f, 3.0f, 1.0f));
    printf("fmaf %a %a %a = %a\n", 1.0f, 1.0f, -1.0f, fmaf(1.0f, 1.0f, -1.0f));
}

/* ------------------------------------------------------------------ */
/* Classification and signbit */
/* ------------------------------------------------------------------ */
static void test_fpclassifyd(void)
{
    printf("__fpclassifyd normal = %d\n", __fpclassifyd(1.0));
    printf("__fpclassifyd zero = %d\n", __fpclassifyd(0.0));
    printf("__fpclassifyd inf = %d\n", __fpclassifyd(1.0 / 0.0));
}

static void test_fpclassifyf(void)
{
    printf("__fpclassifyf normal = %d\n", __fpclassifyf(1.0f));
    printf("__fpclassifyf zero = %d\n", __fpclassifyf(0.0f));
    printf("__fpclassifyf inf = %d\n", __fpclassifyf(1.0f / 0.0f));
}

static void test_signbitd(void)
{
    printf("__signbitd pos = %d\n", __signbitd(1.0));
    printf("__signbitd neg = %d\n", __signbitd(-1.0));
    printf("__signbitd zero = %d\n", __signbitd(0.0));
}

static void test_signbitf(void)
{
    printf("__signbitf pos = %d\n", __signbitf(1.0f));
    printf("__signbitf neg = %d\n", __signbitf(-1.0f));
    printf("__signbitf zero = %d\n", __signbitf(0.0f));
}

/* ------------------------------------------------------------------ */
/* Internal trig helpers (non-static) */
/* ------------------------------------------------------------------ */
static void test___cos(void)
{
    printf("__cos %a %a = %a\n", 1.0, 0.0, __cos(1.0, 0.0));
    printf("__cos %a %a = %a\n", 0.0, 0.0, __cos(0.0, 0.0));
}

static void test___sin(void)
{
    printf("__sin %a %a %d = %a\n", 1.0, 0.0, 0, __sin(1.0, 0.0, 0));
    printf("__sin %a %a %d = %a\n", 0.0, 0.0, 1, __sin(0.0, 0.0, 1));
}

static void test___cosf(void)
{
    printf("__cosf %a %a = %a\n", 1.0f, 0.0f, __cosf(1.0f, 0.0f));
    printf("__cosf %a %a = %a\n", 0.0f, 0.0f, __cosf(0.0f, 0.0f));
}

static void test___sinf(void)
{
    printf("__sinf %a %a %d = %a\n", 1.0f, 0.0f, 0, __sinf(1.0f, 0.0f, 0));
    printf("__sinf %a %a %d = %a\n", 0.0f, 0.0f, 1, __sinf(0.0f, 0.0f, 1));
}

static void test___rem_pio2(void)
{
    double y[2];
    int32_t n = __rem_pio2(1.0, y);
    printf("__rem_pio2 %a n=%d y0=%a\n", 1.0, n, y[0]);
    n = __rem_pio2(5.0, y);
    printf("__rem_pio2 %a n=%d y0=%a\n", 5.0, n, y[0]);
}

static void test___rem_pio2f(void)
{
    float y[2];
    int32_t n = __rem_pio2f(1.0f, y);
    printf("__rem_pio2f %a n=%d y0=%a\n", 1.0f, n, y[0]);
    n = __rem_pio2f(5.0f, y);
    printf("__rem_pio2f %a n=%d y0=%a\n", 5.0f, n, y[0]);
}

static void test___lgamma(void)
{
    int sgn;
    double r = __lgamma(2.0, &sgn);
    printf("__lgamma %a = %a sgn=%d\n", 2.0, r, sgn);
    r = __lgamma(0.5, &sgn);
    printf("__lgamma %a = %a sgn=%d\n", 0.5, r, sgn);
}

static void test___lgammaf(void)
{
    int sgn;
    float r = __lgammaf(2.0f, &sgn);
    printf("__lgammaf %a = %a sgn=%d\n", 2.0f, r, sgn);
    r = __lgammaf(0.5f, &sgn);
    printf("__lgammaf %a = %a sgn=%d\n", 0.5f, r, sgn);
}

static void test___redupi(void)
{
    printf("__redupi %a = %a\n", 1.0, __redupi(1.0));
    printf("__redupi %a = %a\n", 4.0, __redupi(4.0));
}

static void test___redupif(void)
{
    printf("__redupif %a = %a\n", 1.0f, __redupif(1.0f));
    printf("__redupif %a = %a\n", 4.0f, __redupif(4.0f));
}

static void test___ccoshsinh(void)
{
    double c, s;
    __ccoshsinh(1.0, &c, &s);
    printf("__ccoshsinh %a c=%a s=%a\n", 1.0, c, s);
    __ccoshsinh(0.0, &c, &s);
    printf("__ccoshsinh %a c=%a s=%a\n", 0.0, c, s);
}

static void test___ccoshsinhf(void)
{
    float c, s;
    __ccoshsinhf(1.0f, &c, &s);
    printf("__ccoshsinhf %a c=%a s=%a\n", 1.0f, c, s);
    __ccoshsinhf(0.0f, &c, &s);
    printf("__ccoshsinhf %a c=%a s=%a\n", 0.0f, c, s);
}

/* ------------------------------------------------------------------ */
/* Static internal (via bridge) */
/* ------------------------------------------------------------------ */
static void test_bridge___rem_pio2_internal(void)
{
    double x = 1.0;
    double y[2];
    int n = bridge___rem_pio2_internal(&x, y, 0, 1);
    printf("bridge___rem_pio2_internal n=%d y0=%a\n", n, y[0]);
}

static void test_bridge___rem_pio2f_internal(void)
{
    float x = 1.0f;
    float y[2];
    int n = bridge___rem_pio2f_internal(&x, y, 0, 1);
    printf("bridge___rem_pio2f_internal n=%d y0=%a\n", n, y[0]);
}

static void test_bridge___tan(void)
{
    double r = bridge___tan(1.0, 0.0, 1);
    printf("bridge___tan %a %a %d = %a\n", 1.0, 0.0, 1, r);
    r = bridge___tan(0.0, 0.0, 0);
    printf("bridge___tan %a %a %d = %a\n", 0.0, 0.0, 0, r);
}

static void test_bridge___tanf(void)
{
    float r = bridge___tanf(1.0f, 0.0f, 1);
    printf("bridge___tanf %a %a %d = %a\n", 1.0f, 0.0f, 1, r);
    r = bridge___tanf(0.0f, 0.0f, 0);
    printf("bridge___tanf %a %a %d = %a\n", 0.0f, 0.0f, 0, r);
}

static void test_bridge___sin_pi(void)
{
    double r = bridge___sin_pi(0.5);
    printf("bridge___sin_pi %a = %a\n", 0.5, r);
    r = bridge___sin_pi(1.0);
    printf("bridge___sin_pi %a = %a\n", 1.0, r);
}

static void test_bridge___sin_pif(void)
{
    float r = bridge___sin_pif(0.5f);
    printf("bridge___sin_pif %a = %a\n", 0.5f, r);
    r = bridge___sin_pif(1.0f);
    printf("bridge___sin_pif %a = %a\n", 1.0f, r);
}

static void test_bridge___ctans(void)
{
    double _Complex z = CMPLX(1.0, 1.0);
    double r = bridge___ctans(z);
    printf("bridge___ctans %a+%ai = %a\n", creal(z), cimag(z), r);
}

static void test_bridge___ctansf(void)
{
    float _Complex z = CMPLXF(1.0f, 1.0f);
    float r = bridge___ctansf(z);
    printf("bridge___ctansf %a+%ai = %a\n", crealf(z), cimagf(z), r);
}

/* ------------------------------------------------------------------ */
/* Complex double */
/* ------------------------------------------------------------------ */
static void test_cabs(void)
{
    double _Complex z = CMPLX(3.0, 4.0);
    printf("cabs %a+%ai = %a\n", creal(z), cimag(z), cabs(z));
    z = CMPLX(1.0, 0.0);
    printf("cabs %a+%ai = %a\n", creal(z), cimag(z), cabs(z));
}

static void test_carg(void)
{
    double _Complex z = CMPLX(1.0, 1.0);
    printf("carg %a+%ai = %a\n", creal(z), cimag(z), carg(z));
    z = CMPLX(1.0, 0.0);
    printf("carg %a+%ai = %a\n", creal(z), cimag(z), carg(z));
}

static void test_cimag(void)
{
    double _Complex z = CMPLX(3.0, 4.0);
    printf("cimag %a+%ai = %a\n", creal(z), cimag(z), cimag(z));
}

static void test_creal(void)
{
    double _Complex z = CMPLX(3.0, 4.0);
    printf("creal %a+%ai = %a\n", creal(z), cimag(z), creal(z));
}

static void test_conj(void)
{
    double _Complex z = CMPLX(3.0, 4.0);
    double _Complex r = conj(z);
    printf("conj %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_cproj(void)
{
    double _Complex z = CMPLX(1.0, 2.0);
    double _Complex r = cproj(z);
    printf("cproj %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_cacos(void)
{
    double _Complex z = CMPLX(0.5, 0.0);
    double _Complex r = cacos(z);
    printf("cacos %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_casin(void)
{
    double _Complex z = CMPLX(0.5, 0.0);
    double _Complex r = casin(z);
    printf("casin %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_catan(void)
{
    double _Complex z = CMPLX(1.0, 0.5);
    double _Complex r = catan(z);
    printf("catan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_ccos(void)
{
    double _Complex z = CMPLX(1.0, 1.0);
    double _Complex r = ccos(z);
    printf("ccos %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_csin(void)
{
    double _Complex z = CMPLX(1.0, 1.0);
    double _Complex r = csin(z);
    printf("csin %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_ctan(void)
{
    double _Complex z = CMPLX(1.0, 1.0);
    double _Complex r = ctan(z);
    printf("ctan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_cacosh(void)
{
    double _Complex z = CMPLX(2.0, 0.0);
    double _Complex r = cacosh(z);
    printf("cacosh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_casinh(void)
{
    double _Complex z = CMPLX(1.0, 0.5);
    double _Complex r = casinh(z);
    printf("casinh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_catanh(void)
{
    double _Complex z = CMPLX(0.5, 0.5);
    double _Complex r = catanh(z);
    printf("catanh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_ccosh(void)
{
    double _Complex z = CMPLX(1.0, 1.0);
    double _Complex r = ccosh(z);
    printf("ccosh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_csinh(void)
{
    double _Complex z = CMPLX(1.0, 1.0);
    double _Complex r = csinh(z);
    printf("csinh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_ctanh(void)
{
    double _Complex z = CMPLX(1.0, 1.0);
    double _Complex r = ctanh(z);
    printf("ctanh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_cexp(void)
{
    double _Complex z = CMPLX(1.0, 1.0);
    double _Complex r = cexp(z);
    printf("cexp %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_clog(void)
{
    double _Complex z = CMPLX(1.0, 1.0);
    double _Complex r = clog(z);
    printf("clog %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_cpow(void)
{
    double _Complex z = CMPLX(1.0, 1.0);
    double _Complex w = CMPLX(2.0, 0.0);
    double _Complex r = cpow(z, w);
    printf("cpow %a+%ai ^ %a+%ai = %a+%ai\n",
           creal(z), cimag(z), creal(w), cimag(w), creal(r), cimag(r));
}

static void test_csqrt(void)
{
    double _Complex z = CMPLX(3.0, 4.0);
    double _Complex r = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
    z = CMPLX(4.0, 0.0);
    r = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test___ccoshsinh_d(void)
{
    /* exercised via test___ccoshsinh */
}

/* ------------------------------------------------------------------ */
/* Complex float */
/* ------------------------------------------------------------------ */
static void test_cabsf(void)
{
    float _Complex z = CMPLXF(3.0f, 4.0f);
    printf("cabsf %a+%ai = %a\n", crealf(z), cimagf(z), cabsf(z));
}

static void test_cargf(void)
{
    float _Complex z = CMPLXF(1.0f, 1.0f);
    printf("cargf %a+%ai = %a\n", crealf(z), cimagf(z), cargf(z));
}

static void test_cimagf(void)
{
    float _Complex z = CMPLXF(3.0f, 4.0f);
    printf("cimagf %a+%ai = %a\n", crealf(z), cimagf(z), cimagf(z));
}

static void test_crealf(void)
{
    float _Complex z = CMPLXF(3.0f, 4.0f);
    printf("crealf %a+%ai = %a\n", crealf(z), cimagf(z), crealf(z));
}

static void test_conjf(void)
{
    float _Complex z = CMPLXF(3.0f, 4.0f);
    float _Complex r = conjf(z);
    printf("conjf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
}

static void test_cprojf(void)
{
    float _Complex z = CMPLXF(1.0f, 2.0f);
    float _Complex r = cprojf(z);
    printf("cprojf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
}

static void test_cacosf(void)
{
    float _Complex z = CMPLXF(0.5f, 0.0f);
    float _Complex r = cacosf(z);
    printf("cacosf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
}

static void test_casinf(void)
{
    float _Complex z = CMPLXF(0.5f, 0.0f);
    float _Complex r = casinf(z);
    printf("casinf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
}

static void test_catanf(void)
{
    float _Complex z = CMPLXF(1.0f, 0.5f);
    float _Complex r = catanf(z);
    printf("catanf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
}

static void test_ccosf(void)
{
    float _Complex z = CMPLXF(1.0f, 1.0f);
    float _Complex r = ccosf(z);
    printf("ccosf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
}

static void test_csinf(void)
{
    float _Complex z = CMPLXF(1.0f, 1.0f);
    float _Complex r = csinf(z);
    printf("csinf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
}

static void test_ctanf(void)
{
    float _Complex z = CMPLXF(1.0f, 1.0f);
    float _Complex r = ctanf(z);
    printf("ctanf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
}

static void test_cacoshf(void)
{
    float _Complex z = CMPLXF(2.0f, 0.0f);
    float _Complex r = cacoshf(z);
    printf("cacoshf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
}

static void test_casinhf(void)
{
    float _Complex z = CMPLXF(1.0f, 0.5f);
    float _Complex r = casinhf(z);
    printf("casinhf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
}

static void test_catanhf(void)
{
    float _Complex z = CMPLXF(0.5f, 0.5f);
    float _Complex r = catanhf(z);
    printf("catanhf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
}

static void test_ccoshf(void)
{
    float _Complex z = CMPLXF(1.0f, 1.0f);
    float _Complex r = ccoshf(z);
    printf("ccoshf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
}

static void test_csinhf(void)
{
    float _Complex z = CMPLXF(1.0f, 1.0f);
    float _Complex r = csinhf(z);
    printf("csinhf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
}

static void test_ctanhf(void)
{
    float _Complex z = CMPLXF(1.0f, 1.0f);
    float _Complex r = ctanhf(z);
    printf("ctanhf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
}

static void test_cexpf(void)
{
    float _Complex z = CMPLXF(1.0f, 1.0f);
    float _Complex r = cexpf(z);
    printf("cexpf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
}

static void test_clogf(void)
{
    float _Complex z = CMPLXF(1.0f, 1.0f);
    float _Complex r = clogf(z);
    printf("clogf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
}

static void test_cpowf(void)
{
    float _Complex z = CMPLXF(1.0f, 1.0f);
    float _Complex w = CMPLXF(2.0f, 0.0f);
    float _Complex r = cpowf(z, w);
    printf("cpowf %a+%ai ^ %a+%ai = %a+%ai\n",
           crealf(z), cimagf(z), crealf(w), cimagf(w), crealf(r), cimagf(r));
}

static void test_csqrtf(void)
{
    float _Complex z = CMPLXF(3.0f, 4.0f);
    float _Complex r = csqrtf(z);
    printf("csqrtf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
}

/* ------------------------------------------------------------------ */
/* main */
/* ------------------------------------------------------------------ */

/* ── Independent test execution wrapper ── */
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

static void run_test(const char *name, void (*fn)(void), int timeout_sec) {
    fflush(stdout);
    fflush(stderr);
    pid_t pid = fork();
    if (pid == 0) {
        /* Child: run the test, exit */
        fn();
        fflush(stdout);
        _exit(0);
    }
    /* Parent: wait with timeout using alarm */
    int status;
    /* First try non-blocking wait — most tests finish instantly */
    usleep(1000); /* 1ms grace period */
    pid_t r = waitpid(pid, &status, WNOHANG);
    if (r == pid) goto done;
    if (r < 0) goto done;
    /* Still running — poll with 100ms intervals up to timeout */
    int polls = timeout_sec * 10; /* 100ms per poll */
    for (int i = 0; i < polls; i++) {
        usleep(100000); /* 100ms */
        r = waitpid(pid, &status, WNOHANG);
        if (r == pid) goto done;
        if (r < 0) goto done;
    }
    /* Timeout — kill child */
    kill(pid, SIGKILL);
    waitpid(pid, &status, 0);
    printf("FAULT %s TIMEOUT\n", name);
    fflush(stdout);
    return;
done:
    if (WIFSIGNALED(status)) {
        printf("FAULT %s SIGNAL %d\n", name, WTERMSIG(status));
        fflush(stdout);
    } else if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
        printf("FAULT %s EXIT %d\n", name, WEXITSTATUS(status));
        fflush(stdout);
    }
}
/* ── End wrapper ── */

int main(void)
{
    /* Double trig */
    run_test("acos", test_acos, 2);
    run_test("asin", test_asin, 2);
    run_test("atan", test_atan, 2);
    run_test("atan2", test_atan2, 2);
    run_test("cos", test_cos, 2);
    run_test("sin", test_sin, 2);
    run_test("tan", test_tan, 2);

    /* Double hyperbolic */
    run_test("acosh", test_acosh, 2);
    run_test("asinh", test_asinh, 2);
    run_test("atanh", test_atanh, 2);
    run_test("cosh", test_cosh, 2);
    run_test("sinh", test_sinh, 2);
    run_test("tanh", test_tanh, 2);

    /* Double exp/log */
    run_test("exp", test_exp, 2);
    run_test("exp2", test_exp2, 2);
    run_test("expm1", test_expm1, 2);
    run_test("frexp", test_frexp, 2);
    run_test("ilogb", test_ilogb, 2);
    run_test("ldexp", test_ldexp, 2);
    run_test("log", test_log, 2);
    run_test("log10", test_log10, 2);
    run_test("log1p", test_log1p, 2);
    run_test("log2", test_log2, 2);
    run_test("logb", test_logb, 2);
    run_test("modf", test_modf, 2);
    run_test("scalbn", test_scalbn, 2);
    run_test("scalbln", test_scalbln, 2);

    /* Double power/abs */
    run_test("cbrt", test_cbrt, 2);
    run_test("fabs", test_fabs, 2);
    run_test("hypot", test_hypot, 2);
    run_test("pow", test_pow, 2);
    run_test("sqrt", test_sqrt, 2);

    /* Double error/gamma */
    run_test("erf", test_erf, 2);
    run_test("erfc", test_erfc, 2);
    run_test("lgamma", test_lgamma, 2);
    run_test("tgamma", test_tgamma, 2);

    /* Double nearest int */
    run_test("ceil", test_ceil, 2);
    run_test("floor", test_floor, 2);
    run_test("nearbyint", test_nearbyint, 2);
    run_test("rint", test_rint, 2);
    run_test("lrint", test_lrint, 2);
    run_test("llrint", test_llrint, 2);
    run_test("round", test_round, 2);
    run_test("lround", test_lround, 2);
    run_test("llround", test_llround, 2);
    run_test("trunc", test_trunc, 2);

    /* Double remainder */
    run_test("fmod", test_fmod, 2);
    run_test("remainder", test_remainder, 2);
    run_test("remquo", test_remquo, 2);

    /* Double manipulation */
    run_test("copysign", test_copysign, 2);
    run_test("nan", test_nan, 2);
    run_test("nextafter", test_nextafter, 2);

    /* Double max/min/fdim/fma */
    run_test("fdim", test_fdim, 2);
    run_test("fmax", test_fmax, 2);
    run_test("fmin", test_fmin, 2);
    run_test("fma", test_fma, 2);

    /* Double Bessel */
    run_test("j0", test_j0, 2);
    run_test("j1", test_j1, 2);
    run_test("jn", test_jn, 2);
    run_test("y0", test_y0, 2);
    run_test("y1", test_y1, 2);
    run_test("yn", test_yn, 2);

    /* Float trig */
    run_test("acosf", test_acosf, 2);
    run_test("asinf", test_asinf, 2);
    run_test("atanf", test_atanf, 2);
    run_test("atan2f", test_atan2f, 2);
    run_test("cosf", test_cosf, 2);
    run_test("sinf", test_sinf, 2);
    run_test("tanf", test_tanf, 2);

    /* Float hyperbolic */
    run_test("acoshf", test_acoshf, 2);
    run_test("asinhf", test_asinhf, 2);
    run_test("atanhf", test_atanhf, 2);
    run_test("coshf", test_coshf, 2);
    run_test("sinhf", test_sinhf, 2);
    run_test("tanhf", test_tanhf, 2);

    /* Float exp/log */
    run_test("expf", test_expf, 2);
    run_test("exp2f", test_exp2f, 2);
    run_test("expm1f", test_expm1f, 2);
    run_test("frexpf", test_frexpf, 2);
    run_test("ilogbf", test_ilogbf, 2);
    run_test("ldexpf", test_ldexpf, 2);
    run_test("logf", test_logf, 2);
    run_test("log10f", test_log10f, 2);
    run_test("log1pf", test_log1pf, 2);
    run_test("log2f", test_log2f, 2);
    run_test("logbf", test_logbf, 2);
    run_test("modff", test_modff, 2);
    run_test("scalbnf", test_scalbnf, 2);
    run_test("scalblnf", test_scalblnf, 2);

    /* Float power/abs */
    run_test("cbrtf", test_cbrtf, 2);
    run_test("fabsf", test_fabsf, 2);
    run_test("hypotf", test_hypotf, 2);
    run_test("powf", test_powf, 2);
    run_test("sqrtf", test_sqrtf, 2);

    /* Float error/gamma */
    run_test("erff", test_erff, 2);
    run_test("erfcf", test_erfcf, 2);
    run_test("lgammaf", test_lgammaf, 2);
    run_test("tgammaf", test_tgammaf, 2);

    /* Float nearest int */
    run_test("ceilf", test_ceilf, 2);
    run_test("floorf", test_floorf, 2);
    run_test("nearbyintf", test_nearbyintf, 2);
    run_test("rintf", test_rintf, 2);
    run_test("lrintf", test_lrintf, 2);
    run_test("llrintf", test_llrintf, 2);
    run_test("roundf", test_roundf, 2);
    run_test("lroundf", test_lroundf, 2);
    run_test("llroundf", test_llroundf, 2);
    run_test("truncf", test_truncf, 2);

    /* Float remainder */
    run_test("fmodf", test_fmodf, 2);
    run_test("remainderf", test_remainderf, 2);
    run_test("remquof", test_remquof, 2);

    /* Float manipulation */
    run_test("copysignf", test_copysignf, 2);
    run_test("nanf", test_nanf, 2);
    run_test("nextafterf", test_nextafterf, 2);

    /* Float max/min/fdim/fma */
    run_test("fdimf", test_fdimf, 2);
    run_test("fmaxf", test_fmaxf, 2);
    run_test("fminf", test_fminf, 2);
    run_test("fmaf", test_fmaf, 2);

    /* Classification / signbit */
    run_test("fpclassifyd", test_fpclassifyd, 2);
    run_test("fpclassifyf", test_fpclassifyf, 2);
    run_test("signbitd", test_signbitd, 2);
    run_test("signbitf", test_signbitf, 2);

    /* Internal non-static helpers */
    run_test("__cos", test___cos, 2);
    run_test("__sin", test___sin, 2);
    run_test("__cosf", test___cosf, 2);
    run_test("__sinf", test___sinf, 2);
    run_test("__rem_pio2", test___rem_pio2, 2);
    run_test("__rem_pio2f", test___rem_pio2f, 2);
    run_test("__lgamma", test___lgamma, 2);
    run_test("__lgammaf", test___lgammaf, 2);
    run_test("__redupi", test___redupi, 2);
    run_test("__redupif", test___redupif, 2);
    run_test("__ccoshsinh", test___ccoshsinh, 2);
    run_test("__ccoshsinhf", test___ccoshsinhf, 2);

    /* Bridge (static) helpers */
    run_test("bridge___rem_pio2_internal", test_bridge___rem_pio2_internal, 2);
    run_test("bridge___rem_pio2f_internal", test_bridge___rem_pio2f_internal, 2);
    run_test("bridge___tan", test_bridge___tan, 2);
    run_test("bridge___tanf", test_bridge___tanf, 2);
    run_test("bridge___sin_pi", test_bridge___sin_pi, 2);
    run_test("bridge___sin_pif", test_bridge___sin_pif, 2);
    run_test("bridge___ctans", test_bridge___ctans, 2);
    run_test("bridge___ctansf", test_bridge___ctansf, 2);

    /* Complex double */
    run_test("cabs", test_cabs, 2);
    run_test("carg", test_carg, 2);
    run_test("cimag", test_cimag, 2);
    run_test("creal", test_creal, 2);
    run_test("conj", test_conj, 2);
    run_test("cproj", test_cproj, 2);
    run_test("cacos", test_cacos, 2);
    run_test("casin", test_casin, 2);
    run_test("catan", test_catan, 2);
    run_test("ccos", test_ccos, 2);
    run_test("csin", test_csin, 2);
    run_test("ctan", test_ctan, 2);
    run_test("cacosh", test_cacosh, 2);
    run_test("casinh", test_casinh, 2);
    run_test("catanh", test_catanh, 2);
    run_test("ccosh", test_ccosh, 2);
    run_test("csinh", test_csinh, 2);
    run_test("ctanh", test_ctanh, 2);
    run_test("cexp", test_cexp, 2);
    run_test("clog", test_clog, 2);
    run_test("cpow", test_cpow, 2);
    run_test("csqrt", test_csqrt, 2);

    /* Complex float */
    run_test("cabsf", test_cabsf, 2);
    run_test("cargf", test_cargf, 2);
    run_test("cimagf", test_cimagf, 2);
    run_test("crealf", test_crealf, 2);
    run_test("conjf", test_conjf, 2);
    run_test("cprojf", test_cprojf, 2);
    run_test("cacosf", test_cacosf, 2);
    run_test("casinf", test_casinf, 2);
    run_test("catanf", test_catanf, 2);
    run_test("ccosf", test_ccosf, 2);
    run_test("csinf", test_csinf, 2);
    run_test("ctanf", test_ctanf, 2);
    run_test("cacoshf", test_cacoshf, 2);
    run_test("casinhf", test_casinhf, 2);
    run_test("catanhf", test_catanhf, 2);
    run_test("ccoshf", test_ccoshf, 2);
    run_test("csinhf", test_csinhf, 2);
    run_test("ctanhf", test_ctanhf, 2);
    run_test("cexpf", test_cexpf, 2);
    run_test("clogf", test_clogf, 2);
    run_test("cpowf", test_cpowf, 2);
    run_test("csqrtf", test_csqrtf, 2);

    return 0;
}
