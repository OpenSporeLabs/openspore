# Implementation Brief — Cell content and resource record semantics

Package: `PKG-05-CELL-CONTENT`  
Readiness: `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`  
Evidence: `SUPPORTED`

## Purpose

Decode direct Cell content records/references while separating static content from live gameplay and save state.

## Authoritative semantic specification

["Authoritative: direct Cell layouts and hard references", "Runtime: lazy cCellDataReference handles", "Persistent: direct records only", "Invariant: direct record is not live Cell/GFX/save record"]

## Source evidence

- docs/analysis/gameplay-data-model.md:119-150
- docs/analysis/reconstruction-packages.md:409-486
- knowledgegraph/research/gameplay-state-machines.json
- knowledgegraph/research/global-campaign-2026/track-d-sim-cell.json:218-224
- knowledgegraph/research/types/09-asset-content.json

## Relevant original functions and structures

- 0x00e82340 candidate is not merged with 0x00e82420 Create
- parseCellCellResource
- parseCellEffectMapResource
- parseCellLootTableResource
- parseCellPopulateResource
- parseCellStructureResource
- parseCellWorldResource
- cCellCellResource TypeID 0xDFAD9F51, 796 bytes
- cCellEffectMapResource TypeID 0x433FB70C, 8+28N
- cCellGlobalsResource TypeID 0x2A3CE5B7, 276 bytes/69 fields
- cCellLootTableResource TypeID 0xD92AF091, 36+28N
- cCellPopulateResource TypeID 0xDA141C1B, 16+76N
- cCellStructureResource TypeID 0x4B9EF6DC, 28+40N
- cCellWorldResource TypeID 0x9B8E862F, 16+12N+24N

## Exact interfaces to implement

- ICellContentCatalog.records(TypeID) -> typed record set
- ICellReferenceResolver.resolve(record, reference) -> typed reference or error
- ICellContentLoader.load(ResourceKey) -> immutable content record

## Dependencies and prerequisites

- C++/Python differential
- Cell packages
- PKG-03
- PKG-04
- SDK layouts
- alias adjudication
- canonical manifest
- negative reference fixtures

## Tests required

- asset_driven
- cell_* tests
- decomp_differential
- deterministic_unit
- fixture_comparison
- integration
- tools/spore/cellres/

## Acceptance criteria

- All required interface operations have explicit success, unsupported, and failure results.
- The listed invariants are covered by deterministic tests or explicit static tests.
- No original runtime behavior is claimed from host fixtures or decompilation alone.
- The package can integrate through the listed engine ports without importing raw original layouts.
- Unknowns and divergences remain visible in code/test documentation and the evidence register.

## Known limitations and unresolved assumptions

- 0x00e82340/0x00e82420 alias
- Decoders do not execute world/AI/loot
- GFX associations separate
- Loot settlement
- Runtime use
- Soft-ID selection
- World placement
- cCellSerializableData not a direct record

## Validation boundary

Use STATIC_ONLY, DECOMP_DIFFERENTIAL, FIXTURE, INTEGRATION, or REPLACEMENT_HOOK only as specified. ORIGINAL_RUNTIME_ORACLE is required before an original-compatibility claim; a synthetic hook or generated fixture is not an original oracle.
