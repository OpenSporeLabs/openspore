# Simulator Root Closure — final Phase-0 synthesis

Snapshot `f0e310e0`, triage-v6, canonical xrefs `2540f2ca`, binary SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`. This is the final synthesis of the six track pairs, the cross-root pair, and the five follow-up pairs. It preserves static evidence levels and source provenance. **No runtime, Wine, trace, differential, OBSERVED, or VERIFIED evidence exists for this closure.** Sources: `docs/analysis/simulator-shared-state-interface.md:1-15`, `knowledgegraph/research/root-closure/followup-metrics.md:1-26`.

This deliverable characterizes interfaces and dependencies only. It does not implement replacements or begin Phase 1.

## Executive synthesis

### Definitively identified roots

- `00b3d350` is the SDK-named `Simulator::cGameInputManager::Get`; its field map is `CONFIRMED`, and it is independent from space context and b5 forwarded state. (`docs/analysis/simulator-shared-state-interface.md:81-94`)
- `01021260` and `01021080` are read views over authoritative `Simulator::sSpacePlayerData+0x04` and `+0x10`; the latter returns the exact `SpaceContext` enum. The recovered lifecycle now includes allocation/publication, two active-reference replacers, an independent context normalizer, and field teardown. (`knowledgegraph/research/root-closure/followup-space-lifecycle.md:7-16`, `knowledgegraph/research/root-closure/followup-space-lifecycle.md:64-128`)
- `00b1fdb0` returns a raw borrowed `cCreatureBase`/`cCreatureAnimal` pointer, not an ID. Receiver `+0x54` is strongly `cGameNounManager::mpAvatar`; `00b1fd50` proves AddRef/store/Release replacement. `result+0xd8` is a vtable slot, while the old `result+0x55c` association is rejected. (`knowledgegraph/research/root-closure/track-c-opaque-owner.md:48-112`, `knowledgegraph/research/root-closure/followup-receiver-provenance.md:88-129`)
- `00b21340` is the actual `cGameNounManager::GetData` implementation. SDK address `00b212d0` is a split continuation label reached by an intra-function jump from `00b211e0`; the xref was misclassified as a call, so it is not a second implementation. (`knowledgegraph/research/root-closure/followup-noun-boundary.md:15-85`)
- `01021300` is the validated current-player `cEmpire` cache; `00ba9370` is a `cStarManager::mEmpires` unsigned lower-bound/ceiling lookup; `00b25fb0` normally resolves a `cCivilization`-compatible result through `00b25f40 -> 00b21340`. (`knowledgegraph/research/root-closure/track-e-empire-chain.md:55-158`, `knowledgegraph/research/root-closure/followup-noun-boundary.md:107-149`)
- `00b3d300` and `00b3d2a0` are strong alternate manager-pointer accessors, not generic service locators: the former is noun-manager-specific; the latter is `cStarManager`-compatible. Their alternate/canonical aliases and lifecycle remain open. (`knowledgegraph/research/root-closure/followup-global-slots.md:11-22`)

`00b5b800` is deliberately not identified beyond its forwarding contract: no explicit arguments, `DAT_0167eaec` receiver source, `0xffffffff` on null receiver, and borrowed `receiver+0x20` on the non-null path. Its receiver class, mode/strategy identity, and physical storage type remain `UNKNOWN`. (`knowledgegraph/research/root-closure/track-b-strategy-handle.md:7-20`, `knowledgegraph/research/root-closure/track-b-strategy-handle.md:158-178`)

### Remaining ambiguities

1. Whether `DAT_0167eae0 == DAT_0167eb60` and `DAT_0167eae4 == DAT_0167eb0c` at every lifecycle point, and how each pair is published and torn down.
2. The concrete receiver and lifetime behind `DAT_0167eaec` and forwarded `+0x20`.
3. The one selected `00b1fdb0` receiver not sourced from `00b3d300`: `00bff2d0:00bff3b4` receives ECX from `01002bd0`. (`knowledgegraph/research/root-closure/followup-receiver-provenance.md:22-40`)
4. Whole-object teardown and final global release for `Simulator::sSpacePlayerData`; only field cleanup is closed. (`knowledgegraph/research/root-closure/followup-space-lifecycle.md:180-199`)
5. Noun create-callback versus `00ba8420` allocation ownership, allocation failure, erase/rekey, invalidation, locking, and reentrancy.
6. Exact SDK identity and a narrow static return contract for `00b25fb0`, especially its no-empire path returning the saved incoming ECX.
7. The domain effect of the `SpaceContext==2` follow-up through `00c8b360`, `00ffbe50`, and `01001360`.
8. The semantic name of `cSpeciesProfile+0x61c`, observed only as a 1..5 categorical scalar.

### Newly recovered structures and types

- `cGameNounManager` is closed to `0x11c` for the relevant domain, including `mpAvatar+0x54`, `mpPlayer+0x74`, `mNouns+0x78`, `mNounMap+0x98`, `mPoliticalMap+0xb4`, and `mObjects+0x10c`.
- `tGameDataVectorT<cGameData>` is closed to `0x18`, adding `mGarbage+0x10` and `mAllocator+0x14` to the earlier partial map.
- `cGameData` is `0x34`, with list links `+0x0c/+0x10`, political ID `+0x30`, `GetNounID` vtable `+0x20`, and `GetPoliticalID` vtable `+0x4c`; `cCivilization` is `0x4d8`.
- The `00b1fdb0` return surface is a `cCreatureBase`/`cCreatureAnimal` pointer with vtable `+0x84`, vtable `+0xd8`, `cLocomotiveObject+0xc0`, `field_B5C+0xb5c`, and `cSpeciesProfile*+0xb20`.
- `SpacePlayerData` is `0x34`; `01021d40` allocates/publishes and initializes it, `010219b0` and `010221f0` replace active planet/star references, `01021960` conditionally writes context, `01022580` independently normalizes context to Planet, and `01022460` releases owned fields.
- `cStarManager` retains `mEmpires+0x150` and `mpRelationshipManager+0x204`; `cEmpire` retains AddRef vtable `+0x00`, Release vtable `+0x04`, and `mPoliticalID+0x84`.
- The shared EASTL prerequisite is an unsigned lower-bound, not exact-find; successor selection is a required caller hazard.

Primary layout evidence: `knowledgegraph/research/root-closure/track-d-noun-registry.md:90-159`, `knowledgegraph/research/root-closure/track-f-space-context.md:161-193`, `knowledgegraph/research/root-closure/track-e-empire-chain.md:160-171`, `knowledgegraph/research/root-closure/track-c-opaque-owner.md:99-127`.

### Newly understandable callers

The evidence-selected semantic subset is exactly **40 direct callers**, **33 gameplay** and **7 non-gameplay**. It is a conservative union, not an inference from co-calling or triage category. The seven curated high-information samples are `00aebe90`, `00bff2d0`, `00c099e0`, `00cfbc10`, `010027b0`, `010225d0`, and `010593e0`. (`knowledgegraph/research/root-closure/followup-metrics.md:60-75`)

The 40 are:

`00ad12a0`, `00aebe90`, `00b25ca0`, `00b25f40`, `00b25fe0`, `00b32b20`, `00ba0080`, `00bbc370`, `00bbdff0`, `00bc2c00`, `00bdde70`, `00bf9820`, `00bfbbf0`, `00bff2d0`, `00c099e0`, `00c32cd0`, `00c3ae70`, `00c3dae0`, `00c8e5bb`, `00c8eb90`, `00d01ff0`, `00d06270`, `00d2e380`, `00d2e4a0`, `00d2e580`, `00d2e720`, `00d2e8a0`, `00d39360`, `00feb770`, `00febce0`, `00ff9100`, `010027b0`, `01003690`, `01021300`, `01021370`, `010225d0`, `010229d0`, `0102d1b0`, `0102df20`, `010593e0`.

The most material corrected consumer shapes are:

- `00bff2d0`: `00b3d300` result becomes the `00b21340` receiver.
- `00aebe90`, `00bdde70`, `00d06270`, and `00bf9820`: `00b3d300` result is the selected `00b25fb0` ECX source.
- `00d2e380`, `00d2e4a0`, `00d2e580`, `00d2e8a0`, and `00d39360`: `00b1fdb0` is a creature/avatar pointer with coherent polymorphic use.
- `01021300`, `00aebe90`, `00c32cd0`, `00feb770`, and `0102df20`: cache and registry consumers expose the AddRef/order and lower-bound constraints.
- `01003690`, `00b32b20`, `00c3ae70`, `00bbdff0`, `00bbc370`, and `00bc2c00`: space readers/writers remain separate from input/game mode.

### Downstream function counts

| metric | exact value | interpretation |
|---|---:|---|
| roots | 11 | frozen readiness/fan-in order |
| distinct direct-caller union | 2,303 | mechanically constrained by a root call/return contract |
| direct-call edges | 6,077 | repeated callsites count separately |
| gameplay-caller union | 516 | triage-v6 `GAMEPLAY_LOGIC` or `GAMEPLAY_SUPPORT` |
| callers directly reaching at least 2 roots | 948 | multi-root set intersection |
| callers directly reaching at least 3 roots | 390 | mechanical threshold, not a semantic claim |
| evidence-selected semantic subset | 40 | semantically adjudicated callers |
| gameplay in semantic subset | 33 | static category under triage-v6 |
| curated high-information callers | 7 | bounded examples, not exhaustive |
| per-root memberships | 3,896 | sum before caller deduplication |

The crucial distinction is that all **2,303** callers are mechanically constrained, but only **40** are semantically adjudicated in this campaign. The remaining callers are not claimed fully understood, runtime-reachable, or semantically uniform. (`knowledgegraph/research/root-closure/followup-metrics.md:5-26`, `knowledgegraph/research/root-closure/followup-metrics.md:60-71`)

### Phase-1 packages

The following are **characterization packages only**:

1. `alternate-canonical-manager-slots` — publication/teardown and receiver provenance for `00b3d300`, `00b3d2a0`, `00b3d400`, and `00b3d3a0`.
2. `noun-getdata-materialization` — ABI, callback order, lower-bound/successor table, ownership, and failure matrix for `00b21340` and helpers.
3. `current-empire-civilization-chain` — cache ordering, empire successor matrix, normal `cCivilization`-compatible result, and no-empire ECX return for `01021300`, `00ba9370`, and `00b25fb0`.
4. `space-player-data-lifecycle` — allocation/publication, active-reference replacement, context writers, field teardown, and the whole-object teardown boundary.
5. `avatar-accessor-replacement-lifetime` — `00b1fdb0` borrowed pointer, `00b1fd50` replacement, selected ECX provenance, and null-precondition plan.
6. `opaque-forwarded-state-corpus` — sentinel-gate matrix and first-writer search for `00b5b800`.
7. `bounded-semantic-caller-sequencing` — direct versus conditional/transitive paths in the seven curated callers.

No package authorizes implementation, replacement, or Phase-1 start.

### Single highest-impact unresolved root

**`00b3d300`** is the single highest-impact unresolved root. Its alternate noun-manager slot has 1,097 direct callers, is the dominant selected ECX source for both `00b1fdb0` and `00b25fb0`, and is not proven equal to canonical `DAT_0167eb60`. The smallest experiment is a read-only scratch trace of computed/indirect publishers and teardown for `DAT_0167eae0` and `DAT_0167eb60`, compared through `00b3d400` and one representative receiver window (`00bff2d0`). This also constrains the owner boundary used by `00b1fdb0` and `00b25fb0`. (`knowledgegraph/research/root-closure/cross-root-relationships.md:186-190`)

## Cross-root dependency diagram

```text
Simulator state substrate — multiple independent owners, not one singleton
│
├─ DAT_0167eae0 / 00b3d300 ── alternate cGameNounManager*
│  ├─ ECX -> 00b21340 GetData
│  │         └─ 00e5c780 lower_bound + 00ba8420 insertion
│  ├─ ECX -> 00b25fb0
│  │         ├─ 01021300 current cEmpire cache
│  │         └─ 00b25f40 kCivilization -> 00b21340
│  └─ ECX -> 00b1fdb0 receiver+0x54 creature/avatar pointer
│
├─ DAT_0167eb60 / 00b3d400 ── canonical cGameNounManager*
│     alias/lifecycle with DAT_0167eae0 unresolved
│
├─ DAT_0167eae4 / 00b3d2a0 ── alternate cStarManager*
│  └─ 01021300 -> 00ba9370 -> cStarManager.mEmpires lower_bound
│
├─ DAT_0167eb0c / 00b3d3a0 ── canonical cStarManager*
│     alias/lifecycle with DAT_0167eae4 unresolved
│
├─ DAT_0167eaec / 00b5b800 ── receiver+0x20 opaque state
│     null receiver -> 0xffffffff; no concrete receiver/storage type
│
├─ DAT_0167eaf8 / 00b3d350 ── cGameInputManager* input/game-mode state
│
└─ Simulator::sSpacePlayerData @ 0x016dda8c
   ├─ +0x04 ── 01021260 active-planet read view
   ├─ +0x10 ── 01021080 SpaceContext read view
   └─ +0x18/+0x1c ── 01021300 current-empire ID/cache
