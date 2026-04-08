#!/usr/bin/env python3
"""Parse glibc libm-test-*.inc files for functions not in auto-libm-test-in.

Extracts test inputs from C struct initializer macros (TEST_f_f, TEST_ff_f,
etc.) and generates a bitwise-print C test file for C-vs-Rust diffing.

Functions covered: ceil, floor, trunc, round, rint, nearbyint, fabs, logb,
fdim, fmax, fmin, fmod, remainder, copysign, nextafter, nexttoward,
scalbn, scalbln, ilogb, frexp, modf, remquo, lrint, lround, llrint,
llround, conj, cproj.

License: test data from glibc (LGPL 2.1+).
"""

import re
import os

GLIBC_MATH = os.path.join(os.path.dirname(__file__), "..", "glibc_repo", "math")
OUT = os.path.join(os.path.dirname(__file__), "..", "tests", "test_glibc_inc_bitwise.c")

# --- Function categories and their macro / arity ---
# Unary double→double  (TEST_f_f: func, in, out, flags)
UNARY_D = ["ceil", "floor", "trunc", "round", "rint", "nearbyint", "fabs", "logb"]

# Binary double,double→double  (TEST_ff_f: func, in1, in2, out, flags)
BINARY_D = ["fdim", "fmax", "fmin", "fmod", "remainder", "copysign", "nextafter"]

# double,int→double  (TEST_fi_f: func, in1, in2_int, out, flags)
FLOAT_INT_D = ["scalbn"]

# double,long→double  (TEST_fl_f: func, in1, in2_long, out, flags)
FLOAT_LONG_D = ["scalbln"]

# double,double→double  (TEST_fj_f: func, in1, in2, out, flags)
# nexttoward second arg is long double but we cast to double
FLOAT_J_D = ["nexttoward"]

# double→int  (TEST_f_i: func, in, out_int, flags)
FLOAT_TO_INT = ["ilogb"]

# double→long  (TEST_f_l: func, in, out_long, flags)
FLOAT_TO_LONG = ["lrint", "lround"]

# double→long long  (TEST_f_L: func, in, out_ll, flags)
FLOAT_TO_LLONG = ["llrint", "llround"]

# double,int*→double  (TEST_fI_f1: func, in, out, out_int, flags)
UNARY_WITH_IPTR = ["frexp"]

# double,double*→double  (TEST_fF_f1: func, in, out, out_frac, flags)
UNARY_WITH_FPTR = ["modf"]

# double,double,int*→double  (TEST_ffI_f1: func, in1, in2, out, out_int, flags)
BINARY_WITH_IPTR = ["remquo"]

# complex→complex  (TEST_c_c: func, re_in, im_in, re_out, im_out, flags)
COMPLEX_CC = ["conj", "cproj"]

# --- Symbolic-constant mapping ---
SYM_MAP = {
    "plus_infty": "INFINITY",
    "minus_infty": "(-INFINITY)",
    "qnan_value": "NAN",
    "-qnan_value": "(-NAN)",
    "snan_value": '__builtin_nans("")',
    "-snan_value": '(-__builtin_nans(""))',
    "minus_zero": "(-0.0)",
    "plus_zero": "0.0",
    "lit_pi": "M_PI",
    "-lit_pi": "(-M_PI)",
    "lit_e": "M_E",
    "min_value": "DBL_MIN",
    "-min_value": "(-DBL_MIN)",
    "max_value": "DBL_MAX",
    "-max_value": "(-DBL_MAX)",
    "min_subnorm_value": "0x1p-1074",
    "-min_subnorm_value": "(-0x1p-1074)",
}

# For double (binary64): MANT_DIG=53, MIN_EXP=-1021
# Evaluate preprocessor conditions for binary64 on 64-bit Linux
COND_MAP = {
    "TEST_COND_binary32": False,
    "TEST_COND_binary64": True,
    "TEST_COND_binary128": False,
    "TEST_COND_intel96": False,
    "TEST_COND_m68k96": False,
    "TEST_COND_ibm128": False,
    "TEST_FLOATN": False,
}

MANT_DIG = 53
MIN_EXP = -1021


