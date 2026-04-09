/* test_suite.c — comprehensive test suite for libmcs */
/* Generated for s2: covers all public and internal functions */

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <complex.h>
#include "test_bridge.h"

/* Forward declarations for non-static internal functions not in public headers */

/* mathd/internal/trigd.c — non-static */
extern double __cos(double x, double y);
extern double __sin(double x, double y, int iy);
extern int32_t __rem_pio2(double x, double *y);

/* mathf/internal/trigf.c — non-static */
extern float __cosf(float x, float y);
extern float __sinf(float x, float y, int iy);
extern int32_t __rem_pio2f(float x, float *y);

/* mathd/internal/gammad.c — non-static */
extern double __lgamma(double x, int *signgamp);

/* mathf/internal/gammaf.c — non-static */
extern float __lgammaf(float x, int *signgamp);

/* complexd/internal/ctrigd.c — non-static */
extern void __ccoshsinh(double x, double *c, double *s);
extern double __redupi(double x);

/* complexf/internal/ctrigf.c — non-static */
extern void __ccoshsinhf(float x, float *c, float *s);
extern float __redupif(float x);

/* mathd/internal/fpclassifyd.c — declared in math.h */
/* extern int __fpclassifyd(double); */
/* extern int __fpclassifyf(float); */
/* extern int __signbitd(double); */
/* extern int __signbitf(float); */

/* common/fenv.c — declared without including fenv.h (which has #error guard) */
extern int feclearexcept(int excepts);
extern int feraiseexcept(int excepts);
extern int fegetround(void);
extern int fesetround(int rdir);
extern int fegetexceptflag(void *flagp, int excepts);
extern int fesetexceptflag(const void *flagp, int excepts);
extern int fegetenv(void *envp);
extern int fesetenv(const void *envp);
extern int feholdexcept(void *envp);
extern int feupdateenv(const void *envp);
extern int fetestexcept(int excepts);

/* signgam */
extern int __signgam;

/* ============================================================
 * Double trigonometric functions
 * ============================================================ */
static void test_trig_double(void)
{
    printf("=== Double Trig ===\n");
    printf("acos %a = %a\n", 0.5, acos(0.5));
    printf("acos %a = %a\n", -0.5, acos(-0.5));
    printf("acos %a = %a\n", 1.0, acos(1.0));
    printf("acos %a = %a\n", 0.0, acos(0.0));

    printf("asin %a = %a\n", 0.5, asin(0.5));
    printf("asin %a = %a\n", -0.5, asin(-0.5));
    printf("asin %a = %a\n", 1.0, asin(1.0));
    printf("asin %a = %a\n", 0.0, asin(0.0));

    printf("atan %a = %a\n", 1.0, atan(1.0));
    printf("atan %a = %a\n", -1.0, atan(-1.0));
    printf("atan %a = %a\n", 0.0, atan(0.0));
    printf("atan %a = %a\n", 1e10, atan(1e10));

    printf("atan2 %a %a = %a\n", 1.0, 1.0, atan2(1.0, 1.0));
    printf("atan2 %a %a = %a\n", -1.0, 1.0, atan2(-1.0, 1.0));
    printf("atan2 %a %a = %a\n", 1.0, -1.0, atan2(1.0, -1.0));
    printf("atan2 %a %a = %a\n", 0.0, 0.0, atan2(0.0, 0.0));
    printf("atan2 %a %a = %a\n", 0.0, -0.0, atan2(0.0, -0.0));

    printf("cos %a = %a\n", 0.0, cos(0.0));
    printf("cos %a = %a\n", 0.5, cos(0.5));
    printf("cos %a = %a\n", 1.0, cos(1.0));
    printf("cos %a = %a\n", M_PI, cos(M_PI));
    printf("cos %a = %a\n", M_PI_2, cos(M_PI_2));

    printf("sin %a = %a\n", 0.0, sin(0.0));
    printf("sin %a = %a\n", 0.5, sin(0.5));
    printf("sin %a = %a\n", 1.0, sin(1.0));
    printf("sin %a = %a\n", M_PI, sin(M_PI));
    printf("sin %a = %a\n", M_PI_2, sin(M_PI_2));

    printf("tan %a = %a\n", 0.0, tan(0.0));
    printf("tan %a = %a\n", 0.5, tan(0.5));
    printf("tan %a = %a\n", 1.0, tan(1.0));
    printf("tan %a = %a\n", M_PI_4, tan(M_PI_4));
}

/* ============================================================
 * Double hyperbolic functions
 * ============================================================ */
static void test_hyperbolic_double(void)
{
    printf("=== Double Hyperbolic ===\n");
    printf("acosh %a = %a\n", 1.0, acosh(1.0));
    printf("acosh %a = %a\n", 2.0, acosh(2.0));
    printf("acosh %a = %a\n", 10.0, acosh(10.0));

    printf("asinh %a = %a\n", 0.0, asinh(0.0));
    printf("asinh %a = %a\n", 1.0, asinh(1.0));
    printf("asinh %a = %a\n", -1.0, asinh(-1.0));

    printf("atanh %a = %a\n", 0.0, atanh(0.0));
    printf("atanh %a = %a\n", 0.5, atanh(0.5));
    printf("atanh %a = %a\n", -0.5, atanh(-0.5));

    printf("cosh %a = %a\n", 0.0, cosh(0.0));
    printf("cosh %a = %a\n", 1.0, cosh(1.0));
    printf("cosh %a = %a\n", -1.0, cosh(-1.0));

    printf("sinh %a = %a\n", 0.0, sinh(0.0));
    printf("sinh %a = %a\n", 1.0, sinh(1.0));
    printf("sinh %a = %a\n", -1.0, sinh(-1.0));

    printf("tanh %a = %a\n", 0.0, tanh(0.0));
    printf("tanh %a = %a\n", 1.0, tanh(1.0));
    printf("tanh %a = %a\n", -1.0, tanh(-1.0));
    printf("tanh %a = %a\n", 100.0, tanh(100.0));
}

/* ============================================================
 * Double exponential and logarithmic functions
 * ============================================================ */
