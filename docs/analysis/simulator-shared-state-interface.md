# Simulator shared-state interface — Phase-0 semantic reconnaissance

Snapshot `f0e310e0`, triage-v6, canonical xref basis. This document is a bounded semantic interface freeze for the high-fan-in Simulator roots. It characterizes contracts and state domains for later reconstruction; it does not implement replacements.

## 1. Scope and evidence discipline

The primary set contains exactly 11 roots, retained in readiness/fan-in order:

`00b3d300`, `00b3d2a0`, `00b5b800`, `00b3d350`, `01021260`, `00b1fdb0`, `00b21340`, `01021300`, `01021080`, `00b25fb0`, `00ba9370`.

`00e5c780` is a generic lower-bound map prerequisite, not a primary gameplay root. The forwarding helpers `00b3d320`, `00a42730`, and `00ba8420` are retained only where the supplied evidence makes them relevant.

Evidence levels in this deliverable are `UNKNOWN`, `APPROXIMATION`, `INFERRED`, `SUPPORTED`, and `CONFIRMED`. Structural offsets and call behavior are not silently promoted to exact C++ identity. No runtime trace or differential result exists for this interface set; no `OBSERVED` or `VERIFIED` claim is made.

The canonical xref export identifies the analyzed binary SHA-256 as `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`. The edge export is the canonical deduplicated xref export with call/reference types. The analysis snapshot is `f0e310e0`; the canonical xref export is pinned separately as `2540f2ca`.

## 2. Artifact identity and inventory

| item | value |
|---|---|
| artifact | `simulator-shared-state-interface` |
| purpose | Phase-0 shared-state interface reconnaissance |
| binary | `SporeApp.exe`, x86-LE 32-bit |
| analysis snapshot | `f0e310e0` |
| classifier | `triage-v6` |
| canonical xrefs | `knowledgegraph/triage/xrefs-2540f2ca.tsv` |
| xref edge count | 223,704 |
| xref edge SHA-256 | `89e74b8a03c4db38a1927f8c95c38db507bf99cb8a11de6b6eb6a9484d8c79cb` |
| primary root count | 11 |
| runtime evidence | none |

Fan-in is shown as total direct callers / gameplay callers. The ordering is intentional and must not be replaced with address sort when the root order is serialized.

## 3. Per-root contracts

### 3.1 `00b3d300` — `FUN_00b3d300`

| contract item | characterization |
|---|---|
| category | `STATE_MANAGER` or `UNKNOWN` shared global service |
| call shape | no arguments; returns a 4-byte value in EAX |
| return contract | raw `DAT_0167eae0`; likely manager/service pointer, but pointee type is unresolved |
| callers | 1,097 total; 252 gameplay |
| lifecycle | no initialization, allocation, or lock observed in the root |
| state | read-only accessor contract; many callers discard the return value |
| confidence | high mechanics; low exact identity |
| boundary | characterize the global slot and its use contract, not a service implementation |

Representative callers include `00be34a0`, `00d2e380`, `00d2e4a0`, `00d2e580`, `00d2e720`, `00d39360`, and `00fee310`. Field and vtable use of the returned value are not established.

### 3.2 `00b3d2a0` — `FUN_00b3d2a0`

| contract item | characterization |
|---|---|
| category | shared manager / identity-lookup service, exact class unknown |
| call shape | no arguments; returns `DAT_0167eae4` in EAX |
| return contract | likely central object or lookup-manager handle; exact type unresolved |
| callers | 314 total; 101 gameplay |
| lifecycle | no initialization or allocation observed in the root |
| state | adjacent-global observation: `00b3d2c0` directly reads `DAT_0167eae4`; returned receiver layout is not established by this root |
| confidence | high return-slot mechanics; medium lookup-manager interpretation |
| boundary | do not assign a C++ class until the receiver layout is corroborated |

`00b3d2c0` directly reads `DAT_0167eae4` and is not a direct caller of `00b3d2a0`; `01021300` uses the root before its map lookup. Apparent pushed arguments near this root belong to following helpers and are not assigned to `00b3d2a0`.

