#!/usr/bin/env python3
"""Convert core-math worst-case (.wc) files to a bitwise-print C test file.

Reads binary64 and binary32 .wc files from the core-math repo. No cap on
inputs per function — uses all available worst cases.
"""

import os

COREMATH = os.path.join(os.path.dirname(__file__), "..", "..",
                        "coremath_repo", "src")
OUT_DIR = os.path.join(os.path.dirname(__file__), "..", "tests", "wc")
# Also generate a manifest for the runner
MANIFEST = os.path.join(os.path.dirname(__file__), "..", "tests", "wc_manifest.txt")

# Map core-math function names to libmcs C names (binary64)
UNARY_D = {
    "acos": "acos", "acosh": "acosh", "asin": "asin", "asinh": "asinh",
    "atan": "atan", "atanh": "atanh", "cbrt": "cbrt", "cos": "cos",
    "cosh": "cosh", "erf": "erf", "erfc": "erfc", "exp": "exp",
    "exp2": "exp2", "expm1": "expm1", "lgamma": "lgamma", "log": "log",
    "log10": "log10", "log1p": "log1p", "log2": "log2",
    "sin": "sin", "sinh": "sinh", "tan": "tan", "tanh": "tanh",
    "tgamma": "tgamma",
}

BINARY_D = {
    "atan2": "atan2", "hypot": "hypot", "pow": "pow",
}

# Symmetric: also test -x
SYMMETRIC = {"tanh", "sinh", "sin", "tan", "asinh", "atanh", "erf", "expm1", "cbrt"}

# binary32
BINARY_F = {
    "atan2": "atan2f", "pow": "powf", "hypot": "hypotf",
}


def read_wc(path):
    """Read .wc file, return list of cleaned input strings."""
    inputs = []
    with open(path) as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            # Strip inline comments
            if "#" in line:
                line = line[:line.index("#")].strip()
            if not line:
                continue
            # Skip symbolic entries (snan, nan, inf, bare ±0)
            lower = line.lower().replace(" ", "")
            if "nan" in lower or "inf" in lower or "snan" in lower:
                continue
            inputs.append(line)
    return inputs


def is_valid_hex_or_decimal(v):
    """Check if a value is a valid C numeric literal (not a symbolic name)."""
    v = v.strip().lstrip("+-")
    if v.startswith("0x") or v.startswith("0X"):
        return True
    if v.replace(".", "", 1).replace("e", "", 1).replace("-", "", 1).replace("+", "", 1).isdigit():
        return True
    if "." in v or "e" in v.lower() or "p" in v.lower():
        return True
    # Bare integer
    try:
        int(v)
        return True
    except ValueError:
        return False


def to_float_literal(v):
    """Convert a .wc value to a valid C float literal."""
    v = v.strip().lstrip('+')
    if 'x' in v.lower():
        return v + 'f'
    if '.' in v:
        return v + 'f'
    return v + '.0f'


# Maximum printf calls per C function to avoid GCC memory explosion
CHUNK_SIZE = 50000


def write_file(filepath, func_name, test_lines):
    """Write one per-function test C file, splitting into sub-functions."""
    with open(filepath, 'w') as f:
        f.write(f"""\
/* AUTO-GENERATED — {func_name} worst cases from core-math. Do not edit. */
#include <math.h>
#include <stdio.h>

""")
        # Split into sub-functions to keep each one small enough for GCC
        n_chunks = (len(test_lines) + CHUNK_SIZE - 1) // CHUNK_SIZE
        for i in range(n_chunks):
            start = i * CHUNK_SIZE
            end = min(start + CHUNK_SIZE, len(test_lines))
            f.write(f"static void chunk_{i}(void) {{\n")
            f.writelines(test_lines[start:end])
            f.write("}\n\n")

        f.write("int main(void) {\n")
        for i in range(n_chunks):
            f.write(f"    chunk_{i}();\n")
        f.write("    return 0;\n}\n")


