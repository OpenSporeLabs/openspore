# MIGRATION — classifying every existing subsystem

OpenSpore has **two coexisting halves**. Nothing was deleted when the Rust
workspace landed (`068124b`, `37efba9`).

* A **Rust + Bevy engine** (`crates/`, Cargo workspace, Bevy 0.19) — the
  direction. It renders a real Spore asset end to end. See
  [`RUST-ENGINE.md`](RUST-ENGINE.md).
* A **C++17 / Python reverse-engineering corpus** (`src/`, `tools/`,
  `knowledgegraph/`, `docs/`, `tests/`) — the knowledge, and still the
  reference implementation. It builds, it runs, and it remains the differential
  oracle for the Rust side.

This document is the classification the orchestrator directive requires: **one
verdict per subsystem**, from a closed set.

| verdict | meaning |
|---|---|
| **KEEP** | keep as-is; it is still the right thing |
| **PORT** | move into the Rust architecture |
| **REIMPLEMENT** | deliberately rewritten rather than translated |
| **RESEARCH-ONLY** | never code; it is knowledge and documentation |
| **OBSOLETE** | no longer useful, safe to drop (the replacement is named) |

Every number in this file was produced by a command run on **2026-10-04**; the
command is given next to it.

---

## 1. `src/assets/` — the C++ decoders

| subsystem | verdict | rationale |
|---|---|---|
| `Dbpf.{cpp,hpp}` | **PORT** | Already ported: `spore-dbpf` (DBPF v3 index + QFS/RefPack). The C++ stays as the differential oracle. |
| `Rw4.{cpp,hpp}` | **PORT** | Already ported: `spore-rw4` decodes the section **directory** only, by design. |
| `Gmdl.{cpp,hpp}` | **PORT** | Already ported: `spore-gmdl` (record walk + static mesh extraction). |
| `Mesh.{cpp,hpp}` | **PORT** | Already ported: `spore_gmdl::mesh_from_gmdl` + `compute_mesh_bounds`. |
| `Dxt5.{cpp,hpp}`, `Texture.{cpp,hpp}` | **PORT** | Already ported: `spore-texture` (32-byte envelope + the DXT5 block codec). |
| `ResourceStore.{cpp,hpp}` | **PORT** | Superseded by `spore_assets::ContentStore`, which adds ordered package priority and a typed `AssetError` instead of a `ContentErrorCode` + message pair. |
| `ModelStore.{cpp,hpp}` | **PORT** | Superseded by `spore_assets::model::ModelStore`; it accepts the same identities and additionally reports `ModelFormat`. |
| `TextureStore.{cpp,hpp}` | **PORT** | Superseded by `spore_assets::model::TextureStore`. |
| `ResourceKey.{cpp,hpp}` | **PORT** | Superseded by `spore_core::ResourceKey` (+ `WILDCARD`), which is the workspace's single identity type. |
| `MaterialRegistry.{cpp,hpp}` | **REIMPLEMENT** | The id→name mapping was **never recovered** — the C++ registry is populated from outside the record. `spore-material` re-implements the honest version: `MaterialModel::name` is `None`, `SamplerRole` has exactly one variant (`Unresolved`), and the type assumption is a parameter of every entry point. |
| `PropertyStore.{cpp,hpp}` | **PORT** (later) | `.prop` (1 162 records in `Spore_Content`) is still an explicit non-boundary (`docs/BOUNDARIES.md` §5.5). `osptool manifest` counts it `container-undecoded`. |
| `CellContent.{cpp,hpp}` | **PORT** (later) | Layouts are known and a Python oracle exists (`tools/spore/cellres/cellres.py`); the Rust side has none of the eleven cell-content record types. |
| `CellResource.{cpp,hpp}` | **PORT** (later) | Same eleven records. Gameplay configuration, not geometry; it does not unblock the render path. |
| `WorldObject.{cpp,hpp}` | **PORT** (later) | The `0x0F43029A` model-group walker (1 022 records in `Spore_Content`) plus `tools/spore/worldobj/worldobj.py`; scene placement needs it and the Rust engine has no scene loader yet. |
| `Stream.hpp` | **OBSOLETE** | A byte `Reader`/`Writer` pair absorbed into each Rust crate's own bounds-checked `cursor.rs`. Nothing outside `src/assets/` used it. |
| `src/assets/tests/` | **PORT** | Superseded by `tests/test_formats.py`, `tests/test_textures.py`, `tests/test_rw4.py` (Python oracles) and by `crates/*/tests/*.rs` (Rust). |

