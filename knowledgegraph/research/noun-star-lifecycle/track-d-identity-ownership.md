# Track D — runtime identity and ownership

## Scope and evidence boundary

This report is limited to runtime identity, ownership, invalidation, and survival. It does not implement behavior and does not alter the original executable, `SPORE/`, shared final artifacts, or other worker reports.

The binary baseline is `SporeApp.exe` 3.1.0.22, SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`, `x86:LE:32:windows`, image base `0x00400000`. The current Ghidra program is open and was queried read-only. The strongest evidence is static: decompilation, disassembly, imported structures, data layouts, xrefs, and bounded call paths. There is no positive original-process gameplay, mode-transition, save, or load trace. “Supported” below therefore means statically supported, not runtime-validated.

Evidence precedence is:

- direct Ghidra bodies, layouts, and xrefs;
- the existing root-closure and architecture-blocker reports, used as bounded historical context rather than counted as independent binary proof;
- the authoritative semantic, gameplay-data, gameplay-state-machine, serialization, and root-closure documents;
- current OpenSpore source as a clean-room comparison only.

The semantic blueprint explicitly keeps resource identity, runtime entities, caches, save state, and object registry separate (`docs/analysis/semantic-blueprint.md:51-65,101-107`). The serialization model is stricter: a pointer or cache is not save state merely because it is reachable from a persistent owner (`docs/analysis/serialization-model.md:23-25,294-364`). The architecture-blocker report retains four distinct noun/star root slots but unresolved publication, equality, and teardown (`docs/analysis/architecture-blockers.md:31-91`).

## Executive finding

There is no single original runtime identity. The evidence supports at least seven identity axes that must remain separate:

1. **ResourceKey** identifies packaged content by a complete type/group/instance triple.
2. **Noun identity** identifies a game-data category/type through a 32-bit noun ID and the noun manager’s category projection.
3. **Star identity** is a domain identity carried by a live `cStar` and/or a separate refcounted `cStarRecord`; the two representations are not physically the same object.
4. **Game-object identity** is the address and virtual type of a live `cGameData`-derived object, with intrusive reference lifetime.
5. **Pointer identity** is process-local address equality and is never a durable content or save identity.
6. **Handle identity** is an address-like runtime reference or wrapper used to borrow or own a live object, record, resource, or cache entry; handle validity depends on its owner and release policy.
7. **Registry identity** is the key used by a particular registry plus the registry owner. The same domain object can be reachable through multiple registries and caches, and a registry key need not be an object address or durable global ID.

The central ownership rule is: **the owner stores a reference or key; accessors usually return borrowed pointers; a registry erase releases the registry’s reference but does not necessarily invalidate every other borrowed pointer or cache.** The noun, empire, star-record, and resource paths each show this rule directly.

## 1. Identity model

### 1.1 ResourceKey: content identity

Ghidra’s `ResourceKey` type is 12 bytes with the observed field order:

```text
+0x00 uint32 instanceID
+0x04 uint32 typeID
+0x08 uint32 groupID
```

The semantic order is the complete type/group/instance tuple, not an unlabelled memory layout. The serialization model and gameplay-data model both require explicit named conversion before treating the structure as a serialized field order (`docs/analysis/serialization-model.md:74-82`; `docs/analysis/gameplay-data-model.md:111-117`). A partial or wildcard key is not a content identity. Current OpenSpore encodes that rule as `ResourceKey::isComplete()` and rejects incomplete keys before reading (`src/assets/ResourceKey.hpp:8-18`; `src/assets/CellContent.cpp:253-271`).

ResourceKey is therefore a **stable content locator**, not a noun ID, star ID, political ID, live object address, registry node address, or save-slot object reference. The same key may select a different typed object after a factory or codec changes, and the same live object may be referenced by more than one domain-specific record.

The current OpenSpore `DbpfContentStore` is deliberately a one-package exact lookup and bounded byte reader (`src/assets/ResourceStore.hpp:60-86`; `src/assets/Dbpf.cpp:36-110,209-240`). It establishes current clean-room behavior, not original multi-package priority, cache lifetime, or write integration.

### 1.2 Noun identity: category identity, not object identity

The noun path has two related but non-identical identities:

- a semantic noun ID, passed as `uint32 nounID` to `0x00b21340`;
- a live `cGameData*`, whose `GetNounID` virtual slot is `+0x20`.

`0x00b21340` is the actual `cGameNounManager::GetData` implementation. Its `cGameNounManager+0x98` map is keyed by `uint32` noun ID, and it filters the manager’s `mNouns` list by calling the object’s noun-ID virtual method. The direct call path is:

```text
0x00b3d300 or 0x00b3d400
  -> cGameNounManager* receiver
  -> 0x00b21340
  -> 0x00e5c780 unsigned lower_bound on +0x98
  -> filter callback
  -> cGameData::GetNounID vtable +0x20
  -> add callback
