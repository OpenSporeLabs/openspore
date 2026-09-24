# Track F Follow-up — SpacePlayerData lifecycle and SpaceContext transitions

**Phase:** Phase-0 Root Closure  
**Status:** static follow-up complete; no runtime execution  
**Scope:** `01021d40`, `01021960`, `01001360`, `010219b0`, `00b60d80`, the nine direct callers of `01021960`, and writes/releases to `Simulator::sSpacePlayerData`, `SpacePlayerData+0x04`, `+0x08`, and `+0x10`.

## Executive findings

- `01021d40` is a confirmed `SpacePlayerData` allocator/initializer. It allocates `0x34` bytes, publishes the pointer to `0x016dda8c`, initializes `+0x04=0`, `+0x08=0`, `+0x0c=0`, `+0x10=-1`, `+0x18=-1`, `+0x1c=0`, the colony-vector words, and `+0x14=1.0`.
- `01021d40` does not explicitly initialize `+0x00`, release an old global, allocate an active planet/star, or free the whole object.
- `01021960` is a conditional `SpaceContext` writer. It stores the supplied integer at `+0x10` only when the old value differs. The value-2 path is conditional on the old `+0x08` object and `00ffbe50` being non-null, then calls `00c8b360` and `01001360`.
- `010219b0` replaces `+0x08` and `+0x04` with reference-managed objects. `010221f0` is a second active-planet/star replacement path, so `010219b0` is not the only assignment root.
- `01022460` provides field teardown: it clears/releases `+0x04`, `+0x08`, `+0x0c`, `+0x1c`, releases `+0x20`, and resets `+0x18`. `00bb7250` independently clears/releases `+0x08`.
- `01022580` is an additional `+0x10` writer: after its one-shot guard, it writes `0` when the current value is non-zero. This is not routed through `01021960`.
- The nine direct `01021960` callers request `-1`, `0`, `1`, or `2`; requested values and actual stores are distinct because `01021960` suppresses same-value writes.
- No direct final nulling, whole-object free, or global release of `Simulator::sSpacePlayerData` is established. Field cleanup is established; whole-object teardown is not.

## Evidence and provenance

Only committed static material and read-only inspection were used:

- baseline: `knowledgegraph/research/00-baseline-inventory.json:1-32`
- analysis snapshot: `f0e310e0`, triage-v6
- canonical xrefs: `knowledgegraph/triage/xrefs-2540f2ca.tsv`
- SDK export: `.spore-analysis/ghidra-exports/spore_sdk.xml`
- structure fields: `.spore-analysis/ghidra-exports/structs_fields.tsv:11683-11691`
- decomp-gap projections: `knowledgegraph/research/decomp-gap/sim-core-07.json:24448-25579` and related partitions
- read-only Ghidra inspection: existing `SporeApp.exe` project snapshot, Ghidra 12.1.2, temporary copy, no persisted decompilation

The canonical xref file identifies the nine `01021960` calls at:

| caller | callsite | argument | static context |
|---|---:|---:|---|
| `00b32b20` | `00b32be7` | `-1` | initialization/reset; `01022460` immediately precedes it |
| `00b32ce0` | `00b32d87` | `-1` | initialization/reset; `01022460` immediately precedes it |
| `00b33350` | `00b33463` | `-1` | conditional reset for `0x1654c01`, `0x1654c02`, `0x1654c04` |
| `00fda9f0` | `00fdaa5f` | `-1` | context-specific work followed by reset; `01021080` is read first when the receiver object is non-null |
| `00fdf5f0` | `00fdf823` | `0` | requests Planet |
| `01003490` | `010034fd` | `2` | requests Galaxy; `01021080` is read afterward |
| `01003690` | `01003750` | `0` | requests Planet during planet/space setup |
| `01003a50` | `01003aaf` | `1` | requests SolarSystem during system-space setup |
| `0100a960` | `0100ab17` | `-1` | requests None in a larger teardown/transition body |

The same xref export records `00b60d80 -> 01021d40` as a computed call at `00b622eb`.

