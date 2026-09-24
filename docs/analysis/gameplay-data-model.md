# Gameplay Data Model

## Scope and evidence policy

This report is the bounded gameplay-data synthesis defined by `knowledgegraph/research/gameplay-data-model.json`. It describes the relationships among packaged content, decoded static records, runtime gameplay state, caches/presentation, mode ownership, and save/profile state. It is not a claim that the original executable has been reconstructed or that OpenSpore has original runtime, ABI, save/load, or pixel equivalence.

The canonical dossier covers 21 deterministic JSON artifacts, 21 requested domains, 32 schema nodes, 12 major relationships, 31 lifecycle/content transitions, 18 save/load entry points, 72 OpenSpore comparisons, 14 reconstruction packages, and 15 remaining questions (`knowledgegraph/research/gameplay-data-model.json:3344-3356`, `knowledgegraph/research/gameplay-data-model.json:4388-4408`). The eleven final-report points are retained as the coverage checklist (`knowledgegraph/research/gameplay-data-model.json:4409-4542`).

The source hierarchy is deliberate:

- Artifacts 15-18 are canonical cross-track reconciliations.
- Artifacts 19-21 are controlling audits for provenance, graph direction, unresolved claims, and mission coverage.
- Artifacts 01-14 retain direct bounded detail and are used only where a concrete symbol, layout, address, or evidence locator is needed for clarification.
- Current local-worktree OpenSpore source, tests, fixtures, and clean-room projections establish current behavior only. They are not original save/runtime/ABI/pixel oracles.
- SDK names, layouts, enums, and vtables are static evidence; they do not independently prove undocumented behavior, exact function identity, ownership, or runtime execution.
- Static decompilation is used for bounded mechanics and provenance only; no decompiled code is reproduced.

The staged input scope is intentional: DM01-DM18 are the 18 worker inputs, while DM01-DM21 are the 21 canonical input artifacts. DM01-DM18 and TY08 are untracked local-worktree inputs, so no clean-checkout reproducibility is claimed (`knowledgegraph/research/gameplay-data-model.json:12066-12078`).

These rules are stated in `knowledgegraph/research/gameplay-data-model.json:4360-4386`, including the precedence order at `knowledgegraph/research/gameplay-data-model.json:4376-4383`. The input set explicitly excludes the Ghidra database, `SPORE/`, historical artifact rewrites, proprietary or leaked material, and runtime-validation claims (`knowledgegraph/research/gameplay-data-model.json:12042-12064`).

### Evidence levels used here

| Level | Meaning in this report |
|---|---|
| `VERIFIED` | A direct current implementation, local-worktree test, frozen export, pinned read-only query, or deterministic artifact comparison proves the stated bounded claim. It does not automatically prove original runtime truth. |
| `CONFIRMED` | A targeted static body or exact read-only layout/body query is corroborated by structure, xref, or a second static source. It is still not runtime truth. |
| `SUPPORTED` | A direct structure, interface surface, local-worktree dossier, or multi-source static agreement supports a bounded claim without runtime confirmation. |
| `INFERRED` | A bounded interpretation follows from static names, layouts, call shape, or cross-artifact agreement. The undocumented suffix remains open. |
| `OBSERVED_CURRENT` | Direct current OpenSpore source, test, fixture, or clean-room projection establishes current behavior only. |
| `UNKNOWN` | Available evidence is absent, contradictory, or insufficient for the stated claim. |

The campaign runtime-validation result is `NOT_ESTABLISHED` (`knowledgegraph/research/gameplay-data-model.json:3498-3498`). Whenever a flow or lifecycle below is described as partial, inferred, or static, that qualification is intentional: no positive original-process gameplay, editor, save, or load trace is available.

## Final-report coverage

| Point | Status | Coverage in this report |
|---|---|---|
| FR-01 Scope, inputs, evidence | Covered | Scope, clean-room boundary, artifact hierarchy, and evidence levels above. |
| FR-02 Executive coverage | Covered | Coverage counts and classification totals below. |
| FR-03 Resource identity, DBPF, QFS, registry | Partial | Resource identity, package record lookup, registry, cache, and openSpore provider seam. |
| FR-04 Asset and presentation formats | Partial | GMDL, RW4, raster/DXT5, WorldObject, and presentation separation. |
| FR-05 Gameplay content and configuration | Partial | Twelve direct Cell schemas, hard/soft references, configuration, and `0x00E4CE20` correction. |
| FR-06 Cell runtime and gameplay | Partial | Pool, query, live state, pure rules, and missing original update order. |
| FR-07 Creature and editor authoring | Partial | CreatureData, rigblocks, authored assets, transient editor runtime, and asset-save boundary. |
| FR-08 Planet, Space, Empire, city, building | Partial | Generated records, surface state, empire/space projections, city/layout, and missing lifecycle rules. |
| FR-09 Progression, economy, events, messages | Partial | Progression/economy projections, subsystem-specific events, queues, and no universal ABI. |
| FR-10 Persistence and serialization | Missing | Layer inventory, entry points, codecs, survival limits, and blockers. |
| FR-11 Cross-mode ownership and lifecycle | Partial | Noun/object registry, mode transitions, ownership boundaries, and unresolved handoff. |

## Executive coverage summary

The requested-domain result is 20 partial and one missing; no domain is fully covered. The OpenSpore comparison inventory contains 10 represented, 10 partial, 20 missing, 20 incorrect, and 12 intentional modern-divergence items (`knowledgegraph/research/gameplay-data-model.json:4388-4408`). The source graph retains 48 edges and 10 flows; the canonical normalized graph has 32 canonical nodes plus the disclosed `N-PLANET-SURFACE` supporting node, 49 edges after adding `E-052`, and the 10 source flows plus one qualified derived flow (`knowledgegraph/research/gameplay-data-model.json:446-449`, `knowledgegraph/research/gameplay-data-model.json:2253-2271`, `knowledgegraph/research/gameplay-data-model.json:12066-12070`).

The model is therefore best read as a semantic partition with explicit seams, not as a recovered universal class hierarchy, generic content envelope, universal event ABI, or complete persistence stack. `N-OBJECT-REGISTRY` is explicitly a semantic adapter boundary rather than a universal original ABI (`knowledgegraph/research/gameplay-data-model.json:2-18`).

## Data-state partition

The central rule is to keep the following categories separate.

| Category | Canonical examples | What it owns | What it does not own |
|---|---|---|---|
| Static templates/content | DBPF record bytes; direct Cell TypeID records; GMDL v8; RW4 envelope; raster/DXT5; `cCreatureDataResource` | Packaged definitions, references, tuning, model/material/texture identity, authored data | Live transforms, pool ownership, save fields, event order, original writers |
| Runtime entities/state | `cCellGame`, `cObjectPool<cCellObjectData>`, `cCellObjectData`, creature runtime, `cGameData` instances, city/space session objects | Transform, health, behavior, query state, live ownership, mode-owned composition | Static asset bytes as a substitute, presentation pixels as gameplay truth, whole-object save coverage |
| Caches/derived/presentation | `cCellDataReference_`, resource cache, `cCellGFX`, `MaterialShader`, renderer handles, editor skin/mesh | Lazy resolution, resource retention, preload, draw state, derived presentation | Profile/save state, collision/health/progression ownership, original RenderWare execution |
| Persistent save/profile state | `cCellSerializableData`, `cSavedGameHeader`, `GameLoadParameters`, `cGameData`, `cCollectableItems`, `cStarRecord`, `cEmpire`, missions, inventory, trade routes | Declared serializable candidates, headers, mode-specific state, version/count metadata | Automatic survival, exact wire framing, universal object restoration, direct live-object wholesale serialization |

The classification is explicit in the persistent/transient table at `knowledgegraph/research/gameplay-data-model.json:10641-11903`. A pointer, cache, material, or draw handle is not a save field merely because it is reachable from a persistent owner.

## Major gameplay data structures

The following are the 32 canonical semantic nodes. Stable node IDs are synthesis identifiers unless the dossier explicitly names a recovered structure. Identifiers are unique within each entity kind/view; intentional cross-view reuse is reference linkage, not duplicate identity, and global uniqueness is not a valid test for this model. The node type and package assignments are taken from `knowledgegraph/research/gameplay-data-model.json:2049-2208`; the identifier contract is at `knowledgegraph/research/gameplay-data-model.json:4373-4374`.

