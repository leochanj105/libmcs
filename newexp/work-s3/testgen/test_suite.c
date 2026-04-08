/* test_suite.c — comprehensive test suite for libmcs */
/* Covers all public and bridge-accessible static functions. */
/* All float/double results printed in %a hex float format. */

#include "/home/leochanj/Desktop/libmcs/libm/include/math.h"
#include "/home/leochanj/Desktop/libmcs/libm/include/complex.h"
#include "test_bridge.h"
#include <stdio.h>
#include <stdint.h>

/* ===== Helpers ===== */
#define POS_INF  (1.0/0.0)
#define NEG_INF  (-1.0/0.0)
#define POS_INFF (1.0f/0.0f)
#define NEG_INFF (-1.0f/0.0f)
/* smallest positive subnormal double */
#define DBL_DENORM  5e-324
/* smallest positive subnormal float */
#define FLT_DENORM  1.4e-45f

/* Print helper for complex double */
static void print_cdbl(const char *name, double complex a, double complex r) {
    printf("%s (%a,%a) = %a,%a\n", name, creal(a), cimag(a), creal(r), cimag(r));
}
static void print_cdbl2(const char *name, double complex a, double complex b, double complex r) {
    printf("%s (%a,%a),(%a,%a) = %a,%a\n", name,
           creal(a), cimag(a), creal(b), cimag(b), creal(r), cimag(r));
}
/* Print helper for complex float */
static void print_cflt(const char *name, float complex a, float complex r) {
    printf("%s (%a,%a) = %a,%a\n", name, (double)crealf(a), (double)cimagf(a),
           (double)crealf(r), (double)cimagf(r));
}
static void print_cflt2(const char *name, float complex a, float complex b, float complex r) {
    printf("%s (%a,%a),(%a,%a) = %a,%a\n", name,
           (double)crealf(a), (double)cimagf(a), (double)crealf(b), (double)cimagf(b),
           (double)crealf(r), (double)cimagf(r));
}

/* ===== 1. Double trigonometric functions ===== */
static void test_acos(void) {
    printf("acos %a = %a\n", 0.0, acos(0.0));
    printf("acos %a = %a\n", 1.0, acos(1.0));
    printf("acos %a = %a\n", -1.0, acos(-1.0));
    printf("acos %a = %a\n", 0.5, acos(0.5));
    printf("acos %a = %a\n", -0.5, acos(-0.5));
    printf("acos %a = %a\n", (double)NAN, acos((double)NAN));
    printf("acos %a = %a\n", POS_INF, acos(POS_INF));
    printf("acos %a = %a\n", NEG_INF, acos(NEG_INF));
    printf("acos %a = %a\n", 1.1, acos(1.1));
    printf("acos %a = %a\n", -1.1, acos(-1.1));
    printf("acos %a = %a\n", 0.7071067811865476, acos(0.7071067811865476));
}

static void test_asin(void) {
    printf("asin %a = %a\n", 0.0, asin(0.0));
    printf("asin %a = %a\n", -0.0, asin(-0.0));
    printf("asin %a = %a\n", 1.0, asin(1.0));
    printf("asin %a = %a\n", -1.0, asin(-1.0));
    printf("asin %a = %a\n", 0.5, asin(0.5));
    printf("asin %a = %a\n", (double)NAN, asin((double)NAN));
    printf("asin %a = %a\n", POS_INF, asin(POS_INF));
    printf("asin %a = %a\n", NEG_INF, asin(NEG_INF));
    printf("asin %a = %a\n", 1.1, asin(1.1));
    printf("asin %a = %a\n", DBL_DENORM, asin(DBL_DENORM));
}

static void test_atan(void) {
    printf("atan %a = %a\n", 0.0, atan(0.0));
    printf("atan %a = %a\n", -0.0, atan(-0.0));
    printf("atan %a = %a\n", 1.0, atan(1.0));
    printf("atan %a = %a\n", -1.0, atan(-1.0));
    printf("atan %a = %a\n", POS_INF, atan(POS_INF));
    printf("atan %a = %a\n", NEG_INF, atan(NEG_INF));
    printf("atan %a = %a\n", (double)NAN, atan((double)NAN));
    printf("atan %a = %a\n", 1e300, atan(1e300));
    printf("atan %a = %a\n", DBL_DENORM, atan(DBL_DENORM));
    printf("atan %a = %a\n", -1e300, atan(-1e300));
}

static void test_atan2(void) {
    printf("atan2 %a %a = %a\n", 0.0, 1.0, atan2(0.0, 1.0));
    printf("atan2 %a %a = %a\n", 0.0, -1.0, atan2(0.0, -1.0));
    printf("atan2 %a %a = %a\n", -0.0, -1.0, atan2(-0.0, -1.0));
    printf("atan2 %a %a = %a\n", 1.0, 0.0, atan2(1.0, 0.0));
    printf("atan2 %a %a = %a\n", -1.0, 0.0, atan2(-1.0, 0.0));
    printf("atan2 %a %a = %a\n", POS_INF, POS_INF, atan2(POS_INF, POS_INF));
    printf("atan2 %a %a = %a\n", NEG_INF, NEG_INF, atan2(NEG_INF, NEG_INF));
    printf("atan2 %a %a = %a\n", POS_INF, NEG_INF, atan2(POS_INF, NEG_INF));
    printf("atan2 %a %a = %a\n", (double)NAN, 1.0, atan2((double)NAN, 1.0));
    printf("atan2 %a %a = %a\n", 1.0, (double)NAN, atan2(1.0, (double)NAN));
    printf("atan2 %a %a = %a\n", 1.0, 1.0, atan2(1.0, 1.0));
    printf("atan2 %a %a = %a\n", -1.0, 1.0, atan2(-1.0, 1.0));
}

static void test_cos(void) {
    printf("cos %a = %a\n", 0.0, cos(0.0));
    printf("cos %a = %a\n", -0.0, cos(-0.0));
    printf("cos %a = %a\n", M_PI, cos(M_PI));
    printf("cos %a = %a\n", M_PI_2, cos(M_PI_2));
    printf("cos %a = %a\n", POS_INF, cos(POS_INF));
    printf("cos %a = %a\n", NEG_INF, cos(NEG_INF));
    printf("cos %a = %a\n", (double)NAN, cos((double)NAN));
    printf("cos %a = %a\n", 1e15, cos(1e15));
    printf("cos %a = %a\n", DBL_DENORM, cos(DBL_DENORM));
    printf("cos %a = %a\n", 1.0, cos(1.0));
    printf("cos %a = %a\n", -1.0, cos(-1.0));
}

static void test_sin(void) {
    printf("sin %a = %a\n", 0.0, sin(0.0));
    printf("sin %a = %a\n", -0.0, sin(-0.0));
    printf("sin %a = %a\n", M_PI, sin(M_PI));
    printf("sin %a = %a\n", M_PI_2, sin(M_PI_2));
    printf("sin %a = %a\n", POS_INF, sin(POS_INF));
    printf("sin %a = %a\n", NEG_INF, sin(NEG_INF));
    printf("sin %a = %a\n", (double)NAN, sin((double)NAN));
    printf("sin %a = %a\n", 1e15, sin(1e15));
    printf("sin %a = %a\n", DBL_DENORM, sin(DBL_DENORM));
    printf("sin %a = %a\n", 1.0, sin(1.0));
    printf("sin %a = %a\n", -1.0, sin(-1.0));
}

static void test_tan(void) {
    printf("tan %a = %a\n", 0.0, tan(0.0));
    printf("tan %a = %a\n", -0.0, tan(-0.0));
    printf("tan %a = %a\n", M_PI_4, tan(M_PI_4));
    printf("tan %a = %a\n", -M_PI_4, tan(-M_PI_4));
    printf("tan %a = %a\n", POS_INF, tan(POS_INF));
    printf("tan %a = %a\n", NEG_INF, tan(NEG_INF));
    printf("tan %a = %a\n", (double)NAN, tan((double)NAN));
    printf("tan %a = %a\n", 1e15, tan(1e15));
    printf("tan %a = %a\n", DBL_DENORM, tan(DBL_DENORM));
    printf("tan %a = %a\n", 1.0, tan(1.0));
}

/* ===== 2. Double hyperbolic functions ===== */
static void test_acosh(void) {
    printf("acosh %a = %a\n", 1.0, acosh(1.0));
    printf("acosh %a = %a\n", 2.0, acosh(2.0));
    printf("acosh %a = %a\n", POS_INF, acosh(POS_INF));
    printf("acosh %a = %a\n", (double)NAN, acosh((double)NAN));
    printf("acosh %a = %a\n", 0.5, acosh(0.5));
    printf("acosh %a = %a\n", 1e308, acosh(1e308));
    printf("acosh %a = %a\n", 1.0+DBL_DENORM, acosh(1.0+DBL_DENORM));
}

static void test_asinh(void) {
    printf("asinh %a = %a\n", 0.0, asinh(0.0));
    printf("asinh %a = %a\n", -0.0, asinh(-0.0));
    printf("asinh %a = %a\n", 1.0, asinh(1.0));
    printf("asinh %a = %a\n", -1.0, asinh(-1.0));
    printf("asinh %a = %a\n", POS_INF, asinh(POS_INF));
    printf("asinh %a = %a\n", NEG_INF, asinh(NEG_INF));
    printf("asinh %a = %a\n", (double)NAN, asinh((double)NAN));
    printf("asinh %a = %a\n", 1e300, asinh(1e300));
    printf("asinh %a = %a\n", DBL_DENORM, asinh(DBL_DENORM));
}

static void test_atanh(void) {
    printf("atanh %a = %a\n", 0.0, atanh(0.0));
    printf("atanh %a = %a\n", -0.0, atanh(-0.0));
    printf("atanh %a = %a\n", 1.0, atanh(1.0));
    printf("atanh %a = %a\n", -1.0, atanh(-1.0));
    printf("atanh %a = %a\n", 0.5, atanh(0.5));
    printf("atanh %a = %a\n", (double)NAN, atanh((double)NAN));
    printf("atanh %a = %a\n", POS_INF, atanh(POS_INF));
    printf("atanh %a = %a\n", 2.0, atanh(2.0));
    printf("atanh %a = %a\n", DBL_DENORM, atanh(DBL_DENORM));
}

static void test_cosh(void) {
    printf("cosh %a = %a\n", 0.0, cosh(0.0));
    printf("cosh %a = %a\n", -0.0, cosh(-0.0));
    printf("cosh %a = %a\n", 1.0, cosh(1.0));
    printf("cosh %a = %a\n", -1.0, cosh(-1.0));
    printf("cosh %a = %a\n", POS_INF, cosh(POS_INF));
    printf("cosh %a = %a\n", NEG_INF, cosh(NEG_INF));
    printf("cosh %a = %a\n", (double)NAN, cosh((double)NAN));
    printf("cosh %a = %a\n", 710.0, cosh(710.0));
    printf("cosh %a = %a\n", DBL_DENORM, cosh(DBL_DENORM));
}

static void test_sinh(void) {
    printf("sinh %a = %a\n", 0.0, sinh(0.0));
    printf("sinh %a = %a\n", -0.0, sinh(-0.0));
    printf("sinh %a = %a\n", 1.0, sinh(1.0));
    printf("sinh %a = %a\n", -1.0, sinh(-1.0));
    printf("sinh %a = %a\n", POS_INF, sinh(POS_INF));
    printf("sinh %a = %a\n", NEG_INF, sinh(NEG_INF));
    printf("sinh %a = %a\n", (double)NAN, sinh((double)NAN));
    printf("sinh %a = %a\n", 710.0, sinh(710.0));
    printf("sinh %a = %a\n", DBL_DENORM, sinh(DBL_DENORM));
}

static void test_tanh(void) {
    printf("tanh %a = %a\n", 0.0, tanh(0.0));
    printf("tanh %a = %a\n", -0.0, tanh(-0.0));
    printf("tanh %a = %a\n", 1.0, tanh(1.0));
    printf("tanh %a = %a\n", -1.0, tanh(-1.0));
    printf("tanh %a = %a\n", POS_INF, tanh(POS_INF));
    printf("tanh %a = %a\n", NEG_INF, tanh(NEG_INF));
    printf("tanh %a = %a\n", (double)NAN, tanh((double)NAN));
    printf("tanh %a = %a\n", 20.0, tanh(20.0));
    printf("tanh %a = %a\n", DBL_DENORM, tanh(DBL_DENORM));
}

/* ===== 3. Double exponential and logarithmic ===== */
static void test_exp(void) {
    printf("exp %a = %a\n", 0.0, exp(0.0));
    printf("exp %a = %a\n", -0.0, exp(-0.0));
    printf("exp %a = %a\n", 1.0, exp(1.0));
    printf("exp %a = %a\n", -1.0, exp(-1.0));
    printf("exp %a = %a\n", POS_INF, exp(POS_INF));
    printf("exp %a = %a\n", NEG_INF, exp(NEG_INF));
    printf("exp %a = %a\n", (double)NAN, exp((double)NAN));
    printf("exp %a = %a\n", 709.8, exp(709.8));
    printf("exp %a = %a\n", -745.1, exp(-745.1));
    printf("exp %a = %a\n", DBL_DENORM, exp(DBL_DENORM));
}

static void test_exp2(void) {
    printf("exp2 %a = %a\n", 0.0, exp2(0.0));
    printf("exp2 %a = %a\n", -0.0, exp2(-0.0));
    printf("exp2 %a = %a\n", 1.0, exp2(1.0));
    printf("exp2 %a = %a\n", -1.0, exp2(-1.0));
    printf("exp2 %a = %a\n", POS_INF, exp2(POS_INF));
    printf("exp2 %a = %a\n", NEG_INF, exp2(NEG_INF));
    printf("exp2 %a = %a\n", (double)NAN, exp2((double)NAN));
    printf("exp2 %a = %a\n", 1023.0, exp2(1023.0));
    printf("exp2 %a = %a\n", -1074.0, exp2(-1074.0));
    printf("exp2 %a = %a\n", 10.0, exp2(10.0));
}

static void test_expm1(void) {
    printf("expm1 %a = %a\n", 0.0, expm1(0.0));
    printf("expm1 %a = %a\n", -0.0, expm1(-0.0));
    printf("expm1 %a = %a\n", 1.0, expm1(1.0));
    printf("expm1 %a = %a\n", -1.0, expm1(-1.0));
    printf("expm1 %a = %a\n", POS_INF, expm1(POS_INF));
    printf("expm1 %a = %a\n", NEG_INF, expm1(NEG_INF));
    printf("expm1 %a = %a\n", (double)NAN, expm1((double)NAN));
    printf("expm1 %a = %a\n", 1e-10, expm1(1e-10));
    printf("expm1 %a = %a\n", DBL_DENORM, expm1(DBL_DENORM));
    printf("expm1 %a = %a\n", 709.0, expm1(709.0));
}

static void test_frexp(void) {
    int exp;
    double r;
    r = frexp(0.0, &exp);   printf("frexp %a = %a exp %d\n", 0.0, r, exp);
    r = frexp(-0.0, &exp);  printf("frexp %a = %a exp %d\n", -0.0, r, exp);
    r = frexp(1.0, &exp);   printf("frexp %a = %a exp %d\n", 1.0, r, exp);
    r = frexp(-1.0, &exp);  printf("frexp %a = %a exp %d\n", -1.0, r, exp);
    r = frexp(4.0, &exp);   printf("frexp %a = %a exp %d\n", 4.0, r, exp);
    r = frexp(POS_INF, &exp); printf("frexp %a = %a exp %d\n", POS_INF, r, exp);
    r = frexp(NEG_INF, &exp); printf("frexp %a = %a exp %d\n", NEG_INF, r, exp);
    r = frexp((double)NAN, &exp); printf("frexp nan = %a exp %d\n", r, exp);
    r = frexp(DBL_DENORM, &exp); printf("frexp %a = %a exp %d\n", DBL_DENORM, r, exp);
    r = frexp(1e300, &exp); printf("frexp %a = %a exp %d\n", 1e300, r, exp);
}

static void test_ilogb(void) {
    printf("ilogb %a = %d\n", 0.0, ilogb(0.0));
    printf("ilogb %a = %d\n", -0.0, ilogb(-0.0));
    printf("ilogb %a = %d\n", 1.0, ilogb(1.0));
    printf("ilogb %a = %d\n", 2.0, ilogb(2.0));
    printf("ilogb %a = %d\n", POS_INF, ilogb(POS_INF));
    printf("ilogb %a = %d\n", NEG_INF, ilogb(NEG_INF));
    printf("ilogb %a = %d\n", (double)NAN, ilogb((double)NAN));
    printf("ilogb %a = %d\n", DBL_DENORM, ilogb(DBL_DENORM));
    printf("ilogb %a = %d\n", 1e300, ilogb(1e300));
    printf("ilogb %a = %d\n", 0.5, ilogb(0.5));
}

