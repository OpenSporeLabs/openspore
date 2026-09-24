# Final runtime experiment specification

**Date:** 2026-09-24  
**Status:** **PROPOSED / UNVERIFIED**  
**Target:** `SPORE/SporeBin/SporeApp.exe` 3.1.0.22  
**SHA-256:** `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`  
**Architecture:** x86 PE32/i386, little-endian, preferred image base `0x00400000`

## Status and evidence boundary

This document specifies exactly 20 ranked runtime experiments. It does not report that any of them was executed while preparing this specification. Every experiment remains **PROPOSED / UNVERIFIED** until a future raw trace, manifest, analysis, and independent review satisfy its stated decision criterion.

The only positive original-process runtime record cited here is historical bounded startup/service-access evidence. Historical Cell attempts are reachability negatives. No positive original Cell, persistence, Space, presentation, movement-return, or replacement-control result exists. OpenSpore source, host fixtures, screenshots, decompilation, SDK names, and static negative scans are not original runtime evidence.

Evidence labels used in this document:

- `CONFIRMED`: a committed name/type/constant contract supported by the cited source record.
- `VERIFIED`: a directly checked byte, arithmetic, tool behavior, or static instruction fact; it does not imply runtime reachability.
- `HISTORICAL OBSERVED`: present in an earlier committed runtime record but not reproduced by this specification.
- `SUPPORTED`: a bounded interpretation from direct static behavior.
- `INFERRED`: a semantic interpretation that still requires direct evidence.
- `APPROXIMATION`: a host or clean-room stand-in, not an original oracle.
- `UNKNOWN`: not established.
- A future positive trace may be recorded as `OBSERVED` only for the exact event, address, identity, time window, and environment actually captured. Independent review may promote that observation to a stronger project status; the experiment itself does not do so.

## Global execution contract

These rules apply to every experiment:

1. **Human authorization.** A future original-process launch requires explicit human approval, `OPENSPORE_MCP_TRUSTED=1`, human presence on the shared display, physical emergency-stop readiness, and the shared machine lock. No experiment in this document is safe unattended in its current form. Static preflight, dry-run, and pure analysis may be unattended but are not runtime outcomes.
2. **No shared-display automation as evidence.** The current `cell_trace.sh` is not a complete unattended supervisor: its lock handoff is not atomic, process supervision is incomplete, failure paths may omit manifests, screenshot correlation is not implemented, and the Cell classifier is too broad. A future run must repair or replace those gaps before use.
3. **Identity pinning.** Record the executable path, SHA-256, version, PE image base, section mapping, probe-set path and SHA-256, tracer/harness source revision or hash, tool versions, address convention, module load base, target original bytes, and attached module-host PID.
4. **Environment pinning.** Record the fresh wineserver generation, Wine version, `DISPLAY`, compositor/session, primary output, display server version, xdotool/maim/Xlib versions where used, window ID, `WM_CLASS`, `_NET_WM_PID` presence or absence, exact geometry, duration, and machine-lock acquisition result.
5. **Read-only default.** Ranks 1-19 are read-only with respect to original code, game data, saves, and profile state. They may use temporary `0xCC` breakpoints, bounded reads, and hardware watchpoints only in an approved disposable process. They must not install a hook, patch bytes, write a slot, inject a message, force pool exhaustion, synthesize damage/death, or treat an opaque value as a pointer.
6. **Disposable state.** Save/load and replacement experiments use a disposable profile/save directory and, for rank 20, a byte-identical disposable process image. Canonical `SPORE/`, canonical profiles/saves, and the canonical executable remain read-only. No proprietary payload or memory dump is retained.
7. **Fixed input.** Use only a pre-approved, reviewable action from the current navigation allowlist. Prefer focused-window input for Cell work. Never type credentials or log secrets. A human-prepared disposable profile is the only proposed registration bypass.
8. **Artifact floor.** Every run must preserve the exact command or policy, approval identity, raw JSONL, per-probe active/skipped/retired/dropped counts, exact event count, monotonic timestamps, process/signal/exit status, stderr and harness hashes, input log, screenshot hashes as annotations only, exact positive/negative reason, and a final queue/capture-horizon marker.
9. **Address discipline.** `linked VA = 0x00400000 + PE RVA`; the existing observatory's JSON field named `rva` contains a tracer address in linked-VA terms. Runtime addresses are `module_load_base + PE RVA`. File offsets come from the PE section map. The `0x016B3C04` versus `0x116B3C04` conflict must fail preflight until reconciled.
10. **Negative classification.** Zero active probes, zero events, clean exit, stall, renderer failure, registration gate, partial instrumentation, target unreachability, and missing target-specific callback are distinct outcomes. None is evidence of absent gameplay behavior. A screenshot or generic frame heartbeat cannot substitute for a raw event.
11. **Stop rule.** Stop after one bounded approved attempt when a prerequisite fails. Do not retry by increasing key count, duration, or injection strength. A boot or reachability negative blocks only dependent behavioral claims.
12. **No promotion from setup.** Hash agreement, static bytes, successful tracer attachment, a visible window, a changed screenshot, or a process surviving a duration is not behavioral evidence for the experiment's hypothesis.

## Ranked experiment set

| Rank | ID | Experiment | Primary information gain | Gate | Architecture blockers addressed | Runtime status |
|---:|---|---|---|---|---|---|
| 1 | RE-01 | Fresh-generation boot and exact negative classification | Establish whether any original behavioral run is interpretable | Required for ranks 2-20 | Prerequisite for `BLOCKER-A`, `BLOCKER-B`, and `BLOCKER-C` | Human-only; current tooling not safe unattended |
| 2 | RE-02 | Noun/star root publication, equality, replacement, and teardown | Select the root owner/liveness graph | RE-01 positive or explicitly scoped boot investigation | `BLOCKER-A`; DEC-04A/04B; COND-03 | Human-only |
| 3 | RE-03 | `DAT_0167eaec` and forwarded `receiver+0x20` | Identify first writer, freshness, and downstream ownership | RE-01 plus a naturally reachable state transition | `BLOCKER-B`; DEC-06; COND-04 | Human-only |
| 4 | RE-04 | App message-queue ABI and mode-announcement bridge | Separate registration, immediate, and deferred transport records | RE-01 plus one attributable mode request | Event-timing residual; DEC-02/03 | Human-only |
| 5 | RE-05 | Persistence object/reference graph and failure behavior | Select schema, object-table, cycle, and transaction design | RE-01 plus approved disposable save/load path | `BLOCKER-C` persistence graph; DEC-10; COND-05 | Human-only |
| 6 | RE-06 | Mode handoff, automatic save, and restore ownership | Decide live transfer, DTO, or explicit save at teardown | RE-05 and a reachable mode transition | `BLOCKER-C` mode handoff; COND-05 | Human-only |
| 7 | RE-07 | Cell reachability control | Establish a Cell-specific gate without false-positive frame classification | RE-01 and legitimate disposable-profile navigation | Unblocks Cell owner/lifecycle experiments; not itself a blocker resolution | Human-only |
| 8 | RE-08 | Cell lifecycle and pool identity | Separate simulation allocation from presentation and mode lifetime | RE-07 | DEC-08; Cell pool/avatar ownership | Human-only |
| 9 | RE-09 | Receiver-typed avatar ownership and `receiver+0x54` replacement | Preserve receiver qualification and reference replacement | RE-07 or a naturally reachable noun-layout receiver | DEC-07 avatar boundary; part of `BLOCKER-A` consumer graph | Human-only |
| 10 | RE-10 | Cell gameplay versus presentation/effect boundary | Establish whether gameplay requires presentation | RE-07 plus one attributable interaction or effect | DEC-08; interaction/presentation coupling | Human-only |
| 11 | RE-11 | Star/empire lookup, cache, and Space context lifecycle | Preserve lower-bound/cache semantics and Space owner handoff | RE-02 and positive Space reachability | `BLOCKER-A` star half; DEC-05; Space owner graph | Human-only |
| 12 | RE-12 | Deferred scheduler, pause/speed, and App queue separation | Distinguish timing substrate from message transport | RE-04 plus a naturally due event | Event-family ordering residual | Human-only |
| 13 | RE-13 | Cell movement ABI, return, direct writes, and callee side effects | Establish the minimum valid movement oracle | RE-07 and dedicated return/memory coverage | Movement ABI/side-effect blocker; no architecture-cluster resolution by itself | Human-only |
| 14 | RE-14 | Mouse/camera causality for movement | Establish input-to-ray-to-target order | RE-13 | Movement input contract; mode/input-axis residual | Human-only |
| 15 | RE-15 | Cell object/GFX detach and rebuild identity | Determine when pool identity survives presentation rebuild | RE-08 plus a natural detach/rebuild | DEC-08 pool/presentation coupling | Human-only |
| 16 | RE-16 | Input, message, callback, resource, and frame ordering | Bound producer-consumer and callback order | RE-01 and one fixed attributable UI action | DEC-01/02/03 timing residual | Human-only |
| 17 | RE-17 | Resource-key/cache/lease versus GFX presentation boundary | Preserve layered resource identity and display causality | RE-16 plus one attributable resource/display transition | DEC-09; Cell presentation/content boundary | Human-only |
| 18 | RE-18 | Independent mode axes across a transition | Keep App, strategy, input, Space, and Cell state distinct | RE-04 and a naturally reachable transition | DEC-01 mode-axis boundary | Human-only |
| 19 | RE-19 | Save-field survival and restoration matrix | Determine which declared fields survive explicit save/reopen | RE-05 and one approved round trip | `BLOCKER-C` descriptor/field survival; COND-05 | Human-only |
| 20 | RE-20 | Positive replacement control on `App::IAppSystem::Get` | Validate install, return observation, policy, and restore before any Cell write | All static/native/runtime replacement preflights | Replacement observability only; no gameplay blocker resolved | Human-only and separately authorized |

## Experiment specifications

