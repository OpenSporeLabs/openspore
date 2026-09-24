# Source Reconstruction Runtime Gates

These gates do not block static reconstruction. Each item records the smallest original-process observation needed to replace an explicit `RE:` uncertainty with evidence. No experiment is authorized by this file. Human approval, the machine lock, a pinned executable/environment, and the repository observatory safety rules are required.

## Global accessor gates

### gate-simulator-global-slots

- **Affected functions:** `0x00b3d300`, `0x00b3d2a0`, `0x00b3d4f0`.
- **Hypotheses:** each function returns the value of its named global slot; slot owners are distinct service pointers; uninitialized slots are null or an engine sentinel.
- **Smallest experiment:** after a positive boot control, read the three slots at a single post-initialization point and record owner identity, value, and subsequent call-site use.
- **Expected evidence:** raw event contains slot addresses, read values, lifecycle timestamp, and one representative caller result.
- **Acceptance criterion:** static accessor bodies and slot ownership agree across repeated runs; null/sentinel behavior is explicit.
- **Affected types:** `OpaqueSimulatorGlobalAccessor`, service-handle types.
- **Affected edges:** `PKG-01` to `PKG-06`, `PKG-11`, and dependent singleton consumers.

## Cell state and lifecycle gates

### gate-cell-damage

- **Affected functions:** `0x00e7a7c0`, `0x00e7a4a0`.
- **Hypotheses:** health is reduced by a computed damage amount; zero health enters a death animation/event path; invulnerability and attack checks precede damage.
- **Smallest experiment:** after a Cell-positive control, correlate one controlled damage event with object fields, return/flag behavior, animation/effect calls, and resulting health.
- **Expected evidence:** pre/post field samples and ordered static call-path observations.
- **Acceptance criterion:** all branch conditions and field mutations are observed or explicitly rejected.
- **Affected types:** `OpaqueCellObjectData`, `CellDamageContext`.
- **Affected edges:** `PKG-06` to `PKG-09` presentation and `PKG-17` animation.

### gate-cell-reset

- **Affected function:** `0x00e7fd00`.
- **Hypotheses:** reset writes the observed global state and mode tables before dispatching manager/UI initialization.
- **Smallest experiment:** observe one reset/reinitialization with stable object identity and no unrelated input.
- **Expected evidence:** ordered global writes, mode values, and called manager results.
- **Acceptance criterion:** static write set and dispatch order match the trace or the difference is recorded as a bounded failure.
- **Affected types:** `OpaqueCellGameResetContext`, `CellModeContext`.
- **Affected edges:** `PKG-06` to `PKG-08`, `PKG-09`, and `PKG-11`.

### gate-cell-lifetime

- **Affected function:** `0x00e780a0`.
- **Hypotheses:** removal is conditional on object existence; optional animation/effect dispatch precedes registry deletion; callbacks observe a stable object identity.
- **Smallest experiment:** remove one controlled object and record pool membership, callback order, and registry state.
- **Expected evidence:** pre/post object identity and ordered lifecycle callbacks.
- **Acceptance criterion:** no unobserved release or callback is required to explain the static body.
- **Affected types:** `OpaqueCellObjectData`, `CellLifecycleContext`.
- **Affected edges:** `PKG-06` to `PKG-07`, `PKG-09`, and resource lifetime.

## Palette and editor gates

### gate-palette-factory

- **Affected function:** `0x005cb5a0`.
- **Hypotheses:** the stack contains four values despite five decompiler labels; factory callbacks return concrete palette/UI objects; vector growth preserves construction order.
- **Smallest experiment:** open the palette with a fixed empty project and record argument values, factory return identities, and collection writes.
- **Expected evidence:** call-entry bytes, factory/vtable calls, and resulting collection state.
- **Acceptance criterion:** the canonical prototype and source-like object ownership are supported by bytes and one runtime instance.
- **Affected types:** `OpaquePaletteConstructionContext`, `OpaquePaletteItem`.
- **Affected edges:** `PKG-15` to `PKG-18` UI shell.

### gate-palette-selection

- **Affected function:** `0x005cb240`.
- **Hypotheses:** invalid indices are rejected; old selection deactivates before new selection activates; vtable `+0x28` drives both transitions.
- **Smallest experiment:** select invalid, same, and distinct palette entries in a fixed project.
- **Expected evidence:** ordered deactivation/activation calls and UI state.
- **Acceptance criterion:** branch and side-effect order match the static body for all three cases.
- **Affected types:** `OpaquePaletteSelectionContext`.
- **Affected edges:** `PKG-15` to editor dispatch.

