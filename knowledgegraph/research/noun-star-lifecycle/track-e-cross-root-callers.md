# Track E — Cross-root caller families

**Scope:** highest-information callers of the eleven canonical cross-root Simulator roots, with emphasis on multi-root sequencing, noun materialization and avatar replacement, cleanup/erase boundaries, input/mode transitions, world/planet transitions, empire/space state, and serialization-adjacent calls.

**Status:** static-only research report. No implementation was performed. No original executable, `SPORE/`, shared final artifact, or other worker file was modified.

**Runtime evidence:** none collected for these families. The repository’s historical runtime corpus is limited to bounded application startup/service access; it does not establish these gameplay, world, empire, teardown, or persistence paths (`docs/analysis/gameplay-state-machines.md:44-65`, `docs/analysis/serialization-model.md:1-25`).

## Evidence and selection policy

The canonical corpus is `knowledgegraph/triage/xrefs-2540f2ca.tsv` (223,704 direct canonical edges; snapshot `2540f2ca`) under triage-v6. Root contracts and the existing KG projection are in `knowledgegraph/research/root-closure/cross-root-relationships.json:1-211` and `:393-730`; follow-up counts are in `knowledgegraph/research/root-closure/followup-metrics.md:1-89`.

The seven callers below are the committed high-information set, not an arbitrary expansion of the 948 mechanically multi-root callers. They were retained because their bodies cross a meaningful subset of the root families rather than merely co-calling unrelated infrastructure. I used canonical xrefs for direct call edges, read-only Ghidra decompilation and control-flow analysis for the selected bodies and helpers, and bounded Ghidra dataflow where the high-P-code variable was identifiable. The existing KG/report artifacts supplied structure, ownership, and contradiction checks; Ghidra SDK names were not promoted beyond their evidence level.

The principal Ghidra control-flow measurements are:

| caller | size | cyclomatic complexity | blocks | loops | interpretation |
|---|---:|---:|---:|---:|---|
| `00aebe90` | 4,327 | 260 | 180 | 8 | extreme shared-state/event orchestration |
| `00bff2d0` | 1,038 | 73 | 34 | 2 | initialization/context plus noun and planet paths |
| `00c099e0` | 1,467 | 76 | 59 | 1 | creature initialization/state transition |
| `00cfbc10` | 5,601 | 409 | 212 | 36 | phase-driven world/mode/ownership orchestrator |
| `010027b0` | 1,010 | 75 | 54 | 1 | space/world materialization and context switch |
| `010225d0` | 842 | 58 | 37 | 3 | batched space/player update traversal |
| `010593e0` | 2,855 | 198 | 93 | 1 | tool/creature action dispatch with world and empire effects |

## Root shorthand and ownership boundary

| shorthand | root | direct contract | ownership/lifecycle consequence |
|---|---|---|---|
| `CTX` | `00b3d300` | returns `DAT_0167eae0` | raw context/owner candidate; no allocation, ref, write, or outgoing edge |
| `STAR` | `00b3d2a0` | returns `DAT_0167eae4` | cStarManager-compatible receiver candidate; map and relationship state are manager-owned |
| `STATE` | `00b5b800` | forwarded scalar/opaque value, null receiver sentinel `0xffffffff` | no root mutation or ref operation; do not dereference as a normal pointer |
| `INPUT` | `00b3d350` | borrowed `cGameInputManager*` | input/mode owner, distinct from `SpaceContext` and `STATE` |
| `PLANET` | `01021260` | null-guarded read of `sSpacePlayerData+0x04` | active planet is borrowed from `SpacePlayerData` |
| `AVATAR` | `00b1fdb0` | reads receiver `+0x54` | borrowed creature/avatar pointer; no AddRef/Release |
| `NOUN` | `00b21340` | five-argument noun materialization ABI | manager-owned noun vector/map; no AddRef/Release for returned records |
| `SPACE` | `01021300` | `SpacePlayerData+0x18/+0x1c` empire cache | one cache-owned empire reference; miss path AddRefs/stores/Releases |
| `CONTEXT` | `01021080` | reads `SpacePlayerData+0x10` | `None=-1`, `Planet=0`, `SolarSystem=1`, `Galaxy=2` |
| `CIV` | `00b25fb0` | current empire to noun/civilization bridge | borrowed result on normal path; caller-stack fallback only when empire is null |
| `EMPIRE` | `00ba9370` | cStarManager-compatible map ceiling/lower-bound | borrowed `cEmpire*`; no AddRef/Release and no exact-key check |

The strongest direct chains are:

```text
SPACE -> STAR -> EMPIRE
CIV -> SPACE
CIV -> 00b25f40 -> NOUN
EMPIRE -> lower-bound helper
NOUN -> lower-bound helper -> map insertion helper
```

