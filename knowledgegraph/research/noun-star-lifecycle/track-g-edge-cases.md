# Track G — runtime identity edge cases

## Scope and result

This report investigates only runtime identity edge cases in the noun and star lifecycle: missing or invalid objects, duplicate publication, rekey, cache eviction, stale pointers/handles, teardown while referenced, and repeated lookup after invalidation.

**Result:** `ARCHITECTURE_CHANGING`. The original has several preconditions rather than general fail-safe null handling, and it mixes three different validity domains:

1. borrowed manager, registry-result, and vector-view pointers;
2. intrusive references that keep payload objects alive without preserving registry membership; and
3. high-level ModAPI snapshots returned by value.

Those domains must remain distinct in OpenSpore. The most important consequences are:

- noun and empire lookup are lower-bound operations, so a missing key may return a greater-key successor;
- noun removal marks selected cached vectors for lazy rebuild, while the previously analyzed `0x00b21410` path is **not** a `mNounMap` erase;
- the current-player cache is not membership- or generation-validating and is not invalidated by empire-map erase;
- a reentrant or concurrent noun-cache miss can create a record that loses a duplicate insertion race and is then returned without becoming the map payload;
- empire creation is an insert-or-replace operation under a duplicate key, so the last store wins while a caller can still return its own replaced object;
- rekeying an indexed object outside a closed transaction can make the object's political ID disagree with its map node key; and
- borrowed handles are unsafe across owner teardown even when separately referenced payload elements remain alive.

No implementation was performed. No runtime experiment was run. No Ghidra state, original executable, `SPORE/`, KG database, shared final artifact, or other worker file was modified.

## Evidence lanes and independence

1. **Current Ghidra static evidence.** Read-only decompilation, disassembly, callers/xrefs, one P-code forward trace through the noun insertion result, structure-derived field use, and direct-root-reference queries on explicit program `SporeApp.exe`.
2. **Existing KG, read-only.** The SQLite database was opened with `mode=ro`; only existing noun/star function nodes, structures, globals, and edges were consulted. The KG's root-closure nodes for `0x00b21340`, `0x00ba9370`, and `0x01021300` agree with current instruction evidence and record no runtime evidence.
3. **SDK type contract.** Current local Spore-ModAPI headers for `cGameNounManager`, `tGameDataVectorT`, `cStarManager`, `cEmpire`, and `cGameData`.
4. **Community evidence.** The generated Sporecommunity documentation and the 2019 Spore Modder tutorial, used as API-usage and intent evidence rather than binary proof.

The two noun/star architecture reports are prior interpretations of the same binary evidence, not independent runtime lanes. Repeated claims in those reports and in the KG were checked against current instructions and were not counted as fresh proof.

## Identity and validity model used by this report

| Boundary | Static ownership/lifetime fact | Consequence |
|---|---|---|
| `0x00b3d300` / `0x00b3d400` noun-root getters | Return raw global words; no validation, AddRef, Release, or ownership transfer | A non-null value is not evidence of a live manager |
| `0x00b3d2a0` / `0x00b3d3a0` star-root getters | Return raw global words; no validation, AddRef, Release, or ownership transfer | A non-null value is not evidence of a live manager |
| `0x00b21340` low-level `GetData` | Normally returns a raw pointer to the manager-owned `mNounMap` vector record; no AddRef, and a duplicate-insertion race can violate that ownership assumption | The record/vector and iterators require manager/record lifetime; payload liveness is separate |
| `GetData<T>(nounID)` in `GameNounManager.h` | Returns `tGameDataVectorT<T>` **by value** | Normal ModAPI helper use obtains a snapshot of intrusive element references, not a borrowed record handle |
| `0x00ba9370` empire lookup | Returns a raw borrowed `cEmpire*` from lower-bound result; no AddRef | The pointer can outlive map membership only if some other owner keeps it alive |
| `0x01021300` current-player cache | `SpacePlayerData+0x1c` owns one intrusive `cEmpire` reference; the accessor returns borrowed | A cached erased empire can remain allocated while being no longer a registry member |
| `cEmpire+0x84` political ID | Object field used by cache validation and lower-bound erase | It is a logical identity field, not proof that the `mEmpires` node key is synchronized |

The SDK calls `GetData` a reference-returning low-level API but its convenience `GetData<T>(nounID)` returns by value. The community tutorial's `auto creatures = GetData<cVehicle>()` therefore demonstrates snapshot-style ownership, not permission to retain the low-level manager-owned record.

## Architecture-impact summary

