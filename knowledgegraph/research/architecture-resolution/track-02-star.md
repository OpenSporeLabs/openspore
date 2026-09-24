# Track 02 — star-manager, empire registry, and current-player cache

## Result

**Classification:** `UNRESOLVED_BUT_SAFE`  
**Resolution:** partial static resolution. Lookup, successor caching, map ownership, insertion, erase, relationship-field ownership, and local teardown are resolved. Physical aliasing of `DAT_0167eae4` and `DAT_0167eb0c` is rejected; value aliasing, publication, and unpublication remain open.

The safe architecture keeps two opaque star-manager ports with explicit lifecycle events and does not treat `0x00ba9370` or `0x01021300` as exact lookup contracts.

## Scope and method

Read-only Ghidra analysis used explicit program `SporeApp.exe`. No Ghidra program mutation, source implementation, runtime/Wine experiment, `SPORE/` access, `knowledgegraph/spore.db` access, or historical-artifact modification was performed. No subagent interface was exposed. The evidence record separates three current static lanes—Track 2 decomp/callgraph, Track 2 structures/globals/map/lifecycle, and the separate `followup-03-root-publication` static root search—from historical root-closure/adjudication context. Historical derivatives were not counted as fresh binary evidence; no community evidence was used.

## Allowed taxonomy

- Artifact classifications: `ARCHITECTURE_CHANGING`, `RESOLVED_SUPPORTED`, `UNRESOLVED_BUT_SAFE`, `UNKNOWN`; the sole selected value is `UNRESOLVED_BUT_SAFE`.
- Hypothesis statuses: `SUPPORTED`, `SUPPORTED_WITH_ALIAS_LIMIT`, `REJECTED`, `REJECTED_AS_ONE_CHAIN;_RELATIVE_ORDER_UNRESOLVED`, `REJECTED;_FALLBACK_CONTRACT_SUPPORTED`, `UNRESOLVED`, `UNRESOLVED_NOT_SUPPORTED_AS_FACT`, `PLAUSIBLE_BUT_UNPROVEN`, `PLAUSIBLE_GENERIC_MECHANISM_NO_IDENTIFIED_PATH`, and `PLAUSIBLE_FOR_CANONICAL_LIVENESS_UNPROVEN`.
- `UNRESOLVED_BUT_SAFE` permits publication/equality to remain open only when the minimum-safe semantics are independent of the unresolved outcome.

## Nine-step adversarial record

| Step | Action | Result |
|---|---|---|
| 1 | Enumerate all material hypotheses | Permanent alias, phase rebinding, distinct phase instances, indirect common publication, obsolete/unpublished slot, exact find, lower bound, exact cache, successor-tolerant cache, unified invalidation, relationship alias, and null-only no-empire behavior were tested. |
| 2 | State exact predictions | Predictions included writer/equality evidence, post-lookup ID validation, node-key checks before erase, cache clearing during map teardown, and distinct nonzero slot values. |
| 3 | Collect current static evidence | Getter/global xrefs, map helper/wrapper, cache branches, allocation/insertion, erase, initialize/shutdown, vtables, destructors, no-empire bridge, exact root literals, bounded P-code publication, and star accessor co-call topology were inspected. |
| 4 | Separate historical context | Prior root-closure reports supplied the exact-find correction and unresolved alias blocker as context; repeated derivatives were not counted as fresh binary evidence. |
| 5 | Mark support and contradiction | Exact-find, exact-cache, unified invalidation, and null-only fallback claims were rejected. Lower-bound and successor-tolerant cache claims survived. Physical slot aliasing was rejected; value equality/publication remained unresolved. |
| 6 | Audit independence and repetition | Current static lanes were kept separate from historical context. SDK singleton wording, sparse canonical fan-in, old exact-find labels, and “no identified writer means immutable” were rejected as reasoning shortcuts. |
| 7 | Perform smallest separators | Direct/global/literal/table/P-code scans, star pair co-calls, the `0x0167ea80` base test, helper/wrapper comparison, cache-miss inspection, erase inspection, and owner-teardown comparison were performed. |
| 8 | Record runtime feasibility | No runtime was justified or run. The historical corpus does not reach empire/space lifecycle; static separators already decide the minimum semantics. |
| 9 | Architecture-dependence test | Equal, rebound, distinct-phase, and obsolete-canonical outcomes require different ownership/publication designs. A dual-port interim boundary is safe without selecting among them. |

