# Event and Message Map

## Scope and evidence rules

This map is derived from the merged record `knowledgegraph/research/gameplay-state-machines.json` and the 17 files under `knowledgegraph/research/state-machines/`. It describes event transport and notification boundaries, not an implementation design.

The following evidence distinctions are preserved:

- **SDK-name-only**: a message enum, class name, vtable slot, or field establishes a name/layout contract but not a producer, consumer, payload mapping, or runtime order.
- **Decompilation**: a recovered body establishes direct calls, branches, memory operations, and local ordering where the boundary is reliable.
- **Disassembly**: instruction-level state writes, call order, and vtable entries are stronger than a stale SDK anchor.
- **Runtime**: the only positive original-process evidence in the corpus is the bounded application startup/service-access path in `tools/observatory/examples/obs_main_menu_example.jsonl`. No positive original Cell, editor, empire, progression, save/load, resource, or world-transition trace is available.

Message names, numeric IDs, and payload records are not interchangeable. A 0x40-byte `StandardMessage` layout does not identify its parameter meanings. Where the source record says `type_only`, `sdk_only`, `producer_unresolved`, or `payload_unresolved`, that limitation is retained below.

## Central dispatcher inventory

The major central dispatchers discovered across the merged JSON and source artifacts are:

1. **App message manager**: registration, send/post routing, queue processing, listener adapters, and static handlers.
2. **App game-mode manager**: concrete mode activation helper, lifecycle callbacks, and mode enter/exit announcements.
3. **App runtime message handler**: `App::cSporeApp::HandleMessage` at `0x00f47b10`, including `kMsgAppUpdate` and stop dispatch.
4. **Simulator mode listener**: `0x00b63510`, which reads mode announcement payload words and selects last/current mode commits.
5. **Simulator input manager**: global `DAT_0167eaf8`, getter `0x00b3d350`, and the six SDK-mapped input callback slots `+0x4c..+0x60`.
6. **UTFWin window dispatcher**: `UTFWin::Window::SendMsg` at `0x00960250`, `IWinProc` filtering and `InteractiveWinProc` callbacks.
7. **Editor message dispatcher**: `Editors::cEditor::HandleMessage` at `0x00591fa0` plus the request helper at `0x00591690`.
8. **EditorUI dispatchers**: app-message switch at `0x005dec10`, UI-command switch at `0x005e0000`, and mode updater at `0x005dda30`.
9. **Civ communication dispatcher**: `cCommManager` create/show path around `0x00aeb160` and `0x00aebe90`, driven by the body at `0x00aeb7b0`.
10. **Star/world message dispatcher**: star-generation consumer around `0x00bb5d80`; planet regeneration and record creation around `0x00bb4af0` and `0x00bb4100`.
11. **Persistence service**: `Simulator::cGamePersistenceManager::Get` at `0x00b3d440` and the SDK `LoadGame` surface at vtable `+0x10`; serializer dispatchers are separate from the message manager.
12. **Resource manager**: cache/database/factory acquisition around `0x008df460` and the SDK resource interfaces; this is a content lifecycle dispatcher, not an App message dispatcher.
13. **Cell interaction queue dispatcher**: `FUN_00e7e130`, with timer/behavior coordination at `FUN_00e7e6c0`.

The event families below are separated because their payloads and callback contracts differ. A listener registered in one family does not establish that it receives a record from another family.

## Event families

### App message-manager records

`App::IMessageManager` exposes `AddListener`, `AddUnmanagedListener`, `AddHandler`, `AddEntry`, and removal operations. Registration records contain listener, priority, refcount flag, handler, object, and optional ID array/count. Registration sites include `0x00883a90`, `0x00883ad0`, `0x00883b20`, and `0x00884d70`.

`MessageSend` is the SDK-named vtable operation at `IMessageManager+0x14`; `MessagePost` is `+0x18`; `MessagePostFunction` is `+0x1c`. `MessageSend` takes an unmanaged `void*`; `MessagePost` takes `IMessageRC*` and a listener; `MessagePostFunction` adds a handler, integer routing/option value, and context object. Immediate versus queued timing, priority direction, tie order, consume-result behavior, lock rules, and release timing are unresolved.

