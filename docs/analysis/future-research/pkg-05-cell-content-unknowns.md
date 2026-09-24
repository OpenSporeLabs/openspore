# PKG-05 Cell Content Unknowns

Package: `PKG-05-CELL-CONTENT`  
Status: `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`  
Scope: immutable direct Cell content records, catalog lookup, and one-hop hard-reference validation.

## Contract boundary

- `CellContentValue` has exactly twelve alternatives: Globals, EffectMap, BackgroundMap, Structure, World, RandomCreature, Powers, LookTable, LookAlgorithm, LootTable, Populate, and Cell.
- `CellContentLoader::load(ResourceKey)` borrows PKG-03 `IContentStore`, requires a complete supported key, reads owned bytes, dispatches to the matching existing `CellResource` parser, and returns a `shared_ptr<const CellContentRecord>` on success.
- `CellContentRecord` owns one immutable `ResourceKey` and one immutable typed value. It exposes checked typed access through `as<T>()` and does not expose live Cell, GFX, AI, world-placement, animation, or save state.
- `CellContentCatalog` indexes immutable records by complete type/group/instance key and by TypeID. Exact duplicate keys are rejected without replacement. Repeated-TypeID result vectors are sorted by complete key.
- `CellReferenceResolver` enumerates decoded nonzero hard-reference candidates in record field/entry order and performs one catalog lookup only. It does not recurse, load through the provider, retain a runtime reference handle, or invoke world/AI/loot behavior.
- A stored zero reference word is treated as a nullable/empty host field and is omitted from hard-reference enumeration. A nonzero reference whose catalog target is absent returns `reference_not_found`; a fabricated zero or otherwise nonmatching reference returns `invalid_reference`.
- Type/group context is checked before resolution. An external or unsupported target TypeID, such as the current advect target, returns `unsupported_type` rather than an untyped success.
- Failure results are explicit: invalid key, unsupported TypeID, provider/not-found failure, decode failure, malformed catalog record, duplicate key, invalid reference, source mismatch, type mismatch, target absence, and ambiguous partial identity.
- The loader is decode-only. It does not publish a Cell cache, execute procedural world/AI/loot behavior, associate GFX, handle `cCellSerializableData`, or provide a writer.

## Evidence classes

### BLUEPRINT_BACKED

- The frozen package requires `ICellContentCatalog::records(TypeID)`, `ICellReferenceResolver::resolve(record, reference)`, and `ICellContentLoader::load(ResourceKey)`.
- The authoritative package boundary identifies twelve direct Cell TypeID records, typed hard references, and a state split between static content, runtime handles, presentation, and save state.
- The blueprints require TypeID/extent checks, explicit unknown TypeID/truncation/count/extent/reference errors, decode-only direct records, and no generic CellSerializer envelope.
- The source model identifies the twelve direct layouts, including fixed Globals/Cell/Powers records and count-bounded variable records.
- The static model keeps `cCellDataReference_` lazy resolution and use-counted handles outside this immutable catalog/reference layer.
- The static model separates direct content from `cCellGame`, `cCellObjectData`, `cCellGFX`, `cCellUI`, and `cCellSerializableData`.
- Soft random-creature identity, procedural placement, loot settlement, and runtime selection are not promoted to hard references or executable behavior.

### EXISTING_OPENSPORE_BEHAVIOR

- PKG-03 supplies host `ResourceKey` as type/group/instance and `IContentStore::read(ResourceKey)` with explicit `ContentErrorCode` and owned bytes.
- Existing `CellResource` parsers supply all twelve typed record structures, TypeID constants, fixed sizes, count/span checks, and diagnostics. PKG-05 dispatches to them without duplicating wire layouts.
- Existing direct parser semantics decode serialized u32 reference words as resource instances rather than host pointers.
- Existing Cell record structures expose field names and ordered nested entries; PKG-05 converts only the bounded reference roles listed below.
- Existing `CellContentValue` uses a closed `std::variant`, and the catalog returns `shared_ptr<const CellContentRecord>` values. This is current clean-room behavior, not original ABI behavior.