## RE-01 — Fresh-generation boot and exact negative classification

**Status:** **PROPOSED / UNVERIFIED**  
**Execution:** Human-only. One bounded 30-60 second run; unattended execution is prohibited by the automation audit.  
**Current evidence:** Historical positive startup only (`entry`, `InitPlugins`, `Init`, `Startup`, high-frequency `IAppSystem::Get`); historical Cell runs include stable zero-event/stall/self-exit negatives.  
**Evidence target:** A yields `HISTORICAL/REPRODUCED OBSERVED` only if the complete pinned sequence is captured; B is an exact environment/outcome negative, not a gameplay result.  
**Architecture blockers resolved:** None directly; supplies the prerequisite for `BLOCKER-A`, `BLOCKER-B`, and `BLOCKER-C`.

### Hypothesis A

A fresh approved generation produces the reproducible linked-VA sequence `entry` (`0x011E11A0`) → `InitPlugins` (`0x007E93D0`) → `Init` (`0x007E8BA0`) → `Startup` (`0x007E67A0`) → repeated `App::IAppSystem::Get` (`0x0067DCC0`), identifies the module-host PID and load base, maps a renderer marker/window at pinned geometry, and remains alive for the declared observation horizon.

### Hypothesis B

The run instead reaches a clean exit, boot stall, registration/module-attach gate, no-window outcome, renderer failure, zero-active-probe state, or early tracee termination. The exact failure phase is identifiable, and no Cell or gameplay conclusion is permissible.

### Required setup

- Pin the canonical binary identity, `main_menu.json` bytes/hash, tracer build/hash, `0x011E11A0` control bytes, address convention, Wine version/generation, display/compositor, output identity, xdotool/window tools, and exact geometry.
- Acquire `/tmp/openspore-machine.lock` atomically through the reviewed `lock.py acquire -- <command>` path; verify acquisition rather than check-then-act.
- Verify human approval, `OPENSPORE_MCP_TRUSTED=1`, overlay readiness, physical `Ctrl+Alt+Backspace` stop readiness, all seven expected probe mappings, raw-output writability, and `wineserver -k` immediately before launch.
- Send no input. Open the raw JSONL before planting breakpoints in any revised tracer and record active/skipped/retired/dropped probe counts.
- Use a fresh run directory under `/tmp/openspore-runtime/<run_id>/`; preserve no screenshots as semantic evidence.

### Intervention

Perform one no-input, bounded boot observation. Supervise the tracer, Wine host, and shell to the end. Do not retry automatically and do not infer a mode transition from startup events.

### Observable outcome A

The raw manifest records the exact first-occurrence sequence `entry → InitPlugins → Init → Startup → IAppSystem::Get`; all seven probes are active or explicitly accounted for; module host/path/load base and original control bytes match; a mapped window has the pinned identity/geometry; the renderer marker is present; the process remains alive through the horizon; and teardown restores all breakpoints. This is a boot control, not a Cell result.

### Observable outcome B

The manifest records exactly one of: `zero_active_probes`, `target_exited_before_module`, `module_attach_failed`, `boot_stall_before_renderer`, `registration_gate`, `window_not_found`, `renderer_failure`, `tracee_clean_exit`, `tracee_signal_exit`, or `timeout_with_live_process`, with actual elapsed time, process/signal status, stderr hash, and event count. The result remains an environment/boot negative.

### Interpretation

Outcome A authorizes separately approved, target-specific experiments but does not prove gameplay reachability. Outcome B blocks behavioral interpretation and directs work to boot/Wine/renderer/registration diagnosis. Historical startup evidence is not silently reused as a new observation.

### Failure conditions

- Binary, probe, tracer, environment, display, window, or address identity is incomplete.
- Any expected probe is inactive/retired without coverage accounting.
- Direct `observe.py` is treated as the MCP approval boundary.
- The shell writes a manifest after early process death without recording the actual exit.
- A clean exit, stall, screenshot change, generic frame, or zero events is described as “no Cell behavior.”
- A retry occurs without a separately approved diagnosis.

### Cleanup

Terminate through the supervised bounded stop path, verify no stale `SporeApp` or wineserver process remains, release the machine lock, preserve the raw artifact and exact negative reason, and leave `SPORE/`, profiles, canonical KG, and the executable unchanged.

## RE-02 — Noun/star root publication, equality, replacement, and teardown

**Status:** **PROPOSED / UNVERIFIED**  
**Execution:** Human-only; read-only lifecycle observation.  
**Current evidence:** Four distinct four-byte storage words and four accessors are `VERIFIED` statically; publication, value equality, liveness, and teardown are `UNKNOWN`. DEC-04A/04B freezes separate ports but leaves equality open.  
**Evidence target:** Direct owner-qualified lifecycle records can produce `OBSERVED`; a single-owner conclusion requires the complete publish/equality/teardown set.  
**Architecture blockers resolved:** `BLOCKER-A`; COND-03 noun/star root compatibility.

### Hypothesis A

For each observed noun and star family, the two slots become equal for a documented publication window, are published/replaced through the same owner, and are invalidated together during teardown. A one-owner result is valid only for the observed phase and does not imply a global singleton.

### Hypothesis B

At least one pair is unequal, stale, phase-specific, or independently rebound/invalidated. Four explicit ports with phase-qualified owner identities remain necessary; a single registry would be incorrect.

### Required setup

- Require RE-01 outcome A, or record an explicit decision to investigate a boot negative without making Cell/root claims.
- Pin read-only observations for noun slots `DAT_0167eae0`/`DAT_0167eb60` and accessors `0x00B3D300`/`0x00B3D400`; star slots `DAT_0167eae4`/`DAT_0167EB0C` and accessors `0x00B3D2A0`/`0x00B3D3A0`.
- Correlate mode helper/lifecycle events at `0x007D85B0`, `0x007D8C80`, `0x007D9120`, `0x00E552F0`, `0x00E7FC00`, and `0x00E81F30` only if naturally reached.
- For each sample record timestamp, phase, active mode/index, raw slot bits, inferred pointer only when separately proven, accessor receiver/return, publisher/releaser identity, and teardown phase. Do not dereference by resemblance.

### Intervention

Observe one naturally approved mode entry and exit, including snapshots before old exit, after old exit/before new enter, after new enter, and after dispose. Add a naturally occurring teardown if the first transition exposes one. Do not write slots or manufacture a transition.

### Observable outcome A

Each noun pair and each star pair has a complete timestamped `publish → equal window → replace/unpublish → coordinated teardown` matrix, with the same identified owner and no stale slot after the new phase commits. A supports a conditional alias/view contract for the observed phase only.

### Observable outcome B

At least one snapshot has noun pair inequality, star pair inequality, a replacement window, a stale old value after new entry, or independent clear/release. B preserves four phase-qualified ports and requires explicit rebind, cache invalidation, and teardown ordering.

### Interpretation

Neither result proves a named manager, pointer type, cross-mode singleton, or save-restoration rule. Complete A permits collapsing only the observed family/phase relation; incomplete A or any B retains the current interim architecture. A negative or unreachable result leaves `BLOCKER-A` open.

### Failure conditions

- A slot is read without owner, phase, accessor, or publication provenance.
- High fan-in is treated as owner proof.
- A bounded static negative scan is described as proof that no computed writer exists.
- One phase's equality is generalized to all modes/plugins/save restoration.
- Pointer teardown is inferred from a zero word without a release/lifetime event.
- Boot or transition is unreachable but a root conclusion is recorded.

### Cleanup

Stop at the approved transition, restore breakpoints, release the lock, teardown processes, and retain the slot/owner/phase table. Do not collapse KG records, edit the architecture register, or mutate any slot.

## RE-03 — `DAT_0167eaec` first writer and forwarded receiver state

**Status:** **PROPOSED / UNVERIFIED**  
**Execution:** Human-only; bounded read-only writer/consumer trace.  
**Current evidence:** `0x00B3D320` source read, zero→`0xffffffff`, and nonzero `receiver+0x20` forwarding are `VERIFIED` statically; first writer, physical type, freshness, and ownership are `UNKNOWN`.  
**Evidence target:** Producer/consumer identity and lifecycle records can produce `OBSERVED`; the current opaque contract remains until complete.  
**Architecture blockers resolved:** `BLOCKER-B`; COND-04 typed-state ownership.

### Hypothesis A

`DAT_0167eaec` is a borrowed opaque `uint32` publication gate. `0x00B5B800` returns exactly `0xffffffff` when the source is zero and otherwise returns the scalar word at `receiver+0x20`; identified consumers use it as a scalar and neither dereference nor retain it.

### Hypothesis B

An identified constructor or lifecycle writer publishes the source; `receiver+0x20` changes or clears across a mode transition; or a consumer dereferences, retains, or routes by the returned value as an owning object. A typed owner graph and freshness/teardown contract are then required.

### Required setup

- Require RE-01 and a naturally reachable initialization/replacement/teardown path. Otherwise classify as static-only.
- Pin observations at `0x00B3D320`, `0x00A42730`, and `0x00B5B800`; cover known consumers `0x00AD12A0`, `0x00D2E4A0`, `0x00D2E580`, `0x00D2E8A0`, and `0x00C099E0` when reached.
- Record source word, receiver identity/provenance, `receiver+0x20`, returned bits, consumer operation, thread, and lifecycle phase. Keep `C00`, `C01`, `C02`, `C04`, `C05`, `C06`, unknown `C03`, and `0xffffffff` distinct.
- Use a bounded hardware watchpoint or store probe only on statically identified source/field writes. Do not place a sentinel or manufacture a receiver.

### Intervention

Observe initialization and one natural mode/state replacement, recording the source and forwarded word before and after each identified consumer path. If a defining store is found, follow it to its constructor/writer; do not follow an unproven value as a pointer.

### Observable outcome A

