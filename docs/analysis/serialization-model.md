# Serialization model

**Status:** bounded static synthesis; no original-process serialization or save/load oracle.

This document describes the serialization boundaries recovered for the OpenSpore clean-room project. The controlling model is `knowledgegraph/research/gameplay-data-model.json`; `knowledgegraph/research/data-model/09-save-load-persistence.json`, `10-serialization.json`, `17-persistence-synthesis.json`, and audits `19-evidence-audit.json` through `24-final-scope-audit.json` are clarification/control records for persistence details, serializer surfaces, synthesis, evidence limits, graph direction, coverage, determinism, consistency, and scope. The conclusions below are not a claim of byte-perfect reproduction, complete format recovery, or runtime validation.

The canonical dossier inventories 21 deterministic JSON artifacts. Audits 19-21 retain a staged DM01-DM18 worker scope, while audits 22-24 validate the canonical report, determinism, cross-document consistency, and local-worktree scope. `knowledgegraph/research/data-model/19-evidence-audit.json:3-21`; `knowledgegraph/research/data-model/21-mission-coverage-audit.json:3-24`; `knowledgegraph/research/data-model/22-final-determinism-validation.json:111-137`; `knowledgegraph/research/data-model/23-final-consistency-review.json:122-343`; `knowledgegraph/research/data-model/24-final-scope-audit.json:245-252`.

## Evidence and interpretation rules

The canonical evidence vocabulary is used as follows:

| Level | Meaning in this document |
|---|---|
| `VERIFIED` | Directly established by a local-worktree layout/dossier, deterministic decoder/test, frozen export, or pinned read-only query for the stated bounded claim. It is not automatically original runtime truth. |
| `CONFIRMED` | A targeted static body or exact read-only query with corroborating structure or xref. It remains static evidence. |
| `SUPPORTED` | A structure, interface, or multiple static artifacts support a bounded relationship without runtime confirmation. |
| `INFERRED` | A bounded interpretation of static names, layouts, call shape, or cross-artifact agreement. Exact order, coverage, or survival remains unproved. |
| `UNKNOWN` | The available evidence is absent, contradictory, or insufficient. |
| `OBSERVED_CURRENT` | Current OpenSpore source, tests, or fixtures establish current behavior only. |
| `OBSERVED_NEGATIVE` | A local-worktree negative result, such as the absence of a successful original Cell Stage or save/load trace; absence of evidence is not evidence of absence. |

The canonical model requires static/current/runtime separation and says that no original-process gameplay, editor, save, or load trace is available. SDK names, offsets, vtable surfaces, and static bodies do not establish undocumented behavior, exact function identity, byte order, or runtime ownership. See `knowledgegraph/research/gameplay-data-model.json:4357-4382` and `knowledgegraph/research/data-model/19-evidence-audit.json:23-35,78-84`.

The persistence policy in the synthesis is especially important: a field is not called save-surviving merely because it exists in a structure. A survival claim requires an explicit persisted field, explicit write/read codec, or static write/read relationship tied to the boundary. A layout alone is insufficient. `knowledgegraph/research/data-model/17-persistence-synthesis.json:80-92`.

## Model at a glance

The recovered model has several distinct layers. They may share a resource identity, but they do not share one proven wire format.

```text
DBPF type/group/instance
          |
          v
bounded record bytes --[direct TypeID schema; VERIFIED]--> static content value
          |
          v
cCellDataReference_/resource cache --[lazy runtime resolution; VERIFIED]--> live Cell content
          |
          v
cCellGame pools, queries, GFX, and cCellSerializableData
          |
          |  only this is a mode-specific persistence candidate;
          |  its exact Write/Read wire is UNKNOWN
          v
cGamePersistenceManager + ClassSerializer + ISimulatorSerializable + PropertyList
          |
          v
saved-game records/load context --[outer .spo framing, order, migration: UNKNOWN]--> load
```

This is a bounded architectural relationship, not a recovered execution trace. The canonical graph separates `N-CELL-CONTENT`, `N-CELL-RUNTIME-STATE`, `N-CELL-SAVE-STATE`, `N-SAVE-DATA`, and `N-OBJECT-REGISTRY`; `N-OBJECT-REGISTRY` is an analytical adapter boundary rather than a universal original ABI. The graph has 32 nodes, 48 source edges, 49 normalized edges after the disclosed supporting planet-surface node/edge, and 10 source flows plus one derived flow. Its `package` fields are reconstruction-package assignments, while central-structure IDs are a centrality index with aliases, not additional graph nodes or original ownership claims. `knowledgegraph/research/gameplay-data-model.json:445-510,1093-1125,2210-2250`; `knowledgegraph/research/data-model/20-graph-audit.json:95-123`.

A second, independent diagram shows the property/object surfaces:

```text
PropertyList <---- explicit stream Read/Write ----> property entries
     ^                         [bytes/parent/version: UNKNOWN]
     |
     +-- local uint32 property IDs + typed Property values
     +-- parent lookup overlay at runtime

ClassSerializer <---- Attribute callbacks ----> binary/text object stream
     |                                             [order/pointer table: UNKNOWN]
     v
ISimulatorSerializable implementations
     +-- cCellSerializableData
     +-- cGameData-derived objects
     +-- cEmpire, cMission, cStarRecord, and related owners
```

`knowledgegraph/research/data-model/17-persistence-synthesis.json:1154-1186` supplies the serializer split; the canonical graph uses `N-SAVE-DATA -> N-OBJECT-REGISTRY` for inferred load reconstruction, with pointer restoration unresolved. `knowledgegraph/research/gameplay-data-model.json:1346-1360,2210-2239`.

## 1. Packaged content and direct fixed-layout records

### Package boundary

A DBPF record is selected by the complete `typeID/groupID/instanceID` identity. The package index provides a record extent and bounded payload bytes; current OpenSpore additionally handles QFS decompression at that boundary. The current provider is a one-package read seam, not proof of original multi-package precedence, cache ownership, directory behavior, or write integration.

**Evidence:** `VERIFIED` for identity-to-bytes and the current DBPF/QFS read boundary; `SUPPORTED` for the broader original resource architecture. Provenance: `knowledgegraph/research/data-model/17-persistence-synthesis.json:609-630,1370-1378,1480-1545`; `knowledgegraph/research/gameplay-data-model.json:513-555`.

Conceptual DBPF identity is `type/group/instance`. The strongest `ResourceKey` memory-layout evidence is not the same thing as conceptual identity: the synthesis retains an `instance/type/group` memory-layout caveat and requires explicit conversion before assigning a serialized field order. `knowledgegraph/research/data-model/17-persistence-synthesis.json:1368-1388`; `knowledgegraph/research/data-model/19-evidence-audit.json:57-62`.

### Direct Cell records versus envelope/object serialization

The recovered Cell records are direct, TypeID-specific, fixed-size or count-prefixed layouts. They do **not** demonstrate a generic CellSerializer name/ID envelope. Pointer-shaped slots that occur inside a record are preserved content bytes or reference slots, not host addresses and not automatically serialized runtime pointers.

