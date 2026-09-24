# Original Executable Replacement Feasibility

## Scope and status

This is a clean-room feasibility synthesis for the original `SporeApp.exe` 3.1.0.22. It uses only repository evidence and static/tooling evidence. No binary was patched, no game was run, and no existing file was changed.

**Decision: technically feasible, not implemented for Spore.** The smallest safe PoC is a read-only preflight/identity validator, followed by a 32-bit ABI-compatible one-float shim and a reversible call-site or entry detour on a disposable process or copy. That PoC must use a dedicated entry, return, and memory oracle. The current Cell target is not ready for an installed replacement because its runtime reachability and field semantics are unresolved.

Evidence is labeled as `CONFIRMED`, `VERIFIED`, `OBSERVED`, `SUPPORTED`, `INFERRED`, `APPROXIMATION`, or `UNKNOWN`. Decompilation is evidence, not truth. The evidence vocabulary and its use are recorded in `docs/RECON-3.1.0.22.md:147-170` and `docs/REPLACEMENT-ABI.md:7-10`.

## Eight questions answered

### 1. What binary and address model is being replaced?

The target is `SPORE/SporeBin/SporeApp.exe`, SporeApp.exe 3.1.0.22, an x86 PE32/i386 Windows executable with image base `0x00400000`. Its engine is statically linked in the executable; it is not a set of replaceable engine DLLs (`docs/RECON-3.1.0.22.md:9-20,72-78`).

The address convention is:

```text
linked VA = image base + PE RVA
RVA       = linked VA - 0x00400000
```

A reported file offset must be computed from the PE section mapping, not by subtracting the image base from every artifact field. The committed Cell probe documentation records a historical address-column inconsistency and the verified mapping (`docs/analysis/CELL-RUNTIME-OBSERVATION.md:21-42`; `tools/re/data/ghidra_snapshot_cell_movement.json:3-5,190`). The target's confirmed linked VA is `0x00E5B790`, true RVA `0x00A5B790`, and file offset `0x00A5AB90` (`docs/REPLACEMENT-ABI.md:13-25`).

### 2. Is replacing a function in the original executable technically feasible?

Yes, technically, but the evidence currently proves only a mechanism in a synthetic native process. `tools/replace/synthetic/` builds a Linux-native, 32-bit, non-PIE target. Its constructor uses `mprotect`, writes a 5-byte `E9 rel32` jump at a verified function entry, reads the bytes back, restores execute permissions, and retains the original bytes (`tools/replace/synthetic/hooker.c:24-70`; `tools/replace/synthetic/README.md:7-30`). The before/after test proves redirected behavior, not Spore compatibility (`tools/replace/synthetic/README.md:32-58`).

The existing implementation has no unhook path, range-checked relocation, page-boundary handling, thread quiescing, or thread-safe synchronization. It is not a Spore installer and has not been used to modify SporeApp.exe. Therefore the current state is `verified_synthetic_only`, not `implemented_for_spore`.

### 3. Which replacement mechanisms are applicable?

| Mechanism | Safe use | Current assessment |
|---|---|---|
| PE import replacement | Only actual PE imports, such as imported OS/library entry points | Applicable in principle to imports, not to statically linked engine internals. No Spore replacement exists. |
| Vtable replacement | Confirmed object dispatch and a proven vtable slot | Candidate in principle. `App::cCellModeStrategy` has a strong static vtable association, but there is no RTTI and no runtime dispatch trace. |
| Call-site patch | One known call instruction/call chain | Smallest scope when the direct call site is proven and the desired behavior is to affect that caller only. The Cell target reports a direct caller at `0x00E8083B`; the call instruction and all alternative callers still need runtime/static reconciliation. |
| Function-pointer replacement | A function pointer with a proven writer, reader, lifetime, and synchronization model | Not safe without those proofs; writer/reader evidence is currently missing. |
| Inline detour | Every caller that enters the function | The synthetic proves the byte-level seam only. Production use still needs relocation/range checks, instruction-boundary validation, page protection, and thread safety. |
| Trampoline | The original must remain callable, or callers must be able to fall through | Not implemented. A correct trampoline must preserve the original ABI and decode any overwritten instructions. |
| Wrapper interception | An architectural facade that exposes replacement behavior to host code | It still needs one concrete attachment mechanism above; a wrapper alone does not intercept the original binary. |

