/* test_suite.c — function coverage tests for libmcs */

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <complex.h>

/* Bridge declarations for static functions */
extern int    bridge___rem_pio2_internal(double *x, double *y, int e0, int nx);
extern double bridge___tan(double x, double y, int iy);
extern double bridge___sin_pi(double x);
extern int    bridge___rem_pio2f_internal(float *x, float *y, int e0, int nx);
extern float  bridge___tanf(float x, float y, int iy);
extern double bridge___ctans(double _Complex z);
extern float  bridge___ctansf(float _Complex z);
extern float  bridge___sin_pif(float x);

/* Internal function declarations (non-static, from library internals) */
extern double __cos(double x, double y);
extern float  __cosf(float x, float y);
extern double __sin(double x, double y, int iy);
extern float  __sinf(float x, float y, int iy);
extern int32_t __rem_pio2(double x, double *y);
extern int32_t __rem_pio2f(float x, float *y);
extern double __lgamma(double x, int *signgamp);
extern float  __lgammaf(float x, int *signgamp);
extern int    __fpclassifyd(double x);
extern int    __fpclassifyf(float x);
extern int    __signbitd(double x);
extern int    __signbitf(float x);
extern void   __ccoshsinh(double x, double *c, double *s);
extern void   __ccoshsinhf(float x, float *c, float *s);
extern double __redupi(double x);
extern float  __redupif(float x);

/* ================================================================
 * Test functions grouped by category
 * ================================================================ */

static void test_trig_double(void)
{
    printf("=== Trigonometric (double) ===\n");
    printf("sin %a = %a\n",  0.5, sin(0.5));
    printf("cos %a = %a\n",  0.5, cos(0.5));
    printf("tan %a = %a\n",  0.5, tan(0.5));
    printf("asin %a = %a\n", 0.5, asin(0.5));
    printf("acos %a = %a\n", 0.5, acos(0.5));
    printf("atan %a = %a\n", 0.5, atan(0.5));
    printf("atan2 %a %a = %a\n", 1.0, 2.0, atan2(1.0, 2.0));
}

static void test_trig_float(void)
{
    printf("=== Trigonometric (float) ===\n");
    printf("sinf %a = %a\n",  (double)0.5f, (double)sinf(0.5f));
    printf("cosf %a = %a\n",  (double)0.5f, (double)cosf(0.5f));
    printf("tanf %a = %a\n",  (double)0.5f, (double)tanf(0.5f));
    printf("asinf %a = %a\n", (double)0.5f, (double)asinf(0.5f));
    printf("acosf %a = %a\n", (double)0.5f, (double)acosf(0.5f));
    printf("atanf %a = %a\n", (double)0.5f, (double)atanf(0.5f));
    printf("atan2f %a %a = %a\n", (double)1.0f, (double)2.0f, (double)atan2f(1.0f, 2.0f));
}

static void test_trig_long(void)
{
    printf("=== Trigonometric (long double) ===\n");
    printf("sinl %La = %La\n",  0.5L, sinl(0.5L));
    printf("cosl %La = %La\n",  0.5L, cosl(0.5L));
    printf("tanl %La = %La\n",  0.5L, tanl(0.5L));
    printf("asinl %La = %La\n", 0.5L, asinl(0.5L));
    printf("acosl %La = %La\n", 0.5L, acosl(0.5L));
    printf("atanl %La = %La\n", 0.5L, atanl(0.5L));
    printf("atan2l %La %La = %La\n", 1.0L, 2.0L, atan2l(1.0L, 2.0L));
}

static void test_hyp_double(void)
{
    printf("=== Hyperbolic (double) ===\n");
    printf("sinh %a = %a\n",  0.5, sinh(0.5));
    printf("cosh %a = %a\n",  0.5, cosh(0.5));
    printf("tanh %a = %a\n",  0.5, tanh(0.5));
    printf("asinh %a = %a\n", 0.5, asinh(0.5));
    printf("acosh %a = %a\n", 2.0, acosh(2.0));
    printf("atanh %a = %a\n", 0.5, atanh(0.5));
}

static void test_hyp_float(void)
{
    printf("=== Hyperbolic (float) ===\n");
    printf("sinhf %a = %a\n",  (double)0.5f, (double)sinhf(0.5f));
    printf("coshf %a = %a\n",  (double)0.5f, (double)coshf(0.5f));
    printf("tanhf %a = %a\n",  (double)0.5f, (double)tanhf(0.5f));
    printf("asinhf %a = %a\n", (double)0.5f, (double)asinhf(0.5f));
    printf("acoshf %a = %a\n", (double)2.0f, (double)acoshf(2.0f));
    printf("atanhf %a = %a\n", (double)0.5f, (double)atanhf(0.5f));
}

static void test_hyp_long(void)
{
    printf("=== Hyperbolic (long double) ===\n");
    printf("sinhl %La = %La\n",  0.5L, sinhl(0.5L));
    printf("coshl %La = %La\n",  0.5L, coshl(0.5L));
    printf("tanhl %La = %La\n",  0.5L, tanhl(0.5L));
    printf("asinhl %La = %La\n", 0.5L, asinhl(0.5L));
    printf("acoshl %La = %La\n", 2.0L, acoshl(2.0L));
    printf("atanhl %La = %La\n", 0.5L, atanhl(0.5L));
}

static void test_exp_log_double(void)
{
    printf("=== Exp/Log (double) ===\n");
    printf("exp %a = %a\n",    1.0, exp(1.0));
    printf("exp2 %a = %a\n",   3.0, exp2(3.0));
    printf("expm1 %a = %a\n",  0.5, expm1(0.5));
    printf("log %a = %a\n",    2.0, log(2.0));
    printf("log2 %a = %a\n",   8.0, log2(8.0));
    printf("log10 %a = %a\n",  100.0, log10(100.0));
    printf("log1p %a = %a\n",  0.5, log1p(0.5));
}

static void test_exp_log_float(void)
{
    printf("=== Exp/Log (float) ===\n");
    printf("expf %a = %a\n",    (double)1.0f, (double)expf(1.0f));
    printf("exp2f %a = %a\n",   (double)3.0f, (double)exp2f(3.0f));
    printf("expm1f %a = %a\n",  (double)0.5f, (double)expm1f(0.5f));
    printf("logf %a = %a\n",    (double)2.0f, (double)logf(2.0f));
    printf("log2f %a = %a\n",   (double)8.0f, (double)log2f(8.0f));
    printf("log10f %a = %a\n",  (double)100.0f, (double)log10f(100.0f));
    printf("log1pf %a = %a\n",  (double)0.5f, (double)log1pf(0.5f));
}

static void test_exp_log_long(void)
{
    printf("=== Exp/Log (long double) ===\n");
    printf("expl %La = %La\n",    1.0L, expl(1.0L));
    printf("exp2l %La = %La\n",   3.0L, exp2l(3.0L));
    printf("expm1l %La = %La\n",  0.5L, expm1l(0.5L));
    printf("logl %La = %La\n",    2.0L, logl(2.0L));
    printf("log2l %La = %La\n",   8.0L, log2l(8.0L));
    printf("log10l %La = %La\n",  100.0L, log10l(100.0L));
    printf("log1pl %La = %La\n",  0.5L, log1pl(0.5L));
}

static void test_pow_sqrt_double(void)
{
    printf("=== Power/Sqrt (double) ===\n");
    printf("pow %a %a = %a\n",  2.0, 3.0, pow(2.0, 3.0));
    printf("sqrt %a = %a\n",    2.0, sqrt(2.0));
    printf("cbrt %a = %a\n",    27.0, cbrt(27.0));
    printf("hypot %a %a = %a\n", 3.0, 4.0, hypot(3.0, 4.0));
}

static void test_pow_sqrt_float(void)
{
    printf("=== Power/Sqrt (float) ===\n");
    printf("powf %a %a = %a\n",  (double)2.0f, (double)3.0f, (double)powf(2.0f, 3.0f));
    printf("sqrtf %a = %a\n",    (double)2.0f, (double)sqrtf(2.0f));
    printf("cbrtf %a = %a\n",    (double)27.0f, (double)cbrtf(27.0f));
    printf("hypotf %a %a = %a\n", (double)3.0f, (double)4.0f, (double)hypotf(3.0f, 4.0f));
}

