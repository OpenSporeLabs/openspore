# Track 8 — Cell Runtime / Presentation Lifecycle

## Resolution

**Status: `RESOLVED_SUPPORTED` at the architecture boundary; runtime and save/load details remain insufficient.**

**Normalized classification:** `preferred_claim_with_limit`  
**Allowed report taxonomy:** `unresolved`, `preserved_alternatives`, `preferred_claim_with_limit`, `same_observation_different_scope`  
**Concept ownership labels:** `simulation`, `presentation`, `persistent_content`, `cross_boundary`

The evidence supports an explicit split, not a merged runtime:

- `cCellGame` and `cCellObjectData` own runtime pool identity/state, indexed by a 4096-slot pool. `cCellGame+0x411c` is the avatar pool index; it is not a GFX pointer.
- A static per-cell GFX detach path (`0x00e66010`) clears `mGFXObjectIndex+0x248` and releases the GFX record without releasing the `cCellObjectData`; a separate same-cell rebuild path (`0x00e6d8f0`) writes a new GFX index. This is not an atomic detach→rebuild guarantee.
- `mModelKey` is persistent content identity. `mCellResource` and `cCellDataReference_` are runtime cross-boundary references, not persistent content records and not GFX handles.
- `cCellGFX` and `cCellUI` are separate presentation/service domains. Their worlds, layers, effects, rollovers, audio, and UI handles are presentation proxies.
- `cCellModeStrategy` is the cross-boundary coordinator. `OnExit` is cross-boundary mode/service cleanup, while `Dispose` is a deeper owner/service release.
- Death, pending interaction, per-cell GFX detach/rebuild, despawn, stage rebuild, `OnExit`, and `Dispose` are separate lifecycle operations; a single alive/dead flag is insufficient.

## Smallest separator

A static field/handle snapshot was performed because the requested positive runtime trace is unavailable:

1. `CreateCellObject` (`0x00e74a20`) returns a pool index and initializes `mModelKey+0xfc`, `mCellResource+0x108`, `mGFXObjectIndex+0x248`, `mScale+0x358`, and `mpQuery+0x35c`.
2. `FUN_00e66010` (`0x00e66010`) clears `+0x248` and releases the GFX record without releasing the `cCellObjectData`; `FUN_00e6d8f0` (`0x00e6d8f0`) later rebuilds the GFX association on the same cell through a separate conditional branch.
3. `FUN_00e780a0` (`0x00e780a0`) is different: it detaches GFX state, may create replacement/child state, then releases the old Cell object. `FUN_00e7fd00` (`0x00e7fd00`) clears `+0x411c`, drains old cells, and rebuilds runtime state; neither retains old identity.
4. `OnExit` (`0x00e7fc00`) is cross-boundary mode/service cleanup and does not directly rewrite `+0x411c`, `+0x108`, or `+0x248`; `Dispose` (`0x00e81f30`) releases GFX, CellGame, and UI through separate service paths.

This supports a bounded per-cell GFX detach/rebuild seam. The broader rule that every presentation detach preserves pool identity is a **modern design invariant**, not recovered original behavior. It does not prove runtime callback order, GPU retirement timing, or save/load behavior.

## Nine-step adversarial result

| Step | Result |
|---|---|
| Ownership collapse | Contradicted: separate Game/GFX/UI types and teardown paths. |
| Identity/detach | Static per-cell detach retains the Cell object; same-cell rebuild is a separate branch, not an atomic or universal guarantee. |
| Transient proxies | Supported: GFX/UI/effect/world handles are replaceable; retirement timing open. |
| Content identity | Supported: `mModelKey` is content identity; `mCellResource`/`cCellDataReference_` are runtime cross-boundary references. |
| Animation intent | Supported: Cell state owns intent; pose/render output is downstream. |
| Update order | Static orchestration supports separation; complete runtime order open. |
| Death/rebuild | Supported as separate transitions; player rebuild chain open. |
| Save/reload | Runtime rebuild is distinct from save transaction; save wire unknown. |
| Teardown/separator | Static snapshot completed; runtime separator unavailable. |

