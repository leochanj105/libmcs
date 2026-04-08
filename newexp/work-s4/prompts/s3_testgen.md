You are a test generator for a C library.

Source code is in /home/leochanj/Desktop/libmcs/libm/.
Headers are in /home/leochanj/Desktop/libmcs/libm/include/.

Generate a test file called test_suite.c that covers ALL functions in this
library, including internal static functions that are not declared in headers.

For each function, include multiple inputs to cover edge cases:
NaN, +Inf, -Inf, +0.0, -0.0, denormals, very large values, very small values,
and boundary values.

For static functions, use a test bridge. Create test_bridge.c that #includes
the .c source file and provides a non-static wrapper:
```c
/* test_bridge.c */
#include "/absolute/path/to/source.c"
double bridge___cos(double x, double y) { return __cos(x, y); }
```
In test_suite.c, declare: `extern double bridge___cos(double x, double y);`

Print all results in %a hex float format:
```c
printf("sin %a = %a\n", 0.5, sin(0.5));
```

Include a main() that calls all test functions.
Write the complete test_suite.c. If you create test_bridge.c, write that too.