static void test_ldexp(void) {
    printf("ldexp %a %d = %a\n", 1.0, 0, ldexp(1.0, 0));
    printf("ldexp %a %d = %a\n", 1.0, 1, ldexp(1.0, 1));
    printf("ldexp %a %d = %a\n", 1.0, -1, ldexp(1.0, -1));
    printf("ldexp %a %d = %a\n", 0.0, 5, ldexp(0.0, 5));
    printf("ldexp %a %d = %a\n", POS_INF, 1, ldexp(POS_INF, 1));
    printf("ldexp %a %d = %a\n", (double)NAN, 1, ldexp((double)NAN, 1));
    printf("ldexp %a %d = %a\n", 1.0, 1023, ldexp(1.0, 1023));
    printf("ldexp %a %d = %a\n", 1.0, -1074, ldexp(1.0, -1074));
    printf("ldexp %a %d = %a\n", 1.0, 2000, ldexp(1.0, 2000));
}

static void test_log(void) {
    printf("log %a = %a\n", 1.0, log(1.0));
    printf("log %a = %a\n", M_E, log(M_E));
    printf("log %a = %a\n", 0.0, log(0.0));
    printf("log %a = %a\n", -0.0, log(-0.0));
    printf("log %a = %a\n", POS_INF, log(POS_INF));
    printf("log %a = %a\n", -1.0, log(-1.0));
    printf("log %a = %a\n", (double)NAN, log((double)NAN));
    printf("log %a = %a\n", DBL_DENORM, log(DBL_DENORM));
    printf("log %a = %a\n", 1e300, log(1e300));
    printf("log %a = %a\n", 0.5, log(0.5));
}

static void test_log10(void) {
    printf("log10 %a = %a\n", 1.0, log10(1.0));
    printf("log10 %a = %a\n", 10.0, log10(10.0));
    printf("log10 %a = %a\n", 0.0, log10(0.0));
    printf("log10 %a = %a\n", POS_INF, log10(POS_INF));
    printf("log10 %a = %a\n", -1.0, log10(-1.0));
    printf("log10 %a = %a\n", (double)NAN, log10((double)NAN));
    printf("log10 %a = %a\n", DBL_DENORM, log10(DBL_DENORM));
    printf("log10 %a = %a\n", 1e300, log10(1e300));
}

static void test_log1p(void) {
    printf("log1p %a = %a\n", 0.0, log1p(0.0));
    printf("log1p %a = %a\n", -0.0, log1p(-0.0));
    printf("log1p %a = %a\n", 1.0, log1p(1.0));
    printf("log1p %a = %a\n", -1.0, log1p(-1.0));
    printf("log1p %a = %a\n", POS_INF, log1p(POS_INF));
    printf("log1p %a = %a\n", -2.0, log1p(-2.0));
    printf("log1p %a = %a\n", (double)NAN, log1p((double)NAN));
    printf("log1p %a = %a\n", 1e-10, log1p(1e-10));
    printf("log1p %a = %a\n", DBL_DENORM, log1p(DBL_DENORM));
}

static void test_log2(void) {
    printf("log2 %a = %a\n", 1.0, log2(1.0));
    printf("log2 %a = %a\n", 2.0, log2(2.0));
    printf("log2 %a = %a\n", 0.5, log2(0.5));
    printf("log2 %a = %a\n", 0.0, log2(0.0));
    printf("log2 %a = %a\n", POS_INF, log2(POS_INF));
    printf("log2 %a = %a\n", -1.0, log2(-1.0));
    printf("log2 %a = %a\n", (double)NAN, log2((double)NAN));
    printf("log2 %a = %a\n", DBL_DENORM, log2(DBL_DENORM));
    printf("log2 %a = %a\n", 1e300, log2(1e300));
}

static void test_logb(void) {
    printf("logb %a = %a\n", 1.0, logb(1.0));
    printf("logb %a = %a\n", 2.0, logb(2.0));
    printf("logb %a = %a\n", 0.0, logb(0.0));
    printf("logb %a = %a\n", -0.0, logb(-0.0));
    printf("logb %a = %a\n", POS_INF, logb(POS_INF));
    printf("logb %a = %a\n", NEG_INF, logb(NEG_INF));
    printf("logb %a = %a\n", (double)NAN, logb((double)NAN));
    printf("logb %a = %a\n", DBL_DENORM, logb(DBL_DENORM));
    printf("logb %a = %a\n", 1e300, logb(1e300));
}

static void test_modf(void) {
    double intpart;
    double r;
    r = modf(0.0, &intpart);   printf("modf %a = %a int %a\n", 0.0, r, intpart);
    r = modf(-0.0, &intpart);  printf("modf %a = %a int %a\n", -0.0, r, intpart);
    r = modf(1.5, &intpart);   printf("modf %a = %a int %a\n", 1.5, r, intpart);
    r = modf(-1.5, &intpart);  printf("modf %a = %a int %a\n", -1.5, r, intpart);
    r = modf(POS_INF, &intpart); printf("modf %a = %a int %a\n", POS_INF, r, intpart);
    r = modf(NEG_INF, &intpart); printf("modf %a = %a int %a\n", NEG_INF, r, intpart);
    r = modf((double)NAN, &intpart); printf("modf nan = %a int %a\n", r, intpart);
    r = modf(1e300, &intpart); printf("modf %a = %a int %a\n", 1e300, r, intpart);
}

static void test_scalbn(void) {
    printf("scalbn %a %d = %a\n", 1.0, 0, scalbn(1.0, 0));
    printf("scalbn %a %d = %a\n", 1.0, 1, scalbn(1.0, 1));
    printf("scalbn %a %d = %a\n", 1.0, -1, scalbn(1.0, -1));
    printf("scalbn %a %d = %a\n", 0.0, 5, scalbn(0.0, 5));
    printf("scalbn %a %d = %a\n", POS_INF, 1, scalbn(POS_INF, 1));
    printf("scalbn %a %d = %a\n", (double)NAN, 1, scalbn((double)NAN, 1));
    printf("scalbn %a %d = %a\n", DBL_DENORM, 1074, scalbn(DBL_DENORM, 1074));
    printf("scalbn %a %d = %a\n", 1.0, 2000, scalbn(1.0, 2000));
}

static void test_scalbln(void) {
    printf("scalbln %a %ld = %a\n", 1.0, 0L, scalbln(1.0, 0L));
    printf("scalbln %a %ld = %a\n", 1.0, 1L, scalbln(1.0, 1L));
    printf("scalbln %a %ld = %a\n", 1.0, -1L, scalbln(1.0, -1L));
    printf("scalbln %a %ld = %a\n", POS_INF, 1L, scalbln(POS_INF, 1L));
    printf("scalbln %a %ld = %a\n", (double)NAN, 1L, scalbln((double)NAN, 1L));
    printf("scalbln %a %ld = %a\n", 1.0, 100000L, scalbln(1.0, 100000L));
    printf("scalbln %a %ld = %a\n", 1.0, -100000L, scalbln(1.0, -100000L));
}

/* ===== 4. Double power and absolute-value functions ===== */
static void test_cbrt(void) {
    printf("cbrt %a = %a\n", 0.0, cbrt(0.0));
    printf("cbrt %a = %a\n", -0.0, cbrt(-0.0));
    printf("cbrt %a = %a\n", 1.0, cbrt(1.0));
    printf("cbrt %a = %a\n", -1.0, cbrt(-1.0));
    printf("cbrt %a = %a\n", 8.0, cbrt(8.0));
    printf("cbrt %a = %a\n", POS_INF, cbrt(POS_INF));
    printf("cbrt %a = %a\n", NEG_INF, cbrt(NEG_INF));
    printf("cbrt %a = %a\n", (double)NAN, cbrt((double)NAN));
    printf("cbrt %a = %a\n", DBL_DENORM, cbrt(DBL_DENORM));
    printf("cbrt %a = %a\n", 1e300, cbrt(1e300));
}

static void test_fabs(void) {
    printf("fabs %a = %a\n", 0.0, fabs(0.0));
    printf("fabs %a = %a\n", -0.0, fabs(-0.0));
    printf("fabs %a = %a\n", 1.0, fabs(1.0));
    printf("fabs %a = %a\n", -1.0, fabs(-1.0));
    printf("fabs %a = %a\n", POS_INF, fabs(POS_INF));
    printf("fabs %a = %a\n", NEG_INF, fabs(NEG_INF));
    printf("fabs %a = %a\n", (double)NAN, fabs((double)NAN));
    printf("fabs %a = %a\n", DBL_DENORM, fabs(DBL_DENORM));
    printf("fabs %a = %a\n", -DBL_DENORM, fabs(-DBL_DENORM));
}

static void test_hypot(void) {
    printf("hypot %a %a = %a\n", 3.0, 4.0, hypot(3.0, 4.0));
    printf("hypot %a %a = %a\n", 0.0, 0.0, hypot(0.0, 0.0));
    printf("hypot %a %a = %a\n", POS_INF, 1.0, hypot(POS_INF, 1.0));
    printf("hypot %a %a = %a\n", 1.0, POS_INF, hypot(1.0, POS_INF));
    printf("hypot %a %a = %a\n", NEG_INF, (double)NAN, hypot(NEG_INF, (double)NAN));
    printf("hypot %a %a = %a\n", (double)NAN, 1.0, hypot((double)NAN, 1.0));
    printf("hypot %a %a = %a\n", DBL_DENORM, DBL_DENORM, hypot(DBL_DENORM, DBL_DENORM));
    printf("hypot %a %a = %a\n", 1e300, 1e300, hypot(1e300, 1e300));
    printf("hypot %a %a = %a\n", -3.0, -4.0, hypot(-3.0, -4.0));
}

static void test_pow(void) {
    printf("pow %a %a = %a\n", 0.0, 0.0, pow(0.0, 0.0));
    printf("pow %a %a = %a\n", 2.0, 10.0, pow(2.0, 10.0));
    printf("pow %a %a = %a\n", 2.0, -1.0, pow(2.0, -1.0));
    printf("pow %a %a = %a\n", 0.0, -1.0, pow(0.0, -1.0));
    printf("pow %a %a = %a\n", -0.0, -1.0, pow(-0.0, -1.0));
    printf("pow %a %a = %a\n", POS_INF, 2.0, pow(POS_INF, 2.0));
    printf("pow %a %a = %a\n", NEG_INF, 3.0, pow(NEG_INF, 3.0));
    printf("pow %a %a = %a\n", (double)NAN, 1.0, pow((double)NAN, 1.0));
    printf("pow %a %a = %a\n", 1.0, (double)NAN, pow(1.0, (double)NAN));
    printf("pow %a %a = %a\n", -1.0, POS_INF, pow(-1.0, POS_INF));
    printf("pow %a %a = %a\n", 1.0, POS_INF, pow(1.0, POS_INF));
    printf("pow %a %a = %a\n", 0.0, POS_INF, pow(0.0, POS_INF));
    printf("pow %a %a = %a\n", 2.0, POS_INF, pow(2.0, POS_INF));
    printf("pow %a %a = %a\n", 0.5, NEG_INF, pow(0.5, NEG_INF));
    printf("pow %a %a = %a\n", -2.0, 2.0, pow(-2.0, 2.0));
    printf("pow %a %a = %a\n", -2.0, 3.0, pow(-2.0, 3.0));
    printf("pow %a %a = %a\n", -2.0, 0.5, pow(-2.0, 0.5));
}

static void test_sqrt(void) {
    printf("sqrt %a = %a\n", 0.0, sqrt(0.0));
    printf("sqrt %a = %a\n", -0.0, sqrt(-0.0));
    printf("sqrt %a = %a\n", 1.0, sqrt(1.0));
    printf("sqrt %a = %a\n", 4.0, sqrt(4.0));
    printf("sqrt %a = %a\n", 2.0, sqrt(2.0));
    printf("sqrt %a = %a\n", POS_INF, sqrt(POS_INF));
    printf("sqrt %a = %a\n", -1.0, sqrt(-1.0));
    printf("sqrt %a = %a\n", (double)NAN, sqrt((double)NAN));
    printf("sqrt %a = %a\n", DBL_DENORM, sqrt(DBL_DENORM));
    printf("sqrt %a = %a\n", 1e300, sqrt(1e300));
}

/* ===== 5. Double error and gamma functions ===== */
static void test_erf(void) {
    printf("erf %a = %a\n", 0.0, erf(0.0));
    printf("erf %a = %a\n", -0.0, erf(-0.0));
    printf("erf %a = %a\n", 1.0, erf(1.0));
    printf("erf %a = %a\n", -1.0, erf(-1.0));
    printf("erf %a = %a\n", POS_INF, erf(POS_INF));
    printf("erf %a = %a\n", NEG_INF, erf(NEG_INF));
    printf("erf %a = %a\n", (double)NAN, erf((double)NAN));
    printf("erf %a = %a\n", 0.5, erf(0.5));
    printf("erf %a = %a\n", 6.0, erf(6.0));
    printf("erf %a = %a\n", DBL_DENORM, erf(DBL_DENORM));
}

static void test_erfc(void) {
    printf("erfc %a = %a\n", 0.0, erfc(0.0));
    printf("erfc %a = %a\n", -0.0, erfc(-0.0));
    printf("erfc %a = %a\n", 1.0, erfc(1.0));
    printf("erfc %a = %a\n", -1.0, erfc(-1.0));
    printf("erfc %a = %a\n", POS_INF, erfc(POS_INF));
    printf("erfc %a = %a\n", NEG_INF, erfc(NEG_INF));
    printf("erfc %a = %a\n", (double)NAN, erfc((double)NAN));
    printf("erfc %a = %a\n", 0.5, erfc(0.5));
    printf("erfc %a = %a\n", 28.0, erfc(28.0));
}

static void test_lgamma(void) {
    printf("lgamma %a = %a signgam %d\n", 1.0, lgamma(1.0), signgam);
    printf("lgamma %a = %a signgam %d\n", 2.0, lgamma(2.0), signgam);
    printf("lgamma %a = %a signgam %d\n", 0.5, lgamma(0.5), signgam);
    printf("lgamma %a = %a signgam %d\n", -0.5, lgamma(-0.5), signgam);
    printf("lgamma %a = %a signgam %d\n", POS_INF, lgamma(POS_INF), signgam);
    printf("lgamma %a = %a signgam %d\n", NEG_INF, lgamma(NEG_INF), signgam);
    printf("lgamma %a = %a signgam %d\n", 0.0, lgamma(0.0), signgam);
    printf("lgamma %a = %a signgam %d\n", (double)NAN, lgamma((double)NAN), signgam);
    printf("lgamma %a = %a signgam %d\n", -1.0, lgamma(-1.0), signgam);
    printf("lgamma %a = %a signgam %d\n", 1e-300, lgamma(1e-300), signgam);
}

static void test_tgamma(void) {
    printf("tgamma %a = %a\n", 1.0, tgamma(1.0));
    printf("tgamma %a = %a\n", 2.0, tgamma(2.0));
    printf("tgamma %a = %a\n", 0.5, tgamma(0.5));
    printf("tgamma %a = %a\n", -0.5, tgamma(-0.5));
    printf("tgamma %a = %a\n", POS_INF, tgamma(POS_INF));
    printf("tgamma %a = %a\n", 0.0, tgamma(0.0));
    printf("tgamma %a = %a\n", -0.0, tgamma(-0.0));
    printf("tgamma %a = %a\n", (double)NAN, tgamma((double)NAN));
    printf("tgamma %a = %a\n", -1.0, tgamma(-1.0));
    printf("tgamma %a = %a\n", 172.0, tgamma(172.0));
    printf("tgamma %a = %a\n", 0.1, tgamma(0.1));
}

/* ===== 6. Double nearest integer functions ===== */
static void test_ceil(void) {
    printf("ceil %a = %a\n", 0.0, ceil(0.0));
    printf("ceil %a = %a\n", -0.0, ceil(-0.0));
    printf("ceil %a = %a\n", 0.5, ceil(0.5));
    printf("ceil %a = %a\n", -0.5, ceil(-0.5));
    printf("ceil %a = %a\n", 1.0, ceil(1.0));
    printf("ceil %a = %a\n", -1.0, ceil(-1.0));
    printf("ceil %a = %a\n", POS_INF, ceil(POS_INF));
    printf("ceil %a = %a\n", NEG_INF, ceil(NEG_INF));
    printf("ceil %a = %a\n", (double)NAN, ceil((double)NAN));
    printf("ceil %a = %a\n", DBL_DENORM, ceil(DBL_DENORM));
    printf("ceil %a = %a\n", 1e18, ceil(1e18));
}