static void test_exp_log_double(void)
{
    int exp_out;
    double intpart;
    printf("=== Double Exp/Log ===\n");

    printf("exp %a = %a\n", 0.0, exp(0.0));
    printf("exp %a = %a\n", 1.0, exp(1.0));
    printf("exp %a = %a\n", -1.0, exp(-1.0));
    printf("exp %a = %a\n", 2.0, exp(2.0));

    printf("exp2 %a = %a\n", 0.0, exp2(0.0));
    printf("exp2 %a = %a\n", 1.0, exp2(1.0));
    printf("exp2 %a = %a\n", -1.0, exp2(-1.0));
    printf("exp2 %a = %a\n", 10.0, exp2(10.0));

    printf("expm1 %a = %a\n", 0.0, expm1(0.0));
    printf("expm1 %a = %a\n", 1.0, expm1(1.0));
    printf("expm1 %a = %a\n", 1e-10, expm1(1e-10));

    printf("frexp %a = %a exp=%d\n", 1.0, frexp(1.0, &exp_out), exp_out);
    printf("frexp %a = %a exp=%d\n", 0.5, frexp(0.5, &exp_out), exp_out);
    printf("frexp %a = %a exp=%d\n", 4.0, frexp(4.0, &exp_out), exp_out);

    printf("ilogb %a = %d\n", 1.0, ilogb(1.0));
    printf("ilogb %a = %d\n", 2.0, ilogb(2.0));
    printf("ilogb %a = %d\n", 0.5, ilogb(0.5));

    printf("ldexp %a %d = %a\n", 1.0, 0, ldexp(1.0, 0));
    printf("ldexp %a %d = %a\n", 1.0, 1, ldexp(1.0, 1));
    printf("ldexp %a %d = %a\n", 1.0, -1, ldexp(1.0, -1));

    printf("log %a = %a\n", 1.0, log(1.0));
    printf("log %a = %a\n", M_E, log(M_E));
    printf("log %a = %a\n", 2.0, log(2.0));

    printf("log10 %a = %a\n", 1.0, log10(1.0));
    printf("log10 %a = %a\n", 10.0, log10(10.0));
    printf("log10 %a = %a\n", 100.0, log10(100.0));

    printf("log1p %a = %a\n", 0.0, log1p(0.0));
    printf("log1p %a = %a\n", 1.0, log1p(1.0));
    printf("log1p %a = %a\n", 1e-10, log1p(1e-10));

    printf("log2 %a = %a\n", 1.0, log2(1.0));
    printf("log2 %a = %a\n", 2.0, log2(2.0));
    printf("log2 %a = %a\n", 4.0, log2(4.0));

    printf("logb %a = %a\n", 1.0, logb(1.0));
    printf("logb %a = %a\n", 2.0, logb(2.0));
    printf("logb %a = %a\n", 0.5, logb(0.5));

    printf("modf %a = %a intpart=%a\n", 1.5, modf(1.5, &intpart), intpart);
    printf("modf %a = %a intpart=%a\n", -1.5, modf(-1.5, &intpart), intpart);
    printf("modf %a = %a intpart=%a\n", 0.0, modf(0.0, &intpart), intpart);

    printf("scalbn %a %d = %a\n", 1.0, 0, scalbn(1.0, 0));
    printf("scalbn %a %d = %a\n", 1.0, 1, scalbn(1.0, 1));
    printf("scalbn %a %d = %a\n", 1.0, -1, scalbn(1.0, -1));

    printf("scalbln %a %ld = %a\n", 1.0, 0L, scalbln(1.0, 0L));
    printf("scalbln %a %ld = %a\n", 1.0, 2L, scalbln(1.0, 2L));
    printf("scalbln %a %ld = %a\n", 1.0, -2L, scalbln(1.0, -2L));
}

/* ============================================================
 * Double power and absolute-value functions
 * ============================================================ */
static void test_power_double(void)
{
    printf("=== Double Power/Abs ===\n");
    printf("cbrt %a = %a\n", 8.0, cbrt(8.0));
    printf("cbrt %a = %a\n", -8.0, cbrt(-8.0));
    printf("cbrt %a = %a\n", 0.0, cbrt(0.0));

    printf("fabs %a = %a\n", -1.5, fabs(-1.5));
    printf("fabs %a = %a\n", 1.5, fabs(1.5));
    printf("fabs %a = %a\n", 0.0, fabs(0.0));

    printf("hypot %a %a = %a\n", 3.0, 4.0, hypot(3.0, 4.0));
    printf("hypot %a %a = %a\n", 0.0, 1.0, hypot(0.0, 1.0));
    printf("hypot %a %a = %a\n", 1.0, 0.0, hypot(1.0, 0.0));

    printf("pow %a %a = %a\n", 2.0, 10.0, pow(2.0, 10.0));
    printf("pow %a %a = %a\n", 2.0, 0.5, pow(2.0, 0.5));
    printf("pow %a %a = %a\n", 1.0, 0.0, pow(1.0, 0.0));

    printf("sqrt %a = %a\n", 4.0, sqrt(4.0));
    printf("sqrt %a = %a\n", 2.0, sqrt(2.0));
    printf("sqrt %a = %a\n", 0.0, sqrt(0.0));
}

/* ============================================================
 * Double error and gamma functions
 * ============================================================ */
static void test_gamma_double(void)
{
    printf("=== Double Erf/Gamma ===\n");
    printf("erf %a = %a\n", 0.0, erf(0.0));
    printf("erf %a = %a\n", 1.0, erf(1.0));
    printf("erf %a = %a\n", -1.0, erf(-1.0));
    printf("erf %a = %a\n", 0.5, erf(0.5));

    printf("erfc %a = %a\n", 0.0, erfc(0.0));
    printf("erfc %a = %a\n", 1.0, erfc(1.0));
    printf("erfc %a = %a\n", -1.0, erfc(-1.0));

    printf("lgamma %a = %a\n", 1.0, lgamma(1.0));
    printf("lgamma %a = %a\n", 2.0, lgamma(2.0));
    printf("lgamma %a = %a\n", 0.5, lgamma(0.5));
    printf("lgamma %a signgam=%d\n", -0.5, lgamma(-0.5), __signgam);

    printf("tgamma %a = %a\n", 1.0, tgamma(1.0));
    printf("tgamma %a = %a\n", 2.0, tgamma(2.0));
    printf("tgamma %a = %a\n", 0.5, tgamma(0.5));
}

/* ============================================================
 * Double nearest integer functions
 * ============================================================ */
static void test_nearest_int_double(void)
{
    printf("=== Double Nearest Int ===\n");
    printf("ceil %a = %a\n", 1.5, ceil(1.5));
    printf("ceil %a = %a\n", -1.5, ceil(-1.5));
    printf("ceil %a = %a\n", 2.0, ceil(2.0));

    printf("floor %a = %a\n", 1.5, floor(1.5));
    printf("floor %a = %a\n", -1.5, floor(-1.5));
    printf("floor %a = %a\n", 2.0, floor(2.0));

    printf("nearbyint %a = %a\n", 1.5, nearbyint(1.5));
    printf("nearbyint %a = %a\n", -1.5, nearbyint(-1.5));
    printf("nearbyint %a = %a\n", 2.5, nearbyint(2.5));

    printf("rint %a = %a\n", 1.5, rint(1.5));
    printf("rint %a = %a\n", -1.5, rint(-1.5));
    printf("rint %a = %a\n", 2.5, rint(2.5));

    printf("lrint %a = %ld\n", 1.5, lrint(1.5));
    printf("lrint %a = %ld\n", -1.5, lrint(-1.5));
    printf("lrint %a = %ld\n", 2.5, lrint(2.5));

    printf("llrint %a = %lld\n", 1.5, llrint(1.5));
    printf("llrint %a = %lld\n", -1.5, llrint(-1.5));
    printf("llrint %a = %lld\n", 2.5, llrint(2.5));

    printf("round %a = %a\n", 0.5, round(0.5));
    printf("round %a = %a\n", -0.5, round(-0.5));
    printf("round %a = %a\n", 1.5, round(1.5));

    printf("lround %a = %ld\n", 0.5, lround(0.5));
    printf("lround %a = %ld\n", -0.5, lround(-0.5));
    printf("lround %a = %ld\n", 1.5, lround(1.5));

    printf("llround %a = %lld\n", 0.5, llround(0.5));
    printf("llround %a = %lld\n", -0.5, llround(-0.5));
    printf("llround %a = %lld\n", 1.5, llround(1.5));

    printf("trunc %a = %a\n", 1.5, trunc(1.5));
    printf("trunc %a = %a\n", -1.5, trunc(-1.5));
    printf("trunc %a = %a\n", 2.0, trunc(2.0));
}

