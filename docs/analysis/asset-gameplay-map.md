# Asset–Gameplay Map

## Scope and evidence policy

This document maps the important Spore asset/data families to their lookup, ownership, runtime, gameplay, presentation, event, and serialization boundaries. `knowledgegraph/research/gameplay-data-model.json` is the canonical truth. Data-model artifacts 01–08, 11, 12, and 14 provide family detail and OpenSpore correspondence; audit 20 controls graph direction, unresolved claims, centrality, and flow coverage (`knowledgegraph/research/gameplay-data-model.json:4357-4382`; `knowledgegraph/research/data-model/20-graph-audit.json:1121-1180`).

The scope is staged: the 18 worker inputs are DM01–DM18, while the canonical synthesis has 21 input artifacts DM01–DM21. The source graph has 10 source-graph flows, while the canonical normalized graph has one qualified derived flow, `F-ASSET-LOOKUP-RUNTIME-GAMEPLAY-EVENT`, in addition to those 10; the source graph has 48 source edges, while the canonical graph has 49 normalized edges because the disclosed `N-PLANET-SURFACE` supporting node and `E-052` edge are added. These are intentional staged scope and normalization differences, not missing semantics or runtime coverage (`knowledgegraph/research/gameplay-data-model.json:3341-3355,446-449,1403-1440,2253-2270,12066-12070`; `knowledgegraph/research/data-model/19-evidence-audit.json:3-35`; `knowledgegraph/research/data-model/21-mission-coverage-audit.json:3-24`; `knowledgegraph/research/data-model/23-final-consistency-review.json:14-21,207-216`; `knowledgegraph/research/data-model/24-final-scope-audit.json:291-313`).

The evidence has the following hard limits:

- **No original runtime validation is established.** Static layouts, SDK names, decompilation, and current OpenSpore behavior do not prove undocumented runtime order or ownership (`knowledgegraph/research/gameplay-data-model.json:4544-4551,4635-4636`; `knowledgegraph/research/data-model/20-graph-audit.json:1231-1234`).
- **Logical names are projections unless marked literal.** `WorldData`, `PlanetData`, `EditorData`, `ProgressionData`, and `EconomyData` are analytical composites, not recovered original classes (`knowledgegraph/research/data-model/05-world-planet-data.json:24-53`; `knowledgegraph/research/data-model/07-editor-data.json:5-18`; `knowledgegraph/research/data-model/08-progression-economy.json:8-15`).
- **Identity is not host-pointer identity.** DBPF records use `(type, group, instance)` semantically, while the 12-byte `ResourceKey` memory layout is `instanceID, typeID, groupID`; conversions must be explicit (`knowledgegraph/research/data-model/01-dbpf-resource-formats.json:153-175,188-194,224-233`; `src/assets/Dbpf.hpp:16-26`; `src/compat/ResourceProvider.hpp:24-53`).
- **The research dossier is local-worktree provenance.** DM01–DM18 and TY08 are untracked inputs; no clean-checkout reproducibility is claimed. Current source, tests, and fixtures establish current OpenSpore behavior only, not original runtime behavior (`knowledgegraph/research/data-model/19-evidence-audit.json:23-35,47-48,78-84`; `knowledgegraph/research/data-model/21-mission-coverage-audit.json:335-344`; `knowledgegraph/research/data-model/24-final-scope-audit.json:291-303,480-485`).
- **Inherited provenance remains qualified.** The audit retains two missing paths, five stale ranges, and weak semantic or grouped anchors; no replacement path, range, or anchor was invented. Citations in this report are current local-file checks, not repaired historical provenance (`knowledgegraph/research/data-model/19-evidence-audit.json:37-49,71-84`; `knowledgegraph/research/data-model/24-final-scope-audit.json:307-320,694-705`; `knowledgegraph/research/gameplay-data-model.json:12072-12078`).
- **Identifiers are view-local.** Intentional cross-view reuse is reference linkage, not duplicate identity; strict global uniqueness is not a valid test. Validation records 169 globally reused values and zero within-array duplicates (`knowledgegraph/research/gameplay-data-model.json:4372-4374`; `knowledgegraph/research/data-model/22-final-determinism-validation.json:13-30,281-284`).
- **C002 and C014 remain open inherited contradictions.** Property memory layout (`C002`) and `cCreatureGameData` field typing (`C014`) are unresolved, so related family statements remain qualified (`knowledgegraph/research/data-model/19-evidence-audit.json:56-62`; `knowledgegraph/research/data-model/23-final-consistency-review.json:698-706`; `knowledgegraph/research/data-model/24-final-scope-audit.json:355-361`).

Evidence labels used below:

- **VERIFIED / OBSERVED_CURRENT** — direct current implementation, local-worktree test, frozen export, pinned query, or deterministic artifact comparison for the stated bounded claim. This does not imply original runtime equivalence.
- **SUPPORTED / CONFIRMED** — bounded static agreement across layout, call shape, SDK, or local-worktree dossier. It does not imply original runtime equivalence.
- **INFERRED** — narrow interpretation; ordering or ownership remains unproved.
- **UNKNOWN** — not established.

## Executive map

| Family | Primary identity | Canonical owner | Runtime target | Current OpenSpore coverage |
|---|---|---|---|---|
| DBPF/resource keys | type/group/instance | package database + resource manager | bounded bytes, factory/resource object | One-package provider; manager orchestration missing |
| GMDL/RW4/model | DBPF triple; internal group/instance texture refs | resource/model/graphics managers | RenderWare-style model, mesh, material, texture state | GMDL v8 prefix and RW4 directory represented; execution partial |
| Cell records/config | DBPF triple; typed instance refs inside payloads | `cCellDataReference_`, `cCellGame`, `cCellGFX` | Cell templates, pooled Cell state, GFX/preload state | Record decoders and selected projections represented |
| World objects | `0x0F43029A` DBPF triple or planet-object runtime identity | model-content subsystem or `cPlanetRecord` | model-part metadata or positioned planet object | Structural WorldObject decoder only; not placement |
| Creatures/entities | authored part/resource refs; definition/political IDs | editor/model systems, noun/object registry, creature runtime | creature block/base/animal and gameplay entity state | Cell pool projection; creature/editor systems missing |
| World/planet | Cell world refs; `PlanetID`; generated terrain `ResourceKey` | `cCellGame`; galaxy/planet/terrain managers | Cell world data; generated record, live planet, terrain sphere | Cell decode/lookup only; no planet/terrain runtime |
| Empire/Space | political ID, star/planet IDs, item/model `ResourceKey` | `cStarManager`, empire/relationship/trade/mission services, Space session | Space and colony/empire/inventory/relationship state | No general Space/economy implementation |
| Editor | editor ID, creation/model `ResourceKey`, part hierarchy indices | `cEditor` and authoring templates | transient editor shell plus derived skin/animation state | Missing |
| Progression/economy | per-domain IDs, ResourceKeys, counters | several mode/domain owners | live progression, inventory, mission, trade, scenario state | Cell loot/growMeter only; not global progression/economy |
| Textures/materials | material IDs, texture group/instance, RW4 section codes | material/texture managers and Cell/editor presentation | compiled material/raster/slot state and host texture | DXT5 decode + single-level Vulkan; original semantics missing |

This is a semantic family map, not a claim that one universal original object or registry owns every row.

## Central lookup and registry model

### Identity domains

1. **Package-record identity** is the complete DBPF triple `(type, group, instance)`. Group does not imply a semantic stage/category unless a source artifact establishes that mapping; type and group labels remain secondary to raw IDs (`knowledgegraph/research/data-model/01-dbpf-resource-formats.json:224-233`; `knowledgegraph/research/gameplay-data-model.json:4638-4718`).
2. **Runtime `ResourceKey` identity** is the same three IDs in a different memory order. Original lookup and object identity use the complete key; a GMDL texture-set entry is the notable exception because it retains only group/instance in the current bounded decoder (`knowledgegraph/research/data-model/02-gmdl-rw4-object-metadata.json:324-347`; `src/assets/Gmdl.hpp:51-56`; `src/assets/Gmdl.cpp:210-225`).
3. **Cell typed references** are not complete DBPF triples. `cCellDataReference_` stores an instance ID, a `CellSerializer*`, a lazy `cCellResource*`, and a counter; the serializer supplies type context (`knowledgegraph/research/data-model/03-gameplay-configuration.json:260-261`; `knowledgegraph/research/data-model/12-asset-registry.json:679-695`).
4. **Runtime object identity** may instead be a noun/definition ID, political ID, `PlanetID`, pool index, editor ID, mission ID, or property ID. These are not interchangeable with DBPF identity.
5. **Presentation identity** is a material ID, texture key, RW4 section type code, render-world handle, GFX index, or model key. Presentation identity can be selected by gameplay data but does not own gameplay state.

