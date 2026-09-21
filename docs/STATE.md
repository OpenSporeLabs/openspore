# OpenSpore — Project State

Current phase: **Obj 5–10 done — vertical slices through asset→mesh→pixels** (see §2). Next milestone: §6.
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

## 3. Architecture (current tree)
```
src/apps/ (triangle, asset_view)  renderer/ (Renderer.hpp, VulkanRenderer)  assets/ (Dbpf, Gmdl, Mesh)  compat/ (B1–B3 seams)
tools/spore/ (dbpf, rw4, gmdl oracles)  observatory/ (probe_tracer, observe.py, probes/)  ghidra/ (ImportSporeSDK, VtableDetect)
tests/ (fixtures, test_formats.py, diff_real.py opt-in)  knowledgegraph/ (kg.py, seed_sprint.py; spore.db git-ignored)
docs/ (RECON-3.1.0.22, RENDERWARE-RESEARCH, RENDERER-DESIGN, ASSET-PATH, BOUNDARIES, KNOWLEDGE-GRAPH, replacement-status.json, analysis/vtables.json)
```

## 4. Validated capabilities (exact commands, repo root unless noted)
- C++ build + tests: `cmake -S . -B build && cmake --build build -j && ctest --test-dir build -V` (`triangle_smoke`; `asset_render` needs `SPORE/`, else skips).
- Python format tests: `python3 -m unittest discover -s tests -t . -v` (synthetic, CI-safe).
- Real-asset differential (opt-in): `python3 tests/diff_real.py` (exit 0 with message when `SPORE/` absent).
- Tracer self-test (no Wine): `cd tools/observatory && ./probe_tracer --launch ./test/m32target --launch-arg 400 test/probes_m32.json /tmp/obs_m32.jsonl --duration 3 --module m32target` (exit 0, ~1801 events) + `python3 analyze.py /tmp/obs_m32.jsonl`.
- Game startup trace — **`wineserver -k` FIRST (mandatory: later boots on one wineserver generation stall in `ntsync_schedule` or exit silently)**, then: `timeout -s KILL 120 python3 tools/observatory/observe.py main_menu --duration 30` (1004 events: entry→InitPlugins/Init/Startup→`IAppSystem::Get`×1000 capped).

## 5. Known limitations (evidence → impact)
- No MSVC RTTI in SporeApp.exe; vtable pass labeled only 20 VTABs from 3081 candidates → class hierarchy stays partial; `this`-typing/hierarchy claims capped at INFERRED.
- Renderer is offscreen-only: no swapchain/present, materials, lighting, textures (`docs/RENDERER-DESIGN.md` non-goals; status `replaced-stub`) → no visible game window yet.
- GMDL walker accepts v8/static/single-stream/trilist only; RW4 decode, skins, v9, 32-bit indices are hard errors by design → most game models still unloadable.
- Tracing needs a real X display (`DISPLAY=:0`); Xvfb/xdotool absent → no synthetic input, no menu-transition trace; `menu_transition.json` probes defined but never run.
- Headless GhidraMCP cannot open programs (needs GUI mode) → RVA cross-checks done via `objdump`/byte inspection instead.

## 6. Immediate next milestone
Run `menu_transition` under the tracer (needs §5 rows 4–5 resolved or worked around), then widen B1 to multi-package fetch and B2 to a second mesh family (v9 or 32-bit-index) without interface change — gates in `docs/replacement-status.json`.

## 7. Repo hygiene (enforced by `.gitignore`)
- NEVER commit: `SPORE/` game assets (`SPORE/`, `*.package`), generated binaries (`build/`, `probe_tracer`, `test/m32target`), traces/logs (`*.log`, `out/`), `*.db` (`spore.db`); test PPMs land in build dir only.
- GPL reference stays out: ModAPI/SporeModder-FX are semantics-only (see §8); no `/tmp` oracle or third-party code copied in.
- Working tree only — no commits unless asked. Devlog (`docs/devlog/`) is user-maintained: do not edit.

## 8. Clean-room boundary
All code is independent from-scratch authorship; no EA binaries, assets, or decompiled source in git. Ghidra/ModAPI give addresses + semantics only (ModAPI + SporeModder-FX are GPL → reference-only, never copied); `librw` (MIT) is the only usable external renderer reference — see `docs/RENDERWARE-RESEARCH.md` licenses.

## 9. Replacement strategy (observe → bound → implement → compare → replace)
Trace the original under Wine (observatory) to pin behavior; draw a minimal seam in `src/compat/`;
implement clean-room C++ behind it; differentially compare (bytes/pixels/event order) vs the original as oracle;
mark `replaced-stub`/`replaced-verified` in `docs/replacement-status.json` (seams + gates: `docs/BOUNDARIES.md`).
Live injection into SporeApp.exe is NOT the mechanism (static EXE, no engine DLLs) — substitution happens at link time in-tree.
