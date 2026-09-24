# Type Conflict Audit

## Scope

Read-only cross-artifact audit of the 17 JSON partitions in `knowledgegraph/research/types`. No worker, source, `SPORE/`, Ghidra, knowledge-graph, or history artifact was modified. The audit is timestamp-free and preserves source alternatives instead of silently selecting a winner.

## Merge rules

1. A positive original binary/runtime observation would outrank all static evidence. None is present in these partitions.
2. Direct persisted field, offset, body, and address evidence outranks a name-only interpretation.
3. Independent matching size, field-prefix, and consumer evidence supports alias canonicalization, but not automatic subtype or inheritance merging.
4. SDK names, declarations, and slot names are reference provenance only.
5. Vtable candidates, vtable references, and shared prefixes establish structural candidates only; SporeApp.exe has no MSVC RTTI.
6. Current OpenSpore types are comparison boundaries, not original identity or ABI evidence.

Canonical IDs use `namespace.kind.name`; anonymous records use stable address or record-shape IDs. A canonical ID is an index key, not a silent resolution of a conflict.

## Canonical entity decisions

| Canonical ID | Decision | Guard |
|---|---|---|
| `sim.cell-game-state` | Merge `sCellGame` and `cCellGame` aliases. | 20,964-byte state, pool/world/avatar fields, and repeated Cell initialization. |
| `sim.cell-object-data` | Deduplicate the 920-byte pooled entity records. | Selected offsets and first-word index agree; omitted middle fields remain opaque. |
| `sim.cell-object-pool` | Keep Cell specialization separate from `sim.object-pool-generic`. | 4096 capacity, 920-byte stride, and Cell lifecycle are stronger than generic SDK labels. |
| `sim.cgame-data` | Deduplicate the 52-byte identity record. | Do not merge `cEmpire`, `cPlayer`, `cMission`, or other prefix-derived records. |
| `sim.cempire` | Keep the 344-byte political identity separate from `cGameData`. | The `cGameData / cEmpire` family label is shorthand only. |
| `sim.cspace-player-data` | Deduplicate `SpacePlayerData`/`sSpacePlayerData`. | Cached empire ownership remains unresolved. |
| `editors.editor-model` | Deduplicate the 224-byte model name/layout. | Candidate vtable bases remain alternatives. |
| `app.ceditor` | Deduplicate the 1536-byte editor root. | Constructor evidence, `0x013f57f8`, and editor-family projections are not interchangeable. |
| `app.cgame-mode-manager` | Keep App registry and `sim.cgame-mode-manager-simulator-candidate` separate. | 52-byte registry and 156-byte Simulator service/state object. |
| `app.igame-mode` | Keep the 16-slot interface separate from concrete mode tables. | Concrete `0x01485550` has 27 slots. |
| `app.property` | Keep separate from `app.property-list`. | Property has 0x04 versus 0x14 layout alternatives; PropertyList is 0x38. |
| `app.property-list` | Deduplicate the 56-byte property store. | Do not merge DirectPropertyList or cPropManager. |
| `events.comm-event` | Deduplicate the 160-byte communication event. | Do not merge anonymous space records. |
| `events.utfwin-message` | Keep the 0x0C base versus effective 0x1C payload alternative. | Do not treat anonymous payload records as a universal event ABI. |
| `sim.cell-data-reference` | Canonicalize the shared 16-byte typed-reference family. | Keep `0x00E82340` and `0x00E82420` as unresolved function alternatives. |
| `sim.cell-query-entry` | Split from linked-pool data/header records. | 28-byte entry, 24-byte data record, and 16-byte header are distinct. |
| `ui.window` | Keep separate from `utfwin.window`. | `UI::Window` has an exact opaque constructor; `UTFWin::Window` has a 524-byte framework layout. |
| `unknown.vtable.013f1a30` | Retain address-based candidate. | No class, namespace, constructor, or ownership is proven. |
| `unknown.map.00e5c780` | Retain mechanics-only candidate. | Owner, key/value domain, and message-handler identity remain unresolved. |
| `unknown.wrapper-forest` | Retain as a mechanics family. | Allocator/release labels remain source-purpose hypotheses. |

