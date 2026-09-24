# Gameplay Transition Map

## Purpose and ranking method

This document ranks transitions by likely gameplay impact and separates direct static mechanics from inferred phases. It is a clean-room research map derived from `knowledgegraph/research/gameplay-state-machines.json` and all 17 source artifacts in `knowledgegraph/research/state-machines/`. It is not an implementation sequence and does not propose proprietary replacement behavior.

Impact ranking uses four questions:

1. Does the transition change the active application, mode, world, or player-facing lifecycle?
2. Does it allocate, release, persist, or replace a large state graph?
3. Does it gate combat, progression, economy, or population?
4. Does it sit on a central dispatcher and therefore affect many consumers?

The rank is impact priority, not confidence. Confidence and evidence levels remain attached to every claim.

## Ranked transition inventory

| Rank | Transition family | Representative addresses | Impact reason | Evidence summary |
|---:|---|---|---|---|
| 1 | Application lifecycle and frame phase | `0x00f47ed0`, `0x00f47b10`, `0x00f47930`, `0x00f47700` | Controls whether any gameplay update runs and releases the application service graph | Startup and accessor access are OBSERVED; frame/shutdown mechanics SUPPORTED |
| 2 | App game-mode switching | `0x007d8c80`, `0x007d85b0`, `0x007d9120` | Replaces active mode services and broadcasts the global mode boundary | Concrete vtable and send order CONFIRMED; producer/queue details unresolved |
| 3 | Cell player death and stage rebuild | `0x00e7a7c0`, `0x00e7a4a0`, `0x00e72060`, `0x00e50940`, `0x00e7fd00` | Changes avatar identity, health/death state, UI, interaction, and world population | Direct Cell bodies SUPPORTED; no positive Cell trace |
| 4 | Cell object allocation and despawn | `0x00e80ba0`, `0x00e74a20`, `0x00e780a0` | Owns the 4096-slot population spine and query/GFX associations | Allocation and cleanup mechanics HIGH/SUPPORTED; sentinel and replacement policy open |
| 5 | Persistence checkpoint and load | `0x006a1540`, `0x006a2f60`, `0x00692900`, `0x00693e10`, `0x00bb4ba0`, `0x00b3d440` | Can define durable player/profile state and recovery boundaries | Local serializer mechanics SUPPORTED; whole-save transaction semantics UNRESOLVED |
| 6 | Resource/content acquisition | `0x008df460`, `0x008da3d0`, `0x00e666f0`, `0x00e55120` | Gates models, effects, cell resources, and stage presentation | Cache/fallback and preload mechanics SUPPORTED; priorities and async order UNRESOLVED |
| 7 | Editor entry, mode change, and history | `0x0058e6d0`, `0x00587a20`, `0x00587270`, `0x00586410`, `0x0058a5a0`, `0x0058a950` | Replaces editor mode, model, animation, and reversible state | Direct bodies HIGH/SUPPORTED; opaque message and manipulator contracts open |
| 8 | Space context and planet generation | `0x01021960`, `0x00bb4af0`, `0x00bb4100`, `0x00c86760` | Changes active world, persistent planet records, and presentation generation | Direct setter/guards SUPPORTED; formulas and runtime binding UNRESOLVED |
| 9 | Empire relationship and ownership | `0x00d065a0`, `0x00d038e0`, `0x00d06920`, `0x00d01e30`, `0x00c341a0`, `0x00c34ee0` | Changes diplomacy, player notifications, and star ownership | Direct flag/message mechanics CONFIRMED; score ordering partial |
| 10 | Progression, mission, and resource economy | `0x00d2e8a0`, `cMission::SetState`, `0x00596da0`, `0x0104cbd0`, `0x0103fba0` | Changes persistent progression, unlocks, inventory, tools, and economy | Direct mutators CONFIRMED/SUPPORTED; currency identity and mission body order open |
| 11 | Temporal pause/speed and scheduler | `cGameTimeManager`, `tDeferredEvent` | Alters time conversion and delayed callback behavior across all subsystems | SDK fields CONFIRMED; native pause/convert/deferred dispatch UNRESOLVED |
| 12 | Additional domain state | `0x00b21340`, `0x00aeb160`, `0x005c7d00`, `0x00845310`, `0x00571f80` | Shared registry, civ communication, palette, parser, and audio state | Mixed direct mechanics; lower confidence and broad consumers |

