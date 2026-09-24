# Simulator Core Type Archaeology

- **Partition:** `01-simulator-core`
- **Status:** research only; no implementation, runtime trace, Ghidra mutation, knowledge-graph mutation, or `SPORE/` write
- **Binary:** `SporeApp.exe` 3.1.0.22, x86:LE:32, image base `0x00400000`
- **Binary SHA-256:** `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`
- **Analysis snapshot:** `f0e310e0`; 58,757 functions and 223,704 xrefs
- **Canonical xref snapshot:** `2540f2ca`
- **Live Ghidra state:** no open programs; this partition uses committed exports only

This is a clean-room static archaeology partition. SDK names, sizes, offsets, and vtable slots are evidence, not proof of undocumented gameplay semantics. `SporeApp.exe` has no MSVC RTTI, so adjacent vtable pointers are recorded as structural interface embedding rather than proven C++ inheritance. Detailed empire, star, planet, diplomacy, trade, mission, inventory, and serialization records remain in `05-empire-space`.

## Evidence policy

The evidence scale is `UNKNOWN < INFERRED < SUPPORTED < OBSERVED`. `OBSERVED` is used only for direct bytes or bounded decompiler reads/writes, `SUPPORTED` for corroborated static structure, `INFERRED` for bounded interpretation, and `UNKNOWN` for unresolved semantics. Confidence applies to the static contract, not to undocumented runtime behavior.

Source precedence is pinned binary/runtime artifacts, committed Ghidra/SDK/vtable/xref exports, triage-v6/read-only KG projections, existing dossiers, and current OpenSpore source. No proprietary source or assets are copied into this research.

## Reconstruction spine

```text
cSimulatorSystem
  -> mSubSystems vector of ISimulatorStrategy
     -> input / view / behavior / mode / time / tool / noun / persistence strategies
        -> direct consumers through the packed global accessor block
           DAT_0167eaf0 .. DAT_0167eb54

Cell::sCellGame
  -> cObjectPool_<cCellObjectData>
     -> first-word free-list and stable pool indices
     -> avatar, target transform, model/resource, graphics/query state
  -> camera-ray -> movement-plane -> target position/orientation
```

The first spine is a structural reconstruction order. The second has direct decompilation and current clean-room implementation evidence, but no original Cell runtime trace.

## Type inventory

| Type | Size | Static role | Evidence |
|---|---:|---|---|
| `cSimulatorSystem` | 112 | service root, subsystem vector, message listener, update/serialization slots | `SUPPORTED`, 0.94 |
| `cSimTicker` | 68 | active/pending simulator lists and ticking flags | `SUPPORTED`, 0.90 |
| `cGameInputManager` | 276 | input, mouse, mode, maps, and strategy/message interfaces | `SUPPORTED`, 0.96 |
| `cGameViewManager` | 424 | views, worlds, layer drawing, mouse position, and ray queries | `SUPPORTED`, 0.90 |
| `cGameBehaviorManager` | 164 | stopwatch, agents, and object associations | `SUPPORTED`, 0.90 |
| `cGameModeManager` | 156 | active mode, transition state, difficulty and scenario tuning | `SUPPORTED`, 0.91 |
| `cGameTimeManager` | 128 | speed factors, timing, pause maps, and pause types | `SUPPORTED`, 0.91 |
| `cGamePersistenceManager` | 76 | strategy/message listener with `LoadGame` slot | `SUPPORTED`, 0.88 |
| `cToolManager` | 668 | tool strategies, maps, and 26 failure strings | `SUPPORTED`, 0.90 |
| `cGameNounManager` | 284 | noun registry, player/tribe references, political and object maps | `SUPPORTED`, 0.91 |
| `cUIEventLog` | 112 | feedback-event map and property-backed state | `SUPPORTED`, 0.88 |
| `cGameData` | 52 | game-data identity, reference, view, scenario, owner, political ID | `SUPPORTED`, 0.88 |
| `cObjectPool_` | 28 | fixed-size index pool and free-list head | `SUPPORTED`, 0.93 |
| `cCellObjectData` | 920 | pooled cell transform, model, resource, graphics, query, and behavior state | `SUPPORTED`, 0.96 |
| `cCellGame` | 20,964 | Cell global state, pools, worlds, query links, timing, and mode | `SUPPORTED`, 0.93 |

The SDK exports contain 390 Simulator structures in total. This partition freezes the core types needed by shared state and Cell reconstruction; it is not an exhaustive transcription of every Simulator namespace type.

## Service composition

`cSimulatorSystem` begins with `cSimulatorSystem__vftable`, an `IVirtual` pointer, and `mnRefCount`. It stores a list of `ISimulatorUIGraphic` at `+0x20`, `MessageListenerData` at `+0x48`, and `mSubSystems` at `+0x5c` as a 20-byte vector of intrusive `ISimulatorStrategy` pointers.