| Node | Type | Bounded role |
|---|---|---|
| `N-ASSET-RECORD` | template boundary | DBPF content record selected by complete type/group/instance identity; raw or QFS-compressed payload; not runtime or save state. |
| `N-ASSET-REGISTRY` | manager service | `cResourceManager` boundary over databases, factories, type/name/extension mappings, notifications, and cache state. |
| `N-RESOURCE-KEY` | identity boundary | Stable content identity expressed as three named `uint32` components; memory order is not the semantic graph key. |
| `N-RESOURCE-SYSTEM` | manager service | Identity-to-record/factory/typed-object/cache path. |
| `N-TYPED-RESOURCE-CACHE` | runtime reference | `cCellDataReference_` lazy reference/cache boundary; not a serialized save record. |
| `N-CELL-CONTENT` | template family | Twelve direct Cell TypeID records, typed hard references, and Cell content graphs. |
| `N-CELL-WORLD-DATA` | logical data boundary | Cell world/populate/advect/background/look template aggregate; excludes live per-entity x/y claims. |
| `N-CELL-RUNTIME-STATE` | runtime state | Canonical gameplay-runtime node: `cCellGame`, pool/query state, transforms, health, GFX associations, and world references. |
| `N-CELL-SAVE-STATE` | save state | `cCellSerializableData` progression/tutorial/mission/counter candidate held separately from live pools. |
| `N-CELL-PRESENTATION` | presentation boundary | `cCellGFX`, `cCellUI`, render worlds, preload vectors, effects, and display state downstream of gameplay. |
| `N-CONFIGURATION-DATA` | configuration boundary | `IConfigManager`, `cOption`, `ArgScript`, collectable configuration, and named preference surfaces. |
| `N-PROPERTY-LIST` | configuration/serialization boundary | Typed local property map, parent fallback, operation counter, and explicit `Read`/`Write`. |
| `N-CREATURE-DATA` | logical data boundary | Analytical name for authored `cCreatureDataResource`; no literal original `CreatureData` type is claimed. |
| `N-CREATURE-RIGBLOCK` | template boundary | Authored part, hierarchy, symmetry, transform, capability, paint, and model-group definitions. |
| `N-CREATURE-RUNTIME` | runtime entity boundary | `cCreatureBase`/`cCreatureAnimal` and related live state resolved through the noun registry. |
| `N-EDITOR-DATA` | logical data boundary | Analytical composite separating authored core from editor runtime; not a literal `EditorData` record. |
| `N-EDITOR-RUNTIME` | runtime state | `cEditor`, history, animation world/controller, pose, skin, and request state. |
| `N-CITY-DATA` | logical data boundary | `cCity`, `cBuilding`, `cLayoutSlot`, value/live records, placement, processing, ownership, and removal. |
| `N-EMPIRE-DATA` | logical data boundary | Political identity, home world, culture/color, relationships, economy, and `SpacePlayerData` cache projection. |
| `N-RELATIONSHIP-DATA` | logical data boundary | Relationship map, status/attitude, transition deltas, and communication consequences keyed by political identity. |
| `N-PLANET-DATA` | logical data boundary | `cPlanetRecord` and generated planet schema state; distinct from live terrain. |
| `N-SPACE-DATA` | logical data boundary | `cStarManager`, `cStarRecord`, `cPlanetRecord`, space session, empire, missions, inventory, trade, and active context. |
| `N-MISSION-DATA` | logical data boundary | Tracked missions, objectives, costs, rewards, tools, deliverables, and progress. |
| `N-ECONOMY-DATA` | logical data boundary | Commodities, inventory, trade routes, mission costs/rewards, currency/value, and resource-key exchanges. |
| `N-PROGRESSION-DATA` | analytical projection | Creature evolution, collectables, Cell progression, scenario goals/acts/points, difficulty, and mode state. |
| `N-EVENT-DATA` | logical data boundary | Family of communication, animation, editor, deferred, feedback, and space event records; no universal event ABI. |
| `N-MESSAGE-SYSTEM` | manager service | `IMessageManager` registration, queue records, send/post, dispatch, and release. |
| `N-PRESENTATION-DATA` | logical data boundary | Composite model/material/shader/raster, render worlds, UI, Cell GFX, and draw state. |
| `N-MODEL-ASSETS` | template family | GMDL/RW4/model, material, texture, and derived presentation inputs. |
| `N-OBJECT-REGISTRY` | manager service | `Object`, `ISimulatorSerializable`, `cGameData`, noun factory/materialization, and owner/political identity. |
| `N-SAVE-DATA` | logical data boundary | Header, load context, persistence manager, serializers, mode-specific save candidates, and database records. |
| `N-GAME-MODE-LIFECYCLE` | lifecycle boundary | Mode registration, exit/enter, mode-owned runtime/presentation services, and unresolved handoff. |

`N-PLANET-SURFACE` is an additional supporting node, not a claimed literal original type. It exists to separate generated `N-PLANET-DATA` from the live surface/terrain transition (`knowledgegraph/research/gameplay-data-model.json:2257-2271`).

## Logical schemas

### Resource identity and lookup schema

The stable content identity is the complete type/group/instance tuple. The canonical memory layout is reported as `group_id`, `instance_id`, `type_id`, while the strongest original `ResourceKey` layout evidence is `instance_id`, `type_id`, `group_id`; the semantic model therefore requires named conversion and forbids treating the memory order as an unlabelled serialized triple (`knowledgegraph/research/gameplay-data-model.json:9035-9138`). Raw DBPF IDs remain authoritative over names, labels, and resolver heuristics (`knowledgegraph/research/gameplay-data-model.json:3333-3337`).

The current DBPF seam is bounded to the 32-bit DBPF v3 path, QFS decompression, extent checks, and exact record lookup. The current Python tool can inspect more variants than the production C++ path, but that is an intentional tool/runtime capability split (`knowledgegraph/research/gameplay-data-model.json:10506-10555`, `knowledgegraph/research/gameplay-data-model.json:9980-9988`).

### Direct Cell content schemas

The twelve direct Cell records are static content layouts. They do not use a recovered generic `CellSerializer` name/ID envelope. The exact layout and TypeID evidence is:

| TypeID | Structure | Bounded layout/semantic role |
|---|---|---|
| `0x2A3CE5B7` | `cCellGlobalsResource` | Fixed 276 bytes; 69 consecutive 4-byte fields; Cell tuning and world-selection content. |
| `0x433FB70C` | `cCellEffectMapResource` | `8 + 28*numEntries`; effect rows and Cell gameplay-to-presentation bridge. |
| `0x4B9EF6DC` | `cCellStructureResource` | `28 + 40*numAttachments`; attachment rows and Cell content graph. |
| `0x612B3191` | `cCellBackgroundMapResource` | `8 + 16*numEntries`; background/color input, not team, selection, or collision state. |
| `0x754BE343` | `cCellPowersResource` | Fixed 8 bytes; teleport cost/range tuning; runtime use is unresolved. |
| `0x8C042499` | `cCellLookTableResource` | `8 + 8*numEntries`; appearance rows, not gameplay identity. |
| `0x9B8E862F` | `cCellWorldResource` | `16 + 12*numPopulate + 24*numAdvect`; world, populate, and advect content references. |
| `0xD92AF091` | `cCellLootTableResource` | `36 + 28*numEntries`; reward rows; inventory settlement and original payout order are unresolved. |
| `0xDA141C1B` | `cCellPopulateResource` | `16 + 76*numMarkers`; marker/spawn planning; live x/y is not recovered. |
| `0xDBA35AE2` | `cCellLookAlgorithmResource` | `8 + 20*numEntries`; role/reference rows; algorithm execution is unresolved. |
| `0xDFAD9F51` | `cCellCellResource` | Fixed 796 bytes; identity, AI, size/eat data, and references to structure, loot, effects, missions, look, and related content. |
| `0xF9C3D770` | `cCellRandomCreatureResource` | `8 + 28*numEntries`; spawn candidates; soft-ID selection and original integration are unresolved. |

The exact TypeID/layout pairs are in `knowledgegraph/research/gameplay-data-model.json:14135-14385`. The semantic roles and unresolved suffixes are in `knowledgegraph/research/gameplay-data-model.json:2471-3342`. The direct-record versus `cCellSerializableData` distinction is verified at `knowledgegraph/research/gameplay-data-model.json:14653-14662`.

`cCellGlobalsResource` must not be identified as Ghidra structure `61843`: the canonical correction assigns `61843` to `cCellSerializableData` and `61885` to `cCellGlobalsResource` (`knowledgegraph/research/gameplay-data-model.json:3921-3944`). The `0x00E4CE20` configuration/global-accessor naming correction is also retained: its exact accessor identity and namespace are unresolved, and the earlier `GetGlobalsData` name is not promoted (`knowledgegraph/research/gameplay-data-model.json:10287-10295`).

### Runtime, cache, and persistence schemas

`cCellDataReference_` is a runtime linkage/cache schema keyed by instance identity plus serializer context, with a resource pointer, serializer association, and use counter. It is not a save record (`knowledgegraph/research/gameplay-data-model.json:9580-9707`). `cCellGame` owns the 4096-entry pool, foreground/background query state, world references, avatar index, timing, and the separately held serializable-state pointer; `cCellObjectData` carries live transform, health, behavior, query, and GFX associations (`knowledgegraph/research/gameplay-data-model.json:5920-6085`).

`cCellSerializableData` is the explicit Cell save-state candidate and contains player creature identity, food progression, spent evolution points, unlocked parts, counters, game identity/difficulty, missions, tutorial/nanite flags, and telemetry fields. The interface proves eligibility, not complete field emission or round-trip behavior (`knowledgegraph/research/gameplay-data-model.json:6087-6239`).

`PropertyList` has local-first lookup, parent fallback, an operation counter, and explicit `Read`/`Write` surfaces. The `Property` memory layout remains unresolved under `C002`: SDK-derived evidence gives 20 bytes while imported evidence gives 4 bytes, so the authoritative runtime and wire representation, exact bytes, parent encoding, and round-trip behavior are not established (`knowledgegraph/research/gameplay-data-model.json:11180-11201`, `knowledgegraph/research/gameplay-data-model.json:12921-12936`). `ClassSerializer` exposes a 128-slot attribute architecture, object ID/current-object state, binary/text callbacks, and `ISimulatorSerializable` relationships; concrete bodies, attribute vocabulary, pointer remapping, and rollback are unresolved (`knowledgegraph/research/gameplay-data-model.json:11224-11288`).

Analytical projections such as `N-PROGRESSION-DATA`, `N-ECONOMY-DATA`, `N-EMPIRE-DATA`, `N-MISSION-DATA`, `N-PLANET-DATA`, `N-SPACE-DATA`, and `N-PRESENTATION-DATA` are not asserted to be literal original types. Their stable node IDs describe semantic boundaries and mode/domain ownership (`knowledgegraph/research/gameplay-data-model.json:8668-8780`, `knowledgegraph/research/gameplay-data-model.json:9437-9531`, `knowledgegraph/research/gameplay-data-model.json:8524-8666`).

## Asset and data relationships

The twelve major relationships are the canonical high-level relations. “Supported” or “confirmed” here is bounded static evidence; it is not a runtime observation.