## Ownership matrix

| Concept | Classification | Authority |
|---|---|---|
| `cCellGame`, pool/query, avatar index, timing, world refs | `simulation` | Runtime Cell state and identity |
| `cCellObjectData` transform, health, scale, query, AI/death | `simulation` | Authoritative gameplay state |
| `mGFXObjectIndex`, GFX/UI handles, effects, world/layer bindings | `presentation` | Replaceable visual association |
| `mModelKey` | `persistent_content` | Stable model/content identity |
| `mCellResource` / `cCellDataReference_` | `cross_boundary` | Runtime resource-reference boundary |
| Animation clip/blend intent | `cross_boundary` | Simulation-owned intent, presentation-evaluated pose |
| `cCellModeStrategy`, including `OnExit` | `cross_boundary` | Mode lifecycle, service coordination, and cleanup boundary |
| `cCellSerializableData` | `cross_boundary` | Runtime serializable/save candidate, not content record |

The complete matrix, hypothesis predictions, independence/repetition notes, evidence, citations, dependent decisions, freeze/defer lists, and blockers are recorded in `track-08-cell-lifecycle.json`.

## Runtime blocker

No positive original Cell-mode trace reached create → gameplay mutation → GFX detach/rebuild → teardown. Historical traces reached only bounded main-menu startup; the permitted investigation has no usable headless Cell path. The report does not fabricate runtime evidence.

## Track 10 vtable correction

The Cell mode object is a 12-byte multiple-interface object: Track 10 identifies primary vptr `0x01485558` at object `+0` and secondary vptr `0x01485550` at `+4`. The historical aggregate is not a safe single primary-table claim. Keep the semantic `IGameMode`/manager boundary; defer exact raw slot mapping and AddGameMode pointer adjustment.

## Freeze

Freeze the explicit simulation/presentation/content boundary; `mModelKey` as content identity; `mCellResource`/`cCellDataReference_` as runtime cross-boundary references; the bounded per-cell GFX detach/rebuild seam; identity-destructive despawn/reload; and cross-boundary `OnExit` versus deeper `Dispose`.

## Defer

Defer universal identity survival across presentation changes, atomic detach→rebuild behavior, full frame/pose/render order, GPU retirement, exact pool exhaustion/replacement policy, event queue timing, player rebuild construction, and complete `cCellSerializableData` save/load coverage.

## Sources

- `docs/analysis/dossiers/unknown-high/cell-object-pool-lifecycle.md`
- `docs/analysis/dossiers/cell-movement.md`
- `docs/analysis/gameplay-render-dependencies.md`
- `docs/analysis/gameplay-transition-map.md`
- `docs/analysis/event-message-map.md`
- `docs/analysis/serialization-model.md`
- `knowledgegraph/research/types/13-lifecycle.md`
- `knowledgegraph/research/types/02-gameplay-entity.md`
- `knowledgegraph/research/types/08-persistence-serialization.md`
- `knowledgegraph/research/conflict-adjudication.json`
- `knowledgegraph/research/architecture-resolution/followup-04-cell-boundary.json`
- `knowledgegraph/research/architecture-resolution/followup-04-cell-boundary.md`
- `knowledgegraph/research/architecture-resolution/track-10-vtable-conditional.json`
- `knowledgegraph/research/architecture-resolution/track-10-vtable-conditional.md`
- Ghidra read-only `SporeApp.exe`: `0x00e74a20`, `0x00e66010`, `0x00e6d8f0`, `0x00e78c00`, `0x00e7c8c0`, `0x00e780a0`, `0x00e7fd00`, `0x00e7fc00`, `0x00e81f30`, `0x00e6d200`, `0x00e63d10`, `0x00e819b0`.
