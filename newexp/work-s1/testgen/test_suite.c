/* test_suite.c — generated test harness for libmcs */

#include <stdio.h>
#include <limits.h>
#include "math.h"
#include "complex.h"

/* ===== Double trigonometric ===== */
static void test_acos(void)
{
    double vals[] = {-1.0, -0.5, 0.0, 0.5, 1.0};
    for (int i = 0; i < 5; i++)
        printf("acos %a = %a\n", vals[i], acos(vals[i]));
}

static void test_asin(void)
{
    double vals[] = {-1.0, -0.5, 0.0, 0.5, 1.0};
    for (int i = 0; i < 5; i++)
        printf("asin %a = %a\n", vals[i], asin(vals[i]));
}

static void test_atan(void)
{
    double vals[] = {-1.0, 0.0, 1.0, 100.0, -100.0};
    for (int i = 0; i < 5; i++)
        printf("atan %a = %a\n", vals[i], atan(vals[i]));
}

static void test_atan2(void)
{
    double ys[] = {1.0, -1.0, 0.0, 1.0};
    double xs[] = {1.0,  1.0, 1.0, 0.0};
    for (int i = 0; i < 4; i++)
        printf("atan2 %a %a = %a\n", ys[i], xs[i], atan2(ys[i], xs[i]));
}

static void test_cos(void)
{
    double vals[] = {0.0, 0.5, 1.0, 3.14159265358979323846, -1.0};
    for (int i = 0; i < 5; i++)
        printf("cos %a = %a\n", vals[i], cos(vals[i]));
}

static void test_sin(void)
{
    double vals[] = {0.0, 0.5, 1.0, 3.14159265358979323846, -1.0};
    for (int i = 0; i < 5; i++)
        printf("sin %a = %a\n", vals[i], sin(vals[i]));
}

static void test_tan(void)
{
    double vals[] = {0.0, 0.5, 1.0, -1.0, 0.7853981633974483};
    for (int i = 0; i < 5; i++)
        printf("tan %a = %a\n", vals[i], tan(vals[i]));
}

/* ===== Double hyperbolic ===== */
static void test_acosh(void)
{
    double vals[] = {1.0, 2.0, 10.0, 100.0};
    for (int i = 0; i < 4; i++)
        printf("acosh %a = %a\n", vals[i], acosh(vals[i]));
}

static void test_asinh(void)
{
    double vals[] = {0.0, 1.0, -1.0, 10.0, -10.0};
    for (int i = 0; i < 5; i++)
        printf("asinh %a = %a\n", vals[i], asinh(vals[i]));
}

static void test_atanh(void)
{
    double vals[] = {0.0, 0.5, -0.5, 0.99, -0.99};
    for (int i = 0; i < 5; i++)
        printf("atanh %a = %a\n", vals[i], atanh(vals[i]));
}

static void test_cosh(void)
{
    double vals[] = {0.0, 1.0, -1.0, 10.0};
    for (int i = 0; i < 4; i++)
        printf("cosh %a = %a\n", vals[i], cosh(vals[i]));
}

static void test_sinh(void)
{
    double vals[] = {0.0, 1.0, -1.0, 10.0};
    for (int i = 0; i < 4; i++)
        printf("sinh %a = %a\n", vals[i], sinh(vals[i]));
}

static void test_tanh(void)
{
    double vals[] = {0.0, 1.0, -1.0, 10.0, -10.0};
    for (int i = 0; i < 5; i++)
        printf("tanh %a = %a\n", vals[i], tanh(vals[i]));
}

/* ===== Double exponential / logarithmic ===== */
static void test_exp(void)
{
    double vals[] = {0.0, 1.0, -1.0, 2.0, 10.0};
    for (int i = 0; i < 5; i++)
        printf("exp %a = %a\n", vals[i], exp(vals[i]));
}

static void test_exp2(void)
{
    double vals[] = {0.0, 1.0, 10.0, -1.0, 0.5};
    for (int i = 0; i < 5; i++)
        printf("exp2 %a = %a\n", vals[i], exp2(vals[i]));
}

static void test_expm1(void)
{
    double vals[] = {0.0, 1.0, -1.0, 1e-10, -1e-10};
    for (int i = 0; i < 5; i++)
        printf("expm1 %a = %a\n", vals[i], expm1(vals[i]));
}

static void test_frexp(void)
{
    double vals[] = {0.0, 1.0, -1.0, 1024.0, 0.1};
    int e;
    for (int i = 0; i < 5; i++) {
        double r = frexp(vals[i], &e);
        printf("frexp %a = %a exp=%d\n", vals[i], r, e);
    }
}

static void test_ilogb(void)
{
    double vals[] = {1.0, 2.0, 0.5, 1024.0, 0.001};
    for (int i = 0; i < 5; i++)
        printf("ilogb %a = %d\n", vals[i], ilogb(vals[i]));
}

static void test_ldexp(void)
{
    double bases[] = {1.0, 0.5, -1.0, 1.0};
    int exps[] = {0, 1, 10, -3};
    for (int i = 0; i < 4; i++)
        printf("ldexp %a %d = %a\n", bases[i], exps[i], ldexp(bases[i], exps[i]));
}

static void test_log(void)
{
    double vals[] = {1.0, 2.718281828459045, 10.0, 0.5, 100.0};
    for (int i = 0; i < 5; i++)
        printf("log %a = %a\n", vals[i], log(vals[i]));
}

static void test_log10(void)
{
    double vals[] = {1.0, 10.0, 100.0, 0.1, 1000.0};
    for (int i = 0; i < 5; i++)
        printf("log10 %a = %a\n", vals[i], log10(vals[i]));
}

static void test_log1p(void)
{
    double vals[] = {0.0, 1.0, -0.5, 1e-15, 1e-10};
    for (int i = 0; i < 5; i++)
        printf("log1p %a = %a\n", vals[i], log1p(vals[i]));
}

static void test_log2(void)
{
    double vals[] = {1.0, 2.0, 4.0, 0.5, 1024.0};
    for (int i = 0; i < 5; i++)
        printf("log2 %a = %a\n", vals[i], log2(vals[i]));
}

