/* test_bridge_ctand.c — bridge for static functions in ctand.c */
/* Provides: bridge___ctans */

#define __LIBMCS_WANT_COMPLEX
#define LIBMCS_WANT_COMPLEX

#include "/home/leochanj/Desktop/libmcs/libm/complexd/ctand.c"

double bridge___ctans(double complex z) { return __ctans(z); }
