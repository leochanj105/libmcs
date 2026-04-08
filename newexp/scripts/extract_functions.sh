#!/usr/bin/env bash
set -euo pipefail

# extract_functions.sh — extract all C function names from the library.
# Output: one function per line, [static] prefix for internal functions.
# Run once; output is reused across all scenarios/rounds.
#
# Usage: extract_functions.sh <output_file>

OUTPUT="${1:?Usage: extract_functions.sh <output_file>}"

LIBMCS="${LIBMCS:-/home/leochanj/Desktop/libmcs/libm}"
C_SRC_DIRS="${C_SRC_DIRS:-${LIBMCS}/mathd ${LIBMCS}/mathf ${LIBMCS}/common ${LIBMCS}/complexd ${LIBMCS}/complexf}"

if [ -f "$OUTPUT" ]; then
    echo "Functions already extracted: ${OUTPUT} ($(wc -l < "$OUTPUT") lines)"
    exit 0
fi

echo "Extracting function list from C source..."

{
    echo "# C functions in libmcs"
    echo "# [static] prefix = internal linkage, not callable from test_suite.c"
    echo ""
    for d in $C_SRC_DIRS; do
        [ -d "$d" ] || continue
        find "$d" -name '*.c' -type f 2>/dev/null | grep -v fenv.c | sort | while read -r f; do
            awk '
            /^#/                    { next }
            /^(if|for|while|switch|return|else|do|typedef|struct|union|enum)\b/ { next }
            /^[a-zA-Z_][a-zA-Z0-9_ *]*[[:space:]+\*]([a-zA-Z_][a-zA-Z0-9_]*)[[:space:]]*\(/ {
                is_static = ($0 ~ /^static /)
                line = $0
                sub(/\(.*/, "", line)
                gsub(/[*]/, " ", line)
                n = split(line, parts, /[[:space:]]+/)
                if (n >= 1 && parts[n] ~ /^[a-zA-Z_]/) {
                    if (is_static)
                        print "[static] " parts[n]
                    else
                        print parts[n]
                }
            }
            ' "$f" 2>/dev/null || true
        done
    done
} | sort -u > "$OUTPUT"

echo "  $(grep -c -v '^#' "$OUTPUT" | head -1) functions -> ${OUTPUT}"
