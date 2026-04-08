#!/usr/bin/env python3
"""Convert core-math .wc files into clean .dat data files.

Reads binary64 and binary32 .wc files, strips comments and special values
(nan, inf, snan), expands symmetric functions (both +x and -x), and writes
one input per line as hex floats.

Output:
  tests/wc_data/<func>.dat   — cleaned inputs
  tests/wc_data/manifest.txt — function metadata (name, type, count)
"""

import os
import re

COREMATH = os.path.join(os.path.dirname(__file__), "..", "..",
                        "coremath_repo", "src")
OUT_DIR = os.path.join(os.path.dirname(__file__), "..", "tests", "wc_data")
MANIFEST = os.path.join(OUT_DIR, "manifest.txt")

# Map core-math function names to (libmcs_name, signature)
# Signatures: unary_d, binary_d, unary_f, binary_f
BINARY64_UNARY = {
    "acos": "acos", "acosh": "acosh", "asin": "asin", "asinh": "asinh",
    "atan": "atan", "atanh": "atanh", "cbrt": "cbrt", "cos": "cos",
    "cosh": "cosh", "erf": "erf", "erfc": "erfc", "exp": "exp",
    "exp2": "exp2", "expm1": "expm1", "lgamma": "lgamma", "log": "log",
    "log10": "log10", "log1p": "log1p", "log2": "log2",
    "sin": "sin", "sinh": "sinh", "tan": "tan", "tanh": "tanh",
    "tgamma": "tgamma",
}

BINARY64_BINARY = {
    "atan2": "atan2", "hypot": "hypot", "pow": "pow",
}

BINARY32_BINARY = {
    "atan2": "atan2f", "pow": "powf", "hypot": "hypotf",
}

# Symmetric functions: also test -x
SYMMETRIC = {"tanh", "sinh", "sin", "tan", "asinh", "atanh", "erf", "expm1", "cbrt"}


def is_special(s):
    """Check if a value is a special (nan/inf/snan) that we skip."""
    lower = s.lower().replace(" ", "").lstrip("+-")
    return "nan" in lower or "inf" in lower or "snan" in lower


def is_valid_numeric(v):
    """Check if a value is a valid numeric literal (hex float or decimal)."""
    v = v.strip().lstrip("+-")
    if v.startswith("0x") or v.startswith("0X"):
        return True
    if v.replace(".", "", 1).replace("e", "", 1).replace("-", "", 1).replace("+", "", 1).isdigit():
        return True
    if "." in v or "e" in v.lower() or "p" in v.lower():
        return True
    try:
        int(v)
        return True
    except ValueError:
        return False


def clean_line(line):
    """Strip comments and whitespace from a .wc line. Returns None if empty."""
    line = line.strip()
    if not line or line.startswith("#"):
        return None
    if "#" in line:
        line = line[:line.index("#")].strip()
    if not line:
        return None
    return line


def process_unary(wc_path, cm_name):
    """Process a unary .wc file. Returns list of input strings."""
    inputs = []
    with open(wc_path) as f:
        for line in f:
            line = clean_line(line)
            if line is None:
                continue
            if "," in line:
                continue
            if is_special(line):
                continue
            if not is_valid_numeric(line):
                continue
            inputs.append(line.strip())
            if cm_name in SYMMETRIC:
                # Add negated version
                v = line.strip()
                if v.startswith("-"):
                    inputs.append(v[1:])
                elif v.startswith("+"):
                    inputs.append("-" + v[1:])
                else:
                    inputs.append("-" + v)
    return inputs


def process_binary(wc_path):
    """Process a binary .wc file. Returns list of 'x,y' strings."""
    inputs = []
    with open(wc_path) as f:
        for line in f:
            line = clean_line(line)
            if line is None:
                continue
            parts = [p.strip() for p in line.split(",")]
            if len(parts) != 2:
                continue
            x, y = parts
            if is_special(x) or is_special(y):
                continue
            if not (is_valid_numeric(x) and is_valid_numeric(y)):
                continue
            inputs.append(f"{x.strip()},{y.strip()}")
    return inputs


def generate():
    os.makedirs(OUT_DIR, exist_ok=True)

    manifest_lines = []
    total = 0

    # Binary64 unary
    for cm_name, c_name in sorted(BINARY64_UNARY.items()):
        wc_path = os.path.join(COREMATH, "binary64", cm_name, f"{cm_name}.wc")
        if not os.path.exists(wc_path):
            continue
        inputs = process_unary(wc_path, cm_name)
        if not inputs:
            continue
        dat_path = os.path.join(OUT_DIR, f"{c_name}.dat")
        with open(dat_path, 'w') as f:
            f.write("\n".join(inputs) + "\n")
        manifest_lines.append(f"{c_name} unary_d {len(inputs)}")
        total += len(inputs)
        print(f"  {c_name}: {len(inputs)} inputs")

    # Binary64 binary
    for cm_name, c_name in sorted(BINARY64_BINARY.items()):
        wc_path = os.path.join(COREMATH, "binary64", cm_name, f"{cm_name}.wc")
        if not os.path.exists(wc_path):
            continue
        inputs = process_binary(wc_path)
        if not inputs:
            continue
        dat_path = os.path.join(OUT_DIR, f"{c_name}.dat")
        with open(dat_path, 'w') as f:
            f.write("\n".join(inputs) + "\n")
        manifest_lines.append(f"{c_name} binary_d {len(inputs)}")
        total += len(inputs)
        print(f"  {c_name}: {len(inputs)} inputs")

    # Binary32 binary
    for cm_name, c_name in sorted(BINARY32_BINARY.items()):
        wc_path = os.path.join(COREMATH, "binary32", cm_name, f"{cm_name}f.wc")
        if not os.path.exists(wc_path):
            continue
        inputs = process_binary(wc_path)
        if not inputs:
            continue
        dat_path = os.path.join(OUT_DIR, f"{c_name}.dat")
        with open(dat_path, 'w') as f:
            f.write("\n".join(inputs) + "\n")
        manifest_lines.append(f"{c_name} binary_f {len(inputs)}")
        total += len(inputs)
        print(f"  {c_name}: {len(inputs)} inputs")

    with open(MANIFEST, 'w') as f:
        f.write("\n".join(manifest_lines) + "\n")

    print(f"\nGenerated {len(manifest_lines)} .dat files in {OUT_DIR}: {total} total inputs")


if __name__ == "__main__":
    generate()