| TypeID | Record | Recovered layout | Envelope | Classification / evidence |
|---|---|---|---|---|
| `0x2A3CE5B7` | `cCellGlobalsResource` | Fixed 276 bytes; 69 consecutive fields | None | Static asset/template; `VERIFIED` |
| `0xDFAD9F51` | `cCellCellResource` | Fixed 796 bytes; identity, AI, size/eat data, behavior, and references | None | Static asset/template; `VERIFIED` |
| `0x9B8E862F` | `cCellWorldResource` | `16 + 12*numPopulate + 24*numAdvect` bytes | None; pointer-shaped slots are preserved framing/reference slots | Static content; `VERIFIED` |
| `0xDA141C1B` | `cCellPopulateResource` | `16 + 76*numMarkers` bytes | None | Static spawn/distribution content; `VERIFIED` |
| `0x4B9EF6DC` | `cCellStructureResource` | `28 + 40*numAttachments` bytes | None | Static Cell content with instance-like references; `VERIFIED` |
| `0xD92AF091` | `cCellLootTableResource` | `36 + 28*numEntries` bytes | None | Static reward/effect content; `VERIFIED` |
| `0x433FB70C` | `cCellEffectMapResource` | `8 + 28*numEntries` bytes | None | Static presentation/content; `VERIFIED` |
| `0x612B3191` | `cCellBackgroundMapResource` | `8 + 16*numEntries` bytes | None | Static presentation/content; `VERIFIED` |
| `0x8C042499` | `cCellLookTableResource` | `8 + 8*numEntries` bytes | None | Static Cell content; `VERIFIED` |
| `0xDBA35AE2` | `cCellLookAlgorithmResource` | `8 + 20*numEntries` bytes | None | Static selection content; `VERIFIED` |
| `0xF9C3D770` | `cCellRandomCreatureResource` | `8 + 28*numEntries` bytes | None | Static spawn tuning/content; `VERIFIED` |
| `0x754BE343` | `cCellPowersResource` | Fixed 8 bytes: teleport cost/range | None | Static content; `VERIFIED` |

The table is the direct-record serializer set summarized in `knowledgegraph/research/data-model/17-persistence-synthesis.json:1043-1152`. The record-level detail and content/runtime separation are in `knowledgegraph/research/data-model/10-serialization.json:140-505` and `knowledgegraph/research/gameplay-data-model.json:2459-3339`.

The direct record layouts are a content serialization schema, not profile or save-game state. They describe what can be decoded from a record; they do not establish an original writer, a higher-level container, exact runtime selection, or a save/load round trip. `knowledgegraph/research/data-model/10-serialization.json:1485-1510`; `knowledgegraph/research/data-model/17-persistence-synthesis.json:1043-1170`.

A historical claim that these records used a CellSerializer name/ID envelope is explicitly superseded for the recovered direct Cell TypeIDs. Generic CellSerializer wire behavior remains `UNKNOWN` unless a different record family is found that does not match the direct schemas. `knowledgegraph/research/data-model/10-serialization.json:109-114,1831-1882`; `knowledgegraph/research/gameplay-data-model.json:17-18`.

### Cell resource and lazy reference boundary

`cCellResource` couples a resource byte buffer and size with a `CellSerializer*` association and a `ResourceKey`. `cCellDataReference_` is a runtime handle keyed by instance ID and serializer context. Its create/acquire path increments a counter, lazily resolves the resource, and retains the loaded resource; teardown/decrement paths clear or release it.

This is a resource-loader relationship:

```text
(instance ID + serializer context)
             |
             v
 cCellDataReference_ cache/counter
             |
             +----> cCellResource bytes + resource key
             |
             +----> TypeID-specific direct Cell decoder
```

The stable identity is the content identity. `mpSerializer`, `mpResource`, and the counter are runtime linkage/ownership state and are not proven serialized fields. Exact record selection, failure behavior, release order, and package precedence remain bounded or unresolved. **Evidence:** `VERIFIED` for lazy resolution and counter/cache operations; `SUPPORTED` for the broader loading relation; `INFERRED` for exact loader selection. `knowledgegraph/research/data-model/10-serialization.json:692-723,899-914,1196-1256`; `knowledgegraph/research/data-model/17-persistence-synthesis.json:1370-1408`.

The canonical graph explicitly says that lazy Cell references resolve record bytes and direct Cell templates, not runtime state. `knowledgegraph/research/gameplay-data-model.json:603-619`.

## 2. Property and PropertyList serialization

### Runtime structure

`App::PropertyList` is a mixed runtime/persistence boundary:

- size: 56 bytes;
- local sorted map of `uint32` property ID to `Property` at `0x18`;
- parent `PropertyList*` at `0x30`;
- operation counter at `0x34`.

`DirectPropertyList` is a specialization with parent/fast-access/temporary runtime state. Its `Read` and `Write` paths are observed, but fast-access values and temporary `Property` state do not establish a separate file format. `knowledgegraph/research/data-model/10-serialization.json:561-602`; `knowledgegraph/research/data-model/17-persistence-synthesis.json:1154-1161,1624-1629`.

Runtime behavior is explicit:

- `SetProperty` inserts or updates a local property by `uint32` ID and increments the operation counter;
- `GetProperty` searches the local map first and then falls back to the parent;
- mutation by `SetProperty` does not imply an automatic save.

These are `VERIFIED` static relationships. The operation counter has unresolved semantics and must not be treated as a persisted field. `knowledgegraph/research/data-model/10-serialization.json:851-873,1032-1050`; `knowledgegraph/research/data-model/09-save-load-persistence.json:581-586,720-737`.

### Stream shape

`App::PropertyList::Write` at `0x006A1540` and `App::PropertyList::Read` at `0x006A2F60` provide explicit stream boundaries. The supported shape is:

```text
count/framing
    +--> uint32 property ID + typed Property value
    +--> uint32 property ID + typed Property value
    +--> ...
```

A negative-count branch appears to read additional words and resolve a parent, but its exact semantics are unresolved. A 24-byte-per-entry value is a decompilation-derived clue, not a complete value encoding proof. Exact `Property` bytes, ordering, parent encoding, compression, version negotiation, and round-trip behavior remain `UNKNOWN`. `knowledgegraph/research/data-model/10-serialization.json:570-583,1415-1437`; `knowledgegraph/research/data-model/09-save-load-persistence.json:680-700`.

The retained `Property` type tags are:

| Type | ID |
|---|---:|
| None | 0 |
| Bool | 1 |
| Int32 | 9 |
| UInt32 | 10 |
| Float | 13 |
| String8 | 18 |
| String16 | 19 |
| Key | 32 |
| Text | 34 |

The broader dossier also lists vector, color, transform, and bounding-box type IDs, but C002 remains `UNRESOLVED`: the SDK source describes a 20-byte `Property` with a value union and later flags/type offsets, while the imported Ghidra structure is 4 bytes with flags/type. Neither layout is promoted to an authoritative runtime or wire representation. Preserve both source-specific claims until allocation-size, constructor, getter, and typed-value evidence resolves them; no wire contract can safely be inferred from either layout alone. `knowledgegraph/research/data-model/15-cross-track-evidence-ledger.json:1007-1022`; `knowledgegraph/research/data-model/09-save-load-persistence.json:397-418`; `knowledgegraph/research/data-model/10-serialization.json:524-559`; `knowledgegraph/research/data-model/19-evidence-audit.json:61-62`.

### PROP boundary

