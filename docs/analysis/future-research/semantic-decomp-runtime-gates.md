# Semantic Decompilation Runtime Gates

**Status:** `NO_RUNTIME_EVIDENCE / DESIGN_ONLY`  
**Scope:** Eight `knowledgegraph/research/semantic-decomp/worker-*.json` campaign artifacts for `SporeApp.exe`.  
**Runtime rule:** Nothing below is observed runtime evidence. No Wine or original process was run. Every experiment is a future, human-approved gate only.
**Required gate count:** 15 records. These are the exact records classified as `NEEDS_RUNTIME` in the harmonized campaign outputs.

## Collection rule

The eight inputs reviewed were:

- `knowledgegraph/research/semantic-decomp/worker-00-roots.json`
- `knowledgegraph/research/semantic-decomp/worker-01-gameglobal.json`
- `knowledgegraph/research/semantic-decomp/worker-02-cell.json`
- `knowledgegraph/research/semantic-decomp/worker-03-space.json`
- `knowledgegraph/research/semantic-decomp/worker-04-editor-core.json`
- `knowledgegraph/research/semantic-decomp/worker-05-ui-shell.json`
- `knowledgegraph/research/semantic-decomp/worker-06-editor-support.json`
- `knowledgegraph/research/semantic-decomp/worker-07-sporepedia-events.json`

A record is included only when it is marked `NEEDS_RUNTIME`, has an equivalent required runtime gate, and the unresolved question can change materially different behavior, ownership, branch selection, carrier identity, or timing. Optional confirmation traces are excluded when the worker supplies a sufficient static contract or an explicit static replacement boundary.

Expected evidence below is the acceptance target for a future run, not evidence collected here. A runtime result must remain separate from static evidence until a manifest, raw trace, and independent review satisfy the stated criterion.

## 1. Root and shared-state gates

### `0x00b3d2a0` — `FUN_00b3d2a0` (alternate `cStarManager` pointer accessor)

**Source record:** `worker-00-roots.json`; static body is `MOV EAX,[0x0167eae4]; RET`.

- **Competing hypotheses:** `DAT_0167eae4` always aliases the canonical `DAT_0167eb0c`; it is a phase-specific star-manager instance while the canonical slot names another instance; one or both slots can be null, stale, replaced, or still valid during teardown.
- **Exact observable needed:** An ordered, owner-qualified trace of `DAT_0167eae4`, canonical `DAT_0167eb0c`, returns from `0x00b3d2a0` and `0x00b3d3a0`, and a downstream receiver field at initialization, first live use, mode transition, and teardown.
- **Smallest experiment:** Observe only the two global words, both accessor returns, and one downstream receiver across one naturally approved mode entry-to-exit cycle. Record equality, replacement, clearing, and phase without manufacturing a transition.
- **Success/failure decision criterion:** Success requires attributable records for publication/equality and teardown across the declared cycle. Any inequality, replacement window, stale value, or null transition requires phase-qualified ports. Failure to reach or attribute the lifecycle leaves the runtime-only question unresolved; it must not be converted into a singleton result.
- **Expected evidence:** A phase-by-phase table of raw slot values, accessor returns, receiver identity, equality result, and explicit clear/replace/no-observation status.
- **Runtime-plan reference:** `docs/analysis/runtime-experiments.md`, `RE-02`; `docs/analysis/runtime-oracle-plan.md`, shared-root lifecycle contract and `C-STATE` boundary.
- **Safety boundary:** Read-only owner-qualified observations only. Do not write either slot, force a mode transition, dereference an unproven value, run a broad trace, or touch canonical files. Any future run requires explicit approval, a disposable process/profile, and the shared machine lock.

### `0x00b3d300` — `FUN_00b3d300` (alternate `cGameNounManager` pointer accessor)

**Source record:** `worker-00-roots.json`; static body is `MOV EAX,[0x0167eae0]; RET`.

