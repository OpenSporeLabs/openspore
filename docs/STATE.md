# OpenSpore — Project State

Current phase: **Reconstruction phase (2026-09-23) — community Ghidra work made directly usable + playable Cell Stage slice + UNKNOWN-HIGH adjudication (triage-v6, 699/862 resolved) + Reconstruction Readiness Audit (strategy D)** (see §6, §14, §15). Priority is REUSE → UNDERSTAND → REIMPLEMENT → TEST → PLAYABLE (docs/SPORE-RECONSTRUCTION-ROADMAP.md). The community SDK (Spore-ModAPI, rev cbf9206) + local Ghidra project (58,757 fns, 1,666 SDK-named, 2,035 structs) are the knowledge base; exports at git-ignored `.spore-analysis/ghidra-exports/`; KG indexes the full binary (65,461 nodes / 20,397 edges / 25,561 fields, provenance on every ingested row). `cell_stage` now runs the original Cell-Stage pipeline end-to-end on real GOG assets (decode → sim → gfx → scene → render + HUD; deterministic raster output; ctest 36/36). The cell-movement replacement stays `replaced-approx` (differential-verified against the decompilation reference); promotion to `replaced-verified` is blocked on the cell-mode trace, and S5 was already run 2026-09-22 and recorded **NEGATIVE** (devlog 018: SporeApp.exe self-exits under Wine before Cell Stage; run #1 reached the menu then the process tree exited clean ~12.7 s in).
Cell campaign: **COMPLETE 2026-09-23** — all 32 targets executed: 31 DONE, CS-32 PARTIAL (only its trace-gated verification sub-part BLOCKED). `docs/replacement-status.json` (18 subsystems): 4 replaced-verified / 1 replaced-approx / 3 replaced-stub / 1 approximated / 3 supported / 2 inferred / 2 hypothesis / 2 unknown. The CS-32 trace sub-part is verification-only: it pins sCellGame field semantics beyond decompilation, records KG trace_run artifacts, and would promote the replaced-approx entry; it cannot run until the Wine boot-stability blocker from devlog 018 is diagnosed. The campaign is complete without it.
Machine: **CachyOS / Arch** (use `pacman`, not `apt`).

## 1. Environment (Phase-0 table; ✅-verified rows re-checked 2026-09-21, rest carried over)
| Item | Status | Location |
|------|--------|----------|
| Ghidra 12.1.2 | ✅ verified (`ls /opt/ghidra` lists Ghidra) | `/opt/ghidra` (profile `ghidra_12.1.2_DEV`) |
| Java 21 (OpenJDK) | ✅ | — |
| Maven | ✅ | `/usr/bin/mvn` |
| Wine 11.17 | ✅ verified (`wine --version` → `wine-11.17`) | — |
| radare2 6.2 | ✅ | `/usr/bin/radare2` |
| gdb / lldb | ✅ | — |
| CMake / Clang / GCC | ✅ | — |
| SDL3 3.4.16 | ✅ | — |
| Vulkan (radeon/RADV) | ✅ verified (`vulkaninfo` present, Instance 1.4.357) | — |
| Python + `uv` | ✅ | `uv` at `~/.local/bin/uv` |
| codegraph 1.6.0 | ✅ | npm global; per-repo `.codegraph/` |
| ghidra-mcp 7.0.0 | ✅ | `~/apps/ghidra-mcp` (uv venv); extension in `_DEV` profile |

## 2. Completed objectives (SHAs from `git log --oneline`)
- Phase 0 scaffold (`f6f850d`): opencode.json, .gitignore, README/CONTRIBUTING/LICENSE, AGENTS.md.
- Defensive SDK import (`4927122`, `tools/ghidra/ImportSporeSDK.java`): 1670/1671 fns named, 1895 structs; GOG build uses `SporeGhidra_march2017.xml`. Project `~/ghidra-spore-project/SporeProject` (rebuilt 2026-09-20; broken backup in `/tmp/opencode/ghidra/`).
- RenderWare research (`36e704a`, `docs/RENDERWARE-RESEARCH.md`): RW3 static-linked/D3D9, RW4 spec, gmdl layout, no runtime HLSL.
- Asset tooling (`8a2caf5`, `tools/spore/`): DBPF+QFS / RW4 / GMDL stdlib-only Python oracles.
- Fixtures + tests (`9f073dd`, `tests/`): synthetic fixtures, semantic snapshots, opt-in real-asset differential.
- Vtable pass (`f138be7`, `tools/ghidra/VtableDetect.java`): 3081 candidates, 20 VTAB labels → `docs/analysis/vtables.json`.
- Observatory (`e10ba0c` + Obj 6 `51d24ff` + Obj 6.1 `6a41c66`): ptrace tracer, main_menu RVAs, 1004-event startup trace (see §4).
- Obj 7 renderer (`1a2e9a7`, `src/renderer/`): IRenderer + offscreen Vulkan backend, triangle smoke green.
- Obj 8 asset path (`3a52600`, `src/assets/` + `src/apps/asset_view.cpp`): real gmdl 32v/20tris → 27,685 px (`docs/ASSET-PATH.md`).
- Obj 9 boundaries (`bb2e6fd`): B1 `IResourceProvider` / B2 `IMeshSource` / B3 `IRenderer` seams (`src/compat/`) + `docs/BOUNDARIES.md`, `docs/replacement-status.json`.
- Obj 10 knowledge loop (`f5ae618`): `knowledgegraph/seed_sprint.py` (60 nodes / 68 edges / 7 test rows), `docs/KNOWLEDGE-GRAPH.md`. Superseded by S1: canonical seed `knowledgegraph/seed.py` + `seed-literals.json` (96 / 115 / 14; 18 subsystems) — `seed_sprint.py` is a deprecation shim.
- Obj 13 sanitation (`e0d6230`): verbose-gated maps logging, traces default to `/tmp`, ignore `*.ppm`.
- Obj 15 materials/textures + recon (`855254b`): GMDL refCount-BE fix, raster 32B envelope + DXT5 decode, lit pipeline + Vulkan texture/sampler, `material_smoke`; `docs/CELLSTAGE-RECON.md`, `docs/MATERIALS-DESIGN.md`.
- Obj 16 cell stage scene (`b5e96f0`): `src/apps/cell_stage.cpp` — real gmdl + real DXT5 backdrop, stand-in player cell, food/prey, orbit camera, soup clear (`docs/CELLSTAGE.md`).
- Obj 17a deterministic sim (`cf7147a`): `src/sim/` CellSim (movement, eat/flee, scripted `--input` replay, camera follow) + `cell_stage --input`.
- Obj 17b interactive presentation (`8cedc60`): SDL3 + Vulkan live window (swapchain/vsync), keyboard-driven CellSim, follow camera, driver fallback.
- Obj 18 validation + boundary review (`b939cb7`): `docs/CELLSTAGE-VALIDATION.md`, BOUNDARIES.md + replacement-status updates (no seam changes needed).
- Obj 30 baseline (`—`): tree clean, 8/8 CTest, hygiene audit (git-ignored `SPORE/`/`*.ppm`/`build/`).
- Obj 31 RE-Intelligence MVP (`d43e324`): `tools/re/dossier.py` + `docs/RE-DOSSIER-SCHEMA.md` (7-level evidence vocab) + first `cell-movement` dossier (ray-plane headline); 7 new Python tests.
- Obj 32 runtime observation + address fix (`1c3035b`): 12 byte-verified cell probes; 9 bounded Wine runs → cell unreachable headless; `docs/analysis/CELL-RUNTIME-OBSERVATION.md`; corrected probe `rva`=linked-VA / `image_base 0x400000` convention.
- Obj 33 evidence-backed steering (`1a3dd2c`): CellSim now camera-ray ∩ movement-plane, keyboard secondary; plane params labeled APPROXIMATION; +`testRayPlaneHit`, `testMouseSteer`.
- Obj 34 sporemol resolver (`a4b5ac5`): `tools/spore/asset_resolver.py` + `groupnames.json` + extended `typenames.json` (31→40); **player-cell stand-in REJECTED** (it's a building); real cell GMDLs at groups 0x40616201/02; 19 tests.
- Obj 35 canonical contract + fixtures (`6470cca`): `docs/CELL-CONTRACT.md` (`cell-sim-contract/1`) + `contract_scenarios.hpp` + `sim_contract_test` (bit-exact replay, double-run determinism, frame-count guard) + `tools/gen_cell_fixtures.py`.
- Obj 36A/B synthetic hook + ABI (`9734cc3`): `tools/replace/synthetic/` proves 0xE9 rel32 + RWX mprotect patch (BEFORE 40× / AFTER `replacement_ran=1`); `docs/REPLACEMENT-ABI.md` for `Simulator::Cell::MovePlayerToMousePosition` (VA 0x00e5b790, `void(float)` cdecl, sCellGame@0x16b3c04).
- Obj 36C/D replacement + differential (`b44e683`): `src/replace/` (SCellGameView + replacement impl) + `Reference.cpp` (decomp transcription) + `diff_test` → **64/64 MATCH** vs the decompilation reference; `docs/REPLACEMENT-DIFF.md`; status `replaced-approx` (NOT a live-runtime verification).
- Obj 37/38 boundary + workflow docs (`cfd0da6`): `docs/replacement-boundaries.md` (18-subsystem status table + gates) + `docs/RE-WORKFLOW.md` (7-stage pipeline + evidence decision table + known limitations).
- Obj 39/41/42 KG + devlog + roadmap (`ace8e1d`): KG 88→96 nodes / 102→115 edges / +3 test records; `docs/devlog/014-re-intelligence-and-first-replacement.md`; `docs/ASSET-IMPORT-ROADMAP.md`.
- Reconstruction Readiness Audit (triage-v6 baseline): 368-function queue → 6 READY / 29 READY_WITH_LOCAL_CONTEXT / 24 DEPENDENCY_FIRST / 23 ENGINE_BOUNDARY / 101 NEEDS_RE / 185 LIKELY_INFRASTRUCTURE; 172/2149 decomp; strategy D (hybrid); `knowledgegraph/triage/reconstruction-readiness-f0e310e0.json` + `docs/analysis/reconstruction-readiness.md` (see §15).

## 3. Architecture (current tree)
```
src/apps/ (triangle, asset_view, material_smoke, cell_stage)  renderer/ (Renderer.hpp, VulkanRenderer + present mode, lit pipeline)
assets/ (Dbpf, Gmdl, Mesh, Dxt5, Texture, Stream)  sim/ (Sim: CellSim, MovementPlane, ray→plane steer, scripted input)  compat/ (B1–B3 seams)
replace/ (SCellGameView, replacement impl, decompilation reference, diff_test)   [Obj36]
tools/spore/ (dbpf, rw4, gmdl, raster, dxt5, typescan oracles, asset_resolver + types/{typenames,groupnames})   [Obj34]
tools/re/ (dossier.py + data/{ghidra_snapshot, decompiled/})   [Obj31/32]
observatory/ (probe_tracer, observe.py, probes/)  ghidra/ (ImportSporeSDK, VtableDetect)
tools/replace/synthetic/ (native 32-bit hook proof)   [Obj36A]  tools/gen_cell_fixtures.py   [Obj35]
tests/ (fixtures/cell/, test_formats, test_textures, test_sim, test_cellstage, test_dossier, test_asset_resolver, test_kg_{schema,scale,seed}, diff_real.py opt-in)  knowledgegraph/ (kg.py, scale.py, seed.py, seed-literals.json; seed_sprint.py deprecation shim; spore.db git-ignored)
docs/ (RECON-3.1.0.22, RENDERWARE-RESEARCH, RENDERER-DESIGN, ASSET-PATH, BOUNDARIES, KNOWLEDGE-GRAPH, MATERIALS-DESIGN, CELLSTAGE{,-RECON,-VALIDATION}, RE-DOSSIER-SCHEMA, CELL-CONTRACT, REPLACEMENT-ABI, REPLACEMENT-DIFF, replacement-boundaries, RE-WORKFLOW, ASSET-IMPORT-ROADMAP, devlog/, replacement-status.json, analysis/{vtables,dossiers/})
```

## 4. Validated capabilities (exact commands, repo root unless noted)
- C++ build + tests: `cmake -S . -B build && cmake --build build -j && ctest --test-dir build -V` (`triangle_smoke`; `asset_render` needs `SPORE/`, else skips).
- Python format tests: `python3 -m unittest discover -s tests -t . -v` (synthetic, CI-safe).
- Real-asset differential (opt-in): `python3 tests/diff_real.py` (exit 0 with message when `SPORE/` absent).
- Tracer self-test (no Wine): `cd tools/observatory && ./probe_tracer --launch ./test/m32target --launch-arg 400 test/probes_m32.json /tmp/obs_m32.jsonl --duration 3 --module m32target` (exit 0, ~1801 events) + `python3 analyze.py /tmp/obs_m32.jsonl`.
- Game startup trace — **`wineserver -k` FIRST (mandatory: later boots on one wineserver generation stall in `ntsync_schedule` or exit silently)**, then: `timeout -s KILL 120 python3 tools/observatory/observe.py main_menu --duration 30` (1004 events: entry→InitPlugins/Init/Startup→`IAppSystem::Get`×1000 capped; Obj18 retrace completed cleanly but recorded 0 events — see §5).
- Cell stage, fixed frame: `build/src/cell_stage SPORE/Data/Spore_Content.package` → 512×512 `cell_stage.ppm` + `CELLSTAGE-MANIFEST v1` on stdout; two runs print byte-identical manifests. Sim replay: `--input script.jsonl` (JSON-lines frames; `CELLSTAGE-SIMMANIFEST v1`, deterministic). Interactive: `--interactive [--frames N]` — live SDL3+Vulkan window at 60 fps on `:0` XWayland, keyboard-driven CellSim, follow camera; 0 KHRONOS validation-layer errors over 120 frames (SDL3 driver quirk → `default→wayland→x11` fallback, §5).
- `material_smoke` (ctest): real mesh + real DXT5 raster through the lit pipeline → non-uniform colored pixels, frame-to-frame light change, checksum differs from the flat `asset_render` baseline.
- `sim_test` (ctest, pure C++ — no GPU/package): movement, eat/flee rules, scripted input replay, determinism; `tests/test_sim.py` + `tests/test_cellstage.py` + `tests/test_textures.py` (DXT5/refCount-BE/raster oracles) run the binaries and skip without `SPORE/`.
- `sim_contract_test` (Obj35): bit-exact replay of the frozen `tests/fixtures/cell/fixtures.json` (5 scenarios) + double-run determinism + frame-count guard — catches silent sim regressions.
- `replace_diff_test` (Obj36D): 8 input cases × 8 output fields = **64/64 MATCH** between the decompilation-derived reference and the replacement (`docs/REPLACEMENT-DIFF.md`; NOT a live-runtime oracle).
- Asset resolver (Obj34): `python3 -m tools.spore.asset_resolver` resolves a DBPF record → type/group/instance → sporemol name; `tests/test_asset_resolver.py` (19 tests) lock the type/group tables.
- RE dossier (Obj31): `python3 tools/re/dossier.py cell-movement` regenerates `docs/analysis/dossiers/cell-movement.{md,json}` from the committed Ghidra snapshot + decompilation captures (idempotent; `tests/test_dossier.py`).
- Synthetic hook proof (Obj36A): `cd tools/replace/synthetic && make && python3 test_hook.py` — BEFORE the original probe fires 40×; AFTER the patch the replacement runs and the probe is gone (0xE9 rel32 + RWX mprotect on native 32-bit).

## 5. Known limitations (evidence → impact)
- No MSVC RTTI in SporeApp.exe; vtable pass labeled only 20 VTABs from 3081 candidates → class hierarchy stays partial; `this`-typing/hierarchy claims capped at INFERRED.
- Materials are a fixed-function approximation: lit-pipeline light values (dir/ambient) are APPROXIMATION, not game data; no full Spore material system, no runtime HLSL.
- PNG32 records (DBPF type `0x2f4e681b`, 1131 in Spore_Content) are **RW4 containers, not raw PNG** (60/60 sampled) → no PNG decoder / ZLIB dependency exists; decoding them needs the RW4 reader first.
- GMDL walker accepts v8 + BE refCount, static, single-stream, trilist only; 32-bit indices and v9 are hard errors by design — **0 such records observed** across the 4209-record content population (1510 walk-fails = BE refCount + v9); v9 layout itself not decoded.
- Raster envelope: 2 header fields semantically unresolved (0x10 = 8, 0x18 = 0x00040000, constant in every sample); decoder derives layer count from record size and never trusts them.
- Player-cell asset identity **REJECTED as previously assumed**: the roundish stand-in `0x40637E02/0x067A0801` was resolved to a **building-category** GMDL, not a cell asset (Obj34). Real cell-stage GMDLs sit at groups `0x40616201`/`0x40616202`. No name↔instance map exists in the assets, so the exact player-cell record is still unidentified — see `docs/ASSET-IMPORT-ROADMAP.md` for the proposed manifest-driven path.
- Scene placement is hard-coded: 1022 world-object records (`0x0f43029a`) confirmed to exist but undecoded; no scene/level files found.
- Tracing needs a real X display (`DISPLAY=:0`); Xvfb/xdotool absent → no synthetic input, no menu-transition trace; `menu_transition.json` probes defined but never run. Obj18 retrace of `main_menu` attached cleanly (33.7 s) but recorded **0 events** (game never reached the menu in the window) — cell-mode traces never run (headless menu navigation impossible), so all camera/movement/interaction semantics stay INFERRED/APPROXIMATION.
- SDL3 video-driver auto-probe fails with an empty error in some sessions even when a backend works → interactive path falls back `default→wayland→x11` and reports the driver that succeeded; no display → exit 0 with a notice (never crashes).
- Headless GhidraMCP cannot open programs (needs GUI mode) → RVA cross-checks done via `objdump`/byte inspection instead.

## 6. Immediate next milestone
The cell-stage campaign (`docs/analysis/campaigns/cell-stage-campaign.md`, 32 targets / 5 waves) is **COMPLETE** (2026-09-23): 31 targets DONE, CS-32 PARTIAL (trace-gated verification sub-part only). What `cell_stage` now does end-to-end on real GOG assets: real cell GMDL decode (88 records) + backgroundMap 12-stop ramp → clear (0,90,152); 4096-cell sim pool + advect + damage/scale/attack; `cCellGFX` 8-world table + record-key preload; declarative `scene.json` placement (6 entities, per-value provenance — original placement is *procedural*: populate records carry zOffset/distribution, no stored x/y table); mode-strategy lifecycle mapped 1:1 to the original `cCellModeStrategy` vtable slots; table-driven input; `cCellUI` health HUD; deterministic raster output (`content=94211`, `distinct=10860`); ctest 36/36.
Gates remaining, in priority order:
1. **Wine boot-stability diagnostic (read-only).** S5 ran 2026-09-22 (devlog 018, human-watched, 3 runs) and recorded NEGATIVE: run #1 booted to the menu then the whole process tree self-exited clean (~12.7 s); run #2 never booted. The exact exit trigger is unknown — establishing it is the only thing blocking the cell-mode trace (→ `replaced-verified` promotion + sCellGame field pinning).
2. **Player-cell identity** was resolved in CS-13 (manifest-driven; the Obj34 building stand-in rejection at §5 line "Player-cell asset identity" is superseded — see campaign doc for the mapping + caveats).
Lower-risk parallel: **creature-creator block assembly** (sporemol XML → block gmdl groups already decode). Widen B1 to multi-package fetch only if the chosen slice needs it.

## 7. Repo hygiene (enforced by `.gitignore`)
- NEVER commit: `SPORE/` game assets (`SPORE/`, `*.package`), generated binaries (`build/`, `probe_tracer`, `test/m32target`), traces/logs (`*.log`, `out/`), `*.db` (`spore.db`); test PPMs land in build dir only.
- GPL reference stays out: ModAPI/SporeModder-FX are semantics-only (see §8); no `/tmp` oracle or third-party code copied in.
- Working tree only — no commits unless asked. Devlog (`docs/devlog/`) is user-maintained, EXCEPT new chapters may be added per the sprint protocol — the index in `docs/devlog/README.md` governs (read the index, take the next free chapter number, never modify existing chapters).

## 8. Clean-room boundary
All code is independent from-scratch authorship; no EA binaries, assets, or decompiled source in git. Ghidra/ModAPI give addresses + semantics only (ModAPI + SporeModder-FX are GPL → reference-only, never copied); `librw` (MIT) is the only usable external renderer reference — see `docs/RENDERWARE-RESEARCH.md` licenses.

## 9. Replacement strategy (observe → bound → implement → compare → replace)
Trace the original under Wine (observatory) to pin behavior; draw a minimal seam in `src/compat/`;
implement clean-room C++ behind it; differentially compare (bytes/pixels/event order) vs the original as oracle;
mark `replaced-stub`/`replaced-verified` in `docs/replacement-status.json` (seams + gates: `docs/BOUNDARIES.md`).
Live injection into SporeApp.exe is NOT the day-to-day mechanism (static EXE, no engine DLLs) — substitution happens at link time in-tree. The in-process inline-hook path *is* proven on a native 32-bit target (Obj36A: 5-byte `0xE9 rel32` + RWX `mprotect`; per-target contract in `docs/REPLACEMENT-ABI.md`), so patching the real EXE is a viable future step once a cell-mode runtime trace gates the semantics.

## 10. RE automation platform (6 analyses → one build plan, 2026-09-22)
Six sub-agent analyses landed in `docs/analysis/{SCALABILITY,MCP-DESIGN,ORCHESTRATOR,SCHEMA-DELTA,VIEWER,GUI-BOUNDARY}.md`; their synthesis is `docs/RE-AUTOMATION-ARCHITECTURE.md` (16 sections: 24-tool stdlib MCP surface, KG schema delta with `field`/`trace_run`/`investigations` + canonical 7-level evidence scale, orchestrator lifecycle with no-self-verification invariant, read-only :8787 viewer, single-script GUI boundary with 7 safety boundaries, NOW/LATER/EXPERIMENTAL/MANUAL/AUTONOMOUS classification, S0–S6 sprint plan with verification gates). **S1 (KG spine) is implemented and verified** — see below; **S2 (MCP surface) is implemented and verified** — see below; **S2.1 (MCP hardening) is implemented and verified** — see below; **S3 (GUI automation shell) is implemented and verified** — see below; **S4 is complete with fallback and primary inconclusive** — see below; **S5 was run 2026-09-22 and recorded NEGATIVE** (devlog 018: 3 human-watched runs; SporeApp.exe self-exits under Wine before Cell Stage); S6 is not started. The sprint's goal remains the separately gated cell-stage trace → adjudication → `replaced-verified` promotion of `cell-movement-mouse-steering`.

### S1 — KG spine (done 2026-09-22; commits `9e72a57`, `d304c70`)
- **Schema** (`knowledgegraph/schema.sql` + `kg.py:_migrate`): `node` + `evidence_level` (7-level CHECK) / `updated_at` / `binary_sha256`; new tables `field`, `trace_run`, `investigations` (+ `UNIQUE(kind,va,binary_sha256)`); 6 new indexes. Additive-only, idempotent migration (copy-then-rename node rebuild; `user_version` 0→1 once).
- **Canonical scale** (`knowledgegraph/scale.py`): 7 levels `UNKNOWN 0.0 < APPROXIMATION 0.3 < INFERRED 0.5 < SUPPORTED 0.75 < OBSERVED 0.85 < CONFIRMED 0.9 < VERIFIED 1.0`; 9-status `STATUS2EV`; 5-level legacy map is read-only compat. Sole code definition (dossier vocab derives from it); stale 7-key `STATUS2EV` KeyError fixed + regression test.
- **Canonical seed** (`knowledgegraph/seed.py` + `seed-literals.json`, verbatim 96/115/14): deterministic, idempotent, bare-clone-safe; optional machine inputs (SDK XML) via flags, gracefully skipped; `seed_sprint.py` is a deprecation shim (no data). Rebuild: `python3 knowledgegraph/kg.py init && python3 knowledgegraph/seed.py [--binary-sha256 <sha> | --build-agnostic]`.
- **Stale-state**: re-seed under a new `binary_sha256` preserves old rows (parked, queryable `!= current`, never dropped).
- **Verified** (independent review from committed tree, fresh worktrees): Python suite 77/77 OK ×3; seed → 96 nodes / 115 edges / 14 test rows, 18 `Subsystem` nodes, 19 investigations (18 sub + 1 done/RECORDED cell), 15 `field` rows; two worktrees seed byte-identical dumps; C++ from scratch with `-Werror` zero warnings, ctest 10/10; clean-room audit of all S1 commits: text-only, no blobs.
- **Tests added**: `tests/test_kg_schema.py` (6), `test_kg_scale.py` (7), `test_kg_seed.py` (12).

- **S4 result:** final run `S4-20260922T171504Z-379947` (`tools/observatory/out/S4-20260922T171504Z-379947/`) used the defined manual feasibility experiment on `:0` under KDE Wayland/XWayland, Wine 11.17, xdotool 4.20260303.1, xwininfo 1.1.7, and maim 5.8.2. Window `44040193` had stable geometry `2304x1296+2561+144`, WM_CLASS `sporeapp.exe`, and executable SHA256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`. The primary `xdotool --window` Return/click path was inconclusive: screenshots stayed on animated/loading/splash progression with no attributable UI response. The one approved fallback (`windowactivate --sync 44040193`, then focused-window Return) visibly changed the registration form from no validation text to `Email is required. Screen Name is required. Password is required.`
- **S4 cleanup and limits:** cleanup passed with no S4 Spore/Wine/overlay processes remaining; a separate post-teardown probe verified `machine_locked=false`. Physical Ctrl+Alt+Backspace was not performed, so `HUMAN_ACTION_REQUIRED` remains unresolved; the synthetic stop event is a substitute only. Independent review classification is **S4 PASS WITH FALLBACK / PRIMARY INCONCLUSIVE**. No S5 walk, Cell trace, Cell reachability claim, status update, or evidence promotion was made.
- **Next action:** **S5 remains gated and next.** Do not start S5 in this task; S5 requires separate approval and a human-watched run and remains not started.

### S2 — MCP stdlib surface (done 2026-09-22; commits `8e09a9c`, `93b3317`, `2bc16c5`)
- **Server** (`tools/mcp/server.py`): stdlib-only newline-delimited JSON-RPC 2.0 over stdio (`initialize`/`tools/list`/`tools/call`/`ping`, `quit`/`shutdown`/`exit`); stdout = protocol only, stderr = diagnostics; no threads, no hidden state. Launch: `python3 tools/mcp/server.py` or `python3 -m tools.mcp.server`. OpenCode entry `openspore` in `opencode.json` (verified: `initialize` → 24 tools, `tools/call pipeline_state {}` → ok, `quit` → exit 0).
- **24 tools exactly** (all real, zero stubs): `pipeline_state`, `target_select`, `function_context`, `frontier_context`, `reconstruction_status`, `kg_query`, `kg_neighbors`, `kg_record`, `dossier_read`, `dossier_regenerate`, `ghidra_decompile`, `ghidra_function`, `ghidra_search`, `ghidra_snapshot_save`, `asset_resolve`, `asset_scan`, `vtable_lookup`, `trace_run`, `trace_analyze`, `trace_status`, `test_run`, `status_update`, `fixture_check`, `queue_op` (`tools/mcp/{registry,config,safety,cache,ghidra_client,kg_tools,reconstruction_tools,ghidra_tools,asset_tools,runtime_tools}.py`). Uniform error shape (`status=error + ok=False + code + message`); successes carry `status=ok`.
- **KG/queue** use the S1 canonical schema + 7-level scale (`scale.py` import); `kg_record` requires `reason`, rejects `status` writes; `queue_op` dedups on `(kind,va,binary_sha256)`, terminal rows never deleted; stale identities remain queryable.
- **Decompile cache** keyed exactly `(binary_sha256, rva, ghidra_version, program)` under git-ignored `tools/mcp/cache/`; same key → hit with stored provenance, any field change → miss, malformed entries fail safe to miss. Offline serves warm cache, else structured `ghidra_offline`.
- **Safety**: `trace_run`/`status_update` always gated, `fixture_check` gated on `rebuild=true` (`approve=true` + `OPENSPORE_MCP_TRUSTED=1`, else `approval_required`); adversarial review confined all path params to repo-root-or-tmp + clamped timeouts to [1,900]; assets metadata-only, `SPORE/` never written; `test_run` lock-aware; out-of-scope `tools/viewer` stray removed uncommitted (S2 forbids the graph viewer).
- **Graceful-blocked** (structured, never crash): `trace_run` needs approval + wine + display + free lock; `status_update` → `replaced-verified` capped without a trace manifest (decomp caps at `replaced-approx`); `fixture_check --rebuild` needs built emitter; `test_run` reports `blocked_no_ctest/build` when toolchain absent. No live GhidraMCP was running; live-bridge paths covered by fakes + offline-cache tests.
- **Verified**: `tests/mcp/` 208 tests OK (core/contract/kg/ghidra/assets_runtime/server incl. real-subprocess stdio suite + fresh-worktree run with no `SPORE/`, no wine/display); full Python suite **285/285 OK**; C++ `cmake --build build -j` clean (all targets); S1 seed invariants intact (tests carry the 96/115/14 + 18/19/15 checks); no proprietary files, no committed DBs/binaries.
- **Tests added**: `tests/mcp/{test_core,test_contract,test_kg,test_ghidra,test_assets_runtime,test_server}.py` (208 total).

### S2.1 — MCP hardening (done 2026-09-22; commits `44eaf13`, `0346b8c`, `b275d52`)
Autonomous-agent usability pass over the 24-tool surface: remove ambiguity and redundant context. No scoring engine, deterministic only (no LLM summarizer), S3/GUI untouched.
- **A — provenance envelope**: every Ghidra result (`ghidra_decompile`/`ghidra_function`/`ghidra_search`/`ghidra_snapshot_save`/`vtable_lookup`/`dossier_read`) now carries a uniform `mode` (`live|cache|snapshot|offline|unavailable`) + `provenance` + `binary_sha256`/`program`/`image_base`. An agent can distinguish "no result" from "source unavailable" on every call.
- **B — shared resolver**: `ghidra_function` and `ghidra_decompile` share `_resolve_with_fallback` — VA/RVA/name/alias all resolve identically; committed-snapshot fallback; a bad name returns `not_found` with candidates, never an empty `ok`.
- **C — search diagnostics**: `ghidra_search` gains `search_status` (`matched|matched_zero|offline_no_index|invalid_query`) + `truncated`; `count:0` is no longer ambiguous.
- **D — target_select**: `select_status` (`selected|not_found|no_target`) + `why_ranked` + `next_action`; slim bounded candidate rows + `status` filter; rank order frozen (active > queued > blocked, `ORDER BY stage,id`).
- **E/F — schema + JSON-RPC**: required/`required_one_of` + declared aliases across all 24 tools; `-32602` reserved for malformed envelopes only — domain validation (incl. missing `field` keys) stays in-band. Bridge `{"error":…}` payloads map to `ghidra_rest_error` (no longer swallowed as `ok`); `search_functions` sends `name_pattern` as a query param.
- **G — context slimming**: `kg_neighbors` brief `{name,label,evidence_level}` default (+`detail`/`limit`); `vtable_lookup` null-stripped `{ptr,func}` slots + `limit`; `dossier_read` `section`/`keys`/`expand` (md opt-in; `expand=true` is byte-identical to the committed raw — zero evidence loss).
- **Measured cell-movement movement** (git stash, same server): `kg_neighbors` depth-2 21,275→8,204 B (−61%); `vtable_lookup` namespace 89,602→6,562 B (−93%); dossier whole 52,093→49,724 B (−5%), `section=functions` 8,067 B (−84%); zero evidence-field loss.
- **Verified**: each commit independently green; `tests/mcp/` **208→283 OK**; full Python suite **373/373 OK**; C++ `cmake --build build -j` 100% clean, zero C++ files in the S2.1 diff; S1 KG invariants + runtime approval gates unchanged; adversarial review (F-1 wire shape, F-2 bridge error swallow, F-3 undeclared alias) found, fixed, re-reviewed READY.
- **Tests added**: `tests/mcp/test_wire_contract.py` (real client over a stub HTTP bridge), `tests/mcp/test_protocol_errors.py` (malformed JSON/method/tool; server stays alive); envelope/search/target/slimming tests across `test_ghidra.py`/`test_kg.py`/`test_contract.py`.

### S3 — GUI automation shell (done 2026-09-22; commits below)
The single committed automation surface: `tools/observatory/menu_walk.sh` + a ~60-LOC `python3-xlib` AGENT DRIVING overlay + global stop key + input log + shot manifest + 3-level no-op ladder + dry-run. Evidence is **BUILD/VERIFY only** — no real game boot, no cell trace (that is S5), no XSendEvent feasibility check (that is S4).

- **Deliverables**: `menu_walk.sh` (approval gate `--approve`+`OPENSPORE_MCP_TRUSTED=1` else exit 3; machine-lock re-exec; `wineserver -k` discipline before every spawn; `xrandr`/`xwininfo` window pin + **per-step geometry-drift → STOP** (reads live `Absolute upper-left X/Y`, not the stale 2796×1290); fixed key allowlist `Return Escape Up Down Left Right` only; 3-level no-op ladder; stop-state poll each step; `maim -i` shot manifest `out/shots/<run_id>/shots.jsonl` w/ sha256 + `delta_vs_prev_sha`; trap cleanup; file surface limited to `out/**` + `/tmp/openspore-walk/**`); `agent_overlay.py` (borderless `override_redirect` always-on-top red-frame "AGENT DRIVING — press Ctrl+Alt+Backspace to stop"; global `XGrabKey` → stop-state file → SIGTERM walker; `--selftest`); `lock.py` + `machine_lock.sh` (`flock /tmp/openspore-machine.lock`, body `{pid,label,ts,task_id}`, `machine_locked` exit 5); `observe.py` lock gate; `src/CMakeLists.txt` wraps the 4 display smoke tests with `machine_lock.sh`.
- **Item 9 (installs)**: `xdotool 4.20260303.1`, `maim 5.8.2`, `xorg-xwininfo 1.1.7` installed via pacman (Arch has no `x11-utils` metapackage; `xwd` deliberately not used — `maim` is the capture path). `python3-xlib 0.33` already present.
- **Bugs found & fixed under adversarial fail-closed testing** (subagent-4, all minimal/in-scope): `--walk` direct-invocation bypass → refused exit 3; INT/TERM traps resumed the walk → now tear down + `exit 130/143`; `--shot-line` accepted non-numeric fields → exit 2; `win_geom` parsed dead xwininfo fields so **position drift was undetectable** → now reads real X/Y; failed boot generation fell through to pin+drive a **foreign "Spore" window** → now stops on non-zero generation; foreground key steps un-interruptible by trapped signals → run via `&`+`wait`; `--selftest` with no display returned 0 "skipped" → now exit 2 "refused".
- **Critical lock fix** (subagent-5, independently re-verified): CPython 3.4+ opens with `O_CLOEXEC` by default, so the flock'd fd was closed at `os.execvpe` and the **command path released the lock at exec time** — `machine_lock.sh <cmd>` / the walk re-exec / the CMake smoke-test wiring did NOT serialize. Fixed by clearing close-on-exec (`fcntl(fd, F_SETFD, 0)`) so the child inherits the flock; the kernel now holds it for the whole command. Regression test `test_command_path_holds_lock_during_execution` (probe during a running child → `machine_locked` exit 5).
- **Fail-closed matrix** (13 modes, all CLOSED): no-display / no-wine / missing-exe / missing-tool / window-gone / geometry-drift / lock-contention / hung-step / process-exit / file-surface / stale-foreign-identity / missing-approval / malformed-manifest.
- **Verified** (fresh independent review, no implementer claims trusted): dry-run lists all 9 steps and issues nothing (PATH-shimmed tools → empty marker, no file-surface change; deterministic ×2); overlay selftest maps a real `override_redirect=1` viewable window on `:0` and tears it down cleanly; stop chain writes `stop-state` + destroys overlay + SIGTERMs walker (fired via `xdotool key ctrl+alt+BackSpace`, a functional substitute for the one-time hand press); lock acquire/deny/release serializes live. **Full Python suite 392/392 OK** (373 S2.1 baseline + 19 new S3); C++ `cmake --build build -j` clean under `-Wall -Wextra -Werror`, **ctest 10/10**; S1 KG invariants + S2 MCP (24 tools, `ALWAYS_GATED = trace_run/status_update` + `fixture_check(rebuild)` intact) + read-only viewer all unchanged; this change is limited to MCP/Python/docs and does not add C++ or S4/S5/S6 behavior.
- **Tests added**: `tests/test_lock.py` (6), `tests/test_menu_walk.py` (7), `tests/test_observe_lock.py` (2), `tests/test_agent_overlay.py` (3) — 18 new.
- **Recorded UNVERIFIED / out-of-scope gaps (do NOT promote S3 evidence on these)**: no per-step hard `timeout` (SIGTERM covers hangs); no binary/wine identity in the shot manifest; no explicit `wine`/exe precheck (missing-exe and boot-stall are log-indistinguishable — real wine exits 0 silently); no OS sandbox (confinement is convention + `xdotool search --name Spore` trust — any window named "Spore" matches until a strict WM_CLASS/geometry/age check is added). The **S5** unattended walk ×3 + `cell_movement.json` cell trace was NOT performed. **What S3 proved:** the shell plumbing is built, diff-reviewable, and fail-closed on every tested mode; it proved **nothing** about live runtime behavior, cell-stage reachability, or synthetic-input acceptance.

### S4 — X11 input feasibility (complete; fallback pass, primary inconclusive)
The final manual feasibility run was `S4-20260922T171504Z-379947`, at
`tools/observatory/out/S4-20260922T171504Z-379947/`. Its definition was to test
attributable visible response to `xdotool --window` XSendEvent input under KDE
Wayland/XWayland on `:0`, with one approved focused-window fallback. Environment and
provenance were Wine 11.17, xdotool 4.20260303.1, xwininfo 1.1.7, maim 5.8.2, window
`44040193`, WM_CLASS `sporeapp.exe`, stable `2304x1296+2561+144`, fresh renderer marker,
and executable SHA256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`.

The primary Return/click screenshots remained on animated/loading/splash progression,
so the primary path is **INCONCLUSIVE**. The approved fallback ran exactly once:
`xdotool windowactivate --sync 44040193`, then focused-window Return. The registration
form visibly changed to `Email is required. Screen Name is required. Password is
required.` This is an attributable visual-response pass, not an exit-code or focus
inference. Independent review classification: **S4 PASS WITH FALLBACK / PRIMARY
INCONCLUSIVE**.

Cleanup passed with no S4 Spore/Wine/overlay processes; a separate post-teardown probe
verified `machine_locked=false`. Physical Ctrl+Alt+Backspace was not performed, so
`HUMAN_ACTION_REQUIRED` remains unresolved; the synthetic stop event is a substitute
only. No S5 walk, Cell trace, Cell reachability claim, status update, or evidence
promotion was made. S5 remains not started and requires separate approval and a
human-watched run.

## 11. Full-function triage v4 (done 2026-09-23; superseded by §12 v5, same snapshot 2540f2ca)

Deterministic classification of **all 58,757 functions** (`tools/triage/classify.py`
stdlib-only + `tools/triage/rules-v4.json`; two `--dry-run`s byte-identical,
sha256 `4cd8b052…85423`). Live-DB counts: GAMEPLAY_LOGIC 117 /
GAMEPLAY_SUPPORT 75 / ENGINE_INTERFACE 302 / ENGINE_IMPLEMENTATION 5759 /
THIRD_PARTY_OR_RUNTIME 3564 / UNKNOWN 48940; P0 159 (= recon candidates, all
with decomp) / P1 5759 / P2 19 / P3 52642 / IGNORE 178; CONFIRMED 474
(SDK-name provenance only — name-level, not EA source) / SUPPORTED 3440 /
INFERRED 5755 / UNKNOWN 49088. SDK rows 477, all with decomp; caller/callee
NULL everywhere (no xref export); 1186 SDK VAs have no function entry.
Queue `knowledgegraph/triage/queue-2540f2ca.json` (207 rows: queued 153 /
candidate 19 / implemented 35 Cell reference; 7-state lifecycle with DB
mapping; `replacement-tested`/`runtime-validated` never assigned — S5
NEGATIVE). Note: live-DB `investigations` shows queued 1665 — that is the full
investigation ledger, not the reconstruction projection (207). Clusters
`clusters-2540f2ca.json` (20, sum 58757 ✓). Tests: 408/408 unittest OK +
ctest 36/36. Full report: `docs/analysis/function-triage.md`.
**Next step: mass semantic reconstruction of the selected gameplay surface, no
re-inventory** — entry point is queue rank 1 (`005737d0
Editors::cEditor::OnMouseMove`); wave order utfwin-framework → app-lifecycle →
resource-io → sim-core → editor/sporepedia, then carve `unknown-vtable-impl`
via pair-clusters; `unknown-fun-mass` needs the xref export first.

## 12. Full-function triage v5 (done 2026-09-23; classifier triage-v5, snapshot f0e310e0 over 2540f2ca)

`triage-v5` re-runs the v4 rule chain over the same frozen 58,757-function
snapshot with three evidence layers (SDK contained-alias policy, vtable-family
attribution, middleware identification) + a priority-quirk fix. Projections only
(no DB writes by default); 3 consecutive runs byte-identical; 408/408 unittest OK;
v4 dry-run regression matches `summary-2540f2ca.json`; 2540f2ca artifacts
unchanged. v5 counts: GAMEPLAY_LOGIC 493 / GAMEPLAY_SUPPORT 85 / ENGINE_INTERFACE
680 / ENGINE_IMPLEMENTATION 5496 / THIRD_PARTY_OR_RUNTIME 3707 / UNKNOWN 48296
(−644 vs v4); CONFIRMED 1168 (694 via alias) / P1 6261 (192 quirk-fixed); 143
CRT-wrapper rows rescued out of UNKNOWN; 71 vtable-family rows flipped to
GAMEPLAY_LOGIC (INFERRED); 81 queue rows promoted (`candidate`, 207 v4 rows
preserved verbatim → 288 total). DirectX + EASTL confirmed ABSENT (GOG build uses
RenderWare). Full handoff: `docs/analysis/function-triage-v5-handoff.md`.
**Next step: ingest v5 into the live DB** (`classify.py --rules rules-v5.json
--db knowledgegraph/spore.db`), then mass reconstruction from queue rank 1; the
4,398 anonymous-family vtable rows are the residual debt (need deeper vtable work,
not more rules).

## 13. Xref resolution + UNKNOWN debt map (done 2026-09-23; read-only, no Ghidra state writes)

Phase closed with the UNKNOWN debt map (`tools/triage/debt_map.py` →
`knowledgegraph/triage/debtmap-f0e310e0.json`, two runs byte-identical,
sha256 `b5b98ede…968fa`): all 48,296 UNKNOWN rows scored with absolute,
documented thresholds — connectivity isolated 8,362 / low 26,450 / high
13,484 (distinct call-type endpoints); ownership gameplay_affinity 2,950 /
engine_runtime 8,789 / third_party_hint 786 / genuinely_unknown 35,771;
tiers **UNKNOWN-HIGH 862** (747 gameplay-affinity; all need a fresh decompile
pass — none have decomp files) / MEDIUM 6,400 / LOW 41,034. Zero UNKNOWN rows
carry a vtable slot (v5 resolved every vtable member); the 4,398-row
anonymous-family pool is tracked separately in `attribution-f0e310e0.json`.
Queue integrity verified: 288 rows = 207 v4 verbatim (zero field diffs; 35
implemented preserved) + 81 family-backed v5 candidates; all 207 v4 rows
match `investigations.triage_status` 1:1; the 81 promoted rows stay
projection-only until the §12 opt-in ingest. Validation: xref re-export from
cached raw MCP TSV byte-identical (223,704 edges / 362 externals / summary);
v5 classifier re-run byte-identical across all 5 projections; v4 dry-run
regression clean; 58,757 unique VAs (no dups); 20 clusters sum to 58,757;
408/408 unittest OK; C++ build + ctest green; tracked files untouched beyond
this §13 append. Full report: `docs/analysis/xref-resolution.md`.
**Next step (unchanged from §12):** opt-in v5 DB ingest, then decompile pass
over the 862 UNKNOWN-HIGH rows (747 gameplay first), then queue-rank-1
reconstruction.

## 14. UNKNOWN-HIGH adjudication (triage-v6, 2026-09-23) — 699/862 resolved
The 862 UNKNOWN-HIGH rows (all high connectivity, none with decomp files) were
adjudicated in three sequential passes over the §13 snapshot (f0e310e0, 58,757
functions; binary `25d42a7a…d914e`):
- SA-2 decompiled 5 hubs + call-graph/vtable expansion → 921 working rows (862 + 59
  adjacent; 44 are Ghidra non-function addresses).
- SA-3 category propagation (single-category caller rule) → 7,955 rows; 87
  blocked-flag rows + 7 misattributed regions excluded.
- SA-4 180-region subsystem map; 7 regions flagged `review` and blocked from propagation.

Result: **699 resolved / 163 parked** (all 163 "insufficient evidence" — clean
justified UNKNOWN, none forced). Resolved by category ENGINE_IMPL 396 /
GAMEPLAY_LOGIC 194 / ENGINE_IF 61 / GAMEPLAY_SUPPORT 45 / THIRD_PARTY 3; evidence
SUPPORTED 414 / INFERRED 285 (0 CONFIRMED — no SDK names; nothing OBSERVED/VERIFIED);
ownership gameplay_affinity 614 / engine_runtime 83 / third_party_hint 2. 15 per-hub
dossiers in `docs/analysis/dossiers/unknown-high/` (cEmpire ID-color, cell-pool
lifecycle, space event records, pdtk text widget, star-system regen + accessor
families). Artifacts: `unknown-high-investigation-f0e310e0.json`,
`summary-f0e310e0.triage-v6.json` (whole binary: ENGINE_IMPL 11,585 / ENGINE_IF 1,227
/ GAMEPLAY_LOGIC 1,656 / GAMEPLAY_SUPPORT 493 / THIRD_PARTY 4,080 / UNKNOWN 39,716),
`clusters-f0e310e0-v6.json` (20 clusters sum 58,757 + 180 regions),
`queue-f0e310e0-v6.json` (368 rows = 207 v4 + 81 v5 + 80 new v6 candidates; 153
queued / 180 candidate / 35 implemented). Full report:
`docs/analysis/unknown-high-resolution.md`.
**Next step (rank 1 of `queue-f0e310e0-v6.json`):** the mass semantic reconstruction
campaign over the 368-row queue (entry `005737d0 Editors::cEditor::OnMouseMove`,
P0/CONFIRMED/`editor-core`); 163 parked + 7 `review` regions remain open. NOT started
now.

## 15. Reconstruction Readiness Audit (triage-v6 baseline, done 2026-09-23)

Read-only structural audit over the 2,149 gameplay functions (ground truth:
`/tmp/opencode/audit/00`–`03` artifacts built from
`triage-f0e310e0.triage-v6.jsonl` + `queue-f0e310e0-v6.json` +
`xrefs-2540f2ca.tsv`; no v1–v6 artifacts modified). Headline numbers:
172/2149 decomp (8.0%); 368 queue → 6 READY / 29 READY_WITH_LOCAL_CONTEXT /
24 DEPENDENCY_FIRST / 23 ENGINE_BOUNDARY / 101 NEEDS_RE / 185 LIKELY_INFRASTRUCTURE;
dependency: ONE 1,761-node core (81.9%, ~1,600 unnamed `FUN_*`) + 21 small (58 nodes)
+ 330 isolated singletons (55 decomp-backed); 12 foundations — 11 shared-state
singleton accessors (top: `00b3d300` gl_fan_in=252 / 1,097 total callers) +
`map_int_whatever_find` (`00e5c780`, the only genuine algorithm). Strategy **D**
(hybrid): Phase-0 interface freeze on the ~11 shared-state roots, then the 35
READY/READY_WITH_LOCAL_CONTEXT fns, then subsystem-first on decomp-covered clusters
(sim-cell / editor-core / sporepedia-online), isolated singletons as parallel units;
185 LIKELY_INFRASTRUCTURE + 23 ENGINE_BOUNDARY excluded (stubs only). Test baseline
python 408/408 + ctest 36/36. Deliverables:
`knowledgegraph/triage/reconstruction-readiness-f0e310e0.json` (deterministic, no
wall-clock fields, sha256 `44e89b29…`) + `docs/analysis/reconstruction-readiness.md`
(9-section report).

## 16. Phase-0 Root Closure — final synthesis (2026-09-24)

Final static synthesis is complete across the six track pairs, cross-root pair, and five follow-up pairs. The closure covers exactly 11 roots on snapshot `f0e310e0` / canonical xrefs `2540f2ca`; no runtime, Wine, trace, differential, OBSERVED, or VERIFIED evidence was used.

- **Root identities:** `00b3d300` is a strong alternate `cGameNounManager*` accessor (`DAT_0167eae0`), not a generic service locator; `00b3d2a0` is an alternate `cStarManager*`-compatible accessor (`DAT_0167eae4`) while canonical SDK getters are `00b3d400/DAT_0167eb60` and `00b3d3a0/DAT_0167eb0c`. Alternate/canonical equality and lifecycle remain unresolved.
- **Closed contracts:** `00b5b800` remains an opaque borrowed `receiver+0x20` forwarding state/handle with `0xffffffff` null semantics; `00b3d350` remains the separate named `cGameInputManager*`; `00b1fdb0` returns a raw borrowed `cCreatureBase/cCreatureAnimal*`, with `00b1fd50` proving AddRef/store/Release at receiver `+0x54`.
- **Noun/identity chain:** `00b21340` is the actual `cGameNounManager::GetData` implementation; SDK `00b212d0` is a split continuation/misclassified xref, not a second implementation. `00b25fb0` has no caller stack fallback: its no-empire path returns saved incoming ECX and plain `ret`; its normal result is `cCivilization`-compatible. `01021300` retains exact cache AddRef/store/Release ordering, while `00ba9370` retains lower-bound/ceiling rather than exact-find semantics.
- **Space lifecycle:** `01021260` and `01021080` remain read views. `01021d40` allocation/publication, `01021960` conditional context writing, `01022580` independent context normalization, `010219b0`/`010221f0` active planet/star replacement, and `01022460` field teardown are now characterized. Whole-object teardown and the unowned `01022572` write remain open; SpaceContext, scenario mode, and input/game mode remain separate axes.
- **Cross-root model:** the roots are a shared Simulator state substrate with independent owners/domains. `Simulator::sSpacePlayerData` is the common authoritative container for the three target fields, not a single global singleton. Direct calls, receiver propagation, conditional paths, and transitive dependencies remain explicitly distinct.
- **Downstream metrics:** 11 roots; 2,303 distinct direct callers; 6,077 direct-call edges; 516 gameplay-caller union; 948 multi-root callers; 390 callers reaching at least 3 roots; 7 curated high-information callers; 3,896 per-root memberships. The 2,303 population is mechanically constrained, not fully semantically understood; only the evidence-selected 40 callers (33 gameplay) are semantically adjudicated.
- **Highest-impact remainder:** `00b3d300` alternate noun-manager publication/alias/lifecycle. The smallest next experiment is a read-only trace of computed/indirect publishers and teardown for `DAT_0167eae0` versus `DAT_0167eb60`, checked through `00b3d400` and one `00bff2d0` receiver window.
- **Phase-1 boundary:** seven proposed packages are characterization-only (manager slots, noun materialization, empire/civilization chain, SpacePlayerData lifecycle, avatar lifetime, opaque forwarded state, and bounded semantic callers). No replacement is implemented and Phase 1 is not started.

Final outputs: `knowledgegraph/research/root-closure-f0e310e0.json` and `docs/analysis/simulator-root-closure.md`. No `SPORE/`, OpenSpore source, historical v1-v6 artifact, or Phase-0 interface artifact was modified.
