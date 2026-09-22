# OpenSpore — Project State

Current phase: **Obj 30–42 done — RE-Intelligence workflow + first in-process replacement** (see §2). The Cell Stage slice (Obj13–18) is now backed by an evidence pipeline (dossier → static Ghidra → runtime observatory → asset resolver → contract+fixtures → replace → record) and its movement is `replaced-approx` (differential-verified against a decompilation reference; live-runtime verification still gated on a Wine cell-mode trace). Next milestone: §6.
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
S4 is complete with fallback; S5 is gated and remains the next milestone. Two gates remain, in priority order:
1. **S5 runtime evidence (separately approved and human-watched; not started).** A cell-mode trace is what promotes `cell-movement-mouse-steering` from `replaced-approx` → `replaced-verified` and fills the APPROXIMATION plane constants + movement/interaction semantics. It requires a separate approval and human-watched run on a real X display + `xdotool` (`xdotool`/`maim`/`xorg-xwininfo` now **installed** via S3; Xvfb intentionally absent — it is a trap, GUI-BOUNDARY.md) to navigate main-menu → cell stage, then `tools/observatory/observe.py` under the byte-verified `cell_movement.json` probes. Do not start S5 in this task. Until then the sim stays INFERRED/APPROXIMATION (documented, not fabricated).
2. **Player-cell identity.** Resolve the real player-cell record (groups `0x40616201`/`02`) via the manifest-driven loader in `docs/ASSET-IMPORT-ROADMAP.md`, replacing the building stand-in.
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
Six sub-agent analyses landed in `docs/analysis/{SCALABILITY,MCP-DESIGN,ORCHESTRATOR,SCHEMA-DELTA,VIEWER,GUI-BOUNDARY}.md`; their synthesis is `docs/RE-AUTOMATION-ARCHITECTURE.md` (16 sections: 21-tool stdlib MCP surface, KG schema delta with `field`/`trace_run`/`investigations` + canonical 7-level evidence scale, orchestrator lifecycle with no-self-verification invariant, read-only :8787 viewer, single-script GUI boundary with 7 safety boundaries, NOW/LATER/EXPERIMENTAL/MANUAL/AUTONOMOUS classification, S0–S6 sprint plan with verification gates). **S1 (KG spine) is implemented and verified** — see below; **S2 (MCP surface) is implemented and verified** — see below; **S2.1 (MCP hardening) is implemented and verified** — see below; **S3 (GUI automation shell) is implemented and verified** — see below; **S4 is complete with fallback and primary inconclusive** — see below; S5–S6 are not started. The sprint's goal remains the separately gated cell-stage trace → adjudication → `replaced-verified` promotion of `cell-movement-mouse-steering`.

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
- **Server** (`tools/mcp/server.py`): stdlib-only newline-delimited JSON-RPC 2.0 over stdio (`initialize`/`tools/list`/`tools/call`/`ping`, `quit`/`shutdown`/`exit`); stdout = protocol only, stderr = diagnostics; no threads, no hidden state. Launch: `python3 tools/mcp/server.py` or `python3 -m tools.mcp.server`. OpenCode entry `openspore` in `opencode.json` (verified: `initialize` → 21 tools, `tools/call pipeline_state {}` → ok, `quit` → exit 0).
- **21 tools exactly** (all real, zero stubs): `pipeline_state`, `target_select`, `kg_query`, `kg_neighbors`, `kg_record`, `dossier_read`, `dossier_regenerate`, `ghidra_decompile`, `ghidra_function`, `ghidra_search`, `ghidra_snapshot_save`, `asset_resolve`, `asset_scan`, `vtable_lookup`, `trace_run`, `trace_analyze`, `trace_status`, `test_run`, `status_update`, `fixture_check`, `queue_op` (`tools/mcp/{registry,config,safety,cache,ghidra_client,kg_tools,ghidra_tools,asset_tools,runtime_tools}.py`). Uniform error shape (`status=error + ok=False + code + message`); successes carry `status=ok`.
- **KG/queue** use the S1 canonical schema + 7-level scale (`scale.py` import); `kg_record` requires `reason`, rejects `status` writes; `queue_op` dedups on `(kind,va,binary_sha256)`, terminal rows never deleted; stale identities remain queryable.
- **Decompile cache** keyed exactly `(binary_sha256, rva, ghidra_version, program)` under git-ignored `tools/mcp/cache/`; same key → hit with stored provenance, any field change → miss, malformed entries fail safe to miss. Offline serves warm cache, else structured `ghidra_offline`.
- **Safety**: `trace_run`/`status_update` always gated, `fixture_check` gated on `rebuild=true` (`approve=true` + `OPENSPORE_MCP_TRUSTED=1`, else `approval_required`); adversarial review confined all path params to repo-root-or-tmp + clamped timeouts to [1,900]; assets metadata-only, `SPORE/` never written; `test_run` lock-aware; out-of-scope `tools/viewer` stray removed uncommitted (S2 forbids the graph viewer).
- **Graceful-blocked** (structured, never crash): `trace_run` needs approval + wine + display + free lock; `status_update` → `replaced-verified` capped without a trace manifest (decomp caps at `replaced-approx`); `fixture_check --rebuild` needs built emitter; `test_run` reports `blocked_no_ctest/build` when toolchain absent. No live GhidraMCP was running; live-bridge paths covered by fakes + offline-cache tests.
- **Verified**: `tests/mcp/` 208 tests OK (core/contract/kg/ghidra/assets_runtime/server incl. real-subprocess stdio suite + fresh-worktree run with no `SPORE/`, no wine/display); full Python suite **285/285 OK**; C++ `cmake --build build -j` clean (all targets); S1 seed invariants intact (tests carry the 96/115/14 + 18/19/15 checks); no proprietary files, no committed DBs/binaries.
- **Tests added**: `tests/mcp/{test_core,test_contract,test_kg,test_ghidra,test_assets_runtime,test_server}.py` (208 total).

