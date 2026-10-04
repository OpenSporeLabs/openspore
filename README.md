# OpenSpore

An open, from-scratch, clean-room reimplementation of *Spore* (base game) and its
expansions (e.g. *Galactic Adventures*).

> **Warning:** This project is for research purposes only. It does **not**
> contain, build, or distribute any proprietary *Spore* code, assets, models,
> textures, sounds, or data files. You must legally own a copy of *Spore* and
> any expansions you wish to test against. Reverse engineering is limited to
> interoperability analysis under applicable law (see `CONTRIBUTING.md` and
> the legal notes).

## Two halves, both alive

This repository has **two coexisting halves**. Nothing was deleted when the
second one landed.

1. **A Rust + Bevy engine** — the direction. It loads a real Spore `.package`
   from disk and renders pixels.
2. **A C++17 / Python reverse-engineering corpus** — the knowledge, and still the
   reference implementation. It builds, it runs, and it remains the differential
   oracle for the Rust side.

## The headline: a vertical slice that works

A real Spore asset, decoded and on screen, with nothing faked in between:

```bash
cargo run -q -p spore-engine -- --preset documented-asset \
    --package SPORE/Data/Spore_Content.package
```

Add `--info` and it decodes, prints one machine-readable line and exits **without
opening a window** — which is what makes it usable as a CI gate:

```
OPENSPORE-STAGED v1 key=0x00e6bce5:0x40637e03:0x067a07f0 package=Spore_Content format=gmdl meshes=1 triangles=20 bounds_min=-2.070057,0.139144,0.081329 bounds_max=-0.371524,2.164293,5.326164 normals=derived
```

794 stored bytes → QFS → 1 156 bytes → one gmdl record, version 8, 32 vertices,
20 triangles, from `SPORE/Data/Spore_Content.package`.

### What works today

| | |
|---|---|
| **Rust** | 9 crates, `cargo test --workspace` → **696 passed, 0 failed, 10 ignored** (the 10 need the game installed). `cargo clippy --workspace --all-targets -- -D warnings` is clean. |
| **The engine** | decodes and renders a real gmdl; derives normals because the record's `UBYTE4` encoding is only INFERRED; `--placeholder` proves the renderer with no game data at all. |
| **`osptool`** | offline inspector for DBPF packages: `list`, `find`, `describe`, `extract`, `manifest`, `verify`, `types`. Byte-for-byte reproducible output. |
| **C++** | still builds and still runs; `ctest --test-dir build -N` lists 131 tests. It is the differential reference — do not delete it. |
| **Python** | the reverse-engineering suite: `uv run --no-project --with pytest python3 -m pytest tests/ -q`. |
| **Tools** | a 24-tool JSON-RPC MCP server, a Ghidra import/vtable/xref pipeline, a ptrace tracer, and a stdlib-only Go CLI that exports a per-function passport. |

## The crates

| crate | one line |
|---|---|
| `spore-core` | resource identity, record type ids, and the evidence/provenance vocabulary. Dependency-free. |
| `spore-dbpf` | DBPF v3 package index, QFS/RefPack decompression, record extraction. |
| `spore-rw4` | RenderWare 4 section **directory** walker. Section payloads are deliberately out of scope. |
| `spore-gmdl` | gmdl (`GameModel`) record decoder and static-mesh extractor. |
| `spore-texture` | raster envelope parsing and the DXT5/BC3 block codec. |
| `spore-assets` | the boundary where Spore data enters the engine: package priority, identity resolution, typed decode, the canonical manifest. |
| `spore-material` | what a gmdl material id names — and what this build does not know. |
| `spore-engine` | the runtime: a Bevy application that loads and renders real Spore assets. |
| `spore-tools` | `osptool`, an offline inspector. Library-first, binary-as-shim. |

Everything above the engine is renderer-agnostic and Bevy-free, which is why the
asset layer is testable with no window and no GPU.

## Read next

| | |
|---|---|
| [`docs/RUST-ENGINE.md`](docs/RUST-ENGINE.md) | developer guide to the Rust workspace: crate graph, build/test/lint, running the slice, `osptool`, the Bevy feature set and why, the two gotchas, the honest limits |
| [`docs/MIGRATION.md`](docs/MIGRATION.md) | how every existing subsystem is classified — KEEP / PORT / REIMPLEMENT / RESEARCH-ONLY / OBSOLETE — what "PORT" meant in practice, and **what the Rust workspace deliberately does not do yet** |
| [`docs/SEMANTIC-BRIDGE.md`](docs/SEMANTIC-BRIDGE.md) | what the read-only semantic exchange actually contains, measured |
| [`docs/STATE.md`](docs/STATE.md) | state of the C++/Python research corpus: objectives, validated capabilities, known limitations |
| [`AGENTS.md`](AGENTS.md) | rules and durable context for any agent working in this repo, including the hard legal rules and the traps that cost real debugging time |

## The research corpus

The C++/Python half is not legacy to be tidied away — it is where the knowledge
lives, and it is still the specification the Rust side is written against.

- **Ghidra (via MCP)** — the analysis knowledge graph: functions, classes,
  structures, cross-references and decompilation. The Spore-ModAPI SDK symbols
  are imported here.
- **codegraph (via MCP)** — a pre-built index of this repository for surgical
  agent navigation.
- **SQLite sidecar** (`knowledgegraph/spore.db`, git-ignored) — a small,
  versioned, shared memory store for cross-tool results: differential-test
  outcomes, decisions, and asset-format mappings.
- **`spore-semantic`** — a stdlib-only Go CLI that exports a deterministic
  snapshot of per-function knowledge (58 757 functions) and answers
  `binary_sha256 + VA` lookups. No network, no Python, no Ghidra at runtime.

## Repository layout

```
Cargo.toml crates/     # the Rust + Bevy engine
CMakeLists.txt src/    # the C++17 reference implementation — still built, still the oracle
tools/                 # Python oracles, MCP server, Ghidra scripts, tracer, Go CLI
knowledge/             # the committed per-function passport (JSON Lines)
knowledgegraph/        # SQLite sidecar + triage artifacts
reconstruction/        # evidence packs, metadata, ownership, staging
docs/                  # analysis notes, contracts, decisions
tests/                 # the Python suite + shared synthetic fixtures
SPORE/                 # your local game install — IGNORED, never committed
```

## Prerequisites

**Rust:** a Rust toolchain (edition 2021, `rust-version = "1.85"`), plus a GPU
driver for anything that opens a window. `--info`, `osptool` and the whole test
suite need no GPU and no game install.

**C++ / research:** see `CONTRIBUTING.md` for the full toolchain (Ghidra 12.1.2,
Java 21, Maven, Wine, radare2, gdb/lldb, SDL3, Vulkan, CMake/Clang, `uv`,
codegraph, ghidra-mcp).

## Legal

This is clean-room reverse engineering. Do not copy EA source code, do not
redistribute game assets, and do not break DRM — use DRM-free (GOG) copies.
Contributors assume responsibility for their contributions.

Concretely, and enforced by `.gitignore`: no EA or Maxis code, asset or data is
vendored, linked or embedded in either half; `SPORE/` and `*.package` are never
committed; the community SDK and ModAPI/SporeModder-FX are **semantics-only**
reference material and their code is never copied; and no external
reimplementation's source is vendored. Spore's assets stay on your disk and are
read at runtime, never copied into the repository.