The current `src/replace/Replace.cpp` stand-in has four arguments, while the original target is a one-argument `void(float)` function (`src/replace/Replace.cpp:25-27`; `docs/REPLACEMENT-ABI.md:84-100`). It cannot be jumped to directly. The `src/compat` seams—`ResourceProvider`, `MeshSource`, and the renderer—are real host abstractions, not original-binary ABI replacements (`docs/replacement-boundaries.md:47-60`; `src/compat/ResourceProvider.hpp:19-30`; `src/compat/MeshSource.hpp:22-49`).

### 4. What does the current observation infrastructure prove?

`tools/observatory` is a 32-bit ptrace/INT3 tracer. It discovers modules, plants temporary breakpoints, records function-entry events and registers as JSONL, and detaches with breakpoint restoration (`tools/observatory/README.md:1-7,20-61`). `menu_walk.sh` and `cell_trace.sh` provide screenshot and input-log plumbing, but neither injects replacement code.

The historical nine-run Cell observation is a negative reachability result: the Cell-stage probes fired zero times. One run reached the main menu, where the suspected orientation callee ran as a generic 30 Hz frame-loop function; the Cell stage was never entered (`docs/analysis/CELL-RUNTIME-OBSERVATION.md:44-84`). Xvfb and xdotool were absent, so the menu could not be driven to Cell Stage. Entry-only probes do not capture return values (`docs/analysis/CELL-RUNTIME-OBSERVATION.md:86-96`; `tools/observatory/README.md:167-176`).

The current infrastructure therefore supports observation and identity checking, but not ABI-level return, memory-effect, or replacement validation.

### 5. What is the current Cell target, and what is unresolved?

| Field | Current evidence |
|---|---|
| Symbol | `Simulator::Cell::MovePlayerToMousePosition`; SDK name `CONFIRMED` |
| Linked VA / RVA / file offset | `0x00E5B790` / `0x00A5B790` / `0x00A5AB90` |
| Entry bytes | `a1 04 3c 6b 01`, one complete `mov eax,[absolute]` instruction; `VERIFIED` |
| Prototype | Return `void` and one `float` parameter are confirmed; cdecl is likely/inferred for the one-float frame |
| Direct caller | `0x00E8083B` is reported as a direct caller; complete caller enumeration is not established |
| Static behavior | Lock guard, player lookup, camera ray/movement-plane intersection, target/orientation writes, and moving flag are visible in decompilation; semantics remain evidence, not truth |
| Runtime | No live Cell trace; no positive return-value or side-effect oracle |

The entry bytes encode the absolute global address `0x016B3C04`. Older Cell probe/decompilation artifacts refer to `0x116B3C04`, and the repository's field/global address evidence has unresolved conflicts. The current ABI uses `0x016B3C04`; the conflict must be resolved against the current binary bytes and runtime module map before any installation. Do not silently treat the old value as equivalent (`tools/observatory/probes/cell_movement.json:1-4,31-39`; `docs/REPLACEMENT-ABI.md:40-52`; `tools/re/data/decompiled/MovePlayerToMousePosition.c:1-16`).

The reported `sCellGame` offsets, player fields, plane constants, and field meanings are static/alias evidence, not a live Cell contract. The normal is statically read as `{0,0,1}` in the current repository evidence, but the per-world point and field meanings remain unresolved or inferred (`docs/REPLACEMENT-DIFF.md:15-24,105-118`; `src/replace/CellGameView.hpp:4-14`).