### BOUNDED_INFERENCE

- The current direct TypeID set is the complete set for this package: `0x2A3CE5B7`, `0x433FB70C`, `0x612B3191`, `0x4B9EF6DC`, `0x9B8E862F`, `0xF9C3D770`, `0x754BE343`, `0x8C042499`, `0xDBA35AE2`, `0xD92AF091`, `0xDA141C1B`, and `0xDFAD9F51`.
- A zero instance word is a nullable/empty field for the host reference projection. This keeps absent fields out of hard-reference enumeration; it is not a recovered original null ABI.
- A decoded field supplies TypeID context when known. Otherwise its target retains a wildcard TypeID/group and cannot resolve successfully until a bounded type mapping is evidenced.
- Hard-reference candidates are derived for Globals world/effect/background/start/look slots; Cell structure/content/AI-output slots; World populate/advect slots; Populate distribute/cluster Cell slots; LookAlgorithm table slots; LootTable Cell/table slots; and Structure attachment/effect slots.
- RandomCreature `creatureID` is soft identity and is not enumerated as a hard reference.
- Reference enumeration and catalog resolution are bounded by the record's accepted payload extent and current parsed entry vectors. Resolution performs one direct catalog scan and no transitive graph walk.
- Exact duplicate `ResourceKey` insertion preserves the first immutable record. Insertion does not replace or merge records.
- Catalog result order is host deterministic type/group/instance order. Provider/package enumeration order is not claimed.
- A wildcard group in a decoded reference cannot select among multiple catalog records with the same TypeID/instance. The resolver reports ambiguity rather than guessing.
- Provider `not_found`, malformed package/index/decompression failures, unsupported provider operations, and parse failures remain distinct result paths through mapped diagnostics.
- The catalog does not retain the bytes after a successful parse; its immutable identity is the record key and typed decoded value.

### PROVISIONAL

- The exact current field-to-hard-reference classification is bounded by SDK/layout evidence and must be revised if a field is a union, discriminator-controlled slot, soft ID, or presentation-only value.
- Current wildcard targets for Cell content/effect slots and advect targets are intentionally unresolved rather than assigned guessed TypeIDs.
- The closed variant is a host convenience and does not reproduce original class layout, inheritance, vtables, pointer widths, or serializer objects.
- Shared immutable pointers are a host ownership mechanism and do not reproduce `cCellResource`, `cCellDataReference_`, loader leases, cache hits, or use counters.
- Synthetic byte vectors and deterministic unit tests validate current contracts only; they are not original-runtime or original-byte oracles.
- Build-system integration is complete through the aggregate CMake target `assets_cell_content`.

## Intentional deviations and non-claims

- The package does not implement original multi-package priority, directory lookup, cache eviction, lazy runtime reference creation, reload, async loading, or exact release timing.
- Direct content is not `cCellSerializableData`; this package has no profile/save codec or field-survival claim.
- Decoders do not execute world selection, procedural marker placement, AI, combat, loot selection/settlement, animation, effects, or GFX preload/association.
- Advect and other non-catalog target types fail explicitly instead of being decoded or represented as generic records.
- Reference enumeration omits zero/nullable host fields and does not expose a universal optional-reference wrapper. Missing nonzero targets and fabricated invalid references use distinct error codes.
- The catalog resolves TypeID/instance with optional group narrowing because direct record words generally do not carry a complete `ResourceKey`. It does not claim that this is the original lookup identity.
- Repeated decode and catalog insertion are deterministic in the current host, but no original enumeration, cache, or duplicate-package precedence claim is made.
- No Ghidra work, `SPORE/` access, original runtime execution, runtime oracle, or evidence promotion was performed for this implementation.

## Bounded unknowns

