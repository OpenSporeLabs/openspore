# Track 10 — conditional primary vtable architecture

## Result

- **Classification:** `preferred_claim_with_limit`
- **Allowed resolution values:** `unresolved`, `preserved_alternatives`, `preferred_claim_with_limit`, `same_observation_different_scope`
- **Resolution:** architecture dependency resolved; raw ABI residuals deferred
- **Redesign required:** no
- **Runtime:** not used; not architecture-deciding
- **Scope:** read-only Ghidra queries were used against explicit `SporeApp.exe`; the program was never mutated, saved, or reanalyzed. Historical artifacts and source were not modified; `SPORE/` and `spore.db` were not accessed.

The mode architecture is a manager-owned registry of polymorphic mode objects with semantic initialize/dispose/enter/exit/input/update operations. OpenSpore should keep that semantic interface, not reproduce MSVC vptrs or slot numbers.

## Nine adversarial steps

| Step | Test | Result |
|---:|---|---|
| 1 | Single-class vs multiple-interface vs contaminated candidate | All three retained as separate hypotheses |
| 2 | Constructor, destructor, and selected-slot predictions | Defined before adjudication |
| 3 | Direct support | Constructor writes, table bytes, destructors, manager calls, SDK layouts |
| 4 | Contradiction | The historical 27-entry scanner run cannot be treated as one Cell primary; `0x01445cb8` is not the message-manager primary |
| 5 | Independence | Constructor, destructor, dispatch, SDK, and history treated separately |
| 6 | Repetition | Confirmed across Cell, App manager, cEditor, and Terrain |
| 7 | Smallest separator | Constructor vptr write + destructor/reset + one selected slot call |
| 8 | Separator execution | Passed for Cell/App/cEditor/Terrain; UTFWin candidates had zero xrefs |
| 9 | Architecture dependence | Raw ABI matters only for original-object/binary compatibility |

## Hypotheses

### H1 — single complete owner

Rejected as a general rule. It holds for selected primaries such as `0x01412598`, but fails for `0x01485550`: that address is the Cell object's secondary vptr, not a safe primary. It also fails for `0x01445cb8`, which is installed at `UTFWin::Window+0x20c`.

### H2 — multiple-interface/subobject ownership

Supported. `0x00e616c0` allocates the 12-byte Cell mode object and writes:

- `object+0x00 = 0x01485558` — primary
- `object+0x04 = 0x01485550` — secondary

The secondary slot 0 at `0x00e5c590` is an adjusting destructor thunk (`ECX-=4`, then jump); slot 1 is `HandleMessage` at `0x00e62700`. The same pattern repeats in App mode manager, cEditor, and Terrain constructors/destructors.

### H3 — contaminated candidate

Supported. The observed 27-entry contiguous run at `0x01485550` consists of the two directly supported secondary entries followed by a 25-entry primary-observed suffix beginning at `0x01485558`. This arithmetic does not establish the complete primary table extent. The old message-manager candidate and Terrain cross-namespace projection are also contaminated or mis-scoped. Contamination does not invalidate the constructor-selected primary.

## Closure matrix

