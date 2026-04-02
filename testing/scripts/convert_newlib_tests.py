#!/usr/bin/env python3
"""Convert Newlib libm test vectors to a standalone C test file.

Reads *_vec.c files from Newlib, extracts IEEE-754 hex test vectors,
and generates newlib_tests/test_newlib.c.

Vector format in Newlib:
  {accuracy, errno, 123, __LINE__, result_hi, result_lo, input_hi, input_lo}
where hi/lo are the 32-bit halves of an IEEE-754 double.

For 2-arg functions (like atan2):
  {accuracy, errno, 123, __LINE__, result_hi, result_lo, input1_hi, input1_lo, input2_hi, input2_lo}
"""

import os
import re
import glob

NEWLIB_TEST_DIR = os.path.join(os.path.dirname(__file__), "..",
    "newlib_tests", "newlib_repo", "newlib", "libm", "test")
OUT_DIR = os.path.join(os.path.dirname(__file__), "..", "newlib_tests")

# Functions with 2 args
TWO_ARG_FUNCS = {"atan2", "atan2f", "pow", "powf", "fmod", "fmodf",
                  "hypot", "hypotf"}

# Map vec file name to C function name
def vec_to_func(filename):
    return filename.replace("_vec.c", "")


def parse_vec_file(filepath):
    """Extract test vectors from a _vec.c file."""
    func = vec_to_func(os.path.basename(filepath))
    is_two_arg = func in TWO_ARG_FUNCS

    vectors = []
    with open(filepath) as f:
        for line in f:
            # Match: {accuracy, errno, 123, __LINE__, hex, hex, hex, hex[, hex, hex]}
            m = re.findall(r'0x[0-9a-fA-F]+', line)
            if len(m) >= 4:
                if is_two_arg and len(m) >= 6:
                    vectors.append({
                        "result_hi": m[0], "result_lo": m[1],
                        "input1_hi": m[2], "input1_lo": m[3],
                        "input2_hi": m[4], "input2_lo": m[5],
                        "nargs": 2,
                    })
                elif len(m) >= 4:
                    vectors.append({
                        "result_hi": m[0], "result_lo": m[1],
                        "input_hi": m[2], "input_lo": m[3],
                        "nargs": 1,
                    })
    return func, vectors


def main():
    os.makedirs(OUT_DIR, exist_ok=True)

    vec_files = sorted(glob.glob(os.path.join(NEWLIB_TEST_DIR, "*_vec.c")))
    if not vec_files:
        print(f"No vec files found in {NEWLIB_TEST_DIR}")
        return

    all_tests = {}
    for vf in vec_files:
        func, vectors = parse_vec_file(vf)
        if vectors:
            all_tests[func] = vectors

    # Generate C test file
    c_out = os.path.join(OUT_DIR, "test_newlib.c")
    with open(c_out, "w") as f:
        f.write("""/* Auto-generated from Newlib libm test vectors */
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static int total = 0, passed = 0, failed = 0;

static double make_double(uint32_t hi, uint32_t lo) {
    uint64_t bits = ((uint64_t)hi << 32) | lo;
    double d;
    memcpy(&d, &bits, 8);
    return d;
}

static int double_close(double a, double b, int ulp_tol) {
    if (isnan(a) && isnan(b)) return 1;
    if (isinf(a) && isinf(b)) return (a > 0) == (b > 0);
    if (a == b) return 1;
    /* ULP comparison */
    int64_t ai, bi;
    memcpy(&ai, &a, 8);
    memcpy(&bi, &b, 8);
    int64_t diff = ai - bi;
    if (diff < 0) diff = -diff;
    return diff <= ulp_tol;
}

static float make_float(uint32_t bits) {
    float fl;
    memcpy(&fl, &bits, 4);
    return fl;
}

static int float_close(float a, float b, int ulp_tol) {
    if (isnan(a) && isnan(b)) return 1;
    if (isinf(a) && isinf(b)) return (a > 0) == (b > 0);
    if (a == b) return 1;
    int32_t ai, bi;
    memcpy(&ai, &a, 4);
    memcpy(&bi, &b, 4);
    int32_t diff = ai - bi;
    if (diff < 0) diff = -diff;
    return diff <= ulp_tol;
}

""")

        # For each function, generate a test function
        for func, vectors in sorted(all_tests.items()):
            is_float = func.endswith("f") and func not in ("erf", "modf", "ceil", "floor")
            nargs = vectors[0]["nargs"] if vectors else 1

            f.write(f"static void test_{func}(void) {{\n")

            for i, v in enumerate(vectors):
                if nargs == 1:
                    if is_float:
                        f.write(f"    {{ float inp = make_float({v['input_hi']}); ")
                        f.write(f"float exp = make_float({v['result_hi']}); ")
                        f.write(f"float res = {func}(inp); ")
                        f.write(f"total++; if (float_close(res, exp, 2)) passed++; ")
                        f.write(f"else {{ failed++; printf(\"FAIL {func} vec {i}: got %a exp %a inp %a\\n\", (double)res, (double)exp, (double)inp); }} }}\n")
                    else:
                        f.write(f"    {{ double inp = make_double({v['input_hi']}, {v['input_lo']}); ")
                        f.write(f"double exp = make_double({v['result_hi']}, {v['result_lo']}); ")
                        f.write(f"double res = {func}(inp); ")
                        f.write(f"total++; if (double_close(res, exp, 2)) passed++; ")
                        f.write(f"else {{ failed++; printf(\"FAIL {func} vec {i}: got %a exp %a inp %a\\n\", res, exp, inp); }} }}\n")
                else:
                    if is_float:
                        f.write(f"    {{ float i1 = make_float({v['input1_hi']}); ")
                        f.write(f"float i2 = make_float({v['input2_hi']}); ")
                        f.write(f"float exp = make_float({v['result_hi']}); ")
                        f.write(f"float res = {func}(i1, i2); ")
                        f.write(f"total++; if (float_close(res, exp, 2)) passed++; ")
                        f.write(f"else {{ failed++; printf(\"FAIL {func} vec {i}\\n\"); }} }}\n")
                    else:
                        f.write(f"    {{ double i1 = make_double({v['input1_hi']}, {v['input1_lo']}); ")
                        f.write(f"double i2 = make_double({v['input2_hi']}, {v['input2_lo']}); ")
                        f.write(f"double exp = make_double({v['result_hi']}, {v['result_lo']}); ")
                        f.write(f"double res = {func}(i1, i2); ")
                        f.write(f"total++; if (double_close(res, exp, 2)) passed++; ")
                        f.write(f"else {{ failed++; printf(\"FAIL {func} vec {i}\\n\"); }} }}\n")

            f.write("}\n\n")

        # Main
        f.write("int main(void) {\n")
        for func in sorted(all_tests.keys()):
            f.write(f"    test_{func}();\n")
        f.write('    printf("\\nNewlib Vectors: %d passed, %d failed out of %d\\n", passed, failed, total);\n')
        f.write("    return failed > 0 ? 1 : 0;\n")
        f.write("}\n")

    total_vecs = sum(len(v) for v in all_tests.values())
    print(f"Generated {total_vecs} test vectors for {len(all_tests)} functions")
    print(f"  C: {c_out}")
    for func, vecs in sorted(all_tests.items()):
        print(f"    {func}: {len(vecs)} vectors")


if __name__ == "__main__":
    main()
