# Noun/star lifecycle architecture decision

## Decision record

**Decision:** adopt a layered owner-qualified lifecycle graph for OpenSpore’s noun and star domains. Keep four separate opaque root observation ports: alternate noun, canonical noun, alternate star, and canonical star. Give every port an explicit generation and lifecycle state. Do not merge ports, claim a recovered owner, or claim original publication parity.

**Decision status:** accepted for clean-room semantic design, characterization, fixtures, and host-side tests. Original root ABI, root publication, liveness, cross-root teardown, and complete save/load compatibility remain blocked.

**Selected model:** layered owner-qualified lifecycle graph. No single Model A/B/C/D is selected. The original evidence supports a shared substrate with multiple local ownership graphs, not a universal singleton or universal object identity.

**Evidence boundary:** static/read-only Ghidra analysis of `SPORE/SporeBin/SporeApp.exe` 3.1.0.22 plus one bounded no-input runtime attempt documented in `knowledgegraph/research/noun-star-lifecycle/runtime-feasibility.md` and `runtime-experiment.md`. The attempt mapped the module and activated 16 probes but collected zero boundary events and zero root samples before exit; it was not decisive for lifecycle behavior. Direct Ghidra anchors and source citations are listed at the end. No decisive original lifecycle trace, implementation, executable mutation, `SPORE/` modification, or architecture-decision-register modification is part of this decision.

## Decision rationale

The four target globals are physically distinct four-byte words:

- `0x0167eae0` is read by `0x00b3d300`.
- `0x0167eb60` is read by the named `Simulator::cGameNounManager::Get` accessor `0x00b3d400`.
- `0x0167eae4` is read by `0x00b3d2a0` and `0x00b3d2c0`.
- `0x0167eb0c` is read by the named `Simulator::cStarManager::Get` accessor `0x00b3d3a0`.

The alternate noun result is used as a receiver by `0x00b21340`, which reads noun-manager-shaped `mNounMap+0x98` and `mNouns+0x78`. The alternate star result reaches `mEmpires+0x150` and `mpRelationshipManager+0x204`. This supports manager-compatible receiver contracts, not root ownership or alias equality. The direct bodies and xrefs are in `knowledgegraph/research/noun-star-lifecycle/track-a-root-identity.md:34-45` and `review-roots-publication.md:20-70`.

No direct root writer, clear, equality operation, replacement order, or joined teardown path was recovered. Manager construction and parent registration are candidate service-lifecycle surfaces, not publishers. The bounded negative is explicitly not proof that no computed, bulk, loader, external, or runtime publisher exists. The authoritative status is unresolved architecture-changing in `docs/analysis/architecture-blockers.md:31-89` and `knowledgegraph/research/architecture-blockers.json:28-135`.

## Runtime attempt disposition

The isolated runtime reports add a bounded failed-reachability observation. `SporeApp.exe` was mapped at base `0x400000`; 16 selected probes resolved and were active; the process tree exited before any manager, noun, star, mode, teardown, or root-getter boundary event; and the event log contained zero events and zero four-word root samples (`runtime-experiment.md:72-98`).

This is not a lifecycle result. It does not establish root equality, inequality, publication, replacement, liveness, unpublication, teardown order, mode survival, or save/load survival, and it does not establish that a publisher or lifecycle path is absent. The feasibility report also records that the existing probe tracer is entry-only, cannot sample the root words, and temporarily writes `INT3` bytes rather than being strictly process-memory-read-only (`runtime-feasibility.md:3-11`, `:15-26`, `:182-198`).

The attempted experiment was not decisive. Blocker A remains unresolved, and the clean-room decision below remains unchanged: four separate opaque root ports with explicit host-side publication, replacement, invalidation, and unpublication policy; no original root ABI, ownership, equality, liveness, or teardown claim.

## Original architecture versus clean-room model

### Original architecture: static facts

The original binary contains multiple local graphs:

```text
noun factory
  -> cGameNounManager
  -> mObjects and mNouns
  -> mNounMap projection
  -> typed noun vectors and intrusive element references

cStarManager
  -> cStarRecord grids and candidate collections
  -> cEmpire registry and home map
  -> live cPlanet cache
  -> relationship manager

cStar
  -> cStarRecord
  -> cSolarSystem

cSolarSystem
  -> live cPlanet objects
  -> cPlanetRecord links
```

The noun path is eager for concrete object publication and lazy for typed vector materialization. The star path separates record generation, record registries, live-planet materialization, solar-system loading, empire references, and manager teardown. These local mechanics are substantially recovered in `track-b-noun-publication.md`, `track-c-star-publication.md`, `track-d-identity-ownership.md`, and `track-f-lifecycle-ordering.md`.

