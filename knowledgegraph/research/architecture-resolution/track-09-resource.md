# Track 9 — Resource identity, providers, and cache layers

## Resolution

**Status: `RESOLVED_SUPPORTED` for semantic layering; runtime package precedence, cache eviction, and async behavior remain provisional.**

Manager/provider content requests use the full numeric `ResourceKey` triple `(instanceID, typeID, groupID)`. The Cell local `cCellDataReference_` list is a separate contract keyed by `(instanceID, serializer*)`; it is not a manager/provider request key. The binary does not use one identity everywhere:

- `ResourceKey` memory order is `instance,type,group`.
- DBPF v3 index rows serialize the same identity as `type,group,instance`; row position is not conceptual identity.
- `DatabasePackedFile` keeps a `map<ResourceKey, PFRecordBase*>` at `+0x2e8` and returns a separate record/stream lease.
- `cResourceManager` layers database, factory, type-mapping, cache, and filename registries.
- Manager cache lookup is key-based; a cache hit returns a separate runtime object.
- Manager/provider requests (including FindRecord, database/factory selection, and cache lookup) use full numeric `ResourceKey`; Cell local lookup is outside that contract and uses `(instanceID, serializer*)`.
- `cCellDataReference_` is a separate lazy local-reference layer keyed by `(instanceID, serializer pointer)`, not by the full key.
- `ResourceObject`, `CachedResourceObject`, `cCellResource`, record leases, and serializer pointers are runtime/ownership identities, not replacements for the content triple.

Architecture decision: preserve the manager/provider full-key contract, but keep Cell-local pair identity, representation order, package order, provider order, cache identity, lease/reference state, and runtime object identity separate. Runtime package precedence, cache eviction, and async behavior remain provisional. No implementation was made.

## Identity and ordering matrix

| Layer | Identity | Order | Decision |
|---|---|---|---|
| Conceptual content | Full `instance/type/group` triple | Field-aware equality | `required_for_semantics` |
| Manager/provider request | Full numeric `ResourceKey` | Manager/database/factory/cache request boundary | `required_for_semantics` |
| `ResourceKey` memory | `instanceID@0`, `typeID@4`, `groupID@8` | SDK order: instance, type, group | `required_for_semantics` |
| DBPF row | `type,group,instance` plus extent/compression fields | File/index order only | `replaceable_infrastructure` |
| Database map | `ResourceKey` → `PFRecordBase*` | Map lookup, not raw row order | `required_for_semantics` |
| Manager type mapping | resource type ↔ record type(s) | Mapping before DB/factory selection | `required_for_semantics` |
| Manager cache | Full numeric `ResourceKey` or alternate `pCacheName`; not the Cell pair | First cache hit/success | `replaceable_infrastructure` |
| Cell local reference | `(instanceID, serializer*)`; not a manager/provider key | First list match | `required_for_semantics` |
| Record lease | `IRecord*` plus open/ref state | Open/close lifetime | `runtime_compatibility_only` |
| Runtime object | `ResourceObject*` with embedded key/refcount | Allocation/ownership order | `runtime_compatibility_only` |

`0x00e82340` is the separate 24-byte node allocator/helper. `0x00e82420` is `cCellDataReference_::Create`: it searches by instance and serializer, calls the allocator on a miss, links the node through `DAT_016b44f0`, and returns the embedded 16-byte payload. This is not an alias pair.

## Provider and cache semantics

The current manager vtable is at `0x01436ae8` and has 38 slots. `cResourceManager` construction at `0x008e20c0` initializes separate database, factory, type-mapping, cache, and filename state.

- `0x008de280` / `0x008de360`: iterate registered caches and return the first cache hit for a key.
- `0x008de3b0`: call `ICache::CacheResource` until the first successful insertion.
- `0x008de400`: flush one cache or every registered cache.
- `0x008e1d50`: add/remove caches with priority-ordered storage and refcount operations.
- `0x008df460`/`0x008df700`: cache-first request body; `0x008df700` is an SDK/interior anchor, not a new identity.
- `0x008df0b0`: related database/factory/record-construction load body reached by the short `0x008df430` wrapper.

Minimum safe manager/provider contract: requests use the full numeric `ResourceKey`; Cell local `cCellDataReference_` lookup is separate and uses `(instanceID, serializer*)`. Manager cache lookup is full-key or alternate-cache-key based, first-hit/first-success is replaceable infrastructure, and cache eviction plus reload/private object identity remain provisional.

## Package precedence (static policy; runtime provisional)

`0x008e0d30` is the current `RegisterDatabase` body. It rejects duplicate registration, inserts by priority through `0x008de940`, and supports removal through `0x008e07b0`.

`0x008de940` stores database pointer and priority in list nodes and inserts before the first lower-priority node. The list is therefore a static descending-priority model; equal priorities remain in registration/traversal order. `0x008de310` traverses that list and returns the first database whose record path succeeds. An explicit database override bypasses the global list. This is a provisional runtime model until boot registration and duplicate selection are observed.

`0x008df9b0` first consults the manager resource-type-to-record-type mapping, then follows the database path; on success it can write the corrected real key. `0x008dfb20` returns the first registered factory whose `CanConvert(resourceType,recordType)` succeeds. Factory and database precedence are provider-list policies, not key ordering; runtime precedence remains provisional.

## Cell reference lifecycle