| ID | Relationship | Status and qualification |
|---|---|---|
| `R001` | DBPF index row → bounded record bytes | `VERIFIED`; a complete type/group/instance selection yields raw or QFS-decompressed payload. Original package precedence and write integration are separate. |
| `R002` | `cCellDataReference_` → `cCellResource` and direct Cell records | `CONFIRMED`; serializer-associated references lazily resolve bytes interpreted by TypeID-specific Cell schemas; ownership linkage is not the content wire schema. |
| `R003` | CellWorld/CellPopulate → definitions, models, population metadata, GFX preload | `SUPPORTED`; procedural placement and exact runtime selection remain inferred. |
| `R004` | Cell definition → structure, loot, random creature, AI, look, interaction | `VERIFIED`; this is gameplay content, not texture state. |
| `R005` | GMDL/RW4 record → model, mesh, material, raster presentation | `SUPPORTED`; current host meshes/textures are not the full original RenderWare object graph or material execution. |
| `R006` | `cCellGame` → `cObjectPool`, `CellQuery`, GFX association, live entity state | `CONFIRMED`; `cCellObjectData` is the live record shape, while current `CellSim` and `CellGame` remain parallel bounded projections until integration is evidenced. |
| `R007` | `cCreatureGameData` → Cell serializable progression | `SUPPORTED`; creature evolution/brain/ability domain and Cell food/unlocked-part/mission state are related but separate records; `C014` leaves field typing unresolved and synchronization is also unresolved. |
| `R008` | `cGameData`/`ISimulatorSerializable` → noun, building, space-world, editor object graphs | `SUPPORTED`; static prefixes, interfaces, intrusive ownership, and noun management support a broad family, but no RTTI and incomplete factories prevent an exact universal hierarchy. |
| `R009` | `cStarManager`/`cStarRecord` → planet, colony, terrain, Space context | `SUPPORTED`; generation, surface transition, terrain execution, and persistence order remain inferred. |
| `R010` | `cCity`/`cCommunityLayout` → building, layout, effectiveness, owner state | `SUPPORTED`; placement, cost, connectivity, political ownership, and destruction transactions remain incomplete. |
| `R011` | `IMessageManager` and subsystem owners → mode, editor, communication, animation, UI consumers | `SUPPORTED`; message IDs, listener entries, queues, and domain events are related but have distinct ownership/ordering; no universal event ABI is proven. |
| `R012` | persistence manager/`PropertyList`/`ClassSerializer`/serializable records → save/load restoration | `SUPPORTED`; transaction, `PROP`/`SPO` framing, remapping, migration, and cross-stage survival are not recovered. |

The exact statements, evidence levels, and source artifacts are at `knowledgegraph/research/gameplay-data-model.json:19-445`. The normalized graph deliberately corrects several directions: `E-007` is `N-CELL-WORLD-DATA` → `N-CELL-CONTENT`; `E-030` is `N-CONFIGURATION-DATA` → `N-PROPERTY-LIST`; and `E-047` is `N-SAVE-DATA` → `N-OBJECT-REGISTRY` for the bounded `reconstructs` relation while pointer restoration remains unresolved. The same normalization makes `N-CELL-RUNTIME-STATE` the canonical gameplay node, separates presentation from gameplay, distinguishes model-reference resolution from derived-skin production, and distinguishes enqueue from dispatch (`knowledgegraph/research/gameplay-data-model.json:621-636`, `knowledgegraph/research/gameplay-data-model.json:1037-1057`, `knowledgegraph/research/gameplay-data-model.json:1346-1361`, `knowledgegraph/research/gameplay-data-model.json:1403-1473`).

The graph’s high-centrality nodes, in numeric rank order 1-10 over the 48 source edges, are `N-PRESENTATION-DATA` (10 total degree), `N-CELL-RUNTIME-STATE` (6), `N-ASSET-REGISTRY` (5), `N-GAME-MODE-LIFECYCLE` (5), `N-SPACE-DATA` (5), `N-CELL-CONTENT` (4), `N-CREATURE-RIGBLOCK` (4), `N-EVENT-DATA` (4), `N-SAVE-DATA` (4), and `N-CONFIGURATION-DATA` (3) (`knowledgegraph/research/gameplay-data-model.json:4642-4722`). These are structural graph centrality values, not original ownership guarantees.

## Lookup → runtime → gameplay flows

### Asset-to-gameplay path

The canonical flow `F-ASSET-LOOKUP-RUNTIME-GAMEPLAY-EVENT` is `qualified_not_runtime_validated` and explicitly retains unresolved claim `U-003-TRANSPORT` (`knowledgegraph/research/gameplay-data-model.json:1403-1473`). Its bounded sequence is:

1. **Asset:** select the complete type/group/instance record and bounded payload bytes. This stage is `VERIFIED`.
2. **Lookup:** resolve database, factory, typed reference, and cache state. This stage is `SUPPORTED`; original precedence is unresolved.
3. **Runtime:** materialize a bounded resource, Cell state, or host value. This stage is `SUPPORTED`.
4. **Gameplay:** use `N-CELL-RUNTIME-STATE` as the canonical runtime gameplay node. This stage is `SUPPORTED`; active update order is unresolved.
5. **Event:** emit or enqueue a subsystem-specific event/message consequence. This stage is `INFERRED`; transport ABI, payload ownership, priority, and timing are unresolved.

This is a structural flow, not a runtime trace. The original process has no positive gameplay trace in the input set (`knowledgegraph/research/gameplay-data-model.json:4553-4565`).

### Content-to-live-Cell path

`F-CELL-CONTENT-TO-EVENT` is `partial`. It decodes world/populate/Cell/structure/effect references, creates or queries pooled Cell state, applies movement/combat/eat/animation/interaction transitions, and routes bounded presentation/event consequences. The original event transport remains unresolved (`knowledgegraph/research/gameplay-data-model.json:1531-1596`). In particular, `cCellPopulateResource` marker rows do not establish live x/y coordinates, and `cCellWorldResource` execution/selection is not recovered (`knowledgegraph/research/gameplay-data-model.json:3011-3173`).

### Canonical flow inventory

The source graph's 10 flows are retained. The canonical normalized graph adds `F-ASSET-LOOKUP-RUNTIME-GAMEPLAY-EVENT` as one qualified derived flow over the connected edge path; it does not become a single source-graph flow or a runtime-validation claim (`knowledgegraph/research/gameplay-data-model.json:1403-1473`, `knowledgegraph/research/gameplay-data-model.json:12066-12070`).

| Flow | Bounded path | Status |
|---|---|---|
| `F-ASSET-LOOKUP-RUNTIME-GAMEPLAY-EVENT` | Asset record → registry/key → typed cache → Cell runtime → event consequence | `qualified_not_runtime_validated`; `U-003-TRANSPORT` remains open. |
| `F-ASSET-TO-PRESENTATION` | TGI identity → database/factory/cache → typed object → model/material/texture/world binding | `partial`; exact original load order is inferred where noted. |
| `F-CELL-CONTENT-TO-EVENT` | Cell templates → live entities → gameplay transition → presentation/event surface | `partial`; event transport unresolved. |
| `F-CITY-LIFECYCLE` | Noun materialization → city/layout slot → processing/owner state → removal | `partial_event_consequence_unresolved`; costs, rollback, and full destruction order unknown. |
| `F-CONFIGURATION-TO-RUNTIME` | Config/options/properties → current configuration state → bounded consumers → named save/reset | `partial`; defaults and migration are not inferred where absent. |
| `F-CREATURE-AUTHORING-TO-PRESENTATION` | Creature data/rigblocks → editor session/history → derived skin → editor presentation | `partial`; authored asset save remains a separate boundary. |
| `F-EVENT-TO-MODE-STATE` | Event/listener request → queue/ID/priority semantics → dispatch → owned mode/UI/pose/effect state | `partial_event_consumer_edges_unresolved`; event/message variants remain distinct. |
| `F-MODE-TRANSITION` | Active mode A → `SetActiveModeAt`/messages → mode B initialization → handoff decision | `partial_editor_handoff_unresolved`; reset/serialize/rehydrate is unknown. |
| `F-PLANET-TO-SURFACE` | Generated planet record → planet/terrain transition → terrain mutation → render passes | `partial_direct_surface_edge_added_but_runtime_transition_unresolved`; no original transition trace. |
| `F-PROGRESSION-SETTLEMENT` | Live progression → serializable candidate → serializer/PropertyList/persistence service → rehydration | `partial`; exact handoff and synchronization unresolved. |
| `F-SPACE-GALAXY-TO-EVENT` | Star/planet records → empire/ownership → relationship/mission/economy → communication event | `partial`; generation and event order are static/inferred, not runtime-observed. |

The flows and their individual stage evidence are defined at `knowledgegraph/research/gameplay-data-model.json:1403-2047`; the same canonical flow inventory is repeated in the normalized graph at `knowledgegraph/research/gameplay-data-model.json:4724-5369`.

## Central structures and functions

The addresses below are the original addresses or SDK/vtable anchors retained by the canonical dossier. `null`, `UNKNOWN`, or a vtable-only description is preserved rather than replaced with a guessed address.

### Resource, package, and typed-reference seams