These are call/dataflow chains only where the local P-code or direct body proves them. A co-call is not an ownership edge. In particular, the `CTX`, `STAR`, and canonical noun-manager slots remain separate physical/global words; the existing follow-up does not close their value/publication relationship (`knowledgegraph/research/root-closure/followup-receiver-provenance.md:13-20`, `:131-137`).

## Family A — `00aebe90`: empire-aware event/comm orchestration

**Canonical roots:** `CTX`, `STAR`, `STATE`, `SPACE`, `EMPIRE`, `CIV` (six roots; 28 selected root-edge rows in the canonical export).

**Arguments and receiver:** Ghidra recovers `FUN_00aebe90(int param_1, string16 *param_2)`. `param_1` is a receiver with a field at `+0x20`; `param_2` is a structured string/event-like record. The exact original method and payload names are unresolved. The existing KG labels this a cross-domain comm/event orchestration sample, not a narrow accessor (`cross-root-relationships.json:656-668`).

**Call order and root interaction:**

1. The body establishes tool/context state, calls `FUN_00b5b800`, `00b3d2a0`, and `00ba6dc0`, then branches on the opaque forwarded value.
2. In the empire-oriented branch, `STAR@00aebf13/00aebf2e` supplies the manager context; `EMPIRE@00aebf35` obtains an empire pointer; `SPACE@00aebf44`, `00aebf4e`, and `00aebf70` query or refresh the current-player cache. The body compares the direct map result with the cache result and conditionally calls `FUN_010829f0`.
3. The non-empire branch uses `CTX@00aec5b6` and `CIV@00aec5bd` to obtain the current civilization-compatible pointer. The `CIV` receiver is the `CTX` result; the normal path can therefore reach noun materialization transitively through `00b25f40 -> NOUN`, but this function has no direct `NOUN` edge.
4. The body continues through virtual callbacks, event processing, and later calls to `00b3d400`; it then releases callback/event storage and frees temporary allocations.

The order of `SPACE` and `EMPIRE` is conditional: `SPACE` may return a cache hit without traversing `STAR -> EMPIRE`, while the body itself calls `EMPIRE` independently in the event path. A later `SPACE` call is not proof that the earlier lookup was a miss.

**Object identity and ownership:** `EMPIRE` and `CIV` return borrowed pointers. `SpacePlayerData+0x1c` owns one cache reference, the selected star manager map owns its empire references, and the noun vector owns the returned game-data vector. This caller reads those surfaces and releases its own temporary/event records; it does not establish a new empire or noun owner.

**Lifecycle stage:** shared comm/event creation or update with current-player empire/civilization context. The static body is consistent with a stateful event/materialization stage, but no exact original event type, mode transition, or persistence stage is proven.

**Evidence strength:** high for direct calls, conditional branch placement, and the `CTX -> CIV` receiver pattern; medium for “comm/event” semantics; low for exact event type and lifecycle name. No runtime evidence.

**Hypotheses and contradictions:**

- Supported: this is a high-information shared-state integration point, not a generic root wrapper.
- Rejected: all six roots are one object. The root contracts, distinct globals, and receiver-provenance follow-up contradict a single-owner claim.
- Supported with a limit: `SPACE` and `EMPIRE` are consulted as one current-player identity decision. The cache can return a lower-bound successor and the direct caller must not assume exact membership.
- Rejected: the `CIV` call proves that `CTX` is the canonical `cGameNounManager` global. It proves receiver propagation and noun-layout use, not publication or aliasing.

## Family B — `00bff2d0`: mode/scene initialization, noun materialization, and avatar access

**Canonical roots:** `CTX`, `STATE`, `INPUT`, `PLANET`, `AVATAR`, `CIV`, and `NOUN` (seven roots; 26 selected root-edge rows). This is a correction to the compact `high_information_shared_callers` projection, which lists only four roots for this caller; the canonical xref rows show the additional direct `INPUT`, `AVATAR`, and `PLANET` edges.

**Arguments and receiver:** Ghidra recovers `FUN_00bff2d0(int *param_1, CommandLine *param_2)`. `param_1` is a mutable scene/controller-like receiver with virtual callbacks and state words; `param_2` is an optional command/transition argument. Exact original names are unresolved.

**Call order and root interaction:**

