/* test_bridge.c — bridge for static functions in gammad.c */
/* Provides: bridge___sin_pi */
/* NOTE: Each source with statics needs its own bridge file to avoid
 * conflicting static const variable names. See test_bridge_*.c files. */

#define __LIBMCS_WANT_COMPLEX
#define LIBMCS_WANT_COMPLEX

#include "/home/leochanj/Desktop/libmcs/libm/mathd/internal/gammad.c"

double bridge___sin_pi(double x) { return __sin_pi(x); }
