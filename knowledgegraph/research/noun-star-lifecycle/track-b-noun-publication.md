# Track B — Noun publication and lifecycle

## Status and scope

Static-only investigation of the pinned live binary `SporeApp.exe` 3.1.0.22 (`x86:LE:32:windows`) through Ghidra decompilation, disassembly, xrefs, type layouts, and vtable data. No runtime execution, Wine, source modification, shared-artifact modification, or `SPORE/` access was used. The only file created by this track is this report.

This report concerns noun **publication/lifecycle** only. Star-record lookup, empire caching, and the separate star-root lifecycle are mentioned only where they constrain noun conclusions.

## Executive conclusion

The live binary supports two different lifecycle layers:

1. **Eager live-object publication** is closed for noun instances. `0x00b20c60` asks the app class factory for a concrete `cGameData`, gives it a runtime ID, publishes it to manager `mObjects +0x10c`, publishes it to `mNouns +0x78`, and invokes dirty-cache invalidation `0x00b201a0`.
2. **Lazy typed-view materialization** is also substantially closed. `0x00b21340` lower-bounds `mNounMap +0x98`, creates a cache record only on end, scans `mNouns` through four callbacks, clears `needsUpdate`, and returns a borrowed manager-owned vector. It is cached after the first successful materialization.
3. **Logical destruction and reclamation are separate.** `0x00b225d0` sets `cGameData+0x20`, retains the object in the manager's transient `field_80` vector, unlinks it from `mNouns` through `0x00b20d30`, and invalidates cached views. Later `0x00b22960` removes/releases the `mObjects` entry and releases the `field_80` retention.
4. **Normal noun destruction does not erase the `mNounMap` key.** The map payload is refreshed lazily; normal destroy performs logical list erase, not per-key cache-node erase. Whole-map cleanup belongs to manager teardown, not the individual noun lifecycle.
5. **The manager-root publication lifecycle remains unresolved.** A real `0x11c` `cGameNounManager` is constructed at `0x00b232b0`, allocated and retained in a parent/vector path at `0x00b61bd3..0x00b61c5d`, but the two global accessors `0x00b3d300 -> DAT_0167eae0` and `0x00b3d400 -> DAT_0167eb60` have only their accessor occurrences in exact byte scans. No direct writer, equality check, replacement, clear, or destructor-to-root-unpublication join is statically closed.
6. **The SDK address anchors are not all current binary function entries.** In this binary, `0x00b20bf0`, `0x00b22560`, and `0x00b23e40` land on `INT3` padding; `0x00b20dd0` and `0x00b228f0` land inside unrelated bodies; `0x00b221a0` lands inside manager teardown. The mechanically supported live bodies are `0x00b20c60`, `0x00b20d30`, `0x00b225d0`, `0x00b22650`, `0x00b227c0`, `0x00b22960`, and `0x00b237d0`.

The strongest safe model is therefore:

```text
static/app-lifetime type registration
  -> eager concrete cGameData allocation
  -> eager mObjects + mNouns publication
  -> lazy mNounMap lookup/materialization
  -> borrowed typed-view use
  -> dirty invalidation
  -> mNouns logical erase + deferred mObjects/field_80 reclamation
  -> manager-wide teardown
```

The service-root edge between that sequence and either noun-manager global remains open.

## Evidence authority and terminology

- Live Ghidra bytes/decompilation are primary for mechanics and failure behavior.
- The March 2017 SDK export is used for signatures, layouts, and vtable slot meaning, not as proof that an SDK address is a valid body in this binary:
  - `SporeGhidra_march2017.xml:23387-23430` defines `Get`, `CreateInstance`, `DestroyInstance`, `GetData`, and the four callback parameters plus noun ID.
  - `SporeGhidra_march2017.xml:23455-23484` defines the `0x11c` manager layout.
  - `SporeGhidra_march2017.xml:12919-12956` defines the `cGameData` vtable and `0x34` object layout.
  - `SporeGhidra_march2017.xml:32589-32604` defines `NounCreateMap` and `RegisterNounType`/`GetNounCreateMap` declarations.
- Community SDK source describes intent, not runtime proof:
  - `Spore ModAPI/Spore/Simulator/SubSystem/GameNounManager.h:42-60` defines the four callback roles.
  - `GameNounManager.h:62-86` says the manager creates/destroys Simulator objects and exposes typed views.
  - `GameNounManager.h:129-150` matches the live `0x11c` field offsets used here.
  - `GameNounManager.h:174-223` shows that `GetData` builds a lazy/filterable vector and may filter by noun ID or cast.
  - `Spore ModAPI/Spore/Simulator/NounClassFactories.h:11-33` declares a hash map from noun/type identity to a create function and says the class is already registered with the class manager.
