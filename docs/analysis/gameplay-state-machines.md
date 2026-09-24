# Gameplay State Machines

## Scope and evidence policy

This document is clean-room research documentation, not an implementation plan. It describes the state and lifecycle evidence merged in `knowledgegraph/research/gameplay-state-machines.json` and the 17 source artifacts under `knowledgegraph/research/state-machines/`.

The pinned original is `SPORE/SporeBin/SporeApp.exe`, build `3.1.0.22`, SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`, x86:LE:32:windows, image base `0x00400000`. The binary has no MSVC RTTI. Vtable and SDK relationships are therefore structural evidence unless a concrete body or call path corroborates them.

The evidence labels used below retain the source vocabulary:

- **CONFIRMED**: direct control/data flow, a concrete body, a vtable data read, or a structure field corroborated by instructions.
- **SUPPORTED**: direct static evidence with a boundary, type, or semantic gap.
- **CONFIRMED_NAME_ONLY**: an SDK name, enum, field, or vtable slot establishes interface shape but not an original behavior.
- **INFERRED**: a bounded control-flow interpretation, not a direct original state assignment.
- **OBSERVED**: positive original-process evidence. The corpus only provides positive observations for application startup and service access; it does not provide a positive Cell, empire, editor, progression, persistence, or world-transition trace.
- **UNKNOWN / UNRESOLVED / APPROXIMATION**: explicitly retained gaps or clean-room comparisons, never promoted to original behavior.

Decompilation and disassembly are evidence for instructions, guards, calls, and memory operations; decompiler parameters and comments are not authoritative. SDK-name-only claims are not used to invent writers or transition order. Current OpenSpore source is not used as original-game evidence.

## Corpus and reconciliation

The merged JSON reconciles duplicate callback records through its `provenance.source_records`; the source artifacts are:

- `additional-domains.json`
- `app-lifecycle.json`
- `cell-stage.json`
- `combat.json`
- `creature-civilization.json`
- `editor-workflows.json`
- `economy.json`
- `empire-space.json`
- `global-events.json`
- `persistence.json`
- `progression.json`
- `resource-content.json`
- `simulator-core.json`
- `spawning-population.json`
- `temporal-semantics.json`
- `ui-gameplay.json`
- `world-planet.json`

The merged file is the primary index for callback provenance and duplicate-record reconciliation. The source artifacts remain the detailed evidence records. The high-impact central dispatchers found across them are `App::cMessageManager`, `App::cGameModeManager`, `App::cSporeApp::HandleMessage`, the Simulator mode listener, `Simulator::cGameInputManager`, `UTFWin::Window`, `Editors::cEditor::HandleMessage`, the EditorUI message dispatchers, `Simulator::cCommManager`, `Simulator::cStarManager`, `Simulator::cGamePersistenceManager`, `Resource::cResourceManager`, and the Cell queued-interaction dispatcher. Their contracts are expanded in `docs/analysis/event-message-map.md`.

## Runtime and application lifecycle

### `spore_app_runtime`

- **State variable**: `App::cSporeApp+0x0c` (`mHasInitialized`) and `+0x0d` (`mIsRunning`). The fields are SDK-confirmed; the static body supplies the observed writes.
- **States**:
  - `uninitialized_or_tearing_down`: `mHasInitialized == 0`; the frame handler does not dispatch normal frame work.
  - `initialized_frame_listener`: `mHasInitialized != 0`; the application listener can enter the frame body.
  - `running`: initialization and startup succeeded; `mIsRunning != 0` and `kMsgAppUpdate` is accepted.
  - `stop_requested`: message `0x0153c326` writes a result and clears `mIsRunning`.
  - `shutdown`: teardown clears initialization, removes listeners, and releases services.
- **Transitions, guards, actions**:
  - Startup sets running state and registers the application listener for `kMsgAppUpdate`; initialization checks must pass.
  - `kMsgAppUpdate` remains a self-transition when initialized; the frame body is called once per accepted message.
  - Stop message `0x0153c326` writes the result and clears `mIsRunning`.
  - Shutdown clears `mHasInitialized`, removes listeners, and releases service pointers.
- **Events**: `app_bootstrap_entry`, `app_plugins_initialized`, `app_system_init`, `app_system_startup`, `app_update`, stop message `0x0153c326`, shutdown.
- **Consumers**: `cSporeApp::HandleMessage` at `0x00f47b10`, application service callbacks, `IAppSystem::Update`, `IAppSystem::func7Ch`, `IAppSystem::PostUpdate`.
- **Structures**: `App::cSporeApp`, `App::IAppSystem`, `App::cAppSystem`.
- **Functions**: `0x00f47ed0`, `0x00f47930`, `0x00f47b10`, `0x00f47700`, `0x00f48850`.
- **Evidence**: `0x00f47f1a` sets `mIsRunning`; `0x00f4827e-0x00f48286` registers the app-update listener; `0x00f47b9b-0x00f47bae` handles the stop ID; `0x00f47700-0x00f47922` is teardown. Sources: `temporal-semantics.json`, `app-lifecycle.json`, `persistence.json`, and `SPORE/SporeBin/SporeApp.exe` read-only disassembly.
- **Confidence**: **SUPPORTED** for the static lifecycle body; **OBSERVED** only for the bounded main-menu startup/access path in `tools/observatory/examples/obs_main_menu_example.jsonl`.
- **Validation**: instrument the two flags and listener registration through startup, an app-update message, stop, and teardown; byte-verify the frame and teardown entry boundaries.

### `app_update_dispatch`

- **State variable**: the frame body’s transient integer delta and timing baseline at `cSporeApp+0x10/+0x14`; conversion fields at `+0x18/+0x1c`.
- **States**: message received, delta measured, optional pacing wait, updated, post-updated.
- **Transitions, guards, actions**: message ID `0x01ee100a` enters the frame body. A positive pacing target below the current delta can enter a wait path. The body then calls the application `+0x78` update callback with an integer millisecond delta, an intermediate service callback, `+0x7c` (`func7Ch`), and finally `+0x80` (`PostUpdate`).
- **Events**: `kMsgAppUpdate` / `app_update`.
- **Consumers**: `cSporeApp::HandleMessage`, `IAppSystem` update slots, scheduled-task and update-message listener adapters.
- **Structures**: `App::cSporeApp`, `App::IAppSystem`, `MessageListenerData`, update and scheduled listener adapters.
- **Functions**: `0x00f47b10`, `0x00f47930`; the mode and message infrastructure is in `global-events.json`.
- **Evidence**: disassembly at `0x00f47b20-0x00f47bca`, `0x00f47948-0x00f47a14`, and the SDK names `Update`, `func7Ch`, and `PostUpdate` in `cAppSystem.h`. The SDK `SetFixedStepping` slot is **CONFIRMED_NAME_ONLY** and is not connected to the observed pacing path.
- **Confidence**: **SUPPORTED** for direct call order; **UNKNOWN** for fixed-step accumulator semantics.
- **Validation**: record one update message, QPC delta, pacing decision, and each callback entry/exit; do not infer a fixed-step accumulator from the fields alone.

## Game-mode registry and Simulator routing

### `app_game_mode_activation`

- **State variable**: `App::cGameModeManager+0x28` (`mnActiveIndex`) over the `ModeEntry` vector at `+0x14`; initialization flag at `+0x10`.
- **States**:
  - `manager_uninitialized_or_disposed`: initialization flag false.
  - `no_active_mode`: initialized, no active index.
  - `active_mode_index`: `0 <= mnActiveIndex < mode_count`.
- **Transitions, guards, actions**:
  - `Initialize` at `0x007d8060` creates camera state, installs an ID helper, and registers messages `0x00d3c602`, `0x00e11332`, and `0x00e11333`.
  - `SetActiveModeAt` at `0x007d8c80` range-checks the requested index and delegates to `0x007d85b0`.
  - A same-index request is a no-op.
  - A different valid request calls old `OnExit`, writes the active index, sends `0x0212d3e7`, calls new `OnEnter`, and sends `0x022d1adc`.
  - `Dispose` at `0x007d9120` unregisters messages, exits the active mode, disposes registered modes, clears entries, and sets the index to `-1`.
- **Events**: `mode_set_by_name`, `mode_exit_announcement`, `mode_enter_announcement`, manager initialization and disposal.
- **Consumers**: `IGameModeManager`, `IGameMode` lifecycle slots, Simulator strategy commit listener, transition-effect callbacks, camera/viewer consumers.
- **Structures**: `App::cGameModeManager`, `ModeEntry`, `App::IGameMode`, `App::IGameModeManager`.
- **Functions**: `0x007d8060`, `0x007d8230`, `0x007d8360`, `0x007d8c80`, `0x007d85b0`, `0x007d9120`, `0x007d9320`; concrete vtable data at `0x01412598`.
- **Evidence**: live vtable/disassembly in `ui-gameplay.json`; the SDK-labeled `0x007d8d40` body is a teardown body and is not silently merged with `0x007d8c80`.
- **Confidence**: **CONFIRMED** for the concrete vtable, range guard, helper order, and send IDs; **SUPPORTED** for lifecycle consequences; duplicate names, active-entry removal, and listener priority remain unresolved.
- **Validation**: record the index, mode ID/name, `OnExit`, active-index write, message sends, and `OnEnter` for same, invalid, no-active, and distinct-index cases.

### `simulator_strategy_mode_routing`

- **State variable**: `cStrategy+0x18` request path and `cStrategy+0x14` pending opaque mode ID; committed IDs are at `+0x0c` and `+0x10`.
- **States**: no pending request, pending path 1, pending path 2, and the committed last/current pair.
- **Transitions, guards, actions**:
  - Constructor writes `-1` to committed and pending IDs and `0` to request path.
  - Request helpers at `0x00b5b880` and `0x00b5b8a0` set paths 1 or 2; the first pending ID wins.
  - Commit-last at `0x00b5b8c0` copies the pending ID to `mLastGameMode`, clears the pending ID, and returns to path 0.
  - Commit-current at `0x00b5b8e0` performs the corresponding write to `mCurrentGameMode`.
  - The listener at `0x00b63510` handles both mode messages, reads payload words at `+0x08/+0x10`, normalizes them, and selects the commit behavior.
- **Events**: `strategy_mode_request`, `strategy_mode_last_committed`, `strategy_mode_current_committed`, `mode_exit_announcement`, `mode_enter_announcement`.
- **Consumers**: `Simulator::cGameModeManager`, `cGameInputManager`, other `cStrategy`-derived managers, transition-effect callbacks.
- **Structures**: `Simulator::cStrategy`, `ISimulatorStrategy`, `Simulator::cGameModeManager`.
- **Functions**: `0x00b5b840`, `0x00b5b880`, `0x00b5b8a0`, `0x00b5b8c0`, `0x00b5b8e0`, `0x00b5b960`, `0x00b1db60`, `0x00b1dbd0`, `0x00b63510`.
- **Evidence**: read-only disassembly in `simulator-core.json`; `ISimulatorStrategy` slot names are SDK-confirmed, but the opaque game-mode ID domain is not.
- **Confidence**: **CONFIRMED** for the three-state request/commit mechanics; **UNKNOWN** for the semantic identity of each mode ID and the exact relationship between the transition callback and commit listener.
- **Validation**: trace simultaneous/repeated requests, both message paths, and the first-request-wins guard.

## Temporal control

### `game_time_pause_and_speed`

- **State variable**: `Simulator::cGameTimeManager` fields at `+0x30..+0x7b`: base time, frame-start time, speed factors, current speed, speed index, flags, pause maps, and pause-type counters.
- **States**: unpaused, game-paused, effects-paused, audio-paused, and speed-scaled/frame-sample. These are phase projections, not a single original enum.
- **Transitions, guards, actions**:
  - `Pause` / `Toggle` requests change pause collections and effective pause count; exact native pause body is missing.
  - Resume-like removal changes the effective pause count.
  - `SetSpeed` selects a speed factor/index.
  - `ConvertDeltaTime` is SDK-documented to return zero while game time is paused and otherwise multiply elapsed time by current speed; the original body is not safely mapped.
  - The frame boundary samples the frame timestamp and feeds the Simulator update.
- **Events**: `game_time_pause_changed`, `game_time_speed_changed`, `app_update`, `scheduled_callback_due`.
- **Consumers**: `cGameTimeManager::Get`, `ConvertDeltaTime`, `GetPauseCount`, `Toggle`, game-speed UI, scheduled-task adapter.
- **Structures**: `Simulator::cGameTimeManager`, `PauseType`, `TimeManagerPause`.
- **Functions**: `0x00b3d480`, `0x00b32330`, `0x00b32390`, `0x00b321e0`, `0x00b32560`, `0x00b31da0`, `0x00b63980`.
- **Evidence**: SDK fields in `structs_fields.tsv` are **CONFIRMED**; direct pause/speed/convert bodies are not in the committed set. `temporal-semantics.json` records the address conflict for `ConvertDeltaTime`.
- **Confidence**: **MEDIUM / UNRESOLVED** for transition mechanics; high confidence only that the interface and fields exist.
- **Validation**: recover all pause and speed functions together, then trace nested pauses, mismatched pause keys, and every speed index against actual deltas.

## Cell stage

### `cell_mode_lifecycle`

- **State variable**: mode lifecycle flags and the `sCellGame`, `sCellGFX`, and `sCellUI` service pointers.
- **States**: uninitialized, initialized, active, exited, disposed.
- **Transitions, guards, actions**: `Initialize` at `0x00e81cf0` constructs the Cell service globals; `OnEnter` at `0x00e552f0` resets flags, starts Cell GFX display, and invokes gameplay/UI setup; `Update` at `0x00e80980` forwards the first delta to `0x00e806b0`; `OnExit` at `0x00e7fc00` flushes pending work and releases active state; `Dispose` at `0x00e81f30` releases Cell services and changes pause state.
- **Events**: `cell_mode_initialized`, `cell_mode_entered`, `cell_update`, `cell_mode_exited`, `cell_mode_disposed`.
- **Consumers**: active `IGameMode` update/input dispatch, Cell GFX/UI, stage population helpers, app pause/unpause.
- **Structures**: `App::cCellModeStrategy`, `cCellGame`, `cCellGFX`, `cCellUI`.
- **Evidence**: decompilation paths listed above; no positive Cell runtime trace.
- **Confidence**: **SUPPORTED** for static lifecycle; **UNRESOLVED** for runtime order and exact ownership of indirect services.
- **Validation**: trace all five callbacks and the three service pointers through a real mode entry; verify whether mode exit saves state.

### `cell_object_pool_lifecycle`

- **State variable**: `cCellGame+0x1c` main pool, pool counters at `+0x04/+0x0c/+0x10`, and the dual-purpose first word at `cCellObjectData+0x00`.
- **States**: free, allocated/live, dying, despawning, and rebuild-releasing.
- **Transitions, guards, actions**:
  - `CreateCellObject` at `0x00e74a20` pops a free slot, writes the slot’s own index, and initializes transform, size, model, resource, query, effect, and health state.
  - `FUN_00e780a0` clears a matching avatar reference, query/GFX/association state, may create a scale replacement, and returns the old slot to the pool.
  - The free-list sentinel and exact generic pool address remain unresolved; index-zero rejection is reported but not promoted to a complete ABI.
- **Events**: `cell_object_allocated`, `cell_object_despawned`, `cell_stage_reload_requested`.
- **Consumers**: pool lookup/release, query and GFX systems, population, death/eat/replacement callers, stage rebuild.
- **Structures**: `cObjectPool<cCellObjectData>`, `cCellObjectData`, `cCellGame`, `cCellQueryLinkedPool`.
- **Evidence**: `cCellGame::Initialize` and `CreateCellObject` decompilation, `cell-object-pool-lifecycle.md`, and `cell-stage.json`.
- **Confidence**: **HIGH** for allocation/cleanup mechanics; **UNRESOLVED** for the original free-list sentinel and pool-exhaustion result.
- **Validation**: byte-verify pool initialization, lookup domain, and free-list writes; trace all `0x00e780a0` callers and forced exhaustion.

### `cell_player_lifecycle`

- **State variable**: `sCellGame+0x411c` avatar pool index, `cCellObjectData+0x113` terminal/death state, and `sCellGame+0x51d8` reload request.
- **States**: absent, active, dying/cinematic, and stage-rebuild-pending.
- **Transitions, guards, actions**:
  - Population or rebuild assigns the avatar index and makes the player available to movement, AI, combat, query, and UI consumers.
  - Lethal player damage diverts to `0x00e72060`, which marks the terminal state, queues action/effect/UI state, and stores pending interaction at `sCellGame+0x5194`.
  - `0x00e50940` and `0x00e72200` set the deferred reload fields; `0x00e806b0` observes them on an active frame and calls `0x00e7fd00`.
  - `0x00e7fd00` drains Cell/UI/effect state, clears the avatar, reloads world/UI/scale data, and calls population/setup helpers.
  - Despawn outside normal rebuild can clear the avatar index directly.
- **Events**: `cell_death_started`, `cell_stage_reload_requested`, `cell_object_despawned`, `cell_mouse_steering_sample`.
- **Consumers**: player movement, `FUN_00e5b2e0`, `FUN_00e73f60`, per-cell iteration, stage rebuild.
- **Structures**: `cCellGame`, `cCellObjectData`, `cCellSerializableData`, `cCellUI`, `cCellUIRollover`.
- **Evidence**: `cell-stage.json` lines covering the state field, player death, reload request, frame observation, and despawn.
- **Confidence**: **HIGH** for the composite static mechanics; exact player construction subpath is unresolved.
- **Validation**: trace avatar index and death/rebuild fields through lethal interaction and a scale transition.

### `cell_health_damage_death` and `cell_attack_guard`

- **State variables**: `cCellObjectData+0x244` health, `+0x111` invulnerability, `+0x113` death flag, target slots at `+0xe0/+0x194/+0x248`, flee/chase timers at `+0x21c/+0x220/+0x22c/+0x230`.
- **States**: attack permitted/suppressed, health positive, health zero, death marked, flee timer active, chase timer active, target unresolved.
- **Transitions, guards, actions**: `ShouldNotAttack` at `0x00e57460` gates the resolver; `GetDamageAmount` at `0x00e58980` supplies damage; `0x00e7a7c0` subtracts, clamps at zero, optionally shows a rollover, and enters `0x00e7a4a0`; the death path marks non-player cells, selects effects, updates nearby reactions, and queues an action, or diverts player death to `0x00e72060`.
- **Events**: `cell_attack_guard_decision`, `cell_damage_resolved`, `cell_death_transition`, `cell_target_selection`, `cell_target_reaction_update`, `cell_health_rollover_shown`.
- **Consumers**: collision/ingestion paths, `cCellUI::ShowHealthRollover`, queued interaction dispatcher, AI behavior update.
- **Structures**: `cCellObjectData`, `cCellUI`, `cCellUIRollover`, `cCellCellResource`/`cAIData`.
- **Evidence**: direct decompilation and disassembly in `combat.json` and `cell-stage.json`; no combat runtime trace.
- **Confidence**: **HIGH** for health zero/death branching; **MEDIUM** for target selector semantics and reaction transitions.
- **Validation**: trace damage values, invulnerability, health writes, death flag, effects, and flee/chase fields for each attack class.

### `cell_queued_interactions` and `swarm_effect_lifecycle`

- **State variable**: queued record type at `+0x24`; effect world state at `cEffectsWorld+0x20`; per-effect running/paused/hidden flags.
- **States**: interaction queued, interaction dispatched/released, effect uninstantiated, created, running, paused/hidden, stopped, released.
- **Transitions, guards, actions**: `FUN_00e7e130` switches on record types `1, 2, 5, 6, 7, 0x0c, 0x0d, 0x13, 0x14, 0x1d, 0x1e, 0x2c, 0x32, 0x33` and releases the record after dispatch. `cCellGFX::LoadEffectMap` at `0x00e63560` stops/releases invalid effects and creates/starts valid effects; `InstanceEffectOnCell` at `0x00e66840` stores an effect and applies the Cell transform.
- **Events**: `cell_eat_or_mouth_interaction`, `cell_death_started`, `swarm_effect_created`, `swarm_effect_started_or_stopped`.
- **Consumers**: Cell behavior timers, interaction pool, Cell GFX, Swarm effects manager/world, visual and death presentation.
- **Structures**: queued interaction records, `cCellGame`, `cCellGFX`, `cEffectsWorld`, `IVisualEffect`.
- **Evidence**: `cell-stage.json`, `combat.json`, and `additional-domains.json`; the record types are observed raw constants, not all SDK-named actions.
- **Confidence**: **SUPPORTED** for dispatch and effect calls; **UNRESOLVED** for record payload schemas and exact queue timing.
- **Validation**: trace one interaction and one effect from allocation through dispatch, stop, replacement, and release.

## Editor workflows

### `editor_lifecycle`

- **State variable**: `cEditor+0x2b0` active flag and `cEditor+0x31c` mode.
- **States**: uninitialized, initialized, entering, active, exited, disposed; editor submode is Build (`0`), Paint (`1`), or Play (`2`).
- **Transitions, guards, actions**:
  - `Initialize` at `0x00584300` creates editor, UI, shadow, model, and message services but does not set active.
  - `OnEnter` at `0x0058e6d0` checks shadow state, requests PaintMode, and writes active near successful completion.
  - `OnExit` at `0x00587a20` clears active, requests PaintMode, and releases selection, manipulator, model, skin, PlayMode, animation, and world support.
  - `Dispose` at `0x00576c50` calls `OnExit` when active, removes generated commands/listeners, and releases the editor graph.
- **Events**: `editor_constructed`, `editor_initialized`, `editor_entered`, `editor_exited`, `editor_disposed`, `editor_active_mode_requested`.
- **Consumers**: `IGameModeManager`, EditorUI, PlayMode, animation world, graphics/shadow services.
- **Structures**: `Editors::cEditor`, `EditorModel`, `EditorStateEditHistory`, `cEditorResource`.
- **Evidence**: `editor-workflows.json` and `creature-civilization.json`; direct editor bodies and vtable data.
- **Confidence**: **HIGH** for lifecycle field writes and broad teardown; **UNRESOLVED** for full resource ownership and all failure paths.
- **Validation**: trace active flag, mode, model, UI, animation world, and command/listener lifetime across entry and exit.

### `editor_mode_history_and_animation`

- **State variable**: `cEditor+0x31c` mode, `cEditor+0x188` history index, parallel history vectors, `cEditor+0x148` active manipulator, and editor animation-world map.
- **States**: Build, Paint, Play, no manipulator, manipulator active, history at prior/committed/future, editor creature absent/loaded/targeted/destroying/destroyed.
- **Transitions, guards, actions**:
  - `SetActiveMode` at `0x00587270` rejects invalid/equal requests, tears down old mode state, writes the new enum, performs mode-specific entry, and may emit an animation event.
  - `CommitEditHistory` at `0x00586410` appends paired state/resource records and increments the history index.
  - `Undo` at `0x0058a5a0` requires index greater than one; `Redo` at `0x0058a950` requires index less than history count.
  - `SetEditorModel` at `0x00586b00` clears derived selection/tool state, replaces the model, destroys the old animation creature, and rebuilds derived state.
  - `cEditorAnimWorld::DestroyCreature` at `0x0059c6e0` dispatches controller teardown, releases the controller, and erases the map entry.
- **Events**: `editor_mouse_down`, `editor_mouse_move`, `editor_mouse_up`, `manipulator_started`, `manipulator_updated`, `manipulator_finished`, `edit_committed`, `edit_undo_requested`, `edit_redo_requested`, `editor_anim_event_send`, `editor_anim_event_post`.
- **Consumers**: EditorModel, EditorUI, PlayMode actors/modules, palette/skin, `cEditorAnimWorld`, message manager.
- **Structures**: `Editors::cEditor`, `EditorModel`, `EditorStateEditHistory`, `cEditorResource`, `EditorCreatureController`, `Anim::IAnimWorld`.
- **Evidence**: `editor-workflows.json`, `additional-domains.json`, and `creature-civilization.json`.
- **Confidence**: **HIGH** for direct callbacks and history bounds; **MEDIUM / UNRESOLVED** for opaque manipulator class identities, redo-tail truncation, and animation consumer timing.
- **Validation**: trace mode, button, manipulator, model, history vectors, index, and animation record for every input transaction.

## World, space, and population

### `space_context_navigation`

- **State variable**: `sSpacePlayerData+0x10` (`mCurrentContext`) with `None=-1`, `Planet=0`, `SolarSystem=1`, `Galaxy=2`; active planet/star slots at `+0x04/+0x08`; player ID at `+0x18`.
- **States**: None, Planet, SolarSystem, Galaxy.
- **Transitions, guards, actions**: initialization at `0x01021d40` sets None and clears identity; `0x01021960` stores the requested context and runs `0x01001360` only for Galaxy when companion pointers are non-null; `0x010219b0` binds/replaces active star/planet records; `0x01022580` bootstraps a temporary star and forces Planet on first activation.
- **Events**: `space_context_request`, `space_context_galaxy_followup`, `active_world_binding_request`, `space_activation`.
- **Consumers**: space update, camera/navigation, star/planet presentation, relationship and empire consumers.
- **Structures**: `Simulator::SpacePlayerData`, `cEmpire`, `cStarRecord`, `cPlanetRecord`, `cSolarSystem`.
- **Evidence**: direct decompilation in `world-planet.json`; SDK enum is **CONFIRMED_NAME_ONLY** for the four values.
- **Confidence**: **SUPPORTED** for the setter and initialization; **UNKNOWN** for the Galaxy helper and cross-context binding order.
- **Validation**: probe the context accessor/setter, active pointer replacement order, and Galaxy follow-up for all four values.

### `star_planet_generation` and `solar_system_materialization`

- **State variable**: `cStarRecord+0xac` planet count, `+0x84` planet vector, `+0x0c` observed time; owner solar-system pointer at `+0x40`; `cSolarSystem` planet/body vectors.
- **States**: star not generated, counted planet records, planet record materialized, solar system absent, data loaded, graphics request, graphics destroyed.
- **Transitions, guards, actions**: `0x00bb4af0` returns when the count is nonzero; when zero and timing passes it updates observed time, removes pending state, resets manager state, and calls generation. `0x00bb4100` allocates/initializes planet records and increments the count. `0x00c8b700` lazily allocates/loads `cSolarSystem`; `0x00c86760` populates runtime vectors; `0x00c86e00` dispatches graphics create/destroy.
- **Events**: `planet_generation_request`, `planet_record_generation`, `star_system_regeneration_checked`, `star_planets_generated`, `star_planet_materialized`, `solar_system_load_or_graphics_request`.
- **Consumers**: star discovery, planet record persistence, `RecordToPlanet`, space/solar-system update, terrain and graphics.
- **Structures**: `cStarRecord`, `cPlanetRecord`, `cPlanet`, `cSolarSystem`, `cCelestialBody`, `cTerrainSphere`.
- **Evidence**: `world-planet.json`, `spawning-population.json`, and decompilation at `0x00ba61b0`, `0x00ba64a0`, `0x00bb4100`, `0x00bb5b50`.
- **Confidence**: **SUPPORTED** for count guards and record creation; **UNKNOWN** for generation formulas, materialization internals, and graphics ownership.
- **Validation**: record count, vector contents, terrain key, type/scores, and pointer replacement separately; do not equate `mPlanetCount` with vector size.

### `world_transition_step`

- **State variable**: transition owner fields at `+0x164`, `+0x18e`, `+0x18f`, `+0x190`, `+0x191`, `+0x192`, with countdown at `+0x194`; other guard getters read `+0x370`, `+0x454`, `+0x528`.
- **States**: raw phase flags and countdown progression; the names are not recovered.
- **Transitions, guards, actions**: `0x00fe0f40` uses a countdown, accumulates time, checks the initial gate, advances four independent bytes through separate guard getters, and reaches a terminal mode request.
- **Events**: `world_transition_step`.
- **Consumers**: space/planet transition owner and mode request path.
- **Structures/function**: unresolved transition owner; `FUN_00fe0f40`.
- **Evidence**: direct decompilation in `world-planet.json`.
- **Confidence**: **SUPPORTED** for raw field flow; **UNKNOWN** for semantic phase names and terminal request target.
- **Validation**: identify the owner and instrument all guard getters and byte writes before assigning states.

### Population and civilization planning surfaces

- **State variable**: `cTribePlan.mState` at `+0x04`, `mCheckTime` at `+0x0c`, `mFoodAccumulated` at `+0x14`, `mbCheck` at `+0x18`; `cTribePlanner` plans, interval map, tribe pointer, and accumulated delta; `cHerd` target size, respawn, nest/egg, extinction, and evolution fields.
- **States**: plan waiting, check due, food accumulating, requirements ready, executing/terminal; herd target, nest/egg, respawn, extinction, and evolution are SDK-declared surfaces but native transition rules are unresolved.
- **Transitions, guards, actions**: no native planner body or herd respawn body is committed. Tribe plan type must not be equated with `cTribePlan.mState`.
- **Events**: `tribe_plan_check_due`, `tribe_population_timer_due`, `tribe_member_spawn_requested`, `herd_respawn_checked`, `herd_evolution_checked`, `npc_baby_growth_timer_expired`.
- **Consumers**: tribe behavior, creature citizens, herd growth/evolution, city/vehicle population.
- **Structures**: `cTribe`, `cTribePlanner`, `cTribePlan`, `cHerd`, `cNpcTribeController`.
- **Evidence**: SDK layouts in `structs_fields.tsv`; `creature-civilization.json`, `spawning-population.json`, and `progression.json` explicitly retain missing native bodies.
- **Confidence**: **LOW / UNRESOLVED** for transitions; **CONFIRMED_NAME_ONLY** for fields and callback slots.
- **Validation**: recover planner, herd, tribe spawn, and growth bodies before naming states or thresholds.

## Empire, relationships, and progression

### `civilization_relationship_state`

- **State variable**: ordered political-ID relationship records with `mValue`, `mFlags`, and relationship-event data; alliance is bit 1 and war is bit 0 in the direct bodies.
- **States**: relationship absent, neutral, allied, at war.
- **Transitions, guards, actions**:
  - `DeclareWar` at `0x00d065a0` returns if already at war; otherwise sets bit 0, clears bit 1, and updates empire/player paths.
  - `DeclarePeace` at `0x00d038e0` clears bit 0 when the war guard passes.
  - `DeclareAlliance` at `0x00d06920` calls peace, then sets bit 1 and may emit `0x04445d43` for the player.
  - `BreakAlliance` at `0x00d01e30` clears bit 1 and may emit `0x04445d44`.
  - `ApplyRelationship` at `0x00d06270` changes score/event state without directly changing political flags.
- **Events**: relationship war/peace/alliance/lost-alliance, relationship score event, player relationship messages.
- **Consumers**: empire, diplomacy UI, mission and trade producers, player relationship listeners.
- **Structures**: `cRelationshipManager`, `cRelationshipData`, `RelationshipEvents`, `cEmpire`, `cCivilization`.
- **Evidence**: direct Ghidra decompilation in `creature-civilization.json` and `empire-space.json`; message IDs also appear in `global-events.json`.
- **Confidence**: **CONFIRMED** for flag writes and direct event emission; **SUPPORTED / UNRESOLVED** for all score clamps and complete caller ordering.
- **Validation**: trace both directed entries, player involvement, emitted message, and post-transition UI updates.

### `creature_ability_mode`

- **State variable**: `Simulator::sCreatureGameData+0x24` / global `0x0169e394`; SDK enum Attack `0`, Social `1`.
- **States**: Attack, Social, and same-state request.
- **Transitions, guards, actions**: `SetAbilityMode` at `0x00d2e4a0` writes the raw value, synchronizes dependent state only when old differs from new, and optionally plays a mode-specific sound. The setter itself does not reject other raw integers.
- **Events**: `ability_mode_change_requested`, `creature_ability_mode_commit`.
- **Consumers**: creature tool, UI, sound, and gameplay synchronization helpers.
- **Structures/functions**: `cCreatureGameData`, `0x00d2e490`, `0x00d2e4a0`.
- **Evidence**: direct decompilation plus SDK enum in `creature-civilization.json` and `combat.json`.
- **Confidence**: **HIGH** for values and changed-state/audio guard; no inference for out-of-domain integers.
- **Validation**: test both directions and same-state calls with sound on and off.

### `creature_evolution_point_accumulation` and `mission_lifecycle`

- **State variable**: evolution points in `cCreatureGameData+0x28` backed by `0x0169e398`; current brain level at `+0x00`; goal progress at `cPlayer+0x10f0`; mission state at `cMission+0x84`.
- **States**: evolution unchanged, increased below cap, at cap; mission Unaccepted `0`, Finished `1`, Accepted `2`, Active `3`, Completed `5`, Failed `6`, Aborted `7`, Rejected `8`, StepCompleted `9`.
- **Transitions, guards, actions**:
  - `SetEvolutionPoints` at `0x00d2e480` assigns directly without goal/action side effects.
  - `AddEvolutionPoints` at `0x00d2e8a0` ignores zero, stores `min(old+points, cap)`, adds the requested amount to goal progress, and conditionally dispatches action `0x45ab96e`; it does not directly advance brain level.
  - `cMission::SetState` is SDK-confirmed to clear title/secondary fields and emit mission update on Active entry; callback ordering and mission-type overrides remain unresolved.
  - SDK contract routes Accepted to Active, completion to Completed then StepCompleted or Finished, and failure/abort/rejection through their callbacks to terminal routing.
- **Events**: `creature_evolution_points_added`, `creature_evolution_points_set`, `creature_brain_requirement_queried`, `mission_update_message`, `mission_completion_rewards`, mission acceptance/failure/abort/rejection.
- **Consumers**: creature UI, goal progress, mode strategy, mission manager, player empire, inventory, relationships, tutorial state.
- **Structures/functions**: `cCreatureGameData`, `cPlayer`, `cMission`, `cMissionManager`, `0x00d2e350`, `0x00d2e380`, `0x00d2e480`, `0x00d2e8a0`.
- **Evidence**: direct evolution decompilation in `progression.json`, `creature-civilization.json`, and `economy.json`; mission transition order is primarily **SUPPORTED SDK contract**, not a complete native body.
- **Confidence**: **HIGH** for evolution arithmetic; **MEDIUM** for mission lifecycle; exact rewards, thresholds, and brain-level writer are unresolved.
- **Validation**: record signed/over-cap evolution values and every mission state/callback/message for top-level and sub-missions.

### `collectable_unlock_and_economy`

- **State variable**: collectable status byte and membership in `mUnlockedItems`, plus `mUnlockPoints`; mission reward/cost fields; tool ammunition; rare map entry; energy fields only where a direct body is not conflicting.
- **States**: collectable neither unlocked/highlighted, unlocked only, unlocked and highlighted, nonpositive/positive/capped tool ammunition, rare not found/found.
- **Transitions, guards, actions**:
  - `UnlockPart` at `0x00596da0` rejects an unaffordable nonzero cost, subtracts the cost, sets status bits `0x03`, updates the list, and returns true.
  - `LockPart` at `0x00596e10` clears status bits and updates the list; no refund is shown.
  - `AddAmmo` at `0x0104cbd0` leaves at/above maximum unchanged, otherwise adds and caps; `ConsumeAmmo` at `0x0104cc00` subtracts with no lower clamp.
  - `SetRareAsFound` at `0x0103fba0` stores the value and emits `0x06779f04` only on a transition to 1; `ObtainTradingObject` is a supported acquisition boundary whose exact ordering is unresolved.
  - Mission completion money/tool/relationship effects are SDK contract only; money identity and ordering are unresolved.
- **Events**: collectable unlock/lock, evolution points, mission rewards, rare found/discovered, ammo added/consumed, relationship score, scenario energy message.
- **Consumers**: collectable editor, creature UI, tool manager, space trading UI, inventory, badge/event log, mission/economy systems.
- **Structures**: `cCollectableItems`, `cSpaceToolData`, `cSpaceTrading`, `cMission`, `cEmpire`, `cPlayerInventory`.
- **Evidence**: disassembly and decompilation in `economy.json`; currency identity is not collapsed across resources, points, relationship score, and energy.
- **Confidence**: **HIGH** for direct collectable/ammo/rare mechanics; **MEDIUM / UNRESOLVED** for mission economy and energy conflicts.
- **Validation**: exercise affordability, zero/exact/negative costs, cap boundaries, repeated rare acquisition, and real mission reward field linkage.

## Persistence and resource lifecycle

### `property_list_transfer` and `class_serializer_object_transfer`

- **State variable**: analytical transfer phase plus local success flag; ClassSerializer counters, object pointer, attribute table, and current stream position.
- **States**: transfer not started, transfer in progress, succeeded, failed; serializer constructed, header transfer, attribute transfer, complete, failed.
- **Transitions, guards, actions**:
  - `PropertyList::Write` at `0x006a1540` writes count then local ID/value entries and stops on first failed stream operation.
  - `PropertyList::Read` at `0x006a2f60` reads framing, may resolve/replace a parent list, resizes local entries, and stops on first failure.
  - ClassSerializer constructor at `0x00692880`/`0x00692f90` initializes bounded metadata; write dispatcher `0x00692900` invokes attribute callbacks; read dispatcher `0x00693e10` validates object counts, resolves identities, invokes callbacks, and checks stream state.
- **Events**: `property_list_transfer`, `simulator_object_write`, `simulator_object_read`, `star_database_checkpoint`, `cell_serializable_handoff`.
- **Consumers**: serializable object/resource owners, `stars.db` reader/writer, profile/save orchestration, Cell initialization.
- **Structures**: `PropertyList`, `DirectPropertyList`, `ClassSerializer`, `Attribute`, `ISimulatorSerializable`, `SerializerDatabase`, `IO::IStream`.
- **Evidence**: direct decompilation in `persistence.json`; SDK interior anchors are not treated as standalone `ClassSerializer::Write/Read` bodies.
- **Confidence**: **SUPPORTED** for local transfer mechanics; **UNKNOWN** for whole-save framing, rollback, atomicity, version negotiation, and parent ownership.
- **Validation**: inject failures at count, identity, attribute, and stream operations; trace one `.spo` and `stars.db` checkpoint without modifying original data.

### `resource_manager_registry_lifecycle`

- **State variable**: manager registry fields for notifications, factories, type mappings, caches, extension mappings, and filename mappings.
- **States**: uninitialized, initialized/unconfigured, configured, disposed/unavailable; per-request cache miss/hit/unavailable.
- **Transitions, guards, actions**:
  - Initialize at `0x008de530` builds lookup storage.
  - SDK-confirmed registration surfaces add/remove databases, factories, and caches; lookup must find the required database/factory before a record can be produced.
  - `GetResource` is anchored at `0x008df700` with the live body around `0x008df460`; it probes cache-like storage before database/factory fallback.
  - `GetPrivateResource` is SDK-confirmed as cache-bypassing; `GetResourceAsync` returns an `IAsyncRequest`; `ReloadResource` and `FlushCache` have unresolved replacement/eviction behavior.
  - `DatabasePackedFile::OpenRecord` around `0x008da3d0` resolves the full `(type, group, instance)` identity; `CloseRecord` is coupled to reference bookkeeping.
- **Events**: `resource_manager_initialize`, database/factory/cache registration, `resource_requested`, `resource_cache_hit`, `resource_cache_miss`, `package_index_loaded`, `record_identity_matched`, `record_opened`, `resource_unavailable`, `cell_preload_started`, `cell_content_preloaded`, `cell_display_started`, `cell_display_exited`.
- **Consumers**: Cell GFX preload, model/effect/texture/creature consumers, resource factories, database/cache registries.
- **Structures**: `Resource::cResourceManager`, `Database`, `DatabasePackedFile`, `IRecord`, `ICache`, `IResourceFactory`, `ResourceKey`, `cCellGFX`.
- **Evidence**: SDK interfaces and static bodies in `resource-content.json`; the current OpenSpore provider is only a clean-room byte provider and is not original behavior.
- **Confidence**: **SUPPORTED / MEDIUM** for cache-before-fallback and record identity; **UNKNOWN** for database priority, async scheduling, cache eviction, QFS call site, and output ownership.
- **Validation**: trace one exact ResourceKey through cache hit, miss, record open/close, factory decode, cache insertion, reload, and unavailable error.

## Additional state domains

- **Shared noun registry**: `FUN_00b21340` maps noun keys through `cGameNounManager+0x98`, materializes/inserts `tGameDataVectorT<cGameData>`, and clears `needsUpdate`. It has 254 total and 50 gameplay callers in the source dossier, but the function identity and callback arguments are unresolved. Evidence **SUPPORTED**; validation must instrument map presence and update flags.
- **Civ communication**: `cCommManager` event body `0x00aeb160` allocates a 0xa0 event and appends it to `+0x20`; `ShowCommEvent` body `0x00aebe90` stores the current event at `+0x1c` before UI/message processing. Payload codecs and completion/clear are unresolved. Evidence **SUPPORTED**.
- **Palette/editor UI**: `PaletteIterator` at `0x005c7d00`/`0x005c7f10` advances four nested cursors and returns the current item; `PaletteUI` active category at `0x005cb240` range-checks, swaps panels, updates page number, and sends `0x44ef2b8`. Evidence **SUPPORTED**; names of some page/category effects remain bounded.
- **ArgScript parser**: `FormatParser` fields include definitions, variables, global variables, blocks, special blocks, current scope, and scope lengths. Scope nesting must balance before close/dispose, but `Initialize`, `StartScope`, `EndScope`, `Close`, `Dispose`, and processing bodies are incomplete. Evidence **SUPPORTED / UNRESOLVED**.
- **Audio**: `PlayProceduralAudio` at `0x00571f80` obtains a non-null audio system and dispatches virtual operations; track ownership is unresolved. Evidence **SUPPORTED / LOW**.
- **Tribe, herd, and scenario population**: SDK fields establish timer, egg/nest, target population, spawn, and evolution surfaces, but no native scheduler transition is committed. These are documented state surfaces, not reconstructed machines.

## Evidence ledger and validation boundary

The strongest high-impact direct evidence is concentrated at the mode manager helper `0x007d85b0`, Cell frame/death/despawn paths `0x00e806b0`, `0x00e7a7c0`, `0x00e7a4a0`, `0x00e780a0`, editor lifecycle/history/mode bodies `0x0058e6d0`, `0x00587a20`, `0x00587270`, `0x00586410`, `0x0058a5a0`, `0x0058a950`, space context `0x01021960`, serialization dispatchers `0x00692900`/`0x00693e10`, and resource lookup `0x008df460`.

Validation must remain read-only and hash-pinned. The corpus does not justify claiming runtime reachability for gameplay transitions. A future validation plan should resolve the listed native bodies, establish producer/consumer paths for SDK-only messages, and record positive traces before raising any static transition to runtime or verified evidence.