## Competing hypotheses

| ID | Hypothesis | Status | Decisive evidence |
|---|---|---|---|
| H1 | The two star slots always hold the same pointer | Unresolved, unsupported as fact | Distinct four-byte words; no direct/equality/alias store, no star pair co-call, and zero bounded concrete target stores |
| H2 | The slots alias only during active phases and are rebound | Plausible, unproven | Missing publication and distinct consumers permit it; no direct or bounded concrete rebind chain found |
| H3 | The slots hold phase-specific distinct managers | Plausible, unproven | Direct chains are port-specific; no unequal non-null observation |
| H4 | A common computed/bulk publisher fills both | Generic mechanism remains possible | Manager registration requires some publication model, but `0x0167ea80` was rejected and literal/table/P-code scans found no concrete publisher |
| H5 | The canonical slot is obsolete/unpublished in exercised modes | Plausible liveness alternative, unproven | Canonical getter has one sparse executable thunk data-referenced at `0x0146286c`; no null/dead runtime observation |
| H6 | `0x00ba9370` is exact find | Rejected | `0x00e5c780` is lower bound; wrapper checks only end |
| H7 | `0x00ba9370` is ceiling/lower bound | Supported | Complete missing-key matrix is direct |
| H8 | `0x01021300` validates every lookup result exactly | Rejected | Miss branch stores the lookup result without checking its `+0x84` |
| H9 | The cache can retain and return a successor | Supported | Direct miss path and repeated-mismatch behavior |
| H10 | Map erase, manager teardown, and cache/global teardown are one invalidation chain | Rejected | Map and cache owners clear separate fields; no global unpublish found |
| H11 | `cStarManager+0x204` always equals `DAT_0167eb14` | Unresolved | Field-owned manager lifecycle is direct; canonical global has no writer/equality chain |
| H12 | The no-empire bridge always returns null or a concrete civilization | Rejected | Null current empire returns a caller stack fallback unchanged |

## Primary separating observation

A full direct-reference, exact-literal, table, bounded computed-store, and pair co-call scan found:

- `0x00b3d2a0: mov eax,[0x0167eae4]; ret`
- `0x00b3d2c0: mov ecx,[0x0167eae4]; jmp 0x00c4f030` (read instruction at `0x00b3d2f2`)
- `0x00b3d3a0: mov eax,[0x0167eb0c]; ret`
- no other direct references to either word;
- no direct writer, equality operation, alias store, static pointer initializer, or unpublish path;
- exact four-byte literals occur only in those accessor instructions, with no exact data occurrence for the accessor entry addresses;
- bounded concrete P-code propagation found zero target addresses and zero target stores;
- no recovered function co-calls both star accessors;
- both loaded words are zero.

This proves physical non-aliasing. It does not prove unequal runtime values. The negative publication search is bounded: it does not exclude opaque pointer-derived stores, external or runtime writes, unresolved code, or opaque bulk operations.

The `0x00b5ca50` thunk is data-referenced from `0x0146286c`; it calls the canonical getter and dispatches through the returned object's vtable. It is a getter consumer, not a root-publication or aliasing mechanism.

The arithmetic candidate `0x0167ea80+0x64=0x0167eae4` and `+0x8c=0x0167eb0c` was tested and rejected as a publisher: `0x00b3cf40` initializes only twelve floats at `+0x00..+0x2c`, while `0x00b3ce80/0x00b3cec0/0x00b3cf00` read that float array. It is not a manager-pointer table.

## Exact star-slot lower bound

The defensible star-pair boundary is:

- **Physical aliasing:** rejected; the two roots are distinct four-byte words.
- **Publication:** 2 unresolved slot states, one for each root.
- **Unpublication/teardown:** 2 unresolved slot states, one for each root.
- **Value equality:** 1 unresolved relation between the two root values.

A single opaque function could publish or clear both slots, so these are slot-contract obligations, not a count of undiscovered writer functions. The direct/literal/table/P-code/lifecycle negatives do not prove that no such function exists. The safe interim model is two opaque ports with explicit publication, replacement, and unpublication events; it never merges the ports.

## Resolved lifecycle chain

### Construction and registration

1. `0x00b60d80` allocates `0x22c` bytes with factory type `0x01463cfc`.
2. `0x00bae490` constructs `cStarManager`, initializes refcount/base fields, `mEmpires +0x150..+0x168`, `mNextPoliticalID +0x1d4`, and null `mpRelationshipManager +0x204`.
3. The manager is placed in simulator service-registration state.
4. Primary vtable `+0x08` invokes `0x00bb6a30`, which creates and initializes a `cRelationshipManager`, AddRefs/stores it at `+0x204`, and Releases the old non-null value.

This is object construction and registration, not a recovered direct write to either global star slot.

### Empire allocation and insertion

`0x00bb1340 -> 0x00baf0b0`:

1. Allocate `0x158` bytes.
2. Construct through `0x00c34830`; the constructor initializes `cEmpire+0x84` to `-1`.
3. Write the requested political ID to `+0x84`.
4. Call `0x00dd85c0`, the intrusive-map access/upsert helper.
5. AddRef the new empire, store it in the map payload, and Release the old equal-key value.

The map owns the stored `intrusive_ptr<cEmpire>` reference. Key and payload identity are established together on this creation path.

### Lookup

`0x00ba9370` is not exact find:

| Input | Result |
|---|---|
| `0xffffffff` | null before map traversal |
| exact key exists | that empire |
| key absent, greater key exists | first greater key’s empire |
| key absent, no greater key | null |
| null manager | no guard; undefined/crash risk |

`0x00e5c780` returns the first unsigned key `>= request`; `0x00ba9370` checks only the end sentinel and returns node payload `+0x14`. It performs no AddRef, Release, insertion, or equality check.

The safe exact postcondition is:

```text
result != null && result->mPoliticalID(+0x84) == requested_id
```

### Current-player cache

`0x01021300` reads:

- request: `SpacePlayerData+0x18`;
- owned cache: `SpacePlayerData+0x1c`;
- identity: `cEmpire+0x84`;
- manager source: alternate `DAT_0167eae4` through `0x00b3d2a0`.

Replacement order is exact:

1. lookup;
2. AddRef new when new is non-null and differs from old;
3. store new;
4. Release old when non-null;
5. return new.

The hit branch checks identity, but the miss branch does not check the returned empire before storing it.

| Case | Result |
|---|---|
| request `0xffffffff` | return null; old cache and reference remain untouched |
| cached ID equals request | borrowed hit |
| exact key exists | cache exact empire |
| missing request, greater key exists | cache and return the mismatched successor |
| missing request, map end | store null and Release old |
| successor already cached | repeat lookup; same pointer means no reference churn |
| cached empire erased but ID unchanged | can continue hitting because membership is not validated |

A cache-owned reference can keep an erased empire alive, so the immediate result is stale registry membership rather than guaranteed dangling storage.

### Single erase and full teardown

`0x00bad7a0` is the bounded empire-map eraser:

1. read `cEmpire+0x84`;
2. lower-bound `mEmpires +0x150`;
3. if non-end, unlink and decrement `+0x164`;
4. Release node payload `+0x14`;
5. free the node.

It does not compare the node key. If the key is absent and a greater key exists, it removes that successor. The path is safe only under a current-membership invariant.

`0x00babe70`, reached through the cStarManager refcount destructor chain, passes the mEmpires root at `+0x15c` to `0x00d0c930`. That helper recursively Releases every empire payload and frees every map node.

