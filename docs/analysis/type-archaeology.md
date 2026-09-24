# OpenSpore Type Archaeology

> **Status:** validated static research synthesis. This document reports evidence and future research boundaries; it does not describe an implementation, compatibility port, runtime replay, or verified replacement.

## 1. Scope and method

This report synthesizes the validated final corpus at [`knowledgegraph/research/type-archaeology.json`](../../knowledgegraph/research/type-archaeology.json) (schema `openspore-type-archaeology-1.1`) with worker artifacts `WA-00` through `WA-16`, the final JSON audit context, and the report brief.

The controlling machine-readable source is the final corpus; worker and audit Markdown files provide readable provenance and context. The final corpus records 19 top-level sections: the 18-section blueprint plus the explicitly identified `class_families` extension (`FINAL:metadata,schema_extensions,top_level_order`). Documentation corrections in this revision follow [`25-docs-validation.md`](../../knowledgegraph/research/types/25-docs-validation.md).

The method was lossless and static:

1. Inventory the pinned binary, analysis exports, SDK references, xrefs, triage, dossiers, decomp-gap records, and current OpenSpore comparison points.
2. Preserve source-native names, levels, offsets, addresses, methods, layouts, and raw claims before normalization.
3. Normalize stable addresses and selected identities while keeping aliases, alternatives, conflicts, and projection rows explicit.
4. Separate exact source populations, computed final-record counts, and bounded hypotheses.
5. Correlate type layouts, vtable candidates, fields, shared prefixes, method bodies, lifecycle operations, and fan-in/fan-out without promoting structural association to runtime behavior.

The report's 10 required items are the report brief's items in `AUD-21`: recovered classes and types, structures, vtables, inheritance chains, shared structures, highest fan-out/reuse, types that unlock unknown functions, unresolved types, infrastructure-only candidates, and recommended OpenSpore semantic interfaces.

The final corpus was not an implementation artifact. The source artifacts and audits explicitly record no implementation, no `SPORE/` access or write, no Ghidra mutation, no SQLite write, no historical triage rewrite, and no proprietary EA source or asset payload. Current OpenSpore source appears only as comparison evidence.

## 2. Evidence legend and count discipline

| Legend | Meaning in this report |
|---|---|
| **OBSERVED** | Directly present in the pinned binary identity, committed export, exact count, field/offset record, vtable byte run, or bounded static operation. It is not automatically runtime-observed. |
| **SUPPORTED** | Multiple consistent static sources or direct static agreement. It remains static evidence, not function-level original runtime validation. |
| **INFERRED** | Bounded identity, ownership, semantic, or reconstruction conclusion from names, topology, fields, partial bodies, or shared layout. |
| **UNKNOWN** | The corpus does not establish the identity, population, owner, layout, wire format, or behavior. |
| **CONFIRMED / VERIFIED** | Reserved for the strongest byte-level or original-runtime evidence. No function-level original runtime trace is present; these grades are not used to imply runtime validation here. |

Evidence is bounded to the claim being made. `SUPPORTED` for a field offset does not establish a field's runtime meaning. `OBSERVED` for a candidate table does not establish its owner. A decompiled read/write is a static operation; xrefs are structural dependencies; SDK names and current source are provenance or comparison evidence. Source-native qualifiers such as name-only, structural-only, approximation, and unknown remain bounded in the final corpus.

Count labels are deliberately explicit:

- **Exact** means exact for the named source population and unit.
- **Computed** means a count of a final corpus array, not a unique original class count.
- **De-duplicated estimate** means a reconciliation is defensible only within a defined population.
- **Unknown** means no defensible unique total exists.
- Counts that mention candidates, hypotheses, naming-only families, projection rows, or reach can include those items; they must not be read as proven original identities.

## 3. Source and snapshot limitations

| Item | Pinned value | Evidence / use |
|---|---|---|
| Binary | `SPORE/SporeBin/SporeApp.exe` | `WA-00` identity; final corpus metadata |
| Version | `3.1.0.22` | `WA-00`, final corpus metadata |
| Architecture | `x86:LE:32` | `WA-00`, final corpus metadata |
| Image base | `0x00400000` | `WA-00`, final corpus metadata |
| Binary SHA-256 | `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e` | pinned binary identity |
| Canonical triage snapshot | `f0e310e0` | `WA-00`, final corpus metadata |
| Canonical xref snapshot | `2540f2ca` | `WA-00`, final corpus metadata |
| Runtime evidence | none; `runtime_validation_functions=0` | `WA-00`, `WA-15`, `AUD-18`, final corpus |
| MSVC RTTI | no MSVC RTTI observed in the supplied corpus | `WA-00`, `WA-11`, `WA-16`, `AUD-18`, final corpus metadata |
| Worker corpus | 17 JSON/Markdown pairs, `WA-00`–`WA-16` | final provenance; `AUD-17`, `AUD-20`, `AUD-22` |
| Independent audit context | `AUD-17`–`AUD-21` | integrity, coverage, conflicts, blueprint, and brief |
| Audit context only | `AUD-22`, `AUD-23` | final corpus excludes them as circular inputs; used for validation/spot-check context, not as metric authority |

The principal limitations are:

- No positive original-process trace reaches Cell, Space, Empire, Editor, UI, terrain, audio, or persistence. Static decompilation, current source, names, xrefs, and negative historical attempts do not establish original runtime behavior.
- Only 478 canonical bodies are persisted, including 172 of 2,149 gameplay rows. Missing persisted text is uncaptured evidence, not proof that Ghidra cannot decompile.
- `SporeApp.exe` has no MSVC RTTI. Vtable candidates, shared prefixes, SDK inheritance declarations, and adjacent interface pointers are structural evidence, not a unique compiler-emitted C++ hierarchy.
- The final corpus contains 6,967 TypeRecord rows, but only 1,591 are marked `semantic_entity=true`; the remaining 5,376 are explicit projection/evidence rows. Neither count is a unique original-class count.
- The vtable scan reports 58,756 functions while the canonical triage/xref universe is 58,757; a prior live manager report was 59,245 including externals. The population difference is retained rather than reconciled by assumption.
- SDK XML has 1,895 structures, while current Ghidra exports have 2,035 structures. These are separate populations, not additive totals.
- The SQLite knowledge graph is generated, WAL-enabled, mutable, and not a pinned original source. Its current counts cannot substitute for the pinned exports.
- Current OpenSpore files are bounded comparison projections. They may reproduce selected offsets or deterministic contracts, but they do not prove original layouts, ownership, event order, or wire compatibility.
- Static fan-in, fan-out, vtable-reference, candidate, label, association, and chain metrics are not runtime reachability. Distinct caller/callee unions and arithmetic sums can overlap.

## 4. Headline counts

### 4.1 Exact corpus and structure populations

These are exact for the stated source population and unit. They include candidates, hypotheses, or naming-only families where the source population says so.

| Population | Exact count | Unit | Evidence |
|---|---:|---|---|
| Canonical functions / unique VAs | 58,757 | functions/VAs | `WA-00`; `FINAL:M-BASELINE-FUNCTIONS`, `EV:e8301f5e201363df2e584309` |
| Canonical xref edges | 223,704 | deduplicated reference edges | `WA-00`; `FINAL:M-BASELINE-XREFS`, `EV:e8301f5e201363df2e584309` |
| Current Ghidra structures | 2,035 | structures | `WA-00:61-79`; `WA-12:27-39` |
| Current structure fields | 25,546 | fields | `WA-00:61-79`; `WA-12:27-39` |
| Raw SDK XML structures | 1,895 | structures | `WA-00:163-193` |
| Raw SDK XML members | 22,056 | members | `WA-00:163-193` |

### 4.2 Exact vtable and unknown-function populations

| Population | Exact count | Unit | Evidence |
|---|---:|---|---|
| Vtable candidate bases | 3,081 | candidate bases | `WA-00:244-264`; `WA-11:5-19`; `FINAL:M-VTABLE-INVENTORY` |
| Vtable labels | 20 | labels | `WA-00:251-264`; `WA-11:7-19` |
| High/medium/low vtable candidates | 369 / 871 / 1,841 | candidate bases | `WA-00:251-264` |
| Shared-slot clusters | 16,107 | clusters | `WA-00:251-264`; `WA-11:7-19` |
| Vtable pair clusters | 300 | clusters | `WA-16:38-49`; `AUD-18:25-45` |
| Explicit prefix/inheritance chains | 12 | chains | `WA-11:7-19`; `WA-14` |
| Vtable-reference edges | 11,898 | reference rows | `WA-00:231-242`; `WA-11:7-19` |
| Data-reference edges | 4,049 | reference rows | `WA-00:231-242`; `AUD-18:25-45` |
| Unknown-vtable implementation rows | 4,384 | canonical rows | `WA-16:38-49`; `WA-15:17-23` |
| `unknown-fun-mass` rows | 44,978 | canonical rows | `WA-16:38-49` |
| Triage `UNKNOWN` category rows | 39,716 | category rows | `WA-00:195-218`; `WA-16:38-49` |
| Debt-map `UNKNOWN` rows | 48,296 | debt rows | `WA-00:366-380`; `WA-16:178-186` |
| Genuinely unknown ownership rows | 35,771 | ownership projection rows | `WA-00:366-380`; `WA-16:38-49` |

