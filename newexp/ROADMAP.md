# Experiment Roadmap

## What this experiment does

Transpiles libmcs (C math library, ~190 source files) to Rust, then compares
4 test generation strategies for finding and fixing transpilation bugs:

| Scenario | Description | Testgen method |
|----------|-------------|----------------|
| S1 | Naive one-shot | "generate tests" — no guidance |
| S2 | Explicit one-shot | All functions listed, internals via bridge wrappers |
| S3 | Multi-round + function coverage | Coverage feedback loop, up to 5 rounds |
| S4 | Multi-round + function + branch coverage | LLVM branch coverage feedback, up to 5 rounds |

Plus a **baseline** (raw transpiled Rust, no fixes) judged for comparison.

## API key

Both `claude` and `codex` CLIs read from the environment:

```bash
export ANTHROPIC_API_KEY="sk-ant-api03-YOUR_KEY_HERE"
```

Set this before running any script. `common.sh` validates it.

## Scripts

```
newexp/
├── common.sh           # Shared helpers, constants, env check (sourced by all)
├── run_experiment.sh   # Runs all 5 phases in order
├── 01_transpile.sh     # Phase 0: shared C→Rust transpilation
├── 02_testgen.sh       # Phase 1: test generation (all 4 scenarios)
├── 03_diffgen.sh       # Phase 2: generate differential tests
├── 04_difffix.sh       # Phase 3: diff-test-fix loop
├── 05_judge.sh         # Phase 4: judger evaluation
├── run_difftest.sh     # Separate-binary differential test runner
├── judger_wrapper.sh   # Bridges judger_v2 to harness contract
├── specialize.md       # Libmcs context injected into prompts
├── prompts/
│   ├── transpile.md    # C→Rust (used by 01)
│   ├── s1_testgen.md   # S1 naive testgen (used by 02)
│   ├── s2_testgen.md   # S2 explicit testgen (used by 02)
│   ├── testgen.md      # S3/S4 coverage-guided testgen (used by 02)
│   ├── strategy.md     # S3/S4 coverage gap analysis (used by 02)
│   ├── difftest.md     # Differential test generation (used by 03)
│   ├── analyze.md      # Failure analysis → fix goals (used by 04)
│   └── fixer.md        # Surgical Rust fixes (used by 04)
├── scenarios/
│   ├── s1_naive/config_overrides.sh
│   ├── s2_explicit/config_overrides.sh
│   ├── s3_function/config_overrides.sh
│   └── s4_branch/config_overrides.sh
└── results/            # Judger reports (created at runtime)
```

## Running

### Full experiment

```bash
export ANTHROPIC_API_KEY="sk-ant-..."
cd /home/leochanj/Desktop/libmcs/newexp
./run_experiment.sh -v
```

### Phase by phase

```bash
./01_transpile.sh -v                      # Shared C→Rust
./02_testgen.sh -v                        # All 4 scenarios
./03_diffgen.sh -v                        # Derive diff tests
./04_difffix.sh -v                        # Fix loops
./05_judge.sh -v                          # Final evaluation
```

### Single scenario

Every phase script (except 01) accepts `--scenario`:

```bash
./02_testgen.sh -v --scenario s3          # Only S3 testgen
./04_difffix.sh -v --scenario s1          # Only S1 fix loop
./run_experiment.sh -v --scenario s2      # Full pipeline, S2 only
```

## What each phase does

### 01_transpile.sh

- Reads all ~190 C source files from libm/
- Calls codex with `prompts/transpile.md`
- Produces `rust-baseline/` (Cargo.toml + src/)
- Skips if `rust-baseline/Cargo.toml` exists

### 02_testgen.sh

- **S1**: One codex call with `prompts/s1_testgen.md` → `work-s1/testgen/test_suite.c`
- **S2**: One codex call with `prompts/s2_testgen.md` → `work-s2/testgen/test_suite.c`
- **S3**: Harness loop (extract functions → check coverage → strategy → generate → repeat up to 5 rounds)
  - Uses `prompts/testgen.md` + `prompts/strategy.md`
- **S4**: Same loop with LLVM branch coverage feedback added
- Skips if `test_suite.c` already exists for that scenario

### 03_diffgen.sh

- Copies `rust-baseline/` → `rust-s{1,2,3,4}/`
- For each: generates `difftest_suite.c` that calls both C and Rust, compares bitwise
- Includes compile-fix loop if generated code has errors
- Uses `prompts/difftest.md`

### 04_difffix.sh

- For each scenario: runs iterative fix loop via the progress harness
  1. Run diff tests → collect failures
  2. Analyze failures → goal files (claude, `prompts/analyze.md`)
  3. Fix Rust per goal (codex, `prompts/fixer.md`)
  4. Re-test → check progress
  5. Repeat until pass or stall
- Modifies `rust-s{N}/` in place (checkpoints for rollback)

### 05_judge.sh

- Runs `judger_v2` on all 5 Rust codebases (baseline + s1-s4)
- ~16M test cases: glibc vectors + core-math worst cases
- Bitwise comparison, zero tolerance
- Prints summary table

## Output (at runtime)

```
newexp/
├── rust-baseline/              # Raw transpilation (never modified)
├── rust-s1/ .. rust-s4/        # Fixed by each scenario's diff loop
├── work-transpile/             # Transpilation logs
├── work-s1/ .. work-s4/        # Per-scenario artifacts
│   ├── testgen/                #   test_suite.c, logs
│   ├── diffgen/                #   difftest_suite.c, logs
│   ├── difffix/                #   rounds/, checkpoints/, fix_journal.md
│   └── prompts/                #   Expanded prompts (RUST_DIR filled in)
└── results/
    ├── judger_baseline.txt
    └── judger_s{1,2,3,4}.txt
```

## Prompts

All prompts are in `prompts/`. **Review them before running** — they are the
independent variable of the experiment. Prompts containing `__RUST_DIR__` are
expanded per-scenario at runtime by `common.sh:expand_prompt()`.

| File | Phase | AI tool | Purpose |
|------|-------|---------|---------|
| `transpile.md` | 01 | codex | C→Rust transpilation |
| `s1_testgen.md` | 02 (S1) | codex | Naive: "generate tests" |
| `s2_testgen.md` | 02 (S2) | codex | Explicit: all functions + internals + bridges |
| `testgen.md` | 02 (S3/S4) | codex | Coverage-guided test generation |
| `strategy.md` | 02 (S3/S4) | claude | Coverage gap analysis |
| `difftest.md` | 03 | codex | Generate C-vs-Rust differential tests |
| `analyze.md` | 04 | claude | Analyze failures → fix goals |
| `fixer.md` | 04 | codex | Surgical Rust fixes |

## Prerequisites

```
clang-21          # C compiler (LLVM coverage instrumentation)
cargo             # Rust toolchain
claude            # Claude CLI (~/.local/bin/claude)
codex             # Codex CLI (npm)
jq                # JSON processor
```

## Troubleshooting

**Check logs**: Each AI call writes to `*_output` in the work directory.

**Re-run a phase**: Delete the artifact it checks:
- 01: `rm -rf rust-baseline/`
- 02: `rm work-sN/testgen/test_suite.c`
- 03: `rm work-sN/diffgen/difftest_suite.c`
- 04: `rm work-sN/difffix/.transpile_done` + step markers

**Rate limits**: Harness wraps claude/codex with 5-min retry, 4-hr max.
Adjust: `export CLAUDE_RETRY_INTERVAL=300 CLAUDE_MAX_WAIT=14400`

**Judger setup**: First run clones glibc + generates test files automatically.