static void test_pow_sqrt_long(void)
{
    printf("=== Power/Sqrt (long double) ===\n");
    printf("powl %La %La = %La\n",  2.0L, 3.0L, powl(2.0L, 3.0L));
    printf("sqrtl %La = %La\n",     2.0L, sqrtl(2.0L));
    printf("cbrtl %La = %La\n",     27.0L, cbrtl(27.0L));
    printf("hypotl %La %La = %La\n", 3.0L, 4.0L, hypotl(3.0L, 4.0L));
}

static void test_err_gamma_double(void)
{
    printf("=== Error/Gamma (double) ===\n");
    printf("erf %a = %a\n",    0.5, erf(0.5));
    printf("erfc %a = %a\n",   0.5, erfc(0.5));
    printf("lgamma %a = %a\n", 2.5, lgamma(2.5));
    printf("lgamma %a = %a\n", -2.5, lgamma(-2.5));   /* triggers __sin_pi */
    printf("tgamma %a = %a\n", 3.5, tgamma(3.5));
}

static void test_err_gamma_float(void)
{
    printf("=== Error/Gamma (float) ===\n");
    printf("erff %a = %a\n",    (double)0.5f, (double)erff(0.5f));
    printf("erfcf %a = %a\n",   (double)0.5f, (double)erfcf(0.5f));
    printf("lgammaf %a = %a\n", (double)2.5f, (double)lgammaf(2.5f));
    printf("lgammaf %a = %a\n", (double)-2.5f, (double)lgammaf(-2.5f)); /* triggers __sin_pif */
    printf("tgammaf %a = %a\n", (double)3.5f, (double)tgammaf(3.5f));
}

static void test_err_gamma_long(void)
{
    printf("=== Error/Gamma (long double) ===\n");
    printf("erfl %La = %La\n",    0.5L, erfl(0.5L));
    printf("erfcl %La = %La\n",   0.5L, erfcl(0.5L));
    printf("lgammal %La = %La\n", 2.5L, lgammal(2.5L));
    printf("tgammal %La = %La\n", 3.5L, tgammal(3.5L));
}

static void test_bessel(void)
{
    printf("=== Bessel ===\n");
    printf("j0 %a = %a\n", 1.0, j0(1.0));
    printf("j1 %a = %a\n", 1.0, j1(1.0));
    printf("jn %d %a = %a\n", 2, 1.0, jn(2, 1.0));
    printf("y0 %a = %a\n", 1.0, y0(1.0));
    printf("y1 %a = %a\n", 1.0, y1(1.0));
    printf("yn %d %a = %a\n", 2, 1.0, yn(2, 1.0));
}

static void test_rounding_double(void)
{
    printf("=== Rounding (double) ===\n");
    printf("ceil %a = %a\n",      2.3, ceil(2.3));
    printf("floor %a = %a\n",     2.7, floor(2.7));
    printf("round %a = %a\n",     2.5, round(2.5));
    printf("trunc %a = %a\n",     2.9, trunc(2.9));
    printf("rint %a = %a\n",      2.5, rint(2.5));
    printf("nearbyint %a = %a\n", 2.5, nearbyint(2.5));
    printf("lrint %a = %ld\n",    2.5, lrint(2.5));
    printf("llrint %a = %lld\n",  2.5, llrint(2.5));
    printf("lround %a = %ld\n",   2.5, lround(2.5));
    printf("llround %a = %lld\n", 2.5, llround(2.5));
}

static void test_rounding_float(void)
{
    printf("=== Rounding (float) ===\n");
    printf("ceilf %a = %a\n",      (double)2.3f, (double)ceilf(2.3f));
    printf("floorf %a = %a\n",     (double)2.7f, (double)floorf(2.7f));
    printf("roundf %a = %a\n",     (double)2.5f, (double)roundf(2.5f));
    printf("truncf %a = %a\n",     (double)2.9f, (double)truncf(2.9f));
    printf("rintf %a = %a\n",      (double)2.5f, (double)rintf(2.5f));
    printf("nearbyintf %a = %a\n", (double)2.5f, (double)nearbyintf(2.5f));
    printf("lrintf %a = %ld\n",    (double)2.5f, lrintf(2.5f));
    printf("llrintf %a = %lld\n",  (double)2.5f, llrintf(2.5f));
    printf("lroundf %a = %ld\n",   (double)2.5f, lroundf(2.5f));
    printf("llroundf %a = %lld\n", (double)2.5f, llroundf(2.5f));
}

static void test_rounding_long(void)
{
    printf("=== Rounding (long double) ===\n");
    printf("ceill %La = %La\n",      2.3L, ceill(2.3L));
    printf("floorl %La = %La\n",     2.7L, floorl(2.7L));
    printf("roundl %La = %La\n",     2.5L, roundl(2.5L));
    printf("truncl %La = %La\n",     2.9L, truncl(2.9L));
    printf("rintl %La = %La\n",      2.5L, rintl(2.5L));
    printf("nearbyintl %La = %La\n", 2.5L, nearbyintl(2.5L));
    printf("lrintl %La = %ld\n",     2.5L, lrintl(2.5L));
    printf("llrintl %La = %lld\n",   2.5L, llrintl(2.5L));
    printf("lroundl %La = %ld\n",    2.5L, lroundl(2.5L));
    printf("llroundl %La = %lld\n",  2.5L, llroundl(2.5L));
}

static void test_fp_manip_double(void)
{
    printf("=== FP manipulation (double) ===\n");
    printf("fabs %a = %a\n",       -2.5, fabs(-2.5));
    printf("copysign %a %a = %a\n", 2.5, -1.0, copysign(2.5, -1.0));
    printf("fdim %a %a = %a\n",    5.0, 3.0, fdim(5.0, 3.0));
    printf("fmax %a %a = %a\n",    2.0, 3.0, fmax(2.0, 3.0));
    printf("fmin %a %a = %a\n",    2.0, 3.0, fmin(2.0, 3.0));
    printf("fmod %a %a = %a\n",    5.5, 2.0, fmod(5.5, 2.0));
    printf("fma %a %a %a = %a\n",  2.0, 3.0, 4.0, fma(2.0, 3.0, 4.0));

    int exp_val;
    double frac = frexp(6.0, &exp_val);
    printf("frexp %a = %a exp=%d\n", 6.0, frac, exp_val);

    printf("ldexp %a %d = %a\n", 1.5, 3, ldexp(1.5, 3));
    printf("logb %a = %a\n", 8.0, logb(8.0));
    printf("ilogb %a = %d\n", 8.0, ilogb(8.0));
    printf("scalbn %a %d = %a\n", 1.5, 3, scalbn(1.5, 3));
    printf("scalbln %a %ld = %a\n", 1.5, 3L, scalbln(1.5, 3L));

    double int_part;
    double frac2 = modf(3.75, &int_part);
    printf("modf %a = frac=%a int=%a\n", 3.75, frac2, int_part);

    printf("nextafter %a %a = %a\n", 1.0, 2.0, nextafter(1.0, 2.0));
    printf("nexttoward %a %La = %a\n", 1.0, 2.0L, nexttoward(1.0, 2.0L));

    int quot;
    double rem = remquo(10.0, 3.0, &quot);
    printf("remainder %a %a = %a\n", 10.0, 3.0, remainder(10.0, 3.0));
    printf("remquo %a %a = %a quot=%d\n", 10.0, 3.0, rem, quot);

    printf("nan = %a\n", nan(""));
}