## 1. Application lifecycle transitions

### Bootstrap and startup

The outer application body at `0x00f48850` creates the application object, invokes initialization, conditionally invokes shutdown/cleanup, releases the object, and returns a result. The initialization body at `0x00f47ed0` constructs services, configures directories, initializes app/editor/simulator services, and gates startup on returned success flags. The precise service order and whether a named `Run` callback is reached through this body remain unresolved.

The historical positive path is bounded to main-menu startup: `InitPlugins` at `0x007e93d0`, `Init` at the conflicting `0x007e8ba0`/`0x007e6850` boundary, and `Startup` at `0x007e67a0`. This is **OBSERVED** only for the historical main-menu path. It is not evidence for menu-to-gameplay, mode transition, orderly shutdown, or save/load.

### Frame update

`kMsgAppUpdate` (`0x01ee100a`) is the central application tick. `cSporeApp::HandleMessage` at `0x00f47b10` matches the ID, enters `0x00f47930`, measures a QPC-based delta, optionally waits for pacing, calls the application `+0x78` update, an intermediate service callback, `+0x7c` (`func7Ch`), and `+0x80` (`PostUpdate`). The direct order is **SUPPORTED**. The SDK `SetFixedStepping` interface is name-only and cannot be used to claim a fixed-step accumulator.

### Stop and teardown

The stop message `0x0153c326` writes a result and clears `mIsRunning`. The teardown body at `0x00f47700` clears `mHasInitialized`, removes listeners, invokes service teardown callbacks, and releases service pointers. `App::cAppSystem::PreShutdown` at `0x007e6470` releases application resources, clears preferences/configuration, dispatches `0x0212d3e7`, and releases remaining job/configuration services. The overlap between the mode-exit message and pre-shutdown message is retained as a shared-ID ambiguity, not silently split.

### Lifecycle transition map

- **Entry**: application construction and service publication; no single complete state word is proven.
- **Normal transition**: `InitPlugins -> Init -> Startup` is the only positive historical order, limited to main menu; `kMsgAppUpdate` is statically mapped but not observed in that trace.
- **Pause/unpause**: `IAppSystem::Pause` and `Unpause` are interface surfaces; Cell dispose invokes pause/unpause paths, but the full call relation is unresolved.
- **Shutdown transition**: `PreShutdown -> Shutdown` is an SDK interface surface; the runtime shutdown path is not observed.
- **Impact boundary**: application services and frame delivery must be treated as a top-level OpenSpore boundary, not as Cell/Simulator state.

## 2. Mode-change transitions

### App registry transition

`cGameModeManager::SetActiveModeAt` at `0x007d8c80` rejects invalid indices and delegates to `0x007d85b0`. The concrete vtable at `0x01412598` establishes the activation path; the SDK-labeled body at `0x007d8d40` is a teardown body. This address conflict must remain explicit.

For a valid different index, the supported static order is:

1. Call old `IGameMode::OnExit`.
2. Write the new `mnActiveIndex` at manager `+0x28`.
3. Send mode-exit `0x0212d3e7`.
4. Call new `IGameMode::OnEnter`.
5. Send mode-enter `0x022d1adc`.

This is **CONFIRMED** for the helper’s direct order and IDs. The message payload parameter mapping, send-versus-queue timing, listener priority, and mode producer from the main menu remain **UNRESOLVED**.

### Same-index and invalid-index paths