/* ============================================================
 * Double remainder functions
 * ============================================================ */
static void test_remainder_double(void)
{
    int quo;
    printf("=== Double Remainder ===\n");
    printf("fmod %a %a = %a\n", 5.0, 3.0, fmod(5.0, 3.0));
    printf("fmod %a %a = %a\n", -5.0, 3.0, fmod(-5.0, 3.0));
    printf("fmod %a %a = %a\n", 0.0, 1.0, fmod(0.0, 1.0));

    printf("remainder %a %a = %a\n", 5.0, 3.0, remainder(5.0, 3.0));
    printf("remainder %a %a = %a\n", -5.0, 3.0, remainder(-5.0, 3.0));

    printf("remquo %a %a = %a quo=%d\n", 5.0, 3.0, remquo(5.0, 3.0, &quo), quo);
    printf("remquo %a %a = %a quo=%d\n", -5.0, 3.0, remquo(-5.0, 3.0, &quo), quo);
}

/* ============================================================
 * Double manipulation functions
 * ============================================================ */
static void test_manip_double(void)
{
    printf("=== Double Manipulation ===\n");
    printf("copysign %a %a = %a\n", 1.0, -1.0, copysign(1.0, -1.0));
    printf("copysign %a %a = %a\n", -1.0, 1.0, copysign(-1.0, 1.0));
    printf("copysign %a %a = %a\n", 0.0, -1.0, copysign(0.0, -1.0));

    printf("nan = %a\n", nan(""));

    printf("nextafter %a %a = %a\n", 1.0, 2.0, nextafter(1.0, 2.0));
    printf("nextafter %a %a = %a\n", 1.0, 0.0, nextafter(1.0, 0.0));
    printf("nextafter %a %a = %a\n", 0.0, 1.0, nextafter(0.0, 1.0));
}

/* ============================================================
 * Double max, min, dim, fma
 * ============================================================ */
static void test_maxmin_double(void)
{
    printf("=== Double Max/Min/Dim/FMA ===\n");
    printf("fdim %a %a = %a\n", 3.0, 1.0, fdim(3.0, 1.0));
    printf("fdim %a %a = %a\n", 1.0, 3.0, fdim(1.0, 3.0));
    printf("fdim %a %a = %a\n", 0.0, 0.0, fdim(0.0, 0.0));

    printf("fmax %a %a = %a\n", 1.0, 2.0, fmax(1.0, 2.0));
    printf("fmax %a %a = %a\n", -1.0, 2.0, fmax(-1.0, 2.0));

    printf("fmin %a %a = %a\n", 1.0, 2.0, fmin(1.0, 2.0));
    printf("fmin %a %a = %a\n", -1.0, 2.0, fmin(-1.0, 2.0));

    printf("fma %a %a %a = %a\n", 2.0, 3.0, 4.0, fma(2.0, 3.0, 4.0));
    printf("fma %a %a %a = %a\n", -1.0, 2.0, 1.0, fma(-1.0, 2.0, 1.0));
    printf("fma %a %a %a = %a\n", 0.0, 1.0, 0.0, fma(0.0, 1.0, 0.0));
}

/* ============================================================
 * Double Bessel functions
 * ============================================================ */
static void test_bessel_double(void)
{
    printf("=== Double Bessel ===\n");
    printf("j0 %a = %a\n", 0.0, j0(0.0));
    printf("j0 %a = %a\n", 1.0, j0(1.0));
    printf("j0 %a = %a\n", 5.0, j0(5.0));

    printf("j1 %a = %a\n", 0.0, j1(0.0));
    printf("j1 %a = %a\n", 1.0, j1(1.0));
    printf("j1 %a = %a\n", 5.0, j1(5.0));

    printf("jn %d %a = %a\n", 0, 1.0, jn(0, 1.0));
    printf("jn %d %a = %a\n", 1, 1.0, jn(1, 1.0));
    printf("jn %d %a = %a\n", 2, 1.0, jn(2, 1.0));

    printf("y0 %a = %a\n", 1.0, y0(1.0));
    printf("y0 %a = %a\n", 5.0, y0(5.0));

    printf("y1 %a = %a\n", 1.0, y1(1.0));
    printf("y1 %a = %a\n", 5.0, y1(5.0));

    printf("yn %d %a = %a\n", 0, 1.0, yn(0, 1.0));
    printf("yn %d %a = %a\n", 1, 1.0, yn(1, 1.0));
    printf("yn %d %a = %a\n", 2, 1.0, yn(2, 1.0));
}

/* ============================================================
 * Float trigonometric functions
 * ============================================================ */
static void test_trig_float(void)
{
    printf("=== Float Trig ===\n");
    printf("acosf %a = %a\n", 0.5f, acosf(0.5f));
    printf("acosf %a = %a\n", -0.5f, acosf(-0.5f));
    printf("acosf %a = %a\n", 1.0f, acosf(1.0f));
    printf("acosf %a = %a\n", 0.0f, acosf(0.0f));

    printf("asinf %a = %a\n", 0.5f, asinf(0.5f));
    printf("asinf %a = %a\n", -0.5f, asinf(-0.5f));
    printf("asinf %a = %a\n", 1.0f, asinf(1.0f));
    printf("asinf %a = %a\n", 0.0f, asinf(0.0f));

    printf("atanf %a = %a\n", 1.0f, atanf(1.0f));
    printf("atanf %a = %a\n", -1.0f, atanf(-1.0f));
    printf("atanf %a = %a\n", 0.0f, atanf(0.0f));

    printf("atan2f %a %a = %a\n", 1.0f, 1.0f, atan2f(1.0f, 1.0f));
    printf("atan2f %a %a = %a\n", -1.0f, 1.0f, atan2f(-1.0f, 1.0f));
    printf("atan2f %a %a = %a\n", 0.0f, 0.0f, atan2f(0.0f, 0.0f));

    printf("cosf %a = %a\n", 0.0f, cosf(0.0f));
    printf("cosf %a = %a\n", 0.5f, cosf(0.5f));
    printf("cosf %a = %a\n", (float)M_PI, cosf((float)M_PI));

    printf("sinf %a = %a\n", 0.0f, sinf(0.0f));
    printf("sinf %a = %a\n", 0.5f, sinf(0.5f));
    printf("sinf %a = %a\n", (float)M_PI_2, sinf((float)M_PI_2));

    printf("tanf %a = %a\n", 0.0f, tanf(0.0f));
    printf("tanf %a = %a\n", 0.5f, tanf(0.5f));
    printf("tanf %a = %a\n", (float)M_PI_4, tanf((float)M_PI_4));
}

