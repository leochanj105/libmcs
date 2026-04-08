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
/* Branch-coverage tests — special values & edge cases                */
/* ------------------------------------------------------------------ */

/* Helper macros for special values */
#define D_NAN    (0.0/0.0)
#define D_INF    (1.0/0.0)
#define D_NINF   (-1.0/0.0)
#define F_NAN    (0.0f/0.0f)
#define F_INF    (1.0f/0.0f)
#define F_NINF   (-1.0f/0.0f)
/* smallest subnormal */
#define D_SUBNORM  5e-324          /* 0x1p-1074 */
#define F_SUBNORM  1.4e-45f        /* 0x1p-149f  */

static void test_acos_branches(void)
{
    /* Branch 90: |x|>1 → NaN */
    printf("acos %a = %a\n", 1.5, acos(1.5));
    printf("acos %a = %a\n", -1.5, acos(-1.5));
    /* Branch 106: small |x| < 2^-57 */
    printf("acos %a = %a\n", 0x1p-60, acos(0x1p-60));
    /* Branch 115: x > 0.5 → sqrt path */
    printf("acos %a = %a\n", 0.7, acos(0.7));
    printf("acos %a = %a\n", 0.9, acos(0.9));
    printf("acos %a = %a\n", -0.7, acos(-0.7));
    printf("acos %a = %a\n", -0.9, acos(-0.9));
    /* NaN */
    printf("acos nan = %a\n", acos(D_NAN));
}

static void test_acosf_branches(void)
{
    /* Branch 36: |x|==1 */
    printf("acosf %a = %a\n", -1.0f, acosf(-1.0f));
    /* Branch 41: |x|>1 */
    printf("acosf %a = %a\n", 1.5f, acosf(1.5f));
    printf("acosf %a = %a\n", -1.5f, acosf(-1.5f));
    /* Branch 52: small |x| */
    printf("acosf %a = %a\n", 0x1p-60f, acosf(0x1p-60f));
    /* Branch 61: x > 0.5 / x < -0.5 */
    printf("acosf %a = %a\n", 0.7f, acosf(0.7f));
    printf("acosf %a = %a\n", -0.7f, acosf(-0.7f));
    printf("acosf %a = %a\n", 0.9f, acosf(0.9f));
    printf("acosf nan = %a\n", acosf(F_NAN));
}

static void test_acosh_branches(void)
{
    /* Branch 73: x < 1 → NaN */
    printf("acosh %a = %a\n", 0.5, acosh(0.5));
    printf("acosh %a = %a\n", -1.0, acosh(-1.0));
    /* Branch 79: x > 2^28 */
    printf("acosh %a = %a\n", 0x1p30, acosh(0x1p30));
    /* Branch 80: x exactly 1 */
    printf("acosh %a = %a\n", 1.0 + 0x1p-52, acosh(1.0 + 0x1p-52));
    /* inf */
    printf("acosh %a = %a\n", D_INF, acosh(D_INF));
    printf("acosh nan = %a\n", acosh(D_NAN));
}

static void test_acoshf_branches(void)
{
    /* Branch 22: x < 1 */
    printf("acoshf %a = %a\n", 0.5f, acoshf(0.5f));
    /* Branch 28: x > 2^28 */
    printf("acoshf %a = %a\n", 0x1p30f, acoshf(0x1p30f));
    /* Branch 29: inf */
    printf("acoshf %a = %a\n", F_INF, acoshf(F_INF));
    /* Branch 36: x > 2.0 */
    printf("acoshf %a = %a\n", 3.0f, acoshf(3.0f));
    printf("acoshf nan = %a\n", acoshf(F_NAN));
}

static void test_asin_branches(void)
{
    /* Branch 92: |x|>1 → NaN */
    printf("asin %a = %a\n", 1.5, asin(1.5));
    printf("asin %a = %a\n", -1.5, asin(-1.5));
    /* Branch 104: |x|<2^-26 non-zero */
    printf("asin %a = %a\n", 0x1p-30, asin(0x1p-30));
    /* Branch 105: x == 0 */
    printf("asin %a = %a\n", -0.0, asin(-0.0));
    /* Branch 128: |x|>0.975 */
    printf("asin %a = %a\n", 0.99, asin(0.99));
    printf("asin %a = %a\n", -0.99, asin(-0.99));
    printf("asin nan = %a\n", asin(D_NAN));
}

static void test_asinf_branches(void)
{
    /* Branch 36: |x|==1 */
    printf("asinf %a = %a\n", -1.0f, asinf(-1.0f));
    /* Branch 38: |x|>1 */
    printf("asinf %a = %a\n", 1.5f, asinf(1.5f));
    printf("asinf %a = %a\n", -1.5f, asinf(-1.5f));
    /* Branch 45: |x|<2^-27 non-zero */
    printf("asinf %a = %a\n", 0x1p-30f, asinf(0x1p-30f));
    /* Branch 69: |x|>0.975 */
    printf("asinf %a = %a\n", 0.99f, asinf(0.99f));
    printf("asinf %a = %a\n", -0.99f, asinf(-0.99f));
    printf("asinf nan = %a\n", asinf(F_NAN));
}

static void test_asinh_branches(void)
{
    /* Branch 74: inf or NaN */
    printf("asinh %a = %a\n", D_INF, asinh(D_INF));
    printf("asinh %a = %a\n", D_NINF, asinh(D_NINF));
    printf("asinh nan = %a\n", asinh(D_NAN));
    /* Branch 79: x==0 */
    printf("asinh %a = %a\n", -0.0, asinh(-0.0));
    /* Branch 86: |x|>2^28 */
    printf("asinh %a = %a\n", 0x1p30, asinh(0x1p30));
    printf("asinh %a = %a\n", -0x1p30, asinh(-0x1p30));
    /* Branch 88: 2<|x|<=2^28 */
    printf("asinh %a = %a\n", 3.0, asinh(3.0));
    printf("asinh %a = %a\n", -3.0, asinh(-3.0));
    /* small */
    printf("asinh %a = %a\n", 0x1p-30, asinh(0x1p-30));
}

static void test_asinhf_branches(void)
{
    /* Branch 23: inf or NaN */
    printf("asinhf %a = %a\n", F_INF, asinhf(F_INF));
    printf("asinhf %a = %a\n", F_NINF, asinhf(F_NINF));
    printf("asinhf nan = %a\n", asinhf(F_NAN));
    /* Branch 35: |x|>2^28 */
    printf("asinhf %a = %a\n", 0x1p30f, asinhf(0x1p30f));
    printf("asinhf %a = %a\n", -0x1p30f, asinhf(-0x1p30f));
    /* Branch 37: 2<|x|<=2^28 */
    printf("asinhf %a = %a\n", 3.0f, asinhf(3.0f));
    /* Branch 45: |x|>=2^-14 */
    printf("asinhf %a = %a\n", 0.5f, asinhf(0.5f));
    printf("asinhf %a = %a\n", 0x1p-30f, asinhf(0x1p-30f));
}

static void test_atan_branches(void)
{
    /* Branch 100: |x|>=2^66 */
    printf("atan %a = %a\n", 0x1p80, atan(0x1p80));
    printf("atan %a = %a\n", -0x1p80, atan(-0x1p80));
    /* Branch 104: NaN */
    printf("atan nan = %a\n", atan(D_NAN));
    /* Branch 105: x==0 */
    printf("atan %a = %a\n", -0.0, atan(-0.0));
    /* Branch 109: inf */
    printf("atan %a = %a\n", D_INF, atan(D_INF));
    printf("atan %a = %a\n", D_NINF, atan(D_NINF));
    /* Branch 117: |x|<2^-27 */
    printf("atan %a = %a\n", 0x1p-30, atan(0x1p-30));
    /* Branch 118: id=-1 (|x|<7/16) */
    printf("atan %a = %a\n", 0.3, atan(0.3));
    printf("atan %a = %a\n", -0.3, atan(-0.3));
    /* Branch 129: 7/16<=|x|<11/16 */
    printf("atan %a = %a\n", 0.5, atan(0.5));
    printf("atan %a = %a\n", -0.5, atan(-0.5));
    /* Branch 138: 11/16<=|x|<2.4375 */
    printf("atan %a = %a\n", 2.0, atan(2.0));
    printf("atan %a = %a\n", -2.0, atan(-2.0));
    /* id>=2: |x|>=2.4375 */
    printf("atan %a = %a\n", 3.0, atan(3.0));
    printf("atan %a = %a\n", -3.0, atan(-3.0));
}

static void test_atanf_branches(void)
{
    /* Branch 50: |x|>=2^34 */
    printf("atanf %a = %a\n", 0x1p40f, atanf(0x1p40f));
    printf("atanf %a = %a\n", -0x1p40f, atanf(-0x1p40f));
    /* Branch 55: |x|<2^-29 */
    printf("atanf %a = %a\n", 0x1p-30f, atanf(0x1p-30f));
    printf("atanf nan = %a\n", atanf(F_NAN));
    /* Branch 63: |x|<0.4375 */
    printf("atanf %a = %a\n", 0.2f, atanf(0.2f));
    printf("atanf %a = %a\n", -0.2f, atanf(-0.2f));
    /* Branch 75: 0.4375<=|x|<1.1875 */
    printf("atanf %a = %a\n", 0.7f, atanf(0.7f));
    printf("atanf %a = %a\n", -0.7f, atanf(-0.7f));
    /* Branch 84: 1.1875<=|x|<2.4375 */
    printf("atanf %a = %a\n", 2.0f, atanf(2.0f));
    printf("atanf %a = %a\n", -2.0f, atanf(-2.0f));
    /* id>=2: |x|>=2.4375 */
    printf("atanf %a = %a\n", 3.0f, atanf(3.0f));
    printf("atanf %a = %a\n", -3.0f, atanf(-3.0f));
    /* Branch 101: id>=0 */
    printf("atanf %a = %a\n", F_INF, atanf(F_INF));
    printf("atanf %a = %a\n", F_NINF, atanf(F_NINF));
}

static void test_atan2_branches(void)
{
    /* Branch 102-103: NaN inputs */
    printf("atan2 nan 1 = %a\n", atan2(D_NAN, 1.0));
    printf("atan2 1 nan = %a\n", atan2(1.0, D_NAN));
    /* Branch 116: y==0 */
    printf("atan2 %a %a = %a\n", 0.0, 1.0, atan2(0.0, 1.0));
    printf("atan2 %a %a = %a\n", -0.0, 1.0, atan2(-0.0, 1.0));
    printf("atan2 %a %a = %a\n", 0.0, -1.0, atan2(0.0, -1.0));
    printf("atan2 %a %a = %a\n", -0.0, -1.0, atan2(-0.0, -1.0));
    printf("atan2 %a %a = %a\n", 0.0, 0.0, atan2(0.0, 0.0));
    printf("atan2 %a %a = %a\n", -0.0, 0.0, atan2(-0.0, 0.0));
    /* Branch 124: x==0 */
    printf("atan2 %a %a = %a\n", 1.0, 0.0, atan2(1.0, 0.0));
    printf("atan2 %a %a = %a\n", -1.0, 0.0, atan2(-1.0, 0.0));
    printf("atan2 %a %a = %a\n", -1.0, -0.0, atan2(-1.0, -0.0));
    /* Branch 135: x==0, y!=0 */
    printf("atan2 %a %a = %a\n", 1.0, -0.0, atan2(1.0, -0.0));
    /* Branch 170: x is +Inf, y is Inf */
    printf("atan2 %a %a = %a\n", D_INF, D_INF, atan2(D_INF, D_INF));
    printf("atan2 %a %a = %a\n", D_NINF, D_INF, atan2(D_NINF, D_INF));
    printf("atan2 %a %a = %a\n", D_INF, D_NINF, atan2(D_INF, D_NINF));
    printf("atan2 %a %a = %a\n", D_NINF, D_NINF, atan2(D_NINF, D_NINF));
    /* Branch 177: x is Inf, y is not Inf */
    printf("atan2 %a %a = %a\n", 1.0, D_INF, atan2(1.0, D_INF));
    printf("atan2 %a %a = %a\n", 1.0, D_NINF, atan2(1.0, D_NINF));
    printf("atan2 %a %a = %a\n", -1.0, D_INF, atan2(-1.0, D_INF));
    printf("atan2 %a %a = %a\n", -1.0, D_NINF, atan2(-1.0, D_NINF));
    /* Branch 180: y is Inf */
    printf("atan2 %a %a = %a\n", D_INF, 1.0, atan2(D_INF, 1.0));
    printf("atan2 %a %a = %a\n", D_NINF, 1.0, atan2(D_NINF, 1.0));
    /* Branch 190: k>60 */
    printf("atan2 %a %a = %a\n", 0x1p70, 1.0, atan2(0x1p70, 1.0));
    printf("atan2 %a %a = %a\n", -0x1p70, 1.0, atan2(-0x1p70, 1.0));
    /* Branch 193: k<-60 */
    printf("atan2 %a %a = %a\n", 0x1p-70, -1.0, atan2(0x1p-70, -1.0));
    printf("atan2 %a %a = %a\n", -0x1p-70, -1.0, atan2(-0x1p-70, -1.0));
    /* branches for table lookup in quadrants */
    printf("atan2 %a %a = %a\n", 2.0, 1.0, atan2(2.0, 1.0));
    printf("atan2 %a %a = %a\n", 1.0, 2.0, atan2(1.0, 2.0));
    printf("atan2 %a %a = %a\n", -2.0, -1.0, atan2(-2.0, -1.0));
    printf("atan2 %a %a = %a\n", -1.0, -2.0, atan2(-1.0, -2.0));
}

static void test_atan2f_branches(void)
{
    printf("atan2f nan 1 = %a\n", atan2f(F_NAN, 1.0f));
    printf("atan2f 1 nan = %a\n", atan2f(1.0f, F_NAN));
    printf("atan2f %a %a = %a\n", 0.0f, 1.0f, atan2f(0.0f, 1.0f));
    printf("atan2f %a %a = %a\n", -0.0f, 1.0f, atan2f(-0.0f, 1.0f));
    printf("atan2f %a %a = %a\n", 0.0f, -1.0f, atan2f(0.0f, -1.0f));
    printf("atan2f %a %a = %a\n", -0.0f, -1.0f, atan2f(-0.0f, -1.0f));
    printf("atan2f %a %a = %a\n", 0.0f, 0.0f, atan2f(0.0f, 0.0f));
    printf("atan2f %a %a = %a\n", -0.0f, 0.0f, atan2f(-0.0f, 0.0f));
    printf("atan2f %a %a = %a\n", 1.0f, 0.0f, atan2f(1.0f, 0.0f));
    printf("atan2f %a %a = %a\n", -1.0f, 0.0f, atan2f(-1.0f, 0.0f));
    printf("atan2f %a %a = %a\n", 1.0f, -0.0f, atan2f(1.0f, -0.0f));
    printf("atan2f %a %a = %a\n", -1.0f, -0.0f, atan2f(-1.0f, -0.0f));
    printf("atan2f %a %a = %a\n", F_INF, F_INF, atan2f(F_INF, F_INF));
    printf("atan2f %a %a = %a\n", F_NINF, F_INF, atan2f(F_NINF, F_INF));
    printf("atan2f %a %a = %a\n", F_INF, F_NINF, atan2f(F_INF, F_NINF));
    printf("atan2f %a %a = %a\n", F_NINF, F_NINF, atan2f(F_NINF, F_NINF));
    printf("atan2f %a %a = %a\n", 1.0f, F_INF, atan2f(1.0f, F_INF));
    printf("atan2f %a %a = %a\n", -1.0f, F_INF, atan2f(-1.0f, F_INF));
    printf("atan2f %a %a = %a\n", 1.0f, F_NINF, atan2f(1.0f, F_NINF));
    printf("atan2f %a %a = %a\n", F_INF, 1.0f, atan2f(F_INF, 1.0f));
    printf("atan2f %a %a = %a\n", F_NINF, 1.0f, atan2f(F_NINF, 1.0f));
    printf("atan2f %a %a = %a\n", 0x1p40f, 1.0f, atan2f(0x1p40f, 1.0f));
    printf("atan2f %a %a = %a\n", 0x1p-40f, -1.0f, atan2f(0x1p-40f, -1.0f));
    printf("atan2f %a %a = %a\n", -0x1p-40f, -1.0f, atan2f(-0x1p-40f, -1.0f));
    printf("atan2f %a %a = %a\n", 2.0f, 1.0f, atan2f(2.0f, 1.0f));
    printf("atan2f %a %a = %a\n", -2.0f, -1.0f, atan2f(-2.0f, -1.0f));
}

static void test_atanh_branches(void)
{
    /* Branch 77: |x|>1 */
    printf("atanh %a = %a\n", 1.5, atanh(1.5));
    printf("atanh %a = %a\n", -1.5, atanh(-1.5));
    /* Branch 85: |x|==1 */
    printf("atanh %a = %a\n", 1.0, atanh(1.0));
    printf("atanh %a = %a\n", -1.0, atanh(-1.0));
    /* Branch 90: |x|<2^-28 */
    printf("atanh %a = %a\n", 0x1p-30, atanh(0x1p-30));
    printf("atanh %a = %a\n", -0x1p-30, atanh(-0x1p-30));
    /* Branch 99: |x|<0.5 */
    printf("atanh %a = %a\n", 0.3, atanh(0.3));
    printf("atanh %a = %a\n", -0.3, atanh(-0.3));
    printf("atanh nan = %a\n", atanh(D_NAN));
    printf("atanh %a = %a\n", D_INF, atanh(D_INF));
}

static void test_atanhf_branches(void)
{
    /* Branch 21: |x|>1 */
    printf("atanhf %a = %a\n", 1.5f, atanhf(1.5f));
    printf("atanhf %a = %a\n", -1.5f, atanhf(-1.5f));
    /* Branch 29: |x|==1 */
    printf("atanhf %a = %a\n", 1.0f, atanhf(1.0f));
    printf("atanhf %a = %a\n", -1.0f, atanhf(-1.0f));
    /* Branch 43: |x|<0.5 */
    printf("atanhf %a = %a\n", 0.3f, atanhf(0.3f));
    printf("atanhf %a = %a\n", -0.3f, atanhf(-0.3f));
    /* Branch 50: |x|>=0.5 (normal path) */
    printf("atanhf %a = %a\n", 0.7f, atanhf(0.7f));
    printf("atanhf %a = %a\n", -0.7f, atanhf(-0.7f));
    printf("atanhf nan = %a\n", atanhf(F_NAN));
}

static void test_cosh_branches(void)
{
    /* Branch 73: inf or NaN */
    printf("cosh %a = %a\n", D_INF, cosh(D_INF));
    printf("cosh %a = %a\n", D_NINF, cosh(D_NINF));
    printf("cosh nan = %a\n", cosh(D_NAN));
    /* Branch 90: |x|<2^-55 (tiny) */
    printf("cosh %a = %a\n", 0x1p-60, cosh(0x1p-60));
    /* Branch 96: |x| in [0.5*ln2, 22] */
    printf("cosh %a = %a\n", 5.0, cosh(5.0));
    printf("cosh %a = %a\n", -5.0, cosh(-5.0));
    /* |x| in [22, log(maxdouble)] */
    printf("cosh %a = %a\n", 500.0, cosh(500.0));
    /* Branch 103: overflow threshold */
    printf("cosh %a = %a\n", 710.0, cosh(710.0));
    printf("cosh %a = %a\n", 712.0, cosh(712.0));
}

static void test_coshf_branches(void)
{
    /* Branch 23: inf or NaN */
    printf("coshf %a = %a\n", F_INF, coshf(F_INF));
    printf("coshf %a = %a\n", F_NINF, coshf(F_NINF));
    printf("coshf nan = %a\n", coshf(F_NAN));
    /* Branch 40: |x|<2^-28 */
    printf("coshf %a = %a\n", 0x1p-30f, coshf(0x1p-30f));
    /* Branch 46: |x| in [0.5*ln2, 9] */
    printf("coshf %a = %a\n", 5.0f, coshf(5.0f));
    /* Branch 51: |x| in [9, log(maxfloat)] */
    printf("coshf %a = %a\n", 50.0f, coshf(50.0f));
    /* overflow */
    printf("coshf %a = %a\n", 200.0f, coshf(200.0f));
}

static void test_sinh_branches(void)
{
    /* Branch 76: inf or NaN */
    printf("sinh %a = %a\n", D_INF, sinh(D_INF));
    printf("sinh %a = %a\n", D_NINF, sinh(D_NINF));
    printf("sinh nan = %a\n", sinh(D_NAN));
    /* Branch 87: |x|<2^-28 */
    printf("sinh %a = %a\n", 0x1p-30, sinh(0x1p-30));
    printf("sinh %a = %a\n", -0x1p-30, sinh(-0x1p-30));
    /* Branch 89: x==0 */
    printf("sinh %a = %a\n", -0.0, sinh(-0.0));
    /* |x| in [0,22] */
    printf("sinh %a = %a\n", 5.0, sinh(5.0));
    printf("sinh %a = %a\n", -5.0, sinh(-5.0));
    /* Branch 106: |x| in [22, log(maxdouble)] */
    printf("sinh %a = %a\n", 500.0, sinh(500.0));
    /* overflow */
    printf("sinh %a = %a\n", 710.0, sinh(710.0));
    printf("sinh %a = %a\n", -710.0, sinh(-710.0));
}

