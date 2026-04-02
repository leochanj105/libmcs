#!/usr/bin/env python3
"""Parse SDD RST special case tables into C test vectors.

Reads doc/sdd/.../NNNN_funcname.rst files, extracts the "Special cases" table,
and generates sdd_tests/test_sdd.c with one test per concrete special case.

Only emits tests for cases with concrete input/output values (e.g., +0, NaN, ±Inf).
Skips cases with set-based conditions (e.g., "∉ [-1, 1]", "> 0") since those
need representative inputs chosen separately.
"""

import os
import re
import glob
import json
import sys

SDD_DIR = os.path.join(os.path.dirname(__file__), "..", "..", "doc", "sdd",
    "5_Software_Design", "4_Software_Component_Design_Aspects_Of_Each_Component")
OUT_DIR = os.path.join(os.path.dirname(__file__), "..", "sdd_tests")

# Map RST function file names to C function names
FUNC_NAME_MAP = {
    "fpclassify": None,  # macro, skip
    "isfinite": None,
    "isinf": None,
    "isnan": None,
    "isnormal": None,
    "signbit": None,
}

# Map math notation to C values
VALUE_MAP = {
    "+0": "+0.0",
    "-0": "-0.0",
    "+Inf": "INFINITY",
    "-Inf": "-INFINITY",
    "Inf": "INFINITY",
    "+1": "1.0",
    "-1": "-1.0",
    "+2": "2.0",
    "+0.5": "0.5",
    "NaN": "NAN",
    "qNaN": "NAN",
    "sNaN": "__builtin_nans(\"\")",
    "-NaN": "-NAN",
    "+NaN": "NAN",
    "+\\pi": "M_PI",
    "-\\pi": "-M_PI",
    "\\pi": "M_PI",
}

# Special result comparisons
RESULT_CMP = {
    "NAN": "isnan(result)",
    "qNaN": "isnan(result)",
    "sNaN": "isnan(result)",
    "-NAN": "isnan(result)",
}

def parse_math(s):
    """Parse :math:`...` notation to a C expression or None if not concrete."""
    s = s.strip()
    # Remove :math:` and trailing `
    m = re.match(r':math:`(.+)`', s)
    if m:
        s = m.group(1)
    s = s.strip()

    # Direct lookups
    if s in VALUE_MAP:
        return VALUE_MAP[s]

    # ±0 means two tests needed
    if s == "±0":
        return None  # handled specially

    # ±Inf
    if s == "±Inf":
        return None  # handled specially

    # x (identity)
    if s == "x":
        return "INPUT"  # placeholder

    # Fractions like \frac{\pi}{2}
    m = re.match(r'[+-]?\\frac\{\\pi\}\{(\d+)\}', s)
    if m:
        sign = "-" if s.startswith("-") else ""
        return f"{sign}M_PI/{m.group(1)}.0"

    # Skip set-based conditions
    if any(c in s for c in ['\\notin', '\\in', '\\neq', '\\wedge', '\\setminus',
                             '<', '>', '\\{', 'k ', 'mathbb']):
        return None

    # Try parsing as a number
    try:
        float(s)
        return s
    except ValueError:
        pass

    return None


def is_nan_result(s):
    s = s.strip()
    m = re.match(r':math:`(.+)`', s)
    if m:
        s = m.group(1)
    return s in ("qNaN", "NaN", "sNaN", "-NaN", "+NaN")


def parse_rst_table(filepath):
    """Extract special case rows from an RST file."""
    with open(filepath) as f:
        lines = f.readlines()

    # Find "Special cases" section
    in_section = False
    table_lines = []
    for i, line in enumerate(lines):
        if "Special cases" in line:
            in_section = True
            continue
        if in_section:
            if line.startswith("| ") or line.startswith("|"):
                table_lines.append(line.strip())
            elif line.startswith("+") and "-" in line:
                continue  # table separator
            elif line.strip().startswith("=") and "=" * 5 in line:
                continue  # table header separator
            elif table_lines and not line.strip().startswith("+") and not line.strip().startswith("|"):
                break  # end of table

    if not table_lines:
        return []

    # Parse table rows
    rows = []
    for line in table_lines:
        cells = [c.strip() for c in line.split("|")[1:-1]]  # split by | and strip
        if len(cells) >= 2:
            # Skip header row
            if "x" == cells[0].strip() and ("Result" in cells[-1] or "y" in cells[1]):
                continue
            rows.append(cells)

    return rows