- Repository adjudication agrees with most mechanics but retains root publication open:
  - `knowledgegraph/research/root-closure/followup-noun-boundary.md:7-13,53-91` closes lookup, materialization, callback, and successor behavior.
  - `knowledgegraph/research/root-closure-f0e310e0.json:456-525` records the same `0x00b21340` contract and open allocation/invalidation/erase questions.
  - `docs/analysis/architecture-blockers.md:31-89` keeps noun-root publication architecture-blocking.
  - `docs/analysis/architecture-decisions.md:29-51` requires separate noun-root ports and preserves lower-bound behavior.
  - `docs/analysis/semantic-blueprint.md:959-969` keeps publication, replacement, invalidation, and unpublication explicit and unresolved.
  - `docs/analysis/simulator-shared-state-interface.md:126-141` independently identifies `0x00b21340` as the noun map/materialization bridge.
  - `docs/analysis/gameplay-state-machines.md:395-408` classifies it as a shared noun registry and requires runtime instrumentation for map/update behavior.

No noun lifecycle implementation exists in the current OpenSpore `src/` tree. The only nearby registry is the unrelated game-mode registry: `src/apps/IGameMode.hpp:70-78` and its implementation at `src/apps/CellModeStrategy.cpp:89-127`. It has add/activate behavior but no noun factory, `mNounMap`, dirty vector, pending destruction, or root publication semantics.

## Structures and ownership

### `cGameNounManager` — `0x11c`

The SDK layout is confirmed by both the imported type and the live constructor/destructor:

| offset | live role | lifetime class |
|---:|---|---|
| `+0x00` | primary `IMessageListener` vptr | runtime object |
| `+0x04` | secondary `cStrategy` vptr | runtime object |
| `+0x08` | tertiary `IVirtual` vptr | runtime object |
| `+0x0c` | manager refcount | runtime ownership |
| `+0x54` | `mpAvatar` | borrowed/reference-managed runtime selection |
| `+0x58` | `mpAvatarHerd` | runtime ownership |
| `+0x70` | `mpPlayerTribe` | runtime ownership |
| `+0x74` | `mpPlayer` | runtime ownership |
| `+0x78` | `mNouns`, intrusive list of live `cGameData` | eager runtime publication |
| `+0x80` | `field_80`, vector of pending destruction retentions | transient runtime queue |
| `+0x98` | `mNounMap`, ordered `nounID -> tGameDataVectorT<cGameData>` | lazy runtime cache |
| `+0xb4` | `mPoliticalMap` | runtime index |
| `+0x10c` | `mObjects`, intrusive owner list | eager publication, later pruned |
| `+0x118` | final field | runtime |

Live constructor `0x00b232b0`:

- installs `0x0145ef10` at `+0x00`, `0x0145eec0` at `+0x04`, and `0x0145eeb8` at `+0x08`;
- initializes the intrusive-list anchors and all manager maps/vectors;
- returns the same receiver passed at `0x00b61beb`.

Primary vtable data at `0x0145ef10` contains:

| slot | address | bounded role |
|---:|---:|---|
| `+0x00` | `0x00b23430` | deleting destructor thunk |
| `+0x04` | `0x00b23ab0` | strategy/message dispatch body |
| `+0x08` | `0x00671f50` | inherited/base virtual body |
| `+0x0c` | `0x00ae06a0` | inherited/base virtual body |
| `+0x10` | `0x00476300` | inherited/base virtual body |

Secondary vtable data at `0x0145eec0` includes `0x00b25e80` and `0x00b237d0`; the latter is the manager-wide teardown body. The third subobject vtable begins at `0x0145eeb8`.

### `cGameData` — `0x34`

The live-relevant SDK fields are:

| offset | role |
|---:|---|
| `+0x00/+0x04` | primary/refcount vptrs |
| `+0x08` | `mnRefCount` |
| `+0x0c/+0x10` | intrusive `mNouns` links |
| `+0x20` | boolean set to one by `0x00b225d0`; exact semantic name is not proven |
| `+0x21` | `mbIsDestroyed`, set by teardown `0x00b20d30` |
| `+0x24` | runtime `mID`, assigned by `0x00b20c60` |
| `+0x28` | `mDefinitionID` |
| `+0x2c` | intrusive game-data owner |
| `+0x30` | `mPoliticalID` |

Vtable slots used by the noun path are exact from `SporeGhidra_march2017.xml:12919-12940`: `+0x0c Cast`, `+0x20 GetNounID`, `+0x24 SetDefinitionID`, `+0x2c IsDestroyed`, `+0x44 RemoveOwner`, and `+0x4c GetPoliticalID`.

### `tGameDataVectorT<cGameData>` — `0x18`

| offset | role |
|---:|---|
| `+0x00` | `needsUpdate` |
| `+0x04` | `mpBegin` |
| `+0x08` | `mpEnd` |
| `+0x0c` | `mpCapacity` |
| `+0x10/+0x14` | garbage/allocator state |

This is a manager-owned by-value map payload. `0x00b21340` returns a borrowed pointer to it; it does not AddRef or return ownership.

## Recovered lifecycle

## 0. Static/app-lifetime noun type registration

The exact live app class-factory publication is stronger than the stale `RegisterNounType` address:

