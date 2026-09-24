# Track C — cStarManager and star publication

## Scope and evidence boundary

This is a static-only investigation of the pinned live binary `SporeApp.exe` 3.1.0.22, SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`, `x86:LE:32:windows`, image base `0x00400000`. The Ghidra program was queried read-only. No runtime execution, Wine, source implementation, original-executable modification, `SPORE/` access, shared-artifact modification, or modification of another worker report was performed. The only file created by this track is this report.

The question is narrow: how stars and their record/planet data are created, registered, found, materialized, linked to empires, invalidated, re-generated, torn down, and whether a star owns or only references the noun-like records involved.

Evidence precedence is:

- live Ghidra disassembly, decompilation, xrefs, and imported layouts;
- the March 2017 SDK for semantic names, intended contracts, and canonical addresses;
- existing OpenSpore architecture and knowledge-graph reports as bounded context, not as independent proof of unresolved mechanics.

SDK addresses are not automatically current function entries in this binary. When the SDK anchor and live Ghidra body differ, both are identified.

## Executive conclusion

1. **A star is not one homogeneous object.** The model contains a live `cStar` game-data noun, a separate refcounted/serializable `cStarRecord`, live `cSolarSystem`/`cPlanet` objects, and separate `cPlanetRecord` values. The types have distinct sizes, vtables, fields, and lifetimes.
2. **`cStarManager` is a registry and cache owner, not the sole owner of star identity.** It owns intrusive references to `cStarRecord` values in several vectors/maps and owns a live-planet cache vector. `cEmpire` separately owns references to `cStarRecord` values. A live `cStar` separately points to its `cStarRecord` and `cSolarSystem`.
3. **Star-record publication is closed inside the manager’s record registries.** `FUN_00bb5d80` constructs a `cStarRecord`, assigns a sector/slot `StarID`, and appends it to `mStarRecordGrid`; starter, saved, possible-start, and black-hole collections are separate reference-bearing publication surfaces.
4. **Star-root publication is not closed.** The alternate accessor `0x00b3d2a0` returns `DAT_0167eae4`; the canonical `cStarManager::Get` at `0x00b3d3a0` returns `DAT_0167eb0c`. Both words are physically distinct, but focused xrefs show only reads/accessor paths and no direct store, replacement, clear, equality test, or destructor-to-root-unpublication join.
5. **Planet materialization is a second lifecycle.** A `cStarRecord` owns/holds `cPlanetRecord` references. `cSolarSystem::Load` and `cStarManager::RecordToPlanet` convert or reuse those records as live `cPlanet` objects, which are retained by the manager’s live-planet vector and by the solar-system planet vector. The same `cPlanetRecord` pointer is the cache identity used to reuse a live planet.
6. **Empire linkage is bidirectional but split across owners.** `cEmpire::mStars` holds `cStarRecord` references; `cStarManager::mEmpireHomeStarRecords` maps an empire political ID to a home-star record; `cEmpire` also stores `mHomeStar` and `mHomePlanet`. Replacing the home-star map entry does not by itself erase a record from the grid, the empire star vector, or the saved/starter vectors.
7. **Regeneration is record reuse, not a new star allocation.** `FUN_00bb4af0` tests a record’s planet count, updates observation time, removes the record from a pending list, resets state, and calls the live `FUN_00bb4100` generation body. The record identity/key remains the stable object being regenerated.
8. **Teardown is manager-internal and layered.** `FUN_00bb6390` clears the manager’s live-planet, star-record, empire, home-map, and candidate collections; `FUN_00bb7250` unregisters the star-generation callback and releases manager-owned fields. This still does not prove that either global root is cleared.

The smallest safe model is:

```text
cStarManager
  owns references to cStarRecord values in grid/starter/saved/possible/black-hole collections
  owns a live cPlanet cache
  owns cEmpire references
  owns/replaces empire-home -> cStarRecord map entries

cStarRecord
  owns/holds cPlanetRecord references
  carries StarID, position, type, empire/state fields, and generation metadata

cStar (live noun)
  references cStarRecord
  references cSolarSystem

cSolarSystem
  references cStar as owner
  owns/holds live cPlanet objects

cPlanet (live noun)
  references cPlanetRecord
  is cached by cStarManager and collected by cSolarSystem

cEmpire
  owns/holds cStarRecord references
  stores political ID, home-star ID, and home-planet ID