The `.prop`/`PROP` identity is known, but the exact outer record envelope, property ordering, parent encoding, value bytes, and round trip are not. `App::PropertyList` is therefore supported as an explicit stream substrate, not as an exact `.prop` implementation. **Evidence:** `SUPPORTED` for the codec surface; `UNKNOWN` for the wire format. `knowledgegraph/research/data-model/10-serialization.json:140-155,1415-1437`.

## 3. Object serializers and field descriptors

### `ClassSerializer` and `Attribute`

`ClassSerializer` is a runtime serializer authority, not itself a saved profile record. Its static layout contains:

- `attributes[128]` at `0x00`;
- `count` at `0xA00`;
- `countSerialized` at `0xA04`;
- `id` at `0xA08`;
- `pObject` at `0xA0C`;
- `pAttributes` at `0xA10`.

`Attribute` is a 60-byte descriptor with a name, `uint32` ID, offset, current-object pointer, and binary/text read/write callbacks. The known architecture is an ordered/binary-searchable attribute table with callbacks; the concrete class registry, field order, object-pointer table, version gates, rollback, and text/binary wire framing are unresolved. **Evidence:** `SUPPORTED` architecture, `UNKNOWN` concrete wire. `knowledgegraph/research/data-model/10-serialization.json:603-642,875-886`; `knowledgegraph/research/data-model/17-persistence-synthesis.json:1171-1177`.

The SDK semantic addresses and the current triage/containing entries are not interchangeable without body evidence. The synthesis retains `0x006928C0/0x00693DE0` as SDK anchors and `0x00692880/0x00693DD0` as alternate/containing entries; nearby current bodies do not establish serializer implementation. **Evidence:** `SUPPORTED_AS_ARCHITECTURE_ONLY`; address/body contradiction remains open. `knowledgegraph/research/data-model/17-persistence-synthesis.json:1171-1177,1251-1266`; `knowledgegraph/research/data-model/19-evidence-audit.json:63-69`.

### `ISimulatorSerializable`

`ISimulatorSerializable` is the explicit object-level contract supplying `Write`, `Read`, `WriteToXML`, and identity/noun-object slots in the static object family. The interface proves serialization eligibility, not complete field coverage for every subtype. `cGameData` and derived owners such as `cEmpire`, `cMission`, `cMissionManager`, `cCollectableItems`, `PlayerPlanetData`, `cSpaceTradeRouteManager`, and `cCommEvent` have bounded static serialization relationships, but their concrete field lists and restore order are not fully recovered.

**Evidence:** `VERIFIED` for the interface surface; `SUPPORTED` for the named owner relationships; `UNKNOWN` for field-level write/read coverage and pointer restoration. `knowledgegraph/research/data-model/17-persistence-synthesis.json:358-371,413-438,580-589,805-810,1709-1731,1781-1785`.

### `CellSerializer` and field IDs

`CellSerializerField` contains a name, `uint32` field ID, serializer type, size, offset, callbacks, and flags. `CellSerializer` contains a name, field pointer, field count, `mVersion`, flags, and callbacks. These structures establish descriptor metadata, not the actual field ID table or generic wire envelope.

| Identifier surface | Known structure | What is known | What remains unknown |
|---|---|---|---|
| `CellSerializerField::mID` | `uint32` at `0x04` | Field-ID slot exists | Concrete values and per-record assignment |
| `CellSerializerField::mOffset` | `uint32` at `0x10` | Metadata offset exists | Binary emission order |
| `CellSerializerField::mSize` | `uint32` at `0x0C` | Metadata size exists | Whether size is wire size, field size, or a callback hint |
| `ClassSerializer::id` | `uint32` at `0xA08` | Class/object ID slot exists | Class registry and object mapping |
| `Attribute::id` | `uint32` at `0x04` | Attribute ID slot exists | Attribute IDs, serialized flags, and concrete callbacks |
| Property IDs | `uint32` map key | Local property lookup key exists | Definition-name mapping, parent wire relation, complete value encoding |

The important correction is that no recovered direct Cell record demonstrates a name/ID envelope. `CellSerializer` remains a runtime loading/descriptor boundary unless a different record family proves another use. **Evidence:** `VERIFIED` metadata layout; `UNKNOWN` generic descriptor stream and field-ID values. `knowledgegraph/research/data-model/10-serialization.json:645-689,1466-1483`; `knowledgegraph/research/data-model/17-persistence-synthesis.json:1163-1170,1480-1547`.

### `cCellSerializableData`

`cCellGame` holds an intrusive `cCellSerializableData*` at offset `0x5190`. The 236-byte object is the explicit Cell runtime serializable-state holder and a strong persistence candidate. The field layout is:

| Offset | Field | Persistence interpretation |
|---:|---|---|
| `0x0C` | `mGameMode` | Cell game mode candidate |
| `0x10` | `mPlayerCreatureKey` | Player creature identity candidate |
| `0x1C` | `mFoodProgression` | Food progression candidate |
| `0x20` | `mPlantFoodProgression` | Plant-food progression candidate |
| `0x24` | `mOverPlantFoodProgression` | Over-plant-food progression candidate |
| `0x28` | `mOverAnimalFoodProgression` | Over-animal-food progression candidate |
| `0x2C` | `mEvolutionPointsSpent` | Spent progression candidate |
| `0x34` | `mUnlockedParts[13]` | Unlocked-part state candidate |
| `0x6C` | `mKillCount` | Counter candidate |
| `0x70` | `mDeathCount` | Counter candidate |
| `0x74` | `gameTimeMS` | Elapsed game-time candidate |
| `0x78` | `gameID` | Game identity candidate |
| `0x7C` | `difficulty` | Difficulty candidate |
| `0x80` | `missions[6]` | Cell mission-state candidate |
| `0xE0` | `playerHasMoved` | Telemetry/progression flag candidate |
| `0xE1` | `playerHasEaten` | Telemetry/progression flag candidate |
| `0xE2` | `mFirstEditorEntry` | Editor-entry progression flag candidate |
| `0xE4` | `mNanites` | Nanite-state candidate |
| `0xE8` | `mNanovirusActive` | Nanovirus-state candidate |
| `0xE9` | `mAddedStartTelemetry` | Telemetry flag candidate |

The object is held by `cCellGame`, while the Cell pool, query pools, world references, avatar index, and display/GFX state are runtime state. `cCellSerializableData` is not the same thing as a direct Cell content record. The actual Write/Read order, whether every listed field is emitted, default/reset semantics, and cross-stage handoff are `UNKNOWN`. **Evidence:** `SUPPORTED` ownership/serializable candidate; `VERIFIED` for the bounded layout; `UNKNOWN` for wire coverage. `knowledgegraph/research/data-model/09-save-load-persistence.json:339-383`; `knowledgegraph/research/data-model/10-serialization.json:726-757`; `knowledgegraph/research/data-model/17-persistence-synthesis.json:258-281,815-823`.

`cCreatureGameData` is a separate progression owner for brain level, evolution points, learned abilities, and ability mode. C014 remains `UNRESOLVED` for field typing: the SDK/export labels `cCreatureGameData+0x08` as an integer-like flap field, while static writes to the corresponding global use float-sized operations. Retain the export label, but do not promote the field's runtime type or semantic identity, and do not use it as a current or original serialization field. Its relationship to Cell evolution/food state is related but not synchronized in the evidence. Do not merge the two structures or assume automatic handoff. **Evidence:** `SUPPORTED_AS_LAYOUT_WITH_UNRESOLVED_HANDOFF`; `knowledgegraph/research/data-model/15-cross-track-evidence-ledger.json:1220-1234`; `knowledgegraph/research/data-model/09-save-load-persistence.json:552-560`; `knowledgegraph/research/data-model/17-persistence-synthesis.json:375-382,1937-1951`.

