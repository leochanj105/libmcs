# func_cov Experiment Results

## Function Coverage
- **259/259 libmcs functions tested** (100% function coverage)
- Test suite: 584 lines, 272 test cases across all libmcs public + internal functions

## Judger (Bitwise Differential Test) Results
- **15,713 total test cases** (364 sdd + 15,349 newlib)
- **414 bitwise divergences** (C != Rust, zero-tolerance %%a comparison)
- **97.4% bitwise match rate** (15,299 / 15,713)

### Divergences by test suite
- **sdd**: 10 divergences / 364 cases (97.3% match)
  - atanf(2), y1(1), y0(1), sqrtf(1), sqrt(1), pow(1), j1(1), atanhf(1), atanh(1)
- **newlib**: 404 divergences / 15,349 cases (97.4% match)
  - j0(99), tanh(77), j1(47), y0(36), tanf(31), erfcf(18), asinf(14), sinf(13), cosf(13), erff(12), erf(11), cosh(8), atan2f(8), erfc(6), log(3), acosf(3), coshf(2), y1(1), hypotf(1), cos(1)

### Difffix loop self-test (AI-generated tests)
- 267 passed, 5 failed out of 272 (98.2%)
- 5 unfixed 1-ULP precision bugs: cacos, casin, casinh, clog, __rem_pio2f

## Timeline
- Testgen: 6 rounds (stalled at round 6, coverage detection was broken for rounds 2-5)
- Difffix: 6 rounds (fixed 3 bugs in rounds 1-2, stalled on final 5)
- Judger report generated: 2026-04-05 23:16
