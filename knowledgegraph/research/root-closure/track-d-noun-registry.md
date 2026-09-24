# Track D — Noun Registry Root Closure

## Status and scope

**Static-only result; no runtime evidence.** Binary: `SporeApp.exe` 3.1.0.22, SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`, `x86:LE:32:windows`.

This track closes the static identity and boundary contract for `0x00b21340`, `0x00e5c780`, and `0x00ba8420`; it does not modify SPORE, source, historical artifacts, or the Phase-0 interface.

## Executive finding

`0x00b21340` is the high-confidence implementation entry for **`Simulator::cGameNounManager::GetData`**, but the SDK XML address **`0x00b212d0` is not safe to merge with it as the same exact function entry**.

| item | address | result | confidence |
|---|---:|---|---|
| `cGameNounManager::GetData` implementation | `0x00b21340` | noun-vector cache lookup/materialization | high |
| SDK-declared `GetData` address | `0x00b212d0` | distinct 98-byte Ghidra function; decompilation is boundary-contaminated | low exact-address confidence |
| generic map helper | `0x00e5c780` | unsigned ordered-map `lower_bound`; no mutation | high mechanics, medium exact ABI |
| noun-path mutation helper | `0x00ba8420` | probable `mNounMap` insertion/default-record construction | medium role, low exact ABI/failure contract |
| noun manager singleton | `0x00b3d400` | returns global `cGameNounManager*` from `DAT_0167eb60` | confirmed |

The safe label is:

> `Simulator::cGameNounManager::GetData [implementation 0x00b21340; SDK address 0x00b212d0 boundary-contaminated]`

## Identity adjudication

### Why `0x00b21340` is GetData

The SDK prototype is:

```cpp
tGameDataVectorT<Simulator::cGameData> *GetData(
    cGameNounManager *this,
    ContainerCreateCallback_t pCreateCallback,
    ContainerClearCallback_t pClearCallback,
    ContainerAddCallback_t pAddCallback,
    ContainerFilterCallback_t pFilterCallback,
    uint32_t nounID);
