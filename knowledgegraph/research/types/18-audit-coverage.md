# Type Research Coverage Audit

## Scope and policy

This audit evaluates the read-only worker artifacts in `knowledgegraph/research/types/` against six campaign objectives:

1. vtable archaeology;
2. class and struct recovery;
3. field archaeology;
4. lifecycle recovery;
5. class-family recovery; and
6. reconstruction value.

The audit distinguishes static evidence, inference, contradiction, and missing evidence. A candidate identity, source-purpose label, SDK association, vtable proximity, or current OpenSpore projection does not by itself establish original runtime behavior, C++ ownership, or a complete ABI.

- Binary: `SporeApp.exe`, version `3.1.0.22`
- Architecture: `x86:LE:32`
- Image base: `0x00400000`
- SHA-256: `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`
- No new Ghidra, runtime, build, test, or game evidence was added.
- No worker artifact, source, `SPORE/`, Ghidra state, history, triage, or knowledge-graph mutation occurred.

## Baseline and limitations

| Metric | Count |
|---|---:|
| Canonical functions | 58,757 |
| Xref edges | 223,704 |
| Persisted decompilation bodies | 478 |
| Gameplay rows | 2,149 |
| Persisted gameplay bodies | 172 |
| Runtime-validated functions | 0 |
| Ghidra structures | 2,035 |
| Structure fields | 25,546 |
| SDK association records | 306 |
| Vtable candidate bases | 3,081 |
| Vtable labels | 20 |
| High-confidence vtable candidates | 369 |
| Medium-confidence vtable candidates | 871 |
| Low-confidence vtable candidates | 1,841 |
| Vtable-reference edges | 11,898 |
| Data-reference edges | 4,049 |
| Shared-slot clusters | 16,107 |
| Vtable pair clusters | 300 |
| Explicit inheritance chains | 12 |

Global limits:

- `SporeApp.exe` has no MSVC RTTI, so class and inheritance identity cannot be promoted from candidate proximity alone.
- No positive original Cell, Space, Empire, Editor, UI, or persistence runtime trace is present.
- Persisted-body absence is uncaptured evidence, not proof that decompilation is impossible.
- The vtable scan reports 58,756 functions while the canonical triage/xref universe reports 58,757; this scope drift is preserved.
- Historical verification status is not original semantic truth.

## Partition verification

| ID | Kind | Status | Coverage |
|---|---|---|---|
| `00-corpus-inventory` | Inventory | Strong | Canonical corpus identity, authority precedence, hashes, source manifest, conflicts, and follow-up leads. |
| `01-simulator-core` | Semantic domain | Strong | Simulator services, shared managers, Cell state, pool identity, accessors, and reconstruction spine. |
| `02-gameplay-entity` | Semantic domain | Strong | Gameplay/entity types, Cell state, fields, vtable candidates, lifecycle anchors, and reconstruction relevance. |
| `03-creature` | Semantic domain | Partial | Creature simulation, evolution, editable models, rigblocks, animation, ornaments, herd, and collectables. |
| `04-world-planet` | Semantic domain | Partial | Stars, planets, orbital data, generation, terrain, climate, geography, managers, consumers, and serialization. |
| `05-empire-space` | Semantic domain | Partial | Empire, player, diplomacy, trade, missions, star/planet records, inventory, and relationships. |
| `06-editor-ui` | Semantic domain | Partial | Editor, input, UTFWin, message, layout, controller, rendering, and UI-object types. |
| `07-event-message` | Semantic domain | Strong | Message records, listeners, handlers, queues, UTFWin dispatch, mode events, animation events, deferred events, feedback, and comms. |
| `08-persistence-serialization` | Semantic domain | Partial | Resource databases, Property/PropertyList, serializer interfaces, saved-game headers, Cell persistence, and format gates. |
| `09-asset-content` | Semantic domain | Partial | DBPF, RW4, GMDL, raster, world-object, Cell records, content graphs, handles, and terrain/audio/metadata content. |
| `10-managers-registries` | Semantic domain | Strong | Application/Simulator accessors, service slots, registries, pools, allocators, vtable families, and replaceable boundaries. |
| `11-vtable-archaeology` | Cross-cutting | Strong | Candidate vtables, slot status, SDK associations, high-value records, families, consumers, inheritance candidates, and contradictions. |
| `12-field-archaeology` | Cross-cutting | Strong | High-value offsets, read/write consumers, shared layouts, current-source comparisons, contradictions, and semantic ceilings. |
| `13-lifecycle` | Cross-cutting | Partial | Construction, initialization, registration, enter/update, reuse, exit, dispose, pools, managers, cleanup, and exception paths. |
| `14-class-families` | Cross-cutting | Partial | Class/interface inventory, address-bearing trees, ctor/dtor records, factory candidates, and contradictions. |
| `15-reconstruction-relevance` | Cross-cutting | Strong | Gameplay importance, reuse, unknown-unlock leverage, classification, interface anchors, and ordered priorities. |
| `16-misc-unknown` | Cross-cutting | Strong | Unowned wrapper forests, buffer/string/map candidates, unattributed vtables, records, exclusions, and next actions. |

