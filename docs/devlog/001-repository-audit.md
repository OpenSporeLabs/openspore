# 001 — Repository audit

**2026-09-20, shortly after the bootstrap commit.** The repository now exists as
scaffolding: commit `f6f850d` (13:37) landed the README, CONTRIBUTING, MIT LICENSE,
code of conduct, GitHub templates, `AGENTS.md`, the 331-line plan in `OpenSpore.md`,
a 67-line `docs/STATE.md`, the `knowledgegraph/` sidecar (`schema.sql` + `kg.py`),
and `opencode.json`. That was [where it all started](000-project-origin.md). Before
we trusted any of it, we did what we should have done before writing the plan:
audit what the plan had assumed against what the machine and the toolchain actually
offered. This is that audit — a desk audit, run the same afternoon, not a crisis
response.

## The audit

The plan in `OpenSpore.md` was written generically. The machine is specific. Walking
the plan's environment table row by row produced five observed discrepancies.

### OS: Ubuntu 22.04 + apt → CachyOS / Arch + pacman

The plan's dependency table is headed *"Installation (Ubuntu 22.04)"* and every
install command in it is an `apt` command (`sudo apt install radare2`, `sudo apt
install winehq-stable`, the winehq `deb` repository setup, `libsdl3-dev`, ...).
The host is **CachyOS / Arch**. None of those commands run here; the correct form
for every one of them is `pacman -S`. The plan's suggested CI (`runs-on:
ubuntu-22.04` with apt caches) remains valid *for CI runners* — it is simply not a
description of the development box. We recorded the correction in `AGENTS.md`
("CachyOS / Arch — use `pacman`, NOT `apt`") so no future agent repeats the plan's
commands verbatim.

### Ghidra: pinned 10.3.x → installed 12.1.2, with API drift

The plan pinned **Ghidra 10.3.x** (its `analyzeHeadless` examples path into
`ghidra_10.3.8_PUBLIC/`). What is installed is **12.1.2** at `/opt/ghidra`, and
its user profile is `ghidra_12.1.2_DEV` — not the `_PUBLIC` suffix every 10.x
write-up (and the plan's examples) assume.

The deeper issue is that the plan's Ghidra examples were written against older
documentation, and Ghidra 12's API has renamed the things those examples rely on.
`run_script_inline` compiles Java against the Ghidra 12 OSGi classpath, so every
assumption in the older docs is a compile error. The concrete renames we hit:

- `Symbol` — `getName()` / `getAddress()`, not `getPrimaryName()` / `getPrimaryAddress()`
- `getSymbols(String)` returns a `SymbolIterator` — there is no `SymbolType` overload
- No for-each on `Function` — iterate `program.getInstructionIterator(setView)` instead
- `AddressSetView.getMaxAddress()`, not `getEnd()`
- No `AddressSpace.translateFromInteger`

Evidence that this was not theoretical: by the time the recon ran, **10+ failed
inline scripts had accumulated as `McpInline_*.java` files in `~/ghidra_scripts/`**
— each one a rename of the list above, compiled, failed, and left behind. We
recorded the renames in `AGENTS.md` so the cost of learning them is paid once.

### Knowledge graph: Neo4j → SQLite sidecar

The plan's default was **Neo4j** ("We will start with Neo4j (Community Edition)
due to its robustness with graphs and support for intelligent agents"; the agent
fleet was to query it via Cypher). What the repo actually shipped at bootstrap was
a **SQLite** sidecar: `knowledgegraph/schema.sql` + `kg.py`, with a query CLI
(`init | add-node | add-edge | query | neighbors | record-test | dump`).

This is an implementation decision, recorded as such in `AGENTS.md` ("No Neo4j /
no general graph DB"), with the rationale being simple:

- single file, versionable, zero services to run
- the query CLI was already tested at bootstrap (nodes / edges / test-results
  round-tripped)
- the *analysis* graph (Ghidra) and the *source* graph (codegraph) are already
  their own graph stores; SQLite only holds cross-tool results — test outcomes,
  decisions, asset-format mappings — where Cypher buys nothing

The plan's own comparison table listed SQLite as a candidate format; we kept the
plan's *options* and dropped its *default*.

### LLM: LM-Studio fleet on a big GPU → opencode + local llama.cpp

The plan assumed **Qwen 3.8 27B served by LM Studio** on a large GPU (~25 GB VRAM,
"RTX 3090 / 7900 XTX"), with an agent fleet (binary / structures / asset / dynamics
/ rendering / tracing / implementation / verification agents) talking to it.
Reality is **opencode** orchestrating agents against a **local llama.cpp server**.
No LM Studio, no HuggingFace container, no gRPC between agents.

The consequence worth stating explicitly: on this machine, **subagent work must be
strictly sequential (RAM)**. There is no headroom for parallel local inference.
That constraint shaped how all later work was scheduled — one workstream at a
time, even where the plan's architecture implied parallel agents.

### Game: 1.5.1-patched install → GOG 3.1.0.22

The plan's game row said: install from GOG/Steam, then *"Patch to v1.5.1 with the
official fix."* What is at `./SPORE/` is the **GOG digital collection, build
3.1.0.22** — the final unpatched GOG build, not a 1.5.1 install. Two direct
consequences for the whole project:

1. **Every address, RVA and symbol offset in the project is from 3.1.0.22.**
   There is no 1.5.1 baseline to speak of; the plan's "final version" target and
   the binary we analyze are different binaries.
2. **The SDK symbol file is the digital-build variant.** The Spore-ModAPI SDK
   ships two XMLs: `SporeGhidra_disk.xml` (disk install) and
   `SporeGhidra_march2017.xml` (digital). GOG = digital → we use `march2017.xml`.
   The plan's `analyzeHeadless` example passes `SporeGhidra_disk.xml`; that line
   is wrong here, and `AGENTS.md` now pins the correct file.

## Proprietary-asset hygiene

For a clean-room project the repository *is* the public artifact. One accidental
commit of a `.package` file would break the entire legal posture — the code can be
MIT while the repository contains EA assets, and that combination is not
defensible. So the enforcement point is the `.gitignore`, and it had to be
complete, not exemplary.

The bootstrap `.gitignore` covers:

- `SPORE/` (the whole game tree) — plus `*.package`, `*.gmd`, `*.bmdl`, `*.bgeo`,
  `*.manifest` as catch-alls in case assets land anywhere else
- third-party / platform DLLs that ship with the GOG build: `msvcr*.dll`,
  `steam_api.dll`, `goggame-*.dll`, `goggame-*.info`, and `gog_installer/*`
- build outputs: `build/`, `cmake-build-*/`, `out/`, `__pycache__/`, `*.o`, `*.so`,
  `*.dll`, `*.exe`, plus the observatory's built tracer and capture scratch space
- logs / traces: `*.log`, `wine_trace.log`, `spore_log.txt`, `*.out`
- local generated state: `*.db`, `*.sqlite3` (KG sidecars), `.codegraph/`,
  editor cruft

Verification at bootstrap: `git status` showed nothing ignored-but-tracked — no
file that matched an ignore pattern was already in the index. (A later re-check of
`git ls-files` against the asset patterns returns only project-named files —
`tools/spore/*`, `OpenSpore.md`, and the synthetic `tests/fixtures/mini.gmdl`,
which is a generated fixture, not an EA asset.) The rule lives in `AGENTS.md` in
its strongest form: `SPORE/` is git-ignored — *keep it that way*.

## GPL / reference-material hazards

The analysis workflow leans on existing open-source RE material. The license
boundaries are explicit, because they are the difference between "informed by" and
"derived from":

| Project | License | Status in this project |
|---|---|---|
| librw (libRenderWare) | MIT | **Usable** — as code or reference, with attribution |
| re3 / reVC | Unlicensed (DMCA'd 2021-02) | Reference only — never code |
| Spore-ModAPI | GPL-3.0 | Reference only — semantics, not code |
| SporeModder-FX | GPL-3.0 | Reference only — semantics, not code |

The rule, exactly as the project enforces it: **copy code only from MIT, with
attribution.** Everything else may inform analysis — struct layouts, enum values,
field order, format parsers used as cross-checks — but no code from GPL or
unlicensed projects enters the MIT tree, because it would taint it. The full
license landscape and its consequences for the renderer are covered in
[chapter 003](003-renderware-research.md).

## Why the project needed stronger foundations

Nothing here is dramatic. The repository was hours old. But the audit showed the
risks were real, and all three of them were of the kind that do not announce
themselves until they bite:

1. **A plan whose environment assumptions were all stale.** Every install command,
   the Ghidra version, the profile name, the SDK XML variant, the game version —
   each one silently wrong on this machine. Left unrecorded, each would have been
   re-discovered, and re-wrong, by a future agent.
2. **Analysis tooling with silent API drift.** Ghidra 12 breaks older examples at
   *compile time of the script*, not at runtime of the analysis — failures look
   like "the script is buggy" and accumulate in `~/ghidra_scripts/` until someone
   notices the pattern. The 10+ `McpInline_*.java` corpses are that pattern.
3. **Legal hygiene that only holds if the ignore-list is complete and the license
   boundaries are explicit.** A `.gitignore` that catches `SPORE/` but not
   `goggame-*.dll`, or a rule that says "GPL is fine for reference" without
   defining where reference ends and copying begins, is hygiene in name only.

All three were addressed inside the first day: the corrections landed in
`AGENTS.md` (which is what agents actually read), the SQLite decision was recorded
with its rationale, and the ignore-list was verified against `git status`.

## Cross-links

- Back: [000 — Project origin](000-project-origin.md) (the plan being audited, and
  the bootstrap commit).
- Forward: [002 — Ghidra foundation](002-ghidra-foundation.md) (the import repair,
  the corrupt project, the recon — where the audit's Ghidra findings start paying
  off).

### Outcome

| Proven | Open |
|---|---|
| Environment tabled and verified per `STATE.md`: 12 tool rows (Ghidra 12.1.2, Java 21, Maven, Wine 11.17, radare2 6.2, gdb/lldb, CMake/Clang/GCC, SDL3 3.4.16, Vulkan, Python + uv, codegraph 1.6.0, ghidra-mcp 7.0.0) | Ghidra 12 API friction would bite again in the next phase — the renames were recorded, not eliminated |
| Ignore-list complete at bootstrap: verified via `git status`, nothing ignored-but-tracked | The Neo4j→SQLite deviation is an internal decision, unreviewed by any external party |
| SQLite KG tested at bootstrap: nodes / edges / test-results round-trip through `kg.py` | No `src/` code existed yet, so the build path (CMake, zero-warning policy) was untested |
| `AGENTS.md` encodes the corrected toolchain rules (pacman, `_DEV` profile, headless MCP server, `march2017.xml`, defensive import, API renames) | The sequential-subagent constraint (RAM) is an observed limit, not a documented capacity plan |
