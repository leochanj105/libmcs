/* Auto-generated from SDD special case tables */
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static int total = 0, passed = 0, failed = 0;

static int double_eq(double a, double b) {
    if (isnan(a) && isnan(b)) return 1;
    if (isinf(a) && isinf(b)) return (a > 0) == (b > 0);
    /* Bitwise comparison for ±0 */
    uint64_t ai, bi;
    memcpy(&ai, &a, 8);
    memcpy(&bi, &b, 8);
    return ai == bi;
}

static int float_eq(float a, float b) {
    if (isnan(a) && isnan(b)) return 1;
    if (isinf(a) && isinf(b)) return (a > 0) == (b > 0);
    uint32_t ai, bi;
    memcpy(&ai, &a, 4);
    memcpy(&bi, &b, 4);
    return ai == bi;
}

#define TEST_D1(func, x, expected) do { \
    total++; \
    double result = func(x); \
    if (double_eq(result, expected)) { passed++; } \
    else { failed++; printf("FAIL %s(%a) = %a, expected %a\n", #func, (double)(x), result, (double)(expected)); } \
} while(0)

#define TEST_D2(func, x, y, expected) do { \
    total++; \
    double result = func(x, y); \
    if (double_eq(result, expected)) { passed++; } \
    else { failed++; printf("FAIL %s(%a, %a) = %a, expected %a\n", #func, (double)(x), (double)(y), result, (double)(expected)); } \
} while(0)

#define TEST_F1(func, x, expected) do { \
    total++; \
    float result = func(x); \
    if (float_eq(result, expected)) { passed++; } \
    else { failed++; printf("FAIL %s(%a) = %a, expected %a\n", #func, (double)(x), (double)result, (double)(expected)); } \
} while(0)

#define TEST_F2(func, x, y, expected) do { \
    total++; \
    float result = func(x, y); \
    if (float_eq(result, expected)) { passed++; } \
    else { failed++; printf("FAIL %s(%a, %a) = %a, expected %a\n", #func, (double)(x), (double)(y), (double)result, (double)(expected)); } \
} while(0)

#define TEST_NAN_D1(func, x) do { \
    total++; \
    double result = func(x); \
    if (isnan(result)) { passed++; } \
    else { failed++; printf("FAIL %s(%a) = %a, expected NaN\n", #func, (double)(x), result); } \
} while(0)

#define TEST_NAN_D2(func, x, y) do { \
    total++; \
    double result = func(x, y); \
    if (isnan(result)) { passed++; } \
    else { failed++; printf("FAIL %s(%a, %a) = %a, expected NaN\n", #func, (double)(x), (double)(y), result); } \
} while(0)

#define TEST_NAN_F1(func, x) do { \
    total++; \
    float result = func(x); \
    if (isnan(result)) { passed++; } \
    else { failed++; printf("FAIL %s(%a) = %a, expected NaN\n", #func, (double)(x), (double)result); } \
} while(0)

#define TEST_NAN_F2(func, x, y) do { \
    total++; \
    float result = func(x, y); \
    if (isnan(result)) { passed++; } \
    else { failed++; printf("FAIL %s(%a, %a) = %a, expected NaN\n", #func, (double)(x), (double)(y), (double)result); } \
} while(0)

int main(void) {
    TEST_D1(acos, 1.0, +0.0);
    TEST_NAN_D1(acos, INFINITY);
    TEST_NAN_D1(acos, -INFINITY);
    TEST_NAN_D1(acos, NAN);
    TEST_D1(asin, +0.0, +0.0);
    TEST_D1(asin, -0.0, -0.0);
    TEST_NAN_D1(asin, INFINITY);
    TEST_NAN_D1(asin, -INFINITY);
    TEST_NAN_D1(asin, NAN);
    TEST_D1(atan, +0.0, +0.0);
    TEST_D1(atan, -0.0, -0.0);
    TEST_D1(atan, -INFINITY, -M_PI/2.0);
    TEST_D1(atan, INFINITY, M_PI/2.0);
    TEST_NAN_D1(atan, NAN);
    TEST_D2(atan2, -0.0, -0.0, -M_PI);
    TEST_D2(atan2, -0.0, +0.0, M_PI);
    TEST_D2(atan2, +0.0, -0.0, -0.0);
    TEST_D2(atan2, +0.0, +0.0, +0.0);
    TEST_D2(atan2, INFINITY, -INFINITY, -M_PI/4.0);
    TEST_D2(atan2, INFINITY, INFINITY, M_PI/4.0);
    TEST_D1(cos, +0.0, 1);
    TEST_D1(cos, -0.0, 1);
    TEST_NAN_D1(cos, INFINITY);
    TEST_NAN_D1(cos, -INFINITY);
    TEST_NAN_D1(cos, NAN);
    TEST_D1(sin, +0.0, +0.0);
    TEST_D1(sin, -0.0, -0.0);
    TEST_NAN_D1(sin, INFINITY);
    TEST_NAN_D1(sin, -INFINITY);
    TEST_NAN_D1(sin, NAN);
    TEST_D1(tan, +0.0, +0.0);
    TEST_D1(tan, -0.0, -0.0);
    TEST_NAN_D1(tan, INFINITY);
    TEST_NAN_D1(tan, -INFINITY);
    TEST_NAN_D1(tan, NAN);
    TEST_D1(acosh, 1.0, +0.0);
    TEST_NAN_D1(acosh, -INFINITY);
    TEST_D1(acosh, INFINITY, INFINITY);
    TEST_NAN_D1(acosh, NAN);
    TEST_D1(asinh, +0.0, +0.0);
    TEST_D1(asinh, -0.0, -0.0);
    TEST_D1(asinh, INFINITY, INFINITY);
    TEST_D1(asinh, -INFINITY, -INFINITY);
    TEST_NAN_D1(asinh, NAN);
    TEST_D1(atanh, +0.0, +0.0);
    TEST_D1(atanh, -0.0, -0.0);
    TEST_NAN_D1(atanh, INFINITY);
    TEST_NAN_D1(atanh, -INFINITY);
    TEST_NAN_D1(atanh, NAN);
    TEST_D1(cosh, +0.0, 1);
    TEST_D1(cosh, -0.0, 1);
    TEST_D1(cosh, INFINITY, INFINITY);
    TEST_D1(cosh, -INFINITY, INFINITY);
    TEST_NAN_D1(cosh, NAN);
    TEST_D1(sinh, +0.0, +0.0);
    TEST_D1(sinh, -0.0, -0.0);
    TEST_D1(sinh, INFINITY, INFINITY);
    TEST_D1(sinh, -INFINITY, -INFINITY);
    TEST_NAN_D1(sinh, NAN);
    TEST_D1(tanh, +0.0, +0.0);
    TEST_D1(tanh, -0.0, -0.0);
    TEST_NAN_D1(tanh, NAN);
    TEST_D1(exp, +0.0, 1);
    TEST_D1(exp, -0.0, 1);
    TEST_D1(exp, -INFINITY, +0.0);
    TEST_D1(exp, INFINITY, INFINITY);
    TEST_NAN_D1(exp, NAN);
    TEST_D1(exp2, +0.0, 1);
    TEST_D1(exp2, -0.0, 1);
    TEST_D1(exp2, -INFINITY, +0.0);
    TEST_D1(exp2, INFINITY, INFINITY);
    TEST_NAN_D1(exp2, NAN);
    TEST_D1(expm1, +0.0, +0.0);
    TEST_D1(expm1, -0.0, +0.0);
    TEST_D1(expm1, -INFINITY, -1.0);
    TEST_D1(expm1, INFINITY, INFINITY);
    TEST_NAN_D1(expm1, NAN);
    TEST_D1(log, +0.0, -INFINITY);
    TEST_D1(log, -0.0, -INFINITY);
    TEST_D1(log, 1, +0.0);
    TEST_D1(log, INFINITY, INFINITY);
    TEST_NAN_D1(log, NAN);
    TEST_D1(log10, +0.0, -INFINITY);
    TEST_D1(log10, -0.0, -INFINITY);
    TEST_D1(log10, 1, +0.0);
    TEST_D1(log10, INFINITY, INFINITY);
    TEST_NAN_D1(log10, NAN);
    TEST_D1(log1p, -1.0, -INFINITY);
    TEST_D1(log1p, +0.0, +0.0);
    TEST_D1(log1p, -0.0, -0.0);
    TEST_D1(log1p, INFINITY, INFINITY);
    TEST_NAN_D1(log1p, NAN);
    TEST_D1(log2, +0.0, -INFINITY);
    TEST_D1(log2, -0.0, -INFINITY);
    TEST_D1(log2, 1, +0.0);
    TEST_D1(log2, INFINITY, INFINITY);
    TEST_NAN_D1(log2, NAN);
    TEST_D1(logb, +0.0, -INFINITY);
    TEST_D1(logb, -0.0, -INFINITY);
    TEST_D1(logb, INFINITY, INFINITY);
    TEST_D1(logb, -INFINITY, INFINITY);
    TEST_NAN_D1(logb, NAN);
    TEST_D1(cbrt, +0.0, +0.0);
    TEST_D1(cbrt, -0.0, -0.0);
    TEST_D1(cbrt, INFINITY, INFINITY);
    TEST_D1(cbrt, -INFINITY, -INFINITY);
    TEST_NAN_D1(cbrt, NAN);
    TEST_D1(fabs, +0.0, +0.0);
    TEST_D1(fabs, -0.0, +0.0);
    TEST_D1(fabs, INFINITY, INFINITY);
    TEST_D1(fabs, -INFINITY, INFINITY);
    TEST_NAN_D1(fabs, NAN);
    TEST_NAN_D1(fabs, __builtin_nans(""));
    TEST_D2(pow, 1.0, NAN, 1.0);
    TEST_NAN_D2(pow, 1.0, __builtin_nans(""));
    TEST_D1(sqrt, +0.0, +0.0);
    TEST_D1(sqrt, -0.0, -0.0);
    TEST_NAN_D1(sqrt, -INFINITY);
    TEST_D1(sqrt, INFINITY, INFINITY);
    TEST_NAN_D1(sqrt, NAN);
    TEST_D1(erf, +0.0, +0.0);
    TEST_D1(erf, -0.0, -0.0);
    TEST_D1(erf, INFINITY, INFINITY);
    TEST_D1(erf, -INFINITY, -INFINITY);
    TEST_NAN_D1(erf, NAN);
    TEST_D1(erfc, +0.0, 1.0);
    TEST_D1(erfc, -0.0, 1.0);
    TEST_D1(erfc, -INFINITY, 2.0);
    TEST_D1(erfc, INFINITY, +0.0);
    TEST_NAN_D1(erfc, NAN);
    TEST_D1(lgamma, +0.0, INFINITY);
    TEST_D1(lgamma, -0.0, INFINITY);
    TEST_D1(lgamma, 1.0, +0.0);
    TEST_D1(lgamma, 2.0, +0.0);
    TEST_D1(lgamma, INFINITY, INFINITY);
    TEST_D1(lgamma, -INFINITY, INFINITY);
    TEST_NAN_D1(lgamma, NAN);
    TEST_NAN_D1(tgamma, -INFINITY);
    TEST_D1(tgamma, INFINITY, INFINITY);
    TEST_NAN_D1(tgamma, NAN);
    TEST_D1(ceil, +0.0, +0.0);
    TEST_D1(ceil, -0.0, -0.0);
    TEST_D1(ceil, INFINITY, INFINITY);
    TEST_D1(ceil, -INFINITY, -INFINITY);
    TEST_NAN_D1(ceil, NAN);
    TEST_D1(floor, +0.0, +0.0);
    TEST_D1(floor, -0.0, -0.0);
    TEST_D1(floor, INFINITY, INFINITY);
    TEST_D1(floor, -INFINITY, -INFINITY);
    TEST_NAN_D1(floor, NAN);
    TEST_D1(nearbyint, +0.0, +0.0);
    TEST_D1(nearbyint, -0.0, -0.0);
    TEST_D1(nearbyint, INFINITY, INFINITY);
    TEST_D1(nearbyint, -INFINITY, -INFINITY);
    TEST_NAN_D1(nearbyint, NAN);
    TEST_D1(rint, +0.0, +0.0);
    TEST_D1(rint, -0.0, -0.0);
    TEST_D1(rint, INFINITY, INFINITY);
    TEST_D1(rint, -INFINITY, -INFINITY);
    TEST_NAN_D1(rint, NAN);
    TEST_D1(round, +0.0, +0.0);
    TEST_D1(round, -0.0, -0.0);
    TEST_D1(round, INFINITY, INFINITY);
    TEST_D1(round, -INFINITY, -INFINITY);
    TEST_NAN_D1(round, NAN);
    TEST_D1(trunc, +0.0, +0.0);
    TEST_D1(trunc, -0.0, -0.0);
    TEST_D1(trunc, INFINITY, INFINITY);
    TEST_D1(trunc, -INFINITY, -INFINITY);
    TEST_NAN_D1(trunc, NAN);
    TEST_D2(fdim, INFINITY, -INFINITY, INFINITY);
    TEST_D2(fdim, INFINITY, INFINITY, +0.0);
    TEST_NAN_D2(fmax, NAN, NAN);
    TEST_NAN_D2(fmin, NAN, NAN);
    TEST_D1(j0, INFINITY, +0.0);
    TEST_D1(j0, -INFINITY, +0.0);
    TEST_NAN_D1(j0, NAN);
    TEST_D1(j1, INFINITY, +0.0);
    TEST_D1(j1, -INFINITY, +0.0);
    TEST_NAN_D1(j1, NAN);
    TEST_NAN_D1(y0, -INFINITY);
    TEST_D1(y0, +0.0, -INFINITY);
    TEST_D1(y0, -0.0, -INFINITY);
    TEST_D1(y0, INFINITY, +0.0);
    TEST_NAN_D1(y0, NAN);
    TEST_NAN_D1(y1, -INFINITY);
    TEST_D1(y1, +0.0, -INFINITY);
    TEST_D1(y1, -0.0, -INFINITY);
    TEST_D1(y1, INFINITY, +0.0);
    TEST_NAN_D1(y1, NAN);
    TEST_F1(acosf, 1.0f, +0.0f);
    TEST_NAN_F1(acosf, INFINITY);
    TEST_NAN_F1(acosf, -INFINITY);
    TEST_NAN_F1(acosf, NAN);
    TEST_F1(asinf, +0.0f, +0.0f);
    TEST_F1(asinf, -0.0f, -0.0f);
    TEST_NAN_F1(asinf, INFINITY);
    TEST_NAN_F1(asinf, -INFINITY);
    TEST_NAN_F1(asinf, NAN);
    TEST_F1(atanf, +0.0f, +0.0f);
    TEST_F1(atanf, -0.0f, -0.0f);
    TEST_F1(atanf, -INFINITY, -M_PI/2.0f);
    TEST_F1(atanf, INFINITY, M_PI/2.0f);
    TEST_NAN_F1(atanf, NAN);
    TEST_F2(atan2f, -0.0f, -0.0f, -M_PI);
    TEST_F2(atan2f, -0.0f, +0.0f, M_PI);
    TEST_F2(atan2f, +0.0f, -0.0f, -0.0f);
    TEST_F2(atan2f, +0.0f, +0.0f, +0.0f);
    TEST_F2(atan2f, INFINITY, -INFINITY, -M_PI/4.0f);
    TEST_F2(atan2f, INFINITY, INFINITY, M_PI/4.0f);
    TEST_F1(cosf, +0.0f, 1.0f);
    TEST_F1(cosf, -0.0f, 1.0f);
    TEST_NAN_F1(cosf, INFINITY);
    TEST_NAN_F1(cosf, -INFINITY);
    TEST_NAN_F1(cosf, NAN);
    TEST_F1(sinf, +0.0f, +0.0f);
    TEST_F1(sinf, -0.0f, -0.0f);
    TEST_NAN_F1(sinf, INFINITY);
    TEST_NAN_F1(sinf, -INFINITY);
    TEST_NAN_F1(sinf, NAN);
    TEST_F1(tanf, +0.0f, +0.0f);
    TEST_F1(tanf, -0.0f, -0.0f);
    TEST_NAN_F1(tanf, INFINITY);
    TEST_NAN_F1(tanf, -INFINITY);
    TEST_NAN_F1(tanf, NAN);
    TEST_F1(acoshf, 1.0f, +0.0f);
    TEST_NAN_F1(acoshf, -INFINITY);
    TEST_F1(acoshf, INFINITY, INFINITY);
    TEST_NAN_F1(acoshf, NAN);
    TEST_F1(asinhf, +0.0f, +0.0f);
    TEST_F1(asinhf, -0.0f, -0.0f);
    TEST_F1(asinhf, INFINITY, INFINITY);
    TEST_F1(asinhf, -INFINITY, -INFINITY);
    TEST_NAN_F1(asinhf, NAN);
    TEST_F1(atanhf, +0.0f, +0.0f);
    TEST_F1(atanhf, -0.0f, -0.0f);
    TEST_NAN_F1(atanhf, INFINITY);
    TEST_NAN_F1(atanhf, -INFINITY);
    TEST_NAN_F1(atanhf, NAN);
    TEST_F1(coshf, +0.0f, 1.0f);
    TEST_F1(coshf, -0.0f, 1.0f);
    TEST_F1(coshf, INFINITY, INFINITY);
    TEST_F1(coshf, -INFINITY, INFINITY);
    TEST_NAN_F1(coshf, NAN);
    TEST_F1(sinhf, +0.0f, +0.0f);
    TEST_F1(sinhf, -0.0f, -0.0f);
    TEST_F1(sinhf, INFINITY, INFINITY);
    TEST_F1(sinhf, -INFINITY, -INFINITY);
    TEST_NAN_F1(sinhf, NAN);
    TEST_F1(tanhf, +0.0f, +0.0f);
    TEST_F1(tanhf, -0.0f, -0.0f);
    TEST_NAN_F1(tanhf, NAN);
    TEST_F1(expf, +0.0f, 1.0f);
    TEST_F1(expf, -0.0f, 1.0f);
    TEST_F1(expf, -INFINITY, +0.0f);
    TEST_F1(expf, INFINITY, INFINITY);
    TEST_NAN_F1(expf, NAN);
    TEST_F1(exp2f, +0.0f, 1.0f);
    TEST_F1(exp2f, -0.0f, 1.0f);
    TEST_F1(exp2f, -INFINITY, +0.0f);
    TEST_F1(exp2f, INFINITY, INFINITY);
    TEST_NAN_F1(exp2f, NAN);
    TEST_F1(expm1f, +0.0f, +0.0f);
    TEST_F1(expm1f, -0.0f, +0.0f);
    TEST_F1(expm1f, -INFINITY, -1.0f);
    TEST_F1(expm1f, INFINITY, INFINITY);
    TEST_NAN_F1(expm1f, NAN);
    TEST_F1(logf, +0.0f, -INFINITY);
    TEST_F1(logf, -0.0f, -INFINITY);
    TEST_F1(logf, 1.0f, +0.0f);
    TEST_F1(logf, INFINITY, INFINITY);
    TEST_NAN_F1(logf, NAN);
    TEST_F1(log10f, +0.0f, -INFINITY);
    TEST_F1(log10f, -0.0f, -INFINITY);
    TEST_F1(log10f, 1.0f, +0.0f);
    TEST_F1(log10f, INFINITY, INFINITY);
    TEST_NAN_F1(log10f, NAN);
    TEST_F1(log1pf, -1.0f, -INFINITY);
    TEST_F1(log1pf, +0.0f, +0.0f);
    TEST_F1(log1pf, -0.0f, -0.0f);
    TEST_F1(log1pf, INFINITY, INFINITY);
    TEST_NAN_F1(log1pf, NAN);
    TEST_F1(log2f, +0.0f, -INFINITY);
    TEST_F1(log2f, -0.0f, -INFINITY);
    TEST_F1(log2f, 1.0f, +0.0f);
    TEST_F1(log2f, INFINITY, INFINITY);
    TEST_NAN_F1(log2f, NAN);
    TEST_F1(logbf, +0.0f, -INFINITY);
    TEST_F1(logbf, -0.0f, -INFINITY);
    TEST_F1(logbf, INFINITY, INFINITY);
    TEST_F1(logbf, -INFINITY, INFINITY);
    TEST_NAN_F1(logbf, NAN);
    TEST_F1(cbrtf, +0.0f, +0.0f);
    TEST_F1(cbrtf, -0.0f, -0.0f);
    TEST_F1(cbrtf, INFINITY, INFINITY);
    TEST_F1(cbrtf, -INFINITY, -INFINITY);
    TEST_NAN_F1(cbrtf, NAN);
    TEST_F1(fabsf, +0.0f, +0.0f);
    TEST_F1(fabsf, -0.0f, +0.0f);
    TEST_F1(fabsf, INFINITY, INFINITY);
    TEST_F1(fabsf, -INFINITY, INFINITY);
    TEST_NAN_F1(fabsf, NAN);
    TEST_NAN_F1(fabsf, __builtin_nans(""));
    TEST_F2(powf, 1.0f, NAN, 1.0f);
    TEST_NAN_F2(powf, 1.0f, __builtin_nans(""));
    TEST_F1(sqrtf, +0.0f, +0.0f);
    TEST_F1(sqrtf, -0.0f, -0.0f);
    TEST_NAN_F1(sqrtf, -INFINITY);
    TEST_F1(sqrtf, INFINITY, INFINITY);
    TEST_NAN_F1(sqrtf, NAN);
    TEST_F1(erff, +0.0f, +0.0f);
    TEST_F1(erff, -0.0f, -0.0f);
    TEST_F1(erff, INFINITY, INFINITY);
    TEST_F1(erff, -INFINITY, -INFINITY);
    TEST_NAN_F1(erff, NAN);
    TEST_F1(erfcf, +0.0f, 1.0f);
    TEST_F1(erfcf, -0.0f, 1.0f);
    TEST_F1(erfcf, -INFINITY, 2.0f);
    TEST_F1(erfcf, INFINITY, +0.0f);
    TEST_NAN_F1(erfcf, NAN);
    TEST_F1(lgammaf, +0.0f, INFINITY);
    TEST_F1(lgammaf, -0.0f, INFINITY);
    TEST_F1(lgammaf, 1.0f, +0.0f);
    TEST_F1(lgammaf, 2.0f, +0.0f);
    TEST_F1(lgammaf, INFINITY, INFINITY);
    TEST_F1(lgammaf, -INFINITY, INFINITY);
    TEST_NAN_F1(lgammaf, NAN);
    TEST_NAN_F1(tgammaf, -INFINITY);
    TEST_F1(tgammaf, INFINITY, INFINITY);
    TEST_NAN_F1(tgammaf, NAN);
    TEST_F1(ceilf, +0.0f, +0.0f);
    TEST_F1(ceilf, -0.0f, -0.0f);
    TEST_F1(ceilf, INFINITY, INFINITY);
    TEST_F1(ceilf, -INFINITY, -INFINITY);
    TEST_NAN_F1(ceilf, NAN);
    TEST_F1(floorf, +0.0f, +0.0f);
    TEST_F1(floorf, -0.0f, -0.0f);
    TEST_F1(floorf, INFINITY, INFINITY);
    TEST_F1(floorf, -INFINITY, -INFINITY);
    TEST_NAN_F1(floorf, NAN);
    TEST_F1(nearbyintf, +0.0f, +0.0f);
    TEST_F1(nearbyintf, -0.0f, -0.0f);
    TEST_F1(nearbyintf, INFINITY, INFINITY);
    TEST_F1(nearbyintf, -INFINITY, -INFINITY);
    TEST_NAN_F1(nearbyintf, NAN);
    TEST_F1(rintf, +0.0f, +0.0f);
    TEST_F1(rintf, -0.0f, -0.0f);
    TEST_F1(rintf, INFINITY, INFINITY);
    TEST_F1(rintf, -INFINITY, -INFINITY);
    TEST_NAN_F1(rintf, NAN);
    TEST_F1(roundf, +0.0f, +0.0f);
    TEST_F1(roundf, -0.0f, -0.0f);
    TEST_F1(roundf, INFINITY, INFINITY);
    TEST_F1(roundf, -INFINITY, -INFINITY);
    TEST_NAN_F1(roundf, NAN);
    TEST_F1(truncf, +0.0f, +0.0f);
    TEST_F1(truncf, -0.0f, -0.0f);
    TEST_F1(truncf, INFINITY, INFINITY);
    TEST_F1(truncf, -INFINITY, -INFINITY);
    TEST_NAN_F1(truncf, NAN);
    TEST_F2(fdimf, INFINITY, -INFINITY, INFINITY);
    TEST_F2(fdimf, INFINITY, INFINITY, +0.0f);
    TEST_NAN_F2(fmaxf, NAN, NAN);
    TEST_NAN_F2(fminf, NAN, NAN);

    printf("\nSDD Special Case Tests: %d passed, %d failed out of %d\n", passed, failed, total);
    return failed > 0 ? 1 : 0;
}
