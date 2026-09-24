# Editor and UI Types — Archaeology Partition 06

## Scope

This partition reconstructs the original editor, input/controller, UTFWin/pdtk widget, window, menu, rendering, and UI-object type system for `SporeApp.exe` 3.1.0.22 (`x86:LE:32`, image base `0x00400000`). It is research-only: no implementation, binary, Ghidra project, triage artifact, or database was changed. No program was open in Ghidra, so no live query was made.

Names are hypotheses unless corroborated by SDK layout, exact symbols, vtable stores, direct body evidence, or independent consumers. The binary has no MSVC RTTI; scanner-proposed tables and inheritance remain structural evidence, not language-level proof.

### Evidence vocabulary

| Level | Meaning |
|---|---|
| **OBSERVED** | Present in committed bytes, exports, source, or a read-only body/assembly observation. |
| **SUPPORTED** | Independent static sources agree; no positive original runtime trace exists. |
| **INFERRED** | Bounded interpretation from topology, naming, partial decompilation, or adjacent contracts. |
| **UNKNOWN** | Evidence does not establish identity, ABI, ownership, or behavior. |

The JSON companion is authoritative and contains per-type evidence, provenance, confidence, complete selected offsets, source catalog, and machine-readable ownership/factory/serialization records.

## Main conclusions

1. **`Editors::cEditor` is the editor root, not a widget.** It is a 1536-byte reference-counted multiple-inheritance object implementing `IGameMode`, `ILayer`, `IHintConditioner`, `INameableEntity`, `IMessageListener`, and `DefaultRefCounted`. Six adjacent vptrs occupy offsets `0x00`–`0x14`; `mnRefCount` is at `0x18`. **SUPPORTED / high confidence.**
2. **The `cEditor` vtable candidate at `0x013f57f8` has 29 slots, but `App::IGameMode` has 16.** The first 16 slots align exactly with the SDK `IGameMode` contract; the remaining slots are additional editor/base virtuals or adjacent continuations. **OBSERVED / high confidence.**
3. **UTFWin is the central replaceable infrastructure boundary.** It supplies the 71-slot window interface, 7-slot message-proc interface, resource-backed layouts, drawable painting, widget adapters, and 1093-function subsystem. **SUPPORTED / high confidence.**
4. **Input is centralized in `Simulator::cGameInputManager` plus embedded `GameInput` state.** The manager has 27 slots, explicit key/mouse callbacks, current/last mode fields, and input-region state; its accessor has 614 total and 80 gameplay callers. **SUPPORTED / high confidence.**
5. **The pdtk text bridge is observable but not an SDK ABI.** `FUN_00a4e9c0` constructs `pdtk_text_new`, selection, focus, and cursor commands while returning widget size/cursor state. **SUPPORTED / high confidence.**
6. **A distinct menu type is not established.** No committed SDK function or structure name contains `Menu`; the main menu is best treated as layout/window/button/message composition. **UNKNOWN / medium confidence.**
7. **Editor serialization exists but is not replaceable yet.** `EditorModel::Load/Save` and `cCreatureDataResource::Read/Write` are contained SDK labels; exact file grammar and ABIs remain unknown. **SUPPORTED / medium confidence.**
8. **The current tree has useful cell slices, not the original editor/UI infrastructure.** Current `CellInput`, `CellModeStrategy`, `CellUI`, and `IRenderer` are bounded clean-room approximations; general UTFWin, message-manager, pdtk, editor-model, layered renderer, and animation/UI-object behavior is absent. **SUPPORTED / high confidence.**

## Type catalog

### Editor root, model, and history

