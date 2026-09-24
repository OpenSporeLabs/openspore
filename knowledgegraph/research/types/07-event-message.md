# 07 — Event, message, record, handler, dispatch, and command archaeology

## Scope and result

This partition characterizes the original event/message surface of `SporeApp.exe` 3.1.0.22 (`25d42a7a…d914e`, image base `0x00400000`) from committed SDK exports, dossiers, semantic atlas, global campaign tracks, decomp-gap holds, triage, xrefs, vtables, and current OpenSpore source comparison.

It is reverse-engineering documentation only. No OpenSpore implementation, `SPORE/` content, Ghidra program, binary, knowledge-graph database, or historical artifact was modified. No Ghidra program was open during this partition, so no live Ghidra result was used.

The central result is that there is **no universal event ABI**. At least nine distinct families coexist:

1. App refcounted messages and a central message manager.
2. UTFWin tagged-union UI messages routed through window procedures.
3. Game-mode lifecycle/input virtual dispatch.
4. Editor animation messages and refcounted animation events.
5. Deferred gameplay event value records.
6. UI feedback event records and a keyed event log.
7. Serializable civilization/space communication events.
8. Mode-specific anonymous space-event records.
9. Numeric UI commands and a separate pdtk text command language.

The current `InputEvent`, `InputFrame`, `SimEvent`, and `CellAnim` helpers are local clean-room contracts. They are useful comparisons, not evidence for original layouts or dispatch semantics.

## Evidence policy

| Evidence level | Meaning in this partition |
|---|---|
| `CONFIRMED_NAME_ONLY` | A community SDK name is anchored at an address; body semantics and runtime behavior remain unproved. |
| `OBSERVED` | Directly present in current source/artifacts; says nothing about original runtime semantics by itself. |
| `SUPPORTED` | Direct static body, structural layout, vtable, or multi-source agreement; no runtime verification. |
| `INFERRED` | Semantic interpretation from names, call shape, ownership, or neighboring types. |
| `UNKNOWN` | Material identity, layout, ownership, ordering, or behavior remains unresolved. |

Additional rules:

- SDK names/layouts are community-header provenance, not EA source and not proof of behavior.
- Decompilation is evidence, not truth; bad calling-convention and type propagation remain explicit.
- Xrefs prove structural dependence, not runtime execution or order.
- Vtable candidates are structural evidence, not RTTI or a complete hierarchy.
- Current source cannot backfill original semantics.
- No claim in this partition is runtime-verified.

Unless a field overrides it, every layout field inherits its type's evidence level, confidence, and provenance.

## Architecture map

```text
Win32 / DINPUT / GameInput
  -> cGameInputManager
  -> IGameMode input callbacks
  -> Cell / editor / camera consumers

App service
  -> StandardMessage or derived message
  -> IMessageManager::MessageSend / MessagePost
  -> cMessageManager listener map + unresolved 0x18-byte queue records
  -> IMessageListener::HandleMessage or MessageHandler_t

UTFWin widget/input conversion
  -> UTFWin::Message { source, eventType, payload union }
  -> Window WinProc list
  -> IWinProc filter/priority
  -> HandleUIMessage / InteractiveWinProc callback

Editor operation
  -> cEditorAnimEvent
  -> MessageSend or MessagePost
  -> recovered IAppSystem Init / InitPlugins slots
  -> unresolved animation/edit consumer route

Simulator communication
  -> cCommManager
  -> serializable cCommEvent
  -> mission/galaxy state and communication presentation

Space state/tool/trading cluster
  -> FUN_00e39ab0
  -> two anonymous allocated records
  -> unresolved 14-node state-handler SCC
```

## Type catalog

### App message value and parameter types

#### `App::StandardMessage::MessageParameter`

Size: **8 bytes**.

| Offset | Alternative fields |
|---:|---|
| `0x00` | `bool`, `int8_t`, `uint8_t`, `int16_t`, `uint16_t`, `int32_t`, `uint32_t`, `int64_t`, `uint64_t`, `float`, `double`, `Object*`, `void*`, `RefCountedString*` |

A `StandardMessage` owns five inline 8-byte parameter slots, but pointer targets have independent lifetime rules.

#### `App::StandardMessage`

Size: **64 bytes / `0x40`**.