| Edge case | Static disposition | OpenSpore architecture effect | Runtime experiment priority |
|---|---|---|---|
| Missing/invalid object | Unsupported as a general fail-safe boundary; lower-bound successor behavior is direct | Must define exact vs ceiling lookup, null manager policy, and allocation-failure policy | **Yes, narrow and read-only** for the documented exact-miss contradiction |
| Duplicate publication | Conditional noun orphan hazard and star insert-or-replace behavior are direct; root-slot duplicate publication is unresolved | Requires atomic cache publication, deterministic replacement, and separate lifecycle ports | **Conditional**; duplicate root publication trace is useful, race reproduction is not yet justified |
| Rekey | Creation-scoped writer is supported; general indexed rekey transaction is not | Indexed identity must be immutable or rekey must atomically move map, cache, and dependent keys | **Only as a non-destructive observation**; do not synthesize a live rekey |
| Cache eviction | Noun paths show lazy invalidation, not proven per-key eviction; star cache has no erase-time eviction | Separate invalidate, evict, clear, and destroy operations | **No** for basic mechanics; use later only to characterize phase-specific policy |
| Stale pointer/handle | Supported for raw views, stale membership, and unproven slot teardown | Borrowed versus owned results and membership/generation validation must be explicit | **Yes** for slot liveness and teardown ordering, with memory sampling |
| Teardown while referenced | Separate payload and owner teardown are direct; global unpublication order is unresolved | Owner/borrower generation tokens or ordered teardown are required for raw handles | **Yes**, but the current probe tracer needs memory sampling |
| Repeated lookup after invalidation | Mixed: noun lazy refresh versus star identity-only cache hit | Callers must opt into refresh, exact membership, or cache bypass after invalidation | **No** for static semantics; natural lifecycle trace is supplementary |

## Edge case 1 — missing or invalid objects

### Competing hypotheses

**M1 — All public missing-object paths return null.** Prediction: a missing noun/empire key, null manager, null create result, or null element would have an explicit guard and return null/error.

**M2 — Missing keys are valid only under a no-greater-successor/membership invariant.** Prediction: absent keys with a greater successor are never exposed by normal callers, and raw helpers may rely on caller preconditions.

**M3 — Public SDK semantics are safer than the concrete lower-bound wrappers.** Prediction: the documented `GetEmpire` exact-null behavior is enforced by a wrapper before the lower-bound helper becomes observable.

**M4 — Low-level and convenience ModAPI paths have different failure contracts.** Prediction: the low-level API returns borrowed raw storage or a successor, while the value-returning convenience helper copies intrusive references and is safer for element lifetime.

### Predictions from current instructions

- `0x00b21340` with an absent noun key and a greater node returns the greater node's payload; only map end triggers create/insert.
- `0x00ba9370` with a missing political ID and greater key returns that greater key's `cEmpire*`; no exact-key check follows lower-bound.
- `0x00b201a0`, the noun invalidator, likewise lower-bounds the removed object's noun ID and can mark the greater successor before it separately scans cast-compatible categories.
- `0x00baf0b0` unconditionally writes `cEmpire+0x84` after allocation; a null allocation result is dereferenced.
- `0x00ba83a0` and `0x00dd85c0` also have no visible recoverable allocation-failure branch.
- `0x00b21340`, `0x00ba9370`, and `0x00bad7a0` do not test a null manager receiver.
- The noun create callback can visibly return null, but `0x00b21340` has no guard before reading the returned record's `needsUpdate` byte.
- `0x00b21410` immediately dereferences its object argument.
- `0x01021300` special-cases request `0xffffffff` to null without replacing an existing cache, but does not guard the selected manager or validate the lookup result.

### Evidence for and against

- **For M1:** SDK/community prose promises an active singleton, `GetEmpire` promises null for a missing political ID, and `CreateInstance` returns an object. Convenience APIs generally discourage direct error handling.
- **Against M1:** those are conceptual API contracts, not guards in the recovered bodies. All three lower-bound-based missing-key cases can return a successor. Null manager and allocation paths are preconditions/fatal cases, not explicit null results.
- **For M2:** normal star creation prechecks map membership before calling `0x00baf0b0`; erase is only called with a looked-up empire. These callers can enforce the membership invariant that the raw helpers omit.
- **Against M2:** `0x01021300` and other direct consumers do not perform exact validation, and the ModAPI exposes a public `cStarManager::GetEmpire` contract without exposing the membership precondition.
- **For M3:** the SDK's `GetEmpire` documentation explicitly says it returns null when no empire has the requested ID.
- **Against M3:** the current function attributed to that API is `0x00ba9370`, whose direct lower-bound/sentinel-only mechanics reject exact-null semantics. No exact-check wrapper was recovered on this path.
- **For M4:** `GameNounManager.h:97-106` returns a low-level reference, while `GameNounManager.h:174-193` returns a value. The community tutorial's `auto creatures = GetData<...>()` follows the latter form.

