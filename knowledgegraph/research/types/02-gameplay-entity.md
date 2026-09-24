# Gameplay and entity-types archaeology partition

## Scope and evidence policy

This partition covers the original gameplay/entity object surface: Cell state and pooled cell objects, query and advection records, Cell presentation/UI ownership, simulator shared-state roots, creature/city/tribe/model/tool families, and serialization/event boundaries. It is a clean-room research artifact for `SporeApp.exe` 3.1.0.22, x86:LE:32, image base `0x00400000`, binary SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`.

No `SPORE/` files, binary/Ghidra state, historical triage artifacts, or OpenSpore implementation files were modified. Live Ghidra had no open program when checked, so this report uses committed artifacts only.

Evidence labels:

- **OBSERVED** — byte-level, static write/read, or current-source fact; not automatically runtime validation.
- **SUPPORTED** — independently reproduced/identity-checked record or parser contract.
- **SUPPORTED** — multiple consistent sources, with a bounded interpretation.
- **INFERRED** — reasoned from one or more sources, not directly established.
- **UNKNOWN** — evidence is insufficient.

SDK and community names are not promoted to binary class identity. Decompilation is evidence, not truth. The current `src/` tree is comparison evidence only; its deterministic contracts and tests do not establish original Spore semantics.

The machine-readable companion is `knowledgegraph/research/types/02-gameplay-entity.json`.

## Executive findings

1. **The strongest gameplay spine is Cell.** `sCellGame/cCellGame` owns a 4,096-cell main pool, query references, world references, avatar index, timing/flags, and serializable state. `cCellObjectData` is a 920-byte gameplay/graphics/animation record. **[SUPPORTED, high; E02, E04, E11, E12]**
2. **Identity is index-mediated.** The avatar is referenced by a pool index, and the pool's first object word is both the free-list link and the allocated object's self-index. The replacement seam still needs a real 32-bit pool lookup. **[SUPPORTED for static mechanics, INFERRED for all runtime ownership; E03, E04, E14]**
3. **Cell content is not runtime truth.** Typed Cell records and the `0x0F43029A` model-group records decode and byte-account well, but placement, population execution, player identity, and runtime AI remain open. **[SUPPORTED for record formats, UNKNOWN for runtime consumption; E09, E11, E17]**
4. **Cell presentation/UI are separate state domains.** `cCellGFX` owns world/layer/effect/preload state; `cCellUI` owns HUD/selection/zoom/rollover state. The current host models them as tokens and small records, not RenderWare/UTFWin objects. **[SUPPORTED, high; E02, E11, E18]**
5. **The broader gameplay graph is not one component architecture.** Creature, city, tribe, tool, editor-model, animation, and shared-state names are real SDK or structural anchors, but no RTTI hierarchy or complete runtime object graph is established. **[INFERRED, medium; E06, E07, E08, E10, E15]**
6. **The largest unresolved gameplay boundary is the unnamed per-frame orchestrator.** `FUN_00e806b0` is a strong static call/branch boundary, but its arguments, continuations, and runtime state are not pinned. **[SUPPORTED for body shape, UNKNOWN for full contract; E02, E03, E16]**

## Types

| ID | Type | Status | Claim and evidence | Confidence | Provenance / limits |
|---|---|---|---|---|---|
| T01 | `Simulator::Cell::sCellGame / cCellGame` | SUPPORTED | 20,964-byte global Cell state object with pool, query, world, avatar, timing, flags, and serializable state. [E02, E04, E11, E12] | high | `track-d-sim-cell.json`; current logical projection is not byte-complete. |
| T02 | `Simulator::Cell::cCellObjectData` | SUPPORTED | 920-byte pooled per-cell record carrying transform, resource, animation, health, GFX, scale, query, flee/chase, and attack-related state. [E02, E04, E10, E12] | high | Cell campaign and `src/sim/CellPool.hpp`; full fields/AI ownership remain open. |
| T03 | `cObjectPool<cCellObjectData>` | SUPPORTED | 28-byte metadata pool, contiguous 920-byte elements, free-list head, capacity, live count, stride, and capacity 4,096. [E02, E04, E08, E12] | high | Cell pool dossier and current pool projection; generic `cObjectPool_` identity is less certain. |
| T04 | `cCellQueryEntry / cCellQueryLinkedPool / cCellQueryLinkedPoolData` | SUPPORTED | Spatial query family stores position, size, next links, and cell pool indices. [E02, E11, E12] | high | Query predicate is bounded; insertion/removal/ordering are unresolved. |
| T05 | `cCellDataReference` | INFERRED | Small Cell world reference object used by current/background state. [E02, E16] | low | `0x00e82340` and SDK-associated `0x00e82420` remain separate. |
| T06 | `cCellSerializableData` | SUPPORTED | Serialization/runtime-state boundary reached from CellGame. [E02, E03, E10, E11] | medium | Field schema, save/load coverage, and round-trip order unknown. |
| T07 | `cCellCellResource / cCellWorldResource / cCellPopulateResource` | SUPPORTED | Typed records provide cell definitions, world/advection data, and population markers. [E11, E12, E17] | high | Record decoding is strong; runtime selection/placement/behavior is not. |
| T08 | `Simulator::Cell::cCellGFX` | SUPPORTED | Presentation singleton with world/layer handles, effect slots, preload records, and display state. [E02, E03, E11, E18] | high | RenderWare ownership/material/live handle lifetime is out of scope. |
| T09 | `Simulator::Cell::cCellUI / cCellUIRollover` | SUPPORTED | HUD/input/selection/zoom state plus health-feedback rollover records. [E02, E03, E11, E18] | high | Current host is a bounded UI projection, not the original graph. |
| T10 | `App::cCellModeStrategy` | SUPPORTED | 27-slot vtable-shaped mode object coordinating CellGame, CellGFX, and CellUI. [E02, E03, E10, E11, E18] | high | Base class and full slot hierarchy unresolved. |
| T11 | `Simulator::cGameInputManager` | SUPPORTED | 276-byte, 27-slot shared input/mode object with named field map. [E05, E06, E10, E15] | high | Name/accessor/field map are strong; routing and ownership are open. |
| T12 | `Graphics::Model / cModelObject` | INFERRED | SDK and targeted static evidence associate a model object with `owner+0x780..0x78c`; no common original class layout is proven. [E06, E08, E10, E13, E15] | low | Do not equate with current `GmdlModel`. |
| T13 | `AnimatedCreature / IAnimWorld / EditorCreatureController` | SUPPORTED | SDK field/vtable evidence links actor, animation world, model, positions, angles, movement/rotation speed, and update/load/destroy operations. [E10, E15] | medium | No complete pose/animation implementation or runtime ownership. |
| T14 | `AnimationMessage` | SUPPORTED | Message ID, name, creature pointer, block index, integer, and float parameter record. [E10, E15] | medium | Message IDs, queue order, and send/post behavior unresolved. |
| T15 | `cCreatureBase / cCreatureGameData / cCreatureAnimal` | SUPPORTED | SDK/vtable families cover ability, target, animation, effects, walking, voice, creation, and AI ticks. [E06, E08, E09, E15, E16] | medium | Most bodies are not persisted; hierarchy and layouts are not proven. |
| T16 | `Simulator::cCity` | SUPPORTED | SDK-attributed city operations cover buildings, vehicles, and above-city tests. [E06, E09, E15] | medium | No current implementation or runtime trace. |
| T17 | `cTribe` | INFERRED | 6,624-byte state object read for int3 position data in the space event builder. [E04, E06] | medium | Structural/decompiler identity only; full ownership/lifecycle unknown. |
| T18 | `Simulator::cGameData / cEmpire` | SUPPORTED | Game-data owner/serialization/write operations; empire identity/cache/map structure. [E05, E06, E15] | high | Game-data schema, cross-stage handoffs, and full empire ownership unresolved. |
| T19 | `cToolStrategy` variants | SUPPORTED | Tool family includes AOE, beam, and UFO-exit strategies with named virtuals. [E06, E08, E15, E16] | medium | Hierarchy, event order, and actor ownership unresolved. |
| T20 | `Editors::EditorModel` | SUPPORTED | Editor model vtable family with `SetColor` at `0x004ae250` and related state operations. [E06, E10, E15, E16] | medium | No RTTI; family membership is structural/name-level. |
| T21 | `Simulator::cObjectPool_` | INFERRED | Generic SDK pool family named Initialize/CreateObject/Get/DeleteObject. [E06, E08, E15] | low | Generic Initialize body/name conflict must be resolved. |
| T22 | `0x0F43029A` world-object record | SUPPORTED | 20-byte header, 1,365 records, part-name strings, vector candidates, complete byte accounting; not CellSerializer. [E11, E13, E17] | high | Record field order and runtime ownership/placement unresolved. |
| T23 | `GmdlModel / Mesh / SceneEntity / openspore::sim::Entity` | OBSERVED | Current host comparison objects only. [E12, E13, E16, E18] | high | No original ABI/runtime claim; current role strings, positions, and events are bounded choices. |

## Fields and offsets

The table records high-value offsets and bounded offsets. Every row is tied to one of the evidence records in the JSON companion.

### Cell state and cell object

| Type | Offset | Field | Status | Evidence |
|---|---:|---|---|---|
| `cCellGame` | `0x001c` | `mCells` main pool | SUPPORTED | E02, E12 |
| `cCellGame` | `0x40fc`, `0x4100` | foreground/background query pools | SUPPORTED | E02, E12 |
| `cCellGame` | `0x4114`, `0x4118` | current/background world references | SUPPORTED | E02, E12 |
| `cCellGame` | `0x411c` | `mAvatarCellIndex` | SUPPORTED | E02, E03, E14 |
| `cCellGame` | `0x514c`, `0x5150` | time scale and adjacent copy, initialized to `1.0f` | OBSERVED | E02, E12 |
| `cCellGame` | `0x5158` | movement/paused guard | INFERRED | E03, E14 |
| `cCellGame` | `0x515c`, `0x51e0` | update gate and mode/state word | INFERRED | E02 |
| `cCellGame` | `0x5190`, nested `0x5270` | serializable state and movement flag | SUPPORTED/INFERRED | E02, E03, E14 |
| `cCellObjectData` | `0x00`, `0x04` | pool index/free-list link and idle flag | SUPPORTED | E04, E12 |
| `cCellObjectData` | `0x08`, `0x14` | target position and orientation quaternion | INFERRED | E03, E14 |
| `cCellObjectData` | `0x48`, `0x80` | transform and relative elevation | SUPPORTED | E02, E12 |
| `cCellObjectData` | `0xa0`, `0xa4`, `0xb4`, `0xbc` | opacity, target opacity, target size, computed size | SUPPORTED | E02, E12 |
| `cCellObjectData` | `0xfc`, `0x108` | model key and Cell resource reference | SUPPORTED | E02, E04, E12 |
| `cCellObjectData` | `0x111`, `0x112` | invulnerability and attack bypass | INFERRED | E02, E11 |
| `cCellObjectData` | `0x1b0`, `0x1b4`, `0x1b8` | animation state and blend fields | SUPPORTED | E10, E11 |
| `cCellObjectData` | `0x21c`–`0x230` | flee/chase state | INFERRED | E02 |
| `cCellObjectData` | `0x244`, `0x248`, `0x358`, `0x35c` | health, GFX index, scale, query ownership | SUPPORTED | E02, E04, E10 |
| `cObjectPool` | `0x00`–`0x18` | buffer, free head, id, capacity, count, stride, tail | SUPPORTED | E08, E12 |
| `cCellQueryEntry` | `0x00`, `0x0c`, `0x10`, `0x14`, `0x18` | position, size, unresolved field, next, cell index | SUPPORTED/UNKNOWN | E02, E12 |

### Presentation, input, model, and identity anchors

| Type | Offset | Field | Status | Evidence |
|---|---:|---|---|---|
| `cCellGFX` | `0x161a0`–`0x161d8` | world handle table | SUPPORTED | E02, E18 |
| `cCellGFX` | `0x161b4`, `0x161bc`, `0x161c8` | persistent effect slots | SUPPORTED | E02, E18 |
| `cCellUI` | `0x80`, `0xbc`, `0x24` | layout constants and rollover disappear time | OBSERVED | E02, E18 |
| `cCellModeStrategy` | `+0x00` | 27-slot vtable | SUPPORTED | E03, E10, E11 |
| `cGameInputManager` | `+0x18`, `+0x1c` | last/current mode | SUPPORTED | E05, E10 |
| `cGameInputManager` | `+0x68`, `+0x6c` | mouse fields | SUPPORTED | E05, E10 |
| `cGameInputManager` | `+0x74`, `+0x90`, `+0xc0` | input regions | SUPPORTED | E05, E10 |
| `cGameInputManager` | `+0xdc`, `+0xec`, `+0xfc`, `+0x110` | strings, vector, unresolved integer | SUPPORTED/UNKNOWN | E05 |
| `cModelObject` candidate | owner `+0x780`–`+0x78c` | three floats and byte copied to caller | INFERRED/UNKNOWN | E08 |
| `AnimatedCreature` | `+0x04`, `+0x10`, `+0x17c`, `+0x180`, `+0x18c`, `+0x190` | position, orientation, creature ID, model, animation index, anim world | SUPPORTED | E10 |
| `cTribe` | `+0x504`, `+0x508`, `+0x50c` | int3 position source for event records | INFERRED | E04, E06 |
| `cEmpire` | `+0x84`; manager `+0x150` | political ID and empire map | SUPPORTED | E05, E06 |
| world-object record | `0x00`–`0x13` and variable body | header, names, vector candidates, byte accounting | SUPPORTED | E11, E13, E17 |

## Vtables and families

| Family | Address/size | Known anchors | Status | Limits |
|---|---|---|---|---|
| `App::cCellModeStrategy` | `0x01485550`, 27 slots | Initialize `0x00e81cf0`; Dispose `0x00e81f30`; OnEnter `0x00e552f0`; OnExit `0x00e7fc00`; OnKeyDown `0x00e818f0`; Update `0x00e80980` | SUPPORTED | Base class and all slot meanings unknown. |
| `Simulator::cObjectPool_` | `0x014650e8` | DeleteObject `0x00b72370` | INFERRED | Generic pool identity conflicts with a targeted Initialize body. |
| `Simulator::cCreatureBase` | `0x0146a5f0` | PlayAnimationTo `0x00c14aa0`; GetAbilityIndexByType `0x00c0c1c0` | SUPPORTED | Family/slot projection only. |
| `Simulator::cCreatureAnimal` | `0x0146a0e0` | AvatarTickAI `0x00c04010` | SUPPORTED | No inheritance proof. |
| `Simulator::cToolStrategy` | `0x013f8100`, `0x0148c008`, `0x014529fc` | OnSelect `0x01053790` | SUPPORTED | Bounded family projection. |
| `Editors::EditorModel` | `0x013ef110` and related candidates | SetColor `0x004ae250` | SUPPORTED | No MSVC RTTI. |
| `cGameInputManager` | address unknown, 27 slots | Get `0x00b3d350` | SUPPORTED | Accessor/interface anchor, not complete vtable map. |
| `AnimatedCreature` / `IAnimWorld` | address unknown | SDK-only PlayAnimation, UpdateCreatures, LoadCreature, DestroyCreature | SUPPORTED | Concrete implementation unknown. |
| Cell state families | no Cell vtable recorded | none | UNKNOWN | Do not invent Cell vtables. |

## Inheritance and ownership relations

- `cObjectPool_` to `cObjectPool<cCellObjectData>` is a supported template/structure relation, not RTTI. **[SUPPORTED, medium; E08, E12]**
- `cCellQueryLinkedPoolData` to `cCellQueryEntry` is a supported structural arena relation, not proven C++ inheritance. **[SUPPORTED, medium; E02, E11]**
- `cCreatureAnimal` from `cCreatureBase` is only a name-level hypothesis. **[INFERRED, low; E06, E08, E15]**
- Tool variants from `cToolStrategy` are a family hypothesis, not proven single inheritance. **[INFERRED, low; E06, E15]**
- `cCellGame` to `cCellGFX`/`cCellUI` is coordination through mode state, not demonstrated inheritance. **[UNKNOWN, high; E02, E11]**
- `AnimatedCreature` and `EditorCreatureController` are associated through fields and calls, not a proven subclass relation. **[UNKNOWN, low; E10, E15]**
- `Graphics::Model`, `cModelObject`, and `AnimatedCreature` must not be collapsed into one model ABI without owner/layout data-flow. **[UNKNOWN, high; E06, E08, E10]**

## Lifecycle

1. **Mode initialize:** `cCellModeStrategy::Initialize` (`0x00e81cf0`) coordinates CellGame, CellGFX, and CellUI; CellGame initializes the 4,096-cell pool and state flags. **[SUPPORTED, high; E02, E03, E11]**
2. **Mode enter:** `OnEnter` (`0x00e552f0`) and `cCellGFX::StartDisplay` (`0x00e55120`) activate display/world/UI state. **[SUPPORTED, high; E02, E11]**
3. **Object create:** `CreateCellObject` (`0x00e74a20`) pops a free pool entry, initializes size/orientation/position/elevation/opacity/transform/model/scale/query/effect state, and returns an index. **[SUPPORTED, high; E02, E04, E12]**
4. **Object release/rebuild:** `FUN_00e780a0` clears a matching avatar reference, releases old GFX/associated state, rebuilds on scale change, and recreates the pooled object. **[SUPPORTED, medium; E04, E06]**
5. **Object reuse/deallocate:** the free-list link is the first object word; allocation changes it to the object's own index and deallocation returns it to the head. **[SUPPORTED for Cell projection, INFERRED for generic DeleteObject; E04, E08, E12]**
6. **Active update:** `cCellModeStrategy::Update` delegates to `FUN_00e806b0`; the latter gates state, scales delta, calls movement, and dispatches further Cell/AI/GFX/effect work. **[SUPPORTED for branch/call shape, UNKNOWN for full order; E02, E03, E14]**
7. **Query/interact:** query entries identify existing cells by pool index; attack/scale/damage/advect functions consume those identities and resources. **[SUPPORTED, medium; E02, E11, E12]**
8. **Mode exit/dispose:** `OnExit` and `Dispose` restore global/display state and release Cell presentation/state resources. **[SUPPORTED, medium; E02, E03, E11]**
9. **Serialization boundary:** CellGame reaches serializable state and `cGameData` has owner/write operations, but save/load schema and rehydration order are not established. **[INFERRED, low/medium; E10, E11, E20]**

## Major methods and consumers

| Address | Method | Consumer/role | Status |
|---:|---|---|---|
| `0x00e80ba0` | `cCellGame::Initialize` | mode initialization, pool and state roots | SUPPORTED |
| `0x00e74a20` | `CreateCellObject` | cell population and lifecycle | SUPPORTED |
| `0x00e5b790` | `MovePlayerToMousePosition` | avatar target/orientation/moving writes | SUPPORTED |
| `0x00e806b0` | `FUN_00e806b0` | real per-frame Cell orchestrator | SUPPORTED / INFERRED contract |
| `0x00e5b2e0` | `FUN_00e5b2e0` | UI/world plane and avatar target update | SUPPORTED / INFERRED meaning |
| `0x00e780a0` | pool lifecycle | avatar detach, GFX release/rebuild, recreation | SUPPORTED |
| `0x00b72160` | `cObjectPool_::Initialize`/unresolved body | generic pool boundary | INFERRED |
| `0x00b72260` | `cObjectPool_::CreateObject` | generic pooled object creation | SUPPORTED name-level |
| `0x00b72320` | `cObjectPool_::Get` | generic pooled object lookup | SUPPORTED name-level |
| `0x00b72370` | `cObjectPool_::DeleteObject` | generic object release | SUPPORTED name-level |
| `0x00e5dba0` | `cCellGFX::Initialize` | world/layer/effect initialization | SUPPORTED |
| `0x00e666f0` | `cCellGFX::PreloadResources` | cell/populate resource preload | SUPPORTED |
| `0x00e55120` | `cCellGFX::StartDisplay` | display activation | SUPPORTED |
| `0x00e66840` | `InstanceEffectOnCell` | visual effect instance and placement | SUPPORTED |
| `0x00e63560` | `LoadEffectMap` | persistent three-slot effect selection | SUPPORTED |
| `0x00e54270` | `cCellUI::Load` | HUD/rollover initialization | SUPPORTED |
| `0x00e62340` | `ShowHealthRollover` | health feedback allocation | SUPPORTED |
| `0x00e81cf0` | `cCellModeStrategy::Initialize` | mode/singleton coordination | SUPPORTED |
| `0x00e552f0` | `cCellModeStrategy::OnEnter` | mode entry/display start | SUPPORTED |
| `0x00e80980` | `cCellModeStrategy::Update` | vtable adapter to orchestrator | SUPPORTED |
| `0x00b3d350` | `cGameInputManager::Get` | shared input/mode service accessor | SUPPORTED |
| `0x00c37230` | `cModelObject_GetScale` | candidate model field accessor | INFERRED |
| `0x00c14aa0` | `cCreatureBase::PlayAnimationTo` | creature animation virtual | SUPPORTED name/vtable |
| `0x00c1d460` | `cCreatureBase::CreateAndStartEffectForPool1` | creature effect-pool operation | SUPPORTED name/vtable |
| `0x00c04010` | `cCreatureAnimal::AvatarTickAI` | creature actor AI virtual | SUPPORTED name/vtable |
| `0x00c099e0` | `cCreatureAnimal::Create` | creature actor creation | SUPPORTED name-level |
| `0x00bdde70` | `cCity::SpawnVehicle` | city actor mutation | SUPPORTED name-level |
| `0x00b18490` | `cGameData::SetGameDataOwner2` | ownership mutation | SUPPORTED name-level |
| `0x00b184c0` | `cGameData::Write` | serialization/write boundary | SUPPORTED name-level |
| `0x01052f90` | `cDefaultAoETool::OnMouseDown` | tool input virtual | SUPPORTED name/vtable |
| `0x01053db0` | `cDefaultBeamTool::func4Ch` | tool virtual | SUPPORTED name/vtable |
| `0x01054080` | `cGetOutOfUFOToolStrategy::OnSelect` | tool selection virtual | SUPPORTED name/vtable |
| `0x004ae250` | `Editors::EditorModel::SetColor` | editor model mutation | SUPPORTED name/address |

## Major consumers and subsystem boundaries

### Cell state and entity spine

The stable chain is `sCellGame -> cObjectPool<cCellObjectData> -> cCellObjectData`, with `mAvatarCellIndex` and query records providing entity identity. The important consumers are `CreateCellObject`, `MovePlayerToMousePosition`, cell lifecycle, query/attack logic, and mode update. **[SUPPORTED, high; E02, E03, E04, E15, E16]**

### Cell content and world population

`cCellCellResource`, `cCellWorldResource`, `cCellPopulateResource`, and `0x0F43029A` records are content inputs. They can identify model/resource keys, advection data, markers, and part names, but they do not prove original runtime placement, player identity, or AI execution. **[SUPPORTED for records, UNKNOWN for runtime consumption; E09, E11, E17]**

### Cell presentation and UI

`cCellGFX` and `cCellUI` are coordinated by the mode lifecycle. World/layer order, preload key association, effect slots, UI constants, and health rollover formulas are stronger than original RenderWare/UTFWin ownership and timing. **[SUPPORTED, high; E02, E11, E18]**

### Shared Simulator state

The eleven-root interface freeze identifies unresolved global/service slots, input/mode state, current-planet/context accessors, lazy empire caching, noun materialization, map lookup, and an opaque mixed scalar/pointer boundary. These roots are prerequisites for dependent gameplay but are not a single service. **[SUPPORTED, high; E05, E06, E15, E16]**

### Creature, city, tribe, model, and tools

Creature/city/tribe/model/tool names are real SDK or structural anchors with consumers, but no complete cross-stage component graph is established. Animation/model boundaries are especially distinct from Cell gameplay state. **[INFERRED, medium; E04, E06, E08, E09, E10, E15]**

### Serialization and events

`cCellSerializableData`, `cGameData`, `AnimationMessage`, and the space event-record pair demonstrate mode-specific persistence/event records. Current `SimEvent` is local deterministic contract surface, not an original event ABI. **[INFERRED, medium; E10, E11, E20]**

## Reconstruction relevance

| Priority | Candidate | Reconstruction value | Gate |
|---:|---|---|---|
| 0 | `CellGameStateFacade` | Preserve player index, world/query references, timing/lock/update gates, serializable state, and lifecycle ordering. | Positive Cell trace and field semantics. |
| 0 | `CellObjectLifecycle` | Preserve pool-index identity, create/free/reuse, GFX association release, and scale-change rebuild. | Generic pool contradiction and GFX release/rebuild callees. |
| 0 | `CellFrameOrchestrator` | Preserve state-gated frame order and continuation boundaries. | Unnamed arguments, service order, runtime state. |
| 1 | `CellSpatialInteraction` | Preserve candidate handles, pool indices, scale/damage/attack predicates, and unknown event boundaries. | Query order, AI wiring, event transport. |
| 1 | `CellContentAndPresentation` | Preserve content key triples, model/world/populate associations, world order, effect slots, and UI feedback. | Placement, handle lifetime, material/HUD timing, preload order. |
| 1 | `SharedStateInterfaceFreeze` | Characterize raw global/service handles, null/sentinel behavior, map lower-bound semantics, and lazy reference management. | Ten unnamed roots and mixed scalar/pointer roots. |
| 1 | `CreatureAnimationComponentModel` | Recover separate creature/model/animation relations before generalizing entities. | Address-level vtable map, owner/layout data flow, pose/message trace. |
| 2 | `SerializationAndOwnership` | Map Cell/game-data ownership, writes, and mode-specific event records without inventing a universal ABI. | Schema/version/default behavior, save/load coverage, queue order, round-trip oracle. |

## Unresolved questions

1. What are the full `cCellObjectData` fields from `+0x100` through `+0x358`, and which own AI, health, damage, animation, power, projectile, and effect state? **[UNKNOWN, high; E02, E10, E11]**
2. What do `sCellGame+0x5158`, `+0x515c`, `+0x51d8`, `+0x51d9`, and `+0x51e0` mean? **[INFERRED access, UNKNOWN meaning; E02, E03]**
3. What are the exact arguments and continuation order of `FUN_00e806b0` and `FUN_00e5b2e0`? **[UNKNOWN, high; E02, E03]**
4. How are `cCellQueryLinkedPool` entries inserted, removed, partitioned, and ordered? **[UNKNOWN, high; E02, E12]**
5. How do generic `cObjectPool_` addresses and names resolve against the SDK `Initialize` label, and what are exact create/get/delete contracts? **[INFERRED, high; E06, E08, E15]**
6. What are the exact Cell vtable slots and unknown-vtable implementations for CellGame, CellGFX, and CellUI? **[UNKNOWN, high; E02, E07, E11]**
7. Which runtime resources populate the world and what creates player-cell identity and placement? **[UNKNOWN, high; E09, E11, E17, E18]**
8. What is the complete Cell/game-data save/load schema, version/default behavior, and cross-stage handoff? **[UNKNOWN, high; E10, E20]**
9. What is the original event/message path for eat, damage, death, animation, effects, and health feedback? **[UNKNOWN, high; E03, E10, E20]**
10. What concrete owner, layout, and vtable implementation correspond to `cModelObject`/`Graphics::Model`, `cCreatureBase`, `cCreatureAnimal`, and the editor model family? **[UNKNOWN, high; E06, E07, E08, E10]**
11. Can a positive original Cell trace correlate avatar pointer/index, mode state, per-world plane point, camera/UI gates, and pool reuse? **[UNKNOWN, high; E03, E14, E16]**

## Evidence and provenance index

- **E01** — Binary identity and image base; **SUPPORTED, high**.
- **E02** — `knowledgegraph/research/global-campaign-2026/track-d-sim-cell.json`; Cell roots, structures, lifecycle, functions, dependencies, and gaps; **SUPPORTED, high**.
- **E03** — `docs/analysis/dossiers/cell-movement.md`; movement, pool lookup, vtable flow, and negative runtime evidence; **SUPPORTED, high**.
- **E04** — `docs/analysis/dossiers/unknown-high/cell-object-pool-lifecycle.md`; avatar detach, GFX release/rebuild, 17 callers; **SUPPORTED, medium**.
- **E05** — `docs/analysis/simulator-shared-state-interface.md` and shared-state triage; roots, fields, null/sentinel/cache/map behavior; **SUPPORTED, high**.
- **E06** — `knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl` and unknown-high resolution; SDK/vtable anchors, categories, and unknown families; **SUPPORTED, high**.
- **E07** — `docs/analysis/vtables.json`; vtable candidates and structural families; no RTTI; **SUPPORTED, high**.
- **E08** — decomp-gap `sim-core-00.json`, `sim-core-02.json`, `sim-core-03.json`; pool mechanics, model candidate, creature virtuals; **SUPPORTED, medium**.
- **E09** — `docs/analysis/campaigns/cell-stage-campaign.md`; Cell record census, SDK structure anchors, player/entity boundary; **SUPPORTED, high**.
- **E10** — `knowledgegraph/research/global-campaign-2026/track-g-editor-ui-input.json`; animation/model/input/event boundaries; **SUPPORTED, medium**.
- **E11** — Cell structure/resource synthesis; sizes, offsets, query/advection/content inputs; **SUPPORTED, high**.
- **E12** — current `src/sim` comparison; typed projections and explicit approximation labels; **OBSERVED, high**.
- **E13** — current `src/assets` comparison; WorldObject/GMDL/Mesh structures; **OBSERVED, high**.
- **E14** — replacement ABI and replacement seam; movement offsets, guards, and decomp-reference-only status; **SUPPORTED, medium**.
- **E15** — xref summary/TSV and dependency census; structural consumers/fan-in; **SUPPORTED, high**.
- **E16** — coverage/readiness artifacts; denominators, blockers, and reconstruction ordering; **SUPPORTED, high**.
- **E17** — Cell campaign asset decoders/tests; record sizes, references, byte accounting; **SUPPORTED, high**.
- **E18** — current `src/apps` presentation/lifecycle source; world tokens, UI rollover, lifecycle, animation/effect contracts; **OBSERVED, high**.
- **E19** — coverage and semantic atlas; 172/2,149 gameplay bodies, all contracts unknown, zero runtime-validated functions; **SUPPORTED, high**.
- **E20** — event dossiers and editor/input campaign; space records, game-data writes/owners, separate event grammars; **INFERRED, medium**.

## Source boundary

This report is a static research partition. It deliberately does not alter `SPORE/`, does not mutate Ghidra, does not rewrite historical triage, and does not implement or validate OpenSpore replacement behavior. The current source and tests are comparison surfaces only. The deterministic OpenSpore Cell contract and its 64/64 decompilation-reference differential remain bounded replacements, not original runtime evidence.
