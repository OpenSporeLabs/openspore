# Replacement Observability — Harness and Oracle Design

Status: design-only research artifact. No game, broad trace, patch, copy, canonical KG write, or executable modification was performed for this document.

## 1. Scope and decision

The required capability is a disposable-process replacement harness with a deterministic oracle. It must:

1. identify one target by binary identity, linked VA, true PE RVA, file offset, and load-base formula;
2. prove the selected attachment site, instruction boundary, relocation behavior, and original bytes before any write;
3. install either a process-local entry detour or a narrowly proven call-site replacement;
4. run explicit `original`, `bypass`, `passthrough`, `replace`, and only-if-needed `replace_then_original` policies;
5. preserve the x86-32 Windows ABI exactly;
6. restore the exact original bytes, page protection, breakpoint ownership, and thread state before process teardown; and
7. emit evidence for return state, state changes, memory writes, event emission, logs, screenshots, mode changes, object lifecycle, and save-state changes.

The work is split so the gates are not conflated:

- **Phase A — static preflight:** hashes and parses the PE, resolves VA/RVA/file offset, decodes instructions, checks caller/continuation coverage, and validates the ABI. It does not launch the game or write process memory.
- **Phase C — native ABI harness:** validates the shim and any trampoline on a controlled 32-bit target. It is not Spore evidence.
- **Phase B — read-only runtime preflight:** in an explicitly approved disposable process, discovers the module host and compares file, mapped, and original-bytes evidence. It may read only the declared oracle fields and arms no replacement.
- **Phase D — disposable Spore experiment:** installs and restores process-local code only after A, C, and B pass. Each policy uses fresh state.

The current Cell target is a candidate, not an authorized installation target. The only positive original-process evidence currently available is bounded startup/menu capture. The Cell probes have zero positive Cell events in the recorded S5 runs, and the game self-exits or stalls before Cell Stage. A zero-event run is a negative reachability result, not evidence that the replacement matches the original.

## 2. Evidence ledger

| Claim | Level | Evidence and boundary |
|---|---|---|
| Target is `Simulator::Cell::MovePlayerToMousePosition` | `CONFIRMED` | SDK name, return type, and parameter are recorded in `docs/REPLACEMENT-ABI.md:13-23` and `knowledgegraph/research/replacement-feasibility.json:355-390`. |
| Target linked VA is `0x00E5B790` | `CONFIRMED` | `docs/REPLACEMENT-ABI.md:13-20`; the current binary identity is SporeApp.exe 3.1.0.22. |
| True PE RVA is `0x00A5B790` | `VERIFIED` | `0x00E5B790 - 0x00400000`; the calculation and the file-offset rule are documented in `docs/analysis/original-exe-replacement.md:13-24`. |
| File offset is `0x00A5AB90` | `VERIFIED` | `.text` maps linked `0x401000` to file `0x400`; see `docs/REPLACEMENT-ABI.md:19-20` and `docs/analysis/original-exe-replacement.md:17-24`. |
| First five bytes are `a1 04 3c 6b 01` | `VERIFIED` | `docs/REPLACEMENT-ABI.md:25-39`; decode is `mov eax, [0x016B3C04]`. |
| `void(float)` cdecl contract | `CONFIRMED` return/parameter; `INFERRED` SDK convention label, `VERIFIED` static frame behavior | `docs/REPLACEMENT-ABI.md:21-23`; direct disassembly reads the original argument from `[ESP+4]`, uses a plain `RET`, and its sole Ghidra caller supplies a stack float and later removes it. No `RET N` is present. |
| Direct call site and continuation | `VERIFIED` static | Read-only Ghidra xref/disassembly of snapshot `f0e310e0` finds one direct caller, `FUN_00e806b0`, with `CALL 0x00E5B790` at `0x00E8083B` (`e8 50 af fd ff`) and continuation `0x00E80840`. This narrows the first Spore experiment to that five-byte call site; it does not prove runtime reachability. |
| Final return instruction | `VERIFIED` static | The function ends `ADD ESP,0x38; RET` at `0x00E5B9FE/0x00E5BA01`; there is no stack-pop immediate. This removes return cleanup as an unknown for the current target. |
| Physical moving field is `sCellGame+0x5270` | `VERIFIED` false by direct disassembly | Direct disassembly at `0x00E5B983..0x00E5B98E` loads `ECX = [sCellGame+0x5190]` and writes the byte `1` at `[ECX+0xE0]`. The field is one byte behind the `cCellSerializableData` pointer, not a four-byte word at `+0x5270`. Several repository prose/view files flatten this dereference and are internally consistent only with their stand-in. |
| Current host movement function is jump-compatible | `VERIFIED` signature/layout mismatch | `src/replace/Replace.hpp:66-67` and `src/replace/Replace.cpp:25-68` take four arguments; `src/replace/CellGameView.hpp:44-60` additionally models the rejected flattened moving field. Neither is the original one-argument x86 ABI nor the original write path. |
| `sCellGame` is at `0x016B3C04` | `VERIFIED` as the current instruction operand; `CONFIRMED` global name | The current bytes encode `0x016B3C04`. Older probe prose encodes `0x116B3C04`; this conflict is unresolved and must fail preflight until reconciled. See `docs/analysis/original-exe-replacement.md:54-68` and `tools/observatory/probes/cell_movement.json:31-39`. |
| Entry-detour mechanism works | `VERIFIED` synthetic only | `tools/replace/synthetic/hooker.c:31-66` and `tools/replace/synthetic/README.md:32-58` prove a native 32-bit `E9 rel32` write/readback. No Spore patch is proven. |
| Observatory captures function entry and register snapshots | `VERIFIED` | `tools/observatory/README.md:20-61`; the current JSON event is entry-only and lacks ESP, EBP, ESI, EDI, EFLAGS, return state, and memory snapshots. |
| Observatory can capture return values, exact write sets, or aggregate returns | `UNKNOWN` / not implemented | The tracer has no return, watchpoint, or post-call oracle. `knowledgegraph/research/replacement-feasibility.json:399-422` lists the missing fields. |
| Cell field meanings and plane point are live-verified | `INFERRED` / `APPROXIMATION` | `docs/REPLACEMENT-DIFF.md:15-24`; the normal is statically read, while the per-world point and live meanings are not verified. |
| Cell Stage was positively reached | `OBSERVED` negative result | `docs/devlog/018-s5-cell-runtime-evidence.md:25-63`; S5 recorded no Cell probe events and the game exited before Cell Stage. |
| Screenshot/input plumbing exists | `VERIFIED` for the existing shell, not a Cell oracle | `tools/observatory/cell_trace.sh:108-113,191-210,436-443`; screenshots and input logs are scenario evidence, not target-call evidence. |

Decompilation is evidence, not truth. This document does not promote any `INFERRED` field meaning or `APPROXIMATION` constant to a runtime contract.

## 3. Target identity and RVA resolution

### 3.1 Canonical target manifest

The harness must treat the following as an immutable, hash-pinned identity record. It must not accept a symbol name or an address string alone.

