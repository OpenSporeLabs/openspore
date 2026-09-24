# Candidate runtime experiments

Status: **PROPOSED / UNVERIFIED**. No experiment in this document was executed while preparing it. The existing runtime record contains a positive historical main-menu startup observation, but no positive original Cell, persistence, Space, or presentation trace. S5 is a negative Cell-reachability result under the tested environment, not behavioral evidence about Cell.

These candidates are ordered by information gain. C0 is a prerequisite control, not a gameplay claim. C1-C3 target architecture-changing blockers; C4-C9 target the highest-value owner, ABI, lifecycle, and handoff boundaries. C10 is lower-priority scheduler discrimination.

## Selection and global rules

- Use only the pinned `SporeApp.exe` 3.1.0.22 identity: SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`, image base `0x00400000`, x86:LE:32.
- Require human approval, the normal display/Wine generation and machine-lock gates, explicit window geometry, and a fresh raw-JSONL destination before any future run.
- Prefer read-only entry, return, field, identity, and ordering observations. Do not install a hook, patch the executable, write to `SPORE/`, modify the canonical KG, or record proprietary payloads or memory dumps.
- Preserve zero events, clean exit, boot stall, renderer failure, and unreachable-target outcomes as distinct negative results. A screenshot or generic frame callback is not a Cell or gameplay observation.
- Any future result must retain binary/probe hashes, address convention, Wine generation, display/compositor, window geometry, input log, raw event path, event count, and exact outcome.

## Candidate summary

| Rank | ID | Highest-value question | Gate |
|---:|---|---|---|
| 0 | C0 | Can the original boot reproducibly under the approved environment? | Required prerequisite for runtime candidates |
| 1 | C1 | Are noun and star roots one owner, phase-specific, stale, or independent ports? | Architecture blocker A |
| 2 | C2 | Is `0x00b5b800` scalar state or pointer/owner-backed state, and who publishes it? | Architecture blocker B |
| 3 | C7 | What object/reference and failure graph does persistence actually use? | Architecture blocker C; explicit save/load path required |
| 4 | C3 | What are the App queue ABI, mode-announcement payload, and delivery timing? | M0, then a reachable transition |
| 5 | C4 | Does Cell lifecycle keep gameplay pool identity separate from GFX/UI? | Positive Cell entry |
| 6 | C5 | What does `receiver+0x54` own, and when is it replaced? | M0 plus a receiver-reachable stage |
| 7 | C6 | Where does Cell gameplay state end and presentation begin? | Positive Cell entry and one attributable interaction or display event |
| 8 | C8 | Does mode exit transfer live state, a DTO, or save automatically? | Positive mode transition; disposable save profile |
| 9 | C9 | How do star/empire lookup, cache, and Space context owners behave over selection and teardown? | Positive Space reachability, or a bounded negative |
| 10 | C10 | Is deferred timing owned by a distinct scheduler or merely App queue delivery? | M0; Cell or Space timing event if reachable |

## C0 — Fresh-generation boot control and exact negative classification

**Status:** PROPOSED / UNVERIFIED.

#### Hypothesis A

A fresh approved generation produces a reproducible positive boot with `entry`, `InitPlugins`, `Init`, `Startup`, and `IAppSystem::Get` in the historical supported order, with a renderer marker and a stable process/window.

#### Hypothesis B

The current environment produces a clean exit, stall, module-attach failure, registration gate, or renderer failure before a stable boot; no Cell experiment can be interpreted until that cause is isolated.

#### Required setup

- Human approval and the normal `OPENSPORE_MCP_TRUSTED=1`/approved runtime gate.
- Pinned binary and probe-set hashes; no replacement, patch, or synthetic input.
- Fresh wineserver generation immediately before the run, `DISPLAY`/compositor and xdotool identity recorded, and the shared machine lock free.
- Use `tools/observatory/probes/main_menu.json` unchanged. Record the module host, window identity, pinned geometry, duration, raw JSONL, stderr, and exact exit status.

#### Intervention

Perform one bounded 30-60 second boot observation with no gameplay input. Do not retry automatically and do not infer a menu-to-stage transition from startup events.

#### Observable outcome A

`entry`, `InitPlugins`, `Init`, `Startup`, and `IAppSystem::Get` fire in the supported order, the module host is identified, the renderer marker is present, and the process remains alive for the bounded window. This would be a positive boot-control observation only.

#### Observable outcome B

Breakpoints load but startup events are zero, the process exits cleanly before/after a brief window, the window never maps, the renderer marker is absent, or the run stalls. The result remains a boot/registration/renderer negative and is not evidence about Cell semantics.

#### Interpretation

Outcome A permits C1-C10 to proceed as separate runtime questions. Outcome B blocks behavioral interpretation and should trigger a separately scoped boot/Wine/renderer investigation rather than a Cell claim.

#### Failure conditions

- Binary, probe, Wine generation, display, or window identity is not pinned.
- Module discovery or tracer attachment is incomplete.
- Lock, approval, geometry, or stop conditions fail.
- A screenshot is used as a substitute for raw events.
- A clean exit, stall, or zero-event run is reported as “no gameplay behavior.”

#### Cleanup

Release the machine lock, perform the approved bounded wineserver/process teardown, verify no stale `SporeApp` or wineserver process remains, and preserve the raw artifact and negative reason. Do not edit historical output or the canonical KG.

## C1 — Noun/star root publication, equality, replacement, and teardown

**Status:** PROPOSED / UNVERIFIED. This is the primary runtime test for `BLOCKER-A`.

#### Hypothesis A

The noun slots `DAT_0167eae0`/`DAT_0167eb60` and star slots `DAT_0167eae4`/`DAT_0167eb0c` are phase-independent aliases or views of one owner per noun/star family, with a stable equality window and shared or coordinated teardown.

#### Hypothesis B

The four slots are independent or phase-specific ports. At least one pair is unequal during a transition, a replacement changes one slot without the other, or teardown invalidates one owner independently. No shared singleton or global teardown graph should be assumed.

#### Required setup

- C0 positive boot or an explicitly recorded decision to investigate a boot negative without making Cell claims.
- Pinned read-only probes for the four global words and their accessors `0x00b3d300`, `0x00b3d400`, `0x00b3d2a0`, and `0x00b3d3a0`.
- Correlated mode-manager and lifecycle observations around `0x007d85b0`, `0x007d8c80`, `0x007d9120`, `0x00e552f0`, `0x00e7fc00`, and `0x00e81f30` when those paths are reachable.
- Record owner, address, value/identity, mode phase, active index, and teardown phase for every sample. Do not dereference an opaque value based on resemblance.

#### Intervention

Use one naturally reachable, approved mode entry/exit and, if possible, one mode teardown. Capture pre-transition, between-old-exit/new-enter, post-transition, and post-dispose snapshots of all four words. If the stage is not reachable, perform no synthetic root write or state injection; the run remains a reachability negative.

#### Observable outcome A

Both noun values and both star values have a documented pointer-equality window, the same writer/rebind owner, and a coordinated teardown sequence. A would support an alias/view model only for the observed phase, not for all modes or save restoration.

#### Observable outcome B

At least one snapshot shows unequal values, a replacement window, a stale value after the new mode enters, or independent invalidation/unpublication. B would preserve separate owner-qualified ports and require phase-specific rebind, cache invalidation, and teardown handling.

#### Interpretation

A and B are observations of lifecycle behavior, not proof that either root is a named manager. A supports a conditional alias contract; B supports the current safe four-port boundary. Neither outcome licenses merging noun and star roots, asserting a singleton, or transferring ownership across modes.

#### Failure conditions

- A value is observed but its owner, publication, or phase cannot be identified.
- Only a generic frame or menu activity is captured.
- A direct scan is treated as exhaustive; computed/address-taken/runtime writers remain possible.
- Teardown is inferred from pointer clearing without an owner-lifetime trace.
- A failed boot prevents any lifecycle snapshot.

#### Cleanup

Stop at the approved teardown, release the lock, verify no processes remain, and retain a timestamped slot/owner/phase table. Do not write the slots, collapse the records in the KG, or edit the architecture decision register.

## C2 — First writer and ownership of `DAT_0167eaec` / forwarded `receiver+0x20`

**Status:** PROPOSED / UNVERIFIED. This is the primary runtime test for `BLOCKER-B`.

#### Hypothesis A

`0x00b5b800` is a borrowed opaque `uint32` read. `0x00b3d320` reads `DAT_0167eaec`; zero produces exactly `0xffffffff`; a nonzero source yields the value at `receiver+0x20`; no allocation, reference retention, replacement, or downstream ownership is established by the read.

#### Hypothesis B

`DAT_0167eaec` or `receiver+0x20` is a published owner, mode, strategy, or object field with a real first writer, replacement/freshness rule, reference lifetime, or downstream dereference/retention. This would change the routing and ownership architecture.

#### Required setup

- C0 and a reachable mode/state transition; otherwise this remains a static-only blocker.
- Pinned observations at `0x00b3d320`, `0x00a42730`, and `0x00b5b800`, plus known consumers `0x00ad12a0`, `0x00d2e4a0`, `0x00d2e580`, `0x00d2e8a0`, and `0x00c099e0`.
- Capture the source word, receiver identity/provenance, `receiver+0x20`, returned value, and consumer operation as separate records. Treat `C00`, `C01`, `C02`, `C04`, `C05`, `C06`, unknown `C03`, and `0xffffffff` as distinct raw observations.

#### Intervention

During a natural mode transition, observe the source and forwarded field before and after the known consumer paths. Use a bounded read-only writer trace only for candidate stores that are statically identified; do not write a sentinel, manufacture a receiver, or treat an unproven value as a pointer.

#### Observable outcome A

The source is observed changing only through an identified lifecycle event, `receiver+0x20` remains a scalar word, the returned value is used by scalar compare/branch/copy consumers, and no observed consumer dereferences or retains it. A supports the current opaque by-value contract and makes freshness/publication explicit unknowns.

#### Observable outcome B

A runtime writer or constructor populates the source, replacement or clear changes the forwarded value across a mode boundary, or a consumer treats the result as an owning/reference object. B requires a typed owner graph, freshness contract, and teardown contract before downstream architecture proceeds.

#### Interpretation

A does not prove that the field is semantically a mode ID or enum. B does not by itself prove a particular class or mode; it establishes that the current safe scalar boundary is insufficient for that compatibility requirement. If only a single value is seen with no writer/consumer path, the blocker remains unresolved.

#### Failure conditions

- No positive source/field observation or the transition is unreachable.
- A candidate value is dereferenced without receiver provenance.
- A producer and consumer are temporally conflated without a stable identity.
- Static negative scans are reported as proof that no computed or indirect writer exists.
- Any instrumentation would require a write, hook, patch, or payload dump.

#### Cleanup

Release the lock and approved process teardown, retain only bounded scalar/identity observations, and leave the opaque contract, sentinel, and unresolved publication questions unchanged.

## C3 — App message queue ABI, mode-announcement bridge, and queue timing

**Status:** PROPOSED / UNVERIFIED. This is a T0 chokepoint and does not authorize a universal event ABI.

#### Hypothesis A

The App manager is a family-specific transport: a 0x14-byte registration `Entry`, a separate 0x18-byte deferred delivery record, immediate `MessageSend` traversal, targeted deferred `MessagePost`/`MessagePostFunction`, conditional retain/release, and a distinct mode-announcement payload/bridge to Simulator strategy state. Domain payloads remain separate.

#### Hypothesis B

The observed transport records, domain payloads, and mode/Cell/UI records participate in a shared payload ABI, total order, pointer/ownership model, or consume/cancellation contract. This would be architecture-changing and would contradict the current family-separation boundary.

#### Required setup

- C0 positive boot and the existing approved menu/mode input path; do not use arbitrary clicks, typing, or a synthetic message injection.
- Pinned probes around `0x00884100`, `0x00884550`, `0x008841f0`, `0x00884700`, `0x00885710`, `0x00885890`, `0x00885930`, `0x008853e7/0x008854a0`, and mode listener `0x00b63510`.
- Correlate registration, message ID, payload pointer/size class, target kind, priority/key, queue insertion/processor, callback, release, mode ID, and `cStrategy` fields `+0x0c/+0x10/+0x14`.

#### Intervention

Use one fixed, pre-approved UI action that requests a mode transition if reachable. Observe the natural immediate/deferred messages, mode-exit `0x0212d3e7`, mode-enter `0x022d1adc`, callback-produced posts, and the next queue pass. If no transition occurs, record a reachable-frame/negative result without forcing a message.

#### Observable outcome A

Immediate callbacks complete before the send returns; deferred records are separate from registration entries; priority/tie order, targeted versus handler/context delivery, snapshot versus drain behavior, release order, and Simulator mode payload/commit writes are timestamped. A would validate the existing family-separated transport boundary and may close timing details for that path.

#### Observable outcome B

The same record or key crosses families, a listener return cancels later delivery, removal cancels queued delivery, a domain payload is retained by an unobserved owner, or mode/Simulator state commits before the expected callback boundary. B would require explicit cross-family ownership, timing, and cancellation decisions before implementation.

#### Interpretation

A does not establish a total order across StandardMessage, UTFWin, editor animation, Cell interaction, deferred-domain, or space records. B must be adjudicated from direct producer/consumer paths, not from record size, queue-key resemblance, or a generic frame. If only frame events occur, the experiment remains a UI/frame negative.

#### Failure conditions

- No attributable input, mode message, or queue processor event is observed.
- An event is assigned to a family solely because it passes through a common processor.
- A screenshot or UI response is used in place of callback/resource order.
- Queue key units, signed zero, thread affinity, reentrancy, or the unresolved `0x008853b0` word are invented.
- The run requires a message injection or a binary patch.

#### Cleanup

End the fixed-input walk, release the machine lock, perform approved teardown, and retain the raw queue/lifecycle order and exact negative reason. Keep family records separate in the resulting artifact.

## C4 — Cell mode lifecycle, pool identity, and GFX/UI ownership

**Status:** PROPOSED / UNVERIFIED. This targets the static Cell lifecycle and pool/presentation boundary; it is not a claim that Cell has been reached.

#### Hypothesis A

Cell simulation identity is held by the pooled `cCellObjectData`/player index and survives GFX/UI detach, preload, display changes, and presentation rebuild. `Initialize`, `OnEnter`, `Update`, `OnExit`, and `Dispose` have distinct lifecycle roles.

#### Hypothesis B

GFX/UI handles, avatar identity, and pool entries are co-owned or rebound as one graph. A presentation change, display stop, or despawn can change gameplay identity, and mode teardown cannot be modeled independently of the presentation stage.

#### Required setup

- C0 plus positive M1 Cell reachability; no Cell conclusion from menu-only activity.
- Pinned probes for `0x00e81cf0`, `0x00e552f0`, `0x00e80980`, `0x00e806b0`, `0x00e7fc00`, `0x00e81f30`, `0x00e80ba0`, `0x00e74a20`, `0x00e780a0`, `0x00e7fd00`, and `0x00e6d8f0`.
- Correlate `sCellGame+0x411c` player index, resolved object identity, pool index, GFX association, `+0x248`, model/resource references, reload flags `+0x51d8/+0x51d9`, and GFX display/preload events.
- Use bounded read-only field/identity samples; do not force pool exhaustion or write reload flags.

#### Intervention

Observe natural Cell entry, several bounded frames, any normal reload/display transition, and exit. Record pool allocation/deallocation and GFX/UI attach/detach at the same timestamps. If no Cell-specific event fires, stop after the entry gate as a negative.

#### Observable outcome A

The same pool index/object identity is observed across presentation changes while GFX handles or UI state are replaced independently; lifecycle callbacks occur in the expected order; reload drains and re-creates state without proving automatic save. A supports a separate simulation/presentation boundary.

#### Observable outcome B

Presentation operations change the player/pool identity, GFX release removes the gameplay object, or mode teardown releases/relinks gameplay state in lockstep with the stage. B would require a joint Cell/GFX owner graph and changes the current safe separation.

#### Interpretation

A is conditional on stable object identity and correlated event order. B may expose a hidden coupling but does not prove that presentation is gameplay authority. Unknown indirect service ownership, free-list sentinel, or reload subpath remains unknown.

#### Failure conditions

- Only the generic menu loop, renderer marker, or screenshots fire.
- Pool index and resolved entity are collapsed into one identity.
- GFX/UI functions are counted as Cell gameplay state without a stable correlation.
- A reload or death is synthesized by writing state.
- The run lacks C0, M1, or provenance fields.

#### Cleanup

Stop at the approved Cell observation boundary, release the lock, teardown the process, and retain only the bounded identity/handle/order table. Do not add runtime claims to the current negative Cell record.

## C5 — Receiver-typed avatar ownership and replacement

**Status:** PROPOSED / UNVERIFIED. This targets `0x00b1fdb0` and `0x00b1fd50` without promoting `+0x54` globally to “avatar.”

#### Hypothesis A

For a noun-layout receiver, `0x00b1fdb0` exposes a current gameplay-creature selection at `receiver+0x54`, while `0x00b1fd50` performs AddRef-new/store-new/Release-old replacement with equal-address no-op and null clear semantics. The receiver remains part of the type/owner contract.

#### Hypothesis B

`+0x54` is receiver-specific state. At least one reachable receiver, including the `DAT_016dc0fc`/high-LOD planet path around `0x00bff2d0`, exposes a non-avatar object, so a global avatar owner or pointer type is invalid.

#### Required setup

- C0 plus a naturally reachable noun-layout receiver and, where possible, a Space/creature receiver comparison.
- Pinned entry observations for `0x00b1fdb0` and `0x00b1fd50`, receiver identity, `+0x54` before/after, and any observed AddRef/Release or vtable call.
- Record the receiver type/provenance, current noun/player identity, object identity, and lifecycle phase. Do not dereference an unproven returned value.

#### Intervention

Use normal mode/creature/current-player selection or replacement actions. Observe a same-object request, a replacement request, and a null/teardown path if the reachable UI provides them; do not synthesize an object or force a receiver type.

#### Observable outcome A

The same noun-layout receiver carries a stable current gameplay-creature identity; replacement stores the new value only after a new reference is acquired and releases the old value; null/equal paths are distinguishable. A supports receiver-typed borrowed/current-selection ports.

#### Observable outcome B

A different receiver exposes a stable non-avatar identity, the `+0x54` value is not an intrusive gameplay object, or no consistent replacement/lifetime relation is observed. B supports keeping the field opaque and forbids a global `GetAvatar` interpretation.

#### Interpretation

A does not merge the Cell pool, Space planet, or presentation GFX identity. B is an architecture boundary for cross-stage ownership, not a failure of the receiver-typed contract. If only one receiver is reachable, the competing hypothesis remains unresolved.

#### Failure conditions

- Receiver provenance is not recorded before interpreting `+0x54`.
- Return-value use is mistaken for dereference or retention.
- A Cell pointer is compared directly with a Space planet or high-LOD receiver.
- A null/equal path is forced by a direct memory write.
- The stage containing the receiver is unreachable.

#### Cleanup

Release the lock and approved teardown, retain receiver/value/refcount observations only, and leave all noun, planet, Cell, and presentation identities separate.

## C6 — Cell gameplay state versus GFX/presentation/effect boundary

**Status:** PROPOSED / UNVERIFIED. This is the presentation-boundary experiment after C4 establishes Cell reachability.

#### Hypothesis A

Cell gameplay state, queued interaction dispatch, health/death state, and query/pool identity are authoritative before presentation. GFX preload, effect instances, animation, health rollover, and renderer submission consume or project that state and can be detached or rebuilt without becoming the gameplay owner.

#### Hypothesis B

GFX/effect/animation state feeds back into gameplay authority, or presentation lifecycle is required to interpret health, interaction, avatar, or pool state. The clean-room boundary would need a joint simulation/presentation contract.

#### Required setup

- Positive C4 Cell reachability, renderer marker, pinned window, and a bounded one-interaction trigger already approved by the human operator.
- Pinned probes for `0x00e7e6c0`, `0x00e7e130`, `0x00e63560`, `0x00e66840`, `0x00e6d200`, `0x00e62340`, `0x00e55120`, `0x00e666f0`, and the relevant renderer anchors.
- Record interaction type/timer, health/death fields, pool identity, effect instance, animation event, UI rollover, GFX handle, and frame annotation in one timeline. Do not capture effect/model payloads.

#### Intervention

Trigger exactly one naturally reachable Cell interaction or, if no interaction is safely reachable, observe one display/effect transition without injecting damage, death, or state. Use no more than the approved input and no direct writes.

#### Observable outcome A

A gameplay mutation and interaction dispatch are timestamped before or independently of GFX/effect/UI operations; the simulation identity remains stable while presentation handles can be created, stopped, replaced, or released. A supports the existing Cell/presentation separation.

#### Observable outcome B

A renderer/effect/UI operation is required for the gameplay transition, changes the authoritative pool/avatar/health state, or the gameplay event exists only when a presentation instance is live. B would require explicit joint ownership and lifecycle ordering.

#### Interpretation

A does not establish original pixel/material/pose behavior. B requires a new boundary only if the direct event/state order proves feedback or ownership. A frame, screenshot, or visual effect alone is insufficient.

#### Failure conditions

- No attributable Cell event or interaction is observed.
- Effect/animation names are assigned to raw types without payload evidence.
- Renderer calls are treated as gameplay calls.
- A direct damage/death write is used to create a transition.
- Presentation timing is inferred from a host OpenSpore fixture.

#### Cleanup

Stop before any replacement or renderer intervention, release the lock, teardown, and retain the bounded state/presentation timeline. Keep all visual outcomes marked proposed until a positive original trace exists.

## C7 — ClassSerializer/PropertyList object-reference graph and failure behavior

**Status:** PROPOSED / UNVERIFIED. This is the object/reference and stream branch part of `BLOCKER-C`.

#### Hypothesis A

`PropertyList::Write/Read` and `ClassSerializer` callbacks provide a local, versionable graph with stable object identities, deferred association, cycle handling, and short-circuit stream failure. The graph can remain separate from live pointers and presentation state.

#### Hypothesis B

The save format requires a specific object table, parent-reference encoding, cycle representation, descriptor/field graph, integrity/outer envelope, or rollback protocol. The callback body alone is insufficient to define persistence architecture or byte compatibility.

#### Required setup

- C0 and an explicitly approved, disposable profile/save location; never write to the original profile or `SPORE/`.
- Pinned probes for `0x006a1540`, `0x006a2f60`, `0x00692900`, `0x00693e10`, `0x00692880/0x00692f90`, `0x00b26800`, `0x00b26840`, `0x00b274e0`, and `0x00b279e0`.
- Capture stream open/write/read/failure positions, object count, identity tokens, parent branches, attribute callbacks, and finalization/reopen order without retaining proprietary payloads.
- Use a disposable copy for any failure or malformed-stream branch. A failure case must be preapproved and must not alter the original binary or save data.

#### Intervention

Perform one explicit save and reopen/load round trip in the disposable profile, then exercise one preapproved failing-stream or cyclic-reference branch if the runtime surface makes it reachable. Do not inject a pointer or modify serializer code.

#### Observable outcome A

A field/object/association matrix is emitted and restored, object identities are remapped or preserved according to a documented rule, cycles and deferred references have a bounded outcome, and the first stream failure has a deterministic short-circuit/rollback result. A supports a schema registry with explicit object references and transaction boundaries.

#### Observable outcome B

The run exposes a distinct object table, parent/cycle encoding, descriptor dependency, outer envelope/checksum/compression boundary, migration/default path, or failure that leaves partial state. B requires a separate schema/transaction design and no byte-compatible claim without byte fixtures.

#### Interpretation

A is not proof of byte compatibility with an original `.spo`/`.prop` file. B identifies which parts of the safe current architecture are provisional. If no positive save/load path exists, only a reachability negative is justified.

#### Failure conditions

- Original profile, `SPORE/`, or canonical KG is modified.
- The run relies on a decompilation-only reference or generated fixture.
- Stream failure is simulated by silently changing the target after the run.
- A field is called durable without surviving reopen.
- A callback order is treated as a complete object graph.

#### Cleanup

Close streams and the disposable test profile, verify the original profile and `SPORE/` are unchanged, release the machine lock, and preserve only bounded schema/order observations and exact failure outcomes.

## C8 — Cell mode handoff, automatic save, and restore ownership

**Status:** PROPOSED / UNVERIFIED. This separates persistence from mode teardown and addresses the `cGamePersistenceManager` membership question.

#### Hypothesis A

Cell `OnExit`/`Dispose` releases live mode/presentation state but does not automatically write a durable save. A serializable candidate or DTO is produced only at an explicit save or handoff boundary, and restore creates a new live owner.

#### Hypothesis B

Mode exit/dispose triggers a save or transfers a live serializable object across mode boundaries. The persistence service owns restoration, and the original pointer or live Cell graph survives the handoff.

#### Required setup

- C0 and positive mode/Cell reachability; use a disposable profile and explicitly approved save/load controls.
- Correlate `0x00e7fc00`, `0x00e81f30`, `0x00e51300`, `0x00e51370`, `0x00e61550`, `0x00e63d10`, `0x00e80ba0`, `0x00b3d440`, `0x00b28ec0`, and `0x00b279e0`.
- Record mode owner, `sCellGame` identity, avatar/pool identity, `cCellSerializableData` fields, serializer callbacks, service receiver/vtable, file open/close/replace, and restored identity.

#### Intervention

Perform one explicit save, one mode exit/dispose, and one restore/reload in the disposable profile. Observe whether any save operation occurs during teardown without invoking an extra save. Do not call load or write from a synthetic script.

#### Observable outcome A

No serializer/file write occurs during ordinary `OnExit`/`Dispose`; explicit save emits the candidate, close/replace completes, and load creates a new live Cell/runtime owner with presentation rebuilt separately. A supports a transient live state plus explicit serialized handoff boundary.

#### Observable outcome B

Teardown emits a save/checkpoint, a live pointer/DTO is transferred, or the persistence service restores the same object identity/owner. B supports automatic mode persistence or transfer semantics and changes the handoff architecture.

#### Interpretation

A does not claim that Cell state is never saved by another path. B does not prove `cGamePersistenceManager` membership without concrete this-binding or vtable/service-routing evidence. If the transition is unreachable, the result is negative only.

#### Failure conditions

- A save is inferred from a teardown call without file/serializer events.
- The same pointer is compared across process restart without an identity protocol.
- Original profile or executable data is changed.
- A serializer callback is called “automatic save” without an actual checkpoint.
- A restore is accepted solely because a mode entered.

#### Cleanup

Close the disposable profile and restore the original environment, release the lock, teardown processes, and retain the exact save/teardown/reload timeline. Do not promote the persistence membership or autosave claim.

## C9 — Star/empire lookup, cache, and Space context lifecycle

**Status:** PROPOSED / UNVERIFIED. This targets the Space/star half of the shared-state and noun/star lifecycle boundary.

#### Hypothesis A

`0x00e5c780` and `0x00ba9370` implement unsigned lower-bound/successor-tolerant lookup; `0x01021300` independently validates and refreshes the empire cache; star, empire, `SpaceContext`, active planet/star, and renderer objects have separate owner/lifetime boundaries.

#### Hypothesis B

A phase-specific or shared registry requires exact-find semantics, a coupled cache/root owner, or a Space/terrain presentation handoff that makes one identity authoritative across stages. Lower-bound or independent-cache assumptions would then be insufficient.

#### Required setup

- C0 plus positive Space reachability; if Space is unreachable, record a stage-reachability negative and do not synthesize stars or planets.
- Pinned probes for `0x00e5c780`, `0x00ba9370`, `0x01021300`, `0x00b3d2a0`, `0x00b25fb0`, `0x01021960`, `0x010219b0`, `0x00c8b6b0`, `0x00c8d060`, `0x00c86760`, and `0x00c86e00`.
- Record lookup key, successor/result, empire political ID, cache pointer, cache replacement/AddRef/Release, active star/planet pointer, `SpaceContext`, and graphics object identity.

#### Intervention

Use naturally approved Space navigation to select different existing stars/planets, change context where available, return/tear down the stage, and observe a cache miss/refresh or owner replacement. Do not alter map keys, caches, or pointers directly.

#### Observable outcome A

A lookup returns a successor for a non-exact key, the cache refreshes when player/political identity changes, map/cache/terrain owners teardown independently, and `SpaceContext` remains distinct from presentation objects. A supports the current lower-bound and owner-qualified contracts.

#### Observable outcome B

A lookup requires exact identity, cache results are reused across incompatible owners, star/empire roots are rebound as one graph, or terrain/graphics creation is required to interpret gameplay state. B requires a phase-specific registry and handoff model.

#### Interpretation

A does not prove the semantic meaning of every map value. B does not prove that a star root is a pointer or that graphics state owns gameplay. If no positive Space event occurs, the star/cell/terrain ownership remains unresolved.

#### Failure conditions

- Lower-bound behavior is called exact-find without a successor observation.
- A cache pointer is treated as the same identity as a star, planet, or renderer object.
- A map miss is induced by direct memory modification.
- SDK names or one predicate are used as runtime evidence.
- The Space stage is not reached but a stage claim is recorded.

#### Cleanup

Exit the approved Space observation cleanly, release the lock, teardown the process, and retain only the bounded lookup/cache/context/owner table. Do not mutate map/cache state or the shared-root decision register.

## C10 — Deferred scheduler, pause/speed, and App queue separation

**Status:** PROPOSED / UNVERIFIED. This is lower priority than the architecture blockers but high information for temporal ordering.

#### Hypothesis A

`cGameTimeManager`, `tDeferredEvent`, and `ScheduledTaskListener` form a timing/scheduling substrate with its own epoch, pause/speed conversion, due-time, duplicate, expiry, cancellation, and callback rules. It is not equivalent to App queue delivery.

#### Hypothesis B

Deferred domain records are simply App queue records, or all delayed callbacks share a single total ordering, scheduler owner, cancellation policy, and delivery contract. That coupling would change the event architecture.

#### Required setup

- C0 and a reachable stage with a naturally occurring scheduled/deferred event; no injected delay or scheduler mutation.
- Pin the identified scheduler surfaces around `0x00b3d480`, `0x00b32330`, `0x00b32390`, `0x00b321e0`, `0x00b32560`, `0x00b31da0`, and `0x00b63980`, plus the `tDeferredEvent` record and App processor events.
- Record trigger time, scheduler epoch, pause/speed state, queue placement, callback, callback-produced post, duplicate/expired/cancelled outcome, and thread ID where safely available.

#### Intervention

Observe natural pause/speed changes and a delayed callback over bounded frames. Do not force duplicate, expiry, or cancellation unless an existing approved gameplay path naturally produces it.

#### Observable outcome A

A deferred event remains separate from the App queue, has a traceable trigger/epoch and callback, and its timing changes with game-time state without inheriting App registration order. A supports a distinct scheduler interface.

#### Observable outcome B

The deferred record is delivered only through the App processor, shares its ordering/cancellation key, or callback timing follows App queue drain behavior. B requires a coupled scheduler/transport design and direct family evidence.

#### Interpretation

A does not establish fixed stepping, signed-zero behavior, or a complete scheduler owner. B must distinguish record-shape similarity from an actual cross-family ABI. No scheduler name may be assigned solely from SDK layout.

#### Failure conditions

- No naturally due deferred event is observed.
- App queue timestamp and SDK trigger time are conflated.
- Pause/speed state is inferred from a field write without a corresponding delta.
- Duplicate, expiry, or cancellation is invented from queue behavior.
- A generic frame is counted as a scheduled callback.

#### Cleanup

Stop at bounded observation completion, release the lock, teardown, and retain the timestamped timing/family table. Keep the scheduler and App queue as separate unresolved families.

## Source basis and non-promotion boundary

This selection was synthesized from:

- `knowledgegraph/research/semantic-blueprint.json:3-150,243-348,1810-1964,3008-3760,4034-4253` — blockers, chokepoints, flows, event families, and validation gates.
- `docs/analysis/architecture-decisions.md:7-112,114-170` — frozen semantic boundaries, unresolved questions, and compatibility triggers.
- `docs/analysis/future-research/01-architecture-blocker-1.md:6-48`, `02-architecture-blocker-2.md:6-48`, and `03-architecture-blocker-3.md:6-55` — architecture-changing research questions.
- `docs/analysis/future-research/01-pkg-01-shared-state-roots.md:7-40`, `02-pkg-02-app-lifecycle.md:7-39`, `03-pkg-07-cell-movement.md:7-42`, `04-pkg-10-editor-dispatch.md:7-39`, `06-pkg-12-sim-space.md:7-40`, `07-pkg-13-sim-creature-tribeciv.md:7-40`, `09-pkg-18-ui-scripting.md:7-40`, and `11-pkg-20-gameglobal.md:7-40` — package gates and required observations.
- `docs/analysis/reconstruction-packages.md:37-60,129-201,490-777,779-846,916-1088,1215-1405` — package ownership, Cell/presentation boundaries, Space/creature/terrain, UI, persistence-adjacent, and GameGlobal contracts.
- `knowledgegraph/research/track-m-oracle-plan.json:25-329,353-778` — existing runtime evidence, C-PROV/C-NEG/C-ORDER/C-STATE/C-EVENT contracts, M0-M6 proposals, and safety gates.
- `knowledgegraph/research/architecture-resolution/track-05-event.md:1-156` and `track-06-forwarded-state.md:1-119` — App transport family separation and the safe opaque forwarded-state contract.
- `docs/analysis/gameplay-state-machines.md:142-210,361-393` and `docs/analysis/gameplay-transition-map.md:83-107,171-205` — Cell lifecycle, pool/avatar ownership, persistence/resource boundaries, and mode transitions.
- `docs/analysis/event-message-map.md:38-176` and `docs/analysis/simulator-shared-state-interface.md:34-323` — family-specific dispatch, shared-root contracts, lower-bound/cache mechanics, and the explicit no-runtime-evidence boundary.
- `docs/devlog/018-s5-cell-runtime-evidence.md:10-76` — the current negative Cell runtime record and boot-stability limitation.

No statement in this file is a runtime result. No canonical KG record, tracked source file, `SPORE/` file, or executable was modified.