- **Competing hypotheses:** `DAT_0167eae0` always aliases canonical `DAT_0167eb60`; it is a phase-specific noun manager while the canonical slot names another instance; one or both slots can remain null, stale, or published through an indirect owner that is not the receiver observed by the consumer.
- **Exact observable needed:** Ordered reads of `DAT_0167eae0`, canonical `DAT_0167eb60`, both accessor returns, and the `ECX` receiver passed by `0x00bff2d0` to `0x00b21340` at initialization, first live use, mode transition, and teardown.
- **Smallest experiment:** Observe the two noun-root words, both accessors, and the one receiver handoff across one naturally approved mode cycle. Do not force the non-root receiver or synthesize noun-manager publication.
- **Success/failure decision criterion:** Success requires a complete owner/phase matrix showing publication, alias or inequality, receiver provenance, and teardown. A different receiver, stale/null value, or replacement window is a positive separation result that preserves distinct ports. Failure to attribute the cycle is `UNRESOLVED`, not evidence of a global noun singleton.
- **Expected evidence:** Raw slot/accessor values, receiver identity before `0x00b21340`, phase labels, equality or inequality, and explicit replacement/clear outcomes.
- **Runtime-plan reference:** `docs/analysis/runtime-experiments.md`, `RE-02` and `RE-11`; `docs/analysis/runtime-oracle-plan.md`, `C-STATE` owner qualification.
- **Safety boundary:** Read-only only. Do not alter noun-root slots, inject receiver values, force noun creation, or generalize one phase to all modes. A future run must be human-approved and isolated from the canonical binary and game state.

### `0x00b3d4f0` — `Simulator_GetUIMissionLogManager`

**Source record:** `worker-01-gameglobal.json`; the target returns `DAT_0167eb64` without validation.

- **Competing hypotheses:** The slot publishes the opaque UI mission-log manager consumed by the observed vtable/vector clients; it publishes a different manager or service object; the slot can be null, stale, replaced, or torn down before a consumer dereferences it. The SDK `cMissionManager` identity is explicitly not established.
- **Exact observable needed:** The first non-null write to `DAT_0167eb64`, the caller and phase, the value returned by `0x00b3d4f0`, the returned object's vtable identity, and one safe `0x00e30d20` or vtable `+0x38` consumer operation, including replacement or teardown if observed.
- **Smallest experiment:** On one naturally reached mission/communication event, use a read-only watchpoint on `DAT_0167eb64` and a bounded accessor/consumer trace. Record the publication-to-consumer order and the first teardown or replacement.
- **Success/failure decision criterion:** Success requires an attributable non-null publication before the first dereference, a stable live vtable during the consumer operation, and explicit lifetime coverage. A null window, stale value, replacement, or untraceable publisher keeps the manager opaque; no concrete class or `cMissionManager` identity may be promoted.
- **Expected evidence:** A slot transition record, accessor return, vtable pointer identity, consumer operation, and a separate teardown/replacement record or an explicit not-observed field.
- **Runtime-plan reference:** `docs/analysis/runtime-experiments.md`, `RE-04` and `RE-16`; `docs/analysis/runtime-oracle-plan.md`, `C-EVENT` and `C-BOUNDARY`.
- **Safety boundary:** Read-only debugger observation only. Do not write the global, trigger a synthetic mission, install a hook, call the function manually, or run a network path. No canonical game state may be changed.

## 2. Cell lifecycle and behavior gates

### `0x00e7a7c0` — `FUN_00e7a7c0` (Cell damage resolver)

**Source record:** `worker-02-cell.json`; `needs_runtime.required=true`.

