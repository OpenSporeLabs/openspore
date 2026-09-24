# Cross-Corpus Conflict Adjudication

## Scope and counts

- Selected and examined worker records: **263** (A=13, B=31, C=191, D=8, E=10, F=10).
- Authoritative type conflict population: **2,738** retained ConflictRecord rows; **not individually adjudicated** and retained as unresolved backlog.
- Exact derived resolution counts: **10** `RESOLVED_OBSERVED`, **52** `RESOLVED_SUPPORTED`, **0** `RESOLVED_INFERRED`, **27** `CONFLICT_REMAINS`, **0** `DUPLICATE_HYPOTHESES`, **174** `INSUFFICIENT_EVIDENCE`.
- Prior normalized buckets retained for audit: **86** `preferred_claim_with_limit`, **26** `preserved_alternatives`, **3** `same_observation_different_scope`, **148** `unresolved`; source-native closed contested claims: **13**; architecture-closing resolutions: **0**.
- Counts are non-disjoint. Conflict rows, source claims, projection rows, unknowns, contradictions, and selected worker records have different identities and must not be summed.
- No worker records were deduplicated. Cross-track overlap is retained because scope, evidence, and resolution claims differ even when subjects and addresses repeat.

## Methodology and evidence hierarchy

1. original_binary_bytes.
2. runtime_observation.
3. pinned_static_export.
4. targeted_static_body_or_dossier.
5. sdk_declaration.
6. vtable_xref_or_triage_projection.
7. research_synthesis.
8. current_openspore_source.

Static call order is not runtime validation. SDK names and current source cannot settle original layouts, ownership, event timing, or wire formats. The binary has no MSVC RTTI. Direct binary/control-flow, multiple call sites, and ABI/lifecycle convergence support bounded `RESOLVED_SUPPORTED` classifications; direct source-native observations may be `RESOLVED_OBSERVED`; for Track C preferred claims, at least two non-anchor direct static evidence entries are required, while SDK/projection anchors alone remain `INSUFFICIENT_EVIDENCE`. Unresolved questions and bounded static subclaims without closure remain `INSUFFICIENT_EVIDENCE`. Competing claims are preserved as `CONFLICT_REMAINS`; no record closes the full reconstruction architecture.

Source artifacts:

- `knowledgegraph/research/conflicts/00-corpus-inventory.json` — 12 ranked/selected records, SHA-256 `c2cfcc5869956d3de16a7da7817bfc19ea1d5e9bad85fef3d7e36697df2ad390`.
- `knowledgegraph/research/conflicts/track-b-vtable-fields.json` — 31 ranked/selected records, SHA-256 `3a6ef3bab31697ff9a86c5b6a14c8139ae9bf61cb46dfafc19b377bbc2c2c793`.
- `knowledgegraph/research/conflicts/track-c-state-events.json` — 191 ranked/selected records, SHA-256 `8f4f1e92596321d8becca1ab15b09a89cae519ed3bd24fcfeef1b57ab56fbd7a`.
- `knowledgegraph/research/conflicts/track-d-data-serialization.json` — 8 ranked/selected records, SHA-256 `0fd58603ad2930d4aeb5fe8918361a8bd14e226284053dd572e18dbf90b1bde3`.
- `knowledgegraph/research/conflicts/track-e-roots-functions.json` — 10 ranked/selected records, SHA-256 `24e7b0e38b2e8f635a9631d89d41d03116b27f4414035eb74405c764facacd3b`.
- `knowledgegraph/research/conflicts/track-f-cross-domain-impact.json` — 10 ranked/selected records, SHA-256 `10737458e1954a6d703eb2a0280dee2d01d1736737445edfd772f3062f7fe84f`.
- `knowledgegraph/research/global-campaign-2026/conflicts/track-a-type-signature.json` — 13 ranked/selected records, SHA-256 `e898e10c05eeee8ceb1a62b5f40db21df8c7dba619bf893b49b93d9b132f300d`.

Track A was copied byte-for-byte from `knowledgegraph/research/global-campaign-2026/conflicts/track-a-type-signature.json` to `knowledgegraph/research/conflicts/track-a-type-signature.json`; the misplaced source was not altered.

## Resolution taxonomy