| Type | Size | Recovered type facts | Name status | Evidence | Level / confidence |
|---|---:|---|---|---|---|
| `Editors::cEditor` | 1536 | Six vptrs; mouse state; EditorUI/PlayMode; lighting/model/effect/shadow worlds; EditorModel; active/moving/selected rigblocks; two intrusive history vectors; EditorNamePanel; cEditorAnimWorld; palettes; `mMode @ 0x31c`. | Corroborated layout/method family; constructor spelling remains bounded. | E02, E03, E05, E06, E15, E20 | SUPPORTED / high |
| `Editors::EditorModel` | 224 | `INameableEntity + IVirtual + DefaultRefCounted`; ResourceKey; intrusive rigblocks; model type; name/description/accepted name; three colors; bounding boxes. | Corroborated by layout, `SetColor`, and load/save boundaries. | E02–E05, E15, E18 | SUPPORTED / high |
| `Editors::EditorStateEditHistory` | 44 | Refcount, budget, mode, and state fields. | SDK-layout corroborated. | E02, E03, E15 | SUPPORTED / high |
| `Editors::cEditorResource` | 172 | Resource key, properties, and block vector; paired with state-history snapshots. | Paired history-record hypothesis. | E02, E03, E15 | SUPPORTED / medium |
| `Editors::EditorRigblock` | 3592 | `DefaultRefCounted + Object`; PropertyList; model/world; IDs; EditorModel back-pointer; position/orientation; handles; parent rigblock. | Corroborated SDK layout; dynamic subtype unknown. | E02–E04 | SUPPORTED / high |

### Editor UI, play mode, camera, and animation

| Type | Size / slots | Recovered type facts | Name status | Evidence | Level / confidence |
|---|---:|---|---|---|---|
| `Editors::EditorCamera` | 236 | `ICamera + IMessageListener + IVirtual`; embedded `GameInput @ 0xa0`; zoom/translate/rotate scales; camera position; clip/FOV limits; viewer back-pointer. 27-slot candidate `0x014105ac`. | Corroborated. | E02–E05, E07 | SUPPORTED / high |
| `Editors::EditorUI` | 300 | Four interface vptrs; main/shared/camera-control layouts; editor back-pointer; raw window handles; message listener/manager/ID registry. | Corroborated. | E02–E04, E08 | SUPPORTED / high |
| `Editors::EditorPlayMode` | 22416 | Ten-slot vtable; intrusive PlayModeUI; main actor; four raw module pointers; embedded animations/backgrounds; editor back-pointer; environment reaction and button IDs. | Corroborated. | E02–E04, E07, E15 | SUPPORTED / high |
| `Editors::IPlayModeModule` | 4 + 48-byte vtable | Load, Dispose, OnEnter/Exit/Update, mouse/key, and HandleUIButton slots. | Corroborated SDK contract. | E02, E03 | SUPPORTED / high |
| `Editors::PlayModeUI` | 112 | `IWinProc + DefaultRefCounted`; editor/play-mode back-pointers; two layouts; clock/state. | Corroborated. | E02–E04 | SUPPORTED / high |
| `Editors::PlayModeAnimations` | 140 | Four-slot vtable; editor back-pointer; intrusive panel vector; animation/button/panel state. | Corroborated. | E02–E04 | SUPPORTED / high |
| `Editors::PlayModeBackgrounds` | 72 | Background vector; current/target indices and effect IDs; PlayModeUI back-pointer; lighting world. | Corroborated. | E02–E04 | SUPPORTED / high |
| `Editors::EditorCreatureController` | 136 | Intrusive AnimatedCreature; raw model world; current animation; real/target/current positions; target/current angle; movement/rotation speeds; look-at vectors. | Corroborated. | E02–E04, E07 | SUPPORTED / high |
| `Editors::cEditorAnimWorld` | 72 | Intrusive creature-controller map; event vector; IAnimWorld/EditorAnimations/IModelWorld; next creature index. | Corroborated. | E02–E04, E07 | SUPPORTED / high |
| `Editors::cEditorAnimEvent` | 48 | `IMessageRC + DefaultRefCounted`; EditorModel pointer, event ID, and scalar event parameters. | Corroborated. | E02–E04, E07, E15 | SUPPORTED / high |

### Input and application messages

