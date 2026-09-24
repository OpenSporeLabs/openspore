# Roots and publication review

## Review scope and verdict

This review compares the isolated noun/star lifecycle reports, especially tracks A, B, C, and E, against the root-closure, architecture-resolution, blocker-A, shared-state, gameplay-data, serialization, and type-archaeology artifacts. It does not modify those artifacts. The binary under review is the pinned `SporeApp.exe` 3.1.0.22 image, SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`, and all evidence below is static unless explicitly labelled runtime-needed.

**Overall verdict:** the reports support a strong mechanical boundary and a useful manager-local lifecycle model. They do not support a recovered original root-publication, root-equality, root-lifetime, or cross-root teardown model. The final synthesis may safely state that there are four physically distinct four-byte slots, that `00b3d300` is a noun-manager-compatible alternate accessor, and that `00b3d2a0` is a `cStarManager`-compatible alternate accessor. It must not state that either accessor returns a proven canonical manager owner, that the alternate and canonical values are equal or unequal, or that manager construction/record lifecycle is root publication.

The safe compatibility conclusion is narrower than “four recovered owners”: **four separate, opaque observation ports, with host-side publication/replacement/invalidation/unpublication policy, and no original-compatibility claim.** This is a clean-room boundary, not a recovered original ABI.

## Evidence scale used here

- **Static fact:** directly established by a pinned instruction, decompilation body, data/layout read, direct xref, or a bounded memory/reference scan.
- **Interpretation:** a semantic label supported by multiple static facts but not proven as exact original class, owner, or runtime behavior.
- **Bounded negative:** a scan did not find a class of operation in the inspected surface. It is not proof of universal absence.
- **Runtime-needed:** a question that static analysis cannot close, usually publication order, value equality, liveness, or teardown timing.

The repository consistently states that there is no original-process trace for these roots and that no `OBSERVED` or `VERIFIED` original-runtime claim is available. See `docs/analysis/simulator-root-closure.md:1-5`, `knowledgegraph/research/root-closure/root-closure-f0e310e0.json:6-35`, and `knowledgegraph/research/architecture-resolution/followup-03-root-publication.md:9-14`.

## 1. Facts that survive adversarial comparison

### 1.1 Accessor mechanics and physical storage

The following are high-confidence static facts:

| Accessor | Direct body | Backing word | Direct result |
|---|---|---|---|
| `00b3d300` | `MOV EAX,[DAT_0167eae0]; RET` | `DAT_0167eae0` | raw four-byte value |
| `00b3d400` | `MOV EAX,[DAT_0167eb60]; RET` | `DAT_0167eb60` | raw four-byte value |
| `00b3d2a0` | `MOV EAX,[DAT_0167eae4]; RET` | `DAT_0167eae4` | raw four-byte value |
| `00b3d3a0` | `MOV EAX,[DAT_0167eb0c]; RET` | `DAT_0167eb0c` | raw four-byte value |

All four accessors are read-only loaders at their own bodies. They do not validate, allocate, lock, AddRef, Release, or transfer ownership. The four words are distinct four-byte storage locations. The direct-reference and bounded literal scans found reads at the accessor sites, with no direct writer, clear, or equality operand. This rejects physical aliasing; it does not reject value aliasing. See `knowledgegraph/research/architecture-resolution/followup-03-root-publication.json:103-118,181-186` and `knowledgegraph/research/root-closure/followup-global-slots.md:26-35`.

The canonical labels are useful access-path names, not proof of canonical ownership:

- `00b3d400` is the named `Simulator::cGameNounManager::Get` accessor in the available static/type evidence.
- `00b3d3a0` is the named `Simulator::cStarManager::Get` accessor in the available static/type evidence.
- `00b3d300` and `00b3d2a0` are distinct alternate accessors.

The strongest safe terminology is therefore “alternate/canonical accessor path,” not “the active owner” and not “the obsolete getter.”

### 1.2 Noun receiver compatibility

Track A and the root-closure follow-up recover a decisive receiver chain:

```text
00b3d300
  -> 00bff408
  -> MOV ECX, EAX
  -> 00b21340
