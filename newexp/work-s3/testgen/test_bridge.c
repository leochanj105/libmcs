/*
 * test_bridge.c - Bridge to access static internal functions in libmcs
 *
 * Compile with: gcc -I/home/leochanj/Desktop/libmcs/libm/include test_bridge.c ...
 *
 * This file #includes selected .c source files from the library to gain access
 * to static functions. Public functions from included sources are renamed via
 * preprocessor macros to avoid link-time conflicts with the actual library.
 * Static variable names that conflict between included sources are also renamed.
 */

/* Pre-include the library headers so subsequent source includes find them
   already processed (via include guards). */
#include "/home/leochanj/Desktop/libmcs/libm/include/math.h"
#include "/home/leochanj/Desktop/libmcs/libm/include/complex.h"

/* ========================================================================
 * Bridge 1: static inline double __tan(double x, double y, int iy)
 *   Source: mathd/tand.c
 *   Rename public: tan
 *   Rename statics: pio4, pio4lo, T  (conflict with tanf.c)
 * ======================================================================== */
#define tan     bridge_skip_tan_d
#define pio4    pio4_td
#define pio4lo  pio4lo_td
#define T       T_td
#include "/home/leochanj/Desktop/libmcs/libm/mathd/tand.c"
#undef T
#undef pio4lo
#undef pio4
#undef tan

double bridge___tan(double x, double y, int iy)
{
    return __tan(x, y, iy);
}

/* ========================================================================
 * Bridge 2: static inline float __tanf(float x, float y, int iy)
 *   Source: mathf/tanf.c
 *   Rename public: tanf
 *   Rename statics: pio4, pio4lo, T  (conflict with tand.c)
 * ======================================================================== */
#define tanf    bridge_skip_tanf_f
#define pio4    pio4_tf
#define pio4lo  pio4lo_tf
#define T       T_tf
#include "/home/leochanj/Desktop/libmcs/libm/mathf/tanf.c"
#undef T
#undef pio4lo
#undef pio4
#undef tanf

float bridge___tanf(float x, float y, int iy)
{
    return __tanf(x, y, iy);
}

/* ========================================================================
 * Bridge 3: static inline double __ctans(double complex z)
 *   Source: complexd/ctand.c
 *   Rename public: ctan
 *   No static variable conflicts.
 * ======================================================================== */
#define ctan    bridge_skip_ctan_d
#include "/home/leochanj/Desktop/libmcs/libm/complexd/ctand.c"
#undef ctan

double bridge___ctans(double complex z)
{
    return __ctans(z);
}

/* ========================================================================
 * Bridge 4: static inline float __ctansf(float complex z)
 *   Source: complexf/ctanf.c
 *   Rename public: ctanf
 *   No static variable conflicts.
 * ======================================================================== */
#define ctanf   bridge_skip_ctanf_f
#include "/home/leochanj/Desktop/libmcs/libm/complexf/ctanf.c"
#undef ctanf

float bridge___ctansf(float complex z)
{
    return __ctansf(z);
}

/* ========================================================================
 * Bridge 5: static double __sin_pi(double x)
 *   Source: mathd/internal/gammad.c
 *   Rename public: __lgamma
 *   Rename all static variables with _gd suffix to avoid conflict with gammaf.c
 * ======================================================================== */