```

A compatible implementation must not collapse `cStar*`, `cStarRecord*`, `cPlanet*`, `cPlanetRecord*`, `cEmpire*`, and the manager-root pointers into one generic noun ownership rule.

## Evidence authority and address correction

The SDK and live-binary mapping used in this report is:

| SDK semantic anchor | live Ghidra body | note |
|---|---:|---|
| `cStarManager::StarGenerationMessageHandler` `0x00BB5F00` | `FUN_00bb5d80` at `0x00BB5D80` | live function begins before SDK anchor; callback is registered indirectly |
| `GeneratePlanetsForStar` `0x00BB42A0` | `FUN_00bb4100` at `0x00BB4100` | current live body is offset from SDK anchor |
| `RequirePlanetsForStar` `0x00BB4C90` | `FUN_00bb4ba0` at `0x00BB4BA0` | current live body is offset from SDK anchor |
| `cSolarSystem::Load` `0x00C868F0` | `FUN_00c86760` at `0x00C86760` | current live body is offset from SDK anchor |
| `cStarManager::RecordToPlanet` `0x00BB5B50` | `Simulator::cStarManager::RecordToPlanet` at `0x00BB5B50` | wrapper delegates to `FUN_00bb1560` |
| `cStarManager::Get` `0x00B3D3A0` | `Simulator::cStarManager::Get` at `0x00B3D3A0` | returns canonical root word |

The live bodies, not the stale/offset SDK addresses alone, are used for mechanics. The SDK documentation used for intent includes:

- `Spore ModAPI/Spore/Simulator/SubSystem/StarManager.h:102-121` for saved star records, the 64×64 grid, generation messages, and post-generation record policy;
- `Spore ModAPI/Spore/Simulator/cStarRecord.h:51-65,85-89` for serialized record semantics and lazy planet data;
- `Spore ModAPI/Spore/Simulator/cStar.h:29-42` for live `cStar` and `cSolarSystem` association;
- `Spore ModAPI/Spore/Simulator/cPlanet.h:41-44` for the distinction between live visual planets and records;
- `Spore ModAPI/Spore/Simulator/cSolarSystem.h:33-38` for system ownership and celestial bodies;
- `Spore ModAPI/Spore/Simulator/cEmpire.h:61-85` for empire home-star, ownership, and capture operations;
- `Spore ModAPI/SourceCode/Simulator/StarManager.cpp:29-60` for canonical lookup intent;
- `Spore ModAPI/SourceCode/AddressesSimulator.cpp:623-636` for canonical address anchors.

The existing repository reports consistently retain the distinction between live noun objects, star records, planets, empires, and root pointers: `knowledgegraph/research/noun-star-lifecycle/track-d-identity-ownership.md:84-114,340-345`, `knowledgegraph/research/architecture-resolution/track-02-star.md`, `knowledgegraph/research/root-closure/followup-global-slots.md`, and `knowledgegraph/research/architecture-resolution/followup-03-root-publication.md`.

## Structures and ownership

### `cStarManager` — size `0x22c`

The live Ghidra layout is:

| offset | field / observed role | lifetime or ownership |
|---:|---|---|
| `+0x20` | message/map state | manager-owned |
| `+0x50..+0x5c` | `vector<intrusive_ptr<cPlanet>>` | manager-owned live-planet cache |
| `+0xa0..+0xb4` | `mAvailableStarterWorlds` and related candidate storage | manager-owned references/values |
| `+0xc8..+0xdc` | `mStarRecordGrid` | nested vectors of `intrusive_ptr<cStarRecord>` |
| `+0xdc..+0xf0` | `mStarterStarRecords` | manager-owned record references |
| `+0xf0..+0x104` | `mSavedGameStarRecords` | manager-owned record references |
| `+0x104..+0x118` | `mBlackHoles` | manager-owned record references |
| `+0x118..+0x12c` | `mPossibleStartLocations` | manager-owned record references |
| `+0x12c..+0x148` | `mEmpireHomeStarRecords` | map from empire political ID to record reference |
| `+0x148` | `mSol` | manager-owned `cStarRecord` reference |
| `+0x14c` | `mpTempStar` | manager-owned temporary `cStarRecord` reference |
| `+0x150..+0x16c` | `mEmpires` | map owning `cEmpire` references |
| `+0x1d4` | `mNextPoliticalID` | allocator/counter, not a star key |
| `+0x1d8` | `mGrobID` | political/grob ID state |
| `+0x1dc` | `mpScenarioStar` | manager-owned scenario-star reference |
| `+0x204` | `mpRelationshipManager` | manager-owned relationship service |

The grid is not a flat `StarID -> pointer` map. It is a 64×64 sector grid. The live generation path computes a sector and local slot; the key construction in `FUN_00bb5d80` is:

```text
StarID = (sectorY * 64 + sectorX) * 0x1000 + localRecordSlot
```

The live lookup path in `FUN_00bb5640` uses the complementary decomposition:

```text
sector = StarID >> 0x0c
slot   = StarID & 0x0fff
```

This is a registry key and address decomposition, not a durable object pointer. The 64×64 and `0x1000` limits are part of the observed layout and key encoding.

### `cStarRecord` — size `0xb0`

The imported/current layout is:

| offset | field | role |
|---:|---|---|
| `+0x00` | serializable vtable | record interface |
| `+0x04/+0x08` | refcounted vtable and count | refcounted lifetime |
| `+0x0c` | `mLastObservedTime` | regeneration/observation state |
| `+0x10..+0x24` | saved-game version fields | serialized metadata candidates |
| `+0x24..+0x38` | save timestamp | serialized metadata candidate |
| `+0x3c` | `mPosition` | star position |
| `+0x48` | `mType` | star type |
| `+0x4c` | `mTechLevel` | star state |
| `+0x54` | `mEmpireID` | political/empire association field |
| `+0x58` | `mStarterWorldID` | starter-world metadata |
| `+0x5c` | `mFlags` | generation/state flags |
| `+0x60` | `mName` | name value |
| `+0x70` | `mKey` | `StarID` domain key |
| `+0x74..+0x80` | citizen/species key data | species/profile association |
| `+0x80` | `mpSpeciesProfile` | profile pointer |
| `+0x84` | `mPlanets` | vector of `cPlanetRecord` references |
| `+0x98` | second record vector | generated/alternate planet-record storage; exact semantic name unresolved |
| `+0xac` | `mPlanetCount` | byte-sized generation/count state |

`FUN_00bba130` constructs a zero/empty `cStarRecord`, installs both vtables, initializes the two vectors, and defaults `mEmpireID` at `+0x54` to `-1`. The constructor does not create a live `cStar`, `cSolarSystem`, or `cPlanet`; it creates the separate serializable/refcounted record representation.

### `cStar` — size `0x50`

The live noun representation is distinct:

| offset | field / role |
|---:|---|
| `+0x00..+0x08` | game-data/refcount vtables and count |
| `+0x0c/+0x10` | intrusive list links |
| `+0x24` | `mID` |
| `+0x28` | `mDefinitionID` |
| `+0x30` | `mPoliticalID` |
| `+0x40` | `mpSolarSystem` |
| `+0x48` | `mpStarRecord` |
| `+0x4c` | `mKey` |

A `cStar` is therefore a live `cGameData`-derived noun with references to both the visual/system object and the separate record. It is not the same allocation or type as `cStarRecord`.

### `cSolarSystem` and `cPlanet`

`cSolarSystem` is `0x54` bytes in the current layout:

| offset | field / role |
|---:|---|
| `+0x0c` | `mpOwnerStar` |
| `+0x10` | `mPlanets` |
| `+0x24` | `mCelestialBodies` |
| `+0x38/+0x3c` | star/celestial-body references |

`cPlanet` is `0x1c8` bytes. Its important record link is:

```text
cPlanet +0x13c -> cPlanetRecord*
```

The live planet also carries visual/game-data state, orbit data, model references, political identity, and other runtime fields. The record link is the identity used to reuse a previously materialized planet; it does not make the visual `cPlanet` and serialized `cPlanetRecord` the same object.

### `cEmpire` — size `0x158`

The relevant fields are:

| offset | field / role |
|---:|---|
| `+0x84` | `mPoliticalID` |
| `+0x88` | `mStars` vector of `cStarRecord` references |
| `+0x9c` | `mNextStarTowardsHome` vector |
| `+0xb0` | `mHomeStar` `StarID` |
| `+0xb4` | `mHomePlanet` `PlanetID` |

`FUN_00baf0b0` constructs an `0x158` `cEmpire`, writes the requested political ID to `+0x84`, upserts the manager’s empire map, AddRefs the new empire, stores it, and Releases the old equal-key payload. The map owns the empire reference; callers that read an empire from the map receive a borrowed pointer unless they retain it separately.

## Recovered lifecycle

## 1. Manager construction — `FUN_00bae490`

`FUN_00bae490` constructs a passed `cStarManager` receiver. It initializes the vtables, intrusive/map anchors, vectors, relationship fields, planet database pointers, and ID state. The constructor initializes `mNextPoliticalID` at `+0x1d4` to `0x1234` and `mGrobID` at `+0x1d8` to `-1`.

This is strong evidence for manager-local initialization, but it is not evidence that either global root word is written. The constructor returns the same receiver passed by the caller.

## 2. Star-record construction — `FUN_00bba130` and `FUN_00bae6f0`

### Normal generated record

`FUN_00bb5d80` is the star-generation callback for generated star records. It allocates `0xb0` bytes tagged `Simulator/cStarRecord`, invokes `FUN_00bba130`, and then populates the record through star-generation helpers. The direct sequence includes:

- position/sector calculation through the live star-position helpers;
- star type and star state initialization;
- species/name/profile setup;
- planet generation;
- `mKey` assignment using the sector/slot formula above;
- append to the sector’s `mStarRecordGrid` vector;
- conditional append to `mBlackHoles` when the generated star is a black hole.

The callback is not normally reached by a direct call from the manager body. `FUN_00bb6a30` passes `FUN_00bb5d80` as a callback for ten message IDs, and `FUN_00bb7250` passes the same function to the corresponding teardown/unregister sequence. This is callback registration, separate from global manager-root publication.

### Temporary record

`FUN_00bae6f0` allocates a second `cStarRecord` for `cStarManager::mpTempStar` at `+0x14c` when no temporary record exists. It sets a fixed/synthetic position, sets `mType` to `5`, sets `mKey` to `0`, creates one planet record, increments the record’s planet-count byte, and stores the result in `mpTempStar`. The temporary record is not inserted into the 64×64 grid by this body.

`FUN_00bb5640` explicitly treats `StarID == 0` as the temporary-record case when resolving a record. `StarID == 0xffffffff` is an early-return boundary in the same cleanup path.

### Sol system path

SDK `GenerateSolSystem` is documented as selecting/modifying an existing closest star rather than creating a new star. The live `FUN_00bb2a50` path calls the closest-star search, stores/uses the selected record as `mSol` at `+0x148`, and performs system/planet generation work. The absence of a normal `cStarRecord` allocation in that path supports the SDK distinction between selecting a record and creating a new one.

## 3. Grid publication and lookup

### Publication

The key path in `FUN_00bb5d80` is:

```text
sector = position -> 64x64 sector coordinates
slot   = current length of the sector record vector
key    = (sectorY * 64 + sectorX) * 0x1000 + slot
record.mKey = key
mStarRecordGrid[sectorX, sectorY].push_back(record)
```

The vector element is an intrusive reference. The record is not copied by value into the grid.

The same record may then be selected for other manager collections. `mStarterStarRecords`, `mSavedGameStarRecords`, `mPossibleStartLocations`, and `mBlackHoles` are not aliases of the grid vector; they are independent manager-owned reference collections with different lifecycle and selection rules.

### Lookup

`FUN_00bb5640` resolves a record from an encoded ID:

- `0` selects `mpTempStar`;
- `0xffffffff` returns without cleanup;
- other IDs are decomposed into sector and local slot and indexed into the nested grid;
- the resolved record is used by the cleanup/regeneration path.

`FUN_00bb9950` is a separate starter-record selection path. If no scenario/grid state is ready, it calls `FUN_00bb8b20` to load/bootstrap the manager and then `FUN_00bb6040` to refresh candidate records. It returns a record from `mStarterStarRecords` after bounded retry/selection logic. It does not allocate a new star record in the visible path.

## 4. Starter, saved, and possible-start publication

`FUN_00bb6040` is the main candidate/starter refresh path. It uses the manager fields at `+0xdc`, `+0xf0`, and `+0x118`, checks the available planet-record database, and fills starter/possible candidate collections. It calls record-generation helpers, filters candidates, and adds selected records to the manager-owned starter collection. The exact semantic split among `mAvailableStarterWorlds`, `mStarterStarRecords`, and `mPossibleStartLocations` is partially SDK-supported and partially bounded by decompilation.

The important ownership result is direct: selected `cStarRecord` values are stored as intrusive references in these collections. Candidate selection does not transfer the record’s identity to a raw pointer-only index, and it does not establish a one-to-one relationship with a live `cStar`.

## 5. Empire linkage and home-star replacement

### Empire record vector

`FUN_00c34ee0` directly scans `cEmpire::mStars` at `+0x88..+0x8c`, compares intrusive elements to the target `cStarRecord`, and removes/releases the matching element. This proves that the empire owns or holds a separate reference to the star record.

The same body updates empire state and, when the removed record is the home system, walks related records, calls `FUN_00bb4af0` for regeneration, updates `mHomeStar`/`mHomePlanet`, and calls the manager home-map setter/clearer. These operations are separate phases: removing an empire star-vector element is not the same operation as clearing `mEmpireHomeStarRecords`.

### Home-star map

`FUN_00baf630` operates on `cStarManager::mEmpireHomeStarRecords` at `+0x12c` (map anchor at `+0x130`). The live disassembly:

- lower-bounds the map using the supplied empire/political ID;
- clears a bit on the previous record when the map entry changes;
- if the new record is non-null, sets a corresponding bit, retains the new record, and replaces the map payload;
- Releases the previous payload;
- if the new record is null, removes the map entry.

The helper is called from star-manager/empire paths including:

- `FUN_00bb2610`, where a newly allocated political ID is paired with a selected star record;
- `FUN_00c30c10`, where an empire’s `mHomeStar` is set to a record key;
- `FUN_00c316c0`, where `mHomePlanet` and `mHomeStar` are set together;
- `FUN_00c35810` and `FUN_00c34ee0`, where the home map is cleared or reassigned during removal/ownership changes.

This is a manager cache/index keyed by political ID. It is not proof that the record exists only there. A record can simultaneously be referenced by the grid, a starter/saved collection, an empire star vector, and the home-star map.

### Home-star fields

`FUN_00c30c10` writes the selected `cStarRecord::mKey` to `cEmpire::mHomeStar` at `+0xb0` and updates the manager home-star map. `FUN_00c316c0` writes the planet identity to `cEmpire::mHomePlanet` at `+0xb4` and updates `mHomeStar` from the record returned by `FUN_00b8de30`. The inverse paths set both fields to `-1` and pass a null record to `FUN_00baf630` when the home association is removed.

The record’s `mEmpireID` field at `+0x54` is part of the record layout, but the map/vector operations above are already sufficient to prove empire linkage without treating that field as the sole ownership authority. The exact write coverage and semantic relationship between `mEmpireID`, `cEmpire::mStars`, and `mEmpireHomeStarRecords` are not fully closed by the focused static pass.

## 6. Planet-record generation

`FUN_00bb4100` is the live `GeneratePlanetsForStar` body. It works through the `cStarRecord` generation helpers, the `mPlanets`/secondary record vectors, species/profile data, and the record’s planet-count state. The SDK method intent and the current live body agree that this is a record-generation phase, not a second allocation of the star identity.

`FUN_00bb4ba0` is the live `RequirePlanetsForStar`/persistence-adjacent path. It:

- checks the manager’s generation/availability state;
- initializes planet scripts and generation state;
- updates record timestamps and save metadata;
- removes a record from a pending list when required;
- opens a temporary star/planet database stream;
- writes star/planet data through the database and serializer helpers;
- replaces `stars.db.tmp` with `stars.db`.

This is database/materialization work attached to the record. It does not prove that raw `cPlanet*`, `cSolarSystem*`, manager vectors, or root pointers are serialized.

## 7. Record-to-planet lookup and live materialization

### `cStarManager::RecordToPlanet`

The current wrapper at `0x00bb5b50` is:

```text
RecordToPlanet(manager, cPlanetRecord* record, intrusive_ptr<cPlanet>* dst)
  -> delegate with a helper context at manager+0x16c
  -> FUN_00bb1560