static void test_sinhf_branches(void)
{
    /* Branch 23: inf or NaN */
    printf("sinhf %a = %a\n", F_INF, sinhf(F_INF));
    printf("sinhf %a = %a\n", F_NINF, sinhf(F_NINF));
    printf("sinhf nan = %a\n", sinhf(F_NAN));
    /* Branch 29: |x|<2^-28 non-zero */
    printf("sinhf %a = %a\n", 0x1p-30f, sinhf(0x1p-30f));
    printf("sinhf %a = %a\n", -0x1p-30f, sinhf(-0x1p-30f));
    /* Branch 34: x==0 */
    printf("sinhf %a = %a\n", -0.0f, sinhf(-0.0f));
    /* Branch 53: |x| in [9, log(maxfloat)] */
    printf("sinhf %a = %a\n", 50.0f, sinhf(50.0f));
    /* overflow */
    printf("sinhf %a = %a\n", 200.0f, sinhf(200.0f));
    printf("sinhf %a = %a\n", -200.0f, sinhf(-200.0f));
}

static void test_tanh_branches(void)
{
    /* Branch 74: inf or NaN */
    printf("tanh %a = %a\n", D_INF, tanh(D_INF));
    printf("tanh %a = %a\n", D_NINF, tanh(D_NINF));
    printf("tanh nan = %a\n", tanh(D_NAN));
    /* Branch 77: |x|>=1 */
    printf("tanh %a = %a\n", 2.0, tanh(2.0));
    printf("tanh %a = %a\n", -2.0, tanh(-2.0));
    /* Branch 85: |x|<2^-55 */
    printf("tanh %a = %a\n", 0x1p-60, tanh(0x1p-60));
    /* Branch 87: x==0 */
    printf("tanh %a = %a\n", -0.0, tanh(-0.0));
    /* Branch 94: |x|>=1 path */
    printf("tanh %a = %a\n", 5.0, tanh(5.0));
    printf("tanh %a = %a\n", -5.0, tanh(-5.0));
    /* large */
    printf("tanh %a = %a\n", 30.0, tanh(30.0));
    printf("tanh %a = %a\n", -30.0, tanh(-30.0));
}

static void test_tanhf_branches(void)
{
    /* Branch 23: inf or NaN */
    printf("tanhf %a = %a\n", F_INF, tanhf(F_INF));
    printf("tanhf %a = %a\n", F_NINF, tanhf(F_NINF));
    printf("tanhf nan = %a\n", tanhf(F_NAN));
    /* Branch 26: |x|>=1 */
    printf("tanhf %a = %a\n", 2.0f, tanhf(2.0f));
    printf("tanhf %a = %a\n", -2.0f, tanhf(-2.0f));
    /* Branch 34: x==0 */
    printf("tanhf %a = %a\n", -0.0f, tanhf(-0.0f));
    /* Branch 43: |x|<2^-28 */
    printf("tanhf %a = %a\n", 0x1p-30f, tanhf(0x1p-30f));
    /* Branch 56: large */
    printf("tanhf %a = %a\n", 20.0f, tanhf(20.0f));
    printf("tanhf %a = %a\n", -20.0f, tanhf(-20.0f));
}

static void test_exp_branches(void)
{
    /* Branch 101: |x|>=709.78 */
    printf("exp %a = %a\n", 800.0, exp(800.0));
    printf("exp %a = %a\n", -800.0, exp(-800.0));
    /* Branch 102: inf or NaN */
    printf("exp %a = %a\n", D_INF, exp(D_INF));
    printf("exp %a = %a\n", D_NINF, exp(D_NINF));
    printf("exp nan = %a\n", exp(D_NAN));
    /* Branch 113: overflow */
    printf("exp %a = %a\n", 710.0, exp(710.0));
    /* Branch 117: underflow */
    printf("exp %a = %a\n", -750.0, exp(-750.0));
    /* Branch 136: |x|<2^-32 non-zero */
    printf("exp %a = %a\n", 0x1p-40, exp(0x1p-40));
    printf("exp %a = %a\n", -0x1p-40, exp(-0x1p-40));
    /* Branch 137: x==0 */
    printf("exp %a = %a\n", -0.0, exp(-0.0));
    /* Branch 150: k==0 */
    printf("exp %a = %a\n", 0.3, exp(0.3));
    printf("exp %a = %a\n", -0.3, exp(-0.3));
    /* Branch 156: k!=0 and k>=-1021 */
    printf("exp %a = %a\n", 2.0, exp(2.0));
    printf("exp %a = %a\n", -2.0, exp(-2.0));
    /* k< -1021 */
    printf("exp %a = %a\n", -745.0, exp(-745.0));
}

static void test_expf_branches(void)
{
    /* Branch 49: inf */
    printf("expf %a = %a\n", F_INF, expf(F_INF));
    /* Branch 52: -inf */
    printf("expf %a = %a\n", F_NINF, expf(F_NINF));
    printf("expf nan = %a\n", expf(F_NAN));
    /* Branch 56: overflow */
    printf("expf %a = %a\n", 200.0f, expf(200.0f));
    /* underflow */
    printf("expf %a = %a\n", -200.0f, expf(-200.0f));
    /* Branch 74: |x|<2^-23 non-zero */
    printf("expf %a = %a\n", 0x1p-30f, expf(0x1p-30f));
    printf("expf %a = %a\n", -0x1p-30f, expf(-0x1p-30f));
    /* Branch 75: x==0 */
    printf("expf %a = %a\n", -0.0f, expf(-0.0f));
    /* Branch 88: k==0 */
    printf("expf %a = %a\n", 0.3f, expf(0.3f));
    printf("expf %a = %a\n", -0.3f, expf(-0.3f));
    /* Branch 94: k>=-125 */
    printf("expf %a = %a\n", 2.0f, expf(2.0f));
    /* k<-125 (underflow path) */
    printf("expf %a = %a\n", -130.0f, expf(-130.0f));
}

static void test_expm1_branches(void)
{
    /* Various ranges */
    printf("expm1 %a = %a\n", D_INF, expm1(D_INF));
    printf("expm1 %a = %a\n", D_NINF, expm1(D_NINF));
    printf("expm1 nan = %a\n", expm1(D_NAN));
    printf("expm1 %a = %a\n", 0x1p-60, expm1(0x1p-60));
    printf("expm1 %a = %a\n", -0x1p-60, expm1(-0x1p-60));
    printf("expm1 %a = %a\n", -0.0, expm1(-0.0));
    printf("expm1 %a = %a\n", 2.0, expm1(2.0));
    printf("expm1 %a = %a\n", -2.0, expm1(-2.0));
    printf("expm1 %a = %a\n", 0.5, expm1(0.5));
    printf("expm1 %a = %a\n", -0.5, expm1(-0.5));
    printf("expm1 %a = %a\n", 710.0, expm1(710.0));
    printf("expm1 %a = %a\n", -50.0, expm1(-50.0));
}

static void test_expm1f_branches(void)
{
    printf("expm1f %a = %a\n", F_INF, expm1f(F_INF));
    printf("expm1f %a = %a\n", F_NINF, expm1f(F_NINF));
    printf("expm1f nan = %a\n", expm1f(F_NAN));
    printf("expm1f %a = %a\n", 0x1p-30f, expm1f(0x1p-30f));
    printf("expm1f %a = %a\n", -0x1p-30f, expm1f(-0x1p-30f));
    printf("expm1f %a = %a\n", -0.0f, expm1f(-0.0f));
    printf("expm1f %a = %a\n", 2.0f, expm1f(2.0f));
    printf("expm1f %a = %a\n", -2.0f, expm1f(-2.0f));
    printf("expm1f %a = %a\n", 0.5f, expm1f(0.5f));
    printf("expm1f %a = %a\n", -0.5f, expm1f(-0.5f));
    printf("expm1f %a = %a\n", 200.0f, expm1f(200.0f));
    printf("expm1f %a = %a\n", -50.0f, expm1f(-50.0f));
}

static void test_log_branches(void)
{
    /* Branch 86: x==0 or subnormal */
    printf("log %a = %a\n", 0.0, log(0.0));
    printf("log %a = %a\n", -0.0, log(-0.0));
    /* Branch 87: x<0 */
    printf("log %a = %a\n", -1.0, log(-1.0));
    /* subnormal */
    printf("log %a = %a\n", D_SUBNORM, log(D_SUBNORM));
    /* Branch 91: normalize subnormal */
    printf("log %a = %a\n", 0x1p-1050, log(0x1p-1050));
    /* Branch 104: inf or nan */
    printf("log %a = %a\n", D_INF, log(D_INF));
    printf("log nan = %a\n", log(D_NAN));
    /* Branch 127: k==0, f==0 */
    printf("log %a = %a\n", 1.0, log(1.0));
    /* Branch 146: k!=0 */
    printf("log %a = %a\n", 0.5, log(0.5));
    printf("log %a = %a\n", 0.25, log(0.25));
}

static void test_logf_branches(void)
{
    printf("logf %a = %a\n", 0.0f, logf(0.0f));
    printf("logf %a = %a\n", -1.0f, logf(-1.0f));
    printf("logf %a = %a\n", F_SUBNORM, logf(F_SUBNORM));
    printf("logf %a = %a\n", 0x1p-130f, logf(0x1p-130f));
    printf("logf %a = %a\n", F_INF, logf(F_INF));
    printf("logf nan = %a\n", logf(F_NAN));
    printf("logf %a = %a\n", 1.0f, logf(1.0f));
    printf("logf %a = %a\n", 0.5f, logf(0.5f));
    printf("logf %a = %a\n", 0.25f, logf(0.25f));
}

static void test_log10_branches(void)
{
    printf("log10 %a = %a\n", 0.0, log10(0.0));
    printf("log10 %a = %a\n", -1.0, log10(-1.0));
    printf("log10 %a = %a\n", D_SUBNORM, log10(D_SUBNORM));
    printf("log10 %a = %a\n", D_INF, log10(D_INF));
    printf("log10 nan = %a\n", log10(D_NAN));
    printf("log10 %a = %a\n", 1.0, log10(1.0));
    printf("log10 %a = %a\n", 0.5, log10(0.5));
}

static void test_log10f_branches(void)
{
    printf("log10f %a = %a\n", 0.0f, log10f(0.0f));
    printf("log10f %a = %a\n", F_SUBNORM, log10f(F_SUBNORM));
    printf("log10f %a = %a\n", F_INF, log10f(F_INF));
    printf("log10f %a = %a\n", 0.5f, log10f(0.5f));
}

static void test_log2_branches(void)
{
    printf("log2 %a = %a\n", 0.0, log2(0.0));
    printf("log2 %a = %a\n", -1.0, log2(-1.0));
    printf("log2 %a = %a\n", D_SUBNORM, log2(D_SUBNORM));
    printf("log2 %a = %a\n", D_INF, log2(D_INF));
    printf("log2 nan = %a\n", log2(D_NAN));
    printf("log2 %a = %a\n", 1.0, log2(1.0));
    printf("log2 %a = %a\n", 0.5, log2(0.5));
}

static void test_log2f_branches(void)
{
    printf("log2f %a = %a\n", 0.0f, log2f(0.0f));
    printf("log2f %a = %a\n", F_SUBNORM, log2f(F_SUBNORM));
    printf("log2f %a = %a\n", F_INF, log2f(F_INF));
    printf("log2f %a = %a\n", 0.5f, log2f(0.5f));
}

static void test_log1p_branches(void)
{
    /* Branch 150: x < -1 */
    printf("log1p %a = %a\n", -2.0, log1p(-2.0));
    /* Branch 155: x == -1 */
    printf("log1p %a = %a\n", -1.0, log1p(-1.0));
    /* Branch 158: x is inf or NaN */
    printf("log1p %a = %a\n", D_INF, log1p(D_INF));
    printf("log1p nan = %a\n", log1p(D_NAN));
    /* Branch 165: |x| < 2^-29 */
    printf("log1p %a = %a\n", 0x1p-30, log1p(0x1p-30));
    printf("log1p %a = %a\n", -0x1p-30, log1p(-0x1p-30));
    /* Branch 173: f in different ranges */
    printf("log1p %a = %a\n", 0.5, log1p(0.5));
    printf("log1p %a = %a\n", -0.5, log1p(-0.5));
    /* Branch 181: k != 0, large f */
    printf("log1p %a = %a\n", 2.0, log1p(2.0));
    printf("log1p %a = %a\n", -0.9, log1p(-0.9));
    printf("log1p %a = %a\n", 0x1p30, log1p(0x1p30));
}

static void test_log1pf_branches(void)
{
    printf("log1pf %a = %a\n", -2.0f, log1pf(-2.0f));
    printf("log1pf %a = %a\n", -1.0f, log1pf(-1.0f));
    printf("log1pf %a = %a\n", F_INF, log1pf(F_INF));
    printf("log1pf nan = %a\n", log1pf(F_NAN));
    printf("log1pf %a = %a\n", 0x1p-30f, log1pf(0x1p-30f));
    printf("log1pf %a = %a\n", 0.5f, log1pf(0.5f));
    printf("log1pf %a = %a\n", -0.5f, log1pf(-0.5f));
    printf("log1pf %a = %a\n", 2.0f, log1pf(2.0f));
    printf("log1pf %a = %a\n", -0.9f, log1pf(-0.9f));
}

static void test_logb_branches(void)
{
    /* Branch 71: subnormal */
    printf("logb %a = %a\n", D_SUBNORM, logb(D_SUBNORM));
    /* Branch 72: x==0 */
    printf("logb %a = %a\n", 0.0, logb(0.0));
    /* Branch 76: inf or NaN */
    printf("logb %a = %a\n", D_INF, logb(D_INF));
    printf("logb nan = %a\n", logb(D_NAN));
    /* Branch 80: x != 0 finite */
    printf("logb %a = %a\n", 0.5, logb(0.5));
    printf("logb %a = %a\n", 3.0, logb(3.0));
}

static void test_logbf_branches(void)
{
    printf("logbf %a = %a\n", F_SUBNORM, logbf(F_SUBNORM));
    printf("logbf %a = %a\n", 0.0f, logbf(0.0f));
    printf("logbf %a = %a\n", F_INF, logbf(F_INF));
    printf("logbf nan = %a\n", logbf(F_NAN));
    printf("logbf %a = %a\n", 0.5f, logbf(0.5f));
}

static void test_cos_branches(void)
{
    /* Branch 73: |x| < 2^-27 (returns 1) */
    printf("cos %a = %a\n", 0x1p-30, cos(0x1p-30));
    printf("cos %a = %a\n", -0x1p-30, cos(-0x1p-30));
    /* Branch 74: x==0 */
    printf("cos %a = %a\n", -0.0, cos(-0.0));
    /* Branch 85: inf or NaN */
    printf("cos %a = %a\n", D_INF, cos(D_INF));
    printf("cos %a = %a\n", D_NINF, cos(D_NINF));
    printf("cos nan = %a\n", cos(D_NAN));
    /* Branch 98: n&3 cases via argument reduction */
    printf("cos %a = %a\n", 2.0, cos(2.0));
    printf("cos %a = %a\n", 3.14, cos(3.14));
    printf("cos %a = %a\n", 5.0, cos(5.0));
    printf("cos %a = %a\n", 10.0, cos(10.0));
    printf("cos %a = %a\n", 100.0, cos(100.0));
    printf("cos %a = %a\n", 1e8, cos(1e8));
}

static void test_cosf_branches(void)
{
    /* Branch 24: |x|<2^-12 */
    printf("cosf %a = %a\n", 0x1p-14f, cosf(0x1p-14f));
    printf("cosf %a = %a\n", -0x1p-14f, cosf(-0x1p-14f));
    /* Branch 25: x==0 */
    printf("cosf %a = %a\n", -0.0f, cosf(-0.0f));
    /* Branch 35: inf or NaN */
    printf("cosf %a = %a\n", F_INF, cosf(F_INF));
    printf("cosf %a = %a\n", F_NINF, cosf(F_NINF));
    printf("cosf nan = %a\n", cosf(F_NAN));
    /* n&3 cases */
    printf("cosf %a = %a\n", 2.0f, cosf(2.0f));
    printf("cosf %a = %a\n", 3.14f, cosf(3.14f));
    printf("cosf %a = %a\n", 5.0f, cosf(5.0f));
    printf("cosf %a = %a\n", 100.0f, cosf(100.0f));
}

static void test_sin_branches(void)
{
    /* Branch 76: |x|<2^-26 */
    printf("sin %a = %a\n", 0x1p-30, sin(0x1p-30));
    printf("sin %a = %a\n", -0x1p-30, sin(-0x1p-30));
    /* Branch 75: x==0 */
    printf("sin %a = %a\n", -0.0, sin(-0.0));
    /* Branch 87: inf or NaN */
    printf("sin %a = %a\n", D_INF, sin(D_INF));
    printf("sin %a = %a\n", D_NINF, sin(D_NINF));
    printf("sin nan = %a\n", sin(D_NAN));
    /* n&3 cases via argument reduction */
    printf("sin %a = %a\n", 2.0, sin(2.0));
    printf("sin %a = %a\n", 3.14, sin(3.14));
    printf("sin %a = %a\n", 5.0, sin(5.0));
    printf("sin %a = %a\n", 10.0, sin(10.0));
    printf("sin %a = %a\n", 1e8, sin(1e8));
}

static void test_sinf_branches(void)
{
    /* Branch 24: |x|<2^-12 */
    printf("sinf %a = %a\n", 0x1p-14f, sinf(0x1p-14f));
    printf("sinf %a = %a\n", -0x1p-14f, sinf(-0x1p-14f));
    /* Branch 25: x==0 */
    printf("sinf %a = %a\n", -0.0f, sinf(-0.0f));
    /* Branch 35: inf or NaN */
    printf("sinf %a = %a\n", F_INF, sinf(F_INF));
    printf("sinf %a = %a\n", F_NINF, sinf(F_NINF));
    printf("sinf nan = %a\n", sinf(F_NAN));
    /* n&3 cases */
    printf("sinf %a = %a\n", 2.0f, sinf(2.0f));
    printf("sinf %a = %a\n", 3.14f, sinf(3.14f));
    printf("sinf %a = %a\n", 5.0f, sinf(5.0f));
    printf("sinf %a = %a\n", 100.0f, sinf(100.0f));
}

static void test_tan_branches(void)
{
    /* Branch 98-99: NaN and large */
    printf("tan %a = %a\n", D_INF, tan(D_INF));
    printf("tan nan = %a\n", tan(D_NAN));
    printf("tan %a = %a\n", 0x1p-30, tan(0x1p-30));
    printf("tan %a = %a\n", -0.0, tan(-0.0));
    printf("tan %a = %a\n", 2.0, tan(2.0));
    printf("tan %a = %a\n", 3.14, tan(3.14));
    printf("tan %a = %a\n", 5.0, tan(5.0));
    printf("tan %a = %a\n", 10.0, tan(10.0));
    printf("tan %a = %a\n", 1e8, tan(1e8));
}

static void test_tanf_branches(void)
{
    printf("tanf %a = %a\n", F_INF, tanf(F_INF));
    printf("tanf nan = %a\n", tanf(F_NAN));
    printf("tanf %a = %a\n", 0x1p-30f, tanf(0x1p-30f));
    printf("tanf %a = %a\n", -0.0f, tanf(-0.0f));
    printf("tanf %a = %a\n", 2.0f, tanf(2.0f));
    printf("tanf %a = %a\n", 3.14f, tanf(3.14f));
    printf("tanf %a = %a\n", 5.0f, tanf(5.0f));
    printf("tanf %a = %a\n", 100.0f, tanf(100.0f));
    /* Branch 99: n&3 case 1 */
    printf("tanf %a = %a\n", -2.0f, tanf(-2.0f));
    printf("tanf %a = %a\n", -3.14f, tanf(-3.14f));
}

static void test_ceil_branches(void)
{
    /* ceild.c branches 68-119 */
    printf("ceil %a = %a\n", 0.0, ceil(0.0));
    printf("ceil %a = %a\n", -0.0, ceil(-0.0));
    printf("ceil %a = %a\n", 0x1p-60, ceil(0x1p-60));
    printf("ceil %a = %a\n", -0x1p-60, ceil(-0x1p-60));
    printf("ceil %a = %a\n", D_INF, ceil(D_INF));
    printf("ceil %a = %a\n", D_NINF, ceil(D_NINF));
    printf("ceil nan = %a\n", ceil(D_NAN));
    printf("ceil %a = %a\n", 0x1p51, ceil(0x1p51));
    printf("ceil %a = %a\n", -0x1p51, ceil(-0x1p51));
    printf("ceil %a = %a\n", 0x1p52, ceil(0x1p52));
    printf("ceil %a = %a\n", 1.5, ceil(1.5));
    printf("ceil %a = %a\n", -1.5, ceil(-1.5));
    printf("ceil %a = %a\n", -0.5, ceil(-0.5));
    printf("ceil %a = %a\n", 0.5, ceil(0.5));
    printf("ceil %a = %a\n", 1e15, ceil(1e15));
    printf("ceil %a = %a\n", -1e15, ceil(-1e15));
}

static void test_ceilf_branches(void)
{
    printf("ceilf %a = %a\n", 0.0f, ceilf(0.0f));
    printf("ceilf %a = %a\n", -0.0f, ceilf(-0.0f));
    printf("ceilf %a = %a\n", 0x1p-30f, ceilf(0x1p-30f));
    printf("ceilf %a = %a\n", -0x1p-30f, ceilf(-0x1p-30f));
    printf("ceilf %a = %a\n", F_INF, ceilf(F_INF));
    printf("ceilf nan = %a\n", ceilf(F_NAN));
    printf("ceilf %a = %a\n", 0x1p23f, ceilf(0x1p23f));
    printf("ceilf %a = %a\n", -0x1p23f, ceilf(-0x1p23f));
    printf("ceilf %a = %a\n", 1.5f, ceilf(1.5f));
    printf("ceilf %a = %a\n", -1.5f, ceilf(-1.5f));
    printf("ceilf %a = %a\n", 1e7f, ceilf(1e7f));
}

