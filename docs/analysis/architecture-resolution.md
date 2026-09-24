# Final Architecture-Changing Contradiction Resolution

**Campaign:** Architecture-Changing Contradiction Resolution
**Date:** 2026-09-24
**Subject binary:** `SporeApp.exe` 3.1.0.22, `x86:LE:32:windows`, image base `0x00400000`

This is the final synthesis of all eleven `track-*.json` reports, all six `followup-*.json` reports, `knowledgegraph/research/conflict-adjudication.json`, and `docs/analysis/conflict-adjudication.md`. All work was static/read-only. No Ghidra mutation, runtime execution, `SPORE/` access, `spore.db` access, source implementation, or historical-artifact edit was performed. No new runtime observation was made.

## 1. Nine contradictions

The historical corpus selected 263 records: 62 resolved and 201 unresolved. Nine contradictions were assessed as architecture-changing. Two more are conditional. Historical counts are retained as counts, not as additive populations.

| Rank | Exact conflict ID | Post-campaign classification | Resolution status |
|---:|---|---|---|
| 1 | `CONFLICT-ROOT-NOUN-MANAGER-SLOTS` | `ARCHITECTURE_CHANGING` | Partially resolved; publication, equality, and teardown open |
| 2 | `CONFLICT-STAR-MANAGER-EMPIRE-CACHE` | `UNRESOLVED_BUT_SAFE` | Lookup/cache mechanics resolved; root equality/publication open |
| 3 | `CONFLICT-MODE-STATE-AXES` | `ARCHITECTURE_LOCAL` | Semantic axes resolved; timing/ABI details deferred |
| 4 | `CONFLICT-PROPERTY-PERSISTENCE-CODEC` | `ARCHITECTURE_CHANGING` | Local codecs resolved; save graph/outer framing open |
| 5 | `CONFLICT-MESSAGE-QUEUE-AND-EVENT-ABI` | `ARCHITECTURE_LOCAL` | Transport boundary resolved |
| 6 | `CONFLICT-OPAQUE-FORWARDED-STATE` | `ARCHITECTURE_CHANGING` | Opaque mechanics resolved; first writer/identity open |
| 7 | `CONFLICT-AVATAR-OWNER-LIFETIME` | `ARCHITECTURE_LOCAL` | Receiver-typed contract resolved; root/save coupling open |
| 8 | `CONFLICT-CELL-RUNTIME-PRESENTATION-LIFECYCLE` | `ARCHITECTURE_LOCAL` | Ownership split resolved; runtime order deferred |
| 9 | `CONFLICT-RESOURCE-IDENTITY-CACHE` | `ARCHITECTURE_LOCAL` | Identity layering resolved; runtime precedence deferred |

The two conditional contradictions are `CONFLICT-VTABLE-AND-SDK-IDENTITY-CORPUS` and `CONFLICT-ANONYMOUS-SPACE-RECORDS`; both are `UNRESOLVED_BUT_SAFE`.

## 2. Competing hypotheses and evidence

### 1) `CONFLICT-ROOT-NOUN-MANAGER-SLOTS`

**Addresses and symbols:** `0x00b3d300`, `0x00b3d400`, `0x00b21340`, `0x00bff2d0`, `0x01002bd0`, `DAT_0167eae0`, `DAT_0167eb60`.

**Competing hypotheses.**

- `DAT_0167eae0` and `DAT_0167eb60` always contain the same manager pointer.
- They are phase-specific, stale, or independently published.
- `0x00b3d300` is a noun-manager-compatible alternate accessor and `0x00b3d400` is a separate canonical accessor.
- `0x00b3d300` is only a generic context/service locator.
- The exceptional `0x00bff2d0` receiver is one of the noun roots.
- The noun lookup is exact find.
- The words are physically aliased.
- An opaque common publisher writes equal values into distinct words.
- Inspected noun lifecycle paths directly publish or unpublish both roots.

**Evidence for and against.**

- `0x00b3d300` is exactly `mov eax,[DAT_0167eae0]; ret`; `0x00b3d400` is exactly `mov eax,[DAT_0167eb60]; ret`.
- `0x00bff408` passes the alternate result into `0x00b21340`, which reads `receiver+0x78` and `receiver+0x98` as noun-manager fields. This rejects the generic-context claim.
- `0x01002bd0` returns `DAT_016dc0fc`; `0x00bff3b2` moves that value to `ECX`; `0x00bff3b4` calls `0x00b1fdb0`. This rejects the special receiver as either noun root.
- `0x00e5c780` and `0x00b21340` show lower-bound, end-sentinel behavior. Exact find is rejected; a greater successor can be reused.
- The two words are distinct four-byte storage locations. Physical aliasing is rejected, but value equality remains unresolved.
- Direct and bounded scans found no concrete writer/equality path. This is a bounded negative, not proof that no opaque, external, bulk, loader, runtime, or unresolved publication exists.
- SDK singleton language, repeated historical reports, co-calls, and fan-in are not original runtime proof.