`ProcessQueue` at `0x008841f0` and `ProcessQueue2` at `0x00847f0` walk unresolved queue records and release referenced objects. The 0x18-byte queue record is not assumed to be identical to the 20-byte registration `Entry`.

### Lifecycle and mode announcements

The game-mode helper at `0x007d85b0` calls old `OnExit`, updates the active index, sends `0x0212d3e7`, calls new `OnEnter`, then sends `0x022d1adc`. The source artifacts preserve both `CONFIRMED` send order and **UNRESOLVED** queue timing. The SDK names the first record `OnModeExitMessage` and the second `OnModeEnterMessage`; their parameter words are not fully mapped.

`kMsgAppUpdate` is `0x01ee100a`, described by the SDK as once per game frame after other systems update. The binary handler compares the ID and calls the frame body, then `IAppSystem::PostUpdate`. This is the strongest callback/update bridge in the corpus.

### Simulator StandardMessage-derived records

The merged event catalog identifies `MissionUpdateMessage`, `CombatantKilledMessage`, `PlayerEmpireAlliedMessage`, `PlayerEmpireLostAllianceMessage`, `ToolOnHitMessage`, `GameNounStatusChangedMessage`, `ScenarioCreatureHealedMessage`, and `SpaceRareFoundMessage` as 0x40-byte `StandardMessage`-derived records. Their record layout is SDK-confirmed, but most message IDs and parameter mappings are type-only. They must not be treated as equivalent merely because their C++ record sizes match.

### Editor message and animation records

`Editors::cEditor::HandleMessage` at `0x00591fa0` is a large hash/message switch. It has exact branch constants, but payload schemas and control names are not all recoverable. The EditorUI app-message dispatcher at `0x005dec10` handles `0x100`, `0x102`, `0x103`, `0x104`, and `0x107`; semantic names such as New, Finish, and Cancel are intentionally not assigned. The UI-command dispatcher at `0x005e0000` directly routes known commands to PlayMode, Undo, Redo, and mode changes.

`cEditorAnimEvent::MessageSend` at `0x0059d8b0` and `MessagePost` at `0x0059d840` pack a 48-byte refcounted editor animation record containing model, event ID, and scalar fields. The recovered AppSystem destination slots differ, but the final animation consumer and queue timing remain unresolved.

### UTFWin UI messages

`UTFWin::Window` owns a WinProc list at `+0x64`; `IWinProc` exposes priority and event-flag filters before `HandleUIMessage`. SDK `MessageType` values include key-down `0x01`, key-up `0x02`, key-down2 `0x03`, key-up2 `0x04`, key-press `0x05`, mouse-down `0x06`, mouse-up `0x07`, mouse-move `0x08`, mouse-wheel `0x09`, refresh `0x0a`, update `0x0c`, paint `0x0d`, window-changed `0x0e`, layout `0x10`, element-added `0x11`, element-removed `0x12`, state-changed `0x13`, collision `0x14`, transform `0x15`, button-click `0x17`, button-select `0x18`, mouse-enter `0x1b`, and mouse-leave `0x1c`.

Payload schemas are complete only for selected records. Button select is a high-value direct bridge: `EditorNamePanel` at `0x005c0100` handles the SDK `kMsgButtonSelect` branch and forwards a boolean payload. `Window::SetState` recursively compares child state values for `kMsgStateChanged`.

### Cell interaction records

The Cell gameplay loop uses pooled objects and transient action records, not the current local OpenSpore event record. `FUN_00e7e130` switches on record type `+0x24` and releases each record after dispatch. Observed raw types include `1`, `2`, `5`, `6`, `7`, `0x0c`, `0x0d`, `0x13`, `0x14`, `0x1d`, `0x1e`, `0x2c`, `0x32`, and `0x33`. The type domain and payloads are not fully named. `FUN_00e7e6c0` decrements behavior timers and dispatches the queued interaction when timers expire.

### Scheduler and deferred records

`Simulator::tDeferredEvent` is a 28-byte SDK record with GUID, trigger time, and four user payload fields. The scheduler owner, epoch, ordering, duplicate policy, expiry, and callback are unresolved. `ScheduledTaskListener` is an adapter contract for timing callbacks, but the artifact does not establish that every deferred event reaches the App message manager.