The complete matrix shows an identified publisher lifecycle; `receiver+0x20` remains a four-byte scalar word; `0x00B5B800` returns the exact expected bits; observed consumers perform scalar compare/branch/copy operations; no observed consumer dereferences or retains the result. Publication and freshness remain explicit unknowns.

### Observable outcome B

A defining source store, receiver clear/replacement, mode-boundary change, pointer-like dereference, refcount call, or retained identity is directly observed. B identifies which of a typed scalar, pointer-backed object, or owner-backed field must be modeled; it does not by itself select a class or mode ID.

### Interpretation

A validates only the opaque by-value mechanics for the captured window. B is architecture-changing and keeps `BLOCKER-B` open until writer, field type, publication/freshness, replacement, teardown, and consumer ownership are all covered. A single value without producer and consumer paths does not resolve the blocker.

### Failure conditions

- The source or forwarded field is not positively observed.
- A value is dereferenced without receiver provenance.
- Producer and consumer records are joined by temporal proximity rather than stable identity.
- A static negative scan is promoted to absence of computed writers.
- A watchpoint is treated as proof of a particular write instruction.
- Any write, hook, message injection, or payload dump is required.

### Cleanup

Remove bounded watchpoints/breakpoints, release the lock, teardown the process, retain scalar/identity/order records only, and leave the opaque contract and unresolved publication questions unchanged.

## RE-04 — App message queue ABI and mode-announcement bridge

**Status:** **PROPOSED / UNVERIFIED**  
**Execution:** Human-only; one fixed pre-approved UI/mode action.  
**Current evidence:** Immediate registry traversal, separate `0x14` registration Entry and `0x18` deferred delivery record, targeted post paths, and mode IDs/order are `VERIFIED` or `CONFIRMED` statically; live timing, priority direction, cancellation, thread affinity, and reentrancy are `UNKNOWN`.  
**Evidence target:** Direct entry/queue/callback records can produce `OBSERVED` queue timing; no universal payload ABI is inferred.  
**Architecture blockers resolved:** Event-timing residual under DEC-02/03; supports mode-axis evidence for RE-18.

### Hypothesis A

The App manager is a family-specific transport with `0x14` registration entries, separate `0x18` deferred records, immediate `MessageSend` traversal, targeted `MessagePost`/`MessagePostFunction`, conditional retain/release, and a distinct mode-announcement bridge at `0x00B63510`. StandardMessage, UTFWin, editor animation, Cell interaction, deferred, and Space records remain separate families.

### Hypothesis B

The same record/key crosses families, a listener return cancels later delivery, removal cancels queued delivery, a domain payload is retained unexpectedly, or Simulator mode state commits before the expected callback boundary. Cross-family ownership/timing/cancellation must then be specified explicitly.

### Required setup

- Require RE-01 and a prepared disposable profile or other legitimate, non-secret route past registration.
- Pin probes around `0x00884100`, `0x00884550`, `0x008841F0`, `0x00884700`, `0x00885710`, `0x00885890`, `0x00885930`, `0x008853E7`, `0x008854A0`, and mode listener `0x00B63510`.
- For each record capture registration/queue address, record size, listener/handler/context identity, message ID, payload pointer/size/hash, priority/key raw bits, thread, insertion/processor time, callback result, release, and mode ID.
- Declare start at the attributable input/request and end at a fixed app-update count plus a `queue_drained` marker. Do not inject a message.

### Intervention

Issue one fixed UI action that naturally requests a mode transition. Observe registration, immediate send, deferred post, callback-produced posts, mode-exit `0x0212D3E7`, mode-enter `0x022D1ADC`, listener commits, and the next queue pass.

### Observable outcome A

Immediate callbacks complete before send return; deferred records are physically distinct from registration entries; priority/tie order, targeted versus handler/context delivery, snapshot versus drain behavior, release order, and Simulator payload/commit writes are all timestamped. A validates the existing family-separated transport boundary for this path.

### Observable outcome B

A record or key crosses family boundaries, callback return/removal changes queued delivery, a payload outlives its declared owner, or commit order differs from the captured callback contract. B requires an explicit cross-family ABI decision and invalidates any universal-total-order assumption.

### Interpretation

A does not merge domain payload layouts or establish global ordering. B must be based on direct producer/consumer identity, not equal record sizes, common processors, or fan-in. A frame-only or menu-visible result remains a UI/frame negative.

### Failure conditions

- No attributable input, mode request, message record, or processor event is captured.
- A family is assigned solely because it passes through a common processor.
- Screenshot/UI response substitutes for callback/resource order.
- Queue-key units, signed zero, thread affinity, reentrancy, or unresolved `0x008853B0` is invented.
- Capture horizon ends without a queue marker and absence is treated as proof.
- Message injection or binary modification is required.

### Cleanup

End the fixed-input walk through the emergency stop, restore breakpoints, release the lock, teardown, and preserve the raw queue/lifecycle order and exact negative reason. Keep family IDs separate in the artifact.

## RE-05 — Persistence object/reference graph and failure behavior

**Status:** **PROPOSED / UNVERIFIED**  
**Execution:** Human-only; disposable profile and save directory; explicit save/load approval.  
**Current evidence:** Local Property framing, ClassSerializer callbacks, stable-reference/deferred-association boundary, and temp/close/replace candidates are `SUPPORTED`/`VERIFIED` statically. Outer envelope, object table, cycles, migration, rollback, and complete field graph are `UNKNOWN`.  
**Evidence target:** A byte-position/object-identity matrix tied to an actual save/reopen can produce `OBSERVED`; it does not by itself prove compatibility.  
**Architecture blockers resolved:** `BLOCKER-C` persistence graph and transaction design; COND-05.

### Hypothesis A

`PropertyList::Write/Read` and ClassSerializer callbacks implement a versionable local object graph with stable identities, deferred association, bounded cycle handling, first-failure short-circuiting, and explicit temp/close/replace. Live pointers and presentation state remain outside the graph.

### Hypothesis B

The format requires a distinct object table, parent/cycle encoding, runtime-populated descriptor graph, outer checksum/compression/envelope, migration/default path, multi-file transaction, or partial-state failure behavior. A separate schema/recovery design is required.

### Required setup

- Require RE-01 and an explicitly approved disposable profile/save root. Record the prefix/save directory identity and verify canonical `SPORE/` and the original profile are read-only.
- Pin `0x006A1540`, `0x006A2F60`, `0x00692900`, `0x00693E10`, `0x00692880`, `0x00692F90`, `0x00B26800`, `0x00B26840`, `0x00B274E0`, `0x00B279E0`, `0x00B28EC0`, and `0x006891F0` when reached.
- Capture only bounded metadata: stream open/write/read/fail positions, counts, object identity tokens, parent branches, descriptor/class IDs, attribute callback order, temp/final paths, sizes, hashes, and close/replace outcomes. Do not retain payload bytes.
- Any failing-stream or cyclic branch requires a separately approved disposable copy; do not alter a save after the run to simulate failure.

### Intervention

Perform one explicit save and reopen/load round trip. If naturally and safely reachable without file mutation, exercise one cyclic or preapproved failing-stream branch. Do not inject pointers, call serializer code synthetically, or alter serializer implementation.

### Observable outcome A

The artifact yields a field/object/association matrix with object tokens preserved or remapped by a stated rule; cycles/deferred references have bounded outcomes; the first stream failure short-circuits deterministically; and temp→close→replace has explicit success/failure state. A supports a schema/reference/transaction architecture.

### Observable outcome B

The trace exposes a separate object table, parent/cycle bytes, checksum/compression/outer envelope, migration/default behavior, cross-file commit, or partial restoration after failure. B requires a separate schema and recovery design; no byte-compatible claim is permitted without a retained byte fixture policy.

### Interpretation

A supports the interim architecture but is not proof of original `.spo`/`.prop` byte compatibility. B identifies architecture portions that are provisional. If save/load is unreachable, the result is a reachability negative and `BLOCKER-C` remains open.

### Failure conditions

- Canonical profile, `SPORE/`, canonical KG, or executable is modified.
- Proprietary payload or memory dump is retained.
- Decompilation or a host fixture substitutes for an actual stream event.
- Failure is simulated by changing the target after capture.
- A field is called durable without surviving reopen.
- Callback order is called a complete object graph.
- `0x00B28EC0`/`0x00B279E0` are called `cGamePersistenceManager` members without this-binding/service-routing evidence.

### Cleanup

Close all streams, close the disposable profile, verify canonical files unchanged, release the lock, teardown, and retain only bounded schema/order/hash observations and exact failure outcomes.

## RE-06 — Mode handoff, automatic save, and restore ownership

**Status:** **PROPOSED / UNVERIFIED**  
**Execution:** Human-only; positive Cell/mode reachability and disposable save state.  
**Current evidence:** Cell `OnExit`/`Dispose` and in-memory serializable handoff are `SUPPORTED` statically; no runtime teardown save, restore owner, or automatic checkpoint is observed.  
**Evidence target:** A serializer/file timeline can establish automatic versus explicit persistence for the captured transition.  
**Architecture blockers resolved:** `BLOCKER-C` mode handoff and autosave; membership of `cGamePersistenceManager` remains separate.

### Hypothesis A

Ordinary `OnExit`/`Dispose` releases transient mode/presentation state without an automatic durable write. An explicit save boundary emits `cCellSerializableData`; restore constructs a new live owner and rebuilds presentation separately.

### Hypothesis B

Mode teardown triggers a save/checkpoint, transfers a live serializable object or DTO, or the persistence service restores the same live identity. Automatic mode persistence or transfer semantics then become part of the architecture.

### Required setup

- Require RE-07, RE-05, and an approved disposable profile.
- Correlate `0x00E7FC00`, `0x00E81F30`, `0x00E51300`, `0x00E51370`, `0x00E61550`, `0x00E63D10`, `0x00E80BA0`, `0x00B3D440`, `0x00B28EC0`, and `0x00B279E0` when reached.
- Record mode owner, `sCellGame` identity, pool/avatar identity, `cCellSerializableData` pointer/field hashes, serializer callbacks, file events, service receiver/vtable evidence, and restored owner identity.
- Declare one explicit-save branch and one no-extra-save teardown branch. Do not equate a mode entry with restore.

