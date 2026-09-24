# Noun and star lifecycle synthesis

## Scope and evidence boundary

This report synthesizes tracks A–G and both adversarial reviews under `knowledgegraph/research/noun-star-lifecycle/`. It cross-checks the authoritative root-closure, architecture-blocker, architecture-resolution, semantic-blueprint, gameplay-data, serialization, and type-archaeology artifacts. The analyzed program is the pinned `SPORE/SporeBin/SporeApp.exe` 3.1.0.22, `x86:LE:32:windows`, image base `0x00400000`, SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`.

The Ghidra validation in this synthesis was read-only. A separate bounded no-input runtime attempt was made against `SporeApp.exe`; it mapped the module and activated 16 probes but collected zero boundary events and zero root samples before the traced process tree exited. The attempt therefore supplies runtime evidence for a failed reachability experiment only, not for noun/star lifecycle, root identity, or teardown. No save/load round trip, implementation, executable mutation, `SPORE/` modification, or historical-artifact modification was performed. The attempted runtime reports are `knowledgegraph/research/noun-star-lifecycle/runtime-feasibility.md` and `runtime-experiment.md`.

The repository’s root closure records `runtime_evidence=false` and makes no `OBSERVED` or `VERIFIED` original-lifecycle claim (`docs/analysis/simulator-root-closure.md:1-5`; `knowledgegraph/research/root-closure-f0e310e0.json:4-35`). The new runtime attempt does not change that classification. “Proven” below means directly established by static bytes, decompilation, layout, xref, or a direct local call path, unless a section explicitly labels the bounded attempt as non-decisive.

## Executive answer

The original architecture is best described as a shared Simulator substrate with multiple independent service paths, not one recovered universal manager. Four four-byte global words are physically distinct. Two alternate accessors are strongly manager-compatible for noun and star consumers. Their publishers, runtime value equality, rebind order, liveness, and unpublication order are not recovered.

The safe clean-room decision is therefore a layered owner-qualified lifecycle graph with four separate opaque root observation ports. This resolves the minimum semantic boundary, not original root compatibility. Blocker A remains unresolved and architecture-changing (`docs/analysis/architecture-blockers.md:19-27`; `docs/analysis/architecture-blockers.md:31-89`; `docs/analysis/architecture-decisions.md:29-43`).

## Runtime attempt result

The bounded attempt reported in `knowledgegraph/research/noun-star-lifecycle/runtime-experiment.md:1-5` and `:72-127` mapped `SporeApp.exe` at base `0x400000`, resolved and activated all 16 selected probes, and then recorded zero boundary events and zero four-word root samples before the traced process tree exited. The six requested boundary classes—manager initialization, noun materialization, star materialization, mode transition, manager/cache teardown, and root getters—were all unobserved.

This result is decisive only about the attempted reachability observation. It is not decisive for the original lifecycle. It does not establish root equality or inequality, root publication, replacement, liveness, unpublication, teardown order, mode survival, or save/load behavior. It also does not establish the absence of a publisher or lifecycle path. The feasibility report further records that the existing probe tracer is entry-only, cannot sample the four root words, and uses temporary `INT3` bytes rather than being strictly process-memory-read-only (`runtime-feasibility.md:3-11`, `:28-58`, `:182-198`).

The clean-room boundary remains unchanged: four separate opaque root ports with explicit host-side lifecycle policy. Blocker A remains unresolved.

## Required answers

| # | Answer | Status |
|---:|---|---|
| 1 | `00b3d300` and `00b3d2a0` are distinct service paths, not aliases of one another. The first is an alternate noun-manager-compatible receiver; the second is an alternate `cStarManager`-compatible receiver. Their relation to the canonical accessors remains open. | Static mechanics high; exact owner low |
| 2 | `DAT_0167eae0` and `DAT_0167eb60` are distinct four-byte globals: alternate noun slot and named canonical noun slot. Physical aliasing is rejected; value equality and publication are unresolved. | Static fact plus open lifecycle |
| 3 | No concrete original noun-root publisher is recovered. `00b232b0` and `00b61bd3..00b61c5d` are construction/registration candidates, not a proven slot writer. | Unresolved |
| 4 | No concrete original star-root publisher is recovered. `00bae490` and the later alternate read at `00b634ab` do not join a manager allocation to either star root. | Unresolved |
| 5 | Noun objects are eager at `00b20c60`; noun typed views are lazy at `00b21340`. Star records are generated/registered at `00bb5d80`, planet records at `00bb4100`, live planets at `00baf130`/`00bb59b0`, and solar-system planet lists at `00c86760`. Root non-null timing is unresolved. | Local lifecycle static |
| 6 | Selected managers own local registries and references. `cStarManager` is a major registry/cache owner, not a proven sole owner of every star-related identity. The root words have no proven ownership authority. | Local ownership static |
| 7 | Noun invalidation is lower-bound dirty marking at `00b201a0` followed by lazy rebuild. Empire map erase and current-player cache teardown are separate. No root invalidation is proven. | Static mechanics |
| 8 | Normal noun destruction does not prove per-key `mNounMap` eviction; `00b21410` is a `+0xd0` map erase. Empire erase is lower-bound-selected. General rekey is unresolved. | Static mechanics plus open rekey |
| 9 | Mode survival is not proven. `007d85b0` proves local transition order, not noun/star survival or root rebind. | Runtime required |
| 10 | Save/load survival is not proven. Serializable records and `stars.db` replacement exist, but field coverage, logical remapping, restore order, and root persistence are unresolved. | Runtime required for parity |
| 11 | Manager-local teardown is recovered. Final root unpublication, root release, and total cross-root teardown order are not recovered. | Static local teardown; open root teardown |
| 12 | Live-object identity is process-local address plus virtual type. Root identity has no generation or membership metadata; allocator reuse and stale values cannot be excluded statically. | Static identity boundary |
| 13 | OpenSpore needs typed domain identities, owner-qualified registries, borrowed/owned/snapshot results, exact/ceiling lookup, generation-aware ports, and separate invalidation/eviction/erase/teardown operations. | Clean-room decision |
| 14 | No. Blocker A is resolved only as a safe clean-room boundary; original root publication compatibility remains blocked. | Architecture-changing unresolved |
| 15 | Four direct Ghidra accessor bodies, direct xrefs, receiver-field paths, local lifecycle bodies, and adversarial reviews support physical separation and a safe seam while preserving the root-publication gap. | Evidence ledgered |
| 16 | Downstream semantic packages are unblocked for clean-room contracts, characterization, fixtures, and host-side tests. Original ABI/root/persistence parity is not unblocked. | Clean-room yes; original no |

The machine-readable answers and evidence references are in `knowledgegraph/research/noun-star-lifecycle.json`, keys `required_questions` and `evidence_ledger`.

## Proven static facts

### Root accessors and storage

The direct Ghidra bodies are:

```text
00b3d300  mov eax, [DAT_0167eae0]; ret
00b3d400  mov eax, [DAT_0167eb60]; ret
00b3d2a0  mov eax, [DAT_0167eae4]; ret
00b3d3a0  mov eax, [DAT_0167eb0c]; ret
```

`00b3d400` is named `Simulator::cGameNounManager::Get`; `00b3d3a0` is named `Simulator::cStarManager::Get`. The accessors perform no validation, allocation, AddRef, Release, lock, or write. The direct Ghidra xrefs to the four words show only the corresponding reads; `DAT_0167eae4` also has the direct read in `00b3d2c0` (`knowledgegraph/research/noun-star-lifecycle/track-a-root-identity.md:34-45`; `knowledgegraph/research/noun-star-lifecycle/review-roots-publication.md:20-41`).

The four words are physically distinct. That rejects physical aliasing, not value aliasing. The absence of a direct writer is a bounded negative. It does not prove that no computed, table-driven, bulk, loader, external, or runtime publication path exists.

The safest terminology is alternate noun-root path and alternate star-root path, not active owner and not obsolete getter. Naming and fan-in do not establish priority, ownership, liveness, or equality (`knowledgegraph/research/root-closure-f0e310e0.json:112-218`; `docs/analysis/simulator-root-closure.md:131-158`).

### Noun receiver compatibility

The selected chain `00bff408 -> 00b3d300 -> ECX -> 00b21340` passes the alternate noun result into a function that reads manager-shaped `mNounMap+0x98`, `mNouns+0x78`, and the associated vector record. This proves noun-manager-compatible receiver use. It does not prove that the returned address is the allocation from `00b232b0`, that the global owns it, or that it equals `DAT_0167eb60` (`knowledgegraph/research/noun-star-lifecycle/track-a-root-identity.md:60-74`; `knowledgegraph/research/noun-star-lifecycle/review-roots-publication.md:43-60`).

### Star receiver compatibility

`00ba9370` uses the alternate result as a receiver with `mEmpires+0x150` and the map end/anchor at `+0x154`. The `00b3d2c0 -> 00c4f030` relationship path reads `receiver+0x204`, matching the SDK `mpRelationshipManager` field. This is strong layout compatibility, not a unique C++ class or owner proof (`knowledgegraph/research/noun-star-lifecycle/track-a-root-identity.md:76-104`; `knowledgegraph/research/noun-star-lifecycle/review-roots-publication.md:62-70`).

### Noun lifecycle

The strongest local noun sequence is:

```text
class/factory create
  -> assign runtime object ID
  -> link mObjects+0x10c and mNouns+0x78
  -> invalidate typed projections
  -> lower-bound lookup/materialization
  -> clear dirty vector, filter mNouns, add matches
  -> return borrowed manager-owned vector record
