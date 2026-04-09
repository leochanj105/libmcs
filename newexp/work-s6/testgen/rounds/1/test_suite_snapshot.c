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
/* Coverage-targeted: double special values                           */
/* ------------------------------------------------------------------ */
static void test_acos_cov(void)
{
    printf("acos NaN = %a\n", acos(nan("")));
    printf("acos 2.0 = %a\n", acos(2.0));
    printf("acos -2.0 = %a\n", acos(-2.0));
    printf("acos 1e-16 = %a\n", acos(1e-16));
    printf("acos -0.5 = %a\n", acos(-0.5));
    printf("acos 0.75 = %a\n", acos(0.75));
    printf("acos -0.75 = %a\n", acos(-0.75));
    printf("acos 0x1p-60 = %a\n", acos(0x1p-60));
}

static void test_asin_cov(void)
{
    printf("asin NaN = %a\n", asin(nan("")));
    printf("asin 2.0 = %a\n", asin(2.0));
    printf("asin -2.0 = %a\n", asin(-2.0));
    printf("asin 1e-30 = %a\n", asin(1e-30));
    printf("asin 0.0 = %a\n", asin(0.0));
    printf("asin 0x1p-27 = %a\n", asin(0x1p-27));
    printf("asin 0.99 = %a\n", asin(0.99));
    printf("asin -0.99 = %a\n", asin(-0.99));
    printf("asin 0.5 = %a\n", asin(0.5));
}

static void test_atan2_cov(void)
{
    /* y=0 cases */
    printf("atan2 0.0 -1.0 = %a\n", atan2(0.0, -1.0));
    printf("atan2 -0.0 -1.0 = %a\n", atan2(-0.0, -1.0));
    printf("atan2 -0.0 1.0 = %a\n", atan2(-0.0, 1.0));
    /* x=0 cases */
    printf("atan2 -1.0 0.0 = %a\n", atan2(-1.0, 0.0));
    /* x=1 shortcut */
    printf("atan2 2.0 1.0 = %a\n", atan2(2.0, 1.0));
    /* NaN */
    printf("atan2 nan 1.0 = %a\n", atan2(nan(""), 1.0));
    printf("atan2 1.0 nan = %a\n", atan2(1.0, nan("")));
    /* Inf combinations */
    printf("atan2 1.0 inf = %a\n", atan2(1.0, 1.0/0.0));
    printf("atan2 1.0 -inf = %a\n", atan2(1.0, -1.0/0.0));
    printf("atan2 -1.0 -inf = %a\n", atan2(-1.0, -1.0/0.0));
    printf("atan2 inf inf = %a\n", atan2(1.0/0.0, 1.0/0.0));
    printf("atan2 inf -inf = %a\n", atan2(1.0/0.0, -1.0/0.0));
    printf("atan2 -inf inf = %a\n", atan2(-1.0/0.0, 1.0/0.0));
    printf("atan2 -inf -inf = %a\n", atan2(-1.0/0.0, -1.0/0.0));
    printf("atan2 inf 1.0 = %a\n", atan2(1.0/0.0, 1.0));
    printf("atan2 -inf 1.0 = %a\n", atan2(-1.0/0.0, 1.0));
    printf("atan2 inf -1.0 = %a\n", atan2(1.0/0.0, -1.0));
    printf("atan2 -inf -1.0 = %a\n", atan2(-1.0/0.0, -1.0));
    /* |y|>>|x| and |y|<<|x| with x<0 */
    printf("atan2 1e200 1.0 = %a\n", atan2(1e200, 1.0));
    printf("atan2 1.0 -1e200 = %a\n", atan2(1.0, -1e200));
    /* negative quadrants */
    printf("atan2 1.0 -1.0 = %a\n", atan2(1.0, -1.0));
    printf("atan2 -1.0 -1.0 = %a\n", atan2(-1.0, -1.0));
    printf("atan2 -1.0 1.0 = %a\n", atan2(-1.0, 1.0));
}

static void test_acosh_cov(void)
{
    printf("acosh 0.5 = %a\n", acosh(0.5));
    printf("acosh -1.0 = %a\n", acosh(-1.0));
    printf("acosh nan = %a\n", acosh(nan("")));
    printf("acosh inf = %a\n", acosh(1.0/0.0));
    printf("acosh 1.5 = %a\n", acosh(1.5));
    printf("acosh 1e9 = %a\n", acosh(1e9));
}

static void test_asinh_cov(void)
{
    printf("asinh nan = %a\n", asinh(nan("")));
    printf("asinh inf = %a\n", asinh(1.0/0.0));
    printf("asinh -inf = %a\n", asinh(-1.0/0.0));
    printf("asinh 1e-30 = %a\n", asinh(1e-30));
    printf("asinh 2.0 = %a\n", asinh(2.0));
    printf("asinh 1e9 = %a\n", asinh(1e9));
    printf("asinh 0.5 = %a\n", asinh(0.5));
}

static void test_atanh_cov(void)
{
    printf("atanh nan = %a\n", atanh(nan("")));
    printf("atanh 1.0 = %a\n", atanh(1.0));
    printf("atanh -1.0 = %a\n", atanh(-1.0));
    printf("atanh 2.0 = %a\n", atanh(2.0));
    printf("atanh 1e-30 = %a\n", atanh(1e-30));
    printf("atanh 0.1 = %a\n", atanh(0.1));
}

static void test_cosh_cov(void)
{
    printf("cosh nan = %a\n", cosh(nan("")));
    printf("cosh inf = %a\n", cosh(1.0/0.0));
    printf("cosh -inf = %a\n", cosh(-1.0/0.0));
    printf("cosh 1e-55 = %a\n", cosh(1e-55));
    printf("cosh 0.3 = %a\n", cosh(0.3));
    printf("cosh 22.0 = %a\n", cosh(22.0));
    printf("cosh 100.0 = %a\n", cosh(100.0));
    printf("cosh 709.0 = %a\n", cosh(709.0));
    printf("cosh 710.0 = %a\n", cosh(710.0));
    printf("cosh -22.0 = %a\n", cosh(-22.0));
}

static void test_sinh_cov(void)
{
    printf("sinh nan = %a\n", sinh(nan("")));
    printf("sinh inf = %a\n", sinh(1.0/0.0));
    printf("sinh -inf = %a\n", sinh(-1.0/0.0));
    printf("sinh 1e-30 = %a\n", sinh(1e-30));
    printf("sinh 22.0 = %a\n", sinh(22.0));
    printf("sinh -22.0 = %a\n", sinh(-22.0));
    printf("sinh 100.0 = %a\n", sinh(100.0));
    printf("sinh 710.0 = %a\n", sinh(710.0));
    printf("sinh -0.5 = %a\n", sinh(-0.5));
    printf("sinh 0.5 = %a\n", sinh(0.5));
}

static void test_tanh_cov(void)
{
    printf("tanh nan = %a\n", tanh(nan("")));
    printf("tanh inf = %a\n", tanh(1.0/0.0));
    printf("tanh -inf = %a\n", tanh(-1.0/0.0));
    printf("tanh 1e-30 = %a\n", tanh(1e-30));
    printf("tanh 100.0 = %a\n", tanh(100.0));
    printf("tanh -100.0 = %a\n", tanh(-100.0));
    printf("tanh 0.3 = %a\n", tanh(0.3));
    printf("tanh -0.3 = %a\n", tanh(-0.3));
}

static void test_exp_cov(void)
{
    printf("exp nan = %a\n", exp(nan("")));
    printf("exp inf = %a\n", exp(1.0/0.0));
    printf("exp -inf = %a\n", exp(-1.0/0.0));
    printf("exp 710.0 = %a\n", exp(710.0));
    printf("exp -750.0 = %a\n", exp(-750.0));
    printf("exp 1e-35 = %a\n", exp(1e-35));
    printf("exp 0.3 = %a\n", exp(0.3));
    printf("exp -0.3 = %a\n", exp(-0.3));
    printf("exp 1.5 = %a\n", exp(1.5));
    printf("exp -1.5 = %a\n", exp(-1.5));
}

static void test_expm1_cov(void)
{
    printf("expm1 nan = %a\n", expm1(nan("")));
    printf("expm1 inf = %a\n", expm1(1.0/0.0));
    printf("expm1 -inf = %a\n", expm1(-1.0/0.0));
    printf("expm1 1e-35 = %a\n", expm1(1e-35));
    printf("expm1 0.3 = %a\n", expm1(0.3));
    printf("expm1 -0.3 = %a\n", expm1(-0.3));
    printf("expm1 40.0 = %a\n", expm1(40.0));
    printf("expm1 -40.0 = %a\n", expm1(-40.0));
    printf("expm1 710.0 = %a\n", expm1(710.0));
    printf("expm1 -750.0 = %a\n", expm1(-750.0));
    printf("expm1 1.5 = %a\n", expm1(1.5));
    printf("expm1 -1.5 = %a\n", expm1(-1.5));
}

static void test_frexp_cov(void)
{
    int e;
    printf("frexp nan = %a\n", frexp(nan(""), &e));
    printf("frexp inf = %a\n", frexp(1.0/0.0, &e));
    printf("frexp -inf = %a\n", frexp(-1.0/0.0, &e));
    printf("frexp 0x1p-1074 = %a exp=%d\n", frexp(0x1p-1074, &e), e);
    printf("frexp -1.5 = %a exp=%d\n", frexp(-1.5, &e), e);
}

static void test_ilogb_cov(void)
{
    printf("ilogb 0.0 = %d\n", ilogb(0.0));
    printf("ilogb nan = %d\n", ilogb(nan("")));
    printf("ilogb inf = %d\n", ilogb(1.0/0.0));
    printf("ilogb 0x1p-1074 = %d\n", ilogb(0x1p-1074));
    printf("ilogb 0x1p-1022 = %d\n", ilogb(0x1p-1022));
}

static void test_ldexp_cov(void)
{
    printf("ldexp 1.0 1000 = %a\n", ldexp(1.0, 1000));
    printf("ldexp 1.0 -1000 = %a\n", ldexp(1.0, -1000));
    printf("ldexp 0.0 5 = %a\n", ldexp(0.0, 5));
    printf("ldexp nan 2 = %a\n", ldexp(nan(""), 2));
    printf("ldexp inf 2 = %a\n", ldexp(1.0/0.0, 2));
}

static void test_log_cov(void)
{
    printf("log 0.0 = %a\n", log(0.0));
    printf("log -1.0 = %a\n", log(-1.0));
    printf("log nan = %a\n", log(nan("")));
    printf("log inf = %a\n", log(1.0/0.0));
    printf("log 0x1p-1074 = %a\n", log(0x1p-1074));
    printf("log 0x1p-1022 = %a\n", log(0x1p-1022));
    printf("log 0.5 = %a\n", log(0.5));
    printf("log 1.5 = %a\n", log(1.5));
}

static void test_log10_cov(void)
{
    printf("log10 0.0 = %a\n", log10(0.0));
    printf("log10 -1.0 = %a\n", log10(-1.0));
    printf("log10 nan = %a\n", log10(nan("")));
    printf("log10 inf = %a\n", log10(1.0/0.0));
    printf("log10 0x1p-1074 = %a\n", log10(0x1p-1074));
    printf("log10 0.5 = %a\n", log10(0.5));
}

static void test_log2_cov(void)
{
    printf("log2 0.0 = %a\n", log2(0.0));
    printf("log2 -1.0 = %a\n", log2(-1.0));
    printf("log2 nan = %a\n", log2(nan("")));
    printf("log2 inf = %a\n", log2(1.0/0.0));
    printf("log2 0x1p-1074 = %a\n", log2(0x1p-1074));
    printf("log2 0.5 = %a\n", log2(0.5));
    printf("log2 1.5 = %a\n", log2(1.5));
}

static void test_log1p_cov(void)
{
    printf("log1p -1.0 = %a\n", log1p(-1.0));
    printf("log1p -2.0 = %a\n", log1p(-2.0));
    printf("log1p nan = %a\n", log1p(nan("")));
    printf("log1p inf = %a\n", log1p(1.0/0.0));
    printf("log1p 1e-35 = %a\n", log1p(1e-35));
    printf("log1p -0.5 = %a\n", log1p(-0.5));
    printf("log1p 1.5 = %a\n", log1p(1.5));
    printf("log1p 0.1 = %a\n", log1p(0.1));
}

static void test_logb_cov(void)
{
    printf("logb 0.0 = %a\n", logb(0.0));
    printf("logb nan = %a\n", logb(nan("")));
    printf("logb inf = %a\n", logb(1.0/0.0));
    printf("logb 0x1p-1074 = %a\n", logb(0x1p-1074));
    printf("logb 0x1p-1022 = %a\n", logb(0x1p-1022));
    printf("logb -1.0 = %a\n", logb(-1.0));
}

static void test_cbrt_cov(void)
{
    printf("cbrt nan = %a\n", cbrt(nan("")));
    printf("cbrt inf = %a\n", cbrt(1.0/0.0));
    printf("cbrt -inf = %a\n", cbrt(-1.0/0.0));
    printf("cbrt 0x1p-1074 = %a\n", cbrt(0x1p-1074));
    printf("cbrt 1e300 = %a\n", cbrt(1e300));
    printf("cbrt -1e300 = %a\n", cbrt(-1e300));
}

static void test_hypot_cov(void)
{
    printf("hypot 0.0 0.0 = %a\n", hypot(0.0, 0.0));
    printf("hypot inf 1.0 = %a\n", hypot(1.0/0.0, 1.0));
    printf("hypot 1.0 inf = %a\n", hypot(1.0, 1.0/0.0));
    printf("hypot nan 1.0 = %a\n", hypot(nan(""), 1.0));
    printf("hypot 1.0 nan = %a\n", hypot(1.0, nan("")));
    printf("hypot 1e300 1e300 = %a\n", hypot(1e300, 1e300));
    printf("hypot 1e-300 1e-300 = %a\n", hypot(1e-300, 1e-300));
    printf("hypot 0x1p-1074 0x1p-1074 = %a\n", hypot(0x1p-1074, 0x1p-1074));
    printf("hypot 5.0 0.0 = %a\n", hypot(5.0, 0.0));
    printf("hypot 0.0 5.0 = %a\n", hypot(0.0, 5.0));
}

static void test_pow_cov(void)
{
    /* y=0 cases */
    printf("pow nan 0.0 = %a\n", pow(nan(""), 0.0));
    printf("pow 1.0 nan = %a\n", pow(1.0, nan("")));
    printf("pow nan nan = %a\n", pow(nan(""), nan("")));
    /* x=1 with NaN y */
    printf("pow 1.0 inf = %a\n", pow(1.0, 1.0/0.0));
    /* Inf exponent */
    printf("pow 2.0 inf = %a\n", pow(2.0, 1.0/0.0));
    printf("pow 0.5 inf = %a\n", pow(0.5, 1.0/0.0));
    printf("pow 2.0 -inf = %a\n", pow(2.0, -1.0/0.0));
    printf("pow 0.5 -inf = %a\n", pow(0.5, -1.0/0.0));
    /* special x */
    printf("pow 0.0 0.5 = %a\n", pow(0.0, 0.5));
    printf("pow 0.0 -1.0 = %a\n", pow(0.0, -1.0));
    printf("pow -0.0 -1.0 = %a\n", pow(-0.0, -1.0));
    printf("pow -0.0 -2.0 = %a\n", pow(-0.0, -2.0));
    printf("pow -0.0 3.0 = %a\n", pow(-0.0, 3.0));
    printf("pow inf 0.5 = %a\n", pow(1.0/0.0, 0.5));
    printf("pow inf -0.5 = %a\n", pow(1.0/0.0, -0.5));
    printf("pow -inf 3.0 = %a\n", pow(-1.0/0.0, 3.0));
    printf("pow -inf 2.0 = %a\n", pow(-1.0/0.0, 2.0));
    printf("pow -inf -3.0 = %a\n", pow(-1.0/0.0, -3.0));
    /* overflow/underflow */
    printf("pow 2.0 1000.0 = %a\n", pow(2.0, 1000.0));
    printf("pow 2.0 -1000.0 = %a\n", pow(2.0, -1000.0));
    /* negative base integer exponent */
    printf("pow -2.0 3.0 = %a\n", pow(-2.0, 3.0));
    printf("pow -2.0 2.0 = %a\n", pow(-2.0, 2.0));
    printf("pow -2.0 0.5 = %a\n", pow(-2.0, 0.5));
    /* y=+-1 */
    printf("pow 3.0 1.0 = %a\n", pow(3.0, 1.0));
    printf("pow 3.0 -1.0 = %a\n", pow(3.0, -1.0));
    /* y=2, y=0.5 */
    printf("pow 3.0 2.0 = %a\n", pow(3.0, 2.0));
    printf("pow 4.0 0.5 = %a\n", pow(4.0, 0.5));
}

static void test_sqrt_cov(void)
{
    printf("sqrt -1.0 = %a\n", sqrt(-1.0));
    printf("sqrt nan = %a\n", sqrt(nan("")));
    printf("sqrt -inf = %a\n", sqrt(-1.0/0.0));
    printf("sqrt inf = %a\n", sqrt(1.0/0.0));
    printf("sqrt -0.0 = %a\n", sqrt(-0.0));
    printf("sqrt 0x1p-1074 = %a\n", sqrt(0x1p-1074));
    printf("sqrt 0x1p-1022 = %a\n", sqrt(0x1p-1022));
    printf("sqrt 2.5 = %a\n", sqrt(2.5));
    printf("sqrt 1e300 = %a\n", sqrt(1e300));
}

static void test_ceil_cov(void)
{
    printf("ceil nan = %a\n", ceil(nan("")));
    printf("ceil inf = %a\n", ceil(1.0/0.0));
    printf("ceil -inf = %a\n", ceil(-1.0/0.0));
    printf("ceil -0.0 = %a\n", ceil(-0.0));
    printf("ceil 0.5 = %a\n", ceil(0.5));
    printf("ceil -0.5 = %a\n", ceil(-0.5));
    printf("ceil 0.9 = %a\n", ceil(0.9));
    printf("ceil -0.9 = %a\n", ceil(-0.9));
    printf("ceil 2097152.5 = %a\n", ceil(2097152.5));  /* 2^21 + 0.5 */
    printf("ceil -2097152.5 = %a\n", ceil(-2097152.5));
    printf("ceil 2097152.0 = %a\n", ceil(2097152.0));  /* already integer */
    printf("ceil -2097152.0 = %a\n", ceil(-2097152.0));
    printf("ceil 4503599627370496.5 = %a\n", ceil(4503599627370496.5)); /* near 2^52 */
    printf("ceil -4503599627370496.5 = %a\n", ceil(-4503599627370496.5));
    printf("ceil 1e20 = %a\n", ceil(1e20));
}

static void test_floor_cov(void)
{
    printf("floor nan = %a\n", floor(nan("")));
    printf("floor inf = %a\n", floor(1.0/0.0));
    printf("floor -inf = %a\n", floor(-1.0/0.0));
    printf("floor -0.0 = %a\n", floor(-0.0));
    printf("floor 0.5 = %a\n", floor(0.5));
    printf("floor -0.5 = %a\n", floor(-0.5));
    printf("floor 0.9 = %a\n", floor(0.9));
    printf("floor -0.9 = %a\n", floor(-0.9));
    printf("floor 2097152.5 = %a\n", floor(2097152.5));
    printf("floor -2097152.5 = %a\n", floor(-2097152.5));
    printf("floor 2097152.0 = %a\n", floor(2097152.0));
    printf("floor -2097152.0 = %a\n", floor(-2097152.0));
    printf("floor 4503599627370496.5 = %a\n", floor(4503599627370496.5));
    printf("floor -4503599627370496.5 = %a\n", floor(-4503599627370496.5));
    printf("floor 1e20 = %a\n", floor(1e20));
}

static void test_trunc_cov(void)
{
    printf("trunc nan = %a\n", trunc(nan("")));
    printf("trunc inf = %a\n", trunc(1.0/0.0));
    printf("trunc -0.0 = %a\n", trunc(-0.0));
    printf("trunc 0.5 = %a\n", trunc(0.5));
    printf("trunc -0.5 = %a\n", trunc(-0.5));
    printf("trunc 2097152.5 = %a\n", trunc(2097152.5));
    printf("trunc 1e20 = %a\n", trunc(1e20));
}

static void test_round_cov(void)
{
    printf("round nan = %a\n", round(nan("")));
    printf("round inf = %a\n", round(1.0/0.0));
    printf("round -0.0 = %a\n", round(-0.0));
    printf("round 0.5 = %a\n", round(0.5));
    printf("round -0.5 = %a\n", round(-0.5));
    printf("round 0.4 = %a\n", round(0.4));
    printf("round -0.4 = %a\n", round(-0.4));
    printf("round 2097152.5 = %a\n", round(2097152.5));
    printf("round -2097152.5 = %a\n", round(-2097152.5));
    printf("round 1e20 = %a\n", round(1e20));
}

static void test_rint_cov(void)
{
    printf("rint nan = %a\n", rint(nan("")));
    printf("rint inf = %a\n", rint(1.0/0.0));
    printf("rint -0.0 = %a\n", rint(-0.0));
    printf("rint 0.5 = %a\n", rint(0.5));
    printf("rint -0.5 = %a\n", rint(-0.5));
    printf("rint 0.4 = %a\n", rint(0.4));
    printf("rint 2097152.5 = %a\n", rint(2097152.5));
    printf("rint -2097152.5 = %a\n", rint(-2097152.5));
    printf("rint 1e20 = %a\n", rint(1e20));
    printf("rint 0x1p-1074 = %a\n", rint(0x1p-1074));
}

static void test_lrint_cov(void)
{
    printf("lrint 0.4 = %ld\n", lrint(0.4));
    printf("lrint -0.4 = %ld\n", lrint(-0.4));
    printf("lrint 0.6 = %ld\n", lrint(0.6));
    printf("lrint 1.5 = %ld\n", lrint(1.5));
    printf("lrint 1e18 = %ld\n", lrint(1e18));
    printf("lrint -1e18 = %ld\n", lrint(-1e18));
}

static void test_llrint_cov(void)
{
    printf("llrint 0.4 = %lld\n", llrint(0.4));
    printf("llrint -0.4 = %lld\n", llrint(-0.4));
    printf("llrint 0.6 = %lld\n", llrint(0.6));
    printf("llrint 1.5 = %lld\n", llrint(1.5));
    printf("llrint 1e18 = %lld\n", llrint(1e18));
}

static void test_lround_cov(void)
{
    printf("lround 0.4 = %ld\n", lround(0.4));
    printf("lround -0.4 = %ld\n", lround(-0.4));
    printf("lround 0.5 = %ld\n", lround(0.5));
    printf("lround -0.5 = %ld\n", lround(-0.5));
    printf("lround 1e18 = %ld\n", lround(1e18));
    printf("lround -1e18 = %ld\n", lround(-1e18));
}

static void test_llround_cov(void)
{
    printf("llround 0.4 = %lld\n", llround(0.4));
    printf("llround -0.4 = %lld\n", llround(-0.4));
    printf("llround 0.5 = %lld\n", llround(0.5));
    printf("llround -0.5 = %lld\n", llround(-0.5));
    printf("llround 1e18 = %lld\n", llround(1e18));
}