The original root layer is not recovered. The original is known to have four physical observation words, but not their publishers, owners, equality relation, phase relation, rebind order, or unpublication order. The OpenSpore model must therefore not claim to reproduce the original root graph.

### Minimum clean-room model

OpenSpore defines the following semantic layers.

#### Typed identity domains

| Domain | Meaning | Must not be substituted with |
|---|---|---|
| `ContentKey` / `ResourceKey` | Complete packaged-content key | Noun ID, star ID, pointer, cache handle |
| `NounCategoryId` | Noun projection/category key | Live object address or definition ID |
| `StarKey` | Star-record/grid domain key | Live `cStar*`, empire political ID, ResourceKey |
| `PoliticalId` | Empire/player political domain value | Star key, pointer, cache counter |
| `LiveObjectIdentity` | Process-local address plus virtual type | Durable save identity |
| `RegistryIdentity` | Owner plus key domain plus key | Bare key or pointer |
| `PersistenceReference` | Logical serialized relation requiring reconstruction | Raw host pointer |

These domains are justified by the noun map’s `uint32` category key, the star record key, the empire political ID, separate live object layouts, and serializer boundaries (`track-d-identity-ownership.md:32-192`; `docs/analysis/serialization-model.md:301-316`).

#### Result kinds

| Kind | Contract |
|---|---|
| `BorrowedView<T>` | Valid only under the selected owner generation; does not prove membership or currentness |
| `OwnedReference<T>` | Keeps payload allocation alive; does not prove registry membership |
| `Snapshot<T>` | Owns payload references and is explicitly historical after invalidation or erase |
| `RootObservation` | Borrowed port observation with a port generation; never serialized as a host address |

A bare `T*` is not an adequate public lifecycle contract. The caller must know whether it has a live payload, current registry membership, historical snapshot validity, or only a borrowed owner view.

#### Registry contracts

Every ordered registry exposes these operations, whether or not the original has matching names:

```text
lookupExact(key)
lookupCeiling(key)
upsertOrGetOrCreate(key, value)
removeCurrent(entry, generation)
invalidate(entry)
rekey(oldEntry, newKey)
```

`lookupCeiling` may return a greater successor and must be named as such. `lookupExact` calls the lower-bound primitive and then verifies the returned key/identity. `removeCurrent` requires exact membership and generation, not merely a lower-bound result. Duplicate publication has a deterministic OpenSpore policy. A registered indexed key is immutable by default; if rekey is required, it is one manager-mediated transaction that updates authoritative keys, dependent registries, cache generations, and observers before publishing the new identity.

These rules preserve the static hazards found at `0x00e5c780`, `0x00b21340`, `0x00ba9370`, `0x00bad7a0`, and `0x01021300` without copying unchecked dereferences or claiming original API semantics.

#### Root observation ports

The four ports are separate even if a future runtime trace shows equal values:

```text
noun.alternate       observes DAT_0167eae0 through 0x00b3d300
noun.canonical       observes DAT_0167eb60 through 0x00b3d400
star.alternate       observes DAT_0167eae4 through 0x00b3d2a0
star.canonical       observes DAT_0167eb0c through 0x00b3d3a0
```

Each port exposes:

```text
observe() -> RootObservation
publish(manager)
rebind(manager)
invalidateDependentObservations()
unpublish()
```

Each observation carries:

- port identity;
- manager address, if any;
- owner generation;
- lifecycle state;
- publication source, if known;
- explicit membership/validity status.

The port state machine is host-side:

```text
unpublished -> published -> replacing -> live -> unpublishing -> dead
```

A port never falls back to its alternate/canonical sibling. A port never asserts that a non-null value is live. A port never turns allocator address equality into generation-stable identity. A port never serializes its address. These rules are the clean-room safety boundary proposed by `docs/analysis/architecture-decisions.md:29-51` and the reviews.

#### Noun lifecycle boundary

The minimum noun model is:

```text
register type
  -> create concrete noun
  -> eager manager-local object/list publication
  -> lazy lower-bound projection lookup
  -> materialize typed vector
  -> borrow or snapshot result
  -> invalidate projection on create/destroy
  -> unlink live list membership
  -> defer owner/reference reclamation
  -> manager-local teardown
  -> explicit root-port lifecycle independent of the noun graph
```