static void test_fp_manip_float(void)
{
    printf("=== FP manipulation (float) ===\n");
    printf("fabsf %a = %a\n",       (double)-2.5f, (double)fabsf(-2.5f));
    printf("copysignf %a %a = %a\n", (double)2.5f, (double)-1.0f, (double)copysignf(2.5f, -1.0f));
    printf("fdimf %a %a = %a\n",    (double)5.0f, (double)3.0f, (double)fdimf(5.0f, 3.0f));
    printf("fmaxf %a %a = %a\n",    (double)2.0f, (double)3.0f, (double)fmaxf(2.0f, 3.0f));
    printf("fminf %a %a = %a\n",    (double)2.0f, (double)3.0f, (double)fminf(2.0f, 3.0f));
    printf("fmodf %a %a = %a\n",    (double)5.5f, (double)2.0f, (double)fmodf(5.5f, 2.0f));
    printf("fmaf %a %a %a = %a\n",  (double)2.0f, (double)3.0f, (double)4.0f, (double)fmaf(2.0f, 3.0f, 4.0f));

    int exp_val;
    float frac = frexpf(6.0f, &exp_val);
    printf("frexpf %a = %a exp=%d\n", (double)6.0f, (double)frac, exp_val);

    printf("ldexpf %a %d = %a\n", (double)1.5f, 3, (double)ldexpf(1.5f, 3));
    printf("logbf %a = %a\n", (double)8.0f, (double)logbf(8.0f));
    printf("ilogbf %a = %d\n", (double)8.0f, ilogbf(8.0f));
    printf("scalbnf %a %d = %a\n", (double)1.5f, 3, (double)scalbnf(1.5f, 3));
    printf("scalblnf %a %ld = %a\n", (double)1.5f, 3L, (double)scalblnf(1.5f, 3L));

    float int_part;
    float frac2 = modff(3.75f, &int_part);
    printf("modff %a = frac=%a int=%a\n", (double)3.75f, (double)frac2, (double)int_part);

    printf("nextafterf %a %a = %a\n", (double)1.0f, (double)2.0f, (double)nextafterf(1.0f, 2.0f));
    printf("nexttowardf %a %La = %a\n", (double)1.0f, 2.0L, (double)nexttowardf(1.0f, 2.0L));

    int quot;
    float rem = remquof(10.0f, 3.0f, &quot);
    printf("remainderf %a %a = %a\n", (double)10.0f, (double)3.0f, (double)remainderf(10.0f, 3.0f));
    printf("remquof %a %a = %a quot=%d\n", (double)10.0f, (double)3.0f, (double)rem, quot);

    printf("nanf = %a\n", (double)nanf(""));
}

static void test_fp_manip_long(void)
{
    printf("=== FP manipulation (long double) ===\n");
    printf("fabsl %La = %La\n",       -2.5L, fabsl(-2.5L));
    printf("copysignl %La %La = %La\n", 2.5L, -1.0L, copysignl(2.5L, -1.0L));
    printf("fdiml %La %La = %La\n",    5.0L, 3.0L, fdiml(5.0L, 3.0L));
    printf("fmaxl %La %La = %La\n",    2.0L, 3.0L, fmaxl(2.0L, 3.0L));
    printf("fminl %La %La = %La\n",    2.0L, 3.0L, fminl(2.0L, 3.0L));
    printf("fmodl %La %La = %La\n",    5.5L, 2.0L, fmodl(5.5L, 2.0L));
    printf("fmal %La %La %La = %La\n", 2.0L, 3.0L, 4.0L, fmal(2.0L, 3.0L, 4.0L));

    int exp_val;
    long double frac = frexpl(6.0L, &exp_val);
    printf("frexpl %La = %La exp=%d\n", 6.0L, frac, exp_val);

    printf("ldexpl %La %d = %La\n", 1.5L, 3, ldexpl(1.5L, 3));
    printf("logbl %La = %La\n", 8.0L, logbl(8.0L));
    printf("ilogbl %La = %d\n", 8.0L, ilogbl(8.0L));
    printf("scalbnl %La %d = %La\n", 1.5L, 3, scalbnl(1.5L, 3));
    printf("scalblnl %La %ld = %La\n", 1.5L, 3L, scalblnl(1.5L, 3L));

    long double int_part;
    long double frac2 = modfl(3.75L, &int_part);
    printf("modfl %La = frac=%La int=%La\n", 3.75L, frac2, int_part);

    printf("nextafterl %La %La = %La\n", 1.0L, 2.0L, nextafterl(1.0L, 2.0L));
    printf("nexttowardl %La %La = %La\n", 1.0L, 2.0L, nexttowardl(1.0L, 2.0L));

    int quot;
    long double rem = remquol(10.0L, 3.0L, &quot);
    printf("remainderl %La %La = %La\n", 10.0L, 3.0L, remainderl(10.0L, 3.0L));
    printf("remquol %La %La = %La quot=%d\n", 10.0L, 3.0L, rem, quot);

    printf("nanl = %La\n", nanl(""));
}

/* ================================================================
 * Complex functions
 * ================================================================ */

static void test_complex_double(void)
{
    printf("=== Complex (double) ===\n");
    double _Complex z1 = CMPLX(1.0, 2.0);
    double _Complex z2 = CMPLX(0.5, 0.5);

    printf("creal %a+%ai\n", creal(z1), cimag(z1));
    printf("cimag %a+%ai = %a\n", creal(z1), cimag(z1), cimag(z1));
    printf("cabs %a+%ai = %a\n", creal(z1), cimag(z1), cabs(z1));
    printf("carg %a+%ai = %a\n", creal(z1), cimag(z1), carg(z1));

    double _Complex r;
    r = conj(z1);
    printf("conj %a+%ai = %a+%ai\n", creal(z1), cimag(z1), creal(r), cimag(r));
    r = cproj(z1);
    printf("cproj %a+%ai = %a+%ai\n", creal(z1), cimag(z1), creal(r), cimag(r));

    r = csin(z2);
    printf("csin %a+%ai = %a+%ai\n", creal(z2), cimag(z2), creal(r), cimag(r));
    r = ccos(z2);
    printf("ccos %a+%ai = %a+%ai\n", creal(z2), cimag(z2), creal(r), cimag(r));
    r = ctan(z2);
    printf("ctan %a+%ai = %a+%ai\n", creal(z2), cimag(z2), creal(r), cimag(r));
    r = casin(z2);
    printf("casin %a+%ai = %a+%ai\n", creal(z2), cimag(z2), creal(r), cimag(r));
    r = cacos(z2);
    printf("cacos %a+%ai = %a+%ai\n", creal(z2), cimag(z2), creal(r), cimag(r));
    r = catan(z2);
    printf("catan %a+%ai = %a+%ai\n", creal(z2), cimag(z2), creal(r), cimag(r));

    r = csinh(z2);
    printf("csinh %a+%ai = %a+%ai\n", creal(z2), cimag(z2), creal(r), cimag(r));
    r = ccosh(z2);
    printf("ccosh %a+%ai = %a+%ai\n", creal(z2), cimag(z2), creal(r), cimag(r));
    r = ctanh(z2);
    printf("ctanh %a+%ai = %a+%ai\n", creal(z2), cimag(z2), creal(r), cimag(r));
    r = casinh(z2);
    printf("casinh %a+%ai = %a+%ai\n", creal(z2), cimag(z2), creal(r), cimag(r));
    r = cacosh(z2);
    printf("cacosh %a+%ai = %a+%ai\n", creal(z2), cimag(z2), creal(r), cimag(r));
    r = catanh(z2);
    printf("catanh %a+%ai = %a+%ai\n", creal(z2), cimag(z2), creal(r), cimag(r));

    r = cexp(z2);
    printf("cexp %a+%ai = %a+%ai\n", creal(z2), cimag(z2), creal(r), cimag(r));
    r = clog(z2);
    printf("clog %a+%ai = %a+%ai\n", creal(z2), cimag(z2), creal(r), cimag(r));
    r = csqrt(z2);
    printf("csqrt %a+%ai = %a+%ai\n", creal(z2), cimag(z2), creal(r), cimag(r));
    r = cpow(z1, z2);
    printf("cpow %a+%ai = %a+%ai\n", creal(z1), cimag(z1), creal(r), cimag(r));
}

