# Track F — Space context, active-planet state, and navigation root closure

**Phase:** Phase-0 Root Closure  
**Status:** static characterization complete; no implementation or interface change  
**Runtime:** none

## Executive conclusion

`01021260` and `01021080` are reader boundaries, not navigation engines.

- `01021260` is a null-guarded read of `Simulator::sSpacePlayerData+0x04`. The SDK names that slot `mpActivePlanet` and types it as `intrusive_ptr<Simulator::cPlanet>`. It does not allocate or mutate the planet.
- `01021080` directly returns `Simulator::sSpacePlayerData+0x10`. The SDK names that slot `mCurrentContext` and defines `SpaceContext` as `None=-1`, `Planet=0`, `SolarSystem=1`, and `Galaxy=2`.
- `01021d40` is the committed interface report's allocation/initialization site for `SpacePlayerData`; its body and teardown path are not persisted.
- `01021960` is a static candidate writer for `mCurrentContext`. Its body stores the new value and has a special follow-up when the new value is `2`.
- `010219b0` is a static candidate writer for `SpacePlayerData+0x04` and `+0x08`, with reference-counted replacement and a null-secondary path. The SDK field map identifies those slots as active planet and active star.
- `SpaceContext`, `cScenarioMode::mMode`, and `cGameInputManager::mCurrentGameMode` are separate state axes. No committed direct edge or field alias maps them to one another.
- `01021300` is a separate lazy, mutable empire cache keyed by `mPlayerEmpireID`; it is not derived from `mCurrentContext` or `mpActivePlanet`.

## Evidence discipline and provenance

The closure uses only committed static material:

| evidence | identity / use |
|---|---|
| baseline | `knowledgegraph/research/00-baseline-inventory.json:1-32` defines source precedence and rejects runtime absence as a reason to invent behavior. Binary SHA-256: `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`. |
| analysis snapshot | `f0e310e0`, triage-v6, `SporeApp.exe`, x86-LE-32. |
| canonical xrefs | `knowledgegraph/triage/xrefs-2540f2ca.tsv`; 223,704 rows; SHA-256 `89e74b8a03c4db38a1927f8c95c38db507bf99cb8a11de6b6eb6a9484d8c79cb`. |
| SDK export | `.spore-analysis/ghidra-exports/spore_sdk.xml`; baseline pins the source SDK XML at SHA-256 `5d894677c1835082da0392e8b794f3c93a0251733898c3c5b81cf7945f458f09`. |
| structures | `.spore-analysis/ghidra-exports/structs_fields.tsv:11683-11691`. |
| decomp projections | `knowledgegraph/research/decomp-gap/sim-core-07.json`, `sim-core-03.json`, and `hold-infrastructure.json`. |
| triage/readiness | `knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json`, `triage-f0e310e0.triage-v6.jsonl`, and `reconstruction-readiness-f0e310e0.json`. |

SDK names and layouts are treated as type/layout provenance. Ghidra bodies, xrefs, and graph degree are treated as static mechanics unless explicitly identified as runtime behavior. No runtime trace, differential result, or live ordering is claimed.

## Root closure

### `01021260` — active-planet reader

| item | result |
|---|---|
| classification | `DIRECT_STATE_ACCESSOR` |
| function size | 63 bytes |
| call shape | no explicit arguments; EAX return |
| body mechanics | null-guard `Simulator::sSpacePlayerData`; read `+0x04`; return `0` if the global is null |
| return | raw `cPlanet*` / `cPlanetPtr` candidate |
| backing field | `SpacePlayerData.mpActivePlanet` at `+0x04` |
| direct callers | 262 distinct; 68 gameplay |
| direct-call rows | 357 |
| outgoing calls | none |
| allocation/mutation | none in the root |
| runtime evidence | none |

Evidence: `docs/analysis/dossiers/unknown-high/space-player-data-accessors.md:36-69`, `knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json:1182-1240`, and `knowledgegraph/research/decomp-gap/hold-infrastructure.json:148597-148606`.

Representative consumers include `00b31cc0`, `00c706d0`, `00f31d80`, `01021370`, and `01037a20`. `01021370` is recorded as dereferencing `+0x13c` on the returned planet object; the meaning of that planet offset remains unresolved.