```

A direct edge means a canonical direct call. `00b3d300 -> ECX -> 00b21340` is receiver propagation inside a consumer, not a call from `00b3d300` to `00b21340`. `00b25fb0 -> 00b21340` is transitive through `00b25f40`; its no-empire path does not traverse the noun registry. `01021300 -> 00b3d2a0/00ba9370` executes only on cache miss or ID mismatch. Shared caller sets do not establish object identity or dataflow. (`knowledgegraph/research/root-closure/cross-root-relationships.md:3-27`, `knowledgegraph/research/root-closure/cross-root-relationships.md:162-176`)

The roots form a shared Simulator substrate, but `sSpacePlayerData` is the only common authoritative container for the three target fields. It does not make context, navigation, and empire identity one state axis. `SpaceContext`, `cScenarioMode::mMode`, and `cGameInputManager::mCurrentGameMode` remain distinct. (`knowledgegraph/research/root-closure/followup-space-lifecycle.md:170-178`)

## Root-by-root closure matrix

| root | closed mechanics / identity | lifecycle / ownership | closure status | bounded remainder |
|---|---|---|---|---|
| `00b3d300` | raw `DAT_0167eae0`; strong alternate `cGameNounManager*`; decisive `00bff408 -> 00bff426 -> 00bff428 -> 00b21340` | borrowed getter; no ref/write | `SUPPORTED`; alias/lifecycle open | equality/publication with `DAT_0167eb60` |
| `00b3d2a0` | raw `DAT_0167eae4`; alternate `cStarManager*`; `mEmpires+0x150`, relationship `+0x204` | borrowed getter; no ref/write | `SUPPORTED`; alias/lifecycle open | equality/publication with `DAT_0167eb0c` |
| `00b5b800` | no args; null `0xffffffff`; non-null borrowed `receiver+0x20` | no allocation/mutation/ref | mechanics `SUPPORTED`; identity `UNKNOWN` | receiver class, mode identity, physical storage |
| `00b3d350` | named `cGameInputManager::Get`; `0x114` field map | borrowed pointer; getter does not AddRef | `CONFIRMED`; behavior not reconstructed | publication/ownership/runtime input behavior |
| `01021260` | null-guarded read of `mpActivePlanet+0x04` | allocation/publication and field teardown recovered; whole-object teardown open | strong `SUPPORTED` | retained-pointer expectations and final object destruction |
| `00b1fdb0` | raw `cCreatureBase/cCreatureAnimal*`; `receiver+0x54` strongly `mpAvatar`; `00b1fd50` replacement | borrowed return; AddRef/store/Release writer | return `SUPPORTED`; owner/lifetime bounded | one `01002bd0` receiver, canonical/global binding, null contract |
| `00b21340` | actual `GetData`; five args; `mNounMap+0x98`; callbacks; successor hazard | borrowed vector; no root ref; map mutation through helper | mechanics/identity `CONFIRMED` | allocation, invalidation, erase, locking |
| `01021300` | ID/cache validation; exact AddRef/store/Release; ceiling successor may cache | one owned cache reference; borrowed return | `CONFIRMED` | registry invalidation and manager lifecycle |
| `01021080` | direct `SpaceContext+0x10` read with exact values | three writer paths recovered; field teardown separate | `CONFIRMED` | helper domain and whole-object teardown |
| `00b25fb0` | no explicit stack args/plain ret; normal `cCivilization`-compatible result; no-empire returns incoming ECX | borrowed normal result; no ref | mechanics `SUPPORTED` | exact SDK name and narrow no-empire return contract |
| `00ba9370` | `mEmpires` unsigned lower-bound/ceiling; sentinel/end null; borrowed payload | map owns intrusive pointer | `CONFIRMED` | receiver slot alias and runtime rekey behavior |

## Corrected contracts that must survive Phase-1 handoff

- `00b3d300` is not a generic service locator/context; its direct consumer contract is noun-manager pointer use.
- `00b3d2a0` is not canonical `cStarManager::Get`; canonical `Get` is `00b3d3a0/DAT_0167eb0c`.
- `00b5b800` is a scalar/opaque forwarded state view, not a normal pointer or confirmed strategy interface.
- `00b3d350` remains a separate `cGameInputManager*` accessor.
- `00b1fdb0` is not a player ID. `result+0xd8` is a vtable slot; `result+0x55c` is not a supported root-result association.
- `00b21340` is the real GetData implementation; `00b212d0` is a split continuation/misclassified xref.
- `00b25fb0` has **no caller stack fallback** and ends with plain `ret`; the no-empire result is saved incoming ECX.
- `00ba9370` is lower-bound/ceiling, not exact-find; callers requiring exact identity must compare `cEmpire+0x84`.
- `01021300` can cache a lower-bound successor and its reference ordering is AddRef-new, store, Release-old.
- SpaceContext, game/input mode, and scenario mode are distinct axes.

## Smallest next experiment by remaining ambiguity

| ambiguity | smallest next experiment | expected resolution |
|---|---|---|
| noun alternate/canonical alias | scan computed publishers/teardown of `DAT_0167eae0` and `DAT_0167eb60`; inspect one `00bff2d0` receiver window | publication, equality, and owner boundary |
| star alternate/canonical alias | scan computed publishers of `DAT_0167eae4` and `DAT_0167eb0c`; classify unowned `00b5ca50` | publication/alias and canonical-getter consumer |
| b5 identity | find first writer of `DAT_0167eaec`, then type its `+0x20` store | receiver class and physical state type |
| avatar receiver exception | decompile `01002bd0` and `00bff2d0:00bff3b4` | classify the sole selected non-`00b3d300` receiver |
| whole SpacePlayerData teardown | search free/reset and the unowned `01022572` write | final teardown path or bounded negative result |
| noun allocation/invalidation | decompile `00ba8420/00ba83a0/009215c0`; trace one `needsUpdate` writer | create/insertion relation and invalidation |
| empire stale cache | inspect one `mEmpires` erase/rekey site and one cache-miss consumer | stale/successor constraints |
| `00b25fb0` exact contract | recover one complete no-empire caller frame | bounded no-empire type and SDK-name evidence |
| context value-2 helper | decompile only `01001360` and annotate its own writes/slot `+0x16c` | concrete collection/domain effect |
| profile `+0x61c` | find one writer and one independent reader | categorical name only with agreeing evidence |

## Evidence and provenance

The synthesis follows the repository's static precedence: pinned bytes/instruction verification, canonical xrefs and SDK exports, six track reports, five follow-up reports, the Phase-0 interface, reconstruction readiness, and current project state. Original and follow-up contradictions are superseded only where the required follow-up provides direct static evidence.

Primary line-range anchors:

- Baseline scope and no-runtime policy: `docs/analysis/simulator-shared-state-interface.md:1-15`
- Cross-root model: `knowledgegraph/research/root-closure/cross-root-relationships.md:3-27`
- Exact metrics: `knowledgegraph/research/root-closure/followup-metrics.md:5-42`
- Manager slots: `knowledgegraph/research/root-closure/followup-global-slots.md:11-22`
- Noun boundary/callbacks: `knowledgegraph/research/root-closure/followup-noun-boundary.md:7-14`
- Avatar receiver/write: `knowledgegraph/research/root-closure/followup-receiver-provenance.md:13-40`, `knowledgegraph/research/root-closure/followup-receiver-provenance.md:88-129`
- Space lifecycle: `knowledgegraph/research/root-closure/followup-space-lifecycle.md:7-16`
- Readiness roots: `knowledgegraph/triage/reconstruction-readiness-f0e310e0.json:24-179`

No `SPORE/` file, OpenSpore source, historical v1-v6 artifact, or Phase-0 interface artifact is modified by this synthesis. The machine-readable companion is `knowledgegraph/research/root-closure-f0e310e0.json`.