static void test_complex_float(void)
{
    printf("=== Complex (float) ===\n");
    float _Complex z1 = CMPLXF(1.0f, 2.0f);
    float _Complex z2 = CMPLXF(0.5f, 0.5f);

    printf("crealf %a+%ai\n", (double)crealf(z1), (double)cimagf(z1));
    printf("cimagf %a+%ai = %a\n", (double)crealf(z1), (double)cimagf(z1), (double)cimagf(z1));
    printf("cabsf %a+%ai = %a\n", (double)crealf(z1), (double)cimagf(z1), (double)cabsf(z1));
    printf("cargf %a+%ai = %a\n", (double)crealf(z1), (double)cimagf(z1), (double)cargf(z1));

    float _Complex r;
    r = conjf(z1);
    printf("conjf %a+%ai = %a+%ai\n", (double)crealf(z1), (double)cimagf(z1), (double)crealf(r), (double)cimagf(r));
    r = cprojf(z1);
    printf("cprojf %a+%ai = %a+%ai\n", (double)crealf(z1), (double)cimagf(z1), (double)crealf(r), (double)cimagf(r));

    r = csinf(z2);
    printf("csinf %a+%ai = %a+%ai\n", (double)crealf(z2), (double)cimagf(z2), (double)crealf(r), (double)cimagf(r));
    r = ccosf(z2);
    printf("ccosf %a+%ai = %a+%ai\n", (double)crealf(z2), (double)cimagf(z2), (double)crealf(r), (double)cimagf(r));
    r = ctanf(z2);
    printf("ctanf %a+%ai = %a+%ai\n", (double)crealf(z2), (double)cimagf(z2), (double)crealf(r), (double)cimagf(r));
    r = casinf(z2);
    printf("casinf %a+%ai = %a+%ai\n", (double)crealf(z2), (double)cimagf(z2), (double)crealf(r), (double)cimagf(r));
    r = cacosf(z2);
    printf("cacosf %a+%ai = %a+%ai\n", (double)crealf(z2), (double)cimagf(z2), (double)crealf(r), (double)cimagf(r));
    r = catanf(z2);
    printf("catanf %a+%ai = %a+%ai\n", (double)crealf(z2), (double)cimagf(z2), (double)crealf(r), (double)cimagf(r));

    r = csinhf(z2);
    printf("csinhf %a+%ai = %a+%ai\n", (double)crealf(z2), (double)cimagf(z2), (double)crealf(r), (double)cimagf(r));
    r = ccoshf(z2);
    printf("ccoshf %a+%ai = %a+%ai\n", (double)crealf(z2), (double)cimagf(z2), (double)crealf(r), (double)cimagf(r));
    r = ctanhf(z2);
    printf("ctanhf %a+%ai = %a+%ai\n", (double)crealf(z2), (double)cimagf(z2), (double)crealf(r), (double)cimagf(r));
    r = casinhf(z2);
    printf("casinhf %a+%ai = %a+%ai\n", (double)crealf(z2), (double)cimagf(z2), (double)crealf(r), (double)cimagf(r));
    r = cacoshf(z2);
    printf("cacoshf %a+%ai = %a+%ai\n", (double)crealf(z2), (double)cimagf(z2), (double)crealf(r), (double)cimagf(r));
    r = catanhf(z2);
    printf("catanhf %a+%ai = %a+%ai\n", (double)crealf(z2), (double)cimagf(z2), (double)crealf(r), (double)cimagf(r));

    r = cexpf(z2);
    printf("cexpf %a+%ai = %a+%ai\n", (double)crealf(z2), (double)cimagf(z2), (double)crealf(r), (double)cimagf(r));
    r = clogf(z2);
    printf("clogf %a+%ai = %a+%ai\n", (double)crealf(z2), (double)cimagf(z2), (double)crealf(r), (double)cimagf(r));
    r = csqrtf(z2);
    printf("csqrtf %a+%ai = %a+%ai\n", (double)crealf(z2), (double)cimagf(z2), (double)crealf(r), (double)cimagf(r));
    r = cpowf(z1, z2);
    printf("cpowf %a+%ai = %a+%ai\n", (double)crealf(z1), (double)cimagf(z1), (double)crealf(r), (double)cimagf(r));
}

static void test_complex_long(void)
{
    printf("=== Complex (long double) ===\n");
    long double _Complex z1 = CMPLXL(1.0L, 2.0L);
    long double _Complex z2 = CMPLXL(0.5L, 0.5L);

    long double _Complex r;
    printf("creall %La+%Lai\n", creall(z1), cimagl(z1));
    printf("cimagl = %La\n", cimagl(z1));
    printf("cabsl = %La\n", cabsl(z1));
    printf("cargl = %La\n", cargl(z1));

    r = conjl(z1);
    printf("conjl = %La+%Lai\n", creall(r), cimagl(r));
    r = cprojl(z1);
    printf("cprojl = %La+%Lai\n", creall(r), cimagl(r));

    r = csinl(z2);
    printf("csinl = %La+%Lai\n", creall(r), cimagl(r));
    r = ccosl(z2);
    printf("ccosl = %La+%Lai\n", creall(r), cimagl(r));
    r = ctanl(z2);
    printf("ctanl = %La+%Lai\n", creall(r), cimagl(r));
    r = casinl(z2);
    printf("casinl = %La+%Lai\n", creall(r), cimagl(r));
    r = cacosl(z2);
    printf("cacosl = %La+%Lai\n", creall(r), cimagl(r));
    r = catanl(z2);
    printf("catanl = %La+%Lai\n", creall(r), cimagl(r));

    r = csinhl(z2);
    printf("csinhl = %La+%Lai\n", creall(r), cimagl(r));
    r = ccoshl(z2);
    printf("ccoshl = %La+%Lai\n", creall(r), cimagl(r));
    r = ctanhl(z2);
    printf("ctanhl = %La+%Lai\n", creall(r), cimagl(r));
    r = casinhl(z2);
    printf("casinhl = %La+%Lai\n", creall(r), cimagl(r));
    r = cacoshl(z2);
    printf("cacoshl = %La+%Lai\n", creall(r), cimagl(r));
    r = catanhl(z2);
    printf("catanhl = %La+%Lai\n", creall(r), cimagl(r));

    r = cexpl(z2);
    printf("cexpl = %La+%Lai\n", creall(r), cimagl(r));
    r = clogl(z2);
    printf("clogl = %La+%Lai\n", creall(r), cimagl(r));
    r = csqrtl(z2);
    printf("csqrtl = %La+%Lai\n", creall(r), cimagl(r));
    r = cpowl(z1, z2);
    printf("cpowl = %La+%Lai\n", creall(r), cimagl(r));
}

/* ================================================================
 * Internal / bridge functions
 * ================================================================ */

static void test_internal_trig(void)
{
    printf("=== Internal trig ===\n");

    /* __cos, __sin: kernel functions for reduced arguments */
    printf("__cos %a %a = %a\n", 0.25, 0.0, __cos(0.25, 0.0));
    printf("__sin %a %a %d = %a\n", 0.25, 0.0, 1, __sin(0.25, 0.0, 1));
    printf("__cosf %a %a = %a\n", (double)0.25f, 0.0, (double)__cosf(0.25f, 0.0f));
    printf("__sinf %a %a %d = %a\n", (double)0.25f, 0.0, 1, (double)__sinf(0.25f, 0.0f, 1));

    /* __rem_pio2: argument reduction */
    double y[2];
    int32_t n = __rem_pio2(3.0, y);
    printf("__rem_pio2 %a = n=%d y=%a %a\n", 3.0, n, y[0], y[1]);

    float yf[2];
    int32_t nf = __rem_pio2f(3.0f, yf);
    printf("__rem_pio2f %a = n=%d y=%a %a\n", (double)3.0f, nf, (double)yf[0], (double)yf[1]);

    /* __redupi, __redupif: reduce to [-pi, pi] */
    printf("__redupi %a = %a\n", 7.0, __redupi(7.0));
    printf("__redupif %a = %a\n", (double)7.0f, (double)__redupif(7.0f));
}

static void test_internal_gamma(void)
{
    printf("=== Internal gamma ===\n");

    int signgam_d;
    double lg = __lgamma(2.5, &signgam_d);
    printf("__lgamma %a = %a sign=%d\n", 2.5, lg, signgam_d);

    int signgam_f;
    float lgf = __lgammaf(2.5f, &signgam_f);
    printf("__lgammaf %a = %a sign=%d\n", (double)2.5f, (double)lgf, signgam_f);
}

static void test_internal_classify(void)
{
    printf("=== Internal classify ===\n");
    printf("__fpclassifyd %a = %d\n", 1.0, __fpclassifyd(1.0));
    printf("__fpclassifyd %a = %d\n", 0.0, __fpclassifyd(0.0));
    printf("__fpclassifyf %a = %d\n", (double)1.0f, __fpclassifyf(1.0f));
    printf("__fpclassifyf %a = %d\n", 0.0, __fpclassifyf(0.0f));
    printf("__signbitd %a = %d\n", -1.0, __signbitd(-1.0));
    printf("__signbitd %a = %d\n", 1.0, __signbitd(1.0));
    printf("__signbitf %a = %d\n", (double)-1.0f, __signbitf(-1.0f));
    printf("__signbitf %a = %d\n", (double)1.0f, __signbitf(1.0f));
}

static void test_internal_complex(void)
{
    printf("=== Internal complex ===\n");

    /* __ccoshsinh */
    double c_d, s_d;
    __ccoshsinh(1.0, &c_d, &s_d);
    printf("__ccoshsinh %a = c=%a s=%a\n", 1.0, c_d, s_d);

    float c_f, s_f;
    __ccoshsinhf(1.0f, &c_f, &s_f);
    printf("__ccoshsinhf %a = c=%a s=%a\n", (double)1.0f, (double)c_f, (double)s_f);
}

