# Adversarial review — identity, ownership, and lifecycle ordering

## Scope and evidence boundary

This review covers the seven isolated reports in this directory, with extra weight on Tracks D, E, F, and G:

- `track-a-root-identity.md`
- `track-b-noun-publication.md`
- `track-c-star-publication.md`
- `track-d-identity-ownership.md`
- `track-e-cross-root-callers.md`
- `track-f-lifecycle-ordering.md`
- `track-g-edge-cases.md`

It reconciles them with the authoritative root, lifecycle, mode, and persistence artifacts they cite, including `docs/analysis/simulator-root-closure.md`, `docs/analysis/architecture-blockers.md`, `docs/analysis/architecture-decisions.md`, `docs/analysis/semantic-blueprint.md`, `docs/analysis/gameplay-data-model.md`, `docs/analysis/gameplay-state-machines.md`, `docs/analysis/gameplay-transition-map.md`, `docs/analysis/serialization-model.md`, `knowledgegraph/research/architecture-resolution/track-01-noun.md`, `track-02-star.md`, `followup-03-root-publication.md`, `followup-06-persistence.md`, and the root-closure follow-ups.

No original-process gameplay, mode, teardown, or save/load trace is present. The reports are static analyses of the same pinned binary, not independent runtime votes. Repetition of the same xrefs, layouts, or conclusions must not be counted as corroboration. SDK names, singleton wording, fan-in, and image-time zero bytes are semantic priors, not runtime identity evidence.

## Executive verdict

OpenSpore does **not** need, and must not assume, one universal noun/star identity, one universal manager owner, or one universal lifecycle. The minimum safe model is a layered identity and ownership contract:

1. Content identity, domain IDs, live-object identity, registry identity, pointer/handle identity, and persistence identity remain separate typed domains.
2. A selected noun or star manager owns its local registries and caches; a root slot is an observation port, not proof of ownership or lifetime.
3. Registry membership, object liveness, cache residency, and snapshot validity are different states.
4. Invalidation, eviction, clear, registry erase, deferred reclamation, owner teardown, and root unpublication are separate operations.
5. A transition order is not a survival rule. A serialization capability is not a field-survival rule. A raw pointer is not a durable save identity.
6. OpenSpore should make publication, rebind, invalidation, rekey, and teardown explicit in its own clean-room lifecycle policy rather than inventing an original ABI for the unresolved portions.

The most important unresolved facts are the four root-slot publishers, runtime equality/liveness of each alternate/canonical pair, cross-root teardown order, general rekey behavior, and the exact original save/load restore order. These do not block a host-side semantic model, but they block original root/liveness/persistence compatibility claims.

## Evidence strength

