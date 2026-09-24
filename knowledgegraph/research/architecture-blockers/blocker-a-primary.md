# Blocker A Primary Investigation — Noun/star publication lifecycle

**Status:** `OPEN_ARCHITECTURE_BLOCKER_CLUSTER_A`
**Binary:** `SporeApp.exe` 3.1.0.22, `x86:LE:32`, image base `0x00400000`
**Investigation mode:** static/read-only; no Wine run; no Ghidra mutation; no source, `SPORE/`, or canonical SQLite mutation

## Executive conclusion

Blocker A is not resolved. The binary proves four distinct root storage words and proves a rich noun/star object lifecycle below those words, but it does not prove the publisher, equality relation, phase identity, liveness, or teardown order for the roots.

The safe implementation boundary is therefore four separate opaque ports with explicit `publish`, `replace`, `invalidate`, and `unpublish` operations. Noun/star mechanics can proceed as owner-qualified clean-room behavior, provided the implementation does not merge the two noun roots, merge the two star roots, assume singleton equality, serialize raw root pointers, or treat lower-bound lookup as exact-find.

Implementation can proceed for a bounded clean-room replacement. Implementation cannot proceed as an original-compatible root/liveness/persistence adapter until the smallest runtime lifecycle observation below is obtained or an equivalent static publisher trace is recovered.

## Prior conclusions retained

The existing architecture work already identifies the blocker as publication, equality, and teardown rather than the lower-level map mechanics. `docs/analysis/architecture-resolution.md:29-65` rejects physical aliasing of the noun words, confirms the noun receiver is not a generic context, and records that noun lookup is lower-bound/successor-tolerant. `docs/analysis/architecture-resolution.md:67-92` records the star root pair, empire lower-bound lookup, lazy successor-tolerant cache, and independent map/cache invalidation. The final architecture decision keeps four separate opaque ports and makes root equality/publication an architecture-changing blocker (`docs/analysis/architecture-decisions.md:29-51`).

The semantic freeze likewise marks the shared-state roots as an unresolved service-publication boundary, keeps noun/empire lookup mechanics separate from lifecycle, and states that no original runtime validation exists (`docs/analysis/semantic-blueprint.md:183-215`; `docs/analysis/semantic-blueprint.md:943-969`). The serialization model treats `cGameNounManager` as a live registry/materialization owner rather than a persistence format, and treats `cStarManager`/`cStarRecord`/star databases as separate runtime and persistence layers (`docs/analysis/serialization-model.md:31-72`; `docs/analysis/serialization-model.md:335-363`).

## Evidence inventory and limits

### Binary evidence collected

Ghidra was queried against the open `SporeApp.exe` program. The important direct bodies and disassembly were:

- root accessors `0x00b3d300`, `0x00b3d2a0`, `0x00b3d400`, `0x00b3d3a0`;
- noun materialization `0x00b21340` and its `0x00e5c780` / `0x00ba8420` helpers;
- noun construction/invalidation/destruction `0x00b20c60`, `0x00b201a0`, `0x00b225d0`, `0x00b20d30`, `0x00b22650`, `0x00b227c0`, `0x00b232b0`, `0x00b22440`;
- star empire lookup/cache `0x00ba9370`, `0x01021300`, `0x00bad7a0`, `0x01022460`;
- star record generation/database paths `0x00bb4af0`, `0x00bb4100`, `0x00bb4ba0`, `0x00bb8b20`, `0x00bb5b50`.

Ghidra’s current function boundaries are not all identical to the SDK anchor addresses. For example, the SDK XML places `cGameNounManager::GetData` at `0x00b212d0`, while the requested body `0x00b21340` is a separately analyzed function with the same callback/map mechanics. The prior interface report explicitly preserves that address identity as unresolved (`docs/analysis/simulator-shared-state-interface.md:126-141`). This report therefore cites the requested body and does not promote the SDK anchor into a stronger claim.

