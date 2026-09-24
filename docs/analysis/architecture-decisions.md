# Architecture Decisions

This register contains only evidence-supported clean-room decisions. Original-binary observations are separated from modern recommendations. No raw vtable slot number, current source behavior, SDK name, or historical report repetition is treated as original runtime proof. All campaign work was static/read-only; no new runtime observation was performed.

## Freeze now

### DEC-01 — Preserve separate mode-state axes

**Evidence:** `0x007d85b0` performs App active-index transition ordering; `0x00b5b840`, `0x00b5b880`, `0x00b5b8a0`, `0x00b5b8c0`, `0x00b5b8e0`, and `0x00b5b960` support a first-request-wins pending strategy state with separate committed state; `0x01021960` owns `SpacePlayerData+0x10`; input, scenario, App, Simulator, and Cell owners are distinct.

**Decision:** Freeze App mode orchestration, Simulator pending/committed strategy state, input mode, SpaceContext, scenario mode, and Cell lifecycle as separate axes with explicit request and transition phases. Freeze semantic lifecycle/input/update operations, not original raw vtable slots.

**Addresses:** `0x007d85b0`, `0x007d8c80`, `0x00b3d350`, `0x00b5b840`, `0x00b5b960`, `0x00b63510`, `0x01021960`, `0x00e616c0`, `0x01485550`, `0x01485558`.

### DEC-02 — Freeze immediate versus deferred App event transport

**Evidence:** `0x00884100` is the outer ProcessQueue entry, `0x00884550` walks six-word records, `0x008841f0` is cleanup/storage walking, and `0x00884700` dispatches listener/handler/context branches. `0x00885710`, `0x00885890`, and `0x00885930` show deferred insertion; `0x008853e7/0x008854a0` show immediate registry traversal. Entry is 0x14 bytes; queue records are 0x18 bytes.

**Decision:** Freeze separate registration Entry and deferred queue-delivery records, separate immediate dispatch from deferred targeted delivery, and tagged listener versus handler/context targets. Freeze only the App transport; do not merge domain payload families or promise cross-family total order.

**Addresses:** `0x008839a0`, `0x008839e0`, `0x00883a30`, `0x00884100`, `0x008841f0`, `0x00884550`, `0x00884700`, `0x008853e7`, `0x008854a0`, `0x00885710`, `0x00885890`, `0x00885930`, `0x01427920`.

### DEC-03 — Reject a universal event payload ABI

**Evidence:** StandardMessage, UTFWin::Message, AnimationMessage, `cCommEvent`, and anonymous space records have incompatible semantic prefixes, owners, and release paths. The App queue record is generic transport state, not a domain payload base.

**Decision:** Keep StandardMessage-derived payloads, UTFWin messages, animation/editor events, deferred gameplay values, `cCommEvent`, Cell interaction records, and anonymous keyed space records as separate families with separate ownership and ordering contracts.

### DEC-04A — Freeze noun-root ports as the architecture-changing boundary

**Evidence:** `DAT_0167eae0`/`DAT_0167eb60` are distinct four-byte words with bounded direct/literal/computed negative scans. `0x00b3d300` and `0x00b3d400` are distinct raw loads, and no cross-accessor equality is recovered.

**Decision:** Scope the architecture-changing root decision to noun-root publication, equality, and teardown. Freeze separate opaque noun-root ports with explicit publication, replacement, invalidation, and unpublication lifecycle events. Do not merge the noun globals, assert a singleton, or claim that a failed direct scan proves no writer.

**Addresses:** `0x00b3d300`, `0x00b3d400`, `DAT_0167eae0`, `DAT_0167eb60`.

### DEC-04B — Freeze star-root ports as a safe-local unresolved boundary

**Evidence:** `DAT_0167eae4`/`DAT_0167eb0c` are distinct four-byte words with bounded direct/literal/computed negative scans. `0x00b3d2a0` and `0x00b3d3a0` are distinct raw loads, and no cross-accessor equality is recovered.

**Decision:** Keep separate opaque star-root ports with explicit publication, replacement, invalidation, and unpublication lifecycle events. Star root equality/publication remains `UNRESOLVED — not frozen`, but this is `UNRESOLVED_BUT_SAFE` and does not by itself change the current semantic architecture.

**Addresses:** `0x00b3d2a0`, `0x00b3d3a0`, `DAT_0167eae4`, `DAT_0167eb0c`.

