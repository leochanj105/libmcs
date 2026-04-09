#!/usr/bin/env bash
set -uo pipefail

# run_coverage.sh — Build libmcs with LLVM coverage, run all tests, report.
#
# Usage: run_coverage.sh [--quick | --full] [-o OUTDIR]
#
# Requires: clang, llvm-profdata, llvm-cov
#
# Defaults:
#   MODE   = full
#   OUTDIR = results/coverage

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LIBMCS_ROOT="${SCRIPT_DIR}/../.."
MODE="full" OUTDIR=""

while [[ $# -gt 0 ]]; do
    case "$1" in
        --quick) MODE="quick"; shift ;;
        --full)  MODE="full"; shift ;;
        -o) OUTDIR="$2"; shift 2 ;;
        *) echo "Usage: $0 [--quick|--full] [-o OUTDIR]"; exit 1 ;;
    esac
done

[ -z "$OUTDIR" ] && OUTDIR="${SCRIPT_DIR}/results/coverage"

# Prefer versioned LLVM tools (clang-21, etc.), fall back to unversioned
CLANG="${CLANG:-$(which clang-21 2>/dev/null || which clang)}"
PROFDATA="${PROFDATA:-$(which llvm-profdata-21 2>/dev/null || which llvm-profdata)}"
LLVMCOV="${LLVMCOV:-$(which llvm-cov-21 2>/dev/null || which llvm-cov)}"

for tool in "$CLANG" "$PROFDATA" "$LLVMCOV"; do
    [ -x "$tool" ] || { echo "Error: $tool not found"; exit 1; }
done
echo "Using: $CLANG, $PROFDATA, $LLVMCOV"

INCDIR="${LIBMCS_ROOT}/libm/include"
COVFLAGS="-fprofile-instr-generate -fcoverage-mapping -O0 -fno-builtin"

mkdir -p "$OUTDIR"

# --- Step 1: Build libmcs with coverage ---
echo "Building libmcs with LLVM coverage..."
(cd "$LIBMCS_ROOT" && make clean > /dev/null 2>&1 && \
 make CC="$CLANG" EXTRA_CFLAGS="-fprofile-instr-generate -fcoverage-mapping -O0" > /dev/null 2>&1) || \
    { echo "FATAL: build failed"; exit 1; }

LIBM="${LIBMCS_ROOT}/build-x86_64-linux-gnu/bin/libm.a"
[ -f "$LIBM" ] || { echo "FATAL: $LIBM not found after build"; exit 1; }

# --- Step 2: Compile test programs ---
echo "Compiling test programs..."
$CLANG $COVFLAGS -I"$INCDIR" "${SCRIPT_DIR}/tests/test_glibc_bitwise.c" "$LIBM" -lm \
    -o "$OUTDIR/test_glibc" 2>/dev/null || { echo "FATAL: test_glibc compile failed"; exit 1; }
$CLANG $COVFLAGS -I"$INCDIR" "${SCRIPT_DIR}/tests/test_glibc_inc_bitwise.c" "$LIBM" -lm \
    -o "$OUTDIR/test_glibc_inc" 2>/dev/null || { echo "FATAL: test_glibc_inc compile failed"; exit 1; }
$CLANG $COVFLAGS -I"$INCDIR" "${SCRIPT_DIR}/tests/wc_driver.c" "$LIBM" -lm \
    -o "$OUTDIR/wc_driver" 2>/dev/null || { echo "FATAL: wc_driver compile failed"; exit 1; }

# --- Step 3: Run tests ---
rm -f "$OUTDIR"/*.profraw

echo "Running glibc tests..."
LLVM_PROFILE_FILE="$OUTDIR/glibc.profraw" "$OUTDIR/test_glibc" > /dev/null 2>&1
LLVM_PROFILE_FILE="$OUTDIR/glibc_inc.profraw" "$OUTDIR/test_glibc_inc" > /dev/null 2>&1

echo "Running core-math WC tests ($MODE)..."
DATA_DIR="${SCRIPT_DIR}/tests/wc_data"
MANIFEST="$DATA_DIR/manifest.txt"
QUICK_TARGET=10000

while read -r func_name sig_type count; do
    dat_file="$DATA_DIR/${func_name}.dat"
    [ -f "$dat_file" ] || continue

    if [ "$MODE" = "quick" ] && [ "$count" -gt "$QUICK_TARGET" ]; then
        stride=$(( count / QUICK_TARGET ))
        [ "$stride" -lt 2 ] && stride=2
        LLVM_PROFILE_FILE="$OUTDIR/wc_${func_name}.profraw" \
            awk "NR%${stride}==0" "$dat_file" | "$OUTDIR/wc_driver" "$func_name" > /dev/null 2>&1
    else
        LLVM_PROFILE_FILE="$OUTDIR/wc_${func_name}.profraw" \
            "$OUTDIR/wc_driver" "$func_name" < "$dat_file" > /dev/null 2>&1
    fi
done < "$MANIFEST"

# --- Step 4: Merge and report ---
echo "Merging profiles..."
$PROFDATA merge -sparse "$OUTDIR"/*.profraw -o "$OUTDIR/merged.profdata"

echo ""
echo "========================================"
echo "Coverage Report (${MODE} mode)"
echo "========================================"
echo ""

# Full per-file report (library only)
$LLVMCOV report "$OUTDIR/test_glibc" -instr-profile="$OUTDIR/merged.profdata" \
    -object="$OUTDIR/test_glibc_inc" -object="$OUTDIR/wc_driver" 2>&1 | \
    grep "^libm/" | sort > "$OUTDIR/per_file.txt"

# Print files with < 100% branch coverage
echo "Files with incomplete branch coverage:"
echo ""
printf "%-55s %8s %8s %8s\n" "File" "Branches" "Missed" "Cover"
echo "-------------------------------------------------------------------------------------------------------"
awk '{
    n = NF
    cover = $(n)
    branches = $(n-2) + 0
    missed = $(n-1) + 0
    if (branches > 0 && missed > 0)
        printf "%-55s %8d %8d %8s\n", $1, branches, missed, cover
}' "$OUTDIR/per_file.txt"

echo ""

# Summary: library-only totals
awk '{
    n = NF
    b = $(n-2) + 0
    m = $(n-1) + 0
    if ($(n) == "-") next
    total_b += b
    total_m += m

    # Lines
    lines = $(n-5) + 0
    lines_m = $(n-4) + 0
    total_l += lines
    total_lm += lines_m

    # Functions
    funcs = $(n-8) + 0
    funcs_m = $(n-7) + 0
    total_f += funcs
    total_fm += funcs_m
} END {
    printf "========================================"
    printf "\nLIBRARY SUMMARY (libm/ only)\n"
    printf "========================================\n"
    printf "Functions: %d / %d (%.1f%%)\n", total_f - total_fm, total_f, (total_f - total_fm) * 100.0 / total_f
    printf "Lines:     %d / %d (%.1f%%)\n", total_l - total_lm, total_l, (total_l - total_lm) * 100.0 / total_l
    printf "Branches:  %d / %d (%.1f%%)\n", total_b - total_m, total_b, (total_b - total_m) * 100.0 / total_b
    printf "\n"
}' "$OUTDIR/per_file.txt"

# --- Step 5: Rebuild without coverage ---
echo "Rebuilding libmcs without coverage..."
(cd "$LIBMCS_ROOT" && make clean > /dev/null 2>&1 && make > /dev/null 2>&1)
echo "Done. Report saved to: $OUTDIR/per_file.txt"