### Registry and lookup inventory

| Registry/lookup | Key | Owner and consumers | Supported behavior | Missing or bounded behavior | Evidence |
|---|---|---|---|---|---|
| `cResourceManager` | `ResourceKey`, factory/resource type, name/extension | Databases, factories, model/Cell/editor/Space consumers | manager initialization, database/factory registration surfaces, find/load/cache surfaces | package priority, exact traversal, eviction, async and release order | `knowledgegraph/research/data-model/12-asset-registry.json:502-519,1361-1412,1474-1522` |
| `DatabasePackedFile` / `PFIndexModifiable` | `ResourceKey`/index row | package database and record readers | identity, index extent, integrity/read surfaces | original write/compaction and lookup precedence | `knowledgegraph/research/data-model/12-asset-registry.json:522-595,1688-1703` |
| `DatabaseDirectoryFiles` | name/extension/default group + `ResourceKey` | resource manager and non-packed records | extension map, record-list map, default group, name converter surfaces | name derivation and directory lookup precedence | `knowledgegraph/research/data-model/12-asset-registry.json:547-562,1710-1777` |
| `cCellDataReference_` | instance ID + serializer context | Cell content/game/GFX consumers | lazy cached resource and reference counter | package selection, exact invalidation/release order | `knowledgegraph/research/data-model/12-asset-registry.json:489-500,679-695,1704-1718` |
| Cell object pool | pool/self index | `cCellGame` and Cell rules/presentation | 4096 slots, 920-byte elements, free-list allocation | complete original side effects and non-main pools | `knowledgegraph/research/data-model/04-creature-data.json:374-426`; `src/sim/CellPool.hpp:66-162` |
| Cell query pools | pool index, position, size | steering/combat consumers | linked query records and bounded near predicate | original insertion/removal/iteration body and order | `knowledgegraph/research/data-model/04-creature-data.json:492-507`; `src/sim/CellQuery.hpp:27-81` |
| `cGameNounManager` / normalized `N-OBJECT-REGISTRY` | definition/noun/owner/political IDs | creatures, buildings, ships, editor/world objects | noun materialization surface | no universal exact original hierarchy, restoration, or destruction cascade | `knowledgegraph/research/gameplay-data-model.json:3522-3568,2317-2434`; `knowledgegraph/research/data-model/20-graph-audit.json:1139-1148` |
| `cStarManager` + empire registry | star/planet/political/owner IDs; ResourceKeys | Space, empire, colony, trade, relationship, mission | star/planet ownership and ID-keyed empire lookup surfaces | generation, manager registry, transaction order | `knowledgegraph/research/data-model/06-empire-space-data.json:175-219,394-438,529-583` |
| `PropertyList` / `ClassSerializer` | property ID, class/object ID | config, editor, missions, items, save service | property lookup/mutation and named persistence interfaces | parent encoding, pointer remapping, framing, migration | `knowledgegraph/research/gameplay-data-model.json:3588-3601`; `knowledgegraph/research/data-model/08-progression-economy.json:609-633` |
| `MaterialShader` / texture manager | material ID; texture ResourceKey | graphics, materials, Cell/editor presentation | shader ID cache and raster/material binding surfaces | complete shader families, atlas, external references, pixel order | `knowledgegraph/research/data-model/11-textures-materials-gameplay.json:129-149,169-170,203-216` |

### Central registry findings

- The normalized graph's highest-degree node is `N-PRESENTATION-DATA`, not gameplay state. This is useful for finding renderer crossings but does **not** make presentation the owner of health, collision, progression, or save data (`knowledgegraph/research/gameplay-data-model.json:4638-4670`; `knowledgegraph/research/data-model/20-graph-audit.json:408-492`).
- `N-ASSET-REGISTRY`, `N-CELL-RUNTIME-STATE`, `N-SPACE-DATA`, and normalized `N-OBJECT-REGISTRY` are the practical cross-domain hubs. `N-OBJECT-REGISTRY` is explicitly a semantic adapter boundary, not a recovered universal original ABI (`knowledgegraph/research/gameplay-data-model.json:18-19,4638-4718`).
- The remediated normalized directions are `N-CELL-WORLD-DATA → N-CELL-CONTENT` (`E-007`), `N-PLANET-DATA → N-PLANET-SURFACE` (`E-021`), `N-CITY-DATA → N-PRESENTATION-DATA` (`E-027`), `N-CONFIGURATION-DATA → N-PROPERTY-LIST` (`E-030`), and `N-SAVE-DATA → N-OBJECT-REGISTRY` (`E-047`). Model-reference resolution and derived-skin production remain separate relations; these normalized directions are not universal original runtime behavior (`knowledgegraph/research/gameplay-data-model.json:621-636,746-760,869-884,977-996,1037-1057,1346-1361`; `knowledgegraph/research/data-model/20-graph-audit.json:256-320`; `knowledgegraph/research/data-model/23-final-consistency-review.json:24-39`).
- The correct normalized separation is **asset/content → lookup/registry → typed runtime reference → live gameplay state → bounded event consequence**, with presentation as a projection and persistence as a separate owner.
- The end-to-end asset→lookup→runtime→gameplay→event path is structurally present but not runtime validated; gameplay-to-event transport remains `U-003-TRANSPORT` (`knowledgegraph/research/gameplay-data-model.json:1402-1471,4720-4789`; `knowledgegraph/research/data-model/20-graph-audit.json:1066-1118`).

## Cross-family relationship chains

### Asset → lookup → runtime → gameplay → event

```text
DBPF row (type, group, instance)
  -> package database / cResourceManager surfaces
  -> decompressed bounded bytes
  -> type-specific factory/parser or lazy cCellDataReference_
  -> typed resource/model/content representation
  -> mode/domain owner materializes or selects a live object
  -> gameplay state mutation
  -> subsystem-specific event/message consequence
```

Supported anchors include `cResourceManager::Initialize` at `0x008DE530`, manager find/load surfaces at `0x008DF9B0` and `0x008DF0B0`, `cCellDataReference_::Create` at `0x00E82420`, `GetModelKeyForCellResource` at `0x00E65640`, Cell preload at `0x00E666F0`, and `CreateCellObject` at `0x00E74A20` (`knowledgegraph/research/data-model/12-asset-registry.json:1389-1405,1524-1572`).

The last edge is not a proven universal event ABI. Damage, eat, death, evolution, diplomacy, and mode changes have domain-specific records, but transport payloads, timing, priority, and event-to-message mapping remain unresolved (`knowledgegraph/research/data-model/04-creature-data.json:803-814`; `knowledgegraph/research/gameplay-data-model.json:2302-2419`).

### Asset → presentation chain

```text
ResourceKey / model selector
  -> GMDL or RW4 record
  -> model geometry/material/texture references
  -> original RenderWare-style model/mesh/material/raster state
  -> presentation world and draw
```

Original model selection has bounded RW4→GMDL fallback evidence at `0x0073D160`; model construction is at `0x006F1C40`; Cell model derivation is at `0x00E65640`; material lookup and draw setup are at `0x011FA030` and `0x011F9710` (`knowledgegraph/research/data-model/02-gmdl-rw4-object-metadata.json:1122-1143,1257-1301,1347-1389`). This chain does not establish all material/animation semantics.

### Cell content → runtime → event consequence

```text
cCellGlobalsResource
  -> cCellWorldResource
  -> cCellPopulateResource
  -> cCellCellResource
  -> cCellStructureResource / random creature / loot / look / effects
  -> 4096-cell pool and query state
  -> movement/combat/eat/animation/effect/health projections
```

The chain is structurally supported, but exact world selection, procedural x/y placement, record choice, active-update order, and event transport remain unresolved (`knowledgegraph/research/data-model/05-world-planet-data.json:569-598,674-692`; `knowledgegraph/research/gameplay-data-model.json:1531-1596`).

### Space generation → gameplay → communication

```text
cStarManager
  -> cStarRecord
  -> cPlanetRecord
  -> cEmpire / colony / commodity state
  -> relationship, mission, inventory and trade mutations
  -> cCommEvent or other subsystem-specific event
```

Manager and field relationships are supported, but generation formulas and event/payout order are not (`knowledgegraph/research/data-model/06-empire-space-data.json:394-438,529-616,672-744`; `knowledgegraph/research/gameplay-data-model.json:1983-2045`).