| field | required value for the current target |
|---|---|
| `artifact` | `SPORE/SporeBin/SporeApp.exe` |
| `artifact_version` | `3.1.0.22` |
| `artifact_sha256` | `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e` |
| `architecture` | `x86-LE-32 PE32/i386` |
| `pe_image_base` | `0x00400000` |
| `symbol` | `Simulator::Cell::MovePlayerToMousePosition` |
| `linked_va` | `0x00E5B790` |
| `pe_rva` | `0x00A5B790` |
| `file_offset` | `0x00A5AB90` |
| `section` | `.text` |
| `entry_bytes` | `a1 04 3c 6b 01` |
| `entry_decode` | `mov eax, dword ptr [0x016B3C04]` |
| `entry_relocation_class` | `relocation_free_absolute_operand`; the five overwritten bytes are complete and relocation-free |
| `entry_return_contract` | plain `RET` at `0x00E5BA01`; no immediate stack cleanup (`VERIFIED` static) |
| `direct_call_site` | linked VA `0x00E8083B`, bytes `e8 50 af fd ff`; one Ghidra direct xref from `FUN_00e806b0` |
| `direct_call_continuation` | linked VA `0x00E80840` |
| `preferred_scope` | call-site replacement for the first Spore experiment, subject to positive runtime reachability; entry detour remains the all-entry fallback |
| `declared_return` | `void` |
| `declared_parameters` | one `float` at entry stack slot `[ESP+4]` |
| `declared_convention` | `cdecl`; stack/caller-cleanup behavior is `VERIFIED` static even though the SDK has no convention attribute |
| `global_operand` | `0x016B3C04` (`VERIFIED` from current bytes; semantic name separately `CONFIRMED`) |
| `moving_observable` | `byte [u32[sCellGame+0x5190]+0xE0]`; pointer width and byte store are `VERIFIED` static, meaning is `INFERRED` |
| `runtime_address_formula` | `module_load_base + pe_rva` |
| `tracer_probe_rva_field` | `0x00E5B790`, because the existing tracer interprets its `rva` field as a linked VA and computes `load_base + (probe_rva - image_base)` |

The `tracer_probe_rva_field` naming is intentional. The existing `cell_movement.json` field called `rva` is not a raw PE RVA. A new artifact must carry both `pe_rva` and `tracer_probe_rva`; never serialize both as the same field.

### 3.2 Phase-A static preflight (no launch)

Phase A operates only on the immutable file and static analysis corpus. It must stop on any mismatch:

1. Hash the executable and compare size, PE machine, image base, section table, timestamp, and checksum metadata with the target manifest.
2. Recompute `pe_rva` from the PE section mapping and recompute `file_offset`; never subtract the image base from a file offset.
3. Read the file at `file_offset`; compare all five expected entry bytes and a declared before/after guard window.
4. Decode the first instruction independently. It must be one complete, relocation-free `mov eax,[0x016B3C04]`; `0x116B3C04` is not an accepted alias.
5. Verify the preferred call site at `0x00E8083B` is an instruction-aligned five-byte `E8 rel32`, its decoded target is the selected function, and its continuation is `0x00E80840`. Store both call-site and entry-site decision records even if only one is chosen.
6. Re-read the terminal instructions and record the verified plain `RET` at `0x00E5BA01`; the ABI profile records that there is no `RET N` immediate.
7. Resolve the direct xref set and the known static caller. Record that the current Ghidra graph has one direct reference while runtime reachability remains unobserved; do not turn that bounded graph result into a universal dynamic-caller claim.
8. Enumerate direct writes and called callees in the selected function. The minimum static write set is the player target words, player orientation words, and the one-byte serializable-state store; called-callee effects remain a separate required oracle channel.
9. Resolve the page boundaries and signed `rel32` range for each proposed site. Entry and call-site patches are both five bytes for this target.
10. Produce a complete check list. A skipped required check is `fail` or `blocked`, never `pass`.

Phase A is the artifact that permits design review. It does not authorize a game run, process-memory read, or process-memory write.

### 3.3 Phase-B read-only runtime preflight (approved disposable process)

Phase B runs only after Phases A and C pass and the normal human/runtime gates are satisfied. Before any replacement write, it must:

1. Record PID, lineage, Wine generation, host path, module path, module load base, header mapping, executable mapping, and whether code is file-backed or Wine's anonymous PE mapping.
2. Resolve `runtime_site = module_load_base + pe_site_rva` and prove the target and call-site addresses lie in the expected module mapping.
3. Read the exact site and guard window from process memory. For the relocation-free entry bytes, equality with the file is required. For a future PC-relative target, the validator must apply the declared relocation class instead of incorrectly requiring identical bytes.
4. Check that the current bytes equal the expected original bytes. Reject `0xCC` and reject every byte sequence not owned by the baseline oracle; never overwrite an unknown writer.
5. Verify page protection, page boundaries, and write scope. No change occurs in Phase B.
6. Read only the approved oracle whitelist: global pointer, pool index, declared gate fields, plane values, resolved object guard ranges, serializable pointer/byte, mode identity, and the isolated prefix/save-directory identity.
7. Record all breakpoint/debug-register owners. The existing observatory cannot share an address with the patch writer.
8. Require a disposable process, byte-identical copy identity, isolated prefix/save directory, explicit write authorization, and a declared end condition before transitioning to Phase D.

The Phase-B output includes both pass/fail reasons and coverage. `not_observed` means a declared capture channel had no event; it is not automatically a pass.

### 3.4 Mechanism selection and decision record

The harness must select one concrete attachment mechanism; a menu of plausible mechanisms is not an installation contract.

| mechanism | required proof | disposition for the current Cell target |
|---|---|---|
| PE import replacement | target is an actual imported symbol and import slot/owner is identified | rejected: the engine is statically linked |
| vtable replacement | live receiver, subobject, vptr, slot, and dispatch are proven | deferred: no RTTI and no live dispatch evidence; unnecessary for a global free function |
| function-pointer replacement | writer, reader, lifetime, publication, and synchronization are all proven | deferred: no such pointer evidence for this target |
| call-site replacement | exact instruction, direct caller set, stack contract, continuation, and scope are pinned | **preferred first Spore experiment:** `0x00E8083B`, continuation `0x00E80840`; does not cover unobserved dynamic calls |
| entry detour | all entry paths, exact overwrite instructions, relocation class, and unhook are proven | fallback: all entries at `0x00E5B790`; first five bytes are clean and relocation-free |
| trampoline | relocated prefix, stack frame, return path, and lifetime are independently tested | required only for entry `passthrough`; not needed for call-site passthrough because the dispatcher can call the untouched original |

The decision record names `call_site:00e8083b` or `entry:00e5b790`, exact site bytes, original-byte owner, target destination class, relocation strategy, page set, thread-quiescence method, and unhook owner. It also records rejected alternatives and why. A symbol name, linked VA, or prior feasibility JSON is insufficient input to the installer.

## 4. Safe replacement lifecycle

### 4.1 Containment model

The safe unit is a controller plus a child process launched from a byte-identical disposable executable, an isolated disposable Wine prefix, and an isolated disposable save/profile directory. The canonical `SPORE/` tree, canonical saves, canonical KG, and original executable remain read-only. The copy's file hash is recorded before and after every process lifetime and must remain identical for a process-local experiment.

The executable copy is an isolation boundary, not permission to patch the file. The intended design is process-local only: controller writes target process memory, and the on-disk copy never changes. If a file-backed experiment is ever proposed, it requires a separate disposable file, a separate authorization record, and cannot be presented as evidence about the canonical executable.

The lifecycle is fail-closed and separated into non-writing and write-bearing states:

```text
PHASE_A_STATIC_IDENTITY
  -> PHASE_C_NATIVE_ABI_GATE
  -> PHASE_B_RUNTIME_IDENTITY
  -> BASELINE_ORIGINAL_RUN
  -> COLLECT_BASELINE
  -> FRESH_DISPOSABLE_POLICY_PROCESS
  -> RUNTIME_READ_PREFLIGHT
  -> SUSPEND_AND_VERIFY
  -> INSTALL
  -> VERIFY_PATCH
  -> RESUME
  -> RUN_BOUNDED_POLICY
  -> COLLECT_POLICY
  -> SUSPEND_AND_VERIFY
  -> RESTORE
  -> VERIFY_RESTORE
  -> DETACH
  -> FINAL_COPY_HASH_AND_CLEANUP
  -> COMPARE
```