static void test_floor(void) {
    printf("floor %a = %a\n", 0.0, floor(0.0));
    printf("floor %a = %a\n", -0.0, floor(-0.0));
    printf("floor %a = %a\n", 0.5, floor(0.5));
    printf("floor %a = %a\n", -0.5, floor(-0.5));
    printf("floor %a = %a\n", 1.0, floor(1.0));
    printf("floor %a = %a\n", -1.0, floor(-1.0));
    printf("floor %a = %a\n", POS_INF, floor(POS_INF));
    printf("floor %a = %a\n", NEG_INF, floor(NEG_INF));
    printf("floor %a = %a\n", (double)NAN, floor((double)NAN));
    printf("floor %a = %a\n", DBL_DENORM, floor(DBL_DENORM));
    printf("floor %a = %a\n", 1e18, floor(1e18));
}

static void test_nearbyint(void) {
    printf("nearbyint %a = %a\n", 0.0, nearbyint(0.0));
    printf("nearbyint %a = %a\n", -0.0, nearbyint(-0.0));
    printf("nearbyint %a = %a\n", 0.5, nearbyint(0.5));
    printf("nearbyint %a = %a\n", -0.5, nearbyint(-0.5));
    printf("nearbyint %a = %a\n", 1.5, nearbyint(1.5));
    printf("nearbyint %a = %a\n", -1.5, nearbyint(-1.5));
    printf("nearbyint %a = %a\n", POS_INF, nearbyint(POS_INF));
    printf("nearbyint %a = %a\n", (double)NAN, nearbyint((double)NAN));
    printf("nearbyint %a = %a\n", DBL_DENORM, nearbyint(DBL_DENORM));
}

static void test_rint(void) {
    printf("rint %a = %a\n", 0.0, rint(0.0));
    printf("rint %a = %a\n", -0.0, rint(-0.0));
    printf("rint %a = %a\n", 0.5, rint(0.5));
    printf("rint %a = %a\n", -0.5, rint(-0.5));
    printf("rint %a = %a\n", 1.5, rint(1.5));
    printf("rint %a = %a\n", -1.5, rint(-1.5));
    printf("rint %a = %a\n", POS_INF, rint(POS_INF));
    printf("rint %a = %a\n", (double)NAN, rint((double)NAN));
    printf("rint %a = %a\n", DBL_DENORM, rint(DBL_DENORM));
}

static void test_lrint(void) {
    printf("lrint %a = %ld\n", 0.0, lrint(0.0));
    printf("lrint %a = %ld\n", 0.5, lrint(0.5));
    printf("lrint %a = %ld\n", -0.5, lrint(-0.5));
    printf("lrint %a = %ld\n", 1.5, lrint(1.5));
    printf("lrint %a = %ld\n", -1.5, lrint(-1.5));
    printf("lrint %a = %ld\n", 1e10, lrint(1e10));
    printf("lrint %a = %ld\n", -1e10, lrint(-1e10));
}

static void test_llrint(void) {
    printf("llrint %a = %lld\n", 0.0, llrint(0.0));
    printf("llrint %a = %lld\n", 0.5, llrint(0.5));
    printf("llrint %a = %lld\n", -0.5, llrint(-0.5));
    printf("llrint %a = %lld\n", 1.5, llrint(1.5));
    printf("llrint %a = %lld\n", -1.5, llrint(-1.5));
    printf("llrint %a = %lld\n", 1e15, llrint(1e15));
}

static void test_round(void) {
    printf("round %a = %a\n", 0.0, round(0.0));
    printf("round %a = %a\n", -0.0, round(-0.0));
    printf("round %a = %a\n", 0.5, round(0.5));
    printf("round %a = %a\n", -0.5, round(-0.5));
    printf("round %a = %a\n", 1.5, round(1.5));
    printf("round %a = %a\n", -1.5, round(-1.5));
    printf("round %a = %a\n", POS_INF, round(POS_INF));
    printf("round %a = %a\n", (double)NAN, round((double)NAN));
    printf("round %a = %a\n", DBL_DENORM, round(DBL_DENORM));
}

static void test_lround(void) {
    printf("lround %a = %ld\n", 0.0, lround(0.0));
    printf("lround %a = %ld\n", 0.5, lround(0.5));
    printf("lround %a = %ld\n", -0.5, lround(-0.5));
    printf("lround %a = %ld\n", 1.5, lround(1.5));
    printf("lround %a = %ld\n", -1.5, lround(-1.5));
    printf("lround %a = %ld\n", 1e10, lround(1e10));
}

static void test_llround(void) {
    printf("llround %a = %lld\n", 0.0, llround(0.0));
    printf("llround %a = %lld\n", 0.5, llround(0.5));
    printf("llround %a = %lld\n", -0.5, llround(-0.5));
    printf("llround %a = %lld\n", 1.5, llround(1.5));
    printf("llround %a = %lld\n", -1.5, llround(-1.5));
    printf("llround %a = %lld\n", 1e15, llround(1e15));
}

static void test_trunc(void) {
    printf("trunc %a = %a\n", 0.0, trunc(0.0));
    printf("trunc %a = %a\n", -0.0, trunc(-0.0));
    printf("trunc %a = %a\n", 0.5, trunc(0.5));
    printf("trunc %a = %a\n", -0.5, trunc(-0.5));
    printf("trunc %a = %a\n", 1.9, trunc(1.9));
    printf("trunc %a = %a\n", -1.9, trunc(-1.9));
    printf("trunc %a = %a\n", POS_INF, trunc(POS_INF));
    printf("trunc %a = %a\n", (double)NAN, trunc((double)NAN));
    printf("trunc %a = %a\n", DBL_DENORM, trunc(DBL_DENORM));
}

/* ===== 7. Double remainder functions ===== */
static void test_fmod(void) {
    printf("fmod %a %a = %a\n", 5.0, 3.0, fmod(5.0, 3.0));
    printf("fmod %a %a = %a\n", -5.0, 3.0, fmod(-5.0, 3.0));
    printf("fmod %a %a = %a\n", 5.0, -3.0, fmod(5.0, -3.0));
    printf("fmod %a %a = %a\n", 0.0, 1.0, fmod(0.0, 1.0));
    printf("fmod %a %a = %a\n", 1.0, 0.0, fmod(1.0, 0.0));
    printf("fmod %a %a = %a\n", POS_INF, 1.0, fmod(POS_INF, 1.0));
    printf("fmod %a %a = %a\n", (double)NAN, 1.0, fmod((double)NAN, 1.0));
    printf("fmod %a %a = %a\n", 1.0, (double)NAN, fmod(1.0, (double)NAN));
    printf("fmod %a %a = %a\n", DBL_DENORM, 1.0, fmod(DBL_DENORM, 1.0));
}

static void test_remainder(void) {
    printf("remainder %a %a = %a\n", 5.0, 3.0, remainder(5.0, 3.0));
    printf("remainder %a %a = %a\n", -5.0, 3.0, remainder(-5.0, 3.0));
    printf("remainder %a %a = %a\n", 0.0, 1.0, remainder(0.0, 1.0));
    printf("remainder %a %a = %a\n", POS_INF, 1.0, remainder(POS_INF, 1.0));
    printf("remainder %a %a = %a\n", (double)NAN, 1.0, remainder((double)NAN, 1.0));
    printf("remainder %a %a = %a\n", 1.0, 0.0, remainder(1.0, 0.0));
    printf("remainder %a %a = %a\n", DBL_DENORM, 1.0, remainder(DBL_DENORM, 1.0));
}

static void test_remquo(void) {
    int quo;
    double r;
    r = remquo(5.0, 3.0, &quo);   printf("remquo %a %a = %a quo %d\n", 5.0, 3.0, r, quo);
    r = remquo(-5.0, 3.0, &quo);  printf("remquo %a %a = %a quo %d\n", -5.0, 3.0, r, quo);
    r = remquo(0.0, 1.0, &quo);   printf("remquo %a %a = %a quo %d\n", 0.0, 1.0, r, quo);
    r = remquo(POS_INF, 1.0, &quo); printf("remquo %a %a = %a quo %d\n", POS_INF, 1.0, r, quo);
    r = remquo(1.0, 0.0, &quo);   printf("remquo %a %a = %a quo %d\n", 1.0, 0.0, r, quo);
    r = remquo((double)NAN, 1.0, &quo); printf("remquo nan %a = %a quo %d\n", 1.0, r, quo);
}

/* ===== 8. Double manipulation functions ===== */
static void test_copysign(void) {
    printf("copysign %a %a = %a\n", 1.0, -1.0, copysign(1.0, -1.0));
    printf("copysign %a %a = %a\n", -1.0, 1.0, copysign(-1.0, 1.0));
    printf("copysign %a %a = %a\n", 0.0, -1.0, copysign(0.0, -1.0));
    printf("copysign %a %a = %a\n", -0.0, 1.0, copysign(-0.0, 1.0));
    printf("copysign %a %a = %a\n", POS_INF, -1.0, copysign(POS_INF, -1.0));
    printf("copysign %a %a = %a\n", (double)NAN, -1.0, copysign((double)NAN, -1.0));
    printf("copysign %a %a = %a\n", DBL_DENORM, -1.0, copysign(DBL_DENORM, -1.0));
}

static void test_nan(void) {
    /* nan returns a NaN; test that result is a NaN */
    double r = nan("");
    printf("nan \"\" isnan = %d\n", r != r ? 1 : 0);
    r = nan("1");
    printf("nan \"1\" isnan = %d\n", r != r ? 1 : 0);
}

static void test_nextafter(void) {
    printf("nextafter %a %a = %a\n", 0.0, 1.0, nextafter(0.0, 1.0));
    printf("nextafter %a %a = %a\n", 0.0, -1.0, nextafter(0.0, -1.0));
    printf("nextafter %a %a = %a\n", 1.0, 2.0, nextafter(1.0, 2.0));
    printf("nextafter %a %a = %a\n", 1.0, 0.0, nextafter(1.0, 0.0));
    printf("nextafter %a %a = %a\n", POS_INF, 0.0, nextafter(POS_INF, 0.0));
    printf("nextafter %a %a = %a\n", (double)NAN, 1.0, nextafter((double)NAN, 1.0));
    printf("nextafter %a %a = %a\n", 1.0, (double)NAN, nextafter(1.0, (double)NAN));
    printf("nextafter %a %a = %a\n", DBL_DENORM, 1.0, nextafter(DBL_DENORM, 1.0));
    printf("nextafter %a %a = %a\n", DBL_DENORM, 0.0, nextafter(DBL_DENORM, 0.0));
}

/* ===== 9. Double max/min/fdim ===== */
static void test_fdim(void) {
    printf("fdim %a %a = %a\n", 3.0, 1.0, fdim(3.0, 1.0));
    printf("fdim %a %a = %a\n", 1.0, 3.0, fdim(1.0, 3.0));
    printf("fdim %a %a = %a\n", 0.0, 0.0, fdim(0.0, 0.0));
    printf("fdim %a %a = %a\n", POS_INF, 1.0, fdim(POS_INF, 1.0));
    printf("fdim %a %a = %a\n", (double)NAN, 1.0, fdim((double)NAN, 1.0));
    printf("fdim %a %a = %a\n", 1.0, (double)NAN, fdim(1.0, (double)NAN));
    printf("fdim %a %a = %a\n", -1.0, -2.0, fdim(-1.0, -2.0));
}

static void test_fmax(void) {
    printf("fmax %a %a = %a\n", 1.0, 2.0, fmax(1.0, 2.0));
    printf("fmax %a %a = %a\n", 2.0, 1.0, fmax(2.0, 1.0));
    printf("fmax %a %a = %a\n", (double)NAN, 1.0, fmax((double)NAN, 1.0));
    printf("fmax %a %a = %a\n", 1.0, (double)NAN, fmax(1.0, (double)NAN));
    printf("fmax %a %a = %a\n", POS_INF, NEG_INF, fmax(POS_INF, NEG_INF));
    printf("fmax %a %a = %a\n", -0.0, 0.0, fmax(-0.0, 0.0));
}

static void test_fmin(void) {
    printf("fmin %a %a = %a\n", 1.0, 2.0, fmin(1.0, 2.0));
    printf("fmin %a %a = %a\n", 2.0, 1.0, fmin(2.0, 1.0));
    printf("fmin %a %a = %a\n", (double)NAN, 1.0, fmin((double)NAN, 1.0));
    printf("fmin %a %a = %a\n", 1.0, (double)NAN, fmin(1.0, (double)NAN));
    printf("fmin %a %a = %a\n", POS_INF, NEG_INF, fmin(POS_INF, NEG_INF));
    printf("fmin %a %a = %a\n", -0.0, 0.0, fmin(-0.0, 0.0));
}

/* ===== 10. Double fma ===== */
static void test_fma(void) {
    printf("fma %a %a %a = %a\n", 2.0, 3.0, 4.0, fma(2.0, 3.0, 4.0));
    printf("fma %a %a %a = %a\n", 1.0, 1.0, -1.0, fma(1.0, 1.0, -1.0));
    printf("fma %a %a %a = %a\n", 0.0, 1.0, 1.0, fma(0.0, 1.0, 1.0));
    printf("fma %a %a %a = %a\n", POS_INF, 1.0, NEG_INF, fma(POS_INF, 1.0, NEG_INF));
    printf("fma %a %a %a = %a\n", (double)NAN, 1.0, 1.0, fma((double)NAN, 1.0, 1.0));
    printf("fma %a %a %a = %a\n", 1.0, (double)NAN, 1.0, fma(1.0, (double)NAN, 1.0));
    printf("fma %a %a %a = %a\n", 1.0, 1.0, (double)NAN, fma(1.0, 1.0, (double)NAN));
    printf("fma %a %a %a = %a\n", DBL_DENORM, 2.0, 0.0, fma(DBL_DENORM, 2.0, 0.0));
}

/* ===== 11. Double Bessel functions ===== */
static void test_j0(void) {
    printf("j0 %a = %a\n", 0.0, j0(0.0));
    printf("j0 %a = %a\n", 1.0, j0(1.0));
    printf("j0 %a = %a\n", -1.0, j0(-1.0));
    printf("j0 %a = %a\n", POS_INF, j0(POS_INF));
    printf("j0 %a = %a\n", NEG_INF, j0(NEG_INF));
    printf("j0 %a = %a\n", (double)NAN, j0((double)NAN));
    printf("j0 %a = %a\n", 2.4048255577, j0(2.4048255577));
    printf("j0 %a = %a\n", 1e10, j0(1e10));
}

static void test_j1(void) {
    printf("j1 %a = %a\n", 0.0, j1(0.0));
    printf("j1 %a = %a\n", 1.0, j1(1.0));
    printf("j1 %a = %a\n", -1.0, j1(-1.0));
    printf("j1 %a = %a\n", POS_INF, j1(POS_INF));
    printf("j1 %a = %a\n", (double)NAN, j1((double)NAN));
    printf("j1 %a = %a\n", 1e10, j1(1e10));
}

static void test_jn(void) {
    printf("jn %d %a = %a\n", 0, 1.0, jn(0, 1.0));
    printf("jn %d %a = %a\n", 1, 1.0, jn(1, 1.0));
    printf("jn %d %a = %a\n", 2, 1.0, jn(2, 1.0));
    printf("jn %d %a = %a\n", 5, 5.0, jn(5, 5.0));
    printf("jn %d %a = %a\n", 0, 0.0, jn(0, 0.0));
    printf("jn %d %a = %a\n", 1, POS_INF, jn(1, POS_INF));
    printf("jn %d %a = %a\n", 0, (double)NAN, jn(0, (double)NAN));
}

static void test_y0(void) {
    printf("y0 %a = %a\n", 1.0, y0(1.0));
    printf("y0 %a = %a\n", 0.0, y0(0.0));
    printf("y0 %a = %a\n", -1.0, y0(-1.0));
    printf("y0 %a = %a\n", POS_INF, y0(POS_INF));
    printf("y0 %a = %a\n", (double)NAN, y0((double)NAN));
    printf("y0 %a = %a\n", 0.8935769662791675, y0(0.8935769662791675));
    printf("y0 %a = %a\n", 1e10, y0(1e10));
}