static void test_modf_cov(void)
{
    double ip;
    printf("modf nan = %a\n", modf(nan(""), &ip));
    printf("modf inf = %a int=%a\n", modf(1.0/0.0, &ip), ip);
    printf("modf -inf = %a int=%a\n", modf(-1.0/0.0, &ip), ip);
    printf("modf 1e20 = %a int=%a\n", modf(1e20, &ip), ip);
    printf("modf 0x1p-1074 = %a int=%a\n", modf(0x1p-1074, &ip), ip);
    printf("modf -3.75 = %a int=%a\n", modf(-3.75, &ip), ip);
}

static void test_fmod_cov(void)
{
    printf("fmod inf 2.0 = %a\n", fmod(1.0/0.0, 2.0));
    printf("fmod nan 2.0 = %a\n", fmod(nan(""), 2.0));
    printf("fmod 2.0 nan = %a\n", fmod(2.0, nan("")));
    printf("fmod 2.0 0.0 = %a\n", fmod(2.0, 0.0));
    printf("fmod 1.0 2.0 = %a\n", fmod(1.0, 2.0));
    printf("fmod 2.0 2.0 = %a\n", fmod(2.0, 2.0));
    printf("fmod -2.0 2.0 = %a\n", fmod(-2.0, 2.0));
    printf("fmod 0x1p-1074 2.0 = %a\n", fmod(0x1p-1074, 2.0));
    printf("fmod 2.0 0x1p-1074 = %a\n", fmod(2.0, 0x1p-1074));
    printf("fmod 5.0 0x1p-1074 = %a\n", fmod(5.0, 0x1p-1074));
    printf("fmod 1e200 1e-200 = %a\n", fmod(1e200, 1e-200));
    printf("fmod -0.0 1.0 = %a\n", fmod(-0.0, 1.0));
}

static void test_remainder_cov(void)
{
    printf("remainder inf 2.0 = %a\n", remainder(1.0/0.0, 2.0));
    printf("remainder nan 2.0 = %a\n", remainder(nan(""), 2.0));
    printf("remainder 2.0 0.0 = %a\n", remainder(2.0, 0.0));
    printf("remainder 1.0 2.0 = %a\n", remainder(1.0, 2.0));
    printf("remainder 2.0 2.0 = %a\n", remainder(2.0, 2.0));
    printf("remainder 0x1p-1074 2.0 = %a\n", remainder(0x1p-1074, 2.0));
    printf("remainder 2.0 0x1p-1074 = %a\n", remainder(2.0, 0x1p-1074));
}

static void test_remquo_cov(void)
{
    int quo;
    printf("remquo inf 2.0 = %a\n", remquo(1.0/0.0, 2.0, &quo));
    printf("remquo nan 2.0 = %a\n", remquo(nan(""), 2.0, &quo));
    printf("remquo 2.0 0.0 = %a\n", remquo(2.0, 0.0, &quo));
    printf("remquo 1.0 2.0 = %a quo=%d\n", remquo(1.0, 2.0, &quo), quo);
    printf("remquo 0x1p-1074 2.0 = %a\n", remquo(0x1p-1074, 2.0, &quo));
}

static void test_nextafter_cov(void)
{
    printf("nextafter 0.0 1.0 = %a\n", nextafter(0.0, 1.0));
    printf("nextafter -0.0 1.0 = %a\n", nextafter(-0.0, 1.0));
    printf("nextafter 0.0 -1.0 = %a\n", nextafter(0.0, -1.0));
    printf("nextafter -0.0 -1.0 = %a\n", nextafter(-0.0, -1.0));
    printf("nextafter 1.0 1.0 = %a\n", nextafter(1.0, 1.0));
    printf("nextafter nan 1.0 = %a\n", nextafter(nan(""), 1.0));
    printf("nextafter 1.0 nan = %a\n", nextafter(1.0, nan("")));
    printf("nextafter inf 0.0 = %a\n", nextafter(1.0/0.0, 0.0));
    printf("nextafter -inf 0.0 = %a\n", nextafter(-1.0/0.0, 0.0));
    printf("nextafter 1.0 0.0 = %a\n", nextafter(1.0, 0.0));
    printf("nextafter -1.0 0.0 = %a\n", nextafter(-1.0, 0.0));
    printf("nextafter 0x1p-1074 0.0 = %a\n", nextafter(0x1p-1074, 0.0));
    printf("nextafter 0x1p-1074 1.0 = %a\n", nextafter(0x1p-1074, 1.0));
}

static void test_scalbn_cov(void)
{
    printf("scalbn 1.0 1023 = %a\n", scalbn(1.0, 1023));
    printf("scalbn 1.0 -1074 = %a\n", scalbn(1.0, -1074));
    printf("scalbn 1.0 -2000 = %a\n", scalbn(1.0, -2000));
    printf("scalbn 1.0 2000 = %a\n", scalbn(1.0, 2000));
    printf("scalbn nan 2 = %a\n", scalbn(nan(""), 2));
    printf("scalbn inf 2 = %a\n", scalbn(1.0/0.0, 2));
    printf("scalbn 0x1p-1074 1 = %a\n", scalbn(0x1p-1074, 1));
}

static void test_scalbln_cov(void)
{
    printf("scalbln 1.0 1023L = %a\n", scalbln(1.0, 1023L));
    printf("scalbln 1.0 -1074L = %a\n", scalbln(1.0, -1074L));
    printf("scalbln 1.0 -2000L = %a\n", scalbln(1.0, -2000L));
    printf("scalbln 1.0 2000L = %a\n", scalbln(1.0, 2000L));
    printf("scalbln nan 2L = %a\n", scalbln(nan(""), 2L));
}

static void test_fmax_cov(void)
{
    printf("fmax nan 1.0 = %a\n", fmax(nan(""), 1.0));
    printf("fmax 1.0 nan = %a\n", fmax(1.0, nan("")));
    printf("fmax nan nan = %a\n", fmax(nan(""), nan("")));
    printf("fmax 1.0 1.0 = %a\n", fmax(1.0, 1.0));
    printf("fmax -0.0 0.0 = %a\n", fmax(-0.0, 0.0));
    printf("fmax 0.0 -0.0 = %a\n", fmax(0.0, -0.0));
}

static void test_fmin_cov(void)
{
    printf("fmin nan 1.0 = %a\n", fmin(nan(""), 1.0));
    printf("fmin 1.0 nan = %a\n", fmin(1.0, nan("")));
    printf("fmin nan nan = %a\n", fmin(nan(""), nan("")));
    printf("fmin 1.0 1.0 = %a\n", fmin(1.0, 1.0));
    printf("fmin -0.0 0.0 = %a\n", fmin(-0.0, 0.0));
    printf("fmin 0.0 -0.0 = %a\n", fmin(0.0, -0.0));
}

static void test_fdim_cov(void)
{
    printf("fdim nan 1.0 = %a\n", fdim(nan(""), 1.0));
    printf("fdim 1.0 nan = %a\n", fdim(1.0, nan("")));
    printf("fdim inf inf = %a\n", fdim(1.0/0.0, 1.0/0.0));
}

static void test_fabs_cov(void)
{
    printf("fabs nan = %a\n", fabs(nan("")));
    printf("fabs inf = %a\n", fabs(1.0/0.0));
    printf("fabs -inf = %a\n", fabs(-1.0/0.0));
    printf("fabs -0.0 = %a\n", fabs(-0.0));
    printf("fabs 0x1p-1074 = %a\n", fabs(0x1p-1074));
}

static void test_copysign_cov(void)
{
    printf("copysign nan -1.0 = %a\n", copysign(nan(""), -1.0));
    printf("copysign nan 1.0 = %a\n", copysign(nan(""), 1.0));
    printf("copysign inf -1.0 = %a\n", copysign(1.0/0.0, -1.0));
    printf("copysign 0.0 -1.0 = %a\n", copysign(0.0, -1.0));
    printf("copysign 0.0 0.0 = %a\n", copysign(0.0, 0.0));
}

static void test_erf_cov(void)
{
    printf("erf nan = %a\n", erf(nan("")));
    printf("erf inf = %a\n", erf(1.0/0.0));
    printf("erf -inf = %a\n", erf(-1.0/0.0));
    printf("erf 1e-35 = %a\n", erf(1e-35));
    printf("erf 10.0 = %a\n", erf(10.0));
    printf("erf -10.0 = %a\n", erf(-10.0));
    printf("erf 2.0 = %a\n", erf(2.0));
    printf("erf 4.0 = %a\n", erf(4.0));
    printf("erf 6.0 = %a\n", erf(6.0));
    printf("erf 0.5 = %a\n", erf(0.5));
    printf("erf -0.5 = %a\n", erf(-0.5));
}

static void test_erfc_cov(void)
{
    printf("erfc nan = %a\n", erfc(nan("")));
    printf("erfc inf = %a\n", erfc(1.0/0.0));
    printf("erfc -inf = %a\n", erfc(-1.0/0.0));
    printf("erfc 1e-35 = %a\n", erfc(1e-35));
    printf("erfc 10.0 = %a\n", erfc(10.0));
    printf("erfc -10.0 = %a\n", erfc(-10.0));
    printf("erfc 2.0 = %a\n", erfc(2.0));
    printf("erfc 4.0 = %a\n", erfc(4.0));
    printf("erfc 6.0 = %a\n", erfc(6.0));
    printf("erfc 28.0 = %a\n", erfc(28.0));
    printf("erfc -4.0 = %a\n", erfc(-4.0));
}

static void test_lgamma_cov(void)
{
    printf("lgamma 0.0 = %a\n", lgamma(0.0));
    printf("lgamma -1.0 = %a\n", lgamma(-1.0));
    printf("lgamma -2.0 = %a\n", lgamma(-2.0));
    printf("lgamma -0.5 = %a\n", lgamma(-0.5));
    printf("lgamma nan = %a\n", lgamma(nan("")));
    printf("lgamma inf = %a\n", lgamma(1.0/0.0));
    printf("lgamma -inf = %a\n", lgamma(-1.0/0.0));
    printf("lgamma 0.5 = %a\n", lgamma(0.5));
    printf("lgamma 10.0 = %a\n", lgamma(10.0));
    printf("lgamma -0.1 = %a\n", lgamma(-0.1));
}

static void test_tgamma_cov(void)
{
    printf("tgamma 0.0 = %a\n", tgamma(0.0));
    printf("tgamma -1.0 = %a\n", tgamma(-1.0));
    printf("tgamma -0.5 = %a\n", tgamma(-0.5));
    printf("tgamma nan = %a\n", tgamma(nan("")));
    printf("tgamma inf = %a\n", tgamma(1.0/0.0));
    printf("tgamma -inf = %a\n", tgamma(-1.0/0.0));
    printf("tgamma 0.5 = %a\n", tgamma(0.5));
    printf("tgamma 172.0 = %a\n", tgamma(172.0));
    printf("tgamma -0.1 = %a\n", tgamma(-0.1));
    printf("tgamma -10.5 = %a\n", tgamma(-10.5));
}

static void test_j0_cov(void)
{
    printf("j0 nan = %a\n", j0(nan("")));
    printf("j0 inf = %a\n", j0(1.0/0.0));
    printf("j0 -inf = %a\n", j0(-1.0/0.0));
    printf("j0 10.0 = %a\n", j0(10.0));
    printf("j0 100.0 = %a\n", j0(100.0));
    printf("j0 -5.0 = %a\n", j0(-5.0));
    printf("j0 2.0 = %a\n", j0(2.0));
}

static void test_j1_cov(void)
{
    printf("j1 nan = %a\n", j1(nan("")));
    printf("j1 inf = %a\n", j1(1.0/0.0));
    printf("j1 10.0 = %a\n", j1(10.0));
    printf("j1 100.0 = %a\n", j1(100.0));
    printf("j1 -5.0 = %a\n", j1(-5.0));
    printf("j1 2.0 = %a\n", j1(2.0));
}

static void test_jn_cov(void)
{
    printf("jn 2 nan = %a\n", jn(2, nan("")));
    printf("jn 2 inf = %a\n", jn(2, 1.0/0.0));
    printf("jn 2 10.0 = %a\n", jn(2, 10.0));
    printf("jn 10 5.0 = %a\n", jn(10, 5.0));
    printf("jn 2 -5.0 = %a\n", jn(2, -5.0));
    printf("jn 0 5.0 = %a\n", jn(0, 5.0));
    printf("jn 1 5.0 = %a\n", jn(1, 5.0));
}

static void test_y0_cov(void)
{
    printf("y0 0.0 = %a\n", y0(0.0));
    printf("y0 nan = %a\n", y0(nan("")));
    printf("y0 -1.0 = %a\n", y0(-1.0));
    printf("y0 inf = %a\n", y0(1.0/0.0));
    printf("y0 10.0 = %a\n", y0(10.0));
    printf("y0 100.0 = %a\n", y0(100.0));
    printf("y0 2.0 = %a\n", y0(2.0));
    printf("y0 0.5 = %a\n", y0(0.5));
}

static void test_y1_cov(void)
{
    printf("y1 0.0 = %a\n", y1(0.0));
    printf("y1 nan = %a\n", y1(nan("")));
    printf("y1 -1.0 = %a\n", y1(-1.0));
    printf("y1 inf = %a\n", y1(1.0/0.0));
    printf("y1 10.0 = %a\n", y1(10.0));
    printf("y1 100.0 = %a\n", y1(100.0));
    printf("y1 2.0 = %a\n", y1(2.0));
}

static void test_yn_cov(void)
{
    printf("yn 2 0.0 = %a\n", yn(2, 0.0));
    printf("yn 2 nan = %a\n", yn(2, nan("")));
    printf("yn 2 -1.0 = %a\n", yn(2, -1.0));
    printf("yn 2 inf = %a\n", yn(2, 1.0/0.0));
    printf("yn 2 10.0 = %a\n", yn(2, 10.0));
    printf("yn 0 2.0 = %a\n", yn(0, 2.0));
    printf("yn 1 2.0 = %a\n", yn(1, 2.0));
    printf("yn 10 5.0 = %a\n", yn(10, 5.0));
}

static void test_fpclassify_cov(void)
{
    printf("__fpclassifyd subnorm = %d\n", __fpclassifyd(0x1p-1074));
    printf("__fpclassifyd nan = %d\n", __fpclassifyd(nan("")));
    printf("__fpclassifyd -inf = %d\n", __fpclassifyd(-1.0/0.0));
    printf("__fpclassifyd -0.0 = %d\n", __fpclassifyd(-0.0));
    printf("__fpclassifyf subnorm = %d\n", __fpclassifyf(0x1p-149f));
    printf("__fpclassifyf nan = %d\n", __fpclassifyf(nanf("")));
    printf("__fpclassifyf -inf = %d\n", __fpclassifyf(-1.0f/0.0f));
}

static void test_sin_cov(void)
{
    printf("sin nan = %a\n", sin(nan("")));
    printf("sin inf = %a\n", sin(1.0/0.0));
    printf("sin -inf = %a\n", sin(-1.0/0.0));
    printf("sin 1e-35 = %a\n", sin(1e-35));
    printf("sin 3*pi/2 = %a\n", sin(3.0*M_PI_2));
    printf("sin 5*pi/2 = %a\n", sin(5.0*M_PI_2));
    printf("sin 1e9 = %a\n", sin(1e9));
    printf("sin -1.0 = %a\n", sin(-1.0));
}

static void test_cos_cov(void)
{
    printf("cos nan = %a\n", cos(nan("")));
    printf("cos inf = %a\n", cos(1.0/0.0));
    printf("cos -inf = %a\n", cos(-1.0/0.0));
    printf("cos 1e-35 = %a\n", cos(1e-35));
    printf("cos 3*pi/2 = %a\n", cos(3.0*M_PI_2));
    printf("cos 1e9 = %a\n", cos(1e9));
    printf("cos -1.0 = %a\n", cos(-1.0));
}

static void test_tan_cov(void)
{
    printf("tan nan = %a\n", tan(nan("")));
    printf("tan inf = %a\n", tan(1.0/0.0));
    printf("tan 1e-35 = %a\n", tan(1e-35));
    printf("tan 3*pi/4 = %a\n", tan(3.0*M_PI/4.0));
    printf("tan -3*pi/4 = %a\n", tan(-3.0*M_PI/4.0));
    printf("tan 1e9 = %a\n", tan(1e9));
}

/* ------------------------------------------------------------------ */
/* Coverage-targeted: float special values                            */
/* ------------------------------------------------------------------ */
static void test_acosf_cov(void)
{
    printf("acosf nanf = %a\n", acosf(nanf("")));
    printf("acosf 2.0f = %a\n", acosf(2.0f));
    printf("acosf -2.0f = %a\n", acosf(-2.0f));
    printf("acosf 0.75f = %a\n", acosf(0.75f));
    printf("acosf -0.75f = %a\n", acosf(-0.75f));
    printf("acosf 1e-16f = %a\n", acosf(1e-16f));
}

static void test_asinf_cov(void)
{
    printf("asinf nanf = %a\n", asinf(nanf("")));
    printf("asinf 2.0f = %a\n", asinf(2.0f));
    printf("asinf 0.99f = %a\n", asinf(0.99f));
    printf("asinf -0.99f = %a\n", asinf(-0.99f));
    printf("asinf 0x1p-27f = %a\n", asinf(0x1p-27f));
}

static void test_atanf_cov(void)
{
    printf("atanf nanf = %a\n", atanf(nanf("")));
    printf("atanf inff = %a\n", atanf(1.0f/0.0f));
    printf("atanf -inff = %a\n", atanf(-1.0f/0.0f));
    printf("atanf 10.0f = %a\n", atanf(10.0f));
    printf("atanf -10.0f = %a\n", atanf(-10.0f));
    printf("atanf 0.5f = %a\n", atanf(0.5f));
}

static void test_atan2f_cov(void)
{
    printf("atan2f 0.0f -1.0f = %a\n", atan2f(0.0f, -1.0f));
    printf("atan2f -0.0f -1.0f = %a\n", atan2f(-0.0f, -1.0f));
    printf("atan2f -1.0f 0.0f = %a\n", atan2f(-1.0f, 0.0f));
    printf("atan2f nanf 1.0f = %a\n", atan2f(nanf(""), 1.0f));
    printf("atan2f 1.0f nanf = %a\n", atan2f(1.0f, nanf("")));
    printf("atan2f inff inff = %a\n", atan2f(1.0f/0.0f, 1.0f/0.0f));
    printf("atan2f inff -inff = %a\n", atan2f(1.0f/0.0f, -1.0f/0.0f));
    printf("atan2f -inff inff = %a\n", atan2f(-1.0f/0.0f, 1.0f/0.0f));
    printf("atan2f -inff -inff = %a\n", atan2f(-1.0f/0.0f, -1.0f/0.0f));
    printf("atan2f inff 1.0f = %a\n", atan2f(1.0f/0.0f, 1.0f));
    printf("atan2f inff -1.0f = %a\n", atan2f(1.0f/0.0f, -1.0f));
    printf("atan2f 1.0f inff = %a\n", atan2f(1.0f, 1.0f/0.0f));
    printf("atan2f 1.0f -inff = %a\n", atan2f(1.0f, -1.0f/0.0f));
    printf("atan2f 1e20f 1.0f = %a\n", atan2f(1e20f, 1.0f));
    printf("atan2f 1.0f -1e20f = %a\n", atan2f(1.0f, -1e20f));
    printf("atan2f 1.0f -1.0f = %a\n", atan2f(1.0f, -1.0f));
    printf("atan2f -1.0f -1.0f = %a\n", atan2f(-1.0f, -1.0f));
}

static void test_acoshf_cov(void)
{
    printf("acoshf 0.5f = %a\n", acoshf(0.5f));
    printf("acoshf nanf = %a\n", acoshf(nanf("")));
    printf("acoshf inff = %a\n", acoshf(1.0f/0.0f));
    printf("acoshf 1.5f = %a\n", acoshf(1.5f));
    printf("acoshf 1e9f = %a\n", acoshf(1e9f));
}

static void test_asinhf_cov(void)
{
    printf("asinhf nanf = %a\n", asinhf(nanf("")));
    printf("asinhf inff = %a\n", asinhf(1.0f/0.0f));
    printf("asinhf 1e-30f = %a\n", asinhf(1e-30f));
    printf("asinhf 2.0f = %a\n", asinhf(2.0f));
    printf("asinhf 1e9f = %a\n", asinhf(1e9f));
    printf("asinhf 0.5f = %a\n", asinhf(0.5f));
}

static void test_atanhf_cov(void)
{
    printf("atanhf nanf = %a\n", atanhf(nanf("")));
    printf("atanhf 1.0f = %a\n", atanhf(1.0f));
    printf("atanhf -1.0f = %a\n", atanhf(-1.0f));
    printf("atanhf 2.0f = %a\n", atanhf(2.0f));
    printf("atanhf 1e-30f = %a\n", atanhf(1e-30f));
    printf("atanhf 0.1f = %a\n", atanhf(0.1f));
}

static void test_coshf_cov(void)
{
    printf("coshf nanf = %a\n", coshf(nanf("")));
    printf("coshf inff = %a\n", coshf(1.0f/0.0f));
    printf("coshf 1e-30f = %a\n", coshf(1e-30f));
    printf("coshf 22.0f = %a\n", coshf(22.0f));
    printf("coshf 90.0f = %a\n", coshf(90.0f));
    printf("coshf -22.0f = %a\n", coshf(-22.0f));
    printf("coshf 0.3f = %a\n", coshf(0.3f));
}

static void test_sinhf_cov(void)
{
    printf("sinhf nanf = %a\n", sinhf(nanf("")));
    printf("sinhf inff = %a\n", sinhf(1.0f/0.0f));
    printf("sinhf 1e-30f = %a\n", sinhf(1e-30f));
    printf("sinhf 22.0f = %a\n", sinhf(22.0f));
    printf("sinhf 90.0f = %a\n", sinhf(90.0f));
    printf("sinhf -22.0f = %a\n", sinhf(-22.0f));
    printf("sinhf 0.5f = %a\n", sinhf(0.5f));
}

static void test_tanhf_cov(void)
{
    printf("tanhf nanf = %a\n", tanhf(nanf("")));
    printf("tanhf inff = %a\n", tanhf(1.0f/0.0f));
    printf("tanhf 1e-30f = %a\n", tanhf(1e-30f));
    printf("tanhf 100.0f = %a\n", tanhf(100.0f));
    printf("tanhf 0.3f = %a\n", tanhf(0.3f));
    printf("tanhf -0.3f = %a\n", tanhf(-0.3f));
}

static void test_expf_cov(void)
{
    printf("expf nanf = %a\n", expf(nanf("")));
    printf("expf inff = %a\n", expf(1.0f/0.0f));
    printf("expf -inff = %a\n", expf(-1.0f/0.0f));
    printf("expf 90.0f = %a\n", expf(90.0f));
    printf("expf -105.0f = %a\n", expf(-105.0f));
    printf("expf 0.3f = %a\n", expf(0.3f));
    printf("expf 1.5f = %a\n", expf(1.5f));
    printf("expf 1e-15f = %a\n", expf(1e-15f));
}