static void test_floor_branches(void)
{
    printf("floor %a = %a\n", 0.0, floor(0.0));
    printf("floor %a = %a\n", -0.0, floor(-0.0));
    printf("floor %a = %a\n", 0x1p-60, floor(0x1p-60));
    printf("floor %a = %a\n", -0x1p-60, floor(-0x1p-60));
    printf("floor %a = %a\n", D_INF, floor(D_INF));
    printf("floor %a = %a\n", D_NINF, floor(D_NINF));
    printf("floor nan = %a\n", floor(D_NAN));
    printf("floor %a = %a\n", 0x1p51, floor(0x1p51));
    printf("floor %a = %a\n", -0x1p51, floor(-0x1p51));
    printf("floor %a = %a\n", 1.5, floor(1.5));
    printf("floor %a = %a\n", -1.5, floor(-1.5));
    printf("floor %a = %a\n", 1e15, floor(1e15));
    printf("floor %a = %a\n", -1e15, floor(-1e15));
}

static void test_floorf_branches(void)
{
    printf("floorf %a = %a\n", 0.0f, floorf(0.0f));
    printf("floorf %a = %a\n", -0.0f, floorf(-0.0f));
    printf("floorf %a = %a\n", 0x1p-30f, floorf(0x1p-30f));
    printf("floorf %a = %a\n", -0x1p-30f, floorf(-0x1p-30f));
    printf("floorf %a = %a\n", F_INF, floorf(F_INF));
    printf("floorf nan = %a\n", floorf(F_NAN));
    printf("floorf %a = %a\n", 0x1p23f, floorf(0x1p23f));
    printf("floorf %a = %a\n", 1.5f, floorf(1.5f));
    printf("floorf %a = %a\n", -1.5f, floorf(-1.5f));
    printf("floorf %a = %a\n", 1e7f, floorf(1e7f));
}

static void test_trunc_branches(void)
{
    printf("trunc %a = %a\n", 0.0, trunc(0.0));
    printf("trunc %a = %a\n", -0.0, trunc(-0.0));
    printf("trunc %a = %a\n", 0x1p-60, trunc(0x1p-60));
    printf("trunc %a = %a\n", -0x1p-60, trunc(-0x1p-60));
    printf("trunc %a = %a\n", D_INF, trunc(D_INF));
    printf("trunc nan = %a\n", trunc(D_NAN));
    printf("trunc %a = %a\n", 1.5, trunc(1.5));
    printf("trunc %a = %a\n", -1.5, trunc(-1.5));
    printf("trunc %a = %a\n", 0x1p51, trunc(0x1p51));
}

static void test_truncf_branches(void)
{
    printf("truncf %a = %a\n", 0.0f, truncf(0.0f));
    printf("truncf %a = %a\n", -0.0f, truncf(-0.0f));
    printf("truncf %a = %a\n", 0x1p-30f, truncf(0x1p-30f));
    printf("truncf %a = %a\n", F_INF, truncf(F_INF));
    printf("truncf nan = %a\n", truncf(F_NAN));
    printf("truncf %a = %a\n", 1.5f, truncf(1.5f));
    printf("truncf %a = %a\n", -1.5f, truncf(-1.5f));
    printf("truncf %a = %a\n", 0x1p23f, truncf(0x1p23f));
}

static void test_rint_branches(void)
{
    printf("rint %a = %a\n", 0.0, rint(0.0));
    printf("rint %a = %a\n", -0.0, rint(-0.0));
    printf("rint %a = %a\n", 0x1p-60, rint(0x1p-60));
    printf("rint %a = %a\n", -0x1p-60, rint(-0x1p-60));
    printf("rint %a = %a\n", D_INF, rint(D_INF));
    printf("rint nan = %a\n", rint(D_NAN));
    printf("rint %a = %a\n", 1.5, rint(1.5));
    printf("rint %a = %a\n", -1.5, rint(-1.5));
    printf("rint %a = %a\n", 2.5, rint(2.5));
    printf("rint %a = %a\n", -2.5, rint(-2.5));
    printf("rint %a = %a\n", 0x1p52, rint(0x1p52));
}

static void test_rintf_branches(void)
{
    printf("rintf %a = %a\n", 0.0f, rintf(0.0f));
    printf("rintf %a = %a\n", -0.0f, rintf(-0.0f));
    printf("rintf %a = %a\n", 0x1p-30f, rintf(0x1p-30f));
    printf("rintf %a = %a\n", F_INF, rintf(F_INF));
    printf("rintf nan = %a\n", rintf(F_NAN));
    printf("rintf %a = %a\n", 1.5f, rintf(1.5f));
    printf("rintf %a = %a\n", -1.5f, rintf(-1.5f));
    printf("rintf %a = %a\n", 2.5f, rintf(2.5f));
    printf("rintf %a = %a\n", 0x1p23f, rintf(0x1p23f));
}

static void test_round_branches(void)
{
    printf("round %a = %a\n", 0.0, round(0.0));
    printf("round %a = %a\n", -0.0, round(-0.0));
    printf("round %a = %a\n", 0x1p-60, round(0x1p-60));
    printf("round %a = %a\n", -0x1p-60, round(-0x1p-60));
    printf("round %a = %a\n", D_INF, round(D_INF));
    printf("round nan = %a\n", round(D_NAN));
    printf("round %a = %a\n", 1.4, round(1.4));
    printf("round %a = %a\n", -1.4, round(-1.4));
    printf("round %a = %a\n", 0x1p51, round(0x1p51));
    printf("round %a = %a\n", -0x1p51, round(-0x1p51));
}

static void test_roundf_branches(void)
{
    printf("roundf %a = %a\n", 0.0f, roundf(0.0f));
    printf("roundf %a = %a\n", -0.0f, roundf(-0.0f));
    printf("roundf %a = %a\n", 0x1p-30f, roundf(0x1p-30f));
    printf("roundf %a = %a\n", F_INF, roundf(F_INF));
    printf("roundf nan = %a\n", roundf(F_NAN));
    printf("roundf %a = %a\n", 1.4f, roundf(1.4f));
    printf("roundf %a = %a\n", -1.4f, roundf(-1.4f));
    printf("roundf %a = %a\n", 0x1p23f, roundf(0x1p23f));
}

static void test_lrint_branches(void)
{
    printf("lrint %a = %ld\n", D_INF, lrint(D_INF));
    printf("lrint %a = %ld\n", D_NAN, lrint(D_NAN));
    printf("lrint %a = %ld\n", 0x1p60, lrint(0x1p60));
    printf("lrint %a = %ld\n", -0x1p60, lrint(-0x1p60));
    printf("lrint %a = %ld\n", 0.0, lrint(0.0));
    printf("lrint %a = %ld\n", -0.0, lrint(-0.0));
    printf("lrint %a = %ld\n", 0.5, lrint(0.5));
    printf("lrint %a = %ld\n", -0.5, lrint(-0.5));
}

static void test_lrintf_branches(void)
{
    printf("lrintf %a = %ld\n", F_INF, lrintf(F_INF));
    printf("lrintf %a = %ld\n", F_NAN, lrintf(F_NAN));
    printf("lrintf %a = %ld\n", 0x1p30f, lrintf(0x1p30f));
    printf("lrintf %a = %ld\n", -0x1p30f, lrintf(-0x1p30f));
    printf("lrintf %a = %ld\n", 0.5f, lrintf(0.5f));
    printf("lrintf %a = %ld\n", -0.5f, lrintf(-0.5f));
}

static void test_llrint_branches(void)
{
    printf("llrint %a = %lld\n", D_INF, llrint(D_INF));
    printf("llrint %a = %lld\n", D_NAN, llrint(D_NAN));
    printf("llrint %a = %lld\n", 0x1p62, llrint(0x1p62));
    printf("llrint %a = %lld\n", -0x1p62, llrint(-0x1p62));
    printf("llrint %a = %lld\n", 0.0, llrint(0.0));
    printf("llrint %a = %lld\n", 0.5, llrint(0.5));
    printf("llrint %a = %lld\n", -0.5, llrint(-0.5));
}

static void test_llrintf_branches(void)
{
    printf("llrintf %a = %lld\n", F_INF, llrintf(F_INF));
    printf("llrintf %a = %lld\n", F_NAN, llrintf(F_NAN));
    printf("llrintf %a = %lld\n", 0x1p30f, llrintf(0x1p30f));
    printf("llrintf %a = %lld\n", 0.5f, llrintf(0.5f));
    printf("llrintf %a = %lld\n", -0.5f, llrintf(-0.5f));
}

static void test_lround_branches(void)
{
    printf("lround %a = %ld\n", D_INF, lround(D_INF));
    printf("lround %a = %ld\n", D_NAN, lround(D_NAN));
    printf("lround %a = %ld\n", 0x1p60, lround(0x1p60));
    printf("lround %a = %ld\n", 0.0, lround(0.0));
    printf("lround %a = %ld\n", -0.0, lround(-0.0));
    printf("lround %a = %ld\n", 0.4, lround(0.4));
    printf("lround %a = %ld\n", -0.4, lround(-0.4));
}

static void test_lroundf_branches(void)
{
    printf("lroundf %a = %ld\n", F_INF, lroundf(F_INF));
    printf("lroundf %a = %ld\n", F_NAN, lroundf(F_NAN));
    printf("lroundf %a = %ld\n", 0x1p30f, lroundf(0x1p30f));
    printf("lroundf %a = %ld\n", 0.4f, lroundf(0.4f));
    printf("lroundf %a = %ld\n", -0.4f, lroundf(-0.4f));
}

static void test_llround_branches(void)
{
    printf("llround %a = %lld\n", D_INF, llround(D_INF));
    printf("llround %a = %lld\n", D_NAN, llround(D_NAN));
    printf("llround %a = %lld\n", 0x1p62, llround(0x1p62));
    printf("llround %a = %lld\n", 0.0, llround(0.0));
    printf("llround %a = %lld\n", 0.4, llround(0.4));
    printf("llround %a = %lld\n", -0.4, llround(-0.4));
}

static void test_llroundf_branches(void)
{
    printf("llroundf %a = %lld\n", F_INF, llroundf(F_INF));
    printf("llroundf %a = %lld\n", F_NAN, llroundf(F_NAN));
    printf("llroundf %a = %lld\n", 0x1p30f, llroundf(0x1p30f));
    printf("llroundf %a = %lld\n", 0.4f, llroundf(0.4f));
    printf("llroundf %a = %lld\n", -0.4f, llroundf(-0.4f));
}

static void test_fmax_branches(void)
{
    /* Branch 75: x is NaN */
    printf("fmax nan 1 = %a\n", fmax(D_NAN, 1.0));
    printf("fmax nan nan = %a\n", fmax(D_NAN, D_NAN));
    /* Branch 85: y is NaN */
    printf("fmax 1 nan = %a\n", fmax(1.0, D_NAN));
    /* Branch 99: x>y vs x<=y */
    printf("fmax %a %a = %a\n", 3.0, 2.0, fmax(3.0, 2.0));
    printf("fmax %a %a = %a\n", 2.0, 3.0, fmax(2.0, 3.0));
    printf("fmax %a %a = %a\n", -0.0, 0.0, fmax(-0.0, 0.0));
    printf("fmax %a %a = %a\n", 0.0, -0.0, fmax(0.0, -0.0));
    printf("fmax %a %a = %a\n", D_INF, 1.0, fmax(D_INF, 1.0));
    printf("fmax %a %a = %a\n", D_NINF, 1.0, fmax(D_NINF, 1.0));
}

static void test_fmaxf_branches(void)
{
    /* Branch 10: x is NaN */
    printf("fmaxf nan 1 = %a\n", fmaxf(F_NAN, 1.0f));
    printf("fmaxf nan nan = %a\n", fmaxf(F_NAN, F_NAN));
    /* Branch 20: y is NaN */
    printf("fmaxf 1 nan = %a\n", fmaxf(1.0f, F_NAN));
    /* Branch 34: x>y vs x<=y */
    printf("fmaxf %a %a = %a\n", 3.0f, 2.0f, fmaxf(3.0f, 2.0f));
    printf("fmaxf %a %a = %a\n", 2.0f, 3.0f, fmaxf(2.0f, 3.0f));
    printf("fmaxf %a %a = %a\n", F_INF, 1.0f, fmaxf(F_INF, 1.0f));
    printf("fmaxf %a %a = %a\n", F_NINF, 1.0f, fmaxf(F_NINF, 1.0f));
}

static void test_fmin_branches(void)
{
    /* Branch 75: x is NaN */
    printf("fmin nan 1 = %a\n", fmin(D_NAN, 1.0));
    printf("fmin nan nan = %a\n", fmin(D_NAN, D_NAN));
    /* Branch 85: y is NaN */
    printf("fmin 1 nan = %a\n", fmin(1.0, D_NAN));
    /* Branch 99: x<y vs x>=y */
    printf("fmin %a %a = %a\n", 3.0, 2.0, fmin(3.0, 2.0));
    printf("fmin %a %a = %a\n", 2.0, 3.0, fmin(2.0, 3.0));
    printf("fmin %a %a = %a\n", D_INF, 1.0, fmin(D_INF, 1.0));
    printf("fmin %a %a = %a\n", D_NINF, 1.0, fmin(D_NINF, 1.0));
}

static void test_fminf_branches(void)
{
    printf("fminf nan 1 = %a\n", fminf(F_NAN, 1.0f));
    printf("fminf nan nan = %a\n", fminf(F_NAN, F_NAN));
    printf("fminf 1 nan = %a\n", fminf(1.0f, F_NAN));
    printf("fminf %a %a = %a\n", 3.0f, 2.0f, fminf(3.0f, 2.0f));
    printf("fminf %a %a = %a\n", 2.0f, 3.0f, fminf(2.0f, 3.0f));
    printf("fminf %a %a = %a\n", F_INF, 1.0f, fminf(F_INF, 1.0f));
}

static void test_fpclassify_branches(void)
{
    /* fpclassifyd: NaN, subnormal, inf */
    printf("__fpclassifyd nan = %d\n", __fpclassifyd(D_NAN));
    printf("__fpclassifyd -nan = %d\n", __fpclassifyd(-D_NAN));
    printf("__fpclassifyd subnorm = %d\n", __fpclassifyd(D_SUBNORM));
    printf("__fpclassifyd -subnorm = %d\n", __fpclassifyd(-D_SUBNORM));
    printf("__fpclassifyd -inf = %d\n", __fpclassifyd(D_NINF));
    printf("__fpclassifyd -0 = %d\n", __fpclassifyd(-0.0));
    /* fpclassifyf */
    printf("__fpclassifyf nan = %d\n", __fpclassifyf(F_NAN));
    printf("__fpclassifyf subnorm = %d\n", __fpclassifyf(F_SUBNORM));
    printf("__fpclassifyf -inf = %d\n", __fpclassifyf(F_NINF));
    printf("__fpclassifyf -0 = %d\n", __fpclassifyf(-0.0f));
}

static void test_frexp_branches(void)
{
    int e;
    double m;
    /* Branch 84: x==0 or subnormal */
    m = frexp(0.0, &e);
    printf("frexp %a = %a exp %d\n", 0.0, m, e);
    m = frexp(-0.0, &e);
    printf("frexp %a = %a exp %d\n", -0.0, m, e);
    m = frexp(D_SUBNORM, &e);
    printf("frexp %a = %a exp %d\n", D_SUBNORM, m, e);
    /* Branch 85: inf or NaN */
    m = frexp(D_INF, &e);
    printf("frexp inf = %a exp %d\n", m, e);
    m = frexp(D_NAN, &e);
    printf("frexp nan = %a exp %d\n", m, e);
    /* Branch 93: subnormal normalization */
    m = frexp(0x1p-1050, &e);
    printf("frexp %a = %a exp %d\n", 0x1p-1050, m, e);
    /* Branch 97: negative */
    m = frexp(-2.0, &e);
    printf("frexp %a = %a exp %d\n", -2.0, m, e);
}

static void test_frexpf_branches(void)
{
    int e;
    float m;
    m = frexpf(0.0f, &e);
    printf("frexpf %a = %a exp %d\n", 0.0f, m, e);
    m = frexpf(-0.0f, &e);
    printf("frexpf %a = %a exp %d\n", -0.0f, m, e);
    m = frexpf(F_SUBNORM, &e);
    printf("frexpf %a = %a exp %d\n", F_SUBNORM, m, e);
    m = frexpf(F_INF, &e);
    printf("frexpf inf = %a exp %d\n", m, e);
    m = frexpf(F_NAN, &e);
    printf("frexpf nan = %a exp %d\n", m, e);
    m = frexpf(0x1p-130f, &e);
    printf("frexpf %a = %a exp %d\n", 0x1p-130f, m, e);
    m = frexpf(-2.0f, &e);
    printf("frexpf %a = %a exp %d\n", -2.0f, m, e);
}

static void test_modf_branches(void)
{
    double ipart;
    double f;
    f = modf(0.0, &ipart);
    printf("modf %a = %a ipart %a\n", 0.0, f, ipart);
    f = modf(-0.0, &ipart);
    printf("modf %a = %a ipart %a\n", -0.0, f, ipart);
    f = modf(D_INF, &ipart);
    printf("modf inf = %a ipart %a\n", f, ipart);
    f = modf(D_NINF, &ipart);
    printf("modf -inf = %a ipart %a\n", f, ipart);
    f = modf(D_NAN, &ipart);
    printf("modf nan = %a ipart %a\n", f, ipart);
    f = modf(0x1p53, &ipart);
    printf("modf %a = %a ipart %a\n", 0x1p53, f, ipart);
    f = modf(-0x1p53, &ipart);
    printf("modf %a = %a ipart %a\n", -0x1p53, f, ipart);
    f = modf(0.5, &ipart);
    printf("modf %a = %a ipart %a\n", 0.5, f, ipart);
    f = modf(-0.5, &ipart);
    printf("modf %a = %a ipart %a\n", -0.5, f, ipart);
}

static void test_modff_branches(void)
{
    float ipart;
    float f;
    f = modff(0.0f, &ipart);
    printf("modff %a = %a ipart %a\n", 0.0f, f, ipart);
    f = modff(-0.0f, &ipart);
    printf("modff %a = %a ipart %a\n", -0.0f, f, ipart);
    f = modff(F_INF, &ipart);
    printf("modff inf = %a ipart %a\n", f, ipart);
    f = modff(F_NAN, &ipart);
    printf("modff nan = %a ipart %a\n", f, ipart);
    f = modff(0x1p24f, &ipart);
    printf("modff %a = %a ipart %a\n", 0x1p24f, f, ipart);
    f = modff(0.5f, &ipart);
    printf("modff %a = %a ipart %a\n", 0.5f, f, ipart);
    f = modff(-0.5f, &ipart);
    printf("modff %a = %a ipart %a\n", -0.5f, f, ipart);
}

static void test_nextafter_branches(void)
{
    /* Branch 90-92: NaN, x==y */
    printf("nextafter nan 1 = %a\n", nextafter(D_NAN, 1.0));
    printf("nextafter 1 nan = %a\n", nextafter(1.0, D_NAN));
    printf("nextafter %a %a = %a\n", 1.0, 1.0, nextafter(1.0, 1.0));
    /* Branch 94: x==0 */
    printf("nextafter %a %a = %a\n", 0.0, 1.0, nextafter(0.0, 1.0));
    printf("nextafter %a %a = %a\n", 0.0, -1.0, nextafter(0.0, -1.0));
    printf("nextafter %a %a = %a\n", -0.0, 1.0, nextafter(-0.0, 1.0));
    printf("nextafter %a %a = %a\n", -0.0, -1.0, nextafter(-0.0, -1.0));
    /* Branch 105: x>0, x>y */
    printf("nextafter %a %a = %a\n", 2.0, 1.0, nextafter(2.0, 1.0));
    printf("nextafter %a %a = %a\n", 1.0, 2.0, nextafter(1.0, 2.0));
    /* Branch 120: x<0 */
    printf("nextafter %a %a = %a\n", -2.0, -1.0, nextafter(-2.0, -1.0));
    printf("nextafter %a %a = %a\n", -1.0, -2.0, nextafter(-1.0, -2.0));
    /* overflow */
    printf("nextafter %a %a = %a\n", 0x1.fffffffffffffp+1023, D_INF, nextafter(0x1.fffffffffffffp+1023, D_INF));
    /* underflow subnorm */
    printf("nextafter %a %a = %a\n", D_SUBNORM, 0.0, nextafter(D_SUBNORM, 0.0));
}

static void test_nextafterf_branches(void)
{
    printf("nextafterf nan 1 = %a\n", nextafterf(F_NAN, 1.0f));
    printf("nextafterf 1 nan = %a\n", nextafterf(1.0f, F_NAN));
    printf("nextafterf %a %a = %a\n", 1.0f, 1.0f, nextafterf(1.0f, 1.0f));
    printf("nextafterf %a %a = %a\n", 0.0f, 1.0f, nextafterf(0.0f, 1.0f));
    printf("nextafterf %a %a = %a\n", 0.0f, -1.0f, nextafterf(0.0f, -1.0f));
    printf("nextafterf %a %a = %a\n", 2.0f, 1.0f, nextafterf(2.0f, 1.0f));
    printf("nextafterf %a %a = %a\n", 1.0f, 2.0f, nextafterf(1.0f, 2.0f));
    printf("nextafterf %a %a = %a\n", -2.0f, -1.0f, nextafterf(-2.0f, -1.0f));
    printf("nextafterf %a %a = %a\n", F_SUBNORM, 0.0f, nextafterf(F_SUBNORM, 0.0f));
}