### Contradictions and limits

- SDK/community `GetEmpire` exact-null documentation conflicts with current binary lower-bound behavior.
- The SDK calls `GetData` conceptually immutable/active-instance oriented, while the concrete cache can return a mismatched successor and has no observable locking.
- No current instruction evidence proves that allocation failure is a supported gameplay outcome. Absence of a recovery branch supports a fatal/precondition interpretation, not a recoverable null contract.
- The lower-bound facts are direct. Whether normal gameplay ever presents a missing key to these functions remains unobserved.

### OpenSpore architecture decision

This edge case **affects architecture**. OpenSpore must not expose one ambiguous `find` operation:

- provide `ceilingByPoliticalId`/`ceilingByNounId` only if successor behavior is intentional;
- provide exact lookup as a separate wrapper with a postcondition check;
- reject null managers explicitly at public boundaries;
- make element and manager ownership distinct; and
- define allocation failure according to the chosen architecture rather than inheriting unchecked dereferences accidentally.

An exact wrapper can safely call the lower-bound primitive and reject a mismatched result. Removing lower-bound behavior is not required.

### Narrow runtime experiment

**Justified for one read-only question:** during a live space-stage state, call the documented `GetEmpire` with a reserved missing political ID immediately below a known empire, while tracing the call to `0x00ba9370` and its returned pointer. The expected positive observation is a greater-key successor with a different `cEmpire+0x84`.

This is interpretable because the call is read-only and the static prediction is exact. It resolves API-wrapper behavior, not publication identity. The current probe tracer can observe function entry registers, but comparing the returned object's `+0x84` requires a small memory-sampling extension or a purpose-built observation detour. Deliberately invoking null managers or allocation failure is **not** justified.

## Edge case 2 — duplicate publication

### Competing hypotheses

**D1 — Map uniqueness plus serial callers prevents duplicate cache-record publication.** Prediction: a second equal-key lookup never creates a new value, and every returned record pointer is the canonical map payload.

**D2 — Reentrant/concurrent noun misses can create an orphan record.** Prediction: both callers create records, the first insertion wins, the second helper reports `inserted=false`, but the losing `GetData` caller still returns its own newly created record.

**D3 — Duplicate empire creation is insert-or-replace.** Prediction: an equal key leaves one map node, stores the last completing object, releases the displaced map reference, and may return an object no longer present in the map.

**D4 — Duplicate root publication means the noun/star accessor pair should share one owner.** Prediction: both global words are updated together and share one teardown generation; otherwise phase/replacement events remain independent.

### Predictions and evidence

- `0x00ba8420` returns the existing equal-key node with `inserted=false` and does not replace its payload on that branch.
- `0x00b21340` calls the create callback before insertion, passes the created record as the proposed value, ignores the insertion helper's returned iterator and inserted flag, and continues with the record held in `EBX`.
- P-code forward tracing from the `0x00b21340 -> 0x00ba8420` call terminates at a phi fed by the created record and the non-end payload path; it does not show reassignment from the insertion result.
- Therefore, if the create callback re-enters `GetData` for the same noun, or another thread inserts between the initial lower-bound and `0x00ba8420`, the outer call can populate and return a record that did not win map publication. This is a static conditional hazard; actual reentrancy/concurrency is not proven.
- `0x00dd85c0` returns the payload slot for an equal existing key. `0x00baf0b0` then AddRefs the new object, stores it into that slot, and Releases the old map-owned object. The function returns the new object even if another interleaving replaces it afterward.
- `0x00bb1340` prechecks for an exact existing non-null payload before entering `0x00baf0b0`, which protects the normal serial creation path from this replacement.
- The four global root words remain physically distinct. Current direct-reference scans recover only getter reads and no concrete duplicate publisher/unpublisher.

### Evidence against and contradictions

- No recovered lock, atomic publication protocol, or explicit reentrant guard was found in the inspected functions, but absence of a visible lock is not proof that higher-level serialization cannot hold.
- Calling noun `GetData` repeatedly on an already published key does not create a second record; the hazard requires a race/reentrancy between lookup and insert.
- The SDK's singleton wording says nothing about duplicate record creation, duplicate map replacement, or root-word publication order.
- Existing KG/root-closure artifacts resolve successor semantics and direct reference topology but contain no duplicate-publication runtime evidence.

### OpenSpore architecture decision

This edge case **affects architecture**:

- noun cache creation must publish atomically and return the winning map-owned record, not the provisional callback result;
- rejected provisional records must have an explicit cleanup path;
- empire creation should be named `getOrCreate`/`upsert` and its replacement semantics made deterministic;
- a caller must not assume its returned raw object is still the registry payload after a concurrent replacement; and
- alternate/canonical root ports must accept explicit publication, replacement, duplicate-publication, and unpublication events even if a later runtime trace shows permanent value aliasing.