```text
0x00f47ed0
  -> allocate 0x148 class manager, constructor 0x009206d0
  -> store in app field +0x24
  -> publish DAT_01667b84 through 0x009200a0
  -> 0x00692ee0 walks DAT_01600c58 descriptors
  -> for each unregistered descriptor, call class-manager vtable +0x04

0x00f47700
  -> 0x00692f20 walks the same descriptors and calls vtable +0x08
  -> 0x009200a0(0) clears DAT_01667b84
```

Evidence:

- `0x009200a0` is a direct read-old/write-new helper around `DAT_01667b84`.
- The class-manager vtable at `0x0143d824` has `0x00920b30` at `+0x04`, `0x00920780` at `+0x08`, and `0x00920110` at `+0x20`.
- `0x00692850` is the lazy per-descriptor form: if descriptor `+0x0c` is false, it calls class-manager vtable `+0x04` and stores the result.
- The descriptor list head `DAT_01600c58` has only the list readers/writer used by `0x00692ee0`, `0x00692f20`, and `0x00692f60` in the focused xref set.

This registration is **eager, app-lifetime, and not profile persistence**. It establishes type availability before noun objects are created.

The SDK's `NounCreateMap` remains a useful ABI description (`NounClassFactories.h:11-33`) but is not proven to be a separately live singleton in this binary. The recovered creation path uses the larger `0x148` app class manager and its descriptor list. Competing interpretations are listed below.

## 1. Create concrete noun instance — eager, `0x00b20c60`

The current generic creator is `0x00b20c60`, not SDK anchor `0x00b20bf0`.

Observed sequence:

1. Read app class factory through `0x00920090` (`DAT_01667b84`).
2. Call class-factory vtable `+0x20` with:
   - requested noun ID;
   - `0x17f243b`, the `cGameData` cast/type ID;
   - two zero arguments.
3. If the factory result is non-null, AddRef it.
4. Allocate a `0x0c` intrusive list node through `0x00f473a0`.
5. Link that intrusive pointer node into manager `mObjects +0x10c`.
6. Increment `DAT_0167be28` and assign the result to `cGameData+0x24` (`mID`).
7. Link the `cGameData`'s embedded `+0x0c/+0x10` nodes at the head of manager `mNouns +0x78`.
8. AddRef the published object and call `0x00b201a0(manager, object)`.
9. Return the raw object.

This body has 164 direct call xrefs in the live graph. Representative specialized creators are:

- `0x00b20e40`: creates noun `0x52aa6122` and initializes nested state.
- `0x00b20fb0`: ensures `mpPlayer` by creating noun `0x02c21781` when absent.
- `0x00b23940`: creates noun `0x01be418e` and initializes a nest/herd-related subtype.
- `0x00b22cc0`: creates from a descriptor, then calls object vtable `+0x24` (`SetDefinitionID`) and rolls back on false.

**Publication classification:** eager and immediate for both `mObjects` and `mNouns`.

## 2. Register/publish instance — eager dual ownership

Registration is not deferred:

- `mObjects +0x10c` is the intrusive owner list that holds a reference and is later pruned by `0x00b22960`.
- `mNouns +0x78` is the authoritative live noun list used by `0x00b21340` materialization.

The two registrations happen in `0x00b20c60` before it returns. The later `b201a0` call marks every compatible typed cache dirty, but does not publish the new instance; publication already occurred.

The SDK's `mObjects` name is retained because it is the imported field name. Its exact semantic difference from `mNouns` is only partly known: `mNouns` is directly scanned by typed lookup, while `mObjects` is walked by model/update/teardown code.

## 3. Lookup typed view — `0x00b21340`

The implementation ABI is:

```text
ECX = cGameNounManager*
+0x04 create callback
+0x08 clear callback
+0x0c add callback
+0x10 filter callback
+0x14 uint32 nounID
return borrowed tGameDataVectorT<cGameData>*
ret 0x14
```

This is four callbacks plus one noun ID. Documentation that calls it “five callbacks” is imprecise.

Sequence:

1. `0x00e5c780` lower-bounds `mNounMap` at `+0x98` by unsigned noun ID.
2. Compare the result only with map end at `+0x9c`.
3. On end, call the create callback and invoke insertion helper `0x00ba8420`.
4. On non-end, load the payload at map node `+0x14`; do **not** compare the node key with the requested noun ID.
5. If payload `needsUpdate` is nonzero, invoke the clear callback.
6. Walk `mNouns`; call `filter(cGameData*, nounID)`.
7. For each accepted object, call `add(record, object)`.
8. Clear `needsUpdate` and return the record.

This body has 254 unique callers / 318 direct call edges in the committed closure, including city/civilization, gameplay, and cross-mode consumers (`knowledgegraph/research/root-closure/track-d-noun-registry.md:208-224`).

### `0x00e5c780`

This is not exact find:

- map header is anchor at `+0x04`, root at `+0x0c`, size at `+0x14`;
- node key is `+0x10`, node payload is `+0x14`;
- traversal is unsigned ordered lower-bound;
- the helper is read-only and never inserts.

