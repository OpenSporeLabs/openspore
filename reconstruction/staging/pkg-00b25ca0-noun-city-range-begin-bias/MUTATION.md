# Mutation campaign — FUN_00b25ca0 @ 0x00b25ca0

15 perturbations, every one rejected. Nine died on a runtime assertion in
`noun_city_range_00b25ca0_model_test.cpp`; six never built, because a
`static_assert` in the header refuses the mutated bytes. Both counts are kills.
Nothing survived.

Build for every mutation: `g++ -m32 -std=c++17 -O1` over the three sources plus
the assembly trampoline.

| # | perturbation | rejected by | kind |
|---|---|---|---|
| M1 | swap the first and fourth argument constants | group 1 (`args[0] != kArg2ClearCallback` and the per-slot equality checks) | runtime |
| M2 | put the wrong constant in argument slot 4 | group 1 (`args[4] == kArg5KeyOperand`) | runtime |
| M3 | transpose the whole argument list (order reversed) | group 1 (per-slot equality checks) | runtime |
| M4 | no bias — return the callee pointer as-is | group 5 (`== raw` is excluded; `== &vector->begin` fails) | runtime |
| M5 | bias of 8 — the `end` member instead of `begin` | group 5 (`!= raw + 8`) | runtime |
| M6 | receiver not forwarded (`nullptr` passed on) | group 3 (`receiver == &g_receiver`) | runtime |
| M7 | invented `if (receiver == nullptr) return nullptr;` | group 7 (`g_callee.called` after a null-receiver call) | runtime |
| M8 | dereference through the bias instead of stopping on it | group 6 (the pair no longer reads as `{begin,end}`) | runtime |
| M15 | bias off by one (4 → 3) | group 5 (`== &vector->begin`, `!= raw + 2`) | runtime |
| M9 | bias 4 → 8 in the header constant **and** the encoding byte | `static_assert(kBeginFieldBias == offsetof(NounRange, end))`, `kBeginFieldBias == 4u` | static_assert |
| M10 | encoding's imm8 changed, constant untouched | `static_assert(kTargetEncoding[32] == kBeginFieldBias)` | static_assert |
| M11 | one push constant off by a single hex digit | the five `read_imm32(...) == kArgN...` static_asserts | static_assert |
| M12 | bare `RET` (0xc3) → `RET imm16` (0xc2 0x04) | `static_assert(kTargetEncoding[33] == 0xc3u && != 0xc2u)` | static_assert |
| M13 | `PUSH imm32` (0x68) → memory form (0x35) on the first push | `static_assert(kTargetEncoding[0] != 0x35u)` and the five `== 0x68u` | static_assert |
| M14 | `CALL` rel32 retargeted by +0x100 | `static_assert` on the signed rel32 and its resolved target | static_assert |

## Two gaps this campaign found, and what closed them

**An invented null guard survived the first run (M7).** The suite checked that a
null *callee result* was published unfiltered, but no test ever called with a
null *receiver*, so adding a `receiver == nullptr` early return was invisible.
Group 7 now calls with a null receiver and asserts the callee was **still**
invoked — which is what the machine does, since the body has no branch.

**A mutated encoding byte survived the first run (M9).** The encoding array was
only ever compared against the header constants by `static_assert`, so a
byte-array edit that was *consistent* with the constants could not be caught by
anything that ran. Group 8 now decodes the bytes again at runtime and compares
them to the values the entry actually hands the callee
(`read_imm32(1) == g_callee.args[4]`, `read_imm32(21) == g_callee.args[0]`).

## Two toolchain faults found while building this, recorded because both pointed at the reconstruction

Both were faults in the *test*, not in the reconstruction, and both produced a
segfault whose backtrace named the code under test — the most expensive kind of
false signal.

1. **The inline-asm ESP measurement passed while measuring nothing.** Naming
   only `eax`/`ecx` as clobbered let GCC allocate a sample register to `ebx`,
   which the call then overwrote. The trampolines moved to assembly
   (`noun_city_range_00b25ca0_trampoline.s`), which removes register allocation
   from the question. The stack offsets there were then **measured** with a
   probe rather than reasoned: reading `8(%esp)` as the call target instead of
   the receiver loads the *receiver* into `ebx` and jumps into the test fixture.

2. **clang widened the recording stub's five stack arguments into one `movaps`.**
   `movaps` faults unless ESP is 16-byte aligned, and the trampoline does not
   guarantee that, so the stub crashed inside itself at `-O1`/`-O2` while GCC
   was clean at every level. Fixed with `volatile` copies of the arguments,
   which forbids the widening. Plain non-`volatile` copies did **not** help.

Both are why the package builds and passes on `g++` and `clang++` at `-O0`
through `-O3`, which is the check that caught them.
