# Runtime Oracle and Replacement Research Plan

**Date:** 2026-09-24  
**Status:** `PROPOSED / DESIGN_ONLY`  
**Subject:** `SporeApp.exe` 3.1.0.22, `x86:LE:32:windows`  
**Primary target:** `Simulator::Cell::MovePlayerToMousePosition`

This document synthesizes the four research notes under `knowledgegraph/research/runtime-oracle/` into one execution and promotion plan. It does not implement the harness, launch the original, run tracing, access or modify the executable, modify `SPORE/`, or write the canonical knowledge graph.

## 1. Decision and evidence vocabulary

### 1.1 Current decision

- **[VERIFIED]** A native 32-bit five-byte `E9 rel32` entry detour is mechanically proven on a synthetic, non-PIE fixture.
- **[VERIFIED]** The current observatory can follow a bounded process lineage, discover the Wine module host, plant temporary `INT3` breakpoints, record selected entry registers, restore breakpoint bytes, and detach.
- **[HISTORICAL]** A fresh-Wine startup run recorded the expected startup prefix, and focused-window Return reached the registration UI.
- **[HISTORICAL]** All recorded original Cell runs are negative for Cell reachability. No positive original Cell call, return, memory-effect, mode, object-lifecycle, or save oracle exists.
- **[PROPOSED]** The safest Spore mechanism is a process-local, reversible call-site replacement at the verified direct call site. An entry detour is a separately gated all-entry fallback.
- **[UNKNOWN]** The current original-process boot is not reproducible; the clean-exit trigger is unknown; Cell navigation is not proven; live field meanings and most omitted callee effects are unknown.

The immediate research artifact is a static, hash-pinned target preflight. The immediate implementation candidates, in order, are a native 32-bit ABI gate, a read-only runtime identity preflight, and a disposable positive control. The Cell target is not yet authorized for replacement installation.

### 1.2 Labels used in this plan

| Label | Meaning |
|---|---|
| **VERIFIED** | Established by current source/tooling inspection, a bounded static decode, or a committed static identity record. It does not imply a fresh runtime result. |
| **HISTORICAL** | Recorded by an earlier run, devlog, example JSONL, or manifest and not reproduced while preparing this plan. |
| **PROPOSED** | Future design, experiment, gate, schema, or mechanism. It is not evidence of original behavior. |
| **UNKNOWN** | No adequate direct evidence exists. Absence from a static scan or zero-event run is not a universal negative. |
| **SUPPORTED / INFERRED / APPROXIMATION** | Intermediate evidence levels retained where the repository already uses them. Decompilation is evidence, not truth. |

### 1.3 Evidence precedence

A future conclusion is ranked by:

1. raw JSONL and immutable run manifests;
2. committed hashes, bounded records, and trace summaries;
3. committed decompilation captures and byte-verified static records;
4. prose, status files, and generated OpenSpore fixtures.

A screenshot, clean exit, boot stall, zero-event trace, generic frame callback, or host-generated 64/64 result cannot outrank direct paired runtime evidence.

## 2. Exact target identity and address rules

### 2.1 Immutable candidate identity

The following is a candidate identity contract, not permission to launch or patch.

| Field | Required candidate value | Status |
|---|---|---|
| Artifact | `SPORE/SporeBin/SporeApp.exe` | **VERIFIED** committed identity |
| Version | `3.1.0.22` | **VERIFIED** committed identity |
| SHA-256 | `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e` | **VERIFIED** committed identity; not rehashed for this document |
| Architecture | x86 little-endian, PE32/i386, `x86:LE:32:windows` | **VERIFIED** committed identity |
| Preferred image base | `0x00400000` | **VERIFIED** static |
| Symbol | `Simulator::Cell::MovePlayerToMousePosition` | **CONFIRMED** SDK name |
| Linked VA | `0x00E5B790` | **CONFIRMED/VERIFIED** static |
| True PE RVA | `0x00A5B790` | **VERIFIED** static |
| File offset | `0x00A5AB90` | **VERIFIED** static |
| Section | `.text` | **VERIFIED** static |
| Entry bytes | `a1 04 3c 6b 01` | **VERIFIED** static |
| Entry decode | `mov eax, dword ptr [0x016B3C04]` | **VERIFIED** static |
| Return | `void` | **CONFIRMED** SDK; return-path behavior verified statically |
| Parameter | one `float deltaTime` at `[ESP+4]` | **CONFIRMED** SDK; stack access verified statically |
| Convention | caller cleanup / cdecl behavior | **VERIFIED STATIC**, not independently observed live |
| Terminal return | plain `RET` at linked VA `0x00E5BA01`, no `RET N` | **VERIFIED** static |
| Direct call site | linked VA `0x00E8083B` | **VERIFIED** in the bounded Ghidra snapshot; not live-verified |
| Call-site bytes | `e8 50 af fd ff` | **VERIFIED** static |
| Call-site PE RVA | `0x00A8083B` | **VERIFIED** arithmetic |
| Call-site file offset | `0x00A7FC3B` | **VERIFIED** `.text` section arithmetic |
| Call continuation | linked VA `0x00E80840` | **VERIFIED** static |
| Known direct caller | `FUN_00E806B0` | **VERIFIED** in current Ghidra graph; complete dynamic caller set is **UNKNOWN** |
| Preferred attachment | call-site replacement at `0x00E8083B` | **PROPOSED**, subject to all gates |
| Fallback attachment | entry detour at `0x00E5B790` | **PROPOSED**, broader scope and separate approval |
| Entrypoint relocation class | first five bytes form one complete relocation-free instruction | **VERIFIED** static |

The existing `src/replace/Replace.cpp` function is not this target ABI. It takes four host arguments and models a flattened view. It must not be used as the installed x86 shim.

### 2.2 Address formulas

Use these formulas without renaming fields:

```text
preferred linked VA = pe_image_base + pe_rva
pe_rva              = preferred linked VA - pe_image_base
runtime address     = actual module load base + pe_rva
linked-to-runtime    = runtime address = actual load base + (linked VA - pe_image_base)
file offset          = pe_rva - section_rva + section_raw_offset
```

