# OpenSpore

An open, from-scratch reimplementation of *Spore* (base game) and its
expansions (e.g. *Galactic Adventures*), built with reverse-engineering tools
and a fully AI-driven analysis pipeline.

> **Warning:** This project is for research purposes only. It does **not**
> contain, build, or distribute any proprietary *Spore* code, assets, models,
> textures, sounds, or data files. You must legally own a copy of *Spore* and
> any expansions you wish to test against. Reverse engineering is limited to
> interoperability analysis under applicable law (see `CONTRIBUTING.md` and
> the legal notes).

## What this is

OpenSpore reimplements *Spore* logic and data handling in C++ (C++17),
separating logic from data. A pipeline of specialized AI agents is orchestrated
by a main agent (opencode) and shares findings through:

- **Ghidra (via MCP)** — the analysis knowledge graph: functions, classes,
  structures, cross-references and decompilation. The Spore-ModAPI SDK symbols
  are imported here.
- **codegraph (via MCP)** — a pre-built index of this C++ codebase for surgical
  agent navigation.
- **SQLite sidecar** (`knowledgegraph/spore.db`) — a small, versioned, shared
  memory store for cross-tool results: differential-test outcomes, decisions,
  and asset-format mappings.

## Repository layout

```
opencode.json           # opencode config: wires codegraph + ghidra MCP servers
SPORE/                  # your local game install — IGNORED, never committed
knowledgegraph/         # SQLite sidecar + query helpers
docs/                   # analysis notes, UML, decisions
src/                    # C++ reimplementation (added in later phases)
tests/                  # unit + differential tests
.github/                # issue / PR templates
```

## Prerequisites

See `CONTRIBUTING.md` for the full toolchain (Ghidra 12.1.2, Java 21, Maven,
Wine, radare2, gdb/lldb, SDL3, Vulkan, CMake/Clang, `uv`, codegraph, ghidra-mcp).

## Quick start

```bash
# 1. Install codegraph (indexes this repo for agents)
npm i -g @colbymchenry/codegraph
codegraph install          # wire opencode
codegraph init

# 2. Start the Ghidra MCP server (see ghidra-mcp README), then
#    restart opencode so it picks up the MCP servers from opencode.json

# 3. Build the reimplementation (once src/ exists)
mkdir -p build && cd build && cmake .. && make -j
```

## Legal

This is clean-room reverse engineering. Do not copy EA source code, do not
redistribute game assets, and do not break DRM — use DRM-free (GOG) copies.
Contributors assume responsibility for their contributions.