| Structure/function | Address | Bounded operation |
|---|---:|---|
| `cResourceManager::Initialize` | `0x008DE530` | Bring up manager registry/index structures. |
| `RegisterDatabase` / `RegisterFactory` | `0x008E0D30` / `0x008E1D20` | Register packed/directory sources and type-specific factories. |
| `FindRecord` / `FindFactory` | `0x008DF9B0` / `0x008DFB20` | Resolve record/factory state for a resource query; exact precedence is inferred. |
| `cResourceManager::GetResource` / `FindRecord` | `0x008DF700` / `0x008DFC80` | Original named resource/record lookup surfaces; exact precedence is not runtime-observed. |
| `cResourceManager::SetKeyName` | `0x008E1750` | Associate a name with a resource identity and refresh mappings. |
| `cResourceManager` shared load body | `0x008DF0B0` | Use existing lookup or dispatch factory/read/create and cache/release paths. |
| `cResourceManager::CacheResource` / `ReloadResource` | `0x008DE3B0` / `0x008DF7A0` | Retain or reload a typed resource; exact eviction/order is unresolved. |
| `GetLoadedResource` / `FindCache` | `0x008DE280` / `0x008DE360` | Query loaded/cache state. |
| `cCellDataReference_::Create` | `0x00E82420` | Find or create a typed reference keyed by instance and serializer. |
| `FUN_00e823a0` | `0x00E823A0` | Increment use count and lazily resolve resource data on null. |
| `FUN_00e822c0` / `FUN_00e82130` | `0x00E822C0` / `0x00E82130` | Release/reload cached payload and decrement use count. |
| `FUN_00e82280` / `FUN_00e824d0` | `0x00E82280` / `0x00E824D0` | Clear cached payloads and tear down the reference registry. |

These are recorded in `knowledgegraph/research/gameplay-data-model.json:5490-5707` and `knowledgegraph/research/gameplay-data-model.json:9140-9707`. The unresolved distinction between `0x00E82340` and SDK-associated `0x00E82420` is preserved; they are not collapsed into one exact body (`knowledgegraph/research/gameplay-data-model.json:4291-4309`).

### Cell runtime and presentation

| Structure/function | Address | Bounded operation |
|---|---:|---|
| `cCellModeStrategy::Initialize` / `cCellGame::Initialize` | `0x00E81CF0` / `0x00E80BA0` | Initialize mode state, pool, queries, timing, world references, and serializable pointer. |
| `FindCellsInRadius` / `CellQuery` linked pool | `0x00E87210` | Find nearby candidates using position, size, links, and pool indices. |
| `MovePlayerToMousePosition` / `PlayAnimation` / combat and eat paths | `0x00E5B790` / `0x00E6D200` | Mutate movement, animation, target, health, query, and gameplay state. |
| Cell pool lifecycle / mode dispose | `0x00E780A0` / `0x00E81F30` | Release/rebuild pooled objects and mode-owned state. |
| `cCellGFX::Initialize` | `0x00E5DBA0` | Create Cell world/layer/lighting/model/effect presentation state. |
| `cCellGFX::PreloadResources` / `PreloadCellResource` / `PreloadPopulateResource` | `0x00E666F0` / `0x00E663B0` / `0x00E665C0` | Recursively preload models, textures, effects, creatures, and populate dependencies. |
| `LoadEffectMap` / `InstanceEffectOnCell` / `PlayAnimation` / `StartDisplay` | `0x00E63560` / `0x00E66840` / `0x00E6D200` / `0x00E55120` | Configure effects, bind them to Cell transforms, change animation, and activate display. |
| `GetCurrentAdvectInfo` / `GetNextAdvectID` / `cellWorldIssues` | `0x00E58EF0` / `0x00E58E30` | Select scale-banded advect rows and validate world spans/references. |
| `cCellModeStrategy::OnExit` / `Dispose` | `0x00E7FC00` / `0x00E81F30` | Restore display/global state and release CellGame/GFX/UI state. |

The runtime structure and function evidence is in `knowledgegraph/research/gameplay-data-model.json:5770-6085` and `knowledgegraph/research/gameplay-data-model.json:6270-6335`. `N-CELL-RUNTIME-STATE` is the canonical gameplay node; the original active service/AI/graphics/effect order is explicitly unresolved.

### Editor, object, and cross-mode ownership

| Structure/function | Address | Bounded operation |
|---|---:|---|
| `cEditor::Initialize` / `SetEditorModel` / `AddCreature` | `0x00584300` / `0x00586B00` / `0x00582FE0` | Initialize editor services and install/build authored or runtime model state. |
| `cEditor` input/history/mode callbacks | `0x00588570` / `0x00586410` / `0x00587270` | Mutate parts/colors, history, selection, pose, and editor mode state. |
| `cEditorAnimWorld::GetCreatureController` / `EditorRequest::Submit` | `0x0059CAC0` / `0x005A92C0` | Query controller state or submit an external editor request. |
| `Editor_Save` / `EditorModel::Save` / `cCreatureDataResource::Write` | `0x00577650` / `0x004AF780` / `0x004BFCB0` | Asset-save boundary, distinct from profile/save-slot persistence. |
| `cGameNounManager::CreateInstance` | `0x00B20BF0` | SDK-associated creation surface for registered game-data subtypes; exact body unresolved. |
| `cGameNounManager::DestroyInstance` | `0x00B22560` | Remove/release a noun/game-data instance; exact body boundary unresolved. |
| `cGameNounManager::GetData` / `Get` | `0x00B212D0` / `0x00B3D400` | Noun registry/data access and materialization surface. |
| `RegisterNounType` / `cGameNounManager::CreateInstance` | `0x00B23E40` / `0x00B20BF0` | Register subtype/factory and materialize game-data instance. |
| `SetGameDataOwner` / `SetPoliticalID` | no single address retained | Named owner/political registry mutation paths; exact boundaries incomplete. |
| `SetActiveModeAt` / mode callbacks | `0x007D8D40` / callbacks | Exit mode A, activate mode B, and release/restore mode state. |

These anchors and their limitations are recorded at `knowledgegraph/research/gameplay-data-model.json:6668-7422`, `knowledgegraph/research/gameplay-data-model.json:8216-8376`, and `knowledgegraph/research/gameplay-data-model.json:7725-7873`. The noun/object family is a semantic adapter boundary; it is not a universal original ABI and does not own the mode-specific Cell pool.

### Planet, Space, economy, event, and persistence seams

| Structure/function | Address | Bounded operation |
|---|---:|---|
| `cPlanetRecord::Create` / planet generation routine | `0x00BA6300` / `0x00BB4100` | Create/generate planet records from star/system inputs; formulas incomplete. |
| `RecordToPlanet` / `GetGeneratedTerrainKey` / ownership routines | `0x00BB5B50` / `0x00B8DA30` / `0x00C8D060` | Bind record/runtime state, terrain identity, and ownership transitions. |
| `GetPlanetRecords` / `RecordToPlanet` / active-planet access | `0x00BBA900` / `0x00BB5B50` / `0x01021110` | Resolve planet records and live association. |
| Star/planet database persistence | `0x00BB4BA0` | Bounded write/replace path; record coverage and transaction order unresolved. |
| `cStarManager` / `cSimulatorSpaceGame` session setup | `0x00B3D3A0` / `0x010027B0` | Own star databases, empires, trade routes, active context, inventory, missions, and player-UFO state. |
| `GetPlanetRecords` / `RecordToPlanet` / `SpacePlayerData` accessors | `0x00BBA900` / `0x00BB5B50` / `0x01021260` / `0x01021080` | Resolve records, active planet, and Space context. |
| Relationship transition routines | `0x00D065A0` / `0x00D06920` | Apply relationship status/delta transitions and expose communication consequences. |
| `cCommManager` event creator / space event-record builder | `0x00AEB160` / `0x00E39AB0` | Create communication/space event payloads; numeric action meanings unresolved. |
| `ShowCommEvent` / message queue / deferred-event surfaces | `0x00AEBE10` / `0x008854A0` / `0x00885980` | Advance communication/message state or enqueue events; exact ownership/order unresolved. |
| `cMessageManager` registration / `MessagePost` | `0x00883A90 family` / `0x00885980` | Register listeners/handlers or post a refcounted message payload. |
| `MessageSend` / `ProcessQueue` / `ProcessQueue2` | `0x008854A0` / `0x008841F0` / `0x00884700` | Route payloads, process queues, dispatch handlers, and release references. |
| `cGamePersistenceManager::Get` | `0x00B3D440` | Get persistence service; not a concrete save/load sequence. |
| `App::PropertyList::GetProperty` | `0x006A2530` | Search local properties and fall back to the parent list. |
| `App::PropertyList::SetProperty` | `0x006A2E20` | Insert/update a local property and increment the operation counter. |
| `App::PropertyList::Read` / `Write` | `0x006A2F60` / `0x006A1540` | Read/write property framing and typed entries through streams. |
| `ClassSerializer::Write` / `Read` | SDK anchors `0x006928C0` / `0x00693DE0`; containing entries `0x00692880` / `0x00693DD0` | Class/object attribute write/read architecture; address/body contradiction and field order remain unresolved. |
| `cGameData::Write` / `Read` | SDK anchors `0x00B184D0` / `0x00B18540` | Serializable game-data write/read surface; field bodies unresolved. |
| `cStarManager` `stars.db.tmp` replacement | `0x00BB4BA0` | Narrow static evidence for temporary database output and replacement of `stars.db`; not a general save transaction. |

The relevant function entries are in `knowledgegraph/research/gameplay-data-model.json:8379-9570`, `knowledgegraph/research/gameplay-data-model.json:12759-14119`, and the persistence table at `knowledgegraph/research/gameplay-data-model.json:9272-9422`. The complete 18-entry save/load inventory is canonical at `knowledgegraph/research/gameplay-data-model.json:13763-14119`.

## Persistent versus transient state

The following table condenses the canonical `DC001`–`DC057` classification while retaining the stable IDs and the important boundary. Full source references are at `knowledgegraph/research/gameplay-data-model.json:10637-11899`.