Every derived record uses exactly one of the six campaign values in `resolution`: `RESOLVED_OBSERVED`, `RESOLVED_SUPPORTED`, `RESOLVED_INFERRED`, `CONFLICT_REMAINS`, `DUPLICATE_HYPOTHESES`, or `INSUFFICIENT_EVIDENCE`. The prior internal bucket is retained in `normalized_resolution`; source-native status and classification remain embedded in every record. Counts below cover the 263 selected records only; the 49 interpretation projections share conflict IDs and are not additive.

| Exact taxonomy | Count |
|---|---:|
| `RESOLVED_OBSERVED` | 10 |
| `RESOLVED_SUPPORTED` | 52 |
| `RESOLVED_INFERRED` | 0 |
| `CONFLICT_REMAINS` | 27 |
| `DUPLICATE_HYPOTHESES` | 0 |
| `INSUFFICIENT_EVIDENCE` | 174 |

| Track | `RESOLVED_OBSERVED` | `RESOLVED_SUPPORTED` | `RESOLVED_INFERRED` | `CONFLICT_REMAINS` | `DUPLICATE_HYPOTHESES` | `INSUFFICIENT_EVIDENCE` | Total |
|---|---:|---:|---:|---:|---:|---:|---:|
| A | 10 | 2 | 0 | 1 | 0 | 0 | 13 |
| B | 0 | 6 | 0 | 21 | 0 | 4 | 31 |
| C | 0 | 27 | 0 | 0 | 0 | 164 | 191 |
| D | 0 | 8 | 0 | 0 | 0 | 0 | 8 |
| E | 0 | 9 | 0 | 0 | 0 | 1 | 10 |
| F | 0 | 0 | 0 | 5 | 0 | 5 | 10 |

| Retained normalized bucket | Count |
|---|---:|
| `preferred_claim_with_limit` | 86 |
| `preserved_alternatives` | 26 |
| `same_observation_different_scope` | 3 |
| `unresolved` | 148 |

## Twelve requested final-report answers

### 1. 00b3d300 alternate cGameNounManager slot versus 00b3d400 canonical slot and downstream receiver identity

- **Answer:** Priority `critical`; score 12 is an ordering aid, not confidence. Concrete anchors/dimensions: `0x00aebe90`, `0x00aec5b6`, `0x00b21340`, `0x00b25fb0`, `0x00b32b20`, `0x00b3d2a0`, `0x00B3D2A0`, `0x00b3d300`, `0x00b3d3a0`, `0x00b3d400`.
- **Current adjudication:** The root-closure synthesis strongly characterizes the alternate slot as noun-manager-compatible while older type/relevance artifacts retain broader identity uncertainty.
- **Do not infer:** Do not call 00b3d300 a generic service locator, do not assume aliasing from shared callers, and do not collapse the alternate and canonical slots.
- **Selected worker links:** `CA-A-NM-011`, `CA-E-00B3D300`, `CA-F-CF-002`.
- **Next gate:** Read-only publisher/equality/teardown trace for DAT_0167eae0 and DAT_0167eb60, plus one receiver window at 00bff2d0.

### 2. Alternate/canonical cStarManager slots, lower-bound empire lookup, and lazy current-empire cache

- **Answer:** Priority `critical`; score 12 is an ordering aid, not confidence. Concrete anchors/dimensions: `0x00b32b20`, `0x00B3D2A0`, `0x00b3d2a0`, `0x00b3d2c0`, `0x00b3d300`, `0x00b3d3a0`, `0x00b3d400`, `0x00b3d440`, `0x00B3D440`, `0x00b5b800`.
- **Current adjudication:** Whether DAT_0167eae4 and DAT_0167eb0c are always equal or phase-specific instances.
- **Do not infer:** Do not treat lower_bound as exact_find, do not promote the no-empire context return to cCivilization*, and do not flatten manager identity and cache validity.
- **Selected worker links:** `CA-A-NM-011`, `CA-E-00B3D2A0`, `CA-F-CF-002`.
- **Next gate:** Characterize the current-empire cache miss/successor matrix, one erase/rekey site, and the publisher/alias chain for both star-manager slots.

### 3. SpaceContext, cScenarioMode::mMode, cGameInputManager mode fields, and App active-mode index

