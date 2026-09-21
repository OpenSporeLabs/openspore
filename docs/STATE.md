# OpenSpore — Project State

Current phase: **Obj 13–18 done — first interactive Cell Stage vertical slice** (see §2). Next milestone: §6.
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
- Obj 10 knowledge loop (`f5ae618`): `knowledgegraph/seed_sprint.py` (60 nodes / 68 edges / 7 test rows), `docs/KNOWLEDGE-GRAPH.md`.
- Obj 13 sanitation (`e0d6230`): verbose-gated maps logging, traces default to `/tmp`, ignore `*.ppm`.
- Obj 15 materials/textures + recon (`855254b`): GMDL refCount-BE fix, raster 32B envelope + DXT5 decode, lit pipeline + Vulkan texture/sampler, `material_smoke`; `docs/CELLSTAGE-RECON.md`, `docs/MATERIALS-DESIGN.md`.
- Obj 16 cell stage scene (`b5e96f0`): `src/apps/cell_stage.cpp` — real gmdl + real DXT5 backdrop, stand-in player cell, food/prey, orbit camera, soup clear (`docs/CELLSTAGE.md`).
- Obj 17a deterministic sim (`cf7147a`): `src/sim/` CellSim (movement, eat/flee, scripted `--input` replay, camera follow) + `cell_stage --input`.
- Obj 17b interactive presentation (`8cedc60`): SDL3 + Vulkan live window (swapchain/vsync), keyboard-driven CellSim, follow camera, driver fallback.
- Obj 18 validation + boundary review (`b939cb7`): `docs/CELLSTAGE-VALIDATION.md`, BOUNDARIES.md + replacement-status updates (no seam changes needed).

## 3. Architecture (current tree)
```
src/apps/ (triangle, asset_view, material_smoke, cell_stage)  renderer/ (Renderer.hpp, VulkanRenderer + present mode, lit pipeline)
assets/ (Dbpf, Gmdl, Mesh, Dxt5, Texture, Stream)  sim/ (Sim: CellSim, MovementParams, scripted input)  compat/ (B1–B3 seams)
tools/spore/ (dbpf, rw4, gmdl, raster, dxt5, typescan oracles)  observatory/ (probe_tracer, observe.py, probes/)  ghidra/ (ImportSporeSDK, VtableDetect)
tests/ (fixtures, test_formats, test_textures, test_sim, test_cellstage, diff_real.py opt-in)  knowledgegraph/ (kg.py, seed_sprint.py; spore.db git-ignored)
docs/ (RECON-3.1.0.22, RENDERWARE-RESEARCH, RENDERER-DESIGN, ASSET-PATH, BOUNDARIES, KNOWLEDGE-GRAPH, MATERIALS-DESIGN, CELLSTAGE{,-RECON,-VALIDATION}, devlog/, replacement-status.json, analysis/vtables.json)
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

## 5. Known limitations (evidence → impact)
- No MSVC RTTI in SporeApp.exe; vtable pass labeled only 20 VTABs from 3081 candidates → class hierarchy stays partial; `this`-typing/hierarchy claims capped at INFERRED.
- Materials are a fixed-function approximation: lit-pipeline light values (dir/ambient) are APPROXIMATION, not game data; no full Spore material system, no runtime HLSL.
- PNG32 records (DBPF type `0x2f4e681b`, 1131 in Spore_Content) are **RW4 containers, not raw PNG** (60/60 sampled) → no PNG decoder / ZLIB dependency exists; decoding them needs the RW4 reader first.
- GMDL walker accepts v8 + BE refCount, static, single-stream, trilist only; 32-bit indices and v9 are hard errors by design — **0 such records observed** across the 4209-record content population (1510 walk-fails = BE refCount + v9); v9 layout itself not decoded.
- Raster envelope: 2 header fields semantically unresolved (0x10 = 8, 0x18 = 0x00040000, constant in every sample); decoder derives layer count from record size and never trusts them.
- Player-cell asset identity **UNRESOLVED** — no name↔group map exists in the assets (creatures are sporemol block assemblies); scene uses a roundish stand-in gmdl `0x40637E02/0x067A0801`.
- Scene placement is hard-coded: 1022 world-object records (`0x0f43029a`) confirmed to exist but undecoded; no scene/level files found.
- Tracing needs a real X display (`DISPLAY=:0`); Xvfb/xdotool absent → no synthetic input, no menu-transition trace; `menu_transition.json` probes defined but never run. Obj18 retrace of `main_menu` attached cleanly (33.7 s) but recorded **0 events** (game never reached the menu in the window) — cell-mode traces never run (headless menu navigation impossible), so all camera/movement/interaction semantics stay INFERRED/APPROXIMATION.
- SDL3 video-driver auto-probe fails with an empty error in some sessions even when a backend works → interactive path falls back `default→wayland→x11` and reports the driver that succeeded; no display → exit 0 with a notice (never crashes).
- Headless GhidraMCP cannot open programs (needs GUI mode) → RVA cross-checks done via `objdump`/byte inspection instead.

## 6. Immediate next milestone
Second vertical slice: **creature-creator block assembly** (sporemol XML → block gmdl placement) **OR a cell-mode runtime trace via Xvfb**; also **resolve player-cell identity** (no name↔group map exists in the assets — the stand-in `0x40637E02/0x067A0801` is a roundish-bbox pick, not a verified model). A trace session is the higher-leverage option: it gates `simulator-gameplay` (replacing all APPROXIMATION/INFERRED rows in `docs/CELLSTAGE-VALIDATION.md`) and can yield the player-cell identity at the same time; block assembly is the lower-risk path (sporemol XML + block gmdl groups already decode). Widen B1 to multi-package fetch only if the chosen slice needs it.

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
Live injection into SporeApp.exe is NOT the mechanism (static EXE, no engine DLLs) — substitution happens at link time in-tree.