```

`FUN_00bb1560` first searches the helper’s indexed record collection. If an existing runtime planet matches the record, it writes that planet into the output handle and returns a cache-hit indicator. If no match exists, it calls `FUN_00baf820` to materialize a planet and writes the newly obtained object into the output handle.

The result is a reference-managed output, but the wrapper’s exact temporary/output ownership is affected by Ghidra’s stack typing. The safe conclusion is bounded: `RecordToPlanet` is a record-to-live-planet bridge with cache-hit reuse and lazy materialization.

### `FUN_00bb59b0`

`FUN_00bb59b0` receives a manager and a record/record context. It:

1. resolves/normalizes the record and target planet record;
2. scans the manager’s live-planet vector at `+0x50..+0x5c`;
3. compares each live `cPlanet::mpPlanetRecord` at `+0x13c` with the requested `cPlanetRecord`;
4. reuses the matching live planet on a hit;
5. calls `FUN_00baf130` on a miss;
6. returns the live planet through the output handle.

This is the direct proof that `cPlanetRecord*` is the cache key for live-planet reuse.

### `FUN_00bb5b70`

`FUN_00bb5b70` iterates the `cStarRecord`’s planet-count state, obtains each generated planet record, and performs the same live-planet search/reuse decision. On a miss it calls `FUN_00baf130` with the manager/record context, appends the result to the caller’s output vector, and releases temporary references as needed.

`FUN_00baf130` creates/materializes a `cPlanet`, initializes it from the record context, and appends it to the manager’s live-planet vector at `+0x54`. The function is used as the common miss path, so the manager’s live-planet vector is a cache/owner surface rather than a transient-only local list.

## 8. `cSolarSystem::Load` — `FUN_00c86760`

The live `cSolarSystem::Load` body is especially strong because it combines the record and runtime layers:

1. writes the incoming `cStar*` to `cSolarSystem::mpOwnerStar` at `+0x0c`;
2. creates/loads the system’s celestial-body state;
3. obtains the star’s planet-record collection;
4. iterates each `cPlanetRecord`;
5. calls `FUN_00bb59b0` to obtain a matching or newly materialized `cPlanet`;
6. appends the result to `cSolarSystem::mPlanets` at `+0x10`;
7. performs planet-specific initialization and runtime flags afterward.

The direct ownership graph is therefore:

```text
cStar
  -> mpSolarSystem (cSolarSystem)