### Narrow runtime experiment

A read-only trace of both slot pairs plus the manager destructor/accessor calls is **justified** for ordinary publication and teardown, because it can show duplicate publication, replacement, and unpublication order without injecting faults.

Forced callback reentrancy or a two-thread same-key creation is **not yet justified**. It would be intrusive, timing-sensitive, and potentially destructive. A positive observation is strong; a negative run would not disprove the static conditional hazard. The existing observatory supports breakpoint timing and selected registers, but not the needed map-payload snapshots without extension.

## Edge case 3 — rekey

### Competing hypotheses

**R1 — `cEmpire::mPoliticalID` is immutable after creation/indexing.** Prediction: every write occurs before insertion, and no public supported operation changes a registered ID.

**R2 — `cGameData::SetPoliticalID` permits untracked mutation.** Prediction: a mod or indirect caller can change `cEmpire+0x84` without moving its `mEmpires` node.

**R3 — A hidden transaction erases old, writes new, and reinserts atomically.** Prediction: a general writer would update the map node key and coordinate dependent caches/references.

**R4 — Some lifecycle rekeys before or after publication.** Prediction: creation, load, save, ownership transfer, or phase transition writes the field and repairs registry state.

### Predictions and evidence

- `0x00baf0b0` writes `cEmpire+0x84` before calling the map access/upsert helper.
- `0x00c359a0` also writes `cEmpire+0x84` at entry. It has one recovered caller, `0x00bb1340`, on the empire creation/materialization path; no standalone erase-old/change/reinsert chain was recovered.
- The current `cEmpire.h` exposes `GetEmpireID` and stores `mPoliticalID` at `+0x84`; inherited `cGameData.h:70-71` exposes virtual `SetPoliticalID`/`GetPoliticalID`.
- The SDK gives no warning that `SetPoliticalID` is forbidden for a registered empire, and no transaction object is exposed for rekeying `mEmpires`.
- `0x00ba9370`, `0x00bad7a0`, and `0x01021300` read the object's current `+0x84`; the ordered map node stores a separate key at node `+0x10`.
- If those values diverge, exact lookup can miss and return a successor, erase can remove a greater successor, and the player cache can retain an object under its changed ID while registry membership remains under the old key.

### Evidence against and contradictions

- The recovered writers are creation-scoped and static caller analysis found no general rekey chain. This supports R1 for untouched original gameplay but not as a safe public ModAPI invariant.
- `0x00c359a0` is a generic `cGameData`-style initialization/finalization function by shape, but its only recovered caller prevents promoting a general rekey claim from the present bounded evidence.
- Existing KG and architecture reports explicitly preserve the general-rekey blocker; repeated statement of that blocker is not independent proof of immutability.

### OpenSpore architecture decision

This edge case **affects architecture**. A registered object's logical key cannot be independently mutable. OpenSpore should choose one of:

1. make political ID immutable after publication; or
2. expose only a manager-mediated rekey transaction that verifies membership, updates the ordered map, dependent registries, caches, and generations before publishing the new identity.

Exposing a raw `SetPoliticalID` on an indexed object would preserve the original inconsistency hazard. A lower-bound primitive is safe only after exact membership and key synchronization are enforced.

### Narrow runtime experiment

**A non-destructive observation is conditionally justified but not urgent.** Watch all writes to a live `cEmpire+0x84` through one controlled save/load and empire-creation path, recording the object's map position before and after each write. A post-insertion write is decisive evidence that R2/R4 occurs; no observed post-insertion write is only a scenario-bounded negative.

The current observatory tracer does not provide a data watchpoint or memory payload logging, so this needs a purpose-built read-only watchpoint. Intentionally calling `SetPoliticalID` on a live registered empire is **not justified** without an isolated disposable save because it can corrupt registry invariants and trigger destructive erase behavior.

## Edge case 4 — cache eviction

### Competing hypotheses

**C1 — Noun removal evicts the noun-specific vector record immediately.** Prediction: a remove path erases the `mNounMap` node keyed by the removed noun ID.

**C2 — Noun removal invalidates records lazily.** Prediction: remove marks `needsUpdate=1`; the next `GetData` clears, rebuilds, and clears the flag.

**C3 — The raw noun view is stable across invalidation but not across owner teardown.** Prediction: the map node/record address survives a lazy refresh, while vector iterators/references into the old buffer do not.

**C4 — The high-level `GetData<T>` result is an eviction-independent snapshot.** Prediction: clearing/rebuilding the manager cache does not destroy the caller's copied intrusive elements.