- **Competing hypotheses:** A permitted call reduces health, emits a reaction/UI/animation/effect sequence, and returns `1`; an initial gate rejects the call without the accepted health write; a lethal call routes to the player or non-player death branch according to runtime role/flag context; a zero-damage accepted call still follows the default effect path. The static body exposes the branch shape but not argument provenance or downstream ordering.
- **Exact observable needed:** One naturally reached call’s victim/attacker indices, health and guard fields, damage type/flags/effect flags, avatar relation, accepted/rejected return, exact health transition, and the ordered downstream calls to damage selection, nearby reaction, health rollover, animation/effect, and player/non-player death paths.
- **Smallest experiment:** Trace one naturally permitted nonlethal or lethal interaction, with a second observation only if the same path is reached naturally. Use entry/exit snapshots and bounded downstream probes; do not inject damage, death, or a health value.
- **Success/failure decision criterion:** Success requires one attributable call to select exactly one static branch and correlate every claimed field write and downstream phase without reconstructing the effect payload. A missing, contradictory, or unreachable downstream event leaves the exact runtime ordering unresolved; it does not invalidate the static branch mechanics.
- **Expected evidence:** Raw argument values, victim/attacker state snapshots, health before/after, branch predicate results, return value, and a phase-ordered list of observed downstream calls.
- **Runtime-plan reference:** `docs/analysis/runtime-experiments.md`, `RE-08`, `RE-10`, and `RE-15`; `docs/analysis/runtime-oracle-plan.md`, `C-ORDER`, `C-STATE`, and `C-BOUNDARY`.
- **Safety boundary:** Natural gameplay observation only. Do not synthesize damage, force death, write pool/health fields, capture effect or model payloads, or run a broad process trace. A future run requires the existing Cell reachability and read-only state gates.

### `0x00e7a4a0` — `FUN_00e7a4a0` (Cell death and terminal transition)

**Source record:** `worker-02-cell.json`; `needs_runtime.required=true`.

- **Competing hypotheses:** A non-player death marks the Cell terminal, schedules a type-6 interaction, applies a scale-dependent effect, and optionally updates kill state; a player death delegates to `0x00e72060` and schedules a distinct type-`0x1d` path; `playerRelated` and the effect/child helpers select materially different local state changes even though the static branch is visible.
- **Exact observable needed:** Victim/killer indices, `field_112`, `field_113`, scale/resource/model/query identity, `playerRelated`, effect/damage flags, avatar/mode guards, kill-count before/after, pending interaction type and payload, selected effect/animation helpers, and whether the old Cell remains until despawn.
- **Smallest experiment:** Observe one naturally reached lethal Cell death, preferably one branch only, with read-only probes at the death body, player/non-player delegate, nearby-reaction helper, child/effect helper, terminal flag helper, and type-specific dispatcher.
- **Success/failure decision criterion:** Success requires one trace to select either the non-player or player branch and correlate the corresponding event type, kill-counter condition, effect path, and terminal state. If only one carrier is observed or the event cannot be reached, retain the static branch and leave player-related provenance and event lifecycle unresolved.
- **Expected evidence:** Before/after terminal fields, event type and target-specific payload, kill-count delta, selected helper calls, and a phase-ordered state timeline.
- **Runtime-plan reference:** `docs/analysis/runtime-experiments.md`, `RE-08`, `RE-10`, and `RE-15`; `docs/analysis/runtime-oracle-plan.md`, `C-ORDER`, `C-STATE`, and `C-BOUNDARY`.
- **Safety boundary:** No forced lethal damage, direct field writes, synthetic events, or effect payload capture. Use only a naturally reached local event in an approved disposable Cell process.

### `0x00e7fd00` — `FUN_00e7fd00` (Cell stage rebuild)

**Source record:** `worker-02-cell.json`; `needs_runtime.required=true`.