### 6. Which candidates are useful for a proof of concept?

The candidates below are ordered by usefulness for a safe, observable PoC, not by claim that replacement is approved. The first five rows are the recommended first oracle set; `MovePlayerToMousePosition` is retained separately as the current, deferred gameplay target.

| Candidate | Static evidence and prototype | Observable / preferred mechanism | Main risk |
|---|---|---|---|
| `App::IAppSystem::Get` — `0x0067DCC0`, RVA `0x0027DCC0` | Trivial zero-argument global-pointer getter; cdecl is inferred and startup reachability is supported. | Returned pointer and entry registers; call-count/read-only identity control. A behaviorless positive control is easier to validate than a gameplay side effect. | It does not prove engine behavior beyond the getter; use as a control, not a gameplay replacement. |
| `App::cPropManager::SetDevMode` — `0x006A3300`, RVA `0x002A3300` | Inferred thiscall `void` setter taking `bool` and writing receiver `+0x15`; vtable association is medium confidence. | Receiver identity and the store at `+0x15`. Vtable replacement is possible only after slot and receiver validation. | No RTTI, inferred calling convention, and unresolved object identity. |
| `Math::MatrixToEuler` — `0x006A3920`, RVA `0x002A3920` | Likely hidden-sret `Vector3` return; aggregate return and exact parameter order must be confirmed. Deterministic scratch fixtures are suitable. | Hidden sret address, output bytes, input values, and return-path stack. Entry/call-site detour only after the sret contract is established. | Wrong hidden-pointer placement corrupts the stack; the current ABI is unresolved. |
| `Simulator::cCreatureGameData::SetEvolutionPoints` — `0x00D2E480`, RVA `0x0092E480` | Simple cdecl float setter, convention inferred, writing `0x0169E398`; runtime reachability is unconfirmed. | Input float, global write, return behavior, and call count. Call-site patch is preferred if one caller is proven. | Reachability, global identity, and the exact return convention still need observation. |
| `Transform::PreTransformBy` — `0x0040CCB0`, RVA `0x0000CCB0` | Inferred thiscall `Transform&` return; the SDK object size is `0x38`, while the decompilation shows a `0x48`-byte frame and a separate approximately `0x24`-byte matrix temporary. Richer and riskier. | Reference return, object contents, input arguments, and memory side effects. Trampoline/entry/call-site choice depends on a preserved-original requirement. | Reference/scratch lifetime, temporary layout, floating-point operation order, and transformation side effects are ABI-critical. |
| `MovePlayerToMousePosition` — `0x00E5B790`, RVA `0x00A5B790` | One-float void target with a clean 5-byte entry; caller and static body are known, but live semantics are not. | Float input, target/orientation/moving writes, return, and call count. A reversible call-site or entry detour is the proposed future test. | Unresolved field/global layout, no Cell reachability, and the host stand-in has the wrong signature. |

`App::IAppSystem::Get` is the smallest behaviorless positive control, but it is not a substitute for a gameplay oracle. `SetEvolutionPoints` or `SetDevMode` are simpler side-effect candidates than the current movement target. `MatrixToEuler` and `PreTransformBy` should wait for aggregate/reference-return validation.

### 7. What ABI and oracle are required?

The original is x86-32 Windows ABI code. A replacement must account for the following rules (`docs/RECON-3.1.0.22.md:83-89`; `docs/REPLACEMENT-ABI.md:84-100`):

- `cdecl` and `thiscall` are distinct. In `__thiscall`, the receiver is in `ECX`; other arguments use the stack.
- Stack arguments and return address layout must be preserved for an entry jump or trampoline.
- `RET` and `RET N` must be matched exactly. A replacement must leave `ESP` balanced.
- `EBX`, `EBP`, `ESI`, and `EDI` are callee-saved under the applicable convention.
- Wide integer/scalar returns may use `EDX:EAX`; the exact return rule must be selected per prototype.
- Aggregate returns may use a caller-provided hidden sret pointer, typically supplied through the stack, but this must be proven rather than assumed.
- Floating-point argument and return behavior must be reproduced according to the observed function, not guessed from a host C++ declaration.
- No selected target has an observed local SEH frame. The original contains SEH elsewhere, so this report does not claim exceptions are globally irrelevant.