```

`00b21340` uses receiver fields at `+0x98` and `+0x78`, matching the `cGameNounManager` noun-map and noun-list layout in the imported/current static evidence. This is high-confidence evidence that the return is used as a noun-manager-compatible receiver. It is not proof that the pointer is the object allocated by `0x00b232b0`, that the global slot owns it, or that it is the same value as `DAT_0167eb60`.

The exact `cGameNounManager` class association is therefore **supported at the receiver/layout level**, not closed as a unique C++ identity. The binary has no MSVC RTTI, and the type-archaeology synthesis explicitly treats vtable candidates, shared layouts, and SDK names as structural rather than unique hierarchy proof. See `docs/analysis/type-archaeology.md:60-70,337-356`.

The reports that call `00b3d300` a generic context or service locator are too weak where the direct noun field-use chain exists. The reports that call it simply the canonical `cGameNounManager*` are too strong. The synthesis should use:

> `00b3d300` is a raw accessor for an alternate global noun-manager-compatible receiver; its exact owner and relation to the canonical noun slot are unresolved.

### 1.3 Star receiver compatibility

The star alternate path has independent field-use support:

- `00ba9370` treats the returned receiver as a `cStarManager`-compatible object and reads the empire map at `+0x150` and the end/anchor storage at `+0x154`.
- `00b3d2c0` directly reads `DAT_0167eae4` into `ECX` and reaches `00c4f030`, which reads receiver `+0x204`, matching the SDK `mpRelationshipManager` field.
- `01021300` uses the alternate accessor on cache miss or ID mismatch before calling `00ba9370`.

This makes “alternate `cStarManager`-compatible accessor” a sound static interpretation. It does not make `00b3d2a0` the canonical `cStarManager::Get`; the latter is `00b3d3a0 -> DAT_0167eb0c`. It also does not prove that `DAT_0167eae4` and `DAT_0167eb0c` contain the same pointer, that either slot owns the manager, or that the `+0x204` field is aliased by any separate relationship-manager global.

### 1.4 Noun materialization and owner-local lifecycle

Track B, the architecture-resolution noun reports, and the root-closure JSON support a substantial local model:

1. `00b20c60` obtains a concrete game-data object through the class/factory path, installs intrusive list membership, assigns the runtime object ID, links the object into manager `mObjects +0x10c` and `mNouns +0x78`, and calls `00b201a0` invalidation.
2. `00b21340` performs a lazy noun-map lookup/materialization over `mNounMap +0x98`: lower-bound, end-only branch, callback create/insertion, conditional clear/rebuild, filter `mNouns`, add, and clear `needsUpdate`.
3. `00b20d30` performs subtype teardown and unlinks the object from `mNouns`.
4. `00b225d0` stages destruction, retains a pending reference in `field_80 +0x80`, invokes the teardown/invalidation path, and defers some reclamation.
5. `00b22960` later prunes `mObjects` and drains/releases the pending-destroy retention.
6. Manager teardown releases manager-local maps, vectors, lists, and selected fields.

The safe ownership language is “manager-local list/map/vector participation and reference operations.” The evidence does not show that the noun manager is the sole owner of every noun, nor that any of these paths writes a root word.

The noun ABI must be stated as **four callback pointers plus a noun ID**, not “five callbacks.” The returned `tGameDataVectorT<cGameData>*` is a borrowed manager-owned record; the vector elements are separately reference-managed by the callback/container path. See `knowledgegraph/research/root-closure/followup-noun-boundary.md:38-68,84-103` and `knowledgegraph/research/root-closure/root-closure-f0e310e0.json:456-525`.

### 1.5 Star materialization and ownership

Track C provides the strongest bounded evidence for the layered star graph:

- `cStarManager` owns/holds manager-local collections of `cStarRecord` references, empire references, home-star map entries, and a live-planet cache.
- `cStarRecord` is a separate refcounted/serializable representation and holds `cPlanetRecord` references and generation/save metadata.
- `cStar` is a live `cGameData`-derived noun with links to a star record and solar system.
- `cSolarSystem` points back to the live star and holds live planet references.
- `cPlanet` points to a `cPlanetRecord` and is retained by manager/system caches.
- `cEmpire` separately holds `cStarRecord` references and home identity fields.

The key safe conclusion is **no single generic noun owner**. A live `cStar` and `cStarRecord` are distinct physical representations and typed links; their logical association cardinality is not fully closed. `cStarManager` is a major registry/cache owner, not a proved sole owner of all star-related identity. See `knowledgegraph/research/noun-star-lifecycle/track-c-star-publication.md:17-26,502-513`.

The star materialization path is a sequence of bounded boundaries, not one proven call chain:

```text
star-record generation/registry
  -> cStarRecord state
  -> cPlanetRecord state
  -> record-to-live-planet lookup/materialization
  -> cSolarSystem load and live planet collection
