/* test_bridge_gammaf.c — bridge for static functions in gammaf.c */
/* Provides: bridge___sin_pif */

#define __LIBMCS_WANT_COMPLEX
#define LIBMCS_WANT_COMPLEX

#include "/home/leochanj/Desktop/libmcs/libm/mathf/internal/gammaf.c"

float bridge___sin_pif(float x) { return __sin_pif(x); }