def generate():
    os.makedirs(OUT_DIR, exist_ok=True)

    total = 0
    by_func = {}
    manifest = []

    # Unary binary64
    for cm_name, c_name in sorted(UNARY_D.items()):
        wc_path = os.path.join(COREMATH, "binary64", cm_name, f"{cm_name}.wc")
        if not os.path.exists(wc_path):
            continue
        inputs = read_wc(wc_path)
        func_lines = []
        count = 0
        for x in inputs:
            if "," in x:
                continue
            if not is_valid_hex_or_decimal(x):
                continue
            func_lines.append(f'    printf("{c_name} %a = %a\\n", (double)({x}), (double){c_name}({x}));\n')
            total += 1
            count += 1
            if cm_name in SYMMETRIC:
                func_lines.append(f'    printf("{c_name} %a = %a\\n", (double)(-({x})), (double){c_name}(-({x})));\n')
                total += 1
                count += 1
        if func_lines:
            outfile = os.path.join(OUT_DIR, f"wc_{c_name}.c")
            write_file(outfile, c_name, func_lines)
            manifest.append(f"wc_{c_name}.c")
            by_func[c_name] = count

    # Binary binary64
    for cm_name, c_name in sorted(BINARY_D.items()):
        wc_path = os.path.join(COREMATH, "binary64", cm_name, f"{cm_name}.wc")
        if not os.path.exists(wc_path):
            continue
        inputs = read_wc(wc_path)
        func_lines = []
        count = 0
        for entry in inputs:
            parts = [p.strip() for p in entry.split(",")]
            if len(parts) != 2:
                continue
            x, y = parts
            if not (is_valid_hex_or_decimal(x) and is_valid_hex_or_decimal(y)):
                continue
            func_lines.append(f'    printf("{c_name} %a %a = %a\\n", (double)({x}), (double)({y}), (double){c_name}({x}, {y}));\n')
            total += 1
            count += 1
        if func_lines:
            outfile = os.path.join(OUT_DIR, f"wc_{c_name}.c")
            write_file(outfile, c_name, func_lines)
            manifest.append(f"wc_{c_name}.c")
            by_func[c_name] = count

    # Binary binary32
    for cm_name, c_name in sorted(BINARY_F.items()):
        wc_path = os.path.join(COREMATH, "binary32", cm_name, f"{cm_name}f.wc")
        if not os.path.exists(wc_path):
            continue
        inputs = read_wc(wc_path)
        func_lines = []
        count = 0
        for entry in inputs:
            parts = [p.strip() for p in entry.split(",")]
            if len(parts) != 2:
                continue
            x, y = parts
            if not (is_valid_hex_or_decimal(x) and is_valid_hex_or_decimal(y)):
                continue
            xf, yf = to_float_literal(x), to_float_literal(y)
            func_lines.append(f'    printf("{c_name} %a %a = %a\\n", (double)({xf}), (double)({yf}), (double){c_name}({xf}, {yf}));\n')
            total += 1
            count += 1
        if func_lines:
            outfile = os.path.join(OUT_DIR, f"wc_{c_name}.c")
            # Append to existing file if the double version already exists
            if os.path.exists(outfile):
                with open(outfile, 'r') as f:
                    content = f.read()
                content = content.replace("    return 0;\n}\n", "")
                with open(outfile, 'w') as f:
                    f.write(content)
                    f.writelines(func_lines)
                    f.write("    return 0;\n}\n")
            else:
                write_file(outfile, c_name, func_lines)
                manifest.append(f"wc_{c_name}.c")
            by_func[c_name] = by_func.get(c_name, 0) + count

    with open(MANIFEST, 'w') as f:
        for m in manifest:
            f.write(m + "\n")

    print(f"Generated {len(manifest)} files in {OUT_DIR}: {total} total test cases")
    print(f"Functions ({len(by_func)}):")
    for func in sorted(by_func):
        print(f"  {func}: {by_func[func]}")


if __name__ == "__main__":
    generate()