All required partitions are present: 17 JSON files, 17 Markdown files, 10 semantic-domain partitions, six cross-cutting partitions, and one inventory partition. Presence does not imply complete objective coverage; several partitions remain partial.

## Objective coverage summary

| Objective | Overall status | Main result |
|---|---|---|
| O1: vtable archaeology | Strong | Bounded candidate, slot, SDK-association, family, consumer, and contradiction archaeology; no complete global owner map. |
| O2: class/struct recovery | Strong | Broad static structure, field, record, interface, and embedded-layout recovery; semantic identity and ownership remain bounded. |
| O3: field archaeology | Strong | Strong high-value offset, read/write, and shared-layout evidence; not a complete semantic field graph. |
| O4: lifecycle | Partial | Strong phase taxonomy and selected sequences; global order, cleanup pairing, and runtime confirmation remain open. |
| O5: class families | Partial | Substantial inventory and some address-bearing trees; most family nodes remain naming-only. |
| O6: reconstruction value | Strong | Strong research prioritization and boundary assessment; not implementation authorization or behavior proof. |

Overall assessment: the artifacts provide a strong static archaeology package and a reliable bounded reconstruction plan, but not a complete original-runtime or ABI-complete report.

## Objective details

### O1 — vtable archaeology

**Strengths**

- Records 3,081 candidate bases, 369 high-confidence candidates, 871 medium-confidence candidates, 1,841 low-confidence candidates, 20 labels, 16,107 shared-slot clusters, and 300 pair clusters.
- Provides a 33-record high-value union with implemented, inherited, overridden, and unknown slot status, raw method targets, SDK associations, and consumer counts.
- Bounds key families including `cCellModeStrategy`, `PropertyList`/`DirectPropertyList`, `cEditor`, `cToolStrategy`, IO/`PFRecord`, and selected application/UI/resource families.
- Records twelve prefix chains and two 21-slot UTFWin bases as structural evidence.

**Gaps**

- No global owner assignment for candidate bases.
- No complete method-address/slot-name map for all candidates.
- No RTTI-backed or independently corroborated hierarchy.
- Mixed UTFWin/Sporepedia candidate contamination remains unresolved.
- 4,384 unknown-vtable implementation rows and thousands of unlabeled candidates remain without a complete owner map.

Evidence: `11-vtable-archaeology.json`, `11-vtable-archaeology.md`, `14-class-families.json`, `14-class-families.md`.

### O2 — class and struct recovery

**Strengths**

