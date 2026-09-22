# SCALABILITY — what breaks as the evidence base grows from 96 nodes to 58,757 functions

Subagent 2 deliverable (2026-09-22). Scope: the RE-intelligence stack of
`docs/RE-WORKFLOW.md` (dossier → static Ghidra → runtime observatory → asset
correlation → contract+fixtures → replace → record) measured against the real
binary inventory of `SPORE/SporeBin/SporeApp.exe` (GOG 3.1.0.22, PE32 i386,
20.4 MB, image base `0x400000` — `docs/RECON-3.1.0.22.md`).

Grounding rule used throughout: every claim cites the file that proves it.
Counts re-queried 2026-09-22 from `knowledgegraph/spore.db` and the committed
artifacts, not from memory.

---

## Q1 — Baseline: what "96 nodes" actually is

Measured today:

| artifact | size | home | durable? |
|---|---|---|---|
| KG (`spore.db`: 96 nodes / 115 edges / 14 test rows) | 80 KB | git-ignored `knowledgegraph/spore.db` (`.gitignore` `*.db`) | no — rebuilt by `knowledgegraph/seed_sprint.py` |
| vtable scan (`docs/analysis/vtables.json`: 3081 candidates, 16107 clusters, 12 chains, 20 labels; meta: 58,756 functions, 4,618,029 instructions scanned) | 5.6 MB | committed | yes |
| Ghidra snapshot (`tools/re/data/ghidra_snapshot_cell_movement.json`) | per-topic JSON | committed | yes (capture is manual — see Q3) |
| decompiled captures (`tools/re/data/decompiled/`) | 2 files | committed | yes |
| dossiers (`docs/analysis/dossiers/cell-movement.{md,json}`) | ~2 topics | committed | yes |
| fixtures (`tests/fixtures/cell/fixtures.json`: 5 scenarios, contract `cell-sim-contract/1`, 42 floats) | 53 KB | committed | yes (frozen, Q10) |
| replacement status (`docs/replacement-status.json`: 18 subsystems, 9-level vocabulary) | machine-readable | committed | yes |
| runtime traces | up to ~410 KB JSONL | `/tmp/openspore-observatory` + 2 committed examples in `tools/observatory/examples/` | **no** (Q9) |
| Ghidra project (symbols, SDK import 1670/1671 named, vtable labels) | — | `~/ghidra-spore-project` (outside repo) | **no** — reproducible only via the import command in `docs/RECON-3.1.0.22.md` §11 |

The binary contains **58,757 functions** (`vtables.json` meta; `docs/RECON-3.1.0.22.md` §9.2: 54,666 unnamed `FUN_*` + ~4,091 SDK-named; `docs/STATE.md` §2: 1670/1671 named by `tools/ghidra/ImportSporeSDK.java`). Today's KG covers 19 Function nodes (19 of 96). The question is what happens as that number becomes 10², 10⁴, 10⁵.

---

## Q2 — Per-function investigation state: there is none

A "function under investigation" today is a **set of scattered facts**, not a record. The same function appears, independently, as:

- a symbol in the Ghidra project (outside the repo),
- a probe entry with byte-verified RVA in `tools/observatory/probes/cell_movement.json`,
- a hand-picked address in a snapshot JSON (`tools/re/data/ghidra_snapshot_cell_movement.json`),
- a decompiled capture filename (`tools/re/data/decompiled/MovePlayerToMousePosition.c`),
- a `Function` node in `spore.db`,
- a section of a dossier (`docs/analysis/dossiers/cell-movement.md`).

None of these records *why* the function is being investigated, what was already tried, what gates it, or that the work is done. Consequences at scale:

1. **Re-investigation.** Nothing stops a future session from re-decompiling `FUN_00e82130` (camera-mode read, `REPLACEMENT-ABI.md` §4.4) from scratch. The only "done" marker is prose in `docs/STATE.md`.
2. **No dedup key in the repo.** The de-facto key is the Ghidra symbol, which lives outside the repo and is not reproducible from it alone.
3. **No queue.** `docs/STATE.md` §6 names the next milestone by human reading. At 10k functions there is no "what to look at next" computation.

**Required shape:** an investigation record per function —
`(addr, name, why_interesting, status[open|blocked|done], gate, evidence_refs[], last_reviewed)` — seeded from the SDK function list (1670 addresses, `ImportSporeSDK.java`) and growable from probe/snapshot membership. The 18 `Subsystem` entries in `docs/replacement-status.json` are the only existing "work item" records and they stop at subsystem granularity.