## 4. Saved-game header, load context, and orchestration

### Header and load context

`cSavedGameHeader` is a declared 104-byte saved-game header architecture with:

- file major/minor version at `0x0C/0x10`;
- object-count map at `0x14`;
- timestamp at `0x30`;
- game mode at `0x54`;
- snapshot flag at `0x58`;
- current planet `ResourceKey` at `0x5C`.

Its serialized placement, header population, checksum/encryption, and migration behavior are unknown. `GameLoadParameters` is a declared load context with game/star names, creature/species references, creature key, star ID, difficulty, and mode. Its SDK size is marked uncertain, and field consumption is not recovered.

**Evidence:** `SUPPORTED` structural architecture; `UNKNOWN` archive framing and runtime behavior. `knowledgegraph/research/data-model/09-save-load-persistence.json:244-277`; `knowledgegraph/research/data-model/10-serialization.json:760-800`; `knowledgegraph/research/data-model/17-persistence-synthesis.json:665-674,1179-1186`.

`cGamePersistenceManager::Get` at `0x00B3D440` is a verified service lookup for the global persistence manager. The manager layout contains mode markers, unresolved state, flags, a string, and a reference count. A `LoadGame` vtable surface exists; a concrete `SaveGame` body was not found by the read-only named-function search. Missing a `SaveGame` symbol does not mean saving is absent: unnamed vtable, strategy, generic database, or serializer paths remain possible.

**Evidence:** `VERIFIED` for `Get`; `SUPPORTED_AS_SDK_VTABLE_RELATION` for `LoadGame`; `UNKNOWN` for the save operation and transaction. `knowledgegraph/research/data-model/09-save-load-persistence.json:278-304,649-678`; `knowledgegraph/research/data-model/17-persistence-synthesis.json:1204-1231`.

### Save/load entry points

| ID | Entry point | Status | Boundary |
|---|---|---|---|
| `SE01` | `cGamePersistenceManager::Get @ 0x00B3D440` | `VERIFIED` | Service lookup only |
| `SE02` | `cGamePersistenceManager::LoadGame` | `SUPPORTED_AS_SDK_VTABLE_RELATION` | Vtable slot `+0x10`; concrete body, context consumption, and restore order unknown |
| `SE03` | `cGamePersistenceManager::SaveGame` | `UNKNOWN` | No named body; absence of symbol is not absence of capability |
| `SE04` | `PropertyList::Write @ 0x006A1540` | `VERIFIED` | Count/entry dispatch; exact property bytes unknown |
| `SE05` | `PropertyList::Read @ 0x006A2F60` | `VERIFIED` | Count/entry dispatch; parent/version/atomicity unknown |
| `SE06` | `ClassSerializer::Write` | `SUPPORTED_AS_ARCHITECTURE_ONLY` | SDK anchor `0x006928C0` versus alternate `0x00692880`; body/framing unknown |
| `SE07` | `ClassSerializer::Read` | `SUPPORTED_AS_ARCHITECTURE_ONLY` | SDK anchor `0x00693DE0` versus alternate `0x00693DD0`; pointer remapping unknown |
| `SE08` | `cGameData::Write / Read` | `SUPPORTED_AS_SDK_VTABLE_ANCHORS` | SDK anchors `0x00B184D0/0x00B18540`; field bodies unresolved |
| `SE09` | `cCellSerializableData::Write / Read` | `SUPPORTED_AS_INTERFACE` | Concrete body/address, field coverage, defaults, and handoff unknown |
| `SE10` | `cStarManager` database persistence routine `0x00BB4BA0` | `SUPPORTED_BOUNDED_MECHANICS` | Writes `stars.db.tmp` and replaces `stars.db`; not a general save transaction |
| `SE11` | `cScenarioResource::Write @ 0x00F25E00` | `INFERRED` | Stream calls are bounded; field order and property placement unknown |
| `SE12` | `cScenarioResource::Read` | `INFERRED` | SDK anchor `0x00F2FC40` versus containing-function repair `0x00F2F830`; body unknown |
| `SE13` | `EditorModel::Load / Save` | `SUPPORTED_AS_SDK_AND_STATIC_ANCHORS` | `0x004AE8D0/0x004AF780`; authored asset boundary, not profile save |
| `SE14` | `cCreatureDataResource::Read / Write` | `SUPPORTED_AS_STATIC_ANCHORS` | `0x004BF970/0x004BFCB0`; wire, header, and validation unknown |
| `SE15` | `Editor_Save @ 0x00577650` | `SUPPORTED_STATIC_BODY` | Constructs asset metadata and submits asset/resource operation; not game-slot persistence |
| `SE16` | Loose Cell catalog/file serializer | `INFERRED` | Reader initializer `0x00E4CAD0`; catalog writer `0x00E4B470`; grammar and precedence unresolved |
| `SE17` | `IConfigManager::SavePreferences / SaveOptionSetup` | `SUPPORTED_AS_INTERFACE` | Vtable operations; format, namespace, migration, and PROP/SPO relation unknown |
| `SE18` | Material/texture manager write operations | `SUPPORTED_API_SURFACE` | Interface-only; no byte schema or gameplay-save relation |

**Provenance:** `knowledgegraph/research/data-model/17-persistence-synthesis.json:1204-1366`; supporting anchors and boundaries are in `knowledgegraph/research/data-model/09-save-load-persistence.json:649-838` and `knowledgegraph/research/data-model/10-serialization.json:976-1237`.

The only defensible orchestration statement is that these surfaces exist and are candidates for a persistence service. The order among header, PropertyLists, object records, databases, and mode reconstruction is `UNKNOWN`; the canonical model explicitly retains the likely architectural sequence as inference rather than a confirmed write/read trace. `knowledgegraph/research/data-model/09-save-load-persistence.json:1050-1056`; `knowledgegraph/research/gameplay-data-model.json:416-443`.

## 5. Field IDs, versioning, and migration

### Field-ID systems

There is no single recovered global field-ID table. The following are separate ID systems:

1. **DBPF/ResourceKey identity:** `typeID`, `groupID`, and `instanceID` identify a package record. The complete triple is authoritative; a group ID is not inferred from a type ID or label.
2. **Cell content references:** instance-like `uint32` values are interpreted according to the surrounding direct Cell schema. A reference's meaning is schema-relative, not a universal serialized object pointer.
3. **Property IDs:** `uint32` keys in local `PropertyList` storage, with parent fallback at runtime. Definition-name/group mappings and the complete property registry are not recovered.
4. **CellSerializer field IDs:** `CellSerializerField::mID` exists, but concrete values and assignment per record are unknown.
5. **Class/object IDs:** `ClassSerializer::id` and `Attribute::id` provide serializer metadata, but the concrete class registry and object-count-to-object mapping are unknown.
6. **Object domain IDs:** political IDs, star IDs, planet IDs, mission IDs, editor hierarchy indices, and noun IDs have domain-specific resolution paths. They are not interchangeable with `ResourceKey` or field IDs.