**Independent evidence:** fresh accessor disassembly/decompilation, the receiver ECX chain, the lower-bound helper/caller pair, structure field use, and the separate `DAT_016dc0fc` publication lifecycle are separate evidence surfaces. The SDK singleton statement is conceptual corroboration only.

**Repeated/assumption-echo evidence:** historical same-instance language, singleton wording, and repeated co-call counts do not establish pointer equality. The prior “five callbacks” wording is rejected: the binary/header show four callback pointers plus the noun ID.

**Smallest separating observation and whether performed:** performed. The direct root/reference scan, `0x00bff2d0:0x00bff3ad-0x00bff3b4`, and `0x00e5c780/0x00b21340` pair separated physical storage, special receiver provenance, and lower-bound semantics. Runtime equality/publication was not observed.

**Post-campaign classification and status:** `ARCHITECTURE_CHANGING`; partial static resolution, publication/equality/teardown open.

**Minimum OpenSpore semantics:** separate opaque noun-root ports; receiver-owned noun records/maps; lower-bound GetData with four callbacks and end-sentinel behavior; explicit publication, replacement, invalidation, and teardown hooks; separate `DAT_016dc0fc` receiver path.

**Dependent decisions and safety:** equal values would permit one canonical service owner; phase-specific values require phase-aware identities and teardown; opaque publication requires lifecycle hooks. Exact equality, indirect publication, complete teardown, and exact parent class are safely deferrable; merging the roots or assuming a singleton is not.

### 2) `CONFLICT-STAR-MANAGER-EMPIRE-CACHE`

**Addresses and symbols:** `0x00b3d2a0`, `0x00b3d3a0`, `0x00ba9370`, `0x00e5c780`, `0x01021300`, `0x00b25fb0`, `DAT_0167eae4`, `DAT_0167eb0c`.

**Competing hypotheses:** always-equal star roots; phase rebinding; distinct phase-specific managers; common indirect/bulk publisher; obsolete canonical slot; exact empire find; ceiling/lower-bound lookup; exact-identity cache; lazy successor-tolerant cache; one combined empire/cache invalidation chain; canonical relationship-global alias; null-or-concrete-civilization no-empire result.

**Evidence for and against.**

- `0x00e5c780` is unsigned lower-bound; `0x00ba9370` checks only the end sentinel. A missing key below a greater successor can return the successor. Exact find is rejected.
- On a `0x01021300` miss, the successor is AddRefed/stored/returned without a post-lookup ID check. A later hit validates cached `cEmpire+0x84` against the request. The cache is lazy and successor-tolerant.
- `0x00bad7a0` releases the map payload/node but does not clear `SpacePlayerData+0x1c`; `0x01022460` clears/releases the player cache independently. A single invalidation chain is rejected.
- `0x00b25fb0` returns the caller fallback word unchanged when the current-player result is null; the fallback is not proven null or a concrete civilization.
- The two root words are distinct, have no direct writer/equality operation, and are not co-called by a recovered function. Pointer equality and publication remain unresolved. Sparse canonical use does not prove that the canonical slot is dead.
- SDK naming and historical reports do not prove original pointer equality.

**Independent evidence:** generic helper, wrapper, cache miss/hit branches, map erase, player teardown, manager field lifecycle, and root scan are separate. The rejected `0x0167ea80` base-table candidate is a separate separator.

**Repeated/assumption-echo evidence:** repeated singleton language and repeated lower-bound reports derive from the same small original instruction family; they are not independent runtime observations.

**Smallest separating observation and whether performed:** performed. Root scans plus `0x00e5c780/0x00ba9370`, `0x01021300` miss branch, and `0x00bad7a0/0x01022460` separated storage, lookup, cache, and ownership.

**Post-campaign classification and status:** `UNRESOLVED_BUT_SAFE`; lookup/cache mechanics resolved, root publication/equality open.

**Minimum OpenSpore semantics:** two opaque star ports; manager-owned `mEmpires` and `+0x204` state; `ceilingByPoliticalId`; successor-tolerant, non-membership-validating player cache; separate map erase and cache invalidation; explicit no-empire fallback.

**Dependent decisions and safety:** equal roots could permit one shared service owner; phase-specific roots require rebind/order/cache rules; obsolete canonical use cannot be assumed. Root equality and publication may remain deferred; exact-find, exact-cache, guaranteed cache invalidation, and guaranteed null fallback are not safe assumptions.

### 3) `CONFLICT-MODE-STATE-AXES`