Its 23-slot imported vtable establishes:

| Slot offset | Imported name | Bounded role |
|---:|---|---|
| `0x00` | `_virtual_dtor` | virtual destructor |
| `0x04` | `HandleMessage` | listener callback |
| `0x08` / `0x0c` | `AddRef` / `Release` | reference management |
| `0x10` / `0x14` | `Initialize` / `Dispose` | service lifecycle |
| `0x18` / `0x1c` | `InitializeSubSystems` / `DisposeSubSystems` | subsystem lifecycle |
| `0x24` | `InitializeGameModes` | game-mode initialization |
| `0x2c` / `0x30` | `Update` / `PostUpdate` | frame phases |
| `0x34` | `UpdateUIGraphics` | UI-graphic update |
| `0x38`–`0x44` | add/contains/remove/clear UI graphic | UI-graphic registry |
| `0x48` / `0x4c` | `Write` / `Read` | serialization surface |

The slot names do not establish concrete implementation bodies or call order. Recovering `mSubSystems` insertion, `InitializeSubSystems`, `DisposeSubSystems`, `Update`, and `PostUpdate` is the highest-priority core follow-up.

`cSimTicker` stores active simulators in `mSimulators` at `+0x1c`, pending simulators in `mToAddSimulators` at `+0x28`, an integer list at `+0x34`, and `mIsTicking` at `+0x41`. This is a strong scheduling boundary, but its relationship to `cSimulatorSystem::mSubSystems` is not yet proven.

## Manager layouts

### Input

`cGameInputManager` is 276 bytes. Its leading layout contains four interface vtable pointers, two reference-count fields, `mLastGameMode` at `+0x18`, `mCurrentGameMode` at `+0x1c`, maps at `+0x28` and `+0x44`, `mMouseX/mMouseY` at `+0x68/+0x6c`, input regions at `+0x74`, `+0x90`, and `+0xc0`, strings at `+0xdc` and `+0xec`, a vector at `+0xfc`, and an integer at `+0x110`.

The 27-slot vtable exposes reference management, trigger-file/trigger state, unknown intermediate slots, and `OnKeyDown`, `OnKeyUp`, `OnMouseDown`, `OnMouseUp`, `OnMouseMove`, and `OnMouseWheel` at slots `+0x4c` through `+0x60`. The intermediate input slots remain unnamed.

### View and behavior

`cGameViewManager` stores game-data views, model/effect worlds, a viewer pointer, and query-related maps. Its vtable exposes `DrawLayer`, `PrepareSimulator`, `GetWorldMousePosition`, `IntersectSphere`, `RaycastAll`, `Raycast`, and `GetObjectView`.

`cGameBehaviorManager` stores a stopwatch at `+0x20`, agents at `+0x24`, and several object/list/vector collections. Its vtable exposes `GetAgents`, `AddAgent`, `RemoveAgent`, and `HasAgent`; the earlier strategy lifecycle slots are unnamed.

### Mode, time, persistence, and tools

`cGameModeManager` stores `mActiveModeID` at `+0x20`, transition effect/world fields, seven `DifficultyTuning` records at `+0x3c`, and three scenario-tuning `PropertyList` pointers at `+0x90`.

`cGameTimeManager` stores four speed factors at `+0x1c`, `mBaseTimeElapsed` at `+0x30`, `mTimeAtStartOfFrame` at `+0x38`, current speed/index at `+0x40/+0x44`, and pause maps/types after that. This is enough to preserve the timing state shape, not the update formula.

`cGamePersistenceManager` exposes `LoadGame` at vtable `+0x10`; its remaining lifecycle slots are unnamed. `cToolManager` stores tool strategies at `+0x38`, a key map at `+0x58`, and 26 localized failure strings at `+0x74`. `cUIEventLog` stores a feedback-event map at `+0x28` and a `PropertyList` pointer at `+0x6c`.

### Nouns and game data

`cGameNounManager` stores avatar, herd, posse, player tribe, player, noun list, noun map, political map, object maps, and a game-data object list. The high-value fields are:

| Offset | Field | Type |
|---:|---|---|
| `0x54` | `mpAvatar` | `intrusive_ptr<cCreatureAnimal>` |
| `0x58` | `mpAvatarHerd` | `intrusive_ptr<cHerd>` |
| `0x70` | `mpPlayerTribe` | `intrusive_ptr<cTribe>` |
| `0x74` | `mpPlayer` | `intrusive_ptr<cPlayer>` |
| `0x78` | `mNouns` | `intrusive_list<cGameData>` |
| `0x98` | `mNounMap` | `map<uint32_t, tGameDataVectorT<cGameData>>` |
| `0xb4` | `mPoliticalMap` | `map<int32_t, int32_t>` |
| `0x10c` | `mObjects` | `list<intrusive_ptr<cGameData>>` |

