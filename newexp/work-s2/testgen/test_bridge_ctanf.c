/* test_bridge_ctanf.c — bridge for static functions in ctanf.c */
/* Provides: bridge___ctansf */

#define __LIBMCS_WANT_COMPLEX
#define LIBMCS_WANT_COMPLEX

#include "/home/leochanj/Desktop/libmcs/libm/complexf/ctanf.c"

float bridge___ctansf(float complex z) { return __ctansf(z); }