The baseline is an unpatched run. Every non-baseline policy starts from a fresh process or a demonstrably equivalent reset state; state is not reused merely because the original bytes were restored. A failure at any write-bearing state terminates that disposable process. It must not retry a write blindly.

### 4.2 Installation checks

The installer must use one process-side 32-bit writer and one owner lock. It must not run concurrently with the existing INT3 tracer on the same address.

Before writing, while all affected threads are stopped:

- verify module identity, attachment site, and original site bytes again;
- verify the site and destination fit the 32-bit address space;
- for an entry detour, verify `dest - (site + 5)` fits signed `rel32`; for the call site, verify `dest - (site + 5)` for `E8 rel32`;
- verify the exact five-byte overwrite is within one mapped page, or model both pages as one transaction;
- verify the overwritten instructions are independently decoded and classified as `relocation_free`; no arbitrary relocation is performed;
- retain the exact original five bytes, original page protection, original call/entry continuation, and the full guard window;
- reject a pre-existing `E9`, `E8`, or other detour unless it is byte-for-byte the replacement being managed;
- reject an observatory `INT3` or any other writer at the site;
- write exactly `E9 rel32` for an entry detour or `E8 rel32` for a call-site replacement, changing no unrelated byte;
- read back all five bytes and compare them with the requested patch;
- restore the original page protection and issue a process-local instruction/cache-coherency barrier appropriate to the host;
- emit `installed` with the transaction ID, site, destination, old/new protection, thread snapshot, and readback result before resuming the process.

The target page must be writable only for the bounded write window. `RWX` is not a permitted steady state. If the patch writer itself executes from a protected code page, the design must use a separate writable/valid dispatch location rather than copying the synthetic's same-page RWX shortcut.

On Windows/Wine, page protection must be changed through the target process's 32-bit Windows/Wine-compatible mechanism, preserving the old protection. The native synthetic's `mprotect`/RWX approach is not a production Spore implementation. RWX is not an acceptable steady state.

### 4.3 Unhook and failure handling

Unhook is mandatory and must precede process teardown:

1. Stop the policy-specific call and wait for the bounded run to quiesce.
2. Suspend all affected threads. Record every thread ID and verify no stopped thread has `EIP` in the replacement, trampoline, dispatcher, or overwritten bytes and no thread owns a pending site `INT3`.
3. Read the current site bytes. Restore only if they equal the installer-owned bytes.
4. If they differ, record a byte conflict, do not overwrite an unknown writer, terminate the disposable process, and mark the run failed.
5. Restore the exact original five bytes and original page protection.
6. Read back the original bytes, guard window, and page protection.
7. Verify the selected site is no longer redirected, remove all harness-owned debug/watchpoint state, then detach.
8. Record `restored`, `restore_readback`, `page_protection_readback`, `debug_state_restored`, and `detach` as separate events.
9. Recompute the disposable executable hash and verify no canonical path, save, profile, or KG file changed.

Restoration is a mandatory experiment outcome, not best-effort cleanup. A failed restore makes the entire experiment fail even if policy behavior looked correct.

The existing synthetic retains original bytes but does not implement a production unhook, relocator, range check, page-boundary handling, or thread quiescence (`knowledgegraph/research/replacement-feasibility.json:89-107,152-181`).

## 5. ABI contract for the current target

The current host implementation in `src/replace/Replace.hpp:66-67` takes four arguments and is not a valid target for the original. Its POD view also flattens the serializable-data write and is not an ABI-compatible memory model. The installed replacement must therefore be a separate one-argument x86-32 Windows-ABI shim:

```text
void replacement(float deltaTime)
```

The original frame at function entry is:

```text
[ESP + 0]  return address
[ESP + 4]  float deltaTime bits
```

For an entry detour, the shim inherits that frame and must eventually execute a plain `RET`. For a call-site replacement, the caller's `CALL` creates the same frame and the dispatcher returns through it. A dispatcher that calls the original for passthrough must use an explicit adapter and restore its own frame; it must not assume a normal C++ wrapper is transparent.

The shim/dispatcher must:

- read the float from the original argument slot and preserve NaN payload/sign bits if it uses the value;
- match the selected call/entry return continuation;
- leave `ESP` balanced and return with a plain `RET` for this target;
- preserve `EBX`, `EBP`, `ESI`, and `EDI`; the original itself pushes/restores `ESI` and `EDI` on some paths;
- avoid C++ exceptions, CRT/runtime dependencies, and unbounded allocation in the hot path;
- run as 32-bit code and accept only a 32-bit destination;
- treat XMM/YMM registers and `EFLAGS` as volatile and diagnostic, not preserved outputs;
- preserve the direct-call scope when the call site is selected, or preserve entry semantics when the entry is selected;
- never reuse `src/replace/Replace.cpp` directly until its signature and memory-view discrepancies are replaced by a separately validated x86 shim.

`EAX`, `ECX`, and `EDX` have no meaningful `void` return value, but raw bits must still be captured for caller-corruption evidence. The original caller does not receive a defined value from them. `EFLAGS` is captured for diagnosis only.

Static disassembly directly verifies the lock guard, `FUN_00B721D0` lookup, called per-frame/UI/camera gates, ray-plane stores, the one-byte write `[u32[sCellGame+0x5190]+0xE0] = 1`, orientation stores, and plain return. These operations define the minimum oracle whitelist, not a license to treat field meanings as runtime-verified. The oracle must still resolve the player index through the real pool lookup and must sample the serializable pointer before dereferencing it.

### 5.1 Phase-C native ABI acceptance matrix

The controlled 32-bit harness must pass all of these before any Spore write:

| ID | exact fixture | required result |
|---|---|---|
| ABI-01 | normal float, finite, zero, subnormal, `+Inf`, `-Inf`, quiet/signaling NaN payload variants | dispatcher/shim receives the exact 32-bit argument; no canonicalization |
| ABI-02 | call-site `E8 rel32` and entry `E9 rel32` paths | identical one-float frame contract; no wrapper-relative drift |
| ABI-03 | return through both attachment modes | plain `RET`, exact caller continuation, caller `ESP` equals expected pre-call value |
| ABI-04 | sentinel values in `EBX/EBP/ESI/EDI` | exact preservation on every path and policy |
| ABI-05 | nested/re-entrant dispatcher call | stack and per-thread state remain balanced; no global one-shot state |
| ABI-06 | bypass | replacement marker increments once; original marker remains zero |
| ABI-07 | passthrough | original marker increments exactly once; caller/return evidence remains intact |
| ABI-08 | replace_then_original | marker order is exactly replacement → original → continuation |
| ABI-09 | fault-injection before/after dispatcher state transition | no false success; transaction reports exact failure owner |
| ABI-10 | repeated install/restore cycles | original bytes/protection match on every cycle; no drift |
| ABI-11 | multi-thread call | per-thread calls pair correctly; no shared mutable call slot |
| ABI-12 | page-boundary and out-of-`rel32` fixtures | rejected before any write |

The harness records the same `call_id`/transaction schema proposed in Section 8. A green behavioral differential does not compensate for any ABI-row failure.

## 6. Execute, bypass, and original passthrough policies