### Local semantic and architecture reports read

- `docs/analysis/semantic-blueprint.md`
- `docs/analysis/architecture-resolution.md`
- `docs/analysis/serialization-model.md`
- `docs/analysis/architecture-decisions.md`
- `docs/analysis/simulator-shared-state-interface.md`
- `docs/analysis/gameplay-data-model.md`
- `docs/analysis/future-research/01-architecture-blocker-1.md`
- `docs/analysis/future-research/01-pkg-01-shared-state-roots.md`
- `docs/analysis/future-research/06-pkg-12-sim-space.md`
- `docs/analysis/future-research/11-pkg-20-gameglobal.md`
- `docs/analysis/unknown-high-resolution.md`

The prior blocker brief asks specifically for publisher/replacement/equality/unpublication paths, mode-transition snapshots, star rebind/owner traces, and independent cache behavior (`docs/analysis/future-research/01-architecture-blocker-1.md:16-38`).

### Local SDK/modding evidence read

The local Spore-ModAPI headers and XML are corroborating API vocabulary and clean-room type evidence, not original runtime proof:

- `GameNounManager.h:62-86` documents the manager, `CreateInstance`, and `DestroyInstance`; `GameNounManager.h:96-114` defines the four callback shapes and noun ID for `GetData`; `GameNounManager.h:130-152` gives the `mNouns`, `mNounMap`, `mObjects`, and intrusive-pointer fields.
- `GameNounManager.cpp:23-48` binds the SDK methods and exposes the current-player helpers.
- `StarManager.h:102-155` documents the star-manager ownership model; `StarManager.h:270-331` gives star grids, saved/starter records, empire map, relationship manager, and database fields.
- `SpacePlayerData.h:42-61` documents the active planet/star, context, player empire ID, and cached empire pointer.
- `cGameData.h:34-91` documents the refcounted, intrusive-list, owner/political-ID game-data prefix.
- `cStar.h:29-60` shows that live `cStar` is a `cGameData` noun and holds a `cStarRecordPtr` at `+0x48`.
- `cStarRecord.h:51-115` shows that `cStarRecord` is a separate serializable/refcounted record with version/time/position/ownership/planet fields.
- `ISimulatorSerializable.h:30-43` documents the noun/serialization interface, including `GetNounID`.
- `NounClassFactories.h:11-39` documents the noun factory map and `RegisterNounType`; the SDK XML maps that registration anchor to `0x00b23e40` (`SporeGhidra_march2017.xml:52985-52986`).
- The SDK singleton wording is contradicted at the binary boundary by the four distinct words; it is not used as equality evidence.

## Root storage and publisher findings

### Accessor bodies

| Accessor | Direct body | Global word | Direct caller count / xref result | Static result |
|---|---|---:|---|---|
| `FUN_00b3d300` | `MOV EAX,[0x0167eae0]; RET` | `DAT_0167eae0` | 1,097 callers reported by Ghidra; global xref is the accessor read | Raw noun-port candidate |
| `Simulator::cGameNounManager::Get` at `0x00b3d400` | `MOV EAX,[0x0167eb60]; RET` | `DAT_0167eb60` | 43 direct callers reported by Ghidra; global xref is the accessor read | Separate canonical noun-port candidate |
| `FUN_00b3d2a0` | `MOV EAX,[0x0167eae4]; RET` | `DAT_0167eae4` | 314 callers; direct global xrefs at `0x00b3d2a0` and `0x00b3d2f0` | Raw star-port candidate |
| `Simulator::cStarManager::Get` at `0x00b3d3a0` | `MOV EAX,[0x0167eb0c]; RET` | `DAT_0167eb0c` | raw code xref at `0x00b5ca50`; Ghidra did not resolve that site as a named function | Separate canonical star-port candidate |

