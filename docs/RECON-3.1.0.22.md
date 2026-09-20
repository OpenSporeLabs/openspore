# Spore 3.1.0.22 — Ghidra Reconnaissance Report

Read-only recon over the Ghidra project `~/ghidra-spore-project/SporeProject`
(program `SporeApp.exe`, rebuilt headless + defensive SDK import).
Date: 2026-09-20. All addresses are PE RVA as Ghidra displays them (image base `0x00400000`).

---

## 1. Binary inventory

| Item | Detail |
|------|--------|
| `SPORE/SporeBin/SporeApp.exe` | 20.4 MB, PE32 i386, MSVC (msvcr90 = VC9), base `0x00400000`, entry `0x011e11a0` |
| `SPORE/SporebinEP1/SporeApp.exe` | 24.9 MB EP1 build; same import surface; used for differential comparison |
| Engine code | **All in the EXE** — no engine DLLs. RenderWare, Havok 3.1.0, UTFWin, simulator all statically linked |
| Data | 7 DBPF v3 `.package` archives in `SPORE/Data/` (~5 GB total) + `Config/ConfigManager.txt` |

Ghidra project stats: **58,757 functions** (4,091 custom-named via SDK, 54,666 `FUN_*`),
11,808 data types, 190 defined globals, **0 vtable labels**, 5 AddRef/Release thunks.
**No MSVC RTTI** in the binary (zero `?AV...` symbols) — inheritance is not recoverable from the binary; only from vtable data + SDK structures.

SDK import (`SporeGhidra_march2017.xml`): 1,670/1,671 functions named, 1,895 structures imported
(1 skip: `Terrain::cTerrainSphereQuad::RenderAtmosphere` @ `00fb6ca0`, "symbol exists but is not a function").

## 2. Entry points & bootstrap chain

```
entry 0x011e11a0 → ___tmainCRTStartup (msvcr90.dll, external)
```

- No `WinMain` symbol exists; the CRT lives in msvcr90.dll so the link to `WinMain` is inside the DLL.
  Behavioral tracing instead of CRT tracing.
- **Bootstrap state machine `FUN_00e20860`** (the practical "WinMain body"):
  - allocates a `CommandLine` object (0x40 bytes, allocator `FUN_00f473a0`),
  - calls `App::IAppSystem::Get()->Init(...)` and `->InitPlugins(...)` (virtual, vtable slots 0/1),
  - state `3` builds XML `<InstallItems><InstallItem ContentId="%s"/></InstallItems>` from a 0x38-byte item array,
    then **re-spawns itself** as a child process passing `GetCommandLineA()` + `GetCurrentProcessId()`
    (the GOG/Steam install-items handshake — the game launches itself with ContentId args),
  - states 7–10 select the restart flavor (0..3), state `9` = terminal.
- Callers of the state machine: `FUN_00de4c20`, `FUN_00df5ac0`.
- **Message pump `FUN_00848210`**: `PeekMessageW` loop → `TranslateMessage`/`DispatchMessageW`,
  `WM_QUIT` (0x12) exit, `InvalidateRect`, frame render via vtable slot `0x5c`. Invoked virtually (no static callers).
- Window strings: `"Spore"`, `"My Spore Creations/"`; DX failure strings:
  `"Could not create the Graphics Device.\nDirect X is unavailable."`.

## 3. Architecture map (SDK namespace distribution)

Top-level: App(148), Simulator(93), UTFWin(71), Editors(39), Resource(28), IO(22),
Graphics(14), Sporepedia(12), ArgScript(10), Palettes(10), Skinner(8), RenderWare(5), Terrain(5), Audio(4), UI(3).

Notable second-level clusters:

| Namespace | Count | Role |
|-----------|-------|------|
| `App::Property` / `PropertyList` / `DirectPropertyList` | 52/15/14 | Data-driven property system — the core serialization/deserialization model |
| `App::Canvas` | 12 | Rendering canvas |
| `App::cCellModeStrategy` | 11 | Game-mode strategies (init/dispose) |
| `App::cCameraManager` | 5 | |
| `Simulator::Cell` (Cell, cCellGFX, cCellUI, cCellGame, cCellDataReference_) | 26 | Cell stage: models, effects, UI, advect/damage, player movement |
| `Simulator` managers | ~16 singletons | see §6 |
| `Simulator` world | cPlanet, cPlanetModel, cPlanetRecord, cSolarSystem, cStarManager, cStarRecord, cSpaceTrading, cTerraformingManager, cCity | Space stage |
| `Simulator` creature | cCreatureGameData, cCollectableItems, cPlayerInventory, cRelationshipManager, cTribeArchetype, cMissionManager, cScenario*, cToolManager + tool strategies | Creature stage |
| `UTFWin::Window` / `ImageDrawable` | 24/6 | EA's UTFWin UI framework (window classes, drawables) |
| `Editors::cEditor` | 21 | Editor shell: Initialize/Dispose/HandleMessage/OnExit/OnKeyDown/OnMouseUp/SetActiveMode |
| `Resource::cResourceManager` | 7 | Asset loading |
| `ArgScript::FormatParser` | 7 | Script language parser |
| `Skinner::cSkinnerTexturePainter` | 6 | Texture painting/skinning |
| `Sporepedia` (incl. cSPAssetDataOTDB) | 12 | Sporepedia database |

624 `c*` class names / 63 `cSP*` names survive in strings.

## 4. Module & DLL dependencies

22 imported DLLs: `ADVAPI32, d3d9, d3dx9_27, dbghelp, DINPUT8, DSOUND, GDI32, IMM32,
KERNEL32, MSVCR90, ole32, PSAPI, SHELL32, steam_api, USER32, USP10, VERSION, WINMM, WS2_32, WSOCK32` (+2 ordinals-only).

- **RenderWare** (RW9-era) is the 3D renderer, statically linked; the `d3d9` IAT is present but
  **no direct `Direct3DCreate9` calls exist in the EXE** — D3D is driven inside RenderWare's own code.
- **Havok 3.1.0** physics embedded (version string `4Havok-3.1.0`, `hk*` classes).
- **steam_api** = `SteamAPI_Init`/`SteamAPI_Shutdown` only (GOG no-CD-key shim); `SteamApps` path used for install items.
- Real networking: only the Pollinator service client (§7) via `WS2_32`; `RegisterDragDrop`, `SetWindowsHookExA` (keyboard hook) present.

## 5. Types & object model

- 11,808 data types from the SDK import (structures, enums, typedefs) — the canonical type vocabulary.
- Calling conventions: `__thiscall` dominant; decompiler shows `__fastcall` on some CRT-adjacent code.
- **Singleton pattern is the spine of the design**: each manager exposes a free `X::Get()` function
  returning a global pointer. No RTTI → class hierarchy must be reconstructed from vtable data + SDK structs.
- Ghidra vtable labels: none (headless import never ran vtable detection) — see §8 gaps.

## 6. Core runtime structures (confirmed by decompilation)

| Structure | Evidence |
|-----------|----------|
| `App::IAppSystem` (interface) + `App::cAppSystem` | `IAppSystem::Get` @ `0067dcc0` → global `DAT_015fd890` (set by `FUN_0067deb0`, the singleton setter = vtable slot 0). **cAppSystem vtable @ `0x01413af0`** (23 slots: Init, InitPlugins `007e93d0`, +21 more; slots 19–21 are a repeated thunk `00b1e4d0`). 695 callers of `IAppSystem::Get` — it's the global app accessor |
| `CommandLine` | 0x40-byte object, vtables `PTR_FUN_013eb90c` / `PTR_FUN_013eb844` |
| `Simulator::cSimulatorSystem` | `Get` @ `00b3d330` → global `DAT_0167eaf0` |
| Simulator manager singleton block | `::Get` functions packed at `0x00b3d330–0x00b3d550`: cGameViewManager, cGameInputManager, cGameBehaviorManager, cGameNounManager, cGameModeManager, cGamePersistenceManager, cGameTimeManager, cToolManager, cRelationshipManager, cStarManager, cPlanetModel, cPlantSpeciesManager, cAnimalSpeciesManager, cSpaceTrading, cUIEventLog. Writes happen via struct-relative offsets (unresolvable by Ghidra) → one manager-registry struct in `.data` |
| `Simulator::cCreatureGameData` | `Get` @ `00d2e340` (evo points, ability mode, avatar scale) |
| `Simulator::cObjectPool_` | `Get` @ `00b72320` |
| `Editors::cEditor` | full lifecycle SDK-named (Initialize `00584300`, HandleMessage `00591fa0`, SetActiveMode `00587270`…) |