For this build's `.text` section, the linked VA to file-offset delta happens to be `0x000400C00`; the general rule must still use the parsed PE section table. Never subtract the image base from a file offset.

The current observatory's probe field named `rva` is not a true PE RVA. Its implementation computes:

```text
module_base + (probe["rva"] - image_base)
```

Therefore the new manifest must use separate fields:

- `pe_rva: 0x00A5B790` for replacement and runtime resolution;
- `tracer_probe_rva: 0x00E5B790` only when feeding the legacy tracer;
- `file_offset: 0x00A5AB90` for static bytes;
- `linked_va: 0x00E5B790` for cross-reference and snapshot identity.

### 2.3 Static address and layout conflicts that must fail preflight

- **[VERIFIED]** The current target bytes decode absolute global operand `0x016B3C04`.
- **[VERIFIED]** Older prose and probe material claim `0x116B3C04`; those values are not equivalent and must not be normalized silently.
- **[VERIFIED]** Direct disassembly shows the moving write is the byte at `u32[sCellGame+0x5190]+0xE0`, not a four-byte word at `sCellGame+0x5270`.
- **[UNKNOWN]** The runtime meaning of that byte, most `sCellGame` fields, player fields, and most UI/camera gates remains inferred until directly observed.
- **[VERIFIED]** The movement-plane normal is statically `{0,0,1}`; the per-world plane point and most field meanings are not runtime-verified.

The safe treatment is to make `0x016B3C04` the candidate value encoded by the committed bytes, then require Phase A and Phase B to rederive it independently. Any mismatch blocks the run; it does not authorize an alias.

### 2.4 Static direct-write anchors

These are preferred linked VAs from the bounded direct disassembly and are not yet live observations:

| Observation | Linked VA | Evidence |
|---|---:|---|
| Player target stores | `0x00E5B97A`, `0x00E5B97D`, `0x00E5B980` | **VERIFIED** static store instructions; field role supported/inferred |
| Serializable moving byte | `0x00E5B98E` | **VERIFIED** static one-byte store; semantic role inferred |
| Player orientation stores | `0x00E5B9E4`, `0x00E5B9EA`, `0x00E5B9F0`, `0x00E5B9F6` | **VERIFIED** static store instructions; layout/role inferred |

Direct store evidence and watchpoint evidence answer different questions; the future oracle must not conflate them.

## 3. Current harness capability

| Surface | Current capability | Boundary | Status |
|---|---|---|---|
| `tools/observatory/probe_tracer.cpp` | 32-bit ptrace/INT3 tracer; fork/exec and clone/fork/vfork lineage; reparented Wine module-host discovery; bounded breakpoints, event caps, duration, signal interruption, byte restore, detach | Entry-only; no stack/EFLAGS contract in emitted events, no return pairing, no post-state snapshots, no watchpoints, no injected replacement | **VERIFIED** current source |
| Native tracer fixture | Produced 1,801 capped events on `m32target` | Validates tracer mechanics only; not Spore behavior | **HISTORICAL** |
| `main_menu.json` | Seven startup/control probes | Historical startup only; current Cell relevance is indirect | **VERIFIED** fixture; **HISTORICAL** result |
| `cell_movement.json` | Twelve byte-checked/spot-checked linked-VA probes, including eleven non-control candidates and one bootstrap control | No positive non-control original Cell event; broad classifier includes generic helpers | **VERIFIED** fixture; **HISTORICAL** negative |
| `menu_transition.json` | Eight UI/message/resource/frame probes | Defined and spot-checked, but no committed positive original run | **VERIFIED** fixture; no runtime result |
| `observe.py` | Acquires the machine lock and runs raw startup tracing through `probe_tracer` | Direct invocation is not approval-equivalent to MCP; does not drive the GUI path | **VERIFIED** current source |
| MCP `trace_run` | Checks approval, scenario, tracer, Wine, display, binary, lock, duration, timeout, and output path; then calls `observe.py` | Raw startup trace only; no `cell_trace.sh`; does not unify GUI and trace orchestration | **VERIFIED** current source |
| `cell_trace.sh` | Approval gate, focused-window navigation allowlist, screenshots, overlay, renderer marker, fixed geometry, and manifest helpers | Not a complete supervisor; historical Cell result is negative | **VERIFIED** current source; **HISTORICAL** runtime negative |
| `menu_walk.sh` | Approval-gated, lock-exec path, fixed keys, dry-run, screenshots/input manifests | Older `--window` input path was historically inconclusive and differs from the focused-window Cell path | **VERIFIED** current source |
| `analyze.py` / MCP analysis | Deterministic JSONL summaries and hash-pinned normalized analysis | Summary is not a semantic oracle; shallow status does not recurse into Cell artifacts | **VERIFIED** current source |
| `tools/replace/synthetic/` | Five-byte `E9 rel32` write/readback on a native 32-bit non-PIE target | Synthetic only; no production writer, unhook, relocation engine, page transaction, Windows/Wine page protection, or thread quiescence | **VERIFIED** synthetic only |
| Host Cell tests | Deterministic OpenSpore simulation, host rendering, lifecycle, and 64/64 decompilation-reference differential | No original ABI, field, call, return, or external-effect parity | **VERIFIED** host behavior; not original evidence |

The automation audit reports the required GUI/runtime tools installed and 72 focused Python contract tests passing on 2026-09-24. Those tests cover dry runs and pure helpers, not a real Cell process.

## 4. Missing technical pieces

The following capabilities do not exist as a complete, reusable system:

1. **Static identity validator:** hash/size/PE metadata checks, section-map RVA/file-offset derivation, exact-byte decode, call-site alignment, caller/return records, relocation class, and fail-closed manifest.
2. **Native one-float ABI gate:** a separate x86-32 `void(float)` shim and dispatcher, exact stack/return/callee-saved tests, finite and exceptional float cases, reentrancy, multithreading, fault injection, repeated install/restore, page-boundary rejection, and signed-`rel32` rejection.
3. **Dedicated return/continuation oracle:** pairing at `0x00E80840` for call-site scope and a separately proven all-entry return strategy for entry scope.
4. **State oracle:** owner-qualified reads of the whitelisted globals, pool index and resolved object, movement fields, serializable pointer/byte, plane, camera/UI gates, and guard windows.
5. **Write oracle:** hardware watchpoints, selected store probes, guard windows, and explicit coverage gaps. Snapshot deltas must not be reported as exact write sites.
6. **External-effect oracle:** bounded event/message order, separate mode axes, object lifecycle, save status, exact input/shot correlation, and bounded logs.
7. **Process-local transaction controller:** one writer/owner lock, complete thread suspension, page/protection transaction, signed-range and page checks, exact original-byte ownership, no unknown-writer overwrite, and mandatory restore.
8. **Entry trampoline:** relocation of the exact first instruction to the continuation, tested independently; required only for entry passthrough.
9. **Unified process supervisor:** child monitoring, total and per-step deadlines, output-open-before-breakpoints, reliable early-exit classification, atomic machine lock, overlay readiness, emergency stop, and one always-written manifest path.
10. **Human profile handoff:** a legitimate, non-secret route through registration in a disposable profile without logging credentials or adding unrestricted typing.
11. **Independent adjudication:** reproducible analyzer plus a reviewer distinct from the implementer, followed by human-approved status promotion.

## 5. Safest replacement mechanism

### 5.1 Chosen mechanism

**[PROPOSED] Use a process-local call-site replacement at `0x00E8083B` first.**

The controller launches a byte-identical disposable executable copy in a disposable Wine prefix/profile, discovers and verifies the target module, suspends affected threads, verifies the exact original call bytes, writes a five-byte `E8 rel32` to a 32-bit dispatcher, reads back the result, restores page protection, and resumes the process. The on-disk copy remains unchanged. Every non-baseline policy starts in a fresh disposable process or demonstrably equivalent reset state.

This mechanism is preferred because:

- the call and continuation are statically identified;
- the overwritten instruction is a complete five-byte `E8 rel32`;
- the caller's stack frame already matches the original `void(float)` ABI;
- passthrough can call the untouched original without relocating its first instruction;
- the scope is limited to the known direct caller and is easier to bound than entry replacement;
- restoration has a byte-exact local seam.

It does **not** prove or cover unobserved dynamic callers.

### 5.2 Rejected or deferred alternatives

| Mechanism | Disposition | Reason |
|---|---|---|
| PE import replacement | Rejected for this target | The engine is statically linked; no replaceable engine import boundary. |
| Vtable replacement | Deferred | No live receiver/vptr/slot proof; unnecessary for a global free function; original has no MSVC RTTI. |
| Function-pointer replacement | Deferred | No writer, reader, publication, lifetime, or synchronization proof. |
| Synthetic same-page RWX constructor | Rejected for Spore | Proves a seam only; lacks Windows/Wine protection handling, unhook, range, page, and thread safety. |
| Entry detour | Fallback only | Wider all-entry scope; passthrough needs a relocation-correct trampoline; all return/caller/thread behavior must be separately proven. |
| File-backed executable patch | Prohibited in this program | Process-local containment is safer and sufficient for the experiment. |

### 5.3 Ownership and state rules

- The patcher and legacy `INT3` tracer must never own the same bytes concurrently.
- One reviewed controller owns the selected site, original bytes, page protection, debug/watchpoint state, and restore transaction.
- No target memory is written before static preflight, native ABI gate, runtime identity preflight, positive control, and explicit approval all pass.
- `RWX` is not an acceptable steady state. Page execute permission is writable only for the bounded transaction and then restored.
- The process is disposable. A restore conflict or unknown writer terminates the process and fails the experiment.
- Runtime artifacts and the disposable copy remain outside the repository, `SPORE/`, `tools/observatory/out/`, and the canonical KG.

## 6. Phased execution order

The order is strict. A skipped required check is `fail` or `blocked`, never implicitly `pass`.

### Phase 1 — Static preflight, no launch and no process write

**[PROPOSED]**

1. Read the immutable candidate file and verify SHA-256, size, PE machine, preferred base, timestamp/checksum metadata, and section table against the target manifest.
2. Derive the target and call-site PE RVAs and file offsets from the section table.
3. Read exact target, guard, call-site, continuation, and terminal-return bytes.
4. Independently decode the entry instruction and require `mov eax,[0x016B3C04]`; reject an alias or mismatch.
5. Verify the call site is instruction-aligned, exactly `E8 rel32`, decodes to the target, and continues at `0x00E80840`.
6. Record the bounded direct xref set without claiming it is the complete dynamic caller set.
7. Enumerate direct writes, terminal instructions, called callees, page boundaries, and relocation class.
8. Produce `target-manifest.json` and `preflight.json` with every check and evidence level.

**Gate:** all identity, mapping, byte, decode, ABI-static, and scope checks pass. This phase does not authorize a launch or any process-memory operation.

### Phase 2 — Native 32-bit ABI gate, controlled fixture only

**[PROPOSED]**

Build a dedicated one-float `void(float)` shim and dispatcher. The current four-argument host replacement is not reused as the original ABI shim. Test:

- finite values, zero, subnormal, positive/negative infinity, quiet/signaling NaNs, and sign/payload preservation;
- call-site `E8` and entry `E9` paths;
- plain `RET`, exact continuation, and balanced `ESP`;
- preservation of `EBX`, `EBP`, `ESI`, and `EDI`;
- nested/reentrant and multithreaded calls with per-thread state;
- bypass, passthrough, replace, and optional `replace_then_original` marker order;
- fault injection before and after state transitions;
- repeated install/restore with exact bytes and protection;
- rejection of page-boundary and out-of-`rel32` destinations;
- no exceptions, CRT dependency, unbounded allocation, or hidden global one-shot state in the hot path.

**Gate:** every ABI row passes. A behavioral fixture pass cannot compensate for an ABI failure. This is not Spore evidence.

### Phase 3 — Read-only runtime identity preflight

**[PROPOSED]** Run only in an approved disposable process after Phases 1 and 2 pass.