Each policy must run in a fresh disposable process or a fresh explicitly reset state. State must not be reused across policies merely because bytes were restored.

| policy | call-site attachment | entry attachment | expected execution | purpose |
|---|---|---|---|---|
| `original` | no patch | no patch | caller reaches untouched original | baseline |
| `bypass` | dispatcher returns without original | shim returns without original | replacement attachment executes, original does not | proves ownership, frame, and return |
| `passthrough` | dispatcher calls untouched original, then returns | dispatcher tail-jumps relocation-correct trampoline | original executes exactly once | proves passthrough parity and original return |
| `replace` | replacement returns | replacement returns | replacement executes, original does not | measures declared behavior delta |
| `replace_then_original` | replacement executes, then dispatcher calls original, then returns | replacement executes, then dispatcher tail-jumps trampoline | both execute in a declared order | optional stateful experiment only |

For an entry `passthrough`, a minimal trampoline may relocate the exact first instruction `A1 04 3C 6B 01` and jump to `target+5`, where `SUB ESP,0x38` begins. This remains a design candidate: the Phase-C harness must verify the decoder output, relocation-free class, continuation, plain `RET`, thread entry points, and all failure paths. For the preferred call site, no trampoline is needed because the original entry remains intact; the dispatcher supplies an explicit original-call adapter.

A normal C++ wrapper must not silently define the policy. It adds a frame and can make callee-saved, argument, exception, and return evidence ambiguous. `replace_then_original` is prohibited until baseline, bypass, and passthrough independently pass and the policy order is explicitly encoded in the manifest.

A positive control should precede Cell work. `App::IAppSystem::Get` is linked VA `0x0067DCC0`, PE RVA `0x0027DCC0`, with known bytes `a1 90 d8 5f 01 c3` (`docs/analysis/original-exe-replacement.md:70-83`). It is useful for EAX/return observation, but it is not evidence of Cell behavior. Its instruction boundary, caller set, continuation, and module identity require their own preflight.

## 7. Deterministic oracle model

Every observation is associated with one `call_id` and one `policy`. A run is rejected as a differential result if any required coverage field is missing.

The canonical observable vector is:

```text
O = {
  target_identity,
  attachment_transaction,
  entry_frame,
  return_frame,
  typed_return,
  state_before,
  state_after,
  direct_writes,
  guard_memory,
  events,
  logs,
  screenshots,
  input,
  mode_axes,
  object_lifecycle,
  save_state,
  restore_evidence
}
```

Each item carries `value`, `raw_bits`, `source`, `coverage`, `evidence_level`, and `comparison_rule`. The deterministic comparison rules are:

| observable | canonical comparison | disallowed shortcut |
|---|---|---|
| return/control state | exact 32-bit register bits, exact stack delta, exact continuation, exact `RET` form | “returned without crashing” |
| integer/enum/pointer | exact bits plus separately decoded signed/unsigned/pointer meaning | address normalization or pointer reuse |
| float/vector/quaternion | raw-bit equality first; numeric delta and ULP/absolute delta second; NaN payload, sign, and `-0.0` retained | tolerance-only equality that hides `-0.0`/NaN differences |
| state change | exact before/after bytes at the same owner-qualified address, with unresolved pointer meaning marked | reading a different pool object or conflating fields across owners |
| memory write | exact address/width/source PC or watchpoint and before/after bits | snapshot delta labeled as an exact write site |
| event | exact sequence within a declared capture horizon, source, ID, and payload hash | unordered set comparison or omitted `not_observed` records |
| mode/lifecycle | exact ordered transition tuple per owner axis | one global “mode” enum inferred from a screenshot or generic frame |
| object identity | pool index + object address + bounded object hash + generation status | raw pointer alone across pool reuse |
| save state | exact serialized-file bytes/hash when parity is required; otherwise exact whitelisted in-memory fields and explicit unknown coverage | runtime rebuild called a save |
| logs | raw hash plus normalized hash using a versioned allowlist | normalizing addresses, IDs, values, or crash text |
| screenshot | exact PNG hash plus capture metadata | image similarity as a substitute for call/state evidence |

Comparison runs in three layers: `mechanical` (schema, pairing, identity, restore), `declared_delta` (only fields the replacement is authorized to alter), and `external_effect` (events/logs/screens/mode/lifecycle/save). A policy can pass one layer and fail another; no layer silently substitutes for another.

### 7.1 Call and return observation

For every selected call, capture entry and return records with:

- For call-site attachment, `entry` means the first instruction of the owned dispatcher and `original_entry` is a separate optional/nested event at `0x00E5B790`; for entry attachment, `entry` is the original/replacement target entry itself.
- For call-site attachment, `return` is observed at `0x00E80840`; for entry attachment, the oracle also requires a caller continuation or equivalent post-return mechanism.
- `run_id`, `copy_id`, `phase`, `policy`, `scenario_id`, `frame_id`, `call_seq`, and `call_id`;
- monotonic entry/return timestamps and thread ID;
- attachment kind and site, target linked VA/PE RVA, runtime address, original/installed bytes, caller, and expected continuation (`0x00E80840` for the current call site);
- `EIP`, `ESP`, `EBP`, `EAX`, `EBX`, `ECX`, `EDX`, `ESI`, `EDI`, and `EFLAGS` as raw 32-bit values;
- stack words at `[ESP]`, `[ESP+4]`, and a bounded caller-frame guard window;
- the float argument as both `u32_bits` and an optional JSON number;
- return instruction address, opcode, and immediate cleanup value; for the current original target, `0x00E5BA01 / RET / 0` is the expected static contract;
- `ESP` delta from entry to return and exact post-call continuation observation;
- callee-saved comparison for `EBX`, `EBP`, `ESI`, and `EDI`;
- replacement/original policy transition markers, original-execution count, and trampoline entry if used.

The dedicated oracle must pair entry and continuation by thread, call site, stack return address, and monotonic sequence. The current observatory event is entry-only. A future continuation probe is a proposal, not an existing capability.

For a non-void target, add a typed return interpretation: pointer, signed/unsigned integer, wide `EDX:EAX`, or hidden-sret output. For the current `void(float)` target, return semantics are `void`; raw register values are diagnostic only.

The existing observatory event is not sufficient. Its current event line contains only `t`, `rel`, `tid`, `name`, `rva`, `addr`, `this`, `eax`, `ebx`, `ecx`, `edx`, and heuristic `depth` (`tools/observatory/probe_tracer.cpp:1074-1086`).

### 7.2 State snapshots

Capture a canonical before/after snapshot at function entry and at the direct-call continuation. Static linked addresses below must be converted through the module load delta; no oracle should assume Wine used preferred base `0x00400000` merely because the PE header does.

