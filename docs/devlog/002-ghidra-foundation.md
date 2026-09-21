# 002 — Ghidra foundation

**2026-09-20, afternoon.** Same afternoon as the bootstrap commit (`f6f850d`, 13:37) and the
repository audit ([chapter 001](001-repository-audit.md)). By now the project's division of
labor was fixed: the **analysis graph is Ghidra** — a headless project at
`~/ghidra-spore-project/` (program `SporeApp.exe`) reached through the GhidraMCP bridge on
`127.0.0.1:8089` — and it is the source of truth for functions, structures, and xrefs; the
**source graph** is codegraph (this C++ repo, which does not exist yet); and a **SQLite sidecar**
(`knowledgegraph/spore.db` + `kg.py`) holds only the cross-tool residue: test outcomes,
decisions, format mappings. That division held for the rest of the project. The problem was
that the one source of truth did not work. The analysis graph had two independent faults, and
this chapter is about fixing both and then reading what the graph actually says about the
game.

## Two broken things

### (a) The headless project was corrupt

The original headless import of `SporeApp.exe` had produced a project whose
`SporeProject.gpr` was 0 bytes — a project file that opens nowhere. We did not try to repair
it in place. The broken project was moved to `/tmp/opencode/ghidra/SporeProject.broken-backup/`
(kept as evidence, per the RECON's environment snapshot) and a fresh project was built from
scratch: import `SPORE/SporeBin/SporeApp.exe`, let auto-analysis run, then apply the SDK
symbol pass. The rebuild took the afternoon; the backup directory is now gone from `/tmp`
(tmp is not durable), so the 0-byte claim stands on the two documents that recorded it
(`AGENTS.md`, `docs/RECON-3.1.0.22.md`) rather than on anything we can re-inspect on disk.

### (b) The upstream symbol pass aborted on the first bad address

With the project rebuilt, the second fault showed up in the SDK import. The Spore-ModAPI
project ships `SDKtoGhidra/ImportSporeSDK.java` plus a Ghidra XML export of its symbol and
type database — a ready-made tool built for exactly this, so we used it first (the failure
documentation is the point of this paragraph):

1. **What was tried:** run the upstream `ImportSporeSDK.java` as a post-import script against
   `SporeGhidra_march2017.xml`.
2. **Why it seemed reasonable:** it is the community's official import path for Spore-ModAPI
   symbols into Ghidra; the XML was exported by the same people.
3. **What evidence contradicted it:** the pass died on its first non-function address with
   `XmlAttributeException: "Symbol exists but is not a function"` — concretely
   `Terrain::cTerrainSphereQuad::RenderAtmosphere` at `00fb6ca0`. The script's
   `processFunctionAddress` calls `CreateFunctionCmd`, and when that command fails it *throws*;
   the exception propagated out of the `FUNCTION_ADDRESSES` loop and stopped the whole pass.
   Import "succeeded" (the project saved), but only a prefix of the XML's function list was
   processed — the initial `STATE.md` recorded exactly this: *"the symbol pass stops early →
   not all SDK symbols imported."*
4. **What changed afterward:** we forked the script and made the pass total. See below.

## The defensive fork

The fix is small and is committed as `tools/ghidra/ImportSporeSDK.java` (1,073 lines,
commit `4927122`, 15:58): in `processFunctionAddresses`, each address is now processed inside
its own `try`/`catch`, so a bad symbol is **skipped and logged** (`SKIP function <name> at
<addr> : <exception>`) instead of aborting the pass. The script also takes its XML path from
`getScriptArgs()` (with the march2017 file as default), which is what lets the headless
recipe pass the XML as a positional argument.

The full reproducible recipe, now in `AGENTS.md`:

```
/opt/ghidra/support/analyzeHeadless ~/ghidra-spore-project SporeProject \
   -import SPORE/SporeBin/SporeApp.exe \
   -scriptPath tools/ghidra \
   -postScript ImportSporeSDK.java ~/apps/Spore-ModAPI/SDKtoGhidra/SporeGhidra_march2017.xml
```

Two non-obvious choices are encoded in it:

- **Language/compiler spec:** `x86:LE:32` with cspec `windows`. Ghidra 12 has no
  `msvc:LE:32:msvc` variant — the `windows` cspec is the correct MSVC-style one for 32-bit
  Windows in this Ghidra release.
- **The march2017 XML, not the `_disk` one:** the game at `./SPORE/` is the **GOG digital
  build** 3.1.0.22, and the Spore-ModAPI SDK export for it is `SporeGhidra_march2017.xml`.
  (The initial `STATE.md` had flagged this too — GOG = digital build.)

Result: **1,670 of 1,671 functions named, 1,895 structures imported, 1 documented skip** —
the `RenderAtmosphere` address that broke the upstream script. One bad symbol, skipped and
logged; the rest of the pass ran to completion.

The lesson we want recorded is not about Java. It is about tooling maintenance in an
AI-driven pipeline: upstream analysis scripts assume well-formed input, and a bulk pass over
1,671 addresses will meet a malformed one. A defensive wrapper (per-item try/catch, log and
continue) turns "the analysis aborts at an arbitrary point, silently" into "the analysis is
reproducible and its skips are auditable." Every bulk Ghidra script in this project is written
that way. (Separately, the audit's finding about Ghidra 12 API drift cost real time here —
several inline script iterations failed to compile against the OSGi classpath and accumulated
as `McpInline_*.java` corpses in `~/ghidra_scripts/`.)

## The recon

With a healthy project and a complete symbol pass, we ran a read-only reconnaissance over the
whole program and committed it as `docs/RECON-3.1.0.22.md` (same commit, 15:58). It is the
project's binary map. This chapter digests it; the confidence labels below are the report's
own (Appendix A).

### What the binary is

- **One 20.4 MB PE32 i386 executable**, image base `0x00400000`, entry `0x011e11a0`,
  MSVC v9 (`msvcr90`). **All engine code is statically linked into the EXE** — RenderWare,
  Havok 3.1.0 (embedded version string `4Havok-3.1.0`), the UTFWin UI framework, the whole
  simulator. Only `msvcr90.dll` and `steam_api.dll` ship in `SporeBin/`.
- **7 DBPF v3 `.package` archives** in `SPORE/Data/`, ~5 GB total. The DBPF *binary layout*
  itself was still UNKNOWN at this point (the packages exist; the format is to be derived
  later — [chapter 004](004-format-tooling.md)).
- Ghidra sees **58,757 functions**: 4,091 carrying SDK names (≈7%), 54,666 anonymous
  `FUN_*`. Plus 11,808 data types from the SDK import and 190 defined globals.

### The fact that shapes everything: no RTTI

An exhaustive symbol scan found **zero MSVC RTTI symbols** (`?AV...` type-info descriptors
absent) — **VERIFIED**. Consequence: class hierarchy cannot be recovered from the binary's
metadata. It can only come from **vtable data in `.rdata` plus the SDK's structure
definitions**. At recon time the project carried **0 vtable labels** (headless import never
ran vtable detection), so at this moment *no* class structure was labeled at all. This is
the single most important structural fact of the project, and it is the reason
[chapter 006](006-vtable-detection.md) exists.

### Bootstrap: the practical WinMain

There is **no `WinMain` symbol** — the CRT lives in `msvcr90.dll`, so the link target is
inside the DLL. The report marks the WinMain *location* as **HYPOTHESIS** and instead works
with the functional equivalent, the bootstrap state machine at `FUN_00e20860`
(**SUPPORTED**, decompiled):

- allocates a `CommandLine` object (0x40 bytes),
- calls `IAppSystem::Get()->Init(...)` / `->InitPlugins(...)` (vtable slots 0/1),
- state 3 builds `<InstallItems><InstallItem ContentId="%s"/></InstallItems>` XML from a
  0x38-byte item array and then **re-spawns itself** as a child process, passing
  `GetCommandLineA()` + `GetCurrentProcessId()` — the GOG/Steam install-items handshake
  (the game launches itself with ContentId args),
- states 7–10 select the restart flavor (0..3); state 9 is terminal.

The message pump is `FUN_00848210` (**SUPPORTED**): a `PeekMessageW` loop feeding
`TranslateMessage`/`DispatchMessageW`, exiting on `WM_QUIT` (0x12), with frame render via
vtable slot `0x5c`. It is invoked virtually — no static callers.

### The singleton spine

The design's load-bearing pattern is **free `X::Get()` functions returning global pointers**
(**VERIFIED** across multiple decompilations): `IAppSystem::Get` @ `0067dcc0` → global
`DAT_015fd890` (695 callers — the global app accessor), `cSimulatorSystem::Get` @ `00b3d330`
→ `DAT_0167eaf0`, and a **16-manager singleton block packed at `0x00b3d330–0x00b3d550`**
(cGameViewManager, cGameInputManager, cGameBehaviorManager, cGameNounManager,
cGameModeManager, cGamePersistenceManager, cGameTimeManager, cToolManager,
cRelationshipManager, cStarManager, cPlanetModel, cPlantSpeciesManager, cAnimalSpeciesManager,
cSpaceTrading, cUIEventLog, and friends). The setters write through struct-relative offsets
that Ghidra cannot resolve — i.e., there is one manager-registry struct in `.data` whose
layout is **UNKNOWN** at this point.

One vtable *was* recovered by hand: `cAppSystem`'s, at **`0x01413af0`**, 23 slots
(Init, InitPlugins at `007e93d0`, +21 more; slots 19–21 a repeated thunk), reconstructed
from the `.rdata` pointer table — **SUPPORTED**. That manual reconstruction is exactly the
work a vtable-detection pass would do at scale.

### Services, and what is dead

- **Pollinator = EA's Spore online service** (**SUPPORTED**: endpoint strings
  `pollinator.spore.com`, `/pollinator/event/upload`, `/pollinator/telemetry`, `/pollinator/atom/asset`,
  User-Agent `SPORE/%s (Pollinator; %s)`). It is now defunct.