| Offset | Size | Field |
|---:|---:|---|
| `0x00` | 4 | `MultithreadObject__vftable*` |
| `0x04` | 4 | `mnRefCount` |
| `0x08` | 40 | `MessageParameter params[5]` |
| `0x30` | 4 | `uint32_t id` |
| `0x34` | 4 | `int field_34` |
| `0x38` | 4 | `uint32_t objectFlags` |
| `0x3c` | 4 | `int field_3C` |

Exported derived records with the same 64-byte layout:

- `App::OnModeExitMessage`
- `App::OnModeEnterMessage`
- `App::SetGameModeMessage`
- `Simulator::MissionUpdateMessage`
- `Simulator::CombatantKilledMessage`
- `Simulator::PlayerEmpireAlliedMessage`
- `Simulator::PlayerEmpireLostAllianceMessage`
- `Simulator::ToolOnHitMessage`
- `Simulator::GameNounStatusChangedMessage`
- `Simulator::ScenarioCreatureHealedMessage`
- `Simulator::SpaceRareFoundMessage`

Only the three App mode records have exported IDs:

| Record | ID |
|---|---:|
| `OnModeExitMessage` | `0x0212d3e7` (`kMsgOnModeExit`) |
| `OnModeEnterMessage` | `0x022d1adc` (`kMsgOnModeEnter`) |
| `SetGameModeMessage` | `0x00e11333` (`kMsgSetGameModeByName`) |

The parameter-to-mode-ID mapping and the meanings of `field_34`, `objectFlags`, and `field_3C` remain unknown.

#### Heterogeneous transition messages

`Simulator::EnterModeMessage` is an 8-byte value:

| Offset | Field |
|---:|---|
| `0x00` | `uint32_t mModeID` |
| `0x04` | `uint32_t mPreviousModeID` |

`Simulator::EnterEditorMessage` is a 32-byte refcounted interface value:

| Offset | Field |
|---:|---|
| `0x00` | `IMessageParameters__vftable*` |
| `0x04` | `IVirtual__vftable*` |
| `0x08` | `int mnRefCount` |
| `0x0c` | `uint32_t mEditorID` |
| `0x10` | `ResourceKey mCreationName` (12 bytes) |
| `0x1c` | `int field_1C` |

`IMessageParameters` is a three-slot interface: virtual destructor, `AddRef`, and `Release`. These records are not proven to be `StandardMessage` subclasses.

### App listeners, handlers, and message manager

#### Listener interfaces

`IUnmanagedMessageListener` has one pointer and a two-slot vtable:

1. virtual destructor
2. `bool HandleMessage(uint32_t, void*)`

`IMessageListener` adds two slots:

3. `AddRef`
4. `Release`

Listener adapter layouts:

| Type | Size | Layout |
|---|---:|---|
| `DefaultMessageListener` | 8 | vptr, `mnRefCount@4` |
| `LambdaMessageListener` | 12 | vptr, `mnRefCount@4`, callback `@8` |
| `UpdateMessageListener` | 16 | vptr, refcount, void callback `@8`, `intrusive_ptr<IUpdatable>@12` |
| `App::ScheduledTaskListener` | 56 | vptr, refcount, `Clock@8`, callback `@0x20`, schedule/repeat/first times, executed flag |

`UpdateMessageListener` adapts a selected message into `IUpdatable::Update`; `ScheduledTaskListener` adapts timing into a callback. Neither adds a payload layout to the original message.

#### `MessageHandler_t` and `IMessageManager::Entry`

`MessageHandler_t` is:

```text
void handler(uint32_t, void*, void*)
```

`Entry` is **20 bytes / `0x14`**:

| Offset | Size | Field |
|---:|---:|---|
| `0x00` | 4 | `IMessageListener* mpListener` |
| `0x04` | 4 | `int mnPriority` |
| `0x08` | 1 | `bool mbRefCounted` |
| `0x09` | 3 | padding |
| `0x0c` | 4 | `MessageHandler_t mpHandler` |
| `0x10` | 4 | `void* mpObject` |

This is registration metadata. It is **not** the unresolved 0x18-byte record walked by `ProcessQueue`.

#### `App::IMessageManager`

The interface has 19 four-byte slots (`0x4c` bytes):

