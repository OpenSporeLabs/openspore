# Architecture blockers: final resolution report

**Campaign:** Architecture blocker resolution
**Date:** 2026-09-24
**Binary:** `SporeApp.exe` 3.1.0.22, `x86:LE:32:windows`, image base `0x00400000`

This report resolves the practical status of the three remaining architecture-changing blocker clusters from the Semantic Blueprint and Architecture Resolution. It is a static research synthesis. No OpenSpore implementation was performed, `SPORE/` was not modified, and the canonical SQLite knowledgegraph was not mutated.

## Evidence set

Each blocker has an isolated primary report and an isolated adversarial review:

- [Blocker A primary](knowledgegraph/research/architecture-blockers/blocker-a-primary.md) / [adversarial review](knowledgegraph/research/architecture-blockers/blocker-a-adversarial.md)
- [Blocker B primary](knowledgegraph/research/architecture-blockers/blocker-b-primary.md) / [adversarial review](knowledgegraph/research/architecture-blockers/blocker-b-adversarial.md)
- [Blocker C primary](knowledgegraph/research/architecture-blockers/blocker-c-primary.md) / [adversarial review](knowledgegraph/research/architecture-blockers/blocker-c-adversarial.md)

The reports use Ghidra, callers/callees, types/vtables, state/events, data/serialization, runtime plans, and local SDK/community evidence as separate evidence classes. Negative scans are reported as bounded negatives, not as proof of absence.

## Executive decision

| Blocker | Status | Clean-room implementation | Original compatibility |
|---|---|---|---|
| A — noun/star publication lifecycle | **Unresolved; architecture-changing** | **Proceed only with opaque observation ports** | Blocked |
| B — `DAT_0167eaec` / `0x00b5b800` | **Partially resolved; architecture-changing** | **Proceed only with a non-authoritative mode-word adapter** | Blocked |
| C — persistence/reference/mode handoff | **Partially resolved** | **Proceed with an OpenSpore-defined persistence seam** | Blocked |

No architecture rewrite is justified. The unresolved questions constrain the compatibility boundary; they do not require collapsing the existing semantic ports or introducing a new universal mode/owner/identity model.

---

## Blocker A — noun/star publication lifecycle

### Status

**Unresolved; architecture-changing for original root compatibility.**

The binary establishes four distinct physical root slots, but not their publishers, value equality, liveness, rebind order, or root teardown:

- `DAT_0167eae0` read by `0x00b3d300`;
- `DAT_0167eb60` read by `0x00b3d400`;
- `DAT_0167eae4` read by `0x00b3d2a0`;
- `DAT_0167eb0c` read by `0x00b3d3a0`.

The direct bodies are simple word reads. Bounded scans found no direct root store, clear, equality operation, or teardown store. This rejects physical aliasing, but does not prove four owners, four lifetimes, or four publications.

### Strongest evidence

1. **Noun storage and materialization.** `0x00b20c60` uses the noun factory, inserts created objects into manager lists, and calls the invalidation bridge. `0x00b21340` uses the manager noun-ID map and materializes a dirty vector through the lower-bound helper `0x00e5c780`. The callback contract is four callbacks plus noun ID, not five callbacks.
2. **Noun invalidation and destruction.** `0x00b201a0` marks a lower-bound-selected vector dirty and applies type/cast filtering. `0x00b225d0`, `0x00b20d30`, `0x00b22650`, `0x00b227c0`, and `0x00b22440` provide staged destruction and manager cleanup surfaces. These are manager/object lifecycle bodies, not proof of root unpublication.
3. **Star lookup and cache.** `0x00ba9370` performs lower-bound lookup in `cStarManager+0x150`. `0x01021300` lazily caches the current-player empire, AddRefs a new value, and Releases the old value. `0x00bad7a0` erases a lower-bound-selected map payload, while `0x01022460` independently clears the player cache.
4. **Star records.** `cStar` is a live `cGameData` noun with a `cStarRecordPtr` at `+0x48`; `cStarRecord` is a separate serializable/refcounted record. Physical aliasing is rejected. Logical identity and association cardinality are not fully established.
5. **Persistence boundary.** `stars.db.tmp` to `stars.db` replacement is direct at `0x00bb4ba0`, but it is not evidence that noun/star root pointers are saved or restored.

### Competing hypotheses and adversarial result

| Hypothesis | Prediction | Result |
|---|---|---|
| Always-equal pairs | Paired publishers/clears; no unequal window | Unresolved; no paired writer/equality path found |
| Phase-specific or independently rebound roots | Unequal/null/rebind windows; consumer follows selected root | Unresolved and architecture-relevant |
| One accessor is stale/compatibility-only | Active consumer sees old manager after rebind | Unresolved; sparse canonical use is not proof of death |
| Computed/bulk/external publication | Indirect writer or runtime-only write | Possible, but not selected as the leading explanation |