Frame timing: `Simulator::TimeAtStartOfFrame` @ `00b63980`.

## 7. Services & online

**"Pollinator" = EA's Spore online service** (correction to earlier notes): `pollinator.spore.com`,
endpoints `/pollinator/event/upload`, `/pollinator/telemetry`, `/pollinator/atom/asset`,
`/pollinator/atom/creatureMatch`, `/pollinator/atom/static/`, registration form controls.
User-Agent: `SPORE/%s (Pollinator; %s)`. Resource paths use `Pollinator/...` prefixes (MVJ filters, CookieHandler, cJobResultMessage).
For the GOG build the Steam layer is a dead shim; Pollinator endpoints are the real (now-defunct) backend.

## 8. Resource pipeline

- **DBPF v3** (BioWare Data Package Format) — 7 `.package` files in `SPORE/Data/`.
- Extensions seen: `.eBT` (448 refs — the dominant script/asset blob), `.RSU`, `.RWU`, `.PSU`, `.PWU`, `.WSU`, `.QSU`, `.SWU`, `.QWU`.
- `Resource::cResourceManager` (7 SDK functions) + `IO` namespace (22) = the load path.
- `Config/ConfigManager.txt` — data-driven config script language (parsed by `ArgScript`).
- Asset metadata path `Pollinator/cAssetMetadata` suggests per-asset metadata records inside packages.

## 9. Knowledge gaps

