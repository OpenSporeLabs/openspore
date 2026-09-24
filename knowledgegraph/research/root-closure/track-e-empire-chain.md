# Track E — political ID → game data → registry/cache → `cEmpire`

## Scope

Static-only closure for `0x01021300`, `0x00ba9370`, and `0x00b25fb0` in `SporeApp.exe` 3.1.0.22. No runtime, source, `SPORE/`, historical artifact, or Phase-0 interface was modified.

| item | value |
|---|---|
| binary SHA-256 | `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e` |
| analysis snapshot | `f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b` |
| canonical xrefs | `knowledgegraph/triage/xrefs-2540f2ca.tsv` (`2540f2ca…`) |
| SDK | Spore-ModAPI `cbf9206…`, `SporeGhidra_march2017.xml` |
| root fan-in | `01021300`: 182/47 gameplay; `00ba9370`: 136/35; `00b25fb0`: 100/36 |

## Resolved chain

```text
Simulator::sSpacePlayerData (0x016dda8c)
  ├─ mPlayerEmpireID +0x18 : uint32_t
  └─ mpPlayerEmpire   +0x1c : intrusive_ptr<cEmpire> cache
          │
          ▼
01021300 current-player cEmpire cache
  ├─ hit: cache != null && cache->mPoliticalID(+0x84) == id
  ├─ miss: 00b3d2a0 → registry context
  │         00ba9370(context, id)
  │         cStarManager-compatible mEmpires +0x150
  └─ return borrowed cEmpire*
          │
          ▼
00b25fb0 current-player game-data bridge
  ├─ empire = 01021300()
  ├─ empire == null → return caller stack fallback
  └─ id = empire->mPoliticalID(+0x84)
          │
          ▼
00b25f40 cGameNounManager-layout context, id
  ├─ 00b21340(..., nounID=0x018c816a = kCivilization)
  ├─ scan intrusive_ptr<cGameData> vector
  ├─ cGameData::GetPoliticalID at primary vtable+0x4c
  └─ first mPoliticalID(+0x30) == id, else null
```

The base ABI is `cGameData*`. The resolved registry subtype is `cCivilization*` with high confidence; the caller fallback remains type-open.

## Decisive corrections to the baseline

1. **`00ba9370` is not exact-find.** `00e5c780` is unsigned lower-bound, and `00ba9370` never compares the returned node key with the request.
2. **Missing non-sentinel IDs may return a successor.** If ID `x` is absent and key `y > x` exists, the wrapper returns the empire at `y`.
3. **`01021300` can cache that successor.** It does not reject the returned `cEmpire+0x84` during the refresh call. Later calls still fail the equality check and repeat the lookup.
4. **The old cache call is `Release`, not destruction.** New pointer: primary vtable `+0x00` `AddRef`; old pointer: primary vtable `+0x04` `Release`.
5. **`00b25fb0` has an exact fallback path.** It returns the caller’s first stack word unchanged only when `01021300` returns null. A live empire with no matching civilization still returns null.
6. **Do not rename `00b25fb0` to `GetPlayerCivilization`.** The SDK symbol at `0x00b25f90` is a boundary-repaired, zero-xref tail inside `00b25f40`; `0x00b25fb0` is a separate function after padding.

## Exact root contracts

### `0x01021300` — validated current-player `cEmpire*` cache

No explicit arguments. It requires `Simulator::sSpacePlayerData != null`; it dereferences the global without a null guard.

| field/access | offset | semantics |
|---|---:|---|
| `Simulator::sSpacePlayerData` | absolute `0x016dda8c` | SDK-imported `SpacePlayerData*` global |
| `SpacePlayerData.mPlayerEmpireID` | `+0x18` | `uint32_t`, requested political ID |
| `SpacePlayerData.mpPlayerEmpire` | `+0x1c` | `intrusive_ptr<cEmpire>`, one cache-owned reference |
| `cEmpire.mPoliticalID` | `+0x84` | SDK `int`, compared as raw 32-bit value |
| `ISimulatorSerializable::AddRef` | vtable `+0x00` | called on new pointer before store |
| `ISimulatorSerializable::Release` | vtable `+0x04` | called on old pointer after store |

Exact replacement order:

1. Read `id = mPlayerEmpireID`.
2. If `id == 0xffffffff`, return null **without clearing, replacing, AddRefing, or Releasing the old cache**.
3. If cache is non-null and `cache->mPoliticalID == id`, return it without AddRef.
4. Otherwise call `00b3d2a0`, then `00ba9370(context, id)`.
5. If `new != old` and `new != null`, AddRef new.
6. Store new in `mpPlayerEmpire`.
7. If old is non-null, Release old.
8. Return the cache.