static void test_y1(void) {
    printf("y1 %a = %a\n", 1.0, y1(1.0));
    printf("y1 %a = %a\n", 0.0, y1(0.0));
    printf("y1 %a = %a\n", -1.0, y1(-1.0));
    printf("y1 %a = %a\n", POS_INF, y1(POS_INF));
    printf("y1 %a = %a\n", (double)NAN, y1((double)NAN));
    printf("y1 %a = %a\n", 1e10, y1(1e10));
}

static void test_yn(void) {
    printf("yn %d %a = %a\n", 0, 1.0, yn(0, 1.0));
    printf("yn %d %a = %a\n", 1, 1.0, yn(1, 1.0));
    printf("yn %d %a = %a\n", 2, 1.0, yn(2, 1.0));
    printf("yn %d %a = %a\n", 0, 0.0, yn(0, 0.0));
    printf("yn %d %a = %a\n", 0, -1.0, yn(0, -1.0));
    printf("yn %d %a = %a\n", 0, POS_INF, yn(0, POS_INF));
    printf("yn %d %a = %a\n", 1, (double)NAN, yn(1, (double)NAN));
}

/* ===== 12. Float trigonometric functions ===== */
static void test_acosf(void) {
    printf("acosf %a = %a\n", (double)0.0f, (double)acosf(0.0f));
    printf("acosf %a = %a\n", (double)1.0f, (double)acosf(1.0f));
    printf("acosf %a = %a\n", (double)-1.0f, (double)acosf(-1.0f));
    printf("acosf %a = %a\n", (double)0.5f, (double)acosf(0.5f));
    printf("acosf %a = %a\n", (double)NAN, (double)acosf((float)NAN));
    printf("acosf %a = %a\n", (double)POS_INFF, (double)acosf(POS_INFF));
    printf("acosf %a = %a\n", (double)1.1f, (double)acosf(1.1f));
    printf("acosf %a = %a\n", (double)FLT_DENORM, (double)acosf(FLT_DENORM));
}

static void test_asinf(void) {
    printf("asinf %a = %a\n", (double)0.0f, (double)asinf(0.0f));
    printf("asinf %a = %a\n", (double)-0.0f, (double)asinf(-0.0f));
    printf("asinf %a = %a\n", (double)1.0f, (double)asinf(1.0f));
    printf("asinf %a = %a\n", (double)-1.0f, (double)asinf(-1.0f));
    printf("asinf %a = %a\n", (double)NAN, (double)asinf((float)NAN));
    printf("asinf %a = %a\n", (double)POS_INFF, (double)asinf(POS_INFF));
    printf("asinf %a = %a\n", (double)FLT_DENORM, (double)asinf(FLT_DENORM));
}

static void test_atanf(void) {
    printf("atanf %a = %a\n", (double)0.0f, (double)atanf(0.0f));
    printf("atanf %a = %a\n", (double)-0.0f, (double)atanf(-0.0f));
    printf("atanf %a = %a\n", (double)1.0f, (double)atanf(1.0f));
    printf("atanf %a = %a\n", (double)-1.0f, (double)atanf(-1.0f));
    printf("atanf %a = %a\n", (double)POS_INFF, (double)atanf(POS_INFF));
    printf("atanf %a = %a\n", (double)NEG_INFF, (double)atanf(NEG_INFF));
    printf("atanf %a = %a\n", (double)NAN, (double)atanf((float)NAN));
    printf("atanf %a = %a\n", (double)FLT_DENORM, (double)atanf(FLT_DENORM));
}

static void test_atan2f(void) {
    printf("atan2f %a %a = %a\n", (double)0.0f, (double)1.0f, (double)atan2f(0.0f, 1.0f));
    printf("atan2f %a %a = %a\n", (double)0.0f, (double)-1.0f, (double)atan2f(0.0f, -1.0f));
    printf("atan2f %a %a = %a\n", (double)1.0f, (double)0.0f, (double)atan2f(1.0f, 0.0f));
    printf("atan2f %a %a = %a\n", (double)POS_INFF, (double)POS_INFF, (double)atan2f(POS_INFF, POS_INFF));
    printf("atan2f %a %a = %a\n", (double)NAN, (double)1.0f, (double)atan2f((float)NAN, 1.0f));
    printf("atan2f %a %a = %a\n", (double)1.0f, (double)NAN, (double)atan2f(1.0f, (float)NAN));
}

static void test_cosf(void) {
    printf("cosf %a = %a\n", (double)0.0f, (double)cosf(0.0f));
    printf("cosf %a = %a\n", (double)(float)M_PI, (double)cosf((float)M_PI));
    printf("cosf %a = %a\n", (double)POS_INFF, (double)cosf(POS_INFF));
    printf("cosf %a = %a\n", (double)NAN, (double)cosf((float)NAN));
    printf("cosf %a = %a\n", (double)1.0f, (double)cosf(1.0f));
    printf("cosf %a = %a\n", (double)1e15f, (double)cosf(1e15f));
    printf("cosf %a = %a\n", (double)FLT_DENORM, (double)cosf(FLT_DENORM));
}

static void test_sinf(void) {
    printf("sinf %a = %a\n", (double)0.0f, (double)sinf(0.0f));
    printf("sinf %a = %a\n", (double)-0.0f, (double)sinf(-0.0f));
    printf("sinf %a = %a\n", (double)(float)M_PI, (double)sinf((float)M_PI));
    printf("sinf %a = %a\n", (double)POS_INFF, (double)sinf(POS_INFF));
    printf("sinf %a = %a\n", (double)NAN, (double)sinf((float)NAN));
    printf("sinf %a = %a\n", (double)1.0f, (double)sinf(1.0f));
    printf("sinf %a = %a\n", (double)FLT_DENORM, (double)sinf(FLT_DENORM));
}

static void test_tanf(void) {
    printf("tanf %a = %a\n", (double)0.0f, (double)tanf(0.0f));
    printf("tanf %a = %a\n", (double)-0.0f, (double)tanf(-0.0f));
    printf("tanf %a = %a\n", (double)(float)M_PI_4, (double)tanf((float)M_PI_4));
    printf("tanf %a = %a\n", (double)POS_INFF, (double)tanf(POS_INFF));
    printf("tanf %a = %a\n", (double)NAN, (double)tanf((float)NAN));
    printf("tanf %a = %a\n", (double)1.0f, (double)tanf(1.0f));
    printf("tanf %a = %a\n", (double)FLT_DENORM, (double)tanf(FLT_DENORM));
}

/* ===== 13. Float hyperbolic functions ===== */
static void test_acoshf(void) {
    printf("acoshf %a = %a\n", (double)1.0f, (double)acoshf(1.0f));
    printf("acoshf %a = %a\n", (double)2.0f, (double)acoshf(2.0f));
    printf("acoshf %a = %a\n", (double)POS_INFF, (double)acoshf(POS_INFF));
    printf("acoshf %a = %a\n", (double)NAN, (double)acoshf((float)NAN));
    printf("acoshf %a = %a\n", (double)0.5f, (double)acoshf(0.5f));
}

static void test_asinhf(void) {
    printf("asinhf %a = %a\n", (double)0.0f, (double)asinhf(0.0f));
    printf("asinhf %a = %a\n", (double)-0.0f, (double)asinhf(-0.0f));
    printf("asinhf %a = %a\n", (double)1.0f, (double)asinhf(1.0f));
    printf("asinhf %a = %a\n", (double)POS_INFF, (double)asinhf(POS_INFF));
    printf("asinhf %a = %a\n", (double)NAN, (double)asinhf((float)NAN));
    printf("asinhf %a = %a\n", (double)FLT_DENORM, (double)asinhf(FLT_DENORM));
}

static void test_atanhf(void) {
    printf("atanhf %a = %a\n", (double)0.0f, (double)atanhf(0.0f));
    printf("atanhf %a = %a\n", (double)-0.0f, (double)atanhf(-0.0f));
    printf("atanhf %a = %a\n", (double)1.0f, (double)atanhf(1.0f));
    printf("atanhf %a = %a\n", (double)-1.0f, (double)atanhf(-1.0f));
    printf("atanhf %a = %a\n", (double)POS_INFF, (double)atanhf(POS_INFF));
    printf("atanhf %a = %a\n", (double)NAN, (double)atanhf((float)NAN));
    printf("atanhf %a = %a\n", (double)FLT_DENORM, (double)atanhf(FLT_DENORM));
}

static void test_coshf(void) {
    printf("coshf %a = %a\n", (double)0.0f, (double)coshf(0.0f));
    printf("coshf %a = %a\n", (double)1.0f, (double)coshf(1.0f));
    printf("coshf %a = %a\n", (double)POS_INFF, (double)coshf(POS_INFF));
    printf("coshf %a = %a\n", (double)NAN, (double)coshf((float)NAN));
    printf("coshf %a = %a\n", (double)89.0f, (double)coshf(89.0f));
    printf("coshf %a = %a\n", (double)FLT_DENORM, (double)coshf(FLT_DENORM));
}

static void test_sinhf(void) {
    printf("sinhf %a = %a\n", (double)0.0f, (double)sinhf(0.0f));
    printf("sinhf %a = %a\n", (double)-0.0f, (double)sinhf(-0.0f));
    printf("sinhf %a = %a\n", (double)1.0f, (double)sinhf(1.0f));
    printf("sinhf %a = %a\n", (double)POS_INFF, (double)sinhf(POS_INFF));
    printf("sinhf %a = %a\n", (double)NAN, (double)sinhf((float)NAN));
    printf("sinhf %a = %a\n", (double)89.0f, (double)sinhf(89.0f));
    printf("sinhf %a = %a\n", (double)FLT_DENORM, (double)sinhf(FLT_DENORM));
}

static void test_tanhf(void) {
    printf("tanhf %a = %a\n", (double)0.0f, (double)tanhf(0.0f));
    printf("tanhf %a = %a\n", (double)-0.0f, (double)tanhf(-0.0f));
    printf("tanhf %a = %a\n", (double)1.0f, (double)tanhf(1.0f));
    printf("tanhf %a = %a\n", (double)POS_INFF, (double)tanhf(POS_INFF));
    printf("tanhf %a = %a\n", (double)NAN, (double)tanhf((float)NAN));
    printf("tanhf %a = %a\n", (double)FLT_DENORM, (double)tanhf(FLT_DENORM));
}

/* ===== 14. Float exponential and logarithmic ===== */
static void test_expf(void) {
    printf("expf %a = %a\n", (double)0.0f, (double)expf(0.0f));
    printf("expf %a = %a\n", (double)1.0f, (double)expf(1.0f));
    printf("expf %a = %a\n", (double)-1.0f, (double)expf(-1.0f));
    printf("expf %a = %a\n", (double)POS_INFF, (double)expf(POS_INFF));
    printf("expf %a = %a\n", (double)NEG_INFF, (double)expf(NEG_INFF));
    printf("expf %a = %a\n", (double)NAN, (double)expf((float)NAN));
    printf("expf %a = %a\n", (double)88.0f, (double)expf(88.0f));
    printf("expf %a = %a\n", (double)-103.0f, (double)expf(-103.0f));
    printf("expf %a = %a\n", (double)FLT_DENORM, (double)expf(FLT_DENORM));
}

static void test_exp2f(void) {
    printf("exp2f %a = %a\n", (double)0.0f, (double)exp2f(0.0f));
    printf("exp2f %a = %a\n", (double)1.0f, (double)exp2f(1.0f));
    printf("exp2f %a = %a\n", (double)-1.0f, (double)exp2f(-1.0f));
    printf("exp2f %a = %a\n", (double)POS_INFF, (double)exp2f(POS_INFF));
    printf("exp2f %a = %a\n", (double)NEG_INFF, (double)exp2f(NEG_INFF));
    printf("exp2f %a = %a\n", (double)NAN, (double)exp2f((float)NAN));
    printf("exp2f %a = %a\n", (double)127.0f, (double)exp2f(127.0f));
    printf("exp2f %a = %a\n", (double)-149.0f, (double)exp2f(-149.0f));
}

static void test_expm1f(void) {
    printf("expm1f %a = %a\n", (double)0.0f, (double)expm1f(0.0f));
    printf("expm1f %a = %a\n", (double)-0.0f, (double)expm1f(-0.0f));
    printf("expm1f %a = %a\n", (double)1.0f, (double)expm1f(1.0f));
    printf("expm1f %a = %a\n", (double)POS_INFF, (double)expm1f(POS_INFF));
    printf("expm1f %a = %a\n", (double)NEG_INFF, (double)expm1f(NEG_INFF));
    printf("expm1f %a = %a\n", (double)NAN, (double)expm1f((float)NAN));
    printf("expm1f %a = %a\n", (double)1e-10f, (double)expm1f(1e-10f));
    printf("expm1f %a = %a\n", (double)FLT_DENORM, (double)expm1f(FLT_DENORM));
}

static void test_frexpf(void) {
    int exp;
    float r;
    r = frexpf(0.0f, &exp);   printf("frexpf %a = %a exp %d\n", (double)0.0f, (double)r, exp);
    r = frexpf(1.0f, &exp);   printf("frexpf %a = %a exp %d\n", (double)1.0f, (double)r, exp);
    r = frexpf(-1.0f, &exp);  printf("frexpf %a = %a exp %d\n", (double)-1.0f, (double)r, exp);
    r = frexpf(4.0f, &exp);   printf("frexpf %a = %a exp %d\n", (double)4.0f, (double)r, exp);
    r = frexpf(POS_INFF, &exp); printf("frexpf %a = %a exp %d\n", (double)POS_INFF, (double)r, exp);
    r = frexpf((float)NAN, &exp); printf("frexpf nan = %a exp %d\n", (double)r, exp);
    r = frexpf(FLT_DENORM, &exp); printf("frexpf %a = %a exp %d\n", (double)FLT_DENORM, (double)r, exp);
}

static void test_ilogbf(void) {
    printf("ilogbf %a = %d\n", (double)0.0f, ilogbf(0.0f));
    printf("ilogbf %a = %d\n", (double)1.0f, ilogbf(1.0f));
    printf("ilogbf %a = %d\n", (double)2.0f, ilogbf(2.0f));
    printf("ilogbf %a = %d\n", (double)POS_INFF, ilogbf(POS_INFF));
    printf("ilogbf %a = %d\n", (double)NAN, ilogbf((float)NAN));
    printf("ilogbf %a = %d\n", (double)FLT_DENORM, ilogbf(FLT_DENORM));
}

static void test_ldexpf(void) {
    printf("ldexpf %a %d = %a\n", (double)1.0f, 0, (double)ldexpf(1.0f, 0));
    printf("ldexpf %a %d = %a\n", (double)1.0f, 1, (double)ldexpf(1.0f, 1));
    printf("ldexpf %a %d = %a\n", (double)1.0f, -1, (double)ldexpf(1.0f, -1));
    printf("ldexpf %a %d = %a\n", (double)POS_INFF, 1, (double)ldexpf(POS_INFF, 1));
    printf("ldexpf %a %d = %a\n", (double)NAN, 1, (double)ldexpf((float)NAN, 1));
    printf("ldexpf %a %d = %a\n", (double)FLT_DENORM, 149, (double)ldexpf(FLT_DENORM, 149));
}

static void test_logf(void) {
    printf("logf %a = %a\n", (double)1.0f, (double)logf(1.0f));
    printf("logf %a = %a\n", (double)(float)M_E, (double)logf((float)M_E));
    printf("logf %a = %a\n", (double)0.0f, (double)logf(0.0f));
    printf("logf %a = %a\n", (double)POS_INFF, (double)logf(POS_INFF));
    printf("logf %a = %a\n", (double)-1.0f, (double)logf(-1.0f));
    printf("logf %a = %a\n", (double)NAN, (double)logf((float)NAN));
    printf("logf %a = %a\n", (double)FLT_DENORM, (double)logf(FLT_DENORM));
}

static void test_log10f(void) {
    printf("log10f %a = %a\n", (double)1.0f, (double)log10f(1.0f));
    printf("log10f %a = %a\n", (double)10.0f, (double)log10f(10.0f));
    printf("log10f %a = %a\n", (double)0.0f, (double)log10f(0.0f));
    printf("log10f %a = %a\n", (double)POS_INFF, (double)log10f(POS_INFF));
    printf("log10f %a = %a\n", (double)-1.0f, (double)log10f(-1.0f));
    printf("log10f %a = %a\n", (double)NAN, (double)log10f((float)NAN));
    printf("log10f %a = %a\n", (double)FLT_DENORM, (double)log10f(FLT_DENORM));
}

