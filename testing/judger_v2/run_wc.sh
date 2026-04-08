#!/usr/bin/env bash
set -uo pipefail

# run_wc.sh — Run core-math worst-case tests via the data+driver approach.
#
# Usage: run_wc.sh [-c C_LIB] [-I INCDIR] [-o OUTDIR] [--quick | --full]
#
# Modes:
#   --quick (default)  Deterministic stride to ~10K inputs per function.
#   --full             All worst-case inputs (16M+ total).
#
# Defaults:
#   C_LIB  = ../../build-x86_64-linux-gnu/bin/libm.a
#   INCDIR = ../../libm/include
#   OUTDIR = results/wc

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
C_LIB="" INCDIR="" OUTDIR="" MODE="quick"
QUICK_TARGET=10000  # target inputs per function in quick mode

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
[ -z "$OUTDIR" ] && OUTDIR="${SCRIPT_DIR}/results/wc"

[ -f "$C_LIB" ]  || { echo "Error: C library not found: $C_LIB"; exit 1; }
[ -d "$INCDIR" ] || { echo "Error: include dir not found: $INCDIR"; exit 1; }

CC="${CC:-gcc}"
DATA_DIR="${SCRIPT_DIR}/tests/wc_data"
MANIFEST="${DATA_DIR}/manifest.txt"
DRIVER_SRC="${SCRIPT_DIR}/tests/wc_driver.c"

[ -f "$MANIFEST" ]   || { echo "Error: manifest not found. Run: python3 scripts/gen_wc_data.py"; exit 1; }
[ -f "$DRIVER_SRC" ] || { echo "Error: wc_driver.c not found"; exit 1; }

mkdir -p "$OUTDIR"

# Compile driver once
BDIR=$(mktemp -d)
trap 'rm -rf "$BDIR"' EXIT

DRIVER_BIN="$BDIR/wc_driver"
echo "Compiling wc_driver..."
if ! $CC -O0 -I"$INCDIR" "$DRIVER_SRC" "$C_LIB" -fno-builtin -lm \
     -o "$DRIVER_BIN" 2>"$BDIR/compile_err"; then
    echo "FATAL: wc_driver compile failed"
    cat "$BDIR/compile_err"
    exit 1
fi

echo "========================================"
echo "Core-math Worst-Case Tests"
echo "Date: $(date '+%Y-%m-%d %H:%M')"
echo "========================================"
echo "C library: $C_LIB"
echo "Mode:      $MODE (target ~${QUICK_TARGET}/func for quick)"
echo "Output:    $OUTDIR"
echo ""

total_inputs=0
total_funcs=0

while read -r func_name sig_type count; do
    dat_file="${DATA_DIR}/${func_name}.dat"
    [ -f "$dat_file" ] || { echo "  SKIP ${func_name}: .dat not found"; continue; }

    outfile="${OUTDIR}/${func_name}.out"

    if [ "$MODE" = "quick" ] && [ "$count" -gt "$QUICK_TARGET" ]; then
        stride=$(( count / QUICK_TARGET ))
        [ "$stride" -lt 2 ] && stride=2
        awk "NR%${stride}==0" "$dat_file" | timeout 120 "$DRIVER_BIN" "$func_name" > "$outfile" 2>/dev/null
    else
        actual=$count
        timeout 300 "$DRIVER_BIN" "$func_name" < "$dat_file" > "$outfile" 2>/dev/null
    fi

    lines=$(wc -l < "$outfile" | tr -d ' ')
    total_inputs=$(( total_inputs + lines ))
    total_funcs=$(( total_funcs + 1 ))
    printf "  %-12s %7d / %7d inputs\n" "$func_name" "$lines" "$count"

done < "$MANIFEST"

echo ""
echo "========================================"
echo "SUMMARY"
echo "========================================"
echo "Functions: ${total_funcs}"
echo "Total test outputs: ${total_inputs}"
echo "Saved to: ${OUTDIR}/"