**Addresses and symbols:** `0x007d85b0`, `0x007d8c80`, `0x00b3d350`, `0x00b5b840`, `0x00b5b880`, `0x00b5b8a0`, `0x00b5b8c0`, `0x00b5b8e0`, `0x00b5b960`, `0x00b63510`, `0x01021960`, `0x01485550`, `0x01485558`, `0x00e616c0`, `0x013f57f8`, `0x0057ce80`.

**Competing hypotheses:** one global mode enum; separate axes with a request/transition bridge; synchronous global transition; first-request-wins pending strategy state; SDK IGameMode as semantic reference versus concrete Cell/editor ABI; orthogonal SpaceContext/scenario/input/App axes.

**Evidence for and against.**

- App’s active index is at `cGameModeManager+0x28`; `0x007d85b0` performs old OnExit, index write, exit notification, new OnEnter, enter notification in helper-local order.
- Strategy fields and first-request guards are independently visible at `0x00b5b840`, `0x00b5b880`, `0x00b5b8a0`, `0x00b5b8c0`, `0x00b5b8e0`, and `0x00b5b960`.
- `0x01021960` writes only `SpacePlayerData+0x10`; input, scenario, App, strategy, and Cell owners are distinct. Numeric overlap does not alias state.
- The App helper’s send order is exact, but `MessageSend` listener timing and payload mapping are not complete; no runtime transition trace exists.
- `0x01485558` and `0x01485550` are separate installed Cell vptrs. The 27-entry scanner run is not a complete primary ABI. Raw slot numbers are not original runtime proof.

**Independent evidence:** App transition, strategy constructor/guards, Space setter, Cell/editor constructors, and table bytes are distinct evidence classes.

**Repeated/assumption-echo evidence:** repeated state-machine summaries are not independent bodies; SDK names and slot counts do not settle concrete ownership.

**Smallest separating observation and whether performed:** performed. Direct construction, transition, strategy, Space setter, and table inspection separated the semantic axes. Runtime listener timing was not performed.

**Post-campaign classification and status:** `ARCHITECTURE_LOCAL`; semantic axes bounded, timing and raw ABI deferred.

**Minimum OpenSpore semantics:** separate axes; validated index/name requests; same-request no-op; explicit transition phases; first-request-wins only for a retained strategy pending channel; semantic mode interface without raw slots.

**Dependent decisions and safety:** synchronous versus queued timing only changes notification contracts; original ABI adoption would require a separate vtable adapter. Listener timing, payloads, input routing, scenario internals, fixed-step behavior, and unknown slots are safely deferrable.

### 4) `CONFLICT-PROPERTY-PERSISTENCE-CODEC`

**Addresses and symbols:** `0x00422eb0`, `0x00692880`, `0x00692900`, `0x00693e10`, `0x006a1540`, `0x006a2f60`, `0x00693390`, `0x00694440`, `0x00b26800`, `0x00b26840`, `0x00b274e0`, `0x00b279e0`, `0x00b28ec0`, `0x006891f0`, `0x00e51300`, `0x00e51370`, `0x00e61550`, `0x00e63d10`, `0x00e80ba0`, `0x00b3d440`.

**Competing hypotheses:** 0x14 runtime Property versus imported 4-byte view; local PropertyList framing versus parent/raw pointer persistence; typed wire payload branches; setup/teardown versus actual ClassSerializer Write/Read; class/attribute object graph versus raw host pointers; ClassSerializer-backed header versus raw 0x68 block; Cell save candidate versus live mode state; incomplete manager view versus confirmed named member; bounded replacement versus universal atomicity; version carrier versus complete migration; open outer envelope; strong save/load candidates versus confirmed manager membership.

**Evidence for and against.**

- Direct `+0x10/+0x12` accesses and the 0x18 map stride reject the 4-byte Property layout as a complete runtime model.
- `0x006a1540/0x006a2f60` show signed count, local ID/value entries, and a negative three-word parent-reference branch. Parent field order and outer envelope remain unknown.
- `0x00692900/0x00693e10` are the concrete stream callback bodies; the neighboring addresses are setup/teardown. Historical SDK labels do not override direct function roles.
- Class/attribute identity resolution and deferred object association support stable references, not host addresses. Exact object-table bytes and cycle rules are unresolved.
- `cSavedGameHeader` is a 0x68 object with ClassSerializer wrappers, not a raw file block.
- `cCellSerializableData` is a 0xec serializable candidate; `0x00e627a0/0x00e63d10` are in-memory handoff paths, not a disk transaction. Field survival and automatic mode-exit save are unresolved.
- `0x00b28ec0` and `0x00b279e0` are the strongest save/load candidates, but they are **not confirmed cGamePersistenceManager members**; no manager vtable/this binding is proven.
- Temp/close/old/replace is observed, but cross-file atomicity, rollback, outer `.spo/.prop` bytes, CRC placement, and migration are not.