### 4.3 Exact class-family populations

| Population | Exact count | Unit | Evidence |
|---|---:|---|---|
| Class/interface family nodes | 1,250 | family nodes | `WA-14:1-16`; `FINAL:M-CLASS-FAMILIES` |
| Binary-slot-matched class-family nodes | 33 | nodes | `WA-14:1-16`; `AUD-18:169-186` |
| SDK-association-only family nodes | 18 | nodes | `WA-14:1-16` |
| Naming-only family nodes | 1,199 | families | `WA-14:1-16`; `FINAL:M-NAMING-ONLY-FAMILIES` |

The 1,250 family-node census is a family population, not 1,250 unique original classes. The 33 binary-slot matches, 20 vtable labels, 3,081 candidate bases, 16,107 shared-slot clusters, and 12 chains are different units and are not interchangeable.

### 4.4 Final corpus record counts

The final corpus metrics are computed from its final arrays. `TypeRecord` rows can include candidates, naming-only records, SDK references, shared-layout projections, current comparisons, and evidence-only projections; the computed count is not a unique semantic-class count.

| Final metric | Count | Interpretation | Evidence |
|---|---:|---|---|
| `M-CANONICAL-TYPES` | 6,967 | final TypeRecord rows, including projections | `FINAL:metrics:2421422-2421432` |
| `M-SEMANTIC-TYPE-ROWS` | 1,591 | rows explicitly marked semantic entities; not unique original classes | `FINAL:metrics:2421586-2421596` |
| `M-TYPE-PROJECTION-ROWS` | 5,376 | explicit evidence/reference projection rows | `FINAL:metrics:2421604-2421614` |
| `M-CANONICAL-FIELDS` | 646 | field identity clusters; alternatives remain inside clusters | `FINAL:metrics:2421440-2421450` |
| `M-CANONICAL-VTABLES` | 128 | selected/normalized VtableRecord rows, not all 3,081 candidates | `FINAL:metrics:2421458-2421468` |
| `M-CANONICAL-SLOTS` | 53 | SlotRecord rows, not a sum of all alternative slot vectors | `FINAL:metrics:2421476-2421486` |
| `M-CANONICAL-METHODS` | 889 | MethodRecord rows indexed by address or source identity | `FINAL:metrics:2421494-2421504` |
| `M-CANONICAL-CONFLICTS` | 2,738 | retained ConflictRecord rows | `FINAL:metrics:2421512-2421522` |
| `M-CANONICAL-QUESTIONS` | 231 | clustered UnresolvedQuestion rows | `FINAL:metrics:2421530-2421540` |

### 4.5 Final corpus coverage and classification counts

| Final metric | Count | Interpretation | Evidence |
|---|---:|---|---|
| `M-COVERAGE-EVIDENCE` | 9,672 | source EvidenceRecord rows | `FINAL:metrics:2421550-2421560` |
| Family type-key reuse | 16 | index-only reuse; no family rows merged | `FINAL:metrics:2421622-2421632` |
| Methods with normalized kind | 33 | normalized `MethodRecord.kind != unknown` | `FINAL:metrics:2421640-2421650` |
| Methods with source-native kind | 48 | source-native method kinds retained | `FINAL:metrics:2421658-2421668` |

### 4.6 De-duplicated conclusions

- **Unique semantic type count:** **UNKNOWN**. SDK names, current-source values, shared layouts, naming-only families, candidate identities, and projection rows are not one population.
- **Unique original class count:** **UNKNOWN**. The 33 binary-slot matches are a narrow class-family subset, not a complete hierarchy.
- **Unique unresolved-function count:** **UNKNOWN**. The 39,716 triage category, 44,978 long-tail, 4,384 unknown-vtable, 48,296 debt-map, and 35,771 ownership populations have different denominators and semantics.
- **Unique shared-layout type count:** **UNKNOWN**. Reuse populations overlap by type, field, container, and export view.
- **Unique global fan-out/reach total:** **UNKNOWN**. For example, `9,428` for the generic wrapper forest is `6,527 + 2,901`, an arithmetic sum of root caller counts, not a unique caller union.
- **Infrastructure-only type total:** **UNKNOWN**. Infrastructure is a reconstruction classification, not a complete source type population.

## 5. Required item 1 — recovered classes and types

The strongest static spines are:

```text
Simulator shared services
  -> cSimulatorSystem.mSubSystems (+0x5c)
  -> mixed accessor family around the packed service block
  -> managers, mode/input, behavior/time/view, persistence, planet, trade, and UI services

Cell stage
  -> cCellGame / sCellGame
  -> cObjectPool<cCellObjectData>
  -> cCellObjectData
  -> cCellQueryEntry / cCellQueryLinkedPoolData
  -> cCellGFX, cCellUI, cCellModeStrategy

World and space
  -> cStarRecord
  -> cPlanetRecord
  -> cStar / cSolarSystem / cPlanet / cCelestialBody
  -> cStarManager, cPlanetModel, terrain, economy, diplomacy, missions, and communication

Content and persistence
  -> ResourceKey
  -> cGameData / SpacePlayerData / cEmpire
  -> Property / PropertyList
  -> ISimulatorSerializable
  -> resource records, class serializers, and saved-game records
```

### 5.1 Type-family overview

#### Simulator, Cell, and gameplay

| Type family | Representative types | Reconstructed boundary | Status and evidence |
|---|---|---|---|
| Cell state | `cCellGame`/`sCellGame`, `cCellObjectData`, `cObjectPool_`, query records | 20,964-byte state object, 920-byte elements, 28-byte pool descriptor, 4,096 capacity, pool-index identity | **SUPPORTED** static contract; `WA-01`, `WA-02`, `WA-10`, `WA-12` |
| Simulator services | `cSimulatorSystem`, `cSimTicker`, input/view/behavior/mode/time/persistence/noun/tool managers | strategy vector, listener/UI state, packed accessors, manager registries | **SUPPORTED** for layout/topology; ownership writers unresolved; `WA-01`, `WA-10` |
| Creature and social | `cCreatureBase`, `cCreatureAnimal`, `cCreatureGameData`, `cCreatureAbility`, `cTribe`, `cCity` | progression, targets, abilities, editor/presentation boundaries, social state | **SUPPORTED** for bounded layouts; runtime behavior and hierarchy remain open; `WA-03`, `WA-05`, `WA-15` |

#### World, space, and services

| Type family | Representative types | Reconstructed boundary | Status and evidence |
|---|---|---|---|
| World/planet | `cStarRecord`, `cPlanetRecord`, `cStar`, `cSolarSystem`, `cPlanet`, `cCelestialBody`, terrain/weather records | persistent records separated from live graph and surface model | **SUPPORTED** at schema/boundary level; algorithms and ownership open; `WA-04` |
| Empire/space | `cEmpire`, `SpacePlayerData`, `cStarManager`, `cRelationshipManager`, `cSpaceTrading`, `cMissionManager`, `cCommManager` | political identity, galaxy registry, relationships, economy, missions, communication | **SUPPORTED** for selected layouts and static operations; runtime transitions unknown; `WA-05` |
| Managers/registries | mode, message, resource, property, noun, tool, star, mission, and communication registries | typed registries, service slots, pools, and callback/manager boundaries | **SUPPORTED** static contracts; global writers and reset order open; `WA-10` |

#### Events, persistence, and content

| Type family | Representative types | Reconstructed boundary | Status and evidence |
|---|---|---|---|
| Events/messages | `StandardMessage`, `UTFWin::Message`, `AnimationMessage`, `cEditorAnimEvent`, `cFeedbackEvent`, `cCommEvent`, deferred/space records | at least nine distinct event families; no universal event ABI | **SUPPORTED** family separation; queue/payload semantics open; `WA-07` |
| Persistence | `Resource::Database`, `Property`, `PropertyList`, serializer interfaces, `ClassSerializer`, `cSavedGameHeader` | resource/record/property/serializable architecture | **SUPPORTED** architecture; exact wire formats unknown; `WA-08` |
| Assets/content | DBPF, RW4, GMDL, raster, `ResourceKey`, `cCellDataReference_`, world-object and Cell records | stable identity and nested byte-facing records | **SUPPORTED** for bounded record formats; runtime consumption open; `WA-09` |