1. Record PID/lineage, Wine generation, host path, copy hash, module path, header mapping, anonymous executable-code mapping, actual load base, and mapped bytes.
2. Resolve both target and call site as `load_base + pe_rva` and prove they are in the expected mapping.
3. Read the exact site/guard windows and compare the relocation-free bytes with the file. Reject `INT3`, existing detours, and unknown writers.
4. Record page boundaries/protection and intended write scope without changing code or gameplay state.
5. Read only the approved oracle whitelist and record null/unreadable/guard outcomes.
6. Record any existing debugger/watchpoint owners.
7. Require a disposable process, byte-identical copy, isolated prefix/profile/save directory, explicit write authorization, and declared end condition.

**Gate:** module and bytes match, no writer conflict exists, and all addresses are attributable. `not_observed` is not an automatic pass.

### Phase 4 — Positive control in a fresh disposable original process

**[PROPOSED] Candidate:** `App::IAppSystem::Get`, linked VA `0x0067DCC0`, PE RVA `0x0027DCC0`, `.text` file offset `0x0027D0C0`, bytes `a1 90 d8 5f 01 c3`.

The control requires its own caller/continuation/module preflight. Run at least:

1. `original` with entry and return observation;
2. `bypass` with replacement marker exactly once and original marker zero;
3. `passthrough` with original marker exactly once and preserved return evidence;
4. optionally `replace` to validate a behaviorless return policy.

The positive control validates attach ownership, return observation, and restore. It says nothing about Cell behavior. The native Phase 2 fixture remains the authority for the one-float ABI.

### Phase 5 — Original Cell baseline

**[PROPOSED]**

1. First establish Cell-specific reachability with an approved, human-watched run. Require a Cell lifecycle/control event and target-path evidence; exclude `FUN_0069B600` as a Cell marker.
2. Use a fresh disposable process/profile and the focused-window input discipline. Do not type letters/digits or log credentials.
3. Run unpatched `original` with dedicated entry, return/continuation, state, direct-write, event, mode, object, save-status, log, input, screenshot, and process-lifecycle capture.
4. Pair every selected call by thread, call site, stack return address, sequence, and monotonic time.
5. Preserve the baseline if coverage is complete. If it is entry-only, partial, unreachable, or early-exiting, keep it negative/partial and do not proceed to behavior replacement.

**Gate:** positive target calls, paired returns, attributable state, declared write coverage, external-effect horizon, and a complete unpatched manifest.

### Phase 6 — Call-site first

**[PROPOSED]**

Use the verified direct call site only after the baseline proves that call path is live.

1. Revalidate identity and original bytes while all affected threads are stopped.
2. Install exactly one five-byte `E8 rel32`; no unrelated byte changes.
3. Read back the patch, protection, and thread snapshot before resume.
4. Run `bypass` in a fresh process.
5. Run `passthrough` in a fresh process and compare against `original`.
6. Run `replace` only after bypass and passthrough pass.
7. Run `replace_then_original` only if a stateful policy genuinely requires it.

**Gate:** ABI, call scope, return path, declared state delta, external effects, and restore all pass independently.

### Phase 7 — Entry fallback

**[PROPOSED / CONDITIONAL]**

Do not use entry replacement to rescue missing UI navigation or a nonexistent target call. Enter this phase only if the call-site program is mechanically sound but the research requirement is all-entry behavior.

1. Re-run Phase 2's entry-specific ABI and trampoline matrix.
2. Prove all relevant incoming paths reach the chosen entry, and prove all return/caller/thread continuations are compatible with the dispatcher.
3. Install `E9 rel32` at `0x00E5B790`, relocatable only as a reviewed first instruction if passthrough is enabled.
4. Repeat the policy sequence in fresh processes and compare against the unpatched all-entry baseline.
5. Keep call-site and entry results separate; do not merge coverage.

**Gate:** the broader claim is justified and all entry/return/trampoline/restore requirements pass.

### Phase 8 — Policies

**[PROPOSED]** Every policy starts from fresh state.

| Policy | Attachment behavior | Required original execution |
|---|---|---:|
| `original` | No patch | Exactly as baseline |
| `bypass` | Dispatcher returns; original not called | 0 |
| `passthrough` | Dispatcher calls untouched original | Exactly 1 |
| `replace` | Replacement returns | 0 |
| `replace_then_original` | Replacement, then original, then return | Exactly 1, in declared order |

For call-site passthrough, call the untouched target through an explicit original-call adapter. For entry passthrough, use the independently tested trampoline. A normal C++ wrapper must not silently define ABI or policy behavior.

### Phase 9 — Restore, detach, and teardown

**[PROPOSED] Mandatory for every write-bearing run**

1. Stop the policy and wait for its calls to quiesce.
2. Suspend all affected threads and verify no thread has `EIP` in the dispatcher, trampoline, overwritten bytes, or pending site breakpoint.
3. Read the current site. Restore only if it exactly equals the installer-owned bytes.
4. On mismatch, do not overwrite; terminate the disposable process and fail the run.
5. Restore the exact original five bytes and original page protection.
6. Read back bytes, guard windows, and page protection.
7. Verify no redirect remains; remove harness-owned debug/watchpoint state; detach.
8. Record `restored`, `restore_readback`, `page_protection_readback`, `debug_state_restored`, and `detach` separately.
9. Recompute the disposable executable hash and verify no canonical path, profile, save, or KG file changed.
10. Release the machine lock and verify no stale game/Wine process remains.

Restoration is an experiment outcome, not best-effort cleanup. A failed restore makes the whole experiment fail.

## 7. Deterministic observable model

### 7.1 Canonical observation vector

Every selected call is represented by one `call_id`, one `policy`, and one coverage-complete vector:

```text
O = {
  target_identity,
  attachment_transaction,
  entry_frame,
  return_frame,
  state_before,
  state_after,
  direct_writes,
  guard_memory,
  called_callees,
  events,
  logs,
  screenshots,
  input,
  mode_axes,
  object_lifecycle,
  save_state,
  process_lifecycle,
  restore_evidence
}
```

Each field carries `value`, `raw_bits`, `source`, `coverage`, `evidence_level`, and `comparison_rule`.

### 7.2 Entry and return

Capture `EIP`, `ESP`, `EBP`, `EAX`, `EBX`, `ECX`, `EDX`, `ESI`, `EDI`, and `EFLAGS` at entry and return/continuation. Capture:

- `[ESP]`, `[ESP+4]`, and a bounded caller-frame guard;
- the float as exact `u32_bits` plus an optional decoded value;
- caller, return address, target identity, thread, monotonic time, call sequence;
- actual `RET` versus `RET N` and immediate cleanup;
- exact `ESP` delta and callee-saved preservation;
- attachment, policy transition, original-execution count, and trampoline entry.

The current target is `void`; `EAX`, `ECX`, `EDX`, and flags are diagnostic, not typed return values.

### 7.3 State whitelist

Resolve every static linked address through the actual module load base. Compute object fields only from safely resolved runtime pointers.

| State | Static source | Status |
|---|---|---|
| `sCellGame` global slot | linked `0x016B3C04`, RVA `0x012B3C04`, 4 bytes | Address **VERIFIED**; semantic name confirmed |
| Lock field | `sCellGame+0x5158`, 4 bytes | Offset/access **VERIFIED** static; meaning inferred |
| Player pool index | `sCellGame+0x411C`, 4 bytes | Offset/use **VERIFIED** static; lookup semantics supported/inferred |
| Serializable pointer | `sCellGame+0x5190`, 4 bytes | Pointer slot supported; candidate type inferred |
| Moving byte | `u32[sCellGame+0x5190]+0xE0`, 1 byte | Physical write **VERIFIED** static; meaning inferred |
| Caller gates | `sCellGame+0x515C`, `+0x51E0` | Access **VERIFIED** static; meanings inferred |
| Plane normal | linked `0x015A7C40..0x015A7C4C` | Address/value **VERIFIED** static; capture live per call |
| Plane point | linked `0x016B3C28..0x016B3C34` | Address **VERIFIED** static; per-world value unknown |
| Cell UI pointer/gates | linked `0x016B3C0C`, then `sCellUI+0x24/+0x26` if valid | Access **VERIFIED** static; meaning inferred |
| Player target | resolved player `+0x08..+0x10`, 12 bytes | Stores **VERIFIED** static; role inferred |
| Player orientation | resolved player `+0x14..+0x20`, 16 bytes | Stores **VERIFIED** static; layout/meaning inferred |
| Player current position | resolved player `+0x4C..+0x54`, 12 bytes | Reads **VERIFIED** static; role inferred |
| Object identity | pool index, object address, bounded hash, generation status | Generation/reuse semantics unknown |
| Guard ranges | bounded windows before/after each candidate | Detect adjacent change; do not infer the writer |

If `sCellGame`, the serializable pointer, or the resolved player changes, emit an identity/lifecycle transition and do not compare bytes from the old owner to bytes from the new owner as one field. Null or unsafe pointers are recorded as `unreadable`; they are not normalized away.

### 7.4 Comparison rules

| Observable | Required comparison | Disallowed shortcut |
|---|---|---|
| Return/control | Exact register bits, stack delta, continuation, and `RET` form | “Returned without crashing” |
| Integer/pointer | Exact bits plus separately decoded meaning | Normalizing pointer reuse away |
| Float/vector/quaternion | Raw-bit equality first; numeric delta second; retain NaN payload/sign and `-0.0` | Tolerance-only equality |
| State | Exact owner-qualified before/after bytes for the same address | Snapshot from different pool objects |
| Memory write | Exact address/width/source PC or labeled watchpoint/store evidence | Calling a snapshot delta an exact store |
| Event | Ordered sequence, source, ID, and payload hash within a declared horizon | Omitting missing events |
| Mode/lifecycle | Ordered per-owner-axis transitions | One global mode enum from a screenshot |
| Object identity | Pool index + address + bounded hash + generation status | Raw pointer as durable identity |
| Save state | Exact file bytes/hash when parity is required, or exact whitelisted fields with unknowns explicit | Calling in-memory state a save |
| Logs | Raw and narrowly normalized hashes | Normalizing addresses, IDs, or values |
| Screenshot | Exact PNG hash and metadata | Image similarity as call/state evidence |

Cross-run pointer addresses and timing need identity-aware normalization; within a call, stack/register/continuation and declared state deltas remain exact. A policy can pass mechanical ABI checks while failing declared state parity or external-effect parity.

### 7.5 Write and call-local coverage

Use only bounded observation for one selected call or small call window; no whole-process instruction trace is authorized.

- A watchpoint proves an access at an address/width.
- A store probe proves execution at a known store and can pair before/after bytes.
- A snapshot delta proves only that values changed between observations.
- A guard page proves a bounded protection event, not the exact store.
- `not_observed` and `partial_write_coverage` are explicit outcomes, never pass.

A passing replacement claim must cover the selected direct target/orientation/moving stores and the declared omitted callees. If a write is not covered, the result is partial.

### 7.6 Events, modes, objects, and save state

- Declare a capture start, fixed frame/time horizon, and queue-drain/end marker.
- Keep App transport, UTFWin, editor/animation, Cell interaction, persistence, and domain event families separate.
- Record message source, ID, payload length/hash, producer/consumer confidence, and `observed`, `not_observed_in_capture`, or `static_only` status.
- Record separate App, Simulator strategy, input, Space/scenario, and Cell lifecycle axes; do not collapse them.
- Record object create/attach/detach/rebuild/release/destroy/reuse with owner identity and source.
- Record save request, serializer, file open/write/close/replace, and explicit save-state candidate only in an isolated profile. A missing file within a capture is not proof of no save.

### 7.7 GUI and logs

- Record exact focused-window identity, geometry, input command, and allowlist result.
- Screenshot metadata includes PNG hash, dimensions, geometry, input reference, and nearest trace call/frame from a shared monotonic clock.
- `trace_t_nearest` must not be fabricated from a second wall-clock read.
- Logs retain raw hashes and a versioned normalized hash that may replace only run IDs, PIDs, timestamps, and temporary paths—not addresses, message IDs, return values, or memory values.

## 8. Evidence and promotion gates

### 8.1 Cross-phase contracts