```

The noun ID is unique only within the noun/category domain. It is not a unique instance ID. Multiple live objects can have the same noun ID, and one object can be found through different political, owner, empire, or context paths.

The `cGameData` layout separates additional identity fields:

```text
+0x08 mnRefCount
+0x0c/+0x10 intrusive list links
+0x24 mID
+0x28 mDefinitionID
+0x2c mpGameDataOwner
+0x30 mPoliticalID
```

`mID` and `mDefinitionID` must not be silently substituted for `GetNounID`. The noun manager’s `mNouns` list at `+0x78` owns intrusive list membership, while `mNounMap` at `+0x98` stores a per-noun projection of the list. The projection is a cache, not the object identity.

### 1.3 Star identity: live star noun versus star record

The Ghidra layouts expose two different objects:

```text
cStar, size 0x50
  derives from cGameData
  +0x30 mPoliticalID
  +0x40 mpSolarSystem
  +0x48 mpStarRecord
  +0x4c mKey                         StarID/domain key

cStarRecord, size 0xb0
  derives from ISimulatorSerializable and DefaultRefCounted
  +0x70 mKey                         StarID/domain key
  +0x74..+0x80 generated-location/state fields
  +0x80 mpSpeciesProfile
  +0x84 mPlanets
```

A `cStar` is a live noun/game-data object. A `cStarRecord` is a separate refcounted, serializable record containing saved star/planet state. `mpStarRecord` and `mKey` provide a likely association, but physical representation, pointer equality, and one-to-one logical cardinality are not proven. The architecture blockers explicitly retain “live noun objects, persistent star records, live planets, and empire records” as separate identities (`docs/analysis/architecture-blockers.md:46-75`).

The star key must also be separated from:

- `cEmpire::mPoliticalID` at `+0x84`, which is the empire registry key;
- `cStarManager::mNextPoliticalID` at `+0x1d4`, which is an ID allocator;
- `ResourceKey` fields such as `cStarRecord::mCitizenSpeciesKey` and `cEmpire::mUFOKey`, which identify packaged content;
- `SpacePlayerData+0x18`, which is the current political/player selection ID and not a star ID.

The constructor at `0x00bba2a0` initializes/derives star-record generation state and can query the star manager/planet model, but it does not establish that a live `cStar*` and a `cStarRecord*` are the same logical object or are always one-to-one.

### 1.4 Game-object identity and reference lifetime

Live game objects are polymorphic, refcounted values. The `cGameData` type begins with a game-data vtable followed by a `DefaultRefCounted` vtable and `mnRefCount`. The common lifetime slots are:

```text
vtable +0x00  AddRef
vtable +0x04  Release
vtable +0x08  destructor / object lifetime operation
```

The same pattern is visible in `cEmpire`, `cStarRecord`, and other `ISimulatorSerializable`/refcounted types. The raw object address is the live object identity. The reference count is lifetime bookkeeping, not identity. Two handles to the same address can be equal while the object has multiple owning references; a recycled address can later identify a different object.

`0x00b1fdb0` returns the raw pointer stored at `cGameNounManager+0x54` and performs no AddRef, Release, allocation, or locking. `0x00b1fd50` shows the ownership replacement pattern: AddRef/store the new avatar when non-null, store it, then Release the old avatar. Therefore the avatar accessor is a borrowed pointer view, while the manager’s intrusive field is the owner reference. Consumers that retain the returned pointer past replacement or manager teardown need a separate lifetime guarantee that is not established by this accessor.

### 1.5 Pointer identity

Pointer identity is a process-local address. It is useful for equality, null checks, intrusive-list membership, and virtual dispatch, but it is not stable across a process restart, save/load, pool reuse, allocator change, or host implementation.

Static evidence specifically supports these pointer-valued surfaces:

- `0x00b3d300` returns `DAT_0167eae0` and `0x00b3d400` returns `DAT_0167eb60` as raw noun-manager pointers;
- `0x00b3d2a0` returns `DAT_0167eae4` and `0x00b3d3a0` returns `DAT_0167eb0c` as raw star-manager pointers;
- `0x00b1fdb0` returns a raw avatar/creature pointer;
- `0x00b21340` returns a pointer to a manager-owned noun vector record;
- `0x00ba9370` returns a raw empire pointer from a map payload;
- `0x01021300` returns a borrowed current-player empire pointer while separately maintaining an owned cache reference.

The root slots are physically distinct four-byte words. Ghidra xrefs show one direct read for each canonical root and no direct writer:

```text
DAT_0167eae0 <- 0x00b3d300
DAT_0167eb60 <- 0x00b3d400
DAT_0167eae4 <- 0x00b3d2a0 and 0x00b3d2c0
DAT_0167eb0c <- 0x00b3d3a0
```

The four words are `undefined4` globals in the current Ghidra program, with one or two xrefs and no direct publication writer. This rejects physical aliasing but does not prove value inequality, null liveness, phase rebinding, or opaque/external publication. The root-closure reports correctly retain that distinction (`knowledgegraph/research/root-closure/track-d-noun-registry.md:25,182-193`; `knowledgegraph/research/root-closure/track-02-star.md:51-80`).

### 1.6 Handle identity

A handle is best modeled as a runtime reference or wrapper, not as a durable ID. There are two distinct forms in the evidence:

1. **Owning handle/reference:** an `intrusive_ptr<T>` or equivalent wrapper contributes a reference to the pointee. The pointer bit is raw, but the surrounding storage contract owns a lifetime share.
2. **Borrowed handle:** a raw pointer or pointer-like value returned from an accessor. It is valid only while the owner’s object remains alive and the owner has not invalidated the relationship.

Examples:

- `cGameNounManager+0x54` stores an intrusive avatar reference; `0x00b1fdb0` returns its raw address.
- `cGameNounManager::GetData` returns a raw pointer to a manager-owned vector record; the vector elements are intrusive references, but the record pointer itself is borrowed.
- `cCellDataReference_` is a cache handle, not merely a pointer. Its Ghidra layout is:

```text
+0x00 uint32 mInstanceID
+0x04 CellSerializer* mpSerializer
+0x08 intrusive_ptr<cCellResource> mpResource
+0x0c int mCounter
```

`0x00e82420` scans a global circular registry for the `(mInstanceID, mpSerializer)` pair and creates one entry on a miss. The identity of this handle is therefore a composite content/context key, not the `mInstanceID` alone and not the eventual `mpResource` address. `0x00e823a0` increments `mCounter`; `0x00e822c0` releases the loaded resource and can lazily resolve it again; `0x00e824d0` tears down the registry and its cached resources. This is a cache/lease mechanism whose use counter and resource lifetime are runtime state.

The original `Resource::IRecord`/database record lease is also handle-like: the resource manager and packed-file paths open records and couple close/release to reference bookkeeping. Exact record-handle ABI and eviction policy remain unresolved, so a replacement must not treat a record pointer as a durable ID.

### 1.7 Registry identity

A registry identity is `(owner, key domain, key)`, not merely a key value. The following registries are separate:

| Registry | Key | Payload | Owner/lifetime |
|---|---|---|---|
| Resource registry/cache | `ResourceKey` domain or manager-specific record identity | typed resource/record | `cResourceManager`/database/factory/cache; exact eviction unresolved |
| `cCellDataReference_` registry | `(instanceID, serializer)` | cached `cCellResource` and counter | Cell runtime registry at `DAT_016b44f0` |
| noun map | `uint32 nounID` | `tGameDataVectorT<cGameData>` record and intrusive vector elements | selected `cGameNounManager` |
| `cGameData::mID`/definition fields | game-data-specific IDs | live object fields | object, not a universal registry key |
| empire map | `cEmpire::mPoliticalID` | `intrusive_ptr<cEmpire>` | selected `cStarManager` |
| star/home-star maps and vectors | `StarID` or manager-specific domain | `intrusive_ptr<cStarRecord>` | selected `cStarManager` and related owners |
| current-player cache | requested political ID plus cached empire pointer | one `cEmpire` reference | `SpacePlayerData+0x1c` |
| manager root slots | no recovered key; raw pointer | manager/service pointer | publication substrate; owners unresolved |

The noun map and empire map are not a single registry merely because both use ordered maps. Their key domains, owner fields, payloads, and invalidation paths differ.

## 2. Allocation, storage, release, and invalidation

### 2.1 Resource and Cell-content handles

#### Resource manager boundary

`Resource::cResourceManager::Initialize` at `0x008de530` constructs manager lookup storage through the manager’s allocator. The live resource path at `0x008df460` first probes the manager’s cache/lookup state, then falls through to factory/database operations; it uses a lock around the cache/resource transaction and releases a temporary result on failure. The packed-file path at `0x008da3d0` validates flags/index integrity, resolves a record through virtual database/factory operations, and calls the record’s release vtable when the requested result is not retained.

This supports a layered model:

```text
ResourceKey
  -> resource-manager lookup/cache
  -> database/factory record
  -> typed resource object
  -> runtime consumer