1. `param_1` virtual slots `+0x4c` and `+0x48` are called, then several state words are reset. `INPUT` is obtained at `00bff32f`, `00bff346`, and `00bff355`; the body updates an input-related object.
2. `STATE@00bff387` gates the path. A `CTX@00bff3e9 -> CIV@00bff3f0` pair obtains a civilization-compatible pointer, while a later branch reads `PLANET@00bff393/00bff39c`.
3. If the active planet exists, the body calls `FUN_01002bd0` and then `AVATAR@00bff3b4`. This is the exceptional receiver provenance case: the avatar receiver is the return of `01002bd0`, not the immediately preceding `CTX` result. The result is passed to `FUN_00ff5b30`.
4. Under the `STATE == &DAT_01654c04` branch, the body calls `CTX@00bff408`, `CIV@00bff3f0`, and then directly `NOUN@00bff428` with a five-callback set and noun ID `0x403df5c`. It scans the returned vector by political ID and emits error/event paths on mismatch.
5. The body repeats `CTX`/`CIV` around `FUN_00b25c30`, `FUN_00b25fb0`, `FUN_00b3d3e0`, and `FUN_00dd8640`; it then constructs a command object, calls an application-system initialization vtable, and destroys the temporary command object.

**Object identity and ownership:** `NOUN` returns a manager-owned vector. The kCivilization/city callback set may AddRef individual intrusive pointers while building the vector, but `NOUN` itself does not AddRef or Release its returned record or elements. `CIV` returns a borrowed civilization pointer; `AVATAR` returns a borrowed pointer. The `01002bd0` avatar path is a concrete exception to the otherwise common `CTX` receiver source and must not be normalized into the named noun getter.

**Lifecycle stage:** scene/mode initialization or entry preparation with active-planet gating, current-civilization setup, optional avatar initialization, and noun materialization. It is not proven to be the App game-mode registry transition; the static body has no direct `cGameModeManager::SetActiveModeAt` call.

**Evidence strength:** high for the seven-root edge set, control-flow branches, the `01002bd0 -> AVATAR` exception, and `CTX -> CIV` sequence. Ghidra dataflow at `00bff3f0` terminated at the `CIV` call boundary; the ECX source and exception are established by the pinned disassembly/receiver follow-up, not by promoting a decompiler argument name. Medium for “scene/mode” semantics; no runtime evidence.

**Hypotheses and contradictions:**

- Supported: this caller materializes or refreshes noun/civilization data while preparing a scene and can read a current avatar.
- Supported: `STATE` is a scalar/opaque gate, not a pointer to the same receiver as `CTX`.
- Rejected: every `CIV` receiver comes from `CTX`. `00bff3b4` is the direct `AVATAR` exception; the common `CTX` pattern does not cover it.
- Unresolved: whether `CTX` eventually aliases `00b3d400`/the named noun manager. Receiver layout is compatible, but the global publication relation remains open.
- Rejected: the direct `NOUN` call proves that this is the same manager as `STAR`; no such identity edge exists.

## Family C — `00c099e0`: creature initialization and avatar replacement under input/strategy gates

**Canonical roots:** `CTX`, `INPUT`, and `STATE` (three roots; seven selected root-edge rows). The important non-root helper is `00b1fd50`, the direct `owner+0x54` replacement writer.

**Arguments and receiver:** Ghidra recovers `FUN_00c099e0(int param_1, int param_2, undefined4 param_3, int *param_4)`. The arguments are a creature/player-like identity, a record with a field at `+0x504`, a mode/control flag, and a flag/optional pointer. Exact SDK names are not recovered.

**Call order and root interaction:**

1. The body obtains a service/creature object through `FUN_0067cb40` and initializes or updates its state. `param_2+0x504` is released, stored into `piVar4[0x59d]`, and the old object is released through the intrusive virtual slots.
2. If `param_3` is set, `CTX@00c09af0` is followed by `FUN_00b1fd50@00c09af7`, then species-manager/editor helpers. `b1fd50` clears the old avatar’s state bit, sets the new avatar’s state bit, AddRefs the new pointer, stores it at owner `+0x54`, and Releases the old pointer.
3. `FUN_00c037c0` gates the path. A failure path calls `CTX -> FUN_00b225d0` and returns null; the success path later inserts the object into the `param_2+0x548` vector and releases the temporary reference.
4. `STATE@00c09b52`, `00c09b6a`, and `00c09ca2` gates additional action/effect work. `INPUT@00c09f07` is used in the final strategy/input setup path. The body calls cleanup helpers and returns the initialized object.

Ghidra high-P-code dataflow at the `00c09af7` call did not reduce the implicit receiver to a single global: the `b1fd50` receiver high-variable is a pre-existing `ESI`-derived object, while the nearby `CTX` call is separately present. This is a concrete warning against treating the co-call as a complete dataflow chain.