Identifier contract: IDs are unique within each entity kind/view; intentional reuse across views is reference linkage, not duplicate identity. Global uniqueness across views is not a valid test for this model. `knowledgegraph/research/gameplay-data-model.json:4370-4374`.

Provenance: `knowledgegraph/research/data-model/17-persistence-synthesis.json:1368-1478`; `knowledgegraph/research/gameplay-data-model.json:3497-3602`.

### Version carriers

| ID | Owner/carrier | Known version or compatibility clue | Status |
|---|---|---|---|
| `V01` | `cSavedGameHeader` | `mFileVersionMajor`, `mFileVersionMinor` | `SUPPORTED`; migration `UNKNOWN` |
| `V02` | `cStarRecord` | saved-game major/minor version and timestamp | `SUPPORTED` as layout; consumer gate `UNKNOWN` |
| `V03` | `cScenarioResource` | `mVersion`, `mMarkerPositioningVersion`, deprecated/old fields | `SUPPORTED` as layout; migration body `UNKNOWN` |
| `V04` | `CellSerializer` | `mVersion`, `mFlags` | `SUPPORTED` metadata; direct Cell records do not prove an envelope |
| `V05` | `ClassSerializer`/`ISerializer` | declared serialization-version operations and `countSerialized` | `SUPPORTED` architecture; exact gates/defaults `UNKNOWN` |
| `V06` | DBPF v3 | package major/minor/index fields | `SUPPORTED` current package schema; migration `UNKNOWN` |
| `V07` | GMDL | version 8 tested path | `SUPPORTED` for the tested parser; other versions/migration `UNKNOWN` |
| `V08` | Direct Cell records | TypeID, exact size, and count-span compatibility | `VERIFIED` for decoder invariants; save migration does not apply without a higher-level codec |

**Provenance:** `knowledgegraph/research/data-model/17-persistence-synthesis.json:1480-1547`; `knowledgegraph/research/data-model/09-save-load-persistence.json:1199-1213`.

No compatibility matrix, downgrade policy, migration branch, atomic migration, or defaulting rule is recovered. A version field is evidence of a version carrier, not proof of backward compatibility or automatic migration. `knowledgegraph/research/data-model/17-persistence-synthesis.json:1547`; `knowledgegraph/research/data-model/19-evidence-audit.json:61-69`.

## 6. Ownership and reference resolution

| ID | Reference system | Resolution boundary | Post-load state |
|---|---|---|---|
| `RR01` | DBPF/`ResourceKey` | Original manager/database/factory/cache lookup; current OpenSpore exact TGI lookup in one package | Multi-package precedence and package remapping `UNKNOWN` |
| `RR02` | `ResourceKey` serialized primitive | Conceptual triple is stable, but declared serializer order conflicts with memory-layout evidence | Exact serialized order `UNKNOWN` |
| `RR03` | `cCellDataReference_` | Instance plus serializer context, lazy load, counter, cache | Runtime linkage, not a save pointer |
| `RR04` | Direct Cell content references | World → populate → Cell → structure/loot/look; schema-relative instance-like values | Hard/soft domain validation exists; original lookup/ownership `UNKNOWN` |
| `RR05` | `PropertyList` | Local map first, parent fallback; mutation increments operation counter | Parent persistence and complete round trip `UNKNOWN` |
| `RR06` | Class/object pointers | Class/object ID and attribute metadata with declared pointer operations | Pointer table, remapping, cycle handling, and owner restoration `UNKNOWN` |
| `RR07` | Political/Empire IDs | `cStarManager` empire map and cached current-player empire | Object-count mapping and cross-save ID remapping `UNKNOWN` |
| `RR08` | Star/Planet IDs | `cStarRecord` owns planet records; header carries current planet key | Header/terrain restoration order and live-object resolution `UNKNOWN` |
| `RR09` | Mission IDs | `cMissionManager::GetMissionByID` provides named lookup | Object-count mapping and cross-save remapping `UNKNOWN` |
| `RR10` | Editor hierarchy/composition | Parent/children/symmetry indices and creation keys | Duplicate repair, group/instance allocation, and validation `UNKNOWN` |
| `RR11` | Live noun/game-data ownership | Noun manager, definition/owner/political IDs, intrusive references | Object creation, pointer restoration, destruction cascade, and owner rehydration `UNKNOWN` |

**Provenance:** `knowledgegraph/research/data-model/17-persistence-synthesis.json:1368-1478`; `knowledgegraph/research/gameplay-data-model.json:122-220,1346-1360`.

### Ownership classes

- `Resource::Database`/`IRecord` own record streams and indexes; database write/flush infrastructure exists, but complete commit order is unknown. `knowledgegraph/research/data-model/17-persistence-synthesis.json:1196-1202,1559-1565`.
- `cGamePersistenceManager` is a runtime singleton/service, not a saved record. `knowledgegraph/research/data-model/17-persistence-synthesis.json:1569-1576`.
- `cStarManager` owns saved/starter star records, empire/home-star mappings, PropertyLists, trade routes, collectables, and temporary/main planet databases. Manager-wide transaction semantics are unknown. `knowledgegraph/research/data-model/17-persistence-synthesis.json:1577-1585`.
- `cCellGame` owns the 4096-cell pool, query pools, world references, avatar index, timing/flags, and the intrusive `cCellSerializableData` pointer. The live runtime graph is transient; only the pointed-to object is a persistence candidate. `knowledgegraph/research/data-model/17-persistence-synthesis.json:258-275,1586-1594`.
- `cCellDataReference_` owns cached resource pointers and counters; the serializer pointer, resource pointer, and counter are runtime linkage state. `knowledgegraph/research/data-model/17-persistence-synthesis.json:1595-1603`.
- `cGameNounManager` owns live noun maps/lists and materializes registered game-data instances. The registry is a reconstruction target on load, not the persistence format itself. `knowledgegraph/research/data-model/17-persistence-synthesis.json:1604-1612`; `knowledgegraph/research/gameplay-data-model.json:958-997,1346-1360`.
- `cEditor` owns editor services, input, selection, edit history, animation world, and derived skin. These are predominantly runtime state; the authored asset has a separate load/write boundary. `knowledgegraph/research/data-model/17-persistence-synthesis.json:1613-1621`.
- `PropertyList` owns local entries, parent linkage, and operation state, but only stream entries are persistence candidates. `knowledgegraph/research/data-model/17-persistence-synthesis.json:1622-1629`.
- GFX, resource caches, editor skin, material lookups, and host mesh/texture handles are derived/cache state. Interface-only material/texture writes do not establish profile persistence. `knowledgegraph/research/data-model/17-persistence-synthesis.json:1631-1648`.

## 7. Persistence boundaries