```

It does not close original multi-package precedence, cache eviction, async request lifetime, or exact replacement order. The gameplay state-machine report and serialization model retain these as open (`docs/analysis/gameplay-state-machines.md:378-393`; `docs/analysis/serialization-model.md:74-129`).

#### Cell content cache handle

`0x00e82490` allocates the circular registry head. `0x00e82420` creates a `cCellDataReference_` entry keyed by both `instanceID` and serializer context. `0x00e823a0` increments its use counter and lazily resolves the resource when `mpResource` is null. `0x00e822c0` clears and releases the cached resource before attempting resolution again. `0x00e82280` clears all cached resource pointers without removing every reference node; `0x00e824d0` then releases the reference objects and frees the registry head.

The resulting ownership chain is:

```text
DAT_016b44f0
  -> cCellDataReference_ node
       -> intrusive_ptr<cCellResource>
            -> cCellResource
                 +0x08 ResourceKey mNameKey
                 +0x10 decoded data pointer/size
```

`cCellDataReference_` is therefore cache-only runtime linkage. It is not a save record. Current OpenSpore’s `CellDataReference` is only a lightweight `uint32` world ID (`src/sim/CellGame.hpp:49-53`), while its `CellContentLoader` owns returned decoded value objects after an exact key lookup (`src/assets/CellContent.cpp:253-388`). That is a clean-room comparison, not evidence that the original save format stores the handle.

### 2.2 Noun objects and noun-vector records

#### Creation and manager ownership

`0x00b20c60` is the strong creation surface. It:

1. calls the noun/factory path with a type token;
2. obtains a newly allocated live `cGameData`-derived object;
3. uses its AddRef virtual slot while installing intrusive-list nodes;
4. links the object into the manager’s `mObjects`/`mNouns`-related storage;
5. assigns runtime fields such as the definition or owner linkage;
6. calls `0x00b201a0` to invalidate affected noun projections.

`0x00b201a0` obtains the object’s noun ID, performs a lower-bound search over the noun map, and marks the selected vector record’s `needsUpdate` byte. It also scans other noun-map records and marks records dirty when the subtype/cast test requires it. Because it uses the same lower-bound helper as `0x00b21340`, “invalidate the requested noun” must not be promoted to exact-key invalidation without a membership check.

#### Noun-vector cache ownership

The Ghidra layout is:

```text
tGameDataVectorT<cGameData>, size 0x18
+0x00 bool needsUpdate
+0x04 intrusive_ptr<cGameData>* begin
+0x08 intrusive_ptr<cGameData>* end
+0x0c intrusive_ptr<cGameData>* capacity
+0x10 int garbage
+0x14 allocator
```

`0x00b21340` allocates/uses this record through four callbacks:

- create: `0x00b21080`, allocating a `0x18` record and setting `needsUpdate=1`;
- clear: `0x00d3d420`, releasing each non-null vector element through vtable `+0x04`, then moving `end` back to `begin`;
- add: `0x00b236c0`, AddRefing a successfully cast object, appending it, and releasing the temporary reference;
- filter: `0x00b1e500`, calling `GetNounID` at vtable `+0x20` and comparing it with the requested noun ID.

The `0x00ba8420`/`0x00ba83a0` path allocates a `0x18` ordered-map node, copies the noun key and vector value, links/rebalances the node, and increments the map count. The node is registry storage. The vector elements are separate intrusive references. The create callback and map-node allocation are both visible but their dataflow relationship is not closed; the map node and vector record must not be collapsed into one allocation claim.

`0x00b21410` demonstrates destruction of a noun-map record: it reads the object’s political identity, lower-bound searches the noun map, verifies the node payload is the target pointer, then calls `0x01045590`. That helper decrements the map count, unlinks the node, releases the payload through the payload’s release vtable, frees the node, and returns the successor. It then clears the owner field at `+0x70` when it matches.

#### Invalidation and destruction

`0x00b225d0` is a staged object/teardown surface: it marks an object field, uses AddRef/store/release while placing/removing the object from a manager vector, calls `0x00b20d30` for subtype-specific cleanup, and calls `0x00b201a0` to dirty noun projections. `0x00b22650` and `0x00b227c0` scan the manager noun list, select by vtable/type predicate, remove matching objects, and release them. `0x00b22440` releases manager-owned maps, lists, and service-like fields during manager cleanup.

What is not closed:

- whether a noun-map erase and a noun-list removal are one transaction;
- whether every `mObjects` owner releases before `mNouns` invalidation;
- whether `needsUpdate` is always cleared after partial or failed materialization;
- allocator failure and exception behavior;
- global noun-root unpublication and manager lifetime.

The noun manager getter at `0x00b3d400` returns a raw global pointer. The alternate getter at `0x00b3d300` returns a different global word. The two words are not physically aliased, but the binary does not establish a publisher, equality relation, or phase rebind contract.

### 2.3 Star manager, empires, and current-player cache

#### Manager and empire allocation

`0x00b60d80` allocates a `cStarManager`-sized object; `0x00bae490` constructs manager fields including the empire map at `+0x150`, relationship state at `+0x204`, and several star-record vectors/maps. The constructor is manager construction, not a direct write to either global star root.

`0x00baf0b0` is the empire creation/upsert path:

1. allocate `0x158` bytes for `cEmpire`;
2. construct it through `0x00c34830`;
3. write the requested political ID to `cEmpire+0x84`;
4. find/upsert the empire map node;
5. AddRef the new empire;
6. store the new pointer in the map payload;
7. Release the old equal-key payload.

The map therefore owns an intrusive reference to each empire. A returned empire from map lookup is borrowed; the map payload owns one reference.

#### Empire lookup and erase

`0x00ba9370` calls `0x00e5c780` and returns the first node payload whose key is at least the requested political ID. It checks only the map end sentinel, not exact key equality. The exact postcondition needed by a caller is:

```text
result != null && result->mPoliticalID(+0x84) == requested_id
```

A missing key with a greater successor can return the successor empire. The current-player cache path intentionally preserves that hazard.

`0x00bad7a0` reads the target empire’s political ID, lower-bound searches the same map, decrements the map count, unlinks the node, releases the payload, and frees the node. It does not compare the node key before removal. It is safe only under a current-membership invariant. The architecture blockers explicitly correct the earlier “matching erase” claim (`docs/analysis/architecture-blockers.md:46-63`).

#### Current-player cache

`SpacePlayerData` is allocated by `0x01021d40` as a `0x34` object. Its identity fields are separate from the empire pointer:

```text
+0x04 active planet
+0x08 active star
+0x10 SpaceContext
+0x18 requested current political/player ID
+0x1c cached cEmpire*
+0x20/+0x24 additional state
```

`0x01021300` first checks the requested ID. If the cached pointer is null or its `+0x84` political ID differs, it obtains the alternate star-manager pointer through `0x00b3d2a0`, performs the lower-bound lookup through `0x00ba9370`, AddRefs the new non-null result, stores it at `+0x1c`, and Releases the old value. The cache is therefore:

```text
request ID at +0x18
  -> lower-bound registry lookup
  -> one owned intrusive reference at +0x1c