### 3.3 `00b5b800` — `FUN_00b5b800`

| contract item | characterization |
|---|---|
| category | `UNKNOWN` or factory/owner accessor; not a proven direct singleton |
| call shape | no explicit arguments |
| return contract | scalar/opaque handle; null path returns `0xffffffff` |
| callers | 459 total; 80 gameplay |
| lifecycle | no initialization, allocation, or lock observed in the root |
| state | loads `DAT_0167eaec`; non-null path sets ECX and tail-jumps to `00a42730`, which reads `object+0x20` |
| confidence | high forwarding mechanics; low exact identity |
| boundary | preserve scalar semantics until consumers prove a pointer interpretation |

Representative callers include `00aca360`, `00acc800`, `00acd790`, `00b3d2c0`, `00d2e4a0`, `00d2e580`, and `00d2e8a0`. Sampled consumers consistently treat the result as a scalar or opaque handle.

### 3.4 `00b3d350` — `Simulator::cGameInputManager::Get`

| contract item | characterization |
|---|---|
| category | named input-boundary accessor |
| call shape | no arguments; returns `DAT_0167eaf8` in EAX |
| return contract | SDK-declared `cGameInputManager*`; borrowed shared pointer |
| callers | 614 total; 80 gameplay |
| lifecycle | no initialization or allocation observed in the root |
| state | shared input/mode-routing object, size `0x114` (276) |
| confidence | high named accessor and field map; exact runtime ownership not established |
| boundary | expose a read-only interface and field offsets, not input behavior |

The SDK map is: vtable `+0x00`; `mLastGameMode +0x18`; `mCurrentGameMode +0x1c`; maps `+0x28` and `+0x44`; mouse `+0x68` and `+0x6c`; input regions `+0x74`, `+0x90`, and `+0xc0`; strings `+0xdc` and `+0xec`; vector `+0xfc`; integer `+0x110`. `00e0bcb0` and `00ac2e20` demonstrably use the returned pointer; `01053d00` calls the accessor but discards its return.

### 3.5 `01021260` — `FUN_01021260`

| contract item | characterization |
|---|---|
| category | `DIRECT_STATE_ACCESSOR` |
| call shape | no arguments; null-guarded global read |
| return contract | raw `cPlanet*` / `cPlanetPtr` from `Simulator::sSpacePlayerData+0x4`; null global returns zero |
| callers | 262 total; 68 gameplay |
| lifecycle | `01021d40` allocates and initializes `SpacePlayerData`; the active-planet object allocation is not established at that helper |
| state | active planet/navigation state |
| confidence | high typed accessor contract; object layout beyond the pointer slot is not reconstructed |
| boundary | do not allocate the planet here |

Representative consumers include `00b31cc0`, `00c706d0`, `00f31d80`, `01021370`, and `01037a20`; `01021370` dereferences `+0x13c` on the returned planet object.

### 3.6 `00b1fdb0` — `FUN_00b1fdb0`

| contract item | characterization |
|---|---|
| category | `UNKNOWN`; semantic type intentionally unresolved |
| call shape | hidden ECX/this owner; exact convention is unresolved between `__thiscall` and `__fastcall` |
| return contract | raw 32-bit read from owner `+0x54` |
| callers | 303 total; 68 gameplay |
| lifecycle | no initialization, allocation, mutation, or lock observed in the root |
| state | caller usage is both scalar/action-handle-like and pointer-like/vtable-object-like |
| confidence | high offset mechanics; low semantic identity |
| boundary | do not type as player ID or pointer without new evidence |

Representative consumers include `00b0a6f0`, `00b2dac0`, `00bb1340`, `00d2e380`, `00d2e4a0`, `00d2e580`, and `00d39360`. Consumer accesses on the returned object include `+0xc0`, `+0xd8`, `+0x55c`, and `+0xb20`; `+0x61c` is reached through the nested object returned at `+0xb20`. These are observations of use, not proven field names.

### 3.7 `00b21340` — `FUN_00b21340`