| Type | Size / slots | Recovered type facts | Name status | Evidence | Level / confidence |
|---|---:|---|---|---|---|
| `GameInput` | 72 | 256-bit key set; modifiers; eight mouse buttons; position/button/click/mouse-state/wheel fields. | Corroborated. | E02–E04, E16 | SUPPORTED / high |
| `App::IGameMode` | 4 + 64-byte vtable | 16 slots: AddRef/Release/dtor/Cast, Initialize, Dispose, OnEnter/Exit, key/mouse callbacks, Update. | Corroborated. | E03, E04, E19 | SUPPORTED / high |
| `Simulator::cGameInputManager` | 276 / 27 slots | Four vptrs; last/current mode; two maps; mouse state; three input-region records; strings/vector; explicit six input callbacks at slots 19–24. | Corroborated. | E03, E04, E06, E07, E16 | SUPPORTED / high |
| `App::IMessageManager` | 4 + 76-byte vtable | 19 slots for lifecycle, options, send/post, listeners/handlers, queues, lock, and entry removal. | Corroborated API. | E02–E04, E17 | SUPPORTED / high |
| `App::cMessageManager` | 200 | Mutexes, listener maps, state bytes, and 0x18-byte message entries in 0xc0-byte ranges. | Corroborated concrete layout; ordering incomplete. | E02, E03, E17 | SUPPORTED / high |
| `App::StandardMessage` | 64 | Refcount, five `MessageParameter` slots, ID, and object flags. | Corroborated. | E02, E03 | SUPPORTED / high |

### UTFWin, widgets, and rendering objects

| Type | Size / slots | Recovered type facts | Name status | Evidence | Level / confidence |
|---|---:|---|---|---|---|
| `UTFWin::IWindow` | 12 + 284-byte vtable | 71 slots for IDs/state/geometry/layout/drawable/hit-testing/children/z-order/lookup/win-procs/messages. | Corroborated. | E02–E05, E13 | SUPPORTED / high |
| `UTFWin::Window` | 524 | Primary plus `IWindow` vptr; intrusive parent/children/drawable; manager; allocator; win-proc list; IDs; areas; flags; caption/font; transform blocks; color; object map. | Corroborated. | E02–E05 | SUPPORTED / high |
| `UTFWin::Message` | 12 | Tagged union for key, mouse, wheel, window, renderer, refresh, and other payloads. | Corroborated; variants/IDs unresolved. | E03, E04, E10 | SUPPORTED / high |
| `UTFWin::IWinProc` | 4 + 28-byte vtable | AddRef/Release/dtor/Cast, priority, event flags, HandleUIMessage. | Corroborated. | E02–E04 | SUPPORTED / high |
| `UTFWin::LambdaProc` | 20 | Function pointer, event flags, priority. | Corroborated. | E02, E03 | SUPPORTED / high |
| `UTFWin::UILayout` | 24 | Refcount, ResourceKey, intrusive UILayoutObjects. | Corroborated. | E02–E04, E10 | SUPPORTED / high |
| `UTFWin::UILayoutObjects` | 156 | Two ID maps, root components, name, container window, visibility/state. | Corroborated. | E02, E03, E10 | SUPPORTED / high |
| `UTFWin::ILayoutElement` | 4 + 24-byte vtable | Refcount/dtor/Cast plus serializer and proxy ID. | Corroborated. | E02–E04 | SUPPORTED / high |
| `UTFWin::SimpleLayout` | 20 / 34 slots | Layout-style implementation with apply/revert/serializer boundaries. | Corroborated. | E02–E04 | SUPPORTED / high |
| `UTFWin::ProportionalLayout` | 32 / 34 slots | Parallel 34-slot layout-style implementation. | Corroborated. | E02–E04 | SUPPORTED / high |
| `UTFWin::IDrawable` | 4 + 32-byte vtable | Refcount/dtor/Cast, Paint, collision, dimensions, collision policy. | Corroborated. | E02–E05 | SUPPORTED / high |
| `UTFWin::IButton` | 4 + 112-byte vtable | Window conversion, type/state/flags/alignment/group/caption/drawable/outline. | Corroborated. | E02–E04 | SUPPORTED / high |
| `UTFWin::ITextEdit` | 4 + 160-byte vtable | Style/color/border/caret/wrap, text, selection, cursor, anchor, and edit flags. | Corroborated. | E02–E04 | SUPPORTED / high |
| `UTFWin::IText` | 4 + 60-byte vtable | Fifteen text-interface slots. | Corroborated; full semantics not required here. | E02, E03 | SUPPORTED / high |
| `UTFWin::IImageDrawable` | 4 + 72-byte vtable | Drawable conversion, image, flags, tiling, scale, alignment, dimensions, serializer. | Corroborated. | E02–E04 | SUPPORTED / high |
| pdtk text widget | Unknown | Opaque runtime toolkit object updated through `pdtk_text_new`, `select`, `focus`, and `icursor`; size/cursor outputs. | Structural hypothesis only. | E06, E11 | SUPPORTED / high |
| main-menu type | Unknown | No SDK `Menu` type; behavior is presumed composition until traced. | UNKNOWN. | E10, E12, E21 | UNKNOWN / medium |
| `UI::EditorNamePanel` | 56 / 8 slots | IWinProc-like panel plus IMessageListener/refcount; validation proc; layout; nameable entity; randomized-name type; text; container window. | Corroborated; several SDK methods are contained aliases. | E02–E04, E10 | SUPPORTED / high |
| `UI::Window` | Unknown | Exact Itanium constructor; opaque count/storage/scalars; concrete higher-level meaning unknown. | Exact symbol, unknown type. | E04, E06, E10 | SUPPORTED / medium |
| `UI::cSPUITextZoom` | 120 | Refcount plus 112 unnamed bytes; targeted Initialize accesses style/resource and associated-object offsets. | Corroborated name/size, partial fields. | E02–E04, E10 | SUPPORTED / high |
| `Simulator::Cell::cCellUI` | 2372 | Embedded GameInput; global layout; progress bar; rollover pool; zoom; hovered name; input flags. | Corroborated. | E02–E04, E07, E19 | SUPPORTED / high |
| `Simulator::Cell::cCellUIRollover` | 56 | Object/cell indices, eight float/int slots, disappearance time, layout pointer. | Corroborated. | E02, E03, E19 | SUPPORTED / high |
| `Graphics::IRenderer` | 4 + 144-byte vtable | 36 slots for lifecycle/display, viewer/render, layers, jobs, flags, and budget. | Corroborated; current renderer is reduced. | E02–E04, E07, E13, E19 | SUPPORTED / high |
| `UI::cLayerManager` / `cSPUILayeredObject` / `Graphics::ILayer` | 152 / 124 / 4 | Intrusive UI layer registry; viewer/window-proc/transform state; renderer layer DrawLayer contract. | Corroborated. | E02–E04 | SUPPORTED / high |
| `UI::SpaceGameUI` | 1708 | Cross-stage example: IWinProc/message listener; layouts, palettes, tool panels, minimap, and listener data. | Corroborated. | E02–E04, E10 | SUPPORTED / high |