## Vtable and slot conflicts

- `0x01490BE8` is associated with both `Terrain::cTerrainSphere::GetSimDataRTT` and `Sporepedia::cSPAssetDataOTDB`; no unique owner is selected.
- `0x01485550` is a strong `App::cCellModeStrategy` candidate but also appears in an `Editors::cEditor` projection; the projection is preserved.
- UTFWin bases `0x013FA974` and `0x01419794` share a 21-slot prefix and are both reported as bases; neither is selected.
- UTFWin 40-slot families mix Window anchors with `cSPAssetDataOTDB::HasName`; this is cross-namespace candidate contamination, not a hierarchy.
- EditorModel has object-start and scanner candidates including `0x013EF110`, `0x013F2194`, `0x013F21D8`, `0x013F276C`, and `0x013F2D68`; no canonical base is chosen.
- SDK `IGameMode` order is Initialize 4, Dispose 5, OnEnter 6, OnExit 7, input 9-14, Update 15. The 27-slot Cell mode candidate places Initialize at 6, Dispose at 7, OnEnter at 8, OnExit at 9, input at 11-16, Update at 17. These remain separate interface and concrete-table contracts.
- `ITerrain` is recorded as 74 slots in one SDK export and 75 slots in the asset partition; 40-slot terrain scanner runs are not a class-size claim.
- The 27-slot `cGameInputManager` interface is strong, but its concrete vtable address is not pinned.
- A vtable size, object size, and vtable-reference count are separate dimensions and are not collapsed.

## Field-layout conflicts

- `cCreatureGameData`: persisted export `0x4C` versus SDK header `0x50`.
- `cSpeciesProfile`: persisted export `0xEEC` versus SDK/targeted allocation `0xA18`.
- `cPlanetRecord`: `mCivData`/`mTribeData` at `+0x15C`/`+0x170` versus `+0x188`/`+0x1A0`.
- `cStarManager`: five selected field offsets differ between SDK export and campaign summary; matching fields such as `+0xDC` do not validate the other alternatives.
- `cAdvectEntry`: Ghidra integer-like fields versus decompiler/current float reads.
- `App::Property`: imported 4-byte layout versus SDK 0x14 layout.
- `UTFWin::Message`: 0x0C base export versus effective anonymous payload footprint of at least 0x1C.
- `ResourceKey`: memory field order, construction order, and DBPF lookup order are distinct; current comments are not wire order.
- `cCellGame +0x5168`: four-byte int export versus byte flags in the targeted Initialize path.
- `cSpaceInventoryItem`: 05-empire-space and 12-field-archaeology disagree on the shared inventory prefix; the prefix cannot be applied to cSpaceToolData or cargo variants without adjudication.
- `cCellDataReference`: original 16-byte reference versus current one-word projection.
- `cCellObjectData`: original combat/resource fields in the middle range versus current opaque padding.
- `cSPUITextZoom`: SDK padding versus later targeted body writes; padding is not promoted to named fields.

## Inheritance disagreements

- `cCreatureBase` to `cCreatureAnimal` has a supported layout prefix in `03-creature.json`, but `02-gameplay-entity.json` correctly retains the lack of binary C++ inheritance proof. Canonical relation: `layout_prefix`, not language inheritance.
- `cGameData`-derived records share prefixes and identity fields, but remain a structural family, not one type or proven hierarchy.
- `cCellGame`, `cCellGFX`, and `cCellUI` are coordinated services/state holders; no demonstrated inheritance relation is added.
- `cCellQueryEntry` and `cCellQueryLinkedPoolData` are related by an arena/header relationship, not proven C++ inheritance.
- UTFWin 21-slot chains are explicit prefix evidence only; the two identical candidate bases remain unresolved.
- `IGameMode` implementation by concrete modes is structural interface evidence, not a universal ABI relation.