| Claim | Strength | Adversarial assessment |
|---|---|---|
| Four noun/star root words are physically distinct | **High static** | Direct accessor bodies and addresses establish physical non-aliasing only. This does not establish four owners, four lifetimes, or unequal runtime values. See Tracks A, D, F, G and `followup-03-root-publication.md:15-33,84-91`. |
| Alternate noun/star getters are manager-compatible receivers | **High for selected receiver use; medium for class identity** | The noun result is passed into `0x00b21340`, and the star result reaches `mEmpires`/`+0x204` consumers. This is not root publication or exact class proof. `track-a-root-identity.md:60-94`; `track-d-identity-ownership.md:50-113`. |
| Root getters return borrowed raw values | **High static** | The bodies contain no validation, AddRef, Release, allocation, or lock. A later non-null read still does not prove liveness. `track-d-identity-ownership.md:129-151`; `track-g-edge-cases.md:34-46`. |
| Noun/star manager-local ownership and intrusive references | **High static** | The lists, maps, vectors, and explicit AddRef/store/Release paths establish selected owner fields. They do not establish the root publisher or complete object-owner graph. `track-b-noun-publication.md:60-129`; `track-c-star-publication.md:86-201`. |
| Noun and empire lookups are lower-bound/ceiling operations | **High static** | The wrappers check the end sentinel rather than the returned key. Exact callers need a postcondition. `track-b-noun-publication.md:217-239`; `track-c-star-publication.md:255-265`; `track-f-lifecycle-ordering.md:194-212`. |
| App mode switch order | **High for the concrete helper, not for listener timing** | `0x007d85b0` proves local `OnExit -> active-index write -> exit announcement -> OnEnter -> enter announcement` order. Message delivery timing and root/state survival remain unresolved. `track-f-lifecycle-ordering.md:253-291`. |
| Noun-manager construction before star-manager construction | **High local conditional order** | The linear `0x00b60d80` body constructs, initializes, and registers the noun manager before the star manager, then reads the alternate star root later. This is not proof that either global slot was written. `track-f-lifecycle-ordering.md:72-147`. |
| Star-record generation preserves record identity | **High local static** | The inspected regeneration path resets/reuses the existing record and calls planet generation. It does not prove a new record allocation or full cross-file restore identity. `track-c-star-publication.md:386-413`; `track-f-lifecycle-ordering.md:471-490`. |
| Root equality, liveness, publication, and unpublication | **Unresolved** | Direct scans are bounded negatives. They do not select always-equal, phase-rebound, distinct-instance, stale, or opaque-publication hypotheses. `track-d-identity-ownership.md:263-277`; `track-f-lifecycle-ordering.md:135-147`. |
| General political-ID rekey | **Unresolved** | Creation-scoped writes and a bounded payload-erase hazard are not a transaction covering map keys, dependent registries, and caches. `track-c-star-publication.md:484-500`; `track-g-edge-cases.md:164-204`. |
| Duplicate noun-cache publication under race/reentrancy | **Conditional static hazard, not observed behavior** | The provisional record is not visibly replaced by the insertion winner, and insertion failure/cleanup is not closed. No race or reentrant event was observed. `track-g-edge-cases.md:119-162`. |
| Original save/load field survival and root restoration | **Unresolved** | Local serializer and replacement bodies exist, but complete field coverage, reference remapping, manager binding, and restore order are not recovered. `track-f-lifecycle-ordering.md:492-542`; `followup-06-persistence.md:17-37,154-187`. |

## Runtime identity and ownership

### Identity is a tuple of scoped meanings, not a value type

The reports converge on a multi-axis model. The minimum identity vocabulary is:

- **Content key:** full packaged `ResourceKey` tuple `(typeID, groupID, instanceID)`. It selects content, not a noun, star, political identity, live object, or cache node. DBPF row order, in-memory field order, serializer declaration order, and the narrower Cell cache key are separate representations. `track-d-identity-ownership.md:32-48`; `knowledgegraph/research/conflicts/track-d-data-serialization.json:14-180,705-834`.
- **Noun category ID:** the `uint32` key used by `0x00b21340` and `GetNounID`. It projects a set of live objects sharing a category; it is not a unique live-instance ID. `mID`, `mDefinitionID`, and `mPoliticalID` are separate object fields. `track-d-identity-ownership.md:50-82`; `track-b-noun-publication.md:101-117`.
- **Star key:** the `StarID`/record key is a registry/domain key. `cStar::mKey`, `cStarRecord::mKey`, grid sector/slot, empire political ID, current-player ID, and ResourceKey are not interchangeable. `track-c-star-publication.md:88-124,126-168`; `track-d-identity-ownership.md:84-113`.
- **Live object identity:** process-local address plus virtual type. The same address can be allocator-reused for a different object; the reference count is lifetime bookkeeping, not identity. `track-d-identity-ownership.md:115-128`.
- **Registry identity:** `(owner, key domain, key)`, not the key alone. The noun map, empire map, star grid, home-star map, current-player cache, and root slots are different registries. `track-d-identity-ownership.md:177-192`.
- **Handle identity:** an owning reference, borrowed pointer, cache lease, or snapshot. A borrowed manager/vector pointer is not ownership; an intrusive element copy can keep an object live after registry removal. `track-d-identity-ownership.md:153-175`; `track-g-edge-cases.md:34-46`.

A single `uint32` “entity ID” API would hide these boundaries and is unsafe. The minimum is a domain-tagged ID or a separate typed value for each identity class.

### Noun ownership is layered, not root-owned

The noun path has at least four ownership levels:

```text
noun factory/type registry
  -> concrete cGameData allocation
  -> selected manager mObjects/mNouns membership
  -> mNounMap vector projection and intrusive element references
  -> borrowed consumer pointer or copied snapshot
```

`0x00b20c60` eagerly links a created object into manager-local owner/list structures and calls `0x00b201a0`. `0x00b21340` lazily creates or refreshes a manager-owned vector record by lower-bound lookup. The returned record is borrowed; element references are managed by the add/clear callbacks. This is strong local evidence, not proof that a root slot points to the manager or that the manager is the only owner of every noun subtype. `track-b-noun-publication.md:131-197,241-275`; `track-d-identity-ownership.md:231-283`.

The two noun root words remain separate observations:

- `DAT_0167eae0` via `0x00b3d300`;
- `DAT_0167eb60` via the SDK-named `0x00b3d400`.

The high fan-in of the alternate path demonstrates use, not ownership or priority. The absence of a direct writer is bounded evidence only. A non-null value can be stale, null, equal to the other value, or point to a phase-specific manager. `track-a-root-identity.md:95-116,128-149`; `track-g-edge-cases.md:253-302`.

### Star ownership is a graph, not one registry or one noun

The star reports correctly reject collapsing the following representations:

- live `cStar`, a `cGameData` noun;
- refcounted/serializable `cStarRecord`;
- `cPlanetRecord` data;
- live/materialized `cPlanet`;
- `cSolarSystem`;
- `cEmpire`;
- manager registries and root slots.

`cStarManager` owns several reference-bearing record collections and a live-planet cache, but `cEmpire` independently owns `cStarRecord` references and `cSolarSystem` points back to its owner star. Replacing the empire-home map entry releases only that map reference; it does not erase the grid, empire vector, or live object. `track-c-star-publication.md:17-58,189-201,272-303,502-513`.

The star root pair has the same physical/value distinction as the noun pair. `DAT_0167eae4` is the alternate receiver used by the current-player cache; `DAT_0167eb0c` is the SDK-named getter. Neither value equality nor the publisher/teardown order is known. `track-d-identity-ownership.md:142-151`; `track-f-lifecycle-ordering.md:449-482`.

Physical separation of `cStar` and `cStarRecord` does **not** prove that their logical identity or association cardinality is different. The safe statement is: distinct physical representations and typed links, with a likely logical association whose one-to-one/one-to-many status is unresolved. This corrects over-strong “distinct identities” wording in parts of Tracks B and C and the blocker reports. `track-c-star-publication.md:153-187`; `blocker-a-adversarial.md:171-184`.

## Exact ordering

The evidence supports several local orderings, but not a single global noun/star lifecycle order.

### Initialization and service construction

Within the conditional body `0x00b60d80`, the local order is:

```text
noun-manager allocation
  -> noun-manager constructor
  -> noun-manager virtual initialization
  -> noun-manager registration append
  -> star-manager allocation
  -> star-manager constructor
  -> star-manager virtual initialization
  -> star-manager registration append
  -> later alternate star-root read
```

This proves construction and registration order only if that body is entered. It does not prove that the four global slots are initialized at those points, that the manager allocation is the selected root, or that root values remain equal afterward. `track-f-lifecycle-ordering.md:72-147`.

### Noun object lifecycle

The strongest local noun sequence is:

```text
factory create
  -> assign runtime object ID
  -> link mObjects and mNouns
  -> invalidate affected projections
  -> lookup/materialize by lower bound
  -> clear dirty vector, scan mNouns, filter/add
  -> return borrowed vector record
```

Destroy is staged:

```text
mark pending/status
  -> retain in field_80
  -> subtype teardown and mNouns unlink
  -> invalidate projections
  -> later mObjects prune and pending-reference release
  -> manager teardown
```

This separates logical removal from reclamation and manager teardown. It does not show root unpublication. `track-b-noun-publication.md:294-365`; `track-f-lifecycle-ordering.md:149-188`.

### Current-player and star lookup order

`0x01021300` has a precise local replacement order:

```text
read requested political ID
  -> sentinel return null without clearing old cache
  -> hit only if cached object field matches request
  -> read alternate star root
  -> ceiling/lower-bound empire lookup
  -> AddRef new, store, Release old
  -> return borrowed result
```

