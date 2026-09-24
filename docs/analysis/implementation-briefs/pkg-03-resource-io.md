# Implementation Brief — Resource manager, DBPF/QFS I/O, and property substrate

Package: `PKG-03-RESOURCE-IO`  
Readiness: `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`  
Evidence: `SUPPORTED`

## Purpose

Provide bounded clean-room content bytes and original resource/property boundary.

## Authoritative semantic specification

["Authoritative: ResourceKey, DBPF metadata/bytes, typed payloads, bounded property entries", "Runtime: registries/databases/factories/cache/handles", "Persistent: packages and property/config streams", "Invariant: handles/caches are not gameplay entities"]

## Source evidence

- docs/analysis/gameplay-data-model.md:113-171
- docs/analysis/gameplay-state-machines.md:378-393
- docs/analysis/reconstruction-packages.md:271-336
- knowledgegraph/research/global-campaign-2026/track-k-engine-boundaries.json:293-364
- knowledgegraph/research/types/08-persistence-serialization.json
- knowledgegraph/research/types/09-asset-content.json

## Relevant original functions and structures

- 0x008de530 cResourceManager::Initialize
- PropertyList::Read/Write local typed entries with first-failure behavior
- parseDbpfIndex/extractDbpfRecord/qfsDecompress
- DatabasePackedFile: index/extents/holes/allocator
- PFIndexModifiable: index read/write
- PropertyList: local entries/parent/counter/Read/Write
- RecordInfo: offset/sizes/flags/saved state
- ResourceKey: type/group/instance

## Exact interfaces to implement

- IContentStore.lookup(ResourceKey) -> RecordLocator
- IContentStore.read(ResourceKey) -> bounded bytes or typed error
- IRecordCodec.decode(type_id, bytes) -> typed record
- IStream.read_exact/write_all/close
- IPropertyStore.read_local/write_local

## Dependencies and prerequisites

- DBPF/QFS evidence
- PKG-04 codecs
- PKG-05 readers
- SPORE package bytes
- malformed fixtures
- menu trace
- property round-trip

## Tests required

- asset_driven
- deterministic_unit
- fixture_comparison
- integration
- mini_package.dbpf
- original_binary_oracle
- real_asset_test.cpp
- tests/test_formats.py

## Acceptance criteria

- All required interface operations have explicit success, unsupported, and failure results.
- The listed invariants are covered by deterministic tests or explicit static tests.
- No original runtime behavior is claimed from host fixtures or decompilation alone.
- The package can integrate through the listed engine ports without importing raw original layouts.
- Unknowns and divergences remain visible in code/test documentation and the evidence register.

## Known limitations and unresolved assumptions

- Async scheduling
- B1 one-package provider is not original multi-package manager
- Cache eviction
- Directory semantics
- Priority
- Property wire format
- QFS call site
- Typed readers are not general property persistence

## Validation boundary

Use STATIC_ONLY, DECOMP_DIFFERENTIAL, FIXTURE, INTEGRATION, or REPLACEMENT_HOOK only as specified. ORIGINAL_RUNTIME_ORACLE is required before an original-compatibility claim; a synthetic hook or generated fixture is not an original oracle.