cSolarSystem
  -> mpOwnerStar (cStar)
  -> mPlanets (live cPlanet references)
cPlanet
  -> mpPlanetRecord (cPlanetRecord)
cStarRecord
  -> mPlanets/field_98 (cPlanetRecord references)
cStarManager
  -> live-planet cache (cPlanet references)
```

The reverse pointers and separate intrusive vectors are why record removal, live-planet invalidation, and system teardown must be modeled as distinct operations.

## 9. Regeneration and invalidation

### `FUN_00bb4af0`

The regeneration path is not a new star allocation. Its visible sequence is:

1. inspect the target `cStarRecord` and test whether its planet-count/generation state is empty;
2. compare/update `mLastObservedTime` or related observation state;
3. remove the record from a pending-generation list through `FUN_00bf3420`;
4. reset or invalidate the record’s generation state;
5. call live `FUN_00bb4100` (`GeneratePlanetsForStar`) on the same record;
6. leave the `cStarRecord` identity/key available for later grid and record lookups.

This is record-level regeneration. A new `cStarRecord` would require a separate allocation/grid-publication path; the observed regeneration path does not do that.

### `FUN_00bb5640`

`FUN_00bb5640` is the stronger invalidation/cleanup path. It:

- resolves a record from the temporary slot or grid key;
- returns for the invalid sentinel;
- updates record flags/observability state;
- removes the record from `mPossibleStartLocations` when present;
- invokes empire/planet/record cleanup helpers, including `FUN_00bad7a0` and `FUN_00c8c2a0` on the resolved state;
- removes the record from `mSavedGameStarRecords` and releases the vector element;
- calls the live require/regeneration path when necessary.

The exact semantic names of the two cleanup helpers are not fully recovered, but the collection-level erase and regeneration behavior are direct. The path does not prove that all star references disappear at one instant: the record can be removed from a saved/candidate collection while remaining reachable through another registry or an external reference until that owner releases it.

### Invalidation versus erase

The star path has the same architectural distinction as the noun path:

```text
record state/flag invalidation
  -> possible/saved/empire collection removal
  -> regeneration or re-materialization
  -> manager-wide vector/map teardown
