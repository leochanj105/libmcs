#!/usr/bin/env python3
"""Convert glibc auto-libm-test-in to a bitwise-print C test file.

Only includes functions that exist in libmcs. Prints computed results
in %a format for C-vs-Rust diffing.
"""

import re
import os

GLIBC_IN = os.path.join(os.path.dirname(__file__), "..", "glibc_repo", "math", "auto-libm-test-in")
OUT = os.path.join(os.path.dirname(__file__), "..", "tests", "test_glibc_bitwise.c")

# libmcs functions and their signatures
# Unary double: func(double) -> double
UNARY_D = [
    "acos", "acosh", "asin", "asinh", "atan", "atanh", "cbrt", "cos", "cosh",
    "erf", "erfc", "exp", "exp2", "expm1", "log", "log10", "log1p", "log2",
    "sin", "sinh", "sqrt", "tan", "tanh", "tgamma",
    "j0", "j1", "y0", "y1",
]

# Binary double: func(double, double) -> double
BINARY_D = ["atan2", "hypot", "pow"]

# lgamma: unary but has signgam side effect
LGAMMA = ["lgamma"]

# Integer-first-arg: func(int, double) -> double
INT_FIRST_D = ["jn", "yn"]

# fma: func(double, double, double) -> double
FMA = ["fma"]

# Complex: func(complex) -> complex or func(complex) -> double
COMPLEX_UNARY = [
    "cacos", "cacosh", "casin", "casinh", "catan", "catanh",
    "ccos", "ccosh", "cexp", "clog", "csin", "csinh", "csqrt", "ctan", "ctanh",
]
COMPLEX_TO_REAL = ["cabs", "carg"]
COMPLEX_BINARY = ["cpow"]

ALL_FUNCS = set(UNARY_D + BINARY_D + LGAMMA + INT_FIRST_D + FMA +
                COMPLEX_UNARY + COMPLEX_TO_REAL + COMPLEX_BINARY)

# Float versions of functions that exist in libmcs (no Bessel for float)
UNARY_F = [
    "acos", "acosh", "asin", "asinh", "atan", "atanh", "cbrt", "cos", "cosh",
    "erf", "erfc", "exp", "exp2", "expm1", "log", "log10", "log1p", "log2",
    "sin", "sinh", "sqrt", "tan", "tanh", "tgamma",
]
BINARY_F = ["atan2", "hypot", "pow"]
LGAMMA_F = ["lgamma"]
FMA_F = ["fma"]
COMPLEX_UNARY_F = [
    "cacos", "cacosh", "casin", "casinh", "catan", "catanh",
    "ccos", "ccosh", "cexp", "clog", "csin", "csinh", "csqrt", "ctan", "ctanh",
]
COMPLEX_TO_REAL_F = ["cabs", "carg"]
COMPLEX_BINARY_F = ["cpow"]


def parse_value(s):
    """Convert a glibc symbolic value to a C expression."""
    s = s.strip()
    # Handle special constants
    mapping = {
        "inf": "INFINITY",
        "+inf": "INFINITY",
        "-inf": "(-INFINITY)",
        "nan": "NAN",
        "+nan": "NAN",
        "-nan": "(-NAN)",
        "qnan_value": "NAN",
        "snan_value": "__builtin_nans(\"\")",
        "-qnan_value": "(-NAN)",
        "-snan_value": "(-__builtin_nans(\"\"))",
        "pi": "M_PI",
        "-pi": "(-M_PI)",
        "pi/2": "(M_PI/2)",
        "-pi/2": "(-(M_PI/2))",
        "pi/4": "(M_PI/4)",
        "-pi/4": "(-(M_PI/4))",
        "pi/3": "(M_PI/3)",
        "-pi/3": "(-(M_PI/3))",
        "pi/6": "(M_PI/6)",
        "2pi": "(2*M_PI)",
        "2pi/3": "(2*M_PI/3)",
        "-2pi/3": "(-(2*M_PI/3))",
        "3pi/4": "(3*M_PI/4)",
        "-3pi/4": "(-(3*M_PI/4))",
        "e": "M_E",
        "1/e": "(1.0/M_E)",
        "0": "0.0",
        "+0": "0.0",
        "-0": "(-0.0)",
        "min": "DBL_MIN",
        "-min": "(-DBL_MIN)",
        "min_subnorm": "0x1p-1074",
        "-min_subnorm": "(-0x1p-1074)",
        "max": "DBL_MAX",
        "-max": "(-DBL_MAX)",
    }
    if s.lower() in mapping:
        return mapping[s.lower()]
    if s in mapping:
        return mapping[s]
    # Already a valid C literal (hex float or decimal)
    if re.match(r'^[+-]?0x[0-9a-fA-F]', s) or re.match(r'^[+-]?[0-9]', s):
        # Make sure it has a decimal point or is hex
        if '.' not in s and 'x' not in s.lower() and 'e' not in s.lower() and 'p' not in s.lower():
            # bare integer like "1" or "-2" -> "1.0" or "-2.0"
            if s.startswith('-'):
                return s + '.0'
            return s + '.0'
        return s
    # Unknown — skip
    return None