`0x01022460` is a separate `SpacePlayerData` teardown: it clears/releases `+0x1c` and resets `+0x18` to `0xffffffff`. Neither the single eraser nor the manager destructor writes the player cache.

No standalone political-ID rekey transaction was found. `0x00c359a0` writes `cEmpire+0x84`, but its one recovered caller is the creation/materialization path; it is not evidence of a general erase-old/change-ID/insert-new API.

## Relationship manager at `+0x204`

- `0x00c4f030` returns `[manager+0x204]` borrowed.
- `0x00b3d2c0` is state-selected: it may return `+0x204`, `SpacePlayerData+0x0c`, or null.
- `0x00bb6a30` AddRefs/stores a newly created relationship manager at `+0x204`, Releases the old value, and initializes the new value.
- `0x00bb7250` shuts down, clears, and Releases `+0x204`.
- The destructor invokes the relationship-manager teardown virtual through `+0x204`.

`0x00b3d3c0` returns a distinct `DAT_0167eb14` global with one direct read and no direct writer. Equality with `+0x204` is unresolved; the field remains manager-owned regardless.

## No-empire behavior

`0x00b25fb0` has two distinct branches:

- `0x01021300() == null`: return the caller’s stack fallback word unchanged;
- current empire non-null: read `cEmpire+0x84` and call `0x00b25f40`.

`0x00b25f40` returns the first materialized `kCivilization` game-data record whose political ID matches, otherwise null. The fallback is not used for a live empire with no matching civilization. Its exact type is unresolved in this track.

Because the cache can return a successor, the bridge can resolve the successor’s actual political ID rather than the original request.

## Ownership and roots sharing storage

| Object/state | Owner | Returned-pointer contract |
|---|---|---|
| `DAT_0167eae4` | distinct global word; physical aliasing rejected; publication/unpublication unresolved | raw borrowed manager pointer |
| `DAT_0167eb0c` | distinct global word; physical aliasing rejected; publication/unpublication unresolved | raw borrowed manager pointer |
| selected manager `mEmpires +0x150` | selected `cStarManager` | map owns intrusive empire references; lookup borrows |
| `SpacePlayerData+0x1c` | `SpacePlayerData` | one owned intrusive reference; accessor returns borrowed |
| selected manager `+0x204` | selected `cStarManager` | one owned intrusive reference; reader returns borrowed |

No cross-slot shared `mEmpires` storage is proven. A selected receiver’s `+0x150` is its own map. Value equality between the two manager slots, and equality between `+0x204` and `DAT_0167eb14`, remain open; only physical storage aliasing of the two root words is rejected.

## Independence and repeated assumptions

Fresh Track 2 decomp/callgraph and structure/global/lifecycle observations are separate static evidence surfaces. The separate `followup-03-root-publication` lane adds direct/literal/table, bounded P-code, star pair co-call, and root-lifecycle observations; its noun findings are excluded from Track 2. Historical reports identify the prior contradiction but are context only, and repeated lower-bound/cache statements are one source family rather than multiple independent binary observations.

The following were explicitly not promoted:

- SDK `cStarManager::Get` naming does not prove value alias equality.
- A singleton concept does not identify the publisher of two distinct words.
- No direct, exact-literal, exact-table, or bounded concrete P-code writer does not prove immutability, null liveness, or absence of opaque/runtime publication.
- Sparse canonical fan-in does not prove the canonical path is dead.
- A hit-time cache ID check does not prove post-lookup exact validation.
- A separate cache teardown does not prove erase-time invalidation.
- Creation-scoped ID assignment does not prove a general rekey API.

## Architecture-dependence test

| Slot outcome | Exact architecture decision |
|---|---|
| Always equal | one manager/registry owner; getters are aliases; one map, relationship field, and teardown order |
| Equal only during active phases | two publication ports plus explicit rebind/phase ordering and cache policy |
| Distinct phase instances | manager-scoped maps/relationship state; current cache explicitly alternate-scoped |
| Canonical obsolete/unpublished | alternate is the live gameplay registry; no invented canonical fallback |