#define __lgamma bridge_skip___lgamma_gd
#define two52   two52_gd
#define half    half_gd
#define one     one_gd
#define pi      pi_gd
#define a0      a0_gd
#define a1      a1_gd
#define a2      a2_gd
#define a3      a3_gd
#define a4      a4_gd
#define a5      a5_gd
#define a6      a6_gd
#define a7      a7_gd
#define a8      a8_gd
#define a9      a9_gd
#define a10     a10_gd
#define a11     a11_gd
#define tc      tc_gd
#define tf      tf_gd
#define tt      tt_gd
#define t0      t0_gd
#define t1      t1_gd
#define t2      t2_gd
#define t3      t3_gd
#define t4      t4_gd
#define t5      t5_gd
#define t6      t6_gd
#define t7      t7_gd
#define t8      t8_gd
#define t9      t9_gd
#define t10     t10_gd
#define t11     t11_gd
#define t12     t12_gd
#define t13     t13_gd
#define t14     t14_gd
#define u0      u0_gd
#define u1      u1_gd
#define u2      u2_gd
#define u3      u3_gd
#define u4      u4_gd
#define u5      u5_gd
#define v1      v1_gd
#define v2      v2_gd
#define v3      v3_gd
#define v4      v4_gd
#define v5      v5_gd
#define s0      s0_gd
#define s1      s1_gd
#define s2      s2_gd
#define s3      s3_gd
#define s4      s4_gd
#define s5      s5_gd
#define s6      s6_gd
#define r1      r1_gd
#define r2      r2_gd
#define r3      r3_gd
#define r4      r4_gd
#define r5      r5_gd
#define r6      r6_gd
#define w0      w0_gd
#define w1      w1_gd
#define w2      w2_gd
#define w3      w3_gd
#define w4      w4_gd
#define w5      w5_gd
#define w6      w6_gd
#define zero    zero_gd
#include "/home/leochanj/Desktop/libmcs/libm/mathd/internal/gammad.c"
#undef zero
#undef w6
#undef w5
#undef w4
#undef w3
#undef w2
#undef w1
#undef w0
#undef r6
#undef r5
#undef r4
#undef r3
#undef r2
#undef r1
#undef s6
#undef s5
#undef s4
#undef s3
#undef s2
#undef s1
#undef s0
#undef v5
#undef v4
#undef v3
#undef v2
#undef v1
#undef u5
#undef u4
#undef u3
#undef u2
#undef u1
#undef u0
#undef t14
#undef t13
#undef t12
#undef t11
#undef t10
#undef t9
#undef t8
#undef t7
#undef t6
#undef t5
#undef t4
#undef t3
#undef t2
#undef t1
#undef t0
#undef tt
#undef tf
#undef tc
#undef a11
#undef a10
#undef a9
#undef a8
#undef a7
#undef a6
#undef a5
#undef a4
#undef a3
#undef a2
#undef a1
#undef a0
#undef pi
#undef one
#undef half
#undef two52
#undef __lgamma

double bridge___sin_pi(double x)
{
    return __sin_pi(x);
}

/* ========================================================================
 * Bridge 6: static float __sin_pif(float x)
 *   Source: mathf/internal/gammaf.c
 *   Rename public: __lgammaf
 *   Rename all static variables with _gf suffix to avoid conflict with gammad.c
 * ======================================================================== */
#define __lgammaf bridge_skip___lgammaf_gf
#define two23   two23_gf
#define half    half_gf
#define one     one_gf
#define pi      pi_gf
#define a0      a0_gf
#define a1      a1_gf
#define a2      a2_gf
#define a3      a3_gf
#define a4      a4_gf
#define a5      a5_gf
#define a6      a6_gf
#define a7      a7_gf
#define a8      a8_gf
#define a9      a9_gf
#define a10     a10_gf
#define a11     a11_gf
#define tc      tc_gf
#define tf      tf_gf
#define tt      tt_gf
#define t0      t0_gf
#define t1      t1_gf
#define t2      t2_gf
#define t3      t3_gf
#define t4      t4_gf
#define t5      t5_gf
#define t6      t6_gf
#define t7      t7_gf
#define t8      t8_gf
#define t9      t9_gf
#define t10     t10_gf
#define t11     t11_gf
#define t12     t12_gf
#define t13     t13_gf
#define t14     t14_gf
#define u0      u0_gf
#define u1      u1_gf
#define u2      u2_gf
#define u3      u3_gf
#define u4      u4_gf
#define u5      u5_gf
#define v1      v1_gf
#define v2      v2_gf
#define v3      v3_gf
#define v4      v4_gf
#define v5      v5_gf
#define s0      s0_gf
#define s1      s1_gf
#define s2      s2_gf
#define s3      s3_gf
#define s4      s4_gf
#define s5      s5_gf
#define s6      s6_gf
#define r1      r1_gf
#define r2      r2_gf
#define r3      r3_gf
#define r4      r4_gf
#define r5      r5_gf
#define r6      r6_gf
#define w0      w0_gf
#define w1      w1_gf
#define w2      w2_gf
#define w3      w3_gf
#define w4      w4_gf
#define w5      w5_gf
#define w6      w6_gf
#define zero    zero_gf
#include "/home/leochanj/Desktop/libmcs/libm/mathf/internal/gammaf.c"
#undef zero
#undef w6
#undef w5
#undef w4
#undef w3
#undef w2
#undef w1
#undef w0
#undef r6
#undef r5
#undef r4
#undef r3
#undef r2
#undef r1
#undef s6
#undef s5
#undef s4
#undef s3
#undef s2
#undef s1
#undef s0
#undef v5
#undef v4
#undef v3
#undef v2
#undef v1
#undef u5
#undef u4
#undef u3
#undef u2
#undef u1
#undef u0
#undef t14
#undef t13
#undef t12
#undef t11
#undef t10
#undef t9
#undef t8
#undef t7
#undef t6
#undef t5
#undef t4
#undef t3
#undef t2
#undef t1
#undef t0
#undef tt
#undef tf
#undef tc
#undef a11
#undef a10
#undef a9
#undef a8
#undef a7
#undef a6
#undef a5
#undef a4
#undef a3
#undef a2
#undef a1
#undef a0
#undef pi
#undef one
#undef half
#undef two23
#undef __lgammaf

