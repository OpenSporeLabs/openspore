# Cross-root relationships — Phase-0 Root Closure

## Scope and conclusion

This report reconciles the six committed track pairs, the Phase-0 shared-state baseline, reconstruction readiness, canonical direct-call xrefs, and the existing dependency projection. It uses static artifacts only. No runtime, Wine, source, `SPORE/`, historical artifact, or Phase-0 interface was used or changed.

The roots form a shared Simulator state substrate, not one larger object. The strongest common state owner is `Simulator::sSpacePlayerData`: `01021260` reads `+0x04`, `01021080` reads `+0x10`, and `01021300` reads/replaces `+0x18/+0x1c`. The global service slots, input manager, cStarManager-compatible registry, noun manager, avatar accessor, and opaque strategy state remain separate domains.

```text
DAT_0167eae0  00b3d300  shared context/owner accessor
DAT_0167eae4  00b3d2a0  cStarManager-compatible manager/registry owner
DAT_0167eaec  00b5b800  forwarded_object+0x20 opaque state value
DAT_0167eaf8  00b3d350  cGameInputManager* input/mode state

sSpacePlayerData
  +0x04  01021260  active planet reader
  +0x10  01021080  SpaceContext reader
  +0x18  01021300  empire ID/cache key
  +0x1c  01021300  lazy cEmpire cache

00b3d2a0 ──(used by 01021300)──> 00ba9370
00b25fb0 ──> 01021300
00b25fb0 ──> 00b25f40 ──> 00b21340 ──> 00e5c780 / 00ba8420
00b5b800 ──> 00b3d320 ──> 00a42730
```

The arrows above are direct xref edges. High overlap between caller sets is not an object or dataflow edge.

## Evidence identity and counting