**Independent evidence:** direct Property getter/setter/writer/reader, function-boundary query, ClassSerializer writer/reader, object-dispatch paths, header factory/wrappers, Cell constructor/write/read/handoff, and file replacement bodies are separate surfaces.

**Repeated/assumption-echo evidence:** SDK comments, historical `cGamePersistenceManager` naming, and repeated “serializable” claims do not establish exact fields, membership, or runtime round-trip survival.

**Smallest separating observation and whether performed:** performed. Direct local codec pairs, address/body separator, Cell serializer path, and save/load stream lifecycle separated local semantics from the open save graph. No save/load runtime round trip was performed.

**Post-campaign classification and status:** `ARCHITECTURE_CHANGING`; persistence spine bounded, object/reference/restore graph and mode handoff open.

**Minimum OpenSpore semantics:** 0x14 Property carrier; 0x18 local entries; explicit count/ID/type/flags/array handling; class/attribute callback schema; stable object reference table; deferred restore; ClassSerializer-backed header; explicit Cell save candidate; live mode/presentation/pointer state transient; temp/close/replace boundary.

**Dependent decisions and safety:** a raw or pointer-based format forces an envelope/object-table redesign; runtime descriptors and version branches force a schema registry/migration graph; shared mode ownership versus DTO handoff forces a transfer protocol; independent artifact commits force a multi-file transaction. Outer bytes, unknown payloads, parent order, descriptors, migration, field survival, and crash behavior are deferrable only absent compatibility requirements.

### 5) `CONFLICT-MESSAGE-QUEUE-AND-EVENT-ABI`

**Addresses and symbols:** `0x008839a0`, `0x008839e0`, `0x00883a30`, `0x00884100`, `0x008841f0`, `0x00884550`, `0x00884700`, `0x008853e7`, `0x008854a0`, `0x00885710`, `0x00885890`, `0x00885930`, `0x01427920`.

**Competing hypotheses:** universal event ABI; one App record; send/post aliases; transport implies StandardMessage; one total-order bus; bounded App transport plus family-specific payloads.

**Evidence for and against.**

- The semantic-prefix test rejects a universal payload ABI: StandardMessage, UTFWin::Message, AnimationMessage, `cCommEvent`, and space records begin with incompatible roles/layouts.
- Entry is 0x14 bytes; deferred queue records are 0x18 bytes. `0x00884100` is the outer processor, `0x00884550` the record walker, `0x008841f0` cleanup/storage walking, and `0x00884700` the dispatch processor.
- Send performs immediate registry traversal; Post/PostFunction enqueue 0x18 records through `0x00885710`.
- Listener and handler/context targets are distinct; callback return is not used as a universal consume bit. Family order and ownership remain separate.

**Independent evidence:** raw producer, registration, dequeue, dispatch, and family-layout bodies are separate. `0x01427920` ownership is structural, not RTTI proof.

**Repeated/assumption-echo evidence:** historical universal-event and message-map repetition does not add binary evidence.

**Smallest separating observation and whether performed:** performed. Direct queue boundary bodies, vtable assignment, and family-prefix comparison separated records and timing.

**Post-campaign classification and status:** `ARCHITECTURE_LOCAL`; transport boundary resolved.

**Minimum OpenSpore semantics:** immediate and deferred surfaces; separate registration/queue records; tagged listener/handler targets; family-specific schemas and ordering.

**Dependent decisions and safety:** a cross-family total-order requirement would need a new scheduler; a raw ABI/plugin requirement would need an adapter. Queue key units, thread/reentrancy, and `0x008853b0` are safely deferrable.

### 6) `CONFLICT-OPAQUE-FORWARDED-STATE`

**Addresses and symbols:** `0x00b5b800`, `0x00b3d320`, `0x00a42730`, `DAT_0167eaec`, `receiver+0x20`, `0x01654c00` through `0x01654c06`, `0x00ad12a0`, `0x00b3d2c0`, `0x00d2e4a0`, `0x00d2e580`, `0x00d2e8a0`, `0x00c099e0`.

**Competing hypotheses:** receiver/field pointer; opaque 32-bit state/handle; current mode ID; strategy/interface pointer; alias to input/game-mode manager; one enum including `0xffffffff`; recovered first writer/publication.

**Evidence for and against.**

- `0x00b5b800` calls `0x00b3d320`, tests the receiver, returns `0xffffffff` for zero, otherwise reads `receiver+0x20` through `0x00a42730`.
- Of 843 direct callsites, the exact partition is **829 scalar + 6 normalization + 1 return-only + 7 ambiguous = 843**. The categories correspond to scalar compare/branch/copy/pass, normalization/indexing, return-only, and bounded-ambiguous sites respectively. No strict returned-value pointer dereference was observed.
- The receiver is distinct from `DAT_0167eaf8` and `DAT_0167eb2c`; no result-to-named-mode-manager dataflow exists.
- `C00/C01/C02/C04/C05/C06` are observed comparison tokens; `C03` is not observed exactly. No typed writer unifies the tokens with `0xffffffff`.
- Direct xref, literal, byte-pattern, and memory searches found one read of `DAT_0167eaec` and no connected writer, constructor, `+0x20` store, clear, or teardown. Indirect publication remains possible.