static void test_expm1f_cov(void)
{
    printf("expm1f nanf = %a\n", expm1f(nanf("")));
    printf("expm1f inff = %a\n", expm1f(1.0f/0.0f));
    printf("expm1f -inff = %a\n", expm1f(-1.0f/0.0f));
    printf("expm1f 1e-15f = %a\n", expm1f(1e-15f));
    printf("expm1f 0.3f = %a\n", expm1f(0.3f));
    printf("expm1f -0.3f = %a\n", expm1f(-0.3f));
    printf("expm1f 40.0f = %a\n", expm1f(40.0f));
    printf("expm1f -40.0f = %a\n", expm1f(-40.0f));
    printf("expm1f 90.0f = %a\n", expm1f(90.0f));
    printf("expm1f 1.5f = %a\n", expm1f(1.5f));
}

static void test_frexpf_cov(void)
{
    int e;
    printf("frexpf nanf = %a\n", frexpf(nanf(""), &e));
    printf("frexpf inff = %a\n", frexpf(1.0f/0.0f, &e));
    printf("frexpf 0x1p-149f = %a exp=%d\n", frexpf(0x1p-149f, &e), e);
    printf("frexpf -1.5f = %a exp=%d\n", frexpf(-1.5f, &e), e);
}

static void test_ilogbf_cov(void)
{
    printf("ilogbf 0.0f = %d\n", ilogbf(0.0f));
    printf("ilogbf nanf = %d\n", ilogbf(nanf("")));
    printf("ilogbf inff = %d\n", ilogbf(1.0f/0.0f));
    printf("ilogbf 0x1p-149f = %d\n", ilogbf(0x1p-149f));
}

static void test_logf_cov(void)
{
    printf("logf 0.0f = %a\n", logf(0.0f));
    printf("logf -1.0f = %a\n", logf(-1.0f));
    printf("logf nanf = %a\n", logf(nanf("")));
    printf("logf inff = %a\n", logf(1.0f/0.0f));
    printf("logf 0x1p-149f = %a\n", logf(0x1p-149f));
    printf("logf 0.5f = %a\n", logf(0.5f));
    printf("logf 1.5f = %a\n", logf(1.5f));
}

static void test_log10f_cov(void)
{
    printf("log10f 0.0f = %a\n", log10f(0.0f));
    printf("log10f -1.0f = %a\n", log10f(-1.0f));
    printf("log10f nanf = %a\n", log10f(nanf("")));
    printf("log10f 0x1p-149f = %a\n", log10f(0x1p-149f));
}

static void test_log2f_cov(void)
{
    printf("log2f 0.0f = %a\n", log2f(0.0f));
    printf("log2f -1.0f = %a\n", log2f(-1.0f));
    printf("log2f nanf = %a\n", log2f(nanf("")));
    printf("log2f 0x1p-149f = %a\n", log2f(0x1p-149f));
    printf("log2f 0.5f = %a\n", log2f(0.5f));
}

static void test_log1pf_cov(void)
{
    printf("log1pf -1.0f = %a\n", log1pf(-1.0f));
    printf("log1pf -2.0f = %a\n", log1pf(-2.0f));
    printf("log1pf nanf = %a\n", log1pf(nanf("")));
    printf("log1pf inff = %a\n", log1pf(1.0f/0.0f));
    printf("log1pf 1e-15f = %a\n", log1pf(1e-15f));
    printf("log1pf 0.1f = %a\n", log1pf(0.1f));
    printf("log1pf 1.5f = %a\n", log1pf(1.5f));
}

static void test_logbf_cov(void)
{
    printf("logbf 0.0f = %a\n", logbf(0.0f));
    printf("logbf nanf = %a\n", logbf(nanf("")));
    printf("logbf inff = %a\n", logbf(1.0f/0.0f));
    printf("logbf 0x1p-149f = %a\n", logbf(0x1p-149f));
}

static void test_cbrtf_cov(void)
{
    printf("cbrtf nanf = %a\n", cbrtf(nanf("")));
    printf("cbrtf inff = %a\n", cbrtf(1.0f/0.0f));
    printf("cbrtf 0x1p-149f = %a\n", cbrtf(0x1p-149f));
    printf("cbrtf 1e30f = %a\n", cbrtf(1e30f));
}

static void test_hypotf_cov(void)
{
    printf("hypotf 0.0f 0.0f = %a\n", hypotf(0.0f, 0.0f));
    printf("hypotf inff 1.0f = %a\n", hypotf(1.0f/0.0f, 1.0f));
    printf("hypotf nanf 1.0f = %a\n", hypotf(nanf(""), 1.0f));
    printf("hypotf 1e30f 1e30f = %a\n", hypotf(1e30f, 1e30f));
    printf("hypotf 0x1p-149f 0x1p-149f = %a\n", hypotf(0x1p-149f, 0x1p-149f));
    printf("hypotf 5.0f 0.0f = %a\n", hypotf(5.0f, 0.0f));
}

static void test_powf_cov(void)
{
    printf("powf nanf 0.0f = %a\n", powf(nanf(""), 0.0f));
    printf("powf 1.0f nanf = %a\n", powf(1.0f, nanf("")));
    printf("powf 2.0f inff = %a\n", powf(2.0f, 1.0f/0.0f));
    printf("powf 0.5f inff = %a\n", powf(0.5f, 1.0f/0.0f));
    printf("powf 0.0f 0.5f = %a\n", powf(0.0f, 0.5f));
    printf("powf 0.0f -1.0f = %a\n", powf(0.0f, -1.0f));
    printf("powf inff 0.5f = %a\n", powf(1.0f/0.0f, 0.5f));
    printf("powf -inff 3.0f = %a\n", powf(-1.0f/0.0f, 3.0f));
    printf("powf -inff 2.0f = %a\n", powf(-1.0f/0.0f, 2.0f));
    printf("powf 2.0f 200.0f = %a\n", powf(2.0f, 200.0f));
    printf("powf 2.0f -200.0f = %a\n", powf(2.0f, -200.0f));
    printf("powf -2.0f 3.0f = %a\n", powf(-2.0f, 3.0f));
    printf("powf -2.0f 2.0f = %a\n", powf(-2.0f, 2.0f));
    printf("powf -2.0f 0.5f = %a\n", powf(-2.0f, 0.5f));
}

static void test_sqrtf_cov(void)
{
    printf("sqrtf -1.0f = %a\n", sqrtf(-1.0f));
    printf("sqrtf nanf = %a\n", sqrtf(nanf("")));
    printf("sqrtf inff = %a\n", sqrtf(1.0f/0.0f));
    printf("sqrtf -0.0f = %a\n", sqrtf(-0.0f));
    printf("sqrtf 0x1p-149f = %a\n", sqrtf(0x1p-149f));
    printf("sqrtf 2.5f = %a\n", sqrtf(2.5f));
}

static void test_erff_cov(void)
{
    printf("erff nanf = %a\n", erff(nanf("")));
    printf("erff inff = %a\n", erff(1.0f/0.0f));
    printf("erff -inff = %a\n", erff(-1.0f/0.0f));
    printf("erff 1e-15f = %a\n", erff(1e-15f));
    printf("erff 10.0f = %a\n", erff(10.0f));
    printf("erff 2.0f = %a\n", erff(2.0f));
    printf("erff 4.0f = %a\n", erff(4.0f));
    printf("erff -2.0f = %a\n", erff(-2.0f));
}

static void test_erfcf_cov(void)
{
    printf("erfcf nanf = %a\n", erfcf(nanf("")));
    printf("erfcf inff = %a\n", erfcf(1.0f/0.0f));
    printf("erfcf -inff = %a\n", erfcf(-1.0f/0.0f));
    printf("erfcf 1e-15f = %a\n", erfcf(1e-15f));
    printf("erfcf 10.0f = %a\n", erfcf(10.0f));
    printf("erfcf 2.0f = %a\n", erfcf(2.0f));
    printf("erfcf 4.0f = %a\n", erfcf(4.0f));
    printf("erfcf -2.0f = %a\n", erfcf(-2.0f));
    printf("erfcf 28.0f = %a\n", erfcf(28.0f));
}

static void test_lgammaf_cov(void)
{
    printf("lgammaf 0.0f = %a\n", lgammaf(0.0f));
    printf("lgammaf -1.0f = %a\n", lgammaf(-1.0f));
    printf("lgammaf -0.5f = %a\n", lgammaf(-0.5f));
    printf("lgammaf nanf = %a\n", lgammaf(nanf("")));
    printf("lgammaf inff = %a\n", lgammaf(1.0f/0.0f));
    printf("lgammaf 10.0f = %a\n", lgammaf(10.0f));
}

static void test_tgammaf_cov(void)
{
    printf("tgammaf 0.0f = %a\n", tgammaf(0.0f));
    printf("tgammaf -1.0f = %a\n", tgammaf(-1.0f));
    printf("tgammaf -0.5f = %a\n", tgammaf(-0.5f));
    printf("tgammaf nanf = %a\n", tgammaf(nanf("")));
    printf("tgammaf inff = %a\n", tgammaf(1.0f/0.0f));
    printf("tgammaf 40.0f = %a\n", tgammaf(40.0f));
    printf("tgammaf -10.5f = %a\n", tgammaf(-10.5f));
}

static void test_ceilf_cov(void)
{
    printf("ceilf nanf = %a\n", ceilf(nanf("")));
    printf("ceilf inff = %a\n", ceilf(1.0f/0.0f));
    printf("ceilf -0.0f = %a\n", ceilf(-0.0f));
    printf("ceilf 0.5f = %a\n", ceilf(0.5f));
    printf("ceilf -0.5f = %a\n", ceilf(-0.5f));
    printf("ceilf 1.5f = %a\n", ceilf(1.5f));
    printf("ceilf -1.5f = %a\n", ceilf(-1.5f));
    printf("ceilf 8388608.5f = %a\n", ceilf(8388608.5f));  /* 2^23 + 0.5 */
    printf("ceilf -8388608.5f = %a\n", ceilf(-8388608.5f));
    printf("ceilf 1e10f = %a\n", ceilf(1e10f));
}

static void test_floorf_cov(void)
{
    printf("floorf nanf = %a\n", floorf(nanf("")));
    printf("floorf inff = %a\n", floorf(1.0f/0.0f));
    printf("floorf -0.0f = %a\n", floorf(-0.0f));
    printf("floorf 0.5f = %a\n", floorf(0.5f));
    printf("floorf -0.5f = %a\n", floorf(-0.5f));
    printf("floorf 1.5f = %a\n", floorf(1.5f));
    printf("floorf -1.5f = %a\n", floorf(-1.5f));
    printf("floorf 8388608.5f = %a\n", floorf(8388608.5f));
    printf("floorf -8388608.5f = %a\n", floorf(-8388608.5f));
    printf("floorf 1e10f = %a\n", floorf(1e10f));
}

static void test_truncf_cov(void)
{
    printf("truncf nanf = %a\n", truncf(nanf("")));
    printf("truncf inff = %a\n", truncf(1.0f/0.0f));
    printf("truncf -0.0f = %a\n", truncf(-0.0f));
    printf("truncf 0.5f = %a\n", truncf(0.5f));
    printf("truncf -0.5f = %a\n", truncf(-0.5f));
    printf("truncf 8388608.5f = %a\n", truncf(8388608.5f));
    printf("truncf 1e10f = %a\n", truncf(1e10f));
}

static void test_roundf_cov(void)
{
    printf("roundf nanf = %a\n", roundf(nanf("")));
    printf("roundf inff = %a\n", roundf(1.0f/0.0f));
    printf("roundf -0.0f = %a\n", roundf(-0.0f));
    printf("roundf 0.5f = %a\n", roundf(0.5f));
    printf("roundf -0.5f = %a\n", roundf(-0.5f));
    printf("roundf 0.4f = %a\n", roundf(0.4f));
    printf("roundf 8388608.5f = %a\n", roundf(8388608.5f));
    printf("roundf 1e10f = %a\n", roundf(1e10f));
}

static void test_rintf_cov(void)
{
    printf("rintf nanf = %a\n", rintf(nanf("")));
    printf("rintf inff = %a\n", rintf(1.0f/0.0f));
    printf("rintf -0.0f = %a\n", rintf(-0.0f));
    printf("rintf 0.5f = %a\n", rintf(0.5f));
    printf("rintf -0.5f = %a\n", rintf(-0.5f));
    printf("rintf 0.4f = %a\n", rintf(0.4f));
    printf("rintf 8388608.5f = %a\n", rintf(8388608.5f));
    printf("rintf 0x1p-149f = %a\n", rintf(0x1p-149f));
}

static void test_lrintf_cov(void)
{
    printf("lrintf 0.4f = %ld\n", lrintf(0.4f));
    printf("lrintf -0.4f = %ld\n", lrintf(-0.4f));
    printf("lrintf 0.6f = %ld\n", lrintf(0.6f));
    printf("lrintf 1e8f = %ld\n", lrintf(1e8f));
}

static void test_llrintf_cov(void)
{
    printf("llrintf 0.4f = %lld\n", llrintf(0.4f));
    printf("llrintf -0.4f = %lld\n", llrintf(-0.4f));
    printf("llrintf 1e8f = %lld\n", llrintf(1e8f));
}

static void test_lroundf_cov(void)
{
    printf("lroundf 0.4f = %ld\n", lroundf(0.4f));
    printf("lroundf -0.4f = %ld\n", lroundf(-0.4f));
    printf("lroundf 0.5f = %ld\n", lroundf(0.5f));
    printf("lroundf -0.5f = %ld\n", lroundf(-0.5f));
    printf("lroundf 1e8f = %ld\n", lroundf(1e8f));
}

static void test_llroundf_cov(void)
{
    printf("llroundf 0.4f = %lld\n", llroundf(0.4f));
    printf("llroundf -0.4f = %lld\n", llroundf(-0.4f));
    printf("llroundf 0.5f = %lld\n", llroundf(0.5f));
    printf("llroundf 1e8f = %lld\n", llroundf(1e8f));
}

static void test_modff_cov(void)
{
    float ip;
    printf("modff nanf = %a\n", modff(nanf(""), &ip));
    printf("modff inff = %a int=%a\n", modff(1.0f/0.0f, &ip), ip);
    printf("modff -inff = %a int=%a\n", modff(-1.0f/0.0f, &ip), ip);
    printf("modff 1e10f = %a int=%a\n", modff(1e10f, &ip), ip);
    printf("modff -3.75f = %a int=%a\n", modff(-3.75f, &ip), ip);
}

static void test_fmodf_cov(void)
{
    printf("fmodf inff 2.0f = %a\n", fmodf(1.0f/0.0f, 2.0f));
    printf("fmodf nanf 2.0f = %a\n", fmodf(nanf(""), 2.0f));
    printf("fmodf 2.0f 0.0f = %a\n", fmodf(2.0f, 0.0f));
    printf("fmodf 1.0f 2.0f = %a\n", fmodf(1.0f, 2.0f));
    printf("fmodf 2.0f 2.0f = %a\n", fmodf(2.0f, 2.0f));
    printf("fmodf 0x1p-149f 2.0f = %a\n", fmodf(0x1p-149f, 2.0f));
    printf("fmodf 2.0f 0x1p-149f = %a\n", fmodf(2.0f, 0x1p-149f));
}

static void test_remainderf_cov(void)
{
    printf("remainderf inff 2.0f = %a\n", remainderf(1.0f/0.0f, 2.0f));
    printf("remainderf nanf 2.0f = %a\n", remainderf(nanf(""), 2.0f));
    printf("remainderf 2.0f 0.0f = %a\n", remainderf(2.0f, 0.0f));
    printf("remainderf 1.0f 2.0f = %a\n", remainderf(1.0f, 2.0f));
    printf("remainderf 0x1p-149f 2.0f = %a\n", remainderf(0x1p-149f, 2.0f));
}

static void test_nextafterf_cov(void)
{
    printf("nextafterf 0.0f 1.0f = %a\n", nextafterf(0.0f, 1.0f));
    printf("nextafterf -0.0f 1.0f = %a\n", nextafterf(-0.0f, 1.0f));
    printf("nextafterf 0.0f -1.0f = %a\n", nextafterf(0.0f, -1.0f));
    printf("nextafterf 1.0f 1.0f = %a\n", nextafterf(1.0f, 1.0f));
    printf("nextafterf nanf 1.0f = %a\n", nextafterf(nanf(""), 1.0f));
    printf("nextafterf inff 0.0f = %a\n", nextafterf(1.0f/0.0f, 0.0f));
    printf("nextafterf 1.0f 0.0f = %a\n", nextafterf(1.0f, 0.0f));
    printf("nextafterf 0x1p-149f 0.0f = %a\n", nextafterf(0x1p-149f, 0.0f));
    printf("nextafterf 0x1p-149f 1.0f = %a\n", nextafterf(0x1p-149f, 1.0f));
}

static void test_scalbnf_cov(void)
{
    printf("scalbnf 1.0f 127 = %a\n", scalbnf(1.0f, 127));
    printf("scalbnf 1.0f -149 = %a\n", scalbnf(1.0f, -149));
    printf("scalbnf 1.0f -200 = %a\n", scalbnf(1.0f, -200));
    printf("scalbnf 1.0f 200 = %a\n", scalbnf(1.0f, 200));
    printf("scalbnf nanf 2 = %a\n", scalbnf(nanf(""), 2));
    printf("scalbnf inff 2 = %a\n", scalbnf(1.0f/0.0f, 2));
}

static void test_scalblnf_cov(void)
{
    printf("scalblnf 1.0f 127L = %a\n", scalblnf(1.0f, 127L));
    printf("scalblnf 1.0f -149L = %a\n", scalblnf(1.0f, -149L));
    printf("scalblnf 1.0f 200L = %a\n", scalblnf(1.0f, 200L));
    printf("scalblnf 1.0f -200L = %a\n", scalblnf(1.0f, -200L));
}

static void test_fmaxf_cov(void)
{
    printf("fmaxf nanf 1.0f = %a\n", fmaxf(nanf(""), 1.0f));
    printf("fmaxf 1.0f nanf = %a\n", fmaxf(1.0f, nanf("")));
    printf("fmaxf 1.0f 1.0f = %a\n", fmaxf(1.0f, 1.0f));
    printf("fmaxf -0.0f 0.0f = %a\n", fmaxf(-0.0f, 0.0f));
}

static void test_fminf_cov(void)
{
    printf("fminf nanf 1.0f = %a\n", fminf(nanf(""), 1.0f));
    printf("fminf 1.0f nanf = %a\n", fminf(1.0f, nanf("")));
    printf("fminf 1.0f 1.0f = %a\n", fminf(1.0f, 1.0f));
    printf("fminf -0.0f 0.0f = %a\n", fminf(-0.0f, 0.0f));
}

static void test_fabsf_cov(void)
{
    printf("fabsf nanf = %a\n", fabsf(nanf("")));
    printf("fabsf inff = %a\n", fabsf(1.0f/0.0f));
    printf("fabsf -inff = %a\n", fabsf(-1.0f/0.0f));
    printf("fabsf -0.0f = %a\n", fabsf(-0.0f));
}

static void test_copysignf_cov(void)
{
    printf("copysignf nanf -1.0f = %a\n", copysignf(nanf(""), -1.0f));
    printf("copysignf 0.0f -1.0f = %a\n", copysignf(0.0f, -1.0f));
}

static void test_sinf_cov(void)
{
    printf("sinf nanf = %a\n", sinf(nanf("")));
    printf("sinf inff = %a\n", sinf(1.0f/0.0f));
    printf("sinf 1e-15f = %a\n", sinf(1e-15f));
    printf("sinf 1e9f = %a\n", sinf(1e9f));
    printf("sinf 3*pi/2 = %a\n", sinf(3.0f*(float)M_PI_2));
    printf("sinf -1.0f = %a\n", sinf(-1.0f));
}

static void test_cosf_cov(void)
{
    printf("cosf nanf = %a\n", cosf(nanf("")));
    printf("cosf inff = %a\n", cosf(1.0f/0.0f));
    printf("cosf 1e-15f = %a\n", cosf(1e-15f));
    printf("cosf 1e9f = %a\n", cosf(1e9f));
    printf("cosf 3*pi/2 = %a\n", cosf(3.0f*(float)M_PI_2));
}

static void test_tanf_cov(void)
{
    printf("tanf nanf = %a\n", tanf(nanf("")));
    printf("tanf inff = %a\n", tanf(1.0f/0.0f));
    printf("tanf 1e-15f = %a\n", tanf(1e-15f));
    printf("tanf 1e9f = %a\n", tanf(1e9f));
    printf("tanf 3*pi/4 = %a\n", tanf(3.0f*(float)M_PI/4.0f));
}