- **steam_api = a dead GOG shim** (**SUPPORTED**): only `SteamAPI_Init`/`SteamAPI_Shutdown`
  are imported; the `SteamApps` path is used for install items. No other real networking
  exists in the EXE.

### Gaps (report §9)

1. **No vtable labels** (0 of them) — headless never ran vtable detection; class hierarchy
   is unlabeled.
2. **54,666 unnamed functions** — SDK names cover ≈7%.
3. **Decompiler garbling** on vtable/`thiscall` code (fake fields, spurious dtor calls) —
   pseudocode is noisy until types are applied.
4. **WinMain not directly identified** (CRT in msvcr90) — HYPOTHESIS only.
5. **Struct-relative singleton writes** unresolvable — the manager-registry layout needs
   manual work.
6. **EP1 diff not started** (24.9 MB EP1 build, same import surface).

### Recommendations (report §10)

Priority order for the clean-room build: **(1) DBPF v3 parser** (the gate to everything),
**(2) `Stream` / property serialization** (`App::Property*`, 81 SDK functions — the
data-model spine), **(3) `cResourceManager`** (load path over DBPF),
**(4) `cAppSystem` / `cSimulatorSystem` singleton skeletons** (mirror the
Get/Init/InitPlugins lifecycle), **(5) `Simulator::Cell` + `cGameModeManager`** (first
playable stage). **Defer:** Pollinator client (dead service — stub it), Skinner, Sporepedia,
EP1-specific code. And before any Phase-1 code lands in Ghidra-dependent work: run a
**vtable detection pass** — that single step unlocks the biggest share of the remaining 54k
functions.