The adversarial review corrected several overclaims: “four slots” does not mean four owners; “matching” invalidation/erase means lower-bound-selected unless exact membership is proven; and `cStar`/`cStarRecord` have distinct physical representations, not necessarily distinct logical identities.

### Remaining ambiguity

- Root publishers, replace/clear operations, and unpublication order.
- Value equality and phase identity for both pairs.
- Root ownership and lifetime authority.
- Exact-key membership before noun invalidation/erase or empire-map erase.
- Complete star record-to-live-planet materialization ownership.

### Architecture impact

A single-owner result could collapse the service graph. Phase-specific roots would require phase-aware identities, rebind ordering, and separate teardown/cache graphs. Until then, the noun and star service graphs must remain separate. The semantic noun/star distinction also survives: live noun objects, persistent star records, live planets, and empire records require typed links rather than physical aliasing.

### Affected packages

`PKG-01-SHARED-STATE-ROOTS`, `PKG-02-APP-LIFECYCLE`, `PKG-06-CELL-STATE`, `PKG-08-CELL-MODE`, `PKG-11-SIM-CORE`, `PKG-12-SIM-SPACE`.

### Exact next action

1. Statically trace constructor/registration results, aliases, bulk-copy helpers, tables, loader paths, and computed writes/clears for all four root words.
2. If static analysis remains inconclusive, capture one naturally reachable transition with synchronized reads of all four words, pointee addresses, vtable pointers, generation markers, map/list sizes, noun create/destroy, empire cache refresh, and manager teardown.
3. Require a complete publisher/equality/teardown matrix. A single unequal snapshot can reject unconditional equality but cannot prove a positive always-equal model.

### Implementation decision

**Safe only as a compatibility-excluded clean-room seam.** Use four opaque observation ports with no implicit equality, fallback, owner claim, raw-pointer persistence, or original lifecycle emulation. Preserve lower-bound/successor-tolerant behavior and add explicit exactness postconditions where the replacement needs exact keys. Do not expose the ports as four recovered owners or as the original publication ABI.

---

## Blocker B — forwarded state at `0x00b5b800` / `DAT_0167eaec`

### Status

**Partially resolved; architecture-changing for publication/identity compatibility.**

The forwarding mechanics are exact:

```text
0x00b5b800
  -> 0x00b3d320: read DAT_0167eaec
  -> zero receiver: return 0xffffffff
  -> non-zero receiver: read [receiver+0x20] through 0x00a42730
```

The returned value is a borrowed 32-bit mode-domain scalar discriminator in observed consumers. It is not safely classified as a pointer, handle, tagged value, or forwarded interface.

### Strongest evidence

1. `0x00b289ac` writes `GameModeIDs::kLoadGameMode` to `[FUN_00b3d320()+0x20]`; `0x00b5f056` writes a normalized transition mode to the same current-result field. These are pointee-field writers, not global-slot writers.
2. `0x00b1d870` constructs a `0x9c` object family with a `cGameModeManager`-compatible vtable and layout, including `+0x20 = -1`, and `0x00b60d80` allocates it. `0x00b1d970`/`0x00b1dc40` provide a matching teardown family.
3. There is no direct evidence that the `0x00b1d870` allocation is ever published in `DAT_0167eaec`. The target-slot writer, backing publication, and allocation-to-slot join remain open.
4. `DAT_0167eaec` has one direct read xref and no recovered direct writer. The canonical accessor `0x00b3d420` reads the distinct `DAT_0167eb2c` slot; no equality or common writer is proven.
5. The mode normalizer at `0x00b5c9d0` collapses invalid values to `0xffffffff`, and the SDK event contracts use mode IDs. This corroborates scalar mode semantics but not freshness or authority.

### Competing hypotheses and adversarial result

| Hypothesis | Prediction | Result |
|---|---|---|
| Strategy/mode owner | Scalar mode values and transition writers | Supported as a compatible semantic model, not as a publication/ownership proof |
| Current-object state | `+0x20` changes at mode events | Supported for field meaning; freshness unresolved |
| Handle/pointer | Returned value is dereferenced or retained | Rejected for the returned value |
| Tagged value | Tag decoder required | Not needed under the observed mode constants |
| Forwarded interface | `+0x20` is dispatched as an interface | Rejected for `+0x20`; receiver has a vtable, but field writes are scalar |
| `0x00b28990` is first target writer | Earliest static mode store is runtime first transition | Unresolved; address order is not runtime order and target publication is unjoined |

