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
    printf("acos %a = %a\n", 0.5, acos(0.5)); /* S4 */
    printf("acos %a = %a\n", 0.0, acos(0.0)); /* S4 */
    printf("acos %a = %a\n", 1.0, acos(1.0)); /* S4 */
    printf("acos %a = %a\n", -1.0, acos(-1.0)); /* S4 */
}

static void test_asin(void)
{
    printf("asin %a = %a\n", 0.5, asin(0.5)); /* S4 */
    printf("asin %a = %a\n", 0.0, asin(0.0)); /* S4 */
    printf("asin %a = %a\n", 1.0, asin(1.0)); /* S4 */
    printf("asin %a = %a\n", -0.5, asin(-0.5)); /* S4 */
}

static void test_atan(void)
{
    printf("atan %a = %a\n", 1.0, atan(1.0)); /* S4 */
    printf("atan %a = %a\n", 0.0, atan(0.0)); /* S4 */
    printf("atan %a = %a\n", -1.0, atan(-1.0)); /* S4 */
}

static void test_atan2(void)
{
    printf("atan2 %a %a = %a\n", 1.0, 1.0, atan2(1.0, 1.0)); /* S4 */
    printf("atan2 %a %a = %a\n", 0.0, 1.0, atan2(0.0, 1.0)); /* S4 */
    printf("atan2 %a %a = %a\n", 1.0, 0.0, atan2(1.0, 0.0)); /* S4 */
    printf("atan2 %a %a = %a\n", -1.0, -1.0, atan2(-1.0, -1.0)); /* S4 */
}

static void test_cos(void)
{
    printf("cos %a = %a\n", 0.0, cos(0.0)); /* S4 */
    printf("cos %a = %a\n", 1.0, cos(1.0)); /* S4 */
    printf("cos %a = %a\n", 3.141592653589793, cos(3.141592653589793)); /* S4 */
}

static void test_sin(void)
{
    printf("sin %a = %a\n", 0.0, sin(0.0)); /* S4 */
    printf("sin %a = %a\n", 1.0, sin(1.0)); /* S4 */
    printf("sin %a = %a\n", 0.5, sin(0.5)); /* S4 */
}

static void test_tan(void)
{
    printf("tan %a = %a\n", 0.0, tan(0.0)); /* S4 */
    printf("tan %a = %a\n", 0.5, tan(0.5)); /* S4 */
    printf("tan %a = %a\n", 1.0, tan(1.0)); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Trigonometric functions — float                                     */
/* ------------------------------------------------------------------ */

static void test_acosf(void)
{
    printf("acosf %a = %a\n", 0.5f, acosf(0.5f)); /* S4 */
    printf("acosf %a = %a\n", 0.0f, acosf(0.0f)); /* S4 */
    printf("acosf %a = %a\n", 1.0f, acosf(1.0f)); /* S4 */
}

static void test_asinf(void)
{
    printf("asinf %a = %a\n", 0.5f, asinf(0.5f)); /* S4 */
    printf("asinf %a = %a\n", 0.0f, asinf(0.0f)); /* S4 */
    printf("asinf %a = %a\n", -0.5f, asinf(-0.5f)); /* S4 */
}

static void test_atanf(void)
{
    printf("atanf %a = %a\n", 1.0f, atanf(1.0f)); /* S4 */
    printf("atanf %a = %a\n", 0.0f, atanf(0.0f)); /* S4 */
}

static void test_atan2f(void)
{
    printf("atan2f %a %a = %a\n", 1.0f, 1.0f, atan2f(1.0f, 1.0f)); /* S4 */
    printf("atan2f %a %a = %a\n", 0.0f, 1.0f, atan2f(0.0f, 1.0f)); /* S4 */
}

static void test_cosf(void)
{
    printf("cosf %a = %a\n", 0.0f, cosf(0.0f)); /* S4 */
    printf("cosf %a = %a\n", 1.0f, cosf(1.0f)); /* S4 */
}

static void test_sinf(void)
{
    printf("sinf %a = %a\n", 0.0f, sinf(0.0f)); /* S4 */
    printf("sinf %a = %a\n", 1.0f, sinf(1.0f)); /* S4 */
}

static void test_tanf(void)
{
    printf("tanf %a = %a\n", 0.0f, tanf(0.0f)); /* S4 */
    printf("tanf %a = %a\n", 0.5f, tanf(0.5f)); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Hyperbolic functions — double                                       */
/* ------------------------------------------------------------------ */

static void test_acosh(void)
{
    printf("acosh %a = %a\n", 1.0, acosh(1.0)); /* S4 */
    printf("acosh %a = %a\n", 2.0, acosh(2.0)); /* S4 */
    printf("acosh %a = %a\n", 10.0, acosh(10.0)); /* S4 */
}

static void test_asinh(void)
{
    printf("asinh %a = %a\n", 0.0, asinh(0.0)); /* S4 */
    printf("asinh %a = %a\n", 1.0, asinh(1.0)); /* S4 */
    printf("asinh %a = %a\n", -1.0, asinh(-1.0)); /* S4 */
}

static void test_atanh(void)
{
    printf("atanh %a = %a\n", 0.0, atanh(0.0)); /* S4 */
    printf("atanh %a = %a\n", 0.5, atanh(0.5)); /* S4 */
    printf("atanh %a = %a\n", -0.5, atanh(-0.5)); /* S4 */
}

static void test_cosh(void)
{
    printf("cosh %a = %a\n", 0.0, cosh(0.0)); /* S4 */
    printf("cosh %a = %a\n", 1.0, cosh(1.0)); /* S4 */
    printf("cosh %a = %a\n", -1.0, cosh(-1.0)); /* S4 */
}

static void test_sinh(void)
{
    printf("sinh %a = %a\n", 0.0, sinh(0.0)); /* S4 */
    printf("sinh %a = %a\n", 1.0, sinh(1.0)); /* S4 */
    printf("sinh %a = %a\n", -1.0, sinh(-1.0)); /* S4 */
}

static void test_tanh(void)
{
    printf("tanh %a = %a\n", 0.0, tanh(0.0)); /* S4 */
    printf("tanh %a = %a\n", 1.0, tanh(1.0)); /* S4 */
    printf("tanh %a = %a\n", -1.0, tanh(-1.0)); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Hyperbolic functions — float                                        */
/* ------------------------------------------------------------------ */

static void test_acoshf(void)
{
    printf("acoshf %a = %a\n", 1.0f, acoshf(1.0f)); /* S4 */
    printf("acoshf %a = %a\n", 2.0f, acoshf(2.0f)); /* S4 */
}

static void test_asinhf(void)
{
    printf("asinhf %a = %a\n", 0.0f, asinhf(0.0f)); /* S4 */
    printf("asinhf %a = %a\n", 1.0f, asinhf(1.0f)); /* S4 */
}

static void test_atanhf(void)
{
    printf("atanhf %a = %a\n", 0.0f, atanhf(0.0f)); /* S4 */
    printf("atanhf %a = %a\n", 0.5f, atanhf(0.5f)); /* S4 */
}

static void test_coshf(void)
{
    printf("coshf %a = %a\n", 0.0f, coshf(0.0f)); /* S4 */
    printf("coshf %a = %a\n", 1.0f, coshf(1.0f)); /* S4 */
}

static void test_sinhf(void)
{
    printf("sinhf %a = %a\n", 0.0f, sinhf(0.0f)); /* S4 */
    printf("sinhf %a = %a\n", 1.0f, sinhf(1.0f)); /* S4 */
}

static void test_tanhf(void)
{
    printf("tanhf %a = %a\n", 0.0f, tanhf(0.0f)); /* S4 */
    printf("tanhf %a = %a\n", 1.0f, tanhf(1.0f)); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Exponential / logarithmic — double                                  */
/* ------------------------------------------------------------------ */

static void test_exp(void)
{
    printf("exp %a = %a\n", 0.0, exp(0.0)); /* S4 */
    printf("exp %a = %a\n", 1.0, exp(1.0)); /* S4 */
    printf("exp %a = %a\n", -1.0, exp(-1.0)); /* S4 */
}

static void test_exp2(void)
{
    printf("exp2 %a = %a\n", 0.0, exp2(0.0)); /* S4 */
    printf("exp2 %a = %a\n", 1.0, exp2(1.0)); /* S4 */
    printf("exp2 %a = %a\n", 10.0, exp2(10.0)); /* S4 */
}

static void test_expm1(void)
{
    printf("expm1 %a = %a\n", 0.0, expm1(0.0)); /* S4 */
    printf("expm1 %a = %a\n", 1.0, expm1(1.0)); /* S4 */
    printf("expm1 %a = %a\n", 1e-10, expm1(1e-10)); /* S4 */
}

static void test_frexp(void)
{
    int e;
    double m;
    m = frexp(1.0, &e);
    printf("frexp %a = %a exp %d\n", 1.0, m, e); /* S4 */
    m = frexp(4.0, &e);
    printf("frexp %a = %a exp %d\n", 4.0, m, e); /* S4 */
    m = frexp(0.0, &e);
    printf("frexp %a = %a exp %d\n", 0.0, m, e); /* S4 */
}

static void test_ilogb(void)
{
    printf("ilogb %a = %d\n", 1.0, ilogb(1.0)); /* S4 */
    printf("ilogb %a = %d\n", 2.0, ilogb(2.0)); /* S4 */
    printf("ilogb %a = %d\n", 0.5, ilogb(0.5)); /* S4 */
}

static void test_ldexp(void)
{
    printf("ldexp %a %d = %a\n", 1.0, 1, ldexp(1.0, 1)); /* S4 */
    printf("ldexp %a %d = %a\n", 1.0, 10, ldexp(1.0, 10)); /* S4 */
    printf("ldexp %a %d = %a\n", 1.5, -1, ldexp(1.5, -1)); /* S4 */
}

static void test_log(void)
{
    printf("log %a = %a\n", 1.0, log(1.0)); /* S4 */
    printf("log %a = %a\n", 2.718281828459045, log(2.718281828459045)); /* S4 */
    printf("log %a = %a\n", 10.0, log(10.0)); /* S4 */
}

static void test_log10(void)
{
    printf("log10 %a = %a\n", 1.0, log10(1.0)); /* S4 */
    printf("log10 %a = %a\n", 10.0, log10(10.0)); /* S4 */
    printf("log10 %a = %a\n", 100.0, log10(100.0)); /* S4 */
}

static void test_log1p(void)
{
    printf("log1p %a = %a\n", 0.0, log1p(0.0)); /* S4 */
    printf("log1p %a = %a\n", 1.0, log1p(1.0)); /* S4 */
    printf("log1p %a = %a\n", 1e-10, log1p(1e-10)); /* S4 */
}

static void test_log2(void)
{
    printf("log2 %a = %a\n", 1.0, log2(1.0)); /* S4 */
    printf("log2 %a = %a\n", 2.0, log2(2.0)); /* S4 */
    printf("log2 %a = %a\n", 8.0, log2(8.0)); /* S4 */
}

static void test_logb(void)
{
    printf("logb %a = %a\n", 1.0, logb(1.0)); /* S4 */
    printf("logb %a = %a\n", 2.0, logb(2.0)); /* S4 */
    printf("logb %a = %a\n", 0.5, logb(0.5)); /* S4 */
}

static void test_modf(void)
{
    double ipart;
    double f;
    f = modf(3.14, &ipart);
    printf("modf %a = %a ipart %a\n", 3.14, f, ipart); /* S4 */
    f = modf(-3.14, &ipart);
    printf("modf %a = %a ipart %a\n", -3.14, f, ipart); /* S4 */
    f = modf(2.0, &ipart);
    printf("modf %a = %a ipart %a\n", 2.0, f, ipart); /* S4 */
}

static void test_scalbn(void)
{
    printf("scalbn %a %d = %a\n", 1.0, 2, scalbn(1.0, 2)); /* S4 */
    printf("scalbn %a %d = %a\n", 1.5, -1, scalbn(1.5, -1)); /* S4 */
    printf("scalbn %a %d = %a\n", 1.0, 0, scalbn(1.0, 0)); /* S4 */
}

static void test_scalbln(void)
{
    printf("scalbln %a %ld = %a\n", 1.0, 2L, scalbln(1.0, 2L)); /* S4 */
    printf("scalbln %a %ld = %a\n", 1.5, -1L, scalbln(1.5, -1L)); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Exponential / logarithmic — float                                   */
/* ------------------------------------------------------------------ */

static void test_expf(void)
{
    printf("expf %a = %a\n", 0.0f, expf(0.0f)); /* S4 */
    printf("expf %a = %a\n", 1.0f, expf(1.0f)); /* S4 */
    printf("expf %a = %a\n", -1.0f, expf(-1.0f)); /* S4 */
}

static void test_exp2f(void)
{
    printf("exp2f %a = %a\n", 0.0f, exp2f(0.0f)); /* S4 */
    printf("exp2f %a = %a\n", 1.0f, exp2f(1.0f)); /* S4 */
    printf("exp2f %a = %a\n", 10.0f, exp2f(10.0f)); /* S4 */
}

static void test_expm1f(void)
{
    printf("expm1f %a = %a\n", 0.0f, expm1f(0.0f)); /* S4 */
    printf("expm1f %a = %a\n", 1.0f, expm1f(1.0f)); /* S4 */
}

static void test_frexpf(void)
{
    int e;
    float m;
    m = frexpf(1.0f, &e);
    printf("frexpf %a = %a exp %d\n", 1.0f, m, e); /* S4 */
    m = frexpf(4.0f, &e);
    printf("frexpf %a = %a exp %d\n", 4.0f, m, e); /* S4 */
}

static void test_ilogbf(void)
{
    printf("ilogbf %a = %d\n", 1.0f, ilogbf(1.0f)); /* S4 */
    printf("ilogbf %a = %d\n", 2.0f, ilogbf(2.0f)); /* S4 */
}

static void test_ldexpf(void)
{
    printf("ldexpf %a %d = %a\n", 1.0f, 1, ldexpf(1.0f, 1)); /* S4 */
    printf("ldexpf %a %d = %a\n", 1.5f, -1, ldexpf(1.5f, -1)); /* S4 */
}

static void test_logf(void)
{
    printf("logf %a = %a\n", 1.0f, logf(1.0f)); /* S4 */
    printf("logf %a = %a\n", 10.0f, logf(10.0f)); /* S4 */
}

static void test_log10f(void)
{
    printf("log10f %a = %a\n", 1.0f, log10f(1.0f)); /* S4 */
    printf("log10f %a = %a\n", 10.0f, log10f(10.0f)); /* S4 */
}

static void test_log1pf(void)
{
    printf("log1pf %a = %a\n", 0.0f, log1pf(0.0f)); /* S4 */
    printf("log1pf %a = %a\n", 1.0f, log1pf(1.0f)); /* S4 */
}

static void test_log2f(void)
{
    printf("log2f %a = %a\n", 1.0f, log2f(1.0f)); /* S4 */
    printf("log2f %a = %a\n", 2.0f, log2f(2.0f)); /* S4 */
    printf("log2f %a = %a\n", 8.0f, log2f(8.0f)); /* S4 */
}

static void test_logbf(void)
{
    printf("logbf %a = %a\n", 1.0f, logbf(1.0f)); /* S4 */
    printf("logbf %a = %a\n", 2.0f, logbf(2.0f)); /* S4 */
}

static void test_modff(void)
{
    float ipart;
    float f;
    f = modff(3.14f, &ipart);
    printf("modff %a = %a ipart %a\n", 3.14f, f, ipart); /* S4 */
    f = modff(-3.14f, &ipart);
    printf("modff %a = %a ipart %a\n", -3.14f, f, ipart); /* S4 */
}

static void test_scalbnf(void)
{
    printf("scalbnf %a %d = %a\n", 1.0f, 2, scalbnf(1.0f, 2)); /* S4 */
    printf("scalbnf %a %d = %a\n", 1.5f, -1, scalbnf(1.5f, -1)); /* S4 */
}

static void test_scalblnf(void)
{
    printf("scalblnf %a %ld = %a\n", 1.0f, 2L, scalblnf(1.0f, 2L)); /* S4 */
    printf("scalblnf %a %ld = %a\n", 1.5f, -1L, scalblnf(1.5f, -1L)); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Power and absolute-value — double                                   */
/* ------------------------------------------------------------------ */

static void test_cbrt(void)
{
    printf("cbrt %a = %a\n", 1.0, cbrt(1.0)); /* S4 */
    printf("cbrt %a = %a\n", 8.0, cbrt(8.0)); /* S4 */
    printf("cbrt %a = %a\n", -8.0, cbrt(-8.0)); /* S4 */
    printf("cbrt %a = %a\n", 27.0, cbrt(27.0)); /* S4 */
}

static void test_fabs(void)
{
    printf("fabs %a = %a\n", 1.0, fabs(1.0)); /* S4 */
    printf("fabs %a = %a\n", -1.0, fabs(-1.0)); /* S4 */
    printf("fabs %a = %a\n", 0.0, fabs(0.0)); /* S4 */
}

static void test_hypot(void)
{
    printf("hypot %a %a = %a\n", 3.0, 4.0, hypot(3.0, 4.0)); /* S4 */
    printf("hypot %a %a = %a\n", 1.0, 0.0, hypot(1.0, 0.0)); /* S4 */
    printf("hypot %a %a = %a\n", 0.0, 0.0, hypot(0.0, 0.0)); /* S4 */
}

static void test_pow(void)
{
    printf("pow %a %a = %a\n", 2.0, 10.0, pow(2.0, 10.0)); /* S4 */
    printf("pow %a %a = %a\n", 1.0, 0.0, pow(1.0, 0.0)); /* S4 */
    printf("pow %a %a = %a\n", 4.0, 0.5, pow(4.0, 0.5)); /* S4 */
}

static void test_sqrt(void)
{
    printf("sqrt %a = %a\n", 4.0, sqrt(4.0)); /* S4 */
    printf("sqrt %a = %a\n", 2.0, sqrt(2.0)); /* S4 */
    printf("sqrt %a = %a\n", 0.0, sqrt(0.0)); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Power and absolute-value — float                                    */
/* ------------------------------------------------------------------ */

static void test_cbrtf(void)
{
    printf("cbrtf %a = %a\n", 1.0f, cbrtf(1.0f)); /* S4 */
    printf("cbrtf %a = %a\n", 8.0f, cbrtf(8.0f)); /* S4 */
    printf("cbrtf %a = %a\n", -8.0f, cbrtf(-8.0f)); /* S4 */
}

static void test_fabsf(void)
{
    printf("fabsf %a = %a\n", 1.0f, fabsf(1.0f)); /* S4 */
    printf("fabsf %a = %a\n", -1.0f, fabsf(-1.0f)); /* S4 */
    printf("fabsf %a = %a\n", 0.0f, fabsf(0.0f)); /* S4 */
}

static void test_hypotf(void)
{
    printf("hypotf %a %a = %a\n", 3.0f, 4.0f, hypotf(3.0f, 4.0f)); /* S4 */
    printf("hypotf %a %a = %a\n", 1.0f, 0.0f, hypotf(1.0f, 0.0f)); /* S4 */
}

static void test_powf(void)
{
    printf("powf %a %a = %a\n", 2.0f, 10.0f, powf(2.0f, 10.0f)); /* S4 */
    printf("powf %a %a = %a\n", 4.0f, 0.5f, powf(4.0f, 0.5f)); /* S4 */
}

static void test_sqrtf(void)
{
    printf("sqrtf %a = %a\n", 4.0f, sqrtf(4.0f)); /* S4 */
    printf("sqrtf %a = %a\n", 2.0f, sqrtf(2.0f)); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Error and gamma — double                                            */
/* ------------------------------------------------------------------ */

static void test_erf(void)
{
    printf("erf %a = %a\n", 0.0, erf(0.0)); /* S4 */
    printf("erf %a = %a\n", 1.0, erf(1.0)); /* S4 */
    printf("erf %a = %a\n", -1.0, erf(-1.0)); /* S4 */
}

static void test_erfc(void)
{
    printf("erfc %a = %a\n", 0.0, erfc(0.0)); /* S4 */
    printf("erfc %a = %a\n", 1.0, erfc(1.0)); /* S4 */
    printf("erfc %a = %a\n", -1.0, erfc(-1.0)); /* S4 */
}

static void test_lgamma(void)
{
    printf("lgamma %a = %a\n", 1.0, lgamma(1.0)); /* S4 */
    printf("lgamma %a = %a\n", 2.0, lgamma(2.0)); /* S4 */
    printf("lgamma %a = %a\n", 0.5, lgamma(0.5)); /* S4 */
}

static void test_tgamma(void)
{
    printf("tgamma %a = %a\n", 1.0, tgamma(1.0)); /* S4 */
    printf("tgamma %a = %a\n", 2.0, tgamma(2.0)); /* S4 */
    printf("tgamma %a = %a\n", 0.5, tgamma(0.5)); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Error and gamma — float                                             */
/* ------------------------------------------------------------------ */

static void test_erff(void)
{
    printf("erff %a = %a\n", 0.0f, erff(0.0f)); /* S4 */
    printf("erff %a = %a\n", 1.0f, erff(1.0f)); /* S4 */
    printf("erff %a = %a\n", -1.0f, erff(-1.0f)); /* S4 */
}

static void test_erfcf(void)
{
    printf("erfcf %a = %a\n", 0.0f, erfcf(0.0f)); /* S4 */
    printf("erfcf %a = %a\n", 1.0f, erfcf(1.0f)); /* S4 */
}

static void test_lgammaf(void)
{
    printf("lgammaf %a = %a\n", 1.0f, lgammaf(1.0f)); /* S4 */
    printf("lgammaf %a = %a\n", 2.0f, lgammaf(2.0f)); /* S4 */
    printf("lgammaf %a = %a\n", 0.5f, lgammaf(0.5f)); /* S4 */
}

static void test_tgammaf(void)
{
    printf("tgammaf %a = %a\n", 1.0f, tgammaf(1.0f)); /* S4 */
    printf("tgammaf %a = %a\n", 2.0f, tgammaf(2.0f)); /* S4 */
    printf("tgammaf %a = %a\n", 0.5f, tgammaf(0.5f)); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Nearest integer — double                                            */
/* ------------------------------------------------------------------ */

static void test_ceil(void)
{
    printf("ceil %a = %a\n", 1.2, ceil(1.2)); /* S4 */
    printf("ceil %a = %a\n", -1.2, ceil(-1.2)); /* S4 */
    printf("ceil %a = %a\n", 2.0, ceil(2.0)); /* S4 */
}

static void test_floor(void)
{
    printf("floor %a = %a\n", 1.9, floor(1.9)); /* S4 */
    printf("floor %a = %a\n", -1.1, floor(-1.1)); /* S4 */
    printf("floor %a = %a\n", 2.0, floor(2.0)); /* S4 */
}

static void test_nearbyint(void)
{
    printf("nearbyint %a = %a\n", 1.5, nearbyint(1.5)); /* S4 */
    printf("nearbyint %a = %a\n", -1.5, nearbyint(-1.5)); /* S4 */
    printf("nearbyint %a = %a\n", 2.0, nearbyint(2.0)); /* S4 */
}

static void test_rint(void)
{
    printf("rint %a = %a\n", 1.5, rint(1.5)); /* S4 */
    printf("rint %a = %a\n", -1.5, rint(-1.5)); /* S4 */
    printf("rint %a = %a\n", 2.0, rint(2.0)); /* S4 */
}

static void test_lrint(void)
{
    printf("lrint %a = %ld\n", 1.5, lrint(1.5)); /* S4 */
    printf("lrint %a = %ld\n", -1.5, lrint(-1.5)); /* S4 */
    printf("lrint %a = %ld\n", 2.0, lrint(2.0)); /* S4 */
}

static void test_llrint(void)
{
    printf("llrint %a = %lld\n", 1.5, llrint(1.5)); /* S4 */
    printf("llrint %a = %lld\n", -1.5, llrint(-1.5)); /* S4 */
}

static void test_round(void)
{
    printf("round %a = %a\n", 1.5, round(1.5)); /* S4 */
    printf("round %a = %a\n", -1.5, round(-1.5)); /* S4 */
    printf("round %a = %a\n", 2.0, round(2.0)); /* S4 */
}

static void test_lround(void)
{
    printf("lround %a = %ld\n", 1.5, lround(1.5)); /* S4 */
    printf("lround %a = %ld\n", -1.5, lround(-1.5)); /* S4 */
}

static void test_llround(void)
{
    printf("llround %a = %lld\n", 1.5, llround(1.5)); /* S4 */
    printf("llround %a = %lld\n", -1.5, llround(-1.5)); /* S4 */
}

static void test_trunc(void)
{
    printf("trunc %a = %a\n", 1.9, trunc(1.9)); /* S4 */
    printf("trunc %a = %a\n", -1.9, trunc(-1.9)); /* S4 */
    printf("trunc %a = %a\n", 2.0, trunc(2.0)); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Nearest integer — float                                             */
/* ------------------------------------------------------------------ */

static void test_ceilf(void)
{
    printf("ceilf %a = %a\n", 1.2f, ceilf(1.2f)); /* S4 */
    printf("ceilf %a = %a\n", -1.2f, ceilf(-1.2f)); /* S4 */
}

static void test_floorf(void)
{
    printf("floorf %a = %a\n", 1.9f, floorf(1.9f)); /* S4 */
    printf("floorf %a = %a\n", -1.1f, floorf(-1.1f)); /* S4 */
}

static void test_nearbyintf(void)
{
    printf("nearbyintf %a = %a\n", 1.5f, nearbyintf(1.5f)); /* S4 */
    printf("nearbyintf %a = %a\n", -1.5f, nearbyintf(-1.5f)); /* S4 */
}

static void test_rintf(void)
{
    printf("rintf %a = %a\n", 1.5f, rintf(1.5f)); /* S4 */
    printf("rintf %a = %a\n", -1.5f, rintf(-1.5f)); /* S4 */
}

static void test_lrintf(void)
{
    printf("lrintf %a = %ld\n", 1.5f, lrintf(1.5f)); /* S4 */
    printf("lrintf %a = %ld\n", -1.5f, lrintf(-1.5f)); /* S4 */
}

static void test_llrintf(void)
{
    printf("llrintf %a = %lld\n", 1.5f, llrintf(1.5f)); /* S4 */
    printf("llrintf %a = %lld\n", -1.5f, llrintf(-1.5f)); /* S4 */
}

static void test_roundf(void)
{
    printf("roundf %a = %a\n", 1.5f, roundf(1.5f)); /* S4 */
    printf("roundf %a = %a\n", -1.5f, roundf(-1.5f)); /* S4 */
}

static void test_lroundf(void)
{
    printf("lroundf %a = %ld\n", 1.5f, lroundf(1.5f)); /* S4 */
    printf("lroundf %a = %ld\n", -1.5f, lroundf(-1.5f)); /* S4 */
}

static void test_llroundf(void)
{
    printf("llroundf %a = %lld\n", 1.5f, llroundf(1.5f)); /* S4 */
    printf("llroundf %a = %lld\n", -1.5f, llroundf(-1.5f)); /* S4 */
}

static void test_truncf(void)
{
    printf("truncf %a = %a\n", 1.9f, truncf(1.9f)); /* S4 */
    printf("truncf %a = %a\n", -1.9f, truncf(-1.9f)); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Remainder — double                                                  */
/* ------------------------------------------------------------------ */

static void test_fmod(void)
{
    printf("fmod %a %a = %a\n", 5.0, 3.0, fmod(5.0, 3.0)); /* S4 */
    printf("fmod %a %a = %a\n", -5.0, 3.0, fmod(-5.0, 3.0)); /* S4 */
    printf("fmod %a %a = %a\n", 1.0, 1.0, fmod(1.0, 1.0)); /* S4 */
}

static void test_remainder(void)
{
    printf("remainder %a %a = %a\n", 5.0, 3.0, remainder(5.0, 3.0)); /* S4 */
    printf("remainder %a %a = %a\n", -5.0, 3.0, remainder(-5.0, 3.0)); /* S4 */
}

static void test_remquo(void)
{
    int q;
    double r;
    r = remquo(5.0, 3.0, &q);
    printf("remquo %a %a = %a quo %d\n", 5.0, 3.0, r, q); /* S4 */
    r = remquo(-5.0, 3.0, &q);
    printf("remquo %a %a = %a quo %d\n", -5.0, 3.0, r, q); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Remainder — float                                                   */
/* ------------------------------------------------------------------ */

static void test_fmodf(void)
{
    printf("fmodf %a %a = %a\n", 5.0f, 3.0f, fmodf(5.0f, 3.0f)); /* S4 */
    printf("fmodf %a %a = %a\n", -5.0f, 3.0f, fmodf(-5.0f, 3.0f)); /* S4 */
}

static void test_remainderf(void)
{
    printf("remainderf %a %a = %a\n", 5.0f, 3.0f, remainderf(5.0f, 3.0f)); /* S4 */
    printf("remainderf %a %a = %a\n", -5.0f, 3.0f, remainderf(-5.0f, 3.0f)); /* S4 */
}

static void test_remquof(void)
{
    int q;
    float r;
    r = remquof(5.0f, 3.0f, &q);
    printf("remquof %a %a = %a quo %d\n", 5.0f, 3.0f, r, q); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Manipulation — double                                               */
/* ------------------------------------------------------------------ */

static void test_copysign(void)
{
    printf("copysign %a %a = %a\n", 1.0, -2.0, copysign(1.0, -2.0)); /* S4 */
    printf("copysign %a %a = %a\n", -1.0, 2.0, copysign(-1.0, 2.0)); /* S4 */
    printf("copysign %a %a = %a\n", 0.0, -1.0, copysign(0.0, -1.0)); /* S4 */
}

static void test_nan(void)
{
    double v = nan("");
    printf("nan isnan = %d\n", v != v ? 1 : 0); /* S4 */
}

static void test_nextafter(void)
{
    printf("nextafter %a %a = %a\n", 0.0, 1.0, nextafter(0.0, 1.0)); /* S4 */
    printf("nextafter %a %a = %a\n", 1.0, 0.0, nextafter(1.0, 0.0)); /* S4 */
    printf("nextafter %a %a = %a\n", 1.0, 1.0, nextafter(1.0, 1.0)); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Manipulation — float                                                */
/* ------------------------------------------------------------------ */

static void test_copysignf(void)
{
    printf("copysignf %a %a = %a\n", 1.0f, -2.0f, copysignf(1.0f, -2.0f)); /* S4 */
    printf("copysignf %a %a = %a\n", -1.0f, 2.0f, copysignf(-1.0f, 2.0f)); /* S4 */
}

static void test_nanf(void)
{
    float v = nanf("");
    printf("nanf isnan = %d\n", v != v ? 1 : 0); /* S4 */
}

static void test_nextafterf(void)
{
    printf("nextafterf %a %a = %a\n", 0.0f, 1.0f, nextafterf(0.0f, 1.0f)); /* S4 */
    printf("nextafterf %a %a = %a\n", 1.0f, 0.0f, nextafterf(1.0f, 0.0f)); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Max, min, positive difference — double                              */
/* ------------------------------------------------------------------ */

static void test_fdim(void)
{
    printf("fdim %a %a = %a\n", 3.0, 2.0, fdim(3.0, 2.0)); /* S4 */
    printf("fdim %a %a = %a\n", 2.0, 3.0, fdim(2.0, 3.0)); /* S4 */
}

static void test_fmax(void)
{
    printf("fmax %a %a = %a\n", 3.0, 2.0, fmax(3.0, 2.0)); /* S4 */
    printf("fmax %a %a = %a\n", -3.0, -2.0, fmax(-3.0, -2.0)); /* S4 */
}

static void test_fmin(void)
{
    printf("fmin %a %a = %a\n", 3.0, 2.0, fmin(3.0, 2.0)); /* S4 */
    printf("fmin %a %a = %a\n", -3.0, -2.0, fmin(-3.0, -2.0)); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Max, min, positive difference — float                               */
/* ------------------------------------------------------------------ */

static void test_fdimf(void)
{
    printf("fdimf %a %a = %a\n", 3.0f, 2.0f, fdimf(3.0f, 2.0f)); /* S4 */
    printf("fdimf %a %a = %a\n", 2.0f, 3.0f, fdimf(2.0f, 3.0f)); /* S4 */
}

static void test_fmaxf(void)
{
    printf("fmaxf %a %a = %a\n", 3.0f, 2.0f, fmaxf(3.0f, 2.0f)); /* S4 */
    printf("fmaxf %a %a = %a\n", -3.0f, -2.0f, fmaxf(-3.0f, -2.0f)); /* S4 */
}

static void test_fminf(void)
{
    printf("fminf %a %a = %a\n", 3.0f, 2.0f, fminf(3.0f, 2.0f)); /* S4 */
    printf("fminf %a %a = %a\n", -3.0f, -2.0f, fminf(-3.0f, -2.0f)); /* S4 */
}

/* ------------------------------------------------------------------ */
/* FMA — double and float                                              */
/* ------------------------------------------------------------------ */

static void test_fma(void)
{
    printf("fma %a %a %a = %a\n", 2.0, 3.0, 4.0, fma(2.0, 3.0, 4.0)); /* S4 */
    printf("fma %a %a %a = %a\n", 1.0, 1.0, 1.0, fma(1.0, 1.0, 1.0)); /* S4 */
    printf("fma %a %a %a = %a\n", -2.0, 3.0, 1.0, fma(-2.0, 3.0, 1.0)); /* S4 */
}

static void test_fmaf(void)
{
    printf("fmaf %a %a %a = %a\n", 2.0f, 3.0f, 4.0f, fmaf(2.0f, 3.0f, 4.0f)); /* S4 */
    printf("fmaf %a %a %a = %a\n", 1.0f, 1.0f, 1.0f, fmaf(1.0f, 1.0f, 1.0f)); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Bessel functions                                                    */
/* ------------------------------------------------------------------ */

static void test_j0(void)
{
    printf("j0 %a = %a\n", 0.0, j0(0.0)); /* S4 */
    printf("j0 %a = %a\n", 1.0, j0(1.0)); /* S4 */
    printf("j0 %a = %a\n", 2.0, j0(2.0)); /* S4 */
}

static void test_j1(void)
{
    printf("j1 %a = %a\n", 0.0, j1(0.0)); /* S4 */
    printf("j1 %a = %a\n", 1.0, j1(1.0)); /* S4 */
    printf("j1 %a = %a\n", 2.0, j1(2.0)); /* S4 */
}

static void test_jn(void)
{
    printf("jn %d %a = %a\n", 0, 1.0, jn(0, 1.0)); /* S4 */
    printf("jn %d %a = %a\n", 1, 1.0, jn(1, 1.0)); /* S4 */
    printf("jn %d %a = %a\n", 2, 1.0, jn(2, 1.0)); /* S4 */
}

static void test_y0(void)
{
    printf("y0 %a = %a\n", 1.0, y0(1.0)); /* S4 */
    printf("y0 %a = %a\n", 2.0, y0(2.0)); /* S4 */
}

static void test_y1(void)
{
    printf("y1 %a = %a\n", 1.0, y1(1.0)); /* S4 */
    printf("y1 %a = %a\n", 2.0, y1(2.0)); /* S4 */
}

static void test_yn(void)
{
    printf("yn %d %a = %a\n", 0, 1.0, yn(0, 1.0)); /* S4 */
    printf("yn %d %a = %a\n", 1, 1.0, yn(1, 1.0)); /* S4 */
    printf("yn %d %a = %a\n", 2, 1.0, yn(2, 1.0)); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Classification functions                                            */
/* ------------------------------------------------------------------ */

static void test_fpclassifyd(void)
{
    printf("__fpclassifyd %a = %d\n", 1.0, __fpclassifyd(1.0)); /* S4 */
    printf("__fpclassifyd %a = %d\n", 0.0, __fpclassifyd(0.0)); /* S4 */
    printf("__fpclassifyd inf = %d\n", __fpclassifyd(1.0 / 0.0)); /* S4 */
}

static void test_fpclassifyf(void)
{
    printf("__fpclassifyf %a = %d\n", 1.0f, __fpclassifyf(1.0f)); /* S4 */
    printf("__fpclassifyf %a = %d\n", 0.0f, __fpclassifyf(0.0f)); /* S4 */
    printf("__fpclassifyf inf = %d\n", __fpclassifyf(1.0f / 0.0f)); /* S4 */
}

static void test_signbitd(void)
{
    printf("__signbitd %a = %d\n", 1.0, __signbitd(1.0)); /* S4 */
    printf("__signbitd %a = %d\n", -1.0, __signbitd(-1.0)); /* S4 */
    printf("__signbitd %a = %d\n", 0.0, __signbitd(0.0)); /* S4 */
}

static void test_signbitf(void)
{
    printf("__signbitf %a = %d\n", 1.0f, __signbitf(1.0f)); /* S4 */
    printf("__signbitf %a = %d\n", -1.0f, __signbitf(-1.0f)); /* S4 */
    printf("__signbitf %a = %d\n", 0.0f, __signbitf(0.0f)); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Internal trig helpers — double                                      */
/* ------------------------------------------------------------------ */

static void test_cos_internal(void)
{
    printf("__cos %a %a = %a\n", 0.5, 0.0, __cos(0.5, 0.0)); /* S4 */
    printf("__cos %a %a = %a\n", 0.0, 0.0, __cos(0.0, 0.0)); /* S4 */
    printf("__cos %a %a = %a\n", 0.3, 0.0, __cos(0.3, 0.0)); /* S4 */
}

static void test_sin_internal(void)
{
    printf("__sin %a %a %d = %a\n", 0.5, 0.0, 0, __sin(0.5, 0.0, 0)); /* S4 */
    printf("__sin %a %a %d = %a\n", 0.0, 0.0, 0, __sin(0.0, 0.0, 0)); /* S4 */
    printf("__sin %a %a %d = %a\n", 0.3, 0.0, 1, __sin(0.3, 0.0, 1)); /* S4 */
}

static void test_rem_pio2(void)
{
    double y[2];
    int n;
    n = __rem_pio2(1.5, y);
    printf("__rem_pio2 %a = %d y0 %a y1 %a\n", 1.5, n, y[0], y[1]); /* S4 */
    n = __rem_pio2(4.0, y);
    printf("__rem_pio2 %a = %d y0 %a y1 %a\n", 4.0, n, y[0], y[1]); /* S4 */
    n = __rem_pio2(1000.0, y);
    printf("__rem_pio2 %a = %d y0 %a y1 %a\n", 1000.0, n, y[0], y[1]); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Internal trig helpers — float                                       */
/* ------------------------------------------------------------------ */

static void test_cosf_internal(void)
{
    printf("__cosf %a %a = %a\n", 0.5f, 0.0f, __cosf(0.5f, 0.0f)); /* S4 */
    printf("__cosf %a %a = %a\n", 0.0f, 0.0f, __cosf(0.0f, 0.0f)); /* S4 */
}

static void test_sinf_internal(void)
{
    printf("__sinf %a %a %d = %a\n", 0.5f, 0.0f, 0, __sinf(0.5f, 0.0f, 0)); /* S4 */
    printf("__sinf %a %a %d = %a\n", 0.0f, 0.0f, 0, __sinf(0.0f, 0.0f, 0)); /* S4 */
}

static void test_rem_pio2f(void)
{
    float y[2];
    int n;
    n = __rem_pio2f(1.5f, y);
    printf("__rem_pio2f %a = %d y0 %a y1 %a\n", 1.5f, n, y[0], y[1]); /* S4 */
    n = __rem_pio2f(4.0f, y);
    printf("__rem_pio2f %a = %d y0 %a y1 %a\n", 4.0f, n, y[0], y[1]); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Internal gamma helpers                                              */
/* ------------------------------------------------------------------ */

static void test_lgamma_internal(void)
{
    int signgam;
    double v;
    v = __lgamma(1.0, &signgam);
    printf("__lgamma %a = %a sign %d\n", 1.0, v, signgam); /* S4 */
    v = __lgamma(2.0, &signgam);
    printf("__lgamma %a = %a sign %d\n", 2.0, v, signgam); /* S4 */
    v = __lgamma(0.5, &signgam);
    printf("__lgamma %a = %a sign %d\n", 0.5, v, signgam); /* S4 */
}

static void test_lgammaf_internal(void)
{
    int signgam;
    float v;
    v = __lgammaf(1.0f, &signgam);
    printf("__lgammaf %a = %a sign %d\n", 1.0f, v, signgam); /* S4 */
    v = __lgammaf(2.0f, &signgam);
    printf("__lgammaf %a = %a sign %d\n", 2.0f, v, signgam); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Complex functions — double                                          */
/* ------------------------------------------------------------------ */

static void test_cabs(void)
{
    double complex z = CMPLX(3.0, 4.0);
    printf("cabs %a+%ai = %a\n", creal(z), cimag(z), cabs(z)); /* S4 */
    z = CMPLX(0.0, 0.0);
    printf("cabs %a+%ai = %a\n", creal(z), cimag(z), cabs(z)); /* S4 */
    z = CMPLX(1.0, 0.0);
    printf("cabs %a+%ai = %a\n", creal(z), cimag(z), cabs(z)); /* S4 */
}

static void test_cacos(void)
{
    double complex z = CMPLX(0.5, 0.0);
    double complex w = cacos(z);
    printf("cacos %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(0.0, 1.0);
    w = cacos(z);
    printf("cacos %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
}

static void test_cacosh(void)
{
    double complex z = CMPLX(1.0, 0.0);
    double complex w = cacosh(z);
    printf("cacosh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(2.0, 0.0);
    w = cacosh(z);
    printf("cacosh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
}

static void test_carg(void)
{
    double complex z = CMPLX(1.0, 0.0);
    printf("carg %a+%ai = %a\n", creal(z), cimag(z), carg(z)); /* S4 */
    z = CMPLX(0.0, 1.0);
    printf("carg %a+%ai = %a\n", creal(z), cimag(z), carg(z)); /* S4 */
    z = CMPLX(-1.0, 0.0);
    printf("carg %a+%ai = %a\n", creal(z), cimag(z), carg(z)); /* S4 */
}

static void test_casin(void)
{
    double complex z = CMPLX(0.5, 0.0);
    double complex w = casin(z);
    printf("casin %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(0.0, 1.0);
    w = casin(z);
    printf("casin %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
}

static void test_casinh(void)
{
    double complex z = CMPLX(1.0, 0.0);
    double complex w = casinh(z);
    printf("casinh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(0.0, 1.0);
    w = casinh(z);
    printf("casinh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
}

static void test_catan(void)
{
    double complex z = CMPLX(1.0, 0.0);
    double complex w = catan(z);
    printf("catan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(0.0, 0.5);
    w = catan(z);
    printf("catan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
}

static void test_catanh(void)
{
    double complex z = CMPLX(0.5, 0.0);
    double complex w = catanh(z);
    printf("catanh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(0.0, 1.0);
    w = catanh(z);
    printf("catanh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
}

static void test_ccos(void)
{
    double complex z = CMPLX(0.0, 0.0);
    double complex w = ccos(z);
    printf("ccos %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(1.0, 1.0);
    w = ccos(z);
    printf("ccos %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
}

static void test_ccosh(void)
{
    double complex z = CMPLX(0.0, 0.0);
    double complex w = ccosh(z);
    printf("ccosh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(1.0, 1.0);
    w = ccosh(z);
    printf("ccosh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
}

static void test_ccoshsinh(void)
{
    double c, s;
    __ccoshsinh(0.0, &c, &s);
    printf("__ccoshsinh %a c=%a s=%a\n", 0.0, c, s); /* S4 */
    __ccoshsinh(1.0, &c, &s);
    printf("__ccoshsinh %a c=%a s=%a\n", 1.0, c, s); /* S4 */
    __ccoshsinh(0.3, &c, &s);
    printf("__ccoshsinh %a c=%a s=%a\n", 0.3, c, s); /* S4 */
}

static void test_cexp(void)
{
    double complex z = CMPLX(0.0, 0.0);
    double complex w = cexp(z);
    printf("cexp %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(1.0, 0.0);
    w = cexp(z);
    printf("cexp %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(0.0, 1.0);
    w = cexp(z);
    printf("cexp %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
}

static void test_cimag(void)
{
    double complex z = CMPLX(3.0, 4.0);
    printf("cimag %a+%ai = %a\n", creal(z), cimag(z), cimag(z)); /* S4 */
    z = CMPLX(0.0, -1.0);
    printf("cimag %a+%ai = %a\n", creal(z), cimag(z), cimag(z)); /* S4 */
}

static void test_clog(void)
{
    double complex z = CMPLX(1.0, 0.0);
    double complex w = clog(z);
    printf("clog %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(0.0, 1.0);
    w = clog(z);
    printf("clog %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
}

static void test_conj(void)
{
    double complex z = CMPLX(3.0, 4.0);
    double complex w = conj(z);
    printf("conj %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(-1.0, 2.0);
    w = conj(z);
    printf("conj %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
}

static void test_cpow(void)
{
    double complex z = CMPLX(1.0, 0.0);
    double complex w_exp = CMPLX(2.0, 0.0);
    double complex w = cpow(z, w_exp);
    printf("cpow %a+%ai %a+%ai = %a+%ai\n", /* S4 */
           creal(z), cimag(z), creal(w_exp), cimag(w_exp), creal(w), cimag(w));
    z = CMPLX(1.0, 1.0);
    w_exp = CMPLX(2.0, 0.0);
    w = cpow(z, w_exp);
    printf("cpow %a+%ai %a+%ai = %a+%ai\n", /* S4 */
           creal(z), cimag(z), creal(w_exp), cimag(w_exp), creal(w), cimag(w));
}

static void test_cproj(void)
{
    double complex z = CMPLX(1.0, 2.0);
    double complex w = cproj(z);
    printf("cproj %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
}

static void test_creal(void)
{
    double complex z = CMPLX(3.0, 4.0);
    printf("creal %a+%ai = %a\n", creal(z), cimag(z), creal(z)); /* S4 */
    z = CMPLX(-2.0, 1.0);
    printf("creal %a+%ai = %a\n", creal(z), cimag(z), creal(z)); /* S4 */
}

static void test_csin(void)
{
    double complex z = CMPLX(0.0, 0.0);
    double complex w = csin(z);
    printf("csin %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(1.0, 1.0);
    w = csin(z);
    printf("csin %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
}

static void test_csinh(void)
{
    double complex z = CMPLX(0.0, 0.0);
    double complex w = csinh(z);
    printf("csinh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(1.0, 1.0);
    w = csinh(z);
    printf("csinh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
}

static void test_csqrt(void)
{
    double complex z = CMPLX(4.0, 0.0);
    double complex w = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(0.0, 4.0);
    w = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
}

static void test_ctan(void)
{
    double complex z = CMPLX(0.0, 0.0);
    double complex w = ctan(z);
    printf("ctan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(1.0, 1.0);
    w = ctan(z);
    printf("ctan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
}

static void test_ctanh(void)
{
    double complex z = CMPLX(0.0, 0.0);
    double complex w = ctanh(z);
    printf("ctanh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(1.0, 1.0);
    w = ctanh(z);
    printf("ctanh %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
}

static void test_redupi(void)
{
    printf("__redupi %a = %a\n", 0.0, __redupi(0.0)); /* S4 */
    printf("__redupi %a = %a\n", 3.141592653589793, __redupi(3.141592653589793)); /* S4 */
    printf("__redupi %a = %a\n", 6.283185307179586, __redupi(6.283185307179586)); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Complex functions — float                                           */
/* ------------------------------------------------------------------ */

static void test_cabsf(void)
{
    float complex z = CMPLXF(3.0f, 4.0f);
    printf("cabsf %a+%ai = %a\n", crealf(z), cimagf(z), cabsf(z)); /* S4 */
    z = CMPLXF(0.0f, 0.0f);
    printf("cabsf %a+%ai = %a\n", crealf(z), cimagf(z), cabsf(z)); /* S4 */
}

static void test_cacosf(void)
{
    float complex z = CMPLXF(0.5f, 0.0f);
    float complex w = cacosf(z);
    printf("cacosf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
}

static void test_cacoshf(void)
{
    float complex z = CMPLXF(1.0f, 0.0f);
    float complex w = cacoshf(z);
    printf("cacoshf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
}

static void test_cargf(void)
{
    float complex z = CMPLXF(1.0f, 0.0f);
    printf("cargf %a+%ai = %a\n", crealf(z), cimagf(z), cargf(z)); /* S4 */
    z = CMPLXF(0.0f, 1.0f);
    printf("cargf %a+%ai = %a\n", crealf(z), cimagf(z), cargf(z)); /* S4 */
}

static void test_casinf(void)
{
    float complex z = CMPLXF(0.5f, 0.0f);
    float complex w = casinf(z);
    printf("casinf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
}

static void test_casinhf(void)
{
    float complex z = CMPLXF(1.0f, 0.0f);
    float complex w = casinhf(z);
    printf("casinhf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
}

static void test_catanf(void)
{
    float complex z = CMPLXF(1.0f, 0.0f);
    float complex w = catanf(z);
    printf("catanf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
}

static void test_catanhf(void)
{
    float complex z = CMPLXF(0.5f, 0.0f);
    float complex w = catanhf(z);
    printf("catanhf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
}

static void test_ccosf(void)
{
    float complex z = CMPLXF(0.0f, 0.0f);
    float complex w = ccosf(z);
    printf("ccosf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
    z = CMPLXF(1.0f, 1.0f);
    w = ccosf(z);
    printf("ccosf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
}

static void test_ccoshf(void)
{
    float complex z = CMPLXF(0.0f, 0.0f);
    float complex w = ccoshf(z);
    printf("ccoshf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
    z = CMPLXF(1.0f, 1.0f);
    w = ccoshf(z);
    printf("ccoshf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
}

static void test_ccoshsinhf(void)
{
    float c, s;
    __ccoshsinhf(0.0f, &c, &s);
    printf("__ccoshsinhf %a c=%a s=%a\n", 0.0f, c, s); /* S4 */
    __ccoshsinhf(1.0f, &c, &s);
    printf("__ccoshsinhf %a c=%a s=%a\n", 1.0f, c, s); /* S4 */
    __ccoshsinhf(0.3f, &c, &s);
    printf("__ccoshsinhf %a c=%a s=%a\n", 0.3f, c, s); /* S4 */
}

static void test_cexpf(void)
{
    float complex z = CMPLXF(0.0f, 0.0f);
    float complex w = cexpf(z);
    printf("cexpf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
    z = CMPLXF(1.0f, 0.0f);
    w = cexpf(z);
    printf("cexpf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
}

static void test_cimagf(void)
{
    float complex z = CMPLXF(3.0f, 4.0f);
    printf("cimagf %a+%ai = %a\n", crealf(z), cimagf(z), cimagf(z)); /* S4 */
    z = CMPLXF(0.0f, -1.0f);
    printf("cimagf %a+%ai = %a\n", crealf(z), cimagf(z), cimagf(z)); /* S4 */
}

static void test_clogf(void)
{
    float complex z = CMPLXF(1.0f, 0.0f);
    float complex w = clogf(z);
    printf("clogf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
    z = CMPLXF(0.0f, 1.0f);
    w = clogf(z);
    printf("clogf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
}

static void test_conjf(void)
{
    float complex z = CMPLXF(3.0f, 4.0f);
    float complex w = conjf(z);
    printf("conjf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
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
    printf("cpowf %a+%ai %a+%ai = %a+%ai\n", /* S4 */
           crealf(z), cimagf(z), crealf(w_exp), cimagf(w_exp), crealf(w), cimagf(w));
}

static void test_cprojf(void)
{
    float complex z = CMPLXF(1.0f, 2.0f);
    float complex w = cprojf(z);
    printf("cprojf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
}

static void test_crealf(void)
{
    float complex z = CMPLXF(3.0f, 4.0f);
    printf("crealf %a+%ai = %a\n", crealf(z), cimagf(z), crealf(z)); /* S4 */
}

static void test_csinf(void)
{
    float complex z = CMPLXF(0.0f, 0.0f);
    float complex w = csinf(z);
    printf("csinf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
    z = CMPLXF(1.0f, 1.0f);
    w = csinf(z);
    printf("csinf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
}

static void test_csinhf(void)
{
    float complex z = CMPLXF(0.0f, 0.0f);
    float complex w = csinhf(z);
    printf("csinhf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
    z = CMPLXF(1.0f, 1.0f);
    w = csinhf(z);
    printf("csinhf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
}

static void test_csqrtf(void)
{
    float complex z = CMPLXF(4.0f, 0.0f);
    float complex w = csqrtf(z);
    printf("csqrtf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
    z = CMPLXF(0.0f, 4.0f);
    w = csqrtf(z);
    printf("csqrtf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
}

static void test_ctanf(void)
{
    float complex z = CMPLXF(0.0f, 0.0f);
    float complex w = ctanf(z);
    printf("ctanf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
    z = CMPLXF(1.0f, 1.0f);
    w = ctanf(z);
    printf("ctanf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
}

static void test_ctanhf(void)
{
    float complex z = CMPLXF(0.0f, 0.0f);
    float complex w = ctanhf(z);
    printf("ctanhf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
    z = CMPLXF(1.0f, 1.0f);
    w = ctanhf(z);
    printf("ctanhf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
}

static void test_redupif(void)
{
    printf("__redupif %a = %a\n", 0.0f, __redupif(0.0f)); /* S4 */
    printf("__redupif %a = %a\n", 3.141592653589793f, __redupif(3.141592653589793f)); /* S4 */
    printf("__redupif %a = %a\n", 6.283185307179586f, __redupif(6.283185307179586f)); /* S4 */
}

/* ------------------------------------------------------------------ */
/* Static bridge functions                                             */
/* ------------------------------------------------------------------ */

static void test_bridge_rem_pio2_internal(void)
{
    double x[3] = { 0x1.921fb4p+0, 0.0, 0.0 };
    double y[2];
    int n = bridge___rem_pio2_internal(x, y, -1, 1);
    printf("bridge___rem_pio2_internal n=%d y0=%a y1=%a\n", n, y[0], y[1]); /* S4 */

    x[0] = 0x1.8p+0;
    x[1] = 0.0;
    n = bridge___rem_pio2_internal(x, y, 0, 1);
    printf("bridge___rem_pio2_internal n=%d y0=%a y1=%a\n", n, y[0], y[1]); /* S4 */
}

static void test_bridge_tan(void)
{
    printf("bridge___tan %a %a %d = %a\n", 0.5, 0.0, 1, bridge___tan(0.5, 0.0, 1)); /* S4 */
    printf("bridge___tan %a %a %d = %a\n", 0.0, 0.0, 1, bridge___tan(0.0, 0.0, 1)); /* S4 */
    printf("bridge___tan %a %a %d = %a\n", 0.3, 0.0, 0, bridge___tan(0.3, 0.0, 0)); /* S4 */
}

static void test_bridge_sin_pi(void)
{
    printf("bridge___sin_pi %a = %a\n", 0.5, bridge___sin_pi(0.5)); /* S4 */
    printf("bridge___sin_pi %a = %a\n", 1.0, bridge___sin_pi(1.0)); /* S4 */
    printf("bridge___sin_pi %a = %a\n", 0.25, bridge___sin_pi(0.25)); /* S4 */
    printf("bridge___sin_pi %a = %a\n", 2.0, bridge___sin_pi(2.0)); /* S4 */
}

static void test_bridge_rem_pio2f_internal(void)
{
    float x[3] = { 0x1.921fb4p+0f, 0.0f, 0.0f };
    float y[2];
    int n = bridge___rem_pio2f_internal(x, y, -1, 1);
    printf("bridge___rem_pio2f_internal n=%d y0=%a y1=%a\n", n, y[0], y[1]); /* S4 */

    x[0] = 0x1.8p+0f;
    x[1] = 0.0f;
    n = bridge___rem_pio2f_internal(x, y, 0, 1);
    printf("bridge___rem_pio2f_internal n=%d y0=%a y1=%a\n", n, y[0], y[1]); /* S4 */
}

static void test_bridge_tanf(void)
{
    printf("bridge___tanf %a %a %d = %a\n", 0.5f, 0.0f, 1, bridge___tanf(0.5f, 0.0f, 1)); /* S4 */
    printf("bridge___tanf %a %a %d = %a\n", 0.0f, 0.0f, 1, bridge___tanf(0.0f, 0.0f, 1)); /* S4 */
    printf("bridge___tanf %a %a %d = %a\n", 0.3f, 0.0f, 0, bridge___tanf(0.3f, 0.0f, 0)); /* S4 */
}

static void test_bridge_ctans(void)
{
    double complex z = CMPLX(0.1, 0.1);
    double r = bridge___ctans(z);
    printf("bridge___ctans %a+%ai = %a\n", creal(z), cimag(z), r); /* S4 */
    z = CMPLX(0.01, 0.05);
    r = bridge___ctans(z);
    printf("bridge___ctans %a+%ai = %a\n", creal(z), cimag(z), r); /* S4 */
}

static void test_bridge_ctansf(void)
{
    float complex z = CMPLXF(0.1f, 0.1f);
    float r = bridge___ctansf(z);
    printf("bridge___ctansf %a+%ai = %a\n", crealf(z), cimagf(z), r); /* S4 */
    z = CMPLXF(0.01f, 0.05f);
    r = bridge___ctansf(z);
    printf("bridge___ctansf %a+%ai = %a\n", crealf(z), cimagf(z), r); /* S4 */
}

static void test_bridge_sin_pif(void)
{
    printf("bridge___sin_pif %a = %a\n", 0.5f, bridge___sin_pif(0.5f)); /* S4 */
    printf("bridge___sin_pif %a = %a\n", 1.0f, bridge___sin_pif(1.0f)); /* S4 */
    printf("bridge___sin_pif %a = %a\n", 0.25f, bridge___sin_pif(0.25f)); /* S4 */
    printf("bridge___sin_pif %a = %a\n", 2.0f, bridge___sin_pif(2.0f)); /* S4 */
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
    printf("acos %a = %a\n", 1.5, acos(1.5)); /* R1 */
    printf("acos %a = %a\n", -1.5, acos(-1.5)); /* R1 */
    /* Branch 106: small |x| < 2^-57 */
    printf("acos %a = %a\n", 0x1p-60, acos(0x1p-60)); /* R1 */
    /* Branch 115: x > 0.5 → sqrt path */
    printf("acos %a = %a\n", 0.7, acos(0.7)); /* R1 */
    printf("acos %a = %a\n", 0.9, acos(0.9)); /* R1 */
    printf("acos %a = %a\n", -0.7, acos(-0.7)); /* R1 */
    printf("acos %a = %a\n", -0.9, acos(-0.9)); /* R1 */
    /* NaN */
    printf("acos nan = %a\n", acos(D_NAN)); /* R1 */
}

static void test_acosf_branches(void)
{
    /* Branch 36: |x|==1 */
    printf("acosf %a = %a\n", -1.0f, acosf(-1.0f)); /* R1 */
    /* Branch 41: |x|>1 */
    printf("acosf %a = %a\n", 1.5f, acosf(1.5f)); /* R1 */
    printf("acosf %a = %a\n", -1.5f, acosf(-1.5f)); /* R1 */
    /* Branch 52: small |x| */
    printf("acosf %a = %a\n", 0x1p-60f, acosf(0x1p-60f)); /* R1 */
    /* Branch 61: x > 0.5 / x < -0.5 */
    printf("acosf %a = %a\n", 0.7f, acosf(0.7f)); /* R1 */
    printf("acosf %a = %a\n", -0.7f, acosf(-0.7f)); /* R1 */
    printf("acosf %a = %a\n", 0.9f, acosf(0.9f)); /* R1 */
    printf("acosf nan = %a\n", acosf(F_NAN)); /* R1 */
}

static void test_acosh_branches(void)
{
    /* Branch 73: x < 1 → NaN */
    printf("acosh %a = %a\n", 0.5, acosh(0.5)); /* R1 */
    printf("acosh %a = %a\n", -1.0, acosh(-1.0)); /* R1 */
    /* Branch 79: x > 2^28 */
    printf("acosh %a = %a\n", 0x1p30, acosh(0x1p30)); /* R1 */
    /* Branch 80: x exactly 1 */
    printf("acosh %a = %a\n", 1.0 + 0x1p-52, acosh(1.0 + 0x1p-52)); /* R1 */
    /* inf */
    printf("acosh %a = %a\n", D_INF, acosh(D_INF)); /* R1 */
    printf("acosh nan = %a\n", acosh(D_NAN)); /* R1 */
}

static void test_acoshf_branches(void)
{
    /* Branch 22: x < 1 */
    printf("acoshf %a = %a\n", 0.5f, acoshf(0.5f)); /* R1 */
    /* Branch 28: x > 2^28 */
    printf("acoshf %a = %a\n", 0x1p30f, acoshf(0x1p30f)); /* R1 */
    /* Branch 29: inf */
    printf("acoshf %a = %a\n", F_INF, acoshf(F_INF)); /* R1 */
    /* Branch 36: x > 2.0 */
    printf("acoshf %a = %a\n", 3.0f, acoshf(3.0f)); /* R1 */
    printf("acoshf nan = %a\n", acoshf(F_NAN)); /* R1 */
}

static void test_asin_branches(void)
{
    /* Branch 92: |x|>1 → NaN */
    printf("asin %a = %a\n", 1.5, asin(1.5)); /* R1 */
    printf("asin %a = %a\n", -1.5, asin(-1.5)); /* R1 */
    /* Branch 104: |x|<2^-26 non-zero */
    printf("asin %a = %a\n", 0x1p-30, asin(0x1p-30)); /* R1 */
    /* Branch 105: x == 0 */
    printf("asin %a = %a\n", -0.0, asin(-0.0)); /* R1 */
    /* Branch 128: |x|>0.975 */
    printf("asin %a = %a\n", 0.99, asin(0.99)); /* R1 */
    printf("asin %a = %a\n", -0.99, asin(-0.99)); /* R1 */
    printf("asin nan = %a\n", asin(D_NAN)); /* R1 */
}

static void test_asinf_branches(void)
{
    /* Branch 36: |x|==1 */
    printf("asinf %a = %a\n", -1.0f, asinf(-1.0f)); /* R1 */
    /* Branch 38: |x|>1 */
    printf("asinf %a = %a\n", 1.5f, asinf(1.5f)); /* R1 */
    printf("asinf %a = %a\n", -1.5f, asinf(-1.5f)); /* R1 */
    /* Branch 45: |x|<2^-27 non-zero */
    printf("asinf %a = %a\n", 0x1p-30f, asinf(0x1p-30f)); /* R1 */
    /* Branch 69: |x|>0.975 */
    printf("asinf %a = %a\n", 0.99f, asinf(0.99f)); /* R1 */
    printf("asinf %a = %a\n", -0.99f, asinf(-0.99f)); /* R1 */
    printf("asinf nan = %a\n", asinf(F_NAN)); /* R1 */
}

static void test_asinh_branches(void)
{
    /* Branch 74: inf or NaN */
    printf("asinh %a = %a\n", D_INF, asinh(D_INF)); /* R1 */
    printf("asinh %a = %a\n", D_NINF, asinh(D_NINF)); /* R1 */
    printf("asinh nan = %a\n", asinh(D_NAN)); /* R1 */
    /* Branch 79: x==0 */
    printf("asinh %a = %a\n", -0.0, asinh(-0.0)); /* R1 */
    /* Branch 86: |x|>2^28 */
    printf("asinh %a = %a\n", 0x1p30, asinh(0x1p30)); /* R1 */
    printf("asinh %a = %a\n", -0x1p30, asinh(-0x1p30)); /* R1 */
    /* Branch 88: 2<|x|<=2^28 */
    printf("asinh %a = %a\n", 3.0, asinh(3.0)); /* R1 */
    printf("asinh %a = %a\n", -3.0, asinh(-3.0)); /* R1 */
    /* small */
    printf("asinh %a = %a\n", 0x1p-30, asinh(0x1p-30)); /* R1 */
}

static void test_asinhf_branches(void)
{
    /* Branch 23: inf or NaN */
    printf("asinhf %a = %a\n", F_INF, asinhf(F_INF)); /* R1 */
    printf("asinhf %a = %a\n", F_NINF, asinhf(F_NINF)); /* R1 */
    printf("asinhf nan = %a\n", asinhf(F_NAN)); /* R1 */
    /* Branch 35: |x|>2^28 */
    printf("asinhf %a = %a\n", 0x1p30f, asinhf(0x1p30f)); /* R1 */
    printf("asinhf %a = %a\n", -0x1p30f, asinhf(-0x1p30f)); /* R1 */
    /* Branch 37: 2<|x|<=2^28 */
    printf("asinhf %a = %a\n", 3.0f, asinhf(3.0f)); /* R1 */
    /* Branch 45: |x|>=2^-14 */
    printf("asinhf %a = %a\n", 0.5f, asinhf(0.5f)); /* R1 */
    printf("asinhf %a = %a\n", 0x1p-30f, asinhf(0x1p-30f)); /* R1 */
}

static void test_atan_branches(void)
{
    /* Branch 100: |x|>=2^66 */
    printf("atan %a = %a\n", 0x1p80, atan(0x1p80)); /* R1 */
    printf("atan %a = %a\n", -0x1p80, atan(-0x1p80)); /* R1 */
    /* Branch 104: NaN */
    printf("atan nan = %a\n", atan(D_NAN)); /* R1 */
    /* Branch 105: x==0 */
    printf("atan %a = %a\n", -0.0, atan(-0.0)); /* R1 */
    /* Branch 109: inf */
    printf("atan %a = %a\n", D_INF, atan(D_INF)); /* R1 */
    printf("atan %a = %a\n", D_NINF, atan(D_NINF)); /* R1 */
    /* Branch 117: |x|<2^-27 */
    printf("atan %a = %a\n", 0x1p-30, atan(0x1p-30)); /* R1 */
    /* Branch 118: id=-1 (|x|<7/16) */
    printf("atan %a = %a\n", 0.3, atan(0.3)); /* R1 */
    printf("atan %a = %a\n", -0.3, atan(-0.3)); /* R1 */
    /* Branch 129: 7/16<=|x|<11/16 */
    printf("atan %a = %a\n", 0.5, atan(0.5)); /* R1 */
    printf("atan %a = %a\n", -0.5, atan(-0.5)); /* R1 */
    /* Branch 138: 11/16<=|x|<2.4375 */
    printf("atan %a = %a\n", 2.0, atan(2.0)); /* R1 */
    printf("atan %a = %a\n", -2.0, atan(-2.0)); /* R1 */
    /* id>=2: |x|>=2.4375 */
    printf("atan %a = %a\n", 3.0, atan(3.0)); /* R1 */
    printf("atan %a = %a\n", -3.0, atan(-3.0)); /* R1 */
}

static void test_atanf_branches(void)
{
    /* Branch 50: |x|>=2^34 */
    printf("atanf %a = %a\n", 0x1p40f, atanf(0x1p40f)); /* R1 */
    printf("atanf %a = %a\n", -0x1p40f, atanf(-0x1p40f)); /* R1 */
    /* Branch 55: |x|<2^-29 */
    printf("atanf %a = %a\n", 0x1p-30f, atanf(0x1p-30f)); /* R1 */
    printf("atanf nan = %a\n", atanf(F_NAN)); /* R1 */
    /* Branch 63: |x|<0.4375 */
    printf("atanf %a = %a\n", 0.2f, atanf(0.2f)); /* R1 */
    printf("atanf %a = %a\n", -0.2f, atanf(-0.2f)); /* R1 */
    /* Branch 75: 0.4375<=|x|<1.1875 */
    printf("atanf %a = %a\n", 0.7f, atanf(0.7f)); /* R1 */
    printf("atanf %a = %a\n", -0.7f, atanf(-0.7f)); /* R1 */
    /* Branch 84: 1.1875<=|x|<2.4375 */
    printf("atanf %a = %a\n", 2.0f, atanf(2.0f)); /* R1 */
    printf("atanf %a = %a\n", -2.0f, atanf(-2.0f)); /* R1 */
    /* id>=2: |x|>=2.4375 */
    printf("atanf %a = %a\n", 3.0f, atanf(3.0f)); /* R1 */
    printf("atanf %a = %a\n", -3.0f, atanf(-3.0f)); /* R1 */
    /* Branch 101: id>=0 */
    printf("atanf %a = %a\n", F_INF, atanf(F_INF)); /* R1 */
    printf("atanf %a = %a\n", F_NINF, atanf(F_NINF)); /* R1 */
}

static void test_atan2_branches(void)
{
    /* Branch 102-103: NaN inputs */
    printf("atan2 nan 1 = %a\n", atan2(D_NAN, 1.0)); /* R1 */
    printf("atan2 1 nan = %a\n", atan2(1.0, D_NAN)); /* R1 */
    /* Branch 116: y==0 */
    printf("atan2 %a %a = %a\n", 0.0, 1.0, atan2(0.0, 1.0)); /* S4 */
    printf("atan2 %a %a = %a\n", -0.0, 1.0, atan2(-0.0, 1.0)); /* R1 */
    printf("atan2 %a %a = %a\n", 0.0, -1.0, atan2(0.0, -1.0)); /* R1 */
    printf("atan2 %a %a = %a\n", -0.0, -1.0, atan2(-0.0, -1.0)); /* R1 */
    printf("atan2 %a %a = %a\n", 0.0, 0.0, atan2(0.0, 0.0)); /* R1 */
    printf("atan2 %a %a = %a\n", -0.0, 0.0, atan2(-0.0, 0.0)); /* R1 */
    /* Branch 124: x==0 */
    printf("atan2 %a %a = %a\n", 1.0, 0.0, atan2(1.0, 0.0)); /* S4 */
    printf("atan2 %a %a = %a\n", -1.0, 0.0, atan2(-1.0, 0.0)); /* R1 */
    printf("atan2 %a %a = %a\n", -1.0, -0.0, atan2(-1.0, -0.0)); /* R1 */
    /* Branch 135: x==0, y!=0 */
    printf("atan2 %a %a = %a\n", 1.0, -0.0, atan2(1.0, -0.0)); /* R1 */
    /* Branch 170: x is +Inf, y is Inf */
    printf("atan2 %a %a = %a\n", D_INF, D_INF, atan2(D_INF, D_INF)); /* R1 */
    printf("atan2 %a %a = %a\n", D_NINF, D_INF, atan2(D_NINF, D_INF)); /* R1 */
    printf("atan2 %a %a = %a\n", D_INF, D_NINF, atan2(D_INF, D_NINF)); /* R1 */
    printf("atan2 %a %a = %a\n", D_NINF, D_NINF, atan2(D_NINF, D_NINF)); /* R1 */
    /* Branch 177: x is Inf, y is not Inf */
    printf("atan2 %a %a = %a\n", 1.0, D_INF, atan2(1.0, D_INF)); /* R1 */
    printf("atan2 %a %a = %a\n", 1.0, D_NINF, atan2(1.0, D_NINF)); /* R1 */
    printf("atan2 %a %a = %a\n", -1.0, D_INF, atan2(-1.0, D_INF)); /* R1 */
    printf("atan2 %a %a = %a\n", -1.0, D_NINF, atan2(-1.0, D_NINF)); /* R1 */
    /* Branch 180: y is Inf */
    printf("atan2 %a %a = %a\n", D_INF, 1.0, atan2(D_INF, 1.0)); /* R1 */
    printf("atan2 %a %a = %a\n", D_NINF, 1.0, atan2(D_NINF, 1.0)); /* R1 */
    /* Branch 190: k>60 */
    printf("atan2 %a %a = %a\n", 0x1p70, 1.0, atan2(0x1p70, 1.0)); /* R1 */
    printf("atan2 %a %a = %a\n", -0x1p70, 1.0, atan2(-0x1p70, 1.0)); /* R1 */
    /* Branch 193: k<-60 */
    printf("atan2 %a %a = %a\n", 0x1p-70, -1.0, atan2(0x1p-70, -1.0)); /* R1 */
    printf("atan2 %a %a = %a\n", -0x1p-70, -1.0, atan2(-0x1p-70, -1.0)); /* R1 */
    /* branches for table lookup in quadrants */
    printf("atan2 %a %a = %a\n", 2.0, 1.0, atan2(2.0, 1.0)); /* R1 */
    printf("atan2 %a %a = %a\n", 1.0, 2.0, atan2(1.0, 2.0)); /* R1 */
    printf("atan2 %a %a = %a\n", -2.0, -1.0, atan2(-2.0, -1.0)); /* R1 */
    printf("atan2 %a %a = %a\n", -1.0, -2.0, atan2(-1.0, -2.0)); /* R1 */
}

static void test_atan2f_branches(void)
{
    printf("atan2f nan 1 = %a\n", atan2f(F_NAN, 1.0f)); /* R1 */
    printf("atan2f 1 nan = %a\n", atan2f(1.0f, F_NAN)); /* R1 */
    printf("atan2f %a %a = %a\n", 0.0f, 1.0f, atan2f(0.0f, 1.0f)); /* S4 */
    printf("atan2f %a %a = %a\n", -0.0f, 1.0f, atan2f(-0.0f, 1.0f)); /* R1 */
    printf("atan2f %a %a = %a\n", 0.0f, -1.0f, atan2f(0.0f, -1.0f)); /* R1 */
    printf("atan2f %a %a = %a\n", -0.0f, -1.0f, atan2f(-0.0f, -1.0f)); /* R1 */
    printf("atan2f %a %a = %a\n", 0.0f, 0.0f, atan2f(0.0f, 0.0f)); /* R1 */
    printf("atan2f %a %a = %a\n", -0.0f, 0.0f, atan2f(-0.0f, 0.0f)); /* R1 */
    printf("atan2f %a %a = %a\n", 1.0f, 0.0f, atan2f(1.0f, 0.0f)); /* R1 */
    printf("atan2f %a %a = %a\n", -1.0f, 0.0f, atan2f(-1.0f, 0.0f)); /* R1 */
    printf("atan2f %a %a = %a\n", 1.0f, -0.0f, atan2f(1.0f, -0.0f)); /* R1 */
    printf("atan2f %a %a = %a\n", -1.0f, -0.0f, atan2f(-1.0f, -0.0f)); /* R1 */
    printf("atan2f %a %a = %a\n", F_INF, F_INF, atan2f(F_INF, F_INF)); /* R1 */
    printf("atan2f %a %a = %a\n", F_NINF, F_INF, atan2f(F_NINF, F_INF)); /* R1 */
    printf("atan2f %a %a = %a\n", F_INF, F_NINF, atan2f(F_INF, F_NINF)); /* R1 */
    printf("atan2f %a %a = %a\n", F_NINF, F_NINF, atan2f(F_NINF, F_NINF)); /* R1 */
    printf("atan2f %a %a = %a\n", 1.0f, F_INF, atan2f(1.0f, F_INF)); /* R1 */
    printf("atan2f %a %a = %a\n", -1.0f, F_INF, atan2f(-1.0f, F_INF)); /* R1 */
    printf("atan2f %a %a = %a\n", 1.0f, F_NINF, atan2f(1.0f, F_NINF)); /* R1 */
    printf("atan2f %a %a = %a\n", F_INF, 1.0f, atan2f(F_INF, 1.0f)); /* R1 */
    printf("atan2f %a %a = %a\n", F_NINF, 1.0f, atan2f(F_NINF, 1.0f)); /* R1 */
    printf("atan2f %a %a = %a\n", 0x1p40f, 1.0f, atan2f(0x1p40f, 1.0f)); /* R1 */
    printf("atan2f %a %a = %a\n", 0x1p-40f, -1.0f, atan2f(0x1p-40f, -1.0f)); /* R1 */
    printf("atan2f %a %a = %a\n", -0x1p-40f, -1.0f, atan2f(-0x1p-40f, -1.0f)); /* R1 */
    printf("atan2f %a %a = %a\n", 2.0f, 1.0f, atan2f(2.0f, 1.0f)); /* R1 */
    printf("atan2f %a %a = %a\n", -2.0f, -1.0f, atan2f(-2.0f, -1.0f)); /* R1 */
}

static void test_atanh_branches(void)
{
    /* Branch 77: |x|>1 */
    printf("atanh %a = %a\n", 1.5, atanh(1.5)); /* R1 */
    printf("atanh %a = %a\n", -1.5, atanh(-1.5)); /* R1 */
    /* Branch 85: |x|==1 */
    printf("atanh %a = %a\n", 1.0, atanh(1.0)); /* R1 */
    printf("atanh %a = %a\n", -1.0, atanh(-1.0)); /* R1 */
    /* Branch 90: |x|<2^-28 */
    printf("atanh %a = %a\n", 0x1p-30, atanh(0x1p-30)); /* R1 */
    printf("atanh %a = %a\n", -0x1p-30, atanh(-0x1p-30)); /* R1 */
    /* Branch 99: |x|<0.5 */
    printf("atanh %a = %a\n", 0.3, atanh(0.3)); /* R1 */
    printf("atanh %a = %a\n", -0.3, atanh(-0.3)); /* R1 */
    printf("atanh nan = %a\n", atanh(D_NAN)); /* R1 */
    printf("atanh %a = %a\n", D_INF, atanh(D_INF)); /* R1 */
}

static void test_atanhf_branches(void)
{
    /* Branch 21: |x|>1 */
    printf("atanhf %a = %a\n", 1.5f, atanhf(1.5f)); /* R1 */
    printf("atanhf %a = %a\n", -1.5f, atanhf(-1.5f)); /* R1 */
    /* Branch 29: |x|==1 */
    printf("atanhf %a = %a\n", 1.0f, atanhf(1.0f)); /* R1 */
    printf("atanhf %a = %a\n", -1.0f, atanhf(-1.0f)); /* R1 */
    /* Branch 43: |x|<0.5 */
    printf("atanhf %a = %a\n", 0.3f, atanhf(0.3f)); /* R1 */
    printf("atanhf %a = %a\n", -0.3f, atanhf(-0.3f)); /* R1 */
    /* Branch 50: |x|>=0.5 (normal path) */
    printf("atanhf %a = %a\n", 0.7f, atanhf(0.7f)); /* R1 */
    printf("atanhf %a = %a\n", -0.7f, atanhf(-0.7f)); /* R1 */
    printf("atanhf nan = %a\n", atanhf(F_NAN)); /* R1 */
}

static void test_cosh_branches(void)
{
    /* Branch 73: inf or NaN */
    printf("cosh %a = %a\n", D_INF, cosh(D_INF)); /* R1 */
    printf("cosh %a = %a\n", D_NINF, cosh(D_NINF)); /* R1 */
    printf("cosh nan = %a\n", cosh(D_NAN)); /* R1 */
    /* Branch 90: |x|<2^-55 (tiny) */
    printf("cosh %a = %a\n", 0x1p-60, cosh(0x1p-60)); /* R1 */
    /* Branch 96: |x| in [0.5*ln2, 22] */
    printf("cosh %a = %a\n", 5.0, cosh(5.0)); /* R1 */
    printf("cosh %a = %a\n", -5.0, cosh(-5.0)); /* R1 */
    /* |x| in [22, log(maxdouble)] */
    printf("cosh %a = %a\n", 500.0, cosh(500.0)); /* R1 */
    /* Branch 103: overflow threshold */
    printf("cosh %a = %a\n", 710.0, cosh(710.0)); /* R1 */
    printf("cosh %a = %a\n", 712.0, cosh(712.0)); /* R1 */
}

static void test_coshf_branches(void)
{
    /* Branch 23: inf or NaN */
    printf("coshf %a = %a\n", F_INF, coshf(F_INF)); /* R1 */
    printf("coshf %a = %a\n", F_NINF, coshf(F_NINF)); /* R1 */
    printf("coshf nan = %a\n", coshf(F_NAN)); /* R1 */
    /* Branch 40: |x|<2^-28 */
    printf("coshf %a = %a\n", 0x1p-30f, coshf(0x1p-30f)); /* R1 */
    /* Branch 46: |x| in [0.5*ln2, 9] */
    printf("coshf %a = %a\n", 5.0f, coshf(5.0f)); /* R1 */
    /* Branch 51: |x| in [9, log(maxfloat)] */
    printf("coshf %a = %a\n", 50.0f, coshf(50.0f)); /* R1 */
    /* overflow */
    printf("coshf %a = %a\n", 200.0f, coshf(200.0f)); /* R1 */
}

static void test_sinh_branches(void)
{
    /* Branch 76: inf or NaN */
    printf("sinh %a = %a\n", D_INF, sinh(D_INF)); /* R1 */
    printf("sinh %a = %a\n", D_NINF, sinh(D_NINF)); /* R1 */
    printf("sinh nan = %a\n", sinh(D_NAN)); /* R1 */
    /* Branch 87: |x|<2^-28 */
    printf("sinh %a = %a\n", 0x1p-30, sinh(0x1p-30)); /* R1 */
    printf("sinh %a = %a\n", -0x1p-30, sinh(-0x1p-30)); /* R1 */
    /* Branch 89: x==0 */
    printf("sinh %a = %a\n", -0.0, sinh(-0.0)); /* R1 */
    /* |x| in [0,22] */
    printf("sinh %a = %a\n", 5.0, sinh(5.0)); /* R1 */
    printf("sinh %a = %a\n", -5.0, sinh(-5.0)); /* R1 */
    /* Branch 106: |x| in [22, log(maxdouble)] */
    printf("sinh %a = %a\n", 500.0, sinh(500.0)); /* R1 */
    /* overflow */
    printf("sinh %a = %a\n", 710.0, sinh(710.0)); /* R1 */
    printf("sinh %a = %a\n", -710.0, sinh(-710.0)); /* R1 */
}

static void test_sinhf_branches(void)
{
    /* Branch 23: inf or NaN */
    printf("sinhf %a = %a\n", F_INF, sinhf(F_INF)); /* R1 */
    printf("sinhf %a = %a\n", F_NINF, sinhf(F_NINF)); /* R1 */
    printf("sinhf nan = %a\n", sinhf(F_NAN)); /* R1 */
    /* Branch 29: |x|<2^-28 non-zero */
    printf("sinhf %a = %a\n", 0x1p-30f, sinhf(0x1p-30f)); /* R1 */
    printf("sinhf %a = %a\n", -0x1p-30f, sinhf(-0x1p-30f)); /* R1 */
    /* Branch 34: x==0 */
    printf("sinhf %a = %a\n", -0.0f, sinhf(-0.0f)); /* R1 */
    /* Branch 53: |x| in [9, log(maxfloat)] */
    printf("sinhf %a = %a\n", 50.0f, sinhf(50.0f)); /* R1 */
    /* overflow */
    printf("sinhf %a = %a\n", 200.0f, sinhf(200.0f)); /* R1 */
    printf("sinhf %a = %a\n", -200.0f, sinhf(-200.0f)); /* R1 */
}

static void test_tanh_branches(void)
{
    /* Branch 74: inf or NaN */
    printf("tanh %a = %a\n", D_INF, tanh(D_INF)); /* R1 */
    printf("tanh %a = %a\n", D_NINF, tanh(D_NINF)); /* R1 */
    printf("tanh nan = %a\n", tanh(D_NAN)); /* R1 */
    /* Branch 77: |x|>=1 */
    printf("tanh %a = %a\n", 2.0, tanh(2.0)); /* R1 */
    printf("tanh %a = %a\n", -2.0, tanh(-2.0)); /* R1 */
    /* Branch 85: |x|<2^-55 */
    printf("tanh %a = %a\n", 0x1p-60, tanh(0x1p-60)); /* R1 */
    /* Branch 87: x==0 */
    printf("tanh %a = %a\n", -0.0, tanh(-0.0)); /* R1 */
    /* Branch 94: |x|>=1 path */
    printf("tanh %a = %a\n", 5.0, tanh(5.0)); /* R1 */
    printf("tanh %a = %a\n", -5.0, tanh(-5.0)); /* R1 */
    /* large */
    printf("tanh %a = %a\n", 30.0, tanh(30.0)); /* R1 */
    printf("tanh %a = %a\n", -30.0, tanh(-30.0)); /* R1 */
}

static void test_tanhf_branches(void)
{
    /* Branch 23: inf or NaN */
    printf("tanhf %a = %a\n", F_INF, tanhf(F_INF)); /* R1 */
    printf("tanhf %a = %a\n", F_NINF, tanhf(F_NINF)); /* R1 */
    printf("tanhf nan = %a\n", tanhf(F_NAN)); /* R1 */
    /* Branch 26: |x|>=1 */
    printf("tanhf %a = %a\n", 2.0f, tanhf(2.0f)); /* R1 */
    printf("tanhf %a = %a\n", -2.0f, tanhf(-2.0f)); /* R1 */
    /* Branch 34: x==0 */
    printf("tanhf %a = %a\n", -0.0f, tanhf(-0.0f)); /* R1 */
    /* Branch 43: |x|<2^-28 */
    printf("tanhf %a = %a\n", 0x1p-30f, tanhf(0x1p-30f)); /* R1 */
    /* Branch 56: large */
    printf("tanhf %a = %a\n", 20.0f, tanhf(20.0f)); /* R1 */
    printf("tanhf %a = %a\n", -20.0f, tanhf(-20.0f)); /* R1 */
}

static void test_exp_branches(void)
{
    /* Branch 101: |x|>=709.78 */
    printf("exp %a = %a\n", 800.0, exp(800.0)); /* R1 */
    printf("exp %a = %a\n", -800.0, exp(-800.0)); /* R1 */
    /* Branch 102: inf or NaN */
    printf("exp %a = %a\n", D_INF, exp(D_INF)); /* R1 */
    printf("exp %a = %a\n", D_NINF, exp(D_NINF)); /* R1 */
    printf("exp nan = %a\n", exp(D_NAN)); /* R1 */
    /* Branch 113: overflow */
    printf("exp %a = %a\n", 710.0, exp(710.0)); /* R1 */
    /* Branch 117: underflow */
    printf("exp %a = %a\n", -750.0, exp(-750.0)); /* R1 */
    /* Branch 136: |x|<2^-32 non-zero */
    printf("exp %a = %a\n", 0x1p-40, exp(0x1p-40)); /* R1 */
    printf("exp %a = %a\n", -0x1p-40, exp(-0x1p-40)); /* R1 */
    /* Branch 137: x==0 */
    printf("exp %a = %a\n", -0.0, exp(-0.0)); /* R1 */
    /* Branch 150: k==0 */
    printf("exp %a = %a\n", 0.3, exp(0.3)); /* R1 */
    printf("exp %a = %a\n", -0.3, exp(-0.3)); /* R1 */
    /* Branch 156: k!=0 and k>=-1021 */
    printf("exp %a = %a\n", 2.0, exp(2.0)); /* R1 */
    printf("exp %a = %a\n", -2.0, exp(-2.0)); /* R1 */
    /* k< -1021 */
    printf("exp %a = %a\n", -745.0, exp(-745.0)); /* R1 */
}

static void test_expf_branches(void)
{
    /* Branch 49: inf */
    printf("expf %a = %a\n", F_INF, expf(F_INF)); /* R1 */
    /* Branch 52: -inf */
    printf("expf %a = %a\n", F_NINF, expf(F_NINF)); /* R1 */
    printf("expf nan = %a\n", expf(F_NAN)); /* R1 */
    /* Branch 56: overflow */
    printf("expf %a = %a\n", 200.0f, expf(200.0f)); /* R1 */
    /* underflow */
    printf("expf %a = %a\n", -200.0f, expf(-200.0f)); /* R1 */
    /* Branch 74: |x|<2^-23 non-zero */
    printf("expf %a = %a\n", 0x1p-30f, expf(0x1p-30f)); /* R1 */
    printf("expf %a = %a\n", -0x1p-30f, expf(-0x1p-30f)); /* R1 */
    /* Branch 75: x==0 */
    printf("expf %a = %a\n", -0.0f, expf(-0.0f)); /* R1 */
    /* Branch 88: k==0 */
    printf("expf %a = %a\n", 0.3f, expf(0.3f)); /* R1 */
    printf("expf %a = %a\n", -0.3f, expf(-0.3f)); /* R1 */
    /* Branch 94: k>=-125 */
    printf("expf %a = %a\n", 2.0f, expf(2.0f)); /* R1 */
    /* k<-125 (underflow path) */
    printf("expf %a = %a\n", -130.0f, expf(-130.0f)); /* R1 */
}

static void test_expm1_branches(void)
{
    /* Various ranges */
    printf("expm1 %a = %a\n", D_INF, expm1(D_INF)); /* R1 */
    printf("expm1 %a = %a\n", D_NINF, expm1(D_NINF)); /* R1 */
    printf("expm1 nan = %a\n", expm1(D_NAN)); /* R1 */
    printf("expm1 %a = %a\n", 0x1p-60, expm1(0x1p-60)); /* R1 */
    printf("expm1 %a = %a\n", -0x1p-60, expm1(-0x1p-60)); /* R1 */
    printf("expm1 %a = %a\n", -0.0, expm1(-0.0)); /* R1 */
    printf("expm1 %a = %a\n", 2.0, expm1(2.0)); /* R1 */
    printf("expm1 %a = %a\n", -2.0, expm1(-2.0)); /* R1 */
    printf("expm1 %a = %a\n", 0.5, expm1(0.5)); /* R1 */
    printf("expm1 %a = %a\n", -0.5, expm1(-0.5)); /* R1 */
    printf("expm1 %a = %a\n", 710.0, expm1(710.0)); /* R1 */
    printf("expm1 %a = %a\n", -50.0, expm1(-50.0)); /* R1 */
}

static void test_expm1f_branches(void)
{
    printf("expm1f %a = %a\n", F_INF, expm1f(F_INF)); /* R1 */
    printf("expm1f %a = %a\n", F_NINF, expm1f(F_NINF)); /* R1 */
    printf("expm1f nan = %a\n", expm1f(F_NAN)); /* R1 */
    printf("expm1f %a = %a\n", 0x1p-30f, expm1f(0x1p-30f)); /* R1 */
    printf("expm1f %a = %a\n", -0x1p-30f, expm1f(-0x1p-30f)); /* R1 */
    printf("expm1f %a = %a\n", -0.0f, expm1f(-0.0f)); /* R1 */
    printf("expm1f %a = %a\n", 2.0f, expm1f(2.0f)); /* R1 */
    printf("expm1f %a = %a\n", -2.0f, expm1f(-2.0f)); /* R1 */
    printf("expm1f %a = %a\n", 0.5f, expm1f(0.5f)); /* R1 */
    printf("expm1f %a = %a\n", -0.5f, expm1f(-0.5f)); /* R1 */
    printf("expm1f %a = %a\n", 200.0f, expm1f(200.0f)); /* R1 */
    printf("expm1f %a = %a\n", -50.0f, expm1f(-50.0f)); /* R1 */
}

static void test_log_branches(void)
{
    /* Branch 86: x==0 or subnormal */
    printf("log %a = %a\n", 0.0, log(0.0)); /* R1 */
    printf("log %a = %a\n", -0.0, log(-0.0)); /* R1 */
    /* Branch 87: x<0 */
    printf("log %a = %a\n", -1.0, log(-1.0)); /* R1 */
    /* subnormal */
    printf("log %a = %a\n", D_SUBNORM, log(D_SUBNORM)); /* R1 */
    /* Branch 91: normalize subnormal */
    printf("log %a = %a\n", 0x1p-1050, log(0x1p-1050)); /* R1 */
    /* Branch 104: inf or nan */
    printf("log %a = %a\n", D_INF, log(D_INF)); /* R1 */
    printf("log nan = %a\n", log(D_NAN)); /* R1 */
    /* Branch 127: k==0, f==0 */
    printf("log %a = %a\n", 1.0, log(1.0)); /* S4 */
    /* Branch 146: k!=0 */
    printf("log %a = %a\n", 0.5, log(0.5)); /* R1 */
    printf("log %a = %a\n", 0.25, log(0.25)); /* R1 */
}

static void test_logf_branches(void)
{
    printf("logf %a = %a\n", 0.0f, logf(0.0f)); /* R1 */
    printf("logf %a = %a\n", -1.0f, logf(-1.0f)); /* R1 */
    printf("logf %a = %a\n", F_SUBNORM, logf(F_SUBNORM)); /* R1 */
    printf("logf %a = %a\n", 0x1p-130f, logf(0x1p-130f)); /* R1 */
    printf("logf %a = %a\n", F_INF, logf(F_INF)); /* R1 */
    printf("logf nan = %a\n", logf(F_NAN)); /* R1 */
    printf("logf %a = %a\n", 1.0f, logf(1.0f)); /* S4 */
    printf("logf %a = %a\n", 0.5f, logf(0.5f)); /* R1 */
    printf("logf %a = %a\n", 0.25f, logf(0.25f)); /* R1 */
}

static void test_log10_branches(void)
{
    printf("log10 %a = %a\n", 0.0, log10(0.0)); /* R1 */
    printf("log10 %a = %a\n", -1.0, log10(-1.0)); /* R1 */
    printf("log10 %a = %a\n", D_SUBNORM, log10(D_SUBNORM)); /* R1 */
    printf("log10 %a = %a\n", D_INF, log10(D_INF)); /* R1 */
    printf("log10 nan = %a\n", log10(D_NAN)); /* R1 */
    printf("log10 %a = %a\n", 1.0, log10(1.0)); /* S4 */
    printf("log10 %a = %a\n", 0.5, log10(0.5)); /* R1 */
}

static void test_log10f_branches(void)
{
    printf("log10f %a = %a\n", 0.0f, log10f(0.0f)); /* R1 */
    printf("log10f %a = %a\n", F_SUBNORM, log10f(F_SUBNORM)); /* R1 */
    printf("log10f %a = %a\n", F_INF, log10f(F_INF)); /* R1 */
    printf("log10f %a = %a\n", 0.5f, log10f(0.5f)); /* R1 */
}

static void test_log2_branches(void)
{
    printf("log2 %a = %a\n", 0.0, log2(0.0)); /* R1 */
    printf("log2 %a = %a\n", -1.0, log2(-1.0)); /* R1 */
    printf("log2 %a = %a\n", D_SUBNORM, log2(D_SUBNORM)); /* R1 */
    printf("log2 %a = %a\n", D_INF, log2(D_INF)); /* R1 */
    printf("log2 nan = %a\n", log2(D_NAN)); /* R1 */
    printf("log2 %a = %a\n", 1.0, log2(1.0)); /* S4 */
    printf("log2 %a = %a\n", 0.5, log2(0.5)); /* R1 */
}

static void test_log2f_branches(void)
{
    printf("log2f %a = %a\n", 0.0f, log2f(0.0f)); /* R1 */
    printf("log2f %a = %a\n", F_SUBNORM, log2f(F_SUBNORM)); /* R1 */
    printf("log2f %a = %a\n", F_INF, log2f(F_INF)); /* R1 */
    printf("log2f %a = %a\n", 0.5f, log2f(0.5f)); /* R1 */
}

static void test_log1p_branches(void)
{
    /* Branch 150: x < -1 */
    printf("log1p %a = %a\n", -2.0, log1p(-2.0)); /* R1 */
    /* Branch 155: x == -1 */
    printf("log1p %a = %a\n", -1.0, log1p(-1.0)); /* R1 */
    /* Branch 158: x is inf or NaN */
    printf("log1p %a = %a\n", D_INF, log1p(D_INF)); /* R1 */
    printf("log1p nan = %a\n", log1p(D_NAN)); /* R1 */
    /* Branch 165: |x| < 2^-29 */
    printf("log1p %a = %a\n", 0x1p-30, log1p(0x1p-30)); /* R1 */
    printf("log1p %a = %a\n", -0x1p-30, log1p(-0x1p-30)); /* R1 */
    /* Branch 173: f in different ranges */
    printf("log1p %a = %a\n", 0.5, log1p(0.5)); /* R1 */
    printf("log1p %a = %a\n", -0.5, log1p(-0.5)); /* R1 */
    /* Branch 181: k != 0, large f */
    printf("log1p %a = %a\n", 2.0, log1p(2.0)); /* R1 */
    printf("log1p %a = %a\n", -0.9, log1p(-0.9)); /* R1 */
    printf("log1p %a = %a\n", 0x1p30, log1p(0x1p30)); /* R1 */
}

static void test_log1pf_branches(void)
{
    printf("log1pf %a = %a\n", -2.0f, log1pf(-2.0f)); /* R1 */
    printf("log1pf %a = %a\n", -1.0f, log1pf(-1.0f)); /* R1 */
    printf("log1pf %a = %a\n", F_INF, log1pf(F_INF)); /* R1 */
    printf("log1pf nan = %a\n", log1pf(F_NAN)); /* R1 */
    printf("log1pf %a = %a\n", 0x1p-30f, log1pf(0x1p-30f)); /* R1 */
    printf("log1pf %a = %a\n", 0.5f, log1pf(0.5f)); /* R1 */
    printf("log1pf %a = %a\n", -0.5f, log1pf(-0.5f)); /* R1 */
    printf("log1pf %a = %a\n", 2.0f, log1pf(2.0f)); /* R1 */
    printf("log1pf %a = %a\n", -0.9f, log1pf(-0.9f)); /* R1 */
}

static void test_logb_branches(void)
{
    /* Branch 71: subnormal */
    printf("logb %a = %a\n", D_SUBNORM, logb(D_SUBNORM)); /* R1 */
    /* Branch 72: x==0 */
    printf("logb %a = %a\n", 0.0, logb(0.0)); /* R1 */
    /* Branch 76: inf or NaN */
    printf("logb %a = %a\n", D_INF, logb(D_INF)); /* R1 */
    printf("logb nan = %a\n", logb(D_NAN)); /* R1 */
    /* Branch 80: x != 0 finite */
    printf("logb %a = %a\n", 0.5, logb(0.5)); /* S4 */
    printf("logb %a = %a\n", 3.0, logb(3.0)); /* R1 */
}

static void test_logbf_branches(void)
{
    printf("logbf %a = %a\n", F_SUBNORM, logbf(F_SUBNORM)); /* R1 */
    printf("logbf %a = %a\n", 0.0f, logbf(0.0f)); /* R1 */
    printf("logbf %a = %a\n", F_INF, logbf(F_INF)); /* R1 */
    printf("logbf nan = %a\n", logbf(F_NAN)); /* R1 */
    printf("logbf %a = %a\n", 0.5f, logbf(0.5f)); /* R1 */
}

static void test_cos_branches(void)
{
    /* Branch 73: |x| < 2^-27 (returns 1) */
    printf("cos %a = %a\n", 0x1p-30, cos(0x1p-30)); /* R1 */
    printf("cos %a = %a\n", -0x1p-30, cos(-0x1p-30)); /* R1 */
    /* Branch 74: x==0 */
    printf("cos %a = %a\n", -0.0, cos(-0.0)); /* R1 */
    /* Branch 85: inf or NaN */
    printf("cos %a = %a\n", D_INF, cos(D_INF)); /* R1 */
    printf("cos %a = %a\n", D_NINF, cos(D_NINF)); /* R1 */
    printf("cos nan = %a\n", cos(D_NAN)); /* R1 */
    /* Branch 98: n&3 cases via argument reduction */
    printf("cos %a = %a\n", 2.0, cos(2.0)); /* R1 */
    printf("cos %a = %a\n", 3.14, cos(3.14)); /* R1 */
    printf("cos %a = %a\n", 5.0, cos(5.0)); /* R1 */
    printf("cos %a = %a\n", 10.0, cos(10.0)); /* R1 */
    printf("cos %a = %a\n", 100.0, cos(100.0)); /* R1 */
    printf("cos %a = %a\n", 1e8, cos(1e8)); /* R1 */
}

static void test_cosf_branches(void)
{
    /* Branch 24: |x|<2^-12 */
    printf("cosf %a = %a\n", 0x1p-14f, cosf(0x1p-14f)); /* R1 */
    printf("cosf %a = %a\n", -0x1p-14f, cosf(-0x1p-14f)); /* R1 */
    /* Branch 25: x==0 */
    printf("cosf %a = %a\n", -0.0f, cosf(-0.0f)); /* R1 */
    /* Branch 35: inf or NaN */
    printf("cosf %a = %a\n", F_INF, cosf(F_INF)); /* R1 */
    printf("cosf %a = %a\n", F_NINF, cosf(F_NINF)); /* R1 */
    printf("cosf nan = %a\n", cosf(F_NAN)); /* R1 */
    /* n&3 cases */
    printf("cosf %a = %a\n", 2.0f, cosf(2.0f)); /* R1 */
    printf("cosf %a = %a\n", 3.14f, cosf(3.14f)); /* R1 */
    printf("cosf %a = %a\n", 5.0f, cosf(5.0f)); /* R1 */
    printf("cosf %a = %a\n", 100.0f, cosf(100.0f)); /* R1 */
}

static void test_sin_branches(void)
{
    /* Branch 76: |x|<2^-26 */
    printf("sin %a = %a\n", 0x1p-30, sin(0x1p-30)); /* R1 */
    printf("sin %a = %a\n", -0x1p-30, sin(-0x1p-30)); /* R1 */
    /* Branch 75: x==0 */
    printf("sin %a = %a\n", -0.0, sin(-0.0)); /* R1 */
    /* Branch 87: inf or NaN */
    printf("sin %a = %a\n", D_INF, sin(D_INF)); /* R1 */
    printf("sin %a = %a\n", D_NINF, sin(D_NINF)); /* R1 */
    printf("sin nan = %a\n", sin(D_NAN)); /* R1 */
    /* n&3 cases via argument reduction */
    printf("sin %a = %a\n", 2.0, sin(2.0)); /* R1 */
    printf("sin %a = %a\n", 3.14, sin(3.14)); /* R1 */
    printf("sin %a = %a\n", 5.0, sin(5.0)); /* R1 */
    printf("sin %a = %a\n", 10.0, sin(10.0)); /* R1 */
    printf("sin %a = %a\n", 1e8, sin(1e8)); /* R1 */
}

static void test_sinf_branches(void)
{
    /* Branch 24: |x|<2^-12 */
    printf("sinf %a = %a\n", 0x1p-14f, sinf(0x1p-14f)); /* R1 */
    printf("sinf %a = %a\n", -0x1p-14f, sinf(-0x1p-14f)); /* R1 */
    /* Branch 25: x==0 */
    printf("sinf %a = %a\n", -0.0f, sinf(-0.0f)); /* R1 */
    /* Branch 35: inf or NaN */
    printf("sinf %a = %a\n", F_INF, sinf(F_INF)); /* R1 */
    printf("sinf %a = %a\n", F_NINF, sinf(F_NINF)); /* R1 */
    printf("sinf nan = %a\n", sinf(F_NAN)); /* R1 */
    /* n&3 cases */
    printf("sinf %a = %a\n", 2.0f, sinf(2.0f)); /* R1 */
    printf("sinf %a = %a\n", 3.14f, sinf(3.14f)); /* R1 */
    printf("sinf %a = %a\n", 5.0f, sinf(5.0f)); /* R1 */
    printf("sinf %a = %a\n", 100.0f, sinf(100.0f)); /* R1 */
}

static void test_tan_branches(void)
{
    /* Branch 98-99: NaN and large */
    printf("tan %a = %a\n", D_INF, tan(D_INF)); /* R1 */
    printf("tan nan = %a\n", tan(D_NAN)); /* R1 */
    printf("tan %a = %a\n", 0x1p-30, tan(0x1p-30)); /* R1 */
    printf("tan %a = %a\n", -0.0, tan(-0.0)); /* R1 */
    printf("tan %a = %a\n", 2.0, tan(2.0)); /* R1 */
    printf("tan %a = %a\n", 3.14, tan(3.14)); /* R1 */
    printf("tan %a = %a\n", 5.0, tan(5.0)); /* R1 */
    printf("tan %a = %a\n", 10.0, tan(10.0)); /* R1 */
    printf("tan %a = %a\n", 1e8, tan(1e8)); /* R1 */
}

static void test_tanf_branches(void)
{
    printf("tanf %a = %a\n", F_INF, tanf(F_INF)); /* R1 */
    printf("tanf nan = %a\n", tanf(F_NAN)); /* R1 */
    printf("tanf %a = %a\n", 0x1p-30f, tanf(0x1p-30f)); /* R1 */
    printf("tanf %a = %a\n", -0.0f, tanf(-0.0f)); /* R1 */
    printf("tanf %a = %a\n", 2.0f, tanf(2.0f)); /* R1 */
    printf("tanf %a = %a\n", 3.14f, tanf(3.14f)); /* R1 */
    printf("tanf %a = %a\n", 5.0f, tanf(5.0f)); /* R1 */
    printf("tanf %a = %a\n", 100.0f, tanf(100.0f)); /* R1 */
    /* Branch 99: n&3 case 1 */
    printf("tanf %a = %a\n", -2.0f, tanf(-2.0f)); /* R1 */
    printf("tanf %a = %a\n", -3.14f, tanf(-3.14f)); /* R1 */
}

static void test_ceil_branches(void)
{
    /* ceild.c branches 68-119 */
    printf("ceil %a = %a\n", 0.0, ceil(0.0)); /* R1 */
    printf("ceil %a = %a\n", -0.0, ceil(-0.0)); /* R1 */
    printf("ceil %a = %a\n", 0x1p-60, ceil(0x1p-60)); /* R1 */
    printf("ceil %a = %a\n", -0x1p-60, ceil(-0x1p-60)); /* R1 */
    printf("ceil %a = %a\n", D_INF, ceil(D_INF)); /* R1 */
    printf("ceil %a = %a\n", D_NINF, ceil(D_NINF)); /* R1 */
    printf("ceil nan = %a\n", ceil(D_NAN)); /* R1 */
    printf("ceil %a = %a\n", 0x1p51, ceil(0x1p51)); /* R1 */
    printf("ceil %a = %a\n", -0x1p51, ceil(-0x1p51)); /* R1 */
    printf("ceil %a = %a\n", 0x1p52, ceil(0x1p52)); /* R1 */
    printf("ceil %a = %a\n", 1.5, ceil(1.5)); /* R1 */
    printf("ceil %a = %a\n", -1.5, ceil(-1.5)); /* R1 */
    printf("ceil %a = %a\n", -0.5, ceil(-0.5)); /* R1 */
    printf("ceil %a = %a\n", 0.5, ceil(0.5)); /* R1 */
    printf("ceil %a = %a\n", 1e15, ceil(1e15)); /* R1 */
    printf("ceil %a = %a\n", -1e15, ceil(-1e15)); /* R1 */
}

static void test_ceilf_branches(void)
{
    printf("ceilf %a = %a\n", 0.0f, ceilf(0.0f)); /* R1 */
    printf("ceilf %a = %a\n", -0.0f, ceilf(-0.0f)); /* R1 */
    printf("ceilf %a = %a\n", 0x1p-30f, ceilf(0x1p-30f)); /* R1 */
    printf("ceilf %a = %a\n", -0x1p-30f, ceilf(-0x1p-30f)); /* R1 */
    printf("ceilf %a = %a\n", F_INF, ceilf(F_INF)); /* R1 */
    printf("ceilf nan = %a\n", ceilf(F_NAN)); /* R1 */
    printf("ceilf %a = %a\n", 0x1p23f, ceilf(0x1p23f)); /* R1 */
    printf("ceilf %a = %a\n", -0x1p23f, ceilf(-0x1p23f)); /* R1 */
    printf("ceilf %a = %a\n", 1.5f, ceilf(1.5f)); /* R1 */
    printf("ceilf %a = %a\n", -1.5f, ceilf(-1.5f)); /* R1 */
    printf("ceilf %a = %a\n", 1e7f, ceilf(1e7f)); /* R1 */
}

static void test_floor_branches(void)
{
    printf("floor %a = %a\n", 0.0, floor(0.0)); /* R1 */
    printf("floor %a = %a\n", -0.0, floor(-0.0)); /* R1 */
    printf("floor %a = %a\n", 0x1p-60, floor(0x1p-60)); /* R1 */
    printf("floor %a = %a\n", -0x1p-60, floor(-0x1p-60)); /* R1 */
    printf("floor %a = %a\n", D_INF, floor(D_INF)); /* R1 */
    printf("floor %a = %a\n", D_NINF, floor(D_NINF)); /* R1 */
    printf("floor nan = %a\n", floor(D_NAN)); /* R1 */
    printf("floor %a = %a\n", 0x1p51, floor(0x1p51)); /* R1 */
    printf("floor %a = %a\n", -0x1p51, floor(-0x1p51)); /* R1 */
    printf("floor %a = %a\n", 1.5, floor(1.5)); /* R1 */
    printf("floor %a = %a\n", -1.5, floor(-1.5)); /* R1 */
    printf("floor %a = %a\n", 1e15, floor(1e15)); /* R1 */
    printf("floor %a = %a\n", -1e15, floor(-1e15)); /* R1 */
}

static void test_floorf_branches(void)
{
    printf("floorf %a = %a\n", 0.0f, floorf(0.0f)); /* R1 */
    printf("floorf %a = %a\n", -0.0f, floorf(-0.0f)); /* R1 */
    printf("floorf %a = %a\n", 0x1p-30f, floorf(0x1p-30f)); /* R1 */
    printf("floorf %a = %a\n", -0x1p-30f, floorf(-0x1p-30f)); /* R1 */
    printf("floorf %a = %a\n", F_INF, floorf(F_INF)); /* R1 */
    printf("floorf nan = %a\n", floorf(F_NAN)); /* R1 */
    printf("floorf %a = %a\n", 0x1p23f, floorf(0x1p23f)); /* R1 */
    printf("floorf %a = %a\n", 1.5f, floorf(1.5f)); /* R1 */
    printf("floorf %a = %a\n", -1.5f, floorf(-1.5f)); /* R1 */
    printf("floorf %a = %a\n", 1e7f, floorf(1e7f)); /* R1 */
}

static void test_trunc_branches(void)
{
    printf("trunc %a = %a\n", 0.0, trunc(0.0)); /* R1 */
    printf("trunc %a = %a\n", -0.0, trunc(-0.0)); /* R1 */
    printf("trunc %a = %a\n", 0x1p-60, trunc(0x1p-60)); /* R1 */
    printf("trunc %a = %a\n", -0x1p-60, trunc(-0x1p-60)); /* R1 */
    printf("trunc %a = %a\n", D_INF, trunc(D_INF)); /* R1 */
    printf("trunc nan = %a\n", trunc(D_NAN)); /* R1 */
    printf("trunc %a = %a\n", 1.5, trunc(1.5)); /* R1 */
    printf("trunc %a = %a\n", -1.5, trunc(-1.5)); /* R1 */
    printf("trunc %a = %a\n", 0x1p51, trunc(0x1p51)); /* R1 */
}

static void test_truncf_branches(void)
{
    printf("truncf %a = %a\n", 0.0f, truncf(0.0f)); /* R1 */
    printf("truncf %a = %a\n", -0.0f, truncf(-0.0f)); /* R1 */
    printf("truncf %a = %a\n", 0x1p-30f, truncf(0x1p-30f)); /* R1 */
    printf("truncf %a = %a\n", F_INF, truncf(F_INF)); /* R1 */
    printf("truncf nan = %a\n", truncf(F_NAN)); /* R1 */
    printf("truncf %a = %a\n", 1.5f, truncf(1.5f)); /* R1 */
    printf("truncf %a = %a\n", -1.5f, truncf(-1.5f)); /* R1 */
    printf("truncf %a = %a\n", 0x1p23f, truncf(0x1p23f)); /* R1 */
}

static void test_rint_branches(void)
{
    printf("rint %a = %a\n", 0.0, rint(0.0)); /* R1 */
    printf("rint %a = %a\n", -0.0, rint(-0.0)); /* R1 */
    printf("rint %a = %a\n", 0x1p-60, rint(0x1p-60)); /* R1 */
    printf("rint %a = %a\n", -0x1p-60, rint(-0x1p-60)); /* R1 */
    printf("rint %a = %a\n", D_INF, rint(D_INF)); /* R1 */
    printf("rint nan = %a\n", rint(D_NAN)); /* R1 */
    printf("rint %a = %a\n", 1.5, rint(1.5)); /* S4 */
    printf("rint %a = %a\n", -1.5, rint(-1.5)); /* S4 */
    printf("rint %a = %a\n", 2.5, rint(2.5)); /* R1 */
    printf("rint %a = %a\n", -2.5, rint(-2.5)); /* R1 */
    printf("rint %a = %a\n", 0x1p52, rint(0x1p52)); /* R1 */
}

static void test_rintf_branches(void)
{
    printf("rintf %a = %a\n", 0.0f, rintf(0.0f)); /* R1 */
    printf("rintf %a = %a\n", -0.0f, rintf(-0.0f)); /* R1 */
    printf("rintf %a = %a\n", 0x1p-30f, rintf(0x1p-30f)); /* R1 */
    printf("rintf %a = %a\n", F_INF, rintf(F_INF)); /* R1 */
    printf("rintf nan = %a\n", rintf(F_NAN)); /* R1 */
    printf("rintf %a = %a\n", 1.5f, rintf(1.5f)); /* S4 */
    printf("rintf %a = %a\n", -1.5f, rintf(-1.5f)); /* S4 */
    printf("rintf %a = %a\n", 2.5f, rintf(2.5f)); /* R1 */
    printf("rintf %a = %a\n", 0x1p23f, rintf(0x1p23f)); /* R1 */
}

static void test_round_branches(void)
{
    printf("round %a = %a\n", 0.0, round(0.0)); /* R1 */
    printf("round %a = %a\n", -0.0, round(-0.0)); /* R1 */
    printf("round %a = %a\n", 0x1p-60, round(0x1p-60)); /* R1 */
    printf("round %a = %a\n", -0x1p-60, round(-0x1p-60)); /* R1 */
    printf("round %a = %a\n", D_INF, round(D_INF)); /* R1 */
    printf("round nan = %a\n", round(D_NAN)); /* R1 */
    printf("round %a = %a\n", 1.4, round(1.4)); /* R1 */
    printf("round %a = %a\n", -1.4, round(-1.4)); /* R1 */
    printf("round %a = %a\n", 0x1p51, round(0x1p51)); /* R1 */
    printf("round %a = %a\n", -0x1p51, round(-0x1p51)); /* R1 */
}

static void test_roundf_branches(void)
{
    printf("roundf %a = %a\n", 0.0f, roundf(0.0f)); /* R1 */
    printf("roundf %a = %a\n", -0.0f, roundf(-0.0f)); /* R1 */
    printf("roundf %a = %a\n", 0x1p-30f, roundf(0x1p-30f)); /* R1 */
    printf("roundf %a = %a\n", F_INF, roundf(F_INF)); /* R1 */
    printf("roundf nan = %a\n", roundf(F_NAN)); /* R1 */
    printf("roundf %a = %a\n", 1.4f, roundf(1.4f)); /* R1 */
    printf("roundf %a = %a\n", -1.4f, roundf(-1.4f)); /* R1 */
    printf("roundf %a = %a\n", 0x1p23f, roundf(0x1p23f)); /* R1 */
}

static void test_lrint_branches(void)
{
    printf("lrint %a = %ld\n", D_INF, lrint(D_INF)); /* R1 */
    printf("lrint %a = %ld\n", D_NAN, lrint(D_NAN)); /* R1 */
    printf("lrint %a = %ld\n", 0x1p60, lrint(0x1p60)); /* R1 */
    printf("lrint %a = %ld\n", -0x1p60, lrint(-0x1p60)); /* R1 */
    printf("lrint %a = %ld\n", 0.0, lrint(0.0)); /* R1 */
    printf("lrint %a = %ld\n", -0.0, lrint(-0.0)); /* R1 */
    printf("lrint %a = %ld\n", 0.5, lrint(0.5)); /* R1 */
    printf("lrint %a = %ld\n", -0.5, lrint(-0.5)); /* R1 */
}

static void test_lrintf_branches(void)
{
    printf("lrintf %a = %ld\n", F_INF, lrintf(F_INF)); /* R1 */
    printf("lrintf %a = %ld\n", F_NAN, lrintf(F_NAN)); /* R1 */
    printf("lrintf %a = %ld\n", 0x1p30f, lrintf(0x1p30f)); /* R1 */
    printf("lrintf %a = %ld\n", -0x1p30f, lrintf(-0x1p30f)); /* R1 */
    printf("lrintf %a = %ld\n", 0.5f, lrintf(0.5f)); /* R1 */
    printf("lrintf %a = %ld\n", -0.5f, lrintf(-0.5f)); /* R1 */
}

static void test_llrint_branches(void)
{
    printf("llrint %a = %lld\n", D_INF, llrint(D_INF)); /* R1 */
    printf("llrint %a = %lld\n", D_NAN, llrint(D_NAN)); /* R1 */
    printf("llrint %a = %lld\n", 0x1p62, llrint(0x1p62)); /* R1 */
    printf("llrint %a = %lld\n", -0x1p62, llrint(-0x1p62)); /* R1 */
    printf("llrint %a = %lld\n", 0.0, llrint(0.0)); /* R1 */
    printf("llrint %a = %lld\n", 0.5, llrint(0.5)); /* R1 */
    printf("llrint %a = %lld\n", -0.5, llrint(-0.5)); /* R1 */
}

static void test_llrintf_branches(void)
{
    printf("llrintf %a = %lld\n", F_INF, llrintf(F_INF)); /* R1 */
    printf("llrintf %a = %lld\n", F_NAN, llrintf(F_NAN)); /* R1 */
    printf("llrintf %a = %lld\n", 0x1p30f, llrintf(0x1p30f)); /* R1 */
    printf("llrintf %a = %lld\n", 0.5f, llrintf(0.5f)); /* R1 */
    printf("llrintf %a = %lld\n", -0.5f, llrintf(-0.5f)); /* R1 */
}

static void test_lround_branches(void)
{
    printf("lround %a = %ld\n", D_INF, lround(D_INF)); /* R1 */
    printf("lround %a = %ld\n", D_NAN, lround(D_NAN)); /* R1 */
    printf("lround %a = %ld\n", 0x1p60, lround(0x1p60)); /* R1 */
    printf("lround %a = %ld\n", 0.0, lround(0.0)); /* R1 */
    printf("lround %a = %ld\n", -0.0, lround(-0.0)); /* R1 */
    printf("lround %a = %ld\n", 0.4, lround(0.4)); /* R1 */
    printf("lround %a = %ld\n", -0.4, lround(-0.4)); /* R1 */
}

static void test_lroundf_branches(void)
{
    printf("lroundf %a = %ld\n", F_INF, lroundf(F_INF)); /* R1 */
    printf("lroundf %a = %ld\n", F_NAN, lroundf(F_NAN)); /* R1 */
    printf("lroundf %a = %ld\n", 0x1p30f, lroundf(0x1p30f)); /* R1 */
    printf("lroundf %a = %ld\n", 0.4f, lroundf(0.4f)); /* R1 */
    printf("lroundf %a = %ld\n", -0.4f, lroundf(-0.4f)); /* R1 */
}

static void test_llround_branches(void)
{
    printf("llround %a = %lld\n", D_INF, llround(D_INF)); /* R1 */
    printf("llround %a = %lld\n", D_NAN, llround(D_NAN)); /* R1 */
    printf("llround %a = %lld\n", 0x1p62, llround(0x1p62)); /* R1 */
    printf("llround %a = %lld\n", 0.0, llround(0.0)); /* R1 */
    printf("llround %a = %lld\n", 0.4, llround(0.4)); /* R1 */
    printf("llround %a = %lld\n", -0.4, llround(-0.4)); /* R1 */
}

static void test_llroundf_branches(void)
{
    printf("llroundf %a = %lld\n", F_INF, llroundf(F_INF)); /* R1 */
    printf("llroundf %a = %lld\n", F_NAN, llroundf(F_NAN)); /* R1 */
    printf("llroundf %a = %lld\n", 0x1p30f, llroundf(0x1p30f)); /* R1 */
    printf("llroundf %a = %lld\n", 0.4f, llroundf(0.4f)); /* R1 */
    printf("llroundf %a = %lld\n", -0.4f, llroundf(-0.4f)); /* R1 */
}

static void test_fmax_branches(void)
{
    /* Branch 75: x is NaN */
    printf("fmax nan 1 = %a\n", fmax(D_NAN, 1.0)); /* R1 */
    printf("fmax nan nan = %a\n", fmax(D_NAN, D_NAN)); /* R1 */
    /* Branch 85: y is NaN */
    printf("fmax 1 nan = %a\n", fmax(1.0, D_NAN)); /* R1 */
    /* Branch 99: x>y vs x<=y */
    printf("fmax %a %a = %a\n", 3.0, 2.0, fmax(3.0, 2.0)); /* S4 */
    printf("fmax %a %a = %a\n", 2.0, 3.0, fmax(2.0, 3.0)); /* R1 */
    printf("fmax %a %a = %a\n", -0.0, 0.0, fmax(-0.0, 0.0)); /* R1 */
    printf("fmax %a %a = %a\n", 0.0, -0.0, fmax(0.0, -0.0)); /* R1 */
    printf("fmax %a %a = %a\n", D_INF, 1.0, fmax(D_INF, 1.0)); /* R1 */
    printf("fmax %a %a = %a\n", D_NINF, 1.0, fmax(D_NINF, 1.0)); /* R1 */
}

static void test_fmaxf_branches(void)
{
    /* Branch 10: x is NaN */
    printf("fmaxf nan 1 = %a\n", fmaxf(F_NAN, 1.0f)); /* R1 */
    printf("fmaxf nan nan = %a\n", fmaxf(F_NAN, F_NAN)); /* R1 */
    /* Branch 20: y is NaN */
    printf("fmaxf 1 nan = %a\n", fmaxf(1.0f, F_NAN)); /* R1 */
    /* Branch 34: x>y vs x<=y */
    printf("fmaxf %a %a = %a\n", 3.0f, 2.0f, fmaxf(3.0f, 2.0f)); /* S4 */
    printf("fmaxf %a %a = %a\n", 2.0f, 3.0f, fmaxf(2.0f, 3.0f)); /* R1 */
    printf("fmaxf %a %a = %a\n", F_INF, 1.0f, fmaxf(F_INF, 1.0f)); /* R1 */
    printf("fmaxf %a %a = %a\n", F_NINF, 1.0f, fmaxf(F_NINF, 1.0f)); /* R1 */
}

static void test_fmin_branches(void)
{
    /* Branch 75: x is NaN */
    printf("fmin nan 1 = %a\n", fmin(D_NAN, 1.0)); /* R1 */
    printf("fmin nan nan = %a\n", fmin(D_NAN, D_NAN)); /* R1 */
    /* Branch 85: y is NaN */
    printf("fmin 1 nan = %a\n", fmin(1.0, D_NAN)); /* R1 */
    /* Branch 99: x<y vs x>=y */
    printf("fmin %a %a = %a\n", 3.0, 2.0, fmin(3.0, 2.0)); /* S4 */
    printf("fmin %a %a = %a\n", 2.0, 3.0, fmin(2.0, 3.0)); /* R1 */
    printf("fmin %a %a = %a\n", D_INF, 1.0, fmin(D_INF, 1.0)); /* R1 */
    printf("fmin %a %a = %a\n", D_NINF, 1.0, fmin(D_NINF, 1.0)); /* R1 */
}

static void test_fminf_branches(void)
{
    printf("fminf nan 1 = %a\n", fminf(F_NAN, 1.0f)); /* R1 */
    printf("fminf nan nan = %a\n", fminf(F_NAN, F_NAN)); /* R1 */
    printf("fminf 1 nan = %a\n", fminf(1.0f, F_NAN)); /* R1 */
    printf("fminf %a %a = %a\n", 3.0f, 2.0f, fminf(3.0f, 2.0f)); /* S4 */
    printf("fminf %a %a = %a\n", 2.0f, 3.0f, fminf(2.0f, 3.0f)); /* R1 */
    printf("fminf %a %a = %a\n", F_INF, 1.0f, fminf(F_INF, 1.0f)); /* R1 */
}

static void test_fpclassify_branches(void)
{
    /* fpclassifyd: NaN, subnormal, inf */
    printf("__fpclassifyd nan = %d\n", __fpclassifyd(D_NAN)); /* R1 */
    printf("__fpclassifyd -nan = %d\n", __fpclassifyd(-D_NAN)); /* R1 */
    printf("__fpclassifyd subnorm = %d\n", __fpclassifyd(D_SUBNORM)); /* R1 */
    printf("__fpclassifyd -subnorm = %d\n", __fpclassifyd(-D_SUBNORM)); /* R1 */
    printf("__fpclassifyd -inf = %d\n", __fpclassifyd(D_NINF)); /* R1 */
    printf("__fpclassifyd -0 = %d\n", __fpclassifyd(-0.0)); /* R1 */
    /* fpclassifyf */
    printf("__fpclassifyf nan = %d\n", __fpclassifyf(F_NAN)); /* R1 */
    printf("__fpclassifyf subnorm = %d\n", __fpclassifyf(F_SUBNORM)); /* R1 */
    printf("__fpclassifyf -inf = %d\n", __fpclassifyf(F_NINF)); /* R1 */
    printf("__fpclassifyf -0 = %d\n", __fpclassifyf(-0.0f)); /* R1 */
}

static void test_frexp_branches(void)
{
    int e;
    double m;
    /* Branch 84: x==0 or subnormal */
    m = frexp(0.0, &e);
    printf("frexp %a = %a exp %d\n", 0.0, m, e); /* S4 */
    m = frexp(-0.0, &e);
    printf("frexp %a = %a exp %d\n", -0.0, m, e); /* R1 */
    m = frexp(D_SUBNORM, &e);
    printf("frexp %a = %a exp %d\n", D_SUBNORM, m, e); /* R1 */
    /* Branch 85: inf or NaN */
    m = frexp(D_INF, &e);
    printf("frexp inf = %a exp %d\n", m, e); /* R1 */
    m = frexp(D_NAN, &e);
    printf("frexp nan = %a exp %d\n", m, e); /* R1 */
    /* Branch 93: subnormal normalization */
    m = frexp(0x1p-1050, &e);
    printf("frexp %a = %a exp %d\n", 0x1p-1050, m, e); /* R1 */
    /* Branch 97: negative */
    m = frexp(-2.0, &e);
    printf("frexp %a = %a exp %d\n", -2.0, m, e); /* R1 */
}

static void test_frexpf_branches(void)
{
    int e;
    float m;
    m = frexpf(0.0f, &e);
    printf("frexpf %a = %a exp %d\n", 0.0f, m, e); /* R1 */
    m = frexpf(-0.0f, &e);
    printf("frexpf %a = %a exp %d\n", -0.0f, m, e); /* R1 */
    m = frexpf(F_SUBNORM, &e);
    printf("frexpf %a = %a exp %d\n", F_SUBNORM, m, e); /* R1 */
    m = frexpf(F_INF, &e);
    printf("frexpf inf = %a exp %d\n", m, e); /* R1 */
    m = frexpf(F_NAN, &e);
    printf("frexpf nan = %a exp %d\n", m, e); /* R1 */
    m = frexpf(0x1p-130f, &e);
    printf("frexpf %a = %a exp %d\n", 0x1p-130f, m, e); /* R1 */
    m = frexpf(-2.0f, &e);
    printf("frexpf %a = %a exp %d\n", -2.0f, m, e); /* R1 */
}

static void test_modf_branches(void)
{
    double ipart;
    double f;
    f = modf(0.0, &ipart);
    printf("modf %a = %a ipart %a\n", 0.0, f, ipart); /* R1 */
    f = modf(-0.0, &ipart);
    printf("modf %a = %a ipart %a\n", -0.0, f, ipart); /* R1 */
    f = modf(D_INF, &ipart);
    printf("modf inf = %a ipart %a\n", f, ipart); /* R1 */
    f = modf(D_NINF, &ipart);
    printf("modf -inf = %a ipart %a\n", f, ipart); /* R1 */
    f = modf(D_NAN, &ipart);
    printf("modf nan = %a ipart %a\n", f, ipart); /* R1 */
    f = modf(0x1p53, &ipart);
    printf("modf %a = %a ipart %a\n", 0x1p53, f, ipart); /* R1 */
    f = modf(-0x1p53, &ipart);
    printf("modf %a = %a ipart %a\n", -0x1p53, f, ipart); /* R1 */
    f = modf(0.5, &ipart);
    printf("modf %a = %a ipart %a\n", 0.5, f, ipart); /* R1 */
    f = modf(-0.5, &ipart);
    printf("modf %a = %a ipart %a\n", -0.5, f, ipart); /* R1 */
}

static void test_modff_branches(void)
{
    float ipart;
    float f;
    f = modff(0.0f, &ipart);
    printf("modff %a = %a ipart %a\n", 0.0f, f, ipart); /* R1 */
    f = modff(-0.0f, &ipart);
    printf("modff %a = %a ipart %a\n", -0.0f, f, ipart); /* R1 */
    f = modff(F_INF, &ipart);
    printf("modff inf = %a ipart %a\n", f, ipart); /* R1 */
    f = modff(F_NAN, &ipart);
    printf("modff nan = %a ipart %a\n", f, ipart); /* R1 */
    f = modff(0x1p24f, &ipart);
    printf("modff %a = %a ipart %a\n", 0x1p24f, f, ipart); /* R1 */
    f = modff(0.5f, &ipart);
    printf("modff %a = %a ipart %a\n", 0.5f, f, ipart); /* R1 */
    f = modff(-0.5f, &ipart);
    printf("modff %a = %a ipart %a\n", -0.5f, f, ipart); /* R1 */
}

static void test_nextafter_branches(void)
{
    /* Branch 90-92: NaN, x==y */
    printf("nextafter nan 1 = %a\n", nextafter(D_NAN, 1.0)); /* R1 */
    printf("nextafter 1 nan = %a\n", nextafter(1.0, D_NAN)); /* R1 */
    printf("nextafter %a %a = %a\n", 1.0, 1.0, nextafter(1.0, 1.0)); /* S4 */
    /* Branch 94: x==0 */
    printf("nextafter %a %a = %a\n", 0.0, 1.0, nextafter(0.0, 1.0)); /* S4 */
    printf("nextafter %a %a = %a\n", 0.0, -1.0, nextafter(0.0, -1.0)); /* R1 */
    printf("nextafter %a %a = %a\n", -0.0, 1.0, nextafter(-0.0, 1.0)); /* R1 */
    printf("nextafter %a %a = %a\n", -0.0, -1.0, nextafter(-0.0, -1.0)); /* R1 */
    /* Branch 105: x>0, x>y */
    printf("nextafter %a %a = %a\n", 2.0, 1.0, nextafter(2.0, 1.0)); /* R1 */
    printf("nextafter %a %a = %a\n", 1.0, 2.0, nextafter(1.0, 2.0)); /* R1 */
    /* Branch 120: x<0 */
    printf("nextafter %a %a = %a\n", -2.0, -1.0, nextafter(-2.0, -1.0)); /* R1 */
    printf("nextafter %a %a = %a\n", -1.0, -2.0, nextafter(-1.0, -2.0)); /* R1 */
    /* overflow */
    printf("nextafter %a %a = %a\n", 0x1.fffffffffffffp+1023, D_INF, nextafter(0x1.fffffffffffffp+1023, D_INF)); /* R1 */
    /* underflow subnorm */
    printf("nextafter %a %a = %a\n", D_SUBNORM, 0.0, nextafter(D_SUBNORM, 0.0)); /* R1 */
}

static void test_nextafterf_branches(void)
{
    printf("nextafterf nan 1 = %a\n", nextafterf(F_NAN, 1.0f)); /* R1 */
    printf("nextafterf 1 nan = %a\n", nextafterf(1.0f, F_NAN)); /* R1 */
    printf("nextafterf %a %a = %a\n", 1.0f, 1.0f, nextafterf(1.0f, 1.0f)); /* R1 */
    printf("nextafterf %a %a = %a\n", 0.0f, 1.0f, nextafterf(0.0f, 1.0f)); /* S4 */
    printf("nextafterf %a %a = %a\n", 0.0f, -1.0f, nextafterf(0.0f, -1.0f)); /* R1 */
    printf("nextafterf %a %a = %a\n", 2.0f, 1.0f, nextafterf(2.0f, 1.0f)); /* R1 */
    printf("nextafterf %a %a = %a\n", 1.0f, 2.0f, nextafterf(1.0f, 2.0f)); /* R1 */
    printf("nextafterf %a %a = %a\n", -2.0f, -1.0f, nextafterf(-2.0f, -1.0f)); /* R1 */
    printf("nextafterf %a %a = %a\n", F_SUBNORM, 0.0f, nextafterf(F_SUBNORM, 0.0f)); /* R1 */
}

static void test_scalbn_branches(void)
{
    /* Branch 96: subnormal input */
    printf("scalbn %a %d = %a\n", D_SUBNORM, 1, scalbn(D_SUBNORM, 1)); /* R1 */
    printf("scalbn %a %d = %a\n", D_SUBNORM, 1074, scalbn(D_SUBNORM, 1074)); /* R1 */
    /* Branch 97: x==0, inf, nan */
    printf("scalbn %a %d = %a\n", 0.0, 5, scalbn(0.0, 5)); /* R1 */
    printf("scalbn %a %d = %a\n", D_INF, 5, scalbn(D_INF, 5)); /* R1 */
    printf("scalbn nan %d = %a\n", 5, scalbn(D_NAN, 5)); /* R1 */
    /* Branch 105: large k */
    printf("scalbn %a %d = %a\n", 1.0, 2000, scalbn(1.0, 2000)); /* R1 */
    printf("scalbn %a %d = %a\n", 1.0, -2000, scalbn(1.0, -2000)); /* R1 */
    printf("scalbn %a %d = %a\n", 1.0, 600, scalbn(1.0, 600)); /* R1 */
    printf("scalbn %a %d = %a\n", 1.0, -600, scalbn(1.0, -600)); /* R1 */
    printf("scalbn %a %d = %a\n", 1.0, 100, scalbn(1.0, 100)); /* R1 */
    printf("scalbn %a %d = %a\n", 1.0, -100, scalbn(1.0, -100)); /* R1 */
}

static void test_scalbnf_branches(void)
{
    printf("scalbnf %a %d = %a\n", F_SUBNORM, 1, scalbnf(F_SUBNORM, 1)); /* R1 */
    printf("scalbnf %a %d = %a\n", 0.0f, 5, scalbnf(0.0f, 5)); /* R1 */
    printf("scalbnf %a %d = %a\n", F_INF, 5, scalbnf(F_INF, 5)); /* R1 */
    printf("scalbnf nan %d = %a\n", 5, scalbnf(F_NAN, 5)); /* R1 */
    printf("scalbnf %a %d = %a\n", 1.0f, 200, scalbnf(1.0f, 200)); /* R1 */
    printf("scalbnf %a %d = %a\n", 1.0f, -200, scalbnf(1.0f, -200)); /* R1 */
    printf("scalbnf %a %d = %a\n", 1.0f, 100, scalbnf(1.0f, 100)); /* R1 */
    printf("scalbnf %a %d = %a\n", 1.0f, -100, scalbnf(1.0f, -100)); /* R1 */
}

static void test_scalbln_branches(void)
{
    printf("scalbln %a %ld = %a\n", 1.0, 2000L, scalbln(1.0, 2000L)); /* R1 */
    printf("scalbln %a %ld = %a\n", 1.0, -2000L, scalbln(1.0, -2000L)); /* R1 */
    printf("scalbln %a %ld = %a\n", 1.0, 600L, scalbln(1.0, 600L)); /* R1 */
    printf("scalbln %a %ld = %a\n", 1.0, -600L, scalbln(1.0, -600L)); /* R1 */
    printf("scalbln %a %ld = %a\n", 0.0, 5L, scalbln(0.0, 5L)); /* R1 */
    printf("scalbln %a %ld = %a\n", D_INF, 5L, scalbln(D_INF, 5L)); /* R1 */
    printf("scalbln %a %ld = %a\n", D_SUBNORM, 1L, scalbln(D_SUBNORM, 1L)); /* R1 */
}

static void test_scalblnf_branches(void)
{
    printf("scalblnf %a %ld = %a\n", 1.0f, 200L, scalblnf(1.0f, 200L)); /* R1 */
    printf("scalblnf %a %ld = %a\n", 1.0f, -200L, scalblnf(1.0f, -200L)); /* R1 */
    printf("scalblnf %a %ld = %a\n", 1.0f, 100L, scalblnf(1.0f, 100L)); /* R1 */
    printf("scalblnf %a %ld = %a\n", 0.0f, 5L, scalblnf(0.0f, 5L)); /* R1 */
    printf("scalblnf %a %ld = %a\n", F_INF, 5L, scalblnf(F_INF, 5L)); /* R1 */
    printf("scalblnf %a %ld = %a\n", F_SUBNORM, 1L, scalblnf(F_SUBNORM, 1L)); /* R1 */
}

static void test_ldexp_branches(void)
{
    /* ldexpd.c: subnormal, special */
    printf("ldexp %a %d = %a\n", D_SUBNORM, 1, ldexp(D_SUBNORM, 1)); /* R1 */
    printf("ldexp %a %d = %a\n", 0.0, 5, ldexp(0.0, 5)); /* R1 */
    printf("ldexp %a %d = %a\n", D_INF, 5, ldexp(D_INF, 5)); /* R1 */
    printf("ldexp nan %d = %a\n", 5, ldexp(D_NAN, 5)); /* R1 */
    printf("ldexp %a %d = %a\n", 1.0, 2000, ldexp(1.0, 2000)); /* R1 */
    printf("ldexp %a %d = %a\n", 1.0, -2000, ldexp(1.0, -2000)); /* R1 */
}

static void test_ldexpf_branches(void)
{
    printf("ldexpf %a %d = %a\n", F_SUBNORM, 1, ldexpf(F_SUBNORM, 1)); /* R1 */
    printf("ldexpf %a %d = %a\n", 0.0f, 5, ldexpf(0.0f, 5)); /* R1 */
    printf("ldexpf %a %d = %a\n", F_INF, 5, ldexpf(F_INF, 5)); /* R1 */
    printf("ldexpf %a %d = %a\n", 1.0f, 200, ldexpf(1.0f, 200)); /* R1 */
    printf("ldexpf %a %d = %a\n", 1.0f, -200, ldexpf(1.0f, -200)); /* R1 */
}

static void test_ilogb_branches(void)
{
    /* ilogbd.c: 0, subnormal, inf, nan */
    printf("ilogb %a = %d\n", 0.0, ilogb(0.0)); /* R1 */
    printf("ilogb %a = %d\n", D_INF, ilogb(D_INF)); /* R1 */
    printf("ilogb %a = %d\n", D_NINF, ilogb(D_NINF)); /* R1 */
    printf("ilogb nan = %d\n", ilogb(D_NAN)); /* R1 */
    printf("ilogb %a = %d\n", D_SUBNORM, ilogb(D_SUBNORM)); /* R1 */
    printf("ilogb %a = %d\n", -1.0, ilogb(-1.0)); /* R1 */
    printf("ilogb %a = %d\n", 0x1p-1022, ilogb(0x1p-1022)); /* R1 */
}

static void test_ilogbf_branches(void)
{
    printf("ilogbf %a = %d\n", 0.0f, ilogbf(0.0f)); /* R1 */
    printf("ilogbf %a = %d\n", F_INF, ilogbf(F_INF)); /* R1 */
    printf("ilogbf nan = %d\n", ilogbf(F_NAN)); /* R1 */
    printf("ilogbf %a = %d\n", F_SUBNORM, ilogbf(F_SUBNORM)); /* R1 */
    printf("ilogbf %a = %d\n", -1.0f, ilogbf(-1.0f)); /* R1 */
}

static void test_hypot_branches(void)
{
    /* hypotd.c: inf, nan, large */
    printf("hypot %a %a = %a\n", D_INF, 1.0, hypot(D_INF, 1.0)); /* R1 */
    printf("hypot %a %a = %a\n", 1.0, D_INF, hypot(1.0, D_INF)); /* R1 */
    printf("hypot %a %a = %a\n", D_NINF, 1.0, hypot(D_NINF, 1.0)); /* R1 */
    printf("hypot nan %a = %a\n", 1.0, hypot(D_NAN, 1.0)); /* R1 */
    printf("hypot %a nan = %a\n", 1.0, hypot(1.0, D_NAN)); /* R1 */
    printf("hypot %a %a = %a\n", D_SUBNORM, 0.0, hypot(D_SUBNORM, 0.0)); /* R1 */
    printf("hypot %a %a = %a\n", 0x1p600, 1.0, hypot(0x1p600, 1.0)); /* R1 */
    printf("hypot %a %a = %a\n", 0x1p-600, 1.0, hypot(0x1p-600, 1.0)); /* R1 */
}

static void test_hypotf_branches(void)
{
    printf("hypotf %a %a = %a\n", F_INF, 1.0f, hypotf(F_INF, 1.0f)); /* R1 */
    printf("hypotf %a %a = %a\n", 1.0f, F_INF, hypotf(1.0f, F_INF)); /* R1 */
    printf("hypotf nan %a = %a\n", 1.0f, hypotf(F_NAN, 1.0f)); /* R1 */
    printf("hypotf %a %a = %a\n", 0x1p60f, 1.0f, hypotf(0x1p60f, 1.0f)); /* R1 */
    printf("hypotf %a %a = %a\n", 0x1p-60f, 1.0f, hypotf(0x1p-60f, 1.0f)); /* R1 */
}

static void test_cbrt_branches(void)
{
    /* cbrtd.c: subnormal, negative */
    printf("cbrt %a = %a\n", D_SUBNORM, cbrt(D_SUBNORM)); /* R1 */
    printf("cbrt %a = %a\n", -0.0, cbrt(-0.0)); /* R1 */
    printf("cbrt %a = %a\n", D_INF, cbrt(D_INF)); /* R1 */
    printf("cbrt %a = %a\n", D_NINF, cbrt(D_NINF)); /* R1 */
    printf("cbrt nan = %a\n", cbrt(D_NAN)); /* R1 */
    printf("cbrt %a = %a\n", 0x1p-1020, cbrt(0x1p-1020)); /* R1 */
}

static void test_cbrtf_branches(void)
{
    printf("cbrtf %a = %a\n", F_SUBNORM, cbrtf(F_SUBNORM)); /* R1 */
    printf("cbrtf %a = %a\n", -0.0f, cbrtf(-0.0f)); /* R1 */
    printf("cbrtf %a = %a\n", F_INF, cbrtf(F_INF)); /* R1 */
    printf("cbrtf nan = %a\n", cbrtf(F_NAN)); /* R1 */
    printf("cbrtf %a = %a\n", 0x1p-126f, cbrtf(0x1p-126f)); /* R1 */
}

static void test_sqrt_branches(void)
{
    /* sqrtd.c: negative, subnormal, inf, nan */
    printf("sqrt %a = %a\n", -1.0, sqrt(-1.0)); /* R1 */
    printf("sqrt %a = %a\n", -0.0, sqrt(-0.0)); /* R1 */
    printf("sqrt %a = %a\n", D_INF, sqrt(D_INF)); /* R1 */
    printf("sqrt nan = %a\n", sqrt(D_NAN)); /* R1 */
    printf("sqrt %a = %a\n", D_SUBNORM, sqrt(D_SUBNORM)); /* R1 */
    printf("sqrt %a = %a\n", 0x1p-1022, sqrt(0x1p-1022)); /* R1 */
    printf("sqrt %a = %a\n", 3.0, sqrt(3.0)); /* R1 */
    printf("sqrt %a = %a\n", 0x1p1000, sqrt(0x1p1000)); /* R1 */
}

static void test_sqrtf_branches(void)
{
    printf("sqrtf %a = %a\n", -1.0f, sqrtf(-1.0f)); /* R1 */
    printf("sqrtf %a = %a\n", -0.0f, sqrtf(-0.0f)); /* R1 */
    printf("sqrtf %a = %a\n", F_INF, sqrtf(F_INF)); /* R1 */
    printf("sqrtf nan = %a\n", sqrtf(F_NAN)); /* R1 */
    printf("sqrtf %a = %a\n", F_SUBNORM, sqrtf(F_SUBNORM)); /* R1 */
    printf("sqrtf %a = %a\n", 3.0f, sqrtf(3.0f)); /* R1 */
}

static void test_pow_branches(void)
{
    /* powd.c: many special cases */
    /* y==0 → 1 */
    printf("pow %a %a = %a\n", 1.0, 0.0, pow(1.0, 0.0)); /* S4 */
    printf("pow %a %a = %a\n", D_NAN, 0.0, pow(D_NAN, 0.0)); /* R1 */
    /* NaN cases */
    printf("pow nan %a = %a\n", 1.0, pow(D_NAN, 1.0)); /* R1 */
    printf("pow %a nan = %a\n", 1.0, pow(1.0, D_NAN)); /* R1 */
    printf("pow %a nan = %a\n", 2.0, pow(2.0, D_NAN)); /* R1 */
    /* x==1 */
    printf("pow %a %a = %a\n", 1.0, D_NAN, pow(1.0, D_NAN)); /* R1 */
    /* y==±inf */
    printf("pow %a %a = %a\n", 1.0, D_INF, pow(1.0, D_INF)); /* R1 */
    printf("pow %a %a = %a\n", 2.0, D_INF, pow(2.0, D_INF)); /* R1 */
    printf("pow %a %a = %a\n", 0.5, D_INF, pow(0.5, D_INF)); /* R1 */
    printf("pow %a %a = %a\n", 2.0, D_NINF, pow(2.0, D_NINF)); /* R1 */
    printf("pow %a %a = %a\n", 0.5, D_NINF, pow(0.5, D_NINF)); /* R1 */
    /* x==±inf */
    printf("pow %a %a = %a\n", D_INF, 2.0, pow(D_INF, 2.0)); /* R1 */
    printf("pow %a %a = %a\n", D_INF, -2.0, pow(D_INF, -2.0)); /* R1 */
    printf("pow %a %a = %a\n", D_NINF, 2.0, pow(D_NINF, 2.0)); /* R1 */
    printf("pow %a %a = %a\n", D_NINF, 3.0, pow(D_NINF, 3.0)); /* R1 */
    printf("pow %a %a = %a\n", D_NINF, -3.0, pow(D_NINF, -3.0)); /* R1 */
    printf("pow %a %a = %a\n", D_INF, D_INF, pow(D_INF, D_INF)); /* R1 */
    printf("pow %a %a = %a\n", D_INF, D_NINF, pow(D_INF, D_NINF)); /* R1 */
    /* x==0 */
    printf("pow %a %a = %a\n", 0.0, 1.0, pow(0.0, 1.0)); /* R1 */
    printf("pow %a %a = %a\n", 0.0, -1.0, pow(0.0, -1.0)); /* R1 */
    printf("pow %a %a = %a\n", -0.0, 1.0, pow(-0.0, 1.0)); /* R1 */
    printf("pow %a %a = %a\n", -0.0, 2.0, pow(-0.0, 2.0)); /* R1 */
    printf("pow %a %a = %a\n", -0.0, -1.0, pow(-0.0, -1.0)); /* R1 */
    printf("pow %a %a = %a\n", 0.0, D_INF, pow(0.0, D_INF)); /* R1 */
    printf("pow %a %a = %a\n", 0.0, D_NINF, pow(0.0, D_NINF)); /* R1 */
    /* negative base */
    printf("pow %a %a = %a\n", -2.0, 3.0, pow(-2.0, 3.0)); /* R1 */
    printf("pow %a %a = %a\n", -2.0, 2.0, pow(-2.0, 2.0)); /* R1 */
    printf("pow %a %a = %a\n", -2.0, 0.5, pow(-2.0, 0.5)); /* R1 */
    printf("pow %a %a = %a\n", -1.0, D_INF, pow(-1.0, D_INF)); /* R1 */
    printf("pow %a %a = %a\n", -1.0, D_NINF, pow(-1.0, D_NINF)); /* R1 */
    /* large results */
    printf("pow %a %a = %a\n", 2.0, 1024.0, pow(2.0, 1024.0)); /* R1 */
    printf("pow %a %a = %a\n", 2.0, -1075.0, pow(2.0, -1075.0)); /* R1 */
    /* normal values */
    printf("pow %a %a = %a\n", 2.0, 0.5, pow(2.0, 0.5)); /* R1 */
    printf("pow %a %a = %a\n", 2.0, -1.0, pow(2.0, -1.0)); /* R1 */
    printf("pow %a %a = %a\n", 0.5, 2.0, pow(0.5, 2.0)); /* R1 */
    printf("pow %a %a = %a\n", 0.5, -2.0, pow(0.5, -2.0)); /* R1 */
}

static void test_powf_branches(void)
{
    printf("powf %a %a = %a\n", D_NAN, 0.0f, (double)powf(F_NAN, 0.0f)); /* R1 */
    printf("powf nan %a = %a\n", 1.0f, (double)powf(F_NAN, 1.0f)); /* R1 */
    printf("powf %a nan = %a\n", 2.0f, (double)powf(2.0f, F_NAN)); /* R1 */
    printf("powf %a %a = %a\n", 1.0f, D_NAN, (double)powf(1.0f, F_NAN)); /* R1 */
    printf("powf %a %a = %a\n", 2.0f, F_INF, (double)powf(2.0f, F_INF)); /* R1 */
    printf("powf %a %a = %a\n", 0.5f, F_INF, (double)powf(0.5f, F_INF)); /* R1 */
    printf("powf %a %a = %a\n", 2.0f, F_NINF, (double)powf(2.0f, F_NINF)); /* R1 */
    printf("powf %a %a = %a\n", F_INF, 2.0f, (double)powf(F_INF, 2.0f)); /* R1 */
    printf("powf %a %a = %a\n", F_NINF, 3.0f, (double)powf(F_NINF, 3.0f)); /* R1 */
    printf("powf %a %a = %a\n", 0.0f, 1.0f, (double)powf(0.0f, 1.0f)); /* R1 */
    printf("powf %a %a = %a\n", 0.0f, -1.0f, (double)powf(0.0f, -1.0f)); /* R1 */
    printf("powf %a %a = %a\n", -2.0f, 3.0f, (double)powf(-2.0f, 3.0f)); /* R1 */
    printf("powf %a %a = %a\n", -2.0f, 2.0f, (double)powf(-2.0f, 2.0f)); /* R1 */
    printf("powf %a %a = %a\n", 2.0f, 200.0f, (double)powf(2.0f, 200.0f)); /* R1 */
    printf("powf %a %a = %a\n", 2.0f, -200.0f, (double)powf(2.0f, -200.0f)); /* R1 */
    printf("powf %a %a = %a\n", 2.0f, 0.5f, (double)powf(2.0f, 0.5f)); /* R1 */
}

static void test_fmod_branches(void)
{
    /* fmodd.c: various special cases */
    printf("fmod %a %a = %a\n", D_INF, 1.0, fmod(D_INF, 1.0)); /* R1 */
    printf("fmod %a %a = %a\n", 1.0, 0.0, fmod(1.0, 0.0)); /* R1 */
    printf("fmod nan %a = %a\n", 1.0, fmod(D_NAN, 1.0)); /* R1 */
    printf("fmod %a nan = %a\n", 1.0, fmod(1.0, D_NAN)); /* R1 */
    printf("fmod %a %a = %a\n", 0.0, 1.0, fmod(0.0, 1.0)); /* R1 */
    printf("fmod %a %a = %a\n", -0.0, 1.0, fmod(-0.0, 1.0)); /* R1 */
    printf("fmod %a %a = %a\n", 0x1p-1074, 1.0, fmod(0x1p-1074, 1.0)); /* R1 */
    printf("fmod %a %a = %a\n", 1.0, 0x1p-1074, fmod(1.0, 0x1p-1074)); /* R1 */
    printf("fmod %a %a = %a\n", 5.0, 0x1p-1074, fmod(5.0, 0x1p-1074)); /* R1 */
    printf("fmod %a %a = %a\n", 0x1p1000, 0x1p-1022, fmod(0x1p1000, 0x1p-1022)); /* R1 */
}

static void test_fmodf_branches(void)
{
    printf("fmodf %a %a = %a\n", F_INF, 1.0f, fmodf(F_INF, 1.0f)); /* R1 */
    printf("fmodf %a %a = %a\n", 1.0f, 0.0f, fmodf(1.0f, 0.0f)); /* R1 */
    printf("fmodf nan %a = %a\n", 1.0f, fmodf(F_NAN, 1.0f)); /* R1 */
    printf("fmodf %a %a = %a\n", 0.0f, 1.0f, fmodf(0.0f, 1.0f)); /* R1 */
    printf("fmodf %a %a = %a\n", -0.0f, 1.0f, fmodf(-0.0f, 1.0f)); /* R1 */
    printf("fmodf %a %a = %a\n", 0x1p-149f, 1.0f, fmodf(0x1p-149f, 1.0f)); /* R1 */
    printf("fmodf %a %a = %a\n", 1.0f, 0x1p-149f, fmodf(1.0f, 0x1p-149f)); /* R1 */
}

static void test_remainder_branches(void)
{
    /* remainderd.c */
    printf("remainder %a %a = %a\n", D_INF, 1.0, remainder(D_INF, 1.0)); /* R1 */
    printf("remainder %a %a = %a\n", 1.0, 0.0, remainder(1.0, 0.0)); /* R1 */
    printf("remainder nan %a = %a\n", 1.0, remainder(D_NAN, 1.0)); /* R1 */
    printf("remainder %a %a = %a\n", 0.0, 1.0, remainder(0.0, 1.0)); /* R1 */
    printf("remainder %a %a = %a\n", 1.0, D_INF, remainder(1.0, D_INF)); /* R1 */
    printf("remainder %a %a = %a\n", 3.0, 2.0, remainder(3.0, 2.0)); /* R1 */
    printf("remainder %a %a = %a\n", -3.0, 2.0, remainder(-3.0, 2.0)); /* R1 */
    printf("remainder %a %a = %a\n", 0x1p-1074, 1.0, remainder(0x1p-1074, 1.0)); /* R1 */
}

static void test_remainderf_branches(void)
{
    printf("remainderf %a %a = %a\n", F_INF, 1.0f, remainderf(F_INF, 1.0f)); /* R1 */
    printf("remainderf %a %a = %a\n", 1.0f, 0.0f, remainderf(1.0f, 0.0f)); /* R1 */
    printf("remainderf nan %a = %a\n", 1.0f, remainderf(F_NAN, 1.0f)); /* R1 */
    printf("remainderf %a %a = %a\n", 0.0f, 1.0f, remainderf(0.0f, 1.0f)); /* R1 */
    printf("remainderf %a %a = %a\n", 1.0f, F_INF, remainderf(1.0f, F_INF)); /* R1 */
    printf("remainderf %a %a = %a\n", 3.0f, 2.0f, remainderf(3.0f, 2.0f)); /* R1 */
}

static void test_remquo_branches(void)
{
    int q;
    double r;
    r = remquo(D_INF, 1.0, &q);
    printf("remquo inf 1 = %a quo %d\n", r, q); /* R1 */
    r = remquo(1.0, 0.0, &q);
    printf("remquo 1 0 = %a quo %d\n", r, q); /* R1 */
    r = remquo(D_NAN, 1.0, &q);
    printf("remquo nan 1 = %a quo %d\n", r, q); /* R1 */
    r = remquo(0.0, 1.0, &q);
    printf("remquo 0 1 = %a quo %d\n", r, q); /* R1 */
    r = remquo(-0.0, 1.0, &q);
    printf("remquo -0 1 = %a quo %d\n", r, q); /* R1 */
    r = remquo(1.0, D_INF, &q);
    printf("remquo 1 inf = %a quo %d\n", r, q); /* R1 */
    r = remquo(7.0, 3.0, &q);
    printf("remquo %a %a = %a quo %d\n", 7.0, 3.0, r, q); /* R1 */
    r = remquo(-7.0, 3.0, &q);
    printf("remquo %a %a = %a quo %d\n", -7.0, 3.0, r, q); /* R1 */
}

static void test_remquof_branches(void)
{
    int q;
    float r;
    r = remquof(F_INF, 1.0f, &q);
    printf("remquof inf 1 = %a quo %d\n", r, q); /* R1 */
    r = remquof(1.0f, 0.0f, &q);
    printf("remquof 1 0 = %a quo %d\n", r, q); /* R1 */
    r = remquof(0.0f, 1.0f, &q);
    printf("remquof 0 1 = %a quo %d\n", r, q); /* R1 */
    r = remquof(-0.0f, 1.0f, &q);
    printf("remquof -0 1 = %a quo %d\n", r, q); /* R1 */
    r = remquof(1.0f, F_INF, &q);
    printf("remquof 1 inf = %a quo %d\n", r, q); /* R1 */
    r = remquof(7.0f, 3.0f, &q);
    printf("remquof %a %a = %a quo %d\n", 7.0f, 3.0f, r, q); /* R1 */
}

static void test_erf_branches(void)
{
    /* erfd.c */
    printf("erf %a = %a\n", D_INF, erf(D_INF)); /* R1 */
    printf("erf %a = %a\n", D_NINF, erf(D_NINF)); /* R1 */
    printf("erf nan = %a\n", erf(D_NAN)); /* R1 */
    printf("erf %a = %a\n", 0x1p-30, erf(0x1p-30)); /* R1 */
    printf("erf %a = %a\n", -0x1p-30, erf(-0x1p-30)); /* R1 */
    printf("erf %a = %a\n", -0.0, erf(-0.0)); /* R1 */
    printf("erf %a = %a\n", 0.5, erf(0.5)); /* R1 */
    printf("erf %a = %a\n", -0.5, erf(-0.5)); /* R1 */
    printf("erf %a = %a\n", 1.5, erf(1.5)); /* R1 */
    printf("erf %a = %a\n", 4.0, erf(4.0)); /* R1 */
    printf("erf %a = %a\n", 6.0, erf(6.0)); /* R1 */
    printf("erf %a = %a\n", 20.0, erf(20.0)); /* R1 */
    printf("erf %a = %a\n", -4.0, erf(-4.0)); /* R1 */
}

static void test_erff_branches(void)
{
    printf("erff %a = %a\n", F_INF, erff(F_INF)); /* R1 */
    printf("erff %a = %a\n", F_NINF, erff(F_NINF)); /* R1 */
    printf("erff nan = %a\n", erff(F_NAN)); /* R1 */
    printf("erff %a = %a\n", 0x1p-30f, erff(0x1p-30f)); /* R1 */
    printf("erff %a = %a\n", -0.0f, erff(-0.0f)); /* R1 */
    printf("erff %a = %a\n", 0.5f, erff(0.5f)); /* R1 */
    printf("erff %a = %a\n", -0.5f, erff(-0.5f)); /* R1 */
    printf("erff %a = %a\n", 1.5f, erff(1.5f)); /* R1 */
    printf("erff %a = %a\n", 4.0f, erff(4.0f)); /* R1 */
    printf("erff %a = %a\n", 10.0f, erff(10.0f)); /* R1 */
    printf("erff %a = %a\n", -4.0f, erff(-4.0f)); /* R1 */
}

static void test_erfc_branches(void)
{
    /* erfcd.c */
    printf("erfc %a = %a\n", D_INF, erfc(D_INF)); /* R1 */
    printf("erfc %a = %a\n", D_NINF, erfc(D_NINF)); /* R1 */
    printf("erfc nan = %a\n", erfc(D_NAN)); /* R1 */
    printf("erfc %a = %a\n", 0x1p-30, erfc(0x1p-30)); /* R1 */
    printf("erfc %a = %a\n", -0.0, erfc(-0.0)); /* R1 */
    printf("erfc %a = %a\n", 0.5, erfc(0.5)); /* R1 */
    printf("erfc %a = %a\n", -0.5, erfc(-0.5)); /* R1 */
    printf("erfc %a = %a\n", 1.5, erfc(1.5)); /* R1 */
    printf("erfc %a = %a\n", 4.0, erfc(4.0)); /* R1 */
    printf("erfc %a = %a\n", 6.0, erfc(6.0)); /* R1 */
    printf("erfc %a = %a\n", 20.0, erfc(20.0)); /* R1 */
    printf("erfc %a = %a\n", -4.0, erfc(-4.0)); /* R1 */
    printf("erfc %a = %a\n", 28.0, erfc(28.0)); /* R1 */
}

static void test_erfcf_branches(void)
{
    printf("erfcf %a = %a\n", F_INF, erfcf(F_INF)); /* R1 */
    printf("erfcf %a = %a\n", F_NINF, erfcf(F_NINF)); /* R1 */
    printf("erfcf nan = %a\n", erfcf(F_NAN)); /* R1 */
    printf("erfcf %a = %a\n", 0x1p-30f, erfcf(0x1p-30f)); /* R1 */
    printf("erfcf %a = %a\n", -0.0f, erfcf(-0.0f)); /* R1 */
    printf("erfcf %a = %a\n", 0.5f, erfcf(0.5f)); /* R1 */
    printf("erfcf %a = %a\n", -0.5f, erfcf(-0.5f)); /* R1 */
    printf("erfcf %a = %a\n", 1.5f, erfcf(1.5f)); /* R1 */
    printf("erfcf %a = %a\n", 4.0f, erfcf(4.0f)); /* R1 */
    printf("erfcf %a = %a\n", 10.0f, erfcf(10.0f)); /* R1 */
    printf("erfcf %a = %a\n", -4.0f, erfcf(-4.0f)); /* R1 */
}

static void test_tgamma_branches(void)
{
    /* tgammad.c */
    printf("tgamma %a = %a\n", D_INF, tgamma(D_INF)); /* R1 */
    printf("tgamma %a = %a\n", D_NINF, tgamma(D_NINF)); /* R1 */
    printf("tgamma nan = %a\n", tgamma(D_NAN)); /* R1 */
    printf("tgamma %a = %a\n", 0.0, tgamma(0.0)); /* R1 */
    printf("tgamma %a = %a\n", -0.0, tgamma(-0.0)); /* R1 */
    printf("tgamma %a = %a\n", -1.0, tgamma(-1.0)); /* R1 */
    printf("tgamma %a = %a\n", 0.5, tgamma(0.5)); /* S4 */
    printf("tgamma %a = %a\n", -0.5, tgamma(-0.5)); /* R1 */
    printf("tgamma %a = %a\n", 10.0, tgamma(10.0)); /* R1 */
    printf("tgamma %a = %a\n", 172.0, tgamma(172.0)); /* R1 */
    printf("tgamma %a = %a\n", -100.5, tgamma(-100.5)); /* R1 */
}

static void test_tgammaf_branches(void)
{
    printf("tgammaf %a = %a\n", F_INF, tgammaf(F_INF)); /* R1 */
    printf("tgammaf %a = %a\n", F_NINF, tgammaf(F_NINF)); /* R1 */
    printf("tgammaf nan = %a\n", tgammaf(F_NAN)); /* R1 */
    printf("tgammaf %a = %a\n", 0.0f, tgammaf(0.0f)); /* R1 */
    printf("tgammaf %a = %a\n", -0.0f, tgammaf(-0.0f)); /* R1 */
    printf("tgammaf %a = %a\n", -1.0f, tgammaf(-1.0f)); /* R1 */
    printf("tgammaf %a = %a\n", 0.5f, tgammaf(0.5f)); /* S4 */
    printf("tgammaf %a = %a\n", 36.0f, tgammaf(36.0f)); /* R1 */
}

static void test_lgamma_branches(void)
{
    printf("lgamma %a = %a\n", D_INF, lgamma(D_INF)); /* R1 */
    printf("lgamma %a = %a\n", D_NINF, lgamma(D_NINF)); /* R1 */
    printf("lgamma nan = %a\n", lgamma(D_NAN)); /* R1 */
    printf("lgamma %a = %a\n", 0.0, lgamma(0.0)); /* R1 */
    printf("lgamma %a = %a\n", -0.0, lgamma(-0.0)); /* R1 */
    printf("lgamma %a = %a\n", -1.0, lgamma(-1.0)); /* R1 */
    printf("lgamma %a = %a\n", 0.5, lgamma(0.5)); /* S4 */
    printf("lgamma %a = %a\n", -0.5, lgamma(-0.5)); /* R1 */
    printf("lgamma %a = %a\n", 10.0, lgamma(10.0)); /* R1 */
    printf("lgamma %a = %a\n", 0x1p-30, lgamma(0x1p-30)); /* R1 */
    printf("lgamma %a = %a\n", -2.5, lgamma(-2.5)); /* R1 */
    printf("lgamma %a = %a\n", 3.0, lgamma(3.0)); /* R1 */
    printf("lgamma %a = %a\n", 8.0, lgamma(8.0)); /* R1 */
}

static void test_lgammaf_branches(void)
{
    printf("lgammaf %a = %a\n", F_INF, lgammaf(F_INF)); /* R1 */
    printf("lgammaf %a = %a\n", F_NINF, lgammaf(F_NINF)); /* R1 */
    printf("lgammaf nan = %a\n", lgammaf(F_NAN)); /* R1 */
    printf("lgammaf %a = %a\n", 0.0f, lgammaf(0.0f)); /* R1 */
    printf("lgammaf %a = %a\n", -1.0f, lgammaf(-1.0f)); /* R1 */
    printf("lgammaf %a = %a\n", 0.5f, lgammaf(0.5f)); /* S4 */
    printf("lgammaf %a = %a\n", -0.5f, lgammaf(-0.5f)); /* R1 */
    printf("lgammaf %a = %a\n", 10.0f, lgammaf(10.0f)); /* R1 */
    printf("lgammaf %a = %a\n", 0x1p-30f, lgammaf(0x1p-30f)); /* R1 */
    printf("lgammaf %a = %a\n", -2.5f, lgammaf(-2.5f)); /* R1 */
}

static void test_j0_branches(void)
{
    /* j0d.c */
    printf("j0 %a = %a\n", D_INF, j0(D_INF)); /* R1 */
    printf("j0 %a = %a\n", D_NINF, j0(D_NINF)); /* R1 */
    printf("j0 nan = %a\n", j0(D_NAN)); /* R1 */
    printf("j0 %a = %a\n", 0.0, j0(0.0)); /* S4 */
    printf("j0 %a = %a\n", 0x1p-30, j0(0x1p-30)); /* R1 */
    printf("j0 %a = %a\n", 3.0, j0(3.0)); /* R1 */
    printf("j0 %a = %a\n", 8.0, j0(8.0)); /* R1 */
    printf("j0 %a = %a\n", 20.0, j0(20.0)); /* R1 */
    printf("j0 %a = %a\n", 100.0, j0(100.0)); /* R1 */
}

static void test_j1_branches(void)
{
    /* j1d.c */
    printf("j1 %a = %a\n", D_INF, j1(D_INF)); /* R1 */
    printf("j1 %a = %a\n", D_NINF, j1(D_NINF)); /* R1 */
    printf("j1 nan = %a\n", j1(D_NAN)); /* R1 */
    printf("j1 %a = %a\n", 0.0, j1(0.0)); /* S4 */
    printf("j1 %a = %a\n", 0x1p-30, j1(0x1p-30)); /* R1 */
    printf("j1 %a = %a\n", 3.0, j1(3.0)); /* R1 */
    printf("j1 %a = %a\n", 8.0, j1(8.0)); /* R1 */
    printf("j1 %a = %a\n", 20.0, j1(20.0)); /* R1 */
}

static void test_jn_branches(void)
{
    /* jnd.c */
    printf("jn %d %a = %a\n", 0, D_INF, jn(0, D_INF)); /* R1 */
    printf("jn %d %a = %a\n", 1, D_NAN, jn(1, D_NAN)); /* R1 */
    printf("jn %d %a = %a\n", 5, 0.0, jn(5, 0.0)); /* R1 */
    printf("jn %d %a = %a\n", 5, 0x1p-30, jn(5, 0x1p-30)); /* R1 */
    printf("jn %d %a = %a\n", 3, 5.0, jn(3, 5.0)); /* R1 */
    printf("jn %d %a = %a\n", 5, 20.0, jn(5, 20.0)); /* R1 */
    printf("jn %d %a = %a\n", 10, 50.0, jn(10, 50.0)); /* R1 */
    printf("jn %d %a = %a\n", -1, 1.0, jn(-1, 1.0)); /* R1 */
    printf("jn %d %a = %a\n", 2, -1.0, jn(2, -1.0)); /* R1 */
}

static void test_y0_branches(void)
{
    /* y0d.c */
    printf("y0 %a = %a\n", 0.0, y0(0.0)); /* R1 */
    printf("y0 %a = %a\n", -1.0, y0(-1.0)); /* R1 */
    printf("y0 %a = %a\n", D_INF, y0(D_INF)); /* R1 */
    printf("y0 nan = %a\n", y0(D_NAN)); /* R1 */
    printf("y0 %a = %a\n", 0x1p-30, y0(0x1p-30)); /* R1 */
    printf("y0 %a = %a\n", 3.0, y0(3.0)); /* R1 */
    printf("y0 %a = %a\n", 8.0, y0(8.0)); /* R1 */
    printf("y0 %a = %a\n", 20.0, y0(20.0)); /* R1 */
}

static void test_y1_branches(void)
{
    /* y1d.c */
    printf("y1 %a = %a\n", 0.0, y1(0.0)); /* R1 */
    printf("y1 %a = %a\n", -1.0, y1(-1.0)); /* R1 */
    printf("y1 %a = %a\n", D_INF, y1(D_INF)); /* R1 */
    printf("y1 nan = %a\n", y1(D_NAN)); /* R1 */
    printf("y1 %a = %a\n", 0x1p-30, y1(0x1p-30)); /* R1 */
    printf("y1 %a = %a\n", 3.0, y1(3.0)); /* R1 */
    printf("y1 %a = %a\n", 8.0, y1(8.0)); /* R1 */
    printf("y1 %a = %a\n", 20.0, y1(20.0)); /* R1 */
}

static void test_yn_branches(void)
{
    /* ynd.c */
    printf("yn %d %a = %a\n", 0, 0.0, yn(0, 0.0)); /* R1 */
    printf("yn %d %a = %a\n", 1, -1.0, yn(1, -1.0)); /* R1 */
    printf("yn %d %a = %a\n", 1, D_INF, yn(1, D_INF)); /* R1 */
    printf("yn %d %a = %a\n", 1, D_NAN, yn(1, D_NAN)); /* R1 */
    printf("yn %d %a = %a\n", 2, 0x1p-30, yn(2, 0x1p-30)); /* R1 */
    printf("yn %d %a = %a\n", 5, 1.0, yn(5, 1.0)); /* R1 */
    printf("yn %d %a = %a\n", 5, 20.0, yn(5, 20.0)); /* R1 */
    printf("yn %d %a = %a\n", 10, 50.0, yn(10, 50.0)); /* R1 */
}

static void test_csqrt_branches(void)
{
    /* csqrtd.c */
    double complex w;
    double complex z;
    /* Branch: x<0, y==0 */
    z = CMPLX(-4.0, 0.0);
    w = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(-4.0, -0.0);
    w = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    /* Branch: NaN */
    z = CMPLX(D_NAN, 1.0);
    w = csqrt(z);
    printf("csqrt nan+%ai = %a+%ai\n", cimag(z), creal(w), cimag(w)); /* R1 */
    z = CMPLX(1.0, D_NAN);
    w = csqrt(z);
    printf("csqrt %a+nani = %a+%ai\n", creal(z), creal(w), cimag(w)); /* R1 */
    /* Branch: inf */
    z = CMPLX(D_INF, 1.0);
    w = csqrt(z);
    printf("csqrt inf+%ai = %a+%ai\n", cimag(z), creal(w), cimag(w)); /* R1 */
    z = CMPLX(D_NINF, 1.0);
    w = csqrt(z);
    printf("csqrt -inf+%ai = %a+%ai\n", cimag(z), creal(w), cimag(w)); /* R1 */
    z = CMPLX(1.0, D_INF);
    w = csqrt(z);
    printf("csqrt %a+infi = %a+%ai\n", creal(z), creal(w), cimag(w)); /* R1 */
    /* large */
    z = CMPLX(0x1p1000, 0x1p1000);
    w = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    /* subnormal */
    z = CMPLX(D_SUBNORM, 0.0);
    w = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
}

static void test_csqrtf_branches(void)
{
    float complex w;
    float complex z;
    z = CMPLXF(-4.0f, 0.0f);
    w = csqrtf(z);
    printf("csqrtf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
    z = CMPLXF(F_NAN, 1.0f);
    w = csqrtf(z);
    printf("csqrtf nan+%ai = %a+%ai\n", cimagf(z), crealf(w), cimagf(w)); /* R1 */
    z = CMPLXF(F_INF, 1.0f);
    w = csqrtf(z);
    printf("csqrtf inf+%ai = %a+%ai\n", cimagf(z), crealf(w), cimagf(w)); /* R1 */
    z = CMPLXF(F_NINF, 1.0f);
    w = csqrtf(z);
    printf("csqrtf -inf+%ai = %a+%ai\n", cimagf(z), crealf(w), cimagf(w)); /* R1 */
    z = CMPLXF(1.0f, F_INF);
    w = csqrtf(z);
    printf("csqrtf %a+infi = %a+%ai\n", crealf(z), crealf(w), cimagf(w)); /* R1 */
}

static void test_ctan_branches(void)
{
    /* ctand.c */
    double complex w;
    double complex z;
    z = CMPLX(0.0, 0.0);
    w = ctan(z);
    printf("ctan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(0.5, 2.0);
    w = ctan(z);
    printf("ctan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(D_NAN, 1.0);
    w = ctan(z);
    printf("ctan nan+%ai = %a+%ai\n", cimag(z), creal(w), cimag(w)); /* R1 */
    z = CMPLX(1.0, D_INF);
    w = ctan(z);
    printf("ctan %a+infi = %a+%ai\n", creal(z), creal(w), cimag(w)); /* R1 */
    z = CMPLX(1.0, D_NINF);
    w = ctan(z);
    printf("ctan %a-infi = %a+%ai\n", creal(z), creal(w), cimag(w)); /* R1 */
    z = CMPLX(1.0, 20.0);
    w = ctan(z);
    printf("ctan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
}

static void test_ctanf_branches(void)
{
    /* ctanf.c */
    float complex w;
    float complex z;
    z = CMPLXF(0.5f, 2.0f);
    w = ctanf(z);
    printf("ctanf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
    z = CMPLXF(F_NAN, 1.0f);
    w = ctanf(z);
    printf("ctanf nan+%ai = %a+%ai\n", cimagf(z), crealf(w), cimagf(w)); /* R1 */
    z = CMPLXF(1.0f, F_INF);
    w = ctanf(z);
    printf("ctanf %a+infi = %a+%ai\n", crealf(z), crealf(w), cimagf(w)); /* R1 */
    z = CMPLXF(1.0f, 20.0f);
    w = ctanf(z);
    printf("ctanf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
}

static void test_cpow_branches(void)
{
    /* cpowd.c */
    double complex w;
    double complex z = CMPLX(0.0, 0.0);
    double complex p = CMPLX(2.0, 0.0);
    w = cpow(z, p);
    printf("cpow 0+0i 2+0i = %a+%ai\n", creal(w), cimag(w)); /* R1 */
    z = CMPLX(-1.0, 0.0);
    p = CMPLX(1.0, 0.0);
    w = cpow(z, p);
    printf("cpow -1+0i 1+0i = %a+%ai\n", creal(w), cimag(w)); /* R1 */
    z = CMPLX(2.0, 1.0);
    p = CMPLX(0.5, 0.5);
    w = cpow(z, p);
    printf("cpow %a+%ai %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(p), cimag(p), creal(w), cimag(w)); /* R1 */
}

static void test_cpowf_branches(void)
{
    float complex w;
    float complex z = CMPLXF(0.0f, 0.0f);
    float complex p = CMPLXF(2.0f, 0.0f);
    w = cpowf(z, p);
    printf("cpowf 0+0i 2+0i = %a+%ai\n", crealf(w), cimagf(w)); /* R1 */
    z = CMPLXF(2.0f, 1.0f);
    p = CMPLXF(0.5f, 0.5f);
    w = cpowf(z, p);
    printf("cpowf %a+%ai %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(p), cimagf(p), crealf(w), cimagf(w)); /* R1 */
}

static void test_catan_branches(void)
{
    /* catand.c */
    double complex w;
    double complex z;
    z = CMPLX(0.0, 2.0);
    w = catan(z);
    printf("catan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(D_INF, 1.0);
    w = catan(z);
    printf("catan inf+%ai = %a+%ai\n", cimag(z), creal(w), cimag(w)); /* R1 */
    z = CMPLX(D_NAN, 1.0);
    w = catan(z);
    printf("catan nan+%ai = %a+%ai\n", cimag(z), creal(w), cimag(w)); /* R1 */
}

static void test_catanf_branches(void)
{
    /* catanf.c */
    float complex w;
    float complex z;
    z = CMPLXF(0.0f, 2.0f);
    w = catanf(z);
    printf("catanf %a+%ai = %a+%ai\n", crealf(z), cimagf(z), crealf(w), cimagf(w)); /* S4 */
    z = CMPLXF(F_INF, 1.0f);
    w = catanf(z);
    printf("catanf inf+%ai = %a+%ai\n", cimagf(z), crealf(w), cimagf(w)); /* R1 */
    z = CMPLXF(F_NAN, 1.0f);
    w = catanf(z);
    printf("catanf nan+%ai = %a+%ai\n", cimagf(z), crealf(w), cimagf(w)); /* R1 */
}

/* ------------------------------------------------------------------ */
/* Branch coverage — round 3 additions                                 */
/* ------------------------------------------------------------------ */

/* acos/asin: polynomial range (2^-57 <= |x| <= 0.5) */
static void test_acos_extra(void)
{
    /* Branch (106:13): False — |x| in [2^-57, 0.5] */
    printf("acos %a = %a\n", 0.3, acos(0.3)); /* R2 */
    printf("acos %a = %a\n", 0.1, acos(0.1)); /* R2 */
    printf("acos %a = %a\n", -0.3, acos(-0.3)); /* R2 */
    printf("acos %a = %a\n", -0.1, acos(-0.1)); /* R2 */
    printf("acos %a = %a\n", 0x1p-56, acos(0x1p-56)); /* R2 */
}

static void test_acosf_extra(void)
{
    /* Branch (52:13): False */
    printf("acosf %a = %a\n", 0.3f, acosf(0.3f)); /* R2 */
    printf("acosf %a = %a\n", 0.1f, acosf(0.1f)); /* R2 */
    printf("acosf %a = %a\n", -0.3f, acosf(-0.3f)); /* R2 */
    printf("acosf %a = %a\n", 0x1p-26f, acosf(0x1p-26f)); /* R2 */
}

static void test_asin_extra(void)
{
    /* Branch (104:13): False — |x| >= 2^-26 in polynomial range */
    printf("asin %a = %a\n", 0.3, asin(0.3)); /* R2 */
    printf("asin %a = %a\n", 0.1, asin(0.1)); /* R2 */
    printf("asin %a = %a\n", -0.3, asin(-0.3)); /* R2 */
    printf("asin %a = %a\n", -0.1, asin(-0.1)); /* R2 */
}

static void test_asinf_extra(void)
{
    /* Branch (45:13): False */
    printf("asinf %a = %a\n", 0.3f, asinf(0.3f)); /* R2 */
    printf("asinf %a = %a\n", 0.1f, asinf(0.1f)); /* R2 */
    printf("asinf %a = %a\n", -0.3f, asinf(-0.3f)); /* R2 */
}

/* atan2: extra edge cases */
static void test_atan2_extra(void)
{
    /* Branch (107:29): False — x near 1 but lx != 0 */
    printf("atan2 %a %a = %a\n", 1.0, 1.0 + 0x1p-52, atan2(1.0, 1.0 + 0x1p-52)); /* R2 */
    printf("atan2 %a %a = %a\n", -1.0, 1.0 + 0x1p-52, atan2(-1.0, 1.0 + 0x1p-52)); /* R2 */
    /* Branch (116): y=0 with x=+-0 cases */
    printf("atan2 %a %a = %a\n", 0.0, -0.0, atan2(0.0, -0.0)); /* R2 */
    printf("atan2 %a %a = %a\n", -0.0, -0.0, atan2(-0.0, -0.0)); /* R2 */
    /* Branch (138): x=inf, y=inf all quadrants */
    printf("atan2 %a %a = %a\n", D_INF, D_INF, atan2(D_INF, D_INF)); /* R1 */
    printf("atan2 %a %a = %a\n", D_NINF, D_INF, atan2(D_NINF, D_INF)); /* R1 */
    printf("atan2 %a %a = %a\n", D_INF, D_NINF, atan2(D_INF, D_NINF)); /* R1 */
    printf("atan2 %a %a = %a\n", D_NINF, D_NINF, atan2(D_NINF, D_NINF)); /* R1 */
    /* Branch (153): x=inf, y finite */
    printf("atan2 %a %a = %a\n", 2.0, D_INF, atan2(2.0, D_INF)); /* R2 */
    printf("atan2 %a %a = %a\n", -2.0, D_INF, atan2(-2.0, D_INF)); /* R2 */
    printf("atan2 %a %a = %a\n", 2.0, D_NINF, atan2(2.0, D_NINF)); /* R2 */
    printf("atan2 %a %a = %a\n", -2.0, D_NINF, atan2(-2.0, D_NINF)); /* R2 */
    /* Branch (170)/(171): y=inf */
    printf("atan2 %a %a = %a\n", D_INF, 3.0, atan2(D_INF, 3.0)); /* R2 */
    printf("atan2 %a %a = %a\n", D_NINF, 3.0, atan2(D_NINF, 3.0)); /* R2 */
    printf("atan2 %a %a = %a\n", D_INF, -3.0, atan2(D_INF, -3.0)); /* R2 */
    printf("atan2 %a %a = %a\n", D_NINF, -3.0, atan2(D_NINF, -3.0)); /* R2 */
    /* Branch (177): |y/x| > 2^60 with negative x */
    printf("atan2 %a %a = %a\n", 0x1p70, -1.0, atan2(0x1p70, -1.0)); /* R2 */
    printf("atan2 %a %a = %a\n", -0x1p70, -1.0, atan2(-0x1p70, -1.0)); /* R2 */
    /* Branch (190): m=1 case: y<0, x>0 */
    printf("atan2 %a %a = %a\n", -3.0, 4.0, atan2(-3.0, 4.0)); /* R2 */
    printf("atan2 %a %a = %a\n", -0.5, 1.0, atan2(-0.5, 1.0)); /* R2 */
}

static void test_atan2f_extra(void)
{
    printf("atan2f %a %a = %a\n", 1.0f, 1.0f + 0x1p-23f, (double)atan2f(1.0f, 1.0f + 0x1p-23f)); /* R2 */
    printf("atan2f %a %a = %a\n", 0.0f, -0.0f, (double)atan2f(0.0f, -0.0f)); /* R2 */
    printf("atan2f %a %a = %a\n", -0.0f, -0.0f, (double)atan2f(-0.0f, -0.0f)); /* R2 */
    printf("atan2f %a %a = %a\n", F_INF, F_INF, (double)atan2f(F_INF, F_INF)); /* R2 */
    printf("atan2f %a %a = %a\n", F_NINF, F_INF, (double)atan2f(F_NINF, F_INF)); /* R2 */
    printf("atan2f %a %a = %a\n", F_INF, F_NINF, (double)atan2f(F_INF, F_NINF)); /* R2 */
    printf("atan2f %a %a = %a\n", F_NINF, F_NINF, (double)atan2f(F_NINF, F_NINF)); /* R2 */
    printf("atan2f %a %a = %a\n", 2.0f, F_INF, (double)atan2f(2.0f, F_INF)); /* R2 */
    printf("atan2f %a %a = %a\n", -2.0f, F_INF, (double)atan2f(-2.0f, F_INF)); /* R2 */
    printf("atan2f %a %a = %a\n", 2.0f, F_NINF, (double)atan2f(2.0f, F_NINF)); /* R2 */
    printf("atan2f %a %a = %a\n", -2.0f, F_NINF, (double)atan2f(-2.0f, F_NINF)); /* R2 */
    printf("atan2f %a %a = %a\n", F_INF, 3.0f, (double)atan2f(F_INF, 3.0f)); /* R2 */
    printf("atan2f %a %a = %a\n", F_NINF, 3.0f, (double)atan2f(F_NINF, 3.0f)); /* R2 */
    printf("atan2f %a %a = %a\n", F_INF, -3.0f, (double)atan2f(F_INF, -3.0f)); /* R2 */
    printf("atan2f %a %a = %a\n", F_NINF, -3.0f, (double)atan2f(F_NINF, -3.0f)); /* R2 */
    printf("atan2f %a %a = %a\n", 0x1p30f, -1.0f, (double)atan2f(0x1p30f, -1.0f)); /* R2 */
    printf("atan2f %a %a = %a\n", -0x1p30f, -1.0f, (double)atan2f(-0x1p30f, -1.0f)); /* R2 */
    printf("atan2f %a %a = %a\n", -3.0f, 4.0f, (double)atan2f(-3.0f, 4.0f)); /* R2 */
}

/* tan: inputs in range-reduction threshold */
static void test_tan_extra(void)
{
    /* Branch (98:9): True — |x| >= ~0.6744 in tan kernel */
    printf("tan %a = %a\n", 0.7, tan(0.7)); /* R2 */
    printf("tan %a = %a\n", 0.8, tan(0.8)); /* R2 */
    printf("tan %a = %a\n", 0.9, tan(0.9)); /* R2 */
    /* Branch (99:13): hx < 0 (negative x) */
    printf("tan %a = %a\n", -0.7, tan(-0.7)); /* R2 */
    printf("tan %a = %a\n", -0.8, tan(-0.8)); /* R2 */
    printf("tan %a = %a\n", -0.9, tan(-0.9)); /* R2 */
    printf("tan %a = %a\n", -1.0, tan(-1.0)); /* R2 */
    printf("tan %a = %a\n", -1.2, tan(-1.2)); /* R2 */
}

static void test_tanf_extra(void)
{
    /* Branch (36:9): True — |x| >= ~0.6744 */
    printf("tanf %a = %a\n", 0.7f, tanf(0.7f)); /* R2 */
    printf("tanf %a = %a\n", 0.8f, tanf(0.8f)); /* R2 */
    printf("tanf %a = %a\n", -0.7f, tanf(-0.7f)); /* R2 */
    printf("tanf %a = %a\n", -0.8f, tanf(-0.8f)); /* R2 */
    printf("tanf %a = %a\n", -1.0f, tanf(-1.0f)); /* R2 */
}

/* sin/cos/tan — large args to trigger trigd.c range-reduction branches */
static void test_sin_extra(void)
{
    printf("sin %a = %a\n", 1e6, sin(1e6)); /* R2 */
    printf("sin %a = %a\n", 1e10, sin(1e10)); /* R2 */
    printf("sin %a = %a\n", 1e15, sin(1e15)); /* R2 */
    printf("sin %a = %a\n", 1e18, sin(1e18)); /* R2 */
    printf("sin %a = %a\n", -1e15, sin(-1e15)); /* R2 */
    printf("sin %a = %a\n", 0x1p20, sin(0x1p20)); /* R2 */
    printf("sin %a = %a\n", 0x1p40, sin(0x1p40)); /* R2 */
    printf("sin %a = %a\n", 0x1p60, sin(0x1p60)); /* R2 */
    printf("sin %a = %a\n", 4.71238898038469, sin(4.71238898038469)); /* R2 */
    printf("sin %a = %a\n", -4.71238898038469, sin(-4.71238898038469)); /* R2 */
}

static void test_cos_extra(void)
{
    printf("cos %a = %a\n", 1e6, cos(1e6)); /* R2 */
    printf("cos %a = %a\n", 1e10, cos(1e10)); /* R2 */
    printf("cos %a = %a\n", 1e15, cos(1e15)); /* R2 */
    printf("cos %a = %a\n", -1e15, cos(-1e15)); /* R2 */
    printf("cos %a = %a\n", 0x1p20, cos(0x1p20)); /* R2 */
    printf("cos %a = %a\n", 0x1p40, cos(0x1p40)); /* R2 */
    printf("cos %a = %a\n", 0x1p60, cos(0x1p60)); /* R2 */
}

static void test_tan_range_extra(void)
{
    printf("tan %a = %a\n", 1e6, tan(1e6)); /* R2 */
    printf("tan %a = %a\n", 1e10, tan(1e10)); /* R2 */
    printf("tan %a = %a\n", 1e15, tan(1e15)); /* R2 */
    printf("tan %a = %a\n", -1e15, tan(-1e15)); /* R2 */
    printf("tan %a = %a\n", 0x1p20, tan(0x1p20)); /* R2 */
    printf("tan %a = %a\n", 0x1p40, tan(0x1p40)); /* R2 */
}

/* sinf/cosf/tanf — large args for trigf.c branches */
static void test_sinf_extra(void)
{
    printf("sinf %a = %a\n", 1e4f, sinf(1e4f)); /* R2 */
    printf("sinf %a = %a\n", 1e6f, sinf(1e6f)); /* R2 */
    printf("sinf %a = %a\n", 1e7f, sinf(1e7f)); /* R2 */
    printf("sinf %a = %a\n", 1e8f, sinf(1e8f)); /* R2 */
    printf("sinf %a = %a\n", -1e7f, sinf(-1e7f)); /* R2 */
    printf("sinf %a = %a\n", 0x1p15f, sinf(0x1p15f)); /* R2 */
    printf("sinf %a = %a\n", 0x1p20f, sinf(0x1p20f)); /* R2 */
    printf("sinf %a = %a\n", 1.5707963f, sinf(1.5707963f)); /* R2 */
    printf("sinf %a = %a\n", -1.5707963f, sinf(-1.5707963f)); /* R2 */
}

static void test_cosf_extra(void)
{
    printf("cosf %a = %a\n", 1e4f, cosf(1e4f)); /* R2 */
    printf("cosf %a = %a\n", 1e6f, cosf(1e6f)); /* R2 */
    printf("cosf %a = %a\n", 1e7f, cosf(1e7f)); /* R2 */
    printf("cosf %a = %a\n", -1e7f, cosf(-1e7f)); /* R2 */
    printf("cosf %a = %a\n", 0x1p15f, cosf(0x1p15f)); /* R2 */
    printf("cosf %a = %a\n", 0x1p20f, cosf(0x1p20f)); /* R2 */
}

static void test_tanf_range_extra(void)
{
    printf("tanf %a = %a\n", 1e4f, tanf(1e4f)); /* R2 */
    printf("tanf %a = %a\n", 1e6f, tanf(1e6f)); /* R2 */
    printf("tanf %a = %a\n", 1e7f, tanf(1e7f)); /* R2 */
    printf("tanf %a = %a\n", -1e7f, tanf(-1e7f)); /* R2 */
    printf("tanf %a = %a\n", 0x1p15f, tanf(0x1p15f)); /* R2 */
}

/* sinh/cosh/tanh extra */
static void test_sinh_extra(void)
{
    /* Branch (113:29)/(113:49): within/above overflow threshold */
    printf("sinh %a = %a\n", 700.0, sinh(700.0)); /* R2 */
    printf("sinh %a = %a\n", 709.0, sinh(709.0)); /* R2 */
    printf("sinh %a = %a\n", -700.0, sinh(-700.0)); /* R2 */
    printf("sinh %a = %a\n", 800.0, sinh(800.0)); /* R2 */
    printf("sinh %a = %a\n", -800.0, sinh(-800.0)); /* R2 */
}

static void test_sinhf_extra(void)
{
    /* Branch (58:9): within/above overflow threshold */
    printf("sinhf %a = %a\n", 88.0f, sinhf(88.0f)); /* R2 */
    printf("sinhf %a = %a\n", 88.7f, sinhf(88.7f)); /* R2 */
    printf("sinhf %a = %a\n", -88.0f, sinhf(-88.0f)); /* R2 */
    printf("sinhf %a = %a\n", 100.0f, sinhf(100.0f)); /* R2 */
    printf("sinhf %a = %a\n", -100.0f, sinhf(-100.0f)); /* R2 */
}

static void test_cosh_extra(void)
{
    /* Branch (104:10)/(104:30): within/above overflow threshold */
    printf("cosh %a = %a\n", 700.0, cosh(700.0)); /* R2 */
    printf("cosh %a = %a\n", 709.0, cosh(709.0)); /* R2 */
    printf("cosh %a = %a\n", -700.0, cosh(-700.0)); /* R2 */
    printf("cosh %a = %a\n", 800.0, cosh(800.0)); /* R2 */
}

static void test_coshf_extra(void)
{
    /* Branch (51:9): within/above overflow threshold */
    printf("coshf %a = %a\n", 88.0f, coshf(88.0f)); /* R2 */
    printf("coshf %a = %a\n", 89.0f, coshf(89.0f)); /* R2 */
    printf("coshf %a = %a\n", -88.0f, coshf(-88.0f)); /* R2 */
    printf("coshf %a = %a\n", 100.0f, coshf(100.0f)); /* R2 */
}

static void test_tanh_extra(void)
{
    /* Branch (94:13): False — |x| < 1, use small-x formula */
    printf("tanh %a = %a\n", 0.3, tanh(0.3)); /* R2 */
    printf("tanh %a = %a\n", 0.7, tanh(0.7)); /* R2 */
    printf("tanh %a = %a\n", -0.3, tanh(-0.3)); /* R2 */
    printf("tanh %a = %a\n", -0.7, tanh(-0.7)); /* R2 */
}

static void test_tanhf_extra(void)
{
    /* Branch (34:9): False — |x| >= 22 */
    printf("tanhf %a = %a\n", 22.0f, tanhf(22.0f)); /* R2 */
    printf("tanhf %a = %a\n", -22.0f, tanhf(-22.0f)); /* R2 */
    printf("tanhf %a = %a\n", 100.0f, tanhf(100.0f)); /* R2 */
    printf("tanhf %a = %a\n", -100.0f, tanhf(-100.0f)); /* R2 */
    /* Small values */
    printf("tanhf %a = %a\n", 0.3f, tanhf(0.3f)); /* R2 */
    printf("tanhf %a = %a\n", 0.7f, tanhf(0.7f)); /* R2 */
    printf("tanhf %a = %a\n", -0.3f, tanhf(-0.3f)); /* R2 */
}

/* ceil/floor/trunc: bit-manipulation ranges */
static void test_ceil_extra(void)
{
    /* (1, 2^20) range with fractional parts */
    printf("ceil %a = %a\n", 2.7, ceil(2.7)); /* R2 */
    printf("ceil %a = %a\n", -2.7, ceil(-2.7)); /* R2 */
    printf("ceil %a = %a\n", 100.3, ceil(100.3)); /* R2 */
    printf("ceil %a = %a\n", -100.3, ceil(-100.3)); /* R2 */
    printf("ceil %a = %a\n", 50000.7, ceil(50000.7)); /* R2 */
    printf("ceil %a = %a\n", -50000.7, ceil(-50000.7)); /* R2 */
    /* j0 = 20 exactly */
    printf("ceil %a = %a\n", 0x1p20 + 0.5, ceil(0x1p20 + 0.5)); /* R2 */
    printf("ceil %a = %a\n", -(0x1p20 + 0.5), ceil(-(0x1p20 + 0.5))); /* R2 */
    /* j0 in (20, 51): fractional bits in low word */
    printf("ceil %a = %a\n", 0x1p21 + 0.5, ceil(0x1p21 + 0.5)); /* R2 */
    printf("ceil %a = %a\n", -(0x1p21 + 0.5), ceil(-(0x1p21 + 0.5))); /* R2 */
    printf("ceil %a = %a\n", 0x1p30 + 0.5, ceil(0x1p30 + 0.5)); /* R2 */
    printf("ceil %a = %a\n", 0x1p40 + 0.5, ceil(0x1p40 + 0.5)); /* R2 */
    printf("ceil %a = %a\n", 0x1p50 + 0.5, ceil(0x1p50 + 0.5)); /* R2 */
    printf("ceil %a = %a\n", -(0x1p50 + 0.5), ceil(-(0x1p50 + 0.5))); /* R2 */
}

static void test_floor_extra(void)
{
    printf("floor %a = %a\n", 2.7, floor(2.7)); /* R2 */
    printf("floor %a = %a\n", -2.7, floor(-2.7)); /* R2 */
    printf("floor %a = %a\n", 100.3, floor(100.3)); /* R2 */
    printf("floor %a = %a\n", -100.3, floor(-100.3)); /* R2 */
    printf("floor %a = %a\n", 0x1p20 + 0.5, floor(0x1p20 + 0.5)); /* R2 */
    printf("floor %a = %a\n", -(0x1p20 + 0.5), floor(-(0x1p20 + 0.5))); /* R2 */
    printf("floor %a = %a\n", 0x1p21 + 0.5, floor(0x1p21 + 0.5)); /* R2 */
    printf("floor %a = %a\n", -(0x1p21 + 0.5), floor(-(0x1p21 + 0.5))); /* R2 */
    printf("floor %a = %a\n", 0x1p30 + 0.5, floor(0x1p30 + 0.5)); /* R2 */
    printf("floor %a = %a\n", 0x1p40 + 0.5, floor(0x1p40 + 0.5)); /* R2 */
    printf("floor %a = %a\n", 0x1p50 + 0.5, floor(0x1p50 + 0.5)); /* R2 */
    printf("floor %a = %a\n", -(0x1p50 + 0.5), floor(-(0x1p50 + 0.5))); /* R2 */
    printf("floor %a = %a\n", 50000.7, floor(50000.7)); /* R2 */
    printf("floor %a = %a\n", -50000.7, floor(-50000.7)); /* R2 */
}

static void test_ceilf_extra(void)
{
    printf("ceilf %a = %a\n", 2.7f, ceilf(2.7f)); /* R2 */
    printf("ceilf %a = %a\n", -2.7f, ceilf(-2.7f)); /* R2 */
    printf("ceilf %a = %a\n", 100.3f, ceilf(100.3f)); /* R2 */
    printf("ceilf %a = %a\n", -100.3f, ceilf(-100.3f)); /* R2 */
    printf("ceilf %a = %a\n", 0x1p10f + 0.5f, ceilf(0x1p10f + 0.5f)); /* R2 */
    printf("ceilf %a = %a\n", -(0x1p10f + 0.5f), ceilf(-(0x1p10f + 0.5f))); /* R2 */
    printf("ceilf %a = %a\n", 0x1p15f + 0.5f, ceilf(0x1p15f + 0.5f)); /* R2 */
    printf("ceilf %a = %a\n", -(0x1p15f + 0.5f), ceilf(-(0x1p15f + 0.5f))); /* R2 */
    printf("ceilf %a = %a\n", 0x1p22f + 0.5f, ceilf(0x1p22f + 0.5f)); /* R2 */
}

static void test_floorf_extra(void)
{
    printf("floorf %a = %a\n", 2.7f, floorf(2.7f)); /* R2 */
    printf("floorf %a = %a\n", -2.7f, floorf(-2.7f)); /* R2 */
    printf("floorf %a = %a\n", 100.3f, floorf(100.3f)); /* R2 */
    printf("floorf %a = %a\n", -100.3f, floorf(-100.3f)); /* R2 */
    printf("floorf %a = %a\n", 0x1p10f + 0.5f, floorf(0x1p10f + 0.5f)); /* R2 */
    printf("floorf %a = %a\n", -(0x1p10f + 0.5f), floorf(-(0x1p10f + 0.5f))); /* R2 */
    printf("floorf %a = %a\n", 0x1p15f + 0.5f, floorf(0x1p15f + 0.5f)); /* R2 */
    printf("floorf %a = %a\n", -(0x1p15f + 0.5f), floorf(-(0x1p15f + 0.5f))); /* R2 */
}

static void test_trunc_extra(void)
{
    printf("trunc %a = %a\n", 2.7, trunc(2.7)); /* R2 */
    printf("trunc %a = %a\n", -2.7, trunc(-2.7)); /* R2 */
    printf("trunc %a = %a\n", 100.3, trunc(100.3)); /* R2 */
    printf("trunc %a = %a\n", -100.3, trunc(-100.3)); /* R2 */
    printf("trunc %a = %a\n", 0x1p20 + 0.5, trunc(0x1p20 + 0.5)); /* R2 */
    printf("trunc %a = %a\n", -(0x1p20 + 0.5), trunc(-(0x1p20 + 0.5))); /* R2 */
    printf("trunc %a = %a\n", 0x1p30 + 0.5, trunc(0x1p30 + 0.5)); /* R2 */
    printf("trunc %a = %a\n", -(0x1p30 + 0.5), trunc(-(0x1p30 + 0.5))); /* R2 */
    printf("trunc %a = %a\n", 0x1p53, trunc(0x1p53)); /* R2 */
    printf("trunc %a = %a\n", D_INF, trunc(D_INF)); /* R1 */
    printf("trunc %a = %a\n", D_NINF, trunc(D_NINF)); /* R2 */
}

static void test_truncf_extra(void)
{
    printf("truncf %a = %a\n", 2.7f, truncf(2.7f)); /* R2 */
    printf("truncf %a = %a\n", -2.7f, truncf(-2.7f)); /* R2 */
    printf("truncf %a = %a\n", 100.3f, truncf(100.3f)); /* R2 */
    printf("truncf %a = %a\n", -100.3f, truncf(-100.3f)); /* R2 */
    printf("truncf %a = %a\n", 0x1p10f + 0.5f, truncf(0x1p10f + 0.5f)); /* R2 */
    printf("truncf %a = %a\n", -(0x1p10f + 0.5f), truncf(-(0x1p10f + 0.5f))); /* R2 */
    printf("truncf %a = %a\n", 0x1p24f, truncf(0x1p24f)); /* R2 */
    printf("truncf %a = %a\n", F_INF, truncf(F_INF)); /* R1 */
}

/* rint/round extra */
static void test_rint_extra(void)
{
    printf("rint %a = %a\n", 2.5, rint(2.5)); /* R1 */
    printf("rint %a = %a\n", 3.5, rint(3.5)); /* R2 */
    printf("rint %a = %a\n", -3.5, rint(-3.5)); /* R2 */
    printf("rint %a = %a\n", 0.3, rint(0.3)); /* R2 */
    printf("rint %a = %a\n", -0.3, rint(-0.3)); /* R2 */
    printf("rint %a = %a\n", 0x1p20 + 0.5, rint(0x1p20 + 0.5)); /* R2 */
    printf("rint %a = %a\n", 0x1p50 + 0.5, rint(0x1p50 + 0.5)); /* R2 */
}

static void test_rintf_extra(void)
{
    printf("rintf %a = %a\n", 2.5f, rintf(2.5f)); /* R1 */
    printf("rintf %a = %a\n", 3.5f, rintf(3.5f)); /* R2 */
    printf("rintf %a = %a\n", -3.5f, rintf(-3.5f)); /* R2 */
    printf("rintf %a = %a\n", 0.3f, rintf(0.3f)); /* R2 */
    printf("rintf %a = %a\n", -0.3f, rintf(-0.3f)); /* R2 */
    printf("rintf %a = %a\n", 0x1p10f + 0.5f, rintf(0x1p10f + 0.5f)); /* R2 */
}

static void test_round_extra(void)
{
    printf("round %a = %a\n", 2.5, round(2.5)); /* R2 */
    printf("round %a = %a\n", -2.5, round(-2.5)); /* R2 */
    printf("round %a = %a\n", 0.7, round(0.7)); /* R2 */
    printf("round %a = %a\n", -0.7, round(-0.7)); /* R2 */
    printf("round %a = %a\n", 0x1p20 + 0.5, round(0x1p20 + 0.5)); /* R2 */
    printf("round %a = %a\n", -(0x1p20 + 0.5), round(-(0x1p20 + 0.5))); /* R2 */
}

static void test_roundf_extra(void)
{
    printf("roundf %a = %a\n", 2.5f, roundf(2.5f)); /* R2 */
    printf("roundf %a = %a\n", -2.5f, roundf(-2.5f)); /* R2 */
    printf("roundf %a = %a\n", 0.7f, roundf(0.7f)); /* R2 */
    printf("roundf %a = %a\n", -0.7f, roundf(-0.7f)); /* R2 */
    printf("roundf %a = %a\n", 0x1p10f + 0.5f, roundf(0x1p10f + 0.5f)); /* R2 */
}

/* lrint/llrint/lround/llround extra */
static void test_lrint_extra(void)
{
    printf("lrint %a = %ld\n", -1.5, lrint(-1.5)); /* S4 */
    printf("lrint %a = %ld\n", 2.5, lrint(2.5)); /* R2 */
    printf("lrint %a = %ld\n", -2.5, lrint(-2.5)); /* R2 */
}

static void test_lrintf_extra(void)
{
    printf("lrintf %a = %ld\n", -1.5f, lrintf(-1.5f)); /* S4 */
    printf("lrintf %a = %ld\n", 2.5f, lrintf(2.5f)); /* R2 */
    printf("lrintf %a = %ld\n", -2.5f, lrintf(-2.5f)); /* R2 */
    printf("lrintf %a = %ld\n", 0x1p20f, lrintf(0x1p20f)); /* R2 */
}

static void test_llrint_extra(void)
{
    printf("llrint %a = %lld\n", -1.5, llrint(-1.5)); /* S4 */
    printf("llrint %a = %lld\n", 2.5, llrint(2.5)); /* R2 */
    printf("llrint %a = %lld\n", -2.5, llrint(-2.5)); /* R2 */
    printf("llrint %a = %lld\n", 0x1p52, llrint(0x1p52)); /* R2 */
}

static void test_llrintf_extra(void)
{
    printf("llrintf %a = %lld\n", -1.5f, llrintf(-1.5f)); /* S4 */
    printf("llrintf %a = %lld\n", 2.5f, llrintf(2.5f)); /* R2 */
    printf("llrintf %a = %lld\n", -2.5f, llrintf(-2.5f)); /* R2 */
    printf("llrintf %a = %lld\n", 0x1p20f, llrintf(0x1p20f)); /* R2 */
}

static void test_lround_extra(void)
{
    printf("lround %a = %ld\n", -0.6, lround(-0.6)); /* R2 */
    printf("lround %a = %ld\n", 0.6, lround(0.6)); /* R2 */
    printf("lround %a = %ld\n", -1.5, lround(-1.5)); /* S4 */
    printf("lround %a = %ld\n", 2.5, lround(2.5)); /* R2 */
    printf("lround %a = %ld\n", -2.5, lround(-2.5)); /* R2 */
}

static void test_lroundf_extra(void)
{
    printf("lroundf %a = %ld\n", -0.6f, lroundf(-0.6f)); /* R2 */
    printf("lroundf %a = %ld\n", 0.6f, lroundf(0.6f)); /* R2 */
    printf("lroundf %a = %ld\n", -1.5f, lroundf(-1.5f)); /* S4 */
    printf("lroundf %a = %ld\n", 2.5f, lroundf(2.5f)); /* R2 */
}

static void test_llround_extra(void)
{
    printf("llround %a = %lld\n", -0.6, llround(-0.6)); /* R2 */
    printf("llround %a = %lld\n", 0.6, llround(0.6)); /* R2 */
    printf("llround %a = %lld\n", -1.5, llround(-1.5)); /* S4 */
    printf("llround %a = %lld\n", 2.5, llround(2.5)); /* R2 */
    printf("llround %a = %lld\n", -2.5, llround(-2.5)); /* R2 */
    printf("llround %a = %lld\n", 0x1p51, llround(0x1p51)); /* R2 */
}

static void test_llroundf_extra(void)
{
    printf("llroundf %a = %lld\n", -0.6f, llroundf(-0.6f)); /* R2 */
    printf("llroundf %a = %lld\n", 0.6f, llroundf(0.6f)); /* R2 */
    printf("llroundf %a = %lld\n", -1.5f, llroundf(-1.5f)); /* S4 */
    printf("llroundf %a = %lld\n", 2.5f, llroundf(2.5f)); /* R2 */
}

/* lgamma: fine-grained ranges for gammad.c/gammaf.c branches */
static void test_lgamma_extra(void)
{
    /* x in [0,2) polynomial ranges */
    printf("lgamma %a = %a\n", 0.1, lgamma(0.1)); /* R2 */
    printf("lgamma %a = %a\n", 0.2, lgamma(0.2)); /* R2 */
    printf("lgamma %a = %a\n", 0.4, lgamma(0.4)); /* R2 */
    printf("lgamma %a = %a\n", 0.7, lgamma(0.7)); /* R2 */
    printf("lgamma %a = %a\n", 0.8, lgamma(0.8)); /* R2 */
    printf("lgamma %a = %a\n", 0.9, lgamma(0.9)); /* R2 */
    printf("lgamma %a = %a\n", 0.95, lgamma(0.95)); /* R2 */
    printf("lgamma %a = %a\n", 1.1, lgamma(1.1)); /* R2 */
    printf("lgamma %a = %a\n", 1.3, lgamma(1.3)); /* R2 */
    printf("lgamma %a = %a\n", 1.5, lgamma(1.5)); /* R2 */
    printf("lgamma %a = %a\n", 1.7, lgamma(1.7)); /* R2 */
    printf("lgamma %a = %a\n", 1.9, lgamma(1.9)); /* R2 */
    /* x in [2,8) */
    printf("lgamma %a = %a\n", 2.5, lgamma(2.5)); /* R2 */
    printf("lgamma %a = %a\n", 3.5, lgamma(3.5)); /* R2 */
    printf("lgamma %a = %a\n", 4.5, lgamma(4.5)); /* R2 */
    printf("lgamma %a = %a\n", 5.5, lgamma(5.5)); /* R2 */
    printf("lgamma %a = %a\n", 6.5, lgamma(6.5)); /* R2 */
    printf("lgamma %a = %a\n", 7.5, lgamma(7.5)); /* R2 */
    /* x >= 2^58: asymptotic */
    printf("lgamma %a = %a\n", 0x1p60, lgamma(0x1p60)); /* R2 */
    printf("lgamma %a = %a\n", 1e20, lgamma(1e20)); /* R2 */
    /* Negative non-integers */
    printf("lgamma %a = %a\n", -0.1, lgamma(-0.1)); /* R2 */
    printf("lgamma %a = %a\n", -1.5, lgamma(-1.5)); /* R2 */
    printf("lgamma %a = %a\n", -3.5, lgamma(-3.5)); /* R2 */
    printf("lgamma %a = %a\n", -4.5, lgamma(-4.5)); /* R2 */
    printf("lgamma %a = %a\n", -100.5, lgamma(-100.5)); /* R2 */
    /* Very small |x| < 2^-70 */
    printf("lgamma %a = %a\n", 0x1p-80, lgamma(0x1p-80)); /* R2 */
    printf("lgamma %a = %a\n", -0x1p-80, lgamma(-0x1p-80)); /* R2 */
    /* Large negative (must be integer) */
    printf("lgamma %a = %a\n", -1e16, lgamma(-1e16)); /* R2 */
}

static void test_lgammaf_extra(void)
{
    /* x in [0,2) polynomial ranges */
    printf("lgammaf %a = %a\n", 0.1f, lgammaf(0.1f)); /* R2 */
    printf("lgammaf %a = %a\n", 0.2f, lgammaf(0.2f)); /* R2 */
    printf("lgammaf %a = %a\n", 0.4f, lgammaf(0.4f)); /* R2 */
    printf("lgammaf %a = %a\n", 0.7f, lgammaf(0.7f)); /* R2 */
    printf("lgammaf %a = %a\n", 0.8f, lgammaf(0.8f)); /* R2 */
    printf("lgammaf %a = %a\n", 0.9f, lgammaf(0.9f)); /* R2 */
    printf("lgammaf %a = %a\n", 1.1f, lgammaf(1.1f)); /* R2 */
    printf("lgammaf %a = %a\n", 1.3f, lgammaf(1.3f)); /* R2 */
    printf("lgammaf %a = %a\n", 1.5f, lgammaf(1.5f)); /* R2 */
    printf("lgammaf %a = %a\n", 1.7f, lgammaf(1.7f)); /* R2 */
    printf("lgammaf %a = %a\n", 1.9f, lgammaf(1.9f)); /* R2 */
    /* x in [2,8) */
    printf("lgammaf %a = %a\n", 2.5f, lgammaf(2.5f)); /* R2 */
    printf("lgammaf %a = %a\n", 3.5f, lgammaf(3.5f)); /* R2 */
    printf("lgammaf %a = %a\n", 4.5f, lgammaf(4.5f)); /* R2 */
    printf("lgammaf %a = %a\n", 5.5f, lgammaf(5.5f)); /* R2 */
    printf("lgammaf %a = %a\n", 6.5f, lgammaf(6.5f)); /* R2 */
    printf("lgammaf %a = %a\n", 7.5f, lgammaf(7.5f)); /* R2 */
    /* x >= 2^23: asymptotic */
    printf("lgammaf %a = %a\n", 1e8f, lgammaf(1e8f)); /* R2 */
    printf("lgammaf %a = %a\n", 0x1p60f, lgammaf(0x1p60f)); /* R2 */
    /* Negative non-integers */
    printf("lgammaf %a = %a\n", -0.1f, lgammaf(-0.1f)); /* R2 */
    printf("lgammaf %a = %a\n", -1.5f, lgammaf(-1.5f)); /* R2 */
    printf("lgammaf %a = %a\n", -2.5f, lgammaf(-2.5f)); /* R1 */
    printf("lgammaf %a = %a\n", -3.5f, lgammaf(-3.5f)); /* R2 */
    printf("lgammaf %a = %a\n", -4.5f, lgammaf(-4.5f)); /* R2 */
    printf("lgammaf %a = %a\n", -5.5f, lgammaf(-5.5f)); /* R2 */
    printf("lgammaf %a = %a\n", -6.5f, lgammaf(-6.5f)); /* R2 */
    printf("lgammaf %a = %a\n", -100.5f, lgammaf(-100.5f)); /* R2 */
    /* Very small |x| */
    printf("lgammaf %a = %a\n", 0x1p-40f, lgammaf(0x1p-40f)); /* R2 */
    printf("lgammaf %a = %a\n", -0x1p-40f, lgammaf(-0x1p-40f)); /* R2 */
    /* Large negative integer */
    printf("lgammaf %a = %a\n", -1e8f, lgammaf(-1e8f)); /* R2 */
}

/* pow extra cases */
static void test_pow_extra(void)
{
    /* Near-unity x with large y (Branches 274-289) */
    printf("pow %a %a = %a\n", 1.0 + 0x1p-52, 1e15, pow(1.0 + 0x1p-52, 1e15)); /* R2 */
    printf("pow %a %a = %a\n", 1.0 - 0x1p-53, 1e15, pow(1.0 - 0x1p-53, 1e15)); /* R2 */
    printf("pow %a %a = %a\n", 1.0 + 0x1p-52, -1e15, pow(1.0 + 0x1p-52, -1e15)); /* R2 */
    printf("pow %a %a = %a\n", 1.0 - 0x1p-53, -1e15, pow(1.0 - 0x1p-53, -1e15)); /* R2 */
    /* Subnormal x (Branch 306) */
    printf("pow %a %a = %a\n", D_SUBNORM, 0.5, pow(D_SUBNORM, 0.5)); /* R2 */
    printf("pow %a %a = %a\n", 0x1p-1022, 2.0, pow(0x1p-1022, 2.0)); /* R2 */
    /* Negative x: even/odd/non-integer y */
    printf("pow %a %a = %a\n", -2.0, 4.0, pow(-2.0, 4.0)); /* R2 */
    printf("pow %a %a = %a\n", -2.0, 5.0, pow(-2.0, 5.0)); /* R2 */
    printf("pow %a %a = %a\n", -2.0, 1.5, pow(-2.0, 1.5)); /* R2 */
    printf("pow %a %a = %a\n", -1.0, 1.0, pow(-1.0, 1.0)); /* R2 */
    printf("pow %a %a = %a\n", -1.0, 2.0, pow(-1.0, 2.0)); /* R2 */
    printf("pow %a %a = %a\n", -1.0, 0.5, pow(-1.0, 0.5)); /* R2 */
    /* Huge y (Branch 274) */
    printf("pow %a %a = %a\n", 2.0, 0x1p52, pow(2.0, 0x1p52)); /* R2 */
    printf("pow %a %a = %a\n", 0.5, 0x1p52, pow(0.5, 0x1p52)); /* R2 */
    /* Result subnormal (Branch 426) */
    printf("pow %a %a = %a\n", 2.0, -1074.0, pow(2.0, -1074.0)); /* R2 */
    /* Signaling NaN with y=0 (Branch 139) */
    {
        union { double d; uint64_t i; } u;
        u.i = 0x7FF0000000000001ULL;
        printf("pow snan 0 = %a\n", pow(u.d, 0.0)); /* R2 */
    }
}

static void test_powf_extra(void)
{
    /* Near-unity x with large y */
    printf("powf %a %a = %a\n", 1.0f + 0x1p-23f, 1e6f, (double)powf(1.0f + 0x1p-23f, 1e6f)); /* R2 */
    printf("powf %a %a = %a\n", 1.0f - 0x1p-24f, 1e6f, (double)powf(1.0f - 0x1p-24f, 1e6f)); /* R2 */
    printf("powf %a %a = %a\n", 1.0f + 0x1p-23f, -1e6f, (double)powf(1.0f + 0x1p-23f, -1e6f)); /* R2 */
    /* Subnormal x */
    printf("powf %a %a = %a\n", F_SUBNORM, 0.5f, (double)powf(F_SUBNORM, 0.5f)); /* R2 */
    printf("powf %a %a = %a\n", 0x1p-126f, 2.0f, (double)powf(0x1p-126f, 2.0f)); /* R2 */
    /* Negative x: even/odd/non-integer y */
    printf("powf %a %a = %a\n", -2.0f, 4.0f, (double)powf(-2.0f, 4.0f)); /* R2 */
    printf("powf %a %a = %a\n", -2.0f, 5.0f, (double)powf(-2.0f, 5.0f)); /* R2 */
    printf("powf %a %a = %a\n", -2.0f, 1.5f, (double)powf(-2.0f, 1.5f)); /* R2 */
    printf("powf %a %a = %a\n", -1.0f, 1.0f, (double)powf(-1.0f, 1.0f)); /* R2 */
    /* Huge y */
    printf("powf %a %a = %a\n", 2.0f, 0x1p23f, (double)powf(2.0f, 0x1p23f)); /* R2 */
    /* Result subnormal */
    printf("powf %a %a = %a\n", 2.0f, -149.0f, (double)powf(2.0f, -149.0f)); /* R2 */
    /* Signaling NaN with y=0 (Branch 53) */
    {
        union { float f; uint32_t i; } u;
        u.i = 0x7F800001U;
        printf("powf snan 0 = %a\n", (double)powf(u.f, 0.0f)); /* R2 */
    }
    /* sqrt case */
    printf("powf %a %a = %a\n", -4.0f, 0.5f, (double)powf(-4.0f, 0.5f)); /* R2 */
}

/* fmod extra */
static void test_fmod_extra(void)
{
    printf("fmod %a %a = %a\n", 3.0, 2.0, fmod(3.0, 2.0)); /* R2 */
    printf("fmod %a %a = %a\n", 3.5, 1.5, fmod(3.5, 1.5)); /* R2 */
    printf("fmod %a %a = %a\n", -3.5, 1.5, fmod(-3.5, 1.5)); /* R2 */
    printf("fmod %a %a = %a\n", 1000.0, 3.0, fmod(1000.0, 3.0)); /* R2 */
    printf("fmod %a %a = %a\n", 1e10, 3.0, fmod(1e10, 3.0)); /* R2 */
    printf("fmod %a %a = %a\n", 1e15, 7.0, fmod(1e15, 7.0)); /* R2 */
    printf("fmod %a %a = %a\n", 0x1p-1022, 0x1p-1074, fmod(0x1p-1022, 0x1p-1074)); /* R2 */
    printf("fmod %a %a = %a\n", 7.0, 3.0, fmod(7.0, 3.0)); /* R2 */
    printf("fmod %a %a = %a\n", -7.0, 3.0, fmod(-7.0, 3.0)); /* R2 */
}

static void test_fmodf_extra(void)
{
    printf("fmodf %a %a = %a\n", 3.0f, 2.0f, fmodf(3.0f, 2.0f)); /* R2 */
    printf("fmodf %a %a = %a\n", 3.5f, 1.5f, fmodf(3.5f, 1.5f)); /* R2 */
    printf("fmodf %a %a = %a\n", -3.5f, 1.5f, fmodf(-3.5f, 1.5f)); /* R2 */
    printf("fmodf %a %a = %a\n", 1000.0f, 3.0f, fmodf(1000.0f, 3.0f)); /* R2 */
    printf("fmodf %a %a = %a\n", 1e7f, 3.0f, fmodf(1e7f, 3.0f)); /* R2 */
    printf("fmodf %a %a = %a\n", 7.0f, 3.0f, fmodf(7.0f, 3.0f)); /* R2 */
    printf("fmodf %a %a = %a\n", -7.0f, 3.0f, fmodf(-7.0f, 3.0f)); /* R2 */
    printf("fmodf %a %a = %a\n", 0x1p-126f, 0x1p-149f, fmodf(0x1p-126f, 0x1p-149f)); /* R2 */
}

/* remainder/remquo extra */
static void test_remainder_extra(void)
{
    printf("remainder %a %a = %a\n", 5.0, 2.0, remainder(5.0, 2.0)); /* R2 */
    printf("remainder %a %a = %a\n", 5.5, 2.0, remainder(5.5, 2.0)); /* R2 */
    printf("remainder %a %a = %a\n", 7.0, 3.0, remainder(7.0, 3.0)); /* R2 */
    printf("remainder %a %a = %a\n", -7.0, 3.0, remainder(-7.0, 3.0)); /* R2 */
    printf("remainder %a %a = %a\n", 1000.0, 7.0, remainder(1000.0, 7.0)); /* R2 */
    printf("remainder %a %a = %a\n", 0x1p-1074, 0x1p-1022, remainder(0x1p-1074, 0x1p-1022)); /* R2 */
}

static void test_remainderf_extra(void)
{
    printf("remainderf %a %a = %a\n", 5.0f, 2.0f, remainderf(5.0f, 2.0f)); /* R2 */
    printf("remainderf %a %a = %a\n", 5.5f, 2.0f, remainderf(5.5f, 2.0f)); /* R2 */
    printf("remainderf %a %a = %a\n", 7.0f, 3.0f, remainderf(7.0f, 3.0f)); /* R2 */
    printf("remainderf %a %a = %a\n", -7.0f, 3.0f, remainderf(-7.0f, 3.0f)); /* R2 */
    printf("remainderf %a %a = %a\n", 1000.0f, 7.0f, remainderf(1000.0f, 7.0f)); /* R2 */
}

static void test_remquo_extra(void)
{
    int q;
    double r;
    r = remquo(5.0, 2.0, &q);
    printf("remquo %a %a = %a quo %d\n", 5.0, 2.0, r, q); /* R2 */
    r = remquo(5.5, 2.0, &q);
    printf("remquo %a %a = %a quo %d\n", 5.5, 2.0, r, q); /* R2 */
    r = remquo(100.0, 7.0, &q);
    printf("remquo %a %a = %a quo %d\n", 100.0, 7.0, r, q); /* R2 */
    r = remquo(-100.0, 7.0, &q);
    printf("remquo %a %a = %a quo %d\n", -100.0, 7.0, r, q); /* R2 */
    r = remquo(0x1p-1074, 0x1p-1022, &q);
    printf("remquo tiny = %a quo %d\n", r, q); /* R2 */
}

static void test_remquof_extra(void)
{
    int q;
    float r;
    r = remquof(5.0f, 2.0f, &q);
    printf("remquof %a %a = %a quo %d\n", 5.0f, 2.0f, r, q); /* R2 */
    r = remquof(100.0f, 7.0f, &q);
    printf("remquof %a %a = %a quo %d\n", 100.0f, 7.0f, r, q); /* R2 */
    r = remquof(-100.0f, 7.0f, &q);
    printf("remquof %a %a = %a quo %d\n", -100.0f, 7.0f, r, q); /* R2 */
    r = remquof(5.5f, 2.0f, &q);
    printf("remquof %a %a = %a quo %d\n", 5.5f, 2.0f, r, q); /* R2 */
}

/* sqrt extra */
static void test_sqrt_extra(void)
{
    printf("sqrt %a = %a\n", 2.0, sqrt(2.0)); /* S4 */
    printf("sqrt %a = %a\n", 3.0, sqrt(3.0)); /* R1 */
    printf("sqrt %a = %a\n", 5.0, sqrt(5.0)); /* R2 */
    printf("sqrt %a = %a\n", 7.0, sqrt(7.0)); /* R2 */
    printf("sqrt %a = %a\n", 0.1, sqrt(0.1)); /* R2 */
    printf("sqrt %a = %a\n", 0.3, sqrt(0.3)); /* R2 */
    printf("sqrt %a = %a\n", 1.5, sqrt(1.5)); /* R2 */
    printf("sqrt %a = %a\n", 1e100, sqrt(1e100)); /* R2 */
    printf("sqrt %a = %a\n", 1e-100, sqrt(1e-100)); /* R2 */
}

static void test_sqrtf_extra(void)
{
    printf("sqrtf %a = %a\n", 2.0f, sqrtf(2.0f)); /* S4 */
    printf("sqrtf %a = %a\n", 3.0f, sqrtf(3.0f)); /* R1 */
    printf("sqrtf %a = %a\n", 0.1f, sqrtf(0.1f)); /* R2 */
    printf("sqrtf %a = %a\n", 0.3f, sqrtf(0.3f)); /* R2 */
    printf("sqrtf %a = %a\n", 1.5f, sqrtf(1.5f)); /* R2 */
    printf("sqrtf %a = %a\n", 0x1p-126f, sqrtf(0x1p-126f)); /* R2 */
}

/* log/log10/log2/logb/log1p extra */
static void test_log_extra(void)
{
    /* Subnormal input */
    printf("log %a = %a\n", D_SUBNORM, log(D_SUBNORM)); /* R1 */
    printf("log %a = %a\n", 0x1p-1022, log(0x1p-1022)); /* R2 */
    /* Range (0,1) */
    printf("log %a = %a\n", 0.5, log(0.5)); /* R1 */
    printf("log %a = %a\n", 0.7, log(0.7)); /* R2 */
    printf("log %a = %a\n", 0.9, log(0.9)); /* R2 */
    /* Range (1, sqrt(2)) and (sqrt(2), 2) */
    printf("log %a = %a\n", 1.2, log(1.2)); /* R2 */
    printf("log %a = %a\n", 1.41, log(1.41)); /* R2 */
    printf("log %a = %a\n", 1.42, log(1.42)); /* R2 */
    printf("log %a = %a\n", 1.8, log(1.8)); /* R2 */
}

static void test_logf_extra(void)
{
    printf("logf %a = %a\n", F_SUBNORM, logf(F_SUBNORM)); /* R1 */
    printf("logf %a = %a\n", 0x1p-126f, logf(0x1p-126f)); /* R2 */
    printf("logf %a = %a\n", 0.5f, logf(0.5f)); /* R1 */
    printf("logf %a = %a\n", 0.7f, logf(0.7f)); /* R2 */
    printf("logf %a = %a\n", 1.2f, logf(1.2f)); /* R2 */
    printf("logf %a = %a\n", 1.41f, logf(1.41f)); /* R2 */
    printf("logf %a = %a\n", 1.42f, logf(1.42f)); /* R2 */
    printf("logf %a = %a\n", 1.8f, logf(1.8f)); /* R2 */
}

static void test_log10_extra(void)
{
    printf("log10 %a = %a\n", D_SUBNORM, log10(D_SUBNORM)); /* R1 */
    printf("log10 %a = %a\n", 0.5, log10(0.5)); /* R1 */
    printf("log10 %a = %a\n", 0x1p-1022, log10(0x1p-1022)); /* R2 */
}

static void test_log10f_extra(void)
{
    printf("log10f %a = %a\n", F_SUBNORM, log10f(F_SUBNORM)); /* R1 */
    printf("log10f %a = %a\n", 0.5f, log10f(0.5f)); /* R1 */
    printf("log10f %a = %a\n", 0x1p-126f, log10f(0x1p-126f)); /* R2 */
}

static void test_log2_extra(void)
{
    printf("log2 %a = %a\n", D_SUBNORM, log2(D_SUBNORM)); /* R1 */
    printf("log2 %a = %a\n", 0.5, log2(0.5)); /* R1 */
    printf("log2 %a = %a\n", 0x1p-1022, log2(0x1p-1022)); /* R2 */
}

static void test_log2f_extra(void)
{
    printf("log2f %a = %a\n", F_SUBNORM, log2f(F_SUBNORM)); /* R1 */
    printf("log2f %a = %a\n", 0.5f, log2f(0.5f)); /* R1 */
    printf("log2f %a = %a\n", 0x1p-126f, log2f(0x1p-126f)); /* R2 */
}

static void test_logb_extra(void)
{
    printf("logb %a = %a\n", -1.0, logb(-1.0)); /* R2 */
    printf("logb %a = %a\n", D_NINF, logb(D_NINF)); /* R2 */
    printf("logb %a = %a\n", -D_SUBNORM, logb(-D_SUBNORM)); /* R2 */
}

static void test_log1p_extra(void)
{
    printf("log1p %a = %a\n", -0.9, log1p(-0.9)); /* R1 */
    printf("log1p %a = %a\n", -0.5, log1p(-0.5)); /* R1 */
    printf("log1p %a = %a\n", -0.3, log1p(-0.3)); /* R2 */
    printf("log1p %a = %a\n", 0.1, log1p(0.1)); /* R2 */
    printf("log1p %a = %a\n", 0.5, log1p(0.5)); /* R1 */
    printf("log1p %a = %a\n", 2.0, log1p(2.0)); /* R1 */
    printf("log1p %a = %a\n", 100.0, log1p(100.0)); /* R2 */
}

static void test_log1pf_extra(void)
{
    printf("log1pf %a = %a\n", -0.9f, log1pf(-0.9f)); /* R1 */
    printf("log1pf %a = %a\n", -0.5f, log1pf(-0.5f)); /* R1 */
    printf("log1pf %a = %a\n", -0.3f, log1pf(-0.3f)); /* R2 */
    printf("log1pf %a = %a\n", 0.1f, log1pf(0.1f)); /* R2 */
    printf("log1pf %a = %a\n", 0.5f, log1pf(0.5f)); /* R1 */
    printf("log1pf %a = %a\n", 2.0f, log1pf(2.0f)); /* R1 */
    printf("log1pf %a = %a\n", 0x1p-26f, log1pf(0x1p-26f)); /* R2 */
}

/* expm1 extra */
static void test_expm1_extra(void)
{
    printf("expm1 %a = %a\n", -0.5, expm1(-0.5)); /* R1 */
    printf("expm1 %a = %a\n", -1.0, expm1(-1.0)); /* R2 */
    printf("expm1 %a = %a\n", -2.0, expm1(-2.0)); /* R1 */
    printf("expm1 %a = %a\n", 50.0, expm1(50.0)); /* R2 */
    printf("expm1 %a = %a\n", 700.0, expm1(700.0)); /* R2 */
}

static void test_expm1f_extra(void)
{
    printf("expm1f %a = %a\n", -0.5f, expm1f(-0.5f)); /* R1 */
    printf("expm1f %a = %a\n", -1.0f, expm1f(-1.0f)); /* R2 */
    printf("expm1f %a = %a\n", 50.0f, expm1f(50.0f)); /* R2 */
    printf("expm1f %a = %a\n", 200.0f, expm1f(200.0f)); /* R1 */
}

/* modf extra */
static void test_modf_extra(void)
{
    double ipart;
    double frac;
    frac = modf(3.7, &ipart);
    printf("modf %a = %a ipart %a\n", 3.7, frac, ipart); /* R2 */
    frac = modf(-3.7, &ipart);
    printf("modf %a = %a ipart %a\n", -3.7, frac, ipart); /* R2 */
    /* j0 > 51: large integral */
    frac = modf(0x1p52 + 0.5, &ipart);
    printf("modf %a = %a ipart %a\n", 0x1p52 + 0.5, frac, ipart); /* R2 */
    frac = modf(0x1p60, &ipart);
    printf("modf %a = %a ipart %a\n", 0x1p60, frac, ipart); /* R2 */
    /* j0 in (20,51): fraction in low word */
    frac = modf(0x1p21 + 0.5, &ipart);
    printf("modf %a = %a ipart %a\n", 0x1p21 + 0.5, frac, ipart); /* R2 */
    frac = modf(0x1p30 + 0.5, &ipart);
    printf("modf %a = %a ipart %a\n", 0x1p30 + 0.5, frac, ipart); /* R2 */
}

static void test_modff_extra(void)
{
    float ipartf;
    float fracf;
    fracf = modff(3.7f, &ipartf);
    printf("modff %a = %a ipart %a\n", 3.7f, fracf, ipartf); /* R2 */
    fracf = modff(-3.7f, &ipartf);
    printf("modff %a = %a ipart %a\n", -3.7f, fracf, ipartf); /* R2 */
    /* j0 > 23: already integral */
    fracf = modff(0x1p24f, &ipartf);
    printf("modff %a = %a ipart %a\n", 0x1p24f, fracf, ipartf); /* R2 */
    /* j0 in (0,22) range */
    fracf = modff(0x1p10f + 0.5f, &ipartf);
    printf("modff %a = %a ipart %a\n", 0x1p10f + 0.5f, fracf, ipartf); /* R2 */
}

/* nextafter extra */
static void test_nextafter_extra(void)
{
    printf("nextafter %a %a = %a\n", 1.0, 1.0, nextafter(1.0, 1.0)); /* S4 */
    printf("nextafter %a %a = %a\n", D_NAN, 1.0, nextafter(D_NAN, 1.0)); /* R2 */
    printf("nextafter %a %a = %a\n", 1.0, D_NAN, nextafter(1.0, D_NAN)); /* R2 */
    printf("nextafter %a %a = %a\n", D_INF, 0.0, nextafter(D_INF, 0.0)); /* R2 */
    printf("nextafter %a %a = %a\n", D_NINF, 0.0, nextafter(D_NINF, 0.0)); /* R2 */
    printf("nextafter %a %a = %a\n", 0.0, 1.0, nextafter(0.0, 1.0)); /* S4 */
    printf("nextafter %a %a = %a\n", 0.0, -1.0, nextafter(0.0, -1.0)); /* R1 */
    printf("nextafter %a %a = %a\n", -0.0, 1.0, nextafter(-0.0, 1.0)); /* R1 */
    printf("nextafter %a %a = %a\n", D_SUBNORM, 0.0, nextafter(D_SUBNORM, 0.0)); /* R1 */
    printf("nextafter %a %a = %a\n", -D_SUBNORM, 0.0, nextafter(-D_SUBNORM, 0.0)); /* R2 */
}

static void test_nextafterf_extra(void)
{
    printf("nextafterf %a %a = %a\n", 1.0f, 1.0f, nextafterf(1.0f, 1.0f)); /* R1 */
    printf("nextafterf %a %a = %a\n", F_NAN, 1.0f, nextafterf(F_NAN, 1.0f)); /* R2 */
    printf("nextafterf %a %a = %a\n", F_INF, 0.0f, nextafterf(F_INF, 0.0f)); /* R2 */
    printf("nextafterf %a %a = %a\n", 0.0f, 1.0f, nextafterf(0.0f, 1.0f)); /* S4 */
    printf("nextafterf %a %a = %a\n", 0.0f, -1.0f, nextafterf(0.0f, -1.0f)); /* R1 */
    printf("nextafterf %a %a = %a\n", F_SUBNORM, 0.0f, nextafterf(F_SUBNORM, 0.0f)); /* R1 */
}

/* ilogb extra */
static void test_ilogb_extra(void)
{
    /* hx==0 subnormal: min subnormal has high word 0, low word 1 */
    printf("ilogb %a = %d\n", 0x1p-1074, ilogb(0x1p-1074)); /* R2 */
    printf("ilogb %a = %d\n", -0x1p-1074, ilogb(-0x1p-1074)); /* R2 */
    printf("ilogb %a = %d\n", 1.5, ilogb(1.5)); /* R2 */
    printf("ilogb %a = %d\n", 0.5, ilogb(0.5)); /* S4 */
    printf("ilogb %a = %d\n", 1024.0, ilogb(1024.0)); /* R2 */
    printf("ilogb %a = %d\n", -1.0, ilogb(-1.0)); /* R1 */
}

/* hypot extra */
static void test_hypot_extra(void)
{
    printf("hypot %a %a = %a\n", 3.0, 4.0, hypot(3.0, 4.0)); /* S4 */
    printf("hypot %a %a = %a\n", 0.3, 0.4, hypot(0.3, 0.4)); /* R2 */
    printf("hypot %a %a = %a\n", D_SUBNORM, D_SUBNORM, hypot(D_SUBNORM, D_SUBNORM)); /* R2 */
    printf("hypot %a %a = %a\n", 1.0, 0x1p600, hypot(1.0, 0x1p600)); /* R2 */
    printf("hypot %a %a = %a\n", 0x1p500, 0x1p500, hypot(0x1p500, 0x1p500)); /* R2 */
}

static void test_hypotf_extra(void)
{
    printf("hypotf %a %a = %a\n", 3.0f, 4.0f, hypotf(3.0f, 4.0f)); /* S4 */
    printf("hypotf %a %a = %a\n", F_SUBNORM, F_SUBNORM, hypotf(F_SUBNORM, F_SUBNORM)); /* R2 */
    printf("hypotf %a %a = %a\n", 0x1p60f, 0x1p60f, hypotf(0x1p60f, 0x1p60f)); /* R2 */
    printf("hypotf %a %a = %a\n", 0x1p-60f, 0x1p-60f, hypotf(0x1p-60f, 0x1p-60f)); /* R2 */
}

/* erfc extra */
static void test_erfc_extra(void)
{
    printf("erfc %a = %a\n", -1.0, erfc(-1.0)); /* S4 */
    printf("erfc %a = %a\n", -2.0, erfc(-2.0)); /* R2 */
    printf("erfc %a = %a\n", -5.0, erfc(-5.0)); /* R2 */
    printf("erfc %a = %a\n", -20.0, erfc(-20.0)); /* R2 */
    printf("erfc %a = %a\n", 3.0, erfc(3.0)); /* R2 */
    printf("erfc %a = %a\n", 10.0, erfc(10.0)); /* R2 */
    printf("erfc %a = %a\n", 30.0, erfc(30.0)); /* R2 */
    printf("erfc %a = %a\n", 0.7, erfc(0.7)); /* R2 */
}

static void test_erfcf_extra(void)
{
    printf("erfcf %a = %a\n", -1.0f, erfcf(-1.0f)); /* R2 */
    printf("erfcf %a = %a\n", -2.0f, erfcf(-2.0f)); /* R2 */
    printf("erfcf %a = %a\n", -5.0f, erfcf(-5.0f)); /* R2 */
    printf("erfcf %a = %a\n", 3.0f, erfcf(3.0f)); /* R2 */
    printf("erfcf %a = %a\n", 0.7f, erfcf(0.7f)); /* R2 */
    printf("erfcf %a = %a\n", 1.0f, erfcf(1.0f)); /* S4 */
    printf("erfcf %a = %a\n", 2.0f, erfcf(2.0f)); /* R2 */
}

/* Bessel extra */
static void test_j0_extra(void)
{
    printf("j0 %a = %a\n", -3.0, j0(-3.0)); /* R2 */
    printf("j0 %a = %a\n", 5.0, j0(5.0)); /* R2 */
    printf("j0 %a = %a\n", 200.0, j0(200.0)); /* R2 */
    printf("j0 %a = %a\n", 0x1p-100, j0(0x1p-100)); /* R2 */
    printf("j0 %a = %a\n", -8.0, j0(-8.0)); /* R2 */
}

static void test_j1_extra(void)
{
    printf("j1 %a = %a\n", -3.0, j1(-3.0)); /* R2 */
    printf("j1 %a = %a\n", 5.0, j1(5.0)); /* R2 */
    printf("j1 %a = %a\n", 200.0, j1(200.0)); /* R2 */
    printf("j1 %a = %a\n", 0x1p-100, j1(0x1p-100)); /* R2 */
}

static void test_jn_extra(void)
{
    printf("jn %d %a = %a\n", 1, 0.0, jn(1, 0.0)); /* R2 */
    printf("jn %d %a = %a\n", 2, 0.0, jn(2, 0.0)); /* R2 */
    printf("jn %d %a = %a\n", 1, 0x1p-30, jn(1, 0x1p-30)); /* R2 */
    printf("jn %d %a = %a\n", 3, 0x1p-30, jn(3, 0x1p-30)); /* R2 */
    printf("jn %d %a = %a\n", 5, 2.0, jn(5, 2.0)); /* R2 */
    printf("jn %d %a = %a\n", 10, 3.0, jn(10, 3.0)); /* R2 */
    printf("jn %d %a = %a\n", 50, 1.0, jn(50, 1.0)); /* R2 */
    printf("jn %d %a = %a\n", 3, 0.5, jn(3, 0.5)); /* R2 */
    printf("jn %d %a = %a\n", 2, 5.0, jn(2, 5.0)); /* R2 */
    printf("jn %d %a = %a\n", 100, 1.0, jn(100, 1.0)); /* R2 */
    printf("jn %d %a = %a\n", 2, 1000.0, jn(2, 1000.0)); /* R2 */
    printf("jn %d %a = %a\n", 5, 0.001, jn(5, 0.001)); /* R2 */
}

static void test_yn_extra(void)
{
    printf("yn %d %a = %a\n", 2, 1.0, yn(2, 1.0)); /* S4 */
    printf("yn %d %a = %a\n", 3, 1.0, yn(3, 1.0)); /* R2 */
    printf("yn %d %a = %a\n", 5, 0.5, yn(5, 0.5)); /* R2 */
    printf("yn %d %a = %a\n", -2, 1.0, yn(-2, 1.0)); /* R2 */
    printf("yn %d %a = %a\n", -3, 1.0, yn(-3, 1.0)); /* R2 */
    printf("yn %d %a = %a\n", 10, 1.0, yn(10, 1.0)); /* R2 */
    printf("yn %d %a = %a\n", 2, 1e5, yn(2, 1e5)); /* R2 */
    printf("yn %d %a = %a\n", 0, 1.0, yn(0, 1.0)); /* S4 */
    printf("yn %d %a = %a\n", 1, 1.0, yn(1, 1.0)); /* S4 */
    printf("yn %d %a = %a\n", 2, 0x1p302, yn(2, 0x1p302)); /* R2 */
}

static void test_y0_extra(void)
{
    printf("y0 %a = %a\n", 5.0, y0(5.0)); /* R2 */
    printf("y0 %a = %a\n", 100.0, y0(100.0)); /* R2 */
    printf("y0 %a = %a\n", 0x1p302, y0(0x1p302)); /* R2 */
    printf("y0 %a = %a\n", 0.1, y0(0.1)); /* R2 */
    printf("y0 %a = %a\n", -0.5, y0(-0.5)); /* R2 */
}

static void test_y1_extra(void)
{
    printf("y1 %a = %a\n", 5.0, y1(5.0)); /* R2 */
    printf("y1 %a = %a\n", 100.0, y1(100.0)); /* R2 */
    printf("y1 %a = %a\n", 0x1p302, y1(0x1p302)); /* R2 */
    printf("y1 %a = %a\n", 0.1, y1(0.1)); /* R2 */
}

/* csqrt extra */
static void test_csqrt_extra(void)
{
    double complex z, w;
    z = CMPLX(4.0, 0x1p-1074);
    w = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(-4.0, 100.0);
    w = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(0x1p500, 0x1p500);
    w = csqrt(z);
    printf("csqrt large = %a+%ai\n", creal(w), cimag(w)); /* R2 */
    z = CMPLX(0.0, 4.0);
    w = csqrt(z);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(1e300, 1.0);
    w = csqrt(z);
    printf("csqrt large+1i = %a+%ai\n", creal(w), cimag(w)); /* R2 */
}

static void test_csqrtf_extra(void)
{
    float complex z, w;
    z = CMPLXF(-4.0f, 100.0f);
    w = csqrtf(z);
    printf("csqrtf %a+%ai = %a+%ai\n", (double)crealf(z), (double)cimagf(z), /* R2 */
           (double)crealf(w), (double)cimagf(w));
    z = CMPLXF(0x1p60f, 0x1p60f);
    w = csqrtf(z);
    printf("csqrtf large = %a+%ai\n", (double)crealf(w), (double)cimagf(w)); /* R2 */
    z = CMPLXF(0.0f, 4.0f);
    w = csqrtf(z);
    printf("csqrtf %a+%ai = %a+%ai\n", (double)crealf(z), (double)cimagf(z), /* R2 */
           (double)crealf(w), (double)cimagf(w));
}

/* ctan extra */
static void test_ctan_extra(void)
{
    double complex z, w;
    z = CMPLX(1.0, 100.0);
    w = ctan(z);
    printf("ctan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(1.0, -100.0);
    w = ctan(z);
    printf("ctan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(D_NAN, 1.0);
    w = ctan(z);
    printf("ctan nan+%ai = %a+%ai\n", cimag(z), creal(w), cimag(w)); /* R1 */
    z = CMPLX(1.0, D_INF);
    w = ctan(z);
    printf("ctan %a+infi = %a+%ai\n", creal(z), creal(w), cimag(w)); /* R1 */
    z = CMPLX(D_INF, 1.0);
    w = ctan(z);
    printf("ctan inf+%ai = %a+%ai\n", cimag(z), creal(w), cimag(w)); /* R2 */
    z = CMPLX(0.0, 0.0);
    w = ctan(z);
    printf("ctan %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
}

static void test_ctanf_extra(void)
{
    float complex z, w;
    z = CMPLXF(1.0f, 100.0f);
    w = ctanf(z);
    printf("ctanf %a+%ai = %a+%ai\n", (double)crealf(z), (double)cimagf(z), /* R2 */
           (double)crealf(w), (double)cimagf(w));
    z = CMPLXF(1.0f, -100.0f);
    w = ctanf(z);
    printf("ctanf %a+%ai = %a+%ai\n", (double)crealf(z), (double)cimagf(z), /* R2 */
           (double)crealf(w), (double)cimagf(w));
    z = CMPLXF(F_NAN, 1.0f);
    w = ctanf(z);
    printf("ctanf nan+%ai = %a+%ai\n", (double)cimagf(z), (double)crealf(w), (double)cimagf(w)); /* R2 */
    z = CMPLXF(1.0f, F_INF);
    w = ctanf(z);
    printf("ctanf %a+infi = %a+%ai\n", (double)crealf(z), (double)crealf(w), (double)cimagf(w)); /* R2 */
    z = CMPLXF(F_INF, 1.0f);
    w = ctanf(z);
    printf("ctanf inf+%ai = %a+%ai\n", (double)cimagf(z), (double)crealf(w), (double)cimagf(w)); /* R2 */
}

/* Complex trig extra (ctrigd.c / ctrigf.c) */
static void test_ctrig_extra(void)
{
    double complex z, w;
    z = CMPLX(1.0, 100.0);
    w = csin(z);
    printf("csin %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    w = ccos(z);
    printf("ccos %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(1.0, -100.0);
    w = csin(z);
    printf("csin %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(w), cimag(w)); /* S4 */
    z = CMPLX(D_INF, 1.0);
    w = csin(z);
    printf("csin inf+%ai = %a+%ai\n", cimag(z), creal(w), cimag(w)); /* R2 */
    z = CMPLX(1.0, D_INF);
    w = ccos(z);
    printf("ccos %a+infi = %a+%ai\n", creal(z), creal(w), cimag(w)); /* R2 */
    z = CMPLX(1000.0, 1.0);
    w = csin(z);
    printf("csin large real = %a+%ai\n", creal(w), cimag(w)); /* R2 */
}

static void test_ctrigf_extra(void)
{
    float complex z, w;
    z = CMPLXF(1.0f, 100.0f);
    w = csinf(z);
    printf("csinf %a+%ai = %a+%ai\n", (double)crealf(z), (double)cimagf(z), /* R2 */
           (double)crealf(w), (double)cimagf(w));
    w = ccosf(z);
    printf("ccosf %a+%ai = %a+%ai\n", (double)crealf(z), (double)cimagf(z), /* R2 */
           (double)crealf(w), (double)cimagf(w));
    z = CMPLXF(F_INF, 1.0f);
    w = csinf(z);
    printf("csinf inf+%ai = %a+%ai\n", (double)cimagf(z), (double)crealf(w), (double)cimagf(w)); /* R2 */
    z = CMPLXF(1.0f, F_INF);
    w = ccosf(z);
    printf("ccosf %a+infi = %a+%ai\n", (double)crealf(z), (double)crealf(w), (double)cimagf(w)); /* R2 */
}

/* fpclassify extra */
static void test_fpclassify_extra(void)
{
    /* SNaN: high exp bits set, mantissa nonzero only in low word */
    union { double d; uint64_t i; } u;
    u.i = 0x7FF0000000000001ULL;
    printf("__fpclassifyd snan = %d\n", __fpclassifyd(u.d)); /* R2 */
    printf("__fpclassifyd inf = %d\n", __fpclassifyd(D_INF)); /* R2 */
    printf("__fpclassifyd -inf = %d\n", __fpclassifyd(D_NINF)); /* R1 */
    printf("__fpclassifyd -0 = %d\n", __fpclassifyd(-0.0)); /* R1 */
}

/* atand extra: SNaN with ix=0x7ff00000 and low!=0 */
static void test_atand_extra(void)
{
    union { double d; uint64_t i; } u;
    u.i = 0x7FF0000000000001ULL;
    printf("atan snan = %a\n", atan(u.d)); /* R2 */
}

/* ------------------------------------------------------------------ */
/* Branch coverage round 5 — targeted edge cases                       */
/* ------------------------------------------------------------------ */

/* ---- ceil ---- */
static void test_ceil_extra2(void)
{
    /* j0 < 0: |x| < 1 */
    printf("ceil %a = %a\n", 0.0,  ceil(0.0)); /* R3 */
    printf("ceil %a = %a\n", 0.5,  ceil(0.5)); /* R3 */
    printf("ceil %a = %a\n", -0.5, ceil(-0.5)); /* R1 */
    /* j0 in [0,20): |x| in [1, 2^20) */
    printf("ceil %a = %a\n", 2.0,  ceil(2.0)); /* R3 */
    printf("ceil %a = %a\n", 1.5,  ceil(1.5)); /* R3 */
    printf("ceil %a = %a\n", -1.5, ceil(-1.5)); /* R1 */
    printf("ceil %a = %a\n", 1.75, ceil(1.75)); /* R3 */
    printf("ceil %a = %a\n", -1.75, ceil(-1.75)); /* R3 */
    /* j0 > 51 */
    printf("ceil %a = %a\n", 1.0e16, ceil(1.0e16)); /* R3 */
    printf("ceil %a = %a\n", D_INF,  ceil(D_INF)); /* R3 */
    printf("ceil %a = %a\n", D_NAN,  ceil(D_NAN)); /* R3 */
    /* j0 in [20,51]: |x| in [2^20, 2^52) */
    printf("ceil %a = %a\n", 1048576.0,  ceil(1048576.0)); /* R3 */
    printf("ceil %a = %a\n", 1048576.5,  ceil(1048576.5)); /* R3 */
    printf("ceil %a = %a\n", -1048576.5, ceil(-1048576.5)); /* R3 */
    printf("ceil %a = %a\n", 2097152.5,  ceil(2097152.5)); /* R3 */
    /* j0=21, carry: _i1 has bit 31 set → j overflows uint32 */
    union { double d; uint64_t u; } _cu;
    _cu.u = 0x41400000c0000001ULL;
    printf("ceil carry = %a\n", ceil(_cu.d)); /* R3 */
}

static void test_ceilf_extra2(void)
{
    printf("ceilf %a = %a\n", 0.0,  (double)ceilf(0.0f)); /* R3 */
    printf("ceilf %a = %a\n", 0.5,  (double)ceilf(0.5f)); /* R3 */
    printf("ceilf %a = %a\n", -0.5, (double)ceilf(-0.5f)); /* R3 */
    printf("ceilf %a = %a\n", 2.0,  (double)ceilf(2.0f)); /* R3 */
    printf("ceilf %a = %a\n", 1.5,  (double)ceilf(1.5f)); /* R3 */
    printf("ceilf %a = %a\n", -1.5, (double)ceilf(-1.5f)); /* R3 */
    printf("ceilf %a = %a\n", (double)1.0e7f,    (double)ceilf(1.0e7f)); /* R3 */
    printf("ceilf %a = %a\n", (double)8388608.5f,(double)ceilf(8388608.5f)); /* R3 */
    printf("ceilf %a = %a\n", (double)F_INF,     (double)ceilf(F_INF)); /* R3 */
    printf("ceilf %a = %a\n", (double)F_NAN,     (double)ceilf(F_NAN)); /* R3 */
}

/* ---- floor ---- */
static void test_floor_extra2(void)
{
    printf("floor %a = %a\n", 0.0,  floor(0.0)); /* R3 */
    printf("floor %a = %a\n", 0.5,  floor(0.5)); /* R3 */
    printf("floor %a = %a\n", -0.5, floor(-0.5)); /* R3 */
    printf("floor %a = %a\n", 2.0,  floor(2.0)); /* R3 */
    printf("floor %a = %a\n", 1.5,  floor(1.5)); /* R3 */
    printf("floor %a = %a\n", -1.5, floor(-1.5)); /* R1 */
    printf("floor %a = %a\n", -1.75, floor(-1.75)); /* R3 */
    printf("floor %a = %a\n", 1.0e16, floor(1.0e16)); /* R3 */
    printf("floor %a = %a\n", D_INF,  floor(D_INF)); /* R3 */
    printf("floor %a = %a\n", 1048576.0,  floor(1048576.0)); /* R3 */
    printf("floor %a = %a\n", 1048576.5,  floor(1048576.5)); /* R3 */
    printf("floor %a = %a\n", -1048576.5, floor(-1048576.5)); /* R3 */
    printf("floor %a = %a\n", 2097152.5,  floor(2097152.5)); /* R3 */
    /* negative, j0=21, carry: hx<0, _i1 has bit 31 set */
    union { double d; uint64_t u; } _fu;
    _fu.u = 0xC1400000c0000001ULL;
    printf("floor carry neg = %a\n", floor(_fu.d)); /* R3 */
}

static void test_floorf_extra2(void)
{
    printf("floorf %a = %a\n", (double)0.5f,      (double)floorf(0.5f)); /* R3 */
    printf("floorf %a = %a\n", (double)-0.5f,     (double)floorf(-0.5f)); /* R3 */
    printf("floorf %a = %a\n", (double)1.5f,      (double)floorf(1.5f)); /* R3 */
    printf("floorf %a = %a\n", (double)-1.5f,     (double)floorf(-1.5f)); /* R3 */
    printf("floorf %a = %a\n", (double)2.0f,      (double)floorf(2.0f)); /* R3 */
    printf("floorf %a = %a\n", (double)1.0e7f,    (double)floorf(1.0e7f)); /* R3 */
    printf("floorf %a = %a\n", (double)8388607.5f,(double)floorf(8388607.5f)); /* R3 */
    printf("floorf %a = %a\n", (double)F_INF,     (double)floorf(F_INF)); /* R3 */
}

/* ---- trunc ---- */
static void test_trunc_extra2(void)
{
    printf("trunc %a = %a\n", 0.5,    trunc(0.5)); /* R3 */
    printf("trunc %a = %a\n", -0.5,   trunc(-0.5)); /* R3 */
    printf("trunc %a = %a\n", 1.5,    trunc(1.5)); /* R3 */
    printf("trunc %a = %a\n", -1.5,   trunc(-1.5)); /* R3 */
    printf("trunc %a = %a\n", 1.0e16, trunc(1.0e16)); /* R3 */
    printf("trunc %a = %a\n", D_INF,  trunc(D_INF)); /* R3 */
    printf("trunc %a = %a\n", D_NAN,  trunc(D_NAN)); /* R3 */
    printf("trunc %a = %a\n", 1048576.5,  trunc(1048576.5)); /* R3 */
    printf("trunc %a = %a\n", -1048576.5, trunc(-1048576.5)); /* R3 */
}

static void test_truncf_extra2(void)
{
    printf("truncf %a = %a\n", (double)0.5f,   (double)truncf(0.5f)); /* R3 */
    printf("truncf %a = %a\n", (double)-0.5f,  (double)truncf(-0.5f)); /* R3 */
    printf("truncf %a = %a\n", (double)1.5f,   (double)truncf(1.5f)); /* R3 */
    printf("truncf %a = %a\n", (double)-1.5f,  (double)truncf(-1.5f)); /* R3 */
    printf("truncf %a = %a\n", (double)1.0e7f, (double)truncf(1.0e7f)); /* R3 */
    printf("truncf %a = %a\n", (double)F_INF,  (double)truncf(F_INF)); /* R3 */
    printf("truncf %a = %a\n", (double)F_NAN,  (double)truncf(F_NAN)); /* R3 */
}

/* ---- modf ---- */
static void test_modf_extra2(void)
{
    double ip;
    float fip;
    printf("modf %a = %a ip=%a\n", 0.5,    modf(0.5, &ip),    ip); /* R3 */
    printf("modf %a = %a ip=%a\n", -0.5,   modf(-0.5, &ip),   ip); /* R3 */
    printf("modf %a = %a ip=%a\n", 2.0,    modf(2.0, &ip),    ip); /* R3 */
    printf("modf %a = %a ip=%a\n", 1.5,    modf(1.5, &ip),    ip); /* R3 */
    printf("modf %a = %a ip=%a\n", 1.0e16, modf(1.0e16, &ip), ip); /* R3 */
    printf("modf %a = %a ip=%a\n", D_NAN,  modf(D_NAN, &ip),  ip); /* R3 */
    printf("modf %a = %a ip=%a\n", 1048576.0, modf(1048576.0, &ip), ip); /* R3 */
    printf("modf %a = %a ip=%a\n", 1048576.5, modf(1048576.5, &ip), ip); /* R3 */
    printf("modff %a = %a ip=%a\n", (double)0.5f,   (double)modff(0.5f,   &fip), (double)fip); /* R3 */
    printf("modff %a = %a ip=%a\n", (double)-0.5f,  (double)modff(-0.5f,  &fip), (double)fip); /* R3 */
    printf("modff %a = %a ip=%a\n", (double)2.0f,   (double)modff(2.0f,   &fip), (double)fip); /* R3 */
    printf("modff %a = %a ip=%a\n", (double)1.5f,   (double)modff(1.5f,   &fip), (double)fip); /* R3 */
    printf("modff %a = %a ip=%a\n", (double)3.0f,   (double)modff(3.0f,   &fip), (double)fip); /* R3 */
    printf("modff %a = %a ip=%a\n", (double)F_NAN,  (double)modff(F_NAN,  &fip), (double)fip); /* R3 */
    printf("modff %a = %a ip=%a\n", (double)1.0e7f, (double)modff(1.0e7f, &fip), (double)fip); /* R3 */
}

/* ---- frexp ---- */
static void test_frexp_extra2(void)
{
    int e;
    double r;
    float rf;
    /* subnormal with lx only (hx=0): D_SUBNORM → (84:5) True, (85:8) True */
    r = frexp(D_SUBNORM, &e);
    printf("frexp D_SUBNORM = %a exp=%d\n", r, e); /* R3 */
    /* subnormal with hx!=0: 2^-1023, hx=0x00080000 */
    double _sub2 = 1.1125369292536007e-308;
    r = frexp(_sub2, &e);
    printf("frexp subnorm-hi = %a exp=%d\n", r, e); /* R3 */
    /* normal → (84:5) False */
    r = frexp(1.5, &e);
    printf("frexp 1.5 = %a exp=%d\n", r, e); /* R3 */
    /* frexpf: subnormal */
    rf = frexpf(F_SUBNORM, &e);
    printf("frexpf F_SUBNORM = %a exp=%d\n", (double)rf, e); /* R3 */
    rf = frexpf(1.5f, &e);
    printf("frexpf 1.5 = %a exp=%d\n", (double)rf, e); /* R3 */
    /* subnormal float with hx!=0: exponent=0, mantissa high bit set */
    union { float f; uint32_t u; } _sf2;
    _sf2.u = 0x00400000U;
    rf = frexpf(_sf2.f, &e);
    printf("frexpf subnorm-hi = %a exp=%d\n", (double)rf, e); /* R3 */
}

/* ---- nextafter ---- */
static void test_nextafter_extra2(void)
{
    /* x==0 paths */
    printf("nextafter 0 1 = %a\n",  nextafter(0.0, 1.0)); /* R3 */
    printf("nextafter 0 -1 = %a\n", nextafter(0.0, -1.0)); /* R3 */
    /* x>0, x>y */
    printf("nextafter 2 1 = %a\n",  nextafter(2.0, 1.0)); /* R3 */
    /* x>0, x<y */
    printf("nextafter 1 2 = %a\n",  nextafter(1.0, 2.0)); /* R3 */
    /* x<0 paths */
    printf("nextafter -1 0 = %a\n",  nextafter(-1.0, 0.0)); /* R3 */
    printf("nextafter -1 -2 = %a\n", nextafter(-1.0, -2.0)); /* R3 */
    printf("nextafter -2 -1 = %a\n", nextafter(-2.0, -1.0)); /* R3 */
    /* overflow: max double toward +inf */
    printf("nextafter max +inf = %a\n", /* R3 */
           nextafter(1.7976931348623157e308, D_INF));
    /* nextafterf */
    printf("nextafterf 0 1 = %a\n",   (double)nextafterf(0.0f, 1.0f)); /* R3 */
    printf("nextafterf 0 -1 = %a\n",  (double)nextafterf(0.0f, -1.0f)); /* R3 */
    printf("nextafterf 2 1 = %a\n",   (double)nextafterf(2.0f, 1.0f)); /* R3 */
    printf("nextafterf -1 0 = %a\n",  (double)nextafterf(-1.0f, 0.0f)); /* R3 */
    printf("nextafterf -1 -2 = %a\n", (double)nextafterf(-1.0f, -2.0f)); /* R3 */
    printf("nextafterf max +inf = %a\n", /* R3 */
           (double)nextafterf(3.4028235e38f, F_INF));
}

/* ---- scalbn / scalbln ---- */
static void test_scalbn_extra2(void)
{
    printf("scalbn 1 50001 = %a\n",  scalbn(1.0, 50001)); /* R3 */
    printf("scalbn 1 -50001 = %a\n", scalbn(1.0, -50001)); /* R3 */
    printf("scalbn 2 1024 = %a\n",   scalbn(2.0, 1024)); /* R3 */
    printf("scalbn 2 -1075 = %a\n",  scalbn(2.0, -1075)); /* R3 */
    printf("scalbnf 1 50001 = %a\n",  (double)scalbnf(1.0f, 50001)); /* R3 */
    printf("scalbnf 1 -50001 = %a\n", (double)scalbnf(1.0f, -50001)); /* R3 */
    printf("scalbnf 2 200 = %a\n",    (double)scalbnf(2.0f, 200)); /* R3 */
    printf("scalbnf 2 -200 = %a\n",   (double)scalbnf(2.0f, -200)); /* R3 */
}

static void test_scalbln_extra2(void)
{
    printf("scalbln 1 50001 = %a\n",   scalbln(1.0, 50001L)); /* R3 */
    printf("scalbln 1 -50001 = %a\n",  scalbln(1.0, -50001L)); /* R3 */
    printf("scalbln 2 1024 = %a\n",    scalbln(2.0, 1024L)); /* R3 */
    printf("scalbln 2 -1075 = %a\n",   scalbln(2.0, -1075L)); /* R3 */
    printf("scalblnf 1 50001 = %a\n",  (double)scalblnf(1.0f, 50001L)); /* R3 */
    printf("scalblnf 1 -50001 = %a\n", (double)scalblnf(1.0f, -50001L)); /* R3 */
    printf("scalblnf 2 200 = %a\n",    (double)scalblnf(2.0f, 200L)); /* R3 */
    printf("scalblnf 2 -200 = %a\n",   (double)scalblnf(2.0f, -200L)); /* R3 */
}

/* ---- rint ---- */
static void test_rint_extra2(void)
{
    /* j0 < 0: |x| < 0.5 */
    printf("rint %a = %a\n", 0.3,  rint(0.3)); /* R3 */
    printf("rint %a = %a\n", -0.3, rint(-0.3)); /* R2 */
    /* j0 in [0,20): 2nd bit after radix set → (99:17) True */
    printf("rint %a = %a\n", 1.75, rint(1.75)); /* R3 */
    printf("rint %a = %a\n", 1.5,  rint(1.5)); /* R3 */
    printf("rint %a = %a\n", 2.0,  rint(2.0)); /* R3 */
    /* j0 == 19: → (101:21) True */
    printf("rint %a = %a\n", 524288.1,  rint(524288.1)); /* R3 */
    printf("rint %a = %a\n", -524288.1, rint(-524288.1)); /* R3 */
    /* j0 > 51 */
    printf("rint %a = %a\n", 1.0e16, rint(1.0e16)); /* R3 */
    printf("rint %a = %a\n", D_INF,  rint(D_INF)); /* R3 */
    /* j0 in [20,51]: integral → (119:13) True */
    printf("rint %a = %a\n", 1048576.0, rint(1048576.0)); /* R3 */
    /* j0 in [20,51]: non-integral, 2nd bit → (125:13) True */
    printf("rint %a = %a\n", 1048576.75, rint(1048576.75)); /* R3 */
    printf("rint %a = %a\n", 1048576.5,  rint(1048576.5)); /* R3 */
    /* rintf */
    printf("rintf %a = %a\n", (double)0.3f,       (double)rintf(0.3f)); /* R3 */
    printf("rintf %a = %a\n", (double)1.75f,      (double)rintf(1.75f)); /* R3 */
    printf("rintf %a = %a\n", (double)1.0e7f,     (double)rintf(1.0e7f)); /* R3 */
    printf("rintf %a = %a\n", (double)8388608.5f, (double)rintf(8388608.5f)); /* R3 */
}

/* ---- round ---- */
static void test_round_extra2(void)
{
    printf("round %a = %a\n", 0.4,  round(0.4)); /* R3 */
    printf("round %a = %a\n", 0.5,  round(0.5)); /* R3 */
    printf("round %a = %a\n", -0.5, round(-0.5)); /* R3 */
    printf("round %a = %a\n", 1.5,  round(1.5)); /* R3 */
    printf("round %a = %a\n", -1.5, round(-1.5)); /* S4 */
    printf("round %a = %a\n", 2.0,  round(2.0)); /* R3 */
    printf("round %a = %a\n", 1.0e16, round(1.0e16)); /* R3 */
    printf("round %a = %a\n", D_INF,  round(D_INF)); /* R3 */
    printf("round %a = %a\n", 1048576.3, round(1048576.3)); /* R3 */
    printf("round %a = %a\n", 1048576.7, round(1048576.7)); /* R3 */
    printf("roundf %a = %a\n", (double)0.5f,  (double)roundf(0.5f)); /* R3 */
    printf("roundf %a = %a\n", (double)-0.5f, (double)roundf(-0.5f)); /* R3 */
    printf("roundf %a = %a\n", (double)1.5f,  (double)roundf(1.5f)); /* R3 */
    printf("roundf %a = %a\n", (double)2.0f,  (double)roundf(2.0f)); /* R3 */
}

/* ---- lrint / lround ---- */
static void test_lrint_extra2(void)
{
    printf("lrint %a = %ld\n", 0.3,  lrint(0.3)); /* R3 */
    printf("lrint %a = %ld\n", -0.3, lrint(-0.3)); /* R3 */
    printf("lrint %a = %ld\n", 1.5,  lrint(1.5)); /* R3 */
    printf("lrint %a = %ld\n", 1048576.5, lrint(1048576.5)); /* R3 */
    /* overflow negative → (140:13) True */
    printf("lrint 1e19 = %ld\n",  lrint(1.0e19)); /* R3 */
    printf("lrint -1e19 = %ld\n", lrint(-1.0e19)); /* R3 */
    printf("lrintf %a = %ld\n",  (double)0.3f, (long)lrintf(0.3f)); /* R3 */
    printf("lrintf %a = %ld\n",  (double)1.5f, (long)lrintf(1.5f)); /* R3 */
    printf("lrintf 1e10 = %ld\n",  (long)lrintf(1.0e10f)); /* R3 */
    printf("lrintf -1e10 = %ld\n", (long)lrintf(-1.0e10f)); /* R3 */
}

static void test_lround_extra2(void)
{
    /* exponent in [20,51] → (96:13) False */
    printf("lround %a = %ld\n", 1048576.7, lround(1048576.7)); /* R3 */
    printf("lround %a = %ld\n", 1048576.3, lround(1048576.3)); /* R3 */
    /* carry case */
    union { double d; uint64_t u; } _lru;
    _lru.u = 0x41400000c0000001ULL;
    printf("lround carry = %ld\n", lround(_lru.d)); /* R3 */
    /* overflow */
    printf("lround 1e19 = %ld\n",  lround(1.0e19)); /* R3 */
    printf("lround -1e19 = %ld\n", lround(-1.0e19)); /* R3 */
    printf("lroundf %a = %ld\n",   (double)1.5f,  (long)lroundf(1.5f)); /* R3 */
    printf("lroundf 1e10 = %ld\n", (long)lroundf(1.0e10f)); /* R3 */
    printf("lroundf -1e10 = %ld\n",(long)lroundf(-1.0e10f)); /* R3 */
}

/* ---- llrint / llround ---- */
static void test_llrint_extra2(void)
{
    printf("llrint %a = %lld\n", 0.3,  llrint(0.3)); /* R3 */
    printf("llrint %a = %lld\n", -0.3, llrint(-0.3)); /* R3 */
    printf("llrint %a = %lld\n", 1.5,  llrint(1.5)); /* R3 */
    printf("llrint %a = %lld\n", 1048576.5, llrint(1048576.5)); /* R3 */
    printf("llrint 1e19 = %lld\n",  llrint(1.0e19)); /* R3 */
    printf("llrint -1e19 = %lld\n", llrint(-1.0e19)); /* R3 */
    printf("llrintf %a = %lld\n",  (double)0.3f,  (long long)llrintf(0.3f)); /* R3 */
    printf("llrintf %a = %lld\n",  (double)1.5f,  (long long)llrintf(1.5f)); /* R3 */
    printf("llrintf 1e10 = %lld\n",  (long long)llrintf(1.0e10f)); /* R3 */
    printf("llrintf -1e10 = %lld\n", (long long)llrintf(-1.0e10f)); /* R3 */
}

static void test_llround_extra2(void)
{
    /* carry: exponent [20,51], lsw overflows when rounded → (107:17) True */
    union { double d; uint64_t u; } _llru;
    _llru.u = 0x41400000c0000001ULL;
    printf("llround carry = %lld\n", llround(_llru.d)); /* R3 */
    printf("llround %a = %lld\n",   1048576.7, llround(1048576.7)); /* R3 */
    /* overflow negative → (118:13) True */
    printf("llround -1e19 = %lld\n", llround(-1.0e19)); /* R3 */
    printf("llround 1e19 = %lld\n",  llround(1.0e19)); /* R3 */
    printf("llroundf %a = %lld\n",  (double)1.5f,  (long long)llroundf(1.5f)); /* R3 */
    printf("llroundf -1e10 = %lld\n",(long long)llroundf(-1.0e10f)); /* R3 */
    printf("llroundf 1e10 = %lld\n", (long long)llroundf(1.0e10f)); /* R3 */
}

/* ---- fmax / fmin ---- */
static void test_fmax_extra2(void)
{
    union { double d; uint64_t u; } _snand, _snan2d, _qnand;
    _snand.u  = 0x7FF0000000000001ULL;
    _snan2d.u = 0x7FF0000000000002ULL;
    _qnand.u  = 0x7FF8000000000001ULL;
    /* isnan(x), at least one signaling → (75:13) True */
    printf("fmax snan snan = %a\n", fmax(_snand.d, _snan2d.d)); /* R3 */
    /* isnan(x), x quiet but y signaling → (75:38) True */
    printf("fmax qnan snan = %a\n", fmax(_qnand.d, _snand.d)); /* R3 */
    /* isnan(x), neither signaling → (75:13) False */
    printf("fmax qnan 1 = %a\n",    fmax(_qnand.d, 1.0)); /* R3 */
    /* isnan(y), y signaling → (85:13) True */
    printf("fmax 1 snan = %a\n",    fmax(1.0, _snand.d)); /* R3 */
    /* isnan(y), y quiet → (85:13) False */
    printf("fmax 1 qnan = %a\n",    fmax(1.0, _qnand.d)); /* R3 */
    /* no NaN: x > y → (99:12) True */
    printf("fmax 2 1 = %a\n",       fmax(2.0, 1.0)); /* R3 */
    /* x <= y → (99:12) False */
    printf("fmax 1 2 = %a\n",       fmax(1.0, 2.0)); /* R3 */
    /* fmaxf */
    union { float f; uint32_t u; } _snanf, _snan2f, _qnanf;
    _snanf.u  = 0x7F800001U;
    _snan2f.u = 0x7F800002U;
    _qnanf.u  = 0x7FC00001U;
    printf("fmaxf snan snan = %a\n", (double)fmaxf(_snanf.f, _snan2f.f)); /* R3 */
    printf("fmaxf qnan snan = %a\n", (double)fmaxf(_qnanf.f, _snanf.f)); /* R3 */
    printf("fmaxf qnan 1 = %a\n",    (double)fmaxf(_qnanf.f, 1.0f)); /* R3 */
    printf("fmaxf 1 snan = %a\n",    (double)fmaxf(1.0f, _snanf.f)); /* R3 */
    printf("fmaxf 1 qnan = %a\n",    (double)fmaxf(1.0f, _qnanf.f)); /* R3 */
    printf("fmaxf 2 1 = %a\n",       (double)fmaxf(2.0f, 1.0f)); /* R3 */
    printf("fmaxf 1 2 = %a\n",       (double)fmaxf(1.0f, 2.0f)); /* R3 */
}

static void test_fmin_extra2(void)
{
    union { double d; uint64_t u; } _snand, _snan2d, _qnand;
    _snand.u  = 0x7FF0000000000001ULL;
    _snan2d.u = 0x7FF0000000000002ULL;
    _qnand.u  = 0x7FF8000000000001ULL;
    printf("fmin snan snan = %a\n", fmin(_snand.d, _snan2d.d)); /* R3 */
    printf("fmin qnan snan = %a\n", fmin(_qnand.d, _snand.d)); /* R3 */
    printf("fmin qnan 1 = %a\n",    fmin(_qnand.d, 1.0)); /* R3 */
    printf("fmin 1 snan = %a\n",    fmin(1.0, _snand.d)); /* R3 */
    printf("fmin 1 qnan = %a\n",    fmin(1.0, _qnand.d)); /* R3 */
    printf("fmin 2 1 = %a\n",       fmin(2.0, 1.0)); /* R3 */
    printf("fmin 1 2 = %a\n",       fmin(1.0, 2.0)); /* R3 */
    union { float f; uint32_t u; } _snanf, _snan2f, _qnanf;
    _snanf.u  = 0x7F800001U;
    _snan2f.u = 0x7F800002U;
    _qnanf.u  = 0x7FC00001U;
    printf("fminf snan snan = %a\n", (double)fminf(_snanf.f, _snan2f.f)); /* R3 */
    printf("fminf qnan snan = %a\n", (double)fminf(_qnanf.f, _snanf.f)); /* R3 */
    printf("fminf qnan 1 = %a\n",    (double)fminf(_qnanf.f, 1.0f)); /* R3 */
    printf("fminf 1 snan = %a\n",    (double)fminf(1.0f, _snanf.f)); /* R3 */
    printf("fminf 1 qnan = %a\n",    (double)fminf(1.0f, _qnanf.f)); /* R3 */
    printf("fminf 2 1 = %a\n",       (double)fminf(2.0f, 1.0f)); /* R3 */
    printf("fminf 1 2 = %a\n",       (double)fminf(1.0f, 2.0f)); /* R3 */
}

/* ---- fmod ---- */
static void test_fmod_extra2(void)
{
    printf("fmod 1.5 1 = %a\n",      fmod(1.5, 1.0)); /* R3 */
    printf("fmod -1.5 1 = %a\n",     fmod(-1.5, 1.0)); /* R3 */
    printf("fmod 5 3 = %a\n",        fmod(5.0, 3.0)); /* R3 */
    printf("fmod 1e20 3 = %a\n",     fmod(1.0e20, 3.0)); /* R3 */
    printf("fmod 1e-5 1e-10 = %a\n", fmod(1.0e-5, 1.0e-10)); /* R3 */
    printf("fmod 0 1 = %a\n",        fmod(0.0, 1.0)); /* R3 */
    printf("fmod 1 0 = %a\n",        fmod(1.0, 0.0)); /* R3 */
    printf("fmod inf 1 = %a\n",      fmod(D_INF, 1.0)); /* R3 */
    printf("fmod 1 inf = %a\n",      fmod(1.0, D_INF)); /* R3 */
    printf("fmod 5.5 2.5 = %a\n",    fmod(5.5, 2.5)); /* R3 */
    printf("fmod 1e-320 5e-324 = %a\n", fmod(1.0e-320, 5e-324)); /* R3 */
    printf("fmodf 5 3 = %a\n",   (double)fmodf(5.0f, 3.0f)); /* R3 */
    printf("fmodf -5 3 = %a\n",  (double)fmodf(-5.0f, 3.0f)); /* R3 */
    printf("fmodf 1e6 7 = %a\n", (double)fmodf(1.0e6f, 7.0f)); /* R3 */
    printf("fmodf 0 1 = %a\n",   (double)fmodf(0.0f, 1.0f)); /* R3 */
    printf("fmodf 1 0 = %a\n",   (double)fmodf(1.0f, 0.0f)); /* R3 */
    printf("fmodf inf 1 = %a\n", (double)fmodf(F_INF, 1.0f)); /* R3 */
    printf("fmodf 1 inf = %a\n", (double)fmodf(1.0f, F_INF)); /* R3 */
}

/* ---- remainder / remquo ---- */
static void test_remainder_extra2(void)
{
    printf("remainder 5 3 = %a\n",   remainder(5.0, 3.0)); /* R3 */
    printf("remainder 5 2 = %a\n",   remainder(5.0, 2.0)); /* R3 */
    printf("remainder -5 3 = %a\n",  remainder(-5.0, 3.0)); /* R3 */
    printf("remainder 5.5 2 = %a\n", remainder(5.5, 2.0)); /* R3 */
    printf("remainder 4 2 = %a\n",   remainder(4.0, 2.0)); /* R3 */
    /* hy small: subnormal y */
    printf("remainder 1e-300 1e-316 = %a\n", remainder(1.0e-300, 1.0e-316)); /* R3 */
    printf("remainderf 5 3 = %a\n",   (double)remainderf(5.0f, 3.0f)); /* R3 */
    printf("remainderf 5 2 = %a\n",   (double)remainderf(5.0f, 2.0f)); /* R3 */
    printf("remainderf -5 2 = %a\n",  (double)remainderf(-5.0f, 2.0f)); /* R3 */
    printf("remainderf 4 2 = %a\n",   (double)remainderf(4.0f, 2.0f)); /* R3 */
    printf("remainderf 1 0 = %a\n",   (double)remainderf(1.0f, 0.0f)); /* R3 */
}

static void test_remquo_extra2(void)
{
    int q;
    printf("remquo 5 3 = %a q=%d\n",  remquo(5.0, 3.0, &q), q); /* R3 */
    printf("remquo 5 2 = %a q=%d\n",  remquo(5.0, 2.0, &q), q); /* R3 */
    printf("remquo -5 3 = %a q=%d\n", remquo(-5.0, 3.0, &q), q); /* R3 */
    printf("remquo 1e-300 1e-316 = %a q=%d\n", remquo(1.0e-300, 1.0e-316, &q), q); /* R3 */
    printf("remquof 5 3 = %a q=%d\n",  (double)remquof(5.0f, 3.0f, &q), q); /* R3 */
    printf("remquof 5 2 = %a q=%d\n",  (double)remquof(5.0f, 2.0f, &q), q); /* R3 */
    printf("remquof -5 3 = %a q=%d\n", (double)remquof(-5.0f, 3.0f, &q), q); /* R3 */
    printf("remquof 4 2 = %a q=%d\n",  (double)remquof(4.0f, 2.0f, &q), q); /* R3 */
}

/* ---- sqrt ---- */
static void test_sqrt_extra2(void)
{
    /* subnormal with ix1 only (ix0=0) */
    printf("sqrt D_SUBNORM = %a\n", sqrt(D_SUBNORM)); /* R3 */
    union { double d; uint64_t u; } _sq;
    _sq.u = 0x0000000000000001ULL;
    printf("sqrt tiny subnorm = %a\n", sqrt(_sq.d)); /* R3 */
    printf("sqrt 2 = %a\n",   sqrt(2.0)); /* R3 */
    printf("sqrt 3 = %a\n",   sqrt(3.0)); /* R3 */
    printf("sqrt 0.5 = %a\n", sqrt(0.5)); /* R3 */
    /* sqrtf */
    printf("sqrtf F_SUBNORM = %a\n", (double)sqrtf(F_SUBNORM)); /* R3 */
    union { float f; uint32_t u; } _sqf;
    _sqf.u = 0x00000001U;
    printf("sqrtf tiny subnorm = %a\n", (double)sqrtf(_sqf.f)); /* R3 */
}

/* ---- hypot ---- */
static void test_hypot_extra2(void)
{
    /* ha > 2^500, not Inf/NaN → scale down */
    printf("hypot 1e200 1e200 = %a\n", hypot(1.0e200, 1.0e200)); /* R3 */
    /* Inf */
    printf("hypot inf 1 = %a\n",       hypot(D_INF, 1.0)); /* R3 */
    printf("hypot 1 inf = %a\n",       hypot(1.0, D_INF)); /* R3 */
    /* hb < 2^-500: b very small */
    printf("hypot 1 1e-320 = %a\n",    hypot(1.0, 1.0e-320)); /* R3 */
    printf("hypot 1 0 = %a\n",         hypot(1.0, 0.0)); /* R3 */
    printf("hypot 1e155 1e155 = %a\n", hypot(1.0e155, 1.0e155)); /* R3 */
    /* hypotf: large → scale */
    printf("hypotf 1e20 1e20 = %a\n",  (double)hypotf(1.0e20f, 1.0e20f)); /* R3 */
    printf("hypotf 1e-30 1e-30 = %a\n",(double)hypotf(1.0e-30f, 1.0e-30f)); /* R3 */
}

/* ---- sinh / cosh threshold ---- */
static void test_sinh_extra2(void)
{
    /* |x| in [22, log(maxdouble)] */
    printf("sinh 22.5 = %a\n",  sinh(22.5)); /* R3 */
    printf("sinh 709.5 = %a\n", sinh(709.5)); /* R3 */
    /* near exact overflow threshold: ix=0x408633CE */
    union { double d; uint64_t u; } _sh;
    _sh.u = 0x408633CE8fb9f87dULL;
    printf("sinh at-thresh = %a\n", sinh(_sh.d)); /* R3 */
    _sh.u = 0x408633CE8fb9f87eULL;
    printf("sinh above-thresh = %a\n", sinh(_sh.d)); /* R3 */
    /* sinhf */
    printf("sinhf 89 = %a\n",  (double)sinhf(89.0f)); /* R3 */
    printf("sinhf -89 = %a\n", (double)sinhf(-89.0f)); /* R3 */
    printf("sinhf 10 = %a\n",  (double)sinhf(10.0f)); /* R3 */
}

static void test_cosh_extra2(void)
{
    printf("cosh 709.5 = %a\n",  cosh(709.5)); /* R3 */
    printf("cosh -709.5 = %a\n", cosh(-709.5)); /* R3 */
    printf("cosh 709.89 = %a\n", cosh(709.89)); /* R3 */
    printf("cosh 710.5 = %a\n",  cosh(710.5)); /* R3 */
    union { double d; uint64_t u; } _ch;
    _ch.u = 0x408633CE8fb9f87dULL;
    printf("cosh at-thresh = %a\n", cosh(_ch.d)); /* R3 */
    _ch.u = 0x408633CE8fb9f87eULL;
    printf("cosh above-thresh = %a\n", cosh(_ch.d)); /* R3 */
}

/* ---- log variants ---- */
static void test_log_extra2(void)
{
    /* k != 0: x not in (0.5, 2) */
    printf("log 4 = %a\n",       log(4.0)); /* R3 */
    printf("log 0.1 = %a\n",     log(0.1)); /* R3 */
    printf("log subnorm = %a\n",  log(D_SUBNORM)); /* R3 */
    printf("logf 4 = %a\n",      (double)logf(4.0f)); /* R3 */
    printf("logf 0.1 = %a\n",    (double)logf(0.1f)); /* R3 */
    printf("logf 0.9 = %a\n",    (double)logf(0.9f)); /* R3 */
    printf("logf 1.1 = %a\n",    (double)logf(1.1f)); /* R3 */
    printf("logf subnorm = %a\n", (double)logf(F_SUBNORM)); /* R3 */
    /* log10 */
    printf("log10 subnorm = %a\n",   log10(D_SUBNORM)); /* R3 */
    printf("log10 1e-5 = %a\n",      log10(1.0e-5)); /* R3 */
    printf("log10f subnorm = %a\n",  (double)log10f(F_SUBNORM)); /* R3 */
    printf("log10f 1e-5 = %a\n",     (double)log10f(1.0e-5f)); /* R3 */
    /* log1p */
    printf("log1p -0.9 = %a\n",      log1p(-0.9)); /* R3 */
    printf("log1p 1e-20 = %a\n",     log1p(1.0e-20)); /* R3 */
    printf("log1p 2 = %a\n",         log1p(2.0)); /* R3 */
    printf("log1pf -0.9 = %a\n",     (double)log1pf(-0.9f)); /* R3 */
    printf("log1pf 1e-10 = %a\n",    (double)log1pf(1.0e-10f)); /* R3 */
    printf("log1pf 2 = %a\n",        (double)log1pf(2.0f)); /* R3 */
    /* log2 */
    printf("log2 subnorm = %a\n",    log2(D_SUBNORM)); /* R3 */
    printf("log2 0.5 = %a\n",        log2(0.5)); /* R3 */
    printf("log2f subnorm = %a\n",   (double)log2f(F_SUBNORM)); /* R3 */
    printf("log2f 0.5 = %a\n",       (double)log2f(0.5f)); /* R3 */
}

static void test_logb_extra2(void)
{
    /* subnormal with hx==0 (all bits in lx) → (75:17) True */
    printf("logb D_SUBNORM = %a\n",  logb(D_SUBNORM)); /* R3 */
    /* subnormal with hx!=0: 2^-1023 → (75:17) False */
    double _sub2 = 1.1125369292536007e-308;
    printf("logb subnorm-hi = %a\n", logb(_sub2)); /* R3 */
    printf("logb 1e-308 = %a\n",     logb(1.0e-308)); /* R3 */
    printf("logb 0 = %a\n",          logb(0.0)); /* R3 */
    printf("logb 1 = %a\n",          logb(1.0)); /* R3 */
    printf("logb inf = %a\n",        logb(D_INF)); /* R3 */
    /* ilogb */
    printf("ilogb D_SUBNORM = %d\n", ilogb(D_SUBNORM)); /* R3 */
    printf("ilogb subnorm-hi = %d\n",ilogb(_sub2)); /* R3 */
    printf("ilogb 0 = %d\n",         ilogb(0.0)); /* R3 */
    printf("ilogb nan = %d\n",       ilogb(D_NAN)); /* R3 */
    printf("ilogb inf = %d\n",       ilogb(D_INF)); /* R3 */
    printf("ilogb 1 = %d\n",         ilogb(1.0)); /* R3 */
}

/* ---- tan (large args to cover __tan branches) ---- */
static void test_tan_extra2(void)
{
    /* |reduced_x| >= 0.6744 → (98:9) True */
    printf("tan pi/4 = %a\n",    tan(0.7853981633974483)); /* R3 */
    printf("tan -pi/4 = %a\n",   tan(-0.7853981633974483)); /* R3 */
    printf("tan 3pi/8 = %a\n",   tan(1.1780972450961724)); /* R3 */
    printf("tan -3pi/8 = %a\n",  tan(-1.1780972450961724)); /* R3 */
    /* small args: |reduced_x| < 0.6744 → (98:9) False */
    printf("tan 0.5 = %a\n",     tan(0.5)); /* R3 */
    printf("tan 0.6 = %a\n",     tan(0.6)); /* R3 */
    /* large args for range reduction */
    printf("tan 1e15 = %a\n",    tan(1.0e15)); /* R3 */
    printf("tan -1e15 = %a\n",   tan(-1.0e15)); /* R3 */
    /* tanf */
    printf("tanf pi/4 = %a\n",   (double)tanf(0.7853982f)); /* R3 */
    printf("tanf -pi/4 = %a\n",  (double)tanf(-0.7853982f)); /* R3 */
    printf("tanf 1e6 = %a\n",    (double)tanf(1.0e6f)); /* R3 */
    printf("tanf -1e6 = %a\n",   (double)tanf(-1.0e6f)); /* R3 */
}

/* ---- Internal range reduction (trigd.c / trigf.c) ---- */
static void test_trig_internal_extra2(void)
{
    printf("sin 1e15 = %a\n",   sin(1.0e15)); /* R3 */
    printf("cos 1e15 = %a\n",   cos(1.0e15)); /* R3 */
    printf("sin 1e200 = %a\n",  sin(1.0e200)); /* R3 */
    printf("cos 1e200 = %a\n",  cos(1.0e200)); /* R3 */
    printf("sin -1e15 = %a\n",  sin(-1.0e15)); /* R3 */
    printf("sin 1e100 = %a\n",  sin(1.0e100)); /* R3 */
    printf("sin 1e14 = %a\n",   sin(1.0e14)); /* R3 */
    printf("sin 1e16 = %a\n",   sin(1.0e16)); /* R3 */
    printf("sin 1e50 = %a\n",   sin(1.0e50)); /* R3 */
    printf("cos 1e50 = %a\n",   cos(1.0e50)); /* R3 */
    /* float range reduction */
    printf("sinf 1e6 = %a\n",   (double)sinf(1.0e6f)); /* R3 */
    printf("cosf 1e6 = %a\n",   (double)cosf(1.0e6f)); /* R3 */
    printf("sinf 1e20 = %a\n",  (double)sinf(1.0e20f)); /* R3 */
    printf("cosf 1e20 = %a\n",  (double)cosf(1.0e20f)); /* R3 */
    printf("sinf 1e10 = %a\n",  (double)sinf(1.0e10f)); /* R3 */
    printf("cosf -1e6 = %a\n",  (double)cosf(-1.0e6f)); /* R3 */
    printf("sinf -1e6 = %a\n",  (double)sinf(-1.0e6f)); /* R3 */
    printf("sinf 1e8 = %a\n",   (double)sinf(1.0e8f)); /* R3 */
}

/* ---- csqrt: negative imaginary paths ---- */
static void test_csqrt_extra2(void)
{
    double complex zd, wd;
    float complex zf, wf;
    /* x==0, y < 0 → (76:13) False */
    zd = CMPLX(0.0, -4.0);
    wd = csqrt(zd);
    printf("csqrt 0-4i = %a+%ai\n", creal(wd), cimag(wd)); /* R3 */
    zd = CMPLX(0.0, -1.0);
    wd = csqrt(zd);
    printf("csqrt 0-1i = %a+%ai\n", creal(wd), cimag(wd)); /* R3 */
    /* general path, y < 0 → (109:9) True */
    zd = CMPLX(4.0, -2.0);
    wd = csqrt(zd);
    printf("csqrt 4-2i = %a+%ai\n", creal(wd), cimag(wd)); /* R3 */
    zd = CMPLX(1.0, -3.0);
    wd = csqrt(zd);
    printf("csqrt 1-3i = %a+%ai\n", creal(wd), cimag(wd)); /* R3 */
    /* csqrtf: x==0, y < 0 → (34:13) False */
    zf = CMPLXF(0.0f, -4.0f);
    wf = csqrtf(zf);
    printf("csqrtf 0-4i = %a+%ai\n", (double)crealf(wf), (double)cimagf(wf)); /* R3 */
    /* csqrtf: y < 0 → (67:9) True */
    zf = CMPLXF(4.0f, -2.0f);
    wf = csqrtf(zf);
    printf("csqrtf 4-2i = %a+%ai\n", (double)crealf(wf), (double)cimagf(wf)); /* R3 */
    zf = CMPLXF(1.0f, -3.0f);
    wf = csqrtf(zf);
    printf("csqrtf 1-3i = %a+%ai\n", (double)crealf(wf), (double)cimagf(wf)); /* R3 */
}

/* ---- ctan: d near 0 and large imaginary ---- */
static void test_ctan_extra2(void)
{
    double complex zd, wd;
    float complex zf, wf;
    /* ctand.c Branch (82:14) True: fabs(d) < 0.25, near pi/2 */
    zd = CMPLX(1.5707963267948966, 0.0001);
    wd = ctan(zd);
    printf("ctan pi/2+0.0001i = %a+%ai\n", creal(wd), cimag(wd)); /* R3 */
    /* ctand.c Branch (82:14) False: fabs(d) >= 0.25 */
    zd = CMPLX(0.5, 0.5);
    wd = ctan(zd);
    printf("ctan 0.5+0.5i = %a+%ai\n", creal(wd), cimag(wd)); /* R3 */
    /* ctand.c Branch (98:9) True: d == 0.0 */
    zd = CMPLX(0.0, 0.0);
    wd = ctan(zd);
    printf("ctan 0+0i = %a+%ai\n", creal(wd), cimag(wd)); /* R3 */
    zd = CMPLX(1.5707963267948966, 0.0);
    wd = ctan(zd);
    printf("ctan pi/2+0i = %a+%ai\n", creal(wd), cimag(wd)); /* R3 */
    /* ctanf */
    zf = CMPLXF(1.5707963f, 0.001f);
    wf = ctanf(zf);
    printf("ctanf pi/2+0.001i = %a+%ai\n", (double)crealf(wf), (double)cimagf(wf)); /* R3 */
    zf = CMPLXF(0.5f, 0.5f);
    wf = ctanf(zf);
    printf("ctanf 0.5+0.5i = %a+%ai\n", (double)crealf(wf), (double)cimagf(wf)); /* R3 */
    /* ctanf.c Branch (62:9) and (66:9): large imaginary */
    zf = CMPLXF(0.5f, 50.0f);
    wf = ctanf(zf);
    printf("ctanf 0.5+50i = %a+%ai\n", (double)crealf(wf), (double)cimagf(wf)); /* R3 */
    zf = CMPLXF(0.5f, -50.0f);
    wf = ctanf(zf);
    printf("ctanf 0.5-50i = %a+%ai\n", (double)crealf(wf), (double)cimagf(wf)); /* R3 */
}

/* ---- ctrig: ccoshsinh exp→0 path ---- */
static void test_ctrig_ccosh_extra2(void)
{
    /* ctrigd.c Branch (21:13) False: exp(x)→0 for large negative x */
    double complex rd;
    rd = bridge___ctans(CMPLX(1.0, -1000.0));
    printf("ctans 1-1000i = %a+%ai\n", creal(rd), cimag(rd)); /* R3 */
    rd = bridge___ctans(CMPLX(0.5, -800.0));
    printf("ctans 0.5-800i = %a+%ai\n", creal(rd), cimag(rd)); /* R3 */
    /* ctrigf.c Branch (19:13) False */
    float complex rf;
    rf = bridge___ctansf(CMPLXF(1.0f, -1000.0f));
    printf("ctansf 1-1000i = %a+%ai\n", (double)crealf(rf), (double)cimagf(rf)); /* R3 */
}

/* ---- erfc / erf ---- */
static void test_erfc_extra2(void)
{
    printf("erfc 0.5 = %a\n",  erfc(0.5)); /* R3 */
    printf("erfc 1.0 = %a\n",  erfc(1.0)); /* R3 */
    printf("erfc 5.0 = %a\n",  erfc(5.0)); /* R3 */
    printf("erfc 10.0 = %a\n", erfc(10.0)); /* R3 */
    printf("erfc 28.0 = %a\n", erfc(28.0)); /* R3 */
    printf("erfc -5.0 = %a\n", erfc(-5.0)); /* R3 */
    printf("erfcf 0.5 = %a\n",  (double)erfcf(0.5f)); /* R3 */
    printf("erfcf 4.0 = %a\n",  (double)erfcf(4.0f)); /* R3 */
    printf("erfcf 10.0 = %a\n", (double)erfcf(10.0f)); /* R3 */
    printf("erfcf 14.0 = %a\n", (double)erfcf(14.0f)); /* R3 */
    printf("erfcf -4.0 = %a\n", (double)erfcf(-4.0f)); /* R3 */
    printf("erfcf 0.3 = %a\n",  (double)erfcf(0.3f)); /* R3 */
}

static void test_erf_extra2(void)
{
    printf("erf 0.8 = %a\n",  erf(0.8)); /* R3 */
    printf("erf 4.0 = %a\n",  erf(4.0)); /* R3 */
    printf("erf 6.0 = %a\n",  erf(6.0)); /* R3 */
    printf("erf -4.0 = %a\n", erf(-4.0)); /* R3 */
    printf("erff 0.8 = %a\n",  (double)erff(0.8f)); /* R3 */
    printf("erff 4.0 = %a\n",  (double)erff(4.0f)); /* R3 */
    printf("erff -4.0 = %a\n", (double)erff(-4.0f)); /* R3 */
    printf("erff 0.3 = %a\n",  (double)erff(0.3f)); /* R3 */
}

/* ---- expm1 ---- */
static void test_expm1_extra2(void)
{
    printf("expm1 -0.5 = %a\n",   expm1(-0.5)); /* R3 */
    printf("expm1 0.5 = %a\n",    expm1(0.5)); /* R3 */
    printf("expm1 1e-10 = %a\n",  expm1(1.0e-10)); /* R3 */
    printf("expm1 -1e-10 = %a\n", expm1(-1.0e-10)); /* R3 */
    printf("expm1 100 = %a\n",    expm1(100.0)); /* R3 */
    printf("expm1 -100 = %a\n",   expm1(-100.0)); /* R3 */
    printf("expm1 0.3 = %a\n",    expm1(0.3)); /* R3 */
    printf("expm1 -0.3 = %a\n",   expm1(-0.3)); /* R3 */
    printf("expm1f 100 = %a\n",   (double)expm1f(100.0f)); /* R3 */
    printf("expm1f -100 = %a\n",  (double)expm1f(-100.0f)); /* R3 */
    printf("expm1f 0.5 = %a\n",   (double)expm1f(0.5f)); /* R3 */
    printf("expm1f 1e-10 = %a\n", (double)expm1f(1.0e-10f)); /* R3 */
    printf("expm1f 0.3 = %a\n",   (double)expm1f(0.3f)); /* R3 */
}

/* ---- lgamma / tgamma ---- */
static void test_gamma_extra2(void)
{
    /* Various piecewise ranges to cover gammad.c __sin_pi branches */
    printf("lgamma 0.5 = %a\n",    lgamma(0.5)); /* R3 */
    printf("lgamma -0.5 = %a\n",   lgamma(-0.5)); /* R3 */
    printf("lgamma 1.5 = %a\n",    lgamma(1.5)); /* R3 */
    printf("lgamma -1.5 = %a\n",   lgamma(-1.5)); /* R3 */
    printf("lgamma 2.5 = %a\n",    lgamma(2.5)); /* R3 */
    printf("lgamma -2.5 = %a\n",   lgamma(-2.5)); /* R3 */
    printf("lgamma 3.5 = %a\n",    lgamma(3.5)); /* R3 */
    printf("lgamma -3.5 = %a\n",   lgamma(-3.5)); /* R3 */
    printf("lgamma 4.5 = %a\n",    lgamma(4.5)); /* R3 */
    printf("lgamma -4.5 = %a\n",   lgamma(-4.5)); /* R3 */
    printf("lgamma 5.5 = %a\n",    lgamma(5.5)); /* R3 */
    printf("lgamma -5.5 = %a\n",   lgamma(-5.5)); /* R3 */
    printf("lgamma 0.1 = %a\n",    lgamma(0.1)); /* R3 */
    printf("lgamma -0.1 = %a\n",   lgamma(-0.1)); /* R3 */
    printf("lgamma -0.999 = %a\n", lgamma(-0.999)); /* R3 */
    printf("lgamma -1.001 = %a\n", lgamma(-1.001)); /* R3 */
}

static void test_gammaf_extra2(void)
{
    /* Extensive piecewise ranges for gammaf.c */
    printf("lgammaf 0.5 = %a\n",    (double)lgammaf(0.5f)); /* R3 */
    printf("lgammaf -0.5 = %a\n",   (double)lgammaf(-0.5f)); /* R3 */
    printf("lgammaf 1.5 = %a\n",    (double)lgammaf(1.5f)); /* R3 */
    printf("lgammaf -1.5 = %a\n",   (double)lgammaf(-1.5f)); /* R3 */
    printf("lgammaf 2.5 = %a\n",    (double)lgammaf(2.5f)); /* R3 */
    printf("lgammaf -2.5 = %a\n",   (double)lgammaf(-2.5f)); /* R3 */
    printf("lgammaf 3.5 = %a\n",    (double)lgammaf(3.5f)); /* R3 */
    printf("lgammaf -3.5 = %a\n",   (double)lgammaf(-3.5f)); /* R3 */
    printf("lgammaf 0.1 = %a\n",    (double)lgammaf(0.1f)); /* R3 */
    printf("lgammaf -0.1 = %a\n",   (double)lgammaf(-0.1f)); /* R3 */
    printf("lgammaf 0.3 = %a\n",    (double)lgammaf(0.3f)); /* R3 */
    printf("lgammaf 0.7 = %a\n",    (double)lgammaf(0.7f)); /* R3 */
    printf("lgammaf 1.3 = %a\n",    (double)lgammaf(1.3f)); /* R3 */
    printf("lgammaf 1.7 = %a\n",    (double)lgammaf(1.7f)); /* R3 */
    printf("lgammaf 2.3 = %a\n",    (double)lgammaf(2.3f)); /* R3 */
    printf("lgammaf 3.0 = %a\n",    (double)lgammaf(3.0f)); /* R3 */
    printf("lgammaf 4.0 = %a\n",    (double)lgammaf(4.0f)); /* R3 */
    printf("lgammaf 7.0 = %a\n",    (double)lgammaf(7.0f)); /* R3 */
    printf("lgammaf 8.0 = %a\n",    (double)lgammaf(8.0f)); /* R3 */
    printf("lgammaf -4.5 = %a\n",   (double)lgammaf(-4.5f)); /* R3 */
    printf("lgammaf -0.999 = %a\n", (double)lgammaf(-0.999f)); /* R3 */
    printf("tgammaf 0.5 = %a\n",    (double)tgammaf(0.5f)); /* R3 */
    printf("tgammaf -0.5 = %a\n",   (double)tgammaf(-0.5f)); /* R3 */
    printf("tgammaf 2.5 = %a\n",    (double)tgammaf(2.5f)); /* R3 */
}

/* ---- Bessel j0, j1, jn ---- */
static void test_j0_extra2(void)
{
    printf("j0 0.5 = %a\n",   j0(0.5)); /* R3 */
    printf("j0 3.0 = %a\n",   j0(3.0)); /* R3 */
    printf("j0 5.0 = %a\n",   j0(5.0)); /* R3 */
    printf("j0 8.0 = %a\n",   j0(8.0)); /* R3 */
    printf("j0 10.0 = %a\n",  j0(10.0)); /* R3 */
    printf("j0 100.0 = %a\n", j0(100.0)); /* R3 */
    printf("j0 1e-5 = %a\n",  j0(1.0e-5)); /* R3 */
}

static void test_j1_extra2(void)
{
    printf("j1 0.5 = %a\n",   j1(0.5)); /* R3 */
    printf("j1 3.0 = %a\n",   j1(3.0)); /* R3 */
    printf("j1 5.0 = %a\n",   j1(5.0)); /* R3 */
    printf("j1 8.0 = %a\n",   j1(8.0)); /* R3 */
    printf("j1 10.0 = %a\n",  j1(10.0)); /* R3 */
    printf("j1 100.0 = %a\n", j1(100.0)); /* R3 */
    printf("j1 1e-5 = %a\n",  j1(1.0e-5)); /* R3 */
}

static void test_jn_extra2(void)
{
    printf("jn 0 0.5 = %a\n",   jn(0, 0.5)); /* R3 */
    printf("jn 1 0.5 = %a\n",   jn(1, 0.5)); /* R3 */
    printf("jn 5 0.5 = %a\n",   jn(5, 0.5)); /* R3 */
    printf("jn 5 10 = %a\n",    jn(5, 10.0)); /* R3 */
    printf("jn 10 5 = %a\n",    jn(10, 5.0)); /* R3 */
    printf("jn 50 10 = %a\n",   jn(50, 10.0)); /* R3 */
    printf("jn 2 0.01 = %a\n",  jn(2, 0.01)); /* R3 */
    printf("jn 3 100 = %a\n",   jn(3, 100.0)); /* R3 */
    printf("jn 0 100 = %a\n",   jn(0, 100.0)); /* R3 */
    printf("jn 1 1e-10 = %a\n", jn(1, 1.0e-10)); /* R3 */
    printf("jn 2 1e-10 = %a\n", jn(2, 1.0e-10)); /* R3 */
    printf("jn 100 1 = %a\n",   jn(100, 1.0)); /* R3 */
}

/* ---- Bessel y0, y1, yn ---- */
static void test_y0_extra2(void)
{
    printf("y0 0.5 = %a\n",   y0(0.5)); /* R3 */
    printf("y0 3.0 = %a\n",   y0(3.0)); /* R3 */
    printf("y0 5.0 = %a\n",   y0(5.0)); /* R3 */
    printf("y0 8.0 = %a\n",   y0(8.0)); /* R3 */
    printf("y0 10.0 = %a\n",  y0(10.0)); /* R3 */
    printf("y0 100.0 = %a\n", y0(100.0)); /* R3 */
    printf("y0 1e-5 = %a\n",  y0(1.0e-5)); /* R3 */
}

static void test_y1_extra2(void)
{
    printf("y1 0.5 = %a\n",   y1(0.5)); /* R3 */
    printf("y1 3.0 = %a\n",   y1(3.0)); /* R3 */
    printf("y1 5.0 = %a\n",   y1(5.0)); /* R3 */
    printf("y1 8.0 = %a\n",   y1(8.0)); /* R3 */
    printf("y1 10.0 = %a\n",  y1(10.0)); /* R3 */
    printf("y1 100.0 = %a\n", y1(100.0)); /* R3 */
    printf("y1 1e-5 = %a\n",  y1(1.0e-5)); /* R3 */
}

static void test_yn_extra2(void)
{
    printf("yn 0 0.5 = %a\n",  yn(0, 0.5)); /* R3 */
    printf("yn 1 0.5 = %a\n",  yn(1, 0.5)); /* R3 */
    printf("yn 2 0.5 = %a\n",  yn(2, 0.5)); /* R3 */
    printf("yn 5 10 = %a\n",   yn(5, 10.0)); /* R3 */
    printf("yn 10 5 = %a\n",   yn(10, 5.0)); /* R3 */
    printf("yn 0 100 = %a\n",  yn(0, 100.0)); /* R3 */
    printf("yn 1 100 = %a\n",  yn(1, 100.0)); /* R3 */
    printf("yn 50 10 = %a\n",  yn(50, 10.0)); /* R3 */
    printf("yn 3 1e-5 = %a\n", yn(3, 1.0e-5)); /* R3 */
}

/* ---- pow / powf ---- */
static void test_pow_extra2(void)
{
    union { double d; uint64_t u; } _snand, _qnand;
    _snand.u = 0x7FF0000000000001ULL;
    _qnand.u = 0x7FF8000000000000ULL;
    /* pow(1, quiet NaN) → 1 */
    printf("pow 1 qnan = %a\n",     pow(1.0, _qnand.d)); /* R3 */
    /* pow(quiet NaN, 0) → 1 */
    printf("pow qnan 0 = %a\n",     pow(_qnand.d, 0.0)); /* R3 */
    /* pow(1, signaling NaN) → NaN */
    printf("pow 1 snan = %a\n",     pow(1.0, _snand.d)); /* R3 */
    /* x<0, non-integer y → invalid */
    printf("pow -2 1.5 = %a\n",     pow(-2.0, 1.5)); /* R3 */
    /* x<0, odd int y */
    printf("pow -2 3 = %a\n",       pow(-2.0, 3.0)); /* R3 */
    /* x<0, even int y */
    printf("pow -2 2 = %a\n",       pow(-2.0, 2.0)); /* R3 */
    /* large |y| > 2^64 */
    printf("pow 2 1e20 = %a\n",     pow(2.0, 1.0e20)); /* R3 */
    printf("pow 0.5 1e20 = %a\n",   pow(0.5, 1.0e20)); /* R3 */
    /* |y| > 2^33: |x|<1, hy>0 → underflow */
    printf("pow 0.9 1e11 = %a\n",   pow(0.9, 1.0e11)); /* R3 */
    /* |y| > 2^33: |x|>1, hy>0 → overflow */
    printf("pow 1.1 1e11 = %a\n",   pow(1.1, 1.0e11)); /* R3 */
    /* special x cases */
    printf("pow 0 -1 = %a\n",       pow(0.0, -1.0)); /* R3 */
    printf("pow -0 -1 = %a\n",      pow(-0.0, -1.0)); /* R3 */
    printf("pow -0 -3 = %a\n",      pow(-0.0, -3.0)); /* R3 */
    printf("pow -0 -2 = %a\n",      pow(-0.0, -2.0)); /* R3 */
    printf("pow -0 3 = %a\n",       pow(-0.0, 3.0)); /* R3 */
    printf("pow -0 2 = %a\n",       pow(-0.0, 2.0)); /* R3 */
    printf("pow -1 inf = %a\n",     pow(-1.0, D_INF)); /* R3 */
    printf("pow -1 -inf = %a\n",    pow(-1.0, D_NINF)); /* R3 */
    /* overflow / underflow */
    printf("pow 2 1024 = %a\n",     pow(2.0, 1024.0)); /* R3 */
    printf("pow 0.5 -1075 = %a\n",  pow(0.5, -1075.0)); /* R3 */
    printf("pow 2 100 = %a\n",      pow(2.0, 100.0)); /* R3 */
    printf("pow 0.5 -100 = %a\n",   pow(0.5, -100.0)); /* R3 */
    /* powf */
    union { float f; uint32_t u; } _snanf, _qnanf;
    _snanf.u = 0x7F800001U;
    _qnanf.u = 0x7FC00000U;
    printf("powf 1 qnan = %a\n",    (double)powf(1.0f, _qnanf.f)); /* R3 */
    printf("powf 1 snan = %a\n",    (double)powf(1.0f, _snanf.f)); /* R3 */
    printf("powf -2 1.5 = %a\n",    (double)powf(-2.0f, 1.5f)); /* R3 */
    printf("powf -2 3 = %a\n",      (double)powf(-2.0f, 3.0f)); /* R3 */
    printf("powf -2 2 = %a\n",      (double)powf(-2.0f, 2.0f)); /* R3 */
    printf("powf 2 200 = %a\n",     (double)powf(2.0f, 200.0f)); /* R3 */
    printf("powf 0.5 -200 = %a\n",  (double)powf(0.5f, -200.0f)); /* R3 */
    printf("powf 0 -1 = %a\n",      (double)powf(0.0f, -1.0f)); /* R3 */
    printf("powf -0 -3 = %a\n",     (double)powf(-0.0f, -3.0f)); /* R3 */
    printf("powf 0.9 1e11 = %a\n",  (double)powf(0.9f, 1.0e11f)); /* R3 */
    printf("powf 1.1 1e11 = %a\n",  (double)powf(1.1f, 1.0e11f)); /* R3 */
    printf("powf 2 127 = %a\n",     (double)powf(2.0f, 127.0f)); /* R3 */
}

/* ------------------------------------------------------------------ */
/* Long double and nexttoward — conditionally compiled                 */
/* ------------------------------------------------------------------ */

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

static void test_long_double_trig(void)
{
    printf("acosl %La = %La\n", (long double)0.5, acosl((long double)0.5)); /* S4 */
    printf("asinl %La = %La\n", (long double)0.5, asinl((long double)0.5)); /* S4 */
    printf("atanl %La = %La\n", (long double)1.0, atanl((long double)1.0)); /* S4 */
    printf("atan2l %La %La = %La\n", (long double)1.0, (long double)1.0, /* S4 */
           atan2l((long double)1.0, (long double)1.0));
    printf("cosl %La = %La\n", (long double)1.0, cosl((long double)1.0)); /* S4 */
    printf("sinl %La = %La\n", (long double)1.0, sinl((long double)1.0)); /* S4 */
    printf("tanl %La = %La\n", (long double)0.5, tanl((long double)0.5)); /* S4 */
}

static void test_long_double_hyperbolic(void)
{
    printf("acoshl %La = %La\n", (long double)2.0, acoshl((long double)2.0)); /* S4 */
    printf("asinhl %La = %La\n", (long double)1.0, asinhl((long double)1.0)); /* S4 */
    printf("atanhl %La = %La\n", (long double)0.5, atanhl((long double)0.5)); /* S4 */
    printf("coshl %La = %La\n", (long double)1.0, coshl((long double)1.0)); /* S4 */
    printf("sinhl %La = %La\n", (long double)1.0, sinhl((long double)1.0)); /* S4 */
    printf("tanhl %La = %La\n", (long double)1.0, tanhl((long double)1.0)); /* S4 */
}

static void test_long_double_exp_log(void)
{
    printf("expl %La = %La\n", (long double)1.0, expl((long double)1.0)); /* S4 */
    printf("exp2l %La = %La\n", (long double)2.0, exp2l((long double)2.0)); /* S4 */
    printf("expm1l %La = %La\n", (long double)1.0, expm1l((long double)1.0)); /* S4 */
    int e;
    long double m = frexpl((long double)4.0, &e);
    printf("frexpl %La = %La exp %d\n", (long double)4.0, m, e); /* S4 */
    printf("ilogbl %La = %d\n", (long double)2.0, ilogbl((long double)2.0)); /* S4 */
    printf("ldexpl %La %d = %La\n", (long double)1.0, 2, ldexpl((long double)1.0, 2)); /* S4 */
    printf("logl %La = %La\n", (long double)1.0, logl((long double)1.0)); /* S4 */
    printf("log10l %La = %La\n", (long double)10.0, log10l((long double)10.0)); /* S4 */
    printf("log1pl %La = %La\n", (long double)1.0, log1pl((long double)1.0)); /* S4 */
    printf("log2l %La = %La\n", (long double)2.0, log2l((long double)2.0)); /* S4 */
    printf("logbl %La = %La\n", (long double)2.0, logbl((long double)2.0)); /* S4 */
    long double ipart;
    long double frac = modfl((long double)3.14, &ipart);
    printf("modfl %La = %La ipart %La\n", (long double)3.14, frac, ipart); /* S4 */
    printf("scalbnl %La %d = %La\n", (long double)1.0, 2, scalbnl((long double)1.0, 2)); /* S4 */
    printf("scalblnl %La %ld = %La\n", (long double)1.0, 2L, scalblnl((long double)1.0, 2L)); /* S4 */
}

static void test_long_double_power(void)
{
    printf("cbrtl %La = %La\n", (long double)8.0, cbrtl((long double)8.0)); /* S4 */
    printf("fabsl %La = %La\n", (long double)-1.0, fabsl((long double)-1.0)); /* S4 */
    printf("hypotl %La %La = %La\n", (long double)3.0, (long double)4.0, /* S4 */
           hypotl((long double)3.0, (long double)4.0));
    printf("powl %La %La = %La\n", (long double)2.0, (long double)10.0, /* S4 */
           powl((long double)2.0, (long double)10.0));
    printf("sqrtl %La = %La\n", (long double)4.0, sqrtl((long double)4.0)); /* S4 */
}

static void test_long_double_errorgamma(void)
{
    printf("erfl %La = %La\n", (long double)1.0, erfl((long double)1.0)); /* S4 */
    printf("erfcl %La = %La\n", (long double)1.0, erfcl((long double)1.0)); /* S4 */
    printf("lgammal %La = %La\n", (long double)2.0, lgammal((long double)2.0)); /* S4 */
    printf("tgammal %La = %La\n", (long double)2.0, tgammal((long double)2.0)); /* S4 */
}

static void test_long_double_nearbyint(void)
{
    printf("ceill %La = %La\n", (long double)1.2, ceill((long double)1.2)); /* S4 */
    printf("floorl %La = %La\n", (long double)1.9, floorl((long double)1.9)); /* S4 */
    printf("nearbyintl %La = %La\n", (long double)1.5, nearbyintl((long double)1.5)); /* S4 */
    printf("rintl %La = %La\n", (long double)1.5, rintl((long double)1.5)); /* S4 */
    printf("lrintl %La = %ld\n", (long double)1.5, lrintl((long double)1.5)); /* S4 */
    printf("llrintl %La = %lld\n", (long double)1.5, llrintl((long double)1.5)); /* S4 */
    printf("roundl %La = %La\n", (long double)1.5, roundl((long double)1.5)); /* S4 */
    printf("lroundl %La = %ld\n", (long double)1.5, lroundl((long double)1.5)); /* S4 */
    printf("llroundl %La = %lld\n", (long double)1.5, llroundl((long double)1.5)); /* S4 */
    printf("truncl %La = %La\n", (long double)1.9, truncl((long double)1.9)); /* S4 */
}

static void test_long_double_remainder(void)
{
    printf("fmodl %La %La = %La\n", (long double)5.0, (long double)3.0, /* S4 */
           fmodl((long double)5.0, (long double)3.0));
    printf("remainderl %La %La = %La\n", (long double)5.0, (long double)3.0, /* S4 */
           remainderl((long double)5.0, (long double)3.0));
    int q;
    long double r = remquol((long double)5.0, (long double)3.0, &q);
    printf("remquol %La %La = %La quo %d\n", (long double)5.0, (long double)3.0, r, q); /* S4 */
}

static void test_long_double_manipulation(void)
{
    printf("copysignl %La %La = %La\n", (long double)1.0, (long double)-2.0, /* S4 */
           copysignl((long double)1.0, (long double)-2.0));
    long double v = nanl("");
    printf("nanl isnan = %d\n", v != v ? 1 : 0); /* S4 */
    printf("nextafterl %La %La = %La\n", (long double)0.0, (long double)1.0, /* S4 */
           nextafterl((long double)0.0, (long double)1.0));
    printf("nexttoward %a %La = %a\n", 0.0, (long double)1.0, /* S4 */
           nexttoward(0.0, (long double)1.0));
    printf("nexttowardf %a %La = %a\n", 0.0f, (long double)1.0, /* S4 */
           nexttowardf(0.0f, (long double)1.0));
    printf("nexttowardl %La %La = %La\n", (long double)0.0, (long double)1.0, /* S4 */
           nexttowardl((long double)0.0, (long double)1.0));
}

static void test_long_double_maxmindiff(void)
{
    printf("fdiml %La %La = %La\n", (long double)3.0, (long double)2.0, /* S4 */
           fdiml((long double)3.0, (long double)2.0));
    printf("fmaxl %La %La = %La\n", (long double)3.0, (long double)2.0, /* S4 */
           fmaxl((long double)3.0, (long double)2.0));
    printf("fminl %La %La = %La\n", (long double)3.0, (long double)2.0, /* S4 */
           fminl((long double)3.0, (long double)2.0));
    printf("fmal %La %La %La = %La\n", (long double)2.0, (long double)3.0, (long double)4.0, /* S4 */
           fmal((long double)2.0, (long double)3.0, (long double)4.0));
}

static void test_long_double_complex(void)
{
    long double complex z, w;

    z = CMPLXL((long double)3.0, (long double)4.0);
    printf("cabsl %La+%Lai = %La\n", creall(z), cimagl(z), cabsl(z)); /* S4 */

    z = CMPLXL((long double)0.5, (long double)0.0);
    w = cacosl(z);
    printf("cacosl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w)); /* S4 */

    z = CMPLXL((long double)0.5, (long double)0.0);
    w = casinl(z);
    printf("casinl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w)); /* S4 */

    z = CMPLXL((long double)1.0, (long double)0.0);
    w = catanl(z);
    printf("catanl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w)); /* S4 */

    z = CMPLXL((long double)0.0, (long double)0.0);
    w = ccosl(z);
    printf("ccosl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w)); /* S4 */

    z = CMPLXL((long double)0.0, (long double)0.0);
    w = csinl(z);
    printf("csinl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w)); /* S4 */

    z = CMPLXL((long double)0.5, (long double)0.5);
    w = ctanl(z);
    printf("ctanl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w)); /* S4 */

    z = CMPLXL((long double)2.0, (long double)0.0);
    w = cacoshl(z);
    printf("cacoshl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w)); /* S4 */

    z = CMPLXL((long double)1.0, (long double)0.0);
    w = casinhl(z);
    printf("casinhl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w)); /* S4 */

    z = CMPLXL((long double)0.5, (long double)0.0);
    w = catanhl(z);
    printf("catanhl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w)); /* S4 */

    z = CMPLXL((long double)0.0, (long double)0.0);
    w = ccoshl(z);
    printf("ccoshl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w)); /* S4 */

    z = CMPLXL((long double)0.0, (long double)0.0);
    w = csinhl(z);
    printf("csinhl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w)); /* S4 */

    z = CMPLXL((long double)0.5, (long double)0.5);
    w = ctanhl(z);
    printf("ctanhl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w)); /* S4 */

    z = CMPLXL((long double)1.0, (long double)0.0);
    w = cexpl(z);
    printf("cexpl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w)); /* S4 */

    z = CMPLXL((long double)1.0, (long double)0.0);
    w = clogl(z);
    printf("clogl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w)); /* S4 */

    z = CMPLXL((long double)1.0, (long double)1.0);
    long double base_r = cpowl(z, CMPLXL((long double)2.0, (long double)0.0));
    (void)base_r;
    w = cpowl(z, CMPLXL((long double)2.0, (long double)0.0));
    printf("cpowl %La+%Lai 2+0i = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w)); /* S4 */

    z = CMPLXL((long double)4.0, (long double)0.0);
    w = csqrtl(z);
    printf("csqrtl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w)); /* S4 */

    z = CMPLXL((long double)1.0, (long double)0.0);
    printf("cargl %La+%Lai = %La\n", creall(z), cimagl(z), cargl(z)); /* S4 */

    z = CMPLXL((long double)3.0, (long double)4.0);
    printf("cimagl %La+%Lai = %La\n", creall(z), cimagl(z), cimagl(z)); /* S4 */

    w = conjl(z);
    printf("conjl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w)); /* S4 */

    w = cprojl(z);
    printf("cprojl %La+%Lai = %La+%Lai\n", creall(z), cimagl(z), creall(w), cimagl(w)); /* S4 */

    printf("creall %La+%Lai = %La\n", creall(z), cimagl(z), creall(z)); /* S4 */
}

#endif /* __LIBMCS_LONG_DOUBLE_IS_64BITS */

/* ------------------------------------------------------------------ */
/* Forward declarations for extra3 test functions                     */
/* ------------------------------------------------------------------ */

static void test_ceil_extra3(void);
static void test_ceilf_extra3(void);
static void test_floor_extra3(void);
static void test_floorf_extra3(void);
static void test_trunc_extra3(void);
static void test_truncf_extra3(void);
static void test_fmax_extra3(void);
static void test_fmin_extra3(void);
static void test_fmaxf_extra3(void);
static void test_fminf_extra3(void);
static void test_fmod_extra3(void);
static void test_fmodf_extra3(void);
static void test_frexp_extra3(void);
static void test_frexpf_extra3(void);
static void test_modf_extra3(void);
static void test_modff_extra3(void);
static void test_remainder_extra3(void);
static void test_remainderf_extra3(void);
static void test_remquo_extra3(void);
static void test_remquof_extra3(void);
static void test_nextafter_extra3(void);
static void test_nextafterf_extra3(void);
static void test_scalbn_extra3(void);
static void test_scalbnf_extra3(void);
static void test_sqrt_extra3(void);
static void test_sqrtf_extra3(void);
static void test_atan2_extra3(void);
static void test_atan2f_extra3(void);
static void test_tan_extra3(void);
static void test_tanf_extra3(void);
static void test_trig_internal_extra3(void);
static void test_trigf_internal_extra3(void);
static void test_gamma_extra3(void);
static void test_gammaf_extra3(void);
static void test_hypot_extra3(void);
static void test_hypotf_extra3(void);
static void test_ilogb_extra3(void);
static void test_log10_extra3(void);
static void test_log10f_extra3(void);
static void test_log1p_extra3(void);
static void test_log1pf_extra3(void);
static void test_log2f_extra3(void);
static void test_logf_extra3(void);
static void test_expm1_extra3(void);
static void test_expm1f_extra3(void);
static void test_round_extra3(void);
static void test_lrintf_extra3(void);
static void test_lroundf_extra3(void);
static void test_llrintf_extra3(void);
static void test_llroundf_extra3(void);
static void test_rintf_extra3(void);
static void test_jn_extra3(void);
static void test_yn_extra3(void);
static void test_y1_extra3(void);
static void test_pow_extra3(void);
static void test_powf_extra3(void);
static void test_ctanf_extra3(void);
static void test_ctrigf_extra3(void);
static void test_ctrigd_extra3(void);
static void test_erf_extra3(void);
static void test_erfc_extra3(void);
static void test_erfcf_extra3(void);

/* Forward declarations for s5 branch-coverage test functions         */
/* ------------------------------------------------------------------ */
static void test_atan2_s5(void);
static void test_ceil_s5(void);
static void test_ceilf_s5(void);
static void test_floor_s5(void);
static void test_floorf_s5(void);
static void test_trunc_s5(void);
static void test_truncf_s5(void);
static void test_fmaxmin_s5(void);
static void test_fmod_s5(void);
static void test_frexp_s5(void);
static void test_gamma_s5(void);
static void test_gammaf_s5(void);
static void test_hypot_s5(void);
static void test_ilogb_s5(void);
static void test_bessel_s5(void);
static void test_log_s5(void);
static void test_modf_s5(void);
static void test_nextafter_s5(void);
static void test_pow_s5(void);
static void test_remainder_s5(void);
static void test_remquo_s5(void);
static void test_rint_s5(void);
static void test_round_s5(void);
static void test_scalbn_s5(void);
static void test_sqrt_s5(void);
static void test_trigd_s5(void);
static void test_trigf_s5(void);
static void test_erf_s5(void);
static void test_expm1_s5(void);
static void test_ctan_s5(void);

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
    test_ceil_extra2();
    test_ceilf_extra2();
    test_floor_extra2();
    test_floorf_extra2();
    test_trunc_extra2();
    test_truncf_extra2();
    test_modf_extra2();
    test_frexp_extra2();
    test_nextafter_extra2();
    test_scalbn_extra2();
    test_scalbln_extra2();
    test_rint_extra2();
    test_round_extra2();
    test_lrint_extra2();
    test_lround_extra2();
    test_llrint_extra2();
    test_llround_extra2();
    test_fmax_extra2();
    test_fmin_extra2();
    test_fmod_extra2();
    test_remainder_extra2();
    test_remquo_extra2();
    test_sqrt_extra2();
    test_hypot_extra2();
    test_sinh_extra2();
    test_cosh_extra2();
    test_log_extra2();
    test_logb_extra2();
    test_tan_extra2();
    test_trig_internal_extra2();
    test_csqrt_extra2();
    test_ctan_extra2();
    test_ctrig_ccosh_extra2();
    test_erfc_extra2();
    test_erf_extra2();
    test_expm1_extra2();
    test_gamma_extra2();
    test_gammaf_extra2();
    test_j0_extra2();
    test_j1_extra2();
    test_jn_extra2();
    test_y0_extra2();
    test_y1_extra2();
    test_yn_extra2();
    test_pow_extra2();

    /* extra3 tests for uncovered branches */
    test_ceil_extra3();
    test_ceilf_extra3();
    test_floor_extra3();
    test_floorf_extra3();
    test_trunc_extra3();
    test_truncf_extra3();
    test_fmax_extra3();
    test_fmin_extra3();
    test_fmaxf_extra3();
    test_fminf_extra3();
    test_fmod_extra3();
    test_fmodf_extra3();
    test_frexp_extra3();
    test_frexpf_extra3();
    test_modf_extra3();
    test_modff_extra3();
    test_remainder_extra3();
    test_remainderf_extra3();
    test_remquo_extra3();
    test_remquof_extra3();
    test_nextafter_extra3();
    test_nextafterf_extra3();
    test_scalbn_extra3();
    test_scalbnf_extra3();
    test_sqrt_extra3();
    test_sqrtf_extra3();
    test_atan2_extra3();
    test_atan2f_extra3();
    test_tan_extra3();
    test_tanf_extra3();
    test_trig_internal_extra3();
    test_trigf_internal_extra3();
    test_gamma_extra3();
    test_gammaf_extra3();
    test_hypot_extra3();
    test_hypotf_extra3();
    test_ilogb_extra3();
    test_log10_extra3();
    test_log10f_extra3();
    test_log1p_extra3();
    test_log1pf_extra3();
    test_log2f_extra3();
    test_logf_extra3();
    test_expm1_extra3();
    test_expm1f_extra3();
    test_round_extra3();
    test_lrintf_extra3();
    test_lroundf_extra3();
    test_llrintf_extra3();
    test_llroundf_extra3();
    test_rintf_extra3();
    test_jn_extra3();
    test_yn_extra3();
    test_y1_extra3();
    test_pow_extra3();
    test_powf_extra3();
    test_ctanf_extra3();
    test_ctrigf_extra3();
    test_ctrigd_extra3();
    test_erf_extra3();
    test_erfc_extra3();
    test_erfcf_extra3();

    /* s5 branch-coverage tests */
    test_atan2_s5();
    test_ceil_s5();
    test_ceilf_s5();
    test_floor_s5();
    test_floorf_s5();
    test_trunc_s5();
    test_truncf_s5();
    test_fmaxmin_s5();
    test_fmod_s5();
    test_frexp_s5();
    test_gamma_s5();
    test_gammaf_s5();
    test_hypot_s5();
    test_ilogb_s5();
    test_bessel_s5();
    test_log_s5();
    test_modf_s5();
    test_nextafter_s5();
    test_pow_s5();
    test_remainder_s5();
    test_remquo_s5();
    test_rint_s5();
    test_round_s5();
    test_scalbn_s5();
    test_sqrt_s5();
    test_trigd_s5();
    test_trigf_s5();
    test_erf_s5();
    test_expm1_s5();
    test_ctan_s5();

    return 0;
}

/* ================================================================== */
/* extra3 test functions — targeting uncovered branches                */
/* ================================================================== */

/* ceild.c uncovered branches:
 * Line 68: _j0 < 20 (True) — small exponent
 * Line 69: _j0 < 0  (True/False)
 * Line 70: zero/non-zero check (True/False)
 * Line 76: _i0 < 0 (True/False)
 * Line 86: integral check (True/False)
 * Line 92: _i0 > 0 (True/False)
 * Line 99: _j0 > 51 (True)
 * Line 100: _j0 == 0x400 (True/False)
 * Line 108: integral check (True/False)
 * Line 113: _i0 > 0 (True)
 * Line 114: _j0 == 20 (True)
 * Line 119: carry (False)
 */
static void test_ceil_extra3(void)
{
    printf("=== test_ceil_extra3 ===\n"); /* R4 */
    /* _j0 < 0, |x|!=0, _i0 >= 0 (positive small fraction) */
    printf("ceil(0.3) = %a\n", ceil(0.3)); /* R4 */
    /* _j0 < 0, |x|!=0, _i0 < 0 (negative small fraction) */
    printf("ceil(-0.3) = %a\n", ceil(-0.3)); /* R4 */
    /* _j0 < 0, |x|==0 (zero) */
    printf("ceil(0.0) = %a\n", ceil(0.0)); /* R4 */
    printf("ceil(-0.0) = %a\n", ceil(-0.0)); /* R4 */
    /* _j0 in [0,20), x is integral */
    printf("ceil(2.0) = %a\n", ceil(2.0)); /* R4 */
    /* _j0 in [0,20), x is NOT integral, _i0 > 0 */
    printf("ceil(1.5) = %a\n", ceil(1.5)); /* R4 */
    /* _j0 in [0,20), x is NOT integral, _i0 < 0 */
    printf("ceil(-1.5) = %a\n", ceil(-1.5)); /* R4 */
    /* _j0 in [0,20), _j0 == 0 edge */
    printf("ceil(1.25) = %a\n", ceil(1.25)); /* R4 */
    printf("ceil(-1.25) = %a\n", ceil(-1.25)); /* R4 */
    /* _j0 > 51, _j0 == 0x400: NaN/Inf */
    printf("ceil(INFINITY) = %a\n", ceil(INFINITY)); /* R4 */
    printf("ceil(-INFINITY) = %a\n", ceil(-INFINITY)); /* R4 */
    printf("ceil(NAN) = %a\n", ceil(NAN)); /* R4 */
    /* _j0 > 51, _j0 != 0x400: large integer */
    printf("ceil(1e20) = %a\n", ceil(1e20)); /* R4 */
    /* _j0 in [20,52): x is integral */
    printf("ceil(0x1p30) = %a\n", ceil(0x1p30)); /* R4 */
    /* _j0 in [20,52): x is NOT integral, _i0 > 0, _j0==20 */
    printf("ceil(0x1.8p20) = %a\n", ceil(0x1.8p20)); /* R4 */
    /* _j0 in [20,52): x NOT integral, _i0 > 0, _j0 != 20 */
    printf("ceil(0x1.0000000000001p30) = %a\n", ceil(0x1.0000000000001p30)); /* R4 */
    /* _j0 in [20,52): x NOT integral, _i0 < 0 */
    printf("ceil(-0x1.8p20) = %a\n", ceil(-0x1.8p20)); /* R4 */
    printf("ceil(-0x1.0000000000001p30) = %a\n", ceil(-0x1.0000000000001p30)); /* R4 */
}

/* ceilf.c uncovered branches */
static void test_ceilf_extra3(void)
{
    printf("=== test_ceilf_extra3 ===\n"); /* R4 */
    /* _j0 < 0, zero (True) */
    printf("ceilf(0.0f) = %a\n", ceilf(0.0f)); /* R4 */
    /* _j0 < 0, zero (False), _i0 < 0 */
    printf("ceilf(-0.3f) = %a\n", ceilf(-0.3f)); /* R4 */
    /* _j0 < 0, zero (False), _i0 >= 0 */
    printf("ceilf(0.3f) = %a\n", ceilf(0.3f)); /* R4 */
    /* _j0 in [0,23): integral */
    printf("ceilf(2.0f) = %a\n", ceilf(2.0f)); /* R4 */
    /* _j0 in [0,23): not integral, _i0 > 0 */
    printf("ceilf(1.5f) = %a\n", ceilf(1.5f)); /* R4 */
    /* _j0 in [0,23): not integral, _i0 < 0 */
    printf("ceilf(-1.5f) = %a\n", ceilf(-1.5f)); /* R4 */
    /* _j0 >= 23: not finite (NaN/Inf) */
    printf("ceilf(INFINITY) = %a\n", ceilf(INFINITY)); /* R4 */
    printf("ceilf(NAN) = %a\n", ceilf(NAN)); /* R4 */
    /* _j0 >= 23: finite (large integer) */
    printf("ceilf(1e10f) = %a\n", ceilf(1e10f)); /* R4 */
    /* _j0 in [0,23): _j0 == 0 */
    printf("ceilf(1.25f) = %a\n", ceilf(1.25f)); /* R4 */
    printf("ceilf(-1.25f) = %a\n", ceilf(-1.25f)); /* R4 */
}

/* floord.c uncovered branches */
static void test_floor_extra3(void)
{
    printf("=== test_floor_extra3 ===\n"); /* R4 */
    /* _j0 in [0,20): _i0 < 0 (True) */
    printf("floor(-1.5) = %a\n", floor(-1.5)); /* R4 */
    /* _j0 > 51, _j0 == 0x400: Inf/NaN handled */
    printf("floor(INFINITY) = %a\n", floor(INFINITY)); /* R4 */
    printf("floor(NAN) = %a\n", floor(NAN)); /* R4 */
    /* _j0 > 51 but not 0x400: large integer */
    printf("floor(1e20) = %a\n", floor(1e20)); /* R4 */
    /* _j0 in [20,52): not integral, _i0 < 0, _j0==20 */
    printf("floor(-0x1.8p20) = %a\n", floor(-0x1.8p20)); /* R4 */
    /* _j0 in [20,52): not integral, _i0 < 0, _j0 != 20 */
    printf("floor(-0x1.0000000000001p30) = %a\n", floor(-0x1.0000000000001p30)); /* R4 */
    /* _j0 in [20,52): carry */
    printf("floor(-0x1.fffffffffffffp30) = %a\n", floor(-0x1.fffffffffffffp30)); /* R4 */
    /* floord line 99: _j0 > 51, False */
    printf("floor(-1e20) = %a\n", floor(-1e20)); /* R4 */
}

/* floorf.c uncovered branches */
static void test_floorf_extra3(void)
{
    printf("=== test_floorf_extra3 ===\n"); /* R4 */
    /* line 51: _i0 < 0 (True) */
    printf("floorf(-1.5f) = %a\n", floorf(-1.5f)); /* R4 */
    /* line 58: not finite */
    printf("floorf(INFINITY) = %a\n", floorf(INFINITY)); /* R4 */
    printf("floorf(NAN) = %a\n", floorf(NAN)); /* R4 */
    /* line 58: finite but large */
    printf("floorf(1e10f) = %a\n", floorf(1e10f)); /* R4 */
    printf("floorf(-0.3f) = %a\n", floorf(-0.3f)); /* R4 */
}

/* truncd.c uncovered branches */
static void test_trunc_extra3(void)
{
    printf("=== test_trunc_extra3 ===\n"); /* R4 */
    /* exponent < 20: True */
    printf("trunc(1.7) = %a\n", trunc(1.7)); /* R4 */
    /* exponent < 20: False → exponent in [20,51] */
    printf("trunc(0x1.4p25) = %a\n", trunc(0x1.4p25)); /* R4 */
    /* exponent < 0 (True): |x|<1 */
    printf("trunc(0.5) = %a\n", trunc(0.5)); /* R4 */
    /* exponent < 0 (False) but < 20: 1 <= |x| < 2 */
    printf("trunc(1.5) = %a\n", trunc(1.5)); /* R4 */
    /* exponent > 51: NaN/Inf case */
    printf("trunc(NAN) = %a\n", trunc(NAN)); /* R4 */
    printf("trunc(INFINITY) = %a\n", trunc(INFINITY)); /* R4 */
    /* exponent > 51 but not 1024: large exact integer */
    printf("trunc(1e20) = %a\n", trunc(1e20)); /* R4 */
    /* negative */
    printf("trunc(-1.7) = %a\n", trunc(-1.7)); /* R4 */
    printf("trunc(-0.5) = %a\n", trunc(-0.5)); /* R4 */
    /* exponent in [20,52): _j0 == 20 and _j0 > 20 */
    printf("trunc(0x1.8p20) = %a\n", trunc(0x1.8p20)); /* R4 */
    printf("trunc(-0x1.8p20) = %a\n", trunc(-0x1.8p20)); /* R4 */
    printf("trunc(0x1.0000000000001p40) = %a\n", trunc(0x1.0000000000001p40)); /* R4 */
}

/* truncf.c uncovered branches */
static void test_truncf_extra3(void)
{
    printf("=== test_truncf_extra3 ===\n"); /* R4 */
    /* exponent < 23: True */
    printf("truncf(1.7f) = %a\n", truncf(1.7f)); /* R4 */
    /* exponent < 23: False (>= 23) */
    printf("truncf(1e10f) = %a\n", truncf(1e10f)); /* R4 */
    /* exponent < 0: True */
    printf("truncf(0.5f) = %a\n", truncf(0.5f)); /* R4 */
    /* exponent < 0: False */
    printf("truncf(1.5f) = %a\n", truncf(1.5f)); /* R4 */
    /* exponent >= 23: == 128 (NaN/Inf) */
    printf("truncf(NAN) = %a\n", truncf(NAN)); /* R4 */
    printf("truncf(INFINITY) = %a\n", truncf(INFINITY)); /* R4 */
    /* negative */
    printf("truncf(-1.7f) = %a\n", truncf(-1.7f)); /* R4 */
    printf("truncf(-0.5f) = %a\n", truncf(-0.5f)); /* R4 */
}

/* fmaxd.c uncovered branches:
 * line 75:13 isnan(x) True/False
 * line 75:38 __issignaling(x) or __issignaling(y) True/False
 * line 85:13 isnan(y) True/False
 * line 99:12 x>y True/False
 */
static void test_fmax_extra3(void)
{
    printf("=== test_fmax_extra3 ===\n"); /* R4 */
    /* isnan(x) True, no signaling */
    printf("fmax(NAN, 2.0) = %a\n", fmax(NAN, 2.0)); /* R4 */
    /* isnan(x) True, x is sNaN */
    printf("fmax(__builtin_nans(\"\"), 2.0) = %a\n", fmax(__builtin_nans(""), 2.0)); /* R4 */
    /* isnan(x) True, y is sNaN */
    printf("fmax(NAN, __builtin_nans(\"\")) = %a\n", fmax(NAN, __builtin_nans(""))); /* R4 */
    /* isnan(y) True, no signaling */
    printf("fmax(2.0, NAN) = %a\n", fmax(2.0, NAN)); /* R4 */
    /* isnan(y) True, y is sNaN */
    printf("fmax(2.0, __builtin_nans(\"\")) = %a\n", fmax(2.0, __builtin_nans(""))); /* R4 */
    /* neither NaN: x > y (True) */
    printf("fmax(3.0, 2.0) = %a\n", fmax(3.0, 2.0)); /* R4 */
    /* neither NaN: x > y (False) */
    printf("fmax(1.0, 2.0) = %a\n", fmax(1.0, 2.0)); /* R4 */
    /* equal */
    printf("fmax(2.0, 2.0) = %a\n", fmax(2.0, 2.0)); /* R4 */
    /* negative values */
    printf("fmax(-1.0, -2.0) = %a\n", fmax(-1.0, -2.0)); /* R4 */
}

/* fmind.c uncovered branches: same structure as fmaxd.c */
static void test_fmin_extra3(void)
{
    printf("=== test_fmin_extra3 ===\n"); /* R4 */
    /* isnan(x) True, no signaling */
    printf("fmin(NAN, 2.0) = %a\n", fmin(NAN, 2.0)); /* R4 */
    /* isnan(x) True, x is sNaN */
    printf("fmin(__builtin_nans(\"\"), 2.0) = %a\n", fmin(__builtin_nans(""), 2.0)); /* R4 */
    /* isnan(x) True, y is sNaN */
    printf("fmin(NAN, __builtin_nans(\"\")) = %a\n", fmin(NAN, __builtin_nans(""))); /* R4 */
    /* isnan(y) True, no signaling */
    printf("fmin(2.0, NAN) = %a\n", fmin(2.0, NAN)); /* R4 */
    /* isnan(y) True, y is sNaN */
    printf("fmin(2.0, __builtin_nans(\"\")) = %a\n", fmin(2.0, __builtin_nans(""))); /* R4 */
    /* neither NaN: x < y (True) */
    printf("fmin(1.0, 2.0) = %a\n", fmin(1.0, 2.0)); /* R4 */
    /* neither NaN: x < y (False) */
    printf("fmin(3.0, 2.0) = %a\n", fmin(3.0, 2.0)); /* R4 */
    printf("fmin(-1.0, -2.0) = %a\n", fmin(-1.0, -2.0)); /* R4 */
}

/* fmaxf.c uncovered branches */
static void test_fmaxf_extra3(void)
{
    printf("=== test_fmaxf_extra3 ===\n"); /* R4 */
    printf("fmaxf(NAN, 2.0f) = %a\n", fmaxf(NAN, 2.0f)); /* R4 */
    printf("fmaxf(__builtin_nansf(\"\"), 2.0f) = %a\n", fmaxf(__builtin_nansf(""), 2.0f)); /* R4 */
    printf("fmaxf(NAN, __builtin_nansf(\"\")) = %a\n", fmaxf(NAN, __builtin_nansf(""))); /* R4 */
    printf("fmaxf(2.0f, NAN) = %a\n", fmaxf(2.0f, NAN)); /* R4 */
    printf("fmaxf(2.0f, __builtin_nansf(\"\")) = %a\n", fmaxf(2.0f, __builtin_nansf(""))); /* R4 */
    printf("fmaxf(3.0f, 2.0f) = %a\n", fmaxf(3.0f, 2.0f)); /* R4 */
    printf("fmaxf(1.0f, 2.0f) = %a\n", fmaxf(1.0f, 2.0f)); /* R4 */
    printf("fmaxf(-1.0f, -2.0f) = %a\n", fmaxf(-1.0f, -2.0f)); /* R4 */
}

/* fminf.c uncovered branches */
static void test_fminf_extra3(void)
{
    printf("=== test_fminf_extra3 ===\n"); /* R4 */
    printf("fminf(NAN, 2.0f) = %a\n", fminf(NAN, 2.0f)); /* R4 */
    printf("fminf(__builtin_nansf(\"\"), 2.0f) = %a\n", fminf(__builtin_nansf(""), 2.0f)); /* R4 */
    printf("fminf(NAN, __builtin_nansf(\"\")) = %a\n", fminf(NAN, __builtin_nansf(""))); /* R4 */
    printf("fminf(2.0f, NAN) = %a\n", fminf(2.0f, NAN)); /* R4 */
    printf("fminf(2.0f, __builtin_nansf(\"\")) = %a\n", fminf(2.0f, __builtin_nansf(""))); /* R4 */
    printf("fminf(1.0f, 2.0f) = %a\n", fminf(1.0f, 2.0f)); /* R4 */
    printf("fminf(3.0f, 2.0f) = %a\n", fminf(3.0f, 2.0f)); /* R4 */
    printf("fminf(-1.0f, -2.0f) = %a\n", fminf(-1.0f, -2.0f)); /* R4 */
}

/* fmodd.c uncovered branches */
static void test_fmod_extra3(void)
{
    printf("=== test_fmod_extra3 ===\n"); /* R4 */
    /* line 118: hx == 0x7ff00000 && lx == 0: x is +-Inf */
    printf("fmod(INFINITY, 1.0) = %a\n", fmod(INFINITY, 1.0)); /* R4 */
    printf("fmod(-INFINITY, 1.0) = %a\n", fmod(-INFINITY, 1.0)); /* R4 */
    /* line 118: False — x is NaN (not inf but exponent == inf) */
    printf("fmod(NAN, 1.0) = %a\n", fmod(NAN, 1.0)); /* R4 */
    printf("fmod(1.0, NAN) = %a\n", fmod(1.0, NAN)); /* R4 */
    /* x is finite but y is Inf (should return x) */
    printf("fmod(3.0, INFINITY) = %a\n", fmod(3.0, INFINITY)); /* R4 */
    /* line 132: |x| < |y| */
    printf("fmod(0.5, 3.0) = %a\n", fmod(0.5, 3.0)); /* R4 */
    /* line 132: |x| == |y| */
    printf("fmod(3.0, 3.0) = %a\n", fmod(3.0, 3.0)); /* R4 */
    printf("fmod(-3.0, 3.0) = %a\n", fmod(-3.0, 3.0)); /* R4 */
    /* subnormal x: hx == 0 */
    printf("fmod(0x1p-1074, 0x1p-1000) = %a\n", fmod(0x1p-1074, 0x1p-1000)); /* R4 */
    /* subnormal x: hx != 0 */
    printf("fmod(0x1p-1023, 0x1p-1000) = %a\n", fmod(0x1p-1023, 0x1p-1000)); /* R4 */
    /* subnormal y: hy == 0 */
    printf("fmod(0x1p-1000, 0x1p-1074) = %a\n", fmod(0x1p-1000, 0x1p-1074)); /* R4 */
    /* normal subtraction leading to exact zero */
    printf("fmod(6.0, 3.0) = %a\n", fmod(6.0, 3.0)); /* R4 */
    /* subnormal output (n = ix-iy is large) */
    printf("fmod(0x1p-1020, 0x1p-1074) = %a\n", fmod(0x1p-1020, 0x1p-1074)); /* R4 */
    /* line 237: result == 0 */
    printf("fmod(4.0, 2.0) = %a\n", fmod(4.0, 2.0)); /* R4 */
}

/* fmodf.c uncovered branches */
static void test_fmodf_extra3(void)
{
    printf("=== test_fmodf_extra3 ===\n"); /* R4 */
    /* line 33: x is +-Inf */
    printf("fmodf(INFINITY, 1.0f) = %a\n", fmodf(INFINITY, 1.0f)); /* R4 */
    /* line 35: x or y is NaN */
    printf("fmodf(NAN, 1.0f) = %a\n", fmodf(NAN, 1.0f)); /* R4 */
    printf("fmodf(1.0f, NAN) = %a\n", fmodf(1.0f, NAN)); /* R4 */
    /* line 40: y is +-0 */
    printf("fmodf(1.0f, 0.0f) = %a\n", fmodf(1.0f, 0.0f)); /* R4 */
    /* x < y */
    printf("fmodf(0.5f, 3.0f) = %a\n", fmodf(0.5f, 3.0f)); /* R4 */
    /* x == y */
    printf("fmodf(3.0f, 3.0f) = %a\n", fmodf(3.0f, 3.0f)); /* R4 */
    printf("fmodf(-3.0f, 3.0f) = %a\n", fmodf(-3.0f, 3.0f)); /* R4 */
    /* subnormal x */
    printf("fmodf(0x1p-149f, 0x1p-100f) = %a\n", fmodf(0x1p-149f, 0x1p-100f)); /* R4 */
    /* subnormal y */
    printf("fmodf(0x1p-100f, 0x1p-149f) = %a\n", fmodf(0x1p-100f, 0x1p-149f)); /* R4 */
    /* hz == 0 in loop: exact zero mid-loop */
    printf("fmodf(6.0f, 3.0f) = %a\n", fmodf(6.0f, 3.0f)); /* R4 */
    /* line 113: result == 0 */
    printf("fmodf(4.0f, 2.0f) = %a\n", fmodf(4.0f, 2.0f)); /* R4 */
    /* subnormal output */
    printf("fmodf(0x1p-120f, 0x1p-149f) = %a\n", fmodf(0x1p-120f, 0x1p-149f)); /* R4 */
    /* line 75: not subnormal x */
    printf("fmodf(5.0f, 3.0f) = %a\n", fmodf(5.0f, 3.0f)); /* R4 */
}

/* frexpd.c uncovered branches:
 * line 84:5 ix >= 0x7ff00000 or (ix|lx)==0 → True/False
 * line 85:8 ix < 0x00100000 (subnormal) → True
 */
static void test_frexp_extra3(void)
{
    printf("=== test_frexp_extra3 ===\n"); /* R4 */
    int e;
    /* line 84: True — Inf */
    printf("frexp(INFINITY, &e) = %a\n", frexp(INFINITY, &e)); /* R4 */
    /* line 84: True — NaN */
    printf("frexp(NAN, &e) = %a\n", frexp(NAN, &e)); /* R4 */
    /* line 84: True — zero */
    printf("frexp(0.0, &e) = %a\n", frexp(0.0, &e)); /* R4 */
    /* line 84: False — normal */
    printf("frexp(4.0, &e) = %a, e=%d\n", frexp(4.0, &e), e); /* R4 */
    /* line 85: True — subnormal */
    printf("frexp(0x1p-1074, &e) = %a, e=%d\n", frexp(0x1p-1074, &e), e); /* R4 */
    printf("frexp(0x1p-1022, &e) = %a, e=%d\n", frexp(0x1p-1022, &e), e); /* R4 */
    /* negative normal */
    printf("frexp(-8.0, &e) = %a, e=%d\n", frexp(-8.0, &e), e); /* R4 */
}

/* frexpf.c uncovered branches */
static void test_frexpf_extra3(void)
{
    printf("=== test_frexpf_extra3 ===\n"); /* R4 */
    int e;
    printf("frexpf(INFINITY, &e) = %a\n", frexpf(INFINITY, &e)); /* R4 */
    printf("frexpf(NAN, &e) = %a\n", frexpf(NAN, &e)); /* R4 */
    printf("frexpf(0.0f, &e) = %a\n", frexpf(0.0f, &e)); /* R4 */
    printf("frexpf(4.0f, &e) = %a, e=%d\n", frexpf(4.0f, &e), e); /* R4 */
    /* subnormal */
    printf("frexpf(0x1p-149f, &e) = %a, e=%d\n", frexpf(0x1p-149f, &e), e); /* R4 */
    printf("frexpf(-8.0f, &e) = %a, e=%d\n", frexpf(-8.0f, &e), e); /* R4 */
}

/* modfd.c uncovered branches:
 * line 73:5 iptr == NULL (True/False)
 * line 74:8 iptr == NULL True
 */
static void test_modf_extra3(void)
{
    printf("=== test_modf_extra3 ===\n"); /* R4 */
    double ipart;
    /* normal */
    printf("modf(3.7, &ipart) = %a, ipart=%a\n", modf(3.7, &ipart), ipart); /* R4 */
    printf("modf(-3.7, &ipart) = %a, ipart=%a\n", modf(-3.7, &ipart), ipart); /* R4 */
    /* |x| < 1 */
    printf("modf(0.5, &ipart) = %a, ipart=%a\n", modf(0.5, &ipart), ipart); /* R4 */
    /* |x| >= 2^20 (integer, high exponent) */
    printf("modf(1e6, &ipart) = %a, ipart=%a\n", modf(1e6, &ipart), ipart); /* R4 */
    /* Inf */
    printf("modf(INFINITY, &ipart) = %a, ipart=%a\n", modf(INFINITY, &ipart), ipart); /* R4 */
    /* NaN */
    printf("modf(NAN, &ipart) = %a\n", modf(NAN, &ipart)); /* R4 */
}

/* modff.c uncovered branches */
static void test_modff_extra3(void)
{
    printf("=== test_modff_extra3 ===\n"); /* R4 */
    float ipart;
    printf("modff(3.7f, &ipart) = %a, ipart=%a\n", modff(3.7f, &ipart), ipart); /* R4 */
    printf("modff(-3.7f, &ipart) = %a, ipart=%a\n", modff(-3.7f, &ipart), ipart); /* R4 */
    printf("modff(0.5f, &ipart) = %a, ipart=%a\n", modff(0.5f, &ipart), ipart); /* R4 */
    printf("modff(1e6f, &ipart) = %a, ipart=%a\n", modff(1e6f, &ipart), ipart); /* R4 */
    printf("modff(INFINITY, &ipart) = %a, ipart=%a\n", modff(INFINITY, &ipart), ipart); /* R4 */
    printf("modff(NAN, &ipart) = %a\n", modff(NAN, &ipart)); /* R4 */
}

/* remainderd.c uncovered branches */
static void test_remainder_extra3(void)
{
    printf("=== test_remainder_extra3 ===\n"); /* R4 */
    /* line 136: x == y */
    printf("remainder(3.0, 3.0) = %a\n", remainder(3.0, 3.0)); /* R4 */
    printf("remainder(-3.0, 3.0) = %a\n", remainder(-3.0, 3.0)); /* R4 */
    /* line 147: hy < 0x00200000 branch (True) — small y */
    printf("remainder(1.0, 0x1p-1022) = %a\n", remainder(1.0, 0x1p-1022)); /* R4 */
    /* line 147: hy >= 0x00200000 (False) — normal y */
    printf("remainder(3.0, 2.0) = %a\n", remainder(3.0, 2.0)); /* R4 */
    printf("remainder(5.5, 2.0) = %a\n", remainder(5.5, 2.0)); /* R4 */
    /* NaN */
    printf("remainder(NAN, 1.0) = %a\n", remainder(NAN, 1.0)); /* R4 */
    /* Inf */
    printf("remainder(INFINITY, 1.0) = %a\n", remainder(INFINITY, 1.0)); /* R4 */
    printf("remainder(1.0, INFINITY) = %a\n", remainder(1.0, INFINITY)); /* R4 */
}

/* remainderf.c uncovered branches */
static void test_remainderf_extra3(void)
{
    printf("=== test_remainderf_extra3 ===\n"); /* R4 */
    /* line 40: hx == hy (x == y) */
    printf("remainderf(3.0f, 3.0f) = %a\n", remainderf(3.0f, 3.0f)); /* R4 */
    printf("remainderf(-3.0f, 3.0f) = %a\n", remainderf(-3.0f, 3.0f)); /* R4 */
    /* line 47: hy < 0x01000000 True (small y) */
    printf("remainderf(1.0f, 0x1p-126f) = %a\n", remainderf(1.0f, 0x1p-126f)); /* R4 */
    /* line 47: False (normal y) */
    printf("remainderf(3.0f, 2.0f) = %a\n", remainderf(3.0f, 2.0f)); /* R4 */
    printf("remainderf(5.5f, 2.0f) = %a\n", remainderf(5.5f, 2.0f)); /* R4 */
    /* line 48: x+x > y (True) */
    printf("remainderf(0.7f, 0.5f) = %a\n", remainderf(0.7f, 0.5f)); /* R4 */
    /* line 48: x+x > y (False) */
    printf("remainderf(0.2f, 0.5f) = %a\n", remainderf(0.2f, 0.5f)); /* R4 */
    /* line 51: x+x >= y (True) */
    printf("remainderf(0.9f, 0.5f) = %a\n", remainderf(0.9f, 0.5f)); /* R4 */
    /* NaN/Inf */
    printf("remainderf(INFINITY, 1.0f) = %a\n", remainderf(INFINITY, 1.0f)); /* R4 */
}

/* remquod.c uncovered branches */
static void test_remquo_extra3(void)
{
    printf("=== test_remquo_extra3 ===\n"); /* R4 */
    int q;
    /* line 119: quo == NULL (True/False) — both via normal call */
    printf("remquo(3.0, 2.0, &q) = %a, q=%d\n", remquo(3.0, 2.0, &q), q); /* R4 */
    /* line 120: inside assert path — use valid pointer always */
    /* line 151: x == y */
    printf("remquo(3.0, 3.0, &q) = %a, q=%d\n", remquo(3.0, 3.0, &q), q); /* R4 */
    printf("remquo(-3.0, 3.0, &q) = %a, q=%d\n", remquo(-3.0, 3.0, &q), q); /* R4 */
    /* line 152: sq nonzero (opposite signs) */
    printf("remquo(-3.0, -3.0, &q) = %a, q=%d\n", remquo(-3.0, -3.0, &q), q); /* R4 */
    printf("remquo(3.0, -3.0, &q) = %a, q=%d\n", remquo(3.0, -3.0, &q), q); /* R4 */
    /* line 169: hy < 0x00200000 (small y) */
    printf("remquo(1.0, 0x1p-1022, &q) = %a, q=%d\n", remquo(1.0, 0x1p-1022, &q), q); /* R4 */
    /* line 174: normal y, large quotient */
    printf("remquo(10.5, 2.0, &q) = %a, q=%d\n", remquo(10.5, 2.0, &q), q); /* R4 */
    printf("remquo(5.5, 2.0, &q) = %a, q=%d\n", remquo(5.5, 2.0, &q), q); /* R4 */
    /* NaN */
    printf("remquo(NAN, 1.0, &q) = %a\n", remquo(NAN, 1.0, &q)); /* R4 */
    /* Inf */
    printf("remquo(INFINITY, 1.0, &q) = %a\n", remquo(INFINITY, 1.0, &q)); /* R4 */
}

/* remquof.c uncovered branches */
static void test_remquof_extra3(void)
{
    printf("=== test_remquof_extra3 ===\n"); /* R4 */
    int q;
    printf("remquof(3.0f, 2.0f, &q) = %a, q=%d\n", remquof(3.0f, 2.0f, &q), q); /* R4 */
    /* x == y (hx == hy) */
    printf("remquof(3.0f, 3.0f, &q) = %a, q=%d\n", remquof(3.0f, 3.0f, &q), q); /* R4 */
    printf("remquof(-3.0f, 3.0f, &q) = %a, q=%d\n", remquof(-3.0f, 3.0f, &q), q); /* R4 */
    printf("remquof(3.0f, -3.0f, &q) = %a, q=%d\n", remquof(3.0f, -3.0f, &q), q); /* R4 */
    /* hy < 0x01000000 (small y): line 66 True */
    printf("remquof(1.0f, 0x1p-126f, &q) = %a, q=%d\n", remquof(1.0f, 0x1p-126f, &q), q); /* R4 */
    /* large quotient: x >= 4y, x >= 2y */
    printf("remquof(10.5f, 2.0f, &q) = %a, q=%d\n", remquof(10.5f, 2.0f, &q), q); /* R4 */
    /* line 67: x+x > y (True) */
    printf("remquof(0.7f, 0.5f, &q) = %a, q=%d\n", remquof(0.7f, 0.5f, &q), q); /* R4 */
    /* line 67: False */
    printf("remquof(0.2f, 0.5f, &q) = %a, q=%d\n", remquof(0.2f, 0.5f, &q), q); /* R4 */
    /* line 71: x+x >= y (True) */
    printf("remquof(0.9f, 0.5f, &q) = %a, q=%d\n", remquof(0.9f, 0.5f, &q), q); /* R4 */
    printf("remquof(INFINITY, 1.0f, &q) = %a\n", remquof(INFINITY, 1.0f, &q)); /* R4 */
    printf("remquof(NAN, 1.0f, &q) = %a\n", remquof(NAN, 1.0f, &q)); /* R4 */
}

/* nextafterd.c uncovered branches */
static void test_nextafter_extra3(void)
{
    printf("=== test_nextafter_extra3 ===\n"); /* R4 */
    /* line 95: x == 0 */
    printf("nextafter(0.0, 1.0) = %a\n", nextafter(0.0, 1.0)); /* R4 */
    printf("nextafter(0.0, -1.0) = %a\n", nextafter(0.0, -1.0)); /* R4 */
    /* line 95:40 ix == hy & 0x7fffffff && ly == 0 (True) → |x| == |y| */
    printf("nextafter(1.0, 1.0) = %a\n", nextafter(1.0, 1.0)); /* R4 */
    /* line 95:40 False */
    printf("nextafter(1.0, 2.0) = %a\n", nextafter(1.0, 2.0)); /* R4 */
    /* line 106: lx == 0, hx decrements */
    printf("nextafter(1.0, 0.0) = %a\n", nextafter(1.0, 0.0)); /* R4 */
    /* line 120: hx >= 0, hx > hy (True) */
    printf("nextafter(2.0, 1.0) = %a\n", nextafter(2.0, 1.0)); /* R4 */
    /* line 120:50 lx == 0 (True) */
    printf("nextafter(0x1p10, 0.0) = %a\n", nextafter(0x1p10, 0.0)); /* R4 */
    /* x < 0 */
    printf("nextafter(-1.0, 0.0) = %a\n", nextafter(-1.0, 0.0)); /* R4 */
    printf("nextafter(-1.0, -2.0) = %a\n", nextafter(-1.0, -2.0)); /* R4 */
    /* overflow path: x near max */
    printf("nextafter(0x1.fffffffffffffp1023, INFINITY) = %a\n", /* R4 */
           nextafter(0x1.fffffffffffffp1023, INFINITY));
    /* underflow path (subnormal result) */
    printf("nextafter(0x1p-1074, 0.0) = %a\n", nextafter(0x1p-1074, 0.0)); /* R4 */
    printf("nextafter(0x1p-1022, 0.0) = %a\n", nextafter(0x1p-1022, 0.0)); /* R4 */
}

/* nextafterf.c uncovered branches */
static void test_nextafterf_extra3(void)
{
    printf("=== test_nextafterf_extra3 ===\n"); /* R4 */
    /* line 27: ix == 0 */
    printf("nextafterf(0.0f, 1.0f) = %a\n", nextafterf(0.0f, 1.0f)); /* R4 */
    printf("nextafterf(0.0f, -1.0f) = %a\n", nextafterf(0.0f, -1.0f)); /* R4 */
    printf("nextafterf(1.0f, 1.0f) = %a\n", nextafterf(1.0f, 1.0f)); /* R4 */
    printf("nextafterf(1.0f, 2.0f) = %a\n", nextafterf(1.0f, 2.0f)); /* R4 */
    printf("nextafterf(1.0f, 0.0f) = %a\n", nextafterf(1.0f, 0.0f)); /* R4 */
    printf("nextafterf(-1.0f, 0.0f) = %a\n", nextafterf(-1.0f, 0.0f)); /* R4 */
    printf("nextafterf(0x1.fffffep127f, INFINITY) = %a\n", /* R4 */
           nextafterf(0x1.fffffep127f, INFINITY));
    printf("nextafterf(0x1p-149f, 0.0f) = %a\n", nextafterf(0x1p-149f, 0.0f)); /* R4 */
}

/* scalbnd.c uncovered branches */
static void test_scalbn_extra3(void)
{
    printf("=== test_scalbn_extra3 ===\n"); /* R4 */
    /* line 105: k == 0 subnormal x */
    printf("scalbn(0x1p-1074, 10) = %a\n", scalbn(0x1p-1074, 10)); /* R4 */
    printf("scalbn(0x1p-1022, -10) = %a\n", scalbn(0x1p-1022, -10)); /* R4 */
    /* normal */
    printf("scalbn(1.0, 10) = %a\n", scalbn(1.0, 10)); /* R4 */
    printf("scalbn(1.0, -10) = %a\n", scalbn(1.0, -10)); /* R4 */
    /* n < -50000 underflow */
    printf("scalbn(1.0, -60000) = %a\n", scalbn(1.0, -60000)); /* R4 */
    /* n > 50000 overflow */
    printf("scalbn(1.0, 60000) = %a\n", scalbn(1.0, 60000)); /* R4 */
    /* zero input */
    printf("scalbn(0.0, 5) = %a\n", scalbn(0.0, 5)); /* R4 */
    /* NaN/Inf */
    printf("scalbn(NAN, 5) = %a\n", scalbn(NAN, 5)); /* R4 */
    printf("scalbn(INFINITY, 5) = %a\n", scalbn(INFINITY, 5)); /* R4 */
}

/* scalbnf.c uncovered branches */
static void test_scalbnf_extra3(void)
{
    printf("=== test_scalbnf_extra3 ===\n"); /* R4 */
    printf("scalbnf(0x1p-149f, 10) = %a\n", scalbnf(0x1p-149f, 10)); /* R4 */
    printf("scalbnf(0x1p-126f, -10) = %a\n", scalbnf(0x1p-126f, -10)); /* R4 */
    printf("scalbnf(1.0f, 10) = %a\n", scalbnf(1.0f, 10)); /* R4 */
    printf("scalbnf(1.0f, -60000) = %a\n", scalbnf(1.0f, -60000)); /* R4 */
    printf("scalbnf(1.0f, 60000) = %a\n", scalbnf(1.0f, 60000)); /* R4 */
    printf("scalbnf(0.0f, 5) = %a\n", scalbnf(0.0f, 5)); /* R4 */
    printf("scalbnf(NAN, 5) = %a\n", scalbnf(NAN, 5)); /* R4 */
    printf("scalbnf(INFINITY, 5) = %a\n", scalbnf(INFINITY, 5)); /* R4 */
}

/* sqrtd.c uncovered branches */
static void test_sqrt_extra3(void)
{
    printf("=== test_sqrt_extra3 ===\n"); /* R4 */
    /* line 73:20 ix0 <= 0: True — ix0 < 0 (negative) */
    printf("sqrt(-1.0) = %a\n", sqrt(-1.0)); /* R4 */
    /* line 73:20 ix0 <= 0: True — ix0 == 0 (zero) */
    printf("sqrt(0.0) = %a\n", sqrt(0.0)); /* R4 */
    printf("sqrt(-0.0) = %a\n", sqrt(-0.0)); /* R4 */
    /* line 106: m == 0 (subnormal) */
    printf("sqrt(0x1p-1074) = %a\n", sqrt(0x1p-1074)); /* R4 */
    printf("sqrt(0x1p-1022) = %a\n", sqrt(0x1p-1022)); /* R4 */
    /* line 148: inner condition: t < ix0 or (t==ix0 and t1 <= ix1) */
    printf("sqrt(2.0) = %a\n", sqrt(2.0)); /* R4 */
    printf("sqrt(3.0) = %a\n", sqrt(3.0)); /* R4 */
    /* line 173: inexact rounding */
    printf("sqrt(0.5) = %a\n", sqrt(0.5)); /* R4 */
    /* NaN/Inf from line 70 */
    printf("sqrt(NAN) = %a\n", sqrt(NAN)); /* R4 */
    printf("sqrt(INFINITY) = %a\n", sqrt(INFINITY)); /* R4 */
    printf("sqrt(-INFINITY) = %a\n", sqrt(-INFINITY)); /* R4 */
}

/* sqrtf.c uncovered branches */
static void test_sqrtf_extra3(void)
{
    printf("=== test_sqrtf_extra3 ===\n"); /* R4 */
    /* line 25:20 FLT_UWORD_IS_ZERO (True) */
    printf("sqrtf(0.0f) = %a\n", sqrtf(0.0f)); /* R4 */
    /* line 25:20 FLT_UWORD_IS_ZERO (False) → negative: invalid */
    printf("sqrtf(-1.0f) = %a\n", sqrtf(-1.0f)); /* R4 */
    /* subnormal */
    printf("sqrtf(0x1p-149f) = %a\n", sqrtf(0x1p-149f)); /* R4 */
    printf("sqrtf(2.0f) = %a\n", sqrtf(2.0f)); /* R4 */
    printf("sqrtf(NAN) = %a\n", sqrtf(NAN)); /* R4 */
}

/* atan2d.c uncovered branches */
static void test_atan2_extra3(void)
{
    printf("=== test_atan2_extra3 ===\n"); /* R4 */
    /* line 116: x=1.0 (True) */
    printf("atan2(1.0, 1.0) = %a\n", atan2(1.0, 1.0)); /* R4 */
    /* line 138: both INF, m=2 (True) */
    printf("atan2(INFINITY, -INFINITY) = %a\n", atan2(INFINITY, -INFINITY)); /* R4 */
    /* line 138: m=3 */
    printf("atan2(-INFINITY, -INFINITY) = %a\n", atan2(-INFINITY, -INFINITY)); /* R4 */
    /* line 153: y is INF */
    printf("atan2(INFINITY, 0.0) = %a\n", atan2(INFINITY, 0.0)); /* R4 */
    printf("atan2(-INFINITY, 0.0) = %a\n", atan2(-INFINITY, 0.0)); /* R4 */
    /* x=+0 */
    printf("atan2(1.0, 0.0) = %a\n", atan2(1.0, 0.0)); /* R4 */
    printf("atan2(-1.0, 0.0) = %a\n", atan2(-1.0, 0.0)); /* R4 */
    /* y=+0 */
    printf("atan2(0.0, -1.0) = %a\n", atan2(0.0, -1.0)); /* R4 */
    printf("atan2(-0.0, -1.0) = %a\n", atan2(-0.0, -1.0)); /* R4 */
    /* NaN */
    printf("atan2(NAN, 1.0) = %a\n", atan2(NAN, 1.0)); /* R4 */
    printf("atan2(1.0, NAN) = %a\n", atan2(1.0, NAN)); /* R4 */
}

/* atan2f.c uncovered branches */
static void test_atan2f_extra3(void)
{
    printf("=== test_atan2f_extra3 ===\n"); /* R4 */
    /* line 44: x=1.0 */
    printf("atan2f(1.0f, 1.0f) = %a\n", atan2f(1.0f, 1.0f)); /* R4 */
    /* line 66: both INF */
    printf("atan2f(INFINITY, -INFINITY) = %a\n", atan2f(INFINITY, -INFINITY)); /* R4 */
    printf("atan2f(-INFINITY, -INFINITY) = %a\n", atan2f(-INFINITY, -INFINITY)); /* R4 */
    /* line 81: y is INF */
    printf("atan2f(INFINITY, 0.0f) = %a\n", atan2f(INFINITY, 0.0f)); /* R4 */
    printf("atan2f(-INFINITY, 0.0f) = %a\n", atan2f(-INFINITY, 0.0f)); /* R4 */
    printf("atan2f(1.0f, 0.0f) = %a\n", atan2f(1.0f, 0.0f)); /* R4 */
    printf("atan2f(0.0f, -1.0f) = %a\n", atan2f(0.0f, -1.0f)); /* R4 */
    printf("atan2f(NAN, 1.0f) = %a\n", atan2f(NAN, 1.0f)); /* R4 */
}

/* tand.c uncovered branches */
static void test_tan_extra3(void)
{
    printf("=== test_tan_extra3 ===\n"); /* R4 */
    /* line 98: ix >= 0x3FE59428 (|x| >= 0.6744), hx < 0 (True) */
    printf("__tan(-0.8, 0.0, 1) = %a\n", bridge___tan(-0.8, 0.0, 1)); /* R4 */
    printf("__tan(-0.8, 0.0, -1) = %a\n", bridge___tan(-0.8, 0.0, -1)); /* R4 */
    /* line 98: False, iy==1 */
    printf("__tan(0.3, 0.0, 1) = %a\n", bridge___tan(0.3, 0.0, 1)); /* R4 */
    /* line 99: ix >= 0x3FE59428, iy==1 (True) — return via formula */
    printf("__tan(0.8, 0.0, 1) = %a\n", bridge___tan(0.8, 0.0, 1)); /* R4 */
    /* line 99: False, iy==-1 */
    printf("__tan(0.8, 0.0, -1) = %a\n", bridge___tan(0.8, 0.0, -1)); /* R4 */
    /* line 123: ix >= 0x3FE59428 True after normalization */
    /* public tan: large arg reduction */
    printf("tan(100.0) = %a\n", tan(100.0)); /* R4 */
    printf("tan(-100.0) = %a\n", tan(-100.0)); /* R4 */
    /* tan NaN/Inf */
    printf("tan(NAN) = %a\n", tan(NAN)); /* R4 */
    printf("tan(INFINITY) = %a\n", tan(INFINITY)); /* R4 */
}

/* tanf.c uncovered branches */
static void test_tanf_extra3(void)
{
    printf("=== test_tanf_extra3 ===\n"); /* R4 */
    /* ix >= 0x3f2ca140 (|x| >= 0.6744f), hx < 0 True */
    printf("__tanf(-0.8f, 0.0f, 1) = %a\n", bridge___tanf(-0.8f, 0.0f, 1)); /* R4 */
    printf("__tanf(-0.8f, 0.0f, -1) = %a\n", bridge___tanf(-0.8f, 0.0f, -1)); /* R4 */
    printf("__tanf(0.3f, 0.0f, 1) = %a\n", bridge___tanf(0.3f, 0.0f, 1)); /* R4 */
    printf("__tanf(0.8f, 0.0f, 1) = %a\n", bridge___tanf(0.8f, 0.0f, 1)); /* R4 */
    printf("__tanf(0.8f, 0.0f, -1) = %a\n", bridge___tanf(0.8f, 0.0f, -1)); /* R4 */
    /* line 61: ix >= threshold after second branch */
    printf("tanf(100.0f) = %a\n", tanf(100.0f)); /* R4 */
    printf("tanf(-100.0f) = %a\n", tanf(-100.0f)); /* R4 */
    printf("tanf(NAN) = %a\n", tanf(NAN)); /* R4 */
    printf("tanf(INFINITY) = %a\n", tanf(INFINITY)); /* R4 */
}

/* trigd.c (internal) uncovered branches — exercise via sin/cos/tan with large args */
static void test_trig_internal_extra3(void)
{
    printf("=== test_trig_internal_extra3 ===\n"); /* R4 */
    /* Large arguments trigger __rem_pio2 medium/large paths */
    /* |x| in (3pi/4, 2^19*pi/2) medium size path */
    printf("sin(5.0) = %a\n", sin(5.0)); /* R4 */
    printf("cos(5.0) = %a\n", cos(5.0)); /* R4 */
    printf("sin(100.0) = %a\n", sin(100.0)); /* R4 */
    printf("cos(100.0) = %a\n", cos(100.0)); /* R4 */
    printf("sin(1e15) = %a\n", sin(1e15)); /* R4 */
    printf("cos(1e15) = %a\n", cos(1e15)); /* R4 */
    /* Very large (> 2^19*pi/2): uses __rem_pio2_internal */
    printf("sin(1e100) = %a\n", sin(1e100)); /* R4 */
    printf("cos(1e100) = %a\n", cos(1e100)); /* R4 */
    /* NaN/Inf in __rem_pio2 */
    printf("sin(INFINITY) = %a\n", sin(INFINITY)); /* R4 */
    printf("cos(INFINITY) = %a\n", cos(INFINITY)); /* R4 */
    /* Negative large */
    printf("sin(-1e100) = %a\n", sin(-1e100)); /* R4 */
    printf("cos(-1e100) = %a\n", cos(-1e100)); /* R4 */
    /* hx < 0 for medium path */
    printf("sin(-100.0) = %a\n", sin(-100.0)); /* R4 */
    printf("cos(-100.0) = %a\n", cos(-100.0)); /* R4 */
    /* ix == 0x3ff921fb (near pi/2) */
    printf("sin(1.5707963267948966) = %a\n", sin(1.5707963267948966)); /* R4 */
    printf("cos(1.5707963267948966) = %a\n", cos(1.5707963267948966)); /* R4 */
    /* negative near pi/2 */
    printf("sin(-1.5707963267948966) = %a\n", sin(-1.5707963267948966)); /* R4 */
}

/* trigf.c (internal) uncovered branches */
static void test_trigf_internal_extra3(void)
{
    printf("=== test_trigf_internal_extra3 ===\n"); /* R4 */
    printf("sinf(5.0f) = %a\n", sinf(5.0f)); /* R4 */
    printf("cosf(5.0f) = %a\n", cosf(5.0f)); /* R4 */
    printf("sinf(100.0f) = %a\n", sinf(100.0f)); /* R4 */
    printf("cosf(100.0f) = %a\n", cosf(100.0f)); /* R4 */
    printf("sinf(1e10f) = %a\n", sinf(1e10f)); /* R4 */
    printf("cosf(1e10f) = %a\n", cosf(1e10f)); /* R4 */
    printf("sinf(1e30f) = %a\n", sinf(1e30f)); /* R4 */
    printf("cosf(1e30f) = %a\n", cosf(1e30f)); /* R4 */
    printf("sinf(INFINITY) = %a\n", sinf(INFINITY)); /* R4 */
    printf("cosf(INFINITY) = %a\n", cosf(INFINITY)); /* R4 */
    printf("sinf(-100.0f) = %a\n", sinf(-100.0f)); /* R4 */
    printf("cosf(-100.0f) = %a\n", cosf(-100.0f)); /* R4 */
    printf("sinf(-1e30f) = %a\n", sinf(-1e30f)); /* R4 */
    /* near pi/2 for float */
    printf("sinf(1.5707963f) = %a\n", sinf(1.5707963f)); /* R4 */
    printf("cosf(1.5707963f) = %a\n", cosf(1.5707963f)); /* R4 */
}

/* gammad.c (internal) uncovered branches */
static void test_gamma_extra3(void)
{
    printf("=== test_gamma_extra3 ===\n"); /* R4 */
    int sign;
    /* line 218: ix < 0x3b900000 (|x| < 2^-70) */
    printf("lgamma(0x1p-80) = %a\n", lgamma(0x1p-80)); /* R4 */
    printf("lgamma(-0x1p-80) = %a\n", lgamma(-0x1p-80)); /* R4 */
    /* line 244: switch case 1 in __sin_pi */
    printf("lgamma(-1.25) = %a\n", lgamma(-1.25)); /* R4 */
    /* line 248: case 2 in __sin_pi */
    printf("lgamma(-1.75) = %a\n", lgamma(-1.75)); /* R4 */
    /* line 249: case 3 in __sin_pi */
    printf("lgamma(-2.25) = %a\n", lgamma(-2.25)); /* R4 */
    /* line 253: case 4 in __sin_pi */
    printf("lgamma(-2.75) = %a\n", lgamma(-2.75)); /* R4 */
    /* line 254: case 5 in __sin_pi */
    printf("lgamma(-3.25) = %a\n", lgamma(-3.25)); /* R4 */
    /* line 258: case 6 in __sin_pi */
    printf("lgamma(-3.75) = %a\n", lgamma(-3.75)); /* R4 */
    /* line 263: case 7 (default) in __sin_pi */
    printf("lgamma(-4.25) = %a\n", lgamma(-4.25)); /* R4 */
    /* line 357: negative x, t < zero */
    printf("lgamma(-0.5) = %a\n", lgamma(-0.5)); /* R4 */
    printf("lgamma(-1.5) = %a\n", lgamma(-1.5)); /* R4 */
    /* via __lgamma */
    printf("__lgamma(0x1p-80, &sign) = %a\n", __lgamma(0x1p-80, &sign)); /* R4 */
    printf("__lgamma(-0.5, &sign) = %a, sign=%d\n", __lgamma(-0.5, &sign), sign); /* R4 */
}

/* gammaf.c (internal) uncovered branches — many switch/range branches */
static void test_gammaf_extra3(void)
{
    printf("=== test_gammaf_extra3 ===\n"); /* R4 */
    int sign;
    /* line 113: ix == 0 (zero input) */
    printf("lgammaf(0.0f) = %a\n", lgammaf(0.0f)); /* R4 */
    printf("lgammaf(-0.0f) = %a\n", lgammaf(-0.0f)); /* R4 */
    /* line 117: ix < 0x30800000 (|x| < 2^-30), positive */
    printf("lgammaf(0x1p-40f) = %a\n", lgammaf(0x1p-40f)); /* R4 */
    /* line 118: negative tiny */
    printf("lgammaf(-0x1p-40f) = %a\n", lgammaf(-0x1p-40f)); /* R4 */
    /* line 122: ix >= 0x4b000000 (large negative integer) */
    printf("lgammaf(-1e8f) = %a\n", lgammaf(-1e8f)); /* R4 */
    /* line 123: negative non-integer */
    printf("lgammaf(-0.5f) = %a\n", lgammaf(-0.5f)); /* R4 */
    /* line 127: t < zero (negative sin_pi) */
    printf("lgammaf(-1.5f) = %a\n", lgammaf(-1.5f)); /* R4 */
    /* line 132: case 0 in __sin_pif switch */
    printf("lgammaf(-0.1f) = %a\n", lgammaf(-0.1f)); /* R4 */
    /* various x in (0,8) ranges */
    printf("lgammaf(0.5f) = %a\n", lgammaf(0.5f)); /* R4 */
    printf("lgammaf(0.8f) = %a\n", lgammaf(0.8f)); /* R4 */
    printf("lgammaf(1.0f) = %a\n", lgammaf(1.0f)); /* R4 */
    printf("lgammaf(1.3f) = %a\n", lgammaf(1.3f)); /* R4 */
    printf("lgammaf(1.5f) = %a\n", lgammaf(1.5f)); /* R4 */
    printf("lgammaf(1.8f) = %a\n", lgammaf(1.8f)); /* R4 */
    printf("lgammaf(2.0f) = %a\n", lgammaf(2.0f)); /* R4 */
    printf("lgammaf(2.5f) = %a\n", lgammaf(2.5f)); /* R4 */
    printf("lgammaf(3.0f) = %a\n", lgammaf(3.0f)); /* R4 */
    printf("lgammaf(3.5f) = %a\n", lgammaf(3.5f)); /* R4 */
    printf("lgammaf(4.0f) = %a\n", lgammaf(4.0f)); /* R4 */
    printf("lgammaf(4.5f) = %a\n", lgammaf(4.5f)); /* R4 */
    printf("lgammaf(5.0f) = %a\n", lgammaf(5.0f)); /* R4 */
    printf("lgammaf(6.0f) = %a\n", lgammaf(6.0f)); /* R4 */
    printf("lgammaf(7.0f) = %a\n", lgammaf(7.0f)); /* R4 */
    printf("lgammaf(7.5f) = %a\n", lgammaf(7.5f)); /* R4 */
    /* x in [8, 2^58) */
    printf("lgammaf(10.0f) = %a\n", lgammaf(10.0f)); /* R4 */
    printf("lgammaf(100.0f) = %a\n", lgammaf(100.0f)); /* R4 */
    /* x >= 2^58 */
    printf("lgammaf(1e18f) = %a\n", lgammaf(1e18f)); /* R4 */
    /* NaN/Inf */
    printf("lgammaf(NAN) = %a\n", lgammaf(NAN)); /* R4 */
    printf("lgammaf(INFINITY) = %a\n", lgammaf(INFINITY)); /* R4 */
    /* negative integer */
    printf("lgammaf(-2.0f) = %a\n", lgammaf(-2.0f)); /* R4 */
    /* via __lgammaf */
    printf("__lgammaf(0.5f, &sign) = %a, sign=%d\n", __lgammaf(0.5f, &sign), sign); /* R4 */
    printf("__lgammaf(-0.5f, &sign) = %a, sign=%d\n", __lgammaf(-0.5f, &sign), sign); /* R4 */
    printf("__lgammaf(-1.25f, &sign) = %a, sign=%d\n", __lgammaf(-1.25f, &sign), sign); /* R4 */
    printf("__lgammaf(-1.75f, &sign) = %a, sign=%d\n", __lgammaf(-1.75f, &sign), sign); /* R4 */
    printf("__lgammaf(-2.25f, &sign) = %a, sign=%d\n", __lgammaf(-2.25f, &sign), sign); /* R4 */
    printf("__lgammaf(-2.75f, &sign) = %a, sign=%d\n", __lgammaf(-2.75f, &sign), sign); /* R4 */
    printf("__lgammaf(-3.25f, &sign) = %a, sign=%d\n", __lgammaf(-3.25f, &sign), sign); /* R4 */
    printf("__lgammaf(-3.75f, &sign) = %a, sign=%d\n", __lgammaf(-3.75f, &sign), sign); /* R4 */
    printf("__lgammaf(-4.25f, &sign) = %a, sign=%d\n", __lgammaf(-4.25f, &sign), sign); /* R4 */
}

/* hypotd.c uncovered branches */
static void test_hypot_extra3(void)
{
    printf("=== test_hypot_extra3 ===\n"); /* R4 */
    /* line 108: ha >= 0x7ff00000 (Inf or NaN) */
    printf("hypot(INFINITY, 1.0) = %a\n", hypot(INFINITY, 1.0)); /* R4 */
    printf("hypot(1.0, INFINITY) = %a\n", hypot(1.0, INFINITY)); /* R4 */
    printf("hypot(NAN, 1.0) = %a\n", hypot(NAN, 1.0)); /* R4 */
    /* line 113: scaled to large: ha > 0x5f300000 */
    printf("hypot(0x1p600, 0x1p599) = %a\n", hypot(0x1p600, 0x1p599)); /* R4 */
    /* line 113: False (normal case) */
    printf("hypot(3.0, 4.0) = %a\n", hypot(3.0, 4.0)); /* R4 */
    /* line 119: hb < 0x20b00000 (very small b) True */
    printf("hypot(1.0, 0x1p-600) = %a\n", hypot(1.0, 0x1p-600)); /* R4 */
    /* line 119: False */
    printf("hypot(1.0, 0.5) = %a\n", hypot(1.0, 0.5)); /* R4 */
    /* subnormal b (hb <= 0x000fffff) */
    printf("hypot(1.0, 0x1p-1074) = %a\n", hypot(1.0, 0x1p-1074)); /* R4 */
    /* line 135: hb <= 0x000fffff but b == 0 */
    printf("hypot(1.0, 0.0) = %a\n", hypot(1.0, 0.0)); /* R4 */
}

/* hypotf.c uncovered branches */
static void test_hypotf_extra3(void)
{
    printf("=== test_hypotf_extra3 ===\n"); /* R4 */
    /* line 43: ha > 0x58800000, not finite (Inf or NaN) */
    printf("hypotf(INFINITY, 1.0f) = %a\n", hypotf(INFINITY, 1.0f)); /* R4 */
    printf("hypotf(NAN, 1.0f) = %a\n", hypotf(NAN, 1.0f)); /* R4 */
    printf("hypotf(0x1p70f, 0x1p65f) = %a\n", hypotf(0x1p70f, 0x1p65f)); /* R4 */
    printf("hypotf(3.0f, 4.0f) = %a\n", hypotf(3.0f, 4.0f)); /* R4 */
    printf("hypotf(1.0f, 0.0f) = %a\n", hypotf(1.0f, 0.0f)); /* R4 */
}

/* ilogbd.c uncovered branches */
static void test_ilogb_extra3(void)
{
    printf("=== test_ilogb_extra3 ===\n"); /* R4 */
    /* line 99: subnormal, hx == 0 branch */
    printf("ilogb(0x1p-1074) = %d\n", ilogb(0x1p-1074)); /* R4 */
    /* line 207: subnormal, hx != 0 branch */
    printf("ilogb(0x1p-1023) = %d\n", ilogb(0x1p-1023)); /* R4 */
    /* line 311: hx > 0x7ff00000 (NaN) */
    printf("ilogb(NAN) = %d\n", ilogb(NAN)); /* R4 */
    /* line 420: hx == 0x7ff00000 (Inf) */
    printf("ilogb(INFINITY) = %d\n", ilogb(INFINITY)); /* R4 */
    printf("ilogb(-INFINITY) = %d\n", ilogb(-INFINITY)); /* R4 */
    /* normal */
    printf("ilogb(8.0) = %d\n", ilogb(8.0)); /* R4 */
    /* zero */
    printf("ilogb(0.0) = %d\n", ilogb(0.0)); /* R4 */
}

/* log10d.c uncovered branches */
static void test_log10_extra3(void)
{
    printf("=== test_log10_extra3 ===\n"); /* R4 */
    /* line 104:29 hx == 0x3ff00000 && lx == 0: log(1) = 0 (False) */
    printf("log10(2.0) = %a\n", log10(2.0)); /* R4 */
    printf("log10(1.0) = %a\n", log10(1.0)); /* R4 */
    printf("log10(0.5) = %a\n", log10(0.5)); /* R4 */
    /* subnormal */
    printf("log10(0x1p-1074) = %a\n", log10(0x1p-1074)); /* R4 */
    printf("log10(0.0) = %a\n", log10(0.0)); /* R4 */
    printf("log10(-1.0) = %a\n", log10(-1.0)); /* R4 */
    printf("log10(NAN) = %a\n", log10(NAN)); /* R4 */
    printf("log10(INFINITY) = %a\n", log10(INFINITY)); /* R4 */
}

/* log10f.c uncovered branches */
static void test_log10f_extra3(void)
{
    printf("=== test_log10f_extra3 ===\n"); /* R4 */
    /* line 39: hx < 0 (negative) */
    printf("log10f(-1.0f) = %a\n", log10f(-1.0f)); /* R4 */
    printf("log10f(2.0f) = %a\n", log10f(2.0f)); /* R4 */
    printf("log10f(1.0f) = %a\n", log10f(1.0f)); /* R4 */
    printf("log10f(0.5f) = %a\n", log10f(0.5f)); /* R4 */
    printf("log10f(0x1p-149f) = %a\n", log10f(0x1p-149f)); /* R4 */
    printf("log10f(0.0f) = %a\n", log10f(0.0f)); /* R4 */
    printf("log10f(NAN) = %a\n", log10f(NAN)); /* R4 */
    printf("log10f(INFINITY) = %a\n", log10f(INFINITY)); /* R4 */
}

/* log1pd.c uncovered branches */
static void test_log1p_extra3(void)
{
    printf("=== test_log1p_extra3 ===\n"); /* R4 */
    /* line 173: hx > 0 condition */
    printf("log1p(0.3) = %a\n", log1p(0.3)); /* R4 */
    printf("log1p(-0.2) = %a\n", log1p(-0.2)); /* R4 */
    /* line 181: k == 0 (False) */
    printf("log1p(1.0) = %a\n", log1p(1.0)); /* R4 */
    printf("log1p(-0.5) = %a\n", log1p(-0.5)); /* R4 */
    /* tiny x */
    printf("log1p(0x1p-55) = %a\n", log1p(0x1p-55)); /* R4 */
    printf("log1p(0x1p-31) = %a\n", log1p(0x1p-31)); /* R4 */
    /* special */
    printf("log1p(-1.0) = %a\n", log1p(-1.0)); /* R4 */
    printf("log1p(INFINITY) = %a\n", log1p(INFINITY)); /* R4 */
    printf("log1p(NAN) = %a\n", log1p(NAN)); /* R4 */
}

/* log1pf.c uncovered branches */
static void test_log1pf_extra3(void)
{
    printf("=== test_log1pf_extra3 ===\n"); /* R4 */
    /* line 56: hx > 0 */
    printf("log1pf(0.3f) = %a\n", log1pf(0.3f)); /* R4 */
    printf("log1pf(-0.2f) = %a\n", log1pf(-0.2f)); /* R4 */
    /* line 64: k != 0 (False) */
    printf("log1pf(0.0f) = %a\n", log1pf(0.0f)); /* R4 */
    /* line 94: hu == 0 */
    printf("log1pf(0x1p-22f) = %a\n", log1pf(0x1p-22f)); /* R4 */
    /* tiny x */
    printf("log1pf(0x1p-55f) = %a\n", log1pf(0x1p-55f)); /* R4 */
    printf("log1pf(0x1p-31f) = %a\n", log1pf(0x1p-31f)); /* R4 */
    printf("log1pf(-1.0f) = %a\n", log1pf(-1.0f)); /* R4 */
    printf("log1pf(INFINITY) = %a\n", log1pf(INFINITY)); /* R4 */
    printf("log1pf(1.0f) = %a\n", log1pf(1.0f)); /* R4 */
    printf("log1pf(-0.5f) = %a\n", log1pf(-0.5f)); /* R4 */
}

/* log2f.c uncovered branches */
static void test_log2f_extra3(void)
{
    printf("=== test_log2f_extra3 ===\n"); /* R4 */
    /* line 37: hx < 0 (negative) */
    printf("log2f(-1.0f) = %a\n", log2f(-1.0f)); /* R4 */
    printf("log2f(2.0f) = %a\n", log2f(2.0f)); /* R4 */
    printf("log2f(1.0f) = %a\n", log2f(1.0f)); /* R4 */
    printf("log2f(0x1p-149f) = %a\n", log2f(0x1p-149f)); /* R4 */
    printf("log2f(0.0f) = %a\n", log2f(0.0f)); /* R4 */
}

/* logf.c uncovered branches */
static void test_logf_extra3(void)
{
    printf("=== test_logf_extra3 ===\n"); /* R4 */
    /* line 65: hx < 0 (negative input) (False = already handled) */
    printf("logf(0.5f) = %a\n", logf(0.5f)); /* R4 */
    printf("logf(2.0f) = %a\n", logf(2.0f)); /* R4 */
    /* line 76: subnormal (True/False) */
    printf("logf(0x1p-149f) = %a\n", logf(0x1p-149f)); /* R4 */
    printf("logf(0x1p-126f) = %a\n", logf(0x1p-126f)); /* R4 */
    printf("logf(0.0f) = %a\n", logf(0.0f)); /* R4 */
    printf("logf(-1.0f) = %a\n", logf(-1.0f)); /* R4 */
    printf("logf(NAN) = %a\n", logf(NAN)); /* R4 */
    printf("logf(INFINITY) = %a\n", logf(INFINITY)); /* R4 */
}

/* expm1d.c uncovered branches */
static void test_expm1_extra3(void)
{
    printf("=== test_expm1_extra3 ===\n"); /* R4 */
    /* line 202: k == 1, x < -0.25 (True) */
    printf("expm1(0.8) = %a\n", expm1(0.8)); /* R4 */
    printf("expm1(-0.8) = %a\n", expm1(-0.8)); /* R4 */
    /* line 261: k == 1 True */
    printf("expm1(0.75) = %a\n", expm1(0.75)); /* R4 */
    /* line 278: k <= -2 or k > 56 (False) — k in range */
    printf("expm1(2.0) = %a\n", expm1(2.0)); /* R4 */
    printf("expm1(-2.0) = %a\n", expm1(-2.0)); /* R4 */
    /* k <= -2 */
    printf("expm1(-3.0) = %a\n", expm1(-3.0)); /* R4 */
    /* k > 56 */
    printf("expm1(60.0) = %a\n", expm1(60.0)); /* R4 */
    /* NaN */
    printf("expm1(NAN) = %a\n", expm1(NAN)); /* R4 */
    printf("expm1(INFINITY) = %a\n", expm1(INFINITY)); /* R4 */
    printf("expm1(-INFINITY) = %a\n", expm1(-INFINITY)); /* R4 */
}

/* expm1f.c uncovered branches */
static void test_expm1f_extra3(void)
{
    printf("=== test_expm1f_extra3 ===\n"); /* R4 */
    /* line 105: k == 1, x < -0.25f (True) */
    printf("expm1f(0.8f) = %a\n", expm1f(0.8f)); /* R4 */
    printf("expm1f(-0.8f) = %a\n", expm1f(-0.8f)); /* R4 */
    /* line 122: k != 0 (False) — k is 0 */
    printf("expm1f(0.3f) = %a\n", expm1f(0.3f)); /* R4 */
    printf("expm1f(2.0f) = %a\n", expm1f(2.0f)); /* R4 */
    printf("expm1f(-2.0f) = %a\n", expm1f(-2.0f)); /* R4 */
    printf("expm1f(-3.0f) = %a\n", expm1f(-3.0f)); /* R4 */
    printf("expm1f(NAN) = %a\n", expm1f(NAN)); /* R4 */
    printf("expm1f(INFINITY) = %a\n", expm1f(INFINITY)); /* R4 */
}

/* roundd.c uncovered branches */
static void test_round_extra3(void)
{
    printf("=== test_round_extra3 ===\n"); /* R4 */
    /* line 85:47 (msw & exponent_mask) == 0 && lsw == 0: integral (True) */
    printf("round(2.0) = %a\n", round(2.0)); /* R4 */
    /* False: not integral */
    printf("round(2.5) = %a\n", round(2.5)); /* R4 */
    printf("round(-2.5) = %a\n", round(-2.5)); /* R4 */
    printf("round(0.5) = %a\n", round(0.5)); /* R4 */
    printf("round(-0.5) = %a\n", round(-0.5)); /* R4 */
    /* exponent_less_1023 == -1: result is +/-1 */
    printf("round(0.7) = %a\n", round(0.7)); /* R4 */
    printf("round(-0.7) = %a\n", round(-0.7)); /* R4 */
    /* exponent > 51: NaN/Inf */
    printf("round(NAN) = %a\n", round(NAN)); /* R4 */
    printf("round(INFINITY) = %a\n", round(INFINITY)); /* R4 */
    printf("round(1e20) = %a\n", round(1e20)); /* R4 */
}

/* lrintf.c uncovered branches */
static void test_lrintf_extra3(void)
{
    printf("=== test_lrintf_extra3 ===\n"); /* R4 */
    /* line 66: exponent >= sizeof(long)*8-1, sign negative */
    printf("lrintf(-0.0f) = %ld\n", lrintf(-0.0f)); /* R4 */
    printf("lrintf(0.0f) = %ld\n", lrintf(0.0f)); /* R4 */
    printf("lrintf(1.5f) = %ld\n", lrintf(1.5f)); /* R4 */
    printf("lrintf(-1.5f) = %ld\n", lrintf(-1.5f)); /* R4 */
    /* overflow: exponent >= sizeof(long)*8-1 */
    printf("lrintf(1e30f) = %ld\n", lrintf(1e30f)); /* R4 */
    printf("lrintf(-1e30f) = %ld\n", lrintf(-1e30f)); /* R4 */
}

/* lroundf.c uncovered branches */
static void test_lroundf_extra3(void)
{
    printf("=== test_lroundf_extra3 ===\n"); /* R4 */
    /* line 31: exponent >= sizeof(long)*8-1 (True) */
    printf("lroundf(1e30f) = %ld\n", lroundf(1e30f)); /* R4 */
    printf("lroundf(-1e30f) = %ld\n", lroundf(-1e30f)); /* R4 */
    printf("lroundf(1.5f) = %ld\n", lroundf(1.5f)); /* R4 */
    printf("lroundf(-1.5f) = %ld\n", lroundf(-1.5f)); /* R4 */
    printf("lroundf(0.5f) = %ld\n", lroundf(0.5f)); /* R4 */
}

/* llrintf.c uncovered branches */
static void test_llrintf_extra3(void)
{
    printf("=== test_llrintf_extra3 ===\n"); /* R4 */
    /* line 67: exponent >= sizeof(long long)*8-1 (True) */
    printf("llrintf(1e30f) = %lld\n", llrintf(1e30f)); /* R4 */
    printf("llrintf(-1e30f) = %lld\n", llrintf(-1e30f)); /* R4 */
    printf("llrintf(1.5f) = %lld\n", llrintf(1.5f)); /* R4 */
    printf("llrintf(-1.5f) = %lld\n", llrintf(-1.5f)); /* R4 */
}

/* llroundf.c uncovered branches */
static void test_llroundf_extra3(void)
{
    printf("=== test_llroundf_extra3 ===\n"); /* R4 */
    /* line 32: exponent >= sizeof(long long)*8-1 (True) */
    printf("llroundf(1e30f) = %lld\n", llroundf(1e30f)); /* R4 */
    printf("llroundf(-1e30f) = %lld\n", llroundf(-1e30f)); /* R4 */
    printf("llroundf(1.5f) = %lld\n", llroundf(1.5f)); /* R4 */
    printf("llroundf(-1.5f) = %lld\n", llroundf(-1.5f)); /* R4 */
}

/* rintf.c uncovered branches */
static void test_rintf_extra3(void)
{
    printf("=== test_rintf_extra3 ===\n"); /* R4 */
    /* line 47: (_i0 & i) != 0 (round-half-to-even bit set) */
    printf("rintf(0.5f) = %a\n", rintf(0.5f)); /* R4 */
    printf("rintf(1.5f) = %a\n", rintf(1.5f)); /* R4 */
    printf("rintf(2.5f) = %a\n", rintf(2.5f)); /* R4 */
    printf("rintf(-0.5f) = %a\n", rintf(-0.5f)); /* R4 */
    printf("rintf(-1.5f) = %a\n", rintf(-1.5f)); /* R4 */
    printf("rintf(0.3f) = %a\n", rintf(0.3f)); /* R4 */
    printf("rintf(1.3f) = %a\n", rintf(1.3f)); /* R4 */
}

/* jnd.c uncovered branches */
static void test_jn_extra3(void)
{
    printf("=== test_jn_extra3 ===\n"); /* R4 */
    /* line 122: n == 0 */
    printf("jn(0, 1.0) = %a\n", jn(0, 1.0)); /* R4 */
    /* line 126: n == 1 */
    printf("jn(1, 1.0) = %a\n", jn(1, 1.0)); /* R4 */
    /* line 141: n <= x (True/False) */
    printf("jn(3, 5.0) = %a\n", jn(3, 5.0)); /* R4 */
    printf("jn(5, 1.0) = %a\n", jn(5, 1.0)); /* R4 */
    /* line 142: ix >= 0x52D00000 (x > 2^302) True */
    printf("jn(2, 1e100) = %a\n", jn(2, 1e100)); /* R4 */
    /* line 142: False (normal path) */
    printf("jn(4, 10.0) = %a\n", jn(4, 10.0)); /* R4 */
    /* switch n&3 cases */
    printf("jn(4, 1e100) = %a\n", jn(4, 1e100)); /* R4 */
    printf("jn(5, 1e100) = %a\n", jn(5, 1e100)); /* R4 */
    printf("jn(6, 1e100) = %a\n", jn(6, 1e100)); /* R4 */
    printf("jn(7, 1e100) = %a\n", jn(7, 1e100)); /* R4 */
    /* line 146-154: x < 2^-29 cases */
    printf("jn(2, 1e-10) = %a\n", jn(2, 1e-10)); /* R4 */
    printf("jn(35, 1e-10) = %a\n", jn(35, 1e-10)); /* n > 33: underflow */ /* R4 */
    /* line 175: backward recurrence for larger x */
    printf("jn(10, 3.0) = %a\n", jn(10, 3.0)); /* R4 */
    /* negative x */
    printf("jn(2, -5.0) = %a\n", jn(2, -5.0)); /* R4 */
    printf("jn(3, -5.0) = %a\n", jn(3, -5.0)); /* R4 */
    /* line 256: ix == 0 */
    printf("jn(3, 0.0) = %a\n", jn(3, 0.0)); /* R4 */
    /* ix >= 0x7ff00000 */
    printf("jn(3, INFINITY) = %a\n", jn(3, INFINITY)); /* R4 */
    printf("jn(3, NAN) = %a\n", jn(3, NAN)); /* R4 */
}

/* ynd.c uncovered branches */
static void test_yn_extra3(void)
{
    printf("=== test_yn_extra3 ===\n"); /* R4 */
    /* line 122: n == 0 */
    printf("yn(0, 1.0) = %a\n", yn(0, 1.0)); /* R4 */
    /* line 141: n == 1 (positive) */
    printf("yn(1, 1.0) = %a\n", yn(1, 1.0)); /* R4 */
    /* line 142: n == 1 (negative n) */
    printf("yn(-1, 1.0) = %a\n", yn(-1, 1.0)); /* R4 */
    /* line 142: other negative n */
    printf("yn(-2, 1.0) = %a\n", yn(-2, 1.0)); /* R4 */
    /* line 146: ix == 0x7ff00000 (+Inf) */
    printf("yn(2, INFINITY) = %a\n", yn(2, INFINITY)); /* R4 */
    /* line 150: ix >= 0x52D00000 (very large x) */
    printf("yn(2, 1e100) = %a\n", yn(2, 1e100)); /* R4 */
    /* switch n&3 */
    printf("yn(4, 1e100) = %a\n", yn(4, 1e100)); /* R4 */
    printf("yn(5, 1e100) = %a\n", yn(5, 1e100)); /* R4 */
    printf("yn(6, 1e100) = %a\n", yn(6, 1e100)); /* R4 */
    printf("yn(7, 1e100) = %a\n", yn(7, 1e100)); /* R4 */
    /* normal recurrence */
    printf("yn(3, 5.0) = %a\n", yn(3, 5.0)); /* R4 */
    /* line 154: False path (normal recurrence, not large x) */
    printf("yn(5, 3.0) = %a\n", yn(5, 3.0)); /* R4 */
    /* line 167: sign > 0 (False: sign <= 0) */
    printf("yn(-3, 1.0) = %a\n", yn(-3, 1.0)); /* R4 */
}

/* y1d.c uncovered branches */
static void test_y1_extra3(void)
{
    printf("=== test_y1_extra3 ===\n"); /* R4 */
    /* line 118: ix < 0x7fe00000 True path */
    printf("y1(2.0) = %a\n", y1(2.0)); /* R4 */
    printf("y1(10.0) = %a\n", y1(10.0)); /* R4 */
    /* line 150: ix <= 0x3c900000 (x < 2^-54) */
    printf("y1(0x1p-60) = %a\n", y1(0x1p-60)); /* R4 */
    /* various other */
    printf("y1(1.0) = %a\n", y1(1.0)); /* R4 */
    printf("y1(0.1) = %a\n", y1(0.1)); /* R4 */
    printf("y1(INFINITY) = %a\n", y1(INFINITY)); /* R4 */
    printf("y1(NAN) = %a\n", y1(NAN)); /* R4 */
    printf("y1(0.0) = %a\n", y1(0.0)); /* R4 */
    printf("y1(-1.0) = %a\n", y1(-1.0)); /* R4 */
}

/* powd.c uncovered branches */
static void test_pow_extra3(void)
{
    printf("=== test_pow_extra3 ===\n"); /* R4 */
    /* line 147:51 x==1 with sNaN y */
    printf("pow(1.0, __builtin_nans(\"\")) = %a\n", pow(1.0, __builtin_nans(""))); /* R4 */
    /* line 179: hx < 0, yisint from iy >= 0x43400000 */
    printf("pow(-2.0, 1e16) = %a\n", pow(-2.0, 1e16)); /* R4 */
    /* line 182: k > 20, j not integer */
    printf("pow(-2.0, 1.5) = %a\n", pow(-2.0, 1.5)); /* R4 */
    /* line 182: k > 20, integer */
    printf("pow(-2.0, 3.0) = %a\n", pow(-2.0, 3.0)); /* R4 */
    /* line 185: ly == 0 but iy >= 0x3ff00000, k <= 20 */
    printf("pow(-2.0, 2.0) = %a\n", pow(-2.0, 2.0)); /* R4 */
    /* line 240: iy == 0x7ff00000 (y is Inf) */
    printf("pow(0.5, -INFINITY) = %a\n", pow(0.5, -INFINITY)); /* R4 */
    printf("pow(2.0, -INFINITY) = %a\n", pow(2.0, -INFINITY)); /* R4 */
    /* line 277: iy > 0x42000000, iy > 0x43f00000, ix < 1 */
    printf("pow(0.5, 1e20) = %a\n", pow(0.5, 1e20)); /* R4 */
    printf("pow(2.0, 1e20) = %a\n", pow(2.0, 1e20)); /* R4 */
    /* line 279: ix < 0x3fefffff */
    printf("pow(0.5, 1e10) = %a\n", pow(0.5, 1e10)); /* R4 */
    /* line 285: ix > 0x3ff00000 */
    printf("pow(2.0, 1e10) = %a\n", pow(2.0, 1e10)); /* R4 */
    /* line 289: hy < 0 */
    printf("pow(0.5, -1e10) = %a\n", pow(0.5, -1e10)); /* R4 */
    /* line 306: ix < 0x00100000 subnormal x */
    printf("pow(0x1p-1074, 0.5) = %a\n", pow(0x1p-1074, 0.5)); /* R4 */
    /* line 317: j <= 0x3988E */
    printf("pow(1.1, 2.0) = %a\n", pow(1.1, 2.0)); /* R4 */
    /* line 319: j in (0x3988E, 0xBB67A): k=1 */
    printf("pow(1.3, 2.0) = %a\n", pow(1.3, 2.0)); /* R4 */
    /* line 376: z >= 1024 */
    printf("pow(2.0, 1023.0) = %a\n", pow(2.0, 1023.0)); /* R4 */
    /* line 381: z <= -1075 */
    printf("pow(2.0, -1075.0) = %a\n", pow(2.0, -1075.0)); /* R4 */
    /* line 384: p_l <= z-p_h underflow exact border */
    printf("pow(0.5, 1074.0) = %a\n", pow(0.5, 1074.0)); /* R4 */
}

/* powf.c uncovered branches */
static void test_powf_extra3(void)
{
    printf("=== test_powf_extra3 ===\n"); /* R4 */
    /* line 87: hx < 0, yisint from iy >= 0x4b800000 */
    printf("powf(-2.0f, 1e8f) = %a\n", powf(-2.0f, 1e8f)); /* R4 */
    /* line 103: y == Inf */
    printf("powf(1.0f, INFINITY) = %a\n", powf(1.0f, INFINITY)); /* R4 */
    /* line 108: ix > 0x3f800000, hy >= 0 */
    printf("powf(2.0f, INFINITY) = %a\n", powf(2.0f, INFINITY)); /* R4 */
    /* powf(x<1, -inf) = inf */
    printf("powf(0.5f, -INFINITY) = %a\n", powf(0.5f, -INFINITY)); /* R4 */
    /* line 133: special x (Inf/0/1), hy < 0 */
    printf("powf(INFINITY, -1.0f) = %a\n", powf(INFINITY, -1.0f)); /* R4 */
    printf("powf(0.0f, -1.0f) = %a\n", powf(0.0f, -1.0f)); /* R4 */
    /* line 146: hx < 0, x==-1, yisint==0 */
    printf("powf(-1.0f, 1.5f) = %a\n", powf(-1.0f, 1.5f)); /* R4 */
    /* line 147: yisint == 1 (odd exponent) */
    printf("powf(-2.0f, 3.0f) = %a\n", powf(-2.0f, 3.0f)); /* R4 */
    /* line 149: (x<0)^(non-int) NaN */
    printf("powf(-2.0f, 1.5f) = %a\n", powf(-2.0f, 1.5f)); /* R4 */
    /* line 165-173: |y| > 2^27 */
    printf("powf(0.5f, 1e10f) = %a\n", powf(0.5f, 1e10f)); /* R4 */
    printf("powf(2.0f, 1e10f) = %a\n", powf(2.0f, 1e10f)); /* R4 */
    printf("powf(0.5f, -1e10f) = %a\n", powf(0.5f, -1e10f)); /* R4 */
    /* line 172: ix > 0x3f800007 */
    printf("powf(2.0f, -1e10f) = %a\n", powf(2.0f, -1e10f)); /* R4 */
    /* line 204: j <= 0x1cc471 */
    printf("powf(1.1f, 2.0f) = %a\n", powf(1.1f, 2.0f)); /* R4 */
    /* line 271: j > 0, overflow check */
    printf("powf(2.0f, 127.0f) = %a\n", powf(2.0f, 127.0f)); /* R4 */
    /* line 272: i == FLT_UWORD_EXP_MAX exact border */
    printf("powf(2.0f, 128.0f) = %a\n", powf(2.0f, 128.0f)); /* R4 */
    /* line 281: i == FLT_UWORD_EXP_MIN exact border */
    printf("powf(0.5f, 127.0f) = %a\n", powf(0.5f, 127.0f)); /* R4 */
    printf("powf(0.5f, 128.0f) = %a\n", powf(0.5f, 128.0f)); /* R4 */
    /* subnormal x */
    printf("powf(0x1p-149f, 0.5f) = %a\n", powf(0x1p-149f, 0.5f)); /* R4 */
}

/* ctanf.c uncovered branches */
static void test_ctanf_extra3(void)
{
    printf("=== test_ctanf_extra3 ===\n"); /* R4 */
    /* line 66: d == 0.0f */
    /* Make d = cos(2*re) + cosh(2*im) close to zero:
     * cos(2*re) = -1 when re = pi/2, cosh(2*im) = 1 when im = 0
     * so d = 0 exactly isn't easy, use edge case: large imaginary */
    float complex z_ctanf = CMPLXF(1.5707963f, 50.0f);
    float complex r_ctanf = ctanf(z_ctanf);
    printf("ctanf(1.5707963+50i) = %a+%ai\n", crealf(r_ctanf), cimagf(r_ctanf)); /* R4 */
    /* normal */
    z_ctanf = CMPLXF(0.5f, 0.5f);
    r_ctanf = ctanf(z_ctanf);
    printf("ctanf(0.5+0.5i) = %a+%ai\n", crealf(r_ctanf), cimagf(r_ctanf)); /* R4 */
    /* large imaginary (d near 0) */
    z_ctanf = CMPLXF(0.0f, 100.0f);
    r_ctanf = ctanf(z_ctanf);
    printf("ctanf(0+100i) = %a+%ai\n", crealf(r_ctanf), cimagf(r_ctanf)); /* R4 */
    /* fabsf(d) < 0.25 path: __ctansf */
    z_ctanf = CMPLXF(1.5707963f, 0.1f);
    r_ctanf = ctanf(z_ctanf);
    printf("ctanf(pi/2+0.1i) = %a+%ai\n", crealf(r_ctanf), cimagf(r_ctanf)); /* R4 */
}

/* ctrigf.c uncovered branches */
static void test_ctrigf_extra3(void)
{
    printf("=== test_ctrigf_extra3 ===\n"); /* R4 */
    /* line 19: fabsf(x) <= 0.5f True */
    float c, s;
    __ccoshsinhf(0.3f, &c, &s);
    printf("__ccoshsinhf(0.3) c=%a s=%a\n", c, s); /* R4 */
    /* line 19: False */
    __ccoshsinhf(1.0f, &c, &s);
    printf("__ccoshsinhf(1.0) c=%a s=%a\n", c, s); /* R4 */
    /* exp(x) == 0: extremely negative x */
    __ccoshsinhf(-200.0f, &c, &s);
    printf("__ccoshsinhf(-200) c=%a s=%a\n", c, s); /* R4 */
    /* __redupif: t >= 0 (True) */
    printf("__redupif(3.14f) = %a\n", __redupif(3.14f)); /* R4 */
    /* __redupif: t < 0 (False) */
    printf("__redupif(-3.14f) = %a\n", __redupif(-3.14f)); /* R4 */
    /* line 79: __rem_pio2f branches via sinf/cosf/tanf with large args */
    printf("sinf(1e8f) = %a\n", sinf(1e8f)); /* R4 */
    /* line 124, 125: internal ctrig paths via csinf/ccosf */
    float complex zc = CMPLXF(10.0f, 1.0f);
    float complex rc = csinf(zc);
    printf("csinf(10+1i) = %a+%ai\n", crealf(rc), cimagf(rc)); /* R4 */
    rc = ccosf(zc);
    printf("ccosf(10+1i) = %a+%ai\n", crealf(rc), cimagf(rc)); /* R4 */
    /* line 322: large real/imag */
    zc = CMPLXF(1e20f, 1e20f);
    rc = csinf(zc);
    printf("csinf(1e20+1e20i) = %a+%ai\n", crealf(rc), cimagf(rc)); /* R4 */
}

/* ctrigd.c uncovered branches */
static void test_ctrigd_extra3(void)
{
    printf("=== test_ctrigd_extra3 ===\n"); /* R4 */
    /* line 21: fabs(x) <= 0.5 True */
    double c, s;
    __ccoshsinh(0.3, &c, &s);
    printf("__ccoshsinh(0.3) c=%a s=%a\n", c, s); /* R4 */
    /* line 21: False */
    __ccoshsinh(1.0, &c, &s);
    printf("__ccoshsinh(1.0) c=%a s=%a\n", c, s); /* R4 */
    /* exp(x) == 0 for large negative x */
    __ccoshsinh(-800.0, &c, &s);
    printf("__ccoshsinh(-800) c=%a s=%a\n", c, s); /* R4 */
    /* complex trig via public functions */
    double complex zd = CMPLX(10.0, 1.0);
    double complex rd = csin(zd);
    printf("csin(10+1i) = %a+%ai\n", creal(rd), cimag(rd)); /* R4 */
    rd = ccos(zd);
    printf("ccos(10+1i) = %a+%ai\n", creal(rd), cimag(rd)); /* R4 */
}

/* erfd.c uncovered branches */
static void test_erf_extra3(void)
{
    printf("=== test_erf_extra3 ===\n"); /* R4 */
    /* line 205: ix < 0x3ff00000 False path (|x| >= 1.0) */
    printf("erf(1.0) = %a\n", erf(1.0)); /* R4 */
    printf("erf(2.0) = %a\n", erf(2.0)); /* R4 */
    printf("erf(-1.0) = %a\n", erf(-1.0)); /* R4 */
    printf("erf(0.0) = %a\n", erf(0.0)); /* R4 */
    printf("erf(0.5) = %a\n", erf(0.5)); /* R4 */
    printf("erf(NAN) = %a\n", erf(NAN)); /* R4 */
    printf("erf(INFINITY) = %a\n", erf(INFINITY)); /* R4 */
    printf("erf(-INFINITY) = %a\n", erf(-INFINITY)); /* R4 */
}

/* erfcd.c uncovered branches */
static void test_erfc_extra3(void)
{
    printf("=== test_erfc_extra3 ===\n"); /* R4 */
    /* line 237: ix < 0x3ff40000 False — |x| >= some threshold */
    printf("erfc(1.5) = %a\n", erfc(1.5)); /* R4 */
    printf("erfc(2.0) = %a\n", erfc(2.0)); /* R4 */
    printf("erfc(5.0) = %a\n", erfc(5.0)); /* R4 */
    printf("erfc(-2.0) = %a\n", erfc(-2.0)); /* R4 */
    printf("erfc(0.0) = %a\n", erfc(0.0)); /* R4 */
    printf("erfc(NAN) = %a\n", erfc(NAN)); /* R4 */
    printf("erfc(INFINITY) = %a\n", erfc(INFINITY)); /* R4 */
}

/* erfcf.c uncovered branches */
static void test_erfcf_extra3(void)
{
    printf("=== test_erfcf_extra3 ===\n"); /* R4 */
    /* line 73: ix >= 0x3f580000 and <= condition (True) */
    printf("erfcf(0.75f) = %a\n", erfcf(0.75f)); /* R4 */
    printf("erfcf(1.0f) = %a\n", erfcf(1.0f)); /* R4 */
    /* line 91: False — |x| >= threshold */
    printf("erfcf(2.0f) = %a\n", erfcf(2.0f)); /* R4 */
    printf("erfcf(5.0f) = %a\n", erfcf(5.0f)); /* R4 */
    printf("erfcf(-2.0f) = %a\n", erfcf(-2.0f)); /* R4 */
    printf("erfcf(0.0f) = %a\n", erfcf(0.0f)); /* R4 */
    printf("erfcf(NAN) = %a\n", erfcf(NAN)); /* R4 */
    printf("erfcf(INFINITY) = %a\n", erfcf(INFINITY)); /* R4 */
}

/* ================================================================== */
/* S5 round-6 targeted branch coverage tests                          */
/* ================================================================== */

/* atan2d/atan2f — y==0 switch cases 0 and 1 (m=0,1 with x > 0, x != 1) */
static void test_atan2_s5(void)
{
    printf("=== test_atan2_s5 ===\n"); /* R5 */
    /* y=+0, x=+2 (x not 1.0): y==0 switch m=0 → return +0 */
    printf("atan2(+0,2) = %a\n", atan2(0.0, 2.0)); /* R5 */
    /* y=-0, x=+2: y==0 switch m=1 → return -0 */
    printf("atan2(-0,2) = %a\n", atan2(-0.0, 2.0)); /* R5 */
    /* y=+0, x=+0.5: m=0 */
    printf("atan2(+0,0.5) = %a\n", atan2(0.0, 0.5)); /* R5 */
    /* y=-0, x=+0.5: m=1 */
    printf("atan2(-0,0.5) = %a\n", atan2(-0.0, 0.5)); /* R5 */
    /* float versions */
    printf("atan2f(+0,2) = %a\n", atan2f(0.0f, 2.0f)); /* R5 */
    printf("atan2f(-0,2) = %a\n", atan2f(-0.0f, 2.0f)); /* R5 */
    printf("atan2f(+0,0.5) = %a\n", atan2f(0.0f, 0.5f)); /* R5 */
    printf("atan2f(-0,0.5) = %a\n", atan2f(-0.0f, 0.5f)); /* R5 */
    /* x=+Inf with finite positive y: m=0 switch default+case0 */
    printf("atan2(2,+inf) = %a\n", atan2(2.0, D_INF)); /* R5 */
    /* x=+Inf with finite negative y: m=1 */
    printf("atan2(-2,+inf) = %a\n", atan2(-2.0, D_INF)); /* R5 */
    /* float */
    printf("atan2f(2,+inf) = %a\n", atan2f(2.0f, F_INF)); /* R5 */
    printf("atan2f(-2,+inf) = %a\n", atan2f(-2.0f, F_INF)); /* R5 */
    /* x=-Inf, y finite positive: m=2 → pi */
    printf("atan2(2,-inf) = %a\n", atan2(2.0, D_NINF)); /* R5 */
    /* x=-Inf, y finite negative: m=3 → -pi */
    printf("atan2(-2,-inf) = %a\n", atan2(-2.0, D_NINF)); /* R5 */
    /* both Inf: all 4 cases */
    printf("atan2(+inf,+inf) = %a\n", atan2(D_INF, D_INF)); /* R5 */
    printf("atan2(-inf,+inf) = %a\n", atan2(D_NINF, D_INF)); /* R5 */
    printf("atan2(+inf,-inf) = %a\n", atan2(D_INF, D_NINF)); /* R5 */
    printf("atan2(-inf,-inf) = %a\n", atan2(D_NINF, D_NINF)); /* R5 */
}

/* ceild/ceilf — comprehensive bit-pattern branches */
static void test_ceil_s5(void)
{
    printf("=== test_ceil_s5 ===\n"); /* R5 */
    /* j0 < 0: ±0 (True) */
    printf("ceil(+0) = %a\n", ceil(0.0)); /* R5 */
    printf("ceil(-0) = %a\n", ceil(-0.0)); /* R5 */
    /* j0 < 0: positive nonzero (False, _i0>=0) */
    printf("ceil(0.1) = %a\n", ceil(0.1)); /* R5 */
    printf("ceil(0.5) = %a\n", ceil(0.5)); /* R5 */
    printf("ceil(0.9) = %a\n", ceil(0.9)); /* R5 */
    /* j0 < 0: negative nonzero (_i0<0) */
    printf("ceil(-0.1) = %a\n", ceil(-0.1)); /* R5 */
    printf("ceil(-0.5) = %a\n", ceil(-0.5)); /* R5 */
    printf("ceil(-0.9) = %a\n", ceil(-0.9)); /* R5 */
    /* j0 in [0,20): integral (_i0>0) */
    printf("ceil(4.0) = %a\n", ceil(4.0)); /* R5 */
    printf("ceil(8.0) = %a\n", ceil(8.0)); /* R5 */
    /* j0 in [0,20): not integral, positive */
    printf("ceil(1.1) = %a\n", ceil(1.1)); /* R5 */
    printf("ceil(3.7) = %a\n", ceil(3.7)); /* R5 */
    /* j0 in [0,20): not integral, negative */
    printf("ceil(-1.1) = %a\n", ceil(-1.1)); /* R5 */
    printf("ceil(-3.7) = %a\n", ceil(-3.7)); /* R5 */
    /* j0 > 51: not 0x400, large integer */
    printf("ceil(1e18) = %a\n", ceil(1e18)); /* R5 */
    printf("ceil(-1e18) = %a\n", ceil(-1e18)); /* R5 */
    /* j0 == 0x400: Inf/NaN */
    printf("ceil(inf) = %a\n", ceil(D_INF)); /* R5 */
    printf("ceil(-inf) = %a\n", ceil(D_NINF)); /* R5 */
    printf("ceil(nan) = %a\n", ceil(D_NAN)); /* R5 */
    /* j0 in [20,52): integral */
    printf("ceil(0x1p25) = %a\n", ceil(0x1p25)); /* R5 */
    printf("ceil(0x1p40) = %a\n", ceil(0x1p40)); /* R5 */
    /* j0 in [20,52): not integral, j0==20, positive */
    printf("ceil(0x1.8p20) = %a\n", ceil(0x1.8p20)); /* R4 */
    /* j0 in [20,52): not integral, j0>20, positive, no carry */
    printf("ceil(0x1.0000000001p30) = %a\n", ceil(0x1.0000000001p30)); /* R5 */
    /* j0 in [20,52): not integral, negative */
    printf("ceil(-0x1.8p20) = %a\n", ceil(-0x1.8p20)); /* R4 */
    printf("ceil(-0x1.0000000001p30) = %a\n", ceil(-0x1.0000000001p30)); /* R5 */
    /* carry case: j1 overflows low word into high */
    printf("ceil(0x1.ffffffffffff0p30) = %a\n", ceil(0x1.ffffffffffff0p30)); /* R5 */
}

static void test_ceilf_s5(void)
{
    printf("=== test_ceilf_s5 ===\n"); /* R5 */
    printf("ceilf(+0) = %a\n", ceilf(0.0f)); /* R5 */
    printf("ceilf(-0) = %a\n", ceilf(-0.0f)); /* R5 */
    printf("ceilf(0.1f) = %a\n", ceilf(0.1f)); /* R5 */
    printf("ceilf(0.5f) = %a\n", ceilf(0.5f)); /* R5 */
    printf("ceilf(-0.1f) = %a\n", ceilf(-0.1f)); /* R5 */
    printf("ceilf(-0.5f) = %a\n", ceilf(-0.5f)); /* R5 */
    printf("ceilf(4.0f) = %a\n", ceilf(4.0f)); /* R5 */
    printf("ceilf(1.5f) = %a\n", ceilf(1.5f)); /* R4 */
    printf("ceilf(-1.5f) = %a\n", ceilf(-1.5f)); /* R4 */
    printf("ceilf(1e10f) = %a\n", ceilf(1e10f)); /* R4 */
    printf("ceilf(inf) = %a\n", ceilf(F_INF)); /* R5 */
    printf("ceilf(nan) = %a\n", ceilf(F_NAN)); /* R5 */
    printf("ceilf(0x1p22f+0.5f) = %a\n", ceilf(0x1p22f + 0.5f)); /* R5 */
    printf("ceilf(-0x1p22f-0.5f) = %a\n", ceilf(-(0x1p22f + 0.5f))); /* R5 */
}

/* floord/floorf — bit-pattern branches */
static void test_floor_s5(void)
{
    printf("=== test_floor_s5 ===\n"); /* R5 */
    printf("floor(+0) = %a\n", floor(0.0)); /* R5 */
    printf("floor(-0) = %a\n", floor(-0.0)); /* R5 */
    printf("floor(0.5) = %a\n", floor(0.5)); /* R5 */
    printf("floor(-0.5) = %a\n", floor(-0.5)); /* R5 */
    printf("floor(0.1) = %a\n", floor(0.1)); /* R5 */
    printf("floor(-0.1) = %a\n", floor(-0.1)); /* R5 */
    printf("floor(1.5) = %a\n", floor(1.5)); /* R5 */
    printf("floor(-1.5) = %a\n", floor(-1.5)); /* R4 */
    printf("floor(4.0) = %a\n", floor(4.0)); /* R5 */
    printf("floor(1e18) = %a\n", floor(1e18)); /* R5 */
    printf("floor(-1e18) = %a\n", floor(-1e18)); /* R5 */
    printf("floor(inf) = %a\n", floor(D_INF)); /* R5 */
    printf("floor(nan) = %a\n", floor(D_NAN)); /* R5 */
    /* j0 in [20,52): not integral, negative, j0==20 */
    printf("floor(-0x1.8p20) = %a\n", floor(-0x1.8p20)); /* R4 */
    /* j0 in [20,52): not integral, negative, j0>20 with carry */
    printf("floor(-0x1.ffffffffffff0p30) = %a\n", floor(-0x1.ffffffffffff0p30)); /* R5 */
    /* j0 in [20,52): not integral, positive */
    printf("floor(0x1.8p20) = %a\n", floor(0x1.8p20)); /* R5 */
    /* j0 in [20,52): integral */
    printf("floor(0x1p30) = %a\n", floor(0x1p30)); /* R5 */
}

static void test_floorf_s5(void)
{
    printf("=== test_floorf_s5 ===\n"); /* R5 */
    printf("floorf(+0) = %a\n", floorf(0.0f)); /* R5 */
    printf("floorf(-0) = %a\n", floorf(-0.0f)); /* R5 */
    printf("floorf(0.5f) = %a\n", floorf(0.5f)); /* R5 */
    printf("floorf(-0.5f) = %a\n", floorf(-0.5f)); /* R5 */
    printf("floorf(1.5f) = %a\n", floorf(1.5f)); /* R5 */
    printf("floorf(-1.5f) = %a\n", floorf(-1.5f)); /* R4 */
    printf("floorf(4.0f) = %a\n", floorf(4.0f)); /* R5 */
    printf("floorf(1e10f) = %a\n", floorf(1e10f)); /* R4 */
    printf("floorf(inf) = %a\n", floorf(F_INF)); /* R5 */
    printf("floorf(nan) = %a\n", floorf(F_NAN)); /* R5 */
    printf("floorf(-0x1.8p22f) = %a\n", floorf(-0x1.8p22f)); /* R5 */
}

/* truncd/truncf */
static void test_trunc_s5(void)
{
    printf("=== test_trunc_s5 ===\n"); /* R5 */
    printf("trunc(+0) = %a\n", trunc(0.0)); /* R5 */
    printf("trunc(-0) = %a\n", trunc(-0.0)); /* R5 */
    printf("trunc(0.9) = %a\n", trunc(0.9)); /* R5 */
    printf("trunc(-0.9) = %a\n", trunc(-0.9)); /* R5 */
    printf("trunc(1.7) = %a\n", trunc(1.7)); /* R4 */
    printf("trunc(-1.7) = %a\n", trunc(-1.7)); /* R4 */
    printf("trunc(1e18) = %a\n", trunc(1e18)); /* R5 */
    printf("trunc(inf) = %a\n", trunc(D_INF)); /* R5 */
    printf("trunc(nan) = %a\n", trunc(D_NAN)); /* R5 */
    printf("trunc(0x1.8p20) = %a\n", trunc(0x1.8p20)); /* R4 */
    printf("trunc(-0x1.8p20) = %a\n", trunc(-0x1.8p20)); /* R4 */
    printf("trunc(0x1.0001p35) = %a\n", trunc(0x1.0001p35)); /* R5 */
    printf("trunc(-0x1.0001p35) = %a\n", trunc(-0x1.0001p35)); /* R5 */
}

static void test_truncf_s5(void)
{
    printf("=== test_truncf_s5 ===\n"); /* R5 */
    printf("truncf(+0) = %a\n", truncf(0.0f)); /* R5 */
    printf("truncf(-0) = %a\n", truncf(-0.0f)); /* R5 */
    printf("truncf(0.9f) = %a\n", truncf(0.9f)); /* R5 */
    printf("truncf(-0.9f) = %a\n", truncf(-0.9f)); /* R5 */
    printf("truncf(1.7f) = %a\n", truncf(1.7f)); /* R4 */
    printf("truncf(-1.7f) = %a\n", truncf(-1.7f)); /* R4 */
    printf("truncf(1e10f) = %a\n", truncf(1e10f)); /* R4 */
    printf("truncf(inf) = %a\n", truncf(F_INF)); /* R5 */
    printf("truncf(nan) = %a\n", truncf(F_NAN)); /* R5 */
    printf("truncf(0x1.8p22f) = %a\n", truncf(0x1.8p22f)); /* R5 */
    printf("truncf(-0x1.8p22f) = %a\n", truncf(-0x1.8p22f)); /* R5 */
}

/* fmaxd/fmaxf/fmind/fminf — NaN and sNaN branches */
static void test_fmaxmin_s5(void)
{
    printf("=== test_fmaxmin_s5 ===\n"); /* R5 */
    /* fmaxd: x=qNaN */
    printf("fmax(nan,2) = %a\n", fmax(D_NAN, 2.0)); /* R5 */
    /* fmaxd: x=sNaN → x*y */
    printf("fmax(snan,2) = %a\n", fmax(__builtin_nans(""), 2.0)); /* R5 */
    /* fmaxd: x=qNaN, y=sNaN */
    printf("fmax(nan,snan) = %a\n", fmax(D_NAN, __builtin_nans(""))); /* R5 */
    /* fmaxd: y=qNaN */
    printf("fmax(2,nan) = %a\n", fmax(2.0, D_NAN)); /* R5 */
    /* fmaxd: y=sNaN */
    printf("fmax(2,snan) = %a\n", fmax(2.0, __builtin_nans(""))); /* R5 */
    /* fmaxd: x>y, x<y */
    printf("fmax(3,2) = %a\n", fmax(3.0, 2.0)); /* R5 */
    printf("fmax(1,2) = %a\n", fmax(1.0, 2.0)); /* R5 */
    printf("fmax(-1,-2) = %a\n", fmax(-1.0, -2.0)); /* R5 */
    /* fmaxf: same */
    printf("fmaxf(nan,2) = %a\n", fmaxf(F_NAN, 2.0f)); /* R5 */
    printf("fmaxf(snan,2) = %a\n", fmaxf(__builtin_nansf(""), 2.0f)); /* R5 */
    printf("fmaxf(2,nan) = %a\n", fmaxf(2.0f, F_NAN)); /* R5 */
    printf("fmaxf(2,snan) = %a\n", fmaxf(2.0f, __builtin_nansf(""))); /* R5 */
    printf("fmaxf(3,2) = %a\n", fmaxf(3.0f, 2.0f)); /* R5 */
    printf("fmaxf(1,2) = %a\n", fmaxf(1.0f, 2.0f)); /* R5 */
    /* fmind */
    printf("fmin(nan,2) = %a\n", fmin(D_NAN, 2.0)); /* R5 */
    printf("fmin(snan,2) = %a\n", fmin(__builtin_nans(""), 2.0)); /* R5 */
    printf("fmin(2,nan) = %a\n", fmin(2.0, D_NAN)); /* R5 */
    printf("fmin(2,snan) = %a\n", fmin(2.0, __builtin_nans(""))); /* R5 */
    printf("fmin(3,2) = %a\n", fmin(3.0, 2.0)); /* R5 */
    printf("fmin(1,2) = %a\n", fmin(1.0, 2.0)); /* R5 */
    /* fminf */
    printf("fminf(nan,2) = %a\n", fminf(F_NAN, 2.0f)); /* R5 */
    printf("fminf(snan,2) = %a\n", fminf(__builtin_nansf(""), 2.0f)); /* R5 */
    printf("fminf(2,nan) = %a\n", fminf(2.0f, F_NAN)); /* R5 */
    printf("fminf(2,snan) = %a\n", fminf(2.0f, __builtin_nansf(""))); /* R5 */
    printf("fminf(3,2) = %a\n", fminf(3.0f, 2.0f)); /* R5 */
    printf("fminf(1,2) = %a\n", fminf(1.0f, 2.0f)); /* R5 */
}

/* fmodd/fmodf — subnormal, |x|<|y|, |x|==|y| */
static void test_fmod_s5(void)
{
    printf("=== test_fmod_s5 ===\n"); /* R5 */
    /* x=Inf → invalid */
    printf("fmod(inf,3) = %a\n", fmod(D_INF, 3.0)); /* R5 */
    printf("fmod(-inf,3) = %a\n", fmod(D_NINF, 3.0)); /* R5 */
    /* y=0 → invalid */
    printf("fmod(5,0) = %a\n", fmod(5.0, 0.0)); /* R5 */
    /* NaN */
    printf("fmod(nan,3) = %a\n", fmod(D_NAN, 3.0)); /* R5 */
    printf("fmod(5,nan) = %a\n", fmod(5.0, D_NAN)); /* R5 */
    /* |x| < |y| → return x */
    printf("fmod(1,3) = %a\n", fmod(1.0, 3.0)); /* R5 */
    printf("fmod(-1,3) = %a\n", fmod(-1.0, 3.0)); /* R5 */
    /* |x| == |y| → return signed zero */
    printf("fmod(3,3) = %a\n", fmod(3.0, 3.0)); /* R5 */
    printf("fmod(-3,3) = %a\n", fmod(-3.0, 3.0)); /* R5 */
    /* subnormal x */
    printf("fmod(5e-324,3) = %a\n", fmod(D_SUBNORM, 3.0)); /* R5 */
    /* subnormal y */
    printf("fmod(1,5e-324) = %a\n", fmod(1.0, D_SUBNORM)); /* R5 */
    /* fmodf */
    printf("fmodf(inf,3) = %a\n", fmodf(F_INF, 3.0f)); /* R5 */
    printf("fmodf(5,0) = %a\n", fmodf(5.0f, 0.0f)); /* R5 */
    printf("fmodf(nan,3) = %a\n", fmodf(F_NAN, 3.0f)); /* R5 */
    printf("fmodf(1,3) = %a\n", fmodf(1.0f, 3.0f)); /* R5 */
    printf("fmodf(3,3) = %a\n", fmodf(3.0f, 3.0f)); /* R5 */
    printf("fmodf(sn,3) = %a\n", fmodf(F_SUBNORM, 3.0f)); /* R5 */
    printf("fmodf(1,sn) = %a\n", fmodf(1.0f, F_SUBNORM)); /* R5 */
    /* fmodf subnormal y path (iy flag) */
    printf("fmodf(0x1p-126f,0x1p-149f) = %a\n", fmodf(0x1p-126f, 0x1p-149f)); /* R5 */
}

/* frexpd/frexpf — subnormal paths */
static void test_frexp_s5(void)
{
    printf("=== test_frexp_s5 ===\n"); /* R5 */
    int e;
    double m;
    float mf;
    /* subnormal double: hx==0, lx nonzero → ix=-1043 loop */
    m = frexp(D_SUBNORM, &e);
    printf("frexp(5e-324) = %a exp %d\n", m, e); /* R5 */
    m = frexp(0x1p-1050, &e);
    printf("frexp(0x1p-1050) = %a exp %d\n", m, e); /* R5 */
    /* subnormal double: hx nonzero → ix=-1022 loop */
    m = frexp(0x1p-1022, &e);
    printf("frexp(0x1p-1022) = %a exp %d\n", m, e); /* R5 */
    m = frexp(0x1.8p-1040, &e);
    printf("frexp(0x1.8p-1040) = %a exp %d\n", m, e); /* R5 */
    /* zero */
    m = frexp(0.0, &e);
    printf("frexp(0) = %a exp %d\n", m, e); /* R5 */
    /* inf */
    m = frexp(D_INF, &e);
    printf("frexp(inf) = %a exp %d\n", m, e); /* R5 */
    /* frexpf subnormal */
    mf = frexpf(F_SUBNORM, &e);
    printf("frexpf(1.4e-45) = %a exp %d\n", mf, e); /* R5 */
    mf = frexpf(0x1p-130f, &e);
    printf("frexpf(0x1p-130) = %a exp %d\n", mf, e); /* R5 */
    /* frexpf zero */
    mf = frexpf(0.0f, &e);
    printf("frexpf(0) = %a exp %d\n", mf, e); /* R5 */
    /* frexpf inf */
    mf = frexpf(F_INF, &e);
    printf("frexpf(inf) = %a exp %d\n", mf, e); /* R5 */
}

/* gammad.c — __sin_pi, __lgamma branches */
static void test_gamma_s5(void)
{
    printf("=== test_gamma_s5 ===\n"); /* R5 */
    /* __sin_pi: |x| < 0.25 path (line 218 True) — triggered via lgamma(negative x) */
    /* lgamma(-0.1): x<0 path, __sin_pi(0.1), 0.1 < 0.25 → True */
    printf("lgamma(-0.1) = %a\n", lgamma(-0.1)); /* R5 */
    printf("lgamma(-0.2) = %a\n", lgamma(-0.2)); /* R5 */
    /* lgamma negative: hx < 0 (line 244 True) */
    printf("lgamma(-0.5) = %a\n", lgamma(-0.5)); /* R4 */
    printf("lgamma(-1.5) = %a\n", lgamma(-1.5)); /* R4 */
    printf("lgamma(-2.5) = %a\n", lgamma(-2.5)); /* R5 */
    /* lgamma negative integer → div by zero (line 249 True) */
    printf("lgamma(-1) = %a\n", lgamma(-1.0)); /* R5 */
    printf("lgamma(-2) = %a\n", lgamma(-2.0)); /* R5 */
    /* lgamma large negative integer >=2^52 (line 248 True) */
    printf("lgamma(-1e16) = %a\n", lgamma(-1e16)); /* R5 */
    /* lgamma: x in [2,8) — switch cases 3,4,5,6,7 (line 357 True) */
    printf("lgamma(3.5) = %a\n", lgamma(3.5)); /* R5 */
    printf("lgamma(4.5) = %a\n", lgamma(4.5)); /* R5 */
    printf("lgamma(5.5) = %a\n", lgamma(5.5)); /* R5 */
    printf("lgamma(6.5) = %a\n", lgamma(6.5)); /* R5 */
    printf("lgamma(7.5) = %a\n", lgamma(7.5)); /* R5 */
    /* lgamma x >= 8: large x */
    printf("lgamma(10.0) = %a\n", lgamma(10.0)); /* R5 */
    printf("lgamma(1e60) = %a\n", lgamma(1e60)); /* R5 */
    /* lgamma x=0 */
    printf("lgamma(0) = %a\n", lgamma(0.0)); /* R5 */
    /* lgamma x=Inf */
    printf("lgamma(inf) = %a\n", lgamma(D_INF)); /* R5 */
    /* lgamma tiny |x| */
    printf("lgamma(1e-300) = %a\n", lgamma(1e-300)); /* R5 */
    /* tgamma similar paths */
    printf("tgamma(-0.5) = %a\n", tgamma(-0.5)); /* R5 */
    printf("tgamma(-1.5) = %a\n", tgamma(-1.5)); /* R5 */
    printf("tgamma(5.5) = %a\n", tgamma(5.5)); /* R5 */
    printf("tgamma(7.5) = %a\n", tgamma(7.5)); /* R5 */
    printf("tgamma(10.0) = %a\n", tgamma(10.0)); /* R5 */
}

/* gammaf.c — __lgammaf branches (many) */
static void test_gammaf_s5(void)
{
    printf("=== test_gammaf_s5 ===\n"); /* R5 */
    /* __lgammaf: Inf/NaN (line 151 True) */
    printf("lgammaf(inf) = %a\n", lgammaf(F_INF)); /* R5 */
    printf("lgammaf(nan) = %a\n", lgammaf(F_NAN)); /* R5 */
    /* x=0 (line 155 True) */
    printf("lgammaf(0) = %a\n", lgammaf(0.0f)); /* R5 */
    /* tiny x (line 162 True): |x| < 2^-30 */
    printf("lgammaf(1e-10f) = %a\n", lgammaf(1e-10f)); /* R5 */
    printf("lgammaf(-1e-10f) = %a\n", lgammaf(-1e-10f)); /* R5 */
    /* negative x branches (line 171 True) */
    printf("lgammaf(-0.5f) = %a\n", lgammaf(-0.5f)); /* R4 */
    printf("lgammaf(-1.5f) = %a\n", lgammaf(-1.5f)); /* R4 */
    printf("lgammaf(-2.5f) = %a\n", lgammaf(-2.5f)); /* R5 */
    printf("lgammaf(-3.5f) = %a\n", lgammaf(-3.5f)); /* R5 */
    /* negative integer (t==0, line 178 True) */
    printf("lgammaf(-1) = %a\n", lgammaf(-1.0f)); /* R5 */
    printf("lgammaf(-2) = %a\n", lgammaf(-2.0f)); /* R5 */
    /* large negative (>= 2^23, line 172 True) */
    printf("lgammaf(-1e8f) = %a\n", lgammaf(-1e8f)); /* R4 */
    /* t < 0: signgamp=-1 (line 184 True) */
    printf("lgammaf(-0.3f) = %a\n", lgammaf(-0.3f)); /* R5 */
    printf("lgammaf(-1.3f) = %a\n", lgammaf(-1.3f)); /* R5 */
    /* x=1 or x=2 (line 192 True) */
    printf("lgammaf(1) = %a\n", lgammaf(1.0f)); /* R5 */
    printf("lgammaf(2) = %a\n", lgammaf(2.0f)); /* R5 */
    /* x < 2: various sub-ranges */
    printf("lgammaf(0.3f) = %a\n", lgammaf(0.3f)); /* R5 */
    printf("lgammaf(0.5f) = %a\n", lgammaf(0.5f)); /* R4 */
    printf("lgammaf(0.8f) = %a\n", lgammaf(0.8f)); /* R4 */
    printf("lgammaf(1.2f) = %a\n", lgammaf(1.2f)); /* R5 */
    printf("lgammaf(1.5f) = %a\n", lgammaf(1.5f)); /* R4 */
    printf("lgammaf(1.8f) = %a\n", lgammaf(1.8f)); /* R4 */
    /* x in [2,8): switch cases */
    printf("lgammaf(2.5f) = %a\n", lgammaf(2.5f)); /* R4 */
    printf("lgammaf(3.5f) = %a\n", lgammaf(3.5f)); /* R4 */
    printf("lgammaf(4.5f) = %a\n", lgammaf(4.5f)); /* R4 */
    printf("lgammaf(5.5f) = %a\n", lgammaf(5.5f)); /* R5 */
    printf("lgammaf(6.5f) = %a\n", lgammaf(6.5f)); /* R5 */
    printf("lgammaf(7.5f) = %a\n", lgammaf(7.5f)); /* R4 */
    /* x in [8, 2^58) */
    printf("lgammaf(9.0f) = %a\n", lgammaf(9.0f)); /* R5 */
    printf("lgammaf(100.0f) = %a\n", lgammaf(100.0f)); /* R4 */
    /* x >= 2^58 */
    printf("lgammaf(1e20f) = %a\n", lgammaf(1e20f)); /* R5 */
    /* tgammaf */
    printf("tgammaf(inf) = %a\n", tgammaf(F_INF)); /* R5 */
    printf("tgammaf(-0.5f) = %a\n", tgammaf(-0.5f)); /* R5 */
    printf("tgammaf(-1.5f) = %a\n", tgammaf(-1.5f)); /* R5 */
    printf("tgammaf(5.5f) = %a\n", tgammaf(5.5f)); /* R5 */
    printf("tgammaf(7.5f) = %a\n", tgammaf(7.5f)); /* R5 */
    printf("tgammaf(10.0f) = %a\n", tgammaf(10.0f)); /* R5 */
    printf("tgammaf(1e20f) = %a\n", tgammaf(1e20f)); /* R5 */
}

/* hypotd/hypotf — large and subnormal paths */
static void test_hypot_s5(void)
{
    printf("=== test_hypot_s5 ===\n"); /* R5 */
    /* a > 2^500, Inf */
    printf("hypot(inf,1) = %a\n", hypot(D_INF, 1.0)); /* R5 */
    printf("hypot(1,inf) = %a\n", hypot(1.0, D_INF)); /* R5 */
    printf("hypot(nan,1) = %a\n", hypot(D_NAN, 1.0)); /* R5 */
    printf("hypot(1,nan) = %a\n", hypot(1.0, D_NAN)); /* R5 */
    /* a > 2^500 but finite: scale down */
    printf("hypot(0x1p600,0x1p599) = %a\n", hypot(0x1p600, 0x1p599)); /* R5 */
    /* b < 2^-500 subnormal */
    printf("hypot(1,5e-324) = %a\n", hypot(1.0, D_SUBNORM)); /* R5 */
    printf("hypot(5e-324,5e-324) = %a\n", hypot(D_SUBNORM, D_SUBNORM)); /* R5 */
    /* ratio > 2^60 */
    printf("hypot(1e60,1) = %a\n", hypot(1e60, 1.0)); /* R5 */
    /* normal cases */
    printf("hypot(3,4) = %a\n", hypot(3.0, 4.0)); /* R5 */
    printf("hypot(5,12) = %a\n", hypot(5.0, 12.0)); /* R5 */
    /* hypotf: very large */
    printf("hypotf(inf,1) = %a\n", hypotf(F_INF, 1.0f)); /* R5 */
    printf("hypotf(1,inf) = %a\n", hypotf(1.0f, F_INF)); /* R5 */
    printf("hypotf(1e20f,1) = %a\n", hypotf(1e20f, 1.0f)); /* R5 */
    printf("hypotf(1,1e-20f) = %a\n", hypotf(1.0f, 1e-20f)); /* R5 */
    printf("hypotf(1e30f,1e-10f) = %a\n", hypotf(1e30f, 1e-10f)); /* R5 */
}

/* ilogbd — zero, subnormal with hx=0 and hx≠0, Inf, NaN */
static void test_ilogb_s5(void)
{
    printf("=== test_ilogb_s5 ===\n"); /* R5 */
    /* subnormal: hx==0 branch (ix=-1043 loop) */
    printf("ilogb(5e-324) = %d\n", ilogb(D_SUBNORM)); /* R5 */
    printf("ilogb(0x1p-1074) = %d\n", ilogb(0x1p-1074)); /* R4 */
    /* subnormal: hx!=0 branch (ix=-1022 loop) */
    printf("ilogb(0x1p-1022) = %d\n", ilogb(0x1p-1022)); /* R5 */
    printf("ilogb(0x0.8p-1022) = %d\n", ilogb(0x0.8p-1022)); /* R5 */
    printf("ilogb(0x1.8p-1040) = %d\n", ilogb(0x1.8p-1040)); /* R5 */
    /* zero */
    printf("ilogb(0) = %d\n", ilogb(0.0)); /* R5 */
    /* Inf */
    printf("ilogb(inf) = %d\n", ilogb(D_INF)); /* R5 */
    /* NaN */
    printf("ilogb(nan) = %d\n", ilogb(D_NAN)); /* R5 */
    /* ilogbf subnormal */
    printf("ilogbf(1.4e-45f) = %d\n", ilogbf(F_SUBNORM)); /* R5 */
    printf("ilogbf(0) = %d\n", ilogbf(0.0f)); /* R5 */
    printf("ilogbf(inf) = %d\n", ilogbf(F_INF)); /* R5 */
    printf("ilogbf(nan) = %d\n", ilogbf(F_NAN)); /* R5 */
}

/* j0d, j1d, jnd — specific branches */
static void test_bessel_s5(void)
{
    printf("=== test_bessel_s5 ===\n"); /* R5 */
    /* j0d: |x|>=2: (s*c)<0 branch */
    printf("j0(3) = %a\n", j0(3.0)); /* R5 */
    printf("j0(5) = %a\n", j0(5.0)); /* R5 */
    printf("j0(10) = %a\n", j0(10.0)); /* R5 */
    printf("j0(100) = %a\n", j0(100.0)); /* R5 */
    /* j0d: Inf → 0 */
    printf("j0(inf) = %a\n", j0(D_INF)); /* R5 */
    /* j0d: |x|<2^-13 */
    printf("j0(1e-5) = %a\n", j0(1e-5)); /* R5 */
    printf("j0(1e-15) = %a\n", j0(1e-15)); /* R5 */
    /* j1d: |x|>=2 */
    printf("j1(3) = %a\n", j1(3.0)); /* R5 */
    printf("j1(10) = %a\n", j1(10.0)); /* R5 */
    printf("j1(100) = %a\n", j1(100.0)); /* R5 */
    /* j1d: Inf */
    printf("j1(inf) = %a\n", j1(D_INF)); /* R5 */
    /* j1d: |x|<2^-27 */
    printf("j1(1e-10) = %a\n", j1(1e-10)); /* R5 */
    /* jnd: n > x forward recurrence, large x */
    printf("jn(10,100) = %a\n", jn(10, 100.0)); /* R5 */
    printf("jn(10,1e60) = %a\n", jn(10, 1e60)); /* R5 */
    /* jnd: n <= x backward recurrence */
    printf("jn(5,3) = %a\n", jn(5, 3.0)); /* R5 */
    printf("jn(100,50) = %a\n", jn(100, 50.0)); /* R5 */
    /* jnd: x < 2^-29 */
    printf("jn(5,1e-10) = %a\n", jn(5, 1e-10)); /* R5 */
    printf("jn(40,1e-10) = %a\n", jn(40, 1e-10)); /* R5 */
    /* y0d: Inf */
    printf("y0(inf) = %a\n", y0(D_INF)); /* R5 */
    /* y0d: |x| >= 2 with s*c sign check */
    printf("y0(3) = %a\n", y0(3.0)); /* R5 */
    printf("y0(10) = %a\n", y0(10.0)); /* R5 */
    printf("y0(100) = %a\n", y0(100.0)); /* R5 */
    /* y1d: Inf */
    printf("y1(inf) = %a\n", y1(D_INF)); /* R5 */
    printf("y1(10) = %a\n", y1(10.0)); /* R5 */
    printf("y1(100) = %a\n", y1(100.0)); /* R5 */
    /* ynd: x > 2^302 */
    printf("yn(3,1e100) = %a\n", yn(3, 1e100)); /* R5 */
    printf("yn(3,1e200) = %a\n", yn(3, 1e200)); /* R5 */
    /* ynd: backward from y0,y1 with overflow check */
    printf("yn(5,1.0) = %a\n", yn(5, 1.0)); /* R5 */
    printf("yn(10,0.5) = %a\n", yn(10, 0.5)); /* R5 */
}

/* log branches */
static void test_log_s5(void)
{
    printf("=== test_log_s5 ===\n"); /* R5 */
    /* logd: k==0 and f==0 (x near 1.0, no exponent shift) */
    printf("log(1.0) = %a\n", log(1.0)); /* R5 */
    /* logd: |f|<2^-20, f!=0 */
    printf("log(1.0+1e-7) = %a\n", log(1.0 + 1e-7)); /* R5 */
    /* logd: k != 0 */
    printf("log(2.0) = %a\n", log(2.0)); /* R5 */
    printf("log(0.5) = %a\n", log(0.5)); /* R5 */
    /* logd: x = 1.0 (k=0, f=0) */
    printf("log(1.0000000001) = %a\n", log(1.0000000001)); /* R5 */
    /* log10d: k=0, f!=0 near 1 */
    printf("log10(1.0+1e-7) = %a\n", log10(1.0 + 1e-7)); /* R5 */
    /* log10d: subnormal x */
    printf("log10(5e-324) = %a\n", log10(D_SUBNORM)); /* R5 */
    /* log2d: k=0, f near 0 */
    printf("log2(1.0+1e-7) = %a\n", log2(1.0 + 1e-7)); /* R5 */
    /* log1pd: k!=0, correction term */
    printf("log1p(0.5) = %a\n", log1p(0.5)); /* R5 */
    printf("log1p(2.0) = %a\n", log1p(2.0)); /* R5 */
    printf("log1p(1e30) = %a\n", log1p(1e30)); /* R5 */
    /* log1pd: f==0 large x (k large, hu=0 region) */
    printf("log1p(1e15) = %a\n", log1p(1e15)); /* R5 */
    /* log1pf */
    printf("log1pf(0.5f) = %a\n", log1pf(0.5f)); /* R5 */
    printf("log1pf(2.0f) = %a\n", log1pf(2.0f)); /* R5 */
    printf("log1pf(1e8f) = %a\n", log1pf(1e8f)); /* R5 */
    /* logf: k=0, f=0 */
    printf("logf(1.0f) = %a\n", logf(1.0f)); /* R5 */
    printf("logf(1.0f+1e-7f) = %a\n", logf(1.0f + 1e-7f)); /* R5 */
    printf("logf(2.0f) = %a\n", logf(2.0f)); /* R4 */
}

/* modfd/modff — branches for different exponent ranges */
static void test_modf_s5(void)
{
    printf("=== test_modf_s5 ===\n"); /* R5 */
    double ip;
    float ipf;
    /* j0 < 0: |x| < 1 */
    printf("modf(0.5) = %a\n", modf(0.5, &ip)); /* R5 */
    printf("modf(-0.5) = %a\n", modf(-0.5, &ip)); /* R5 */
    printf("modf(0.0) = %a\n", modf(0.0, &ip)); /* R5 */
    printf("modf(-0.0) = %a\n", modf(-0.0, &ip)); /* R5 */
    /* j0 in [0,20): integral */
    printf("modf(4.0) = %a\n", modf(4.0, &ip)); /* R5 */
    printf("modf(-4.0) = %a\n", modf(-4.0, &ip)); /* R5 */
    /* j0 in [0,20): not integral */
    printf("modf(3.7) = %a\n", modf(3.7, &ip)); /* R5 */
    printf("modf(-3.7) = %a\n", modf(-3.7, &ip)); /* R5 */
    /* j0 > 51: integral (high bits only) */
    printf("modf(0x1p55) = %a\n", modf(0x1p55, &ip)); /* R5 */
    printf("modf(0x1p60) = %a\n", modf(0x1p60, &ip)); /* R5 */
    /* j0 in [20,52): low-word fractional */
    printf("modf(0x1p25+0.5) = %a\n", modf(0x1p25 + 0.5, &ip)); /* R5 */
    printf("modf(-(0x1p25+0.5)) = %a\n", modf(-(0x1p25 + 0.5), &ip)); /* R5 */
    /* modff similar */
    printf("modff(0.5f) = %a\n", modff(0.5f, &ipf)); /* R5 */
    printf("modff(-0.5f) = %a\n", modff(-0.5f, &ipf)); /* R5 */
    printf("modff(4.0f) = %a\n", modff(4.0f, &ipf)); /* R5 */
    printf("modff(3.7f) = %a\n", modff(3.7f, &ipf)); /* R5 */
    printf("modff(0x1p26f) = %a\n", modff(0x1p26f, &ipf)); /* R5 */
    printf("modff(0x1p22f+0.5f) = %a\n", modff(0x1p22f + 0.5f, &ipf)); /* R5 */
}

/* nextafterd/nextafterf branches */
static void test_nextafter_s5(void)
{
    printf("=== test_nextafter_s5 ===\n"); /* R5 */
    /* x=0, y=0 of same sign → return y */
    printf("nextafter(+0,+0) = %a\n", nextafter(0.0, 0.0)); /* R5 */
    printf("nextafter(-0,-0) = %a\n", nextafter(-0.0, -0.0)); /* R5 */
    /* x=0, y≠0 → return ±minnorm */
    printf("nextafter(+0,1) = %a\n", nextafter(0.0, 1.0)); /* R5 */
    printf("nextafter(+0,-1) = %a\n", nextafter(0.0, -1.0)); /* R5 */
    printf("nextafter(-0,1) = %a\n", nextafter(-0.0, 1.0)); /* R5 */
    /* x>0, x>y (decrease) */
    printf("nextafter(2,1) = %a\n", nextafter(2.0, 1.0)); /* R5 */
    /* x>0, x<y (increase) */
    printf("nextafter(1,2) = %a\n", nextafter(1.0, 2.0)); /* R5 */
    /* x<0, x<y (increase toward 0) */
    printf("nextafter(-2,1) = %a\n", nextafter(-2.0, 1.0)); /* R5 */
    /* x<0, x>y (decrease away from 0) */
    printf("nextafter(-1,-2) = %a\n", nextafter(-1.0, -2.0)); /* R5 */
    /* x=y (same) */
    printf("nextafter(1,1) = %a\n", nextafter(1.0, 1.0)); /* R5 */
    /* overflow: near max */
    printf("nextafter(0x1.fffffffffffffp1023,inf) = %a\n", /* R5 */
           nextafter(0x1.fffffffffffffp1023, D_INF));
    /* underflow: near min subnormal */
    printf("nextafter(5e-324,0) = %a\n", nextafter(D_SUBNORM, 0.0)); /* R5 */
    /* NaN */
    printf("nextafter(nan,1) = %a\n", nextafter(D_NAN, 1.0)); /* R5 */
    printf("nextafter(1,nan) = %a\n", nextafter(1.0, D_NAN)); /* R5 */
    /* nextafterf */
    printf("nextafterf(+0,1) = %a\n", nextafterf(0.0f, 1.0f)); /* R5 */
    printf("nextafterf(+0,-1) = %a\n", nextafterf(0.0f, -1.0f)); /* R5 */
    printf("nextafterf(1,2) = %a\n", nextafterf(1.0f, 2.0f)); /* R5 */
    printf("nextafterf(2,1) = %a\n", nextafterf(2.0f, 1.0f)); /* R5 */
    printf("nextafterf(-2,1) = %a\n", nextafterf(-2.0f, 1.0f)); /* R5 */
    printf("nextafterf(nan,1) = %a\n", nextafterf(F_NAN, 1.0f)); /* R5 */
    printf("nextafterf(1.4e-45f,0) = %a\n", nextafterf(F_SUBNORM, 0.0f)); /* R5 */
}

/* powd/powf — many branches */
static void test_pow_s5(void)
{
    printf("=== test_pow_s5 ===\n"); /* R5 */
    /* y=0 → 1.0 */
    printf("pow(5,0) = %a\n", pow(5.0, 0.0)); /* R5 */
    printf("pow(nan,0) = %a\n", pow(D_NAN, 0.0)); /* R5 */
    /* y=NaN: 1^NaN=1 */
    printf("pow(1,nan) = %a\n", pow(1.0, D_NAN)); /* R5 */
    /* y=NaN: x≠1 → NaN */
    printf("pow(2,nan) = %a\n", pow(2.0, D_NAN)); /* R5 */
    /* x<0: yisint cases */
    printf("pow(-2,3) = %a\n", pow(-2.0, 3.0)); /* R5 */
    printf("pow(-2,2) = %a\n", pow(-2.0, 2.0)); /* R5 */
    printf("pow(-2,0.5) = %a\n", pow(-2.0, 0.5)); /* R5 */
    /* y=+Inf: |x|=1 → 1 */
    printf("pow(1,inf) = %a\n", pow(1.0, D_INF)); /* R5 */
    printf("pow(-1,inf) = %a\n", pow(-1.0, D_INF)); /* R5 */
    /* y=+Inf: |x|>1 → +Inf */
    printf("pow(2,inf) = %a\n", pow(2.0, D_INF)); /* R5 */
    /* y=+Inf: |x|<1 → 0 */
    printf("pow(0.5,inf) = %a\n", pow(0.5, D_INF)); /* R5 */
    /* y=-Inf: |x|=1 → 1 */
    printf("pow(1,-inf) = %a\n", pow(1.0, D_NINF)); /* R5 */
    /* x=0: y>0 → 0 */
    printf("pow(0,2) = %a\n", pow(0.0, 2.0)); /* R5 */
    /* x=0: y<0 → +Inf */
    printf("pow(0,-2) = %a\n", pow(0.0, -2.0)); /* R5 */
    /* x=+Inf: y>0 → +Inf */
    printf("pow(inf,2) = %a\n", pow(D_INF, 2.0)); /* R5 */
    /* x=-Inf: y=odd_int > 0 → -Inf */
    printf("pow(-inf,3) = %a\n", pow(D_NINF, 3.0)); /* R5 */
    /* x=-Inf: y=even_int > 0 → +Inf */
    printf("pow(-inf,4) = %a\n", pow(D_NINF, 4.0)); /* R5 */
    /* |y| very large: overflow path */
    printf("pow(1.1,1e100) = %a\n", pow(1.1, 1e100)); /* R5 */
    printf("pow(0.9,1e100) = %a\n", pow(0.9, 1e100)); /* R5 */
    /* subnormal x */
    printf("pow(5e-324,0.5) = %a\n", pow(D_SUBNORM, 0.5)); /* R5 */
    /* log interval selection (j near sqrt(3/2) and sqrt(3)) */
    printf("pow(1.22,10) = %a\n", pow(1.22, 10.0)); /* R5 */
    printf("pow(1.23,10) = %a\n", pow(1.23, 10.0)); /* R5 */
    printf("pow(1.73,10) = %a\n", pow(1.73, 10.0)); /* R5 */
    printf("pow(1.74,10) = %a\n", pow(1.74, 10.0)); /* R5 */
    /* overflow/underflow near threshold */
    printf("pow(2,1023) = %a\n", pow(2.0, 1023.0)); /* R5 */
    printf("pow(2,-1074) = %a\n", pow(2.0, -1074.0)); /* R5 */
    /* powf */
    printf("powf(1,nan) = %a\n", powf(1.0f, F_NAN)); /* R5 */
    printf("powf(-2,3) = %a\n", powf(-2.0f, 3.0f)); /* R5 */
    printf("powf(-2,0.5) = %a\n", powf(-2.0f, 0.5f)); /* R5 */
    printf("powf(2,inf) = %a\n", powf(2.0f, F_INF)); /* R5 */
    printf("powf(0.5,inf) = %a\n", powf(0.5f, F_INF)); /* R5 */
    printf("powf(1.1f,1e10f) = %a\n", powf(1.1f, 1e10f)); /* R5 */
    printf("powf(0.9f,1e10f) = %a\n", powf(0.9f, 1e10f)); /* R5 */
    printf("powf(1.22f,100) = %a\n", powf(1.22f, 100.0f)); /* R5 */
    printf("powf(1.73f,100) = %a\n", powf(1.73f, 100.0f)); /* R5 */
    printf("powf(2,-150) = %a\n", powf(2.0f, -150.0f)); /* R5 */
}

/* remainderd/remainderf — subnormal y */
static void test_remainder_s5(void)
{
    printf("=== test_remainder_s5 ===\n"); /* R5 */
    /* subnormal y (hy < 0x00200000) */
    printf("remainder(3,5e-324) = %a\n", remainder(3.0, D_SUBNORM)); /* R5 */
    printf("remainder(1e-300,5e-324) = %a\n", remainder(1e-300, D_SUBNORM)); /* R5 */
    /* normal */
    printf("remainder(5,3) = %a\n", remainder(5.0, 3.0)); /* R5 */
    printf("remainder(-5,3) = %a\n", remainder(-5.0, 3.0)); /* R5 */
    printf("remainder(7,3) = %a\n", remainder(7.0, 3.0)); /* R5 */
    /* remainderf: subnormal y */
    printf("remainderf(3,1.4e-45f) = %a\n", remainderf(3.0f, F_SUBNORM)); /* R5 */
    printf("remainderf(1e-37f,1.4e-45f) = %a\n", remainderf(1e-37f, F_SUBNORM)); /* R5 */
    printf("remainderf(5,3) = %a\n", remainderf(5.0f, 3.0f)); /* R5 */
    printf("remainderf(7,3) = %a\n", remainderf(7.0f, 3.0f)); /* R5 */
}

/* remquod/remquof — special cases */
static void test_remquo_s5(void)
{
    printf("=== test_remquo_s5 ===\n"); /* R5 */
    int q;
    double r;
    float rf;
    /* x=Inf → invalid */
    r = remquo(D_INF, 3.0, &q);
    printf("remquo(inf,3) = %a\n", r); /* R5 */
    /* NaN */
    r = remquo(D_NAN, 3.0, &q);
    printf("remquo(nan,3) = %a\n", r); /* R5 */
    /* y=0 → invalid */
    r = remquo(5.0, 0.0, &q);
    printf("remquo(5,0) = %a\n", r); /* R5 */
    /* |x|==|y| → return +-0 */
    r = remquo(3.0, 3.0, &q);
    printf("remquo(3,3) = %a quo %d\n", r, q); /* R5 */
    r = remquo(-3.0, 3.0, &q);
    printf("remquo(-3,3) = %a quo %d\n", r, q); /* R5 */
    /* x >= 4y */
    r = remquo(13.0, 3.0, &q);
    printf("remquo(13,3) = %a quo %d\n", r, q); /* R5 */
    /* x >= 2y */
    r = remquo(7.0, 3.0, &q);
    printf("remquo(7,3) = %a quo %d\n", r, q); /* R5 */
    /* subnormal y */
    r = remquo(1.0, D_SUBNORM, &q);
    printf("remquo(1,5e-324) = %a\n", r); /* R5 */
    /* remquof */
    rf = remquof(F_INF, 3.0f, &q);
    printf("remquof(inf,3) = %a\n", rf); /* R5 */
    rf = remquof(F_NAN, 3.0f, &q);
    printf("remquof(nan,3) = %a\n", rf); /* R5 */
    rf = remquof(5.0f, 0.0f, &q);
    printf("remquof(5,0) = %a\n", rf); /* R5 */
    rf = remquof(3.0f, 3.0f, &q);
    printf("remquof(3,3) = %a quo %d\n", rf, q); /* R5 */
    rf = remquof(13.0f, 3.0f, &q);
    printf("remquof(13,3) = %a quo %d\n", rf, q); /* R5 */
    rf = remquof(7.0f, 3.0f, &q);
    printf("remquof(7,3) = %a quo %d\n", rf, q); /* R5 */
    rf = remquof(1.0f, F_SUBNORM, &q);
    printf("remquof(1,1.4e-45) = %a\n", rf); /* R5 */
}

/* rintf — branch at line 47 (already integral) */
static void test_rint_s5(void)
{
    printf("=== test_rint_s5 ===\n"); /* R5 */
    /* j0 >= 0 and (_i0 & i) == 0: already integral float */
    printf("rintf(2.0f) = %a\n", rintf(2.0f)); /* R5 */
    printf("rintf(4.0f) = %a\n", rintf(4.0f)); /* R5 */
    printf("rintf(8.0f) = %a\n", rintf(8.0f)); /* R5 */
    printf("rintf(-2.0f) = %a\n", rintf(-2.0f)); /* R5 */
    /* j0 >= 0, not integral, half-bit set */
    printf("rintf(1.5f) = %a\n", rintf(1.5f)); /* R4 */
    printf("rintf(2.5f) = %a\n", rintf(2.5f)); /* R4 */
    printf("rintf(-1.5f) = %a\n", rintf(-1.5f)); /* R4 */
    /* large */
    printf("rintf(1e10f) = %a\n", rintf(1e10f)); /* R5 */
    printf("rintf(inf) = %a\n", rintf(F_INF)); /* R5 */
}

/* roundd — branch at line 85 (integral with mask) */
static void test_round_s5(void)
{
    printf("=== test_round_s5 ===\n"); /* R5 */
    /* exponent < 20: integral (msw fractional bits all zero, lsw==0) */
    printf("round(4.0) = %a\n", round(4.0)); /* R5 */
    printf("round(8.0) = %a\n", round(8.0)); /* R5 */
    printf("round(-4.0) = %a\n", round(-4.0)); /* R5 */
    /* exponent < 20: not integral */
    printf("round(1.5) = %a\n", round(1.5)); /* R5 */
    printf("round(2.5) = %a\n", round(2.5)); /* R4 */
    printf("round(-1.5) = %a\n", round(-1.5)); /* R5 */
    /* exponent == -1: round to +-1 */
    printf("round(0.5) = %a\n", round(0.5)); /* R4 */
    printf("round(-0.5) = %a\n", round(-0.5)); /* R4 */
    /* exponent < -1: round to 0 */
    printf("round(0.3) = %a\n", round(0.3)); /* R5 */
    printf("round(-0.3) = %a\n", round(-0.3)); /* R5 */
    /* exponent > 51 but not 1024 */
    printf("round(1e18) = %a\n", round(1e18)); /* R5 */
    /* exponent in [20,51]: lsw fractional bits */
    printf("round(0x1p30+0.5) = %a\n", round(0x1p30 + 0.5)); /* R5 */
    printf("round(0x1p30) = %a\n", round(0x1p30)); /* R5 */
    /* NaN/Inf */
    printf("round(inf) = %a\n", round(D_INF)); /* R5 */
    printf("round(nan) = %a\n", round(D_NAN)); /* R5 */
}

/* scalbnd/scalbnf — subnormal, n very large/small */
static void test_scalbn_s5(void)
{
    printf("=== test_scalbn_s5 ===\n"); /* R5 */
    /* subnormal input: scale up by 2^54 first */
    printf("scalbn(5e-324,1) = %a\n", scalbn(D_SUBNORM, 1)); /* R5 */
    printf("scalbn(0x1p-1050,100) = %a\n", scalbn(0x1p-1050, 100)); /* R5 */
    /* subnormal with n very negative */
    printf("scalbn(0x1p-1022,−50000) = %a\n", scalbn(0x1p-1022, -50000)); /* R5 */
    /* n very large → overflow */
    printf("scalbn(1,50001) = %a\n", scalbn(1.0, 50001)); /* R5 */
    /* k after n too large → overflow */
    printf("scalbn(1,2047) = %a\n", scalbn(1.0, 2047)); /* R5 */
    /* k after n too small → underflow (k<=0 path) */
    printf("scalbn(1,-2000) = %a\n", scalbn(1.0, -2000)); /* R5 */
    /* NaN/Inf */
    printf("scalbn(nan,1) = %a\n", scalbn(D_NAN, 1)); /* R5 */
    printf("scalbn(inf,1) = %a\n", scalbn(D_INF, 1)); /* R5 */
    /* scalbnf subnormal */
    printf("scalbnf(1.4e-45f,1) = %a\n", scalbnf(F_SUBNORM, 1)); /* R5 */
    printf("scalbnf(0x1p-130f,100) = %a\n", scalbnf(0x1p-130f, 100)); /* R5 */
    printf("scalbnf(0x1p-126f,-50000) = %a\n", scalbnf(0x1p-126f, -50000)); /* R5 */
    printf("scalbnf(1,50001) = %a\n", scalbnf(1.0f, 50001)); /* R5 */
    printf("scalbnf(1,255) = %a\n", scalbnf(1.0f, 255)); /* R5 */
    printf("scalbnf(1,-200) = %a\n", scalbnf(1.0f, -200)); /* R5 */
}

/* sqrtd/sqrtf — subnormal, negative, special */
static void test_sqrt_s5(void)
{
    printf("=== test_sqrt_s5 ===\n"); /* R5 */
    /* subnormal input (m=0 branch) */
    printf("sqrt(5e-324) = %a\n", sqrt(D_SUBNORM)); /* R5 */
    printf("sqrt(0x1p-1050) = %a\n", sqrt(0x1p-1050)); /* R5 */
    printf("sqrt(0x1p-1022) = %a\n", sqrt(0x1p-1022)); /* R4 */
    /* odd exponent bit (m&1 branch) */
    printf("sqrt(2.0) = %a\n", sqrt(2.0)); /* R4 */
    printf("sqrt(8.0) = %a\n", sqrt(8.0)); /* R5 */
    /* even exponent */
    printf("sqrt(4.0) = %a\n", sqrt(4.0)); /* R5 */
    printf("sqrt(9.0) = %a\n", sqrt(9.0)); /* R5 */
    /* remainder loop (ix0|ix1 != 0) */
    printf("sqrt(2.1) = %a\n", sqrt(2.1)); /* R5 */
    printf("sqrt(3.14159) = %a\n", sqrt(3.14159)); /* R5 */
    /* specific round bit cases */
    printf("sqrt(0x1.0000000000001p0) = %a\n", sqrt(0x1.0000000000001p0)); /* R5 */
    /* sqrtf: NaN/Inf */
    printf("sqrtf(inf) = %a\n", sqrtf(F_INF)); /* R5 */
    printf("sqrtf(nan) = %a\n", sqrtf(F_NAN)); /* R5 */
    printf("sqrtf(-inf) = %a\n", sqrtf(F_NINF)); /* R5 */
    printf("sqrtf(-1) = %a\n", sqrtf(-1.0f)); /* R5 */
    /* sqrtf subnormal */
    printf("sqrtf(1.4e-45f) = %a\n", sqrtf(F_SUBNORM)); /* R5 */
    printf("sqrtf(0x1p-130f) = %a\n", sqrtf(0x1p-130f)); /* R5 */
    /* sqrtf: (ix<0) → negative */
    printf("sqrtf(-0.5f) = %a\n", sqrtf(-0.5f)); /* R5 */
}

/* trigd/__rem_pio2 — small and Inf/NaN paths */
static void test_trigd_s5(void)
{
    printf("=== test_trigd_s5 ===\n"); /* R5 */
    double y[2];
    int n;
    /* line 461: |x| <= pi/4 → no reduction */
    n = __rem_pio2(0.5, y);
    printf("__rem_pio2(0.5) n=%d y0=%a\n", n, y[0]); /* R5 */
    n = __rem_pio2(0.7, y);
    printf("__rem_pio2(0.7) n=%d y0=%a\n", n, y[0]); /* R5 */
    /* line 467: near pi/2 positive */
    n = __rem_pio2(1.5707963267948966, y);  /* exact pi/2 */
    printf("__rem_pio2(pi/2) n=%d y0=%a\n", n, y[0]); /* R5 */
    /* line 467: |x| < 3pi/4, negative */
    n = __rem_pio2(-1.5, y);
    printf("__rem_pio2(-1.5) n=%d y0=%a\n", n, y[0]); /* R5 */
    /* line 544: Inf/NaN */
    n = __rem_pio2(D_INF, y);
    printf("__rem_pio2(inf) n=%d\n", n); /* R5 */
    n = __rem_pio2(D_NAN, y);
    printf("__rem_pio2(nan) n=%d\n", n); /* R5 */
    /* medium range: 2nd and 3rd iteration */
    n = __rem_pio2(1e5, y);
    printf("__rem_pio2(1e5) n=%d y0=%a\n", n, y[0]); /* R5 */
    n = __rem_pio2(1e10, y);
    printf("__rem_pio2(1e10) n=%d y0=%a\n", n, y[0]); /* R5 */
    /* large: Payne-Hanek */
    n = __rem_pio2(1e20, y);
    printf("__rem_pio2(1e20) n=%d y0=%a\n", n, y[0]); /* R5 */
    n = __rem_pio2(1e100, y);
    printf("__rem_pio2(1e100) n=%d y0=%a\n", n, y[0]); /* R5 */
    /* internal branches via sin/cos with specific values */
    printf("sin(0.5) = %a\n", sin(0.5)); /* R5 */
    printf("cos(0.5) = %a\n", cos(0.5)); /* R5 */
    printf("tan(0.5) = %a\n", tan(0.5)); /* R5 */
    printf("sin(1.5) = %a\n", sin(1.5)); /* R5 */
    printf("cos(1.5) = %a\n", cos(1.5)); /* R5 */
    printf("sin(1e6) = %a\n", sin(1e6)); /* R5 */
    printf("cos(1e6) = %a\n", cos(1e6)); /* R5 */
    printf("sin(1e15) = %a\n", sin(1e15)); /* R4 */
    printf("cos(1e15) = %a\n", cos(1e15)); /* R4 */
    printf("tan(1e15) = %a\n", tan(1e15)); /* R5 */
}

/* trigf/__rem_pio2f — small and Inf/NaN paths */
static void test_trigf_s5(void)
{
    printf("=== test_trigf_s5 ===\n"); /* R5 */
    float yf[2];
    int n;
    /* line 343: |x| <= pi/4f → no reduction */
    n = __rem_pio2f(0.5f, yf);
    printf("__rem_pio2f(0.5) n=%d y0=%a\n", n, yf[0]); /* R5 */
    n = __rem_pio2f(0.7f, yf);
    printf("__rem_pio2f(0.7) n=%d y0=%a\n", n, yf[0]); /* R5 */
    /* near pi/2f */
    n = __rem_pio2f(1.5707963f, yf);
    printf("__rem_pio2f(pi/2f) n=%d y0=%a\n", n, yf[0]); /* R5 */
    /* negative */
    n = __rem_pio2f(-1.5f, yf);
    printf("__rem_pio2f(-1.5f) n=%d y0=%a\n", n, yf[0]); /* R5 */
    /* line 427: Inf/NaN */
    n = __rem_pio2f(F_INF, yf);
    printf("__rem_pio2f(inf) n=%d\n", n); /* R5 */
    n = __rem_pio2f(F_NAN, yf);
    printf("__rem_pio2f(nan) n=%d\n", n); /* R5 */
    /* medium range: 2nd and 3rd iteration */
    n = __rem_pio2f(1e3f, yf);
    printf("__rem_pio2f(1e3) n=%d y0=%a\n", n, yf[0]); /* R5 */
    n = __rem_pio2f(1e5f, yf);
    printf("__rem_pio2f(1e5) n=%d y0=%a\n", n, yf[0]); /* R5 */
    /* large: Payne-Hanek float */
    n = __rem_pio2f(1e10f, yf);
    printf("__rem_pio2f(1e10) n=%d y0=%a\n", n, yf[0]); /* R5 */
    /* via sinf/cosf/tanf */
    printf("sinf(0.5f) = %a\n", sinf(0.5f)); /* R5 */
    printf("cosf(0.5f) = %a\n", cosf(0.5f)); /* R5 */
    printf("tanf(0.5f) = %a\n", tanf(0.5f)); /* R5 */
    printf("sinf(1e5f) = %a\n", sinf(1e5f)); /* R5 */
    printf("cosf(1e5f) = %a\n", cosf(1e5f)); /* R5 */
    printf("sinf(1e8f) = %a\n", sinf(1e8f)); /* R4 */
    printf("cosf(1e8f) = %a\n", cosf(1e8f)); /* R5 */
}

/* erf/erfc/erff/erfcf — additional branches */
static void test_erf_s5(void)
{
    printf("=== test_erf_s5 ===\n"); /* R5 */
    /* erfd: |x| < 0.84375 */
    printf("erf(0.5) = %a\n", erf(0.5)); /* R4 */
    printf("erf(0.8) = %a\n", erf(0.8)); /* R5 */
    /* erfd: 0.84375 <= |x| < 1.25 */
    printf("erf(1.0) = %a\n", erf(1.0)); /* R4 */
    printf("erf(-1.0) = %a\n", erf(-1.0)); /* R4 */
    printf("erf(1.2) = %a\n", erf(1.2)); /* R5 */
    /* erfd: |x| >= 6 */
    printf("erf(6.0) = %a\n", erf(6.0)); /* R5 */
    printf("erf(-6.0) = %a\n", erf(-6.0)); /* R5 */
    printf("erf(10.0) = %a\n", erf(10.0)); /* R5 */
    /* erfd: 1/0.35 boundary */
    printf("erf(2.5) = %a\n", erf(2.5)); /* R5 */
    printf("erf(3.5) = %a\n", erf(3.5)); /* R5 */
    /* erfcd: positive x, small erfc */
    printf("erfc(1.25) = %a\n", erfc(1.25)); /* R5 */
    printf("erfc(2.0) = %a\n", erfc(2.0)); /* R4 */
    /* erfcd: large positive → ~0 */
    printf("erfc(28.0) = %a\n", erfc(28.0)); /* R5 */
    /* erfcd: large negative → ~2 */
    printf("erfc(-28.0) = %a\n", erfc(-28.0)); /* R5 */
    /* erff: |x| < 0.84375 */
    printf("erff(0.5f) = %a\n", erff(0.5f)); /* R5 */
    /* erff: |x| >= 4 */
    printf("erff(4.0f) = %a\n", erff(4.0f)); /* R5 */
    printf("erff(-4.0f) = %a\n", erff(-4.0f)); /* R5 */
    /* erff: 1/0.35 boundary */
    printf("erff(2.5f) = %a\n", erff(2.5f)); /* R5 */
    printf("erff(3.5f) = %a\n", erff(3.5f)); /* R5 */
    /* erfcf: 0.84375 <= |x| < 1.25 */
    printf("erfcf(1.0f) = %a\n", erfcf(1.0f)); /* R4 */
    printf("erfcf(-1.0f) = %a\n", erfcf(-1.0f)); /* R5 */
    /* erfcf: |x| < 1/0.35, negative x near -6 */
    printf("erfcf(-5.5f) = %a\n", erfcf(-5.5f)); /* R5 */
    /* erfcf: |x| >= 10.125, positive → ~0 */
    printf("erfcf(11.0f) = %a\n", erfcf(11.0f)); /* R5 */
    /* erfcf: |x| >= 10.125, negative → ~2 */
    printf("erfcf(-11.0f) = %a\n", erfcf(-11.0f)); /* R5 */
}

/* expm1d/expm1f — specific k paths */
static void test_expm1_s5(void)
{
    printf("=== test_expm1_s5 ===\n"); /* R5 */
    /* k = -1 path */
    printf("expm1(-0.6) = %a\n", expm1(-0.6)); /* R5 */
    printf("expm1(-0.9) = %a\n", expm1(-0.9)); /* R5 */
    /* k = 1 path */
    printf("expm1(0.8) = %a\n", expm1(0.8)); /* R4 */
    printf("expm1(0.95) = %a\n", expm1(0.95)); /* R5 */
    /* k = 1, x < -0.25 */
    printf("expm1(0.65) = %a\n", expm1(0.65)); /* R5 */
    /* k <= -2 (large negative) */
    printf("expm1(-2.0) = %a\n", expm1(-2.0)); /* R4 */
    printf("expm1(-5.0) = %a\n", expm1(-5.0)); /* R5 */
    /* k > 56 */
    printf("expm1(60.0) = %a\n", expm1(60.0)); /* R4 */
    printf("expm1(100.0) = %a\n", expm1(100.0)); /* R5 */
    /* k < 20 */
    printf("expm1(10.0) = %a\n", expm1(10.0)); /* R5 */
    printf("expm1(15.0) = %a\n", expm1(15.0)); /* R5 */
    /* k >= 20 */
    printf("expm1(20.0) = %a\n", expm1(20.0)); /* R5 */
    printf("expm1(30.0) = %a\n", expm1(30.0)); /* R5 */
    /* tiny */
    printf("expm1(1e-20) = %a\n", expm1(1e-20)); /* R5 */
    /* x < -56*ln2 */
    printf("expm1(-50.0) = %a\n", expm1(-50.0)); /* R5 */
    /* expm1f similar */
    printf("expm1f(-0.6f) = %a\n", expm1f(-0.6f)); /* R5 */
    printf("expm1f(0.8f) = %a\n", expm1f(0.8f)); /* R4 */
    printf("expm1f(-2.0f) = %a\n", expm1f(-2.0f)); /* R4 */
    printf("expm1f(60.0f) = %a\n", expm1f(60.0f)); /* R5 */
    printf("expm1f(10.0f) = %a\n", expm1f(10.0f)); /* R5 */
    printf("expm1f(25.0f) = %a\n", expm1f(25.0f)); /* R5 */
    printf("expm1f(1e-10f) = %a\n", expm1f(1e-10f)); /* R5 */
}

/* ctand/ctanf — d==0 branch and |d|<0.25 branch */
static void test_ctan_s5(void)
{
    printf("=== test_ctan_s5 ===\n"); /* R5 */
    /* ctand: |d|<0.25 path — near pole, use __ctans */
    double complex zd;
    /* re=pi/2 (near pole): cos(2*re)~0, cosh(2*im)~1, d~0 */
    zd = CMPLX(1.5707963267948966, 0.1);
    printf("ctan(pi/2+0.1i) = %a+%ai\n", creal(ctan(zd)), cimag(ctan(zd))); /* R5 */
    zd = CMPLX(1.5707963267948966, 0.05);
    printf("ctan(pi/2+0.05i) = %a+%ai\n", creal(ctan(zd)), cimag(ctan(zd))); /* R5 */
    /* ctand: large imaginary → d near 0 */
    zd = CMPLX(0.0, 50.0);
    printf("ctan(0+50i) = %a+%ai\n", creal(ctan(zd)), cimag(ctan(zd))); /* R5 */
    /* ctanf similar */
    float complex zf;
    zf = CMPLXF(1.5707963f, 0.1f);
    printf("ctanf(pi/2+0.1i) = %a+%ai\n", crealf(ctanf(zf)), cimagf(ctanf(zf))); /* R5 */
    zf = CMPLXF(1.5707963f, 0.05f);
    printf("ctanf(pi/2+0.05i) = %a+%ai\n", crealf(ctanf(zf)), cimagf(ctanf(zf))); /* R5 */
    zf = CMPLXF(0.0f, 50.0f);
    printf("ctanf(0+50i) = %a+%ai\n", crealf(ctanf(zf)), cimagf(ctanf(zf))); /* R5 */
    /* ctrigf/__ccoshsinhf: |x|>0.5, exp(x)=0 for very negative x */
    float c, s;
    __ccoshsinhf(-200.0f, &c, &s);
    printf("__ccoshsinhf(-200) c=%a s=%a\n", c, s); /* R4 */
    __ccoshsinhf(200.0f, &c, &s);
    printf("__ccoshsinhf(200) c=%a s=%a\n", c, s); /* R5 */
    /* __redupif: t<0 path */
    printf("__redupif(-3.14f) = %a\n", __redupif(-3.14f)); /* R4 */
    printf("__redupif(-6.28f) = %a\n", __redupif(-6.28f)); /* R5 */
    /* ctrigf complex sin/cos with large imaginary */
    float complex zfc = CMPLXF(1.0f, 10.0f);
    printf("csinf(1+10i) = %a+%ai\n", crealf(csinf(zfc)), cimagf(csinf(zfc))); /* R5 */
    printf("ccosf(1+10i) = %a+%ai\n", crealf(ccosf(zfc)), cimagf(ccosf(zfc))); /* R5 */
    /* large real in ctrigf: __rem_pio2f through ccoshsinhf */
    float complex zfb = CMPLXF(100.0f, 0.5f);
    printf("csinf(100+0.5i) = %a+%ai\n", crealf(csinf(zfb)), cimagf(csinf(zfb))); /* R5 */
    printf("ccosf(100+0.5i) = %a+%ai\n", crealf(ccosf(zfb)), cimagf(ccosf(zfb))); /* R5 */
}
