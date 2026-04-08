/* test_bridge.c — wrappers for static/inline internal functions */

#define __LIBMCS_WANT_COMPLEX
#define LIBMCS_WANT_COMPLEX

/* Include the .c files that contain static functions we need to test */
#include "/home/leochanj/Desktop/libmcs/libm/mathd/internal/gammad.c"
#include "/home/leochanj/Desktop/libmcs/libm/mathf/internal/gammaf.c"
#include "/home/leochanj/Desktop/libmcs/libm/mathd/internal/trigd.c"
#include "/home/leochanj/Desktop/libmcs/libm/mathf/internal/trigf.c"
#include "/home/leochanj/Desktop/libmcs/libm/complexd/ctand.c"
#include "/home/leochanj/Desktop/libmcs/libm/complexf/ctanf.c"

/* Bridge wrappers for static double __sin_pi(double x) */
double bridge___sin_pi(double x) { return __sin_pi(x); }

/* Bridge wrappers for static float __sin_pif(float x) */
float bridge___sin_pif(float x) { return __sin_pif(x); }

/* Bridge wrappers for static inline int __rem_pio2_internal(double *x, double *y, int e0, int nx) */
int bridge___rem_pio2_internal(double *x, double *y, int e0, int nx) {
    return __rem_pio2_internal(x, y, e0, nx);
}

/* Bridge wrappers for static inline int __rem_pio2f_internal(float *x, float *y, int e0, int nx) */
int bridge___rem_pio2f_internal(float *x, float *y, int e0, int nx) {
    return __rem_pio2f_internal(x, y, e0, nx);
}

/* Bridge wrappers for static inline double __ctans(double complex z) */
double bridge___ctans(double complex z) { return __ctans(z); }

/* Bridge wrappers for static inline float __ctansf(float complex z) */
float bridge___ctansf(float complex z) { return __ctansf(z); }