### 5.2 Major cross-domain identity and persistence types

- `ResourceKey` is 12 bytes: `instanceID` at `+0x00`, `typeID` at `+0x04`, and `groupID` at `+0x08`. It crosses Cell content, assets, space, editor, rendering, and persistence. The source export's field order and DBPF lookup order are separate dimensions; current comments are not wire order. **SUPPORTED** in `WA-09:48-65`, `WA-12:61-70`, and `AUD-19:55-69`.
- `cGameData` is a 52-byte recurring identity record with view, scenario, owner, object ID, definition ID, and political ID. It is not interchangeable with `cEmpire`, `cPlayer`, `cMission`, or every `cGameData`-prefixed family. **SUPPORTED** in `WA-01:104-121` and `AUD-19:18-40`.
- `SpacePlayerData` is 52 bytes. Its fields are update time `+0x00`, active planet `+0x04`, active star `+0x08`, relationship manager `+0x0c`, context `+0x10`, rotation factor `+0x14`, empire ID `+0x18`, cached empire `+0x1c`, and colony vector `+0x20`. The accessors at `0x01021080`, `0x01021260`, and `0x01021300` expose context, active-planet, and lazy empire-cache behavior. **SUPPORTED** in `WA-05:79-101`.
- `cEmpire` is 344 bytes; major fields include political ID at `+0x84`, home star/planet at `+0xb0/+0xb4`, money at `+0xd0`, and adventure list at `+0x148`. The field is recovered; balance formulas and payout rules are not. **SUPPORTED** in `WA-05:73-77`.
- `Property` has an unresolved SDK/XML layout conflict: a four-byte imported Ghidra record versus an SDK header layout of `0x14` with flags at `+0x10` and type at `+0x12`. `PropertyList` is a 19-slot, 56-byte semantic store with parent fallback, operation count, and read/write anchors. **SUPPORTED** for the conflict, **UNKNOWN** for the exact binary Property representation; `WA-06:69-97`, `WA-08:86-97`, `AUD-19:55-69`.

### 5.3 Lifecycle and factory patterns

The most defensible lifecycle is a set of bounded operations, not a global original bootstrap/shutdown trace.

#### Simulator, modes, and Cell

- **Simulator strategy composition.** `cSimulatorSystem+0x5c` is a 20-byte intrusive vector; `cSimTicker+0x1c/+0x28/+0x34/+0x41` holds active/pending simulator state. This is a strong structural seam; insertion/update order is unresolved. Evidence: `WA-01:59-80`; `WA-10:91-109`.
- **Mode registration.** `App::cGameModeManager` entries are at `+0x14`, with the active index at `+0x28`. The four SDK-associated interior labels are `Initialize 0x007d8120` (inside `0x007d8060`), `RemoveGameMode 0x007d90b0`, `Dispose 0x007d91e0`, and `AddGameMode 0x007d9320` (the last three inside `0x007d90a0`). `SetActiveModeAt 0x007d8d40` is independently resolved, not an interior label: its address equals its containing function in the `WA-14` and final-corpus records. Registration and active selection are bounded; exit-before-enter order is not runtime-proven. Evidence: `WA-10:91-109`; `WA-13:61-71`; `WA-14 JSON:/families/56/address_resolution/15`; `WA-14 JSON:/call_patterns/22/methods/15`; `FINAL:1219761-1219763`.
- **Cell mode activation.** `cCellModeStrategy::Initialize 0x00e81cf0`, `OnEnter 0x00e552f0`, and `cCellGFX::StartDisplay 0x00e55120` are separate static stages. Evidence: `WA-02:128-137`; `WA-09:92-106`.
- **Cell state and pool.** `cCellGame::Initialize 0x00e80ba0`, `CreateCellObject 0x00e74a20`, and `FUN_00e780a0` bound initialization, creation, and release/rebuild/recreate. Evidence: `WA-02:128-137`; `WA-13:84-110`.
- **Cell frame.** `cCellModeStrategy::Update 0x00e80980` reaches unnamed orchestrator `0x00e806b0`, then movement/AI/GFX/effect consumers. The dispatch boundary exists, but arguments, continuations, and runtime order are unknown. Evidence: `WA-02:135-137`, `WA-15:202-208`; `AUD-18:230-236`.

#### World, persistence, and UI factories

- **Resource database.** `cResourceManager::Initialize 0x008de530`, `DatabasePackedFile::Lock` around `0x008d84d0`, and `PFIndexModifiable::Read` around `0x008dbc20` establish a package/record stream boundary. Cache, async, priority, and reload order are unresolved. Evidence: `WA-09:31-46`, `WA-09:92-106`.
- **UI/editor factories.** SDK-associated interior labels are `IButton::Create 0x009670a0` (inside `0x00966f90`), `ITextEdit::Create 0x0098caa0` (inside `0x0098c9d0`), and `UILayout::Load 0x008121c0` (inside `0x008121b0`). Exact function anchors include the `cEditor` constructor `0x0057ce80` and `cEditorAnimEvent` constructor `0x0059d960`. Generic UTFWin allocation and persistence grammar remain open. Evidence: `WA-06:145-169`; `WA-07:428-466`.
- **Communication event.** Allocator `0x00aeb160`, create/append wrapper `0x00aeb720`, and downstream `0x00aebe90` are bounded operations. `0x00aeb720` creates and dispatches despite a contested SDK `HandleSpaceCommAction` label. Evidence: `WA-05:132-138`; `WA-13:133-145`; `AUD-19:80-93`.
- **Inventory/tool.** `0x00c877f0` initializes item/property/localization state; `cSpaceInventoryItem` has message/listener fields. Creation/release is bounded, but registration/removal pairing is unresolved. Evidence: `WA-05:111-115`; `WA-13:133-141`.
- **World generation/regeneration.** `cPlanetRecord::Create 0x00ba6300` and the regeneration sequence around `0x00bb4af0` call `GeneratePlanetsForStar`. The boundary is supported; formulas and complete destruction are not. Evidence: `WA-04:24-40`, `WA-04:60-70`; `WA-13:143-145`.
- **Editor serialization.** SDK `EditorModel::Load 0x004ae8d0` is contained in `0x004ae3b0`; Save `0x004af780` is contained in `0x004af260`; creature resource Read/Write are at `0x004bf770`/`0x004bfc40`. Containing functions are evidence; grammar, version, and field order are unknown. Evidence: `WA-06:155-169`; `WA-03:109-117`.

## 6. Required item 2 — major structures

### 6.1 Simulator and Cell structures

| Type | Size | Important offsets / layout | Evidence ceiling |
|---|---:|---|---|
| `cSimulatorSystem` | 112 | UI-graphic list `+0x20`; message-listener data `+0x48`; `mSubSystems` `+0x5c` | **SUPPORTED** layout/topology; service writer order open |
| `cGameInputManager` | 276 | last/current mode `+0x18/+0x1c`; maps `+0x28/+0x44`; mouse `+0x68/+0x6c`; regions `+0x74/+0x90/+0xc0`; strings `+0xdc/+0xec`; vector `+0xfc`; integer `+0x110` | **SUPPORTED** field map; 27-slot concrete vtable address not pinned |
| `cGameNounManager` | 284 | avatar `+0x54`; herd `+0x58`; player tribe `+0x70`; player `+0x74`; noun list `+0x78`; noun map `+0x98`; political map `+0xb4`; object list `+0x10c` | **SUPPORTED** fields; `GetData 0x00b212d0` ABI contaminated |
| `cCellGame`/`sCellGame` | 20,964 | pool `+0x1c`; query candidates `+0x40fc/+0x4100`; later world/avatar offsets conflict | **SUPPORTED** main structure; complete field semantics unresolved |
| `cCellObjectData` | 920 | Identity/transform prefix `+0x00..+0x80`; presentation/resource `+0xa0..+0x248`; scale/query tail `+0x358..+0x35c` | **SUPPORTED/OBSERVED** selected offsets; middle-range AI/combat/ownership open |
| `cObjectPool_` | 28 | data `+0x00`; next-free `+0x04`; identifier `+0x08`; capacity `+0x0c`; live count `+0x10`; element size `+0x14`; trailing state `+0x18` | **SUPPORTED** Cell descriptor; generic function identity conflicts |

`cCellObjectData` high-value offset groups:

- **Identity and target state:** pool index `+0x00`, idle `+0x04`, target position `+0x08`, target orientation `+0x14`, transform `+0x48`, and elevation `+0x80`.
- **Presentation and resource state:** opacity `+0xa0/+0xa4`, target size `+0xb4`, model key `+0xfc`, Cell resource `+0x108`, health `+0x244`, and GFX index `+0x248`.
- **AI, scale, and query state:** scale `+0x358` and query pointer `+0x35c`; the intervening fields remain materially unresolved.

### 6.2 Creature, editor, and progression structures

| Type | Size | Important offsets / layout | Evidence ceiling |
|---|---:|---|---|
| `cCreatureBase` / `cCreatureAnimal` | 4,032 / 5,792 | creature base/extension and locomotion/animation surfaces | **SUPPORTED** layouts; binary inheritance not proven |
| `cCreatureGameData` | 76 export / 80 SDK | brain level `+0x00`; avatar scale `+0x04`; ability mode `+0x24`; evolution points `+0x28`; learned abilities `+0x34`; glide state `+0x40` | **SUPPORTED** field anchors; `0x4c` vs `0x50` conflict |
| `Editors::cEditor` | 1,536 | six vptrs `+0x00..+0x14`; refcount `+0x18`; mode `+0x31c` | **SUPPORTED** layout; constructor ownership and full lifecycle open |
| `Editors::EditorModel` | 224 | key `+0x0c`; rigblock vector `+0x18`; name `+0x5c`; colors `+0xa4`; back-pointer from rigblock `+0x28` | **SUPPORTED** layout; candidate table owners unresolved |

### 6.3 World, space, and terrain structures

| Type | Size | Important offsets / layout | Evidence ceiling |
|---|---:|---|---|
| `cStarManager` | 556 | maps/vectors `0x00..0x150`; relationship manager `+0x204`; generation controls and databases through `0x21c` | **SUPPORTED** selected fields; campaign offsets conflict |
| `cStarRecord` | 176 | serializable prefix `+0x00`; planet vectors `+0x74..0xac`; star/empire identity `+0x3c..0x70` | **SUPPORTED** record layout; exact save order open |
| `cPlanetRecord` | 432 | orbit `+0x30`; scores `+0x9c..0xb8`; civ/tribe and generated resources `+0x15c..0x1ac` | **SUPPORTED** export; civ/tribe offsets conflict |
| `cPlanet` / `cVisiblePlanet` / `cPlanetGfx` | 456 / 268 / 104 | live planet links record, visible representation, hit sphere, low-LOD model; visible planet back-pointer at `+0x108` | **SUPPORTED** live graph; destruction/copy order open |
| `cSolarSystem` | 84 | `DefaultRefCounted +0x00`; `ISimulatorSerializable +0x08`; owner star/planets/celestial bodies/model vector | **SUPPORTED** layout/interface; load/render order open |
| `cPlanetModel` | 92 | message listener `+0x00`; simulator strategy `+0x04`; intrusive/raw terrain; resource key; A*/obstacle/ribbon pointers | **SUPPORTED** join; raw-pointer ownership open |
| `cTerrainSphere` / `cWeatherManager` | 2,640 / 416 | maps, quads, textures/RTT, terrain state, camera/sun; weather/rain/storm/ambient/terrain state | **SUPPORTED** layout; equations/property IDs open |
| `cEmpire` | 344 | ID color `+0x10`; name `+0x3c`; political ID `+0x84`; stars `+0x88`; home `+0xb0/+0xb4`; money `+0xd0`; adventure `+0x148` | **SUPPORTED** fields; economy behavior open |
| `SpacePlayerData` | 52 | active planet/star, relationship, context, empire ID/cache, colonies at `+0x00..+0x20` | **SUPPORTED** exact layout; cache ownership operation open |

### 6.4 Mission, inventory, and persistence structures

| Type | Size | Important offsets / layout | Evidence ceiling |
|---|---:|---|---|
| `cMission` / `cMissionManager` | 496 / 324 | mission state, owners/targets/rewards/progress; manager tracked/recent lists and limits | **SUPPORTED** selected layouts; transition order open |
| `cSpaceInventoryItem` / `cSpaceToolData` | 124 / 672 | item identity/count/cost/political ID/property key; tool adds ammo/projectile/damage/effect state | **SUPPORTED** selected fields; prefix use across cargo variants is conflicted |
| `cSavedGameHeader` | 104 | version `+0x0c/+0x10`; object map `+0x14`; timestamp `+0x30`; mode `+0x54`; snapshot `+0x58`; current planet key `+0x5c` | **SUPPORTED** SDK structure; wire order unverified |
| `ClassSerializer` | 2,580 (`0xa14`) | 128 attribute-pointer entries; attributes contain names, IDs, offsets, callbacks | **SUPPORTED** structural declaration; body/wire encoding unavailable |

Sources for the major layout claims are `WA-01:37-57,82-164`, `WA-02:30-103`, `WA-03:22-87`, `WA-04:24-124,126-214`, `WA-05:47-138`, `WA-06:31-97`, `WA-08:66-181`, and `WA-10:91-133`.

## 7. Required item 3 — vtables

### 7.1 Vtable inventory and selected records

The vtable inventory is structural. A vtable reference identifies a containing table base and does not by itself identify the selected slot.

For 32-bit entries, the slot address is the table base plus `4 * zero_based_index`; the offsets in the tables below are therefore slot addresses relative to the cited base. The 33 high-value records in `WA-11` are a selected union, not the complete 3,081-candidate population.

The final corpus contains 128 selected/normalized `VtableRecord` rows and 53 `SlotRecord` rows; alternative target/name claims remain preserved.

### 7.2 Cell-mode candidate `0x01485550`

The candidate has 27 slots. Ten named lifecycle/input/update function anchors are separate from the SDK-associated slot-1 data label:

| Slot | Offset | Function anchor or label status |
|---:|---:|---|
| 1 | `+0x04` | SDK-associated `HandleMessage` data label `0x00e62700`; containing function `0x00e62500`; raw target remains **UNKNOWN** in the I/H/O/U accounting |
| 6 | `+0x18` | `Initialize 0x00e81cf0` |
| 7 | `+0x1c` | `Dispose 0x00e81f30` |
| 8 | `+0x20` | `OnEnter 0x00e552f0` |
| 9 | `+0x24` | `OnExit 0x00e7fc00` |
| 11 | `+0x2c` | `OnKeyDown 0x00e818f0` |
| 12 | `+0x30` | `OnMouseMove 0x00e51010` |
| 13 | `+0x34` | `OnMouseDown 0x00e6c860` |
| 14 | `+0x38` | `OnMouseUp 0x00e5c0f0` |
| 16 | `+0x40` | `OnMouseWheel 0x00e7d660` |
| 17 | `+0x44` | `Update 0x00e80980` |

This is a strong `App::cCellModeStrategy` candidate, not a complete `IGameMode` ABI proof. Slot 1 is not counted as a resolved implemented function anchor. Evidence: `WA-07:378-405`, `WA-11:375-384`.

### 7.3 Other selected vtable candidates

| Candidate base | Slots | Evidence and status |
|---|---:|---|
| `0x013f57f8` | 29 | Strong `Editors::cEditor` candidate; constructor `0x0057ce80`; slots 4/5 are Initialize/Dispose candidates, slots 6/7 are OnEnter/OnExit candidates, and five slots remain unresolved; first 16 align with `IGameMode`; `WA-06:99-125`, `WA-11:85-93` |
| `0x01408820` | 19 | High static identity for `App::PropertyList`; named Read/Write/GetProperty/SetProperty/copy/remove/clear operations; `WA-08:66-97`, `WA-11:156-164` |
| `0x01408870` | 19 | High static identity for `App::DirectPropertyList`; direct storage remains replaceable infrastructure; `WA-08:66-97`, `WA-11:166-174` |
| `0x013f1a30` | 40 | Unattributed candidate: 38 implemented, 2 unknown at indices 0 and 10, 17 method-address entries, and 71 unique consumer VAs; `WA-11:63-73`, `WA-16:98-109` |
| `0x01490be8` | 40 | Contested Terrain/Sporepedia candidate; `Terrain::cTerrainSphere::GetSimDataRTT 0x00f968b0` appears at a sampled slot with a Sporepedia `HasName` association; `WA-04:191-214`, `WA-11:386-395` |
| `0x014624d0` | 40 | `Simulator::cToolStrategy::OnSelect`; most slots unknown; family candidate, not a complete tool ABI; `WA-11:365-373` |
| `0x013fa974` / `0x01419794` | 21 each | Shared UTFWin 21-slot prefix; each is reported as base for six derived candidates; neither base is selected; `WA-11:95-124` |