def func_name_from_path(path):
    """Extract function name from file path like 0100_acos.rst -> acos"""
    base = os.path.basename(path).replace(".rst", "")
    m = re.match(r'\d+_(.*)', base)
    if m:
        return m.group(1)
    return base


def generate_test_cases(func, rows, is_float=False):
    """Generate test case structs from parsed table rows."""
    suffix = "f" if is_float else ""
    cases = []

    for row in rows:
        if len(row) == 2:
            # 1-arg function: x, result
            x_val = parse_math(row[0])
            r_val = parse_math(row[1])
            is_nan = is_nan_result(row[1])

            if x_val is None:
                # Handle ±0 and ±Inf expansions
                raw = row[0].strip()
                m = re.match(r':math:`(.+)`', raw)
                if m:
                    raw = m.group(1)

                if raw == "±0":
                    for xv in ["+0.0", "-0.0"]:
                        rv = r_val if r_val != "INPUT" else xv
                        if rv is not None:
                            cases.append((func, [xv], rv, is_nan))
                    continue
                elif raw == "±Inf":
                    for xv in ["INFINITY", "-INFINITY"]:
                        rv = r_val
                        if rv is not None:
                            cases.append((func, [xv], rv, is_nan))
                    continue
                else:
                    continue

            if r_val is None and not is_nan:
                continue
            if r_val == "INPUT":
                r_val = x_val

            cases.append((func, [x_val], r_val if not is_nan else "NAN", is_nan))

        elif len(row) == 3:
            # 2-arg function: x, y, result
            x_val = parse_math(row[0])
            y_val = parse_math(row[1])
            r_val = parse_math(row[2])
            is_nan = is_nan_result(row[2])

            if x_val is None or y_val is None:
                continue
            if r_val is None and not is_nan:
                continue
            if r_val == "INPUT":
                continue

            cases.append((func, [x_val, y_val], r_val if not is_nan else "NAN", is_nan))

    return cases