1. **No RTTI / no vtable labels** — class hierarchy unknown; cAppSystem vtable was reconstructed by hand from `.rdata` (`0x01413af0`). A headless vtable-detection pass (e.g. Ghidra's "Create Vtable" / vtable finder script) would label all vtables and let `set_function_this_type`/namespace grouping work.
2. **54,666 unnamed functions** — SDK names only ~7% of them.
3. **Decompiler garbling** on vtable/thiscall code (fake fields like `field_28.mpCapacity`, spurious dtor calls) — expect noisy pseudocode until types are applied.
4. **WinMain not directly identified** (CRT in msvcr90.dll); the bootstrap state machine `FUN_00e20860` is the functional equivalent and is well understood.
5. **Struct-relative singleton writes** unresolvable — the manager-registry struct in `.data` needs manual layout.
6. **EP1 diff** not started (24.9 MB vs 20.4 MB; same import surface).
7. Ghidra 12 inline-script API friction (several API renames vs. older docs) — 10+ failed scripts accumulated in `/home/juanr/ghidra_scripts/`; clean up before future bulk script work.

## 10. Recommendations for Phase 1+

Priority order for clean-room reimplementation (what to reverse first, what Phase 1 can safely ignore):

1. **DBPF v3 parser** — the gate to everything; derive layout from the 7 packages (header + TOC format is stable across BioWare titles) without copying EA code.
2. **`Stream` / property serialization** — `App::Property*` (81 SDK functions) is the data model spine; round-trip tests against original files.
3. **`cResourceManager`** — load path over DBPF.
4. **`cAppSystem` / `cSimulatorSystem` singleton skeletons** — mirror the Get/init/InitPlugins lifecycle.
5. **`Simulator::Cell` + `cGameModeManager`** — first playable stage.
6. Defer: Pollinator client (dead service — stub it), Skinner, Sporepedia, EP1-specific code.

Before Phase 1 code lands in Ghidra-dependent work: run a **vtable detection pass** on the project
(§9.1) so that class/vtable structure is labeled; that single step unlocks the biggest share of the remaining 54k unnamed functions.

---

## Appendix A — Evidence & confidence table

Scale: **UNKNOWN** no reliable semantic info · **HYPOTHESIS** naming/analogy only ·
**INFERRED** names + partial decompilation/xrefs · **SUPPORTED** decompilation + multiple
independent evidence sources · **VERIFIED** exhaustively checked in the binary.

| Area | Confidence | Basis |
|------|-----------|-------|
| No MSVC RTTI in binary | VERIFIED | exhaustive symbol scan: zero `?AV...` / RTTI type-info symbols |
| Singleton `X::Get()` spine of design | VERIFIED | multiple decompilations: `IAppSystem::Get` @ `0067dcc0` → `DAT_015fd890`, `cSimulatorSystem::Get` @ `00b3d330` → `DAT_0167eaf0`, 16-manager block `0x00b3d330–0x00b3d550` |
| cAppSystem vtable @ `0x01413af0` (23 slots) | SUPPORTED | reconstructed from `.rdata` pointer table; slot targets decompiled; 695 `Get()` callers |
| Bootstrap state machine `FUN_00e20860` + self-respawn install-items handshake | SUPPORTED | decompiled: CommandLine alloc, `Init/InitPlugins`, `<InstallItems>` XML, child re-spawn |
| WinMain location | HYPOTHESIS | no symbol; CRT in msvcr90.dll — state machine is the functional equivalent |
| Message pump `FUN_00848210` | SUPPORTED | decompiled `PeekMessageW`/`DispatchMessageW`/`WM_QUIT` loop |
| RenderWare renderer, D3D driven internally (no direct `Direct3DCreate9` in EXE) | SUPPORTED | IAT present, zero call xrefs from EXE code |
| Havok 3.1.0 physics embedded | SUPPORTED | version string `4Havok-3.1.0`, `hk*` type names |
| steam_api = GOG dead shim | SUPPORTED | only `SteamAPI_Init/Shutdown` imported; `SteamApps` path strings |
| Pollinator = EA online service (defunct) | SUPPORTED | endpoint strings `pollinator.spore.com`, User-Agent `SPORE/%s (Pollinator; %s)` |
| App::Property serialization is the data-model spine | INFERRED | 81 SDK-named functions; not yet decompiled |
| Resource::cResourceManager + IO = load path over DBPF v3 | INFERRED | SDK names + 448 `.eBT` extension refs; DBPF layout itself not yet parsed |
| DBPF v3 binary format | UNKNOWN | packages exist; layout to be derived in Phase 1 |
| Editors::cEditor lifecycle (Initialize/HandleMessage/…) | INFERRED | full SDK naming; bodies not inspected |
| Cell / space / creature stage systems, cGameModeManager | HYPOTHESIS | SDK names + namespace grouping only |
| ArgScript/ConfigManager script language | HYPOTHESIS | `ConfigManager.txt` exists; parser bodies not read |
| Sporepedia, Skinner | HYPOTHESIS | names only |
| Manager-registry struct layout in `.data` | UNKNOWN | struct-relative writes unresolvable by Ghidra (gap §9.5) |

---

### Environment snapshot (for reproducibility)
- Ghidra 12.1.2, profile `ghidra_12.1.2_DEV`, GhidraMCP 7.0.0 headless on `127.0.0.1:8089` (`GHIDRA_MCP_ALLOW_SCRIPTS=1`), project dir `/home/juanr/ghidra-spore-project`.
- Import: `analyzeHeadless ... -import SPORE/SporeBin/SporeApp.exe` (x86:LE:32:default, cspec `windows`), post-script = defensive `ImportSporeSDK.java` (committed at `tools/ghidra/`).
- Original broken project backed up at `/tmp/opencode/ghidra/SporeProject.broken-backup/`.
