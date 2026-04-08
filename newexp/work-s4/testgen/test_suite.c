/* test_suite.c — comprehensive test suite for libmcs math library.
 * Tests all public and bridged-static functions.
 * Results printed in %a hex float format for bitwise comparison.
 */

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <complex.h>
#include "test_bridge.h"

/* Internal function declarations not in public headers */
extern double __sin(double x, double y, int iy);
extern double __cos(double x, double y);
extern int32_t __rem_pio2(double x, double *y);
extern float __sinf(float x, float y, int iy);
extern float __cosf(float x, float y);
extern int32_t __rem_pio2f(float x, float *y);
extern void __ccoshsinh(double x, double *c, double *s);
extern double __redupi(double x);
extern void __ccoshsinhf(float x, float *c, float *s);
extern float __redupif(float x);
extern double __lgamma(double x, int *signgamp);
extern float __lgammaf(float x, int *signgamp);
extern int __fpclassifyd(double x);
extern int __fpclassifyf(float x);
extern int __signbitd(double x);
extern int __signbitf(float x);

/* ------------------------------------------------------------------ */
/* Trigonometric functions — double                                    */
/* ------------------------------------------------------------------ */

static void test_acos(void)
{
    printf("acos %a = %a\n", 0.5, acos(0.5));
    printf("acos %a = %a\n", 0.0, acos(0.0));
    printf("acos %a = %a\n", 1.0, acos(1.0));
    printf("acos %a = %a\n", -1.0, acos(-1.0));
}

static void test_asin(void)
{
    printf("asin %a = %a\n", 0.5, asin(0.5));
    printf("asin %a = %a\n", 0.0, asin(0.0));
    printf("asin %a = %a\n", 1.0, asin(1.0));
    printf("asin %a = %a\n", -0.5, asin(-0.5));
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
    printf("cos %a = %a\n", 3.141592653589793, cos(3.141592653589793));
}

static void test_sin(void)
{
    printf("sin %a = %a\n", 0.0, sin(0.0));
    printf("sin %a = %a\n", 1.0, sin(1.0));
    printf("sin %a = %a\n", 0.5, sin(0.5));
}

static void test_tan(void)
{
    printf("tan %a = %a\n", 0.0, tan(0.0));
    printf("tan %a = %a\n", 0.5, tan(0.5));
    printf("tan %a = %a\n", 1.0, tan(1.0));
}

/* ------------------------------------------------------------------ */
/* Trigonometric functions — float                                     */
/* ------------------------------------------------------------------ */

static void test_acosf(void)
{
    printf("acosf %a = %a\n", 0.5f, acosf(0.5f));
    printf("acosf %a = %a\n", 0.0f, acosf(0.0f));
    printf("acosf %a = %a\n", 1.0f, acosf(1.0f));
}

static void test_asinf(void)
{
    printf("asinf %a = %a\n", 0.5f, asinf(0.5f));
    printf("asinf %a = %a\n", 0.0f, asinf(0.0f));
    printf("asinf %a = %a\n", -0.5f, asinf(-0.5f));
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
    printf("tanf %a = %a\n", 0.5f, tanf(0.5f));
}

/* ------------------------------------------------------------------ */
/* Hyperbolic functions — double                                       */
/* ------------------------------------------------------------------ */

static void test_acosh(void)
{
    printf("acosh %a = %a\n", 1.0, acosh(1.0));
    printf("acosh %a = %a\n", 2.0, acosh(2.0));
    printf("acosh %a = %a\n", 10.0, acosh(10.0));
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
/* Hyperbolic functions — float                                        */
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
/* Exponential / logarithmic — double                                  */
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
    printf("exp2 %a = %a\n", 10.0, exp2(10.0));
}

static void test_expm1(void)
{
    printf("expm1 %a = %a\n", 0.0, expm1(0.0));
    printf("expm1 %a = %a\n", 1.0, expm1(1.0));
    printf("expm1 %a = %a\n", 1e-10, expm1(1e-10));
}

static void test_frexp(void)
{
    int e;
    double m;
    m = frexp(1.0, &e);
    printf("frexp %a = %a exp %d\n", 1.0, m, e);
    m = frexp(4.0, &e);
    printf("frexp %a = %a exp %d\n", 4.0, m, e);
    m = frexp(0.0, &e);
    printf("frexp %a = %a exp %d\n", 0.0, m, e);
}

static void test_ilogb(void)
{
    printf("ilogb %a = %d\n", 1.0, ilogb(1.0));
    printf("ilogb %a = %d\n", 2.0, ilogb(2.0));
    printf("ilogb %a = %d\n", 0.5, ilogb(0.5));
}

static void test_ldexp(void)
{
    printf("ldexp %a %d = %a\n", 1.0, 1, ldexp(1.0, 1));
    printf("ldexp %a %d = %a\n", 1.0, 10, ldexp(1.0, 10));
    printf("ldexp %a %d = %a\n", 1.5, -1, ldexp(1.5, -1));
}

static void test_log(void)
{
    printf("log %a = %a\n", 1.0, log(1.0));
    printf("log %a = %a\n", 2.718281828459045, log(2.718281828459045));
    printf("log %a = %a\n", 10.0, log(10.0));
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
    printf("log1p %a = %a\n", 1e-10, log1p(1e-10));
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
    double ipart;
    double f;
    f = modf(3.14, &ipart);
    printf("modf %a = %a ipart %a\n", 3.14, f, ipart);
    f = modf(-3.14, &ipart);
    printf("modf %a = %a ipart %a\n", -3.14, f, ipart);
    f = modf(2.0, &ipart);
    printf("modf %a = %a ipart %a\n", 2.0, f, ipart);
}

static void test_scalbn(void)
{
    printf("scalbn %a %d = %a\n", 1.0, 2, scalbn(1.0, 2));
    printf("scalbn %a %d = %a\n", 1.5, -1, scalbn(1.5, -1));
    printf("scalbn %a %d = %a\n", 1.0, 0, scalbn(1.0, 0));
}

static void test_scalbln(void)
{
    printf("scalbln %a %ld = %a\n", 1.0, 2L, scalbln(1.0, 2L));
    printf("scalbln %a %ld = %a\n", 1.5, -1L, scalbln(1.5, -1L));
}

/* ------------------------------------------------------------------ */
/* Exponential / logarithmic — float                                   */
/* ------------------------------------------------------------------ */

static void test_expf(void)
{
    printf("expf %a = %a\n", 0.0f, expf(0.0f));
    printf("expf %a = %a\n", 1.0f, expf(1.0f));
    printf("expf %a = %a\n", -1.0f, expf(-1.0f));
}

static void test_exp2f(void)
{
    printf("exp2f %a = %a\n", 0.0f, exp2f(0.0f));
    printf("exp2f %a = %a\n", 1.0f, exp2f(1.0f));
    printf("exp2f %a = %a\n", 10.0f, exp2f(10.0f));
}

static void test_expm1f(void)
{
    printf("expm1f %a = %a\n", 0.0f, expm1f(0.0f));
    printf("expm1f %a = %a\n", 1.0f, expm1f(1.0f));
}

static void test_frexpf(void)
{
    int e;
    float m;
    m = frexpf(1.0f, &e);
    printf("frexpf %a = %a exp %d\n", 1.0f, m, e);
    m = frexpf(4.0f, &e);
    printf("frexpf %a = %a exp %d\n", 4.0f, m, e);
}

