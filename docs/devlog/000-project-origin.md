# 000 — Project origin: a 331-line plan becomes a repository

**State of play — 2026-09-20, morning.** The repository is about to be born,
and the tree contains exactly one document: `OpenSpore.md`, a 331-line plan
that describes — in the future tense — everything the project is supposed to
become. No code, no tools, no tests, no analysis. By 13:37 that single plan
plus its scaffolding is committed as `f6f850d`, and the project exists.

## The plan

`OpenSpore.md` is self-labelled a BOOTSTRAP document: "an open repository for
a clean reimplementation of *Spore* (base game) and its expansions (e.g.
*Galactic Adventures*) from scratch, using reverse engineering tools and
LLMs". Read honestly, it is an executive summary that grew legs — objectives,
legal requirements, a dependency table, installation steps, architecture
diagrams, test scripts, and a roadmap — and it states its target audience
plainly: intermediate/advanced developers in C++ and reverse engineering.

**The agent fleet.** The pipeline is a star topology: one orchestrator (a
"master script or service" managing work queues) dispatching to nine
specialized agents, all of which read from and write to a shared knowledge
graph:

```
                     Orchestrator (main agent)
   +--------+---------+----------+----------+----------+----------+
   v        v         v          v          v          v          v
 Binary  Decompiler  Structures  Assets   Dynamics  Rendering   Tracing
   +--------+---------+----------+----------+----------+
   v        v         v          v          v
 Implementation Engineering   Verification (differential)
   \______________________________________/
                  shared knowledge graph
```

The plan names all nine: Binary Analysis, Decompilation and Calls, Data
Structures, Asset Formats, Game Dynamics, Rendering/Graphics, Runtime
Tracing, Implementation Engineering, and Verification/Differential.
Communication between agents is left open — JSON-based APIs or gRPC, with the
Model Context Protocol (MCP) suggested for graph querying from inside a
conversational agent. (MCP is the option that survives, see below.)

**The knowledge graph.** The plan's centerpiece is a graph of Spore entities
— *Creature*, *Resource*, *Renderer*, *Class/Method* nodes — where every node
carries confidence attributes ("validated?", `origin: static/dynamic/SDK`)
so the agents' "memory" of what has already been analyzed is explicit. For
storage, the plan evaluated five candidates in a comparison table and chose
Neo4j Community Edition first:

| Candidate (plan's table) | Plan's verdict |
|---|---|
| Neo4j Community | **chosen** — Cypher, ACID, mature visualizations |
| SQLite (+RDF) | easy install, portable single file; not a native graph DB |
| GraphML | open standard, readable; no native queries, weak at scale |
| ArangoDB | multi-model (AQL), Apache; more config, smaller community |
| JanusGraph/TinkerPop | scales on Cassandra/HBase; "overkill for a small project" |

**Differential verification.** Wine is the oracle. The plan's instrumentation
menu: `WINEDEBUG=+all` to capture the API log; `gdb`/`lldb` attached to the
Wine process for register/memory dumps at key points; `apitrace` or RenderDoc
to capture a DirectX9 frame. Comparison metrics: entity positions, health
points, creature genomes, AI outcomes (e.g. number of tribes created); for
rendering, screenshots at defined moments with a pixel diff. Reproducibility
comes from seeded runs — a script sets the RNG seed, runs 10 game ticks under
Wine and under OpenSpore, and diffs internal variables — integrated into CI
so every PR runs the differential tests.

**The phases.** The plan's priority ladder:

| Phase | Priority |
|---|---|
| Foundation (build env, Vector3/Stream) | Very high |
| Basic simulation (cell/Protospora stage) | High |
| Creature creator | Medium |
| Creature/Tribe stage | Medium |
| Civilization stage | Low |
| Space stage | Very low |
| Rendering (Vulkan/OpenGL pipeline) | Medium, "no fixed order" |
| Expansions (GA, Creepy & Cute, Bot Parts) | Post-final, Phase 2+ |

**The legal frame.** Everything hangs on the Spanish Intellectual Property
Act, art. 100: as a legitimate user you may study a program's internal
workings; decompilation is lawful only to achieve interoperability and only
to the strictly necessary extent; copying source to create a substantially
similar program is forbidden. From that single article the plan derives the
whole constraint set: the team must legally own a copy of *Spore*; no EA
source in the repository; no proprietary assets (each developer extracts
their own from their own copy); no DRM circumvention — a DRM-free (GOG) copy
is preferred; code released under MIT (or Apache-2.0); a disclaimer in the
docs; a Contributor Covenant; and no trade secrets or leaked code, ever.

## What the plan assumed

The plan is concrete about the machine it expects, and it is concrete about
the wrong machine:

| # | Assumption in the plan |
|---|---|
| 1 | Ubuntu 22.04, `apt` for everything (`setup.sh`, `FROM ubuntu:22.04` Dockerfile) |
| 2 | Ghidra 10.3.x, NSA zip unpacked to `~/apps/ghidra` |
| 3 | winehq-stable 8/9 from the winehq deb repository |
| 4 | *Spore* installed under `wine64` and patched to v1.5.1 |
| 5 | Qwen 3.8 27B served locally via LM Studio, on a ~24-GB-VRAM GPU (RTX 3090 / 7900 XTX class) |
| 6 | Neo4j Community Edition as the knowledge-graph store |

The machine that actually got this project running was none of that. It is
CachyOS/Arch (`pacman`, not `apt`), Ghidra 12.1.2 at `/opt/ghidra`, a
pre-existing Wine 11.17, a GOG 3.1.0.22 install at `./SPORE/` (never a
1.5.1 patch), and opencode orchestrating the agent fleet against a local
llama.cpp model instead of an LM-Studio serving stack. The plan's *shape*
survived — orchestrator, agent fleet, shared graph, Wine oracle, phase
ladder, legal frame. Its specifics did not. [Chapter 001](001-repository-audit.md)
audits that divergence item by item; for now we only record that the plan was
written for a machine we did not have, and that we kept the plan's document
rather than rewriting it.

## Clean-room, as a working constraint

A legal rule that lives only in prose will be forgotten; so at bootstrap the
rules were converted into repository mechanics, enforced by tooling:

- **License.** The code is MIT (`LICENSE`, 21 lines) — the plan's "MIT or
  Apache-2.0" resolved to MIT.
- **`.gitignore` as a legal boundary.** It excludes `SPORE/` and every asset
  pattern the game uses — `*.package`, `*.gmd`, `*.bmdl`, `*.bgeo`,
  `*.manifest` — plus the runtime DLLs (`msvcr*.dll`, `steam_api.dll`,
  `goggame-*.dll`) and all trace/log output (`*.log`, `spore_log.txt`,
  `*.out`). Proprietary bytes and differential-test output cannot reach git
  by accident.
- **README warning box.** "This project is for research purposes only. It
  does not contain, build, or distribute any proprietary *Spore* code,
  assets... You must legally own a copy... Reverse engineering is limited to
  interoperability analysis under applicable law."
- **CONTRIBUTING legal & ethics.** No proprietary assets or code; clean-room
  only; no DRM circumvention (use GOG); no trade secrets/leaked code; report
  anything that looks like leaked material.
- **AGENTS.md hard rules** — the same set, aimed at the agents themselves —
  plus the most pointed override of the plan: the knowledge-graph
  architecture section reads "Analysis graph = Ghidra (via MCP); source graph
  = codegraph (MCP); shared memory = SQLite at `knowledgegraph/spore.db`...
  No Neo4j / no general graph DB." The plan's Neo4j decision was reversed
  before the first commit, and the "do NOT reinvent" rule freezes that
  reversal so no future agent resurrects a server.
- **Reference material stays reference.** The Spore-ModAPI SDK and
  SporeModder-FX are GPL; they are used for semantics only — symbol and
  structure names — never for code (the full license landscape is catalogued
  in [chapter 003](003-renderware-research.md)).

The sidecar that replaces Neo4j is small: `knowledgegraph/schema.sql` (41
lines) defines `node` (label, name, attrs, `confidence` 0..1,
`origin: static|dynamic|sdk|llm|manual`), `edge`, and test outcomes;
`kg.py` (171 lines) is a stdlib CLI over it. The plan's "validated? /
origin" node attributes survive — just in a single committable file instead
of a Java server.

The first commit, `f6f850d` (2026-09-20 13:37, *"Add AGENTS.md and STATE.md
for project guidelines and status"*), is the entire scaffolding — 13 files,
931 insertions, nothing else:

| File | Lines (at commit) | Role |
|---|---|---|
| `OpenSpore.md` | 331 | The plan itself, committed as the record of intent |
| `README.md` | 65 | What this is + legal warning box |
| `CONTRIBUTING.md` | 60 | Legal & ethics, Arch toolchain, workflow |
| `AGENTS.md` | 49 | Hard rules, KG architecture, environment |
| `LICENSE` | 21 | MIT |
| `CODE_OF_CONDUCT.md` | 15 | Contributor Covenant |
| `.github/ISSUE_TEMPLATE.md` | 18 | Plan's template, verbatim in spirit |
| `.github/PULL_REQUEST_TEMPLATE.md` | 13 | Plan's template, verbatim in spirit |
| `.gitignore` | 49 | Legal boundary (above) |
| `docs/STATE.md` | 67 | Phase 0 status + environment table |
| `knowledgegraph/kg.py` | 171 | SQLite sidecar CLI |
| `knowledgegraph/schema.sql` | 41 | node / edge / test schema |
| `opencode.json` | 31 | Wires the `codegraph` + `ghidra` MCP servers |

`docs/STATE.md` at that commit declares Phase 0 (environment + tooling)
COMPLETE and tables the machine — 12 rows, all confirmed: Ghidra 12.1.2 at
`/opt/ghidra` (profile `ghidra_12.1.2_DEV`), Java 21, Maven, Wine 11.17,
radare2 6.2, gdb/lldb, CMake/Clang/GCC, SDL3 3.4.16, Vulkan (radeon),
Python + `uv`, codegraph 1.6.0, ghidra-mcp 7.0.0. It also logs two known
issues that become later chapters' material: `ImportSporeSDK.java` aborts on
the first non-function address, and the GOG digital build needs
`SporeGhidra_march2017.xml`, not the disk XML.

## Why a journal

The decision recorded here, before any code exists: keep a chronological
development journal under `docs/devlog/`, one chapter per workstream, with
real values — addresses, counts, timestamps, commit SHAs — and with failures
kept visible instead of edited out. The point is that a reader arriving years
later should be able to follow *how* this project got from a 331-line plan
written for Ubuntu and Neo4j to an independent reimplementation, including
every assumption that did not survive contact with the actual machine.

### Outcome

| | |
|---|---|
| **Proven** | Repository born in a single commit (`f6f850d`, 2026-09-20 13:37; 13 files, 931 insertions). Legal frame codified as repository mechanics (MIT, asset-excluding `.gitignore`, README/CONTRIBUTING/AGENTS warnings). Plan committed verbatim as the record of intent. Phase 0 environment tabled in `docs/STATE.md` (12/12 tools). |
| **Open** | Every plan assumption about the environment untested as a working stack; no code, no systematic analysis, no assets parsed yet. Six of the plan's six concrete specifics (distro, Ghidra version, Wine source, game version, LLM serving, graph store) already diverge from reality — audited in [chapter 001](001-repository-audit.md). |