### Intervention

In one bounded sequence, perform an explicit save, then exit/dispose without invoking another save, then restore/reload through the approved UI/service. Record whether any file or serializer event occurs during teardown.

### Observable outcome A

The explicit-save interval contains serializer and temp/close/replace events; the teardown interval contains none; restore creates a new live Cell/runtime owner; presentation is rebuilt separately. A supports transient live state plus an explicit serialized handoff.

### Observable outcome B

`OnExit`/`Dispose` contains a serializer/file write, a live pointer/DTO crosses the boundary, or restore recreates the same object/owner identity. B supports automatic persistence or transfer and requires an explicit mode-handoff protocol.

### Interpretation

A does not prove that no other path can save Cell state. B does not prove `cGamePersistenceManager` membership without concrete receiver/vtable/service routing. A missing save event inside the declared horizon is `not_observed_in_capture`, not universal absence.

### Failure conditions

- Save is inferred from teardown without serializer/file events.
- Pointer equality is used across process restart without an identity protocol.
- Canonical profile or executable data changes.
- A serializer callback is called an automatic save without a checkpoint.
- Restore is accepted solely because a mode entered.
- The same live object is compared across a process boundary without a declared mapping.

### Cleanup

Close the disposable profile, verify canonical state unchanged, release the lock, teardown, and retain the exact save/teardown/reload timeline. Do not promote autosave or persistence-manager membership.

## RE-07 — Cell reachability control

**Status:** **PROPOSED / UNVERIFIED**  
**Execution:** Human-only and human-watched; legitimate prepared disposable profile; fixed reviewed input only.  
**Current evidence:** Eleven Cell probes are byte-verified statically. Historical `entry`-only/generic-frame runs did not reach Cell; `FUN_0069B600` is explicitly not a Cell marker.  
**Evidence target:** A correlated Cell lifecycle/update pair can produce `OBSERVED` Cell reachability; B remains a precise navigation/boot/registration negative.  
**Architecture blockers resolved:** None by itself; unblocks RE-08 through RE-10, RE-13 through RE-15, and RE-19.

### Hypothesis A

A naturally navigated Cell mode produces a correlated pair such as `cCellModeStrategy::OnEnter` at `0x00E552F0` and `Update` at `0x00E80980`/real update body `0x00E806B0`, after the bootstrap control and in the same traced module-host lineage. The target call may subsequently become eligible for a dedicated oracle.

### Hypothesis B

The process exits/stalls, registration blocks navigation, only the bootstrap or generic frame helper fires, or a non-Cell event is misclassified. Cell remains unobserved and all Cell-dependent hypotheses stay blocked.

### Required setup

- Require RE-01 outcome A, atomic lock, human emergency-stop readiness, and a human-prepared disposable profile that avoids credential entry/logging.
- Bind the window to module-host PID plus generation marker/WM_CLASS/geometry; explicitly record missing `_NET_WM_PID`.
- Require all `cell_movement.json` probes active. Exclude `FUN_0069B600` as a classifier. Use focused-window input only and a reviewed menu plan.
- Correct the current shell gaps first: atomic lock, complete child/operation deadlines, output-open-before-probe check, fail-on-partial instrumentation, real monotonic screenshot correlation, and always-emitted manifest.

### Intervention

Follow the fixed approved navigation plan to Cell without writing state. Stop at the first positive Cell-specific pair or at the declared timeout/stop condition.

### Observable outcome A

Raw JSONL records `entry` before `OnEnter`, `OnEnter` before active `Update`/`0x00E806B0`, all Cell probes active with zero unexplained drops, correct module identity, and process survival through the Cell observation. A establishes reachability only.

### Observable outcome B

The manifest records the exact blocked phase: boot/window, registration/profile, fixed-input navigation, partial probes, target event absence, early exit, or timeout. Only generic `FUN_0069B600`/frame activity yields `menu_only`, not Cell.

### Interpretation

Outcome A permits Cell owner/lifecycle experiments; it does not prove movement, gameplay, presentation, or save behavior. Outcome B blocks those experiments and does not support a semantic conclusion about Cell.

### Failure conditions

- Any Cell probe is inactive, skipped, or ambiguously retired without coverage accounting.
- A screenshot, registration response, menu frame, or `FUN_0069B600` marks Cell reached.
- Input is free-form, credential-bearing, unreviewed, or not bound to the traced window/process.
- The shell reports `completed` after the traced process has exited.
- A zero-event run is summarized as proof that Cell behavior is absent.

### Cleanup

Stop before any state intervention, restore probes, release the lock, verify no stale processes, and preserve the raw positive or exact negative manifest. Do not alter the historical negative record.

## RE-08 — Cell lifecycle and pool identity

**Status:** **PROPOSED / UNVERIFIED**  
**Execution:** Human-only; read-only Cell lifecycle observation after RE-07.  
**Current evidence:** Initialize/OnEnter/Update/OnExit/Dispose, 4096-entry pool initialization, allocation, query, and despawn mechanics are `SUPPORTED`/`VERIFIED` statically. Runtime identity and order are unobserved.  
**Evidence target:** A correlated pool/object/lifecycle trace can produce `OBSERVED`; B requires a joint owner graph.  
**Architecture blockers resolved:** DEC-08 Cell simulation/presentation/save ownership and pool identity.

### Hypothesis A

A pooled `cCellObjectData`/player index remains stable through natural GFX/UI detach, preload, and presentation changes, while `Initialize`, `OnEnter`, `Update`, `OnExit`, and `Dispose` retain distinct roles.

### Hypothesis B

Presentation release, display stop, despawn, or mode teardown changes or releases the gameplay pool identity in lockstep with GFX/UI. Simulation and presentation require a joint owner/lifecycle graph.

### Required setup

- Require RE-07 and a renderer marker.
- Pin `0x00E81CF0`, `0x00E552F0`, `0x00E80980`, `0x00E806B0`, `0x00E7FC00`, `0x00E81F30`, `0x00E80BA0`, `0x00E74A20`, `0x00E780A0`, `0x00E7FD00`, and `0x00E6D8F0` as applicable.
- For every sample record `sCellGame+0x411C`, resolved object address, self-index `+0x00`, bounded object hash, GFX index `+0x248`, query pointer `+0x35C`, scale `+0x358`, health `+0x244`, reload flags `+0x51D8/+0x51D9`, and GFX attach/detach/rebuild event.
- Do not force pool exhaustion or write reload/death fields.

### Intervention

Observe natural Cell entry, several bounded frames, one normal display/presentation transition if available, and exit. Record allocation/release and GFX/UI events on one monotonic timeline.

### Observable outcome A

The same pool index/object address/hash survives presentation changes while GFX/UI handles change independently; lifecycle events occur in captured order; a reload drains/recreates presentation and gameplay state as separate events. A supports a stable simulation identity.

### Observable outcome B

A GFX/UI event changes the player/pool index, releases the gameplay object, or teardown releases gameplay and presentation in inseparable lockstep. B requires an explicit joint Cell/GFX owner graph.

### Interpretation

A is conditional on object hash and generation status. B exposes coupling but does not make presentation the gameplay authority. Free-list sentinel, generation reuse, and indirect service ownership remain unknown unless directly observed.

### Failure conditions

- Pool index and resolved object are collapsed into one identity.
- GFX/UI events are treated as gameplay state without a stable correlation.
- A reload, despawn, or death is synthesized.
- Object address reuse is called stable identity without generation evidence.
- Only generic frame/menu events are available.

### Cleanup

Stop at the approved Cell boundary, restore probes/watchpoints, release the lock, teardown, and retain the bounded identity/handle/order table. Do not alter the negative Cell record.

## RE-09 — Receiver-typed avatar ownership and replacement

**Status:** **PROPOSED / UNVERIFIED**  
**Execution:** Human-only; naturally reachable noun-layout receiver and, if possible, Space receiver comparison.  
**Current evidence:** `+0x54` raw read and AddRef-new/store-new/Release-old replacement mechanics are `VERIFIED` statically; the exceptional `DAT_016DC0FC` receiver exposes high-LOD planet state. Global “GetAvatar” typing is rejected.  
**Evidence target:** Receiver/value/refcount records can produce `OBSERVED` receiver-specific behavior.  
**Architecture blockers resolved:** DEC-07 receiver-typed avatar boundary; supports `BLOCKER-A` consumer semantics without claiming root equality.

### Hypothesis A

For a noun-layout receiver, `0x00B1FDB0` exposes a current gameplay-creature selection at `receiver+0x54`, and `0x00B1FD50` performs equal-address no-op, AddRef-new/store-new/Release-old replacement, and null clear.

### Hypothesis B

`+0x54` is receiver-specific. A reachable receiver, including the `DAT_016DC0FC`/high-LOD planet path, exposes a non-avatar object or a different lifetime, so a global avatar pointer/owner is invalid.

### Required setup

- Require a naturally reachable noun-layout receiver; record receiver type/provenance before reading `+0x54`.
- Pin `0x00B1FDB0`, `0x00B1FD50`, the current noun/player identity, object identity/hash, `+0x54` before/after, and observed AddRef/Release/vtable events.
- If reachable, cover `0x00BFF2D0`/`DAT_016DC0FC` and active star/planet identities as a separate receiver class.
- Do not dereference an unproven returned value or force equal/null/replacement paths.

### Intervention

Use natural current-creature/player selection or replacement actions. Capture same-object, replacement, and null/teardown paths only if the approved UI produces them.

### Observable outcome A

The noun-layout receiver carries a stable current gameplay-creature identity; replacement acquires the new reference before storing and releases the old afterward; equal and null outcomes are distinguishable. A supports borrowed receiver-typed ports.