```

Source: `.spore-analysis/ghidra-exports/spore_sdk.xml:23408`.

`0x00b21340` independently matches the complete contract:

- ECX `this`, five 32-bit stack arguments, and `RET 0x14`.
- Reads/writes `cGameNounManager::mNounMap +0x98`.
- Returns a `tGameDataVectorT<Simulator::cGameData>*` map payload.
- Calls the generic lower-bound helper and a map mutation/construction helper.
- Is the direct target of 318 callsites from 254 unique caller functions, including the noun accessor, culture-creation, and state/empire bridge families.

### Why the SDK address remains contradictory

`0x00b212d0` is also a distinct Ghidra function of 98 bytes. The pinned xrefs show only one direct caller, `0x00b211e0` at `0x00b212cb`; `0x00b21340` has 318 direct-call edges. The available decompilation at `0x00b212d0` has inconsistent locals and callback shapes and even recursively calls the SDK-named body (`.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cGameNounManager__GetData.c:8-55`). It is therefore evidence of a boundary/import mismatch, not proof that `0x00b212d0` and `0x00b21340` are one exact entry.

## Resolved contract: `0x00b21340`

### ABI and data flow

```text
ECX cGameNounManager*
+0x04 pCreateCallback
+0x08 pClearCallback
+0x0c pAddCallback
+0x10 pFilterCallback
+0x14 uint32_t nounID
-> tGameDataVectorT<cGameData>*
```

Static path:

1. Search `this+0x98` (`mNounMap`) with unsigned `lower_bound` through `0x00e5c780` at `0x00b2135a`.
2. If the noun-specific map record is absent or requires materialization, call `0x00ba8420` at `0x00b21395` to insert/default-construct the record.
3. If the record is stale, project manager-owned `mNouns` entries into the noun-specific vector through the callback boundary.
4. Apply `pFilter(cGameData*, uint)` to each list element and pass accepted elements to `pAdd(vector*, cGameData*)`.
5. Clear `tGameDataVectorT::needsUpdate +0x00` and return the pointer to the manager-owned map payload.

The callback roles and `needsUpdate` behavior are high-confidence; the exact create/clear/add/filter sequencing is medium-confidence until the boundary is retyped.

### Callbacks

| SDK type | exact signature | resolved role |
|---|---|---|
| `ContainerCreateCallback_t` | `tGameDataVectorT<cGameData>* (*)(void)` | create/obtain the vector record |
| `ContainerClearCallback_t` | `void (*)(tGameDataVectorT<cGameData>*)` | clear/release vector contents before refresh |
| `ContainerAddCallback_t` | `void (*)(tGameDataVectorT<cGameData>*, cGameData*)` | append an accepted noun object |
| `ContainerFilterCallback_t` | `bool (*)(cGameData*, uint)` | test a `mNouns` element against noun ID/context |

SDK definitions: `.spore-analysis/ghidra-exports/spore_sdk.xml:23366-23386`.

## `cGameNounManager` and container layouts

### `cGameNounManager` — `0x11c` bytes

| offset | field | type |
|---:|---|---|
| `+0x00` | `_vftable0` | `IMessageListener__vftable*` |
| `+0x04` | `_vftable1` | `ISimulatorStrategy__vftable*` |
| `+0x08` | `_vftable2` | `IVirtual__vftable*` |
| `+0x0c` | `mnRefCount` | `int` |
| `+0x78` | `mNouns` | `intrusive_list<cGameData>` (`0x08`) |
| `+0x80` | `field_80` | `vector<intrusive_ptr<Object>>` (`0x14`) |
| `+0x98` | `mNounMap` | `map<uint32_t,tGameDataVectorT<cGameData>>` (`0x1c`) |
| `+0xb4` | `mPoliticalMap` | `map<int,int>` (`0x1c`) |
| `+0x10c` | `mObjects` | `list<intrusive_ptr<cGameData>>` (`0x0c`) |
| `+0x118` | `field_118` | `int` |

SDK source: `.spore-analysis/ghidra-exports/spore_sdk.xml:23455-23484`.

`manager+0x9c` is internal `mNounMap` anchor/end storage, not a separately declared manager field.

### `mNounMap`

```text
map +0x00  mCompare
map +0x04  rbtree anchor/end (0x10 bytes)
map +0x0c  root observed by 0x00e5c780
map +0x14  mnSize
map +0x18  allocator