A missing requested key with a greater successor returns that successor. `0x00b21340` then uses and potentially refreshes the successor's payload under the requested ID. The cache key itself is not rewritten by the visible path.

## 4. Materialize typed vector — lazy, cached

Classification by trigger:

| condition | behavior |
|---|---|
| lower-bound result is end | invoke create callback and insertion path; materialize |
| existing record with `needsUpdate=1` | clear old elements, scan `mNouns`, append accepted objects, clear dirty bit |
| existing record with `needsUpdate=0` | return cached vector without scanning |
| existing greater successor, dirty | rebuild successor payload while filtering by the requested noun ID |
| existing greater successor, clean | return successor payload directly |

The representative callback set is exact:

| address | role | ownership/failure behavior |
|---:|---|---|
| `0x00b21080` | create `0x18` record | sets `needsUpdate=1`; returns null on its explicit allocation-null path |
| `0x00d3d420` | clear record | releases non-null vector elements through vtable `+0x04`, resets end |
| `0x00b236c0` | cast/add to `cCivilization` | `Cast(0x901f1362)`, AddRef/store, Release temporary |
| `0x00b1e500` | noun-ID filter | calls vtable `+0x20` (`GetNounID`) and compares |

`0x00b25f40` is a concrete use: it calls `0x00b21340` with the civilization callbacks and noun ID `0x018c816a`, then scans the returned vector and compares each object's vtable `+0x4c` political ID. It returns the first raw match or null and performs no ownership transfer. This is the chain summarized at `knowledgegraph/research/root-closure/followup-noun-boundary.md:93-116`.

## 5. Use — borrowed view, runtime object

Use is direct and immediate after registration/materialization. Representative paths:

- `0x00b25f40`: civilization lookup by political ID.
- `0x00b294c0`: `0x00b3d300` supplies a noun-manager-compatible receiver, then `0x00b21340` obtains the city vector for `0x018c43e8` and coordinates city/civilization state.
- `0x00b25fe0`: teardown/update orchestration that materializes several noun categories and queues selected destruction.
- `0x00b25ee0`: iterates the cached civilization vector and queues each object for destruction.

The return from `0x00b21340` and the raw object pointers in representative consumers are borrowed. Cache elements themselves own intrusive references through the add callback, but lookup does not AddRef the returned record or its elements.

External consumers can therefore retain a raw noun pointer after invalidation unless their own ownership rules prevent it. No lock, generation token, or use-count guard was found at the lookup boundary.

## 6. Invalidate — `0x00b201a0`

`0x00b201a0` has exactly two direct callers: create `0x00b20c60` and destroy-queue `0x00b225d0`. That is strong lifecycle placement evidence.

Sequence:

1. Return immediately for a null object.
2. Read `GetNounID()` through vtable `+0x20`.
3. Lower-bound `mNounMap` and, if the result is not end, set that payload's `needsUpdate=1` without checking exact key equality.
4. Iterate all map nodes.
5. For each still-clean cache record, call the new object's vtable `+0x0c` (`Cast`) with the map key.
6. If the cast succeeds, set that record's `needsUpdate=1`.

This invalidates both noun-ID projections and cast-based projections. It has the same successor hazard as lookup. A newly created object therefore cannot appear in a previously materialized view until `0x00b21340` refreshes it.

Invalidation does not clear any returned pointer. It only marks manager-owned cache records dirty.

## 7. Logical erase — `0x00b20d30`

`0x00b20d30` is the noun-list erase/terminal teardown body, called by `0x00b225d0` and by type-specific cleanup such as `0x00b22bc0`.

If the object reports `IsDestroyed()==false` through vtable `+0x2c`, it:

1. invokes the subtype teardown virtual at `+0x20`;
2. invokes service/configure teardown at `+0x44`;
3. asks the subtype to remove owner state through vtable `+0x0c` for type `0x01186577`;
4. sets `cGameData+0x21` (`mbIsDestroyed=1`);
5. clears and releases the owner intrusive pointer at `+0x2c`;
6. calls additional owner/remove-owner virtuals;
7. unlinks `+0x0c/+0x10` from `mNouns`, clears both links, and calls a virtual cleanup slot.

If `IsDestroyed()` is already true, the body returns without repeating teardown. This is the clearest idempotence guard in the lifecycle.

**What is erased:** the object's intrusive membership in `mNouns`, plus owner/subtype state.

**What is not erased here:** the object's `mObjects` list node and the `mNounMap` cache node.

## 8. Queue destruction — `0x00b225d0`

`0x00b225d0` has 227 direct xrefs and is the dominant logical destroy entry.

Sequence:

1. Set `cGameData+0x20 = 1` (field name unresolved; it precedes `mbIsDestroyed` and is not the SDK `IsDestroyed` slot).
2. AddRef the object and append it to manager `field_80 +0x80`.
3. Release the temporary reference.
4. Call `0x00b20d30` for subtype teardown and `mNouns` erase.
5. Call `0x00b201a0` to dirty noun/cast views.