The normalized graph now separates generated `N-PLANET-DATA` from live surface/terrain state and presentation: `E-021` is `N-PLANET-DATA → N-PLANET-SURFACE`, and `E-052` is `N-PLANET-SURFACE → N-PRESENTATION-DATA`. `F-PLANET-TO-SURFACE` is `partial_direct_surface_edge_added_but_runtime_transition_unresolved`; the direct structural edge gap is closed, while generation, transition, terrain codec, and execution remain unresolved (`knowledgegraph/research/gameplay-data-model.json:869-884,1385-1400,1874-1924`; `knowledgegraph/research/data-model/23-final-consistency-review.json:77-86,218-228`; `knowledgegraph/research/data-model/24-final-scope-audit.json:340-345`).

### Editor authoring → derived presentation

```text
cCreatureDataResource / EditorModel / rigblocks
  -> cEditor authored core
  -> transient history, tools, pose and animation controllers
  -> cEditorSkin / cEditorSkinMesh
  -> presentation model/texture state
  -> EditorModel::Save or cCreatureDataResource::Write boundary
```

The static sequence is supported, but the exact save/apply validation and round trip are not (`knowledgegraph/research/data-model/07-editor-data.json:588-611,655-722`).

## Family dossiers

The dossiers below are evidence-bounded family summaries that separate identity, ownership, runtime relationships, serialization, gameplay significance, and current OpenSpore fidelity; confidence and unresolved behavior remain qualified by their labels and citations (`knowledgegraph/research/gameplay-data-model.json:4357-4382`; `knowledgegraph/research/data-model/20-graph-audit.json:1121-1180`).

## 1. DBPF, QFS, and resource keys

- **Identity / type / group / instance:** DBPF identity is exactly `(type, group, instance)`; each row also carries payload offset, stored size, memory size, compression, and saved marker. Raw IDs are authoritative. A `ResourceKey` holds the same three IDs in `instance/type/group` memory order (`knowledgegraph/research/data-model/01-dbpf-resource-formats.json:138-175,188-204`; `src/assets/Dbpf.cpp:37-100`).
- **Owner:** package/database owns the index and bytes; original `cResourceManager` owns database, factory, type/name, cache, and notification registries. Current `DbpfResourceProvider` borrows one package image and does not own it (`knowledgegraph/research/data-model/12-asset-registry.json:502-595`; `src/compat/ResourceProvider.hpp:32-59`).
- **Producer:** original package authoring/packing; current `parseDbpfIndex`, `extractDbpfRecord`, and `qfsDecompress` (`src/assets/Dbpf.cpp:37-223`).
- **Consumers:** format parsers and original factories/model/Cell/editor/Space paths. Current consumers are GMDL/RW4/WorldObject/raster/Cell parsers and scene loading (`knowledgegraph/research/data-model/12-asset-registry.json:641-749`; `src/assets/Dbpf.hpp:28-46`).
- **Runtime representation:** current `DbpfEntry` plus a bounded `std::vector<uint8_t>` payload. Original representation is bounded by `PFRecordRead`/`RecordInfo` and then a factory-owned typed resource object; exact cache/object lifetime is unresolved (`knowledgegraph/research/data-model/12-asset-registry.json:577-605,1587-1663`).
- **References:** the key is the content address. A DBPF row contains no path/name table; name-to-key derivation remains unresolved (`knowledgegraph/research/data-model/01-dbpf-resource-formats.json:224-233`; `knowledgegraph/research/gameplay-data-model.json:2270-2285`).
- **Lifecycle:** current parse per fetch → exact linear identity scan → extent check → optional QFS decompression → declared-size check (`src/compat/ResourceProvider.hpp:40-53`; `src/assets/Dbpf.cpp:200-235`). Original manager surfaces are initialize/register/find/load/cache/reload/flush/dispose, but exact order and priority are inferred (`knowledgegraph/research/data-model/12-asset-registry.json:1361-1412`).
- **Serialization:** DBPF v3 is a 96-byte header plus 28-byte logical index rows and QFS-compressed or raw payloads. This is static package persistence, not gameplay/save state (`knowledgegraph/research/data-model/01-dbpf-resource-formats.json:138-186`; `src/assets/Dbpf.hpp:1-6`).
- **Gameplay significance:** the key selects or identifies content; it is not itself a team, collision, selection, health, economy, or progression predicate (`knowledgegraph/research/data-model/11-textures-materials-gameplay.json:129-149,174-187`).
- **Current fidelity:** record identity/extraction is represented. Multi-package priority, directory mapping, factory/cache/reload, async ownership, and property round trips are missing (`knowledgegraph/research/data-model/12-asset-registry.json:1671-1703,1753-1833`).

## 2. GMDL, RW4, and model metadata

### GMDL GameModel

- **Identity:** DBPF type `0x00E6BCE5`; group/instance are package-defined per record. Internal top-level keys exist in the static file prefix, while the bounded current parser skips them; material texture-set entries retain group/instance only (`knowledgegraph/research/data-model/02-gmdl-rw4-object-metadata.json:168-200,324-443`; `src/assets/Gmdl.cpp:113-122,210-225`).
- **Owner:** original model/graphics resource system; current parser is a clean-room value decoder (`knowledgegraph/research/data-model/02-gmdl-rw4-object-metadata.json:1015-1066`).
- **Producer:** packaged authoring plus original resource loading; current `parseGmdl` (`src/assets/Gmdl.cpp:95-270`).
- **Consumers:** original model world, bounds/preview, material and draw paths; current `meshFromGmdl` and host renderer. Current `cell_stage` does not consume parsed `materialIds` or `textureRefs` end to end (`knowledgegraph/research/data-model/02-gmdl-rw4-object-metadata.json:1122-1208`; `knowledgegraph/research/data-model/11-textures-materials-gameplay.json:270-291`).
- **Runtime representation:** current `GmdlModel` retains bounds, buffers, descriptors, mesh refs, material IDs, texture refs, and a bounded trailer key. Original static model resources feed RenderWare-style model/mesh/material state; that graph is not reproduced (`src/assets/Gmdl.hpp:58-72`; `knowledgegraph/research/data-model/02-gmdl-rw4-object-metadata.json:768-842`).
- **References:** mesh→index/vertex buffers; mesh→material ID; material-info `0x20D`→texture group/instance; top-level keys are currently skipped (`knowledgegraph/research/data-model/02-gmdl-rw4-object-metadata.json:893-1012`).
- **Lifecycle:** current fetch/decode→host mesh conversion. Original paths include RW4 fallback, model construction, bounds extraction, lifecycle dispatch, and draw submission, but ordering is static-only (`knowledgegraph/research/data-model/02-gmdl-rw4-object-metadata.json:1122-1411`).
- **Serialization:** version-8 static prefix is strictly walked. The remaining animation/bone/deform trailer is accepted opaquely; version 9, unsupported index widths, unknown shader IDs, and incomplete trailer variants are not supported (`src/assets/Gmdl.hpp:1-11,75-82`; `src/assets/Gmdl.cpp:95-270`).
- **Gameplay significance:** model identity and bounds can affect what is visible/selected, but geometry/material fields are not gameplay rules. Gameplay data selects the model through a separate path (`knowledgegraph/research/data-model/11-textures-materials-gameplay.json:129-136,174-185`).
- **Current fidelity:** v8/static path is partial. `consumed == input size` does not prove exact trailer consumption because the parser assigns it after best-effort trailer reads (`src/assets/Gmdl.cpp:244-270`; `knowledgegraph/research/gameplay-data-model.json:3976-3999`).

### RW4 container

- **Identity:** DBPF type `0x2F4E681B`; group/instance are package-defined. Internal section type codes and adjusted offsets locate payloads, but they are not gameplay IDs (`knowledgegraph/research/data-model/02-gmdl-rw4-object-metadata.json:201-225,550-766`).
- **Owner:** original model/material/animation resource manager; current `Rw4` is a structural value object.
- **Producer:** packaged RW4 authoring; current `parseRw4` (`src/assets/Rw4.cpp:107-204`).
- **Consumers:** original RenderWare/model/animation/material paths; current tests and future section decoders only (`knowledgegraph/research/data-model/02-gmdl-rw4-object-metadata.json:982-1012`; `knowledgegraph/research/data-model/11-textures-materials-gameplay.json:270-280`).
- **Runtime representation:** current header fields, type-code table, 24-byte section rows, and adjusted data addresses (`src/assets/Rw4.hpp:35-79`).
- **References:** manifest→types; manifest→section table; each section→type code and extent. `BaseResource` adjusts `pData + pBufferData`; other sections use stored `pData` (`src/assets/Rw4.cpp:147-198`).
- **Lifecycle:** decode/inspect only in OpenSpore. Original payload load and release are not implemented.
- **Serialization:** structural directory bytes only. Mesh, raster, skeleton, skin, keyframe animation, blend shape, and material payload semantics remain unresolved (`knowledgegraph/research/data-model/02-gmdl-rw4-object-metadata.json:657-765`; `knowledgegraph/research/data-model/14-openspore-cross-map.json:1012-1018`).
- **Gameplay significance:** indirect through model/LOD/animation selection; no section code has been shown to encode gameplay selection, team, or collision.
- **Current fidelity:** `complete()` proves structural bounds only. Unknown type codes are informational, and known set membership is not semantic decoding (`src/assets/Rw4.hpp:64-85`; `src/assets/Rw4.cpp:18-49,66-93`).