### Domain and serializable records

`Simulator::cCommEvent` is a 160-byte serializable communication record. `cFeedbackEvent` is a 148-byte record stored in `cUIEventLog` by key. `AnimationMessage` is a distinct 24-byte record. These families must not be conflated with `StandardMessage`, UTFWin messages, Cell interaction records, or the current OpenSpore `SimEvent`.

## High-value event map

The following table records the high-value events needed to reason about mode changes, lifecycle, death, progression, diplomacy, persistence, and world transitions. “Produced by” and “consumed by” intentionally retain unresolved entries where the corpus has no complete path.

| Event / record | Produced by | Consumed by | Payload | Conditions | Resulting state changes | Evidence / confidence |
|---|---|---|---|---|---|---|
| `app_update` / `kMsgAppUpdate` (`0x01ee100a`) | App frame/message producer around `0x00f4827e-0x00f4828a`; SDK update listeners | `cSporeApp::HandleMessage` `0x00f47b10`, frame body `0x00f47930`, `IAppSystem::Update/func7Ch/PostUpdate` | Message ID; payload meaning is not used by the recovered handler | `mHasInitialized != 0`; pacing target is evaluated; no fixed-step accumulator is established | QPC/timing baseline changes; one app update sequence runs; PostUpdate follows | SDK enum + disassembly; **SUPPORTED**, **CONFIRMED_NAME_ONLY** for SDK contract |
| `mode_exit_announcement` / `0x0212d3e7` | `cGameModeManager` transition helper `0x007d85b0`; also `cAppSystem::PreShutdown` dispatch at `0x007e6470` | Manager listeners, Simulator mode listener `0x00b63510`, transition-effect and achievement listeners; exact listener set incomplete | SDK `OnModeExitMessage` is 64-byte `StandardMessage`; mode-ID parameter words are not fully mapped | Valid old active mode; different requested mode for transition case; pre-shutdown can dispatch the same numeric ID | App active index already changed; Simulator may commit last mode; achievement checkpoint branch may mutate manager/achievement state | Live disassembly/decompilation; **CONFIRMED** ID/send order, **UNRESOLVED** payload and queue timing |
| `mode_enter_announcement` / `0x022d1adc` | `cGameModeManager` transition helper `0x007d85b0` | Manager, Simulator mode listener `0x00b63510`, `OnModeEntered` transition callback `0x00b1dbd0` | SDK `OnModeEnterMessage` 64-byte record; current/previous mode words observed at `+0x08/+0x10` in listener | New `OnEnter` has completed for a different valid mode | New mode is active; Simulator may commit current mode; transition effect may be enabled | Live disassembly; **CONFIRMED** ID/order, **UNRESOLVED** queue semantics |
| `mode_set_by_name` / `0x00e11333` | UI/menu/command producer unresolved | `cGameModeManager::SetActiveModeByName` `0x007d8360` and indexed activation `0x007d8c80` | SDK `SetGameModeMessage`; exact mode-name parameter placement unresolved | Manager initialized; name comparison succeeds; matching ModeEntry found | Matching mode is requested; normal exit/enter helper may follow | SDK enum + direct decompilation; **CONFIRMED_NAME_ONLY** record, **SUPPORTED** consumer, producer **UNRESOLVED** |
| `app_pre_shutdown_checkpoint` / `0x0212d3e7` | `App::cAppSystem::PreShutdown` `0x007e6470` | Achievement manager registration/handler around `0x00676c80`/`0x00677140`; other application listeners unknown | Same numeric ID as mode-exit announcement; payload role not proven | Pre-shutdown path invoked | Achievement manager branch mutates achievement `0xA3434A32` and manager byte `+0x24`; serializer/database write is not proven | Direct decompilation/raw bytes; **SUPPORTED** dispatch, persistence behavior **UNRESOLVED** |
| `save_game_request` / `kMsgSaveGame` (`0x01cd20f0`) | Save UI and Cell save-related path around `0x00e53f20`; producer path incomplete | Save dialog/UI, application listeners, Cell UI save path; exact writer is unresolved | SDK message contract; Cell handler references `ui_global_save` and message constant; payload schema unresolved | Save operation requested | SDK contract says pause and success dialog; Cell field `cCellGame+0x51DA` is set in the early handler; full writer not established | SDK + direct decompilation; **SUPPORTED** early handler, **CONFIRMED_NAME_ONLY** full contract |
| `load_game_request` / `LoadGame` | Load-game UI/orchestration unresolved | `cGamePersistenceManager` SDK `LoadGame(GameLoadParameters)` vtable `+0x10`; `Get` at `0x00b3d440` | `GameLoadParameters` SDK contract; exact fields and payload not recovered | Persistence service exists; SDK requires player noun before load, but runtime condition is not observed | Intended object/profile restoration; exact order, failure behavior, and post-load callbacks unresolved | SDK-name-only plus accessor; **CONFIRMED_NAME_ONLY**, runtime **UNRESOLVED** |
| `mission_update_message` | `cMission::SetState(Active)` contract | Mission UI, mission manager, related listeners | 0x40-byte `StandardMessage`; ID and parameters unresolved | Entering `MissionState::Active` | Mission state is Active; listener/UI state may refresh | SDK semantics; **SUPPORTED** contract, native body/order **UNRESOLVED** |
| `mission_completion_rewards` | `cMission::OnMissionCompleted` `+0x94` | Tutorial state, player empire, inventory, relationship manager, mission UI | Callback payload and exact field order unresolved | Completion succeeds; sub-mission vs top-level route unresolved | Reward money, tool, relationship, tutorial/empire updates may occur; Completed/StepCompleted/Finished route | SDK callback contract; **SUPPORTED** contract, exact runtime/order **UNRESOLVED** |
| `combatant_killed_message` | Unresolved combat death publisher | Combat, mission, and UI listeners; exact producer/consumer path absent | 0x40-byte `StandardMessage`; killer/victim parameters unresolved | Combatant death occurs, per SDK type name | Combat/mission/UI state may update; generic cCreature death flag path is not proven to publish this record | SDK type only; **CONFIRMED_NAME_ONLY**, runtime **UNRESOLVED** |
| `player_empire_allied_message` / `0x04445d43` | `cRelationshipManager::DeclareAlliance` body `0x00d06920` when player is involved | Player relationship/diplomacy listeners; exact listener set incomplete | SDK/relationship message; political IDs and parameter placement unresolved | Alliance transition and player involvement | Alliance bit set; relationship/UI state may update | Direct body + SDK name; **SUPPORTED** emission, payload **UNRESOLVED** |
| `player_empire_lost_alliance_message` / `0x04445d44` | `cRelationshipManager::BreakAlliance` body `0x00d01e30` when player is involved | Relationship/diplomacy/UI listeners; exact set incomplete | SDK/relationship message; fields unresolved | Alliance is broken and player is involved | Alliance bit cleared; relationship/UI state may update | Direct body + SDK name; **SUPPORTED**, payload **UNRESOLVED** |
| `star_ownership_changed` / `0x55bd8f7` | `cEmpire` star membership add/remove bodies `0x00c341a0`/`0x00c34ee0` | Star ownership/presentation listeners; exact listener set incomplete | SDK contract mentions star ownership; payload details unresolved | A star pointer is added to or removed from `cEmpire.mStars`; home-state update may occur | Empire star membership changes; home-star/home-planet cleanup may run | Direct decompilation; **SUPPORTED** mechanics, message payload **UNRESOLVED** |
| `space_rare_discovered` / `0x06779f04` | `cSpaceTrading::SetRareAsFound` `0x0103fba0` | Rare UI, event log, badge/progression observers | SDK rare-found record; exact rare instance/location fields unresolved | Stored value changes to 1 from a value other than 1 | `mRareMap[ResourceKey]` becomes found; first-discovery notification emitted | Direct disassembly; **CONFIRMED** message ID/branch, payload **UNRESOLVED** |
| `space_rare_found` | `cSpaceTrading::ObtainTradingObject` around `0x0103fc10` | Inventory, event log, badge, rare/progression listeners | SDK `SpaceRareFoundMessage`; exact acquisition payload unresolved | Rare object acquired; exact inventory/stacking order unresolved | Inventory/resource state may update; rare/map/badge state may update | SDK contract + static xrefs; **SUPPORTED** acquisition boundary, order **UNRESOLVED** |
| `badge_progress_changed` / `0x38cf2fb` | `cBadgeManager::AddToBadgeProgress` around `0x00fe52c0` | Badge UI, badge state map, event counters | Signed badge value; message payload schema unresolved | Existing badge progress entry receives a signed addition | Badge progress map changes; completion/unlock thresholds are not recovered | SDK semantics only; **SUPPORTED** contract, native producer **UNRESOLVED** |
| `cell_eat_or_mouth_interaction` | Contact/ingestion paths around `0x00e71520`, `0x00e725c0`, `0x00e727e0` | `FUN_00e7e130` queued-record dispatcher, animation/effect, health/damage reconciliation | Duration-bearing queued record; type and payload fields partly unknown | Contact/ingestion action queues a record | Interaction animation/effect and health state may change; record is released after dispatch | Direct Cell decompilation; **SUPPORTED** mechanics, enum mapping **UNRESOLVED** |
| `cell_damage_resolved` | Collision/attack callers and `FUN_00e7a7c0` | `FUN_00e7a4a0`, UI rollover, death/effect path | Victim, attacker, contact position, damage type/flags/effect flags; selector meanings unresolved | `ShouldNotAttack` permits; invulnerability does not suppress; damage is positive | `cCellObjectData+0x244` decreases and clamps; death path may run | Direct Cell/combat decompilation; **SUPPORTED**, no combat runtime |
| `cell_death_started` | `FUN_00e7a7c0` / `0x00e7a4a0` / `0x00e72060` | Death animation/effect, flee/chase reactions, queued interaction, stage reload | Cell/killer context and flags; exact payload schema unresolved | Health reaches zero; player/non-player branch selected | Death flag, UI/cinematic state, pending action, and possibly reload request change | Direct decompilation; **SUPPORTED**, no Cell runtime |
| `cell_stage_reload_requested` | `0x00e50940`, `0x00e72200`, `0x00e7b410` | Cell frame `0x00e806b0`, stage rebuild `0x00e7fd00`, population/UI setup | Supplied progression/scale/player/world fields; exact ABI unresolved | `sCellGame+0x51d8` set and an active frame observes it | Cell/UI/effect state drains; world/scale/UI reloads; population/setup runs | Direct decompilation; **SUPPORTED**, exact transition origin/runtime **UNRESOLVED** |
| `editor_app_message_0x44ef2b8` | `PaletteUI` active-category setter `0x005cb240`; editor paths can also emit it | `Editors::cEditor::HandleMessage` and palette/editor UI consumers | Opaque category/payload; parameter schema unresolved | Valid signed category index; active category changes | Palette category/page/UI state changes; secondary editor message dispatch may occur | Direct body + dispatcher evidence; **SUPPORTED** ID/side effects, schema **UNRESOLVED** |
| `editor_app_message_0x51cc0b8` | `cEditor::HandleMessage` branch at `0x00591fa0` or its registered producer | `cEditor::SetActiveMode` / editor mode machinery | Opaque editor message payload; exact schema unresolved | Branch selected by the editor hash dispatcher | PaintMode may be requested; mode-specific editor state may change | Direct body; **SUPPORTED** branch, no typed message name |
| `editor_anim_event_send` | `cEditor::SetActiveMode`, neutral-pose and animation callers | Recovered IAppSystem virtual destination; final animation consumer unresolved | 48-byte `cEditorAnimEvent`: model, event ID, scalar fields; packed local layout unresolved | Event record populated; IAppSystem pointer usable | Animation intent routed; final animation state not established | Direct editor bodies + SDK/type layout; **SUPPORTED** call shape |
| `editor_anim_event_post` | Neutral-pose and animation callers | Alternate IAppSystem slot; final animation consumer unresolved | Same 48-byte editor event family; queue timing unresolved | Event record populated; alternate send path selected | Intent is posted through a different slot; final state unresolved | Direct editor bodies; **SUPPORTED** call shape |
| `galaxy_star_generation_message` | Galaxy generation effect; exact producer unresolved | `cStarManager` handler around `0x00bb5d80` | SDK family includes star colors/types, black holes, protoplanetary disks, galactic core, binary stars; record payload varies | Galaxy generation effect dispatches a typed record | `cStarRecord` objects are created and inserted into the star grid | Direct consumer + SDK enum; **SUPPORTED** consumer, producer **UNRESOLVED** |
| `planet_tool_hit` / `kMsgToolOnHit` / sculpt hit | Space tool strategies; exact binary producer unresolved | Space tool, combat, mission, and UI listeners; exact set incomplete | SDK tool-hit record; tool/target/damage fields unresolved | Tool reports a hit or sculpt/color tool hit | Combat/planet interaction and possibly progression/UI state may change | SDK message contract; **CONFIRMED_NAME_ONLY**, native path **UNRESOLVED** |
| `cross_stage_world_transition` | Stage/cinematic systems; exact binary producer unresolved | Cross-stage transition listeners; exact set incomplete | SDK IDs `CellToCreatureTransition=0x02a4f8f0` and `CreatureToTribeTransition=0x0477f66c`; payload schemas unresolved | Stage transition request occurs | Target stage/cinematic state may change; exact target/mode request unresolved | SDK names only; **CONFIRMED_NAME_ONLY**, no runtime |