| Slot | Offset | Operation |
|---:|---:|---|
| 0 | `0x00` | virtual destructor |
| 1 | `0x04` | `Initialize` |
| 2 | `0x08` | `Dispose` |
| 3 | `0x0c` | `GetOption` |
| 4 | `0x10` | `SetOption` |
| 5 | `0x14` | `MessageSend(messageID, void*, IUnmanagedMessageListener*)` |
| 6 | `0x18` | `MessagePost(messageID, IMessageRC*, IMessageListener*)` |
| 7 | `0x1c` | `MessagePostFunction(messageID, IMessageRC*, int, handler, object)` |
| 8 | `0x20` | `AddListener` |
| 9 | `0x24` | `AddUnmanagedListener` |
| 10 | `0x28` | `AddHandler(function, object, messageID, refCounted, priority)` |
| 11 | `0x2c` | `RemoveListener` |
| 12 | `0x30` | `RemoveHandler` |
| 13 | `0x34` | `ProcessQueue(int,int,int)` |
| 14 | `0x38` | `ProcessQueue2` |
| 15 | `0x3c` | `GetMessageQueue` |
| 16 | `0x40` | `Lock(bool)` |
| 17 | `0x44` | `AddEntry(Entry*, messageID)` |
| 18 | `0x48` | `RemoveEntry(object, messageID, priority)` |

The ownership split is structural: `MessageSend` accepts an unmanaged pointer/listener, while `MessagePost` accepts `IMessageRC` and `IMessageListener`. Exact synchronous/asynchronous behavior is not proven by the names.

#### `App::cMessageManager`

Size: **200 bytes / `0xc8`**.

| Offset | Size | Field |
|---:|---:|---|
| `0x00` | 4 | `IMessageManager__vftable*` |
| `0x04` | 52 | opaque state |
| `0x38` | 48 | mutex |
| `0x68` | 4 | `int field_68` |
| `0x6c` | 4 | `int field_6C` |
| `0x70` | 32 | `hash_map<uint32, list<IMessageListener*>> mListeners` |
| `0x90` | 48 | listener mutex |
| `0xc0` | 6 | `bool[6]` options/state |
| `0xc6` | 2 | tail padding |

The persisted `ProcessQueue` body walks **0x18-byte records**, follows a **0xc0-sized range**, and releases referenced objects. The mapping of those records to the field map above is not settled.

`MessageListenerData` is a 20-byte object-level registration helper:

| Offset | Field |
|---:|---|
| `0x00` | `IMessageManager*` |
| `0x04` | `IMessageListener*` |
| `0x08` | `uint32_t* mpMessageIDs` |
| `0x0c` | `size_t mNumMessageIDs` |
| `0x10` | `int field_10` |

### UTFWin messages, windows, and procedures

#### `UTFWin::MessageType`

| Value | Name |
|---:|---|
| `0x01` | `kMsgKeyDown` |
| `0x02` | `kMsgKeyUp` |
| `0x03` | `kMsgKeyDown2` |
| `0x04` | `kMsgKeyUp2` |
| `0x05` | `kMsgKeyPress` |
| `0x06` | `kMsgMouseDown` |
| `0x07` | `kMsgMouseUp` |
| `0x08` | `kMsgMouseMove` |
| `0x09` | `kMsgMouseWheel` |
| `0x0a` | `kMsgRefresh` |
| `0x0c` | `kMsgUpdate` |
| `0x0d` | `kMsgPaint` |
| `0x0e` | `kMsgWindowChanged` |
| `0x10` | `kMsgLayout` |
| `0x11` | `kMsgElementAdded` |
| `0x12` | `kMsgElementRemoved` |
| `0x13` | `kMsgStateChanged` |
| `0x14` | `kMsgCollisionDetect` |
| `0x15` | `kMsgTransformed` |
| `0x17` | `kMsgButtonClick` |
| `0x18` | `kMsgButtonSelect` |
| `0x1b` | `kMsgMouseEnter` |
| `0x1c` | `kMsgMouseLeave` |
| `0x1000` | `kMsgWinProcAdded` |
| `0x1001` | `kMsgWinProcRemoved` |
| `0x287259f6` | `kMsgComponentActivated` |
| `0x9b1552da` | `kMsgTextChanged` |

Values `0x0b`, `0x0f`, `0x16`, `0x19`, and `0x1a` are absent from the exported enum and remain unknown.

`EventFlags` values are `0x01` basic input, `0x02` update, `0x04` paint, `0x08` window changed, `0x10` state changed, `0x40` refresh, `0x80` advanced, `0x108` layout, and `0x400` element.

#### `UTFWin::Message`

The SDK exporter emits a **12-byte base**:

