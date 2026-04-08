Libmcs is a C math library (libm implementation).

Comparison rule: all outputs must be bitwise exact. Use %a hex float format for
all float/double values. Zero tolerance for divergence.

The library has no global/static mutable state except signgam (used by lgamma).