---

## Q3 — Provenance and staleness: the one script that is missing

The snapshot's own `source` field reads:

> "…Generated via GhidraMCP 7.0.0 REST. **See `tools/re/ghidra_snapshot.py` for regeneration.**"

**That file does not exist** (verified: `tools/re/` contains only `dossier.py` + `data/`). The snapshot is a manual MCP session. Nothing in it records the binary's sha256, the capture timestamp, the Ghidra project state, or the function list used. The only binary-drift detection in the whole pipeline is the probe byte-check at `file_off = linked − 0x400C00` (`docs/replacement-boundaries.md` §3) — and that only covers the 12 cell probes.

This matters because drift is imminent: the EP1 binary (24.9 MB, `docs/RECON-3.1.0.22.md` §9.6) is explicitly in scope, and `tools/replace/synthetic`-style hooks are keyed to file offsets of the 3.1.0.22 build. Pointing any capture at a different build silently invalidates every `VERIFIED`/`CONFIRMED` label that rests on it.

Decompiled captures are marginally better — `tools/re/data/decompiled/MovePlayerToMousePosition.c` header names the Ghidra version and build, but carries no hash.

**Must persist:** (a) a committed capture script that emits snapshot + decompiled captures with a manifest `{binary_sha256, build_version, image_base, function_list, tool_versions, captured_at}`; (b) every dossier's `sources[]` (Q5) upgraded from file paths to hash-pinned paths.

---

## Q4 — The knowledge graph at 100k nodes

SQLite and the schema (`knowledgegraph/schema.sql`: `UNIQUE(label,name)`, upsert in `kg.py`) handle 100k+ nodes in a few MB; the storage is not the bottleneck. What breaks:

1. **The seed is a hand-written literal.** `knowledgegraph/seed_sprint.py` embeds ~70 nodes/70 edges as Python list literals, maintained in sync with `docs/replacement-status.json` by editing source. At 100k nodes the seed must be *generated* from records (Q2, Q8), not written.
2. **Node names are a collision minefield.** The same function can be addressed as SDK name (`App::cAppSystem::Init`), `obs:main_menu:Init`, address-derived, or `sub:*`-style. `UNIQUE(label,name)` merges silently; `seed_sprint.py` even relies on "names are globally unique by construction" (line 367 comment). At scale, two traces that both name a probe by SDK name become one node.
3. **One `confidence` REAL per node** cannot express the mixed-evidence reality that the ABI doc handles field-by-field: `REPLACEMENT-ABI.md` §2 has field *addresses* VERIFIED and field *meanings* INFERRED on the same struct. The node-level scalar forces a lossy average.
4. **No timestamps.** `schema.sql` has no created/updated column; staleness of any node is invisible (Q3).
5. **The graph is not in the repo.** `.gitignore` excludes `*.db`; a fresh checkout has no graph until `seed_sprint.py` runs. `docs/KNOWLEDGE-GRAPH.md`'s "shared memory" is shared per-machine only.

---

## Q5 — The dossier as the work unit

`tools/re/dossier.py` is the right unit (one topic → one MD + one JSON, `tests/test_dossier.py` pins the contract) and its failure mode is honest: missing inputs degrade to explicit `NOT OBTAINED` (e.g. `cell-movement.json` `runtime: {obtained: false, reason: "No cell-mode trace was recorded…"}`).

Gaps that bite at 100 dossiers:

- `sources[]` lists file paths, not hashes (Q3) — so a dossier cannot prove its inputs haven't moved.
- No capture timestamp, no binary identity in the JSON.
- No index: `docs/analysis/dossiers/` is a directory; cross-dossier references are prose (e.g. `src/sim/tests/contract_scenarios.hpp` line 93 citing "docs/analysis/dossiers/cell-movement.md resource refs").
- The 7-level evidence vocab (`docs/RE-DOSSIER-SCHEMA.md`) is applied per-claim in free text — fine at 2 topics, un-auditable at 100 without a machine-readable claim table.

---

## Q6 — Confidence modeling: three overlapping scales

Three vocabularies coexist with **no mechanical mapping**:

| scale | levels | home |
|---|---|---|
| KG numeric | UNKNOWN 0.0 / HYPOTHESIS 0.25 / INFERRED 0.5 / SUPPORTED 0.75 / VERIFIED 1.0 | `knowledgegraph/seed_sprint.py` `CONF`, `STATUS2EV` |
| dossier | OBSERVED / VERIFIED / CONFIRMED / SUPPORTED / INFERRED / APPROXIMATION / UNKNOWN (7) | `docs/RE-DOSSIER-SCHEMA.md` |
| replacement status | unknown…replaced-verified (9) | `docs/replacement-status.json` `vocabulary` |

The collision is not cosmetic: **APPROXIMATION exists in no KG scale.** The movement-plane constants (`DAT_015a7c40/44/48`, `DAT_016b3c28/2c/30` — "addresses VERIFIED, values never read", `REPLACEMENT-ABI.md` §2) must be recorded as UNKNOWN 0.0 (understates: the addresses *are* known) or INFERRED 0.5 (overstates: the values are *assumed*). `VERIFIED` itself means three different things across `docs/RECON-3.1.0.22.md` appendix A, `seed_sprint.py`'s header, and the dossier schema.

At every scale step (Q11) a consumer must translate between these; today the translation lives in comments and prose. **Must persist:** one canonical scale + the mapping table *in code* (it already exists as the `STATUS2EV` dict — generalize it, don't fork it again).

---

## Q7 — Dependency ordering: gates exist, ordering is human

Gates are declared in three places and agree by hand: the "done" table in `docs/BOUNDARIES.md`, `docs/replacement-status.json` entries, and `docs/replacement-boundaries.md` §3 (e.g. `cell-movement-mouse-steering` → `replaced-verified` needs "a Wine cell-mode trace that (a) byte-reads the plane constants and (b) confirms the sCellGame field offsets").

The KG already encodes some of it (`gatedBy`, `verifiedBy` edges in `seed_sprint.py`). What's missing is a **machine-readable gate table**: `{gate, unlock_artifact, cost[cheap|medium|operator-blocked], depends_on[]}`. The single highest-leverage fact in the repo is that one artifact — a cell-mode trace — unlocks ≥4 subsystems (`replacement-boundaries.md` §3 lists `cell-movement-mouse-steering`, `resource-manager-full`, `utfwin-message-dispatch`, `simulator-gameplay` all as runtime-blocked). That fact is currently prose in two documents. At 100 subsystems, "next action = open gate with cheapest unlock" must be computed from a table, not read from `docs/STATE.md` §6.

---

## Q8 — Replacement-target state: the per-target record

For the one existing target, the state is spread across **five artifacts**: `docs/REPLACEMENT-ABI.md` (target: symbol/VA/file-offset/entry-bytes; §2–§3 field tables with per-field evidence labels; §4 behavioral contract; §5 replacement contract), `tools/re/data/decompiled/MovePlayerToMousePosition.c`, `src/replace/CellGameView.hpp` (the field table re-projected as POD structs in code), `docs/REPLACEMENT-DIFF.md` (64 comparisons), and the `replacement-status.json` entry.

The load-bearing piece is the **per-field evidence label** (§2: `+0x5158` lock flag INFERRED; plane values APPROXIMATION). A target is promotable `replaced-approx → replaced-verified` exactly when every compared field's label reaches VERIFIED via trace — and that promotion rule is prose (`replacement-boundaries.md` §5.7: "Status is `replaced-approx` until the live trace of §3 lands — never `replaced-verified` on a decompilation reference alone").

At 100+ targets, five prose documents per target don't scale, and the code/doc split (`CellGameView.hpp` vs `REPLACEMENT-ABI.md` §2–§3) drifts silently. **Must persist:** one per-target record `{va, hook_boundary_bytes, fields[{offset, role, evidence}], contract_version, diff_summary{cases, fields, mismatches}, status, gate}` — the ABI doc and the POD view *generated from* it.

---

## Q9 — Ghidra at scale: the headless wall and the batch unit

Verified constraints:

- Headless GhidraMCP **cannot open programs** — `docs/STATE.md` §5: "Headless GhidraMCP cannot open programs (needs GUI mode) → RVA cross-checks done via `objdump`/byte inspection instead." Per-function decompilation is a GUI-mode session.
- The full-binary passes are the good pattern: `tools/ghidra/VtableDetect.java` (committed, defensive, one-shot scan of 778,058 words / 4.6M instructions → one committed JSON; re-runnable via `analyzeHeadless`, `docs/RECON-3.1.0.22.md` §10) and `tools/ghidra/ImportSporeSDK.java` (defensive fork, 1670/1671).
- The project lives at `~/ghidra-spore-project` — outside the repo, reproducible only via the documented import command (`docs/RECON-3.1.0.22.md` §11).

The missing piece is the **per-topic batch**: the snapshot (Q3). It is the unit that converts "58k functions in a project outside the repo" into "N functions with decompilation in the repo." Until a capture script with a function list + binary-hash manifest exists, every new topic costs a manual MCP session, and the 10k-function stage is simply not enterable headless.

---

## Q10 — Runtime observatory: the only evidence that promotes INFERRED→VERIFIED, stored in /tmp

The observatory is the *only* path by which a label becomes VERIFIED from runtime (`seed_sprint.py` header: "Only measured bytes, passing tests, and planted-breakpoint traces count as evidence"). Its state today:

- **Probes are the durable asset**: `tools/observatory/probes/cell_movement.json` — 12 probes, each byte-verified at `file_off = linked − 0x400C00`, image base `0x400000` (`docs/replacement-boundaries.md` §3). These are committed and re-checkable against any build.
- **Traces are ephemeral**: `tools/observatory/observe.py` writes to `/tmp/openspore-observatory`; `.gitignore` excludes `tools/observatory/out/`. The 9 runs of `docs/analysis/CELL-RUNTIME-OBSERVATION.md` (8/9 boot-stalls pre-D3D; menu reached once; 0 cell-probe events) exist as prose + 2 committed example JSONLs.
- **The run is operator-blocked**: needs a real X display + `xdotool` (absent — `docs/STATE.md` §5, §6.1), with the non-obvious `wineserver -k`-first requirement (`docs/STATE.md` §4).
- `tools/observatory/analyze.py` is deterministic on a given JSONL (per-function counts/intervals/tids, 1 s-window spikes) — the summarizer side is fine.

KG observations cite the trace files by path (`seed_sprint.py` `src: "tools/observatory/examples/obs_main_menu_example.jsonl"`) — durable only for the two committed examples. **Must persist:** a committed trace archive (even the empty/failed runs — they *are* the negative evidence) plus a run manifest `{binary_sha256, probes_file_hash, display_env, wine_version, captured_at, events}`. A failed run is a first-class observation (the KG already models this: `obs:menu_transition` with 8 probes / 0 events / "never run under tracer").

---

## Q11 — Deterministic evidence: the pattern that *does* scale

`tests/fixtures/cell/fixtures.json` (53 KB: 5 scenarios × per-frame `FrameSnapshot` of pos/heading/vel/growMeter/events/alive; contract string `cell-sim-contract/1`; dt `0.0166666675`; 42 pinned floats) is frozen by double-run sha256 identity (`tools/gen_cell_fixtures.py`), and `src/sim/tests/contract_scenarios.hpp` drives **both** the emitter and `sim_contract_test` from the same `Scenario` list — identity by construction. Likewise `src/replace/tests/diff_test.cpp` (8 cases × 8 fields = 64 comparisons, tolerance 1e-6/exact, `MAP_32BIT` state buffers, `docs/REPLACEMENT-DIFF.md`).

This is the scale-safe shape: **pinned inputs + pinned expected outputs + a version string in committed files, replayed by tests.** Bumping the contract version is a deliberate semantics change. Replicate per subsystem-being-replaced; nothing about it degrades from 5 scenarios to 5,000 (the fixture file grows linearly; the test runtime is the only cost).

---

## Q12 — What breaks, at which scale, and in what order

| scale | ≈ | first to break | evidence |
|---|---|---|---|
| **~100 functions** (current: 19) | 0.03% of binary | Manual snapshot capture; per-function re-investigation | Q3 (missing script), Q2 (no records) |
| **~1,000 functions** | ~2% | Dossier proliferation (no index, path-only sources); hand-maintained seed literals; 3-scale confidence translation done in prose | Q5, Q4.1, Q6 |
| **~10,000 functions** | ~17% | Seed-as-literal impossible; node-name collisions merge silently; human gate ordering fails; per-target 5-doc spread drifts code↔doc | Q4.2, Q7, Q8 |
| **~58,757 functions** (whole binary) | 100% | Every hand-written input list (functions, probes, dossiers) must become *generated* from records; Ghidra project reproducibility (outside repo) becomes the single point of failure | Q9, Q2 |

Order of breakage is: **capture (Q3) → records (Q2) → confidence (Q6) → ordering (Q7) → graph (Q4) → dossiers (Q5)**. Fixing in that order means each step's output is the input of the next; the fixtures/contract pattern (Q11) needs no change at any scale.

---

## STATE THAT MUST PERSIST

Concrete state, its current home, and the shape it needs at scale. "Today" = where it exists now (path verified 2026-09-22).

| # | State | Today (home) | Breaks at | Required shape |
|---|---|---|---|---|
| 1 | Binary identity (sha256 + build 3.1.0.22 + image base 0x400000) | Prose only (`docs/RECON-3.1.0.22.md`, `docs/STATE.md`); probe byte-checks | 100 fns (EP1 build) | `binary_manifest.json` per build; every capture/dossier/trace references it by hash |
| 2 | Function investigation records (addr, name, why, status, gate, evidence refs, last_reviewed) | **Nowhere** — scattered across Ghidra project, probes, snapshots, dossiers (Q2) | 100 fns | Table in `spore.db` (label `Investigation`), seeded from the 1670 SDK functions |
| 3 | Ghidra snapshot capture (per topic: function list + decompilation) | Manual MCP session; `tools/re/ghidra_snapshot.py` referenced but **absent** (Q3) | 100 fns | Committed script emitting snapshot + `decompiled/*.c` with manifest {binary_sha256, tool versions, captured_at, function list} |
| 4 | Decompiled captures | `tools/re/data/decompiled/` (2 files; header names build, no hash) | 1k fns | Keep format; add manifest hash + timestamp to the header block |
| 5 | Knowledge graph content | git-ignored `spore.db` (80 KB, 96/115/14) rebuilt from **hand-written** `seed_sprint.py` literals | 10k nodes | Seed *generated* from records #2/#7/#8; `schema.sql` gains created/updated; name-collision rule documented |
| 6 | Confidence scale + mapping | 3 overlapping vocabularies (KG 5-level `seed_sprint.py` CONF; dossier 7-level `RE-DOSSIER-SCHEMA.md`; status 9-level `replacement-status.json`) | 1k fns | One canonical scale incl. APPROXIMATION; `STATUS2EV` generalized to the full mapping, in code |
| 7 | Subsystem status + gates | `docs/replacement-status.json` (18) + prose gates (`BOUNDARIES.md`, `replacement-boundaries.md` §3) | 10k fns | Add machine-readable `gate`/`unlock`/`depends_on` to each entry; "next action" computed as cheapest open gate |
| 8 | Replacement-target contracts (per-field evidence labels, hook bytes, diff summary) | 5 prose/code artifacts per target (`REPLACEMENT-ABI.md`, `CellGameView.hpp`, `REPLACEMENT-DIFF.md`, …) | 1k targets | One record per target; ABI doc + POD view **generated** from it; promotion rule (Q8) in code |
| 9 | Probe definitions (byte-verified RVAs) | `tools/observatory/probes/*.json` (12 cell probes — the pattern that works) | any scale | Keep; generate candidate lists from record #2, keep the byte-check as the drift gate |
| 10 | Runtime traces (incl. failed runs) | `/tmp/openspore-observatory` (git-ignored) + 2 committed examples | first trace | Committed `traces/` archive + run manifest {binary_sha256, probes hash, env, captured_at}; failed runs are first-class observations |
| 11 | Frozen contracts + fixtures | `tests/fixtures/cell/fixtures.json` + `contract_scenarios.hpp` + `gen_cell_fixtures.py` (Q11) | **does not break** | Replicate the pattern per subsystem; contract version string is the staleness key |
| 12 | Differential results (64 comparisons for the one target) | `docs/REPLACEMENT-DIFF.md` table | 1k targets | Per-target summary record {cases × fields, mismatches, tolerance} feeding #8 and `test_result` |

**One-line summary:** the pipeline's *methods* (dossier, probes, fixtures, diff tests) already scale; the *state* doesn't — it is hand-written prose and literals, lives in `/tmp` or outside the repo, and is not hash-pinned to the binary. The 12 rows above are the concrete persistent state that has to exist before the 1,000-function mark, in the breakage order Q12 gives.