**Object identity and ownership:** `b1fd50` is the strongest avatar ownership writer in the selected set: AddRef new, store, Release old. The receiver is layout-compatible with `cGameNounManager::mpAvatar`, but this caller does not close the owner to the canonical global. The `param_2+0x548` vector and related list operations are separate from the avatar slot.

**Lifecycle stage:** creature/avatar initialization and state transition, followed by optional action/effect setup. It is not proven to be the App or Simulator game-mode registry transition; `INPUT` and `STATE` are used as gates/inputs.

**Evidence strength:** high for the three-root call set, the `b1fd50` replacement mechanics, and the `param_2+0x504` intrusive replacement. Medium for the creature/mode semantic label. Ghidra dataflow supports a bounded local provenance finding but does not prove global owner identity. No runtime evidence.

**Hypotheses and contradictions:**

- Supported: `b1fd50` is an avatar replacement/lifetime boundary.
- Supported: `STATE` is used as an opaque gate, not a dereferenced object.
- Rejected: `INPUT` and `STATE` are the same mode axis. The root closure explicitly separates input mode, scenario mode, and forwarded strategy state.
- Unresolved: whether the `b1fd50` receiver is the same noun-manager instance later reached through `CTX`.

## Family D — `00cfbc10`: phase-driven world/mode/ownership orchestrator

**Canonical roots:** `CTX`, `STAR`, `INPUT`, `PLANET`, `CIV`, `NOUN`, and `EMPIRE` (seven roots; 41 selected root-edge rows). A decompiler-visible `FUN_00b5b800` test exists in this body, but it is not a direct row for the canonical root filter and is not counted as a canonical root membership here. This is the highest-complexity selected body and the strongest sequencing sample.

**Arguments and receiver:** Ghidra recovers `FUN_00cfbc10(int param_1, undefined4 param_2)`. The switch reads `*(param_1+0xb4)` and uses the state words at `+0xb8` and `+0xbc`; `param_2` is an event/update argument passed to final service calls. The raw phase values are 0 through 10, but their semantic names are not recovered.

**Call order and root interaction by phase:**

- **Phase 0:** sets the phase to 1, calls `FUN_00cf71d0`, consults `STATE`, and reads `PLANET@00cfbcc6`. The body initializes camera, lighting, rendering, and space presentation. For selected state values it obtains `CTX`, calls `CIV`, and may use `FUN_00ba1c60` before applying a transform.
- **Phase 1:** sets phase 2, reads `CTX`, and calls `CIV@00cfc39c`, `00cfc3f7`, and `00cfc446`; another branch calls `CIV@00cfc797`. In the `STATE == &DAT_01654c08` branch it obtains `STAR@00cfc49b`, calls `EMPIRE@00cfc4a2`, and later reads noun vectors through `FUN_00b25ca0`. It materializes a noun category with direct `NOUN@00cfc62e` and `00cfc9d0`, then iterates the returned records and invokes `FUN_00cf94e0`.
- **Phase 2:** guards an active object, then can call `FUN_00cf44c0(*(param_1+0x100)+0x18)`. That helper materializes a city/civilization noun record, iterates city-like entries, conditionally calls `FUN_00bd9bb0`, clears the owner pointer, and invokes a vtable teardown. This is the selected destruction/erase-adjacent family, but the exact noun/empire identity and final destruction rule remain bounded.
- **Phases 3–6:** wait/transition/lighting stages. Phase 4 calls `FUN_0050f740` over queued records, phase 5 checks plant-species/last-mode state, and phase 6 invokes mode-exit/mode-enter callbacks, trading/space setup, and an interface `Write` call on an object obtained through a strategy vtable. The `Write` call is serialization-adjacent only; no direct `ClassSerializer` or save/load root is reached.
- **Phases 7–9:** guarded handoff/restore-like transition steps. The body calls the persistence-like helpers `FUN_00e36fa0`, `00e36de0`, `00e3b1f0`, `00e36dd0`, and `00e36e10`, but their concrete persistence/identity classification is not closed by the root body.

**Object identity and ownership:** `PLANET` is borrowed from `SpacePlayerData`; `EMPIRE` is borrowed from the manager map; `SPACE` is not a direct root here but the empire/civilization path can still be affected by cache state. `NOUN` records and noun-vector elements are manager-owned and borrowed. `FUN_00cf44c0` clears an owner-held pointer and invokes release-like virtual operations, but the selected body does not prove that it erases the canonical `mEmpires` map or destroys the noun registry itself.

**Lifecycle stage:** a high-level world/scene/mode state machine spanning initialization, noun/city materialization, transition guards, mode exit/enter, and cleanup. Its phase machine is separate from `SpaceContext`, `cGameInputManager::mCurrentGameMode`, and `cScenarioMode::mMode`; the existing space follow-up explicitly rejects collapsing those axes (`knowledgegraph/research/root-closure/followup-space-lifecycle.md:170-178`).