## 2. `src/renderer/` — the hand-rolled Vulkan backend

| subsystem | verdict | rationale |
|---|---|---|
| `Renderer.hpp` (the `IRenderer` seam) | **REIMPLEMENT** | Bevy's `Assets<Mesh>` / `Assets<StandardMaterial>` / entity-component pipeline replaces the interface. Its stated job in `docs/BOUNDARIES.md` B3 — allow substitution against the original — cannot apply to a Rust engine that never runs inside the original process. |
| `VulkanRenderer.{cpp,hpp}` | **OBSOLETE** | Replaced by `bevy_render` + `wgpu`, which already covers device init, swapchain/vsync present, offscreen readback and the lit path. A hand-written Vulkan backend is now pure maintenance. |
| `shaders/{triangle,lit}.{vert,frag}` + `embed_spv.py` | **OBSOLETE** | The SPIR-V is a from-scratch emulation of D3D9 fixed-function lighting. `bevy_pbr` supplies a real PBR pipeline; `tonemapping_luts` supplies the LUTs. `embed_spv.py`'s job (pack `.spv` into a C array) has no Rust consumer. |
| Root `CMakeLists.txt`'s `find_package(Vulkan REQUIRED)` | **OBSOLETE** *(for the Rust half)* | Stays exactly as it is for the C++ tree, which is still built and still the differential reference. Nothing in `Cargo.toml` needs Vulkan. |

## 3. `src/sim/` — the Cell Stage simulation

| subsystem | verdict | rationale |
|---|---|---|
| `Sim.{cpp,hpp}` (`CellSim`), `CellMovement.*`, `CellGame.*` | **REIMPLEMENT** (deferred) | The *contract* is right and stays (fixed `1/60` step, bit-exact replay, no `time()`/`rand()`). The *code* is not ported: the Rust engine has no simulation at all. See `docs/CELL-CONTRACT.md`. |
| `CellPool.hpp`, `CellQuery.hpp`, `Advect.hpp`, `Combat.hpp` | **REIMPLEMENT** (deferred) | Header-only gameplay helpers with no Rust counterpart; the Rust gap list names simulation explicitly. |
| `contract_scenarios.hpp` + `sim/` tests + `tests/fixtures/cell/fixtures.json` | **KEEP** | The frozen `cell-sim-contract/2` fixture set is the specification any future port must satisfy. Deleting it would delete the acceptance criteria. |
| `tools/gen_cell_fixtures.py` | **KEEP** | Generator for those fixtures; the double-run discipline is part of their value. |

## 4. `src/apps/` — the C++ applications and stage modules

| subsystem | verdict | rationale |
|---|---|---|
| `triangle.cpp` | **OBSOLETE** | Replaced by `openspore --placeholder` and by the unit-tested `convert` module. |
| `asset_view.cpp` | **OBSOLETE** | Replaced by `openspore --preset documented-asset --info` (headless) and `osptool describe`. |
| `material_smoke.cpp` | **OBSOLETE** | Existed to prove the C++ lit/DXT5 path; the Rust equivalent is `spore-material`'s synthetic tests plus `osptool verify`. |
| `cell_stage.cpp` | **REIMPLEMENT** (deferred) | The 32-target Cell Stage campaign is the reference behaviour (deterministic raster, `CELLSTAGE-MANIFEST v1`, ctest green). The Rust engine renders one static model and has no gameplay loop. |
| `CellGfx`, `CellUI`, `CellInput`, `CellModeStrategy`, `CellAnim`, `CellPresentation`, `CellSceneStage`, `IGameMode.hpp` | **REIMPLEMENT** (deferred) | A mode-strategy lifecycle mapped 1:1 to the original vtable is a real design worth carrying; none of it is in Rust yet. |
| `InputRouter.*`, `MessageManager.*` | **REIMPLEMENT** (deferred) | Same. The Rust engine's entire input surface is Escape-to-close (`spore_engine::exit_on_escape`). |
| `SceneConfig.{cpp,hpp}` + `scene.json` | **KEEP** | Declarative scene placement with per-value provenance, including the finding that the original placement is *procedural* (populate records carry `zOffset`/distribution; there is no stored x/y table). This is data a future Rust scene loader will read. |