### Observable outcome B

A different receiver exposes a stable non-avatar identity, `+0x54` is not an intrusive gameplay object, or reference/lifetime behavior differs. B preserves receiver qualification and forbids a global `GetAvatar` interface.

### Interpretation

A does not merge Cell pool, Space planet, presentation GFX, or serializable identity. B is a boundary result, not a receiver-contract failure. One reachable receiver cannot resolve all receiver classes.

### Failure conditions

- Receiver provenance is absent or inferred after dereferencing.
- Return-value use is treated as proof of ownership.
- Cell, planet, GFX, and noun identities are compared without owner qualification.
- A null/equal path is forced by a direct write.
- The stage is unreachable but an avatar conclusion is recorded.

### Cleanup

Restore breakpoints, release the lock, teardown, and retain receiver/value/refcount observations only. Leave noun, planet, Cell, GFX, and save identities separate.

## RE-10 — Cell gameplay/presentation interaction boundary

**Status:** **PROPOSED / UNVERIFIED**  
**Execution:** Human-only; one approved interaction or one natural display/effect transition.  
**Current evidence:** Health/death writes, queued interaction dispatch, GFX/effect/animation calls, and separate service structures are `SUPPORTED` statically. No original Cell interaction is observed.  
**Evidence target:** A direct state/event timeline can establish presentation independence or required coupling.  
**Architecture blockers resolved:** DEC-08 gameplay/presentation boundary; Cell interaction/UI coupling residual.

### Hypothesis A

Gameplay mutation, interaction dispatch, health/death, and query/pool identity are authoritative before or independently of GFX preload, effects, animation, health rollover, and renderer submission. Presentation can be detached/rebuilt without owning gameplay state.

### Hypothesis B

A renderer/effect/UI event is required for a gameplay transition, mutates authoritative pool/avatar/health state, or the gameplay event exists only while a presentation instance is live. A joint simulation/presentation contract is then required.

### Required setup

- Require RE-07, a stable renderer marker, pinned window, and one human-approved bounded interaction trigger.
- Pin `0x00E7E6C0`, `0x00E7E130`, `0x00E63560`, `0x00E66840`, `0x00E6D200`, `0x00E62340`, `0x00E55120`, `0x00E666F0`, and the health/death paths `0x00E7A7C0`/`0x00E7A4A0` when reached.
- Record interaction raw type `+0x24`, timer, health/death fields, pool/avatar identity, effect instance, animation/UI event, GFX handle, frame ID, and thread on one timeline. Do not capture effect/model payloads.

### Intervention

Trigger exactly one natural Cell interaction. If no interaction is safely reachable, observe one natural display/effect transition without injecting damage, death, or state.

### Observable outcome A

A gameplay mutation and interaction dispatch are timestamped before or independently of GFX/effect/UI operations; pool/avatar identity remains stable while presentation handles create/stop/replace/release. A supports the existing separation.

### Observable outcome B

Presentation is required for the gameplay event, changes authoritative health/pool/avatar state, or gameplay ceases when presentation is absent. B requires explicit joint ownership and callback order.

### Interpretation

A does not establish original pixels, materials, animation content, or effect payload schemas. B requires a new boundary only when direct state/event order proves feedback or ownership. A visual effect alone is insufficient.

### Failure conditions

- No attributable Cell event or interaction occurs.
- Raw effect/animation types are assigned semantic names without payload evidence.
- Renderer calls are treated as gameplay calls.
- Damage/death is injected by a direct write.
- Host OpenSpore timing is used as original ordering.

### Cleanup

Stop before replacement or renderer intervention, restore probes, release the lock, teardown, and retain the bounded state/presentation timeline. Keep visual outcomes proposed.

## RE-11 — Star/empire lookup, cache, and Space context lifecycle

**Status:** **PROPOSED / UNVERIFIED**  
**Execution:** Human-only; positive Space navigation only.  
**Current evidence:** Lower-bound/ceiling lookup, successor-tolerant cache validation, active star/planet binding, and context enum are `SUPPORTED`/`CONFIRMED` statically. No Space runtime trace exists.  
**Evidence target:** Lookup, cache refresh, context, and owner-teardown records can produce `OBSERVED`; semantic map values remain opaque.  
**Architecture blockers resolved:** `BLOCKER-A` star half; DEC-05 and Space/terrain owner handoff.

### Hypothesis A

`0x00E5C780`/`0x00BA9370` perform unsigned lower-bound/ceiling lookup; `0x01021300` validates player/political identity and refreshes the empire cache; star, empire, `SpaceContext`, active planet/star, and graphics objects have distinct owners and lifetimes.

### Hypothesis B

Lookup requires exact identity, cache results are reused across incompatible owners, star/empire roots are rebound as one graph, or terrain/graphics creation is required to interpret gameplay state. A phase-specific registry and handoff model is then required.

### Required setup

- Require RE-02 and positive Space reachability. If Space is unreachable, stop with a stage-reachability negative.
- Pin `0x00E5C780`, `0x00BA9370`, `0x01021300`, `0x00B3D2A0`, `0x00B25FB0`, `0x01021960`, `0x010219B0`, `0x00C8B6B0`, `0x00C8D060`, `0x00C86760`, and `0x00C86E00` as reached.
- Record lookup key, predecessor/successor/result, empire political ID `+0x84`, cache pointer, AddRef/Release/replacement, active star/planet, `SpaceContext` values `-1/0/1/2`, and terrain/graphics object identity.

### Intervention

Use approved Space navigation to select different existing stars/planets, change context, and return/tear down the stage. Observe a natural cache miss/refresh or owner replacement. Do not alter keys, caches, or pointers.

### Observable outcome A

A non-exact key returns the recorded successor, cache refresh occurs when player/political identity differs, map/cache/terrain owners tear down independently, and `SpaceContext` remains distinct from presentation objects. A supports lower-bound and owner-qualified contracts.

### Observable outcome B

Lookup requires exact key equality, a cache result is reused after incompatible identity, root/terrain/graphics owners are coupled, or graphics creation is required for gameplay interpretation. B requires a phase-specific registry/handoff design.

### Interpretation

A does not assign semantic meaning to every map value. B does not prove a star root pointer or graphics ownership. Without a positive Space event, the star/cell/terrain relationship remains unresolved.

### Failure conditions

- Lower-bound is called exact-find without a successor record.
- Cache, star, planet, or renderer identities are conflated.
- A miss is induced by direct modification.
- SDK names or one predicate are used as runtime evidence.
- Space is unobserved but a stage claim is recorded.

### Cleanup

Exit the approved Space observation, restore probes, release the lock, teardown, and retain the bounded lookup/cache/context/owner table. Do not mutate map/cache state or the shared-root register.

## RE-12 — Deferred scheduler, pause/speed, and App queue separation

**Status:** **PROPOSED / UNVERIFIED**  
**Execution:** Human-only; naturally occurring deferred event and bounded pause/speed action.  
**Current evidence:** `cGameTimeManager` fields, `tDeferredEvent` shape, and App timing surfaces are `CONFIRMED`/`SUPPORTED`; scheduler owner, epoch, ordering, cancellation, and native pause/speed conversion are `UNKNOWN`.  
**Evidence target:** Direct due/callback/time-state records can establish a distinct timing substrate.  
**Architecture blockers resolved:** Event-family ordering residual; no immediate DEC-02/03 change without direct cross-family evidence.

### Hypothesis A

`cGameTimeManager`, `tDeferredEvent`, and `ScheduledTaskListener` form a timing substrate with a traceable epoch, pause/speed conversion, due time, duplicate, expiry, cancellation, and callback policy independent of App registration order.

### Hypothesis B

Deferred domain records are delivered only through the App processor or share its ordering/cancellation key and delivery contract. Scheduler and transport are architecturally coupled.

### Required setup

- Require RE-04 and a naturally due deferred/scheduled event. No delay injection.
- Pin `0x00B3D480`, `0x00B32330`, `0x00B32390`, `0x00B321E0`, `0x00B32560`, `0x00B31DA0`, `0x00B63980`, the 28-byte `tDeferredEvent`, and App processor markers.
- Record trigger time, scheduler epoch, pause/speed fields, queue placement, callback, callback-produced post, duplicate/expired/cancelled result, and thread ID.

### Intervention

Observe natural pause/speed changes and one delayed callback over bounded frames. Do not force duplicate, expiry, or cancellation unless an existing approved path naturally produces it.

### Observable outcome A

The deferred record is physically and temporally separate from the App queue, has trigger/epoch/callback identity, and timing changes with captured game-time state without inheriting App registration order. A supports a distinct scheduler interface.

### Observable outcome B

The record is delivered only through the App processor, shares its ordering/cancellation key, or callback timing follows App queue drain behavior. B requires a coupled scheduler/transport design and direct family evidence.

### Interpretation

A does not establish fixed stepping, signed-zero behavior, or a complete scheduler owner. B must distinguish record-shape similarity from actual cross-family ABI. No scheduler class is named solely from SDK layout.

### Failure conditions

- No naturally due event is observed.
- App timestamp and SDK trigger time are conflated.
- Pause/speed is inferred from a field without a corresponding delta/callback.
- Duplicate, expiry, or cancellation is invented.
- A generic frame is counted as a scheduled callback.

### Cleanup

Stop at bounded completion, restore breakpoints, release the lock, teardown, and retain the timestamped timing/family table. Keep scheduler and App records separate.

## RE-13 — Cell movement ABI, return, direct writes, and callee side effects

**Status:** **PROPOSED / UNVERIFIED**  
**Execution:** Human-only; dedicated entry/return/memory oracle, never the entry-only observatory schema.  
**Current evidence:** Target identity, `void(float)`, one-float stack slot, plain `RET`, direct call-site bytes, direct stores, and physical moving-byte path are `VERIFIED` statically. Runtime reachability and live field meanings are unobserved. The `0x016B3C04`/`0x116B3C04` conflict is unresolved.  
**Evidence target:** Paired entry/continuation, ABI, state, and write records can produce `OBSERVED`; partial coverage remains `partial_write_coverage`.  
**Architecture blockers resolved:** Movement ABI/side-effect blocker; prerequisite to any Cell replacement. No replacement is performed.