```

It validates ID equality only on the hit path. The miss path can store a successor, and an erased empire can remain alive if the cache reference keeps it alive. The cache is not membership-validating and is not a general identity authority.

`0x01022460` is a separate teardown path: it clears the active planet/star references, clears and Releases the cached empire at `+0x1c`, and resets the requested ID to `-1`. It does not prove that empire-map erase and cache invalidation are one operation. The safe model is separate map teardown and separate cache teardown.

#### Star records and persistent identity

`cStarRecord` is `ISimulatorSerializable` and `DefaultRefCounted`; it is a record owner/value candidate rather than a live noun pointer. `cStarManager` owns vectors of intrusive star-record references, including saved, starter, and home-star collections. `cStar` is a live game-data object with `mpStarRecord` and `mpSolarSystem` links. The exact `cStar`/`cStarRecord` association cardinality and the order of star-record rehydration versus live star materialization remain unresolved.

The manager teardown at `0x00babe70` releases owned fields and passes map roots to `0x00d0c930`, which recursively releases payloads and frees map nodes. This is manager/map ownership cleanup, not proof of global star-slot unpublication.

### 2.4 Avatar and service handles

`0x00b1fdb0` is a raw pointer accessor to the field at `+0x54`, strongly identified as `cGameNounManager::mpAvatar`. `0x00b1fd50` is the reference-managed replacement operation. This is the clearest static example of the separation between pointer identity and ownership:

```text
raw address == current avatar identity in-process
intrusive field == owner-managed lifetime
accessor return == borrowed
replacement == AddRef(new), store, Release(old)
```

The manager-root publication words are not the same thing as the avatar field. A root may be null, stale, or rebound while the avatar field on a selected manager is still valid. No original runtime trace establishes the relative teardown order.

## 3. Mode transitions and save/load survival

### 3.1 Mode transitions

The App mode manager’s concrete helper at `0x007d85b0` establishes this order:

1. old mode `OnExit`;
2. write the new active index;
3. send mode-exit announcement;
4. new mode `OnEnter`;
5. send mode-enter announcement.

This is a lifecycle ordering observation, not a survival rule (`docs/analysis/gameplay-state-machines.md:81-120`; `docs/analysis/gameplay-transition-map.md:57-81`). The noun and star root publication paths are not in that direct order. Therefore:

- if a mode transition retains the same manager and only changes mode state, manager-owned noun/star maps may survive;
- if a transition publishes a new manager, old borrowed manager/object pointers and caches are not safe;
- if a transition only resets Cell presentation, noun/star state may remain in the Simulator substrate, but cross-mode handoff is not proven;
- the binary does not establish that `OnExit` saves any identity-bearing state.

Cell initialization at `0x00e80ba0` and rebuild at `0x00e7fd00` reset runtime Cell pools, world references, and serializable-state linkage. The current report synthesis does not establish that these bodies read the noun/star registries or save manager roots. Cell `OnExit`/`Dispose` release stage state; they do not prove an autosave (`docs/analysis/serialization-model.md:431-448`; `docs/analysis/gameplay-transition-map.md:83-107`).

### 3.2 Save/load surfaces

The relevant persistence layers are distinct:

```text
packaged ResourceKey
  -> database record / direct resource bytes
  -> typed content

