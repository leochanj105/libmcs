#!/usr/bin/env bash
set -uo pipefail

# run.sh — run judger_v2 bitwise differential tests (glibc + core-math WC)
#
# Usage: run.sh -c C_LIB -r RUST_LIB [-I INCDIR] [-o REPORT]

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
C_LIB="" RUST_LIB="" INCDIR="" REPORT=""

while getopts "c:r:I:o:" opt; do
    case $opt in
        c) C_LIB="$OPTARG" ;; r) RUST_LIB="$OPTARG" ;;
        I) INCDIR="$OPTARG" ;; o) REPORT="$OPTARG" ;;
        *) echo "Usage: $0 -c C_LIB -r RUST_LIB [-I INCDIR] [-o REPORT]"; exit 1 ;;
    esac
done

[ -n "$C_LIB" ]    || { echo "Error: -c C_LIB required"; exit 1; }
[ -n "$RUST_LIB" ] || { echo "Error: -r RUST_LIB required"; exit 1; }
[ -f "$C_LIB" ]    || { echo "Error: $C_LIB not found"; exit 1; }
[ -f "$RUST_LIB" ] || { echo "Error: $RUST_LIB not found"; exit 1; }
[ -z "$INCDIR" ] && INCDIR=$(dirname "$(dirname "$C_LIB")")/include
[ -d "$INCDIR" ] || { echo "Error: include dir $INCDIR not found"; exit 1; }

CC="${CC:-gcc}"
BDIR=$(mktemp -d)
trap 'rm -rf "$BDIR"' EXIT

total_diff=0
total_lines=0

run_one() {
    local name="$1" src="$2"
    echo "--- ${name} ---"

    if ! $CC -I"$INCDIR" "$src" "$C_LIB" -fno-builtin -lm \
         -o "$BDIR/${name}_c" 2>"$BDIR/${name}_c_err"; then
        echo "  C compile FAILED"
        head -5 "$BDIR/${name}_c_err"
        return
    fi
    if ! $CC -I"$INCDIR" "$src" "$RUST_LIB" -fno-builtin -lm -lpthread -ldl \
         -o "$BDIR/${name}_r" 2>"$BDIR/${name}_r_err"; then
        echo "  Rust compile FAILED"
        head -5 "$BDIR/${name}_r_err"
        return
    fi

    timeout 600 "$BDIR/${name}_c" > "$BDIR/${name}_c.out" 2>/dev/null
    timeout 600 "$BDIR/${name}_r" > "$BDIR/${name}_r.out" 2>/dev/null

    local lines diff_lines ndiff
    lines=$(wc -l < "$BDIR/${name}_c.out" | tr -d ' ')
    diff_lines=$(diff "$BDIR/${name}_c.out" "$BDIR/${name}_r.out" \
                 | grep -c '^[<>]' 2>/dev/null || true)
    diff_lines=$(echo "$diff_lines" | tr -d '[:space:]')
    diff_lines=${diff_lines:-0}
    ndiff=$(( diff_lines / 2 ))

    echo "  Test cases:  ${lines}"
    echo "  Divergences: ${ndiff}"

    if [ "$ndiff" -gt 0 ]; then
        echo "  By function:"
        diff "$BDIR/${name}_c.out" "$BDIR/${name}_r.out" \
            | grep '^<' | awk '{print $2}' | sort | uniq -c | sort -rn \
            | sed 's/^/    /'
        diff "$BDIR/${name}_c.out" "$BDIR/${name}_r.out" \
            > "${SCRIPT_DIR}/tests/${name}_diff.txt" 2>/dev/null || true
        echo "  Saved: ${SCRIPT_DIR}/tests/${name}_diff.txt"
    fi

    total_diff=$(( total_diff + ndiff ))
    total_lines=$(( total_lines + lines ))
    echo ""
}

GLIBC_SRC="${SCRIPT_DIR}/tests/test_glibc_bitwise.c"
GLIBC_INC_SRC="${SCRIPT_DIR}/tests/test_glibc_inc_bitwise.c"
WC_DIR="${SCRIPT_DIR}/tests/wc"
WC_MANIFEST="${SCRIPT_DIR}/tests/wc_manifest.txt"

{
    echo "========================================"
    echo "Judger V2 — Bitwise Differential Test"
    echo "Date: $(date '+%Y-%m-%d %H:%M')"
    echo "========================================"
    echo "C library:    $C_LIB"
    echo "Rust library: $RUST_LIB"
    echo "Method:       bitwise %a comparison, zero tolerance"
    echo ""

    [ -f "$GLIBC_SRC" ] && run_one "glibc" "$GLIBC_SRC"
    [ -f "$GLIBC_INC_SRC" ] && run_one "glibc_inc" "$GLIBC_INC_SRC"

    # Core-math WC: per-function files
    if [ -f "$WC_MANIFEST" ]; then
        echo "--- coremath_wc (per-function) ---"
        wc_total_lines=0
        wc_total_diff=0
        while read -r fname; do
            src="${WC_DIR}/${fname}"
            [ -f "$src" ] || continue
            func=$(echo "$fname" | sed 's/^wc_//;s/\.c$//')

            $CC -I"$INCDIR" "$src" "$C_LIB" -fno-builtin -lm \
                -o "$BDIR/wc_${func}_c" 2>/dev/null || { echo "  $func: C compile FAILED"; continue; }
            $CC -I"$INCDIR" "$src" "$RUST_LIB" -fno-builtin -lm -lpthread -ldl \
                -o "$BDIR/wc_${func}_r" 2>/dev/null || { echo "  $func: Rust compile FAILED"; continue; }

            timeout 120 "$BDIR/wc_${func}_c" > "$BDIR/wc_${func}_c.out" 2>/dev/null
            timeout 120 "$BDIR/wc_${func}_r" > "$BDIR/wc_${func}_r.out" 2>/dev/null

            lines=$(wc -l < "$BDIR/wc_${func}_c.out" | tr -d ' ')
            dl=$(diff "$BDIR/wc_${func}_c.out" "$BDIR/wc_${func}_r.out" \
                 | grep -c '^[<>]' 2>/dev/null || true)
            dl=$(echo "$dl" | tr -d '[:space:]'); dl=${dl:-0}
            ndiff=$(( dl / 2 ))

            wc_total_lines=$(( wc_total_lines + lines ))
            wc_total_diff=$(( wc_total_diff + ndiff ))

            if [ "$ndiff" -gt 0 ]; then
                printf "    %-12s %6d tests, %4d divergences\n" "$func" "$lines" "$ndiff"
                diff "$BDIR/wc_${func}_c.out" "$BDIR/wc_${func}_r.out" \
                    >> "${SCRIPT_DIR}/tests/wc_diff.txt" 2>/dev/null || true
            fi
        done < "$WC_MANIFEST"

        echo "  Total WC test cases:  ${wc_total_lines}"
        echo "  Total WC divergences: ${wc_total_diff}"
        total_diff=$(( total_diff + wc_total_diff ))
        total_lines=$(( total_lines + wc_total_lines ))
        echo ""
    fi

    echo "========================================"
    echo "SUMMARY"
    echo "========================================"
    echo "Total test cases: ${total_lines}"
    echo "Total divergences (C != Rust): ${total_diff}"
    echo ""
    if [ "$total_diff" -eq 0 ]; then
        echo "Result: BITWISE IDENTICAL"
    else
        echo "Result: ${total_diff} BITWISE DIVERGENCES"
    fi
} | tee "${REPORT:-/dev/null}"

[ "$total_diff" -eq 0 ] && exit 0 || exit 1