This is not immediate reclamation. The `field_80` retention keeps the object alive until update/teardown drains it.

Selective and global wrappers are distinct:

- `0x00b22650(manager, nounID)` walks `mNouns`, compares each `GetNounID()` for exact equality, retains matches in a temporary global vector, then calls `0x00b225d0` for each. It has 40 direct call xrefs.
- `0x00b227c0(manager)` performs the same queueing for all nouns. It has five direct call xrefs.
- `0x00b25ee0` and `0x00b25fe0` compose these helpers during larger cleanup sequences.

## 9. Reclaim/update drain — `0x00b22960`

`0x00b22960` is the post-queue update/teardown drain. It has 29 direct callers.

Observed behavior:

1. Walk manager `mObjects +0x10c`.
2. For each object, obtain its spatial model/view and inspect model/visibility state.
3. Depending on model readiness/flags, update the model or remove the object from `mObjects`.
4. On removal, unlink and clear the list links, Release the object, and free the `0x0c` list node.
5. Clear manager `field_80 +0x80..+0x88` through `0x00e25bd0`, which Releases each retained pending-destroy object.
6. Release the temporary shadow-world handle.

Thus:

- logical destruction (`+0x21`) and mNouns erase happen in the destroy path;
- ownership reclamation and mObjects erase happen later;
- external references can keep the actual allocation alive after both.

## 10. Manager teardown — `0x00b237d0`

The live manager teardown body:

- releases manager-owned pointers and special fields;
- destroys the player through `0x00b225d0` and then calls `0x00b22960`;
- clears/reset manager lists and vectors;
- tears down internal maps and owner collections;
- reinitializes the final list anchors.

`0x00b234c0` is the deleting-destructor thunk at primary vtable `+0x00`; it calls `0x00b22440` and optionally frees the `0x11c` allocation.

This closes manager-internal teardown, but **not service-root unpublication**: no direct store to `DAT_0167eae0` or `DAT_0167eb60` is joined to this destructor.

## The requested “erase” phase is not one operation

The original binary does not expose a clean `invalidate -> erase map key -> destroy` chain for an individual noun.

Observed instead:

```text
invalidate dirty vector
  -> set destroyed/pending bytes
  -> unlink cGameData from mNouns
  -> retain in field_80
  -> later unlink mObjects and release
  -> later GetData clears cached vector elements and rebuilds
```

The `mNounMap` node can outlive all objects of that noun. An empty rebuilt vector is the normal representation. No exact-key erase from `cGameData.mNounMap` was found in the normal create/destroy bodies. Whole-map cleanup is manager teardown.

This distinction matters for compatibility: replacing noun destruction with unconditional `mNounMap.erase(nounID)` would not match observed mechanics.

## Root publication and replacement

## Constructor/parent publication candidate

A strong allocation path exists:

```text
0x00b60d80
  0x00b61bd3 push "Simulator/SubSystem/GameNounManager"
  0x00b61bd8 push 0x11c
  0x00b61bdd allocate
  0x00b61beb call cGameNounManager ctor 0x00b232b0
  0x00b61bf7 store result at parent+0x20
  0x00b61bff/0x00b61c3d invoke secondary vtable behavior
  0x00b61c1f..0x00b61c5d AddRef and append to parent vector
```

This proves construction and parent-owned retention. It is the best static publication candidate for a live manager instance.

## Global noun roots remain separate

| accessor | backing word | direct behavior | focused xref result |
|---|---|---|---|
| `0x00b3d300` | `DAT_0167eae0` | `mov eax, word; ret` | one direct read xref; exact byte pattern only at `0x00b3d301` |
| `0x00b3d400` | `DAT_0167eb60` | `mov eax, word; ret` | one direct read xref; exact byte pattern only at `0x00b3d401` |

There is no direct:

- store/replacement;
- clear;
- equality comparison;
- null-to-live transition;
- manager-destructor-to-global-clear join.

The canonical `Get` body is preserved at `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cGameNounManager__Get.c:1-13`. The alternate accessor has much larger consumer fan-in, while the canonical accessor still has 63 direct xrefs. Neither can be removed or merged.

The parent slot/vector path may be joined to one or both global words by generic service registration, computed indexing, bulk copy, or runtime-only publication. Static evidence does not select among those mechanisms.

## Eager/lazy/cached/transient/persistent classification