| ID | Domain | Established boundary | Not established |
|---|---|---|---|
| `PB01` | Packaged content | DBPF type/group/instance identity → bounded raw or QFS-decompressed bytes | Original multi-package priority, cache behavior, write order, save integration |
| `PB02` | Typed static content | DBPF bytes → TypeID-specific static values and references | Universal content envelope, profile persistence, original writers |
| `PB03` | PropertyList | uint32 IDs + typed values + count/framing + parent branch | Exact PROP bytes, parent serialization, compression, version handling, whole-save behavior |
| `PB04` | Class/object serialization | ClassSerializer ID, attributes, object context, binary/text callbacks | Concrete bodies, class registry, object-pointer table, order, gates, rollback |
| `PB05` | Mode-specific serializable state | Named `ISimulatorSerializable` objects, including Cell/Empire/Mission/Star candidates | Per-field coverage, object order, cross-stage synchronization, restore effects |
| `PB06` | Header/load context | Header versions/counts/timestamp/mode/snapshot/current planet and load parameters | `.spo` framing, placement, checksum/encryption, slots/profiles, consumption |
| `PB07` | Editor asset persistence | Paired editor resource/model load/write anchors and `Editor_Save` | Common wire format, validation, save-before-dispose, history survival |
| `PB08` | Runtime/derived assets | Resource/GFX/editor/renderer caches and derived products | That cache/derived state is profile data |
| `PB09` | Simulation reset | Fresh mode-local state, Cell pool/query/world setup | Generic reset-versus-save semantics and progression preservation |
| `PB10` | Game-mode transition | Mode A `OnExit` then mode B `OnEnter` | Cross-mode handoff, autosave, universal persistence |

**Provenance:** `knowledgegraph/research/data-model/17-persistence-synthesis.json:609-719`.

## 8. Transition matrices

The tables below report the transition itself and the persistence consequence. “Survival” is intentionally qualified: `UNKNOWN` means the evidence does not establish that the state survives.

### 8.1 Level and stage transitions

| ID | From → to | Entry point | Explicit effects | Survival / evidence |
|---|---|---|---|---|
| `LT01` | Existing Cell world/scale/player state → rebuilt Cell world/scale/player state | `0x00E7FD00` | Reset Cell/UI/GFX, replace world selection, recreate player from start cell, derive scale/time | Static content remains input; live pool/query/display state resets; Cell serializable-state survival `UNKNOWN`; `VERIFIED` |
| `LT02` | Space planet context → planet surface/terrain context | `cPlanetModel::ToSurface @ 0x00B81780` | Named Space-to-surface transition and 55 static callers | Field transformation, generated-terrain resolution, and return ownership `UNKNOWN`; `INFERRED` |
| `LT03` | Scenario play state → selected/jumped act | `cScenarioPlayMode::SetCurrentAct`, `JumpToAct` | Act selection surfaces | Act order, scenario field persistence, and save/load synchronization `UNKNOWN`; `INFERRED` |
| `LT04` | Cell scale change on live object → released and optionally recreated object | `0x00E780A0` | Clear avatar reference, release GFX/query/effect associations, deallocate/recreate | No individual live-object save or cross-stage survival; `SUPPORTED` |

**Provenance:** `knowledgegraph/research/data-model/17-persistence-synthesis.json:721-763`.

### 8.2 Save/load transitions

| ID | From → to | Entry point | Explicit effects | Survival / evidence |
|---|---|---|---|---|
| `SL01` | Saved-game request → serialized records | Exact save entry `UNKNOWN` | Serializer, PropertyList, database, and serializable-object write surfaces exist | No field-level save matrix; `UNKNOWN` |
| `SL02` | `GameLoadParameters` → restored simulator state | `LoadGame` vtable slot `+0x10` | Context includes game/star names, creature/profile, star, difficulty, mode | Consumption and restored-object coverage `UNKNOWN`; `INFERRED` |
| `SL03` | Declared header → saved-game metadata | `cSavedGameHeader` | Versions, object counts, timestamp, mode, snapshot, current planet key | Structural header evidence only; placement and population not runtime-verified; `SUPPORTED` |
| `SL04` | Runtime PropertyList → property stream | `PropertyList::Write/Read` | Count/framing plus property ID and typed-value dispatch | Explicit codec path; exact bytes, parent, round trip `UNKNOWN`; `SUPPORTED` |
| `SL05` | Serializable object → object attribute stream | ClassSerializer anchors and `ISimulatorSerializable` | Attribute metadata and binary/text callbacks | Eligibility supported; field and pointer survival `UNKNOWN`; `SUPPORTED` |
| `SL06` | Cell runtime progression → Cell serializable state | `cCellSerializableData` held at `cCellGame+0x5190` | Mode, creature key, progression, parts, counters, game ID/difficulty, missions, flags | Explicit candidate; per-field emission and round trip `UNKNOWN`; `SUPPORTED` |
| `SL07` | Star/planet database state → `stars.db` through `stars.db.tmp` | `0x00BB4BA0` | Write temporary database and replace main database | Narrow operation supported; full atomicity/rollback/crash consistency `UNKNOWN`; `SUPPORTED` |
| `SL08` | Scenario resource → scenario stream | Write `0x00F25E00`; read anchors `0x00F2FC40/0x00F2F830` | Stream calls, embedded PropertyList, version fields | Exact order and PropertyList placement `UNKNOWN`; `INFERRED` |

**Provenance:** `knowledgegraph/research/data-model/17-persistence-synthesis.json:764-844`; `knowledgegraph/research/data-model/09-save-load-persistence.json:1068-1153`.

### 8.3 Editor operations

| ID | From → to | Entry point | Explicit effects | Survival / evidence |
|---|---|---|---|---|
| `EO01` | Hover/idle → transient mouse/tool state | `cEditor::OnMouseMove @ 0x005737D0` | Store pointer/coordinates and dispatch tool state | Runtime input only; `SUPPORTED` |
| `EO02` | Selection/drag/tool → authored/runtime mutation | `cEditor::OnMouseDown @ 0x00588570` | Hit testing, tool/actor mutations, part state changes | Live EditorModel mutation; durable bytes need asset save; `SUPPORTED` |
| `EO03` | Drag/tool → history commit | `0x0058B650`, `CommitEditHistory @ 0x00586410` | Truncate redo tail, append snapshots, refresh derived state | History transient; no history serialization; `SUPPORTED` |
| `EO04` | History cursor → prior/redone state | `Undo @ 0x0058A5A0`, `Redo @ 0x0058A950` | Restore model/resource state and refresh animation/transform | In-memory only; no persistence claim; `SUPPORTED` |
| `EO05` | Active editor mode → new editor mode | `cEditor::SetActiveMode @ 0x00587270` | Prior-mode cleanup, pose/controller update, enter new mode, event | Model/pose survival across transition not established; `SUPPORTED` |
| `EO06` | Authored editor state → asset metadata/resource save submission | `Editor_Save @ 0x00577650` | Construct metadata and route asset/resource operation | Asset save boundary only; not profile/slot/game-state; `SUPPORTED` |
| `EO07` | Authored model/resource → editor read/write stream | `EditorModel::Load/Save`, `cCreatureDataResource::Read/Write` | Paired asset load/write anchors | Common format, field order, validation, and round trip `UNKNOWN`; `SUPPORTED` |
| `EO08` | Initialized editor → exited/disposed editor | `cEditor::OnExit @ 0x00587A20`, `Dispose @ 0x00576C50` | Release runtime resources and dispose editor shell | Authored core, history, pose, and derived skin survival not established; `SUPPORTED` |

**Provenance:** `knowledgegraph/research/data-model/17-persistence-synthesis.json:846-925`.

### 8.4 Simulation reset