- **Answer:** Priority `critical`; score 12 is an ordering aid, not confidence. Concrete anchors/dimensions: `0x007d85b0`, `0x00b3d350`, `0x013f57f8`, `0x01485550`, `0x114`.
- **Current adjudication:** Mode transition message payloads, listener timing, and runtime reachability remain unresolved despite static send-order support.
- **Do not infer:** Do not merge App and Simulator game-mode managers, do not treat a pointer-run as the complete IGameMode ABI, and do not infer fixed-step semantics from SDK names.
- **Selected worker links:** `CA-B-TB-VT-006`, `CA-B-TB-VT-008`, `CA-F-CF-008`.
- **Next gate:** Freeze field/vtable dimensions separately, then trace one mode request through App selection, message dispatch, input routing, and runtime state snapshots.

### 4. App::Property layout, PropertyList transfer, ClassSerializer dispatch, and save/load state partition

- **Answer:** Priority `critical`; score 12 is an ordering aid, not confidence. Concrete anchors/dimensions: `0x00422eb0`, `0x00692880`, `0x006928bb`, `0x006928c0`, `0x006928C0`, `0x006928f0`, `0x006928f5`, `0x00693390`, `0x00693dd0`, `0x00693ddb`.
- **Current adjudication:** ClassSerializer exposes an attribute architecture but concrete bodies, pointer encoding, migration, and round-trip order are unresolved.
- **Do not infer:** Do not use a current parser, serializer interface, or SDK header to declare the original wire format or automatic cross-mode survival.
- **Selected worker links:** `CA-D-TD-DATA-002`, `CA-D-TD-DATA-003`, `CA-D-TD-DATA-004`, `CA-D-TD-DATA-007`, `CA-F-CF-003`, `CA-F-CF-009`.
- **Next gate:** Adjudicate Property bytes and parent encoding first, then trace one saved object through header, attributes, object-pointer restoration, and a failing stream operation.

### 5. IMessageManager send/post/post-function, registration Entry versus queue record, and event-family transport

- **Answer:** Priority `high`; score 11 is an ordering aid, not confidence. Concrete anchors/dimensions: `0x000847f0`, `0x00883a90`, `0x00883ad0`, `0x00883b20`, `0x008841f0`, `0x14`, `0x18`, `0x1c`.
- **Current adjudication:** 0x14-byte registration Entry and 0x18-byte queue record are distinct dimensions; no universal event ABI is proven.
- **Do not infer:** Do not merge equal-sized records, numeric IDs, or SDK names into a single event record or queue ABI.
- **Selected worker links:** `CA-C-Q-DISPATCH-ORDER`, `CA-C-Q-QUEUE-LAYOUT`, `CA-C-Q-SEND-POST-OWNERSHIP`, `CA-F-CF-008`.
- **Next gate:** Recover AddEntry, MessageSend, MessagePost, ProcessQueue, and one listener pair; record message ID, payload ownership, priority, return handling, and release order.

### 6. 00b5b800 forwarded receiver+0x20 state and its sentinel-gated consumers

- **Answer:** Priority `high`; score 10 is an ordering aid, not confidence. Concrete anchors/dimensions: `0x00a42730`, `0x00b3d2a0`, `0x00b3d300`, `0x00b3d320`, `0x00b3d3a0`, `0x00b3d400`, `0x00b5b800`, `0x00b5b810`, `0x01654c00`, `0x01654c06`.
- **Current adjudication:** Concrete receiver class, physical storage type, mode/strategy identity, and owner lifecycle are unknown.
- **Do not infer:** Do not call the returned value a player ID, generic service pointer, or strategy pointer from fan-in alone.
- **Selected worker links:** `CA-E-00B5B800`, `CA-F-CF-002`.
- **Next gate:** Find the first writer of DAT_0167eaec, type that writer's forwarded_object+0x20 store, and compare one sentinel gate with one ordinary consumer.

### 7. 00b1fdb0 cCreatureBase/cCreatureAnimal pointer and cGameNounManager mpAvatar ownership