float bridge___sin_pif(float x)
{
    return __sin_pif(x);
}

/* ========================================================================
 * Bridge 7: static inline int __rem_pio2_internal(double *x, double *y, int e0, int nx)
 *   Source: mathd/internal/trigd.c
 *   Rename public: __cos, __sin, __rem_pio2
 *   Rename all static variables with _trd suffix
 * ======================================================================== */
#define __cos       bridge_skip___cos_trd
#define __sin       bridge_skip___sin_trd
#define __rem_pio2  bridge_skip___rem_pio2_trd
#define PIo2    PIo2_trd
#define ipio2   ipio2_trd
#define zero    zero_trd
#define one     one_trd
#define two24   two24_trd
#define twon24  twon24_trd
#define half    half_trd
#define invpio2 invpio2_trd
#define pio2_1  pio2_1_trd
#define pio2_1t pio2_1t_trd
#define pio2_2  pio2_2_trd
#define pio2_2t pio2_2t_trd
#define pio2_3  pio2_3_trd
#define pio2_3t pio2_3t_trd
#define C1      C1_trd
#define C2      C2_trd
#define C3      C3_trd
#define C4      C4_trd
#define C5      C5_trd
#define C6      C6_trd
#define S1      S1_trd
#define S2      S2_trd
#define S3      S3_trd
#define S4      S4_trd
#define S5      S5_trd
#define S6      S6_trd
#include "/home/leochanj/Desktop/libmcs/libm/mathd/internal/trigd.c"
#undef S6
#undef S5
#undef S4
#undef S3
#undef S2
#undef S1
#undef C6
#undef C5
#undef C4
#undef C3
#undef C2
#undef C1
#undef pio2_3t
#undef pio2_3
#undef pio2_2t
#undef pio2_2
#undef pio2_1t
#undef pio2_1
#undef invpio2
#undef half
#undef twon24
#undef two24
#undef one
#undef zero
#undef ipio2
#undef PIo2
#undef __rem_pio2
#undef __sin
#undef __cos

int bridge___rem_pio2_internal(double *x, double *y, int e0, int nx)
{
    return __rem_pio2_internal(x, y, e0, nx);
}

/* ========================================================================
 * Bridge 8: static inline int __rem_pio2f_internal(float *x, float *y, int e0, int nx)
 *   Source: mathf/internal/trigf.c
 *   Rename public: __cosf, __sinf, __rem_pio2f
 *   Rename all static variables with _trf suffix
 * ======================================================================== */
#define __cosf      bridge_skip___cosf_trf
#define __sinf      bridge_skip___sinf_trf
#define __rem_pio2f bridge_skip___rem_pio2f_trf
#define PIo2    PIo2_trf
#define ipio2   ipio2_trf
#define zero    zero_trf
#define one     one_trf
#define two8    two8_trf
#define twon8   twon8_trf
#define half    half_trf
#define invpio2 invpio2_trf
#define pio2_1  pio2_1_trf
#define pio2_1t pio2_1t_trf
#define pio2_2  pio2_2_trf
#define pio2_2t pio2_2t_trf
#define pio2_3  pio2_3_trf
#define pio2_3t pio2_3t_trf
#define C1      C1_trf
#define C2      C2_trf
#define C3      C3_trf
#define S1      S1_trf
#define S2      S2_trf
#define S3      S3_trf
#define S4      S4_trf
#include "/home/leochanj/Desktop/libmcs/libm/mathf/internal/trigf.c"
#undef S4
#undef S3
#undef S2
#undef S1
#undef C3
#undef C2
#undef C1
#undef pio2_3t
#undef pio2_3
#undef pio2_2t
#undef pio2_2
#undef pio2_1t
#undef pio2_1
#undef invpio2
#undef half
#undef twon8
#undef two8
#undef one
#undef zero
#undef ipio2
#undef PIo2
#undef __rem_pio2f
#undef __sinf
#undef __cosf

int bridge___rem_pio2f_internal(float *x, float *y, int e0, int nx)
{
    return __rem_pio2f_internal(x, y, e0, nx);
}