### Hypothesis A

At the direct call site `0x00E8083B` (`e8 50 af fd ff`), target `0x00E5B790` receives the exact `float` at `[ESP+4]`, returns through continuation `0x00E80840` with a balanced stack, resolves the player through the pool index, applies the statically identified guard/ray-plane/orientation behavior, and writes only the declared target/orientation/moving state plus the declared callee effects.

### Hypothesis B

The target is unreachable; the caller/continuation or stack contract differs; guards suppress the call; callees mutate additional whitelisted state; or direct/side effects differ from the static minimum. Entry-only evidence remains insufficient.

### Required setup

- Require RE-07, address-conflict reconciliation, and a dedicated disposable-process oracle with exact call/return pairing, watchpoints, store probes, guard windows, and coverage reporting.
- Pin linked VA `0x00E5B790`, PE RVA `0x00A5B790`, file offset `0x00A5AB90`, entry bytes `a1 04 3c 6b 01`, call site/continuation, module base, and plain `RET` at `0x00E5BA01`.
- Capture all general registers, `EFLAGS`, `[ESP]`, `[ESP+4]`, thread, caller, return address, and float raw bits. Pair entry and continuation by thread/call ID.
- Whitelist `sCellGame` slot `0x016B3C04`, lock `+0x5158`, pool index `+0x411C`, serializable pointer `+0x5190`, physical moving byte `u32[sCellGame+0x5190]+0xE0`, gates `+0x515C/+0x51E0`, plane point `0x016B3C28..34`, normal `0x015A7C40..4C`, and resolved player target/orientation/current/guard fields.
- Pin direct store probes at `0x00E5B97A/7D/80`, `0x00E5B98E`, and `0x00E5B9E4/EA/F0/F6`; cover selected callees `0x00E5B2E0`, `0x00743B50`, `0x00E82130`, `0x007C4900`, and `0x0069B600` without assuming `FUN_0069B600` is Cell-exclusive.

### Intervention

Observe natural active frames for a bounded number of calls. No target-state write, replacement code, injected call, or synthetic plane/camera value is permitted.

### Observable outcome A

For each call ID, entry `[ESP]=0x00E80840`, `[ESP+4]` equals the raw caller float, direct writes match the pinned store PCs/widths, moving state is the physical `+0x5190` pointer plus byte `+0xE0`, and the continuation is reached with expected `ESP`/callee-saved values. All required fields/callees have direct or explicitly partial coverage. A validates the live ABI/window for that run.

### Observable outcome B

The target is not reached; the observed frame/call site differs; a guard or null path returns without the expected sequence; a direct store is absent/different; or a covered callee changes additional state. B identifies which static contract or field meaning must be revised and is not normalized into A.

### Interpretation

A validates only the captured call path and scenario. Raw-bit equality is primary for float/state comparison; it does not establish semantic field names. Snapshot deltas without store evidence are not exact write sites. Partial coverage cannot support replacement parity.

### Failure conditions

- The `sCellGame` address conflict is ignored or runtime module mapping is unpinned.
- Entry is captured without a paired continuation/return.
- Moving state is flattened as `sCellGame+0x5270` instead of the resolved pointer-plus-byte path.
- Snapshot delta is called an exact write.
- A callee or field is omitted without `partial_write_coverage`/`not_observed`.
- The existing entry-only tracer is treated as an ABI oracle.
- Any code or state write is used to manufacture a call.

### Cleanup

Remove all breakpoints/watchpoints, verify no debug-register residue, release the lock, teardown the disposable process, and retain the bounded ABI/state/write table. Do not patch or install a replacement.

## RE-14 — Mouse/camera causality for movement

**Status:** **PROPOSED / UNVERIFIED**  
**Execution:** Human-only; fixed pointer waypoint plan after RE-13.  
**Current evidence:** Cell `OnMouseMove` at `0x00E51010`, camera-source helper, camera-mode getter, ray-plane stores, and input offsets are `SUPPORTED`/`VERIFIED` statically. No original mouse/movement order is observed.  
**Evidence target:** A fixed input-to-camera-to-target sequence can produce `OBSERVED` causality.  
**Architecture blockers resolved:** Movement input contract and independent mode/input axis residual.

### Hypothesis A

A focused-window pointer waypoint reaches Cell input, updates the input manager/mouse state, is consumed with the captured camera origin/direction and movement-plane values, then causes the target/orientation/moving stores in the next attributable target call.

### Hypothesis B

Pointer input is consumed by another mode, the camera source/mode is independent or stale, target stores occur without the pointer event, or the host's keyboard/camera approximation is mistaken for original behavior.

### Required setup

- Require RE-13, a stable pinned window, and a pre-approved pointer waypoint sequence with monotonic timestamps.
- Pin `0x00E818F0`, `0x00E51010`, `0x00E7D660`, input manager `DAT_0167EAF8`/`0x00B3D350`, `0x00E4CE40` and `+0xD4`, `0x007C4900`, `0x00E5B790`, and plane/player state from RE-13.
- Record pointer coordinates/state, mode axis, input-manager fields, camera origin/direction raw bits, plane point/normal, target/orientation/current/moving before/after, and call/frame ID.

### Intervention

Move the pointer through fixed, reviewable waypoints with dwell intervals; observe one target call per attributable interval. Do not alter camera or plane state and do not use host OpenSpore input as an oracle.

### Observable outcome A

For each waypoint, the raw timeline is `OnMouseMove/input update → camera source/mode sample → target entry → target/orientation/moving stores → continuation`, and changed target values are numerically consistent with the captured ray/plane data. A supports mouse-steering causality for that camera/mode window.

### Hypothesis B

The event order is absent, belongs to a different mode, is dominated by generic frames, or camera/plane values do not explain the stores. B keeps mouse/camera semantics unresolved and prevents host approximation promotion.

### Interpretation

A supports causality but does not prove all camera modes, smoothing, collision, or movement integration. B may indicate mode routing, a missing camera dependency, or an unobserved path; it does not select among them without direct evidence.

### Failure conditions

- Pointer event is not bound to the traced window/process and monotonic time.
- Screenshot position substitutes for raw pointer/input state.
- Camera helper activity is treated as Cell movement.
- Host orbit-camera or keyboard-thrust behavior is used as original expected behavior.
- Plane point/normal is assumed from load image rather than captured per-world bits.

### Cleanup

Stop the waypoint plan, restore probes, release the lock, teardown, and retain the fixed input, camera, target, and call timeline. Do not modify camera or movement state.

## RE-15 — Cell object/GFX detach and rebuild identity

**Status:** **PROPOSED / UNVERIFIED**  
**Execution:** Human-only; natural GFX detach/rebuild or Cell reload after RE-08.  
**Current evidence:** `+0x248` clear/release without pool release, same-object GFX reattach, despawn release, and stage rebuild bodies are `SUPPORTED`/`VERIFIED` statically. Runtime identity order is unobserved.  
**Evidence target:** Object and GFX lifecycle records can establish when gameplay identity survives presentation rebuild.  
**Architecture blockers resolved:** DEC-08 pool/presentation coupling.

### Hypothesis A

A normal GFX detach clears/releases `cCellObjectData+0x248` and presentation resources while preserving the pool object, self-index, gameplay fields, and avatar selection; reattach assigns a new GFX index to the same object. Stage reload may create a new object only after an explicit old-object release.

### Hypothesis B

Detach, scale replacement, despawn, or rebuild changes the pool/avatar identity, releases gameplay state, or makes presentation lifetime authoritative for object survival.

### Required setup

- Require RE-08 and a naturally reachable display/reload transition; do not force a scale change or death.
- Pin `0x00E66010`, `0x00E6D8F0`, `0x00E780A0`, `0x00E7FD00`, `0x00E6D8F0`, plus pool create/lookup/release events.
- For each object event record pool index, object address, self-index, bounded hash/generation status, GFX index `+0x248`, model/resource references, query pointer, scale, avatar index, and source event.

### Intervention

Observe one natural GFX detach/attach, despawn, scale replacement, or stage reload if reachable. Otherwise stop at the entry gate as a negative.

### Observable outcome A

The timeline records `same object + old GFX released → object retained → new GFX attached`, or a separately identified `old object released → new object allocated/rebound`; avatar/query/gameplay identity changes only in the latter event. A supports separate presentation and pool lifecycles.

### Observable outcome B

GFX release also destroys/releases the gameplay object, or rebuild cannot be interpreted without presentation handles. B requires a joint object/GFX owner model and explicit identity rules.

### Interpretation

A does not prove pool generation semantics or every despawn branch. B identifies coupling but does not make GFX the gameplay authority. Unknown indirect service ownership remains explicit.

### Failure conditions

- GFX index/handle is treated as gameplay identity.
- A pointer is reused across pool generations without hash/generation evidence.
- Death, scale, or reload is forced by a write.
- Static `0x00E780A0` behavior is claimed from a different path.
- No positive object event is observed.

### Cleanup

Stop before intervention, restore probes/watchpoints, release the lock, teardown, and retain the object/GFX lifecycle table. Do not write reload flags or pool state.

## RE-16 — Input, message, callback, resource, and frame ordering

**Status:** **PROPOSED / UNVERIFIED**  
**Execution:** Human-only; one fixed, attributable UI action.  
**Current evidence:** Menu/UI/message/resource/frame probe anchors exist; editor and resource paths are `SUPPORTED` statically. No menu-transition probe set has produced a positive original trace.  
**Evidence target:** A producer-consumer timeline can produce `OBSERVED` order; a frame/screenshot only remains a negative.  
**Architecture blockers resolved:** DEC-01/02/03 callback and ordering residual; supports RE-17 and RE-18.