| Offset | Field |
|---:|---|
| `0x00` | `IWindow* source` |
| `0x04` | `int field_04` |
| `0x08` | `int eventType` / `MessageType` |

Separate anonymous payload structures have fields named from logical offset `0x0c`, implying an effective footprint of at least `0x1c`. This is retained as a conflict rather than silently changing the SDK's exported size.

Recovered payload forms include:

- key down: three integers, including virtual key and modifiers;
- key up: event discriminator plus 16-bit virtual key;
- mouse down: `float x`, `float y`, mouse state, mouse button;
- mouse wheel: `float x`, `float y`, mouse state, wheel delta;
- WinProc add/remove: three integers plus a pointer-like field;
- refresh: `RefreshType` plus window pointer;
- update: three integers plus `Rectangle*`;
- state changed: old and new state;
- collision detect: `float x`, `float y`, mouse state, `bool*`;
- transformed: three integers plus `Matrix4*`;
- button click: `uint32_t commandID`;
- button select: command ID, integer, selected bool;
- text changed: three integers plus `TextChange*`;
- control ID: one `uint32_t` for an otherwise unknown event.

Some event-to-union associations remain inferred because the exporter emitted anonymous structures separately.

#### `IWindow` and `Window`

`IWindow` has 71 slots. Dispatch-relevant slots include:

- slot 8, `0x20`: `GetCommandID`
- slot 21, `0x54`: `SetCommandID`
- slot 65, `0x104`: `AddWinProc`
- slot 66, `0x108`: `RemoveWinProc`
- slot 67, `0x10c`: `GetNextWinProc`
- slot 69, `0x114`: `SendMsg`

`Window` is **524 bytes / `0x20c`** and uses two vptrs (`Window__vftable*` and `IWindow__vftable*`). Important fields:

| Offset | Field |
|---:|---|
| `0x08` | intrusive parent/previous link pair |
| `0x34` | `IWindowManager*` |
| `0x38` | parent `intrusive_ptr<Window>` |
| `0x3c` | child intrusive list (8 bytes) |
| `0x44` | fixed-pool allocator (32 bytes) |
| `0x64` | WinProc list (16 bytes) |
| `0x80` | `uint32_t mControlID` |
| `0x84` | `uint32_t mCommandID` |
| `0x88` | real-area rectangle |
| `0x98` | area rectangle |
| `0xa8` | cursor ID |
| `0xac` | state flags |
| `0xb0` | caption |
| `0xc0` | text font ID |
| `0xc4` | four 68-byte unknown matrices |
| `0x1d8` | shade color |
| `0x1dc` | fill color |
| `0x1e0` | drawable intrusive pointer |
| `0x1ec` | `hash_map<int,int>` |

#### `IWinProc` and `InteractiveWinProc`

Base `IWinProc` has seven slots: `AddRef`, `Release`, virtual destructor, `Cast`, `GetPriority`, `GetEventFlags`, and `HandleUIMessage`.

`InteractiveWinProc` has 32 slots and exposes callbacks for:

- key down/up variants, key press;
- mouse down/up/move/wheel and enter/leave;
- refresh and update;
- collision detection;
- element add/remove;
- layout and transform;
- WinProc add/remove;
- button click/select.

This is a strong structural match for priority/filter/handler dispatch, but runtime traversal and handled-result semantics remain unknown.

### Game-mode message and input dispatch

The SDK `IGameMode` vtable exports:

`AddRef`, `Release`, virtual destructor, `func0Ch`, `Initialize`, `Dispose`, `OnEnter`, `OnExit`, `func20h`, `OnKeyDown`, `OnKeyUp`, `OnMouseDown`, `OnMouseUp`, `OnMouseMove`, `OnMouseWheel`, `Update`.

A separate high-confidence 27-slot candidate at `0x01485550` identifies `App::cCellModeStrategy` slots:

| Index | VA | Name |
|---:|---:|---|
| 1 | `0x00e62700` | `HandleMessage` |
| 6 | `0x00e81cf0` | `Initialize` |
| 7 | `0x00e81f30` | `Dispose` |
| 8 | `0x00e552f0` | `OnEnter` |
| 9 | `0x00e7fc00` | `OnExit` |
| 11 | `0x00e818f0` | `OnKeyDown` |
| 12 | `0x00e51010` | `OnMouseMove` |
| 13 | `0x00e6c860` | `OnMouseDown` |
| 14 | `0x00e5c0f0` | `OnMouseUp` |
| 16 | `0x00e7d660` | `OnMouseWheel` |
| 17 | `0x00e80980` | `Update` |