```

The repository correctly does not promote `cStarRecord` to a live `cStar`, `cPlanetRecord` to a `cPlanet`, or a star database checkpoint to root-pointer serialization.

## 2. Contradictions and overstatements that must be corrected

### 2.1 “cGameNounManager” versus “context/owner candidate”

Track A and `followup-global-slots.md` promote `00b3d300` to an alternate noun-manager-compatible receiver because of the `00bff408 -> 00bff426 -> 00bff428 -> 00b21340` chain. The earlier `track-a-service-identity.md` and `followup-receiver-provenance.md` retain more conservative “shared context/owner candidate” wording.

**Adjudication:** the later receiver/field evidence supersedes the generic-context reading for the selected consumer window, but it does not prove the unique class or owner of the global pointer. The final synthesis should retain “noun-manager-compatible receiver” and avoid “canonical noun owner.”

### 2.2 Caller-count and xref-count discrepancy

The reports use different units for the canonical noun getter. Track A and the root-closure metrics report 43 direct callers for `00b3d400`, while Track B reports 63 direct xrefs for the same accessor. This may be a caller-versus-callsite or snapshot/tool-boundary discrepancy, but the reports do not establish the reconciliation. The final synthesis should not use either number as a semantic liveness or ownership fact. The canonical star comparison has the analogous issue: the committed xref projection reports no named caller, while raw disassembly finds the `00b5ca50` thunk. Both cases are evidence of measurement boundaries, not proof that a path is dead or live.

### 2.3 “Five callbacks” versus four callbacks plus noun ID

Some interface/report wording calls the `00b21340` argument tuple “five callbacks.” The direct ABI and current SDK export show four callback pointers plus `uint32 nounID`. The root-closure JSON records the latter. The synthesis must use the corrected form and should not count the noun ID as a callback.

### 2.4 “Matching invalidation/erase” versus lower-bound-selected behavior

Several reports use “matching” for noun invalidation or erase and for empire erase. The direct helper behavior is lower-bound. `00b21340` checks only map end, and `00b201a0` similarly lower-bounds before marking a vector dirty. `00ba9370` checks only end, and `00bad7a0` lower-bounds before removing the selected map node. The correct description is “lower-bound-selected” unless exact membership is separately proven.

This matters even if callers normally pass an existing key: the static body itself does not establish the membership invariant. A clean-room exact lookup must add a key/identity postcondition rather than silently claim the original wrapper is exact.

### 2.5 `00b21410` is not a `mNounMap +0x98` erase

The strongest correction is explicit in Track G and supported by the later noun-boundary artifacts. `00b21410` uses manager map storage at `+0xd0`, checks the selected payload against the object, erases through `01045590`, and may clear owner `+0x70`. It is not evidence that normal individual noun destruction erases `mNounMap +0x98` by noun ID.

The safe lifecycle statement is:

```text
create -> eager mObjects/mNouns publication
lookup/materialize -> lazy mNounMap record
invalidate -> needsUpdate
destroy queue -> mNouns logical unlink and deferred reclamation
manager teardown -> manager-wide map/list cleanup
```

A normal noun destroy does not have recovered `mNounMap +0x98` per-key eviction. A cache node may survive with an empty or refreshed vector until manager-wide cleanup.

### 2.6 “cStarManager owns star identity” versus layered ownership

Track C correctly rejects sole ownership. The final synthesis must distinguish:

- manager-owned references to `cStarRecord` values;
- empire-owned references to `cStarRecord` values;
- live `cStar` links to record and solar system;
- solar-system ownership of live planets;
- manager/system caches of live planets;
- `cPlanet` links to `cPlanetRecord`.

“Registry owner” is safe. “Sole owner of star identity” is not. “Materialization of a live star” should not be used as shorthand for either record generation or root publication.

### 2.7 “Opaque publication is the leading explanation” is too strong

The direct scans found no writer, and the slots lie in writable zero-fill `.data` storage, so some indirect publication mechanism is possible. That does not establish that opaque/bulk publication is more likely than always-equal publication, phase-specific publication, stale canonical storage, or another service-layer mechanism. The adversarial blocker review correctly says the negative does not select a leading mechanism.

Final wording should be:

> No direct, literal, bounded computed, or inspected lifecycle writer was recovered; the publication mechanism remains unresolved. Opaque, computed, bulk, external, loader, and phase-specific mechanisms are not excluded.

### 2.8 Raw pointer persistence is a design boundary, not a proven original negative

The reports correctly reject treating raw root pointers as durable save identity. The stronger statement “the original does not serialize roots” is not proven by a negative root xref scan. The safe conclusion is:

- raw host-pointer persistence is unsafe and unauthorized for the clean-room model;
- `cStarRecord` and selected serializable data are persistence candidates;
- `stars.db.tmp -> stars.db` is a bounded database replacement;
- root publication/restore and exact save field coverage remain unresolved.

## 3. Missing xrefs and missing joins

The following absences are important and should not be hidden by a confident lifecycle diagram.

### 3.1 Root publication and unpublication

For each of `DAT_0167eae0`, `DAT_0167eb60`, `DAT_0167eae4`, and `DAT_0167eb0c`, the focused corpus lacks:

- a concrete allocation-to-slot store;
- a service-registration helper that receives a manager pointer and writes the slot;
- a common/paired publisher for alternate and canonical words;
- a replacement/rebind path;
- a direct or joined unpublication/clear path;
- an equality operation that joins the alternate and canonical values;
- a runtime snapshot of first publication, phase replacement, and final teardown.

The missing xrefs are not limited to literal direct references. The reports explicitly preserve unresolved pointer-derived, bulk-copy, external, loader, unresolved-code, and runtime publication possibilities.

### 3.2 Manager construction to global root

`00b60d80` constructs and registers a noun-manager-shaped object and later a star-manager-shaped object. `00b232b0` and `00bae490` initialize manager-local fields. The parent/vector registration path in `00b61bd3..00b61c5d` is a publication candidate for manager retention, but no concrete xref joins that retained object to either noun root. The same gap exists for the star manager. Constructor order is not root publication order.

### 3.3 Canonical consumer provenance

The canonical star getter has an executable thunk at `00b5ca50`, data-referenced from `0146286c`, which calls `00b3d3a0` and dispatches through the returned vtable. The canonical noun getter has ordinary consumers, including `00aebe90`, but the selected receiver windows for `00b1fdb0` and `00b25fb0` are dominated by the alternate path. Missing data:

- the owner/caller chain for the unowned star thunk;
- the allocation/registration relation between canonical star getter consumers and `00bae490`;
- a direct canonical noun consumer that also establishes root owner/lifetime.

Sparse fan-in cannot settle liveness.

### 3.4 Noun cache ownership and race behavior

The create callback allocates a `0x18` vector record, while `00ba8420` can allocate a separate `0x18` map node. The reports do not close which value is published on duplicate insertion, whether a losing provisional record is cleaned up, or whether reentrancy/concurrency can return a non-map-owned record. This is an edge-case architecture concern, not a claim that a race occurs in normal play.

The map lower-bound and end-only check are direct. Locking, reentrancy, allocation failure, and partial-materialization behavior remain unresolved.

### 3.5 Star erase membership and cache invalidation

`00bad7a0` erases a lower-bound-selected empire map node and releases its map-owned reference. `01022460` separately clears/releases the current-player empire cache. No recovered path joins the two operations. The static consequence is that a cache-owned reference can keep an erased empire alive, but the reports correctly leave the natural gameplay occurrence of that state runtime-unobserved.

The exact membership invariant at all erase call sites is not closed. A clean-room API should require exact membership or make the selected node/key explicit.

### 3.6 Logical star identity and persistence association

The evidence is strong for distinct physical representations and typed links:

```text
cStar -> cStarRecord
cStarRecord -> cPlanetRecord
cSolarSystem -> cStar
cPlanet -> cPlanetRecord
```

It is insufficient to prove a one-to-one logical lifecycle between every live `cStar` and `cStarRecord`, or the exact order in which saved records are restored, live stars are constructed, active star/planet references are rebound, and graphics materialization occurs. The restore path and pointer remapping remain unknown.

## 4. What can safely feed the final synthesis

### Safe claims

The final synthesis may use the following as bounded static conclusions:

1. `00b3d300` is a raw no-argument load of `DAT_0167eae0`, and selected consumers use the result as a noun-manager-compatible receiver.
2. `00b3d400` is the named canonical noun getter over the distinct word `DAT_0167eb60`; the binary does not prove value equality or a common publisher with the alternate noun word.
3. `00b3d2a0` is a raw no-argument load of `DAT_0167eae4`, and selected consumers use the result as a `cStarManager`-compatible receiver.
4. `00b3d3a0` is the named canonical star getter over the distinct word `DAT_0167eb0c`; the binary does not prove value equality or a common publisher with the alternate star word.
5. The four words are physically distinct. This is a storage statement, not a four-owner statement.
6. Noun object creation, manager-local list publication, lazy vector materialization, invalidation, logical list erase, deferred reclamation, and manager-local teardown are substantially supported.
7. Noun and empire lookup paths used here are lower-bound/ceiling operations, not exact finds. Exact lookup requires an added postcondition.
8. Star records, live stars, planets, planet records, solar systems, empires, and manager caches are separate physical/typed domains. `cStarManager` is a registry/cache owner, not a proven sole owner of star identity.
9. Empire map erase and current-player cache teardown are separate operations. A cache hit validates object ID, not registry membership or generation.
10. `cStarRecord` is a serializable/persistence candidate; the manager, roots, caches, and raw live pointers are not established save fields.
11. A compatibility-excluded clean-room model may use separate opaque root observations and explicit host-side lifecycle policy, provided it does not claim original publication, equality, ownership, or teardown semantics.

### Claims to reject or downgrade

The final synthesis should not use these as facts:

- “The four slots have four owners.”
- “Alternate and canonical roots are always equal.”
- “Alternate and canonical roots are always unequal.”
- “The alternate accessors are the active owner and the canonical getters are dead.”
- “Manager construction publishes a root.”
- “Manager teardown unpublishes a root.”
- “`00b21410` erases `mNounMap +0x98`.”
- “Noun invalidation/erase is exact-key.”
- “`00bad7a0` definitely erases the requested empire without a membership invariant.”
- “Empire-map erase invalidates the current-player cache.”
- “`cStar` and `cStarRecord` are the same object or necessarily one-to-one.”
- “A `Write`/database replacement proves a complete save or root restore.”
- “No direct writer was found, therefore no writer exists.”
- “A four-port seam reproduces the original four-owner lifecycle.”

## 5. Proposed high-level answers to questions 1–11 and 14–16

The prompt did not provide a separate numbered question list. To make the requested answer set auditable, the numbering below maps the mission topics to the following high-level questions. Questions 12 and 13 are intentionally omitted as requested.

| Question | Proposed high-level answer | Status |
|---|---|---|
| **1. What does `00b3d300` do?** | It loads the raw four-byte value in `DAT_0167eae0` and returns it without validation, allocation, locking, or reference management. Selected consumers pass it into noun-layout operations. | Static fact, high confidence; exact class/owner not closed. |
| **2. What does `00b3d2a0` do?** | It loads the raw four-byte value in `DAT_0167eae4` and returns it without validation, allocation, locking, or reference management. Selected consumers use it as a `cStarManager`-compatible receiver. | Static fact plus strong layout interpretation. |
| **3. What are the canonical getters?** | `00b3d400 -> DAT_0167eb60` is the named noun getter; `00b3d3a0 -> DAT_0167eb0c` is the named star getter. Both are raw borrowed loaders. | Static/name-supported; naming does not prove publication ownership. |
| **4. Do the four target words physically alias?** | No. They are four distinct four-byte storage words. This rejects physical aliasing only. | Static fact, high confidence. |
| **5. Do `DAT_0167eae0` and `DAT_0167eb60` have the same value?** | Unknown at every lifecycle point. No common writer, equality operation, replacement order, or runtime equality observation was recovered. | Unresolved blocker. |
| **6. Do `DAT_0167eae4` and `DAT_0167eb0c` have the same value?** | Unknown at every lifecycle point. The alternate path is operationally prominent and the canonical path is sparse, but that does not prove equality, inequality, or staleness. | Unresolved blocker. |
| **7. Is `00b3d300` a `cGameNounManager` and `00b3d2a0` a `cStarManager`?** | The receiver layouts support “noun-manager-compatible” and “cStarManager-compatible” descriptions. Exact class identity, manager owner, and whether the returned objects are the constructed managers remain unresolved. The alternate noun accessor is not proven canonical. | Safe bounded interpretation, not unique-type proof. |
| **8. What is proven about root publication?** | A manager construction/registration path exists, and the four words have no recovered direct writer. The static scans are bounded negatives. Publication, replacement, and unpublication remain unresolved; no parent/constructor candidate should be promoted to a root publisher. | Static local facts plus unresolved lifecycle. |
| **9. What is proven about noun materialization and ownership?** | Noun creation eagerly inserts into manager-local `mObjects` and `mNouns`; `00b21340` lazily materializes a manager-local vector cache through lower-bound lookup; cache records are borrowed while element references are separately managed. Normal noun destruction invalidates, unlinks `mNouns`, and later reclaims `mObjects`/pending state. Root publication is not involved. | Strong bounded static model; exact failure/ownership and root join open. |
| **10. What is proven about star materialization and ownership?** | `cStarManager` publishes/caches `cStarRecord` and live-planet state; `cStarRecord` holds planet-record data; `cStar`, `cSolarSystem`, `cPlanet`, and `cEmpire` provide separate typed links/references. There is no single generic noun owner, and the root pointer is not the record registry. | Strong layered model; logical cardinality and restore order open. |
| **11. What may the final synthesis safely state?** | State the closed accessor, receiver-layout, lower-bound, manager-local lifecycle, cache, and ownership boundaries; retain four opaque ports and all publication/equality/teardown unknowns. Do not merge roots, assume singleton behavior, call lower-bound exact, or claim root serialization. | Safe final-synthesis boundary. |
| **14. What runtime evidence is needed for the root question?** | A synchronized, read-only transition/teardown matrix capturing all four words, pointee addresses, vtables or generation markers, manager construction/registration, noun create/destroy, star record/planet materialization, empire erase/cache refresh, and teardown. One unequal snapshot can reject unconditional equality but cannot prove always-equal behavior or universal teardown order. | Runtime-needed. |
| **15. What static work remains before runtime?** | Trace concrete manager-allocation-to-slot dataflow, computed/bulk/table/loader/service-registration writes and clears, the owner/caller chain for `00b5ca50`, and any canonical noun consumers that could establish root provenance. Also close noun cache insertion ownership and exact erase membership where possible. | Static continuation; still not proof if opaque paths remain. |
| **16. What is the final classification?** | Blocker A remains unresolved and architecture-changing for original root compatibility. A bounded clean-room implementation may proceed only with separate opaque observation ports and explicit host-side lifecycle/generation policy. Original publication, equality, liveness, unpublication, and cross-root teardown remain blocked. | Final classification. |

## 6. Runtime questions that static evidence cannot answer

A runtime experiment, if authorized, should be read-only and synchronized. It should record at each event:

- all four root words and, for non-null values, the pointee address and a vtable/generation marker;
- the noun and star manager construction receivers and the parent/registration object addresses;
- noun `mNouns`, `mObjects`, pending-destroy vector, and `mNounMap` size/selected record state;
- requested noun ID, lower-bound node key, requested record key, `needsUpdate`, and returned record address;
- requested and cached political ID, map node key, returned `cEmpire+0x84`, and cache reference state;
- `cStarRecord` key, grid/vector membership, record reference count, and linked live `cStar`/planet state;
- manager teardown entry/exit, root clear/replacement events, and owner release order.

The minimum positive separator is a natural noun/star phase transition with sampling before and after the transition. The minimum positive lifetime experiment is a controlled transition that actually replaces or destroys a manager, without dereferencing a possibly stale pointer. Forced null allocation, synthetic rekey, or destructive erase should not be used merely to manufacture a result; the static lower-bound behavior is already strong enough to define the clean-room contract.

## 7. Bottom line

The corpus supports a clean separation between **root observation**, **manager-local publication**, **noun/star materialization**, **cache invalidation**, **registry erase**, **manager teardown**, and **root unpublication**. The reports sometimes collapse those levels, especially when using “owned,” “matching,” “canonical,” or “publication” without a direct join. The final synthesis should preserve the distinction.

The strongest defensible final statement is:

> `00b3d300` and `00b3d2a0` are raw accessors to alternate global words whose selected consumers use noun-manager- and star-manager-compatible layouts. Their canonical counterparts are distinct raw words. The noun and star manager-local materialization, invalidation, registry, and teardown bodies are substantially recovered, but no root publisher, replacement/equality path, root unpublication, or cross-root lifetime order is recovered. The four words must remain separate opaque compatibility ports; their values and owners are runtime-needed or unresolved.

## Primary review inputs

- Isolated reports: `knowledgegraph/research/noun-star-lifecycle/track-a-root-identity.md`, `track-b-noun-publication.md`, `track-c-star-publication.md`, `track-d-identity-ownership.md`, `track-e-cross-root-callers.md`, `track-f-lifecycle-ordering.md`, `track-g-edge-cases.md`.
- Root closure: `docs/analysis/simulator-root-closure.md`; `docs/analysis/simulator-shared-state-interface.md`; `knowledgegraph/research/root-closure/root-closure-f0e310e0.json`.
- Root follow-ups: `knowledgegraph/research/root-closure/followup-global-slots.md`; `followup-noun-boundary.md`; `cross-root-relationships.md`; `followup-space-lifecycle.md`; `followup-receiver-provenance.md`; `track-d-noun-registry.md`; `track-e-empire-chain.md`.
- Architecture resolution: `knowledgegraph/research/architecture-resolution/track-01-noun.md`; `track-02-star.md`; `followup-03-root-publication.md` and its JSON.
- Blocker adjudication: `knowledgegraph/research/architecture-blockers/blocker-a-primary.md`; `blocker-a-adversarial.md`; `docs/analysis/architecture-blockers.md`; `docs/analysis/architecture-decisions.md`.
- Supporting semantic boundaries: `docs/analysis/gameplay-data-model.md`; `docs/analysis/serialization-model.md`; `docs/analysis/gameplay-state-machines.md`; `docs/analysis/type-archaeology.md`.