| Contract | Required pass condition |
|---|---|
| `C-PROV` | Binary/copy hash, probe/harness hashes, address convention, Wine generation, display/compositor, window/geometry, tool versions, raw paths, counts, exact outcome |
| `C-NEG` | Zero events, clean exit, stall, renderer failure, and unreachable target remain distinct; no screenshot/generic frame promotion |
| `C-BOOT` | Fresh generation, module host, startup controls, renderer marker where rendered, and explicit process outcome |
| `C-ENTRY` | Cell-specific positive control and target-path evidence after entry; no generic helper marker |
| `C-ORDER` | Claimed lifecycle/input/event order is directly timestamped with stable or explained identities |
| `C-SIDE` | Entry, return, before/after state, direct writes, and omitted callees are separately observed |
| `C-STATE` | Pool index, resolved entity, serializable state, gameplay state, GFX/UI handles, and transient state are not conflated |
| `C-ABI` | Exact target/stack/return/callee-saved contract and real pool lookup are observed; host stand-ins remain excluded |
| `C-EVENT` | Input/message/handler/resource order is attributable within a declared horizon |
| `C-BOUNDARY` | Gameplay, resource, GFX, UI, and renderer observations remain separate |
| `C-REPLACEMENT` | Live hash-pinned original/replacement comparison, complete required coverage, restore, independent adjudication, and human approval |

### 8.2 Layered result

Every differential is reported in three non-substitutable layers:

1. **Mechanical:** identity, call pairing, ABI, thread/stack, restore, and process lifecycle.
2. **Declared delta:** only fields the policy is authorized to alter.
3. **External effect:** events, logs, screenshots, input, mode, object lifecycle, and save state.

A run passes only if every layer required by the claim passes. Partial coverage is a diagnostic result.

### 8.3 Promotion to `replaced-verified`

The current `replaced-approx` status remains unchanged unless all of the following are true:

1. Phase A static identity and exact target mapping pass.
2. Phase C native one-float ABI and mechanism-containment matrix passes.
3. Phase B live module/bytes/address preflight passes in a hash-identical disposable process.
4. A disposable positive control passes attach, return, policy, and restore gates.
5. A positive original Cell baseline reaches the target and records paired entry/return evidence.
6. The selected call-site or entry policy has complete required ABI/state/write/external-effect coverage.
7. The experiment restores exact bytes, protection, debug state, and process ownership, with no canonical file changes.
8. A separate adjudicator reproduces the comparison from immutable artifacts.
9. A human approves promotion through the existing status workflow.
10. The status record points to the exact run manifest, target manifest, analyzer output, adjudication, and negative/partial coverage disclosures.

No decompilation-only 64/64 host result, screenshot, clean exit, or positive control can satisfy these gates.

## 9. Top-20 experiment map

This is the proposed research-value queue, not an authorization or execution-order list. Safety prerequisites, especially Phases 1–4, remain mandatory before any Cell write experiment.

| Rank | ID | Phase | Question / value | Minimum pass or bounded negative |
|---:|---|---|---|---|
| 1 | RO-01 / M0 | Boot | Can the original boot reproducibly and attach under pinned conditions? | Startup controls, module host, renderer marker, and process outcome; otherwise classify boot/registration/renderer negative |
| 2 | RO-02 | Static | Does the exact target/call-site/address manifest hold? | All Phase A checks pass; address conflicts fail closed |
| 3 | RO-03 | Native ABI | Can the one-float dispatcher preserve exact x86-32 ABI and restore safely? | Complete ABI matrix passes on controlled fixture |
| 4 | RO-04 | Runtime identity | Do file, mapped module, load base, bytes, and whitelist agree? | Phase B passes with no writer conflict |
| 5 | RO-05 | Positive control | Can attach, return, policy order, and restore be observed without Cell semantics? | `original`, `bypass`, and `passthrough` pass on independently pinned control |
| 6 | RO-06 / M1 | Cell reachability | Does the original reach Cell and the target path? | Cell-specific control plus target-path event; otherwise bounded reachability negative |
| 7 | RO-07 / M2 | Cell baseline | What are the target's real ABI, guards, state, writes, and omitted callees? | Paired call/return and declared state/write coverage; otherwise partial |
| 8 | RO-08 | Call-site policy | Does call-site `bypass` return correctly and suppress original execution? | Marker order, stack, continuation, and absence of original are exact |
| 9 | RO-09 | Call-site policy | Does call-site `passthrough` preserve original behavior and return? | Original executes once; ABI/state/external effects compare with baseline |
| 10 | RO-10 | Call-site policy | What declared behavior delta does `replace` cause? | Only authorized observables change; all other required effects match |
| 11 | RO-11 | Call-site policy | Is `replace_then_original` needed and ordered? | Optional policy only; exact replacement → original → continuation order |
| 12 | RO-12 | Entry fallback | Can all-entry scope and the five-byte trampoline be proven? | Separate entry ABI/return/caller/trampoline matrix passes; otherwise remain call-site-only |
| 13 | RO-13 / C4+C6 | Cell lifecycle | Are pool identity, GFX/UI, content, and serializable state separate in live order? | Correlated identity and lifecycle timeline, or explicit unknown/negative |
| 14 | RO-14 / M3 | Input causality | Do fixed pointer waypoints cause camera-ray and movement changes? | Input, `OnMouseMove`, camera, target call, and state changes correlate |
| 15 | RO-15 / C3+C10 | Event/scheduler | Is App transport separate from mode/domain events and deferred scheduling? | Producer/consumer order and capture horizon are observed; no universal ABI inference |
| 16 | RO-16 / C1 | Shared roots | Are noun/star root slots aliases, phase ports, or independently rebound? | Equality/publication/teardown timeline across a real transition; otherwise blocker remains open |
| 17 | RO-17 / C2 | Forwarded state | Who first writes `DAT_0167eaec` / `receiver+0x20`, and is it scalar or owner-backed? | Direct writer/consumer/lifetime evidence; a single value is insufficient |
| 18 | RO-18 / C5 | Receiver-typed state | Is `receiver+0x54` stable only for noun-layout receivers? | Receiver provenance and replacement/lifetime order across naturally reachable receivers |
| 19 | RO-19 / C7+C8 | Persistence | What object/reference graph and mode-handoff boundary are actually used? | Explicit disposable save/load and teardown timeline; no byte-compatibility claim without outer format evidence |
| 20 | RO-20 / C9 | Space/empire | How do lookup, cache, roots, and context owners behave over selection/teardown? | Direct lookup/cache/context identity transitions, or a bounded Space reachability negative |