**Independent evidence:** root body, caller census, selected consumer decompilation/p-code, and first-writer scan are independent.

**Repeated/assumption-echo evidence:** nearby manager names, co-call counts, and address-like constants are not pointer/alias/enum proof.

**Smallest separating observation and whether performed:** performed. Root mechanics, caller-use census, and direct first-writer search separated opaque by-value use from identity/lifecycle claims. Runtime first-writer/freshness was not observed.

**Post-campaign classification and status:** `ARCHITECTURE_CHANGING`; opaque contract bounded, first writer/physical identity open.

**Minimum OpenSpore semantics:** borrowed opaque uint32 read; exact `0xffffffff` absent-source result; distinct C00/C01/C02/C04/C05/C06; C03 unknown; no pointer/mode/strategy/player/enum promotion; explicit freshness/publication/teardown unknown.

**Dependent decisions and safety:** a named mode/strategy first writer would force typed routing and ownership; a pointer-backed field would force refcount/object identity; a tagged scalar would force a tagged-state and freshness adapter. C03, exact token names, and seven bounded callsites are deferrable under the opaque contract.

### 7) `CONFLICT-AVATAR-OWNER-LIFETIME`

**Addresses and symbols:** `0x00b1fdb0`, `0x00b1fd50`, `0x00b3d300`, `0x00b3d400`, `0x00bff2d0`, `0x01002bd0`, `0x00c099e0`, `0x00d2e380`, `0x00d2e4a0`, `0x00d2e580`, `0x00d2e8a0`, `0x00d39360`, `0x00ef10c0`, `0x010066e0`, `0x01006880`.

**Competing hypotheses:** authoritative current gameplay selection; borrowed transient pointer; presentation proxy; scalar handle; receiver-typed hybrid; universal avatar accessor.

**Evidence for and against.**

- `0x00b1fdb0` is a raw `+0x54` load. `0x00b1fd50` updates old/new flags and performs AddRef-new, store-new, Release-old; equal pointers do not churn and null is valid.
- Creature consumers use gameplay fields and vtable calls; `cCreatureBase+0xb54` is a separate AnimatedCreature presentation association.
- `0x00bff3ad-0x00bff3b4` obtains `DAT_016dc0fc`, not a noun slot. Its `+0x54` is the high-LOD planet-simulation field. The accessor is not globally `GetAvatar`.
- `result+0xd8` is `GetCurrentBrainLevel`; the historical `result+0x55c` association is rejected. `cSpeciesProfile+0x55c` is separate and its meaning remains open.
- Current noun publication/liveness is unresolved; current raw pointer is not a durable identity or generation handle.

**Independent evidence:** receiver chain, parent publication/teardown, noun-layout refcount body, creature consumers, and separate presentation structure are separate surfaces.

**Repeated/assumption-echo evidence:** the same tiny accessor body and historical avatar labels do not prove one semantic type; current OpenSpore avatar/pool code is comparison only.

**Smallest separating observation and whether performed:** performed. Exceptional receiver trace plus noun-layout refcount and gameplay consumers separated receiver semantics. Root equality/teardown remains coupled to cluster A; save field coverage remains coupled to cluster C.

**Post-campaign classification and status:** `ARCHITECTURE_LOCAL`; receiver-typed contract resolved.

**Minimum OpenSpore semantics:** receiver-typed ports; noun-layout current gameplay selection with borrowed reads and exact replacement; separate high-LOD planet, Cell pool, presentation, progression, and save domains.

**Dependent decisions and safety:** root publication affects which receiver supplies selection; save restoration of current pointers/presentation affects cluster C. Source-symbol identity, complete owner multiplicity, detach timing, null classification, and exact save fields are deferrable unless compatibility is required.

### 8) `CONFLICT-CELL-RUNTIME-PRESENTATION-LIFECYCLE`

**Addresses and symbols:** `0x00e74a20`, `0x00e66010`, `0x00e6d8f0`, `0x00e78c00`, `0x00e780a0`, `0x00e7fd00`, `0x00e7fc00`, `0x00e81f30`, `0x00e80ba0`, `0x00e806b0`, `0x00e7f3a0`, `0x00e6d200`.

**Competing hypotheses:** merged Cell runtime; explicit simulation/presentation split; transient presentation proxies; content/serializable state boundary.

**Evidence for and against.**