| state | static source address / resolution | semantics status |
|---|---|---|
| `sCellGame` global slot | linked `0x016B3C04`, 4 bytes; runtime `module_base + (linked - image_base)` | slot/address `VERIFIED`; global name `CONFIRMED` |
| lock field | `sCellGame+0x5158`, 4 bytes | offset/store `VERIFIED` static; meaning `INFERRED` |
| player pool index | `sCellGame+0x411C`, 4 bytes | offset/use `VERIFIED` static; index/lookup behavior `SUPPORTED`, not a pointer |
| serializable pointer | `sCellGame+0x5190`, 4 bytes | pointer slot and `cCellSerializableData` candidate `SUPPORTED` |
| moving byte | resolved `u32[sCellGame+0x5190]+0xE0`, 1 byte | physical write `VERIFIED` static; semantic meaning `INFERRED`; null dereference is a risk |
| caller update gates | `sCellGame+0x515C` and `sCellGame+0x51E0`, 4 bytes each | access `VERIFIED` static; meanings `INFERRED` |
| movement-plane normal | linked `0x015A7C40..0x015A7C4C`, 12 bytes | addresses `VERIFIED`; runtime values captured per call |
| movement-plane point | linked `0x016B3C28..0x016B3C34`, 12 bytes | addresses `VERIFIED`; per-world value `UNKNOWN` until read |
| Cell UI pointer and gates | linked `0x016B3C0C`, then `sCellUI+0x24/+0x26`, 1 byte each when the pointer resolves | accesses `VERIFIED` static; UI meaning `INFERRED` |
| camera mode word | return of `0x00E4CE40`, then `+0xD4`, 4 bytes | access `VERIFIED` static; mode meaning `INFERRED` |
| player target | pool-resolved player `+0x08..+0x10`, 12 bytes | stores `VERIFIED` static; role `SUPPORTED/INFERRED` |
| player orientation | pool-resolved player `+0x14..+0x20`, 16 bytes | stores `VERIFIED` static; quaternion layout/meaning `INFERRED` |
| player current position | pool-resolved player `+0x4C..+0x54`, 12 bytes | reads `VERIFIED` static; role `INFERRED` |
| player object identity | object `+0x00`, object address, bounded object hash | pool identity `SUPPORTED`; generation/reuse semantics remain explicit |
| object guard windows | before/after each bounded candidate range | detects overflow/underflow; does not identify the writer |

If `sCellGame` or the serializable pointer changes across a call, compare both resolved objects and emit a lifecycle event; do not compare a byte at the old address to a byte at the new address as if they were the same field. A null serializable pointer is recorded as `unreadable`; the original's dereference behavior is not normalized away by the oracle.

A state field is `changed` when its raw bytes differ. Store both raw bits and a numeric interpretation. Float comparison must never discard NaN, negative zero, or sign information. Runtime float comparison is reported as both exact-bit equality and numeric delta; the existing host `1e-6` comparison is not a runtime promotion rule.

### 7.3 Memory-write evidence

A before/after difference is not by itself proof of a write instruction. Every write record must state its evidence source:

- `watchpoint`: a hardware debug-register observation at the exact address and width;
- `store_probe`: an execution stop at a statically identified store instruction, with the source operand captured;
- `snapshot_delta`: only the first and last bytes were observed; the write site is unresolved;
- `page_guard`: a bounded page/guard observation; the exact store is unresolved;
- `not_observed`: no write was captured in the declared coverage.

For the current target, the minimum write oracle is:

1. a target-entry snapshot and post-call continuation snapshot;
2. hardware watchpoint coverage for the serializable pointer slot, serializable byte, lock field, player pool index, and player target/orientation fields, cycled across calls because x86 has finite debug registers;
3. a store probe at each selected direct write: player target stores at `0x00E5B97A/0x00E5B97D/0x00E5B980`, serializable-byte store at `0x00E5B98E`, and player orientation stores at `0x00E5B9E4/0x00E5B9EA/0x00E5B9F0/0x00E5B9F6`;
4. bounded entry/return probes for called functions whose effects are omitted from the current stand-in, including at least `0x00E5B2E0`, `0x00743B50`, `0x00E82130`, `0x007C4900`, and `0x0069B600`, selected only as needed for the declared call;
5. guard-window comparison; and
6. a coverage record listing every field/callee not directly watched.

The exact store PCs above are read-only static evidence for the current disassembly. A watchpoint proves an access; a store probe plus pre/post memory proves a write at that instruction. Either one alone is insufficient for a claim about the other. If the harness cannot cover all writes, the result is `partial_write_coverage`, not a passing replacement. A call-local instruction trace is permitted for one selected call with a hard instruction/event cap; whole-process tracing is not part of this design.

### 7.4 Events and message observations

Event capture must be bounded to known handlers, message IDs, or a selected dispatcher. The event map identifies `kMsgAppUpdate = 0x01EE100A`, mode-exit `0x0212D3E7`, mode-enter `0x022D1ADC`, save request `0x01CD20F0`, and the Cell interaction dispatcher `0x00E7E130`, but many payload meanings remain unresolved (`docs/analysis/event-message-map.md:80-112`).

Before execution, declare a capture horizon: start at the logged input or selected call, stop after a fixed number of app-update frames or elapsed monotonic time, and include an explicit queue-drain marker. Deferred events emitted after that horizon are outside the run, not evidence of non-emission. Keep App messages, UTFWin messages, Cell interaction records, animation messages, and persistence callbacks as separate event families.

Each event record must include:

- event sequence and call/frame relationship;
- source RVA or handler identity;
- message ID and payload length, or `unknown`;
- raw payload hash and, only when decoded, typed fields;
- producer/consumer confidence;
- `observed`, `not_observed_in_capture`, or `static_only` status.

An empty event file means `not_observed_in_capture` with a declared coverage window. It never means that the game emitted no event.

### 7.5 Mode changes

For each mode-sensitive frame, record the active mode before the target call and after return. When the known mode transition helper or handlers are observed, record:

- owner-qualified axis values for App active mode, Simulator strategy/input, SpaceContext/scenario mode, and Cell lifecycle; these axes must not be collapsed into one enum;
- old/new mode IDs and the mode-entry names/handles only when decoded;
- mode enter/exit announcement IDs;
- handler RVAs and thread IDs;
- ordering of `OnExit`, App active-index change, `OnEnter`, and announcements, where observed;
- a `queue_drained`/capture-end marker so absence inside the horizon is explicit;
- `cell_stage_reached` only when a positive Cell-specific control and the target call path are both observed.

The existing rule “any non-control cell probe fired” is a reachability heuristic, not a semantic mode proof. `FUN_0069B600` is known to fire in the main-menu frame loop and must not be used as a Cell marker (`docs/analysis/CELL-RUNTIME-OBSERVATION.md:65-84`).

### 7.6 Logs and process lifecycle

Capture bounded stdout, stderr, Wine diagnostics, tracer diagnostics, and harness diagnostics. Each line or stream chunk records raw bytes, sequence, stream, and SHA-256. For comparison, store both:

- `raw_sha256`, which proves artifact integrity; and
- `normalized_sha256`, after replacing only run IDs, PIDs, timestamps, temporary paths, and other explicitly allowed nondeterminism.

Do not normalize addresses, message IDs, return values, or memory values. Record process exit status, terminating signal, crash signal, and any fault address. A clean exit is not automatically a pass; the target policy, expected calls, and required artifacts must also pass.

### 7.7 Screenshots and input

Reuse the existing `maim` screenshot and focused-window input discipline, but make screenshots part of the oracle:

- `shots/<seq>.png` is the exact captured image;
- `shots.jsonl` records sequence, path, SHA-256, dimensions, window geometry, mode label, input event, and `delta_vs_prev_sha`;
- `input.jsonl` records timestamp, target window ID, exact command, allowlist result, and outcome;
- before/after images use the same pinned geometry and input sequence;
- animated frames are not required to be pixel-identical across runs unless the scenario is explicitly frozen.

A screenshot is supporting presentation evidence. It cannot substitute for a target call record or memory/state record.

### 7.8 Object lifecycle

For the Cell target, record `sCellGame+0x411C` before and after lookup, the resolved `cCellObjectData*`, and at least these owner-qualified fields: object self-index `+0x00`, model/content key `+0xFC`, runtime resource reference `+0x108`, health `+0x244`, GFX index `+0x248`, scale `+0x358`, query pointer `+0x35C`, and a bounded object hash. Also record `sCellGame+0x5190` serializable pointer separately; it is not part of the live object identity.