### Hypothesis A

One fixed focused-window UI action produces an ordered, owner-qualified sequence from input through UTFWin/editor callback, App message handling, resource request/load, and frame heartbeat, with no universal payload family or inferred screenshot state.

### Hypothesis B

Only a generic frame/resource event occurs, the input response is not attributable, the resource request has a different producer, or message/callback order cannot be paired. The experiment remains a UI/frame/resource negative.

### Required setup

- Require RE-01 and legitimate disposable-profile navigation.
- Pin `menu_transition.json` targets: editor handler `0x00591FA0`, editor mouse `0x00588570`, editor update `0x0058BE50`, message pump `0x00848210`, resource initialize `0x008DE530`, DBPF lock `0x008D84F0`, index read `0x008DBCC0`, and frame heartbeat `0x00B63980`.
- Record focused-window input pre-issuance, target window, message IDs/handlers/contexts, resource keys/cache/lease events, frame ID, and monotonic callback order. Hash screenshots but do not infer semantics from them.

### Intervention

Issue one pre-approved action and observe through a fixed frame/callback horizon. No arbitrary click, text, resource injection, or repeated action ladder.

### Observable outcome A

A single input event is followed by the attributable UI callback, message/dispatcher event, resource event where expected, and frame heartbeat with exact order and thread IDs. A bounds the event path without merging families.

### Observable outcome B

No direct input/callback pair exists, only high-frequency editor/frame events occur, resource activity is unrelated, or timestamps cannot be shared. B is classified exactly as frame-only, resource-only, partial, or unreachable.

### Interpretation

A does not establish payload schemas or global order. B does not imply absent callback behavior. Visible response and screenshots remain annotations.

### Failure conditions

- Input is not pre-issued, reviewed, and bound to the traced window.
- Frame activity is counted as a semantic transition.
- Screenshot change substitutes for a raw callback/event.
- Resource and message families are merged by shared timing.
- Capture lacks a common monotonic clock or end marker.

### Cleanup

Stop the fixed action, restore probes, release the lock, teardown, and preserve input/event/resource/frame order and the exact negative reason.

## RE-17 — Resource-key/cache/lease versus GFX presentation boundary

**Status:** **PROPOSED / UNVERIFIED**  
**Execution:** Human-only; one attributable Cell resource/preload/display transition.  
**Current evidence:** Full ResourceKey manager/provider identity, cache-before-fallback, record lease, Cell local pair, preload, and display layers are `SUPPORTED`/`VERIFIED` statically. Runtime precedence, eviction, async, and display order are unobserved.  
**Evidence target:** A key-to-cache/lease/runtime/display timeline can establish layered identity and causality.  
**Architecture blockers resolved:** DEC-09 and Cell presentation/content boundary.

### Hypothesis A

A full `(type, group, instance)` ResourceKey is resolved through cache/database/factory/record-lease layers, then retained by Cell GFX preload and activated for display. Cell local pair identity, cache key, record lease, runtime object, and presentation handle remain distinct.

### Hypothesis B

Cache key, record, Cell pair, runtime object, and GFX handle are treated as one identity; resource precedence/eviction is required for gameplay; or display creation feeds back into content identity.

### Required setup

- Require RE-16 and a naturally attributable resource request/display transition.
- Pin `0x008DF460`, `0x008DA3D0`, `0x008DF9B0`, `0x008DFB20`, `0x008DE280`, `0x008DE360`, `0x008DE3B0`, `0x008DE400`, `0x00E82340`, `0x00E82420`, `0x00E666F0`, `0x00E55120`, and Cell model/resource fields `+0xFC/+0x108`.
- Record full ResourceKey, manager/provider, database/factory, cache hit/miss, record lease, Cell local pair, decoded runtime object identity/hash, preload/display event, and release. Do not retain asset payloads.

### Intervention

Observe one natural cache hit or miss, preload, display start/stop, and release if reachable. Do not flush caches, inject keys, or force an error path.

### Observable outcome A

The exact ResourceKey traverses the recorded cache/database/factory/lease path, then a distinct Cell pair/runtime/GFX object is preloaded and displayed; release is owner-qualified and presentation can be rebuilt without changing gameplay identity. A supports layered resource identity.

### Observable outcome B

The same pointer/key is required across incompatible layers, cache eviction/priority is gameplay-significant, display creation changes content identity, or resource release destroys simulation state. B requires a joint or policy-specific content/presentation architecture.

### Interpretation

A does not establish package precedence, eviction, async polling, or all failure paths. B is architecture-changing only for the directly observed coupling. Resource presence in a host fixture is not original resource behavior.

### Failure conditions

- Cache key, record, lease, runtime object, and GFX handle are conflated.
- A cache miss is induced by direct mutation.
- A host resource provider is used as an original trace.
- Asset/model/effect payloads are dumped.
- Screenshot/display presence substitutes for resource lifecycle events.

### Cleanup

Close/release resources naturally, restore probes, release the lock, teardown, and retain only keys, hashes, identities, order, and release outcomes. Do not flush or mutate original resources.

## RE-18 — Independent mode axes across a transition

**Status:** **PROPOSED / UNVERIFIED**  
**Execution:** Human-only; one naturally attributable mode transition.  
**Current evidence:** Static helper order is `old OnExit → App active-index change → mode-exit announcement → new OnEnter → mode-enter announcement`; Simulator pending/last/current, input, SpaceContext, and Cell lifecycle are separate owners. Exact runtime order/values are unobserved.  
**Evidence target:** A per-axis before/pending/after tuple can produce `OBSERVED` transition order.  
**Architecture blockers resolved:** DEC-01 mode-axis boundary; corroborates RE-02, RE-04, and RE-06.

### Hypothesis A

During transition, App active index, Simulator pending/last/current strategy, input routing, `SpaceContext`, and Cell lifecycle change independently according to their owner contracts, while the two mode announcements bridge App to Simulator without collapsing axes.

### Hypothesis B

A screenshot/global enum suggests one mode, a single owner writes all axes, commit occurs before/after the callback contract unexpectedly, or one axis remains stale across handoff. A phase-specific transition model is required.

### Required setup

- Require RE-04 and an attributable mode request.
- Pin `0x007D85B0`, `0x007D8C80`, `0x007D9120`, `0x00B63510`, `0x00B5B840`, `0x00B5B880`, `0x00B5B8A0`, `0x00B5B8C0`, `0x00B5B8E0`, `0x00B5B960`, `0x00B3D350`, `0x01021080`, and Cell lifecycle events.
- Record an owner-qualified tuple before request, after request, after old exit, after index write, after each announcement, after new enter, and after first update. Include thread and raw bits.

### Intervention

Request one naturally reachable mode transition using the same fixed action as RE-04. Do not force equal/invalid modes or inject announcement messages.

### Observable outcome A

The captured tuple distinguishes `app_active`, `simulator_pending`, `simulator_last`, `simulator_current`, `input_mode`, `space_context`, and `cell_lifecycle`; static helper order is preserved; no axis is inferred from another. A validates the separate-axis architecture for this transition.

### Observable outcome B

Two supposedly separate axes share an unproven owner/write, commit timing contradicts direct listener evidence, or a stale value survives its owner transition without an explicit rebind. B requires a phase-specific handoff/flush contract.

### Interpretation

A does not identify all raw mode values or every phase. B does not justify one global mode enum. A missing axis event within the horizon is `not_observed_in_capture`, not a default value.

### Failure conditions

- One global “mode” value is synthesized from a screenshot or partial owner.
- Static helper order is reported as observed runtime order.
- First-request-wins, last/current commit, or announcement payload words are invented.
- Same/invalid mode paths are forced by state writes.
- Cell lifecycle is inferred from a generic frame.

### Cleanup

Stop after first update and queue horizon, restore probes, release the lock, teardown, and retain the per-axis transition tuple. Do not collapse axes in the KG.

## RE-19 — Save-field survival and restoration matrix

**Status:** **PROPOSED / UNVERIFIED**  
**Execution:** Human-only; disposable profile; explicit save/reopen.  
**Current evidence:** `cCellSerializableData` 236-byte candidate, mode/progression field candidates, and serializer callbacks are `SUPPORTED`; field survival, defaults, migration, and complete descriptor graph are `UNKNOWN`.  
**Evidence target:** A field-by-field before/save/reopen matrix can produce `OBSERVED` survival for the exact captured fields.  
**Architecture blockers resolved:** `BLOCKER-C` descriptor/field survival and migration; COND-05.

### Hypothesis A

Each declared save candidate is either serialized and restored with the same owner-qualified scalar/vector meaning, or is explicitly marked `not_serialized`; absent/default fields follow a documented version/default rule. Presentation and live pointer identities are not treated as durable fields.

### Hypothesis B

A field changes value, is reset to default, is regenerated from another owner, is omitted, or appears only through a descriptor/dependency/migration path. The descriptor graph and migration policy must expand.

### Required setup

- Require RE-05 and an approved save/reopen in a disposable profile.
- Whitelist `sCellGame+0x5190`, the safe 236-byte `cCellSerializableData` candidate, player pool index, avatar/progression/mode fields explicitly approved before the run, file/temp metadata, and field hashes.
- Record for each field: source owner/address, pre-save bits, serializer callback/descriptor, in-memory post-save bits, file presence status without payload retention, reopen value, default/migration path, and new live owner identity.
- Distinguish `not_serialized`, `not_observed_in_capture`, `unreadable`, and `not_applicable`.

### Intervention

Set only naturally reachable, explicitly selected candidate fields through approved gameplay/UI; save once; reopen/load once; compare. Do not directly write save candidates or inspect proprietary payload contents.

### Observable outcome A

The matrix shows a deterministic rule for every whitelisted field: exact restore, explicit omission, or documented default/version transformation. New runtime owners are created and field identity is mapped by schema, not raw pointer. A supports the field schema for the captured version.