static void test_ilogbf(void)
{
    printf("ilogbf %a = %d\n", 1.0f, ilogbf(1.0f));
    printf("ilogbf %a = %d\n", 2.0f, ilogbf(2.0f));
}

static void test_ldexpf(void)
{
    printf("ldexpf %a %d = %a\n", 1.0f, 1, ldexpf(1.0f, 1));
    printf("ldexpf %a %d = %a\n", 1.5f, -1, ldexpf(1.5f, -1));
}

static void test_logf(void)
{
    printf("logf %a = %a\n", 1.0f, logf(1.0f));
    printf("logf %a = %a\n", 10.0f, logf(10.0f));
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
    printf("log2f %a = %a\n", 2.0f, log2f(2.0f));
    printf("log2f %a = %a\n", 8.0f, log2f(8.0f));
}

static void test_logbf(void)
{
    printf("logbf %a = %a\n", 1.0f, logbf(1.0f));
    printf("logbf %a = %a\n", 2.0f, logbf(2.0f));
}

static void test_modff(void)
{
    float ipart;
    float f;
    f = modff(3.14f, &ipart);
    printf("modff %a = %a ipart %a\n", 3.14f, f, ipart);
    f = modff(-3.14f, &ipart);
    printf("modff %a = %a ipart %a\n", -3.14f, f, ipart);
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
/* Power and absolute-value — double                                   */
/* ------------------------------------------------------------------ */

static void test_cbrt(void)
{
    printf("cbrt %a = %a\n", 1.0, cbrt(1.0));
    printf("cbrt %a = %a\n", 8.0, cbrt(8.0));
    printf("cbrt %a = %a\n", -8.0, cbrt(-8.0));
    printf("cbrt %a = %a\n", 27.0, cbrt(27.0));
}

static void test_fabs(void)
{
    printf("fabs %a = %a\n", 1.0, fabs(1.0));
    printf("fabs %a = %a\n", -1.0, fabs(-1.0));
    printf("fabs %a = %a\n", 0.0, fabs(0.0));
}

static void test_hypot(void)
{
    printf("hypot %a %a = %a\n", 3.0, 4.0, hypot(3.0, 4.0));
    printf("hypot %a %a = %a\n", 1.0, 0.0, hypot(1.0, 0.0));
    printf("hypot %a %a = %a\n", 0.0, 0.0, hypot(0.0, 0.0));
}

static void test_pow(void)
{
    printf("pow %a %a = %a\n", 2.0, 10.0, pow(2.0, 10.0));
    printf("pow %a %a = %a\n", 1.0, 0.0, pow(1.0, 0.0));
    printf("pow %a %a = %a\n", 4.0, 0.5, pow(4.0, 0.5));
}

static void test_sqrt(void)
{
    printf("sqrt %a = %a\n", 4.0, sqrt(4.0));
    printf("sqrt %a = %a\n", 2.0, sqrt(2.0));
    printf("sqrt %a = %a\n", 0.0, sqrt(0.0));
}

/* ------------------------------------------------------------------ */
/* Power and absolute-value — float                                    */
/* ------------------------------------------------------------------ */

static void test_cbrtf(void)
{
    printf("cbrtf %a = %a\n", 1.0f, cbrtf(1.0f));
    printf("cbrtf %a = %a\n", 8.0f, cbrtf(8.0f));
    printf("cbrtf %a = %a\n", -8.0f, cbrtf(-8.0f));
}

static void test_fabsf(void)
{
    printf("fabsf %a = %a\n", 1.0f, fabsf(1.0f));
    printf("fabsf %a = %a\n", -1.0f, fabsf(-1.0f));
    printf("fabsf %a = %a\n", 0.0f, fabsf(0.0f));
}

static void test_hypotf(void)
{
    printf("hypotf %a %a = %a\n", 3.0f, 4.0f, hypotf(3.0f, 4.0f));
    printf("hypotf %a %a = %a\n", 1.0f, 0.0f, hypotf(1.0f, 0.0f));
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
/* Error and gamma — double                                            */
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
/* Error and gamma — float                                             */
/* ------------------------------------------------------------------ */

static void test_erff(void)
{
    printf("erff %a = %a\n", 0.0f, erff(0.0f));
    printf("erff %a = %a\n", 1.0f, erff(1.0f));
    printf("erff %a = %a\n", -1.0f, erff(-1.0f));
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
    printf("lgammaf %a = %a\n", 0.5f, lgammaf(0.5f));
}

static void test_tgammaf(void)
{
    printf("tgammaf %a = %a\n", 1.0f, tgammaf(1.0f));
    printf("tgammaf %a = %a\n", 2.0f, tgammaf(2.0f));
    printf("tgammaf %a = %a\n", 0.5f, tgammaf(0.5f));
}

/* ------------------------------------------------------------------ */
/* Nearest integer — double                                            */
/* ------------------------------------------------------------------ */

static void test_ceil(void)
{
    printf("ceil %a = %a\n", 1.2, ceil(1.2));
    printf("ceil %a = %a\n", -1.2, ceil(-1.2));
    printf("ceil %a = %a\n", 2.0, ceil(2.0));
}

static void test_floor(void)
{
    printf("floor %a = %a\n", 1.9, floor(1.9));
    printf("floor %a = %a\n", -1.1, floor(-1.1));
    printf("floor %a = %a\n", 2.0, floor(2.0));
}

static void test_nearbyint(void)
{
    printf("nearbyint %a = %a\n", 1.5, nearbyint(1.5));
    printf("nearbyint %a = %a\n", -1.5, nearbyint(-1.5));
    printf("nearbyint %a = %a\n", 2.0, nearbyint(2.0));
}

static void test_rint(void)
{
    printf("rint %a = %a\n", 1.5, rint(1.5));
    printf("rint %a = %a\n", -1.5, rint(-1.5));
    printf("rint %a = %a\n", 2.0, rint(2.0));
}

static void test_lrint(void)
{
    printf("lrint %a = %ld\n", 1.5, lrint(1.5));
    printf("lrint %a = %ld\n", -1.5, lrint(-1.5));
    printf("lrint %a = %ld\n", 2.0, lrint(2.0));
}

static void test_llrint(void)
{
    printf("llrint %a = %lld\n", 1.5, llrint(1.5));
    printf("llrint %a = %lld\n", -1.5, llrint(-1.5));
}

static void test_round(void)
{
    printf("round %a = %a\n", 1.5, round(1.5));
    printf("round %a = %a\n", -1.5, round(-1.5));
    printf("round %a = %a\n", 2.0, round(2.0));
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
    printf("trunc %a = %a\n", 1.9, trunc(1.9));
    printf("trunc %a = %a\n", -1.9, trunc(-1.9));
    printf("trunc %a = %a\n", 2.0, trunc(2.0));
}

/* ------------------------------------------------------------------ */
/* Nearest integer — float                                             */
/* ------------------------------------------------------------------ */

static void test_ceilf(void)
{
    printf("ceilf %a = %a\n", 1.2f, ceilf(1.2f));
    printf("ceilf %a = %a\n", -1.2f, ceilf(-1.2f));
}

static void test_floorf(void)
{
    printf("floorf %a = %a\n", 1.9f, floorf(1.9f));
    printf("floorf %a = %a\n", -1.1f, floorf(-1.1f));
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
    printf("truncf %a = %a\n", 1.9f, truncf(1.9f));
    printf("truncf %a = %a\n", -1.9f, truncf(-1.9f));
}

/* ------------------------------------------------------------------ */
/* Remainder — double                                                  */
/* ------------------------------------------------------------------ */

static void test_fmod(void)
{
    printf("fmod %a %a = %a\n", 5.0, 3.0, fmod(5.0, 3.0));
    printf("fmod %a %a = %a\n", -5.0, 3.0, fmod(-5.0, 3.0));
    printf("fmod %a %a = %a\n", 1.0, 1.0, fmod(1.0, 1.0));
}

static void test_remainder(void)
{
    printf("remainder %a %a = %a\n", 5.0, 3.0, remainder(5.0, 3.0));
    printf("remainder %a %a = %a\n", -5.0, 3.0, remainder(-5.0, 3.0));
}

static void test_remquo(void)
{
    int q;
    double r;
    r = remquo(5.0, 3.0, &q);
    printf("remquo %a %a = %a quo %d\n", 5.0, 3.0, r, q);
    r = remquo(-5.0, 3.0, &q);
    printf("remquo %a %a = %a quo %d\n", -5.0, 3.0, r, q);
}

/* ------------------------------------------------------------------ */
/* Remainder — float                                                   */
/* ------------------------------------------------------------------ */

static void test_fmodf(void)
{
    printf("fmodf %a %a = %a\n", 5.0f, 3.0f, fmodf(5.0f, 3.0f));
    printf("fmodf %a %a = %a\n", -5.0f, 3.0f, fmodf(-5.0f, 3.0f));
}

static void test_remainderf(void)
{
    printf("remainderf %a %a = %a\n", 5.0f, 3.0f, remainderf(5.0f, 3.0f));
    printf("remainderf %a %a = %a\n", -5.0f, 3.0f, remainderf(-5.0f, 3.0f));
}

static void test_remquof(void)
{
    int q;
    float r;
    r = remquof(5.0f, 3.0f, &q);
    printf("remquof %a %a = %a quo %d\n", 5.0f, 3.0f, r, q);
}

/* ------------------------------------------------------------------ */
/* Manipulation — double                                               */
/* ------------------------------------------------------------------ */

static void test_copysign(void)
{
    printf("copysign %a %a = %a\n", 1.0, -2.0, copysign(1.0, -2.0));
    printf("copysign %a %a = %a\n", -1.0, 2.0, copysign(-1.0, 2.0));
    printf("copysign %a %a = %a\n", 0.0, -1.0, copysign(0.0, -1.0));
}

static void test_nan(void)
{
    double v = nan("");
    printf("nan isnan = %d\n", v != v ? 1 : 0);
}

static void test_nextafter(void)
{
    printf("nextafter %a %a = %a\n", 0.0, 1.0, nextafter(0.0, 1.0));
    printf("nextafter %a %a = %a\n", 1.0, 0.0, nextafter(1.0, 0.0));
    printf("nextafter %a %a = %a\n", 1.0, 1.0, nextafter(1.0, 1.0));
}

/* ------------------------------------------------------------------ */
/* Manipulation — float                                                */
/* ------------------------------------------------------------------ */

static void test_copysignf(void)
{
    printf("copysignf %a %a = %a\n", 1.0f, -2.0f, copysignf(1.0f, -2.0f));
    printf("copysignf %a %a = %a\n", -1.0f, 2.0f, copysignf(-1.0f, 2.0f));
}

static void test_nanf(void)
{
    float v = nanf("");
    printf("nanf isnan = %d\n", v != v ? 1 : 0);
}

static void test_nextafterf(void)
{
    printf("nextafterf %a %a = %a\n", 0.0f, 1.0f, nextafterf(0.0f, 1.0f));
    printf("nextafterf %a %a = %a\n", 1.0f, 0.0f, nextafterf(1.0f, 0.0f));
}

/* ------------------------------------------------------------------ */
/* Max, min, positive difference — double                              */
/* ------------------------------------------------------------------ */

static void test_fdim(void)
{
    printf("fdim %a %a = %a\n", 3.0, 2.0, fdim(3.0, 2.0));
    printf("fdim %a %a = %a\n", 2.0, 3.0, fdim(2.0, 3.0));
}

static void test_fmax(void)
{
    printf("fmax %a %a = %a\n", 3.0, 2.0, fmax(3.0, 2.0));
    printf("fmax %a %a = %a\n", -3.0, -2.0, fmax(-3.0, -2.0));
}

static void test_fmin(void)
{
    printf("fmin %a %a = %a\n", 3.0, 2.0, fmin(3.0, 2.0));
    printf("fmin %a %a = %a\n", -3.0, -2.0, fmin(-3.0, -2.0));
}

/* ------------------------------------------------------------------ */
/* Max, min, positive difference — float                               */
/* ------------------------------------------------------------------ */

static void test_fdimf(void)
{
    printf("fdimf %a %a = %a\n", 3.0f, 2.0f, fdimf(3.0f, 2.0f));
    printf("fdimf %a %a = %a\n", 2.0f, 3.0f, fdimf(2.0f, 3.0f));
}

static void test_fmaxf(void)
{
    printf("fmaxf %a %a = %a\n", 3.0f, 2.0f, fmaxf(3.0f, 2.0f));
    printf("fmaxf %a %a = %a\n", -3.0f, -2.0f, fmaxf(-3.0f, -2.0f));
}

static void test_fminf(void)
{
    printf("fminf %a %a = %a\n", 3.0f, 2.0f, fminf(3.0f, 2.0f));
    printf("fminf %a %a = %a\n", -3.0f, -2.0f, fminf(-3.0f, -2.0f));
}

/* ------------------------------------------------------------------ */
/* FMA — double and float                                              */
/* ------------------------------------------------------------------ */

static void test_fma(void)
{
    printf("fma %a %a %a = %a\n", 2.0, 3.0, 4.0, fma(2.0, 3.0, 4.0));
    printf("fma %a %a %a = %a\n", 1.0, 1.0, 1.0, fma(1.0, 1.0, 1.0));
    printf("fma %a %a %a = %a\n", -2.0, 3.0, 1.0, fma(-2.0, 3.0, 1.0));
}

static void test_fmaf(void)
{
    printf("fmaf %a %a %a = %a\n", 2.0f, 3.0f, 4.0f, fmaf(2.0f, 3.0f, 4.0f));
    printf("fmaf %a %a %a = %a\n", 1.0f, 1.0f, 1.0f, fmaf(1.0f, 1.0f, 1.0f));
}

/* ------------------------------------------------------------------ */
/* Bessel functions                                                    */
/* ------------------------------------------------------------------ */

static void test_j0(void)
{
    printf("j0 %a = %a\n", 0.0, j0(0.0));
    printf("j0 %a = %a\n", 1.0, j0(1.0));
    printf("j0 %a = %a\n", 2.0, j0(2.0));
}

static void test_j1(void)
{
    printf("j1 %a = %a\n", 0.0, j1(0.0));
    printf("j1 %a = %a\n", 1.0, j1(1.0));
    printf("j1 %a = %a\n", 2.0, j1(2.0));
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
/* Classification functions                                            */
/* ------------------------------------------------------------------ */

static void test_fpclassifyd(void)
{
    printf("__fpclassifyd %a = %d\n", 1.0, __fpclassifyd(1.0));
    printf("__fpclassifyd %a = %d\n", 0.0, __fpclassifyd(0.0));
    printf("__fpclassifyd inf = %d\n", __fpclassifyd(1.0 / 0.0));
}

static void test_fpclassifyf(void)
{
    printf("__fpclassifyf %a = %d\n", 1.0f, __fpclassifyf(1.0f));
    printf("__fpclassifyf %a = %d\n", 0.0f, __fpclassifyf(0.0f));
    printf("__fpclassifyf inf = %d\n", __fpclassifyf(1.0f / 0.0f));
}

static void test_signbitd(void)
{
    printf("__signbitd %a = %d\n", 1.0, __signbitd(1.0));
    printf("__signbitd %a = %d\n", -1.0, __signbitd(-1.0));
    printf("__signbitd %a = %d\n", 0.0, __signbitd(0.0));
}

static void test_signbitf(void)
{
    printf("__signbitf %a = %d\n", 1.0f, __signbitf(1.0f));
    printf("__signbitf %a = %d\n", -1.0f, __signbitf(-1.0f));
    printf("__signbitf %a = %d\n", 0.0f, __signbitf(0.0f));
}

/* ------------------------------------------------------------------ */
/* Internal trig helpers — double                                      */
/* ------------------------------------------------------------------ */

static void test_cos_internal(void)
{
    printf("__cos %a %a = %a\n", 0.5, 0.0, __cos(0.5, 0.0));
    printf("__cos %a %a = %a\n", 0.0, 0.0, __cos(0.0, 0.0));
    printf("__cos %a %a = %a\n", 0.3, 0.0, __cos(0.3, 0.0));
}

static void test_sin_internal(void)
{
    printf("__sin %a %a %d = %a\n", 0.5, 0.0, 0, __sin(0.5, 0.0, 0));
    printf("__sin %a %a %d = %a\n", 0.0, 0.0, 0, __sin(0.0, 0.0, 0));
    printf("__sin %a %a %d = %a\n", 0.3, 0.0, 1, __sin(0.3, 0.0, 1));
}

static void test_rem_pio2(void)
{
    double y[2];
    int n;
    n = __rem_pio2(1.5, y);
    printf("__rem_pio2 %a = %d y0 %a y1 %a\n", 1.5, n, y[0], y[1]);
    n = __rem_pio2(4.0, y);
    printf("__rem_pio2 %a = %d y0 %a y1 %a\n", 4.0, n, y[0], y[1]);
    n = __rem_pio2(1000.0, y);
    printf("__rem_pio2 %a = %d y0 %a y1 %a\n", 1000.0, n, y[0], y[1]);
}

/* ------------------------------------------------------------------ */
/* Internal trig helpers — float                                       */
/* ------------------------------------------------------------------ */

static void test_cosf_internal(void)
{
    printf("__cosf %a %a = %a\n", 0.5f, 0.0f, __cosf(0.5f, 0.0f));
    printf("__cosf %a %a = %a\n", 0.0f, 0.0f, __cosf(0.0f, 0.0f));
}

static void test_sinf_internal(void)
{
    printf("__sinf %a %a %d = %a\n", 0.5f, 0.0f, 0, __sinf(0.5f, 0.0f, 0));
    printf("__sinf %a %a %d = %a\n", 0.0f, 0.0f, 0, __sinf(0.0f, 0.0f, 0));
}

static void test_rem_pio2f(void)
{
    float y[2];
    int n;
    n = __rem_pio2f(1.5f, y);
    printf("__rem_pio2f %a = %d y0 %a y1 %a\n", 1.5f, n, y[0], y[1]);
    n = __rem_pio2f(4.0f, y);
    printf("__rem_pio2f %a = %d y0 %a y1 %a\n", 4.0f, n, y[0], y[1]);
}

/* ------------------------------------------------------------------ */
/* Internal gamma helpers                                              */
/* ------------------------------------------------------------------ */

static void test_lgamma_internal(void)
{
    int signgam;
    double v;
    v = __lgamma(1.0, &signgam);
    printf("__lgamma %a = %a sign %d\n", 1.0, v, signgam);
    v = __lgamma(2.0, &signgam);
    printf("__lgamma %a = %a sign %d\n", 2.0, v, signgam);
    v = __lgamma(0.5, &signgam);
    printf("__lgamma %a = %a sign %d\n", 0.5, v, signgam);
}

static void test_lgammaf_internal(void)
{
    int signgam;
    float v;
    v = __lgammaf(1.0f, &signgam);
    printf("__lgammaf %a = %a sign %d\n", 1.0f, v, signgam);
    v = __lgammaf(2.0f, &signgam);
    printf("__lgammaf %a = %a sign %d\n", 2.0f, v, signgam);
}

/* ------------------------------------------------------------------ */
/* Complex functions — double                                          */
/* ------------------------------------------------------------------ */

static void test_cabs(void)
{
    double complex z = CMPLX(3.0, 4.0);
    printf("cabs %a+%ai = %a\n", creal(z), cimag(z), cabs(z));
    z = CMPLX(0.0, 0.0);
    printf("cabs %a+%ai = %a\n", creal(z), cimag(z), cabs(z));
    z = CMPLX(1.0, 0.0);
    printf("cabs %a+%ai = %a\n", creal(z), cimag(z), cabs(z));
}

static void test_cacos(void)
{
    double complex z = CMPLX(0.5, 0.0);
    double complex w = cacos(z);
    printf("cacos %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(0.0, 1.0);
    w = cacos(z);
    printf("cacos %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
}

static void test_cacosh(void)
{
    double complex z = CMPLX(1.0, 0.0);
    double complex w = cacosh(z);
    printf("cacosh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(2.0, 0.0);
    w = cacosh(z);
    printf("cacosh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
}

static void test_carg(void)
{
    double complex z = CMPLX(1.0, 0.0);
    printf("carg %a+%ai = %a\n", creal(z), cimag(z), carg(z));
    z = CMPLX(0.0, 1.0);
    printf("carg %a+%ai = %a\n", creal(z), cimag(z), carg(z));
    z = CMPLX(-1.0, 0.0);
    printf("carg %a+%ai = %a\n", creal(z), cimag(z), carg(z));
}

static void test_casin(void)
{
    double complex z = CMPLX(0.5, 0.0);
    double complex w = casin(z);
    printf("casin %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(0.0, 1.0);
    w = casin(z);
    printf("casin %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
}

static void test_casinh(void)
{
    double complex z = CMPLX(1.0, 0.0);
    double complex w = casinh(z);
    printf("casinh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(0.0, 1.0);
    w = casinh(z);
    printf("casinh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
}

static void test_catan(void)
{
    double complex z = CMPLX(1.0, 0.0);
    double complex w = catan(z);
    printf("catan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(0.0, 0.5);
    w = catan(z);
    printf("catan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
}

static void test_catanh(void)
{
    double complex z = CMPLX(0.5, 0.0);
    double complex w = catanh(z);
    printf("catanh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(0.0, 1.0);
    w = catanh(z);
    printf("catanh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
}

static void test_ccos(void)
{
    double complex z = CMPLX(0.0, 0.0);
    double complex w = ccos(z);
    printf("ccos %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(1.0, 1.0);
    w = ccos(z);
    printf("ccos %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
}

static void test_ccosh(void)
{
    double complex z = CMPLX(0.0, 0.0);
    double complex w = ccosh(z);
    printf("ccosh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(1.0, 1.0);
    w = ccosh(z);
    printf("ccosh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
}

static void test_ccoshsinh(void)
{
    double c, s;
    __ccoshsinh(0.0, &c, &s);
    printf("__ccoshsinh %a c=%a s=%a\n", 0.0, c, s);
    __ccoshsinh(1.0, &c, &s);
    printf("__ccoshsinh %a c=%a s=%a\n", 1.0, c, s);
    __ccoshsinh(0.3, &c, &s);
    printf("__ccoshsinh %a c=%a s=%a\n", 0.3, c, s);
}

static void test_cexp(void)
{
    double complex z = CMPLX(0.0, 0.0);
    double complex w = cexp(z);
    printf("cexp %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(1.0, 0.0);
    w = cexp(z);
    printf("cexp %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(0.0, 1.0);
    w = cexp(z);
    printf("cexp %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
}

static void test_cimag(void)
{
    double complex z = CMPLX(3.0, 4.0);
    printf("cimag %a+%ai = %a\n", creal(z), cimag(z), cimag(z));
    z = CMPLX(0.0, -1.0);
    printf("cimag %a+%ai = %a\n", creal(z), cimag(z), cimag(z));
}

static void test_clog(void)
{
    double complex z = CMPLX(1.0, 0.0);
    double complex w = clog(z);
    printf("clog %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(0.0, 1.0);
    w = clog(z);
    printf("clog %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
}

static void test_conj(void)
{
    double complex z = CMPLX(3.0, 4.0);
    double complex w = conj(z);
    printf("conj %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(-1.0, 2.0);
    w = conj(z);
    printf("conj %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
}

static void test_cpow(void)
{
    double complex z = CMPLX(1.0, 0.0);
    double complex w_exp = CMPLX(2.0, 0.0);
    double complex w = cpow(z, w_exp);
    printf("cpow %a+%ai %a+%ai = %a+%ai\n",
           creal(z), cimag(z), creal(w_exp), cimag(w_exp), creal(w), cimag(w));
    z = CMPLX(1.0, 1.0);
    w_exp = CMPLX(2.0, 0.0);
    w = cpow(z, w_exp);
    printf("cpow %a+%ai %a+%ai = %a+%ai\n",
           creal(z), cimag(z), creal(w_exp), cimag(w_exp), creal(w), cimag(w));
}

static void test_cproj(void)
{
    double complex z = CMPLX(1.0, 2.0);
    double complex w = cproj(z);
    printf("cproj %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
}

static void test_creal(void)
{
    double complex z = CMPLX(3.0, 4.0);
    printf("creal %a+%ai = %a\n", creal(z), cimag(z), creal(z));
    z = CMPLX(-2.0, 1.0);
    printf("creal %a+%ai = %a\n", creal(z), cimag(z), creal(z));
}

static void test_csin(void)
{
    double complex z = CMPLX(0.0, 0.0);
    double complex w = csin(z);
    printf("csin %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(1.0, 1.0);
    w = csin(z);
    printf("csin %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
}

static void test_csinh(void)
{
    double complex z = CMPLX(0.0, 0.0);
    double complex w = csinh(z);
    printf("csinh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(1.0, 1.0);
    w = csinh(z);
    printf("csinh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
}

static void test_csqrt(void)
{
    double complex z = CMPLX(4.0, 0.0);
    double complex w = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(0.0, 4.0);
    w = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
}

static void test_ctan(void)
{
    double complex z = CMPLX(0.0, 0.0);
    double complex w = ctan(z);
    printf("ctan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(1.0, 1.0);
    w = ctan(z);
    printf("ctan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
}

static void test_ctanh(void)
{
    double complex z = CMPLX(0.0, 0.0);
    double complex w = ctanh(z);
    printf("ctanh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(1.0, 1.0);
    w = ctanh(z);
    printf("ctanh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
}

static void test_redupi(void)
{
    printf("__redupi %a = %a\n", 0.0, __redupi(0.0));
    printf("__redupi %a = %a\n", 3.141592653589793, __redupi(3.141592653589793));
    printf("__redupi %a = %a\n", 6.283185307179586, __redupi(6.283185307179586));
}

/* ------------------------------------------------------------------ */
/* Complex functions — float                                           */
/* ------------------------------------------------------------------ */

static void test_cabsf(void)
{
    float complex z = CMPLXF(3.0f, 4.0f);
    printf("cabsf %a+%ai = %a\n", crealf(z), cimagf(z), cabsf(z));
    z = CMPLXF(0.0f, 0.0f);
    printf("cabsf %a+%ai = %a\n", crealf(z), cimagf(z), cabsf(z));
}

static void test_cacosf(void)
{
    float complex z = CMPLXF(0.5f, 0.0f);
    float complex w = cacosf(z);
    printf("cacosf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
}

static void test_cacoshf(void)
{
    float complex z = CMPLXF(1.0f, 0.0f);
    float complex w = cacoshf(z);
    printf("cacoshf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
}

static void test_cargf(void)
{
    float complex z = CMPLXF(1.0f, 0.0f);
    printf("cargf %a+%ai = %a\n", crealf(z), cimagf(z), cargf(z));
    z = CMPLXF(0.0f, 1.0f);
    printf("cargf %a+%ai = %a\n", crealf(z), cimagf(z), cargf(z));
}

static void test_casinf(void)
{
    float complex z = CMPLXF(0.5f, 0.0f);
    float complex w = casinf(z);
    printf("casinf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
}

static void test_casinhf(void)
{
    float complex z = CMPLXF(1.0f, 0.0f);
    float complex w = casinhf(z);
    printf("casinhf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
}

static void test_catanf(void)
{
    float complex z = CMPLXF(1.0f, 0.0f);
    float complex w = catanf(z);
    printf("catanf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
}

static void test_catanhf(void)
{
    float complex z = CMPLXF(0.5f, 0.0f);
    float complex w = catanhf(z);
    printf("catanhf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
}

static void test_ccosf(void)
{
    float complex z = CMPLXF(0.0f, 0.0f);
    float complex w = ccosf(z);
    printf("ccosf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
    z = CMPLXF(1.0f, 1.0f);
    w = ccosf(z);
    printf("ccosf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
}

static void test_ccoshf(void)
{
    float complex z = CMPLXF(0.0f, 0.0f);
    float complex w = ccoshf(z);
    printf("ccoshf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
    z = CMPLXF(1.0f, 1.0f);
    w = ccoshf(z);
    printf("ccoshf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
}

static void test_ccoshsinhf(void)
{
    float c, s;
    __ccoshsinhf(0.0f, &c, &s);
    printf("__ccoshsinhf %a c=%a s=%a\n", 0.0f, c, s);
    __ccoshsinhf(1.0f, &c, &s);
    printf("__ccoshsinhf %a c=%a s=%a\n", 1.0f, c, s);
    __ccoshsinhf(0.3f, &c, &s);
    printf("__ccoshsinhf %a c=%a s=%a\n", 0.3f, c, s);
}

static void test_cexpf(void)
{
    float complex z = CMPLXF(0.0f, 0.0f);
    float complex w = cexpf(z);
    printf("cexpf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
    z = CMPLXF(1.0f, 0.0f);
    w = cexpf(z);
    printf("cexpf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
}

static void test_cimagf(void)
{
    float complex z = CMPLXF(3.0f, 4.0f);
    printf("cimagf %a+%ai = %a\n", crealf(z), cimagf(z), cimagf(z));
    z = CMPLXF(0.0f, -1.0f);
    printf("cimagf %a+%ai = %a\n", crealf(z), cimagf(z), cimagf(z));
}

static void test_clogf(void)
{
    float complex z = CMPLXF(1.0f, 0.0f);
    float complex w = clogf(z);
    printf("clogf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
    z = CMPLXF(0.0f, 1.0f);
    w = clogf(z);
    printf("clogf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
}

static void test_conjf(void)
{
    float complex z = CMPLXF(3.0f, 4.0f);
    float complex w = conjf(z);
    printf("conjf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
}

static void test_copysignf_test(void)
{
    /* Already tested as test_copysignf above — no-op */
}

static void test_cpowf(void)
{
    float complex z = CMPLXF(1.0f, 0.0f);
    float complex w_exp = CMPLXF(2.0f, 0.0f);
    float complex w = cpowf(z, w_exp);
    printf("cpowf %a+%ai %a+%ai = %a+%ai\n",
           crealf(z), cimagf(z), crealf(w_exp), cimagf(w_exp), crealf(w), cimagf(w));
}

static void test_cprojf(void)
{
    float complex z = CMPLXF(1.0f, 2.0f);
    float complex w = cprojf(z);
    printf("cprojf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
}

static void test_crealf(void)
{
    float complex z = CMPLXF(3.0f, 4.0f);
    printf("crealf %a+%ai = %a\n", crealf(z), cimagf(z), crealf(z));
}

static void test_csinf(void)
{
    float complex z = CMPLXF(0.0f, 0.0f);
    float complex w = csinf(z);
    printf("csinf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
    z = CMPLXF(1.0f, 1.0f);
    w = csinf(z);
    printf("csinf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
}

static void test_csinhf(void)
{
    float complex z = CMPLXF(0.0f, 0.0f);
    float complex w = csinhf(z);
    printf("csinhf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
    z = CMPLXF(1.0f, 1.0f);
    w = csinhf(z);
    printf("csinhf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
}

static void test_csqrtf(void)
{
    float complex z = CMPLXF(4.0f, 0.0f);
    float complex w = csqrtf(z);
    printf("csqrtf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
    z = CMPLXF(0.0f, 4.0f);
    w = csqrtf(z);
    printf("csqrtf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
}

static void test_ctanf(void)
{
    float complex z = CMPLXF(0.0f, 0.0f);
    float complex w = ctanf(z);
    printf("ctanf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
    z = CMPLXF(1.0f, 1.0f);
    w = ctanf(z);
    printf("ctanf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
}

static void test_ctanhf(void)
{
    float complex z = CMPLXF(0.0f, 0.0f);
    float complex w = ctanhf(z);
    printf("ctanhf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
    z = CMPLXF(1.0f, 1.0f);
    w = ctanhf(z);
    printf("ctanhf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
}

static void test_redupif(void)
{
    printf("__redupif %a = %a\n", 0.0f, __redupif(0.0f));
    printf("__redupif %a = %a\n", 3.141592653589793f, __redupif(3.141592653589793f));
    printf("__redupif %a = %a\n", 6.283185307179586f, __redupif(6.283185307179586f));
}

/* ------------------------------------------------------------------ */
/* Static bridge functions                                             */
/* ------------------------------------------------------------------ */

static void test_bridge_rem_pio2_internal(void)
{
    double x[3] = { 0x1.921fb4p+0, 0.0, 0.0 };
    double y[2];
    int n = bridge___rem_pio2_internal(x, y, -1, 1);
    printf("bridge___rem_pio2_internal n=%d y0=%a y1=%a\n", n, y[0], y[1]);

    x[0] = 0x1.8p+0;
    x[1] = 0.0;
    n = bridge___rem_pio2_internal(x, y, 0, 1);
    printf("bridge___rem_pio2_internal n=%d y0=%a y1=%a\n", n, y[0], y[1]);
}

static void test_bridge_tan(void)
{
    printf("bridge___tan %a %a %d = %a\n", 0.5, 0.0, 1, bridge___tan(0.5, 0.0, 1));
    printf("bridge___tan %a %a %d = %a\n", 0.0, 0.0, 1, bridge___tan(0.0, 0.0, 1));
    printf("bridge___tan %a %a %d = %a\n", 0.3, 0.0, 0, bridge___tan(0.3, 0.0, 0));
}

static void test_bridge_sin_pi(void)
{
    printf("bridge___sin_pi %a = %a\n", 0.5, bridge___sin_pi(0.5));
    printf("bridge___sin_pi %a = %a\n", 1.0, bridge___sin_pi(1.0));
    printf("bridge___sin_pi %a = %a\n", 0.25, bridge___sin_pi(0.25));
    printf("bridge___sin_pi %a = %a\n", 2.0, bridge___sin_pi(2.0));
}

static void test_bridge_rem_pio2f_internal(void)
{
    float x[3] = { 0x1.921fb4p+0f, 0.0f, 0.0f };
    float y[2];
    int n = bridge___rem_pio2f_internal(x, y, -1, 1);
    printf("bridge___rem_pio2f_internal n=%d y0=%a y1=%a\n", n, y[0], y[1]);

    x[0] = 0x1.8p+0f;
    x[1] = 0.0f;
    n = bridge___rem_pio2f_internal(x, y, 0, 1);
    printf("bridge___rem_pio2f_internal n=%d y0=%a y1=%a\n", n, y[0], y[1]);
}

static void test_bridge_tanf(void)
{
    printf("bridge___tanf %a %a %d = %a\n", 0.5f, 0.0f, 1, bridge___tanf(0.5f, 0.0f, 1));
    printf("bridge___tanf %a %a %d = %a\n", 0.0f, 0.0f, 1, bridge___tanf(0.0f, 0.0f, 1));
    printf("bridge___tanf %a %a %d = %a\n", 0.3f, 0.0f, 0, bridge___tanf(0.3f, 0.0f, 0));
}

static void test_bridge_ctans(void)
{
    double complex z = CMPLX(0.1, 0.1);
    double r = bridge___ctans(z);
    printf("bridge___ctans %a+%ai = %a\n", creal(z), cimag(z), r);
    z = CMPLX(0.01, 0.05);
    r = bridge___ctans(z);
    printf("bridge___ctans %a+%ai = %a\n", creal(z), cimag(z), r);
}

static void test_bridge_ctansf(void)
{
    float complex z = CMPLXF(0.1f, 0.1f);
    float r = bridge___ctansf(z);
    printf("bridge___ctansf %a+%ai = %a\n", crealf(z), cimagf(z), r);
    z = CMPLXF(0.01f, 0.05f);
    r = bridge___ctansf(z);
    printf("bridge___ctansf %a+%ai = %a\n", crealf(z), cimagf(z), r);
}

static void test_bridge_sin_pif(void)
{
    printf("bridge___sin_pif %a = %a\n", 0.5f, bridge___sin_pif(0.5f));
    printf("bridge___sin_pif %a = %a\n", 1.0f, bridge___sin_pif(1.0f));
    printf("bridge___sin_pif %a = %a\n", 0.25f, bridge___sin_pif(0.25f));
    printf("bridge___sin_pif %a = %a\n", 2.0f, bridge___sin_pif(2.0f));
}

/* ------------------------------------------------------------------ */
/* Long double and nexttoward — conditionally compiled                 */
/* ------------------------------------------------------------------ */

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

static void test_long_double_trig(void)
{
    printf("acosl %La = %La\n", (long double)0.5, acosl((long double)0.5));
    printf("asinl %La = %La\n", (long double)0.5, asinl((long double)0.5));
    printf("atanl %La = %La\n", (long double)1.0, atanl((long double)1.0));
    printf("atan2l %La %La = %La\n", (long double)1.0, (long double)1.0,
           atan2l((long double)1.0, (long double)1.0));
    printf("cosl %La = %La\n", (long double)1.0, cosl((long double)1.0));
    printf("sinl %La = %La\n", (long double)1.0, sinl((long double)1.0));
    printf("tanl %La = %La\n", (long double)0.5, tanl((long double)0.5));
}

static void test_long_double_hyperbolic(void)
{
    printf("acoshl %La = %La\n", (long double)2.0, acoshl((long double)2.0));
    printf("asinhl %La = %La\n", (long double)1.0, asinhl((long double)1.0));
    printf("atanhl %La = %La\n", (long double)0.5, atanhl((long double)0.5));
    printf("coshl %La = %La\n", (long double)1.0, coshl((long double)1.0));
    printf("sinhl %La = %La\n", (long double)1.0, sinhl((long double)1.0));
    printf("tanhl %La = %La\n", (long double)1.0, tanhl((long double)1.0));
}

static void test_long_double_exp_log(void)
{
    printf("expl %La = %La\n", (long double)1.0, expl((long double)1.0));
    printf("exp2l %La = %La\n", (long double)2.0, exp2l((long double)2.0));
    printf("expm1l %La = %La\n", (long double)1.0, expm1l((long double)1.0));
    int e;
    long double m = frexpl((long double)4.0, &e);
    printf("frexpl %La = %La exp %d\n", (long double)4.0, m, e);
    printf("ilogbl %La = %d\n", (long double)2.0, ilogbl((long double)2.0));
    printf("ldexpl %La %d = %La\n", (long double)1.0, 2, ldexpl((long double)1.0, 2));
    printf("logl %La = %La\n", (long double)1.0, logl((long double)1.0));
    printf("log10l %La = %La\n", (long double)10.0, log10l((long double)10.0));
    printf("log1pl %La = %La\n", (long double)1.0, log1pl((long double)1.0));
    printf("log2l %La = %La\n", (long double)2.0, log2l((long double)2.0));
    printf("logbl %La = %La\n", (long double)2.0, logbl((long double)2.0));
    long double ipart;
    long double frac = modfl((long double)3.14, &ipart);
    printf("modfl %La = %La ipart %La\n", (long double)3.14, frac, ipart);
    printf("scalbnl %La %d = %La\n", (long double)1.0, 2, scalbnl((long double)1.0, 2));
    printf("scalblnl %La %ld = %La\n", (long double)1.0, 2L, scalblnl((long double)1.0, 2L));
}

static void test_long_double_power(void)
{
    printf("cbrtl %La = %La\n", (long double)8.0, cbrtl((long double)8.0));
    printf("fabsl %La = %La\n", (long double)-1.0, fabsl((long double)-1.0));
    printf("hypotl %La %La = %La\n", (long double)3.0, (long double)4.0,
           hypotl((long double)3.0, (long double)4.0));
    printf("powl %La %La = %La\n", (long double)2.0, (long double)10.0,
           powl((long double)2.0, (long double)10.0));
    printf("sqrtl %La = %La\n", (long double)4.0, sqrtl((long double)4.0));
}

static void test_long_double_errorgamma(void)
{
    printf("erfl %La = %La\n", (long double)1.0, erfl((long double)1.0));
    printf("erfcl %La = %La\n", (long double)1.0, erfcl((long double)1.0));
    printf("lgammal %La = %La\n", (long double)2.0, lgammal((long double)2.0));
    printf("tgammal %La = %La\n", (long double)2.0, tgammal((long double)2.0));
}

static void test_long_double_nearbyint(void)
{
    printf("ceill %La = %La\n", (long double)1.2, ceill((long double)1.2));
    printf("floorl %La = %La\n", (long double)1.9, floorl((long double)1.9));
    printf("nearbyintl %La = %La\n", (long double)1.5, nearbyintl((long double)1.5));
    printf("rintl %La = %La\n", (long double)1.5, rintl((long double)1.5));
    printf("lrintl %La = %ld\n", (long double)1.5, lrintl((long double)1.5));
    printf("llrintl %La = %lld\n", (long double)1.5, llrintl((long double)1.5));
    printf("roundl %La = %La\n", (long double)1.5, roundl((long double)1.5));
    printf("lroundl %La = %ld\n", (long double)1.5, lroundl((long double)1.5));
    printf("llroundl %La = %lld\n", (long double)1.5, llroundl((long double)1.5));
    printf("truncl %La = %La\n", (long double)1.9, truncl((long double)1.9));
}

static void test_long_double_remainder(void)
{
    printf("fmodl %La %La = %La\n", (long double)5.0, (long double)3.0,
           fmodl((long double)5.0, (long double)3.0));
    printf("remainderl %La %La = %La\n", (long double)5.0, (long double)3.0,
           remainderl((long double)5.0, (long double)3.0));
    int q;
    long double r = remquol((long double)5.0, (long double)3.0, &q);
    printf("remquol %La %La = %La quo %d\n", (long double)5.0, (long double)3.0, r, q);
}

static void test_long_double_manipulation(void)
{
    printf("copysignl %La %La = %La\n", (long double)1.0, (long double)-2.0,
           copysignl((long double)1.0, (long double)-2.0));
    long double v = nanl("");
    printf("nanl isnan = %d\n", v != v ? 1 : 0);
    printf("nextafterl %La %La = %La\n", (long double)0.0, (long double)1.0,
           nextafterl((long double)0.0, (long double)1.0));
    printf("nexttoward %a %La = %a\n", 0.0, (long double)1.0,
           nexttoward(0.0, (long double)1.0));
    printf("nexttowardf %a %La = %a\n", 0.0f, (long double)1.0,
           nexttowardf(0.0f, (long double)1.0));
    printf("nexttowardl %La %La = %La\n", (long double)0.0, (long double)1.0,
           nexttowardl((long double)0.0, (long double)1.0));
}

static void test_long_double_maxmindiff(void)
{
    printf("fdiml %La %La = %La\n", (long double)3.0, (long double)2.0,
           fdiml((long double)3.0, (long double)2.0));
    printf("fmaxl %La %La = %La\n", (long double)3.0, (long double)2.0,
           fmaxl((long double)3.0, (long double)2.0));
    printf("fminl %La %La = %La\n", (long double)3.0, (long double)2.0,
           fminl((long double)3.0, (long double)2.0));
    printf("fmal %La %La %La = %La\n", (long double)2.0, (long double)3.0, (long double)4.0,
           fmal((long double)2.0, (long double)3.0, (long double)4.0));
}

static void test_long_double_complex(void)
{
    long double complex z, w;

    z = CMPLXL((long double)3.0, (long double)4.0);
    printf("cabsl %La+%Lai = %La\n", creall(z), cimagl(z), cabsl(z));

    z = CMPLXL((long double)0.5, (long double)0.0);
    w = cacosl(z);
    printf("cacosl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w));

    z = CMPLXL((long double)0.5, (long double)0.0);
    w = casinl(z);
    printf("casinl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w));

    z = CMPLXL((long double)1.0, (long double)0.0);
    w = catanl(z);
    printf("catanl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w));

    z = CMPLXL((long double)0.0, (long double)0.0);
    w = ccosl(z);
    printf("ccosl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w));

    z = CMPLXL((long double)0.0, (long double)0.0);
    w = csinl(z);
    printf("csinl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w));

    z = CMPLXL((long double)0.5, (long double)0.5);
    w = ctanl(z);
    printf("ctanl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w));

    z = CMPLXL((long double)2.0, (long double)0.0);
    w = cacoshl(z);
    printf("cacoshl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w));

    z = CMPLXL((long double)1.0, (long double)0.0);
    w = casinhl(z);
    printf("casinhl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w));

    z = CMPLXL((long double)0.5, (long double)0.0);
    w = catanhl(z);
    printf("catanhl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w));

    z = CMPLXL((long double)0.0, (long double)0.0);
    w = ccoshl(z);
    printf("ccoshl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w));

    z = CMPLXL((long double)0.0, (long double)0.0);
    w = csinhl(z);
    printf("csinhl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w));

    z = CMPLXL((long double)0.5, (long double)0.5);
    w = ctanhl(z);
    printf("ctanhl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w));

    z = CMPLXL((long double)1.0, (long double)0.0);
    w = cexpl(z);
    printf("cexpl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w));

    z = CMPLXL((long double)1.0, (long double)0.0);
    w = clogl(z);
    printf("clogl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w));

    z = CMPLXL((long double)1.0, (long double)1.0);
    long double base_r = cpowl(z, CMPLXL((long double)2.0, (long double)0.0));
    (void)base_r;
    w = cpowl(z, CMPLXL((long double)2.0, (long double)0.0));
    printf("cpowl %La+%Lai 2+0i = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w));

    z = CMPLXL((long double)4.0, (long double)0.0);
    w = csqrtl(z);
    printf("csqrtl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w));

    z = CMPLXL((long double)1.0, (long double)0.0);
    printf("cargl %La+%Lai = %La\n", creall(z), cimagl(z), cargl(z));

    z = CMPLXL((long double)3.0, (long double)4.0);
    printf("cimagl %La+%Lai = %La\n", creall(z), cimagl(z), cimagl(z));

    w = conjl(z);
    printf("conjl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w));

    w = cprojl(z);
    printf("cprojl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w));

    printf("creall %La+%Lai = %La\n", creall(z), cimagl(z), creall(z));
}

#endif /* __LIBMCS_LONG_DOUBLE_IS_64BITS */

/* ------------------------------------------------------------------ */
/* main                                                                */
/* ------------------------------------------------------------------ */

int main(void)
{
    /* Double trigonometric */
    test_acos();
    test_asin();
    test_atan();
    test_atan2();
    test_cos();
    test_sin();
    test_tan();

    /* Float trigonometric */
    test_acosf();
    test_asinf();
    test_atanf();
    test_atan2f();
    test_cosf();
    test_sinf();
    test_tanf();

    /* Double hyperbolic */
    test_acosh();
    test_asinh();
    test_atanh();
    test_cosh();
    test_sinh();
    test_tanh();

    /* Float hyperbolic */
    test_acoshf();
    test_asinhf();
    test_atanhf();
    test_coshf();
    test_sinhf();
    test_tanhf();

    /* Double exponential/log */
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

    /* Float exponential/log */
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

    /* Double power/abs */
    test_cbrt();
    test_fabs();
    test_hypot();
    test_pow();
    test_sqrt();

    /* Float power/abs */
    test_cbrtf();
    test_fabsf();
    test_hypotf();
    test_powf();
    test_sqrtf();

    /* Double error/gamma */
    test_erf();
    test_erfc();
    test_lgamma();
    test_tgamma();

    /* Float error/gamma */
    test_erff();
    test_erfcf();
    test_lgammaf();
    test_tgammaf();

    /* Double nearest integer */
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

    /* Float nearest integer */
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

    /* Double remainder */
    test_fmod();
    test_remainder();
    test_remquo();

    /* Float remainder */
    test_fmodf();
    test_remainderf();
    test_remquof();

    /* Double manipulation */
    test_copysign();
    test_nan();
    test_nextafter();

    /* Float manipulation */
    test_copysignf();
    test_nanf();
    test_nextafterf();

    /* Double max/min/diff */
    test_fdim();
    test_fmax();
    test_fmin();

    /* Float max/min/diff */
    test_fdimf();
    test_fmaxf();
    test_fminf();

    /* FMA */
    test_fma();
    test_fmaf();

    /* Bessel */
    test_j0();
    test_j1();
    test_jn();
    test_y0();
    test_y1();
    test_yn();

    /* Classification */
    test_fpclassifyd();
    test_fpclassifyf();
    test_signbitd();
    test_signbitf();

    /* Internal trig — double */
    test_cos_internal();
    test_sin_internal();
    test_rem_pio2();

    /* Internal trig — float */
    test_cosf_internal();
    test_sinf_internal();
    test_rem_pio2f();

    /* Internal gamma */
    test_lgamma_internal();
    test_lgammaf_internal();

    /* Complex double */
    test_cabs();
    test_cacos();
    test_cacosh();
    test_carg();
    test_casin();
    test_casinh();
    test_catan();
    test_catanh();
    test_ccos();
    test_ccosh();
    test_ccoshsinh();
    test_cexp();
    test_cimag();
    test_clog();
    test_conj();
    test_cpow();
    test_cproj();
    test_creal();
    test_csin();
    test_csinh();
    test_csqrt();
    test_ctan();
    test_ctanh();
    test_redupi();

    /* Complex float */
    test_cabsf();
    test_cacosf();
    test_cacoshf();
    test_cargf();
    test_casinf();
    test_casinhf();
    test_catanf();
    test_catanhf();
    test_ccosf();
    test_ccoshf();
    test_ccoshsinhf();
    test_cexpf();
    test_cimagf();
    test_clogf();
    test_conjf();
    test_cpowf();
    test_cprojf();
    test_crealf();
    test_csinf();
    test_csinhf();
    test_csqrtf();
    test_ctanf();
    test_ctanhf();
    test_redupif();

    /* Bridge (static) functions */
    test_bridge_rem_pio2_internal();
    test_bridge_tan();
    test_bridge_sin_pi();
    test_bridge_rem_pio2f_internal();
    test_bridge_tanf();
    test_bridge_ctans();
    test_bridge_ctansf();
    test_bridge_sin_pif();

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS
    test_long_double_trig();
    test_long_double_hyperbolic();
    test_long_double_exp_log();
    test_long_double_power();
    test_long_double_errorgamma();
    test_long_double_nearbyint();
    test_long_double_remainder();
    test_long_double_manipulation();
    test_long_double_maxmindiff();
    test_long_double_complex();
#endif

    return 0;
}
