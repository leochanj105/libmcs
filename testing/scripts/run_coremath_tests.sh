#!/usr/bin/env bash
set -uo pipefail
set +o pipefail  # nm | grep -q breaks with pipefail (SIGPIPE on large .a files)

# run_coremath_tests.sh — run core-math check_special tests against a static library.
#
# Usage: run_coremath_tests.sh [-l LIBPATH] [-n NUM_TESTS] [-v]
#   -l LIBPATH     path to libm.a (default: auto-detect)
#   -n NUM_TESTS   random tests per function (default: 100000)
#   -v             verbose (show each failure)

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TESTING_DIR="$(dirname "$SCRIPT_DIR")"
LIBMCS_DIR="$(dirname "$TESTING_DIR")"
CM="${TESTING_DIR}/coremath_repo/src"

LIBPATH=""
NUM_TESTS=100000
VERBOSE=0

while getopts "l:n:v" opt; do
    case $opt in
        l) LIBPATH="$OPTARG" ;;
        n) NUM_TESTS="$OPTARG" ;;
        v) VERBOSE=1 ;;
        *) echo "Usage: $0 [-l libm.a] [-n num_tests] [-v]"; exit 1 ;;
    esac
done

if [ -z "$LIBPATH" ]; then
    LIBPATH=$(find "$LIBMCS_DIR" -name "libm.a" -path "*/bin/*" 2>/dev/null | head -1)
    [ -n "$LIBPATH" ] || { echo "Error: libm.a not found"; exit 1; }
fi
[ -f "$LIBPATH" ] || { echo "Error: $LIBPATH not found"; exit 1; }
[ -d "$CM" ] || { echo "Error: coremath_repo not found. Clone it first."; exit 1; }

CC="${CC:-gcc}"
BUILDDIR=$(mktemp -d)
trap 'rm -rf "$BUILDDIR"' EXIT

RESULTS="${TESTING_DIR}/coremath_tests/results.txt"
mkdir -p "${TESTING_DIR}/coremath_tests"

echo "========================================"
echo "Core-Math Tests (MPFR reference)"
echo "========================================"
echo "Library: $LIBPATH"
echo "Tests per function: $NUM_TESTS"
echo ""

total_funcs=0
passed_funcs=0
failed_funcs=0
error_funcs=0

: > "$RESULTS"

# Map from core-math function name to libmcs function name
# Most are identical; skip functions not in libmcs
declare -A FUNC_MAP
# Functions that don't exist in libmcs or have different names
SKIP_FUNCS="acospi asinpi atanpi atan2pi cospi sinpi tanpi compound exp10 exp10m1 exp2m1 log10p1 log2p1 rsqrt sincos"

run_check() {
    local precision="$1"  # binary32 or binary64
    local func="$2"
    local check_src="${CM}/${precision}/${func}/check_special.c"
    local mpfr_src="${CM}/${precision}/${func}/${func}_mpfr.c"
    local support_dir="${CM}/${precision}/support"

    [ -f "$check_src" ] || return 1
    [ -f "$mpfr_src" ] || return 1

    # Determine C function name (e.g., sinf for binary32/sin, sin for binary64/sin)
    local c_func="$func"
    if [ "$precision" = "binary32" ]; then
        c_func="${func}f"
    fi

    # Check if function exists in libmcs
    if ! nm "$LIBPATH" 2>/dev/null | grep -q " T ${c_func}$"; then
        return 1
    fi

    local obj_check="$BUILDDIR/${precision}_${func}_check.o"
    local obj_mpfr="$BUILDDIR/${precision}_${func}_mpfr.o"
    local bin="$BUILDDIR/${precision}_${func}_test"

    # Compile check_special.c
    if ! $CC -O2 -I"$support_dir" \
        -Dcr_${func}=${c_func} \
        -DCORE_MATH_TESTS=${NUM_TESTS} \
        -c "$check_src" -o "$obj_check" 2>/dev/null; then
        return 2
    fi

    # Compile MPFR reference
    if ! $CC -O2 -I"$support_dir" \
        -c "$mpfr_src" -o "$obj_mpfr" 2>/dev/null; then
        return 2
    fi

    # Link
    if ! $CC -o "$bin" "$obj_check" "$obj_mpfr" \
        "$LIBPATH" -lmpfr -lgmp -lm -fno-builtin 2>/dev/null; then
        return 2
    fi

    # Run
    local output
    output=$(timeout 60 "$bin" --rndn 2>&1)
    local rc=$?

    if [ $rc -eq 0 ]; then
        return 0
    else
        echo "$output" > "$BUILDDIR/${precision}_${func}_failures.txt"
        local fail_count=$(echo "$output" | grep -c "^FAIL" || echo 0)
        echo "${precision}/${func} (${c_func}): ${fail_count} failures" >> "$RESULTS"
        if [ "$VERBOSE" -eq 1 ]; then
            echo "$output" | grep "^FAIL" | head -5
        fi
        return 3
    fi
}

