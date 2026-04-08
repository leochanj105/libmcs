#!/usr/bin/env bash
set -uo pipefail

# run_c_baseline.sh — compile and run all tests against the C library only.
# Produces baseline outputs that can later be diffed against Rust (or other).
#
# Usage: run_c_baseline.sh [-c C_LIB] [-I INCDIR] [-o OUTDIR] [--quick | --full]
#
# Defaults:
#   C_LIB  = ../../build-x86_64-linux-gnu/bin/libm.a
#   INCDIR = ../../libm/include
#   OUTDIR = results/c_baseline
#   MODE   = quick

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
C_LIB="" INCDIR="" OUTDIR="" MODE="quick"

while [[ $# -gt 0 ]]; do
    case "$1" in
        -c) C_LIB="$2"; shift 2 ;;
        -I) INCDIR="$2"; shift 2 ;;
        -o) OUTDIR="$2"; shift 2 ;;
        --quick) MODE="quick"; shift ;;
        --full)  MODE="full"; shift ;;
        *) echo "Usage: $0 [-c C_LIB] [-I INCDIR] [-o OUTDIR] [--quick|--full]"; exit 1 ;;
    esac
done

# Defaults
[ -z "$C_LIB" ]  && C_LIB="${SCRIPT_DIR}/../../build-x86_64-linux-gnu/bin/libm.a"
[ -z "$INCDIR" ] && INCDIR="${SCRIPT_DIR}/../../libm/include"
[ -z "$OUTDIR" ] && OUTDIR="${SCRIPT_DIR}/results/c_baseline"

[ -f "$C_LIB" ]  || { echo "Error: C library not found: $C_LIB"; exit 1; }
[ -d "$INCDIR" ] || { echo "Error: include dir not found: $INCDIR"; exit 1; }

CC="${CC:-gcc}"
BDIR=$(mktemp -d)
trap 'rm -rf "$BDIR"' EXIT
mkdir -p "$OUTDIR"

total_tests=0
total_failed=0

compile_and_run() {
    local name="$1" src="$2" outfile="$3"

    if ! $CC -O0 -I"$INCDIR" "$src" "$C_LIB" -fno-builtin -lm \
         -o "$BDIR/${name}" 2>"$BDIR/${name}_err"; then
        echo "  FAIL (compile): ${name}"
        head -5 "$BDIR/${name}_err" | sed 's/^/    /'
        total_failed=$(( total_failed + 1 ))
        return 1
    fi

    if ! timeout 600 "$BDIR/${name}" > "$outfile" 2>/dev/null; then
        echo "  FAIL (timeout/crash): ${name}"
        total_failed=$(( total_failed + 1 ))
        return 1
    fi

    local lines
    lines=$(wc -l < "$outfile" | tr -d ' ')
    total_tests=$(( total_tests + lines ))
    printf "  %-30s %7d tests\n" "$name" "$lines"
    return 0
}

echo "========================================"
echo "Judger V2 — C Baseline Output"
echo "Date: $(date '+%Y-%m-%d %H:%M')"
echo "========================================"
echo "C library: $C_LIB"
echo "Include:   $INCDIR"
echo "Output:    $OUTDIR"
echo "WC mode:   $MODE"
echo ""

# --- GLIBC auto-libm-test-in ---
GLIBC_SRC="${SCRIPT_DIR}/tests/test_glibc_bitwise.c"
if [ -f "$GLIBC_SRC" ]; then
    echo "--- glibc (auto-libm-test-in) ---"
    compile_and_run "glibc" "$GLIBC_SRC" "$OUTDIR/glibc.out"
    echo ""
fi

# --- GLIBC .inc files ---
GLIBC_INC_SRC="${SCRIPT_DIR}/tests/test_glibc_inc_bitwise.c"
if [ -f "$GLIBC_INC_SRC" ]; then
    echo "--- glibc (libm-test-*.inc) ---"
    compile_and_run "glibc_inc" "$GLIBC_INC_SRC" "$OUTDIR/glibc_inc.out"
    echo ""
fi

# --- Core-math worst cases (via run_wc.sh) ---
echo "--- core-math worst cases (${MODE}) ---"
bash "${SCRIPT_DIR}/run_wc.sh" -c "$C_LIB" -I "$INCDIR" -o "$OUTDIR/wc" --${MODE}
wc_lines=$(cat "$OUTDIR"/wc/*.out 2>/dev/null | wc -l | tr -d ' ')
total_tests=$(( total_tests + wc_lines ))
echo ""

echo "========================================"
echo "SUMMARY"
echo "========================================"
echo "Failures: ${total_failed}"
echo "Total test outputs: ${total_tests}"
echo "Saved to: ${OUTDIR}/"