- The controlling inventory records 2,035 Ghidra structures, 25,546 fields, and 1,895 SDK XML structures while preserving distinct historical populations.
- Semantic-domain partitions enumerate core, entity, creature, world/planet, empire/space, editor/UI, event, persistence, asset, and manager types with selected sizes, fields, vtables, and contracts.
- Layouts generally separate SDK/community provenance, Ghidra export evidence, and current-source comparison.
- Embedded vtable/interface layouts are well represented.

**Gaps**

- Row-level reconciliation of 1,895 SDK structures versus 2,035 Ghidra structures is incomplete.
- Large tails such as `cCellObjectData`, `cTribe`, `cVehicle`, `cGameDataUFO`, and `cCreatureBase` retain opaque fields.
- Structural embedding is not promoted to language-level inheritance without RTTI.
- Complete semantic field/type identity is not available for every structure.

Evidence: `00-corpus-inventory.json`, `00-corpus-inventory.md`, semantic-domain artifacts `01` through `10`, and `12-field-archaeology.json`.

### O3 — field archaeology

**Strengths**

- Fifteen high-value offset groups cover CellGame, CellObjectData, query, Cell references, advection, Cell records, Space/Empire, input, EASTL, resources, inventory, UTFWin, and Space UI/editor surfaces.
- Material rows carry candidate structure, offset, consumer VA, access mode, behavior, evidence, and provenance.
- Six shared layouts are identified, including `cCellDataReference`, `ResourceKey`, `eastl::map`, `eastl::vector`, inventory base, and UTFWin `Window`.
- Observed offsets are separated from inferred or unknown meanings.

**Gaps**

- `cCellObjectData +0x100..+0x358` lacks complete AI, damage, projectile, health, and animation semantics.
- Query insertion, removal, partition, and iteration order remain unresolved.
- Unresolved shared-state and editor/UI fields retain incomplete meanings.
- Ownership, nullability, and runtime-value relationships are not complete for all exported fields.
- The artifacts do not classify every one of the 25,546 fields semantically.

Evidence: `12-field-archaeology.json`, `12-field-archaeology.md`, `01-simulator-core.json`, and `05-empire-space.json`.

### O4 — lifecycle

**Strengths**

- Construction, initialize, register, enter/update, replace/reuse, exit, and dispose/destroy are explicitly separated.
- Records cover mode managers, Cell mode, CellGame, pools, CellGFX, CellUI, inventory/trading, communications, star regeneration, message manager, editor, species profile, and animation boundaries.
- The 28-byte pool, 920-byte element, 4,096 capacity, first-word free-list/self-index behavior, Cell GFX rebuild, and rollover pool are characterized.
- Registration and release-before-replace patterns are recorded for selected systems.

**Gaps**

- No complete application/mode/Simulator/Cell/UI/message/resource bootstrap or shutdown order exists.
- Exact ISimulatorStrategy registration and update order is unresolved.
- Destructor, AddRef, and Release balance for pooled, cached, message, and service objects is incomplete.
- Listener removal, service deregistration, event completion, and removal order are incomplete.
- No positive original runtime trace validates lifecycle relations.

Evidence: `13-lifecycle.json`, `13-lifecycle.md`, `02-gameplay-entity.json`, `07-event-message.json`, and `10-managers-registries.json`.

### O5 — class families

**Strengths**

- The family artifact inventories 1,250 class/interface nodes, 278 ctor/dtor records, and 18 factory candidates.
- Address-bearing trees exist for App, DefaultRefCounted, IUnmanagedMessageListener, Resource, IO, Object, and other interface families.
- SDK family associations, vtable-family associations, concrete anchors, and reconstruction relevance are cross-referenced.
- Twelve explicit prefix chains and two UTFWin bases provide structural anchors.

**Gaps**

- Only 33 nodes have class-specific binary virtual-slot matches; 1,199 families remain naming-only.
- Many descendants have no class-specific binary vtable.
- Candidate families are not uniquely assigned to owners.
- RTTI-backed hierarchy and runtime dispatch proof are absent.
- Namespace, prefix, and mixed-family projection conflicts remain open.