## Dispatcher and callback contracts

### App message manager

Registration is separated from emission. `IMessageManager::Entry` carries listener, priority, refcount flag, `MessageHandler_t`, and object. A listener can be selected by a message ID array; a handler is function-plus-context metadata. The message manager’s queue processor does not prove traversal order, consume semantics, or whether a handled result stops later listeners.

The `LambdaMessageListener`, `UpdateMessageListener`, and `ScheduledTaskListener` adapters store callback/context and timing fields. Update listeners forward a selected message to `IUpdatable::Update`; scheduled listeners adapt timing to callbacks. Adapters do not reinterpret the selected payload, and cancellation/removal timing remains unresolved.

### App game-mode manager and Simulator listener

`cGameModeManager` owns `ModeEntry` pointers, mode IDs, and names. The concrete vtable at `0x01412598` maps `SetActiveMode`, `SetActiveModeAt`, and `SetActiveModeByName`; the activation helper is `0x007d85b0`. The stale SDK-labeled body at `0x007d8d40` is treated as a teardown body, not merged into the activation path.

The Simulator mode listener at `0x00b63510` is the bridge from App mode announcements to the two commit helpers. It reads words at `+0x08/+0x10`, normalizes them, and selects last/current commit behavior. This bridge is more specific than assuming that the transition-effect callbacks themselves write `mLastGameMode` or `mCurrentGameMode`.