The miss path does not validate the returned empire's political ID. The map eraser and player-cache teardown are separate. This is a stale-membership hazard, not necessarily a dangling allocation, because the player cache owns a reference. `track-c-star-publication.md:515-536`; `track-d-identity-ownership.md:303-338`; `track-g-edge-cases.md:350-377`.

### Mode and world ordering

The concrete App helper order is proven locally, but mode axes remain separate:

- App active mode: old `OnExit`, active-index write, exit announcement, new `OnEnter`, enter announcement.
- Simulator strategy: pending request and separate last/current commits.
- SpaceContext: `SpacePlayerData+0x10`, independently written by `0x01021960` and `0x01022580`.
- Scenario mode: scenario field `+0xcc`, independently switched by `0x00ef12d0`.
- Input mode and Cell lifecycle: separate owners.

No one of these orders implies that noun, star, empire, avatar, or cache state survives the transition. Scenario play teardown reaches noun cleanup, but that is not root unpublication. Space context setup may occur after or before other world work, but its helper-local order is not a complete cross-domain runtime schedule. `track-e-cross-root-callers.md:139-192,246-267`; `track-f-lifecycle-ordering.md:253-364,366-469`.

### Save/load ordering

`FUN_00b28ec0` and `FUN_00b279e0` are strong save/load operation candidates. Their local bodies show stream/database setup, header serialization, service dispatch, close/replacement, and a separate `stars.db.tmp -> stars.db` path. This does not establish the serialized record order, complete object-reference table, manager membership, automatic mode-exit save, or exact restore order. `followup-06-persistence.md:17-37,39-71,154-187`; `track-f-lifecycle-ordering.md:492-542`.

The phase-6 `Write` interface in `0x00cfbc10` is not a save claim. It is an interface call whose receiver is not statically bound to the authoritative persistence bodies. `track-e-cross-root-callers.md:145-165,262-267`.

## Invalidation, erase, and cache eviction

### Noun invalidation

`0x00b201a0` lower-bounds the noun ID and marks the selected payload dirty, then scans cast-compatible records. It does not compare the selected node key with the requested noun ID. Therefore the precise claim is “lower-bound-selected projection invalidated,” not “exact-key invalidation.” `track-b-noun-publication.md:277-292`; `track-g-edge-cases.md:60-82`.

A missing noun key with a greater successor can therefore return/rebuild the successor record using the missing request's filter. Repeated requests can continue using that mismatched record. The map node key is not rewritten by the visible path. `track-f-lifecycle-ordering.md:153-164`; `track-g-edge-cases.md:350-377`.

### The `0x00b21410` contradiction

The reports contain a material contradiction:

- Track B says normal noun destruction does not erase the `mNounMap` key; only manager teardown cleans the whole map.
- Tracks D and F call `0x00b21410` a noun-map erase.
- Track G reports direct disassembly that the helper operates on the manager map at `+0xd0`, checks the payload pointer, and erases that map node; it is not evidence of `mNounMap+0x98` eviction.

The Track G correction is the strongest direct-instruction interpretation and is consistent with Track B's later lifecycle analysis: normal noun removal invalidates the typed vector projection; per-key `mNounMap` eviction is not established. OpenSpore must not model every noun destroy as an unconditional `mNounMap.erase(nounID)`. `track-b-noun-publication.md:367-384`; `track-d-identity-ownership.md:267-281`; `track-f-lifecycle-ordering.md:166-175`; `track-g-edge-cases.md:206-235`.

### Empire map and player cache

Empire lookup, cache hit, map erase, and player-cache teardown are independent layers. A missing political ID can return a greater successor; the cache can retain that successor. A map erase releases the map-owned reference but does not clear `SpacePlayerData+0x1c`; the cache can keep the object alive and return it on a later ID match. This is a current-membership failure, not proof of immediate pointer dangling. `track-d-identity-ownership.md:303-338`; `track-g-edge-cases.md:206-235,253-302`.

### Star records and multiple registries