The four globals are four distinct four-byte words. Ghidra’s raw memory reads at `0x0167eac0` and `0x0167eb00` show image-time zero bytes in these regions; that is an image-layout observation, not a runtime liveness result. Ghidra audits each word as an `undefined4` with one or two xrefs and no documentation.

Exact byte-pattern searches found the root addresses only in these accessor/read sites:

- `E0 EA 67 01` at `0x00b3d301`;
- `60 EB 67 01` at `0x00b3d401`;
- `E4 EA 67 01` at `0x00b3d2a1` and `0x00b3d2f2`;
- `0C EB 67 01` at `0x00b3d3a1`.

No concrete direct store, clear, equality operation, or teardown store was recovered for any of the four words. This is a bounded negative: computed, bulk, relocation, external, loader, or opaque publication remains possible. The prior architecture report reaches the same bounded-negative conclusion (`docs/analysis/architecture-resolution.md:45-59`).

### Publisher matrix

| Event | `DAT_0167eae0` | `DAT_0167eb60` | `DAT_0167eae4` | `DAT_0167eb0c` | Confidence |
|---|---|---|---|---|---|
| Image-time value | zero in raw image | zero in raw image | zero in raw image | zero in raw image | Observed image bytes only |
| Direct publisher | none found | none found | none found | none found | Bounded negative |
| Direct reader | `0x00b3d300` | `0x00b3d400` | `0x00b3d2a0`, `0x00b3d2c0` | `0x00b3d3a0` | Confirmed static mechanics |
| Physical alias | rejected | rejected | rejected | rejected | Confirmed static layout |
| Value equality | unknown | unknown | unknown | unknown | Unresolved blocker |
| Replace/rebind path | unknown | unknown | unknown | unknown | Unresolved blocker |
| Unpublish/teardown path | unknown | unknown | unknown | unknown | Unresolved blocker |

The high fan-in asymmetry is evidence of use, not ownership: the alternate noun accessor has 1,097 reported direct callers versus 43 for the SDK-labeled canonical accessor, and the alternate star accessor has 314 callers while the canonical star accessor has a sparse unresolved code xref. This can indicate active operational versus compatibility/legacy access, but it does not establish that either word is stale or that the values are equal. The prior interface report records the same fan-in counts and rejects fan-in as an ownership proof (`docs/analysis/simulator-shared-state-interface.md:36-64`; `docs/analysis/simulator-shared-state-interface.md:226-251`).

## Noun publication, storage, lookup, and materialization

### Type and storage boundary

Ghidra’s `cGameNounManager` type is 284 bytes (`0x11c`) and its recovered layout agrees with the SDK fields used by the binary:

- `mNouns` intrusive list at `+0x78`;
- `mNounMap` at `+0x98`, an EASTL map keyed by `uint32_t` and valued by `tGameDataVectorT<cGameData>`;
- `mObjects` list at `+0x10c`;
- `mpAvatar` at `+0x54`, `mpPlayerTribe` at `+0x70`, and `mpPlayer` at `+0x74`.

The map container is 28 bytes: comparator at `+0`, tree anchor at `+0x4`, size at `+0x14`, and allocator at `+0x18`. The loaded `tGameDataVectorT<cGameData>` is 24 bytes in Ghidra: `needsUpdate` at `+0`, vector begin/end/capacity at `+0x4/+0x8/+0xc`, and allocator/garbage state afterward. The SDK gives the same high-level `needsUpdate` plus intrusive-pointer vector contract (`GameNounManager.h:130-152`; `tGameDataVectorT.h:30-43`, `tGameDataVectorT.h:77-87`).

The noun manager is a multi-inheritance object. Ghidra’s layout begins with an `IMessageListener` vtable pointer, a Simulator strategy vtable pointer, an `IVirtual` vtable pointer, refcount/mode fields, then the noun and cache fields. The constructor body `FUN_00b232b0` writes the vtable pointers and initializes the intrusive-list/map anchors and the `mObjects` list. The vtable is referenced by `0x00b22440` and `0x00b232b0`; no RTTI-backed universal noun hierarchy was recovered.