### App runtime handler

`cSporeApp::HandleMessage` at `0x00f47b10` compares incoming IDs, dispatches the app-update frame path for `0x01ee100a`, and handles stop ID `0x0153c326` in a separate path. The frame body’s QPC measurement and optional pacing are not a fixed-step accumulator contract. The app-update handler calls the application post-update slot after the frame sequence.

### Simulator input manager

`cGameInputManager::Get` at `0x00b3d350` returns `DAT_0167eaf8`. SDK layout maps `OnKeyDown`, `OnKeyUp`, `OnMouseDown`, `OnMouseUp`, `OnMouseMove`, and `OnMouseWheel` to vtable offsets `+0x4c`, `+0x50`, `+0x54`, `+0x58`, `+0x5c`, and `+0x60`. The manager stores mode IDs, input maps, mouse state, and callback slots. The concrete router body, input-region algorithm, and camera fan-out are unresolved. The Cell mode body at `0x00e818f0` is a downstream consumer, not proof of the manager’s complete routing order.

### UTFWin window dispatcher

`Window::SendMsg` is SDK-named at `0x00960250`, with an intrusive list at `Window+0x64`. `IWinProc::GetPriority`, `GetEventFlags`, and `HandleUIMessage` are SDK-confirmed callback slots. Event type selects the matching `InteractiveWinProc` callback; return-value consumption, bubbling, focus, tie order, and thread affinity are unresolved. `EditorNamePanel::HandleUIMessage` at `0x005c0100` demonstrates direct button-select/component-activation handling but not the whole window routing policy.