- Separate `cCellGame`, `cCellGFX`, and `cCellUI` globals/structures and separate initialization/OnExit/Dispose paths reject merged ownership.
- `0x00e66010` clears `cCellObjectData+0x248` and releases the GFX record without releasing the Cell pool entry. `0x00e6d8f0` writes a new GFX index to the same Cell. These are separate branches, not a proven atomic detach/rebuild call.
- `0x00e780a0` and `0x00e7fd00` release old Cell identities during despawn/reload.
- `mModelKey`/`mCellResource`, GFX/UI handles, gameplay state, and `cCellSerializableData` are separate layers. The serializable handoff is in memory; it is not a disk transaction.

**Independent evidence:** create, detach, rebuild, despawn, reload, mode teardown, service dispose, content lookup, and serializable handoff bodies are separate.

**Repeated/assumption-echo evidence:** static lifecycle descriptions are not runtime ordering; a modern stable CellId is a recommendation, not universal original behavior.

**Smallest separating observation and whether performed:** performed. Static field/handle snapshot across the lifecycle separated identity, presentation, content, and save domains. No positive Cell-mode runtime trace was performed.

**Post-campaign classification and status:** `ARCHITECTURE_LOCAL`; ownership split resolved.

**Minimum OpenSpore semantics:** stable simulation CellId separate from presentation; explicit create/mutate/attach/detach/rebuild/death/despawn/reload/OnExit/Dispose transitions; live GFX/UI/query/world state transient.

**Dependent decisions and safety:** save-on-mode-exit or original Cell ABI requirements couple this to clusters C or the vtable trigger. GPU retirement, pool exhaustion, respawn policy, exact update order, and field coverage are deferrable.

### 9) `CONFLICT-RESOURCE-IDENTITY-CACHE`

**Addresses and symbols:** `0x01436ae8`, `0x008e20c0`, `0x008e0d30`, `0x008de940`, `0x008de310`, `0x008df9b0`, `0x008dfb20`, `0x008de280`, `0x008de360`, `0x008de3b0`, `0x008de400`, `0x008da3d0`, `0x00e82340`, `0x00e82420`, `0x00e823a0`, `0x00e82280`, `0x00e823e0`, `0x00e824d0`, `0x016b44f0`.

**Competing hypotheses:** one global identity; layered identities; cache key equals runtime object; DBPF row order is identity; one global provider; runtime object is durable identity.

**Evidence for and against.**

- Manager/provider requests use full `ResourceKey`; `0x00e82420` searches only `instanceID` and serializer pointer. Cell local identity is therefore distinct.
- `DatabasePackedFile` has a ResourceKey map; manager has separate database, factory, type-map, cache, and filename registries.
- Cache calls are key-based and return separate resource objects; records have separate leases. Runtime pointers and serializer pointers are not durable content identity.
- DBPF row order is serialization/enumeration order; database priority and first-match traversal are separate. The current one-package parser is comparison context only.
- Runtime package precedence, eviction, async, and exact release timing remain unresolved.

**Independent evidence:** manager layout/vtable, database map/list, factory, cache traversal, record lease, Cell Create/load/release, and current-provider comparison are separate.

**Repeated/assumption-echo evidence:** full-key recurrence in manager APIs is convergent contract evidence, not independent runtime proof; current source behavior is not original proof.

**Smallest separating observation and whether performed:** performed. Cell hit/miss, lazy load/release, database registration/find, and cache hit/insert/flush bodies separated the layers. No positive resource trace was performed.

**Post-campaign classification and status:** `ARCHITECTURE_LOCAL`; identity layering resolved, runtime precedence provisional.

**Minimum OpenSpore semantics:** field-aware full ResourceKey; separate Cell pair identity; separate database/factory/cache/lease/runtime-object layers; explicit priority/override and first-hit/first-success policies.

**Dependent decisions and safety:** exact cache eviction/package precedence needs a provider policy adapter if made compatible; pointer survival needs a typed runtime-handle boundary. Runtime precedence, eviction, async, rekey, and address aliases are safely deferrable.

## 3. Resolved contradictions

The following boundaries are resolved well enough to freeze as semantic architecture:

- The noun/star roots are distinct storage words; physical aliasing is rejected. Value equality is not selected.
- Noun and empire lookups are lower-bound/ceiling operations, not exact find.
- The current-player cache is lazy and can return/store a mismatched successor; map erase does not clear it.
- Mode state is separated into App, Simulator strategy, input, SpaceContext, scenario, and Cell axes.
- Property runtime layout, local PropertyList framing, ClassSerializer callback boundaries, and the Cell save candidate are bounded.
- App message transport separates immediate registry dispatch, deferred targeted delivery, and registration/queue records.
- Event families do not share a universal semantic payload ABI or total order.
- `0x00b5b800` is an opaque by-value read, not a proven pointer/mode/strategy.
- `0x00b1fdb0` is receiver-typed; the noun-layout path is a current gameplay creature selection and the exceptional `DAT_016dc0fc` path is high-LOD planet simulation.
- Cell simulation, GFX/UI presentation, content/resource state, and serializable Cell state are separate.
- Resource provider identity, Cell pair identity, cache identity, record leases, and runtime objects are separate.