## Lifecycle contradictions

- Original mode lifecycle coordinates global Cell GFX/UI state; current source owns value members. The projections are not equivalent.
- `cObjectPool_` Initialize/Create SDK addresses differ from targeted bulk/create bodies.
- `cGameData::Write` has teardown-like body mechanics.
- `cCellDataReference_::Create` has a separate `0x00E82340` candidate.
- SpacePlayerData cached empire replacement is described as both destruction and AddRef/Release management.
- `0x00AEB720` is a create/append/dispatch wrapper despite a `HandleSpaceCommAction` SDK association.
- `EditorNamePanel::Initialize` is a contained SDK label after the recovered function entry.
- `cSpeciesProfile` allocation is observed but cache/transfer/destruction ownership is not.
- Cell UI rollover pool versus current vector projection is a non-equivalent lifecycle.
- App and Simulator game-mode manager lifecycle and ownership must remain separate.
- `FUN_00B21340` is labelled message-handler registration in a dossier but later map/noun-materialization artifacts provide a competing explanation.
- `cObjectPool_::Get` body conflicts with the index-accessor name and cannot define pool lookup.

## Naming-versus-evidence mismatches

- `cGameData / cEmpire` is a family shorthand, not one type.
- Unqualified `cGameModeManager` collides across App and Simulator.
- Generic `cObjectPool_` is not interchangeable with the Cell specialization.
- `UI::Window` is not `UTFWin::Window`.
- SDK names for `cGameData::Write`, pool functions, `cCellDataReference_::Create`, and `cCommManager::HandleSpaceCommAction` are retained separately from body mechanics.
- `EditorNamePanel::Initialize` is a contained label, not an exact function entry.
- `FUN_00B21340` retains the address and mechanics while its semantic label remains contested.
- `0x00B3D2A0` remains unnamed; a historical player-ID label is not sufficient.
- Decompiled types remain bounded and separate from direct field offsets.
- `cCellModeStrategy` dossier names and raw unnamed table targets remain separate.
- Current SimEvent/InputEvent, CellPool, CellGame, ResourceProvider, and mode-shell types cannot backfill original ABI or ownership.

## Claims that remain unresolved

- No positive original-process runtime trace exists; runtime behavior, event order, and teardown are not verified.
- No MSVC RTTI exists; vtable candidates and prefixes do not establish unique class identity.
- Generic pool function identity and failure/destruction semantics remain unresolved.
- The `0x00E82340`/`0x00E82420` Cell reference alias remains unresolved.
- `cGameData::Write` function identity remains contested.
- EditorModel, cGameInputManager, Terrain/Sporepedia, UTFWin bases, and other high-value vtable bases remain unresolved.
- ITerrain 74/75 slots, 40-slot scanner runs, and IGameMode 16 versus Cell mode 27 remain dimension-specific alternatives.
- Creature-game-data and species-profile sizes remain conflicted.
- Planet/star field maps and inventory prefixes remain conflicted.
- Message Entry `0x14` versus queue record `0x18`, queue order, priority, send/post timing, and removal remain unresolved.
- `FUN_00B21340` owner and semantic identity remain unresolved.
- Editor animation to IAnimWorld/renderer/pose integration remains unresolved.
- PROP, SPO, serializer stream framing, ClassSerializer bodies, and round-trip order remain unresolved.
- Anonymous 27-field/24-field space records lack exact sizes, fields, owner, consumers, and serialization.
- Star/planet generation, economy, mission, trade, palette, and global ownership remain unresolved.
- Unnamed simulator accessors cannot be assigned from adjacency or fan-in alone.
- pdtk grammar and toolkit protocol remain unresolved.
- Global shutdown order remains unresolved.
- Current source remains comparison-only and non-equivalent to original layouts and behavior.

The complete alternatives, source references, canonical IDs, and precedence rules are recorded in `19-audit-conflicts.json`.