The accessor is a **derived read view** over the authoritative `mpActivePlanet` slot. The SDK says the slot is an `intrusive_ptr<cPlanet>`, but the accessor does not show whether it adds a reference, releases a reference, or returns a borrowed pointer. That ownership question is intentionally open.

The separate SDK-imported symbol `Simulator_GetActivePlanet` is at `01021110` in `functions.tsv`; it is not evidence that `01021260` is that exact function. The supported conclusion is narrower: `01021260` reads the SDK-named active-planet slot.

### `01021080` — space-context reader

| item | result |
|---|---|
| classification | `DIRECT_STATE_ACCESSOR` |
| function size | 9 bytes |
| call shape | no explicit arguments; direct EAX return |
| body mechanics | return `Simulator::sSpacePlayerData+0x10` |
| return | `SpaceContext` enum value |
| null behavior | no null guard; assumes the global is valid |
| direct callers | 175 distinct; 38 gameplay |
| direct-call rows | 230 |
| outgoing calls | none |
| allocation/mutation | none in the root |
| runtime evidence | none |

Evidence: `docs/analysis/dossiers/unknown-high/space-player-data-accessors-3.md:36-69`, `knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json:1544-1599`, and `knowledgegraph/research/decomp-gap/hold-infrastructure.json:137949-137958`.

The SDK enum is:

| value | name |
|---:|---|
| `-1` / `0xffffffff` | `None` |
| `0` | `Planet` |
| `1` | `SolarSystem` |
| `2` | `Galaxy` |

The field/return value is therefore a space-navigation context, not a pointer and not a game-mode ID. The committed consumer projections use values `0`, `1`, and `2`; the committed writer projection characterizes a special follow-up for value `2`. A complete `None` transition is not established.

## State-transition evidence

### 1. SpacePlayerData initialization

The committed shared-state interface states that `01021d40` allocates and initializes `SpacePlayerData`: `docs/analysis/simulator-shared-state-interface.md:96-109` and `knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json:1214-1230`.

Static xrefs show:

- `01021d40` calls `00f473a0` at `01021d4e`.
- `00b60d80` reaches `01021d40` through a computed call at `00b622eb`.
- The body is not persisted in the decomp-gap ledger.

This supports an initialization/lifecycle association, not the exact initialization order. It does not prove that the active planet is allocated by `01021d40`, that all fields are zeroed, that the global is published at a particular point, or that the object is destroyed through a corresponding teardown path.

### 2. Active planet/star reference replacement

`010219b0` is a read-only static candidate for space-player reference assignment. The committed projection records:

```text
reads:  sSpacePlayerData, player id, primary object, secondary object
writes: sSpacePlayerData+0x04, sSpacePlayerData+0x08
event:  reference-counted object replacement
rule:   clear the secondary slot when the secondary object is null
```

The SDK layout makes the likely owner mapping:

- `+0x04` → `mpActivePlanet`
- `+0x08` → `mpActiveStar`

The helper names and the decompiler ABI remain incomplete, so the report records the field mapping as supported by SDK layout and the write mechanics as supported static evidence, while keeping the exact primary/secondary object identities open. See `knowledgegraph/research/decomp-gap/sim-core-07.json:24977-25057` and `25282-25577`.

### 3. Context write and value-2 follow-up

`01021960` is projected as:

```text
read  sSpacePlayerData+0x10
write sSpacePlayerData+0x10 = mode
if mode == 2 and both global player references are non-null:
    call FUN_01001360
```

It has three internal callees: `00c8b360`, `00ffbe50`, and `01001360`. The committed evidence does not establish the semantic action of `01001360`, nor does it establish a complete transition table. The input is observed as an integer mode by the decompiler; it should not be narrowed to a fully typed enum until the field write and callers are audited.

Evidence: `knowledgegraph/research/decomp-gap/sim-core-07.json:24448-24505` and `24708-24975`.

### 4. Context consumers

`00c3ae70` is projected as selecting different float behavior for `SpaceContext` values `0`, `1`, and `2`, with interpolation/clamping branches. This is a consumer contract, not a navigation transition:

- `knowledgegraph/research/decomp-gap/sim-core-03.json:22975-23069`.

`00c3dae0` is projected as routing a supplied vector through different helpers according to `SpaceContext`, then committing through `00c37e60`:

- `knowledgegraph/research/decomp-gap/sim-core-03.json:25252-25340`.

Neither consumer is evidence that `SpaceContext` is derived from a game mode. They establish that the context value controls different static behavior branches.

### 5. Identity cache refresh

`01021300` is a separate state boundary. It reads:

- `SpacePlayerData+0x18` → `mPlayerEmpireID`
- `SpacePlayerData+0x1c` → `mpPlayerEmpire`
- cached `cEmpire+0x84` → `mPoliticalID`

`ID == -1` returns null. A missing or stale cache is refreshed through `00b3d2a0` and `00ba9370`, followed by reference-management calls. The ID is the cache key; the empire pointer is the derived/lazy value. This root does not read or write `mCurrentContext` or `mpActivePlanet`.

Evidence: `knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json:1465-1541` and `docs/analysis/dossiers/unknown-high/space-player-data-accessors-2.md:36-70`.

## Structure and offset map

The SDK/exported structure is 52 bytes (`0x34`):

| offset | field | type | state role |
|---:|---|---|---|
| `0x00` | `mMillisecondsSinceLastUpdate` | `int` | timing; no target-root evidence |
| `0x04` | `mpActivePlanet` | `intrusive_ptr<Simulator::cPlanet>` | authoritative active-planet storage; read by `01021260`; candidate write by `010219b0` |
| `0x08` | `mpActiveStar` | `intrusive_ptr<Simulator::cStar>` | authoritative active-star storage; candidate write by `010219b0` |
| `0x0c` | `mpTribeCivRelationships` | `intrusive_ptr<Simulator::cRelationshipManager>` | relationship pointer; unresolved by target roots |
| `0x10` | `mCurrentContext` | `SpaceContext` | authoritative space-context storage; read by `01021080`; candidate write by `01021960` |
| `0x14` | `mfRotationRateFactor` | `float` | space rate/transform state; unresolved by target roots |
| `0x18` | `mPlayerEmpireID` | `uint32_t` | identity key; read by `01021300` |
| `0x1c` | `mpPlayerEmpire` | `intrusive_ptr<Simulator::cEmpire>` | derived lazy empire cache; read/replaced by `01021300` |
| `0x20` | `mPlayerColonies` | `vector<eastl::intrusive_ptr<Simulator::cPlanet>>` | colony collection; no target-root transition evidence |

Sources: `.spore-analysis/ghidra-exports/spore_sdk.xml:25374-25383` and `.spore-analysis/ghidra-exports/structs_fields.tsv:11683-11691`.

The global is `Simulator::sSpacePlayerData` at absolute address `0x016dda8c`, typed as `SpacePlayerData*`: `.spore-analysis/ghidra-exports/spore_sdk.xml:51791,52107`.

### Authority classification

| state | classification | reason |
|---|---|---|
| `mpActivePlanet +0x04` | authoritative storage | SDK field and intrusive-pointer declaration; `01021260` only reads it |
| `mpActiveStar +0x08` | authoritative storage | SDK field and intrusive-pointer declaration; candidate writer is `010219b0` |
| `mCurrentContext +0x10` | authoritative storage | SDK field and enum declaration; `01021960` is the candidate writer |
| `01021260` result | derived read view | no mutation or allocation in the accessor |
| `01021080` result | derived read view | direct field read, no transformation beyond returning the stored value |
| `mPlayerEmpireID +0x18` | identity key | `01021300` compares it with `cEmpire+0x84` |
| `mpPlayerEmpire +0x1c` | derived mutable cache | `01021300` validates, replaces, and reference-manages it |
| `cGameInputManager.mCurrentGameMode +0x1c` | separate mode-routing state | different owner and field map |
| `cScenarioMode.mMode +0xcc` | separate scenario state | different owner and enum |

## Scenario and game-mode relationship

`SpaceContext` is a space/navigation-scale enum:

```text
None=-1, Planet=0, SolarSystem=1, Galaxy=2
```

`cScenarioMode::mMode` is a different enum and owner:

```text
UnkMode=0, EditMode=1, PlayMode=2
```

The SDK makes `cScenarioMode` an `IGameMode` implementation, with scenario data/play-mode pointers and `mMode` at `+0xcc`: `.spore-analysis/ghidra-exports/spore_sdk.xml:32687-32733`.