| contract item | characterization |
|---|---|
| category | `REGISTRY` / noun-data map bridge |
| call shape | ECX-dependent context plus five 32-bit stack arguments; `RET 0x14` |
| return contract | SDK-shaped `tGameDataVectorT<cGameData>*`; exact address/type identity is unresolved |
| callers | 254 total; 50 gameplay |
| lifecycle | map lookup/materialization path; mutation/insertion is performed through helpers |
| state | noun map, linked-list materialization, and vector record state |
| confidence | high map/vector mechanics; medium exact SDK-name match |
| boundary | do not label this function a message handler; exact function/address identity is not proven |

The context map is at `this+0x98`; internal map-end storage at `+0x9c` is noted only as evidence and is not a declared `cGameNounManager` field. The returned record is a pointer to `tGameDataVectorT<cGameData>` with `needsUpdate +0x00`, `begin +0x04`, `end +0x08`, and `capacity +0x0c`. The noun list's `next +0x0c` is observed on an unknown noun list node. The function calls `00e5c780` and `00ba8420`, can mutate/insert through a helper, and clears `needsUpdate`. The callback-shaped arguments resemble noun-data callbacks for create, clear, add, filter, and noun ID, but the Ghidra boundary prevents exact function identity.

Representative callers include `00acd9a0`, `00ace2c0`, `00b25f40`, `00b25fe0`, `00ba0080`, and `00bf9820`.

### 3.8 `01021300` — `FUN_01021300`

| contract item | characterization |
|---|---|
| category | `LAZY_INITIALIZED_GLOBAL` |
| call shape | no arguments; returns a validated cached pointer |
| return contract | `cEmpire*`; cache is lazy and reference-managed |
| callers | 182 total; 47 gameplay |
| lifecycle | cache mutation and virtual AddRef/Release calls occur in this root |
| state | current player ID and current empire identity |
| confidence | high |
| boundary | preserve validation and cache-refresh ordering |

The root reads `Simulator::sSpacePlayerData+0x18` as the player ID and `+0x1c` as the intrusive cache pointer. ID `-1` returns null. If the cache is absent or the cached `cEmpire+0x84` differs from the current ID, the root calls `00b3d2a0`, then `00ba9370`, replaces the cache, and invokes the virtual AddRef/Release slots. Representative consumers include `00b25fb0`, `00ba0080`, `00c32cd0`, `00d01ff0` alliance, and `00febce0` mission-color logic.

### 3.9 `01021080` — `FUN_01021080`

| contract item | characterization |
|---|---|
| category | `DIRECT_STATE_ACCESSOR` |
| call shape | no arguments; returns EAX directly |
| return contract | exact SDK enum `SpaceContext` from `Simulator::sSpacePlayerData+0x10` |
| callers | 175 total; 38 gameplay |
| lifecycle | no calls, allocation, or mutation observed; no null guard |
| state | current space navigation context |
| confidence | high |
| boundary | preserve enum values; do not treat the value as a pointer |

SDK values are `None=-1`, `Planet=0`, `SolarSystem=1`, and `Galaxy=2`. Representative consumers include `00aeb3e0`, `00ad23c0`, `00b28ec0`, `00b444c0`, and `00b4a720`.

### 3.10 `00b25fb0` — `FUN_00b25fb0`

| contract item | characterization |
|---|---|
| category | factory/owner accessor or registry bridge |
| call shape | ECX context plus an ambiguous stack fallback |
| return contract | game-data/civilization object; exact dynamic subtype unknown |
| callers | 100 total; 36 gameplay |
| lifecycle | no direct allocation or mutation observed |
| state | resolves the current player's political ID toward game-data/civilization state |
| confidence | medium |
| boundary | do not select a concrete subtype for the returned object |

The root calls `01021300`, reads the cached `cEmpire` political ID at `+0x84`, and then calls `00b25f40`. Complete representative consumers are `00ae2f70`, `00aebe90`, `00bf9820`, and `00c94470`; the supplied evidence also contains the incomplete address token `00bba?`, which is not promoted to a graph node. The downstream `cGameData`/civilization subtype remains unresolved.

### 3.11 `00ba9370` — `FUN_00ba9370`