## Vtables and inheritance

### `cEditor`

The scanner and constructor independently place `0x013f57f8` at `cEditor + 0x00`. The candidate's first 16 slots match `App::IGameMode`:

| Slot | Committed target |
|---:|---|
| 0–3 | AddRef/Release/dtor/Cast |
| 4 | `Editors::cEditor::Initialize` |
| 5 | `Editors::cEditor::Dispose` |
| 6 | SDK OnEnter address; one-byte function, scanner marks it inside another function |
| 7 | `Editors::cEditor::OnExit` |
| 8 | Unknown hook |
| 9 | `OnKeyDown` |
| 10 | `OnKeyUp` |
| 11 | `OnMouseDown` |
| 12 | `OnMouseUp` |
| 13 | `OnMouseMove` |
| 14 | `OnMouseWheel` |
| 15 | `Update` |

Slots 16–28 remain additional/adjacent virtuals. The current `src/apps/IGameMode.hpp` comments are not authoritative: they label Initialize as slot 6 and Update as slot 17, while the SDK layout places them at slots 4 and 15.

### UTFWin scanner chains

The committed scanner reports twelve 21-slot-prefix chains. Bases `0x013fa974` and `0x01419794` each relate to derived candidates `0x01442604`, `0x014434fc`, `0x013fa794`, `0x013fef9c`, `0x0141a024`, and `0x01442324`. This supports a UTFWin hierarchy hypothesis, but no class names or RTTI can be assigned from prefix sharing alone.

### Other interfaces