```

`00b20c60` performs eager concrete allocation and local list publication. `00b21340` is the actual `cGameNounManager::GetData` implementation. Its stack contract is four callback pointers plus `uint32 nounID`, not five callbacks. It lower-bounds `mNounMap+0x98`, creates/inserts on end, conditionally clears and rebuilds dirty vectors, and clears `needsUpdate` (`knowledgegraph/research/noun-star-lifecycle/track-b-noun-publication.md:161-239`; `knowledgegraph/research/noun-star-lifecycle/track-f-lifecycle-ordering.md:149-164`).

`00b201a0` obtains the object noun ID through the vtable, lower-bounds the noun map, marks the selected payload dirty, and scans cast-compatible records. This is lower-bound-selected invalidation, not exact-key invalidation. The successor hazard is part of the raw contract (`knowledgegraph/research/noun-star-lifecycle/track-b-noun-publication.md:277-292`; `knowledgegraph/research/noun-star-lifecycle/track-g-edge-cases.md:60-82`).

`00b225d0` sets a pending/status byte, retains the object in `field_80+0x80`, calls `00b20d30` for subtype teardown and `mNouns` unlinking, then calls `00b201a0`. `00b22960` later prunes `mObjects+0x10c` and releases the deferred retention. Logical removal and reclamation are separate (`knowledgegraph/research/noun-star-lifecycle/track-b-noun-publication.md:294-365`; `knowledgegraph/research/noun-star-lifecycle/track-f-lifecycle-ordering.md:166-188`).

The correction at `00b21410` is material. Direct decompilation shows `+0xd0` map storage, a payload-pointer check, and an erase through `01045590`; it is not evidence that normal individual destruction erases `mNounMap+0x98` (`knowledgegraph/research/noun-star-lifecycle/track-g-edge-cases.md:206-251`; `knowledgegraph/research/noun-star-lifecycle/review-identity-ordering.md:186-202`).

Manager teardown at `00b22440`/`00b237d0` releases manager-local maps, lists, vectors, and fields. It does not prove a root-slot clear or final service release.

### Star lifecycle and ownership

The original star domain is layered rather than homogeneous:

```text
cStarManager
  -> cStarRecord registries and cEmpire references
  -> live cPlanet cache
  -> empire-home map