- `0x00e82490` allocates and self-links the 12-byte `DAT_016b44f0` sentinel; its caller is `0x00e4c8c0`.
- `0x00e823a0` increments the reference counter and lazily calls `0x00e822c0` when `mpResource` is null.
- `0x00e82280` releases all live resource pointers but retains list nodes.
- `0x00e823e0` releases resources and frees nodes.
- `0x00e824d0`, called from the mode teardown path, clears resources, destroys nodes, and frees the sentinel.

This local Cell list is not the manager `ICache`. A Cell hit does not prove a manager cache hit, and the serializer pointer is process-local type discrimination rather than portable content identity.

## Nine adversarial steps

| Step | Result |
|---|---|
| 1. One global identity | Rejected: the Cell pair, cache key, record lease, and object pointer are separate. |
| 2. Global versus layered provider | Layered providers supported; the manager coordinates rather than owns every layer. |
| 3. DBPF order | Row order rejected as identity; database map and package priority govern lookup. |
| 4. ResourceKey memory order | Field order is explicit and distinct from DBPF order. |
| 5. Serializer versus key | Cell local identity is `(instance,serializer)`; the loaded object still carries `mNameKey`. |
| 6. Cache versus lease/reference | Cache key, record lease, and runtime object/refcount are separate. |
| 7. Package precedence | Static list mechanics support a provisional descending-priority/first-successful model; runtime precedence and duplicate selection remain provisional. |
| 8. Cell hit/miss/release | Static separator completed: pair hit returns node+8; miss allocates/relinks; null resource lazily loads; clear/destroy are distinct. |
| 9. Architecture/runtime | Semantic layering is portable; x86 offsets, vtable slots, and pointer serializer identity are compatibility details. Runtime trace not justified/performed. |

## Freeze

- Full `(instance,type,group)` manager/provider request identity.
- Cell local `cCellDataReference_` lookup is the separate `(instanceID, serializer*)` pair identity.
- `instance,type,group` memory order versus `type,group,instance` DBPF order.
- Separate database, factory, type-mapping, cache, and Cell-reference providers.
- Static database priority/list mechanics and explicit override; runtime package precedence and duplicate selection remain provisional.
- Full-key manager cache lookup and first-success insertion; eviction/final-release timing remains provisional.
- `cCellDataReference_::Create` at `0x00e82420`; `0x00e82340` is its node allocator/helper.
- Cell local pair key and separate resource-pointer release/node destruction.
- Runtime pointer/refcount/lease identity is not durable content identity.
- Current B1 is one-package exact T:G:I byte access, not original manager parity.

## Defer

- Exact public-wrapper mapping for `0x008de530`, `0x008df0b0/0x008df460/0x008df700`, `0x008e1d20`, and `0x008e1750` where SDK labels and current boundaries differ.
- ResourceKey name parsing/hash/rekey behavior.
- Runtime package precedence, boot registration order, and duplicate selection.
- Runtime cache hit/miss/factory/preload/release order.
- Cache eviction, reload replacement, and post-flush refcount timing.
- Async scheduling/completion/cancellation and original QFS call site.
- Duplicate same-key rows within one package and duplicate package content.
- Concrete ResourceObject factory/final-release ownership.
- Any replacement implementation.

## Blockers

1. **Critical:** no positive original trace of one key through registration, mapping, cache, factory, record open, resource construction, Cell reference, preload, and release.
2. **High:** current vtable entries and historical SDK labels disagree at several requested addresses; adjacency cannot merge them.
3. **High:** static cache traversal does not prove runtime package precedence, duplicate selection, eviction, replacement, or final-release timing.
4. **High:** Cell pair-keyed local references have no observed runtime relationship to manager/provider full-key requests or cache precedence.
5. **High:** async request scheduling, completion, and cancellation are not covered by the static request body.
6. **Medium:** DBPF row serialization order, ResourceKey ordering, and database list order are distinct but original write order is not fully characterized.

## Sources

- Read-only Ghidra `SporeApp.exe`: `0x01436ae8`, `0x008e20c0`, `0x008de530`, `0x008de360`, `0x008de3b0`, `0x008df0b0`, `0x008df460`, `0x008df700`, `0x008df9b0`, `0x008dfb20`, `0x008e0d30`, `0x008e1d20`, `0x008e1750`, `0x008da3d0`, `0x00e82340`, `0x00e82420`, `0x00e823a0`, `0x00e82280`, `0x00e823e0`, `0x00e824d0`, `0x00e82490`, `0x016b44f0`.
- SDK `ResourceKey.h`, `IResourceManager.h`, `ICache.h`, `ResourceObject.h`, `Database.h`, and `cCellResource.h`.
- `knowledgegraph/research/data-model/01-dbpf-resource-formats.json:153-175,188-233,248-264,286-311`.
- `knowledgegraph/research/types/09-asset-content.md:31-40,61-75,92-120`.
- `knowledgegraph/research/conflicts/track-a-type-signature.json:241-420`.
- `src/compat/ResourceProvider.hpp:32-59` and `src/assets/Dbpf.cpp`.

## Limitations

Ghidra was read-only and explicitly targeted `SporeApp.exe`; no Ghidra mutation, implementation, `SPORE/` inspection, or `spore.db` access occurred. No runtime trace was performed. Decompiler register recovery, SDK/live address boundaries, and vtable ownership remain bounded evidence. The report is an architecture investigation, not implementation authorization.