## 3. Cell records and configuration

### Common identity and ownership

- Each packaged record has a DBPF `(type, group, instance)` identity. Typed cross-record fields usually carry an instance ID; `CellSerializer` or the surrounding typed reference supplies the type context. Group is not inferred from a current source comment or numeric range (`knowledgegraph/research/data-model/03-gameplay-configuration.json:253-261`; `knowledgegraph/research/data-model/20-graph-audit.json:1173-1179`).
- `cCellDataReference_` owns lazy resource resolution and reference lifetime. `cCellGame` owns live pools/current worlds; `cCellGFX` owns preload and presentation state. These are separate owners (`knowledgegraph/research/data-model/12-asset-registry.json:1474-1522`).
- Current OpenSpore represents typed record values and hard-reference validation, but does not reproduce the lazy serializer-backed reference object (`knowledgegraph/research/data-model/12-asset-registry.json:1704-1718`).

### Record registry

| Type | Name and shape | Owner / producer | Main consumers | Key references and significance | Serialization / current mapping |
|---|---|---|---|---|---|
| `0x2A3CE5B7` | `cCellGlobalsResource`, 276 B, 69 words | Cell content; packaged record / `parseCellGlobals` | `cCellGame` initialization and Cell tuning/UI/GFX consumers | world/background refs, start cell, effect/background maps, look algorithm, movement/density/mission/editor methods | direct 276-byte record, not `cCellSerializableData`; represented in `src/assets/CellResource.hpp:32-53`, `src/assets/CellResource.cpp:14-152` |
| `0x9B8E862F` | `cCellWorldResource`, 16 B + 12 B levels + 24 B advect | Cell content; `parseCellWorld` | current/background world refs and advect queries | level→populate, advect→flow ID; execution is not decoding | direct variable record; represented in `src/assets/CellResource.hpp:165-197`, parser at `src/assets/CellResource.cpp:1050-1124` |
| `0xDA141C1B` | `cCellPopulateResource`, 16 B + 76 B markers | Cell content; `parseCellPopulate` | preload, population/spawn planning | distribute/cluster Cell refs, nested populate, counts/size/parts/z; no x/y | represented as typed markers/validation only; `src/assets/CellResource.hpp:442-484`, `src/assets/CellResource.cpp:925-1030` |
| `0xDFAD9F51` | `cCellCellResource`, fixed 796 B | Cell definition content; `parseCellCell` | object creation, model derivation, Cell rules, preload | structure/loot/effect/projectile/transform refs, normal/hard/easy AI, HP, unlock, size, eat, mission trigger | represented in `src/assets/CellResource.hpp:124-163`, `src/assets/CellResource.cpp:1126-1222`; runtime selection is separate |
| `0x4B9EF6DC` | `cCellStructureResource`, 28 B + 40 B attachments | Cell content; `parseCellStructure` | hatch/death effects, attachments, random creature/look presentation | on-death/hatch refs, random creature, effect ID, level bounds, color | represented in `src/assets/CellResource.hpp:406-440`, `src/assets/CellResource.cpp:815-905`; lifecycle execution unknown |
| `0xD92AF091` | `cCellLootTableResource`, 36 B + 28 B rows | Cell reward content; `parseCellLootTable` | eat/decomposition reward path | cell/nested table refs, weight/count/delta/level | represented in `src/assets/CellResource.hpp:366-404`, `src/assets/CellResource.cpp:727-813`; selection/payout unknown |
| `0xF9C3D770` | `cCellRandomCreatureResource`, 8 B + 28 B rows | Cell spawn content; `parseCellRandomCreature` | spawn selection and preload | soft creature ID—not a Cell record ref—plus weight/speed/danger | represented in `src/assets/CellResource.hpp:269-312`; soft-ID resolution missing |
| `0x754BE343` | `cCellPowersResource`, fixed 8 B | Cell tuning; `parseCellPowers` | power/interaction path | teleport cost/range | represented in `src/assets/CellResource.hpp:292-312`; currency/consumer unresolved |
| `0x8C042499` | `cCellLookTableResource`, 8 B + 8 B rows | Cell appearance; `parseCellLookTable` | look selection | type/value table | represented in `src/assets/CellResource.hpp:314-330`; not gameplay identity |
| `0xDBA35AE2` | `cCellLookAlgorithmResource`, 8 B + 20 B rows | Cell appearance; `parseCellLookAlgorithm` | role-based look selection | player/NPC/epic→look-table instance refs | represented in `src/assets/CellResource.hpp:332-364`; original algorithm order missing |
| `0x433FB70C` | `cCellEffectMapResource`, 8 B + 28 B rows | Cell presentation bridge; `parseCellEffectMap` | `cCellGFX::LoadEffectMap` / `InstanceEffectOnCell` | soft effect ID + type/scalars | represented in `src/assets/CellResource.hpp:199-220`, `src/assets/CellResource.cpp:395-427`; original slot/parameter lifecycle partial |
| `0x612B3191` | `cCellBackgroundMapResource`, 8 B + 16 B rows | Cell presentation/world-scale; `parseCellBackgroundMap` | background clear/color | RGB + geometric scale ladder | represented and sampled in current stage; `src/assets/CellResource.hpp:222-267` |

Detailed record layouts and measured counts are in `knowledgegraph/research/data-model/03-gameplay-configuration.json:48-64,67-261` and `knowledgegraph/research/gameplay-data-model.json:2570-3339`.

### Cell runtime representation

- **Identity:** a live Cell is selected by pool/self index, not by a host pointer or DBPF row (`knowledgegraph/research/data-model/04-creature-data.json:374-408`).
- **Owner:** `cCellGame` owns the 4096-slot pool and world/query state. `cCellGFX` owns the associated graphics object and preload worlds.
- **Producer:** `cCellGame::Initialize` at `0x00E80BA0`; `CreateCellObject` at `0x00E74A20`; current `CellGame::initialize` and `createCellObject` reproduce selected writes only (`knowledgegraph/research/data-model/04-creature-data.json:742-759`; `src/sim/CellGame.cpp:22-152`).
- **Consumers:** movement, combat, animation, effects, health UI, queries, and draw. OpenSpore implements selected pure rules but not the original active-update orchestrator (`knowledgegraph/research/data-model/14-openspore-cross-map.json:979-1059`).
- **Runtime representation:** current padded `cCellObjectData` is 920 bytes and preserves selected offsets; it is not the complete logical schema. `Entity` is a separate role/string contract superset and is not a byte-compatible object (`src/sim/CellPool.hpp:23-64`; `src/sim/Sim.hpp:37-78`; `knowledgegraph/research/data-model/14-openspore-cross-map.json:405-434`).
- **References:** main object→model key/Cell resource/GFX index/query pointer; query entry→position/size/pool index. The runtime model key is derived separately at `0x00E65640` (`knowledgegraph/research/data-model/04-creature-data.json:374-405`; `knowledgegraph/research/data-model/12-asset-registry.json:697-748`).
- **Lifecycle:** mode init→CellGame init→GFX preload/display→pool create/update→pool release/rebuild→mode exit/dispose. Static anchors exist, but exact original active order is not observed (`knowledgegraph/research/data-model/04-creature-data.json:772-783`).
- **Serialization:** `cCellSerializableData` (structure 61843) is the mode/save candidate, separate from the direct globals/content records. It contains player creature key, food progression, unlocked parts, counters, missions, difficulty, nanites, and related state; no current parser or round trip exists (`knowledgegraph/research/data-model/04-creature-data.json:429-458,785-791`; `knowledgegraph/research/data-model/14-openspore-cross-map.json:1028-1035`).
- **Gameplay significance:** this is the strongest mapped content-to-gameplay family. AI, size, health, friend/territory, attack gates, eat yield, structure effects, spawns, loot, and mission triggers are gameplay data. Model/material/texture data remains a downstream presentation dependency.
- **Current fidelity:** all twelve direct schemas are represented; runtime reference resolution, record selection, procedural placement, full cCellObjectData behavior, global progression/economy, and persistence are not.