static void test_logb(void)
{
    double vals[] = {1.0, 2.0, 0.5, 1024.0, 0.001};
    for (int i = 0; i < 5; i++)
        printf("logb %a = %a\n", vals[i], logb(vals[i]));
}

static void test_modf(void)
{
    double vals[] = {3.14, -3.14, 0.0, 100.5, -0.5};
    double ipart;
    for (int i = 0; i < 5; i++) {
        double r = modf(vals[i], &ipart);
        printf("modf %a = %a ipart=%a\n", vals[i], r, ipart);
    }
}

static void test_scalbn(void)
{
    double bases[] = {1.0, 0.5, -1.0};
    int exps[] = {2, 3, 10};
    for (int i = 0; i < 3; i++)
        printf("scalbn %a %d = %a\n", bases[i], exps[i], scalbn(bases[i], exps[i]));
}

static void test_scalbln(void)
{
    double bases[] = {1.0, 0.5, -1.0};
    long exps[] = {2, 3, 10};
    for (int i = 0; i < 3; i++)
        printf("scalbln %a %ld = %a\n", bases[i], exps[i], scalbln(bases[i], exps[i]));
}

/* ===== Double power / absolute ===== */
static void test_cbrt(void)
{
    double vals[] = {0.0, 1.0, 8.0, -8.0, 27.0};
    for (int i = 0; i < 5; i++)
        printf("cbrt %a = %a\n", vals[i], cbrt(vals[i]));
}

static void test_fabs(void)
{
    double vals[] = {0.0, 1.0, -1.0, -3.14, 3.14};
    for (int i = 0; i < 5; i++)
        printf("fabs %a = %a\n", vals[i], fabs(vals[i]));
}

static void test_hypot(void)
{
    double xs[] = {3.0, 1.0, 0.0, -3.0};
    double ys[] = {4.0, 1.0, 0.0,  4.0};
    for (int i = 0; i < 4; i++)
        printf("hypot %a %a = %a\n", xs[i], ys[i], hypot(xs[i], ys[i]));
}

static void test_pow(void)
{
    double bs[] = {2.0, 10.0, 2.0, 0.5, 2.0};
    double es[] = {0.0, 2.0, 10.0, 2.0, -1.0};
    for (int i = 0; i < 5; i++)
        printf("pow %a %a = %a\n", bs[i], es[i], pow(bs[i], es[i]));
}

static void test_sqrt(void)
{
    double vals[] = {0.0, 1.0, 2.0, 4.0, 100.0};
    for (int i = 0; i < 5; i++)
        printf("sqrt %a = %a\n", vals[i], sqrt(vals[i]));
}

/* ===== Double error / gamma ===== */
static void test_erf(void)
{
    double vals[] = {0.0, 0.5, 1.0, 2.0, -1.0};
    for (int i = 0; i < 5; i++)
        printf("erf %a = %a\n", vals[i], erf(vals[i]));
}

static void test_erfc(void)
{
    double vals[] = {0.0, 0.5, 1.0, 2.0, 3.0};
    for (int i = 0; i < 5; i++)
        printf("erfc %a = %a\n", vals[i], erfc(vals[i]));
}

static void test_lgamma(void)
{
    double vals[] = {1.0, 2.0, 0.5, 5.0, 10.0};
    for (int i = 0; i < 5; i++)
        printf("lgamma %a = %a\n", vals[i], lgamma(vals[i]));
}

static void test_tgamma(void)
{
    double vals[] = {1.0, 2.0, 3.0, 5.0, 0.5};
    for (int i = 0; i < 5; i++)
        printf("tgamma %a = %a\n", vals[i], tgamma(vals[i]));
}

/* ===== Double nearest integer ===== */
static void test_ceil(void)
{
    double vals[] = {0.0, 0.1, -0.1, 2.9, -2.9};
    for (int i = 0; i < 5; i++)
        printf("ceil %a = %a\n", vals[i], ceil(vals[i]));
}

static void test_floor(void)
{
    double vals[] = {0.0, 0.1, -0.1, 2.9, -2.9};
    for (int i = 0; i < 5; i++)
        printf("floor %a = %a\n", vals[i], floor(vals[i]));
}

static void test_nearbyint(void)
{
    double vals[] = {0.5, 1.5, 2.5, -0.5, -1.5};
    for (int i = 0; i < 5; i++)
        printf("nearbyint %a = %a\n", vals[i], nearbyint(vals[i]));
}

static void test_rint(void)
{
    double vals[] = {0.5, 1.5, 2.5, -0.5, -1.5};
    for (int i = 0; i < 5; i++)
        printf("rint %a = %a\n", vals[i], rint(vals[i]));
}

static void test_lrint(void)
{
    double vals[] = {0.5, 1.5, 2.5, -0.5, -1.5};
    for (int i = 0; i < 5; i++)
        printf("lrint %a = %ld\n", vals[i], lrint(vals[i]));
}

static void test_llrint(void)
{
    double vals[] = {0.5, 1.5, 2.5, -0.5, -1.5};
    for (int i = 0; i < 5; i++)
        printf("llrint %a = %lld\n", vals[i], llrint(vals[i]));
}

static void test_round(void)
{
    double vals[] = {0.5, 1.5, 2.5, -0.5, -1.5};
    for (int i = 0; i < 5; i++)
        printf("round %a = %a\n", vals[i], round(vals[i]));
}

static void test_lround(void)
{
    double vals[] = {0.5, 1.5, 2.5, -0.5, -1.5};
    for (int i = 0; i < 5; i++)
        printf("lround %a = %ld\n", vals[i], lround(vals[i]));
}

static void test_llround(void)
{
    double vals[] = {0.5, 1.5, 2.5, -0.5, -1.5};
    for (int i = 0; i < 5; i++)
        printf("llround %a = %lld\n", vals[i], llround(vals[i]));
}

static void test_trunc(void)
{
    double vals[] = {0.0, 2.9, -2.9, 0.1, -0.1};
    for (int i = 0; i < 5; i++)
        printf("trunc %a = %a\n", vals[i], trunc(vals[i]));
}

/* ===== Double remainder ===== */
static void test_fmod(void)
{
    double xs[] = {5.0, -5.0, 10.0, 7.5};
    double ys[] = {3.0,  3.0,  3.0, 2.5};
    for (int i = 0; i < 4; i++)
        printf("fmod %a %a = %a\n", xs[i], ys[i], fmod(xs[i], ys[i]));
}