| Canonical IDs | Classification | Structures and state | Persistence conclusion |
|---|---|---|---|
| `DC001` | Static asset/template | DBPF v3 package/index/record payload | Persistent on-disk content substrate, not profile/save state. |
| `DC002` | Static asset/template | GMDL v8 record | Packaged model/material/texture/animation-boundary content; current parser is one-way. |
| `DC003` | Static asset/template | RW4 container | Static RenderWare section directory; payload execution and writer unresolved. |
| `DC004` | Static asset/template | Raster record plus derived `Graphics::Texture`/`Raster` | DBPF raster is static; wrapper pointers/device state are runtime-only. |
| `DC005` | Static asset/template | `0x0F43029A` WorldObject/model-part record | Model-group/part-definition content, not recovered Cell scene placement. |
| `DC006` | Static asset/template | `cCellGlobalsResource` | 276-byte, 69-field direct content record; distinct from `cCellSerializableData`. |
| `DC007` | Static asset/template | `cCellEffectMapResource` | 8-byte header plus 28-byte effect rows; not save state. |
| `DC008` | Static asset/template | `cCellStructureResource` | 28-byte header plus 40-byte attachment rows; instance-like content references. |
| `DC009` | Static asset/template | `cCellBackgroundMapResource` | 8-byte header plus 16-byte background rows; presentation/content input. |
| `DC010` | Static asset/template | `cCellPowersResource` | Fixed 8-byte teleport-cost/range record, not a serializer envelope or save record. |
| `DC011` | Static asset/template | `cCellLookTableResource` | 8-byte header plus 8-byte look rows. |
| `DC012` | Static asset/template | `cCellWorldResource` | 16-byte header plus 12-byte level rows and 24-byte advect rows; static content, not live `cCellGame`. |
| `DC013` | Static asset/template | `cCellLootTableResource` | 36-byte header plus 28-byte reward rows; not inventory/profile state. |
| `DC014` | Static asset/template | `cCellPopulateResource` | 16-byte header plus 76-byte markers; procedural x/y and live actors are not stored in the recovered marker. |
| `DC015` | Static asset/template | `cCellLookAlgorithmResource` | 8-byte header plus 20-byte role/reference rows. |
| `DC016` | Static asset/template | `cCellCellResource` | Fixed 796-byte Cell definition, not `cCellSerializableData` or a live Cell object. |
| `DC017` | Static asset/template | `cCellRandomCreatureResource` | 8-byte header plus 28-byte spawn candidates, not a runtime entity pool. |
| `DC018` | Runtime transient | `cCellResource` wrapper and `cCellDataReference_` | Instance identity is content identity; serializer pointer, loaded resource pointer, and use counter are runtime linkage. |
| `DC019` | Runtime transient | `cCellGame` and `cObjectPool<cCellObjectData>` | Live pool/query/display state resets/releases; only the separately held `cCellSerializableData` is a persistence candidate. |
| `DC020` | Runtime transient | `cCellObjectData` and `cCellQueryEntry` | Live transform, model/GFX, health, animation, and spatial query; no individual live-object save path established. |
| `DC021` | Profile/save persistent | `cCellSerializableData` | Explicit serializable Cell state holder, 236 bytes in the static layout, held by `cCellGame` at `+0x5190`; field emission, order, defaults, and round trip unknown. |
| `DC022` | Profile/save persistent | `cSavedGameHeader` | Major/minor version, object counts, timestamp, game mode, snapshot flag, and current planet key; placement/field emission not runtime-verified. |
| `DC023` | Profile/save persistent | `GameLoadParameters` | Load context for game/star names, creature/profile identity, star, difficulty, and mode; exact consumption body unknown. |
| `DC024` | Runtime transient | `cGamePersistenceManager` | Runtime message-aware service and `LoadGame` surface; concrete orchestration/transaction unresolved. |
| `DC025` | Unknown/mixed | `PropertyList` | Local property map, parent overlay, operation counter, and explicit stream boundary; whole-object persistence is not proven. |
| `DC026` | Unknown | `Property` | Typed value carrier; `C002` keeps the SDK 20-byte and imported 4-byte layouts open, with no authoritative runtime or wire representation. |
| `DC027` | Runtime transient | `DirectPropertyList` | Fast-access and temporary property state; no separate file format established. |
| `DC028` | Runtime transient | `ClassSerializer` | Runtime serializer authority with 128 attribute slots, object ID/current object, and callback storage; mediates persistence without being a profile field. |
| `DC029` | Runtime transient | `Attribute` | Serializer metadata descriptor, not a profile field. |
| `DC030` | Unknown | `ISimulatorSerializable` contract | Proves `Write`, `Read`, `WriteToXML`, and noun/object identity slots; does not prove complete subtype field coverage. |
| `DC031` | Profile/save persistent | `cGameData` and derived live objects | Serializable identity, owner, political ID, and subtype state; field-by-field emission and pointer restoration unresolved. |
| `DC032` | Unknown | `cCreatureGameData` | Creature brain/evolution/ability/positioning domain; `C014` leaves field typing unresolved, and no direct disk serializer or cross-stage synchronization with Cell state is established. |
| `DC033` | Profile/save persistent | `cCollectableItems` | Serializable unlock registry, status map, unlock points, and unlocked item list; exact emitted set/order unknown. |
| `DC034` | Profile/save persistent | `cStarRecord` | Serializable star position/version/timestamp/ownership/species and owned planet records; database ordering unknown. |
| `DC035` | Runtime transient | `cStarManager` | Runtime manager owning star grids, saved/starter records, empire homes, collectables, trade routes, and temporary/main databases. |
| `DC036` | Profile/save persistent | `cEmpire` | Serializable political identity, home world, relationships, money, culture, assets, and adventure state; exact field set unresolved. |
| `DC037` | Profile/save persistent | `cMission`, `cMissionManager` | Serializable mission state, rewards/costs/unlocks, tracking, recent lists, and configuration PropertyLists; payout/callback order unresolved. |
| `DC038` | Profile/save persistent | `cSpaceInventoryItem`, `cPlayerInventory` | Serializable item/tool/cargo identity, counts, costs, and inventory ownership candidates; transaction order unresolved. |
| `DC039` | Profile/save persistent | `PlayerPlanetData` | Write/Read object with scan maps, encountered political IDs, spice timer, explored/TScore fields, and `PlanetID`; framing and field coverage unknown. |
| `DC040` | Profile/save persistent | `cSpaceTradeRouteManager` | Serializable trade-route map owner; route value schema and stream order unresolved. |
| `DC041` | Unknown | `cPlanetRecord` | Generated/schema planet record owned by star/planet databases; no direct `ISimulatorSerializable` write/read surface established. |
| `DC042` | Profile/save persistent | `cSimulatorSpaceGame`, `cSolarSystem` | Serializable active Space composition/session roots; restoration and field coverage unknown. |
| `DC043` | Runtime transient | `cPlanet`, `cPlanetModel`, `cTerrainSphere`, surface runtime | Active planet, surface transition, terrain runtime, models, weather, and render state; current-planet header metadata does not prove survival. |
| `DC044` | Runtime transient | `TerrainModification`, planet editor dirty/model-footprint state | Live edit state; commit, dirty persistence, undo, and play-mode restore unknown. |
| `DC045` | Static asset/template | `cCreatureDataResource`, `cEditorResource`, `EditorModel`, `EditorRigblock`, `cEditorResourceBlock` | Authored asset candidates with read/write boundaries; common wire format unknown. |
| `DC046` | Runtime transient | `cEditor`, history/snapshots, editor resource-like history | Editor shell/history are in-memory; save-before-dispose and history survival not established. |
| `DC047` | Derived/cache | `cEditorSkin`, `cEditorSkinMesh`, host mesh/texture handles | Derived skin/model/material/texture production; no independent profile persistence established. |
| `DC048` | Runtime transient | `cEditorAnimWorld`, controller, animated creature, `cEditorAnimEvent` | Editor pose/animation/target/event state; survival across mode changes/restart unknown. |
| `DC049` | Runtime transient | `EditorRequest` | External request carrying editor ID, creation key, mode, policy flags, strings, and payload objects; not a saved document. |
| `DC050` | Derived/cache | `Resource::cResourceManager` cache/factory/name/type registry | Runtime cache and mappings over persistent package records; cache is not profile state. |
| `DC051` | Derived/cache | `MaterialShader`, `Material`, `CompiledState`, `TextureSlot`, renderer handles | Material/shader/texture binding and device objects; writer surfaces do not establish gameplay persistence. |
| `DC052` | Runtime transient | `cCity`, `cBuilding`, `cLayoutSlot`, noun instances | Live ownership, buildings, and placement slots; restoration/value-record synchronization unresolved. |
| `DC053` | Unknown | `cCityData`, `cBuildingData` | Value records resemble save counterparts, but serialization and live-object synchronization are not established. |
| `DC054` | Runtime transient | Standard, deferred, feedback, animation messages, anonymous space event pairs | Runtime dispatch payloads/queues; not evidence of a save record. |
| `DC055` | Profile/save persistent exception | `cCommEvent` | Serializable communication/mission event that is also queued runtime state; dispatch timing, field coverage, and restoration order unknown. |
| `DC056` | Profile/save persistent | `stars.db`, `stars.db.tmp` | Bounded temporary database output and replacement; not general atomic save/slot policy. |
| `DC057` | Derived/cache | Current OpenSpore parsed records, host meshes, scene fixtures, CellSim entities/events/state strings | Current in-process clean-room state only; not an original profile/save schema. |

### Supported survival claims

The canonical dossier supports only these bounded survival claims:

- A saved-game header architecture carries major/minor versions, object counts, timestamp, game mode, snapshot flag, and current planet key (`SC01`).
- `PropertyList` has explicit `Read`/`Write` stream operations dispatching entries by ID/type (`SC02`).
- `ClassSerializer`/`Attribute` and `ISimulatorSerializable` provide an object-level binary/text attribute architecture (`SC03`).
- `cCellSerializableData` is the explicit Cell runtime serializable state holder with progression, unlocked-part, counter, difficulty, mission, and telemetry fields (`SC04`).
- `cStarRecord` is a serializable record with saved-game version/timestamp fields and owned planet records (`SC05`).
- A narrow star/planet database path writes `stars.db.tmp` and replaces `stars.db` (`SC06`).
- The mode manager exits the current mode before entering the selected mode (`SC07`).
- Cell mode initialization creates fresh pools/world references/serializable-state path rather than loading that path in the same body (`SC08`).
- Direct Cell TypeIDs are static content layouts distinct from `cCellSerializableData` (`SC10`).
- `cGameData`, `cEmpire`, `cMission`, `cMissionManager`, `cCollectableItems`, `PlayerPlanetData`, `cSpaceTradeRouteManager`, and `cCommEvent` expose explicit serializable/Write/Read relationships (`SC11`).
- Resource caches, GFX preloads, material/shader lookups, editor skin, and host handles are derived/runtime state rather than independently established profile fields (`SC12`).

These claims and their qualifications are in `knowledgegraph/research/gameplay-data-model.json:14563-14684`.

### Unsupported survival claims

The following claims must not be promoted:

- Every `cCellSerializableData` field survives save/load (`UC01`).
- A direct Cell resource is a `CellSerializer` envelope or profile record (`UC02`).
- The exact `.prop` or `.spo` byte format is known (`UC03`).
- Saving is absent because no named `SaveGame` body was found (`UC04`).
- Mode exit/dispose autosaves state (`UC05`).
- State survives a mode transition by default (`UC06`).
- Editor history, selection, pose, animation world, or derived skin survives editor exit/dispose (`UC07`).
- `Editor_Save` writes a game profile or save slot (`UC08`).
- Live Cell/city/planet/terrain/renderer/cache objects are serialized wholesale (`UC09`).
- Creature and Cell evolution fields synchronize automatically across stages (`UC10`).
- A fixed slot count, single local profile, or account file is established (`UC11`).
- General save writes are atomic, crash-safe, checksummed, encrypted, or lock-protected (`UC12`).
- Version fields prove compatibility or migration (`UC13`).
- Object pointers are restored by direct address equality or raw pointer serialization (`UC14`).
- Current OpenSpore decoding, fixtures, state strings, scene JSON, or provider seam establish `.prop`/`.spo` compatibility (`UC15`).

The exact reasons and direct source locators are recorded in `knowledgegraph/research/gameplay-data-model.json:14685-14821`.

## OpenSpore semantic status

The OpenSpore comparison is intentionally not an equivalence score. “Represented” means the current implementation/test/fixture covers the named bounded behavior; it does not imply original runtime fidelity. “Partial” requires both a represented prefix and an explicit missing remainder. “Missing” blocks equivalence until a separately evidenced package exists. “Incorrect” quarantines a stale or overbroad claim. “Intentional modern divergence” is a valid current design choice but not an original semantic contract (`knowledgegraph/research/gameplay-data-model.json:10454-10503`).

### Represented: 10 items

- `REP-001` — DBPF v3/QFS record bytes: bounded 32-bit package parsing, raw extraction, compression, bounds checks, and TypeID/group/instance lookup (`knowledgegraph/research/gameplay-data-model.json:10506-10518`).
- `REP-002` — provider-neutral record-bytes seam: substitutable package/memory record fetch without claiming `cResourceManager` equivalence (`knowledgegraph/research/gameplay-data-model.json:10519-10530`).
- `REP-003` — direct Cell content schemas: typed decoding for globals, cells, worlds, random creatures, powers, loot, structures, markers, and related layouts within tested records (`knowledgegraph/research/gameplay-data-model.json:10531-10543`).
- `REP-004` — raster DXT5 slice: DXT5 decode, mip sizing, RGBA output, and exact record-size/layer checks for supported FourCC only (`knowledgegraph/research/gameplay-data-model.json:10544-10556`).
- `REP-005` — Cell advect selection: bounded table selection and fallback behavior as pure host functions (`knowledgegraph/research/gameplay-data-model.json:10557-10569`).
- `REP-006` — Cell combat and attack-gate functions: pure table-driven calculations, not entity mutation/health/animation/effect/event order (`knowledgegraph/research/gameplay-data-model.json:10570-10582`).
- `REP-007` — Cell object-pool structural contract: named fields, sentinel index, capacity, allocation, and reuse mechanics implemented in current source (`knowledgegraph/research/gameplay-data-model.json:10583-10595`).
- `REP-008` — deterministic CellSim movement/eat/flee host contract: fixed-step deterministic replayable behavior with explicit approximations and local events (`knowledgegraph/research/gameplay-data-model.json:10596-10609`).
- `REP-009` — single-package asset record lookup: record identity, type/group filters, exact lookup, and nearby-ID search over one parsed package (`knowledgegraph/research/gameplay-data-model.json:10610-10622`).
- `REP-010` — CellGame named initialization slice: named pool capacity, timing fields, world references, and background-bbox constants (`knowledgegraph/research/gameplay-data-model.json:10623-10634`).

### Partial: 10 items

- `PAR-001` — GMDL v8 static model: strict v8 prefix and texture identity, without top-level references, typed animation, or complete trailer semantics (`knowledgegraph/research/gameplay-data-model.json:10320-10334`).
- `PAR-002` — RW4 container directory: envelope, manifest, type table, section directory, BaseResource adjustment, and extents only; payloads remain opaque (`knowledgegraph/research/gameplay-data-model.json:10335-10348`).
- `PAR-003` — WorldObject model-part extraction: byte accounting, headers, names, and heuristic vectors, without byte-exact c-entry grammar (`knowledgegraph/research/gameplay-data-model.json:10349-10361`).
- `PAR-004` — Cell query and pool state: stable arena, LIFO links, and bounded query output, while current order/lifetime remain host projections (`knowledgegraph/research/gameplay-data-model.json:10362-10374`).
- `PAR-005` — Cell content-to-model graph: typed hard-reference validation and role/model candidates, not procedural x/y or live ownership (`knowledgegraph/research/gameplay-data-model.json:10375-10387`).
- `PAR-006` — Cell scene and presentation: declarative host scene with provenance labels and static textured drawing; positions/identity/layers/world selection/pixels are non-original (`knowledgegraph/research/gameplay-data-model.json:10388-10400`).
- `PAR-007` — Vulkan renderer: host flat/textured mesh path and ambient-plus-N-dot-L shader, excluding RenderWare/D3D9/original material/animation/pixel equivalence (`knowledgegraph/research/gameplay-data-model.json:10401-10414`).
- `PAR-008` — asset resolver naming/group heuristics: useful labels/filters with raw IDs retained; stage/category bytes are analytical conventions (`knowledgegraph/research/gameplay-data-model.json:10415-10427`).
- `PAR-009` — Python format inspection tools: analysis/oracle helpers with format-specific assumptions and capability beyond production C++ (`knowledgegraph/research/gameplay-data-model.json:10428-10440`).
- `PAR-010` — Cell mode/GFX lifecycle shell: bounded host lifecycle and presentation shell without complete original mode-manager behavior (`knowledgegraph/research/gameplay-data-model.json:10441-10452`).

### Missing: 20 items

- `MIS-001` — Original resource-manager orchestration: multi-package priority, database access, cache, directory, load continuation, and property-backed lookup behavior (`knowledgegraph/research/gameplay-data-model.json:10096-10107`).
- `MIS-002` — Original Cell active-update orchestration: service/AI/graphics/effect update graph absent from fixed-step `CellSim` (`knowledgegraph/research/gameplay-data-model.json:10108-10118`).
- `MIS-003` — Generic persistence manager: concrete write/read orchestration and transaction state (`knowledgegraph/research/gameplay-data-model.json:10119-10129`).
- `MIS-004` — `PropertyList` codec: compatible property serialization, inheritance, arrays, defaults, and migration (`knowledgegraph/research/gameplay-data-model.json:10130-10140`).
- `MIS-005` — Saved-game container and migration: archive framing, slots/profiles, checksum/encryption, atomicity, and version branches (`knowledgegraph/research/gameplay-data-model.json:10141-10151`).
- `MIS-006` — `ClassSerializer` and object-pointer restoration: concrete bodies, attribute vocabulary, object streams, and pointer tables (`knowledgegraph/research/gameplay-data-model.json:10152-10162`).
- `MIS-007` — `cCellSerializableData` codec: emitted fields, read paths, defaults, and cross-stage progression reconstruction (`knowledgegraph/research/gameplay-data-model.json:10163-10173`).
- `MIS-008` — GMDL v9/animation/deform variants: material framing, bones, animation, baked deform, and strict end offsets (`knowledgegraph/research/gameplay-data-model.json:10174-10185`).
- `MIS-009` — RW4 payload execution: mesh, material evaluation, skinning, animation, LOD, and texture-slot behavior (`knowledgegraph/research/gameplay-data-model.json:10186-10196`).
- `MIS-010` — WorldObject byte-exact grammar: c-entry field order, delimiters, vector meaning, ownership, and attachment semantics (`knowledgegraph/research/gameplay-data-model.json:10197-10207`).
- `MIS-011` — Original procedural Cell placement and player composition: exact scene reconstruction, player identity, layer order, and live world composition (`knowledgegraph/research/gameplay-data-model.json:10208-10218`).
- `MIS-012` — Original RenderWare materials/animation/pixels: original lighting, material, skinning, effect, UI, and pixel-equivalence claims (`knowledgegraph/research/gameplay-data-model.json:10219-10230`).
- `MIS-013` — Cross-mode noun/object ownership spine: safe generic entity registry, factory, destruction cascade, and stable owner graph (`knowledgegraph/research/gameplay-data-model.json:10231-10241`).
- `MIS-014` — City/building/layout behavior: placement eligibility, costs, adjacency, effectiveness, removal order, and rollback (`knowledgegraph/research/gameplay-data-model.json:10242-10252`).
- `MIS-015` — Original message/event dispatcher: deterministic event order, send/post timing, payload ownership, and event-to-state/presentation integration (`knowledgegraph/research/gameplay-data-model.json:10253-10263`).
- `MIS-016` — Progression/missions/inventory/economy transactions: unlock, reward, price, stock, and cross-stage handoff reconstruction (`knowledgegraph/research/gameplay-data-model.json:10264-10274`).
- `MIS-017` — Editor runtime and asset-save semantics: editor state persistence, tool behavior, document lifecycle, and event-to-animation integration (`knowledgegraph/research/gameplay-data-model.json:10275-10285`).
- `MIS-018` — Original configuration/global accessor contract: complete namespace, defaults, property import, gameplay-global access, and the true role of `0x00E4CE20` (`knowledgegraph/research/gameplay-data-model.json:10286-10296`).
- `MIS-019` — Creature/tribe/civilization/planet/space modes: cross-stage continuity, mode dispatch, and non-Cell behavior (`knowledgegraph/research/gameplay-data-model.json:10297-10307`).
- `MIS-020` — Original runtime/differential oracle: promotion of static constants, comments, fixtures, or decompilation-only differentials to observed runtime truth (`knowledgegraph/research/gameplay-data-model.json:10308-10318`).