`M5` menu/resource transition and `M6` renderer-boundary characterization remain lower-priority follow-ons after the target oracle and architecture-changing blockers above. They must use bounded probes and must not be confused with Cell or gameplay evidence.

## 10. Unattended versus human interaction

| Activity | Classification | Rule |
|---|---|---|
| PE parse, target manifest, static address/byte checks | **Unattended safe** | No game or process access. |
| Native 32-bit ABI, range/page/fault tests | **Unattended safe** | Controlled fixture only. |
| Schema validation, deterministic analysis, dry runs | **Unattended safe** | No original launch. |
| Acquire machine lock and prepare a run directory | **Unattended after authorization** | Atomic inherited lock; fail if held. |
| Launch original under Wine | **Human-approved, machine-executed** | Existing trusted approval gate; fresh generation; human-visible on shared display. |
| Fixed navigation/input | **Human-approved and supervised** | Focused window, pinned geometry, allowlist, no typing/secrets, emergency stop ready. |
| Process-memory instrumentation or replacement | **Explicit human-authorized phase** | Only after named gate passes; fresh disposable process. |
| Registration/profile preparation | **Human interaction required** | Prepare an isolated profile without logging secrets; do not automate unrestricted text. |
| Physical emergency-stop verification | **Human required** | Synthetic injection is not equivalent. |
| Diagnosing an unexpected exit/stall | **Human research judgment** | Agent may collect bounded logs but must not invent the cause or retry broadly. |
| Adjudication | **Independent human/agent review** | Reviewer differs from implementer. |
| Status promotion | **Human-approved gated write** | Existing status workflow only; never from this plan. |

A worker may execute a pre-authorized bounded workflow, but it may not self-approve the original launch, expansion of input, patch authorization, or status promotion.

## 11. Current automation blockers

| Blocker | Current state | Required gate before future Cell replacement work |
|---|---|---|
| Boot stability | **HISTORICAL:** one renderer/menu run self-exited; two runs had no window; exact cause **UNKNOWN** | One bounded no-input M0 diagnosis that records actual process lifecycle, not another click loop |
| Registration/profile | **HISTORICAL:** validation requires email/name/password; current allowlist cannot type them | Human-prepared disposable profile or separately approved non-secret state; no credential logging |
| Cell reachability | **VERIFIED/HISTORICAL:** no non-control Cell probe has fired | Positive Cell-specific control and target-path event |
| Entry-only tracer | **VERIFIED:** no call/return pairing or post-state | Dedicated continuation/state oracle |
| Write coverage | **VERIFIED:** no exact watch/store oracle | Required direct writes and omitted callees covered or partial result |
| Positive control | **UNKNOWN/not implemented as replacement harness** | Independently preflighted control passes before Cell write phase |
| Spore writer/unhook | **UNKNOWN/not implemented** | Thread, page, range, byte-owner, restore, and detach transaction implemented and tested |
| Cell process supervision | **VERIFIED:** tracer is backgrounded and not monitored during walk; shell can report `completed` after early exit | Supervise every child and classify exit/signal/time independently |
| Manifest completeness | **VERIFIED:** several failure exits write no manifest; parse errors can appear as zero events | One cleanup path always writes a manifest; malformed JSONL fails distinctly |
| Tracer coverage | **VERIFIED:** inactive probes do not fail; zero-active traces can exit 0; dropped counts are not JSONL; output opens after breakpoints | Open output first, require expected active probes, emit skipped/retired/dropped counts, distinguish early exit |
| Machine lock | **VERIFIED:** `cell_trace.sh` uses check-then-start rather than atomic acquisition | Use inherited `lock.py acquire -- command` and prove holder acquisition |
| Window identity | **VERIFIED:** hard-coded geometry and loose name fallback; not bound to module-host PID | Bind PID where possible, else require WM_CLASS + renderer generation + geometry and record missing `_NET_WM_PID` |
| Stage classifier | **VERIFIED:** any non-control probe, including generic `FUN_0069b600`, can count as Cell | Require Cell-specific lifecycle/control and target-path evidence |
| Screenshot correlation | **VERIFIED:** `trace_t_nearest` is not based on tracer monotonic time | Shared monotonic clock and actual nearest-event computation, or omit the field |
| Overlay/stop readiness | **VERIFIED:** startup sleep does not prove mapped overlay or grabbed key | Verify overlay and grab readiness; physical stop remains human-gated |
| Deadlines | **VERIFIED:** not every GUI/overlay/X11 command has a timeout | Per-operation and whole-run deadlines with fail-closed teardown |
| Provenance | **VERIFIED:** current manifest omits important hashes, tool versions, actual exit/elapsed time, coverage counts, and log/shot hashes | Complete `C-PROV` manifest before evidence review |
| Orchestration | **VERIFIED:** MCP traces raw startup; GUI path is separate; direct `observe.py` is not approval-equivalent | One reviewed, gated workflow for launch/GUI/trace/teardown |
| CI | **VERIFIED:** no committed CI workflow for focused contracts/native harness | Add side-effect-free gates separately; keep original runtime opt-in |

Missing `xdotool`, `maim`, Wine, Python Xlib, CMake, or Vulkan is not the current blocker according to the 2026-09-24 audit. Runtime state, registration/profile handling, process supervision, provenance, and evidence coverage are the blockers.

## 12. Proposed artifact layout

All proposed run artifacts live under a disposable root such as:

```text
/tmp/openspore-replacement/<run_id>/
  environment/
    environment.json
    versions.txt
    wine-generation.txt
  identity/
    source-identity.json
    target-manifest.json
    preflight.json
  disposable/
    SporeApp.exe
    prefix/
    profile/
    saves/
  control/<policy>/
  cell/baseline/
  cell/call-site/<policy>/
  cell/entry/<policy>/
  artifacts/
    transactions.jsonl
    calls.jsonl
    state.jsonl
    writes.jsonl
    events.jsonl
    modes.jsonl
    objects.jsonl
    save.jsonl
    shots.jsonl
    input.jsonl
    logs.jsonl
  cleanup/
    restore-readback.json
    teardown.json
    hash-check.json
  run-manifest.json
```

Rules:

- The disposable copy, Wine prefix/profile, and saves never live in the repository.
- No raw process memory dumps or proprietary payloads are retained.
- Event/message payloads are represented only by bounded length/hash and decoded fields when legally and technically necessary.
- Every JSONL file uses a versioned schema and a common envelope with `run_id`, sequence/time, thread, status, and evidence level.
- Missing observations are serialized as `not_observed_in_capture`, not omitted.
- The final manifest records every artifact path/hash, policy, call count, unpaired calls, coverage, dropped/capped events, process exit, restore status, and exact negative reason.
- A pass requires `proprietary_bytes_added: false`, `canonical_paths_written: []`, and `canonical_kg_written: false`.
- Historical examples may be committed only after legal/provenance review; `/tmp` evidence is not automatically committed.

## 13. Explicit prohibitions

This program must not:

1. Modify `SPORE/`, `SporeApp.exe`, the disposable executable on disk, canonical saves/profiles, or the canonical KG.
2. Implement the harness, patcher, dispatcher, trampoline, or GUI automation as part of this design task.
3. Launch the original, run a broad trace, inject input, inspect process memory, or install a breakpoint while preparing this document.
4. Commit proprietary EA code, assets, models, textures, sounds, scripts, decompiled source, or raw proprietary payloads.
5. Use screenshots, generic frame callbacks, clean exits, zero events, or the decompilation-derived 64/64 result as original Cell semantics.
6. Treat `0x116B3C04` as an alias for `0x016B3C04`, or treat `sCellGame+0x5270` as the physical moving store.
7. Use `src/replace/Replace.cpp` directly as the one-float original ABI shim.
8. Combine import, vtable, function-pointer, call-site, and entry mechanisms in one experiment without a new decision record.
9. Relocate arbitrary instructions, use steady-state `RWX`, cross a `rel32` limit, patch across an unmodeled page transaction, or overwrite bytes not owned by the installer.
10. Run the legacy `INT3` tracer and patch writer on the same site concurrently.
11. Retry write-bearing runs blindly after restore conflict, crash, unknown bytes, module mismatch, or failed thread quiescence.
12. Use broad whole-process instruction tracing, force damage/death/reload, inject state, or create sentinel objects to manufacture a transition.
13. Use unrestricted clicks, free-form input, `xdotool type`, or logged credentials. Registration/profile preparation is a human handoff.
14. Normalize away addresses, object reuse, NaN payloads, signed zero, message IDs, memory values, or missing events in a comparison.
15. Promote `replaced-approx` to `replaced-verified` without live Cell evidence, exact ABI/return/state/write coverage, external-effect coverage, successful restore, independent adjudication, and human approval.

## 14. Source basis and unresolved questions

### 14.1 Primary synthesis notes

- `knowledgegraph/research/runtime-oracle/input-synthesis.md`
- `knowledgegraph/research/runtime-oracle/replacement-observability.md`
- `knowledgegraph/research/runtime-oracle/candidate-experiments.md`
- `knowledgegraph/research/runtime-oracle/automation-audit.md`

### 14.2 Required repository inputs reconciled

The plan was synthesized from the input note's primary corpus, including:

- `knowledgegraph/research/replacement-feasibility.json`
- `docs/analysis/original-exe-replacement.md`
- `knowledgegraph/research/semantic-blueprint.json`
- `docs/analysis/future-research/01-architecture-blocker-1.md` through `12-pkg-21-unknown-routing.md`
- `docs/analysis/architecture-decisions.md`
- `docs/analysis/architecture-resolution.md` and `knowledgegraph/research/architecture-resolution.json`
- `docs/analysis/reconstruction-packages.md`
- `docs/analysis/reconstruction-blueprint.md`
- `docs/analysis/reconstruction-readiness.md`
- `docs/analysis/reconstruction-research-queue.md`
- `knowledgegraph/research/track-m-oracle-plan.json`
- `knowledgegraph/research/track-n-testability.json`
- `docs/RE-AUTOMATION-ARCHITECTURE.md`
- `docs/REPLACEMENT-ABI.md` and `docs/REPLACEMENT-DIFF.md`
- `tools/observatory/README.md`, `SCENARIO-main_menu.md`, probes, scripts, and tests
- `docs/analysis/CELL-RUNTIME-OBSERVATION.md`
- `docs/CELL-CONTRACT.md`, `docs/CELLSTAGE-RECON.md`
- `docs/analysis/campaigns/cell-stage-campaign.md`
- Cell movement, pool-lifecycle, and state-machine dossiers
- GUI/input/runtime devlogs 016–019

Source conflicts were preserved and resolved only to the extent allowed by a more specific bounded static record. Older prose remains historical where it conflicts with current source or the latest direct byte record.

### 14.3 Explicit unknowns

- **[UNKNOWN]** Exact trigger and reproducibility of the original's clean exit and boot stalls.
- **[UNKNOWN]** A legitimate unattended route through registration and into Cell.
- **[UNKNOWN]** Complete dynamic caller set for the movement target.
- **[UNKNOWN]** Live meanings of the pool index, player fields, UI/camera gates, and most state words.
- **[UNKNOWN]** Runtime per-world movement-plane point.
- **[UNKNOWN]** Effects of omitted callees beyond the selected direct stores.
- **[UNKNOWN]** Live mode/event timing, thread affinity, and reentrancy.
- **[UNKNOWN]** Object generation/reuse, presentation ownership timing, and complete lifecycle order.
- **[UNKNOWN]** Persistence outer envelope, object/reference graph, migration, atomicity, and mode-handoff ownership.
- **[UNKNOWN]** Whether an entry-all-caller policy is required after a safe call-site experiment.

## 15. Final decision

**[PROPOSED]** Build the program in the order: static preflight → native ABI gate → read-only runtime preflight → positive control → original Cell baseline → call-site bypass/passthrough/replace → optional entry fallback → mandatory restore. Broader Cell lifecycle, event, shared-root, persistence, Space, and renderer experiments remain bounded read-only research and do not authorize patch installation.

Until that order produces a complete, hash-pinned, independently adjudicated Cell baseline and a safely restored replacement differential, the correct status remains `replaced-approx`; the original replacement remains `not_implemented`.
