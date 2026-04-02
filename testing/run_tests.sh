#!/usr/bin/env bash
set -uo pipefail

# run_tests.sh — run all gathered tests against a static library.
#
# Usage: run_tests.sh [-l LIBPATH] [-I INCDIR] [-v]
#   -l LIBPATH   path to libm.a (default: ../build-x86_64-linux-gnu/bin/libm.a)
#   -I INCDIR    path to include dir (default: ../build-x86_64-linux-gnu/include)
#   -v           verbose (show individual failures)

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LIBMCS_DIR="$(dirname "$SCRIPT_DIR")"

LIBPATH=""
INCDIR=""
VERBOSE=0

while getopts "l:I:v" opt; do
    case $opt in
        l) LIBPATH="$OPTARG" ;;
        I) INCDIR="$OPTARG" ;;
        v) VERBOSE=1 ;;
        *) echo "Usage: $0 [-l libm.a] [-I includedir] [-v]"; exit 1 ;;
    esac
done

# Auto-detect from default build
if [ -z "$LIBPATH" ]; then
    LIBPATH=$(find "$LIBMCS_DIR" -name "libm.a" -path "*/bin/*" 2>/dev/null | head -1)
    [ -n "$LIBPATH" ] || { echo "Error: libm.a not found. Build first or pass -l."; exit 1; }
fi

if [ -z "$INCDIR" ]; then
    INCDIR=$(dirname "$(dirname "$LIBPATH")")/include
fi

[ -f "$LIBPATH" ] || { echo "Error: $LIBPATH not found"; exit 1; }
[ -d "$INCDIR" ] || { echo "Error: $INCDIR not found"; exit 1; }

CC="${CC:-gcc}"
BUILDDIR=$(mktemp -d)
trap 'rm -rf "$BUILDDIR"' EXIT

echo "========================================"
echo "LibmCS Test Runner"
echo "========================================"
echo "Library: $LIBPATH"
echo "Include: $INCDIR"
echo ""

total_pass=0
total_fail=0
total_tests=0

# ── SDD Special Case Tests ────────────────────────────────────────────
SDD_TEST="${SCRIPT_DIR}/sdd_tests/test_sdd.c"
if [ -f "$SDD_TEST" ]; then
    echo "--- SDD Special Case Tests ---"
    if $CC -o "$BUILDDIR/test_sdd" "$SDD_TEST" -I"$INCDIR" "$LIBPATH" -fno-builtin -lm 2>/dev/null; then
        output=$("$BUILDDIR/test_sdd" 2>&1)
        summary=$(echo "$output" | grep "^SDD Special Case Tests:")
        p=$(echo "$summary" | grep -oP '\d+ passed' | grep -oP '\d+')
        f=$(echo "$summary" | grep -oP '\d+ failed' | grep -oP '\d+')
        t=$(echo "$summary" | grep -oP 'out of \d+' | grep -oP '\d+')
        echo "  $summary"
        [ "$VERBOSE" -eq 1 ] && echo "$output" | grep "^FAIL" | sed 's/^/    /'
        total_pass=$((total_pass + p))
        total_fail=$((total_fail + f))
        total_tests=$((total_tests + t))
    else
        echo "  COMPILE ERROR"
    fi
    echo ""
fi

# ── Newlib Vector Tests ───────────────────────────────────────────────
NEWLIB_TEST="${SCRIPT_DIR}/newlib_tests/test_newlib.c"
if [ -f "$NEWLIB_TEST" ]; then
    echo "--- Newlib Vector Tests ---"
    if $CC -o "$BUILDDIR/test_newlib" "$NEWLIB_TEST" -I"$INCDIR" "$LIBPATH" -fno-builtin -lm 2>/dev/null; then
        output=$(timeout 120 "$BUILDDIR/test_newlib" 2>&1)
        summary=$(echo "$output" | grep "^Newlib:")
        p=$(echo "$summary" | grep -oP '\d+ passed' | grep -oP '\d+')
        f=$(echo "$summary" | grep -oP '\d+ failed' | grep -oP '\d+')
        t=$(echo "$summary" | grep -oP 'out of \d+' | grep -oP '\d+')
        echo "  $summary"
        [ "$VERBOSE" -eq 1 ] && echo "$output" | grep "^FAIL" | sed 's/^/    /'
        total_pass=$((total_pass + p))
        total_fail=$((total_fail + f))
        total_tests=$((total_tests + t))
    else
        echo "  COMPILE ERROR"
    fi
    echo ""
fi

# ── Summary ──────────────────────────────────────────────────────────
echo "========================================"
echo "TOTAL: ${total_pass} passed, ${total_fail} failed out of ${total_tests}"
echo "========================================"

exit $( [ "$total_fail" -eq 0 ] && echo 0 || echo 1 )
