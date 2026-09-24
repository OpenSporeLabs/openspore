# Managers, service singletons, registries, and pools

## Scope and snapshot

This is a read-only, clean-room archaeology partition for Spore 3.1.0.22 `SPORE/SporeBin/SporeApp.exe` (`x86:LE:32`, image base `0x00400000`, SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`). It characterizes access patterns, collection layouts, lifecycle boundaries, ownership evidence, conflicts, and replaceable contracts without copying proprietary code or assets.

- Triage snapshot: `f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b`
- Xref snapshot: `2540f2ca7cd361a72b559448fa5cf247eff3cee20d375b14ed0dd256c45229c8`
- SDK commit: `cbf9206b9a823f0911cd9be0217104a49d72380b`
- Runtime evidence: none
- MSVC RTTI: absent

Evidence precedence is direct body and field access, then committed dossiers, SDK structures/functions/vtables, canonical xrefs, and historical wording. SDK labels are reference provenance rather than runtime truth. A getter or vtable does not by itself prove ownership.

## Principal findings

1. The SDK export contains 66 exact `::Get` anchors, but only a subset read stable global service slots. Other accessors are indirect, factory-derived, mode-derived, thread-local, pool-related, or unresolved.
2. The `0x00b3d220-0x00b3d5a0` simulator accessor region is heterogeneous. It contains named SDK anchors, unnamed six-byte functions, longer bodies, and imported anchors absorbed into neighboring Ghidra functions; address order is not a service-table order.
3. `Simulator::cSimulatorSystem+0x5c` owns an intrusive `ISimulatorStrategy` vector and is the central simulator composition boundary.
4. Manager collections include intrusive lists and vectors, EASTL vectors and maps, hash maps, ordered maps, nested vectors, sets, mutexes, and fixed-pool allocators.
5. The main Cell pool is a 4096-element pool of 920-byte objects. The first object word is a free-list link while free and the object's own index while allocated.
6. Original global access, vtable ABIs, EASTL layouts, allocator internals, RenderWare/D3D dependencies, and the original global spine are replaceable. Semantic identities, ordering, ownership, handles, and lifecycle contracts are not automatically replaceable.

**Evidence:** VERIFIED/SUPPORTED from `sdk_functions.tsv`, `functions.tsv`, `structs.tsv`, `structs_fields.tsv`, targeted decompilation, the canonical shared-state dossier, and campaign tracks. **Confidence:** high.

## Accessor classification

### Direct application services

| Slot | SDK identity | Accessor |
|---|---|---|
| `0x015fd890` | `App::IAppSystem` | `0x0067dcc0` |
| `0x015fd894` | `App::IGameModeManager` | `0x0067dcd0` |
| `0x015fd898` | `App::IStateManager` | `0x0067dce0` |
| `0x015fd89c` | `App::IConfigManager` | `0x0067dcf0` |
| `0x015fd8b0` | `Graphics::IRenderer` | `0x0067dd10` |
| `0x015fd8b4` | `Graphics::ITextureManager` | `0x0067dd20` |
| `0x015fd8b8` | `Graphics::IMaterialManager` | `0x0067dd30` |
| `0x015fd8bc` | `Graphics::IModelManager` | `0x0067dd40` |
| `0x015fd8c0` | `Graphics::ILightingManager` | `0x0067dd50` |
| `0x015fd8c4` | `Graphics::IRenderTargetManager` | `0x0067dd60` |
| `0x015fd8c8` | `Graphics::IThumbnailManager` | `0x0067dd70` |
| `0x015fd8cc` | `Graphics::IShadowWorld` | `0x0067dd80` |
| `0x015fd8d0` | `Swarm::IEffectsManager` | `0x0067dd90` |
| `0x015fd8dc` | `App::IMessageManager` | `0x0067dc80` |
| `0x015fd8ec` | `App::ICheatManager` | `0x0067dde0` |
| `0x015fd8f0` | `App::IPropManager` | `0x0067ddf0` |
| `0x015fd8f4` | `App::cLocaleManager` | `0x0067de00` |

These are verified direct slot reads. Their process-lifetime owner is not inferred from the global address.

### Simulator services

| Slot | SDK identity or status | Accessor |
|---|---|---|
| `0x0167eac4` | unresolved | direct slot body |
| `0x0167eaf0` | `Simulator::cSimulatorSystem` | `0x00b3d330` |
| `0x0167eaf4` | `Simulator::cGameViewManager` | `0x00b3d340` |
| `0x0167eaf8` | `Simulator::cGameInputManager` | `0x00b3d350` |
| `0x0167eafc` | `Simulator::cGameBehaviorManager` | `0x00b3d360` |
| `0x0167eae0` | unresolved | direct slot body |
| `0x0167eae4` | unresolved | direct slot body |
| `0x0167eaec` | unresolved | direct slot body |
| `0x0167eb04` | unresolved | direct slot body |
| `0x0167eb0c` | `Simulator::cStarManager` | `0x00b3d3a0` |
| `0x0167eb14` | `Simulator::cRelationshipManager` | `0x00b3d3c0` |
| `0x0167eb2c` | `Simulator::cGameModeManager` | `0x00b3d420` |
| `0x0167eb34` | `Simulator::cGamePersistenceManager` | `0x00b3d440` |
| `0x0167eb38` | `Simulator::cPlanetModel` | `0x00b3d450` |
| `0x0167eb3c` | `Simulator::cGameTimeManager` | `0x00b3d480` |
| `0x0167eb40` | `Simulator::cToolManager` | `0x00b3d490` |
| `0x0167eb50` | `Simulator::cSpaceTrading` | `0x00b3d4d0` |
| `0x0167eb54` | `Simulator::cUIEventLog` | `0x00b3d4e0` |
| `0x0167eb60` | `Simulator::cGameNounManager` | `0x00b3d400` |
| `0x0167eb64` | UI mission log manager | `0x00b3d4f0` |

The slot order is not the accessor-address order. The unresolved editor-stage range `0x015d0c04-0x015d0c28` contains ten contiguous pointer candidates whose identities are not established here.

### Remaining SDK `::Get` anchors

The exact inventory in the JSON file contains all 66 anchors. The non-direct groups are:

- Editor, palette, Sporepedia, skinning, UI, animation, audio, class, command-line, terrain, time-of-day, scenario, player-UFO, and space-game accessors with unresolved access paths.
- `Resource::IResourceManager::Get`, `App::IClassManager::Get`, `App::cIDGenerator::Get`, and `App::IJobManager::Get`, which are SDK anchors but not proven stable global-slot reads in this partition.
- `cPlantSpeciesManager::Get` `0x00b3d520`, `cTerraformingManager::Get` `0x00b3d530`, `cAnimalSpeciesManager::Get` `0x00b3d550`, `cSpaceGfx::Get` `0x00b3d570`, and `cCommManager::Get` `0x00b3d5a0`, classified as factory- or mode-derived candidates.
- `cMissionManager::Get` `0x00feb880`, classified as a mode- or owner-derived candidate.
- `Simulator::cObjectPool_::Get` `0x00b72320`, treated as a pool constructor or factory anchor rather than a service getter.

**Evidence:** the SDK function export is VERIFIED; the direct-slot and access-class assignments are SUPPORTED by direct bodies and the shared-state dossier. **Confidence:** high for anchors and direct slots, medium for factory/mode-derived classification.

## Registries and lookup containers

| Owner | Offset | Layout | Responsibility |
|---|---:|---|---|
| `Simulator::cSimulatorSystem` | `0x5c` | `vector<intrusive_ptr<ISimulatorStrategy>>` | Compose simulator strategies and mediate mode/update lifecycle |
| `Simulator::cSimulatorSystem` | `0x20` | `list<intrusive_ptr<ISimulatorUIGraphic>>` | Track updatable UI graphics |
| `App::cGameModeManager` | `0x14` | `vector<ModeEntry>` | Store mode pointer, ID, and name; active index is `+0x28` |
| `App::cMessageManager` | `0x70` | `hash_map<unsigned int, list<IMessageListener *>>` | Route message IDs to listeners; mutex at `+0x90` |
| `Simulator::cGameNounManager` | `0x98` | `map<unsigned int, tGameDataVectorT<cGameData>>` | Index nouns; live noun list at `+0x78`, objects at `+0x10c` |
| `Simulator::cToolManager` | `0x38` | `hash_map<unsigned int, intrusive_ptr<cToolStrategy>>` | Map tool IDs to strategies |
| `Resource::cResourceManager` | `0x30` | `FactoriesMap_t` | Resource factory dispatch; type maps at `+0x54/+0x78`, cache at `+0x9c` |
| `App::cPropManager` | `0x74` | `hash_map<ResourceID, intrusive_ptr<PropertyList>>` | Materialize property lists; name and group indexes follow at `+0x94` onward |
| `Simulator::cStarManager` | `0x150` | `EmpiresMap` | Index empires; relationship manager at `+0x204` |
| `Simulator::cMissionManager` | `0xa8` | `vector<intrusive_ptr<cMission>>` | Track missions; tutorial and recent-mission state are adjacent fields |
| `Simulator::cCommManager` | `0x20` | `vector<intrusive_ptr<cCommEvent>>` | Retain communication events; current event at `+0x1c` |

`App::cGameModeManager::ModeEntry` is 24 bytes: `mpMode` at `+0x00`, `mModeID` at `+0x04`, and `mpName` at `+0x08`. The manager stores `mnActiveIndex` at `+0x28`, `mpCameraMgr` at `+0x2c`, and `mpViewer` at `+0x30`.

**Evidence:** imported structure fields and targeted static bodies. **Confidence:** high.

## Pools and allocators

### Main Cell pool

`Simulator::cObjectPool_` is 28 bytes:

| Offset | Field |
|---:|---|
| `0x00` | `mpData` |
| `0x04` | `mNextAvailableIndex` |
| `0x08` | `mObjectPoolIdentifier` |
| `0x0c` | `mNumObjects` |
| `0x10` | `mNumAllocatedObjects` |
| `0x14` | `mObjectSize` |
| `0x18` | trailing state field |

The main Cell pool is backed by 4096 elements of 920 bytes and is embedded in Cell-stage state at `sCellGame+0x001c`. The first object word is the free-list link while free and the object's own index while allocated. Two additional pool candidates occur at `sCellGame+0x40fc` and `sCellGame+0x4100`; their element types, capacities, and consumers remain unresolved.

### Fixed-pool allocator

`FixedPoolAllocator` is 32 bytes with `mpAllocator` at `+0x04` and `mnObjectSize` at `+0x14`. It is used by `cResourceManager+0xd4`, `PFIndexModifiable+0x08`, and database directory storage. `PFHoleTable` is a 32-byte object with a 28-byte `set<HoleRecord>` at `+0x04`; packed-file storage uses it at `+0x33c` and `+0x35c`.

**Evidence:** direct field layout, Cell dossier, and current `src/sim/CellPool.hpp`. **Confidence:** high for the main pool; medium for the two query-pool identities.

## Vtable families

- `App::IGameMode`: 16 slots; `cCellModeStrategy` candidate at `0x01485550` has 27 slots.
- `App::IGameModeManager`: concrete `App::cGameModeManager` candidate at `0x01412598` has 23 slots.
- `Simulator::ISimulatorStrategy`: shared strategy interface implemented by simulator system, noun, star, tool, and communication managers.
- `Resource::IResourceManager`: 38 slots with `Resource::cResourceManager` concrete candidate.
- `App::IMessageManager`: 19 slots with `App::cMessageManager` concrete candidate.

These are interface and data-layout facts, not proof that every concrete candidate is a unique runtime class in the absence of MSVC RTTI.

## Lifecycle and ownership boundaries

1. Application bootstrap establishes the application service spine before stage-specific services are consumed.
2. `IGameMode` implementations are registered in `App::cGameModeManager::mEntries`; active selection drives enter and exit callbacks.
3. `cSimulatorSystem` owns intrusive simulator strategies; consumers reach individual services through the mixed accessor family.
4. `cMessageManager` stores listeners by message ID and uses a listener mutex.
5. Cell-stage initialization establishes the main pool and query candidates; disposal releases stage resources and resets global stage pointers.

These are static lifecycle boundaries. The exact mode-by-mode registration, update, transition, and teardown order is not runtime-verified.

### Replaceable versus semantic contracts

| Boundary | Retain | Replace |
|---|---|---|
| Application services | Service identity, dependencies, lifecycle visibility | Global slots, wrapper ABI, static access |
| Simulator strategies | Roles, transitions, update dependencies | EASTL vector, intrusive ABI, global spine |
| Mode registry | Mode ID, name, registration order, active selection, enter/exit order | Original vtable ABI and global access |
| Registries | Key/value domains, one-to-many behavior, ordering, handle stability, mutation atomicity | EASTL ABI, raw intrusive pointers, mutex implementation |
| Resource service | Resource identity, lookup, factory dispatch, caching, invalidation, errors | 38-slot ABI, allocator internals, RenderWare/D3D |
| Cell pool | Capacity, element size, stable indices, live count, reuse | Global stage pointer and original ABI where unnecessary |

The clean-room direction is explicit service composition, typed registries, scoped ownership, stable semantic handles, and backend seams rather than reproduction of the original global spine.

## Conflicts preserved

- Historical 15/16-manager counts do not match the SDK inventory, named slots, unnamed gaps, and factory-derived accessors.
- The `0x00b3d240-0x00b3d5a0` range is not a uniform global-getter table.
- `0x00b3d2a0` is not securely identified as a player-ID accessor; mixed consumers leave the identity unresolved.
- `0x00b321340` is not securely identified as message-handler registration; noun-map materialization is a competing explanation.
- The mode-entry vector belongs to `App::cGameModeManager+0x14`, not the same-named `Simulator::cGameModeManager+0x14` field.
- Decompiler type names are not authoritative where they conflict with imported SDK structures.

## Unknowns

- Complete `ISimulatorStrategy` registration and update order.
- Exact service/return identities for the unnamed simulator accessors.
- Service identities and owners of the ten editor-stage slots.
- Concrete element types, capacities, and consumers of the two Cell query pools.
- Runtime-observed initialization, update, mode-transition, and teardown sequences.

## Current OpenSpore comparison

- `src/sim/CellPool.hpp` models the 28-byte manager and 920-byte Cell object, including the free-list/self-index contract, but is owned by typed `CellGame` state rather than the original global stage pointer.
- `src/apps/CellModeStrategy.hpp` uses an explicit `IGameMode` vector, active index, and scoped `CellGfx`/`CellUI` ownership; it replaces the original vtable ABI and global access.
- `src/compat/ResourceProvider.hpp` exposes lookup by type, group, and instance with DBPF and in-memory providers; it preserves semantic identity while replacing the original 38-slot manager and backend coupling.

## Primary provenance

- `.spore-analysis/ghidra-exports/sdk_functions.tsv`
- `.spore-analysis/ghidra-exports/functions.tsv`
- `.spore-analysis/ghidra-exports/structs.tsv`
- `.spore-analysis/ghidra-exports/structs_fields.tsv`
- `.spore-analysis/ghidra-exports/vtables.json`
- `.spore-analysis/ghidra-exports/decompiled_sdk/`
- `knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json`
- `knowledgegraph/research/global-campaign-2026/track-d-sim-cell.json`
- `knowledgegraph/research/global-campaign-2026/track-f-empire-economy.json`
- `knowledgegraph/research/global-campaign-2026/track-j-dependency-graph.json`
- `knowledgegraph/research/global-campaign-2026/track-k-engine-boundaries.json`
- `docs/RECON-3.1.0.22.md`
- `src/sim/CellPool.hpp`
- `src/apps/CellModeStrategy.hpp`
- `src/compat/ResourceProvider.hpp`