The lifecycle event vocabulary is:

```text
unresolved | resolved | create | attach | detach | rebuild | release | destroy | reuse | unknown
```

Each object event includes pool index, object address, source RVA, thread, pre/post object hash, generation status, and lifecycle time. If the original pool provides no generation counter, `generation_status` remains `unknown`; a reused address is never promoted to stable identity merely because it equals an earlier pointer. `FUN_00E66010`/`0x00E6D8F0` are static evidence for separate per-cell GFX detach/attach operations that retain the Cell object in those branches, while `FUN_00E780A0`/`0x00E7FD00` are static evidence for identity-destructive release/rebuild. None proves that a specific run executed the lifecycle.

### 7.9 Save-state changes

Save/load behavior is currently unobserved. Any future save experiment must use the disposable process/copy and an isolated prefix/save directory. The minimum in-memory whitelist is the `sCellGame+0x5190` serializable pointer, the resolved `cCellSerializableData` 236-byte object when non-null and safe to read, the player pool index, and any explicitly declared mode/progression fields. The `0xEC`-byte object is a serializable-state candidate, not a proven complete save payload.

Record:

- save request/message ID and handler RVA;
- request-to-write ordering and capture horizon;
- before-request, pre-write, post-write, and post-close hashes of the declared whitelist;
- pointer identity and field-by-field before/after table for safe scalar candidates;
- save/temp file relative path, byte length, and SHA-256, if a file is actually created;
- temp-to-final replacement event, completion/failure result, and dialog/screenshot evidence;
- `not_serialized`, `not_observed_in_capture`, and `unreadable` as distinct statuses.

Do not claim persistence from a changed in-memory field, `cCellSerializableData` eligibility, `OnExit`/`Dispose`, or an SDK save message name. A missing save file is `not_observed_in_capture`, not proof that the original did not save. Byte-identical saves are a separate, stronger requirement than whitelisted field parity and may remain unsupported unless the outer persistence contract is proven.

## 8. Proposed artifact formats

All runtime artifacts belong under a disposable run directory such as `/tmp/openspore-replacement/<run_id>/`, never under `SPORE/`, `tools/observatory/out/`, or the canonical KG. The following formats are proposed, not implemented.

### 8.1 `preflight.json`

Required top-level fields:

```json
{
  "schema": "replacement-preflight-1",
  "phase": "A_static|B_runtime",
  "run_id": "string",
  "created_utc": "RFC3339 string",
  "source": {
    "path": "string",
    "sha256": "64 lowercase hex characters",
    "size": 0,
    "version": "string",
    "sha256_before_run": "64 lowercase hex characters"
  },
  "target": {
    "symbol": "string",
    "linked_va": "0xXXXXXXXX",
    "pe_rva": "0xXXXXXXXX",
    "tracer_probe_rva": "0xXXXXXXXX",
    "file_offset": "0xXXXXXXXX",
    "section": "string",
    "image_base": "0xXXXXXXXX",
    "entry_bytes": "lowercase hex",
    "entry_decode": "string",
    "return_contract": "void|integer|pointer|wide|aggregate",
    "parameter_contract": "object",
    "calling_convention": "cdecl|thiscall|fastcall|unknown",
    "ret_cleanup_bytes": 0,
    "ret_instruction_verified": true
  },
  "module": {
    "pid": 0,
    "host_path": "string",
    "load_base": "0xXXXXXXXX",
    "code_mapping": "object",
    "original_page_protection": "string",
    "module_identity_verified": true
  },
  "checks": [
    {
      "id": "string",
      "status": "pass|fail|blocked|not_applicable",
      "evidence_level": "CONFIRMED|VERIFIED|OBSERVED|SUPPORTED|INFERRED|APPROXIMATION|UNKNOWN",
      "observed": {},
      "failure_reason": "string|null"
    }
  ],
  "result": "pass|fail|blocked"
}
```

`not_applicable` is allowed only for checks assigned exclusively to the other phase. A missing or skipped check required for the current phase is `blocked` or `fail`; it never enables a write phase.

### 8.2 `target-manifest.json`

This is the immutable target contract consumed by the patcher:

```json
{
  "schema": "replacement-target-manifest-1",
  "binary_sha256": "64 lowercase hex characters",
  "image_base": "0x400000",
  "module_suffix": "SporeApp.exe",
  "targets": [
    {
      "target_id": "cell-move-player",
      "symbol": "Simulator::Cell::MovePlayerToMousePosition",
      "linked_va": "0x00E5B790",
      "pe_rva": "0x00A5B790",
      "tracer_probe_rva": "0x00E5B790",
      "file_offset": "0x00A5AB90",
      "entry_bytes": "a1043c6b01",
      "overwrite_bytes": 5,
      "return_cleanup_bytes": 0,
      "ret_instruction_address": "0x00E5BA01",
      "ret_instruction_verified": true,
      "preferred_call_site": "0x00E8083B",
      "preferred_call_site_bytes": "e850affdff",
      "call_continuation": "0x00E80840",
      "entry_relocation_class": "relocation_free",
      "moving_write": "byte [u32 [sCellGame+0x5190]+0xE0]",
      "expected_page_boundary": false,
      "expected_operands": ["0x016B3C04"],
      "policy": ["original", "bypass", "passthrough", "replace", "replace_then_original"],
      "entry_level": "VERIFIED",
      "abi_level": "VERIFIED_STATIC"
    }
  ]
}
```

`return_cleanup_bytes` is zero for this target only because the final plain `RET` is now statically verified at `0x00E5BA01`. A new target must leave the field null/blocked until its own return is decoded.

### 8.3 `transactions.jsonl`

One JSON object per install, execution, or restore transaction:

```json
{
  "schema": "replacement-transaction-1",
  "run_id": "string",
  "transaction_id": "string",
  "phase": "preflight|install|run|restore|detach|abort",
  "policy": "original|bypass|passthrough|replace|replace_then_original",
  "target_id": "string",
  "tid": 0,
  "t_rel_ns": 0,
  "runtime_target": "0xXXXXXXXX",
  "original_bytes": "hex",
  "installed_bytes": "hex|null",
  "page_start": "0xXXXXXXXX",
  "page_end": "0xXXXXXXXX",
  "old_protection": "string|null",
  "new_protection": "string|null",
  "rel32_delta": 0,
  "readback_match": true,
  "status": "started|verified|failed|restored",
  "failure_reason": "string|null"
}
```

### 8.4 `calls.jsonl`

One record for every target entry and one matching return record:

```json
{
  "schema": "replacement-call-1",
  "run_id": "string",
  "call_id": "string",
  "scenario_id": "string",
  "frame_id": "integer",
  "call_seq": "integer",
  "policy": "original|bypass|passthrough|replace|replace_then_original",
  "phase": "entry|return",
  "target_id": "string",
  "attachment_kind": "call_site|entry",
  "attachment_runtime_site": "0xXXXXXXXX",
  "original_entry_observed": true,
  "tid": "integer",
  "t_rel_ns": "integer",
  "runtime_target": "0xXXXXXXXX",
  "caller": "0xXXXXXXXX",
  "return_address": "0xXXXXXXXX",
  "expected_continuation": "0xXXXXXXXX",
  "registers": {
    "eip": "0xXXXXXXXX", "esp": "0xXXXXXXXX", "ebp": "0xXXXXXXXX",
    "eax": "0xXXXXXXXX", "ebx": "0xXXXXXXXX", "ecx": "0xXXXXXXXX",
    "edx": "0xXXXXXXXX", "esi": "0xXXXXXXXX", "edi": "0xXXXXXXXX",
    "eflags": "0xXXXXXXXX"
  },
  "stack": {
    "arg0_bits": "0xXXXXXXXX",
    "arg0_f32": 0.0,
    "guard_before": "hex",
    "guard_after": "hex"
  },
  "return_instruction": {
    "address": "0xXXXXXXXX",
    "opcode": "ret|retn",
    "immediate": 0
  },
  "abi_checks": {
    "esp_balanced": true,
    "callee_saved_preserved": true,
    "return_path_observed": true
  },
  "evidence_level": "OBSERVED|VERIFIED|UNKNOWN"
}
```