The adversarial review found the key missing join: a `cGameModeManager`-compatible constructor family exists, but no evidence proves its allocation is the current pointee returned by `DAT_0167eaec`. The older “no `+0x20` writer” result is too broad, but its global-slot negative remains valid.

### Remaining ambiguity

- Receiver exact identity and backing storage.
- First writer and first mode transition.
- Global publication, replacement, freshness, and teardown.
- Aliasing/equality with `DAT_0167eb2c`.
- Ownership, thread-safe lifetime, and whether the scalar is authoritative or a stale mirror.
- `0xffffffff` has at least two possible origins: zero receiver and a `-1` field state.

### Architecture impact

The mode-routing state machine can safely consume a scalar mode discriminator. A future pointer/tagged/strategy resolution would add a typed adapter and explicit publication/lifecycle model; it must not be smuggled into the current scalar seam. The alternate and canonical manager slots remain separate even if a future runtime trace observes equal values.

### Affected packages

`PKG-01-SHARED-STATE-ROOTS`, `PKG-02-APP-LIFECYCLE`, `PKG-08-CELL-MODE`, `PKG-11-SIM-CORE`.

### Exact next action

1. Statically trace aliases, bulk-copy paths, service registration, and computed writers for `DAT_0167eaec`; compare them with the `0x00b1d870` allocation.
2. If static evidence remains inconclusive, record one allocation-to-slot-to-field identity chain: allocation base/vtable, first non-zero alternate result, canonical result, `P == allocation`, `P == canonical`, vtable of `P`, first `[P+0x20]` write, and first replacement/clear/teardown.
3. Keep the result `uint32` and the two possible `0xffffffff` origins explicit until the identity chain is closed.

### Implementation decision

**Safe only as a compatibility-excluded clean-room adapter.** Expose a non-owning, non-authoritative forwarded mode-word value. Do not expose a `cGameModeManager*`, merge slots, claim first writer, promise lifetime safety, or persist the value as authoritative mode state.

---

## Blocker C — persistence reference/restore and mode handoff

### Status

**Partially resolved; clean-room implementation may proceed; original wire/runtime parity remains blocked.**

The useful resolved surfaces are:

- `PropertyList` local-entry Read/Write and typed-value dispatch, with an unresolved parent-related negative-count branch;
- `ClassSerializer` ordered attribute descriptors and callback-based Write/Read with identity/count/status checks;
- `ISimulatorSerializable` as a serialization capability, not complete field coverage;
- `cSavedGameHeader` and `cCellSerializableData` serializer-vtable/copy-adopt candidates;
- static save/load candidate operation sequences and bounded temp/old/replacement helpers;
- separate App mode lifecycle, Simulator strategy state, and Cell runtime/presentation state.

### Strongest evidence

1. `0x006a1540` and `0x006a2f60` show local property ID/value stream dispatch. The reader has a negative-count branch that resolves a parent/list relationship. Exact Property carrier, parent encoding, and round-trip bytes remain unresolved.
2. `0x00692880`, `0x00692900`, `0x00693e10`, and `0x00e0e9f0` show descriptor setup, callback write/read, identity/count checks, attribute resolution, and status paths.
3. `0x00695140`, `0x00695b40`, and `0x00695770` show runtime association/create-or-reuse behavior. They do not prove a durable object table, stable instance IDs, or cycle encoding.
4. `0x00b268a0` and the Cell vtable methods around `0x00e51300/0x00e51370` use serializer callbacks. `0x00e63d10` and `0x00e627a0` provide a bounded in-memory Cell DTO copy/adopt seam. Direct save/load participation of the Cell object is not fully joined.
5. `0x00b28ec0` and `0x00b279e0` are strong save/load operation candidates with database/stream, header, service, close, and replacement surfaces. `0x006891f0` and `0x00bb4ba0` are separate replacement paths. No universal transaction, crash atomicity, manifest, or persistence-manager membership is proven.
6. `0x007d85b0` establishes old OnExit -> active-state write -> exit announcement -> new OnEnter -> enter announcement in helper-local order. `0x00b5b960`/`0x00b63510` establish a separate Simulator strategy channel. Direct `0x00e7fc00`/`0x00e81f30` Cell bodies do not call the observed save/load candidates, but indirect higher-level autosave remains unexcluded.

### Competing hypotheses and adversarial result