cStarRecord
  -> cPlanetRecord values and generation/save metadata

cStar
  -> cStarRecord and cSolarSystem links

cSolarSystem
  -> live cPlanet collection and owner-star link

cPlanet
  -> cPlanetRecord link
```

`00bb5d80` constructs generated `cStarRecord` values, computes a sector/slot `StarID`, and appends intrusive references to `mStarRecordGrid`; separate starter, saved, possible-start, and black-hole collections are not aliases of that grid. `00bb4100` regenerates planet-record data. `00bb4af0` reuses the existing record identity rather than proving a new star allocation. `00bb5b50` and `00bb59b0` bridge `cPlanetRecord` to live `cPlanet`, with cache reuse keyed by the `cPlanet+0x13c` record link. `00c86760` loads the solar-system planet collection (`knowledgegraph/research/noun-star-lifecycle/track-c-star-publication.md:203-354`; `knowledgegraph/research/noun-star-lifecycle/track-c-star-publication.md:386-426`).

`cStarManager` owns substantial registry/cache state, but `cEmpire` independently owns `cStarRecord` references, and `cSolarSystem` holds live planets. A home-map replacement releases the map’s old reference; it is not a universal record erase. The record can remain in the grid, empire vector, saved/starter collection, or external owner. The physical separation of `cStar` and `cStarRecord` is proven; their logical association cardinality and restore order are not (`knowledgegraph/research/noun-star-lifecycle/track-c-star-publication.md:272-303`; `knowledgegraph/research/noun-star-lifecycle/track-c-star-publication.md:502-513`).

`00ba9370` is a lower-bound/ceiling lookup over `mEmpires+0x150`. A missing political ID can return a greater successor. `01021300` validates a cache hit by `cEmpire+0x84` but does not revalidate registry membership on the miss path. `00bad7a0` erases the lower-bound-selected map payload; `01022460` independently clears and releases the player cache (`knowledgegraph/research/noun-star-lifecycle/track-f-lifecycle-ordering.md:190-230`; `knowledgegraph/research/noun-star-lifecycle/track-g-edge-cases.md:206-235`).

## Strongest interpretation

The original architecture is a shared substrate with independent noun, star, empire, space, and mode state domains. The four globals are observation points into a service-publication substrate, not four proven owners. The noun and star managers each have a manager-local graph, but neither manager-local graph is joined to a global root publication path.

The strongest static model is therefore:

```text
manager construction/registration candidate
  -> manager-local state initialization
  -> object/record/cache materialization
  -> borrowed or owned consumer access
  -> local invalidation, erase, or teardown