/* ============================================================
 * Float hyperbolic functions
 * ============================================================ */
static void test_hyperbolic_float(void)
{
    printf("=== Float Hyperbolic ===\n");
    printf("acoshf %a = %a\n", 1.0f, acoshf(1.0f));
    printf("acoshf %a = %a\n", 2.0f, acoshf(2.0f));

    printf("asinhf %a = %a\n", 0.0f, asinhf(0.0f));
    printf("asinhf %a = %a\n", 1.0f, asinhf(1.0f));

    printf("atanhf %a = %a\n", 0.0f, atanhf(0.0f));
    printf("atanhf %a = %a\n", 0.5f, atanhf(0.5f));

    printf("coshf %a = %a\n", 0.0f, coshf(0.0f));
    printf("coshf %a = %a\n", 1.0f, coshf(1.0f));

    printf("sinhf %a = %a\n", 0.0f, sinhf(0.0f));
    printf("sinhf %a = %a\n", 1.0f, sinhf(1.0f));

    printf("tanhf %a = %a\n", 0.0f, tanhf(0.0f));
    printf("tanhf %a = %a\n", 1.0f, tanhf(1.0f));
    printf("tanhf %a = %a\n", 100.0f, tanhf(100.0f));
}

/* ============================================================
 * Float exponential and logarithmic functions
 * ============================================================ */
static void test_exp_log_float(void)
{
    int exp_out;
    float intpart;
    printf("=== Float Exp/Log ===\n");

    printf("expf %a = %a\n", 0.0f, expf(0.0f));
    printf("expf %a = %a\n", 1.0f, expf(1.0f));
    printf("expf %a = %a\n", -1.0f, expf(-1.0f));

    printf("exp2f %a = %a\n", 0.0f, exp2f(0.0f));
    printf("exp2f %a = %a\n", 1.0f, exp2f(1.0f));
    printf("exp2f %a = %a\n", -1.0f, exp2f(-1.0f));

    printf("expm1f %a = %a\n", 0.0f, expm1f(0.0f));
    printf("expm1f %a = %a\n", 1.0f, expm1f(1.0f));
    printf("expm1f %a = %a\n", 1e-7f, expm1f(1e-7f));

    printf("frexpf %a = %a exp=%d\n", 1.0f, frexpf(1.0f, &exp_out), exp_out);
    printf("frexpf %a = %a exp=%d\n", 4.0f, frexpf(4.0f, &exp_out), exp_out);

    printf("ilogbf %a = %d\n", 1.0f, ilogbf(1.0f));
    printf("ilogbf %a = %d\n", 2.0f, ilogbf(2.0f));

    printf("ldexpf %a %d = %a\n", 1.0f, 0, ldexpf(1.0f, 0));
    printf("ldexpf %a %d = %a\n", 1.0f, 1, ldexpf(1.0f, 1));

    printf("logf %a = %a\n", 1.0f, logf(1.0f));
    printf("logf %a = %a\n", (float)M_E, logf((float)M_E));

    printf("log10f %a = %a\n", 1.0f, log10f(1.0f));
    printf("log10f %a = %a\n", 10.0f, log10f(10.0f));

    printf("log1pf %a = %a\n", 0.0f, log1pf(0.0f));
    printf("log1pf %a = %a\n", 1.0f, log1pf(1.0f));

    printf("log2f %a = %a\n", 1.0f, log2f(1.0f));
    printf("log2f %a = %a\n", 4.0f, log2f(4.0f));

    printf("logbf %a = %a\n", 1.0f, logbf(1.0f));
    printf("logbf %a = %a\n", 2.0f, logbf(2.0f));

    printf("modff %a = %a intpart=%a\n", 1.5f, modff(1.5f, &intpart), intpart);
    printf("modff %a = %a intpart=%a\n", -1.5f, modff(-1.5f, &intpart), intpart);

    printf("scalbnf %a %d = %a\n", 1.0f, 0, scalbnf(1.0f, 0));
    printf("scalbnf %a %d = %a\n", 1.0f, 2, scalbnf(1.0f, 2));

    printf("scalblnf %a %ld = %a\n", 1.0f, 0L, scalblnf(1.0f, 0L));
    printf("scalblnf %a %ld = %a\n", 1.0f, 3L, scalblnf(1.0f, 3L));
}

/* ============================================================
 * Float power and absolute-value functions
 * ============================================================ */
static void test_power_float(void)
{
    printf("=== Float Power/Abs ===\n");
    printf("cbrtf %a = %a\n", 8.0f, cbrtf(8.0f));
    printf("cbrtf %a = %a\n", -8.0f, cbrtf(-8.0f));
    printf("cbrtf %a = %a\n", 0.0f, cbrtf(0.0f));

    printf("fabsf %a = %a\n", -1.5f, fabsf(-1.5f));
    printf("fabsf %a = %a\n", 1.5f, fabsf(1.5f));

    printf("hypotf %a %a = %a\n", 3.0f, 4.0f, hypotf(3.0f, 4.0f));
    printf("hypotf %a %a = %a\n", 0.0f, 1.0f, hypotf(0.0f, 1.0f));

    printf("powf %a %a = %a\n", 2.0f, 10.0f, powf(2.0f, 10.0f));
    printf("powf %a %a = %a\n", 2.0f, 0.5f, powf(2.0f, 0.5f));

    printf("sqrtf %a = %a\n", 4.0f, sqrtf(4.0f));
    printf("sqrtf %a = %a\n", 2.0f, sqrtf(2.0f));
}

/* ============================================================
 * Float error and gamma functions
 * ============================================================ */
static void test_gamma_float(void)
{
    printf("=== Float Erf/Gamma ===\n");
    printf("erff %a = %a\n", 0.0f, erff(0.0f));
    printf("erff %a = %a\n", 1.0f, erff(1.0f));
    printf("erff %a = %a\n", -1.0f, erff(-1.0f));

    printf("erfcf %a = %a\n", 0.0f, erfcf(0.0f));
    printf("erfcf %a = %a\n", 1.0f, erfcf(1.0f));

    printf("lgammaf %a = %a\n", 1.0f, lgammaf(1.0f));
    printf("lgammaf %a = %a\n", 2.0f, lgammaf(2.0f));
    printf("lgammaf %a = %a\n", 0.5f, lgammaf(0.5f));

    printf("tgammaf %a = %a\n", 1.0f, tgammaf(1.0f));
    printf("tgammaf %a = %a\n", 2.0f, tgammaf(2.0f));
    printf("tgammaf %a = %a\n", 0.5f, tgammaf(0.5f));
}

/* ============================================================
 * Float nearest integer functions
 * ============================================================ */