`IWindow` is a 71-slot SDK interface. Dispatch-relevant slot offsets are `+0x20` GetCommandID (slot 8), `+0x54` SetCommandID (slot 21), `+0x104` AddWinProc (slot 65), `+0x108` RemoveWinProc (slot 66), `+0x10c` GetNextWinProc (slot 67), and `+0x114` SendMsg (slot 69).

`IWinProc` has seven slots: AddRef, Release, destructor, Cast, priority, event flags, and `HandleUIMessage`. These are interface/SDK contracts, not proof that a particular table implements the full interface. **SUPPORTED** in `WA-06:99-143` and `WA-07:326-376`.

The `ITerrain` conflict is material: the SDK export records 74 named slots, the asset partition records 75, and scanner candidates are 40 slots. The 40-slot table at `0x01490be8` or `0x01490c7c` cannot be used to shorten the SDK interface. **SUPPORTED conflict** in `WA-04:191-214` and `WA-09:69-90`.

## 8. Required item 4 — vtable and inheritance findings

There are exactly 12 explicit scanner prefix-chain records, with two 21-slot UTFWin bases and six derived candidates reported per base. The two bases, `0x013fa974` and `0x01419794`, share the same 21-slot prefix. The corpus does not select a canonical base. **SUPPORTED structural evidence**; `WA-11:13-19,95-124`.

The following relations are useful, but their language status differs:

| Relation | Finding | Status |
|---|---|---|
| `cCreatureBase` -> `cCreatureAnimal` | repeated exported field prefix and size extension; `cCreatureBase` is `0xfc0` and `cCreatureAnimal` is `0x16a0` | **SUPPORTED layout prefix**, not RTTI-backed C++ inheritance; `WA-03:89-108`, `AUD-19:71-78` |
| `cGameData` -> many game-data records | common identity/ownership prefix across empire, player, city, tribe, mission, tool, planet, and projectile records | structural family, not one type or proven hierarchy; `WA-05:47-71`, `AUD-19:18-40` |
| `cPlanet` | embedded `cSpatialObject`, `cGameData`, and `DefaultRefCounted` prefixes | supported layout embedding; raw pointer ownership separate; `WA-04:191-203` |
| `cStarRecord` | `ISimulatorSerializable` and `DefaultRefCounted` prefixes | supported SDK/Ghidra layout relation; exact save implementation open; `WA-04:60-70,191-203` |
| `cSolarSystem` | `DefaultRefCounted` at `+0x00`, `ISimulatorSerializable` at `+0x08` | supported interface prefix, not runtime class proof; `WA-04:84-90,191-203` |
| `cPlanetModel` | `IMessageListener`, `ISimulatorStrategy`, and `IVirtual` prefixes at `+0x00/+0x04/+0x08` | supported interface embedding; `WA-04:116-124,191-203` |
| `cTerrainSphere` | `ITerrain`, `ILayer`, `IMessageListener`, `IAmbientOccluder`, and `ResourceObject` prefixes | supported SDK layout; candidate 40-slot table is not equivalent to 74/75-slot interface; `WA-04:126-145,191-214` |
| `cCellGame` -> `cCellGFX` / `cCellUI` | mode coordination and state sharing; no demonstrated inheritance | **UNKNOWN**; `WA-02:118-126` |
| `cCellQueryEntry` -> linked-pool data | arena/header relationship | structural relation, not C++ inheritance; `WA-02:118-126`, `AUD-19:71-78` |
| `cEditor` / `cCellModeStrategy` vs `IGameMode` | SDK interface prefixes and candidate slots agree only partially; concrete tables have 29 and 27 slots | interface evidence, not complete ABI identity; `WA-06:99-125`, `WA-11:85-93,375-395` |

No MSVC RTTI was observed, so a complete C++ inheritance graph is not defensible. The final corpus retains `layout_prefix`, `shared_layout`, `composition`, `embedding`, and candidate-family relations separately.

## 9. Required item 5 — major shared structures and shared fields

| Shared layout | Repeated fields / prefix | Reuse and limit |
|---|---|---|
| `cCellDataReference_` | 16-byte layout: ID `+0x00`, serializer `+0x04`, intrusive resource `+0x08`, counter `+0x0c` | 13 exported typed reference variants share the prefix; `0x00e82420` and `0x00e82340` remain alternative function identities; `WA-09:61-65`, `WA-12:61-70` |
| `ResourceKey` | instance/type/group at `+0x00/+0x04/+0x08` | broadest semantic identity primitive across content, space, editor, rendering, and persistence; field order and lookup order are separate; `WA-09:48-59`, `WA-12:61-70` |
| `eastl::map` | comparator `+0x00`, 16-byte anchor/end candidate `+0x04`, root `+0x0c`, size `+0x14`, allocator `+0x18`; 40 typedefs | shared container substrate; `+0x04` is called anchor/end/sentinel by different sources; `WA-12:61-70`, `WA-16:85-96` |
| `eastl::vector` | begin/end/capacity at `+0x00/+0x04/+0x08`, allocator `+0x0c`, trailing word `+0x10`; 60 ordinary typedefs; 10 `vector_map` typedefs | shared pointer layout is not a reason to reproduce EASTL ABI; `WA-12:61-70` |
| Space inventory/tool/cargo | vtable/refcount prefix, item identity/ownership `+0x10..+0x34`, cargo/property list `+0x48/+0x50`, resource key around `+0x5c`, message fields | five inventory/tool/cargo structures share a prefix, but the prefix cannot be applied to all variants without adjudication; `WA-05:111-115`, `WA-12:61-70`, `AUD-19:55-69` |
| UTFWin `Window` | two vptrs `+0x00/+0x04`, links `+0x08/+0x0c`, refcount `+0x28`, manager `+0x34`, parent `+0x38`, children `+0x3c`, procs `+0x64`, IDs `+0x80/+0x84`, areas `+0x88/+0x98`, font `+0xc0`, drawable `+0x1e0` | 524-byte framework layout reused by UTFWin/UI structures; semantics can be retained behind a modern UI boundary; `WA-06:69-97`, `WA-12:61-70` |
| Cell query record | position/size, link pointer, pool index; entry/header/data records have distinct sizes | exact query iteration, insertion, partition, and ownership remain unknown; `WA-02:62-84`, `WA-12:43-50` |
| Cell content/advect | `cCellWorldResource` header plus 24-byte `cAdvectEntry` records with scale bucket, strength, variance, period, ID | record shape/selection supported; Ghidra integer types conflict with decompiler/current float reads; `WA-09:50-60`, `WA-12:41-52` |

## 10. Required item 6 — highest fan-out and reuse

| Surface | Exact static metric | Interpretation |
|---|---:|---|
| `cGameInputManager::Get` | 614 total / 80 gameplay distinct callers | broadest direct gameplay dependency named in the assessment; 27-slot input/mode surface; `WA-15:148-161` |
| `cEditor` | 21 associated functions; 494 distinct callees; maximum fan-out 111; sum fan-out 701 | broad editor command/UI/resource/gameplay dependency surface; not a complete object ABI; `WA-15:148-167` |
| `cSpaceTrading` | 168 callers; maximum fan-in 156 | high fan-in semantic owner for economy/trade paths; `WA-15:77-90` |
| `cRelationshipManager` | 78 callers; maximum fan-in 53 | high fan-in diplomacy owner; `WA-15:84-90` |
| `cCreatureBase` | 83 distinct callers | broad creature behavior/animation/social reuse root; `WA-15:52-60` |
| `map_int_whatever_find` | 265 distinct callers | shared map lookup chokepoint, not a domain owner; `WA-12:54-56`, `WA-16:85-96` |
| Noun bridge projection | 254 distinct callers | high fan-in map/materialization candidate; not automatically message-handler registration; `WA-07:406-426`, `WA-16:85-96` |
| Generic wrapper forest | 6,527 callers at `0x00f47380` + 2,901 at `0x00f473a0`; arithmetic sum 9,428 | infrastructure reach, not a unique caller union or gameplay type; `WA-16:55-75` |
| Property data spine | 841 total / 82 gameplay reach | typed property/configuration/persistence unlock surface; `WA-15:148-160` |
| Unknown vtable implementation corpus | 4,384 rows | high dispatch leverage, but owner and slot semantics unresolved; `WA-15:150-160`, `WA-16:38-53` |

The highest-value reuse is not always the highest-value reconstruction target. Generic allocator/reference forwarding and UTFWin internals have large graph reach but are replaceable infrastructure. The input manager, editor command surface, identity/persistence records, and Cell state have the strongest combination of semantic breadth and compatibility value.