static void test_bridge_static(void)
{
    printf("=== Bridge: static functions ===\n");

    /* bridge___tan: kernel tangent for [-pi/4, pi/4] */
    printf("bridge___tan %a %a %d = %a\n", 0.25, 0.0, 1, bridge___tan(0.25, 0.0, 1));
    printf("bridge___tan %a %a %d = %a\n", 0.25, 0.0, -1, bridge___tan(0.25, 0.0, -1));

    /* bridge___tanf */
    printf("bridge___tanf %a %a %d = %a\n", (double)0.25f, 0.0, 1, (double)bridge___tanf(0.25f, 0.0f, 1));

    /* bridge___rem_pio2_internal: triggered by large arguments */
    {
        double x_arr[3] = {1.0, 0.0, 0.0};
        double y_arr[2];
        int r = bridge___rem_pio2_internal(x_arr, y_arr, 3, 1);
        printf("bridge___rem_pio2_internal = n=%d y=%a %a\n", r, y_arr[0], y_arr[1]);
    }

    /* bridge___rem_pio2f_internal */
    {
        float x_arr[3] = {1.0f, 0.0f, 0.0f};
        float y_arr[2];
        int r = bridge___rem_pio2f_internal(x_arr, y_arr, 3, 1);
        printf("bridge___rem_pio2f_internal = n=%d y=%a %a\n", r, (double)y_arr[0], (double)y_arr[1]);
    }

    /* bridge___sin_pi: sin(pi*x), used by lgamma for negative args */
    printf("bridge___sin_pi %a = %a\n", 0.5, bridge___sin_pi(0.5));
    printf("bridge___sin_pi %a = %a\n", 0.25, bridge___sin_pi(0.25));

    /* bridge___ctans: Taylor series for cosh(2y)-cos(2x), small args */
    {
        double _Complex z = CMPLX(0.01, 0.01);
        printf("bridge___ctans %a+%ai = %a\n", creal(z), cimag(z), bridge___ctans(z));
    }

    /* bridge___ctansf */
    {
        float _Complex z = CMPLXF(0.01f, 0.01f);
        printf("bridge___ctansf %a+%ai = %a\n", (double)crealf(z), (double)cimagf(z), (double)bridge___ctansf(z));
    }

    /* bridge___sin_pif: sin(pi*x) for float, used by lgamma for negative args */
    printf("bridge___sin_pif %a = %a\n", (double)0.5f, (double)bridge___sin_pif(0.5f));
    printf("bridge___sin_pif %a = %a\n", (double)0.25f, (double)bridge___sin_pif(0.25f));
}

/* ================================================================
 * Additional coverage: large arguments to trigger __rem_pio2*_internal
 * ================================================================ */

static void test_large_arg_trig(void)
{
    printf("=== Large-arg trig (triggers internal reduction) ===\n");
    /* Large args ensure __rem_pio2_internal / __rem_pio2f_internal are called */
    printf("sin %a = %a\n", 1.0e20, sin(1.0e20));
    printf("cos %a = %a\n", 1.0e20, cos(1.0e20));
    printf("sinf %a = %a\n", (double)1.0e10f, (double)sinf(1.0e10f));
    printf("cosf %a = %a\n", (double)1.0e10f, (double)cosf(1.0e10f));

    /* Small complex args to trigger __ctans/__ctansf Taylor series path */
    {
        double _Complex z = CMPLX(0.001, 0.001);
        double _Complex r = ctan(z);
        printf("ctan_small %a+%ai = %a+%ai\n", creal(z), cimag(z), creal(r), cimag(r));
    }
    {
        float _Complex z = CMPLXF(0.001f, 0.001f);
        float _Complex r = ctanf(z);
        printf("ctanf_small %a+%ai = %a+%ai\n", (double)crealf(z), (double)cimagf(z), (double)crealf(r), (double)cimagf(r));
    }
}

/* ================================================================
 * Additional coverage: exercise static functions via public API
 * ================================================================ */

static void test_static_via_public_api(void)
{
    printf("=== Static functions via public API ===\n");

    /* __tan / __tanf: called by tan()/tanf() for |x| < pi/4 */
    /* Small args (no reduction needed, direct __tan/__tanf call) */
    printf("tan %a = %a\n", 0.1, tan(0.1));
    printf("tan %a = %a\n", 0.7, tan(0.7));
    printf("tan %a = %a\n", -0.3, tan(-0.3));
    printf("tanf %a = %a\n", (double)0.1f, (double)tanf(0.1f));
    printf("tanf %a = %a\n", (double)0.7f, (double)tanf(0.7f));
    printf("tanf %a = %a\n", (double)-0.3f, (double)tanf(-0.3f));

    /* __rem_pio2_internal / __rem_pio2f_internal: triggered by very large args */
    printf("sin %a = %a\n", 1.0e30, sin(1.0e30));
    printf("cos %a = %a\n", 1.0e30, cos(1.0e30));
    printf("tan %a = %a\n", 1.0e15, tan(1.0e15));
    printf("sinf %a = %a\n", (double)1.0e15f, (double)sinf(1.0e15f));
    printf("cosf %a = %a\n", (double)1.0e15f, (double)cosf(1.0e15f));
    printf("tanf %a = %a\n", (double)1.0e15f, (double)tanf(1.0e15f));
    /* Medium large args */
    printf("sin %a = %a\n", 1.0e8, sin(1.0e8));
    printf("cos %a = %a\n", 1.0e8, cos(1.0e8));
    printf("sinf %a = %a\n", (double)1.0e6f, (double)sinf(1.0e6f));
    printf("cosf %a = %a\n", (double)1.0e6f, (double)cosf(1.0e6f));

    /* __sin_pi / __sin_pif: called by lgamma/tgamma for negative args */
    printf("lgamma %a = %a\n", -0.5, lgamma(-0.5));
    printf("lgamma %a = %a\n", -1.5, lgamma(-1.5));
    printf("lgamma %a = %a\n", -2.5, lgamma(-2.5));
    printf("lgamma %a = %a\n", -3.7, lgamma(-3.7));
    printf("lgammaf %a = %a\n", (double)-0.5f, (double)lgammaf(-0.5f));
    printf("lgammaf %a = %a\n", (double)-1.5f, (double)lgammaf(-1.5f));
    printf("lgammaf %a = %a\n", (double)-2.5f, (double)lgammaf(-2.5f));
    printf("lgammaf %a = %a\n", (double)-3.7f, (double)lgammaf(-3.7f));
    printf("tgamma %a = %a\n", -0.5, tgamma(-0.5));
    printf("tgamma %a = %a\n", -1.5, tgamma(-1.5));
    printf("tgammaf %a = %a\n", (double)-0.5f, (double)tgammaf(-0.5f));
    printf("tgammaf %a = %a\n", (double)-1.5f, (double)tgammaf(-1.5f));

    /* __ctans / __ctansf: called by ctan/ctanf when cos(2x)+cosh(2y) < 0.25 */
    /* Need z where cos(2*re)+cosh(2*im) is small, i.e. re near pi/2, im near 0 */
    {
        double _Complex z1 = CMPLX(0.785, 0.001);  /* re ~ pi/4 */
        double _Complex r1 = ctan(z1);
        printf("ctan %a+%ai = %a+%ai\n", creal(z1), cimag(z1), creal(r1), cimag(r1));
    }
    {
        double _Complex z2 = CMPLX(0.0001, 0.0001);
        double _Complex r2 = ctan(z2);
        printf("ctan %a+%ai = %a+%ai\n", creal(z2), cimag(z2), creal(r2), cimag(r2));
    }
    {
        double _Complex z3 = CMPLX(0.005, 0.005);
        double _Complex r3 = ctan(z3);
        printf("ctan %a+%ai = %a+%ai\n", creal(z3), cimag(z3), creal(r3), cimag(r3));
    }
    {
        float _Complex z1 = CMPLXF(0.785f, 0.001f);
        float _Complex r1 = ctanf(z1);
        printf("ctanf %a+%ai = %a+%ai\n", (double)crealf(z1), (double)cimagf(z1), (double)crealf(r1), (double)cimagf(r1));
    }
    {
        float _Complex z2 = CMPLXF(0.0001f, 0.0001f);
        float _Complex r2 = ctanf(z2);
        printf("ctanf %a+%ai = %a+%ai\n", (double)crealf(z2), (double)cimagf(z2), (double)crealf(r2), (double)cimagf(r2));
    }
    {
        float _Complex z3 = CMPLXF(0.005f, 0.005f);
        float _Complex r3 = ctanf(z3);
        printf("ctanf %a+%ai = %a+%ai\n", (double)crealf(z3), (double)cimagf(z3), (double)crealf(r3), (double)cimagf(r3));
    }
}