static void test_scalbn_branches(void)
{
    /* Branch 96: subnormal input */
    printf("scalbn %a %d = %a\n", D_SUBNORM, 1, scalbn(D_SUBNORM, 1));
    printf("scalbn %a %d = %a\n", D_SUBNORM, 1074, scalbn(D_SUBNORM, 1074));
    /* Branch 97: x==0, inf, nan */
    printf("scalbn %a %d = %a\n", 0.0, 5, scalbn(0.0, 5));
    printf("scalbn %a %d = %a\n", D_INF, 5, scalbn(D_INF, 5));
    printf("scalbn nan %d = %a\n", 5, scalbn(D_NAN, 5));
    /* Branch 105: large k */
    printf("scalbn %a %d = %a\n", 1.0, 2000, scalbn(1.0, 2000));
    printf("scalbn %a %d = %a\n", 1.0, -2000, scalbn(1.0, -2000));
    printf("scalbn %a %d = %a\n", 1.0, 600, scalbn(1.0, 600));
    printf("scalbn %a %d = %a\n", 1.0, -600, scalbn(1.0, -600));
    printf("scalbn %a %d = %a\n", 1.0, 100, scalbn(1.0, 100));
    printf("scalbn %a %d = %a\n", 1.0, -100, scalbn(1.0, -100));
}

static void test_scalbnf_branches(void)
{
    printf("scalbnf %a %d = %a\n", F_SUBNORM, 1, scalbnf(F_SUBNORM, 1));
    printf("scalbnf %a %d = %a\n", 0.0f, 5, scalbnf(0.0f, 5));
    printf("scalbnf %a %d = %a\n", F_INF, 5, scalbnf(F_INF, 5));
    printf("scalbnf nan %d = %a\n", 5, scalbnf(F_NAN, 5));
    printf("scalbnf %a %d = %a\n", 1.0f, 200, scalbnf(1.0f, 200));
    printf("scalbnf %a %d = %a\n", 1.0f, -200, scalbnf(1.0f, -200));
    printf("scalbnf %a %d = %a\n", 1.0f, 100, scalbnf(1.0f, 100));
    printf("scalbnf %a %d = %a\n", 1.0f, -100, scalbnf(1.0f, -100));
}

static void test_scalbln_branches(void)
{
    printf("scalbln %a %ld = %a\n", 1.0, 2000L, scalbln(1.0, 2000L));
    printf("scalbln %a %ld = %a\n", 1.0, -2000L, scalbln(1.0, -2000L));
    printf("scalbln %a %ld = %a\n", 1.0, 600L, scalbln(1.0, 600L));
    printf("scalbln %a %ld = %a\n", 1.0, -600L, scalbln(1.0, -600L));
    printf("scalbln %a %ld = %a\n", 0.0, 5L, scalbln(0.0, 5L));
    printf("scalbln %a %ld = %a\n", D_INF, 5L, scalbln(D_INF, 5L));
    printf("scalbln %a %ld = %a\n", D_SUBNORM, 1L, scalbln(D_SUBNORM, 1L));
}

static void test_scalblnf_branches(void)
{
    printf("scalblnf %a %ld = %a\n", 1.0f, 200L, scalblnf(1.0f, 200L));
    printf("scalblnf %a %ld = %a\n", 1.0f, -200L, scalblnf(1.0f, -200L));
    printf("scalblnf %a %ld = %a\n", 1.0f, 100L, scalblnf(1.0f, 100L));
    printf("scalblnf %a %ld = %a\n", 0.0f, 5L, scalblnf(0.0f, 5L));
    printf("scalblnf %a %ld = %a\n", F_INF, 5L, scalblnf(F_INF, 5L));
    printf("scalblnf %a %ld = %a\n", F_SUBNORM, 1L, scalblnf(F_SUBNORM, 1L));
}

static void test_ldexp_branches(void)
{
    /* ldexpd.c: subnormal, special */
    printf("ldexp %a %d = %a\n", D_SUBNORM, 1, ldexp(D_SUBNORM, 1));
    printf("ldexp %a %d = %a\n", 0.0, 5, ldexp(0.0, 5));
    printf("ldexp %a %d = %a\n", D_INF, 5, ldexp(D_INF, 5));
    printf("ldexp nan %d = %a\n", 5, ldexp(D_NAN, 5));
    printf("ldexp %a %d = %a\n", 1.0, 2000, ldexp(1.0, 2000));
    printf("ldexp %a %d = %a\n", 1.0, -2000, ldexp(1.0, -2000));
}

static void test_ldexpf_branches(void)
{
    printf("ldexpf %a %d = %a\n", F_SUBNORM, 1, ldexpf(F_SUBNORM, 1));
    printf("ldexpf %a %d = %a\n", 0.0f, 5, ldexpf(0.0f, 5));
    printf("ldexpf %a %d = %a\n", F_INF, 5, ldexpf(F_INF, 5));
    printf("ldexpf %a %d = %a\n", 1.0f, 200, ldexpf(1.0f, 200));
    printf("ldexpf %a %d = %a\n", 1.0f, -200, ldexpf(1.0f, -200));
}

static void test_ilogb_branches(void)
{
    /* ilogbd.c: 0, subnormal, inf, nan */
    printf("ilogb %a = %d\n", 0.0, ilogb(0.0));
    printf("ilogb %a = %d\n", D_INF, ilogb(D_INF));
    printf("ilogb %a = %d\n", D_NINF, ilogb(D_NINF));
    printf("ilogb nan = %d\n", ilogb(D_NAN));
    printf("ilogb %a = %d\n", D_SUBNORM, ilogb(D_SUBNORM));
    printf("ilogb %a = %d\n", -1.0, ilogb(-1.0));
    printf("ilogb %a = %d\n", 0x1p-1022, ilogb(0x1p-1022));
}

static void test_ilogbf_branches(void)
{
    printf("ilogbf %a = %d\n", 0.0f, ilogbf(0.0f));
    printf("ilogbf %a = %d\n", F_INF, ilogbf(F_INF));
    printf("ilogbf nan = %d\n", ilogbf(F_NAN));
    printf("ilogbf %a = %d\n", F_SUBNORM, ilogbf(F_SUBNORM));
    printf("ilogbf %a = %d\n", -1.0f, ilogbf(-1.0f));
}

static void test_hypot_branches(void)
{
    /* hypotd.c: inf, nan, large */
    printf("hypot %a %a = %a\n", D_INF, 1.0, hypot(D_INF, 1.0));
    printf("hypot %a %a = %a\n", 1.0, D_INF, hypot(1.0, D_INF));
    printf("hypot %a %a = %a\n", D_NINF, 1.0, hypot(D_NINF, 1.0));
    printf("hypot nan %a = %a\n", 1.0, hypot(D_NAN, 1.0));
    printf("hypot %a nan = %a\n", 1.0, hypot(1.0, D_NAN));
    printf("hypot %a %a = %a\n", D_SUBNORM, 0.0, hypot(D_SUBNORM, 0.0));
    printf("hypot %a %a = %a\n", 0x1p600, 1.0, hypot(0x1p600, 1.0));
    printf("hypot %a %a = %a\n", 0x1p-600, 1.0, hypot(0x1p-600, 1.0));
}

static void test_hypotf_branches(void)
{
    printf("hypotf %a %a = %a\n", F_INF, 1.0f, hypotf(F_INF, 1.0f));
    printf("hypotf %a %a = %a\n", 1.0f, F_INF, hypotf(1.0f, F_INF));
    printf("hypotf nan %a = %a\n", 1.0f, hypotf(F_NAN, 1.0f));
    printf("hypotf %a %a = %a\n", 0x1p60f, 1.0f, hypotf(0x1p60f, 1.0f));
    printf("hypotf %a %a = %a\n", 0x1p-60f, 1.0f, hypotf(0x1p-60f, 1.0f));
}

static void test_cbrt_branches(void)
{
    /* cbrtd.c: subnormal, negative */
    printf("cbrt %a = %a\n", D_SUBNORM, cbrt(D_SUBNORM));
    printf("cbrt %a = %a\n", -0.0, cbrt(-0.0));
    printf("cbrt %a = %a\n", D_INF, cbrt(D_INF));
    printf("cbrt %a = %a\n", D_NINF, cbrt(D_NINF));
    printf("cbrt nan = %a\n", cbrt(D_NAN));
    printf("cbrt %a = %a\n", 0x1p-1020, cbrt(0x1p-1020));
}

static void test_cbrtf_branches(void)
{
    printf("cbrtf %a = %a\n", F_SUBNORM, cbrtf(F_SUBNORM));
    printf("cbrtf %a = %a\n", -0.0f, cbrtf(-0.0f));
    printf("cbrtf %a = %a\n", F_INF, cbrtf(F_INF));
    printf("cbrtf nan = %a\n", cbrtf(F_NAN));
    printf("cbrtf %a = %a\n", 0x1p-126f, cbrtf(0x1p-126f));
}

static void test_sqrt_branches(void)
{
    /* sqrtd.c: negative, subnormal, inf, nan */
    printf("sqrt %a = %a\n", -1.0, sqrt(-1.0));
    printf("sqrt %a = %a\n", -0.0, sqrt(-0.0));
    printf("sqrt %a = %a\n", D_INF, sqrt(D_INF));
    printf("sqrt nan = %a\n", sqrt(D_NAN));
    printf("sqrt %a = %a\n", D_SUBNORM, sqrt(D_SUBNORM));
    printf("sqrt %a = %a\n", 0x1p-1022, sqrt(0x1p-1022));
    printf("sqrt %a = %a\n", 3.0, sqrt(3.0));
    printf("sqrt %a = %a\n", 0x1p1000, sqrt(0x1p1000));
}

static void test_sqrtf_branches(void)
{
    printf("sqrtf %a = %a\n", -1.0f, sqrtf(-1.0f));
    printf("sqrtf %a = %a\n", -0.0f, sqrtf(-0.0f));
    printf("sqrtf %a = %a\n", F_INF, sqrtf(F_INF));
    printf("sqrtf nan = %a\n", sqrtf(F_NAN));
    printf("sqrtf %a = %a\n", F_SUBNORM, sqrtf(F_SUBNORM));
    printf("sqrtf %a = %a\n", 3.0f, sqrtf(3.0f));
}

static void test_pow_branches(void)
{
    /* powd.c: many special cases */
    /* y==0 → 1 */
    printf("pow %a %a = %a\n", 1.0, 0.0, pow(1.0, 0.0));
    printf("pow %a %a = %a\n", D_NAN, 0.0, pow(D_NAN, 0.0));
    /* NaN cases */
    printf("pow nan %a = %a\n", 1.0, pow(D_NAN, 1.0));
    printf("pow %a nan = %a\n", 1.0, pow(1.0, D_NAN));
    printf("pow %a nan = %a\n", 2.0, pow(2.0, D_NAN));
    /* x==1 */
    printf("pow %a %a = %a\n", 1.0, D_NAN, pow(1.0, D_NAN));
    /* y==±inf */
    printf("pow %a %a = %a\n", 1.0, D_INF, pow(1.0, D_INF));
    printf("pow %a %a = %a\n", 2.0, D_INF, pow(2.0, D_INF));
    printf("pow %a %a = %a\n", 0.5, D_INF, pow(0.5, D_INF));
    printf("pow %a %a = %a\n", 2.0, D_NINF, pow(2.0, D_NINF));
    printf("pow %a %a = %a\n", 0.5, D_NINF, pow(0.5, D_NINF));
    /* x==±inf */
    printf("pow %a %a = %a\n", D_INF, 2.0, pow(D_INF, 2.0));
    printf("pow %a %a = %a\n", D_INF, -2.0, pow(D_INF, -2.0));
    printf("pow %a %a = %a\n", D_NINF, 2.0, pow(D_NINF, 2.0));
    printf("pow %a %a = %a\n", D_NINF, 3.0, pow(D_NINF, 3.0));
    printf("pow %a %a = %a\n", D_NINF, -3.0, pow(D_NINF, -3.0));
    printf("pow %a %a = %a\n", D_INF, D_INF, pow(D_INF, D_INF));
    printf("pow %a %a = %a\n", D_INF, D_NINF, pow(D_INF, D_NINF));
    /* x==0 */
    printf("pow %a %a = %a\n", 0.0, 1.0, pow(0.0, 1.0));
    printf("pow %a %a = %a\n", 0.0, -1.0, pow(0.0, -1.0));
    printf("pow %a %a = %a\n", -0.0, 1.0, pow(-0.0, 1.0));
    printf("pow %a %a = %a\n", -0.0, 2.0, pow(-0.0, 2.0));
    printf("pow %a %a = %a\n", -0.0, -1.0, pow(-0.0, -1.0));
    printf("pow %a %a = %a\n", 0.0, D_INF, pow(0.0, D_INF));
    printf("pow %a %a = %a\n", 0.0, D_NINF, pow(0.0, D_NINF));
    /* negative base */
    printf("pow %a %a = %a\n", -2.0, 3.0, pow(-2.0, 3.0));
    printf("pow %a %a = %a\n", -2.0, 2.0, pow(-2.0, 2.0));
    printf("pow %a %a = %a\n", -2.0, 0.5, pow(-2.0, 0.5));
    printf("pow %a %a = %a\n", -1.0, D_INF, pow(-1.0, D_INF));
    printf("pow %a %a = %a\n", -1.0, D_NINF, pow(-1.0, D_NINF));
    /* large results */
    printf("pow %a %a = %a\n", 2.0, 1024.0, pow(2.0, 1024.0));
    printf("pow %a %a = %a\n", 2.0, -1075.0, pow(2.0, -1075.0));
    /* normal values */
    printf("pow %a %a = %a\n", 2.0, 0.5, pow(2.0, 0.5));
    printf("pow %a %a = %a\n", 2.0, -1.0, pow(2.0, -1.0));
    printf("pow %a %a = %a\n", 0.5, 2.0, pow(0.5, 2.0));
    printf("pow %a %a = %a\n", 0.5, -2.0, pow(0.5, -2.0));
}

static void test_powf_branches(void)
{
    printf("powf %a %a = %a\n", D_NAN, 0.0f, (double)powf(F_NAN, 0.0f));
    printf("powf nan %a = %a\n", 1.0f, (double)powf(F_NAN, 1.0f));
    printf("powf %a nan = %a\n", 2.0f, (double)powf(2.0f, F_NAN));
    printf("powf %a %a = %a\n", 1.0f, D_NAN, (double)powf(1.0f, F_NAN));
    printf("powf %a %a = %a\n", 2.0f, F_INF, (double)powf(2.0f, F_INF));
    printf("powf %a %a = %a\n", 0.5f, F_INF, (double)powf(0.5f, F_INF));
    printf("powf %a %a = %a\n", 2.0f, F_NINF, (double)powf(2.0f, F_NINF));
    printf("powf %a %a = %a\n", F_INF, 2.0f, (double)powf(F_INF, 2.0f));
    printf("powf %a %a = %a\n", F_NINF, 3.0f, (double)powf(F_NINF, 3.0f));
    printf("powf %a %a = %a\n", 0.0f, 1.0f, (double)powf(0.0f, 1.0f));
    printf("powf %a %a = %a\n", 0.0f, -1.0f, (double)powf(0.0f, -1.0f));
    printf("powf %a %a = %a\n", -2.0f, 3.0f, (double)powf(-2.0f, 3.0f));
    printf("powf %a %a = %a\n", -2.0f, 2.0f, (double)powf(-2.0f, 2.0f));
    printf("powf %a %a = %a\n", 2.0f, 200.0f, (double)powf(2.0f, 200.0f));
    printf("powf %a %a = %a\n", 2.0f, -200.0f, (double)powf(2.0f, -200.0f));
    printf("powf %a %a = %a\n", 2.0f, 0.5f, (double)powf(2.0f, 0.5f));
}

static void test_fmod_branches(void)
{
    /* fmodd.c: various special cases */
    printf("fmod %a %a = %a\n", D_INF, 1.0, fmod(D_INF, 1.0));
    printf("fmod %a %a = %a\n", 1.0, 0.0, fmod(1.0, 0.0));
    printf("fmod nan %a = %a\n", 1.0, fmod(D_NAN, 1.0));
    printf("fmod %a nan = %a\n", 1.0, fmod(1.0, D_NAN));
    printf("fmod %a %a = %a\n", 0.0, 1.0, fmod(0.0, 1.0));
    printf("fmod %a %a = %a\n", -0.0, 1.0, fmod(-0.0, 1.0));
    printf("fmod %a %a = %a\n", 0x1p-1074, 1.0, fmod(0x1p-1074, 1.0));
    printf("fmod %a %a = %a\n", 1.0, 0x1p-1074, fmod(1.0, 0x1p-1074));
    printf("fmod %a %a = %a\n", 5.0, 0x1p-1074, fmod(5.0, 0x1p-1074));
    printf("fmod %a %a = %a\n", 0x1p1000, 0x1p-1022, fmod(0x1p1000, 0x1p-1022));
}

static void test_fmodf_branches(void)
{
    printf("fmodf %a %a = %a\n", F_INF, 1.0f, fmodf(F_INF, 1.0f));
    printf("fmodf %a %a = %a\n", 1.0f, 0.0f, fmodf(1.0f, 0.0f));
    printf("fmodf nan %a = %a\n", 1.0f, fmodf(F_NAN, 1.0f));
    printf("fmodf %a %a = %a\n", 0.0f, 1.0f, fmodf(0.0f, 1.0f));
    printf("fmodf %a %a = %a\n", -0.0f, 1.0f, fmodf(-0.0f, 1.0f));
    printf("fmodf %a %a = %a\n", 0x1p-149f, 1.0f, fmodf(0x1p-149f, 1.0f));
    printf("fmodf %a %a = %a\n", 1.0f, 0x1p-149f, fmodf(1.0f, 0x1p-149f));
}

static void test_remainder_branches(void)
{
    /* remainderd.c */
    printf("remainder %a %a = %a\n", D_INF, 1.0, remainder(D_INF, 1.0));
    printf("remainder %a %a = %a\n", 1.0, 0.0, remainder(1.0, 0.0));
    printf("remainder nan %a = %a\n", 1.0, remainder(D_NAN, 1.0));
    printf("remainder %a %a = %a\n", 0.0, 1.0, remainder(0.0, 1.0));
    printf("remainder %a %a = %a\n", 1.0, D_INF, remainder(1.0, D_INF));
    printf("remainder %a %a = %a\n", 3.0, 2.0, remainder(3.0, 2.0));
    printf("remainder %a %a = %a\n", -3.0, 2.0, remainder(-3.0, 2.0));
    printf("remainder %a %a = %a\n", 0x1p-1074, 1.0, remainder(0x1p-1074, 1.0));
}

static void test_remainderf_branches(void)
{
    printf("remainderf %a %a = %a\n", F_INF, 1.0f, remainderf(F_INF, 1.0f));
    printf("remainderf %a %a = %a\n", 1.0f, 0.0f, remainderf(1.0f, 0.0f));
    printf("remainderf nan %a = %a\n", 1.0f, remainderf(F_NAN, 1.0f));
    printf("remainderf %a %a = %a\n", 0.0f, 1.0f, remainderf(0.0f, 1.0f));
    printf("remainderf %a %a = %a\n", 1.0f, F_INF, remainderf(1.0f, F_INF));
    printf("remainderf %a %a = %a\n", 3.0f, 2.0f, remainderf(3.0f, 2.0f));
}

static void test_remquo_branches(void)
{
    int q;
    double r;
    r = remquo(D_INF, 1.0, &q);
    printf("remquo inf 1 = %a quo %d\n", r, q);
    r = remquo(1.0, 0.0, &q);
    printf("remquo 1 0 = %a quo %d\n", r, q);
    r = remquo(D_NAN, 1.0, &q);
    printf("remquo nan 1 = %a quo %d\n", r, q);
    r = remquo(0.0, 1.0, &q);
    printf("remquo 0 1 = %a quo %d\n", r, q);
    r = remquo(-0.0, 1.0, &q);
    printf("remquo -0 1 = %a quo %d\n", r, q);
    r = remquo(1.0, D_INF, &q);
    printf("remquo 1 inf = %a quo %d\n", r, q);
    r = remquo(7.0, 3.0, &q);
    printf("remquo %a %a = %a quo %d\n", 7.0, 3.0, r, q);
    r = remquo(-7.0, 3.0, &q);
    printf("remquo %a %a = %a quo %d\n", -7.0, 3.0, r, q);
}

static void test_remquof_branches(void)
{
    int q;
    float r;
    r = remquof(F_INF, 1.0f, &q);
    printf("remquof inf 1 = %a quo %d\n", r, q);
    r = remquof(1.0f, 0.0f, &q);
    printf("remquof 1 0 = %a quo %d\n", r, q);
    r = remquof(0.0f, 1.0f, &q);
    printf("remquof 0 1 = %a quo %d\n", r, q);
    r = remquof(-0.0f, 1.0f, &q);
    printf("remquof -0 1 = %a quo %d\n", r, q);
    r = remquof(1.0f, F_INF, &q);
    printf("remquof 1 inf = %a quo %d\n", r, q);
    r = remquof(7.0f, 3.0f, &q);
    printf("remquof %a %a = %a quo %d\n", 7.0f, 3.0f, r, q);
}