### Construction/materialization

The SDK anchor `CreateInstance` is `0x00b20bf0`, but Ghidra resolves the containing analyzed body as `FUN_00b20c60` beginning at `0x00b20c60`. The body has the expected noun factory shape:

1. obtains the class/factory service through `FUN_00920090`;
2. calls the factory virtual at `+0x20` with the requested noun ID and base type `0x17f243b`;
3. if creation succeeds, allocates a 12-byte intrusive-list node and links it into manager `+0x10c` (`mObjects`);
4. increments the global object counter and writes the resulting identifier to the created object at `+0x24`;
5. writes the object’s intrusive-list links using manager `+0x78` (`mNouns`);
6. invokes the object’s virtual/AddRef path and calls `FUN_00b201a0` to invalidate noun caches.

This is strong static evidence for manager-owned materialization into the live noun list. It is not evidence that a noun is a save record. The SDK explicitly says `cGameNounManager` creates/destroys Simulator objects and gets active instances by noun ID (`GameNounManager.h:62-86`), while the local data model keeps the noun/object family a semantic adapter boundary and not a universal original ABI (`docs/analysis/gameplay-data-model.md:252-267`).

### Lookup and callback materialization

The requested body `FUN_00b21340` uses the manager receiver at `+0x98` as the noun-ID map and `+0x9c` as its end sentinel. It calls `0x00e5c780`, which is an unsigned lower-bound helper. If the returned iterator is the end sentinel, it invokes the create callback and routes through `0x00ba8420`; otherwise it obtains the map payload at node `+0x14`. It then:

- checks the payload’s `needsUpdate` byte;
- clears the vector through the clear callback when dirty;
- walks the manager’s `mNouns` list at `+0x78`;
- calls the filter callback with the noun ID;
- calls the add callback for matching entries;
- clears `needsUpdate` after the rebuild.

The five callback arguments match the SDK’s `ContainerCreateCallback_t`, `ContainerClearCallback_t`, `ContainerAddCallback_t`, `ContainerFilterCallback_t`, and noun ID tuple (`GameNounManager.h:96-114`; XML `SporeGhidra_march2017.xml:23408-23415`). This supports a noun-data materialization/cache contract, not exact address identity and not an exact map-find contract. The prior report records the same bounded conclusion and preserves the “five callback pointers plus noun ID” correction (`docs/analysis/architecture-resolution.md:55-63`).

### Cache invalidation

`FUN_00b201a0` is the explicit invalidation bridge:

- gets the created/destroyed object’s noun ID through its virtual at `+0x20`;
- lower-bounds the manager’s `mNounMap`;
- sets the matching `tGameDataVectorT::needsUpdate` byte;
- walks the remaining noun-map vectors and marks entries for which the object’s type/cast test succeeds.

`FUN_00b20c60` calls it after creation. `FUN_00b225d0` calls it after destruction. This is a direct static invalidation path for the cached noun vectors. The prior shared-state report independently records the `needsUpdate +0x00`, begin/end/capacity layout and the noun-map/list materialization contract (`docs/analysis/simulator-shared-state-interface.md:126-141`, `docs/analysis/simulator-shared-state-interface.md:240-249`).

### Erase and destruction

The requested noun destroy surface is not a single static address because the SDK anchor `0x00b22560` falls inside a damaged/overlapping Ghidra function region. The coherent analyzed bodies are:

- `FUN_00b20d30`: unlinks an object from the noun/list structures, clears selected owner/player references, and performs the object teardown path;
- `FUN_00b225d0`: marks the object’s destruction state, places it in the manager’s `field_80` processing vector, releases the temporary reference, calls `FUN_00b20d30`, and invalidates noun caches;
- `FUN_00b21410`: lower-bounds a manager map at `+0xd0`, erases the matching object entry, and clears/releases `mpPlayerTribe` when the destroyed object is the current player tribe;
- `FUN_00b22650`: walks `mNouns`, filters by virtual noun ID, collects matches, destroys each, then releases the temporary collection;
- `FUN_00b227c0`: walks `mNouns`, filters by virtual cast/type, collects matches, destroys each, and releases the collection;
- `FUN_00b22440`: tears down manager vectors/maps/fields and restores base vtables.

This supports a staged destroy/invalidate/collection model, but it does not show a write to any root global. The owner/player-reference clearing is separate from root unpublication.

## Star publication, storage, lookup, and materialization

### Type and storage boundary

Ghidra’s `cStarManager` type is 556 bytes (`0x22c`). The recovered fields match the SDK layout:

- `mStarRecordGrid` at `+0xc8`;
- `mStarterStarRecords` at `+0xdc`;
- `mSavedGameStarRecords` at `+0xf0`;
- `mEmpireHomeStarRecords` at `+0x12c`;
- `mSol` at `+0x148`;
- `mpTempStar` at `+0x14c`;
- `mEmpires` at `+0x150`, with map end at `+0x154`;
- `mpRelationshipManager` at `+0x204`;
- temporary/main planet databases at `+0x224/+0x228`.

The SDK describes the manager as the owner of galaxy records, saved/starter records, empire homes, relationships, collectables, trade routes, and temporary/main databases (`StarManager.h:102-128`, `StarManager.h:270-331`). The local architecture model calls `cStarManager` runtime transient and `cStarRecord` a separate persistence candidate (`docs/analysis/gameplay-data-model.md:315-355`).

### Empire lookup and cache

`FUN_00ba9370` takes a star-manager receiver and a political ID. For ID `-1` it returns null. Otherwise it calls the generic lower-bound helper on the map beginning at receiver `+0x150`; if the returned iterator is the end sentinel at `+0x154`, it returns null, otherwise it returns the intrusive pointer payload at node `+0x14`.

This is `ceilingByPoliticalId`/successor-tolerant lookup, not exact find. A missing ID below a greater successor can return that successor unless a caller adds an identity postcondition. The local map report makes the same boundary decision (`docs/analysis/architecture-resolution.md:67-80`; `docs/analysis/simulator-shared-state-interface.md:188-201`).

`FUN_01021300` is the current-player empire cache:

1. read `Simulator__sSpacePlayerData+0x18` as the current empire ID;
2. return null for `-1`;
3. if the cached pointer at `+0x1c` is null or its `+0x84` political ID differs, call `FUN_00b3d2a0` and use its returned receiver in `FUN_00ba9370`;
4. store the returned intrusive pointer at `+0x1c`;
5. AddRef the new object and Release the old object;
6. return the cache.

The disassembly at `0x01021321-0x0102132d` shows the alternate star-root result is moved into `ECX` before the empire-map call. This proves the cache depends on the alternate star root in this path; it does not prove equality with `0x00b3d3a0`’s root.

The cache is not the empire map. `FUN_00bad7a0` releases a lower-bound-selected map payload and erases the map node, but it does not clear `SpacePlayerData+0x1c`. `FUN_01022460` independently clears the active planet, star, and empire cache, and resets the player ID. The local architecture synthesis explicitly rejects a single map/cache invalidation chain (`docs/analysis/architecture-resolution.md:73-80`).

### Star record materialization and aliasing

The noun and star domains are not one object registry:

- `cGameNounManager` materializes live `cGameData` objects and filters them by noun ID/type.
- `cStar` is a `cGameData` noun, but it contains `cStarRecordPtr mpStarRecord` at `+0x48` (`cStar.h:29-60`).
- `cStarRecord` is not a `cGameData`; it is a separate `ISimulatorSerializable`/refcounted record with `mPlanets` at `+0x84`, `mKey` at `+0x70`, and version/time/ownership/position fields (`cStarRecord.h:51-115`).
- `cStarManager` owns the record grid and record vectors, while `cGameNounManager` owns the live noun list/cache.