| Interface | Slots |
|---|---:|
| `IGameMode` | 16 |
| `cGameInputManager` | 27 |
| `IMessageManager` | 19 |
| `IWindow` | 71 |
| `IWindowManager` | 24 |
| `IWinProc` | 7 |
| `IDrawable` | 8 |
| `IButton` | 28 |
| `ITextEdit` | 40 |
| `IText` | 15 |
| `IImageDrawable` | 18 |
| `IRenderer` | 36 |
| `ILayer` | 4 |

## Ownership and lifecycle

- **`cEditor` is the reference-counted owner.** Intrusive members include services, worlds, models, selected parts, skins, history, palettes, name panel, animation world, and event. Child UI/play-mode types use raw back-pointers to `cEditor`, so the ownership graph is not a simple cycle contract.
- **Construction is not fully persisted.** `_ZN6EditorC2Ev @ 0x0057ce80` stores `0x013f57f8` and five additional vtable addresses. Its only canonical direct caller is `0x0057f3e0`; readiness remains `NEEDS_RE` because the body was not persisted.
- **Initialize/Dispose are asymmetrically observed.** Initialize allocates/replaces services, UI, render worlds, viewers, listeners, and message registrations. Dispose releases intrusive members, removes graphics registrations, clears state, and tears down mode/UI resources. Exact cleanup order remains open.
- **History is snapshot-based.** `CommitEditHistory` allocates a `0x2c` state-history record, allocates a `0xac` resource through `0x004b9c70`, appends both to intrusive vectors, updates `mEditHistoryIndex`, and refreshes UI/model state.
- **Windows own a tree.** `Window` has intrusive parent/child/drawable/proc relationships; disposal is expressed through window-family APIs.
- **Messages are registry-driven.** Entries hold listener, priority, handler, object, and refcount flag. Queue blocks and entry stride are observed, but priority direction, reentrancy, and exact dispatch order are not.
- **Animation is a bridge, not UI storage.** `cEditorAnimWorld` owns controllers/events; controllers interpolate target position/angle and invoke AnimatedCreature/model-world state; `cEditorAnimEvent::Send/Post` crosses `IAppSystem` virtuals.

## Factories and serialization

| Boundary | Recovered fact | Status |
|---|---|---|
| Editor constructor | `0x0057ce80`, exact Itanium symbol; cEditor association via vtable stores. | SUPPORTED / medium |
| Generic UTFWin allocation | `UTFWinObject::new_` and `GetAllocator` recur in scanner candidates but do not identify one concrete constructor contract. | INFERRED / medium |
| Button | `UTFWin::IButton::Create @ 0x009670a0`. | SUPPORTED / high |
| Text edit | `UTFWin::ITextEdit::Create @ 0x0098caa0`. | SUPPORTED / high |
| Layout | `UILayout::Load @ 0x008121c0`, `LoadByName @ 0x00812250`, ResourceKey-backed. | SUPPORTED / high |
| Text zoom | `0x00989000` returns/creates a cSPUITextZoom-compatible object in the targeted UI-shell partition. | INFERRED / medium |
| Animation event | `cEditorAnimEvent__ctor @ 0x0059d960`; `SetActiveMode` allocates `0x30` bytes before construction. | SUPPORTED / high |
| Editor model | SDK Load `0x004ae8d0` is contained in `0x004ae3b0`; Save `0x004af780` is contained in `0x004af260`. | SUPPORTED / medium |
| Creature resource | SDK Read `0x004bf970` is contained in `0x004bf770`; Write `0x004bfcb0` is contained in `0x004bfc40`. | SUPPORTED / medium |
| Editor save orchestrator | `Editor_Save @ 0x00577650` has one direct caller, 22 unique callee destinations, 39 direct calls, and reaches editor resource, mode-manager, render-target, metadata, and allocation paths. | INFERRED / medium |
| UTFWin resources | ResourceKey, Load/LoadByName, SetSerializer, proxy IDs, and layout object maps establish serialized resource composition; grammar is unknown. | SUPPORTED / medium |
| pdtk text | Runtime command strings, not a serialized object format. | SUPPORTED / high |
| Game settings | `GameSettings::Show` materializes App string16 property arrays into an unknown owner container. | SUPPORTED / medium |

No pdtk dossier identified DBPF resource links for the text-widget wrapper. `pdtk` should be treated as a runtime toolkit interface, not a package format without new evidence.