root publication/rebind/unpublication
  -> unresolved between the manager-local graph and the four global words
```

This interpretation explains the evidence without requiring a majority vote among reports. It is supported by direct field-use and lifecycle bodies, but it remains a model, not a recovered original publisher.

## Hypotheses retained but not selected

1. **Always-equal alternate/canonical pairs.** This predicts paired publication, replacement, and teardown. It remains unresolved because no common writer, equality operation, or joined teardown was found.
2. **Phase-specific or independently rebound managers.** This predicts unequal or one-sided-null windows and phase-specific cache consequences. It remains unresolved; distinct words and consumer asymmetry make it relevant but not proven.
3. **One path is stale or compatibility-only.** High alternate fan-in and sparse canonical fan-in do not prove liveness or deadness. The canonical star path has a raw code reference at `00b5ca50`.
4. **Computed, bulk, loader, or external publication.** The writable zero-fill root region and missing direct writer leave this possible, but no such publisher was selected as the leading explanation.
5. **Noun cache duplicate race or provisional-record orphan.** `00b21340` creates before insertion and does not visibly switch to the insertion winner. This is a conditional static hazard, not observed ordinary behavior.
6. **General indexed rekey.** Creation-scoped political-ID writes exist, but no transaction was found that updates the object field, ordered map key, dependent registries, and cache generations together.

## Ownership and identity answer

The minimum identity vocabulary is domain-separated:

- `ResourceKey` is a complete packaged-content key.
- `NounID` is a noun/category projection key and is not a unique live-object address.
- `StarID` is a star-record/grid domain key and is not a live `cStar*` address.
- `PoliticalID` is an empire/player domain value and is not a star key.
- `cGameData*`, `cStar*`, `cEmpire*`, and `cStarRecord*` are process-local live representations with different layouts and lifetimes.
- Registry identity is `(owner, key domain, key)`, not a bare key.
- A borrowed pointer, an owned intrusive reference, a cache record, and a by-value snapshot have different validity contracts.

The central ownership rule is: an owner stores a reference or key; an accessor may return a borrowed pointer; registry erase releases the registry’s reference but does not automatically invalidate every alias or cache. This is direct in the noun map, empire map, and star-record graph (`knowledgegraph/research/noun-star-lifecycle/track-d-identity-ownership.md:115-192`; `knowledgegraph/research/noun-star-lifecycle/track-d-identity-ownership.md:231-344`).

## Mode transition, save/load, and teardown

### Mode transition

`007d85b0` proves the concrete local order:

```text
old OnExit
  -> active-index write
  -> exit announcement
  -> new OnEnter
  -> enter announcement