def eval_condition(cond_str):
    """Evaluate a preprocessor condition for binary64 on 64-bit Linux."""
    cond = cond_str.strip()

    # Direct boolean lookups
    if cond.startswith("!"):
        inner = cond[1:].strip()
        if inner in COND_MAP:
            return not COND_MAP[inner]
    if cond in COND_MAP:
        return COND_MAP[cond]

    # Compound: TEST_COND_m68k96 || TEST_COND_intel96
    if "||" in cond:
        return any(eval_condition(p) for p in cond.split("||"))
    if "&&" in cond:
        return all(eval_condition(p) for p in cond.split("&&"))

    # MANT_DIG comparisons
    m = re.match(r"MANT_DIG\s*>=\s*(\d+)", cond)
    if m:
        return MANT_DIG >= int(m.group(1))

    # MIN_EXP comparisons
    m = re.match(r"MIN_EXP\s*<=\s*(-?\d+)", cond)
    if m:
        return MIN_EXP <= int(m.group(1))
    m = re.match(r"MIN_EXP\s*-\s*MANT_DIG\s*<=\s*(-?\d+)", cond)
    if m:
        return (MIN_EXP - MANT_DIG) <= int(m.group(1))

    # LONG_MAX comparisons (64-bit: LONG_MAX = 0x7fffffffffffffff)
    m = re.match(r"LONG_MAX\s*>\s*0x([0-9a-fA-F]+)", cond)
    if m:
        return 0x7FFFFFFFFFFFFFFF > int(m.group(1), 16)
    m = re.match(r"LONG_MAX\s*>=\s*0x([0-9a-fA-F]+)", cond)
    if m:
        return 0x7FFFFFFFFFFFFFFF >= int(m.group(1), 16)

    # Default: include
    return True


def parse_value(s):
    """Convert a glibc .inc symbolic value to a C expression."""
    s = s.strip()
    if s == "IGNORE":
        return None  # caller decides whether to skip

    # Direct mapping
    if s in SYM_MAP:
        return SYM_MAP[s]

    # MANT_DIG references
    if s == "MANT_DIG":
        return str(MANT_DIG)
    m = re.match(r"MANT_DIG\s*-\s*(\d+)", s)
    if m:
        return str(MANT_DIG - int(m.group(1)))

    # Expressions with symbolic constants: min_value / 2, etc.
    expr = s
    changed = True
    while changed:
        changed = False
        for sym, repl in SYM_MAP.items():
            if sym in expr and sym not in ("0", "-0"):
                expr = expr.replace(sym, f"({repl})")
                changed = True
    # Check if it's a valid-looking C expression
    if re.match(r'^[0-9eE.xXpP+\-/*()LlUu _a-fA-F]+$', expr):
        # Strip L suffixes that are for long double
        expr = re.sub(r'(\d)L\b', r'\1', expr)
        return expr

    # Hex float or decimal
    if re.match(r'^[+-]?0x[0-9a-fA-F]', s) or re.match(r'^[+-]?[0-9]', s):
        return re.sub(r'(\d)L\b', r'\1', s)

    return None


def split_macro_args(s):
    """Split TEST_xxx(...) arguments respecting parentheses."""
    depth = 0
    parts = []
    current = []
    for ch in s:
        if ch == '(' :
            depth += 1
            current.append(ch)
        elif ch == ')':
            depth -= 1
            current.append(ch)
        elif ch == ',' and depth == 0:
            parts.append(''.join(current).strip())
            current = []
        else:
            current.append(ch)
    if current:
        parts.append(''.join(current).strip())
    return parts


def parse_inc_file(func_name, filepath):
    """Parse a libm-test-*.inc file, return list of (macro_type, [args...])."""
    if not os.path.exists(filepath):
        return []

    with open(filepath) as f:
        lines = f.readlines()

    # Handle preprocessor conditionals
    results = []
    include_stack = [True]  # stack of booleans; top = current inclusion state

    for line in lines:
        stripped = line.strip()

        # Preprocessor
        if stripped.startswith("#if "):
            cond = stripped[4:].strip()
            include_stack.append(include_stack[-1] and eval_condition(cond))
            continue
        if stripped.startswith("#elif "):
            cond = stripped[6:].strip()
            include_stack[-1] = include_stack[-2] and eval_condition(cond)
            continue
        if stripped == "#else":
            include_stack[-1] = include_stack[-2] and not include_stack[-1]
            continue
        if stripped == "#endif":
            if len(include_stack) > 1:
                include_stack.pop()
            continue

        if not include_stack[-1]:
            continue

        # Match TEST_xxx lines
        m = re.match(r'\s*(TEST_\w+)\s*\((.+)', stripped)
        if not m:
            continue

        macro = m.group(1)
        rest = m.group(2)

        # The args may span multiple lines (rare), but typically single line
        # Remove trailing ),  or )  at end
        rest = re.sub(r'\)\s*,?\s*$', '', rest)

        args = split_macro_args(rest)
        if len(args) < 2:
            continue

        results.append((macro, args))

    return results