```

There is no evidence for a single universal `erase(cStarID)` operation that simultaneously clears the grid, starter, saved, possible, black-hole, empire-home, empire-star, live-planet, solar-system, and root surfaces.

## 10. Manager teardown and callback removal

### `FUN_00bb6390`

The reset/teardown body clears or releases the manager’s local state, including:

- `mEmpires` nodes and empire payloads;
- the live-planet vector at `+0x50`;
- `mStarterStarRecords` at `+0xdc`;
- `mEmpireHomeStarRecords` at `+0x12c`;
- `mSavedGameStarRecords` at `+0xf0`;
- `mBlackHoles` at `+0x104`;
- `mPossibleStartLocations` at `+0x118`;
- other manager maps, trade-route state, and runtime fields.

The body uses the manager’s vector/map destructors and reference-release virtuals, then resets map anchors/end pointers. This proves manager-local ownership cleanup, including ownership of the star-record and live-planet references.

### `FUN_00bb7250`

The later shutdown path removes the star-generation callback registration for the corresponding message IDs, clears manager-specific runtime fields, releases remaining vector/map payloads, and tears down relationship/manager state. The callback argument is the same `FUN_00bb5d80` used by `FUN_00bb6a30`.

### Global-root boundary

Neither `FUN_00bb6390` nor `FUN_00bb7250` is joined by a direct store to `DAT_0167eae4` or `DAT_0167eb0c`. Manager-local teardown therefore does not establish global-root unpublication.

## Star root publication

### Accessors and physical slots

| accessor | live body | backing word | focused result |
|---|---:|---|---|
| alternate `cStarManager` accessor | `0x00b3d2a0` | `DAT_0167eae4` | two direct reads; many callers of the accessor |
| canonical `cStarManager::Get` | `0x00b3d3a0` | `DAT_0167eb0c` | one direct read; accessor body is `MOV EAX,[word]; RET` |

The two backing words are four-byte globals at different addresses. They are therefore not physically the same storage slot. The focused xref scan did not find a direct writer, replacement, clear, equality comparison, or null-to-live transition for either word.

`FUN_00b3d2a0` is a broad alternate-root accessor used by the current-player/space paths. `Simulator::cStarManager::Get` is a narrow canonical accessor with a much smaller direct consumer set. The difference is an unresolved service-root relationship, not evidence that either accessor is stale.

### What is closed

- A real `cStarManager` is constructed through a passed receiver at `FUN_00bae490`.
- The manager owns substantial star-record, empire, planet, and relationship state.
- A cStarManager-compatible object is used throughout the star-generation, world-loading, and empire paths.
- The alternate and canonical root words are physically distinct.

### What is not closed

- which construction path first populates each root word;
- whether the two words receive the same allocation;
- whether one word is published before the other;
- whether a root is phase-specific, stale, or rebound;
- whether shutdown clears either word;
- whether a root writer is hidden behind computed addressing, bulk copy, generic service registration, or an external initialization layer.

The strongest static candidate is the passed-receiver manager construction and parent/service registration path, but no direct join from that construction to either word was found. The root question must remain open in any compatibility model.

## Rekeying and replacement

### Star IDs

`cStarRecord::mKey` at `+0x70` is assigned during generated-record publication. The grid sector and local slot are recoverable from that key, and the temporary record uses key `0`. The live paths inspected do not show a normal rename/rekey operation that changes a generated record’s key while retaining all registry entries.

`cStar::mKey` at `+0x4c` is a separate live-object field. A matching value is an association/domain identity, not proof that the live star pointer and record pointer are identical.

### Political IDs and home-star replacement

`FUN_00bb2610` allocates a new political ID through `mNextPoliticalID` and pairs it with a selected star record in `mEmpireHomeStarRecords`. `FUN_00baf630` replaces the map payload with AddRef/store/Release semantics. `cEmpire::mHomeStar` and `mHomePlanet` are updated independently by the empire methods.

This is cache/index replacement, not star rekeying. The star’s `StarID`, grid slot, and record allocation remain separate from the empire political ID and home-map entry.

### Record replacement

Normal invalidation removes a record from selected candidate/saved collections and may regenerate the same record. Manager teardown releases collections wholesale. Neither path proves a transactional replacement of every registry at once. A caller must treat the record key, physical record pointer, and membership in each collection as separate facts.

## Ownership answer: does a star own the noun?

The safe answer is **no single owner relationship**.

- `cStar` is the live noun and holds intrusive references to `cStarRecord` and `cSolarSystem`.
- `cStarRecord` is a separate refcounted/serializable record and holds planet-record references.
- `cStarManager` owns references to record values in its registries and owns a live-planet cache.
- `cEmpire` owns references to `cStarRecord` values and stores home identities.
- `cSolarSystem` holds live planet references and points back to the owner star.
- `cPlanet` points to a `cPlanetRecord` and is independently retained by the manager/system caches.

Thus, star publication is primarily publication of a **record identity** into manager registries, followed by a separate **live-world materialization** path. A live star is not the only owner of a star record, and a record is not itself a live noun or visual system.

## Failure and edge semantics

| condition or edge | observed behavior | confidence |
|---|---|---|
| normal star generation callback | constructs a record, computes sector/slot key, appends to the grid | high |
| generated black hole | record is additionally appended to `mBlackHoles` | high for conditional path |
| key `0` | resolves to `mpTempStar` | high |
| key `0xffffffff` | invalidation path returns without normal record cleanup | high |
| starter list empty | `FUN_00bb9950` can bootstrap/load, refresh candidates, and return null if no candidate becomes available | high for visible control flow |
| planet-record miss | `FUN_00bb59b0`/`FUN_00bb5b70` call `FUN_00baf130` and cache a new live planet | high |
| planet-record hit | live planet is reused when `cPlanet+0x13c` matches | high |
| `RecordToPlanet` hit/miss | helper searches a record-indexed collection; miss calls `FUN_00baf820` | high for mechanics, medium for exact temporary ownership |
| home-star map replacement | AddRef new record, replace payload, Release old record | high |
| home-star map clear | null value removes the map entry and releases the prior payload | high |
| empire star removal | removes/releases the intrusive element from `cEmpire::mStars`; home-map update is a separate phase | high |
| regeneration with no planet records | resets/regenerates same record through `FUN_00bb4100` | high |
| candidate/saved cleanup | removes the selected vector reference and may regenerate; does not prove all registries are simultaneously empty | high bounded |
| manager reset | releases manager-owned vectors/maps and resets local state | high |
| global root teardown | no direct writer/clear found for either star root | unresolved |
| sector local-slot overflow | `StarID` reserves `0x1000` local-slot values per sector; generation is expected to stay within that domain, but an overflow guard was not recovered | medium |
| allocation failure | no complete rollback contract for every star/planet creation path | unresolved |
| reentrant callback/threading | no lock or reentrancy guard was established in the focused path | unresolved |

## Competing hypotheses

### H1 — `cStar` and `cStarRecord` are the same noun object

**Prediction:** one pointer/type/refcount, one destruction path, and direct field sharing.

**Evidence:** `cStar` is a `cGameData` noun with `mpStarRecord`; `cStarRecord` is `ISimulatorSerializable` and `DefaultRefCounted`, size `0xb0`, with separate `mPlanets` and save metadata. The constructors, vtables, and fields are distinct.

**Verdict:** **Rejected.**

### H2 — `cStarManager` is the sole owner of all star identity

**Prediction:** every record, live star, planet, and empire is reachable only through one manager field.

**Evidence against:** `cEmpire::mStars` independently holds `cStarRecord` references; `cStar` points to record and solar system; `cSolarSystem` points back to owner star; `cPlanet` points to `cPlanetRecord`; root slots are separate globals.

**Verdict:** **Rejected as a complete ownership claim.** The manager is a major registry/cache owner, not the sole domain owner.

### H3 — Generated star-record publication is a flat star-ID map

**Prediction:** one ordered map keyed by `StarID` stores all records.

**Evidence against:** `mStarRecordGrid` is a 64×64 nested vector; generation computes sector and local slot; cleanup decomposes the key with `>>12` and `&0x0fff`; other vectors are independent.

**Verdict:** **Rejected.**

### H4 — Star generation creates a new star every time a planet set is required

**Prediction:** `RequirePlanetsForStar` allocates a new `cStarRecord` and changes the grid key.

**Evidence against:** `FUN_00bb4af0` checks the existing record, removes it from a pending list, resets state, and calls the generation body; the record identity remains the lookup key.

**Verdict:** **Rejected for the observed regeneration path.**

### H5 — `cPlanetRecord` and `cPlanet` are interchangeable

**Prediction:** one pointer serves as both serialized and visual planet identity.

**Evidence against:** separate types/sizes; `cStarRecord` holds `cPlanetRecord`; `cPlanet` has visual/game-data state and points to a record at `+0x13c`; `RecordToPlanet` and `FUN_00bb59b0` explicitly bridge the two.

**Verdict:** **Rejected.**

### H6 — `mEmpireHomeStarRecords` is the authoritative empire/star ownership relation

**Prediction:** the map alone is sufficient to enumerate all empire stars and all references to a record.

**Evidence against:** `cEmpire::mStars` is a separate intrusive vector; the manager has grid/starter/saved/possible collections; the home map is keyed by political ID and only represents the home association.

**Verdict:** **Rejected.** The map is an indexed home association, not the complete ownership graph.

### H7 — Empire home replacement destroys the old star record

**Prediction:** replacing `mEmpireHomeStarRecords[empire]` immediately releases/frees the old record.

**Evidence against:** `FUN_00baf630` releases the map’s old reference, but the record can remain in the grid, empire vector, or other collections. The map operation is not joined to a universal record erase.

**Verdict:** **Rejected.**

### H8 — The alternate and canonical star roots are physically one slot

**Prediction:** the two globals would alias or a paired writer would be present.

**Evidence:** the words are at different addresses and the focused xrefs show reads only.

**Verdict:** **Rejected for physical aliasing; runtime value equality remains unresolved.**

### H9 — A direct root writer must exist and is simply missing from the current scan

**Prediction:** literal stores to one or both words should be discoverable in a static scan.

**Evidence against:** the focused xref/byte scans found no direct store or clear, while real manager construction and manager-internal teardown exist.

**Verdict:** **Plausible as a hidden computed/bulk/service publication path, not established.**

### H10 — Root publication is performed by `FUN_00bb6a30` or `FUN_00bb7250`

**Prediction:** those bodies directly write or clear `DAT_0167eae4`/`DAT_0167eb0c`.

**Evidence against:** their direct callback data xrefs point to `FUN_00bb5d80`; the bodies register/unregister message handlers and tear down manager state, but no direct root-word store is present.

**Verdict:** **Rejected as a direct writer claim; retained as a possible surrounding service-registration context.**

## Runtime requirement

Static analysis is sufficient for the manager-local record, grid, candidate, home-map, live-planet, solar-system, and manager-teardown mechanics. Runtime is required before claiming original root-publication compatibility.

The smallest decisive trace should observe:

1. `0x00bae490` manager construction and the passed receiver;
2. `0x00b3d2a0` and `0x00b3d3a0` root reads;
3. `0x00bb5d80` star-generation callback delivery;
4. `0x00baf630` home-map replacement/clear;
5. `0x00baf130` live-planet creation;
6. `0x00bb59b0` and `0x00bb5b50` planet reuse/materialization;
7. `0x00c86760` solar-system load;
8. `0x00bb5640` invalidation/cleanup;
9. `0x00bb4af0` regeneration;
10. `0x00bb6390` and `0x00bb7250` teardown.

At each event record:

- `DAT_0167eae4` and `DAT_0167eb0c` values and pointee vtables;
- the `cStarManager` pointer passed to construction and all manager fields at the offsets above;
- `cStarRecord*` address, `mKey`, `mEmpireID`, `mPlanetCount`, and refcount;
- grid sector/vector slot and all other record collections containing the same pointer;
- `cEmpire::mStars` membership, `mHomeStar`, `mHomePlanet`, and the home-map payload;
- `cStar*`, `mpStarRecord`, `mpSolarSystem`, `cSolarSystem::mPlanets`;
- `cPlanet*`, `mpPlanetRecord`, and the manager live-planet vector;
- callback registration/removal and the first/last reference counts for each object.

A pass condition is a synchronized publication/ownership matrix proving:

1. which root word(s), if any, receive the constructed manager;
2. whether the root values are equal, unequal, null, phase-specific, or rebound;
3. that one record can be simultaneously present in the expected registry collections;
4. that home-map replacement releases only the map reference;
5. that live planets are reused by `cPlanetRecord` pointer;
6. that regeneration preserves the record identity/key;
7. that teardown releases manager-owned references and whether either root is cleared.

## Final lifecycle classification

```text
CONSTRUCT MANAGER
  0x00bae490
  initializes manager-local maps/vectors/IDs
  does not directly publish either global root