### Incorrect: 20 quarantined claims

- `INC-001` — Provider equals original resource manager (`knowledgegraph/research/gameplay-data-model.json:3881-3900`).
- `INC-002` — Cell content records are save state (`knowledgegraph/research/gameplay-data-model.json:3901-3920`).
- `INC-003` — `cCellGlobalsResource` is Ghidra structure `61843` (`knowledgegraph/research/gameplay-data-model.json:3921-3945`).
- `INC-004` — C++ GMDL rejects any opaque trailer failure (`knowledgegraph/research/gameplay-data-model.json:3946-3975`).
- `INC-005` — `GmdlModel.consumed` proves exact input consumption (`knowledgegraph/research/gameplay-data-model.json:3976-4000`).
- `INC-006` — RW4 `complete` means all type codes are known (`knowledgegraph/research/gameplay-data-model.json:4001-4025`).
- `INC-007` — C++ and Python RW4 type maps are equivalent (`knowledgegraph/research/gameplay-data-model.json:4026-4045`).
- `INC-008` — Current C++ GMDL supports version 9 (`knowledgegraph/research/gameplay-data-model.json:4046-4065`).
- `INC-009` — WorldObject records are `CellSerializer` resources or placement data (`knowledgegraph/research/gameplay-data-model.json:4066-4090`).
- `INC-010` — `Entity.mIsIdle` is maintained as `!alive` (`knowledgegraph/research/gameplay-data-model.json:4091-4115`).
- `INC-011` — `CellSim growMeter` is evolution points or empire money (`knowledgegraph/research/gameplay-data-model.json:4116-4140`).
- `INC-012` — Generated Cell fixtures are an original oracle (`knowledgegraph/research/gameplay-data-model.json:4141-4165`).
- `INC-013` — Cell fixture contract version is `/1` (`knowledgegraph/research/gameplay-data-model.json:4166-4190`).
- `INC-014` — C++ and Python DBPF support the same variants (`knowledgegraph/research/gameplay-data-model.json:4191-4215`).
- `INC-015` — `CellSim` is the original Cell update loop (`knowledgegraph/research/gameplay-data-model.json:4216-4240`).
- `INC-016` — Vulkan lit output represents original rendering (`knowledgegraph/research/gameplay-data-model.json:4241-4265`).
- `INC-017` — Resolver names and stage/category bytes are canonical semantics (`knowledgegraph/research/gameplay-data-model.json:4266-4290`).
- `INC-018` — `0x00E82340` and `0x00E82420` are the same `cCellDataReference Create` body (`knowledgegraph/research/gameplay-data-model.json:4291-4310`).
- `INC-019` — SDK addresses inside current functions are exact semantic bodies (`knowledgegraph/research/gameplay-data-model.json:4311-4330`).
- `INC-020` — WorldObject Python vectors are byte-exact fields (`knowledgegraph/research/gameplay-data-model.json:4331-4355`).

### Intentional modern divergence: 12 items

- `DIV-001` — host value types/containers improve modularity and safety but do not reproduce original ABI/container layout (`knowledgegraph/research/gameplay-data-model.json:3605-3630`).
- `DIV-002` — stateless single-package provider keeps a deterministic fetch seam at the cost of original manager behavior (`knowledgegraph/research/gameplay-data-model.json:3631-3650`).
- `DIV-003` — DBPF variant support differs between C++ and Python tools (`knowledgegraph/research/gameplay-data-model.json:3651-3670`).
- `DIV-004` — GMDL version support differs between C++ and Python (`knowledgegraph/research/gameplay-data-model.json:3671-3690`).
- `DIV-005` — opaque GMDL trailer acceptance permits bounded static loading while giving up strict trailer completeness (`knowledgegraph/research/gameplay-data-model.json:3691-3710`).
- `DIV-006` — fixed-step role-string `CellSim` enables deterministic fixtures with approximate speeds/radii/event ordering (`knowledgegraph/research/gameplay-data-model.json:3711-3735`).
- `DIV-007` — generated deterministic fixtures pin current determinism but do not establish original truth (`knowledgegraph/research/gameplay-data-model.json:3736-3760`).
- `DIV-008` — modern Vulkan/GLSL renderer provides a portable host backend while omitting original material/animation semantics (`knowledgegraph/research/gameplay-data-model.json:3761-3785`).
- `DIV-009` — vector-backed Cell query improves deterministic host implementation but does not prove original insertion/removal order or arena ownership (`knowledgegraph/research/gameplay-data-model.json:3786-3810`).
- `DIV-010` — resolver fallbacks and near-record heuristics prioritize inspectability over strict rejection (`knowledgegraph/research/gameplay-data-model.json:3811-3835`).
- `DIV-011` — WorldObject semantic extraction provides byte accounting and inspectability without claiming a typed loader or field order (`knowledgegraph/research/gameplay-data-model.json:3836-3855`).
- `DIV-012` — content pointer slots are kept separate from host addresses, preventing host pointers from contaminating content serialization (`knowledgegraph/research/gameplay-data-model.json:3856-3880`).

## Corrected assumptions

The following corrections are part of the model, not optional interpretation:

1. `cResourceManager` is not replaced by the current one-package provider seam. The provider is `REP-002`; original manager orchestration is `MIS-001` (`INC-001`).
2. Direct Cell content is not saved state. `cCellCellResource` and the other twelve direct layouts are templates; `cCellSerializableData` is a separate save candidate (`INC-002`).
3. `cCellGlobalsResource` is not Ghidra structure `61843`; the canonical correction is `61843 = cCellSerializableData` and `61885 = cCellGlobalsResource` (`INC-003`).
4. GMDL strictness and `consumed` are bounded current-parser facts, not proof of strict original trailer completeness or exact input consumption (`INC-004`, `INC-005`).
5. RW4 `complete` proves implemented directory invariants, not semantic coverage of every type code. C++ and Python type maps are separate registries until reconciled (`INC-006`, `INC-007`).
6. Python GMDL version-9 handling is analysis-only; current C++ supports the bounded v8 path (`INC-008`).
7. WorldObject records are model-group/part metadata, not `CellSerializer`, `cGameData`, or scene-placement records. Python vectors remain heuristic candidates rather than byte-exact fields (`INC-009`, `INC-020`).
8. `Entity.mIsIdle` is not a maintained inverse of `alive`; current updates gate on `alive` and do not synchronize that field (`INC-010`).
9. `growMeter` is a local deterministic CellSim integer; it is not automatically evolution points or empire money (`INC-011`).
10. Generated Cell fixtures are current regression evidence, not an original oracle. The generated fixture declares `cell-sim-contract/2` while the README retains conflicting `/1` text (`INC-012`, `INC-013`).
11. C++ DBPF and Python DBPF capabilities differ; tool acceptance cannot be transferred to production C++ (`INC-014`).
12. `CellSim` is a deterministic host approximation, not the original service/AI/graphics/effects update loop (`INC-015`).
13. Vulkan lit output is a modern renderer abstraction, not original RenderWare/D3D9 material, lighting, animation, or pixel equivalence (`INC-016`).
14. Resolver labels and group-byte stage/category conventions are fallbacks; raw TypeID/group/instance identity remains authoritative (`INC-017`).
15. `0x00E82340` and `0x00E82420` remain separate anchors until the body identity is resolved (`INC-018`).
16. SDK labels/addresses identify architectural interfaces or anchors; they do not automatically identify the exact mechanics of the containing body (`INC-019`).
17. The `0x00E4CE20` global-accessor label must not be promoted to `GetGlobalsData`; its exact namespace/accessor semantics remain a research gate (`MIS-018`, `RQ-014`).

The complete assumptions, replacement effect, and direct references are retained in `knowledgegraph/research/gameplay-data-model.json:3605-4354`. No code or historical artifact was changed to implement these corrections.

## Semantic gaps

The highest-impact semantic gaps are not merely “unknown fields.” They are missing ownership and execution edges:

- `GAP-CELL-ACTIVE-UPDATE`: original state-gated service, AI, movement, graphics, and effect update order is missing (`knowledgegraph/research/gameplay-data-model.json:12761-12776`).
- `GAP-NON-CELL-MODES`: creature, editor, planet, Space, civilization, and cross-mode runtime behavior is missing (`knowledgegraph/research/gameplay-data-model.json:12777-12792`).
- `GAP-ORIGINAL-ORACLE`: no approved original-process runtime or save/load oracle is established (`knowledgegraph/research/gameplay-data-model.json:12793-12808`).
- `GAP-RESOURCE-MANAGER`: original multi-package priority, asynchronous load continuation, cache lifetime, and release rules are missing (`knowledgegraph/research/gameplay-data-model.json:12809-12824`).
- `MR-001`/`MR-002`: the asset-to-gameplay-to-event path is connected structurally and receives one qualified derived flow, but gameplay-to-event transport remains qualified by `U-003-TRANSPORT` and is not runtime complete (`knowledgegraph/research/gameplay-data-model.json:12825-12856`).
- `MR-003`: `E-021` and `E-052` now connect generated `PlanetData` to the live surface and then presentation; the runtime transition contract, terrain codec, and execution boundary remain unresolved (`knowledgegraph/research/gameplay-data-model.json:12857-12871`).
- `MR-004`: city lifecycle is mapped, but city removal/event consequences are not present in the selected flow (`knowledgegraph/research/gameplay-data-model.json:12873-12888`).
- `MR-005`: mode transition does not establish editor-state handoff (`knowledgegraph/research/gameplay-data-model.json:12889-12904`).
- `MR-006`: event routing does not establish direct editor/presentation consumer edges (`knowledgegraph/research/gameplay-data-model.json:12905-12919`).
- `C002`: the `Property` memory-layout contradiction remains open; no exact layout, parent encoding, or round-trip behavior is inferred (`knowledgegraph/research/gameplay-data-model.json:12921-12936`).
- `C014`: `cCreatureGameData` field typing remains unresolved; field meaning, write/read coverage, and cross-stage synchronization are not inferred (`knowledgegraph/research/gameplay-data-model.json:12937-12952`).
- `PKG-11-PERSISTENCE`: complete save/load codec, transaction, migration, pointer restoration, and profile/slot contract is missing (`knowledgegraph/research/gameplay-data-model.json:12953-12967`).
- `SEM-001` through `SEM-015` remain open semantic-gap placeholders. The concrete questions and evidence gates that operationalize those gaps are listed below (`knowledgegraph/research/gameplay-data-model.json:12969-13118`).

## Highest-value remaining questions

These are the canonical prioritized questions, in canonical order:

| Priority | ID | Question | Blocking gap |
|---:|---|---|---|
| 1 | `RQ-001` | What are the exact original multi-package priority, cache, directory, and record-release rules? | Resource identity and load-order reconstruction. |
| 2 | `RQ-002` | How does `cCellDataReference` select a record, load it lazily, and release or invalidate cached state? | Cell content loading and runtime ownership. |
| 3 | `RQ-003` | What state gates and service/AI/graphics/effect order does the original Cell update orchestrator use? | Live-state, event, and presentation differential comparison. |
| 4 | `RQ-004` | What are the exact GMDL v8/v9 material, bone, animation, deform, and resource-key framings? | Complete model dependencies and animation metadata. |
| 5 | `RQ-005` | Which RW4 section type codes and payload layouts are authoritative for mesh, material, skeleton, skin, animation, and blend shapes? | RenderWare object and material reconstruction. |
| 6 | `RQ-006` | What is the byte-exact `0x0F43029A` c-entry grammar and which runtime structures consume it? | Typed part graph and ownership. |
| 7 | `RQ-007` | What resource traversal, world selection, and procedural placement rules create the original Cell scene? | Exact player, entity, world, layer, and population reconstruction. |
| 8 | `RQ-008` | What is the exact saved-game header, `PropertyList`, `ClassSerializer`, and object-pointer record order? | Save/load compatibility and migration. |
| 9 | `RQ-009` | Which `cCellSerializableData` fields are actually written, read, defaulted, or migrated? | Cell progression and cross-stage persistence. |
| 10 | `RQ-010` | How are noun types registered, materialized, owned, and destroyed across modes? | Generic registry, factory, and destruction model. |
| 11 | `RQ-011` | What are the message queue record layout, priority direction, tie order, and send/post timing? | Deterministic event dispatch and ownership transfer. |
| 12 | `RQ-012` | How do collectables, missions, evolution, inventory, trade, and empire state synchronize and persist across modes? | Progression/economy and saved-state continuity. |
| 13 | `RQ-013` | Which `cCity`, `cBuilding`, layout-slot, cost, adjacency, and destruction rules govern city state? | City/building lifecycle and persistence. |
| 14 | `RQ-014` | What configuration accessor and property namespace does the original gameplay system use, and what did `0x00E4CE20` actually do? | Configuration and global-state access semantics. |
| 15 | `RQ-015` | What bounded original traces can adjudicate static field meanings, event order, placement, rendering, and save/load? | Promotion of static evidence to runtime truth. |

The questions and their direct references are at `knowledgegraph/research/gameplay-data-model.json:12579-12738`. The executive summary’s highest-value blockers are GMDL/RW4 payload and animation semantics; original Cell update order; original multi-package resource management; procedural Cell placement/planet terrain/non-Cell behavior; saved-game framing, pointer restoration, migration, and atomicity; and `cCellSerializableData` field coverage/cross-stage synchronization (`knowledgegraph/research/gameplay-data-model.json:4544-4551`).

## Reconstruction packages

All fourteen canonical packages are partial except `PKG-11-PERSISTENCE`, whose audit status is missing. “Covered operations” mean the bounded package boundary has evidence for those operation classes; they do not mean the missing suffix has been recovered.

| Package | Name | Status | Scope/boundary | Blocking gates |
|---|---|---|---|---|
| `PKG-01-APP-MODE-LIFECYCLE` | Application and mode lifecycle | Partial | Cell mode lifecycle, `IGameMode`/`cGameModeManager`, editor request/mode transitions, Space mode composition | Approved non-Cell trace; cross-stage handoff; exact mode IDs/names. |
| `PKG-02-ASSET-REGISTRY` | Asset registry and resource resolution | Partial | DBPF/QFS identity/extraction, manager databases/factories/caches, directory mapping, typed references | Factory/cache/async ownership; multi-package priority; name-to-key derivation. |
| `PKG-03-PROPERTY-CONFIG` | Property and configuration substrate | Partial | `IConfigManager`/`cOption`, `Property`/`PropertyList`, collectable configuration, save/reset | Configuration grammar/versioning; exact property layout/dictionary; round-trip oracle. |
| `PKG-04-GEOMETRY-PRESENTATION` | Asset geometry, materials, and presentation | Partial | Cell GFX, GMDL/RW4/raster, draw/teardown, editor skin, material/shader/texture binding | GMDL v9/trailer; RW4 payload execution; material/pixel oracle; original teardown. |
| `PKG-05-CELL-CONTENT` | Cell content graph | Partial | Globals/world/populate/cell/structure/loot/look/effect records, direct schemas, typed hard references | Loot/AI execution; original writers; resource precedence; runtime selection/placement. |
| `PKG-06-CELL-RUNTIME` | Cell runtime and gameplay state | Partial | Entity lifecycle, Cell state to presentation, `cCellGame`/pool/query, movement/combat/advect | Original update/event order; pool/query side effects; positive Cell oracle; runtime resource ownership. |
| `PKG-07-CREATURE-EDITOR` | Creature authored data and editor | Partial | Authored asset save, `cCreatureDataResource`/`EditorModel`/rigblock, editor history/pose/skin | Literal `EditorData` identity; record framing/round trip; rigblock conversion; validator/apply order. |
| `PKG-08-SPACE-EMPIRE` | Space and Empire graph | Partial | `SpaceData`/`EmpireData`, colonies/ownership, missions/inventory/trade, relationships, star/planet records | Space runtime trace; generation formulas; manager roots; mission/inventory transactions. |
| `PKG-09-PROGRESSION-ECONOMY` | Progression and economy | Partial | Unlocks, creature/Cell/scenario progression, inventory/trade/commodity, mission costs/rewards | Cross-stage synchronization; formulas/payout order; grant/spend order; round trip. |
| `PKG-10-EVENT-MESSAGES` | Events and message routing | Partial | App messages/listeners/queues, `cCommEvent`/Space events, editor/animation/deferred/feedback variants | Completion/removal order; no universal ABI; numeric IDs/payloads; priority/tie order. |
| `PKG-11-PERSISTENCE` | SaveData and serialization | Missing | Cell/Space/mission/inventory candidates, `PropertyList`/`ClassSerializer`, persistence manager, header/load context | Exact outer codec; pointer restoration; profile/slot/transaction semantics; version migration. |
| `PKG-12-TERRAIN-PLANET` | Planet and terrain lifecycle | Partial | `PlanetData`, planet model, terrain sphere, surface transition, modifications, render passes | `ToSurface` contract; generated terrain key/type; runtime terrain oracle; terrain codec. |
| `PKG-13-CITY-BUILDING` | City, building, and layout lifecycle | Partial | `cCity`/`cBuilding`/`cLayoutSlot`, value/live records, construction/update/removal | Cost/eligibility/adjacency; destruction rollback/order; layout compaction; value/live mapping. |
| `PKG-14-CROSS-MODE-OBJECT` | Generic object identity and ownership spine | Partial | `Object`/`ISimulatorSerializable`/`cGameData`, mode adapters, noun registry/factory/materialization, owner/political identity | Cross-mode trace; exact create/owner/destroy lifecycle; no universal ABI; noun factory entries. |

The package definitions, covered operations, evidence levels, and gates are canonical at `knowledgegraph/research/gameplay-data-model.json:12081-12597`.

## Bottom line

The defensible model is a layered, qualified graph: raw DBPF identity and bytes feed bounded registries and lazy caches; direct Cell and model records are static content; `cCellGame` and subtype-specific noun/space/city objects are runtime state; `cCellGFX`, material/shader/texture, renderer, editor skin, and resource caches are downstream or derived presentation; and selected `ISimulatorSerializable` owners plus headers and databases are persistence candidates. The largest unresolved boundary is the original orchestration and codec layer: exact resource precedence/release, Cell update/event order, model payload semantics, procedural placement, cross-mode ownership, and save/load framing and restoration remain open. No original runtime validation is claimed.