static void test_erf_branches(void)
{
    /* erfd.c */
    printf("erf %a = %a\n", D_INF, erf(D_INF));
    printf("erf %a = %a\n", D_NINF, erf(D_NINF));
    printf("erf nan = %a\n", erf(D_NAN));
    printf("erf %a = %a\n", 0x1p-30, erf(0x1p-30));
    printf("erf %a = %a\n", -0x1p-30, erf(-0x1p-30));
    printf("erf %a = %a\n", -0.0, erf(-0.0));
    printf("erf %a = %a\n", 0.5, erf(0.5));
    printf("erf %a = %a\n", -0.5, erf(-0.5));
    printf("erf %a = %a\n", 1.5, erf(1.5));
    printf("erf %a = %a\n", 4.0, erf(4.0));
    printf("erf %a = %a\n", 6.0, erf(6.0));
    printf("erf %a = %a\n", 20.0, erf(20.0));
    printf("erf %a = %a\n", -4.0, erf(-4.0));
}

static void test_erff_branches(void)
{
    printf("erff %a = %a\n", F_INF, erff(F_INF));
    printf("erff %a = %a\n", F_NINF, erff(F_NINF));
    printf("erff nan = %a\n", erff(F_NAN));
    printf("erff %a = %a\n", 0x1p-30f, erff(0x1p-30f));
    printf("erff %a = %a\n", -0.0f, erff(-0.0f));
    printf("erff %a = %a\n", 0.5f, erff(0.5f));
    printf("erff %a = %a\n", -0.5f, erff(-0.5f));
    printf("erff %a = %a\n", 1.5f, erff(1.5f));
    printf("erff %a = %a\n", 4.0f, erff(4.0f));
    printf("erff %a = %a\n", 10.0f, erff(10.0f));
    printf("erff %a = %a\n", -4.0f, erff(-4.0f));
}

static void test_erfc_branches(void)
{
    /* erfcd.c */
    printf("erfc %a = %a\n", D_INF, erfc(D_INF));
    printf("erfc %a = %a\n", D_NINF, erfc(D_NINF));
    printf("erfc nan = %a\n", erfc(D_NAN));
    printf("erfc %a = %a\n", 0x1p-30, erfc(0x1p-30));
    printf("erfc %a = %a\n", -0.0, erfc(-0.0));
    printf("erfc %a = %a\n", 0.5, erfc(0.5));
    printf("erfc %a = %a\n", -0.5, erfc(-0.5));
    printf("erfc %a = %a\n", 1.5, erfc(1.5));
    printf("erfc %a = %a\n", 4.0, erfc(4.0));
    printf("erfc %a = %a\n", 6.0, erfc(6.0));
    printf("erfc %a = %a\n", 20.0, erfc(20.0));
    printf("erfc %a = %a\n", -4.0, erfc(-4.0));
    printf("erfc %a = %a\n", 28.0, erfc(28.0));
}

static void test_erfcf_branches(void)
{
    printf("erfcf %a = %a\n", F_INF, erfcf(F_INF));
    printf("erfcf %a = %a\n", F_NINF, erfcf(F_NINF));
    printf("erfcf nan = %a\n", erfcf(F_NAN));
    printf("erfcf %a = %a\n", 0x1p-30f, erfcf(0x1p-30f));
    printf("erfcf %a = %a\n", -0.0f, erfcf(-0.0f));
    printf("erfcf %a = %a\n", 0.5f, erfcf(0.5f));
    printf("erfcf %a = %a\n", -0.5f, erfcf(-0.5f));
    printf("erfcf %a = %a\n", 1.5f, erfcf(1.5f));
    printf("erfcf %a = %a\n", 4.0f, erfcf(4.0f));
    printf("erfcf %a = %a\n", 10.0f, erfcf(10.0f));
    printf("erfcf %a = %a\n", -4.0f, erfcf(-4.0f));
}

static void test_tgamma_branches(void)
{
    /* tgammad.c */
    printf("tgamma %a = %a\n", D_INF, tgamma(D_INF));
    printf("tgamma %a = %a\n", D_NINF, tgamma(D_NINF));
    printf("tgamma nan = %a\n", tgamma(D_NAN));
    printf("tgamma %a = %a\n", 0.0, tgamma(0.0));
    printf("tgamma %a = %a\n", -0.0, tgamma(-0.0));
    printf("tgamma %a = %a\n", -1.0, tgamma(-1.0));
    printf("tgamma %a = %a\n", 0.5, tgamma(0.5));
    printf("tgamma %a = %a\n", -0.5, tgamma(-0.5));
    printf("tgamma %a = %a\n", 10.0, tgamma(10.0));
    printf("tgamma %a = %a\n", 172.0, tgamma(172.0));
    printf("tgamma %a = %a\n", -100.5, tgamma(-100.5));
}

static void test_tgammaf_branches(void)
{
    printf("tgammaf %a = %a\n", F_INF, tgammaf(F_INF));
    printf("tgammaf %a = %a\n", F_NINF, tgammaf(F_NINF));
    printf("tgammaf nan = %a\n", tgammaf(F_NAN));
    printf("tgammaf %a = %a\n", 0.0f, tgammaf(0.0f));
    printf("tgammaf %a = %a\n", -0.0f, tgammaf(-0.0f));
    printf("tgammaf %a = %a\n", -1.0f, tgammaf(-1.0f));
    printf("tgammaf %a = %a\n", 0.5f, tgammaf(0.5f));
    printf("tgammaf %a = %a\n", 36.0f, tgammaf(36.0f));
}

static void test_lgamma_branches(void)
{
    printf("lgamma %a = %a\n", D_INF, lgamma(D_INF));
    printf("lgamma %a = %a\n", D_NINF, lgamma(D_NINF));
    printf("lgamma nan = %a\n", lgamma(D_NAN));
    printf("lgamma %a = %a\n", 0.0, lgamma(0.0));
    printf("lgamma %a = %a\n", -0.0, lgamma(-0.0));
    printf("lgamma %a = %a\n", -1.0, lgamma(-1.0));
    printf("lgamma %a = %a\n", 0.5, lgamma(0.5));
    printf("lgamma %a = %a\n", -0.5, lgamma(-0.5));
    printf("lgamma %a = %a\n", 10.0, lgamma(10.0));
    printf("lgamma %a = %a\n", 0x1p-30, lgamma(0x1p-30));
    printf("lgamma %a = %a\n", -2.5, lgamma(-2.5));
    printf("lgamma %a = %a\n", 3.0, lgamma(3.0));
    printf("lgamma %a = %a\n", 8.0, lgamma(8.0));
}

static void test_lgammaf_branches(void)
{
    printf("lgammaf %a = %a\n", F_INF, lgammaf(F_INF));
    printf("lgammaf %a = %a\n", F_NINF, lgammaf(F_NINF));
    printf("lgammaf nan = %a\n", lgammaf(F_NAN));
    printf("lgammaf %a = %a\n", 0.0f, lgammaf(0.0f));
    printf("lgammaf %a = %a\n", -1.0f, lgammaf(-1.0f));
    printf("lgammaf %a = %a\n", 0.5f, lgammaf(0.5f));
    printf("lgammaf %a = %a\n", -0.5f, lgammaf(-0.5f));
    printf("lgammaf %a = %a\n", 10.0f, lgammaf(10.0f));
    printf("lgammaf %a = %a\n", 0x1p-30f, lgammaf(0x1p-30f));
    printf("lgammaf %a = %a\n", -2.5f, lgammaf(-2.5f));
}

static void test_j0_branches(void)
{
    /* j0d.c */
    printf("j0 %a = %a\n", D_INF, j0(D_INF));
    printf("j0 %a = %a\n", D_NINF, j0(D_NINF));
    printf("j0 nan = %a\n", j0(D_NAN));
    printf("j0 %a = %a\n", 0.0, j0(0.0));
    printf("j0 %a = %a\n", 0x1p-30, j0(0x1p-30));
    printf("j0 %a = %a\n", 3.0, j0(3.0));
    printf("j0 %a = %a\n", 8.0, j0(8.0));
    printf("j0 %a = %a\n", 20.0, j0(20.0));
    printf("j0 %a = %a\n", 100.0, j0(100.0));
}

static void test_j1_branches(void)
{
    /* j1d.c */
    printf("j1 %a = %a\n", D_INF, j1(D_INF));
    printf("j1 %a = %a\n", D_NINF, j1(D_NINF));
    printf("j1 nan = %a\n", j1(D_NAN));
    printf("j1 %a = %a\n", 0.0, j1(0.0));
    printf("j1 %a = %a\n", 0x1p-30, j1(0x1p-30));
    printf("j1 %a = %a\n", 3.0, j1(3.0));
    printf("j1 %a = %a\n", 8.0, j1(8.0));
    printf("j1 %a = %a\n", 20.0, j1(20.0));
}

static void test_jn_branches(void)
{
    /* jnd.c */
    printf("jn %d %a = %a\n", 0, D_INF, jn(0, D_INF));
    printf("jn %d %a = %a\n", 1, D_NAN, jn(1, D_NAN));
    printf("jn %d %a = %a\n", 5, 0.0, jn(5, 0.0));
    printf("jn %d %a = %a\n", 5, 0x1p-30, jn(5, 0x1p-30));
    printf("jn %d %a = %a\n", 3, 5.0, jn(3, 5.0));
    printf("jn %d %a = %a\n", 5, 20.0, jn(5, 20.0));
    printf("jn %d %a = %a\n", 10, 50.0, jn(10, 50.0));
    printf("jn %d %a = %a\n", -1, 1.0, jn(-1, 1.0));
    printf("jn %d %a = %a\n", 2, -1.0, jn(2, -1.0));
}

static void test_y0_branches(void)
{
    /* y0d.c */
    printf("y0 %a = %a\n", 0.0, y0(0.0));
    printf("y0 %a = %a\n", -1.0, y0(-1.0));
    printf("y0 %a = %a\n", D_INF, y0(D_INF));
    printf("y0 nan = %a\n", y0(D_NAN));
    printf("y0 %a = %a\n", 0x1p-30, y0(0x1p-30));
    printf("y0 %a = %a\n", 3.0, y0(3.0));
    printf("y0 %a = %a\n", 8.0, y0(8.0));
    printf("y0 %a = %a\n", 20.0, y0(20.0));
}

static void test_y1_branches(void)
{
    /* y1d.c */
    printf("y1 %a = %a\n", 0.0, y1(0.0));
    printf("y1 %a = %a\n", -1.0, y1(-1.0));
    printf("y1 %a = %a\n", D_INF, y1(D_INF));
    printf("y1 nan = %a\n", y1(D_NAN));
    printf("y1 %a = %a\n", 0x1p-30, y1(0x1p-30));
    printf("y1 %a = %a\n", 3.0, y1(3.0));
    printf("y1 %a = %a\n", 8.0, y1(8.0));
    printf("y1 %a = %a\n", 20.0, y1(20.0));
}

static void test_yn_branches(void)
{
    /* ynd.c */
    printf("yn %d %a = %a\n", 0, 0.0, yn(0, 0.0));
    printf("yn %d %a = %a\n", 1, -1.0, yn(1, -1.0));
    printf("yn %d %a = %a\n", 1, D_INF, yn(1, D_INF));
    printf("yn %d %a = %a\n", 1, D_NAN, yn(1, D_NAN));
    printf("yn %d %a = %a\n", 2, 0x1p-30, yn(2, 0x1p-30));
    printf("yn %d %a = %a\n", 5, 1.0, yn(5, 1.0));
    printf("yn %d %a = %a\n", 5, 20.0, yn(5, 20.0));
    printf("yn %d %a = %a\n", 10, 50.0, yn(10, 50.0));
}

static void test_csqrt_branches(void)
{
    /* csqrtd.c */
    double complex w;
    double complex z;
    /* Branch: x<0, y==0 */
    z = CMPLX(-4.0, 0.0);
    w = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(-4.0, -0.0);
    w = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    /* Branch: NaN */
    z = CMPLX(D_NAN, 1.0);
    w = csqrt(z);
    printf("csqrt nan+%ai = %a+%ai\n", cimag(z), creal(w), cimag(w));
    z = CMPLX(1.0, D_NAN);
    w = csqrt(z);
    printf("csqrt %a+nani = %a+%ai\n", creal(z), creal(w), cimag(w));
    /* Branch: inf */
    z = CMPLX(D_INF, 1.0);
    w = csqrt(z);
    printf("csqrt inf+%ai = %a+%ai\n", cimag(z), creal(w), cimag(w));
    z = CMPLX(D_NINF, 1.0);
    w = csqrt(z);
    printf("csqrt -inf+%ai = %a+%ai\n", cimag(z), creal(w), cimag(w));
    z = CMPLX(1.0, D_INF);
    w = csqrt(z);
    printf("csqrt %a+infi = %a+%ai\n", creal(z), creal(w), cimag(w));
    /* large */
    z = CMPLX(0x1p1000, 0x1p1000);
    w = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    /* subnormal */
    z = CMPLX(D_SUBNORM, 0.0);
    w = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
}