The SDK order and concrete candidate order are not silently merged. The current source comments follow the concrete candidate but omit `OnKeyUp`; the current C++ interface is a clean-room abstraction, not the original ABI.

A medium-confidence editor candidate at `0x013f57a4` places `Editors::cEditor::HandleMessage` at sampled slot 6. The full window hierarchy behind that candidate is not recovered here.

The OS message pump root `0x00848210` appears in high/medium Canvas candidates at `0x0141ca70` and `0x0141cab8`; it is below the App/UTFWin/gameplay layers and represents `PeekMessageW`/`TranslateMessage`/`DispatchMessageW` plus frame dispatch.

### Unnamed handler/registration bridge

`FUN_00b21340` at `0x00b21340` is summarized by a dossier as a map/list callback bridge:

1. look up an ID with `map_int_whatever_find`;
2. if a result exists at context `+0x9c`, register through `FUN_00ba8420`;
3. otherwise resolve a non-empty name at context `+0x14`;
4. invoke `param_3(name)`;
5. walk linked-list state at `+0x6c..+0x78` with `0x0c` item stride;
6. invoke `param_5(item,id)` and `param_4(name,item)`;
7. clear and return the name buffer.

The function is not a recovered vtable member. The dossier calls it “message-handler registration”; the held decomp-gap record says not to relabel it and treats the identity as a generic map/callback bridge. Both positions are retained.

Counts are also source-attributed:

- dossier caller list: 10 examples;
- held reconciliation: 254 distinct callers;
- pinned TSV: 318 incoming direct-call edge rows.

These are different units, not a single reconciled caller total.

### Animation event records

#### `Anim::AnimationMessage`

Size: **24 bytes**.

| Offset | Field |
|---:|---|
| `0x00` | `uint32_t messageID` |
| `0x04` | `char* pName` |
| `0x08` | `AnimatedCreature* pCreature` |
| `0x0c` | `int blockIndex` |
| `0x10` | `int parameter0` |
| `0x14` | `float parameter1` |

This is not a `StandardMessage` subtype. Its dispatch table, message-ID catalog, and `pName` lifetime are unknown.

#### `Editors::cEditorAnimEvent`

Size: **48 bytes / `0x30`**.

| Offset | Field |
|---:|---|
| `0x00` | `IMessageRC__vftable*` |
| `0x04` | `DefaultRefCounted__vftable*` |
| `0x08` | `int mnRefCount` |
| `0x0c` | `int field_C` |
| `0x10` | `int field_10` |
| `0x14` | `EditorModel* mpEditorModel` |
| `0x18` | `uint32_t mEventID` |
| `0x1c` | `bool field_1C` |
| `0x20` | `float field_20` |
| `0x24` | `bool field_24` |
| `0x28` | `int field_28` |
| `0x2c` | `float field_2C` |

`cEditorAnimWorld` stores `vector<intrusive_ptr<cEditorAnimEvent>>` at `+0x24`.

`MessageSend` at `0x0059d8b0` and `MessagePost` at `0x0059d840` pack editor-model/event/scalar values and call distinct recovered `IAppSystem` slots (`Init` and `InitPlugins`). Their decompilation incorrectly types the packed local as `CommandLine`; that local type and inferred stack offsets are rejected as exact-layout evidence.

### Deferred gameplay events

`Simulator::tDeferredEvent` is **28 bytes**:

| Offset | Size | Field |
|---:|---:|---|
| `0x00` | 4 | `uint32_t mEventGuid` |
| `0x04` | 8 | `uint64_t mTriggerTime` |
| `0x0c` | 4 | `float mUserFloat1` |
| `0x10` | 4 | `float mUserFloat2` |
| `0x14` | 4 | `uint32_t mUserUint1` |
| `0x18` | 4 | `uint32_t mUserUint2` |

An `eastl::vector<tDeferredEvent>` is 20 bytes. The 64-bit trigger time begins at an unaligned offset `0x04` in the SDK structure. The record is value-like and has no vtable. Its owning scheduler, time epoch/unit, GUID namespace, ordering, duplicate policy, and callback are unknown.

### UI feedback events

`Simulator::cFeedbackEvent` is a 148-byte refcounted UI record. Important fields include event category indices, a `Vector3`, fade/remove times, context-change removal, current context, command ID, description string, item layout, and a four-integer field array.