**C5 — Empire erase/current-player replacement share one eviction policy.** Prediction: empire-map erase clears `SpacePlayerData+0x1c`.

### Predictions and evidence

- `0x00b201a0` is a noun-cache invalidator. It lower-bounds the removed object's noun ID, sets the lower-bound payload's `needsUpdate` byte, then walks existing noun records and marks every clean record for which the removed object casts to that record's key.
- `0x00b225d0` calls `0x00b20d30` and then `0x00b201a0`, connecting object-removal work to cache invalidation.
- `0x00b21340` on a flagged record calls the clear callback, repopulates from `mNouns`, and clears `needsUpdate`.
- **Correction to prior interpretation:** disassembly of `0x00b21410` uses manager map `+0xd0`, not `mNounMap +0x98`. It lower-bounds an object's political ID, requires the `+0xd0` node payload to equal that object, erases through `0x01045590`, and may clear `+0x70`. It is not evidence of per-key `mNounMap` eviction. This contradicts the prior architecture report's identification of that function as a noun-map erase.
- No per-key `mNounMap` erase was recovered in this bounded work. The noun manager destructor at `0x00b22440` destroys `+0x98` in bulk.
- `tGameDataVectorT` stores `needsUpdate` and an EASTL vector of `intrusive_ptr` objects. The convenience helper returns this wrapper by value, copying intrusive element references.
- `0x00bad7a0` erases the empire map node and Releases only the map reference.
- `0x01021300` does not observe that erase. `0x01022460` independently clears/Releases the player cache and resets the request to `0xffffffff`.

### Evidence against and contradictions

- The invalidator's first lower-bound action can mark a greater successor even when the requested key is absent; the later all-record cast scan is independent. This is another successor hazard.
- Prior noun reports correctly recovered lazy `needsUpdate` refresh but over-attributed per-key eviction to `0x00b21410`. The current instruction receiver at `+0xd0` is decisive against that specific claim.
- The SDK's unmodifiable-vector wording and the value-returning helper support snapshot use, but do not guarantee safety for a caller who explicitly takes the low-level returned reference.

### OpenSpore architecture decision

This edge case **affects architecture**. OpenSpore must distinguish:

- lazy invalidation from eviction;
- stable record identity from stable vector iterators/element references;
- manager-map destruction from element-reference survival;
- map-membership invalidation from current-player cache clearing; and
- raw borrowed registry view from by-value snapshot.

A high-level snapshot can safely retain payload objects through `intrusive_ptr`, but it must not claim current registry membership after invalidation. A low-level view handle needs an owner generation and must not be retained across invalidate/evict/teardown unless its contract explicitly says the record address is stable.

### Narrow runtime experiment

**Not justified for the core decision.** The invalidation/clear/rebuild sequence and `0x00b21410` receiver are already instruction-level facts. A later natural lifecycle trace could characterize how many categories are marked and whether any unlocated per-key erase occurs, but the existing KG/runtime corpus does not justify making that the next experiment.

## Edge case 5 — stale pointer or handle

### Competing hypotheses

**S1 — Non-null raw pointers are valid until explicitly cleared.** Prediction: every erase/destroy path clears every borrowed alias or root word.

**S2 — Object liveness and membership are independent.** Prediction: an intrusive owner can keep an erased empire allocated while the registry no longer contains it.

**S3 — Cached vector validity is stronger than cached element validity.** Prediction: the `mNounMap` record survives lazy invalidation, but its vector storage and iterators are replaced.

**S4 — Root slots may remain stale across manager destruction.** Prediction: destructor paths free fields but do not clear/accessor-guard the global words.

### Predictions and evidence

- `0x00bad7a0` Releases the map-owned empire reference. If `SpacePlayerData+0x1c` owns another reference, the object remains allocated; if it is the current-player cache, that reference specifically keeps it alive after erase.
- `0x01021300` validates a cache hit only by `cached->mPoliticalID == requestedId`; it does not test membership or generation. Therefore an erased unchanged-ID empire continues to hit.
- The cache's own reference prevents immediate dangling storage, but all borrowed aliases to the empire, manager, or relationship manager remain unsafe when their owners die.
- `0x00b21340` returns a raw manager-owned vector record. Lazy invalidation reuses the record but clear/rebuild may replace the vector's allocation. Iterators or references into the old vector are stale; the record address alone is not a general snapshot.
- The value-returning `GetData<T>(nounID)` copies intrusive elements, so those elements survive cache invalidation and manager teardown while other references remain alive.
- Current noun and star destructors destroy their internal maps/fields, but direct-root scans still show only getter reads and no recovered global unpublication. A slot can therefore not be assumed live merely because it is non-null.
- The four global words are physically distinct, so a handle cannot encode both equality and inequality of alternate/canonical manager values.