`new == old` performs neither reference call. A null lookup with a live old cache stores null and Releases old once.

The validation is identity-only: no registry membership, generation, lifetime, or version check exists. A removed empire can remain valid to this cache if its `mPoliticalID` still equals the stored ID.

**Confidence:** mechanics `0.99`, identity `0.96`.

### `0x00ba9370` — empire-registry ceiling lookup

Call shape: ECX registry context plus one caller-cleaned `uint32_t` stack ID; returns a raw borrowed `cEmpire*`.

| field | offset | role |
|---|---:|---|
| `cStarManager.mEmpires` | `+0x150` | `map<uint32_t,intrusive_ptr<cEmpire>>` |
| map `mCompare` | map `+0x00` / object `+0x150` | comparator slot |
| map anchor/end | map `+0x04` / object `+0x154` | end/tree anchor |
| map root through anchor | map `+0x0c` / object `+0x15c` | tree root |
| map size | map `+0x14` / object `+0x164` | not used here |
| map allocator | map `+0x18` / object `+0x168` | not used here |
| node key | node `+0x10` | unsigned lower-bound comparison |
| node payload | node `+0x14` | returned `cEmpire*` |

Missing-ID matrix:

| input | result |
|---|---|
| `0xffffffff` | null, before map lookup |
| exact key exists | that empire |
| key absent, greater key exists | first greater key’s empire |
| key absent, no greater key | null |

No AddRef/Release occurs. The map owns its intrusive pointer; callers receive a borrowed pointer.

Direct callers that require exact identity must compare `result->mPoliticalID(+0x84)` with the request or guarantee that the key exists.

The receiver is structurally `cStarManager`, but `01021300` obtains it from `00b3d2a0 -> DAT_0167eae4`; the SDK maps `cStarManager::Get` to `00b3d3a0 -> DAT_0167eb0c`. The exact accessor/global alias remains unresolved.

**Confidence:** mechanics `0.99`, layout `0.94`, named accessor identity `0.62`.

### `0x00b25fb0` — current empire to `kCivilization` bridge

Call shape: ECX `cGameNounManager`-layout context plus one caller-cleaned four-byte stack fallback.

```text
fallback = stack[entry+0x04]
empire = 01021300()
if empire == null:
    return fallback
return 00b25f40(context, empire->mPoliticalID)
```

`00b25f40`:

1. Calls `00b21340` with SDK-shaped callback arguments.
2. Uses noun key `0x018c816a`, exactly `GameNounIDs::kCivilization`.
3. Reads `tGameDataVectorT<cGameData>.begin +0x04` and `.end +0x08`.
4. For each intrusive pointer, calls primary vtable `+0x4c`, exactly `cGameData::GetPoliticalID`.
5. Returns the first pointer whose political ID equals `cEmpire+0x84`; otherwise null.

SDK callback slots:

| role | address | identity |
|---|---:|---|
| create | `0x00b21080` | unresolved |
| clear | `0x00d3d420` | unresolved |
| add | `0x00b236c0` | unresolved |
| filter | `0x00b1e500` | unresolved |
| noun ID | `0x018c816a` | `GameNounIDs::kCivilization` |

No AddRef/Release occurs. The noun vector owns the returned intrusive pointer.

Fallback constraints:

- Used only when `01021300` returns null.
- Not used when a current empire exists but no civilization matches.
- Returned without validation or reference transfer.
- Exact type is unresolved, but callers must supply a `cCivilization`-compatible pointer.

**Confidence:** mechanics `0.98`, base `cGameData*` `0.97`, resolved dynamic subtype `cCivilization*` `0.93`, exact SDK function name `0.35`.

## Relevant field maps

| structure | size | chain-relevant fields |
|---|---:|---|
| `SpacePlayerData` | `0x34` | `mPlayerEmpireID +0x18`; `mpPlayerEmpire +0x1c` |
| `cEmpire` | `0x158` | primary vtable `+0x00`; `mnRefCount +0x08`; `mPoliticalID +0x84` |
| `cGameData` | `0x34` | vtable `+0x00`; `mnRefCount +0x08`; `mID +0x24`; `mDefinitionID +0x28`; owner `+0x2c`; `mPoliticalID +0x30`; `GetPoliticalID` vtable `+0x4c` |
| `cCivilization` | `0x4d8` | inherits `cGameData` through `+0x30`; `mIsPlayerOwned +0x88` |
| `cGameNounManager` | `0x11c` | `mNouns +0x78`; `mNounMap +0x98`; internal map end `+0x9c` |
| `cStarManager` | `0x22c` | `mEmpires +0x150`; map end `+0x154` |
| `cCity` | `0x818` | `mpCivilization +0x590` |
| `tGameDataVectorT<cGameData>` | `0x18` | `needsUpdate +0x00`; begin `+0x04`; end `+0x08`; capacity `+0x0c` |