The return record must reference the same `call_id`; a return-only or entry-only record is incomplete for a differential claim.

### 8.5 `state.jsonl`

Each line contains a before/after pair for one call:

```json
{
  "schema": "replacement-state-1",
  "run_id": "string",
  "call_id": "string",
  "target_id": "string",
  "phase": "before|after",
  "t_rel_ns": 0,
  "globals": {
    "sCellGame": {"linked_address": "0x016B3C04", "runtime_address": "0xXXXXXXXX", "u32_bits": "0x00000000"},
    "lock": {"expression": "sCellGame+0x5158", "runtime_address": "0xXXXXXXXX", "u32_bits": "0x00000000"},
    "player_pool_index": {"expression": "sCellGame+0x411C", "runtime_address": "0xXXXXXXXX", "u32_bits": "0x00000000"},
    "serializable_ptr": {"expression": "sCellGame+0x5190", "runtime_address": "0xXXXXXXXX", "u32_bits": "0x00000000"},
    "moving": {
      "expression": "u32[sCellGame+0x5190]+0xE0",
      "status": "unreadable|null",
      "runtime_address": "0xXXXXXXXX",
      "u8": "0x00"
    }
  },
  "plane": {
    "normal_address": "0x015A7C40",
    "normal_bits": ["0x00000000", "0x00000000", "0x00000000"],
    "point_address": "0x016B3C28",
    "point_bits": ["0x00000000", "0x00000000", "0x00000000"]
  },
  "player": {
    "resolved": true,
    "address": "0xXXXXXXXX",
    "target_bits": ["0x00000000", "0x00000000", "0x00000000"],
    "orientation_bits": ["0x00000000", "0x00000000", "0x00000000", "0x00000000"],
    "current_bits": ["0x00000000", "0x00000000", "0x00000000"],
    "guard_before": "hex",
    "guard_after": "hex"
  },
  "mode_axes": {
    "app": {"value": "unknown", "source": "not_observed"},
    "simulator_strategy": {"value": "unknown", "source": "not_observed"},
    "input": {"value": "unknown", "source": "not_observed"},
    "space_scenario": {"value": "unknown", "source": "not_observed"},
    "cell_lifecycle": {"value": "unknown", "source": "not_observed"}
  },
  "semantic_status": "CONFIRMED|VERIFIED|OBSERVED|SUPPORTED|INFERRED|APPROXIMATION|UNKNOWN"
}
```

The example computed addresses are illustrative only. The artifact generator must resolve them from the captured `sCellGame` pointer and must record the actual addresses.

### 8.6 `writes.jsonl`

One line per observed write or bounded snapshot delta:

```json
{
  "schema": "replacement-write-1",
  "run_id": "string",
  "call_id": "string",
  "write_seq": 0,
  "source": "watchpoint|store_probe|snapshot_delta|page_guard|not_observed",
  "address": "0xXXXXXXXX",
  "size": 4,
  "before_bits": "0xXXXXXXXX",
  "after_bits": "0xXXXXXXXX",
  "numeric_before": 0.0,
  "numeric_after": 0.0,
  "store_rva": "0xXXXXXXXX|null",
  "store_eip": "0xXXXXXXXX|null",
  "coverage": "direct|delta_only|uncovered",
  "evidence_level": "OBSERVED|INFERRED|UNKNOWN"
}
```

The analyzer must reject a `coverage: direct` claim when the source is `snapshot_delta`.

### 8.7 `events.jsonl`, `modes.jsonl`, `objects.jsonl`, and `save.jsonl`

All use the same envelope fields: `schema`, `run_id`, `call_id` or `frame_id`, `seq`, `t_rel_ns`, `tid`, `status`, and `evidence_level`.

`events.jsonl` adds `source_rva`, `message_id`, `payload_length`, `payload_sha256`, `producer`, `consumer`, and `decode_status`.

`modes.jsonl` adds `point`, owner-qualified old/new axis values, `announcement_id`, `handler_rva`, `queue_drained`, and `cell_specific_positive_control`.

`objects.jsonl` adds `event`, `pool_index`, `object_address`, `object_identity`, `generation_status`, `pre_object_sha256`, `post_object_sha256`, and `lifecycle_source_rva`.

`save.jsonl` adds `point`, `request_id`, `serializable_ptr_before/after`, `serializable_object_sha256_before/after`, field-level whitelist deltas, `save_relative_path`, `save_size`, `save_sha256`, and `result`.

An absent event is serialized with `status: "not_observed_in_capture"`, not omitted.

### 8.8 `shots.jsonl` and `input.jsonl`

`shots.jsonl` extends the existing format with `run_id`, `mode_before`, `mode_after`, `trace_call_ids`, and `frame_id`:

```json
{
  "seq": 0,
  "path": "shots/000.png",
  "sha256": "64 lowercase hex characters",
  "width": 0,
  "height": 0,
  "window_geom": "WxH+X+Y",
  "input_event": "string",
  "mode_before": "string",
  "mode_after": "string",
  "trace_call_ids": ["string"],
  "delta_vs_prev_sha": true
}
```

`input.jsonl` retains exact command and outcome:

```json
{
  "seq": 0,
  "wall_utc": "RFC3339 string",
  "window_id": "0xXXXXXXXX",
  "command": "string",
  "allowlist": true,
  "status": "sent|rejected|failed|stopped",
  "shot_seq": 0
}
```

### 8.9 `logs.jsonl`

Each normalized and raw log chunk has:

```json
{
  "schema": "replacement-log-1",
  "run_id": "string",
  "seq": 0,
  "t_rel_ns": 0,
  "stream": "harness|tracer|wine|stdout|stderr|overlay",
  "raw_sha256": "64 lowercase hex characters",
  "normalized_sha256": "64 lowercase hex characters",
  "byte_count": 0,
  "status": "captured|truncated|unavailable"
}
```

Truncated output must be explicitly marked; it cannot be compared as a complete log.

### 8.10 `run-manifest.json`

The final manifest must be deterministic for fixed inputs and include:

- source/copy identity and before/after hashes;
- all target, caller, return, relocation, and ABI checks;
- selected attachment kind/site, installed policy order, exact patch bytes, and page/thread transaction IDs;
- every `call_id`, required artifact count, dropped/capped event count, and unpaired call count;
- direct-watch/store-probe/snapshot-delta write coverage and every uncovered field/callee;
- event/mode/object/save observation status with capture horizon and drain marker;
- screenshot/input/log hashes and normalization version;
- install, restore, page-protection/debug-state restore, and detach statuses;
- process exit status and crash/signal/fault result;
- `result: pass|fail|blocked|partial`;
- `proprietary_bytes_added: false`;
- `canonical_paths_written: []` and `canonical_kg_written: false`.