static void test_remainder(void)
{
    double xs[] = {5.0, -5.0, 10.0, 7.5};
    double ys[] = {3.0,  3.0,  3.0, 2.5};
    for (int i = 0; i < 4; i++)
        printf("remainder %a %a = %a\n", xs[i], ys[i], remainder(xs[i], ys[i]));
}

static void test_remquo(void)
{
    double xs[] = {5.0, 10.0};
    double ys[] = {3.0,  3.0};
    int q;
    for (int i = 0; i < 2; i++) {
        double r = remquo(xs[i], ys[i], &q);
        printf("remquo %a %a = %a quo=%d\n", xs[i], ys[i], r, q);
    }
}

/* ===== Double manipulation ===== */
static void test_copysign(void)
{
    printf("copysign %a %a = %a\n", 1.0, -1.0, copysign(1.0, -1.0));
    printf("copysign %a %a = %a\n", -1.0, 1.0, copysign(-1.0, 1.0));
    printf("copysign %a %a = %a\n", 0.0, -1.0, copysign(0.0, -1.0));
}

static void test_nan_func(void)
{
    double n = nan("");
    printf("nan = %a\n", n);
}

static void test_nextafter(void)
{
    printf("nextafter %a %a = %a\n", 1.0, 2.0, nextafter(1.0, 2.0));
    printf("nextafter %a %a = %a\n", 1.0, 0.0, nextafter(1.0, 0.0));
    printf("nextafter %a %a = %a\n", 0.0, 1.0, nextafter(0.0, 1.0));
}

/* ===== Double min/max/dim ===== */
static void test_fdim(void)
{
    printf("fdim %a %a = %a\n", 5.0, 3.0, fdim(5.0, 3.0));
    printf("fdim %a %a = %a\n", 3.0, 5.0, fdim(3.0, 5.0));
    printf("fdim %a %a = %a\n", -3.0, -5.0, fdim(-3.0, -5.0));
}

static void test_fmax(void)
{
    printf("fmax %a %a = %a\n", 2.0, 3.0, fmax(2.0, 3.0));
    printf("fmax %a %a = %a\n", -2.0, -3.0, fmax(-2.0, -3.0));
}

static void test_fmin(void)
{
    printf("fmin %a %a = %a\n", 2.0, 3.0, fmin(2.0, 3.0));
    printf("fmin %a %a = %a\n", -2.0, -3.0, fmin(-2.0, -3.0));
}

/* ===== Double fma ===== */
static void test_fma(void)
{
    printf("fma %a %a %a = %a\n", 2.0, 3.0, 4.0, fma(2.0, 3.0, 4.0));
    printf("fma %a %a %a = %a\n", -1.0, 5.0, 0.5, fma(-1.0, 5.0, 0.5));
}

/* ===== Double Bessel ===== */
static void test_j0(void)
{
    double vals[] = {0.0, 1.0, 2.0, 5.0, 10.0};
    for (int i = 0; i < 5; i++)
        printf("j0 %a = %a\n", vals[i], j0(vals[i]));
}

static void test_j1(void)
{
    double vals[] = {0.0, 1.0, 2.0, 5.0, 10.0};
    for (int i = 0; i < 5; i++)
        printf("j1 %a = %a\n", vals[i], j1(vals[i]));
}

static void test_jn(void)
{
    int ns[] = {0, 1, 2, 3};
    double xs[] = {1.0, 2.0, 3.0, 5.0};
    for (int i = 0; i < 4; i++)
        printf("jn %d %a = %a\n", ns[i], xs[i], jn(ns[i], xs[i]));
}

static void test_y0(void)
{
    double vals[] = {0.5, 1.0, 2.0, 5.0, 10.0};
    for (int i = 0; i < 5; i++)
        printf("y0 %a = %a\n", vals[i], y0(vals[i]));
}

static void test_y1(void)
{
    double vals[] = {0.5, 1.0, 2.0, 5.0, 10.0};
    for (int i = 0; i < 5; i++)
        printf("y1 %a = %a\n", vals[i], y1(vals[i]));
}

static void test_yn(void)
{
    int ns[] = {0, 1, 2, 3};
    double xs[] = {1.0, 2.0, 3.0, 5.0};
    for (int i = 0; i < 4; i++)
        printf("yn %d %a = %a\n", ns[i], xs[i], yn(ns[i], xs[i]));
}

/* ===== Float trigonometric ===== */
static void test_acosf(void)
{
    float vals[] = {-1.0f, -0.5f, 0.0f, 0.5f, 1.0f};
    for (int i = 0; i < 5; i++)
        printf("acosf %a = %a\n", (double)vals[i], (double)acosf(vals[i]));
}

static void test_asinf(void)
{
    float vals[] = {-1.0f, -0.5f, 0.0f, 0.5f, 1.0f};
    for (int i = 0; i < 5; i++)
        printf("asinf %a = %a\n", (double)vals[i], (double)asinf(vals[i]));
}

static void test_atanf(void)
{
    float vals[] = {-1.0f, 0.0f, 1.0f, 100.0f, -100.0f};
    for (int i = 0; i < 5; i++)
        printf("atanf %a = %a\n", (double)vals[i], (double)atanf(vals[i]));
}

static void test_atan2f(void)
{
    float ys[] = {1.0f, -1.0f, 0.0f, 1.0f};
    float xs[] = {1.0f,  1.0f, 1.0f, 0.0f};
    for (int i = 0; i < 4; i++)
        printf("atan2f %a %a = %a\n", (double)ys[i], (double)xs[i], (double)atan2f(ys[i], xs[i]));
}

static void test_cosf(void)
{
    float vals[] = {0.0f, 0.5f, 1.0f, 3.14159265f, -1.0f};
    for (int i = 0; i < 5; i++)
        printf("cosf %a = %a\n", (double)vals[i], (double)cosf(vals[i]));
}

static void test_sinf(void)
{
    float vals[] = {0.0f, 0.5f, 1.0f, 3.14159265f, -1.0f};
    for (int i = 0; i < 5; i++)
        printf("sinf %a = %a\n", (double)vals[i], (double)sinf(vals[i]));
}