The report also established the **evidence discipline** the journal inherits: every claim
carries a confidence label on the Appendix A scale — **UNKNOWN** (no reliable semantic
info), **HYPOTHESIS** (naming/analogy only), **INFERRED** (names + partial
decompilation/xrefs), **SUPPORTED** (decompilation + multiple independent evidence sources),
**VERIFIED** (exhaustively checked in the binary) — and the same scale is used throughout
this devlog.

## Cross-links

- Back: [001 — Repository audit](001-repository-audit.md) (the afternoon this followed;
  its "Ghidra 12 API friction" finding is the `McpInline_*.java` debris mentioned above).
- Forward: [003 — Renderware research](003-renderware-research.md) (the same day, ~1.5 h
  later — the static-linking fact above is the entry point into that chapter).
- Forward: [006 — Vtable detection](006-vtable-detection.md) (closes gap §9.1; the
  0-label state is the baseline it improves on).

### Outcome

| Proven | Open |
|---|---|
| Corrupt headless project diagnosed (0-byte `.gpr`), backed up, and rebuilt from scratch — the analysis graph is reproducible | The backup lives in `/tmp` (not durable); the 0-byte claim rests on the two documents that recorded it |
| Defensive import fork is reproducible via the committed `analyzeHeadless` recipe: **1,670/1,671 functions named, 1,895 structures, 1 logged skip** | The one skipped symbol (`cTerrainSphereQuad::RenderAtmosphere` @ `00fb6ca0`) remains unnamed |
| Full binary map with per-claim confidence (RECON committed, `4927122`): static-link inventory, no-RTTI (VERIFIED), bootstrap state machine, singleton spine, dead services | **0 vtable labels** at this point — no class hierarchy is labeled |
| | 54,666 unnamed functions; WinMain location (HYPOTHESIS); manager-registry struct layout (UNKNOWN); EP1 diff not started |