### Editor dispatchers

`cEditor::HandleMessage` at `0x00591fa0` is a high-fan-out hash switch. The request helper `0x00591690` creates or changes resource-backed editor state, invokes `SetEditorModel`, commits history, and may emit app/animation events. `EditorUI` at `0x005dec10` dispatches app IDs `0x100`, `0x102`, `0x103`, `0x104`, and `0x107`; the names of those branches are intentionally opaque. `EditorUI` at `0x005e0000` routes `0x70218642` to PlayMode, `0xb006ef6e` to Undo, and `0xf006efa5` to Redo, with other control hashes remaining opaque. `0x005dda30` suppresses equal mode requests and otherwise calls `cEditor::SetActiveMode`.

### Civ communication

The civ communication body at `0x00aeb7b0` calls the event factory around `0x00aeb160`, which allocates a 0xa0-byte event and appends it to `cCommManager+0x20`. The show body around `0x00aebe90` AddRefs and stores the event at `+0x1c` before UI/message processing. The numeric action IDs, queue order, completion, and codec lifetime are unresolved.

### Star/world and persistence dispatchers

The star-generation consumer at `0x00bb5d80` creates and inserts star records from `DistributeEffectMessageData`. The no-planet regeneration body at `0x00bb4af0` and record generation body at `0x00bb4100` are separate from the App message manager.