| Class/family | Constructor → vptrs | Selected dispatch/lifecycle | Slot dimension | Decision |
|---|---|---|---|---|
| `App::cGameModeManager` | `0x007d8dc0` → `0x01412598/+0`, `0x01412584/+4`, `0x01412580/+8` | `0x007d8c80` → `0x007d85b0`; old `+0x1c`, publish index, new `+0x18`; announcement calls are separate | 23-slot/92-byte primary, exactly `IGameModeManager` | Freeze as 52-byte App registry |
| `App::cCellModeStrategy` | `0x00e616c0` → `0x01485558/+0`, `0x01485550/+4` | Initialize `0x00e81cf0`; OnEnter `0x00e552f0`; OnExit `0x00e7fc00`; input `0x00e818f0` etc.; Update `0x00e80980`; secondary dtor thunk `0x00e5c590` | observed contiguous run 27 = secondary 2 + primary-observed 25; complete primary extent unresolved | Keep semantic interface; do not expose raw run as ABI |
| `Simulator::Cell::cCellGame` | `0x00e646d0`; no vptr | Initialize `0x00e80ba0`; destructor `0x00e63f90`; mode Dispose frees it; `+0x411c` is simulation identity and `cCellObjectData+0x248` is optional GFX association | 20,964-byte plain state object; `cCellSerializableData` is separate | Separate from mode/GFX/UI; do not merge identity, presentation, or save state |
| `Simulator::cSimulatorSystem` | Concrete vptrs not pinned; getter `0x00b3d330` | Service/strategy composition at `+0x20` and `+0x5c` | 112-byte object; 23-slot SDK type | Preserve composition; defer installed table |
| `Simulator::cGameInputManager` | Four interface pointers in SDK layout; getter `0x00b3d350` | Mode/input state separate from App registry | 276 bytes; 27-slot/108-byte ABI; address unresolved | Defer concrete table |
| `Simulator::cGameModeManager` | Not pinned; getter `0x00b3d420` | Downstream mode service | 156 bytes | Keep separate from 52-byte App manager |
| `App::cMessageManager` | `0x01427920` structural candidate written by `0x00884a20`; `0x01445cb8` disproved | `ProcessQueue 0x00884100`; second surface `0x00884700`; cleanup walker `0x008841f0`; global `0x015fd8dc` | 19-slot/76-byte interface; 19-word candidate; queue record stride `0x18` | Keep bus distinct; defer candidate extent |
| App runtime handler | n/a | `0x00f47b10`: app-update ID then `IAppSystem+0x80` | Message dispatch, not ownership | Separate from manager |
| Cell interaction queue | n/a | `0x00e7e130`: switch record `+0x24`, dispatch, release | Pooled event records | Separate from App bus |
| `Editors::cEditor` | `0x0057ce80` installs six vptrs | `0x00579e20` resets them; 29-entry primary | 29 concrete; 16-slot interface prefix | Positive control for H2 |
| Terrain candidate | `0x00fa1bc0` installs five vptrs | `0x00fa0780` resets them; slot 37 target `0x00f968b0` | 40 observed vs SDK 74/75 | Preserve alternatives |
| UTFWin bases | No direct xrefs at `0x013fa974` or `0x01419794` | No constructor/dispatch separator | identical 21-slot structural prefix | Defer |

## Cell correction

The raw primary/secondary mapping is reconciled for the observed transition:

- The installed primary is `0x01485558`; its observed contiguous suffix has 25 entries.
- The installed secondary is `0x01485550`; its two supported entries are the adjusting destructor thunk `0x00e5c590` and `HandleMessage 0x00e62700`.
- From the installed primary, the selected bodies align as Initialize `+0x10`, Dispose `+0x14`, OnEnter `+0x18`, OnExit `+0x1c`, and Update `+0x3c`; the manager's old `+0x1c`/new `+0x18` calls therefore match the selected lifecycle bodies.
- The complete primary table extent is still unresolved; 25 is only the observed code-pointer suffix, not a proven raw ABI size.

This does not change OpenSpore: its current `IGameMode` interface expresses methods, not slots.

## Architecture decision

The minimum dispatch abstraction is a semantic mode registry:

1. register mode;
2. validate requested index;
3. exit current mode;
4. publish active index;
5. enter requested mode;
6. route input and update independently.

Announcement calls may occur in the original transition helper, but queue timing, listener execution, and announcement delivery are outside this minimum semantic contract.

Cell runtime state, GFX, and UI remain coordinated services. App message dispatch, App runtime handling, Simulator mode listening, and Cell interaction queues remain separate layers.

Current OpenSpore already matches this boundary in `src/apps/IGameMode.hpp:28-51` and `src/apps/CellModeStrategy.cpp:80-91`; no class-topology or ownership redesign is required.

## Exact decisions