A star record can be present in the grid, starter/saved/candidate collections, an empire vector, and the home-star map. Removing one collection reference is not a universal erase. Record regeneration reuses the same record/key in the observed path; a new record allocation is not shown. Live-planet reuse is keyed by the separate `cPlanetRecord` association, not by `cPlanet` address. `track-c-star-publication.md:237-319,386-426`; `track-d-identity-ownership.md:340-344`.

### Cache eviction policy

There is no proven universal noun cache eviction operation. The noun path has lazy invalidation and refresh; `0x00b21410` is not evidence of `mNounMap` eviction; manager teardown destroys maps in bulk. The value-returning ModAPI helper copies intrusive element references and can outlive the cache projection, while the low-level record/iterator view is tied to manager/vector lifetime. The star empire map and player cache have different invalidation policies. Resource-manager eviction and replacement remain separate unresolved questions. `track-g-edge-cases.md:206-251`; `docs/analysis/serialization-model.md:109-128,335-364`.

The minimum cache contract therefore needs at least:

```text
lookup cached
invalidate projection
evict/remove record
clear owner cache
release owner
destroy manager storage
```

These are not synonyms. A cache generation should distinguish “the owner still exists,” “the registry entry still exists,” and “the caller’s copied payload references remain valid.”

## Rekey, duplicate publication, and stale handles

### Rekey

The only strong political-ID write paths are creation/materialization-scoped. No general transaction was found that erases the old ordered-map key, writes a new object field, updates dependent registries, and invalidates caches. If a registered empire's field diverges from its node key, lower-bound lookup can return a successor, the ceiling eraser can select the wrong payload, and the player cache can continue matching the changed object field.

OpenSpore must choose one of two safe policies:

1. make a registered domain ID immutable; or
2. mediate rekey through a manager transaction that updates the authoritative map, all dependent registries, cache generations, and observers before publication.

Exposing a raw `SetPoliticalID` on a registered object would preserve the original inconsistency hazard, not model a safe identity system. `track-g-edge-cases.md:164-204`; `track-c-star-publication.md:484-500`.

### Duplicate publication

Two separate hazards exist:

- A noun cache miss creates a provisional vector record, then the insertion helper may return an existing equal-key record. The outer `GetData` path does not visibly switch to the insertion winner or clean up the provisional record. Reentrancy or concurrency is a conditional static hazard, not observed behavior. `track-g-edge-cases.md:119-162`.
- Empire creation is an insert-or-replace operation under an equal political-ID key. The map stores the last completing object and releases the displaced map reference, while a caller may still hold/return the object it created. `track-g-edge-cases.md:131-139`; `track-c-star-publication.md:189-201`.

OpenSpore needs explicit `getOrCreate`/`upsert` semantics. Cache publication must atomically return the winning map-owned record. An upsert must define last-writer-wins, first-writer-wins, or rejection, and a returned object must not be presented as current after replacement. Root duplicate publication is not proven; the same generation/rebind policy should nevertheless be available at the port boundary.

### Stale handles and pointers

A stale result has several possible meanings:

- pointer address is no longer live;
- pointer remains allocated through another owner but is no longer a registry member;
- cached projection is dirty or rebuilt;
- vector record address is retained but its element buffer/iterators changed;
- copied intrusive references are valid snapshots but no longer represent current membership;
- root slot is non-null but points to a destroyed or rebound generation.

The original accessors do not carry generation, membership, or validity metadata. `GetData` returns a borrowed manager-owned record; the value-returning convenience wrapper copies element references. `SpacePlayerData+0x1c` owns an empire reference but validates only the object field, not map membership. The minimum safe model must label these states separately. `track-g-edge-cases.md:253-302,350-391`; `track-d-identity-ownership.md:455-502`.

## Teardown

The evidence supports manager-local teardown, not a total cross-root order:

- noun manager teardown releases maps, lists, vectors, and fields;
- star manager teardown releases relationship state, record collections, empire map payloads, and live-planet state;
- `SpacePlayerData` field teardown clears active planet/star/relationship/current-empire fields;
- root accessors have no validation or ownership transfer;
- no inspected teardown path proves that all four global root words are cleared.