| ID | From → to | Entry point | Explicit effects | Survival / evidence |
|---|---|---|---|---|
| `SR01` | Cell mode absent → initialized | `0x00E81CF0` | Establish Cell game/GFX/UI singletons and reset mode state | Reset/bring-up boundary, not save/load; `SUPPORTED` |
| `SR02` | Uninitialized Cell game → fresh 4096-cell runtime | `cCellGame::Initialize @ 0x00E80BA0` | Reset flags, query pools, 4096-cell pool, time/serializable path, world refs | Live pool/query/display state is fresh; old serializable contents are not shown to be read; `VERIFIED` |
| `SR03` | Existing Cell world/scale state → reset/rebuilt world and player | `0x00E7FD00` | Pool/UI/GFX reset, world replacement, player recreation | No cross-stage or saved progression survival; `VERIFIED` |
| `SR04` | Old live Cell object → released/recreated object | `0x00E780A0` | Release associations, deallocate pool object, recreate on scale change | No individual entity persistence; `SUPPORTED` |
| `SR05` | Active Cell mode → exited/disposed Cell mode | `cCellModeStrategy::OnExit @ 0x00E7FC00`, `Dispose @ 0x00E81F30` | Restore global/display state and release stage resources | Teardown does not establish automatic `cCellSerializableData` save; `SUPPORTED` |
| `SR06` | Current OpenSpore CellSim state → fresh constructor state | Current CellSim/CellGame initialization | Deterministic in-memory reset | Current fixtures/state strings are not original save data; `OBSERVED_CURRENT` / `VERIFIED` for current behavior only |

**Provenance:** `knowledgegraph/research/data-model/17-persistence-synthesis.json:928-987`.

### 8.5 Game-mode and editor-request changes

| ID | From → to | Entry point | Explicit effects | Survival / evidence |
|---|---|---|---|---|
| `GM01` | Active mode A → selected mode B | `cGameModeManager::SetActiveModeAt @ 0x007D8D40` | Current mode `OnExit`, active-state selection, selected mode `OnEnter` | Lifecycle ordering is supported; handoff `UNKNOWN`; `VERIFIED` for ordering |
| `GM02` | Cell mode → inactive/exited Cell mode | `cCellModeStrategy::OnExit @ 0x00E7FC00` | Restore Cell globals/display and release gameplay/effect state | No automatic save or cross-mode handoff; `SUPPORTED` |
| `GM03` | Cell mode exit → Cell singletons disposed | `cCellModeStrategy::Dispose @ 0x00E81F30` | Release Cell game/GFX/UI and reset graphics state | Persistence handoff unresolved; `SUPPORTED` |
| `GM04` | External editor request → editor mode request | `EditorRequest::Submit @ 0x005A92C0`, `SubmitEditorRequest @ 0x00B1DE20` | Submit editor ID, creation key, active mode, policy request | Request transient; neither authored nor mode state proven to survive; `SUPPORTED` |
| `GM05` | Cell serialization state → creature/Space progression state | Exact entry `UNKNOWN` | None established | Separate owners and message surfaces do not prove synchronization; `UNKNOWN` |

**Provenance:** `knowledgegraph/research/data-model/17-persistence-synthesis.json:990-1041`; mode-order evidence also appears at `knowledgegraph/research/data-model/09-save-load-persistence.json:1013-1020`.

## 9. Supported survival claims

These are the strongest claims the evidence permits. “Supported” does not mean byte-perfect or runtime-validated.

| ID | Bounded claim | Qualification | Evidence |
|---|---|---|---|
| `SC01` | A saved-game header architecture carries major/minor versions, object counts, timestamp, game mode, snapshot flag, and current planet key. | Structural header evidence; placement and population not runtime-verified. | `SUPPORTED` |
| `SC02` | PropertyList has explicit Read/Write stream operations dispatching entries by property ID/type. | Exact PROP bytes, parent encoding, and round trip unknown. | `SUPPORTED` |
| `SC03` | ClassSerializer/Attribute and ISimulatorSerializable provide object-level binary/text attribute serialization architecture. | Concrete bodies, field order, and pointer remapping unknown. | `SUPPORTED` |
| `SC04` | `cCellSerializableData` is the Cell runtime serializable-state holder and contains progression, part, counter, difficulty, mission, and telemetry candidates. | Per-field emission and round trip unknown. | `SUPPORTED` |
| `SC05` | `cStarRecord` is a serializable record with saved-game version/timestamp fields and owned planet records. | Complete field coverage and database ordering unknown. | `SUPPORTED` |
| `SC06` | A narrow star/planet database path writes `stars.db.tmp` and replaces `stars.db`. | Does not establish general save atomicity. | `SUPPORTED` |
| `SC07` | The game-mode manager exits the current mode before entering the selected mode. | No state-survival rule follows from ordering. | `VERIFIED` |
| `SC08` | Cell initialization/reset creates fresh pools, world references, and serializable-state path rather than loading that path in the same body. | Initialization is not save/load; progression reset behavior unknown. | `VERIFIED` |
| `SC09` | Editor history, pose, selection, UI, and derived skin are runtime/history state, not evidenced profile fields. | Authored model/resource records have separate load/write anchors. | `SUPPORTED` |
| `SC10` | Recovered direct Cell TypeIDs are static content layouts distinct from `cCellSerializableData`. | No CellSerializer name/ID envelope is established for those records. | `VERIFIED` |
| `SC11` | `cGameData`, `cEmpire`, `cMission`, `cMissionManager`, `cCollectableItems`, `PlayerPlanetData`, `cSpaceTradeRouteManager`, and `cCommEvent` expose explicit serializable/Write/Read relationships. | Field coverage and restoration ordering are not established. | `SUPPORTED` |
| `SC12` | Resource caches, GFX preloads, material lookups, editor skin, and host mesh/texture handles are derived/runtime state rather than independently established profile fields. | Interface-only material/texture writes do not prove gameplay persistence. | `SUPPORTED` |

**Provenance:** `knowledgegraph/research/data-model/17-persistence-synthesis.json:1709-1793`.

## 10. Unsupported survival claims

The following claims must not be made from the current evidence.

| ID | Unsupported claim | Why |
|---|---|---|
| `UC01` | Every `cCellSerializableData` field survives save/load. | No complete Write/Read body, field list, default/version matrix, or round-trip oracle exists. |
| `UC02` | A direct Cell resource record is a CellSerializer envelope or saved profile record. | Recovered records are direct TypeID-specific layouts with no demonstrated name/ID envelope. |
| `UC03` | The exact `.prop` or `.spo` byte format is known. | Value/parent bytes, header placement, object order, checksum/encryption, and migration are unknown. |
| `UC04` | Saving is absent because no named `SaveGame` function was found. | Unnamed virtual, strategy, serializer, database, or generic writer paths remain possible. |
| `UC05` | Mode exit/dispose autosaves state. | Teardown and persistence architecture do not establish an automatic write. |
| `UC06` | Any state survives a level/game-mode transition by default. | `OnExit`/`OnEnter` order is known, but cross-mode handoff is not. |
| `UC07` | Editor undo/redo, selection, pose, animation world, or derived skin survives editor exit/dispose. | History/runtime conversion is transient; save-before-dispose is not established. |
| `UC08` | `Editor_Save` is a game-profile or save-slot write. | It is an asset metadata/resource boundary. |
| `UC09` | Live Cell objects, buildings, cities, planets, terrain, renderer, or cache objects are serialized wholesale. | They are runtime/derived objects; only selected value-record relationships are known. |
| `UC10` | Creature and Cell evolution fields synchronize automatically across stages. | `cCreatureGameData` and `cCellSerializableData` are separate; handoff body is absent. |
| `UC11` | A fixed number of save slots or one local profile/account file exists. | Slot enumeration, profile schema, directory boundary, and ownership are absent. |
| `UC12` | Profile/save writes are atomic, crash-safe, checksummed, encrypted, or lock-protected. | Only local bool failure and narrow `stars.db.tmp` replacement are supported. |
| `UC13` | Major/minor versions prove compatibility or automatic migration. | No branches, defaults, downgrade policy, or compatibility matrix are recovered. |
| `UC14` | Class/object pointers are restored by direct address equality or raw pointer serialization. | Pointer table/remapping and owner reconstruction are unknown; raw host pointers must not be assumed. |
| `UC15` | Current OpenSpore DBPF/Cell decoders, fixtures, state strings, scene JSON, or provider seam establish original `.prop`/`.spo` compatibility. | Current source is clean-room comparison behavior; the original persistence stack is absent. |