- Freeze `0x01485558` as the installed Cell primary and `0x01485550` as the secondary; treat the 27-entry run only as an observed scanner run.
- Do not infer a complete raw primary size from the 25-entry observed suffix.
- Reject “27-slot Cell primary at `0x01485550`” as a binary-ABI claim.
- Keep `IGameMode` as a clean-room semantic interface; never expose original slot numbers.
- Keep App mode registry, Simulator mode manager, and input manager separate.
- Keep `cCellGame+0x411c` as simulation identity, `cCellObjectData+0x248` as an optional presentation association, and `cCellSerializableData` as a separate mode-state/save candidate.
- Keep the App message bus, App runtime handler, Simulator mode listener, and Cell event queue separate.
- Reject `0x01445cb8` as the `cMessageManager` primary; it belongs to `UTFWin::Window+0x20c`. Use `0x01427920` as the structurally supported candidate, with `0x00884100` as ProcessQueue and `0x008841f0` as cleanup/storage cleanup.
- Do not close unknown slots merely to force class-family consistency.

## Freeze / defer

**Freeze:** manager/input separation; semantic lifecycle; Cell mode versus Cell state/GFX/UI; message versus Cell-event separation; constructor-selected subobject ownership; interface versus concrete ABI separation; `0x01427920` as the structural message-manager candidate with `0x00884100` as ProcessQueue and `0x008841f0` as cleanup/storage walker.

**Defer:** exact Cell binary slot names and complete primary extent beyond the 25-entry observed suffix; AddGameMode pointer adjustment; complete input-manager table; actual message-manager candidate extent beyond the 19-word observation; UTFWin canonical base; Terrain 40 versus 74/75 dimensions; queue order/consume semantics/runtime reachability.

## Blockers

1. Recover the complete `0x007d9260` AddGameMode body in a separately authorized analysis copy and determine whether it stores the Cell object, `object+4`, or an adjusted adapter pointer.
2. Repair missing function boundaries only in a separately authorized copy; the pinned program was not mutated.
3. Find a constructor vptr store for either UTFWin candidate before selecting a canonical base.
4. Find one same-object `+0x94` Terrain dispatch call before extending the 40-entry observed run.
5. Correct stale 27-slot comments in `src/apps/IGameMode.hpp:3-12` and `src/apps/CellModeStrategy.hpp:3-16` in a future documentation-only change.

A runtime probe was not architecture-deciding: it would not reliably recover historical table dimensions or pointer adjustment, and the current clean-room boundary is already settled.

## Citations

- `SporeApp.exe!0x00e616c0`, `0x00e5c590`, `0x00e5c5a0`, `0x00e81cf0`, `0x00e81f30`
- `SporeApp.exe!0x007d8dc0`, `0x007d8d40`, `0x007d8e20`, `0x007d85b0`, `0x007d8c80`
- `SporeApp.exe!0x00e80ba0`, `0x00e646d0`, `0x00e63f90`, `0x00e7e130`, `0x00f47b10`, `0x00b63510`
- `SporeApp.exe!0x0057ce80`, `0x00579e20`, `0x00fa1bc0`, `0x00fa0780`, `0x00991a70`, `0x00991df0`
- `SporeApp.exe!0x00884100`, `0x00884700`, `0x008841f0`, `0x01427920`, `0x00884a20`, `0x00884fb0`
- `knowledgegraph/research/conflicts/00-corpus-inventory.json:1023-1052`
- `knowledgegraph/research/types/19-audit-conflicts.json:1559-1612,1673-1762`
- `knowledgegraph/research/types/01-simulator-core.json:1273-1351`
- `knowledgegraph/research/types/10-managers-registries.json:251-268`
- `docs/analysis/class-family-map.md:119-207,393-415`
- `docs/analysis/event-message-map.md:46-50,68-78,122-134`
- `docs/analysis/simulator-root-closure.md:129-158`
- `knowledgegraph/research/architecture-resolution/followup-01-event-abi.md:9-18,22-46,49-70,105-120`
- `knowledgegraph/research/architecture-resolution/followup-04-cell-boundary.md:7-22,24-42,106-153,230-251`