## 4. Unresolved contradictions

The following remain unresolved but are not all redesign blockers:

- Noun/star root publication, value equality, liveness, and global teardown.
- `DAT_0167eaec` first writer, physical `receiver+0x20` identity, publication/freshness, and downstream ownership.
- Persistence outer envelope, complete object/reference table, descriptor contents, field survival, migration, cross-file commit, mode-handoff ownership, and `cGamePersistenceManager` binding for `0x00b28ec0`/`0x00b279e0` (strong save/load candidates, not confirmed members).
- Exact message timing/threading and concrete ABI residuals.
- Exact star relationship/global alias: `cStarManager+0x204` versus `DAT_0167eb14`; exact `0x00b25fb0` fallback type; and root-specific liveness.
- Key-0x06 consumer identity and telemetry read-back.
- Complete raw vtable extents and several function boundaries.

## 5. Decisions safe to freeze

The final decisions safe to freeze are:

1. Use semantic mode lifecycle/input/update interfaces; do not freeze raw original slots.
2. Keep immediate message dispatch separate from deferred targeted delivery and keep registration Entry separate from queue delivery.
3. Keep event families separate and do not promise cross-family total order.
4. Keep `0x00b5b800` opaque by value; do not expose receiver identity or ownership.
5. Keep noun-root ports separate; noun-root publication/equality is the architecture-changing blocker.
6. Keep star-root ports separate; star-root equality/publication remains `UNRESOLVED — not frozen` but is safe-local under the current boundary.
7. Keep noun/empire lookup and cache semantics exactly at the lower-bound/successor-tolerant boundary.
8. Keep receiver-typed avatar access and noun-layout current-selection replacement mechanics.
9. Keep Cell simulation identity separate from GFX/UI, content/resource, and serializable state.
10. Keep ResourceKey provider identity separate from Cell pair identity, leases, caches, and runtime handles.
11. Keep Property/ClassSerializer schema, stable references, versioned header, Cell save candidate, and explicit transaction boundaries.
12. Keep the conditional vtable and anonymous keyed-record boundaries separate from the semantic architecture.

The detailed decision register is in `docs/analysis/architecture-decisions.md`.

## 6. Provisional decisions

The following are explicitly **UNRESOLVED and not frozen**:

- Whether noun/star root values are equal, phase-rebound, or separately published.
- **UNRESOLVED — not frozen:** exact `cStarManager+0x204` versus `DAT_0167eb14` alias and exact `0x00b25fb0` fallback type.
- **UNRESOLVED — not frozen:** `0x00b28ec0` and `0x00b279e0` are strong save/load candidates but not confirmed `cGamePersistenceManager` members.
- Whether `DAT_0167eaec` is a mode/strategy/owner object, a pointer-backed field, or a tagged scalar.
- The exact persistence outer envelope, reference table, descriptor/field graph, migration policy, field survival, and mode handoff.
- Exact event queue key semantics, thread affinity, and callback timing.
- The key-0x06 consumer and telemetry read-back.
- Complete raw vtable extents and function boundaries.

These are not alternatives to be selected in implementation. They are bounded unknowns that constrain future evidence collection.

## 7. Questions safely deferred until implementation

The following can be deferred while the stated safe boundaries remain in force:

- Event queue units, signed-zero behavior, frame placement, thread affinity, and recursion.
- Cell/editor/Terrain vtable counts and slot names when no original ABI compatibility is required.
- `C03` and the seven bounded-ambiguous `0x00b5b800` callsites under the opaque contract.
- Complete creature presentation detach timing and owner multiplicity.
- GFX/UI retirement timing, pool exhaustion, replacement policies, and full render phase order.
- Runtime package precedence, cache eviction, async completion, and exact rekey behavior.
- Outer `.spo/.prop` bytes, parent-reference field order, unknown Property payloads, descriptor contents, migration defaults, and crash recovery when byte compatibility is not required.
- Key-0x06 field meanings, owner class, external reference lifetime, and telemetry read-back.
- Exact `cStarManager+0x204` versus `DAT_0167eb14` alias and exact `0x00b25fb0` fallback type.
- `cGamePersistenceManager` membership for `0x00b28ec0` and `0x00b279e0`; they are strong save/load candidates, not confirmed manager members.
- Root equality/publication/teardown observations when dual-port characterization is sufficient.

Deferral ends when the question becomes a compatibility requirement or touches blocker clusters A, B, or C.

## 8. Final architecture-level blockers

The smallest unresolved set is exactly three coupled clusters. No evidence proves a smaller replacement.

### Cluster A: noun/star root publication, equality, and teardown