static void test_nearest_int_float(void)
{
    printf("=== Float Nearest Int ===\n");
    printf("ceilf %a = %a\n", 1.5f, ceilf(1.5f));
    printf("ceilf %a = %a\n", -1.5f, ceilf(-1.5f));

    printf("floorf %a = %a\n", 1.5f, floorf(1.5f));
    printf("floorf %a = %a\n", -1.5f, floorf(-1.5f));

    printf("nearbyintf %a = %a\n", 1.5f, nearbyintf(1.5f));
    printf("nearbyintf %a = %a\n", -1.5f, nearbyintf(-1.5f));

    printf("rintf %a = %a\n", 1.5f, rintf(1.5f));
    printf("rintf %a = %a\n", -1.5f, rintf(-1.5f));

    printf("lrintf %a = %ld\n", 1.5f, lrintf(1.5f));
    printf("lrintf %a = %ld\n", -1.5f, lrintf(-1.5f));

    printf("llrintf %a = %lld\n", 1.5f, llrintf(1.5f));
    printf("llrintf %a = %lld\n", -1.5f, llrintf(-1.5f));

    printf("roundf %a = %a\n", 0.5f, roundf(0.5f));
    printf("roundf %a = %a\n", -0.5f, roundf(-0.5f));

    printf("lroundf %a = %ld\n", 0.5f, lroundf(0.5f));
    printf("lroundf %a = %ld\n", -0.5f, lroundf(-0.5f));

    printf("llroundf %a = %lld\n", 0.5f, llroundf(0.5f));
    printf("llroundf %a = %lld\n", -0.5f, llroundf(-0.5f));

    printf("truncf %a = %a\n", 1.5f, truncf(1.5f));
    printf("truncf %a = %a\n", -1.5f, truncf(-1.5f));
}

/* ============================================================
 * Float remainder functions
 * ============================================================ */
static void test_remainder_float(void)
{
    int quo;
    printf("=== Float Remainder ===\n");
    printf("fmodf %a %a = %a\n", 5.0f, 3.0f, fmodf(5.0f, 3.0f));
    printf("fmodf %a %a = %a\n", -5.0f, 3.0f, fmodf(-5.0f, 3.0f));

    printf("remainderf %a %a = %a\n", 5.0f, 3.0f, remainderf(5.0f, 3.0f));
    printf("remainderf %a %a = %a\n", -5.0f, 3.0f, remainderf(-5.0f, 3.0f));

    printf("remquof %a %a = %a quo=%d\n", 5.0f, 3.0f, remquof(5.0f, 3.0f, &quo), quo);
    printf("remquof %a %a = %a quo=%d\n", -5.0f, 3.0f, remquof(-5.0f, 3.0f, &quo), quo);
}

/* ============================================================
 * Float manipulation functions
 * ============================================================ */
static void test_manip_float(void)
{
    printf("=== Float Manipulation ===\n");
    printf("copysignf %a %a = %a\n", 1.0f, -1.0f, copysignf(1.0f, -1.0f));
    printf("copysignf %a %a = %a\n", -1.0f, 1.0f, copysignf(-1.0f, 1.0f));

    printf("nanf = %a\n", nanf(""));

    printf("nextafterf %a %a = %a\n", 1.0f, 2.0f, nextafterf(1.0f, 2.0f));
    printf("nextafterf %a %a = %a\n", 1.0f, 0.0f, nextafterf(1.0f, 0.0f));

    printf("nexttowardf %a %La = %a\n", 1.0f, (long double)2.0, nexttowardf(1.0f, (long double)2.0));
    printf("nexttoward %a %La = %a\n", 1.0, (long double)2.0, nexttoward(1.0, (long double)2.0));
}

/* ============================================================
 * Float max, min, dim, fma
 * ============================================================ */
static void test_maxmin_float(void)
{
    printf("=== Float Max/Min/Dim/FMA ===\n");
    printf("fdimf %a %a = %a\n", 3.0f, 1.0f, fdimf(3.0f, 1.0f));
    printf("fdimf %a %a = %a\n", 1.0f, 3.0f, fdimf(1.0f, 3.0f));

    printf("fmaxf %a %a = %a\n", 1.0f, 2.0f, fmaxf(1.0f, 2.0f));
    printf("fmaxf %a %a = %a\n", -1.0f, 2.0f, fmaxf(-1.0f, 2.0f));

    printf("fminf %a %a = %a\n", 1.0f, 2.0f, fminf(1.0f, 2.0f));
    printf("fminf %a %a = %a\n", -1.0f, 2.0f, fminf(-1.0f, 2.0f));

    printf("fmaf %a %a %a = %a\n", 2.0f, 3.0f, 4.0f, fmaf(2.0f, 3.0f, 4.0f));
    printf("fmaf %a %a %a = %a\n", -1.0f, 2.0f, 1.0f, fmaf(-1.0f, 2.0f, 1.0f));
}

/* ============================================================
 * Classification macros (via internal functions)
 * ============================================================ */
static void test_classify(void)
{
    printf("=== Classification ===\n");
    printf("__fpclassifyd %a = %d\n", 0.0, __fpclassifyd(0.0));
    printf("__fpclassifyd %a = %d\n", 1.0, __fpclassifyd(1.0));
    printf("__fpclassifyd inf = %d\n", __fpclassifyd(1.0/0.0));
    printf("__fpclassifyd nan = %d\n", __fpclassifyd(0.0/0.0));
    printf("__fpclassifyd %a = %d\n", 5e-324, __fpclassifyd(5e-324));

    printf("__fpclassifyf %a = %d\n", 0.0f, __fpclassifyf(0.0f));
    printf("__fpclassifyf %a = %d\n", 1.0f, __fpclassifyf(1.0f));
    printf("__fpclassifyf inf = %d\n", __fpclassifyf(1.0f/0.0f));
    printf("__fpclassifyf nan = %d\n", __fpclassifyf(0.0f/0.0f));
    printf("__fpclassifyf %a = %d\n", 1e-45f, __fpclassifyf(1e-45f));

    printf("__signbitd %a = %d\n", 1.0, __signbitd(1.0));
    printf("__signbitd %a = %d\n", -1.0, __signbitd(-1.0));
    printf("__signbitd %a = %d\n", 0.0, __signbitd(0.0));
    printf("__signbitd %a = %d\n", -0.0, __signbitd(-0.0));

    printf("__signbitf %a = %d\n", 1.0f, __signbitf(1.0f));
    printf("__signbitf %a = %d\n", -1.0f, __signbitf(-1.0f));
    printf("__signbitf %a = %d\n", 0.0f, __signbitf(0.0f));
    printf("__signbitf %a = %d\n", -0.0f, __signbitf(-0.0f));
}

/* ============================================================
 * Complex double functions
 * ============================================================ */