### DEC-05 — Freeze noun and empire lookup/cache mechanics at their observed boundaries

**Evidence:** `0x00e5c780` is lower-bound; `0x00ba9370` checks only the end sentinel; `0x01021300` stores a lookup result without post-lookup identity validation; `0x00bad7a0` releases a lower-bound-selected map payload and `0x01022460` independently clears the player cache.

**Decision:** Freeze `ceilingByPoliticalId` semantics for `0x00ba9370`, successor-tolerant lazy player-cache behavior for `0x01021300`, and independent map/cache ownership and teardown. Callers requiring exactness must add an identity postcondition.

**Addresses:** `0x00e5c780`, `0x00ba9370`, `0x01021300`, `0x00bad7a0`, `0x01022460`.

### DEC-06 — Freeze `0x00b5b800` only as an opaque by-value read

**Evidence:** `0x00b5b800` calls `0x00b3d320`, tests the receiver, returns `0xffffffff` when the source word is zero, and otherwise calls `0x00a42730` to read `receiver+0x20`. The exact corrected caller partition is **829 scalar + 6 normalization + 1 return-only + 7 ambiguous = 843**; no strict returned-value pointer dereference was observed.

**Decision:** Freeze a borrowed opaque uint32 read contract with exact absent-source `0xffffffff`. Keep `C00/C01/C02/C04/C05/C06` distinct and `C03` unknown. Do not expose the result as a pointer, mode ID, strategy pointer, player ID, enum, or retained object.

**Addresses:** `0x00b5b800`, `0x00b3d320`, `0x00a42730`, `DAT_0167eaec`, `receiver+0x20`, `0x01654c00`, `0x01654c01`, `0x01654c02`, `0x01654c03`, `0x01654c04`, `0x01654c05`, `0x01654c06`.

### DEC-07 — Keep avatar access receiver-typed

**Evidence:** `0x00b1fdb0` is a raw `+0x54` read. `0x00b1fd50` performs AddRef-new/store-new/Release-old and supports equal-address no-op and null clear. The `0x00bff2d0:0x00bff3ad-0x00bff3b4` receiver is `DAT_016dc0fc`, whose `+0x54` is high-LOD planet simulation, not an avatar.

**Decision:** Freeze receiver-typed ports. For a live noun-layout receiver, model `+0x54` as an intrusive current gameplay creature selection and expose borrowed reads. Do not type `0x00b1fdb0` globally as GetAvatar.

**Addresses:** `0x00b1fdb0`, `0x00b1fd50`, `0x00b3d300`, `0x00b3d400`, `0x00bff2d0`, `0x01002bd0`, `0x010066e0`, `0x01006880`.

### DEC-08 — Keep Cell simulation, presentation, content, and save state separate

**Evidence:** `0x00e66010` clears `cCellObjectData+0x248` and releases the GFX record without releasing the Cell pool entry; `0x00e6d8f0` writes a new GFX index to the same Cell; `0x00e780a0` and `0x00e7fd00` release old Cell identities; `0x00e74a20` and `0x00e666f0` separate model/content/resource data from presentation; `0x00e63d10` is an in-memory serializable handoff.

**Decision:** Freeze a modern stable simulation CellId/pool identity separate from optional GFX/UI presentation, model/content/resource references, and `cCellSerializableData` save state. Freeze create, mutation, presentation detach/rebuild, death, despawn, reload, OnExit, and Dispose as separate lifecycle operations.

**Addresses:** `0x00e74a20`, `0x00e66010`, `0x00e6d8f0`, `0x00e78c00`, `0x00e780a0`, `0x00e7fd00`, `0x00e7fc00`, `0x00e81f30`, `0x00e80ba0`, `0x00e806b0`, `0x00e7f3a0`, `0x00e6d200`.

### DEC-09 — Freeze layered resource identity

**Evidence:** `0x00e82420` searches by `instanceID` plus serializer pointer; manager/provider APIs use full numeric `ResourceKey`; `DatabasePackedFile` owns a ResourceKey map; `0x008de280`, `0x008de360`, and `0x008de3b0` use key-bearing cache operations; record leases and runtime objects are separate.

**Decision:** Use field-aware full `ResourceKey` for manager/provider identity. Keep Cell local `cCellDataReference_` pair identity, database/factory, cache, record lease, and runtime-object identity separate. Freeze the explicit priority/override and first-hit/first-success boundaries, while keeping runtime precedence and eviction provisional.