A dedicated oracle must capture, for each selected call:

1. Module identity: PE path/version/hash, image base, loaded module base, and target bytes before/after.
2. Entry state: `EIP`, `ESP`, `EBP`, `EAX`, `EBX`, `ECX`, `EDX`, `ESI`, `EDI`, `EFLAGS`, and the argument words at the original entry. For the one-float cdecl target, the float is read from the original stack slot rather than from the current four-argument host stand-in.
3. Return state: a breakpoint or trampoline observation at the call-site continuation/return path, including `EDX:EAX`, `ESP`, flags, and whether the return instruction was `RET` or `RET N`. Entry-only INT3 data is insufficient.
4. Memory effects: pre/post values of the target global, receiver/player state, documented candidate fields, scratch/aggregate storage, and adjacent memory integrity bytes.
5. Reachability and lifecycle: caller identity, call count, thread ID, breakpoint detach, unhook status, and absence of crashes or unexplained module termination.

The existing observatory supplies function-entry events, registers, module discovery, and temporary breakpoints, but it does not supply return values or replacement injection. The existing screenshots and input logs are scenario evidence, not a Cell-stage oracle.

### 8. What is the recommended validation path and current status?

The safe sequence is:

1. **Read-only preflight — `not_implemented`:** verify the exact PE identity, linked VA/RVA/file-offset mapping, entry instruction boundary, module mapping, current global address, all direct and indirect callers, and relevant import/vtable evidence. Resolve the `0x016B3C04` versus `0x116B3C04` conflict from current bytes. Do not patch or run the game for this phase.
2. **ABI shim — `not_implemented`:** build a 32-bit one-float `void(float)` shim, with an explicit cdecl entry contract, balanced stack, preservation of callee-saved registers, and no dependency on the four-argument host stand-in. Test it in a disposable native harness first.
3. **Detour containment — `not_implemented`:** add a disposable-process patcher with instruction-boundary checks, rel32 range checks, page-boundary handling, original-byte retention, exact unhook, and a thread-quiescence protocol. Do not reuse the synthetic constructor as a production Spore patcher.
4. **Positive control — `blocked` until the above exists:** use a reachable, behaviorless zero-argument control such as `App::IAppSystem::Get` only after the preflight and oracle are available. It validates control flow and return observation, not gameplay behavior.
5. **Cell reachability — `blocked`:** obtain a positive Cell trace with the existing tracer and input/screenshot scenario plumbing, then record entry and return/memory observables. A zero-probe Cell run is not a passing replacement test.
6. **Target decision — `blocked` for Spore installation:** only after the oracle confirms the ABI and live state can a reversible call-site or entry detour be evaluated on a disposable process/copy. No actual patch is authorized by this document.

Current status is therefore:

- Mechanism: `verified_synthetic_only`.
- Host compatibility abstractions: `existing_host_only`.
- Host movement replacement: `replaced-approx` against a decompilation reference, not live-runtime verified (`docs/REPLACEMENT-DIFF.md:105-118`).
- Original Spore replacement: `not_implemented`.
- Cell runtime oracle: `blocked`.
- Safe PoC recommendation: read-only identity/preflight first, then a 32-bit one-float shim and reversible call-site/entry detour only in a disposable process/copy with entry, return, and memory validation.

## Conclusion

The repository establishes technical feasibility of an x86-32 entry detour and provides a useful native synthetic proof, but it does not establish a safe, live Spore replacement. The immediate work is a read-only identity validator and a dedicated return/memory oracle—not a patch to `SPORE`, not a binary modification, and not a claim that the current Cell field layout or ABI is known.