static void test_log1pf(void) {
    printf("log1pf %a = %a\n", (double)0.0f, (double)log1pf(0.0f));
    printf("log1pf %a = %a\n", (double)-0.0f, (double)log1pf(-0.0f));
    printf("log1pf %a = %a\n", (double)-1.0f, (double)log1pf(-1.0f));
    printf("log1pf %a = %a\n", (double)POS_INFF, (double)log1pf(POS_INFF));
    printf("log1pf %a = %a\n", (double)NAN, (double)log1pf((float)NAN));
    printf("log1pf %a = %a\n", (double)1e-10f, (double)log1pf(1e-10f));
    printf("log1pf %a = %a\n", (double)FLT_DENORM, (double)log1pf(FLT_DENORM));
}

static void test_log2f(void) {
    printf("log2f %a = %a\n", (double)1.0f, (double)log2f(1.0f));
    printf("log2f %a = %a\n", (double)2.0f, (double)log2f(2.0f));
    printf("log2f %a = %a\n", (double)0.0f, (double)log2f(0.0f));
    printf("log2f %a = %a\n", (double)POS_INFF, (double)log2f(POS_INFF));
    printf("log2f %a = %a\n", (double)-1.0f, (double)log2f(-1.0f));
    printf("log2f %a = %a\n", (double)NAN, (double)log2f((float)NAN));
    printf("log2f %a = %a\n", (double)FLT_DENORM, (double)log2f(FLT_DENORM));
}

static void test_logbf(void) {
    printf("logbf %a = %a\n", (double)1.0f, (double)logbf(1.0f));
    printf("logbf %a = %a\n", (double)0.0f, (double)logbf(0.0f));
    printf("logbf %a = %a\n", (double)POS_INFF, (double)logbf(POS_INFF));
    printf("logbf %a = %a\n", (double)NAN, (double)logbf((float)NAN));
    printf("logbf %a = %a\n", (double)FLT_DENORM, (double)logbf(FLT_DENORM));
}

static void test_modff(void) {
    float intpart;
    float r;
    r = modff(0.0f, &intpart);   printf("modff %a = %a int %a\n", (double)0.0f, (double)r, (double)intpart);
    r = modff(1.5f, &intpart);   printf("modff %a = %a int %a\n", (double)1.5f, (double)r, (double)intpart);
    r = modff(-1.5f, &intpart);  printf("modff %a = %a int %a\n", (double)-1.5f, (double)r, (double)intpart);
    r = modff(POS_INFF, &intpart); printf("modff %a = %a int %a\n", (double)POS_INFF, (double)r, (double)intpart);
    r = modff((float)NAN, &intpart); printf("modff nan = %a int %a\n", (double)r, (double)intpart);
}

static void test_scalbnf(void) {
    printf("scalbnf %a %d = %a\n", (double)1.0f, 0, (double)scalbnf(1.0f, 0));
    printf("scalbnf %a %d = %a\n", (double)1.0f, 1, (double)scalbnf(1.0f, 1));
    printf("scalbnf %a %d = %a\n", (double)1.0f, -1, (double)scalbnf(1.0f, -1));
    printf("scalbnf %a %d = %a\n", (double)POS_INFF, 1, (double)scalbnf(POS_INFF, 1));
    printf("scalbnf %a %d = %a\n", (double)NAN, 1, (double)scalbnf((float)NAN, 1));
    printf("scalbnf %a %d = %a\n", (double)FLT_DENORM, 149, (double)scalbnf(FLT_DENORM, 149));
    printf("scalbnf %a %d = %a\n", (double)1.0f, 10000, (double)scalbnf(1.0f, 10000));
}

static void test_scalblnf(void) {
    printf("scalblnf %a %ld = %a\n", (double)1.0f, 0L, (double)scalblnf(1.0f, 0L));
    printf("scalblnf %a %ld = %a\n", (double)1.0f, 1L, (double)scalblnf(1.0f, 1L));
    printf("scalblnf %a %ld = %a\n", (double)POS_INFF, 1L, (double)scalblnf(POS_INFF, 1L));
    printf("scalblnf %a %ld = %a\n", (double)NAN, 1L, (double)scalblnf((float)NAN, 1L));
    printf("scalblnf %a %ld = %a\n", (double)1.0f, 100000L, (double)scalblnf(1.0f, 100000L));
}

/* ===== 15. Float power and absolute-value ===== */
static void test_cbrtf(void) {
    printf("cbrtf %a = %a\n", (double)0.0f, (double)cbrtf(0.0f));
    printf("cbrtf %a = %a\n", (double)-0.0f, (double)cbrtf(-0.0f));
    printf("cbrtf %a = %a\n", (double)1.0f, (double)cbrtf(1.0f));
    printf("cbrtf %a = %a\n", (double)-8.0f, (double)cbrtf(-8.0f));
    printf("cbrtf %a = %a\n", (double)POS_INFF, (double)cbrtf(POS_INFF));
    printf("cbrtf %a = %a\n", (double)NAN, (double)cbrtf((float)NAN));
    printf("cbrtf %a = %a\n", (double)FLT_DENORM, (double)cbrtf(FLT_DENORM));
}

static void test_fabsf(void) {
    printf("fabsf %a = %a\n", (double)0.0f, (double)fabsf(0.0f));
    printf("fabsf %a = %a\n", (double)-0.0f, (double)fabsf(-0.0f));
    printf("fabsf %a = %a\n", (double)1.0f, (double)fabsf(1.0f));
    printf("fabsf %a = %a\n", (double)-1.0f, (double)fabsf(-1.0f));
    printf("fabsf %a = %a\n", (double)POS_INFF, (double)fabsf(POS_INFF));
    printf("fabsf %a = %a\n", (double)NEG_INFF, (double)fabsf(NEG_INFF));
    printf("fabsf %a = %a\n", (double)NAN, (double)fabsf((float)NAN));
    printf("fabsf %a = %a\n", (double)FLT_DENORM, (double)fabsf(FLT_DENORM));
}

static void test_hypotf(void) {
    printf("hypotf %a %a = %a\n", (double)3.0f, (double)4.0f, (double)hypotf(3.0f, 4.0f));
    printf("hypotf %a %a = %a\n", (double)0.0f, (double)0.0f, (double)hypotf(0.0f, 0.0f));
    printf("hypotf %a %a = %a\n", (double)POS_INFF, (double)1.0f, (double)hypotf(POS_INFF, 1.0f));
    printf("hypotf %a %a = %a\n", (double)NAN, (double)1.0f, (double)hypotf((float)NAN, 1.0f));
    printf("hypotf %a %a = %a\n", (double)FLT_DENORM, (double)FLT_DENORM, (double)hypotf(FLT_DENORM, FLT_DENORM));
}

static void test_powf(void) {
    printf("powf %a %a = %a\n", (double)2.0f, (double)10.0f, (double)powf(2.0f, 10.0f));
    printf("powf %a %a = %a\n", (double)0.0f, (double)0.0f, (double)powf(0.0f, 0.0f));
    printf("powf %a %a = %a\n", (double)0.0f, (double)-1.0f, (double)powf(0.0f, -1.0f));
    printf("powf %a %a = %a\n", (double)POS_INFF, (double)2.0f, (double)powf(POS_INFF, 2.0f));
    printf("powf %a %a = %a\n", (double)NAN, (double)1.0f, (double)powf((float)NAN, 1.0f));
    printf("powf %a %a = %a\n", (double)1.0f, (double)NAN, (double)powf(1.0f, (float)NAN));
    printf("powf %a %a = %a\n", (double)-2.0f, (double)3.0f, (double)powf(-2.0f, 3.0f));
    printf("powf %a %a = %a\n", (double)-2.0f, (double)0.5f, (double)powf(-2.0f, 0.5f));
}

static void test_sqrtf(void) {
    printf("sqrtf %a = %a\n", (double)0.0f, (double)sqrtf(0.0f));
    printf("sqrtf %a = %a\n", (double)-0.0f, (double)sqrtf(-0.0f));
    printf("sqrtf %a = %a\n", (double)1.0f, (double)sqrtf(1.0f));
    printf("sqrtf %a = %a\n", (double)4.0f, (double)sqrtf(4.0f));
    printf("sqrtf %a = %a\n", (double)POS_INFF, (double)sqrtf(POS_INFF));
    printf("sqrtf %a = %a\n", (double)-1.0f, (double)sqrtf(-1.0f));
    printf("sqrtf %a = %a\n", (double)NAN, (double)sqrtf((float)NAN));
    printf("sqrtf %a = %a\n", (double)FLT_DENORM, (double)sqrtf(FLT_DENORM));
}

/* ===== 16. Float error and gamma ===== */
static void test_erff(void) {
    printf("erff %a = %a\n", (double)0.0f, (double)erff(0.0f));
    printf("erff %a = %a\n", (double)-0.0f, (double)erff(-0.0f));
    printf("erff %a = %a\n", (double)1.0f, (double)erff(1.0f));
    printf("erff %a = %a\n", (double)-1.0f, (double)erff(-1.0f));
    printf("erff %a = %a\n", (double)POS_INFF, (double)erff(POS_INFF));
    printf("erff %a = %a\n", (double)NEG_INFF, (double)erff(NEG_INFF));
    printf("erff %a = %a\n", (double)NAN, (double)erff((float)NAN));
    printf("erff %a = %a\n", (double)FLT_DENORM, (double)erff(FLT_DENORM));
    printf("erff %a = %a\n", (double)6.0f, (double)erff(6.0f));
}

static void test_erfcf(void) {
    printf("erfcf %a = %a\n", (double)0.0f, (double)erfcf(0.0f));
    printf("erfcf %a = %a\n", (double)1.0f, (double)erfcf(1.0f));
    printf("erfcf %a = %a\n", (double)-1.0f, (double)erfcf(-1.0f));
    printf("erfcf %a = %a\n", (double)POS_INFF, (double)erfcf(POS_INFF));
    printf("erfcf %a = %a\n", (double)NEG_INFF, (double)erfcf(NEG_INFF));
    printf("erfcf %a = %a\n", (double)NAN, (double)erfcf((float)NAN));
    printf("erfcf %a = %a\n", (double)10.0f, (double)erfcf(10.0f));
}

static void test_lgammaf(void) {
    printf("lgammaf %a = %a signgam %d\n", (double)1.0f, (double)lgammaf(1.0f), signgam);
    printf("lgammaf %a = %a signgam %d\n", (double)0.5f, (double)lgammaf(0.5f), signgam);
    printf("lgammaf %a = %a signgam %d\n", (double)POS_INFF, (double)lgammaf(POS_INFF), signgam);
    printf("lgammaf %a = %a signgam %d\n", (double)NAN, (double)lgammaf((float)NAN), signgam);
    printf("lgammaf %a = %a signgam %d\n", (double)0.0f, (double)lgammaf(0.0f), signgam);
    printf("lgammaf %a = %a signgam %d\n", (double)-0.5f, (double)lgammaf(-0.5f), signgam);
}

static void test_tgammaf(void) {
    printf("tgammaf %a = %a\n", (double)1.0f, (double)tgammaf(1.0f));
    printf("tgammaf %a = %a\n", (double)0.5f, (double)tgammaf(0.5f));
    printf("tgammaf %a = %a\n", (double)0.0f, (double)tgammaf(0.0f));
    printf("tgammaf %a = %a\n", (double)-0.0f, (double)tgammaf(-0.0f));
    printf("tgammaf %a = %a\n", (double)POS_INFF, (double)tgammaf(POS_INFF));
    printf("tgammaf %a = %a\n", (double)NAN, (double)tgammaf((float)NAN));
    printf("tgammaf %a = %a\n", (double)-1.0f, (double)tgammaf(-1.0f));
    printf("tgammaf %a = %a\n", (double)36.0f, (double)tgammaf(36.0f));
}

/* ===== 17. Float nearest integer ===== */
static void test_ceilf(void) {
    printf("ceilf %a = %a\n", (double)0.0f, (double)ceilf(0.0f));
    printf("ceilf %a = %a\n", (double)0.5f, (double)ceilf(0.5f));
    printf("ceilf %a = %a\n", (double)-0.5f, (double)ceilf(-0.5f));
    printf("ceilf %a = %a\n", (double)POS_INFF, (double)ceilf(POS_INFF));
    printf("ceilf %a = %a\n", (double)NAN, (double)ceilf((float)NAN));
    printf("ceilf %a = %a\n", (double)FLT_DENORM, (double)ceilf(FLT_DENORM));
}

static void test_floorf(void) {
    printf("floorf %a = %a\n", (double)0.0f, (double)floorf(0.0f));
    printf("floorf %a = %a\n", (double)0.5f, (double)floorf(0.5f));
    printf("floorf %a = %a\n", (double)-0.5f, (double)floorf(-0.5f));
    printf("floorf %a = %a\n", (double)POS_INFF, (double)floorf(POS_INFF));
    printf("floorf %a = %a\n", (double)NAN, (double)floorf((float)NAN));
    printf("floorf %a = %a\n", (double)FLT_DENORM, (double)floorf(FLT_DENORM));
}

static void test_nearbyintf(void) {
    printf("nearbyintf %a = %a\n", (double)0.0f, (double)nearbyintf(0.0f));
    printf("nearbyintf %a = %a\n", (double)0.5f, (double)nearbyintf(0.5f));
    printf("nearbyintf %a = %a\n", (double)-0.5f, (double)nearbyintf(-0.5f));
    printf("nearbyintf %a = %a\n", (double)1.5f, (double)nearbyintf(1.5f));
    printf("nearbyintf %a = %a\n", (double)POS_INFF, (double)nearbyintf(POS_INFF));
    printf("nearbyintf %a = %a\n", (double)NAN, (double)nearbyintf((float)NAN));
    printf("nearbyintf %a = %a\n", (double)FLT_DENORM, (double)nearbyintf(FLT_DENORM));
}

static void test_rintf(void) {
    printf("rintf %a = %a\n", (double)0.0f, (double)rintf(0.0f));
    printf("rintf %a = %a\n", (double)0.5f, (double)rintf(0.5f));
    printf("rintf %a = %a\n", (double)-0.5f, (double)rintf(-0.5f));
    printf("rintf %a = %a\n", (double)1.5f, (double)rintf(1.5f));
    printf("rintf %a = %a\n", (double)POS_INFF, (double)rintf(POS_INFF));
    printf("rintf %a = %a\n", (double)NAN, (double)rintf((float)NAN));
    printf("rintf %a = %a\n", (double)FLT_DENORM, (double)rintf(FLT_DENORM));
}

static void test_lrintf(void) {
    printf("lrintf %a = %ld\n", (double)0.0f, lrintf(0.0f));
    printf("lrintf %a = %ld\n", (double)0.5f, lrintf(0.5f));
    printf("lrintf %a = %ld\n", (double)-0.5f, lrintf(-0.5f));
    printf("lrintf %a = %ld\n", (double)1.5f, lrintf(1.5f));
    printf("lrintf %a = %ld\n", (double)1e6f, lrintf(1e6f));
}

static void test_llrintf(void) {
    printf("llrintf %a = %lld\n", (double)0.0f, llrintf(0.0f));
    printf("llrintf %a = %lld\n", (double)0.5f, llrintf(0.5f));
    printf("llrintf %a = %lld\n", (double)-0.5f, llrintf(-0.5f));
    printf("llrintf %a = %lld\n", (double)1.5f, llrintf(1.5f));
    printf("llrintf %a = %lld\n", (double)1e9f, llrintf(1e9f));
}

static void test_roundf(void) {
    printf("roundf %a = %a\n", (double)0.0f, (double)roundf(0.0f));
    printf("roundf %a = %a\n", (double)0.5f, (double)roundf(0.5f));
    printf("roundf %a = %a\n", (double)-0.5f, (double)roundf(-0.5f));
    printf("roundf %a = %a\n", (double)1.5f, (double)roundf(1.5f));
    printf("roundf %a = %a\n", (double)POS_INFF, (double)roundf(POS_INFF));
    printf("roundf %a = %a\n", (double)NAN, (double)roundf((float)NAN));
    printf("roundf %a = %a\n", (double)FLT_DENORM, (double)roundf(FLT_DENORM));
}

static void test_lroundf(void) {
    printf("lroundf %a = %ld\n", (double)0.0f, lroundf(0.0f));
    printf("lroundf %a = %ld\n", (double)0.5f, lroundf(0.5f));
    printf("lroundf %a = %ld\n", (double)-0.5f, lroundf(-0.5f));
    printf("lroundf %a = %ld\n", (double)1.5f, lroundf(1.5f));
    printf("lroundf %a = %ld\n", (double)1e6f, lroundf(1e6f));
}

