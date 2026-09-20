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
  The MCP server runs **headless** (no GUI):
  `GHIDRA_MCP_ALLOW_SCRIPTS=1 java -Xmx8g -Dghidra.home=/opt/ghidra \
     -classpath ~/.config/ghidra/ghidra_12.1.2_DEV/Extensions/GhidraMCP/lib/GhidraMCP-7.0.0.jar:$(find /opt/ghidra/Ghidra -name '*.jar' | tr '\n' ':') \
     com.xebyte.headless.GhidraMCPHeadlessServer --port 8089 --bind 127.0.0.1 --project /home/juanr/ghidra-spore-project`
  then verify with `curl 127.0.0.1:8089/check_connection`.
- Spore-ModAPI SDK at `~/apps/Spore-ModAPI`. GOG/digital build →
  `SDKtoGhidra/SporeGhidra_march2017.xml` (+ `GhidraScript/ImportSporeSDK.java`).
- Game (GOG, no DRM) at `./SPORE/`; main exe `SPORE/SporeBin/SporeApp.exe` (+ `SporebinEP1/`).
- codegraph installed via npm (global). `uv` at `~/.local/bin/uv`, `mvn` present.
- Ghidra headless project: `~/ghidra-spore-project/SporeProject` (imported SporeApp.exe).
  Rebuilt 2026-09-20 (original was corrupt; backup in `/tmp/opencode/ghidra/SporeProject.broken-backup/`).
  Full binary map: `docs/RECON-3.1.0.22.md`.

## Working with the game / analysis
- Headless import (defensive — use the committed script, NOT the upstream one):
  `/opt/ghidra/support/analyzeHeadless ~/ghidra-spore-project SporeProject \
     -import SPORE/SporeBin/SporeApp.exe \
     -scriptPath tools/ghidra \
     -postScript ImportSporeSDK.java ~/apps/Spore-ModAPI/SDKtoGhidra/SporeGhidra_march2017.xml`
  `tools/ghidra/ImportSporeSDK.java` is the defensive fork (try/catch per address; the
  upstream `~/apps/Spore-ModAPI` one aborts the symbol pass on the first non-function
  address). Result on 3.1.0.22: 1670/1671 functions named, 1895 structures.
- x86:LE:32 cspec is `windows` (Ghidra 12 has no `msvc:LE:32:msvc`).
- **SporeApp.exe has no MSVC RTTI** — class hierarchy only via vtable data + SDK
  structures. Vtable detection never ran headless (0 vtable labels); run a vtable
  pass before relying on class structure.
- `run_script_inline` compiles Java against the Ghidra 12 OSGi classpath — API renames
  that break common assumptions: `Symbol.getName()`/`getAddress()` (no
  `getPrimaryName`/`getPrimaryAddress`); `getSymbols(String)` returns `SymbolIterator`
  (no `SymbolType` overload); no for-each on `Function` (use
  `program.getInstructionIterator(setView)`); `AddressSetView.getMaxAddress()` (no
  `getEnd()`); no `AddressSpace.translateFromInteger`. Failed scripts accumulate as
  `McpInline_*.java` in `~/ghidra_scripts/` — delete them to stop build warnings.
- Query sidecar: `python3 knowledgegraph/kg.py <init|add-node|add-edge|query|neighbors|record-test|dump>`.

## Build / test (once `src/` exists)
- CMake + Clang/GCC. `mkdir -p build && cd build && cmake .. && make -j`.
- C++17, `clang-format` (modified Google), `fmt` for formatting.
- Differential tests run the original under Wine (11) as an oracle.

## Current status
See `docs/STATE.md` for Phase 0 completion and the next step (Phase 1).