static void test_tanf(void)
{
    float vals[] = {0.0f, 0.5f, 1.0f, -1.0f, 0.7853981f};
    for (int i = 0; i < 5; i++)
        printf("tanf %a = %a\n", (double)vals[i], (double)tanf(vals[i]));
}

/* ===== Float hyperbolic ===== */
static void test_acoshf(void)
{
    float vals[] = {1.0f, 2.0f, 10.0f, 100.0f};
    for (int i = 0; i < 4; i++)
        printf("acoshf %a = %a\n", (double)vals[i], (double)acoshf(vals[i]));
}

static void test_asinhf(void)
{
    float vals[] = {0.0f, 1.0f, -1.0f, 10.0f};
    for (int i = 0; i < 4; i++)
        printf("asinhf %a = %a\n", (double)vals[i], (double)asinhf(vals[i]));
}

static void test_atanhf(void)
{
    float vals[] = {0.0f, 0.5f, -0.5f, 0.99f};
    for (int i = 0; i < 4; i++)
        printf("atanhf %a = %a\n", (double)vals[i], (double)atanhf(vals[i]));
}

static void test_coshf(void)
{
    float vals[] = {0.0f, 1.0f, -1.0f, 10.0f};
    for (int i = 0; i < 4; i++)
        printf("coshf %a = %a\n", (double)vals[i], (double)coshf(vals[i]));
}

static void test_sinhf(void)
{
    float vals[] = {0.0f, 1.0f, -1.0f, 10.0f};
    for (int i = 0; i < 4; i++)
        printf("sinhf %a = %a\n", (double)vals[i], (double)sinhf(vals[i]));
}

static void test_tanhf(void)
{
    float vals[] = {0.0f, 1.0f, -1.0f, 10.0f};
    for (int i = 0; i < 4; i++)
        printf("tanhf %a = %a\n", (double)vals[i], (double)tanhf(vals[i]));
}

/* ===== Float exponential / logarithmic ===== */
static void test_expf(void)
{
    float vals[] = {0.0f, 1.0f, -1.0f, 2.0f, 10.0f};
    for (int i = 0; i < 5; i++)
        printf("expf %a = %a\n", (double)vals[i], (double)expf(vals[i]));
}

static void test_exp2f(void)
{
    float vals[] = {0.0f, 1.0f, 10.0f, -1.0f, 0.5f};
    for (int i = 0; i < 5; i++)
        printf("exp2f %a = %a\n", (double)vals[i], (double)exp2f(vals[i]));
}

static void test_expm1f(void)
{
    float vals[] = {0.0f, 1.0f, -1.0f, 1e-7f};
    for (int i = 0; i < 4; i++)
        printf("expm1f %a = %a\n", (double)vals[i], (double)expm1f(vals[i]));
}

static void test_frexpf(void)
{
    float vals[] = {0.0f, 1.0f, -1.0f, 1024.0f};
    int e;
    for (int i = 0; i < 4; i++) {
        float r = frexpf(vals[i], &e);
        printf("frexpf %a = %a exp=%d\n", (double)vals[i], (double)r, e);
    }
}

static void test_ilogbf(void)
{
    float vals[] = {1.0f, 2.0f, 0.5f, 1024.0f};
    for (int i = 0; i < 4; i++)
        printf("ilogbf %a = %d\n", (double)vals[i], ilogbf(vals[i]));
}

static void test_ldexpf(void)
{
    float bases[] = {1.0f, 0.5f, -1.0f};
    int exps[] = {0, 1, 10};
    for (int i = 0; i < 3; i++)
        printf("ldexpf %a %d = %a\n", (double)bases[i], exps[i], (double)ldexpf(bases[i], exps[i]));
}

static void test_logf(void)
{
    float vals[] = {1.0f, 2.718281828f, 10.0f, 0.5f};
    for (int i = 0; i < 4; i++)
        printf("logf %a = %a\n", (double)vals[i], (double)logf(vals[i]));
}

static void test_log10f(void)
{
    float vals[] = {1.0f, 10.0f, 100.0f, 0.1f};
    for (int i = 0; i < 4; i++)
        printf("log10f %a = %a\n", (double)vals[i], (double)log10f(vals[i]));
}

static void test_log1pf(void)
{
    float vals[] = {0.0f, 1.0f, -0.5f, 1e-7f};
    for (int i = 0; i < 4; i++)
        printf("log1pf %a = %a\n", (double)vals[i], (double)log1pf(vals[i]));
}

static void test_log2f(void)
{
    float vals[] = {1.0f, 2.0f, 4.0f, 0.5f, 1024.0f};
    for (int i = 0; i < 5; i++)
        printf("log2f %a = %a\n", (double)vals[i], (double)log2f(vals[i]));
}

static void test_logbf(void)
{
    float vals[] = {1.0f, 2.0f, 0.5f, 1024.0f};
    for (int i = 0; i < 4; i++)
        printf("logbf %a = %a\n", (double)vals[i], (double)logbf(vals[i]));
}

static void test_modff(void)
{
    float vals[] = {3.14f, -3.14f, 0.0f, 100.5f};
    float ipart;
    for (int i = 0; i < 4; i++) {
        float r = modff(vals[i], &ipart);
        printf("modff %a = %a ipart=%a\n", (double)vals[i], (double)r, (double)ipart);
    }
}

static void test_scalbnf(void)
{
    float bases[] = {1.0f, 0.5f, -1.0f};
    int exps[] = {2, 3, 10};
    for (int i = 0; i < 3; i++)
        printf("scalbnf %a %d = %a\n", (double)bases[i], exps[i], (double)scalbnf(bases[i], exps[i]));
}

static void test_scalblnf(void)
{
    float bases[] = {1.0f, 0.5f};
    long exps[] = {2, 3};
    for (int i = 0; i < 2; i++)
        printf("scalblnf %a %ld = %a\n", (double)bases[i], exps[i], (double)scalblnf(bases[i], exps[i]));
}

/* ===== Float power / absolute ===== */
static void test_cbrtf(void)
{
    float vals[] = {0.0f, 1.0f, 8.0f, -8.0f, 27.0f};
    for (int i = 0; i < 5; i++)
        printf("cbrtf %a = %a\n", (double)vals[i], (double)cbrtf(vals[i]));
}