## 4. World objects

The term covers two distinct families and they must not be conflated.

### Asset `0x0F43029A` world-object/model-part record

- **Identity:** DBPF type `0x0F43029A`, package-defined group/instance; versions 9 and 10 (`knowledgegraph/research/data-model/02-gmdl-rw4-object-metadata.json:256-279`).
- **Owner:** unknown original model/content subsystem; no current consumer owns it.
- **Producer:** packaged model authoring; current `parseWorldObject` extracts semantic-looking content (`src/assets/WorldObject.cpp:23-112`).
- **Consumers:** structural inspection only. No current loader, model resolver, placement executor, or Gameplay consumer exists (`knowledgegraph/research/data-model/14-openspore-cross-map.json:137-146,317-323`).
- **Runtime representation:** current `WorldObject` with header counts, lowercase name candidates, plausible vector candidates, and byte accounting. These are not typed entries (`src/assets/WorldObject.hpp:35-69`).
- **References:** names/vectors are extracted heuristically; exact primary-entry grammar, attachment, model/GUID relation, and consumers are unknown.
- **Lifecycle:** package record→decode→inspection only. No original create/destroy/attach behavior is established.
- **Serialization:** 20-byte header plus variable body; complete byte accounting is current behavior, not a recovered writer schema.
- **Gameplay significance:** potential model/attachment metadata only. It is not `cGameData`, a building, CellSerializer content, or a stored scene x/y record (`knowledgegraph/research/data-model/05-world-planet-data.json:44-53,245-256,694-706`).
- **Current fidelity:** structural partial; no placement or original model ownership.

### `cPlanetObjectData` positioned planet object

- **Identity:** runtime `cPlanetObjectData` is not a DBPF row. It is a 44-byte record owned inside `cPlanetRecord.mPlanetObjects`; its identity includes owner/planet context plus object type and ResourceKey (`knowledgegraph/research/data-model/05-world-planet-data.json:431-439,508-510`).
- **Owner:** `cPlanetRecord`; consumers are planet/terrain gameplay and presentation paths.
- **Producer:** planet generation/population; exact producer is unresolved.
- **Consumers:** live planet/terrain behavior, position, health/ammo/loot, model key, and flags.
- **Runtime representation:** object type, explicit position, ammo, artifact type, health, loot-drop time, ResourceKey, and flags.
- **References:** `cPlanetRecord`→object vector; object→ResourceKey.
- **Lifecycle:** create/initialize/update/destruct/persist bodies are incomplete.
- **Serialization:** field layout is static evidence; owner, save framing, and mutation transaction are unknown.
- **Gameplay significance:** this is actual positioned gameplay content, unlike `0x0F43029A`.

## 5. Creatures and entities

### Authored creature data

- **Identity / type / group / instance:** no package TypeID or group is established for `cCreatureDataResource`. `mNameKey` is a `ResourceKey`; each 140-byte `RigblockData` carries group/instance model references, parent/symmetry indices, transform, and capability data (`knowledgegraph/research/data-model/07-editor-data.json:412-450`; `knowledgegraph/research/data-model/04-creature-data.json:618-628`).
- **Owner:** editor authoring/resource subsystem.
- **Producer:** `cCreatureDataResource::Read` at `0x004BF970` and authoring/editor mutations; exact serialized body/order remains unavailable.
- **Consumers:** editor model/runtime conversion; exact package loader and creature creation owner are unresolved.
- **Runtime representation:** ordered `EditorRigblock`/authored graph, `EditorModel`, `cEditor`, animation controllers, and derived skin meshes.
- **References:** rigblock→group/instance model parts; hierarchy by parent/symmetry indices; capabilities/animations/effects; `cEditorResource` snapshot history.
- **Lifecycle:** authored record read→model installed→tools mutate→history commit/undo/redo→derived skin rebuild→save boundary. Exact validation/apply order is not traced (`knowledgegraph/research/data-model/07-editor-data.json:655-722`).
- **Serialization:** `cCreatureDataResource`, `cEditorResource`, and `EditorModel` load/save surfaces exist; byte framing, version, property mapping, and round trip are unknown.
- **Gameplay significance:** author-time structure determines creature part identity, capabilities, paints, and model assembly, but does not itself prove a live creature's AI or ability behavior.
- **Current fidelity:** missing as an OpenSpore asset contract. Cell records are a different family and cannot substitute for it (`knowledgegraph/research/data-model/04-creature-data.json:793-801`).

### Creature runtime entities

- **Identity:** `cCreatureBase` carries definition ID, political ID, model `ResourceKey`, species key/profile, target/neighbor relations, health, ability state, inventory, and animation owner. `cCreatureGameData` carries brain level, evolution points, ability mode, and learned abilities (`knowledgegraph/research/data-model/04-creature-data.json:319-331,543-615`).
- **Owner:** creature mode/game-data and noun/object services; exact cross-mode ownership is incomplete.
- **Producer:** noun registry/factory plus creature game-data/editor conversion; exact creation body is unresolved.
- **Consumers:** creature AI, movement, combat, hunger, ability, social, inventory, progression, animation, and editor/play-mode paths.
- **Runtime representation:** `cCreatureBase` (4032 B static layout), `cCreatureAnimal` (5792 B), `CreatureBlock` (1128 B), `AnimatedCreature`, and `cCreatureGameData`. These are not Cell entities.
- **References:** definition/political/species IDs and model/species ResourceKeys connect records to runtime; noun destruction/restoration and factory semantics are unknown (`knowledgegraph/research/gameplay-data-model.json:2316-2329`).
- **Lifecycle:** create/noun materialize→edit/load model→live update→ability/progression mutation→destroy/refcount release. AI, hunger, motive, damage, and destruction bodies are incomplete (`knowledgegraph/research/data-model/04-creature-data.json:803-814`).
- **Serialization:** `cCreatureGameData` and creature serializable surfaces are not proven to be the same owner as `cCellSerializableData`; cross-stage synchronization is unresolved (`knowledgegraph/research/data-model/04-creature-data.json:785-791`).
- **Gameplay significance:** strong for creature stage, but behavior claims beyond static fields and selected evolution functions remain qualified.
- **Current fidelity:** no general creature runtime/editor implementation.

### Cell entities

`cCellObjectData` and the Cell pool are the implemented entity slice, but only as bounded projections. The 920-byte object, 4096 capacity, selected offsets, and pure movement/combat rules are represented; AI/update orchestration, all side effects, and save rehydration are missing (`knowledgegraph/research/data-model/04-creature-data.json:793-801`; `src/sim/CellGame.hpp:31-155`).

## 6. World, planet, and terrain

### Cell world data

- **Identity:** packaged `0x9B8E862F`; level entries carry populate instance IDs and player-size buckets, while advect rows carry a soft flow ID. Runtime `cCellGame` holds foreground/background world refs.
- **Owner:** Cell content and `cCellGame`; presentation worlds belong separately to `cCellGFX`.
- **Producer:** packaged authoring and `parseCellWorld`.
- **Consumers:** world/current-background selection, populate preload, player creation, advect lookup.
- **Runtime representation:** current `CellWorld`, `AdvectEntry`, and simplified `CellDataReference{id}` world slots. Original refs are 16-byte typed reference objects (`src/assets/CellResource.hpp:165-197`; `src/sim/Advect.hpp:29-104`; `src/sim/CellGame.hpp:49-74`).
- **References:** globals→world; world→populate/advect; populate→Cell; Cell→structure/loot/look/random.
- **Lifecycle:** mode init selects refs; scale-based advect lookup is represented; world selection/start-tile transition and advect payload execution are unknown (`knowledgegraph/research/data-model/05-world-planet-data.json:488-518,674-685`).
- **Serialization:** direct variable Cell record, not save state.
- **Gameplay significance:** high for scale bands, population recipes, flow tuning, and starting selection. Procedural x/y generation and actor materialization are not recovered.
- **Current fidelity:** records and pure advect lookup represented; world execution/placement absent.

### Planet, galaxy, and surface data

