#!/usr/bin/env bash
set -euo pipefail

# setup.sh — clone sources and generate test files for judger_v2.
# Run once after cloning the repo.

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# 1. Clone glibc (sparse — only math/)
if [ ! -f glibc_repo/math/auto-libm-test-in ]; then
    echo "Cloning glibc (sparse: math/ only)..."
    rm -rf glibc_repo
    git clone --depth 1 --filter=blob:none --sparse \
        https://sourceware.org/git/glibc.git glibc_repo
    cd glibc_repo && git sparse-checkout set math && cd ..
else
    echo "glibc_repo already exists."
fi

# 2. Check core-math repo (should be at ../../coremath_repo)
COREMATH="$(cd ../coremath_repo 2>/dev/null && pwd)" || true
if [ -z "$COREMATH" ] || [ ! -d "$COREMATH/src/binary64" ]; then
    echo "ERROR: core-math repo not found at ../coremath_repo"
    echo "Clone it: git clone https://gitlab.inria.fr/core-math/core-math.git ../coremath_repo"
    exit 1
fi
echo "core-math repo: $COREMATH"

# 3. Generate test files
echo "Generating GLIBC tests (auto-libm-test-in)..."
python3 scripts/gen_glibc_tests.py

echo "Generating GLIBC tests (libm-test-*.inc)..."
python3 scripts/gen_glibc_inc_tests.py

echo "Generating core-math worst-case tests (per-function files)..."
python3 scripts/gen_wc_tests.py

echo ""
echo "Done. Run tests with:"
echo "  bash run.sh -c C_LIB -r RUST_LIB -I INCDIR"
