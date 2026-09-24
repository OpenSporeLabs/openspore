# Reconstruction-Value Assessment

## Scope and verdict

Research-only assessment for the pinned GOG 3.1.0.22 `SporeApp.exe` (SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`). It classifies future reconstruction value; it implements nothing and does not authorize binary, Ghidra, SPORE, source, or database changes.

The highest-value anchors are cross-stage identity/persistence (`ResourceKey`, `cGameData`, `SpacePlayerData`, `cEmpire`, `Property`/`PropertyList`, `ISimulatorSerializable`), the service/lifecycle spine (`IGameMode`, `cGameInputManager`, time/behavior/persistence managers), the concrete Cell state spine (`cCellGame`, `cCellObjectData`, `cObjectPool_`, world/advect records), and the high-leverage editor/content interfaces. Global singleton wrappers and generic allocation chokepoints should not become gameplay APIs.

## Method and score provenance

- **GI (gameplay importance, 1-5):** `5` cross-stage identity/lifecycle/persistence/core state; `4` major stage/subsystem state/content; `3` major bounded feature/editor/presentation; `2` supporting adapter/tool/event; `1` peripheral/replaceable substrate.
- **R (reuse, 1-5):** direct metrics when the exact SDK type has canonical function associations: `5` >=100 caller/callee functions or pervasive owner graph; `4` 40-99, 10-19 methods, 20+ slots, or high-fanout orchestration; `3` 10-39 relationships or 5-9 methods; `2` 1-9 direct relationships; `1` no observed reusable method. Data-only types use the documented owner/field/vtable fallback and are marked high uncertainty.
- **UX (unknown-unlock leverage):** `5` >=200 gameplay callers, >=500 total callers, >=400 distinct callees from an anchor, broad named interface ownership, or >=1,000 unresolved functions; `4` 100-199 gameplay callers, 250-499 total callers, 200-399 distinct callees, 20+ vtable slots, or 100-999 unresolved functions; `3` 25-99 gameplay callers, 50-249 total callers, 100-199 distinct callees, a 10-19 method anchor, or 10-99 unresolved functions; lower bands follow proportionally.
- **Uncertainty:** `L` direct SDK layout plus multiple static artifacts; `M` static names/graphs with missing runtime or incomplete vtable/type evidence; `H` data-only, unnamed, dynamically dispatched, or type-open.
- Every score below carries its own provenance IDs. The machine-readable JSON defines the exact formulas and stores the full caller/callee metrics.

## Quantitative baseline

- Canonical function universe: **58,757**; gameplay rows: **2,149**.
- Xrefs: **223,704** total reference rows, **207,757** call rows; **33,643** functions with callers and **41,031** with callees.
- Persisted decompilation: **478** total and **172/2,149** gameplay bodies.
- Vtables: **3,081** candidates; **1,501** rows with family attribution; **4,384** unknown-vtable implementations; **44,978** unknown non-vtable functions.
- Source: P06, P07, P13. Fan-in/out is static and may miss dynamic dispatch or runtime-populated tables.

## Type assessments

### assets (6)

| Type | GI | Reuse | Class | Semantic owner | Score provenance | Rationale |
|---|---:|---:|---|---|---|---|
| `Simulator::Cell::cCellDataReference<T>` | 5/L | 4/H | `reproduce-layout` | Cell content identity and ownership | P02,P03,P09,P10 | The reference record joins instance identity, serializer state, intrusive resource ownership, and a counter. Those relationships are needed to reproduce Cell content identity and lifetime even when storage is modernized. |
| `Simulator::Cell Cell resource record family` | 5/L | 4/H | `reproduce-layout` | Cell content and tuning | P02,P03,P09 | These records carry Cell tuning, AI, food, populate, effect-map, and global initialization data. Field order and fixed/variable array boundaries are compatibility data, not implementation code. |
| `Resource::DatabasePackedFile` | 3/M | 3/L | `replaceable-infrastructure` | Resource package storage | P02,P06,P07,P12 | DBPF package/index locking and record access are mechanically important but replaceable. Preserve record identity, bounds, priority, and errors; do not reproduce the original object graph or index implementation. |
| `Resource::PFRecordRead` | 2/M | 2/L | `replaceable-infrastructure` | DBPF record access | P02,P06,P07,P12 | PFRecordRead is a bounded record adapter under the resource manager. Its byte-facing read result matters, while its internal cursor/index representation does not. |
| `ResourceKey` | 5/L | 5/H | `reproduce-layout` | Content identity | P02,P03,P10 | The type/group/instance triple is the stable content identity used by Cell, world, empire, missions, editor, rendering, and persistence. It should remain an explicit value type at every future boundary. |
| `Resource::cResourceManager` | 4/M | 4/M | `replaceable-infrastructure` | Multi-package content lookup | P02,P06,P07,P09,P12 | Lookup priority, enumeration, cache invalidation, and key identity are semantic boundaries; the manager's hash/index/cache implementation is replaceable infrastructure. |

### cell (9)

| Type | GI | Reuse | Class | Semantic owner | Score provenance | Rationale |
|---|---:|---:|---|---|---|---|
| `Simulator::Cell::cCellWorldResource::cAdvectEntry` | 4/M | 4/H | `reproduce-layout` | Cell advection and scale-bucket selection | P02,P03,P09 | Scale bucket, strength, variance, period, and advect identity drive Cell world selection and motion. Preserve the decoded record and lookup semantics; do not import original code. |
| `Simulator::Cell::cCellGame / sCellGame` | 5/M | 5/H | `reproduce-layout` | Cell stage global state | P02,P06,P07,P09,P18 | The 20,964-byte object owns world references, the 4096-cell pool, player index, serializable data, timing, lock, and update state. Exact offsets are an oracle/replacement anchor; behavior remains to be reconstructed from bounded evidence. |
| `Simulator::Cell::cCellGFX` | 4/M | 4/M | `semantic-interface-only` | Cell world, layer, model, and effect composition | P02,P06,P07,P09,P12 | World/layer creation order, preload associations, effects, and display activation are observable. The very large internal GFX object graph and RenderWare implementation are not gameplay contracts. |
| `App::cCellModeStrategy` | 5/L | 4/M | `semantic-interface-only` | Cell application mode | P02,P06,P07,P09,P12 | Initialize, enter, update, input callbacks, exit, and disposal define stage activation and ordering. Preserve those operations and transition order, not the original singleton/global ABI. |
| `Simulator::Cell::cCellObjectData` | 5/L | 5/H | `reproduce-layout` | Per-Cell entity state | P02,P03,P09,P18 | The 920-byte object is the identity, transform, target, resource, animation, health, AI, chase/flee, scale, query, and GFX record for each Cell. Its offsets are high-value compatibility facts even though this campaign does not implement the class. |
| `Simulator::Cell::cCellQueryLinkedPoolData` | 4/M | 4/H | `semantic-interface-only` | Cell spatial candidate pools | P02,P03,P09 | The linked-pool data and 28-byte query entry define nearby-cell candidate semantics. OpenSpore may use another arena, but must preserve position, radius, identity, and iteration behavior. |
| `Simulator::Cell::cCellSerializableData` | 5/L | 4/H | `reproduce-layout` | Cell save/progression state | P02,P03,P09 | The record owns Cell progression, unlocked parts, counters, play time, game/difficulty identity, mission state, and tutorial flags. Exact serialization boundaries matter for future compatibility. |
| `Simulator::Cell::cCellUI` | 3/M | 3/M | `semantic-interface-only` | Cell HUD | P02,P06,P07,P09,P11 | Cell HUD state, world/background vectors, zoom, selection, and rollover lifecycle are observable. The original object layout and UTFWin implementation are not necessary if equivalent UI behavior is provided. |
| `Simulator::Cell::cCellWorldResource` | 4/M | 4/H | `reproduce-layout` | Cell world configuration | P02,P03,P09 | The header points to scale-level and advect arrays that determine Cell world population and flow selection. Decode and preserve those relationships even before runtime execution is reconstructed. |

### creatures_social (5)

| Type | GI | Reuse | Class | Semantic owner | Score provenance | Rationale |
|---|---:|---:|---|---|---|---|
| `Simulator::cCreatureCitizen` | 4/M | 4/H | `semantic-interface-only` | Creature social simulation | P02,P03,P10 | The citizen is a core creature/social participant inside tribes and colonies. Preserve identity, membership, needs, abilities, and lifecycle interfaces; the complete 4 KB layout is not automatically a gameplay requirement. |
| `Simulator::cCity` | 4/M | 4/M | `semantic-interface-only` | City simulation | P02,P04,P06,P07,P10 | Buildings, population, vehicles, updates, and city lifecycle are semantic. The original 36-slot ABI and building-object graph may be replaced once the state transitions are identified. |
| `Simulator::cCreatureBase` | 5/M | 4/M | `semantic-interface-only` | Creature base behavior and presentation | P02,P04,P06,P07,P10 | The 58-slot surface spans targets, abilities, animation, effects, movement, social behavior, and gameplay callbacks. Preserve the semantic operations and dispatch order, not the complete original object memory image. |
| `Simulator::cCreatureGameData` | 5/L | 3/L | `reproduce-layout` | Creature progression | P02,P04,P06,P07,P10 | Brain level, evolution points, ability mode, learned abilities, glide state, and normalizing scale are explicit progression state. Exact offsets are useful for reconstruction and differential work. |
| `Simulator::cTribe` | 5/M | 4/H | `reproduce-layout` | Tribe simulation and progression | P02,P03,P10,P16 | Political identity, population, position, members, tools, planners, food, timers, and progression make cTribe a core persistent social-state record. Layout recovery is valuable, but no reconstruction is authorized here. |

### editor_ui (10)

| Type | GI | Reuse | Class | Semantic owner | Score provenance | Rationale |
|---|---:|---:|---|---|---|---|
| `Editors::cEditorAnimEvent` | 3/M | 3/M | `semantic-interface-only` | Editor-to-animation/message bridge | P02,P06,P07,P11,P14 | Send versus post and the packed editor-model/event payload are useful semantic boundaries. The concrete allocator and temporary object implementation are replaceable. |
| `Editors::cEditorAnimWorld` | 3/M | 4/M | `semantic-interface-only` | Editor animation world | P02,P06,P07,P11 | Creature lookup, target position/angle, and controller/animation association are semantic. Container internals may be modernized. |
| `Editors::EditorCreatureController` | 3/M | 2/M | `semantic-interface-only` | Editor creature target interpolation | P02,P03,P06,P07,P11 | Current/real target position, current/target angle, movement, rotation, and update interpolation are the controller contract. Exact singleton/object storage is not necessary. |
| `Editors::EditorModel` | 4/M | 4/M | `semantic-interface-only` | Editor model document | P02,P06,P07,P11 | Creation identity, parts, colors, names, history, and model transitions are editor semantics. The original virtual object graph can be replaced after contracts are frozen. |
| `Editors::EditorPlayMode` | 3/M | 3/M | `semantic-interface-only` | Editor play-mode interaction | P02,P06,P07,P11 | Play-mode input, actor callbacks, environment reactions, and update sequencing are semantic. The 22 KB concrete object layout is not required unless byte-level compatibility is chosen. |
| `Editors::cEditor` | 4/M | 5/M | `semantic-interface-only` | Editor interaction and command dispatch | P02,P06,P07,P08,P11,P14 | cEditor is the input/message/update/edit-history boundary and reaches 494 distinct callees across editor, UI, resources, graphics, and gameplay. Preserve its semantic command surface, not the original object memory or UTFWin hierarchy. |
| `Anim::AnimatedCreature` | 4/M | 4/H | `semantic-interface-only` | Animated creature presentation state | P02,P03,P11 | Position, orientation, model, animation IDs, blend/loop state, and anim-world ownership are the useful contract. The original 32-slot ABI and model objects are replaceable behind an animation interface. |
| `Anim::IAnimWorld` | 4/M | 4/H | `semantic-interface-only` | Animation world | P02,P03,P11 | Load/update/destroy creature operations and model/effect world binding are useful semantic interfaces. Implementations and object ownership are replaceable. |
| `UTFWin::IWindow` | 3/M | 5/H | `replaceable-infrastructure` | Window framework interface | P02,P03,P08,P11 | Window/proc/drawable behavior can be supplied by a modern UI toolkit. Preserve event identity, command IDs, hierarchy effects, and mode routing, not the original 71-slot ABI. |
| `UTFWin::Window` | 3/M | 5/M | `replaceable-infrastructure` | UTFWin window/proc/drawable framework | P02,P06,P07,P08,P11 | Parent/child windows, proc lists, areas, controls, cursor, caption, and drawables define UI behavior, but the original framework can be replaced. Only externally meaningful commands and dispatch survive. |

### empire_space (10)

| Type | GI | Reuse | Class | Semantic owner | Score provenance | Rationale |
|---|---:|---:|---|---|---|---|
| `Simulator::cEmpire` | 5/M | 4/H | `reproduce-layout` | Empire identity, progression, and economy | P02,P03,P06,P07,P10,P15 | Political ID, identity color, names, archetype/trait, allies/enemies, home system, money, culture, and progression form the empire identity record. Its layout is persistent and shared across space, relationships, missions, and events. |
| `Simulator::cMission` | 5/M | 4/H | `reproduce-layout` | Mission instance state | P02,P03,P10 | Mission identity, state, timing, owners/targets, rewards, unlocks, costs, progress events, properties, and communication links are both serialized state and transition semantics. |
| `Simulator::cMissionManager` | 5/M | 3/M | `semantic-interface-only` | Mission lifecycle | P02,P04,P06,P07,P10 | Availability, selection, tracking, recent mission lists, configuration, limits, and gaps are semantic transitions. Internal storage can be replaced after transition contracts are established. |
| `Simulator::cRelationshipData` | 4/L | 4/H | `reproduce-layout` | Directed empire relationship state | P02,P03,P10 | Relationship value, flags, and event modifiers form the durable directed-pair state. Exact field semantics are needed to preserve war/alliance transitions. |
| `Simulator::cRelationshipManager` | 5/M | 4/L | `semantic-interface-only` | Diplomatic relationships | P02,P04,P06,P07,P08,P10 | Directed political-ID lookup, war/alliance/peace transitions, decay queues, and event modifiers are semantic. The map/container implementation is replaceable. |
| `Simulator::cSpaceInventoryItem` | 4/M | 3/M | `reproduce-layout` | Space cargo and trade inventory | P02,P03,P06,P07,P10 | Count, type, cost, uniqueness, political/position IDs, properties, resource key, and message links define cargo/trade identity. The object crosses economy, events, and persistence. |
| `Simulator::SpacePlayerData` | 5/L | 5/H | `reproduce-layout` | Current space/player identity | P02,P03,P15 | Active planet/star, relationship manager, current context, player empire ID/cache, rotation, and colonies form a compact cross-stage identity spine. Exact offsets anchor several unknown roots. |
| `Simulator::cSpaceTrading` | 5/M | 5/L | `semantic-interface-only` | Space trading and rare commodities | P02,P04,P06,P07,P08,P10 | Spices, rare maps/groups, NPC stores, newly available commodities, and mode identity define trade behavior. Internal maps and strategy vtables may be replaced behind that contract. |
| `Simulator::cSpaceTradeRouteManager` | 3/H | 2/H | `semantic-interface-only` | Space trade routes | P02,P06,P07,P10 | Route presence and map data are semantic, but the route algorithm is unresolved. Characterize the interface before deciding whether layout or implementation matters. |
| `Simulator::cCommodityNode` | 4/M | 4/H | `semantic-interface-only` | Planet commodity resources | P02,P03,P10 | Resource points, ownership, capture/convert/buy state, and percentages are gameplay-facing. The full object can remain behind a typed planet-resource interface unless binary replacement requires offsets. |

### events (6)

| Type | GI | Reuse | Class | Semantic owner | Score provenance | Rationale |
|---|---:|---:|---|---|---|---|
| `Anim::AnimationMessage` | 4/M | 3/H | `reproduce-layout` | Animation message payload | P02,P03,P11 | Message ID, name, creature, block, and scalar parameters form a concrete cross-boundary payload. Preserve field order and payload meaning once IDs are named. |
| `Simulator::cCommEvent` | 4/M | 3/H | `semantic-interface-only` | Communication events | P02,P03,P10,P16 | Communication event identity, sender/receiver, arguments, and queue/display transitions are semantic. Numeric message/action IDs and mode-specific records remain unresolved. |
| `Simulator::cCommManager` | 4/M | 3/M | `semantic-interface-only` | Communication event routing | P02,P04,P06,P07,P10 | Current event, event lists, message listener, cancellation conditions, creation, handling, and display are semantic. Container internals are replaceable. |
| `App::IMessageManager` | 4/M | 3/H | `semantic-interface-only` | Application message dispatch | P02,P06,P07,P08,P11 | Send, post, listener/handler registration, priority, locking, and ordered queue processing are semantic routing contracts. The original ABI and storage are replaceable. |
| `App::cMessageManager` | 4/M | 3/H | `semantic-interface-only` | Application message queue | P02,P06,P07,P08,P11 | Queue entries, priorities, listeners, handlers, lock/remove/process operations, and post/send distinctions are semantic. Internal queue objects are replaceable. |
| `Simulator::cUIEventLog` | 3/M | 4/M | `semantic-interface-only` | Gameplay event log | P02,P04,P06,P07,P08 | Event-log entries, timestamps, icons/text, lifetime, and display are semantic; storage and UI widgets are replaceable. |

### managers_gameplay (10)

| Type | GI | Reuse | Class | Semantic owner | Score provenance | Rationale |
|---|---:|---:|---|---|---|---|
| `Simulator::cGameBehaviorManager` | 4/M | 3/M | `semantic-interface-only` | Gameplay behavior service | P02,P06,P07,P08,P12 | AI/behavior registration, update, and event delivery determine gameplay decisions. The concrete manager object and vtable can be replaced by an injected service. |
| `Simulator::cGameData` | 5/M | 4/M | `reproduce-layout` | Gameplay entity identity base | P02,P03,P06,P07,P10 | Game-data ID, definition ID, owner, and political ID form a recurring identity/persistence base across tribes, inventory, cities, commodities, tools, and missions. |
| `Simulator::cGameInputManager` | 5/L | 5/L | `reproduce-layout` | Input and active-mode routing | P02,P03,P06,P07,P08,P15 | Input state, current/previous mode, maps, mouse values, regions, strings, and callbacks are explicit field/vtable facts. A future interface should preserve normalized events and routing, while raw layout is valuable for compatibility and static typing. |
| `App::cGameModeManager / Simulator::cGameModeManager` | 5/L | 4/L | `semantic-interface-only` | Game-mode registry and activation | P02,P04,P06,P07,P08,P10 | Registration, active index, mode identity/name, camera/viewer, set/get operations, and exit-before-enter ordering are central semantic contracts. The global registry layout is replaceable. |
| `Simulator::cGameNounManager` | 4/M | 4/M | `semantic-interface-only` | Noun identity and materialization | P02,P04,P06,P07,P15 | Noun identity, data materialization, model updates, and player/noun lookup are semantic. Exact map/node internals are replaceable once root 00b21340 is characterized. |
| `Simulator::cGamePersistenceManager` | 4/H | 3/H | `semantic-interface-only` | Gameplay persistence coordination | P02,P06,P07,P12 | Save/load coordination is semantically important, but the service implementation is replaceable. First characterize ownership, transaction boundaries, and serializable graph traversal. |
| `Simulator::cGameTimeManager` | 5/M | 4/M | `semantic-interface-only` | Frame time, pause, and speed | P02,P04,P06,P07,P08,P12 | Frame time, delta conversion, pause count, speed, and update order determine deterministic behavior. Expose typed clock operations rather than reproduce the manager object. |
| `Simulator::cGameViewManager` | 4/M | 3/M | `semantic-interface-only` | Game viewer and camera service | P02,P06,P07,P12 | Viewer, camera, projection, and view-ray services affect movement and presentation. Preserve normalized camera/ray operations; replace concrete graphics objects. |
| `Simulator::cObjectPool_` | 4/M | 4/L | `reproduce-layout` | Pooled gameplay entity lifetime | P02,P03,P06,P07,P09,P18 | Data pointer, next-free index, identifier, capacities, object size, and lifetime metadata define pool-index identity used by Cell replacement and creation. Exact offsets are valuable; allocator policy is not sacred. |
| `Simulator::cSimulatorSystem` | 5/M | 4/M | `semantic-interface-only` | Global Simulator service coordination | P02,P04,P06,P07,P08,P17 | The root owns or coordinates global Simulator services. Preserve service lookup/lifecycle semantics through dependency injection; do not reproduce the singleton registry implementation. |

### persistence (6)

| Type | GI | Reuse | Class | Semantic owner | Score provenance | Rationale |
|---|---:|---:|---|---|---|---|
| `App::cPropManager` | 3/M | 3/M | `replaceable-infrastructure` | Property-list registry | P02,P06,P07,P12 | Global/local property-list ownership, preloading, creation, and reference tracking are infrastructure. Typed property keys, lookup, enumeration, and stream behavior are the semantic boundary. |
| `App::DirectPropertyList` | 4/M | 3/M | `replaceable-infrastructure` | Direct property storage | P02,P04,P06,P07,P12 | Direct-property storage is an optimization beneath the property contract. Preserve lookup, typed values, parent behavior, and stream compatibility; the concrete layout may be replaced. |
| `Simulator::ISimulatorSerializable` | 5/L | 4/H | `semantic-interface-only` | Serializable gameplay object contract | P02,P03,P10,P12 | Reference counting, cast identity, read/write, noun identity, and related hooks define the serializable-object contract. Preserve operations and ordering, not the original three-pointer inheritance layout. |
| `App::Property` | 5/M | 5/M | `reproduce-layout` | Typed property value | P02,P04,P06,P07,P12 | The exported size is the small wrapper/union representation, while its typed value forms include booleans, numbers, strings, vectors, keys, transforms, and arrays. Exact stream encoding and typed access semantics are the contract, not the original getter family. |
| `App::PropertyList` | 5/M | 4/M | `reproduce-layout` | Property and configuration serialization | P02,P03,P04,P06,P07,P10,P12 | Sorted entries, parent fallback, operation count, ownership, read/write, and property IDs determine configuration and save behavior. Preserve the stream and inheritance semantics; container internals may later be modernized behind a tested codec. |
| `Simulator::cSavedGameHeader` | 4/M | 3/H | `reproduce-layout` | Save-game header | P02,P03,P10 | The serializable header carries current planet and other save identity. Its stream position and field order are compatibility facts even when the rest of persistence is redesigned. |

### unknown_infrastructure (3)

| Type | GI | Reuse | Class | Semantic owner | Score provenance | Rationale |
|---|---:|---:|---|---|---|---|
| `FUN_00b3d300 / FUN_00b3d2a0 / FUN_00b5b800` | 5/H | 5/H | `semantic-interface-only` | Unknown shared Simulator services | P06,P07,P08,P14,P15 | The unresolved global-slot/accessor family underpins much of Simulator. Characterize return values, ownership, and use domains before assigning any concrete class; never infer implementation from fan-in. |
| `unknown-vtable-impl corpus` | 3/H | 5/H | `semantic-interface-only` | Unknown virtual implementations | P08,P14,P17 | The 4,384 unknown-vtable implementation rows can unlock broad dispatch semantics, but identity is unresolved and 14 rows carry gameplay logic. Vtable-owner mapping should precede body reconstruction. |
| `FUN_00f47380 / FUN_00f473a0 wrapper forest` | 1/M | 5/M | `replaceable-infrastructure` | Generic allocation/reference infrastructure | P06,P07,P08,P12 | The 6,527-caller release/forwarding wrapper and 2,901-caller construction wrapper are graph chokepoints, not gameplay types. Preserve allocator/reference behavior through modern infrastructure and do not anchor gameplay reconstruction on them. |

### worlds (6)

| Type | GI | Reuse | Class | Semantic owner | Score provenance | Rationale |
|---|---:|---:|---|---|---|---|
| `Simulator::cPlanetRecord` | 5/M | 4/H | `reproduce-layout` | Planet identity and generated content | P02,P03,P04,P06,P07,P10 | Planet type/orbit, scores, species, commodities, tech, spice generation, terrain key, tribes, and colonies drive world identity and progression. Exact record layout is valuable for reconstruction and persistence. |
| `Simulator::cPlanetModel` | 5/M | 4/M | `semantic-interface-only` | Planet surface model | P02,P04,P06,P07,P08 | Height, gravity, water, orientation, surface conversion, and nearest-city queries are the gameplay-facing planet model. The 92-byte wrapper is best treated as an interface over replaceable terrain/physics infrastructure. |
| `Simulator::cSolarSystem` | 4/M | 3/M | `semantic-interface-only` | Solar-system load and generation | P02,P04,P06,P07 | Loading, binary stars, asteroids, celestial effects, and graphics are semantic system boundaries. Concrete effects and render objects are replaceable. |
| `Simulator::cStarRecord` | 4/M | 3/M | `reproduce-layout` | Star-system identity | P02,P03,P04,P06,P07,P10 | Last-observed time, empire/starter IDs, key, citizen species, profile, planets, and count define serializable star identity. Preserve layout for world generation and save compatibility. |
| `Simulator::cStarManager` | 5/M | 4/M | `semantic-interface-only` | Galaxy generation and empire registry | P02,P04,P06,P07,P08,P10,P15 | Star grids, starter/saved records, empires, adventure IDs, generation rules, political IDs, trade routes, relationships, and transactions form a major semantic manager. Internal storage is replaceable after state transitions are frozen. |
| `Terrain::cTerrainSphere` | 4/M | 4/M | `semantic-interface-only` | Planet terrain generation and presentation | P02,P04,P06,P07,P08,P12 | Terrain generation, chunks, modifications, height queries, water, land, atmosphere, and render passes carry world behavior. RenderWare-specific structures and passes are replaceable infrastructure; semantic terrain queries are not. |

## Highest-leverage unknown unlockers

| Unlock target | UX | Classification | Quantitative reach | Score provenance | What it unlocks |
|---|---:|---|---:|---|---|
| `unknown-root-00b3d300` | 5/H | `semantic-interface-only` | 1,097 total / 252 gameplay | P08,P14,P15 | Resolve global-slot ownership and consumer domains before dependent Simulator functions. |
| `unknown-root-00b3d2a0` | 4/H | `semantic-interface-only` | 314 total / 101 gameplay | P08,P14,P15 | Resolve adjacent global-slot identity and its role in current-empire lookup. |
| `unknown-root-00b5b800` | 4/H | `semantic-interface-only` | 459 total / 80 gameplay | P08,P14,P15 | Resolve scalar/handle semantics and forwarded object ownership. |
| `unknown-space-player-roots` | 5/M | `semantic-interface-only` | 619 summed root callers / 153 summed gameplay callers | P15 | Roots 01021260, 01021080, and 01021300 expose current planet, context, player ID, and lazy empire cache. |
| `unknown-noun-registry` | 3/H | `semantic-interface-only` | 254 total / 50 gameplay | P08,P14,P15 | Characterize FUN_00b21340 before assigning a concrete cGameNounManager method identity. |
| `editor-command-surface` | 5/M | `semantic-interface-only` | 31 total / 16 gameplay | P08,P11,P14 | 21 named methods and 24 attributed vtable functions reach 494 distinct callees; input/message/tool ownership unlocks a large unknown region. |
| `input-manager-contract` | 5/L | `semantic-interface-only` | 614 total / 80 gameplay | P02,P08,P15 | The 27-slot input/mode vtable and field map anchor the broadest direct gameplay dependency. |
| `property-data-spine` | 5/M | `reproduce-layout` | 841 total / 82 gameplay | P02,P06,P07,P12 | 68 Property methods and 15 PropertyList methods connect configuration, content, and persistence to 74 distinct callees. |
| `unknown-vtable-corpus` | 5/H | `semantic-interface-only` | n/a total / 14 gameplay | P08,P13,P14,P17 | Vtable-owner mapping is a prerequisite for dispatch semantics across editor, app, resource, and UI code. |
| `generic-wrapper-forest` | 5/M | `replaceable-infrastructure` | 9,428 total / n/a gameplay | P08,P12 | High graph leverage but only allocator/reference infrastructure; it must not anchor gameplay reconstruction. |

## Interface anchors for future reconstruction

- **`ICellGameState + IEntityPool + ICameraRayProvider`** — `semantic-interface-only`; owns player identity, pool handles, world/plane state, movement targets, and ordered interaction events. Evidence: P02, P09, P12. Research anchor only.
- **`IAppHost + IGameModeRegistry`** — `semantic-interface-only`; mode registration, activation ordering, frame ticking, shutdown, and injected host services. Evidence: P02, P08, P10, P12. Research anchor only.
- **`IInputRouter + cGameInputManager field contract`** — `reproduce-layout`; the 614-caller input manager and 27-slot vtable are the strongest input/mode state anchor. Evidence: P02, P03, P08, P15. Research anchor only.
- **`IGameServices`** — `semantic-interface-only`; typed input, camera/view, behavior, mode, persistence, and frame-clock operations replace raw global getters. Evidence: P02, P04, P08. Research anchor only.
- **`IContentStore + IRecordCodec`** — `reproduce-layout`; ResourceKey identity and record bytes are semantic; DBPF indexes, caches, and package locks are replaceable. Evidence: P02, P03, P12. Research anchor only.
- **`IPropertyStore + IPropertyCodec`** — `reproduce-layout`; typed keys, parent fallback, enumeration, and versioned read/write behavior anchor configuration and persistence. Evidence: P02, P03, P04, P12. Research anchor only.
- **`ISerializableGameObject`** — `semantic-interface-only`; read/write/noun/refcount operations span empire, star, mission, and Cell save state without requiring the original inheritance ABI. Evidence: P02, P03, P10. Research anchor only.
- **`IEventRouter + typed stage events`** — `semantic-interface-only`; ordered key/mouse/window/message routing and mode transitions must survive UTFWin/message-manager replacement. Evidence: P02, P08, P11. Research anchor only.
- **`IAnimationWorld + IAnimatedCreature`** — `semantic-interface-only`; creature load/update/destroy and animation state/pose operations bridge editor and rendering. Evidence: P02, P11. Research anchor only.
- **`IPlayerIdentity + IEmpireRegistry`** — `semantic-interface-only`; SpacePlayerData, current-empire cache, political ID, and star-manager registry unlock a large unknown space/empire region. Evidence: P02, P08, P10. Research anchor only.
- **`IRelationshipStore + ITradeService + IMissionService`** — `semantic-interface-only`; war/alliance transitions, trade inventory, and mission state are high-value space interfaces; internals remain replaceable. Evidence: P02, P04, P10. Research anchor only.
- **`IUiWindow + IUiCommandRouter`** — `replaceable-infrastructure`; retains command/window semantics while allowing UTFWin, RenderWare, and D3D implementations to be replaced. Evidence: P08, P12. Research anchor only.

## Vtable interfaces

| Interface | Slots | Bytes | Classification | Status | Evidence |
|---|---:|---:|---|---|---|
| `Anim::IAnimWorld` | 23 | 92 | `semantic-interface-only` | major anchor | P02,P17 |
| `Anim::AnimatedCreature` | 32 | 128 | `semantic-interface-only` | major anchor | P02,P08,P10 |
| `App::IGameMode` | 16 | 64 | `semantic-interface-only` | major anchor | P02,P10 |
| `App::IGameModeManager` | 23 | 92 | `semantic-interface-only` | major anchor | P02,P08,P10 |
| `App::IMessageManager` | 19 | 76 | `semantic-interface-only` | major anchor | P02,P11,P12 |
| `App::IAppSystem` | 36 | 144 | `replaceable-infrastructure` | host boundary | P02,P08,P11,P12 |
| `Simulator::ISimulatorSerializable` | 9 | 36 | `semantic-interface-only` | major anchor | P02,P03,P15 |
| `Simulator::cGameInputManager` | 27 | 108 | `reproduce-layout` | major anchor | P02,P15 |
| `Simulator::cCreatureBase` | 58 | 232 | `semantic-interface-only` | major anchor | P02,P04 |
| `Simulator::cMission` | 102 | 408 | `reproduce-layout` | large semantic surface | P02,P10 |
| `Simulator::cSpaceInventoryItem` | 20 | 80 | `reproduce-layout` | economy boundary | P02,P10 |
| `App::PropertyList` | 19 | 76 | `reproduce-layout` | persistence anchor | P02,P12 |
| `UTFWin::IWindow` | 71 | 284 | `replaceable-infrastructure` | replaceable UI surface | P02,P11,P12 |
| `Resource::DatabasePackedFile` | 37 | 148 | `replaceable-infrastructure` | replaceable storage surface | P02,P12 |
| `App::cCellModeStrategy` | 27 | n/a | `semantic-interface-only` | candidate: 13 of 27 named family rows | P06,P08,P09,P11 |
| `Editors::cEditor` | n/a | n/a | `semantic-interface-only` | owner mapping required | P06,P08,P11 |
| `Editors::EditorModel` | n/a | n/a | `semantic-interface-only` | owner mapping required | P06,P08,P11 |

## Recommended anchor order

1. **ResourceKey; cGameData; SpacePlayerData; cEmpire; Property/PropertyList; ISimulatorSerializable** — cross-stage identity and persistence contracts reduce the largest semantic unknowns.
2. **IAppHost + IGameModeRegistry; cGameInputManager; IGameServices; cGameTimeManager; cGameBehaviorManager; cGamePersistenceManager** — mode, input, behavior, clock, and persistence boundaries unlock dependent stage code.
3. **cCellGame; cCellObjectData; cObjectPool_; cCellWorldResource/cAdvectEntry; cCellSerializableData** — these are the concrete Cell state, identity, pool, content, and save spine.
4. **cCreatureBase; cCreatureGameData; cTribe; cCity; cPlanetModel; cStarManager; cSpaceTrading; cRelationshipManager; cMissionManager** — stage and cross-stage gameplay owners should be characterized before their many dependent functions.
5. **cEditor; IAnimationWorld/IAnimatedCreature; IEventRouter; IContentStore; IPropertyStore** — editor, content, UI, animation, and property boundaries concentrate broad fan-out and can be modernized behind interfaces.

**Campaign constraint:** Research only. This campaign implements none of the anchors and authorizes no source, binary, or Ghidra mutation.

## Classification rules

- **replaceable-infrastructure:** A modern equivalent may replace the original implementation. Only externally observable identity, ordering, data, error, and event contracts cross the boundary.
- **reproduce-layout:** The byte layout, field offsets, record order, or serialized identity is itself reconstruction evidence and should be preserved in future clean-room compatibility work. This campaign records the decision only and implements nothing.
- **semantic-interface-only:** Operations, identity, state transitions, event ordering, and cross-subsystem meaning matter; the original in-memory class layout and vtable ABI need not be reproduced.

## Limits and uncertainty

- No function-level original runtime trace exists; semantic understanding is not promoted to OBSERVED or VERIFIED.
- SporeApp.exe has no MSVC RTTI, so class hierarchy and vtable ownership are incomplete.
- The canonical function manager iterator has 58,757 entries while the live manager count previously reported 59,245; all type metrics use the frozen 58,757-row corpus.
- Only 172/2,149 gameplay functions have persisted decompilation, and all persisted exports carry unknown-calling-convention warnings.
- Type-level xrefs are not directly exported. Reuse metrics associate canonical functions through exact SDK `struct_names`; data-only types use a lower-confidence structural fallback.
- Distinct caller/callee unions do not prove runtime reachability and can double-count a caller across methods only in sum metrics; union fields are preferred.
- Function association is name/struct provenance, not proof that every SDK function has the expected receiver type or that every vtable family label is correct.
- SDK layouts include imported or incomplete fields; exact field semantics remain bounded by decompilation, dossiers, and absent runtime evidence.
- The Ghidra MCP connection had no open program at final verification, so no new live query was available.
- The assessment intentionally does not rank implementation effort or authorize implementation.

## Provenance

- **P01** `docs/RECON-3.1.0.22.md` — binary identity, namespace map, manager spine, resource/UI architecture. SHA-256 `fec2d4b2903a92c104088d418453b1fa1c59a6036ecc7a5fb5ba0e9c742d1124`.
- **P02** `.spore-analysis/ghidra-exports/structs.tsv` — SDK structure sizes and field counts. SHA-256 `760abadb93eff534ed51f4c173c9ac01f9f0e39d420cecc655c4ac0d451e6804`.
- **P03** `.spore-analysis/ghidra-exports/structs_fields.tsv` — SDK field offsets, vtable slots, and embedded interface evidence. SHA-256 `5e5cafbd96dd9112dcc276d55a01ac06c95d3950b1b4a7fbce0e2f25293bc706`.
- **P04** `.spore-analysis/ghidra-exports/sdk_functions.tsv` — SDK function/type anchors. SHA-256 `61ab8cd4fbee1e479f574ff8c05364ada16ddbd0d4c07b3fb96f9201ec8d92e9`.
- **P05** `.spore-analysis/ghidra-exports/functions.tsv` — pinned function boundaries and body sizes. SHA-256 `f0d3573c937b6a6ed3ddcc4139188e9e412f81cd1250ef50780338b55ab7f539`.
- **P06** `knowledgegraph/research/track-b-function-accounting.jsonl` — canonical per-function caller/callee, category, SDK type, vtable, and decomp fields. SHA-256 `8a23a836b039f61521b7614c503d4b56981c969be22f345482472e043e983881`.
- **P07** `knowledgegraph/triage/xrefs-2540f2ca.tsv` — canonical call/reference edges used for union and edge metrics. SHA-256 `89e74b8a03c4db38a1927f8c95c38db507bf99cb8a11de6b6eb6a9484d8c79cb`.
- **P08** `knowledgegraph/research/global-campaign-2026/track-j-dependency-graph.json` — global graph, roots, bridges, chokepoints, and cluster leverage. SHA-256 `d17643e9bceba04ac8300e9ae2a674d752ae3da008eda5dcbcc327a890ba7b5a`.
- **P09** `knowledgegraph/research/global-campaign-2026/track-d-sim-cell.json` — Cell structures, state, events, and contracts. SHA-256 `d0d24389d4df21dfa13efb5f0f468bc597361ff8cfe515faef8840fdd0586979`.
- **P10** `knowledgegraph/research/global-campaign-2026/track-f-empire-economy.json` — empire, space, relationships, progression, missions, and serialization. SHA-256 `f4d84eee4efcb6592fcb5cf54fcac414d6b403a1c4bcac57c8630b067e95032d`.
- **P11** `knowledgegraph/research/global-campaign-2026/track-g-editor-ui-input.json` — editor, UI, input, message, animation, and vtable interfaces. SHA-256 `bcaa6fd1af6925702e3da37ff47997f3b6fe02f5c2edf08e479e0dfe5ef6ddde`.
- **P12** `knowledgegraph/research/global-campaign-2026/track-k-engine-boundaries.json` — semantic versus replaceable reconstruction boundaries. SHA-256 `5cbccc99d4de6b0ca4a636c7076f522f37ecbb584b3d6f2a7e59f254617d2cc5`.
- **P13** `knowledgegraph/research/global-campaign-2026/track-p-coverage.json` — canonical function, decompilation, xref, vtable, cluster, and runtime coverage. SHA-256 `750bffa7a7188552ecc5c7197ea5aabccc398026169ca4f13aae88d574b78aa1`.
- **P14** `docs/analysis/reconstruction-readiness.md` — gameplay population, shared-state roots, fan-in/out, and prioritization. SHA-256 `0622c6e26d7214b3158b805acda7591d03a2d5d706cb0e5476ba4d0e4dbe56e3`.
- **P15** `docs/analysis/simulator-shared-state-interface.md` — shared-state root return contracts, offsets, null/handle semantics, and owner domains. SHA-256 `e69656eb1bdb9339d5dd58dc3cffaaae5f253f0522f5c2a33433eb396d886a8a`.
- **P16** `docs/analysis/unknown-high-resolution.md` — unknown-high hubs, dossiers, vtable debt, and event/space follow-up evidence. SHA-256 `9d9480c117365f7e89f39167e98419c10e0713f91498de8d1af41ddaee0d21b4`.
- **P17** `knowledgegraph/research/track-i-dependency-graph.json` — earlier dependency graph and manager-first ordering. SHA-256 `52af99c70284e1276da03051270f1dcf9f475a42fd5927df8f0622c961f20b17`.
- **P18** `docs/REPLACEMENT-ABI.md` — Cell replacement field-offset evidence and explicit status limits. SHA-256 `f31cc8797e363334dfa31d4b7da722a60419676b96add8f0887f9929816f9ca3`.
- **P19** `ghidra_mcp_read_only_status` — final availability check; zero open programs, so no live Ghidra evidence was added. Status-only; no hash.

## Integrity

- Deterministic ordering and no timestamp or wall-clock field.
- Exactly the two requested research files were written.
- No source implementation, binary rewrite, Ghidra mutation, knowledgegraph database write, SPORE access, old-artifact rewrite, or proprietary payload reproduction occurred.