static void test_fabsf(void)
{
    float vals[] = {0.0f, 1.0f, -1.0f, -3.14f};
    for (int i = 0; i < 4; i++)
        printf("fabsf %a = %a\n", (double)vals[i], (double)fabsf(vals[i]));
}

static void test_hypotf(void)
{
    float xs[] = {3.0f, 1.0f, 0.0f};
    float ys[] = {4.0f, 1.0f, 0.0f};
    for (int i = 0; i < 3; i++)
        printf("hypotf %a %a = %a\n", (double)xs[i], (double)ys[i], (double)hypotf(xs[i], ys[i]));
}

static void test_powf(void)
{
    float bs[] = {2.0f, 10.0f, 2.0f, 0.5f};
    float es[] = {0.0f, 2.0f, 10.0f, 2.0f};
    for (int i = 0; i < 4; i++)
        printf("powf %a %a = %a\n", (double)bs[i], (double)es[i], (double)powf(bs[i], es[i]));
}

static void test_sqrtf(void)
{
    float vals[] = {0.0f, 1.0f, 2.0f, 4.0f, 100.0f};
    for (int i = 0; i < 5; i++)
        printf("sqrtf %a = %a\n", (double)vals[i], (double)sqrtf(vals[i]));
}

/* ===== Float error / gamma ===== */
static void test_erff(void)
{
    float vals[] = {0.0f, 0.5f, 1.0f, 2.0f, -1.0f};
    for (int i = 0; i < 5; i++)
        printf("erff %a = %a\n", (double)vals[i], (double)erff(vals[i]));
}

static void test_erfcf(void)
{
    float vals[] = {0.0f, 0.5f, 1.0f, 2.0f};
    for (int i = 0; i < 4; i++)
        printf("erfcf %a = %a\n", (double)vals[i], (double)erfcf(vals[i]));
}

static void test_lgammaf(void)
{
    float vals[] = {1.0f, 2.0f, 0.5f, 5.0f};
    for (int i = 0; i < 4; i++)
        printf("lgammaf %a = %a\n", (double)vals[i], (double)lgammaf(vals[i]));
}

static void test_tgammaf(void)
{
    float vals[] = {1.0f, 2.0f, 3.0f, 5.0f, 0.5f};
    for (int i = 0; i < 5; i++)
        printf("tgammaf %a = %a\n", (double)vals[i], (double)tgammaf(vals[i]));
}

/* ===== Float nearest integer ===== */
static void test_ceilf(void)
{
    float vals[] = {0.0f, 0.1f, -0.1f, 2.9f, -2.9f};
    for (int i = 0; i < 5; i++)
        printf("ceilf %a = %a\n", (double)vals[i], (double)ceilf(vals[i]));
}

static void test_floorf(void)
{
    float vals[] = {0.0f, 0.1f, -0.1f, 2.9f, -2.9f};
    for (int i = 0; i < 5; i++)
        printf("floorf %a = %a\n", (double)vals[i], (double)floorf(vals[i]));
}

static void test_nearbyintf(void)
{
    float vals[] = {0.5f, 1.5f, 2.5f, -0.5f, -1.5f};
    for (int i = 0; i < 5; i++)
        printf("nearbyintf %a = %a\n", (double)vals[i], (double)nearbyintf(vals[i]));
}

static void test_rintf(void)
{
    float vals[] = {0.5f, 1.5f, 2.5f, -0.5f, -1.5f};
    for (int i = 0; i < 5; i++)
        printf("rintf %a = %a\n", (double)vals[i], (double)rintf(vals[i]));
}

static void test_lrintf(void)
{
    float vals[] = {0.5f, 1.5f, 2.5f, -0.5f};
    for (int i = 0; i < 4; i++)
        printf("lrintf %a = %ld\n", (double)vals[i], lrintf(vals[i]));
}

static void test_llrintf(void)
{
    float vals[] = {0.5f, 1.5f, 2.5f, -0.5f};
    for (int i = 0; i < 4; i++)
        printf("llrintf %a = %lld\n", (double)vals[i], llrintf(vals[i]));
}

static void test_roundf(void)
{
    float vals[] = {0.5f, 1.5f, 2.5f, -0.5f, -1.5f};
    for (int i = 0; i < 5; i++)
        printf("roundf %a = %a\n", (double)vals[i], (double)roundf(vals[i]));
}

static void test_lroundf(void)
{
    float vals[] = {0.5f, 1.5f, 2.5f, -0.5f};
    for (int i = 0; i < 4; i++)
        printf("lroundf %a = %ld\n", (double)vals[i], lroundf(vals[i]));
}

static void test_llroundf(void)
{
    float vals[] = {0.5f, 1.5f, 2.5f, -0.5f};
    for (int i = 0; i < 4; i++)
        printf("llroundf %a = %lld\n", (double)vals[i], llroundf(vals[i]));
}

static void test_truncf(void)
{
    float vals[] = {0.0f, 2.9f, -2.9f, 0.1f, -0.1f};
    for (int i = 0; i < 5; i++)
        printf("truncf %a = %a\n", (double)vals[i], (double)truncf(vals[i]));
}

/* ===== Float remainder ===== */
static void test_fmodf(void)
{
    float xs[] = {5.0f, -5.0f, 10.0f};
    float ys[] = {3.0f,  3.0f,  3.0f};
    for (int i = 0; i < 3; i++)
        printf("fmodf %a %a = %a\n", (double)xs[i], (double)ys[i], (double)fmodf(xs[i], ys[i]));
}

static void test_remainderf(void)
{
    float xs[] = {5.0f, -5.0f, 10.0f};
    float ys[] = {3.0f,  3.0f,  3.0f};
    for (int i = 0; i < 3; i++)
        printf("remainderf %a %a = %a\n", (double)xs[i], (double)ys[i], (double)remainderf(xs[i], ys[i]));
}

static void test_remquof(void)
{
    float xs[] = {5.0f, 10.0f};
    float ys[] = {3.0f,  3.0f};
    int q;
    for (int i = 0; i < 2; i++) {
        float r = remquof(xs[i], ys[i], &q);
        printf("remquof %a %a = %a quo=%d\n", (double)xs[i], (double)ys[i], (double)r, q);
    }
}

