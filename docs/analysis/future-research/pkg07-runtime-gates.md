# PKG-07 Runtime Gates: M0/M1/M2

**Package:** `PKG-07-CELL-MOVEMENT`  
**Date:** 2026-09-24  
**Status:** `NOT_RUN / BLOCKED`  
**Binary:** `SPORE/SporeBin/SporeApp.exe`, version `3.1.0.22`  
**Scope:** Durable gate contract for Cell movement runtime preparation. This document does not authorize a launch, a process-memory operation, a replacement, or a status promotion.

## Shared fixed contract

The canonical executable is read-only. The current committed identity is SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`, size `20,454,960` bytes, PE32/i386 little-endian, preferred image base `0x00400000`.

The candidate target is `Simulator::Cell::MovePlayerToMousePosition` at linked VA `0x00E5B790`, PE RVA `0x00A5B790`, `.text` file offset `0x00A5AB90`, with exact entry bytes `a1 04 3c 6b 01`. The current static interpretation is `mov eax, dword ptr [0x016B3C04]`. The older `0x116B3C04` value is not an alias; any probe or prose containing it blocks the gate until independently reconciled.

The bounded direct call site is linked VA `0x00E8083B`, PE RVA `0x00A8083B`, `.text` file offset `0x00A7FC3B`, with exact bytes `e8 50 af fd ff`, decoding to `call rel32 0x00E5B790`, with continuation `0x00E80840`. The known direct caller is `FUN_00E806B0`; the complete dynamic caller set is unknown and is not claimed by the direct-site contract.

The static ABI contract is x86-32 Windows cdecl behavior, return type `void`, one `float deltaTime` at `[ESP+4]`, return address at `[ESP+0]`, expected stack delta zero, and preservation of `EBX`, `EBP`, `ESI`, and `EDI`. The terminal instruction is plain `RET` at `0x00E5BA01`, not `RET N`. `EAX`, `ECX`, `EDX`, and flags are diagnostic; no typed return is inferred for this void target. The existing four-argument OpenSpore stand-in is not this ABI and must not be installed as the original shim.

Runtime address conversion is `module_load_base + PE RVA`; linked VA conversion is `0x00400000 + PE RVA`; file offsets come from the parsed PE section table. The existing observatory probe field named `rva` is a linked-VA convention, not a true PE RVA.

The disposable-copy policy is mandatory for any future original-process work: use a byte-identical copy under a disposable `/tmp` run root, a fresh disposable Wine prefix/profile/save directory, and a fresh artifact directory. The canonical executable, `SPORE/`, canonical profiles/saves, and the canonical knowledge graph remain unchanged. Runtime evidence may contain hashes, bounded raw register/memory values, addresses, metadata, and event ordering; it must not contain proprietary payloads, assets, or full memory dumps. No status promotion is authorized by this document.

Human approval is required before any original-process launch, breakpoint installation, input, process attachment, read, or debugger action. The approval must identify the gate, binary hash, probe-manifest hash, run root, scope, display/Window target, stop condition, and human operator. Static parsing, hash checking, Python syntax checks, and dry-run enumeration are non-human-safe activities and are not runtime evidence. The current status remains `NOT_RUN`; each gate remains `BLOCKED` where its prerequisites or direct evidence are absent.

The M2 state whitelist is limited to owner-qualified reads of: `sCellGame` slot linked `0x016B3C04`; `sCellGame+0x5158`; `sCellGame+0x411C`; `sCellGame+0x5190`; the one-byte candidate `u32[sCellGame+0x5190]+0xE0`; caller gates `sCellGame+0x515C` and `+0x51E0`; movement-plane normal linked `0x015A7C40..0x015A7C4C`; movement-plane point linked `0x016B3C28..0x016B3C34`; the Cell UI slot `0x016B3C0C` and, only when safely resolved, `sCellUI+0x24/+0x26`; resolved player target `+0x08..+0x10`; orientation `+0x14..+0x20`; current position `+0x4C..+0x54`; pool index, object address, bounded object hash, generation status; and bounded guard bytes around each candidate. The older `sCellGame+0x5270` four-byte moving-flag interpretation is not accepted as the physical moving store. Null, unreadable, and guard outcomes are recorded explicitly and are not normalized into zeros.

## M0 — Fresh-generation boot and attach control

### Hypothesis

One bounded, human-approved, no-input boot of the byte-identical disposable copy either produces a attributable original startup sequence and renderer/module identity, or produces an exact, bounded boot negative. M0 is not a Cell, gameplay, ABI, or replacement result.

A positive control would show, with provenance and monotonic ordering, `entry` followed by the expected `InitPlugins`, `Init`, `Startup`, and recurring `App::IAppSystem::Get` events, a discovered `SporeApp.exe` module host and load base, matching control bytes, a pinned renderer/window identity, survival through the declared horizon, and breakpoint restoration. A negative must distinguish zero-active-probe, module-attach failure, target exit before module, boot stall before renderer, registration gate, window-not-found, renderer failure, clean exit, signal exit, and timeout.

### Setup

Use the canonical binary only for the preflight hash and size check. Future runtime work uses a byte-identical disposable copy, fresh disposable prefix/profile/save root, and a fresh run directory under `/tmp/openspore-pkg07/<run_id>/`. Use `tools/observatory/probes/main_menu.json` unchanged, recording its path and SHA-256. Pin the tracer/harness revision, Python/tool versions, Wine version and generation, `DISPLAY`, compositor/session, window identity, geometry, and machine-lock result. Send no input. Use the existing approved command surface; a direct `observe.py` invocation is not approval-equivalent. The operator must establish a fresh Wine generation without affecting unrelated user services, retain the physical emergency-stop boundary, and never log credentials or retain screenshots as semantic evidence.

The target identity remains the fixed contract above: target `0x00E5B790`, bytes `a1 04 3c 6b 01`, call site `0x00E8083B`, bytes `e8 50 af fd ff`, caller `FUN_00E806B0`, continuation `0x00E80840`, and the static void/float/cdecl contract. M0 must not arm a replacement or claim a target call.

### Preflight

Before any launch, verify the canonical file size and SHA-256, parse the PE machine and preferred image base, derive the `.text` mapping, read the target and call-site bytes, decode the target operand and call displacement, and verify the call continuation arithmetic. Verify that `main_menu.json` is syntactically valid, has image base `0x00400000`, contains the seven declared startup probes, and is hash-pinned. Verify that all expected probes are accounted for before planting temporary `INT3` breakpoints, open raw output before instrumentation, and prove the shared machine lock can be acquired through the reviewed inherited-lock path. Recheck the disposable-copy hash immediately before launch. The known `0x116B3C04`/`0x016B3C04` conflict must be marked blocking until the current probe manifest is corrected or a separate reviewed static adjudication is approved; it must not be silently normalized.

Record the M0 manifest fields for binary/copy hash, probe/hash identity, target identity, caller/continuation, ABI static status, address convention, environment, module host, process outcome, event counts, active/skipped/retired/dropped counts, renderer marker, and cleanup status. Static preflight does not authorize a process launch.

### Intervention

After explicit human approval, perform one bounded no-input observation using the disposable copy and approved startup probe set. Supervise the tracer, Wine module host, and shell through the declared deadline. Plant only the reviewed startup breakpoints, preserve the raw JSONL and process logs, and do not inject navigation, registration text, or state. Stop on lock contention, module timeout, missing renderer/window, human stop, malformed output, or the declared timeout. The operator-controlled cleanup path must classify the exact outcome even when the target exits early.

### Observable

The required observables are binary/copy identity, module host PID/path/load base, target control byte equality, startup event sequence and counts, first and last event times, active/skipped/retired/dropped counts, renderer marker, window identity and geometry, process exit/signal/time, stderr hash, and restoration/detach evidence. A missing event is `not_observed_in_capture`; it is not universal absence. A screenshot, window, clean exit, or generic frame is not a positive boot control.

### Expected result

The durable success condition is a complete, hash-pinned M0 positive control with `C-PROV`, `C-BOOT`, and `C-NEG` fields, a reproducible startup sequence, attributable module/renderer identity, bounded survival, and restored instrumentation. Any exact bounded negative records the failure phase and blocks dependent behavioral claims without authorizing retry expansion. **Current status: `NOT_RUN`; historical startup evidence exists but is not a current gate result, and the manifest address conflict keeps static preparation blocked.**

### Failure interpretation

A hash/size/PE/byte/decode/caller/continuation mismatch is `FAIL` and invalidates the candidate. A manifest conflict, missing probe accounting, incomplete provenance, malformed JSONL, stale tracer binary, or missing output path is `BLOCKED`. A boot, registration, renderer, window, process, or timeout negative is an environment/reachability result only; it does not establish that Cell or movement behavior is absent. No agent may convert a historical startup record into a current pass.

### Cleanup

Close the tracer and any approved disposable processes through the supervised teardown path, release the machine lock, preserve only disposable artifacts, and verify no harness-owned breakpoint, writer, or process remains. Recompute the disposable-copy hash and verify the canonical executable, `SPORE/`, canonical profiles/saves, and canonical knowledge graph were not changed. Do not kill unrelated Wine services or use a destructive default-prefix cleanup as part of this document.

## M1 — Cell reachability and lifecycle control

### Hypothesis

A naturally navigated Cell mode produces a Cell-specific lifecycle signal and target-path evidence, with the entry control preceding the Cell events in the same module-host lineage. The minimum positive claim is one non-control Cell probe with attributable time order; `FUN_0069B600` is explicitly not a Cell marker. A failure before that point is a bounded navigation, registration, boot, or instrumentation negative, not a movement semantic result.

### Setup

Require a completed M0 positive control or an explicit human decision to investigate a documented M0 negative. Use a byte-identical disposable copy, fresh disposable prefix/profile/save root, and a human-prepared legitimate profile without credential logging. Use the focused-window navigation path, fixed geometry, and the existing allowlist `Return`, `Escape`, `Up`, `Down`, `Left`, and `Right`; no letters, digits, free-form text, clicks, or `xdotool type`. Use `tools/observatory/probes/cell_movement.json` only after its stale `0x116B3C04` note is blocked or separately adjudicated. Record the exact input manifest before each event, the window identity/geometry, and the human operator/stop readiness. No replacement, hook, memory write, or state injection is permitted.

The target remains linked VA `0x00E5B790`, PE RVA `0x00A5B790`, file offset `0x00A5AB90`, exact bytes `a1 04 3c 6b 01`, with the known direct caller `FUN_00E806B0`, call site `0x00E8083B`, call bytes `e8 50 af fd ff`, continuation `0x00E80840`, and the static `void(float)` cdecl contract. M1 establishes reachability only; it does not establish the complete M2 state oracle.

### Preflight

Revalidate M0 provenance and the disposable-copy hash, probe-manifest hash, target/call bytes, PE mapping, ABI static fields, and address convention. Require a complete active-probe accounting for the twelve-probe Cell set, including the bootstrap control, and reject stale, unknown, or conflicting manifest values. Require module host identity, load base, executable mapping, renderer marker, pinned window, human emergency-stop readiness, fresh profile/save isolation, and atomic machine-lock acquisition. Reject `0x116B3C04` as an alias for `0x016B3C04`; record the current bytes as the candidate and fail closed on disagreement. No input is issued during this preflight.

The M1 manifest must include binary/copy hash, probe hash, exact target/call/caller/continuation identity, environment, window identity, input log, event counts, process outcome, and the first/last observation times. The current entry-only tracer must be disclosed as insufficient for M2; it may be used only for bounded reachability.

### Intervention

After human approval, follow the reviewed fixed navigation plan in a fresh disposable process. Record each intended input before issuing it, stop at the first attributable Cell-specific event or at the declared registration, input, renderer, geometry, lock, human, process, or timeout stop. Do not broaden the allowlist, type registration data, synthesize transitions, inject messages, modify state, or use generic frame activity as a stage marker. Preserve raw JSONL, input metadata, bounded screenshot annotations, stderr hashes, and the final manifest.

### Observable

The positive vector is: bootstrap `entry`; then at least one non-control Cell-specific probe, such as the strategy update/body or movement target path, after the entry control; a stable module-host and load-base identity; complete probe accounting; monotonic event order; a renderer/window identity; and survival through the declared Cell observation. For M1, the target `0x00E5B790` must not be counted merely because its probe is installed; a target-path claim requires a real target event or an explicitly attributable call-path event.

A negative vector names the exact blocked phase: boot, registration, window, renderer, fixed input, partial instrumentation, target unreachability, early process exit, or timeout. Zero events, menu-only activity, and `FUN_0069B600` activity remain distinct from Cell reachability.

### Expected result

The durable success condition is a hash-pinned, human-watched M1 positive Cell control satisfying `C-PROV`, `C-ENTRY`, `C-ORDER`, and `C-NEG`, with no unexplained probe drops and no screenshot-only classification. Only then may M2 proceed. A bounded negative is a valid result but leaves M2 blocked. **Current status: `NOT_RUN / BLOCKED`; historical records are negative for non-control Cell probes, positive boot is not a current M0 result, registration/profile handoff is unresolved, and the probe manifest address conflict remains open.**

### Failure interpretation

A positive screenshot, registration response, menu frame, generic orientation helper, or installed-but-unfired target probe is not M1. Registration persistence, input refusal, window drift, renderer absence, process exit, inactive probes, or generic activity classify the run as a bounded negative or instrumentation failure. It is not evidence that Cell movement is inert, absent, or semantically equal to the OpenSpore stand-in. No input ladder, retry, or replacement may be used to manufacture a transition.

### Cleanup

Stop at the first positive Cell event or the exact negative condition, restore every temporary breakpoint, release the lock, terminate only processes belonging to the disposable run, and preserve the raw result. Verify the disposable-copy hash and that the canonical executable, `SPORE/`, canonical profile/saves, and canonical knowledge graph are unchanged. Do not overwrite the historical negative record or promote PKG-07 readiness from M1 alone.

## M2 — Read-only ABI and side-effect characterization

### Hypothesis

For a naturally reached `0x00E5B790` call, a read-only entry and safe post-return observation can establish the real `void(float)` frame, return/continuation, pool-index resolution, lock and camera/UI gates, movement-plane values, target/orientation/moving writes, and omitted-callee effects. M2 can pass mechanically only when the ABI, return pairing, owner-qualified state, declared write coverage, external-effect horizon, and process teardown are all attributable. Entry-only registers, a pointer-like pool value, a screenshot, or a host/decompilation differential cannot pass it.

### Setup

Require M1 positive reachability, a hash-identical disposable copy, fresh disposable prefix/profile/save root, human approval, display/window pinning, and the shared machine lock. Use a read-only observation adapter or debugger capability that can sample the entry frame and a safe continuation/return point without installing a hook or writing target code. The current observatory `probe_tracer` is entry-only and plants temporary `INT3` bytes, so it is not sufficient by itself for a strict M2 claim. If a reviewed adapter uses software breakpoints, record that process-memory modification and require restoration evidence. Do not retain payloads or full memory dumps.

The target is linked VA `0x00E5B790`, PE RVA `0x00A5B790`, file offset `0x00A5AB90`, exact bytes `a1 04 3c 6b 01`, and the current binary interpretation `mov eax,dword ptr [0x016B3C04]`. The direct caller is `FUN_00E806B0`; the call site is `0x00E8083B` with bytes `e8 50 af fd ff`; the continuation is `0x00E80840`. ABI is static x86-32 cdecl `void(float)`, `deltaTime` at `[ESP+4]`, return address at `[ESP+0]`, zero stack delta, preserved `EBX/EBP/ESI/EDI`, and plain `RET` at `0x00E5BA01`. M2 records raw bits first and decoded values second; it does not invent a typed return.

### Preflight

Revalidate the canonical identity and disposable-copy hash, PE section mapping, target/call bytes, caller/continuation, ABI static record, probe/harness hash, module host, load base, mapped bytes, page boundaries, page protection, thread/debugger ownership, and the state whitelist. Resolve runtime addresses as `load_base + PE RVA`; do not probe preferred-base addresses blindly. Reject any existing `INT3`, detour, unknown writer, unsafe pointer, or `0x116B3C04` conflict. Require the read-only whitelist and a bounded capture horizon to be present before sampling. No M2 state sample may be taken from a different pool owner than the before-sample.

The M2 manifest must include the complete canonical observation vector: target identity, attachment/read transaction, entry frame, return frame, state before/after, direct writes, guard memory, called callees, events, logs, input, mode axes, object lifecycle, save state, process lifecycle, and restore evidence. Every field must carry source, coverage, evidence level, and comparison rule. A snapshot delta is not an exact write; a watchpoint proves access, not an instruction unless directly attributable.

### Intervention

After M1 and human approval, run one naturally reached Cell process with the approved navigation path and bounded capture. Sample the target entry and the safe continuation/return point, plus the exact whitelisted state and guard windows. Pair observations by thread, call sequence, stack return address, target identity, and monotonic time. Use hardware watchpoints or directly attributable store probes only if the capability is proven; otherwise label write coverage partial. Do not patch, hook, call the function synthetically, alter pool state, force input, or run a policy comparison. Stop on unsafe address, owner change, unpaired return, page/debug ownership conflict, target instability, or the declared horizon.

### Observable

Per selected call, capture `EIP`, `ESP`, `EBP`, `EAX`, `EBX`, `ECX`, `EDX`, `ESI`, `EDI`, and `EFLAGS` at entry and return/continuation; `[ESP]`, `[ESP+4]`, bounded caller guards, and the exact float raw bits; target identity, caller, continuation, thread, sequence, and monotonic time; exact `RET` form and stack delta; callee-saved comparison; policy/attachment status; and original-execution count.

Capture only the M2 whitelist: `sCellGame` and its lock, pool index, serializable pointer, candidate moving byte, caller gates, plane normal/point, safe UI slot, resolved player target/orientation/current-position fields, pool/object identity, and bounded guards. Record null/unreadable/owner-change outcomes explicitly. Capture direct writes only through directly attributable store/watch evidence, and record omitted callees separately. Keep events, logs, screenshots, input, mode axes, object lifecycle, save state, and process lifecycle separate from the ABI record. A missing observation is `not_observed_in_capture`, not a pass.

### Expected result

The durable success condition is a complete M2 observation satisfying `C-ABI`, `C-SIDE`, `C-STATE`, and `C-REPLACEMENT` prerequisites: paired entry/return evidence, exact stack/return/callee-saved behavior, distinguishable pool index versus resolved object, owner-qualified state before/after, declared direct-write coverage or explicit partial status, omitted-callee coverage, external-effect horizon, process outcome, and restore/detach evidence. A successful M2 establishes evidence for a later review only; it does not itself authorize installation or promotion. **Current status: `NOT_RUN / BLOCKED`; M1 positive reachability is absent, the current tracer lacks return/post-state coverage, the address conflict is unresolved, and no original target call has been observed.**

### Failure interpretation

An entry-only event, absent return pairing, unsafe or unreadable whitelist read, pointer/index conflation, snapshot delta presented as an exact write, generic frame activity, or incomplete callee coverage is `PARTIAL` or `FAIL`, never pass. A null player, changed owner, missing plane point, or unknown field meaning remains unknown; it is not silently filled from the host model. A failed restore, unknown writer, stale executable, or unpaired continuation fails the whole experiment. The decompilation-derived 64/64 host differential remains `APPROXIMATION`/reference evidence and cannot compensate for missing M2 evidence.

### Cleanup

Stop at the declared M2 boundary, restore every temporary breakpoint or debugger/watchpoint owned by the harness, detach only after verification, release the machine lock, and terminate only the disposable run’s processes. Recompute the disposable-copy hash, verify guard bytes and page protection, and verify the canonical executable, `SPORE/`, canonical profiles/saves, and canonical knowledge graph are unchanged. Preserve bounded ABI/state/write metadata and exact negative or partial reasons; do not commit raw memory, promote replacement status, or claim M0/M1/M2 passed.

## Current handoff

Only non-human preflight, Python contract tests, and dry-run enumeration may be run during preparation. Original launch, Wine attachment, input, breakpoint placement, runtime memory reads, M0/M1/M2 execution, replacement installation, and status promotion remain human-gated and were not performed by this artifact. The current project-level status remains `NOT_RUN / BLOCKED`; this document does not change the existing `replaced-approx` boundary.