## 5. `src/replace/` — the substitution experiment

| subsystem | verdict | rationale |
|---|---|---|
| `CellGameView.hpp` (`SCellGameView`), `Replace.{cpp,hpp}` | **REIMPLEMENT** (deferred) | 64/64 differential match against the decompilation reference, status `replaced-approx`. This is the only `replaced-approx` subsystem in the repository and its ABI record must be reproduced, not translated (`docs/REPLACEMENT-DIFF.md`). |
| `Reference.cpp` (decompilation transcription) | **KEEP** | It is the **oracle** `diff_test` compares against. Never delete an oracle; it is the only thing that makes the 64/64 meaningful. |
| `diff_test` | **KEEP** | The differential mechanism itself. |
| `tools/replace/synthetic/` | **KEEP** | Proves the inline-hook ABI (`0xE9 rel32` + RWX `mprotect`) on a native 32-bit target. See `docs/REPLACEMENT-ABI.md`. |

## 6. `src/reconstruction/` — the promoted-function corpus

Counts, verified 2026-10-04:

```
$ ls src/reconstruction | grep -v CMakeLists | wc -l          # 172
$ find src/reconstruction -maxdepth 2 -name promotion.json | wc -l   # 89
# distinct promoted VAs across those 89 files                   # 92
$ find src/reconstruction -name '*_model_test.cpp' | wc -l     # 176
$ grep -rl __thiscall src/reconstruction --include=*.hpp | wc -l  # 171
$ spore-semantic stats | grep promoted                         # promoted  92 (0.2%)
```

| subsystem | verdict | rationale |
|---|---|---|
| The 172 package directories (163 `pkg_*`, 7 `wave6_*`, `cheat_func44h_*`, `subobject_forward_*`) | **PORT** (mechanical, gated) | Each promoted package is a `.cpp`/`.hpp` pair plus a model test for one original function. Porting them is a transcription job with a per-VA promotion marker as the gate. |
| `promotion.json` markers (89 files, 92 VAs) | **KEEP** | The authoritative, self-maintaining record of what is promoted. `src/reconstruction/CMakeLists.txt` discovers packages *only* by this file, and `tools/reconstruction_tooling/build_gate.py` reads the same markers. |
| `-m32` + `__thiscall` model tests (`OPENSPORE_RECONSTRUCTION_M32`, default `ON`) | **REIMPLEMENT** | `__attribute__((thiscall))` is x86-32-only; clang and gcc both reject it in 64-bit under `-Werror=ignored-attributes`, which is why the flag is per-target. In Rust the calling convention becomes **data** (`Record::abi.calling_convention`, `stack_cleanup_bytes`) carried in the passport, not a compiler attribute. |
| `src/reconstruction/CMakeLists.txt` discovery loop | **OBSOLETE** | Replaced by Cargo workspace/crate discovery. The *rule* it encodes (a package is promoted iff it carries `openspore-promotion-1`) is preserved by `spore-semantic` and by the tooling. |

`reconstruction/` at the repo root is a different thing and stays: `evidence/`
(92 per-VA evidence packs), `knowledge/`, `metadata/`, `ownership/`,
`staging/`, plus `README.md`. **RESEARCH-ONLY** — it is the provenance record,
and `docs/tooling/` describes how it is consumed.

## 7. `src/compat/` — the substitution seams

| subsystem | verdict | rationale |
|---|---|---|
| `IResourceProvider` (`ResourceProvider.hpp`) | **OBSOLETE** | Exists so a caller can link either the real provider or a stub *while substituting for the original game*. The Rust engine reaches assets through `spore_assets::ContentStore` and never runs in the original process, so there is nothing to substitute. |
| `IMeshSource` (`MeshSource.hpp`) | **OBSOLETE** | Same reason. `spore_assets::model::ModelStore` + `spore_gmdl::Mesh` cover the same responsibility without the seam. |
| `IRenderer` | **OBSOLETE** | Same; `src/renderer/Renderer.hpp` is the only consumer and it is going too. |