node +0x00  rbtree_node_base (0x10 bytes)
node +0x10  uint32 nounID key
node +0x14  tGameDataVectorT<cGameData> payload
```

The map value is stored by value in each node. The returned vector pointer therefore points into manager-owned map storage.

### `tGameDataVectorT<cGameData>` — `0x18` bytes

| offset | field | type |
|---:|---|---|
| `+0x00` | `needsUpdate` | `bool` |
| `+0x01` | padding | `undefined[3]` |
| `+0x04` | `mpBegin` | `intrusive_ptr<cGameData>*` |
| `+0x08` | `mpEnd` | `intrusive_ptr<cGameData>*` |
| `+0x0c` | `mpCapacity` | `intrusive_ptr<cGameData>*` |
| `+0x10` | `mGarbage` | `int` |
| `+0x14` | `mAllocator` | `eastl::allocator` |

SDK source: `.spore-analysis/ghidra-exports/spore_sdk.xml:23358-23364`.

This resolves the earlier partial `0x10`-byte mechanics map: the complete SDK record is `0x18` bytes.

### `mNouns` and `cGameData`

`mNouns` is an `intrusive_list<cGameData>` with an `0x08` anchor. The list links are embedded in each `cGameData`:

| `cGameData` offset | field |
|---:|---|
| `+0x08` | `mnRefCount` |
| `+0x0c` | `mpNext` |
| `+0x10` | `mpPrev` |
| `+0x24` | `mID` |
| `+0x28` | `mDefinitionID` |
| `+0x2c` | `mpGameDataOwner` (`intrusive_ptr<cGameData>`) |
| `+0x30` | `mPoliticalID` |

SDK source: `.spore-analysis/ghidra-exports/spore_sdk.xml:12942-12956`.

The old “unknown noun list node with `next +0x0c`” is resolved: the list element is `cGameData`, with links at `+0x0c/+0x10`.

## Helper contracts

### `0x00e5c780` — unsigned map `lower_bound`

- 70 bytes; 239 unique callers; 265 direct-call edges; no outgoing calls.
- Inputs include an ECX map object, a key pointer, and an out iterator/end-result pointer; exact result encoding remains unresolved.
- Reads map end `+0x04`, root `+0x0c`, and unsigned node key `+0x10`.
- Does not mutate the map and does not insert.
- Missing keys produce an end/first-greater lower-bound result; callers must still check key equality.

The name `map_int_whatever_find` is misleading; use **generic unsigned ordered-map lower-bound helper**.

### `0x00ba8420` — probable noun-map insertion/default construction

- 135 bytes; six unique callers and seven direct-call edges.
- Noun path: `0x00b21340` calls it at `0x00b21395`.
- Other callers: `0x00b2ede0`, `0x00baa660`, `0x00d02440`, `0x00d33c30` (twice), and `0x00fe4d60`.
- Calls `0x009215c0` at `0x00ba845b` and `0x00ba83a0` at `0x00ba847c`, consistent with allocation/node construction.

Exact template identity, signature, duplicate handling, allocator failure behavior, and return encoding are unresolved. Keep the role as **probable `mNounMap` insertion/default-record materializer**, not a closed `operator[]` contract.

## Lifecycle and ownership

1. `cGameNounManager::Get` at `0x00b3d400` returns global `DAT_0167eb60` as a borrowed `cGameNounManager*`.
2. `mNounMap` caches one `tGameDataVectorT<cGameData>` per `uint32_t` noun ID.
3. `mNouns` is the manager-owned intrusive list of `cGameData` objects.
4. `GetData` materializes or refreshes the noun-specific vector, then clears `needsUpdate`.
5. The returned vector pointer is manager-owned and borrowed. No caller-side release or ownership transfer is established.
6. Vector elements are `intrusive_ptr<cGameData>` values. Exact AddRef/Release sites are delegated to the create/clear/add callbacks and noun lifecycle methods; this target does not expose a direct cGameData ownership call.
7. `mObjects` at `+0x10c` is a separate `list<intrusive_ptr<cGameData>>`; its participation in `GetData` is not proven.

The likely invalidation writers are `cGameNounManager::CreateInstance` and `DestroyInstance`, but this track did not establish the exact repaired function bodies or their writes to `needsUpdate`.

## Failure semantics

| case | static contract |
|---|---|
| lower-bound miss | `0x00e5c780` yields end/first-greater; a separate noun-path record-construction branch uses `0x00ba8420` rather than treating lower-bound as exact find; exact miss/stale predicate is medium-confidence |
| filter false | element is excluded; this is not an error result |
| add/clear failure | callbacks return `void`, so no direct status channel exists |
| normal success | returns noun-specific map payload pointer with `needsUpdate` clear |
| null create result | unresolved; may propagate or take another path |
| allocation failure | unresolved in `0x00ba8420` and its callees |
| duplicate/erase/concurrency | unresolved |

No null-`this` guard, lock, exception policy, or reentrancy guarantee is established.

## Caller-family matrix

The pinned TSV contains repeated callsites, so unique callers and direct-call edges are reported separately.

| family | address | unique callers | direct edges | relation |
|---|---:|---:|---:|---|
| GetData root | `0x00b21340` | 254 | 318 | noun-vector cache/materialization |
| lower-bound prerequisite | `0x00e5c780` | 239 | 265 | generic unsigned map traversal |
| insertion/default construction | `0x00ba8420` | 6 | 7 | noun-path mutation helper |
| current-player political bridge | `0x00b25fb0` | 100 | 193 | reaches GetData through `0x00b25f40` |
| culture creation bridge | `0x00bf9820` | 1 | 1 | contains `cCultureSet::PickCreation +0x20`; calls GetData, `0x00b25ca0`, and `0x00b25fb0` |
| empire/state bridge | `0x00ba0080` | 1 | 1 | calls GetData, `0x01021300`, and `0x00ba9370` |
| nearby noun accessor | `0x00b25ca0` | 31 | 36 | direct GetData consumer at `0x00b25cb9` |
| nearby noun accessor | `0x00b25f40` | 64 | 80 | direct GetData consumer at `0x00b25f5d`; SDK `GetPlayerCivilization` tail alias at `0x00b25f90` |
| nearby noun accessor | `0x00b25fe0` | 5 | 5 | calls GetData at `0x00b260d3` and `0x00b261b2` |

`0x00b21340` caller triage: 50 gameplay functions (`30 GAMEPLAY_LOGIC`, `20 GAMEPLAY_SUPPORT`), 41 engine implementation, two engine interface, and 161 unknown. By subsystem: 49 Simulator, four UTFWin, one each UI/IO/Math, and 198 unknown.

### Shared direct caller sets

Functions that directly call both GetData and `0x00b25fb0` (12):

```text
00aee830 00bf9820 00bfa660 00bfbbf0 00bff2d0 00cf44c0
00cfb890 00cfbc10 00cfee00 00dcedb0 00fe0160 00ff9100
```

- `0x00bfbbf0` is the sole function that directly calls both GetData and `0x00bf9820`; it also calls `0x00b25fb0`. It is the central shared consumer.
- `0x00ba0080` itself calls GetData, but its sole parent `0x00ba1ce0` does not; therefore the GetData/`0x00ba0080` shared-parent set is empty.
- `0x00bf9820` is called by `0x00bfbbf0` and directly calls GetData, `0x00b25ca0`, and `0x00b25fb0`.
- `0x00ba0080` directly calls GetData, the current-empire accessor `0x01021300`, and the empire map lookup `0x00ba9370`.

Functions that directly call both GetData and the lower-bound helper (4):

```text
00cc6910 00cfbc10 00ff9800 01058c90
```

Functions that directly call both the lower-bound helper and `0x00ba8420` (2):

```text
00b21340 00b2ede0
```

## Contradictions resolved or retained

1. **Message-handler label superseded.** The older dossier says “message-handler registration” (`docs/analysis/dossiers/unknown-high/message-handler-registration.json:25-29`); SDK callback and field types identify noun-vector materialization.
2. **Partial vector layout superseded.** The full SDK structure is `0x18`, not only the first four observed fields.
3. **Unknown noun node resolved.** `mNouns` embeds links in `cGameData +0x0c/+0x10`.
4. **“Name buffer” decompilation alias rejected.** The typed return is a noun vector; the cleared byte is `needsUpdate`, not a name string.
5. **GetData address mismatch retained.** Method identity at `0x00b21340` is high-confidence; exact SDK address identity at `0x00b212d0` is low-confidence.
6. **Insertion helper remains partial.** `0x00ba8420` is strongly indicated to mutate/insert map state, but its exact template and failure contract are not closed.
7. **Fan-in units distinguished.** Triage’s 254/239 values are unique caller functions; the xref TSV has 318/265 direct-call edges.

## Next static experiments

1. Adjudicate `0x00b212d0..0x00b21410` as a possible split GetData region in a scratch analysis view; preserve historical artifacts unchanged.
2. Produce a corrected-signature decompilation of `0x00b21340` with typed manager, vector, callbacks, and iterator objects.
3. Decompile `0x00ba8420`, `0x00ba83a0`, and `0x009215c0` together and compare with other `map<uint32_t,...>` helpers.
4. Trace `needsUpdate` and `mNouns` writes from repaired `CreateInstance` and `DestroyInstance` regions.
5. Bind concrete callback thunks from `0x00acd9a0..0x00ad49e0` and shared consumer `0x00bfbbf0`.
6. Decompile the bounded bridge samples `0x00b25f40`, `0x00b25fe0`, `0x00bf9820`, `0x00ba0080`, and `0x00bfbbf0`.

## Primary evidence

- `.spore-analysis/ghidra-exports/spore_sdk.xml:23358-23484`
- `.spore-analysis/ghidra-exports/structs_fields.tsv:10574-10624`
- `.spore-analysis/ghidra-exports/functions.tsv:23618-23619,25284,33442`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cGameNounManager__GetData.c:1-57`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cGameNounManager__Get.c:1-13`
- `knowledgegraph/triage/xrefs-2540f2ca.tsv` — snapshot `2540f2ca`
- `knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json:366-440,1348-1462`
- `knowledgegraph/triage/sdk-boundary-repairs-2540f2ca.json:23517-23539,24873-24899`
- `docs/analysis/dossiers/unknown-high/message-handler-registration.json:25-29`