def generate():
    with open(GLIBC_IN) as f:
        lines = f.readlines()

    header = """\
/* AUTO-GENERATED from glibc auto-libm-test-in — do not edit.
 * Bitwise-print test: prints computed result in %%a format.
 * Compile against C or Rust lib, diff outputs.
 *
 * Source: glibc/math/auto-libm-test-in
 * License: LGPL 2.1+
 * Generator: gen_glibc_tests.py
 */
#include <math.h>
#include <complex.h>
#include <float.h>
#include <stdio.h>
#include "fault_guard.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main(void) {
    fault_guard_install();
"""
    out = [header]
    total = 0
    skipped = 0
    by_func = {}

    def guard(label, code):
        """Wrap a test in GUARDED() for fault isolation."""
        # Escape quotes in label for C string
        label_esc = label.replace('\\', '\\\\').replace('"', '\\"')
        return f'    GUARDED("{label_esc}", {code});\n'

    for line in lines:
        line = line.strip()
        if not line or line.startswith('#'):
            continue

        parts = line.split()
        func = parts[0]
        args = parts[1:]

        if func not in ALL_FUNCS:
            continue

        # Parse arguments
        parsed = []
        for a in args:
            # Skip flag-like args (e.g., "underflow" annotations)
            if a.startswith('underflow') or a.startswith('overflow') or \
               a.startswith('inexact') or a.startswith('invalid') or \
               a.startswith('divbyzero') or a.startswith('errno') or \
               a.startswith('ignore-zero-inf') or a.startswith('xfail') or \
               a == 'no-test-inline' or '=' in a:
                continue
            v = parse_value(a)
            if v is None:
                break
            parsed.append(v)
        else:
            # All args parsed successfully
            pass

        if func in UNARY_D:
            if len(parsed) < 1:
                skipped += 1
                continue
            x = parsed[0]
            lbl = f"{func} {x}"
            out.append(guard(lbl, f'printf("{func} %a = %a\\n", (double)({x}), (double){func}({x}));'))
            total += 1
            by_func[func] = by_func.get(func, 0) + 1
            if func in UNARY_F:
                ff = func + "f"
                out.append(guard(f"{ff} {x}", f'printf("{ff} %a = %a\\n", (double)(float)({x}), (double){ff}((float)({x})));'))
                total += 1
                by_func[ff] = by_func.get(ff, 0) + 1

        elif func in BINARY_D:
            if len(parsed) < 2:
                skipped += 1
                continue
            x, y = parsed[0], parsed[1]
            lbl = f"{func} {x} {y}"
            out.append(guard(lbl, f'printf("{func} %a %a = %a\\n", (double)({x}), (double)({y}), (double){func}({x}, {y}));'))
            total += 1
            by_func[func] = by_func.get(func, 0) + 1
            if func in BINARY_F:
                ff = func + "f"
                out.append(guard(f"{ff} {x} {y}", f'printf("{ff} %a %a = %a\\n", (double)(float)({x}), (double)(float)({y}), (double){ff}((float)({x}), (float)({y})));'))
                total += 1
                by_func[ff] = by_func.get(ff, 0) + 1

        elif func in LGAMMA:
            if len(parsed) < 1:
                skipped += 1
                continue
            x = parsed[0]
            out.append(guard(f"lgamma {x}", f'printf("lgamma %a = %a\\n", (double)({x}), (double)lgamma({x}));'))
            total += 1
            by_func["lgamma"] = by_func.get("lgamma", 0) + 1
            out.append(guard(f"lgammaf {x}", f'printf("lgammaf %a = %a\\n", (double)(float)({x}), (double)lgammaf((float)({x})));'))
            total += 1
            by_func["lgammaf"] = by_func.get("lgammaf", 0) + 1

        elif func in INT_FIRST_D:
            if len(parsed) < 2:
                skipped += 1
                continue
            n, x = parsed[0], parsed[1]
            n_int = n.replace('.0', '')
            out.append(guard(f"{func} {n_int} {x}", f'printf("{func} %s %a = %a\\n", "{n_int}", (double)({x}), (double){func}({n_int}, {x}));'))
            total += 1
            by_func[func] = by_func.get(func, 0) + 1

        elif func in FMA:
            if len(parsed) < 3:
                skipped += 1
                continue
            x, y, z = parsed[0], parsed[1], parsed[2]
            out.append(guard(f"fma {x} {y} {z}", f'printf("fma %a %a %a = %a\\n", (double)({x}), (double)({y}), (double)({z}), (double)fma({x}, {y}, {z}));'))
            total += 1
            by_func["fma"] = by_func.get("fma", 0) + 1
            out.append(guard(f"fmaf {x} {y} {z}", f'printf("fmaf %a %a %a = %a\\n", (double)(float)({x}), (double)(float)({y}), (double)(float)({z}), (double)fmaf((float)({x}), (float)({y}), (float)({z})));'))
            total += 1
            by_func["fmaf"] = by_func.get("fmaf", 0) + 1

        elif func in COMPLEX_UNARY:
            if len(parsed) < 2:
                skipped += 1
                continue
            re_part, im_part = parsed[0], parsed[1]
            lbl = f"{func} {re_part} {im_part}"
            out.append(guard(lbl,
                f'{{ double complex z = CMPLX({re_part}, {im_part}); '
                f'double complex r = {func}(z); '
                f'printf("{func} %a %a = %a %a\\n", '
                f'(double)({re_part}), (double)({im_part}), creal(r), cimag(r)); }}'))
            total += 1
            by_func[func] = by_func.get(func, 0) + 1
            if func in COMPLEX_UNARY_F:
                ff = func + "f"
                out.append(guard(f"{ff} {re_part} {im_part}",
                    f'{{ float complex zf = CMPLXF((float)({re_part}), (float)({im_part})); '
                    f'float complex rf = {ff}(zf); '
                    f'printf("{ff} %a %a = %a %a\\n", '
                    f'(double)(float)({re_part}), (double)(float)({im_part}), (double)crealf(rf), (double)cimagf(rf)); }}'))
                total += 1
                by_func[ff] = by_func.get(ff, 0) + 1

        elif func in COMPLEX_TO_REAL:
            if len(parsed) < 2:
                skipped += 1
                continue
            re_part, im_part = parsed[0], parsed[1]
            lbl = f"{func} {re_part} {im_part}"
            out.append(guard(lbl,
                f'{{ double complex z = CMPLX({re_part}, {im_part}); '
                f'printf("{func} %a %a = %a\\n", '
                f'(double)({re_part}), (double)({im_part}), (double){func}(z)); }}'))
            total += 1
            by_func[func] = by_func.get(func, 0) + 1
            if func in COMPLEX_TO_REAL_F:
                ff = func + "f"
                out.append(guard(f"{ff} {re_part} {im_part}",
                    f'{{ float complex zf = CMPLXF((float)({re_part}), (float)({im_part})); '
                    f'printf("{ff} %a %a = %a\\n", '
                    f'(double)(float)({re_part}), (double)(float)({im_part}), (double){ff}(zf)); }}'))
                total += 1
                by_func[ff] = by_func.get(ff, 0) + 1

        elif func in COMPLEX_BINARY:
            if len(parsed) < 4:
                skipped += 1
                continue
            r1, i1, r2, i2 = parsed[0], parsed[1], parsed[2], parsed[3]
            lbl = f"{func} {r1} {i1} {r2} {i2}"
            out.append(guard(lbl,
                f'{{ double complex a = CMPLX({r1}, {i1}); '
                f'double complex b = CMPLX({r2}, {i2}); '
                f'double complex r = {func}(a, b); '
                f'printf("{func} = %a %a\\n", creal(r), cimag(r)); }}'))
            total += 1
            by_func[func] = by_func.get(func, 0) + 1
            if func in COMPLEX_BINARY_F:
                ff = func + "f"
                out.append(guard(f"{ff} {r1} {i1} {r2} {i2}",
                    f'{{ float complex af = CMPLXF((float)({r1}), (float)({i1})); '
                    f'float complex bf = CMPLXF((float)({r2}), (float)({i2})); '
                    f'float complex rf = {ff}(af, bf); '
                    f'printf("{ff} = %a %a\\n", (double)crealf(rf), (double)cimagf(rf)); }}'))
                total += 1
                by_func[ff] = by_func.get(ff, 0) + 1

        else:
            skipped += 1
            continue

    out.append(f'    printf("\\nTotal: {total} glibc tests\\n");\n')
    out.append("    return 0;\n")
    out.append("}\n")

    with open(OUT, 'w') as f:
        f.writelines(out)

    print(f"Generated {OUT}: {total} test cases, {skipped} skipped")
    print(f"Functions ({len(by_func)}):")
    for func in sorted(by_func):
        print(f"  {func}: {by_func[func]}")


if __name__ == "__main__":
    generate()