- **Identity:** this family uses `StarID`, `PlanetID`, political/empire IDs, and generated-terrain `ResourceKey`, not a universal DBPF triple. `cStarRecord` owns planet records; `cPlanetRecord` carries a 12-byte generated terrain key (`knowledgegraph/research/data-model/05-world-planet-data.json:407-485`).
- **Owner:** `cStarManager`/`cStarRecord` for generated/schema records; `cPlanet`/`cPlanetModel`/`cTerrainSphere` for live/surface state; `PlayerPlanetData` for per-player scan/progress candidates. Exact enclosing owner for `PlayerPlanetData` is unresolved.
- **Producer:** `cPlanetRecord::Create` at `0x00BA6300`; planet generation at `0x00BB4100`; record-to-runtime helper at `0x00BB5B50`. Generation formulas remain incomplete (`knowledgegraph/research/data-model/06-empire-space-data.json:618-640`).
- **Consumers:** Space session, colony/ownership, active planet/star, terrain/surface transition, editor modification, persistence, and presentation.
- **Runtime representation:** `cStarRecord` (176 B), `cPlanetRecord` (432 B), `cPlanet` (456 B), `cPlanetModel` (92 B), `cTerrainSphere` (2640 B), and `PlayerPlanetData` (176 B) (`knowledgegraph/research/data-model/05-world-planet-data.json:407-485`).
- **References:** manager→stars; star→planet records; planet record→live planet; generated terrain key→surface/terrain; planet→civ/tribe/commodity/planet-object state; terrain modification→ResourceKey (`knowledgegraph/research/data-model/05-world-planet-data.json:488-518`).
- **Lifecycle:** galaxy generation/load→planet record→live planet→surface transition→terrain load/update/modify→return/dispose. This is a static projection; original runtime order is unknown (`knowledgegraph/research/data-model/05-world-planet-data.json:600-614`).
- **Serialization:** `cStarRecord`, `cSolarSystem`, `cSimulatorSpaceGame`, `PlayerPlanetData`, and star/planet databases expose persistence surfaces. Exact record order, versions, transaction, and migration are unknown (`knowledgegraph/research/data-model/05-world-planet-data.json:617-660`).
- **Gameplay significance:** high for planet scores, species, colonies, terrain, ownership, progression, and surface actions. Static vectors/fields alone do not prove generation or transaction semantics.
- **Current fidelity:** no general planet, terrain, or Space-to-surface implementation.

## 7. Empire and Space

- **Identity:** `cEmpire.mPoliticalID` is the primary empire identity; `SpacePlayerData` caches empire ID/pointer, active planet/star, context, and colonies. `ResourceKey` identifies species/UFO/captain/item/tool/mission assets. The logical roots `EmpireData` and `SpaceData` are projections over these types (`knowledgegraph/research/data-model/06-empire-space-data.json:62-220,337-438`).
- **Owner:** `cStarManager` owns star/empire/trade-route registry surfaces; `cRelationshipManager`, `cSpaceTrading`, and `cMissionManager` are separate managers; `cSimulatorSpaceGame` composes the active session. High-fan-in manager accessors are not fully named (`knowledgegraph/research/data-model/06-empire-space-data.json:529-537,845-856`).
- **Producer:** galaxy/star/planet generation, empire/home-world/profile/color setters, ship/vehicle load, item initialization, mission selection, and trade helpers (`knowledgegraph/research/data-model/06-empire-space-data.json:618-670`).
- **Consumers:** Space UI/session, active planet/star, ship/vehicle movement/combat, colonies, inventory, trade, diplomacy, missions, and communication.
- **Runtime representation:** `cGameData` prefix plus `cEmpire`, `cStarRecord`, `cPlanetRecord`, `cSimulatorSpaceGame`, `cGameDataUFO`, `cVehicle`, `cPlayerInventory`, `cSpaceInventoryItem`, `cSpaceToolData`, `cMission`, and `cCommEvent` (`knowledgegraph/research/data-model/06-empire-space-data.json:76-335`).
- **References:** political-ID relationship map; empire↔stars/home world; colonies→planets; item `ResourceKey`→trade/mission/tool; mission owner/target political IDs→empire/planet; events→communication records (`knowledgegraph/research/data-model/06-empire-space-data.json:529-616`).
- **Lifecycle:** manager registration→galaxy generation→empire identity/home world→colony/ownership→Space session→inventory/trade→relationship/mission→persistence/reload (`knowledgegraph/research/data-model/06-empire-space-data.json:672-744`).
- **Serialization:** serializable prefixes and PropertyLists exist for empire, stars, missions, inventory, player-planet progress, and trade routes. Exact field sets, database commit, cross-manager transaction, and pointer rehydration are unresolved (`knowledgegraph/research/data-model/06-empire-space-data.json:746-776`).
- **Gameplay significance:** central Space progression/economy/relationship family, but formulas, callback order, pricing, capacity, reward settlement, and runtime reachability are missing.
- **Current fidelity:** no general Space/economy/fleet/event/persistence counterpart. The current Cell `growMeter` and role-string entities do not represent these systems.

## 8. Editor

- **Identity:** editor requests use `editorID`, a creation `ResourceKey`, and active mode ID. Authored resources use `ResourceKey` plus part group/instance and parent/symmetry indices. There is no recovered literal `EditorData` TypeID/type (`knowledgegraph/research/data-model/07-editor-data.json:555-576,749-761`).
- **Owner:** `cEditor` is the transient shell. `cCreatureDataResource`, `cEditorResource`, `EditorModel`, and `EditorRigblock` form an authored-core candidate. `EditorData` is their composite name, not a recovered class.
- **Producer:** model/resource reads and editor input/tool callbacks. `cCreatureDataResource::Read` is at `0x004BF970`; `EditorModel::Load` is at `0x004AE8D0`; mutation/history starts at `0x00588570` and commits at `0x00586410` (`knowledgegraph/research/data-model/07-editor-data.json:613-653`).
- **Consumers:** part/paint/pose tools, history, derived `cEditorSkin`/`cEditorSkinMesh`, animation controllers, palettes/templates, mode manager, and save handlers.
- **Runtime representation:** current original projection would separate persistent authored core, transient `cEditor`, history, `cEditorAnimWorld`, controllers, and derived skin/animation objects (`knowledgegraph/research/data-model/07-editor-data.json:190-260`).
- **References:** EditorModel→rigblocks→ResourceKeys; rigblock→parent/children/symmetry; cEditor→model/history/UI/worlds; EditorRequest→creation key→mode manager; skin→material/texture/model.
- **Lifecycle:** initialize→enter→hover/select/edit→commit/undo/redo→derive skin/model→save/apply→exit/dispose. Exact validation, property/message IDs, and mode handoff are unresolved (`knowledgegraph/research/data-model/07-editor-data.json:655-722`).
- **Serialization:** `EditorModel::Save` at `0x004AF780` and `cCreatureDataResource::Write` at `0x004BFCB0` are boundaries only. PropertyList/DirectPropertyList framing is partially characterized; editor payload headers, versions, property mapping, and round trip are unknown.
- **Gameplay significance:** defines authored creature/vehicle/building appearance and part/capability data that later feeds gameplay/presentation. Editor transient pose/history must not be serialized wholesale as authored data.
- **Current fidelity:** missing. Current `CellAnim` is not an editor or an integrated original animation system (`knowledgegraph/research/data-model/07-editor-data.json:724-747`).

## 9. Progression and economy

- **Identity:** this is not one asset family. Creature progression uses global/game-data state; Cell progression uses `cCellSerializableData`; collectables use `cCollectableItemID(instance, group)`; inventory items use item `ResourceKey`; missions use mission/owner/target IDs; Space uses political IDs and commodity keys (`knowledgegraph/research/data-model/08-progression-economy.json:239-280,516-539`).
- **Owner:** creature game data, `cCollectableItems`, Cell serializable state, scenario play/economy, `cPlayerInventory`, `cMissionManager`, `cSpaceTrading`, `cEmpire`, and commodity nodes are separate owners. `ProgressionData`/`EconomyData` are analytical projections (`knowledgegraph/research/data-model/08-progression-economy.json:8-15,239-280`).
- **Producer:** evolution point add/set/threshold, collectable registration, mission selection, item initialization, trade/store generation, and scenario/economy setters. Registration is not an unlock grant (`knowledgegraph/research/data-model/08-progression-economy.json:516-566,701-723`).
- **Consumers:** creature/Cell/collectable/scenario progression, missions, inventory, tools, trade, and empire money.
- **Runtime representation:** `cCreatureGameData`, `cCollectableItems`, `cCellSerializableData`, scenario play/economy records, `cPlayerInventory`/`cSpaceInventoryItem`/`cSpaceToolData`, `cMission`/`cMissionManager`, `cSpaceTrading`/`cCommodityNode`, and `cEmpire.mEmpireMoney` (`knowledgegraph/research/data-model/08-progression-economy.json:319-514`).
- **References:** collectable ID→unlock/status/list; mission rewards/unlocks→money/inventory; item ResourceKey→tools/trade/mission; commodity political IDs→empire ownership; scenario economy→play goals. Exact settlement paths are incomplete.
- **Lifecycle:** configure/register→earn/spend→status/unlock/mission/tool/inventory mutation→save/load. Exact grant, debit, payout, rollback, and cross-mode synchronization are unknown (`knowledgegraph/research/data-model/08-progression-economy.json:597-607,701-713`).
- **Serialization:** owner-specific serializable/PropertyList surfaces exist, but PROP/SPO framing, field order, migrations, and cross-stage survival are unknown (`knowledgegraph/research/data-model/08-progression-economy.json:609-633`).
- **Gameplay significance:** very high, but only bounded fields and selected mutations are established. Never merge evolution points, Cell points spent, collectable unlock points, adventure points, mission money, and empire money into one balance.
- **Current fidelity:** missing as a global system. Current `CellLootTable` decoding is content-only; current `PlayerState.growMeter` is a local contract counter and is not any original progression/currency field (`knowledgegraph/research/data-model/08-progression-economy.json:636-699`).