- **Competing hypotheses:** The body drains old Cell/UI/GFX/service state, restores world and progression state, creates a new player Cell, and selects a hatch/presentation branch; a partial or service-unavailable rebuild leaves old or new identities in materially different states; the four progression inputs and `worldMode`, `worldModeValue`, and `hatchBranch` select different runtime branches than their decompiled names suggest.
- **Exact observable needed:** Entry and exit state, all four progression inputs, world-mode values, hatch branch, old/new pool counts, avatar index, serializable progression writes, world references, GFX/UI association counts, player-creation result, and the selected hatch/effect branch.
- **Smallest experiment:** Observe one naturally reached initial stage build or one natural frame-requested rebuild. Sample the drain, population, player-creation, GFX reconciliation, and hatch helpers once; do not force the reload flag or alter progression inputs.
- **Success/failure decision criterion:** Success requires an attributable transition from drained state to new player/population state with the observed input-to-field and branch mapping. Any partial creation, unpaired branch, or unreachable reload remains a bounded runtime negative and must not be reported as a completed rebuild.
- **Expected evidence:** A single ordered timeline from clear/drain through progression/world restoration, new identity creation, presentation attachment, hatch selection, and final state, with explicit null/unreadable outcomes.
- **Runtime-plan reference:** `docs/analysis/runtime-experiments.md`, `RE-07`, `RE-08`, and `RE-15`; `docs/analysis/runtime-oracle-plan.md`, `C-ORDER`, `C-STATE`, and `C-BOUNDARY`.
- **Safety boundary:** Natural stage entry/reload only. Do not write reload flags, fabricate progression, exhaust pools, or force world/service failures. The trace must remain bounded and read-only.

### `0x00e780a0` — `FUN_00e780a0` (Cell despawn and optional scale-aware replacement)

**Source record:** `worker-02-cell.json`; `needs_runtime.required=true`.

- **Competing hypotheses:** The old Cell is always identity-destructively released, while the caller-specific `replaceIfScaled` and scale mismatch cause a new replacement; no replacement occurs despite the scale condition; the optional GFX detach, child release, and scale-aware child/effect helper have different runtime ownership or ordering; the old resource remains usable during replacement even though the old pool object is released afterward.
- **Exact observable needed:** Cell pool index and object identity before/after, avatar index, GFX association, query/link state, child index, old scale/resource/model/transform, replacement context, effect flags, new pool index, and exact order of detach, child/effect work, replacement, and old-object release.
- **Smallest experiment:** Observe one naturally reached despawn with a replacement-capable caller if available; otherwise capture a normal despawn and classify the replacement question as not reached. Do not synthesize a despawn or alter `replaceIfScaled`.
- **Success/failure decision criterion:** Success requires the old identity release and any replacement to be separately attributable and ordered. A no-replacement trace, unavailable replacement path, or missing pool identity remains unresolved; it must not be generalized to all callers.
- **Expected evidence:** Before/after pool and GFX identities, new-object index if created, scale comparison result, helper-call order, and explicit old-release/replacement lifetime evidence.
- **Runtime-plan reference:** `docs/analysis/runtime-experiments.md`, `RE-08`, `RE-10`, and `RE-15`; `docs/analysis/runtime-oracle-plan.md`, `C-ORDER` and `C-STATE`.
- **Safety boundary:** Natural lifecycle observation only. Do not force death, despawn, pool exhaustion, scale changes, child indices, or replacement state. No original Cell process was run for this report.

## 3. Editor palette and message gates

### `0x005cb5a0` — `FUN_005cb5a0` (`PaletteUI` load containing function)

**Source record:** `worker-06-editor-support.json`; `runtime_gate.required=true`.