def main():
    os.makedirs(OUT_DIR, exist_ok=True)

    rst_files = sorted(glob.glob(os.path.join(SDD_DIR, "[0-9]*.rst")))

    all_cases = []
    func_counts = {}

    for path in rst_files:
        func = func_name_from_path(path)

        # Skip macros and non-function entries
        if func in FUNC_NAME_MAP and FUNC_NAME_MAP[func] is None:
            continue
        if func in ("makefile",):
            continue

        rows = parse_rst_table(path)
        if not rows:
            continue

        cases = generate_test_cases(func, rows, is_float=False)
        if cases:
            all_cases.extend(cases)
            func_counts[func] = len(cases)

    # Also generate float versions
    float_cases = []
    for func, args, result, is_nan in all_cases:
        # Skip complex functions for float
        if func.startswith("c") and func not in ("cos", "cosh", "ceil", "cbrt", "copysign"):
            continue
        float_func = func + "f"
        float_cases.append((float_func, args, result, is_nan))

    all_cases.extend(float_cases)

    # Write JSON for reference
    json_out = os.path.join(OUT_DIR, "sdd_test_vectors.json")
    with open(json_out, "w") as f:
        json.dump([{
            "func": c[0], "args": c[1], "expected": c[2], "is_nan": c[3]
        } for c in all_cases], f, indent=2)

    # Write C test file
    c_out = os.path.join(OUT_DIR, "test_sdd.c")
    with open(c_out, "w") as f:
        f.write("""/* Auto-generated from SDD special case tables */
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static int total = 0, passed = 0, failed = 0;

static int double_eq(double a, double b) {
    if (isnan(a) && isnan(b)) return 1;
    if (isinf(a) && isinf(b)) return (a > 0) == (b > 0);
    /* Bitwise comparison for ±0 */
    uint64_t ai, bi;
    memcpy(&ai, &a, 8);
    memcpy(&bi, &b, 8);
    return ai == bi;
}

static int float_eq(float a, float b) {
    if (isnan(a) && isnan(b)) return 1;
    if (isinf(a) && isinf(b)) return (a > 0) == (b > 0);
    uint32_t ai, bi;
    memcpy(&ai, &a, 4);
    memcpy(&bi, &b, 4);
    return ai == bi;
}

#define TEST_D1(func, x, expected) do { \\
    total++; \\
    double result = func(x); \\
    if (double_eq(result, expected)) { passed++; } \\
    else { failed++; printf("FAIL %s(%a) = %a, expected %a\\n", #func, (double)(x), result, (double)(expected)); } \\
} while(0)

#define TEST_D2(func, x, y, expected) do { \\
    total++; \\
    double result = func(x, y); \\
    if (double_eq(result, expected)) { passed++; } \\
    else { failed++; printf("FAIL %s(%a, %a) = %a, expected %a\\n", #func, (double)(x), (double)(y), result, (double)(expected)); } \\
} while(0)

#define TEST_F1(func, x, expected) do { \\
    total++; \\
    float result = func(x); \\
    if (float_eq(result, expected)) { passed++; } \\
    else { failed++; printf("FAIL %s(%a) = %a, expected %a\\n", #func, (double)(x), (double)result, (double)(expected)); } \\
} while(0)

#define TEST_F2(func, x, y, expected) do { \\
    total++; \\
    float result = func(x, y); \\
    if (float_eq(result, expected)) { passed++; } \\
    else { failed++; printf("FAIL %s(%a, %a) = %a, expected %a\\n", #func, (double)(x), (double)(y), (double)result, (double)(expected)); } \\
} while(0)

#define TEST_NAN_D1(func, x) do { \\
    total++; \\
    double result = func(x); \\
    if (isnan(result)) { passed++; } \\
    else { failed++; printf("FAIL %s(%a) = %a, expected NaN\\n", #func, (double)(x), result); } \\
} while(0)

#define TEST_NAN_D2(func, x, y) do { \\
    total++; \\
    double result = func(x, y); \\
    if (isnan(result)) { passed++; } \\
    else { failed++; printf("FAIL %s(%a, %a) = %a, expected NaN\\n", #func, (double)(x), (double)(y), result); } \\
} while(0)

#define TEST_NAN_F1(func, x) do { \\
    total++; \\
    float result = func(x); \\
    if (isnan(result)) { passed++; } \\
    else { failed++; printf("FAIL %s(%a) = %a, expected NaN\\n", #func, (double)(x), (double)result); } \\
} while(0)

#define TEST_NAN_F2(func, x, y) do { \\
    total++; \\
    float result = func(x, y); \\
    if (isnan(result)) { passed++; } \\
    else { failed++; printf("FAIL %s(%a, %a) = %a, expected NaN\\n", #func, (double)(x), (double)(y), (double)result); } \\
} while(0)

int main(void) {
""")

        for func, args, expected, is_nan in all_cases:
            is_float = func.endswith("f") and func not in ("erf", "modf")
            nargs = len(args)

            if is_nan:
                if is_float:
                    if nargs == 1:
                        f.write(f"    TEST_NAN_F1({func}, {args[0]}f);\n")
                    else:
                        f.write(f"    TEST_NAN_F2({func}, {args[0]}f, {args[1]}f);\n")
                else:
                    if nargs == 1:
                        f.write(f"    TEST_NAN_D1({func}, {args[0]});\n")
                    else:
                        f.write(f"    TEST_NAN_D2({func}, {args[0]}, {args[1]});\n")
            else:
                if is_float:
                    if nargs == 1:
                        f.write(f"    TEST_F1({func}, {args[0]}f, {expected}f);\n")
                    else:
                        f.write(f"    TEST_F2({func}, {args[0]}f, {args[1]}f, {expected}f);\n")
                else:
                    if nargs == 1:
                        f.write(f"    TEST_D1({func}, {args[0]}, {expected});\n")
                    else:
                        f.write(f"    TEST_D2({func}, {args[0]}, {args[1]}, {expected});\n")

        f.write("""
    printf("\\nSDD Special Case Tests: %d passed, %d failed out of %d\\n", passed, failed, total);
    return failed > 0 ? 1 : 0;
}
""")

    print(f"Generated {len(all_cases)} test cases for {len(func_counts)} functions")
    print(f"  JSON: {json_out}")
    print(f"  C:    {c_out}")
    for func, count in sorted(func_counts.items()):
        print(f"    {func}: {count} cases (+ {count} float)")


if __name__ == "__main__":
    main()