A passing result requires `result: pass`, a complete required-call set, a verified restore, no unexplained process termination, and no hidden coverage gaps. A run with `partial` coverage is a diagnostic result, not a replacement-verified result.

## 9. Blockers and promotion gates

1. **Cell reachability:** S5 recorded no Cell probe events; the game self-exited or stalled. Fix the Wine boot/registration/exit blocker and obtain a positive Cell-specific trace before installing the current target. See `docs/devlog/018-s5-cell-runtime-evidence.md:25-76`.
2. **Address conflict:** current bytes identify `0x016B3C04`; older probe prose identifies `0x116B3C04`. Resolve by current PE bytes and runtime mapping; never silently normalize the values.
3. **Flattened moving-field claim:** repository prose and `SCellGameView` flatten the write to `sCellGame+0x5270`, while current disassembly shows a one-byte store through `[sCellGame+0x5190]+0xE0`. Runtime preflight must observe the pointer and byte; no stand-in layout may be used as ABI evidence.
4. **Calling convention and return cleanup:** the current one-float, caller-cleanup, plain-`RET` contract is statically verified. Phase C must still prove the one-float shim, stack balance, callee-saved behavior, and exact entry/call-site continuation.
5. **Runtime field contract:** static offsets and access shapes are evidence, not live meaning. Resolve the pool index/player, lock, serializable pointer/byte, target, orientation, current-position, UI/camera gates, and plane point before allowing a behavior replacement to dereference them.
6. **Return oracle:** entry-only observatory data cannot validate return values, aggregate returns, hidden sret pointers, or callee-saved registers. The current target needs a proposed continuation oracle at `0x00E80840` or equivalent.
7. **Write oracle:** existing snapshots are not proof of write sites. A claim of exact memory writes requires direct watchpoints, store probes, or an explicitly labeled partial coverage result.
8. **Unhook containment:** the synthetic mechanism is not a production patcher. Range, page, protection, thread, conflict, and unhook gates are required.
9. **Tracer conflict:** the existing `INT3` tracer and the patch writer cannot own the same site bytes. Use a baseline run before patching or a non-overlapping continuation/memory oracle.
10. **Events, modes, object lifecycle, and save state:** the current corpus has static evidence but no positive original-process trace for these categories. They remain `not_observed_in_capture` until their handlers and payload boundaries are observed.

## 10. Required execution order

1. Complete Phase A and write `preflight.json` with no game launch and no process write.
2. Build and pass a separate native 32-bit ABI harness for the one-float void shim. Include the five-byte entry passthrough trampoline if entry attachment remains a candidate; call-site passthrough needs a dispatcher/original-call adapter instead.
3. Run `original`, `bypass`, and `passthrough` on a disposable positive control whose return and continuation are independently identified.
4. Resolve the Cell runtime reachability blocker and run a positive Cell trace using the existing focused-window/input safety rules.
5. Run Phase-B read-only runtime preflight and an unpatched `original` Cell baseline in a fresh disposable process, with entry, continuation, state, direct-write, event, log, screenshot/input, mode, object, save-status, and restore evidence.
6. Prefer the verified five-byte call site `0x00E8083B` for the first Spore attachment experiment. Use `0x00E5B790` only if complete entry/dynamic-caller coverage justifies the broader scope.
7. Run `bypass` in a fresh process and verify exact stack/continuation behavior plus the declared absence of original/replacement state writes.
8. Run `passthrough` in a fresh process and compare return, state, events, memory, and called-callee coverage with `original`.
9. Run `replace` only after the prior policies pass. Compare the declared observable delta, including the serializable byte at `[u32[sCellGame+0x5190]+0xE0]`, not the 64/64 decompilation-only reference.
10. Run `replace_then_original` only if the selected replacement must preserve original continuation. Keep it separate from plain `replace`.
11. Restore and verify the site, bytes, protection, debug state, threads, and disposable-file hash before detaching. Terminate only the disposable process if restoration conflicts or any crash occurs.
12. Do not promote `cell-movement-mouse-steering` beyond `replaced-approx` until positive live Cell reachability, exact ABI/return/state/write evidence, external-effect coverage, and restore evidence all pass under independent adjudication.

## 11. Repository inputs and how they constrain the design

The design was reconciled against the following committed research surfaces; contradictions were preserved rather than silently reconciled:

- **Feasibility and identity:** `knowledgegraph/research/replacement-feasibility.json`, `docs/analysis/original-exe-replacement.md`, `docs/REPLACEMENT-ABI.md`, and `docs/REPLACEMENT-DIFF.md` establish the synthetic-only mechanism, current PE identity, the 64/64 decompilation-reference boundary, and the absent real return/write oracle.
- **Architecture and semantics:** `knowledgegraph/research/semantic-blueprint.json`, `docs/analysis/architecture-decisions.md`, `docs/analysis/architecture-resolution.md`, and the Cell lifecycle reports require separate mode/state axes, separate simulation/presentation/content/serializable owners, no universal event ABI, and no promotion from static runtime-gap records.
- **Packages and future work:** `docs/analysis/reconstruction-packages.md`, `docs/analysis/reconstruction-blueprint.md`, all files under `docs/analysis/future-research/`, and the M0–M6 oracle plan require M0 boot control, M1 Cell reachability, M2 entry/return/side-effect evidence, M3 mouse attribution, and explicit runtime-validation dependencies.
- **Trace tooling:** `tools/observatory/README.md`, `observe.py`, `probe_tracer.cpp`, probe definitions, and tests establish module discovery, temporary `INT3` ownership, bounded event caps, entry-only records, and detach restoration. They do not provide return, watchpoint, or direct-write records.
- **GUI automation:** `cell_trace.sh`, `menu_walk.sh`, `agent_overlay.py`, their tests, `docs/devlog/017-s4-x11-input-feasibility.md`, and `docs/devlog/018-s5-cell-runtime-evidence.md` establish the focused-window fallback, fixed key allowlist, geometry confinement, overlay stop key, screenshot/input manifests, and the recorded negative Cell reachability.
- **Cell runtime research:** the campaign, dossiers, devlogs, `track-d-sim-cell.json`, `state-machines/cell-stage.json`, and the architecture-resolution Cell reports establish static pool/GFX/mode/persistence boundaries while leaving live parity unverified.
- **Current source boundary:** `src/replace/Replace.*`, `CellGameView.hpp`, and the differential test are current OpenSpore evidence only. The four-argument function and flattened moving field are not promoted to the original x86 ABI.

The direct Ghidra inspection used for this document is bounded to function metadata, the full `0x00E5B790` instruction listing, the five-byte call-site listing, and xrefs. It did not execute the game, persist Ghidra changes, or create a broad trace.

## 12. Current decision

The repository supports a technically feasible, safely contained future experiment, not a current Spore installation. The immediate artifact is the Phase-A static `preflight.json` contract, followed by a native ABI harness, a disposable positive control, and only then Phase-B Cell runtime identity checks. The Cell target's exact PE RVA is `0x00A5B790`; its preferred call-site RVA is `0x00A8083B`; runtime addresses must use `module_load_base + pe_rva`; and the selected five original bytes must be verified again immediately before any process-local write.

Current static disassembly narrows the target but also rejects two important existing assumptions: the preferred direct call site is a complete five-byte `E8 rel32`, and the movement observable is a one-byte store through the `cCellSerializableData` pointer, not a four-byte `sCellGame+0x5270` field. These are static corrections, not runtime field-semantic promotions.

No current result supports a claim of live Cell replacement, exact runtime field meanings, complete memory-write coverage, mode-change parity, object-lifecycle parity, or save-state parity.