**Evidence strength:** high for the switch-driven phase order, selected root callsites, direct noun materialization calls, and the local cleanup/Write interfaces. Medium for the semantic phase names and the `cf44c0` erase interpretation. The `Write` call is not evidence of a profile save. No runtime evidence.

**Hypotheses and contradictions:**

- Supported: `00cfbc10` is a high-degree sequencing and ownership-boundary orchestrator.
- Supported: `CIV` is used as a current civilization bridge in several phase branches, while `EMPIRE` is separately used for manager/registry work.
- Rejected: the phase integer is `SpaceContext` or input mode. The values and owners are different.
- Rejected as an established save claim: the phase-6 `Write` interface is the save path. The strongest authoritative save/load bodies are `FUN_00b28ec0` and `FUN_00b279e0`, and no selected root caller has a direct edge to those bodies or to `00b3d440`.
- Medium: `FUN_00cf44c0` performs noun/city cleanup or destruction. Its release-like operations are direct, but exact object identity and destruction policy are not.

## Family E — `010027b0`: world/planet materialization and context switch

**Canonical roots:** `CTX`, `STAR`, `INPUT`, `PLANET`, `SPACE`, `CONTEXT`, and `EMPIRE` (seven roots; nine selected root-edge rows). Existing state-machine evidence maps the beginning/interior of this function to a space-game accessor and separates it from the authoritative `SpaceContext` setter (`docs/analysis/gameplay-state-machines.md:247-282`, `knowledgegraph/research/root-closure/followup-space-lifecycle.md:130-178`).

**Arguments and receiver:** Ghidra recovers `FUN_010027b0(int param_1, int param_2, char param_3)`. `param_1` owns a linked collection through `+0x74`; `param_2` is a selected empire/world/planet-like object; `param_3` requests optional event/message effects. Exact SDK names are unresolved.

**Call order and root interaction:**

1. The function obtains a global/context result, reads a manager field, and returns early if the manager is not available.
2. It iterates the `param_1+0x70/+0x74` collection. Ghidra dataflow at `01002827` shows `param_2` loaded from `[EBP+8]` and passed to `STAR`; the same value is an explicit input to `EMPIRE@0100282e`. It compares `EMPIRE+0x84` against the requested `01021090` identity and chooses a candidate through additional comparison helpers.
3. If the candidate is accepted, it allocates a `0x0c` linked entry, splices it into the owner list, calls `STAR`/`EMPIRE` for the selected object, counts the list, and calls `FUN_0102b1d0` plus `FUN_0102be20` to materialize a runtime object.
4. It calls `SPACE@01002b5b`, then reads `CONTEXT@01002987`. Context 0 enters planet-surface conversion and `INPUT` setup; context 1 reads `PLANET@010029ec` and adjusts camera/planet presentation; context 2 calls the galaxy-side helpers. The selected empire and current-empire paths then choose a message/cue before `FUN_010666a0` and `FUN_0106b500` cleanup calls.

**Object identity and ownership:** the `0x0c` entry is linked into the `param_1` collection. `FUN_0102b1d0` returns a newly materialized runtime object, but the exact owner and reference contract of the two cleanup helpers are not fully typed. `EMPIRE` and `PLANET` are borrowed; no root in this function AddRefs them. `SPACE` may return a cache-owned current empire pointer, but the function does not make that cache pointer the owner of the newly linked entry.

**Lifecycle stage:** current-world/planet selection, runtime world materialization, and Planet/SolarSystem/Galaxy presentation setup. It is a strong world-transition family, but it is not itself the `SpaceContext` writer; the authoritative setter `01021960` is a separate lifecycle surface.

**Evidence strength:** high for list insertion, direct root callsites, `param_2` propagation into `STAR -> EMPIRE`, context branching, and the conditional cleanup call order. Medium for the semantic identity of `FUN_0102b1d0` and cleanup ownership. No runtime evidence.

**Hypotheses and contradictions:**

- Supported: `010027b0` crosses manager/empire identity and `SpaceContext` without proving those fields are one object.
- Rejected: `EMPIRE` is exact-find. The canonical helper is lower-bound/ceiling; any exact identity depends on the comparison against `cEmpire+0x84` or an invariant.
- Supported with a limit: context values 0/1/2 select distinct planet/solar/galaxy presentation branches.
- Rejected: context selection equals input/game-mode transition. The existing follow-up preserves these as separate axes.
- Medium: `010666a0/0106b500` release the newly materialized object. Their placement supports cleanup, but exact ownership is not closed.

