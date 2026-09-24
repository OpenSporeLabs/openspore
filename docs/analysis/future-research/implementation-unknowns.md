# Implementation Swarm Unknowns

Scope: the eight packages implemented in the first OpenSpore implementation batch. These are clean-room host contracts, not claims of original-runtime equivalence.

## PKG-03-RESOURCE-IO

- Unknown: original multi-package priority, directory resolution, cache policy, async scheduling, and record-handle lifetime.
- Current assumption: one borrowed `IContentStore`/provider with complete `ResourceKey` identity and synchronous lookup/read; `PROVISIONAL` wire-local property encoding.
- Affected code: `src/assets/ResourceStore.*`, `src/assets/Dbpf.*`, `src/assets/PropertyStore.*`, `src/assets/Stream.hpp`.
- Blast radius: resource composition, priority, reload, cache, and persistence integration.
- Resolution evidence: original manager registration/lookup, cache lifecycle, QFS caller, and property read/write traces with round-trip fixtures.

## PKG-04-ASSET-GEOMETRY-TEXTURE

- Unknown: GMDL v9+, GMDL/RW4 animation payloads, RW4 material/compiled-state semantics, raster fields `0x10/0x18/0x1c`, material-slot association, sampler/mip policy, and pixel fidelity.
- Current assumption: GMDL v8 and structural RW4 only; DXT5 mip zero uploads through the existing renderer port; missing materials return unsupported; `BOUNDED_INFERENCE` for host result mapping.
- Affected code: `src/assets/Gmdl.*`, `Rw4.*`, `Mesh.*`, `ModelStore.*`, `MaterialRegistry.*`, `TextureStore.*`, `Dxt5.*`.
- Blast radius: model/material/texture presentation, future animation, and any pixel comparison.
- Resolution evidence: recovered format bodies, section semantics, material fixtures, renderer host API, and matched original captures.

## PKG-05-CELL-CONTENT

- Unknown: `0x00E82340` versus `0x00E82420` identity, complete group identity of direct references, target TypeIDs for wildcard fields, advect references, soft-ID selection, runtime world placement, and loot settlement.
- Current assumption: twelve direct records decode to immutable values; zero references are nullable host fields; unresolved targets fail explicitly; `BOUNDED_INFERENCE` for the bounded hard-reference projection.
- Affected code: `src/assets/CellContent.*` and direct `CellResource.*` reference projection.
- Blast radius: runtime Cell handles, world/AI/loot consumers, and future reference/save integration.
- Resolution evidence: alias adjudication, serializer/consumer bodies, complete-key fixtures, and matched runtime traces.

## PKG-06-CELL-STATE

- Unknown: complete pool side effects/free-list sentinel, AI/effect/query integration, runtime gates, original timing, and live-object save behavior.
- Current assumption: deterministic pure host state with capacity 4096, stable pool indices, health clamping, explicit query/advect/combat results; `BOUNDED_INFERENCE` for bounded pure rules and `PROVISIONAL` for omitted side effects.
- Affected code: `src/sim/CellGame.*`, `CellPool.hpp`, `CellQuery.hpp`, `Advect.hpp`, `Combat.hpp`.
- Blast radius: live Cell simulation, movement, combat, animation intent, and future persistence.
- Resolution evidence: complete pre/post state traces, root resolution, runtime gates, and original differential fixtures.

## PKG-08-CELL-MODE

- Unknown: other modes, input timing, queue timing, registration/camera ownership, consume/default behavior, and SDL bypass semantics.
- Current assumption: clean-room `IGameMode` lifecycle, explicit mode activation ordering, same/invalid-index behavior, and mode-owned normalized input; `PROVISIONAL` for transport and original runtime details.
- Affected code: `src/apps/CellModeStrategy.*`, `InputRouter.*`, `MessageManager.*`, `IGameMode.hpp`, `CellInput.*`.
- Blast radius: Cell stage entry, input routing, message handoff, and future App lifecycle integration.
- Resolution evidence: SetActiveModeAt correlation, input/message traces, and controlled menu/Cell reachability.

## PKG-09-CELL-PRESENTATION

- Unknown: placement, preload order/timeout, material slots, HUD timing/drawing, pose upload, GPU retirement, and original pixels/lighting.
- Current assumption: host scene stage with preload-before-display, stable entity/presentation identities, explicit missing/unsupported resources, and release-before-shutdown; `BOUNDED_INFERENCE` for host lifecycle and `PROVISIONAL` for placement/visual fidelity.
- Affected code: `src/apps/CellPresentation.*`, `CellSceneStage.*`, renderer queue/effect ports.
- Blast radius: Cell visuals, resource handles, scene membership, and future animation/pose integration.
- Resolution evidence: matched render captures, preload/resource traces, material/pose/GPU lifecycle evidence.

## PKG-15-EDITOR-SUPPORT

- Unknown: original palette categories, runtime load/update order, viewer lifecycle, texture-paint state, save support, and command ownership.
- Current assumption: in-memory support assets, deterministic palette filtering, explicit provisional viewer/paint lifecycle, and unsupported writer; `BOUNDED_INFERENCE`/`PROVISIONAL` only.
- Affected code: `src/editor/EditorSupport.*` and `src/editor/tests/editor_support_test.cpp`.
- Blast radius: future editor command, viewer, and resource-authoring integration; no gameplay state.
- Resolution evidence: editor producer/consumer paths, palette/viewer/paint VAs, and controlled editor traces.

## PKG-17-ANIMATION-SWARM

- Unknown: event producer, blend completion, clip duration/loop wrapping, pose order/upload, skeleton/particles, Swarm ownership, and vehicle coupling.
- Current assumption: gameplay intent and deterministic current/target/blend state with explicit pose/effect unsupported seams; `BOUNDED_INFERENCE` for host animation state and `PROVISIONAL` for unresolved backend behavior.
- Affected code: `src/apps/CellAnim.*` and future pose/effect/presentation integration.
- Blast radius: Cell visual animation, effects, pose evaluation, and future Swarm behavior.
- Resolution evidence: event-to-animation, event-to-pose, blend, and Swarm/vehicle ownership traces with controlled fixtures.

## Cross-package non-claims

- No original-runtime equivalence is claimed for any package.
- Host fixtures and decompilation support the documented semantic contract only.
- Remaining unknowns stay behind narrow interfaces and must be replaced when stronger evidence is admitted.