| contract item | characterization |
|---|---|
| category | `REGISTRY` |
| call shape | ECX `cStarManager`/context plus a 32-bit stack ID |
| return contract | raw `cEmpire*`; the loaded SDK map value is `intrusive_ptr<cEmpire>`; null when absent |
| callers | 136 total; 35 gameplay |
| lifecycle | read-only map lookup; no allocation or mutation observed |
| state | empire registry keyed by 32-bit ID |
| confidence | high map mechanics and SDK field names |
| boundary | preserve lower-bound semantics and null result |

The context map is `cStarManager+0x150`, with end at `+0x154`. The root uses `00e5c780` for unsigned lower-bound, then returns node payload `+0x14` or null. The loaded SDK describes `mEmpires` as `map<uint32_t,intrusive_ptr<cEmpire>>`. Representative consumers include `00ae9040`, `00ae9590`, `00b20790`, `00ba0080`, `00bba2a0`, and `01021300`.

## 4. Structures and field maps

Offsets below are evidence records, not a declaration of a complete replacement layout. “Unknown” is intentional where the supplied evidence does not establish a type or field name.

| structure | size or boundary | known field/offset map | evidence level |
|---|---|---|---|
| EASTL map layout | map container and node offsets only | end `+0x04`; root `+0x0c`; node key `+0x10`; node payload `+0x14` | `SUPPORTED` |
| `SpacePlayerData` | `0x34` | active planet `+0x04`; context `+0x10`; player ID `+0x18`; empire cache `+0x1c` | `SUPPORTED` |
| `SpaceContext` | `4` | values `None=-1`, `Planet=0`, `SolarSystem=1`, `Galaxy=2` | `CONFIRMED` |
| `cEmpire` | `0x158` | `mPoliticalID +0x84` | `SUPPORTED` |
| `cGameInputManager` | `0x114` (276), vtable size `0x6c` (27 slots) | vtable `+0x00`; `mLastGameMode +0x18`; `mCurrentGameMode +0x1c`; maps `+0x28`, `+0x44`; mouse `+0x68`, `+0x6c`; input regions `+0x74`, `+0x90`, `+0xc0`; strings `+0xdc`, `+0xec`; vector `+0xfc`; integer `+0x110` | `CONFIRMED` |
| `cGameNounManager` | `0x11c` | `mNouns +0x78`; `mNounMap +0x98` | `SUPPORTED` mechanics; `INFERRED` class association |
| `cStarManager` | `0x22c` | `mEmpires +0x150`; map end `+0x154` | `SUPPORTED` |
| `tGameDataVectorT<cGameData>` | `0x18` | `needsUpdate +0x00`; `begin +0x04`; `end +0x08`; `capacity +0x0c` | `SUPPORTED` |
| `DAT_0167eae0` global slot | 4-byte value | absolute `0x0167eae0` | `SUPPORTED` |
| `DAT_0167eae4` global slot | 4-byte value | absolute `0x0167eae4` | `SUPPORTED` |
| `DAT_0167eaec` global slot | 4-byte value | absolute `0x0167eaec` | `SUPPORTED` |
| `DAT_0167eaf8` global slot | 4-byte value | absolute `0x0167eaf8` | `SUPPORTED` |
| `unknown 00b1fdb0 owner/context` | type and size unresolved | owner field `+0x54` | `SUPPORTED` offset; `INFERRED` meaning |
| `unknown 00b1fdb0 returned object` | type and size unresolved | `+0xc0`, `+0xd8`, `+0x55c`, `+0xb20` | `SUPPORTED` offsets; `INFERRED` meanings |
| `unknown 00b1fdb0 nested object` | type and size unresolved | `+0x61c`, reached through returned object `+0xb20` | `SUPPORTED` offset; `INFERRED` meaning |
| `00b5b800` forwarded object | type and size unresolved | forwarded field `+0x20` | `SUPPORTED` offset; `INFERRED` identity |

## 5. Representative callers and subsystem map