### Evidence against and contradictions

- No unlocated unpublication is proven. The statement that slots “may remain stale” is a lifecycle risk under the observed preconditions, not a runtime observation of a particular stage exit.
- The SDK's intrusive-pointer guidance supports payload-lifetime safety but is commonly phrased as “don't worry about deleting”; it does not make a raw pointer current or registry-valid.
- The noun low-level record may remain at the same address across lazy refresh, but no lifetime guarantee survives manager destruction or an unlocated per-key erase.

### OpenSpore architecture decision

This edge case **strongly affects architecture**. OpenSpore needs typed validity domains:

- **object-live** is insufficient;
- registry membership needs membership/generation validation;
- borrowed handles need owner generation and explicit invalidation on replacement/teardown;
- snapshots own payload references and should be labeled as historical snapshots; and
- root handles need `published/live/replaced/unpublished` lifecycle states rather than a bare nullable pointer.

Returning only `cEmpire*` or `tGameDataVectorT*` loses information needed to distinguish these states.

### Narrow runtime experiment

**Justified for root-slot liveness, not for payload reference counting.** Probe the four root getters, noun manager destructor, star manager destructor, and `0x01022460`; sample all four global words and the manager generation/validity at each event. This can show whether roots are un-published, replaced, equal, or merely left unchanged across a real transition.

Interpretability limits are important:

- observing a stale non-null slot after destructor entry is positive evidence of a stale-window hazard;
- observing null after teardown does not prove every path clears before all possible callers;
- function timing alone cannot prove that borrowed child pointers are dead, so memory/generation snapshots are required; and
- the current probe tracer records selected entry registers but does not sample arbitrary memory or returns, so it is insufficient without a narrowly scoped extension.

## Edge case 6 — teardown while referenced

### Competing hypotheses

**T1 — Intrusive references make teardown safe for every alias.** Prediction: every returned noun, vector view, empire, relationship manager, and root manager is independently retained.

**T2 — Payload references are safe, owner-backed handles are not.** Prediction: copied noun elements/empires survive, while manager-owned records, registries, relationship fields, and root words do not.

**T3 — Global unpublication occurs before field destruction.** Prediction: all root words are null before maps and owned fields are released.

**T4 — Teardown order is hidden/opaque and may be caller-dependent.** Prediction: static consumers can continue using a root word while its manager fields are already destroyed.

### Predictions and evidence

- SDK getters return raw pointers without AddRef. The noun `GetData` low-level boundary also returns a borrowed record.
- `0x00b22440` destroys noun manager fields including the `+0x98` map, `+0xd0` map, and other owned vectors/pointers, then changes the vtable state.
- `0x00babe70` destroys relationship state and other star-manager fields, then recursively Releases and frees the `mEmpires` map nodes.
- Neither inspected destructor directly clears the four noun/star root words. The direct-root evidence remains one noun getter read per word, two star getter reads for the alternate word, and one canonical getter read.
- `0x01022460` separately clears the current-player cache and resets its request. No proven relative order ties it to manager destruction or root unpublication.
- The convenience noun wrapper's copied intrusive elements and `SpacePlayerData`'s cached empire can outlive their registries, but neither keeps the manager, relationship manager, vector record, or root slot alive.

### Evidence against and contradictions

- An unlocated common phase/service publisher may unpublish roots before destructor invocation. Current static evidence neither confirms nor excludes that ordering.
- High-level intrusive-pointer examples are safe for payload deletion but can create a false impression that every returned interface is independently owned.
- Destruction of a manager's `mNounMap` nodes does not by itself prove payload objects die because other intrusive references can remain.

### OpenSpore architecture decision

This edge case **strongly affects architecture**. Teardown must be ordered and observable:

1. mark service/root unavailable;
2. prevent new lookups;
3. invalidate dependent handles/caches;
4. release owner-held references;
5. permit separately owned payload snapshots to remain valid; and
6. free manager-owned storage last.

A borrowed result may outlive registry membership only if explicitly documented; it may not outlive its owner/generation without an independent intrusive reference.

### Narrow runtime experiment

**Justified and interpretable with one condition:** run a controlled stage transition that destroys or replaces the active noun/star managers while tracing root getters and destructors, and sample slot values plus dependent handle validity at each event. A positive trace closes relative teardown/unpublication order for that scenario.

A single scenario is not universal proof. The experiment should not dereference stale handles merely to force a crash; validity should be inferred from lifecycle events, vtable/generation state, and controlled subsequent lookup only after a new manager is published. The current observatory can time entry but needs memory sampling to answer the actual question.

## Edge case 7 — repeated lookup after invalidation

### Competing hypotheses