`docs/BOUNDARIES.md` and `docs/replacement-status.json` stay as
**RESEARCH-ONLY**: they record *what* the original does and *how far* each
boundary got, which is knowledge, not code.

## 8. `src/editor/` — not in the original scope list, but it exists

| subsystem | verdict | rationale |
|---|---|---|
| `EditorSupport.{cpp,hpp}` | **REIMPLEMENT** (deferred) | Creature-editor support scaffolding. No Rust counterpart; the roadmap ranks the creature editor 8th. |

## 9. `tools/spore/` — the stdlib-only Python oracles

| subsystem | verdict | rationale |
|---|---|---|
| `dbpf/dbpf.py`, `rw4/rw4.py`, `gmdl/gmdl.py`, `raster/raster.py`, `dxt5/dxt5.py` | **KEEP** | They are the **independent implementations** the Rust crates are cross-checked against. `spore-rw4`'s `Rw4::describe` reproduces `rw4.py::describe` character for character precisely so the two walkers can be diffed. |
| `cellres/*` (9 modules), `worldobj/worldobj.py` | **KEEP** | The only implementations of the cell-content and world-object layouts. They are the source a future `spore-*` port must match. |
| `manifest/manifest.py` | **PORT** | Reimplemented as `spore_assets::ManifestBuilder` + `osptool manifest`. The determinism property (two runs byte-identical) is asserted by the Rust test suite too. |
| `asset_resolver.py` | **PORT** | Superseded by `spore_core`'s canonical type/group tables plus `osptool types` / `osptool find`. |
| `types/typenames.json`, `types/groupnames.json` | **KEEP** | Transcribed from the community SDK + a per-package prop directory. `spore-core` **copies** these tables; it does not re-derive them. Source data, not code. |
| `typescan.py` | **KEEP** | Builds the per-package type-name histogram; `osptool types --package` reproduces the measurement and cross-checks it against `verify`. |

## 10. `tools/mcp/`, `tools/re/`, `tools/reconstruction_tooling/`, `tools/observatory/`, `tools/ghidra/`, `tools/spore-semantic/`, `tools/triage/`, `tools/recon_worker/`, `tools/viewer/`

| subsystem | verdict | rationale |
|---|---|---|
| `tools/mcp/` — the 24-tool JSON-RPC server | **KEEP** | Verified: `tools/list` returns exactly **24** tools (`printf` an `initialize`/`tools/list`/`quit` sequence into `python3 tools/mcp/server.py`). It is the RE surface and is orthogonal to the engine. |
| `tools/re/` — `dossier.py` + `data/` snapshots | **KEEP** | The evidence dossiers every reconstruction target starts from. |
| `tools/reconstruction_tooling/` (27 modules) | **KEEP** | Owns eligibility, scoring, evidence, promotion, vftables, validation, the frontier. It is the engine of the RE campaign. |
| `tools/observatory/` — ptrace tracer, `observe.py`, `menu_walk.sh`, `agent_overlay.py`, machine lock | **KEEP** | The only runtime-observation path. Nothing else can produce OBSERVED/VERIFIED evidence. |
| `tools/ghidra/` — `ImportSporeSDK.java`, `VtableDetect.java`, `ExportXrefs.java`, headless launcher | **KEEP** | The analysis graph's write side. |
| `tools/spore-semantic/` — the Go 1.27 stdlib-only CLI | **KEEP** | The read-only exchange surface. `spore-semantic stats` reports **58 757** functions and **92** promoted over a 98 080 685-byte snapshot at binary `25d42a7a…d914e`. |
| `tools/triage/` — `classify.py`, `debt_map.py`, `export_xrefs.py`, `export_datarefs.py`, `rules-v1..v5.json` | **KEEP** | The frozen 58 757-function classification and the two canonical TSV exports. |
| `tools/recon_worker/` | **KEEP** | The single-worker execution harness the orchestrator drives. |
| `tools/viewer/` | **KEEP** | Read-only query UI over the KG. |
| `tools/kg_ingest.py`, `tools/openspore.py`, `tools/reconstruction_knowledge.py` | **KEEP** | CLI entry points for the KG and reconstruction knowledge. |

## 11. `knowledge/`, `knowledgegraph/`, `docs/`, `tests/`

