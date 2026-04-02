# LibmCS Test-Guided Transpilation Plan

## Context

LibmCS is a space-grade IEEE-754 compliant math library (190 C source files, 126+ public functions, ~21K LOC). It has complex bit-level IEEE-754 manipulation via unions/macros, conditional compilation for endianness/denormal handling/architecture, and multiple precision variants (float, double, long double, complex).

Unlike SPHINCS+ (where 3 "always-wrong" bugs were caught by trivial function calls), libmcs bugs will be **input-dependent** — wrong behavior only on specific IEEE-754 special values, boundary conditions, or precision edge cases. Naive function-coverage (one call per function with a simple input) will miss most bugs.

## Available Test Sources

### 1. SDD Special Case Tables (in-repo, extractable)

**Location:** `doc/sdd/5_Software_Design/4_Software_Component_Design_Aspects_Of_Each_Component/*.rst`

106 RST files, each containing a "Special cases" table defining IEEE-754 mandated behavior for edge inputs (NaN, ±Inf, ±0, denormals, overflow boundaries). Example from `pow`:

| x | y | Result |
|---|---|--------|
| -0 | odd negative integer | -Inf |
| +0 | < 0 | +Inf |
| -1 | ±Inf | +1 |
| NaN | ≠ ±0 | qNaN |

**Action:** Write a parser to extract these tables into machine-readable test vectors. These are the minimum correctness requirements — every transpilation must pass these.

**Effort:** Script-only, no LLM needed. ~200-300 test vectors total.

### 2. Newlib Test Suite (public, directly applicable)

**Source:** `sourceware.org/git/newlib-cygwin.git` → `newlib/testsuite/libm-test/`

LibmCS is derived from Newlib's libm. The Newlib test suite tests the same API with the same semantics. It includes:
- Special value tests (NaN, Inf, zero handling)
- Accuracy tests (ULP bounds for standard inputs)
- Boundary tests (near overflow/underflow)

**Action:** Clone Newlib, extract the libm test vectors, adapt the test harness to call libmcs. Most functions have identical signatures.

**Effort:** Medium. Need to adapt the test harness, not the test data.

### 3. core-math Exhaustive Tests (public, for float functions)

**Source:** https://core-math.gitlabpages.inria.fr/ (also referenced in the `origin/core-math` branch)

core-math provides **exhaustive** tests for single-precision functions — it tests all 2^32 possible float inputs and verifies correct rounding. This is the strongest possible test oracle for `sinf`, `cosf`, `expf`, `logf`, etc.

The `origin/core-math` branch in this repo already integrates with core-math.

**Action:** Use the core-math branch as a starting point. Build core-math's test infrastructure against the transpiled Rust library.

**Effort:** Low-medium. The integration already exists in the branch.

### 4. glibc libm-test Vectors (public, for double functions)

**Source:** glibc `math/libm-test-*.inc` files

GNU C library maintains thousands of test vectors for all math functions, including:
- Expected results with ULP accuracy bounds
- Special case handling
- Errno/exception flag verification

**Action:** Extract glibc's test vectors (they're in a parseable format) and generate a C test harness that compares libmcs output against expected values.

**Effort:** Medium. The vector format needs parsing.

### 5. MPFR Oracle Testing (for arbitrary precision verification)

**Source:** https://www.mpfr.org/

MPFR provides arbitrary-precision floating-point arithmetic. For any input, MPFR can compute the "true" result to arbitrary precision, which can then be rounded to IEEE-754 double/float for comparison.

**Action:** Generate random + boundary inputs, compute expected results via MPFR, compare against transpiled Rust output. This catches precision bugs that fixed test vectors might miss.

**Effort:** Requires writing a test generator. Best used as a supplement to sources 1-4.

### 6. Private Qualification Kit (not accessible)

GTD GmbH's proprietary test suite achieves 99.8% statement / 99.3% branch coverage. Available only through ESA ESSR (European Space Software Repository) or by contacting libmcs@gtd-gmbh.de.

Not usable for our purposes, but establishes the coverage bar we should aim for.

## Why Naive Function-Coverage Fails Here

Each math function has 5-20 internal branches for different input ranges. Examples:

- `exp(x)`: separate paths for x near 0, x large positive, x large negative, x near ln(2), x = ±Inf, x = NaN
- `pow(x,y)`: 22 special cases in the SDD alone, plus different polynomial approximations for different ranges
- `sin(x)`: range reduction to [-π/4, π/4], then polynomial; different code for |x| < 2^-27, |x| > 2^19π

A transpilation error in the range reduction (e.g., wrong constant in the bit manipulation for `EXTRACT_WORDS`) would only manifest for inputs that reach that specific code path. Testing `sin(1.0)` exercises one path; you need `sin(1e-30)`, `sin(1e15)`, `sin(NaN)`, `sin(nextafter(π/4, ∞))` to cover the others.

## Recommended Execution Order

### Phase 1: Extract SDD special case tests (no LLM needed)
- Parse RST tables → JSON test vectors
- Generate C test harness that calls each function with special case inputs
- Run against original C library to establish ground truth
- **This gives us ~300 targeted edge-case tests**

### Phase 2: Integrate Newlib test suite
- Clone Newlib, extract libm-test vectors
- Adapt harness for libmcs API
- **This gives us ~2000+ tests with accuracy bounds**

### Phase 3: Transpile and diff-test
- Transpile libmcs to Rust (function by function, 190 files)
- Add `_rs` wrappers for each function
- Run Phase 1 + Phase 2 tests as diff tests (C vs Rust)
- Use the diff-fix loop to fix failures

### Phase 4: core-math exhaustive (float functions)
- Build core-math test infrastructure against the Rust library
- Run exhaustive 2^32 tests for each float function
- **This gives definitive correctness proof for all float functions**

### Phase 5: MPFR random + boundary testing (double functions)
- Generate random inputs + IEEE-754 boundary values
- Compute expected results via MPFR
- Compare against transpiled Rust
- Focus on functions not covered by Newlib tests

### Phase 6: Coverage-guided refinement (if needed)
- Use LLVM branch coverage to find untested code paths
- Generate targeted inputs for uncovered branches
- **Only needed if Phases 1-5 leave gaps**

## Configuration Matrix

LibmCS has ~96 build configurations (precision × complex × denormal × endianness × arch). For transpilation testing, prioritize:

1. **x86-64, little-endian, standard denormals, double+float** — the most common config
2. **x86-64, little-endian, DAZ mode** — tests the denormal handling paths
3. **big-endian** — if targeting SPARC/similar, tests the endianness-dependent union layouts

Complex number support and long double can be deferred — they're separate translation units.