Evidence: `14-class-families.json`, `14-class-families.md`, `11-vtable-archaeology.json`, and `11-vtable-archaeology.md`.

### O6 — reconstruction value

**Strengths**

- Scores, bands, formulas, provenance IDs, uncertainty, domains, and high-leverage unlockers are recorded.
- The artifact distinguishes reproduce-layout, semantic-interface-only, and replaceable-infrastructure classifications.
- Identity, service, input, content, property, serializable, event, animation, player/empire, relationship/trade/mission, and UI anchors are explicit.
- Cross-stage identity, service/lifecycle, Cell, gameplay-owner, editor, and content priorities are ordered.

**Gaps**

- Implementation effort and dependency estimates are intentionally not ranked.
- Gameplay importance and transition ordering lack runtime validation.
- The artifacts do not prove current source matches original behavior.
- Research anchors are not promoted to implementation-ready contracts.
- Implementation authorization and source-replacement decisions are outside scope.

Evidence: `15-reconstruction-relevance.json`, `15-reconstruction-relevance.md`, `02-gameplay-entity.json`, and `09-asset-content.json`.

## Important omissions

| ID | Priority | Status | Topic | Effect |
|---|---|---|---|---|
| `OM-001` | P0 | Missing | Positive original runtime trace | Static operation, transition order, field meaning, event routing, and lifecycle claims cannot be promoted to observed behavior. |
| `OM-002` | P0 | Missing | RTTI and complete class ownership | Candidate families and structural embeddings cannot become a complete C++ hierarchy or unique owner graph. |
| `OM-003` | P0 | Missing | Global vtable-to-owner and slot recovery | Much virtual behavior remains structurally known but semantically unowned. |
| `OM-004` | P0 | Partial | High-value identity and boundary conflicts | The final report must preserve competing claims for projected and mixed type boundaries. |
| `OM-005` | P1 | Missing | Complete field semantics and ownership | Current artifacts support bounded interfaces, not complete field-accurate reconstruction. |
| `OM-006` | P0 | Missing | Global manager and service lifecycle order | Exact original initialization and teardown sequencing cannot be finalized. |
| `OM-007` | P1 | Missing | Message queue and event ordering | Cross-subsystem event order and ownership cannot be claimed. |
| `OM-008` | P1 | Missing | Exact persistence formats and round trips | Architecture is reportable, but exact compatibility and round-trip reconstruction are not ready. |
| `OM-009` | P1 | Missing | Runtime/content gaps | Bounded content records do not support complete original content or runtime reconstruction. |
| `OM-010` | P1 | Partial | Class-family naming-only population | Family trees remain a coverage index and hypothesis map, not a completed class map. |
| `OM-011` | P1 | Partial | Current-source comparison boundary | Current source can support bounded correspondence, not original semantic completion. |
| `OM-012` | P2 | Partial | Population and provenance drift | Counts must retain their population and provenance and must not merge incompatible denominators. |

The principal contradictions to preserve include `cCellModeStrategy` projection overlap, the `0x01490be8` Terrain/Sporepedia attribution, `cGameData` write/teardown interpretation, `cObjectPool` naming, `cCellDataReference` alias boundaries, `cGameData`/`Property` layouts, and message-handler interpretation.

## Highest-value follow-up queries