| subsystem | verdict | rationale |
|---|---|---|
| `knowledge/semantic/function-passport-v1.jsonl` (98 080 685 bytes) | **RESEARCH-ONLY** | A committed projection of per-function knowledge with `content_sha256` over the record lines only. Consumers pin its hash, so it is an artifact, not code. |
| `knowledgegraph/` — `kg.py`, `scale.py`, `schema.sql`, `seed.py`, `seed-literals.json` | **KEEP** | The query sidecar and the canonical 7-level evidence scale. The *schema and scale* are code; `spore.db` itself is git-ignored (`*.db`). |
| `knowledgegraph/research/`, `knowledgegraph/triage/` | **RESEARCH-ONLY** | Deterministic JSON/JSONL/TSV projections: triage summaries v2–v6, xrefs `2540f2ca`, datarefs `2540f2ca`, the UNKNOWN debt map, the reconstruction-readiness audit. |
| `docs/` (20 top-level `.md` + `analysis/`, `devlog/`, `tooling/`) | **RESEARCH-ONLY** | The findings. Includes this file. |
| `tests/` (56 entries) | **KEEP** | The Python suite. `uv run --no-project --with pytest python3 -m pytest tests/ -q` → **1 842 passed, 3 failed** in 503.79 s (see §5 for which three and why). |
| `tests/fixtures/` (`mini_package.dbpf`, `mini_rw4.rw4`, `mini.gmdl`, `cell/`, `abi/`, `gen_fixtures.py`) | **KEEP** | Synthetic, committed, game-free fixtures — **shared by both halves**. The Rust integration tests read the same files the Python oracles are tested against, which is what makes the two implementations comparable at all. |
| `opencode.json` | **KEEP** | Wires the `codegraph`, `ghidra` and `openspore` MCP servers. |

## 12. Build systems

| subsystem | verdict | rationale |
|---|---|---|
| `CMakeLists.txt` + `src/**/CMakeLists.txt` | **KEEP** | The C++ tree is still built, still runs, and is still the differential oracle. `ctest --test-dir build -N` lists **131** tests in the configured build tree. |
| `Cargo.toml` + `crates/*/Cargo.toml` | **KEEP** | The Rust build. 9 members. |
| `tools/gen_cell_fixtures.py` | **KEEP** | See §3. |

---

## What "PORT" meant in practice here

The worked example is the **DBPF/QFS decoder**, because it is the only layer
ported end to end with all three references present: the C++ implementation, an
independent Python oracle, and the Rust port.

**Sources.** `src/assets/Dbpf.cpp` is 254 lines and is declared authoritative for
the format. `tools/spore/dbpf/dbpf.py` is an independent stdlib-only decode of
the same bytes and is treated as the *cross-check*, not as the specification.
`crates/spore-dbpf/` is the port, and `crates/spore-dbpf/src/lib.rs` opens with a
section titled **"Divergences from the C++ reference"** listing every place the
two differ.

**Named constants replaced magic numbers.** The C++ declares six file-local
constants (`kMagicSize`, `kHeaderSize`, `kOffIndexCount`, `kOffIndexOffset`,
`kCompQfs`, `kSizeMask`). The port promotes them to documented, `pub`, tested
constants: `MAGIC`/`MAGIC_64`, `COMPRESSION_NONE`/`COMPRESSION_QFS`,
`QFS_MAGIC_VARIANTS`/`QFS_MAGIC`/`QFS_HEADER_SIZE`, and the four token-class
thresholds `CTRL_SHORT_LITERALS` (252), `CTRL_LITERAL_RUN` (224),
`CTRL_LONG_MATCH` (192), `CTRL_MID_MATCH` (128). Each carries a doc comment saying
what it is *for*, and the QFS module opens with the full token grammar as a table
so the arithmetic in the match arms is checkable against the encoding rather than
against the code.

**Error strings became typed error variants.** The C++ threads a
`std::string& error` out of every function. `crates/spore-dbpf/src/error.rs`
(348 lines) defines `DbpfError` with **19 variants**, each mapping 1:1 onto a C++
error string so a Rust failure can be lined up with a C++ log line without a
translation table. One C++ branch — `dbpf: truncated header` — is **deliberately
not reproduced**, and the reason is written down: it is unreachable, because the
guard it sits behind (`ImageTooShort`, the 96-byte header) subsumes it. Its
sibling `dbpf: truncated index row N` is equally unreachable and is **kept**,
because there the guard and the row walk are separate arithmetic a future edit
could unlink.