static void test_llroundf(void) {
    printf("llroundf %a = %lld\n", (double)0.0f, llroundf(0.0f));
    printf("llroundf %a = %lld\n", (double)0.5f, llroundf(0.5f));
    printf("llroundf %a = %lld\n", (double)-0.5f, llroundf(-0.5f));
    printf("llroundf %a = %lld\n", (double)1.5f, llroundf(1.5f));
    printf("llroundf %a = %lld\n", (double)1e9f, llroundf(1e9f));
}

static void test_truncf(void) {
    printf("truncf %a = %a\n", (double)0.0f, (double)truncf(0.0f));
    printf("truncf %a = %a\n", (double)0.5f, (double)truncf(0.5f));
    printf("truncf %a = %a\n", (double)-0.5f, (double)truncf(-0.5f));
    printf("truncf %a = %a\n", (double)1.9f, (double)truncf(1.9f));
    printf("truncf %a = %a\n", (double)POS_INFF, (double)truncf(POS_INFF));
    printf("truncf %a = %a\n", (double)NAN, (double)truncf((float)NAN));
    printf("truncf %a = %a\n", (double)FLT_DENORM, (double)truncf(FLT_DENORM));
}

/* ===== 18. Float remainder ===== */
static void test_fmodf(void) {
    printf("fmodf %a %a = %a\n", (double)5.0f, (double)3.0f, (double)fmodf(5.0f, 3.0f));
    printf("fmodf %a %a = %a\n", (double)-5.0f, (double)3.0f, (double)fmodf(-5.0f, 3.0f));
    printf("fmodf %a %a = %a\n", (double)1.0f, (double)0.0f, (double)fmodf(1.0f, 0.0f));
    printf("fmodf %a %a = %a\n", (double)POS_INFF, (double)1.0f, (double)fmodf(POS_INFF, 1.0f));
    printf("fmodf %a %a = %a\n", (double)NAN, (double)1.0f, (double)fmodf((float)NAN, 1.0f));
    printf("fmodf %a %a = %a\n", (double)FLT_DENORM, (double)1.0f, (double)fmodf(FLT_DENORM, 1.0f));
}

static void test_remainderf(void) {
    printf("remainderf %a %a = %a\n", (double)5.0f, (double)3.0f, (double)remainderf(5.0f, 3.0f));
    printf("remainderf %a %a = %a\n", (double)-5.0f, (double)3.0f, (double)remainderf(-5.0f, 3.0f));
    printf("remainderf %a %a = %a\n", (double)POS_INFF, (double)1.0f, (double)remainderf(POS_INFF, 1.0f));
    printf("remainderf %a %a = %a\n", (double)NAN, (double)1.0f, (double)remainderf((float)NAN, 1.0f));
    printf("remainderf %a %a = %a\n", (double)1.0f, (double)0.0f, (double)remainderf(1.0f, 0.0f));
}

static void test_remquof(void) {
    int quo;
    float r;
    r = remquof(5.0f, 3.0f, &quo);   printf("remquof %a %a = %a quo %d\n", (double)5.0f, (double)3.0f, (double)r, quo);
    r = remquof(-5.0f, 3.0f, &quo);  printf("remquof %a %a = %a quo %d\n", (double)-5.0f, (double)3.0f, (double)r, quo);
    r = remquof(POS_INFF, 1.0f, &quo); printf("remquof %a %a = %a quo %d\n", (double)POS_INFF, (double)1.0f, (double)r, quo);
    r = remquof((float)NAN, 1.0f, &quo); printf("remquof nan %a = %a quo %d\n", (double)1.0f, (double)r, quo);
}

/* ===== 19. Float manipulation ===== */
static void test_copysignf(void) {
    printf("copysignf %a %a = %a\n", (double)1.0f, (double)-1.0f, (double)copysignf(1.0f, -1.0f));
    printf("copysignf %a %a = %a\n", (double)-1.0f, (double)1.0f, (double)copysignf(-1.0f, 1.0f));
    printf("copysignf %a %a = %a\n", (double)0.0f, (double)-1.0f, (double)copysignf(0.0f, -1.0f));
    printf("copysignf %a %a = %a\n", (double)POS_INFF, (double)-1.0f, (double)copysignf(POS_INFF, -1.0f));
    printf("copysignf %a %a = %a\n", (double)NAN, (double)-1.0f, (double)copysignf((float)NAN, -1.0f));
    printf("copysignf %a %a = %a\n", (double)FLT_DENORM, (double)-1.0f, (double)copysignf(FLT_DENORM, -1.0f));
}

static void test_nanf(void) {
    float r = nanf("");
    printf("nanf \"\" isnan = %d\n", r != r ? 1 : 0);
    r = nanf("1");
    printf("nanf \"1\" isnan = %d\n", r != r ? 1 : 0);
}

static void test_nextafterf(void) {
    printf("nextafterf %a %a = %a\n", (double)0.0f, (double)1.0f, (double)nextafterf(0.0f, 1.0f));
    printf("nextafterf %a %a = %a\n", (double)0.0f, (double)-1.0f, (double)nextafterf(0.0f, -1.0f));
    printf("nextafterf %a %a = %a\n", (double)1.0f, (double)2.0f, (double)nextafterf(1.0f, 2.0f));
    printf("nextafterf %a %a = %a\n", (double)POS_INFF, (double)0.0f, (double)nextafterf(POS_INFF, 0.0f));
    printf("nextafterf %a %a = %a\n", (double)NAN, (double)1.0f, (double)nextafterf((float)NAN, 1.0f));
    printf("nextafterf %a %a = %a\n", (double)FLT_DENORM, (double)0.0f, (double)nextafterf(FLT_DENORM, 0.0f));
}

/* ===== 20. Float max/min/fdim ===== */
static void test_fdimf(void) {
    printf("fdimf %a %a = %a\n", (double)3.0f, (double)1.0f, (double)fdimf(3.0f, 1.0f));
    printf("fdimf %a %a = %a\n", (double)1.0f, (double)3.0f, (double)fdimf(1.0f, 3.0f));
    printf("fdimf %a %a = %a\n", (double)NAN, (double)1.0f, (double)fdimf((float)NAN, 1.0f));
    printf("fdimf %a %a = %a\n", (double)1.0f, (double)NAN, (double)fdimf(1.0f, (float)NAN));
}

static void test_fmaxf(void) {
    printf("fmaxf %a %a = %a\n", (double)1.0f, (double)2.0f, (double)fmaxf(1.0f, 2.0f));
    printf("fmaxf %a %a = %a\n", (double)NAN, (double)1.0f, (double)fmaxf((float)NAN, 1.0f));
    printf("fmaxf %a %a = %a\n", (double)POS_INFF, (double)NEG_INFF, (double)fmaxf(POS_INFF, NEG_INFF));
}

static void test_fminf(void) {
    printf("fminf %a %a = %a\n", (double)1.0f, (double)2.0f, (double)fminf(1.0f, 2.0f));
    printf("fminf %a %a = %a\n", (double)NAN, (double)1.0f, (double)fminf((float)NAN, 1.0f));
    printf("fminf %a %a = %a\n", (double)POS_INFF, (double)NEG_INFF, (double)fminf(POS_INFF, NEG_INFF));
}

/* ===== 21. Float fma ===== */
static void test_fmaf(void) {
    printf("fmaf %a %a %a = %a\n", (double)2.0f, (double)3.0f, (double)4.0f, (double)fmaf(2.0f, 3.0f, 4.0f));
    printf("fmaf %a %a %a = %a\n", (double)0.0f, (double)1.0f, (double)1.0f, (double)fmaf(0.0f, 1.0f, 1.0f));
    printf("fmaf %a %a %a = %a\n", (double)NAN, (double)1.0f, (double)1.0f, (double)fmaf((float)NAN, 1.0f, 1.0f));
    printf("fmaf %a %a %a = %a\n", (double)POS_INFF, (double)1.0f, (double)NEG_INFF, (double)fmaf(POS_INFF, 1.0f, NEG_INFF));
    printf("fmaf %a %a %a = %a\n", (double)FLT_DENORM, (double)2.0f, (double)0.0f, (double)fmaf(FLT_DENORM, 2.0f, 0.0f));
}

/* ===== 22-26. Complex double functions ===== */
static void test_cacos(void) {
    double complex z, r;
    z = CMPLX(0.0, 0.0);  r = cacos(z);  print_cdbl("cacos", z, r);
    z = CMPLX(1.0, 0.0);  r = cacos(z);  print_cdbl("cacos", z, r);
    z = CMPLX(0.0, 1.0);  r = cacos(z);  print_cdbl("cacos", z, r);
    z = CMPLX(POS_INF, 0.0); r = cacos(z); print_cdbl("cacos", z, r);
    z = CMPLX((double)NAN, (double)NAN); r = cacos(z); print_cdbl("cacos", z, r);
    z = CMPLX(-0.0, 0.0); r = cacos(z);  print_cdbl("cacos", z, r);
}

static void test_casin(void) {
    double complex z, r;
    z = CMPLX(0.0, 0.0);  r = casin(z);  print_cdbl("casin", z, r);
    z = CMPLX(1.0, 0.0);  r = casin(z);  print_cdbl("casin", z, r);
    z = CMPLX(0.0, 1.0);  r = casin(z);  print_cdbl("casin", z, r);
    z = CMPLX(POS_INF, 1.0); r = casin(z); print_cdbl("casin", z, r);
    z = CMPLX((double)NAN, 0.0); r = casin(z); print_cdbl("casin", z, r);
}

static void test_catan(void) {
    double complex z, r;
    z = CMPLX(0.0, 0.0);  r = catan(z);  print_cdbl("catan", z, r);
    z = CMPLX(1.0, 0.0);  r = catan(z);  print_cdbl("catan", z, r);
    z = CMPLX(0.0, 1.0);  r = catan(z);  print_cdbl("catan", z, r);
    z = CMPLX(POS_INF, 1.0); r = catan(z); print_cdbl("catan", z, r);
    z = CMPLX((double)NAN, 0.0); r = catan(z); print_cdbl("catan", z, r);
    z = CMPLX(0.0, POS_INF); r = catan(z); print_cdbl("catan", z, r);
}

static void test_ccos(void) {
    double complex z, r;
    z = CMPLX(0.0, 0.0);  r = ccos(z);   print_cdbl("ccos", z, r);
    z = CMPLX(1.0, 0.0);  r = ccos(z);   print_cdbl("ccos", z, r);
    z = CMPLX(0.0, 1.0);  r = ccos(z);   print_cdbl("ccos", z, r);
    z = CMPLX(1.0, 1.0);  r = ccos(z);   print_cdbl("ccos", z, r);
    z = CMPLX(POS_INF, 0.0); r = ccos(z); print_cdbl("ccos", z, r);
    z = CMPLX((double)NAN, 0.0); r = ccos(z); print_cdbl("ccos", z, r);
}

static void test_csin(void) {
    double complex z, r;
    z = CMPLX(0.0, 0.0);  r = csin(z);   print_cdbl("csin", z, r);
    z = CMPLX(1.0, 0.0);  r = csin(z);   print_cdbl("csin", z, r);
    z = CMPLX(0.0, 1.0);  r = csin(z);   print_cdbl("csin", z, r);
    z = CMPLX(1.0, 1.0);  r = csin(z);   print_cdbl("csin", z, r);
    z = CMPLX(POS_INF, 0.0); r = csin(z); print_cdbl("csin", z, r);
    z = CMPLX((double)NAN, 0.0); r = csin(z); print_cdbl("csin", z, r);
}

static void test_ctan(void) {
    double complex z, r;
    z = CMPLX(0.0, 0.0);  r = ctan(z);   print_cdbl("ctan", z, r);
    z = CMPLX(1.0, 0.0);  r = ctan(z);   print_cdbl("ctan", z, r);
    z = CMPLX(0.0, 1.0);  r = ctan(z);   print_cdbl("ctan", z, r);
    z = CMPLX(1.0, 1.0);  r = ctan(z);   print_cdbl("ctan", z, r);
    z = CMPLX(POS_INF, 0.0); r = ctan(z); print_cdbl("ctan", z, r);
    z = CMPLX((double)NAN, 0.0); r = ctan(z); print_cdbl("ctan", z, r);
    z = CMPLX(0.0, POS_INF); r = ctan(z); print_cdbl("ctan", z, r);
}

static void test_cacosh(void) {
    double complex z, r;
    z = CMPLX(1.0, 0.0);  r = cacosh(z); print_cdbl("cacosh", z, r);
    z = CMPLX(0.0, 0.0);  r = cacosh(z); print_cdbl("cacosh", z, r);
    z = CMPLX(0.0, 1.0);  r = cacosh(z); print_cdbl("cacosh", z, r);
    z = CMPLX(POS_INF, 1.0); r = cacosh(z); print_cdbl("cacosh", z, r);
    z = CMPLX((double)NAN, 0.0); r = cacosh(z); print_cdbl("cacosh", z, r);
}

static void test_casinh(void) {
    double complex z, r;
    z = CMPLX(0.0, 0.0);  r = casinh(z); print_cdbl("casinh", z, r);
    z = CMPLX(1.0, 0.0);  r = casinh(z); print_cdbl("casinh", z, r);
    z = CMPLX(0.0, 1.0);  r = casinh(z); print_cdbl("casinh", z, r);
    z = CMPLX(POS_INF, 1.0); r = casinh(z); print_cdbl("casinh", z, r);
    z = CMPLX((double)NAN, 0.0); r = casinh(z); print_cdbl("casinh", z, r);
}

static void test_catanh(void) {
    double complex z, r;
    z = CMPLX(0.0, 0.0);  r = catanh(z); print_cdbl("catanh", z, r);
    z = CMPLX(1.0, 0.0);  r = catanh(z); print_cdbl("catanh", z, r);
    z = CMPLX(0.0, 1.0);  r = catanh(z); print_cdbl("catanh", z, r);
    z = CMPLX(POS_INF, 1.0); r = catanh(z); print_cdbl("catanh", z, r);
    z = CMPLX((double)NAN, 0.0); r = catanh(z); print_cdbl("catanh", z, r);
    z = CMPLX(0.0, POS_INF); r = catanh(z); print_cdbl("catanh", z, r);
}

static void test_ccosh(void) {
    double complex z, r;
    z = CMPLX(0.0, 0.0);  r = ccosh(z);  print_cdbl("ccosh", z, r);
    z = CMPLX(1.0, 0.0);  r = ccosh(z);  print_cdbl("ccosh", z, r);
    z = CMPLX(0.0, 1.0);  r = ccosh(z);  print_cdbl("ccosh", z, r);
    z = CMPLX(1.0, 1.0);  r = ccosh(z);  print_cdbl("ccosh", z, r);
    z = CMPLX(POS_INF, 0.0); r = ccosh(z); print_cdbl("ccosh", z, r);
    z = CMPLX((double)NAN, 0.0); r = ccosh(z); print_cdbl("ccosh", z, r);
}

static void test_csinh(void) {
    double complex z, r;
    z = CMPLX(0.0, 0.0);  r = csinh(z);  print_cdbl("csinh", z, r);
    z = CMPLX(1.0, 0.0);  r = csinh(z);  print_cdbl("csinh", z, r);
    z = CMPLX(0.0, 1.0);  r = csinh(z);  print_cdbl("csinh", z, r);
    z = CMPLX(1.0, 1.0);  r = csinh(z);  print_cdbl("csinh", z, r);
    z = CMPLX(POS_INF, 0.0); r = csinh(z); print_cdbl("csinh", z, r);
    z = CMPLX((double)NAN, 0.0); r = csinh(z); print_cdbl("csinh", z, r);
}

static void test_ctanh(void) {
    double complex z, r;
    z = CMPLX(0.0, 0.0);  r = ctanh(z);  print_cdbl("ctanh", z, r);
    z = CMPLX(1.0, 0.0);  r = ctanh(z);  print_cdbl("ctanh", z, r);
    z = CMPLX(0.0, 1.0);  r = ctanh(z);  print_cdbl("ctanh", z, r);
    z = CMPLX(1.0, 1.0);  r = ctanh(z);  print_cdbl("ctanh", z, r);
    z = CMPLX(POS_INF, 0.0); r = ctanh(z); print_cdbl("ctanh", z, r);
    z = CMPLX((double)NAN, 0.0); r = ctanh(z); print_cdbl("ctanh", z, r);
    z = CMPLX(0.0, POS_INF); r = ctanh(z); print_cdbl("ctanh", z, r);
}