### S2.1 — MCP hardening (done 2026-09-22; commits `44eaf13`, `0346b8c`, `b275d52`)
Autonomous-agent usability pass over the 21-tool surface: remove ambiguity and redundant context. No new/removed/renamed tools, no scoring engine, deterministic only (no LLM summarizer), S3/GUI untouched.
- **A — provenance envelope**: every Ghidra result (`ghidra_decompile`/`ghidra_function`/`ghidra_search`/`ghidra_snapshot_save`/`vtable_lookup`/`dossier_read`) now carries a uniform `mode` (`live|cache|snapshot|offline|unavailable`) + `provenance` + `binary_sha256`/`program`/`image_base`. An agent can distinguish "no result" from "source unavailable" on every call.
- **B — shared resolver**: `ghidra_function` and `ghidra_decompile` share `_resolve_with_fallback` — VA/RVA/name/alias all resolve identically; committed-snapshot fallback; a bad name returns `not_found` with candidates, never an empty `ok`.
- **C — search diagnostics**: `ghidra_search` gains `search_status` (`matched|matched_zero|offline_no_index|invalid_query`) + `truncated`; `count:0` is no longer ambiguous.
- **D — target_select**: `select_status` (`selected|not_found|no_target`) + `why_ranked` + `next_action`; slim bounded candidate rows + `status` filter; rank order frozen (active > queued > blocked, `ORDER BY stage,id`).
- **E/F — schema + JSON-RPC**: required/`required_one_of` + declared aliases across all 21 tools; `-32602` reserved for malformed envelopes only — domain validation (incl. missing `field` keys) stays in-band. Bridge `{"error":…}` payloads map to `ghidra_rest_error` (no longer swallowed as `ok`); `search_functions` sends `name_pattern` as a query param.
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
- **Verified** (fresh independent review, no implementer claims trusted): dry-run lists all 9 steps and issues nothing (PATH-shimmed tools → empty marker, no file-surface change; deterministic ×2); overlay selftest maps a real `override_redirect=1` viewable window on `:0` and tears it down cleanly; stop chain writes `stop-state` + destroys overlay + SIGTERMs walker (fired via `xdotool key ctrl+alt+BackSpace`, a functional substitute for the one-time hand press); lock acquire/deny/release serializes live. **Full Python suite 392/392 OK** (373 S2.1 baseline + 19 new S3); C++ `cmake --build build -j` clean under `-Wall -Wextra -Werror`, **ctest 10/10**; S1 KG invariants + S2 MCP (21 tools, `ALWAYS_GATED = trace_run/status_update` + `fixture_check(rebuild)` intact) + read-only viewer all unchanged; scope is clean (no `tools/mcp/*` modified, no C++ source changed, no S4/S5/S6 leak).
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