- Binary: `SporeApp.exe` 3.1.0.22, SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`.
- Analysis: `f0e310e0`, triage-v6, x86-LE-32.
- Canonical xrefs: `knowledgegraph/triage/xrefs-2540f2ca.tsv`, 223,704 rows, SHA-256 `89e74b8a03c4db38a1927f8c95c38db507bf99cb8a11de6b6eb6a9484d8c79cb`.
- Direct caller counts below are distinct caller functions. Direct edges are individual direct-call rows. Gameplay counts are the baseline/readiness fan-in projection.
- All primary roots have `reconstructable_now=false`; `00b3d350` is the named, decomp-backed exception but is not queued as a replacement target.

## Root metrics

| root | role | direct callers / gameplay | direct edges | direct outbound edges |
|---|---|---:|---:|---|
| `00b3d300` | global context/owner accessor | 1,097 / 252 | 1,941 | none |
| `00b3d2a0` | cStarManager-compatible manager/registry owner | 314 / 101 | 510 | none |
| `00b5b800` | opaque forwarded state | 459 / 80 | 701 | `00b3d320`, `00a42730` |
| `00b3d350` | `cGameInputManager::Get` | 614 / 80 | 958 | none |
| `01021260` | active-planet read view | 262 / 68 | 357 | none |
| `00b1fdb0` | receiver `+0x54` avatar pointer | 303 / 68 | 432 | none |
| `00b21340` | noun GetData implementation/materializer | 254 / 50 | 318 | `00e5c780`, `00ba8420` |
| `01021300` | lazy current-player cEmpire cache | 182 / 47 | 246 | `00b3d2a0`, `00ba9370` |
| `01021080` | SpaceContext reader | 175 / 38 | 230 | none |
| `00b25fb0` | current-empire to kCivilization bridge | 100 / 36 | 193 | `01021300`, `00b25f40` |
| `00ba9370` | empire map lower-bound/ceiling lookup | 136 / 35 | 191 | `00e5c780` |

Related helper metrics: `00b25f40` has 64 direct callers and 80 direct edges; `00b3d400` has 43 direct callers and 59 edges; `00b3d2c0` has 127 callers and 253 edges; `00e5c780` has 239 callers and 265 edges; `00ba8420` has 6 callers and 7 edges.

## Domain model

### 1. Global service/context handles

`00b3d300`, `00b3d2a0`, and `00b5b800` have different globals and different return contracts:

- `00b3d300` returns raw `DAT_0167eae0`; sampled consumers propagate it as a receiver into object, player, noun, and state helpers.
- `00b3d2a0` returns raw `DAT_0167eae4`; downstream layout evidence supports a cStarManager-compatible receiver for `mEmpires +0x150` and relationship-manager `+0x204`.
- `00b5b800` reads `DAT_0167eaec`, forwards non-null values to `00a42730`, and returns `[ECX+0x20]`; absent owner returns `0xffffffff`.

The direct common-caller sets are large: `00b3d300/00b3d2a0` = 81, `00b3d300/00b5b800` = 142, and `00b3d2a0/00b5b800` = 30. These are shared-routine intersections, not evidence that the three globals alias or that their return values have one type.

### 2. Input/mode

`00b3d350` is the only primary root with a named SDK accessor and explicit `cGameInputManager` layout. It returns `DAT_0167eaf8`; `mLastGameMode +0x18` and `mCurrentGameMode +0x1c` are separate from `SpacePlayerData.mCurrentContext +0x10` and b5's forwarded `+0x20` value.

There are 64 direct common callers of `00b5b800` and `00b3d350`, and 171 direct common callers of `00b3d300` and `00b3d350`. These are shared subsystem routines, not direct b5-to-input dataflow. The `00b3d420` game-mode accessor is also a different global/owner.

### 3. SpacePlayerData and navigation

`01021260` and `01021080` are direct read views:

- `01021260`: null-guarded `SpacePlayerData+0x04` read, active-planet candidate, 262 callers, no outgoing calls.
- `01021080`: direct `SpacePlayerData+0x10` read, `SpaceContext` enum, 175 callers, no null guard, no outgoing calls.
- `01021960`: candidate context writer; it stores the new value at `+0x10` and has a value-2 follow-up to `01001360`.
- `010219b0`: candidate active-planet/active-star replacement writer; it writes `+0x04/+0x08` with reference-counted replacement and directly calls `00b3d2a0`.
- `01021d40`: reported SpacePlayerData allocator/initializer; body and teardown are not closed.

`01021300` reads different fields of the same backing structure. It does not derive empire identity from `mpActivePlanet` or `mCurrentContext`. The 61 direct common callers of `01021260` and `01021080` are strong space-state consumers, not noun consumers.

### 4. Empire identity/cache

`01021300` is the clearest stateful root:

1. Read `SpacePlayerData+0x18` ID and `+0x1c` cache.
2. Return the cached borrowed `cEmpire*` when `cEmpire+0x84` matches the ID.
3. On miss, call `00b3d2a0` and then `00ba9370`.
4. AddRef the new pointer, store it, and Release the old pointer.

`00ba9370` is an unsigned lower-bound/ceiling lookup over the cStarManager-compatible `mEmpires` map; it is not exact-find. `00b3d2a0` and `00ba9370` have 134 direct common callers, but only a direct chain such as `01021300 -> 00b3d2a0 -> 00ba9370` establishes lookup order and receiver propagation. The root set does not prove that the manager is `sSpacePlayerData`, cGameNounManager, or cGameInputManager.

### 5. Noun/game-data/avatar

The noun domain is coherent but not one receiver:

- `00b3d400` is the named `cGameNounManager::Get`, returning `DAT_0167eb60`.
- `00b21340` is the high-confidence `GetData` implementation entry, using `mNounMap +0x98` and returning a manager-owned `tGameDataVectorT<cGameData>*`.
- `00b25f40` directly calls `00b21340` with `kCivilization` and scans `cGameData::GetPoliticalID`.
- `00b25fb0` directly calls `01021300` and `00b25f40`; it does not directly call `00b21340`.
- `00b1fdb0` reads receiver `+0x54`, strongly matching `cGameNounManager::mpAvatar`; its result is a high-confidence current-avatar pointer, but selected call sites do not preserve the ECX path to `DAT_0167eb60`.

There are 12 functions that directly call both `00b21340` and `00b25fb0`. They are shared noun/bridge consumers. Separately, the 100 direct callers of `00b25fb0` are potential transitive noun consumers through `00b25f40 -> 00b21340`, but fallback calls can return the caller's word without entering the noun registry.

There are only 3 direct common callers of `00b3d400` and `00b25fb0`, and no direct common callers of `00b3d400` with `00b21340` or `00b25f40` in the canonical direct-call set. The named noun getter is therefore related to the noun bridge, but its authoritative context provenance is not closed.

### 6. Avatar and opaque strategy state are separate from empire identity

`00b1fdb0` has 218 direct common callers with `00b3d300`, 77 with `00b3d2a0`, 65 with `00ba9370`, and 60 with `00b5b800`. These are cross-domain creature/gameplay routines. The selected `00d2e380`, `00d2e4a0`, `00d2e580`, `00d2e8a0`, and `00d39360` bodies prove pointer use and cCreatureBase layout, not owner aliasing.

`00b5b800` has 373 direct-call edges with adjacent sentinel comparisons across 251 callers, plus one direct `0xffffffff` comparison. The dominant use is scalar/state gating. Do not treat its result as a pointer because the sentinel constants resemble addresses.

## Track A/C/E reconciliation

| track | supported result | what it does not prove |
|---|---|---|
| A | `00b3d2a0` is cStarManager-compatible at `+0x150` and `+0x204` | exact `cStarManager::Get` identity; alias with `DAT_0167eb0c`; relation to noun manager |
| C | `00b1fdb0` returns a current-avatar object pointer from receiver `+0x54`, layout-matched to `cGameNounManager::mpAvatar` | direct ECX provenance to `00b3d400`/`DAT_0167eb60`; shared object with `00b3d2a0` |
| D | `00b21340` is the GetData implementation using noun-manager layout and `mNounMap +0x98` | exact SDK address `00b212d0`; ownership by `DAT_0167eae4` |
| E | `00b25fb0` has a noun-manager-layout context and reaches GetData through `00b25f40` | authoritative context accessor/global; fallback exact type; common object with star manager |
| F | space readers and candidate writers use separate `SpacePlayerData` fields | context derived from input mode or game mode |

The defensible model is therefore a shared Simulator graph containing separate owner families. Track A's manager, Track C's avatar owner, and Track E's noun context may participate in the same noun/identity subsystem, but forcing them into one object would exceed static evidence.

## Shared-caller intersections

The following are direct co-call counts from the canonical xref export. They are not transitive dependency counts and do not establish object identity.

| relationship | common callers | interpretation |
|---|---:|---|
| `00b3d300` / `00b3d2a0` | 81 | shared context/manager routines |
| `00b3d300` / `00b5b800` | 142 | shared context and opaque state routines |
| `00b3d2a0` / `00b5b800` | 30 | shared identity/strategy routines |
| `00b3d350` / `00b5b800` | 64 | input/strategy shared subsystem routines |
| `00b3d300` / `00b3d350` | 171 | context/input shared routines |
| `00b3d300` / `01021260` | 104 | context plus active-planet reads |
| `00b3d2a0` / `01021260` | 35 | manager plus active-planet reads |
| `00b3d300` / `01021080` | 46 | context plus SpaceContext reads |
| `01021260` / `01021080` | 61 | paired space-state readers |
| `00b3d300` / `01021300` | 64 | context plus empire cache |
| `00b3d2a0` / `01021300` | 70 | manager plus empire cache |
| `00b3d2a0` / `00ba9370` | 134 | manager and registry lookup routines |
| `01021300` / `00ba9370` | 48 | cache and registry lookup routines |
| `00b3d300` / `00b21340` | 232 | context/noun shared routines |
| `00b3d350` / `00b21340` | 56 | input/noun shared routines |
| `01021260` / `00b21340` | 33 | space/noun shared routines, not a direct transition |
| `01021080` / `00b21340` | 14 | context/noun shared routines, not a direct transition |
| `00b21340` / `00b25fb0` | 12 | direct shared noun/bridge consumers |
| `00b21340` / `01021300` | 21 | noun/empire shared routines |
| `00b21340` / `00ba9370` | 11 | noun/registry shared routines |
| `00b1fdb0` / `00b3d300` | 218 | avatar/current-context gameplay routines |
| `00b1fdb0` / `00b3d2a0` | 77 | avatar/manager gameplay routines |
| `00b1fdb0` / `00b5b800` | 60 | avatar/opaque-state gameplay routines |
| `00b1fdb0` / `00ba9370` | 65 | avatar/empire shared routines |
| `00b1fdb0` / `00b25fb0` | 3 | limited avatar/civilization shared routines |

High-information direct co-callers include `00aebe90` (global services plus empire/noun bridge), `010027b0` (context plus empire), `010225d0` (space navigation plus manager), `010593e0` (tool state plus manager/avatar), `00c099e0` (context/input/opaque state), `00bff2d0` (context plus noun/bridge), and `00cfbc10` (a high-degree multi-domain consumer). Their bodies are the right bounded samples for sequencing; their co-call status alone is not an ownership proof.

## Direct versus transitive downstream constraints

| root | direct constraint | direct consumer subset | transitive/conditional consumers |
|---|---|---|---|
| `00b3d300` | all 1,097 direct callers get a raw no-argument global; 252 gameplay | `00aebe90`, `00bff2d0`, `00c099e0`, `010027b0`, `010225d0`, `010593e0` | The 232 `00b3d300/00b21340` co-callers are not noun consumers by edge alone. |
| `00b3d2a0` | all 314 direct callers get raw `DAT_0167eae4`; 101 gameplay | `01021300`, `00aebe90`, `010027b0`, `010225d0`, `010593e0`, `0102df20` | `01021300` conditionally reaches the manager on cache miss; its 182 callers are not guaranteed to execute the refresh path. |
| `00b5b800` | all 459 direct callers get raw 32-bit forwarded state or `0xffffffff`; 701 edges | `00ad12a0`, `00c099e0`, `00d2e4a0`, `00d2e580`, `00d2e8a0` | No root-owned downstream closure; 251 sentinel callers are direct scalar/state gates. |
| `00b3d350` | all 614 direct callers get a borrowed `cGameInputManager*`; 80 gameplay | `00c099e0`, `01003690`, `00b32b20`, `00c3ae70`, `00bbdff0` | The 64 b5 co-callers are shared input routines, not b5 dataflow consumers. |
| `01021260` | all 262 direct callers get null-guarded active-planet storage; 68 gameplay | `00bbc370`, `00bc2c00`, `00bbdff0`, `01021370`, `010229d0` | The 33 direct co-callers with `00b21340` are shared routines; there is no direct edge to the noun root. |
| `00b1fdb0` | all 303 direct callers get receiver `+0x54` as a raw pointer; 68 gameplay | `00d2e380`, `00d2e4a0`, `00d2e580`, `00d2e720`, `00d2e8a0`, `00d39360` | Its 218/77/65/60/45 co-call sets with context, manager, registry, b5, and input are shared identity/gameplay routines, not owner equality. |
| `00b21340` | all 254 direct callers use the five-argument noun ABI; 50 gameplay, 318 edges | `00b25f40`, `00ba0080`, `00b25ca0`, `00b25fe0`, `00bf9820`, `00bfbbf0` | `00b25fb0` reaches it only through `00b25f40`; fallback calls can bypass it. |
| `01021300` | all 182 direct callers use the `SpacePlayerData+0x18/+0x1c` cache; 47 gameplay, 246 edges | `00aebe90`, `00c32cd0`, `00d01ff0`, `00febce0`, `00feb770`, `0102df20` | The direct outbound manager/registry edges execute only on cache miss or ID mismatch. |
| `01021080` | all 175 direct callers get a raw `SpaceContext`; 38 gameplay, 230 edges | `00bbc370`, `00bc2c00`, `00c3ae70`, `00c3dae0`, `010229d0` | The 14 co-callers with `00b21340` are shared routines; no direct context-to-noun edge exists. |
| `00b25fb0` | all 100 direct callers use the noun-layout context and one-word fallback; 36 gameplay, 193 edges | `00aebe90`, `00bdde70`, `00d06270`, `00bf9820`, `00ff9100` | Its callers are potential transitive noun consumers through `00b25f40`, except the fallback path; the 12 direct co-callers are the direct shared subset. |
| `00ba9370` | all 136 direct callers use lower-bound/ceiling semantics; 35 gameplay, 191 edges | `01021300`, `00aebe90`, `00c32cd0`, `00feb770`, `0102df20` | `01021300` is the direct cache bridge; the 134 manager/registry co-callers do not all execute the cache chain. |

## Initialization, teardown, and transitions

- No initialization, allocation, teardown, lock, or direct global write is established for `00b3d300`, `00b3d2a0`, or `00b5b800`.
- `01021d40` is the reported `SpacePlayerData` allocator/initializer; `010219b0` is a candidate reference replacement writer; `01021960` is a candidate context writer. Whole-object teardown and complete field order are not committed.
- `01021300` is the only primary root with established cache mutation: it performs identity validation and AddRef/Release replacement, not allocation or destruction.
- `00b3d400` is a borrowed singleton getter. `00b21340` materializes manager-owned noun records and clears `needsUpdate`; manager-wide teardown and exact invalidation writers remain open.
- `00b5b800` and its helpers are read-only. Their receiver lifetime and initialization are unresolved.

## Highest-impact remaining ambiguity

The single highest-impact ambiguity is global-slot and receiver provenance: whether `DAT_0167eae0` and `DAT_0167eae4` alias, wrap, or differ from `DAT_0167eb60` and `DAT_0167eb0c`, and whether the ECX receivers at `00b1fdb0` and `00b25fb0` come from the named getters.

The smallest static experiment is a read-only scratch trace of writers, getter propagation, and the last ECX definition before the selected `00b1fdb0`/`00b25fb0` calls. Compare `00b3d2c0`, `00ba9370`, `00b3d400`, `00b3d3a0`, and the `00aebe90`, `00bff2d0`, and `00cfbc10` windows. This is more valuable than adding another concrete type to the unnamed roots because it determines which owner/state domains can safely share a future interface.

## Smallest next static experiment by root

| root | smallest experiment | expected resolution |
|---|---|---|
| `00b3d300` | trace all `DAT_0167eae0` references and compare them with `DAT_0167eb60` in three shared bridge windows | context owner, alias status, and noun-manager relation |
| `00b3d2a0` | trace `DAT_0167eae4` versus `DAT_0167eb0c` through `00b3d2c0`, `00ba9370`, and `01021300` | cStarManager accessor identity and lifecycle |
| `00b5b800` | find the first writer of `DAT_0167eaec`; decompile `00b3d320/00a42730/00ad12a0` | physical type and lifetime of forwarded `+0x20` |
| `00b3d350` | trace `DAT_0167eaf8` writers and one input consumer | input-manager ownership and coordination evidence |
| `01021260` | decompile `01021d40`, `010219b0`, and `00b60d80`; enumerate `+0x04/+0x08` writes and releases | active-planet allocation, assignment, and teardown |
| `00b1fdb0` | trace ECX through the six selected call windows to `DAT_0167eb60`; find the first `+0x54` store | avatar owner, ABI, replacement, and lifetime |
| `00b21340` | adjudicate `00b212d0..00b21410`; type/decompile the actual implementation and one `00b25f40` call | SDK boundary, callback order, lower-bound, and `needsUpdate` |
| `01021300` | audit `+0x18/+0x1c` writers and empire-map mutation sites; compare hit/miss callers | stale cache and invalidation constraints |
| `01021080` | audit the applied `+0x10` width; inspect `01021960`, `01001360`, and its nine direct writers | complete static context transition table |
| `00b25fb0` | recover complete frames and ECX provenance in `00aebe90`, `00bdde70`, `00d06270`, and `00bf9820` | fallback type and authoritative noun accessor |
| `00ba9370` | decompile it with `00e5c780`; inspect one cache miss and one exact-identity caller; trace receiver global | result encoding, successor behavior, and named getter provenance |

## Evidence boundary

All conclusions are static. Shared-caller intersections identify bounded investigation samples, not object equality. Direct xref edges are distinguished from transitive consumers and conditional cache/fallback paths. The committed source boundary is preserved: no source, `SPORE/`, historical artifact, or Phase-0 interface edit was made.

Primary inputs:

- `knowledgegraph/research/root-closure/track-a-service-identity.{md,json}`
- `knowledgegraph/research/root-closure/track-b-strategy-handle.{md,json}`
- `knowledgegraph/research/root-closure/track-c-opaque-owner.{md,json}`
- `knowledgegraph/research/root-closure/track-d-noun-registry.{md,json}`
- `knowledgegraph/research/root-closure/track-e-empire-chain.{md,json}`
- `knowledgegraph/research/root-closure/track-f-space-context.{md,json}`
- `docs/analysis/simulator-shared-state-interface.md`
- `knowledgegraph/triage/reconstruction-readiness-f0e310e0.json`
- `knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json`
- `knowledgegraph/triage/xrefs-2540f2ca.tsv`
- `knowledgegraph/research/global-campaign-2026/track-j-dependency-graph.json`