The named `cStarManager::RecordToPlanet` SDK anchor is `0x00bb5b50`; the recovered body is a wrapper whose visible path calls `FUN_00bb1560`, so the complete record-to-live-planet construction is not established in this investigation. `FUN_00baf820` does show a 0x10-byte record append path in the star-record generation neighborhood, but the exact domain-to-owner mapping is incomplete. The safe conclusion is an explicit association boundary: live star noun, persistent star record, live planet, and empire record are distinct identities with typed links where directly evidenced.

`FUN_00bb4af0` provides a concrete star-generation lifecycle: it checks the star record’s no-planet/timing state, updates the record time, removes the record from a pending list, resets the state, and calls `FUN_00bb4100` to generate planets. This is a runtime/record-generation path, not root publication.

## Serialization and persistence boundary

The noun manager is not a serialization owner. `cGameData` and selected subtypes expose `ISimulatorSerializable` methods, but the local serialization model requires explicit field emission or a write/read relationship before calling a field save-surviving (`docs/analysis/serialization-model.md:201-249`). The noun map/list/vector is runtime linkage and cache state; the registry is a reconstruction target on load, not the persistence format (`docs/analysis/serialization-model.md:335-363`).

The star record path is better bounded but still not a universal save transaction:

- `FUN_00bb4ba0` opens `stars.db.tmp`, writes star-manager record data through the serializer/database path, closes the temporary stream, and calls `FUN_006891f0(L"stars.db.tmp", L"stars.db")` for replacement.
- The same body sets serializer-side values from `cStarManager+0x204` and from `FUN_00b3d380`; these are serialized-field candidates, not proof that raw root pointers survive load.
- `FUN_00bb8b20` contains the corresponding database/ClassSerializer read-side machinery and populates star-manager state.
- The local model calls this a narrow temporary-database replacement, not general save atomicity or a universal `.spo/.prop` format (`docs/analysis/serialization-model.md:253-299`; `docs/analysis/gameplay-data-model.md:333-355`, `docs/analysis/gameplay-data-model.md:360-394`).

No root-global write was found in either serialization path. Root publication is therefore not proven to be a save/load operation. A replacement serializer should persist semantic record values and stable references, not raw `cGameNounManager*` or `cStarManager*` addresses.

## State/event model

The bounded static state graph is:

```text
noun manager construction
  -> factory create
  -> object identity + mObjects/mNouns insertion
  -> mNounMap vector invalidation
  -> GetData lower-bound/materialize/filter/add
  -> destroy mark + owner/cache/player-reference cleanup
  -> cache invalidation
  -> list unlink/release
  -> bulk noun/type destroy or manager teardown

star manager/record construction or load
  -> star record grid/database state
  -> empire map keyed by political ID
  -> current-player empire lazy cache
  -> lower-bound empire lookup
  -> map erase independent of player cache
  -> planet generation/materialization boundary
  -> stars.db.tmp -> stars.db replacement
```

The noun manager is an `IMessageListener` and Simulator strategy in the SDK (`GameNounManager.h:62-70`); its vtable, constructor, model-update body `FUN_00b22960`, and teardown body `FUN_00b22440` provide lifecycle surfaces. The star manager is also a strategy/message listener (`StarManager.h:129-132`). No universal event ABI is inferred: event/message transport remains a separate architecture boundary, as required by `docs/analysis/semantic-blueprint.md:115-121` and `docs/analysis/semantic-blueprint.md:943-955`.

## Competing hypotheses and predictions

### H1 — one shared owner, equal values

**Claim:** each noun-root pair and each star-root pair always contains the same manager pointer; a common publisher writes both words together.

**Predictions:**