- **Competing hypotheses:** The body is a bounded `PaletteUI` load that replaces palette/layout references, constructs category objects, installs controls, and selects an initial category; a generic editor/UI bootstrap performs the same visible work with different selected-paint semantics; an empty or partially failed category vector produces a materially different startup state and message behavior.
- **Exact observable needed:** Palette/category count, constructed category and page identities, active-category pointer, helper object identities, layout/resource keys, App message `0x44ef2b8` payload and handler order, selected paint/index, and any EditorModel color/paint mutation.
- **Smallest experiment:** Observe one normal palette load through a fixed, pre-approved editor action. Capture the receiver, category/page counts, constructed object identities, active-category update, helper allocation, message dispatch, and selected-paint fields.
- **Success/failure decision criterion:** Success requires the static load/selection order to reconcile with runtime object identities and message/paint consumers. An empty, partial, or unreachable load is a bounded negative; it cannot promote a generic UI interpretation or a selected-paint identity.
- **Expected evidence:** A receiver-scoped object/vector table, active-category before/after, page/category IDs, helper creation/release order, message payload/handler sequence, and selected-paint state.
- **Runtime-plan reference:** `docs/analysis/runtime-experiments.md`, `RE-16` and `RE-17`; `docs/analysis/runtime-oracle-plan.md`, `C-EVENT` and `C-BOUNDARY`.
- **Safety boundary:** One fixed, human-approved editor observation only. Do not mutate palette state, synthesize messages, install replacements, capture palette assets, or use a broad trace. A future run must use an isolated profile and preserve canonical editor data.

### `0x005cb240` — `FUN_005cb240` (active category setter)

**Source record:** `worker-06-editor-support.json`; `runtime_gate.required=true`.

- **Competing hypotheses:** The live function is an active-category setter that validates an index, swaps old/new category controls, updates page navigation, and emits `0x44ef2b8`; the stale SDK alias `GetSelectedRigblockPaint` describes a materially different operation; the app call may be immediate, registered, deferred, or partially failed; an invalid index or absent category may produce a different visible state than the static no-op branch suggests.
- **Exact observable needed:** Requested index, category count, old/new category pointers, `+0x28` callback arguments, page-number result, `DAT_015ed22c`, message object and handler order, selected-paint/index changes, and result for an invalid index if naturally reached.
- **Smallest experiment:** Observe one valid category switch, with one naturally available out-of-range request as a negative control. Do not write the active-category field or manufacture a selection.
- **Success/failure decision criterion:** Success requires a valid switch to be tied to the observed old/new category identity, page update, and message/paint consumer order, while an invalid request leaves state unchanged. If message ownership or the selected-paint effect remains unobservable, retain the bounded setter classification and do not promote the SDK getter alias.
- **Expected evidence:** A field/object table before and after, exact slot-call arguments, page/toggle state, message payload/handler sequence, and invalid/valid branch result.
- **Runtime-plan reference:** `docs/analysis/runtime-experiments.md`, `RE-16` and `RE-17`; `docs/analysis/runtime-oracle-plan.md`, `C-EVENT` and `C-BOUNDARY`.
- **Safety boundary:** Read-only, fixed-action observation. Do not inject App messages, write category pointers, automate arbitrary UI actions, or run a replacement. The report does not authorize the proposed experiment.

### `0x005c53c0` — `FUN_005c53c0` (`PaletteCategoryUI` load containing function)

**Source record:** `worker-06-editor-support.json`; `runtime_gate.required=true`.

- **Competing hypotheses:** The function is a bounded category load that builds page/category children, binds swatch/palette support, configures app/service state, and updates selected-index state; it is a generic UI construction helper with a different selected-paint contract; a missing resource, page collection, or attachment produces a partial category state whose failure/visibility behavior differs from a successful load.
- **Exact observable needed:** Category and page identity, property/resource compatibility result, child allocation sizes and vector counts, swatch manager binding, app support region, selected index/paint, visibility/fade calls, and any downstream paint/message update.
- **Smallest experiment:** Observe one normal category load in the same approved palette session as the category-setter gate if possible. Capture only the receiver, category/page IDs, child vector state, swatch/app services, selected index/paint, and order of page setup and visibility changes.
- **Success/failure decision criterion:** Success requires the observed page/category construction order and selected-state condition to match one static path. Missing children, a failed compatibility check, or absent selected-paint propagation remains a bounded partial-load result and does not authorize a different SDK identity.
- **Expected evidence:** Receiver-scoped page/category object table, vector before/after, child allocation and release order, service pointers, visibility calls, and selected-paint state.
- **Runtime-plan reference:** `docs/analysis/runtime-experiments.md`, `RE-16` and `RE-17`; `docs/analysis/runtime-oracle-plan.md`, `C-EVENT` and `C-BOUNDARY`.
- **Safety boundary:** Natural editor action only. Do not inject category data, mutate selected index, capture resource payloads, or use an unapproved broad editor trace. Future runtime work remains human-gated and isolated.