/* ===== Float manipulation ===== */
static void test_copysignf(void)
{
    printf("copysignf %a %a = %a\n", 1.0, -1.0, (double)copysignf(1.0f, -1.0f));
    printf("copysignf %a %a = %a\n", -1.0, 1.0, (double)copysignf(-1.0f, 1.0f));
}

static void test_nanf_func(void)
{
    float n = nanf("");
    printf("nanf = %a\n", (double)n);
}

static void test_nextafterf(void)
{
    printf("nextafterf %a %a = %a\n", 1.0, 2.0, (double)nextafterf(1.0f, 2.0f));
    printf("nextafterf %a %a = %a\n", 1.0, 0.0, (double)nextafterf(1.0f, 0.0f));
}

/* ===== Float min/max/dim ===== */
static void test_fdimf(void)
{
    printf("fdimf %a %a = %a\n", 5.0, 3.0, (double)fdimf(5.0f, 3.0f));
    printf("fdimf %a %a = %a\n", 3.0, 5.0, (double)fdimf(3.0f, 5.0f));
}

static void test_fmaxf(void)
{
    printf("fmaxf %a %a = %a\n", 2.0, 3.0, (double)fmaxf(2.0f, 3.0f));
    printf("fmaxf %a %a = %a\n", -2.0, -3.0, (double)fmaxf(-2.0f, -3.0f));
}

static void test_fminf(void)
{
    printf("fminf %a %a = %a\n", 2.0, 3.0, (double)fminf(2.0f, 3.0f));
    printf("fminf %a %a = %a\n", -2.0, -3.0, (double)fminf(-2.0f, -3.0f));
}

/* ===== Float fma ===== */
static void test_fmaf(void)
{
    printf("fmaf %a %a %a = %a\n", 2.0, 3.0, 4.0, (double)fmaf(2.0f, 3.0f, 4.0f));
    printf("fmaf %a %a %a = %a\n", -1.0, 5.0, 0.5, (double)fmaf(-1.0f, 5.0f, 0.5f));
}

/* ===== Complex double ===== */
static void test_cabs_func(void)
{
    double complex z1 = CMPLX(3.0, 4.0);
    double complex z2 = CMPLX(1.0, 1.0);
    double complex z3 = CMPLX(0.0, 0.0);
    printf("cabs (%a,%a) = %a\n", creal(z1), cimag(z1), cabs(z1));
    printf("cabs (%a,%a) = %a\n", creal(z2), cimag(z2), cabs(z2));
    printf("cabs (%a,%a) = %a\n", creal(z3), cimag(z3), cabs(z3));
}