A same-index request is a no-op according to the concrete helper. An invalid index is rejected by `0x007d8c80`. Duplicate names and removal of the active entry are not completely recovered. `SetActiveModeByName` at `0x007d8360` compares 24-byte `ModeEntry` names case-insensitively and calls the indexed activation path; the UI producer of `0x00e11333` is unresolved.

### Simulator strategy commit

`cStrategy` keeps last/current committed mode IDs and one pending first-request-wins slot. `0x00b63510` handles mode announcements and selects commit-last or commit-current behavior. The transition-effect callbacks `0x00b1db60` and `0x00b1dbd0` are separate callbacks; they are not assumed to be the writers of the mode IDs.

The recommended model is therefore two boundaries: App mode registry state and Simulator mode-commit state. The event bridge is observable; the semantic meaning of the opaque mode IDs is not.

## 3. Death, spawn, despawn, and rebuild transitions

### Spawn and allocation

`cCellGame::Initialize` at `0x00e80ba0` resets Cell state, initializes a 4096-entry main pool, sets timing, loads world references, and enters the stage rebuild path. `CreateCellObject` at `0x00e74a20` allocates a pooled object and initializes position, orientation, size, model, resource, scale, query, effect, health, and identity state. A free-list slot becomes a live cell when allocation succeeds.

The high-impact guard is free-slot availability. The exact generic pool entry, invalid-index sentinel, and exhaustion result remain unresolved; the original index-zero lookup rejection is not silently converted into a complete ABI.

### Damage and death

`ShouldNotAttack` at `0x00e57460` is the attack guard. `GetDamageAmount` at `0x00e58980` selects damage. The generic resolver `0x00e7a7c0` subtracts damage, clamps health at zero, may show a health rollover, and enters the death path at zero. The non-player path at `0x00e7a4a0` marks `cCellObjectData+0x113`, selects effects, updates nearby flee/chase reactions, and queues a duration-bearing action. The player path diverts to `0x00e72060`.

Player death sets UI/cinematic state, stores a pending interaction at `sCellGame+0x5194`, and changes the avatar action field. The subsequent rebuild is deferred, not necessarily immediate.

### Despawn

`FUN_00e780a0` clears a matching avatar reference, removes query/GFX/association state, may create a scale replacement, and releases the old object. It is a single teardown boundary reached from death, eat, interaction, replacement, and scale-related callers. Caller-specific reason and replacement policy are not uniform in the evidence.

### Rebuild

A reload request writes `sCellGame+0x51d8` and optionally `+0x51d9`. The next active frame in `0x00e806b0` observes the request and calls `0x00e7fd00`, which drains Cell/UI/effect state, clears the avatar, reloads world and UI references, resets scale/advection state, and invokes population/setup helpers. The exact player-object construction subpath and runtime callback ownership remain unresolved.

### Transition impact

These transitions should remain separated in a clean-room design: pool lifecycle, avatar lifecycle, damage/death, and stage rebuild. A single “alive/dead” flag would lose query, GFX, health, interaction, and scale-replacement evidence.

## 4. Editor transitions

### Entry and exit

`cEditor::Initialize` at `0x00584300` builds editor services but does not mark the editor active. `OnEnter` at `0x0058e6d0` checks the shadow world, requests PaintMode, and writes `cEditor+0x2b0` near successful completion. `OnExit` at `0x00587a20` clears the active flag, requests PaintMode, and releases selection, manipulator, model, skin, palette, PlayMode, animation, and world support. `Dispose` at `0x00576c50` conditionally calls `OnExit`, removes command/listener state, and releases the editor graph.

The Build/Paint/Play enum is **CONFIRMED_NAME_ONLY** at `cEditor+0x31c`; direct mode writes and guards are **CONFIRMED/SUPPORTED**. Full failure and ownership paths are open.

### Mode changes

`SetActiveMode` at `0x00587270` rejects the current Build-to-Build request, checks a secondary state guard, tears down old mode-specific state, writes the requested enum, performs mode-specific entry, and may emit an animation event. The EditorUI mode updater at `0x005dda30` suppresses equal requests before calling it. The UI command dispatcher at `0x005e0000` routes opaque controls to PlayMode, mode changes, Undo, and Redo.