`Simulator::cUIEventLog` is 112 bytes and implements `IWinProc`, `ISimulatorStrategy`, and `IVirtual`. It tracks last/current game mode and owns:

```text
map<uint32, intrusive_ptr<cFeedbackEvent>> mEvents @ +0x28
```

plus timing/visibility state and a property list at `+0x6c`. This family owns active UI feedback and mode-context visibility; it is not the App message queue and not `cCommEvent` persistence.

### Serializable communication events

`Simulator::cCommEvent` is **160 bytes / `0xa0`**:

| Offset | Field |
|---:|---|
| `0x00` | `ISimulatorSerializable__vftable*` |
| `0x04` | `IVirtual__vftable*` |
| `0x08` | `int mnRefCount` |
| `0x0c` | `cCommEventType mEventType` |
| `0x10`, `0x14` | two unknown integers |
| `0x18`, `0x1c` | source and target political IDs |
| `0x20`–`0x2c` | source/target city and civilization intrusive pointers |
| `0x30` | visible-in-galaxy flag |
| `0x34` | planet key |
| `0x38` | file ID |
| `0x3c` | dialog ID |
| `0x40` | mission intrusive pointer |
| `0x44` | priority |
| `0x48` | duration |
| `0x4c` | elapsed time |
| `0x50`, `0x64`, `0x78`, `0x8c` | four 20-byte `vector<int>` fields |

Producers include `cCommManager::CreateSpaceCommEvent` and `CreateCivCommEvent`; `ShowCommEvent` is a named consumer. `cMission` and galaxy state hold intrusive references. The first vtable explicitly establishes `ISimulatorSerializable` ownership, but the codec/version/defaulting rules remain unknown.

### Anonymous space-event record pair

`FUN_00e39ab0` at `0x00e39ab0` builds two allocated records, described by the dossier as 27-field and 24-field structures. Exact sizes, field offsets, and type names are absent from the SDK.

Observed contents are:

- object reference;
- cell IDs populated through `0x00e39450`/`0x00e39420`;
- timestamp computed as `FUN_00b316c0()/1000` and interpreted as millisecond-like;
- slot default `-10` from raw constant `0x53dbcf2`;
- additional IDs;
- float3 positions from arguments or `cTribe+0x504/+0x508/+0x50c`;
- trailing writes observed around `+0x64/+0x68`, semantics unknown.

The pinned graph has 16 distinct callers, 18 incoming direct-call rows, 15 distinct callees, 25 outgoing rows, and an SCC size of 14. Named/SDK-anchored contexts include `cSpaceTrading::ObtainTradingObject` and `cDefaultBeamTool::WhileFiring`. The records are space-mode state-handler data, not `SimEvent`, `StandardMessage`, or `UTFWin::Message`.

### Command surfaces

Three different command meanings must remain separate:

1. **UTFWin numeric command identity:** `Window.mCommandID@0x84` and button-message `uint32_t commandID` payloads.
2. **pdtk text command language:** `pdtk_text_new`, resize, select, focus, and icursor strings built by `0x00a4e9c0`; the complete grammar is unknown.
3. **Other SDK names containing “Command”:** `ArgScript::ICommand` (parser command), `App::CommandLine` (process arguments), and `ICreatureModeActionHandler::ExecuteAction` (creature action). These are not evidence of one command ABI.

The pdtk builder also writes new widget width, height, and cursor, and emits blue/black selection colors.

## Registration and dispatch lifecycles

### App message bus

```text
Initialize
  -> AddListener / AddUnmanagedListener / AddHandler / AddEntry
  -> MessageSend / MessagePost / MessagePostFunction
  -> select listener/handler entries by message ID and priority
  -> ProcessQueue / ProcessQueue2
  -> invoke listener or callback
  -> release referenced payloads at the manager boundary
  -> RemoveListener / RemoveHandler / RemoveEntry
  -> Dispose
```

Known:

- listener map is keyed by 32-bit message ID;
- registration metadata stores priority, refcount flag, handler, and object;
- two mutex regions exist;
- queue processing walks 0x18-byte records and releases objects.

Unknown:

- queued record layout;
- priority direction and tie order;
- send/post timing;
- handled/consume semantics;
- lock and thread rules;
- exact payload-release timing.

### UTFWin window/proc bus

