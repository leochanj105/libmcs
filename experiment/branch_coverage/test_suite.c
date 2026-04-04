#include <stdio.h>
#include <float.h>
#include <math.h>
#include <complex.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif
#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923132169163975144
#endif

extern int signgam;

static void print_double_result(const char *id, const char *expr, double value) {
    if (isnan(value)) {
        printf("%s: %s = nan\n", id, expr);
    } else {
        printf("%s: %s = %a\n", id, expr, value);
    }
}

static void print_float_result(const char *id, const char *expr, float value) {
    if (isnan(value)) {
        printf("%s: %s = nan\n", id, expr);
    } else {
        printf("%s: %s = %a\n", id, expr, (double)value);
    }
}

static void print_long_result(const char *id, const char *expr, long value) {
    printf("%s: %s = %ld\n", id, expr, value);
}

static void print_ll_result(const char *id, const char *expr, long long value) {
    printf("%s: %s = %lld\n", id, expr, value);
}

static void print_int_result(const char *id, const char *expr, int value) {
    printf("%s: %s = %d\n", id, expr, value);
}

static void print_double_complex_result(const char *id, const char *expr, double complex value) {
    double re = creal(value);
    double im = cimag(value);
    printf("%s: %s = ", id, expr);
    if (isnan(re)) {
        printf("nan");
    } else {
        printf("%a", re);
    }
    printf(" ");
    if (isnan(im)) {
        printf("nan");
    } else {
        printf("%a", im);
    }
    printf("\n");
}

static void print_float_complex_result(const char *id, const char *expr, float complex value) {
    float re = crealf(value);
    float im = cimagf(value);
    printf("%s: %s = ", id, expr);
    if (isnan(re)) {
        printf("nan");
    } else {
        printf("%a", (double)re);
    }
    printf(" ");
    if (isnan(im)) {
        printf("nan");
    } else {
        printf("%a", (double)im);
    }
    printf("\n");
}

static const char *fpclass_name(int cls) {
    switch (cls) {
        case FP_NAN:
            return "nan";
        case FP_INFINITE:
            return "infinite";
        case FP_ZERO:
            return "zero";
        case FP_SUBNORMAL:
            return "subnormal";
        case FP_NORMAL:
            return "normal";
        default:
            return "unknown";
    }
}

static void print_classification_result(const char *id, const char *expr, double value) {
    printf("%s: %s = %s\n", id, expr, fpclass_name(fpclassify(value)));
}

static void print_double_int_pair_result(const char *id, const char *expr, double value, int ivalue) {
    if (isnan(value)) {
        printf("%s: %s = nan %d\n", id, expr, ivalue);
    } else {
        printf("%s: %s = %a %d\n", id, expr, value, ivalue);
    }
}

static void print_float_int_pair_result(const char *id, const char *expr, float value, int ivalue) {
    if (isnan(value)) {
        printf("%s: %s = nan %d\n", id, expr, ivalue);
    } else {
        printf("%s: %s = %a %d\n", id, expr, (double)value, ivalue);
    }
}

static void print_double_pair_result(const char *id, const char *expr, double a, double b) {
    printf("%s: %s = ", id, expr);
    if (isnan(a)) {
        printf("nan");
    } else {
        printf("%a", a);
    }
    printf(" ");
    if (isnan(b)) {
        printf("nan");
    } else {
        printf("%a", b);
    }
    printf("\n");
}

static void print_float_pair_result(const char *id, const char *expr, float a, float b) {
    printf("%s: %s = ", id, expr);
    if (isnan(a)) {
        printf("nan");
    } else {
        printf("%a", (double)a);
    }
    printf(" ");
    if (isnan(b)) {
        printf("nan");
    } else {
        printf("%a", (double)b);
    }
    printf("\n");
}



static void print_lgamma_double_result(const char *id, const char *expr, double input) {
    double value;
    signgam = 0;
    value = lgamma(input);
    if (isnan(value)) {
        printf("%s: %s = nan %d\n", id, expr, signgam);
    } else {
        printf("%s: %s = %a %d\n", id, expr, value, signgam);
    }
}

static void print_lgamma_float_result(const char *id, const char *expr, float input) {
    float value;
    signgam = 0;
    value = lgammaf(input);
    if (isnan(value)) {
        printf("%s: %s = nan %d\n", id, expr, signgam);
    } else {
        printf("%s: %s = %a %d\n", id, expr, (double)value, signgam);
    }
}

#ifdef RUN_T001
static void test_T001(void) {
    print_double_result("T001.1", "sqrt(NAN)", sqrt(NAN));
}
#endif


#ifdef RUN_T002
static void test_T002(void) {
    print_double_result("T002.1", "sqrt(INFINITY)", sqrt(INFINITY));
}
#endif


#ifdef RUN_T003
static void test_T003(void) {
    print_double_result("T003.1", "sqrt(-INFINITY)", sqrt(-INFINITY));
}
#endif


#ifdef RUN_T004
static void test_T004(void) {
    print_double_result("T004.1", "sqrt(0.0)", sqrt(0.0));
    print_double_result("T004.2", "sqrt(-0.0)", sqrt(-0.0));
}
#endif


#ifdef RUN_T005
static void test_T005(void) {
    print_double_result("T005.1", "sqrt(-1.0)", sqrt(-1.0));
}
#endif


#ifdef RUN_T006
static void test_T006(void) {
    print_double_result("T006.1", "sqrt(5e-324)", sqrt(5e-324));
}
#endif


#ifdef RUN_T007
static void test_T007(void) {
    print_double_result("T007.1", "sqrt(0.25)", sqrt(0.25));
    print_double_result("T007.2", "sqrt(2.0)", sqrt(2.0));
    print_double_result("T007.3", "sqrt(4.0)", sqrt(4.0));
}
#endif


#ifdef RUN_T008
static void test_T008(void) {
    print_double_result("T008.1", "sqrt(1e300)", sqrt(1e300));
}
#endif


#ifdef RUN_T009
static void test_T009(void) {
    print_double_result("T009.1", "cbrt(NAN)", cbrt(NAN));
}
#endif


#ifdef RUN_T010
static void test_T010(void) {
    print_double_result("T010.1", "cbrt(INFINITY)", cbrt(INFINITY));
    print_double_result("T010.2", "cbrt(-INFINITY)", cbrt(-INFINITY));
}
#endif


#ifdef RUN_T011
static void test_T011(void) {
    print_double_result("T011.1", "cbrt(0.0)", cbrt(0.0));
    print_double_result("T011.2", "cbrt(-0.0)", cbrt(-0.0));
}
#endif


#ifdef RUN_T012
static void test_T012(void) {
    print_double_result("T012.1", "cbrt(5e-324)", cbrt(5e-324));
}
#endif


#ifdef RUN_T013
static void test_T013(void) {
    print_double_result("T013.1", "cbrt(-8.0)", cbrt(-8.0));
}
#endif


#ifdef RUN_T014
static void test_T014(void) {
    print_double_result("T014.1", "cbrt(8.0)", cbrt(8.0));
    print_double_result("T014.2", "cbrt(27.0)", cbrt(27.0));
}
#endif


#ifdef RUN_T015
static void test_T015(void) {
    print_double_result("T015.1", "fabs(-1.0)", fabs(-1.0));
    print_double_result("T015.2", "fabs(1.0)", fabs(1.0));
    print_double_result("T015.3", "fabs(0.0)", fabs(0.0));
    print_double_result("T015.4", "fabs(NAN)", fabs(NAN));
    print_double_result("T015.5", "fabs(INFINITY)", fabs(INFINITY));
}
#endif


#ifdef RUN_T016
static void test_T016(void) {
    print_double_result("T016.1", "copysign(1.0, -1.0)", copysign(1.0, -1.0));
}
#endif


#ifdef RUN_T017
static void test_T017(void) {
    print_double_result("T017.1", "copysign(-1.0, 1.0)", copysign(-1.0, 1.0));
}
#endif


#ifdef RUN_T018
static void test_T018(void) {
    print_double_result("T018.1", "copysign(1.0, NAN)", copysign(1.0, NAN));
}
#endif


#ifdef RUN_T019
static void test_T019(void) {
    print_double_result("T019.1", "fmax(2.0, 1.0)", fmax(2.0, 1.0));
    print_double_result("T019.2", "fmax(1.0, 2.0)", fmax(1.0, 2.0));
}
#endif


#ifdef RUN_T020
static void test_T020(void) {
    print_double_result("T020.1", "fmax(NAN, 1.0)", fmax(NAN, 1.0));
    print_double_result("T020.2", "fmax(1.0, NAN)", fmax(1.0, NAN));
}
#endif


#ifdef RUN_T021
static void test_T021(void) {
    print_double_result("T021.1", "fmax(NAN, NAN)", fmax(NAN, NAN));
}
#endif


#ifdef RUN_T022
static void test_T022(void) {
    print_double_result("T022.1", "fmax(INFINITY, 1.0)", fmax(INFINITY, 1.0));
    print_double_result("T022.2", "fmax(-INFINITY, 1.0)", fmax(-INFINITY, 1.0));
}
#endif


#ifdef RUN_T023
static void test_T023(void) {
    print_double_result("T023.1", "fmin(2.0, 1.0)", fmin(2.0, 1.0));
    print_double_result("T023.2", "fmin(NAN, 1.0)", fmin(NAN, 1.0));
    print_double_result("T023.3", "fmin(1.0, NAN)", fmin(1.0, NAN));
    print_double_result("T023.4", "fmin(INFINITY, 1.0)", fmin(INFINITY, 1.0));
}
#endif


#ifdef RUN_T024
static void test_T024(void) {
    print_double_result("T024.1", "fdim(3.0, 1.0)", fdim(3.0, 1.0));
}
#endif


#ifdef RUN_T025
static void test_T025(void) {
    print_double_result("T025.1", "fdim(1.0, 3.0)", fdim(1.0, 3.0));
    print_double_result("T025.2", "fdim(1.0, 1.0)", fdim(1.0, 1.0));
}
#endif


#ifdef RUN_T026
static void test_T026(void) {
    print_double_result("T026.1", "fdim(NAN, 1.0)", fdim(NAN, 1.0));
    print_double_result("T026.2", "fdim(1.0, NAN)", fdim(1.0, NAN));
}
#endif


#ifdef RUN_T027
static void test_T027(void) {
    print_double_result("T027.1", "fdim(INFINITY, 1.0)", fdim(INFINITY, 1.0));
    print_double_result("T027.2", "fdim(-INFINITY, 1.0)", fdim(-INFINITY, 1.0));
}
#endif


#ifdef RUN_T028
static void test_T028(void) {
    print_double_result("T028.1", "hypot(INFINITY, 1.0)", hypot(INFINITY, 1.0));
    print_double_result("T028.2", "hypot(1.0, INFINITY)", hypot(1.0, INFINITY));
}
#endif


#ifdef RUN_T029
static void test_T029(void) {
    print_double_result("T029.1", "hypot(NAN, 1.0)", hypot(NAN, 1.0));
    print_double_result("T029.2", "hypot(1.0, NAN)", hypot(1.0, NAN));
}
#endif


#ifdef RUN_T030
static void test_T030(void) {
    print_double_result("T030.1", "hypot(0.0, 0.0)", hypot(0.0, 0.0));
    print_double_result("T030.2", "hypot(3.0, 0.0)", hypot(3.0, 0.0));
}
#endif


#ifdef RUN_T031
static void test_T031(void) {
    print_double_result("T031.1", "hypot(1e200, 1e200)", hypot(1e200, 1e200));
}
#endif


#ifdef RUN_T032
static void test_T032(void) {
    print_double_result("T032.1", "hypot(1e-200, 1e-200)", hypot(1e-200, 1e-200));
}
#endif


#ifdef RUN_T033
static void test_T033(void) {
    print_double_result("T033.1", "hypot(3.0, 4.0)", hypot(3.0, 4.0));
}
#endif


#ifdef RUN_T034
static void test_T034(void) {
    print_double_result("T034.1", "fma(2.0, 3.0, 1.0)", fma(2.0, 3.0, 1.0));
}
#endif


#ifdef RUN_T035
static void test_T035(void) {
    print_double_result("T035.1", "fma(NAN, 1.0, 1.0)", fma(NAN, 1.0, 1.0));
    print_double_result("T035.2", "fma(1.0, NAN, 1.0)", fma(1.0, NAN, 1.0));
    print_double_result("T035.3", "fma(1.0, 1.0, NAN)", fma(1.0, 1.0, NAN));
}
#endif


#ifdef RUN_T036
static void test_T036(void) {
    print_double_result("T036.1", "fma(INFINITY, 1.0, 1.0)", fma(INFINITY, 1.0, 1.0));
    print_double_result("T036.2", "fma(INFINITY, 1.0, -INFINITY)", fma(INFINITY, 1.0, -INFINITY));
}
#endif


#ifdef RUN_T037
static void test_T037(void) {
    print_double_result("T037.1", "fma(1e300, 1e300, 0.0)", fma(1e300, 1e300, 0.0));
}
#endif


#ifdef RUN_T038
static void test_T038(void) {
    print_double_result("T038.1", "fma(1.0, 5e-324, 0.0)", fma(1.0, 5e-324, 0.0));
}
#endif


#ifdef RUN_T039
static void test_T039(void) {
    print_double_result("T039.1", "ceil(1.5)", ceil(1.5));
    print_double_result("T039.2", "ceil(-1.5)", ceil(-1.5));
    print_double_result("T039.3", "ceil(1.0)", ceil(1.0));
    print_double_result("T039.4", "ceil(0.0)", ceil(0.0));
    print_double_result("T039.5", "ceil(-0.0)", ceil(-0.0));
    print_double_result("T039.6", "ceil(INFINITY)", ceil(INFINITY));
    print_double_result("T039.7", "ceil(-INFINITY)", ceil(-INFINITY));
    print_double_result("T039.8", "ceil(NAN)", ceil(NAN));
    print_double_result("T039.9", "ceil(1e20)", ceil(1e20));
}
#endif


#ifdef RUN_T040
static void test_T040(void) {
    print_double_result("T040.1", "floor(1.5)", floor(1.5));
    print_double_result("T040.2", "floor(-1.5)", floor(-1.5));
    print_double_result("T040.3", "floor(1.0)", floor(1.0));
    print_double_result("T040.4", "floor(0.0)", floor(0.0));
    print_double_result("T040.5", "floor(-0.0)", floor(-0.0));
    print_double_result("T040.6", "floor(INFINITY)", floor(INFINITY));
    print_double_result("T040.7", "floor(NAN)", floor(NAN));
}
#endif


#ifdef RUN_T041
static void test_T041(void) {
    print_double_result("T041.1", "round(0.5)", round(0.5));
    print_double_result("T041.2", "round(-0.5)", round(-0.5));
    print_double_result("T041.3", "round(1.5)", round(1.5));
    print_double_result("T041.4", "round(-1.5)", round(-1.5));
    print_double_result("T041.5", "round(0.0)", round(0.0));
    print_double_result("T041.6", "round(NAN)", round(NAN));
    print_double_result("T041.7", "round(INFINITY)", round(INFINITY));
}
#endif


#ifdef RUN_T042
static void test_T042(void) {
    print_double_result("T042.1", "trunc(1.9)", trunc(1.9));
    print_double_result("T042.2", "trunc(-1.9)", trunc(-1.9));
    print_double_result("T042.3", "trunc(0.0)", trunc(0.0));
    print_double_result("T042.4", "trunc(NAN)", trunc(NAN));
    print_double_result("T042.5", "trunc(INFINITY)", trunc(INFINITY));
}
#endif


#ifdef RUN_T043
static void test_T043(void) {
    print_double_result("T043.1", "nearbyint(1.5)", nearbyint(1.5));
    print_double_result("T043.2", "nearbyint(-1.5)", nearbyint(-1.5));
    print_double_result("T043.3", "nearbyint(NAN)", nearbyint(NAN));
}
#endif


#ifdef RUN_T044
static void test_T044(void) {
    print_double_result("T044.1", "rint(1.5)", rint(1.5));
    print_double_result("T044.2", "rint(0.0)", rint(0.0));
    print_double_result("T044.3", "rint(NAN)", rint(NAN));
}
#endif


#ifdef RUN_T045
static void test_T045(void) {
    print_long_result("T045.1", "lrint(1.5)", lrint(1.5));
    print_long_result("T045.2", "lrint(-1.5)", lrint(-1.5));
    print_long_result("T045.3", "lrint(1e20)", lrint(1e20));
    print_long_result("T045.4", "lrint(NAN)", lrint(NAN));
    print_long_result("T045.5", "lrint(INFINITY)", lrint(INFINITY));
}
#endif


#ifdef RUN_T046
static void test_T046(void) {
    print_ll_result("T046.1", "llrint(1.5)", llrint(1.5));
    print_ll_result("T046.2", "llrint(-1.5)", llrint(-1.5));
    print_ll_result("T046.3", "llrint(1e20)", llrint(1e20));
    print_ll_result("T046.4", "llrint(NAN)", llrint(NAN));
}
#endif


#ifdef RUN_T047
static void test_T047(void) {
    print_long_result("T047.1", "lround(0.5)", lround(0.5));
    print_long_result("T047.2", "lround(-0.5)", lround(-0.5));
    print_long_result("T047.3", "lround(1e20)", lround(1e20));
    print_long_result("T047.4", "lround(NAN)", lround(NAN));
}
#endif


#ifdef RUN_T048
static void test_T048(void) {
    print_ll_result("T048.1", "llround(0.5)", llround(0.5));
    print_ll_result("T048.2", "llround(-0.5)", llround(-0.5));
    print_ll_result("T048.3", "llround(1e20)", llround(1e20));
}
#endif


#ifdef RUN_T049
static void test_T049(void) {
    print_double_result("T049.1", "exp(NAN)", exp(NAN));
}
#endif


#ifdef RUN_T050
static void test_T050(void) {
    print_double_result("T050.1", "exp(INFINITY)", exp(INFINITY));
}
#endif


#ifdef RUN_T051
static void test_T051(void) {
    print_double_result("T051.1", "exp(-INFINITY)", exp(-INFINITY));
}
#endif


#ifdef RUN_T052
static void test_T052(void) {
    print_double_result("T052.1", "exp(800.0)", exp(800.0));
}
#endif


#ifdef RUN_T053
static void test_T053(void) {
    print_double_result("T053.1", "exp(-800.0)", exp(-800.0));
}
#endif


#ifdef RUN_T054
static void test_T054(void) {
    print_double_result("T054.1", "exp(1e-10)", exp(1e-10));
}
#endif


#ifdef RUN_T055
static void test_T055(void) {
    print_double_result("T055.1", "exp(0.0)", exp(0.0));
    print_double_result("T055.2", "exp(1.0)", exp(1.0));
    print_double_result("T055.3", "exp(-1.0)", exp(-1.0));
    print_double_result("T055.4", "exp(0.5)", exp(0.5));
}
#endif


#ifdef RUN_T056
static void test_T056(void) {
    print_double_result("T056.1", "exp(1e-7)", exp(1e-7));
}
#endif


#ifdef RUN_T057
static void test_T057(void) {
    print_double_result("T057.1", "exp2(NAN)", exp2(NAN));
    print_double_result("T057.2", "exp2(INFINITY)", exp2(INFINITY));
    print_double_result("T057.3", "exp2(-INFINITY)", exp2(-INFINITY));
    print_double_result("T057.4", "exp2(1100.0)", exp2(1100.0));
    print_double_result("T057.5", "exp2(-1100.0)", exp2(-1100.0));
    print_double_result("T057.6", "exp2(0.0)", exp2(0.0));
    print_double_result("T057.7", "exp2(1.0)", exp2(1.0));
    print_double_result("T057.8", "exp2(-1.0)", exp2(-1.0));
}
#endif


#ifdef RUN_T058
static void test_T058(void) {
    print_double_result("T058.1", "expm1(NAN)", expm1(NAN));
}
#endif


#ifdef RUN_T059
static void test_T059(void) {
    print_double_result("T059.1", "expm1(INFINITY)", expm1(INFINITY));
}
#endif


#ifdef RUN_T060
static void test_T060(void) {
    print_double_result("T060.1", "expm1(-INFINITY)", expm1(-INFINITY));
}
#endif


#ifdef RUN_T061
static void test_T061(void) {
    print_double_result("T061.1", "expm1(1e-9)", expm1(1e-9));
}
#endif


#ifdef RUN_T062
static void test_T062(void) {
    print_double_result("T062.1", "expm1(800.0)", expm1(800.0));
}
#endif


#ifdef RUN_T063
static void test_T063(void) {
    print_double_result("T063.1", "expm1(-1.0)", expm1(-1.0));
}
#endif


#ifdef RUN_T064
static void test_T064(void) {
    print_double_result("T064.1", "expm1(1.0)", expm1(1.0));
    print_double_result("T064.2", "expm1(-0.5)", expm1(-0.5));
    print_double_result("T064.3", "expm1(0.5)", expm1(0.5));
}
#endif


#ifdef RUN_T065
static void test_T065(void) {
    print_double_result("T065.1", "log(0.0)", log(0.0));
    print_double_result("T065.2", "log(-0.0)", log(-0.0));
}
#endif


#ifdef RUN_T066
static void test_T066(void) {
    print_double_result("T066.1", "log(-1.0)", log(-1.0));
}
#endif


#ifdef RUN_T067
static void test_T067(void) {
    print_double_result("T067.1", "log(NAN)", log(NAN));
}
#endif


#ifdef RUN_T068
static void test_T068(void) {
    print_double_result("T068.1", "log(5e-324)", log(5e-324));
}
#endif


#ifdef RUN_T069
static void test_T069(void) {
    print_double_result("T069.1", "log(INFINITY)", log(INFINITY));
}
#endif


#ifdef RUN_T070
static void test_T070(void) {
    print_double_result("T070.1", "log(1.0)", log(1.0));
}
#endif


#ifdef RUN_T071
static void test_T071(void) {
    print_double_result("T071.1", "log(2.0)", log(2.0));
}
#endif


#ifdef RUN_T072
static void test_T072(void) {
    print_double_result("T072.1", "log(0.5)", log(0.5));
}
#endif


#ifdef RUN_T073
static void test_T073(void) {
    print_double_result("T073.1", "log(2.718281828)", log(2.718281828));
    print_double_result("T073.2", "log(10.0)", log(10.0));
}
#endif


#ifdef RUN_T074
static void test_T074(void) {
    print_double_result("T074.1", "log2(0.0)", log2(0.0));
    print_double_result("T074.2", "log2(-1.0)", log2(-1.0));
    print_double_result("T074.3", "log2(5e-324)", log2(5e-324));
    print_double_result("T074.4", "log2(1.0)", log2(1.0));
    print_double_result("T074.5", "log2(2.0)", log2(2.0));
    print_double_result("T074.6", "log2(INFINITY)", log2(INFINITY));
    print_double_result("T074.7", "log2(NAN)", log2(NAN));
}
#endif


#ifdef RUN_T075
static void test_T075(void) {
    print_double_result("T075.1", "log10(0.0)", log10(0.0));
    print_double_result("T075.2", "log10(-1.0)", log10(-1.0));
    print_double_result("T075.3", "log10(1.0)", log10(1.0));
    print_double_result("T075.4", "log10(10.0)", log10(10.0));
    print_double_result("T075.5", "log10(INFINITY)", log10(INFINITY));
    print_double_result("T075.6", "log10(NAN)", log10(NAN));
}
#endif


#ifdef RUN_T076
static void test_T076(void) {
    print_double_result("T076.1", "log1p(-1.0)", log1p(-1.0));
}
#endif


#ifdef RUN_T077
static void test_T077(void) {
    print_double_result("T077.1", "log1p(-2.0)", log1p(-2.0));
}
#endif


#ifdef RUN_T078
static void test_T078(void) {
    print_double_result("T078.1", "log1p(1e-10)", log1p(1e-10));
}
#endif


#ifdef RUN_T079
static void test_T079(void) {
    print_double_result("T079.1", "log1p(-INFINITY)", log1p(-INFINITY));
}
#endif


#ifdef RUN_T080
static void test_T080(void) {
    print_double_result("T080.1", "log1p(NAN)", log1p(NAN));
}
#endif


#ifdef RUN_T081
static void test_T081(void) {
    print_double_result("T081.1", "log1p(INFINITY)", log1p(INFINITY));
}
#endif


#ifdef RUN_T082
static void test_T082(void) {
    print_double_result("T082.1", "log1p(0.0)", log1p(0.0));
    print_double_result("T082.2", "log1p(1.0)", log1p(1.0));
    print_double_result("T082.3", "log1p(-0.5)", log1p(-0.5));
}
#endif


#ifdef RUN_T083
static void test_T083(void) {
    print_double_result("T083.1", "pow(2.0, 0.0)", pow(2.0, 0.0));
    print_double_result("T083.2", "pow(-3.0, 0.0)", pow(-3.0, 0.0));
    print_double_result("T083.3", "pow(INFINITY, 0.0)", pow(INFINITY, 0.0));
}
#endif


#ifdef RUN_T084
static void test_T084(void) {
    print_double_result("T084.1", "pow(NAN, 2.0)", pow(NAN, 2.0));
    print_double_result("T084.2", "pow(2.0, NAN)", pow(2.0, NAN));
}
#endif


#ifdef RUN_T085
static void test_T085(void) {
    print_double_result("T085.1", "pow(1.0, NAN)", pow(1.0, NAN));
}
#endif


#ifdef RUN_T086
static void test_T086(void) {
    print_double_result("T086.1", "pow(-2.0, 0.5)", pow(-2.0, 0.5));
}
#endif


#ifdef RUN_T087
static void test_T087(void) {
    print_double_result("T087.1", "pow(-2.0, 3.0)", pow(-2.0, 3.0));
}
#endif


#ifdef RUN_T088
static void test_T088(void) {
    print_double_result("T088.1", "pow(-2.0, 4.0)", pow(-2.0, 4.0));
}
#endif


#ifdef RUN_T089
static void test_T089(void) {
    print_double_result("T089.1", "pow(0.0, 2.0)", pow(0.0, 2.0));
}
#endif


#ifdef RUN_T090
static void test_T090(void) {
    print_double_result("T090.1", "pow(0.0, -1.0)", pow(0.0, -1.0));
}
#endif


#ifdef RUN_T091
static void test_T091(void) {
    print_double_result("T091.1", "pow(-0.0, -1.0)", pow(-0.0, -1.0));
}
#endif


#ifdef RUN_T092
static void test_T092(void) {
    print_double_result("T092.1", "pow(-0.0, 3.0)", pow(-0.0, 3.0));
}
#endif


#ifdef RUN_T093
static void test_T093(void) {
    print_double_result("T093.1", "pow(INFINITY, 2.0)", pow(INFINITY, 2.0));
}
#endif


#ifdef RUN_T094
static void test_T094(void) {
    print_double_result("T094.1", "pow(INFINITY, -2.0)", pow(INFINITY, -2.0));
}
#endif


#ifdef RUN_T095
static void test_T095(void) {
    print_double_result("T095.1", "pow(-INFINITY, 3.0)", pow(-INFINITY, 3.0));
}
#endif


#ifdef RUN_T096
static void test_T096(void) {
    print_double_result("T096.1", "pow(-INFINITY, 4.0)", pow(-INFINITY, 4.0));
}
#endif


#ifdef RUN_T097
static void test_T097(void) {
    print_double_result("T097.1", "pow(-INFINITY, -3.0)", pow(-INFINITY, -3.0));
}
#endif


#ifdef RUN_T098
static void test_T098(void) {
    print_double_result("T098.1", "pow(2.0, INFINITY)", pow(2.0, INFINITY));
}
#endif


#ifdef RUN_T099
static void test_T099(void) {
    print_double_result("T099.1", "pow(2.0, -INFINITY)", pow(2.0, -INFINITY));
}
#endif


#ifdef RUN_T100
static void test_T100(void) {
    print_double_result("T100.1", "pow(0.5, INFINITY)", pow(0.5, INFINITY));
}
#endif


#ifdef RUN_T101
static void test_T101(void) {
    print_double_result("T101.1", "pow(-INFINITY, INFINITY)", pow(-INFINITY, INFINITY));
}
#endif


#ifdef RUN_T102
static void test_T102(void) {
    print_double_result("T102.1", "pow(10.0, 400.0)", pow(10.0, 400.0));
}
#endif


#ifdef RUN_T103
static void test_T103(void) {
    print_double_result("T103.1", "pow(10.0, -400.0)", pow(10.0, -400.0));
}
#endif


#ifdef RUN_T104
static void test_T104(void) {
    print_double_result("T104.1", "pow(5e-324, 0.5)", pow(5e-324, 0.5));
}
#endif


#ifdef RUN_T105
static void test_T105(void) {
    print_double_result("T105.1", "pow(3.0, 1.0)", pow(3.0, 1.0));
}
#endif


#ifdef RUN_T106
static void test_T106(void) {
    print_double_result("T106.1", "pow(3.0, -1.0)", pow(3.0, -1.0));
}
#endif


#ifdef RUN_T107
static void test_T107(void) {
    print_double_result("T107.1", "pow(3.0, 2.0)", pow(3.0, 2.0));
}
#endif


#ifdef RUN_T108
static void test_T108(void) {
    print_double_result("T108.1", "pow(4.0, 0.5)", pow(4.0, 0.5));
}
#endif


#ifdef RUN_T109
static void test_T109(void) {
    print_double_result("T109.1", "pow(1.5, 1.7)", pow(1.5, 1.7));
}
#endif


#ifdef RUN_T110
static void test_T110(void) {
    print_double_result("T110.1", "pow(1.2, 3.0)", pow(1.2, 3.0));
}
#endif


#ifdef RUN_T111
static void test_T111(void) {
    print_double_result("T111.1", "pow(1.0 + 1e-15, 1e10)", pow(1.0 + 1e-15, 1e10));
}
#endif


#ifdef RUN_T112
static void test_T112(void) {
    print_double_result("T112.1", "pow(1.00001, 1e12)", pow(1.00001, 1e12));
}
#endif


#ifdef RUN_T113
static void test_T113(void) {
    print_double_result("T113.1", "sin(0.0)", sin(0.0));
}
#endif


#ifdef RUN_T114
static void test_T114(void) {
    print_double_result("T114.1", "sin(1e-8)", sin(1e-8));
}
#endif


#ifdef RUN_T115
static void test_T115(void) {
    print_double_result("T115.1", "sin(0.5)", sin(0.5));
}
#endif


#ifdef RUN_T116
static void test_T116(void) {
    print_double_result("T116.1", "sin(INFINITY)", sin(INFINITY));
    print_double_result("T116.2", "sin(-INFINITY)", sin(-INFINITY));
}
#endif


#ifdef RUN_T117
static void test_T117(void) {
    print_double_result("T117.1", "sin(NAN)", sin(NAN));
}
#endif


#ifdef RUN_T118
static void test_T118(void) {
    print_double_result("T118.1", "sin(7.0)", sin(7.0));
}
#endif


#ifdef RUN_T119
static void test_T119(void) {
    print_double_result("T119.1", "sin(7.0 + M_PI/2)", sin(7.0 + M_PI/2));
}
#endif


#ifdef RUN_T120
static void test_T120(void) {
    print_double_result("T120.1", "sin(M_PI + 0.5)", sin(M_PI + 0.5));
}
#endif


#ifdef RUN_T121
static void test_T121(void) {
    print_double_result("T121.1", "sin(3*M_PI/2 + 0.5)", sin(3*M_PI/2 + 0.5));
}
#endif


#ifdef RUN_T122
static void test_T122(void) {
    print_double_result("T122.1", "sin(1e20)", sin(1e20));
}
#endif


#ifdef RUN_T123
static void test_T123(void) {
    print_double_result("T123.1", "cos(0.0)", cos(0.0));
}
#endif


#ifdef RUN_T124
static void test_T124(void) {
    print_double_result("T124.1", "cos(0.5)", cos(0.5));
}
#endif


#ifdef RUN_T125
static void test_T125(void) {
    print_double_result("T125.1", "cos(INFINITY)", cos(INFINITY));
    print_double_result("T125.2", "cos(-INFINITY)", cos(-INFINITY));
}
#endif


#ifdef RUN_T126
static void test_T126(void) {
    print_double_result("T126.1", "cos(NAN)", cos(NAN));
}
#endif


#ifdef RUN_T127
static void test_T127(void) {
    print_double_result("T127.1", "cos(7.0)", cos(7.0));
    print_double_result("T127.2", "cos(M_PI + 0.5)", cos(M_PI + 0.5));
    print_double_result("T127.3", "cos(3*M_PI/2 + 0.5)", cos(3*M_PI/2 + 0.5));
}
#endif


#ifdef RUN_T128
static void test_T128(void) {
    print_double_result("T128.1", "tan(0.0)", tan(0.0));
    print_double_result("T128.2", "tan(-0.0)", tan(-0.0));
}
#endif


#ifdef RUN_T129
static void test_T129(void) {
    print_double_result("T129.1", "tan(1e-8)", tan(1e-8));
}
#endif


#ifdef RUN_T130
static void test_T130(void) {
    print_double_result("T130.1", "tan(0.5)", tan(0.5));
}
#endif


#ifdef RUN_T131
static void test_T131(void) {
    print_double_result("T131.1", "tan(INFINITY)", tan(INFINITY));
    print_double_result("T131.2", "tan(-INFINITY)", tan(-INFINITY));
}
#endif


#ifdef RUN_T132
static void test_T132(void) {
    print_double_result("T132.1", "tan(NAN)", tan(NAN));
}
#endif


#ifdef RUN_T133
static void test_T133(void) {
    print_double_result("T133.1", "tan(M_PI_2 - 1e-10)", tan(M_PI_2 - 1e-10));
}
#endif


#ifdef RUN_T134
static void test_T134(void) {
    print_double_result("T134.1", "tan(7.0)", tan(7.0));
    print_double_result("T134.2", "tan(1e10)", tan(1e10));
}
#endif


#ifdef RUN_T135
static void test_T135(void) {
    print_double_result("T135.1", "asin(2.0)", asin(2.0));
    print_double_result("T135.2", "asin(-2.0)", asin(-2.0));
}
#endif


#ifdef RUN_T136
static void test_T136(void) {
    print_double_result("T136.1", "asin(1.0)", asin(1.0));
    print_double_result("T136.2", "asin(-1.0)", asin(-1.0));
}
#endif


#ifdef RUN_T137
static void test_T137(void) {
    print_double_result("T137.1", "asin(1e-9)", asin(1e-9));
}
#endif


#ifdef RUN_T138
static void test_T138(void) {
    print_double_result("T138.1", "asin(NAN)", asin(NAN));
}
#endif


#ifdef RUN_T139
static void test_T139(void) {
    print_double_result("T139.1", "asin(0.0)", asin(0.0));
    print_double_result("T139.2", "asin(0.5)", asin(0.5));
    print_double_result("T139.3", "asin(-0.5)", asin(-0.5));
}
#endif


#ifdef RUN_T140
static void test_T140(void) {
    print_double_result("T140.1", "asin(0.9999)", asin(0.9999));
}
#endif


#ifdef RUN_T141
static void test_T141(void) {
    print_double_result("T141.1", "acos(2.0)", acos(2.0));
    print_double_result("T141.2", "acos(-2.0)", acos(-2.0));
}
#endif


#ifdef RUN_T142
static void test_T142(void) {
    print_double_result("T142.1", "acos(1.0)", acos(1.0));
}
#endif


#ifdef RUN_T143
static void test_T143(void) {
    print_double_result("T143.1", "acos(-1.0)", acos(-1.0));
}
#endif


#ifdef RUN_T144
static void test_T144(void) {
    print_double_result("T144.1", "acos(NAN)", acos(NAN));
}
#endif


#ifdef RUN_T145
static void test_T145(void) {
    print_double_result("T145.1", "acos(0.0)", acos(0.0));
    print_double_result("T145.2", "acos(0.3)", acos(0.3));
}
#endif


#ifdef RUN_T146
static void test_T146(void) {
    print_double_result("T146.1", "acos(0.8)", acos(0.8));
}
#endif


#ifdef RUN_T147
static void test_T147(void) {
    print_double_result("T147.1", "atan(NAN)", atan(NAN));
}
#endif


#ifdef RUN_T148
static void test_T148(void) {
    print_double_result("T148.1", "atan(INFINITY)", atan(INFINITY));
    print_double_result("T148.2", "atan(-INFINITY)", atan(-INFINITY));
}
#endif


#ifdef RUN_T149
static void test_T149(void) {
    print_double_result("T149.1", "atan(1e20)", atan(1e20));
}
#endif


#ifdef RUN_T150
static void test_T150(void) {
    print_double_result("T150.1", "atan(1e-10)", atan(1e-10));
}
#endif


#ifdef RUN_T151
static void test_T151(void) {
    print_double_result("T151.1", "atan(0.5)", atan(0.5));
    print_double_result("T151.2", "atan(1.0)", atan(1.0));
    print_double_result("T151.3", "atan(2.0)", atan(2.0));
    print_double_result("T151.4", "atan(-1.0)", atan(-1.0));
}
#endif


#ifdef RUN_T152
static void test_T152(void) {
    print_double_result("T152.1", "atan2(NAN, 1.0)", atan2(NAN, 1.0));
    print_double_result("T152.2", "atan2(1.0, NAN)", atan2(1.0, NAN));
}
#endif


#ifdef RUN_T153
static void test_T153(void) {
    print_double_result("T153.1", "atan2(0.0, 1.0)", atan2(0.0, 1.0));
}
#endif


#ifdef RUN_T154
static void test_T154(void) {
    print_double_result("T154.1", "atan2(-0.0, 1.0)", atan2(-0.0, 1.0));
}
#endif


#ifdef RUN_T155
static void test_T155(void) {
    print_double_result("T155.1", "atan2(0.0, -1.0)", atan2(0.0, -1.0));
}
#endif


#ifdef RUN_T156
static void test_T156(void) {
    print_double_result("T156.1", "atan2(-0.0, -1.0)", atan2(-0.0, -1.0));
}
#endif


#ifdef RUN_T157
static void test_T157(void) {
    print_double_result("T157.1", "atan2(1.0, 0.0)", atan2(1.0, 0.0));
}
#endif


#ifdef RUN_T158
static void test_T158(void) {
    print_double_result("T158.1", "atan2(-1.0, 0.0)", atan2(-1.0, 0.0));
}
#endif


#ifdef RUN_T159
static void test_T159(void) {
    print_double_result("T159.1", "atan2(0.0, 0.0)", atan2(0.0, 0.0));
    print_double_result("T159.2", "atan2(-0.0, 0.0)", atan2(-0.0, 0.0));
}
#endif


#ifdef RUN_T160
static void test_T160(void) {
    print_double_result("T160.1", "atan2(1.0, 1.0)", atan2(1.0, 1.0));
}
#endif


#ifdef RUN_T161
static void test_T161(void) {
    print_double_result("T161.1", "atan2(1.0, -1.0)", atan2(1.0, -1.0));
}
#endif


#ifdef RUN_T162
static void test_T162(void) {
    print_double_result("T162.1", "atan2(-1.0, -1.0)", atan2(-1.0, -1.0));
}
#endif


#ifdef RUN_T163
static void test_T163(void) {
    print_double_result("T163.1", "atan2(1.0, INFINITY)", atan2(1.0, INFINITY));
    print_double_result("T163.2", "atan2(-1.0, INFINITY)", atan2(-1.0, INFINITY));
}
#endif


#ifdef RUN_T164
static void test_T164(void) {
    print_double_result("T164.1", "atan2(1.0, -INFINITY)", atan2(1.0, -INFINITY));
    print_double_result("T164.2", "atan2(-1.0, -INFINITY)", atan2(-1.0, -INFINITY));
}
#endif


#ifdef RUN_T165
static void test_T165(void) {
    print_double_result("T165.1", "atan2(INFINITY, 1.0)", atan2(INFINITY, 1.0));
    print_double_result("T165.2", "atan2(INFINITY, -1.0)", atan2(INFINITY, -1.0));
}
#endif


#ifdef RUN_T166
static void test_T166(void) {
    print_double_result("T166.1", "atan2(INFINITY, INFINITY)", atan2(INFINITY, INFINITY));
    print_double_result("T166.2", "atan2(INFINITY, -INFINITY)", atan2(INFINITY, -INFINITY));
    print_double_result("T166.3", "atan2(-INFINITY, INFINITY)", atan2(-INFINITY, INFINITY));
    print_double_result("T166.4", "atan2(-INFINITY, -INFINITY)", atan2(-INFINITY, -INFINITY));
}
#endif


#ifdef RUN_T167
static void test_T167(void) {
    print_double_result("T167.1", "sinh(NAN)", sinh(NAN));
}
#endif


#ifdef RUN_T168
static void test_T168(void) {
    print_double_result("T168.1", "sinh(INFINITY)", sinh(INFINITY));
    print_double_result("T168.2", "sinh(-INFINITY)", sinh(-INFINITY));
}
#endif


#ifdef RUN_T169
static void test_T169(void) {
    print_double_result("T169.1", "sinh(1e-9)", sinh(1e-9));
}
#endif


#ifdef RUN_T170
static void test_T170(void) {
    print_double_result("T170.1", "sinh(800.0)", sinh(800.0));
}
#endif


#ifdef RUN_T171
static void test_T171(void) {
    print_double_result("T171.1", "sinh(1.0)", sinh(1.0));
    print_double_result("T171.2", "sinh(-1.0)", sinh(-1.0));
}
#endif


#ifdef RUN_T172
static void test_T172(void) {
    print_double_result("T172.1", "cosh(NAN)", cosh(NAN));
    print_double_result("T172.2", "cosh(INFINITY)", cosh(INFINITY));
    print_double_result("T172.3", "cosh(1e-9)", cosh(1e-9));
    print_double_result("T172.4", "cosh(800.0)", cosh(800.0));
    print_double_result("T172.5", "cosh(1.0)", cosh(1.0));
}
#endif


#ifdef RUN_T173
static void test_T173(void) {
    print_double_result("T173.1", "tanh(NAN)", tanh(NAN));
    print_double_result("T173.2", "tanh(INFINITY)", tanh(INFINITY));
    print_double_result("T173.3", "tanh(-INFINITY)", tanh(-INFINITY));
    print_double_result("T173.4", "tanh(1e-9)", tanh(1e-9));
    print_double_result("T173.5", "tanh(100.0)", tanh(100.0));
    print_double_result("T173.6", "tanh(0.5)", tanh(0.5));
}
#endif


#ifdef RUN_T174
static void test_T174(void) {
    print_double_result("T174.1", "asinh(NAN)", asinh(NAN));
    print_double_result("T174.2", "asinh(INFINITY)", asinh(INFINITY));
    print_double_result("T174.3", "asinh(1e-9)", asinh(1e-9));
    print_double_result("T174.4", "asinh(1e200)", asinh(1e200));
    print_double_result("T174.5", "asinh(1.0)", asinh(1.0));
}
#endif


#ifdef RUN_T175
static void test_T175(void) {
    print_double_result("T175.1", "acosh(0.5)", acosh(0.5));
    print_double_result("T175.2", "acosh(-1.0)", acosh(-1.0));
}
#endif


#ifdef RUN_T176
static void test_T176(void) {
    print_double_result("T176.1", "acosh(1.0)", acosh(1.0));
}
#endif


#ifdef RUN_T177
static void test_T177(void) {
    print_double_result("T177.1", "acosh(NAN)", acosh(NAN));
    print_double_result("T177.2", "acosh(INFINITY)", acosh(INFINITY));
    print_double_result("T177.3", "acosh(1e200)", acosh(1e200));
    print_double_result("T177.4", "acosh(2.0)", acosh(2.0));
}
#endif


#ifdef RUN_T178
static void test_T178(void) {
    print_double_result("T178.1", "atanh(2.0)", atanh(2.0));
    print_double_result("T178.2", "atanh(-2.0)", atanh(-2.0));
}
#endif


#ifdef RUN_T179
static void test_T179(void) {
    print_double_result("T179.1", "atanh(1.0)", atanh(1.0));
    print_double_result("T179.2", "atanh(-1.0)", atanh(-1.0));
}
#endif


#ifdef RUN_T180
static void test_T180(void) {
    print_double_result("T180.1", "atanh(1e-9)", atanh(1e-9));
}
#endif


#ifdef RUN_T181
static void test_T181(void) {
    print_double_result("T181.1", "atanh(NAN)", atanh(NAN));
    print_double_result("T181.2", "atanh(0.5)", atanh(0.5));
    print_double_result("T181.3", "atanh(-0.5)", atanh(-0.5));
}
#endif


#ifdef RUN_T182
static void test_T182(void) {
    print_double_result("T182.1", "erf(NAN)", erf(NAN));
}
#endif


#ifdef RUN_T183
static void test_T183(void) {
    print_double_result("T183.1", "erf(INFINITY)", erf(INFINITY));
    print_double_result("T183.2", "erf(-INFINITY)", erf(-INFINITY));
}
#endif


#ifdef RUN_T184
static void test_T184(void) {
    print_double_result("T184.1", "erf(1e-10)", erf(1e-10));
}
#endif


#ifdef RUN_T185
static void test_T185(void) {
    print_double_result("T185.1", "erf(0.3)", erf(0.3));
}
#endif


#ifdef RUN_T186
static void test_T186(void) {
    print_double_result("T186.1", "erf(1.0)", erf(1.0));
    print_double_result("T186.2", "erf(2.0)", erf(2.0));
    print_double_result("T186.3", "erf(-1.0)", erf(-1.0));
}
#endif


#ifdef RUN_T187
static void test_T187(void) {
    print_double_result("T187.1", "erf(5.0)", erf(5.0));
    print_double_result("T187.2", "erf(-5.0)", erf(-5.0));
}
#endif


#ifdef RUN_T188
static void test_T188(void) {
    print_double_result("T188.1", "erfc(NAN)", erfc(NAN));
    print_double_result("T188.2", "erfc(INFINITY)", erfc(INFINITY));
    print_double_result("T188.3", "erfc(-INFINITY)", erfc(-INFINITY));
    print_double_result("T188.4", "erfc(1e-10)", erfc(1e-10));
    print_double_result("T188.5", "erfc(1.0)", erfc(1.0));
    print_double_result("T188.6", "erfc(10.0)", erfc(10.0));
    print_double_result("T188.7", "erfc(-1.0)", erfc(-1.0));
}
#endif


#ifdef RUN_T189
static void test_T189(void) {
    print_double_result("T189.1", "tgamma(NAN)", tgamma(NAN));
}
#endif


#ifdef RUN_T190
static void test_T190(void) {
    print_double_result("T190.1", "tgamma(0.0)", tgamma(0.0));
    print_double_result("T190.2", "tgamma(-0.0)", tgamma(-0.0));
}
#endif


#ifdef RUN_T191
static void test_T191(void) {
    print_double_result("T191.1", "tgamma(-1.0)", tgamma(-1.0));
    print_double_result("T191.2", "tgamma(-2.0)", tgamma(-2.0));
    print_double_result("T191.3", "tgamma(-10.0)", tgamma(-10.0));
}
#endif


#ifdef RUN_T192
static void test_T192(void) {
    print_double_result("T192.1", "tgamma(-INFINITY)", tgamma(-INFINITY));
}
#endif


#ifdef RUN_T193
static void test_T193(void) {
    print_double_result("T193.1", "tgamma(INFINITY)", tgamma(INFINITY));
}
#endif


#ifdef RUN_T194
static void test_T194(void) {
    print_double_result("T194.1", "tgamma(200.0)", tgamma(200.0));
}
#endif


#ifdef RUN_T195
static void test_T195(void) {
    print_double_result("T195.1", "tgamma(0.5)", tgamma(0.5));
    print_double_result("T195.2", "tgamma(0.9)", tgamma(0.9));
}
#endif


#ifdef RUN_T196
static void test_T196(void) {
    print_double_result("T196.1", "tgamma(1.0)", tgamma(1.0));
    print_double_result("T196.2", "tgamma(1.5)", tgamma(1.5));
    print_double_result("T196.3", "tgamma(2.0)", tgamma(2.0));
}
#endif


#ifdef RUN_T197
static void test_T197(void) {
    print_double_result("T197.1", "tgamma(-0.5)", tgamma(-0.5));
    print_double_result("T197.2", "tgamma(-1.5)", tgamma(-1.5));
}
#endif


#ifdef RUN_T198
static void test_T198(void) {
    double value;
    signgam = 0;
    value = lgamma(0.0);
    print_double_result("T198.1", "lgamma(0.0)", value);
    print_int_result("T198.1.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(-0.0);
    print_double_result("T198.2", "lgamma(-0.0)", value);
    print_int_result("T198.2.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(-1.0);
    print_double_result("T198.3", "lgamma(-1.0)", value);
    print_int_result("T198.3.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(0.5);
    print_double_result("T198.4", "lgamma(0.5)", value);
    print_int_result("T198.4.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(1.0);
    print_double_result("T198.5", "lgamma(1.0)", value);
    print_int_result("T198.5.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(2.0);
    print_double_result("T198.6", "lgamma(2.0)", value);
    print_int_result("T198.6.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(10.0);
    print_double_result("T198.7", "lgamma(10.0)", value);
    print_int_result("T198.7.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(NAN);
    print_double_result("T198.8", "lgamma(NAN)", value);
    print_int_result("T198.8.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(INFINITY);
    print_double_result("T198.9", "lgamma(INFINITY)", value);
    print_int_result("T198.9.signgam", "signgam", signgam);
}
#endif


#ifdef RUN_T199
static void test_T199(void) {
    print_double_result("T199.1", "j0(NAN)", j0(NAN));
    print_double_result("T199.2", "j0(INFINITY)", j0(INFINITY));
    print_double_result("T199.3", "j0(-INFINITY)", j0(-INFINITY));
    print_double_result("T199.4", "j0(0.0)", j0(0.0));
    print_double_result("T199.5", "j0(0.1)", j0(0.1));
    print_double_result("T199.6", "j0(1.0)", j0(1.0));
    print_double_result("T199.7", "j0(10.0)", j0(10.0));
}
#endif


#ifdef RUN_T200
static void test_T200(void) {
    print_double_result("T200.1", "j1(NAN)", j1(NAN));
    print_double_result("T200.2", "j1(INFINITY)", j1(INFINITY));
    print_double_result("T200.3", "j1(0.0)", j1(0.0));
    print_double_result("T200.4", "j1(1.0)", j1(1.0));
    print_double_result("T200.5", "j1(10.0)", j1(10.0));
}
#endif


#ifdef RUN_T201
static void test_T201(void) {
    print_double_result("T201.1", "jn(0, 1.0)", jn(0, 1.0));
}
#endif


#ifdef RUN_T202
static void test_T202(void) {
    print_double_result("T202.1", "jn(1, 1.0)", jn(1, 1.0));
}
#endif


#ifdef RUN_T203
static void test_T203(void) {
    print_double_result("T203.1", "jn(-2, 1.0)", jn(-2, 1.0));
    print_double_result("T203.2", "jn(-3, 1.0)", jn(-3, 1.0));
}
#endif


#ifdef RUN_T204
static void test_T204(void) {
    print_double_result("T204.1", "jn(2, NAN)", jn(2, NAN));
    print_double_result("T204.2", "jn(2, 0.0)", jn(2, 0.0));
    print_double_result("T204.3", "jn(2, INFINITY)", jn(2, INFINITY));
    print_double_result("T204.4", "jn(2, -INFINITY)", jn(2, -INFINITY));
}
#endif


#ifdef RUN_T205
static void test_T205(void) {
    print_double_result("T205.1", "jn(3, 10.0)", jn(3, 10.0));
}
#endif


#ifdef RUN_T206
static void test_T206(void) {
    print_double_result("T206.1", "jn(10, 1.0)", jn(10, 1.0));
}
#endif


#ifdef RUN_T207
static void test_T207(void) {
    print_double_result("T207.1", "y0(0.0)", y0(0.0));
    print_double_result("T207.2", "y0(-1.0)", y0(-1.0));
}
#endif


#ifdef RUN_T208
static void test_T208(void) {
    print_double_result("T208.1", "y0(NAN)", y0(NAN));
    print_double_result("T208.2", "y0(INFINITY)", y0(INFINITY));
    print_double_result("T208.3", "y0(0.1)", y0(0.1));
    print_double_result("T208.4", "y0(1.0)", y0(1.0));
    print_double_result("T208.5", "y0(10.0)", y0(10.0));
}
#endif


#ifdef RUN_T209
static void test_T209(void) {
    print_double_result("T209.1", "y1(0.0)", y1(0.0));
    print_double_result("T209.2", "y1(-1.0)", y1(-1.0));
    print_double_result("T209.3", "y1(NAN)", y1(NAN));
    print_double_result("T209.4", "y1(INFINITY)", y1(INFINITY));
    print_double_result("T209.5", "y1(1.0)", y1(1.0));
    print_double_result("T209.6", "y1(10.0)", y1(10.0));
}
#endif


#ifdef RUN_T210
static void test_T210(void) {
    print_double_result("T210.1", "yn(0, 1.0)", yn(0, 1.0));
    print_double_result("T210.2", "yn(1, 1.0)", yn(1, 1.0));
    print_double_result("T210.3", "yn(-1, 1.0)", yn(-1, 1.0));
    print_double_result("T210.4", "yn(2, NAN)", yn(2, NAN));
    print_double_result("T210.5", "yn(2, 0.0)", yn(2, 0.0));
    print_double_result("T210.6", "yn(2, INFINITY)", yn(2, INFINITY));
    print_double_result("T210.7", "yn(2, 1.0)", yn(2, 1.0));
    print_double_result("T210.8", "yn(2, -1.0)", yn(2, -1.0));
}
#endif


#ifdef RUN_T211
static void test_T211(void) {
    print_double_result("T211.1", "fmod(1.0, 0.0)", fmod(1.0, 0.0));
}
#endif


#ifdef RUN_T212
static void test_T212(void) {
    print_double_result("T212.1", "fmod(INFINITY, 1.0)", fmod(INFINITY, 1.0));
    print_double_result("T212.2", "fmod(-INFINITY, 1.0)", fmod(-INFINITY, 1.0));
}
#endif


#ifdef RUN_T213
static void test_T213(void) {
    print_double_result("T213.1", "fmod(NAN, 1.0)", fmod(NAN, 1.0));
    print_double_result("T213.2", "fmod(1.0, NAN)", fmod(1.0, NAN));
}
#endif


#ifdef RUN_T214
static void test_T214(void) {
    print_double_result("T214.1", "fmod(0.5, 1.0)", fmod(0.5, 1.0));
}
#endif


#ifdef RUN_T215
static void test_T215(void) {
    print_double_result("T215.1", "fmod(1.0, 1.0)", fmod(1.0, 1.0));
    print_double_result("T215.2", "fmod(-1.0, 1.0)", fmod(-1.0, 1.0));
}
#endif


#ifdef RUN_T216
static void test_T216(void) {
    print_double_result("T216.1", "fmod(5e-324, 1.0)", fmod(5e-324, 1.0));
}
#endif


#ifdef RUN_T217
static void test_T217(void) {
    print_double_result("T217.1", "fmod(1.0, 5e-324)", fmod(1.0, 5e-324));
}
#endif


#ifdef RUN_T218
static void test_T218(void) {
    print_double_result("T218.1", "fmod(5.0, 3.0)", fmod(5.0, 3.0));
    print_double_result("T218.2", "fmod(10.0, 3.0)", fmod(10.0, 3.0));
}
#endif


#ifdef RUN_T219
static void test_T219(void) {
    print_double_result("T219.1", "remainder(0.5, 1.0)", remainder(0.5, 1.0));
    print_double_result("T219.2", "remainder(1.0, 0.0)", remainder(1.0, 0.0));
    print_double_result("T219.3", "remainder(NAN, 1.0)", remainder(NAN, 1.0));
    print_double_result("T219.4", "remainder(INFINITY, 1.0)", remainder(INFINITY, 1.0));
    print_double_result("T219.5", "remainder(5.0, 3.0)", remainder(5.0, 3.0));
}
#endif


#ifdef RUN_T220
static void test_T220(void) {
    int q;
    double value;
    q = 0;
    value = remquo(5.0, 3.0, &q);
    print_double_result("T220.1", "remquo(5.0, 3.0, &q)", value);
    print_int_result("T220.1.q", "q", q);
    q = 0;
    value = remquo(0.0, 1.0, &q);
    print_double_result("T220.2", "remquo(0.0, 1.0, &q)", value);
    print_int_result("T220.2.q", "q", q);
    q = 0;
    value = remquo(NAN, 1.0, &q);
    print_double_result("T220.3", "remquo(NAN, 1.0, &q)", value);
    print_int_result("T220.3.q", "q", q);
}
#endif


#ifdef RUN_T221
static void test_T221(void) {
    int e;
    double value;
    e = 0;
    value = frexp(0.0, &e);
    print_double_result("T221.1", "frexp(0.0, &e)", value);
    print_int_result("T221.1.e", "e", e);
    e = 0;
    value = frexp(NAN, &e);
    print_double_result("T221.2", "frexp(NAN, &e)", value);
    print_int_result("T221.2.e", "e", e);
    e = 0;
    value = frexp(INFINITY, &e);
    print_double_result("T221.3", "frexp(INFINITY, &e)", value);
    print_int_result("T221.3.e", "e", e);
    e = 0;
    value = frexp(1.0, &e);
    print_double_result("T221.4", "frexp(1.0, &e)", value);
    print_int_result("T221.4.e", "e", e);
    e = 0;
    value = frexp(5e-324, &e);
    print_double_result("T221.5", "frexp(5e-324, &e)", value);
    print_int_result("T221.5.e", "e", e);
}
#endif


#ifdef RUN_T222
static void test_T222(void) {
    print_double_result("T222.1", "ldexp(1.0, 10)", ldexp(1.0, 10));
    print_double_result("T222.2", "ldexp(1.0, 2000)", ldexp(1.0, 2000));
    print_double_result("T222.3", "ldexp(1.0, -2000)", ldexp(1.0, -2000));
    print_double_result("T222.4", "ldexp(0.0, 10)", ldexp(0.0, 10));
    print_double_result("T222.5", "ldexp(NAN, 5)", ldexp(NAN, 5));
    print_double_result("T222.6", "ldexp(INFINITY, 5)", ldexp(INFINITY, 5));
}
#endif


#ifdef RUN_T223
static void test_T223(void) {
    double ip;
    double value;
    ip = 0.0;
    value = modf(0.0, &ip);
    print_double_result("T223.1", "modf(0.0, &ip)", value);
    print_double_result("T223.1.ip", "ip", ip);
    ip = 0.0;
    value = modf(NAN, &ip);
    print_double_result("T223.2", "modf(NAN, &ip)", value);
    print_double_result("T223.2.ip", "ip", ip);
    ip = 0.0;
    value = modf(INFINITY, &ip);
    print_double_result("T223.3", "modf(INFINITY, &ip)", value);
    print_double_result("T223.3.ip", "ip", ip);
    ip = 0.0;
    value = modf(2.5, &ip);
    print_double_result("T223.4", "modf(2.5, &ip)", value);
    print_double_result("T223.4.ip", "ip", ip);
    ip = 0.0;
    value = modf(-2.5, &ip);
    print_double_result("T223.5", "modf(-2.5, &ip)", value);
    print_double_result("T223.5.ip", "ip", ip);
}
#endif


#ifdef RUN_T224
static void test_T224(void) {
    print_double_result("T224.1", "logb(NAN)", logb(NAN));
    print_double_result("T224.2", "logb(INFINITY)", logb(INFINITY));
    print_double_result("T224.3", "logb(0.0)", logb(0.0));
    print_double_result("T224.4", "logb(5e-324)", logb(5e-324));
    print_double_result("T224.5", "logb(1.0)", logb(1.0));
    print_double_result("T224.6", "logb(2.0)", logb(2.0));
}
#endif


#ifdef RUN_T225
static void test_T225(void) {
    print_double_result("T225.1", "scalbn(1.0, 10)", scalbn(1.0, 10));
    print_double_result("T225.2", "scalbn(1.0, 2000)", scalbn(1.0, 2000));
    print_double_result("T225.3", "scalbn(1.0, -2000)", scalbn(1.0, -2000));
    print_double_result("T225.4", "scalbn(0.0, 5)", scalbn(0.0, 5));
}
#endif


#ifdef RUN_T226
static void test_T226(void) {
    print_double_result("T226.1", "scalbln(1.0, 10L)", scalbln(1.0, 10L));
    print_double_result("T226.2", "scalbln(1.0, 100000L)", scalbln(1.0, 100000L));
}
#endif


#ifdef RUN_T227
static void test_T227(void) {
    print_int_result("T227.1", "ilogb(NAN)", ilogb(NAN));
    print_int_result("T227.2", "ilogb(INFINITY)", ilogb(INFINITY));
    print_int_result("T227.3", "ilogb(0.0)", ilogb(0.0));
    print_int_result("T227.4", "ilogb(5e-324)", ilogb(5e-324));
    print_int_result("T227.5", "ilogb(1.0)", ilogb(1.0));
    print_int_result("T227.6", "ilogb(1024.0)", ilogb(1024.0));
}
#endif


#ifdef RUN_T228
static void test_T228(void) {
    print_double_result("T228.1", "nextafter(1.0, 1.0)", nextafter(1.0, 1.0));
}
#endif


#ifdef RUN_T229
static void test_T229(void) {
    print_double_result("T229.1", "nextafter(0.0, 1.0)", nextafter(0.0, 1.0));
    print_double_result("T229.2", "nextafter(-0.0, 1.0)", nextafter(-0.0, 1.0));
}
#endif


#ifdef RUN_T230
static void test_T230(void) {
    print_double_result("T230.1", "nextafter(0.0, -1.0)", nextafter(0.0, -1.0));
    print_double_result("T230.2", "nextafter(-0.0, -1.0)", nextafter(-0.0, -1.0));
}
#endif


#ifdef RUN_T231
static void test_T231(void) {
    print_double_result("T231.1", "nextafter(-5e-324, 1.0)", nextafter(-5e-324, 1.0));
}
#endif


#ifdef RUN_T232
static void test_T232(void) {
    print_double_result("T232.1", "nextafter(2.2250738585072009e-308, INFINITY)", nextafter(2.2250738585072009e-308, INFINITY));
}
#endif


#ifdef RUN_T233
static void test_T233(void) {
    print_double_result("T233.1", "nextafter(1.7976931348623157e+308, INFINITY)", nextafter(1.7976931348623157e+308, INFINITY));
}
#endif


#ifdef RUN_T234
static void test_T234(void) {
    print_double_result("T234.1", "nextafter(NAN, 1.0)", nextafter(NAN, 1.0));
    print_double_result("T234.2", "nextafter(1.0, NAN)", nextafter(1.0, NAN));
}
#endif


#ifdef RUN_T235
static void test_T235(void) {
#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS
    print_double_result("T235.1", "nexttoward(1.0, 1.0L)", nexttoward(1.0, 1.0L));
    print_double_result("T235.2", "nexttoward(0.0, 1.0L)", nexttoward(0.0, 1.0L));
    print_double_result("T235.3", "nexttoward(1.0, NAN)", nexttoward(1.0, NAN));
#endif
}
#endif


#ifdef RUN_T236
static void test_T236(void) {
    print_double_result("T236.1", "nan(\"\")", nan(""));
}
#endif


#ifdef RUN_T237
static void test_T237(void) {
    print_int_result("T237.1", "fpclassify(0.0)", fpclassify(0.0));
    print_int_result("T237.2", "fpclassify(NAN)", fpclassify(NAN));
    print_int_result("T237.3", "fpclassify(INFINITY)", fpclassify(INFINITY));
    print_int_result("T237.4", "fpclassify(1.0)", fpclassify(1.0));
    print_int_result("T237.5", "fpclassify(5e-324)", fpclassify(5e-324));
}
#endif


#ifdef RUN_T238
static void test_T238(void) {
    print_int_result("T238.1", "signbit(1.0)", signbit(1.0));
    print_int_result("T238.2", "signbit(-1.0)", signbit(-1.0));
    print_int_result("T238.3", "signbit(0.0)", signbit(0.0));
    print_int_result("T238.4", "signbit(-0.0)", signbit(-0.0));
}
#endif


#ifdef RUN_T239
static void test_T239(void) {
    print_float_result("T239.1", "sqrtf(NAN)", sqrtf(NAN));
    print_float_result("T239.2", "sqrtf(INFINITY)", sqrtf(INFINITY));
    print_float_result("T239.3", "sqrtf(-INFINITY)", sqrtf(-INFINITY));
    print_float_result("T239.4", "sqrtf(0.0f)", sqrtf(0.0f));
    print_float_result("T239.5", "sqrtf(-0.0f)", sqrtf(-0.0f));
    print_float_result("T239.6", "sqrtf(-1.0f)", sqrtf(-1.0f));
    print_float_result("T239.7", "sqrtf(1.4e-45f)", sqrtf(1.4e-45f));
    print_float_result("T239.8", "sqrtf(4.0f)", sqrtf(4.0f));
    print_float_result("T239.9", "sqrtf(1e30f)", sqrtf(1e30f));
}
#endif


#ifdef RUN_T240
static void test_T240(void) {
    print_float_result("T240.1", "cbrtf(NAN)", cbrtf(NAN));
    print_float_result("T240.2", "cbrtf(INFINITY)", cbrtf(INFINITY));
    print_float_result("T240.3", "cbrtf(-INFINITY)", cbrtf(-INFINITY));
    print_float_result("T240.4", "cbrtf(-0.0f)", cbrtf(-0.0f));
    print_float_result("T240.5", "cbrtf(-8.0f)", cbrtf(-8.0f));
    print_float_result("T240.6", "cbrtf(1.4e-45f)", cbrtf(1.4e-45f));
    print_float_result("T240.7", "cbrtf(8.0f)", cbrtf(8.0f));
}
#endif


#ifdef RUN_T241
static void test_T241(void) {
    print_float_result("T241.1", "fabsf(-1.0f)", fabsf(-1.0f));
    print_float_result("T241.2", "fabsf(1.0f)", fabsf(1.0f));
    print_float_result("T241.3", "fabsf(NAN)", fabsf(NAN));
    print_float_result("T241.4", "fabsf(-INFINITY)", fabsf(-INFINITY));
}
#endif


#ifdef RUN_T242
static void test_T242(void) {
    print_float_result("T242.1", "copysignf(1.0f, -1.0f)", copysignf(1.0f, -1.0f));
    print_float_result("T242.2", "copysignf(-1.0f, 1.0f)", copysignf(-1.0f, 1.0f));
    print_float_result("T242.3", "copysignf(NAN, -1.0f)", copysignf(NAN, -1.0f));
}
#endif


#ifdef RUN_T243
static void test_T243(void) {
    print_float_result("T243.1", "fmaxf(2.0f, 1.0f)", fmaxf(2.0f, 1.0f));
    print_float_result("T243.2", "fmaxf(NAN, 1.0f)", fmaxf(NAN, 1.0f));
    print_float_result("T243.3", "fmaxf(INFINITY, -INFINITY)", fmaxf(INFINITY, -INFINITY));
}
#endif


#ifdef RUN_T244
static void test_T244(void) {
    print_float_result("T244.1", "fminf(2.0f, 1.0f)", fminf(2.0f, 1.0f));
    print_float_result("T244.2", "fminf(NAN, 1.0f)", fminf(NAN, 1.0f));
    print_float_result("T244.3", "fminf(-INFINITY, 1.0f)", fminf(-INFINITY, 1.0f));
}
#endif


#ifdef RUN_T245
static void test_T245(void) {
    print_float_result("T245.1", "fdimf(3.0f, 1.0f)", fdimf(3.0f, 1.0f));
    print_float_result("T245.2", "fdimf(1.0f, 3.0f)", fdimf(1.0f, 3.0f));
    print_float_result("T245.3", "fdimf(NAN, 1.0f)", fdimf(NAN, 1.0f));
    print_float_result("T245.4", "fdimf(INFINITY, 1.0f)", fdimf(INFINITY, 1.0f));
}
#endif


#ifdef RUN_T246
static void test_T246(void) {
    print_float_result("T246.1", "hypotf(INFINITY, 1.0f)", hypotf(INFINITY, 1.0f));
    print_float_result("T246.2", "hypotf(NAN, 1.0f)", hypotf(NAN, 1.0f));
    print_float_result("T246.3", "hypotf(0.0f, 0.0f)", hypotf(0.0f, 0.0f));
    print_float_result("T246.4", "hypotf(3e20f, 4e20f)", hypotf(3e20f, 4e20f));
    print_float_result("T246.5", "hypotf(3.0f, 4.0f)", hypotf(3.0f, 4.0f));
}
#endif


#ifdef RUN_T247
static void test_T247(void) {
    print_float_result("T247.1", "fmaf(2.0f, 3.0f, 1.0f)", fmaf(2.0f, 3.0f, 1.0f));
    print_float_result("T247.2", "fmaf(NAN, 1.0f, 1.0f)", fmaf(NAN, 1.0f, 1.0f));
    print_float_result("T247.3", "fmaf(INFINITY, 1.0f, -INFINITY)", fmaf(INFINITY, 1.0f, -INFINITY));
    print_float_result("T247.4", "fmaf(1e20f, 1e20f, 0.0f)", fmaf(1e20f, 1e20f, 0.0f));
}
#endif


#ifdef RUN_T248
static void test_T248(void) {
    print_float_result("T248.1", "ceilf(1.5f)", ceilf(1.5f));
    print_float_result("T248.2", "ceilf(-1.5f)", ceilf(-1.5f));
    print_float_result("T248.3", "ceilf(0.0f)", ceilf(0.0f));
    print_float_result("T248.4", "ceilf(NAN)", ceilf(NAN));
    print_float_result("T248.5", "ceilf(INFINITY)", ceilf(INFINITY));
}
#endif


#ifdef RUN_T249
static void test_T249(void) {
    print_float_result("T249.1", "floorf(1.5f)", floorf(1.5f));
    print_float_result("T249.2", "floorf(-1.5f)", floorf(-1.5f));
    print_float_result("T249.3", "floorf(0.0f)", floorf(0.0f));
    print_float_result("T249.4", "floorf(NAN)", floorf(NAN));
}
#endif


#ifdef RUN_T250
static void test_T250(void) {
    print_float_result("T250.1", "roundf(0.5f)", roundf(0.5f));
    print_float_result("T250.2", "roundf(-0.5f)", roundf(-0.5f));
    print_float_result("T250.3", "roundf(NAN)", roundf(NAN));
    print_float_result("T250.4", "roundf(INFINITY)", roundf(INFINITY));
}
#endif


#ifdef RUN_T251
static void test_T251(void) {
    print_float_result("T251.1", "truncf(1.9f)", truncf(1.9f));
    print_float_result("T251.2", "truncf(-1.9f)", truncf(-1.9f));
    print_float_result("T251.3", "truncf(NAN)", truncf(NAN));
}
#endif


#ifdef RUN_T252
static void test_T252(void) {
    print_float_result("T252.1", "nearbyintf(1.5f)", nearbyintf(1.5f));
    print_float_result("T252.2", "nearbyintf(-1.5f)", nearbyintf(-1.5f));
    print_float_result("T252.3", "nearbyintf(NAN)", nearbyintf(NAN));
}
#endif


#ifdef RUN_T253
static void test_T253(void) {
    print_float_result("T253.1", "rintf(1.5f)", rintf(1.5f));
    print_float_result("T253.2", "rintf(0.0f)", rintf(0.0f));
    print_float_result("T253.3", "rintf(NAN)", rintf(NAN));
}
#endif


#ifdef RUN_T254
static void test_T254(void) {
    print_long_result("T254.1", "lrintf(1.5f)", lrintf(1.5f));
    print_long_result("T254.2", "lrintf(-1.5f)", lrintf(-1.5f));
    print_long_result("T254.3", "lrintf(1e20f)", lrintf(1e20f));
    print_long_result("T254.4", "lrintf(NAN)", lrintf(NAN));
    print_long_result("T254.5", "lrintf(INFINITY)", lrintf(INFINITY));
}
#endif


#ifdef RUN_T255
static void test_T255(void) {
    print_ll_result("T255.1", "llrintf(1.5f)", llrintf(1.5f));
    print_ll_result("T255.2", "llrintf(1e20f)", llrintf(1e20f));
    print_ll_result("T255.3", "llrintf(NAN)", llrintf(NAN));
}
#endif


#ifdef RUN_T256
static void test_T256(void) {
    print_long_result("T256.1", "lroundf(0.5f)", lroundf(0.5f));
    print_long_result("T256.2", "lroundf(-0.5f)", lroundf(-0.5f));
    print_long_result("T256.3", "lroundf(1e20f)", lroundf(1e20f));
    print_long_result("T256.4", "lroundf(NAN)", lroundf(NAN));
}
#endif


#ifdef RUN_T257
static void test_T257(void) {
    print_ll_result("T257.1", "llroundf(0.5f)", llroundf(0.5f));
    print_ll_result("T257.2", "llroundf(1e20f)", llroundf(1e20f));
    print_ll_result("T257.3", "llroundf(NAN)", llroundf(NAN));
}
#endif


#ifdef RUN_T258
static void test_T258(void) {
    print_float_result("T258.1", "expf(NAN)", expf(NAN));
    print_float_result("T258.2", "expf(INFINITY)", expf(INFINITY));
    print_float_result("T258.3", "expf(-INFINITY)", expf(-INFINITY));
    print_float_result("T258.4", "expf(200.0f)", expf(200.0f));
    print_float_result("T258.5", "expf(-200.0f)", expf(-200.0f));
    print_float_result("T258.6", "expf(1e-8f)", expf(1e-8f));
    print_float_result("T258.7", "expf(0.0f)", expf(0.0f));
    print_float_result("T258.8", "expf(1.0f)", expf(1.0f));
}
#endif


#ifdef RUN_T259
static void test_T259(void) {
    print_float_result("T259.1", "exp2f(NAN)", exp2f(NAN));
    print_float_result("T259.2", "exp2f(INFINITY)", exp2f(INFINITY));
    print_float_result("T259.3", "exp2f(-INFINITY)", exp2f(-INFINITY));
    print_float_result("T259.4", "exp2f(200.0f)", exp2f(200.0f));
    print_float_result("T259.5", "exp2f(-200.0f)", exp2f(-200.0f));
    print_float_result("T259.6", "exp2f(0.0f)", exp2f(0.0f));
    print_float_result("T259.7", "exp2f(1.0f)", exp2f(1.0f));
}
#endif


#ifdef RUN_T260
static void test_T260(void) {
    print_float_result("T260.1", "expm1f(NAN)", expm1f(NAN));
    print_float_result("T260.2", "expm1f(INFINITY)", expm1f(INFINITY));
    print_float_result("T260.3", "expm1f(-INFINITY)", expm1f(-INFINITY));
    print_float_result("T260.4", "expm1f(1e-9f)", expm1f(1e-9f));
    print_float_result("T260.5", "expm1f(200.0f)", expm1f(200.0f));
    print_float_result("T260.6", "expm1f(1.0f)", expm1f(1.0f));
}
#endif


#ifdef RUN_T261
static void test_T261(void) {
    print_float_result("T261.1", "logf(0.0f)", logf(0.0f));
    print_float_result("T261.2", "logf(-1.0f)", logf(-1.0f));
    print_float_result("T261.3", "logf(1.4e-45f)", logf(1.4e-45f));
    print_float_result("T261.4", "logf(NAN)", logf(NAN));
    print_float_result("T261.5", "logf(INFINITY)", logf(INFINITY));
    print_float_result("T261.6", "logf(1.0f)", logf(1.0f));
    print_float_result("T261.7", "logf(2.0f)", logf(2.0f));
}
#endif


#ifdef RUN_T262
static void test_T262(void) {
    print_float_result("T262.1", "log2f(0.0f)", log2f(0.0f));
    print_float_result("T262.2", "log2f(-1.0f)", log2f(-1.0f));
    print_float_result("T262.3", "log2f(NAN)", log2f(NAN));
    print_float_result("T262.4", "log2f(INFINITY)", log2f(INFINITY));
    print_float_result("T262.5", "log2f(1.0f)", log2f(1.0f));
    print_float_result("T262.6", "log2f(2.0f)", log2f(2.0f));
}
#endif


#ifdef RUN_T263
static void test_T263(void) {
    print_float_result("T263.1", "log10f(0.0f)", log10f(0.0f));
    print_float_result("T263.2", "log10f(-1.0f)", log10f(-1.0f));
    print_float_result("T263.3", "log10f(NAN)", log10f(NAN));
    print_float_result("T263.4", "log10f(INFINITY)", log10f(INFINITY));
    print_float_result("T263.5", "log10f(1.0f)", log10f(1.0f));
    print_float_result("T263.6", "log10f(10.0f)", log10f(10.0f));
}
#endif


#ifdef RUN_T264
static void test_T264(void) {
    print_float_result("T264.1", "log1pf(-1.0f)", log1pf(-1.0f));
    print_float_result("T264.2", "log1pf(-2.0f)", log1pf(-2.0f));
    print_float_result("T264.3", "log1pf(1e-9f)", log1pf(1e-9f));
    print_float_result("T264.4", "log1pf(NAN)", log1pf(NAN));
    print_float_result("T264.5", "log1pf(INFINITY)", log1pf(INFINITY));
    print_float_result("T264.6", "log1pf(-INFINITY)", log1pf(-INFINITY));
    print_float_result("T264.7", "log1pf(1.0f)", log1pf(1.0f));
}
#endif


#ifdef RUN_T265
static void test_T265(void) {
    print_float_result("T265.1", "powf(2.0f, 0.0f)", powf(2.0f, 0.0f));
    print_float_result("T265.2", "powf(-3.0f, 0.0f)", powf(-3.0f, 0.0f));
}
#endif


#ifdef RUN_T266
static void test_T266(void) {
    print_float_result("T266.1", "powf(NAN, 2.0f)", powf(NAN, 2.0f));
    print_float_result("T266.2", "powf(2.0f, NAN)", powf(2.0f, NAN));
}
#endif


#ifdef RUN_T267
static void test_T267(void) {
    print_float_result("T267.1", "powf(1.0f, NAN)", powf(1.0f, NAN));
}
#endif


#ifdef RUN_T268
static void test_T268(void) {
    print_float_result("T268.1", "powf(-2.0f, 0.5f)", powf(-2.0f, 0.5f));
}
#endif


#ifdef RUN_T269
static void test_T269(void) {
    print_float_result("T269.1", "powf(-2.0f, 3.0f)", powf(-2.0f, 3.0f));
}
#endif


#ifdef RUN_T270
static void test_T270(void) {
    print_float_result("T270.1", "powf(-2.0f, 4.0f)", powf(-2.0f, 4.0f));
}
#endif


#ifdef RUN_T271
static void test_T271(void) {
    print_float_result("T271.1", "powf(0.0f, 2.0f)", powf(0.0f, 2.0f));
    print_float_result("T271.2", "powf(0.0f, -1.0f)", powf(0.0f, -1.0f));
    print_float_result("T271.3", "powf(-0.0f, -1.0f)", powf(-0.0f, -1.0f));
    print_float_result("T271.4", "powf(-0.0f, 3.0f)", powf(-0.0f, 3.0f));
}
#endif


#ifdef RUN_T272
static void test_T272(void) {
    print_float_result("T272.1", "powf(INFINITY, 2.0f)", powf(INFINITY, 2.0f));
    print_float_result("T272.2", "powf(INFINITY, -2.0f)", powf(INFINITY, -2.0f));
    print_float_result("T272.3", "powf(-INFINITY, 3.0f)", powf(-INFINITY, 3.0f));
    print_float_result("T272.4", "powf(-INFINITY, 4.0f)", powf(-INFINITY, 4.0f));
}
#endif


#ifdef RUN_T273
static void test_T273(void) {
    print_float_result("T273.1", "powf(2.0f, INFINITY)", powf(2.0f, INFINITY));
    print_float_result("T273.2", "powf(2.0f, -INFINITY)", powf(2.0f, -INFINITY));
    print_float_result("T273.3", "powf(0.5f, INFINITY)", powf(0.5f, INFINITY));
}
#endif


#ifdef RUN_T274
static void test_T274(void) {
    print_float_result("T274.1", "powf(10.0f, 50.0f)", powf(10.0f, 50.0f));
    print_float_result("T274.2", "powf(10.0f, -50.0f)", powf(10.0f, -50.0f));
}
#endif


#ifdef RUN_T275
static void test_T275(void) {
    print_float_result("T275.1", "powf(1.0f + 1e-6f, 1e8f)", powf(1.0f + 1e-6f, 1e8f));
}
#endif


#ifdef RUN_T276
static void test_T276(void) {
    print_float_result("T276.1", "powf(1.4e-45f, 0.5f)", powf(1.4e-45f, 0.5f));
}
#endif


#ifdef RUN_T277
static void test_T277(void) {
    print_float_result("T277.1", "powf(2.0f, 10.0f)", powf(2.0f, 10.0f));
    print_float_result("T277.2", "powf(1.5f, 2.0f)", powf(1.5f, 2.0f));
    print_float_result("T277.3", "powf(4.0f, 0.5f)", powf(4.0f, 0.5f));
}
#endif


#ifdef RUN_T278
static void test_T278(void) {
    print_float_result("T278.1", "sinf(0.0f)", sinf(0.0f));
    print_float_result("T278.2", "sinf(1e-9f)", sinf(1e-9f));
    print_float_result("T278.3", "sinf(0.5f)", sinf(0.5f));
    print_float_result("T278.4", "sinf(INFINITY)", sinf(INFINITY));
    print_float_result("T278.5", "sinf(-INFINITY)", sinf(-INFINITY));
    print_float_result("T278.6", "sinf(NAN)", sinf(NAN));
    print_float_result("T278.7", "sinf(7.0f)", sinf(7.0f));
    print_float_result("T278.8", "sinf((float)(M_PI+0.5))", sinf((float)(M_PI+0.5)));
}
#endif


#ifdef RUN_T279
static void test_T279(void) {
    print_float_result("T279.1", "cosf(0.0f)", cosf(0.0f));
    print_float_result("T279.2", "cosf(0.5f)", cosf(0.5f));
    print_float_result("T279.3", "cosf(INFINITY)", cosf(INFINITY));
    print_float_result("T279.4", "cosf(NAN)", cosf(NAN));
    print_float_result("T279.5", "cosf(7.0f)", cosf(7.0f));
}
#endif


#ifdef RUN_T280
static void test_T280(void) {
    print_float_result("T280.1", "tanf(0.0f)", tanf(0.0f));
    print_float_result("T280.2", "tanf(0.5f)", tanf(0.5f));
    print_float_result("T280.3", "tanf(INFINITY)", tanf(INFINITY));
    print_float_result("T280.4", "tanf(NAN)", tanf(NAN));
    print_float_result("T280.5", "tanf(7.0f)", tanf(7.0f));
    print_float_result("T280.6", "tanf((float)(M_PI_2 - 1e-5))", tanf((float)(M_PI_2 - 1e-5)));
}
#endif


#ifdef RUN_T281
static void test_T281(void) {
    print_float_result("T281.1", "asinf(2.0f)", asinf(2.0f));
    print_float_result("T281.2", "asinf(1.0f)", asinf(1.0f));
    print_float_result("T281.3", "asinf(-1.0f)", asinf(-1.0f));
    print_float_result("T281.4", "asinf(1e-9f)", asinf(1e-9f));
    print_float_result("T281.5", "asinf(NAN)", asinf(NAN));
    print_float_result("T281.6", "asinf(0.5f)", asinf(0.5f));
}
#endif


#ifdef RUN_T282
static void test_T282(void) {
    print_float_result("T282.1", "acosf(2.0f)", acosf(2.0f));
    print_float_result("T282.2", "acosf(1.0f)", acosf(1.0f));
    print_float_result("T282.3", "acosf(-1.0f)", acosf(-1.0f));
    print_float_result("T282.4", "acosf(NAN)", acosf(NAN));
    print_float_result("T282.5", "acosf(0.0f)", acosf(0.0f));
    print_float_result("T282.6", "acosf(0.8f)", acosf(0.8f));
}
#endif


#ifdef RUN_T283
static void test_T283(void) {
    print_float_result("T283.1", "atanf(NAN)", atanf(NAN));
    print_float_result("T283.2", "atanf(INFINITY)", atanf(INFINITY));
    print_float_result("T283.3", "atanf(-INFINITY)", atanf(-INFINITY));
    print_float_result("T283.4", "atanf(1e20f)", atanf(1e20f));
    print_float_result("T283.5", "atanf(1e-9f)", atanf(1e-9f));
    print_float_result("T283.6", "atanf(1.0f)", atanf(1.0f));
}
#endif


#ifdef RUN_T284
static void test_T284(void) {
    print_float_result("T284.1", "atan2f(NAN, 1.0f)", atan2f(NAN, 1.0f));
    print_float_result("T284.2", "atan2f(0.0f, 1.0f)", atan2f(0.0f, 1.0f));
    print_float_result("T284.3", "atan2f(-0.0f, -1.0f)", atan2f(-0.0f, -1.0f));
    print_float_result("T284.4", "atan2f(1.0f, 0.0f)", atan2f(1.0f, 0.0f));
    print_float_result("T284.5", "atan2f(1.0f, 1.0f)", atan2f(1.0f, 1.0f));
    print_float_result("T284.6", "atan2f(1.0f, -1.0f)", atan2f(1.0f, -1.0f));
    print_float_result("T284.7", "atan2f(INFINITY, INFINITY)", atan2f(INFINITY, INFINITY));
}
#endif


#ifdef RUN_T285
static void test_T285(void) {
    print_float_result("T285.1", "sinhf(NAN)", sinhf(NAN));
    print_float_result("T285.2", "sinhf(INFINITY)", sinhf(INFINITY));
    print_float_result("T285.3", "sinhf(1e-9f)", sinhf(1e-9f));
    print_float_result("T285.4", "sinhf(200.0f)", sinhf(200.0f));
    print_float_result("T285.5", "sinhf(1.0f)", sinhf(1.0f));
}
#endif


#ifdef RUN_T286
static void test_T286(void) {
    print_float_result("T286.1", "coshf(NAN)", coshf(NAN));
    print_float_result("T286.2", "coshf(INFINITY)", coshf(INFINITY));
    print_float_result("T286.3", "coshf(1e-9f)", coshf(1e-9f));
    print_float_result("T286.4", "coshf(200.0f)", coshf(200.0f));
    print_float_result("T286.5", "coshf(1.0f)", coshf(1.0f));
}
#endif


#ifdef RUN_T287
static void test_T287(void) {
    print_float_result("T287.1", "tanhf(NAN)", tanhf(NAN));
    print_float_result("T287.2", "tanhf(INFINITY)", tanhf(INFINITY));
    print_float_result("T287.3", "tanhf(-INFINITY)", tanhf(-INFINITY));
    print_float_result("T287.4", "tanhf(1e-9f)", tanhf(1e-9f));
    print_float_result("T287.5", "tanhf(100.0f)", tanhf(100.0f));
    print_float_result("T287.6", "tanhf(0.5f)", tanhf(0.5f));
}
#endif


#ifdef RUN_T288
static void test_T288(void) {
    print_float_result("T288.1", "asinhf(NAN)", asinhf(NAN));
    print_float_result("T288.2", "asinhf(INFINITY)", asinhf(INFINITY));
    print_float_result("T288.3", "asinhf(1e-9f)", asinhf(1e-9f));
    print_float_result("T288.4", "asinhf(1e20f)", asinhf(1e20f));
    print_float_result("T288.5", "asinhf(1.0f)", asinhf(1.0f));
}
#endif


#ifdef RUN_T289
static void test_T289(void) {
    print_float_result("T289.1", "acoshf(0.5f)", acoshf(0.5f));
    print_float_result("T289.2", "acoshf(1.0f)", acoshf(1.0f));
    print_float_result("T289.3", "acoshf(NAN)", acoshf(NAN));
    print_float_result("T289.4", "acoshf(INFINITY)", acoshf(INFINITY));
    print_float_result("T289.5", "acoshf(2.0f)", acoshf(2.0f));
}
#endif


#ifdef RUN_T290
static void test_T290(void) {
    print_float_result("T290.1", "atanhf(2.0f)", atanhf(2.0f));
    print_float_result("T290.2", "atanhf(1.0f)", atanhf(1.0f));
    print_float_result("T290.3", "atanhf(-1.0f)", atanhf(-1.0f));
    print_float_result("T290.4", "atanhf(1e-9f)", atanhf(1e-9f));
    print_float_result("T290.5", "atanhf(NAN)", atanhf(NAN));
    print_float_result("T290.6", "atanhf(0.5f)", atanhf(0.5f));
}
#endif


#ifdef RUN_T291
static void test_T291(void) {
    print_float_result("T291.1", "erff(NAN)", erff(NAN));
    print_float_result("T291.2", "erff(INFINITY)", erff(INFINITY));
    print_float_result("T291.3", "erff(-INFINITY)", erff(-INFINITY));
    print_float_result("T291.4", "erff(1e-9f)", erff(1e-9f));
    print_float_result("T291.5", "erff(0.3f)", erff(0.3f));
    print_float_result("T291.6", "erff(1.0f)", erff(1.0f));
    print_float_result("T291.7", "erff(5.0f)", erff(5.0f));
}
#endif


#ifdef RUN_T292
static void test_T292(void) {
    print_float_result("T292.1", "erfcf(NAN)", erfcf(NAN));
    print_float_result("T292.2", "erfcf(INFINITY)", erfcf(INFINITY));
    print_float_result("T292.3", "erfcf(-INFINITY)", erfcf(-INFINITY));
    print_float_result("T292.4", "erfcf(1e-9f)", erfcf(1e-9f));
    print_float_result("T292.5", "erfcf(1.0f)", erfcf(1.0f));
    print_float_result("T292.6", "erfcf(10.0f)", erfcf(10.0f));
}
#endif


#ifdef RUN_T293
static void test_T293(void) {
    print_float_result("T293.1", "tgammaf(NAN)", tgammaf(NAN));
    print_float_result("T293.2", "tgammaf(0.0f)", tgammaf(0.0f));
    print_float_result("T293.3", "tgammaf(-0.0f)", tgammaf(-0.0f));
    print_float_result("T293.4", "tgammaf(-1.0f)", tgammaf(-1.0f));
    print_float_result("T293.5", "tgammaf(-INFINITY)", tgammaf(-INFINITY));
    print_float_result("T293.6", "tgammaf(INFINITY)", tgammaf(INFINITY));
    print_float_result("T293.7", "tgammaf(40.0f)", tgammaf(40.0f));
    print_float_result("T293.8", "tgammaf(0.5f)", tgammaf(0.5f));
    print_float_result("T293.9", "tgammaf(1.5f)", tgammaf(1.5f));
    print_float_result("T293.10", "tgammaf(-0.5f)", tgammaf(-0.5f));
}
#endif


#ifdef RUN_T294
static void test_T294(void) {
    float value;
    signgam = 0;
    value = lgammaf(0.0f);
    print_float_result("T294.1", "lgammaf(0.0f)", value);
    print_int_result("T294.1.signgam", "signgam", signgam);
    signgam = 0;
    value = lgammaf(-1.0f);
    print_float_result("T294.2", "lgammaf(-1.0f)", value);
    print_int_result("T294.2.signgam", "signgam", signgam);
    signgam = 0;
    value = lgammaf(0.5f);
    print_float_result("T294.3", "lgammaf(0.5f)", value);
    print_int_result("T294.3.signgam", "signgam", signgam);
    signgam = 0;
    value = lgammaf(1.0f);
    print_float_result("T294.4", "lgammaf(1.0f)", value);
    print_int_result("T294.4.signgam", "signgam", signgam);
    signgam = 0;
    value = lgammaf(NAN);
    print_float_result("T294.5", "lgammaf(NAN)", value);
    print_int_result("T294.5.signgam", "signgam", signgam);
    signgam = 0;
    value = lgammaf(INFINITY);
    print_float_result("T294.6", "lgammaf(INFINITY)", value);
    print_int_result("T294.6.signgam", "signgam", signgam);
}
#endif


#ifdef RUN_T295
static void test_T295(void) {
    print_float_result("T295.1", "fmodf(1.0f, 0.0f)", fmodf(1.0f, 0.0f));
    print_float_result("T295.2", "fmodf(INFINITY, 1.0f)", fmodf(INFINITY, 1.0f));
    print_float_result("T295.3", "fmodf(NAN, 1.0f)", fmodf(NAN, 1.0f));
    print_float_result("T295.4", "fmodf(0.5f, 1.0f)", fmodf(0.5f, 1.0f));
    print_float_result("T295.5", "fmodf(1.0f, 1.0f)", fmodf(1.0f, 1.0f));
    print_float_result("T295.6", "fmodf(5.0f, 3.0f)", fmodf(5.0f, 3.0f));
}
#endif


#ifdef RUN_T296
static void test_T296(void) {
    print_float_result("T296.1", "remainderf(1.0f, 0.0f)", remainderf(1.0f, 0.0f));
    print_float_result("T296.2", "remainderf(INFINITY, 1.0f)", remainderf(INFINITY, 1.0f));
    print_float_result("T296.3", "remainderf(NAN, 1.0f)", remainderf(NAN, 1.0f));
    print_float_result("T296.4", "remainderf(5.0f, 3.0f)", remainderf(5.0f, 3.0f));
}
#endif


#ifdef RUN_T297
static void test_T297(void) {
    int qi;
    float value;
    qi = 0;
    value = remquof(5.0f, 3.0f, &qi);
    print_float_result("T297.1", "remquof(5.0f, 3.0f, &qi)", value);
    print_int_result("T297.1.qi", "qi", qi);
    qi = 0;
    value = remquof(NAN, 1.0f, &qi);
    print_float_result("T297.2", "remquof(NAN, 1.0f, &qi)", value);
    print_int_result("T297.2.qi", "qi", qi);
}
#endif


#ifdef RUN_T298
static void test_T298(void) {
    int e;
    float value;
    e = 0;
    value = frexpf(0.0f, &e);
    print_float_result("T298.1", "frexpf(0.0f, &e)", value);
    print_int_result("T298.1.e", "e", e);
    e = 0;
    value = frexpf(NAN, &e);
    print_float_result("T298.2", "frexpf(NAN, &e)", value);
    print_int_result("T298.2.e", "e", e);
    e = 0;
    value = frexpf(INFINITY, &e);
    print_float_result("T298.3", "frexpf(INFINITY, &e)", value);
    print_int_result("T298.3.e", "e", e);
    e = 0;
    value = frexpf(1.0f, &e);
    print_float_result("T298.4", "frexpf(1.0f, &e)", value);
    print_int_result("T298.4.e", "e", e);
    e = 0;
    value = frexpf(1.4e-45f, &e);
    print_float_result("T298.5", "frexpf(1.4e-45f, &e)", value);
    print_int_result("T298.5.e", "e", e);
}
#endif


#ifdef RUN_T299
static void test_T299(void) {
    print_float_result("T299.1", "ldexpf(1.0f, 10)", ldexpf(1.0f, 10));
    print_float_result("T299.2", "ldexpf(1.0f, 200)", ldexpf(1.0f, 200));
    print_float_result("T299.3", "ldexpf(1.0f, -200)", ldexpf(1.0f, -200));
    print_float_result("T299.4", "ldexpf(0.0f, 5)", ldexpf(0.0f, 5));
    print_float_result("T299.5", "ldexpf(NAN, 5)", ldexpf(NAN, 5));
}
#endif


#ifdef RUN_T300
static void test_T300(void) {
    float ipf;
    float value;
    ipf = 0.0f;
    value = modff(0.0f, &ipf);
    print_float_result("T300.1", "modff(0.0f, &ipf)", value);
    print_float_result("T300.1.ipf", "ipf", ipf);
    ipf = 0.0f;
    value = modff(NAN, &ipf);
    print_float_result("T300.2", "modff(NAN, &ipf)", value);
    print_float_result("T300.2.ipf", "ipf", ipf);
    ipf = 0.0f;
    value = modff(INFINITY, &ipf);
    print_float_result("T300.3", "modff(INFINITY, &ipf)", value);
    print_float_result("T300.3.ipf", "ipf", ipf);
    ipf = 0.0f;
    value = modff(2.5f, &ipf);
    print_float_result("T300.4", "modff(2.5f, &ipf)", value);
    print_float_result("T300.4.ipf", "ipf", ipf);
    ipf = 0.0f;
    value = modff(-2.5f, &ipf);
    print_float_result("T300.5", "modff(-2.5f, &ipf)", value);
    print_float_result("T300.5.ipf", "ipf", ipf);
}
#endif


#ifdef RUN_T301
static void test_T301(void) {
    print_float_result("T301.1", "logbf(NAN)", logbf(NAN));
    print_float_result("T301.2", "logbf(INFINITY)", logbf(INFINITY));
    print_float_result("T301.3", "logbf(0.0f)", logbf(0.0f));
    print_float_result("T301.4", "logbf(1.4e-45f)", logbf(1.4e-45f));
    print_float_result("T301.5", "logbf(1.0f)", logbf(1.0f));
}
#endif


#ifdef RUN_T302
static void test_T302(void) {
    print_float_result("T302.1", "scalbnf(1.0f, 10)", scalbnf(1.0f, 10));
    print_float_result("T302.2", "scalbnf(1.0f, 200)", scalbnf(1.0f, 200));
    print_float_result("T302.3", "scalbnf(1.0f, -200)", scalbnf(1.0f, -200));
}
#endif


#ifdef RUN_T303
static void test_T303(void) {
    print_float_result("T303.1", "scalblnf(1.0f, 10L)", scalblnf(1.0f, 10L));
    print_float_result("T303.2", "scalblnf(1.0f, 100000L)", scalblnf(1.0f, 100000L));
}
#endif


#ifdef RUN_T304
static void test_T304(void) {
    print_int_result("T304.1", "ilogbf(NAN)", ilogbf(NAN));
    print_int_result("T304.2", "ilogbf(INFINITY)", ilogbf(INFINITY));
    print_int_result("T304.3", "ilogbf(0.0f)", ilogbf(0.0f));
    print_int_result("T304.4", "ilogbf(1.4e-45f)", ilogbf(1.4e-45f));
    print_int_result("T304.5", "ilogbf(1.0f)", ilogbf(1.0f));
}
#endif


#ifdef RUN_T305
static void test_T305(void) {
    print_float_result("T305.1", "nextafterf(1.0f, 1.0f)", nextafterf(1.0f, 1.0f));
    print_float_result("T305.2", "nextafterf(0.0f, 1.0f)", nextafterf(0.0f, 1.0f));
    print_float_result("T305.3", "nextafterf(-0.0f, -1.0f)", nextafterf(-0.0f, -1.0f));
    print_float_result("T305.4", "nextafterf(-1.4e-45f, 1.0f)", nextafterf(-1.4e-45f, 1.0f));
    print_float_result("T305.5", "nextafterf(3.4028235e38f, INFINITY)", nextafterf(3.4028235e38f, INFINITY));
    print_float_result("T305.6", "nextafterf(NAN, 1.0f)", nextafterf(NAN, 1.0f));
}
#endif


#ifdef RUN_T306
static void test_T306(void) {
#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS
    print_float_result("T306.1", "nexttowardf(1.0f, 1.0L)", nexttowardf(1.0f, 1.0L));
    print_float_result("T306.2", "nexttowardf(0.0f, 1.0L)", nexttowardf(0.0f, 1.0L));
#endif
}
#endif


#ifdef RUN_T307
static void test_T307(void) {
    print_float_result("T307.1", "nanf(\"\")", nanf(""));
}
#endif


#ifdef RUN_T308
static void test_T308(void) {
    print_int_result("T308.1", "isnan(NAN)", isnan(NAN));
    print_int_result("T308.2", "isnan(1.0)", isnan(1.0));
    print_int_result("T308.3", "isnan(INFINITY)", isnan(INFINITY));
}
#endif


#ifdef RUN_T309
static void test_T309(void) {
    print_int_result("T309.1", "isinf(INFINITY)", isinf(INFINITY));
    print_int_result("T309.2", "isinf(-INFINITY)", isinf(-INFINITY));
    print_int_result("T309.3", "isinf(1.0)", isinf(1.0));
    print_int_result("T309.4", "isinf(NAN)", isinf(NAN));
}
#endif


#ifdef RUN_T310
static void test_T310(void) {
    print_int_result("T310.1", "isfinite(1.0)", isfinite(1.0));
    print_int_result("T310.2", "isfinite(INFINITY)", isfinite(INFINITY));
    print_int_result("T310.3", "isfinite(NAN)", isfinite(NAN));
}
#endif


#ifdef RUN_T311
static void test_T311(void) {
    print_int_result("T311.1", "isnormal(1.0)", isnormal(1.0));
    print_int_result("T311.2", "isnormal(5e-324)", isnormal(5e-324));
    print_int_result("T311.3", "isnormal(0.0)", isnormal(0.0));
    print_int_result("T311.4", "isnormal(INFINITY)", isnormal(INFINITY));
    print_int_result("T311.5", "isnormal(NAN)", isnormal(NAN));
}
#endif


#ifdef RUN_T312
static void test_T312(void) {
    print_int_result("T312.1", "isnan(NAN)", isnan(NAN));
    print_int_result("T312.2", "isinf(INFINITY)", isinf(INFINITY));
    print_int_result("T312.3", "isfinite(1.0f)", isfinite(1.0f));
    print_int_result("T312.4", "isnormal(1.0f)", isnormal(1.0f));
}
#endif


#ifdef RUN_T313
static void test_T313(void) {
    print_int_result("T313.1", "isgreater(2.0, 1.0)", isgreater(2.0, 1.0));
    print_int_result("T313.2", "isgreater(1.0, 2.0)", isgreater(1.0, 2.0));
    print_int_result("T313.3", "isgreater(NAN, 1.0)", isgreater(NAN, 1.0));
    print_int_result("T313.4", "isgreater(1.0, NAN)", isgreater(1.0, NAN));
}
#endif


#ifdef RUN_T314
static void test_T314(void) {
    print_int_result("T314.1", "isgreaterequal(2.0, 1.0)", isgreaterequal(2.0, 1.0));
    print_int_result("T314.2", "isgreaterequal(1.0, 1.0)", isgreaterequal(1.0, 1.0));
    print_int_result("T314.3", "isgreaterequal(NAN, 1.0)", isgreaterequal(NAN, 1.0));
}
#endif


#ifdef RUN_T315
static void test_T315(void) {
    print_int_result("T315.1", "isless(1.0, 2.0)", isless(1.0, 2.0));
    print_int_result("T315.2", "isless(2.0, 1.0)", isless(2.0, 1.0));
    print_int_result("T315.3", "isless(NAN, 1.0)", isless(NAN, 1.0));
}
#endif


#ifdef RUN_T316
static void test_T316(void) {
    print_int_result("T316.1", "islessequal(1.0, 2.0)", islessequal(1.0, 2.0));
    print_int_result("T316.2", "islessequal(1.0, 1.0)", islessequal(1.0, 1.0));
    print_int_result("T316.3", "islessequal(NAN, 1.0)", islessequal(NAN, 1.0));
}
#endif


#ifdef RUN_T317
static void test_T317(void) {
    print_int_result("T317.1", "islessgreater(1.0, 2.0)", islessgreater(1.0, 2.0));
    print_int_result("T317.2", "islessgreater(1.0, 1.0)", islessgreater(1.0, 1.0));
    print_int_result("T317.3", "islessgreater(NAN, 1.0)", islessgreater(NAN, 1.0));
}
#endif


#ifdef RUN_T318
static void test_T318(void) {
    print_int_result("T318.1", "isunordered(NAN, 1.0)", isunordered(NAN, 1.0));
    print_int_result("T318.2", "isunordered(1.0, NAN)", isunordered(1.0, NAN));
    print_int_result("T318.3", "isunordered(1.0, 2.0)", isunordered(1.0, 2.0));
}
#endif


#ifdef RUN_T319
static void test_T319(void) {
    print_double_result("T319.1", "cabs(1.0 + 1.0*I)", cabs(1.0 + 1.0*I));
    print_double_result("T319.2", "cabs(1e200 + 1e200*I)", cabs(1e200 + 1e200*I));
    print_double_result("T319.3", "cabs(INFINITY + 1.0*I)", cabs(INFINITY + 1.0*I));
    print_double_result("T319.4", "cabs(NAN + 1.0*I)", cabs(NAN + 1.0*I));
}
#endif


#ifdef RUN_T320
static void test_T320(void) {
    print_double_result("T320.1", "carg(1.0 + 1.0*I)", carg(1.0 + 1.0*I));
    print_double_result("T320.2", "carg(-1.0 + 1.0*I)", carg(-1.0 + 1.0*I));
    print_double_result("T320.3", "carg(-1.0 - 1.0*I)", carg(-1.0 - 1.0*I));
    print_double_result("T320.4", "carg(1.0 - 1.0*I)", carg(1.0 - 1.0*I));
    print_double_result("T320.5", "carg(INFINITY + 0.0*I)", carg(INFINITY + 0.0*I));
    print_double_result("T320.6", "carg(NAN + 1.0*I)", carg(NAN + 1.0*I));
}
#endif


#ifdef RUN_T321
static void test_T321(void) {
    print_double_complex_result("T321.1", "conj(1.0 + 2.0*I)", conj(1.0 + 2.0*I));
    print_double_complex_result("T321.2", "conj(INFINITY + 1.0*I)", conj(INFINITY + 1.0*I));
}
#endif


#ifdef RUN_T322
static void test_T322(void) {
    print_double_result("T322.1", "creal(1.0 + 2.0*I)", creal(1.0 + 2.0 * I));
    print_double_result("T322.2", "cimag(1.0 + 2.0*I)", cimag(1.0 + 2.0 * I));
    print_double_result("T322.3", "creal(NAN + INFINITY*I)", creal(NAN + INFINITY * I));
}
#endif


#ifdef RUN_T323
static void test_T323(void) {
    print_double_complex_result("T323.1", "cexp(0.0 + 0.0*I)", cexp(0.0 + 0.0*I));
    print_double_complex_result("T323.2", "cexp(1.0 + M_PI*I)", cexp(1.0 + M_PI*I));
    print_double_complex_result("T323.3", "cexp(1000.0 + 1.0*I)", cexp(1000.0 + 1.0*I));
    print_double_complex_result("T323.4", "cexp(INFINITY + 0.0*I)", cexp(INFINITY + 0.0*I));
    print_double_complex_result("T323.5", "cexp(0.0 + INFINITY*I)", cexp(0.0 + INFINITY*I));
    print_double_complex_result("T323.6", "cexp(NAN + 1.0*I)", cexp(NAN + 1.0*I));
}
#endif


#ifdef RUN_T324
static void test_T324(void) {
    print_double_complex_result("T324.1", "clog(1.0 + 0.0*I)", clog(1.0 + 0.0*I));
    print_double_complex_result("T324.2", "clog(-1.0 + 0.0*I)", clog(-1.0 + 0.0*I));
    print_double_complex_result("T324.3", "clog(1.0 + 1.0*I)", clog(1.0 + 1.0*I));
    print_double_complex_result("T324.4", "clog(INFINITY + 1.0*I)", clog(INFINITY + 1.0*I));
    print_double_complex_result("T324.5", "clog(NAN + 1.0*I)", clog(NAN + 1.0*I));
}
#endif


#ifdef RUN_T325
static void test_T325(void) {
    print_double_complex_result("T325.1", "cpow(2.0 + 0.0*I, 3.0 + 0.0*I)", cpow(2.0 + 0.0*I, 3.0 + 0.0*I));
    print_double_complex_result("T325.2", "cpow(0.0 + 0.0*I, 1.0 + 0.0*I)", cpow(0.0 + 0.0*I, 1.0 + 0.0*I));
}
#endif


#ifdef RUN_T326
static void test_T326(void) {
    print_double_complex_result("T326.1", "cproj(1.0 + 2.0*I)", cproj(1.0 + 2.0*I));
    print_double_complex_result("T326.2", "cproj(INFINITY + 1.0*I)", cproj(INFINITY + 1.0*I));
    print_double_complex_result("T326.3", "cproj(1.0 + INFINITY*I)", cproj(1.0 + INFINITY*I));
    print_double_complex_result("T326.4", "cproj(NAN + 1.0*I)", cproj(NAN + 1.0*I));
}
#endif


#ifdef RUN_T327
static void test_T327(void) {
    print_double_complex_result("T327.1", "csqrt(4.0 + 0.0*I)", csqrt(4.0 + 0.0*I));
    print_double_complex_result("T327.2", "csqrt(-4.0 + 0.0*I)", csqrt(-4.0 + 0.0*I));
    print_double_complex_result("T327.3", "csqrt(0.0 + 0.0*I)", csqrt(0.0 + 0.0*I));
    print_double_complex_result("T327.4", "csqrt(0.0 + 4.0*I)", csqrt(0.0 + 4.0*I));
    print_double_complex_result("T327.5", "csqrt(1e200 + 1e200*I)", csqrt(1e200 + 1e200*I));
}
#endif


#ifdef RUN_T328
static void test_T328(void) {
    print_double_complex_result("T328.1", "csin(1.0 + 0.0*I)", csin(1.0 + 0.0*I));
    print_double_complex_result("T328.2", "csin(0.0 + 1.0*I)", csin(0.0 + 1.0*I));
    print_double_complex_result("T328.3", "csin(1.0 + 1.0*I)", csin(1.0 + 1.0*I));
    print_double_complex_result("T328.4", "csin(INFINITY + 1.0*I)", csin(INFINITY + 1.0*I));
    print_double_complex_result("T328.5", "csin(NAN + 1.0*I)", csin(NAN + 1.0*I));
}
#endif


#ifdef RUN_T329
static void test_T329(void) {
    print_double_complex_result("T329.1", "ccos(0.0 + 0.0*I)", ccos(0.0 + 0.0*I));
    print_double_complex_result("T329.2", "ccos(0.0 + 1.0*I)", ccos(0.0 + 1.0*I));
    print_double_complex_result("T329.3", "ccos(1.0 + 1.0*I)", ccos(1.0 + 1.0*I));
    print_double_complex_result("T329.4", "ccos(INFINITY + 1.0*I)", ccos(INFINITY + 1.0*I));
}
#endif


#ifdef RUN_T330
static void test_T330(void) {
    print_double_complex_result("T330.1", "ctan(0.0 + 0.0*I)", ctan(0.0 + 0.0*I));
    print_double_complex_result("T330.2", "ctan(1.0 + 1.0*I)", ctan(1.0 + 1.0*I));
    print_double_complex_result("T330.3", "ctan(0.0 + 100.0*I)", ctan(0.0 + 100.0*I));
}
#endif


#ifdef RUN_T331
static void test_T331(void) {
    print_double_complex_result("T331.1", "casin(0.5 + 0.5*I)", casin(0.5 + 0.5*I));
    print_double_complex_result("T331.2", "casin(2.0 + 0.0*I)", casin(2.0 + 0.0*I));
    print_double_complex_result("T331.3", "casin(0.0 + 0.0*I)", casin(0.0 + 0.0*I));
    print_double_complex_result("T331.4", "casin(INFINITY + 1.0*I)", casin(INFINITY + 1.0*I));
}
#endif


#ifdef RUN_T332
static void test_T332(void) {
    print_double_complex_result("T332.1", "cacos(0.5 + 0.5*I)", cacos(0.5 + 0.5*I));
    print_double_complex_result("T332.2", "cacos(2.0 + 0.0*I)", cacos(2.0 + 0.0*I));
    print_double_complex_result("T332.3", "cacos(INFINITY + 1.0*I)", cacos(INFINITY + 1.0*I));
}
#endif


#ifdef RUN_T333
static void test_T333(void) {
    print_double_complex_result("T333.1", "catan(0.0 + 0.0*I)", catan(0.0 + 0.0*I));
    print_double_complex_result("T333.2", "catan(0.0 + 2.0*I)", catan(0.0 + 2.0*I));
    print_double_complex_result("T333.3", "catan(1.0 + 1.0*I)", catan(1.0 + 1.0*I));
    print_double_complex_result("T333.4", "catan(INFINITY + 1.0*I)", catan(INFINITY + 1.0*I));
}
#endif


#ifdef RUN_T334
static void test_T334(void) {
    print_double_complex_result("T334.1", "csinh(1.0 + 0.0*I)", csinh(1.0 + 0.0*I));
    print_double_complex_result("T334.2", "csinh(0.0 + 1.0*I)", csinh(0.0 + 1.0*I));
    print_double_complex_result("T334.3", "csinh(1.0 + 1.0*I)", csinh(1.0 + 1.0*I));
    print_double_complex_result("T334.4", "csinh(INFINITY + 1.0*I)", csinh(INFINITY + 1.0*I));
}
#endif


#ifdef RUN_T335
static void test_T335(void) {
    print_double_complex_result("T335.1", "ccosh(0.0 + 0.0*I)", ccosh(0.0 + 0.0*I));
    print_double_complex_result("T335.2", "ccosh(1.0 + 0.0*I)", ccosh(1.0 + 0.0*I));
    print_double_complex_result("T335.3", "ccosh(0.0 + 1.0*I)", ccosh(0.0 + 1.0*I));
    print_double_complex_result("T335.4", "ccosh(INFINITY + 1.0*I)", ccosh(INFINITY + 1.0*I));
}
#endif


#ifdef RUN_T336
static void test_T336(void) {
    print_double_complex_result("T336.1", "ctanh(0.0 + 0.0*I)", ctanh(0.0 + 0.0*I));
    print_double_complex_result("T336.2", "ctanh(1.0 + 1.0*I)", ctanh(1.0 + 1.0*I));
    print_double_complex_result("T336.3", "ctanh(0.0 + 100.0*I)", ctanh(0.0 + 100.0*I));
    print_double_complex_result("T336.4", "ctanh(INFINITY + 1.0*I)", ctanh(INFINITY + 1.0*I));
}
#endif


#ifdef RUN_T337
static void test_T337(void) {
    print_double_complex_result("T337.1", "casinh(0.0 + 0.0*I)", casinh(0.0 + 0.0*I));
    print_double_complex_result("T337.2", "casinh(1.0 + 1.0*I)", casinh(1.0 + 1.0*I));
    print_double_complex_result("T337.3", "casinh(INFINITY + 1.0*I)", casinh(INFINITY + 1.0*I));
    print_double_complex_result("T337.4", "casinh(0.0 + 2.0*I)", casinh(0.0 + 2.0*I));
}
#endif


#ifdef RUN_T338
static void test_T338(void) {
    print_double_complex_result("T338.1", "cacosh(1.0 + 0.0*I)", cacosh(1.0 + 0.0*I));
    print_double_complex_result("T338.2", "cacosh(2.0 + 0.0*I)", cacosh(2.0 + 0.0*I));
    print_double_complex_result("T338.3", "cacosh(-2.0 + 0.0*I)", cacosh(-2.0 + 0.0*I));
    print_double_complex_result("T338.4", "cacosh(INFINITY + 1.0*I)", cacosh(INFINITY + 1.0*I));
}
#endif


#ifdef RUN_T339
static void test_T339(void) {
    print_double_complex_result("T339.1", "catanh(0.0 + 0.0*I)", catanh(0.0 + 0.0*I));
    print_double_complex_result("T339.2", "catanh(1.0 + 0.0*I)", catanh(1.0 + 0.0*I));
    print_double_complex_result("T339.3", "catanh(-1.0 + 0.0*I)", catanh(-1.0 + 0.0*I));
    print_double_complex_result("T339.4", "catanh(1.0 + 1.0*I)", catanh(1.0 + 1.0*I));
    print_double_complex_result("T339.5", "catanh(INFINITY + 1.0*I)", catanh(INFINITY + 1.0*I));
}
#endif


#ifdef RUN_T340
static void test_T340(void) {
    print_float_result("T340.1", "cabsf(1.0f + 1.0f*I)", cabsf(1.0f + 1.0f * I));
    print_float_result("T340.2", "cabsf(1e20f + 1e20f*I)", cabsf(1e20f + 1e20f * I));
    print_float_result("T340.3", "cargf(1.0f + 1.0f*I)", cargf(1.0f + 1.0f * I));
    print_float_result("T340.4", "cargf(-1.0f + 0.0f*I)", cargf(-1.0f + 0.0f * I));
    print_float_complex_result("T340.5", "conjf(1.0f + 2.0f*I)", conjf(1.0f + 2.0f * I));
}
#endif


#ifdef RUN_T341
static void test_T341(void) {
    print_float_complex_result("T341.1", "cexpf(0.0f + 0.0f*I)", cexpf(0.0f + 0.0f*I));
    print_float_complex_result("T341.2", "cexpf(1.0f + (float)M_PI*I)", cexpf(1.0f + (float)M_PI*I));
    print_float_complex_result("T341.3", "cexpf(200.0f + 1.0f*I)", cexpf(200.0f + 1.0f*I));
    print_float_complex_result("T341.4", "cexpf(0.0f + INFINITY*I)", cexpf(0.0f + INFINITY*I));
}
#endif


#ifdef RUN_T342
static void test_T342(void) {
    print_float_complex_result("T342.1", "clogf(1.0f + 0.0f*I)", clogf(1.0f + 0.0f*I));
    print_float_complex_result("T342.2", "clogf(-1.0f + 0.0f*I)", clogf(-1.0f + 0.0f*I));
    print_float_complex_result("T342.3", "clogf(1.0f + 1.0f*I)", clogf(1.0f + 1.0f*I));
    print_float_complex_result("T342.4", "clogf(INFINITY + 1.0f*I)", clogf(INFINITY + 1.0f*I));
}
#endif


#ifdef RUN_T343
static void test_T343(void) {
    print_float_complex_result("T343.1", "csqrtf(4.0f + 0.0f*I)", csqrtf(4.0f + 0.0f*I));
    print_float_complex_result("T343.2", "csqrtf(-4.0f + 0.0f*I)", csqrtf(-4.0f + 0.0f*I));
    print_float_complex_result("T343.3", "csqrtf(0.0f + 4.0f*I)", csqrtf(0.0f + 4.0f*I));
}
#endif


#ifdef RUN_T344
static void test_T344(void) {
    print_float_complex_result("T344.1", "cpowf(2.0f + 0.0f*I, 3.0f + 0.0f*I)", cpowf(2.0f + 0.0f*I, 3.0f + 0.0f*I));
    print_float_complex_result("T344.2", "cprojf(1.0f + 2.0f*I)", cprojf(1.0f + 2.0f*I));
    print_float_complex_result("T344.3", "cprojf(INFINITY + 1.0f*I)", cprojf(INFINITY + 1.0f*I));
}
#endif


#ifdef RUN_T345
static void test_T345(void) {
    print_float_complex_result("T345.1", "csinf(1.0f + 0.0f*I)", csinf(1.0f + 0.0f*I));
    print_float_complex_result("T345.2", "csinf(0.0f + 1.0f*I)", csinf(0.0f + 1.0f*I));
    print_float_complex_result("T345.3", "ccosf(0.0f + 0.0f*I)", ccosf(0.0f + 0.0f*I));
    print_float_complex_result("T345.4", "ctanf(0.0f + 100.0f*I)", ctanf(0.0f + 100.0f*I));
}
#endif


#ifdef RUN_T346
static void test_T346(void) {
    print_float_complex_result("T346.1", "casinf(0.5f + 0.5f*I)", casinf(0.5f + 0.5f*I));
    print_float_complex_result("T346.2", "cacosf(0.5f + 0.5f*I)", cacosf(0.5f + 0.5f*I));
    print_float_complex_result("T346.3", "catanf(0.0f + 2.0f*I)", catanf(0.0f + 2.0f*I));
}
#endif


#ifdef RUN_T347
static void test_T347(void) {
    print_float_complex_result("T347.1", "csinhf(1.0f + 1.0f*I)", csinhf(1.0f + 1.0f*I));
    print_float_complex_result("T347.2", "ccoshf(0.0f + 0.0f*I)", ccoshf(0.0f + 0.0f*I));
    print_float_complex_result("T347.3", "ctanhf(0.0f + 100.0f*I)", ctanhf(0.0f + 100.0f*I));
}
#endif


#ifdef RUN_T348
static void test_T348(void) {
    print_float_complex_result("T348.1", "casinhf(1.0f + 1.0f*I)", casinhf(1.0f + 1.0f*I));
    print_float_complex_result("T348.2", "cacoshf(2.0f + 0.0f*I)", cacoshf(2.0f + 0.0f*I));
    print_float_complex_result("T348.3", "catanhf(1.0f + 1.0f*I)", catanhf(1.0f + 1.0f*I));
}
#endif


#ifdef RUN_T349
static void test_T349(void) {
    print_float_result("T349.1", "sinf(0.5f)", sinf(0.5f));
    print_float_result("T349.2", "cosf(0.3f)", cosf(0.3f));
    print_float_result("T349.3", "tanf(0.7f)", tanf(0.7f));
}
#endif


#ifdef RUN_T350
static void test_T350(void) {
    print_float_result("T350.1", "sinf(1.2f)", sinf(1.2f));
    print_float_result("T350.2", "cosf(1.5f)", cosf(1.5f));
    print_float_result("T350.3", "tanf(2.0f)", tanf(2.0f));
}
#endif


#ifdef RUN_T351
static void test_T351(void) {
    print_float_result("T351.1", "sinf(-1.2f)", sinf(-1.2f));
    print_float_result("T351.2", "cosf(-1.5f)", cosf(-1.5f));
    print_float_result("T351.3", "tanf(-2.0f)", tanf(-2.0f));
}
#endif


#ifdef RUN_T352
static void test_T352(void) {
    print_float_result("T352.1", "sinf(100.0f)", sinf(100.0f));
    print_float_result("T352.2", "cosf(200.0f)", cosf(200.0f));
    print_float_result("T352.3", "tanf(300.0f)", tanf(300.0f));
}
#endif


#ifdef RUN_T353
static void test_T353(void) {
    print_float_result("T353.1", "sinf(1e10f)", sinf(1e10f));
    print_float_result("T353.2", "cosf(1e20f)", cosf(1e20f));
    print_float_result("T353.3", "tanf(1e30f)", tanf(1e30f));
    print_float_result("T353.4", "sinf(NAN)", sinf(NAN));
}
#endif


#ifdef RUN_T354
static void test_T354(void) {
    print_double_result("T354.1", "sin(0.5)", sin(0.5));
    print_double_result("T354.2", "cos(0.3)", cos(0.3));
    print_double_result("T354.3", "tan(0.7)", tan(0.7));
}
#endif


#ifdef RUN_T355
static void test_T355(void) {
    print_double_result("T355.1", "sin(1.2)", sin(1.2));
    print_double_result("T355.2", "cos(1.5)", cos(1.5));
    print_double_result("T355.3", "tan(2.0)", tan(2.0));
}
#endif


#ifdef RUN_T356
static void test_T356(void) {
    print_double_result("T356.1", "sin(-1.2)", sin(-1.2));
    print_double_result("T356.2", "cos(-1.5)", cos(-1.5));
    print_double_result("T356.3", "tan(-2.0)", tan(-2.0));
}
#endif


#ifdef RUN_T357
static void test_T357(void) {
    print_double_result("T357.1", "sin(1e6)", sin(1e6));
    print_double_result("T357.2", "cos(1e8)", cos(1e8));
    print_double_result("T357.3", "tan(1e10)", tan(1e10));
}
#endif


#ifdef RUN_T358
static void test_T358(void) {
    print_double_result("T358.1", "sin(1e100)", sin(1e100));
    print_double_result("T358.2", "cos(INFINITY)", cos(INFINITY));
    print_double_result("T358.3", "sin(NAN)", sin(NAN));
}
#endif


#ifdef RUN_T359
static void test_T359(void) {
    print_double_result("T359.1", "pow(5e-324, 0.5)", pow(5e-324, 0.5));
    print_double_result("T359.2", "pow(1e-310, 2.0)", pow(1e-310, 2.0));
    print_double_result("T359.3", "pow(1e-310, -1.0)", pow(1e-310, -1.0));
}
#endif


#ifdef RUN_T360
static void test_T360(void) {
    print_double_result("T360.1", "pow(1.2, 3.0)", pow(1.2, 3.0));
    print_double_result("T360.2", "pow(1.5, 3.0)", pow(1.5, 3.0));
    print_double_result("T360.3", "pow(1.8, 3.0)", pow(1.8, 3.0));
}
#endif


#ifdef RUN_T361
static void test_T361(void) {
    print_double_result("T361.1", "pow(2.0, 1024.0)", pow(2.0, 1024.0));
    print_double_result("T361.2", "pow(2.0, -1075.0)", pow(2.0, -1075.0));
    print_double_result("T361.3", "pow(0.5, -1024.0)", pow(0.5, -1024.0));
    print_double_result("T361.4", "pow(0.5, 1075.0)", pow(0.5, 1075.0));
}
#endif


#ifdef RUN_T362
static void test_T362(void) {
    print_double_result("T362.1", "pow(NAN, 1.0)", pow(NAN, 1.0));
    print_double_result("T362.2", "pow(1.0, NAN)", pow(1.0, NAN));
    print_double_result("T362.3", "pow(NAN, NAN)", pow(NAN, NAN));
    print_double_result("T362.4", "pow(1.0, 0.0)", pow(1.0, 0.0));
}
#endif


#ifdef RUN_T363
static void test_T363(void) {
    print_double_result("T363.1", "pow(3.0, 2.0)", pow(3.0, 2.0));
    print_double_result("T363.2", "pow(4.0, 0.5)", pow(4.0, 0.5));
    print_double_result("T363.3", "pow(2.0, -1.0)", pow(2.0, -1.0));
    print_double_result("T363.4", "pow(-4.0, 0.5)", pow(-4.0, 0.5));
}
#endif


#ifdef RUN_T364
static void test_T364(void) {
    print_double_result("T364.1", "pow(-2.0, 3.0)", pow(-2.0, 3.0));
    print_double_result("T364.2", "pow(-2.0, 4.0)", pow(-2.0, 4.0));
    print_double_result("T364.3", "pow(-2.0, 0.5)", pow(-2.0, 0.5));
    print_double_result("T364.4", "pow(-1.0, 0.5)", pow(-1.0, 0.5));
}
#endif


#ifdef RUN_T365
static void test_T365(void) {
    print_double_result("T365.1", "pow(0.9999999, 1e15)", pow(0.9999999, 1e15));
    print_double_result("T365.2", "pow(1.0000001, 1e15)", pow(1.0000001, 1e15));
    print_double_result("T365.3", "pow(0.5, 1e15)", pow(0.5, 1e15));
    print_double_result("T365.4", "pow(2.0, 1e15)", pow(2.0, 1e15));
}
#endif


#ifdef RUN_T366
static void test_T366(void) {
    print_float_result("T366.1", "powf(1e-40f, 0.5f)", powf(1e-40f, 0.5f));
    print_float_result("T366.2", "powf(1e-45f, 2.0f)", powf(1e-45f, 2.0f));
}
#endif


#ifdef RUN_T367
static void test_T367(void) {
    print_float_result("T367.1", "powf(2.0f, 128.0f)", powf(2.0f, 128.0f));
    print_float_result("T367.2", "powf(2.0f, -150.0f)", powf(2.0f, -150.0f));
    print_float_result("T367.3", "powf(0.5f, -128.0f)", powf(0.5f, -128.0f));
    print_float_result("T367.4", "powf(0.5f, 150.0f)", powf(0.5f, 150.0f));
}
#endif


#ifdef RUN_T368
static void test_T368(void) {
    print_float_result("T368.1", "powf(1.2f, 3.0f)", powf(1.2f, 3.0f));
    print_float_result("T368.2", "powf(1.5f, 3.0f)", powf(1.5f, 3.0f));
    print_float_result("T368.3", "powf(1.8f, 3.0f)", powf(1.8f, 3.0f));
}
#endif


#ifdef RUN_T369
static void test_T369(void) {
    double value;
    signgam = 0;
    value = lgamma(-0.5);
    print_double_result("T369.1", "lgamma(-0.5)", value);
    print_int_result("T369.1.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(-1.5);
    print_double_result("T369.2", "lgamma(-1.5)", value);
    print_int_result("T369.2.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(-2.5);
    print_double_result("T369.3", "lgamma(-2.5)", value);
    print_int_result("T369.3.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(-3.5);
    print_double_result("T369.4", "lgamma(-3.5)", value);
    print_int_result("T369.4.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(-100.5);
    print_double_result("T369.5", "lgamma(-100.5)", value);
    print_int_result("T369.5.signgam", "signgam", signgam);
}
#endif


#ifdef RUN_T370
static void test_T370(void) {
    double value;
    signgam = 0;
    value = lgamma(0.5);
    print_double_result("T370.1", "lgamma(0.5)", value);
    print_int_result("T370.1.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(0.8);
    print_double_result("T370.2", "lgamma(0.8)", value);
    print_int_result("T370.2.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(1.2);
    print_double_result("T370.3", "lgamma(1.2)", value);
    print_int_result("T370.3.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(1.5);
    print_double_result("T370.4", "lgamma(1.5)", value);
    print_int_result("T370.4.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(1.8);
    print_double_result("T370.5", "lgamma(1.8)", value);
    print_int_result("T370.5.signgam", "signgam", signgam);
}
#endif


#ifdef RUN_T371
static void test_T371(void) {
    double value;
    signgam = 0;
    value = lgamma(3.5);
    print_double_result("T371.1", "lgamma(3.5)", value);
    print_int_result("T371.1.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(4.5);
    print_double_result("T371.2", "lgamma(4.5)", value);
    print_int_result("T371.2.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(5.5);
    print_double_result("T371.3", "lgamma(5.5)", value);
    print_int_result("T371.3.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(6.5);
    print_double_result("T371.4", "lgamma(6.5)", value);
    print_int_result("T371.4.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(7.5);
    print_double_result("T371.5", "lgamma(7.5)", value);
    print_int_result("T371.5.signgam", "signgam", signgam);
}
#endif


#ifdef RUN_T372
static void test_T372(void) {
    double value;
    signgam = 0;
    value = lgamma(10.0);
    print_double_result("T372.1", "lgamma(10.0)", value);
    print_int_result("T372.1.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(100.0);
    print_double_result("T372.2", "lgamma(100.0)", value);
    print_int_result("T372.2.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(1e18);
    print_double_result("T372.3", "lgamma(1e18)", value);
    print_int_result("T372.3.signgam", "signgam", signgam);
}
#endif


#ifdef RUN_T373
static void test_T373(void) {
    double value;
    signgam = 0;
    value = lgamma(0.0);
    print_double_result("T373.1", "lgamma(0.0)", value);
    print_int_result("T373.1.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(INFINITY);
    print_double_result("T373.2", "lgamma(INFINITY)", value);
    print_int_result("T373.2.signgam", "signgam", signgam);
    signgam = 0;
    value = lgamma(-1e-30);
    print_double_result("T373.3", "lgamma(-1e-30)", value);
    print_int_result("T373.3.signgam", "signgam", signgam);
}
#endif


#ifdef RUN_T374
static void test_T374(void) {
    float value;
    signgam = 0;
    value = lgammaf(-0.5f);
    print_float_result("T374.1", "lgammaf(-0.5f)", value);
    print_int_result("T374.1.signgam", "signgam", signgam);
    signgam = 0;
    value = lgammaf(-1.5f);
    print_float_result("T374.2", "lgammaf(-1.5f)", value);
    print_int_result("T374.2.signgam", "signgam", signgam);
    signgam = 0;
    value = lgammaf(-2.5f);
    print_float_result("T374.3", "lgammaf(-2.5f)", value);
    print_int_result("T374.3.signgam", "signgam", signgam);
    signgam = 0;
    value = lgammaf(-3.5f);
    print_float_result("T374.4", "lgammaf(-3.5f)", value);
    print_int_result("T374.4.signgam", "signgam", signgam);
}
#endif


#ifdef RUN_T375
static void test_T375(void) {
    float value;
    signgam = 0;
    value = lgammaf(0.5f);
    print_float_result("T375.1", "lgammaf(0.5f)", value);
    print_int_result("T375.1.signgam", "signgam", signgam);
    signgam = 0;
    value = lgammaf(1.5f);
    print_float_result("T375.2", "lgammaf(1.5f)", value);
    print_int_result("T375.2.signgam", "signgam", signgam);
    signgam = 0;
    value = lgammaf(3.5f);
    print_float_result("T375.3", "lgammaf(3.5f)", value);
    print_int_result("T375.3.signgam", "signgam", signgam);
    signgam = 0;
    value = lgammaf(5.5f);
    print_float_result("T375.4", "lgammaf(5.5f)", value);
    print_int_result("T375.4.signgam", "signgam", signgam);
    signgam = 0;
    value = lgammaf(7.5f);
    print_float_result("T375.5", "lgammaf(7.5f)", value);
    print_int_result("T375.5.signgam", "signgam", signgam);
}
#endif


#ifdef RUN_T376
static void test_T376(void) {
    float value;
    signgam = 0;
    value = lgammaf(10.0f);
    print_float_result("T376.1", "lgammaf(10.0f)", value);
    print_int_result("T376.1.signgam", "signgam", signgam);
    signgam = 0;
    value = lgammaf(100.0f);
    print_float_result("T376.2", "lgammaf(100.0f)", value);
    print_int_result("T376.2.signgam", "signgam", signgam);
    signgam = 0;
    value = lgammaf(1e15f);
    print_float_result("T376.3", "lgammaf(1e15f)", value);
    print_int_result("T376.3.signgam", "signgam", signgam);
}
#endif


#ifdef RUN_T377
static void test_T377(void) {
    print_double_result("T377.1", "fmod(5e-324, 1e-310)", fmod(5e-324, 1e-310));
    print_double_result("T377.2", "fmod(1e-310, 5e-324)", fmod(1e-310, 5e-324));
    print_double_result("T377.3", "fmod(5e-324, 5e-324)", fmod(5e-324, 5e-324));
}
#endif


#ifdef RUN_T378
static void test_T378(void) {
    print_double_result("T378.1", "fmod(2.0, 2.0)", fmod(2.0, 2.0));
    print_double_result("T378.2", "fmod(1.0, 2.0)", fmod(1.0, 2.0));
    print_double_result("T378.3", "fmod(4.0, 2.0)", fmod(4.0, 2.0));
    print_double_result("T378.4", "fmod(-2.0, 2.0)", fmod(-2.0, 2.0));
}
#endif


#ifdef RUN_T379
static void test_T379(void) {
    print_float_result("T379.1", "fmodf(1e-45f, 1e-40f)", fmodf(1e-45f, 1e-40f));
    print_float_result("T379.2", "fmodf(1e-40f, 1e-45f)", fmodf(1e-40f, 1e-45f));
    print_float_result("T379.3", "fmodf(1e-45f, 1e-45f)", fmodf(1e-45f, 1e-45f));
}
#endif


#ifdef RUN_T380
static void test_T380(void) {
    print_float_result("T380.1", "fmodf(2.0f, 2.0f)", fmodf(2.0f, 2.0f));
    print_float_result("T380.2", "fmodf(1.0f, 3.0f)", fmodf(1.0f, 3.0f));
    print_float_result("T380.3", "fmodf(4.0f, 2.0f)", fmodf(4.0f, 2.0f));
}
#endif


#ifdef RUN_T381
static void test_T381(void) {
    double value;
    int q = 0;
    value = remquo(NAN, 1.0, &q);
    print_double_result("T381.1", "remquo(NAN, 1.0, &q)", value);
    print_int_result("T381.1.quo", "q", q);
    q = 0;
    value = remquo(INFINITY, 1.0, &q);
    print_double_result("T381.2", "remquo(INFINITY, 1.0, &q)", value);
    print_int_result("T381.2.quo", "q", q);
    q = 0;
    value = remquo(1.0, 0.0, &q);
    print_double_result("T381.3", "remquo(1.0, 0.0, &q)", value);
    print_int_result("T381.3.quo", "q", q);
    q = 0;
    value = remquo(7.0, 2.0, &q);
    print_double_result("T381.4", "remquo(7.0, 2.0, &q)", value);
    print_int_result("T381.4.quo", "q", q);
    q = 0;
    value = remquo(5.0, 2.0, &q);
    print_double_result("T381.5", "remquo(5.0, 2.0, &q)", value);
    print_int_result("T381.5.quo", "q", q);
    q = 0;
    value = remquo(-3.0, 2.0, &q);
    print_double_result("T381.6", "remquo(-3.0, 2.0, &q)", value);
    print_int_result("T381.6.quo", "q", q);
    q = 0;
    value = remquo(1e-310, 5e-324, &q);
    print_double_result("T381.7", "remquo(1e-310, 5e-324, &q)", value);
    print_int_result("T381.7.quo", "q", q);
}
#endif


#ifdef RUN_T382
static void test_T382(void) {
    float value;
    int q = 0;
    value = remquof(NAN, 1.0f, &q);
    print_float_result("T382.1", "remquof(NAN, 1.0f, &q)", value);
    print_int_result("T382.1.quo", "q", q);
    q = 0;
    value = remquof(INFINITY, 1.0f, &q);
    print_float_result("T382.2", "remquof(INFINITY, 1.0f, &q)", value);
    print_int_result("T382.2.quo", "q", q);
    q = 0;
    value = remquof(1.0f, 0.0f, &q);
    print_float_result("T382.3", "remquof(1.0f, 0.0f, &q)", value);
    print_int_result("T382.3.quo", "q", q);
    q = 0;
    value = remquof(7.0f, 2.0f, &q);
    print_float_result("T382.4", "remquof(7.0f, 2.0f, &q)", value);
    print_int_result("T382.4.quo", "q", q);
    q = 0;
    value = remquof(5.0f, 2.0f, &q);
    print_float_result("T382.5", "remquof(5.0f, 2.0f, &q)", value);
    print_int_result("T382.5.quo", "q", q);
    q = 0;
    value = remquof(-3.0f, 2.0f, &q);
    print_float_result("T382.6", "remquof(-3.0f, 2.0f, &q)", value);
    print_int_result("T382.6.quo", "q", q);
}
#endif


#ifdef RUN_T383
static void test_T383(void) {
    print_double_result("T383.1", "remainder(NAN, 1.0)", remainder(NAN, 1.0));
    print_double_result("T383.2", "remainder(INFINITY, 1.0)", remainder(INFINITY, 1.0));
    print_double_result("T383.3", "remainder(1.0, 0.0)", remainder(1.0, 0.0));
    print_double_result("T383.4", "remainder(3.7, 2.0)", remainder(3.7, 2.0));
    print_double_result("T383.5", "remainder(-3.7, 2.0)", remainder(-3.7, 2.0));
    print_double_result("T383.6", "remainder(2.0, 2.0)", remainder(2.0, 2.0));
    print_double_result("T383.7", "remainder(1e-310, 5e-324)", remainder(1e-310, 5e-324));
}
#endif


#ifdef RUN_T384
static void test_T384(void) {
    print_float_result("T384.1", "remainderf(NAN, 1.0f)", remainderf(NAN, 1.0f));
    print_float_result("T384.2", "remainderf(INFINITY, 1.0f)", remainderf(INFINITY, 1.0f));
    print_float_result("T384.3", "remainderf(1.0f, 0.0f)", remainderf(1.0f, 0.0f));
    print_float_result("T384.4", "remainderf(3.7f, 2.0f)", remainderf(3.7f, 2.0f));
    print_float_result("T384.5", "remainderf(-3.7f, 2.0f)", remainderf(-3.7f, 2.0f));
    print_float_result("T384.6", "remainderf(1e-40f, 1e-45f)", remainderf(1e-40f, 1e-45f));
}
#endif


#ifdef RUN_T385
static void test_T385(void) {
    print_double_result("T385.1", "ceil(0.3)", ceil(0.3));
    print_double_result("T385.2", "ceil(-0.3)", ceil(-0.3));
    print_double_result("T385.3", "ceil(0.0)", ceil(0.0));
    print_double_result("T385.4", "ceil(1.5)", ceil(1.5));
    print_double_result("T385.5", "ceil(-1.5)", ceil(-1.5));
    print_double_result("T385.6", "ceil(1e16)", ceil(1e16));
    print_double_result("T385.7", "ceil(INFINITY)", ceil(INFINITY));
    print_double_result("T385.8", "ceil(NAN)", ceil(NAN));
}
#endif


#ifdef RUN_T386
static void test_T386(void) {
    print_float_result("T386.1", "ceilf(0.3f)", ceilf(0.3f));
    print_float_result("T386.2", "ceilf(-0.3f)", ceilf(-0.3f));
    print_float_result("T386.3", "ceilf(0.0f)", ceilf(0.0f));
    print_float_result("T386.4", "ceilf(1.5f)", ceilf(1.5f));
    print_float_result("T386.5", "ceilf(1e8f)", ceilf(1e8f));
    print_float_result("T386.6", "ceilf(INFINITY)", ceilf(INFINITY));
}
#endif


#ifdef RUN_T387
static void test_T387(void) {
    print_double_result("T387.1", "floor(0.7)", floor(0.7));
    print_double_result("T387.2", "floor(-0.7)", floor(-0.7));
    print_double_result("T387.3", "floor(0.0)", floor(0.0));
    print_double_result("T387.4", "floor(1.5)", floor(1.5));
    print_double_result("T387.5", "floor(-1.5)", floor(-1.5));
    print_double_result("T387.6", "floor(1e16)", floor(1e16));
    print_double_result("T387.7", "floor(INFINITY)", floor(INFINITY));
    print_double_result("T387.8", "floor(NAN)", floor(NAN));
}
#endif


#ifdef RUN_T388
static void test_T388(void) {
    print_float_result("T388.1", "floorf(0.7f)", floorf(0.7f));
    print_float_result("T388.2", "floorf(-0.7f)", floorf(-0.7f));
    print_float_result("T388.3", "floorf(0.0f)", floorf(0.0f));
    print_float_result("T388.4", "floorf(1.5f)", floorf(1.5f));
    print_float_result("T388.5", "floorf(1e8f)", floorf(1e8f));
    print_float_result("T388.6", "floorf(INFINITY)", floorf(INFINITY));
}
#endif


#ifdef RUN_T389
static void test_T389(void) {
    print_double_result("T389.1", "round(0.3)", round(0.3));
    print_double_result("T389.2", "round(-0.3)", round(-0.3));
    print_double_result("T389.3", "round(0.5)", round(0.5));
    print_double_result("T389.4", "round(-0.5)", round(-0.5));
    print_double_result("T389.5", "round(1.5)", round(1.5));
    print_double_result("T389.6", "round(1e16)", round(1e16));
    print_double_result("T389.7", "round(INFINITY)", round(INFINITY));
}
#endif


#ifdef RUN_T390
static void test_T390(void) {
    print_float_result("T390.1", "roundf(0.3f)", roundf(0.3f));
    print_float_result("T390.2", "roundf(-0.3f)", roundf(-0.3f));
    print_float_result("T390.3", "roundf(0.5f)", roundf(0.5f));
    print_float_result("T390.4", "roundf(-0.5f)", roundf(-0.5f));
    print_float_result("T390.5", "roundf(1.5f)", roundf(1.5f));
    print_float_result("T390.6", "roundf(INFINITY)", roundf(INFINITY));
}
#endif


#ifdef RUN_T391
static void test_T391(void) {
    print_double_result("T391.1", "trunc(0.7)", trunc(0.7));
    print_double_result("T391.2", "trunc(-0.7)", trunc(-0.7));
    print_double_result("T391.3", "trunc(1.5)", trunc(1.5));
    print_double_result("T391.4", "trunc(-1.5)", trunc(-1.5));
    print_double_result("T391.5", "trunc(1e16)", trunc(1e16));
    print_double_result("T391.6", "trunc(INFINITY)", trunc(INFINITY));
}
#endif


#ifdef RUN_T392
static void test_T392(void) {
    print_float_result("T392.1", "truncf(0.7f)", truncf(0.7f));
    print_float_result("T392.2", "truncf(-0.7f)", truncf(-0.7f));
    print_float_result("T392.3", "truncf(1.5f)", truncf(1.5f));
    print_float_result("T392.4", "truncf(1e8f)", truncf(1e8f));
    print_float_result("T392.5", "truncf(INFINITY)", truncf(INFINITY));
}
#endif


#ifdef RUN_T393
static void test_T393(void) {
    print_double_result("T393.1", "rint(0.3)", rint(0.3));
    print_double_result("T393.2", "rint(-0.3)", rint(-0.3));
    print_double_result("T393.3", "rint(0.5)", rint(0.5));
    print_double_result("T393.4", "rint(-0.5)", rint(-0.5));
    print_double_result("T393.5", "rint(1.5)", rint(1.5));
    print_double_result("T393.6", "rint(1e16)", rint(1e16));
    print_double_result("T393.7", "rint(0.0)", rint(0.0));
    print_double_result("T393.8", "rint(INFINITY)", rint(INFINITY));
}
#endif


#ifdef RUN_T394
static void test_T394(void) {
    print_float_result("T394.1", "rintf(0.3f)", rintf(0.3f));
    print_float_result("T394.2", "rintf(-0.3f)", rintf(-0.3f));
    print_float_result("T394.3", "rintf(0.5f)", rintf(0.5f));
    print_float_result("T394.4", "rintf(-0.5f)", rintf(-0.5f));
    print_float_result("T394.5", "rintf(1.5f)", rintf(1.5f));
    print_float_result("T394.6", "rintf(0.0f)", rintf(0.0f));
    print_float_result("T394.7", "rintf(INFINITY)", rintf(INFINITY));
}
#endif


#ifdef RUN_T395
static void test_T395(void) {
    print_double_result("T395.1", "expm1(0.0)", expm1(0.0));
    print_double_result("T395.2", "expm1(0.3)", expm1(0.3));
    print_double_result("T395.3", "expm1(-0.3)", expm1(-0.3));
    print_double_result("T395.4", "expm1(0.4)", expm1(0.4));
    print_double_result("T395.5", "expm1(-0.4)", expm1(-0.4));
    print_double_result("T395.6", "expm1(710.0)", expm1(710.0));
    print_double_result("T395.7", "expm1(-40.0)", expm1(-40.0));
    print_double_result("T395.8", "expm1(NAN)", expm1(NAN));
    print_double_result("T395.9", "expm1(INFINITY)", expm1(INFINITY));
    print_double_result("T395.10", "expm1(-INFINITY)", expm1(-INFINITY));
    print_double_result("T395.11", "expm1(1e-20)", expm1(1e-20));
}
#endif


#ifdef RUN_T396
static void test_T396(void) {
    print_float_result("T396.1", "expm1f(0.0f)", expm1f(0.0f));
    print_float_result("T396.2", "expm1f(0.3f)", expm1f(0.3f));
    print_float_result("T396.3", "expm1f(-0.3f)", expm1f(-0.3f));
    print_float_result("T396.4", "expm1f(90.0f)", expm1f(90.0f));
    print_float_result("T396.5", "expm1f(-20.0f)", expm1f(-20.0f));
    print_float_result("T396.6", "expm1f(NAN)", expm1f(NAN));
    print_float_result("T396.7", "expm1f(INFINITY)", expm1f(INFINITY));
    print_float_result("T396.8", "expm1f(-INFINITY)", expm1f(-INFINITY));
}
#endif


#ifdef RUN_T397
static void test_T397(void) {
    print_double_result("T397.1", "log1p(0.0)", log1p(0.0));
    print_double_result("T397.2", "log1p(1e-20)", log1p(1e-20));
    print_double_result("T397.3", "log1p(1e-60)", log1p(1e-60));
    print_double_result("T397.4", "log1p(-1.0)", log1p(-1.0));
    print_double_result("T397.5", "log1p(-0.5)", log1p(-0.5));
    print_double_result("T397.6", "log1p(0.3)", log1p(0.3));
    print_double_result("T397.7", "log1p(INFINITY)", log1p(INFINITY));
    print_double_result("T397.8", "log1p(NAN)", log1p(NAN));
    print_double_result("T397.9", "log1p(-2.0)", log1p(-2.0));
}
#endif


#ifdef RUN_T398
static void test_T398(void) {
    print_float_result("T398.1", "log1pf(0.0f)", log1pf(0.0f));
    print_float_result("T398.2", "log1pf(1e-10f)", log1pf(1e-10f));
    print_float_result("T398.3", "log1pf(-1.0f)", log1pf(-1.0f));
    print_float_result("T398.4", "log1pf(-0.5f)", log1pf(-0.5f));
    print_float_result("T398.5", "log1pf(0.3f)", log1pf(0.3f));
    print_float_result("T398.6", "log1pf(INFINITY)", log1pf(INFINITY));
    print_float_result("T398.7", "log1pf(NAN)", log1pf(NAN));
}
#endif


#ifdef RUN_T399
static void test_T399(void) {
    print_double_result("T399.1", "atan2(0.0, 1.0)", atan2(0.0, 1.0));
    print_double_result("T399.2", "atan2(0.0, -1.0)", atan2(0.0, -1.0));
    print_double_result("T399.3", "atan2(-0.0, 1.0)", atan2(-0.0, 1.0));
    print_double_result("T399.4", "atan2(-0.0, -1.0)", atan2(-0.0, -1.0));
    print_double_result("T399.5", "atan2(1.0, 0.0)", atan2(1.0, 0.0));
    print_double_result("T399.6", "atan2(-1.0, 0.0)", atan2(-1.0, 0.0));
    print_double_result("T399.7", "atan2(INFINITY, 1.0)", atan2(INFINITY, 1.0));
    print_double_result("T399.8", "atan2(INFINITY, INFINITY)", atan2(INFINITY, INFINITY));
    print_double_result("T399.9", "atan2(INFINITY, -INFINITY)", atan2(INFINITY, -INFINITY));
    print_double_result("T399.10", "atan2(-INFINITY, INFINITY)", atan2(-INFINITY, INFINITY));
    print_double_result("T399.11", "atan2(-INFINITY, -INFINITY)", atan2(-INFINITY, -INFINITY));
    print_double_result("T399.12", "atan2(1e300, 1e-300)", atan2(1e300, 1e-300));
    print_double_result("T399.13", "atan2(1e-300, 1e300)", atan2(1e-300, 1e300));
    print_double_result("T399.14", "atan2(NAN, 1.0)", atan2(NAN, 1.0));
}
#endif


#ifdef RUN_T400
static void test_T400(void) {
    print_double_result("T400.1", "jn(-2, 1.0)", jn(-2, 1.0));
    print_double_result("T400.2", "jn(0, 1.0)", jn(0, 1.0));
    print_double_result("T400.3", "jn(1, 1.0)", jn(1, 1.0));
    print_double_result("T400.4", "jn(2, 0.0)", jn(2, 0.0));
    print_double_result("T400.5", "jn(2, INFINITY)", jn(2, INFINITY));
    print_double_result("T400.6", "jn(2, NAN)", jn(2, NAN));
}
#endif


#ifdef RUN_T401
static void test_T401(void) {
    print_double_result("T401.1", "jn(2, 1e100)", jn(2, 1e100));
    print_double_result("T401.2", "jn(3, 1e100)", jn(3, 1e100));
    print_double_result("T401.3", "jn(4, 1e100)", jn(4, 1e100));
    print_double_result("T401.4", "jn(5, 1e100)", jn(5, 1e100));
    print_double_result("T401.5", "jn(50, 1.0)", jn(50, 1.0));
    print_double_result("T401.6", "jn(2, 10.0)", jn(2, 10.0));
    print_double_result("T401.7", "jn(-3, 2.0)", jn(-3, 2.0));
}
#endif


#ifdef RUN_T402
static void test_T402(void) {
    print_double_result("T402.1", "yn(-2, 1.0)", yn(-2, 1.0));
    print_double_result("T402.2", "yn(0, 1.0)", yn(0, 1.0));
    print_double_result("T402.3", "yn(1, 1.0)", yn(1, 1.0));
    print_double_result("T402.4", "yn(2, INFINITY)", yn(2, INFINITY));
    print_double_result("T402.5", "yn(2, 1e100)", yn(2, 1e100));
    print_double_result("T402.6", "yn(3, 1e100)", yn(3, 1e100));
    print_double_result("T402.7", "yn(-3, 2.0)", yn(-3, 2.0));
    print_double_result("T402.8", "yn(2, 0.0)", yn(2, 0.0));
    print_double_result("T402.9", "yn(2, -1.0)", yn(2, -1.0));
}
#endif


#ifdef RUN_T403
static void test_T403(void) {
    print_double_result("T403.1", "j0(0.0)", j0(0.0));
    print_double_result("T403.2", "j0(0.5)", j0(0.5));
    print_double_result("T403.3", "j0(2.5)", j0(2.5));
    print_double_result("T403.4", "j0(1e10)", j0(1e10));
    print_double_result("T403.5", "j0(1e100)", j0(1e100));
    print_double_result("T403.6", "j0(INFINITY)", j0(INFINITY));
    print_double_result("T403.7", "j0(NAN)", j0(NAN));
    print_double_result("T403.8", "j0(-1.0)", j0(-1.0));
}
#endif


#ifdef RUN_T404
static void test_T404(void) {
    print_double_result("T404.1", "j1(0.0)", j1(0.0));
    print_double_result("T404.2", "j1(0.5)", j1(0.5));
    print_double_result("T404.3", "j1(2.5)", j1(2.5));
    print_double_result("T404.4", "j1(1e10)", j1(1e10));
    print_double_result("T404.5", "j1(1e100)", j1(1e100));
    print_double_result("T404.6", "j1(INFINITY)", j1(INFINITY));
    print_double_result("T404.7", "j1(NAN)", j1(NAN));
    print_double_result("T404.8", "j1(-1.0)", j1(-1.0));
}
#endif


#ifdef RUN_T405
static void test_T405(void) {
    print_double_result("T405.1", "y0(0.5)", y0(0.5));
    print_double_result("T405.2", "y0(2.5)", y0(2.5));
    print_double_result("T405.3", "y0(1e10)", y0(1e10));
    print_double_result("T405.4", "y0(1e100)", y0(1e100));
    print_double_result("T405.5", "y0(INFINITY)", y0(INFINITY));
    print_double_result("T405.6", "y0(NAN)", y0(NAN));
    print_double_result("T405.7", "y0(0.0)", y0(0.0));
    print_double_result("T405.8", "y0(-1.0)", y0(-1.0));
    print_double_result("T405.9", "y0(1e-15)", y0(1e-15));
}
#endif


#ifdef RUN_T406
static void test_T406(void) {
    print_double_result("T406.1", "y1(0.5)", y1(0.5));
    print_double_result("T406.2", "y1(2.5)", y1(2.5));
    print_double_result("T406.3", "y1(1e10)", y1(1e10));
    print_double_result("T406.4", "y1(1e100)", y1(1e100));
    print_double_result("T406.5", "y1(INFINITY)", y1(INFINITY));
    print_double_result("T406.6", "y1(NAN)", y1(NAN));
    print_double_result("T406.7", "y1(0.0)", y1(0.0));
    print_double_result("T406.8", "y1(-1.0)", y1(-1.0));
    print_double_result("T406.9", "y1(1e-15)", y1(1e-15));
}
#endif


#ifdef RUN_T407
static void test_T407(void) {
    print_double_result("T407.1", "erf(0.0)", erf(0.0));
    print_double_result("T407.2", "erf(1e-300)", erf(1e-300));
    print_double_result("T407.3", "erf(1e-20)", erf(1e-20));
    print_double_result("T407.4", "erf(0.5)", erf(0.5));
    print_double_result("T407.5", "erf(0.84)", erf(0.84));
    print_double_result("T407.6", "erf(1.25)", erf(1.25));
    print_double_result("T407.7", "erf(3.0)", erf(3.0));
    print_double_result("T407.8", "erf(7.0)", erf(7.0));
    print_double_result("T407.9", "erf(-7.0)", erf(-7.0));
    print_double_result("T407.10", "erf(NAN)", erf(NAN));
    print_double_result("T407.11", "erf(INFINITY)", erf(INFINITY));
}
#endif


#ifdef RUN_T408
static void test_T408(void) {
    print_double_result("T408.1", "erfc(0.0)", erfc(0.0));
    print_double_result("T408.2", "erfc(0.5)", erfc(0.5));
    print_double_result("T408.3", "erfc(0.84)", erfc(0.84));
    print_double_result("T408.4", "erfc(1.25)", erfc(1.25));
    print_double_result("T408.5", "erfc(3.0)", erfc(3.0));
    print_double_result("T408.6", "erfc(7.0)", erfc(7.0));
    print_double_result("T408.7", "erfc(28.0)", erfc(28.0));
    print_double_result("T408.8", "erfc(-7.0)", erfc(-7.0));
    print_double_result("T408.9", "erfc(NAN)", erfc(NAN));
    print_double_result("T408.10", "erfc(INFINITY)", erfc(INFINITY));
    print_double_result("T408.11", "erfc(-28.0)", erfc(-28.0));
}
#endif


#ifdef RUN_T409
static void test_T409(void) {
    print_float_result("T409.1", "erff(0.0f)", erff(0.0f));
    print_float_result("T409.2", "erff(1e-20f)", erff(1e-20f));
    print_float_result("T409.3", "erff(1e-10f)", erff(1e-10f));
    print_float_result("T409.4", "erff(0.5f)", erff(0.5f));
    print_float_result("T409.5", "erff(0.84f)", erff(0.84f));
    print_float_result("T409.6", "erff(3.0f)", erff(3.0f));
    print_float_result("T409.7", "erff(5.0f)", erff(5.0f));
    print_float_result("T409.8", "erff(-5.0f)", erff(-5.0f));
    print_float_result("T409.9", "erff(NAN)", erff(NAN));
    print_float_result("T409.10", "erff(INFINITY)", erff(INFINITY));
}
#endif


#ifdef RUN_T410
static void test_T410(void) {
    print_float_result("T410.1", "erfcf(0.0f)", erfcf(0.0f));
    print_float_result("T410.2", "erfcf(0.5f)", erfcf(0.5f));
    print_float_result("T410.3", "erfcf(0.84f)", erfcf(0.84f));
    print_float_result("T410.4", "erfcf(3.0f)", erfcf(3.0f));
    print_float_result("T410.5", "erfcf(5.0f)", erfcf(5.0f));
    print_float_result("T410.6", "erfcf(10.0f)", erfcf(10.0f));
    print_float_result("T410.7", "erfcf(-10.0f)", erfcf(-10.0f));
    print_float_result("T410.8", "erfcf(NAN)", erfcf(NAN));
    print_float_result("T410.9", "erfcf(INFINITY)", erfcf(INFINITY));
    print_float_result("T410.10", "erfcf(-6.0f)", erfcf(-6.0f));
}
#endif


#ifdef RUN_T411
static void test_T411(void) {
    print_double_result("T411.1", "sinh(0.0)", sinh(0.0));
    print_double_result("T411.2", "sinh(1e-20)", sinh(1e-20));
    print_double_result("T411.3", "sinh(0.5)", sinh(0.5));
    print_double_result("T411.4", "sinh(10.0)", sinh(10.0));
    print_double_result("T411.5", "sinh(710.0)", sinh(710.0));
    print_double_result("T411.6", "sinh(800.0)", sinh(800.0));
    print_double_result("T411.7", "sinh(-800.0)", sinh(-800.0));
    print_double_result("T411.8", "sinh(NAN)", sinh(NAN));
    print_double_result("T411.9", "sinh(INFINITY)", sinh(INFINITY));
}
#endif


#ifdef RUN_T412
static void test_T412(void) {
    print_double_result("T412.1", "cosh(0.0)", cosh(0.0));
    print_double_result("T412.2", "cosh(1e-20)", cosh(1e-20));
    print_double_result("T412.3", "cosh(0.5)", cosh(0.5));
    print_double_result("T412.4", "cosh(10.0)", cosh(10.0));
    print_double_result("T412.5", "cosh(710.0)", cosh(710.0));
    print_double_result("T412.6", "cosh(800.0)", cosh(800.0));
    print_double_result("T412.7", "cosh(NAN)", cosh(NAN));
    print_double_result("T412.8", "cosh(INFINITY)", cosh(INFINITY));
}
#endif


#ifdef RUN_T413
static void test_T413(void) {
    print_double_result("T413.1", "tanh(0.0)", tanh(0.0));
    print_double_result("T413.2", "tanh(1e-20)", tanh(1e-20));
    print_double_result("T413.3", "tanh(0.5)", tanh(0.5));
    print_double_result("T413.4", "tanh(1.5)", tanh(1.5));
    print_double_result("T413.5", "tanh(30.0)", tanh(30.0));
    print_double_result("T413.6", "tanh(-30.0)", tanh(-30.0));
    print_double_result("T413.7", "tanh(NAN)", tanh(NAN));
    print_double_result("T413.8", "tanh(INFINITY)", tanh(INFINITY));
    print_double_result("T413.9", "tanh(-INFINITY)", tanh(-INFINITY));
}
#endif


#ifdef RUN_T414
static void test_T414(void) {
    print_float_result("T414.1", "sinhf(0.0f)", sinhf(0.0f));
    print_float_result("T414.2", "sinhf(1e-20f)", sinhf(1e-20f));
    print_float_result("T414.3", "sinhf(0.5f)", sinhf(0.5f));
    print_float_result("T414.4", "sinhf(10.0f)", sinhf(10.0f));
    print_float_result("T414.5", "sinhf(89.0f)", sinhf(89.0f));
    print_float_result("T414.6", "sinhf(200.0f)", sinhf(200.0f));
    print_float_result("T414.7", "sinhf(NAN)", sinhf(NAN));
    print_float_result("T414.8", "sinhf(INFINITY)", sinhf(INFINITY));
}
#endif


#ifdef RUN_T415
static void test_T415(void) {
    print_ll_result("T415.1", "llround(0.3)", llround(0.3));
    print_ll_result("T415.2", "llround(-0.3)", llround(-0.3));
    print_ll_result("T415.3", "llround(0.7)", llround(0.7));
    print_ll_result("T415.4", "llround(-0.7)", llround(-0.7));
    print_ll_result("T415.5", "llround(1.5)", llround(1.5));
    print_ll_result("T415.6", "llround(1e15)", llround(1e15));
    print_ll_result("T415.7", "llround(1e18)", llround(1e18));
    print_ll_result("T415.8", "llround(INFINITY)", llround(INFINITY));
    print_ll_result("T415.9", "llround(-INFINITY)", llround(-INFINITY));
}
#endif


#ifdef RUN_T416
static void test_T416(void) {
    print_long_result("T416.1", "lround(0.3)", lround(0.3));
    print_long_result("T416.2", "lround(-0.3)", lround(-0.3));
    print_long_result("T416.3", "lround(0.7)", lround(0.7));
    print_long_result("T416.4", "lround(-0.7)", lround(-0.7));
    print_long_result("T416.5", "lround(1.5)", lround(1.5));
    print_long_result("T416.6", "lround(1e15)", lround(1e15));
    print_long_result("T416.7", "lround(INFINITY)", lround(INFINITY));
    print_long_result("T416.8", "lround(-INFINITY)", lround(-INFINITY));
}
#endif


#ifdef RUN_T417
static void test_T417(void) {
    print_ll_result("T417.1", "llrint(0.3)", llrint(0.3));
    print_ll_result("T417.2", "llrint(-0.3)", llrint(-0.3));
    print_ll_result("T417.3", "llrint(0.5)", llrint(0.5));
    print_ll_result("T417.4", "llrint(-0.5)", llrint(-0.5));
    print_ll_result("T417.5", "llrint(1e15)", llrint(1e15));
    print_ll_result("T417.6", "llrint(1e18)", llrint(1e18));
    print_ll_result("T417.7", "llrint(INFINITY)", llrint(INFINITY));
    print_ll_result("T417.8", "llrint(-INFINITY)", llrint(-INFINITY));
}
#endif


#ifdef RUN_T418
static void test_T418(void) {
    print_long_result("T418.1", "lrint(0.3)", lrint(0.3));
    print_long_result("T418.2", "lrint(-0.3)", lrint(-0.3));
    print_long_result("T418.3", "lrint(0.5)", lrint(0.5));
    print_long_result("T418.4", "lrint(-0.5)", lrint(-0.5));
    print_long_result("T418.5", "lrint(1e15)", lrint(1e15));
    print_long_result("T418.6", "lrint(INFINITY)", lrint(INFINITY));
    print_long_result("T418.7", "lrint(-INFINITY)", lrint(-INFINITY));
}
#endif


#ifdef RUN_T419
static void test_T419(void) {
    print_ll_result("T419.1", "llroundf(0.3f)", llroundf(0.3f));
    print_ll_result("T419.2", "llroundf(-0.3f)", llroundf(-0.3f));
    print_ll_result("T419.3", "llroundf(0.7f)", llroundf(0.7f));
    print_ll_result("T419.4", "llroundf(-0.7f)", llroundf(-0.7f));
    print_ll_result("T419.5", "llroundf(1e9f)", llroundf(1e9f));
    print_ll_result("T419.6", "llroundf(INFINITY)", llroundf(INFINITY));
    print_ll_result("T419.7", "llroundf(-INFINITY)", llroundf(-INFINITY));
}
#endif


#ifdef RUN_T420
static void test_T420(void) {
    print_long_result("T420.1", "lroundf(0.3f)", lroundf(0.3f));
    print_long_result("T420.2", "lroundf(-0.3f)", lroundf(-0.3f));
    print_long_result("T420.3", "lroundf(0.7f)", lroundf(0.7f));
    print_long_result("T420.4", "lroundf(-0.7f)", lroundf(-0.7f));
    print_long_result("T420.5", "lroundf(1e9f)", lroundf(1e9f));
    print_long_result("T420.6", "lroundf(INFINITY)", lroundf(INFINITY));
    print_long_result("T420.7", "lroundf(-INFINITY)", lroundf(-INFINITY));
}
#endif


#ifdef RUN_T421
static void test_T421(void) {
    print_ll_result("T421.1", "llrintf(0.3f)", llrintf(0.3f));
    print_ll_result("T421.2", "llrintf(-0.3f)", llrintf(-0.3f));
    print_ll_result("T421.3", "llrintf(0.5f)", llrintf(0.5f));
    print_ll_result("T421.4", "llrintf(1e9f)", llrintf(1e9f));
    print_ll_result("T421.5", "llrintf(INFINITY)", llrintf(INFINITY));
    print_ll_result("T421.6", "llrintf(-INFINITY)", llrintf(-INFINITY));
}
#endif


#ifdef RUN_T422
static void test_T422(void) {
    print_long_result("T422.1", "lrintf(0.3f)", lrintf(0.3f));
    print_long_result("T422.2", "lrintf(-0.3f)", lrintf(-0.3f));
    print_long_result("T422.3", "lrintf(0.5f)", lrintf(0.5f));
    print_long_result("T422.4", "lrintf(1e9f)", lrintf(1e9f));
    print_long_result("T422.5", "lrintf(INFINITY)", lrintf(INFINITY));
    print_long_result("T422.6", "lrintf(-INFINITY)", lrintf(-INFINITY));
}
#endif


#ifdef RUN_T423
static void test_T423(void) {
    print_double_result("T423.1", "nextafter(0.0, 1.0)", nextafter(0.0, 1.0));
    print_double_result("T423.2", "nextafter(0.0, -1.0)", nextafter(0.0, -1.0));
    print_double_result("T423.3", "nextafter(1.0, 2.0)", nextafter(1.0, 2.0));
    print_double_result("T423.4", "nextafter(1.0, 0.0)", nextafter(1.0, 0.0));
    print_double_result("T423.5", "nextafter(-1.0, 0.0)", nextafter(-1.0, 0.0));
    print_double_result("T423.6", "nextafter(-1.0, -2.0)", nextafter(-1.0, -2.0));
    print_double_result("T423.7", "nextafter(DBL_MAX, INFINITY)", nextafter(DBL_MAX, INFINITY));
    print_double_result("T423.8", "nextafter(5e-324, 0.0)", nextafter(5e-324, 0.0));
    print_double_result("T423.9", "nextafter(NAN, 1.0)", nextafter(NAN, 1.0));
    print_double_result("T423.10", "nextafter(1.0, 1.0)", nextafter(1.0, 1.0));
}
#endif


#ifdef RUN_T424
static void test_T424(void) {
    print_float_result("T424.1", "nextafterf(0.0f, 1.0f)", nextafterf(0.0f, 1.0f));
    print_float_result("T424.2", "nextafterf(0.0f, -1.0f)", nextafterf(0.0f, -1.0f));
    print_float_result("T424.3", "nextafterf(1.0f, 2.0f)", nextafterf(1.0f, 2.0f));
    print_float_result("T424.4", "nextafterf(1.0f, 0.0f)", nextafterf(1.0f, 0.0f));
    print_float_result("T424.5", "nextafterf(-1.0f, 0.0f)", nextafterf(-1.0f, 0.0f));
    print_float_result("T424.6", "nextafterf(FLT_MAX, INFINITY)", nextafterf(FLT_MAX, INFINITY));
    print_float_result("T424.7", "nextafterf(1.4e-45f, 0.0f)", nextafterf(1.4e-45f, 0.0f));
    print_float_result("T424.8", "nextafterf(NAN, 1.0f)", nextafterf(NAN, 1.0f));
    print_float_result("T424.9", "nextafterf(1.0f, 1.0f)", nextafterf(1.0f, 1.0f));
}
#endif


#ifdef RUN_T425
static void test_T425(void) {
    print_double_result("T425.1", "scalbn(0.0, 10)", scalbn(0.0, 10));
    print_double_result("T425.2", "scalbn(1e-310, 10)", scalbn(1e-310, 10));
    print_double_result("T425.3", "scalbn(INFINITY, 0)", scalbn(INFINITY, 0));
    print_double_result("T425.4", "scalbn(NAN, 0)", scalbn(NAN, 0));
    print_double_result("T425.5", "scalbn(1.0, 2000)", scalbn(1.0, 2000));
    print_double_result("T425.6", "scalbn(1.0, -2000)", scalbn(1.0, -2000));
    print_double_result("T425.7", "scalbn(1.0, -1074)", scalbn(1.0, -1074));
    print_double_result("T425.8", "scalbn(1.0, 10)", scalbn(1.0, 10));
}
#endif


#ifdef RUN_T426
static void test_T426(void) {
    print_float_result("T426.1", "scalbnf(0.0f, 10)", scalbnf(0.0f, 10));
    print_float_result("T426.2", "scalbnf(1e-40f, 10)", scalbnf(1e-40f, 10));
    print_float_result("T426.3", "scalbnf(INFINITY, 0)", scalbnf(INFINITY, 0));
    print_float_result("T426.4", "scalbnf(NAN, 0)", scalbnf(NAN, 0));
    print_float_result("T426.5", "scalbnf(1.0f, 200)", scalbnf(1.0f, 200));
    print_float_result("T426.6", "scalbnf(1.0f, -200)", scalbnf(1.0f, -200));
    print_float_result("T426.7", "scalbnf(1.0f, 10)", scalbnf(1.0f, 10));
}
#endif


#ifdef RUN_T427
static void test_T427(void) {
    print_double_result("T427.1", "scalbln(0.0, 10)", scalbln(0.0, 10));
    print_double_result("T427.2", "scalbln(1e-310, 10)", scalbln(1e-310, 10));
    print_double_result("T427.3", "scalbln(INFINITY, 0)", scalbln(INFINITY, 0));
    print_double_result("T427.4", "scalbln(1.0, 60000)", scalbln(1.0, 60000));
    print_double_result("T427.5", "scalbln(1.0, -60000)", scalbln(1.0, -60000));
    print_double_result("T427.6", "scalbln(1.0, -1074)", scalbln(1.0, -1074));
    print_double_result("T427.7", "scalbln(1.0, 10)", scalbln(1.0, 10));
}
#endif


#ifdef RUN_T428
static void test_T428(void) {
    print_float_result("T428.1", "scalblnf(0.0f, 10)", scalblnf(0.0f, 10));
    print_float_result("T428.2", "scalblnf(1e-40f, 10)", scalblnf(1e-40f, 10));
    print_float_result("T428.3", "scalblnf(INFINITY, 0)", scalblnf(INFINITY, 0));
    print_float_result("T428.4", "scalblnf(1.0f, 60000)", scalblnf(1.0f, 60000));
    print_float_result("T428.5", "scalblnf(1.0f, -60000)", scalblnf(1.0f, -60000));
    print_float_result("T428.6", "scalblnf(1.0f, -155)", scalblnf(1.0f, -155));
    print_float_result("T428.7", "scalblnf(1.0f, 10)", scalblnf(1.0f, 10));
}
#endif


#ifdef RUN_T429
static void test_T429(void) {
    print_double_result("T429.1", "log(0.0)", log(0.0));
    print_double_result("T429.2", "log(-1.0)", log(-1.0));
    print_double_result("T429.3", "log(NAN)", log(NAN));
    print_double_result("T429.4", "log(INFINITY)", log(INFINITY));
    print_double_result("T429.5", "log(1e-310)", log(1e-310));
    print_double_result("T429.6", "log(1.0)", log(1.0));
    print_double_result("T429.7", "log(0.9999999999)", log(0.9999999999));
    print_double_result("T429.8", "log(2.0)", log(2.0));
    print_double_result("T429.9", "log(1.5)", log(1.5));
}
#endif


#ifdef RUN_T430
static void test_T430(void) {
    print_float_result("T430.1", "logf(0.0f)", logf(0.0f));
    print_float_result("T430.2", "logf(-1.0f)", logf(-1.0f));
    print_float_result("T430.3", "logf(NAN)", logf(NAN));
    print_float_result("T430.4", "logf(INFINITY)", logf(INFINITY));
    print_float_result("T430.5", "logf(1e-40f)", logf(1e-40f));
    print_float_result("T430.6", "logf(1.0f)", logf(1.0f));
    print_float_result("T430.7", "logf(2.0f)", logf(2.0f));
    print_float_result("T430.8", "logf(1.5f)", logf(1.5f));
}
#endif


#ifdef RUN_T431
static void test_T431(void) {
    print_double_result("T431.1", "atan(0.0)", atan(0.0));
    print_double_result("T431.2", "atan(1e-20)", atan(1e-20));
    print_double_result("T431.3", "atan(0.3)", atan(0.3));
    print_double_result("T431.4", "atan(0.6)", atan(0.6));
    print_double_result("T431.5", "atan(1.0)", atan(1.0));
    print_double_result("T431.6", "atan(2.0)", atan(2.0));
    print_double_result("T431.7", "atan(1e300)", atan(1e300));
    print_double_result("T431.8", "atan(-1e300)", atan(-1e300));
    print_double_result("T431.9", "atan(NAN)", atan(NAN));
    print_double_result("T431.10", "atan(INFINITY)", atan(INFINITY));
}
#endif


#ifdef RUN_T432
static void test_T432(void) {
    print_float_result("T432.1", "atanf(0.0f)", atanf(0.0f));
    print_float_result("T432.2", "atanf(1e-20f)", atanf(1e-20f));
    print_float_result("T432.3", "atanf(0.3f)", atanf(0.3f));
    print_float_result("T432.4", "atanf(0.6f)", atanf(0.6f));
    print_float_result("T432.5", "atanf(1.0f)", atanf(1.0f));
    print_float_result("T432.6", "atanf(2.0f)", atanf(2.0f));
    print_float_result("T432.7", "atanf(1e30f)", atanf(1e30f));
    print_float_result("T432.8", "atanf(-1e30f)", atanf(-1e30f));
    print_float_result("T432.9", "atanf(NAN)", atanf(NAN));
}
#endif


#ifdef RUN_T433
static void test_T433(void) {
    print_double_complex_result("T433.1", "ctan(CMPLX(1.5707963, 20.0))", ctan(CMPLX(1.5707963, 20.0)));
    print_double_complex_result("T433.2", "ctan(CMPLX(0.5, 1.0))", ctan(CMPLX(0.5, 1.0)));
    print_double_complex_result("T433.3", "ctan(CMPLX(0.0, 0.0))", ctan(CMPLX(0.0, 0.0)));
    print_float_complex_result("T433.4", "ctanf(CMPLXF(1.5707963f, 20.0f))", ctanf(CMPLXF(1.5707963f, 20.0f)));
    print_float_complex_result("T433.5", "ctanf(CMPLXF(0.5f, 1.0f))", ctanf(CMPLXF(0.5f, 1.0f)));
}
#endif


#ifdef RUN_T434
static void test_T434(void) {
    print_double_result("T434.1", "acos(0x1p-1074)", acos(0x1p-1074));
    print_double_result("T434.2", "acos(1.0)", acos(1.0));
    print_double_result("T434.3", "acos(-1.0)", acos(-1.0));
    print_double_result("T434.4", "acos(0x1.0000000000001p+0)", acos(0x1.0000000000001p+0));
    print_double_result("T434.5", "acos(NAN)", acos(NAN));
}
#endif


#ifdef RUN_T435
static void test_T435(void) {
    print_float_result("T435.1", "acosf(0x1p-149f)", acosf(0x1p-149f));
    print_float_result("T435.2", "acosf(1.0f)", acosf(1.0f));
    print_float_result("T435.3", "acosf(-1.0f)", acosf(-1.0f));
    print_float_result("T435.4", "acosf(0x1.000002p+0f)", acosf(0x1.000002p+0f));
    print_float_result("T435.5", "acosf(NAN)", acosf(NAN));
}
#endif


#ifdef RUN_T436
static void test_T436(void) {
    print_double_result("T436.1", "acosh(0.5)", acosh(0.5));
    print_double_result("T436.2", "acosh(1.0)", acosh(1.0));
    print_double_result("T436.3", "acosh(2.0)", acosh(2.0));
    print_double_result("T436.4", "acosh(0x1p+20)", acosh(0x1p+20));
    print_double_result("T436.5", "acosh(INFINITY)", acosh(INFINITY));
    print_double_result("T436.6", "acosh(NAN)", acosh(NAN));
}
#endif


#ifdef RUN_T437
static void test_T437(void) {
    print_float_result("T437.1", "acoshf(0.5f)", acoshf(0.5f));
    print_float_result("T437.2", "acoshf(1.0f)", acoshf(1.0f));
    print_float_result("T437.3", "acoshf(2.0f)", acoshf(2.0f));
    print_float_result("T437.4", "acoshf(0x1p+60f)", acoshf(0x1p+60f));
    print_float_result("T437.5", "acoshf(INFINITY)", acoshf(INFINITY));
    print_float_result("T437.6", "acoshf(NAN)", acoshf(NAN));
}
#endif


#ifdef RUN_T438
static void test_T438(void) {
    print_double_result("T438.1", "asin(0x1p-1074)", asin(0x1p-1074));
    print_double_result("T438.2", "asin(1.0)", asin(1.0));
    print_double_result("T438.3", "asin(-1.0)", asin(-1.0));
    print_double_result("T438.4", "asin(-0x1.0000000000001p+0)", asin(-0x1.0000000000001p+0));
    print_double_result("T438.5", "asin(NAN)", asin(NAN));
}
#endif


#ifdef RUN_T439
static void test_T439(void) {
    print_float_result("T439.1", "asinf(0x1p-149f)", asinf(0x1p-149f));
    print_float_result("T439.2", "asinf(1.0f)", asinf(1.0f));
    print_float_result("T439.3", "asinf(-1.0f)", asinf(-1.0f));
    print_float_result("T439.4", "asinf(-0x1.000002p+0f)", asinf(-0x1.000002p+0f));
    print_float_result("T439.5", "asinf(NAN)", asinf(NAN));
}
#endif


#ifdef RUN_T440
static void test_T440(void) {
    print_double_result("T440.1", "asinh(0.0)", asinh(0.0));
    print_double_result("T440.2", "asinh(-0.0)", asinh(-0.0));
    print_double_result("T440.3", "asinh(0x1p-1074)", asinh(0x1p-1074));
    print_double_result("T440.4", "asinh(1.0)", asinh(1.0));
    print_double_result("T440.5", "asinh(-0x1p+10)", asinh(-0x1p+10));
    print_double_result("T440.6", "asinh(0x1p+500)", asinh(0x1p+500));
}
#endif


#ifdef RUN_T441
static void test_T441(void) {
    print_float_result("T441.1", "asinhf(0.0f)", asinhf(0.0f));
    print_float_result("T441.2", "asinhf(-0.0f)", asinhf(-0.0f));
    print_float_result("T441.3", "asinhf(0x1p-149f)", asinhf(0x1p-149f));
    print_float_result("T441.4", "asinhf(1.0f)", asinhf(1.0f));
    print_float_result("T441.5", "asinhf(-0x1p+10f)", asinhf(-0x1p+10f));
    print_float_result("T441.6", "asinhf(0x1p+120f)", asinhf(0x1p+120f));
}
#endif


#ifdef RUN_T442
static void test_T442(void) {
    print_double_result("T442.1", "atan2(0.0, -0.0)", atan2(0.0, -0.0));
    print_double_result("T442.2", "atan2(-0.0, -0.0)", atan2(-0.0, -0.0));
    print_double_result("T442.3", "atan2(1.0, INFINITY)", atan2(1.0, INFINITY));
    print_double_result("T442.4", "atan2(1.0, -INFINITY)", atan2(1.0, -INFINITY));
    print_double_result("T442.5", "atan2(INFINITY, 1.0)", atan2(INFINITY, 1.0));
    print_double_result("T442.6", "atan2(-INFINITY, -1.0)", atan2(-INFINITY, -1.0));
    print_double_result("T442.7", "atan2(0x1p+700, -0x1p+700)", atan2(0x1p+700, -0x1p+700));
}
#endif


#ifdef RUN_T443
static void test_T443(void) {
    print_float_result("T443.1", "atan2f(0.0f, -0.0f)", atan2f(0.0f, -0.0f));
    print_float_result("T443.2", "atan2f(-0.0f, -0.0f)", atan2f(-0.0f, -0.0f));
    print_float_result("T443.3", "atan2f(1.0f, INFINITY)", atan2f(1.0f, INFINITY));
    print_float_result("T443.4", "atan2f(1.0f, -INFINITY)", atan2f(1.0f, -INFINITY));
    print_float_result("T443.5", "atan2f(INFINITY, 1.0f)", atan2f(INFINITY, 1.0f));
    print_float_result("T443.6", "atan2f(-INFINITY, -1.0f)", atan2f(-INFINITY, -1.0f));
    print_float_result("T443.7", "atan2f(0x1p+120f, -0x1p+120f)", atan2f(0x1p+120f, -0x1p+120f));
}
#endif


#ifdef RUN_T444
static void test_T444(void) {
    print_double_result("T444.1", "atan(0.0)", atan(0.0));
    print_double_result("T444.2", "atan(-0.0)", atan(-0.0));
    print_double_result("T444.3", "atan(INFINITY)", atan(INFINITY));
    print_double_result("T444.4", "atan(-INFINITY)", atan(-INFINITY));
    print_double_result("T444.5", "atan(0x1p+500)", atan(0x1p+500));
    print_double_result("T444.6", "atan(-0x1p-40)", atan(-0x1p-40));
}
#endif


#ifdef RUN_T445
static void test_T445(void) {
    print_float_result("T445.1", "atanf(0.0f)", atanf(0.0f));
    print_float_result("T445.2", "atanf(-0.0f)", atanf(-0.0f));
    print_float_result("T445.3", "atanf(INFINITY)", atanf(INFINITY));
    print_float_result("T445.4", "atanf(-INFINITY)", atanf(-INFINITY));
    print_float_result("T445.5", "atanf(0x1p+120f)", atanf(0x1p+120f));
    print_float_result("T445.6", "atanf(-0x1p-20f)", atanf(-0x1p-20f));
}
#endif


#ifdef RUN_T446
static void test_T446(void) {
    print_double_result("T446.1", "atanh(0.0)", atanh(0.0));
    print_double_result("T446.2", "atanh(-0.0)", atanh(-0.0));
    print_double_result("T446.3", "atanh(0x1p-40)", atanh(0x1p-40));
    print_double_result("T446.4", "atanh(0.5)", atanh(0.5));
    print_double_result("T446.5", "atanh(-0.9999999999999999)", atanh(-0.9999999999999999));
    print_double_result("T446.6", "atanh(1.0)", atanh(1.0));
    print_double_result("T446.7", "atanh(2.0)", atanh(2.0));
}
#endif


#ifdef RUN_T447
static void test_T447(void) {
    print_float_result("T447.1", "atanhf(0.0f)", atanhf(0.0f));
    print_float_result("T447.2", "atanhf(-0.0f)", atanhf(-0.0f));
    print_float_result("T447.3", "atanhf(0x1p-20f)", atanhf(0x1p-20f));
    print_float_result("T447.4", "atanhf(0.5f)", atanhf(0.5f));
    print_float_result("T447.5", "atanhf(-0x1.fffffep-1f)", atanhf(-0x1.fffffep-1f));
    print_float_result("T447.6", "atanhf(1.0f)", atanhf(1.0f));
    print_float_result("T447.7", "atanhf(2.0f)", atanhf(2.0f));
}
#endif


#ifdef RUN_T448
static void test_T448(void) {
    print_float_result("T448.1", "sinf(0x1p+120f)", sinf(0x1p+120f));
    print_float_result("T448.2", "cosf(0x1.921fb6p+20f)", cosf(0x1.921fb6p+20f));
    print_float_result("T448.3", "tanf(-0x1p+100f)", tanf(-0x1p+100f));
    print_float_result("T448.4", "sinf(-0x1.fffffep+127f)", sinf(-0x1.fffffep+127f));
}
#endif


#ifdef RUN_T449
static void test_T449(void) {
    print_double_result("T449.1", "sin(0x1p+1000)", sin(0x1p+1000));
    print_double_result("T449.2", "cos(0x1.921fb54442d18p+20)", cos(0x1.921fb54442d18p+20));
    print_double_result("T449.3", "tan(-0x1p+900)", tan(-0x1p+900));
    print_double_result("T449.4", "sin(-0x1.fffffffffffffp+1023)", sin(-0x1.fffffffffffffp+1023));
}
#endif


#ifdef RUN_T450
static void test_T450(void) {
    print_float_complex_result("T450.1", "catanf(CMPLXF(0.0f, 0.0f))", catanf(CMPLXF(0.0f, 0.0f)));
    print_float_complex_result("T450.2", "catanf(CMPLXF(-2.0f, 0.0f))", catanf(CMPLXF(-2.0f, 0.0f)));
    print_float_complex_result("T450.3", "catanf(CMPLXF(1.0f, 0x1p+20f))", catanf(CMPLXF(1.0f, 0x1p+20f)));
    print_float_complex_result("T450.4", "catanf(CMPLXF(INFINITY, NAN))", catanf(CMPLXF(INFINITY, NAN)));
}
#endif


#ifdef RUN_T451
static void test_T451(void) {
    print_double_result("T451.1", "ceil(-1.25)", ceil(-1.25));
    print_double_result("T451.2", "ceil(-0.0)", ceil(-0.0));
    print_double_result("T451.3", "ceil(0.0)", ceil(0.0));
    print_double_result("T451.4", "ceil(0x1.fffffffffffffp-1)", ceil(0x1.fffffffffffffp-1));
    print_double_result("T451.5", "ceil(0x1p+52)", ceil(0x1p+52));
    print_double_result("T451.6", "ceil(NAN)", ceil(NAN));
}
#endif


#ifdef RUN_T452
static void test_T452(void) {
    print_float_result("T452.1", "ceilf(-1.25f)", ceilf(-1.25f));
    print_float_result("T452.2", "ceilf(-0.0f)", ceilf(-0.0f));
    print_float_result("T452.3", "ceilf(0.0f)", ceilf(0.0f));
    print_float_result("T452.4", "ceilf(0x1.fffffep-1f)", ceilf(0x1.fffffep-1f));
    print_float_result("T452.5", "ceilf(0x1p+23f)", ceilf(0x1p+23f));
    print_float_result("T452.6", "ceilf(NAN)", ceilf(NAN));
}
#endif


#ifdef RUN_T453
static void test_T453(void) {
    print_double_result("T453.1", "cos(0.0)", cos(0.0));
    print_double_result("T453.2", "cos(M_PI_2)", cos(M_PI_2));
    print_double_result("T453.3", "cos(0x1p+1000)", cos(0x1p+1000));
    print_double_result("T453.4", "cos(NAN)", cos(NAN));
}
#endif


#ifdef RUN_T454
static void test_T454(void) {
    print_float_result("T454.1", "cosf(0.0f)", cosf(0.0f));
    print_float_result("T454.2", "cosf((float)M_PI_2)", cosf((float)M_PI_2));
    print_float_result("T454.3", "cosf(0x1p+120f)", cosf(0x1p+120f));
    print_float_result("T454.4", "cosf(NAN)", cosf(NAN));
}
#endif


#ifdef RUN_T455
static void test_T455(void) {
    print_double_result("T455.1", "cosh(0.0)", cosh(0.0));
    print_double_result("T455.2", "cosh(1.0)", cosh(1.0));
    print_double_result("T455.3", "cosh(0x1p+9)", cosh(0x1p+9));
    print_double_result("T455.4", "cosh(INFINITY)", cosh(INFINITY));
    print_double_result("T455.5", "cosh(NAN)", cosh(NAN));
}
#endif


#ifdef RUN_T456
static void test_T456(void) {
    print_float_result("T456.1", "coshf(0.0f)", coshf(0.0f));
    print_float_result("T456.2", "coshf(1.0f)", coshf(1.0f));
    print_float_result("T456.3", "coshf(0x1p+6f)", coshf(0x1p+6f));
    print_float_result("T456.4", "coshf(INFINITY)", coshf(INFINITY));
    print_float_result("T456.5", "coshf(NAN)", coshf(NAN));
}
#endif


#ifdef RUN_T457
static void test_T457(void) {
    print_double_complex_result("T457.1", "cpow(CMPLX(0.0, 0.0), CMPLX(2.0, 0.0))", cpow(CMPLX(0.0, 0.0), CMPLX(2.0, 0.0)));
    print_double_complex_result("T457.2", "cpow(CMPLX(-1.0, 0.0), CMPLX(0.5, 0.0))", cpow(CMPLX(-1.0, 0.0), CMPLX(0.5, 0.0)));
    print_double_complex_result("T457.3", "cpow(CMPLX(1.0, 0x1p+20), CMPLX(2.0, -1.0))", cpow(CMPLX(1.0, 0x1p+20), CMPLX(2.0, -1.0)));
    print_double_complex_result("T457.4", "cpow(CMPLX(INFINITY, NAN), CMPLX(1.0, 0.0))", cpow(CMPLX(INFINITY, NAN), CMPLX(1.0, 0.0)));
}
#endif


#ifdef RUN_T458
static void test_T458(void) {
    print_float_complex_result("T458.1", "cpowf(CMPLXF(0.0f, 0.0f), CMPLXF(2.0f, 0.0f))", cpowf(CMPLXF(0.0f, 0.0f), CMPLXF(2.0f, 0.0f)));
    print_float_complex_result("T458.2", "cpowf(CMPLXF(-1.0f, 0.0f), CMPLXF(0.5f, 0.0f))", cpowf(CMPLXF(-1.0f, 0.0f), CMPLXF(0.5f, 0.0f)));
    print_float_complex_result("T458.3", "cpowf(CMPLXF(1.0f, 0x1p+20f), CMPLXF(2.0f, -1.0f))", cpowf(CMPLXF(1.0f, 0x1p+20f), CMPLXF(2.0f, -1.0f)));
    print_float_complex_result("T458.4", "cpowf(CMPLXF(INFINITY, NAN), CMPLXF(1.0f, 0.0f))", cpowf(CMPLXF(INFINITY, NAN), CMPLXF(1.0f, 0.0f)));
}
#endif


#ifdef RUN_T459
static void test_T459(void) {
    print_double_complex_result("T459.1", "csqrt(CMPLX(-4.0, 0.0))", csqrt(CMPLX(-4.0, 0.0)));
    print_double_complex_result("T459.2", "csqrt(CMPLX(-0.0, -0.0))", csqrt(CMPLX(-0.0, -0.0)));
    print_double_complex_result("T459.3", "csqrt(CMPLX(1.0, 0x1p+20))", csqrt(CMPLX(1.0, 0x1p+20)));
    print_double_complex_result("T459.4", "csqrt(CMPLX(INFINITY, NAN))", csqrt(CMPLX(INFINITY, NAN)));
}
#endif


#ifdef RUN_T460
static void test_T460(void) {
    print_float_complex_result("T460.1", "csqrtf(CMPLXF(-4.0f, 0.0f))", csqrtf(CMPLXF(-4.0f, 0.0f)));
    print_float_complex_result("T460.2", "csqrtf(CMPLXF(-0.0f, -0.0f))", csqrtf(CMPLXF(-0.0f, -0.0f)));
    print_float_complex_result("T460.3", "csqrtf(CMPLXF(1.0f, 0x1p+20f))", csqrtf(CMPLXF(1.0f, 0x1p+20f)));
    print_float_complex_result("T460.4", "csqrtf(CMPLXF(INFINITY, NAN))", csqrtf(CMPLXF(INFINITY, NAN)));
}
#endif


#ifdef RUN_T461
static void test_T461(void) {
    print_double_complex_result("T461.1", "ctan(CMPLX(0.0, 0.0))", ctan(CMPLX(0.0, 0.0)));
    print_double_complex_result("T461.2", "ctan(CMPLX(-2.0, 0.0))", ctan(CMPLX(-2.0, 0.0)));
    print_double_complex_result("T461.3", "ctan(CMPLX(1.0, 0x1p+10))", ctan(CMPLX(1.0, 0x1p+10)));
    print_double_complex_result("T461.4", "ctan(CMPLX(INFINITY, NAN))", ctan(CMPLX(INFINITY, NAN)));
}
#endif


#ifdef RUN_T462
static void test_T462(void) {
    print_float_complex_result("T462.1", "ctanf(CMPLXF(0.0f, 0.0f))", ctanf(CMPLXF(0.0f, 0.0f)));
    print_float_complex_result("T462.2", "ctanf(CMPLXF(-2.0f, 0.0f))", ctanf(CMPLXF(-2.0f, 0.0f)));
    print_float_complex_result("T462.3", "ctanf(CMPLXF(1.0f, 0x1p+10f))", ctanf(CMPLXF(1.0f, 0x1p+10f)));
    print_float_complex_result("T462.4", "ctanf(CMPLXF(INFINITY, NAN))", ctanf(CMPLXF(INFINITY, NAN)));
}
#endif


#ifdef RUN_T463
static void test_T463(void) {
    print_double_complex_result("T463.1", "ctan(CMPLX(1.0, 128.0))", ctan(CMPLX(1.0, 128.0)));
    print_double_complex_result("T463.2", "catan(CMPLX(1.0, 128.0))", catan(CMPLX(1.0, 128.0)));
    print_double_complex_result("T463.3", "csin(CMPLX(1.0, 256.0 * M_PI))", csin(CMPLX(1.0, 256.0 * M_PI)));
    print_double_complex_result("T463.4", "ccos(CMPLX(1.0, 257.0 * M_PI))", ccos(CMPLX(1.0, 257.0 * M_PI)));
}
#endif


#ifdef RUN_T464
static void test_T464(void) {
    print_float_complex_result("T464.1", "ctanf(CMPLXF(1.0f, 128.0f))", ctanf(CMPLXF(1.0f, 128.0f)));
    print_float_complex_result("T464.2", "catanf(CMPLXF(1.0f, 128.0f))", catanf(CMPLXF(1.0f, 128.0f)));
    print_float_complex_result("T464.3", "csinf(CMPLXF(1.0f, 256.0f * (float)M_PI))", csinf(CMPLXF(1.0f, 256.0f * (float)M_PI)));
    print_float_complex_result("T464.4", "ccosf(CMPLXF(1.0f, 257.0f * (float)M_PI))", ccosf(CMPLXF(1.0f, 257.0f * (float)M_PI)));
}
#endif


#ifdef RUN_T465
static void test_T465(void) {
    print_double_result("T465.1", "erfc(0.0)", erfc(0.0));
    print_double_result("T465.2", "erfc(-1.0)", erfc(-1.0));
    print_double_result("T465.3", "erfc(1.0)", erfc(1.0));
    print_double_result("T465.4", "erfc(28.0)", erfc(28.0));
}
#endif


#ifdef RUN_T466
static void test_T466(void) {
    print_float_result("T466.1", "erfcf(0.0f)", erfcf(0.0f));
    print_float_result("T466.2", "erfcf(-1.0f)", erfcf(-1.0f));
    print_float_result("T466.3", "erfcf(1.0f)", erfcf(1.0f));
    print_float_result("T466.4", "erfcf(10.0f)", erfcf(10.0f));
}
#endif


#ifdef RUN_T467
static void test_T467(void) {
    print_float_result("T467.1", "erff(0.0f)", erff(0.0f));
    print_float_result("T467.2", "erff(-1.0f)", erff(-1.0f));
    print_float_result("T467.3", "erff(1.0f)", erff(1.0f));
    print_float_result("T467.4", "erff(10.0f)", erff(10.0f));
}
#endif


#ifdef RUN_T468
static void test_T468(void) {
    print_double_result("T468.1", "exp(-0x1p+10)", exp(-0x1p+10));
    print_double_result("T468.2", "exp(0.0)", exp(0.0));
    print_double_result("T468.3", "exp(1.0)", exp(1.0));
    print_double_result("T468.4", "exp(0x1.62e42fefa39efp+9)", exp(0x1.62e42fefa39efp+9));
}
#endif


#ifdef RUN_T469
static void test_T469(void) {
    print_double_result("T469.1", "expm1(-0x1p-54)", expm1(-0x1p-54));
    print_double_result("T469.2", "expm1(0.0)", expm1(0.0));
    print_double_result("T469.3", "expm1(1.0)", expm1(1.0));
    print_double_result("T469.4", "expm1(0x1.62e42fefa39efp+9)", expm1(0x1.62e42fefa39efp+9));
}
#endif


#ifdef RUN_T470
static void test_T470(void) {
    print_float_result("T470.1", "expm1f(-0x1p-25f)", expm1f(-0x1p-25f));
    print_float_result("T470.2", "expm1f(0.0f)", expm1f(0.0f));
    print_float_result("T470.3", "expm1f(1.0f)", expm1f(1.0f));
    print_float_result("T470.4", "expm1f(0x1.62e43p+6f)", expm1f(0x1.62e43p+6f));
}
#endif


#ifdef RUN_T471
static void test_T471(void) {
    print_double_result("T471.1", "floor(-1.25)", floor(-1.25));
    print_double_result("T471.2", "floor(-0.0)", floor(-0.0));
    print_double_result("T471.3", "floor(0.0)", floor(0.0));
    print_double_result("T471.4", "floor(0x1.fffffffffffffp-1)", floor(0x1.fffffffffffffp-1));
    print_double_result("T471.5", "floor(0x1p+52)", floor(0x1p+52));
    print_double_result("T471.6", "floor(NAN)", floor(NAN));
}
#endif


#ifdef RUN_T472
static void test_T472(void) {
    print_float_result("T472.1", "floorf(-1.25f)", floorf(-1.25f));
    print_float_result("T472.2", "floorf(-0.0f)", floorf(-0.0f));
    print_float_result("T472.3", "floorf(0.0f)", floorf(0.0f));
    print_float_result("T472.4", "floorf(0x1.fffffep-1f)", floorf(0x1.fffffep-1f));
    print_float_result("T472.5", "floorf(0x1p+23f)", floorf(0x1p+23f));
    print_float_result("T472.6", "floorf(NAN)", floorf(NAN));
}
#endif


#ifdef RUN_T473
static void test_T473(void) {
    print_double_result("T473.1", "fmax(-0.0, 0.0)", fmax(-0.0, 0.0));
    print_double_result("T473.2", "fmax(NAN, -1.0)", fmax(NAN, -1.0));
    print_double_result("T473.3", "fmax(-1.0, NAN)", fmax(-1.0, NAN));
    print_double_result("T473.4", "fmax(-INFINITY, INFINITY)", fmax(-INFINITY, INFINITY));
}
#endif


#ifdef RUN_T474
static void test_T474(void) {
    print_float_result("T474.1", "fmaxf(-0.0f, 0.0f)", fmaxf(-0.0f, 0.0f));
    print_float_result("T474.2", "fmaxf(NAN, -1.0f)", fmaxf(NAN, -1.0f));
    print_float_result("T474.3", "fmaxf(-1.0f, NAN)", fmaxf(-1.0f, NAN));
    print_float_result("T474.4", "fmaxf(-INFINITY, INFINITY)", fmaxf(-INFINITY, INFINITY));
}
#endif


#ifdef RUN_T475
static void test_T475(void) {
    print_double_result("T475.1", "fmin(-0.0, 0.0)", fmin(-0.0, 0.0));
    print_double_result("T475.2", "fmin(NAN, -1.0)", fmin(NAN, -1.0));
    print_double_result("T475.3", "fmin(-1.0, NAN)", fmin(-1.0, NAN));
    print_double_result("T475.4", "fmin(-INFINITY, INFINITY)", fmin(-INFINITY, INFINITY));
}
#endif


#ifdef RUN_T476
static void test_T476(void) {
    print_float_result("T476.1", "fminf(-0.0f, 0.0f)", fminf(-0.0f, 0.0f));
    print_float_result("T476.2", "fminf(NAN, -1.0f)", fminf(NAN, -1.0f));
    print_float_result("T476.3", "fminf(-1.0f, NAN)", fminf(-1.0f, NAN));
    print_float_result("T476.4", "fminf(-INFINITY, INFINITY)", fminf(-INFINITY, INFINITY));
}
#endif


#ifdef RUN_T477
static void test_T477(void) {
    print_double_result("T477.1", "fmod(5.5, 2.0)", fmod(5.5, 2.0));
    print_double_result("T477.2", "fmod(-5.5, 2.0)", fmod(-5.5, 2.0));
    print_double_result("T477.3", "fmod(0x1p+60, 3.0)", fmod(0x1p+60, 3.0));
    print_double_result("T477.4", "fmod(INFINITY, 2.0)", fmod(INFINITY, 2.0));
}
#endif


#ifdef RUN_T478
static void test_T478(void) {
    print_float_result("T478.1", "fmodf(5.5f, 2.0f)", fmodf(5.5f, 2.0f));
    print_float_result("T478.2", "fmodf(-5.5f, 2.0f)", fmodf(-5.5f, 2.0f));
    print_float_result("T478.3", "fmodf(0x1p+20f, 3.0f)", fmodf(0x1p+20f, 3.0f));
    print_float_result("T478.4", "fmodf(INFINITY, 2.0f)", fmodf(INFINITY, 2.0f));
}
#endif


#ifdef RUN_T479
static void test_T479(void) {
    print_classification_result("T479.1", "fpclassify(0.0)", 0.0);
    print_classification_result("T479.2", "fpclassify(-0.0)", -0.0);
    print_classification_result("T479.3", "fpclassify(0x1p-1074)", 0x1p-1074);
    print_classification_result("T479.4", "fpclassify(1.0)", 1.0);
    print_classification_result("T479.5", "fpclassify(INFINITY)", INFINITY);
    print_classification_result("T479.6", "fpclassify(NAN)", NAN);
}
#endif


#ifdef RUN_T480
static void test_T480(void) {
    int exp;
    double frac;

    frac = frexp(0.0, &exp);
    print_double_int_pair_result("T480.1", "frexp(0.0)", frac, exp);
    frac = frexp(-0.0, &exp);
    print_double_int_pair_result("T480.2", "frexp(-0.0)", frac, exp);
    frac = frexp(0x1p-1074, &exp);
    print_double_int_pair_result("T480.3", "frexp(0x1p-1074)", frac, exp);
    frac = frexp(1.5, &exp);
    print_double_int_pair_result("T480.4", "frexp(1.5)", frac, exp);
    frac = frexp(INFINITY, &exp);
    print_double_int_pair_result("T480.5", "frexp(INFINITY)", frac, exp);
}
#endif


#ifdef RUN_T481
static void test_T481(void) {
    int exp;
    float frac;

    frac = frexpf(0.0f, &exp);
    print_float_int_pair_result("T481.1", "frexpf(0.0f)", frac, exp);
    frac = frexpf(-0.0f, &exp);
    print_float_int_pair_result("T481.2", "frexpf(-0.0f)", frac, exp);
    frac = frexpf(0x1p-149f, &exp);
    print_float_int_pair_result("T481.3", "frexpf(0x1p-149f)", frac, exp);
    frac = frexpf(1.5f, &exp);
    print_float_int_pair_result("T481.4", "frexpf(1.5f)", frac, exp);
    frac = frexpf(INFINITY, &exp);
    print_float_int_pair_result("T481.5", "frexpf(INFINITY)", frac, exp);
}
#endif


#ifdef RUN_T482
static void test_T482(void) {
    double value;

    signgam = 12345;
    value = lgamma(-2.5);
    print_double_int_pair_result("T482.1", "lgamma(-2.5)", value, signgam);
    signgam = 12345;
    value = lgamma(-0x1p-10);
    print_double_int_pair_result("T482.2", "lgamma(-0x1p-10)", value, signgam);
    signgam = 12345;
    value = lgamma(0.5);
    print_double_int_pair_result("T482.3", "lgamma(0.5)", value, signgam);
    signgam = 12345;
    value = lgamma(10.0);
    print_double_int_pair_result("T482.4", "lgamma(10.0)", value, signgam);
}
#endif


#ifdef RUN_T483
static void test_T483(void) {
    float value;

    signgam = 12345;
    value = lgammaf(-2.5f);
    print_float_int_pair_result("T483.1", "lgammaf(-2.5f)", value, signgam);
    signgam = 12345;
    value = lgammaf(-0x1p-10f);
    print_float_int_pair_result("T483.2", "lgammaf(-0x1p-10f)", value, signgam);
    signgam = 12345;
    value = lgammaf(0.5f);
    print_float_int_pair_result("T483.3", "lgammaf(0.5f)", value, signgam);
    signgam = 12345;
    value = lgammaf(10.0f);
    print_float_int_pair_result("T483.4", "lgammaf(10.0f)", value, signgam);
}
#endif


#ifdef RUN_T484
static void test_T484(void) {
    print_double_result("T484.1", "hypot(3.0, 4.0)", hypot(3.0, 4.0));
    print_double_result("T484.2", "hypot(0x1p+700, 0x1p+700)", hypot(0x1p+700, 0x1p+700));
    print_double_result("T484.3", "hypot(INFINITY, 1.0)", hypot(INFINITY, 1.0));
    print_double_result("T484.4", "hypot(NAN, INFINITY)", hypot(NAN, INFINITY));
}
#endif


#ifdef RUN_T485
static void test_T485(void) {
    print_float_result("T485.1", "hypotf(3.0f, 4.0f)", hypotf(3.0f, 4.0f));
    print_float_result("T485.2", "hypotf(0x1p+120f, 0x1p+120f)", hypotf(0x1p+120f, 0x1p+120f));
    print_float_result("T485.3", "hypotf(INFINITY, 1.0f)", hypotf(INFINITY, 1.0f));
    print_float_result("T485.4", "hypotf(NAN, INFINITY)", hypotf(NAN, INFINITY));
}
#endif


#ifdef RUN_T486
static void test_T486(void) {
    print_int_result("T486.1", "ilogb(0.0)", ilogb(0.0));
    print_int_result("T486.2", "ilogb(0x1p-1074)", ilogb(0x1p-1074));
    print_int_result("T486.3", "ilogb(1.0)", ilogb(1.0));
    print_int_result("T486.4", "ilogb(INFINITY)", ilogb(INFINITY));
    print_int_result("T486.5", "ilogb(NAN)", ilogb(NAN));
}
#endif


#ifdef RUN_T487
static void test_T487(void) {
    print_double_result("T487.1", "j0(0.125)", j0(0.125));
    print_double_result("T487.2", "j0(1.0)", j0(1.0));
    print_double_result("T487.3", "j0(1e6)", j0(1e6));
}
#endif


#ifdef RUN_T488
static void test_T488(void) {
    print_double_result("T488.1", "j1(0.125)", j1(0.125));
    print_double_result("T488.2", "j1(1.0)", j1(1.0));
    print_double_result("T488.3", "j1(1e6)", j1(1e6));
}
#endif


#ifdef RUN_T489
static void test_T489(void) {
    print_double_result("T489.1", "jn(2, 0.125)", jn(2, 0.125));
    print_double_result("T489.2", "jn(5, 1.0)", jn(5, 1.0));
    print_double_result("T489.3", "jn(20, 1e6)", jn(20, 1e6));
}
#endif


#ifdef RUN_T490
static void test_T490(void) {
    print_ll_result("T490.1", "llrintf(2.25f)", llrintf(2.25f));
    print_ll_result("T490.2", "llrintf(-2.75f)", llrintf(-2.75f));
    print_ll_result("T490.3", "llrintf(0.0f)", llrintf(0.0f));
}
#endif


#ifdef RUN_T491
static void test_T491(void) {
    print_ll_result("T491.1", "llround(2.5)", llround(2.5));
    print_ll_result("T491.2", "llround(-2.5)", llround(-2.5));
    print_ll_result("T491.3", "llround(0.0)", llround(0.0));
}
#endif


#ifdef RUN_T492
static void test_T492(void) {
    print_ll_result("T492.1", "llroundf(2.5f)", llroundf(2.5f));
    print_ll_result("T492.2", "llroundf(-2.5f)", llroundf(-2.5f));
    print_ll_result("T492.3", "llroundf(0.0f)", llroundf(0.0f));
}
#endif


#ifdef RUN_T493
static void test_T493(void) {
    print_double_result("T493.1", "log10(1.0)", log10(1.0));
    print_double_result("T493.2", "log10(10.0)", log10(10.0));
    print_double_result("T493.3", "log10(0.1)", log10(0.1));
    print_double_result("T493.4", "log10(0x1p-1074)", log10(0x1p-1074));
    print_double_result("T493.5", "log10(INFINITY)", log10(INFINITY));
}
#endif


#ifdef RUN_T494
static void test_T494(void) {
    print_double_result("T494.1", "log1p(-0.5)", log1p(-0.5));
    print_double_result("T494.2", "log1p(-0x1p-54)", log1p(-0x1p-54));
    print_double_result("T494.3", "log1p(0.0)", log1p(0.0));
    print_double_result("T494.4", "log1p(1.0)", log1p(1.0));
    print_double_result("T494.5", "log1p(INFINITY)", log1p(INFINITY));
}
#endif


#ifdef RUN_T495
static void test_T495(void) {
    print_float_result("T495.1", "log1pf(-0.5f)", log1pf(-0.5f));
    print_float_result("T495.2", "log1pf(-0x1p-25f)", log1pf(-0x1p-25f));
    print_float_result("T495.3", "log1pf(0.0f)", log1pf(0.0f));
    print_float_result("T495.4", "log1pf(1.0f)", log1pf(1.0f));
    print_float_result("T495.5", "log1pf(INFINITY)", log1pf(INFINITY));
}
#endif


#ifdef RUN_T496
static void test_T496(void) {
    print_double_result("T496.1", "log2(1.0)", log2(1.0));
    print_double_result("T496.2", "log2(2.0)", log2(2.0));
    print_double_result("T496.3", "log2(0.5)", log2(0.5));
    print_double_result("T496.4", "log2(0x1p-1074)", log2(0x1p-1074));
    print_double_result("T496.5", "log2(INFINITY)", log2(INFINITY));
}
#endif


#ifdef RUN_T497
static void test_T497(void) {
    print_double_result("T497.1", "logb(0.0)", logb(0.0));
    print_double_result("T497.2", "logb(0x1p-1074)", logb(0x1p-1074));
    print_double_result("T497.3", "logb(1.0)", logb(1.0));
    print_double_result("T497.4", "logb(INFINITY)", logb(INFINITY));
    print_double_result("T497.5", "logb(NAN)", logb(NAN));
}
#endif


#ifdef RUN_T498
static void test_T498(void) {
    print_double_result("T498.1", "log(1.0)", log(1.0));
    print_double_result("T498.2", "log(0x1p-1074)", log(0x1p-1074));
    print_double_result("T498.3", "log(2.0)", log(2.0));
    print_double_result("T498.4", "log(INFINITY)", log(INFINITY));
    print_double_result("T498.5", "log(-1.0)", log(-1.0));
}
#endif


#ifdef RUN_T499
static void test_T499(void) {
    print_float_result("T499.1", "logf(1.0f)", logf(1.0f));
    print_float_result("T499.2", "logf(0x1p-149f)", logf(0x1p-149f));
    print_float_result("T499.3", "logf(2.0f)", logf(2.0f));
    print_float_result("T499.4", "logf(INFINITY)", logf(INFINITY));
    print_float_result("T499.5", "logf(-1.0f)", logf(-1.0f));
}
#endif


#ifdef RUN_T500
static void test_T500(void) {
    print_long_result("T500.1", "lrint(2.25)", lrint(2.25));
    print_long_result("T500.2", "lrint(-2.75)", lrint(-2.75));
    print_long_result("T500.3", "lrint(0.0)", lrint(0.0));
}
#endif


#ifdef RUN_T501
static void test_T501(void) {
    print_long_result("T501.1", "lround(2.5)", lround(2.5));
    print_long_result("T501.2", "lround(-2.5)", lround(-2.5));
    print_long_result("T501.3", "lround(0.0)", lround(0.0));
}
#endif


#ifdef RUN_T502
static void test_T502(void) {
    print_long_result("T502.1", "lroundf(2.5f)", lroundf(2.5f));
    print_long_result("T502.2", "lroundf(-2.5f)", lroundf(-2.5f));
    print_long_result("T502.3", "lroundf(0.0f)", lroundf(0.0f));
}
#endif


#ifdef RUN_T503
static void test_T503(void) {
    double iptr;
    double frac;

    frac = modf(1.75, &iptr);
    print_double_pair_result("T503.1", "modf(1.75)", frac, iptr);
    frac = modf(-1.75, &iptr);
    print_double_pair_result("T503.2", "modf(-1.75)", frac, iptr);
    frac = modf(INFINITY, &iptr);
    print_double_pair_result("T503.3", "modf(INFINITY)", frac, iptr);
    frac = modf(NAN, &iptr);
    print_double_pair_result("T503.4", "modf(NAN)", frac, iptr);
}
#endif


#ifdef RUN_T504
static void test_T504(void) {
    float iptr;
    float frac;

    frac = modff(1.75f, &iptr);
    print_float_pair_result("T504.1", "modff(1.75f)", frac, iptr);
    frac = modff(-1.75f, &iptr);
    print_float_pair_result("T504.2", "modff(-1.75f)", frac, iptr);
    frac = modff(INFINITY, &iptr);
    print_float_pair_result("T504.3", "modff(INFINITY)", frac, iptr);
    frac = modff(NAN, &iptr);
    print_float_pair_result("T504.4", "modff(NAN)", frac, iptr);
}
#endif


#ifdef RUN_T505
static void test_T505(void) {
    print_double_result("T505.1", "nextafter(0.0, 1.0)", nextafter(0.0, 1.0));
    print_double_result("T505.2", "nextafter(0.0, -1.0)", nextafter(0.0, -1.0));
    print_double_result("T505.3", "nextafter(1.0, 2.0)", nextafter(1.0, 2.0));
    print_double_result("T505.4", "nextafter(INFINITY, 0.0)", nextafter(INFINITY, 0.0));
}
#endif


#ifdef RUN_T506
static void test_T506(void) {
    print_float_result("T506.1", "nextafterf(0.0f, 1.0f)", nextafterf(0.0f, 1.0f));
    print_float_result("T506.2", "nextafterf(0.0f, -1.0f)", nextafterf(0.0f, -1.0f));
    print_float_result("T506.3", "nextafterf(1.0f, 2.0f)", nextafterf(1.0f, 2.0f));
    print_float_result("T506.4", "nextafterf(INFINITY, 0.0f)", nextafterf(INFINITY, 0.0f));
}
#endif


#ifdef RUN_T507
static void test_T507(void) {
    print_double_result("T507.1", "pow(-2.0, 3.0)", pow(-2.0, 3.0));
    print_double_result("T507.2", "pow(-2.0, 0.5)", pow(-2.0, 0.5));
    print_double_result("T507.3", "pow(0.0, -3.0)", pow(0.0, -3.0));
    print_double_result("T507.4", "pow(INFINITY, -1.0)", pow(INFINITY, -1.0));
    print_double_result("T507.5", "pow(0.5, INFINITY)", pow(0.5, INFINITY));
}
#endif


#ifdef RUN_T508
static void test_T508(void) {
    print_float_result("T508.1", "powf(-2.0f, 3.0f)", powf(-2.0f, 3.0f));
    print_float_result("T508.2", "powf(-2.0f, 0.5f)", powf(-2.0f, 0.5f));
    print_float_result("T508.3", "powf(0.0f, -3.0f)", powf(0.0f, -3.0f));
    print_float_result("T508.4", "powf(INFINITY, -1.0f)", powf(INFINITY, -1.0f));
    print_float_result("T508.5", "powf(0.5f, INFINITY)", powf(0.5f, INFINITY));
}
#endif


#ifdef RUN_T509
static void test_T509(void) {
    print_double_result("T509.1", "remainder(5.5, 2.0)", remainder(5.5, 2.0));
    print_double_result("T509.2", "remainder(-5.5, 2.0)", remainder(-5.5, 2.0));
    print_double_result("T509.3", "remainder(7.0, 2.0)", remainder(7.0, 2.0));
    print_double_result("T509.4", "remainder(INFINITY, 2.0)", remainder(INFINITY, 2.0));
}
#endif


#ifdef RUN_T510
static void test_T510(void) {
    print_float_result("T510.1", "remainderf(5.5f, 2.0f)", remainderf(5.5f, 2.0f));
    print_float_result("T510.2", "remainderf(-5.5f, 2.0f)", remainderf(-5.5f, 2.0f));
    print_float_result("T510.3", "remainderf(7.0f, 2.0f)", remainderf(7.0f, 2.0f));
    print_float_result("T510.4", "remainderf(INFINITY, 2.0f)", remainderf(INFINITY, 2.0f));
}
#endif


#ifdef RUN_T511
static void test_T511(void) {
    int quo;
    double value;

    value = remquo(5.5, 2.0, &quo);
    print_double_int_pair_result("T511.1", "remquo(5.5, 2.0)", value, quo);
    value = remquo(-5.5, 2.0, &quo);
    print_double_int_pair_result("T511.2", "remquo(-5.5, 2.0)", value, quo);
    value = remquo(7.0, 2.0, &quo);
    print_double_int_pair_result("T511.3", "remquo(7.0, 2.0)", value, quo);
}
#endif


#ifdef RUN_T512
static void test_T512(void) {
    int quo;
    float value;

    value = remquof(5.5f, 2.0f, &quo);
    print_float_int_pair_result("T512.1", "remquof(5.5f, 2.0f)", value, quo);
    value = remquof(-5.5f, 2.0f, &quo);
    print_float_int_pair_result("T512.2", "remquof(-5.5f, 2.0f)", value, quo);
    value = remquof(7.0f, 2.0f, &quo);
    print_float_int_pair_result("T512.3", "remquof(7.0f, 2.0f)", value, quo);
}
#endif


#ifdef RUN_T513
static void test_T513(void) {
    print_double_result("T513.1", "rint(2.25)", rint(2.25));
    print_double_result("T513.2", "rint(-2.75)", rint(-2.75));
    print_double_result("T513.3", "rint(0.0)", rint(0.0));
    print_double_result("T513.4", "rint(NAN)", rint(NAN));
}
#endif


#ifdef RUN_T514
static void test_T514(void) {
    print_float_result("T514.1", "rintf(2.25f)", rintf(2.25f));
    print_float_result("T514.2", "rintf(-2.75f)", rintf(-2.75f));
    print_float_result("T514.3", "rintf(0.0f)", rintf(0.0f));
    print_float_result("T514.4", "rintf(NAN)", rintf(NAN));
}
#endif


#ifdef RUN_T515
static void test_T515(void) {
    print_double_result("T515.1", "round(2.5)", round(2.5));
    print_double_result("T515.2", "round(-2.5)", round(-2.5));
    print_double_result("T515.3", "round(0.0)", round(0.0));
    print_double_result("T515.4", "round(-0.0)", round(-0.0));
}
#endif


#ifdef RUN_T516
static void test_T516(void) {
    print_float_result("T516.1", "roundf(2.5f)", roundf(2.5f));
    print_float_result("T516.2", "roundf(-2.5f)", roundf(-2.5f));
    print_float_result("T516.3", "roundf(0.0f)", roundf(0.0f));
    print_float_result("T516.4", "roundf(-0.0f)", roundf(-0.0f));
}
#endif


#ifdef RUN_T517
static void test_T517(void) {
    print_double_result("T517.1", "scalbln(1.5, 5)", scalbln(1.5, 5));
    print_double_result("T517.2", "scalbln(1.0, -1074)", scalbln(1.0, -1074));
    print_double_result("T517.3", "scalbln(1.0, 1024)", scalbln(1.0, 1024));
    print_double_result("T517.4", "scalbln(NAN, 3)", scalbln(NAN, 3));
}
#endif


#ifdef RUN_T518
static void test_T518(void) {
    print_float_result("T518.1", "scalblnf(1.5f, 5)", scalblnf(1.5f, 5));
    print_float_result("T518.2", "scalblnf(1.0f, -149)", scalblnf(1.0f, -149));
    print_float_result("T518.3", "scalblnf(1.0f, 128)", scalblnf(1.0f, 128));
    print_float_result("T518.4", "scalblnf(NAN, 3)", scalblnf(NAN, 3));
}
#endif


#ifdef RUN_T519
static void test_T519(void) {
    print_double_result("T519.1", "scalbn(1.5, 5)", scalbn(1.5, 5));
    print_double_result("T519.2", "scalbn(1.0, -1074)", scalbn(1.0, -1074));
    print_double_result("T519.3", "scalbn(1.0, 1024)", scalbn(1.0, 1024));
    print_double_result("T519.4", "scalbn(NAN, 3)", scalbn(NAN, 3));
}
#endif


#ifdef RUN_T520
static void test_T520(void) {
    print_float_result("T520.1", "scalbnf(1.5f, 5)", scalbnf(1.5f, 5));
    print_float_result("T520.2", "scalbnf(1.0f, -149)", scalbnf(1.0f, -149));
    print_float_result("T520.3", "scalbnf(1.0f, 128)", scalbnf(1.0f, 128));
    print_float_result("T520.4", "scalbnf(NAN, 3)", scalbnf(NAN, 3));
}
#endif


#ifdef RUN_T521
static void test_T521(void) {
    print_double_result("T521.1", "sinh(0.0)", sinh(0.0));
    print_double_result("T521.2", "sinh(-0.0)", sinh(-0.0));
    print_double_result("T521.3", "sinh(1.0)", sinh(1.0));
    print_double_result("T521.4", "sinh(710.0)", sinh(710.0));
    print_double_result("T521.5", "sinh(INFINITY)", sinh(INFINITY));
}
#endif


#ifdef RUN_T522
static void test_T522(void) {
    print_float_result("T522.1", "sinhf(0.0f)", sinhf(0.0f));
    print_float_result("T522.2", "sinhf(-0.0f)", sinhf(-0.0f));
    print_float_result("T522.3", "sinhf(1.0f)", sinhf(1.0f));
    print_float_result("T522.4", "sinhf(80.0f)", sinhf(80.0f));
    print_float_result("T522.5", "sinhf(INFINITY)", sinhf(INFINITY));
}
#endif


#ifdef RUN_T523
static void test_T523(void) {
    print_double_result("T523.1", "sqrt(0x1p-1022)", sqrt(0x1p-1022));
    print_double_result("T523.2", "sqrt(-0.0)", sqrt(-0.0));
    print_double_result("T523.3", "sqrt(INFINITY)", sqrt(INFINITY));
    print_double_result("T523.4", "sqrt(NAN)", sqrt(NAN));
}
#endif


#ifdef RUN_T524
static void test_T524(void) {
    print_double_result("T524.1", "tan(0.0)", tan(0.0));
    print_double_result("T524.2", "tan(-0.0)", tan(-0.0));
    print_double_result("T524.3", "tan(0x1p+1000)", tan(0x1p+1000));
    print_double_result("T524.4", "tan(NAN)", tan(NAN));
}
#endif


#ifdef RUN_T525
static void test_T525(void) {
    print_float_result("T525.1", "tanf(0.0f)", tanf(0.0f));
    print_float_result("T525.2", "tanf(-0.0f)", tanf(-0.0f));
    print_float_result("T525.3", "tanf(0x1p+120f)", tanf(0x1p+120f));
    print_float_result("T525.4", "tanf(NAN)", tanf(NAN));
}
#endif


#ifdef RUN_T526
static void test_T526(void) {
    print_float_result("T526.1", "tanhf(0.0f)", tanhf(0.0f));
    print_float_result("T526.2", "tanhf(-0.0f)", tanhf(-0.0f));
    print_float_result("T526.3", "tanhf(1.0f)", tanhf(1.0f));
    print_float_result("T526.4", "tanhf(-9.0f)", tanhf(-9.0f));
    print_float_result("T526.5", "tanhf(INFINITY)", tanhf(INFINITY));
}
#endif


#ifdef RUN_T527
static void test_T527(void) {
    print_double_result("T527.1", "trunc(-1.75)", trunc(-1.75));
    print_double_result("T527.2", "trunc(1.75)", trunc(1.75));
    print_double_result("T527.3", "trunc(-0.0)", trunc(-0.0));
    print_double_result("T527.4", "trunc(0x1p+52)", trunc(0x1p+52));
    print_double_result("T527.5", "trunc(INFINITY)", trunc(INFINITY));
    print_double_result("T527.6", "trunc(NAN)", trunc(NAN));
}
#endif


#ifdef RUN_T528
static void test_T528(void) {
    print_float_result("T528.1", "truncf(-1.75f)", truncf(-1.75f));
    print_float_result("T528.2", "truncf(1.75f)", truncf(1.75f));
    print_float_result("T528.3", "truncf(-0.0f)", truncf(-0.0f));
    print_float_result("T528.4", "truncf(0x1p+23f)", truncf(0x1p+23f));
    print_float_result("T528.5", "truncf(INFINITY)", truncf(INFINITY));
    print_float_result("T528.6", "truncf(NAN)", truncf(NAN));
}
#endif


#ifdef RUN_T529
static void test_T529(void) {
    print_double_result("T529.1", "y0(0.125)", y0(0.125));
    print_double_result("T529.2", "y0(1.0)", y0(1.0));
    print_double_result("T529.3", "y0(1e6)", y0(1e6));
}
#endif


#ifdef RUN_T530
static void test_T530(void) {
    print_double_result("T530.1", "y1(0.125)", y1(0.125));
    print_double_result("T530.2", "y1(1.0)", y1(1.0));
    print_double_result("T530.3", "y1(1e6)", y1(1e6));
}
#endif


#ifdef RUN_T531
static void test_T531(void) {
    print_double_result("T531.1", "yn(2, 0.125)", yn(2, 0.125));
    print_double_result("T531.2", "yn(5, 1.0)", yn(5, 1.0));
    print_double_result("T531.3", "yn(20, 1e6)", yn(20, 1e6));
}
#endif


#ifdef RUN_T532
static void test_T532(void) {
    print_double_result("T532.1", "acos(-1.0)", acos(-1.0));
    print_double_result("T532.2", "acos(nextafter(-1.0, 0.0))", acos(nextafter(-1.0, 0.0)));
    print_double_result("T532.3", "acos(-0.0)", acos(-0.0));
    print_double_result("T532.4", "acos(nextafter(1.0, 0.0))", acos(nextafter(1.0, 0.0)));
    print_double_result("T532.5", "acos(1.0)", acos(1.0));
    print_double_result("T532.6", "acos(nextafter(1.0, 2.0))", acos(nextafter(1.0, 2.0)));
    print_double_result("T532.7", "acos(NAN)", acos(NAN));
}
#endif


#ifdef RUN_T533
static void test_T533(void) {
    print_float_result("T533.1", "acosf(-1.0f)", acosf(-1.0f));
    print_float_result("T533.2", "acosf(nextafterf(-1.0f, 0.0f))", acosf(nextafterf(-1.0f, 0.0f)));
    print_float_result("T533.3", "acosf(-0.0f)", acosf(-0.0f));
    print_float_result("T533.4", "acosf(nextafterf(1.0f, 0.0f))", acosf(nextafterf(1.0f, 0.0f)));
    print_float_result("T533.5", "acosf(1.0f)", acosf(1.0f));
    print_float_result("T533.6", "acosf(nextafterf(1.0f, 2.0f))", acosf(nextafterf(1.0f, 2.0f)));
    print_float_result("T533.7", "acosf(NAN)", acosf(NAN));
}
#endif


#ifdef RUN_T534
static void test_T534(void) {
    print_float_result("T534.1", "acoshf(0.5f)", acoshf(0.5f));
    print_float_result("T534.2", "acoshf(1.0f)", acoshf(1.0f));
    print_float_result("T534.3", "acoshf(1.25f)", acoshf(1.25f));
    print_float_result("T534.4", "acoshf(8.0f)", acoshf(8.0f));
    print_float_result("T534.5", "acoshf(INFINITY)", acoshf(INFINITY));
    print_float_result("T534.6", "acoshf(NAN)", acoshf(NAN));
}
#endif


#ifdef RUN_T535
static void test_T535(void) {
    print_double_result("T535.1", "asin(-1.0)", asin(-1.0));
    print_double_result("T535.2", "asin(nextafter(-1.0, 0.0))", asin(nextafter(-1.0, 0.0)));
    print_double_result("T535.3", "asin(-0.0)", asin(-0.0));
    print_double_result("T535.4", "asin(nextafter(1.0, 0.0))", asin(nextafter(1.0, 0.0)));
    print_double_result("T535.5", "asin(1.0)", asin(1.0));
    print_double_result("T535.6", "asin(nextafter(1.0, 2.0))", asin(nextafter(1.0, 2.0)));
    print_double_result("T535.7", "asin(NAN)", asin(NAN));
}
#endif


#ifdef RUN_T536
static void test_T536(void) {
    print_float_result("T536.1", "asinf(-1.0f)", asinf(-1.0f));
    print_float_result("T536.2", "asinf(nextafterf(-1.0f, 0.0f))", asinf(nextafterf(-1.0f, 0.0f)));
    print_float_result("T536.3", "asinf(-0.0f)", asinf(-0.0f));
    print_float_result("T536.4", "asinf(nextafterf(1.0f, 0.0f))", asinf(nextafterf(1.0f, 0.0f)));
    print_float_result("T536.5", "asinf(1.0f)", asinf(1.0f));
    print_float_result("T536.6", "asinf(nextafterf(1.0f, 2.0f))", asinf(nextafterf(1.0f, 2.0f)));
    print_float_result("T536.7", "asinf(NAN)", asinf(NAN));
}
#endif


#ifdef RUN_T537
static void test_T537(void) {
    print_double_result("T537.1", "atan2(0.0, 0.0)", atan2(0.0, 0.0));
    print_double_result("T537.2", "atan2(-0.0, 0.0)", atan2(-0.0, 0.0));
    print_double_result("T537.3", "atan2(0.0, -0.0)", atan2(0.0, -0.0));
    print_double_result("T537.4", "atan2(-0.0, -0.0)", atan2(-0.0, -0.0));
    print_double_result("T537.5", "atan2(3.0, -2.0)", atan2(3.0, -2.0));
    print_double_result("T537.6", "atan2(-3.0, -2.0)", atan2(-3.0, -2.0));
    print_double_result("T537.7", "atan2(INFINITY, -INFINITY)", atan2(INFINITY, -INFINITY));
    print_double_result("T537.8", "atan2(-INFINITY, INFINITY)", atan2(-INFINITY, INFINITY));
}
#endif


#ifdef RUN_T538
static void test_T538(void) {
    print_float_result("T538.1", "atan2f(0.0f, 0.0f)", atan2f(0.0f, 0.0f));
    print_float_result("T538.2", "atan2f(-0.0f, 0.0f)", atan2f(-0.0f, 0.0f));
    print_float_result("T538.3", "atan2f(0.0f, -0.0f)", atan2f(0.0f, -0.0f));
    print_float_result("T538.4", "atan2f(-0.0f, -0.0f)", atan2f(-0.0f, -0.0f));
    print_float_result("T538.5", "atan2f(3.0f, -2.0f)", atan2f(3.0f, -2.0f));
    print_float_result("T538.6", "atan2f(-3.0f, -2.0f)", atan2f(-3.0f, -2.0f));
    print_float_result("T538.7", "atan2f(INFINITY, -INFINITY)", atan2f(INFINITY, -INFINITY));
    print_float_result("T538.8", "atan2f(-INFINITY, INFINITY)", atan2f(-INFINITY, INFINITY));
}
#endif


#ifdef RUN_T539
static void test_T539(void) {
    print_double_result("T539.1", "atan(0.0)", atan(0.0));
    print_double_result("T539.2", "atan(-0.0)", atan(-0.0));
    print_double_result("T539.3", "atan(0x0.0000000000001p-1022)", atan(0x0.0000000000001p-1022));
    print_double_result("T539.4", "atan(1.0)", atan(1.0));
    print_double_result("T539.5", "atan(nextafter(1.0, 2.0))", atan(nextafter(1.0, 2.0)));
    print_double_result("T539.6", "atan(0x1p+100)", atan(0x1p+100));
    print_double_result("T539.7", "atan(INFINITY)", atan(INFINITY));
    print_double_result("T539.8", "atan(NAN)", atan(NAN));
}
#endif


#ifdef RUN_T540
static void test_T540(void) {
    print_float_result("T540.1", "atanf(0.0f)", atanf(0.0f));
    print_float_result("T540.2", "atanf(-0.0f)", atanf(-0.0f));
    print_float_result("T540.3", "atanf(0x1p-149f)", atanf(0x1p-149f));
    print_float_result("T540.4", "atanf(1.0f)", atanf(1.0f));
    print_float_result("T540.5", "atanf(nextafterf(1.0f, 2.0f))", atanf(nextafterf(1.0f, 2.0f)));
    print_float_result("T540.6", "atanf(0x1p+50f)", atanf(0x1p+50f));
    print_float_result("T540.7", "atanf(INFINITY)", atanf(INFINITY));
    print_float_result("T540.8", "atanf(NAN)", atanf(NAN));
}
#endif


#ifdef RUN_T541
static void test_T541(void) {
    print_double_result("T541.1", "atanh(0x1p-1074)", atanh(0x1p-1074));
    print_double_result("T541.2", "atanh(-0x1p-1074)", atanh(-0x1p-1074));
    print_double_result("T541.3", "atanh(nextafter(1.0, 0.0))", atanh(nextafter(1.0, 0.0)));
    print_double_result("T541.4", "atanh(nextafter(-1.0, 0.0))", atanh(nextafter(-1.0, 0.0)));
    print_double_result("T541.5", "atanh(1.0)", atanh(1.0));
    print_double_result("T541.6", "atanh(-1.0)", atanh(-1.0));
    print_double_result("T541.7", "atanh(1.25)", atanh(1.25));
}
#endif


#ifdef RUN_T542
static void test_T542(void) {
    print_lgamma_double_result("T542.1", "lgamma(-0.5)", -0.5);
    print_lgamma_double_result("T542.2", "lgamma(-1.5)", -1.5);
    print_lgamma_double_result("T542.3", "lgamma(-2.5)", -2.5);
    print_lgamma_double_result("T542.4", "lgamma(-3.0)", -3.0);
    print_lgamma_double_result("T542.5", "lgamma(-4.0)", -4.0);
}
#endif


#ifdef RUN_T543
static void test_T543(void) {
    print_double_result("T543.1", "ceil(-0.0)", ceil(-0.0));
    print_double_result("T543.2", "ceil(-0x1p-1074)", ceil(-0x1p-1074));
    print_double_result("T543.3", "ceil(-1.0000000000000002)", ceil(-1.0000000000000002));
    print_double_result("T543.4", "ceil(1.0000000000000002)", ceil(1.0000000000000002));
    print_double_result("T543.5", "ceil(2.0)", ceil(2.0));
    print_double_result("T543.6", "ceil(0x1p+52)", ceil(0x1p+52));
    print_double_result("T543.7", "ceil(INFINITY)", ceil(INFINITY));
    print_double_result("T543.8", "ceil(NAN)", ceil(NAN));
}
#endif


#ifdef RUN_T544
static void test_T544(void) {
    print_float_result("T544.1", "ceilf(-0.0f)", ceilf(-0.0f));
    print_float_result("T544.2", "ceilf(-0x1p-149f)", ceilf(-0x1p-149f));
    print_float_result("T544.3", "ceilf(-1.0000001f)", ceilf(-1.0000001f));
    print_float_result("T544.4", "ceilf(1.0000001f)", ceilf(1.0000001f));
    print_float_result("T544.5", "ceilf(2.0f)", ceilf(2.0f));
    print_float_result("T544.6", "ceilf(0x1p+23f)", ceilf(0x1p+23f));
    print_float_result("T544.7", "ceilf(INFINITY)", ceilf(INFINITY));
    print_float_result("T544.8", "ceilf(NAN)", ceilf(NAN));
}
#endif


#ifdef RUN_T545
static void test_T545(void) {
    print_double_result("T545.1", "cos(0.0)", cos(0.0));
    print_double_result("T545.2", "cos(-0.0)", cos(-0.0));
    print_double_result("T545.3", "cos(M_PI_2)", cos(M_PI_2));
    print_double_result("T545.4", "cos(nextafter(M_PI_2, 0.0))", cos(nextafter(M_PI_2, 0.0)));
    print_double_result("T545.5", "cos(0x1p20 * M_PI)", cos(0x1p20 * M_PI));
    print_double_result("T545.6", "cos(0x1p60)", cos(0x1p60));
    print_double_result("T545.7", "cos(NAN)", cos(NAN));
}
#endif


#ifdef RUN_T546
static void test_T546(void) {
    print_float_result("T546.1", "cosf(0.0f)", cosf(0.0f));
    print_float_result("T546.2", "cosf(-0.0f)", cosf(-0.0f));
    print_float_result("T546.3", "cosf((float)M_PI_2)", cosf((float)M_PI_2));
    print_float_result("T546.4", "cosf(nextafterf((float)M_PI_2, 0.0f))", cosf(nextafterf((float)M_PI_2, 0.0f)));
    print_float_result("T546.5", "cosf(0x1p20f * (float)M_PI)", cosf(0x1p20f * (float)M_PI));
    print_float_result("T546.6", "cosf(0x1p30f)", cosf(0x1p30f));
    print_float_result("T546.7", "cosf(NAN)", cosf(NAN));
}
#endif


#ifdef RUN_T547
static void test_T547(void) {
    print_double_result("T547.1", "cosh(0.0)", cosh(0.0));
    print_double_result("T547.2", "cosh(-0.0)", cosh(-0.0));
    print_double_result("T547.3", "cosh(1.0)", cosh(1.0));
    print_double_result("T547.4", "cosh(22.0)", cosh(22.0));
    print_double_result("T547.5", "cosh(710.0)", cosh(710.0));
    print_double_result("T547.6", "cosh(INFINITY)", cosh(INFINITY));
    print_double_result("T547.7", "cosh(NAN)", cosh(NAN));
}
#endif


#ifdef RUN_T548
static void test_T548(void) {
    print_float_result("T548.1", "coshf(0.0f)", coshf(0.0f));
    print_float_result("T548.2", "coshf(-0.0f)", coshf(-0.0f));
    print_float_result("T548.3", "coshf(1.0f)", coshf(1.0f));
    print_float_result("T548.4", "coshf(10.0f)", coshf(10.0f));
    print_float_result("T548.5", "coshf(89.0f)", coshf(89.0f));
    print_float_result("T548.6", "coshf(INFINITY)", coshf(INFINITY));
    print_float_result("T548.7", "coshf(NAN)", coshf(NAN));
}
#endif


#ifdef RUN_T549
static void test_T549(void) {
    print_double_complex_result("T549.1", "csqrt(CMPLX(-4.0, 0.0))", csqrt(CMPLX(-4.0, 0.0)));
    print_double_complex_result("T549.2", "csqrt(CMPLX(-4.0, -0.0))", csqrt(CMPLX(-4.0, -0.0)));
    print_double_complex_result("T549.3", "csqrt(CMPLX(3.0, 4.0))", csqrt(CMPLX(3.0, 4.0)));
    print_double_complex_result("T549.4", "csqrt(CMPLX(INFINITY, 1.0))", csqrt(CMPLX(INFINITY, 1.0)));
    print_double_complex_result("T549.5", "csqrt(CMPLX(NAN, 2.0))", csqrt(CMPLX(NAN, 2.0)));
}
#endif


#ifdef RUN_T550
static void test_T550(void) {
    print_float_complex_result("T550.1", "csqrtf(CMPLXF(-4.0f, 0.0f))", csqrtf(CMPLXF(-4.0f, 0.0f)));
    print_float_complex_result("T550.2", "csqrtf(CMPLXF(-4.0f, -0.0f))", csqrtf(CMPLXF(-4.0f, -0.0f)));
    print_float_complex_result("T550.3", "csqrtf(CMPLXF(3.0f, 4.0f))", csqrtf(CMPLXF(3.0f, 4.0f)));
    print_float_complex_result("T550.4", "csqrtf(CMPLXF(INFINITY, 1.0f))", csqrtf(CMPLXF(INFINITY, 1.0f)));
    print_float_complex_result("T550.5", "csqrtf(CMPLXF(NAN, 2.0f))", csqrtf(CMPLXF(NAN, 2.0f)));
}
#endif


#ifdef RUN_T551
static void test_T551(void) {
    print_double_complex_result("T551.1", "ctan(CMPLX(0.0, 0.0))", ctan(CMPLX(0.0, 0.0)));
    print_double_complex_result("T551.2", "ctan(CMPLX(M_PI_2, 0.0))", ctan(CMPLX(M_PI_2, 0.0)));
    print_double_complex_result("T551.3", "ctan(CMPLX(0.0, 20.0))", ctan(CMPLX(0.0, 20.0)));
    print_double_complex_result("T551.4", "ctan(CMPLX(1.0, 20.0))", ctan(CMPLX(1.0, 20.0)));
    print_double_complex_result("T551.5", "ctan(CMPLX(INFINITY, 1.0))", ctan(CMPLX(INFINITY, 1.0)));
    print_double_complex_result("T551.6", "ctan(CMPLX(NAN, -0.0))", ctan(CMPLX(NAN, -0.0)));
}
#endif


#ifdef RUN_T552
static void test_T552(void) {
    print_float_complex_result("T552.1", "ctanf(CMPLXF(0.0f, 0.0f))", ctanf(CMPLXF(0.0f, 0.0f)));
    print_float_complex_result("T552.2", "ctanf(CMPLXF((float)M_PI_2, 0.0f))", ctanf(CMPLXF((float)M_PI_2, 0.0f)));
    print_float_complex_result("T552.3", "ctanf(CMPLXF(0.0f, 12.0f))", ctanf(CMPLXF(0.0f, 12.0f)));
    print_float_complex_result("T552.4", "ctanf(CMPLXF(1.0f, 12.0f))", ctanf(CMPLXF(1.0f, 12.0f)));
    print_float_complex_result("T552.5", "ctanf(CMPLXF(INFINITY, 1.0f))", ctanf(CMPLXF(INFINITY, 1.0f)));
    print_float_complex_result("T552.6", "ctanf(CMPLXF(NAN, -0.0f))", ctanf(CMPLXF(NAN, -0.0f)));
}
#endif


#ifdef RUN_T553
static void test_T553(void) {
    print_double_complex_result("T553.1", "csin(CMPLX(0x1p60, 1.0))", csin(CMPLX(0x1p60, 1.0)));
    print_double_complex_result("T553.2", "ccos(CMPLX(0x1p60, -1.0))", ccos(CMPLX(0x1p60, -1.0)));
    print_double_complex_result("T553.3", "ctan(CMPLX(0.0, INFINITY))", ctan(CMPLX(0.0, INFINITY)));
    print_double_complex_result("T553.4", "ccos(CMPLX(INFINITY, NAN))", ccos(CMPLX(INFINITY, NAN)));
    print_double_complex_result("T553.5", "csin(CMPLX(NAN, -0.0))", csin(CMPLX(NAN, -0.0)));
}
#endif


#ifdef RUN_T554
static void test_T554(void) {
    print_float_complex_result("T554.1", "csinf(CMPLXF(0x1p30f, 1.0f))", csinf(CMPLXF(0x1p30f, 1.0f)));
    print_float_complex_result("T554.2", "ccosf(CMPLXF(0x1p30f, -1.0f))", ccosf(CMPLXF(0x1p30f, -1.0f)));
    print_float_complex_result("T554.3", "ctanf(CMPLXF(0.0f, INFINITY))", ctanf(CMPLXF(0.0f, INFINITY)));
    print_float_complex_result("T554.4", "ccosf(CMPLXF(INFINITY, NAN))", ccosf(CMPLXF(INFINITY, NAN)));
    print_float_complex_result("T554.5", "csinf(CMPLXF(NAN, -0.0f))", csinf(CMPLXF(NAN, -0.0f)));
}
#endif


#ifdef RUN_T555
static void test_T555(void) {
    print_double_result("T555.1", "erfc(0.0)", erfc(0.0));
    print_double_result("T555.2", "erfc(0.84375)", erfc(0.84375));
    print_double_result("T555.3", "erfc(1.25)", erfc(1.25));
    print_double_result("T555.4", "erfc(2.857143)", erfc(2.857143));
    print_double_result("T555.5", "erfc(28.0)", erfc(28.0));
    print_double_result("T555.6", "erfc(INFINITY)", erfc(INFINITY));
    print_double_result("T555.7", "erfc(NAN)", erfc(NAN));
}
#endif


#ifdef RUN_T556
static void test_T556(void) {
    print_float_result("T556.1", "erfcf(0.0f)", erfcf(0.0f));
    print_float_result("T556.2", "erfcf(0.84375f)", erfcf(0.84375f));
    print_float_result("T556.3", "erfcf(1.25f)", erfcf(1.25f));
    print_float_result("T556.4", "erfcf(2.857143f)", erfcf(2.857143f));
    print_float_result("T556.5", "erfcf(10.0f)", erfcf(10.0f));
    print_float_result("T556.6", "erfcf(INFINITY)", erfcf(INFINITY));
    print_float_result("T556.7", "erfcf(NAN)", erfcf(NAN));
}
#endif


#ifdef RUN_T557
static void test_T557(void) {
    print_float_result("T557.1", "erff(0.0f)", erff(0.0f));
    print_float_result("T557.2", "erff(-0.0f)", erff(-0.0f));
    print_float_result("T557.3", "erff(0.84375f)", erff(0.84375f));
    print_float_result("T557.4", "erff(1.25f)", erff(1.25f));
    print_float_result("T557.5", "erff(3.5f)", erff(3.5f));
    print_float_result("T557.6", "erff(NAN)", erff(NAN));
}
#endif


#ifdef RUN_T558
static void test_T558(void) {
    print_double_result("T558.1", "exp(-745.0)", exp(-745.0));
    print_double_result("T558.2", "exp(-0x1p-1074)", exp(-0x1p-1074));
    print_double_result("T558.3", "exp(0.0)", exp(0.0));
    print_double_result("T558.4", "exp(709.0)", exp(709.0));
    print_double_result("T558.5", "exp(INFINITY)", exp(INFINITY));
    print_double_result("T558.6", "exp(-INFINITY)", exp(-INFINITY));
    print_double_result("T558.7", "exp(NAN)", exp(NAN));
}
#endif


#ifdef RUN_T559
static void test_T559(void) {
    print_double_result("T559.1", "expm1(0.0)", expm1(0.0));
    print_double_result("T559.2", "expm1(-0.0)", expm1(-0.0));
    print_double_result("T559.3", "expm1(0x1p-1074)", expm1(0x1p-1074));
    print_double_result("T559.4", "expm1(-0x1p-1074)", expm1(-0x1p-1074));
    print_double_result("T559.5", "expm1(0x1p-30)", expm1(0x1p-30));
    print_double_result("T559.6", "expm1(20.0)", expm1(20.0));
    print_double_result("T559.7", "expm1(-20.0)", expm1(-20.0));
}
#endif


#ifdef RUN_T560
static void test_T560(void) {
    print_float_result("T560.1", "expm1f(0.0f)", expm1f(0.0f));
    print_float_result("T560.2", "expm1f(-0.0f)", expm1f(-0.0f));
    print_float_result("T560.3", "expm1f(0x1p-149f)", expm1f(0x1p-149f));
    print_float_result("T560.4", "expm1f(-0x1p-149f)", expm1f(-0x1p-149f));
    print_float_result("T560.5", "expm1f(0x1p-20f)", expm1f(0x1p-20f));
    print_float_result("T560.6", "expm1f(10.0f)", expm1f(10.0f));
    print_float_result("T560.7", "expm1f(-10.0f)", expm1f(-10.0f));
}
#endif


#ifdef RUN_T561
static void test_T561(void) {
    print_double_result("T561.1", "floor(0.0)", floor(0.0));
    print_double_result("T561.2", "floor(-0.0)", floor(-0.0));
    print_double_result("T561.3", "floor(0x1p-1074)", floor(0x1p-1074));
    print_double_result("T561.4", "floor(-1.9999999999999998)", floor(-1.9999999999999998));
    print_double_result("T561.5", "floor(1.9999999999999998)", floor(1.9999999999999998));
    print_double_result("T561.6", "floor(2.0)", floor(2.0));
    print_double_result("T561.7", "floor(0x1p+52)", floor(0x1p+52));
    print_double_result("T561.8", "floor(INFINITY)", floor(INFINITY));
    print_double_result("T561.9", "floor(NAN)", floor(NAN));
}
#endif


#ifdef RUN_T562
static void test_T562(void) {
    print_float_result("T562.1", "floorf(0.0f)", floorf(0.0f));
    print_float_result("T562.2", "floorf(-0.0f)", floorf(-0.0f));
    print_float_result("T562.3", "floorf(0x1p-149f)", floorf(0x1p-149f));
    print_float_result("T562.4", "floorf(-1.9999999f)", floorf(-1.9999999f));
    print_float_result("T562.5", "floorf(1.9999999f)", floorf(1.9999999f));
    print_float_result("T562.6", "floorf(2.0f)", floorf(2.0f));
    print_float_result("T562.7", "floorf(0x1p+23f)", floorf(0x1p+23f));
    print_float_result("T562.8", "floorf(INFINITY)", floorf(INFINITY));
    print_float_result("T562.9", "floorf(NAN)", floorf(NAN));
}
#endif


#ifdef RUN_T563
static void test_T563(void) {
    print_double_result("T563.1", "fmax(1.0, 2.0)", fmax(1.0, 2.0));
    print_double_result("T563.2", "fmax(2.0, 1.0)", fmax(2.0, 1.0));
    print_double_result("T563.3", "fmax(NAN, 1.0)", fmax(NAN, 1.0));
    print_double_result("T563.4", "fmax(1.0, NAN)", fmax(1.0, NAN));
    print_double_result("T563.5", "fmax(NAN, NAN)", fmax(NAN, NAN));
    print_double_result("T563.6", "fmax(0.0, -0.0)", fmax(0.0, -0.0));
    print_double_result("T563.7", "fmax(-0.0, 0.0)", fmax(-0.0, 0.0));
}
#endif


#ifdef RUN_T564
static void test_T564(void) {
    print_float_result("T564.1", "fmaxf(1.0f, 2.0f)", fmaxf(1.0f, 2.0f));
    print_float_result("T564.2", "fmaxf(2.0f, 1.0f)", fmaxf(2.0f, 1.0f));
    print_float_result("T564.3", "fmaxf(NAN, 1.0f)", fmaxf(NAN, 1.0f));
    print_float_result("T564.4", "fmaxf(1.0f, NAN)", fmaxf(1.0f, NAN));
    print_float_result("T564.5", "fmaxf(NAN, NAN)", fmaxf(NAN, NAN));
    print_float_result("T564.6", "fmaxf(0.0f, -0.0f)", fmaxf(0.0f, -0.0f));
    print_float_result("T564.7", "fmaxf(-0.0f, 0.0f)", fmaxf(-0.0f, 0.0f));
}
#endif


#ifdef RUN_T565
static void test_T565(void) {
    print_double_result("T565.1", "fmin(1.0, 2.0)", fmin(1.0, 2.0));
    print_double_result("T565.2", "fmin(2.0, 1.0)", fmin(2.0, 1.0));
    print_double_result("T565.3", "fmin(NAN, 1.0)", fmin(NAN, 1.0));
    print_double_result("T565.4", "fmin(1.0, NAN)", fmin(1.0, NAN));
    print_double_result("T565.5", "fmin(NAN, NAN)", fmin(NAN, NAN));
    print_double_result("T565.6", "fmin(0.0, -0.0)", fmin(0.0, -0.0));
    print_double_result("T565.7", "fmin(-0.0, 0.0)", fmin(-0.0, 0.0));
}
#endif


#ifdef RUN_T566
static void test_T566(void) {
    print_float_result("T566.1", "fminf(1.0f, 2.0f)", fminf(1.0f, 2.0f));
    print_float_result("T566.2", "fminf(2.0f, 1.0f)", fminf(2.0f, 1.0f));
    print_float_result("T566.3", "fminf(NAN, 1.0f)", fminf(NAN, 1.0f));
    print_float_result("T566.4", "fminf(1.0f, NAN)", fminf(1.0f, NAN));
    print_float_result("T566.5", "fminf(NAN, NAN)", fminf(NAN, NAN));
    print_float_result("T566.6", "fminf(0.0f, -0.0f)", fminf(0.0f, -0.0f));
    print_float_result("T566.7", "fminf(-0.0f, 0.0f)", fminf(-0.0f, 0.0f));
}
#endif


#ifdef RUN_T567
static void test_T567(void) {
    print_double_result("T567.1", "fmod(3.0, 3.0)", fmod(3.0, 3.0));
    print_double_result("T567.2", "fmod(2.0, 3.0)", fmod(2.0, 3.0));
    print_double_result("T567.3", "fmod(-5.0, 2.0)", fmod(-5.0, 2.0));
    print_double_result("T567.4", "fmod(0x1p-1074, 2.0)", fmod(0x1p-1074, 2.0));
    print_double_result("T567.5", "fmod(1.0, 0.0)", fmod(1.0, 0.0));
    print_double_result("T567.6", "fmod(INFINITY, 2.0)", fmod(INFINITY, 2.0));
}
#endif


#ifdef RUN_T568
static void test_T568(void) {
    print_float_result("T568.1", "fmodf(3.0f, 3.0f)", fmodf(3.0f, 3.0f));
    print_float_result("T568.2", "fmodf(2.0f, 3.0f)", fmodf(2.0f, 3.0f));
    print_float_result("T568.3", "fmodf(-5.0f, 2.0f)", fmodf(-5.0f, 2.0f));
    print_float_result("T568.4", "fmodf(0x1p-149f, 2.0f)", fmodf(0x1p-149f, 2.0f));
    print_float_result("T568.5", "fmodf(1.0f, 0.0f)", fmodf(1.0f, 0.0f));
    print_float_result("T568.6", "fmodf(INFINITY, 2.0f)", fmodf(INFINITY, 2.0f));
}
#endif


#ifdef RUN_T569
static void test_T569(void) {
    print_classification_result("T569.1", "fpclassify(0.0)", 0.0);
    print_classification_result("T569.2", "fpclassify(0x1p-1074)", 0x1p-1074);
    print_classification_result("T569.3", "fpclassify(DBL_MIN)", DBL_MIN);
    print_classification_result("T569.4", "fpclassify(INFINITY)", INFINITY);
    print_classification_result("T569.5", "fpclassify(NAN)", NAN);
}
#endif


#ifdef RUN_T570
static void test_T570(void) {
    double value;
    int exp;
    exp = 0;
    value = frexp(0.0, &exp);
    print_double_int_pair_result("T570.1", "frexp(0.0, &exp)", value, exp);
    exp = 0;
    value = frexp(0x1p-1074, &exp);
    print_double_int_pair_result("T570.2", "frexp(0x1p-1074, &exp)", value, exp);
    exp = 0;
    value = frexp(6.5, &exp);
    print_double_int_pair_result("T570.3", "frexp(6.5, &exp)", value, exp);
    exp = 0;
    value = frexp(INFINITY, &exp);
    print_double_int_pair_result("T570.4", "frexp(INFINITY, &exp)", value, exp);
    exp = 0;
    value = frexp(NAN, &exp);
    print_double_int_pair_result("T570.5", "frexp(NAN, &exp)", value, exp);
}
#endif


#ifdef RUN_T571
static void test_T571(void) {
    float value;
    int exp;
    exp = 0;
    value = frexpf(0.0f, &exp);
    print_float_int_pair_result("T571.1", "frexpf(0.0f, &exp)", value, exp);
    exp = 0;
    value = frexpf(0x1p-149f, &exp);
    print_float_int_pair_result("T571.2", "frexpf(0x1p-149f, &exp)", value, exp);
    exp = 0;
    value = frexpf(6.5f, &exp);
    print_float_int_pair_result("T571.3", "frexpf(6.5f, &exp)", value, exp);
    exp = 0;
    value = frexpf(INFINITY, &exp);
    print_float_int_pair_result("T571.4", "frexpf(INFINITY, &exp)", value, exp);
    exp = 0;
    value = frexpf(NAN, &exp);
    print_float_int_pair_result("T571.5", "frexpf(NAN, &exp)", value, exp);
}
#endif


#ifdef RUN_T572
static void test_T572(void) {
    print_lgamma_float_result("T572.1", "lgammaf(-0.5f)", -0.5f);
    print_lgamma_float_result("T572.2", "lgammaf(-1.5f)", -1.5f);
    print_lgamma_float_result("T572.3", "lgammaf(-2.5f)", -2.5f);
    print_lgamma_float_result("T572.4", "lgammaf(-3.0f)", -3.0f);
    print_lgamma_float_result("T572.5", "lgammaf(-4.0f)", -4.0f);
}
#endif


#ifdef RUN_T573
static void test_T573(void) {
    print_double_result("T573.1", "hypot(0.0, 0.0)", hypot(0.0, 0.0));
    print_double_result("T573.2", "hypot(-0x1p-1074, 0x1p-1074)", hypot(-0x1p-1074, 0x1p-1074));
    print_double_result("T573.3", "hypot(DBL_MAX, 0x1p-1074)", hypot(DBL_MAX, 0x1p-1074));
    print_double_result("T573.4", "hypot(3.0, 4.0)", hypot(3.0, 4.0));
    print_double_result("T573.5", "hypot(INFINITY, NAN)", hypot(INFINITY, NAN));
    print_double_result("T573.6", "hypot(NAN, 1.0)", hypot(NAN, 1.0));
}
#endif


#ifdef RUN_T574
static void test_T574(void) {
    print_int_result("T574.1", "ilogb(0.0)", ilogb(0.0));
    print_int_result("T574.2", "ilogb(0x1p-1074)", ilogb(0x1p-1074));
    print_int_result("T574.3", "ilogb(0.5)", ilogb(0.5));
    print_int_result("T574.4", "ilogb(1.0)", ilogb(1.0));
    print_int_result("T574.5", "ilogb(2.0)", ilogb(2.0));
    print_int_result("T574.6", "ilogb(INFINITY)", ilogb(INFINITY));
    print_int_result("T574.7", "ilogb(NAN)", ilogb(NAN));
}
#endif


#ifdef RUN_T575
static void test_T575(void) {
    print_double_result("T575.1", "j0(0.0)", j0(0.0));
    print_double_result("T575.2", "j0(2.0)", j0(2.0));
    print_double_result("T575.3", "j0(5.0)", j0(5.0));
    print_double_result("T575.4", "j0(1e6)", j0(1e6));
}
#endif


#ifdef RUN_T576
static void test_T576(void) {
    print_double_result("T576.1", "j1(0.0)", j1(0.0));
    print_double_result("T576.2", "j1(-0.0)", j1(-0.0));
    print_double_result("T576.3", "j1(2.0)", j1(2.0));
    print_double_result("T576.4", "j1(5.0)", j1(5.0));
    print_double_result("T576.5", "j1(1e6)", j1(1e6));
}
#endif


#ifdef RUN_T577
static void test_T577(void) {
    print_double_result("T577.1", "jn(0, 3.0)", jn(0, 3.0));
    print_double_result("T577.2", "jn(1, 0.0)", jn(1, 0.0));
    print_double_result("T577.3", "jn(5, 1.0)", jn(5, 1.0));
    print_double_result("T577.4", "jn(10, 20.0)", jn(10, 20.0));
    print_double_result("T577.5", "jn(20, 1e6)", jn(20, 1e6));
}
#endif


#ifdef RUN_T578
static void test_T578(void) {
    print_ll_result("T578.1", "llround(0.49999999999999994)", llround(0.49999999999999994));
    print_ll_result("T578.2", "llround(0.5)", llround(0.5));
    print_ll_result("T578.3", "llround(-0.5)", llround(-0.5));
    print_ll_result("T578.4", "llround(4503599627370495.5)", llround(4503599627370495.5));
    print_ll_result("T578.5", "llround(INFINITY)", llround(INFINITY));
    print_ll_result("T578.6", "llround(NAN)", llround(NAN));
}
#endif


#ifdef RUN_T579
static void test_T579(void) {
    print_double_result("T579.1", "log10(0x1p-1074)", log10(0x1p-1074));
    print_double_result("T579.2", "log10(nextafter(1.0, 0.0))", log10(nextafter(1.0, 0.0)));
    print_double_result("T579.3", "log10(1.0)", log10(1.0));
    print_double_result("T579.4", "log10(0.0)", log10(0.0));
    print_double_result("T579.5", "log10(-1.0)", log10(-1.0));
    print_double_result("T579.6", "log10(INFINITY)", log10(INFINITY));
    print_double_result("T579.7", "log10(NAN)", log10(NAN));
}
#endif


#ifdef RUN_T580
static void test_T580(void) {
    print_double_result("T580.1", "log1p(0x1p-54)", log1p(0x1p-54));
    print_double_result("T580.2", "log1p(-0x1p-54)", log1p(-0x1p-54));
    print_double_result("T580.3", "log1p(nextafter(-1.0, 0.0))", log1p(nextafter(-1.0, 0.0)));
    print_double_result("T580.4", "log1p(-1.0)", log1p(-1.0));
    print_double_result("T580.5", "log1p(-1.25)", log1p(-1.25));
    print_double_result("T580.6", "log1p(1e6)", log1p(1e6));
}
#endif


#ifdef RUN_T581
static void test_T581(void) {
    print_float_result("T581.1", "log1pf(0x1p-25f)", log1pf(0x1p-25f));
    print_float_result("T581.2", "log1pf(-0x1p-25f)", log1pf(-0x1p-25f));
    print_float_result("T581.3", "log1pf(nextafterf(-1.0f, 0.0f))", log1pf(nextafterf(-1.0f, 0.0f)));
    print_float_result("T581.4", "log1pf(-1.0f)", log1pf(-1.0f));
    print_float_result("T581.5", "log1pf(-1.25f)", log1pf(-1.25f));
    print_float_result("T581.6", "log1pf(1e6f)", log1pf(1e6f));
}
#endif


#ifdef RUN_T582
static void test_T582(void) {
    print_double_result("T582.1", "log2(0x1p-1074)", log2(0x1p-1074));
    print_double_result("T582.2", "log2(nextafter(1.0, 0.0))", log2(nextafter(1.0, 0.0)));
    print_double_result("T582.3", "log2(1.0)", log2(1.0));
    print_double_result("T582.4", "log2(2.0)", log2(2.0));
    print_double_result("T582.5", "log2(0.0)", log2(0.0));
    print_double_result("T582.6", "log2(-1.0)", log2(-1.0));
    print_double_result("T582.7", "log2(INFINITY)", log2(INFINITY));
    print_double_result("T582.8", "log2(NAN)", log2(NAN));
}
#endif


#ifdef RUN_T583
static void test_T583(void) {
    print_double_result("T583.1", "logb(0.0)", logb(0.0));
    print_double_result("T583.2", "logb(0x1p-1074)", logb(0x1p-1074));
    print_double_result("T583.3", "logb(1.0)", logb(1.0));
    print_double_result("T583.4", "logb(8.0)", logb(8.0));
    print_double_result("T583.5", "logb(INFINITY)", logb(INFINITY));
    print_double_result("T583.6", "logb(NAN)", logb(NAN));
}
#endif


#ifdef RUN_T584
static void test_T584(void) {
    print_double_result("T584.1", "log(0x1p-1074)", log(0x1p-1074));
    print_double_result("T584.2", "log(nextafter(1.0, 0.0))", log(nextafter(1.0, 0.0)));
    print_double_result("T584.3", "log(1.0)", log(1.0));
    print_double_result("T584.4", "log(0.0)", log(0.0));
    print_double_result("T584.5", "log(-1.0)", log(-1.0));
    print_double_result("T584.6", "log(INFINITY)", log(INFINITY));
    print_double_result("T584.7", "log(NAN)", log(NAN));
}
#endif


#ifdef RUN_T585
static void test_T585(void) {
    print_float_result("T585.1", "logf(0x1p-149f)", logf(0x1p-149f));
    print_float_result("T585.2", "logf(nextafterf(1.0f, 0.0f))", logf(nextafterf(1.0f, 0.0f)));
    print_float_result("T585.3", "logf(1.0f)", logf(1.0f));
    print_float_result("T585.4", "logf(0.0f)", logf(0.0f));
    print_float_result("T585.5", "logf(-1.0f)", logf(-1.0f));
    print_float_result("T585.6", "logf(INFINITY)", logf(INFINITY));
    print_float_result("T585.7", "logf(NAN)", logf(NAN));
}
#endif


#ifdef RUN_T586
static void test_T586(void) {
    print_long_result("T586.1", "lrint(0.49999999999999994)", lrint(0.49999999999999994));
    print_long_result("T586.2", "lrint(0.5)", lrint(0.5));
    print_long_result("T586.3", "lrint(1.5)", lrint(1.5));
    print_long_result("T586.4", "lrint(-1.5)", lrint(-1.5));
    print_long_result("T586.5", "lrint(0x1p+52)", lrint(0x1p+52));
    print_long_result("T586.6", "lrint(INFINITY)", lrint(INFINITY));
    print_long_result("T586.7", "lrint(NAN)", lrint(NAN));
}
#endif


#ifdef RUN_T587
static void test_T587(void) {
    print_long_result("T587.1", "lround(0.49999999999999994)", lround(0.49999999999999994));
    print_long_result("T587.2", "lround(0.5)", lround(0.5));
    print_long_result("T587.3", "lround(-0.5)", lround(-0.5));
    print_long_result("T587.4", "lround(1.5)", lround(1.5));
    print_long_result("T587.5", "lround(0x1p+52)", lround(0x1p+52));
    print_long_result("T587.6", "lround(INFINITY)", lround(INFINITY));
    print_long_result("T587.7", "lround(NAN)", lround(NAN));
}
#endif


#ifdef RUN_T588
static void test_T588(void) {
    double frac;
    double ipart;
    ipart = 0.0;
    frac = modf(0.0, &ipart);
    print_double_pair_result("T588.1", "modf(0.0, &ipart)", frac, ipart);
    ipart = 0.0;
    frac = modf(-0.0, &ipart);
    print_double_pair_result("T588.2", "modf(-0.0, &ipart)", frac, ipart);
    ipart = 0.0;
    frac = modf(0x1p-1074, &ipart);
    print_double_pair_result("T588.3", "modf(0x1p-1074, &ipart)", frac, ipart);
    ipart = 0.0;
    frac = modf(-3.5, &ipart);
    print_double_pair_result("T588.4", "modf(-3.5, &ipart)", frac, ipart);
    ipart = 0.0;
    frac = modf(4.0, &ipart);
    print_double_pair_result("T588.5", "modf(4.0, &ipart)", frac, ipart);
    ipart = 0.0;
    frac = modf(0x1p+52, &ipart);
    print_double_pair_result("T588.6", "modf(0x1p+52, &ipart)", frac, ipart);
    ipart = 0.0;
    frac = modf(INFINITY, &ipart);
    print_double_pair_result("T588.7", "modf(INFINITY, &ipart)", frac, ipart);
    ipart = 0.0;
    frac = modf(NAN, &ipart);
    print_double_pair_result("T588.8", "modf(NAN, &ipart)", frac, ipart);
}
#endif


#ifdef RUN_T589
static void test_T589(void) {
    float frac;
    float ipart;
    ipart = 0.0f;
    frac = modff(0.0f, &ipart);
    print_float_pair_result("T589.1", "modff(0.0f, &ipart)", frac, ipart);
    ipart = 0.0f;
    frac = modff(-0.0f, &ipart);
    print_float_pair_result("T589.2", "modff(-0.0f, &ipart)", frac, ipart);
    ipart = 0.0f;
    frac = modff(0x1p-149f, &ipart);
    print_float_pair_result("T589.3", "modff(0x1p-149f, &ipart)", frac, ipart);
    ipart = 0.0f;
    frac = modff(-3.5f, &ipart);
    print_float_pair_result("T589.4", "modff(-3.5f, &ipart)", frac, ipart);
    ipart = 0.0f;
    frac = modff(4.0f, &ipart);
    print_float_pair_result("T589.5", "modff(4.0f, &ipart)", frac, ipart);
    ipart = 0.0f;
    frac = modff(0x1p+23f, &ipart);
    print_float_pair_result("T589.6", "modff(0x1p+23f, &ipart)", frac, ipart);
    ipart = 0.0f;
    frac = modff(INFINITY, &ipart);
    print_float_pair_result("T589.7", "modff(INFINITY, &ipart)", frac, ipart);
    ipart = 0.0f;
    frac = modff(NAN, &ipart);
    print_float_pair_result("T589.8", "modff(NAN, &ipart)", frac, ipart);
}
#endif


#ifdef RUN_T590
static void test_T590(void) {
    print_double_result("T590.1", "nextafter(1.0, 1.0)", nextafter(1.0, 1.0));
    print_double_result("T590.2", "nextafter(0.0, 1.0)", nextafter(0.0, 1.0));
    print_double_result("T590.3", "nextafter(0.0, -1.0)", nextafter(0.0, -1.0));
    print_double_result("T590.4", "nextafter(DBL_MIN, 0.0)", nextafter(DBL_MIN, 0.0));
    print_double_result("T590.5", "nextafter(DBL_MAX, INFINITY)", nextafter(DBL_MAX, INFINITY));
    print_double_result("T590.6", "nextafter(NAN, 1.0)", nextafter(NAN, 1.0));
    print_double_result("T590.7", "nextafter(1.0, NAN)", nextafter(1.0, NAN));
}
#endif


#ifdef RUN_T591
static void test_T591(void) {
    print_float_result("T591.1", "nextafterf(1.0f, 1.0f)", nextafterf(1.0f, 1.0f));
    print_float_result("T591.2", "nextafterf(0.0f, 1.0f)", nextafterf(0.0f, 1.0f));
    print_float_result("T591.3", "nextafterf(0.0f, -1.0f)", nextafterf(0.0f, -1.0f));
    print_float_result("T591.4", "nextafterf(FLT_MIN, 0.0f)", nextafterf(FLT_MIN, 0.0f));
    print_float_result("T591.5", "nextafterf(FLT_MAX, INFINITY)", nextafterf(FLT_MAX, INFINITY));
    print_float_result("T591.6", "nextafterf(NAN, 1.0f)", nextafterf(NAN, 1.0f));
    print_float_result("T591.7", "nextafterf(1.0f, NAN)", nextafterf(1.0f, NAN));
}
#endif


#ifdef RUN_T592
static void test_T592(void) {
    print_double_result("T592.1", "pow(-0.0, -3.0)", pow(-0.0, -3.0));
    print_double_result("T592.2", "pow(0.0, 5.0)", pow(0.0, 5.0));
    print_double_result("T592.3", "pow(0x1p-1074, 2.0)", pow(0x1p-1074, 2.0));
    print_double_result("T592.4", "pow(-2.0, 3.0)", pow(-2.0, 3.0));
    print_double_result("T592.5", "pow(-2.0, 2.0)", pow(-2.0, 2.0));
    print_double_result("T592.6", "pow(-2.0, 0.5)", pow(-2.0, 0.5));
    print_double_result("T592.7", "pow(INFINITY, -2.0)", pow(INFINITY, -2.0));
    print_double_result("T592.8", "pow(NAN, 2.0)", pow(NAN, 2.0));
}
#endif


#ifdef RUN_T593
static void test_T593(void) {
    print_float_result("T593.1", "powf(-0.0f, -3.0f)", powf(-0.0f, -3.0f));
    print_float_result("T593.2", "powf(0.0f, 5.0f)", powf(0.0f, 5.0f));
    print_float_result("T593.3", "powf(0x1p-149f, 2.0f)", powf(0x1p-149f, 2.0f));
    print_float_result("T593.4", "powf(-2.0f, 3.0f)", powf(-2.0f, 3.0f));
    print_float_result("T593.5", "powf(-2.0f, 2.0f)", powf(-2.0f, 2.0f));
    print_float_result("T593.6", "powf(-2.0f, 0.5f)", powf(-2.0f, 0.5f));
    print_float_result("T593.7", "powf(INFINITY, -2.0f)", powf(INFINITY, -2.0f));
    print_float_result("T593.8", "powf(NAN, 2.0f)", powf(NAN, 2.0f));
}
#endif


#ifdef RUN_T594
static void test_T594(void) {
    print_double_result("T594.1", "remainder(6.0, 3.0)", remainder(6.0, 3.0));
    print_double_result("T594.2", "remainder(7.0, 2.0)", remainder(7.0, 2.0));
    print_double_result("T594.3", "remainder(-7.0, 2.0)", remainder(-7.0, 2.0));
    print_double_result("T594.4", "remainder(0x1p-1074, 2.0)", remainder(0x1p-1074, 2.0));
    print_double_result("T594.5", "remainder(1.0, 0.0)", remainder(1.0, 0.0));
    print_double_result("T594.6", "remainder(INFINITY, 2.0)", remainder(INFINITY, 2.0));
}
#endif


#ifdef RUN_T595
static void test_T595(void) {
    print_float_result("T595.1", "remainderf(6.0f, 3.0f)", remainderf(6.0f, 3.0f));
    print_float_result("T595.2", "remainderf(7.0f, 2.0f)", remainderf(7.0f, 2.0f));
    print_float_result("T595.3", "remainderf(-7.0f, 2.0f)", remainderf(-7.0f, 2.0f));
    print_float_result("T595.4", "remainderf(0x1p-149f, 2.0f)", remainderf(0x1p-149f, 2.0f));
    print_float_result("T595.5", "remainderf(1.0f, 0.0f)", remainderf(1.0f, 0.0f));
    print_float_result("T595.6", "remainderf(INFINITY, 2.0f)", remainderf(INFINITY, 2.0f));
}
#endif


#ifdef RUN_T596
static void test_T596(void) {
    double value;
    int quo;
    quo = 0;
    value = remquo(6.0, 3.0, &quo);
    print_double_int_pair_result("T596.1", "remquo(6.0, 3.0, &quo)", value, quo);
    quo = 0;
    value = remquo(7.0, 2.0, &quo);
    print_double_int_pair_result("T596.2", "remquo(7.0, 2.0, &quo)", value, quo);
    quo = 0;
    value = remquo(-7.0, 2.0, &quo);
    print_double_int_pair_result("T596.3", "remquo(-7.0, 2.0, &quo)", value, quo);
    quo = 0;
    value = remquo(0x1p-1074, 2.0, &quo);
    print_double_int_pair_result("T596.4", "remquo(0x1p-1074, 2.0, &quo)", value, quo);
    quo = 0;
    value = remquo(1.0, 0.0, &quo);
    print_double_int_pair_result("T596.5", "remquo(1.0, 0.0, &quo)", value, quo);
    quo = 0;
    value = remquo(INFINITY, 2.0, &quo);
    print_double_int_pair_result("T596.6", "remquo(INFINITY, 2.0, &quo)", value, quo);
}
#endif


#ifdef RUN_T597
static void test_T597(void) {
    float value;
    int quo;
    quo = 0;
    value = remquof(6.0f, 3.0f, &quo);
    print_float_int_pair_result("T597.1", "remquof(6.0f, 3.0f, &quo)", value, quo);
    quo = 0;
    value = remquof(7.0f, 2.0f, &quo);
    print_float_int_pair_result("T597.2", "remquof(7.0f, 2.0f, &quo)", value, quo);
    quo = 0;
    value = remquof(-7.0f, 2.0f, &quo);
    print_float_int_pair_result("T597.3", "remquof(-7.0f, 2.0f, &quo)", value, quo);
    quo = 0;
    value = remquof(0x1p-149f, 2.0f, &quo);
    print_float_int_pair_result("T597.4", "remquof(0x1p-149f, 2.0f, &quo)", value, quo);
    quo = 0;
    value = remquof(1.0f, 0.0f, &quo);
    print_float_int_pair_result("T597.5", "remquof(1.0f, 0.0f, &quo)", value, quo);
    quo = 0;
    value = remquof(INFINITY, 2.0f, &quo);
    print_float_int_pair_result("T597.6", "remquof(INFINITY, 2.0f, &quo)", value, quo);
}
#endif


#ifdef RUN_T598
static void test_T598(void) {
    print_double_result("T598.1", "rint(0.49999999999999994)", rint(0.49999999999999994));
    print_double_result("T598.2", "rint(0.5)", rint(0.5));
    print_double_result("T598.3", "rint(1.5)", rint(1.5));
    print_double_result("T598.4", "rint(-1.5)", rint(-1.5));
    print_double_result("T598.5", "rint(0x1p+52)", rint(0x1p+52));
    print_double_result("T598.6", "rint(INFINITY)", rint(INFINITY));
    print_double_result("T598.7", "rint(NAN)", rint(NAN));
}
#endif


#ifdef RUN_T599
static void test_T599(void) {
    print_float_result("T599.1", "rintf(0.49999997f)", rintf(0.49999997f));
    print_float_result("T599.2", "rintf(0.5f)", rintf(0.5f));
    print_float_result("T599.3", "rintf(1.5f)", rintf(1.5f));
    print_float_result("T599.4", "rintf(-1.5f)", rintf(-1.5f));
    print_float_result("T599.5", "rintf(0x1p+23f)", rintf(0x1p+23f));
    print_float_result("T599.6", "rintf(INFINITY)", rintf(INFINITY));
    print_float_result("T599.7", "rintf(NAN)", rintf(NAN));
}
#endif


#ifdef RUN_T600
static void test_T600(void) {
    print_double_result("T600.1", "round(0.49999999999999994)", round(0.49999999999999994));
    print_double_result("T600.2", "round(0.5)", round(0.5));
    print_double_result("T600.3", "round(-0.5)", round(-0.5));
    print_double_result("T600.4", "round(1.5)", round(1.5));
    print_double_result("T600.5", "round(0x1p+52)", round(0x1p+52));
    print_double_result("T600.6", "round(INFINITY)", round(INFINITY));
    print_double_result("T600.7", "round(NAN)", round(NAN));
}
#endif


#ifdef RUN_T601
static void test_T601(void) {
    print_float_result("T601.1", "roundf(0.49999997f)", roundf(0.49999997f));
    print_float_result("T601.2", "roundf(0.5f)", roundf(0.5f));
    print_float_result("T601.3", "roundf(-0.5f)", roundf(-0.5f));
    print_float_result("T601.4", "roundf(1.5f)", roundf(1.5f));
    print_float_result("T601.5", "roundf(0x1p+23f)", roundf(0x1p+23f));
    print_float_result("T601.6", "roundf(INFINITY)", roundf(INFINITY));
    print_float_result("T601.7", "roundf(NAN)", roundf(NAN));
}
#endif


#ifdef RUN_T602
static void test_T602(void) {
    print_double_result("T602.1", "scalbln(0x1p-1074, 10)", scalbln(0x1p-1074, 10));
    print_double_result("T602.2", "scalbln(1.5, -10)", scalbln(1.5, -10));
    print_double_result("T602.3", "scalbln(1.5, 10)", scalbln(1.5, 10));
    print_double_result("T602.4", "scalbln(-0.0, 5)", scalbln(-0.0, 5));
    print_double_result("T602.5", "scalbln(INFINITY, -5)", scalbln(INFINITY, -5));
    print_double_result("T602.6", "scalbln(NAN, 5)", scalbln(NAN, 5));
}
#endif


#ifdef RUN_T603
static void test_T603(void) {
    print_double_result("T603.1", "scalbn(0x1p-1074, 10)", scalbn(0x1p-1074, 10));
    print_double_result("T603.2", "scalbn(1.5, -10)", scalbn(1.5, -10));
    print_double_result("T603.3", "scalbn(1.5, 10)", scalbn(1.5, 10));
    print_double_result("T603.4", "scalbn(-0.0, 5)", scalbn(-0.0, 5));
    print_double_result("T603.5", "scalbn(INFINITY, -5)", scalbn(INFINITY, -5));
    print_double_result("T603.6", "scalbn(NAN, 5)", scalbn(NAN, 5));
}
#endif


#ifdef RUN_T604
static void test_T604(void) {
    print_float_result("T604.1", "scalbnf(0x1p-149f, 10)", scalbnf(0x1p-149f, 10));
    print_float_result("T604.2", "scalbnf(1.5f, -10)", scalbnf(1.5f, -10));
    print_float_result("T604.3", "scalbnf(1.5f, 10)", scalbnf(1.5f, 10));
    print_float_result("T604.4", "scalbnf(-0.0f, 5)", scalbnf(-0.0f, 5));
    print_float_result("T604.5", "scalbnf(INFINITY, -5)", scalbnf(INFINITY, -5));
    print_float_result("T604.6", "scalbnf(NAN, 5)", scalbnf(NAN, 5));
}
#endif


#ifdef RUN_T605
static void test_T605(void) {
    print_double_result("T605.1", "sinh(0.0)", sinh(0.0));
    print_double_result("T605.2", "sinh(-0.0)", sinh(-0.0));
    print_double_result("T605.3", "sinh(0x1p-1074)", sinh(0x1p-1074));
    print_double_result("T605.4", "sinh(1.0)", sinh(1.0));
    print_double_result("T605.5", "sinh(20.0)", sinh(20.0));
    print_double_result("T605.6", "sinh(710.0)", sinh(710.0));
    print_double_result("T605.7", "sinh(INFINITY)", sinh(INFINITY));
    print_double_result("T605.8", "sinh(NAN)", sinh(NAN));
}
#endif


#ifdef RUN_T606
static void test_T606(void) {
    print_double_result("T606.1", "sqrt(0.0)", sqrt(0.0));
    print_double_result("T606.2", "sqrt(-0.0)", sqrt(-0.0));
    print_double_result("T606.3", "sqrt(0x1p-1074)", sqrt(0x1p-1074));
    print_double_result("T606.4", "sqrt(2.0)", sqrt(2.0));
    print_double_result("T606.5", "sqrt(-1.0)", sqrt(-1.0));
    print_double_result("T606.6", "sqrt(INFINITY)", sqrt(INFINITY));
    print_double_result("T606.7", "sqrt(NAN)", sqrt(NAN));
}
#endif


#ifdef RUN_T607
static void test_T607(void) {
    print_double_result("T607.1", "tan(0.0)", tan(0.0));
    print_double_result("T607.2", "tan(-0.0)", tan(-0.0));
    print_double_result("T607.3", "tan(nextafter(M_PI_2, 0.0))", tan(nextafter(M_PI_2, 0.0)));
    print_double_result("T607.4", "tan(nextafter(M_PI_2, INFINITY))", tan(nextafter(M_PI_2, INFINITY)));
    print_double_result("T607.5", "tan(0x1p60)", tan(0x1p60));
}
#endif


#ifdef RUN_T608
static void test_T608(void) {
    print_float_result("T608.1", "tanf(0.0f)", tanf(0.0f));
    print_float_result("T608.2", "tanf(-0.0f)", tanf(-0.0f));
    print_float_result("T608.3", "tanf(nextafterf((float)M_PI_2, 0.0f))", tanf(nextafterf((float)M_PI_2, 0.0f)));
    print_float_result("T608.4", "tanf(nextafterf((float)M_PI_2, INFINITY))", tanf(nextafterf((float)M_PI_2, INFINITY)));
    print_float_result("T608.5", "tanf(0x1p30f)", tanf(0x1p30f));
}
#endif


#ifdef RUN_T609
static void test_T609(void) {
    print_double_result("T609.1", "sin(0x1p60)", sin(0x1p60));
    print_double_result("T609.2", "cos(0x1p60)", cos(0x1p60));
    print_double_result("T609.3", "tan(0x1p60)", tan(0x1p60));
    print_double_result("T609.4", "sin(0x1p-1074)", sin(0x1p-1074));
    print_double_result("T609.5", "cos(-0.0)", cos(-0.0));
    print_double_result("T609.6", "tan(M_PI_4)", tan(M_PI_4));
}
#endif


#ifdef RUN_T610
static void test_T610(void) {
    print_float_result("T610.1", "sinf(0x1p30f)", sinf(0x1p30f));
    print_float_result("T610.2", "cosf(0x1p30f)", cosf(0x1p30f));
    print_float_result("T610.3", "tanf(0x1p30f)", tanf(0x1p30f));
    print_float_result("T610.4", "sinf(0x1p-149f)", sinf(0x1p-149f));
    print_float_result("T610.5", "cosf(-0.0f)", cosf(-0.0f));
    print_float_result("T610.6", "tanf((float)M_PI_4)", tanf((float)M_PI_4));
}
#endif


#ifdef RUN_T611
static void test_T611(void) {
    print_double_result("T611.1", "trunc(0.0)", trunc(0.0));
    print_double_result("T611.2", "trunc(-0.0)", trunc(-0.0));
    print_double_result("T611.3", "trunc(0x1p-1074)", trunc(0x1p-1074));
    print_double_result("T611.4", "trunc(-1.75)", trunc(-1.75));
    print_double_result("T611.5", "trunc(1.75)", trunc(1.75));
    print_double_result("T611.6", "trunc(2.0)", trunc(2.0));
    print_double_result("T611.7", "trunc(0x1p+52)", trunc(0x1p+52));
    print_double_result("T611.8", "trunc(INFINITY)", trunc(INFINITY));
    print_double_result("T611.9", "trunc(NAN)", trunc(NAN));
}
#endif


#ifdef RUN_T612
static void test_T612(void) {
    print_float_result("T612.1", "truncf(0.0f)", truncf(0.0f));
    print_float_result("T612.2", "truncf(-0.0f)", truncf(-0.0f));
    print_float_result("T612.3", "truncf(0x1p-149f)", truncf(0x1p-149f));
    print_float_result("T612.4", "truncf(-1.75f)", truncf(-1.75f));
    print_float_result("T612.5", "truncf(1.75f)", truncf(1.75f));
    print_float_result("T612.6", "truncf(2.0f)", truncf(2.0f));
    print_float_result("T612.7", "truncf(0x1p+23f)", truncf(0x1p+23f));
    print_float_result("T612.8", "truncf(INFINITY)", truncf(INFINITY));
    print_float_result("T612.9", "truncf(NAN)", truncf(NAN));
}
#endif


#ifdef RUN_T613
static void test_T613(void) {
    print_double_result("T613.1", "y0(0.0)", y0(0.0));
    print_double_result("T613.2", "y0(0x1p-1022)", y0(0x1p-1022));
    print_double_result("T613.3", "y0(1.0)", y0(1.0));
    print_double_result("T613.4", "y0(8.0)", y0(8.0));
    print_double_result("T613.5", "y0(1e6)", y0(1e6));
}
#endif


#ifdef RUN_T614
static void test_T614(void) {
    print_double_result("T614.1", "y1(0.0)", y1(0.0));
    print_double_result("T614.2", "y1(0x1p-1022)", y1(0x1p-1022));
    print_double_result("T614.3", "y1(1.0)", y1(1.0));
    print_double_result("T614.4", "y1(8.0)", y1(8.0));
    print_double_result("T614.5", "y1(1e6)", y1(1e6));
}
#endif


#ifdef RUN_T615
static void test_T615(void) {
    print_double_result("T615.1", "yn(0, 0.0)", yn(0, 0.0));
    print_double_result("T615.2", "yn(1, 0x1p-1022)", yn(1, 0x1p-1022));
    print_double_result("T615.3", "yn(2, 1.0)", yn(2, 1.0));
    print_double_result("T615.4", "yn(5, 8.0)", yn(5, 8.0));
    print_double_result("T615.5", "yn(20, 1e6)", yn(20, 1e6));
}
#endif


#ifdef RUN_T616
static void test_T616(void) {
    print_float_result("T616.1", "acosf(0.0f)", acosf(0.0f));
    print_float_result("T616.2", "acosf(1.0f)", acosf(1.0f));
    print_float_result("T616.3", "acosf(-1.0f)", acosf(-1.0f));
    print_float_result("T616.4", "acosf(1.0001f)", acosf(1.0001f));
    print_float_result("T616.5", "acosf(0x1p-149f)", acosf(0x1p-149f));
    print_float_result("T616.6", "acosf(NAN)", acosf(NAN));
}
#endif


#ifdef RUN_T617
static void test_T617(void) {
    print_double_result("T617.1", "asin(0.0)", asin(0.0));
    print_double_result("T617.2", "asin(1.0)", asin(1.0));
    print_double_result("T617.3", "asin(-1.0)", asin(-1.0));
    print_double_result("T617.4", "asin(1.0000000000000002)", asin(1.0000000000000002));
    print_double_result("T617.5", "asin(0x1p-1074)", asin(0x1p-1074));
    print_double_result("T617.6", "asin(NAN)", asin(NAN));
}
#endif


#ifdef RUN_T618
static void test_T618(void) {
    print_float_result("T618.1", "asinf(0.0f)", asinf(0.0f));
    print_float_result("T618.2", "asinf(1.0f)", asinf(1.0f));
    print_float_result("T618.3", "asinf(-1.0f)", asinf(-1.0f));
    print_float_result("T618.4", "asinf(-1.0001f)", asinf(-1.0001f));
    print_float_result("T618.5", "asinf(0x1p-149f)", asinf(0x1p-149f));
    print_float_result("T618.6", "asinf(NAN)", asinf(NAN));
}
#endif


#ifdef RUN_T619
static void test_T619(void) {
    print_double_result("T619.1", "atan2(0.0, -0.0)", atan2(0.0, -0.0));
    print_double_result("T619.2", "atan2(-0.0, -0.0)", atan2(-0.0, -0.0));
    print_double_result("T619.3", "atan2(INFINITY, INFINITY)", atan2(INFINITY, INFINITY));
    print_double_result("T619.4", "atan2(-INFINITY, INFINITY)", atan2(-INFINITY, INFINITY));
    print_double_result("T619.5", "atan2(1e308, -1e308)", atan2(1e308, -1e308));
    print_double_result("T619.6", "atan2(0x1p-1074, -0x1p-1074)", atan2(0x1p-1074, -0x1p-1074));
}
#endif


#ifdef RUN_T620
static void test_T620(void) {
    print_float_result("T620.1", "atan2f(0.0f, -0.0f)", atan2f(0.0f, -0.0f));
    print_float_result("T620.2", "atan2f(-0.0f, -0.0f)", atan2f(-0.0f, -0.0f));
    print_float_result("T620.3", "atan2f(INFINITY, INFINITY)", atan2f(INFINITY, INFINITY));
    print_float_result("T620.4", "atan2f(-INFINITY, INFINITY)", atan2f(-INFINITY, INFINITY));
    print_float_result("T620.5", "atan2f(0x1p127f, -0x1p127f)", atan2f(0x1p127f, -0x1p127f));
    print_float_result("T620.6", "atan2f(0x1p-149f, -0x1p-149f)", atan2f(0x1p-149f, -0x1p-149f));
}
#endif


#ifdef RUN_T621
static void test_T621(void) {
    print_double_result("T621.1", "atan(0.0)", atan(0.0));
    print_double_result("T621.2", "atan(-0.0)", atan(-0.0));
    print_double_result("T621.3", "atan(1.0)", atan(1.0));
    print_double_result("T621.4", "atan(-1.0)", atan(-1.0));
    print_double_result("T621.5", "atan(1e308)", atan(1e308));
    print_double_result("T621.6", "atan(-INFINITY)", atan(-INFINITY));
}
#endif


#ifdef RUN_T622
static void test_T622(void) {
    print_float_result("T622.1", "atanf(0.0f)", atanf(0.0f));
    print_float_result("T622.2", "atanf(-0.0f)", atanf(-0.0f));
    print_float_result("T622.3", "atanf(1.0f)", atanf(1.0f));
    print_float_result("T622.4", "atanf(-1.0f)", atanf(-1.0f));
    print_float_result("T622.5", "atanf(0x1p127f)", atanf(0x1p127f));
    print_float_result("T622.6", "atanf(-INFINITY)", atanf(-INFINITY));
}
#endif


#ifdef RUN_T623
static void test_T623(void) {
    print_double_result("T623.1", "atanh(0.0)", atanh(0.0));
    print_double_result("T623.2", "atanh(-0.0)", atanh(-0.0));
    print_double_result("T623.3", "atanh(0.5)", atanh(0.5));
    print_double_result("T623.4", "atanh(-0.9999999999999999)", atanh(-0.9999999999999999));
    print_double_result("T623.5", "atanh(1.0)", atanh(1.0));
    print_double_result("T623.6", "atanh(1.0000000000000002)", atanh(1.0000000000000002));
    print_double_result("T623.7", "atanh(0x1p-1074)", atanh(0x1p-1074));
}
#endif


#ifdef RUN_T624
static void test_T624(void) {
    print_lgamma_double_result("T624.1", "lgamma(-0.25)", -0.25);
    print_lgamma_double_result("T624.2", "lgamma(-0.75)", -0.75);
    print_lgamma_double_result("T624.3", "lgamma(-1.25)", -1.25);
    print_lgamma_double_result("T624.4", "lgamma(-1.75)", -1.75);
    print_lgamma_double_result("T624.5", "lgamma(-3.0)", -3.0);
    print_lgamma_double_result("T624.6", "lgamma(0x1p-1074)", 0x1p-1074);
    print_double_result("T624.7", "tgamma(-0.25)", tgamma(-0.25));
    print_double_result("T624.8", "tgamma(-1.75)", tgamma(-1.75));
}
#endif


#ifdef RUN_T625
static void test_T625(void) {
    print_double_result("T625.1", "ceil(-3.7)", ceil(-3.7));
    print_double_result("T625.2", "ceil(-0.0)", ceil(-0.0));
    print_double_result("T625.3", "ceil(0.0)", ceil(0.0));
    print_double_result("T625.4", "ceil(2.0)", ceil(2.0));
    print_double_result("T625.5", "ceil(0x1p+52)", ceil(0x1p+52));
    print_double_result("T625.6", "ceil(INFINITY)", ceil(INFINITY));
    print_double_result("T625.7", "ceil(NAN)", ceil(NAN));
}
#endif


#ifdef RUN_T626
static void test_T626(void) {
    print_float_result("T626.1", "ceilf(-3.7f)", ceilf(-3.7f));
    print_float_result("T626.2", "ceilf(-0.0f)", ceilf(-0.0f));
    print_float_result("T626.3", "ceilf(0.0f)", ceilf(0.0f));
    print_float_result("T626.4", "ceilf(2.0f)", ceilf(2.0f));
    print_float_result("T626.5", "ceilf(0x1p+23f)", ceilf(0x1p+23f));
    print_float_result("T626.6", "ceilf(INFINITY)", ceilf(INFINITY));
    print_float_result("T626.7", "ceilf(NAN)", ceilf(NAN));
}
#endif


#ifdef RUN_T627
static void test_T627(void) {
    print_double_result("T627.1", "cos(0.0)", cos(0.0));
    print_double_result("T627.2", "cos(-0.0)", cos(-0.0));
    print_double_result("T627.3", "cos(M_PI_2)", cos(M_PI_2));
    print_double_result("T627.4", "cos(0x1p60)", cos(0x1p60));
    print_double_result("T627.5", "cos(INFINITY)", cos(INFINITY));
    print_double_result("T627.6", "cos(NAN)", cos(NAN));
}
#endif


#ifdef RUN_T628
static void test_T628(void) {
    print_float_result("T628.1", "cosf(0.0f)", cosf(0.0f));
    print_float_result("T628.2", "cosf(-0.0f)", cosf(-0.0f));
    print_float_result("T628.3", "cosf((float)M_PI_2)", cosf((float)M_PI_2));
    print_float_result("T628.4", "cosf(0x1p30f)", cosf(0x1p30f));
    print_float_result("T628.5", "cosf(INFINITY)", cosf(INFINITY));
    print_float_result("T628.6", "cosf(NAN)", cosf(NAN));
}
#endif


#ifdef RUN_T629
static void test_T629(void) {
    print_double_result("T629.1", "cosh(0.0)", cosh(0.0));
    print_double_result("T629.2", "cosh(-0.0)", cosh(-0.0));
    print_double_result("T629.3", "cosh(1.0)", cosh(1.0));
    print_double_result("T629.4", "cosh(710.0)", cosh(710.0));
    print_double_result("T629.5", "cosh(INFINITY)", cosh(INFINITY));
    print_double_result("T629.6", "cosh(NAN)", cosh(NAN));
}
#endif


#ifdef RUN_T630
static void test_T630(void) {
    print_double_complex_result("T630.1", "csqrt(CMPLX(0.0, 0.0))", csqrt(CMPLX(0.0, 0.0)));
    print_double_complex_result("T630.2", "csqrt(CMPLX(-4.0, 0.0))", csqrt(CMPLX(-4.0, 0.0)));
    print_double_complex_result("T630.3", "csqrt(CMPLX(-4.0, -0.0))", csqrt(CMPLX(-4.0, -0.0)));
    print_double_complex_result("T630.4", "csqrt(CMPLX(0.0, 1e300))", csqrt(CMPLX(0.0, 1e300)));
    print_double_complex_result("T630.5", "csqrt(CMPLX(INFINITY, 2.0))", csqrt(CMPLX(INFINITY, 2.0)));
    print_double_complex_result("T630.6", "csqrt(CMPLX(NAN, INFINITY))", csqrt(CMPLX(NAN, INFINITY)));
}
#endif


#ifdef RUN_T631
static void test_T631(void) {
    print_float_complex_result("T631.1", "csqrtf(CMPLXF(0.0f, 0.0f))", csqrtf(CMPLXF(0.0f, 0.0f)));
    print_float_complex_result("T631.2", "csqrtf(CMPLXF(-4.0f, 0.0f))", csqrtf(CMPLXF(-4.0f, 0.0f)));
    print_float_complex_result("T631.3", "csqrtf(CMPLXF(-4.0f, -0.0f))", csqrtf(CMPLXF(-4.0f, -0.0f)));
    print_float_complex_result("T631.4", "csqrtf(CMPLXF(0.0f, 0x1p120f))", csqrtf(CMPLXF(0.0f, 0x1p120f)));
    print_float_complex_result("T631.5", "csqrtf(CMPLXF(INFINITY, 2.0f))", csqrtf(CMPLXF(INFINITY, 2.0f)));
    print_float_complex_result("T631.6", "csqrtf(CMPLXF(NAN, INFINITY))", csqrtf(CMPLXF(NAN, INFINITY)));
}
#endif


#ifdef RUN_T632
static void test_T632(void) {
    print_double_complex_result("T632.1", "ctan(CMPLX(0.0, 0.0))", ctan(CMPLX(0.0, 0.0)));
    print_double_complex_result("T632.2", "ctan(CMPLX(-M_PI_2, 0.0))", ctan(CMPLX(-M_PI_2, 0.0)));
    print_double_complex_result("T632.3", "ctan(CMPLX(-1.0, 0.0))", ctan(CMPLX(-1.0, 0.0)));
    print_double_complex_result("T632.4", "ctan(CMPLX(0.0, 40.0))", ctan(CMPLX(0.0, 40.0)));
    print_double_complex_result("T632.5", "ctan(CMPLX(INFINITY, 1.0))", ctan(CMPLX(INFINITY, 1.0)));
    print_double_complex_result("T632.6", "ctan(CMPLX(NAN, -0.0))", ctan(CMPLX(NAN, -0.0)));
}
#endif


#ifdef RUN_T633
static void test_T633(void) {
    print_float_complex_result("T633.1", "ctanf(CMPLXF(0.0f, 0.0f))", ctanf(CMPLXF(0.0f, 0.0f)));
    print_float_complex_result("T633.2", "ctanf(CMPLXF(-(float)M_PI_2, 0.0f))", ctanf(CMPLXF(-(float)M_PI_2, 0.0f)));
    print_float_complex_result("T633.3", "ctanf(CMPLXF(-1.0f, 0.0f))", ctanf(CMPLXF(-1.0f, 0.0f)));
    print_float_complex_result("T633.4", "ctanf(CMPLXF(0.0f, 20.0f))", ctanf(CMPLXF(0.0f, 20.0f)));
    print_float_complex_result("T633.5", "ctanf(CMPLXF(INFINITY, 1.0f))", ctanf(CMPLXF(INFINITY, 1.0f)));
    print_float_complex_result("T633.6", "ctanf(CMPLXF(NAN, -0.0f))", ctanf(CMPLXF(NAN, -0.0f)));
}
#endif


#ifdef RUN_T634
static void test_T634(void) {
    print_double_complex_result("T634.1", "csin(CMPLX(0x1p60, 1.0))", csin(CMPLX(0x1p60, 1.0)));
    print_double_complex_result("T634.2", "ccos(CMPLX(0x1p60, -1.0))", ccos(CMPLX(0x1p60, -1.0)));
    print_double_complex_result("T634.3", "ctan(CMPLX(0.0, INFINITY))", ctan(CMPLX(0.0, INFINITY)));
    print_double_complex_result("T634.4", "ccos(CMPLX(INFINITY, NAN))", ccos(CMPLX(INFINITY, NAN)));
    print_double_complex_result("T634.5", "csin(CMPLX(NAN, -0.0))", csin(CMPLX(NAN, -0.0)));
}
#endif


#ifdef RUN_T635
static void test_T635(void) {
    print_float_complex_result("T635.1", "csinf(CMPLXF(0x1p30f, 1.0f))", csinf(CMPLXF(0x1p30f, 1.0f)));
    print_float_complex_result("T635.2", "ccosf(CMPLXF(0x1p30f, -1.0f))", ccosf(CMPLXF(0x1p30f, -1.0f)));
    print_float_complex_result("T635.3", "ctanf(CMPLXF(0.0f, INFINITY))", ctanf(CMPLXF(0.0f, INFINITY)));
    print_float_complex_result("T635.4", "ccosf(CMPLXF(INFINITY, NAN))", ccosf(CMPLXF(INFINITY, NAN)));
    print_float_complex_result("T635.5", "csinf(CMPLXF(NAN, -0.0f))", csinf(CMPLXF(NAN, -0.0f)));
}
#endif


#ifdef RUN_T636
static void test_T636(void) {
    print_double_result("T636.1", "erfc(0.0)", erfc(0.0));
    print_double_result("T636.2", "erfc(0.84375)", erfc(0.84375));
    print_double_result("T636.3", "erfc(1.25)", erfc(1.25));
    print_double_result("T636.4", "erfc(2.857142857142857)", erfc(2.857142857142857));
    print_double_result("T636.5", "erfc(28.0)", erfc(28.0));
    print_double_result("T636.6", "erfc(-0.0)", erfc(-0.0));
}
#endif


#ifdef RUN_T637
static void test_T637(void) {
    print_float_result("T637.1", "erfcf(0.0f)", erfcf(0.0f));
    print_float_result("T637.2", "erfcf(-0.0f)", erfcf(-0.0f));
    print_float_result("T637.3", "erfcf(0.84375f)", erfcf(0.84375f));
    print_float_result("T637.4", "erfcf(1.25f)", erfcf(1.25f));
    print_float_result("T637.5", "erfcf(2.857143f)", erfcf(2.857143f));
    print_float_result("T637.6", "erfcf(10.0f)", erfcf(10.0f));
}
#endif


#ifdef RUN_T638
static void test_T638(void) {
    print_float_result("T638.1", "erff(0.0f)", erff(0.0f));
    print_float_result("T638.2", "erff(-0.0f)", erff(-0.0f));
    print_float_result("T638.3", "erff(0.84375f)", erff(0.84375f));
    print_float_result("T638.4", "erff(1.25f)", erff(1.25f));
    print_float_result("T638.5", "erff(2.857143f)", erff(2.857143f));
    print_float_result("T638.6", "erff(10.0f)", erff(10.0f));
}
#endif


#ifdef RUN_T639
static void test_T639(void) {
    print_float_result("T639.1", "expm1f(0x1p-149f)", expm1f(0x1p-149f));
    print_float_result("T639.2", "expm1f(-0x1p-149f)", expm1f(-0x1p-149f));
    print_float_result("T639.3", "expm1f(1.0f)", expm1f(1.0f));
    print_float_result("T639.4", "expm1f(88.0f)", expm1f(88.0f));
    print_float_result("T639.5", "expm1f(-100.0f)", expm1f(-100.0f));
    print_float_result("T639.6", "expm1f(INFINITY)", expm1f(INFINITY));
    print_float_result("T639.7", "expm1f(NAN)", expm1f(NAN));
}
#endif


#ifdef RUN_T640
static void test_T640(void) {
    print_double_result("T640.1", "floor(3.7)", floor(3.7));
    print_double_result("T640.2", "floor(-3.7)", floor(-3.7));
    print_double_result("T640.3", "floor(-0.0)", floor(-0.0));
    print_double_result("T640.4", "floor(2.0)", floor(2.0));
    print_double_result("T640.5", "floor(0x1p+52)", floor(0x1p+52));
    print_double_result("T640.6", "floor(INFINITY)", floor(INFINITY));
    print_double_result("T640.7", "floor(NAN)", floor(NAN));
}
#endif


#ifdef RUN_T641
static void test_T641(void) {
    print_float_result("T641.1", "floorf(3.7f)", floorf(3.7f));
    print_float_result("T641.2", "floorf(-3.7f)", floorf(-3.7f));
    print_float_result("T641.3", "floorf(-0.0f)", floorf(-0.0f));
    print_float_result("T641.4", "floorf(2.0f)", floorf(2.0f));
    print_float_result("T641.5", "floorf(0x1p+23f)", floorf(0x1p+23f));
    print_float_result("T641.6", "floorf(INFINITY)", floorf(INFINITY));
    print_float_result("T641.7", "floorf(NAN)", floorf(NAN));
}
#endif


#ifdef RUN_T642
static void test_T642(void) {
    print_double_result("T642.1", "fmax(1.0, 2.0)", fmax(1.0, 2.0));
    print_double_result("T642.2", "fmax(2.0, 1.0)", fmax(2.0, 1.0));
    print_double_result("T642.3", "fmax(NAN, 1.0)", fmax(NAN, 1.0));
    print_double_result("T642.4", "fmax(1.0, NAN)", fmax(1.0, NAN));
    print_double_result("T642.5", "fmax(NAN, NAN)", fmax(NAN, NAN));
    print_double_result("T642.6", "fmax(-0.0, 0.0)", fmax(-0.0, 0.0));
}
#endif


#ifdef RUN_T643
static void test_T643(void) {
    print_float_result("T643.1", "fmaxf(1.0f, 2.0f)", fmaxf(1.0f, 2.0f));
    print_float_result("T643.2", "fmaxf(2.0f, 1.0f)", fmaxf(2.0f, 1.0f));
    print_float_result("T643.3", "fmaxf(NAN, 1.0f)", fmaxf(NAN, 1.0f));
    print_float_result("T643.4", "fmaxf(1.0f, NAN)", fmaxf(1.0f, NAN));
    print_float_result("T643.5", "fmaxf(NAN, NAN)", fmaxf(NAN, NAN));
    print_float_result("T643.6", "fmaxf(-0.0f, 0.0f)", fmaxf(-0.0f, 0.0f));
}
#endif


#ifdef RUN_T644
static void test_T644(void) {
    print_double_result("T644.1", "fmin(1.0, 2.0)", fmin(1.0, 2.0));
    print_double_result("T644.2", "fmin(2.0, 1.0)", fmin(2.0, 1.0));
    print_double_result("T644.3", "fmin(NAN, 1.0)", fmin(NAN, 1.0));
    print_double_result("T644.4", "fmin(1.0, NAN)", fmin(1.0, NAN));
    print_double_result("T644.5", "fmin(NAN, NAN)", fmin(NAN, NAN));
    print_double_result("T644.6", "fmin(-0.0, 0.0)", fmin(-0.0, 0.0));
}
#endif


#ifdef RUN_T645
static void test_T645(void) {
    print_float_result("T645.1", "fminf(1.0f, 2.0f)", fminf(1.0f, 2.0f));
    print_float_result("T645.2", "fminf(2.0f, 1.0f)", fminf(2.0f, 1.0f));
    print_float_result("T645.3", "fminf(NAN, 1.0f)", fminf(NAN, 1.0f));
    print_float_result("T645.4", "fminf(1.0f, NAN)", fminf(1.0f, NAN));
    print_float_result("T645.5", "fminf(NAN, NAN)", fminf(NAN, NAN));
    print_float_result("T645.6", "fminf(-0.0f, 0.0f)", fminf(-0.0f, 0.0f));
}
#endif


#ifdef RUN_T646
static void test_T646(void) {
    print_double_result("T646.1", "fmod(6.0, 3.0)", fmod(6.0, 3.0));
    print_double_result("T646.2", "fmod(1.0, 2.0)", fmod(1.0, 2.0));
    print_double_result("T646.3", "fmod(-7.0, 2.0)", fmod(-7.0, 2.0));
    print_double_result("T646.4", "fmod(0x1p-1074, 2.0)", fmod(0x1p-1074, 2.0));
    print_double_result("T646.5", "fmod(1.0, 0.0)", fmod(1.0, 0.0));
    print_double_result("T646.6", "fmod(INFINITY, 2.0)", fmod(INFINITY, 2.0));
}
#endif


#ifdef RUN_T647
static void test_T647(void) {
    print_float_result("T647.1", "fmodf(6.0f, 3.0f)", fmodf(6.0f, 3.0f));
    print_float_result("T647.2", "fmodf(1.0f, 2.0f)", fmodf(1.0f, 2.0f));
    print_float_result("T647.3", "fmodf(-7.0f, 2.0f)", fmodf(-7.0f, 2.0f));
    print_float_result("T647.4", "fmodf(0x1p-149f, 2.0f)", fmodf(0x1p-149f, 2.0f));
    print_float_result("T647.5", "fmodf(1.0f, 0.0f)", fmodf(1.0f, 0.0f));
    print_float_result("T647.6", "fmodf(INFINITY, 2.0f)", fmodf(INFINITY, 2.0f));
}
#endif


#ifdef RUN_T648
static void test_T648(void) {
    print_classification_result("T648.1", "fpclassify(0.0)", 0.0);
    print_classification_result("T648.2", "fpclassify(0x1p-1074)", 0x1p-1074);
    print_classification_result("T648.3", "fpclassify(DBL_MIN)", DBL_MIN);
    print_classification_result("T648.4", "fpclassify(INFINITY)", INFINITY);
    print_classification_result("T648.5", "fpclassify(NAN)", NAN);
}
#endif


#ifdef RUN_T649
static void test_T649(void) {
    int exp;
    double value;

    value = frexp(0.0, &exp);
    print_double_int_pair_result("T649.1", "frexp(0.0, &exp)", value, exp);
    value = frexp(0x1p-1074, &exp);
    print_double_int_pair_result("T649.2", "frexp(0x1p-1074, &exp)", value, exp);
    value = frexp(-6.5, &exp);
    print_double_int_pair_result("T649.3", "frexp(-6.5, &exp)", value, exp);
    value = frexp(INFINITY, &exp);
    print_double_int_pair_result("T649.4", "frexp(INFINITY, &exp)", value, exp);
    value = frexp(NAN, &exp);
    print_double_int_pair_result("T649.5", "frexp(NAN, &exp)", value, exp);
}
#endif


#ifdef RUN_T650
static void test_T650(void) {
    int exp;
    float value;

    value = frexpf(0.0f, &exp);
    print_float_int_pair_result("T650.1", "frexpf(0.0f, &exp)", value, exp);
    value = frexpf(0x1p-149f, &exp);
    print_float_int_pair_result("T650.2", "frexpf(0x1p-149f, &exp)", value, exp);
    value = frexpf(-6.5f, &exp);
    print_float_int_pair_result("T650.3", "frexpf(-6.5f, &exp)", value, exp);
    value = frexpf(INFINITY, &exp);
    print_float_int_pair_result("T650.4", "frexpf(INFINITY, &exp)", value, exp);
    value = frexpf(NAN, &exp);
    print_float_int_pair_result("T650.5", "frexpf(NAN, &exp)", value, exp);
}
#endif


#ifdef RUN_T651
static void test_T651(void) {
    print_lgamma_double_result("T651.1", "lgamma(1.0)", 1.0);
    print_lgamma_double_result("T651.2", "lgamma(2.0)", 2.0);
    print_lgamma_double_result("T651.3", "lgamma(7.5)", 7.5);
    print_lgamma_double_result("T651.4", "lgamma(8.0)", 8.0);
    print_lgamma_double_result("T651.5", "lgamma(-2.5)", -2.5);
    print_double_result("T651.6", "tgamma(1.0)", tgamma(1.0));
    print_double_result("T651.7", "tgamma(8.0)", tgamma(8.0));
    print_double_result("T651.8", "tgamma(-2.5)", tgamma(-2.5));
}
#endif


#ifdef RUN_T652
static void test_T652(void) {
    print_lgamma_float_result("T652.1", "lgammaf(1.0f)", 1.0f);
    print_lgamma_float_result("T652.2", "lgammaf(2.0f)", 2.0f);
    print_lgamma_float_result("T652.3", "lgammaf(7.5f)", 7.5f);
    print_lgamma_float_result("T652.4", "lgammaf(8.0f)", 8.0f);
    print_lgamma_float_result("T652.5", "lgammaf(-2.5f)", -2.5f);
    print_lgamma_float_result("T652.6", "lgammaf(-3.0f)", -3.0f);
    print_float_result("T652.7", "tgammaf(8.0f)", tgammaf(8.0f));
    print_float_result("T652.8", "tgammaf(-2.5f)", tgammaf(-2.5f));
}
#endif


#ifdef RUN_T653
static void test_T653(void) {
    print_int_result("T653.1", "ilogb(0.0)", ilogb(0.0));
    print_int_result("T653.2", "ilogb(0x1p-1074)", ilogb(0x1p-1074));
    print_int_result("T653.3", "ilogb(6.5)", ilogb(6.5));
    print_int_result("T653.4", "ilogb(INFINITY)", ilogb(INFINITY));
    print_int_result("T653.5", "ilogb(NAN)", ilogb(NAN));
}
#endif


#ifdef RUN_T654
static void test_T654(void) {
    print_double_result("T654.1", "j0(0.0)", j0(0.0));
    print_double_result("T654.2", "j0(1.0)", j0(1.0));
    print_double_result("T654.3", "j0(8.0)", j0(8.0));
    print_double_result("T654.4", "j0(1e6)", j0(1e6));
}
#endif


#ifdef RUN_T655
static void test_T655(void) {
    print_double_result("T655.1", "j1(0.0)", j1(0.0));
    print_double_result("T655.2", "j1(1.0)", j1(1.0));
    print_double_result("T655.3", "j1(8.0)", j1(8.0));
    print_double_result("T655.4", "j1(1e6)", j1(1e6));
}
#endif


#ifdef RUN_T656
static void test_T656(void) {
    print_double_result("T656.1", "jn(0, 1.0)", jn(0, 1.0));
    print_double_result("T656.2", "jn(1, 1.0)", jn(1, 1.0));
    print_double_result("T656.3", "jn(5, 8.0)", jn(5, 8.0));
    print_double_result("T656.4", "jn(20, 1e6)", jn(20, 1e6));
}
#endif


#ifdef RUN_T657
static void test_T657(void) {
    print_double_result("T657.1", "log10(1.0)", log10(1.0));
    print_double_result("T657.2", "log10(1.0000000000000002)", log10(1.0000000000000002));
    print_double_result("T657.3", "log10(0x1p-1074)", log10(0x1p-1074));
    print_double_result("T657.4", "log10(-1.0)", log10(-1.0));
    print_double_result("T657.5", "log10(INFINITY)", log10(INFINITY));
    print_double_result("T657.6", "log10(NAN)", log10(NAN));
}
#endif


#ifdef RUN_T658
static void test_T658(void) {
    print_double_result("T658.1", "log1p(0.0)", log1p(0.0));
    print_double_result("T658.2", "log1p(-0.0)", log1p(-0.0));
    print_double_result("T658.3", "log1p(0x1p-1074)", log1p(0x1p-1074));
    print_double_result("T658.4", "log1p(-0.5)", log1p(-0.5));
    print_double_result("T658.5", "log1p(-1.0)", log1p(-1.0));
    print_double_result("T658.6", "log1p(-1.0000000000000002)", log1p(-1.0000000000000002));
    print_double_result("T658.7", "log1p(INFINITY)", log1p(INFINITY));
}
#endif


#ifdef RUN_T659
static void test_T659(void) {
    print_float_result("T659.1", "log1pf(0.0f)", log1pf(0.0f));
    print_float_result("T659.2", "log1pf(-0.0f)", log1pf(-0.0f));
    print_float_result("T659.3", "log1pf(0x1p-149f)", log1pf(0x1p-149f));
    print_float_result("T659.4", "log1pf(-0.5f)", log1pf(-0.5f));
    print_float_result("T659.5", "log1pf(-1.0f)", log1pf(-1.0f));
    print_float_result("T659.6", "log1pf(-1.0001f)", log1pf(-1.0001f));
    print_float_result("T659.7", "log1pf(INFINITY)", log1pf(INFINITY));
}
#endif


#ifdef RUN_T660
static void test_T660(void) {
    print_double_result("T660.1", "log2(1.0)", log2(1.0));
    print_double_result("T660.2", "log2(1.0000000000000002)", log2(1.0000000000000002));
    print_double_result("T660.3", "log2(0x1p-1074)", log2(0x1p-1074));
    print_double_result("T660.4", "log2(-1.0)", log2(-1.0));
    print_double_result("T660.5", "log2(INFINITY)", log2(INFINITY));
    print_double_result("T660.6", "log2(NAN)", log2(NAN));
}
#endif


#ifdef RUN_T661
static void test_T661(void) {
    print_double_result("T661.1", "logb(0.0)", logb(0.0));
    print_double_result("T661.2", "logb(0x1p-1074)", logb(0x1p-1074));
    print_double_result("T661.3", "logb(6.5)", logb(6.5));
    print_double_result("T661.4", "logb(INFINITY)", logb(INFINITY));
    print_double_result("T661.5", "logb(NAN)", logb(NAN));
}
#endif


#ifdef RUN_T662
static void test_T662(void) {
    print_double_result("T662.1", "log(1.0)", log(1.0));
    print_double_result("T662.2", "log(1.0000000000000002)", log(1.0000000000000002));
    print_double_result("T662.3", "log(0x1p-1074)", log(0x1p-1074));
    print_double_result("T662.4", "log(-1.0)", log(-1.0));
    print_double_result("T662.5", "log(INFINITY)", log(INFINITY));
    print_double_result("T662.6", "log(NAN)", log(NAN));
}
#endif


#ifdef RUN_T663
static void test_T663(void) {
    print_float_result("T663.1", "logf(1.0f)", logf(1.0f));
    print_float_result("T663.2", "logf(1.0001f)", logf(1.0001f));
    print_float_result("T663.3", "logf(0x1p-149f)", logf(0x1p-149f));
    print_float_result("T663.4", "logf(-1.0f)", logf(-1.0f));
    print_float_result("T663.5", "logf(INFINITY)", logf(INFINITY));
    print_float_result("T663.6", "logf(NAN)", logf(NAN));
}
#endif


#ifdef RUN_T664
static void test_T664(void) {
    print_long_result("T664.1", "lround(-2.5)", lround(-2.5));
    print_long_result("T664.2", "lround(-0.0)", lround(-0.0));
    print_long_result("T664.3", "lround(0.5)", lround(0.5));
    print_long_result("T664.4", "lround(1.5)", lround(1.5));
    print_long_result("T664.5", "lround(4503599627370495.5)", lround(4503599627370495.5));
}
#endif


#ifdef RUN_T665
static void test_T665(void) {
    double frac;
    double ipart;

    frac = modf(0.0, &ipart);
    print_double_pair_result("T665.1", "modf(0.0, &ipart)", frac, ipart);
    frac = modf(-0.0, &ipart);
    print_double_pair_result("T665.2", "modf(-0.0, &ipart)", frac, ipart);
    frac = modf(0x1p-1074, &ipart);
    print_double_pair_result("T665.3", "modf(0x1p-1074, &ipart)", frac, ipart);
    frac = modf(-3.5, &ipart);
    print_double_pair_result("T665.4", "modf(-3.5, &ipart)", frac, ipart);
    frac = modf(INFINITY, &ipart);
    print_double_pair_result("T665.5", "modf(INFINITY, &ipart)", frac, ipart);
    frac = modf(NAN, &ipart);
    print_double_pair_result("T665.6", "modf(NAN, &ipart)", frac, ipart);
}
#endif


#ifdef RUN_T666
static void test_T666(void) {
    float frac;
    float ipart;

    frac = modff(0.0f, &ipart);
    print_float_pair_result("T666.1", "modff(0.0f, &ipart)", frac, ipart);
    frac = modff(-0.0f, &ipart);
    print_float_pair_result("T666.2", "modff(-0.0f, &ipart)", frac, ipart);
    frac = modff(0x1p-149f, &ipart);
    print_float_pair_result("T666.3", "modff(0x1p-149f, &ipart)", frac, ipart);
    frac = modff(-3.5f, &ipart);
    print_float_pair_result("T666.4", "modff(-3.5f, &ipart)", frac, ipart);
    frac = modff(INFINITY, &ipart);
    print_float_pair_result("T666.5", "modff(INFINITY, &ipart)", frac, ipart);
    frac = modff(NAN, &ipart);
    print_float_pair_result("T666.6", "modff(NAN, &ipart)", frac, ipart);
}
#endif


#ifdef RUN_T667
static void test_T667(void) {
    print_double_result("T667.1", "nextafter(1.0, 1.0)", nextafter(1.0, 1.0));
    print_double_result("T667.2", "nextafter(0.0, 1.0)", nextafter(0.0, 1.0));
    print_double_result("T667.3", "nextafter(0.0, -1.0)", nextafter(0.0, -1.0));
    print_double_result("T667.4", "nextafter(0x1p-1074, 0.0)", nextafter(0x1p-1074, 0.0));
    print_double_result("T667.5", "nextafter(INFINITY, 0.0)", nextafter(INFINITY, 0.0));
    print_double_result("T667.6", "nextafter(NAN, 1.0)", nextafter(NAN, 1.0));
}
#endif


#ifdef RUN_T668
static void test_T668(void) {
    print_float_result("T668.1", "nextafterf(1.0f, 1.0f)", nextafterf(1.0f, 1.0f));
    print_float_result("T668.2", "nextafterf(0.0f, 1.0f)", nextafterf(0.0f, 1.0f));
    print_float_result("T668.3", "nextafterf(0.0f, -1.0f)", nextafterf(0.0f, -1.0f));
    print_float_result("T668.4", "nextafterf(0x1p-149f, 0.0f)", nextafterf(0x1p-149f, 0.0f));
    print_float_result("T668.5", "nextafterf(INFINITY, 0.0f)", nextafterf(INFINITY, 0.0f));
    print_float_result("T668.6", "nextafterf(NAN, 1.0f)", nextafterf(NAN, 1.0f));
}
#endif


#ifdef RUN_T669
static void test_T669(void) {
    print_double_result("T669.1", "pow(-2.0, 4.0)", pow(-2.0, 4.0));
    print_double_result("T669.2", "pow(-2.0, 3.0)", pow(-2.0, 3.0));
    print_double_result("T669.3", "pow(-2.0, 0.5)", pow(-2.0, 0.5));
    print_double_result("T669.4", "pow(0x1p-1074, 2.0)", pow(0x1p-1074, 2.0));
    print_double_result("T669.5", "pow(2.0, 1024.0)", pow(2.0, 1024.0));
    print_double_result("T669.6", "pow(2.0, -1075.0)", pow(2.0, -1075.0));
}
#endif


#ifdef RUN_T670
static void test_T670(void) {
    print_float_result("T670.1", "powf(-2.0f, 4.0f)", powf(-2.0f, 4.0f));
    print_float_result("T670.2", "powf(-2.0f, 3.0f)", powf(-2.0f, 3.0f));
    print_float_result("T670.3", "powf(-2.0f, 0.5f)", powf(-2.0f, 0.5f));
    print_float_result("T670.4", "powf(0x1p-149f, 2.0f)", powf(0x1p-149f, 2.0f));
    print_float_result("T670.5", "powf(2.0f, 128.0f)", powf(2.0f, 128.0f));
    print_float_result("T670.6", "powf(2.0f, -150.0f)", powf(2.0f, -150.0f));
}
#endif


#ifdef RUN_T671
static void test_T671(void) {
    print_double_result("T671.1", "remainder(6.0, 3.0)", remainder(6.0, 3.0));
    print_double_result("T671.2", "remainder(1.0, 2.0)", remainder(1.0, 2.0));
    print_double_result("T671.3", "remainder(-7.0, 2.0)", remainder(-7.0, 2.0));
    print_double_result("T671.4", "remainder(0x1p-1074, 2.0)", remainder(0x1p-1074, 2.0));
    print_double_result("T671.5", "remainder(1.0, 0.0)", remainder(1.0, 0.0));
    print_double_result("T671.6", "remainder(INFINITY, 2.0)", remainder(INFINITY, 2.0));
}
#endif


#ifdef RUN_T672
static void test_T672(void) {
    print_float_result("T672.1", "remainderf(6.0f, 3.0f)", remainderf(6.0f, 3.0f));
    print_float_result("T672.2", "remainderf(1.0f, 2.0f)", remainderf(1.0f, 2.0f));
    print_float_result("T672.3", "remainderf(-7.0f, 2.0f)", remainderf(-7.0f, 2.0f));
    print_float_result("T672.4", "remainderf(0x1p-149f, 2.0f)", remainderf(0x1p-149f, 2.0f));
    print_float_result("T672.5", "remainderf(1.0f, 0.0f)", remainderf(1.0f, 0.0f));
    print_float_result("T672.6", "remainderf(INFINITY, 2.0f)", remainderf(INFINITY, 2.0f));
}
#endif


#ifdef RUN_T673
static void test_T673(void) {
    int quo;
    double value;

    value = remquo(6.0, 3.0, &quo);
    print_double_int_pair_result("T673.1", "remquo(6.0, 3.0, &quo)", value, quo);
    value = remquo(7.0, 2.0, &quo);
    print_double_int_pair_result("T673.2", "remquo(7.0, 2.0, &quo)", value, quo);
    value = remquo(-7.0, 2.0, &quo);
    print_double_int_pair_result("T673.3", "remquo(-7.0, 2.0, &quo)", value, quo);
    value = remquo(0x1p-1074, 2.0, &quo);
    print_double_int_pair_result("T673.4", "remquo(0x1p-1074, 2.0, &quo)", value, quo);
    value = remquo(1.0, 0.0, &quo);
    print_double_int_pair_result("T673.5", "remquo(1.0, 0.0, &quo)", value, quo);
}
#endif


#ifdef RUN_T674
static void test_T674(void) {
    int quo;
    float value;

    value = remquof(6.0f, 3.0f, &quo);
    print_float_int_pair_result("T674.1", "remquof(6.0f, 3.0f, &quo)", value, quo);
    value = remquof(7.0f, 2.0f, &quo);
    print_float_int_pair_result("T674.2", "remquof(7.0f, 2.0f, &quo)", value, quo);
    value = remquof(-7.0f, 2.0f, &quo);
    print_float_int_pair_result("T674.3", "remquof(-7.0f, 2.0f, &quo)", value, quo);
    value = remquof(0x1p-149f, 2.0f, &quo);
    print_float_int_pair_result("T674.4", "remquof(0x1p-149f, 2.0f, &quo)", value, quo);
    value = remquof(1.0f, 0.0f, &quo);
    print_float_int_pair_result("T674.5", "remquof(1.0f, 0.0f, &quo)", value, quo);
}
#endif


#ifdef RUN_T675
static void test_T675(void) {
    print_double_result("T675.1", "rint(-2.5)", rint(-2.5));
    print_double_result("T675.2", "rint(-0.0)", rint(-0.0));
    print_double_result("T675.3", "rint(0.5)", rint(0.5));
    print_double_result("T675.4", "rint(1.5)", rint(1.5));
    print_double_result("T675.5", "rint(INFINITY)", rint(INFINITY));
    print_double_result("T675.6", "rint(NAN)", rint(NAN));
}
#endif


#ifdef RUN_T676
static void test_T676(void) {
    print_float_result("T676.1", "rintf(-2.5f)", rintf(-2.5f));
    print_float_result("T676.2", "rintf(-0.0f)", rintf(-0.0f));
    print_float_result("T676.3", "rintf(0.5f)", rintf(0.5f));
    print_float_result("T676.4", "rintf(1.5f)", rintf(1.5f));
    print_float_result("T676.5", "rintf(INFINITY)", rintf(INFINITY));
    print_float_result("T676.6", "rintf(NAN)", rintf(NAN));
}
#endif


#ifdef RUN_T677
static void test_T677(void) {
    print_double_result("T677.1", "round(-2.5)", round(-2.5));
    print_double_result("T677.2", "round(-0.0)", round(-0.0));
    print_double_result("T677.3", "round(0.5)", round(0.5));
    print_double_result("T677.4", "round(1.5)", round(1.5));
    print_double_result("T677.5", "round(INFINITY)", round(INFINITY));
    print_double_result("T677.6", "round(NAN)", round(NAN));
}
#endif


#ifdef RUN_T678
static void test_T678(void) {
    print_float_result("T678.1", "roundf(-2.5f)", roundf(-2.5f));
    print_float_result("T678.2", "roundf(-0.0f)", roundf(-0.0f));
    print_float_result("T678.3", "roundf(0.5f)", roundf(0.5f));
    print_float_result("T678.4", "roundf(1.5f)", roundf(1.5f));
    print_float_result("T678.5", "roundf(INFINITY)", roundf(INFINITY));
    print_float_result("T678.6", "roundf(NAN)", roundf(NAN));
}
#endif


#ifdef RUN_T679
static void test_T679(void) {
    print_double_result("T679.1", "scalbln(0x1p-1074, 53L)", scalbln(0x1p-1074, 53L));
    print_double_result("T679.2", "scalbln(0x1p-1074, -1L)", scalbln(0x1p-1074, -1L));
    print_double_result("T679.3", "scalbln(1.0, 1024L)", scalbln(1.0, 1024L));
    print_double_result("T679.4", "scalbln(1.0, -1075L)", scalbln(1.0, -1075L));
}
#endif


#ifdef RUN_T680
static void test_T680(void) {
    print_double_result("T680.1", "scalbn(0x1p-1074, 53)", scalbn(0x1p-1074, 53));
    print_double_result("T680.2", "scalbn(0x1p-1074, -1)", scalbn(0x1p-1074, -1));
    print_double_result("T680.3", "scalbn(1.0, 1024)", scalbn(1.0, 1024));
    print_double_result("T680.4", "scalbn(1.0, -1075)", scalbn(1.0, -1075));
}
#endif


#ifdef RUN_T681
static void test_T681(void) {
    print_float_result("T681.1", "scalbnf(0x1p-149f, 23)", scalbnf(0x1p-149f, 23));
    print_float_result("T681.2", "scalbnf(0x1p-149f, -1)", scalbnf(0x1p-149f, -1));
    print_float_result("T681.3", "scalbnf(1.0f, 128)", scalbnf(1.0f, 128));
    print_float_result("T681.4", "scalbnf(1.0f, -150)", scalbnf(1.0f, -150));
}
#endif


#ifdef RUN_T682
static void test_T682(void) {
    print_double_result("T682.1", "sinh(0.0)", sinh(0.0));
    print_double_result("T682.2", "sinh(-0.0)", sinh(-0.0));
    print_double_result("T682.3", "sinh(1.0)", sinh(1.0));
    print_double_result("T682.4", "sinh(710.0)", sinh(710.0));
    print_double_result("T682.5", "sinh(INFINITY)", sinh(INFINITY));
    print_double_result("T682.6", "sinh(NAN)", sinh(NAN));
}
#endif


#ifdef RUN_T683
static void test_T683(void) {
    print_double_result("T683.1", "sqrt(NAN)", sqrt(NAN));
    print_double_result("T683.2", "sqrt(INFINITY)", sqrt(INFINITY));
    print_double_result("T683.3", "sqrt(-0.0)", sqrt(-0.0));
    print_double_result("T683.4", "sqrt(-1.0)", sqrt(-1.0));
    print_double_result("T683.5", "sqrt(0x1p-1074)", sqrt(0x1p-1074));
}
#endif


#ifdef RUN_T684
static void test_T684(void) {
    print_double_result("T684.1", "tan(0.0)", tan(0.0));
    print_double_result("T684.2", "tan(-0.0)", tan(-0.0));
    print_double_result("T684.3", "tan(M_PI_2)", tan(M_PI_2));
    print_double_result("T684.4", "tan(0x1p60)", tan(0x1p60));
    print_double_result("T684.5", "tan(INFINITY)", tan(INFINITY));
    print_double_result("T684.6", "tan(NAN)", tan(NAN));
}
#endif


#ifdef RUN_T685
static void test_T685(void) {
    print_double_result("T685.1", "sin(0x1p60)", sin(0x1p60));
    print_double_result("T685.2", "cos(0x1p60)", cos(0x1p60));
    print_double_result("T685.3", "tan(0x1p60)", tan(0x1p60));
    print_double_result("T685.4", "sin(M_PI_2 + 0x1p-40)", sin(M_PI_2 + 0x1p-40));
    print_double_result("T685.5", "tan(M_PI_4 - 0x1p-40)", tan(M_PI_4 - 0x1p-40));
}
#endif


#ifdef RUN_T686
static void test_T686(void) {
    print_float_result("T686.1", "sinf(0x1p30f)", sinf(0x1p30f));
    print_float_result("T686.2", "cosf(0x1p30f)", cosf(0x1p30f));
    print_float_result("T686.3", "tanf(0x1p30f)", tanf(0x1p30f));
    print_float_result("T686.4", "sinf((float)M_PI_2 + 0x1p-20f)", sinf((float)M_PI_2 + 0x1p-20f));
    print_float_result("T686.5", "tanf((float)M_PI_4 - 0x1p-20f)", tanf((float)M_PI_4 - 0x1p-20f));
}
#endif


#ifdef RUN_T687
static void test_T687(void) {
    print_double_result("T687.1", "trunc(3.7)", trunc(3.7));
    print_double_result("T687.2", "trunc(-3.7)", trunc(-3.7));
    print_double_result("T687.3", "trunc(-0.0)", trunc(-0.0));
    print_double_result("T687.4", "trunc(2.0)", trunc(2.0));
    print_double_result("T687.5", "trunc(0x1p+52)", trunc(0x1p+52));
    print_double_result("T687.6", "trunc(INFINITY)", trunc(INFINITY));
    print_double_result("T687.7", "trunc(NAN)", trunc(NAN));
}
#endif


#ifdef RUN_T688
static void test_T688(void) {
    print_float_result("T688.1", "truncf(3.7f)", truncf(3.7f));
    print_float_result("T688.2", "truncf(-3.7f)", truncf(-3.7f));
    print_float_result("T688.3", "truncf(-0.0f)", truncf(-0.0f));
    print_float_result("T688.4", "truncf(2.0f)", truncf(2.0f));
    print_float_result("T688.5", "truncf(0x1p+23f)", truncf(0x1p+23f));
    print_float_result("T688.6", "truncf(INFINITY)", truncf(INFINITY));
    print_float_result("T688.7", "truncf(NAN)", truncf(NAN));
}
#endif


#ifdef RUN_T689
static void test_T689(void) {
    print_double_result("T689.1", "y0(0x1p-1022)", y0(0x1p-1022));
    print_double_result("T689.2", "y0(1.0)", y0(1.0));
    print_double_result("T689.3", "y0(8.0)", y0(8.0));
    print_double_result("T689.4", "y0(1e6)", y0(1e6));
}
#endif


#ifdef RUN_T690
static void test_T690(void) {
    print_double_result("T690.1", "y1(0x1p-1022)", y1(0x1p-1022));
    print_double_result("T690.2", "y1(1.0)", y1(1.0));
    print_double_result("T690.3", "y1(8.0)", y1(8.0));
    print_double_result("T690.4", "y1(1e6)", y1(1e6));
}
#endif


#ifdef RUN_T691
static void test_T691(void) {
    print_double_result("T691.1", "yn(0, 1.0)", yn(0, 1.0));
    print_double_result("T691.2", "yn(1, 0x1p-1022)", yn(1, 0x1p-1022));
    print_double_result("T691.3", "yn(2, 1.0)", yn(2, 1.0));
    print_double_result("T691.4", "yn(5, 8.0)", yn(5, 8.0));
    print_double_result("T691.5", "yn(20, 1e6)", yn(20, 1e6));
}
#endif


#ifdef RUN_T692
static void test_T692(void) {
    print_float_result("T692.1", "acosf(-1.0f)", acosf(-1.0f));
    print_float_result("T692.2", "acosf(-0x1p-20f)", acosf(-0x1p-20f));
    print_float_result("T692.3", "acosf(1.0f)", acosf(1.0f));
    print_float_result("T692.4", "acosf(0x1.000002p+0f)", acosf(0x1.000002p+0f));
    print_float_result("T692.5", "acosf(NAN)", acosf(NAN));
}
#endif


#ifdef RUN_T693
static void test_T693(void) {
    print_double_result("T693.1", "asin(-1.0)", asin(-1.0));
    print_double_result("T693.2", "asin(0x1p-1022)", asin(0x1p-1022));
    print_double_result("T693.3", "asin(1.0)", asin(1.0));
    print_double_result("T693.4", "asin(1.0000000000000002)", asin(1.0000000000000002));
    print_double_result("T693.5", "asin(NAN)", asin(NAN));
}
#endif


#ifdef RUN_T694
static void test_T694(void) {
    print_float_result("T694.1", "asinf(-1.0f)", asinf(-1.0f));
    print_float_result("T694.2", "asinf(0x1p-126f)", asinf(0x1p-126f));
    print_float_result("T694.3", "asinf(1.0f)", asinf(1.0f));
    print_float_result("T694.4", "asinf(-0x1.000002p+0f)", asinf(-0x1.000002p+0f));
    print_float_result("T694.5", "asinf(NAN)", asinf(NAN));
}
#endif


#ifdef RUN_T695
static void test_T695(void) {
    print_double_result("T695.1", "atan2(0.0, -0.0)", atan2(0.0, -0.0));
    print_double_result("T695.2", "atan2(-0.0, -0.0)", atan2(-0.0, -0.0));
    print_double_result("T695.3", "atan2(INFINITY, -INFINITY)", atan2(INFINITY, -INFINITY));
    print_double_result("T695.4", "atan2(-INFINITY, INFINITY)", atan2(-INFINITY, INFINITY));
    print_double_result("T695.5", "atan2(1e308, -1e-308)", atan2(1e308, -1e-308));
}
#endif


#ifdef RUN_T696
static void test_T696(void) {
    print_float_result("T696.1", "atan2f(0.0f, -0.0f)", atan2f(0.0f, -0.0f));
    print_float_result("T696.2", "atan2f(-0.0f, -0.0f)", atan2f(-0.0f, -0.0f));
    print_float_result("T696.3", "atan2f(INFINITY, -INFINITY)", atan2f(INFINITY, -INFINITY));
    print_float_result("T696.4", "atan2f(-INFINITY, INFINITY)", atan2f(-INFINITY, INFINITY));
    print_float_result("T696.5", "atan2f(0x1p+120f, -0x1p-120f)", atan2f(0x1p+120f, -0x1p-120f));
}
#endif


#ifdef RUN_T697
static void test_T697(void) {
    print_double_result("T697.1", "atan(-0.0)", atan(-0.0));
    print_double_result("T697.2", "atan(1.0)", atan(1.0));
    print_double_result("T697.3", "atan(-1e300)", atan(-1e300));
    print_double_result("T697.4", "atan(INFINITY)", atan(INFINITY));
    print_double_result("T697.5", "atan(NAN)", atan(NAN));
}
#endif


#ifdef RUN_T698
static void test_T698(void) {
    print_float_result("T698.1", "atanf(-0.0f)", atanf(-0.0f));
    print_float_result("T698.2", "atanf(1.0f)", atanf(1.0f));
    print_float_result("T698.3", "atanf(-0x1p+120f)", atanf(-0x1p+120f));
    print_float_result("T698.4", "atanf(INFINITY)", atanf(INFINITY));
    print_float_result("T698.5", "atanf(NAN)", atanf(NAN));
}
#endif


#ifdef RUN_T699
static void test_T699(void) {
    print_double_result("T699.1", "atanh(-0.0)", atanh(-0.0));
    print_double_result("T699.2", "atanh(0x1p-1074)", atanh(0x1p-1074));
    print_double_result("T699.3", "atanh(0.5)", atanh(0.5));
    print_double_result("T699.4", "atanh(1.0)", atanh(1.0));
    print_double_result("T699.5", "atanh(1.25)", atanh(1.25));
}
#endif


#ifdef RUN_T700
static void test_T700(void) {
    print_lgamma_double_result("T700.1", "lgamma(-0.5)", -0.5);
    print_lgamma_double_result("T700.2", "lgamma(-1.5)", -1.5);
    print_lgamma_double_result("T700.3", "lgamma(-2.0)", -2.0);
    print_lgamma_double_result("T700.4", "lgamma(0.5)", 0.5);
    print_lgamma_double_result("T700.5", "lgamma(8.5)", 8.5);
    print_double_result("T700.6", "tgamma(-0.5)", tgamma(-0.5));
    print_double_result("T700.7", "tgamma(-2.5)", tgamma(-2.5));
    print_double_result("T700.8", "tgamma(8.5)", tgamma(8.5));
}
#endif


#ifdef RUN_T701
static void test_T701(void) {
    print_double_result("T701.1", "ceil(-2.75)", ceil(-2.75));
    print_double_result("T701.2", "ceil(-0.0)", ceil(-0.0));
    print_double_result("T701.3", "ceil(0.25)", ceil(0.25));
    print_double_result("T701.4", "ceil(0x1p+52)", ceil(0x1p+52));
    print_double_result("T701.5", "ceil(INFINITY)", ceil(INFINITY));
    print_double_result("T701.6", "ceil(NAN)", ceil(NAN));
}
#endif


#ifdef RUN_T702
static void test_T702(void) {
    print_float_result("T702.1", "ceilf(-2.75f)", ceilf(-2.75f));
    print_float_result("T702.2", "ceilf(-0.0f)", ceilf(-0.0f));
    print_float_result("T702.3", "ceilf(0.25f)", ceilf(0.25f));
    print_float_result("T702.4", "ceilf(0x1p+23f)", ceilf(0x1p+23f));
    print_float_result("T702.5", "ceilf(INFINITY)", ceilf(INFINITY));
    print_float_result("T702.6", "ceilf(NAN)", ceilf(NAN));
}
#endif


#ifdef RUN_T703
static void test_T703(void) {
    print_double_result("T703.1", "cos(-0.0)", cos(-0.0));
    print_double_result("T703.2", "cos(M_PI_2)", cos(M_PI_2));
    print_double_result("T703.3", "cos(1e20)", cos(1e20));
    print_double_result("T703.4", "cos(INFINITY)", cos(INFINITY));
    print_double_result("T703.5", "cos(NAN)", cos(NAN));
}
#endif


#ifdef RUN_T704
static void test_T704(void) {
    print_float_result("T704.1", "cosf(-0.0f)", cosf(-0.0f));
    print_float_result("T704.2", "cosf((float)M_PI_2)", cosf((float)M_PI_2));
    print_float_result("T704.3", "cosf(0x1p+30f)", cosf(0x1p+30f));
    print_float_result("T704.4", "cosf(INFINITY)", cosf(INFINITY));
    print_float_result("T704.5", "cosf(NAN)", cosf(NAN));
}
#endif


#ifdef RUN_T705
static void test_T705(void) {
    print_double_result("T705.1", "cosh(-0.0)", cosh(-0.0));
    print_double_result("T705.2", "cosh(0x1p-30)", cosh(0x1p-30));
    print_double_result("T705.3", "cosh(1.0)", cosh(1.0));
    print_double_result("T705.4", "cosh(710.0)", cosh(710.0));
    print_double_result("T705.5", "cosh(INFINITY)", cosh(INFINITY));
    print_double_result("T705.6", "cosh(NAN)", cosh(NAN));
}
#endif


#ifdef RUN_T706
static void test_T706(void) {
    print_double_complex_result("T706.1", "csqrt(-4.0 + 0.0*I)", csqrt(-4.0 + 0.0 * I));
    print_double_complex_result("T706.2", "csqrt(-4.0 - 0.0*I)", csqrt(-4.0 - 0.0 * I));
    print_double_complex_result("T706.3", "csqrt(0.0 + 0x1p1023*I)", csqrt(0.0 + 0x1p1023 * I));
    print_double_complex_result("T706.4", "csqrt(INFINITY + NAN*I)", csqrt(INFINITY + NAN * I));
    print_double_complex_result("T706.5", "csqrt(NAN + 1.0*I)", csqrt(NAN + 1.0 * I));
}
#endif


#ifdef RUN_T707
static void test_T707(void) {
    print_float_complex_result("T707.1", "csqrtf(-4.0f + 0.0f*I)", csqrtf(-4.0f + 0.0f * I));
    print_float_complex_result("T707.2", "csqrtf(-4.0f - 0.0f*I)", csqrtf(-4.0f - 0.0f * I));
    print_float_complex_result("T707.3", "csqrtf(0.0f + 0x1p+120f*I)", csqrtf(0.0f + 0x1p+120f * I));
    print_float_complex_result("T707.4", "csqrtf(INFINITY + NAN*I)", csqrtf(INFINITY + NAN * I));
    print_float_complex_result("T707.5", "csqrtf(NAN + 1.0f*I)", csqrtf(NAN + 1.0f * I));
}
#endif


#ifdef RUN_T708
static void test_T708(void) {
    print_double_complex_result("T708.1", "ctan(0.0 + 0.0*I)", ctan(0.0 + 0.0 * I));
    print_double_complex_result("T708.2", "ctan(-0.0 + 0.0*I)", ctan(-0.0 + 0.0 * I));
    print_double_complex_result("T708.3", "ctan(1.0 + 20.0*I)", ctan(1.0 + 20.0 * I));
    print_double_complex_result("T708.4", "ctan(1e6 + 1.0*I)", ctan(1e6 + 1.0 * I));
    print_double_complex_result("T708.5", "ctan(INFINITY + 0.5*I)", ctan(INFINITY + 0.5 * I));
}
#endif


#ifdef RUN_T709
static void test_T709(void) {
    print_float_complex_result("T709.1", "ctanf(0.0f + 0.0f*I)", ctanf(0.0f + 0.0f * I));
    print_float_complex_result("T709.2", "ctanf(-0.0f + 0.0f*I)", ctanf(-0.0f + 0.0f * I));
    print_float_complex_result("T709.3", "ctanf(1.0f + 10.0f*I)", ctanf(1.0f + 10.0f * I));
    print_float_complex_result("T709.4", "ctanf(0x1p+20f + 1.0f*I)", ctanf(0x1p+20f + 1.0f * I));
    print_float_complex_result("T709.5", "ctanf(INFINITY + 0.5f*I)", ctanf(INFINITY + 0.5f * I));
}
#endif


#ifdef RUN_T710
static void test_T710(void) {
    print_double_complex_result("T710.1", "csin(1e6 + 1e6*I)", csin(1e6 + 1e6 * I));
    print_double_complex_result("T710.2", "ccos(-1e6 + 1e6*I)", ccos(-1e6 + 1e6 * I));
    print_double_complex_result("T710.3", "ctan(M_PI_2 + 1e-12*I)", ctan(M_PI_2 + 1e-12 * I));
    print_double_complex_result("T710.4", "csin(INFINITY + 0.0*I)", csin(INFINITY + 0.0 * I));
    print_double_complex_result("T710.5", "ccos(NAN + INFINITY*I)", ccos(NAN + INFINITY * I));
}
#endif


#ifdef RUN_T711
static void test_T711(void) {
    print_float_complex_result("T711.1", "csinf(0x1p+20f + 0x1p+20f*I)", csinf(0x1p+20f + 0x1p+20f * I));
    print_float_complex_result("T711.2", "ccosf(-0x1p+20f + 0x1p+20f*I)", ccosf(-0x1p+20f + 0x1p+20f * I));
    print_float_complex_result("T711.3", "ctanf((float)M_PI_2 + 0x1p-20f*I)", ctanf((float)M_PI_2 + 0x1p-20f * I));
    print_float_complex_result("T711.4", "csinf(INFINITY + 0.0f*I)", csinf(INFINITY + 0.0f * I));
    print_float_complex_result("T711.5", "ccosf(NAN + INFINITY*I)", ccosf(NAN + INFINITY * I));
}
#endif


#ifdef RUN_T712
static void test_T712(void) {
    print_double_result("T712.1", "erfc(-0.0)", erfc(-0.0));
    print_double_result("T712.2", "erfc(0.5)", erfc(0.5));
    print_double_result("T712.3", "erfc(1.0)", erfc(1.0));
    print_double_result("T712.4", "erfc(28.0)", erfc(28.0));
    print_double_result("T712.5", "erfc(INFINITY)", erfc(INFINITY));
}
#endif


#ifdef RUN_T713
static void test_T713(void) {
    print_float_result("T713.1", "erfcf(-0.0f)", erfcf(-0.0f));
    print_float_result("T713.2", "erfcf(0.5f)", erfcf(0.5f));
    print_float_result("T713.3", "erfcf(1.0f)", erfcf(1.0f));
    print_float_result("T713.4", "erfcf(4.0f)", erfcf(4.0f));
    print_float_result("T713.5", "erfcf(INFINITY)", erfcf(INFINITY));
}
#endif


#ifdef RUN_T714
static void test_T714(void) {
    print_float_result("T714.1", "erff(-0.0f)", erff(-0.0f));
    print_float_result("T714.2", "erff(0x1p-20f)", erff(0x1p-20f));
    print_float_result("T714.3", "erff(0.75f)", erff(0.75f));
    print_float_result("T714.4", "erff(4.0f)", erff(4.0f));
    print_float_result("T714.5", "erff(NAN)", erff(NAN));
}
#endif


#ifdef RUN_T715
static void test_T715(void) {
    print_float_result("T715.1", "expm1f(-0.0f)", expm1f(-0.0f));
    print_float_result("T715.2", "expm1f(0x1p-20f)", expm1f(0x1p-20f));
    print_float_result("T715.3", "expm1f(-0x1p-20f)", expm1f(-0x1p-20f));
    print_float_result("T715.4", "expm1f(80.0f)", expm1f(80.0f));
    print_float_result("T715.5", "expm1f(-80.0f)", expm1f(-80.0f));
    print_float_result("T715.6", "expm1f(INFINITY)", expm1f(INFINITY));
    print_float_result("T715.7", "expm1f(NAN)", expm1f(NAN));
}
#endif


#ifdef RUN_T716
static void test_T716(void) {
    print_double_result("T716.1", "floor(-2.75)", floor(-2.75));
    print_double_result("T716.2", "floor(-0.0)", floor(-0.0));
    print_double_result("T716.3", "floor(0.25)", floor(0.25));
    print_double_result("T716.4", "floor(0x1p+52)", floor(0x1p+52));
    print_double_result("T716.5", "floor(INFINITY)", floor(INFINITY));
    print_double_result("T716.6", "floor(NAN)", floor(NAN));
}
#endif


#ifdef RUN_T717
static void test_T717(void) {
    print_float_result("T717.1", "floorf(-2.75f)", floorf(-2.75f));
    print_float_result("T717.2", "floorf(-0.0f)", floorf(-0.0f));
    print_float_result("T717.3", "floorf(0.25f)", floorf(0.25f));
    print_float_result("T717.4", "floorf(0x1p+23f)", floorf(0x1p+23f));
    print_float_result("T717.5", "floorf(INFINITY)", floorf(INFINITY));
    print_float_result("T717.6", "floorf(NAN)", floorf(NAN));
}
#endif


#ifdef RUN_T718
static void test_T718(void) {
    print_double_result("T718.1", "fmax(-2.0, 1.0)", fmax(-2.0, 1.0));
    print_double_result("T718.2", "fmax(3.0, -4.0)", fmax(3.0, -4.0));
    print_double_result("T718.3", "fmax(NAN, 2.0)", fmax(NAN, 2.0));
    print_double_result("T718.4", "fmax(2.0, NAN)", fmax(2.0, NAN));
    print_double_result("T718.5", "fmax(-0.0, 0.0)", fmax(-0.0, 0.0));
    print_double_result("T718.6", "fmax(NAN, NAN)", fmax(NAN, NAN));
}
#endif


#ifdef RUN_T719
static void test_T719(void) {
    print_float_result("T719.1", "fmaxf(-2.0f, 1.0f)", fmaxf(-2.0f, 1.0f));
    print_float_result("T719.2", "fmaxf(3.0f, -4.0f)", fmaxf(3.0f, -4.0f));
    print_float_result("T719.3", "fmaxf(NAN, 2.0f)", fmaxf(NAN, 2.0f));
    print_float_result("T719.4", "fmaxf(2.0f, NAN)", fmaxf(2.0f, NAN));
    print_float_result("T719.5", "fmaxf(-0.0f, 0.0f)", fmaxf(-0.0f, 0.0f));
    print_float_result("T719.6", "fmaxf(NAN, NAN)", fmaxf(NAN, NAN));
}
#endif


#ifdef RUN_T720
static void test_T720(void) {
    print_double_result("T720.1", "fmin(-2.0, 1.0)", fmin(-2.0, 1.0));
    print_double_result("T720.2", "fmin(3.0, -4.0)", fmin(3.0, -4.0));
    print_double_result("T720.3", "fmin(NAN, 2.0)", fmin(NAN, 2.0));
    print_double_result("T720.4", "fmin(2.0, NAN)", fmin(2.0, NAN));
    print_double_result("T720.5", "fmin(-0.0, 0.0)", fmin(-0.0, 0.0));
    print_double_result("T720.6", "fmin(NAN, NAN)", fmin(NAN, NAN));
}
#endif


#ifdef RUN_T721
static void test_T721(void) {
    print_float_result("T721.1", "fminf(-2.0f, 1.0f)", fminf(-2.0f, 1.0f));
    print_float_result("T721.2", "fminf(3.0f, -4.0f)", fminf(3.0f, -4.0f));
    print_float_result("T721.3", "fminf(NAN, 2.0f)", fminf(NAN, 2.0f));
    print_float_result("T721.4", "fminf(2.0f, NAN)", fminf(2.0f, NAN));
    print_float_result("T721.5", "fminf(-0.0f, 0.0f)", fminf(-0.0f, 0.0f));
    print_float_result("T721.6", "fminf(NAN, NAN)", fminf(NAN, NAN));
}
#endif


#ifdef RUN_T722
static void test_T722(void) {
    print_double_result("T722.1", "fmod(7.0, 2.0)", fmod(7.0, 2.0));
    print_double_result("T722.2", "fmod(-7.0, 2.0)", fmod(-7.0, 2.0));
    print_double_result("T722.3", "fmod(2.0, 7.0)", fmod(2.0, 7.0));
    print_double_result("T722.4", "fmod(5e-324, 2.0)", fmod(5e-324, 2.0));
    print_double_result("T722.5", "fmod(1.0, 0.0)", fmod(1.0, 0.0));
    print_double_result("T722.6", "fmod(INFINITY, 2.0)", fmod(INFINITY, 2.0));
}
#endif


#ifdef RUN_T723
static void test_T723(void) {
    print_float_result("T723.1", "fmodf(7.0f, 2.0f)", fmodf(7.0f, 2.0f));
    print_float_result("T723.2", "fmodf(-7.0f, 2.0f)", fmodf(-7.0f, 2.0f));
    print_float_result("T723.3", "fmodf(2.0f, 7.0f)", fmodf(2.0f, 7.0f));
    print_float_result("T723.4", "fmodf(0x1p-149f, 2.0f)", fmodf(0x1p-149f, 2.0f));
    print_float_result("T723.5", "fmodf(1.0f, 0.0f)", fmodf(1.0f, 0.0f));
    print_float_result("T723.6", "fmodf(INFINITY, 2.0f)", fmodf(INFINITY, 2.0f));
}
#endif


#ifdef RUN_T724
static void test_T724(void) {
    print_classification_result("T724.1", "fpclassify(0.0)", 0.0);
    print_classification_result("T724.2", "fpclassify(5e-324)", 5e-324);
    print_classification_result("T724.3", "fpclassify(1.0)", 1.0);
    print_classification_result("T724.4", "fpclassify(INFINITY)", INFINITY);
    print_classification_result("T724.5", "fpclassify(NAN)", NAN);
}
#endif


#ifdef RUN_T725
static void test_T725(void) {
    int exp;
    double x;

    x = frexp(0.0, &exp);
    print_double_int_pair_result("T725.1", "frexp(0.0)", x, exp);
    x = frexp(5e-324, &exp);
    print_double_int_pair_result("T725.2", "frexp(5e-324)", x, exp);
    x = frexp(6.5, &exp);
    print_double_int_pair_result("T725.3", "frexp(6.5)", x, exp);
    x = frexp(INFINITY, &exp);
    print_double_int_pair_result("T725.4", "frexp(INFINITY)", x, exp);
    x = frexp(NAN, &exp);
    print_double_int_pair_result("T725.5", "frexp(NAN)", x, exp);
}
#endif


#ifdef RUN_T726
static void test_T726(void) {
    int exp;
    float x;

    x = frexpf(0.0f, &exp);
    print_float_int_pair_result("T726.1", "frexpf(0.0f)", x, exp);
    x = frexpf(0x1p-149f, &exp);
    print_float_int_pair_result("T726.2", "frexpf(0x1p-149f)", x, exp);
    x = frexpf(6.5f, &exp);
    print_float_int_pair_result("T726.3", "frexpf(6.5f)", x, exp);
    x = frexpf(INFINITY, &exp);
    print_float_int_pair_result("T726.4", "frexpf(INFINITY)", x, exp);
    x = frexpf(NAN, &exp);
    print_float_int_pair_result("T726.5", "frexpf(NAN)", x, exp);
}
#endif


#ifdef RUN_T727
static void test_T727(void) {
    print_lgamma_double_result("T727.1", "lgamma(0x1p-1074)", 0x1p-1074);
    print_lgamma_double_result("T727.2", "lgamma(1.0)", 1.0);
    print_lgamma_double_result("T727.3", "lgamma(2.0)", 2.0);
    print_lgamma_double_result("T727.4", "lgamma(7.999999999999999)", 7.999999999999999);
    print_lgamma_double_result("T727.5", "lgamma(-3.5)", -3.5);
    print_double_result("T727.6", "tgamma(0x1p-1074)", tgamma(0x1p-1074));
    print_double_result("T727.7", "tgamma(2.0)", tgamma(2.0));
    print_double_result("T727.8", "tgamma(-3.5)", tgamma(-3.5));
}
#endif


#ifdef RUN_T728
static void test_T728(void) {
    print_lgamma_float_result("T728.1", "lgammaf(0x1p-149f)", 0x1p-149f);
    print_lgamma_float_result("T728.2", "lgammaf(1.0f)", 1.0f);
    print_lgamma_float_result("T728.3", "lgammaf(2.0f)", 2.0f);
    print_lgamma_float_result("T728.4", "lgammaf(7.5f)", 7.5f);
    print_lgamma_float_result("T728.5", "lgammaf(-3.5f)", -3.5f);
    print_float_result("T728.6", "tgammaf(0x1p-149f)", tgammaf(0x1p-149f));
    print_float_result("T728.7", "tgammaf(2.0f)", tgammaf(2.0f));
    print_float_result("T728.8", "tgammaf(-3.5f)", tgammaf(-3.5f));
}
#endif


#ifdef RUN_T729
static void test_T729(void) {
    print_int_result("T729.1", "ilogb(0.0)", ilogb(0.0));
    print_int_result("T729.2", "ilogb(5e-324)", ilogb(5e-324));
    print_int_result("T729.3", "ilogb(1.0)", ilogb(1.0));
    print_int_result("T729.4", "ilogb(INFINITY)", ilogb(INFINITY));
    print_int_result("T729.5", "ilogb(NAN)", ilogb(NAN));
}
#endif


#ifdef RUN_T730
static void test_T730(void) {
    print_double_result("T730.1", "j0(0.0)", j0(0.0));
    print_double_result("T730.2", "j0(2.4048255576957729)", j0(2.4048255576957729));
    print_double_result("T730.3", "j0(8.0)", j0(8.0));
    print_double_result("T730.4", "j0(1e6)", j0(1e6));
}
#endif


#ifdef RUN_T731
static void test_T731(void) {
    print_double_result("T731.1", "j1(0.0)", j1(0.0));
    print_double_result("T731.2", "j1(1.0)", j1(1.0));
    print_double_result("T731.3", "j1(8.0)", j1(8.0));
    print_double_result("T731.4", "j1(1e6)", j1(1e6));
}
#endif


#ifdef RUN_T732
static void test_T732(void) {
    print_double_result("T732.1", "jn(0, 1.0)", jn(0, 1.0));
    print_double_result("T732.2", "jn(1, 0x1p-1022)", jn(1, 0x1p-1022));
    print_double_result("T732.3", "jn(5, 8.0)", jn(5, 8.0));
    print_double_result("T732.4", "jn(20, 1e6)", jn(20, 1e6));
}
#endif


#ifdef RUN_T733
static void test_T733(void) {
    print_double_result("T733.1", "log10(0.9999999999999999)", log10(0.9999999999999999));
    print_double_result("T733.2", "log10(0x1p-1074)", log10(0x1p-1074));
    print_double_result("T733.3", "log10(-1.0)", log10(-1.0));
    print_double_result("T733.4", "log10(INFINITY)", log10(INFINITY));
    print_double_result("T733.5", "log10(NAN)", log10(NAN));
}
#endif


#ifdef RUN_T734
static void test_T734(void) {
    print_double_result("T734.1", "log1p(-0.0)", log1p(-0.0));
    print_double_result("T734.2", "log1p(0x1p-54)", log1p(0x1p-54));
    print_double_result("T734.3", "log1p(-0.75)", log1p(-0.75));
    print_double_result("T734.4", "log1p(-1.0)", log1p(-1.0));
    print_double_result("T734.5", "log1p(INFINITY)", log1p(INFINITY));
}
#endif


#ifdef RUN_T735
static void test_T735(void) {
    print_float_result("T735.1", "log1pf(-0.0f)", log1pf(-0.0f));
    print_float_result("T735.2", "log1pf(0x1p-25f)", log1pf(0x1p-25f));
    print_float_result("T735.3", "log1pf(-0.75f)", log1pf(-0.75f));
    print_float_result("T735.4", "log1pf(-1.0f)", log1pf(-1.0f));
    print_float_result("T735.5", "log1pf(NAN)", log1pf(NAN));
}
#endif


#ifdef RUN_T736
static void test_T736(void) {
    print_double_result("T736.1", "log2(1.0000000000000002)", log2(1.0000000000000002));
    print_double_result("T736.2", "log2(0x1p-1074)", log2(0x1p-1074));
    print_double_result("T736.3", "log2(-1.0)", log2(-1.0));
    print_double_result("T736.4", "log2(INFINITY)", log2(INFINITY));
    print_double_result("T736.5", "log2(NAN)", log2(NAN));
}
#endif


#ifdef RUN_T737
static void test_T737(void) {
    print_double_result("T737.1", "logb(0.0)", logb(0.0));
    print_double_result("T737.2", "logb(5e-324)", logb(5e-324));
    print_double_result("T737.3", "logb(1.0)", logb(1.0));
    print_double_result("T737.4", "logb(INFINITY)", logb(INFINITY));
    print_double_result("T737.5", "logb(NAN)", logb(NAN));
}
#endif


#ifdef RUN_T738
static void test_T738(void) {
    print_double_result("T738.1", "log(0.9999999999999999)", log(0.9999999999999999));
    print_double_result("T738.2", "log(0x1p-1074)", log(0x1p-1074));
    print_double_result("T738.3", "log(-1.0)", log(-1.0));
    print_double_result("T738.4", "log(INFINITY)", log(INFINITY));
    print_double_result("T738.5", "log(NAN)", log(NAN));
}
#endif


#ifdef RUN_T739
static void test_T739(void) {
    print_float_result("T739.1", "logf(0.99999994f)", logf(0.99999994f));
    print_float_result("T739.2", "logf(0x1p-149f)", logf(0x1p-149f));
    print_float_result("T739.3", "logf(-1.0f)", logf(-1.0f));
    print_float_result("T739.4", "logf(INFINITY)", logf(INFINITY));
    print_float_result("T739.5", "logf(NAN)", logf(NAN));
}
#endif


#ifdef RUN_T740
static void test_T740(void) {
    print_long_result("T740.1", "lround(-2.5)", lround(-2.5));
    print_long_result("T740.2", "lround(-0.0)", lround(-0.0));
    print_long_result("T740.3", "lround(0.5)", lround(0.5));
    print_long_result("T740.4", "lround(1.5)", lround(1.5));
    print_long_result("T740.5", "lround(4503599627370495.0)", lround(4503599627370495.0));
}
#endif


#ifdef RUN_T741
static void test_T741(void) {
    double ipart;
    double fpart;

    fpart = modf(-0.0, &ipart);
    print_double_pair_result("T741.1", "modf(-0.0)", fpart, ipart);
    fpart = modf(5e-324, &ipart);
    print_double_pair_result("T741.2", "modf(5e-324)", fpart, ipart);
    fpart = modf(3.75, &ipart);
    print_double_pair_result("T741.3", "modf(3.75)", fpart, ipart);
    fpart = modf(INFINITY, &ipart);
    print_double_pair_result("T741.4", "modf(INFINITY)", fpart, ipart);
    fpart = modf(NAN, &ipart);
    print_double_pair_result("T741.5", "modf(NAN)", fpart, ipart);
}
#endif


#ifdef RUN_T742
static void test_T742(void) {
    float ipart;
    float fpart;

    fpart = modff(-0.0f, &ipart);
    print_float_pair_result("T742.1", "modff(-0.0f)", fpart, ipart);
    fpart = modff(0x1p-149f, &ipart);
    print_float_pair_result("T742.2", "modff(0x1p-149f)", fpart, ipart);
    fpart = modff(3.75f, &ipart);
    print_float_pair_result("T742.3", "modff(3.75f)", fpart, ipart);
    fpart = modff(INFINITY, &ipart);
    print_float_pair_result("T742.4", "modff(INFINITY)", fpart, ipart);
    fpart = modff(NAN, &ipart);
    print_float_pair_result("T742.5", "modff(NAN)", fpart, ipart);
}
#endif


#ifdef RUN_T743
static void test_T743(void) {
    print_double_result("T743.1", "nextafter(0.0, 1.0)", nextafter(0.0, 1.0));
    print_double_result("T743.2", "nextafter(0.0, -1.0)", nextafter(0.0, -1.0));
    print_double_result("T743.3", "nextafter(1.0, 1.0)", nextafter(1.0, 1.0));
    print_double_result("T743.4", "nextafter(5e-324, 0.0)", nextafter(5e-324, 0.0));
    print_double_result("T743.5", "nextafter(INFINITY, 0.0)", nextafter(INFINITY, 0.0));
    print_double_result("T743.6", "nextafter(NAN, 1.0)", nextafter(NAN, 1.0));
}
#endif


#ifdef RUN_T744
static void test_T744(void) {
    print_float_result("T744.1", "nextafterf(0.0f, 1.0f)", nextafterf(0.0f, 1.0f));
    print_float_result("T744.2", "nextafterf(0.0f, -1.0f)", nextafterf(0.0f, -1.0f));
    print_float_result("T744.3", "nextafterf(1.0f, 1.0f)", nextafterf(1.0f, 1.0f));
    print_float_result("T744.4", "nextafterf(0x1p-149f, 0.0f)", nextafterf(0x1p-149f, 0.0f));
    print_float_result("T744.5", "nextafterf(INFINITY, 0.0f)", nextafterf(INFINITY, 0.0f));
    print_float_result("T744.6", "nextafterf(NAN, 1.0f)", nextafterf(NAN, 1.0f));
}
#endif


#ifdef RUN_T745
static void test_T745(void) {
    print_double_result("T745.1", "pow(-2.0, 3.0)", pow(-2.0, 3.0));
    print_double_result("T745.2", "pow(-2.0, 4.0)", pow(-2.0, 4.0));
    print_double_result("T745.3", "pow(-2.0, 0.5)", pow(-2.0, 0.5));
    print_double_result("T745.4", "pow(0x1p-1074, 2.0)", pow(0x1p-1074, 2.0));
    print_double_result("T745.5", "pow(2.0, 1024.0)", pow(2.0, 1024.0));
    print_double_result("T745.6", "pow(2.0, -1075.0)", pow(2.0, -1075.0));
}
#endif


#ifdef RUN_T746
static void test_T746(void) {
    print_float_result("T746.1", "powf(-2.0f, 3.0f)", powf(-2.0f, 3.0f));
    print_float_result("T746.2", "powf(-2.0f, 4.0f)", powf(-2.0f, 4.0f));
    print_float_result("T746.3", "powf(-2.0f, 0.5f)", powf(-2.0f, 0.5f));
    print_float_result("T746.4", "powf(0x1p-149f, 2.0f)", powf(0x1p-149f, 2.0f));
    print_float_result("T746.5", "powf(2.0f, 128.0f)", powf(2.0f, 128.0f));
    print_float_result("T746.6", "powf(2.0f, -150.0f)", powf(2.0f, -150.0f));
}
#endif


#ifdef RUN_T747
static void test_T747(void) {
    print_double_result("T747.1", "remainder(7.0, 2.0)", remainder(7.0, 2.0));
    print_double_result("T747.2", "remainder(-7.0, 2.0)", remainder(-7.0, 2.0));
    print_double_result("T747.3", "remainder(2.0, 7.0)", remainder(2.0, 7.0));
    print_double_result("T747.4", "remainder(5e-324, 2.0)", remainder(5e-324, 2.0));
    print_double_result("T747.5", "remainder(1.0, 0.0)", remainder(1.0, 0.0));
    print_double_result("T747.6", "remainder(INFINITY, 2.0)", remainder(INFINITY, 2.0));
}
#endif


#ifdef RUN_T748
static void test_T748(void) {
    print_float_result("T748.1", "remainderf(7.0f, 2.0f)", remainderf(7.0f, 2.0f));
    print_float_result("T748.2", "remainderf(-7.0f, 2.0f)", remainderf(-7.0f, 2.0f));
    print_float_result("T748.3", "remainderf(2.0f, 7.0f)", remainderf(2.0f, 7.0f));
    print_float_result("T748.4", "remainderf(0x1p-149f, 2.0f)", remainderf(0x1p-149f, 2.0f));
    print_float_result("T748.5", "remainderf(1.0f, 0.0f)", remainderf(1.0f, 0.0f));
    print_float_result("T748.6", "remainderf(INFINITY, 2.0f)", remainderf(INFINITY, 2.0f));
}
#endif


#ifdef RUN_T749
static void test_T749(void) {
    int quo;
    double value;

    value = remquo(7.0, 2.0, &quo);
    print_double_int_pair_result("T749.1", "remquo(7.0, 2.0)", value, quo);
    value = remquo(-7.0, 2.0, &quo);
    print_double_int_pair_result("T749.2", "remquo(-7.0, 2.0)", value, quo);
    value = remquo(2.0, 7.0, &quo);
    print_double_int_pair_result("T749.3", "remquo(2.0, 7.0)", value, quo);
    value = remquo(5e-324, 2.0, &quo);
    print_double_int_pair_result("T749.4", "remquo(5e-324, 2.0)", value, quo);
    value = remquo(1.0, 0.0, &quo);
    print_double_int_pair_result("T749.5", "remquo(1.0, 0.0)", value, quo);
}
#endif


#ifdef RUN_T750
static void test_T750(void) {
    int quo;
    float value;

    value = remquof(7.0f, 2.0f, &quo);
    print_float_int_pair_result("T750.1", "remquof(7.0f, 2.0f)", value, quo);
    value = remquof(-7.0f, 2.0f, &quo);
    print_float_int_pair_result("T750.2", "remquof(-7.0f, 2.0f)", value, quo);
    value = remquof(2.0f, 7.0f, &quo);
    print_float_int_pair_result("T750.3", "remquof(2.0f, 7.0f)", value, quo);
    value = remquof(0x1p-149f, 2.0f, &quo);
    print_float_int_pair_result("T750.4", "remquof(0x1p-149f, 2.0f)", value, quo);
    value = remquof(1.0f, 0.0f, &quo);
    print_float_int_pair_result("T750.5", "remquof(1.0f, 0.0f)", value, quo);
}
#endif


#ifdef RUN_T751
static void test_T751(void) {
    print_double_result("T751.1", "rint(-2.5)", rint(-2.5));
    print_double_result("T751.2", "rint(-0.0)", rint(-0.0));
    print_double_result("T751.3", "rint(0.5)", rint(0.5));
    print_double_result("T751.4", "rint(1.5)", rint(1.5));
    print_double_result("T751.5", "rint(0x1p+52)", rint(0x1p+52));
    print_double_result("T751.6", "rint(INFINITY)", rint(INFINITY));
    print_double_result("T751.7", "rint(NAN)", rint(NAN));
}
#endif


#ifdef RUN_T752
static void test_T752(void) {
    print_float_result("T752.1", "rintf(-2.5f)", rintf(-2.5f));
    print_float_result("T752.2", "rintf(-0.0f)", rintf(-0.0f));
    print_float_result("T752.3", "rintf(0.5f)", rintf(0.5f));
    print_float_result("T752.4", "rintf(1.5f)", rintf(1.5f));
    print_float_result("T752.5", "rintf(0x1p+23f)", rintf(0x1p+23f));
    print_float_result("T752.6", "rintf(INFINITY)", rintf(INFINITY));
    print_float_result("T752.7", "rintf(NAN)", rintf(NAN));
}
#endif


#ifdef RUN_T753
static void test_T753(void) {
    print_double_result("T753.1", "round(-2.5)", round(-2.5));
    print_double_result("T753.2", "round(-0.0)", round(-0.0));
    print_double_result("T753.3", "round(0.5)", round(0.5));
    print_double_result("T753.4", "round(1.5)", round(1.5));
    print_double_result("T753.5", "round(0x1p+52)", round(0x1p+52));
    print_double_result("T753.6", "round(INFINITY)", round(INFINITY));
    print_double_result("T753.7", "round(NAN)", round(NAN));
}
#endif


#ifdef RUN_T754
static void test_T754(void) {
    print_float_result("T754.1", "roundf(-2.5f)", roundf(-2.5f));
    print_float_result("T754.2", "roundf(-0.0f)", roundf(-0.0f));
    print_float_result("T754.3", "roundf(0.5f)", roundf(0.5f));
    print_float_result("T754.4", "roundf(1.5f)", roundf(1.5f));
    print_float_result("T754.5", "roundf(0x1p+23f)", roundf(0x1p+23f));
    print_float_result("T754.6", "roundf(INFINITY)", roundf(INFINITY));
    print_float_result("T754.7", "roundf(NAN)", roundf(NAN));
}
#endif


#ifdef RUN_T755
static void test_T755(void) {
    print_double_result("T755.1", "scalbln(0x1p-1074, 53)", scalbln(0x1p-1074, 53));
    print_double_result("T755.2", "scalbln(1.0, 1023)", scalbln(1.0, 1023));
    print_double_result("T755.3", "scalbln(1.0, 1024)", scalbln(1.0, 1024));
    print_double_result("T755.4", "scalbln(1.0, -1075)", scalbln(1.0, -1075));
    print_double_result("T755.5", "scalbln(-0.0, 10)", scalbln(-0.0, 10));
}
#endif


#ifdef RUN_T756
static void test_T756(void) {
    print_double_result("T756.1", "scalbn(0x1p-1074, 53)", scalbn(0x1p-1074, 53));
    print_double_result("T756.2", "scalbn(1.0, 1023)", scalbn(1.0, 1023));
    print_double_result("T756.3", "scalbn(1.0, 1024)", scalbn(1.0, 1024));
    print_double_result("T756.4", "scalbn(1.0, -1075)", scalbn(1.0, -1075));
    print_double_result("T756.5", "scalbn(-0.0, 10)", scalbn(-0.0, 10));
}
#endif


#ifdef RUN_T757
static void test_T757(void) {
    print_float_result("T757.1", "scalbnf(0x1p-149f, 23)", scalbnf(0x1p-149f, 23));
    print_float_result("T757.2", "scalbnf(1.0f, 127)", scalbnf(1.0f, 127));
    print_float_result("T757.3", "scalbnf(1.0f, 128)", scalbnf(1.0f, 128));
    print_float_result("T757.4", "scalbnf(1.0f, -150)", scalbnf(1.0f, -150));
    print_float_result("T757.5", "scalbnf(-0.0f, 10)", scalbnf(-0.0f, 10));
}
#endif


#ifdef RUN_T758
static void test_T758(void) {
    print_double_result("T758.1", "sinh(-0.0)", sinh(-0.0));
    print_double_result("T758.2", "sinh(0x1p-30)", sinh(0x1p-30));
    print_double_result("T758.3", "sinh(1.0)", sinh(1.0));
    print_double_result("T758.4", "sinh(710.0)", sinh(710.0));
    print_double_result("T758.5", "sinh(-710.0)", sinh(-710.0));
    print_double_result("T758.6", "sinh(NAN)", sinh(NAN));
}
#endif


#ifdef RUN_T759
static void test_T759(void) {
    print_double_result("T759.1", "sqrt(NAN)", sqrt(NAN));
    print_double_result("T759.2", "sqrt(INFINITY)", sqrt(INFINITY));
    print_double_result("T759.3", "sqrt(-0.0)", sqrt(-0.0));
    print_double_result("T759.4", "sqrt(-1.0)", sqrt(-1.0));
    print_double_result("T759.5", "sqrt(5e-324)", sqrt(5e-324));
}
#endif


#ifdef RUN_T760
static void test_T760(void) {
    print_double_result("T760.1", "tan(-0.0)", tan(-0.0));
    print_double_result("T760.2", "tan(M_PI_2 - 0x1p-40)", tan(M_PI_2 - 0x1p-40));
    print_double_result("T760.3", "tan(-(M_PI_2 - 0x1p-40))", tan(-(M_PI_2 - 0x1p-40)));
    print_double_result("T760.4", "tan(1e20)", tan(1e20));
    print_double_result("T760.5", "tan(INFINITY)", tan(INFINITY));
}
#endif


#ifdef RUN_T761
static void test_T761(void) {
    print_double_result("T761.1", "sin(1e20)", sin(1e20));
    print_double_result("T761.2", "cos(1e20)", cos(1e20));
    print_double_result("T761.3", "tan(0x1.921fb54442d18p+0)", tan(0x1.921fb54442d18p+0));
    print_double_result("T761.4", "sin(5e-324)", sin(5e-324));
    print_double_result("T761.5", "cos(-0.0)", cos(-0.0));
}
#endif


#ifdef RUN_T762
static void test_T762(void) {
    print_float_result("T762.1", "sinf(0x1p+30f)", sinf(0x1p+30f));
    print_float_result("T762.2", "cosf(0x1p+30f)", cosf(0x1p+30f));
    print_float_result("T762.3", "tanf((float)M_PI_2 - 0x1p-12f)", tanf((float)M_PI_2 - 0x1p-12f));
    print_float_result("T762.4", "sinf(0x1p-149f)", sinf(0x1p-149f));
    print_float_result("T762.5", "cosf(-0.0f)", cosf(-0.0f));
}
#endif


#ifdef RUN_T763
static void test_T763(void) {
    print_double_result("T763.1", "trunc(-2.75)", trunc(-2.75));
    print_double_result("T763.2", "trunc(-0.0)", trunc(-0.0));
    print_double_result("T763.3", "trunc(0.25)", trunc(0.25));
    print_double_result("T763.4", "trunc(0x1p+52)", trunc(0x1p+52));
    print_double_result("T763.5", "trunc(INFINITY)", trunc(INFINITY));
    print_double_result("T763.6", "trunc(NAN)", trunc(NAN));
}
#endif


#ifdef RUN_T764
static void test_T764(void) {
    print_float_result("T764.1", "truncf(-2.75f)", truncf(-2.75f));
    print_float_result("T764.2", "truncf(-0.0f)", truncf(-0.0f));
    print_float_result("T764.3", "truncf(0.25f)", truncf(0.25f));
    print_float_result("T764.4", "truncf(0x1p+23f)", truncf(0x1p+23f));
    print_float_result("T764.5", "truncf(INFINITY)", truncf(INFINITY));
    print_float_result("T764.6", "truncf(NAN)", truncf(NAN));
}
#endif


#ifdef RUN_T765
static void test_T765(void) {
    print_double_result("T765.1", "y0(0x1p-1022)", y0(0x1p-1022));
    print_double_result("T765.2", "y0(1.0)", y0(1.0));
    print_double_result("T765.3", "y0(8.0)", y0(8.0));
    print_double_result("T765.4", "y0(1e6)", y0(1e6));
}
#endif


#ifdef RUN_T766
static void test_T766(void) {
    print_double_result("T766.1", "y1(0x1p-1022)", y1(0x1p-1022));
    print_double_result("T766.2", "y1(1.0)", y1(1.0));
    print_double_result("T766.3", "y1(8.0)", y1(8.0));
    print_double_result("T766.4", "y1(1e6)", y1(1e6));
}
#endif


#ifdef RUN_T767
static void test_T767(void) {
    print_double_result("T767.1", "yn(0, 1.0)", yn(0, 1.0));
    print_double_result("T767.2", "yn(1, 0x1p-1022)", yn(1, 0x1p-1022));
    print_double_result("T767.3", "yn(2, 1.0)", yn(2, 1.0));
    print_double_result("T767.4", "yn(5, 8.0)", yn(5, 8.0));
    print_double_result("T767.5", "yn(20, 1e6)", yn(20, 1e6));
}
#endif

int main(void) {
#ifdef RUN_T001
    test_T001();
#endif
#ifdef RUN_T002
    test_T002();
#endif
#ifdef RUN_T003
    test_T003();
#endif
#ifdef RUN_T004
    test_T004();
#endif
#ifdef RUN_T005
    test_T005();
#endif
#ifdef RUN_T006
    test_T006();
#endif
#ifdef RUN_T007
    test_T007();
#endif
#ifdef RUN_T008
    test_T008();
#endif
#ifdef RUN_T009
    test_T009();
#endif
#ifdef RUN_T010
    test_T010();
#endif
#ifdef RUN_T011
    test_T011();
#endif
#ifdef RUN_T012
    test_T012();
#endif
#ifdef RUN_T013
    test_T013();
#endif
#ifdef RUN_T014
    test_T014();
#endif
#ifdef RUN_T015
    test_T015();
#endif
#ifdef RUN_T016
    test_T016();
#endif
#ifdef RUN_T017
    test_T017();
#endif
#ifdef RUN_T018
    test_T018();
#endif
#ifdef RUN_T019
    test_T019();
#endif
#ifdef RUN_T020
    test_T020();
#endif
#ifdef RUN_T021
    test_T021();
#endif
#ifdef RUN_T022
    test_T022();
#endif
#ifdef RUN_T023
    test_T023();
#endif
#ifdef RUN_T024
    test_T024();
#endif
#ifdef RUN_T025
    test_T025();
#endif
#ifdef RUN_T026
    test_T026();
#endif
#ifdef RUN_T027
    test_T027();
#endif
#ifdef RUN_T028
    test_T028();
#endif
#ifdef RUN_T029
    test_T029();
#endif
#ifdef RUN_T030
    test_T030();
#endif
#ifdef RUN_T031
    test_T031();
#endif
#ifdef RUN_T032
    test_T032();
#endif
#ifdef RUN_T033
    test_T033();
#endif
#ifdef RUN_T034
    test_T034();
#endif
#ifdef RUN_T035
    test_T035();
#endif
#ifdef RUN_T036
    test_T036();
#endif
#ifdef RUN_T037
    test_T037();
#endif
#ifdef RUN_T038
    test_T038();
#endif
#ifdef RUN_T039
    test_T039();
#endif
#ifdef RUN_T040
    test_T040();
#endif
#ifdef RUN_T041
    test_T041();
#endif
#ifdef RUN_T042
    test_T042();
#endif
#ifdef RUN_T043
    test_T043();
#endif
#ifdef RUN_T044
    test_T044();
#endif
#ifdef RUN_T045
    test_T045();
#endif
#ifdef RUN_T046
    test_T046();
#endif
#ifdef RUN_T047
    test_T047();
#endif
#ifdef RUN_T048
    test_T048();
#endif
#ifdef RUN_T049
    test_T049();
#endif
#ifdef RUN_T050
    test_T050();
#endif
#ifdef RUN_T051
    test_T051();
#endif
#ifdef RUN_T052
    test_T052();
#endif
#ifdef RUN_T053
    test_T053();
#endif
#ifdef RUN_T054
    test_T054();
#endif
#ifdef RUN_T055
    test_T055();
#endif
#ifdef RUN_T056
    test_T056();
#endif
#ifdef RUN_T057
    test_T057();
#endif
#ifdef RUN_T058
    test_T058();
#endif
#ifdef RUN_T059
    test_T059();
#endif
#ifdef RUN_T060
    test_T060();
#endif
#ifdef RUN_T061
    test_T061();
#endif
#ifdef RUN_T062
    test_T062();
#endif
#ifdef RUN_T063
    test_T063();
#endif
#ifdef RUN_T064
    test_T064();
#endif
#ifdef RUN_T065
    test_T065();
#endif
#ifdef RUN_T066
    test_T066();
#endif
#ifdef RUN_T067
    test_T067();
#endif
#ifdef RUN_T068
    test_T068();
#endif
#ifdef RUN_T069
    test_T069();
#endif
#ifdef RUN_T070
    test_T070();
#endif
#ifdef RUN_T071
    test_T071();
#endif
#ifdef RUN_T072
    test_T072();
#endif
#ifdef RUN_T073
    test_T073();
#endif
#ifdef RUN_T074
    test_T074();
#endif
#ifdef RUN_T075
    test_T075();
#endif
#ifdef RUN_T076
    test_T076();
#endif
#ifdef RUN_T077
    test_T077();
#endif
#ifdef RUN_T078
    test_T078();
#endif
#ifdef RUN_T079
    test_T079();
#endif
#ifdef RUN_T080
    test_T080();
#endif
#ifdef RUN_T081
    test_T081();
#endif
#ifdef RUN_T082
    test_T082();
#endif
#ifdef RUN_T083
    test_T083();
#endif
#ifdef RUN_T084
    test_T084();
#endif
#ifdef RUN_T085
    test_T085();
#endif
#ifdef RUN_T086
    test_T086();
#endif
#ifdef RUN_T087
    test_T087();
#endif
#ifdef RUN_T088
    test_T088();
#endif
#ifdef RUN_T089
    test_T089();
#endif
#ifdef RUN_T090
    test_T090();
#endif
#ifdef RUN_T091
    test_T091();
#endif
#ifdef RUN_T092
    test_T092();
#endif
#ifdef RUN_T093
    test_T093();
#endif
#ifdef RUN_T094
    test_T094();
#endif
#ifdef RUN_T095
    test_T095();
#endif
#ifdef RUN_T096
    test_T096();
#endif
#ifdef RUN_T097
    test_T097();
#endif
#ifdef RUN_T098
    test_T098();
#endif
#ifdef RUN_T099
    test_T099();
#endif
#ifdef RUN_T100
    test_T100();
#endif
#ifdef RUN_T101
    test_T101();
#endif
#ifdef RUN_T102
    test_T102();
#endif
#ifdef RUN_T103
    test_T103();
#endif
#ifdef RUN_T104
    test_T104();
#endif
#ifdef RUN_T105
    test_T105();
#endif
#ifdef RUN_T106
    test_T106();
#endif
#ifdef RUN_T107
    test_T107();
#endif
#ifdef RUN_T108
    test_T108();
#endif
#ifdef RUN_T109
    test_T109();
#endif
#ifdef RUN_T110
    test_T110();
#endif
#ifdef RUN_T111
    test_T111();
#endif
#ifdef RUN_T112
    test_T112();
#endif
#ifdef RUN_T113
    test_T113();
#endif
#ifdef RUN_T114
    test_T114();
#endif
#ifdef RUN_T115
    test_T115();
#endif
#ifdef RUN_T116
    test_T116();
#endif
#ifdef RUN_T117
    test_T117();
#endif
#ifdef RUN_T118
    test_T118();
#endif
#ifdef RUN_T119
    test_T119();
#endif
#ifdef RUN_T120
    test_T120();
#endif
#ifdef RUN_T121
    test_T121();
#endif
#ifdef RUN_T122
    test_T122();
#endif
#ifdef RUN_T123
    test_T123();
#endif
#ifdef RUN_T124
    test_T124();
#endif
#ifdef RUN_T125
    test_T125();
#endif
#ifdef RUN_T126
    test_T126();
#endif
#ifdef RUN_T127
    test_T127();
#endif
#ifdef RUN_T128
    test_T128();
#endif
#ifdef RUN_T129
    test_T129();
#endif
#ifdef RUN_T130
    test_T130();
#endif
#ifdef RUN_T131
    test_T131();
#endif
#ifdef RUN_T132
    test_T132();
#endif
#ifdef RUN_T133
    test_T133();
#endif
#ifdef RUN_T134
    test_T134();
#endif
#ifdef RUN_T135
    test_T135();
#endif
#ifdef RUN_T136
    test_T136();
#endif
#ifdef RUN_T137
    test_T137();
#endif
#ifdef RUN_T138
    test_T138();
#endif
#ifdef RUN_T139
    test_T139();
#endif
#ifdef RUN_T140
    test_T140();
#endif
#ifdef RUN_T141
    test_T141();
#endif
#ifdef RUN_T142
    test_T142();
#endif
#ifdef RUN_T143
    test_T143();
#endif
#ifdef RUN_T144
    test_T144();
#endif
#ifdef RUN_T145
    test_T145();
#endif
#ifdef RUN_T146
    test_T146();
#endif
#ifdef RUN_T147
    test_T147();
#endif
#ifdef RUN_T148
    test_T148();
#endif
#ifdef RUN_T149
    test_T149();
#endif
#ifdef RUN_T150
    test_T150();
#endif
#ifdef RUN_T151
    test_T151();
#endif
#ifdef RUN_T152
    test_T152();
#endif
#ifdef RUN_T153
    test_T153();
#endif
#ifdef RUN_T154
    test_T154();
#endif
#ifdef RUN_T155
    test_T155();
#endif
#ifdef RUN_T156
    test_T156();
#endif
#ifdef RUN_T157
    test_T157();
#endif
#ifdef RUN_T158
    test_T158();
#endif
#ifdef RUN_T159
    test_T159();
#endif
#ifdef RUN_T160
    test_T160();
#endif
#ifdef RUN_T161
    test_T161();
#endif
#ifdef RUN_T162
    test_T162();
#endif
#ifdef RUN_T163
    test_T163();
#endif
#ifdef RUN_T164
    test_T164();
#endif
#ifdef RUN_T165
    test_T165();
#endif
#ifdef RUN_T166
    test_T166();
#endif
#ifdef RUN_T167
    test_T167();
#endif
#ifdef RUN_T168
    test_T168();
#endif
#ifdef RUN_T169
    test_T169();
#endif
#ifdef RUN_T170
    test_T170();
#endif
#ifdef RUN_T171
    test_T171();
#endif
#ifdef RUN_T172
    test_T172();
#endif
#ifdef RUN_T173
    test_T173();
#endif
#ifdef RUN_T174
    test_T174();
#endif
#ifdef RUN_T175
    test_T175();
#endif
#ifdef RUN_T176
    test_T176();
#endif
#ifdef RUN_T177
    test_T177();
#endif
#ifdef RUN_T178
    test_T178();
#endif
#ifdef RUN_T179
    test_T179();
#endif
#ifdef RUN_T180
    test_T180();
#endif
#ifdef RUN_T181
    test_T181();
#endif
#ifdef RUN_T182
    test_T182();
#endif
#ifdef RUN_T183
    test_T183();
#endif
#ifdef RUN_T184
    test_T184();
#endif
#ifdef RUN_T185
    test_T185();
#endif
#ifdef RUN_T186
    test_T186();
#endif
#ifdef RUN_T187
    test_T187();
#endif
#ifdef RUN_T188
    test_T188();
#endif
#ifdef RUN_T189
    test_T189();
#endif
#ifdef RUN_T190
    test_T190();
#endif
#ifdef RUN_T191
    test_T191();
#endif
#ifdef RUN_T192
    test_T192();
#endif
#ifdef RUN_T193
    test_T193();
#endif
#ifdef RUN_T194
    test_T194();
#endif
#ifdef RUN_T195
    test_T195();
#endif
#ifdef RUN_T196
    test_T196();
#endif
#ifdef RUN_T197
    test_T197();
#endif
#ifdef RUN_T198
    test_T198();
#endif
#ifdef RUN_T199
    test_T199();
#endif
#ifdef RUN_T200
    test_T200();
#endif
#ifdef RUN_T201
    test_T201();
#endif
#ifdef RUN_T202
    test_T202();
#endif
#ifdef RUN_T203
    test_T203();
#endif
#ifdef RUN_T204
    test_T204();
#endif
#ifdef RUN_T205
    test_T205();
#endif
#ifdef RUN_T206
    test_T206();
#endif
#ifdef RUN_T207
    test_T207();
#endif
#ifdef RUN_T208
    test_T208();
#endif
#ifdef RUN_T209
    test_T209();
#endif
#ifdef RUN_T210
    test_T210();
#endif
#ifdef RUN_T211
    test_T211();
#endif
#ifdef RUN_T212
    test_T212();
#endif
#ifdef RUN_T213
    test_T213();
#endif
#ifdef RUN_T214
    test_T214();
#endif
#ifdef RUN_T215
    test_T215();
#endif
#ifdef RUN_T216
    test_T216();
#endif
#ifdef RUN_T217
    test_T217();
#endif
#ifdef RUN_T218
    test_T218();
#endif
#ifdef RUN_T219
    test_T219();
#endif
#ifdef RUN_T220
    test_T220();
#endif
#ifdef RUN_T221
    test_T221();
#endif
#ifdef RUN_T222
    test_T222();
#endif
#ifdef RUN_T223
    test_T223();
#endif
#ifdef RUN_T224
    test_T224();
#endif
#ifdef RUN_T225
    test_T225();
#endif
#ifdef RUN_T226
    test_T226();
#endif
#ifdef RUN_T227
    test_T227();
#endif
#ifdef RUN_T228
    test_T228();
#endif
#ifdef RUN_T229
    test_T229();
#endif
#ifdef RUN_T230
    test_T230();
#endif
#ifdef RUN_T231
    test_T231();
#endif
#ifdef RUN_T232
    test_T232();
#endif
#ifdef RUN_T233
    test_T233();
#endif
#ifdef RUN_T234
    test_T234();
#endif
#ifdef RUN_T235
    test_T235();
#endif
#ifdef RUN_T236
    test_T236();
#endif
#ifdef RUN_T237
    test_T237();
#endif
#ifdef RUN_T238
    test_T238();
#endif
#ifdef RUN_T239
    test_T239();
#endif
#ifdef RUN_T240
    test_T240();
#endif
#ifdef RUN_T241
    test_T241();
#endif
#ifdef RUN_T242
    test_T242();
#endif
#ifdef RUN_T243
    test_T243();
#endif
#ifdef RUN_T244
    test_T244();
#endif
#ifdef RUN_T245
    test_T245();
#endif
#ifdef RUN_T246
    test_T246();
#endif
#ifdef RUN_T247
    test_T247();
#endif
#ifdef RUN_T248
    test_T248();
#endif
#ifdef RUN_T249
    test_T249();
#endif
#ifdef RUN_T250
    test_T250();
#endif
#ifdef RUN_T251
    test_T251();
#endif
#ifdef RUN_T252
    test_T252();
#endif
#ifdef RUN_T253
    test_T253();
#endif
#ifdef RUN_T254
    test_T254();
#endif
#ifdef RUN_T255
    test_T255();
#endif
#ifdef RUN_T256
    test_T256();
#endif
#ifdef RUN_T257
    test_T257();
#endif
#ifdef RUN_T258
    test_T258();
#endif
#ifdef RUN_T259
    test_T259();
#endif
#ifdef RUN_T260
    test_T260();
#endif
#ifdef RUN_T261
    test_T261();
#endif
#ifdef RUN_T262
    test_T262();
#endif
#ifdef RUN_T263
    test_T263();
#endif
#ifdef RUN_T264
    test_T264();
#endif
#ifdef RUN_T265
    test_T265();
#endif
#ifdef RUN_T266
    test_T266();
#endif
#ifdef RUN_T267
    test_T267();
#endif
#ifdef RUN_T268
    test_T268();
#endif
#ifdef RUN_T269
    test_T269();
#endif
#ifdef RUN_T270
    test_T270();
#endif
#ifdef RUN_T271
    test_T271();
#endif
#ifdef RUN_T272
    test_T272();
#endif
#ifdef RUN_T273
    test_T273();
#endif
#ifdef RUN_T274
    test_T274();
#endif
#ifdef RUN_T275
    test_T275();
#endif
#ifdef RUN_T276
    test_T276();
#endif
#ifdef RUN_T277
    test_T277();
#endif
#ifdef RUN_T278
    test_T278();
#endif
#ifdef RUN_T279
    test_T279();
#endif
#ifdef RUN_T280
    test_T280();
#endif
#ifdef RUN_T281
    test_T281();
#endif
#ifdef RUN_T282
    test_T282();
#endif
#ifdef RUN_T283
    test_T283();
#endif
#ifdef RUN_T284
    test_T284();
#endif
#ifdef RUN_T285
    test_T285();
#endif
#ifdef RUN_T286
    test_T286();
#endif
#ifdef RUN_T287
    test_T287();
#endif
#ifdef RUN_T288
    test_T288();
#endif
#ifdef RUN_T289
    test_T289();
#endif
#ifdef RUN_T290
    test_T290();
#endif
#ifdef RUN_T291
    test_T291();
#endif
#ifdef RUN_T292
    test_T292();
#endif
#ifdef RUN_T293
    test_T293();
#endif
#ifdef RUN_T294
    test_T294();
#endif
#ifdef RUN_T295
    test_T295();
#endif
#ifdef RUN_T296
    test_T296();
#endif
#ifdef RUN_T297
    test_T297();
#endif
#ifdef RUN_T298
    test_T298();
#endif
#ifdef RUN_T299
    test_T299();
#endif
#ifdef RUN_T300
    test_T300();
#endif
#ifdef RUN_T301
    test_T301();
#endif
#ifdef RUN_T302
    test_T302();
#endif
#ifdef RUN_T303
    test_T303();
#endif
#ifdef RUN_T304
    test_T304();
#endif
#ifdef RUN_T305
    test_T305();
#endif
#ifdef RUN_T306
    test_T306();
#endif
#ifdef RUN_T307
    test_T307();
#endif
#ifdef RUN_T308
    test_T308();
#endif
#ifdef RUN_T309
    test_T309();
#endif
#ifdef RUN_T310
    test_T310();
#endif
#ifdef RUN_T311
    test_T311();
#endif
#ifdef RUN_T312
    test_T312();
#endif
#ifdef RUN_T313
    test_T313();
#endif
#ifdef RUN_T314
    test_T314();
#endif
#ifdef RUN_T315
    test_T315();
#endif
#ifdef RUN_T316
    test_T316();
#endif
#ifdef RUN_T317
    test_T317();
#endif
#ifdef RUN_T318
    test_T318();
#endif
#ifdef RUN_T319
    test_T319();
#endif
#ifdef RUN_T320
    test_T320();
#endif
#ifdef RUN_T321
    test_T321();
#endif
#ifdef RUN_T322
    test_T322();
#endif
#ifdef RUN_T323
    test_T323();
#endif
#ifdef RUN_T324
    test_T324();
#endif
#ifdef RUN_T325
    test_T325();
#endif
#ifdef RUN_T326
    test_T326();
#endif
#ifdef RUN_T327
    test_T327();
#endif
#ifdef RUN_T328
    test_T328();
#endif
#ifdef RUN_T329
    test_T329();
#endif
#ifdef RUN_T330
    test_T330();
#endif
#ifdef RUN_T331
    test_T331();
#endif
#ifdef RUN_T332
    test_T332();
#endif
#ifdef RUN_T333
    test_T333();
#endif
#ifdef RUN_T334
    test_T334();
#endif
#ifdef RUN_T335
    test_T335();
#endif
#ifdef RUN_T336
    test_T336();
#endif
#ifdef RUN_T337
    test_T337();
#endif
#ifdef RUN_T338
    test_T338();
#endif
#ifdef RUN_T339
    test_T339();
#endif
#ifdef RUN_T340
    test_T340();
#endif
#ifdef RUN_T341
    test_T341();
#endif
#ifdef RUN_T342
    test_T342();
#endif
#ifdef RUN_T343
    test_T343();
#endif
#ifdef RUN_T344
    test_T344();
#endif
#ifdef RUN_T345
    test_T345();
#endif
#ifdef RUN_T346
    test_T346();
#endif
#ifdef RUN_T347
    test_T347();
#endif
#ifdef RUN_T348
    test_T348();
#endif
#ifdef RUN_T349
    test_T349();
#endif
#ifdef RUN_T350
    test_T350();
#endif
#ifdef RUN_T351
    test_T351();
#endif
#ifdef RUN_T352
    test_T352();
#endif
#ifdef RUN_T353
    test_T353();
#endif
#ifdef RUN_T354
    test_T354();
#endif
#ifdef RUN_T355
    test_T355();
#endif
#ifdef RUN_T356
    test_T356();
#endif
#ifdef RUN_T357
    test_T357();
#endif
#ifdef RUN_T358
    test_T358();
#endif
#ifdef RUN_T359
    test_T359();
#endif
#ifdef RUN_T360
    test_T360();
#endif
#ifdef RUN_T361
    test_T361();
#endif
#ifdef RUN_T362
    test_T362();
#endif
#ifdef RUN_T363
    test_T363();
#endif
#ifdef RUN_T364
    test_T364();
#endif
#ifdef RUN_T365
    test_T365();
#endif
#ifdef RUN_T366
    test_T366();
#endif
#ifdef RUN_T367
    test_T367();
#endif
#ifdef RUN_T368
    test_T368();
#endif
#ifdef RUN_T369
    test_T369();
#endif
#ifdef RUN_T370
    test_T370();
#endif
#ifdef RUN_T371
    test_T371();
#endif
#ifdef RUN_T372
    test_T372();
#endif
#ifdef RUN_T373
    test_T373();
#endif
#ifdef RUN_T374
    test_T374();
#endif
#ifdef RUN_T375
    test_T375();
#endif
#ifdef RUN_T376
    test_T376();
#endif
#ifdef RUN_T377
    test_T377();
#endif
#ifdef RUN_T378
    test_T378();
#endif
#ifdef RUN_T379
    test_T379();
#endif
#ifdef RUN_T380
    test_T380();
#endif
#ifdef RUN_T381
    test_T381();
#endif
#ifdef RUN_T382
    test_T382();
#endif
#ifdef RUN_T383
    test_T383();
#endif
#ifdef RUN_T384
    test_T384();
#endif
#ifdef RUN_T385
    test_T385();
#endif
#ifdef RUN_T386
    test_T386();
#endif
#ifdef RUN_T387
    test_T387();
#endif
#ifdef RUN_T388
    test_T388();
#endif
#ifdef RUN_T389
    test_T389();
#endif
#ifdef RUN_T390
    test_T390();
#endif
#ifdef RUN_T391
    test_T391();
#endif
#ifdef RUN_T392
    test_T392();
#endif
#ifdef RUN_T393
    test_T393();
#endif
#ifdef RUN_T394
    test_T394();
#endif
#ifdef RUN_T395
    test_T395();
#endif
#ifdef RUN_T396
    test_T396();
#endif
#ifdef RUN_T397
    test_T397();
#endif
#ifdef RUN_T398
    test_T398();
#endif
#ifdef RUN_T399
    test_T399();
#endif
#ifdef RUN_T400
    test_T400();
#endif
#ifdef RUN_T401
    test_T401();
#endif
#ifdef RUN_T402
    test_T402();
#endif
#ifdef RUN_T403
    test_T403();
#endif
#ifdef RUN_T404
    test_T404();
#endif
#ifdef RUN_T405
    test_T405();
#endif
#ifdef RUN_T406
    test_T406();
#endif
#ifdef RUN_T407
    test_T407();
#endif
#ifdef RUN_T408
    test_T408();
#endif
#ifdef RUN_T409
    test_T409();
#endif
#ifdef RUN_T410
    test_T410();
#endif
#ifdef RUN_T411
    test_T411();
#endif
#ifdef RUN_T412
    test_T412();
#endif
#ifdef RUN_T413
    test_T413();
#endif
#ifdef RUN_T414
    test_T414();
#endif
#ifdef RUN_T415
    test_T415();
#endif
#ifdef RUN_T416
    test_T416();
#endif
#ifdef RUN_T417
    test_T417();
#endif
#ifdef RUN_T418
    test_T418();
#endif
#ifdef RUN_T419
    test_T419();
#endif
#ifdef RUN_T420
    test_T420();
#endif
#ifdef RUN_T421
    test_T421();
#endif
#ifdef RUN_T422
    test_T422();
#endif
#ifdef RUN_T423
    test_T423();
#endif
#ifdef RUN_T424
    test_T424();
#endif
#ifdef RUN_T425
    test_T425();
#endif
#ifdef RUN_T426
    test_T426();
#endif
#ifdef RUN_T427
    test_T427();
#endif
#ifdef RUN_T428
    test_T428();
#endif
#ifdef RUN_T429
    test_T429();
#endif
#ifdef RUN_T430
    test_T430();
#endif
#ifdef RUN_T431
    test_T431();
#endif
#ifdef RUN_T432
    test_T432();
#endif
#ifdef RUN_T433
    test_T433();
#endif
#ifdef RUN_T434
    test_T434();
#endif
#ifdef RUN_T435
    test_T435();
#endif
#ifdef RUN_T436
    test_T436();
#endif
#ifdef RUN_T437
    test_T437();
#endif
#ifdef RUN_T438
    test_T438();
#endif
#ifdef RUN_T439
    test_T439();
#endif
#ifdef RUN_T440
    test_T440();
#endif
#ifdef RUN_T441
    test_T441();
#endif
#ifdef RUN_T442
    test_T442();
#endif
#ifdef RUN_T443
    test_T443();
#endif
#ifdef RUN_T444
    test_T444();
#endif
#ifdef RUN_T445
    test_T445();
#endif
#ifdef RUN_T446
    test_T446();
#endif
#ifdef RUN_T447
    test_T447();
#endif
#ifdef RUN_T448
    test_T448();
#endif
#ifdef RUN_T449
    test_T449();
#endif
#ifdef RUN_T450
    test_T450();
#endif
#ifdef RUN_T451
    test_T451();
#endif
#ifdef RUN_T452
    test_T452();
#endif
#ifdef RUN_T453
    test_T453();
#endif
#ifdef RUN_T454
    test_T454();
#endif
#ifdef RUN_T455
    test_T455();
#endif
#ifdef RUN_T456
    test_T456();
#endif
#ifdef RUN_T457
    test_T457();
#endif
#ifdef RUN_T458
    test_T458();
#endif
#ifdef RUN_T459
    test_T459();
#endif
#ifdef RUN_T460
    test_T460();
#endif
#ifdef RUN_T461
    test_T461();
#endif
#ifdef RUN_T462
    test_T462();
#endif
#ifdef RUN_T463
    test_T463();
#endif
#ifdef RUN_T464
    test_T464();
#endif
#ifdef RUN_T465
    test_T465();
#endif
#ifdef RUN_T466
    test_T466();
#endif
#ifdef RUN_T467
    test_T467();
#endif
#ifdef RUN_T468
    test_T468();
#endif
#ifdef RUN_T469
    test_T469();
#endif
#ifdef RUN_T470
    test_T470();
#endif
#ifdef RUN_T471
    test_T471();
#endif
#ifdef RUN_T472
    test_T472();
#endif
#ifdef RUN_T473
    test_T473();
#endif
#ifdef RUN_T474
    test_T474();
#endif
#ifdef RUN_T475
    test_T475();
#endif
#ifdef RUN_T476
    test_T476();
#endif
#ifdef RUN_T477
    test_T477();
#endif
#ifdef RUN_T478
    test_T478();
#endif
#ifdef RUN_T479
    test_T479();
#endif
#ifdef RUN_T480
    test_T480();
#endif
#ifdef RUN_T481
    test_T481();
#endif
#ifdef RUN_T482
    test_T482();
#endif
#ifdef RUN_T483
    test_T483();
#endif
#ifdef RUN_T484
    test_T484();
#endif
#ifdef RUN_T485
    test_T485();
#endif
#ifdef RUN_T486
    test_T486();
#endif
#ifdef RUN_T487
    test_T487();
#endif
#ifdef RUN_T488
    test_T488();
#endif
#ifdef RUN_T489
    test_T489();
#endif
#ifdef RUN_T490
    test_T490();
#endif
#ifdef RUN_T491
    test_T491();
#endif
#ifdef RUN_T492
    test_T492();
#endif
#ifdef RUN_T493
    test_T493();
#endif
#ifdef RUN_T494
    test_T494();
#endif
#ifdef RUN_T495
    test_T495();
#endif
#ifdef RUN_T496
    test_T496();
#endif
#ifdef RUN_T497
    test_T497();
#endif
#ifdef RUN_T498
    test_T498();
#endif
#ifdef RUN_T499
    test_T499();
#endif
#ifdef RUN_T500
    test_T500();
#endif
#ifdef RUN_T501
    test_T501();
#endif
#ifdef RUN_T502
    test_T502();
#endif
#ifdef RUN_T503
    test_T503();
#endif
#ifdef RUN_T504
    test_T504();
#endif
#ifdef RUN_T505
    test_T505();
#endif
#ifdef RUN_T506
    test_T506();
#endif
#ifdef RUN_T507
    test_T507();
#endif
#ifdef RUN_T508
    test_T508();
#endif
#ifdef RUN_T509
    test_T509();
#endif
#ifdef RUN_T510
    test_T510();
#endif
#ifdef RUN_T511
    test_T511();
#endif
#ifdef RUN_T512
    test_T512();
#endif
#ifdef RUN_T513
    test_T513();
#endif
#ifdef RUN_T514
    test_T514();
#endif
#ifdef RUN_T515
    test_T515();
#endif
#ifdef RUN_T516
    test_T516();
#endif
#ifdef RUN_T517
    test_T517();
#endif
#ifdef RUN_T518
    test_T518();
#endif
#ifdef RUN_T519
    test_T519();
#endif
#ifdef RUN_T520
    test_T520();
#endif
#ifdef RUN_T521
    test_T521();
#endif
#ifdef RUN_T522
    test_T522();
#endif
#ifdef RUN_T523
    test_T523();
#endif
#ifdef RUN_T524
    test_T524();
#endif
#ifdef RUN_T525
    test_T525();
#endif
#ifdef RUN_T526
    test_T526();
#endif
#ifdef RUN_T527
    test_T527();
#endif
#ifdef RUN_T528
    test_T528();
#endif
#ifdef RUN_T529
    test_T529();
#endif
#ifdef RUN_T530
    test_T530();
#endif
#ifdef RUN_T531
    test_T531();
#endif
#ifdef RUN_T532
    test_T532();
#endif
#ifdef RUN_T533
    test_T533();
#endif
#ifdef RUN_T534
    test_T534();
#endif
#ifdef RUN_T535
    test_T535();
#endif
#ifdef RUN_T536
    test_T536();
#endif
#ifdef RUN_T537
    test_T537();
#endif
#ifdef RUN_T538
    test_T538();
#endif
#ifdef RUN_T539
    test_T539();
#endif
#ifdef RUN_T540
    test_T540();
#endif
#ifdef RUN_T541
    test_T541();
#endif
#ifdef RUN_T542
    test_T542();
#endif
#ifdef RUN_T543
    test_T543();
#endif
#ifdef RUN_T544
    test_T544();
#endif
#ifdef RUN_T545
    test_T545();
#endif
#ifdef RUN_T546
    test_T546();
#endif
#ifdef RUN_T547
    test_T547();
#endif
#ifdef RUN_T548
    test_T548();
#endif
#ifdef RUN_T549
    test_T549();
#endif
#ifdef RUN_T550
    test_T550();
#endif
#ifdef RUN_T551
    test_T551();
#endif
#ifdef RUN_T552
    test_T552();
#endif
#ifdef RUN_T553
    test_T553();
#endif
#ifdef RUN_T554
    test_T554();
#endif
#ifdef RUN_T555
    test_T555();
#endif
#ifdef RUN_T556
    test_T556();
#endif
#ifdef RUN_T557
    test_T557();
#endif
#ifdef RUN_T558
    test_T558();
#endif
#ifdef RUN_T559
    test_T559();
#endif
#ifdef RUN_T560
    test_T560();
#endif
#ifdef RUN_T561
    test_T561();
#endif
#ifdef RUN_T562
    test_T562();
#endif
#ifdef RUN_T563
    test_T563();
#endif
#ifdef RUN_T564
    test_T564();
#endif
#ifdef RUN_T565
    test_T565();
#endif
#ifdef RUN_T566
    test_T566();
#endif
#ifdef RUN_T567
    test_T567();
#endif
#ifdef RUN_T568
    test_T568();
#endif
#ifdef RUN_T569
    test_T569();
#endif
#ifdef RUN_T570
    test_T570();
#endif
#ifdef RUN_T571
    test_T571();
#endif
#ifdef RUN_T572
    test_T572();
#endif
#ifdef RUN_T573
    test_T573();
#endif
#ifdef RUN_T574
    test_T574();
#endif
#ifdef RUN_T575
    test_T575();
#endif
#ifdef RUN_T576
    test_T576();
#endif
#ifdef RUN_T577
    test_T577();
#endif
#ifdef RUN_T578
    test_T578();
#endif
#ifdef RUN_T579
    test_T579();
#endif
#ifdef RUN_T580
    test_T580();
#endif
#ifdef RUN_T581
    test_T581();
#endif
#ifdef RUN_T582
    test_T582();
#endif
#ifdef RUN_T583
    test_T583();
#endif
#ifdef RUN_T584
    test_T584();
#endif
#ifdef RUN_T585
    test_T585();
#endif
#ifdef RUN_T586
    test_T586();
#endif
#ifdef RUN_T587
    test_T587();
#endif
#ifdef RUN_T588
    test_T588();
#endif
#ifdef RUN_T589
    test_T589();
#endif
#ifdef RUN_T590
    test_T590();
#endif
#ifdef RUN_T591
    test_T591();
#endif
#ifdef RUN_T592
    test_T592();
#endif
#ifdef RUN_T593
    test_T593();
#endif
#ifdef RUN_T594
    test_T594();
#endif
#ifdef RUN_T595
    test_T595();
#endif
#ifdef RUN_T596
    test_T596();
#endif
#ifdef RUN_T597
    test_T597();
#endif
#ifdef RUN_T598
    test_T598();
#endif
#ifdef RUN_T599
    test_T599();
#endif
#ifdef RUN_T600
    test_T600();
#endif
#ifdef RUN_T601
    test_T601();
#endif
#ifdef RUN_T602
    test_T602();
#endif
#ifdef RUN_T603
    test_T603();
#endif
#ifdef RUN_T604
    test_T604();
#endif
#ifdef RUN_T605
    test_T605();
#endif
#ifdef RUN_T606
    test_T606();
#endif
#ifdef RUN_T607
    test_T607();
#endif
#ifdef RUN_T608
    test_T608();
#endif
#ifdef RUN_T609
    test_T609();
#endif
#ifdef RUN_T610
    test_T610();
#endif
#ifdef RUN_T611
    test_T611();
#endif
#ifdef RUN_T612
    test_T612();
#endif
#ifdef RUN_T613
    test_T613();
#endif
#ifdef RUN_T614
    test_T614();
#endif
#ifdef RUN_T615
    test_T615();
#endif
#ifdef RUN_T616
    test_T616();
#endif
#ifdef RUN_T617
    test_T617();
#endif
#ifdef RUN_T618
    test_T618();
#endif
#ifdef RUN_T619
    test_T619();
#endif
#ifdef RUN_T620
    test_T620();
#endif
#ifdef RUN_T621
    test_T621();
#endif
#ifdef RUN_T622
    test_T622();
#endif
#ifdef RUN_T623
    test_T623();
#endif
#ifdef RUN_T624
    test_T624();
#endif
#ifdef RUN_T625
    test_T625();
#endif
#ifdef RUN_T626
    test_T626();
#endif
#ifdef RUN_T627
    test_T627();
#endif
#ifdef RUN_T628
    test_T628();
#endif
#ifdef RUN_T629
    test_T629();
#endif
#ifdef RUN_T630
    test_T630();
#endif
#ifdef RUN_T631
    test_T631();
#endif
#ifdef RUN_T632
    test_T632();
#endif
#ifdef RUN_T633
    test_T633();
#endif
#ifdef RUN_T634
    test_T634();
#endif
#ifdef RUN_T635
    test_T635();
#endif
#ifdef RUN_T636
    test_T636();
#endif
#ifdef RUN_T637
    test_T637();
#endif
#ifdef RUN_T638
    test_T638();
#endif
#ifdef RUN_T639
    test_T639();
#endif
#ifdef RUN_T640
    test_T640();
#endif
#ifdef RUN_T641
    test_T641();
#endif
#ifdef RUN_T642
    test_T642();
#endif
#ifdef RUN_T643
    test_T643();
#endif
#ifdef RUN_T644
    test_T644();
#endif
#ifdef RUN_T645
    test_T645();
#endif
#ifdef RUN_T646
    test_T646();
#endif
#ifdef RUN_T647
    test_T647();
#endif
#ifdef RUN_T648
    test_T648();
#endif
#ifdef RUN_T649
    test_T649();
#endif
#ifdef RUN_T650
    test_T650();
#endif
#ifdef RUN_T651
    test_T651();
#endif
#ifdef RUN_T652
    test_T652();
#endif
#ifdef RUN_T653
    test_T653();
#endif
#ifdef RUN_T654
    test_T654();
#endif
#ifdef RUN_T655
    test_T655();
#endif
#ifdef RUN_T656
    test_T656();
#endif
#ifdef RUN_T657
    test_T657();
#endif
#ifdef RUN_T658
    test_T658();
#endif
#ifdef RUN_T659
    test_T659();
#endif
#ifdef RUN_T660
    test_T660();
#endif
#ifdef RUN_T661
    test_T661();
#endif
#ifdef RUN_T662
    test_T662();
#endif
#ifdef RUN_T663
    test_T663();
#endif
#ifdef RUN_T664
    test_T664();
#endif
#ifdef RUN_T665
    test_T665();
#endif
#ifdef RUN_T666
    test_T666();
#endif
#ifdef RUN_T667
    test_T667();
#endif
#ifdef RUN_T668
    test_T668();
#endif
#ifdef RUN_T669
    test_T669();
#endif
#ifdef RUN_T670
    test_T670();
#endif
#ifdef RUN_T671
    test_T671();
#endif
#ifdef RUN_T672
    test_T672();
#endif
#ifdef RUN_T673
    test_T673();
#endif
#ifdef RUN_T674
    test_T674();
#endif
#ifdef RUN_T675
    test_T675();
#endif
#ifdef RUN_T676
    test_T676();
#endif
#ifdef RUN_T677
    test_T677();
#endif
#ifdef RUN_T678
    test_T678();
#endif
#ifdef RUN_T679
    test_T679();
#endif
#ifdef RUN_T680
    test_T680();
#endif
#ifdef RUN_T681
    test_T681();
#endif
#ifdef RUN_T682
    test_T682();
#endif
#ifdef RUN_T683
    test_T683();
#endif
#ifdef RUN_T684
    test_T684();
#endif
#ifdef RUN_T685
    test_T685();
#endif
#ifdef RUN_T686
    test_T686();
#endif
#ifdef RUN_T687
    test_T687();
#endif
#ifdef RUN_T688
    test_T688();
#endif
#ifdef RUN_T689
    test_T689();
#endif
#ifdef RUN_T690
    test_T690();
#endif
#ifdef RUN_T691
    test_T691();
#endif
#ifdef RUN_T692
    test_T692();
#endif
#ifdef RUN_T693
    test_T693();
#endif
#ifdef RUN_T694
    test_T694();
#endif
#ifdef RUN_T695
    test_T695();
#endif
#ifdef RUN_T696
    test_T696();
#endif
#ifdef RUN_T697
    test_T697();
#endif
#ifdef RUN_T698
    test_T698();
#endif
#ifdef RUN_T699
    test_T699();
#endif
#ifdef RUN_T700
    test_T700();
#endif
#ifdef RUN_T701
    test_T701();
#endif
#ifdef RUN_T702
    test_T702();
#endif
#ifdef RUN_T703
    test_T703();
#endif
#ifdef RUN_T704
    test_T704();
#endif
#ifdef RUN_T705
    test_T705();
#endif
#ifdef RUN_T706
    test_T706();
#endif
#ifdef RUN_T707
    test_T707();
#endif
#ifdef RUN_T708
    test_T708();
#endif
#ifdef RUN_T709
    test_T709();
#endif
#ifdef RUN_T710
    test_T710();
#endif
#ifdef RUN_T711
    test_T711();
#endif
#ifdef RUN_T712
    test_T712();
#endif
#ifdef RUN_T713
    test_T713();
#endif
#ifdef RUN_T714
    test_T714();
#endif
#ifdef RUN_T715
    test_T715();
#endif
#ifdef RUN_T716
    test_T716();
#endif
#ifdef RUN_T717
    test_T717();
#endif
#ifdef RUN_T718
    test_T718();
#endif
#ifdef RUN_T719
    test_T719();
#endif
#ifdef RUN_T720
    test_T720();
#endif
#ifdef RUN_T721
    test_T721();
#endif
#ifdef RUN_T722
    test_T722();
#endif
#ifdef RUN_T723
    test_T723();
#endif
#ifdef RUN_T724
    test_T724();
#endif
#ifdef RUN_T725
    test_T725();
#endif
#ifdef RUN_T726
    test_T726();
#endif
#ifdef RUN_T727
    test_T727();
#endif
#ifdef RUN_T728
    test_T728();
#endif
#ifdef RUN_T729
    test_T729();
#endif
#ifdef RUN_T730
    test_T730();
#endif
#ifdef RUN_T731
    test_T731();
#endif
#ifdef RUN_T732
    test_T732();
#endif
#ifdef RUN_T733
    test_T733();
#endif
#ifdef RUN_T734
    test_T734();
#endif
#ifdef RUN_T735
    test_T735();
#endif
#ifdef RUN_T736
    test_T736();
#endif
#ifdef RUN_T737
    test_T737();
#endif
#ifdef RUN_T738
    test_T738();
#endif
#ifdef RUN_T739
    test_T739();
#endif
#ifdef RUN_T740
    test_T740();
#endif
#ifdef RUN_T741
    test_T741();
#endif
#ifdef RUN_T742
    test_T742();
#endif
#ifdef RUN_T743
    test_T743();
#endif
#ifdef RUN_T744
    test_T744();
#endif
#ifdef RUN_T745
    test_T745();
#endif
#ifdef RUN_T746
    test_T746();
#endif
#ifdef RUN_T747
    test_T747();
#endif
#ifdef RUN_T748
    test_T748();
#endif
#ifdef RUN_T749
    test_T749();
#endif
#ifdef RUN_T750
    test_T750();
#endif
#ifdef RUN_T751
    test_T751();
#endif
#ifdef RUN_T752
    test_T752();
#endif
#ifdef RUN_T753
    test_T753();
#endif
#ifdef RUN_T754
    test_T754();
#endif
#ifdef RUN_T755
    test_T755();
#endif
#ifdef RUN_T756
    test_T756();
#endif
#ifdef RUN_T757
    test_T757();
#endif
#ifdef RUN_T758
    test_T758();
#endif
#ifdef RUN_T759
    test_T759();
#endif
#ifdef RUN_T760
    test_T760();
#endif
#ifdef RUN_T761
    test_T761();
#endif
#ifdef RUN_T762
    test_T762();
#endif
#ifdef RUN_T763
    test_T763();
#endif
#ifdef RUN_T764
    test_T764();
#endif
#ifdef RUN_T765
    test_T765();
#endif
#ifdef RUN_T766
    test_T766();
#endif
#ifdef RUN_T767
    test_T767();
#endif
    return 0;
}
