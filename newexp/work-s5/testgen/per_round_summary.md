# S5 Per-Round Coverage Summary

Total branches (conditions): 2522
S4 baseline: 524 test prints, 2026 lines

## Coverage Progression

| Round | Uncovered Branches | Covered | Coverage % | Test Prints | Lines | New Tests |
|-------|-------------------|---------|-----------|-------------|-------|-----------|
| S4 base | — | — | — | 524 | 2026 | — |
| 1 | 1589 | 933 | 37.0% | 1537 | 3981 | +1013 |
| 2 | 795 | 1727 | 68.5% | 2122 | 5183 | +585 |
| 3 | 584 | 1938 | 76.8% | 2633 | 6134 | +511 |
| 4 | 470 | 2052 | 81.4% | 3295 | 7621 | +649 (new: __tan, __tanf) |
| 5 | 397 | 2125 | 84.3% | 3875 | 8718 | +580 |

## Per-Round Test Generation Details

### Round 1 (+1013 tests)
Top functions by new tests added:
- pow: 3 → 39 (+36)
- atan2f: 2 → 34 (+32)
- atan2l: 1 → 28 (+27)
- powf: 2 → 18 (+16)
- ceil: 3 → 19 (+16)
- exp2: 3 → 18 (+15)
- atanf: 2 → 16 (+14)
- atan2: 4 → 18 (+14)
- nextafter: 3 → 16 (+13)
- __lgamma: 3 → 16 (+13)
- floor: 3 → 16 (+13)
- erfc: 3 → 16 (+13)
- erf: 3 → 16 (+13)
- log1pf: 2 → 14 (+12)
- expm1f: 2 → 14 (+12)

### Round 2 (+585 tests)
Top functions by new tests added:
- __lgammaf: 2 → 43 (+41)
- __lgamma: 3 → 44 (+41)
- atan2: 34 → 54 (+20)
- __sinf: 2 → 21 (+19)
- atan2f: 28 → 46 (+18)
- pow: 39 → 55 (+16)
- tan: 12 → 26 (+14)
- floor: 16 → 30 (+14)
- ceil: 19 → 33 (+14)
- powf: 18 → 31 (+13)
- log2: 10 → 22 (+12)
- log1pl: 1 → 13 (+12)
- jn: 12 → 24 (+12)
- trunc: 12 → 23 (+11)
- yn: 11 → 21 (+10)

### Round 3 (+511 tests, new functions: ctans, ctansf)
Top functions by new tests added:
- powl: 1 → 77 (+76)
- llrint: 13 → 64 (+51)
- floorl: 1 → 44 (+43)
- __redupi: 3 → 43 (+40)
- nextafterl: 1 → 34 (+33)
- rintl: 1 → 33 (+32)
- fmodl: 1 → 33 (+32)
- truncl: 1 → 32 (+31)
- ldexpf: 7 → 36 (+29)
- erfcl: 1 → 30 (+29)
- roundl: 1 → 29 (+28)
- expm1l: 1 → 28 (+27)
- modfl: 1 → 26 (+25)
- fma: 3 → 28 (+25)
- sqrtl: 1 → 25 (+24)

### Round 4 (+649 tests, new functions: __tan, __tanf)
Top functions by new tests added:
- truncl: 1 → 44 (+43)
- lgammaf: 64 → 94 (+30)
- __cos: 3 → 33 (+30)
- powf: 43 → 62 (+19)
- pow: 77 → 95 (+18)
- jn: 36 → 54 (+18)
- ceil: 49 → 67 (+18)
- tanl: 1 → 18 (+17)
- tanhl: 1 → 18 (+17)
- fmod: 33 → 47 (+14)
- tgammal: 1 → 14 (+13)
- fmodf: 24 → 37 (+13)
- tanh: 18 → 30 (+12)
- nextafter: 34 → 46 (+12)
- y0: 22 → 33 (+11)

### Round 5 (+580 tests)
Top functions by new tests added:
- lgammaf: 94 → 125 (+31)
- log2l: 1 → 30 (+29)
- pow: 95 → 121 (+26)
- ceil: 67 → 93 (+26)
- lgamma: 71 → 89 (+18)
- floor: 52 → 69 (+17)
- round: 39 → 54 (+15)
- expm1: 38 → 53 (+15)
- nextafter: 46 → 60 (+14)
- ceilf: 43 → 57 (+14)
- trunc: 44 → 57 (+13)
- modf: 32 → 44 (+12)
- atan2: 65 → 77 (+12)
- truncf: 33 → 44 (+11)
- fmod: 47 → 58 (+11)