/* ------------------------------------------------------------------ */
/* Coverage-targeted: complex edge cases                              */
/* ------------------------------------------------------------------ */
static void test_csqrt_cov(void)
{
    double _Complex z;
    double _Complex r;
    /* y=0 cases */
    z = CMPLX(-4.0, 0.0);
    r = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
    z = CMPLX(0.0, 0.0);
    r = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
    /* x=0 cases */
    z = CMPLX(0.0, 4.0);
    r = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
    z = CMPLX(0.0, -4.0);
    r = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
    /* large */
    z = CMPLX(1e200, 1e200);
    r = csqrt(z);
    printf("csqrt large = %a+%ai\n", creal(r), cimag(r));
    /* small */
    z = CMPLX(1e-200, 1e-200);
    r = csqrt(z);
    printf("csqrt small = %a+%ai\n", creal(r), cimag(r));
    /* negative real */
    z = CMPLX(-1.0, 1.0);
    r = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
    /* negative imag */
    z = CMPLX(1.0, -1.0);
    r = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_csqrtf_cov(void)
{
    float _Complex z;
    float _Complex r;
    z = CMPLXF(-4.0f, 0.0f);
    r = csqrtf(z);
    printf("csqrtf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
    z = CMPLXF(0.0f, 0.0f);
    r = csqrtf(z);
    printf("csqrtf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
    z = CMPLXF(0.0f, 4.0f);
    r = csqrtf(z);
    printf("csqrtf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
    z = CMPLXF(0.0f, -4.0f);
    r = csqrtf(z);
    printf("csqrtf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
    z = CMPLXF(-1.0f, -1.0f);
    r = csqrtf(z);
    printf("csqrtf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
}

static void test_catan_cov(void)
{
    double _Complex z;
    double _Complex r;
    z = CMPLX(0.0, 2.0);
    r = catan(z);
    printf("catan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
    z = CMPLX(0.0, 0.5);
    r = catan(z);
    printf("catan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_catanf_cov(void)
{
    float _Complex z;
    float _Complex r;
    z = CMPLXF(0.0f, 2.0f);
    r = catanf(z);
    printf("catanf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
}

static void test_cpow_cov(void)
{
    double _Complex z, w, r;
    z = CMPLX(0.0, 0.0);
    w = CMPLX(2.0, 0.0);
    r = cpow(z, w);
    printf("cpow 0+0i ^ 2+0i = %a+%ai\n", creal(r), cimag(r));
    z = CMPLX(-1.0, 0.0);
    w = CMPLX(2.0, 0.0);
    r = cpow(z, w);
    printf("cpow -1+0i ^ 2+0i = %a+%ai\n", creal(r), cimag(r));
}

static void test_cpowf_cov(void)
{
    float _Complex z, w, r;
    z = CMPLXF(0.0f, 0.0f);
    w = CMPLXF(2.0f, 0.0f);
    r = cpowf(z, w);
    printf("cpowf 0+0i ^ 2+0i = %a+%ai\n", crealf(r), cimagf(r));
}

static void test_cproj_cov(void)
{
    double _Complex z;
    double _Complex r;
    z = CMPLX(1.0/0.0, 1.0);
    r = cproj(z);
    printf("cproj inf+1i = %a+%ai\n", creal(r), cimag(r));
    z = CMPLX(1.0/0.0, -1.0);
    r = cproj(z);
    printf("cproj inf-1i = %a+%ai\n", creal(r), cimag(r));
    z = CMPLX(1.0, 1.0/0.0);
    r = cproj(z);
    printf("cproj 1+infi = %a+%ai\n", creal(r), cimag(r));
}

static void test_cprojf_cov(void)
{
    float _Complex z;
    float _Complex r;
    z = CMPLXF(1.0f/0.0f, 1.0f);
    r = cprojf(z);
    printf("cprojf inff+1i = %a+%ai\n", crealf(r), cimagf(r));
    z = CMPLXF(1.0f/0.0f, -1.0f);
    r = cprojf(z);
    printf("cprojf inff-1i = %a+%ai\n", crealf(r), cimagf(r));
}

static void test_ctan_cov(void)
{
    double _Complex z;
    double _Complex r;
    /* large imag to trigger overflow path */
    z = CMPLX(1.0, 100.0);
    r = ctan(z);
    printf("ctan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
    z = CMPLX(1.0, -100.0);
    r = ctan(z);
    printf("ctan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_ctanf_cov(void)
{
    float _Complex z;
    float _Complex r;
    z = CMPLXF(1.0f, 50.0f);
    r = ctanf(z);
    printf("ctanf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
    z = CMPLXF(1.0f, -50.0f);
    r = ctanf(z);
    printf("ctanf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(r), cimagf(r));
}

/* ------------------------------------------------------------------ */
/* Coverage round 3: additional uncovered branches                   */
/* ------------------------------------------------------------------ */

/* sin/cos/tan: moderate small range (not tiny, within pi/4)
 * sind.c:75:12:false -- |x| in [2^-26, pi/4]
 * cosd.c:73:12:false -- |x| in [2^-27*sqrt(2), pi/4]
 * tand.c:160:12:false -- |x| in [2^-27, pi/4]
 * sinf.c:24:12:false, cosf.c:24:12:false, tanf.c:100:12:false */
static void test_trig_moderate(void)
{
    printf("sin 0.1 = %a\n", sin(0.1));
    printf("sin 0.5 = %a\n", sin(0.5));
    printf("cos 0.1 = %a\n", cos(0.1));
    printf("cos 0.5 = %a\n", cos(0.5));
    printf("tan 0.1 = %a\n", tan(0.1));
    printf("tan 0.5 = %a\n", tan(0.5));
    printf("sinf 0.1f = %a\n", sinf(0.1f));
    printf("sinf 0.5f = %a\n", sinf(0.5f));
    printf("cosf 0.1f = %a\n", cosf(0.1f));
    printf("cosf 0.5f = %a\n", cosf(0.5f));
    printf("tanf 0.1f = %a\n", tanf(0.1f));
    printf("tanf 0.5f = %a\n", tanf(0.5f));
}

/* asin: |x| in [2^-26, 0.5) -- asind.c:104:13:false */
static void test_asin_moderate(void)
{
    printf("asin 0.1 = %a\n", asin(0.1));
    printf("asin 0.2 = %a\n", asin(0.2));
    printf("asinf 0.1f = %a\n", asinf(0.1f));
    printf("asinf 0.2f = %a\n", asinf(0.2f));
}

/* atan: NaN, Inf, tiny nonzero
 * atand.c:104:13:true, atand.c:118:17:false */
static void test_atan_extra(void)
{
    printf("atan nan = %a\n", atan(nan("")));
    printf("atan inf = %a\n", atan(1.0/0.0));
    printf("atan -inf = %a\n", atan(-1.0/0.0));
    /* tiny nonzero: |x| < 2^-27, x != 0 */
    printf("atan 1e-10 = %a\n", atan(1e-10));
    printf("atan -1e-10 = %a\n", atan(-1e-10));
    printf("atanf nanf = %a\n", atanf(nanf("")));
    printf("atanf 1e-10f = %a\n", atanf(1e-10f));
}

/* acosf(-1.0f): acosf.c:36:13:false (hx <= 0 when x == -1)
 * acoshf in (2, 2^28): acoshf.c:36:16:true */
static void test_acosf_acoshf_extra(void)
{
    printf("acosf -1.0f = %a\n", acosf(-1.0f));
    printf("acoshf 3.0f = %a\n", acoshf(3.0f));
    printf("acoshf 10.0f = %a\n", acoshf(10.0f));
    printf("acoshf 100.0f = %a\n", acoshf(100.0f));
}

/* cpow with imaginary exponent: cpowd.c:67:9:true (imagz != 0) */
static void test_cpow_imagexp(void)
{
    double _Complex r;
    r = cpow(CMPLX(2.0, 1.0), CMPLX(1.0, 2.0));
    printf("cpow 2+1i^1+2i = %a+%ai\n", creal(r), cimag(r));
    r = cpow(CMPLX(1.0, 1.0), CMPLX(2.0, 1.0));
    printf("cpow 1+1i^2+1i = %a+%ai\n", creal(r), cimag(r));
    r = cpow(CMPLX(2.0, 0.0), CMPLX(1.0, 1.0));
    printf("cpow 2+0i^1+1i = %a+%ai\n", creal(r), cimag(r));
}

/* cpowf with imaginary exponent: cpowf.c:28:9:true (imagz != 0) */
static void test_cpowf_imagexp(void)
{
    float _Complex r;
    r = cpowf(CMPLXF(2.0f, 1.0f), CMPLXF(1.0f, 2.0f));
    printf("cpowf 2+1i^1+2i = %a+%ai\n", crealf(r), cimagf(r));
    r = cpowf(CMPLXF(2.0f, 0.0f), CMPLXF(1.0f, 1.0f));
    printf("cpowf 2+0i^1+1i = %a+%ai\n", crealf(r), cimagf(r));
}

/* csqrt with |y| > 4 but |x| <= 4: csqrtd.c:86:28:true */
static void test_csqrt_large_imag(void)
{
    double _Complex r;
    r = csqrt(CMPLX(1.0, 100.0));
    printf("csqrt 1+100i = %a+%ai\n", creal(r), cimag(r));
    r = csqrt(CMPLX(1.0, -100.0));
    printf("csqrt 1-100i = %a+%ai\n", creal(r), cimag(r));
    r = csqrt(CMPLX(-1.0, 100.0));
    printf("csqrt -1+100i = %a+%ai\n", creal(r), cimag(r));
    r = csqrt(CMPLX(0.0, 10.0));
    printf("csqrt 0+10i = %a+%ai\n", creal(r), cimag(r));
}

/* csqrtf with |y| > 4 but |x| <= 4: csqrtf.c:44:9:true, 44:30:true */
static void test_csqrtf_large_imag(void)
{
    float _Complex r;
    r = csqrtf(CMPLXF(1.0f, 100.0f));
    printf("csqrtf 1+100i = %a+%ai\n", crealf(r), cimagf(r));
    r = csqrtf(CMPLXF(-1.0f, 100.0f));
    printf("csqrtf -1+100i = %a+%ai\n", crealf(r), cimagf(r));
    r = csqrtf(CMPLXF(0.0f, 10.0f));
    printf("csqrtf 0+10i = %a+%ai\n", crealf(r), cimagf(r));
    r = csqrtf(CMPLXF(0.001f, 100.0f));
    printf("csqrtf 0.001+100i = %a+%ai\n", crealf(r), cimagf(r));
}

/* ctan with d near zero: ctand.c:98:9:true (fabs(d)<0.25), 102:9:true (d==0)
 * d = cos(2*Re(z)) + cosh(2*Im(z)), near zero when Re(z) ≈ pi/2, Im(z)≈0 */
static void test_ctan_extra(void)
{
    double _Complex r;
    r = ctan(CMPLX(M_PI_2, 0.0));
    printf("ctan pi/2+0i = %a+%ai\n", creal(r), cimag(r));
    r = ctan(CMPLX(M_PI_2, 1e-15));
    printf("ctan pi/2+1e-15i = %a+%ai\n", creal(r), cimag(r));
    r = ctan(CMPLX(M_PI_2 * 0.9999, 0.0));
    printf("ctan near-pi/2+0i = %a+%ai\n", creal(r), cimag(r));
}

/* ctanf: ctanf.c:62:9:true, 66:9:true */
static void test_ctanf_extra(void)
{
    float _Complex r;
    r = ctanf(CMPLXF((float)M_PI_2, 0.0f));
    printf("ctanf pi/2+0i = %a+%ai\n", crealf(r), cimagf(r));
    r = ctanf(CMPLXF((float)M_PI_2 * 0.9999f, 1e-10f));
    printf("ctanf near-pi/2 = %a+%ai\n", crealf(r), cimagf(r));
}

/* __ccoshsinh/-sinhf with very negative x:
 * ctrigd.c:21:13:false -- exp(x) underflows to 0
 * ctrigf.c:19:13:false -- expf(x) underflows to 0 */
static void test_ccoshsinh_extreme(void)
{
    double c, s;
    __ccoshsinh(-800.0, &c, &s);
    printf("__ccoshsinh -800 c=%a s=%a\n", c, s);
    __ccoshsinh(800.0, &c, &s);
    printf("__ccoshsinh 800 c=%a s=%a\n", c, s);
    float cf, sf;
    __ccoshsinhf(-200.0f, &cf, &sf);
    printf("__ccoshsinhf -200 c=%a s=%a\n", cf, sf);
    __ccoshsinhf(200.0f, &cf, &sf);
    printf("__ccoshsinhf 200 c=%a s=%a\n", cf, sf);
}

/* Signaling NaN tests:
 * tools.h:401:21:true -- __issignaling returns 1
 * tools.h:411:47:true -- __issignalingf returns 1
 * powd.c:139:13:true, fmaxd.c:75:13:true and 75:38:true, etc. */
static void test_snan(void)
{
    /* Double sNaN: quiet bit (bit 19 of high word = 0x00080000) cleared */
    uint64_t sbits = 0x7ff0000000000001ULL;
    double snan_d;
    __builtin_memcpy(&snan_d, &sbits, sizeof(snan_d));

    /* Float sNaN: quiet bit (bit 22 = 0x00400000) cleared */
    uint32_t sfbits = 0x7f800001U;
    float snan_f;
    __builtin_memcpy(&snan_f, &sfbits, sizeof(snan_f));

    /* fmaxd.c:75:13:true and 75:38:true: isnan(x) && (issignaling(x)||issignaling(y)) */
    printf("fmax snan 1.0 = %a\n", fmax(snan_d, 1.0));
    printf("fmax 1.0 snan = %a\n", fmax(1.0, snan_d));
    printf("fmax snan snan = %a\n", fmax(snan_d, snan_d));
    /* fmind.c:75:13:true and 75:38:true */
    printf("fmin snan 1.0 = %a\n", fmin(snan_d, 1.0));
    printf("fmin 1.0 snan = %a\n", fmin(1.0, snan_d));
    /* powd.c:139:13:true: if (__issignaling(x) != 0) */
    printf("pow snan 2.0 = %a\n", pow(snan_d, 2.0));
    /* Float variants */
    printf("fmaxf snanf 1.0f = %a\n", fmaxf(snan_f, 1.0f));
    printf("fmaxf 1.0f snanf = %a\n", fmaxf(1.0f, snan_f));
    printf("fminf snanf 1.0f = %a\n", fminf(snan_f, 1.0f));
    printf("fminf 1.0f snanf = %a\n", fminf(1.0f, snan_f));
    printf("powf snanf 2.0f = %a\n", powf(snan_f, 2.0f));
}

/* ldexpf: non-finite and zero inputs
 * ldexpf.c:13:9:true (x non-finite), 13:31:true (x == 0) */
static void test_ldexpf_extra(void)
{
    printf("ldexpf nanf 2 = %a\n", ldexpf(nanf(""), 2));
    printf("ldexpf inff 2 = %a\n", ldexpf(1.0f/0.0f, 2));
    printf("ldexpf -inff 2 = %a\n", ldexpf(-1.0f/0.0f, 2));
    printf("ldexpf 0.0f 5 = %a\n", ldexpf(0.0f, 5));
}

/* asinhf: medium range (not covered by existing tests)
 * asinhf.c:37:16:true */
static void test_asinhf_extra(void)
{
    printf("asinhf 4.0f = %a\n", asinhf(4.0f));
    printf("asinhf -4.0f = %a\n", asinhf(-4.0f));
    printf("asinhf 3.0f = %a\n", asinhf(3.0f));
    printf("asinhf 0.3f = %a\n", asinhf(0.3f));
    printf("asinhf -0.3f = %a\n", asinhf(-0.3f));
}

/* remquof: more cases -- remquof.c various branches */
static void test_remquof_extra(void)
{
    int quo;
    float r;
    r = remquof(100.0f, 1.0f, &quo);
    printf("remquof 100.0 1.0 = %a quo=%d\n", r, quo);
    r = remquof(3.5f, 1.0f, &quo);
    printf("remquof 3.5 1.0 = %a quo=%d\n", r, quo);
    r = remquof(-3.5f, 1.0f, &quo);
    printf("remquof -3.5 1.0 = %a quo=%d\n", r, quo);
    r = remquof(5.0f, 2.0f, &quo);
    printf("remquof 5.0 2.0 = %a quo=%d\n", r, quo);
    r = remquof(0x1p-149f, 1.0f, &quo);
    printf("remquof tiny 1.0 = %a quo=%d\n", r, quo);
}

/* atanf: extra coverage for small/large values */
static void test_atanf_extra(void)
{
    printf("atanf 1e-10f = %a\n", atanf(1e-10f));
    printf("atanf -1e-10f = %a\n", atanf(-1e-10f));
    printf("atanf 0.3f = %a\n", atanf(0.3f));
    printf("atanf -0.3f = %a\n", atanf(-0.3f));
}

/* catanf: catanf.c:19:24:false -- (x==0.0f) && (y>1.0f) is false (y<=1) */
static void test_catanf_extra(void)
{
    float _Complex z, r;
    /* x=0, y=0.5 <= 1: condition (y > 1.0f) is false */
    z = CMPLXF(0.0f, 0.5f);
    r = catanf(z);
    printf("catanf 0+0.5i = %a+%ai\n", crealf(r), cimagf(r));
    /* x=0, y=0.9 <= 1 */
    z = CMPLXF(0.0f, 0.9f);
    r = catanf(z);
    printf("catanf 0+0.9i = %a+%ai\n", crealf(r), cimagf(r));
    /* x=0, y=2.0 > 1: condition is true (overflow path) */
    z = CMPLXF(0.0f, 2.0f);
    r = catanf(z);
    printf("catanf 0+2i = %a+%ai\n", crealf(r), cimagf(r));
}

/* ------------------------------------------------------------------ */
/* Coverage round 4: additional uncovered branches                    */
/* ------------------------------------------------------------------ */

/* lgamma/tgamma with comprehensive range coverage - gammad.c/gammaf.c */
static void test_lgamma_coverage2(void)
{
    /* x in [2,8): different switch cases i=2..7 */
    printf("lgamma 2.5 = %a\n", lgamma(2.5));
    printf("lgamma 3.5 = %a\n", lgamma(3.5));
    printf("lgamma 4.5 = %a\n", lgamma(4.5));
    printf("lgamma 5.5 = %a\n", lgamma(5.5));
    printf("lgamma 6.5 = %a\n", lgamma(6.5));
    printf("lgamma 7.5 = %a\n", lgamma(7.5));
    /* x in (0, 2): sub-range i=0,1,2 */
    printf("lgamma 0.3 = %a\n", lgamma(0.3));
    printf("lgamma 0.4 = %a\n", lgamma(0.4));
    printf("lgamma 0.8 = %a\n", lgamma(0.8));
    printf("lgamma 1.1 = %a\n", lgamma(1.1));
    printf("lgamma 1.5 = %a\n", lgamma(1.5));
    printf("lgamma 1.8 = %a\n", lgamma(1.8));
    /* Negative x: different __sin_pi switch cases */
    printf("lgamma -0.4 = %a\n", lgamma(-0.4));  /* sin_pi n=1 */
    printf("lgamma -0.6 = %a\n", lgamma(-0.6));  /* sin_pi n=2 */
    printf("lgamma -0.8 = %a\n", lgamma(-0.8));  /* sin_pi n=3 */
    printf("lgamma -1.1 = %a\n", lgamma(-1.1));  /* sin_pi n=4 */
    printf("lgamma -1.4 = %a\n", lgamma(-1.4));  /* sin_pi n=5 */
    printf("lgamma -1.6 = %a\n", lgamma(-1.6));  /* sin_pi n=6 */
    printf("lgamma -1.9 = %a\n", lgamma(-1.9));  /* sin_pi default n=7 */
    /* very tiny x: |x| < 2^-70 */
    printf("lgamma 1e-25 = %a\n", lgamma(1e-25));
    printf("lgamma -1e-25 = %a\n", lgamma(-1e-25));
    /* large negative: |x| >= 2^52 → must be -integer */
    printf("lgamma -1e16 = %a\n", lgamma(-1e16));
    /* tgamma same ranges */
    printf("tgamma 2.5 = %a\n", tgamma(2.5));
    printf("tgamma 3.5 = %a\n", tgamma(3.5));
    printf("tgamma 4.5 = %a\n", tgamma(4.5));
    printf("tgamma 5.5 = %a\n", tgamma(5.5));
    printf("tgamma 6.5 = %a\n", tgamma(6.5));
    printf("tgamma 7.5 = %a\n", tgamma(7.5));
}

static void test_lgammaf_coverage2(void)
{
    printf("lgammaf 2.5f = %a\n", lgammaf(2.5f));
    printf("lgammaf 3.5f = %a\n", lgammaf(3.5f));
    printf("lgammaf 4.5f = %a\n", lgammaf(4.5f));
    printf("lgammaf 5.5f = %a\n", lgammaf(5.5f));
    printf("lgammaf 6.5f = %a\n", lgammaf(6.5f));
    printf("lgammaf 7.5f = %a\n", lgammaf(7.5f));
    printf("lgammaf 0.3f = %a\n", lgammaf(0.3f));
    printf("lgammaf 0.4f = %a\n", lgammaf(0.4f));
    printf("lgammaf 0.8f = %a\n", lgammaf(0.8f));
    printf("lgammaf 1.1f = %a\n", lgammaf(1.1f));
    printf("lgammaf 1.5f = %a\n", lgammaf(1.5f));
    printf("lgammaf 1.8f = %a\n", lgammaf(1.8f));
    /* Negative x: different __sin_pif switch cases */
    printf("lgammaf -0.4f = %a\n", lgammaf(-0.4f));
    printf("lgammaf -0.6f = %a\n", lgammaf(-0.6f));
    printf("lgammaf -0.8f = %a\n", lgammaf(-0.8f));
    printf("lgammaf -1.1f = %a\n", lgammaf(-1.1f));
    printf("lgammaf -1.4f = %a\n", lgammaf(-1.4f));
    printf("lgammaf -1.6f = %a\n", lgammaf(-1.6f));
    printf("lgammaf -1.9f = %a\n", lgammaf(-1.9f));
    /* tiny x */
    printf("lgammaf 1e-15f = %a\n", lgammaf(1e-15f));
    printf("lgammaf -1e-15f = %a\n", lgammaf(-1e-15f));
    /* large negative integer: |x| >= 2^23 */
    printf("lgammaf -1e8f = %a\n", lgammaf(-1e8f));
    /* tgammaf same ranges */
    printf("tgammaf 2.5f = %a\n", tgammaf(2.5f));
    printf("tgammaf 3.5f = %a\n", tgammaf(3.5f));
    printf("tgammaf 4.5f = %a\n", tgammaf(4.5f));
    printf("tgammaf 5.5f = %a\n", tgammaf(5.5f));
    printf("tgammaf 6.5f = %a\n", tgammaf(6.5f));
    printf("tgammaf 7.5f = %a\n", tgammaf(7.5f));
}

/* sinh/cosh near and past overflow threshold (~710.476...) */
static void test_sinh_cosh_overflow(void)
{
    printf("sinh 710.47 = %a\n", sinh(710.47));
    printf("cosh 710.47 = %a\n", cosh(710.47));
    printf("sinh 711.0 = %a\n", sinh(711.0));
    printf("cosh 711.0 = %a\n", cosh(711.0));
    printf("sinh -711.0 = %a\n", sinh(-711.0));
    printf("cosh -711.0 = %a\n", cosh(-711.0));
}

/* jn with large x (different n&3 cases), negative n, and small x */
static void test_jn_coverage2(void)
{
    /* Large x > 2^302: switch n&3 = 0,1,2,3 */
    printf("jn 4 1e303 = %a\n", jn(4, 1e303));
    printf("jn 5 1e303 = %a\n", jn(5, 1e303));
    printf("jn 2 1e303 = %a\n", jn(2, 1e303));
    printf("jn 3 1e303 = %a\n", jn(3, 1e303));
    /* Negative n: jn(-n,x) = (-1)^n jn(n,x) */
    printf("jn -2 1.0 = %a\n", jn(-2, 1.0));
    printf("jn -3 1.0 = %a\n", jn(-3, 1.0));
    /* Very small x, n <= 33: tiny Taylor expansion */
    printf("jn 2 1e-10 = %a\n", jn(2, 1e-10));
    printf("jn 5 1e-10 = %a\n", jn(5, 1e-10));
    /* Very small x, n > 33: underflow */
    printf("jn 34 1e-10 = %a\n", jn(34, 1e-10));
    printf("jn 50 1e-10 = %a\n", jn(50, 1e-10));
    /* More n values for backward recurrence */
    printf("jn 3 2.0 = %a\n", jn(3, 2.0));
    printf("jn 4 2.0 = %a\n", jn(4, 2.0));
    printf("jn 5 2.0 = %a\n", jn(5, 2.0));
    printf("jn 100 1.0 = %a\n", jn(100, 1.0));
}

/* yn with large x, negative n, and varied n */
static void test_yn_coverage2(void)
{
    /* Large x > 2^302: switch n&3 = 0,1,2,3 */
    printf("yn 4 1e303 = %a\n", yn(4, 1e303));
    printf("yn 5 1e303 = %a\n", yn(5, 1e303));
    printf("yn 2 1e303 = %a\n", yn(2, 1e303));
    printf("yn 3 1e303 = %a\n", yn(3, 1e303));
    /* Negative n */
    printf("yn -2 1.0 = %a\n", yn(-2, 1.0));
    printf("yn -3 1.0 = %a\n", yn(-3, 1.0));
    /* Various n for forward recurrence */
    printf("yn 3 1.0 = %a\n", yn(3, 1.0));
    printf("yn 4 1.0 = %a\n", yn(4, 1.0));
    printf("yn 5 1.0 = %a\n", yn(5, 1.0));
    printf("yn 10 0.5 = %a\n", yn(10, 0.5));
    printf("yn 20 2.0 = %a\n", yn(20, 2.0));
}

/* atan/atanf with very large x: ix >= 0x44100000 (|x| >= 2^66) */
static void test_atan_xlarge(void)
{
    printf("atan 1e20 = %a\n", atan(1e20));
    printf("atan -1e20 = %a\n", atan(-1e20));
    printf("atan 1e25 = %a\n", atan(1e25));
    printf("atanf 1e20f = %a\n", atanf(1e20f));
    printf("atanf -1e20f = %a\n", atanf(-1e20f));
}

/* y0/y1 extreme: -Inf and x >= 2^1023 */
static void test_y0_y1_extreme(void)
{
    printf("y0 -inf = %a\n", y0(-1.0/0.0));
    printf("y1 -inf = %a\n", y1(-1.0/0.0));
    /* x large: ix >= 0x7fe00000 means make sure x+x doesn't overflow */
    printf("y0 1e308 = %a\n", y0(1e308));
    printf("y1 1e308 = %a\n", y1(1e308));
}

/* j0/j1 with specific x ranges to hit besseld.h branches */
static void test_bessel_ranges(void)
{
    /* __j0_p: ix >= 0x41b00000 (x >= 2^28) → return 1.0 */
    printf("j0 1e9 = %a\n", j0(1e9));
    printf("j1 1e9 = %a\n", j1(1e9));
    /* ix >= 0x40200000 (x >= 8) */
    printf("j0 15.0 = %a\n", j0(15.0));
    printf("j1 15.0 = %a\n", j1(15.0));
    /* ix >= 0x40122E8B (~4.5) */
    printf("j0 5.0 = %a\n", j0(5.0));
    printf("j1 5.0 = %a\n", j1(5.0));
    /* ix >= 0x4006DB6D (~2.86) */
    printf("j0 3.0 = %a\n", j0(3.0));
    printf("j1 3.0 = %a\n", j1(3.0));
    /* y0/y1 large x > 2^28 */
    printf("y0 1e9 = %a\n", y0(1e9));
    printf("y1 1e9 = %a\n", y1(1e9));
    /* y0 with x < 2^-27 */
    printf("y0 1e-10 = %a\n", y0(1e-10));
    printf("y1 1e-10 = %a\n", y1(1e-10));
}

/* pow with more special cases */
static void test_pow_coverage2(void)
{
    /* pow(-x, negative odd integer): yisint=1 */
    printf("pow -2.0 -3.0 = %a\n", pow(-2.0, -3.0));
    /* pow(-x, large even integer): yisint=2 via k>20 path */
    printf("pow -2.0 4.0 = %a\n", pow(-2.0, 4.0));
    printf("pow -2.0 -4.0 = %a\n", pow(-2.0, -4.0));
    /* pow(-x, y >= 2^53): yisint=2 automatically */
    printf("pow -2.0 1e16 = %a\n", pow(-2.0, 1e16));
    /* pow underflow: z <= -1075 */
    printf("pow 2.0 -1075.0 = %a\n", pow(2.0, -1075.0));
    /* pow subnormal output: (j>>20) <= 0 */
    printf("pow 2.0 -1074.0 = %a\n", pow(2.0, -1074.0));
    /* pow near 1 */
    printf("pow 0.999 1000.0 = %a\n", pow(0.999, 1000.0));
    printf("pow 1.001 1000.0 = %a\n", pow(1.001, 1000.0));
    /* pow with non-integer y exponent */
    printf("pow -1.5 2.5 = %a\n", pow(-1.5, 2.5));
    /* powf additional cases */
    printf("powf -2.0f -3.0f = %a\n", powf(-2.0f, -3.0f));
    printf("powf -2.0f 4.0f = %a\n", powf(-2.0f, 4.0f));
    printf("powf 2.0f -200.0f = %a\n", powf(2.0f, -200.0f));
    printf("powf 0.999f 1000.0f = %a\n", powf(0.999f, 1000.0f));
    printf("powf 1.001f 1000.0f = %a\n", powf(1.001f, 1000.0f));
}

/* trig with additional medium-large arguments for rem_pio2 paths */
static void test_trig_coverage2(void)
{
    printf("sin 7*pi/2 = %a\n", sin(7.0 * M_PI_2));
    printf("cos 7*pi/2 = %a\n", cos(7.0 * M_PI_2));
    printf("sin 11*pi/4 = %a\n", sin(11.0 * M_PI / 4.0));
    printf("cos 11*pi/4 = %a\n", cos(11.0 * M_PI / 4.0));
    printf("sin 1e6 = %a\n", sin(1e6));
    printf("cos 1e6 = %a\n", cos(1e6));
    printf("sin 1e15 = %a\n", sin(1e15));
    printf("cos 1e15 = %a\n", cos(1e15));
    printf("sin -5.0 = %a\n", sin(-5.0));
    printf("cos -5.0 = %a\n", cos(-5.0));
    printf("tan -5.0 = %a\n", tan(-5.0));
    printf("sin 1e5 = %a\n", sin(1e5));
    printf("cos 1e5 = %a\n", cos(1e5));
    printf("sinf 7*pi/2 = %a\n", sinf(7.0f * (float)M_PI_2));
    printf("cosf 7*pi/2 = %a\n", cosf(7.0f * (float)M_PI_2));
    printf("sinf 11*pi/4 = %a\n", sinf(11.0f * (float)M_PI / 4.0f));
    printf("tanf 5*pi/4 = %a\n", tanf(5.0f * (float)M_PI / 4.0f));
    printf("sinf 1e6f = %a\n", sinf(1e6f));
    printf("cosf 1e6f = %a\n", cosf(1e6f));
    printf("sinf -5.0f = %a\n", sinf(-5.0f));
    printf("cosf -5.0f = %a\n", cosf(-5.0f));
    printf("tanf -5.0f = %a\n", tanf(-5.0f));
}

/* erff with specific ranges */
static void test_erff_coverage2(void)
{
    /* |x| in [2^-14, 0.84375): erff.c:41:false */
    printf("erff 0.5f = %a\n", erff(0.5f));
    /* negative x in [0.84375, 1.25): erff.c:59:false */
    printf("erff -1.0f = %a\n", erff(-1.0f));
    /* negative x >= 4: erff.c:67:false */
    printf("erff -4.0f = %a\n", erff(-4.0f));
    printf("erff -5.0f = %a\n", erff(-5.0f));
    /* x in [1.25, 4) with |x| >= 1/0.35: erff.c:77:false */
    printf("erff 3.0f = %a\n", erff(3.0f));
    printf("erff -3.0f = %a\n", erff(-3.0f));
    /* |x| in [0.84375, 1.25): erff.c:59:true */
    printf("erff 1.0f = %a\n", erff(1.0f));
    printf("erff 1.1f = %a\n", erff(1.1f));
}

/* erfcf with specific ranges */
static void test_erfcf_coverage2(void)
{
    /* |x| in [2^-24, 0.84375): erfcf.c:36:false */
    printf("erfcf 0.1f = %a\n", erfcf(0.1f));
    /* x >= 0.25 in [0, 0.84375): erfcf.c:42:false */
    printf("erfcf 0.5f = %a\n", erfcf(0.5f));
    /* negative x in [0.84375, 1.25): erfcf.c:56:false */
    printf("erfcf -1.0f = %a\n", erfcf(-1.0f));
    /* |x| in [2.857, 6): erfcf.c:73:false */
    printf("erfcf 3.0f = %a\n", erfcf(3.0f));
    /* negative x < -6: erfcf.c:73:true */
    printf("erfcf -7.0f = %a\n", erfcf(-7.0f));
    printf("erfcf -6.5f = %a\n", erfcf(-6.5f));
    /* |x| >= 10.125, x < 0: erfcf.c:91:false */
    printf("erfcf -11.0f = %a\n", erfcf(-11.0f));
    /* more ranges */
    printf("erfcf 1.5f = %a\n", erfcf(1.5f));
    printf("erfcf -1.5f = %a\n", erfcf(-1.5f));
    printf("erfcf 2.5f = %a\n", erfcf(2.5f));
}

/* atanhf: negative x path */
static void test_atanhf_coverage2(void)
{
    printf("atanhf -0.5f = %a\n", atanhf(-0.5f));
    printf("atanhf -0.1f = %a\n", atanhf(-0.1f));
    printf("atanhf -0.9f = %a\n", atanhf(-0.9f));
}

/* Additional rint/lrint/round for remaining branches */
static void test_rint_coverage2(void)
{
    printf("rint 0.1 = %a\n", rint(0.1));
    printf("rint -0.1 = %a\n", rint(-0.1));
    printf("rint 1.4 = %a\n", rint(1.4));
    printf("rint -1.4 = %a\n", rint(-1.4));
    printf("lrint 0.0 = %ld\n", lrint(0.0));
    printf("lrint 2.5 = %ld\n", lrint(2.5));
    printf("lrint -2.5 = %ld\n", lrint(-2.5));
    printf("llrint 0.0 = %lld\n", llrint(0.0));
    printf("llrint 2.5 = %lld\n", llrint(2.5));
    printf("llrint -2.5 = %lld\n", llrint(-2.5));
    printf("lround 0.0 = %ld\n", lround(0.0));
    printf("lround 2.5 = %ld\n", lround(2.5));
    printf("llround 0.0 = %lld\n", llround(0.0));
    printf("llround 2.5 = %lld\n", llround(2.5));
    printf("rintf 0.1f = %a\n", rintf(0.1f));
    printf("rintf 1.4f = %a\n", rintf(1.4f));
    printf("rintf -1.4f = %a\n", rintf(-1.4f));
    printf("lrintf 0.0f = %ld\n", lrintf(0.0f));
    printf("lrintf 2.5f = %ld\n", lrintf(2.5f));
    printf("llrintf 0.0f = %lld\n", llrintf(0.0f));
    printf("lroundf 0.0f = %ld\n", lroundf(0.0f));
    printf("lroundf 2.5f = %ld\n", lroundf(2.5f));
    printf("llroundf 0.0f = %lld\n", llroundf(0.0f));
    printf("roundf 2.5f = %a\n", roundf(2.5f));
}

/* cosh/sinh additional cases for uncovered branches */
static void test_coshf_sinhf_extra(void)
{
    /* coshf: 51:9:true — |x| in [1, log(max)] */
    printf("coshf 10.0f = %a\n", coshf(10.0f));
    printf("coshf 50.0f = %a\n", coshf(50.0f));
    printf("sinhf 10.0f = %a\n", sinhf(10.0f));
    printf("sinhf 50.0f = %a\n", sinhf(50.0f));
    printf("sinhf -10.0f = %a\n", sinhf(-10.0f));
}

/* Additional log coverage */
static void test_log_coverage2(void)
{
    printf("log 0.75 = %a\n", log(0.75));
    printf("log 1.25 = %a\n", log(1.25));
    printf("log 0.9 = %a\n", log(0.9));
    printf("log10 2.0 = %a\n", log10(2.0));
    printf("log10 5.0 = %a\n", log10(5.0));
    printf("log2 3.0 = %a\n", log2(3.0));
    printf("log2 5.0 = %a\n", log2(5.0));
    printf("logf 0.75f = %a\n", logf(0.75f));
    printf("logf 1.25f = %a\n", logf(1.25f));
    printf("log10f 2.0f = %a\n", log10f(2.0f));
    printf("log10f 5.0f = %a\n", log10f(5.0f));
    printf("log2f 3.0f = %a\n", log2f(3.0f));
    printf("log2f 5.0f = %a\n", log2f(5.0f));
}

/* ------------------------------------------------------------------ */
/* Coverage round 5: additional uncovered branches                    */
/* ------------------------------------------------------------------ */

/* scalbn/scalbln: zero input, subnormal input, extreme n             */
static void test_scalbn_coverage3(void)
{
    /* scalbnd.c:97:13:true - x is ±0 (k==0 and mantissa==0) */
    printf("scalbn 0.0 5 = %a\n", scalbn(0.0, 5));
    printf("scalbn -0.0 5 = %a\n", scalbn(-0.0, 5));
    /* scalbnd.c:114:9:true - n > 50000: overflow */
    printf("scalbn 1.0 100000 = %a\n", scalbn(1.0, 100000));
    printf("scalbn -1.0 100000 = %a\n", scalbn(-1.0, 100000));
    /* subnormal x with large positive n → normal result */
    printf("scalbn 0x1p-1074 2000 = %a\n", scalbn(0x1p-1074, 2000));
    /* subnormal result */
    printf("scalbn 1.0 -1074 = %a\n", scalbn(1.0, -1074));
    /* scalblnd.c:93:13:true - x is ±0 */
    printf("scalbln 0.0 5L = %a\n", scalbln(0.0, 5L));
    printf("scalbln -0.0 3L = %a\n", scalbln(-0.0, 3L));
    /* scalblnd.c:92:9:true and 93:13:false - subnormal non-zero */
    printf("scalbln 0x1p-1074 2L = %a\n", scalbln(0x1p-1074, 2L));
    printf("scalbln 0x1p-1073 3L = %a\n", scalbln(0x1p-1073, 3L));
    /* scalblnd.c:106:9:true - n > 50000 */
    printf("scalbln 1.0 100000L = %a\n", scalbln(1.0, 100000L));
    /* scalblnd.c:116:9:true - n < -50000 */
    printf("scalbln 1.0 -100000L = %a\n", scalbln(1.0, -100000L));
    printf("scalbln -1.0 -100000L = %a\n", scalbln(-1.0, -100000L));
}

static void test_scalbnf_coverage3(void)
{
    /* scalbnf: x = ±0 */
    printf("scalbnf 0.0f 5 = %a\n", scalbnf(0.0f, 5));
    printf("scalbnf -0.0f 5 = %a\n", scalbnf(-0.0f, 5));
    /* scalbnf: n > 50000 overflow */
    printf("scalbnf 1.0f 100000 = %a\n", scalbnf(1.0f, 100000));
    /* scalbnf: subnormal x large positive n */
    printf("scalbnf 0x1p-149f 200 = %a\n", scalbnf(0x1p-149f, 200));
    /* scalblnf: similar */
    printf("scalblnf 0.0f 5L = %a\n", scalblnf(0.0f, 5L));
    printf("scalblnf 0x1p-149f 2L = %a\n", scalblnf(0x1p-149f, 2L));
    printf("scalblnf 1.0f 100000L = %a\n", scalblnf(1.0f, 100000L));
    printf("scalblnf 1.0f -100000L = %a\n", scalblnf(1.0f, -100000L));
    printf("scalblnf -1.0f 100000L = %a\n", scalblnf(-1.0f, 100000L));
}

/* modf: integral values and mid-range fraction (j0 in [20,51])       */
static void test_modf_coverage2(void)
{
    double ip;
    /* modfd.c:88:17:true - x is integral in [1, 2^20) */
    printf("modf 3.0 = %a int=%a\n", modf(3.0, &ip), ip);
    printf("modf -5.0 = %a int=%a\n", modf(-5.0, &ip), ip);
    printf("modf 2.0 = %a int=%a\n", modf(2.0, &ip), ip);
    printf("modf -2.0 = %a int=%a\n", modf(-2.0, &ip), ip);
    /* modfd.c:109:13:true - integral in [2^20, 2^52) */
    printf("modf 2097152.0 = %a int=%a\n", modf(2097152.0, &ip), ip);
    printf("modf -2097152.0 = %a int=%a\n", modf(-2097152.0, &ip), ip);
    printf("modf 1048576.0 = %a int=%a\n", modf(1048576.0, &ip), ip);
    /* modfd.c:109:13:false and 97:16:false - fractional in [2^20, 2^52) */
    printf("modf 1048576.5 = %a int=%a\n", modf(1048576.5, &ip), ip);
    printf("modf -1048576.5 = %a int=%a\n", modf(-1048576.5, &ip), ip);
    printf("modf 4194304.75 = %a int=%a\n", modf(4194304.75, &ip), ip);
}

static void test_modff_coverage2(void)
{
    float ip;
    /* integral in [1, 2^23) */
    printf("modff 3.0f = %a int=%a\n", modff(3.0f, &ip), ip);
    printf("modff -5.0f = %a int=%a\n", modff(-5.0f, &ip), ip);
    printf("modff 2.0f = %a int=%a\n", modff(2.0f, &ip), ip);
    /* float 2^23 boundary */
    printf("modff 8388608.0f = %a int=%a\n", modff(8388608.0f, &ip), ip);
    printf("modff 8388608.5f = %a int=%a\n", modff(8388608.5f, &ip), ip);
    printf("modff -8388608.5f = %a int=%a\n", modff(-8388608.5f, &ip), ip);
}

/* nextafter: ±zero pair, same-exponent, and overflow                 */
static void test_nextafter_coverage2(void)
{
    /* nextafterd.c:95:13:true - x=+0, y=-0 → returns -0 */
    printf("nextafter 0.0 -0.0 = %a\n", nextafter(0.0, -0.0));
    printf("nextafter -0.0 0.0 = %a\n", nextafter(-0.0, 0.0));
    /* nextafterd.c:95:40:false - x=0, y has same upper bits but ly!=0 */
    printf("nextafter 0.0 0x1p-1074 = %a\n", nextafter(0.0, 0x1p-1074));
    /* Same exponent (hx==hy) but different lower word */
    printf("nextafter 1.0 1.0000000000000002 = %a\n", nextafter(1.0, 1.0000000000000002));
    printf("nextafter 1.0000000000000002 1.0 = %a\n", nextafter(1.0000000000000002, 1.0));
    /* nextafterd.c:115:17:true - lx==0 when decreasing positive x */
    printf("nextafter 2.0 1.0 = %a\n", nextafter(2.0, 1.0));
    printf("nextafter 4.0 3.0 = %a\n", nextafter(4.0, 3.0));
    /* Negative x decreasing (x > y) and increasing (x < y) */
    printf("nextafter -2.0 -3.0 = %a\n", nextafter(-2.0, -3.0));
    printf("nextafter -2.0 -1.0 = %a\n", nextafter(-2.0, -1.0));
    printf("nextafter -4.0 -3.0 = %a\n", nextafter(-4.0, -3.0));
    /* nextafterd.c:137:9:true - overflow: nextafter(MAX, inf) */
    printf("nextafter 0x1.fffffffffffffp1023 inf = %a\n",
           nextafter(0x1.fffffffffffffp1023, 1.0/0.0));
    printf("nextafter -0x1.fffffffffffffp1023 -inf = %a\n",
           nextafter(-0x1.fffffffffffffp1023, -1.0/0.0));
}

static void test_nextafterf_coverage2(void)
{
    /* nextafterf.c:27:13:true - x=+0, y=-0 */
    printf("nextafterf 0.0f -0.0f = %a\n", nextafterf(0.0f, -0.0f));
    printf("nextafterf -0.0f 0.0f = %a\n", nextafterf(-0.0f, 0.0f));
    /* same-value float pair */
    printf("nextafterf 2.0f 1.0f = %a\n", nextafterf(2.0f, 1.0f));
    printf("nextafterf 4.0f 3.0f = %a\n", nextafterf(4.0f, 3.0f));
    /* nextafterf.c:37:16:false - overflow */
    printf("nextafterf 0x1.fffffep127f inf = %a\n", nextafterf(0x1.fffffep127f, 1.0f/0.0f));
    printf("nextafterf -0x1.fffffep127f -inf = %a\n", nextafterf(-0x1.fffffep127f, -1.0f/0.0f));
    /* negative branches */
    printf("nextafterf -2.0f -3.0f = %a\n", nextafterf(-2.0f, -3.0f));
    printf("nextafterf -2.0f -1.0f = %a\n", nextafterf(-2.0f, -1.0f));
}

/* lround/llround: overflow and mid-range                             */
static void test_lround_coverage2(void)
{
    /* lroundd.c:93:16:false - exponent >= 63 (8*sizeof(long)-1): overflow */
    printf("lround 1e20 = %ld\n", lround(1e20));
    printf("lround -1e20 = %ld\n", lround(-1e20));
    /* lroundd.c:96:13:false - exponent in [20, 51] */
    printf("lround 2097152.5 = %ld\n", lround(2097152.5));
    printf("lround -2097152.5 = %ld\n", lround(-2097152.5));
    printf("lround 1048576.5 = %ld\n", lround(1048576.5));
    printf("lround 33554432.5 = %ld\n", lround(33554432.5));
    printf("lround -33554432.5 = %ld\n", lround(-33554432.5));
    printf("lround 4503599627370495.5 = %ld\n", lround(4503599627370495.5));
}

static void test_llround_coverage2(void)
{
    printf("llround 1e20 = %lld\n", llround(1e20));
    printf("llround -1e20 = %lld\n", llround(-1e20));
    printf("llround 2097152.5 = %lld\n", llround(2097152.5));
    printf("llround -2097152.5 = %lld\n", llround(-2097152.5));
    printf("llround 33554432.5 = %lld\n", llround(33554432.5));
    printf("llround 4503599627370495.5 = %lld\n", llround(4503599627370495.5));
}

static void test_lroundf_coverage2(void)
{
    /* lroundf.c:20:9:false - overflow */
    printf("lroundf 1e20f = %ld\n", lroundf(1e20f));
    printf("lroundf -1e20f = %ld\n", lroundf(-1e20f));
    /* lroundf.c:23:13:true - exponent >= 23 */
    printf("lroundf 8388608.5f = %ld\n", lroundf(8388608.5f));
    printf("lroundf -8388608.5f = %ld\n", lroundf(-8388608.5f));
    printf("lroundf 16777216.0f = %ld\n", lroundf(16777216.0f));
}

static void test_llroundf_coverage2(void)
{
    printf("llroundf 1e20f = %lld\n", llroundf(1e20f));
    printf("llroundf -1e20f = %lld\n", llroundf(-1e20f));
    printf("llroundf 8388608.5f = %lld\n", llroundf(8388608.5f));
    printf("llroundf -8388608.5f = %lld\n", llroundf(-8388608.5f));
}

/* lrint/llrint: overflow and mid-range                               */
static void test_lrint_coverage2(void)
{
    /* lrintd.c:111:16:false - exponent >= 63: overflow */
    printf("lrint 1e20 = %ld\n", lrint(1e20));
    printf("lrint -1e20 = %ld\n", lrint(-1e20));
    /* lrintd.c:114:13:false - exponent in [20, 51] */
    printf("lrint 2097152.5 = %ld\n", lrint(2097152.5));
    printf("lrint -2097152.5 = %ld\n", lrint(-2097152.5));
    printf("lrint 1048576.5 = %ld\n", lrint(1048576.5));
    printf("lrint 33554432.5 = %ld\n", lrint(33554432.5));
}

static void test_llrint_coverage2(void)
{
    printf("llrint 1e20 = %lld\n", llrint(1e20));
    printf("llrint -1e20 = %lld\n", llrint(-1e20));
    printf("llrint 2097152.5 = %lld\n", llrint(2097152.5));
    printf("llrint -2097152.5 = %lld\n", llrint(-2097152.5));
    printf("llrint 33554432.5 = %lld\n", llrint(33554432.5));
}

static void test_lrintf_coverage2(void)
{
    /* lrintf.c:43:9:false - overflow */
    printf("lrintf 1e20f = %ld\n", lrintf(1e20f));
    printf("lrintf -1e20f = %ld\n", lrintf(-1e20f));
    /* lrintf medium range */
    printf("lrintf 8388608.5f = %ld\n", lrintf(8388608.5f));
    printf("lrintf -8388608.5f = %ld\n", lrintf(-8388608.5f));
}

static void test_llrintf_coverage2(void)
{
    printf("llrintf 1e20f = %lld\n", llrintf(1e20f));
    printf("llrintf -1e20f = %lld\n", llrintf(-1e20f));
    printf("llrintf 8388608.5f = %lld\n", llrintf(8388608.5f));
    printf("llrintf -8388608.5f = %lld\n", llrintf(-8388608.5f));
}

/* remquof: equal values, subnormal y, large y                        */
static void test_remquof_coverage2(void)
{
    int quo;
    float r;
    /* remquof.c:44:9:false - hy > 0x7dffffff (y is very large finite) */
    r = remquof(1.0f, 1e38f, &quo);
    printf("remquof 1.0 1e38 = %a quo=%d\n", r, quo);
    r = remquof(5.0f, 1e38f, &quo);
    printf("remquof 5.0 1e38 = %a quo=%d\n", r, quo);
    /* remquof.c:48:9:true - x == y exactly */
    r = remquof(3.0f, 3.0f, &quo);
    printf("remquof 3.0 3.0 = %a quo=%d\n", r, quo);
    r = remquof(-3.0f, 3.0f, &quo);
    printf("remquof -3.0 3.0 = %a quo=%d\n", r, quo);
    r = remquof(3.0f, -3.0f, &quo);
    printf("remquof 3.0 -3.0 = %a quo=%d\n", r, quo);
    /* remquof.c:66:9:true - subnormal y: hy < 0x01000000 */
    r = remquof(2.0f, 0x1p-149f, &quo);
    printf("remquof 2.0 0x1p-149 = %a quo=%d\n", r, quo);
    /* Normal y, various quotient paths */
    r = remquof(1.5f, 1.0f, &quo);
    printf("remquof 1.5 1.0 = %a quo=%d\n", r, quo);
    r = remquof(2.5f, 2.0f, &quo);
    printf("remquof 2.5 2.0 = %a quo=%d\n", r, quo);
    r = remquof(-5.0f, 2.0f, &quo);
    printf("remquof -5.0 2.0 = %a quo=%d\n", r, quo);
}

/* fmod: subnormal x, subnormal y, equal values                       */
static void test_fmod_coverage2(void)
{
    /* fmodd.c:142:9:true - subnormal x with hx==0 (lx is significant) */
    printf("fmod 0x1p-1074 0x1p-1074 = %a\n", fmod(0x1p-1074, 0x1p-1074));
    printf("fmod 0x1p-1073 0x1p-1074 = %a\n", fmod(0x1p-1073, 0x1p-1074));
    /* fmodd.c:158:13:false - subnormal y with hy==0 */
    printf("fmod 1.0 0x1p-1074 = %a\n", fmod(1.0, 0x1p-1074));
    printf("fmod 3.0 0x1p-1074 = %a\n", fmod(3.0, 0x1p-1074));
    /* Both subnormal */
    printf("fmod 0x1p-1022 0x1p-1073 = %a\n", fmod(0x1p-1022, 0x1p-1073));
    /* Result is exactly zero */
    printf("fmod 5.0 5.0 = %a\n", fmod(5.0, 5.0));
    printf("fmod 7.0 7.0 = %a\n", fmod(7.0, 7.0));
    /* Large shift count needed */
    printf("fmod 1024.0 3.14159 = %a\n", fmod(1024.0, 3.14159));
    /* fmodd.c:191:13:true - subnormal output */
    printf("fmod 0x1p-1022 0x1p-1074 = %a\n", fmod(0x1p-1022, 0x1p-1074));
}

static void test_fmodf_coverage2(void)
{
    /* fmodf.c:32:37:true - subnormal x (ix < 0x00800000) */
    printf("fmodf 0x1p-149f 1.0f = %a\n", fmodf(0x1p-149f, 1.0f));
    printf("fmodf 0x1p-126f 0x1p-149f = %a\n", fmodf(0x1p-126f, 0x1p-149f));
    /* fmodf.c:58:40:true - subnormal y */
    printf("fmodf 1.0f 0x1p-149f = %a\n", fmodf(1.0f, 0x1p-149f));
    printf("fmodf 3.0f 0x1p-149f = %a\n", fmodf(3.0f, 0x1p-149f));
    /* fmodf.c:75:9:false - |x| <= |y| */
    printf("fmodf 0.5f 1.0f = %a\n", fmodf(0.5f, 1.0f));
    printf("fmodf 0.1f 1.0f = %a\n", fmodf(0.1f, 1.0f));
    /* fmodf.c:79:29:false - |x| == |y| exactly */
    printf("fmodf 3.0f 3.0f = %a\n", fmodf(3.0f, 3.0f));
    printf("fmodf 5.0f 5.0f = %a\n", fmodf(5.0f, 5.0f));
    /* Multiple quotient iterations */
    printf("fmodf 1024.0f 3.14159f = %a\n", fmodf(1024.0f, 3.14159f));
    /* Result zero */
    printf("fmodf 6.0f 3.0f = %a\n", fmodf(6.0f, 3.0f));
}

/* remainder: specific branching cases                                 */
static void test_remainder_coverage2(void)
{
    /* remainderd.c:118:31:true - |y| large, skip pre-reduction */
    printf("remainder 1.0 1e300 = %a\n", remainder(1.0, 1e300));
    printf("remainder 5.0 1e300 = %a\n", remainder(5.0, 1e300));
    /* remainderd.c:121:20:false - |x| != |y| */
    printf("remainder 3.0 2.0 = %a\n", remainder(3.0, 2.0));
    printf("remainder -3.0 2.0 = %a\n", remainder(-3.0, 2.0));
    /* remainderd.c:132:9:false - hx < hy */
    printf("remainder 0.5 3.0 = %a\n", remainder(0.5, 3.0));
    printf("remainder 0.1 1.0 = %a\n", remainder(0.1, 1.0));
    /* remainderd.c:144:13:true - halved y comparison cases */
    printf("remainder 1.5 1.0 = %a\n", remainder(1.5, 1.0));
    printf("remainder 2.5 2.0 = %a\n", remainder(2.5, 2.0));
    printf("remainder 3.5 3.0 = %a\n", remainder(3.5, 3.0));
    /* remainderd.c:157:17:false - x+x < y after adjustment */
    printf("remainder 7.0 4.0 = %a\n", remainder(7.0, 4.0));
    printf("remainder 5.0 3.0 = %a\n", remainder(5.0, 3.0));
    /* Subnormal y */
    printf("remainder 1.0 0x1p-1022 = %a\n", remainder(1.0, 0x1p-1022));
}

/* remquo: specific coverage                                          */
static void test_remquo_coverage2(void)
{
    int quo;
    double r;
    /* remquod.c:120:8:true - |y| large (hy > 0x7fbfffff) */
    r = remquo(1.0, 1e300, &quo);
    printf("remquo 1.0 1e300 = %a quo=%d\n", r, quo);
    /* remquod.c:133:31:true - x == y */
    r = remquo(3.0, 3.0, &quo);
    printf("remquo 3.0 3.0 = %a quo=%d\n", r, quo);
    r = remquo(-3.0, 3.0, &quo);
    printf("remquo -3.0 3.0 = %a quo=%d\n", r, quo);
    /* remquod.c:147:9:false - |x| < |y| */
    r = remquo(0.5, 3.0, &quo);
    printf("remquo 0.5 3.0 = %a quo=%d\n", r, quo);
    r = remquo(0.1, 1.0, &quo);
    printf("remquo 0.1 1.0 = %a quo=%d\n", r, quo);
    /* Various quotient values */
    r = remquo(1.5, 1.0, &quo);
    printf("remquo 1.5 1.0 = %a quo=%d\n", r, quo);
    r = remquo(2.5, 2.0, &quo);
    printf("remquo 2.5 2.0 = %a quo=%d\n", r, quo);
    r = remquo(5.5, 3.0, &quo);
    printf("remquo 5.5 3.0 = %a quo=%d\n", r, quo);
    r = remquo(-5.5, 3.0, &quo);
    printf("remquo -5.5 3.0 = %a quo=%d\n", r, quo);
    r = remquo(10.0, 3.0, &quo);
    printf("remquo 10.0 3.0 = %a quo=%d\n", r, quo);
}

/* remainderf coverage                                                */
static void test_remainderf_coverage2(void)
{
    /* remainderf.c:36:9:false - |y| large (no pre-reduction) */
    printf("remainderf 1.0f 1e38f = %a\n", remainderf(1.0f, 1e38f));
    printf("remainderf 5.0f 1e38f = %a\n", remainderf(5.0f, 1e38f));
    /* remainderf.c:40:9:true - |x| == |y| */
    printf("remainderf 3.0f 3.0f = %a\n", remainderf(3.0f, 3.0f));
    printf("remainderf -3.0f 3.0f = %a\n", remainderf(-3.0f, 3.0f));
    /* remainderf.c:47:9:true - subnormal y */
    printf("remainderf 1.0f 0x1p-149f = %a\n", remainderf(1.0f, 0x1p-149f));
    /* remainderf.c:48:13:true - x+x > y */
    printf("remainderf 1.5f 1.0f = %a\n", remainderf(1.5f, 1.0f));
    /* remainderf.c:51:17:true - second check */
    printf("remainderf 2.5f 2.0f = %a\n", remainderf(2.5f, 2.0f));
    printf("remainderf 3.0f 2.0f = %a\n", remainderf(3.0f, 2.0f));
    /* remainderf.c:61:17:false */
    printf("remainderf 7.0f 4.0f = %a\n", remainderf(7.0f, 4.0f));
    printf("remainderf 0.1f 1.0f = %a\n", remainderf(0.1f, 1.0f));
}

/* hypot with sNaN to hit inner Inf/NaN branches                      */
static void test_hypot_snan(void)
{
    uint64_t sbits = 0x7ff0000000000001ULL;
    double snan_d;
    __builtin_memcpy(&snan_d, &sbits, sizeof(snan_d));
    uint32_t sfbits = 0x7f800001U;
    float snan_f;
    __builtin_memcpy(&snan_f, &sfbits, sizeof(snan_f));
    /* hypotd.c:113:17:false - a has mantissa bits (sNaN with mantissa) */
    printf("hypot snan 1.0 = %a\n", hypot(snan_d, 1.0));
    /* hypotd.c:119:17:true - b is plain Inf */
    printf("hypot inf inf = %a\n", hypot(1.0/0.0, 1.0/0.0));
    printf("hypot inf -inf = %a\n", hypot(1.0/0.0, -1.0/0.0));
    /* hypotf.c:80:34:false/true */
    printf("hypotf snanf 1.0f = %a\n", hypotf(snan_f, 1.0f));
    printf("hypotf inff inff = %a\n", hypotf(1.0f/0.0f, 1.0f/0.0f));
    /* hypot large x that requires scaling */
    printf("hypot 1e200 0.0 = %a\n", hypot(1e200, 0.0));
    printf("hypot 1e-300 0.0 = %a\n", hypot(1e-300, 0.0));
}

/* ceil/floor/trunc/round with integral and carry-producing values    */
static void test_ceil_floor_extra(void)
{
    /* ceild.c:86:17:true - integral in [1, 2^20) */
    printf("ceil 3.0 = %a\n", ceil(3.0));
    printf("ceil 10.0 = %a\n", ceil(10.0));
    printf("ceil -3.0 = %a\n", ceil(-3.0));
    /* ceild.c:92:17:false - negative non-integral in [1, 2^20) */
    printf("ceil -1.5 = %a\n", ceil(-1.5));
    printf("ceil -2.9 = %a\n", ceil(-2.9));
    /* ceild.c:108:13:true - integral in [2^20, 2^52) */
    printf("ceil 1048576.0 = %a\n", ceil(1048576.0));
    printf("ceil -1048576.0 = %a\n", ceil(-1048576.0));
    /* ceild.c:114:17:true - _j0 == 20 exactly */
    printf("ceil 1048576.5 = %a\n", ceil(1048576.5));
    printf("ceil -1048576.5 = %a\n", ceil(-1048576.5));
    /* ceild.c:114:17:false - _j0 in (20, 51] */
    printf("ceil 2097152.5 = %a\n", ceil(2097152.5));
    printf("ceil -2097152.5 = %a\n", ceil(-2097152.5));
    /* floord extra */
    printf("floor 3.0 = %a\n", floor(3.0));
    printf("floor -3.0 = %a\n", floor(-3.0));
    printf("floor 1048576.0 = %a\n", floor(1048576.0));
    printf("floor -1048576.0 = %a\n", floor(-1048576.0));
    printf("floor 1048576.5 = %a\n", floor(1048576.5));
    printf("floor -1048576.5 = %a\n", floor(-1048576.5));
    /* truncd extra */
    printf("trunc 3.0 = %a\n", trunc(3.0));
    printf("trunc -3.0 = %a\n", trunc(-3.0));
    printf("trunc 1048576.5 = %a\n", trunc(1048576.5));
    printf("trunc -1048576.5 = %a\n", trunc(-1048576.5));
    printf("trunc 1048576.0 = %a\n", trunc(1048576.0));
    /* roundd extra */
    printf("round 3.0 = %a\n", round(3.0));
    printf("round 3.5 = %a\n", round(3.5));
    printf("round -3.5 = %a\n", round(-3.5));
    printf("round 1048576.5 = %a\n", round(1048576.5));
    printf("round -1048576.5 = %a\n", round(-1048576.5));
    printf("round 2097152.5 = %a\n", round(2097152.5));
}

/* ceilf/floorf/truncf/roundf/rintf extra                            */
static void test_ceilf_floorf_extra(void)
{
    /* ceilf.c:21:13:false - _j0 in [0, 23) not negative: integral */
    printf("ceilf 3.0f = %a\n", ceilf(3.0f));
    printf("ceilf -3.0f = %a\n", ceilf(-3.0f));
    printf("ceilf 1.5f = %a\n", ceilf(1.5f));
    printf("ceilf -1.5f = %a\n", ceilf(-1.5f));
    /* Large float boundary: 2^23 */
    printf("ceilf 8388608.0f = %a\n", ceilf(8388608.0f));
    printf("ceilf 8388608.5f = %a\n", ceilf(8388608.5f));
    printf("ceilf -8388608.5f = %a\n", ceilf(-8388608.5f));
    /* floorf extra */
    printf("floorf 3.0f = %a\n", floorf(3.0f));
    printf("floorf -3.0f = %a\n", floorf(-3.0f));
    printf("floorf 1.5f = %a\n", floorf(1.5f));
    printf("floorf -1.5f = %a\n", floorf(-1.5f));
    printf("floorf 8388608.0f = %a\n", floorf(8388608.0f));
    printf("floorf 8388608.5f = %a\n", floorf(8388608.5f));
    printf("floorf -8388608.5f = %a\n", floorf(-8388608.5f));
    /* truncf extra */
    printf("truncf 3.0f = %a\n", truncf(3.0f));
    printf("truncf -3.0f = %a\n", truncf(-3.0f));
    printf("truncf 1.5f = %a\n", truncf(1.5f));
    printf("truncf -1.5f = %a\n", truncf(-1.5f));
    printf("truncf 8388608.5f = %a\n", truncf(8388608.5f));
    printf("truncf 8388608.0f = %a\n", truncf(8388608.0f));
    /* roundf extra */
    printf("roundf 3.0f = %a\n", roundf(3.0f));
    printf("roundf 3.5f = %a\n", roundf(3.5f));
    printf("roundf -3.5f = %a\n", roundf(-3.5f));
    printf("roundf 8388608.5f = %a\n", roundf(8388608.5f));
    printf("roundf -8388608.5f = %a\n", roundf(-8388608.5f));
    /* rintf extra */
    printf("rintf 3.0f = %a\n", rintf(3.0f));
    printf("rintf -3.0f = %a\n", rintf(-3.0f));
    printf("rintf 1.5f = %a\n", rintf(1.5f));
    printf("rintf -1.5f = %a\n", rintf(-1.5f));
    printf("rintf 8388608.5f = %a\n", rintf(8388608.5f));
}

/* log coverage: various ranges                                       */
static void test_log_coverage3(void)
{
    /* logd.c:127:13:false - exact power of 2 */
    printf("log 4.0 = %a\n", log(4.0));
    printf("log 8.0 = %a\n", log(8.0));
    printf("log 0.25 = %a\n", log(0.25));
    /* logd.c:149:13:true - k != 0 (non-zero exponent) */
    printf("log 3.0 = %a\n", log(3.0));
    printf("log 7.0 = %a\n", log(7.0));
    /* log10d extra */
    printf("log10 0x1p-1022 = %a\n", log10(0x1p-1022));
    printf("log10 4.0 = %a\n", log10(4.0));
    /* log2d extra */
    printf("log2 0x1p-1022 = %a\n", log2(0x1p-1022));
    printf("log2 4.0 = %a\n", log2(4.0));
    /* log1pd.c:173:23:true and 166:17:false */
    printf("log1p 2.0 = %a\n", log1p(2.0));
    printf("log1p 10.0 = %a\n", log1p(10.0));
    printf("log1p -0.9999 = %a\n", log1p(-0.9999));
    printf("log1p 0.001 = %a\n", log1p(0.001));
    /* logf extra */
    printf("logf 4.0f = %a\n", logf(4.0f));
    printf("logf 3.0f = %a\n", logf(3.0f));
    printf("logf 0.25f = %a\n", logf(0.25f));
    /* log1pf extra */
    printf("log1pf 2.0f = %a\n", log1pf(2.0f));
    printf("log1pf 10.0f = %a\n", log1pf(10.0f));
    printf("log1pf -0.9f = %a\n", log1pf(-0.9f));
    printf("log1pf 0.001f = %a\n", log1pf(0.001f));
    /* log10f extra */
    printf("log10f 100.0f = %a\n", log10f(100.0f));
    printf("log10f 0.01f = %a\n", log10f(0.01f));
    /* log2f extra */
    printf("log2f 4.0f = %a\n", log2f(4.0f));
    printf("log2f 0.25f = %a\n", log2f(0.25f));
}

/* trig extra: more rem_pio2 paths and quadrants                      */
static void test_trig_coverage3(void)
{
    printf("sin 3.0 = %a\n", sin(3.0));
    printf("sin 5.0 = %a\n", sin(5.0));
    printf("sin 6.0 = %a\n", sin(6.0));
    printf("sin 7.0 = %a\n", sin(7.0));
    printf("cos 3.0 = %a\n", cos(3.0));
    printf("cos 5.0 = %a\n", cos(5.0));
    printf("cos 6.0 = %a\n", cos(6.0));
    printf("tan 3.0 = %a\n", tan(3.0));
    printf("tan 4.0 = %a\n", tan(4.0));
    printf("sin 1e7 = %a\n", sin(1e7));
    printf("cos 1e7 = %a\n", cos(1e7));
    printf("sin 1e8 = %a\n", sin(1e8));
    printf("cos 1e8 = %a\n", cos(1e8));
    printf("tan 1e7 = %a\n", tan(1e7));
    printf("sinf 3.0f = %a\n", sinf(3.0f));
    printf("sinf 5.0f = %a\n", sinf(5.0f));
    printf("cosf 3.0f = %a\n", cosf(3.0f));
    printf("cosf 5.0f = %a\n", cosf(5.0f));
    printf("tanf 3.0f = %a\n", tanf(3.0f));
    printf("tanf 4.0f = %a\n", tanf(4.0f));
    printf("sinf 1e7f = %a\n", sinf(1e7f));
    printf("cosf 1e7f = %a\n", cosf(1e7f));
    printf("tanf 1e7f = %a\n", tanf(1e7f));
}

/* Additional gamma ranges                                            */
static void test_gamma_coverage2(void)
{
    /* gammad.c:287:12:true - x in [2, 8) various integer steps */
    printf("lgamma 3.0 = %a\n", lgamma(3.0));
    printf("lgamma 4.0 = %a\n", lgamma(4.0));
    printf("lgamma 5.0 = %a\n", lgamma(5.0));
    printf("lgamma 6.0 = %a\n", lgamma(6.0));
    printf("lgamma 7.0 = %a\n", lgamma(7.0));
    printf("lgamma 8.0 = %a\n", lgamma(8.0));
    /* gammad.c:357:9:true - x very large */
    printf("lgamma 30.0 = %a\n", lgamma(30.0));
    printf("lgamma 100.0 = %a\n", lgamma(100.0));
    printf("lgamma 1000.0 = %a\n", lgamma(1000.0));
    /* gammad.c:411:16:false - nadj factor */
    printf("lgamma -3.5 = %a\n", lgamma(-3.5));
    printf("lgamma -5.5 = %a\n", lgamma(-5.5));
    /* gammaf */
    printf("lgammaf 3.0f = %a\n", lgammaf(3.0f));
    printf("lgammaf 4.0f = %a\n", lgammaf(4.0f));
    printf("lgammaf 5.0f = %a\n", lgammaf(5.0f));
    printf("lgammaf 30.0f = %a\n", lgammaf(30.0f));
    printf("lgammaf -3.5f = %a\n", lgammaf(-3.5f));
}

/* ilogb extra coverage                                               */
static void test_ilogb_coverage2(void)
{
    /* ilogbd.c:96:17:false - subnormal x, ix != 0 (upper word has bits) */
    printf("ilogb 0x1p-1023 = %d\n", ilogb(0x1p-1023));
    printf("ilogb 0x1p-1022 = %d\n", ilogb(0x1p-1022));
    /* ilogbd.c:101:45:false/true - subnormal iteration */
    printf("ilogb 0x1p-1073 = %d\n", ilogb(0x1p-1073));
    printf("ilogb 0x1p-1074 = %d\n", ilogb(0x1p-1074));
}

/* Bessel extra coverage                                              */
static void test_bessel_coverage2(void)
{
    /* j0d.c:100:13:false - |x| < 2^-13 (tiny) */
    printf("j0 1e-5 = %a\n", j0(1e-5));
    printf("j0 1e-10 = %a\n", j0(1e-10));
    /* j0d.c:114:13:true - |x| in [3, 5) */
    printf("j0 4.0 = %a\n", j0(4.0));
    printf("j0 4.5 = %a\n", j0(4.5));
    /* j0d.c:126:13:true - |x| in [5, ...) */
    printf("j0 5.5 = %a\n", j0(5.5));
    printf("j0 6.0 = %a\n", j0(6.0));
    /* j0d.c:129:13:false - |x| >= large value */
    printf("j0 50.0 = %a\n", j0(50.0));
    /* j1d.c:101:13:false - tiny x */
    printf("j1 1e-10 = %a\n", j1(1e-10));
    /* j1d.c:115:13:true - specific range */
    printf("j1 4.0 = %a\n", j1(4.0));
    printf("j1 5.5 = %a\n", j1(5.5));
    /* ynd extra */
    printf("yn 1 2.0 = %a\n", yn(1, 2.0));
    printf("yn 2 5.0 = %a\n", yn(2, 5.0));
    printf("yn 5 1.0 = %a\n", yn(5, 1.0));
    printf("yn 2 0.1 = %a\n", yn(2, 0.1));
}

/* logb extra coverage                                                */
static void test_logb_coverage2(void)
{
    /* logbd.c:75:17:false - normal x */
    printf("logb -2.0 = %a\n", logb(-2.0));
    printf("logb -0.5 = %a\n", logb(-0.5));
    printf("logb 0.25 = %a\n", logb(0.25));
    /* logbd.c:80:45:false - subnormal upper word nonzero */
    printf("logb 0x1p-1023 = %a\n", logb(0x1p-1023));
    /* logbd.c:80:45:true - subnormal upper word zero */
    printf("logb 0x1p-1073 = %a\n", logb(0x1p-1073));
}

/* acosh/atanh extra coverage                                         */
static void test_acoshd_atanhd_extra(void)
{
    /* acoshd.c:87:16:true - x in (1, 2]: uses log1p path */
    printf("acosh 1.1 = %a\n", acosh(1.1));
    printf("acosh 1.5 = %a\n", acosh(1.5));
    printf("acosh 1.9 = %a\n", acosh(1.9));
    /* acoshd.c:325:29:true - large x overflow */
    printf("acosh 1e300 = %a\n", acosh(1e300));
    /* atanhd extra */
    printf("atanh 0.1 = %a\n", atanh(0.1));
    printf("atanh -0.1 = %a\n", atanh(-0.1));
    printf("atanh 0.999 = %a\n", atanh(0.999));
    printf("atanh -0.999 = %a\n", atanh(-0.999));
}

/* float-specific uncovered areas                                     */
static void test_float_coverage3(void)
{
    /* erfcf.c:73:27:false - x in [2.857, 6) */
    printf("erfcf 3.5f = %a\n", erfcf(3.5f));
    printf("erfcf 4.0f = %a\n", erfcf(4.0f));
    /* tgammaf extra */
    printf("tgammaf 0.5f = %a\n", tgammaf(0.5f));
    printf("tgammaf 1.5f = %a\n", tgammaf(1.5f));
    printf("tgammaf -0.5f = %a\n", tgammaf(-0.5f));
    printf("tgammaf 3.5f = %a\n", tgammaf(3.5f));
    /* atanhf negative path */
    printf("atanhf -0.5f = %a\n", atanhf(-0.5f));
    printf("atanhf -0.9f = %a\n", atanhf(-0.9f));
    /* tanhf.c:26:20:false - |x| >= 9 */
    printf("tanhf 15.0f = %a\n", tanhf(15.0f));
    printf("tanhf -15.0f = %a\n", tanhf(-15.0f));
    /* coshf/sinhf extra: medium range */
    printf("coshf 5.0f = %a\n", coshf(5.0f));
    printf("coshf 20.0f = %a\n", coshf(20.0f));
    printf("sinhf 5.0f = %a\n", sinhf(5.0f));
    printf("sinhf 20.0f = %a\n", sinhf(20.0f));
    printf("sinhf 30.0f = %a\n", sinhf(30.0f));
    printf("sinhf -30.0f = %a\n", sinhf(-30.0f));
    /* acoshf: large x */
    printf("acoshf 1e38f = %a\n", acoshf(1e38f));
    /* expm1f extra */
    printf("expm1f 0.5f = %a\n", expm1f(0.5f));
    printf("expm1f -0.5f = %a\n", expm1f(-0.5f));
    printf("expm1f 30.0f = %a\n", expm1f(30.0f));
    printf("expm1f 0.1f = %a\n", expm1f(0.1f));
    printf("expm1f 2.0f = %a\n", expm1f(2.0f));
    /* cbrtf extra */
    printf("cbrtf 0.5f = %a\n", cbrtf(0.5f));
    printf("cbrtf 2.0f = %a\n", cbrtf(2.0f));
    /* powf extra */
    printf("powf 3.0f 3.0f = %a\n", powf(3.0f, 3.0f));
    printf("powf -3.0f 2.0f = %a\n", powf(-3.0f, 2.0f));
    printf("powf -3.0f 3.0f = %a\n", powf(-3.0f, 3.0f));
    printf("powf -2.0f -4.0f = %a\n", powf(-2.0f, -4.0f));
    printf("powf 0.0f -3.0f = %a\n", powf(0.0f, -3.0f));
    printf("powf -0.0f -3.0f = %a\n", powf(-0.0f, -3.0f));
    printf("powf 0.1f 200.0f = %a\n", powf(0.1f, 200.0f));
    /* sqrtf extra */
    printf("sqrtf 0x1p-149f = %a\n", sqrtf(0x1p-149f));
    printf("sqrtf 0x1p-126f = %a\n", sqrtf(0x1p-126f));
    /* atan2f extra */
    printf("atan2f 0.5f 2.0f = %a\n", atan2f(0.5f, 2.0f));
    printf("atan2f 1000.0f 1.0f = %a\n", atan2f(1000.0f, 1.0f));
    /* frexpf extra */
    { int e; float fv = frexpf(0x1p-149f, &e); printf("frexpf 0x1p-149f = %a exp=%d\n", fv, e); }
    /* logbf extra */
    printf("logbf 0x1p-149f = %a\n", logbf(0x1p-149f));
    printf("logbf 0x1p-126f = %a\n", logbf(0x1p-126f));
    printf("logbf -2.0f = %a\n", logbf(-2.0f));
}

/* ------------------------------------------------------------------ */
/* Coverage round 6: targeted branches still uncovered after round 5  */
/* ------------------------------------------------------------------ */

/* ceil/floor/trunc: edge cases not yet covered */
static void test_ceil_round6(void)
{
    /* ceild.c:70:17:true — j0<0, x==0 (ceil(+0.0)) */
    printf("ceil 0.0 = %a\n", ceil(0.0));
    /* ceild.c:70:17:false, 76:17:false — j0<0, x > 0 */
    printf("ceil 0.3 = %a\n", ceil(0.3));
    printf("ceil 0.9 = %a\n", ceil(0.9));
    /* ceild.c:76:17:true — j0<0, x < 0 */
    printf("ceil -0.3 = %a\n", ceil(-0.3));
    printf("ceil -0.9 = %a\n", ceil(-0.9));
    /* ceild.c:86:17:true — j0 in [0,19], integral */
    printf("ceil 4.0 = %a\n", ceil(4.0));
    printf("ceil 5.0 = %a\n", ceil(5.0));
    /* ceild.c:86:17:false — non-integral in [0,19] */
    printf("ceil 4.5 = %a\n", ceil(4.5));
    /* ceild.c:92:17:true — positive non-integral in [0,19] */
    printf("ceil 5.2 = %a\n", ceil(5.2));
    /* ceild.c:92:17:false — negative non-integral in [0,19] */
    printf("ceil -4.2 = %a\n", ceil(-4.2));
    /* ceild.c:99:16:false — j0 in [20,51] */
    printf("ceil 2097152.25 = %a\n", ceil(2097152.25));
    /* ceild.c:100:13:false — j0 > 51, finite integral */
    printf("ceil 9007199254740992.0 = %a\n", ceil(9007199254740992.0));
    printf("ceil 1e18 = %a\n", ceil(1e18));
    /* ceild.c:108:13:true — integral in j0 [20,51] */
    printf("ceil 2097153.0 = %a\n", ceil(2097153.0));
    printf("ceil -2097153.0 = %a\n", ceil(-2097153.0));
    /* ceild.c:108:13:false, 113:13:true — positive non-integral in j0 [20,51] */
    printf("ceil 2097153.5 = %a\n", ceil(2097153.5));
    /* ceild.c:113:13:false — negative non-integral in j0 [20,51] */
    printf("ceil -2097153.5 = %a\n", ceil(-2097153.5));
    /* ceild.c:119:21:true — carry in j0 > 20 round-up */
    /* 2^21*(1+1/2^21+1/2^22) has _i1=0xC0000000; +0x80000000 overflows */
    { double v; uint64_t b = (0x41400001ULL << 32) | 0xC0000000ULL;
      __builtin_memcpy(&v, &b, 8);
      printf("ceil carry_test = %a\n", ceil(v)); }
    /* ceild.c:119:21:false — no carry */
    printf("ceil 4194304.25 = %a\n", ceil(4194304.25));
}

static void test_floor_round6(void)
{
    /* floord.c:70:17:true — j0<0, x==0 */
    printf("floor 0.0 = %a\n", floor(0.0));
    printf("floor -0.0 = %a\n", floor(-0.0));
    /* j0<0 positive/negative */
    printf("floor 0.3 = %a\n", floor(0.3));
    printf("floor -0.3 = %a\n", floor(-0.3));
    printf("floor 0.9 = %a\n", floor(0.9));
    printf("floor -0.9 = %a\n", floor(-0.9));
    /* floord.c:107:13:true — integral in j0 [20,51] */
    printf("floor 2097153.0 = %a\n", floor(2097153.0));
    printf("floor -2097153.0 = %a\n", floor(-2097153.0));
    /* floord.c:113:13:true — negative non-integral in j0 [20,51] */
    printf("floor -2097153.5 = %a\n", floor(-2097153.5));
    /* floord.c:114:17:false — j0 != 20 */
    printf("floor -4194304.5 = %a\n", floor(-4194304.5));
    printf("floor 2097153.5 = %a\n", floor(2097153.5));
    /* carry case for floor */
    { double v; uint64_t b = (0xC1400001ULL << 32) | 0xC0000000ULL;
      __builtin_memcpy(&v, &b, 8);
      printf("floor carry_neg = %a\n", floor(v)); }
    /* large integral */
    printf("floor 1e18 = %a\n", floor(1e18));
}

static void test_trunc_round6(void)
{
    /* truncd.c:79:13:true — |x| < 1, result +-0 */
    printf("trunc 0.5 = %a\n", trunc(0.5));
    printf("trunc -0.5 = %a\n", trunc(-0.5));
    printf("trunc 0.99 = %a\n", trunc(0.99));
    printf("trunc -0.99 = %a\n", trunc(-0.99));
    /* truncd.c:79:13:false — exponent in [0,19] */
    printf("trunc 1.5 = %a\n", trunc(1.5));
    printf("trunc -2.7 = %a\n", trunc(-2.7));
    /* truncd.c:86:16:false — exponent in [20,51] */
    printf("trunc 2097152.75 = %a\n", trunc(2097152.75));
    printf("trunc -2097152.75 = %a\n", trunc(-2097152.75));
    /* truncd.c:87:13:false — exponent > 51, finite, integral */
    printf("trunc 1e18 = %a\n", trunc(1e18));
    printf("trunc -1e18 = %a\n", trunc(-1e18));
    printf("trunc 9007199254740993.0 = %a\n", trunc(9007199254740993.0));
}

/* rint/round: additional branch coverage */
static void test_rint_round6(void)
{
    /* rintd.c:93:17:true — integral x in j0 [0,19], early return */
    printf("rint 2.0 = %a\n", rint(2.0));
    printf("rint 3.0 = %a\n", rint(3.0));
    printf("rint -2.0 = %a\n", rint(-2.0));
    /* rintd.c:101:21:true — j0==19, secondary fraction bit set */
    printf("rint 524288.5 = %a\n", rint(524288.5));
    printf("rint 524288.25 = %a\n", rint(524288.25));
    /* rintd.c:119:13:true — non-integral lower word, j0 in [20,51] */
    printf("rint 2097152.25 = %a\n", rint(2097152.25));
    printf("rint 2097152.75 = %a\n", rint(2097152.75));
    printf("rint -2097152.25 = %a\n", rint(-2097152.25));
    /* rintd.c:125:13:true — rounding bit set in lower word */
    printf("rint 4503599627370494.5 = %a\n", rint(4503599627370494.5));
    /* roundd.c:85:47:false — msw fraction==0, lsw != 0 */
    printf("round 1.0000000000000002 = %a\n", round(1.0000000000000002));
    printf("round -1.0000000000000002 = %a\n", round(-1.0000000000000002));
    /* roundd.c:103:13:true — lsw integral in j0>=20 */
    printf("round 2097153.0 = %a\n", round(2097153.0));
    printf("round -2097153.0 = %a\n", round(-2097153.0));
    /* round in j0>=20 non-integral */
    printf("round 2097153.5 = %a\n", round(2097153.5));
    printf("round -2097153.5 = %a\n", round(-2097153.5));
}

/* exp: underflow region between o_threshold and u_threshold */
static void test_exp_round6(void)
{
    /* expd.c:117:13:false — x in [-745.13, -709.78], NOT < u_threshold */
    printf("exp -710.0 = %a\n", exp(-710.0));
    printf("exp -720.0 = %a\n", exp(-720.0));
    printf("exp -740.0 = %a\n", exp(-740.0));
    /* expd.c:156:9:false — k < -1021 (subnormal result path) */
    printf("exp -744.0 = %a\n", exp(-744.0));
}

/* sinh/cosh: exact bit-pattern threshold values */
static void test_sinh_cosh_round6(void)
{
    /* sinhd.c:113:29:true — ix in [0x40862E42, 0x408633CE) */
    printf("sinh 710.0 = %a\n", sinh(710.0));
    printf("sinh 710.4 = %a\n", sinh(710.4));
    /* sinhd.c:113:49:true — ix==0x408633CE, lx <= 0x8fb9f87d */
    { double v; uint64_t b = (0x408633CEULL << 32) | 0x8fb9f87dULL;
      __builtin_memcpy(&v, &b, 8);
      printf("sinh thresh_exact = %a\n", sinh(v));
      printf("sinh -thresh_exact = %a\n", sinh(-v)); }
    /* sinhd.c:113:49:false — ix==0x408633CE, lx > 0x8fb9f87d → overflow */
    { double v; uint64_t b = (0x408633CEULL << 32) | 0x8fb9f87eULL;
      __builtin_memcpy(&v, &b, 8);
      printf("sinh thresh_over = %a\n", sinh(v)); }
    /* coshd.c:104:10:true — ix==0x408633CE */
    { double v; uint64_t b = (0x408633CEULL << 32) | 0x8fb9f87dULL;
      __builtin_memcpy(&v, &b, 8);
      printf("cosh thresh_exact = %a\n", cosh(v)); }
    /* coshd.c:104:30:false — ix==0x408633CE, lx > 0x8fb9f87d */
    { double v; uint64_t b = (0x408633CEULL << 32) | 0x8fb9f87eULL;
      __builtin_memcpy(&v, &b, 8);
      printf("cosh thresh_over = %a\n", cosh(v)); }
    /* cosh in [709.78, 710.47) range */
    printf("cosh 710.0 = %a\n", cosh(710.0));
}

/* lgamma: additional ranges */
static void test_lgamma_round6(void)
{
    /* gammad.c:287:12:true — x == -0.0 */
    printf("lgamma -0.0 = %a\n", lgamma(-0.0));
    /* gammad.c:357:9:true — case 0 in switch: x in [1.7316, 2) */
    printf("lgamma 1.8 = %a\n", lgamma(1.8));
    printf("lgamma 1.9 = %a\n", lgamma(1.9));
    printf("lgamma 1.95 = %a\n", lgamma(1.95));
    /* case 0 in first sub-branch: x near 0.94 */
    printf("lgamma 0.94 = %a\n", lgamma(0.94));
    printf("lgamma 0.97 = %a\n", lgamma(0.97));
    /* gammad.c:411:16:false — x >= 2^58 */
    printf("lgamma 1e18 = %a\n", lgamma(1e18));
    printf("lgamma 1e20 = %a\n", lgamma(1e20));
    /* negative lgamma cases */
    printf("lgamma -0.5 = %a\n", lgamma(-0.5));
    printf("lgamma -1.5 = %a\n", lgamma(-1.5));
    /* tgamma large x */
    printf("tgamma 1.8 = %a\n", tgamma(1.8));
    printf("tgamma 1.9 = %a\n", tgamma(1.9));
}

/* Bessel: y1(tiny), yn(large x) */
static void test_bessel_round6(void)
{
    /* y1d.c:150:9:true — x < 2^-54 */
    printf("y1 1e-20 = %a\n", y1(1e-20));
    printf("y1 1e-17 = %a\n", y1(1e-17));
    /* ynd.c:141:9:true — x > 2^302, case 0 (n&3==0) */
    printf("yn 0 1e91 = %a\n", yn(0, 1e91));
    printf("yn 4 1e91 = %a\n", yn(4, 1e91));
    /* ynd.c: case 1 (n&3==1) */
    printf("yn 1 1e91 = %a\n", yn(1, 1e91));
    /* ynd.c: case 2, 3 */
    printf("yn 2 1e91 = %a\n", yn(2, 1e91));
    printf("yn 3 1e91 = %a\n", yn(3, 1e91));
    /* ynd.c:167:30:false — b becomes -inf during recurrence */
    printf("yn 50 0.01 = %a\n", yn(50, 0.01));
    /* j0/j1 extra ranges */
    printf("j0 1e-5 = %a\n", j0(1e-5));
    printf("j1 1e-5 = %a\n", j1(1e-5));
    printf("j0 4.5 = %a\n", j0(4.5));
    printf("j1 4.5 = %a\n", j1(4.5));
}

/* scalbn: extreme underflow for subnormal input */
static void test_scalbn_round6(void)
{
    /* scalbnd.c:105:13:true — k==0 (subnormal), n < -50000 */
    printf("scalbn 0x1p-1074 -100000 = %a\n", scalbn(0x1p-1074, -100000));
    printf("scalbn 0x1p-1074 -50001 = %a\n", scalbn(0x1p-1074, -50001));
    printf("scalbln 0x1p-1074 -100000 = %a\n", scalbln(0x1p-1074, -100000));
}

/* atan2: extra edge-case paths */
static void test_atan2_round6(void)
{
    /* atan2d.c:107:29:false — hx != 0x3ff00000 (x != 1.0) */
    printf("atan2 1.0 2.0 = %a\n", atan2(1.0, 2.0));
    /* atan2d.c:116:9:true — y==0, m==0 (x>0, y=+0) */
    printf("atan2 0.0 1.0 = %a\n", atan2(0.0, 1.0));
    /* atan2d.c:118:9:true — y==0, case 2 (x<0, y=+0) → pi */
    printf("atan2 0.0 -1.0 = %a\n", atan2(0.0, -1.0));
    /* atan2d.c:138:13:true — x inf, y inf */
    printf("atan2 inf inf = %a\n", atan2(1.0/0.0, 1.0/0.0));
    printf("atan2 inf -inf = %a\n", atan2(1.0/0.0, -1.0/0.0));
    /* atan2d.c:153:13:true — x inf, y finite */
    printf("atan2 1.0 inf = %a\n", atan2(1.0, 1.0/0.0));
    printf("atan2 -1.0 inf = %a\n", atan2(-1.0, 1.0/0.0));
    /* atan2d.c:157:13:true — x inf, case 2,3 */
    printf("atan2 1.0 -inf = %a\n", atan2(1.0, -1.0/0.0));
    printf("atan2 -1.0 -inf = %a\n", atan2(-1.0, -1.0/0.0));
    /* atan2d.c:177:9:true — |y/x| > 2^60 */
    printf("atan2 1e18 1.0 = %a\n", atan2(1e18, 1.0));
    printf("atan2 -1e18 1.0 = %a\n", atan2(-1e18, 1.0));
}

/* Float-precision extra coverage */
static void test_float_round6(void)
{
    /* ceilf: all main paths */
    printf("ceilf 0.0f = %a\n", ceilf(0.0f));
    printf("ceilf 0.5f = %a\n", ceilf(0.5f));
    printf("ceilf -0.5f = %a\n", ceilf(-0.5f));
    printf("ceilf 0.1f = %a\n", ceilf(0.1f));
    printf("ceilf -0.1f = %a\n", ceilf(-0.1f));
    printf("ceilf 1.5f = %a\n", ceilf(1.5f));
    printf("ceilf -1.5f = %a\n", ceilf(-1.5f));
    printf("ceilf 2.0f = %a\n", ceilf(2.0f));
    printf("ceilf 16777216.0f = %a\n", ceilf(16777216.0f));
    printf("ceilf 16777217.0f = %a\n", ceilf(16777217.0f));
    /* floorf: all main paths */
    printf("floorf 0.0f = %a\n", floorf(0.0f));
    printf("floorf 0.5f = %a\n", floorf(0.5f));
    printf("floorf -0.5f = %a\n", floorf(-0.5f));
    printf("floorf 1.5f = %a\n", floorf(1.5f));
    printf("floorf -1.5f = %a\n", floorf(-1.5f));
    printf("floorf 2.0f = %a\n", floorf(2.0f));
    printf("floorf -2.5f = %a\n", floorf(-2.5f));
    printf("floorf 16777216.0f = %a\n", floorf(16777216.0f));
    printf("floorf -16777217.5f = %a\n", floorf(-16777217.5f));
    /* truncf: all main paths */
    printf("truncf 0.5f = %a\n", truncf(0.5f));
    printf("truncf -0.5f = %a\n", truncf(-0.5f));
    printf("truncf 1.5f = %a\n", truncf(1.5f));
    printf("truncf -1.5f = %a\n", truncf(-1.5f));
    printf("truncf 16777217.5f = %a\n", truncf(16777217.5f));
    printf("truncf 1e18f = %a\n", truncf(1e18f));
    /* sinhf near overflow */
    printf("sinhf 88.0f = %a\n", sinhf(88.0f));
    printf("sinhf 89.0f = %a\n", sinhf(89.0f));
    printf("sinhf 90.0f = %a\n", sinhf(90.0f));
    /* coshf near overflow */
    printf("coshf 88.0f = %a\n", coshf(88.0f));
    printf("coshf 89.0f = %a\n", coshf(89.0f));
    /* tanhf near 1 */
    printf("tanhf 0.1f = %a\n", tanhf(0.1f));
    printf("tanhf 10.0f = %a\n", tanhf(10.0f));
    printf("tanhf 20.0f = %a\n", tanhf(20.0f));
    /* lgammaf extra */
    printf("lgammaf 1.8f = %a\n", lgammaf(1.8f));
    printf("lgammaf 0.97f = %a\n", lgammaf(0.97f));
    printf("lgammaf -0.0f = %a\n", lgammaf(-0.0f));
    printf("lgammaf 1e18f = %a\n", lgammaf(1e18f));
    /* expf extra */
    printf("expf -87.5f = %a\n", expf(-87.5f));
    printf("expf -90.0f = %a\n", expf(-90.0f));
    /* expm1f extra */
    printf("expm1f 1.0f = %a\n", expm1f(1.0f));
    printf("expm1f 88.0f = %a\n", expm1f(88.0f));
    printf("expm1f 0.0001f = %a\n", expm1f(0.0001f));
    printf("expm1f -0.0001f = %a\n", expm1f(-0.0001f));
    /* log1pf extra */
    printf("log1pf 1.5f = %a\n", log1pf(1.5f));
    printf("log1pf 0.0001f = %a\n", log1pf(0.0001f));
    printf("log1pf -0.5f = %a\n", log1pf(-0.5f));
    /* logf extra */
    printf("logf 0.5f = %a\n", logf(0.5f));
    printf("logf 2.0f = %a\n", logf(2.0f));
    /* powf extra */
    printf("powf 2.0f 3.0f = %a\n", powf(2.0f, 3.0f));
    printf("powf -1.0f 3.0f = %a\n", powf(-1.0f, 3.0f));
    printf("powf 0.5f -1.0f = %a\n", powf(0.5f, -1.0f));
    /* modff extra */
    printf("modff 0.5f = %a\n", modff(0.5f, &(float){0}));
    printf("modff 1.5f = %a\n", modff(1.5f, &(float){0}));
    /* fmodf extra */
    printf("fmodf 3.5f 1.5f = %a\n", fmodf(3.5f, 1.5f));
    printf("fmodf -3.5f 1.5f = %a\n", fmodf(-3.5f, 1.5f));
    /* remainderf extra */
    printf("remainderf 3.5f 1.5f = %a\n", remainderf(3.5f, 1.5f));
    /* scalbnf extra */
    printf("scalbnf 0x1p-149f -100000 = %a\n", scalbnf(0x1p-149f, -100000));
    printf("scalbnf 1.0f 200 = %a\n", scalbnf(1.0f, 200));
    /* scalblnf extra */
    printf("scalblnf 1.0f 200 = %a\n", scalblnf(1.0f, 200));
    printf("scalblnf 0x1p-149f -100000 = %a\n", scalblnf(0x1p-149f, -100000));
    /* atan2f extra */
    printf("atan2f 0.0f 1.0f = %a\n", atan2f(0.0f, 1.0f));
    printf("atan2f 0.0f -1.0f = %a\n", atan2f(0.0f, -1.0f));
    printf("atan2f 1e10f 1.0f = %a\n", atan2f(1e10f, 1.0f));
    printf("atan2f 1.0f 1e-10f = %a\n", atan2f(1.0f, 1e-10f));
    printf("atan2f 1.0f 0.0f = %a\n", atan2f(1.0f, 0.0f));
    printf("atan2f 1.0f -0.0f = %a\n", atan2f(1.0f, -0.0f));
    /* cbrtf extra */
    printf("cbrtf 0.0f = %a\n", cbrtf(0.0f));
    printf("cbrtf -8.0f = %a\n", cbrtf(-8.0f));
    printf("cbrtf 0x1p-126f = %a\n", cbrtf(0x1p-126f));
    /* hypotf extra */
    printf("hypotf 0.0f 0.0f = %a\n", hypotf(0.0f, 0.0f));
    printf("hypotf 1e-20f 0.0f = %a\n", hypotf(1e-20f, 0.0f));
    /* frexpf extra */
    printf("frexpf 0.0f = %a\n", frexpf(0.0f, &(int){0}));
    printf("frexpf 1.5f = %a\n", frexpf(1.5f, &(int){0}));
    /* nextafterf extra */
    printf("nextafterf 1.0f 2.0f = %a\n", nextafterf(1.0f, 2.0f));
    printf("nextafterf 0x1p-149f 0.0f = %a\n", nextafterf(0x1p-149f, 0.0f));
    /* remquof extra */
    printf("remquof 3.5f 1.5f = %a\n", remquof(3.5f, 1.5f, &(int){0}));
    printf("remquof -3.5f 1.5f = %a\n", remquof(-3.5f, 1.5f, &(int){0}));
    /* fmaxf/fminf extra */
    printf("fmaxf 1.0f nan = %a\n", fmaxf(1.0f, 0.0f/0.0f));
    printf("fmaxf nan 1.0f = %a\n", fmaxf(0.0f/0.0f, 1.0f));
    printf("fminf 1.0f nan = %a\n", fminf(1.0f, 0.0f/0.0f));
    printf("fminf nan 1.0f = %a\n", fminf(0.0f/0.0f, 1.0f));
    /* lrintf/llrintf */
    printf("lrintf 0.5f = %ld\n", lrintf(0.5f));
    printf("lrintf 1e9f = %ld\n", lrintf(1e9f));
    printf("llrintf 0.5f = %lld\n", llrintf(0.5f));
    printf("llrintf 1e9f = %lld\n", llrintf(1e9f));
    /* fmax/fmin double extra */
    printf("fmax 1.0 nan = %a\n", fmax(1.0, 0.0/0.0));
    printf("fmax nan 1.0 = %a\n", fmax(0.0/0.0, 1.0));
    printf("fmin 1.0 nan = %a\n", fmin(1.0, 0.0/0.0));
    printf("fmin nan 1.0 = %a\n", fmin(0.0/0.0, 1.0));
    /* lrint/llrint extra */
    printf("lrint 1e15 = %ld\n", lrint(1e15));
    printf("llrint 1e15 = %lld\n", llrint(1e15));
    /* complex extra */
    printf("ctanf 0.1f+0.1fi = %a + %ai\n",
           crealf(ctanf(0.1f + 0.1f*I)), cimagf(ctanf(0.1f + 0.1f*I)));
    printf("ctan 0.1+0.1i = %a + %ai\n",
           creal(ctan(0.1 + 0.1*I)), cimag(ctan(0.1 + 0.1*I)));
    /* csqrtf negative real */
    printf("csqrtf -1.0f+0.0fi = %a + %ai\n",
           crealf(csqrtf(-1.0f + 0.0f*I)), cimagf(csqrtf(-1.0f + 0.0f*I)));
}

/* ------------------------------------------------------------------ */
/* Coverage round 7: targeted remaining uncovered branches             */
/* ------------------------------------------------------------------ */

/* erfd.c:227:9:false — hx < 0 (negative x in [1.25,6) range) */
static void test_erf_round7(void)
{
    printf("erf -2.0 = %a\n", erf(-2.0));
    printf("erf -2.5 = %a\n", erf(-2.5));
    printf("erf -3.0 = %a\n", erf(-3.0));
    printf("erf -4.0 = %a\n", erf(-4.0));
    printf("erf -5.0 = %a\n", erf(-5.0));
    printf("erf -1.5 = %a\n", erf(-1.5));
    printf("erf -1.25 = %a\n", erf(-1.25));
}

/* erfcd.c: small positive x branches and negative large x */
static void test_erfc_round7(void)
{
    /* erfcd.c:182:13:false — |x| in [2^-56, 0.84375): enter tiny-x section */
    /* erfcd.c:188:13:true  — x < 1/4: x in [2^-56, 0.25) */
    printf("erfc 0.001 = %a\n", erfc(0.001));
    printf("erfc 0.01 = %a\n", erfc(0.01));
    printf("erfc 0.1 = %a\n", erfc(0.1));
    /* erfcd.c:188:13:false — x in [0.25, 0.84375) */
    printf("erfc 0.25 = %a\n", erfc(0.25));
    printf("erfc 0.5 = %a\n", erfc(0.5));
    printf("erfc 0.7 = %a\n", erfc(0.7));
    printf("erfc 0.84 = %a\n", erfc(0.84));
    /* erfcd.c:237:13:false — hx <= 0 (x negative) and |x| >= 28 */
    printf("erfc -28.0 = %a\n", erfc(-28.0));
    printf("erfc -29.0 = %a\n", erfc(-29.0));
    printf("erfc -30.0 = %a\n", erfc(-30.0));
}

/* expm1d.c:261:17:true (k=1, residual < -0.25) and 278:13:false (k >= 20) */
static void test_expm1_round7(void)
{
    /* expm1d.c:261:17:true — k=1, x near ln(2)*1 ≈ 0.693, sub-thresh residual */
    printf("expm1 0.4 = %a\n", expm1(0.4));
    printf("expm1 0.42 = %a\n", expm1(0.42));
    printf("expm1 0.45 = %a\n", expm1(0.45));
    /* expm1d.c:278:13:false — k >= 20 */
    printf("expm1 15.0 = %a\n", expm1(15.0));
    printf("expm1 20.0 = %a\n", expm1(20.0));
}

/* expm1f.c:69:32:false (xsb!=0, negative x ternary side)
   expm1f.c:105:17:true (k=1 residual < -0.25f)
   expm1f.c:112:13:true (k <= -2 or k > 56) */
static void test_expm1f_round7(void)
{
    /* expm1f.c:69:32:false — xsb != 0 path in ternary, x negative */
    printf("expm1f -0.4f = %a\n", expm1f(-0.4f));
    printf("expm1f -0.3f = %a\n", expm1f(-0.3f));
    /* expm1f.c:105:17:true — k=1, residual < -0.25f */
    printf("expm1f 0.4f = %a\n", expm1f(0.4f));
    printf("expm1f 0.42f = %a\n", expm1f(0.42f));
    /* expm1f.c:112:13:true — k <= -2: x sufficiently negative to get k=-3+ */
    printf("expm1f -5.0f = %a\n", expm1f(-5.0f));
    printf("expm1f -10.0f = %a\n", expm1f(-10.0f));
    /* expm1f.c:112:13:true — k > 56: large positive x */
    printf("expm1f 50.0f = %a\n", expm1f(50.0f));
    printf("expm1f 60.0f = %a\n", expm1f(60.0f));
}

/* logf.c:65:13:false (f != 0 in tiny-f region)
   logf.c:76:13:true/false (k == 0 vs k != 0 in tiny-f, f != 0 path)
   logf.c:98:13:true/false (k == 0 vs k != 0 in i>0 main path) */
static void test_logf_round7(void)
{
    /* logf.c:65:13:false, 76:13:true — f tiny, f != 0, k == 0 */
    printf("logf 1.0f+1e-7f = %a\n", logf(1.0f + 1e-7f));
    printf("logf 1.0f-1e-7f = %a\n", logf(1.0f - 1e-7f));
    /* logf.c:65:13:false, 76:13:false — f tiny, f != 0, k != 0 (e.g. near 2.0) */
    printf("logf 2.0f+1e-6f = %a\n", logf(2.0f + 1e-6f));
    printf("logf 2.0f-1e-6f = %a\n", logf(2.0f - 1e-6f));
    /* logf.c:98:13:false — k != 0 in i>0 main path (normal range but k != 0) */
    printf("logf 3.0f = %a\n", logf(3.0f));
    printf("logf 5.0f = %a\n", logf(5.0f));
    /* logf.c:98:13:true and i<=0 k==0/k!=0 */
    printf("logf 1.3f = %a\n", logf(1.3f));
    printf("logf 1.7f = %a\n", logf(1.7f));
    printf("logf 0.7f = %a\n", logf(0.7f));
    printf("logf 0.3f = %a\n", logf(0.3f));
}

/* log1pd.c: small-x branches and k=0 path */
static void test_log1p_round7(void)
{
    /* log1pd.c:166:17:false — |x| in [2^-54, 2^-29) */
    printf("log1p 1e-16 = %a\n", log1p(1e-16));
    printf("log1p 2e-10 = %a\n", log1p(2e-10));
    /* log1pd.c:173:23:true — k=0 path (x in ~(-0.293, 0.414)) */
    printf("log1p 0.1 = %a\n", log1p(0.1));
    printf("log1p 0.3 = %a\n", log1p(0.3));
    printf("log1p -0.1 = %a\n", log1p(-0.1));
    printf("log1p -0.2 = %a\n", log1p(-0.2));
    /* log1pd.c:181:13:false — k != 0 branch (x outside (-0.293, 0.414)) */
    printf("log1p 0.5 = %a\n", log1p(0.5));
    printf("log1p 2.0 = %a\n", log1p(2.0));
    printf("log1p -0.5 = %a\n", log1p(-0.5));
    /* log1pd.c:210:13:false — hu != 0, f != 0 in the hu-correction region */
    printf("log1p 1e-5 = %a\n", log1p(1e-5));
    printf("log1p -1e-5 = %a\n", log1p(-1e-5));
}

/* powd.c:148 — x==1.0 with quiet NaN y */
static void test_pow_round7(void)
{
    /* powd.c:148:13 — ((hx-0x3ff00000)|lx)==0 && __issignaling(y)==0: x=1, y=qNaN */
    double qnan = 0.0 / 0.0;
    printf("pow 1.0 qnan = %a\n", pow(1.0, qnan));
    /* powd.c:139:13:false — x not sNaN (already covered), plus x near 1 */
    printf("pow 1.0 2.0 = %a\n", pow(1.0, 2.0));
    printf("pow 1.0 -inf = %a\n", pow(1.0, -1.0/0.0));
    printf("pow 1.0 inf = %a\n", pow(1.0, 1.0/0.0));
    /* powf.c:62 — x==1.0f with quiet NaN y */
    float qnanf = 0.0f / 0.0f;
    printf("powf 1.0f qnanf = %a\n", powf(1.0f, qnanf));
    printf("powf 1.0f -inff = %a\n", powf(1.0f, -1.0f/0.0f));
    printf("powf 1.0f inff = %a\n", powf(1.0f, 1.0f/0.0f));
}

/* ------------------------------------------------------------------ */
/* main */
/* ------------------------------------------------------------------ */
int main(void)
{
    /* Double trig */
    test_acos();
    test_asin();
    test_atan();
    test_atan2();
    test_cos();
    test_sin();
    test_tan();

    /* Double hyperbolic */
    test_acosh();
    test_asinh();
    test_atanh();
    test_cosh();
    test_sinh();
    test_tanh();

    /* Double exp/log */
    test_exp();
    test_exp2();
    test_expm1();
    test_frexp();
    test_ilogb();
    test_ldexp();
    test_log();
    test_log10();
    test_log1p();
    test_log2();
    test_logb();
    test_modf();
    test_scalbn();
    test_scalbln();

    /* Double power/abs */
    test_cbrt();
    test_fabs();
    test_hypot();
    test_pow();
    test_sqrt();

    /* Double error/gamma */
    test_erf();
    test_erfc();
    test_lgamma();
    test_tgamma();

    /* Double nearest int */
    test_ceil();
    test_floor();
    test_nearbyint();
    test_rint();
    test_lrint();
    test_llrint();
    test_round();
    test_lround();
    test_llround();
    test_trunc();

    /* Double remainder */
    test_fmod();
    test_remainder();
    test_remquo();

    /* Double manipulation */
    test_copysign();
    test_nan();
    test_nextafter();

    /* Double max/min/fdim/fma */
    test_fdim();
    test_fmax();
    test_fmin();
    test_fma();

    /* Double Bessel */
    test_j0();
    test_j1();
    test_jn();
    test_y0();
    test_y1();
    test_yn();

    /* Float trig */
    test_acosf();
    test_asinf();
    test_atanf();
    test_atan2f();
    test_cosf();
    test_sinf();
    test_tanf();

    /* Float hyperbolic */
    test_acoshf();
    test_asinhf();
    test_atanhf();
    test_coshf();
    test_sinhf();
    test_tanhf();

    /* Float exp/log */
    test_expf();
    test_exp2f();
    test_expm1f();
    test_frexpf();
    test_ilogbf();
    test_ldexpf();
    test_logf();
    test_log10f();
    test_log1pf();
    test_log2f();
    test_logbf();
    test_modff();
    test_scalbnf();
    test_scalblnf();

    /* Float power/abs */
    test_cbrtf();
    test_fabsf();
    test_hypotf();
    test_powf();
    test_sqrtf();

    /* Float error/gamma */
    test_erff();
    test_erfcf();
    test_lgammaf();
    test_tgammaf();

    /* Float nearest int */
    test_ceilf();
    test_floorf();
    test_nearbyintf();
    test_rintf();
    test_lrintf();
    test_llrintf();
    test_roundf();
    test_lroundf();
    test_llroundf();
    test_truncf();

    /* Float remainder */
    test_fmodf();
    test_remainderf();
    test_remquof();

    /* Float manipulation */
    test_copysignf();
    test_nanf();
    test_nextafterf();

    /* Float max/min/fdim/fma */
    test_fdimf();
    test_fmaxf();
    test_fminf();
    test_fmaf();

    /* Classification / signbit */
    test_fpclassifyd();
    test_fpclassifyf();
    test_signbitd();
    test_signbitf();

    /* Internal non-static helpers */
    test___cos();
    test___sin();
    test___cosf();
    test___sinf();
    test___rem_pio2();
    test___rem_pio2f();
    test___lgamma();
    test___lgammaf();
    test___redupi();
    test___redupif();
    test___ccoshsinh();
    test___ccoshsinhf();

    /* Bridge (static) helpers */
    test_bridge___rem_pio2_internal();
    test_bridge___rem_pio2f_internal();
    test_bridge___tan();
    test_bridge___tanf();
    test_bridge___sin_pi();
    test_bridge___sin_pif();
    test_bridge___ctans();
    test_bridge___ctansf();

    /* Complex double */
    test_cabs();
    test_carg();
    test_cimag();
    test_creal();
    test_conj();
    test_cproj();
    test_cacos();
    test_casin();
    test_catan();
    test_ccos();
    test_csin();
    test_ctan();
    test_cacosh();
    test_casinh();
    test_catanh();
    test_ccosh();
    test_csinh();
    test_ctanh();
    test_cexp();
    test_clog();
    test_cpow();
    test_csqrt();

    /* Complex float */
    test_cabsf();
    test_cargf();
    test_cimagf();
    test_crealf();
    test_conjf();
    test_cprojf();
    test_cacosf();
    test_casinf();
    test_catanf();
    test_ccosf();
    test_csinf();
    test_ctanf();
    test_cacoshf();
    test_casinhf();
    test_catanhf();
    test_ccoshf();
    test_csinhf();
    test_ctanhf();
    test_cexpf();
    test_clogf();
    test_cpowf();
    test_csqrtf();

    /* Coverage-targeted: double special values */
    test_acos_cov();
    test_asin_cov();
    test_atan2_cov();
    test_acosh_cov();
    test_asinh_cov();
    test_atanh_cov();
    test_cosh_cov();
    test_sinh_cov();
    test_tanh_cov();
    test_exp_cov();
    test_expm1_cov();
    test_frexp_cov();
    test_ilogb_cov();
    test_ldexp_cov();
    test_log_cov();
    test_log10_cov();
    test_log2_cov();
    test_log1p_cov();
    test_logb_cov();
    test_cbrt_cov();
    test_hypot_cov();
    test_pow_cov();
    test_sqrt_cov();
    test_ceil_cov();
    test_floor_cov();
    test_trunc_cov();
    test_round_cov();
    test_rint_cov();
    test_lrint_cov();
    test_llrint_cov();
    test_lround_cov();
    test_llround_cov();
    test_modf_cov();
    test_fmod_cov();
    test_remainder_cov();
    test_remquo_cov();
    test_nextafter_cov();
    test_scalbn_cov();
    test_scalbln_cov();
    test_fmax_cov();
    test_fmin_cov();
    test_fdim_cov();
    test_fabs_cov();
    test_copysign_cov();
    test_erf_cov();
    test_erfc_cov();
    test_lgamma_cov();
    test_tgamma_cov();
    test_j0_cov();
    test_j1_cov();
    test_jn_cov();
    test_y0_cov();
    test_y1_cov();
    test_yn_cov();
    test_fpclassify_cov();
    test_sin_cov();
    test_cos_cov();
    test_tan_cov();

    /* Coverage-targeted: float special values */
    test_acosf_cov();
    test_asinf_cov();
    test_atanf_cov();
    test_atan2f_cov();
    test_acoshf_cov();
    test_asinhf_cov();
    test_atanhf_cov();
    test_coshf_cov();
    test_sinhf_cov();
    test_tanhf_cov();
    test_expf_cov();
    test_expm1f_cov();
    test_frexpf_cov();
    test_ilogbf_cov();
    test_logf_cov();
    test_log10f_cov();
    test_log2f_cov();
    test_log1pf_cov();
    test_logbf_cov();
    test_cbrtf_cov();
    test_hypotf_cov();
    test_powf_cov();
    test_sqrtf_cov();
    test_erff_cov();
    test_erfcf_cov();
    test_lgammaf_cov();
    test_tgammaf_cov();
    test_ceilf_cov();
    test_floorf_cov();
    test_truncf_cov();
    test_roundf_cov();
    test_rintf_cov();
    test_lrintf_cov();
    test_llrintf_cov();
    test_lroundf_cov();
    test_llroundf_cov();
    test_modff_cov();
    test_fmodf_cov();
    test_remainderf_cov();
    test_nextafterf_cov();
    test_scalbnf_cov();
    test_scalblnf_cov();
    test_fmaxf_cov();
    test_fminf_cov();
    test_fabsf_cov();
    test_copysignf_cov();
    test_sinf_cov();
    test_cosf_cov();
    test_tanf_cov();

    /* Coverage-targeted: complex edge cases */
    test_csqrt_cov();
    test_csqrtf_cov();
    test_catan_cov();
    test_catanf_cov();
    test_cpow_cov();
    test_cpowf_cov();
    test_cproj_cov();
    test_cprojf_cov();
    test_ctan_cov();
    test_ctanf_cov();

    /* Coverage round 3: additional branches */
    test_trig_moderate();
    test_asin_moderate();
    test_atan_extra();
    test_acosf_acoshf_extra();
    test_cpow_imagexp();
    test_cpowf_imagexp();
    test_csqrt_large_imag();
    test_csqrtf_large_imag();
    test_ctan_extra();
    test_ctanf_extra();
    test_ccoshsinh_extreme();
    test_snan();
    test_ldexpf_extra();
    test_asinhf_extra();
    test_remquof_extra();
    test_atanf_extra();
    test_catanf_extra();

    /* Coverage round 4: additional uncovered branches */
    test_lgamma_coverage2();
    test_lgammaf_coverage2();
    test_sinh_cosh_overflow();
    test_jn_coverage2();
    test_yn_coverage2();
    test_atan_xlarge();
    test_y0_y1_extreme();
    test_bessel_ranges();
    test_pow_coverage2();
    test_trig_coverage2();
    test_erff_coverage2();
    test_erfcf_coverage2();
    test_atanhf_coverage2();
    test_rint_coverage2();
    test_coshf_sinhf_extra();
    test_log_coverage2();

    /* Coverage round 5: additional uncovered branches */
    test_scalbn_coverage3();
    test_scalbnf_coverage3();
    test_modf_coverage2();
    test_modff_coverage2();
    test_nextafter_coverage2();
    test_nextafterf_coverage2();
    test_lround_coverage2();
    test_llround_coverage2();
    test_lroundf_coverage2();
    test_llroundf_coverage2();
    test_lrint_coverage2();
    test_llrint_coverage2();
    test_lrintf_coverage2();
    test_llrintf_coverage2();
    test_remquof_coverage2();
    test_fmod_coverage2();
    test_fmodf_coverage2();
    test_remainder_coverage2();
    test_remquo_coverage2();
    test_remainderf_coverage2();
    test_hypot_snan();
    test_ceil_floor_extra();
    test_ceilf_floorf_extra();
    test_log_coverage3();
    test_trig_coverage3();
    test_gamma_coverage2();
    test_ilogb_coverage2();
    test_bessel_coverage2();
    test_logb_coverage2();
    test_acoshd_atanhd_extra();
    test_float_coverage3();

    /* Coverage round 6: targeted remaining uncovered branches */
    test_ceil_round6();
    test_floor_round6();
    test_trunc_round6();
    test_rint_round6();
    test_exp_round6();
    test_sinh_cosh_round6();
    test_lgamma_round6();
    test_bessel_round6();
    test_scalbn_round6();
    test_atan2_round6();
    test_float_round6();

    /* Coverage round 7: targeted remaining uncovered branches */
    test_erf_round7();
    test_erfc_round7();
    test_expm1_round7();
    test_expm1f_round7();
    test_logf_round7();
    test_log1p_round7();
    test_pow_round7();

    return 0;
}