**Addresses:** `0x01436ae8`, `0x008e0d30`, `0x008de940`, `0x008de310`, `0x008df9b0`, `0x008dfb20`, `0x008de280`, `0x008de360`, `0x008de3b0`, `0x008de400`, `0x008da3d0`, `0x00e82340`, `0x00e82420`, `0x00e823a0`, `0x00e82280`, `0x00e823e0`, `0x00e824d0`, `0x016b44f0`.

### DEC-10 — Freeze the persistence spine without claiming outer-wire compatibility

**Evidence:** direct `+0x10/+0x12` accesses and 0x18 map stride support the 0x14 Property carrier; `0x006a1540/0x006a2f60` support local count/ID/value framing and a parent-reference branch; `0x00692900/0x00693e10` are concrete ClassSerializer Write/Read; `0x00b26800/0x00b26840` and `0x00b274e0` support a ClassSerializer-backed header; `0x00e61550`, `0x00e51300`, and `0x00e51370` support a 0xec Cell save candidate; `0x00b28ec0` and `0x006891f0` support bounded temp/close/replace.

**Decision:** Freeze typed Property/PropertyList framing, class/attribute callback serialization, stable object references with deferred association, a versioned ClassSerializer-backed header, the Cell save candidate as separate from live mode/presentation state, and explicit temp/close/replace boundaries. Treat `0x00b28ec0` and `0x00b279e0` as strong save/load candidates but not confirmed `cGamePersistenceManager` members. Do not claim complete outer `.spo/.prop`, migration, field-survival, object-table, or cross-file atomicity.

**Addresses:** `0x00422eb0`, `0x00692880`, `0x00692900`, `0x00693e10`, `0x006a1540`, `0x006a2f60`, `0x00693390`, `0x00694440`, `0x00b26800`, `0x00b26840`, `0x00b274e0`, `0x00b279e0`, `0x00b28ec0`, `0x006891f0`, `0x00e51300`, `0x00e51370`, `0x00e61550`, `0x00e63d10`, `0x00e80ba0`.

### DEC-11 — Keep conditional vtable and space records out of the semantic ABI

**Evidence:** `0x00e616c0` installs separate Cell primary/secondary vptrs and `0x00e5c590` adjusts the secondary receiver. `0x00e39ab0` creates independent key `0x0c`/27-slot and key `0x06`/24-slot entries; the latter has no direct consumer in the focused static census.

**Decision:** Keep raw vtable dimensions and anonymous keyed records as separate compatibility surfaces, not semantic interfaces. Do not mirror original MSVC slots, merge the space pair with App/UI/animation/communication/resource records, or infer a common ABI from size/count.

**Addresses:** `0x00e616c0`, `0x00e5c590`, `0x01485550`, `0x01485558`, `0x013f57f8`, `0x01490be8`, `0x00e39ab0`, `DAT_015fd910`.

## Provisional/unresolved — UNRESOLVED and not frozen

These are not decisions. They are the exact unresolved questions that remain outside the freeze set.

- **UNRESOLVED — not frozen:** Whether noun/star root values are equal, phase-rebound, or separately published.
- **UNRESOLVED — not frozen:** Exact `cStarManager+0x204` versus `DAT_0167eb14` alias and exact `0x00b25fb0` fallback type.
- **UNRESOLVED — not frozen:** `0x00b28ec0` and `0x00b279e0` are strong save/load candidates but are not confirmed `cGamePersistenceManager` members.
- **UNRESOLVED — not frozen:** `DAT_0167eaec` first writer, physical `receiver+0x20` identity, publication/freshness, replacement, teardown, and downstream ownership.
- **UNRESOLVED — not frozen:** Persistence outer envelope, object/reference table, descriptor/field graph, field survival, migration, cross-file commit, and mode-handoff ownership.
- **UNRESOLVED — not frozen:** Message queue-key units, listener execution timing, thread affinity, reentrancy, and the unresolved concrete vtable word `0x008853b0`.
- **UNRESOLVED — not frozen:** Key-`0x06` consumer identity and telemetry read-back.
- **UNRESOLVED — not frozen:** Complete raw vtable extents and several interior function boundaries.

## Conditionally freeze if requirement X

### COND-01 — Original vtable/object ABI compatibility

**Requirement X:** OpenSpore must adopt original objects, expose original vtable slots, load plugins against the original ABI, or reproduce raw dispatch.