- **Answer:** Priority `high`; score 10 is an ordering aid, not confidence. Concrete anchors/dimensions: `0x00845310`, `0x00b1fd50`, `0x00b1fdb0`, `0x00b3d300`, `0x00d2e4a0`, `0x00d2e580`, `0x00d2e720`, `0x00d2e8a0`, `0x00d39360`, `0x54`.
- **Current adjudication:** The receiver is strongly cGameNounManager mpAvatar in selected paths, but one selected ECX source comes from 01002bd0.
- **Do not infer:** Do not convert the pointer into a scalar or assume every caller is the canonical noun manager.
- **Selected worker links:** `CA-C-UNRESOLVED-KNOWLEDGEGRAPH-RESEARCH-STATE-MACHINES-ADDITIONAL-DOMAINS-JSO-AC46C6C134EE`, `CA-E-00B1FDB0`.
- **Next gate:** Classify 01002bd0 and the 00bff2d0 receiver window, then trace 00b1fd50 AddRef/store/Release replacement and one null consumer.

### 8. cCellGame/cCellObjectData/cell pool, cCellGFX/cCellUI, cCellModeStrategy, and presentation association

- **Answer:** Priority `high`; score 10 is an ordering aid, not confidence. Concrete anchors/dimensions: `0x01485550`.
- **Current adjudication:** Original mode-owned global cCellGFX/cCellUI state is not equivalent to current value-member ownership.
- **Do not infer:** Do not make presentation pixels or current vector/value members the authority for live gameplay state.
- **Selected worker links:** `CA-F-CF-005`.
- **Next gate:** Freeze stable EntityId/pool identity, then trace one Cell creation, gameplay mutation, presentation detach/rebuild, and mode teardown with field and handle snapshots.

### 9. ResourceKey identity order, cCellDataReference_ runtime layout, asset registry/cache traversal, and presentation resource identity

- **Answer:** Priority `high`; score 10 is an ordering aid, not confidence. Concrete anchors/dimensions: `0x00`, `0x008da3d0`, `0x00e821d0`, `0x00e82280`, `0x00e822c0`, `0x00E82340`, `0x00e82340`, `0x00e823a0`, `0x00e823a9`, `0x00e823da`.
- **Current adjudication:** Cache eviction, multi-package priority, async continuation, and exact original load order remain unknown.
- **Do not infer:** Do not treat current parser field order as original wire order or treat a presentation handle as a save record.
- **Selected worker links:** `CA-A-LC-004`, `CA-D-TD-DATA-001`, `CA-D-TD-DATA-006`, `CA-F-CF-004`.
- **Next gate:** Freeze the semantic tuple and typed reference contract, then trace one ResourceKey through cache hit, miss, record open, factory decode, preload, and release.

### 10. Vtable candidates, unknown vtable implementations, SDK boundary gaps, and concrete slot dimensions

- **Answer:** Priority `high`; score 8 is an ordering aid, not confidence. Concrete anchors/dimensions: `0x00`, `0x00641770`, `0x006F2F20`, `0x00951230`, `0x00DDE980`, `0x00e552f0`, `0x00E616C0`, `0x00e616c0`, `0x00e7fc00`, `0x00e80980`.
- **Current adjudication:** No MSVC RTTI is available to turn candidate bases into unique class identities.
- **Do not infer:** Do not use slot count, vtable family proximity, SDK naming, or fan-in as a class identity or language-inheritance proof.
- **Selected worker links:** `CA-A-VT-001`, `CA-A-VT-002`, `CA-A-VT-003`, `CA-F-CF-010`.
- **Next gate:** Carve high-information vtable references with constructor, consumer, and slot-body evidence; keep candidate, interface, and implementation rows separate.

### 11. Two anonymous 27-field/24-field space event records and their event/codec ownership

- **Answer:** Priority `medium`; score 7 is an ordering aid, not confidence. Concrete anchors/dimensions: `0x00e39ab0`.
- **Current adjudication:** Event action meanings and codec ownership are unresolved.
- **Do not infer:** Do not assign a semantic message type or a common universal event ABI from field count or record size.
- **Selected worker links:** `CA-C-Q-SPACE-RECORDS`.
- **Next gate:** Recover allocation and all consumers of 0x00E39AB0, type the record boundaries, and trace one construction-to-dispatch-to-release path.

### 12. The 1,977-record decomp-gap queue and its contradictions, unknowns, held infrastructure, and static upgrade claims

- **Answer:** Priority `medium`; score 8 is an ordering aid, not confidence. Concrete anchors/dimensions: none declared for this source-population blocker.
- **Current adjudication:** Contradiction and unknown observations are record-level and may overlap the same semantic subject.
- **Do not infer:** Do not report 100% gap coverage as runtime or persisted decompilation coverage, and do not treat 35 static unlocks as implementation authorization.
- **Selected worker links:** `CA-F-CF-010`.
- **Next gate:** Prioritize records by shared-root, state-machine, renderer-boundary, and data-model fan-in; preserve each worker claim and contradiction until independently adjudicated.