### `0x005c9230` — `FUN_005c9230` (`PalettePageUI` load containing function)

**Source record:** `worker-06-editor-support.json`; `runtime_gate.required=true`.

- **Competing hypotheses:** The function loads a page, derives dimensions, constructs standard versus advanced items, attaches them, and leaves vectors populated; layout compatibility failure emits the observed diagnostic and leaves the page unpopulated; hashed item types select materially different advanced-item helpers; the decompiler return is a meaningful status or only a cleanup/last-pointer artifact ignored by the caller.
- **Exact observable needed:** Page ID, item IDs/types, class-ID lookup result, standard/advanced allocation and identity, vector sizes, item-panel attachment, derived dimensions, diagnostic occurrence, return value, and the caller’s treatment of that value.
- **Smallest experiment:** Observe one normal page load containing a standard item and, if naturally present, one advanced item. Record the receiver, page/item metadata, allocations, vector transitions, panel attachment, and the single direct caller’s return-value use.
- **Success/failure decision criterion:** Success requires each observed item to follow one static type branch and the page vector/panel state to match the load contract. A failed compatibility path, unobserved advanced branch, or unconsumed return remains unresolved; the return must not be promoted to a success flag.
- **Expected evidence:** Page/item metadata with bounded hashes, vector before/after, allocation/attachment order, dimensions, diagnostic and return observations, and caller handling.
- **Runtime-plan reference:** `docs/analysis/runtime-experiments.md`, `RE-16` and `RE-17`; `docs/analysis/runtime-oracle-plan.md`, `C-EVENT` and `C-BOUNDARY`.
- **Safety boundary:** Read-only page-load observation only. Do not inject items, change dimensions, capture page resources or payloads, or broaden the editor action. No original process was run.

## 4. Local timeline, editor-mode, and surrender gates

### `0x005dda30` — `FUN_005dda30` (EditorUI mode updater)

**Source record:** `worker-07-sporepedia-events.json`; `validation_strategy.status=NEEDS_RUNTIME`.

- **Competing hypotheses:** The target is a local editor-mode adapter that requests `cEditor::SetActiveMode`, updates the controller field, and runs mode-window hooks; the downstream editor path publishes a `cEditorAnimEvent` through a message bus whose delivery is deferred or consumed differently; the observed mode change is a global Simulator/App mode rather than a local editor state. The first is statically supported; the latter two require runtime separation.
- **Exact observable needed:** Requested mode, receiver `+0x60`, downstream `cEditor+0x31c`, exact `cEditor` receiver, each mode-window `+0x7c` call, and any `cEditorAnimEvent` send/post and listener execution with phase order.
- **Smallest experiment:** Observe one approved local `BuildMode -> PlayMode -> BuildMode` sequence, using read-only breakpoints at the target, `0x00587270`, and the recovered event send/post sites. Do not inject a mode request.
- **Success/failure decision criterion:** Success requires the controller mirror, downstream mode state, window hooks, and event transport to be observed as separate ordered phases. If only the controller field changes or the event path cannot be attributed, retain the local mode-adapter classification and do not promote a global mode or message-bus claim.
- **Expected evidence:** Ordered mode requests, field before/after, downstream receiver/state writes, window callback sequence, and event send/post/consumer records with explicit synchronous/deferred status.
- **Runtime-plan reference:** `docs/analysis/runtime-experiments.md`, `RE-04`, `RE-16`, and `RE-18`; `docs/analysis/runtime-oracle-plan.md`, `C-EVENT`, `C-ORDER`, and `C-BOUNDARY`.
- **Safety boundary:** One fixed, human-approved local editor action. Do not inject messages, force mode transitions, install a hook, or run an online or network path. No Wine or original process was run.