## Family F — `010225d0`: batched space/navigation update and manager traversal

**Canonical roots:** `CTX` and `STAR` only (two roots; five selected root-edge rows). The smaller root set is high-information because the body consumes the context and manager boundaries separately in a world-adjacent traversal.

**Arguments and receiver:** Ghidra recovers `FUN_010225d0(int *param_1, int param_2)`. `param_1` is a traversal/queue owner; `param_2` is a signed update amount. A parse path is conditionally entered when `param_1` and `FUN_00c70c00` succeed. The exact queue/domain name is unresolved.

**Call order and root interaction:**

1. Ghidra renders an accumulation of `param_2` into the symbol `Simulator__sSpacePlayerData`, followed by a `>999` batching loop. The exact field/owner behind that rendered symbol is not promoted here. For each vector item the body parses a scalar and calls `FUN_00c83050`.
2. For a non-null owner, it obtains a time/position-like value, updates `FUN_00c72190`, and traverses an object list obtained through `FUN_01002bd0`.
3. Ghidra dataflow at `010227c4` shows the `STAR` receiver `uVar8` loaded from the vector element at `010227bf`, after the `01002bd0` traversal setup. It calls `FUN_00bb59b0`, compares the resolved object against `param_1`, and may repeat the time/position update path for a nonmatching object.
4. Each resolved object receives a virtual `+0xc0` call after processing. This is release-like in the same sense as the active-planet replacement helper, but the concrete object and slot name are not closed.

**Object identity and ownership:** the traversal reads manager/list objects and invokes virtual operations; the roots do not establish AddRef ownership. The `+0xc0` operation should remain a bounded cleanup candidate, not be promoted to destruction or erase without the concrete vtable owner.

**Lifecycle stage:** batched navigation/space update, with possible per-entry release/cleanup. It is not a direct materializer or world switch: it supports world/planet state consumption but does not allocate a new active planet or set `SpaceContext`.

**Evidence strength:** high for the two-root set, accumulator loop, vector-derived manager receiver, and call order. Medium for the semantic role of the list and `+0xc0` operation. No runtime evidence.

**Hypotheses and contradictions:**

- Supported: the function is a separate space/manager traversal consumer, not a wrapper around the noun or empire cache.
- Supported: the manager receiver comes from a vector entry, not from a proven global value alias.
- Rejected: this body is the authoritative `SpaceContext` transition writer. No direct `01021960` or `01022580` edge is present.
- Rejected: `+0xc0` proves destruction. It is a release-like call, but exact type and lifetime are unresolved.

## Family G — `010593e0`: tool/creature dispatch, empire context, and nested world transition

**Canonical roots:** `CTX`, `STAR`, `EMPIRE`, `AVATAR`, `CONTEXT`, and `PLANET` (six roots; 16 selected root-edge rows).

**Arguments and receiver:** Ghidra recovers `FUN_010593e0(int *param_1, undefined4 param_2, undefined4 param_3)`. `param_1` is a tool/creature action receiver; `param_2` and `param_3` select action variants and positions. The exact SDK method is unresolved.

**Call order and root interaction:**

1. The function rejects a null receiver or null receiver field. It reads `PLANET@01059404` and computes position/scale data from `param_3`; several virtual receiver calls apply the action.
2. It reads `CONTEXT@0105950d`. A non-zero context returns early. The Planet path reads `PLANET` again at `010596f9` and invokes a command/initialization path.
3. In the tool/creature relation path, it calls `AVATAR@01059b73`, `01059c3d`, `01059d31`, or `01059eda`. The nearby `STAR@01059b2a` and `EMPIRE@01059d3e` calls provide separate manager/registry data. It then invokes relationship and effect helpers, including `FUN_00d06240` and `FUN_00b3d2c0` as a relationship-manager-compatible path.
4. In the world path it calls `FUN_010027b0` at `01059ddf`, making the nested `010027b0` family a direct world-transition dependency. It then updates position/presentation through `FUN_00c3be70`, `00c3daa0`, and `00c3dae0`, and performs final cleanup through `FUN_00421cf0`.

**Object identity and ownership:** `AVATAR` is a borrowed creature pointer; `PLANET` is a borrowed active-planet pointer; `EMPIRE` is a borrowed map result. The avatar/manager/planet objects are used as inputs to tool/effect and world setup. No selected call proves that this function AddRefs a noun or empire or that the nested `010027b0` entry outlives the call.

**Lifecycle stage:** tool/creature action dispatch that can affect current-avatar/empire/relationship state and can request a world/planet transition. It is a gameplay integration family, not a save/load caller.