### Input and history

Mouse and key callbacks write editor state and route by mode. `OnMouseDown` at `0x00588570` rejects overlapping manipulator transactions, handles Paint/Play branches, performs Build hit testing, and stores a manipulator. `OnMouseMove` at `0x005737d0` updates an existing manipulator. `OnMouseUp` at `0x0058b650` checks the stored button, finalizes the manipulator, conditionally commits history, and may call Undo.

`CommitEditHistory` at `0x00586410` appends paired state/resource records and increments the history index. `Undo` and `Redo` guard the index and restore the model through `SetEditorModel`. The history contract is direct and strong; the exact opaque manipulator classes and redo-tail truncation helper semantics remain open.

### Animation world

`cEditorAnimWorld::DestroyCreature` at `0x0059c6e0` checks the map and sentinel, dispatches controller teardown, releases the controller, and erases the map entry. Creation bodies at `0x0059c830` and `0x0059c9c0` allocate controllers and insert/retrieve map entries. `cEditorAnimEvent::MessageSend` and `MessagePost` carry model/event/scalar data, but the final animation consumer and queue timing are unresolved.

## 5. Empire and space transitions

### Relationship transitions

The political state is represented by relationship flags, not by relationship score. `DeclareWar` sets bit 0 and clears bit 1; `DeclarePeace` clears bit 0; `DeclareAlliance` first calls peace and then sets bit 1; `BreakAlliance` clears bit 1. Player-involved alliance and lost-alliance paths emit `0x04445d43` and `0x04445d44` respectively. `ApplyRelationship` changes score/event data but does not directly set those political bits.

The high-risk ambiguity is that some SDK or artifact records describe alliance/war as a relationship while other direct bodies use bit operations. The direct bit operations should remain authoritative for the binary mechanics; semantic labels are retained only where SDK names and matching fields support them.

### Star ownership

`cEmpire` star membership add/remove bodies at `0x00c341a0` and `0x00c34ee0` update `mStars`, set the empire flag, emit `0x55bd8f7`, and may update home-star/home-planet state. `CaptureSystem-associated` body at `0x00c8d060` scans loaded systems/planets, rejects inconsistent ownership candidates, and dispatches UI, mission, destruction, and ownership paths. The exact SDK prototype and all ownership write ordering remain unresolved.

### Space context

`SpaceContext` is a direct enum-backed state at `sSpacePlayerData+0x10`: None `-1`, Planet `0`, SolarSystem `1`, Galaxy `2`. The setter at `0x01021960` stores the value and conditionally runs a Galaxy follow-up. `0x010219b0` binds/replaces active star/planet pointers. The first activation body at `0x01022580` may create a temporary star and force Planet. The setter mechanics are **SUPPORTED**; the complete world switch and transition UI are **UNRESOLVED**.

### Planet generation

When `cStarRecord+0xac` is zero and timing permits, `0x00bb4af0` records observed time, removes pending state, resets manager state, and calls generation. `0x00bb4100` creates/initializes `cPlanetRecord` objects and increments the count. `RecordToPlanet` at `0x00bb5b50` is the SDK-confirmed conversion boundary from persistent record to runtime planet. `0x00c8b700` lazily allocates a `cSolarSystem`, `0x00c86760` loads its data, and `0x00c86e00` dispatches graphics create/destroy.

These are separate transitions: persistent record generation, runtime materialization, and graphics generation. No one state variable should own all three.

## 6. Progression and economy transitions

### Evolution

`SetEvolutionPoints` at `0x00d2e480` is a direct assignment. `AddEvolutionPoints` at `0x00d2e8a0` ignores zero, caps the primary store, updates goal progress with the requested amount, and may dispatch creature strategy action `0x45ab96e`. It does not directly set current brain level in the recovered body. The threshold accessor `0x00d2e380` maps levels 0 through 3 to four globals; all other levels return zero. Brain-level promotion and threshold semantics are unresolved.