## Consumers and flows

### Input to editor

```text
OS/DINPUT/GameInput state
  -> cGameInputManager mode/input-region routing
  -> IGameMode key/mouse callback
  -> cEditor mouse/tool/model mutation
  -> edit history and UI refresh
```

**SUPPORTED / high confidence.** The manager routing body and input-region meaning remain unknown.

### Editor to renderer and animation

```text
cEditor state
  -> IModelWorld / ILightingWorld / IEffectsWorld / IShadowWorld
  -> Graphics layer/model update
  -> IRenderer draw/render jobs
```

```text
cEditor mode/action
  -> cEditorAnimWorld / EditorCreatureController targets
  -> AnimatedCreature / IAnimWorld
  -> cEditorAnimEvent Send/Post through IAppSystem
```

Both flows are **SUPPORTED / high confidence**; event IDs, exact dispatch order, and pose synchronization remain open.

### Layout to window to panel

```text
ResourceKey / UILayout::Load
  -> UILayoutObjects and container window
  -> Window children / IDrawable / IWinProc
  -> priority-filtered UI message
  -> EditorUI / PlayModeUI / EditorNamePanel
  -> editor/game state mutation
```

**SUPPORTED / high confidence.** `Window::SendMsg` and `DoMessage` bodies are not type-safe enough to recover complete ordering.

### pdtk text synchronization

```text
text + font + mode(0 skip, 1 create, 2 update)
  -> line wrapping and widget measurement
  -> pdtk_text_new / select / focus / icursor
  -> updated width, height, cursor
```

**SUPPORTED / high confidence.** Five direct callers are in `0x00a4e190`–`0x00a4f380`.

### Main menu to cell

```text
rendered main menu
  -> input/message event
  -> editor/game-mode transition
  -> resource load
  -> cell stage
```

**INFERRED / medium confidence.** The GUI-boundary document identifies this as the required evidence path, but no concrete menu type or positive transition trace is committed.

## Current source comparison

| Original contract | Current counterpart | Finding |
|---|---|---|
| `App::IGameMode` | `src/apps/IGameMode.hpp` | Reduced lifecycle/input interface. `InputEvent` lacks button, wheel delta, mouse state, and explicit held/released edge state. Slot comments conflict with SDK layout. |
| `cGameInputManager + GameInput` | `src/apps/CellInput.*`, `src/apps/cell_stage.cpp` | Table-driven cell key state and frame/camera projection exist. Interactive SDL input bypasses IGameMode callbacks and has no original mode/input-region routing. |
| Game mode manager | `src/apps/CellModeStrategy.*` | Non-owning mode entries and enter/exit lifecycle exist; original registry, allocation, input regions, and full mode set do not. |
| UTFWin windows/layouts/messages/widgets | None | No general window tree, layout loader, message union, proc-priority list, button/text editor, or pdtk grammar. |
| App message manager | None | No priority listener/handler registry, send/post queues, standard payload, or lock/dispose contract. |
| Editor/model/UI | None | No editor root, rigblock document, history, play-mode modules, animation bridge, or EditorUI controller. |
| `cCellUI` | `src/apps/CellUI.*` | Mirrors layout constants and rollover subset, not the 2372-byte UI state, object pool, progress bar, or original rendering path. |
| `Graphics::IRenderer` | `src/renderer/Renderer.hpp`, Vulkan backend | One mesh/texture/frame path exists; original layer registry, render jobs, viewer, model/effect/shadow worlds, and UI painter do not. |

## Replaceability

| Boundary | Verdict | Reason |
|---|---|---|
| Input normalization and mode routing | **Replaceable behavior, not ABI** | A clean-room router can replace the original once event order, regions, and transitions are characterized. |
| UTFWin window/layout/message framework | **Replaceable behavior, not ABI** | A modern UI toolkit can replace it after layout, focus, message, hit-testing, and painter semantics are specified. |
| pdtk runtime | **Replaceable; ABI not required** | Direct text-widget APIs can replace command strings; fidelity tracing still needs the grammar. |
| Menu shell | **Replaceable behavior, not ABI** | No menu ABI is established; rebuild from window/layout/button/message contracts after transition evidence. |
| App message manager | **Replaceable behavior, not ABI** | A new event bus is viable after message IDs, payloads, priority, reentrancy, and lifetime are captured. |
| Editor model/history serialization | **Not replaceable yet** | Existing asset compatibility depends on unresolved resource/property formats. |
| Editor tool/actor/pose semantics | **Not replaceable yet** | Input-to-tool-to-model-to-animation behavior lacks a positive oracle. |
| Renderer/UI-object painting | **Partial existing replacement** | Current Vulkan slice covers static textured cell presentation, not original layer/world/UI painter semantics. |