static void test_complex_double(void)
{
    double complex z1 = CMPLX(1.0, 1.0);
    double complex z2 = CMPLX(0.0, 1.0);
    double complex z3 = CMPLX(0.5, 0.5);
    double complex res;

    printf("=== Complex Double Trig ===\n");
    res = cacos(z1);
    printf("cacos(%a+%ai) = %a+%ai\n", creal(z1), cimag(z1), creal(res), cimag(res));
    res = cacos(z2);
    printf("cacos(%a+%ai) = %a+%ai\n", creal(z2), cimag(z2), creal(res), cimag(res));

    res = casin(z1);
    printf("casin(%a+%ai) = %a+%ai\n", creal(z1), cimag(z1), creal(res), cimag(res));
    res = casin(z2);
    printf("casin(%a+%ai) = %a+%ai\n", creal(z2), cimag(z2), creal(res), cimag(res));

    res = catan(z1);
    printf("catan(%a+%ai) = %a+%ai\n", creal(z1), cimag(z1), creal(res), cimag(res));
    res = catan(z3);
    printf("catan(%a+%ai) = %a+%ai\n", creal(z3), cimag(z3), creal(res), cimag(res));

    res = ccos(z1);
    printf("ccos(%a+%ai) = %a+%ai\n", creal(z1), cimag(z1), creal(res), cimag(res));
    res = ccos(z2);
    printf("ccos(%a+%ai) = %a+%ai\n", creal(z2), cimag(z2), creal(res), cimag(res));

    res = csin(z1);
    printf("csin(%a+%ai) = %a+%ai\n", creal(z1), cimag(z1), creal(res), cimag(res));
    res = csin(z2);
    printf("csin(%a+%ai) = %a+%ai\n", creal(z2), cimag(z2), creal(res), cimag(res));

    res = ctan(z1);
    printf("ctan(%a+%ai) = %a+%ai\n", creal(z1), cimag(z1), creal(res), cimag(res));
    res = ctan(z3);
    printf("ctan(%a+%ai) = %a+%ai\n", creal(z3), cimag(z3), creal(res), cimag(res));

    printf("=== Complex Double Hyperbolic ===\n");
    res = cacosh(z1);
    printf("cacosh(%a+%ai) = %a+%ai\n", creal(z1), cimag(z1), creal(res), cimag(res));

    res = casinh(z1);
    printf("casinh(%a+%ai) = %a+%ai\n", creal(z1), cimag(z1), creal(res), cimag(res));

    res = catanh(z3);
    printf("catanh(%a+%ai) = %a+%ai\n", creal(z3), cimag(z3), creal(res), cimag(res));

    res = ccosh(z1);
    printf("ccosh(%a+%ai) = %a+%ai\n", creal(z1), cimag(z1), creal(res), cimag(res));

    res = csinh(z1);
    printf("csinh(%a+%ai) = %a+%ai\n", creal(z1), cimag(z1), creal(res), cimag(res));

    res = ctanh(z1);
    printf("ctanh(%a+%ai) = %a+%ai\n", creal(z1), cimag(z1), creal(res), cimag(res));

    printf("=== Complex Double Exp/Log ===\n");
    res = cexp(z1);
    printf("cexp(%a+%ai) = %a+%ai\n", creal(z1), cimag(z1), creal(res), cimag(res));
    res = cexp(z2);
    printf("cexp(%a+%ai) = %a+%ai\n", creal(z2), cimag(z2), creal(res), cimag(res));

    res = clog(z1);
    printf("clog(%a+%ai) = %a+%ai\n", creal(z1), cimag(z1), creal(res), cimag(res));
    res = clog(z2);
    printf("clog(%a+%ai) = %a+%ai\n", creal(z2), cimag(z2), creal(res), cimag(res));

    printf("=== Complex Double Power/Abs ===\n");
    printf("cabs(%a+%ai) = %a\n", creal(z1), cimag(z1), cabs(z1));
    printf("cabs(%a+%ai) = %a\n", creal(z2), cimag(z2), cabs(z2));

    res = cpow(z1, z2);
    printf("cpow(%a+%ai, %a+%ai) = %a+%ai\n",
           creal(z1), cimag(z1), creal(z2), cimag(z2), creal(res), cimag(res));

    res = csqrt(z1);
    printf("csqrt(%a+%ai) = %a+%ai\n", creal(z1), cimag(z1), creal(res), cimag(res));
    res = csqrt(CMPLX(-1.0, 0.0));
    printf("csqrt(%a+%ai) = %a+%ai\n", -1.0, 0.0, creal(res), cimag(res));

    printf("=== Complex Double Manipulation ===\n");
    printf("carg(%a+%ai) = %a\n", creal(z1), cimag(z1), carg(z1));
    printf("carg(%a+%ai) = %a\n", creal(z2), cimag(z2), carg(z2));

    printf("cimag(%a+%ai) = %a\n", creal(z1), cimag(z1), cimag(z1));

    res = conj(z1);
    printf("conj(%a+%ai) = %a+%ai\n", creal(z1), cimag(z1), creal(res), cimag(res));

    res = cproj(z1);
    printf("cproj(%a+%ai) = %a+%ai\n", creal(z1), cimag(z1), creal(res), cimag(res));
    res = cproj(CMPLX(1.0/0.0, 1.0));
    printf("cproj(inf+%ai) = %a+%ai\n", 1.0, creal(res), cimag(res));

    printf("creal(%a+%ai) = %a\n", creal(z1), cimag(z1), creal(z1));
}

/* ============================================================
 * Complex float functions
 * ============================================================ */