| state | classification | reason |
|---|---|---|
| app class manager `DAT_01667b84` and type descriptors | static/app-lifetime registration | published during app init, unregistered and cleared at shutdown |
| `cGameNounManager` allocation | runtime object | constructed and parent-retained; root publication unresolved |
| concrete `cGameData` allocation | eager runtime object | allocated synchronously by `0x00b20c60` |
| `mObjects` and `mNouns` membership | eager runtime publication | linked before create returns |
| `mNounMap` record | lazy/cache | created on end and reused while clean |
| typed vector elements | cached/reference-managed projection | add callback retains; clear callback releases |
| `needsUpdate` | transient dirty state | set by create/destroy invalidation and cleared after materialization |
| `field_80` | transient pending-destroy queue | retains objects until update/teardown drain |
| temporary destruction vectors near `0x0167c340/0x0167c358` | transient scratch | exact noun selection, released after queueing |
| `cGameData+0x20/+0x21` | transient lifecycle status | pending/unknown then `mbIsDestroyed` |
| noun ID, definition ID, owner, political ID | profile/save candidates, not proven persistent bytes | `cGameData` is serializable, but field emission/restoration is unresolved |
| `mNounMap` pointer/cache state | not save state | runtime projection; serialization docs explicitly separate it from persistence |
| noun manager global words | runtime service handles, persistence unknown | no static publication/teardown; no direct serialization evidence |

Persistence boundary:

- `ISimulatorSerializable` provides Write/Read/XML and noun/object identity slots, but not complete subtype field coverage (`docs/analysis/serialization-model.md:201-205`).
- Noun IDs, political IDs, class IDs, and field IDs are separate domains (`docs/analysis/serialization-model.md:303-314`).
- `cGameNounManager` owns live noun maps/lists and is a reconstruction target on load, not the persistence format itself (`docs/analysis/serialization-model.md:349-360`).
- `cGameData` and several concrete owners are profile/save candidates, while noun instances are runtime transient state (`docs/analysis/gameplay-data-model.md:329-335,351-356`).
- No evidence shows that `DAT_0167eae0` or `DAT_0167eb60` is saved or restored.

## Events are not the core publication mechanism

The App event system has explicit registration and emission surfaces at `0x008839a0` family and queue processing at `0x008841f0/0x00847f0`; registration is separate from delivery (`docs/analysis/event-message-map.md:40-54,116-126`).

`GameNounStatusChangedMessage` is SDK-known as a `0x40` `StandardMessage`, but the event map does not establish a producer or connect it to `0x00b20c60`, `0x00b201a0`, or `0x00b225d0` (`docs/analysis/event-message-map.md:52-55`). The recovered core noun lifecycle is list/cache mechanics, not message-bus registration.

## Failure semantics

| failure/edge | observed behavior | confidence |
|---|---|---|
| class descriptor registration | per-descriptor success byte is stored; lazy retry path exists; no aggregate failure channel observed | high for mechanics |
| class manager shutdown | descriptors are unregistered and `DAT_01667b84` is cleared | high |
| manager allocation in `0x00b61bd3` path | null branch falls into secondary-vtable use without a recoverable return; no graceful manager-null path | high static absence of guard; allocator policy unknown |
| class factory noun creation | `0x00b20c60` conditionally AddRefs but later dereferences the object/list node without a null return path | high; likely fatal/bad state on actual null |
| post-create subtype init in `0x00b22cc0` | vtable `+0x24` false triggers `0x00b225d0` and returns null | high |
| typed cache create allocation | `0x00b21080` can return null; `0x00b21340` has no local null-record recovery | high |
| map node allocation | `0x00ba83a0` allocates `0x18`; no visible exception/rollback contract | high mechanics, low allocator policy |
| create-result ownership through `0x00ba8420` | stack-built key/value neighborhood is visible, but decompiler/stack typing does not close callback-result versus inserted-payload ownership | unresolved |
| lower-bound absent with greater successor | successor payload is used/rebuilt under requested ID; no exact-key check | high; behavior hazard |
| lower-bound absent with no successor | create/insertion path is taken | high |
| filter rejects object | object is omitted; this is not an error result | high |
| add/clear callback failure | callbacks are `void`; no direct status channel | high |
| null `this`, record, or list element in `0x00b21340` | no general guard; consumers commonly dereference returned record | high static absence of guard |
| null object invalidation | `0x00b201a0` returns | high |
| repeated destruction | `IsDestroyed` true makes `0x00b20d30` a no-op | high |
| destroy with external refs | manager releases its refs; actual deallocation depends on remaining refcount | high ownership inference |
| cache invalidation versus retained borrowed pointer | no generation/use-count protection at lookup | high static absence |
| lock/reentrancy/thread safety | no lock or reentrancy guard in the focused bodies | unresolved; runtime or broader static audit required |
| exact `mNounMap` key erase | not present in normal create/destroy path | medium-high; bounded negative |

## Competing hypotheses

## H1 — Eager live nouns, lazy typed vectors

**Prediction:** concrete objects are immediately in `mNouns`; the first typed query allocates a map record; later clean queries do not rescan; create/dirty only set `needsUpdate`.

**Evidence for:**

- `0x00b20c60` links `mObjects` and `mNouns` before returning.
- `0x00b21340` calls create/insertion only on lower-bound end and refreshes only when `needsUpdate` is set.
- `0x00b201a0` is called from both create and destroy paths.
- callback thunks exactly implement create/clear/add/filter.

**Evidence against:** none material.

**Verdict:** **SUPPORTED, high confidence.**

## H2 — `NounCreateMap` is the exact live singleton used by `CreateInstance`