**Verdict:** infrastructure seams are replaceable as clean-room boundaries, not as ABI-compatible copies. Compatibility-critical editor documents and runtime-verified tool/message behavior remain the gaps.

## Contradictions and unknowns

1. No RTTI exists; multiple-inheritance associations come from SDK layouts and constructor/vtable stores.
2. The `cEditor` 29-slot candidate must not be treated as a 29-slot `IGameMode` interface.
3. `UI::Window` and `UTFWin::Window` are distinct types.
4. SDK method labels are often contained in larger functions; contained association does not justify an exact function rename.
5. Function universes differ by artifact: vtable scanner 58,756; canonical/triage 58,757; prior live manager count 59,245 including externals. All claims remain pinned to stated snapshots.
6. Unknowns that block stronger typing:
   - pdtk parser/object lifetime;
   - concrete menu controller;
   - `Window::SendMsg`/`DoMessage` order and focus;
   - proc priority direction and reentrancy;
   - concrete factories behind generic UTFWin/editor vtables;
   - editor/resource serialization grammar;
   - `cGameInputManager` input-region routing;
   - `cEditor` message IDs/payloads;
   - tool/actor-to-model/pose mutation order;
   - concrete identities behind scanner inheritance chains.

## Read-only next evidence targets

If `SporeApp.exe` is open later, the smallest non-mutating sequence is:

1. decompile/disassemble `0x0057ce80`; decompile `0x00a4e9c0` command consumers; decompile concrete `cGameInputManager` slots;
2. decompile `Window::SendMsg`/`DoMessage`, resolve concrete `EditorUI`/`PlayModeUI` window/proc types, and pin `0x013f21d8`, `0x013f276c`, `0x013f2d68`, and `0x014105ac`;
3. type the containing persistence functions `0x004ae3b0`, `0x004af260`, `0x004bf770`, and `0x004bfc40`; trace `cEditor::HandleMessage` registrations.

## Primary sources

- `knowledgegraph/research/decomp-gap/editor-core-00.json`
- `knowledgegraph/research/decomp-gap/editor-support-00.json`
- `knowledgegraph/research/decomp-gap/ui-shell-00.json`
- `knowledgegraph/research/decomp-gap/gameglobal-misc-00.json`
- `knowledgegraph/research/global-campaign-2026/track-g-editor-ui-input.json`
- `knowledgegraph/research/semantic-atlas.json`
- `knowledgegraph/triage/clusters-f0e310e0-v6.json`
- `knowledgegraph/triage/reconstruction-readiness-f0e310e0.json`
- `knowledgegraph/triage/sdk-boundary-repairs-2540f2ca.tsv`
- `knowledgegraph/triage/xrefs-2540f2ca.tsv`
- `docs/analysis/GUI-BOUNDARY.md`
- `docs/analysis/dossiers/unknown-high/pdtk-text-widget.json`
- `docs/analysis/reconstruction-readiness.md`
- `.spore-analysis/ghidra-exports/structs.tsv`
- `.spore-analysis/ghidra-exports/structs_fields.tsv`
- `.spore-analysis/ghidra-exports/sdk_functions.tsv`
- `.spore-analysis/ghidra-exports/vtables.json`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__*.c`
- `.spore-analysis/ghidra-exports/decompiled_sdk/GameInput__OnKey*.c`
- `.spore-analysis/ghidra-exports/decompiled_sdk/App__cMessageManager__ProcessQueue.c`
- `src/apps/IGameMode.hpp`, `CellInput.*`, `CellModeStrategy.*`, `CellUI.*`, `CellGfx.hpp`
- `src/renderer/Renderer.hpp`