The original’s `0x00b20c60`, `0x00b21340`, `0x00b201a0`, `0x00b225d0`, `0x00b20d30`, and `0x00b22960` provide strong local evidence. OpenSpore must not make every noun destroy an unconditional `mNounMap.erase(nounID)`, because the direct `0x00b21410` correction shows a different `+0xd0` map operation and normal destruction is otherwise lazy invalidation.

#### Star lifecycle boundary

The minimum star model is:

```text
generate or load cStarRecord
  -> publish record reference into selected registries
  -> generate cPlanetRecord data
  -> reuse or materialize live cPlanet
  -> load cSolarSystem planet collection
  -> link empire and home associations independently
  -> invalidate selected collections
  -> regenerate the same record or release selected references
  -> manager-local teardown
```

`cStar`, `cStarRecord`, `cPlanet`, `cPlanetRecord`, `cSolarSystem`, and `cEmpire` remain distinct semantic representations. `cStarManager` is a registry/cache owner, not a universal owner. A home-map replacement is not a universal record erase. A live planet cache hit is not proof of current registry membership. Star-record regeneration is not assumed to allocate a new star identity.

#### Invalidation and teardown

OpenSpore separates all of these operations:

```text
cached hit
materialize
invalidate projection
evict projection record
clear owner cache
remove registry entry
release owner reference
destroy owner storage
unpublish root
```

The minimum teardown order is host policy, not an original claim:

```text
unpublish roots
  -> block new borrowed lookups
  -> invalidate dependent views and caches
  -> release owner references
  -> destroy manager-owned storage
  -> retain separately owned snapshots only
```

This order prevents new consumers from observing an owner while dependent storage is being destroyed. It does not assert that the original follows it.

#### Persistence boundary

OpenSpore persistence has two explicit phases:

```text
serialize logical domain values and explicit logical references
  -> reconstruct registries and objects
  -> bind current player, active star/planet, and mode state
  -> advance owner generations
  -> publish fresh root observations
```

OpenSpore does not serialize raw host pointers, manager addresses, Cell pool indices, cache records, cache counters, renderer handles, or GFX/UI handles. `cStarRecord`, `cGameData`, `cEmpire`, and other domain records are represented only through an explicit OpenSpore schema when their fields are evidenced. Original field coverage, outer envelope, pointer remapping, migration, and restore order remain open.

## Required lifecycle invariants

1. Root ports remain separate and explicit until runtime equality is observed.
2. Object liveness, registry membership, cache residency, and snapshot validity are different states.
3. Lower-bound lookup is never exposed as exact lookup without a postcondition.
4. Noun invalidation is separate from noun projection eviction and owner teardown.
5. Empire map erase is separate from current-player cache teardown.
6. Star home-map replacement is separate from grid, empire-vector, candidate, and live-world removal.
7. An indexed key is immutable after publication or rekeyed transactionally across all dependent indexes.
8. Duplicate creation and cache publication have deterministic winner and cleanup semantics.
9. Borrowed views carry an owner generation and cannot survive owner unpublication.
10. Owned payload references may outlive registry membership but cannot make a snapshot current.
11. Mode axes remain separate; a mode transition does not imply automatic save.
12. Serialization writes logical data and explicit references, then performs a separate reconstruction phase.
13. Root publication and teardown events are host policy and are not labeled original ABI behavior.
14. Failure behavior is explicit in OpenSpore public boundaries rather than inherited from unchecked original dereferences.

## Downstream packages unblocked

The following packages are unblocked for clean-room semantic contracts, characterization, fixtures, and host-side tests:

| Package | Unblocked boundary |
|---|---|
| `PKG-01-SHARED-STATE-ROOTS` | Four root observation ports, generation/lifecycle state, no implicit aliasing |
| `PKG-02-APP-LIFECYCLE` | Mode/root lifecycle as separate axes; explicit transition and teardown hooks |
| `PKG-03-RESOURCE-IO` | `ResourceKey` and content identity separated from runtime noun/star identity |
| `PKG-06-CELL-STATE` | Cell runtime state remains separate from noun/star manager and persistence state |
| `PKG-08-CELL-MODE` | Mode handoff consumes semantic lifecycle events, not root equality or autosave assumptions |
| `PKG-11-SIM-CORE` | Noun registry, materialization, invalidation, ownership, and destruction contracts |
| `PKG-12-SIM-SPACE` | Star/empire/planet records, current-player cache, active references, and context boundaries |
| `PKG-13-SIM-CREATURE-TRIBECIV` | Live noun, political identity, civilization lookup, and snapshot/borrowed result distinction |
| `PKG-20-GAMEGLOBAL` | Shared-state coordination through owner-qualified ports rather than one global entity ID |
| `PKG-21-UNKNOWN-ROUTING` | Opaque observations remain bounded and cannot be promoted to a pointer or mode ABI by this decision |