**Q1 — Every repeated lookup rechecks authoritative membership.** Prediction: noun and empire helpers call lower-bound or exact validation on every call.

**Q2 — Noun invalidation is lazy and the next `GetData` refreshes the same record.** Prediction: `needsUpdate` causes clear/rebuild on the next lookup, even without erasing the map node.

**Q3 — Current-player cache hits bypass invalidated membership.** Prediction: after empire erase, repeated lookup with the same request returns the cached object without calling the manager.

**Q4 — Repeated lookup after manager teardown is safe if the root remains non-null.** Prediction: roots are cleared before manager fields or repeated lookup handles a destroyed generation.

### Predictions and evidence

- `0x00b21340` on a `needsUpdate=1` record clears it, filters current `mNouns`, appends matches, and clears the flag. Repeated lookup should then return the rebuilt content.
- The noun map node key is not corrected when a missing request reuses a greater successor. Rebuilding the successor payload with the missing request's filter does not change the successor node key, so repeated requests continue to observe the same mismatched cache record.
- `0x01021300` on an ID-equal cached empire jumps directly to the return path; repeated lookup does not call `0x00ba9370` and cannot discover map erase.
- If the request changes to a missing ID whose successor is the cached empire, the hit test fails, lookup runs again, and the same pointer is stored without AddRef/Release because `new==old`.
- If the request becomes `0xffffffff`, the function returns null and deliberately leaves the old cache/reference untouched; this is not invalidation.
- `0x01022460` is the separate explicit cache clear/reset path.
- If manager teardown leaves a root word non-null, both noun and star raw helpers have no generation/null guard; repeated lookup can dereference destroyed state.

### Evidence against and contradictions

- The noun invalidator and player cache likely run on the same gameplay thread in ordinary paths, so the unguarded window may be small. No lock or synchronization guarantee was recovered.
- The SDK's “active instances” and exact-empire wording implies freshness, but the concrete cache validates only identity and can retain an erased member.
- Existing KG records the successor-tolerant cache but no runtime trace demonstrates that the current-player empire is naturally erased while still requested.

### OpenSpore architecture decision

This edge case **affects architecture**. Repeated lookup is not automatically a refresh. OpenSpore should expose explicit choices:

- `lookupExactCurrent` rechecks membership/generation;
- `lookupCachedIdentity` may return a stale but live snapshot only when labeled;
- `refreshAfterInvalidation` forces a lookup; and
- a removed/rekeyed object invalidates dependent cache generations.

Noun records should not silently change semantic key under a missing request. A successor-tolerant API needs the request key and actual record key reported together, or should be quarantined as a private compatibility primitive.

### Narrow runtime experiment

**Not justified for the core semantics.** Current instructions already predict the repeated-call outcomes. A natural runtime trace could count hit-versus-refresh calls and observe teardown windows, but it would not resolve missing exact membership, hidden cache policy, or rekey support. Synthetic empire erase/rekey is too destructive for the current evidence.

## Contradictions carried forward

1. **SDK/community versus binary star lookup:** documented exact-null `GetEmpire` versus direct lower-bound/successor behavior.
2. **Prior noun report versus current disassembly:** `0x00b21410` operates on `cGameNounManager+0xd0`, not `mNounMap+0x98`.
3. **KG semantic node versus direct evidence:** `semantic:function:00b21340` still describes an unresolved message-handler/list-predicate role. The root-closure node and current disassembly instead establish `GetData` over `mNounMap`/`mNouns`; the semantic node is stale and should not drive architecture.
4. **Singleton wording versus storage/lifecycle:** both noun and star pairs are singleton APIs conceptually, but they use distinct global words with no recovered common publisher, unpublisher, or runtime equality observation.
5. **Safe-looking ModAPI usage versus raw mechanics:** `auto` noun snapshots and intrusive pointers protect payload lifetime but not registry membership, owner generation, or rekey consistency.
6. **Create/destroy docs versus null paths:** APIs promise objects but concrete allocation/null paths contain no recoverable error channel. This is a precondition/fatal-outcome distinction, not a supported null contract.
7. **Bounded negative evidence:** no general rekey transaction, no direct root writer, no common teardown order, and no per-key `mNounMap` erase were found in the inspected surfaces. These are bounded negatives, not proof of universal absence.

## OpenSpore minimum-safe contract