**Prediction:** `GetNounCreateMap` returns the same object consulted by `0x00b20c60`; its `classMap` is a `noun/type -> create function` map.

**Evidence for:**

- SDK `NounCreateMap` and `RegisterNounType` declarations.
- `NounClassFactories.h:29-30` notes the class is already registered with the class manager.
- the binary clearly has an app class factory and per-descriptor registration.

**Evidence against:**

- current creator calls `DAT_01667b84` vtable `+0x20`, not an imported `NounCreateMap` function;
- current class manager is `0x148`, while SDK `NounCreateMap` is `0x30`;
- SDK anchors `0x00b23e40` and `0x00b221a0` are not current function entries;
- the live registration list is `DAT_01600c58` descriptor nodes, not a proven `NounCreateMap::classMap`.

**Verdict:** **PARTIALLY SUPPORTED as ABI history/type intent; rejected as the exact current creation singleton without more evidence.**

## H3 — `0x00b21340` is exact `cGameNounManager::GetData`

**Prediction:** ECX manager, four callbacks, noun ID, `ret 0x14`, `mNounMap+0x98`, manager-owned `tGameDataVectorT*` return.

**Evidence for:** every item is direct; 254 callers span expected consumers; vtable/SDK callback contract matches.

**Evidence against:** SDK export labels the preceding split continuation `0x00b212d0`, and imported decompilation is contaminated.

**Verdict:** **SUPPORTED, high confidence.**

## H4 — Destroy erases the noun cache key before object teardown

**Prediction:** `DestroyInstance` removes `mNounMap[nounID]`; a later lookup allocates a new record.

**Evidence for:** generic map erase helpers exist elsewhere and `GetData` can create on end.

**Evidence against:**

- destroy path only calls `0x00b201a0` dirty marking;
- `0x00b20d30` unlinks `mNouns`, not `mNounMap`;
- `0x00b22960` drains object/pending vectors, not noun map keys;
- manager teardown is the only closed whole-map cleanup path.

**Verdict:** **REJECTED for the normal individual destroy path.**

## H5 — The two noun-manager globals are always the same object

**Prediction:** paired constructor publications, paired replacement/clear, no unequal/null window, equivalent consumers.

**Evidence for:** both accessors are used as noun-manager-compatible pointers; the SDK calls `Get` a singleton accessor.

**Evidence against:** distinct storage words, no direct paired writer/clear/equality, canonical and alternate fan-ins differ sharply.

**Verdict:** **UNRESOLVED; static evidence does not prove equality or inequality.**

## H6 — One global is stale/compatibility-only

**Prediction:** after rebind, active alternate consumers continue using the old manager while canonical consumers see a different one; canonical teardown does not affect active consumers.

**Evidence for:** `0x00b3d300` has much larger fan-in; canonical publisher is not recovered.

**Evidence against:** canonical `0x00b3d400` has 63 direct xrefs, including Cell initialization and mode entry; no stale window is observed.

**Verdict:** **POSSIBLE, not selected.**

## H7 — Root publication occurs through computed, bulk, loader, or external service registration

**Prediction:** no literal word store; parent/strategy registration, table copy, computed address, or runtime-only write joins the constructor allocation to one or both globals.

**Evidence for:** real constructor/parent publication exists at `0x00b61bd3..0x00b61c5d`; exact byte scans find no direct root stores.

**Evidence against:** no decisive join has been recovered.

**Verdict:** **POSSIBLE and the leading explanation for the missing direct publisher, but unconfirmed.**

## H8 — Save/load directly republishes the noun manager global

**Prediction:** serializer code writes `DAT_0167eae0`/`DAT_0167eb60`, or restoration allocates a new manager and stores it.

**Evidence for:** none in focused xrefs/serialization artifacts.

**Evidence against:** noun manager is classified as runtime reconstruction state; cGameData persistence is a separate field/identity graph; no root serialization or pointer remapping is established.

**Verdict:** **UNSUPPORTED.**

## Contradictions and boundary corrections

1. **SDK function addresses are partly stale for this binary.** `0x00b20bf0`, `0x00b22560`, and `0x00b23e40` are `INT3`; `0x00b20dd0`, `0x00b228f0`, and `0x00b221a0` are interior instructions. The report uses live mechanics rather than promoting these anchors.
2. **SDK GetData address mismatch is boundary contamination.** `0x00b212d0` is a continuation reached inside `0x00b211e0`; `0x00b21340` independently matches the full five-word ABI. See `knowledgegraph/research/root-closure/followup-noun-boundary.md:15-51`.
3. **Return type differs by source layer.** The normal SDK header returns `tGameDataVectorT&`, while the SDK-to-Ghidra declaration and live EAX behavior use a pointer. Consumers treat it as a pointer. This report records the binary pointer contract.
4. **“Five callbacks” is wrong.** There are four callback pointers plus `uint32 nounID` (`SporeGhidra_march2017.xml:23408-23415`).
5. **Exact-key assumptions are wrong.** Both `0x00b21340` and `0x00b201a0` compare only against end after lower-bound.
6. **The create result versus `0x00ba8420` inserted-payload ownership remains open.** The helper allocates a `0x18` node and copies two words, but current Ghidra typing does not reliably close the stack pair. The prior static report preserves the same uncertainty at `knowledgegraph/research/root-closure/followup-noun-boundary.md:70-82`.
7. **Manager-internal destruction is not root unpublication.** `0x00b237d0` closes containers, not either global slot.
8. **Noun and event registration are separate.** The noun path does not contain App message-manager registration, and `GameNounStatusChangedMessage` is not joined to it.
9. **The noun manager is not a universal cross-mode object ABI.** The repository's qualified model remains appropriate: `docs/analysis/gameplay-data-model.md:252-267` and `docs/analysis/semantic-blueprint.md:993-1004`.