Addresses: `0x00b3d300`, `0x00b3d400`, `0x00b3d2a0`, `0x00b3d3a0`, `DAT_0167eae0`, `DAT_0167eb60`, `DAT_0167eae4`, `DAT_0167eb0c`.

Unresolved obligations are four publication states, four unpublication/teardown states, and two pair-equality relations. The interim boundary is four opaque ports with explicit lifecycle hooks. A single-owner outcome can collapse the state graph; a phase-specific outcome forces phase-aware identities, rebind ordering, and separate teardown/cache graphs. The star mechanics remain safe independently, but coupling the root publication decision to the noun root keeps this cluster open.

### Cluster B: `DAT_0167eaec`/`0x00b5b800` first writer, physical state identity, and downstream ownership

Addresses: `0x00b5b800`, `0x00b3d320`, `0x00a42730`, `DAT_0167eaec`, `receiver+0x20`, `0x00ad12a0`, `0x00d2e4a0`, `0x00d2e580`, `0x00d2e8a0`.

Unresolved obligations are first publisher, physical receiver/field type, publication/freshness, replacement/teardown, and downstream ownership. The opaque uint32 contract is safe but not a final state model. A mode/strategy owner forces typed routing and lifecycle; a pointer field forces object ownership and refcounting; a tagged scalar forces a tagged state and freshness adapter. These are major redesign outcomes, not implementation details.

### Cluster C: persistence object/reference/restore graph and mode handoff

Addresses: `0x00692900`, `0x00693e10`, `0x006a2f60`, `0x00695140`, `0x00b28ec0`, `0x00b279e0`, `0x00e63d10`, `0x00e80ba0`, `0x00ef10c0`, `0x01485598`.

Unresolved obligations are outer envelope, object/reference table, descriptor and field survival, migration, cross-file commit, mode handoff ownership, and `cGamePersistenceManager` binding for `0x00b28ec0`/`0x00b279e0` (strong save/load candidates, not confirmed members). The safe interim boundary is schema/callback plus stable-reference plus explicit transaction semantics. Raw pointers force an object-table redesign; runtime-populated conditional descriptors force a versioned schema/migration graph; shared mode ownership forces a transfer protocol; independent artifact commits force a multi-file transaction/recovery design.

An unresolved `ARCHITECTURE_CHANGING` item still forces a major redesign because it can invalidate the owner graph, lifecycle graph, routing graph, or persisted object graph. `ARCHITECTURE_LOCAL` and `UNRESOLVED_BUT_SAFE` are safe now because their unresolved details do not require collapsing the semantic boundary.

## 9. Two-conditional appendix

### `CONFLICT-VTABLE-AND-SDK-IDENTITY-CORPUS`

`0x00e616c0` installs `0x01485558` at Cell object `+0` and `0x01485550` at `+4`; `0x00e5c590` is an adjusting secondary destructor. This supports multiple interface/subobject ownership and rejects treating the 27-entry scanner run as a complete primary ABI. `0x01427920` is structurally supported as the message-manager candidate table; `0x01445cb8` is a UTFWin Window `+0x20c` subobject, not the message-manager primary.

This is `UNRESOLVED_BUT_SAFE`. Raw slot counts, SDK labels, interior function boundaries, UTFWin scanner candidates, and Terrain dimensions do not change the semantic interface unless original-object adoption, plugin ABI compatibility, or raw vtable dispatch is required. That requirement would force a separate compatibility ABI layer, not a collapse of the semantic mode/event architecture.

### `CONFLICT-ANONYMOUS-SPACE-RECORDS`

`0x00e39ab0` inserts independent `DAT_015fd910` table entries: key `0x0c` with 27 slots and key `0x06` with 24 slots. The values have separate nodes and payload pointers. Key `0x0c` has direct space-state consumers; no direct key-`0x06` consumer was found. The pair is not established as `cCommEvent`, StandardMessage, UTFWin, animation, Cell, resource, or protocol data. The conditional App/Telemetry encoder is not game persistence or a read-back ABI.

This is `UNRESOLVED_BUT_SAFE`. A direct key-`0x06` consumer, alias relationship, required telemetry read-back, or compatibility format would force a real sidecar/event dispatch or explicit telemetry schema redesign. Without such a requirement, two opaque independent keyed entries are safe.

## Source manifest

The exhaustive structured source manifest is in `knowledgegraph/research/architecture-resolution.json`. It includes all eleven track reports, all six follow-up reports, `knowledgegraph/research/conflict-adjudication.json`, and `docs/analysis/conflict-adjudication.md`.

## Evidence and clean-room limits

Original-binary evidence is separated from clean-room decisions and modern recommendations throughout. Raw vtable slot numbers, current source behavior, SDK naming, and historical report repetition are not treated as original runtime proof. Static call order is not runtime timing. No new runtime observation was performed.