**Every "unsupported by design" branch was preserved, not relaxed.** This is the
part that matters. The port does not become more permissive because it is new:

* `DBBF` (the 64-bit variant) is refused by name (`Unsupported64BitVariant`).
* A `compression` word outside `{0, 0xFFFF}` is a hard error. The Python oracle
  treats *any* non-`0xFFFF` value as "stored"; the port follows the C++ here and
  says so explicitly, because the oracle is the cross-check and not the spec.
* The index flag bit 2 ("shared instance id") is **skipped, not applied** — the
  port documents that honouring it would substitute one instance id for every
  row's own, which is the worst possible failure mode for a key-addressed store.
* The stored-size word's top bit is a **flag**, masked off with a published
  `SIZE_MASK`; without it every extent check fails on a valid package.
* The QFS decompressed size is the **only big-endian field** in the format and is
  byte-shifted explicitly rather than read through a typed LE reader.
* Every distance formula keeps its `+ 1`, with the reason written down: the stored
  operand is `distance - 1`, so a stored `0` means "one byte back", not "distance
  zero".
* gmdl version 9 is refused **by name** (`UnsupportedVersion`) rather than
  attempted; 32-bit indices, non-triangle-list `primType` and non-zero streams
  are hard errors; `spore-rw4` refuses to open a section payload at all.
* The DXT5 codec reproduces **four documented departures from the published
  BC3 specification** (an inverted palette-size test, R5G5B5 channel reads, a 6/2
  blend where the spec puts the endpoints, and no `alpha0 == alpha1` collapse).
  "Correcting" the codec to the published spec would change every pixel the game
  draws.

**Three divergences are deliberate and each has a stated reason.** The port
enforces the `memory_size == decompressed length` invariant on the *stored* path
too (the C++ only checks it after a QFS decompression), because on the stored
path the two words describe the same bytes twice and a disagreement is always
corruption. It moves that size check ahead of the copy. And it does not
reproduce the unreachable "truncated header" variant.

**How the cross-check actually runs.** The two implementations are tested against
the *same committed synthetic fixture* — `tests/fixtures/mini_package.dbpf`,
generated by `tests/fixtures/gen_fixtures.py`, readable with no game install.
`crates/spore-dbpf/tests/fixture.rs` (22 tests) and `crates/spore-dbpf/tests/qfs_tokens.rs`
(17 tests, with a QFS *encoder* in `tests/support/qfs_encoder.rs` that has no
business inside the decoder) both read it. `crates/spore-dbpf` totals **109**
passing tests (`cargo test -p spore-dbpf`).

**One thing not yet done, stated honestly.** For RW4 there is a live
record-by-record differential — `tests/test_rw4.py` runs the **C++** `rw4_test`
walker and the Python oracle over all 1 131 real records and requires
byte-identical output. The Rust `Rw4::describe` reproduces `rw4.py::describe`
character for character, so its *format* is compatible by construction, but there
is no Rust-vs-oracle differential test in the tree yet (`crates/spore-rw4` has
unit tests only: **45** passing, `cargo test -p spore-rw4`).

---

## What the Rust workspace deliberately does NOT do yet

Each of these is a real gap, not a roadmap item with a date. The Rust crates
state their own gaps in their crate-level docs; this is the consolidated list.