/* ================================================================
 * Additional bridge tests: more code paths within static functions
 * ================================================================ */

static void test_bridge_static_extra(void)
{
    printf("=== Bridge: static functions (extra paths) ===\n");

    /* __tan: |x| >= 0.6744 path */
    printf("bridge___tan %a %a %d = %a\n", 0.7, 0.0, 1, bridge___tan(0.7, 0.0, 1));
    printf("bridge___tan %a %a %d = %a\n", -0.7, 0.0, 1, bridge___tan(-0.7, 0.0, 1));
    printf("bridge___tan %a %a %d = %a\n", 0.7, 0.0, -1, bridge___tan(0.7, 0.0, -1));
    /* __tan: small x path (iy==1 and iy==-1) */
    printf("bridge___tan %a %a %d = %a\n", 0.1, 0.0, 1, bridge___tan(0.1, 0.0, 1));
    printf("bridge___tan %a %a %d = %a\n", 0.1, 0.0, -1, bridge___tan(0.1, 0.0, -1));

    /* __tanf: |x| >= 0.6744 path */
    printf("bridge___tanf %a %a %d = %a\n", (double)0.7f, 0.0, 1, (double)bridge___tanf(0.7f, 0.0f, 1));
    printf("bridge___tanf %a %a %d = %a\n", (double)-0.7f, 0.0, 1, (double)bridge___tanf(-0.7f, 0.0f, 1));
    printf("bridge___tanf %a %a %d = %a\n", (double)0.7f, 0.0, -1, (double)bridge___tanf(0.7f, 0.0f, -1));
    printf("bridge___tanf %a %a %d = %a\n", (double)0.1f, 0.0, -1, (double)bridge___tanf(0.1f, 0.0f, -1));

    /* __rem_pio2_internal: larger e0 values for more ipio2 terms */
    {
        double x_arr[3] = {1.5, 0.5, 0.0};
        double y_arr[2];
        int r = bridge___rem_pio2_internal(x_arr, y_arr, 10, 2);
        printf("bridge___rem_pio2_internal e0=10 nx=2 = n=%d y=%a %a\n", r, y_arr[0], y_arr[1]);
    }
    {
        double x_arr[3] = {1.0, 0.5, 0.25};
        double y_arr[2];
        int r = bridge___rem_pio2_internal(x_arr, y_arr, 50, 3);
        printf("bridge___rem_pio2_internal e0=50 nx=3 = n=%d y=%a %a\n", r, y_arr[0], y_arr[1]);
    }

    /* __rem_pio2f_internal: larger e0 values */
    {
        float x_arr[3] = {1.5f, 0.5f, 0.0f};
        float y_arr[2];
        int r = bridge___rem_pio2f_internal(x_arr, y_arr, 10, 2);
        printf("bridge___rem_pio2f_internal e0=10 nx=2 = n=%d y=%a %a\n", r, (double)y_arr[0], (double)y_arr[1]);
    }
    {
        float x_arr[3] = {1.0f, 0.5f, 0.25f};
        float y_arr[2];
        int r = bridge___rem_pio2f_internal(x_arr, y_arr, 30, 3);
        printf("bridge___rem_pio2f_internal e0=30 nx=3 = n=%d y=%a %a\n", r, (double)y_arr[0], (double)y_arr[1]);
    }

    /* __sin_pi: different switch cases (n=0,1,2,3,4,5,6,default) */
    /* x < 0.25: direct path */
    printf("bridge___sin_pi %a = %a\n", 0.1, bridge___sin_pi(0.1));
    /* y*4 in different ranges for different switch cases */
    printf("bridge___sin_pi %a = %a\n", 0.3, bridge___sin_pi(0.3));   /* n=1 */
    printf("bridge___sin_pi %a = %a\n", 0.75, bridge___sin_pi(0.75)); /* n=3 */
    printf("bridge___sin_pi %a = %a\n", 1.4, bridge___sin_pi(1.4));   /* n=5 */
    printf("bridge___sin_pi %a = %a\n", 1.8, bridge___sin_pi(1.8));   /* n=7/default */
    /* integer arg: z==y path */
    printf("bridge___sin_pi %a = %a\n", 2.0, bridge___sin_pi(2.0));
    printf("bridge___sin_pi %a = %a\n", 3.0, bridge___sin_pi(3.0));

    /* __sin_pif: same coverage for float */
    printf("bridge___sin_pif %a = %a\n", (double)0.1f, (double)bridge___sin_pif(0.1f));
    printf("bridge___sin_pif %a = %a\n", (double)0.3f, (double)bridge___sin_pif(0.3f));
    printf("bridge___sin_pif %a = %a\n", (double)0.75f, (double)bridge___sin_pif(0.75f));
    printf("bridge___sin_pif %a = %a\n", (double)1.4f, (double)bridge___sin_pif(1.4f));
    printf("bridge___sin_pif %a = %a\n", (double)1.8f, (double)bridge___sin_pif(1.8f));
    printf("bridge___sin_pif %a = %a\n", (double)2.0f, (double)bridge___sin_pif(2.0f));

    /* __ctans: varied inputs */
    {
        double _Complex z = CMPLX(0.1, 0.1);
        printf("bridge___ctans %a+%ai = %a\n", creal(z), cimag(z), bridge___ctans(z));
    }
    {
        double _Complex z = CMPLX(0.0, 0.05);
        printf("bridge___ctans %a+%ai = %a\n", creal(z), cimag(z), bridge___ctans(z));
    }

    /* __ctansf: varied inputs */
    {
        float _Complex z = CMPLXF(0.1f, 0.1f);
        printf("bridge___ctansf %a+%ai = %a\n", (double)crealf(z), (double)cimagf(z), (double)bridge___ctansf(z));
    }
    {
        float _Complex z = CMPLXF(0.0f, 0.05f);
        printf("bridge___ctansf %a+%ai = %a\n", (double)crealf(z), (double)cimagf(z), (double)bridge___ctansf(z));
    }
}

/* ================================================================
 * Round 5: targeted tests to cover remaining static functions
 * ================================================================ */