A manager destructor is not automatically final service teardown, root clear, final root release, or proof that no later consumer can use a borrowed pointer. Noun object destruction, noun-manager teardown, star-manager teardown, SpacePlayerData teardown, and root unpublication are distinct lifecycle levels. `track-d-identity-ownership.md:359-430`; `track-f-lifecycle-ordering.md:568-586`; `blocker-a-adversarial.md:186-201`.

OpenSpore should impose a safe host-side order even though the original order is unresolved:

```text
mark root/owner unavailable
  -> block new borrowed lookups
  -> invalidate dependent projections and root handles
  -> release owner references
  -> destroy manager-owned storage
  -> retain separately owned snapshots only
```

This is a clean-room safety policy, not a claim about original unpublication.

## Contradiction register

| Contradiction or stale claim | Adjudication |
|---|---|
| Four distinct root words imply four owners, lifetimes, or always-unequal values. | **Rejected.** Distinct storage is high-confidence; owners, lifetimes, and value equality are unresolved. Track D and the blocker review are right to keep slot contracts separate from owner claims. |
| SDK singleton wording proves the alternate and canonical getters return the same manager. | **Rejected as proof.** It is vocabulary only; no equality, paired publisher, or teardown relation was recovered. |
| The alternate noun path is merely a generic context locator. | **Rejected for the selected path.** `0x00bff408 -> 0x00b3d300 -> ECX -> 0x00b21340` proves noun-manager-compatible receiver use, not root ownership. |
| `0x00b21410` erases `mNounMap+0x98`. | **Superseded by direct Track G disassembly.** The helper is reported at `+0xd0`; no per-key `mNounMap` erase is established. Track B's normal-destroy conclusion survives; Track D/F wording is stale for this helper. |
| “Five callbacks” describes the noun ABI. | **Corrected.** The body has four callback pointers plus one noun ID. Five stack arguments are not five callback pointers. The final contract must use one description only. |
| A missing noun/empire key returns null. | **Rejected for the raw helpers.** The lower-bound successor behavior is direct; SDK exact-null prose is contradicted at the low-level wrapper boundary. |
| A cache hit proves current registry membership. | **Rejected for the empire cache.** The hit checks the object's political field, not the selected manager's map membership. |
| `cStar` and `cStarRecord` are one object / completely different logical identities. | Both extremes are rejected. Physical representations are distinct; typed links exist; logical cardinality and restore mapping remain unresolved. |
| A `Write` call in a mode orchestrator proves save. | **Rejected.** It is not statically bound to the authoritative save/load bodies; persistence is a separate seam. |
| `stars.db.tmp -> stars.db` is a general atomic save transaction. | **Rejected.** It proves bounded temporary replacement only; no cross-file manifest, universal rollback, or crash atomicity is established. |
| `cGameData`, `cEmpire`, `cStarRecord`, or `cCellSerializableData` layout proves complete field survival. | **Rejected.** Explicit Write/Read or field emission is required; layouts and serializable vtables are candidates only. |
| A manager cleanup body is a root unpublication body. | **Rejected.** Manager-local release and global slot lifecycle are different. |
| Image-time zero bytes prove runtime null roots. | **Rejected.** This is only a static image observation. |
| A static no-writer scan proves no publisher exists. | **Rejected as a universal claim.** Computed, bulk, external, loader, unresolved, and runtime publication remain possible. |
| The root ports are a recovered four-owner architecture. | **Rejected.** They are a conservative compatibility-excluded observation boundary. The port hooks are OpenSpore policy, not recovered original operations. |
| The KG semantic description of `0x00b21340` is authoritative. | **Superseded where it conflicts with direct evidence.** The root-closure and direct disassembly establish the `mNounMap`/`mNouns` GetData contract; the stale message-handler description must not drive architecture. |

## Minimum semantic abstraction OpenSpore needs

This is the minimum safe **clean-room semantic abstraction**, not a claim to reproduce the original object graph or ABI.

### 1. Typed identity domains

Use separate types for:

- `ContentKey` / `ResourceKey`;
- `NounCategoryId`;
- `StarKey`;
- `PoliticalId`;
- `ObjectAddress`/live object identity;
- registry key plus registry owner;
- persistence/logical reference;
- cache handle and generation.