The affected-package boundary is consistent with `docs/analysis/architecture-blockers.md:73-89` and `docs/analysis/semantic-blueprint.md:961-969`, with the broader noun/star dependency set in `docs/analysis/semantic-blueprint.md:993-1005`.

“Unblocked” means the packages can consume this semantic decision. It does not mean the original root ABI, raw vtables, original save bytes, original mode handoff, or runtime survival behavior are recovered.

## Non-goals

This decision does not:

- assert that any alternate/canonical pair is always equal or always unequal;
- assert that `0x00b3d300` is the canonical noun getter or that `0x00b3d2a0` is the canonical star getter;
- assert that manager construction publishes a root;
- assert that manager teardown unpublishes a root;
- claim four original owners, four original lifetimes, or four original publishers;
- expose the four ports as a reproduction of the original global ABI;
- claim that raw pointers, root words, cache records, or renderer handles are save fields;
- copy original lower-bound, unchecked-null, allocation-failure, or successor behavior into a public exact API without a named compatibility boundary;
- resolve mode-transition survival, root liveness, general rekey, duplicate races, or complete original restore order;
- replace a local manager graph with a universal noun/star entity;
- modify the architecture decision register, source code, executable, `SPORE/`, or any historical research artifact.

## Validation and future evidence

The minimum clean-room model can be tested with deterministic host fixtures for:

- port publish/rebind/invalidate/unpublish state transitions;
- generation changes and rejection of stale borrowed observations;
- exact versus ceiling lookup postconditions;
- lazy noun projection invalidation and rebuild;
- map erase versus player-cache teardown;
- deterministic duplicate creation and atomic cache publication;
- immutable indexed keys and transactional rekey failure rollback;
- ordered teardown with owner references and snapshots;
- logical save/load reconstruction without host pointers.

A future original-compatibility experiment must be human-gated, bounded, and synchronized. It must disclose that software breakpoints modify process memory unless a verified hardware/debugger facility is used. It should sample all four root words, non-null pointee addresses, vtables or generation markers, manager construction/registration, noun create/destroy, star record/planet materialization, empire erase/cache refresh, mode boundaries, manager teardown, and application shutdown. The prior zero-event attempt supplies no lifecycle samples and cannot substitute for this matrix. A single unequal or one-sided-null observation rejects unconditional equality but does not prove a positive universal model. A complete scenario matrix is required before changing the four-port boundary.

## Evidence and provenance

- Root mechanics: `knowledgegraph/research/noun-star-lifecycle/track-a-root-identity.md:34-285`; `review-roots-publication.md:20-324`.
- Runtime feasibility and attempt: `knowledgegraph/research/noun-star-lifecycle/runtime-feasibility.md:3-11`, `:28-58`, `:182-198`; `runtime-experiment.md:1-5`, `:72-127`. The attempt is host/reachability evidence only, not lifecycle evidence.
- Noun lifecycle: `track-b-noun-publication.md:131-384`; `track-g-edge-cases.md:206-302`; direct Ghidra `0x00b20c60`, `0x00b21340`, `0x00b201a0`, `0x00b225d0`, `0x00b20d30`, `0x00b22960`, `0x00b21410`.
- Star lifecycle: `track-c-star-publication.md:203-513`; direct Ghidra `0x00bae490`, `0x00bb5d80`, `0x00bb4100`, `0x00bb5b50`, `0x00baf130`, `0x00bb59b0`, `0x00c86760`, `0x00bb5640`, `0x00bb4af0`, `0x00bb6390`, `0x00bb7250`.
- Cross-root ordering: `track-f-lifecycle-ordering.md:83-626`; `track-e-cross-root-callers.md:246-295`; `review-identity-ordering.md:103-184`.
- Identity and persistence boundaries: `track-d-identity-ownership.md:359-524`; `docs/analysis/serialization-model.md:253-299`; `docs/analysis/serialization-model.md:335-410`.
- Authoritative status: `docs/analysis/architecture-blockers.md:19-89`; `docs/analysis/architecture-decisions.md:29-51`; `knowledgegraph/research/architecture-blockers.json:28-135`; `knowledgegraph/research/architecture-resolution.json:76-128`; `knowledgegraph/research/root-closure-f0e310e0.json:112-218`.
- Machine-readable synthesis: `knowledgegraph/research/noun-star-lifecycle.json`.