static void test_static_targeted(void)
{
    printf("=== Targeted static function coverage ===\n");

    /*
     * __ctans / __ctansf: triggered when fabs(cos(2*re) + cosh(2*im)) < 0.25
     * Need re ≈ pi/2 so cos(2*re) ≈ cos(pi) = -1, and im ≈ 0 so cosh(2*im) ≈ 1.
     * Then cos(2*re) + cosh(2*im) ≈ 0, which is < 0.25.
     * Previous tests used re ≈ pi/4 which gives cos(pi/2)+cosh(~0) ≈ 1, NOT < 0.25.
     */
    {
        /* re = pi/2 - 0.001, im = 0.001: cos(pi-0.002)+cosh(0.002) ≈ -0.999998+1.000002 ≈ 0.000004 */
        double _Complex z1 = CMPLX(1.5697963267948966, 0.001);
        double _Complex r1 = ctan(z1);
        printf("ctan_ctans %a+%ai = %a+%ai\n", creal(z1), cimag(z1), creal(r1), cimag(r1));
    }
    {
        /* re = pi/2, im = 0: cos(pi)+cosh(0) = -1+1 = 0 exactly */
        double _Complex z2 = CMPLX(1.5707963267948966, 0.0);
        double _Complex r2 = ctan(z2);
        printf("ctan_ctans %a+%ai = %a+%ai\n", creal(z2), cimag(z2), creal(r2), cimag(r2));
    }
    {
        /* re = pi/2 + 0.01, im = 0.01 */
        double _Complex z3 = CMPLX(1.5807963267948966, 0.01);
        double _Complex r3 = ctan(z3);
        printf("ctan_ctans %a+%ai = %a+%ai\n", creal(z3), cimag(z3), creal(r3), cimag(r3));
    }
    {
        /* re = pi/2 - 0.05, im = 0.05: cos(pi-0.1)+cosh(0.1) ≈ -0.995+1.005 ≈ 0.01 */
        double _Complex z4 = CMPLX(1.5207963267948966, 0.05);
        double _Complex r4 = ctan(z4);
        printf("ctan_ctans %a+%ai = %a+%ai\n", creal(z4), cimag(z4), creal(r4), cimag(r4));
    }

    /* __ctansf via ctanf */
    {
        float _Complex z1 = CMPLXF(1.5697963f, 0.001f);
        float _Complex r1 = ctanf(z1);
        printf("ctanf_ctansf %a+%ai = %a+%ai\n", (double)crealf(z1), (double)cimagf(z1), (double)crealf(r1), (double)cimagf(r1));
    }
    {
        float _Complex z2 = CMPLXF(1.5707963f, 0.0f);
        float _Complex r2 = ctanf(z2);
        printf("ctanf_ctansf %a+%ai = %a+%ai\n", (double)crealf(z2), (double)cimagf(z2), (double)crealf(r2), (double)cimagf(r2));
    }
    {
        float _Complex z3 = CMPLXF(1.5807963f, 0.01f);
        float _Complex r3 = ctanf(z3);
        printf("ctanf_ctansf %a+%ai = %a+%ai\n", (double)crealf(z3), (double)cimagf(z3), (double)crealf(r3), (double)cimagf(r3));
    }
    {
        float _Complex z4 = CMPLXF(1.5207963f, 0.05f);
        float _Complex r4 = ctanf(z4);
        printf("ctanf_ctansf %a+%ai = %a+%ai\n", (double)crealf(z4), (double)cimagf(z4), (double)crealf(r4), (double)cimagf(r4));
    }

    /*
     * __rem_pio2_internal / __rem_pio2f_internal: called by __rem_pio2 for
     * arguments with |x| >= 2^20*pi/2 (double) or 2^7*pi/2 (float).
     * Use very large arguments at different magnitudes.
     */
    /* Double: extreme magnitudes for __rem_pio2_internal */
    printf("sin %a = %a\n", 1.0e100, sin(1.0e100));
    printf("cos %a = %a\n", 1.0e100, cos(1.0e100));
    printf("tan %a = %a\n", 1.0e100, tan(1.0e100));
    printf("sin %a = %a\n", 1.0e200, sin(1.0e200));
    printf("cos %a = %a\n", 1.0e200, cos(1.0e200));
    printf("sin %a = %a\n", 1.0e300, sin(1.0e300));
    printf("cos %a = %a\n", 1.0e300, cos(1.0e300));
    /* Medium-large args */
    printf("sin %a = %a\n", 1.0e10, sin(1.0e10));
    printf("cos %a = %a\n", 1.0e10, cos(1.0e10));
    printf("tan %a = %a\n", 1.0e10, tan(1.0e10));

    /* Float: large args for __rem_pio2f_internal */
    printf("sinf %a = %a\n", (double)1.0e20f, (double)sinf(1.0e20f));
    printf("cosf %a = %a\n", (double)1.0e20f, (double)cosf(1.0e20f));
    printf("tanf %a = %a\n", (double)1.0e20f, (double)tanf(1.0e20f));
    printf("sinf %a = %a\n", (double)1.0e30f, (double)sinf(1.0e30f));
    printf("cosf %a = %a\n", (double)1.0e30f, (double)cosf(1.0e30f));
    printf("sinf %a = %a\n", (double)1.0e38f, (double)sinf(1.0e38f));
    printf("cosf %a = %a\n", (double)1.0e38f, (double)cosf(1.0e38f));

    /*
     * __sin_pi / __sin_pif: called by lgamma/tgamma for negative non-integer args.
     * Cover different switch(n) cases by choosing x values:
     *   y = |x| mod 2.0, n = (int)(y*4)
     *   n=0: y in [0, 0.25)       -> x = -N.1
     *   n=1: y in [0.25, 0.5)     -> x = -N.3
     *   n=2: y in [0.5, 0.625)    -> x = -N.55
     *   n=3: y in [0.625, 0.75)   -> x = -N.65
     *   n=4: y in [0.75, 1.0)     -> x = -N.9
     *   n=5: y in [1.0, 1.25)     -> x = -N+1.1  (i.e. -(N-1).1 with mod 2 -> 1.1)
     *   n=6: y in [1.25, 1.5)     -> x mod 2 = 1.3
     *   n=7: y in [1.5, 1.75)     -> x mod 2 = 1.6
     *   default: y in [1.75, 2.0) -> x mod 2 = 1.9
     */
    printf("lgamma %a = %a\n", -0.1, lgamma(-0.1));       /* n=0 */
    printf("lgamma %a = %a\n", -0.3, lgamma(-0.3));       /* n=1 */
    printf("lgamma %a = %a\n", -0.55, lgamma(-0.55));     /* n=2 */
    printf("lgamma %a = %a\n", -0.65, lgamma(-0.65));     /* n=3 */
    printf("lgamma %a = %a\n", -0.9, lgamma(-0.9));       /* n=4, y=0.9 */
    printf("lgamma %a = %a\n", -1.1, lgamma(-1.1));       /* |x|=1.1, y=1.1, n=4 */
    printf("lgamma %a = %a\n", -1.3, lgamma(-1.3));       /* y=1.3, n=5 */
    printf("lgamma %a = %a\n", -1.6, lgamma(-1.6));       /* y=1.6, n=6 */
    printf("lgamma %a = %a\n", -1.9, lgamma(-1.9));       /* y=1.9, n=7/default */
    printf("lgamma %a = %a\n", -2.1, lgamma(-2.1));       /* y=0.1, n=0 */
    printf("lgamma %a = %a\n", -2.3, lgamma(-2.3));       /* y=0.3, n=1 */
    printf("lgamma %a = %a\n", -2.55, lgamma(-2.55));     /* y=0.55, n=2 */
    printf("lgamma %a = %a\n", -3.3, lgamma(-3.3));       /* y=1.3, n=5 */
    printf("lgamma %a = %a\n", -3.6, lgamma(-3.6));       /* y=1.6, n=6 */
    printf("lgamma %a = %a\n", -3.9, lgamma(-3.9));       /* y=1.9, n=7 */
    /* Integer negative: z==y path */
    printf("tgamma %a = %a\n", -2.0, tgamma(-2.0));
    printf("tgamma %a = %a\n", -3.0, tgamma(-3.0));
    printf("tgamma %a = %a\n", -4.0, tgamma(-4.0));
    /* Very small negative for ix < 0x3fd00000 path */
    printf("lgamma %a = %a\n", -0.01, lgamma(-0.01));
    printf("lgamma %a = %a\n", -0.001, lgamma(-0.001));

    /* __sin_pif via lgammaf */
    printf("lgammaf %a = %a\n", (double)-0.1f, (double)lgammaf(-0.1f));
    printf("lgammaf %a = %a\n", (double)-0.3f, (double)lgammaf(-0.3f));
    printf("lgammaf %a = %a\n", (double)-0.55f, (double)lgammaf(-0.55f));
    printf("lgammaf %a = %a\n", (double)-0.65f, (double)lgammaf(-0.65f));
    printf("lgammaf %a = %a\n", (double)-0.9f, (double)lgammaf(-0.9f));
    printf("lgammaf %a = %a\n", (double)-1.3f, (double)lgammaf(-1.3f));
    printf("lgammaf %a = %a\n", (double)-1.6f, (double)lgammaf(-1.6f));
    printf("lgammaf %a = %a\n", (double)-1.9f, (double)lgammaf(-1.9f));
    printf("lgammaf %a = %a\n", (double)-0.01f, (double)lgammaf(-0.01f));
    printf("tgammaf %a = %a\n", (double)-2.0f, (double)tgammaf(-2.0f));
    printf("tgammaf %a = %a\n", (double)-3.0f, (double)tgammaf(-3.0f));

    /*
     * __tan / __tanf: called by tan()/tanf() for |x| < pi/4.
     * Cover both the |x| >= 0.6744 and |x| < 0.6744 paths,
     * and iy=1 vs iy=-1 (determined by quadrant from __rem_pio2).
     * tan(x) with x in different quadrants calls __tan with different iy values.
     */
    /* Direct small args -> __tan with iy=1 */
    printf("tan %a = %a\n", 0.01, tan(0.01));
    printf("tan %a = %a\n", -0.01, tan(-0.01));
    printf("tan %a = %a\n", 0.5, tan(0.5));
    printf("tan %a = %a\n", -0.5, tan(-0.5));
    /* Args in pi/4..pi/2 range: __rem_pio2 returns n=1, calls __tan with iy=-1 */
    printf("tan %a = %a\n", 1.0, tan(1.0));
    printf("tan %a = %a\n", -1.0, tan(-1.0));
    printf("tan %a = %a\n", 1.2, tan(1.2));
    printf("tan %a = %a\n", 1.5, tan(1.5));
    /* Very small args: |x| < 2^-27 path */
    printf("tan %a = %a\n", 1.0e-9, tan(1.0e-9));
    printf("tan %a = %a\n", -1.0e-9, tan(-1.0e-9));

    /* __tanf */
    printf("tanf %a = %a\n", (double)0.01f, (double)tanf(0.01f));
    printf("tanf %a = %a\n", (double)-0.01f, (double)tanf(-0.01f));
    printf("tanf %a = %a\n", (double)0.5f, (double)tanf(0.5f));
    printf("tanf %a = %a\n", (double)1.0f, (double)tanf(1.0f));
    printf("tanf %a = %a\n", (double)-1.0f, (double)tanf(-1.0f));
    printf("tanf %a = %a\n", (double)1.2f, (double)tanf(1.2f));
    printf("tanf %a = %a\n", (double)1.5f, (double)tanf(1.5f));
    printf("tanf %a = %a\n", (double)1.0e-5f, (double)tanf(1.0e-5f));

    /* Additional bridge calls with diverse inputs */
    /* __tan with iy=-1 explicitly */
    printf("bridge___tan %a %a %d = %a\n", 0.3, 1.0e-20, 1, bridge___tan(0.3, 1.0e-20, 1));
    printf("bridge___tan %a %a %d = %a\n", 0.3, 1.0e-20, -1, bridge___tan(0.3, 1.0e-20, -1));
    printf("bridge___tan %a %a %d = %a\n", 0.0, 0.0, 1, bridge___tan(0.0, 0.0, 1));
    printf("bridge___tan %a %a %d = %a\n", 0.75, 1.0e-18, 1, bridge___tan(0.75, 1.0e-18, 1));
    printf("bridge___tan %a %a %d = %a\n", 0.75, 1.0e-18, -1, bridge___tan(0.75, 1.0e-18, -1));

    /* __tanf with varied inputs */
    printf("bridge___tanf %a %a %d = %a\n", (double)0.3f, 0.0, 1, (double)bridge___tanf(0.3f, 0.0f, 1));
    printf("bridge___tanf %a %a %d = %a\n", (double)0.3f, 0.0, -1, (double)bridge___tanf(0.3f, 0.0f, -1));
    printf("bridge___tanf %a %a %d = %a\n", (double)0.0f, 0.0, 1, (double)bridge___tanf(0.0f, 0.0f, 1));
    printf("bridge___tanf %a %a %d = %a\n", (double)0.75f, 0.0, 1, (double)bridge___tanf(0.75f, 0.0f, 1));
    printf("bridge___tanf %a %a %d = %a\n", (double)0.75f, 0.0, -1, (double)bridge___tanf(0.75f, 0.0f, -1));

    /* __rem_pio2_internal with diverse e0/nx */
    {
        double x_arr[3] = {1.0, 0.5, 0.25};
        double y_arr[2];
        int r = bridge___rem_pio2_internal(x_arr, y_arr, 100, 3);
        printf("bridge___rem_pio2_internal e0=100 nx=3 = n=%d y=%a %a\n", r, y_arr[0], y_arr[1]);
    }
    {
        double x_arr[3] = {1.0, 0.0, 0.0};
        double y_arr[2];
        int r = bridge___rem_pio2_internal(x_arr, y_arr, 200, 1);
        printf("bridge___rem_pio2_internal e0=200 nx=1 = n=%d y=%a %a\n", r, y_arr[0], y_arr[1]);
    }

    /* __rem_pio2f_internal with diverse e0/nx */
    {
        float x_arr[3] = {1.0f, 0.5f, 0.25f};
        float y_arr[2];
        int r = bridge___rem_pio2f_internal(x_arr, y_arr, 100, 3);
        printf("bridge___rem_pio2f_internal e0=100 nx=3 = n=%d y=%a %a\n", r, (double)y_arr[0], (double)y_arr[1]);
    }
    {
        float x_arr[3] = {1.0f, 0.0f, 0.0f};
        float y_arr[2];
        int r = bridge___rem_pio2f_internal(x_arr, y_arr, 50, 1);
        printf("bridge___rem_pio2f_internal e0=50 nx=1 = n=%d y=%a %a\n", r, (double)y_arr[0], (double)y_arr[1]);
    }

    /* __sin_pi with more values */
    printf("bridge___sin_pi %a = %a\n", 0.55, bridge___sin_pi(0.55));  /* n=2 */
    printf("bridge___sin_pi %a = %a\n", 0.65, bridge___sin_pi(0.65));  /* n=2 */
    printf("bridge___sin_pi %a = %a\n", 0.9, bridge___sin_pi(0.9));   /* n=3 */
    printf("bridge___sin_pi %a = %a\n", 1.1, bridge___sin_pi(1.1));   /* n=4 */
    printf("bridge___sin_pi %a = %a\n", 1.3, bridge___sin_pi(1.3));   /* n=5 */
    printf("bridge___sin_pi %a = %a\n", 1.6, bridge___sin_pi(1.6));   /* n=6 */
    printf("bridge___sin_pi %a = %a\n", 1.9, bridge___sin_pi(1.9));   /* n=7 */
    printf("bridge___sin_pi %a = %a\n", 0.01, bridge___sin_pi(0.01)); /* ix < 0x3fd00000 */

    /* __sin_pif with more values */
    printf("bridge___sin_pif %a = %a\n", (double)0.55f, (double)bridge___sin_pif(0.55f));
    printf("bridge___sin_pif %a = %a\n", (double)0.65f, (double)bridge___sin_pif(0.65f));
    printf("bridge___sin_pif %a = %a\n", (double)0.9f, (double)bridge___sin_pif(0.9f));
    printf("bridge___sin_pif %a = %a\n", (double)1.1f, (double)bridge___sin_pif(1.1f));
    printf("bridge___sin_pif %a = %a\n", (double)1.3f, (double)bridge___sin_pif(1.3f));
    printf("bridge___sin_pif %a = %a\n", (double)1.6f, (double)bridge___sin_pif(1.6f));
    printf("bridge___sin_pif %a = %a\n", (double)1.9f, (double)bridge___sin_pif(1.9f));
    printf("bridge___sin_pif %a = %a\n", (double)0.01f, (double)bridge___sin_pif(0.01f));

    /* __ctans with pi/2-region inputs via bridge */
    {
        double _Complex z = CMPLX(1.5707963267948966, 0.001);
        printf("bridge___ctans %a+%ai = %a\n", creal(z), cimag(z), bridge___ctans(z));
    }
    {
        double _Complex z = CMPLX(1.5707963267948966, 0.0);
        printf("bridge___ctans %a+%ai = %a\n", creal(z), cimag(z), bridge___ctans(z));
    }

    /* __ctansf with pi/2-region inputs via bridge */
    {
        float _Complex z = CMPLXF(1.5707963f, 0.001f);
        printf("bridge___ctansf %a+%ai = %a\n", (double)crealf(z), (double)cimagf(z), (double)bridge___ctansf(z));
    }
    {
        float _Complex z = CMPLXF(1.5707963f, 0.0f);
        printf("bridge___ctansf %a+%ai = %a\n", (double)crealf(z), (double)cimagf(z), (double)bridge___ctansf(z));
    }
}