```text
construct Window
  -> insert into parent/child intrusive list
  -> AddWinProc
  -> construct Message(source, eventType, payload)
  -> Window::SendMsg
  -> proc priority/event-flag filtering
  -> HandleUIMessage
  -> event-specific InteractiveWinProc callback
  -> RemoveWinProc / dispose window family
```

Exact bubbling, return handling, and thread affinity are unresolved.

### Game mode

```text
register mode + mode ID
  -> activate mode
  -> lifecycle transition
  -> key/mouse callbacks
  -> Update
  -> cleanup/dispose
```

The API and concrete Cell vtable establish the surfaces. Original ordering between old-mode exit, new-mode enter, and mode messages is not runtime-verified.

### Editor animation events

```text
populate cEditorAnimEvent
  -> MessageSend or MessagePost
  -> pack message-like local value
  -> IAppSystem Init or InitPlugins slot
  -> unresolved animation/edit consumer
```

Send versus Post is observable at the recovered slot boundary; queue timing and final ownership are not.

## Producer/consumer relationships

| Producer | Carrier | Consumer/owner | Status |
|---|---|---|---|
| OS input / `GameInput` | normalized input state and mode callbacks | `cGameInputManager`, `IGameMode`, camera/editor/UI | `SUPPORTED` |
| App services/mode manager | `StandardMessage` | `IMessageListener` / `MessageHandler_t` through `cMessageManager` | `SUPPORTED` |
| UTFWin widgets/input conversion | `UTFWin::Message` | Window proc list / `IWinProc` | `SUPPORTED` |
| `cEditor` operations | `cEditorAnimEvent` / animation-like value | IAppSystem slots, then unresolved animation consumer | `INFERRED` |
| `cCommManager` | serializable `cCommEvent` | mission/galaxy/communication presentation | `SUPPORTED` |
| gameplay feedback systems | refcounted `cFeedbackEvent` | `cUIEventLog` keyed event map / UTFWin layout | `SUPPORTED` |
| space trading/tool cluster | two anonymous records | unresolved SCC state handlers | `INFERRED` |
| UTFWin text widget | pdtk command strings | runtime pdtk toolkit | `SUPPORTED` |
| current SDL/CellInput | current `InputFrame` | current `CellSim` | `OBSERVED` |
| current `CellSim` | current `SimEvent` vector | tests/manifests | `OBSERVED` |

## Serialization and semantic ownership

| Type | Classification | Persistence/lifetime evidence |
|---|---|---|
| `StandardMessage` and derived records | runtime message | refcount and manager release boundary; no persistence codec |
| `UTFWin::Message` | transient dispatch value | POD/tagged union; no serializer |
| `AnimationMessage` | transient animation record | POD pointers and parameters; no owning container recovered |
| `cEditorAnimEvent` | refcounted runtime message | `IMessageRC`, `DefaultRefCounted`, intrusive vector |
| `tDeferredEvent` | scheduler value | vector-owned POD; processing owner unknown |
| `cFeedbackEvent` | runtime UI feedback | refcount and keyed intrusive map; not persistent |
| `cCommEvent` | serializable domain event | `ISimulatorSerializable` first vtable; codec unknown |
| anonymous space pair | mode-specific runtime records | allocation/SCC use only; codec unknown |
| pdtk commands | ephemeral text protocol | formatted strings consumed by toolkit |
| current `SimEvent` | local observation serialization | state/manifest output; not original |

Semantic ownership does not cross families:

- `cMessageManager` owns App routing metadata, queues, lock state, and payload release boundary.
- `Window` owns window hierarchy, command/control identity, and WinProc list.
- Game-mode managers own activation and lifecycle callback targets.
- `cUIEventLog` owns active feedback-event lifetime and mode-context visibility.
- `cCommEvent` belongs to communication/mission simulation and persistence.
- The space record pair belongs to the space state/tool subsystem.
- Current `SimEvent` belongs only to the local deterministic harness.

## Current OpenSpore comparison

| Current source | Original comparison | Result |
|---|---|---|
| `gamemode::InputEvent` (virtual key, modifiers, x, y) | UTFWin input payload / `IGameMode` callbacks | local 16-byte value; interactive path bypasses callbacks |
| `cellinput::Key`, `Action`, `Frame`, `CameraDirs` | GameInput/input manager/mode routing | richer local held-state contract; not an original message |
| `sim::InputFrame` | normalized input to simulation | local deterministic bridge; not serialized message |
| `sim::SimEvent` (frame, type, entity) | none established | eat/flee observation vector; explicitly not original ABI |
| `CellAnim` event/effect mapping | Cell animation/effect and `AnimationMessage` | pure tested helper, not wired into `cell_stage`; no original event-to-pose path |