Do not provide a universal integer-ID comparison or serialization conversion. `track-d-identity-ownership.md:20-30,455-502`; `serialization-model.md:301-314`.

### 2. Ownership-qualified references

Represent three different result kinds:

- **Borrowed object/view:** valid only under the selected owner generation; does not prove membership.
- **Owned intrusive/Arc reference:** keeps the payload alive but does not keep it registered.
- **Snapshot:** owns payload references and may remain readable after registry/cache invalidation, but is explicitly historical rather than current.

A bare `T*` result should not be the public lifecycle contract. The caller must know whether it has membership, liveness, or only snapshot validity.

### 3. Separate registry lookup contracts

For each ordered map, expose at least:

```text
lookupExact(key)       // lower-bound primitive plus key/identity postcondition
lookupCeiling(key)     // compatibility primitive that may return a successor
upsert/getOrCreate     // explicit duplicate policy
removeCurrent(entry)   // requires membership/generation, not just lower bound
rekey                  // transaction or forbidden after publication
```

A caller requiring exactness must not silently inherit a lower-bound result. This applies equally to noun projections, empire lookup, and empire erase. `track-g-edge-cases.md:101-111,191-198`.

### 4. Explicit root observation ports

Each noun/star root port needs:

```text
observe() -> borrowed observation with port generation
publish/rebind(manager)
invalidate dependent observations
unpublish()
```

The port must not:

- imply equality with the other alternate/canonical port;
- fall back to the other port when null;
- assert a recovered owner;
- retain a raw pointer across unpublish;
- serialize its address.

The port state machine is host-side:

```text
unpublished -> published -> replacing -> live -> unpublishing -> dead
```

A numeric address alone cannot distinguish allocator reuse. `blocker-a-adversarial.md:203-252`; `architecture-decisions.md:29-51`.

### 5. Projection/cache contract

For noun, star, empire, resource, and presentation projections, distinguish:

```text
cached hit
materialize
invalidate
evict
clear
registry erase
owner release
```

A projection record should carry the selected owner generation and the source registry key. Element iterators must be invalidated on vector rebuild even if the record node address remains stable. Cached data may be retained after registry removal if its owning references remain, but it must not be labeled current membership.

### 6. Immutable or transactional indexed identity

Registered political/noun/star keys should be immutable by default. If rekey is a required feature, make it one manager-mediated operation:

```text
validate old membership
  -> reserve/block new publication
  -> update authoritative object key and registry key together
  -> update dependent registry/cache keys
  -> advance generation
  -> publish new identity
```

Failure must leave the old key and generations coherent. Do not expose an indexed-object field setter that can create object-field/map-key divergence.

### 7. Mode and persistence handoff as explicit phases

Keep App mode, Simulator strategy, input mode, SpaceContext, scenario mode, noun registry, star registry, empire cache, and persistence state as separate axes. A mode transition should be represented as an OpenSpore policy sequence with explicit phase boundaries, not as a claim that the original automatically saves or preserves state.

Persistence should serialize logical domain values and explicit references, then perform a separate reconstruction/binding phase. It must not serialize:

- host manager addresses;
- raw `cGameData*`, `cStar*`, `cEmpire*`, or `cStarManager*` pointers;
- Cell pool indices;
- cache records or cache counters;
- renderer/GFX/UI handles.

The original serializer architecture supports callbacks and association, but its complete reference table, field survival, and restore order are unresolved. `followup-06-persistence.md:110-136,226-245`; `serialization-model.md:335-380`.

## Runtime experiments that are truly needed

### Required for original root/lifecycle compatibility

**One naturally reachable phase transition plus teardown trace, with memory sampling.** This is the highest-value experiment and is genuinely needed before claiming any original root identity or survival rule.

Sample at synchronized points before Simulator construction, after manager registration, after first noun/star materialization, during a mode change, during SpacePlayerData/manager teardown, after each relevant destructor, and after app shutdown:

- all four root words;
- each non-null pointee address, primary vtable, and a host-side generation marker;
- the parent/registration slot if available;
- selected noun `mNouns`, `mObjects`, `field_80`, and `mNounMap` sizes;
- selected star `mEmpires`, record collections, home map, and relationship field;
- `SpacePlayerData+0x04/+0x08/+0x10/+0x18/+0x1c`;
- noun/star cache hit, miss, dirty, and refresh events;
- owner/root publication, rebind, unpublish, and destructor entries.

An unequal or one-sided-null observation rejects unconditional equality. A single equal observation does not prove always-equal behavior. A complete matrix is needed for a positive teardown model. The current probe tracer records selected registers but does not sample arbitrary memory or all return values; it needs a narrowly scoped read-only memory-sampling extension first. `track-g-edge-cases.md:293-302,344-348,418-428`.

### Required for original mode-survival claims

**One naturally reachable mode transition, separate from save/load.** Record App `OnExit`/index/message/enter boundaries, Simulator strategy commits, SpaceContext writes, active planet/star replacement, current-player empire cache, noun/star cache generations, and object refcounts before and after. This can establish whether a particular mode preserves, rebuilds, or invalidates a selected noun/star state. Static mode order alone cannot do that. `track-d-identity-ownership.md:359-378`; `track-f-lifecycle-ordering.md:253-364,588-626`.

### Required for original persistence/survival claims

**One disposable, explicit save/load round trip.** This is needed only if OpenSpore must claim original persistence behavior. Capture:

- save and load candidate entry/exit;
- header and logical object records without assuming their final order;
- one noun/star/empire logical reference and one forward or back-reference if naturally reachable;
- pre-save and post-load domain IDs, registry membership, object addresses, cache generations, and root slots;
- whether IDs are preserved, remapped, duplicated, missing, or rebound;
- whether the current-player cache is restored or rebuilt.

This experiment is necessary to distinguish domain survival, address reuse, and remapping. `stars.db` replacement alone is insufficient. A static `Write` interface or a serializer vtable is insufficient.

### Useful but not needed for the minimum OpenSpore model

A controlled read-only missing-key experiment can confirm that the public wrapper passes through a greater-key successor. It is statically predictable and is not required for the architecture decision. Record the requested key, returned key, and returned object field; do not infer an original wrapper contract without the call frame.

A natural cache-invalidation trace can confirm how many projections are dirtied and whether a phase later evicts records. It is not required to distinguish lazy invalidation from eviction, which is already instruction-level evidence.

### Not justified now

Do not force null-manager calls, allocation failure, live rekey, synthetic duplicate creation, forced same-key races, or stale-handle dereferences. They can corrupt preconditions or manufacture a crash rather than provide clean evidence. A two-thread or reentrant race is a valid future experiment only if concurrency/reentrancy becomes a requirement; a negative result would not disprove the static conditional hazard. `track-g-edge-cases.md:113-117,158-162,200-204,418-428`.

## Final disposition

The minimum safe semantic abstraction is a **domain-separated, owner-qualified lifecycle graph** with explicit root observations, typed registries, exact/ceiling lookup separation, generation-aware borrowed views, reference-preserving snapshots, deterministic duplicate policy, immutable-or-transactional indexed keys, independent invalidation/eviction/erase/clear operations, and a two-phase logical persistence handoff.

The following claims are safe to retain:

- noun and star roots are physically distinct observations;
- selected manager fields and object references have real local ownership;
- noun and empire raw lookups are lower-bound/ceiling operations;
- noun projections are lazily materialized and invalidated;
- empire map and player cache are independently owned;
- star records and live star/planet representations are physically distinct;
- mode and persistence helper-local order is static evidence, not survival evidence.

The following claims remain blocked or explicitly unresolved:

- root pair value equality, liveness, publication, rebind, and unpublication;
- total cross-root teardown order;
- original mode-state survival;
- complete original save/load field and reference survival;
- universal rekey, duplicate-publication, thread/reentrancy, and cache-eviction behavior;
- any claim that the clean-room ports, generations, exact wrappers, or teardown ordering reproduce the original ABI.

OpenSpore can proceed with the minimum semantic boundary as a compatibility-excluded architecture. Original lifecycle and persistence parity must wait for the synchronized root/teardown, mode-survival, and save/load observations above.