| gap | why it is still a gap |
|---|---|
| **RW4 section payloads** | `spore-rw4` decodes the section *directory* (header, manifest, type-code table, 24-byte section rows) and nothing else — no raster texel layout, no mesh vertex/index layout, no skeleton, no animation track. An `rw4` model loads and reports **zero** meshes rather than pretending otherwise. The directory has no opinion about what a payload means, and inventing one in the walker is how a directory starts lying. |
| **gmdl version 9** | `SUPPORTED_VERSION = 8`. Version 9 changes the material-info framing — its per-material block carries no entry-count word — and no version-9 record has been validated against the walk. It is refused by name. |
| **Cell-content records** | The eleven `cCellCellResource` siblings (`cCellGlobalsResource`, `cCellEffectMap`, `cCellBackgroundMap`, `cCellStructure`, `cCellWorldResource`, `cCellPopulate`, `cCellRandomCreature`, powers, look-table, look-algorithm, loot-table) have known layouts and a Python oracle in `tools/spore/cellres/`, but no Rust port. They are gameplay configuration, not geometry, and they do not unblock the render path. |
| **`.prop` records** | 1 162 of `Spore_Content`'s 17 119 rows, counted `container-undecoded`. `PropertyStore` exists in C++; there is no Rust equivalent. `docs/BOUNDARIES.md` §5.5 still lists property serialization as an open non-boundary. |
| **world-object records** | `0x0F43029A`, 1 022 rows in `Spore_Content`. C++ walker + Python oracle exist; no Rust equivalent, so there is no scene placement. |
| **Audio** | Absent by design. `bevy_audio` is not in the workspace, which is also why the build needs no ALSA. |
| **Input beyond the window** | `bevy_gilrs` is not in the workspace. The engine's entire input surface is Escape-to-close, which is an OpenSpore decision, not a recovered Spore binding. |
| **Simulation** | No `CellSim` equivalent. The contract in `docs/CELL-CONTRACT.md` is the spec; nothing implements it in Rust. |
| **Creature model / gameplay** | No mode strategy, no scene stage, no creature data. The engine decodes one static mesh. |
| **UI** | `bevy_ui` is not in the workspace. No menus, no HUD, no Sporepedia. |
| **PNG decoder** | `png`-typed records (`0x2F7D0004`) are **raw PNG** — measured: all 1 642 in `Spore_Content` begin `89 50 4E 47 0D 0A 1A 0A`, and 10 487 of 10 487 across the installed data set. Nothing decodes them; `osptool describe` prints the extent and says so. Bevy's `png` feature is enabled for image *loading* in assets, not for a Spore `png` record decoder. |
| **Palette decoder** | `plt` (`0x011989B7`) has no decoder in either half. `spore-assets`' decodable set is exactly `{gmdl, raster, rw4}` and a test asserts the manifest and the loader agree on it. |
| **Material names** | What a gmdl material id names is **not known**. `spore-material` returns `None` for every id, has one `SamplerRole::Unresolved` variant, and records the type assumption at `INFERRED` rather than burying it. |
| **Instance naming** | DBPF has no string table. An instance id is opaque and nothing in Rust invents a name for one. |

---

## What must never be copied

The clean-room boundary is a hard rule, not a preference. It is stated in
`AGENTS.md` under **Hard rules (legal / ethics)**, in `README.md` §Legal, in
`docs/STATE.md` §8, and — per-crate — in the `# Clean-room` / `# Clean-room
boundary` section of every `crates/*/src/lib.rs` doc comment.

* **No EA or Maxis code, asset or data.** No binaries, no decompiled source, no
  models, no textures, no sounds, no scripts. `AGENTS.md`: *"Reimplement by
  analysis only (clean room)."*
* **No DRM circumvention.** Use DRM-free GOG copies. `SPORE/` is git-ignored and
  `.gitignore` enforces it along with `*.package`, `*.gmd`, `*.bmdl`, `*.bgeo`,
  `*.manifest`, `steam_api.dll` and `goggame-*.dll`. The operator's game install
  is memory-mapped at read time and **never copied into the repository**.
* **The community SDK and ModAPI/SporeModder-FX are semantics-only.** They are
  GPL and are reference material. Addresses and type *names* may inform an
  analysis; code is never copied. `librw` (MIT) is the only external renderer
  reference this repository has used.
* **No `spore-recomp` implementation is vendored, linked or embedded.** The
  runtime-evidence bridge (`spore-semantic runtime`) reads spore-recomp's
  reports as an *optional external artifact* over a documented JSON Lines schema
  (`spore-semantic-runtime-overlay-1`). The dependency runs one way only: no
  OpenSpore checkout, no Python and no Ghidra are needed to produce a report, and
  spore-recomp may stop emitting reports entirely without anything here breaking.
  A runtime observation also never upgrades a static verdict — every joined
  output carries `verdict_unchanged`.
* **The Rust crates import no OpenSpore source as production code.** Every
  container layout in `crates/spore-{dbpf,rw4,gmdl,texture}` is a reimplementation
  from format analysis; the reference material is this repository's own research
  (`docs/ASSET-PATH.md`, `docs/RENDERWARE-RESEARCH.md`) and its independent Python
  oracles under `tools/spore/`, both of which are OpenSpore's own work.