### Missions

`cMission::SetState` is the central SDK-named state writer at `cMission+0x84`. The documented states are Unaccepted, Finished, Accepted, Active, Completed, Failed, Aborted, Rejected, and StepCompleted. Acceptance calls `OnMissionAccept` and enters Active; completion calls `OnMissionCompleted`; failure, abort, and rejection call their respective callbacks before terminal routing. Active entry emits `kMsgMissionUpdate`. The exact native body, callback order, mission-type overrides, and reward ordering are unresolved.

### Collectables and tools

`UnlockPart` at `0x00596da0` performs the direct collectable point debit, status-bit update, and list update. `LockPart` at `0x00596e10` clears status without a visible refund. `AddAmmo` and `ConsumeAmmo` at `0x0104cbd0` and `0x0104cc00` are direct reserve mutators with asymmetrical bounds. These are not proven to be a universal currency or a connection to `cEmpire.mEmpireMoney`.

### Rare discoveries and relationships

`SetRareAsFound` at `0x0103fba0` changes the rare map and emits `0x06779f04` only on first discovery. `ObtainTradingObject` is a supported inventory/rare boundary but its exact order is unresolved. Relationship score effects at `0x00d06270` are separate from political flags and must not be named as money.

## 7. Save/load transitions

### Local property transfer

`PropertyList::Write` and `Read` at `0x006a1540` and `0x006a2f60` are bounded local-entry stream operations. The first failed helper operation short-circuits. This supports local property transfer semantics, not a complete save transaction.

### ClassSerializer transfer

The serializer metadata constructor around `0x00692880`/`0x00692f90` initializes object and attribute metadata. `0x00692900` writes class/stream framing and invokes attribute callbacks. `0x00693e10` reads framing, validates object count, resolves object identities, invokes callbacks, and checks stream state. Imported SDK labels inside these containing bodies are not treated as exact standalone methods.

### Database and profile checkpoints

`0x00bb4ba0` writes temporary star/planet database state and replaces `stars.db`; `0x00b282e0` and `0x00b28750` probe profile files and validity markers. `0x00b28ec0` and `0x00b294c0` provide coarse save/load/profile orchestration. `0x00b3d440` is only the persistence service accessor; the SDK `LoadGame` surface at `+0x10` does not establish file order or failure semantics.

### Application and Cell interaction with persistence

`PreShutdown` dispatches `0x0212d3e7`; the achievement manager has a listener branch that mutates achievement state but does not prove a database write. Cell exit/dispose bodies release mode state without a visible serializer write. The Cell serializable handoff at `0x00e63d10`, `0x00e819b0`, and `0x00e80ba0` is an in-process pointer handoff, not evidence of a disk round trip.

The major unresolved save/load questions are whole-save ordering, object identity encoding, version/rollback/atomicity, parent property ownership, mode restoration, and whether Cell mode exit automatically saves.

## 8. Resource and content transitions

### Manager registry

`Resource::cResourceManager::Initialize` at `0x008de530` constructs lookup storage. SDK registration surfaces add/remove databases, factories, and caches. A successful request needs the correct registry state, but exact database priority and duplicate behavior are not recovered.

### Cache, database, and factory path

`GetResource` is SDK-anchored at `0x008df700`, with the live body around `0x008df460`. The body probes a cache-like path before database/factory fallback. `DatabasePackedFile::OpenRecord` around `0x008da3d0` resolves the full `(type, group, instance)` identity and returns a record lease. `CloseRecord` is coupled to record/reference bookkeeping.

`GetPrivateResource` is SDK-confirmed as cache-bypassing. `GetResourceAsync` exposes an `IAsyncRequest` with `IsReady` and `GetResource`, but scheduling, cancellation, and polling order are unresolved. `ReloadResource` and `FlushCache` are first-class interface operations, but replacement/eviction and reference-release timing are unresolved.

### Cell preload and display