static void test_cexp(void) {
    double complex z, r;
    z = CMPLX(0.0, 0.0);  r = cexp(z);   print_cdbl("cexp", z, r);
    z = CMPLX(1.0, 0.0);  r = cexp(z);   print_cdbl("cexp", z, r);
    z = CMPLX(0.0, 1.0);  r = cexp(z);   print_cdbl("cexp", z, r);
    z = CMPLX(1.0, M_PI); r = cexp(z);   print_cdbl("cexp", z, r);
    z = CMPLX(POS_INF, 0.0); r = cexp(z); print_cdbl("cexp", z, r);
    z = CMPLX(NEG_INF, 0.0); r = cexp(z); print_cdbl("cexp", z, r);
    z = CMPLX((double)NAN, 0.0); r = cexp(z); print_cdbl("cexp", z, r);
}

static void test_clog(void) {
    double complex z, r;
    z = CMPLX(1.0, 0.0);  r = clog(z);   print_cdbl("clog", z, r);
    z = CMPLX(0.0, 1.0);  r = clog(z);   print_cdbl("clog", z, r);
    z = CMPLX(-1.0, 0.0); r = clog(z);   print_cdbl("clog", z, r);
    z = CMPLX(0.0, 0.0);  r = clog(z);   print_cdbl("clog", z, r);
    z = CMPLX(POS_INF, 0.0); r = clog(z); print_cdbl("clog", z, r);
    z = CMPLX((double)NAN, 0.0); r = clog(z); print_cdbl("clog", z, r);
}

static void test_cabs(void) {
    double complex z;
    z = CMPLX(3.0, 4.0);   printf("cabs (%a,%a) = %a\n", creal(z), cimag(z), cabs(z));
    z = CMPLX(0.0, 0.0);   printf("cabs (%a,%a) = %a\n", creal(z), cimag(z), cabs(z));
    z = CMPLX(POS_INF, 0.0); printf("cabs (%a,%a) = %a\n", creal(z), cimag(z), cabs(z));
    z = CMPLX((double)NAN, 0.0); printf("cabs (%a,%a) = %a\n", creal(z), cimag(z), cabs(z));
    z = CMPLX(1.0, POS_INF); printf("cabs (%a,%a) = %a\n", creal(z), cimag(z), cabs(z));
    z = CMPLX(-3.0, -4.0); printf("cabs (%a,%a) = %a\n", creal(z), cimag(z), cabs(z));
}

static void test_cpow(void) {
    double complex z, w, r;
    z = CMPLX(1.0, 0.0); w = CMPLX(2.0, 0.0); r = cpow(z, w); print_cdbl2("cpow", z, w, r);
    z = CMPLX(2.0, 0.0); w = CMPLX(0.5, 0.0); r = cpow(z, w); print_cdbl2("cpow", z, w, r);
    z = CMPLX(0.0, 1.0); w = CMPLX(2.0, 0.0); r = cpow(z, w); print_cdbl2("cpow", z, w, r);
    z = CMPLX(0.0, 0.0); w = CMPLX(1.0, 0.0); r = cpow(z, w); print_cdbl2("cpow", z, w, r);
    z = CMPLX((double)NAN, 0.0); w = CMPLX(1.0, 0.0); r = cpow(z, w); print_cdbl2("cpow", z, w, r);
}

static void test_csqrt(void) {
    double complex z, r;
    z = CMPLX(0.0, 0.0);  r = csqrt(z);  print_cdbl("csqrt", z, r);
    z = CMPLX(1.0, 0.0);  r = csqrt(z);  print_cdbl("csqrt", z, r);
    z = CMPLX(-1.0, 0.0); r = csqrt(z);  print_cdbl("csqrt", z, r);
    z = CMPLX(0.0, 1.0);  r = csqrt(z);  print_cdbl("csqrt", z, r);
    z = CMPLX(3.0, 4.0);  r = csqrt(z);  print_cdbl("csqrt", z, r);
    z = CMPLX(POS_INF, 0.0); r = csqrt(z); print_cdbl("csqrt", z, r);
    z = CMPLX((double)NAN, 0.0); r = csqrt(z); print_cdbl("csqrt", z, r);
}

static void test_carg(void) {
    double complex z;
    z = CMPLX(1.0, 0.0);   printf("carg (%a,%a) = %a\n", creal(z), cimag(z), carg(z));
    z = CMPLX(-1.0, 0.0);  printf("carg (%a,%a) = %a\n", creal(z), cimag(z), carg(z));
    z = CMPLX(0.0, 1.0);   printf("carg (%a,%a) = %a\n", creal(z), cimag(z), carg(z));
    z = CMPLX(0.0, -1.0);  printf("carg (%a,%a) = %a\n", creal(z), cimag(z), carg(z));
    z = CMPLX(1.0, 1.0);   printf("carg (%a,%a) = %a\n", creal(z), cimag(z), carg(z));
    z = CMPLX(0.0, 0.0);   printf("carg (%a,%a) = %a\n", creal(z), cimag(z), carg(z));
    z = CMPLX((double)NAN, 0.0); printf("carg (%a,%a) = %a\n", creal(z), cimag(z), carg(z));
}

static void test_cimag(void) {
    double complex z;
    z = CMPLX(1.0, 2.0);  printf("cimag (%a,%a) = %a\n", creal(z), cimag(z), cimag(z));
    z = CMPLX(0.0, -0.0); printf("cimag (%a,%a) = %a\n", creal(z), cimag(z), cimag(z));
    z = CMPLX(POS_INF, POS_INF); printf("cimag (%a,%a) = %a\n", creal(z), cimag(z), cimag(z));
    z = CMPLX((double)NAN, 1.0); printf("cimag (%a,%a) = %a\n", creal(z), cimag(z), cimag(z));
}

static void test_conj(void) {
    double complex z, r;
    z = CMPLX(1.0, 2.0);  r = conj(z);  print_cdbl("conj", z, r);
    z = CMPLX(1.0, -2.0); r = conj(z);  print_cdbl("conj", z, r);
    z = CMPLX(0.0, 0.0);  r = conj(z);  print_cdbl("conj", z, r);
    z = CMPLX(POS_INF, POS_INF); r = conj(z); print_cdbl("conj", z, r);
    z = CMPLX((double)NAN, 0.0); r = conj(z); print_cdbl("conj", z, r);
}

static void test_cproj(void) {
    double complex z, r;
    z = CMPLX(1.0, 2.0);  r = cproj(z); print_cdbl("cproj", z, r);
    z = CMPLX(POS_INF, 0.0); r = cproj(z); print_cdbl("cproj", z, r);
    z = CMPLX(POS_INF, NEG_INF); r = cproj(z); print_cdbl("cproj", z, r);
    z = CMPLX((double)NAN, POS_INF); r = cproj(z); print_cdbl("cproj", z, r);
    z = CMPLX(0.0, 0.0);  r = cproj(z); print_cdbl("cproj", z, r);
}

static void test_creal(void) {
    double complex z;
    z = CMPLX(1.0, 2.0);  printf("creal (%a,%a) = %a\n", creal(z), cimag(z), creal(z));
    z = CMPLX(-0.0, 0.0); printf("creal (%a,%a) = %a\n", creal(z), cimag(z), creal(z));
    z = CMPLX(POS_INF, 0.0); printf("creal (%a,%a) = %a\n", creal(z), cimag(z), creal(z));
    z = CMPLX((double)NAN, 1.0); printf("creal (%a,%a) = %a\n", creal(z), cimag(z), creal(z));
}

/* ===== 27-31. Complex float functions ===== */
static void test_cacosf(void) {
    float complex z, r;
    z = CMPLXF(0.0f, 0.0f);  r = cacosf(z);  print_cflt("cacosf", z, r);
    z = CMPLXF(1.0f, 0.0f);  r = cacosf(z);  print_cflt("cacosf", z, r);
    z = CMPLXF(0.0f, 1.0f);  r = cacosf(z);  print_cflt("cacosf", z, r);
    z = CMPLXF(POS_INFF, 0.0f); r = cacosf(z); print_cflt("cacosf", z, r);
    z = CMPLXF((float)NAN, (float)NAN); r = cacosf(z); print_cflt("cacosf", z, r);
}

static void test_casinf(void) {
    float complex z, r;
    z = CMPLXF(0.0f, 0.0f);  r = casinf(z);  print_cflt("casinf", z, r);
    z = CMPLXF(1.0f, 0.0f);  r = casinf(z);  print_cflt("casinf", z, r);
    z = CMPLXF(0.0f, 1.0f);  r = casinf(z);  print_cflt("casinf", z, r);
    z = CMPLXF(POS_INFF, 1.0f); r = casinf(z); print_cflt("casinf", z, r);
    z = CMPLXF((float)NAN, 0.0f); r = casinf(z); print_cflt("casinf", z, r);
}

static void test_catanf(void) {
    float complex z, r;
    z = CMPLXF(0.0f, 0.0f);  r = catanf(z);  print_cflt("catanf", z, r);
    z = CMPLXF(1.0f, 0.0f);  r = catanf(z);  print_cflt("catanf", z, r);
    z = CMPLXF(0.0f, 1.0f);  r = catanf(z);  print_cflt("catanf", z, r);
    z = CMPLXF(POS_INFF, 1.0f); r = catanf(z); print_cflt("catanf", z, r);
    z = CMPLXF((float)NAN, 0.0f); r = catanf(z); print_cflt("catanf", z, r);
}

static void test_ccosf(void) {
    float complex z, r;
    z = CMPLXF(0.0f, 0.0f);  r = ccosf(z);   print_cflt("ccosf", z, r);
    z = CMPLXF(1.0f, 0.0f);  r = ccosf(z);   print_cflt("ccosf", z, r);
    z = CMPLXF(0.0f, 1.0f);  r = ccosf(z);   print_cflt("ccosf", z, r);
    z = CMPLXF(1.0f, 1.0f);  r = ccosf(z);   print_cflt("ccosf", z, r);
    z = CMPLXF(POS_INFF, 0.0f); r = ccosf(z); print_cflt("ccosf", z, r);
    z = CMPLXF((float)NAN, 0.0f); r = ccosf(z); print_cflt("ccosf", z, r);
}

static void test_csinf(void) {
    float complex z, r;
    z = CMPLXF(0.0f, 0.0f);  r = csinf(z);   print_cflt("csinf", z, r);
    z = CMPLXF(1.0f, 0.0f);  r = csinf(z);   print_cflt("csinf", z, r);
    z = CMPLXF(0.0f, 1.0f);  r = csinf(z);   print_cflt("csinf", z, r);
    z = CMPLXF(1.0f, 1.0f);  r = csinf(z);   print_cflt("csinf", z, r);
    z = CMPLXF(POS_INFF, 0.0f); r = csinf(z); print_cflt("csinf", z, r);
    z = CMPLXF((float)NAN, 0.0f); r = csinf(z); print_cflt("csinf", z, r);
}

static void test_ctanf(void) {
    float complex z, r;
    z = CMPLXF(0.0f, 0.0f);  r = ctanf(z);   print_cflt("ctanf", z, r);
    z = CMPLXF(1.0f, 0.0f);  r = ctanf(z);   print_cflt("ctanf", z, r);
    z = CMPLXF(0.0f, 1.0f);  r = ctanf(z);   print_cflt("ctanf", z, r);
    z = CMPLXF(1.0f, 1.0f);  r = ctanf(z);   print_cflt("ctanf", z, r);
    z = CMPLXF(POS_INFF, 0.0f); r = ctanf(z); print_cflt("ctanf", z, r);
    z = CMPLXF((float)NAN, 0.0f); r = ctanf(z); print_cflt("ctanf", z, r);
}

static void test_cacoshf(void) {
    float complex z, r;
    z = CMPLXF(1.0f, 0.0f);  r = cacoshf(z); print_cflt("cacoshf", z, r);
    z = CMPLXF(0.0f, 0.0f);  r = cacoshf(z); print_cflt("cacoshf", z, r);
    z = CMPLXF(0.0f, 1.0f);  r = cacoshf(z); print_cflt("cacoshf", z, r);
    z = CMPLXF(POS_INFF, 1.0f); r = cacoshf(z); print_cflt("cacoshf", z, r);
    z = CMPLXF((float)NAN, 0.0f); r = cacoshf(z); print_cflt("cacoshf", z, r);
}

static void test_casinhf(void) {
    float complex z, r;
    z = CMPLXF(0.0f, 0.0f);  r = casinhf(z); print_cflt("casinhf", z, r);
    z = CMPLXF(1.0f, 0.0f);  r = casinhf(z); print_cflt("casinhf", z, r);
    z = CMPLXF(0.0f, 1.0f);  r = casinhf(z); print_cflt("casinhf", z, r);
    z = CMPLXF(POS_INFF, 1.0f); r = casinhf(z); print_cflt("casinhf", z, r);
    z = CMPLXF((float)NAN, 0.0f); r = casinhf(z); print_cflt("casinhf", z, r);
}

static void test_catanhf(void) {
    float complex z, r;
    z = CMPLXF(0.0f, 0.0f);  r = catanhf(z); print_cflt("catanhf", z, r);
    z = CMPLXF(1.0f, 0.0f);  r = catanhf(z); print_cflt("catanhf", z, r);
    z = CMPLXF(0.0f, 1.0f);  r = catanhf(z); print_cflt("catanhf", z, r);
    z = CMPLXF(POS_INFF, 1.0f); r = catanhf(z); print_cflt("catanhf", z, r);
    z = CMPLXF((float)NAN, 0.0f); r = catanhf(z); print_cflt("catanhf", z, r);
}

static void test_ccoshf(void) {
    float complex z, r;
    z = CMPLXF(0.0f, 0.0f);  r = ccoshf(z);  print_cflt("ccoshf", z, r);
    z = CMPLXF(1.0f, 0.0f);  r = ccoshf(z);  print_cflt("ccoshf", z, r);
    z = CMPLXF(0.0f, 1.0f);  r = ccoshf(z);  print_cflt("ccoshf", z, r);
    z = CMPLXF(1.0f, 1.0f);  r = ccoshf(z);  print_cflt("ccoshf", z, r);
    z = CMPLXF(POS_INFF, 0.0f); r = ccoshf(z); print_cflt("ccoshf", z, r);
    z = CMPLXF((float)NAN, 0.0f); r = ccoshf(z); print_cflt("ccoshf", z, r);
}

static void test_csinhf(void) {
    float complex z, r;
    z = CMPLXF(0.0f, 0.0f);  r = csinhf(z);  print_cflt("csinhf", z, r);
    z = CMPLXF(1.0f, 0.0f);  r = csinhf(z);  print_cflt("csinhf", z, r);
    z = CMPLXF(0.0f, 1.0f);  r = csinhf(z);  print_cflt("csinhf", z, r);
    z = CMPLXF(1.0f, 1.0f);  r = csinhf(z);  print_cflt("csinhf", z, r);
    z = CMPLXF(POS_INFF, 0.0f); r = csinhf(z); print_cflt("csinhf", z, r);
    z = CMPLXF((float)NAN, 0.0f); r = csinhf(z); print_cflt("csinhf", z, r);
}

static void test_ctanhf(void) {
    float complex z, r;
    z = CMPLXF(0.0f, 0.0f);  r = ctanhf(z);  print_cflt("ctanhf", z, r);
    z = CMPLXF(1.0f, 0.0f);  r = ctanhf(z);  print_cflt("ctanhf", z, r);
    z = CMPLXF(0.0f, 1.0f);  r = ctanhf(z);  print_cflt("ctanhf", z, r);
    z = CMPLXF(1.0f, 1.0f);  r = ctanhf(z);  print_cflt("ctanhf", z, r);
    z = CMPLXF(POS_INFF, 0.0f); r = ctanhf(z); print_cflt("ctanhf", z, r);
    z = CMPLXF((float)NAN, 0.0f); r = ctanhf(z); print_cflt("ctanhf", z, r);
}

static void test_cexpf(void) {
    float complex z, r;
    z = CMPLXF(0.0f, 0.0f);  r = cexpf(z);   print_cflt("cexpf", z, r);
    z = CMPLXF(1.0f, 0.0f);  r = cexpf(z);   print_cflt("cexpf", z, r);
    z = CMPLXF(0.0f, 1.0f);  r = cexpf(z);   print_cflt("cexpf", z, r);
    z = CMPLXF(POS_INFF, 0.0f); r = cexpf(z); print_cflt("cexpf", z, r);
    z = CMPLXF(NEG_INFF, 0.0f); r = cexpf(z); print_cflt("cexpf", z, r);
    z = CMPLXF((float)NAN, 0.0f); r = cexpf(z); print_cflt("cexpf", z, r);
}