### The test baselines, with the commands that produced them

| suite | command | result (2026-10-04) |
|---|---|---|
| Rust workspace | `cargo test --workspace` | **696 passed, 0 failed, 10 ignored** across 48 suites |
| — `spore-core` | `cargo test -p spore-core` | 24 passed |
| — `spore-dbpf` | `cargo test -p spore-dbpf` | 109 passed |
| — `spore-rw4` | `cargo test -p spore-rw4` | 45 passed |
| — `spore-gmdl` | `cargo test -p spore-gmdl` | 121 passed |
| — `spore-texture` | `cargo test -p spore-texture` | 71 passed |
| — `spore-assets` | `cargo test -p spore-assets` | 22 passed |
| — `spore-material` | `cargo test -p spore-material` | 61 passed, **1 ignored** |
| — `spore-engine` | `cargo test -p spore-engine` | 40 passed |
| — `spore-tools` | `cargo test -p spore-tools` | 203 passed, **9 ignored** |
| C++ | `ctest --test-dir build -N` | 131 tests listed in the configured build tree |
| Python | `uv run --no-project --with pytest python3 -m pytest tests/ -q` | **1 842 passed, 3 failed**, 4 738 subtests, 503.79 s |

The **10 ignored Rust tests** all declare the same reason and are not defects:
`crates/spore-material/tests/real_asset.rs` (1) and
`crates/spore-tools/tests/real_package.rs` (9) need the git-ignored `SPORE/` tree;
each is annotated `needs SPORE/Data/Spore_Content.package; run with --ignored`.

The **3 failing Python tests**:

* `tests/test_agent_overlay.py::OverlaySelfTest::test_selftest_passes_on_display` —
  **ENVIRONMENTAL**. Needs a real X display and the `Xlib` module, which the
  isolated `uv --no-project` environment does not have. Report it as
  ENVIRONMENTAL, never as PASS.
* `tests/test_coverage.py::CoverageSemanticsTest::test_git_index_probe_is_disclosed_not_hidden`
  and
  `tests/test_promotion_hardening.py::DeterminismTest::test_two_scratch_runs_are_comparable_despite_their_random_temp_names`
  — both fail on this machine regardless of the change under test. The second is a
  timing leak: the diff is `0.2s` vs `0.3s` inside the captured CMake output.

### One correction, and it is worth flagging *because of who was wrong*

`docs/STATE.md` §5 states: *"PNG32 records (DBPF type `0x2f4e681b`, 1131 in
Spore_Content) are **RW4 containers, not raw PNG** (60/60 sampled)"*, and
`docs/CELLSTAGE-RECON.md` §2 and `docs/MATERIALS-DESIGN.md` §2 say the same
with the evidence. **That is correct**, and the Rust side confirmed it
independently: all 1 131 `0x2F4E681B` records carry `RW4w32`, none are PNG.

What was wrong was the **new Rust code**, not the research. Three doc comments
written during the port (`spore-core::record::type_id::RW4`,
`spore-assets`'s decoder list and `spore-rw4`'s crate docs) asserted that
*`png`-typed* records are RW4 blobs. They are not: `png` is `0x2F7D0004`, a
different type id from `rw4` (`0x2F4E681B`), and all 1 642 of it in
`Spore_Content` — 10 487 of 10 487 across the installed data set — begin
`89 50 4E 47 0D 0A 1A 0A` and are stored uncompressed. `0x2F4E681B` and
`0x2F7D0004` differ by one bit and mean entirely different things.

The failure mode is worth naming because it is easy to repeat. A *near-miss*
type id was inherited from a summary line rather than from a record, and three
crates then quoted the comment, so the error acquired the appearance of a
consensus. The fix is in `spore-core` (with `type_id::PNG`/`JPEG` added and a
test pinning the two clusters apart) and in `spore-assets`; the existing
research documents were left exactly as they were, because they were right.

The general lesson for the migration: **the corpus outranks the port.** When a
new Rust file and an existing research document disagree, the tie-breaker is a
byte count over the real data — and until that count has been run, the port is
the one that is presumed wrong.