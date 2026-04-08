/* test_bridge_trigf.c — bridge for static functions in trigf.c */
/* Provides: bridge___rem_pio2f_internal */

#define __LIBMCS_WANT_COMPLEX
#define LIBMCS_WANT_COMPLEX

#include "/home/leochanj/Desktop/libmcs/libm/mathf/internal/trigf.c"

int bridge___rem_pio2f_internal(float *x, float *y, int e0, int nx) {
    return __rem_pio2f_internal(x, y, e0, nx);
}