`cGamePersistenceManager::Get` at `0x00b3d440` is only a service accessor. The SDK `LoadGame` vtable contract at `+0x10` does not establish file access, restore order, or failure behavior. Serializer write/read dispatchers `0x00692900` and `0x00693e10` are attribute callbacks, not App messages. `Resource::cResourceManager` lookup around `0x008df460` similarly belongs to the content lifecycle, not the message bus.

### Cell interaction queue

`FUN_00e7e130` is the most direct original event transport recovered for Cell gameplay. It consumes a pooled record, switches on `+0x24`, invokes the matching interaction path, and releases the record. The current OpenSpore local `eat`/`flee` events are an approximation and are not treated as the original record ABI.

## Update and callback contract summary

- `IGameMode`: Initialize, Dispose, OnEnter, OnExit, six input callbacks, and Update; lifecycle order is concrete for the App manager, but the 27-slot Cell mode candidate and input fan-out are not a complete runtime trace.
- `IAppSystem`: Update `+0x78`, unnamed `func7Ch` `+0x7c`, PostUpdate `+0x80`, Pause/Unpause and shutdown surfaces. The fixed-step slot is SDK-name-only and is not mapped to observed pacing.
- `IMessageManager`: send/post/post-function and registration operations have distinct payload ownership and timing contracts.
- `IUnmanagedMessageListener::HandleMessage`: receives a message ID and `void*`; payload interpretation is domain-specific.
- `IUpdatable::Update`: receives a selected message through the update adapter; timing and queue behavior are adapter-specific.
- `ScheduledTaskListener`: timing-driven callback adapter; duplicate, cancellation, and expiry behavior are unresolved.
- `IWinProc`: priority/event flags filter before `HandleUIMessage`; callback return handling is unresolved.
- `Simulator::cSimulatorSystem`: SDK surface exposes subsystem initialization, Update, PostUpdate, and UI graphics update; concrete iteration order is not recovered.
- `EditorPlayMode`: four module callbacks and actors are updated directly; environment and UI sequence fields are guarded but incompletely named.
- `cGameTimeManager`: pause and speed fields are explicit, but the native pause/speed/convert bodies are not complete.
- `Resource::IAsyncRequest`: SDK exposes readiness polling through `IsReady` and `GetResource`; scheduling, cancellation, and polling order are unresolved.

## Event evidence conclusions

The strongest event claims are the app-update ID and frame callback order, the mode enter/exit send IDs and helper order, the Cell queued-record dispatcher’s raw type switch, the relationship/rare/star message emissions with direct bodies, and the editor mode/history callback chain. The weakest claims are the identity of UI/menu producers, parameter meanings for 0x40-byte records, payload schemas for editor hashes, message priority/tie behavior, deferred scheduler ownership, and all runtime reachability beyond bounded startup.

No message should be promoted from an SDK type to a complete producer/consumer state transition without a direct body, a corroborated xref, and a payload boundary. The event map therefore remains a research index, not an ABI specification.