def generate():
    header = """\
/* AUTO-GENERATED from glibc libm-test-*.inc files — do not edit.
 * Bitwise-print test: prints computed result in %a format.
 * Compile against C or Rust lib, diff outputs.
 *
 * Source: glibc/math/libm-test-*.inc
 * License: LGPL 2.1+
 * Generator: gen_glibc_inc_tests.py
 */
#include <math.h>
#include <complex.h>
#include <float.h>
#include <stdio.h>
#include <limits.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif

int main(void) {
"""
    out = [header]
    total = 0
    skipped = 0
    by_func = {}

    def emit(func, line):
        nonlocal total
        out.append(line)
        total += 1
        by_func[func] = by_func.get(func, 0) + 1

    # --- Unary double→double ---
    for func in UNARY_D:
        inc = os.path.join(GLIBC_MATH, f"libm-test-{func}.inc")
        for macro, args in parse_inc_file(func, inc):
            if macro != "TEST_f_f":
                continue
            # args: func_name, input, expected, flags
            if len(args) < 3:
                skipped += 1
                continue
            x = parse_value(args[1])
            if x is None:
                skipped += 1
                continue
            emit(func, f'    printf("{func} %a = %a\\n", (double)({x}), (double){func}({x}));\n')

    # --- Binary double,double→double ---
    for func in BINARY_D:
        inc = os.path.join(GLIBC_MATH, f"libm-test-{func}.inc")
        for macro, args in parse_inc_file(func, inc):
            if macro != "TEST_ff_f":
                continue
            if len(args) < 4:
                skipped += 1
                continue
            x = parse_value(args[1])
            y = parse_value(args[2])
            if x is None or y is None:
                skipped += 1
                continue
            emit(func, f'    printf("{func} %a %a = %a\\n", (double)({x}), (double)({y}), (double){func}({x}, {y}));\n')

    # --- double,int→double (scalbn) ---
    for func in FLOAT_INT_D:
        inc = os.path.join(GLIBC_MATH, f"libm-test-{func}.inc")
        for macro, args in parse_inc_file(func, inc):
            if macro != "TEST_fi_f":
                continue
            if len(args) < 4:
                skipped += 1
                continue
            x = parse_value(args[1])
            n = parse_value(args[2])
            if x is None or n is None:
                skipped += 1
                continue
            emit(func, f'    printf("{func} %a %s = %a\\n", (double)({x}), "{n}", (double){func}({x}, {n}));\n')

    # --- double,long→double (scalbln) ---
    for func in FLOAT_LONG_D:
        inc = os.path.join(GLIBC_MATH, f"libm-test-{func}.inc")
        for macro, args in parse_inc_file(func, inc):
            if macro != "TEST_fl_f":
                continue
            if len(args) < 4:
                skipped += 1
                continue
            x = parse_value(args[1])
            n = parse_value(args[2])
            if x is None or n is None:
                skipped += 1
                continue
            emit(func, f'    printf("{func} %a %s = %a\\n", (double)({x}), "{n}", (double){func}({x}, (long){n}));\n')

    # --- nexttoward (TEST_fj_f: double,long_double→double) ---
    for func in FLOAT_J_D:
        inc = os.path.join(GLIBC_MATH, f"libm-test-{func}.inc")
        for macro, args in parse_inc_file(func, inc):
            if macro != "TEST_fj_f":
                continue
            if len(args) < 4:
                skipped += 1
                continue
            x = parse_value(args[1])
            y = parse_value(args[2])
            if x is None or y is None:
                skipped += 1
                continue
            # Second arg is long double in glibc, cast to long double
            emit(func, f'    printf("{func} %a %a = %a\\n", (double)({x}), (double)({y}), (double){func}({x}, (long double)({y})));\n')

    # --- double→int (ilogb) ---
    for func in FLOAT_TO_INT:
        inc = os.path.join(GLIBC_MATH, f"libm-test-{func}.inc")
        for macro, args in parse_inc_file(func, inc):
            if macro != "TEST_f_i":
                continue
            if len(args) < 3:
                skipped += 1
                continue
            x = parse_value(args[1])
            if x is None:
                skipped += 1
                continue
            emit(func, f'    printf("{func} %a = %d\\n", (double)({x}), {func}({x}));\n')

    # --- double→long (lrint, lround) ---
    for func in FLOAT_TO_LONG:
        inc = os.path.join(GLIBC_MATH, f"libm-test-{func}.inc")
        for macro, args in parse_inc_file(func, inc):
            if macro != "TEST_f_l":
                continue
            if len(args) < 3:
                skipped += 1
                continue
            x = parse_value(args[1])
            if x is None:
                skipped += 1
                continue
            emit(func, f'    printf("{func} %a = %ld\\n", (double)({x}), {func}({x}));\n')

    # --- double→long long (llrint, llround) ---
    for func in FLOAT_TO_LLONG:
        inc = os.path.join(GLIBC_MATH, f"libm-test-{func}.inc")
        for macro, args in parse_inc_file(func, inc):
            if macro != "TEST_f_L":
                continue
            if len(args) < 3:
                skipped += 1
                continue
            x = parse_value(args[1])
            if x is None:
                skipped += 1
                continue
            emit(func, f'    printf("{func} %a = %lld\\n", (double)({x}), {func}({x}));\n')

    # --- frexp: double,int*→double (TEST_fI_f1: func, in, out, out_int, flags) ---
    for func in UNARY_WITH_IPTR:
        inc = os.path.join(GLIBC_MATH, f"libm-test-{func}.inc")
        for macro, args in parse_inc_file(func, inc):
            if macro != "TEST_fI_f1":
                continue
            if len(args) < 3:
                skipped += 1
                continue
            x = parse_value(args[1])
            if x is None:
                skipped += 1
                continue
            emit(func, f'    {{ int _exp; double _r = {func}({x}, &_exp); '
                        f'printf("{func} %a = %a %d\\n", (double)({x}), _r, _exp); }}\n')

    # --- modf: double,double*→double (TEST_fF_f1: func, in, out_frac, out_ipart, flags) ---
    for func in UNARY_WITH_FPTR:
        inc = os.path.join(GLIBC_MATH, f"libm-test-{func}.inc")
        for macro, args in parse_inc_file(func, inc):
            if macro != "TEST_fF_f1":
                continue
            if len(args) < 3:
                skipped += 1
                continue
            x = parse_value(args[1])
            if x is None:
                skipped += 1
                continue
            emit(func, f'    {{ double _ipart; double _r = {func}({x}, &_ipart); '
                        f'printf("{func} %a = %a %a\\n", (double)({x}), _r, _ipart); }}\n')

    # --- remquo: double,double,int*→double (TEST_ffI_f1: func, in1, in2, out, out_int, flags) ---
    for func in BINARY_WITH_IPTR:
        inc = os.path.join(GLIBC_MATH, f"libm-test-{func}.inc")
        for macro, args in parse_inc_file(func, inc):
            if macro != "TEST_ffI_f1":
                continue
            if len(args) < 4:
                skipped += 1
                continue
            x = parse_value(args[1])
            y = parse_value(args[2])
            if x is None or y is None:
                skipped += 1
                continue
            emit(func, f'    {{ int _quo; double _r = {func}({x}, {y}, &_quo); '
                        f'printf("{func} %a %a = %a %d\\n", (double)({x}), (double)({y}), _r, _quo); }}\n')

    # --- Complex→Complex (TEST_c_c: func, re_in, im_in, re_out, im_out, flags) ---
    for func in COMPLEX_CC:
        inc = os.path.join(GLIBC_MATH, f"libm-test-{func}.inc")
        for macro, args in parse_inc_file(func, inc):
            if macro != "TEST_c_c":
                continue
            if len(args) < 4:
                skipped += 1
                continue
            re_in = parse_value(args[1])
            im_in = parse_value(args[2])
            if re_in is None or im_in is None:
                skipped += 1
                continue
            emit(func, f'    {{ double complex z = CMPLX({re_in}, {im_in}); '
                        f'double complex r = {func}(z); '
                        f'printf("{func} %a %a = %a %a\\n", '
                        f'(double)({re_in}), (double)({im_in}), creal(r), cimag(r)); }}\n')

    out.append(f'    printf("\\nTotal: {total} glibc-inc tests\\n");\n')
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
