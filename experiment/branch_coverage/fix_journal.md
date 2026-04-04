# Diff-Fix Loop Journal

## Round 1 — 2026-04-04 00:41

- Tests: ? passed / 11 failed (? configs compile err, ? configs runtime err)
- Goals attempted: 1
- Tests newly fixed: 1
- **REGRESSIONS: 11**
    - default|FAIL C: T057.3: exp2(-INFINITY) = 0x0p+0 | Rust: T057.3: exp2(-INFINITY) = -inf
    - default|FAIL C: T057.4: exp2(1100.0) = inf | Rust: T057.4: exp2(1100.0) = 0x1.13p+10
    - default|FAIL C: T057.5: exp2(-1100.0) = 0x0p+0 | Rust: T057.5: exp2(-1100.0) = -0x1.13p+10
    - default|FAIL C: T057.6: exp2(0.0) = 0x1p+0 | Rust: T057.6: exp2(0.0) = 0x0p+0
    - default|FAIL C: T057.7: exp2(1.0) = 0x1p+1 | Rust: T057.7: exp2(1.0) = 0x1p+0
    - default|FAIL C: T057.8: exp2(-1.0) = 0x1p-1 | Rust: T057.8: exp2(-1.0) = -0x1p+0
    - default|FAIL C: T259.3: exp2f(-INFINITY) = 0x0p+0 | Rust: T259.3: exp2f(-INFINITY) = -inf
    - default|FAIL C: T259.4: exp2f(200.0f) = inf | Rust: T259.4: exp2f(200.0f) = 0x1.9p+7
    - default|FAIL C: T259.5: exp2f(-200.0f) = 0x0p+0 | Rust: T259.5: exp2f(-200.0f) = -0x1.9p+7
    - default|FAIL C: T259.6: exp2f(0.0f) = 0x1p+0 | Rust: T259.6: exp2f(0.0f) = 0x0p+0
    - ... and 1 more
- Fixed:
    - default|COMPILE_ERROR


## Round 2 — 2026-04-04 00:47

- Tests: ? passed / 0 failed (? configs compile err, ? configs runtime err)
- Goals attempted: 1
- Tests newly fixed: 11
- Fixed:
    - default|FAIL C: T057.3: exp2(-INFINITY) = 0x0p+0 | Rust: T057.3: exp2(-INFINITY) = -inf
    - default|FAIL C: T057.4: exp2(1100.0) = inf | Rust: T057.4: exp2(1100.0) = 0x1.13p+10
    - default|FAIL C: T057.5: exp2(-1100.0) = 0x0p+0 | Rust: T057.5: exp2(-1100.0) = -0x1.13p+10
    - default|FAIL C: T057.6: exp2(0.0) = 0x1p+0 | Rust: T057.6: exp2(0.0) = 0x0p+0
    - default|FAIL C: T057.7: exp2(1.0) = 0x1p+1 | Rust: T057.7: exp2(1.0) = 0x1p+0
    - default|FAIL C: T057.8: exp2(-1.0) = 0x1p-1 | Rust: T057.8: exp2(-1.0) = -0x1p+0
    - default|FAIL C: T259.3: exp2f(-INFINITY) = 0x0p+0 | Rust: T259.3: exp2f(-INFINITY) = -inf
    - default|FAIL C: T259.4: exp2f(200.0f) = inf | Rust: T259.4: exp2f(200.0f) = 0x1.9p+7
    - default|FAIL C: T259.5: exp2f(-200.0f) = 0x0p+0 | Rust: T259.5: exp2f(-200.0f) = -0x1.9p+7
    - default|FAIL C: T259.6: exp2f(0.0f) = 0x1p+0 | Rust: T259.6: exp2f(0.0f) = 0x0p+0
    - default|FAIL C: T259.7: exp2f(1.0f) = 0x1p+1 | Rust: T259.7: exp2f(1.0f) = 0x1p+0

