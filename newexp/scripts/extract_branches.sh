#!/usr/bin/env bash
set -euo pipefail

# extract_branches.sh — extract branch targets using LLVM coverage.
# Compiles all C source with coverage instrumentation, runs a trivial binary,
# then extracts all branch locations from llvm-cov output.
#
# Output format: "file.c, Branch (line:col)" — one per line.
# Run once; output is reused across all scenarios/rounds.
#
# Usage: extract_branches.sh <output_file>

OUTPUT="${1:?Usage: extract_branches.sh <output_file>}"

if [ -f "$OUTPUT" ] && [ -s "$OUTPUT" ]; then
    echo "Branches already extracted: ${OUTPUT} ($(wc -l < "$OUTPUT") lines)"
    exit 0
fi

LIBMCS="${LIBMCS:-/home/leochanj/Desktop/libmcs/libm}"
C_SRC_DIRS="${C_SRC_DIRS:-${LIBMCS}/mathd ${LIBMCS}/mathf ${LIBMCS}/common ${LIBMCS}/complexd ${LIBMCS}/complexf}"
C_INCLUDE_DIRS="${C_INCLUDE_DIRS:-${LIBMCS}/include}"
CC="${CC:-clang-21}"
LLVM_PROFDATA="${LLVM_PROFDATA:-llvm-profdata-21}"
LLVM_COV="${LLVM_COV:-llvm-cov-21}"

echo "Extracting branch targets (LLVM)..."

BDIR=$(mktemp -d)
trap 'rm -rf "$BDIR"' EXIT

# Collect all .c files, exclude fenv.c (has #error, not compilable)
SRCS_FILE=$(mktemp)
for d in $C_SRC_DIRS; do
    [ -d "$d" ] || continue
    find "$d" -name '*.c' -type f 2>/dev/null | grep -v fenv.c >> "$SRCS_FILE"
done
N_SRCS=$(wc -l < "$SRCS_FILE")

INC_FLAGS=""
for d in $C_INCLUDE_DIRS; do INC_FLAGS="$INC_FLAGS -I$d"; done

# Compile with coverage instrumentation
echo "  Compiling ${N_SRCS} source files..."
cd "$BDIR"
xargs $CC $INC_FLAGS -fprofile-instr-generate -fcoverage-mapping -c < "$SRCS_FILE" 2>/dev/null || {
    echo "Error: compilation failed" >&2
    exit 1
}

ar rcs libsrc.a ./*.o 2>/dev/null
rm -f ./*.o

# Minimal main
cat > main.c << 'MAINEOF'
#include <math.h>
int main(void) { volatile double x = sin(0.5); (void)x; return 0; }
MAINEOF
$CC $INC_FLAGS -fprofile-instr-generate -fcoverage-mapping -c main.c -o main.o 2>/dev/null

# Link with --whole-archive so all library functions get coverage data
$CC -fprofile-instr-generate main.o \
    -Wl,--whole-archive libsrc.a -Wl,--no-whole-archive \
    -lm -o branch_bin 2>/dev/null || {
    echo "Error: link failed" >&2
    exit 1
}

# Run to generate profdata
LLVM_PROFILE_FILE="${BDIR}/default.profraw" ./branch_bin >/dev/null 2>&1 || true
$LLVM_PROFDATA merge -sparse "${BDIR}/default.profraw" -o "${BDIR}/coverage.profdata"

# Extract branches
echo "  Extracting branches from coverage data..."
$LLVM_COV show ./branch_bin \
    -instr-profile="${BDIR}/coverage.profdata" \
    --show-branches=count 2>/dev/null | \
awk '
/^\/.*\.c:$/ {
    n = split($0, a, "/")
    fname = substr(a[n], 1, length(a[n])-1)
    next
}
/Branch \(/ {
    match($0, /Branch \([0-9]+:[0-9]+\)/)
    if (RSTART > 0) print fname ", " substr($0, RSTART, RLENGTH)
}
' | sort -u > "${BDIR}/raw_branches.txt" || true

TOTAL=$(wc -l < "${BDIR}/raw_branches.txt")

{
    echo "# Reachable branches in the C library"
    echo "# Format: filename.c, Branch (line:col)"
    echo "# Total unique branches: ${TOTAL}"
    echo ""
    cat "${BDIR}/raw_branches.txt"
} > "$OUTPUT"

echo "  ${TOTAL} branches -> ${OUTPUT}"
