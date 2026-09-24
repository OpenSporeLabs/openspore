# Types evidence brief

## Scope and count discipline

This brief synthesizes all worker artifacts `00-corpus-inventory` through `16-misc-unknown` for `SporeApp.exe` 3.1.0.22 (`x86:LE:32`, image base `0x00400000`, SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`).

The corpus is static research evidence. The canonical corpus contains **58,757** functions/VAs, **223,704** deduplicated xref edges, **2,035** current Ghidra structures, **25,546** structure fields, **3,081** vtable candidates, and **11,898** vtable-reference edges. It records **0** function-level runtime validations. The binary has no MSVC RTTI.

Counts are deliberately partitioned:

- **Exact** means exact for the named source population and unit.
- **De-duplicated estimate** means a reconciliation is defensible; unlike populations are not added.
- **Unknown** means no defensible unique total exists in the worker corpus.
- Static graph counts are not runtime reachability. Caller, callee, distinct-function, edge-row, candidate, label, association, and chain units remain separate.

## Evidence levels

- **OBSERVED**: directly present in a committed artifact, pinned count, field/byte record, or bounded static operation.
- **SUPPORTED**: multiple consistent static sources or direct static agreement; not function-level original runtime validation.
- **INFERRED**: bounded identity, ownership, semantic, or reconstruction conclusion from names, topology, fields, or partial bodies.
- **UNKNOWN**: the corpus does not establish the claim, population, or type identity.

## Worker artifact register

| Artifact ID | Files | Primary contribution |
|---|---|---|
| `00-corpus-inventory` | `00-corpus-inventory.json`, `00-corpus-inventory.md` | Corpus authority, provenance, baseline populations |
| `01-simulator-core` | `01-simulator-core.json`, `01-simulator-core.md` | Simulator services, shared state, Cell core |
| `02-gameplay-entity` | `02-gameplay-entity.json`, `02-gameplay-entity.md` | Gameplay/entity and Cell lifecycle |
| `03-creature` | `03-creature.json`, `03-creature.md` | Creature, editor-model, animation, evolution |
| `04-world-planet` | `04-world-planet.json`, `04-world-planet.md` | Star, planet, terrain, climate, world |
| `05-empire-space` | `05-empire-space.json`, `05-empire-space.md` | Empire, space, economy, missions, diplomacy |
| `06-editor-ui` | `06-editor-ui.json`, `06-editor-ui.md` | Editor, input, UTFWin, messages, UI |
| `07-event-message` | `07-event-message.json`, `07-event-message.md` | Events, messages, dispatch, commands |
| `08-persistence-serialization` | `08-persistence-serialization.json`, `08-persistence-serialization.md` | Resource database, properties, serializers, save state |
| `09-asset-content` | `09-asset-content.json`, `09-asset-content.md` | Packages, graphics, textures, Cell content |
| `10-managers-registries` | `10-managers-registries.json`, `10-managers-registries.md` | Singletons, managers, registries, pools |
| `11-vtable-archaeology` | `11-vtable-archaeology.json`, `11-vtable-archaeology.md` | Vtable candidates, slot status, contradictions |
| `12-field-archaeology` | `12-field-archaeology.json`, `12-field-archaeology.md` | Offsets, repeated layouts, containers, fan-out |
| `13-lifecycle` | `13-lifecycle.json`, `13-lifecycle.md` | Allocation, initialization, reuse, cleanup |
| `14-class-families` | `14-class-families.json`, `14-class-families.md` | Class/interface family census and trees |
| `15-reconstruction-relevance` | `15-reconstruction-relevance.json`, `15-reconstruction-relevance.md` | Reuse, unlock leverage, semantic interfaces |
| `16-misc-unknown` | `16-misc-unknown.json`, `16-misc-unknown.md` | Unowned forwarding, container, vtable, record candidates |

## Baseline and population conflicts

| Population | Exact count | Unit | Evidence |
|---|---:|---|---|
| Canonical functions / unique VAs | 58,757 | functions | OBSERVED; `00-corpus-inventory`, `11-vtable-archaeology` |
| Canonical xrefs | 223,704 | deduplicated reference edges | OBSERVED; `00-corpus-inventory`, `15-reconstruction-relevance` |
| Current Ghidra structures | 2,035 | structures | OBSERVED; `00-corpus-inventory`, `12-field-archaeology` |
| Current structure fields | 25,546 | fields | OBSERVED; `00-corpus-inventory`, `12-field-archaeology` |
| Raw SDK XML structures | 1,895 | structures | OBSERVED; `00-corpus-inventory`, `03-creature`, `05-empire-space` |
| Vtable candidates | 3,081 | candidate bases | OBSERVED; `00-corpus-inventory`, `11-vtable-archaeology`, `16-misc-unknown` |
| Vtable-reference edges | 11,898 | reference rows | OBSERVED; `00-corpus-inventory`, `11-vtable-archaeology` |
| Runtime-validated functions | 0 | functions | OBSERVED; `00-corpus-inventory`, `02-gameplay-entity` |

Do not merge these populations: the vtable scan reports 58,756 functions, the canonical triage/xref universe reports 58,757, and the prior live manager count reports 59,245 including externals. The SDK XML has 1,895 structures while the current Ghidra/semantic atlas has 2,035. The current KG field count is 25,561 in the inventory artifact; it is not silently substituted for 25,546.

## 1. Recovered classes and types

### Counts

- **Exact:** 1,250 class/interface nodes, comprising 33 class-specific binary virtual-slot matches, 18 SDK-association-only anchors, and 1,199 naming-only families (`14-class-families`, OBSERVED).
- **Exact selected catalogs:** 15 simulator-core types (`01-simulator-core`), 23 gameplay/entity types (`02-gameplay-entity`), 20 creature/editor types (`03-creature`), and 21 empire/space types (`05-empire-space`).
- **De-duplicated estimate:** no single unique semantic-type total is defensible because workers mix classes, structures, interfaces, records, current-source values, and overlapping families. The 1,250 family-node census is the broadest exact family population, not a type count.

### Top findings

1. The strongest gameplay spine is `cCellGame/sCellGame` -> `cObjectPool<cCellObjectData>` -> `cCellObjectData`, with world/query references, avatar identity, timing, and serializable state. **SUPPORTED** (`01-simulator-core`, `02-gameplay-entity`).
2. `cCreatureBase`, `cCreatureAnimal`, `cCreatureGameData`, `EditorModel`, and editor animation types form a substantial social/editor family, but not a complete RTTI hierarchy. **SUPPORTED** (`03-creature`, `14-class-families`).
3. The world/space spine is `cStarRecord` -> `cPlanetRecord` -> live `cStar`/`cSolarSystem`/`cPlanet`/`cPlanetModel`, with separate terrain, economy, mission, and diplomacy families. **SUPPORTED** (`04-world-planet`, `05-empire-space`).
4. `ResourceKey`, `Property`/`PropertyList`, `ISimulatorSerializable`, `cGameData`, `SpacePlayerData`, `cEmpire`, and Cell reference records are cross-domain identity and persistence seams. **SUPPORTED** (`08-persistence-serialization`, `09-asset-content`, `15-reconstruction-relevance`).

**Citations:** `00-corpus-inventory.md:61-81`; `01-simulator-core.md:37-57`; `02-gameplay-entity.md:21-56`; `03-creature.md:22-47`; `04-world-planet.md:11-22`; `05-empire-space.md:18-45`; `08-persistence-serialization.md:66-145`; `14-class-families.md:7-16`; `15-reconstruction-relevance.md:3-7`.

## 2. Structures

### Counts

- **Exact:** 2,035 current Ghidra structures and 25,546 structure fields (`00-corpus-inventory`, `12-field-archaeology`).
- **Exact separate population:** 1,895 raw SDK XML structures and 22,056 raw XML members (`00-corpus-inventory`).
- **De-duplicated estimate:** 2,035 is the defensible current Ghidra structure population. A unique cross-source structure total is **UNKNOWN** because SDK import, Ghidra manager state, and KG projections are separate populations.

### Top findings

- `cCellGame` is 20,964 bytes; `cCellObjectData` is 920 bytes; the main pool descriptor is 28 bytes; the observed main pool capacity is 4,096. **SUPPORTED** (`01-simulator-core`, `02-gameplay-entity`, `10-managers-registries`).
- `cCreatureBase` is 4,032 bytes, `cCreatureAnimal` 5,792 bytes, `cTribe` 6,624 bytes, and `cEditor` 1,536 bytes. These are high-value layouts, not complete runtime models. **SUPPORTED** (`03-creature`, `05-empire-space`).
- `cStarManager` is 556 bytes, `cPlanetRecord` 432 bytes, `cStarRecord` 176 bytes, and `cPlanetModel` 92 bytes. **SUPPORTED** (`04-world-planet`, `05-empire-space`).
- `ClassSerializer` is declared at `0xA14` with a 128-entry attribute-pointer table; `cSavedGameHeader` is `0x68`; `Property` has an unresolved SDK/XML layout conflict. **SUPPORTED** (`08-persistence-serialization`).

**Citations:** `00-corpus-inventory.md:163-193`; `12-field-archaeology.md:25-39`; `01-simulator-core.md:146-166`; `03-creature.md:22-47`; `04-world-planet.md:24-124`; `08-persistence-serialization.md:99-161`.

## 3. Vtables

### Counts

- **Exact:** 3,081 candidate bases: 369 high-confidence, 871 medium-confidence, and 1,841 low-confidence; 20 labels; 16,107 shared-slot clusters; 12 explicit chains; 11,898 vtable-reference edges (`00-corpus-inventory`, `11-vtable-archaeology`, `16-misc-unknown`).
- **Exact selected populations:** 33 high-value vtable records in `11-vtable-archaeology`; 33 class-specific binary virtual-slot matches in `14-class-families`. These units are not assumed to be the same set.
- **De-duplicated estimate:** no defensible unique class count exists. A candidate, label, cluster, chain, and class-family match are not interchangeable.

### Top findings

- `App::cCellModeStrategy` at `0x01485550` is a 27-slot candidate with ten named lifecycle/input/update methods. It is the strongest mode-family identity, not a complete `IGameMode` ABI proof. **SUPPORTED** (`02-gameplay-entity`, `11-vtable-archaeology`).
- `Editors::cEditor` at `0x013f57f8` is a 29-slot candidate with ten named editor methods and five unresolved slots; SDK `IGameMode` is 16 slots. **SUPPORTED** (`06-editor-ui`, `11-vtable-archaeology`).
- `PropertyList` and `DirectPropertyList` are 19-slot candidates; `UTFWin::IWindow` exposes 71 slots; candidate families contain cross-namespace contamination. **SUPPORTED** (`06-editor-ui`, `11-vtable-archaeology`).
- Unattributed candidate `0x013f1a30` has 40 slots, 38 implemented and 2 unknown slots, 17 method-address entries, and 71 unique consumer VAs. Its identity is **UNKNOWN** (`11-vtable-archaeology`, `16-misc-unknown`).

**Citations:** `00-corpus-inventory.md:244-264`; `11-vtable-archaeology.md:7-19`; `11-vtable-archaeology.md:25-61`; `16-misc-unknown.md:98-109`.

## 4. Inheritance chains

### Counts

- **Exact:** 12 explicit scanner prefix-chain records; two UTFWin base candidates; six derived candidates per base; shared prefix length 21 slots (`11-vtable-archaeology`, `14-class-families`).
- **De-duplicated estimate:** a complete C++ RTTI hierarchy is **UNKNOWN**. The 12 scanner chains, SDK field-prefix relations, and embedded vtable relations are separate evidence populations.

### Top findings

- The 12 explicit chains are UTFWin 21-slot-prefix relationships. Bases `0x013fa974` and `0x01419794` are both reported; the worker does not choose a canonical base. **SUPPORTED** (`11-vtable-archaeology`).
- `cCreatureBase` -> `cCreatureAnimal` is supported by a repeated exported field prefix and size extension, but remains static/layout evidence rather than RTTI-backed C++ inheritance. **SUPPORTED** (`03-creature`).
- Embedded/base-prefix relations are recovered for `cPlanet`, `cStar`, `cSolarSystem`, `cPlanetModel`, `cTerrainSphere`, `cEditor`, and `SpacePlayerData`/`cEmpire` surfaces; raw-pointer ownership remains separate. **SUPPORTED** (`04-world-planet`, `06-editor-ui`).
- `cCellGame` -> `cCellGFX`/`cCellUI` is coordination through Cell mode state and is not established as inheritance. **UNKNOWN** (`02-gameplay-entity`).

**Citations:** `11-vtable-archaeology.md:13-19`; `11-vtable-archaeology.md:115-124`; `03-creature.md:89-108`; `04-world-planet.md:191-203`; `02-gameplay-entity.md:118-126`.

## 5. Shared structures

### Counts

- **Exact:** 13 exported `cCellDataReference` variants; 40 `eastl::map` typedefs; 60 ordinary `eastl::vector` typedefs; 10 `vector_map` typedefs; 5 inventory/tool/cargo structures sharing a base prefix; 5 UTFWin/UI structures sharing the `Window` layout (`12-field-archaeology`).
- **De-duplicated estimate:** no single total for unique shared-layout types is defensible because the populations overlap by type, container role, and export view.

### Top findings

- `ResourceKey` is the broadest semantic identity primitive: instance/type/group crosses cell content, assets, space, editor, rendering, and persistence boundaries. **SUPPORTED** (`09-asset-content`, `12-field-archaeology`).
- `cCellDataReference` shares a 16-byte ID/serializer/resource/counter layout across 13 exported reference structures; `0x00e82340` versus `0x00e82420` remains unresolved. **SUPPORTED** (`09-asset-content`, `12-field-archaeology`).
- EASTL map/vector layouts are cross-domain container substrates; map `+0x04` terminology and vector pointer aliases remain structural rather than host-container equivalences. **SUPPORTED** (`12-field-archaeology`).
- Space inventory/tool/cargo and UTFWin window layouts are high-value compatibility boundaries, not a universal component architecture. **SUPPORTED** (`12-field-archaeology`).

**Citations:** `12-field-archaeology.md:43-70`; `09-asset-content.md:48-65`; `15-reconstruction-relevance.md:27-36`.

## 6. Highest fan-out and reuse

### Counts

| Surface | Exact metric | Unit | Evidence |
|---|---:|---|---|
| `cGameInputManager::Get` | 614 total / 80 gameplay | distinct callers | SUPPORTED |
| `Editors::cEditor` | 494 distinct callees; maximum fan-out 111 | functions per associated function | SUPPORTED |
| `cSpaceTrading` | 168 callers; maximum fan-in 156 | distinct callers / per-function callers | SUPPORTED |
| `cRelationshipManager` | 78 callers; maximum fan-in 53 | distinct callers / per-function callers | SUPPORTED |
| `cCreatureBase` | 83 callers | distinct callers | SUPPORTED |
| `map_int_whatever_find` | 265 callers | distinct callers | SUPPORTED |
| Noun bridge projection | 254 callers | distinct callers in cited projection | SUPPORTED |
| `MISC-AT-001` wrapper forest | 9,428 = 6,527 + 2,901 | arithmetic sum of root caller counts | SUPPORTED |

- **De-duplicated estimate:** 9,428 is not a unique caller union; caller overlap is not computed. No global unique fan-out total is defensible.

### Top findings

- `cGameInputManager` is the broadest direct gameplay dependency named in the assessment: 614 total and 80 gameplay callers, with a 27-slot input/mode surface. **SUPPORTED** (`06-editor-ui`, `15-reconstruction-relevance`).
- `cEditor` is the largest editor command/reuse surface: 21 associated functions, 494 distinct callees, maximum fan-out 111, and sum fan-out 701. These are static graph metrics, not runtime behavior. **SUPPORTED** (`15-reconstruction-relevance`).
- `cSpaceTrading` and `cRelationshipManager` are high fan-in semantic owners; `cCreatureBase` is a broad creature reuse root. **SUPPORTED** (`15-reconstruction-relevance`).
- Generic wrapper roots have the largest raw reach but are infrastructure chokepoints, not evidence for gameplay type identity. **SUPPORTED** (`16-misc-unknown`).

**Citations:** `12-field-archaeology.md:43-59`; `15-reconstruction-relevance.md:148-161`; `16-misc-unknown.md:55-75`.

## 7. Types unlocking unknown functions

### Counts

- **Exact:** unresolved roots `00b3d300`, `00b3d2a0`, and `00b5b800` reach 1,097/252, 314/101, and 459/80 total/gameplay callers. **SUPPORTED**.
- **Exact:** unknown-vtable implementation corpus is 4,384 canonical rows; the generic wrapper forest is 9,428 arithmetic caller reach; `cGameInputManager` is 614/80; the editor command surface is 31/16 total/gameplay callers; the property data spine is 841/82. **SUPPORTED**.
- **De-duplicated estimate:** no unique unknown-function unlock total is defensible because these are dependency reach, vtable rows, property methods, and wrapper caller counts.

### Top findings

- The three unresolved service roots are the highest-leverage shared-state boundaries; their fan-in does not establish concrete service identity. **SUPPORTED** (`15-reconstruction-relevance`, `16-misc-unknown`).
- `cGameInputManager` and the editor command surface are the strongest known type/interface unlockers. **SUPPORTED** (`15-reconstruction-relevance`).
- The 4,384-row unknown-vtable implementation corpus is a high-leverage dispatch population, but owner mapping and slot meaning must precede body reconstruction. **SUPPORTED** (`15-reconstruction-relevance`, `16-misc-unknown`).
- The generic wrapper forest unlocks allocator/reference behavior, not gameplay types. **SUPPORTED** (`15-reconstruction-relevance`, `16-misc-unknown`).

**Citations:** `15-reconstruction-relevance.md:148-161`; `16-misc-unknown.md:68-75`; `16-misc-unknown.md:143-154`.

## 8. Unresolved types

### Counts

- **Exact populations:** 39,716 triage `UNKNOWN` category rows; 44,978 `unknown-fun-mass` rows; 4,384 `unknown-vtable-impl` rows; 48,296 debtmap `UNKNOWN` rows; 35,771 genuinely unknown ownership rows (`00-corpus-inventory`, `16-misc-unknown`).
- **Exact candidate counts:** 2 four-byte forwarding roots in `MISC-AT-001`; 2 records described as 27-field and 24-field in `MISC-REC-001` (**INFERRED**).
- **De-duplicated estimate:** no combined unknown-function total is defensible. The populations have different denominators and semantics.

### Top findings

- `00b3d300`, `00b3d2a0`, and `00b5b800` remain type-open shared service roots. **UNKNOWN** (`10-managers-registries`, `15-reconstruction-relevance`).
- `FUN_00b21340` remains a map/list callback bridge with a competing historical message-handler label; map/materialization mechanics are stronger than the message label. **SUPPORTED** (`07-event-message`, `16-misc-unknown`).
- `MISC-AT-001`, `MISC-BUF-001`, `MISC-STR-001`, `MISC-VT-001`, and `MISC-REC-001` remain candidates, not owned types. **UNKNOWN** (`16-misc-unknown`).
- `cCellDataReference` address aliasing, generic `cObjectPool_` identity, `cSpeciesProfile`/`cCreatureGameData` size conflicts, Terrain 40-slot versus 75-slot interface evidence, and the contested communication wrapper are explicit gates. **UNKNOWN** (`02-gameplay-entity`, `04-world-planet`, `05-empire-space`).
- Complete App message IDs, 0x18-byte queue records, UTFWin dispatch order, pdtk grammar, event-to-pose integration, and most original serialization wire formats remain **UNKNOWN** (`07-event-message`, `08-persistence-serialization`).

**Citations:** `16-misc-unknown.md:36-64`; `16-misc-unknown.md:66-124`; `07-event-message.md:671-697`; `08-persistence-serialization.md:199-228`.

## 9. Infrastructure-only types

Infrastructure-only means the implementation is replaceable while meaningful identity, ordering, error, data, and event contracts remain semantic. It does not mean the type has no gameplay relevance.

### Counts

- **Exact:** UTFWin has 1,093 attributed functions; the cited UTFWin association statement uses 247 of 306 vtable associations. **SUPPORTED**.
- **Exact:** `DatabasePackedFile` has 20 associated functions; `cResourceManager` has 21 associated functions and 22 vtable-family functions; `PFRecordRead` has 7 associated functions. **SUPPORTED**.
- **Exact:** generic wrapper forest is 9,428 arithmetic caller reach across the two named roots. **SUPPORTED**.
- **De-duplicated estimate:** no single infrastructure-type total is defensible.

### Top findings

- UTFWin is the largest replaceable UI infrastructure boundary: 1,093 functions, 71-slot `IWindow`, 7-slot `IWinProc`, layouts/drawables/windows/procs, and pdtk command construction. **SUPPORTED** (`06-editor-ui`).
- Resource manager, packed-file/index/cache/allocator internals, DBPF/QFS, RenderWare/D3D, and DSOUND backends are replaceable storage/render/audio infrastructure; resource identity, record bounds, errors, cache/invalidation, and normalized event contracts remain semantic. **SUPPORTED** (`09-asset-content`, `10-managers-registries`, `15-reconstruction-relevance`).
- Generic forwarding roots are allocator/reference chokepoints with 6,527 and 2,901 callers; do not rename them as allocator classes without ABI evidence. **SUPPORTED** (`16-misc-unknown`).
- Property-manager internals and backend-specific UI/renderer implementations are replaceable, while typed property and command/window semantics are retained. **SUPPORTED** (`06-editor-ui`, `08-persistence-serialization`, `15-reconstruction-relevance`).

**Citations:** `06-editor-ui.md:20-29`; `06-editor-ui.md:69-89`; `09-asset-content.md:31-46`; `10-managers-registries.md:155-166`; `15-reconstruction-relevance.md:129-135`.

## 10. Recommended OpenSpore semantic interfaces

The worker explicitly recommends **12** interface bundles in **5** ordered anchor groups. These are clean-room semantic boundaries, not claims that the original ABIs are recovered.

### Recommended interface bundles

1. **`ICellGameState + IEntityPool + ICameraRayProvider`** — Cell state, stable pool handles, player identity, world/plane state, movement targets, ordered interaction events. **SUPPORTED**.
2. **`IAppHost + IGameModeRegistry`** — application services, mode registration, activation order, frame ticking, shutdown. **SUPPORTED**.
3. **`IInputRouter + cGameInputManager field contract`** — normalized input, current/previous mode, regions, callbacks, and selected layout contract without reproducing the 27-slot ABI. **SUPPORTED**.
4. **`IGameServices`** — injected input, camera/view, behavior, mode, persistence, and frame-clock operations. **SUPPORTED**.
5. **`IContentStore + IRecordCodec`** — ResourceKey identity, record bytes, bounds, missing/error behavior, provider-independent access. **SUPPORTED**.
6. **`IPropertyStore + IPropertyCodec`** — typed keys, parent fallback, enumeration, and versioned read/write behavior. **SUPPORTED**.
7. **`ISerializableGameObject`** — read/write, noun identity, refcount, and serialization hooks without original multiple-inheritance layout. **SUPPORTED**.
8. **`IEventRouter + typed stage events`** — ordered App/UTFWin/mode/animation/feedback/communication routing without one universal event ABI. **SUPPORTED**.
9. **`IAnimationWorld + IAnimatedCreature`** — load/update/destroy, animation state, pose, model/effect world binding, and editor bridge. **SUPPORTED**.
10. **`IPlayerIdentity + IEmpireRegistry`** — `SpacePlayerData`, current empire cache, political ID, and star-manager registry. **SUPPORTED**.
11. **`IRelationshipStore + ITradeService + IMissionService`** — war/alliance/peace transitions, trade inventory, mission state, rewards, and communication-facing space services. **SUPPORTED**.
12. **`IUiWindow + IUiCommandRouter`** — command/window semantics, hierarchy, hit-testing, layout, focus, and event identity while replacing UTFWin and renderer backends. **SUPPORTED**.

### Recommended anchor order

1. **Identity and persistence:** `ResourceKey`, `cGameData`, `SpacePlayerData`, `cEmpire`, `Property`/`PropertyList`, `ISimulatorSerializable`. **SUPPORTED**.
2. **Host and services:** `IAppHost`/`IGameModeRegistry`, `IInputRouter`, `IGameServices`, time/behavior/persistence managers. **SUPPORTED**.
3. **Cell spine:** `cCellGame`, `cCellObjectData`, `cObjectPool_`, world/advect records, `cCellSerializableData`. **SUPPORTED**.
4. **Gameplay owners:** creature, tribe, city, planet, star, trading, relationship, and mission owners. **SUPPORTED**.
5. **Editor/content boundaries:** `cEditor`, animation, event routing, content store, and property store. **SUPPORTED**.

The safe disposition is data-first and interface-first: freeze identity, records, shared service contracts, Cell pool/query/state, and event-family boundaries; replace backend infrastructure only after semantic contracts and compatibility gates are explicit. Do not claim runtime fidelity, complete class hierarchy, or original wire compatibility from this corpus. **UNKNOWN** remains the correct level for original runtime order, message semantics, and save/event ABI.

**Citations:** `15-reconstruction-relevance.md:163-208`; `10-managers-registries.md:155-166`; `07-event-message.md:634-657`; `08-persistence-serialization.md:147-181`.

## Cross-report findings

### Highest-confidence static facts

- The CellGame/CellObjectData/pool and world/query/identity offsets are a high-value compatibility spine. **SUPPORTED** (`01-simulator-core`, `02-gameplay-entity`, `12-field-archaeology`).
- ResourceKey, PropertyList, serializable records, and simulator serializable interfaces are cross-domain identity and persistence seams. **SUPPORTED** (`08-persistence-serialization`, `09-asset-content`, `15-reconstruction-relevance`).
- Editor/UTFWin/input/message surfaces are broad static dependency roots, but their original ABI is replaceable. **SUPPORTED** (`06-editor-ui`, `07-event-message`, `10-managers-registries`, `15-reconstruction-relevance`).

### Largest unknowns

- Concrete owner and type identity behind shared service roots, generic forwarding roots, and unknown-vtable implementations. **UNKNOWN** (`10-managers-registries`, `11-vtable-archaeology`, `16-misc-unknown`).
- Runtime initialization/update/teardown ordering and original event/message semantics. **UNKNOWN** (`07-event-message`, `13-lifecycle`, `14-class-families`).
- Original `.prop`/`.spo`/serializer wire formats, message queue records, space event records, pdtk grammar, and Space-stage runtime transitions. **UNKNOWN** (`04-world-planet`, `07-event-message`, `08-persistence-serialization`, `16-misc-unknown`).

## Integrity

- Only `knowledgegraph/research/types/21-report-brief.json` and `knowledgegraph/research/types/21-report-brief.md` are written.
- No worker, source, SPORE, Ghidra, knowledge-graph database, or history file is modified.
- No timestamps, generated-at fields, random values, proprietary source, or proprietary asset payload is included.
- JSON arrays and report references are stable by artifact ID, report item, metric population, and finding ID.