/* ================================================================
 * main
 * ================================================================ */

int main(void)
{
    /* Standard math functions */
    test_trig_double();
    test_trig_float();
    test_trig_long();
    test_hyp_double();
    test_hyp_float();
    test_hyp_long();
    test_exp_log_double();
    test_exp_log_float();
    test_exp_log_long();
    test_pow_sqrt_double();
    test_pow_sqrt_float();
    test_pow_sqrt_long();
    test_err_gamma_double();
    test_err_gamma_float();
    test_err_gamma_long();
    test_bessel();
    test_rounding_double();
    test_rounding_float();
    test_rounding_long();
    test_fp_manip_double();
    test_fp_manip_float();
    test_fp_manip_long();

    /* Complex functions */
    test_complex_double();
    test_complex_float();
    test_complex_long();

    /* Internal functions */
    test_internal_trig();
    test_internal_gamma();
    test_internal_classify();
    test_internal_complex();

    /* Bridge tests for static functions */
    test_bridge_static();

    /* Additional coverage triggers */
    test_large_arg_trig();

    /* Exercise static functions via public API */
    test_static_via_public_api();

    /* Extra bridge tests for more code paths */
    test_bridge_static_extra();

    /* Targeted tests for remaining uncovered static functions */
    test_static_targeted();

    printf("\nAll tests completed.\n");
    return 0;
}