| ID | Priority | Query | Targets | Required output | Promotion gate |
|---|---|---|---|---|---|
| `Q-001` | P0 | Read-only decompile and disassemble the mixed `0x00b3d220-0x00b3d5a0` accessor region and all direct callers/writers of the `0x0167eac0` packed block; classify each return as pointer, scalar, view, factory, mode-derived, or unresolved. | `0x00b3d220-0x00b3d5a0`; `0x0167eac0`; `0x00b3d300`; `0x00b3d2a0`; `0x00b5b800`; `0x00b21340`; `0x01021260`; `0x01021300`; `0x01021080`; `0x00ba9370` | Per-accessor ABI and return meaning; writer/reader edges; null/sentinel and ownership contract; concrete owner or unresolved status. | Direct field access plus two independent consumers or a corroborated lifecycle chain. |
| `Q-002` | P0 | Recover the 27-slot `cCellModeStrategy` candidate at `0x01485550` against the SDK `IGameMode` order, constructor writes, vtable-reference consumers, and current source slot comments. | `0x01485550`; `0x00e81cf0`; `0x00e552f0`; `0x00e7fc00`; `0x00e81f30`; `0x00e80980`; `0x00e61550`; `0x00e616c0` | Stable slot-to-method table; registration and enter/exit order; unknown-slot classification; original ABI versus clean-room interface separation. | Function-start targets, construction evidence, and a vtable consumer or mode-manager body. |
| `Q-003` | P0 | Carve the unattributed `0x013f1a30` 40-slot candidate against pair clusters, prefix chains, SDK anchors, construction sites, and caller sets. | `0x013f1a30`; `0x013fa974`; `0x01419794`; `0x013f57f8`; `0x013ff648` | Full raw slot vector; slot status; construction and consumer map; corroborated identity only if available. | Stable slot-vector matching plus construction or caller evidence; namespace proximity is insufficient. |
| `Q-004` | P0 | Compare the competing `0x01490be8` Terrain/Sporepedia candidate and mixed UTFWin/Sporepedia 40-slot candidates using exact slot vectors, SDK anchors, construction writes, and all vtable consumers. | `0x01490be8`; `0x01414ed4`; `0x0141873c`; `0x014190d4`; `0x0141930c`; `0x014195ac`; `0x0141ab94`; `0x01441144` | Per-slot method and namespace evidence; construction/base-pointer evidence; resolved or preserved owner ambiguity; candidate-family report. | Two independent structural anchors and a consistent owner explanation. |
| `Q-005` | P0 | Recover serializer, property, and persistence bodies and call sequence: PropertyList Read/Write, ClassSerializer Read/Write, persistence access/load paths, and representative callers. | `0x006a2f60`; `0x006a1540`; `0x00692880`; `0x00693dd0`; `0x00b3d440`; `0x00b2e010`; `0x00b2d7c0`; `0x00c7f060` | Exact read/write order; count/version/checksum/pointer rules; owner and failure behavior; oracle-backed round-trip evidence. | Bodies plus at least one original `.prop` or `.spo` oracle and reproducible round trip. |
| `Q-006` | P0 | Trace Cell per-frame and pool/Gfx lifecycle bodies and their GFX release/rebuild callees, including unnamed arguments and continuation order. | `0x00e806b0`; `0x00e5b2e0`; `0x00e780a0`; `0x00e74a20`; `0x00e80ba0` | Frame/lifecycle call graph; register/argument contracts; pool release/recreate and GFX ownership order; field reads/writes mapped to Cell types. | Multiple consumer bodies and positive original trace for runtime-order claims. |
| `Q-007` | P1 | Perform a field-use closure for `cCellObjectData +0x100..+0x358` and `cCellQueryLinkedPool` entry/header fields across combat, animation, query, rendering, and save/load consumers. | `cCellObjectData +0x100..+0x358`; `cCellQueryEntry +0x00..+0x17`; `0x00e57460`; `0x00e58980`; `0x00e57340`; `0x00e6d200`; `0x00e58ef0`; `0x00e58e30` | Per-field read/write/use table; owner and lifecycle role; AI/combat/animation/query classification; unknown-field list. | Cross-consumer agreement; one decompiler field name or current source name is insufficient. |
| `Q-008` | P1 | Recover message queue registration and dispatch: listener/handler/entry registration, queue processing, send/post, removal, and UTFWin propagation. | `0x00883b20`; `0x008841f0`; `0x008847f0`; `0x008854a0`; `0x00885980`; `0x00885a20`; `0x00960250`; `0x00960310` | `0x18`-byte queue record; priority/tie/handled-result rules; listener ownership and removal; UTFWin bubble behavior. | Corrected calling conventions and a representative dispatch trace. |
| `Q-009` | P1 | Carve the unowned forwarding forest and opaque map family together, correlating forwarding roots, map lookup, mutation, and consumers. | `0x00f47380`; `0x00f473a0`; `0x009276c0`; `0x009289f0`; `0x00e5c780`; `0x00ba8420`; `0x00b21340` | Register/stack ABI; allocation/release or map mutation boundary; owner and return meaning; retirement or demotion of source-purpose labels. | Exact register/stack contract and stable consumer evidence; fan-in is insufficient. |
| `Q-010` | P1 | Recover the paired record ABI from its constructor and at least two independent consumers, including 27-field/24-field offsets, sentinels, allocation, release, and serialization status. | `0x00e39ab0`; `0x00e39420`; `0x00e39450`; `0x00b316c0`; `0x0168de78` | Two record layouts; field offsets and types; allocation/consumer ownership; serialization or explicit runtime-only status. | Constructor and independent consumer agreement; retain inference if absent from SDK export. |
| `Q-011` | P1 | Trace star/planet generation and persistence bodies, record creation, graphics, terrain, and weather load/unload paths. | `0x00bb4af0`; `0x00bb4100`; `0x00bb5b50`; `0x00ba6300`; `0x00f968b0-0x00fa5610` | Generation formula/order map; record-to-live object graph; weather/terrain lifecycle; serialization order and ownership. | Bodies plus original-process or byte-level generation/serialization evidence. |
| `Q-012` | P1 | Resolve the `cCellDataReference` alias and typed reference variants using function comparison, construction/callers, and the Cell reference graph. | `0x00e82340`; `0x00e82420`; `cCellDataReference_` and typed variants; `0x00e58ef0` | Alias/function identity; reference cache and release contract; typed reference resolution; serialized ID versus runtime pointer distinction. | Construction, caller, and field-access agreement; retain both addresses if unresolved. |
| `Q-013` | P2 | Recover editor and animation message dispatch from `cEditorAnimEvent` through IAppSystem into animated-creature/animation-world consumers. | `0x0059d8b0`; `0x0059d840`; `0x00587270`; `0x00591fa0`; `0x00e6d200`; `0x00e66840` | Message/event ID mapping; payload ownership; animation consumer and ordering; original versus current CellAnim boundary. | Typed body chain from producer to final animation/pose consumer. |