### Observable outcome B

At least one field changes unexpectedly, disappears, depends on an unrepresented descriptor/object reference, is generated from live presentation state, or fails migration/default handling. B requires descriptor/dependency/migration redesign and keeps `BLOCKER-C` open.

### Interpretation

A is field survival, not whole-file byte compatibility. B identifies a concrete schema expansion. In-memory equality is not persistence; file absence within a bounded horizon is `not_observed_in_capture`, not universal proof of no save.

### Failure conditions

- A field is called durable from a changed in-memory value or serializer callback alone.
- Raw pointer identity is compared across process restart.
- Proprietary save bytes are retained.
- Unapproved fields are written to create a matrix.
- Missing capture coverage is reported as `not_serialized`.
- Canonical profile or executable data changes.

### Cleanup

Close the disposable save/profile, verify canonical files unchanged, release the lock, teardown, and retain only the bounded field-survival matrix and file metadata. Do not promote byte compatibility.

## RE-20 — Positive replacement control on `App::IAppSystem::Get`

**Status:** **PROPOSED / UNVERIFIED / BLOCKED**  
**Execution:** Human-only and separately authorized. The current observatory, host replacement, and synthetic hook are not sufficient. No Cell replacement is part of this experiment.  
**Current evidence:** Control identity, linked VA `0x0067DCC0`, PE RVA `0x0027DCC0`, and bytes `a1 90 d8 5f 01 c3` are `VERIFIED`; synthetic 32-bit entry-detour mechanics are `VERIFIED` only in a non-Spore fixture. A Spore install/unhook is `NOT IMPLEMENTED`.  
**Evidence target:** Mechanical/pass-through controls can become `OBSERVED`; `VERIFIED` replacement acceptance requires complete identity, return, restore, and independent review.  
**Architecture blockers resolved:** Replacement observability gate only; no Cell or gameplay architecture blocker is resolved.

### Hypothesis A

After Phase-A static identity, Phase-C native ABI acceptance, and Phase-B read-only runtime preflight all pass, a fresh disposable process can execute explicit `original`, `bypass`, `passthrough`, and optionally `replace` policies at one proven control attachment site. Passthrough returns the exact original EAX and reaches the exact caller continuation; install/restore returns the exact original bytes/protection; no Cell target is touched.

### Hypothesis B

Preflight finds byte/address/ABI/caller ambiguity, a policy cannot be isolated, the return/continuation cannot be observed, install/restore conflicts with debugger ownership, callee-saved/stack state is corrupted, or a second byte owner exists. The control remains blocked and no Spore replacement proceeds.

### Required setup

- Pass Phase A: pinned hash/PE/section mapping, `0x0067DCC0` linked/RVA/bytes, instruction boundary, exact proven call site and continuation, original callers, page/rel32 range, and no unresolved site owner.
- Pass Phase C in a controlled 32-bit harness: exact argument/return/stack contract, callee-saved preservation, reentrancy, multithread call pairing, install/restore cycles, and fault handling.
- Pass Phase B: module-host PID/path/load base, mapped original bytes, page protection, debug-register ownership, approved read whitelist, byte-identical disposable process image, isolated prefix, and declared end condition.
- Use the existing lock, human approval, physical stop readiness, fresh process per policy, and an on-disk copy whose SHA-256 must remain identical. The attachment writer and INT3 tracer must not own the same bytes.
- Select one mechanism explicitly: call-site replacement is preferred only if its exact site/caller/continuation scope is proven; otherwise entry detour is fallback. Record original bytes, protection, transaction ID, and thread-quiescence method.

### Intervention

In fresh equivalent state, run `original`, `bypass`, and `passthrough`; run `replace` only if authorized for a control return value. For each policy capture entry/return and continuation, then suspend affected threads, verify installed bytes, restore, read back original bytes/protection, remove debug state, detach, and verify the disposable image hash. Do not patch the on-disk executable or touch `0x00E5B790`.

### Observable outcome A

- `original`: control getter executes from original bytes and returns the captured global pointer bits.
- `bypass`: dispatcher executes once, original execution count is zero, stack is balanced, and the declared bypass return/continuation is exact.
- `passthrough`: original execution count is exactly one; EAX, stack delta, callee-saved registers, and continuation match baseline bit-for-bit.
- `replace`: declared control-only return differs exactly as authorized; no undeclared state delta occurs.
- All policies emit paired call/continuation records and final `restored`, original-byte readback, original-protection readback, debug-state restored, detach, and unchanged disposable-image-hash events.

### Observable outcome B

Any policy lacks paired entry/return, corrupts stack/callee-saved registers, executes original zero/twice times unexpectedly, reaches the wrong continuation, cannot restore owned bytes/protection, detects unknown byte/debug ownership, fails the native ABI row, or changes the disposable image hash. The entire control fails even if one policy appears correct.

### Interpretation

Outcome A proves only the behaviorless control harness and policy lifecycle. It does not validate Cell movement, gameplay, or the four-argument `src/replace/Replace.cpp` stand-in. Outcome B blocks all Spore replacement. Cell installation remains deferred until RE-07 and RE-13 provide live reachability, ABI, return, and memory evidence.

### Failure conditions

- Any Phase-A/B/C check is skipped, failed, or blocked.
- `0x0067DCC0` symbol/address alone is used as the attachment proof.
- The existing entry-only tracer is treated as a return oracle.
- The synthetic Linux `mprotect`/RWX method is treated as a Spore installer.
- An INT3/debug register and patch writer own the same bytes.
- The on-disk executable/copy changes, an unknown writer appears, restore is best-effort, or cleanup cannot be verified.
- A policy reuses prior state merely because bytes were restored.
- The experiment touches the Cell target or claims gameplay parity.

### Cleanup

For every policy, stop the policy call, quiesce threads, restore only installer-owned bytes, restore original page protection, verify guard window and debug state, detach, recompute the disposable image hash, verify canonical `SPORE/`, profile, KG, and executable remain unchanged, release the lock, and teardown. A failed restore is a failed experiment and must not be retried blindly.

## Completion and promotion rules

An experiment is complete only when:

1. its `Hypothesis A` or `Hypothesis B` outcome is supported by the exact declared raw observables;
2. every expected probe/channel has `observed`, `not_observed_in_capture`, `partial`, or `blocked` status with coverage;
3. identity, environment, input, process, and artifact manifests are complete;
4. negative and partial outcomes preserve their exact reason;
5. cleanup and byte/debug-state restoration are verified where applicable;
6. an independent reviewer adjudicates the result; and
7. only the directly observed scope is promoted. A boot result cannot promote Cell semantics, a Cell reachability result cannot promote movement behavior, a field round trip cannot promote whole-save byte compatibility, and a positive replacement control cannot promote Cell replacement.

## Source basis

This specification was synthesized from the following repository inputs:

- `knowledgegraph/research/runtime-oracle/candidate-experiments.md` — original candidate ordering, template, gates, and non-promotion boundary.
- `knowledgegraph/research/runtime-oracle/input-synthesis.md` — binary/address identity, historical evidence, tooling limits, current runtime gaps, and proposed M0-M6 sequence.
- `knowledgegraph/research/runtime-oracle/replacement-observability.md` — replacement phases, target manifest, exact ABI/write/state/oracle requirements, and `App::IAppSystem::Get` positive control.
- `knowledgegraph/research/runtime-oracle/automation-audit.md` — current tool safety, human-only requirements, supervision/manifest/lock/input/provenance blockers, and unattended limits.
- `docs/analysis/architecture-decisions.md` and `docs/analysis/architecture-resolution.md` — frozen semantic boundaries and exact unresolved Clusters A/B/C.
- `docs/analysis/future-research/01-architecture-blocker-1.md`, `02-architecture-blocker-2.md`, and `03-architecture-blocker-3.md` — blocker hypotheses, expected observations, and decision criteria.
- `docs/analysis/future-research/01-pkg-01-shared-state-roots.md`, `02-pkg-02-app-lifecycle.md`, `03-pkg-07-cell-movement.md`, `04-pkg-10-editor-dispatch.md`, and `06-pkg-12-sim-space.md` — package gates and stopping conditions.
- `docs/analysis/event-message-map.md` — event-family separation, IDs, dispatchers, payload limitations, and callback/update contracts.
- `docs/analysis/simulator-shared-state-interface.md` — root mechanics, lookup/cache semantics, field offsets, and no-runtime boundary.
- `docs/analysis/gameplay-state-machines.md` and `docs/analysis/gameplay-transition-map.md` — Cell, mode, Space, persistence, resource, scheduler, and lifecycle surfaces.
- `docs/analysis/dossiers/cell-movement.md` and `docs/analysis/dossiers/unknown-high/cell-object-pool-lifecycle.md` — movement and pool/GFX static evidence and unknowns.
- `docs/analysis/CELL-RUNTIME-OBSERVATION.md` and `docs/devlog/018-s5-cell-runtime-evidence.md` — historical positive startup and stable Cell-reachability negatives.
- `docs/analysis/original-exe-replacement.md` — static identity, address conflict, current entry-only tracer limit, and positive-control sequencing.
- `tools/observatory/README.md`, `tools/observatory/probes/main_menu.json`, `tools/observatory/probes/cell_movement.json`, and `tools/observatory/probes/menu_transition.json` — current tracer schema, address convention, probe inventory, and known coverage limits.
- `src/replace/Replace.cpp`, `src/replace/Replace.hpp`, `src/replace/CellGameView.hpp`, `src/sim/CellGame.cpp`, `src/sim/CellPool.hpp`, `src/apps/CellInput.cpp`, `src/apps/CellModeStrategy.cpp`, and `src/apps/CellGfx.hpp` — relevant current clean-room source inputs only. Their host interfaces, fixtures, and comments are comparison/control context, never original runtime or replacement evidence.

No statement in this document claims that a proposed experiment was executed or that the original produced the described positive outcome.