- every mode transition snapshot has `DAT_0167eae0 == DAT_0167eb60` and `DAT_0167eae4 == DAT_0167eb0c`;
- publication and teardown are paired stores/releases in the same lifecycle operation;
- no unequal, null/stale, or rebind window occurs;
- consumers using alternate and canonical accessors observe identical owner-local map/list/cache state.

**Contradicting evidence:** physical storage is distinct and the two accessors read different words. Direct/byte-pattern scans find no paired publisher or equality operation. The large fan-in difference between alternate and canonical accessors is consistent with different operational use but does not prove unequal values.

**Status:** unresolved; no static evidence is sufficient to select H1.

### H2 — phase-specific owners or phase-specific publication

**Claim:** each pair contains different managers during initialization, mode transitions, Space/Cell handoff, or teardown; each word is published independently.

**Predictions:**

- a trace captures an unequal window or one root null/stale while the other is live;
- publication order is observable at mode entry and reversal at mode exit;
- noun cache or star empire cache state follows the active root used by its consumer;
- teardown releases one manager before the other, or a replacement changes one root only.

**Supporting evidence:** the alternate noun/star roots have radically different caller distributions; the cache path explicitly uses the alternate star root; the noun and star managers have separate vtables, fields, and state machines.

**Contradicting evidence:** no direct writer or runtime unequal window was recovered. SDK singleton wording is not a runtime observation and cannot reject H2.

**Status:** unresolved and architecture-relevant.

### H3 — stale/obsolete canonical root

**Claim:** one root is a compatibility/legacy slot that remains populated after the active root is rebound or cleared.

**Predictions:**

- the alternate root tracks the current manager while the canonical root retains an old pointer;
- a mode transition produces a stale object list/map or a canonical-root consumer sees the old manager;
- canonical-root teardown has no effect on active consumers, or the canonical root is never cleared.

**Supporting evidence:** canonical noun/star accessors have fewer direct callers than the alternate accessors; no canonical publication writer was found.

**Contradicting evidence:** the canonical noun accessor is used by 43 direct callers, and the canonical star accessor has a raw code xref; this is not enough to label either slot obsolete.

**Status:** unresolved; do not remove either port.

### H4 — opaque indirect/bulk/external publication

**Claim:** the roots are written by a computed store, table copy, relocation/loader path, external component, or bulk publication helper with no direct literal address xref.

**Predictions:**

- static recovery of a computed address/data-table writer or loader path;
- a runtime watchpoint records writes without a direct literal store in the main executable;
- a publication helper can explain all four root changes without a direct root equality operation.

**Supporting evidence:** the direct scans are bounded negatives; the root region is adjacent to a larger global service block and the binary has a service/strategy composition architecture.

**Contradicting evidence:** none decisive. The raw image contains zero values and no direct store pattern was found, but that is compatible with runtime/external publication.

**Status:** unresolved and the leading explanation for the static publication gap.

## Contradictory evidence summary

1. SDK documentation calls `cGameNounManager` and `cStarManager` singletons and exposes macros, but the binary has two storage words per manager family. SDK wording cannot prove equality.
2. The noun accessor `0x00b3d300` has 1,097 direct callers while the SDK-labeled `Get` at `0x00b3d400` has 43. This supports distinct access paths, not a conclusion about owner identity.
3. The star cache path at `0x01021300` uses `0x00b3d2a0` and lower-bound empire lookup; the separate canonical accessor at `0x00b3d3a0` is sparsely referenced. This does not prove the two values differ.
4. The noun and star roots have no direct store/clear xrefs, but their manager constructors, factory paths, cache invalidation paths, and destructor paths are richly present. Manager lifetime is not root publication lifetime.
5. `cStar` and `cStarRecord` share semantic star identity but are different types and storage layers. The link is explicit at `cStar+0x48`; physical aliasing is rejected.
6. `stars.db.tmp` replacement is direct static evidence for a narrow database boundary, not evidence that root pointers are serialized or restored.