## Representative consumers

The canonical xref join shows `0x00aebe90` is the only direct caller that calls all three roots. Its representative callsites are `00b25fb0@00aec5bd`, `00ba9370@00aebf35/00aec128`, and `01021300@00aebf44/00aebf4e/00aebf70` plus later mission/color paths. It is a cross-layer shared-state user, not a narrow local accessor.

| consumer | root use | constraint/meaning |
|---|---|---|
| `0x00bf9820` `cCultureSet::PickCreation` | `00b25fb0@00bf985d` | null-checks and uses the result as current civilization in culture selection |
| `0x00bdde70` `cCity::SpawnVehicle` | `00b25fb0@00bde22f` | compares result with `cCity.mpCivilization +0x590`; strongest subtype evidence |
| `0x00d06270` `cRelationshipManager::ApplyRelationship` | `00b25fb0@00d06298` | rejects null; then uses only `cGameData::GetPoliticalID` |
| `0x00d01ff0` `cRelationshipManager::IsAllied2` | `01021300@00d01ff3` | defaulted-empire source; reads `cEmpire+0x84` for relationship lookup |
| `0x00c32cd0` identity-color picker | `01021300@00c32d19/34`; `00ba9370@00c3310f` | current-empire exclusion plus registry iteration for color choice |
| `0x00febce0` `cMissionManager::GetMissionTrackColor` | `01021300@00febd0b` | current-empire pointer constrains mission-track color validation |
| `0x00feb770` `cMissionManager::Get` | `00ba9370@00feb951`; `01021300@00feb980` | shared mission-side registry/cache user |
| `0x0102df20` high-fan-out Simulator orchestrator | multiple `00ba9370` and `01021300` calls | makes exact-vs-ceiling and cache lifetime shared-state-critical; individual semantics unresolved |

Arbitrary top-address callers were not used to infer semantics.

## Ownership summary

- `mEmpires` owns its `intrusive_ptr<cEmpire>`; `00ba9370` returns a borrowed pointer.
- `SpacePlayerData.mpPlayerEmpire` owns one reference; `01021300` adds the new reference before store and releases the old after store.
- `01021300` returns a borrowed pointer on a cache hit.
- The `kCivilization` vector owns its game-data intrusive pointers; `00b25f40`/`00b25fb0` return borrowed pointers.
- No root increments a reference merely for a caller. Consumers retaining a pointer must AddRef explicitly.

## Remaining ambiguities and static next actions

1. **Registry accessor aliases:** trace writers/lifecycle for `DAT_0167eae4` versus `DAT_0167eb0c`.
2. **Noun-manager accessor source:** trace `DAT_0167eae0` versus `DAT_0167eb60`; representative bridge callers use `00b3d300`, while the SDK maps `cGameNounManager::Get` to `00b3d400`.
3. **Fallback ABI:** recover full call frames for `00b25fb0` in culture, city, diplomacy, and `00aebe90` before freezing a replacement interface.
4. **Materialization callbacks:** characterize `00b21080`, `00d3d420`, `00b236c0`, `00b1e500`, and `00ba8420`.
5. **Stale-cache lifecycle:** audit mEmpires erasure/rekey sites against identity-only cache validation; document the risk rather than silently adding invalidation.
6. **Runtime:** none authorized or performed. Registry teardown, rekeying, and destruction ordering remain unknown.

## Evidence

- `docs/analysis/simulator-shared-state-interface.md:143-201,203-224,253-270`
- `knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json:1465-1759`
- `knowledgegraph/triage/xrefs-2540f2ca.tsv`
- `knowledgegraph/triage/reconstruction-readiness-f0e310e0.json`
- `knowledgegraph/triage/unknown-high-investigation-f0e310e0.json`
- `knowledgegraph/triage/sdk-boundary-repairs-2540f2ca.tsv:873`
- `.spore-analysis/ghidra-exports/structs_fields.tsv`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cRelationshipManager__IsAllied2.c`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cMissionManager__GetMissionTrackColor.c`
- SDK XML: `cGameData` lines 12841-12956, `ISimulatorSerializable` lines 1929-1946, `cGameNounManager` lines 23366-23484, `cEmpire` lines 24618-24653, `cStarManager` lines 24874-24929, `SpacePlayerData` lines 25359-25384, `cCivilization` lines 27427-27529
- Read-only static instruction verification in the pinned binary at `01021300`, `00ba9370`, `00e5c780`, `00b25f40`, `00b25fb0`, and `00b21340`