# Test binary64 functions
echo "--- Binary64 (double) ---"
for func_dir in "$CM"/binary64/*/; do
    func=$(basename "$func_dir")
    [ "$func" = "support" ] && continue
    echo "$SKIP_FUNCS" | grep -qw "$func" && continue
    [ -f "${func_dir}/check_special.c" ] || continue
    [ -f "${func_dir}/${func}_mpfr.c" ] || continue

    total_funcs=$((total_funcs + 1))
    printf "  %-20s " "$func"

    run_check "binary64" "$func"
    rc=$?
    case $rc in
        0) echo "PASS"; passed_funcs=$((passed_funcs + 1)) ;;
        1) echo "SKIP (not in libmcs)"; total_funcs=$((total_funcs - 1)) ;;
        2) echo "BUILD_ERROR"; error_funcs=$((error_funcs + 1)) ;;
        3) echo "FAIL"; failed_funcs=$((failed_funcs + 1)) ;;
    esac
done

echo ""

# Test binary32 functions
echo "--- Binary32 (float) ---"
for func_dir in "$CM"/binary32/*/; do
    func=$(basename "$func_dir")
    [ "$func" = "support" ] && continue
    echo "$SKIP_FUNCS" | grep -qw "$func" && continue
    [ -f "${func_dir}/check_special.c" ] || continue
    [ -f "${func_dir}/${func}f_mpfr.c" ] || continue

    total_funcs=$((total_funcs + 1))
    printf "  %-20s " "${func}f"

    # For binary32, the mpfr file is named funcf_mpfr.c
    local_mpfr="${func_dir}/${func}f_mpfr.c"
    local_check="${func_dir}/check_special.c"
    c_func="${func}f"

    if ! nm "$LIBPATH" 2>/dev/null | grep -q " T ${c_func}$"; then
        echo "SKIP (not in libmcs)"
        total_funcs=$((total_funcs - 1))
        continue
    fi

    obj_check="$BUILDDIR/b32_${func}_check.o"
    obj_mpfr="$BUILDDIR/b32_${func}_mpfr.o"
    bin="$BUILDDIR/b32_${func}_test"

    if ! $CC -O2 -I"$CM/binary32/support" \
        -Dcr_${func}f=${c_func} \
        -DCORE_MATH_TESTS=${NUM_TESTS} \
        -c "$local_check" -o "$obj_check" 2>/dev/null; then
        echo "BUILD_ERROR"
        error_funcs=$((error_funcs + 1))
        continue
    fi

    if ! $CC -O2 -I"$CM/binary32/support" \
        -c "$local_mpfr" -o "$obj_mpfr" 2>/dev/null; then
        echo "BUILD_ERROR"
        error_funcs=$((error_funcs + 1))
        continue
    fi

    if ! $CC -o "$bin" "$obj_check" "$obj_mpfr" \
        "$LIBPATH" -lmpfr -lgmp -lm -fno-builtin 2>/dev/null; then
        echo "BUILD_ERROR"
        error_funcs=$((error_funcs + 1))
        continue
    fi

    output=$(timeout 60 "$bin" --rndn 2>&1)
    rc=$?
    if [ $rc -eq 0 ]; then
        echo "PASS"
        passed_funcs=$((passed_funcs + 1))
    else
        echo "FAIL"
        failed_funcs=$((failed_funcs + 1))
        fail_count=$(echo "$output" | grep -c "^FAIL" || echo 0)
        echo "binary32/${func}f: ${fail_count} failures" >> "$RESULTS"
        [ "$VERBOSE" -eq 1 ] && echo "$output" | grep "^FAIL" | head -3 | sed 's/^/    /'
    fi
done

echo ""
echo "========================================"
echo "Core-Math: ${passed_funcs} pass, ${failed_funcs} fail, ${error_funcs} build errors (${total_funcs} total)"
echo "========================================"
[ -s "$RESULTS" ] && echo "Failure details: $RESULTS"