static void test_cacos_func(void)
{
    double complex z = CMPLX(0.5, 0.5);
    double complex r = cacos(z);
    printf("cacos (%a,%a) = (%a,%a)\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_casin_func(void)
{
    double complex z = CMPLX(0.5, 0.5);
    double complex r = casin(z);
    printf("casin (%a,%a) = (%a,%a)\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_catan_func(void)
{
    double complex z = CMPLX(0.5, 0.5);
    double complex r = catan(z);
    printf("catan (%a,%a) = (%a,%a)\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_ccos_func(void)
{
    double complex z = CMPLX(1.0, 1.0);
    double complex r = ccos(z);
    printf("ccos (%a,%a) = (%a,%a)\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_csin_func(void)
{
    double complex z = CMPLX(1.0, 1.0);
    double complex r = csin(z);
    printf("csin (%a,%a) = (%a,%a)\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_ctan_func(void)
{
    double complex z = CMPLX(1.0, 1.0);
    double complex r = ctan(z);
    printf("ctan (%a,%a) = (%a,%a)\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_cacosh_func(void)
{
    double complex z = CMPLX(2.0, 1.0);
    double complex r = cacosh(z);
    printf("cacosh (%a,%a) = (%a,%a)\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_casinh_func(void)
{
    double complex z = CMPLX(1.0, 1.0);
    double complex r = casinh(z);
    printf("casinh (%a,%a) = (%a,%a)\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_catanh_func(void)
{
    double complex z = CMPLX(0.5, 0.5);
    double complex r = catanh(z);
    printf("catanh (%a,%a) = (%a,%a)\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_ccosh_func(void)
{
    double complex z = CMPLX(1.0, 1.0);
    double complex r = ccosh(z);
    printf("ccosh (%a,%a) = (%a,%a)\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_csinh_func(void)
{
    double complex z = CMPLX(1.0, 1.0);
    double complex r = csinh(z);
    printf("csinh (%a,%a) = (%a,%a)\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_ctanh_func(void)
{
    double complex z = CMPLX(1.0, 1.0);
    double complex r = ctanh(z);
    printf("ctanh (%a,%a) = (%a,%a)\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_cexp_func(void)
{
    double complex z1 = CMPLX(0.0, 0.0);
    double complex z2 = CMPLX(1.0, 0.0);
    double complex z3 = CMPLX(0.0, 3.14159265358979323846);
    double complex r1 = cexp(z1);
    double complex r2 = cexp(z2);
    double complex r3 = cexp(z3);
    printf("cexp (%a,%a) = (%a,%a)\n", creal(z1), cimag(z1), creal(r1), cimag(r1));
    printf("cexp (%a,%a) = (%a,%a)\n", creal(z2), cimag(z2), creal(r2), cimag(r2));
    printf("cexp (%a,%a) = (%a,%a)\n", creal(z3), cimag(z3), creal(r3), cimag(r3));
}

static void test_clog_func(void)
{
    double complex z1 = CMPLX(1.0, 0.0);
    double complex z2 = CMPLX(0.0, 1.0);
    double complex z3 = CMPLX(1.0, 1.0);
    double complex r1 = clog(z1);
    double complex r2 = clog(z2);
    double complex r3 = clog(z3);
    printf("clog (%a,%a) = (%a,%a)\n", creal(z1), cimag(z1), creal(r1), cimag(r1));
    printf("clog (%a,%a) = (%a,%a)\n", creal(z2), cimag(z2), creal(r2), cimag(r2));
    printf("clog (%a,%a) = (%a,%a)\n", creal(z3), cimag(z3), creal(r3), cimag(r3));
}

static void test_cpow_func(void)
{
    double complex z = CMPLX(2.0, 0.0);
    double complex w = CMPLX(3.0, 0.0);
    double complex r = cpow(z, w);
    printf("cpow (%a,%a) (%a,%a) = (%a,%a)\n", creal(z), cimag(z), creal(w), cimag(w), creal(r), cimag(r));
}

static void test_csqrt_func(void)
{
    double complex z1 = CMPLX(4.0, 0.0);
    double complex z2 = CMPLX(0.0, 1.0);
    double complex z3 = CMPLX(-1.0, 0.0);
    double complex r1 = csqrt(z1);
    double complex r2 = csqrt(z2);
    double complex r3 = csqrt(z3);
    printf("csqrt (%a,%a) = (%a,%a)\n", creal(z1), cimag(z1), creal(r1), cimag(r1));
    printf("csqrt (%a,%a) = (%a,%a)\n", creal(z2), cimag(z2), creal(r2), cimag(r2));
    printf("csqrt (%a,%a) = (%a,%a)\n", creal(z3), cimag(z3), creal(r3), cimag(r3));
}

static void test_carg_func(void)
{
    double complex z1 = CMPLX(1.0, 0.0);
    double complex z2 = CMPLX(0.0, 1.0);
    double complex z3 = CMPLX(-1.0, 0.0);
    printf("carg (%a,%a) = %a\n", creal(z1), cimag(z1), carg(z1));
    printf("carg (%a,%a) = %a\n", creal(z2), cimag(z2), carg(z2));
    printf("carg (%a,%a) = %a\n", creal(z3), cimag(z3), carg(z3));
}

static void test_conj_func(void)
{
    double complex z = CMPLX(1.0, 2.0);
    double complex r = conj(z);
    printf("conj (%a,%a) = (%a,%a)\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_cproj_func(void)
{
    double complex z = CMPLX(1.0, 2.0);
    double complex r = cproj(z);
    printf("cproj (%a,%a) = (%a,%a)\n", creal(z), cimag(z), creal(r), cimag(r));
}

static void test_creal_cimag(void)
{
    double complex z = CMPLX(3.14, 2.72);
    printf("creal (%a,%a) = %a\n", creal(z), cimag(z), creal(z));
    printf("cimag (%a,%a) = %a\n", creal(z), cimag(z), cimag(z));
}

/* ===== Complex float ===== */
static void test_cabsf_func(void)
{
    float complex z = CMPLXF(3.0f, 4.0f);
    printf("cabsf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)cabsf(z));
}

static void test_cacosf_func(void)
{
    float complex z = CMPLXF(0.5f, 0.5f);
    float complex r = cacosf(z);
    printf("cacosf (%a,%a) = (%a,%a)\n", (double)crealf(z), (double)cimagf(z), (double)crealf(r), (double)cimagf(r));
}

static void test_casinf_func(void)
{
    float complex z = CMPLXF(0.5f, 0.5f);
    float complex r = casinf(z);
    printf("casinf (%a,%a) = (%a,%a)\n", (double)crealf(z), (double)cimagf(z), (double)crealf(r), (double)cimagf(r));
}

static void test_catanf_func(void)
{
    float complex z = CMPLXF(0.5f, 0.5f);
    float complex r = catanf(z);
    printf("catanf (%a,%a) = (%a,%a)\n", (double)crealf(z), (double)cimagf(z), (double)crealf(r), (double)cimagf(r));
}

static void test_ccosf_func(void)
{
    float complex z = CMPLXF(1.0f, 1.0f);
    float complex r = ccosf(z);
    printf("ccosf (%a,%a) = (%a,%a)\n", (double)crealf(z), (double)cimagf(z), (double)crealf(r), (double)cimagf(r));
}

static void test_csinf_func(void)
{
    float complex z = CMPLXF(1.0f, 1.0f);
    float complex r = csinf(z);
    printf("csinf (%a,%a) = (%a,%a)\n", (double)crealf(z), (double)cimagf(z), (double)crealf(r), (double)cimagf(r));
}

static void test_ctanf_func(void)
{
    float complex z = CMPLXF(1.0f, 1.0f);
    float complex r = ctanf(z);
    printf("ctanf (%a,%a) = (%a,%a)\n", (double)crealf(z), (double)cimagf(z), (double)crealf(r), (double)cimagf(r));
}

static void test_cacoshf_func(void)
{
    float complex z = CMPLXF(2.0f, 1.0f);
    float complex r = cacoshf(z);
    printf("cacoshf (%a,%a) = (%a,%a)\n", (double)crealf(z), (double)cimagf(z), (double)crealf(r), (double)cimagf(r));
}

static void test_casinhf_func(void)
{
    float complex z = CMPLXF(1.0f, 1.0f);
    float complex r = casinhf(z);
    printf("casinhf (%a,%a) = (%a,%a)\n", (double)crealf(z), (double)cimagf(z), (double)crealf(r), (double)cimagf(r));
}

static void test_catanhf_func(void)
{
    float complex z = CMPLXF(0.5f, 0.5f);
    float complex r = catanhf(z);
    printf("catanhf (%a,%a) = (%a,%a)\n", (double)crealf(z), (double)cimagf(z), (double)crealf(r), (double)cimagf(r));
}

static void test_ccoshf_func(void)
{
    float complex z = CMPLXF(1.0f, 1.0f);
    float complex r = ccoshf(z);
    printf("ccoshf (%a,%a) = (%a,%a)\n", (double)crealf(z), (double)cimagf(z), (double)crealf(r), (double)cimagf(r));
}

static void test_csinhf_func(void)
{
    float complex z = CMPLXF(1.0f, 1.0f);
    float complex r = csinhf(z);
    printf("csinhf (%a,%a) = (%a,%a)\n", (double)crealf(z), (double)cimagf(z), (double)crealf(r), (double)cimagf(r));
}

static void test_ctanhf_func(void)
{
    float complex z = CMPLXF(1.0f, 1.0f);
    float complex r = ctanhf(z);
    printf("ctanhf (%a,%a) = (%a,%a)\n", (double)crealf(z), (double)cimagf(z), (double)crealf(r), (double)cimagf(r));
}

static void test_cexpf_func(void)
{
    float complex z1 = CMPLXF(0.0f, 0.0f);
    float complex z2 = CMPLXF(1.0f, 0.0f);
    float complex r1 = cexpf(z1);
    float complex r2 = cexpf(z2);
    printf("cexpf (%a,%a) = (%a,%a)\n", (double)crealf(z1), (double)cimagf(z1), (double)crealf(r1), (double)cimagf(r1));
    printf("cexpf (%a,%a) = (%a,%a)\n", (double)crealf(z2), (double)cimagf(z2), (double)crealf(r2), (double)cimagf(r2));
}

static void test_clogf_func(void)
{
    float complex z1 = CMPLXF(1.0f, 0.0f);
    float complex z2 = CMPLXF(0.0f, 1.0f);
    float complex r1 = clogf(z1);
    float complex r2 = clogf(z2);
    printf("clogf (%a,%a) = (%a,%a)\n", (double)crealf(z1), (double)cimagf(z1), (double)crealf(r1), (double)cimagf(r1));
    printf("clogf (%a,%a) = (%a,%a)\n", (double)crealf(z2), (double)cimagf(z2), (double)crealf(r2), (double)cimagf(r2));
}

static void test_cpowf_func(void)
{
    float complex z = CMPLXF(2.0f, 0.0f);
    float complex w = CMPLXF(3.0f, 0.0f);
    float complex r = cpowf(z, w);
    printf("cpowf (%a,%a) (%a,%a) = (%a,%a)\n", (double)crealf(z), (double)cimagf(z), (double)crealf(w), (double)cimagf(w), (double)crealf(r), (double)cimagf(r));
}

static void test_csqrtf_func(void)
{
    float complex z1 = CMPLXF(4.0f, 0.0f);
    float complex z2 = CMPLXF(-1.0f, 0.0f);
    float complex r1 = csqrtf(z1);
    float complex r2 = csqrtf(z2);
    printf("csqrtf (%a,%a) = (%a,%a)\n", (double)crealf(z1), (double)cimagf(z1), (double)crealf(r1), (double)cimagf(r1));
    printf("csqrtf (%a,%a) = (%a,%a)\n", (double)crealf(z2), (double)cimagf(z2), (double)crealf(r2), (double)cimagf(r2));
}

static void test_cargf_func(void)
{
    float complex z1 = CMPLXF(1.0f, 0.0f);
    float complex z2 = CMPLXF(0.0f, 1.0f);
    printf("cargf (%a,%a) = %a\n", (double)crealf(z1), (double)cimagf(z1), (double)cargf(z1));
    printf("cargf (%a,%a) = %a\n", (double)crealf(z2), (double)cimagf(z2), (double)cargf(z2));
}

static void test_conjf_func(void)
{
    float complex z = CMPLXF(1.0f, 2.0f);
    float complex r = conjf(z);
    printf("conjf (%a,%a) = (%a,%a)\n", (double)crealf(z), (double)cimagf(z), (double)crealf(r), (double)cimagf(r));
}

static void test_cprojf_func(void)
{
    float complex z = CMPLXF(1.0f, 2.0f);
    float complex r = cprojf(z);
    printf("cprojf (%a,%a) = (%a,%a)\n", (double)crealf(z), (double)cimagf(z), (double)crealf(r), (double)cimagf(r));
}

static void test_crealf_cimagf(void)
{
    float complex z = CMPLXF(3.14f, 2.72f);
    printf("crealf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)crealf(z));
    printf("cimagf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)cimagf(z));
}

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

    /* Double hyperbolic */
    test_acosh();
    test_asinh();
    test_atanh();
    test_cosh();
    test_sinh();
    test_tanh();

    /* Double exponential / logarithmic */
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

    /* Double power / absolute */
    test_cbrt();
    test_fabs();
    test_hypot();
    test_pow();
    test_sqrt();

    /* Double error / gamma */
    test_erf();
    test_erfc();
    test_lgamma();
    test_tgamma();

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

    /* Double remainder */
    test_fmod();
    test_remainder();
    test_remquo();

    /* Double manipulation */
    test_copysign();
    test_nan_func();
    test_nextafter();

    /* Double min/max/dim */
    test_fdim();
    test_fmax();
    test_fmin();

    /* Double fma */
    test_fma();

    /* Double Bessel */
    test_j0();
    test_j1();
    test_jn();
    test_y0();
    test_y1();
    test_yn();

    /* Float trigonometric */
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

    /* Float exponential / logarithmic */
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

    /* Float power / absolute */
    test_cbrtf();
    test_fabsf();
    test_hypotf();
    test_powf();
    test_sqrtf();

    /* Float error / gamma */
    test_erff();
    test_erfcf();
    test_lgammaf();
    test_tgammaf();

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

    /* Float remainder */
    test_fmodf();
    test_remainderf();
    test_remquof();

    /* Float manipulation */
    test_copysignf();
    test_nanf_func();
    test_nextafterf();

    /* Float min/max/dim */
    test_fdimf();
    test_fmaxf();
    test_fminf();

    /* Float fma */
    test_fmaf();

    /* Complex double */
    test_cabs_func();
    test_cacos_func();
    test_casin_func();
    test_catan_func();
    test_ccos_func();
    test_csin_func();
    test_ctan_func();
    test_cacosh_func();
    test_casinh_func();
    test_catanh_func();
    test_ccosh_func();
    test_csinh_func();
    test_ctanh_func();
    test_cexp_func();
    test_clog_func();
    test_cpow_func();
    test_csqrt_func();
    test_carg_func();
    test_conj_func();
    test_cproj_func();
    test_creal_cimag();

    /* Complex float */
    test_cabsf_func();
    test_cacosf_func();
    test_casinf_func();
    test_catanf_func();
    test_ccosf_func();
    test_csinf_func();
    test_ctanf_func();
    test_cacoshf_func();
    test_casinhf_func();
    test_catanhf_func();
    test_ccoshf_func();
    test_csinhf_func();
    test_ctanhf_func();
    test_cexpf_func();
    test_clogf_func();
    test_cpowf_func();
    test_csqrtf_func();
    test_cargf_func();
    test_conjf_func();
    test_cprojf_func();
    test_crealf_cimagf();

    return 0;
}