Outcome-independent decisions are stronger: lower-bound lookup, successor-tolerant cache, independent owners, membership-guarded erase, and the explicit fallback boundary must not be collapsed.

### Minimum safe semantics

1. Keep two opaque selected-manager ports until publication/equality is observed.
2. Expose publication, replacement, and unpublication as explicit lifecycle events even though the current mechanism is unresolved.
3. Name registry lookup `ceilingByPoliticalId` unless the caller adds an exact postcondition.
4. Treat the current-player cache as identity-validating, not membership- or generation-validating.
5. Keep map erase and player-cache invalidation separate.
6. Keep relationship state selected-manager-owned; do not assume canonical-global alias.
7. Keep the no-empire fallback explicit and type-open.
8. Do not use borrowed manager/registry/relationship/cache pointers after owner teardown without a new guarantee.

### Deferral safety

Safe to defer: runtime value equality, exact direct/computed/table/bulk/runtime publication, canonical liveness, and relative teardown/unpublication order.

Unsafe to defer: merging slots as proven value aliases, exact-find semantics, exact-result cache semantics, erase-time cache invalidation, `+0x204`/canonical relationship alias, or a guaranteed null/concrete no-empire return.

## Blockers

- No direct, exact-literal, exact-table, bounded concrete P-code, or inspected lifecycle publisher/unpublisher for the two star slots; opaque/runtime publication remains open.
- No static or runtime equality observation distinguishes permanent value aliasing, phase rebinding, and distinct instances.
- Exact star-slot lower bound: two publication states, two unpublication/teardown states, and one value-equality relation remain unresolved.
- The unowned `0x00b5ca50` canonical thunk has no recovered owner/caller chain.
- No proven manager/cache/global teardown order.
- `+0x204` versus `DAT_0167eb14` alias remains unresolved.
- No general rekey transaction was found.
- The fallback’s exact type remains unresolved.
- No MSVC RTTI and current Ghidra decomp gaps bound exact class/owner claims.

## References and limitations

Primary committed sources:

- `knowledgegraph/research/architecture-resolution/followup-03-root-publication.json:103-186,188-199,203-254,329-394`
- `knowledgegraph/research/architecture-resolution/followup-03-root-publication.md:26-39,67-117`
- `knowledgegraph/research/root-closure/track-e-empire-chain.md:46-117,190-205`
- `knowledgegraph/research/root-closure/followup-global-slots.md:14-22,102-143,199-245`
- `knowledgegraph/research/root-closure/followup-space-lifecycle.md:7-16,117-128,180-191`
- `knowledgegraph/research/root-closure/cross-root-relationships.md:57-65,85-95,178-206`
- `knowledgegraph/research/data-model/06-empire-space-data.json:175-180,394-438`
- `docs/analysis/simulator-shared-state-interface.md:143-156,173-201`
- `docs/analysis/conflict-adjudication.md:76-82,207-223`
- `.spore-analysis/ghidra-exports/structs_fields.tsv:11458-11514`
- `.spore-analysis/ghidra-exports/sdk_functions.tsv:1243-1289`

Primary Ghidra anchors include `0x00b3d2a0`, `0x00b3d2c0`, `0x00b3d3a0`, `0x00b5ca50`, data reference `0x0146286c`, `0x00ba9370`, `0x00e5c780`, `0x01021300`, `0x00b25f40`, `0x00b25fb0`, `0x00b60d80`, `0x00bae490`, `0x00baf0b0`, `0x00bad7a0`, `0x00bb6a30`, `0x00bb7250`, `0x01022460`, `0x00babe70`, and `0x00d0c930`.

No runtime evidence was used. Community evidence was not used. No source implementation was performed. Full predictions, support/against evidence, independence, blockers, and source addresses are in `knowledgegraph/research/architecture-resolution/track-02-star.json`.