static void test_complex_float(void)
{
    float complex z1 = CMPLXF(1.0f, 1.0f);
    float complex z2 = CMPLXF(0.0f, 1.0f);
    float complex z3 = CMPLXF(0.5f, 0.5f);
    float complex res;

    printf("=== Complex Float Trig ===\n");
    res = cacosf(z1);
    printf("cacosf(%a+%ai) = %a+%ai\n", crealf(z1), cimagf(z1), crealf(res), cimagf(res));

    res = casinf(z1);
    printf("casinf(%a+%ai) = %a+%ai\n", crealf(z1), cimagf(z1), crealf(res), cimagf(res));

    res = catanf(z3);
    printf("catanf(%a+%ai) = %a+%ai\n", crealf(z3), cimagf(z3), crealf(res), cimagf(res));

    res = ccosf(z1);
    printf("ccosf(%a+%ai) = %a+%ai\n", crealf(z1), cimagf(z1), crealf(res), cimagf(res));

    res = csinf(z1);
    printf("csinf(%a+%ai) = %a+%ai\n", crealf(z1), cimagf(z1), crealf(res), cimagf(res));

    res = ctanf(z1);
    printf("ctanf(%a+%ai) = %a+%ai\n", crealf(z1), cimagf(z1), crealf(res), cimagf(res));

    printf("=== Complex Float Hyperbolic ===\n");
    res = cacoshf(z1);
    printf("cacoshf(%a+%ai) = %a+%ai\n", crealf(z1), cimagf(z1), crealf(res), cimagf(res));

    res = casinhf(z1);
    printf("casinhf(%a+%ai) = %a+%ai\n", crealf(z1), cimagf(z1), crealf(res), cimagf(res));

    res = catanhf(z3);
    printf("catanhf(%a+%ai) = %a+%ai\n", crealf(z3), cimagf(z3), crealf(res), cimagf(res));

    res = ccoshf(z1);
    printf("ccoshf(%a+%ai) = %a+%ai\n", crealf(z1), cimagf(z1), crealf(res), cimagf(res));

    res = csinhf(z1);
    printf("csinhf(%a+%ai) = %a+%ai\n", crealf(z1), cimagf(z1), crealf(res), cimagf(res));

    res = ctanhf(z1);
    printf("ctanhf(%a+%ai) = %a+%ai\n", crealf(z1), cimagf(z1), crealf(res), cimagf(res));

    printf("=== Complex Float Exp/Log ===\n");
    res = cexpf(z1);
    printf("cexpf(%a+%ai) = %a+%ai\n", crealf(z1), cimagf(z1), crealf(res), cimagf(res));

    res = clogf(z1);
    printf("clogf(%a+%ai) = %a+%ai\n", crealf(z1), cimagf(z1), crealf(res), cimagf(res));

    printf("=== Complex Float Power/Abs ===\n");
    printf("cabsf(%a+%ai) = %a\n", crealf(z1), cimagf(z1), cabsf(z1));

    res = cpowf(z1, z2);
    printf("cpowf(%a+%ai, %a+%ai) = %a+%ai\n",
           crealf(z1), cimagf(z1), crealf(z2), cimagf(z2), crealf(res), cimagf(res));

    res = csqrtf(z1);
    printf("csqrtf(%a+%ai) = %a+%ai\n", crealf(z1), cimagf(z1), crealf(res), cimagf(res));
    res = csqrtf(CMPLXF(-1.0f, 0.0f));
    printf("csqrtf(%a+%ai) = %a+%ai\n", -1.0f, 0.0f, crealf(res), cimagf(res));

    printf("=== Complex Float Manipulation ===\n");
    printf("cargf(%a+%ai) = %a\n", crealf(z1), cimagf(z1), cargf(z1));

    printf("cimagf(%a+%ai) = %a\n", crealf(z1), cimagf(z1), cimagf(z1));

    res = conjf(z1);
    printf("conjf(%a+%ai) = %a+%ai\n", crealf(z1), cimagf(z1), crealf(res), cimagf(res));

    res = cprojf(z1);
    printf("cprojf(%a+%ai) = %a+%ai\n", crealf(z1), cimagf(z1), crealf(res), cimagf(res));

    printf("crealf(%a+%ai) = %a\n", crealf(z1), cimagf(z1), crealf(z1));
}

/* ============================================================
 * Internal bridge functions (static functions exposed via bridge)
 * ============================================================ */
static void test_bridge_functions(void)
{
    double dx[2], dy[2];
    float  fx[2], fy[2];
    int    r;

    printf("=== Bridge: __rem_pio2_internal ===\n");
    /* Reduce x = 5.0 * pi/4 in scaled form: x[0] = 5.0, e0 = 0, nx = 1 */
    dx[0] = 5.0;
    r = bridge___rem_pio2_internal(dx, dy, 0, 1);
    printf("bridge___rem_pio2_internal([%a], e0=0, nx=1) = %d y=[%a, %a]\n",
           dx[0], r, dy[0], dy[1]);
    dx[0] = 1.0;
    r = bridge___rem_pio2_internal(dx, dy, 2, 1);
    printf("bridge___rem_pio2_internal([%a], e0=2, nx=1) = %d y=[%a, %a]\n",
           dx[0], r, dy[0], dy[1]);

    printf("=== Bridge: __tan ===\n");
    printf("bridge___tan %a %a %d = %a\n", 0.5, 0.0, 1, bridge___tan(0.5, 0.0, 1));
    printf("bridge___tan %a %a %d = %a\n", 0.5, 0.0, -1, bridge___tan(0.5, 0.0, -1));
    printf("bridge___tan %a %a %d = %a\n", 0.0, 0.0, 1, bridge___tan(0.0, 0.0, 1));
    printf("bridge___tan %a %a %d = %a\n", M_PI_4, 0.0, 1, bridge___tan(M_PI_4, 0.0, 1));

    printf("=== Bridge: __sin_pi ===\n");
    printf("bridge___sin_pi %a = %a\n", 0.5, bridge___sin_pi(0.5));
    printf("bridge___sin_pi %a = %a\n", 1.0, bridge___sin_pi(1.0));
    printf("bridge___sin_pi %a = %a\n", 0.25, bridge___sin_pi(0.25));
    printf("bridge___sin_pi %a = %a\n", -0.5, bridge___sin_pi(-0.5));

    printf("=== Bridge: __rem_pio2f_internal ===\n");
    fx[0] = 5.0f;
    r = bridge___rem_pio2f_internal(fx, fy, 0, 1);
    printf("bridge___rem_pio2f_internal([%a], e0=0, nx=1) = %d y=[%a, %a]\n",
           fx[0], r, fy[0], fy[1]);
    fx[0] = 1.0f;
    r = bridge___rem_pio2f_internal(fx, fy, 2, 1);
    printf("bridge___rem_pio2f_internal([%a], e0=2, nx=1) = %d y=[%a, %a]\n",
           fx[0], r, fy[0], fy[1]);

    printf("=== Bridge: __tanf ===\n");
    printf("bridge___tanf %a %a %d = %a\n", 0.5f, 0.0f, 1, bridge___tanf(0.5f, 0.0f, 1));
    printf("bridge___tanf %a %a %d = %a\n", 0.5f, 0.0f, -1, bridge___tanf(0.5f, 0.0f, -1));
    printf("bridge___tanf %a %a %d = %a\n", 0.0f, 0.0f, 1, bridge___tanf(0.0f, 0.0f, 1));

    printf("=== Bridge: __ctans ===\n");
    {
        double complex z = CMPLX(1.0, 1.0);
        printf("bridge___ctans(%a+%ai) = %a\n", creal(z), cimag(z), bridge___ctans(z));
        z = CMPLX(0.0, 0.5);
        printf("bridge___ctans(%a+%ai) = %a\n", creal(z), cimag(z), bridge___ctans(z));
    }

    printf("=== Bridge: __ctansf ===\n");
    {
        float complex z = CMPLXF(1.0f, 1.0f);
        printf("bridge___ctansf(%a+%ai) = %a\n", crealf(z), cimagf(z), bridge___ctansf(z));
        z = CMPLXF(0.0f, 0.5f);
        printf("bridge___ctansf(%a+%ai) = %a\n", crealf(z), cimagf(z), bridge___ctansf(z));
    }

    printf("=== Bridge: __sin_pif ===\n");
    printf("bridge___sin_pif %a = %a\n", 0.5f, bridge___sin_pif(0.5f));
    printf("bridge___sin_pif %a = %a\n", 1.0f, bridge___sin_pif(1.0f));
    printf("bridge___sin_pif %a = %a\n", 0.25f, bridge___sin_pif(0.25f));
    printf("bridge___sin_pif %a = %a\n", -0.5f, bridge___sin_pif(-0.5f));
}

/* ============================================================
 * Non-static internal functions (accessed via extern declarations)
 * ============================================================ */
