# Track A — service identity closure

Snapshot `f0e310e0`; canonical xrefs `2540f2ca`; binary SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`. This is static-only closure. No Wine, runtime trace, source edit, SPORE edit, or Phase-0 interface edit was made.

## Adjudication

### `0x00b3d300` — `DAT_0167eae0`

- **Mechanics — SUPPORTED:** six-byte no-argument accessor; `mov eax, ds:0x167eae0; ret`; 1,097 direct callers, 252 gameplay callers, 1,941 canonical xref rows.
- **Classification — INFERRED, high mechanics:** global simulator/game context or owner object. It is service-locator-like in behavior, but a formal service locator is not proven.
- **Not proven:** concrete C++ class, cache validation, lazy refresh, nullability, AddRef/Release ownership, or a service map. The root itself only reads the global slot.
- **Dominant invariant:** sampled callers move the return into `ECX` and call owner-scoped context/player/object/state-transition helpers. They do not directly dereference the root return as a vtable or field in the selected windows.
- **Cross-domain evidence:** distinct callers span Simulator gameplay/support, Unknown engine implementation, App, UTFWin, IO, Editor, Math, GameGlobal, and UI. This is a shared boundary, not one narrow manager’s domain-specific accessor.

### `0x00b3d2a0` — `DAT_0167eae4`

- **Mechanics — SUPPORTED:** six-byte no-argument accessor; `mov eax, ds:0x167eae4; ret`; 314 direct callers, 101 gameplay callers, 510 canonical xref rows.
- **Classification — SUPPORTED mechanics / INFERRED exact identity:** cached singleton manager and registry owner; probable `Simulator::cStarManager*` or a layout-compatible manager pointer.
- **Not the registry lookup itself:** 134 of 314 distinct callers also directly call `0x00ba9370`; the root returns the receiver, while `0x00ba9370` performs the empire lower-bound lookup.
- **Layout evidence — SUPPORTED:** `0x00ba9370` reads the returned receiver at `+0x150` (`mEmpires`) and `+0x154` (map end storage). `0x00b3d2c0` directly loads `DAT_0167eae4` into `ECX` and tail-jumps to `0x00c4f030`, which reads `[ECX+0x204]`, matching SDK `cStarManager::mpRelationshipManager`.
- **Identity caveat:** SDK-declared `Simulator::cStarManager::Get` at `0x00b3d3a0` returns `DAT_0167eb0c`, a different global. The `0x00b3d2a0` slot is therefore a cStarManager-compatible cached/alternate accessor, not proven to be the canonical SDK getter slot.

## High-information call chains

### Shared simulator context: `0x00b3d300`

| Caller | Subsystem/class | Exact chain | Invariant |
|---|---|---|---|
| `0x00c099e0` | Simulator/GAMEPLAY_LOGIC; initialization/state-transition candidate | `0x00c09a35 -> 0x00b3d300 -> 0x00b20c60(0x018eb45e) -> returned object vtable+0x0c`; `0x00c09af0 -> 0x00b1fd50`; `0x00c09b21 -> 0x00b225d0` | Context is used for object lookup and transition helpers; sampled body does not initialize the global slot. |
| `0x00bff2d0` | UTFWin/ENGINE_IMPLEMENTATION per triage-v6 | `0x00bff370 -> 0x00b25f40`; `0x00bff3e9/0x00bff408 -> 0x00b25fb0/0x00b21340`; `0x00bff471 -> 0x00b25c30`; `0x00bff4b5 -> 0x00f67d90`; `0x00bff4f9/0x00bff56f/0x00bff5a6/0x00bff5d0/0x00bff607 -> 0x00b25fb0` | One context value is repeatedly used as a receiver across noun/player/game-data operations during a transition. |
| `0x00aebe90` | UTFWin/ENGINE_IMPLEMENTATION; SDK boundary overlaps `Simulator::cCommManager::ShowCommEvent` | `0x00aebfa4/0x00aec191/0x00aec3a4/0x00aec3d1/0x00aec42b/0x00aec44c/0x00aec49f/0x00aec56a -> 0x00b20750`; `0x00aec5b6 -> 0x00b25fb0`; `0x00aece60 -> 0x00f67d90` | Event/comm orchestration resolves player/civilization state through the shared context. |
| `0x00c8e5bb` | Simulator/GAMEPLAY_SUPPORT | `0x00c8e5c3 -> 0x00b3d300 -> 0x00b20c60`; returned object later uses vtable `+0xe8` and fields `+0x5a8/+0xc0` | Root is the owner/context, not the returned domain object. |
| `0x00c8eb90` | Simulator/GAMEPLAY_SUPPORT | `0x00c8eb93 -> 0x00b3d300 -> 0x00bfc5f0`; returned object uses vtable `+0x4c`; `0x00c8ebbd -> 0x00b3d2c0` | A multi-root operation uses separate context and relationship/state bridges. |
| `0x00cf84a0` | Simulator/GAMEPLAY_SUPPORT | `0x00cf84d2 -> 0x00b3d300 -> 0x00b25fb0`; downstream result reads `+0xb0/+0xb4`; `0x00cf84fa -> 0x00b3d380` | The `+0xb0/+0xb4` fields belong to the downstream result, not to `DAT_0167eae0`. |
| `0x010027b0` | Simulator/GAMEPLAY_LOGIC; `Simulator::cSimulatorSpaceGame::Get` | `0x010027bb -> 0x00b3d300 -> 0x00f67d90 -> cPlayer+0x124c` | Shared context resolves current-player state. |
| `0x010225d0` | Simulator/GAMEPLAY_LOGIC; `Simulator::SpaceTeleportTo` | `0x0102269d/0x0102271d/0x010227eb/0x0102286a -> 0x00b3d300 -> 0x00f67d90`; result is used around `cPlayer+0x11c0` | Space navigation consumes the context for player state. |
| `0x010593e0` | Simulator/GAMEPLAY_LOGIC; `Simulator::cDefaultBeamTool::WhileFiring` | `0x01059713 -> 0x00ace2c0 -> 0x00ac9dd0`; `0x01059da7/0x01059dbd -> 0x00f67d90 -> cPlayer+0x124c -> 0x00c755c0` | Tool behavior uses current-player/posse state through the context. |

### Manager/registry owner: `0x00b3d2a0`

| Caller | Subsystem/class | Exact chain | Invariant |
|---|---|---|---|
| `0x01021300` | Simulator/GAMEPLAY_SUPPORT; current-player empire cache | `0x01021321 -> 0x00b3d2a0 -> 0x00ba9370`; result compares `cEmpire+0x84`; cache pointer is `sSpacePlayerData+0x1c` | Root is used on cache miss/ID mismatch; `0x00ba9370` resolves the payload. |
| `0x00aebe90` | UTFWin/ENGINE_IMPLEMENTATION; comm/event boundary | `0x00aec121 -> 0x00b3d2a0 -> 0x00ba9370` | Same subsystem that uses `0x00b3d300` for context also uses this root for identity lookup. |
| `0x00b3d2c0` | Simulator/GAMEPLAY_SUPPORT; direct-global bridge | `0x00b3d2f0: mov ecx, ds:0x167eae4; jmp 0x00c4f030`; `0x00c4f030` reads `[ecx+0x204]` | Directly corroborates a manager receiver with the SDK `mpRelationshipManager` offset. |
| `0x0102df20` | Simulator/GAMEPLAY_LOGIC; high fan-out orchestration | `0x0102e034/0x0102e073/0x0102e0aa/0x0102e0c3/0x0102e0dc -> 0x00ba9370`; `0x0102e40b -> 0x00ba9370`; `0x0102ec03 -> 0x00ba9370` followed by `0x0102ec10 -> 0x00b3d300` | Manager receiver is repeatedly used for ID resolution before broader dispatch. |
| `0x0102d1b0` | Pollinator/GAMEPLAY_SUPPORT | `0x0102d24a/0x0102d6ab -> 0x00b3d2a0 -> 0x00ba6490`; `0x0102d2ee -> 0x00ba6490`; `0x0102d32e -> 0x00bb59b0` | The same manager contract crosses into Pollinator identity/player-civilization work. |
| `0x010027b0` | Simulator/GAMEPLAY_LOGIC; `Simulator::cSimulatorSpaceGame::Get` | `0x01002827/0x010028ff -> 0x00b3d2a0`; `0x00ba9370` result is compared at `cEmpire+0x84` | Decisive multi-root chain: current-player context versus manager-owned empire identity. |
| `0x010225d0` | Simulator/GAMEPLAY_LOGIC; `Simulator::SpaceTeleportTo` | `0x010227c4 -> 0x00b3d2a0 -> 0x00bb59b0` | Space navigation uses the manager separately from `0x00b3d300`. |
| `0x010593e0` | Simulator/GAMEPLAY_LOGIC; `Simulator::cDefaultBeamTool::WhileFiring` | `0x01059a51 -> 0x00885c90`; `0x01059b2a -> 0x00bb1080`; `0x01059c5a -> 0x00ba6490`; `0x01059d37 -> 0x00ba9370`, all after `0x00b3d2a0` | Tool behavior crosses the manager boundary for identity/space operations. |

## Root relationship and subsystem invariants

- `0x00b3d300` and `0x00b3d2a0` have **81 common distinct callers**. Representative shared callers are `0x00aebe90`, `0x010027b0`, `0x010225d0`, `0x010593e0`, and `0x0102df20`.
- `0x00b3d2a0` and `0x00b3d2c0` have **40 common distinct callers**. The direct `+0x204` bridge is stronger evidence than fan-in alone.
- The roots are complementary: `0x00b3d300` supplies shared simulator/player context; `0x00b3d2a0` supplies a cStarManager-compatible owner for identity and space operations. They are not interchangeable.
- The frozen interface’s “many discarded returns” observation remains valid for `0x00b3d300`; selected high-information windows instead demonstrate receiver propagation, not a universal field contract.

## Initialization/teardown

No initialization, allocation, teardown, lock, or direct global write was established for either root. A read-only `objdump` scan found only:

- `0x00b3d300` reading `DAT_0167eae0`;
- `0x00b3d2a0` reading `DAT_0167eae4`;
- `0x00b3d2c0` directly reading `DAT_0167eae4` into `ECX`.

`0x00c099e0` is a lifecycle/state-transition candidate that uses `0x00b3d300`, but the sampled windows do not initialize the slot. Do not synthesize constructor/destructor ordering or a live-before-first-call invariant.

## Contradictions and unresolved points

1. `0x00b3d300` is service-locator-like but not a proven formal service locator: there is no service map, key lookup, or service enumeration in the root.
2. `0x00b3d300` is a constant global accessor, but cached-interface semantics are unproven: no refresh, validation, or reference-management operation is present.
3. `0x00b3d2a0` is not itself the registry lookup: `0x00ba9370` is the lookup, using the returned object’s `+0x150` map.
4. The `+0x150/+0x154/+0x204` layout strongly matches `cStarManager`, but SDK `cStarManager::Get` at `0x00b3d3a0` returns `DAT_0167eb0c`, not `DAT_0167eae4`. Aliasing, alternate lifetime, and SDK/Ghidra boundary ambiguity remain open.
5. Domain fields observed after calls (`cPlayer+0x124c`, `cPlayer+0x11c0`, downstream result `+0xb0/+0xb4`) are not fields of the root return itself.

## Downstream constraints

- Keep both roots as no-argument raw global-slot accessors.
- Keep `0x00b3d2a0` distinct from `0x00b3d2c0`; the latter directly reads the same global and exposes `+0x204`.
- Preserve `0x00ba9370` lower-bound/null behavior and `0x01021300` cache-validation ordering.
- Do not flatten these roots with `0x00b3d350` or `0x00b5b800`; their caller invariants and backing slots differ.
- Do not assign concrete ownership, nullability, initialization, or AddRef/Release behavior without a direct writer or lifecycle chain.
- All conclusions remain static; no runtime or differential evidence is claimed.

## Evidence boundary

Primary committed evidence: `docs/analysis/simulator-shared-state-interface.md`, `knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json`, `knowledgegraph/triage/xrefs-2540f2ca.tsv`, `knowledgegraph/triage/unknown-high-investigation-f0e310e0.json`, `.spore-analysis/ghidra-exports/{functions.tsv,structs.tsv,structs_fields.tsv,sdk_functions.tsv,spore_sdk.xml}`, and the committed unknown-high dossiers/decompiled SDK exports. Supplemental exact call-window/global-reference checks used read-only `objdump` only. The Ghidra bridge was reachable but had no open program; headless project listing/opening was unavailable because the GUI `PluginTool` is not exposed, so no live Ghidra query was performed.