## 11. Required item 7 — types that unlock unknown functions

- **Unresolved root `00b3d300`.** Static reach is 1,097 total / 252 gameplay callers. It may identify an unnamed shared service/global-slot owner, but the gate is direct field access plus two independent consumers or a corroborated lifecycle chain. Evidence: `WA-15:148-156`; `AUD-18:226-232`.
- **Conflicted accessor `00b3d2a0`.** Static reach is 314 / 101. `WA-08`/`AUD-19` preserve an SDK alternate for `cGamePersistenceManager` alongside `0x00b3d440`; `WA-15`/`AUD-19` preserve an unresolved high-leverage shared-state root and reject the historical player-ID identity. Do not settle persistence-manager, current-context, or player ownership; require ABI and independent-consumer adjudication. See the conflict table below.
- **Unresolved root `00b5b800`.** Static reach is 459 / 80. It may resolve scalar/handle semantics and forwarded object ownership, but source-purpose labels are not identity. The gate is the same as `00b3d300`.
- **`cGameInputManager`.** Static reach is 614 / 80. It can unlock normalized input, current/previous mode, regions, and callback routing after typed slot bodies and two independent routing consumers are available. Evidence: `WA-06:58-67`; `WA-15:163-172`.
- **`cEditor` command surface.** Static reach is 31 / 16. It can unlock 21 named methods, input/message/tool ownership, and the 494-distinct-callee command surface. Require constructor, message-registration, and final-consumer chains. Evidence: `WA-15:150-160`.
- **Property data spine.** Static reach is 841 / 82. It can unlock property definitions, parent lookup, read/write, configuration, and persistence after property IDs and read/write bodies are recovered. Evidence: `WA-08:86-145`.
- **Unknown-vtable corpus.** The population is 4,384 rows, including 14 gameplay rows in the cited projection. It can unlock owner mapping and virtual slot semantics after stable slot vectors, constructors, and consumer evidence. Evidence: `WA-15:150-160`; `AUD-18:94-110`.
- **Generic wrapper forest.** Arithmetic reach is 9,428. It can unlock allocator/reference boundaries and null/failure behavior only after exact register/stack ABI work; do not rename it as an allocator class from fan-in. Evidence: `WA-16:55-75`.
- **Space-player roots `0x01021260`, `0x01021080`, `0x01021300`.** Summed reach is 619 callers / 153 gameplay callers. They can unlock active-planet, context, player-ID, and lazy-empire-cache behavior after construction, writer, and cache-replacement evidence. Evidence: `WA-05:79-101`; `WA-15:150-160`.
- **Noun bridge `0x00b21340`.** Static reach is 254 callers / 50 gameplay callers in the cited projection. It can unlock map lookup, noun materialization, and callback-bridge behavior, but the message-handler label remains competing evidence. Compare `0x00e5c780`, `0x00ba8420`, and at least two independent consumers. Evidence: `WA-07:406-426`; `WA-16:85-96`.

## 12. Required item 8 — unresolved types, conflicts, and unresolved boundaries

### 12.1 Unresolved candidate families

- **`MISC-AT-001` forwarding pair.** `0x00f47380` and `0x00f473a0` forward to `0x009276c0` and `0x009289f0`; caller counts are 6,527 and 2,901. Return type, null behavior, object size, ownership, and allocation/destruction side effects are unknown. Source labels “free” and “alloc” remain hypotheses. Evidence: `WA-16:55-75`.
- **`MISC-BUF-001`.** `0x009289f0` and `0x00928a30` are an opaque buffer/handle family with 20 and 35 callers and WIN32 dependency hints. Element, lock, storage, and owner layout are absent. Evidence: `WA-16:77-80`.
- **`MISC-STR-001`.** `0x006b55c0` and `0x006b5770` are an SEH-heavy string/localized-value family with 263 and 93 callers. No stable offsets, size, return contract, or ownership are recovered; do not rename it as a string type. Evidence: `WA-16:81-83`.
- **`MISC-MAP-001`.** `0x00e5c780` and related `0x00ba8420` have map offsets `+0x04/+0x0c` and node offsets `+0x10/+0x14`. Lower-bound mechanics are strong, but owner, key/value domains, mutation boundary, and iterator encoding are unresolved. Evidence: `WA-16:85-96`.
- **`MISC-VT-001`.** `0x013f1a30` is a 40-slot candidate with 38 implemented slots, unknown indices 0 and 10, 17 method entries, and 71 consumers. No class, namespace, constructor, slot meaning, or owner is proven. Evidence: `WA-16:98-109`.
- **`MISC-REC-001`.** `0x00e39ab0` builds records described as 27-field and 24-field, with writes at `+0x64/+0x68`, `cTribe+0x504/+0x508/+0x50c` position sources, and global `0x0168de78`. The records have 16 callers and space/tool/trading consumers, but sizes, field order, allocation, owner, serialization, and shared-versus-coincident identity remain unresolved. Evidence: `WA-16:111-124`.
- **Cell reference alias.** `0x00e82420` is SDK-associated while `0x00e82340` is an adjacent candidate body. Construction, caller, cache, and release contracts do not select one identity. Evidence: `WA-09:61-65`; `WA-12:86-90`.
- **Generic pool name.** `cObjectPool_::Get 0x00b72320` conflicts with nearby bodies `0x00b72160` and `0x00b72260`; SDK names occur around `0x00b72190` and `0x00b72270`. The pool descriptor and Cell mechanics are strong, but generic `Get`, address drift, failure, and destruction behavior remain open. Evidence: `WA-01:146-164`; `WA-13:84-110`.
- **Communication wrapper.** `0x00aeb720` allocates/initializes a `0xa0` event and forwards it, while also carrying an `HandleSpaceCommAction` association. The SDK/triage identity is contested; neither exclusive name is promoted. Evidence: `WA-05:132-138`; `AUD-19:80-93`.

### 12.2 Conflicts that must remain open

- **Cell mode/editor projection.** `0x01485550` is strongly `App::cCellModeStrategy`, but an editor family projection also includes it. Retain both projections; do not merge identities.
- **`0x00B3D2A0` accessor identity.** `WA-08`/`AUD-19` preserve an SDK alternate for `cGamePersistenceManager` alongside committed `0x00B3D440`; `WA-15`/`AUD-19` preserve an unresolved high-leverage shared-state root, with the historical player-ID identity unsupported by mixed consumers. Do not settle persistence-manager, current-context, or player ownership; require ABI and independent-consumer adjudication.
- **Terrain/Sporepedia vtable.** `0x01490be8` has a Terrain `GetSimDataRTT` anchor and a Sporepedia `HasName` association. Preserve owner alternatives; there is no canonical owner.
- **UTFWin bases.** `0x013fa974` and `0x01419794` share a 21-slot prefix and both are reported as bases for six derived candidates. Preserve both; no canonical base is selected.
- **`cCreatureGameData`.** Persisted size `0x4c` conflicts with SDK size `0x50`. Retain both layout alternatives.
- **`cSpeciesProfile`.** Export `0xeec` with `mSpeciesKey +0xa18` conflicts with targeted allocation `0xa18` and different field ordering. Do not use either as a settled binary ABI without more evidence.
- **`cPlanetRecord`.** `mCivData/mTribeData` appear at `+0x15c/+0x170` versus `+0x188/+0x1a0`. Preserve both offset sets.
- **`cStarManager`.** SDK and campaign offsets disagree for starter/saved/star-grid fields. Preserve field alternatives and matching fields separately.
- **`cAdvectEntry`.** Ghidra integer-like fields at `+0x08/+0x0c/+0x10` conflict with decompiler/current-source float reads. Do not use host source to silently settle the binary type.
- **`App::Property`.** Imported four-byte layout conflicts with SDK `0x14` layout. Retain the unresolved wire/layout conflict.
- **`UTFWin::Message`.** SDK base `0x0c` conflicts with anonymous payload footprint at least `0x1c`. Retain base/payload alternatives; there is no universal event ABI.
- **`cCellGame` late offsets.** `WA-01` places world references at `+0x411c/+0x4120` and avatar at `+0x4124`; `WA-02`/`WA-12` place world references at `+0x4114/+0x4118` and avatar at `+0x411c`. Field-use closure and a positive trace are required.
- **`cGameData::Write`.** The SDK name at `0x00b184c0` conflicts with a destructor/teardown-like body and global decrement. Preserve name and mechanics separately.
- **`cSpaceInventoryItem` prefix.** The inventory/tool/cargo shared prefix is not uniformly applicable. Retain alternative prefix claims; do not flatten variants.
- **Message bridge.** The dossier calls `0x00b21340` message-handler registration, while later artifacts support generic map/list callback/materialization mechanics. Preserve the historical label; `0x00b21340` is the current address and `0x00b321340` remains an alias.
- **Persistence manager callsites.** `WA-08` prose lists `0x00b32bc8` while its detailed ledger also lists `0x00c7f109`. Use one canonical list in future extraction; do not imply current reconciliation.
- **Current source comparisons.** Current `CellGame`, `CellPool`, `CellQuery`, `ResourceProvider`, and mode shells are reduced projections. Never treat current source as original layout or runtime proof.