**Provenance:** `knowledgegraph/research/data-model/17-persistence-synthesis.json:1795-1885`; audit confirmation of the static/runtime boundary is at `knowledgegraph/research/data-model/19-evidence-audit.json:51-69,78-84`.

## 11. Gaps and next experiments

### Persistence and format gaps

| Gap | Priority | Missing evidence | Next experiment |
|---|---:|---|---|
| `G01` concrete persistence-manager methods | P0 | Exact save/load order, mode gating, profile/slot selection, and failures | Read-only characterization of concrete persistence-manager vtable methods and callers; preserve address-kind metadata |
| `G02` PROP wire format | P0 | Property value bytes, parent encoding, ordering, arrays, and round trip | Reconcile the 20-byte SDK versus 4-byte imported `Property` layout using allocation/type evidence, then characterize typed stream helpers and obtain a bounded oracle if approved |
| `G03` SPO container/header placement | P0 | Archive framing, object order, integrity, slot/profile boundary | Characterize header consumers/writers and perform only a separately approved non-mutating saved-game capture |
| `G04` ClassSerializer wire and object pointers | P0 | Class registry, object table, attribute order, pointer remapping, rollback | Reconcile SDK anchors with current function boundaries and trace serializer database/stream callers |
| `G05` save slots/profile boundary | P0 | Directory, count, ownership, locks, user-visible semantics | Characterize named slot/profile roots, path strings, menu flow, and concurrency boundaries |
| `G06` cross-stage persistence handoff | P0 | What survives Cell → creature → planet → Space | Correlate mode-manager, persistence-manager, serializable-object, and stage lifecycle bodies without modifying Ghidra |
| `G07` Cell serializable write coverage | P1 | Field order, all emitted fields, defaults, version behavior, round trip | Characterize concrete `cCellSerializableData` Write/Read bodies and build field-level fixtures only after static evidence |
| `G08` creature-to-Cell synchronization | P1 | Brain/evolution/ability versus Cell progression handoff | Find mode-exit/load paths that read or write both owners |
| `G09` reference restoration | P1 | ResourceKey, political, planet, mission, noun, and intrusive pointer mapping | Characterize object-count consumers, pointer serializer behavior, and post-load identity resolution |
| `G10` editor asset save/apply | P1 | Common editor wire format, validation order, paint persistence, save-before-exit | Characterize `Editor_Save`, `EditorModel`, and `cCreatureDataResource` bodies and compare before/after authored documents |
| `G11` progression/economy write coverage | P1 | Collectables, missions, inventory, trade routes, empire money, relationships | Build a concrete serializable-owner attribute and mutation-to-write call-path matrix |
| `G12` version migration | P1 | Compatibility matrix, defaults, downgrade behavior, migration branches | Locate version comparisons and deprecated-field consumers; use versioned fixtures only after branches are evidenced |
| `G13` transaction/recovery | P1 | Write order, rollback, crash consistency, locking | Characterize persistence/database write ordering, stream failures, and temporary-file replacement |
| `G14` multi-package resource precedence | P1 | Duplicate-key resolution, overlays, cache revalidation, post-load asset resolution | Determine database registration/search order and use a bounded duplicate-identity fixture |
| `G15` configuration boundary | P1 | Preference storage, namespace/profile scope, reset, PROP/SPO relation | Characterize `IConfigManager`, config schema, and load/reset/save call path |
| `G16` original runtime oracle | P1 | Positive Cell/editor/Space/save/load trace | Obtain a separately approved, hash-pinned, non-mutating original-runtime trace and save/load capture |
| `G17` function/address identity | P1 | Reconciled ClassSerializer, `cGameData`, persistence-manager, and CellDataReference boundaries | Re-run read-only function-boundary queries and record SDK anchor, vtable entry, live entry, and containing-function kinds separately |

**Provenance:** `knowledgegraph/research/data-model/17-persistence-synthesis.json:1887-2023`.

### Evidence-audit defects to resolve before claiming reproducibility

The evidence audits report two inherited missing paths, five stale out-of-bounds ranges, mixed address kinds, and 367 semantic source locators that are alias-aware rather than stable JSON pointers. The research dossier is untracked in the local worktree, so clean-checkout reproducibility and independent historical immutability are not established. The audits attest that no source, Ghidra, SPORE, or historical artifact was modified; that attestation is not independently verifiable for the untracked inputs. These are provenance/reproducibility defects, not permission to infer serialization behavior. `knowledgegraph/research/data-model/19-evidence-audit.json:23-35,37-50,71-84`; `knowledgegraph/research/data-model/24-final-scope-audit.json:292-321,364-383,685-706`.

The current OpenSpore tests validate deterministic content decoding and domain constraints. They do not validate original save/load behavior, `.prop`/`.spo` compatibility, object-pointer restoration, or cross-stage survival. `knowledgegraph/research/data-model/10-serialization.json:1724-1756`.

## Research priorities

1. **P0 — Recover the original persistence orchestration:** characterize concrete `cGamePersistenceManager` vtable methods, callers, header placement, and the actual write/read sequence.
2. **P0 — Resolve the Property/PROP codec:** establish the authoritative `Property` runtime layout, typed value encodings, parent semantics, and a bounded read/write oracle.
3. **P0 — Recover object identity and remapping:** reconcile `ClassSerializer`, `Attribute`, object counts, class IDs, intrusive pointers, and post-load owner reconstruction.
4. **P0 — Establish the SPO/save container boundary:** determine header framing, object order, integrity/encryption, profile/slot ownership, and failure/recovery behavior without assuming atomicity.
5. **P1 — Map field-level Cell persistence:** identify concrete `cCellSerializableData` Write/Read coverage, defaults, version gates, and reset-versus-save behavior.
6. **P1 — Correlate cross-stage transitions:** trace Cell, creature, planet, Space, and editor lifecycle handoffs against persistence candidates; retain `UNKNOWN` for every unsupported survival claim.
7. **P1 — Separate configuration, asset, and profile storage:** determine whether preferences, authored editor assets, resource databases, and saved-game state share any codec or ownership path.
8. **P1 — Repair provenance before implementing a reader/writer:** correct missing/stale references, add stable canonical IDs and address-kind metadata, and obtain a separately approved non-mutating runtime oracle.
