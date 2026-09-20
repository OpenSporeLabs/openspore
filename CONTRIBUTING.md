# Contributing to OpenSpore

Thank you for helping. Read the legal notes first.

## Legal & ethics (read before contributing)

- **No proprietary assets or code.** The repo must never contain *Spore* files,
  decompiled EA source, models, textures, sounds, or scripts. Every developer
  extracts their own assets from a legally owned copy.
- **Clean-room only.** Reimplement by analysis, never by copying EA code.
- **No DRM circumvention.** Use DRM-free (GOG) copies. Do not strip protections.
- **No trade secrets / leaked code.** Every contribution is your own analysis.
- Report anything that looks like leaked material; it will be removed.

## Toolchain (CachyOS / Arch Linux)

| Tool | Notes |
|------|-------|
| Ghidra 12.1.2 | `/opt/ghidra` (pkg `ghidra`) |
| Java 21 (OpenJDK) | required by Ghidra + ghidra-mcp |
| Maven 3.9+ | `pacman -S maven` |
| Wine 11 | for running/verifying the original game |
| radare2 | `pacman -S radare2` |
| gdb / lldb | `pacman -S gdb lldb` |
| CMake / Clang / GCC | `pacman -S cmake clang gcc` |
| SDL3 | `pacman -S sdl3` |
| Vulkan | `pacman -S vulkan-radeon` (or `-intel`) |
| Python 3.10+ + `uv` | `uv` for ghidra-mcp |
| codegraph | `npm i -g @colbymchenry/codegraph` |
| ghidra-mcp | `yay -S ghidra-mcp` (AUR) or clone + `uv` |

## Code style

- C++17, `clang-format` (modified Google style).
- `fmt` for formatting; avoid `printf`/`std::cout` in library code.
- Clear, consistent naming; comments in English (or clear Spanish).
- Run `clang-tidy` / `cppcheck` before submitting.

## Workflow

1. Create a `feature/<name>` branch from `main`.
2. Make focused changes; add tests for any new feature.
3. Expansion-related commits are tagged `feat(GA):`, `feat(CnC):`, etc.
4. Open a PR using the template; CI must pass (build + differential tests).

## Tests

Every accepted feature ships with tests. Differential tests run the original
*Spore* under Wine as an oracle and compare against the reimplementation. See
`tests/` and the differential verification plan in `docs/`.

## Agent pipeline

Analysis is driven by opencode + MCP servers (see `opencode.json`):
- **ghidra** (ghidra-mcp) → binary/structure analysis.
- **codegraph** → C++ source navigation.
- **knowledgegraph/spore.db** → shared memory for results and decisions.

Keep analysis findings in the Ghidra project; persist cross-tool results in the
SQLite sidecar. Do not reinvent a general knowledge-graph store.