PropertyList
  -> explicit local property stream

ISimulatorSerializable + ClassSerializer
  -> object/class attribute stream
  -> object identity/remapping layer unresolved

cGamePersistenceManager + header/load context
  -> mode/profile orchestration, exact order unresolved
```

`App::PropertyList::Write` at `0x006a1540` writes a count and local property entries through stream helpers. `App::PropertyList::Read` at `0x006a2f60` reads framing, may replace a parent, resizes local entries, and reads each property. The parent relationship, exact property carrier, version handling, and whole-save framing remain unresolved. The local property map is runtime/configuration state; only explicitly streamed entries are persistence candidates (`docs/analysis/serialization-model.md:130-182`).

`ISimulatorSerializable` exposes `Write`, `Read`, `WriteToXML`, and identity/noun-related slots. `ClassSerializer` provides ordered attribute descriptors and callbacks, but the concrete class registry, object-pointer table, duplicate handling, cycles, and restore order are not recovered. `cGameData`, `cEmpire`, `cStarRecord`, and other serializable types therefore have serialization eligibility, not a proven complete field map.

`cStarRecord` is a strong persistent-value candidate. `cEmpire` is a strong serializable political/state candidate. `cCellSerializableData` is a separate mode-specific candidate held by `cCellGame`; its fields are not equivalent to a direct Cell content record. The serialization model rejects the inference that every field in that structure survives save/load (`docs/analysis/serialization-model.md:222-249,335-364`).

The static save/load candidates show narrow but real database operations:

- `0x00b28ec0` reaches `0x00bb4ba0`, which writes a temporary star/planet database and replaces `stars.db` through a bounded replacement path.
- `0x00b294c0` reaches `0x00b28ec0` and then validation/check paths.
- `0x00b3d440` is only the borrowed `cGamePersistenceManager::Get` accessor for `DAT_0167eb34`; the Ghidra xref scan finds one direct read and no direct writer.

These paths do not prove that `cGameNounManager*`, `cStarManager*`, raw `cGameData*`, pool indices, `ResourceKey` wrappers, renderer handles, or cache pointers are serialized. A saved logical ID may be remapped to a new runtime object; the pointer remapping algorithm is unknown.

### 3.3 Survival matrix

| Identity/state | Mode transition | Save/load | Status |
|---|---|---|---|
| `ResourceKey` | Can be reused if content substrate remains available | Candidate content locator; exact serialized field order/conflicts remain open | `SUPPORTED` boundary, `UNKNOWN` wire order |
| DBPF/typed record bytes | Static content can be reloaded | Packaged content substrate, not profile state | `SUPPORTED` |
| `cCellDataReference_` | Runtime cache may be rebuilt or released | Not a save record | `SUPPORTED` cache-only classification |
| Noun ID | May be reused by rebuilt objects | Domain identity candidate, but exact serializer coverage unknown | `SUPPORTED` as domain axis, `UNKNOWN` save coverage |
| `cGameData*` | Invalid after object destruction/rebuild | Raw pointer not safe to persist; object remap unresolved | `SUPPORTED` anti-claim |
| Noun manager/list/map | Can survive only if selected manager survives | Registry is runtime, not established as saved data | `SUPPORTED` runtime-only, persistence unknown |
| `cStar*` | Live object can be replaced/rebuilt | Not a durable star record by itself | `SUPPORTED` separation |
| `cStarRecord*` | Refcounted record may outlive live star object | Strong serializable candidate; field/order coverage unknown | `SUPPORTED_AS_CANDIDATE` |
| `cEmpire*` | Manager/space state can be rebuilt or cached | Strong serializable candidate; pointer restoration unknown | `SUPPORTED_AS_CANDIDATE` |
| `SpacePlayerData+0x1c` empire cache | Rebuilt/cleared on teardown; not membership-aware | Runtime cache, not established as save field | `SUPPORTED` cache-only |
| `cCellGame` pool/object index | Rebuilt on Cell reset | Live pool state is not a save record | `SUPPORTED` transient |
| `cCellSerializableData` | Cell mode-specific candidate | Save coverage and handoff unknown | `SUPPORTED_AS_CANDIDATE` |
| Service/root pointer slots | Publication/rebind/teardown unknown | No direct save path established | `UNRESOLVED_ARCHITECTURE_BLOCKER` |

## 4. Competing hypotheses and adversarial evidence

| ID | Hypothesis | Prediction | Evidence and result |
|---|---|---|---|
| H1 | ResourceKey, noun ID, star ID, political ID, pointer, and handle are one global ID | Lookups, comparisons, persistence, and owner transitions would use one value | **Rejected.** Layouts, field offsets, and lookup paths are separate. |
| H2 | Noun ID uniquely identifies one live object | A noun lookup would return exactly one object and a second object could not share it | **Rejected as uniqueness claim.** Noun map projects a filtered list; many game-data objects can share category. |
| H3 | A noun map key is exact-find | Missing key should return null unless equal key exists | **Rejected.** `0x00e5c780` is lower-bound and `0x00b21340` checks only the end sentinel. |
| H4 | Noun vector elements are owned by the manager map node itself | A returned vector pointer would itself own the element objects | **Rejected.** The map node stores a vector record; intrusive elements are separate references released by clear/destruction paths. |
| H5 | The two noun global words are physically the same slot | A direct alias store/equality or same address should be present | **Rejected for physical aliasing.** Distinct four-byte words and only direct reads. Runtime value aliasing/publication remains unresolved. |
| H6 | The two star global words are physically the same slot | Same prediction as H5 | **Rejected for physical aliasing.** Distinct words; value equality/publication unresolved. |
| H7 | Empire lookup is exact political-ID find | Exact requests should never return a greater ID | **Rejected.** `0x00ba9370` is ceiling/lower-bound. |
| H8 | Current-player cache invalidates the empire map | Empire erase would clear `SpacePlayerData+0x1c` in the same path | **Rejected as a unified model.** Map erase and cache teardown are separate bodies. |
| H9 | Star record and live star are one object | Same address, same refcount, and direct one-to-one pointer would be observed | **Rejected as identity claim.** Separate types/fields; association exists, cardinality/order unresolved. |
| H10 | Raw object pointers are durable save identity | Save/load would write/rebind host addresses directly | **Unsupported and unsafe.** Serializer has object-pointer operations, but exact durable encoding/remapping is unknown. |
| H11 | Service roots survive all mode transitions | Slot values remain stable and manager maps are not torn down | **Unresolved.** Direct mode ordering is known; noun/star root publication/teardown is not joined to it. |
| H12 | Cell mode exit autosaves noun/star state | Direct Cell exit/dispose would reach a save/load candidate | **Not supported by direct bodies.** Higher-level autosave remains unexcluded. |
| H13 | `cCellDataReference_` is a durable content handle | It would be serialized or survive registry teardown | **Rejected as save identity.** It owns a runtime cache and use counter; teardown releases cached resources. |
| H14 | Registry erase invalidates every pointer to the payload | All raw consumers would fail after map erase | **Rejected.** A separate cache/refcount can keep an object alive; borrowed pointers may be stale but storage need not immediately disappear. |
| H15 | `cStarManager` is the sole owner of all star identity | Every live star, record, and root pointer resolves through one manager | **Rejected/overstated.** Star manager owns much Space state, but live noun manager, SpacePlayerData, and global root publication remain separate. |
| H16 | A cache hit proves registry membership | Cached object must still be in the current manager map | **Rejected for empire cache.** Hit checks only `cEmpire+0x84`; map membership is not revalidated. |

The most important missing separators are runtime publication/equality traces for the four root words, an allocation-to-slot-to-field trace for noun/star managers, exact noun/star erase membership checks, and one save/load round trip that records logical ID remapping and cache invalidation. Static architecture blockers require keeping these questions open rather than selecting the most convenient singleton model (`docs/analysis/architecture-blockers.md:65-89`; `docs/analysis/simulator-root-closure.md:20-29`).

## 5. Minimal semantic ownership model

This is the smallest model compatible with the evidence and safe under the unresolved hypotheses:

```text
ContentKey
  ResourceKey = (typeID, groupID, instanceID)
  owns/selects: packaged record bytes and typed content
  does not own: live noun/star/player object identity

