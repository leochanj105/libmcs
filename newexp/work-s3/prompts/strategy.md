You are analyzing coverage gaps in a C library's test suite.

Source code is in /home/leochanj/Desktop/libmcs/libm/.
Read the following files:
- uncovered.md                    — conditions still not covered
- rounds/current/newly_covered.md — conditions newly covered last round (context)
- test_suite.c                    — current test file (find highest test ID)
- unreachable.md                  — conditions already identified as unreachable (skip these)

Part 1 — Analysis:
For each uncovered condition:
1. Which source file and function contains it
2. Is the function `static`? (check the definition in the C source)
3. Is it reachable? If provably unreachable, state why and skip it
4. What function call(s) or input pattern reaches it

## Static functions

For each static function with uncovered branches, flag it for bridging:
   BRIDGE NEEDED: <source_file.c> → <static_function_name>

If a static function has NO caller anywhere in the codebase (dead code), append it
to unreachable.md with: "static, dead code".

Part 2 — Test planning:
Assign unique test IDs continuing from the highest existing ID in test_suite.c.

Output two files:

1. rounds/current/strategy.md — for each reachable condition:
   - Location (file, line)
   - Recommended function(s) to call
   - Input setup needed
   - Assigned test ID

2. unreachable.md — append newly identified unreachable conditions (do NOT rewrite,
   only append).