`Simulator::cGameInputManager` separately exposes `mLastGameMode +0x18` and `mCurrentGameMode +0x1c`, plus input-region and mouse state: `knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json:1021-1057`.

`App::cGameModeManager` has its own `mEntries`, `mnActiveIndex`, camera, and viewer state. Its static `SetActiveModeAt` shape exits the old mode, updates active state, and enters the selected mode; live ordering is not observed: `knowledgegraph/research/global-campaign-2026/track-f-empire-economy.json:433-442`.

Therefore:

- `Galaxy == 2` and `PlayMode == 2` are numerically coincidental, not aliases.
- `cScenarioMode::mMode` is not the source of `SpaceContext` in committed evidence.
- `cGameInputManager::mCurrentGameMode` is not the source of `SpaceContext` in committed evidence.
- Scenario play/edit and space navigation may be coordinated by higher-level code, but that coordination is unresolved.
- Any future replacement must preserve separate ports for context and game/scenario mode until a direct static mapping is found.

## High-information callers and constraints

### Navigation + input

| caller | shared roots | static constraint |
|---|---|---|
| `01003690` | `00b3d350`, `01021260`, `01021960`, `010219b0` | reset/initialization sequence; reads active planet and input manager, and invokes both candidate writers. `knowledgegraph/research/decomp-gap/sim-core-07.json:14420-14840` |
| `00b32b20` | `00b3d350`, `01021960`, `010219b0` | broad simulator initialization/update sequence; calls the context/reference writers. `knowledgegraph/triage/xrefs-2540f2ca.tsv:100675-100707`; `knowledgegraph/research/decomp-gap/sim-core-00.json:48371-48405` |
| `00c3ae70` | `00b3d350`, `01021080`, `01021240` | context-dependent float/render behavior with input-manager access; does not establish context ownership. `sim-core-03.json:22975-23069` |
| `00bbdff0` | `00b3d350`, `01021260` | unresolved function directly combines input-manager access with active-planet access. `sim-core-01.json:54318-54425` |
| `00f32240` | `00b3d350`, `01021260` | graph-projected shared caller, but no body is committed. `sim-core-06.json:100000-100219` |

### Context + active-planet pair

| caller | shared roots | static constraint |
|---|---|---|
| `00bbc370` | `01021080`, `01021260` | reads both context and active-planet state before downstream work. `sim-core-01.json:53127-53280` |
| `00bc2c00` | `01021080`, `01021260` | reads both and also calls `Simulator::cTimeOfDay::SetDayDuration`; exact ordering/semantics unresolved. `sim-core-01.json:57225-57352` |
| `00bcd480` | `01021090`, `01021260`, `01021370` | active-star/active-planet/planet-consumer cluster; context getter is not a direct dependency. `sim-core-01.json:60147-60320` |

### Identity adjacency

| caller/root | relationship | constraint |
|---|---|---|
| `010229d0` | directly calls `01021080`, `01021240`, and `01021300` | high-information context + identity consumer; body unavailable. `sim-core-07.json:29333-29503` |
| `00bb4ba0` | directly calls `01021300` and adjacent planet roots | SDK-attributed `Simulator::cStarManager::RequirePlanetsForStar`; identity and planet generation are adjacent, not context-derived. `sim-core-01.json:28542-29067` |
| `00b25fb0` | calls `01021300` and `00b25f40`; interface report labels it identity plus live noun/object registry | bridge from cached political ID toward game-data/civilization state, not an active-planet/context writer. `simulator-shared-state-interface-f0e310e0.json:1602-1654` |

### Noun-root constraint

`00b21340` is a sibling shared-state root with noun-map/vector/list mechanics. The canonical xref search found no direct edge from either target root to `00b21340`. The relationship is therefore:

```text
navigation roots ──direct state reads/writes──> SpacePlayerData
identity root 01021300 ──political-ID bridge──> 00b25fb0
00b25fb0 ──game-data/noun-adjacent state──> 00b21340 domain
```

This is a transitive semantic relationship, not a direct transition edge. The noun root must not be folded into `SpaceContext` or `mpActivePlanet` without new evidence.

## Contradictions and unresolved boundaries

