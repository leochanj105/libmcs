#!/usr/bin/env python3
"""Compare C and Rust test outputs using key-based matching.

Each line is expected to be: "funcname input... = result..."
Matches by key (everything before '='), compares result.

Produces a structured report:
- MISSING: functions in C output but not Rust (crash/not implemented)
- MISMATCH: same key, different result
- EXTRA: in Rust but not C (shouldn't happen)

Usage: compare_outputs.py <c_output> <rust_output> [-o report_file]
"""

import sys
import argparse
from collections import OrderedDict


def parse_output(filepath):
    """Parse test output into {key: full_line} dict."""
    entries = OrderedDict()
    with open(filepath) as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith("Total:") or line.startswith("==="):
                continue
            if '=' not in line:
                continue
            key = line.split('=')[0].strip()
            entries[key] = line
    return entries


def compare(c_file, r_file):
    c_entries = parse_output(c_file)
    r_entries = parse_output(r_file)

    missing = []    # in C but not Rust
    mismatch = []   # in both but different
    extra = []      # in Rust but not C

    for key, c_line in c_entries.items():
        if key not in r_entries:
            missing.append((key, c_line))
        elif c_line != r_entries[key]:
            mismatch.append((key, c_line, r_entries[key]))

    for key, r_line in r_entries.items():
        if key not in c_entries:
            extra.append((key, r_line))

    return missing, mismatch, extra, len(c_entries), len(r_entries)


def func_name(key):
    """Extract function name from key like 'sin 0x1p-1'."""
    return key.split()[0] if key.split() else key


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("c_output")
    parser.add_argument("rust_output")
    parser.add_argument("-o", "--output", default=None)
    args = parser.parse_args()

    missing, mismatch, extra, c_count, r_count = compare(
        args.c_output, args.rust_output)

    lines = []

    lines.append(f"C output: {c_count} test lines")
    lines.append(f"Rust output: {r_count} test lines")
    lines.append("")

    # Group missing by function
    if missing:
        missing_funcs = {}
        for key, c_line in missing:
            fn = func_name(key)
            if fn not in missing_funcs:
                missing_funcs[fn] = []
            missing_funcs[fn].append(c_line)

        lines.append(f"MISSING ({len(missing)} tests, {len(missing_funcs)} functions):")
        lines.append("Functions not in Rust output (not implemented or crashed):")
        for fn in sorted(missing_funcs):
            lines.append(f"  {fn}: {len(missing_funcs[fn])} tests")
        lines.append("")

    # Group mismatch by function
    if mismatch:
        mismatch_funcs = {}
        for key, c_line, r_line in mismatch:
            fn = func_name(key)
            if fn not in mismatch_funcs:
                mismatch_funcs[fn] = []
            mismatch_funcs[fn].append((c_line, r_line))

        lines.append(f"MISMATCH ({len(mismatch)} tests, {len(mismatch_funcs)} functions):")
        lines.append("C and Rust produce different results:")
        for fn in sorted(mismatch_funcs):
            pairs = mismatch_funcs[fn]
            lines.append(f"  {fn}: {len(pairs)} mismatches")
            for c_line, r_line in pairs[:3]:
                lines.append(f"    C:    {c_line}")
                lines.append(f"    Rust: {r_line}")
            if len(pairs) > 3:
                lines.append(f"    ... ({len(pairs) - 3} more)")
        lines.append("")

    if extra:
        lines.append(f"EXTRA ({len(extra)} tests in Rust but not C — unexpected):")
        for key, r_line in extra[:5]:
            lines.append(f"  {r_line}")
        lines.append("")

    # Summary
    total_failures = len(missing) + len(mismatch)
    lines.append("SUMMARY")
    lines.append(f"Tests passed:     {c_count - len(missing) - len(mismatch)}")
    lines.append(f"Tests failed:     {total_failures}")
    if missing:
        missing_funcs_list = sorted(set(func_name(k) for k, _ in missing))
        lines.append(f"Missing functions: {', '.join(missing_funcs_list)}")
    if mismatch:
        mismatch_funcs_list = sorted(set(func_name(k) for k, _, _ in mismatch))
        lines.append(f"Mismatched functions: {', '.join(mismatch_funcs_list)}")

    output = '\n'.join(lines)
    if args.output:
        with open(args.output, 'w') as f:
            f.write(output + '\n')
    print(output)


if __name__ == "__main__":
    main()
