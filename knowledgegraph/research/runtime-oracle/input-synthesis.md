# Runtime-Oracle Input Synthesis

**Date:** 2026-09-24  
**Scope:** Repository-input synthesis only. This note does not run the original, patch a binary, write the canonical KG, access `SPORE/`, or implement anything.

## 1. Bottom line

- **Current decision:** technically feasible to observe/replace the original, but no live Cell oracle and no installed Spore replacement are established.
- **Committed status:** `technically_feasible_not_implemented`; synthetic 5-byte entry detour is verified only on a native 32-bit fixture.
- **Strongest existing original evidence:** static Cell target, byte-verified probe set, decompilation-derived movement body, historical startup/menu evidence, and a committed GUI-observation shell.
- **Blocking gap:** the original has not produced a positive Cell Stage trace with entry, return, memory, and input correlation. The current tracer is function-entry-only.
- **Safe next sequence in the existing plan:** `M0` boot control, then `M1` Cell reachability/lifecycle, then `M2` read-only ABI/side-effect sampling. `M3`–`M6` are later proposed experiments. These are proposals, not evidence.

Primary synthesis inputs:

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
- `docs/REPLACEMENT-ABI.md`, `docs/REPLACEMENT-DIFF.md`
- `tools/observatory/README.md`, `tools/observatory/SCENARIO-main_menu.md`
- `docs/analysis/CELL-RUNTIME-OBSERVATION.md`
- `docs/CELL-CONTRACT.md`, `docs/CELLSTAGE-RECON.md`
- `docs/analysis/campaigns/cell-stage-campaign.md`
- `docs/analysis/dossiers/cell-movement.md` and `.json`
- `docs/analysis/dossiers/unknown-high/cell-object-pool-lifecycle.md` and `.json`
- `docs/devlog/016-gui-automation-shell.md`
- `docs/devlog/017-s4-x11-input-feasibility.md`
- `docs/devlog/018-s5-cell-runtime-evidence.md`
- `docs/devlog/019-reconstruction-phase-cell-campaign.md`

## 2. Evidence vocabulary and source precedence

The repository uses `CONFIRMED`, `VERIFIED`, `OBSERVED`, `SUPPORTED`, `INFERRED`, `APPROXIMATION`, and `UNKNOWN` (`docs/analysis/original-exe-replacement.md:9`; `docs/REPLACEMENT-ABI.md:7-9`). Decompilation is evidence, not truth. The original has no MSVC RTTI, so vtable data, SDK names, xrefs, and runtime dispatch remain separate evidence types (`knowledgegraph/research/replacement-feasibility.json:21-42`; `docs/analysis/architecture-decisions.md:1-3`).

For runtime conclusions, the committed precedence is:

1. Raw trace JSONL and run manifests.
2. Committed observatory summaries and environment records.
3. Committed decompilation captures and byte-verified probe definitions.
4. Status/prose reports.

This precedence is stated in `knowledgegraph/research/track-m-oracle-plan.json:25-35`. A zero-event run, clean exit, boot stall, screenshot, generic frame, or fan-in count must not be promoted to semantic or replacement evidence.

## 3. Original-binary facts and conflicts

### 3.1 Identity and address model