1. **SDK function identity:** `Simulator::GetCurrentContext` is SDK-addressed at `01020f30`, but the boundary adjudication finds no function, no xrefs, and a dead address there. `01021080` has the correct field/enum mechanics but is not automatically that exact SDK function. `knowledgegraph/triage/sdk-boundary-repairs-2540f2ca.json:29054-29074`.
2. **Active-planet function identity:** SDK `Simulator_GetActivePlanet` is at `01021110`; `01021260` is a separate accessor reading `+0x04`. The field name is supported; exact function-name promotion is not.
3. **Persisted versus targeted body:** Track-B/hold records say `decomp_available=false`; targeted read-only captures recover mechanics. Both states are retained: mechanics are static evidence, while complete body/prototype/runtime contracts remain unavailable.
4. **Enum width:** SDK/export says `SpaceContext` is 4 bytes, but the interface projection still marks the field storage width unresolved. The applied binary type must be audited before claiming the layout is independently verified.
5. **None transition:** `None=-1` is confirmed as an enum value, but no committed writer/consumer path establishes a complete `None` transition.
6. **Lifecycle:** `01021d40` is reported as the `SpacePlayerData` allocator/initializer, but there is no committed whole-object teardown or final global-release trace.
7. **Mode axes:** `Galaxy=2` and scenario `PlayMode=2` are different enums with different owners. No direct mapping is established.
8. **Graph versus order:** call-graph adjacency proves static references, not the runtime order of mode changes, planet assignment, or input dispatch.

## Smallest next static experiments

No runtime is required for these experiments.

### Lifecycle and ownership

Read-only decompile `01021d40`, `010219b0`, `00b60d80`, and the four `010219b0` helpers. Enumerate:

- stores to global `0x016dda8c`
- stores to `SpacePlayerData+0x04` and `+0x08`
- release/free/AddRef calls
- whole-object destruction or final nulling

This resolves the active-planet allocation-versus-assignment question and the teardown gap.

### Context transition table

Read-only decompile `01021960` and `01001360`, then inspect its nine direct callers:

`00b32b20`, `00b32ce0`, `00b33350`, `00fda9f0`, `00fdf5f0`, `01003490`, `01003690`, `01003a50`, and `0100a960`.

Record the integer argument and pre-state at each call. This should resolve the value-2 follow-up and whether `-1` is ever written or only used as a sentinel.

### Context consumers

Compare the branch bodies of `00c3ae70` and `00c3dae0` with their helper contracts. Annotate only field/global/vtable effects supported by static evidence. This distinguishes context-derived behavior from a context transition without relying on runtime.

### Scenario/game-mode axis

Read-only inspect `cScenarioMode` `OnEnter`/`OnExit` and `App::cGameModeManager::SetActiveModeAt`. Follow all calls to `01021960` and all writes to:

- `cScenarioMode+0xcc`
- `cGameInputManager+0x1c`
- `SpacePlayerData+0x10`

This determines whether navigation context is a direct game-mode projection or an independent state field.

### Shared callers

Read-only decompile `01003690`, `00b32b20`, `00c3ae70`, `010229d0`, `00bbdff0`, `00bbc370`, and `00bc2c00`. Annotate direct calls to `00b3d350`, `01021300`, `00b25fb0`, and `00b21340`. This will separate direct shared callers from transitive identity/noun coupling.

### Binary type audit

Audit the applied data types and access widths at:

- `0x016dda8c+0x04`
- `0x016dda8c+0x08`
- `0x016dda8c+0x10`
- `0x016dda8c+0x18`
- `0x016dda8c+0x1c`

Compare the applied reads/writes with the SDK export. This resolves enum width, intrusive-pointer representation, and pointer-versus-integer confidence.

## Phase-0 boundary

The safe interface freeze is:

```text
01021260: null-guarded read of SpacePlayerData+0x04 as active-planet pointer
01021080: direct read of SpacePlayerData+0x10 as SpaceContext
01021d40: reported SpacePlayerData allocation/initializer, body unresolved
01021960: candidate context writer, value-2 follow-up unresolved
010219b0: candidate active-reference writer, object types/ordering unresolved
01021300: separate lazy empire cache, not navigation state
```

No SPORE file, OpenSpore source file, historical artifact, or Phase-0 interface was modified. The new outputs are limited to this report and its machine-readable companion.
