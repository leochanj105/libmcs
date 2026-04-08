/* test_bridge_trigd.c — bridge for static functions in trigd.c */
/* Provides: bridge___rem_pio2_internal */

#define __LIBMCS_WANT_COMPLEX
#define LIBMCS_WANT_COMPLEX

#include "/home/leochanj/Desktop/libmcs/libm/mathd/internal/trigd.c"

int bridge___rem_pio2_internal(double *x, double *y, int e0, int nx) {
    return __rem_pio2_internal(x, y, e0, nx);
}