**Conditional decision:** Freeze a separate compatibility ABI adapter for multiple subobjects, exact vptr/slot mapping, pointer adjustment, and function-boundary repair. Do not change the semantic mode/event interfaces.

**Evidence:** `0x00e616c0`, `0x00e5c590`, `0x01485550`, `0x01485558`, `0x013f57f8`, `0x01490be8`.

### COND-02 — Key-`0x06` or telemetry compatibility

**Requirement X:** A direct key-`0x06` consumer, alias relationship, required telemetry read-back, or externally required telemetry format is established.

**Conditional decision:** Freeze a proven sidecar/event dispatch or explicit telemetry schema, ownership, reconstruction, and byte-framing contract. Until then, two opaque independent keyed entries remain safe.

**Evidence:** `0x00e39ab0`, `0x007ec160`, `0x007eb820`, `0x007ebce0`, `0x007ebba0`, `0x00e3a270`, `0x00e3d9e0`.

### COND-03 — Noun/star root compatibility

**Requirement X:** Root identity/liveness must be reproduced across modes, plugins, save restoration, or mode teardown.

**Conditional decision:** Freeze a root publication/equality model with explicit phase/rebind and teardown state. If the outcome is phase-specific, the model must carry phase-specific manager identities, cache invalidation, and relationship-state ordering rather than a shared registry.

**Evidence:** `0x00b3d300`, `0x00b3d400`, `0x00b3d2a0`, `0x00b3d3a0`, `DAT_0167eae0`, `DAT_0167eb60`, `DAT_0167eae4`, `DAT_0167eb0c`.

### COND-04 — Typed `0x00b5b800` state ownership

**Requirement X:** `0x00b5b800` must be treated as a mode/strategy/owner object, or its value must survive a save or mode handoff.

**Conditional decision:** Freeze typed state ownership, publication/freshness, routing, and teardown contracts. If the field is pointer-backed, add object identity/refcount semantics; if it is a scalar, add a tagged-state and freshness contract.

**Evidence:** `0x00b5b800`, `0x00b3d320`, `0x00a42730`, `DAT_0167eaec`, `receiver+0x20`, `0x00ad12a0`, `0x00d2e4a0`, `0x00d2e580`, `0x00d2e8a0`.

### COND-05 — Byte-compatible persistence or automatic mode save

**Requirement X:** Byte-compatible original save/load, exact field survival/migration, cross-artifact atomicity, or automatic persistence on mode exit is required.

**Conditional decision:** Freeze the exact outer envelope, descriptor/field schema, object-reference table, migration graph, mode handoff, and multi-file recovery contract once separated by direct evidence.

**Evidence:** `0x00692900`, `0x00693e10`, `0x006a2f60`, `0x00695140`, `0x00b28ec0`, `0x00b279e0`, `0x00e63d10`, `0x00e80ba0`, `0x00ef10c0`.

## Safely deferred unknowns

The following are not decisions and are safely deferred while the frozen boundaries above remain in force:

- Event queue-key units, signed-zero behavior, frame placement, thread affinity, and recursive callback timing.
- Unknown Cell/editor/Terrain vtable extents, interior function boundaries, and SDK slot labels when no raw ABI compatibility is required.
- `C03` and the seven bounded-ambiguous `0x00b5b800` callsites under the opaque uint32 contract.
- Complete creature presentation detach timing, complete owner multiplicity, and all null classification paths.
- GFX/UI/backend retirement timing, pool exhaustion sentinels, replacement policies, and full pose/render phase order.
- Runtime package precedence, cache eviction, async completion, and exact ResourceKey rekey behavior.
- Outer `.spo/.prop` bytes, parent-reference field order, unknown Property payloads, complete descriptor tables, migration defaults, field survival, and crash recovery when byte-compatible persistence is not required.
- Key-`0x06` field meanings, owner class, external object-reference lifetime, runtime ordering, and telemetry read-back unless a compatibility requirement is added.
- Exact `cStarManager+0x204` versus `DAT_0167eb14` alias and exact `0x00b25fb0` fallback type.
- `cGamePersistenceManager` membership for `0x00b28ec0` and `0x00b279e0`; they are strong save/load candidates, not confirmed manager members.
- Exact root equality, publication, liveness, and teardown observations for all four noun/star words unless root ownership is required for correctness.

This register contains no implementation plan and no code. All campaign work was static/read-only, and no new runtime observation was performed.