## Newly upgraded interpretations

- **Types/layouts:** Track A directly corrects selected vtable, species-profile, and planet-record interpretations; Track B adds bounded vtable/field/lifecycle preferences while retaining alternatives.
- **Functions:** Track A and Track E upgrade exact entry boundaries, wrapper semantics, root return contracts, and function mechanics at `0x00AEB720`, `0x00E82420`, `0x00B184C0`, `0x00B21340`, `0x00B3D2A0`, `0x00B72160`, `0x00B72260`, and the selected Track E roots.
- **State/events:** Static mode order, Cell lifecycle anchors, star-generation address drift, and separate event-family transports are stabilized without runtime promotion.
- **Data/serialization:** The 20-byte runtime `Property`, `PropertyList` local/parent branches, Cell content/runtime/save separation, cache lease behavior, and ClassSerializer boundary correction are bounded upgrades.
- **Roots:** Alternate noun/star manager, opaque forwarded state, avatar, noun materialization, empire bridge, container lookup, and Cell pool lifecycle contracts are upgraded; aliasing, ownership, and runtime identity remain gated.

## Improved reconstruction packages

The derived layer marks **28** canonical package IDs and **59** worker package labels as bounded, scope-separated, or architecturally preserved. Improvement is not implementation authorization; exact record IDs are in `knowledgegraph/research/conflict-adjudication.json:/improved_packages`.

| Canonical package | Improvement |
|---|---|
| `PKG-00-EVIDENCE-VALIDATION` | architectural_boundary_preserved, bounded_interpretation_upgraded; 4 selected records |
| `PKG-01-SHARED-STATE-ROOTS` | architectural_boundary_preserved, bounded_interpretation_upgraded; 58 selected records |
| `PKG-02-APP-LIFECYCLE` | architectural_boundary_preserved, bounded_interpretation_upgraded; 36 selected records |
| `PKG-03-PROPERTY-CONFIG` | bounded_interpretation_upgraded; 2 selected records |
| `PKG-03-RESOURCE-IO` | architectural_boundary_preserved, bounded_interpretation_upgraded, scope_boundary_upgraded; 13 selected records |
| `PKG-04-ASSET-GEOMETRY-TEXTURE` | architectural_boundary_preserved; 4 selected records |
| `PKG-05-CELL-CONTENT` | architectural_boundary_preserved, bounded_interpretation_upgraded, scope_boundary_upgraded; 28 selected records |
| `PKG-06-CELL-STATE` | architectural_boundary_preserved, bounded_interpretation_upgraded; 33 selected records |
| `PKG-07-CELL-MOVEMENT` | architectural_boundary_preserved, bounded_interpretation_upgraded; 24 selected records |
| `PKG-08-CELL-MODE` | architectural_boundary_preserved, bounded_interpretation_upgraded; 48 selected records |
| `PKG-09-CELL-PRESENTATION` | architectural_boundary_preserved, bounded_interpretation_upgraded; 28 selected records |
| `PKG-10-EDITOR-DISPATCH` | architectural_boundary_preserved, bounded_interpretation_upgraded; 38 selected records |
| `PKG-11-PERSISTENCE` | bounded_interpretation_upgraded, scope_boundary_upgraded; 7 selected records |
| `PKG-11-SIM-CORE` | architectural_boundary_preserved, bounded_interpretation_upgraded; 45 selected records |
| `PKG-12-SIM-SPACE` | architectural_boundary_preserved, bounded_interpretation_upgraded, scope_boundary_upgraded; 20 selected records |
| `PKG-13-SIM-CREATURE-TRIBECIV` | architectural_boundary_preserved, bounded_interpretation_upgraded, scope_boundary_upgraded; 20 selected records |
| `PKG-14-CROSS-MODE-OBJECT` | bounded_interpretation_upgraded; 1 selected records |
| `PKG-14-TERRAIN-WORLD` | architectural_boundary_preserved, bounded_interpretation_upgraded; 5 selected records |
| `PKG-15-EDITOR-SUPPORT` | architectural_boundary_preserved, bounded_interpretation_upgraded; 5 selected records |
| `PKG-16-SPOREPEDIA-ONLINE` | architectural_boundary_preserved, bounded_interpretation_upgraded; 3 selected records |
| `PKG-17-ANIMATION-SWARM` | architectural_boundary_preserved, bounded_interpretation_upgraded; 24 selected records |
| `PKG-18-UI-SCRIPTING` | architectural_boundary_preserved, bounded_interpretation_upgraded; 30 selected records |
| `PKG-19-AUDIO-INPUT` | architectural_boundary_preserved, bounded_interpretation_upgraded; 27 selected records |
| `PKG-20-GAMEGLOBAL` | architectural_boundary_preserved, bounded_interpretation_upgraded, scope_boundary_upgraded; 8 selected records |
| `PKG-21-UNKNOWN-ROUTING` | architectural_boundary_preserved, bounded_interpretation_upgraded; 6 selected records |
| `PKG-22-RUNTIME-CRT-STL` | architectural_boundary_preserved; 2 selected records |
| `PKG-PERSIST-01` | architectural_boundary_preserved; 2 selected records |
| `PKG-PERSIST-04` | architectural_boundary_preserved; 1 selected records |