## 10. Textures, materials, and gameplay-significant presentation

### Texture and material identity

- **GMDL texture ref:** material-info ID `0x20D` carries sampler/opaque bytes plus a referenced texture group/instance in the bounded schema. The current parser preserves only group/instance; type is not present in that entry (`knowledgegraph/research/data-model/02-gmdl-rw4-object-metadata.json:444-521`; `src/assets/Gmdl.cpp:210-229`).
- **Raster:** DBPF type `0x2F4E681C`, package-defined group/instance. Current decode covers a 32-byte envelope, derived layer count, DXT5, and layer-0 mips (`src/assets/Texture.hpp:17-49`; `src/assets/Texture.cpp:70-113`).
- **Material runtime:** GMDL material IDs associate meshes with `Material.materialID`/`MaterialShader.mID`; RW4 section codes locate mesh/raster/compiled-state data. Original runtime uses material shader, compiled state, texture slots, and rasters (`knowledgegraph/research/data-model/11-textures-materials-gameplay.json:151-172`).
- **Owner:** original material/texture managers and presentation owners; CellGFX preloads graphics objects, editor skin owns derived material/texture references.
- **Producer:** packaged model/material/raster assets; `PaintSkin`/`FromRigblocks` produce editor skin state. Current DXT5 decoder and Vulkan upload are host producers.
- **Consumers:** model/world/editor draw, Cell GFX, terrain passes, and UI. Current GMDL texture refs are not consumed by `cell_stage`; a fixed raster is used for the bounded textured scene.
- **Runtime representation:** original `MaterialShader`, `Material`, `CompiledState`, `TextureSlot`, `Graphics::Texture`, and `RenderWare::Raster`; current `ImageRGBA`, `TextureHandle`, and `MaterialState` (`src/renderer/Renderer.hpp:21-50,68-81`).
- **References:** mesh→material ID; shader ID→compiled state; slot→raster; gameplay object→model/GFX/effect request. No texture-pixel field participates in Cell query geometry (`knowledgegraph/research/data-model/11-textures-materials-gameplay.json:174-186`).
- **Lifecycle:** original material registry→model/raster load→slot binding→draw; current raster decode→single-level texture upload→textured draw→handle destruction. Original writer/external-reference order is unknown (`knowledgegraph/research/data-model/11-textures-materials-gameplay.json:218-248`).
- **Serialization:** raster and GMDL on-disk records are represented. Original material/texture write APIs are interface-only; byte schemas and round trips are missing.
- **Gameplay significance:** material/texture identity can be selected by gameplay content, but no recovered texture channel directly encodes selection, team/faction, visibility, collision, terrain gameplay, or health. Empire identity color is a separate gameplay field (`knowledgegraph/research/data-model/11-textures-materials-gameplay.json:129-136,243-245`).
- **Current fidelity:** DXT5 and a single lit Vulkan path are bounded. Original shader families, multi-texture state, mip upload, material cache, light/blend behavior, atlas semantics, and pixels are not reproduced (`src/renderer/Renderer.hpp:34-38,68-81`; `knowledgegraph/research/data-model/11-textures-materials-gameplay.json:250-268`).

### Gameplay-significant presentation records

- **Cell effect map:** `0x433FB70C` is gameplay-triggered presentation data, not a texture. Static paths support effect-map loading and effect-on-cell placement, but exact parameter/slot/event semantics are partial (`0x00E63560`, `0x00E66840`; `knowledgegraph/research/data-model/11-textures-materials-gameplay.json:180-181,210-214`).
- **Cell background map:** `0x612B3191` supplies world-scale RGB in the bounded current consumer. It is not a sky/terrain model or gameplay selector (`knowledgegraph/research/data-model/05-world-planet-data.json:219-230`).
- **Health UI:** live GFX object/health state triggers `ShowHealthRollover` at `0x00E62340`; the image/layout asset is downstream and is not the health predicate (`knowledgegraph/research/data-model/11-textures-materials-gameplay.json:182-184,215-216`).
- **Editor skin:** paints/colors are authored state that feeds derived material/texture production, but the exact save/paint-to-texture contract is unresolved.

## OpenSpore comparison

### Represented current behavior

- DBPF/QFS identity, extent, and extraction for one 32-bit package (`src/assets/Dbpf.hpp:16-46`; `src/assets/Dbpf.cpp:37-235`).
- GMDL v8 static geometry/material prefix and host mesh conversion, with the trailer explicitly bounded/opaque (`src/assets/Gmdl.hpp:1-11`; `src/assets/Gmdl.cpp:95-270`).
- RW4 structural directory and DXT5 layer-0 decode (`src/assets/Rw4.hpp:46-85`; `src/assets/Texture.cpp:70-113`).
- Cell direct schemas, hard-reference validation, and byte-stable dumps (`src/assets/CellResource.hpp:32-500`; `src/assets/CellResource.cpp:124-1295`).
- 920-byte/4096 Cell pool projection, selected advect/combat rules, deterministic movement/eat/flee contract, and a narrow mode/GFX/UI shell (`src/sim/CellPool.hpp:23-164`; `src/sim/Combat.hpp:14-128`; `src/apps/CellModeStrategy.cpp:7-94`).
- A declarative scene with record-confirmed/inferred provenance and host flat/textured draw (`src/apps/SceneConfig.hpp:1-47`; `src/apps/scene.json:1-75`; `src/renderer/Renderer.hpp:53-87`).

The cross-map classifies these as bounded format, decoder, pure-rule, seam, and deterministic-contract slices—not original runtime equivalence (`knowledgegraph/research/data-model/14-openspore-cross-map.json:882-928`).

### Intentional modern divergence

| ID | OpenSpore choice | Why intentional | Non-equivalence boundary | Provenance |
|---|---|---|---|---|
| `DIV-001` | C++17 host value types, vectors/maps/strings | modular safety and deterministic behavior | not original 32-bit ABI | `knowledgegraph/research/gameplay-data-model.json:3605-3629` |
| `DIV-002` | stateless single-package provider | isolate record fetch | no original multi-package manager | `knowledgegraph/research/gameplay-data-model.json:3631-3649` |
| `DIV-003` | C++/Python DBPF variant support differs | strict runtime vs research tool | do not transfer Python acceptance to C++ | `knowledgegraph/research/gameplay-data-model.json:3651-3669` |
| `DIV-004` | C++ GMDL v8 vs Python/tool variant support | narrow production path | no GMDL v9 equivalence | `knowledgegraph/research/gameplay-data-model.json:3671-3689` |
| `DIV-005` | best-effort opaque GMDL trailer | load real Cell family | no animation/trailer completeness | `knowledgegraph/research/gameplay-data-model.json:3691-3709` |
| `DIV-006` | fixed-step role-string CellSim | deterministic tests | not original update loop/AI/event order | `knowledgegraph/research/gameplay-data-model.json:3711-3734` |
| `DIV-007` | generated Cell fixtures | regression determinism | not original oracle | `knowledgegraph/research/gameplay-data-model.json:3736-3759` |
| `DIV-008` | modern Vulkan/GLSL renderer | portable minimal backend | no original material/animation/pixel semantics | `knowledgegraph/research/gameplay-data-model.json:3761-3784` |
| `DIV-009` | vector-backed Cell query | simple deterministic host behavior | not original linked-pool storage/order | `knowledgegraph/research/gameplay-data-model.json:3786-3809` |
| `DIV-010` | resolver fallbacks and heuristics | inspectability | raw IDs remain canonical | `knowledgegraph/research/gameplay-data-model.json:3811-3834` |
| `DIV-011` | WorldObject semantic extraction | bounded inspection | no typed loader/placement | `knowledgegraph/research/gameplay-data-model.json:3836-3854` |
| `DIV-012` | content pointer slots vs host addresses | prevent pointer contamination | separate serialization-neutral refs | `knowledgegraph/research/gameplay-data-model.json:3856-3879` |