The full alternatives and merge decisions are in `AUD-19:18-129` and the final corpus `conflicts` section. The final 2,738 conflict rows are record-level preservation, not 2,738 independent semantic disputes.

## 13. Required item 9 — infrastructure-only candidates

“Infrastructure-only” means the original implementation may be replaced while identity, ordering, errors, data, event, and compatibility contracts remain semantic. It does not mean the subsystem is unimportant.

| Infrastructure boundary | Static facts | Retain | Replace or defer | Evidence |
|---|---|---|---|---|
| UTFWin/UI framework | 1,093 attributed functions; `IWindow` 71 slots; `IWinProc` 7 slots; layouts, drawables, windows, procs, commands, hit-testing | command IDs, event identity, hierarchy, focus/hit-test, layout and dispatch ordering | original 71-slot ABI, RenderWare/D3D, pdtk command internals, widget allocation | `WA-06:20-29,69-97,145-173`; `AUD-21:204-222` |
| Resource manager and DBPF/QFS | `cResourceManager::Initialize 0x008de530`; packed-file/index/record boundaries; `ResourceKey` identity | key triple, record bounds, missing/error behavior, cache invalidation semantics, factory dispatch | DBPF index implementation, QFS plumbing, allocator/cache internals, multi-package storage | `WA-09:31-46,92-120`; `WA-10:155-166` |
| RW4/GMDL/raster content | bounded v8 GMDL prefix, RW4 manifest/section topology, DXT5 raster envelope; unknown sections `0x2000B`/`0x7000B` | byte-facing record contracts, references, material/texture slot identity | RenderWare object graph, D3D resources, unknown section semantics, GMDL v9, full animation/baked-deform execution | `WA-09:31-46,108-139` |
| Property manager/storage | `PropertyList` parent lookup, typed property values, `Read/Write`, property manager registry | typed keys, parent fallback, enumeration, versioned read/write behavior, errors | direct-property container optimization, global manager storage, original property internals | `WA-08:86-145`; `WA-15:118-127` |
| Allocator/reference wrappers | `0x00f47380`, `0x00f473a0`; 9,428 arithmetic caller reach | null/failure/release/forwarding semantics after ABI recovery | generic allocation/reference wrappers and source-purpose labels | `WA-16:55-75` |
| Renderer, audio, Win32/CRT plumbing | renderer layer/model/effect worlds, DSOUND and Win32 dependencies, platform runtime | normalized render/audio/UI event outcomes, handle identity, lifecycle ordering | RenderWare/D3D9/DSOUND/Win32/CRT object graphs | `WA-06:243-269`; `WA-09:108-120`; `WA-10:155-166` |
| Shared SDK manager singletons | packed accessor region around `0x0167eac0` and mixed roots | service roles, dependencies, lifecycle visibility, semantic lookup | global storage slots, static access, EASTL ABI, raw intrusive pointers | `WA-10:26-89,145-166` |

Infrastructure candidates can unlock semantic work through call topology, but their fan-in must not be converted into class identity or gameplay ownership.

## 14. Required item 10 — recommended semantic interfaces for future OpenSpore reconstruction

These are clean-room research anchors, not recovered original ABIs and not implemented interfaces.

| Bundle | Future semantic contract | Evidence / boundary |
|---|---|---|
| `ICellGameState + IEntityPool + ICameraRayProvider` | player identity, stable pool handles, world/plane state, movement targets, ordered interaction events | `WA-15:163-172`; Cell state/layout, pool, movement dossier |
| `IAppHost + IGameModeRegistry` | application services, mode registration, activation order, frame ticking, shutdown | `WA-15:165-168`; mode manager and vtable evidence |
| `IInputRouter + cGameInputManager field contract` | normalized input, current/previous mode, regions, callbacks, selected layout contract without the 27-slot ABI | `WA-15:167`; `WA-06:58-67` |
| `IGameServices` | injected input, camera/view, behavior, mode, persistence, and frame-clock operations | `WA-15:168`; manager/root evidence |
| `IContentStore + IRecordCodec` | `ResourceKey` identity, provider-independent record bytes, bounds, missing/error behavior | `WA-15:169`; `WA-09:31-65` |
| `IPropertyStore + IPropertyCodec` | typed keys, parent fallback, enumeration, versioned read/write behavior | `WA-15:170`; `WA-08:86-145` |
| `ISerializableGameObject` | read/write, noun identity, refcount, and serialization hooks without reproducing multiple-inheritance layout | `WA-15:171`; `WA-08:99-181` |
| `IEventRouter + typed stage events` | separate App, UTFWin, mode, animation, feedback, communication, deferred, and space event families; no universal event ABI | `WA-15:172`; `WA-07:9-21,546-657` |
| `IAnimationWorld + IAnimatedCreature` | load/update/destroy, animation state, pose, model/effect world binding, editor bridge | `WA-15:173`; `WA-03:109-169` |
| `IPlayerIdentity + IEmpireRegistry` | `SpacePlayerData`, current-empire cache, political ID, star-manager registry | `WA-15:174`; `WA-05:79-109` |
| `IRelationshipStore + ITradeService + IMissionService` | war/alliance/peace transitions, trade inventory, mission state, rewards, communication-facing services | `WA-15:175`; `WA-05:117-138` |
| `IUiWindow + IUiCommandRouter` | command/window hierarchy, hit-testing, layout, focus, event identity while replacing UTFWin/renderer backends | `WA-15:176`; `WA-06:243-269` |

The recommended anchor order is data-first and interface-first:

1. **Identity and persistence:** `ResourceKey`, `cGameData`, `SpacePlayerData`, `cEmpire`, `Property`/`PropertyList`, `ISimulatorSerializable`.
2. **Host and services:** `IAppHost`, `IGameModeRegistry`, `IInputRouter`, `IGameServices`, time/behavior/persistence managers.
3. **Cell spine:** `cCellGame`, `cCellObjectData`, `cObjectPool_`, world/advect records, `cCellSerializableData`.
4. **Gameplay owners:** creature, tribe, city, planet, star, trading, relationship, and mission owners.
5. **Editor and content boundaries:** `cEditor`, animation, event routing, content store, and property store.

This order is a research recommendation, not implementation authorization. The corpus does not rank implementation effort and does not establish runtime fidelity, complete hierarchy, or original wire compatibility.

## 15. Prioritized follow-up analysis

### 15.1 P0 gates

- **Q-001 — characterize the mixed simulator accessor region and packed global block.**
  - Targets: `0x00b3d220..0x00b3d5a0`, `0x0167eac0`, `0x00b3d300`, `0x00b3d2a0`, `0x00b5b800`, `0x00b21340`, `0x01021260`, `0x01021300`, `0x01021080`, `0x00ba9370`.
  - Output/gate: per-accessor ABI, return meaning, writer/reader edges, null/sentinel/ownership, and concrete owner or unresolved status. Require direct field access plus two independent consumers or a corroborated lifecycle chain. `AUD-18:226-232`.
- **Q-002 — recover the 27-slot Cell mode table against the SDK `IGameMode` order.**
  - Targets: `0x01485550`, `0x00e81cf0`, `0x00e552f0`, `0x00e7fc00`, `0x00e81f30`, `0x00e80980`, `0x00e61550`, `0x00e616c0`.
  - Output/gate: stable slot-to-method table, registration and enter/exit order, unknown-slot classification, and separation of original ABI from a future clean-room interface. `AUD-18:231`.
- **Q-003 — carve unattributed `0x013f1a30` against pair clusters and chains.**
  - Targets: `0x013f1a30`, `0x013fa974`, `0x01419794`, `0x013f57f8`, `0x013ff648`.
  - Output/gate: full raw slot vector, slot status, construction and consumer map. Require a stable slot vector plus construction or caller evidence. `AUD-18:232`.
- **Q-004 — resolve `0x01490be8` and mixed UTFWin/Sporepedia tables.**
  - Targets: `0x01490be8`, `0x01414ed4`, `0x0141873c`, `0x014190d4`, `0x0141930c`, `0x014195ac`, `0x0141ab94`, `0x01441144`.
  - Output/gate: per-slot target/namespace evidence, construction/base-pointer evidence, and a resolved or preserved owner explanation. `AUD-18:233`.