## Top remaining blockers

1. **00b3d300 alternate cGameNounManager slot versus 00b3d400 canonical slot and downstream receiver identity** — The root-closure synthesis strongly characterizes the alternate slot as noun-manager-compatible while older type/relevance artifacts retain broader identity uncertainty; Whether DAT_0167eae0 and DAT_0167eb60 are pointer-equal at every lifecycle point; Whether every receiver passed to 00b21340, 00b1fdb0, and 00b25fb0 is the same noun-manager object; Whether the alternate slot and canonical slot have independent publication, phase, and teardown paths. Next: Read-only publisher/equality/teardown trace for DAT_0167eae0 and DAT_0167eb60, plus one receiver window at 00bff2d0.
2. **Alternate/canonical cStarManager slots, lower-bound empire lookup, and lazy current-empire cache** — Whether DAT_0167eae4 and DAT_0167eb0c are always equal or phase-specific instances; Whether a lower-bound successor may be cached as if it were the requested empire and how erase/rekey invalidates that cache; Whether the no-empire result of 00b25fb0 can share a narrow static return contract with its cCivilization-compatible normal result. Next: Characterize the current-empire cache miss/successor matrix, one erase/rekey site, and the publisher/alias chain for both star-manager slots.
3. **SpaceContext, cScenarioMode::mMode, cGameInputManager mode fields, and App active-mode index** — Mode transition message payloads, listener timing, and runtime reachability remain unresolved despite static send-order support; SpaceContext, scenario mode, input/game mode, and App mode registry are separate axes even when they share a caller or container; The 27-slot concrete Cell mode candidate is not identical to the 16-slot SDK IGameMode interface; The fixed-step SDK slot is not connected to observed frame pacing. Next: Freeze field/vtable dimensions separately, then trace one mode request through App selection, message dispatch, input routing, and runtime state snapshots.
4. **App::Property layout, PropertyList transfer, ClassSerializer dispatch, and save/load state partition** — ClassSerializer exposes an attribute architecture but concrete bodies, pointer encoding, migration, and round-trip order are unresolved; Property is 4 bytes in imported evidence and 0x14 bytes in SDK evidence; PropertyList local transfer is bounded, but parent inclusion, whole-save framing, rollback, atomicity, and versioning are not established; cGameData::Write is SDK-named but has teardown-like mechanics in the targeted body. Next: Adjudicate Property bytes and parent encoding first, then trace one saved object through header, attributes, object-pointer restoration, and a failing stream operation.
5. **IMessageManager send/post/post-function, registration Entry versus queue record, and event-family transport** — 0x14-byte registration Entry and 0x18-byte queue record are distinct dimensions; no universal event ABI is proven; Editor, animation, communication, deferred, Cell interaction, and StandardMessage-derived records remain separate families; Immediate versus queued timing for MessageSend, MessagePost, and MessagePostFunction is unresolved; Priority direction, tie order, consume-result behavior, lock rules, cancellation, removal, and release timing are unresolved. Next: Recover AddEntry, MessageSend, MessagePost, ProcessQueue, and one listener pair; record message ID, payload ownership, priority, return handling, and release order.
6. **00b5b800 forwarded receiver+0x20 state and its sentinel-gated consumers** — Concrete receiver class, physical storage type, mode/strategy identity, and owner lifecycle are unknown; The forwarded value must not be promoted to a mode ID, object pointer, or ISimulatorStrategy without direct storage evidence; The return is scalar/opaque in the null and sentinel paths but is read through forwarded_object+0x20 in the non-null path. Next: Find the first writer of DAT_0167eaec, type that writer's forwarded_object+0x20 store, and compare one sentinel gate with one ordinary consumer.