### gate-palette-setup

- **Affected function:** `0x005c53c0`.
- **Hypotheses:** resource-ID replacement occurs before UI setup; app-system and swatch-manager lookups return the objects used by callbacks.
- **Smallest experiment:** initialize a fixed palette and record resource lookup, replacement, and callback order.
- **Expected evidence:** object identities and ordered calls.
- **Acceptance criterion:** static construction order and resource provenance are corroborated.
- **Affected types:** `OpaquePaletteApplicationContext`.
- **Affected edges:** `PKG-15` to `PKG-03` resource boundary.

### gate-palette-layout

- **Affected function:** `0x005c9230`.
- **Hypotheses:** the function has five stack arguments; layout values determine page-item allocation and collection writes.
- **Smallest experiment:** render one fixed palette page with deterministic layout input.
- **Expected evidence:** call-entry argument values, layout service results, item collection, and failure path if any.
- **Acceptance criterion:** the ABI and page-item loop are independently supported.
- **Affected types:** `OpaquePalettePageContext`, `OpaquePaletteItem`.
- **Affected edges:** `PKG-15` to `PKG-18` and `PKG-09`.

### gate-editor-mode

- **Affected function:** `0x005dda30`.
- **Hypotheses:** mode values `0`, `1`, and `2` are distinct; the guard suppresses redundant transitions; vtable `+0x7c` is the mode-specific action.
- **Smallest experiment:** request each mode and a repeated mode in a fixed editor session.
- **Expected evidence:** field transition, manager lookup, deactivation, and callback order.
- **Acceptance criterion:** all four requests match the static state machine.
- **Affected types:** `OpaqueEditor`, `OpaqueEditorModeManager`.
- **Affected edges:** `PKG-10` to `PKG-15` and `PKG-18`.

## Indirect dispatch and Space gates

### gate-indirect-cell-state

- **Affected function:** `0x00ff3f00`.
- **Hypotheses:** `0x00ff3f00` is a local timeline-event command-line pointer accessor on `OpaqueTimelineEventData`; its `+0x8c` field is a raw pointer/word and has no Cell-owner or online-network classification.
- **Smallest experiment:** identify a local timeline-event object and sample `+0x8c` before/after a stable local operation.
- **Expected evidence:** object identity, `+0x8c` value, local timeline-event ownership, and the absence of a network edge.
- **Acceptance criterion:** local timeline-event ownership and field behavior are corroborated or the function remains opaque; online semantics are not assigned without evidence.
- **Affected types:** `OpaqueTimelineEventData`.
- **Affected edges:** `PKG-01` to local timeline-event consumers; no online/network edge is established.

### gate-gameglobal-dispatch

- **Affected function:** `0x00dd0e10`.
- **Hypotheses:** vtable `+0x0c` is a precondition/dispatch operation; switch cases 1, 2, 4, and 5 select distinct service paths.
- **Smallest experiment:** obtain one object and exercise each reachable state while recording `+0x84` and `+0x88`.
- **Expected evidence:** object identity, field samples, vtable call, switch case, and returned object.
- **Acceptance criterion:** all reachable cases and return ownership are identified.
- **Affected types:** `OpaqueGameObject`.
- **Affected edges:** `PKG-20` to `PKG-10`, `PKG-11`, and `PKG-12`.

### gate-space-communication

- **Affected function:** `0x0102d1b0`.
- **Hypotheses:** distance comparison and negative interval/seed value select communication states; cleanup and event creation occur in the observed order.
- **Smallest experiment:** execute one controlled communication path with fixed nearby/far object positions.
- **Expected evidence:** pre/post object fields, distance result, cleanup events, created event, and achievement-manager result.
- **Acceptance criterion:** the state machine and event payload ownership are independently observed.
- **Affected types:** `OpaqueSpaceContext`, `OpaqueSpaceEvent`.
- **Affected edges:** `PKG-12` to `PKG-11`, `PKG-16`, and achievement services.

## Gate policy

A zero-event, failed-boot, uncorrelated, or provenance-incomplete run is a negative result. It cannot promote a semantic status, close an unresolved question, or establish original compatibility. When evidence arrives, update the function record first, then spawn only dependent re-review or body-reconstruction work.