Committed identity for the oracle target is `SPORE/SporeBin/SporeApp.exe`, version `3.1.0.22`, x86 PE32/i386 Windows, image base `0x00400000`, SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`. These are committed facts, not a fresh hash read in this task (`knowledgegraph/research/semantic-blueprint.json:620-630`; `docs/analysis/CELL-RUNTIME-OBSERVATION.md:23-36`).

Address rules:

- `linked VA = image base + PE RVA`.
- `RVA = linked VA - 0x00400000`.
- File offsets must be resolved through the PE section mapping; do not subtract the image base from every historical artifact field.

The engine is statically linked in the executable; there is no replaceable engine DLL boundary (`knowledgegraph/research/replacement-feasibility.json:31-42`).

### 3.2 Current Cell target

`Simulator::Cell::MovePlayerToMousePosition` is SDK-confirmed at:

- Linked VA: `0x00E5B790`.
- RVA: `0x00A5B790`.
- File offset: `0x00A5AB90`.
- Entry bytes: `a1 04 3c 6b 01`, one complete 5-byte `mov eax,[absolute]` instruction.
- Confirmed return: `void`.
- Confirmed parameter: one `float deltaTime`.
- Convention: cdecl is likely/inferred, not independently runtime-confirmed.
- Direct caller reported by static evidence: `0x00E8083B`; complete caller enumeration is not complete.

Sources: `knowledgegraph/research/replacement-feasibility.json:355-389`; `docs/REPLACEMENT-ABI.md:13-38`.

The static body shows a lock guard, player lookup through `FUN_00b721d0`, per-frame/camera/UI calls, ray-plane intersection, target stores, a moving flag, and an orientation call (`tools/re/data/decompiled/MovePlayerToMousePosition.c:5-42`). This is static evidence, not live behavior.

### 3.3 Global/address conflict

The current replacement record uses `sCellGame` at `0x016B3C04`; older probe/dossier/decompilation material uses `0x116B3C04`. The two must not be silently treated as equivalent. Current binary bytes and the loaded module map must resolve the conflict before any future installation or live memory sampling (`knowledgegraph/research/replacement-feasibility.json:66`, `docs/REPLACEMENT-ABI.md:40-52`, `tools/observatory/probes/cell_movement.json:1-4`).

### 3.4 Field and plane status

Static offsets currently associated with the target are:

- `sCellGame+0x5158`: lock/paused guard; field meaning is inferred.
- `sCellGame+0x411c`: player pool index passed to the collection lookup; field meaning is inferred.
- `sCellGame+0x5270` (`0x5190 + 0xe0`): moving flag; field meaning is inferred.
- `player+0x08/+0x0c/+0x10`: target position; offset evidence is stronger than semantic meaning.
- `player+0x14..+0x20`: orientation quaternion; layout/meaning are inferred.
- `player+0x4c/+0x50/+0x54`: current position; offset evidence is stronger than semantic meaning.

The movement-plane normal was statically read as `{0,0,1}` from `DAT_015a7c40/44/48`. The plane point is BSS-backed at `DAT_016b3c28/2c/30`; `{0,0,0}` is the load-time image value, but the runtime per-world point is unread. The normal is verified; the runtime point and most field meanings are not (`docs/REPLACEMENT-ABI.md:40-62`; `docs/CELL-CONTRACT.md:38-58`).

## 4. Existing trace and oracle tooling

### 4.1 Observatory tracer

`tools/observatory/probe_tracer.cpp` and `tools/observatory/README.md` implement a dependency-free 32-bit ptrace/INT3 tracer:

- Fork/exec/seize and follow clone/fork/vfork/exec lineage.
- Discover the target module through `/proc/*/maps` and support the reparented Wine game host.
- Plant temporary `0xCC` breakpoints, save/restore original bytes, single-step over each breakpoint, and emit JSONL register/event records.
- Bound duration, event caps, breakpoint count, signal interruption, and detach.
- Discover a module by scanning executable mappings and the attached set.

Existing native tracer evidence is positive: the m32 self-test produced 1,801 events (`main` once, `beta` 800, `alpha` 1,000 plus one cap drop). This validates tracer mechanics only; `m32target` is not Spore and proves no Cell semantics (`tools/observatory/README.md:71-83`; `knowledgegraph/research/track-m-oracle-plan.json:37-49`).

The tracer does **not** provide:

- Function return values.
- Call-site continuation or `RET`/`RET N` observations.
- Post-call memory snapshots.
- Hidden-sret output capture.
- Replacement-code injection.
- A positive Cell-stage trace.

Those are explicitly listed as missing in `knowledgegraph/research/replacement-feasibility.json:109-132` and `docs/analysis/original-exe-replacement.md:46-52`.

### 4.2 Existing probe sets

- `tools/observatory/probes/main_menu.json`: seven linked-VA startup probes (`entry`, `Init`, `Startup`, `InitPlugins`, `IAppSystem::Get`, `local_main`, `stateMachine`).
- `tools/observatory/probes/cell_movement.json`: twelve probes, including eleven non-control Cell-related functions and one `entry` bootstrap control. The static set is byte-checked against the original.
- `tools/observatory/probes/menu_transition.json`: eight probes for editor/message/resource/frame transition; defined and byte spot-checked, but not run under the original.

Sources: `tools/observatory/probes/main_menu.json:1-20`; `tools/observatory/probes/cell_movement.json:1-66`; `tools/observatory/probes/menu_transition.json:1-23`; `knowledgegraph/research/track-n-testability.json:177-198`.

### 4.3 Historical original-runtime evidence

Positive historical startup evidence exists:

- A fresh-wineserver run recorded 1,004 events: `entry` once, `InitPlugins` once, `Init` once, `Startup` once, and `IAppSystem::Get` 1,000 times plus one cap drop.
- `local_main` and `stateMachine` were not reached in the 30-second window.
- The committed example is `tools/observatory/examples/obs_main_menu_example.jsonl`; current ignored `tools/observatory/out/obs_main_menu.jsonl` is empty.

Sources: `tools/observatory/SCENARIO-main_menu.md:163-183`; `tools/observatory/README.md:123-134`; `knowledgegraph/research/track-m-oracle-plan.json:50-61`.

The older nine-run Cell observation is a stable negative:

- Eight runs stalled before D3D initialization; one run reached the menu.
- The positive run recorded the generic orientation/frame helper about 226 times at roughly 30 Hz, not a Cell marker.
- All eleven non-control Cell probes recorded zero events in every run.
- `FUN_0069b600` must not be used as Cell reachability evidence.

Source: `docs/analysis/CELL-RUNTIME-OBSERVATION.md:44-96`.

S5 is also negative, with a different observed failure mode:

- Run 1 booted, reached the registration/menu screen, accepted the fixed input plan visibly, recorded nine changing screenshots, and fired the `entry` control once; it self-exited cleanly about 12.7 seconds into the trace.
- Runs 2 and 3 self-exited before a window appeared; both had zero events and no manifest.
- All eleven Cell-stage probes remained at zero.
- Registration/license/renderer interaction and Wine/`ntsync` behavior are hypotheses, not established causes.
- The exact exit trigger remains unknown.

Source: `docs/devlog/018-s5-cell-runtime-evidence.md:25-76`; `knowledgegraph/research/track-m-oracle-plan.json:85-107`.

## 5. GUI automation and input evidence

The committed GUI surface is deliberately narrow:

- `tools/observatory/menu_walk.sh`: approval gate, `wineserver -k`, fixed key allowlist (`Return Escape Up Down Left Right`), pinned geometry, no-op ladder, overlay, stop key, machine lock, and shot/input manifests. It has a dry-run mode and fail-closed exit codes.
- `tools/observatory/cell_trace.sh`: boots the original through `probe_tracer --launch wine`, uses the same allowlist and overlay/lock, requires `:0`, a present executable/tracer/`xdotool`/`maim`, a renderer marker, pinned geometry `2304x1296+2561+144`, and writes an S5 manifest. It determines Cell reachability from any non-control probe event, not screenshots.
- `tools/observatory/agent_overlay.py`: visible `AGENT DRIVING` overlay and global `Ctrl+Alt+Backspace` stop chain.
- `tools/observatory/lock.py` and `machine_lock.sh`: shared `flock` at `/tmp/openspore-machine.lock`; exit `5` on contention. The lock body includes pid, label, timestamp, and task id.
- `tests/test_menu_walk.py` and `tests/test_cell_trace.py`: dry-run, approval, key allowlist, focused-window command, registration gate, manifest, and determinism contracts.

S4 established the important input distinction:

- Primary `xdotool --window`/XSendEvent input was inconclusive.
- Focused-window `xdotool windowactivate --sync` followed by `xdotool key --clearmodifiers Return` produced a visible registration response.
- This is a GUI/input-attribution fact only; it does not establish Cell reachability, message dispatch order, or gameplay semantics.

Source: `docs/devlog/017-s4-x11-input-feasibility.md:7-35`.

The current `cell_trace.sh` intentionally uses the focused-window path and omits the `--window` form. `menu_walk.sh` still contains a window-targeted path; the two scripts should not be conflated when describing input evidence.

The current shell has strong safety/provenance coverage, but screenshots are annotations only. A screenshot without a corresponding trace event in the same time window is not semantic evidence (`docs/RE-AUTOMATION-ARCHITECTURE.md:433-497`; `knowledgegraph/research/track-m-oracle-plan.json:301-307`).

## 6. Existing Cell reconstruction and runtime research

### 6.1 Host Cell implementation

The Cell reconstruction campaign is complete as a static/host slice, not as original runtime verification:

- 31 targets done; CS-32 runtime trace/promotion is partial/blocked.
- `src/apps/cell_stage.cpp` runs the Cell-stage pipeline on real read-only GOG assets: decode, simulation, GFX/resource preload, declarative scene, Vulkan rendering, and HUD.
- Host simulation uses `cell-sim-contract/2`, fixed 60 Hz updates, binary32 state, deterministic fixtures, and generated OpenSpore expectations.
- `src/sim/CellGame.{hpp,cpp}`, `CellPool.hpp`, `CellQuery.hpp`, and related tests model a 4,096-cell pool, selected query/advect/combat rules, and static decomp-derived layouts.
- `src/apps/CellModeStrategy.cpp`, `IGameMode.hpp`, and `CellInput.cpp` provide a clean-room host lifecycle/input shell. `IGameMode` is semantic, not a complete original vtable ABI; `CellInput` is a host table, not original device-input proof.
- `src/replace/Reference.cpp` is a transcription of decompiler output. `src/replace/Replace.cpp` and `Replace.hpp` are a host stand-in with four arguments. It cannot be jumped to as the original one-float target.
- The 64/64 result in `src/replace/tests/diff_test.cpp` compares replacement to the decompiler-derived reference over eight deterministic cases and eight fields. It is `replaced-approx`, never a live original comparison.

Sources: `docs/analysis/campaigns/cell-stage-campaign.md:1-18,44-55,511-519`; `docs/REPLACEMENT-DIFF.md:1-24,105-120`; `src/replace/Replace.hpp:39-80`; `src/replace/CellGameView.hpp:22-62`; `docs/CELL-CONTRACT.md:1-17,120-144`.

### 6.2 Static Cell runtime facts useful to an oracle

Committed static/decomp anchors include:

- `cCellModeStrategy::Update` `0x00e80980`; real body `0x00e806b0`.
- `OnKeyDown` `0x00e818f0`; `OnMouseMove` `0x00e51010`; `OnMouseWheel` `0x00e7d660`.
- `OnEnter` `0x00e552f0`; `OnExit` `0x00e7fc00`; `Initialize` `0x00e81cf0`; `Dispose` `0x00e81f30`.
- `cCellGame::Initialize` `0x00e80ba0`; `CreateCellObject` `0x00e74a20`.
- `cCellGFX::Initialize` `0x00e5dba0`; `PreloadResources` `0x00e666f0`; `StartDisplay` `0x00e55120`.
- `PlayAnimation` `0x00e6d200`; pool lifecycle candidate `0x00e780a0`.

`0x00e780a0` has a static dossier describing avatar-index clearing, GFX release, scale-triggered rebuild, and pool recreation, but it is still `not-started`/partial and not runtime-validated (`docs/analysis/dossiers/unknown-high/cell-object-pool-lifecycle.md:18-93`).

The campaign and architecture resolution explicitly separate Cell simulation, GFX/UI, content/resource state, and serializable save state. A pool index, runtime entity pointer, GFX handle, and serializable record are not interchangeable identities (`docs/analysis/architecture-resolution.md:226-249`; `docs/analysis/reconstruction-packages.md:488-562`).

## 7. Architecture decisions and blockers relevant to runtime evidence

### 7.1 Frozen semantic boundaries

The decision register freezes separate semantic axes for App, Simulator strategy, input, SpaceContext, scenario, and Cell. It freezes separate Cell simulation/presentation/content/save ownership. It rejects a universal event payload ABI and keeps raw vtables as a separate compatibility surface (`docs/analysis/architecture-decisions.md:7-28,69-99`).

The architecture resolution records three final blocker clusters:

- **Cluster A, architecture-changing:** noun/star root publication, equality, liveness, and teardown. Interim boundary is four opaque ports with explicit publish/replace/invalidate/unpublish hooks.
- **Cluster B, architecture-changing:** first writer/physical identity/freshness/ownership of `DAT_0167eaec` and the `0x00b5b800` forwarded `receiver+0x20`. Interim boundary is borrowed opaque `uint32` with `0xffffffff` absent-source sentinel.
- **Cluster C, architecture-changing:** persistence object/reference/restore graph and mode-handoff boundary. Interim boundary is schema/callback serialization, stable references, deferred association, versioned header, and explicit temp/close/replace.

Sources: `knowledgegraph/research/semantic-blueprint.json:1-149`; `docs/analysis/architecture-resolution.md:357-379`.

The focused future-research documents consistently require observation before promotion:

- `03-pkg-07-cell-movement.md`: ABI, guards, side effects, input causality, and pre/post state.
- `01-pkg-01-shared-state-roots.md`: exact root closure, writers, consumers, and lifecycle without fan-in inference.
- `02-pkg-02-app-lifecycle.md`: M0 boot triage with pinned environment.
- `04-pkg-10-editor-dispatch.md`: correlated input/message/resource/frame order, not screenshots.
- `05-pkg-11-sim-core.md`, `06-pkg-12-sim-space.md`, `07-pkg-13-sim-creature-tribeciv.md`, `08-pkg-14-terrain-world.md`, `09-pkg-18-ui-scripting.md`, `10-pkg-19-audio-input.md`, `11-pkg-20-gameglobal.md`, and `12-pkg-21-unknown-routing.md`: owner/callee/contract characterization before semantic or replacement claims.
- `01-architecture-blocker-1.md`, `02-architecture-blocker-2.md`, and `03-architecture-blocker-3.md`: cluster-specific smallest investigations and stopping criteria.

### 7.2 Corpus/readiness facts

The committed semantic blueprint records:

- 58,757 canonical functions and 2,149 gameplay functions.
- 1,598 gameplay rows are `unknown-needs-investigation`.
- 1,976 gameplay rows have no established semantic characterization.
- 1,977 gameplay rows have no persisted body.
- Runtime-verified gameplay functions: `0`.
- No positive original Cell/pose/teardown/final-frame observation.
- Current OpenSpore fixtures and state strings are regression artifacts, not original compatibility oracles.

Sources: `knowledgegraph/research/semantic-blueprint.json:663-718`; `docs/analysis/reconstruction-readiness.md:9-32,191-218`.

## 8. Replacement mechanics and current limits

Supported in principle: PE import replacement for real imports, vtable replacement after dispatch proof, call-site patch for a proven caller, function-pointer replacement only with lifetime/synchronization proof, and entry detour. Not implemented: production Spore patcher, trampoline, function-pointer replacement, and function-pointer/inline mechanism with complete relocation/lifecycle behavior (`knowledgegraph/research/replacement-feasibility.json:44-87`).

The synthetic `tools/replace/synthetic/` proof verifies only a native 32-bit, non-PIE constructor using `mprotect`, a 5-byte `E9 rel32` entry jump, readback, and saved original bytes. It has no unhook, arbitrary instruction relocation, page-boundary handling, thread quiescence, or Spore identity validation (`tools/replace/synthetic/README.md:7-58`; `knowledgegraph/research/replacement-feasibility.json:89-107`).

The host replacement is not directly installable:

- Original: `void(float)` at the target entry.
- Host stand-in: `void(float, SCellGameView*, CameraView*, MovementPlane*)`.
- The host `playerRef` stand-in is a resolved pointer, while the original field is a pool index requiring `FUN_00b721d0` lookup.
- The orientation layout and field meanings are inferred.
- The environment-dependent per-frame/camera/UI calls are omitted from the reference.

The entry detour and an INT3 probe cannot safely own the same target bytes concurrently. Any future install must use a separate, reviewed lifecycle and must not run under the same tracer ownership (`tools/replace/synthetic/README.md:32-37`; `docs/REPLACEMENT-ABI.md:102-118`).

A dedicated per-call oracle must eventually record:

1. Binary/module identity, image base, target bytes, loaded module base, caller, and thread.
2. Entry `EIP`, `ESP`, `EBP`, `EAX`, `EBX`, `ECX`, `EDX`, `ESI`, `EDI`, flags, and original argument words/float interpretation.
3. Return/continuation `EAX`, `EDX`, `ESP`, flags, and `RET` versus `RET N`.
4. Callee-saved register comparison and pre/post memory for the target global, receiver/player/pool identity, target/orientation/moving state, plane, camera/UI state, and adjacent integrity bytes.
5. Call count, caller, detach/unhook state, crash/termination status, and negative reason.

The existing observatory supplies only part of item 1/5 and entry registers; the remainder is missing (`knowledgegraph/research/replacement-feasibility.json:399-422`).

## 9. Unknowns and negative results

1. **Boot stability:** current S5 outcome is a clean self-exit; exact cause is unknown.
2. **Cell reachability:** no positive non-control Cell probe has fired.
3. **Mode transition timing:** App helper-local order is static; actual listener/message delivery is unobserved.
4. **Movement ABI:** cdecl, stack frame, omitted callees, and original pool-index lookup are not live-confirmed.
5. **Memory semantics:** player field meanings, pool pointer/index relationship, current-position source, moving-flag owner, and adjacent side effects are static/inferred.
6. **Plane point:** normal is statically verified; runtime per-world point is unread.
7. **Address conflict:** `0x016B3C04` versus `0x116B3C04` must be adjudicated against current bytes/module mapping.
8. **Return/memory oracle:** unavailable in current entry-only tracer.
9. **Input causality:** focused-window input reaches the registration UI, but no Cell/menu-to-Cell path is proven.
10. **Shared roots:** noun/star publication/equality and `0x00b5b800` first writer/physical ownership remain open.
11. **Persistence:** outer envelope, object table, descriptor graph, field survival, migration, cross-file atomicity, and mode-handoff ownership remain open.
12. **Event/UI/resource order:** message queue timing, thread affinity, reentrancy, payload mapping, and resource causality remain open.
13. **Renderer/presentation:** original placement, materials, lights, pose upload, pixels, and runtime GFX/UI ordering remain unvalidated.

## 10. Proposed experiment sequence (not evidence)

The existing Track M plan defines these proposals:

- **M0 — boot control:** fresh-generation startup trace with `main_menu.json`; separate module attach, renderer, registration, and clean-exit outcomes. No input.
- **M1 — Cell reachability:** up to three approved, human-watched Cell runs using the existing `cell_trace.sh` and `cell_movement.json`; require at least one non-control Cell probe and time-order relative to `entry`.
- **M2 — ABI/side effects:** read-only entry and safe post-return sampling of the one-float argument, `sCellGame`, `+0x411c`, lock, moving flag, player target/current/orientation, plane point/normal, camera/UI words, and state gates. No hook, no payload dump, no memory writes.
- **M3 — mouse/camera causality:** fixed pointer waypoints correlated with `OnMouseMove`, camera source, movement, and state changes; do not treat the generic orientation helper as a Cell marker.
- **M4 — shared state/GFX:** static lifecycle, Cell game, GFX preload, pool lifecycle, and service-root probes to separate gameplay state from presentation/engine handles.
- **M5 — menu/resource transition:** use the existing `menu_transition.json` to correlate input, message pump, editor, resource initialize/lock/index, and frame heartbeat.
- **M6 — renderer boundary:** characterize original graphics/material/layer transitions separately from gameplay and screenshots.

The plan's contracts are `C-PROV`, `C-NEG`, `C-BOOT`, `C-ENTRY`, `C-ORDER`, `C-SIDE`, `C-STATE`, `C-MOUSE`, `C-ABI`, `C-EVENT`, `C-BOUNDARY`, and `C-REPLACEMENT` (`knowledgegraph/research/track-m-oracle-plan.json:353-743`).

The replacement-feasibility record proposes a separate future path:

1. Read-only PE/module/target preflight and identity validator.
2. Native disposable 32-bit ABI harness for a one-float void shim.
3. Disposable-process reversible detour containment with instruction-boundary, rel32-range, page, unhook, and thread-quiescence checks.
4. Behaviorless positive control such as `App::IAppSystem::Get`.
5. Only then consider Cell target replacement.

These are design proposals and gates, not implemented work (`knowledgegraph/research/replacement-feasibility.json:424-511`).

## 11. Constraints for any future researcher

- Keep `SPORE/`, `SporeApp.exe`, and the original executable read-only unless a separately approved disposable-copy/process experiment explicitly authorizes otherwise.
- Do not use proprietary payloads, memory dumps, assets, or decompiled source in the repository.
- Do not write the canonical `knowledgegraph/spore.db` from this note or infer runtime evidence into it.
- Pin `binary_sha256`, probe-set path/hash, linked/RVA/file-offset convention, Wine version/generation, display/compositor, window identity/geometry, tool versions, raw JSONL, event count, and exact outcome for every future run.
- Require human approval for an original launch; direct Cell trace requires `--approve` and `OPENSPORE_MCP_TRUSTED=1` (`tools/observatory/cell_trace.sh:601-629`).
- Acquire the shared machine lock and park on `machine_locked`; use `wineserver -k` before each approved original launch and verify teardown.
- Use fixed, reviewable input only: no typing, letters, digits, or free-form input. Keep the focused-window path for Cell work.
- Treat zero events, boot stalls, clean exits, generic frame activity, and screenshots as bounded negative/annotation outcomes.
- Do not promote `replaced-approx` to `replaced-verified` without hash-pinned live evidence, field/offset evidence, an original/replacement observable comparison, independent adjudication, and human approval.

## 12. Synthesis conclusion

The repository has enough static and tooling evidence to design a bounded runtime-oracle program, but not enough positive Cell evidence to claim original movement semantics or install a replacement. The immediate research artifact should be a read-only preflight plus a capability gap for return/memory observation. The first runtime decision point is not the replacement hook; it is whether a fresh, provenance-pinned M0 boot is reproducible, followed by whether M1 can reach Cell with a non-control probe. Until those gates pass, the correct status remains static/decompilation-backed `replaced-approx`, not original-runtime verified.