static void test_csqrtf_branches(void)
{
    float complex w;
    float complex z;
    z = CMPLXF(-4.0f, 0.0f);
    w = csqrtf(z);
    printf("csqrtf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
    z = CMPLXF(F_NAN, 1.0f);
    w = csqrtf(z);
    printf("csqrtf nan+%ai = %a+%ai\n", cimagf(z), crealf(w), cimagf(w));
    z = CMPLXF(F_INF, 1.0f);
    w = csqrtf(z);
    printf("csqrtf inf+%ai = %a+%ai\n", cimagf(z), crealf(w), cimagf(w));
    z = CMPLXF(F_NINF, 1.0f);
    w = csqrtf(z);
    printf("csqrtf -inf+%ai = %a+%ai\n", cimagf(z), crealf(w), cimagf(w));
    z = CMPLXF(1.0f, F_INF);
    w = csqrtf(z);
    printf("csqrtf %a+infi = %a+%ai\n", crealf(z), crealf(w), cimagf(w));
}

static void test_ctan_branches(void)
{
    /* ctand.c */
    double complex w;
    double complex z;
    z = CMPLX(0.0, 0.0);
    w = ctan(z);
    printf("ctan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(0.5, 2.0);
    w = ctan(z);
    printf("ctan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(D_NAN, 1.0);
    w = ctan(z);
    printf("ctan nan+%ai = %a+%ai\n", cimag(z), creal(w), cimag(w));
    z = CMPLX(1.0, D_INF);
    w = ctan(z);
    printf("ctan %a+infi = %a+%ai\n", creal(z), creal(w), cimag(w));
    z = CMPLX(1.0, D_NINF);
    w = ctan(z);
    printf("ctan %a-infi = %a+%ai\n", creal(z), creal(w), cimag(w));
    z = CMPLX(1.0, 20.0);
    w = ctan(z);
    printf("ctan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
}

static void test_ctanf_branches(void)
{
    /* ctanf.c */
    float complex w;
    float complex z;
    z = CMPLXF(0.5f, 2.0f);
    w = ctanf(z);
    printf("ctanf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
    z = CMPLXF(F_NAN, 1.0f);
    w = ctanf(z);
    printf("ctanf nan+%ai = %a+%ai\n", cimagf(z), crealf(w), cimagf(w));
    z = CMPLXF(1.0f, F_INF);
    w = ctanf(z);
    printf("ctanf %a+infi = %a+%ai\n", crealf(z), crealf(w), cimagf(w));
    z = CMPLXF(1.0f, 20.0f);
    w = ctanf(z);
    printf("ctanf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
}

static void test_cpow_branches(void)
{
    /* cpowd.c */
    double complex w;
    double complex z = CMPLX(0.0, 0.0);
    double complex p = CMPLX(2.0, 0.0);
    w = cpow(z, p);
    printf("cpow 0+0i 2+0i = %a+%ai\n", creal(w), cimag(w));
    z = CMPLX(-1.0, 0.0);
    p = CMPLX(1.0, 0.0);
    w = cpow(z, p);
    printf("cpow -1+0i 1+0i = %a+%ai\n", creal(w), cimag(w));
    z = CMPLX(2.0, 1.0);
    p = CMPLX(0.5, 0.5);
    w = cpow(z, p);
    printf("cpow %a+%ai %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(p), cimag(p), creal(w), cimag(w));
}

static void test_cpowf_branches(void)
{
    float complex w;
    float complex z = CMPLXF(0.0f, 0.0f);
    float complex p = CMPLXF(2.0f, 0.0f);
    w = cpowf(z, p);
    printf("cpowf 0+0i 2+0i = %a+%ai\n", crealf(w), cimagf(w));
    z = CMPLXF(2.0f, 1.0f);
    p = CMPLXF(0.5f, 0.5f);
    w = cpowf(z, p);
    printf("cpowf %a+%ai %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(p), cimagf(p), crealf(w), cimagf(w));
}

static void test_catan_branches(void)
{
    /* catand.c */
    double complex w;
    double complex z;
    z = CMPLX(0.0, 2.0);
    w = catan(z);
    printf("catan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(D_INF, 1.0);
    w = catan(z);
    printf("catan inf+%ai = %a+%ai\n", cimag(z), creal(w), cimag(w));
    z = CMPLX(D_NAN, 1.0);
    w = catan(z);
    printf("catan nan+%ai = %a+%ai\n", cimag(z), creal(w), cimag(w));
}

static void test_catanf_branches(void)
{
    /* catanf.c */
    float complex w;
    float complex z;
    z = CMPLXF(0.0f, 2.0f);
    w = catanf(z);
    printf("catanf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w));
    z = CMPLXF(F_INF, 1.0f);
    w = catanf(z);
    printf("catanf inf+%ai = %a+%ai\n", cimagf(z), crealf(w), cimagf(w));
    z = CMPLXF(F_NAN, 1.0f);
    w = catanf(z);
    printf("catanf nan+%ai = %a+%ai\n", cimagf(z), crealf(w), cimagf(w));
}

/* ------------------------------------------------------------------ */
/* Branch coverage — round 3 additions                                 */
/* ------------------------------------------------------------------ */

/* acos/asin: polynomial range (2^-57 <= |x| <= 0.5) */
static void test_acos_extra(void)
{
    /* Branch (106:13): False — |x| in [2^-57, 0.5] */
    printf("acos %a = %a\n", 0.3, acos(0.3));
    printf("acos %a = %a\n", 0.1, acos(0.1));
    printf("acos %a = %a\n", -0.3, acos(-0.3));
    printf("acos %a = %a\n", -0.1, acos(-0.1));
    printf("acos %a = %a\n", 0x1p-56, acos(0x1p-56));
}

static void test_acosf_extra(void)
{
    /* Branch (52:13): False */
    printf("acosf %a = %a\n", 0.3f, acosf(0.3f));
    printf("acosf %a = %a\n", 0.1f, acosf(0.1f));
    printf("acosf %a = %a\n", -0.3f, acosf(-0.3f));
    printf("acosf %a = %a\n", 0x1p-26f, acosf(0x1p-26f));
}

static void test_asin_extra(void)
{
    /* Branch (104:13): False — |x| >= 2^-26 in polynomial range */
    printf("asin %a = %a\n", 0.3, asin(0.3));
    printf("asin %a = %a\n", 0.1, asin(0.1));
    printf("asin %a = %a\n", -0.3, asin(-0.3));
    printf("asin %a = %a\n", -0.1, asin(-0.1));
}

static void test_asinf_extra(void)
{
    /* Branch (45:13): False */
    printf("asinf %a = %a\n", 0.3f, asinf(0.3f));
    printf("asinf %a = %a\n", 0.1f, asinf(0.1f));
    printf("asinf %a = %a\n", -0.3f, asinf(-0.3f));
}

/* atan2: extra edge cases */
static void test_atan2_extra(void)
{
    /* Branch (107:29): False — x near 1 but lx != 0 */
    printf("atan2 %a %a = %a\n", 1.0, 1.0 + 0x1p-52, atan2(1.0, 1.0 + 0x1p-52));
    printf("atan2 %a %a = %a\n", -1.0, 1.0 + 0x1p-52, atan2(-1.0, 1.0 + 0x1p-52));
    /* Branch (116): y=0 with x=+-0 cases */
    printf("atan2 %a %a = %a\n", 0.0, -0.0, atan2(0.0, -0.0));
    printf("atan2 %a %a = %a\n", -0.0, -0.0, atan2(-0.0, -0.0));
    /* Branch (138): x=inf, y=inf all quadrants */
    printf("atan2 %a %a = %a\n", D_INF, D_INF, atan2(D_INF, D_INF));
    printf("atan2 %a %a = %a\n", D_NINF, D_INF, atan2(D_NINF, D_INF));
    printf("atan2 %a %a = %a\n", D_INF, D_NINF, atan2(D_INF, D_NINF));
    printf("atan2 %a %a = %a\n", D_NINF, D_NINF, atan2(D_NINF, D_NINF));
    /* Branch (153): x=inf, y finite */
    printf("atan2 %a %a = %a\n", 2.0, D_INF, atan2(2.0, D_INF));
    printf("atan2 %a %a = %a\n", -2.0, D_INF, atan2(-2.0, D_INF));
    printf("atan2 %a %a = %a\n", 2.0, D_NINF, atan2(2.0, D_NINF));
    printf("atan2 %a %a = %a\n", -2.0, D_NINF, atan2(-2.0, D_NINF));
    /* Branch (170)/(171): y=inf */
    printf("atan2 %a %a = %a\n", D_INF, 3.0, atan2(D_INF, 3.0));
    printf("atan2 %a %a = %a\n", D_NINF, 3.0, atan2(D_NINF, 3.0));
    printf("atan2 %a %a = %a\n", D_INF, -3.0, atan2(D_INF, -3.0));
    printf("atan2 %a %a = %a\n", D_NINF, -3.0, atan2(D_NINF, -3.0));
    /* Branch (177): |y/x| > 2^60 with negative x */
    printf("atan2 %a %a = %a\n", 0x1p70, -1.0, atan2(0x1p70, -1.0));
    printf("atan2 %a %a = %a\n", -0x1p70, -1.0, atan2(-0x1p70, -1.0));
    /* Branch (190): m=1 case: y<0, x>0 */
    printf("atan2 %a %a = %a\n", -3.0, 4.0, atan2(-3.0, 4.0));
    printf("atan2 %a %a = %a\n", -0.5, 1.0, atan2(-0.5, 1.0));
}

static void test_atan2f_extra(void)
{
    printf("atan2f %a %a = %a\n", 1.0f, 1.0f + 0x1p-23f, (double)atan2f(1.0f, 1.0f + 0x1p-23f));
    printf("atan2f %a %a = %a\n", 0.0f, -0.0f, (double)atan2f(0.0f, -0.0f));
    printf("atan2f %a %a = %a\n", -0.0f, -0.0f, (double)atan2f(-0.0f, -0.0f));
    printf("atan2f %a %a = %a\n", F_INF, F_INF, (double)atan2f(F_INF, F_INF));
    printf("atan2f %a %a = %a\n", F_NINF, F_INF, (double)atan2f(F_NINF, F_INF));
    printf("atan2f %a %a = %a\n", F_INF, F_NINF, (double)atan2f(F_INF, F_NINF));
    printf("atan2f %a %a = %a\n", F_NINF, F_NINF, (double)atan2f(F_NINF, F_NINF));
    printf("atan2f %a %a = %a\n", 2.0f, F_INF, (double)atan2f(2.0f, F_INF));
    printf("atan2f %a %a = %a\n", -2.0f, F_INF, (double)atan2f(-2.0f, F_INF));
    printf("atan2f %a %a = %a\n", 2.0f, F_NINF, (double)atan2f(2.0f, F_NINF));
    printf("atan2f %a %a = %a\n", -2.0f, F_NINF, (double)atan2f(-2.0f, F_NINF));
    printf("atan2f %a %a = %a\n", F_INF, 3.0f, (double)atan2f(F_INF, 3.0f));
    printf("atan2f %a %a = %a\n", F_NINF, 3.0f, (double)atan2f(F_NINF, 3.0f));
    printf("atan2f %a %a = %a\n", F_INF, -3.0f, (double)atan2f(F_INF, -3.0f));
    printf("atan2f %a %a = %a\n", F_NINF, -3.0f, (double)atan2f(F_NINF, -3.0f));
    printf("atan2f %a %a = %a\n", 0x1p30f, -1.0f, (double)atan2f(0x1p30f, -1.0f));
    printf("atan2f %a %a = %a\n", -0x1p30f, -1.0f, (double)atan2f(-0x1p30f, -1.0f));
    printf("atan2f %a %a = %a\n", -3.0f, 4.0f, (double)atan2f(-3.0f, 4.0f));
}

/* tan: inputs in range-reduction threshold */
static void test_tan_extra(void)
{
    /* Branch (98:9): True — |x| >= ~0.6744 in tan kernel */
    printf("tan %a = %a\n", 0.7, tan(0.7));
    printf("tan %a = %a\n", 0.8, tan(0.8));
    printf("tan %a = %a\n", 0.9, tan(0.9));
    /* Branch (99:13): hx < 0 (negative x) */
    printf("tan %a = %a\n", -0.7, tan(-0.7));
    printf("tan %a = %a\n", -0.8, tan(-0.8));
    printf("tan %a = %a\n", -0.9, tan(-0.9));
    printf("tan %a = %a\n", -1.0, tan(-1.0));
    printf("tan %a = %a\n", -1.2, tan(-1.2));
}

static void test_tanf_extra(void)
{
    /* Branch (36:9): True — |x| >= ~0.6744 */
    printf("tanf %a = %a\n", 0.7f, tanf(0.7f));
    printf("tanf %a = %a\n", 0.8f, tanf(0.8f));
    printf("tanf %a = %a\n", -0.7f, tanf(-0.7f));
    printf("tanf %a = %a\n", -0.8f, tanf(-0.8f));
    printf("tanf %a = %a\n", -1.0f, tanf(-1.0f));
}

/* sin/cos/tan — large args to trigger trigd.c range-reduction branches */
static void test_sin_extra(void)
{
    printf("sin %a = %a\n", 1e6, sin(1e6));
    printf("sin %a = %a\n", 1e10, sin(1e10));
    printf("sin %a = %a\n", 1e15, sin(1e15));
    printf("sin %a = %a\n", 1e18, sin(1e18));
    printf("sin %a = %a\n", -1e15, sin(-1e15));
    printf("sin %a = %a\n", 0x1p20, sin(0x1p20));
    printf("sin %a = %a\n", 0x1p40, sin(0x1p40));
    printf("sin %a = %a\n", 0x1p60, sin(0x1p60));
    printf("sin %a = %a\n", 4.71238898038469, sin(4.71238898038469));
    printf("sin %a = %a\n", -4.71238898038469, sin(-4.71238898038469));
}

static void test_cos_extra(void)
{
    printf("cos %a = %a\n", 1e6, cos(1e6));
    printf("cos %a = %a\n", 1e10, cos(1e10));
    printf("cos %a = %a\n", 1e15, cos(1e15));
    printf("cos %a = %a\n", -1e15, cos(-1e15));
    printf("cos %a = %a\n", 0x1p20, cos(0x1p20));
    printf("cos %a = %a\n", 0x1p40, cos(0x1p40));
    printf("cos %a = %a\n", 0x1p60, cos(0x1p60));
}

static void test_tan_range_extra(void)
{
    printf("tan %a = %a\n", 1e6, tan(1e6));
    printf("tan %a = %a\n", 1e10, tan(1e10));
    printf("tan %a = %a\n", 1e15, tan(1e15));
    printf("tan %a = %a\n", -1e15, tan(-1e15));
    printf("tan %a = %a\n", 0x1p20, tan(0x1p20));
    printf("tan %a = %a\n", 0x1p40, tan(0x1p40));
}

/* sinf/cosf/tanf — large args for trigf.c branches */
static void test_sinf_extra(void)
{
    printf("sinf %a = %a\n", 1e4f, sinf(1e4f));
    printf("sinf %a = %a\n", 1e6f, sinf(1e6f));
    printf("sinf %a = %a\n", 1e7f, sinf(1e7f));
    printf("sinf %a = %a\n", 1e8f, sinf(1e8f));
    printf("sinf %a = %a\n", -1e7f, sinf(-1e7f));
    printf("sinf %a = %a\n", 0x1p15f, sinf(0x1p15f));
    printf("sinf %a = %a\n", 0x1p20f, sinf(0x1p20f));
    printf("sinf %a = %a\n", 1.5707963f, sinf(1.5707963f));
    printf("sinf %a = %a\n", -1.5707963f, sinf(-1.5707963f));
}

static void test_cosf_extra(void)
{
    printf("cosf %a = %a\n", 1e4f, cosf(1e4f));
    printf("cosf %a = %a\n", 1e6f, cosf(1e6f));
    printf("cosf %a = %a\n", 1e7f, cosf(1e7f));
    printf("cosf %a = %a\n", -1e7f, cosf(-1e7f));
    printf("cosf %a = %a\n", 0x1p15f, cosf(0x1p15f));
    printf("cosf %a = %a\n", 0x1p20f, cosf(0x1p20f));
}

static void test_tanf_range_extra(void)
{
    printf("tanf %a = %a\n", 1e4f, tanf(1e4f));
    printf("tanf %a = %a\n", 1e6f, tanf(1e6f));
    printf("tanf %a = %a\n", 1e7f, tanf(1e7f));
    printf("tanf %a = %a\n", -1e7f, tanf(-1e7f));
    printf("tanf %a = %a\n", 0x1p15f, tanf(0x1p15f));
}

/* sinh/cosh/tanh extra */
static void test_sinh_extra(void)
{
    /* Branch (113:29)/(113:49): within/above overflow threshold */
    printf("sinh %a = %a\n", 700.0, sinh(700.0));
    printf("sinh %a = %a\n", 709.0, sinh(709.0));
    printf("sinh %a = %a\n", -700.0, sinh(-700.0));
    printf("sinh %a = %a\n", 800.0, sinh(800.0));
    printf("sinh %a = %a\n", -800.0, sinh(-800.0));
}

static void test_sinhf_extra(void)
{
    /* Branch (58:9): within/above overflow threshold */
    printf("sinhf %a = %a\n", 88.0f, sinhf(88.0f));
    printf("sinhf %a = %a\n", 88.7f, sinhf(88.7f));
    printf("sinhf %a = %a\n", -88.0f, sinhf(-88.0f));
    printf("sinhf %a = %a\n", 100.0f, sinhf(100.0f));
    printf("sinhf %a = %a\n", -100.0f, sinhf(-100.0f));
}

static void test_cosh_extra(void)
{
    /* Branch (104:10)/(104:30): within/above overflow threshold */
    printf("cosh %a = %a\n", 700.0, cosh(700.0));
    printf("cosh %a = %a\n", 709.0, cosh(709.0));
    printf("cosh %a = %a\n", -700.0, cosh(-700.0));
    printf("cosh %a = %a\n", 800.0, cosh(800.0));
}

static void test_coshf_extra(void)
{
    /* Branch (51:9): within/above overflow threshold */
    printf("coshf %a = %a\n", 88.0f, coshf(88.0f));
    printf("coshf %a = %a\n", 89.0f, coshf(89.0f));
    printf("coshf %a = %a\n", -88.0f, coshf(-88.0f));
    printf("coshf %a = %a\n", 100.0f, coshf(100.0f));
}

static void test_tanh_extra(void)
{
    /* Branch (94:13): False — |x| < 1, use small-x formula */
    printf("tanh %a = %a\n", 0.3, tanh(0.3));
    printf("tanh %a = %a\n", 0.7, tanh(0.7));
    printf("tanh %a = %a\n", -0.3, tanh(-0.3));
    printf("tanh %a = %a\n", -0.7, tanh(-0.7));
}

static void test_tanhf_extra(void)
{
    /* Branch (34:9): False — |x| >= 22 */
    printf("tanhf %a = %a\n", 22.0f, tanhf(22.0f));
    printf("tanhf %a = %a\n", -22.0f, tanhf(-22.0f));
    printf("tanhf %a = %a\n", 100.0f, tanhf(100.0f));
    printf("tanhf %a = %a\n", -100.0f, tanhf(-100.0f));
    /* Small values */
    printf("tanhf %a = %a\n", 0.3f, tanhf(0.3f));
    printf("tanhf %a = %a\n", 0.7f, tanhf(0.7f));
    printf("tanhf %a = %a\n", -0.3f, tanhf(-0.3f));
}

/* ceil/floor/trunc: bit-manipulation ranges */
static void test_ceil_extra(void)
{
    /* (1, 2^20) range with fractional parts */
    printf("ceil %a = %a\n", 2.7, ceil(2.7));
    printf("ceil %a = %a\n", -2.7, ceil(-2.7));
    printf("ceil %a = %a\n", 100.3, ceil(100.3));
    printf("ceil %a = %a\n", -100.3, ceil(-100.3));
    printf("ceil %a = %a\n", 50000.7, ceil(50000.7));
    printf("ceil %a = %a\n", -50000.7, ceil(-50000.7));
    /* j0 = 20 exactly */
    printf("ceil %a = %a\n", 0x1p20 + 0.5, ceil(0x1p20 + 0.5));
    printf("ceil %a = %a\n", -(0x1p20 + 0.5), ceil(-(0x1p20 + 0.5)));
    /* j0 in (20, 51): fractional bits in low word */
    printf("ceil %a = %a\n", 0x1p21 + 0.5, ceil(0x1p21 + 0.5));
    printf("ceil %a = %a\n", -(0x1p21 + 0.5), ceil(-(0x1p21 + 0.5)));
    printf("ceil %a = %a\n", 0x1p30 + 0.5, ceil(0x1p30 + 0.5));
    printf("ceil %a = %a\n", 0x1p40 + 0.5, ceil(0x1p40 + 0.5));
    printf("ceil %a = %a\n", 0x1p50 + 0.5, ceil(0x1p50 + 0.5));
    printf("ceil %a = %a\n", -(0x1p50 + 0.5), ceil(-(0x1p50 + 0.5)));
}

static void test_floor_extra(void)
{
    printf("floor %a = %a\n", 2.7, floor(2.7));
    printf("floor %a = %a\n", -2.7, floor(-2.7));
    printf("floor %a = %a\n", 100.3, floor(100.3));
    printf("floor %a = %a\n", -100.3, floor(-100.3));
    printf("floor %a = %a\n", 0x1p20 + 0.5, floor(0x1p20 + 0.5));
    printf("floor %a = %a\n", -(0x1p20 + 0.5), floor(-(0x1p20 + 0.5)));
    printf("floor %a = %a\n", 0x1p21 + 0.5, floor(0x1p21 + 0.5));
    printf("floor %a = %a\n", -(0x1p21 + 0.5), floor(-(0x1p21 + 0.5)));
    printf("floor %a = %a\n", 0x1p30 + 0.5, floor(0x1p30 + 0.5));
    printf("floor %a = %a\n", 0x1p40 + 0.5, floor(0x1p40 + 0.5));
    printf("floor %a = %a\n", 0x1p50 + 0.5, floor(0x1p50 + 0.5));
    printf("floor %a = %a\n", -(0x1p50 + 0.5), floor(-(0x1p50 + 0.5)));
    printf("floor %a = %a\n", 50000.7, floor(50000.7));
    printf("floor %a = %a\n", -50000.7, floor(-50000.7));
}

static void test_ceilf_extra(void)
{
    printf("ceilf %a = %a\n", 2.7f, ceilf(2.7f));
    printf("ceilf %a = %a\n", -2.7f, ceilf(-2.7f));
    printf("ceilf %a = %a\n", 100.3f, ceilf(100.3f));
    printf("ceilf %a = %a\n", -100.3f, ceilf(-100.3f));
    printf("ceilf %a = %a\n", 0x1p10f + 0.5f, ceilf(0x1p10f + 0.5f));
    printf("ceilf %a = %a\n", -(0x1p10f + 0.5f), ceilf(-(0x1p10f + 0.5f)));
    printf("ceilf %a = %a\n", 0x1p15f + 0.5f, ceilf(0x1p15f + 0.5f));
    printf("ceilf %a = %a\n", -(0x1p15f + 0.5f), ceilf(-(0x1p15f + 0.5f)));
    printf("ceilf %a = %a\n", 0x1p22f + 0.5f, ceilf(0x1p22f + 0.5f));
}

static void test_floorf_extra(void)
{
    printf("floorf %a = %a\n", 2.7f, floorf(2.7f));
    printf("floorf %a = %a\n", -2.7f, floorf(-2.7f));
    printf("floorf %a = %a\n", 100.3f, floorf(100.3f));
    printf("floorf %a = %a\n", -100.3f, floorf(-100.3f));
    printf("floorf %a = %a\n", 0x1p10f + 0.5f, floorf(0x1p10f + 0.5f));
    printf("floorf %a = %a\n", -(0x1p10f + 0.5f), floorf(-(0x1p10f + 0.5f)));
    printf("floorf %a = %a\n", 0x1p15f + 0.5f, floorf(0x1p15f + 0.5f));
    printf("floorf %a = %a\n", -(0x1p15f + 0.5f), floorf(-(0x1p15f + 0.5f)));
}

static void test_trunc_extra(void)
{
    printf("trunc %a = %a\n", 2.7, trunc(2.7));
    printf("trunc %a = %a\n", -2.7, trunc(-2.7));
    printf("trunc %a = %a\n", 100.3, trunc(100.3));
    printf("trunc %a = %a\n", -100.3, trunc(-100.3));
    printf("trunc %a = %a\n", 0x1p20 + 0.5, trunc(0x1p20 + 0.5));
    printf("trunc %a = %a\n", -(0x1p20 + 0.5), trunc(-(0x1p20 + 0.5)));
    printf("trunc %a = %a\n", 0x1p30 + 0.5, trunc(0x1p30 + 0.5));
    printf("trunc %a = %a\n", -(0x1p30 + 0.5), trunc(-(0x1p30 + 0.5)));
    printf("trunc %a = %a\n", 0x1p53, trunc(0x1p53));
    printf("trunc %a = %a\n", D_INF, trunc(D_INF));
    printf("trunc %a = %a\n", D_NINF, trunc(D_NINF));
}

static void test_truncf_extra(void)
{
    printf("truncf %a = %a\n", 2.7f, truncf(2.7f));
    printf("truncf %a = %a\n", -2.7f, truncf(-2.7f));
    printf("truncf %a = %a\n", 100.3f, truncf(100.3f));
    printf("truncf %a = %a\n", -100.3f, truncf(-100.3f));
    printf("truncf %a = %a\n", 0x1p10f + 0.5f, truncf(0x1p10f + 0.5f));
    printf("truncf %a = %a\n", -(0x1p10f + 0.5f), truncf(-(0x1p10f + 0.5f)));
    printf("truncf %a = %a\n", 0x1p24f, truncf(0x1p24f));
    printf("truncf %a = %a\n", F_INF, truncf(F_INF));
}

/* rint/round extra */
static void test_rint_extra(void)
{
    printf("rint %a = %a\n", 2.5, rint(2.5));
    printf("rint %a = %a\n", 3.5, rint(3.5));
    printf("rint %a = %a\n", -3.5, rint(-3.5));
    printf("rint %a = %a\n", 0.3, rint(0.3));
    printf("rint %a = %a\n", -0.3, rint(-0.3));
    printf("rint %a = %a\n", 0x1p20 + 0.5, rint(0x1p20 + 0.5));
    printf("rint %a = %a\n", 0x1p50 + 0.5, rint(0x1p50 + 0.5));
}

static void test_rintf_extra(void)
{
    printf("rintf %a = %a\n", 2.5f, rintf(2.5f));
    printf("rintf %a = %a\n", 3.5f, rintf(3.5f));
    printf("rintf %a = %a\n", -3.5f, rintf(-3.5f));
    printf("rintf %a = %a\n", 0.3f, rintf(0.3f));
    printf("rintf %a = %a\n", -0.3f, rintf(-0.3f));
    printf("rintf %a = %a\n", 0x1p10f + 0.5f, rintf(0x1p10f + 0.5f));
}

static void test_round_extra(void)
{
    printf("round %a = %a\n", 2.5, round(2.5));
    printf("round %a = %a\n", -2.5, round(-2.5));
    printf("round %a = %a\n", 0.7, round(0.7));
    printf("round %a = %a\n", -0.7, round(-0.7));
    printf("round %a = %a\n", 0x1p20 + 0.5, round(0x1p20 + 0.5));
    printf("round %a = %a\n", -(0x1p20 + 0.5), round(-(0x1p20 + 0.5)));
}

static void test_roundf_extra(void)
{
    printf("roundf %a = %a\n", 2.5f, roundf(2.5f));
    printf("roundf %a = %a\n", -2.5f, roundf(-2.5f));
    printf("roundf %a = %a\n", 0.7f, roundf(0.7f));
    printf("roundf %a = %a\n", -0.7f, roundf(-0.7f));
    printf("roundf %a = %a\n", 0x1p10f + 0.5f, roundf(0x1p10f + 0.5f));
}

/* lrint/llrint/lround/llround extra */
static void test_lrint_extra(void)
{
    printf("lrint %a = %ld\n", -1.5, lrint(-1.5));
    printf("lrint %a = %ld\n", 2.5, lrint(2.5));
    printf("lrint %a = %ld\n", -2.5, lrint(-2.5));
}

static void test_lrintf_extra(void)
{
    printf("lrintf %a = %ld\n", -1.5f, lrintf(-1.5f));
    printf("lrintf %a = %ld\n", 2.5f, lrintf(2.5f));
    printf("lrintf %a = %ld\n", -2.5f, lrintf(-2.5f));
    printf("lrintf %a = %ld\n", 0x1p20f, lrintf(0x1p20f));
}

static void test_llrint_extra(void)
{
    printf("llrint %a = %lld\n", -1.5, llrint(-1.5));
    printf("llrint %a = %lld\n", 2.5, llrint(2.5));
    printf("llrint %a = %lld\n", -2.5, llrint(-2.5));
    printf("llrint %a = %lld\n", 0x1p52, llrint(0x1p52));
}

static void test_llrintf_extra(void)
{
    printf("llrintf %a = %lld\n", -1.5f, llrintf(-1.5f));
    printf("llrintf %a = %lld\n", 2.5f, llrintf(2.5f));
    printf("llrintf %a = %lld\n", -2.5f, llrintf(-2.5f));
    printf("llrintf %a = %lld\n", 0x1p20f, llrintf(0x1p20f));
}

static void test_lround_extra(void)
{
    printf("lround %a = %ld\n", -0.6, lround(-0.6));
    printf("lround %a = %ld\n", 0.6, lround(0.6));
    printf("lround %a = %ld\n", -1.5, lround(-1.5));
    printf("lround %a = %ld\n", 2.5, lround(2.5));
    printf("lround %a = %ld\n", -2.5, lround(-2.5));
}

static void test_lroundf_extra(void)
{
    printf("lroundf %a = %ld\n", -0.6f, lroundf(-0.6f));
    printf("lroundf %a = %ld\n", 0.6f, lroundf(0.6f));
    printf("lroundf %a = %ld\n", -1.5f, lroundf(-1.5f));
    printf("lroundf %a = %ld\n", 2.5f, lroundf(2.5f));
}

static void test_llround_extra(void)
{
    printf("llround %a = %lld\n", -0.6, llround(-0.6));
    printf("llround %a = %lld\n", 0.6, llround(0.6));
    printf("llround %a = %lld\n", -1.5, llround(-1.5));
    printf("llround %a = %lld\n", 2.5, llround(2.5));
    printf("llround %a = %lld\n", -2.5, llround(-2.5));
    printf("llround %a = %lld\n", 0x1p51, llround(0x1p51));
}

static void test_llroundf_extra(void)
{
    printf("llroundf %a = %lld\n", -0.6f, llroundf(-0.6f));
    printf("llroundf %a = %lld\n", 0.6f, llroundf(0.6f));
    printf("llroundf %a = %lld\n", -1.5f, llroundf(-1.5f));
    printf("llroundf %a = %lld\n", 2.5f, llroundf(2.5f));
}

/* lgamma: fine-grained ranges for gammad.c/gammaf.c branches */
static void test_lgamma_extra(void)
{
    /* x in [0,2) polynomial ranges */
    printf("lgamma %a = %a\n", 0.1, lgamma(0.1));
    printf("lgamma %a = %a\n", 0.2, lgamma(0.2));
    printf("lgamma %a = %a\n", 0.4, lgamma(0.4));
    printf("lgamma %a = %a\n", 0.7, lgamma(0.7));
    printf("lgamma %a = %a\n", 0.8, lgamma(0.8));
    printf("lgamma %a = %a\n", 0.9, lgamma(0.9));
    printf("lgamma %a = %a\n", 0.95, lgamma(0.95));
    printf("lgamma %a = %a\n", 1.1, lgamma(1.1));
    printf("lgamma %a = %a\n", 1.3, lgamma(1.3));
    printf("lgamma %a = %a\n", 1.5, lgamma(1.5));
    printf("lgamma %a = %a\n", 1.7, lgamma(1.7));
    printf("lgamma %a = %a\n", 1.9, lgamma(1.9));
    /* x in [2,8) */
    printf("lgamma %a = %a\n", 2.5, lgamma(2.5));
    printf("lgamma %a = %a\n", 3.5, lgamma(3.5));
    printf("lgamma %a = %a\n", 4.5, lgamma(4.5));
    printf("lgamma %a = %a\n", 5.5, lgamma(5.5));
    printf("lgamma %a = %a\n", 6.5, lgamma(6.5));
    printf("lgamma %a = %a\n", 7.5, lgamma(7.5));
    /* x >= 2^58: asymptotic */
    printf("lgamma %a = %a\n", 0x1p60, lgamma(0x1p60));
    printf("lgamma %a = %a\n", 1e20, lgamma(1e20));
    /* Negative non-integers */
    printf("lgamma %a = %a\n", -0.1, lgamma(-0.1));
    printf("lgamma %a = %a\n", -1.5, lgamma(-1.5));
    printf("lgamma %a = %a\n", -3.5, lgamma(-3.5));
    printf("lgamma %a = %a\n", -4.5, lgamma(-4.5));
    printf("lgamma %a = %a\n", -100.5, lgamma(-100.5));
    /* Very small |x| < 2^-70 */
    printf("lgamma %a = %a\n", 0x1p-80, lgamma(0x1p-80));
    printf("lgamma %a = %a\n", -0x1p-80, lgamma(-0x1p-80));
    /* Large negative (must be integer) */
    printf("lgamma %a = %a\n", -1e16, lgamma(-1e16));
}

static void test_lgammaf_extra(void)
{
    /* x in [0,2) polynomial ranges */
    printf("lgammaf %a = %a\n", 0.1f, lgammaf(0.1f));
    printf("lgammaf %a = %a\n", 0.2f, lgammaf(0.2f));
    printf("lgammaf %a = %a\n", 0.4f, lgammaf(0.4f));
    printf("lgammaf %a = %a\n", 0.7f, lgammaf(0.7f));
    printf("lgammaf %a = %a\n", 0.8f, lgammaf(0.8f));
    printf("lgammaf %a = %a\n", 0.9f, lgammaf(0.9f));
    printf("lgammaf %a = %a\n", 1.1f, lgammaf(1.1f));
    printf("lgammaf %a = %a\n", 1.3f, lgammaf(1.3f));
    printf("lgammaf %a = %a\n", 1.5f, lgammaf(1.5f));
    printf("lgammaf %a = %a\n", 1.7f, lgammaf(1.7f));
    printf("lgammaf %a = %a\n", 1.9f, lgammaf(1.9f));
    /* x in [2,8) */
    printf("lgammaf %a = %a\n", 2.5f, lgammaf(2.5f));
    printf("lgammaf %a = %a\n", 3.5f, lgammaf(3.5f));
    printf("lgammaf %a = %a\n", 4.5f, lgammaf(4.5f));
    printf("lgammaf %a = %a\n", 5.5f, lgammaf(5.5f));
    printf("lgammaf %a = %a\n", 6.5f, lgammaf(6.5f));
    printf("lgammaf %a = %a\n", 7.5f, lgammaf(7.5f));
    /* x >= 2^23: asymptotic */
    printf("lgammaf %a = %a\n", 1e8f, lgammaf(1e8f));
    printf("lgammaf %a = %a\n", 0x1p60f, lgammaf(0x1p60f));
    /* Negative non-integers */
    printf("lgammaf %a = %a\n", -0.1f, lgammaf(-0.1f));
    printf("lgammaf %a = %a\n", -1.5f, lgammaf(-1.5f));
    printf("lgammaf %a = %a\n", -2.5f, lgammaf(-2.5f));
    printf("lgammaf %a = %a\n", -3.5f, lgammaf(-3.5f));
    printf("lgammaf %a = %a\n", -4.5f, lgammaf(-4.5f));
    printf("lgammaf %a = %a\n", -5.5f, lgammaf(-5.5f));
    printf("lgammaf %a = %a\n", -6.5f, lgammaf(-6.5f));
    printf("lgammaf %a = %a\n", -100.5f, lgammaf(-100.5f));
    /* Very small |x| */
    printf("lgammaf %a = %a\n", 0x1p-40f, lgammaf(0x1p-40f));
    printf("lgammaf %a = %a\n", -0x1p-40f, lgammaf(-0x1p-40f));
    /* Large negative integer */
    printf("lgammaf %a = %a\n", -1e8f, lgammaf(-1e8f));
}

/* pow extra cases */
static void test_pow_extra(void)
{
    /* Near-unity x with large y (Branches 274-289) */
    printf("pow %a %a = %a\n", 1.0 + 0x1p-52, 1e15, pow(1.0 + 0x1p-52, 1e15));
    printf("pow %a %a = %a\n", 1.0 - 0x1p-53, 1e15, pow(1.0 - 0x1p-53, 1e15));
    printf("pow %a %a = %a\n", 1.0 + 0x1p-52, -1e15, pow(1.0 + 0x1p-52, -1e15));
    printf("pow %a %a = %a\n", 1.0 - 0x1p-53, -1e15, pow(1.0 - 0x1p-53, -1e15));
    /* Subnormal x (Branch 306) */
    printf("pow %a %a = %a\n", D_SUBNORM, 0.5, pow(D_SUBNORM, 0.5));
    printf("pow %a %a = %a\n", 0x1p-1022, 2.0, pow(0x1p-1022, 2.0));
    /* Negative x: even/odd/non-integer y */
    printf("pow %a %a = %a\n", -2.0, 4.0, pow(-2.0, 4.0));
    printf("pow %a %a = %a\n", -2.0, 5.0, pow(-2.0, 5.0));
    printf("pow %a %a = %a\n", -2.0, 1.5, pow(-2.0, 1.5));
    printf("pow %a %a = %a\n", -1.0, 1.0, pow(-1.0, 1.0));
    printf("pow %a %a = %a\n", -1.0, 2.0, pow(-1.0, 2.0));
    printf("pow %a %a = %a\n", -1.0, 0.5, pow(-1.0, 0.5));
    /* Huge y (Branch 274) */
    printf("pow %a %a = %a\n", 2.0, 0x1p52, pow(2.0, 0x1p52));
    printf("pow %a %a = %a\n", 0.5, 0x1p52, pow(0.5, 0x1p52));
    /* Result subnormal (Branch 426) */
    printf("pow %a %a = %a\n", 2.0, -1074.0, pow(2.0, -1074.0));
    /* Signaling NaN with y=0 (Branch 139) */
    {
        union { double d; uint64_t i; } u;
        u.i = 0x7FF0000000000001ULL;
        printf("pow snan 0 = %a\n", pow(u.d, 0.0));
    }
}

static void test_powf_extra(void)
{
    /* Near-unity x with large y */
    printf("powf %a %a = %a\n", 1.0f + 0x1p-23f, 1e6f, (double)powf(1.0f + 0x1p-23f, 1e6f));
    printf("powf %a %a = %a\n", 1.0f - 0x1p-24f, 1e6f, (double)powf(1.0f - 0x1p-24f, 1e6f));
    printf("powf %a %a = %a\n", 1.0f + 0x1p-23f, -1e6f, (double)powf(1.0f + 0x1p-23f, -1e6f));
    /* Subnormal x */
    printf("powf %a %a = %a\n", F_SUBNORM, 0.5f, (double)powf(F_SUBNORM, 0.5f));
    printf("powf %a %a = %a\n", 0x1p-126f, 2.0f, (double)powf(0x1p-126f, 2.0f));
    /* Negative x: even/odd/non-integer y */
    printf("powf %a %a = %a\n", -2.0f, 4.0f, (double)powf(-2.0f, 4.0f));
    printf("powf %a %a = %a\n", -2.0f, 5.0f, (double)powf(-2.0f, 5.0f));
    printf("powf %a %a = %a\n", -2.0f, 1.5f, (double)powf(-2.0f, 1.5f));
    printf("powf %a %a = %a\n", -1.0f, 1.0f, (double)powf(-1.0f, 1.0f));
    /* Huge y */
    printf("powf %a %a = %a\n", 2.0f, 0x1p23f, (double)powf(2.0f, 0x1p23f));
    /* Result subnormal */
    printf("powf %a %a = %a\n", 2.0f, -149.0f, (double)powf(2.0f, -149.0f));
    /* Signaling NaN with y=0 (Branch 53) */
    {
        union { float f; uint32_t i; } u;
        u.i = 0x7F800001U;
        printf("powf snan 0 = %a\n", (double)powf(u.f, 0.0f));
    }
    /* sqrt case */
    printf("powf %a %a = %a\n", -4.0f, 0.5f, (double)powf(-4.0f, 0.5f));
}

/* fmod extra */
static void test_fmod_extra(void)
{
    printf("fmod %a %a = %a\n", 3.0, 2.0, fmod(3.0, 2.0));
    printf("fmod %a %a = %a\n", 3.5, 1.5, fmod(3.5, 1.5));
    printf("fmod %a %a = %a\n", -3.5, 1.5, fmod(-3.5, 1.5));
    printf("fmod %a %a = %a\n", 1000.0, 3.0, fmod(1000.0, 3.0));
    printf("fmod %a %a = %a\n", 1e10, 3.0, fmod(1e10, 3.0));
    printf("fmod %a %a = %a\n", 1e15, 7.0, fmod(1e15, 7.0));
    printf("fmod %a %a = %a\n", 0x1p-1022, 0x1p-1074, fmod(0x1p-1022, 0x1p-1074));
    printf("fmod %a %a = %a\n", 7.0, 3.0, fmod(7.0, 3.0));
    printf("fmod %a %a = %a\n", -7.0, 3.0, fmod(-7.0, 3.0));
}

static void test_fmodf_extra(void)
{
    printf("fmodf %a %a = %a\n", 3.0f, 2.0f, fmodf(3.0f, 2.0f));
    printf("fmodf %a %a = %a\n", 3.5f, 1.5f, fmodf(3.5f, 1.5f));
    printf("fmodf %a %a = %a\n", -3.5f, 1.5f, fmodf(-3.5f, 1.5f));
    printf("fmodf %a %a = %a\n", 1000.0f, 3.0f, fmodf(1000.0f, 3.0f));
    printf("fmodf %a %a = %a\n", 1e7f, 3.0f, fmodf(1e7f, 3.0f));
    printf("fmodf %a %a = %a\n", 7.0f, 3.0f, fmodf(7.0f, 3.0f));
    printf("fmodf %a %a = %a\n", -7.0f, 3.0f, fmodf(-7.0f, 3.0f));
    printf("fmodf %a %a = %a\n", 0x1p-126f, 0x1p-149f, fmodf(0x1p-126f, 0x1p-149f));
}

/* remainder/remquo extra */
static void test_remainder_extra(void)
{
    printf("remainder %a %a = %a\n", 5.0, 2.0, remainder(5.0, 2.0));
    printf("remainder %a %a = %a\n", 5.5, 2.0, remainder(5.5, 2.0));
    printf("remainder %a %a = %a\n", 7.0, 3.0, remainder(7.0, 3.0));
    printf("remainder %a %a = %a\n", -7.0, 3.0, remainder(-7.0, 3.0));
    printf("remainder %a %a = %a\n", 1000.0, 7.0, remainder(1000.0, 7.0));
    printf("remainder %a %a = %a\n", 0x1p-1074, 0x1p-1022, remainder(0x1p-1074, 0x1p-1022));
}

static void test_remainderf_extra(void)
{
    printf("remainderf %a %a = %a\n", 5.0f, 2.0f, remainderf(5.0f, 2.0f));
    printf("remainderf %a %a = %a\n", 5.5f, 2.0f, remainderf(5.5f, 2.0f));
    printf("remainderf %a %a = %a\n", 7.0f, 3.0f, remainderf(7.0f, 3.0f));
    printf("remainderf %a %a = %a\n", -7.0f, 3.0f, remainderf(-7.0f, 3.0f));
    printf("remainderf %a %a = %a\n", 1000.0f, 7.0f, remainderf(1000.0f, 7.0f));
}

static void test_remquo_extra(void)
{
    int q;
    double r;
    r = remquo(5.0, 2.0, &q);
    printf("remquo %a %a = %a quo %d\n", 5.0, 2.0, r, q);
    r = remquo(5.5, 2.0, &q);
    printf("remquo %a %a = %a quo %d\n", 5.5, 2.0, r, q);
    r = remquo(100.0, 7.0, &q);
    printf("remquo %a %a = %a quo %d\n", 100.0, 7.0, r, q);
    r = remquo(-100.0, 7.0, &q);
    printf("remquo %a %a = %a quo %d\n", -100.0, 7.0, r, q);
    r = remquo(0x1p-1074, 0x1p-1022, &q);
    printf("remquo tiny = %a quo %d\n", r, q);
}

static void test_remquof_extra(void)
{
    int q;
    float r;
    r = remquof(5.0f, 2.0f, &q);
    printf("remquof %a %a = %a quo %d\n", 5.0f, 2.0f, r, q);
    r = remquof(100.0f, 7.0f, &q);
    printf("remquof %a %a = %a quo %d\n", 100.0f, 7.0f, r, q);
    r = remquof(-100.0f, 7.0f, &q);
    printf("remquof %a %a = %a quo %d\n", -100.0f, 7.0f, r, q);
    r = remquof(5.5f, 2.0f, &q);
    printf("remquof %a %a = %a quo %d\n", 5.5f, 2.0f, r, q);
}

/* sqrt extra */
static void test_sqrt_extra(void)
{
    printf("sqrt %a = %a\n", 2.0, sqrt(2.0));
    printf("sqrt %a = %a\n", 3.0, sqrt(3.0));
    printf("sqrt %a = %a\n", 5.0, sqrt(5.0));
    printf("sqrt %a = %a\n", 7.0, sqrt(7.0));
    printf("sqrt %a = %a\n", 0.1, sqrt(0.1));
    printf("sqrt %a = %a\n", 0.3, sqrt(0.3));
    printf("sqrt %a = %a\n", 1.5, sqrt(1.5));
    printf("sqrt %a = %a\n", 1e100, sqrt(1e100));
    printf("sqrt %a = %a\n", 1e-100, sqrt(1e-100));
}

static void test_sqrtf_extra(void)
{
    printf("sqrtf %a = %a\n", 2.0f, sqrtf(2.0f));
    printf("sqrtf %a = %a\n", 3.0f, sqrtf(3.0f));
    printf("sqrtf %a = %a\n", 0.1f, sqrtf(0.1f));
    printf("sqrtf %a = %a\n", 0.3f, sqrtf(0.3f));
    printf("sqrtf %a = %a\n", 1.5f, sqrtf(1.5f));
    printf("sqrtf %a = %a\n", 0x1p-126f, sqrtf(0x1p-126f));
}

/* log/log10/log2/logb/log1p extra */
static void test_log_extra(void)
{
    /* Subnormal input */
    printf("log %a = %a\n", D_SUBNORM, log(D_SUBNORM));
    printf("log %a = %a\n", 0x1p-1022, log(0x1p-1022));
    /* Range (0,1) */
    printf("log %a = %a\n", 0.5, log(0.5));
    printf("log %a = %a\n", 0.7, log(0.7));
    printf("log %a = %a\n", 0.9, log(0.9));
    /* Range (1, sqrt(2)) and (sqrt(2), 2) */
    printf("log %a = %a\n", 1.2, log(1.2));
    printf("log %a = %a\n", 1.41, log(1.41));
    printf("log %a = %a\n", 1.42, log(1.42));
    printf("log %a = %a\n", 1.8, log(1.8));
}

static void test_logf_extra(void)
{
    printf("logf %a = %a\n", F_SUBNORM, logf(F_SUBNORM));
    printf("logf %a = %a\n", 0x1p-126f, logf(0x1p-126f));
    printf("logf %a = %a\n", 0.5f, logf(0.5f));
    printf("logf %a = %a\n", 0.7f, logf(0.7f));
    printf("logf %a = %a\n", 1.2f, logf(1.2f));
    printf("logf %a = %a\n", 1.41f, logf(1.41f));
    printf("logf %a = %a\n", 1.42f, logf(1.42f));
    printf("logf %a = %a\n", 1.8f, logf(1.8f));
}

static void test_log10_extra(void)
{
    printf("log10 %a = %a\n", D_SUBNORM, log10(D_SUBNORM));
    printf("log10 %a = %a\n", 0.5, log10(0.5));
    printf("log10 %a = %a\n", 0x1p-1022, log10(0x1p-1022));
}

static void test_log10f_extra(void)
{
    printf("log10f %a = %a\n", F_SUBNORM, log10f(F_SUBNORM));
    printf("log10f %a = %a\n", 0.5f, log10f(0.5f));
    printf("log10f %a = %a\n", 0x1p-126f, log10f(0x1p-126f));
}

static void test_log2_extra(void)
{
    printf("log2 %a = %a\n", D_SUBNORM, log2(D_SUBNORM));
    printf("log2 %a = %a\n", 0.5, log2(0.5));
    printf("log2 %a = %a\n", 0x1p-1022, log2(0x1p-1022));
}

static void test_log2f_extra(void)
{
    printf("log2f %a = %a\n", F_SUBNORM, log2f(F_SUBNORM));
    printf("log2f %a = %a\n", 0.5f, log2f(0.5f));
    printf("log2f %a = %a\n", 0x1p-126f, log2f(0x1p-126f));
}

static void test_logb_extra(void)
{
    printf("logb %a = %a\n", -1.0, logb(-1.0));
    printf("logb %a = %a\n", D_NINF, logb(D_NINF));
    printf("logb %a = %a\n", -D_SUBNORM, logb(-D_SUBNORM));
}

static void test_log1p_extra(void)
{
    printf("log1p %a = %a\n", -0.9, log1p(-0.9));
    printf("log1p %a = %a\n", -0.5, log1p(-0.5));
    printf("log1p %a = %a\n", -0.3, log1p(-0.3));
    printf("log1p %a = %a\n", 0.1, log1p(0.1));
    printf("log1p %a = %a\n", 0.5, log1p(0.5));
    printf("log1p %a = %a\n", 2.0, log1p(2.0));
    printf("log1p %a = %a\n", 100.0, log1p(100.0));
}

static void test_log1pf_extra(void)
{
    printf("log1pf %a = %a\n", -0.9f, log1pf(-0.9f));
    printf("log1pf %a = %a\n", -0.5f, log1pf(-0.5f));
    printf("log1pf %a = %a\n", -0.3f, log1pf(-0.3f));
    printf("log1pf %a = %a\n", 0.1f, log1pf(0.1f));
    printf("log1pf %a = %a\n", 0.5f, log1pf(0.5f));
    printf("log1pf %a = %a\n", 2.0f, log1pf(2.0f));
    printf("log1pf %a = %a\n", 0x1p-26f, log1pf(0x1p-26f));
}

/* expm1 extra */
static void test_expm1_extra(void)
{
    printf("expm1 %a = %a\n", -0.5, expm1(-0.5));
    printf("expm1 %a = %a\n", -1.0, expm1(-1.0));
    printf("expm1 %a = %a\n", -2.0, expm1(-2.0));
    printf("expm1 %a = %a\n", 50.0, expm1(50.0));
    printf("expm1 %a = %a\n", 700.0, expm1(700.0));
}

static void test_expm1f_extra(void)
{
    printf("expm1f %a = %a\n", -0.5f, expm1f(-0.5f));
    printf("expm1f %a = %a\n", -1.0f, expm1f(-1.0f));
    printf("expm1f %a = %a\n", 50.0f, expm1f(50.0f));
    printf("expm1f %a = %a\n", 200.0f, expm1f(200.0f));
}

/* modf extra */
static void test_modf_extra(void)
{
    double ipart;
    double frac;
    frac = modf(3.7, &ipart);
    printf("modf %a = %a ipart %a\n", 3.7, frac, ipart);
    frac = modf(-3.7, &ipart);
    printf("modf %a = %a ipart %a\n", -3.7, frac, ipart);
    /* j0 > 51: large integral */
    frac = modf(0x1p52 + 0.5, &ipart);
    printf("modf %a = %a ipart %a\n", 0x1p52 + 0.5, frac, ipart);
    frac = modf(0x1p60, &ipart);
    printf("modf %a = %a ipart %a\n", 0x1p60, frac, ipart);
    /* j0 in (20,51): fraction in low word */
    frac = modf(0x1p21 + 0.5, &ipart);
    printf("modf %a = %a ipart %a\n", 0x1p21 + 0.5, frac, ipart);
    frac = modf(0x1p30 + 0.5, &ipart);
    printf("modf %a = %a ipart %a\n", 0x1p30 + 0.5, frac, ipart);
}

static void test_modff_extra(void)
{
    float ipartf;
    float fracf;
    fracf = modff(3.7f, &ipartf);
    printf("modff %a = %a ipart %a\n", 3.7f, fracf, ipartf);
    fracf = modff(-3.7f, &ipartf);
    printf("modff %a = %a ipart %a\n", -3.7f, fracf, ipartf);
    /* j0 > 23: already integral */
    fracf = modff(0x1p24f, &ipartf);
    printf("modff %a = %a ipart %a\n", 0x1p24f, fracf, ipartf);
    /* j0 in (0,22) range */
    fracf = modff(0x1p10f + 0.5f, &ipartf);
    printf("modff %a = %a ipart %a\n", 0x1p10f + 0.5f, fracf, ipartf);
}

/* nextafter extra */
static void test_nextafter_extra(void)
{
    printf("nextafter %a %a = %a\n", 1.0, 1.0, nextafter(1.0, 1.0));
    printf("nextafter %a %a = %a\n", D_NAN, 1.0, nextafter(D_NAN, 1.0));
    printf("nextafter %a %a = %a\n", 1.0, D_NAN, nextafter(1.0, D_NAN));
    printf("nextafter %a %a = %a\n", D_INF, 0.0, nextafter(D_INF, 0.0));
    printf("nextafter %a %a = %a\n", D_NINF, 0.0, nextafter(D_NINF, 0.0));
    printf("nextafter %a %a = %a\n", 0.0, 1.0, nextafter(0.0, 1.0));
    printf("nextafter %a %a = %a\n", 0.0, -1.0, nextafter(0.0, -1.0));
    printf("nextafter %a %a = %a\n", -0.0, 1.0, nextafter(-0.0, 1.0));
    printf("nextafter %a %a = %a\n", D_SUBNORM, 0.0, nextafter(D_SUBNORM, 0.0));
    printf("nextafter %a %a = %a\n", -D_SUBNORM, 0.0, nextafter(-D_SUBNORM, 0.0));
}

static void test_nextafterf_extra(void)
{
    printf("nextafterf %a %a = %a\n", 1.0f, 1.0f, nextafterf(1.0f, 1.0f));
    printf("nextafterf %a %a = %a\n", F_NAN, 1.0f, nextafterf(F_NAN, 1.0f));
    printf("nextafterf %a %a = %a\n", F_INF, 0.0f, nextafterf(F_INF, 0.0f));
    printf("nextafterf %a %a = %a\n", 0.0f, 1.0f, nextafterf(0.0f, 1.0f));
    printf("nextafterf %a %a = %a\n", 0.0f, -1.0f, nextafterf(0.0f, -1.0f));
    printf("nextafterf %a %a = %a\n", F_SUBNORM, 0.0f, nextafterf(F_SUBNORM, 0.0f));
}

/* ilogb extra */
static void test_ilogb_extra(void)
{
    /* hx==0 subnormal: min subnormal has high word 0, low word 1 */
    printf("ilogb %a = %d\n", 0x1p-1074, ilogb(0x1p-1074));
    printf("ilogb %a = %d\n", -0x1p-1074, ilogb(-0x1p-1074));
    printf("ilogb %a = %d\n", 1.5, ilogb(1.5));
    printf("ilogb %a = %d\n", 0.5, ilogb(0.5));
    printf("ilogb %a = %d\n", 1024.0, ilogb(1024.0));
    printf("ilogb %a = %d\n", -1.0, ilogb(-1.0));
}

/* hypot extra */
static void test_hypot_extra(void)
{
    printf("hypot %a %a = %a\n", 3.0, 4.0, hypot(3.0, 4.0));
    printf("hypot %a %a = %a\n", 0.3, 0.4, hypot(0.3, 0.4));
    printf("hypot %a %a = %a\n", D_SUBNORM, D_SUBNORM, hypot(D_SUBNORM, D_SUBNORM));
    printf("hypot %a %a = %a\n", 1.0, 0x1p600, hypot(1.0, 0x1p600));
    printf("hypot %a %a = %a\n", 0x1p500, 0x1p500, hypot(0x1p500, 0x1p500));
}

static void test_hypotf_extra(void)
{
    printf("hypotf %a %a = %a\n", 3.0f, 4.0f, hypotf(3.0f, 4.0f));
    printf("hypotf %a %a = %a\n", F_SUBNORM, F_SUBNORM, hypotf(F_SUBNORM, F_SUBNORM));
    printf("hypotf %a %a = %a\n", 0x1p60f, 0x1p60f, hypotf(0x1p60f, 0x1p60f));
    printf("hypotf %a %a = %a\n", 0x1p-60f, 0x1p-60f, hypotf(0x1p-60f, 0x1p-60f));
}

/* erfc extra */
static void test_erfc_extra(void)
{
    printf("erfc %a = %a\n", -1.0, erfc(-1.0));
    printf("erfc %a = %a\n", -2.0, erfc(-2.0));
    printf("erfc %a = %a\n", -5.0, erfc(-5.0));
    printf("erfc %a = %a\n", -20.0, erfc(-20.0));
    printf("erfc %a = %a\n", 3.0, erfc(3.0));
    printf("erfc %a = %a\n", 10.0, erfc(10.0));
    printf("erfc %a = %a\n", 30.0, erfc(30.0));
    printf("erfc %a = %a\n", 0.7, erfc(0.7));
}

static void test_erfcf_extra(void)
{
    printf("erfcf %a = %a\n", -1.0f, erfcf(-1.0f));
    printf("erfcf %a = %a\n", -2.0f, erfcf(-2.0f));
    printf("erfcf %a = %a\n", -5.0f, erfcf(-5.0f));
    printf("erfcf %a = %a\n", 3.0f, erfcf(3.0f));
    printf("erfcf %a = %a\n", 0.7f, erfcf(0.7f));
    printf("erfcf %a = %a\n", 1.0f, erfcf(1.0f));
    printf("erfcf %a = %a\n", 2.0f, erfcf(2.0f));
}

/* Bessel extra */
static void test_j0_extra(void)
{
    printf("j0 %a = %a\n", -3.0, j0(-3.0));
    printf("j0 %a = %a\n", 5.0, j0(5.0));
    printf("j0 %a = %a\n", 200.0, j0(200.0));
    printf("j0 %a = %a\n", 0x1p-100, j0(0x1p-100));
    printf("j0 %a = %a\n", -8.0, j0(-8.0));
}

static void test_j1_extra(void)
{
    printf("j1 %a = %a\n", -3.0, j1(-3.0));
    printf("j1 %a = %a\n", 5.0, j1(5.0));
    printf("j1 %a = %a\n", 200.0, j1(200.0));
    printf("j1 %a = %a\n", 0x1p-100, j1(0x1p-100));
}

static void test_jn_extra(void)
{
    printf("jn %d %a = %a\n", 1, 0.0, jn(1, 0.0));
    printf("jn %d %a = %a\n", 2, 0.0, jn(2, 0.0));
    printf("jn %d %a = %a\n", 1, 0x1p-30, jn(1, 0x1p-30));
    printf("jn %d %a = %a\n", 3, 0x1p-30, jn(3, 0x1p-30));
    printf("jn %d %a = %a\n", 5, 2.0, jn(5, 2.0));
    printf("jn %d %a = %a\n", 10, 3.0, jn(10, 3.0));
    printf("jn %d %a = %a\n", 50, 1.0, jn(50, 1.0));
    printf("jn %d %a = %a\n", 3, 0.5, jn(3, 0.5));
    printf("jn %d %a = %a\n", 2, 5.0, jn(2, 5.0));
    printf("jn %d %a = %a\n", 100, 1.0, jn(100, 1.0));
    printf("jn %d %a = %a\n", 2, 1000.0, jn(2, 1000.0));
    printf("jn %d %a = %a\n", 5, 0.001, jn(5, 0.001));
}

static void test_yn_extra(void)
{
    printf("yn %d %a = %a\n", 2, 1.0, yn(2, 1.0));
    printf("yn %d %a = %a\n", 3, 1.0, yn(3, 1.0));
    printf("yn %d %a = %a\n", 5, 0.5, yn(5, 0.5));
    printf("yn %d %a = %a\n", -2, 1.0, yn(-2, 1.0));
    printf("yn %d %a = %a\n", -3, 1.0, yn(-3, 1.0));
    printf("yn %d %a = %a\n", 10, 1.0, yn(10, 1.0));
    printf("yn %d %a = %a\n", 2, 1e5, yn(2, 1e5));
    printf("yn %d %a = %a\n", 0, 1.0, yn(0, 1.0));
    printf("yn %d %a = %a\n", 1, 1.0, yn(1, 1.0));
    printf("yn %d %a = %a\n", 2, 0x1p302, yn(2, 0x1p302));
}

static void test_y0_extra(void)
{
    printf("y0 %a = %a\n", 5.0, y0(5.0));
    printf("y0 %a = %a\n", 100.0, y0(100.0));
    printf("y0 %a = %a\n", 0x1p302, y0(0x1p302));
    printf("y0 %a = %a\n", 0.1, y0(0.1));
    printf("y0 %a = %a\n", -0.5, y0(-0.5));
}

static void test_y1_extra(void)
{
    printf("y1 %a = %a\n", 5.0, y1(5.0));
    printf("y1 %a = %a\n", 100.0, y1(100.0));
    printf("y1 %a = %a\n", 0x1p302, y1(0x1p302));
    printf("y1 %a = %a\n", 0.1, y1(0.1));
}

/* csqrt extra */
static void test_csqrt_extra(void)
{
    double complex z, w;
    z = CMPLX(4.0, 0x1p-1074);
    w = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(-4.0, 100.0);
    w = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(0x1p500, 0x1p500);
    w = csqrt(z);
    printf("csqrt large = %a+%ai\n", creal(w), cimag(w));
    z = CMPLX(0.0, 4.0);
    w = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(1e300, 1.0);
    w = csqrt(z);
    printf("csqrt large+1i = %a+%ai\n", creal(w), cimag(w));
}

static void test_csqrtf_extra(void)
{
    float complex z, w;
    z = CMPLXF(-4.0f, 100.0f);
    w = csqrtf(z);
    printf("csqrtf %a+%ai = %a+%ai\n", (double)crealf(z), (double)cimagf(z),
           (double)crealf(w), (double)cimagf(w));
    z = CMPLXF(0x1p60f, 0x1p60f);
    w = csqrtf(z);
    printf("csqrtf large = %a+%ai\n", (double)crealf(w), (double)cimagf(w));
    z = CMPLXF(0.0f, 4.0f);
    w = csqrtf(z);
    printf("csqrtf %a+%ai = %a+%ai\n", (double)crealf(z), (double)cimagf(z),
           (double)crealf(w), (double)cimagf(w));
}

/* ctan extra */
static void test_ctan_extra(void)
{
    double complex z, w;
    z = CMPLX(1.0, 100.0);
    w = ctan(z);
    printf("ctan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(1.0, -100.0);
    w = ctan(z);
    printf("ctan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(D_NAN, 1.0);
    w = ctan(z);
    printf("ctan nan+%ai = %a+%ai\n", cimag(z), creal(w), cimag(w));
    z = CMPLX(1.0, D_INF);
    w = ctan(z);
    printf("ctan %a+infi = %a+%ai\n", creal(z), creal(w), cimag(w));
    z = CMPLX(D_INF, 1.0);
    w = ctan(z);
    printf("ctan inf+%ai = %a+%ai\n", cimag(z), creal(w), cimag(w));
    z = CMPLX(0.0, 0.0);
    w = ctan(z);
    printf("ctan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
}

static void test_ctanf_extra(void)
{
    float complex z, w;
    z = CMPLXF(1.0f, 100.0f);
    w = ctanf(z);
    printf("ctanf %a+%ai = %a+%ai\n", (double)crealf(z), (double)cimagf(z),
           (double)crealf(w), (double)cimagf(w));
    z = CMPLXF(1.0f, -100.0f);
    w = ctanf(z);
    printf("ctanf %a+%ai = %a+%ai\n", (double)crealf(z), (double)cimagf(z),
           (double)crealf(w), (double)cimagf(w));
    z = CMPLXF(F_NAN, 1.0f);
    w = ctanf(z);
    printf("ctanf nan+%ai = %a+%ai\n", (double)cimagf(z), (double)crealf(w), (double)cimagf(w));
    z = CMPLXF(1.0f, F_INF);
    w = ctanf(z);
    printf("ctanf %a+infi = %a+%ai\n", (double)crealf(z), (double)crealf(w), (double)cimagf(w));
    z = CMPLXF(F_INF, 1.0f);
    w = ctanf(z);
    printf("ctanf inf+%ai = %a+%ai\n", (double)cimagf(z), (double)crealf(w), (double)cimagf(w));
}

/* Complex trig extra (ctrigd.c / ctrigf.c) */
static void test_ctrig_extra(void)
{
    double complex z, w;
    z = CMPLX(1.0, 100.0);
    w = csin(z);
    printf("csin %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    w = ccos(z);
    printf("ccos %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(1.0, -100.0);
    w = csin(z);
    printf("csin %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w));
    z = CMPLX(D_INF, 1.0);
    w = csin(z);
    printf("csin inf+%ai = %a+%ai\n", cimag(z), creal(w), cimag(w));
    z = CMPLX(1.0, D_INF);
    w = ccos(z);
    printf("ccos %a+infi = %a+%ai\n", creal(z), creal(w), cimag(w));
    z = CMPLX(1000.0, 1.0);
    w = csin(z);
    printf("csin large real = %a+%ai\n", creal(w), cimag(w));
}

static void test_ctrigf_extra(void)
{
    float complex z, w;
    z = CMPLXF(1.0f, 100.0f);
    w = csinf(z);
    printf("csinf %a+%ai = %a+%ai\n", (double)crealf(z), (double)cimagf(z),
           (double)crealf(w), (double)cimagf(w));
    w = ccosf(z);
    printf("ccosf %a+%ai = %a+%ai\n", (double)crealf(z), (double)cimagf(z),
           (double)crealf(w), (double)cimagf(w));
    z = CMPLXF(F_INF, 1.0f);
    w = csinf(z);
    printf("csinf inf+%ai = %a+%ai\n", (double)cimagf(z), (double)crealf(w), (double)cimagf(w));
    z = CMPLXF(1.0f, F_INF);
    w = ccosf(z);
    printf("ccosf %a+infi = %a+%ai\n", (double)crealf(z), (double)crealf(w), (double)cimagf(w));
}

/* fpclassify extra */
static void test_fpclassify_extra(void)
{
    /* SNaN: high exp bits set, mantissa nonzero only in low word */
    union { double d; uint64_t i; } u;
    u.i = 0x7FF0000000000001ULL;
    printf("__fpclassifyd snan = %d\n", __fpclassifyd(u.d));
    printf("__fpclassifyd inf = %d\n", __fpclassifyd(D_INF));
    printf("__fpclassifyd -inf = %d\n", __fpclassifyd(D_NINF));
    printf("__fpclassifyd -0 = %d\n", __fpclassifyd(-0.0));
}

/* atand extra: SNaN with ix=0x7ff00000 and low!=0 */
static void test_atand_extra(void)
{
    union { double d; uint64_t i; } u;
    u.i = 0x7FF0000000000001ULL;
    printf("atan snan = %a\n", atan(u.d));
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

    /* Branch-coverage: special values and edge cases */
    test_acos_branches();
    test_acosf_branches();
    test_acosh_branches();
    test_acoshf_branches();
    test_asin_branches();
    test_asinf_branches();
    test_asinh_branches();
    test_asinhf_branches();
    test_atan_branches();
    test_atanf_branches();
    test_atan2_branches();
    test_atan2f_branches();
    test_atanh_branches();
    test_atanhf_branches();
    test_cosh_branches();
    test_coshf_branches();
    test_sinh_branches();
    test_sinhf_branches();
    test_tanh_branches();
    test_tanhf_branches();
    test_exp_branches();
    test_expf_branches();
    test_expm1_branches();
    test_expm1f_branches();
    test_log_branches();
    test_logf_branches();
    test_log10_branches();
    test_log10f_branches();
    test_log2_branches();
    test_log2f_branches();
    test_log1p_branches();
    test_log1pf_branches();
    test_logb_branches();
    test_logbf_branches();
    test_cos_branches();
    test_cosf_branches();
    test_sin_branches();
    test_sinf_branches();
    test_tan_branches();
    test_tanf_branches();
    test_ceil_branches();
    test_ceilf_branches();
    test_floor_branches();
    test_floorf_branches();
    test_trunc_branches();
    test_truncf_branches();
    test_rint_branches();
    test_rintf_branches();
    test_round_branches();
    test_roundf_branches();
    test_lrint_branches();
    test_lrintf_branches();
    test_llrint_branches();
    test_llrintf_branches();
    test_lround_branches();
    test_lroundf_branches();
    test_llround_branches();
    test_llroundf_branches();
    test_fmax_branches();
    test_fmaxf_branches();
    test_fmin_branches();
    test_fminf_branches();
    test_fpclassify_branches();
    test_frexp_branches();
    test_frexpf_branches();
    test_modf_branches();
    test_modff_branches();
    test_nextafter_branches();
    test_nextafterf_branches();
    test_scalbn_branches();
    test_scalbnf_branches();
    test_scalbln_branches();
    test_scalblnf_branches();
    test_ldexp_branches();
    test_ldexpf_branches();
    test_ilogb_branches();
    test_ilogbf_branches();
    test_hypot_branches();
    test_hypotf_branches();
    test_cbrt_branches();
    test_cbrtf_branches();
    test_sqrt_branches();
    test_sqrtf_branches();
    test_pow_branches();
    test_powf_branches();
    test_fmod_branches();
    test_fmodf_branches();
    test_remainder_branches();
    test_remainderf_branches();
    test_remquo_branches();
    test_remquof_branches();
    test_erf_branches();
    test_erff_branches();
    test_erfc_branches();
    test_erfcf_branches();
    test_tgamma_branches();
    test_tgammaf_branches();
    test_lgamma_branches();
    test_lgammaf_branches();
    test_j0_branches();
    test_j1_branches();
    test_jn_branches();
    test_y0_branches();
    test_y1_branches();
    test_yn_branches();
    test_csqrt_branches();
    test_csqrtf_branches();
    test_ctan_branches();
    test_ctanf_branches();
    test_cpow_branches();
    test_cpowf_branches();
    test_catan_branches();
    test_catanf_branches();

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

    test_acos_extra();
    test_acosf_extra();
    test_asin_extra();
    test_asinf_extra();
    test_atan2_extra();
    test_atan2f_extra();
    test_tan_extra();
    test_tanf_extra();
    test_sin_extra();
    test_cos_extra();
    test_tan_range_extra();
    test_sinf_extra();
    test_cosf_extra();
    test_tanf_range_extra();
    test_sinh_extra();
    test_sinhf_extra();
    test_cosh_extra();
    test_coshf_extra();
    test_tanh_extra();
    test_tanhf_extra();
    test_ceil_extra();
    test_floor_extra();
    test_ceilf_extra();
    test_floorf_extra();
    test_trunc_extra();
    test_truncf_extra();
    test_rint_extra();
    test_rintf_extra();
    test_round_extra();
    test_roundf_extra();
    test_lrint_extra();
    test_lrintf_extra();
    test_llrint_extra();
    test_llrintf_extra();
    test_lround_extra();
    test_lroundf_extra();
    test_llround_extra();
    test_llroundf_extra();
    test_lgamma_extra();
    test_lgammaf_extra();
    test_pow_extra();
    test_powf_extra();
    test_fmod_extra();
    test_fmodf_extra();
    test_remainder_extra();
    test_remainderf_extra();
    test_remquo_extra();
    test_remquof_extra();
    test_sqrt_extra();
    test_sqrtf_extra();
    test_log_extra();
    test_logf_extra();
    test_log10_extra();
    test_log10f_extra();
    test_log2_extra();
    test_log2f_extra();
    test_logb_extra();
    test_log1p_extra();
    test_log1pf_extra();
    test_expm1_extra();
    test_expm1f_extra();
    test_modf_extra();
    test_modff_extra();
    test_nextafter_extra();
    test_nextafterf_extra();
    test_ilogb_extra();
    test_hypot_extra();
    test_hypotf_extra();
    test_erfc_extra();
    test_erfcf_extra();
    test_j0_extra();
    test_j1_extra();
    test_jn_extra();
    test_yn_extra();
    test_y0_extra();
    test_y1_extra();
    test_csqrt_extra();
    test_csqrtf_extra();
    test_ctan_extra();
    test_ctanf_extra();
    test_ctrig_extra();
    test_ctrigf_extra();
    test_fpclassify_extra();
    test_atand_extra();

    return 0;
}