## Object layout

The SDK export places `Simulator::sSpacePlayerData` at `0x016dda8c` and defines the relevant fields as:

| offset | SDK field | type | static role |
|---:|---|---|---|
| `+0x00` | `mMillisecondsSinceLastUpdate` | `int` | not explicitly initialized by `01021d40` |
| `+0x04` | `mpActivePlanet` | `intrusive_ptr<cPlanet>` | active-planet storage |
| `+0x08` | `mpActiveStar` | `intrusive_ptr<cStar>` | active-star storage |
| `+0x0c` | `mpTribeCivRelationships` | `intrusive_ptr<cRelationshipManager>` | relationship-manager storage |
| `+0x10` | `mCurrentContext` | `SpaceContext` | space-navigation context storage |
| `+0x14` | `mfRotationRateFactor` | `float` | initialized to `1.0` |
| `+0x18` | `mPlayerEmpireID` | `uint32_t` | reset to `-1` by `01022460` |
| `+0x1c` | `mpPlayerEmpire` | `intrusive_ptr<cEmpire>` | cleared/released by `01022460` |
| `+0x20` | `mPlayerColonies` | vector of intrusive planet pointers | range released by `01022460` |

The field names and intrusive-pointer types are SDK layout provenance. The recovered writes/releases establish mechanics; they do not identify every concrete dynamic object type.

## Initialization and publication

### `01021d40`

Recovered read-only mechanics:

```text
allocate 0x34 bytes
if allocation succeeds:
    +0x04 = 0
    +0x08 = 0
    +0x0c = 0
    +0x10 = -1
    +0x18 = -1
    +0x1c = 0
    +0x20 = 0
    +0x24 = 0
    +0x28 = 0
    +0x14 = 1.0
    publish allocation to 0x016dda8c
else:
    publish 0 to 0x016dda8c
```

The existing interface report describes `01021d40` as the allocator/initializer and explicitly says active-planet allocation is not established there (`knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json:1214-1230`). The recovered body now establishes the exact explicit field stores, but still does not establish whole-object teardown or allocator behavior for an omitted field.

### `00b60d80`

`00b60d80` is a large simulator initialization component. Its `CALL EAX` at `00b622eb` is represented as a computed-call to `01021d40` in the canonical xref export. It constructs and registers a subsystem object, then reaches the `01021d40` initializer through that indirect call. No direct `sSpacePlayerData` field teardown is established in `00b60d80`.

## Active planet/star assignment and release

### `010219b0`

The recovered body has two observed explicit arguments (`int param_1`, `int *param_2`), not a promoted three-parameter SDK-style prototype. It performs reference replacement in this order:

1. Resolve and replace `SpacePlayerData+0x08`.
2. If the second input is non-null and does not resolve to the same player object, resolve and replace `SpacePlayerData+0x04`; otherwise clear the planet slot.
3. Perform virtual intrusive-style operations on the new and old objects.

The `+0x08` path uses virtual slots `+0x00` and `+0x04`; the `+0x04` path uses virtual slots `+0xbc` and `+0xc0`. These are reference-management candidates supported by the SDK intrusive-pointer types and the repeated vtable mechanics. The exact object identities and helper names remain unresolved.

### `010221f0`

`010221f0` is called by `01022580` and is a second active-reference path. The recovered decompiler's indexed writes correspond to the layout offsets:

- clears and releases the old `+0x08` value;
- clears and releases the old `+0x04` value;
- derives replacement objects through `00b3d2a0`/`00bb3750`;
- stores replacement values into `+0x04` and `+0x08`.

Its input token and resulting concrete object types are not fully identified. The supported conclusion is that active planet/star assignment is not confined to `010219b0`.

### `01022460` and `00bb7250`

`01022460` is the clearest field-level teardown routine. It:

- clears and releases `+0x04`;
- clears and releases `+0x08`;
- clears and releases `+0x0c`;
- clears and releases `+0x1c`;
- releases the `+0x20` colony vector;
- resets `+0x18` to `-1`.

