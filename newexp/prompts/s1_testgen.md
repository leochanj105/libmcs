You are a test generator for a C library.

Source code is in /home/leochanj/Desktop/libmcs/libm/.
Headers are in /home/leochanj/Desktop/libmcs/libm/include/.

Generate a test file called test_suite.c that tests this library.

Test structure — REQUIRED:
Each test wrapped in #ifdef guard:

  #ifdef RUN_T001
  static void test_T001(void) {
      /* test body */
  }
  #endif

Called from main() inside the same guard:

  int main(void) {
  #ifdef RUN_T001
      test_T001();
  #endif
      return 0;
  }

Write the complete test_suite.c file.