static void test_internal_functions(void)
{
    double dy[2];
    float  fy[2];

    printf("=== Internal: __cos, __sin, __rem_pio2 ===\n");
    printf("__cos %a %a = %a\n", 0.5, 0.0, __cos(0.5, 0.0));
    printf("__cos %a %a = %a\n", 0.0, 0.0, __cos(0.0, 0.0));
    printf("__cos %a %a = %a\n", M_PI_4, 0.0, __cos(M_PI_4, 0.0));

    printf("__sin %a %a %d = %a\n", 0.5, 0.0, 0, __sin(0.5, 0.0, 0));
    printf("__sin %a %a %d = %a\n", 0.0, 0.0, 0, __sin(0.0, 0.0, 0));
    printf("__sin %a %a %d = %a\n", M_PI_4, 0.0, 0, __sin(M_PI_4, 0.0, 0));

    printf("__rem_pio2 %a = %d y=[%a, %a]\n", 1.0, __rem_pio2(1.0, dy), dy[0], dy[1]);
    printf("__rem_pio2 %a = %d y=[%a, %a]\n", M_PI, __rem_pio2(M_PI, dy), dy[0], dy[1]);
    printf("__rem_pio2 %a = %d y=[%a, %a]\n", 10.0, __rem_pio2(10.0, dy), dy[0], dy[1]);

    printf("=== Internal: __cosf, __sinf, __rem_pio2f ===\n");
    printf("__cosf %a %a = %a\n", 0.5f, 0.0f, __cosf(0.5f, 0.0f));
    printf("__cosf %a %a = %a\n", 0.0f, 0.0f, __cosf(0.0f, 0.0f));

    printf("__sinf %a %a %d = %a\n", 0.5f, 0.0f, 0, __sinf(0.5f, 0.0f, 0));
    printf("__sinf %a %a %d = %a\n", 0.0f, 0.0f, 0, __sinf(0.0f, 0.0f, 0));

    printf("__rem_pio2f %a = %d y=[%a, %a]\n", 1.0f, __rem_pio2f(1.0f, fy), fy[0], fy[1]);
    printf("__rem_pio2f %a = %d y=[%a, %a]\n", 10.0f, __rem_pio2f(10.0f, fy), fy[0], fy[1]);

    printf("=== Internal: __lgamma, __lgammaf ===\n");
    {
        int sgn;
        printf("__lgamma %a = %a sgn=%d\n", 1.0, __lgamma(1.0, &sgn), sgn);
        printf("__lgamma %a = %a sgn=%d\n", 0.5, __lgamma(0.5, &sgn), sgn);
        printf("__lgamma %a = %a sgn=%d\n", -0.5, __lgamma(-0.5, &sgn), sgn);

        printf("__lgammaf %a = %a sgn=%d\n", 1.0f, __lgammaf(1.0f, &sgn), sgn);
        printf("__lgammaf %a = %a sgn=%d\n", 0.5f, __lgammaf(0.5f, &sgn), sgn);
        printf("__lgammaf %a = %a sgn=%d\n", -0.5f, __lgammaf(-0.5f, &sgn), sgn);
    }

    printf("=== Internal: __ccoshsinh, __redupi ===\n");
    {
        double c, s;
        __ccoshsinh(0.0, &c, &s);
        printf("__ccoshsinh %a: cosh=%a sinh=%a\n", 0.0, c, s);
        __ccoshsinh(1.0, &c, &s);
        printf("__ccoshsinh %a: cosh=%a sinh=%a\n", 1.0, c, s);
        __ccoshsinh(-1.0, &c, &s);
        printf("__ccoshsinh %a: cosh=%a sinh=%a\n", -1.0, c, s);

        printf("__redupi %a = %a\n", M_PI, __redupi(M_PI));
        printf("__redupi %a = %a\n", 2*M_PI, __redupi(2*M_PI));
        printf("__redupi %a = %a\n", 0.5, __redupi(0.5));
    }

    printf("=== Internal: __ccoshsinhf, __redupif ===\n");
    {
        float c, s;
        __ccoshsinhf(0.0f, &c, &s);
        printf("__ccoshsinhf %a: cosh=%a sinh=%a\n", 0.0f, c, s);
        __ccoshsinhf(1.0f, &c, &s);
        printf("__ccoshsinhf %a: cosh=%a sinh=%a\n", 1.0f, c, s);

        printf("__redupif %a = %a\n", (float)M_PI, __redupif((float)M_PI));
        printf("__redupif %a = %a\n", 2.0f*(float)M_PI, __redupif(2.0f*(float)M_PI));
        printf("__redupif %a = %a\n", 0.5f, __redupif(0.5f));
    }
}

/* ============================================================
 * fenv functions
 * ============================================================ */
static void test_fenv(void)
{
    printf("=== fenv ===\n");
    printf("feclearexcept(0) = %d\n", feclearexcept(0));
    printf("feraiseexcept(0) = %d\n", feraiseexcept(0));
    printf("fegetround() = %d\n", fegetround());
    printf("fesetround(0) = %d\n", fesetround(0));
    printf("fetestexcept(0) = %d\n", fetestexcept(0));
    printf("fegetexceptflag(NULL,0) = %d\n", fegetexceptflag(NULL, 0));
    printf("fesetexceptflag(NULL,0) = %d\n", fesetexceptflag(NULL, 0));
    printf("fegetenv(NULL) = %d\n", fegetenv(NULL));
    printf("fesetenv(NULL) = %d\n", fesetenv(NULL));
    printf("feholdexcept(NULL) = %d\n", feholdexcept(NULL));
    printf("feupdateenv(NULL) = %d\n", feupdateenv(NULL));
}

/* ============================================================
 * main
 * ============================================================ */

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
    run_test("trig_double", test_trig_double, 2);
    run_test("hyperbolic_double", test_hyperbolic_double, 2);
    run_test("exp_log_double", test_exp_log_double, 2);
    run_test("power_double", test_power_double, 2);
    run_test("gamma_double", test_gamma_double, 2);
    run_test("nearest_int_double", test_nearest_int_double, 2);
    run_test("remainder_double", test_remainder_double, 2);
    run_test("manip_double", test_manip_double, 2);
    run_test("maxmin_double", test_maxmin_double, 2);
    run_test("bessel_double", test_bessel_double, 2);

    run_test("trig_float", test_trig_float, 2);
    run_test("hyperbolic_float", test_hyperbolic_float, 2);
    run_test("exp_log_float", test_exp_log_float, 2);
    run_test("power_float", test_power_float, 2);
    run_test("gamma_float", test_gamma_float, 2);
    run_test("nearest_int_float", test_nearest_int_float, 2);
    run_test("remainder_float", test_remainder_float, 2);
    run_test("manip_float", test_manip_float, 2);
    run_test("maxmin_float", test_maxmin_float, 2);

    run_test("classify", test_classify, 2);

    run_test("complex_double", test_complex_double, 2);
    run_test("complex_float", test_complex_float, 2);

    run_test("bridge_functions", test_bridge_functions, 2);
    run_test("internal_functions", test_internal_functions, 2);
    run_test("fenv", test_fenv, 2);

    return 0;
}