## Smallest decisive observation

**One bounded original-process lifecycle trace** is the smallest observation that can separate H1-H3:

1. before simulator service publication, capture the four words, manager object addresses, vtable pointers, refcounts, and map/list anchor/size values;
2. immediately after noun and star manager construction/publication;
3. at each required transition: boot/menu → Cell → Space → Cell/menu, including the first frame where any pair is unequal;
4. immediately before and after noun create/destroy, star record generation, empire map erase, and current-player cache refresh;
5. during manager teardown, recording which root is cleared/replaced and which object releases occur.

The decisive pass condition is a complete publisher/equality/teardown matrix, not merely seeing equal values in one frame. One equal observation is insufficient; one unequal observation with the corresponding owner/lifetime transition is sufficient to reject unconditional H1 and force phase-aware identity/rebind/cache rules.

**Static-first continuation before Wine:** inspect computed/table references, PE loader/relocation paths, bulk-copy helpers, and the service-composition initialization graph for all four words. If those paths remain opaque, the runtime trace is necessary for original compatibility. Wine was not run in this investigation.

## Implementation decision

### Safe to proceed now

A clean-room implementation may proceed with:

- four separate opaque ports: noun alternate, noun canonical, star alternate, star canonical;
- explicit `publish`, `replace`, `invalidate`, and `unpublish` events per port;
- no implicit equality between ports and no singleton assumption;
- owner-qualified noun list/map/vector caches;
- lower-bound lookup with an explicit exactness postcondition where the replacement requires exact keys;
- successor-tolerant empire cache behavior retained as a compatibility surface;
- separate map erase and current-player cache invalidation;
- separate live noun, star record, live planet, and empire identities;
- serialization of semantic records and stable references, never raw service pointers.

The local architecture decision already authorizes this bounded interim boundary (`docs/analysis/architecture-decisions.md:29-51`; `docs/analysis/semantic-blueprint.md:961-969`).

### Not safe to proceed

Do not implement or claim:

- unconditional equality of `DAT_0167eae0`/`DAT_0167eb60` or `DAT_0167eae4`/`DAT_0167eb0c`;
- one canonical manager owner selected solely by SDK singleton wording or fan-in;
- root unpublication order or cross-root teardown;
- exact noun/empire find semantics where the binary uses lower-bound;
- guaranteed cache invalidation after map erase;
- raw root pointer save/restore or original-object identity across modes/plugins/saves;
- physical aliasing of `cStar` and `cStarRecord`.

The prior architecture decision explicitly leaves root identity/liveness and publication as unresolved unless compatibility is required (`docs/analysis/architecture-decisions.md:101-112`, `docs/analysis/architecture-decisions.md:132-138`).

## Final classification

- **Publisher:** unresolved; no direct/byte-pattern publisher recovered.
- **Storage:** four distinct four-byte root words; noun/star manager fields and vtables recovered below them.
- **Lookup:** noun-ID and political-ID paths are lower-bound/ceiling-style; no exact-find promotion.
- **Materialization:** noun factory insertion and star record/live-object association are bounded, but star record-to-live-planet body remains incomplete.
- **Invalidation:** noun vector invalidation is direct; empire map erase and current-player cache invalidation are independent.
- **Erase:** noun object/map/list erase paths are direct; star empire map erase is direct and does not clear the player cache.
- **Teardown:** noun manager object teardown is direct; root unpublication is not.
- **Ownership/lifetime:** intrusive references and manager-owned lists/maps are supported; root publication ownership and liveness are not.
- **Noun/star aliasing:** live `cStar` noun and persistent `cStarRecord` are separate objects linked by `cStar+0x48`; no physical alias.
- **Persistence:** star database replacement is bounded; noun registry is runtime reconstruction; raw root serialization is rejected.
- **Blocker status:** remains open for original root compatibility; bounded replacement architecture is implementable.