CREATE GENERATED RECORD
  0x00bb5d80
  allocate 0xb0 cStarRecord
  initialize record state
  assign sector/slot StarID
  append intrusive reference to mStarRecordGrid
  optionally append to mBlackHoles

CREATE TEMP RECORD
  0x00bae6f0
  allocate/replace manager.mpTempStar
  set key 0
  do not insert into normal grid

LOOKUP
  grid sector/slot lookup or mpTempStar
  return record reference/path, not a durable pointer

MATERIALIZE PLANETS
  0x00bb4100 / 0x00bb4ba0
  generate/require cPlanetRecord data
  update/serialize star/planet database state

LINK EMPIRE
  cEmpire::mStars
  cStarManager::mEmpireHomeStarRecords
  cEmpire::mHomeStar/mHomePlanet
  independent intrusive/reference updates

MATERIALIZE LIVE PLANET
  0x00baf130 / 0x00baf820
  cPlanetRecord -> cPlanet
  cache/reuse by cPlanet+0x13c
  append to manager live-planet cache

LOAD SOLAR SYSTEM
  0x00c86760
  cStar -> cSolarSystem owner
  cStarRecord planet records -> live planets
  append live planets to cSolarSystem

REGENERATE
  0x00bb4af0
  reuse same cStarRecord
  reset pending/generation state
  call GeneratePlanetsForStar

