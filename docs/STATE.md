# OpenSpore — Project State

## Phase 0 (environment + tooling): COMPLETE

Machine: **CachyOS / Arch** (use `pacman`, not `apt`).

### Installed / ready
| Item | Status | Location |
|------|--------|----------|
| Ghidra 12.1.2 | ✅ | `/opt/ghidra` (profile `ghidra_12.1.2_DEV`) |
| Java 21 (OpenJDK) | ✅ | — |
| Maven | ✅ | `/usr/bin/mvn` |
| Wine 11.17 | ✅ | — |
| radare2 6.2 | ✅ | `/usr/bin/radare2` |
| gdb / lldb | ✅ | — |
| CMake / Clang / GCC | ✅ | — |
| SDL3 3.4.16 | ✅ | — |
| Vulkan (radeon) | ✅ | — |
| Python + `uv` | ✅ | `uv` at `~/.local/bin/uv` |
| codegraph 1.6.0 | ✅ | npm global; `~/.codegraph` per-repo `.codegraph/` |
| ghidra-mcp 7.0.0 | ✅ | `~/apps/ghidra-mcp` (uv venv); extension in `_DEV` profile |

### Repo scaffolding (committed-ready)
- `opencode.json` — MCP: `codegraph` + `ghidra` (stdio bridge → `127.0.0.1:8089`).
- `.gitignore` (excludes `SPORE/`, assets, `.codegraph/`, `*.db`, logs).
- `README.md`, `CONTRIBUTING.md`, `LICENSE` (MIT), `CODE_OF_CONDUCT.md`,
  `.github/ISSUE_TEMPLATE.md`, `.github/PULL_REQUEST_TEMPLATE.md`, `AGENTS.md`.
- `knowledgegraph/` — `schema.sql` + `kg.py` (tested: nodes/edges/test-results).
- `docs/STATE.md` — this file.

### Verified end-to-end
- codegraph: `codegraph index` → 19 nodes / 39 edges (will grow with C++).
- Ghidra headless: imported `SPORE/SporeBin/SporeApp.exe` + SDK script → named
  real Spore functions (e.g. `Terrain::cTerrainSphereQuad::RenderWater`).
  Project: `~/ghidra-spore-project/SporeProject`.

### Known issues
- `ImportSporeSDK.java` aborts at the first non-function address
  (`XmlAttributeException: Symbol exists but is not a function`). Import succeeds
  and the project saves, but the symbol pass stops early → **not all SDK symbols
  imported**. Fix: wrap `processFunctionAddress` in a try/catch (defensive import)
  so it skips bad addresses instead of aborting.
- GOG = digital build → use `SporeGhidra_march2017.xml` (not `_disk.xml`).

### Runtime note (per session)
Before using the `ghidra` MCP tools, the Ghidra MCP server must be running:
Ghidra GUI → Tools > GhidraMCP > Start MCP Server → `curl 127.0.0.1:8089/check_connection`.

---

## Next step: Phase 1 — Foundation

Build the first C++ engine skeleton + basic structures, compile clean, unit-test.

1. **Build system**: `CMakeLists.txt` (C++17, Clang/GCC, `clang-tidy`, `cppcheck`, `clang-format` modified-Google, `fmt`).
2. **Core structures** (`src/core/`): `Vector3`, `Quaternion`, `Matrix4`, `Stream`
   (binary read/write), `ResourceHandle` / `ResourceManager` stub.
3. **Serialization**: define the Spore data schema for these types; make them
   round-trip through `Stream` (serialize → deserialize → compare).
4. **Tests**: unit tests (serialize/deserialize, math) with a runner wired into CMake.
5. **Re-index** codegraph (`codegraph index`) once `src/` exists so the source graph
   tracks the C++.
6. **Acceptance**: `cmake .. && make -j` builds with zero warnings; unit tests pass;
   `codegraph status` shows the C++ indexed.

Deliverable: a compiling, tested `src/core` with `Vector3` + `Stream` proven by
round-trip tests. Then Phase 2 (basic simulation / cell stage) can start.