### `0x00ff3f00` — `FUN_00ff3f00` (local timeline-event command-line pointer accessor)

**Source record:** `worker-07-sporepedia-events.json`; `validation_strategy.status=NEEDS_RUNTIME`.

- **Competing hypotheses:** The target returns a local `UI/TimelineEventSporepediaData`-owned command-line-shaped pointer; it returns a different local event subtype with a different owner or relation to `receiver+0x90`; the field can be cleared/replaced/stale and its pointee can have a different vtable. The static evidence rejects `cSPAssetDataOTDB` and online-service interpretations but does not identify the exact subtype.
- **Exact observable needed:** A naturally occurring non-null store and read of `receiver+0x8c`, the pointee vtable, the return from `0x00ff3f00`, the consumer branch, replacement through `0x00ff4540`, and release through `0x00ff3e80`/teardown, plus the adjacent `+0x90` field relation.
- **Smallest experiment:** Observe one naturally reached local timeline event with a non-null field, one representative consumer, replacement, and teardown. Do not construct an object, install a synthetic pointee, or call the accessor directly; if no natural non-null path is reached, classify the subtype as unresolved.
- **Success/failure decision criterion:** Success requires a stable field owner and replacement/release order that remain distinct from `cSPAssetDataOTDB` and network state. A missing non-null path, a different pointee vtable, or an unexplained `+0x8c`/`+0x90` relation keeps the field opaque and the experiment non-passing for subtype identity.
- **Expected evidence:** Field before/after values, pointee vtable identity, accessor return, consumer branch, replacement/release order, and explicit local-only/network status.
- **Runtime-plan reference:** `docs/analysis/runtime-experiments.md`, `RE-16` and `RE-18`; `docs/analysis/runtime-oracle-plan.md`, `C-ORDER`, `C-STATE`, and `C-BOUNDARY`.
- **Safety boundary:** Natural local event observation only. Do not construct or inject objects, write `+0x8c`, enable networking, capture payloads, or use a broad process trace.

### `0x00dd0e10` — `FUN_00dd0e10` (local timeline-event variant handler)

**Source record:** `worker-07-sporepedia-events.json`; `validation_strategy.status=NEEDS_RUNTIME`.

- **Competing hypotheses:** The virtual method is a local `UI/TimelineEventSporepediaData` variant handler whose `+0x84/+0x88` discriminators select visible `~Epic`/`~MiniBoss`, local record, or empire-related paths; the same static branches have materially different subtype names, payload ownership, or visible-versus-state effects; the local helper may update only presentation or may participate in broader communication state. The `cSPAssetDataOTDB`, universal message, and online hypotheses are statically rejected, not runtime evidence.
- **Exact observable needed:** Receiver and vtable, `+0x84`, `+0x88`, `+0x9c`, the result of vtable `+0x0c`, selected visible label, selected local record/communication helper, and release order through `0x00dd0cf0`. A null-source or distinct-discriminator observation is a branch-isolation control when naturally available.
- **Smallest experiment:** Trigger one naturally local Epic or MiniBoss variant, then observe its selected downstream helper and teardown. Do not synthesize an object, inject a payload, or enable networking. If the event cannot be reached naturally, retain the vtable and static branch mechanics only.
- **Success/failure decision criterion:** Success requires one observed discriminator tuple to select one local helper and visible effect with a coherent release order. A different tuple selecting a different carrier, an unidentified `+0x0c` result, or an unreachable variant leaves subtype semantics unresolved; a local label must not be promoted to a universal event payload.
- **Expected evidence:** Receiver/vtable identity, discriminator and payload observations, selected label/helper, local state change, release order, and an explicit no-network boundary.
- **Runtime-plan reference:** `docs/analysis/runtime-experiments.md`, `RE-16` and `RE-18`; `docs/analysis/runtime-oracle-plan.md`, `C-ORDER`, `C-STATE`, and `C-BOUNDARY`.
- **Safety boundary:** Natural local UI/timeline event only. No synthetic event creation, field writes, network access, payload capture, or broad trace.

