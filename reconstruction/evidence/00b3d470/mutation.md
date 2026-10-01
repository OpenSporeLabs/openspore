# Mutation record — model test for 0x00b3d470

- Target: `0x00b3d470` (`FUN_00b3d470`), SporeApp.exe 3.1.0.22
- Binary sha256: `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`
- Package: `reconstruction/staging/pkg-00b3d470-root-slot-dword/`
- Implementer: `w22/0x00b3d470`

## Build line

```
g++ -m32 -std=c++17 -O1 -UNDEBUG -I<package> \
    root_slot_dword_00b3d470.cpp root_slot_dword_00b3d470_model_test.cpp -o <out>
```

`-UNDEBUG` is load-bearing: the test is `assert`-based, and a build with
`-DNDEBUG` would compile every check away and exit 0 for a wrong body.

## Baseline (unmutated)

| build | run |
|---|---|
| rc=0 | rc=0 |

## Mutations

The mutated body was written to a scratch copy; the package under
`reconstruction/staging/` was never modified. M1–M6 patch the single
`return g_0167eb18;` in the `.cpp`; M7 patches the prototype in the `.hpp`.

| id | mutation | build rc | run rc | detector |
|---|---|---:|---:|---|
| M1 | `return g_root_slot_image.guard_lo[kGuardWords - 1];` — reads the low neighbour instead of the slot | 0 | -6 (SIGABRT) | `test_returns_the_slot_word` line 135 |
| M2 | `return static_cast<Word>(static_cast<std::uint16_t>(g_0167eb18));` — truncating return | 0 | -6 (SIGABRT) | `test_returns_the_slot_word` line 135 |
| M3 | value cached into a file-static on first call, then returned — stale cache | 0 | -6 (SIGABRT) | `test_returns_the_slot_word` line 135 |
| M4 | `return static_cast<Word>(reinterpret_cast<std::uint32_t>(&g_root_slot_image.slot));` — address, not contents | 0 | -6 (SIGABRT) | `test_returns_the_slot_word` line 135 |
| M5 | `__asm__ __volatile__("addl $4, %esp")` before the return — callee pops 4 | 0 | -11 (SIGSEGV) | stack corruption from the unbalanced `ret` |
| M6 | `g_0167eb18 = 0u;` before the return — a store, not a load | 0 | -6 (SIGABRT) | `test_returns_the_slot_word` line 135 |
| M7 | prototype widened to `Word f(Word)` in header + `AbiRootSlotDword00b3d470` | 1 | n/a | `error: too few arguments to function` — the compile-time ABI gate |

Every mutation fails; the unmutated build passes. M1–M4 and M6 all trip on
`test_returns_the_slot_word` because that test is first in `main()` and arms the
slot with `0x80000000`, `0xdeadbeef` and `0xffffffff` before anything else runs.
That ordering is intentional: a wrong body is caught before a later check can be
satisfied by one lucky register state.

M5 is detected by a crash rather than by an assertion. The reason is structural:
adding 4 to ESP immediately before the callee's own `ret` unbalances the frame,
so control transfers to a wrong return address before any C++ check can run. It
is still a non-zero exit, and it is still the `test_whole_eax_carries_the_word`
measurement — the `before == after` ESP comparison at line ~196 — that the
mutation invalidates; the process simply dies before reaching it. A body that
popped the stack without also corrupting the return path (for example a
callee-cleanup `ret 4`, which this binary's `c3` contradicts) would be caught by
that assert instead.

## What this does and does not establish

The test establishes that the modelled entry is a zero-parameter function
returning all 32 bits of one dword loaded from the single absolute address
`0x0167eb18`, with zero callee-side stack cleanup and no store to the modelled
image. It establishes nothing about what that dword denotes, who writes it, or
when — the body contains no code that would carry that information.

There is no runtime, Wine, trace or differential evidence for `0x00b3d470` in
this repository. Every claim in the package is static and pinned to the bytes of
this binary.