Additional blockers remain in manager publisher/teardown equality, exact event ordering, serializer transaction framing, vtable owner selection, and the 1,977-record decomp-gap residual queue.

## Which contradictions could materially change architecture?

**Yes:**

- `CONFLICT-ROOT-NOUN-MANAGER-SLOTS`: Independent noun-manager roots and lifetimes would change global-service ownership, entity lookup, mode teardown, and save ownership. Anchors: `0x00b3d300`, `0x00b3d400`.
- `CONFLICT-STAR-MANAGER-EMPIRE-CACHE`: A phase-specific star manager or incorrect lower-bound cache contract would alter empire, planet, player, and persistence state graphs. Anchors: `0x00b3d2a0`, `0x00ba9370`, `0x01021300`.
- `CONFLICT-MODE-STATE-AXES`: Collapsing SpaceContext, scenario mode, input mode, App mode, concrete tables, and IGameMode would change the mode-state architecture and dispatch ABI. Anchors: `0x007d85b0`, `0x00b3d350`, `0x114`.
- `CONFLICT-PROPERTY-PERSISTENCE-CODEC`: Property/codec, parent encoding, serializer transaction, and persistent-versus-transient boundaries determine the save architecture and migration surface. Anchors: inventory-level subject.
- `CONFLICT-MESSAGE-QUEUE-AND-EVENT-ABI`: Immediate versus queued semantics and family-specific payload adapters determine event transport architecture and ordering guarantees. Anchors: `0x14`, `0x18`, `0x1c`.
- `CONFLICT-OPAQUE-FORWARDED-STATE`: Typing forwarded_object+0x20 as a mode, strategy, pointer, or scalar changes mode-routing and service-ownership interfaces. Anchors: `0x00b5b800`, `0x01654c00`, `0x01654c06`, `0x20`.
- `CONFLICT-AVATAR-OWNER-LIFETIME`: Avatar return versus ownership would change noun-manager replacement, creature identity, and teardown contracts even if the pointer mechanics are already clear. Anchors: `0x00b1fd50`, `0x00b1fdb0`, `0x54`.
- `CONFLICT-CELL-RUNTIME-PRESENTATION-LIFECYCLE`: Collapsing gameplay pools, presentation services, mode lifecycle, and update ordering would change the simulation/presentation split. Anchors: `0x01485550`.
- `CONFLICT-RESOURCE-IDENTITY-CACHE`: Conceptual identity, memory order, cache leases, multi-package precedence, and serializer order determine the resource and persistence architecture. Anchors: inventory-level subject.

**Conditionally:**

- `CONFLICT-VTABLE-AND-SDK-IDENTITY-CORPUS`: A unique vtable owner/base/interface resolution could change dispatch and object-layout interfaces; candidate counts alone do not.
- `CONFLICT-ANONYMOUS-SPACE-RECORDS`: Anonymous record sizes and ownership could change event/codec design, but the current evidence does not yet establish an architecture-wide contradiction.

**Not an architecture change by itself:**

- `CONFLICT-DECOMP-GAP-RESIDUAL-POPULATION`: Coverage accounting changes readiness and evidence governance, not the reconstructed runtime architecture by itself.

## Final assessment

Yes. Nine ranked contradictions can materially change architecture if resolved incorrectly; two more are conditionally architecture-changing, and the decomp-gap accounting conflict changes readiness rather than architecture directly.

The safe current architecture keeps manager identities, mode axes, event families, content/runtime/save layers, resource identities, presentation services, and static/runtime evidence as separate contracts. The highest-value next gates are the noun/star root publisher-equality traces, one end-to-end mode/message trace, one concrete ClassSerializer/Property/save transaction trace, and one vtable constructor-to-dispatch trace.