`cCellGFX::PreloadResources` around `0x00e666f0` recursively traverses Cell/populate resources and preload helpers. `AddPreloadedModel`, `AddPreloadedEffect`, `AddPreloadedTexture`, and `PreloadCreature` retain content handles under helper-specific rules. `StartDisplay` at `0x00e55120` activates lighting, world/layer, shadow/effect, and audio presentation. The exact relationship between preload completion and display start is static/contract evidence, not runtime-observed.

The current OpenSpore resource provider only establishes a clean-room byte-fetch contract. It does not reproduce the original manager registry, async request, cache, factory, or database lifecycle.

## 9. Unresolved transitions and evidence gaps

The following transitions must remain explicitly unresolved:

- Main-menu producer to the first gameplay mode request, including the producer of `0x00e11333`.
- Exact `SetActiveModeAt` identity at stale SDK address `0x007d8d40` versus concrete activation body `0x007d8c80`.
- Message queue timing, priority direction, tie order, consume semantics, listener removal, and lock rules.
- Full `StandardMessage` parameter mapping for mission, combat, relationship, tool, noun, scenario, and rare records.
- `CombatantKilledMessage` producer and its relationship to the generic Cell death path.
- Exact death/effect duration, queued interaction record schemas, and all raw type values in `FUN_00e7e130`.
- Original cell free-list sentinel, index-zero lookup domain, pool exhaustion result, and replacement ordering.
- Player assignment during stage rebuild and the exact cinematic-to-rebuild callback chain.
- Native `cGameTimeManager::Pause`, `Resume`, `Toggle`, `SetSpeed`, and `ConvertDeltaTime` bodies.
- `tDeferredEvent` scheduler owner, epoch, ordering, duplicate, expiry, and callback.
- Editor hash payload schemas, semantic names for opaque UI branches, manipulator class identities, and redo-tail truncation.
- Mission native `SetState` body, reward order, money backing field, and mission-type overrides.
- `cTribePlanner`, tribe population, herd respawn/evolution, and NPC growth native transition bodies.
- Galaxy/planet generation formulas, `RecordToPlanet` materialization internals, and complete ownership update order.
- Camera setter receiver identity and camera removal behavior; the getter mechanics at `0x007c61a0` are stronger than the setter evidence.
- Resource database priority, async scheduling, cache eviction, reload semantics, factory/database order, and exact QFS call site.
- Whole-save framing, version negotiation, rollback, crash consistency, and object identity encoding.
- Runtime reachability for all gameplay transitions. The positive runtime corpus is limited to bounded application startup/service access.

## Recommended OpenSpore subsystem boundaries

These are explicit clean-room research boundaries, not a claim that the original binary can be copied structurally:

1. **Application lifecycle and frame clock**: own service publication, startup/shutdown phases, app-update delivery, QPC/pacing observations, and post-update ordering.
2. **Mode orchestration**: own registered modes, active index, validated activation, and explicit transition announcements. Keep Simulator mode commit as a separate consumer.
3. **Message and UI dispatch**: keep App message-manager records separate from UTFWin messages, Cell interaction records, deferred records, and serializable domain records. Preserve raw IDs and payload opacity where evidence is incomplete.
4. **Cell population and avatar lifecycle**: separate pool allocation, object despawn, avatar identity, damage/death, interaction queue, and stage rebuild.
5. **Combat and reaction policy**: own attack eligibility, damage arithmetic, health, death, flee/chase targets, and UI rollover requests. Do not infer generic creature death from Cell death without a path.
6. **Editor state and history**: separate editor mode, model/selection/manipulator state, edit-history cursor, animation-world membership, and UI/message dispatch.
7. **Space/world persistence**: separate active `SpaceContext`, persistent star/planet records, runtime solar-system materialization, and graphics presentation.
8. **Empire and diplomacy**: separate relationship score/events, war/alliance flags, star ownership, and player-facing relationship messages.
9. **Progression and economy**: separate evolution points, mission state/rewards, collectable points, inventory, ammunition, rare discovery, and relationship score. Do not collapse them into a generic money store.
10. **Persistence and content I/O**: separate profile/save orchestration, serializer attribute callbacks, database/file checkpoints, resource manager registries, record leases, cache policy, and async requests.