## Runtime requirement

Static analysis is sufficient for the create, list publication, lazy materialization, invalidation, logical erase, deferred reclamation, and manager-internal teardown mechanics.

Runtime is required to resolve:

1. first publication of `DAT_0167eae0` and `DAT_0167eb60`;
2. whether either is phase-specific, stale, or an alias of the parent-retained manager;
3. replacement/clear/unpublication order during mode transition and shutdown;
4. whether one constructor allocation is published to both, one, neither, or different allocations;
5. whether root readers can observe null/unequal windows;
6. actual first noun create failure, registration failure, and subtype-init rollback behavior;
7. real `mNounMap` node survival across the first destroy and first subsequent lookup;
8. lock/reentrancy behavior if noun creation/destruction occurs from callbacks or worker threads.

## Smallest decisive runtime trace

One naturally reachable mode lifecycle with synchronized observations is sufficient:

```text
watch/break:
  0x009200a0          class-factory publish/clear
  0x00692ee0          descriptor registration
  0x00b61bd3..0x00b61c5d manager allocation/parent publication
  0x00b3d300          alternate noun-root read
  0x00b3d400          canonical noun-root read
  0x00b20c60          noun create
  0x00b201a0          invalidation
  0x00b21340          lookup/materialize
  0x00b225d0          destroy queue
  0x00b20d30          terminal teardown/mNouns erase
  0x00b22960          mObjects/pending-destroy drain
  0x00b237d0          manager teardown
```

At each event record:

- `DAT_0167eae0`, `DAT_0167eb60`, and the parent slot from `0x00b61bf7`;
- pointee address and primary vptr for each non-null manager;
- class-factory `DAT_01667b84`;
- `mNouns` head/tail, `mObjects` head/tail, `field_80` begin/end, and `mNounMap` size;
- requested noun ID, lower-bound node key, returned cache pointer, and `needsUpdate` before/after;
- object refcount, `+0x20`, `+0x21`, and membership before/after each destroy stage.

Capture these states:

1. immediately before Simulator subsystem construction;
2. after `0x00b61c5d`;
3. after one first `GetData` miss and one second hit;
4. immediately after create invalidation;
5. after `0x00b225d0` but before `0x00b22960`;
6. after the drain;
7. during mode exit;
8. after manager destructor and after App shutdown.

### Pass condition

A complete publisher/equality/teardown matrix for the two noun roots. One unequal snapshot rejects unconditional equality but cannot prove a positive equality model. Runtime is unnecessary for implementing only the already-closed noun-object/cache mechanics; it is necessary before collapsing the two service roots or emulating root publication compatibility.

## Final lifecycle classification

```text
REGISTER TYPE
  eager app-lifetime
  0xf47ed0 -> 0x9200a0(DAT_01667b84) -> 0x692ee0 -> class-manager vtable +4

PUBLISH MANAGER ROOT
  runtime service publication
  constructor/parent candidate 0xb61bd3..0xb61c5d
  global DAT_0167eae0 / DAT_0167eb60 join UNRESOLVED

CREATE NOUN
  eager concrete allocation
  0xb20c60 -> class factory vtable +0x20

REGISTER/PUBLISH INSTANCE
  eager
  0xb20c60 -> mObjects +0x10c and mNouns +0x78

LOOKUP
  lazy lower-bound lookup
  0xb21340 -> 0xe5c780; successor tolerant

MATERIALIZE
  lazy on end/dirty
  create -> insert -> clear -> filter/add -> clear needsUpdate

USE
  runtime borrowed pointer/vector
  examples 0xb25f40, 0xb294c0, 0xb25fe0

INVALIDATE
  transient dirty marking
  0xb201a0; noun lower-bound plus cast scan

ERASE
  logical membership erase, not map-key erase
  0xb20d30 unlinks mNouns; 0xb22960 later prunes mObjects

DESTROY
  logical + deferred physical
  0xb225d0 pending/detach/invalidate
  0xb20d30 IsDestroyed + mNouns erase
  0xb22960 mObjects erase + field_80 release

PERSIST
  cGameData fields are save candidates
  manager/map/vector/root pointers are runtime state; exact restoration unresolved
```