1. Keep noun and star alternate/canonical root ports separate and explicit; do not merge them from singleton wording.
2. Give root handles lifecycle states and generations: unpublished, published, replacing, live, unpublishing, dead.
3. Keep lower-bound/ceiling lookup private or explicitly named; expose exact-current lookup with postcondition validation.
4. Publish noun cache records atomically and return the map-owned winner; clean up provisional losing records.
5. Define empire duplicate creation as deterministic get-or-create/upsert; never promise that a raw return remains current after concurrent replacement.
6. Make indexed political ID immutable or mediate rekey as one transaction across registry keys and dependent caches/generations.
7. Separate lazy invalidate, per-key evict, cache clear, registry erase, and owner destroy.
8. Distinguish borrowed manager/view handles from by-value intrusive snapshots.
9. Validate membership/generation when a caller needs current state; identity alone is insufficient.
10. Order teardown as unpublish → block new lookup → invalidate dependent handles → release owners → destroy storage.
11. Make public null-manager and allocation-failure behavior explicit in OpenSpore rather than copying unchecked dereferences.
12. Never use a bare `cEmpire*` or noun-view pointer as proof of current registry membership after invalidation.

## Runtime experiment decision

A single narrow read-only experiment is justified as the next runtime task: trace the four root slots and both manager teardown/lookup paths through one real noun/star phase transition, with memory sampling. It can answer publication equality, replacement, unpublication, and stale-root timing for that scenario.

The other proposed edge-case experiments are not currently justified:

- forced null allocation, duplicate race, live rekey, or live erase can violate preconditions and create destructive false evidence;
- basic missing-key, lazy invalidation, cache-bypass, and repeated-lookup behavior is already statically decisive enough for architecture; and
- a single ordinary stage run cannot prove absence of exceptional or hidden writers.

The existing `tools/observatory/probe_tracer.cpp` can timestamp probes and record `this`, `EAX`, `EBX`, `ECX`, and `EDX` at each hit (`probe_tracer.cpp:1074-1084`). It does not currently capture arbitrary memory, `ESI`, or return values. The justified root/teardown experiment therefore requires a narrow read-only sampling extension before execution.

## References

### Current static/Ghidra anchors

- `0x00b21340` — noun `GetData`: lower-bound, create/insert on end only, callback rebuild, borrowed return.
- `0x00ba8420` / `0x00ba83a0` — noun-map insertion/duplicate result and node allocation.
- `0x00b201a0` — noun `needsUpdate` invalidator, including lower-bound successor marking.
- `0x00b225d0` — object-removal/internal path that reaches `0x00b201a0`.
- `0x00b21410` — `+0xd0` map erase/payload check, not `mNounMap` erase.
- `0x00b22440` / `0x00b23430` — noun-manager destructor/free chain.
- `0x00ba9370` — empire lower-bound/ceiling lookup.
- `0x00baf0b0` / `0x00dd85c0` — empire allocation, political-ID write, and insert-or-replace payload slot.
- `0x00bb1340` — normal serial precheck and empire creation call.
- `0x00bad7a0` — membership-assuming lower-bound empire erase.
- `0x00c359a0` — political-ID writer with one recovered creation-path caller.
- `0x01021300` — current-player identity cache and successor refresh.
- `0x01022460` — separate SpacePlayerData cache teardown/reset.
- `0x00babe70` / `0x00d0c930` — star-manager field teardown and `mEmpires` node/payload release.
- `0x0167eae0`, `0x0167eb60`, `0x0167eae4`, `0x0167eb0c` — distinct root words with getter reads only in the current direct-reference surface.

### Existing repository evidence

- `knowledgegraph/research/architecture-resolution/track-01-noun.md:57-78,94-112`
- `knowledgegraph/research/architecture-resolution/track-02-star.md:105-170,221-258`
- `knowledgegraph/research/root-closure/track-d-noun-registry.md:55-206`
- `knowledgegraph/research/root-closure/followup-noun-boundary.md:53-103,176-184`
- KG node `fun:00b21340` (`root_closure_contract`: GetData/lower-bound; `runtime_evidence=false`)
- KG node `fun:01021300` (`root_closure_contract`: current-player cache/lower-bound; `runtime_evidence=false`)
- KG node `semantic:function:00b21340` (stale contradictory message-handler description)

### SDK and community sources

- `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/SubSystem/GameNounManager.h:36-67,96-114,130-152,174-193`
- `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/tGameDataVectorT.h:29-87`
- `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/SubSystem/StarManager.h:100-170,270-331`
- `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/cEmpire.h:45-59,87-134`
- `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/cGameData.h:34-70,80-90`
- `https://modapi-docs.sporecommunity.com/class_simulator_1_1c_game_noun_manager.html`
- `https://modapi-docs.sporecommunity.com/class_simulator_1_1c_star_manager.html`
- `https://modapi-docs.sporecommunity.com/class_simulator_1_1c_game_data.html`
- `https://sporemodder.wordpress.com/2019/02/27/modapi-tutorial-classes-simulator-event-listeners-schedules-and-update-scripts/`
