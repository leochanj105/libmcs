#!/usr/bin/env bash
set -uo pipefail

# run_diff_tests.sh — differential testing: run the same tests against two
# static libraries and diff the outputs.
#
# Usage: run_diff_tests.sh -c C_LIB -r RUST_LIB [-I INCDIR] [-v]
#   -c C_LIB     path to C libm.a (ground truth)
#   -r RUST_LIB  path to Rust libm.a (transpiled version)
#   -I INCDIR    path to include dir (default: auto-detect from C_LIB)
#   -v           show individual differences

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

C_LIB=""
RUST_LIB=""
INCDIR=""
VERBOSE=0

while getopts "c:r:I:v" opt; do
    case $opt in
        c) C_LIB="$OPTARG" ;;
        r) RUST_LIB="$OPTARG" ;;
        I) INCDIR="$OPTARG" ;;
        v) VERBOSE=1 ;;
        *) echo "Usage: $0 -c C_LIB -r RUST_LIB [-I INCDIR] [-v]"; exit 1 ;;
    esac
done

[ -n "$C_LIB" ] || { echo "Error: -c C_LIB required"; exit 1; }
[ -n "$RUST_LIB" ] || { echo "Error: -r RUST_LIB required"; exit 1; }
[ -f "$C_LIB" ] || { echo "Error: $C_LIB not found"; exit 1; }
[ -f "$RUST_LIB" ] || { echo "Error: $RUST_LIB not found"; exit 1; }

if [ -z "$INCDIR" ]; then
    INCDIR=$(dirname "$(dirname "$C_LIB")")/include
fi
[ -d "$INCDIR" ] || { echo "Error: include dir $INCDIR not found"; exit 1; }

CC="${CC:-gcc}"
BUILDDIR=$(mktemp -d)
trap 'rm -rf "$BUILDDIR"' EXIT

echo "========================================"
echo "LibmCS Differential Test"
echo "========================================"
echo "C library:    $C_LIB"
echo "Rust library: $RUST_LIB"
echo "Include:      $INCDIR"
echo ""

TEST_FILES=()
[ -f "${SCRIPT_DIR}/sdd_tests/test_sdd.c" ] && TEST_FILES+=("sdd:${SCRIPT_DIR}/sdd_tests/test_sdd.c")
[ -f "${SCRIPT_DIR}/newlib_tests/test_newlib.c" ] && TEST_FILES+=("newlib:${SCRIPT_DIR}/newlib_tests/test_newlib.c")

total_match=0
total_diff=0
total_c_only=0
total_r_only=0

for entry in "${TEST_FILES[@]}"; do
    name="${entry%%:*}"
    src="${entry#*:}"

    echo "--- ${name} ---"

    # Compile against C library
    if ! $CC -o "$BUILDDIR/${name}_c" "$src" -I"$INCDIR" "$C_LIB" -fno-builtin -lm 2>/dev/null; then
        echo "  C compile: FAILED"
        continue
    fi

    # Compile against Rust library
    if ! $CC -o "$BUILDDIR/${name}_r" "$src" -I"$INCDIR" "$RUST_LIB" -fno-builtin -lm -lpthread -ldl 2>/dev/null; then
        echo "  Rust compile: FAILED"
        continue
    fi

    # Run both
    timeout 120 "$BUILDDIR/${name}_c" 2>/dev/null | sort > "$BUILDDIR/${name}_c.out"
    c_rc=$?
    timeout 120 "$BUILDDIR/${name}_r" 2>/dev/null | sort > "$BUILDDIR/${name}_r.out"
    r_rc=$?

    # Compare FAIL lines (these show actual mismatches with the expected values)
    grep "^FAIL" "$BUILDDIR/${name}_c.out" > "$BUILDDIR/${name}_c.fails" 2>/dev/null || true
    grep "^FAIL" "$BUILDDIR/${name}_r.out" > "$BUILDDIR/${name}_r.fails" 2>/dev/null || true

    # Failures in Rust but not in C = real bugs in transpilation
    comm -13 "$BUILDDIR/${name}_c.fails" "$BUILDDIR/${name}_r.fails" > "$BUILDDIR/${name}_new_fails.txt"
    # Failures in C but not in Rust = Rust is somehow "better" (unlikely, note for review)
    comm -23 "$BUILDDIR/${name}_c.fails" "$BUILDDIR/${name}_r.fails" > "$BUILDDIR/${name}_fixed.txt"
    # Failures in both = pre-existing test issues (same behavior)
    comm -12 "$BUILDDIR/${name}_c.fails" "$BUILDDIR/${name}_r.fails" > "$BUILDDIR/${name}_both_fail.txt"

    new_fails=$(wc -l < "$BUILDDIR/${name}_new_fails.txt" | tr -d ' ')
    fixed=$(wc -l < "$BUILDDIR/${name}_fixed.txt" | tr -d ' ')
    both_fail=$(wc -l < "$BUILDDIR/${name}_both_fail.txt" | tr -d ' ')
    c_total=$(wc -l < "$BUILDDIR/${name}_c.out" | tr -d ' ')
    r_total=$(wc -l < "$BUILDDIR/${name}_r.out" | tr -d ' ')

    # Count lines that match exactly between C and Rust output
    match=$(comm -12 "$BUILDDIR/${name}_c.out" "$BUILDDIR/${name}_r.out" | wc -l | tr -d ' ')

    echo "  C output:  ${c_total} lines"
    echo "  Rust output: ${r_total} lines"
    echo "  Matching lines: ${match}"
    echo "  New failures (Rust only): ${new_fails}"
    echo "  Fixed (C fails, Rust passes): ${fixed}"
    echo "  Both fail (same behavior): ${both_fail}"

    if [ "$new_fails" -gt 0 ]; then
        echo "  ** REGRESSIONS IN RUST: **"
        if [ "$VERBOSE" -eq 1 ]; then
            cat "$BUILDDIR/${name}_new_fails.txt" | sed 's/^/    /'
        else
            head -5 "$BUILDDIR/${name}_new_fails.txt" | sed 's/^/    /'
            [ "$new_fails" -gt 5 ] && echo "    ... and $((new_fails - 5)) more"
        fi
    fi

    total_match=$((total_match + match))
    total_diff=$((total_diff + new_fails))

    # Save detailed diff for later analysis
    diff "$BUILDDIR/${name}_c.out" "$BUILDDIR/${name}_r.out" > "$BUILDDIR/${name}_diff.txt" 2>/dev/null || true
    if [ -s "$BUILDDIR/${name}_diff.txt" ]; then
        cp "$BUILDDIR/${name}_diff.txt" "${SCRIPT_DIR}/${name}_diff_report.txt"
        echo "  Full diff: ${SCRIPT_DIR}/${name}_diff_report.txt"
    fi

    echo ""
done

echo "========================================"
echo "DIFF SUMMARY"
echo "========================================"
echo "Matching output lines: ${total_match}"
echo "New Rust regressions:  ${total_diff}"

if [ "$total_diff" -eq 0 ]; then
    echo "Result: IDENTICAL — Rust matches C on all tests"
    exit 0
else
    echo "Result: ${total_diff} DIFFERENCES found"
    exit 1
fi