```

App active mode, Simulator strategy, input mode, `SpaceContext`, scenario mode, and Cell lifecycle are separate axes. Scenario teardown can reach noun-family cleanup, but that is not root unpublication. No noun/star manager, record, empire cache, or root survival rule is proven by the helper-local order (`knowledgegraph/research/noun-star-lifecycle/track-f-lifecycle-ordering.md:253-291`; `knowledgegraph/research/noun-star-lifecycle/review-identity-ordering.md:168-178`).

### Save/load

`cGameData`, `cStarRecord`, `cEmpire`, and related serializable types are persistence candidates. `00bb4ba0` writes `stars.db.tmp` and replaces `stars.db`. `PropertyList`, `ClassSerializer`, and the save/load candidates at `00b28ec0`/`00b279e0` show real persistence machinery. They do not close the outer envelope, field coverage, reference table, pointer remapping, manager binding, or restore order (`knowledgegraph/research/noun-star-lifecycle/track-f-lifecycle-ordering.md:492-542`; `docs/analysis/serialization-model.md:253-299`; `docs/analysis/serialization-model.md:335-380`).

The original does not statically justify persisting the four root words or raw live pointers. The exact original field survival and mode-transition handoff remain open. OpenSpore must serialize logical values and explicit logical references, then reconstruct and rebind runtime objects in a separate phase.

### Teardown

The static teardown surfaces close manager-local state, not the total root graph:

- noun manager cleanup releases lists, maps, vectors, and owner fields;
- star manager cleanup releases record/planet/empire/relationship state and unregisters callbacks;
- `01022460` clears active planet/star, relationship, and current-empire fields;
- root words have no direct clear or release join in the inspected teardown bodies.

A manager destructor is not automatically final service teardown, root unpublication, or proof that a later consumer cannot use a stale pointer. A natural transition with memory sampling is required for the original order.

## Contradictions and corrections

1. **Singleton wording versus storage.** SDK singleton language and canonical names do not prove value equality. Four distinct words reject physical aliasing only.
2. **Alternate noun generic locator versus noun receiver.** The direct `00bff408 -> 00b21340` receiver chain supersedes the weaker generic-context label, but does not prove unique class or ownership.
3. **`00b21410` as noun-map erase.** The direct `+0xd0` decompilation supersedes the stale interpretation. It is not `mNounMap+0x98` eviction.
4. **Five callbacks.** The corrected noun ABI is four callback pointers plus `nounID`.
5. **Exact lookup wording.** `00b21340` and `00ba9370` check end sentinels after lower-bound. Missing keys can return successors. Exactness requires an explicit postcondition.
6. **Manager lifecycle as root lifecycle.** Constructor, record cleanup, cache teardown, and destructor bodies are not root publication or unpublication.
7. **Write/database replacement as complete save.** A mode-interface `Write` call and `stars.db.tmp -> stars.db` replacement are bounded persistence surfaces, not proof of complete save/load parity or automatic mode-exit save.
8. **Physical versus logical star identity.** `cStar` and `cStarRecord` are distinct physical representations with typed links. This does not prove they are unrelated logical identities or prove one-to-one cardinality.

The authoritative adjudication is summarized in `docs/analysis/architecture-blockers.md:54-89`, `knowledgegraph/research/architecture-blockers.json:77-135`, and the two reviews in this research directory.

## Runtime evidence status and required experiment

No positive original-process lifecycle evidence exists for these roots. One bounded attempt was made, but it was not decisive: `SporeApp.exe` mapped at `0x400000`, all 16 probes were active, and zero boundary events and zero root samples were collected before process exit. This is runtime evidence of a failed reachability attempt only (`runtime-experiment.md:72-127`). It does not establish root values, equality, publication, replacement, liveness, teardown, or absence of any lifecycle path.

The feasibility report further establishes that the existing tracer is entry-only, cannot sample the four root words, and is not strictly process-memory-read-only because it plants temporary `INT3` bytes (`runtime-feasibility.md:3-11`, `:15-26`, `:182-198`). A future human-gated experiment must therefore use a synchronized debugger/memory-sampling design that discloses breakpoint writes and records a natural lifecycle transition. It should record:

- all four root words and non-null pointee address/vtable/generation markers;
- noun and star manager construction/registration receivers and parent slots;
- noun `mNouns`, `mObjects`, `field_80`, and `mNounMap` state;
- star record grids, candidate collections, empire map, home map, and relationship field;
- `SpacePlayerData+0x04/+0x08/+0x10/+0x18/+0x1c`;
- noun and empire requested keys, actual lower-bound keys, cache records, and dirty flags;
- create, destroy, erase, rebind, manager teardown, and root-clear events.

A complete matrix for one scenario is required before claiming original root publication, equality, liveness, rebind, or teardown order. One unequal or one-sided-null snapshot rejects unconditional equality; it cannot prove an always-equal or universally ordered model. Forced null allocation, synthetic rekey, duplicate races, destructive erase, and stale-handle dereferences are not justified for the core question.

The narrowest defensible answer for every runtime-only root question remains: **unresolved; the attempted run did not reach a lifecycle boundary, and the current static evidence does not select among equal, unequal, phase-specific, stale, or opaque publication outcomes.**

## OpenSpore boundary

The original architecture and the minimum clean-room semantic model must remain separate:

- Original: four physical root words, manager-compatible alternate paths, substantial manager-local lifecycle bodies, and unresolved publication/lifecycle.
- Clean room: four separate owner-qualified observation ports with generation and lifecycle state; typed registry keys; borrowed/owned/snapshot result kinds; exact/ceiling lookup separation; explicit invalidation/eviction/erase/teardown; and logical persistence with reconstruction.

This boundary unblocks semantic design and characterization but does not authorize original ABI, root publication, raw vtable, complete save, or mode-survival parity claims. The machine-readable decision and full evidence ledger are `knowledgegraph/research/noun-star-lifecycle.json`.

## Source index

- Worker reports and reviews: `knowledgegraph/research/noun-star-lifecycle/track-a-root-identity.md`, `track-b-noun-publication.md`, `track-c-star-publication.md`, `track-d-identity-ownership.md`, `track-e-cross-root-callers.md`, `track-f-lifecycle-ordering.md`, `track-g-edge-cases.md`, `review-identity-ordering.md`, `review-roots-publication.md`.
- Runtime attempt reports: `knowledgegraph/research/noun-star-lifecycle/runtime-feasibility.md`; `knowledgegraph/research/noun-star-lifecycle/runtime-experiment.md`. These establish host feasibility and a zero-event reachability attempt only.
- Root closure: `docs/analysis/simulator-root-closure.md`; `knowledgegraph/research/root-closure-f0e310e0.json`.
- Architecture status: `docs/analysis/architecture-blockers.md`; `docs/analysis/architecture-decisions.md`; `knowledgegraph/research/architecture-blockers.json`; `knowledgegraph/research/architecture-resolution.json`.
- Semantic boundaries: `docs/analysis/semantic-blueprint.md:943-1005`; `docs/analysis/gameplay-data-model.md:294-396`; `docs/analysis/serialization-model.md:335-410`; `docs/analysis/type-archaeology.md:60-70`.
- Primary Ghidra anchors: `00b3d300`, `00b3d400`, `00b3d2a0`, `00b3d3a0`, `00b3d2c0`, `00b21340`, `00ba9370`, `00b20c60`, `00b201a0`, `00b225d0`, `00b20d30`, `00b22960`, `00b21410`, `00bae490`, `00bb5d80`, `00bb5b50`, `00baf130`, `00bb59b0`, `00c86760`, `00bb5640`, `00bb4af0`, `00bb6390`, `00bb7250`, `00b22440`, `01021300`, `01022460`, `007d85b0`, `00b3d440`, `00b28ec0`, `00b279e0`, and root words `0x0167eae0`, `0x0167eb60`, `0x0167eae4`, `0x0167eb0c`.
