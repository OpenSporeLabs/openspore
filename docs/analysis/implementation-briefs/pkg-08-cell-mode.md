# Implementation Brief — Cell mode lifecycle and input routing

Package: `PKG-08-CELL-MODE`  
Readiness: `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`  
Evidence: `SUPPORTED`

## Purpose

Define original cCellModeStrategy lifecycle and clean-room IGameMode boundary without GFX/UI/movement ownership.

## Authoritative semantic specification

["Authoritative: active index, lifecycle flags, input callbacks, mode handles", "Runtime: App cGameModeManager, cCellModeStrategy, input callbacks, Cell services", "Persistent: none; exit does not imply save", "Invariant: IGameMode is host seam"]

## Source evidence

- docs/analysis/class-family-map.md:135-170
- docs/analysis/gameplay-state-machines.md:142-155
- docs/analysis/gameplay-state-machines.md:81-120
- docs/analysis/reconstruction-packages.md:635-702
- knowledgegraph/research/render-boundary.json:176-225

## Relevant original functions and structures

- 0x007d8d40 SetActiveModeAt boundary
- 0x00e51010 OnMouseMove
- 0x00e552f0 OnEnter
- 0x00e7fc00 OnExit
- 0x00e80980 Update
- 0x00e81cf0 Initialize
- 0x00e81f30 Dispose
- IGameMode: lifecycle/input/update host interface
- cCellModeStrategy: 27-slot candidate, lifecycle, input, update
- cGameModeManager: ModeEntry +0x14, active +0x28, init +0x10

## Exact interfaces to implement

- IGameMode.initialize/on_enter/update/on_exit/dispose
- IGameModeRegistry.activate(index) / activate_by_name(name)
- IInputRouter.route(normalized input)
- IMessageManager.register/post/send

## Dependencies and prerequisites

- M1
- PKG-01
- PKG-02
- PKG-18
- SetActiveModeAt correlation
- message/input trace

## Tests required

- cell/menu probes
- cellmode/input tests
- decomp_differential
- deterministic_unit
- integration
- original_binary_oracle

## Acceptance criteria

- All required interface operations have explicit success, unsupported, and failure results.
- The listed invariants are covered by deterministic tests or explicit static tests.
- No original runtime behavior is claimed from host fixtures or decompilation alone.
- The package can integrate through the listed engine ports without importing raw original layouts.
- Unknowns and divergences remain visible in code/test documentation and the evidence register.

## Known limitations and unresolved assumptions

- Current mode is host shell
- IGameMode omits original slots/metadata
- Input timing
- Other modes
- Queue timing
- Registration/camera ownership
- SDL bypasses callbacks

## Validation boundary

Use STATIC_ONLY, DECOMP_DIFFERENTIAL, FIXTURE, INTEGRATION, or REPLACEMENT_HOOK only as specified. ORIGINAL_RUNTIME_ORACLE is required before an original-compatibility claim; a synthetic hook or generated fixture is not an original oracle.