| subsystem/domain | primary roots | representative evidence |
|---|---|---|
| global Simulator services | `00b3d300`, `00b3d2a0`, `00b5b800` | high fan-in, many discarded returns, shared global slots, scalar/pointer ambiguity |
| input and mode routing | `00b3d350` | `01053d00` passes the manager to input behavior and copies three floats |
| space navigation | `01021260`, `01021080` | active-planet pointer and context enum are separate direct state reads |
| player/empire identity | `01021300`, `00b25fb0`, `00ba9370` | lazy cache validation, political-ID resolution, and empire map lookup |
| live noun/object registry | `00b21340` | noun map, vector materialization, linked-list state, and callback-shaped arguments |
| opaque current-player/object handles | `00b1fdb0` | same return is used as scalar/action handle and pointer-like object |
| container prerequisite | `00e5c780` | unsigned lower-bound over EASTL map layout; not a gameplay root |

The representative set is intentionally bounded. It identifies consumer shapes for interface characterization and is not a complete caller inventory.

## 6. State-domain model

The shared state can be modeled as six cooperating domains:

1. **Service handles:** `00b3d300` and `00b3d2a0` expose unresolved global service/manager values; `00b5b800` is a separate scalar/opaque forwarding path and is not modeled as a direct singleton.
2. **Input/mode routing:** `00b3d350` exposes a named `cGameInputManager*` with explicit mode, input-region, mouse, string, and vector offsets.
3. **Space navigation:** `Simulator::sSpacePlayerData+0x04` supplies the active planet pointer, while `Simulator::sSpacePlayerData+0x10` supplies the `SpaceContext` enum.
4. **Player/empire identity:** `Simulator::sSpacePlayerData+0x18` and `+0x1c` drive validation and lazy cache refresh; `cStarManager+0x150` provides the empire registry.
5. **Noun materialization:** `cGameNounManager+0x98` indexes noun data, with a `tGameDataVectorT<cGameData>` and unknown noun-list node fields controlling materialization and update state.
6. **Opaque handles:** `00b1fdb0` crosses a boundary whose scalar and pointer-like uses cannot yet be reconciled.

These domains share the Simulator context and must not be flattened into one undifferentiated singleton. The root order is a reconstruction priority, not a claim that all roots have identical ownership or lifetime.

## 7. Prerequisite tree and dependency decisions

```text
00e5c780  generic unsigned map lower-bound prerequisite
├── 00b21340  noun map lookup/materialization
└── 00ba9370  empire registry lookup

00b3d2a0 ──┐
            └── 01021300  lazy cEmpire cache validation/refresh
00ba9370 ──┘
00b3d2a0 ─────── 00b25fb0  current-player political-ID bridge
00b21300 ────── 00b25fb0  current-player political-ID bridge

00b3d320 ── DAT_0167eaec ──> 00b5b800 ──tail-jump──> 00a42730 (+0x20)
00e5c780 + 00ba8420 ───────> 00b21340
```

`00e5c780` takes an EASTL map, an output iterator pointer, and a key pointer. It performs unsigned lower-bound rather than an exact-find assertion. The map fields used by the supplied evidence are end `+0x04`, root `+0x0c`, node key `+0x10`, and node payload `+0x14`. It has 239 callers and is a generic container prerequisite only.

`00b3d320` supplies the global read used by `00b5b800`; `00a42730` reads the forwarded object's `+0x20`; `00ba8420` participates in the noun-data mutation/insertion path. Their complete contracts are intentionally not expanded into primary roots.

## 8. Boundary decisions

- The Phase-1 product of this reconnaissance is an interface freeze: signatures, storage relationships, field offsets, null/handle semantics, and dependency order.
- `00b3d300` and `00b3d2a0` return raw global values; the return may be discarded by callers, so the interface cannot assume a service object is used on every call.
- `00b5b800` is treated as a scalar/opaque handle until consumer evidence proves pointer semantics. Its `0xffffffff` null path is preserved.
- `00b3d350` is the only primary root with a named SDK accessor and an explicit return type in the supplied evidence. The returned input manager is treated as borrowed unless ownership evidence is added.
- `01021260` is a null-guarded direct accessor; allocation is not moved into it. `01021080` is a direct enum value accessor without a null guard.
- `01021300` owns lazy cache mutation and reference-management calls; it must not be reduced to a plain field read.
- `00b21340` is mapped to noun data at the mechanics level, but its exact `cGameNounManager::GetData` identity is not proven because of the Ghidra function boundary.
- `00ba9370` preserves lower-bound plus null behavior. The helper is not relabeled as an exact find.
- `00b1fdb0` receives no provisional player-ID or concrete pointer type.
- No allocator, vtable implementation, input behavior, map implementation, or service implementation is part of this deliverable.