`cGameNounManager::GetData` at `0x00b212d0` is a map lower-bound/materialization path. The committed body uses callback-shaped arguments, can recurse, and mutates update state, but its ABI is contaminated; exact callback types and function identity remain unresolved.

`cGameData` is a 52-byte refcounted identity object. It stores a game-data view, scenario marker/class, destroyed flag, object ID, definition ID, owner pointer, and political ID. `mpNext/mpPrev` expose intrusive-list linkage.

## Packed global accessors

The imported functions below are six-byte no-argument accessors that directly return one packed global word. The return mechanism is observed; initialization, setters, reset order, and complete ownership are unresolved.

| Accessor | VA | Global slot |
|---|---:|---:|
| `cSimulatorSystem::Get` | `0x00b3d330` | `DAT_0167eaf0` |
| `cGameViewManager::Get` | `0x00b3d340` | `DAT_0167eaf4` |
| `cGameInputManager::Get` | `0x00b3d350` | `DAT_0167eaf8` |
| `cGameBehaviorManager::Get` | `0x00b3d360` | `DAT_0167eafc` |
| `cStarManager::Get` | `0x00b3d3a0` | `DAT_0167eb0c` |
| `cRelationshipManager::Get` | `0x00b3d3c0` | `DAT_0167eb14` |
| `cGameNounManager::Get` | `0x00b3d400` | `DAT_0167eb60` |
| `cGameModeManager::Get` | `0x00b3d420` | `DAT_0167eb2c` |
| `cGamePersistenceManager::Get` | `0x00b3d440` | `DAT_0167eb34` |
| `cPlanetModel::Get` | `0x00b3d450` | `DAT_0167eb38` |
| `cGameTimeManager::Get` | `0x00b3d480` | `DAT_0167eb3c` |
| `cToolManager::Get` | `0x00b3d490` | `DAT_0167eb40` |
| `cSpaceTrading::Get` | `0x00b3d4d0` | `DAT_0167eb50` |
| `cUIEventLog::Get` | `0x00b3d4e0` | `DAT_0167eb54` |

These must not be modeled as independent owning globals without recovering their writers. The block is a strong shared-state seam but not a recovered lifecycle.

## Cell state and object pool

`cCellGame` is a 20,964-byte state object. The current clean-room header preserves selected original offsets while reducing large backing stores to capacity handles. The main pool is at `+0x1c`; query links are at `+0x410c/+0x4110`; current world references are at `+0x411c/+0x4120`; the avatar pool index is at `+0x4124`. `field_514C` at `+0x514c` is written as `1.0f` during `Initialize`, while the per-frame update branches on `field_51E0` at `+0x51e0`.

`cCellGame::Initialize` at `0x00e80ba0` resets a bounded state set, initializes a 4,096-object main cell pool, writes the two `1.0f` timing-adjacent values, and initializes visible-background bounds. The current model intentionally omits unverified app-layer side effects and does not claim a byte-exact replacement of the full object.

`cObjectPool_` is a 28-byte index pool:

| Offset | Field | Contract |
|---:|---|---|
| `0x00` | `mpData` | contiguous element storage |
| `0x04` | `mNextAvailableIndex` | free-list head |
| `0x08` | `mObjectPoolIndentifier` | pool identifier |
| `0x0c` | `mNumObjects` | capacity |
| `0x10` | `mNumAllocatedObjects` | live count |
| `0x14` | `mObjectSize` | element width |
| `0x18` | `field_18` | unresolved |

The first word of each `cCellObjectData` is `mObjectPoolIndex`: it links free objects while idle and stores the object's own index while allocated. This supports bounded allocate/release/index reconstruction, but not a non-Cell universal interpretation of the template.

`cCellObjectData` is 920 bytes. High-value fields include pool index at `+0x00`, idle at `+0x04`, target position/orientation at `+0x08/+0x14`, transform at `+0x48`, elevation at `+0x80`, opacity/target opacity at `+0xa0/+0xa4`, target size at `+0xb4`, model key at `+0xfc`, cell resource at `+0x108`, graphics pool index at `+0x248`, scale at `+0x358`, and query pointer at `+0x35c`.

At `0x00e780a0`, a matching avatar pool index is cleared, old graphics and associated objects are released, a stage-scale change triggers a rebuild, and the pooled object is recreated. This supports a state-first Cell lifecycle but does not recover the GFX subsystem.

## Cell movement boundary

`Simulator::Cell::MovePlayerToMousePosition` at `0x00e5b790` obtains the player, obtains camera origin and direction, intersects the camera ray with a movement plane, writes the hit point to the player's target position, computes travel orientation, and marks movement state. This is direct static body evidence in `docs/analysis/dossiers/cell-movement.md:46`.

