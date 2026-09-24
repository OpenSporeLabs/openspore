# PKG-03 Resource I/O Unknowns

Package: `PKG-03-RESOURCE-IO`  
Status: `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`  
Scope: host resource/content and property boundary implemented for this wave.

## Contract boundary

- `ResourceKey` is a host type/group/instance tuple. Wildcard `0xFFFFFFFF` is rejected by `IContentStore::lookup` and `read`; the wildcard rule is a host selection rule, not a recovered original query result.
- `DbpfContentStore` borrows one DBPF image, parses the 32-bit DBPF v3 index, validates record extents, extracts raw or QFS-decompressed bytes, and rejects non-zero/non-`0xFFFF` compression flags.
- `RecordLocator` exposes the selected key, source extent, stored size, memory size, and compression. `ReadResult` returns owned bytes or a typed `ContentErrorCode` and diagnostic text.
- `ResourceProviderContentStore` reuses the existing B1 `IResourceProvider::fetch` seam. It supports reads but returns `unsupported_operation` for locators because B1 exposes no metadata.
- `RecordCodecRegistry` maps a 32-bit type ID to a caller-owned `IRecordCodec`. A successful decode must contain a typed `std::any` value; failure results do not expose a record.
- `IStream::read_exact` and `write_all` retry short positive transfers, return the transferred-prefix count on failure, reject null pointers and closed streams, and synthesize short-read/short-write when a provider makes no progress. `close` reports the first result and reports a repeated close as `already_closed`.
- `LocalPropertyStore` stores local scalar/key values, supports local-first parent lookup, bounds parent depth and entry count, detects parent cycles, and serializes a deterministic host-local `OPRP` version-1 stream. Unsupported property tags, versions, malformed framing, duplicate IDs, limits, and stream failures are explicit errors.

## Evidence classes

### BLUEPRINT_BACKED

- The package requires `IContentStore::lookup(ResourceKey)`, `IContentStore::read(ResourceKey)`, `IRecordCodec::decode(typeId, bytes)`, `IStream::read_exact/write_all/close`, and `IPropertyStore::read_local/write_local`.
- The semantic source identifies a stable complete type/group/instance resource identity, DBPF index/extent metadata, QFS decompression, and typed records.
- The source identifies local-first property lookup, parent fallback, an operation counter, and property read/write boundaries.
- The source explicitly leaves original property bytes, parent encoding, and round-trip behavior unresolved.

### EXISTING_OPENSPORE_BEHAVIOR

- `Dbpf`, `Stream`, and `compat::IResourceProvider` are reused rather than replaced. The DBPF/QFS parser and B1 provider remain the existing clean-room seams.
- The DBPF v3 header/index shape, 28-byte rows, QFS `10FB`/`50FB` envelope, and committed synthetic fixture behavior are preserved.
- The current provider contract has only a boolean fetch result and error string; it does not expose record locators or a typed not-found/provider distinction.
- The host stream layer is an in-memory non-owning input/output abstraction; it does not claim to model every original `IO::IStream` implementation.

### BOUNDED_INFERENCE

- A `DbpfContentStore` borrows its package bytes for its lifetime; callers must keep the image alive.
- A `ResourceProviderContentStore` borrows its provider for its lifetime; callers must keep the provider alive.
- The first matching DBPF index row is selected by the existing linear lookup. Duplicate-key precedence is not promoted as original behavior.
- `0` and `0xFFFF` are the accepted compression values for this bounded DBPF path. Other values are unsupported instead of guessed.
- `PropertyLimits::maxEntries` defaults to 4096, and `LocalPropertyStore::kMaxParentDepth` is 64. These are host safety bounds, not recovered original limits.
- Property writes sort entries by numeric ID and reject duplicate IDs before writing. This provides deterministic host output only.
- The operation counter increments on successful local mutation only. Reads, parent traversal, and serialization do not increment it because their original counter semantics are unresolved.
- A property read replaces local state after accepted framing and may retain entries decoded before a later first failure. This is an explicit first-failure host policy, not transactional rollback.
- `IStream::close` leaves the stream open when `do_close` fails, allowing the caller to retry; repeated successful close is reported as `already_closed` rather than silently ignored.
- `RecordCodecRegistry` owns registered codec objects and rejects duplicate or null registrations without replacing existing entries.
- The provider adapter maps all provider fetch failures to `provider_failure`; the existing B1 interface cannot distinguish absence from corruption or provider error.