static void test_clogf(void) {
    float complex z, r;
    z = CMPLXF(1.0f, 0.0f);  r = clogf(z);   print_cflt("clogf", z, r);
    z = CMPLXF(0.0f, 1.0f);  r = clogf(z);   print_cflt("clogf", z, r);
    z = CMPLXF(-1.0f, 0.0f); r = clogf(z);   print_cflt("clogf", z, r);
    z = CMPLXF(0.0f, 0.0f);  r = clogf(z);   print_cflt("clogf", z, r);
    z = CMPLXF(POS_INFF, 0.0f); r = clogf(z); print_cflt("clogf", z, r);
    z = CMPLXF((float)NAN, 0.0f); r = clogf(z); print_cflt("clogf", z, r);
}

static void test_cabsf(void) {
    float complex z;
    z = CMPLXF(3.0f, 4.0f);   printf("cabsf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)cabsf(z));
    z = CMPLXF(0.0f, 0.0f);   printf("cabsf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)cabsf(z));
    z = CMPLXF(POS_INFF, 0.0f); printf("cabsf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)cabsf(z));
    z = CMPLXF((float)NAN, 0.0f); printf("cabsf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)cabsf(z));
}

static void test_cpowf(void) {
    float complex z, w, r;
    z = CMPLXF(2.0f, 0.0f); w = CMPLXF(2.0f, 0.0f); r = cpowf(z, w); print_cflt2("cpowf", z, w, r);
    z = CMPLXF(0.0f, 1.0f); w = CMPLXF(2.0f, 0.0f); r = cpowf(z, w); print_cflt2("cpowf", z, w, r);
    z = CMPLXF(0.0f, 0.0f); w = CMPLXF(1.0f, 0.0f); r = cpowf(z, w); print_cflt2("cpowf", z, w, r);
    z = CMPLXF((float)NAN, 0.0f); w = CMPLXF(1.0f, 0.0f); r = cpowf(z, w); print_cflt2("cpowf", z, w, r);
}

static void test_csqrtf(void) {
    float complex z, r;
    z = CMPLXF(0.0f, 0.0f);  r = csqrtf(z);  print_cflt("csqrtf", z, r);
    z = CMPLXF(1.0f, 0.0f);  r = csqrtf(z);  print_cflt("csqrtf", z, r);
    z = CMPLXF(-1.0f, 0.0f); r = csqrtf(z);  print_cflt("csqrtf", z, r);
    z = CMPLXF(0.0f, 1.0f);  r = csqrtf(z);  print_cflt("csqrtf", z, r);
    z = CMPLXF(3.0f, 4.0f);  r = csqrtf(z);  print_cflt("csqrtf", z, r);
    z = CMPLXF(POS_INFF, 0.0f); r = csqrtf(z); print_cflt("csqrtf", z, r);
    z = CMPLXF((float)NAN, 0.0f); r = csqrtf(z); print_cflt("csqrtf", z, r);
}

static void test_cargf(void) {
    float complex z;
    z = CMPLXF(1.0f, 0.0f);   printf("cargf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)cargf(z));
    z = CMPLXF(-1.0f, 0.0f);  printf("cargf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)cargf(z));
    z = CMPLXF(0.0f, 1.0f);   printf("cargf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)cargf(z));
    z = CMPLXF(0.0f, -1.0f);  printf("cargf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)cargf(z));
    z = CMPLXF(0.0f, 0.0f);   printf("cargf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)cargf(z));
    z = CMPLXF((float)NAN, 0.0f); printf("cargf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)cargf(z));
}

static void test_cimagf(void) {
    float complex z;
    z = CMPLXF(1.0f, 2.0f);  printf("cimagf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)cimagf(z));
    z = CMPLXF(0.0f, -0.0f); printf("cimagf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)cimagf(z));
    z = CMPLXF(POS_INFF, POS_INFF); printf("cimagf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)cimagf(z));
}

static void test_conjf(void) {
    float complex z, r;
    z = CMPLXF(1.0f, 2.0f);  r = conjf(z);  print_cflt("conjf", z, r);
    z = CMPLXF(1.0f, -2.0f); r = conjf(z);  print_cflt("conjf", z, r);
    z = CMPLXF(0.0f, 0.0f);  r = conjf(z);  print_cflt("conjf", z, r);
    z = CMPLXF(POS_INFF, POS_INFF); r = conjf(z); print_cflt("conjf", z, r);
}

static void test_cprojf(void) {
    float complex z, r;
    z = CMPLXF(1.0f, 2.0f);  r = cprojf(z); print_cflt("cprojf", z, r);
    z = CMPLXF(POS_INFF, 0.0f); r = cprojf(z); print_cflt("cprojf", z, r);
    z = CMPLXF(POS_INFF, NEG_INFF); r = cprojf(z); print_cflt("cprojf", z, r);
    z = CMPLXF((float)NAN, POS_INFF); r = cprojf(z); print_cflt("cprojf", z, r);
}

static void test_crealf(void) {
    float complex z;
    z = CMPLXF(1.0f, 2.0f);  printf("crealf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)crealf(z));
    z = CMPLXF(-0.0f, 0.0f); printf("crealf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)crealf(z));
    z = CMPLXF(POS_INFF, 0.0f); printf("crealf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)crealf(z));
}

/* ===== 32. Classification functions ===== */
static void test_fpclassify(void) {
    printf("fpclassifyd %a = %d\n", 0.0, __fpclassifyd(0.0));
    printf("fpclassifyd %a = %d\n", -0.0, __fpclassifyd(-0.0));
    printf("fpclassifyd %a = %d\n", 1.0, __fpclassifyd(1.0));
    printf("fpclassifyd %a = %d\n", POS_INF, __fpclassifyd(POS_INF));
    printf("fpclassifyd %a = %d\n", (double)NAN, __fpclassifyd((double)NAN));
    printf("fpclassifyd %a = %d\n", DBL_DENORM, __fpclassifyd(DBL_DENORM));

    printf("fpclassifyf %a = %d\n", (double)0.0f, __fpclassifyf(0.0f));
    printf("fpclassifyf %a = %d\n", (double)1.0f, __fpclassifyf(1.0f));
    printf("fpclassifyf %a = %d\n", (double)POS_INFF, __fpclassifyf(POS_INFF));
    printf("fpclassifyf %a = %d\n", (double)NAN, __fpclassifyf((float)NAN));
    printf("fpclassifyf %a = %d\n", (double)FLT_DENORM, __fpclassifyf(FLT_DENORM));
}

static void test_signbit(void) {
    printf("signbitd %a = %d\n", 1.0, __signbitd(1.0));
    printf("signbitd %a = %d\n", -1.0, __signbitd(-1.0));
    printf("signbitd %a = %d\n", 0.0, __signbitd(0.0));
    printf("signbitd %a = %d\n", -0.0, __signbitd(-0.0));
    printf("signbitd %a = %d\n", POS_INF, __signbitd(POS_INF));
    printf("signbitd %a = %d\n", NEG_INF, __signbitd(NEG_INF));
    printf("signbitd %a = %d\n", (double)NAN, __signbitd((double)NAN));

    printf("signbitf %a = %d\n", (double)1.0f, __signbitf(1.0f));
    printf("signbitf %a = %d\n", (double)-1.0f, __signbitf(-1.0f));
    printf("signbitf %a = %d\n", (double)0.0f, __signbitf(0.0f));
    printf("signbitf %a = %d\n", (double)-0.0f, __signbitf(-0.0f));
    printf("signbitf %a = %d\n", (double)POS_INFF, __signbitf(POS_INFF));
    printf("signbitf %a = %d\n", (double)NAN, __signbitf((float)NAN));
}

/* ===== 33. Bridge / static internal functions ===== */
static void test_bridge_rem_pio2_internal(void) {
    /* __rem_pio2_internal(x[], y[], e0, nx) - raw large argument reduction */
    /* x[] holds the mantissa pieces, e0 is exponent of first piece, nx is count */
    double x[3], y[2];
    int n;

    /* Reduce pi/2 itself: ipio2 table test */
    x[0] = 1.5707963267948966;
    n = bridge___rem_pio2_internal(x, y, 1, 1);
    printf("rem_pio2_internal pi/2 n=%d y0=%a y1=%a\n", n, y[0], y[1]);

    /* Reduce pi */
    x[0] = 3.141592653589793;
    n = bridge___rem_pio2_internal(x, y, 2, 1);
    printf("rem_pio2_internal pi n=%d y0=%a y1=%a\n", n, y[0], y[1]);

    /* Reduce 3*pi/2 */
    x[0] = 4.71238898038469;
    n = bridge___rem_pio2_internal(x, y, 2, 1);
    printf("rem_pio2_internal 3pi/2 n=%d y0=%a y1=%a\n", n, y[0], y[1]);
}

static void test_bridge_rem_pio2f_internal(void) {
    float x[2], y[1];
    int n;

    x[0] = 1.5707963267948966f;
    n = bridge___rem_pio2f_internal(x, y, 1, 1);
    printf("rem_pio2f_internal pi/2 n=%d y0=%a\n", n, (double)y[0]);

    x[0] = 3.141592653589793f;
    n = bridge___rem_pio2f_internal(x, y, 2, 1);
    printf("rem_pio2f_internal pi n=%d y0=%a\n", n, (double)y[0]);
}

static void test_bridge_tan(void) {
    double r;
    /* __tan(x, y, iy): x+y in [-pi/4, pi/4], iy=0 means y unused */
    r = bridge___tan(0.0, 0.0, 1);
    printf("bridge___tan 0.0 0.0 1 = %a\n", r);
    r = bridge___tan(M_PI_4, 0.0, 1);
    printf("bridge___tan pi/4 0.0 1 = %a\n", r);
    r = bridge___tan(-M_PI_4, 0.0, 1);
    printf("bridge___tan -pi/4 0.0 1 = %a\n", r);
    r = bridge___tan(0.5, 0.0, 1);
    printf("bridge___tan 0.5 0.0 1 = %a\n", r);
    r = bridge___tan(0.1, 0.0, 1);
    printf("bridge___tan 0.1 0.0 1 = %a\n", r);
    /* iy=-1 means compute -1/tan */
    r = bridge___tan(M_PI_4, 0.0, -1);
    printf("bridge___tan pi/4 0.0 -1 = %a\n", r);
}

static void test_bridge_tanf(void) {
    float r;
    r = bridge___tanf(0.0f, 0.0f, 1);
    printf("bridge___tanf 0.0 0.0 1 = %a\n", (double)r);
    r = bridge___tanf((float)M_PI_4, 0.0f, 1);
    printf("bridge___tanf pi/4 0.0 1 = %a\n", (double)r);
    r = bridge___tanf(-(float)M_PI_4, 0.0f, 1);
    printf("bridge___tanf -pi/4 0.0 1 = %a\n", (double)r);
    r = bridge___tanf(0.5f, 0.0f, 1);
    printf("bridge___tanf 0.5 0.0 1 = %a\n", (double)r);
    r = bridge___tanf((float)M_PI_4, 0.0f, -1);
    printf("bridge___tanf pi/4 0.0 -1 = %a\n", (double)r);
}

static void test_bridge_sin_pi(void) {
    double r;
    /* __sin_pi(x): sine of (x * pi) */
    r = bridge___sin_pi(0.0);
    printf("bridge___sin_pi 0.0 = %a\n", r);
    r = bridge___sin_pi(0.5);
    printf("bridge___sin_pi 0.5 = %a\n", r);
    r = bridge___sin_pi(1.0);
    printf("bridge___sin_pi 1.0 = %a\n", r);
    r = bridge___sin_pi(-0.5);
    printf("bridge___sin_pi -0.5 = %a\n", r);
    r = bridge___sin_pi(0.25);
    printf("bridge___sin_pi 0.25 = %a\n", r);
    r = bridge___sin_pi(2.0);
    printf("bridge___sin_pi 2.0 = %a\n", r);
}

static void test_bridge_sin_pif(void) {
    float r;
    /* __sin_pif(x): sine of (x * pi) for float */
    r = bridge___sin_pif(0.0f);
    printf("bridge___sin_pif 0.0 = %a\n", (double)r);
    r = bridge___sin_pif(0.5f);
    printf("bridge___sin_pif 0.5 = %a\n", (double)r);
    r = bridge___sin_pif(1.0f);
    printf("bridge___sin_pif 1.0 = %a\n", (double)r);
    r = bridge___sin_pif(-0.5f);
    printf("bridge___sin_pif -0.5 = %a\n", (double)r);
    r = bridge___sin_pif(0.25f);
    printf("bridge___sin_pif 0.25 = %a\n", (double)r);
}

static void test_bridge_ctans(void) {
    double r;
    double complex z;
    /* __ctans(z): helper used by ctan, computes sin/cos ratio */
    z = CMPLX(0.0, 0.0);
    r = bridge___ctans(z);
    printf("bridge___ctans (%a,%a) = %a\n", creal(z), cimag(z), r);
    z = CMPLX(1.0, 0.0);
    r = bridge___ctans(z);
    printf("bridge___ctans (%a,%a) = %a\n", creal(z), cimag(z), r);
    z = CMPLX(0.0, 1.0);
    r = bridge___ctans(z);
    printf("bridge___ctans (%a,%a) = %a\n", creal(z), cimag(z), r);
    z = CMPLX(1.0, 1.0);
    r = bridge___ctans(z);
    printf("bridge___ctans (%a,%a) = %a\n", creal(z), cimag(z), r);
}

static void test_bridge_ctansf(void) {
    float r;
    float complex z;
    z = CMPLXF(0.0f, 0.0f);
    r = bridge___ctansf(z);
    printf("bridge___ctansf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)r);
    z = CMPLXF(1.0f, 0.0f);
    r = bridge___ctansf(z);
    printf("bridge___ctansf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)r);
    z = CMPLXF(0.0f, 1.0f);
    r = bridge___ctansf(z);
    printf("bridge___ctansf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)r);
    z = CMPLXF(1.0f, 1.0f);
    r = bridge___ctansf(z);
    printf("bridge___ctansf (%a,%a) = %a\n", (double)crealf(z), (double)cimagf(z), (double)r);
}

/* nexttoward is only available with long double == 64-bit double */
#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS
static void test_nexttoward(void) {
    printf("nexttoward %a %La = %a\n", 0.0, (long double)1.0, nexttoward(0.0, (long double)1.0));
    printf("nexttoward %a %La = %a\n", 0.0, (long double)-1.0, nexttoward(0.0, (long double)-1.0));
    printf("nexttoward %a %La = %a\n", 1.0, (long double)2.0, nexttoward(1.0, (long double)2.0));
    printf("nexttoward %a %La = %a\n", (double)NAN, (long double)1.0, nexttoward((double)NAN, (long double)1.0));
}
static void test_nexttowardf(void) {
    printf("nexttowardf %a %La = %a\n", (double)0.0f, (long double)1.0, (double)nexttowardf(0.0f, (long double)1.0));
    printf("nexttowardf %a %La = %a\n", (double)0.0f, (long double)-1.0, (double)nexttowardf(0.0f, (long double)-1.0));
    printf("nexttowardf %a %La = %a\n", (double)NAN, (long double)1.0, (double)nexttowardf((float)NAN, (long double)1.0));
}
#endif

/* ===== main ===== */
int main(void) {
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

    /* Double power */
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

    /* Float power */
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
    test_nanf();
    test_nextafterf();

    /* Float max/min/fdim/fma */
    test_fdimf();
    test_fmaxf();
    test_fminf();
    test_fmaf();

    /* Complex double */
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
    test_cabs();
    test_cpow();
    test_csqrt();
    test_carg();
    test_cimag();
    test_conj();
    test_cproj();
    test_creal();

    /* Complex float */
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
    test_cabsf();
    test_cpowf();
    test_csqrtf();
    test_cargf();
    test_cimagf();
    test_conjf();
    test_cprojf();
    test_crealf();

    /* Classification */
    test_fpclassify();
    test_signbit();

    /* Bridge / static internal functions */
    test_bridge_rem_pio2_internal();
    test_bridge_rem_pio2f_internal();
    test_bridge_tan();
    test_bridge_tanf();
    test_bridge_sin_pi();
    test_bridge_sin_pif();
    test_bridge_ctans();
    test_bridge_ctansf();

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS
    test_nexttoward();
    test_nexttowardf();
#endif

    return 0;
}