No current counterpart exists for `IMessageManager`, `StandardMessage`, UTFWin windows/procs, `AnimationMessage`, `cEditorAnimEvent`, `tDeferredEvent`, `cFeedbackEvent`, `cCommEvent`, the space pair, or pdtk.

## Preserved conflicts

1. `FUN_00b21340`: “message-handler registration” dossier label versus held instruction not to relabel a generic map/list bridge.
2. Handler caller counts: 10 listed examples, 254 distinct reconciled callers, 318 raw incoming direct-call rows.
3. `IMessageManager::Entry` is `0x14`; `ProcessQueue` records are `0x18`; they are not the same type.
4. `cEditorAnimEvent` decompilation says `CommandLine`; SDK says `cEditorAnimEvent`/`IMessageRC`.
5. SDK `IGameMode` slot order differs from the concrete 27-slot Cell candidate and current interface comments.
6. SDK `UTFWin::Message` base size is `0x0c`; anonymous payload fields imply at least `0x1c`.
7. Semantic-atlas `cMessageManager` associations differ from several `sdk_functions.tsv` addresses.
8. `Window::SendMsg` and `GetMessageQueue` decompilation is too type-unsafe for exact traversal claims.
9. Current `InputEvent`/`SimEvent` are local contracts, not original ABI.
10. The two space records have no exact layout despite a detailed static summary.

## Open questions

- Complete App message-ID and payload catalog.
- 0x18-byte queue-record layout and its relationship to 0x14-byte `Entry` records.
- Priority direction, tie order, and handled/consume behavior.
- Exact Send/Post/PostFunction timing and ownership.
- UTFWin proc ordering, bubbling, filters, and handled results.
- Exact anonymous `Message` union-to-`MessageType` mapping.
- Context owner, callback roles, and list invariants of `FUN_00b21340`.
- Exact sizes/offsets/types/consumers/lifetime of the two space records.
- `AnimationMessage` dispatch table and `cEditorAnimEvent` final consumer.
- Owner and ordering rules for `vector<tDeferredEvent>`.
- Versioned `cCommEvent` stream codec and vector/defaulting behavior.
- Complete pdtk grammar and response protocol.

## Primary provenance

- `docs/analysis/dossiers/unknown-high/message-handler-registration.json`
- `docs/analysis/dossiers/unknown-high/space-event-record-pair.json`
- `docs/analysis/dossiers/unknown-high/pdtk-text-widget.json`
- `knowledgegraph/research/decomp-gap/hold-infrastructure.json`
- `knowledgegraph/research/semantic-atlas.json`
- `knowledgegraph/research/global-campaign-2026/track-d-sim-cell.json`
- `knowledgegraph/research/global-campaign-2026/track-f-empire-economy.json`
- `knowledgegraph/research/global-campaign-2026/track-g-editor-ui-input.json`
- `knowledgegraph/research/global-campaign-2026/track-j-dependency-graph.json`
- `knowledgegraph/research/global-campaign-2026/track-k-engine-boundaries.json`
- `knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl`
- `knowledgegraph/triage/xrefs-2540f2ca.tsv`
- `docs/analysis/vtables.json`
- `.spore-analysis/ghidra-exports/spore_sdk.xml`
- `.spore-analysis/ghidra-exports/structs_fields.tsv`
- `.spore-analysis/ghidra-exports/structs.tsv`
- `.spore-analysis/ghidra-exports/sdk_functions.tsv`
- `.spore-analysis/ghidra-exports/decompiled_sdk/App__cMessageManager__ProcessQueue.c`
- `.spore-analysis/ghidra-exports/decompiled_sdk/App__cMessageManager__GetMessageQueue.c`
- `.spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__SendMsg.c`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__HandleMessage.c`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditorAnimEvent__MessageSend.c`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditorAnimEvent__MessagePost.c`
- `src/apps/IGameMode.hpp`
- `src/apps/CellInput.hpp`
- `src/apps/CellAnim.hpp`
- `src/sim/Sim.hpp`

The machine-readable companion is `knowledgegraph/research/types/07-event-message.json`; it contains the complete field, vtable, relationship, conflict, unknown, confidence, and source-reference records.