**Evidence strength:** high for six-root direct calls, the nested `010593e0 -> 010027b0` edge, and the separate avatar/manager/world callsites. Medium for the exact relationship/effect semantics and action-stage name. No runtime evidence.

**Hypotheses and contradictions:**

- Supported: this is a bridge from tool/creature state into current-avatar, empire, and world presentation state.
- Rejected: all of these roots share one owner. `AVATAR`, `PLANET`, and `EMPIRE` have different field/ownership contracts.
- Supported with a limit: the nested world transition is conditional on the selected action path, not universal for every call.
- Rejected: any action result is automatically persisted. No save/load root or `ClassSerializer` call is present in this body.

## Cross-family materialization, destruction, and serialization findings

### Materialization and creation

- `NOUN@00b21340` is the strongest direct materializer in this set. Its Ghidra body performs a map lower-bound, optionally invokes the create callback and `00ba8420`, conditionally clears/rebuilds the returned record, filters the manager list, appends accepted elements, and clears `needsUpdate`. It is called directly by `00bff2d0` and `00cfbc10` and by the `cf44c0` cleanup helper. This is **CONFIRMED** mechanics with a successor-key hazard and a **MEDIUM** ownership boundary for the create-result versus map-node allocation.
- `010027b0` allocates a `0x0c` linked list entry and calls `0102b1d0/0102be20` for a runtime world/planet object. This is **SUPPORTED** materialization, not a complete object ABI.
- `00aebe90` and `010593e0` consume already-materialized/current state; their numerous `FUN_00f473a0` calls are temporary allocation machinery, not root-object creation.

### Destruction, erase, and teardown

- The selected callers do not directly invoke the bounded empire-map eraser `00bad7a0` or the whole-map destructor path. They therefore do not prove cross-root empire erase.
- `00cfbc10 -> FUN_00cf44c0` is the strongest selected destruction-adjacent family. It obtains a noun/city record, conditionally calls `FUN_00bd9bb0`, clears an owner pointer, and performs vtable teardown. The exact identity and destruction policy remain **MEDIUM/UNRESOLVED**.
- `00c099e0 -> 00b1fd50` is a replacement boundary, not destruction: AddRef new, store, Release old for the probable `mpAvatar` field.
- `010593e0` reaches `010027b0`, whose trailing `010666a0/0106b500` calls are cleanup candidates, but their exact ownership is not proven.
- The separate `FUN_01022460` body is direct field teardown: it clears/releases active planet, active star, cached empire, and relationship-manager fields, releases the colony vector, and resets the empire ID. No selected family proves that this field teardown is ordered after all cross-root operations.

### Serialize/restore

- The selected root families contain no direct canonical edge to the authoritative persistence service accessor `00b3d440`, to `FUN_00b28ec0`, or to `FUN_00b279e0`.
- `00cfbc10` does contain an interface `Write` call in its phase-6 transition path. The receiver is a strategy/object obtained through a vtable, and the call is not statically bound to `ClassSerializer::Write`; treat it as serialization-adjacent mode/state output only.
- The authoritative static persistence spine remains `FUN_00b28ec0` (save candidate) -> header/ClassSerializer callbacks -> stream close/replacement and `FUN_00b279e0` (load candidate) -> restoration service calls. The concrete ClassSerializer write/read bodies are `0x00692900/0x00693e10`; the exact outer `.spo`/database envelope, object-reference table, atomicity, and automatic save on mode exit remain unknown (`knowledgegraph/research/architecture-resolution/followup-06-persistence.md:17-37`, `docs/analysis/serialization-model.md:253-299`).
- The authoritative docs classify the Cell serializable object as a save candidate, not as a proven complete field schema (`docs/analysis/serialization-model.md:222-251`). No cross-root caller here closes its survival or restore order.

## Competing hypotheses and contradictions

