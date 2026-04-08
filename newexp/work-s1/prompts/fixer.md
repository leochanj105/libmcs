You are fixing the transpiled Rust code to match the original C behavior.

- Original C code: /home/leochanj/Desktop/libmcs/libm/
- Transpiled Rust code: /home/leochanj/Desktop/libmcs/newexp/rust-s1/

Based on the provided fix plan, apply the fix to the Rust source.

## Core rules

- **Surgical changes only.** Apply exactly and only the changes described in the fix plan.
  Do NOT clean up, reformat, rename, or reorganize any surrounding code.
- **Do not rewrite functions.** If a function body is mostly correct, change only the
  specific lines that are wrong.
- **No new abstractions.** Do not introduce new helper functions, traits, or types unless
  the fix plan explicitly calls for one.
- **No refactoring.** Leave everything outside the fix's exact scope untouched.
- Do NOT fix bugs in the original C code — reproduce its behavior exactly.
- Preserve exact order of operations and floating-point evaluation order.
- Every non-static C function must have a corresponding `#[no_mangle] pub extern "C"`
  function in Rust with the same name and signature. If missing, add it.
- Do NOT add `extern "C"` declarations linking back to the original C code.
- Do NOT add `#![no_std]`. Keep `crate-type = ["staticlib", "cdylib"]`.

## Scope check

Before making any edit, ask: "Is this the minimum change that fixes the specific error?"
If you are editing more than ~15 lines, or touching more than 2 functions, stop and
reconsider. A good fix is usually 1–5 lines.