| Hypothesis | Prediction | Result |
|---|---|---|
| Callback/class-attribute object graph | Class/attribute checks and association before field dispatch | Supported as architecture; wire object table and cycles open |
| Raw fixed header/Cell struct copy | Save/load would copy complete objects without callbacks | Rejected as the general model |
| PropertyList is the outer `.spo` format | Save begins with a PropertyList stream | Not established |
| Persistence manager owns save/load candidates | Manager `this`/vtable reaches both candidates | Unconfirmed |
| Cell OnExit/Dispose autosaves or transfers live graph | Teardown reaches file/serializer and preserves live graph | No static direct evidence; higher-level behavior open |
| Temp/old/replace is crash-atomic across artifacts | Manifest/journal rolls back `.spo` and `stars.db` | Bounded replacement only |
| Host addresses/pool indices are durable identity | Save/load serializes raw addresses | Rejected as a clean-room design; original exact behavior open |

The adversarial review identified the most important unresolved issue: header and Cell wrappers are both reported with `0x01a80d26`. Until the descriptor/key domain is resolved, this cannot be treated as a universal class ID or a universal object-reference namespace. The coherent OpenSpore object graph is a candidate design, not the smallest recovered original model.

### Remaining ambiguity

- Outer `.spo`/`.prop`/database/COM framing and first-record order.
- `0x01a80d26` meaning and descriptor key scope.
- Durable instance/reference encoding, forward references, cycles, duplicates, missing IDs, and restore order.
- Property parent encoding and exact value carrier.
- Whether `cCellSerializableData` is directly reached by save/load candidates.
- `cGamePersistenceManager` binding for `0x00b28ec0`/`0x00b279e0`.
- Automatic mode save, cross-file atomicity, migration, field survival, and recovery.

### Architecture impact

Persistence remains a separate owner from live runtime registries and mode services. OpenSpore may define its own explicit, deterministic document and transaction policy, but must not present it as the recovered original format. Host pointers, Cell pool indices, GFX/UI handles, live Cell objects, and runtime service pointers cannot be made durable identity by convenience.

### Affected packages

`PKG-02-APP-LIFECYCLE`, `PKG-03-RESOURCE-IO`, `PKG-06-CELL-STATE`, `PKG-08-CELL-MODE`, `PKG-11-SIM-CORE`, `PKG-12-SIM-SPACE`, `PKG-15-EDITOR-SUPPORT`.

### Exact next action

1. Resolve the runtime-populated header and Cell descriptor tables and the read resolver key domain, including the shared `0x01a80d26` value.
2. Trace `0x00b28ec0`/`0x00b279e0` through Cell-specific helpers to `0x00e51300`/`0x00e51370` or prove the edge is absent.
3. Trace the PropertyList constructor/getter/map-node layout and the negative-count parent branch.
4. Recover close/status branches before `0x006891f0` and the service vtable/`this` binding for the candidates.
5. If compatibility is required, run one explicit save/load round trip with a forward reference and, if naturally reachable, a cycle; then one Cell teardown without manual save and one controlled failure/recovery case.

### Implementation decision

**Safe only as a compatibility-excluded clean-room architecture.** Use an OpenSpore-defined versioned document with explicit schema descriptors, typed property values, domain-separated logical handles, deterministic deferred binding, explicit DTO handoff, and independently specified artifact transaction/recovery policies. Do not claim original `.spo`/`.prop` bytes, field survival, automatic mode save, manager binding, restore order, or cross-file atomicity.

---

## Cross-blocker architecture rules

1. **No forced type.** Opaque state remains opaque until allocation-to-slot-to-field identity and ownership are observed.
2. **No singleton inference.** Distinct storage words reject physical aliasing, not value equality.
3. **No lookup promotion.** Lower-bound/ceiling behavior must be preserved; exact lookup requires an explicit postcondition.
4. **No raw-pointer persistence.** Runtime addresses, pool indices, GFX/UI handles, and service pointers are not durable identity.
5. **No mode-exit autosave inference.** Direct teardown cleanup is not a save transaction; higher-level autosave remains open.
6. **No manager ownership inference.** Accessor fan-in, SDK singleton wording, and manager-compatible layouts do not establish publishers or lifetime authority.
7. **No universal class/reference namespace.** Until descriptor/key scope is resolved, keep serializer keys, document instance handles, domain IDs, ResourceKeys, and Cell identities separate.
8. **No transaction claim from replacement helpers.** Temp/old/replace is an OpenSpore policy boundary unless runtime behavior proves more.

## Implementation gate

Implementation may proceed only as a clean-room, compatibility-excluded architecture:

- A: four opaque root observation ports with explicit host-side rebind/generation policy.
- B: non-authoritative forwarded mode-word adapter with distinct `0xffffffff` origins.
- C: OpenSpore-defined schema/codec, domain-separated logical handles, deferred binding, DTO handoff, and explicit artifact transaction policy.

The blocker gate reopens if exact original root/plugin identity, original save bytes, field survival, automatic mode persistence, original restore ordering, cross-file atomicity, or original multi-file behavior becomes a requirement.