## 9. Contradictions and unresolved questions

1. `00b1fdb0` is consumed as both a scalar/action handle and a pointer-like object with vtable-style field access. The old `gamemode-state-player-id` interpretation is contradicted by the mixed usage; its exact calling convention is also unresolved.
2. The old `message-handler-registration` interpretation of `00b21340` is superseded by the noun-map/vector mechanics. Exact `cGameNounManager::GetData` function/address identity remains unproven.
3. `00b3d300` and `00b3d2a0` have many callers that discard their return, so high fan-in alone does not establish a universal service-pointer contract.
4. `00b5b800` has scalar/opaque-handle consumers despite a forwarding path that reads a field through ECX. It is not a proven direct singleton.
5. `00b3d2a0` has apparent pushed arguments near the root, but those arguments belong to following helpers; the root itself is no-argument.
6. The exact pointee types, allocator relationships, ownership rules, and vtable identities for the unnamed roots remain unknown. Offset evidence is kept separate from semantic type evidence.
7. No runtime trace, boot oracle, or differential test result is available for this set. All claims remain static.

## 10. Recommended Phase-1 reconstruction packages

These are interface and characterization packages, not implementation tasks.

| order | package | roots/helpers | package output | stopping condition |
|---:|---|---|---|---|
| 1 | `global-service-slots` | `00b3d300`, `00b3d2a0`, `00b5b800` | raw global-slot contracts, null/handle rules, representative return-use matrix | no concrete service type is assigned without new structural evidence |
| 2 | `input-boundary` | `00b3d350` | `cGameInputManager*` field map and input consumer boundary | no input behavior or ownership is invented |
| 3 | `space-navigation` | `01021260`, `01021080` | active-planet and `SpaceContext` direct accessors | planet allocation remains external to the accessor |
| 4 | `empire-identity-cache` | `01021300`, `00ba9370`, `00b25fb0` | ID validation, lazy cache refresh, registry lookup, and political-ID bridge | dynamic game-data subtype remains unknown |
| 5 | `noun-registry-materialization` | `00b21340`, `00e5c780`, `00ba8420` | noun map/vector/list contract and callback-shaped argument boundary | exact `GetData` address identity remains unresolved |
| 6 | `opaque-handle-boundary` | `00b1fdb0` | owner-offset and mixed consumer-use matrix | no player-ID or pointer type is selected |

Package 1 and package 5 are foundational for dependent gameplay characterization. Package 2 and package 3 have the strongest direct field contracts. Package 6 should remain an explicit unknown until a new evidence source resolves the scalar/pointer contradiction.

## 11. Handoff checklist and source boundary

A future engineer should preserve the following invariants when consuming this interface:

- Keep the 11-root `root_order` unchanged in machine-readable projections.
- Keep `00e5c780` under prerequisite helpers, not the primary root list.
- Keep field offsets, absolute global addresses, semantic interpretations, and evidence levels in separate records.
- Keep `00b1fdb0`, `00b5b800`, and the unnamed global roots type-open.
- Preserve lower-bound/null behavior for map bridges and lazy cache validation for `01021300`.
- Do not promote static evidence to runtime evidence without a trace or differential result.

Repository-relative sources are `docs/analysis/reconstruction-readiness.md`, `knowledgegraph/triage/reconstruction-readiness-f0e310e0.json`, `knowledgegraph/triage/summary-f0e310e0.triage-v6.json`, `knowledgegraph/triage/xrefs-2540f2ca.tsv`, and `knowledgegraph/triage/xrefs-2540f2ca.summary.json`. No historical triage artifact, `SPORE/` file, or replacement implementation is modified.