Current OpenSpore implements this ray-plane shape in `src/sim/Sim.hpp:107` and `src/sim/Sim.hpp:147`. The load-time movement normal has been recovered as `{0,0,1}`; the plane point is runtime-written BSS. Numeric speeds, eat/flee radii, damping, and keyboard bias remain approximations because no original Cell trace is committed.

## Current source comparison

| Area | Current state | Remaining gap |
|---|---|---|
| `CellGame` | selected exact offsets and observed initialization/create writes | not a byte-exact 20,964-byte replacement; large stores are handles |
| `cCellObjectData` | exact 920-byte size and selected offsets, opaque remainder | most of 192 fields are not semantically modeled |
| `cObjectPool_` | exact 28-byte header, 4,096 capacity, free-list transitions | no original trace and unresolved `field_18` |
| Cell movement | camera-ray to movement-plane steering | per-world point, state names, and numeric gameplay constants |
| manager registry | no frozen replacement model | global writers, subsystem insertion, listener order, mode transitions |

Current source is comparison evidence, not proof that the clean-room implementation matches the original runtime.

## Conflicts and limits

- `cGameData::Write @ 0x00b184c0` has a destructor/teardown-like body and a global reference decrement. The SDK name is preserved; the conflict is unresolved.
- `cObjectPool_::Get @ 0x00b72320` reads owner `+0x88` and switches on three values to return immediate constants, conflicting with an index-pool accessor. The recovered body is treated as contaminated or misidentified.
- `cGameNounManager::GetData` has useful map/update mechanics but contaminated registers, arguments, and recursion; exact callback ABI is unresolved.
- SDK-declared interface fields establish structural multiple-interface layout, not RTTI-proven C++ inheritance.
- Candidate vtable triage contains over-associated `cGameData`/`cToolStrategy` families; only corroborated slot layouts are frozen here.
- No runtime trace reaches Cell Stage. No manager setup/reset order, mode transition, eat/flee rule, animation transition, or persistence round trip is runtime-verified.

## Reconstruction order

1. Find every writer and clearer of `DAT_0167eaf0` through `DAT_0167eb54` and establish manager setup/reset order.
2. Recover `cSimulatorSystem::InitializeSubSystems`, `DisposeSubSystems`, `Update`, and `PostUpdate` bodies and concrete `mSubSystems` insertion order.
3. Recover message-listener registration/priority/removal and game-mode transition ordering.
4. Resolve noun-materialization callback ABI and list/vector update transitions.
5. Resolve the `cGameData::Write`/teardown conflict from constructor and caller evidence.
6. Preserve the exact Cell pool and selected object layout while recovering combat, eating, fleeing, animation, query, graphics, and save/load fields.
7. Acquire an original Cell trace before validating movement, lifecycle, and gameplay numbers.

## Open questions

- Which functions write, replace, and clear the packed manager globals?
- Which concrete managers enter `cSimulatorSystem::mSubSystems`, and in what order?
- What are the exact lifecycle signatures of the unnamed behavior/input/view vtable slots?
- What are the noun-materialization callback contracts and ownership rules?
- Is `cGameData::Write @ 0x00b184c0` mislabeled, misbounded, or dual-purpose?
- What is `cObjectPool_::field_18`?
- Which Cell fields are required for combat, eating, fleeing, animation, query, graphics, and save/load?
- Can an original trace capture Cell Stage and per-world plane state?

## Sources

- `knowledgegraph/research/types/01-simulator-core.json`
- `knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json`
- `docs/analysis/simulator-shared-state-interface.md`
- `knowledgegraph/research/decomp-gap/sim-core-00.json`
- `knowledgegraph/research/decomp-gap/sim-core-01.json`
- `knowledgegraph/research/semantic-atlas.json`
- `knowledgegraph/research/global-campaign-2026/track-d-sim-cell.json`
- `knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl`
- `knowledgegraph/triage/xrefs-2540f2ca.tsv`
- `.spore-analysis/ghidra-exports/structs.tsv`
- `.spore-analysis/ghidra-exports/structs_fields.tsv`
- `.spore-analysis/ghidra-exports/spore_sdk.xml`
- `.spore-analysis/ghidra-exports/functions.tsv`
- `.spore-analysis/ghidra-exports/decompiled_sdk`
- `docs/analysis/vtables.json`
- `docs/analysis/dossiers/cell-movement.md`
- `docs/analysis/dossiers/unknown-high/cell-object-pool-lifecycle.md`
- `src/sim/Sim.hpp`
- `src/sim/CellGame.hpp`
- `src/sim/CellGame.cpp`
- `src/sim/CellPool.hpp`