It does not write `+0x10` and does not clear the global pointer. `00bb7250` independently clears/releases `+0x08`, providing an additional active-star release path.

## Context writers and transitions

### `01021960`

The recovered body is:

```text
if current +0x10 != argument:
    +0x10 = argument
    if argument == 2:
        if old +0x08 != 0 and FUN_00ffbe50() != 0:
            value = FUN_00c8b360(old +0x08)
            FUN_01001360(FUN_00ffbe50_result, value)
```

The function assumes the global is valid; it has no null guard. The value-2 follow-up is conditional and is not a direct `SpacePlayerData+0x10` write by `01001360`.

### `01001360`

`01001360` is a 917-byte helper with three direct callers: `01021960`, `010213b0`, and `010021a0`. Its recovered body enumerates a manager list, builds a bounded temporary buffer, copies records through helper calls, and performs virtual AddRef/Release and slot-`0x16c` updates. It is reference-managed collection/record infrastructure, not a second context storage writer. The exact navigation meaning of the `00c8b360`/`00ffbe50` values remains unresolved.

### `01022580`

`01022580` has direct callers `00b32dd0`, `00b32f60`, and `00b33130`. After its one-shot guard:

- if `+0x08` is null, it derives a value and calls `010221f0`;
- if `+0x10` is non-zero, it stores `0` directly.

This is an independent `SpaceContext` write path. The prior characterization that treated `01021960` as the sole writer is incomplete.

### Requested values versus actual stores

| actor/path | requested value | actual store condition |
|---|---:|---|
| `01021d40` | `-1` | successful initialization |
| `01021960` | `-1`, `0`, `1`, or `2` | only if old value differs |
| `01022580` | `0` | only if current value is non-zero |

The nine direct callers therefore cover all four SDK values, but static call arguments do not prove that a store occurred on every call. No runtime transition order is claimed.

## Mode-axis comparison

| state | owner/field | values | conclusion |
|---|---|---|---|
| space context | `Simulator::sSpacePlayerData+0x10` | `None=-1`, `Planet=0`, `SolarSystem=1`, `Galaxy=2` | navigation-scale context |
| scenario mode | `App::cScenarioMode+0xcc` | `UnkMode=0`, `EditMode=1`, `PlayMode=2` | scenario edit/play state |
| input manager mode | `Simulator::cGameInputManager+0x1c` | `uint32_t`; related `mLastGameMode+0x18` | input/game-mode routing state |

The SDK export places `cScenarioMode::mMode` at `+0xcc` (`.spore-analysis/ghidra-exports/spore_sdk.xml:32687-32733`) and `cGameInputManager::mCurrentGameMode` at `+0x1c` (`.spore-analysis/ghidra-exports/spore_sdk.xml:15988-16013`). `01021960` has no direct write or field edge to either owner. `Galaxy=2` and `PlayMode=2` are numerically coincidental, not aliases.

## Teardown boundary

The static evidence establishes field cleanup and context reset, not whole-object destruction:

```text
01022460: release/clear SpacePlayerData-owned fields
00bb7250:  release/clear +0x08
01021960(-1): request SpaceContext=None
01021d40: allocate/publish SpacePlayerData
```

No direct `FUN_00f47380(sSpacePlayerData)` or final `sSpacePlayerData=0` path was recovered. The temporary Ghidra inspection did not mutate the program or project.

## Unresolved items

- Exact original ABI and semantic identity of `010219b0`'s two observed arguments.
- Exact object/domain meaning of `00c8b360`, `00ffbe50`, and `01001360`.
- Runtime same-value suppression and ordering.
- Whole-object destruction or final global release.
- The unowned `01022572` write reference is retained as unresolved and not used as lifecycle evidence.

## Source boundary

No SPORE file, OpenSpore source file, historical artifact, interface, or existing research report was modified. The only new outputs are this report and its machine-readable companion:

- `knowledgegraph/research/root-closure/followup-space-lifecycle.json`
- `knowledgegraph/research/root-closure/followup-space-lifecycle.md`