### PROVISIONAL

- `OPRP` version 1 is a host-local property wire format only. Its header, little-endian count, type tags, and ResourceKey order are not an original PROP specification.
- The host property codec supports only boolean, signed 32-bit integer, unsigned 32-bit integer, float, and ResourceKey values. String, text, vector, color, transform, pointer, and other SDK-declared property categories return `unsupported_property` until a separate evidence-backed codec exists.
- Host ResourceKey storage is type/group/instance. The committed evidence also records differing original memory/serialization orders; this implementation does not claim any of those layouts.
- `std::any` is the generic typed-record carrier. PKG-04 and later codec packages own the concrete record types and validation.
- `MemoryInputStream` and `MemoryOutputStream` are deterministic test implementations, not replacements for every file, compression, or platform stream.

## Intentional deviations and non-claims

- This is a one-package host store, not the original multi-package resource manager. Mount order, priority, directory semantics, cache lookup, cache eviction, reload, flush, and async scheduling are not implemented.
- The B1 provider adapter is read-only and cannot provide `RecordLocator` metadata.
- DBBF/64-bit package variants, unknown compression formats, unknown property formats, and unknown property types fail explicitly.
- The property codec is not a PROP/SPO compatibility implementation, and typed record readers are not general property persistence.
- Host fixtures and static evidence do not establish original-runtime equivalence. No original save/load or resource-manager runtime claim is made.
- The implementation does not access or modify `SPORE/` assets. The package test uses only the committed synthetic fixture and generated host byte vectors.

## Bounded unknowns

| Unknown | Affected code | Current bounded behavior | Resolution evidence still required |
|---|---|---|---|
| Async resource scheduling | `IContentStore` and future manager integration | Synchronous read/lookup only | Original manager/request trace and scheduling contract |
| Multi-package lookup priority | Future content-store composition | One borrowed package or B1 provider | Original database registration/order and runtime selection trace |
| Directory/package resolution | Future provider integration | Caller supplies one image/provider | Original directory and package resolution behavior |
| Cache hit/miss/eviction | Future manager integration | No cache layer | Original cache lifecycle and resource identity trace |
| DBPF record index flags and duplicate precedence | `DbpfContentStore::lookup` | Bounded flags and first-row lookup | Original package/index variant evidence and duplicate-key behavior |
| QFS call site and stream ownership | `DbpfContentStore::read` and future record handles | Decode borrowed bytes into owned `ReadResult` | Original QFS caller and record stream lifetime evidence |
| Original `IO::IStream` status/close semantics | `IStream` | Explicit host short-transfer and close results | Original stream interface bodies or controlled original trace |
| Original property runtime layout | `LocalPropertyStore` and property values | Host struct/map only; no raw original layout | Resolved Property/PropertyList layout evidence |
| Original PROP wire bytes and version policy | `LocalPropertyStore::read_local/write_local` | OPRP v1 host-local codec | Decompiled Read/Write body plus captured property fixture/round trip |
| Parent encoding and ownership | `IPropertyStore::parent` and lookup | Non-owning parent pointer with cycle/depth checks | Original parent pointer/lifetime and read/write treatment |
| String/text and aggregate property encodings | Property codec | Explicit `unsupported_property` | Type-specific property body or fixture evidence |
| Typed record schemas | `IRecordCodec` implementations | Registry boundary only | PKG-04/PKG-05 codec layouts and differential fixtures |
| Original runtime cache/reference ownership | Future record and manager integration | Bytes are copied out of the provider | Original record open/close and reference-count trace |

## Validation performed

- `ctest --test-dir /tmp/opencode/openspore-build --output-on-failure -R '^(manifest_test|assets_resource_io|assets_synthetic|assets_cell_content|assets_pkg04)$'`
- `python3 -m unittest tests.test_formats` — 15 tests passed
- `git diff --check`
- Aggregate CMake build completed successfully; four GPU/display tests were separately parked by an active external machine-lock owner after the formatting pass.