## Report support

The current artifacts can support a final research report at the conditional static-report level.

Supported scope:

- Static evidence inventory and provenance.
- Coverage and uncertainty matrix for all six objectives.
- Bounded vtable, structure, field, lifecycle, class-family, and reconstruction-value synthesis.
- Semantic partition index with cross-artifact contradictions.
- Research-only reconstruction anchors, priorities, and evidence gates.

Unsupported scope:

- Original runtime behavior claims.
- Complete C++ class hierarchy or complete vtable ownership.
- Complete field semantics for all structures.
- Exact global initialization and teardown order.
- Exact PROP or SPO wire compatibility and round-trip claims.
- Implementation authorization or source-replacement decisions.

Recommended report position: publish as a static archaeology and reconstruction-planning report with explicit evidence ceilings, preserved contradictions, and follow-up gates. Do not describe the artifacts as runtime-complete, ABI-complete, or implementation-ready.

## Integrity and determinism

- Written files: `knowledgegraph/research/types/18-audit-coverage.json` and `knowledgegraph/research/types/18-audit-coverage.md`.
- Worker artifacts modified: no.
- Source, `SPORE/`, Ghidra state, history, and knowledge graph modified: no.
- Timestamps present: no.
- Proprietary payloads reproduced: no.
- Arrays and tables use stable IDs, objective IDs, partition IDs, paths, or priority order.
- Evidence and assessment vocabulary is limited to stable statuses and does not introduce generated-time data.