### Missing or partial current behavior

- Original active-update orchestrator and full Cell service/AI/GFX/effect ordering (`knowledgegraph/research/data-model/14-openspore-cross-map.json:979-986`).
- Original resource manager priority/cache/directory/factory/property behavior (`knowledgegraph/research/data-model/14-openspore-cross-map.json:1021-1026`).
- Procedural placement and player identity (`knowledgegraph/research/data-model/14-openspore-cross-map.json:997-1003`).
- GMDL v9/complete trailer and RW4 payload/material/animation/skin execution (`knowledgegraph/research/data-model/14-openspore-cross-map.json:1004-1018`).
- `cCellSerializableData` and general PropertyList/SPO persistence (`knowledgegraph/research/data-model/14-openspore-cross-map.json:1028-1035`).
- General editor authored data, paint/skin, history, animation controller, validation, and save/apply (`knowledgegraph/research/data-model/14-openspore-cross-map.json:1053-1059`; `knowledgegraph/research/data-model/07-editor-data.json:724-747`).
- Planet/terrain, Space, empire, fleet, inventory, trade, mission, diplomacy, and cross-stage progression/economy (`knowledgegraph/research/data-model/05-world-planet-data.json:662-672`; `knowledgegraph/research/data-model/06-empire-space-data.json:778-843`; `knowledgegraph/research/data-model/08-progression-economy.json:636-699`).
- Original event transport and universal event-to-message mapping (`knowledgegraph/research/gameplay-data-model.json:2302-2419`).

### Wrong or stale assumptions corrected here

| Assumption | Correct bounded statement | Evidence |
|---|---|---|
| `IResourceProvider` equals original `cResourceManager` | It fetches bytes from one borrowed package; manager orchestration is missing | `knowledgegraph/research/gameplay-data-model.json:3881-3900`; `src/compat/ResourceProvider.hpp:21-59` |
| Cell content records are save state | Content, live `cCellObjectData`, and `cCellSerializableData` are separate | `knowledgegraph/research/gameplay-data-model.json:3901-3920`; `knowledgegraph/research/data-model/04-creature-data.json:785-791` |
| globals are Ghidra structure 61843 | 61843 is `cCellSerializableData`; globals are 61885. Current comments at `src/assets/CellResource.hpp:1-7` are stale provenance | `knowledgegraph/research/gameplay-data-model.json:3921-3945`; `knowledgegraph/research/data-model/14-openspore-cross-map.json:1072-1080` |
| C++ GMDL rejects any opaque trailer failure | It strictly validates the prefix and accepts the remaining tail opaquely | `knowledgegraph/research/gameplay-data-model.json:3946-3999`; `src/assets/Gmdl.cpp:244-270` |
| `GmdlModel.consumed` proves exact parsing | `consumed` is assigned to input size after best-effort trailer reads | `src/assets/Gmdl.cpp:266-270` |
| RW4 `complete()` means all types are decoded | It proves structural bounds; known type maps are informational | `src/assets/Rw4.hpp:64-85`; `src/assets/Rw4.cpp:18-49,66-93` |
| C++ RW4 and Python type maps are equivalent | Labels cannot be transferred across parsers | `knowledgegraph/research/gameplay-data-model.json:4001-4045` |
| current C++ GMDL supports v9 | current C++ requires v8 | `src/assets/Gmdl.cpp:95-112` |
| WorldObject records are CellSerializer or placement data | They are a separate model/part-definition family; markers have no x/y | `knowledgegraph/research/data-model/05-world-planet-data.json:694-706`; `src/apps/SceneConfig.hpp:7-13` |
| `Entity.mIsIdle` is maintained as `!alive` | `mIsIdle` is an inert original-field projection; `alive` is separate contract state | `src/sim/Sim.hpp:37-69`; `knowledgegraph/research/gameplay-data-model.json:4091-4115` |
| `growMeter` is evolution points/unlock points/money | it is only a local CellSim counter | `src/sim/Sim.hpp:80-87`; `knowledgegraph/research/gameplay-data-model.json:4116-4139` |
| generated Cell fixtures are an original oracle | they pin current deterministic behavior only | `knowledgegraph/research/gameplay-data-model.json:4141-4164` |
| C++ and Python DBPF accept the same variants | C++ rejects DBBF and has stricter QFS behavior | `src/assets/Dbpf.cpp:37-100,103-223`; `knowledgegraph/research/gameplay-data-model.json:4191-4215` |
| CellSim is the original update loop | it is a separate fixed-step host contract | `src/sim/Sim.cpp:99-260`; `knowledgegraph/research/data-model/14-openspore-cross-map.json:711-725` |
| Vulkan lit output represents original rendering | it is a modern host approximation | `src/renderer/Renderer.hpp:34-81` |
| resolver names/stage bytes are canonical semantics | raw IDs and bounded semantic evidence take precedence | `knowledgegraph/research/gameplay-data-model.json:4266-4290` |
| `0x00E82340` and `0x00E82420` are the same exact function | use SDK-associated `0x00E82420`; keep `0x00E82340` separate/unresolved | `knowledgegraph/research/gameplay-data-model.json:4291-4310`; `knowledgegraph/research/data-model/20-graph-audit.json:1173-1179` |
| scene roles/positions are original | all positions and player/food/prey roles are inferred; only backdrop identities are verified | `src/apps/scene.json:3-72` |
| `mModelKey[3]` comment order is authoritative | original memory order is instance/type/group; the current `{group,type,instance}` comment is unreliable | `src/sim/CellPool.hpp:51`; `knowledgegraph/research/data-model/05-world-planet-data.json:699-702` |
| CellGlobals and CellSerializableData share provenance | parser shape can be correct while structure attribution is wrong | `knowledgegraph/research/data-model/14-openspore-cross-map.json:1072-1080` |

## Relationship and ownership conclusions

1. **Keep four explicit layers.** Package/content, typed runtime resources, live gameplay state, and presentation/save state must not be collapsed. In particular, `N-PRESENTATION-DATA` has high graph degree but is separated from `N-CELL-RUNTIME-STATE` (`knowledgegraph/research/gameplay-data-model.json:1362-1382`).
2. **Use a complete stable asset key, but preserve domain reference forms.** DBPF/model/texture assets use T:G:I; Cell content uses typed instance refs; Space/editor/progression use their domain IDs. A universal raw-pointer object graph would erase evidence boundaries.
3. **Make registries explicit and non-authoritative by type.** Resource factories/databases, Cell typed refs, noun/object definitions, Space political/planet registries, collectables, and material/texture caches have different keys and owners. Normalize them only at an adapter boundary.
4. **Represent references as values.** Current pointer-shaped serialized slots and current host addresses are not portable or canonical. Preserve logical IDs plus explicit provenance and resolution status (`knowledgegraph/research/gameplay-data-model.json:3497-3502,3856-3879`).
5. **Treat event transport as family-specific.** A gameplay mutation may cause animation/effect/UI/message consequences, but no universal event ABI is proven. Do not promote current `"eat"`/`"flee"` strings into original events (`src/sim/Sim.hpp:208-220`; `knowledgegraph/research/data-model/20-graph-audit.json:289-297`).
6. **Preserve runtime unknowns in the model.** Name-to-key derivation, package precedence, original Cell placement/update, planet surface execution, mission/economy settlement, editor save/apply, and persistence framing remain explicit unknowns rather than defaults.

## Highest-value central gaps

- Original multi-package resource precedence, cache lifetime, directory/name mapping, and factory behavior.
- Cell typed-reference resolution across serializer/group context, world selection, procedural x/y placement, and active-update ordering.
- GMDL v9/trailer/animation and RW4 payload/material/skeleton/skin execution.
- Cell gameplay-to-event transport and all non-Cell live event/queue semantics.
- Planet generation and Space-to-terrain transition, terrain codec, and surface mutation order.
- Editor authored package/loader, exact conversion among authored schemas, save/apply validation, and round trip.
- Progression/economy grant/spend/payout order, cross-mode synchronization, and persistence.
- PROP/SPO framing, object remapping, versions, migration, rollback, and save/load round trips.

These match the canonical blocker set at `knowledgegraph/research/gameplay-data-model.json:4544-4551` and the normalized audit recommendations at `knowledgegraph/research/data-model/20-graph-audit.json:1121-1164`.