| Unknown | Affected code | Blast radius | Current bounded behavior | Future evidence required |
|---|---|---|---|---|
| `0x00E82340` versus `0x00E82420` identity and `cCellDataReference_::Create` lifecycle | Future runtime-reference integration; not this static resolver | Any attempt to adopt original runtime handles, cache ownership, reload, or release | One-hop catalog lookup only; no runtime handle is created | Static alias adjudication plus controlled original handle lifetime trace |
| Complete group identity of direct hard-reference words | `appendReference`, `CellReferenceResolver::resolve` | Cell, Structure, Loot, Populate, and Globals references without a supplied group | Decode TypeID plus instance; group narrows lookup when caller supplies it; otherwise ambiguity is explicit | Original serializer/lookup body and complete-key fixture mapping |
| Null/sentinel semantics beyond zero | `appendReference`, all reference-bearing records | A future codec or compatibility adapter might distinguish absent, invalid, and sentinel values differently | Zero omitted as host nullable absence; synthetic zero is invalid | Type-specific writer/consumer evidence and negative fixtures |
| TypeIDs for Cell `break`, `pieces`, `leak`, `expel`, `explosionTable`, `poison`, AI outputs, and Structure effect words | `appendCellReferences`, `appendStructureReferences` | Those targets cannot resolve through the direct twelve-record catalog | Wildcard target remains explicit and resolves as `unsupported_type` | Type-specific serializer consumers or complete manifest rows |
| Advect payload and reference contract | `appendWorldReferences`, `CellWorld` catalog target | World reference validation only; no advect decoder/runtime selection | `0x04805684` is enumerated but intentionally unresolved | Exact advect layout, key context, and bounded decode evidence |
| Structure effect and attachment field semantics | `appendStructureReferences` | Structure/effect graph completeness | Current field-name mapping is retained; no GFX or effect execution | Type-specific consumers and manifest/differential fixtures |
| Loot entry discriminator versus independently populated slots | `appendLootReferences` | Could expose a nonactive Cell/table slot as a hard reference if future fixtures populate both | Only nonzero Cell/table words are enumerated; no reward settlement | Original entry writer/consumer and negative fixtures |
| Globals alias vocabulary and start-cell/look slots | `appendGlobalsReferences` | Reference count and field-role mapping for Globals | Existing SDK/layout names plus retained aliases are used | Canonical manifest and serializer field ownership evidence |
| Multi-package precedence and duplicate package keys | PKG-03 store composition and future loader integration | Which bytes a repeated `ResourceKey` load returns | Loader reads the supplied store result and catalog rejects duplicate decoded keys | Original database registration/order and controlled load trace |
| Runtime use, world placement, soft-ID selection, AI, and loot settlement | No PKG-05 runtime code | Downstream PKG-06/PKG-09 behavior only | Static references are exposed; no execution | Matched original runtime and differential traces |
| Direct-record writers and versioning | No writer in this package | Round-trip or authoring compatibility | Decode-only bounded layouts | Original writer bodies, fixtures, and version evidence |
| Original runtime equivalence | Entire package | Any compatibility claim | Explicitly not established | ORIGINAL_RUNTIME_ORACLE plus matched fixtures and differential evidence |

## Validation performed

- Strict direct C++17 compilation of `CellContent.cpp` and `CellResource.cpp` passed before package edits.
- The nine existing Cell-resource test binaries compiled with `-std=c++17 -Wall -Wextra -Wpedantic -Werror`; each was run with nonexistent package paths and returned its normal SKIP result without accessing `SPORE/`.
- The direct PKG-05 test compiles `cell_content_test.cpp`, `CellContent.cpp`, `CellResource.cpp`, `ResourceKey.cpp`, `ResourceStore.cpp`, and `Dbpf.cpp` under the same strict gate and reports `cell content: ALL PASS`.
- Final sanitizer, formatting/diff, and repeat existing-test commands are recorded in the implementation handoff after completion.