### `0x0102d1b0` — `FUN_0102d1b0` (local scenario-surrender orchestrator)

**Source record:** `worker-07-sporepedia-events.json`; `validation_strategy.status=NEEDS_RUNTIME`.

- **Competing hypotheses:** The target coordinates a local surrender state, an anonymous keyed space-record pair, a distinct `cCommEvent`, and achievement/UI effects; the anonymous pair is a projection of `cCommEvent`; an indirect path reaches an online service; the exact numeric selector chooses materially different diplomatic Planet and Solar behaviors. Static evidence rejects the latter carrier and network claims but leaves selector semantics and runtime ordering open.
- **Exact observable needed:** Caller parameters and numeric selector, keyed owner/key/value-node identities, `0xa0` `cCommEvent` allocation and manager append, `0x00aebe90` application, achievement call, temporary string lifetime, local UI/state effects, and any network-service crossing.
- **Smallest experiment:** Observe one naturally local surrender, with a second branch only if naturally reachable. Use read-only probes at the dispatcher, target, keyed-record builder, communication wrapper/creator/consumer, and achievement call. Do not inject surrender state, modify a selector, or force a network-disabled control.
- **Success/failure decision criterion:** Success requires the keyed pair, `cCommEvent`, achievement state, and UI effects to be observed as separate lifecycles with a correlated selector and order. Observing only one carrier is a partial result and preserves the other as conditional. An unreachable or unattributable path is a bounded negative, not evidence that the other path does not exist.
- **Expected evidence:** Caller/selector record, carrier identities and vtable/owner fields, manager insertion/application order, achievement and UI order, temporary-string lifetime, and an explicit network-crossing result or bounded non-observation.
- **Runtime-plan reference:** `docs/analysis/runtime-experiments.md`, `RE-16` and `RE-18`; `docs/analysis/runtime-oracle-plan.md`, `C-ORDER`, `C-STATE`, and `C-BOUNDARY`.
- **Safety boundary:** One naturally local surrender in an approved isolated session. Do not send network traffic, inject surrender or communication events, mutate achievement state, capture event payloads, or modify save/profile data. No original process was run.

## Optional traces excluded from this gate set

The following worker experiments were not promoted because their records provide sufficient static adapters or explicitly state that runtime is optional for the current classification:

- `0x00606880`, `0x00aeb720`, `0x00c877f0`, and `0x00de9fc0` in `worker-03-space.json`, where static container, creator/dispatcher, inventory-mutator, or bootstrap boundaries are sufficient unless original ABI/UI compatibility is separately required.
- `0x00b28ec0`, `0x005e0000`, `0x004c5200`, and `0x0062c550` in `worker-04-editor-core.json`, whose current classifications do not require a runtime result for their established mechanics.
- `0x01073700`, `0x00834fa0`, `0x005bf9d0`, and `0x005c0380` in `worker-05-ui-shell.json`, whose static UI boundaries and branch mechanics are already sufficient; their proposed traces remain optional refinements, not runtime-only gates.

## Current handoff

This report contains proposed gates only. It does not authorize a launch, debugger attachment, breakpoint, memory read, input action, message injection, patch, replacement, Wine process, or evidence promotion. Static evidence remains unchanged; these 15 required-gate records are the harmonized `NEEDS_RUNTIME` set.