DomainIdentity
  NounID, StarID, PoliticalID, and subtype/object IDs
  domain-separated uint32/logical values
  never globally interchangeable

LiveObject
  cGameData / cCreature / cStar / cEmpire / cStarRecord*
  identity = process-local address + virtual type
  lifetime = AddRef/Release or owning intrusive field
  pointer values are borrowed unless the caller obtains a reference

RegistryRecord
  owner = selected noun/star/resource registry
  key = owner-specific key domain
  payload = owning intrusive reference, vector, or resource record
  erase = unlink + release registry-owned reference + free registry node

RuntimeHandle
  raw pointer, intrusive_ptr wrapper, record lease, or cache handle
  validity is bounded by owner lifetime and explicit release policy
  handles are not saved unless an independent serializer proves a mapping

ModeRootPort
  noun manager root(s) and star manager root(s)
  identity = selected manager address, not a durable domain ID
  publication/rebind/unpublication are explicit lifecycle events
  alternate and canonical ports remain separate until runtime equality is observed
```

Required ownership invariants for a compatible OpenSpore design are:

1. Keep ResourceKey, noun ID, star ID, political ID, object pointer, handle, and registry key as distinct types or explicitly domain-tagged values.
2. A borrowed pointer must not be retained across owner teardown without a new owner guarantee.
3. A map key is not sufficient to prove exact membership; add an explicit postcondition when exact lookup is required.
4. Registry erase and dependent cache invalidation must be separate operations until runtime evidence joins them.
5. A live noun/star object must not be serialized by address. Save logical fields and reconstruct/rebind objects through a separate restoration policy.
6. Root manager ports must support publication, replacement, and unpublication events; do not merge alternate and canonical noun/star slots merely because their layouts are compatible.
7. Resource/cache/GFX/presentation handles remain runtime linkage unless an explicit codec and round-trip oracle establish persistence.

## 6. Confidence and runtime necessity

| Claim | Confidence | Reason |
|---|---|---|
| Complete `ResourceKey` selects packaged content | High | Ghidra layout, resource-manager/database paths, DBPF/current implementation agreement |
| Noun ID is a category/domain key, not a pointer | High | `GetNounID` vtable use, noun map structure, callback path |
| `cGameData*` is live refcounted game-object identity | High | `cGameData` layout, intrusive vtables, AddRef/Release paths |
| `cStar*` and `cStarRecord*` are distinct representations | High | Separate Ghidra types and fields |
| Empire map owns intrusive empire references | High | `0x00baf0b0`, `0x00bad7a0`, `0x00d0c930` |
| Current-player cache owns one intrusive reference | High | `0x01021300` and `0x01022460` |
| Noun map/cache invalidation is dirty/lower-bound based | High mechanics, medium exact membership | `0x00b201a0`, `0x00b21340`, `0x00e5c780` |
| Raw manager/avatar/vector accessors are borrowed | High | Accessor bodies perform no AddRef/Release |
| Four root words are physically distinct | High | Direct global xrefs and storage layout |
| Four root values are equal, phase-rebound, or distinct | Unresolved | No publication/equality/teardown join |
| `ResourceKey` survives save/load in original wire order | Low/unknown | Serialized operation exists; exact field order and framing unresolved |
| `cStarRecord`/`cEmpire` are save candidates | Medium-high | Explicit `ISimulatorSerializable` and field layouts; field coverage/order incomplete |
| `cGameData*`, pool indices, cache handles, and root pointers survive save/load | Low/unsafe | No direct durable pointer encoding; remapping unresolved |
| Noun/star state survives a mode transition | Unresolved | Mode exit/enter order is known; root publication and handoff are not |
| Any mode transition autosaves | Unsupported | Direct teardown bodies do not establish save |

A runtime trace is not necessary to choose the minimum safe semantic model above. It is necessary before making original-compatibility claims about root publication, exact object remapping, survivor sets, manager rebind order, or save/load transaction behavior. The next highest-value runtime experiment would capture synchronized values of the four root words, selected manager vtables, noun/star map sizes, current-player cache pointer/ID, and one object allocation/release epoch across a mode transition and one save/load cycle. Until that exists, the report intentionally leaves the four root publication states, two root unpublication states, and noun/star value-equality relation unresolved.

## Primary evidence references

- Ghidra `SporeApp.exe`: `0x00b3d300`, `0x00b3d400`, `0x00b3d2a0`, `0x00b3d3a0`, `0x00b3d440`; global xrefs at `0x0167eae0`, `0x0167eb60`, `0x0167eae4`, `0x0167eb0c`, `0x0167eb34`.
- Noun: `0x00b21340`, `0x00ba8420`, `0x00ba83a0`, `0x00b21410`, `0x01045590`, `0x00b20c60`, `0x00b201a0`, `0x00b225d0`, `0x00b20d30`, `0x00b22650`, `0x00b227c0`, `0x00b22440`; layouts `cGameNounManager`, `cGameData`, `tGameDataVectorT<Simulator::cGameData>`.
- Star/current player: `0x00b60d80`, `0x00bae490`, `0x00baf0b0`, `0x00ba9370`, `0x00bad7a0`, `0x01021300`, `0x01022460`, `0x00babe70`, `0x00d0c930`, `0x00bba2a0`; layouts `cStarManager`, `cStar`, `cStarRecord`, `cEmpire`, `SpacePlayerData`.
- Resource/cell cache: `0x008de530`, `0x008df460`, `0x008da3d0`, `0x00e82420`, `0x00e823a0`, `0x00e822c0`, `0x00e824d0`, `0x00e82280`, `0x00e4cde0`, `0x00e4ace0`; layouts `cCellDataReference_`, `cCellResource`, `ResourceKey`.
- Serialization/mode: `0x006a1540`, `0x006a2f60`, `0x00692900`, `0x00693e10`, `0x00b28ec0`, `0x00b294c0`, `0x00bb4ba0`, `0x007d85b0`, `0x00e80ba0`, `0x00e7fd00`, `0x00e7fc00`, `0x00e81f30`.
- KG/docs: `knowledgegraph/research/root-closure/track-d-noun-registry.md`, `track-02-star.md`, `track-a-service-identity.md`, `track-c-opaque-owner.md`, `followup-noun-boundary.md`; `docs/analysis/serialization-model.md`, `docs/analysis/semantic-blueprint.md`, `docs/analysis/gameplay-data-model.md`, `docs/analysis/gameplay-state-machines.md`, `docs/analysis/gameplay-transition-map.md`, `docs/analysis/simulator-root-closure.md`, and `docs/analysis/architecture-blockers.md`.
- Current OpenSpore comparison: `src/assets/ResourceKey.hpp`, `src/assets/ResourceStore.hpp`, `src/assets/Dbpf.cpp`, `src/assets/CellContent.cpp`, `src/assets/PropertyStore.hpp`, `src/sim/CellPool.hpp`, `src/sim/CellGame.hpp`.