- **Q-005 — recover serializer, property, and persistence bodies.**
  - Targets: `0x006a2f60`, `0x006a1540`, `0x00692880`, `0x00693dd0`, `0x00b3d440`, `0x00b2e010`, `0x00b2d7c0`, `0x00c7f060`.
  - Output/gate: exact read/write order, count/version/checksum/pointer rules, owner and failure behavior. Require bodies plus an original `.prop` or `.spo` oracle and reproducible round trip. `AUD-18:234`.
- **Q-006 — trace Cell per-frame and pool/GFX lifecycle.**
  - Targets: `0x00e806b0`, `0x00e5b2e0`, `0x00e780a0`, `0x00e74a20`, `0x00e80ba0`.
  - Output/gate: frame/lifecycle call graph, register contracts, release/recreate and GFX ownership order, and field reads/writes. Runtime-order claims require a positive original trace. `AUD-18:235`.

### 15.2 P1 analyses

- **Q-007 — close the field-use graph for Cell object/query middle ranges.**
  - Targets: `cCellObjectData +0x100..+0x358`, `cCellQueryEntry +0x00..+0x17`, `0x00e57460`, `0x00e58980`, `0x00e57340`, `0x00e6d200`, `0x00e58ef0`, `0x00e58e30`.
  - Output/gate: per-field read/write/use, owner, AI/combat/animation/query classification, and unknown-field list. Require cross-consumer agreement. `AUD-18:236`.
- **Q-008 — recover message registration, queue processing, send/post, removal, and UTFWin propagation.**
  - SDK-associated interior labels and containing functions:
    - `0x00883b20` inside `0x00883b00`.
    - `0x008847f0` inside `0x00884700`.
    - `0x008854a0` inside `0x00885390`.
    - `0x00885980` inside `0x00885930`.
    - `0x00885a20` inside `0x008859f0`.
  - Additional targets: `0x008841f0`, `0x00960250`, `0x00960310`.
  - Output/gate: `0x18` queue record, priority/tie/handled-result rules, listener ownership/removal, and bubbling. Require corrected calling conventions and a representative dispatch trace. `AUD-18:237`.
- **Q-009 — correlate forwarding roots and the opaque map family.**
  - Targets: `0x00f47380`, `0x00f473a0`, `0x009276c0`, `0x009289f0`, `0x00e5c780`, `0x00ba8420`, `0x00b21340`.
  - Output/gate: exact register/stack ABI, allocation/release or map-mutation boundary, owner, and return meaning. Fan-in is insufficient. `AUD-18:238`.
- **Q-010 — recover the paired 27-field/24-field record ABI.**
  - Targets: `0x00e39ab0`, `0x00e39420`, `0x00e39450`, `0x00b316c0`, `0x0168de78`.
  - Output/gate: two record layouts, field offsets/types, allocation/consumer ownership, and serialization status. Require constructor and independent consumer agreement. `AUD-18:239`.
- **Q-011 — trace star/planet generation, persistence, terrain, and weather.**
  - Targets: `0x00bb4af0`, `0x00bb4100`, `0x00bb5b50`, `0x00ba6300`, `0x00f968b0..0x00fa5610`.
  - Output/gate: generation order/formulas, record-to-live graph, weather/terrain lifecycle, and serialization order. Require bodies plus byte-level or original-process evidence. `AUD-18:240`.
- **Q-012 — adjudicate the `cCellDataReference` alias and typed variants.**
  - Targets: `0x00e82340`, `0x00e82420`, `cCellDataReference_`, `0x00e58ef0`.
  - Output/gate: alias identity, cache/release contract, typed-reference resolution, and serialized-ID versus runtime-pointer distinction. Retain both if construction/caller/field evidence does not select one. `AUD-18:241`.

### 15.3 P2 analysis

- **Q-013 — recover editor animation to final animation/pose consumers.**
  - Targets: `0x0059d8b0`, `0x0059d840`, `0x00587270`, `0x00591fa0`, `0x00e6d200`, `0x00e66840`.
  - Output/gate: event IDs, payload ownership, animation consumer and ordering, and the original-versus-current `CellAnim` boundary. Require a typed producer-to-consumer chain. `AUD-18:242`.

## 16. Provenance and validation

The report uses these source families:

| Alias | Clickable artifact |
|---|---|
| `FINAL` | [`knowledgegraph/research/type-archaeology.json`](../../knowledgegraph/research/type-archaeology.json) |
| `WA-00` | [`00-corpus-inventory.md`](../../knowledgegraph/research/types/00-corpus-inventory.md) |
| `WA-01` | [`01-simulator-core.md`](../../knowledgegraph/research/types/01-simulator-core.md) |
| `WA-02` | [`02-gameplay-entity.md`](../../knowledgegraph/research/types/02-gameplay-entity.md) |
| `WA-03` | [`03-creature.md`](../../knowledgegraph/research/types/03-creature.md) |
| `WA-04` | [`04-world-planet.md`](../../knowledgegraph/research/types/04-world-planet.md) |
| `WA-05` | [`05-empire-space.md`](../../knowledgegraph/research/types/05-empire-space.md) |
| `WA-06` | [`06-editor-ui.md`](../../knowledgegraph/research/types/06-editor-ui.md) |
| `WA-07` | [`07-event-message.md`](../../knowledgegraph/research/types/07-event-message.md) |
| `WA-08` | [`08-persistence-serialization.md`](../../knowledgegraph/research/types/08-persistence-serialization.md) |
| `WA-09` | [`09-asset-content.md`](../../knowledgegraph/research/types/09-asset-content.md) |
| `WA-10` | [`10-managers-registries.md`](../../knowledgegraph/research/types/10-managers-registries.md) |
| `WA-11` | [`11-vtable-archaeology.md`](../../knowledgegraph/research/types/11-vtable-archaeology.md) |
| `WA-12` | [`12-field-archaeology.md`](../../knowledgegraph/research/types/12-field-archaeology.md) |
| `WA-13` | [`13-lifecycle.md`](../../knowledgegraph/research/types/13-lifecycle.md) |
| `WA-14` | [`14-class-families.md`](../../knowledgegraph/research/types/14-class-families.md) |
| `WA-15` | [`15-reconstruction-relevance.md`](../../knowledgegraph/research/types/15-reconstruction-relevance.md) |
| `WA-16` | [`16-misc-unknown.md`](../../knowledgegraph/research/types/16-misc-unknown.md) |
| `AUD-17` | [`17-audit-integrity.md`](../../knowledgegraph/research/types/17-audit-integrity.md) |
| `AUD-18` | [`18-audit-coverage.md`](../../knowledgegraph/research/types/18-audit-coverage.md) |
| `AUD-19` | [`19-audit-conflicts.md`](../../knowledgegraph/research/types/19-audit-conflicts.md) |
| `AUD-20` | [`20-synthesis-blueprint.md`](../../knowledgegraph/research/types/20-synthesis-blueprint.md) |
| `AUD-21` | [`21-report-brief.md`](../../knowledgegraph/research/types/21-report-brief.md) |
| `AUD-22` | [`22-final-json-audit.md`](../../knowledgegraph/research/types/22-final-json-audit.md) |
| `AUD-23` | [`23-semantic-spotcheck.md`](../../knowledgegraph/research/types/23-semantic-spotcheck.md) |

The report brief is `AUD-21`.

`AUD-17` found parse/pair integrity but required normalization of paths, identifiers, vocabularies, counts, ordering, and section coverage. `AUD-18` rated vtables, structures, fields, and reconstruction relevance strong; lifecycle and class families partial. `AUD-19` supplied the canonical identity decisions and preserved alternatives. `AUD-20` supplied the deterministic merge and record-contract blueprint. `AUD-21` supplied the 10 required report items. `AUD-22` is the post-remediation JSON audit and reports metric/provenance/fixed-check passes, but the final corpus excludes it as a circular source input. `AUD-23` is a semantic spot-check with residual high/medium findings before the final reporting stage; it is context only and not counted as independent final authority.

The final corpus reports parse/hash validation, 23 manifest entries, 22 JSON/Markdown pairs plus one contextual campaign, and zero self-referential manifest entries. Its merge policy preserves source claims, retains alternative layout and identity claims, keeps current source comparison-only, and sets `runtime_observed=false` for synthesized lifecycle and method records. The final report therefore makes no claim of implementation, runtime validation, complete RTTI hierarchy, complete field semantics, exact global lifecycle, exact `.prop`/`.spo` compatibility, or original event ABI.
