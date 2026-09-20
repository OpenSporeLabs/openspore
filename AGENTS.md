# AGENTS.md — OpenSpore

Rules and durable context for any agent (opencode) working in this repo.

## What this is
Clean-room, from-scratch C++ (C++17) reimplementation of *Spore* + expansions,
driven by a fully AI pipeline. **Never** commit proprietary EA code or assets.

## Hard rules (legal / ethics)
- No *Spore* assets, decompiled EA source, models, textures, sounds, scripts.
- Reimplement by analysis only (clean room). No DRM circumvention (use GOG).
- No trade secrets / leaked code. `SPORE/` is git-ignored — keep it that way.

## Knowledge-graph architecture (do NOT reinvent)
- **Analysis graph** = **Ghidra** (via `ghidra` MCP). Source of truth for
  functions/classes/structures/xrefs/decompilation. Spore-ModAPI SDK symbols live here.
- **Source graph** = **codegraph** (MCP). Indexes this C++ repo for navigation.
- **Shared memory** = **SQLite** at `knowledgegraph/spore.db` (see `kg.py`).
  Cross-tool results only: test outcomes, decisions, asset-format mappings.
- No Neo4j / no general graph DB.

## Environment (CachyOS / Arch — use `pacman`, NOT `apt`)
- Ghidra 12.1.2 at `/opt/ghidra`. **User profile is `ghidra_12.1.2_DEV`**
  (not `_PUBLIC`). GhidraMCP extension already deployed there.
- ghidra-mcp cloned at `~/apps/ghidra-mcp` (uv venv synced). Bridge → `127.0.0.1:8089`.
  Start server via Ghidra GUI: Tools > GhidraMCP > Start MCP Server.
- Spore-ModAPI SDK at `~/apps/Spore-ModAPI`. GOG/digital build →
  `SDKtoGhidra/SporeGhidra_march2017.xml` (+ `GhidraScript/ImportSporeSDK.java`).
- Game (GOG, no DRM) at `./SPORE/`; main exe `SPORE/SporeBin/SporeApp.exe` (+ `SporebinEP1/`).
- codegraph installed via npm (global). `uv` at `~/.local/bin/uv`, `mvn` present.
- Ghidra headless project: `~/ghidra-spore-project/SporeProject` (imported SporeApp.exe).

## Working with the game / analysis
- Headless import:
  `/opt/ghidra/support/analyzeHeadless ~/ghidra-spore-project SporeProject \
     -import SPORE/SporeBin/SporeApp.exe \
     -scriptPath ~/apps/Spore-ModAPI/SDKtoGhidra/GhidraScript \
     -postScript ImportSporeSDK.java ~/apps/Spore-ModAPI/SDKtoGhidra/SporeGhidra_march2017.xml`
- Known issue: `ImportSporeSDK.java` aborts at the first non-function address
  (non-fatal to import, but stops the symbol pass early). Prefer a defensive import.
- Query sidecar: `python3 knowledgegraph/kg.py <init|add-node|add-edge|query|neighbors|record-test|dump>`.

## Build / test (once `src/` exists)
- CMake + Clang/GCC. `mkdir -p build && cd build && cmake .. && make -j`.
- C++17, `clang-format` (modified Google), `fmt` for formatting.
- Differential tests run the original under Wine (11) as an oracle.

## Current status
See `docs/STATE.md` for Phase 0 completion and the next step (Phase 1).