| ID | hypothesis | status | decisive evidence |
|---|---|---|---|
| H1 | The eleven roots are one singleton object | **Rejected as a static fact** | distinct globals, distinct return contracts, and unresolved publication/aliasing; existing KG says shared callers do not merge owners (`cross-root-relationships.json:53-59`, `:213-283`) |
| H2 | Selected callers coordinate a shared lifecycle without sharing one owner | **Supported** | `00cfbc10`, `00aebe90`, and `010027b0` show multi-domain sequencing with separate borrowed/owned contracts |
| H3 | `01021300` is an exact-find current empire cache | **Rejected** | `00ba9370` uses lower-bound/ceiling; cache miss stores the returned successor without exact-ID revalidation (`knowledgegraph/research/root-closure/track-e-empire-chain.md:46-53`, `:87-117`) |
| H4 | `00b21340` materializes by exact noun key | **Rejected** | direct lower-bound plus end-only check; successor payload can be used; no node-key equality check (`followup-noun-boundary.md:53-68`) |
| H5 | `00bff2d0` uses one canonical noun receiver for all avatar/empire operations | **Rejected as a complete claim** | all `CIV` sites use `CTX` in sampled bodies, but `AVATAR@00bff3b4` uses `01002bd0`; canonical `00b3d400` alias remains unresolved |
| H6 | `00c099e0` is an App game-mode registry transition | **Not established** | it uses `INPUT` and `STATE` and performs creature/avatar initialization, but has no direct `cGameModeManager::SetActiveModeAt` path |
| H7 | `00cfbc10` phases are `SpaceContext` values | **Rejected** | phase switch is an owner-local `+0xb4` state machine; space context is `sSpacePlayerData+0x10` and has a separate writer (`followup-space-lifecycle.md:170-178`) |
| H8 | The phase-6 `Write` call proves profile save | **Rejected as established** | no selected direct save/load edge; authoritative save/load candidates are separate bodies and ClassSerializer-backed |
| H9 | `FUN_00cf44c0` is a canonical noun/empire eraser | **Unresolved, medium support for cleanup** | release-like virtual calls and owner pointer clear are direct; exact noun/empire identity and map erase are not |
| H10 | `010027b0` owns a new world object until its trailing cleanup calls | **Plausible, not proven** | allocation/materialization precedes `010666a0/0106b500`; exact reference ownership and release order remain open |
| H11 | `010225d0` is a direct world switch | **Rejected as a primary claim** | it is a batched traversal/update; no direct context writer or active-planet replacement call is present |
| H12 | `00b5b800` carries the same mode ID as `cGameInputManager` | **Rejected** | opaque forwarded value has sentinel-dominated scalar use; input manager is a separate named pointer and field owner |
| H13 | Root co-call counts establish object identity | **Rejected** | canonical xref counting is direct-call evidence only; the existing KG explicitly preserves this limitation |
| H14 | Current-empire/civilization/noun pointers are owned by callers | **Rejected** | `SPACE`, `EMPIRE`, `CIV`, `AVATAR`, and `NOUN` readers return borrowed pointers; only cache/map/vector and explicit replacement writers change ownership |

## Runtime and contradiction register

- **Runtime evidence:** none. No trace, Wine run, save/load round trip, or original-process state observation was used or produced for this report.
- **Static positive:** canonical direct-call edges, Ghidra decompilation, CFG structure, field stores, virtual AddRef/Release calls, and the bounded P-code anchors listed above.
- **Most important contradiction:** the compact KG `high_information_shared_callers` list understates the direct root sets for `00bff2d0` and `010027b0`; the canonical xref rows and Ghidra callee lists show seven roots each. The report uses the canonical direct-call evidence for selection while retaining the KG list as a historical projection.
- **Most important unresolved contradiction:** `00b3d300` is repeatedly propagated into noun-layout consumers, but no selected direct chain proves that it is the canonical `00b3d400` noun-manager global. Conversely, `00bff2d0`'s `01002bd0 -> AVATAR` path is a concrete non-`CTX` receiver source.
- **Most important lifecycle contradiction:** field teardown exists in `01022460`, noun/city cleanup exists around `00cf44c0`, and mode/strategy callbacks exist in `00cfbc10`, but no selected caller closes one ordered teardown chain that covers all roots.
- **Persistence contradiction:** mode/state `Write` interfaces and serializer infrastructure exist, but no selected root caller directly reaches the strongest save/load bodies. Automatic save on mode exit and cross-root restore order remain unresolved.

## Authoritative inputs and provenance

- Canonical xrefs: `knowledgegraph/triage/xrefs-2540f2ca.tsv`, snapshot `2540f2ca`, 223,704 rows.
- Existing KG/report projection: `knowledgegraph/research/root-closure/cross-root-relationships.json` and `.md`.
- Root mechanics: `knowledgegraph/research/root-closure/followup-noun-boundary.md`, `followup-space-lifecycle.md`, `followup-receiver-provenance.md`, `track-e-empire-chain.md`.
- Noun/star lifecycle context: `knowledgegraph/research/architecture-resolution/track-02-star.md`, `followup-05-space-pair.md`, `track-11-space-records-conditional.md`.
- Authoritative state/save synthesis: `docs/analysis/simulator-root-closure.md`, `docs/analysis/gameplay-state-machines.md`, `docs/analysis/serialization-model.md`, and `knowledgegraph/research/architecture-resolution/followup-06-persistence.md`.
- Ghidra read-only program: `SporeApp.exe`, current analyzed project image; no re-import, re-analysis, save, type mutation, or program write was performed.