INVALIDATE/CLEANUP
  0x00bb5640
  resolve record
  remove selected candidate/saved references
  invoke cleanup/regeneration
  do not claim universal registry erase

TEARDOWN
  0x00bb6390 / 0x00bb7250
  release manager-owned vectors/maps/records/planets
  unregister star-generation callback
  global root unpublication remains unresolved

ROOT PUBLICATION
  0x00b3d2a0 -> DAT_0167eae4
  0x00b3d3a0 -> DAT_0167eb0c
  physical slots distinct
  first write/rebind/clear/equality relationship unresolved
```

## Final answer to the ownership question

Stars do not own a single generic noun. The original binary uses a layered, reference-managed graph:

- `cStarManager` publishes and caches `cStarRecord` identities and live `cPlanet` objects;
- `cStarRecord` holds `cPlanetRecord` data and generation metadata;
- `cStar` is a separate live noun referencing a record and solar system;
- `cSolarSystem` references the live star and its live planets;
- `cPlanet` references a `cPlanetRecord`;
- `cEmpire` independently references `cStarRecord` values and stores home identities.

The manager’s record registries are substantially closed, but the two global star-manager root words remain an explicit unresolved publication/replacement/unpublication boundary. Any implementation that treats the canonical and alternate roots as one singleton, treats a record pointer as a save identity, or erases one registry entry as if it erased every star reference would exceed the static evidence.