These boundaries preserve the evidence distinctions in the merged JSON and prevent a generic event bus, generic alive flag, generic economy balance, or generic resource cache from absorbing behavior that the original artifacts only show as separate contracts.

## Final Campaign Report

The ten requested campaign areas are consolidated below. Each item states the strongest supported transition surface, the evidence boundary, and the clean-room boundary that follows from it.

1. **Lifecycle**: application bootstrap, startup, `kMsgAppUpdate`, stop, and teardown are centered on `cSporeApp` fields and `0x00f47b10`/`0x00f47930`/`0x00f47700`. Startup order is **OBSERVED** only in the bounded main-menu path; frame and teardown mechanics are **SUPPORTED** static evidence.
2. **Mode changes**: `cGameModeManager` at `0x007d85b0` has a concrete old-exit, index-write, mode-exit message, new-enter, mode-enter order. Simulator mode commit is a separate bridge at `0x00b63510`; UI producers and queue timing remain **UNRESOLVED**.
3. **Death, spawn, and despawn**: Cell pool allocation at `0x00e74a20`, health/death at `0x00e7a7c0`/`0x00e7a4a0`, despawn at `0x00e780a0`, and rebuild at `0x00e7fd00` are direct static surfaces. They are **SUPPORTED**, not runtime-verified, and should not be collapsed into one boolean.
4. **Editor**: editor initialization/entry/exit, Build/Paint/Play changes, manipulator input, history commit/undo/redo, and animation-world destruction are directly decomposed. Opaque message hashes and manipulator identities remain bounded **UNRESOLVED**.
5. **Empire and world**: relationship flags, star membership, `SpaceContext`, planet-record generation, solar-system loading, and graphics requests are separate transitions. Flag writes and context stores are strong static evidence; formulas, ownership order, and runtime navigation remain **SUPPORTED / UNRESOLVED**.
6. **Progression and economy**: evolution-point arithmetic, mission states/rewards, collectable unlocks, ammunition, rare discovery, badges, and relationship effects have distinct state variables. Direct mutators are **CONFIRMED/SUPPORTED**; universal currency identity and full mission/economy ordering are **UNRESOLVED**.
7. **Save/load**: property and class-serializer callbacks, `stars.db` replacement, profile probes, persistence service access, and the SDK `LoadGame` contract are documented. Local mechanics are **SUPPORTED**; whole-save atomicity, rollback, version negotiation, and runtime round trips are **UNRESOLVED**.
8. **Resources and content**: manager registry, cache hit/miss, database record identity, async requests, Cell preload, effect lifecycle, and display activation are mapped. The resource seam is **SUPPORTED** at the static interface/body level; priority, eviction, async, and QFS details are **UNRESOLVED**.
9. **Events and dispatchers**: the App message manager, App game-mode manager, `cSporeApp` handler, Simulator mode listener, input manager, UTFWin window, editor handlers, EditorUI dispatchers, civ communication, star/world, persistence, resource, and Cell queue dispatchers are the central boundaries recorded in the merged JSON. Producer/consumer gaps are retained rather than filled by inference.
10. **OpenSpore boundaries and validation**: retain separate lifecycle, mode, message, Cell population, combat, editor, world, diplomacy, progression/economy, persistence, and resource/content subsystems. The next evidence gate is a hash-pinned trace that reaches gameplay and records mode, message, state-field, save/load, and world transitions without modifying `SPORE/`, historical triage, or JSON artifacts.

This report is a clean-room transition map. It preserves **SDK-name-only**, **decompilation**, **disassembly**, and **runtime** distinctions and does not claim implementation fidelity or runtime verification where the corpus contains only structural or static evidence.
