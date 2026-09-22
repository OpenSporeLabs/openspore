# RE-AUTOMATION-ARCHITECTURE — the OpenSpore RE evidence platform at scale

Synthesis of six analyses (2026-09-22), reconciled into one build plan:
`docs/analysis/{SCALABILITY,MCP-DESIGN,ORCHESTRATOR,SCHEMA-DELTA,VIEWER,GUI-BOUNDARY}.md`.
Design document only — nothing here is implemented. Every name, path, table, and
number below was re-verified against the committed tree on 2026-09-22
(closing commit `ef0a992`).

---

## 1. Purpose & strategic framing

This platform makes reverse-engineering **investigations** scalable in THIS repo.
It is not a general RE framework: no Neo4j, no web framework, no general
computer-use, no framework that would serve any other project. It is the
evidence pipeline of the OpenSpore clean-room reimplementation, at scale.

1. **Clean-room, always.** No proprietary Spore code/assets/decompilation in git,
   ever. The original game under Wine is a **behavior/data oracle only**
   (`SPORE/` is git-ignored; decompiled captures are EVIDENCE-NOT-TRUTH).
2. **OpenSpore is a modern, extensible successor** — x64, Vulkan, SDL3 — NOT a 1:1
   binary recreation. The reimplementation may differ in implementation as long as
   observed behavior/contracts match. Differential comparison is against *observed
   behavior*, not against the binary.
3. **One investigation = one queue item with a lifecycle.** The machine (Ghidra,
   Wine, tracer, KG, viewer) is fully scripted through one MCP surface; humans are
   in the loop **only at approval gates** (trace run, status promotion, fixture
   rebuild).
4. **Evidence discipline is the product.** Every claim carries its evidence
   (decompile text, trace run id, dossier, test id), hash-pinned, reproducible.
   The 9-level replacement-status vocabulary and the canonical 7-level evidence
   scale (§5) are the spine; promotion above `replaced-approx` requires live
   runtime evidence, never decompilation alone.
5. **The single highest-leverage blocked evidence is the cell-stage trace**
   (menu-walk + xdotool under the byte-verified `cell_movement.json` probes). It
   gates `cell-movement-mouse-steering` from `replaced-approx` to
   `replaced-verified` and unlocks ≥4 subsystems at once.
6. **Everything persistent must survive:** no git-ignored state as source of
   truth, no `/tmp` as home for records, no hand-written seed data that goes
   stale. Records are committed; caches are disposable; the KG is rebuilt from a
   committed generator.
7. **Zero new dependencies where stdlib suffices.** No `package.json` in the repo;
   Python tooling is stdlib-only and CI-safe; C++ is CMake + Clang. The `mcp` SDK
   and React were considered and rejected (MCP-DESIGN §B, VIEWER §2).
8. **Classification is mandatory** for every capability: NOW / LATER /
   EXPERIMENTAL / MANUAL / AUTONOMOUS (§10), with a one-sprint NOW set and a
   build order with verification gates (§11).

## 2. Current state

What exists and works today (all verified):

- **KG**: `knowledgegraph/spore.db` (git-ignored, 80 KB): 96 nodes / 115 edges /
  14 `test_result` rows; labels incl. Function, Subsystem, Dossier, Finding,
  Observation, AssetRecord, Contract, ReplacementTarget. Rebuilt by hand-written
  `knowledgegraph/seed_sprint.py`.
- **Dossier infra**: `tools/re/dossier.py` → `docs/analysis/dossiers/cell-movement.{md,json}`
  (`re-dossier-1`, 7-level vocab, `runtime.obtained=false` — honest gap, never
  fabricated); idempotent, pinned by `tests/test_dossier.py`.
- **Observatory**: `tools/observatory/` — ptrace `probe_tracer`, `observe.py`,
  `analyze.py` (deterministic summarizer), 3 committed probe sets
  (`cell_movement.json` 12 byte-verified probes, `main_menu.json`,
  `menu_transition.json` defined-but-never-run), 2 committed example JSONLs.
- **Headless GhidraMCP**: up at `127.0.0.1:8089`, `SporeApp.exe` open
  (59,245 functions, image base `0x00400000`, PE32 i386, GOG 3.1.0.22);
  decompiles the open program via REST (`/decompile_function` verified).
  SDK import named 1670/1671 functions; `vtables.json` 5.6 MB / 3,081 candidates.
- **sporemol**: `tools/spore/` — 7 stdlib modules (dbpf, rw4, gmdl, raster, dxt5,
  typescan, asset_resolver + type/group name tables); metadata-only.
- **Contract + fixtures**: `docs/CELL-CONTRACT.md` (`cell-sim-contract/1`) +
  `tests/fixtures/cell/fixtures.json` (5 scenarios, 42 floats) frozen by
  double-run byte identity; `replace_diff_test` 64/64 MATCH.
- **Scripts-as-MCP-candidates**: kg.py, dossier.py, asset_resolver.py,
  analyze.py, observe.py, gen_cell_fixtures.py, ctest — the 21-tool MCP surface
  is a thin facade over exactly these.
- **Status board**: `docs/replacement-status.json` — 18 subsystems, 9-level
  vocabulary; only `cell-movement-mouse-steering` at `replaced-approx`.
- **Tests**: 10 ctest + Python `unittest` suites (CI-safe, no wine/SPORE/ needed);
  14 KG `test_result` rows.
- **The 9-run cell observation record** (`docs/analysis/CELL-RUNTIME-OBSERVATION.md`):
  8/9 Wine boots stalled pre-D3D (`ntsync_schedule`), 1 run reached the menu
  (227 events, all the generic `FUN_0069b600` 30 Hz loop), **0 cell-stage probe
  events in all 9 runs** — the stable negative result that is itself committed
  evidence.

The 4 structural weaknesses:

1. **Hand-written state as source of truth.** `seed_sprint.py` embeds ~70 nodes /
   ~70 edges / 14 tests as Python list literals; traces live in
   `/tmp/openspore-observatory`; the snapshot was a manual MCP session.
2. **`tools/re/ghidra_snapshot.py` does not exist** — the snapshot's own `source`
   field references it; `tools/re/` contains only `dossier.py` + `data/`.
3. **Three overlapping confidence scales** with no mechanical mapping (KG 5-level
   `CONF`/`STATUS2EV`; dossier 7-level; status 9-level); `APPROXIMATION` exists in
   no KG scale; `STATUS2EV` is stale (7 keys, `KeyError` on the current status file).
4. **No queue.** "What to investigate next" is prose in STATE.md §6; nothing
   prevents re-investigating a done function; there is no dedup key in the repo.

## 3. Architecture overview

```
                        +----------------------------------------------------------+
                        |  opencode (orchestrator) — the ONLY process that writes  |
                        |  queue rows, spawns ONE worker at a time, runs gates     |
                        +----------------------------------+-----------------------+
                                                           | stdio (JSON-RPC 2.0)
                     +-------------------------------------v----------------------
                     | tools/mcp/server.py  (stdlib, ~300 LOC protocol surface)    |
                     | 21 tools: pipeline_state target_select kg_query kg_neighbors |
                     | kg_record dossier_read dossier_regenerate ghidra_decompile  |
                     | ghidra_function ghidra_search ghidra_snapshot_save          |
                     | asset_resolve asset_scan vtable_lookup trace_run*           |
                     | trace_analyze trace_status test_run status_update*          |
                     | fixture_check* queue_op   (* = HUMAN approval-gated)        |
                     +-----+------------------+------------------+-----------------+
                           |                  |                  |
              REST http    |        sqlite3    |        subprocess|
        +------------------v--------+   +------v-----------+  +---v------------------+
        | GhidraMCP headless :8089  |   | knowledgegraph/  |  | ctest / observe.py / |
        | (SporeApp.exe open;       |   | spore.db (WAL,   |  | dossier.py /         |
        |  decompile/search/...)    |   |  git-ignored,    |  | gen_cell_fixtures.py |
        | GUI wall = importing NEW  |   |  rebuilt by seed |  | (machine lock flock) |
        | binaries only (W2)        |   |  generator)      |  | + xdotool menu-walk  |
        +---------------------------+   +------------------+  +----------------------+
                                              |
              +--------------------------------+---------------------------------+
              | read-only mirror (separate process, sqlite3 mode=ro)             |
              | tools/viewer/server.py — http.server, 127.0.0.1:8787, 11 views  |
              +------------------------------------------------------------------+
```

Single source of truth rules:

1. **`spore.db` is the one shared store** for cross-tool results (KG nodes/edges,
   `field`, `trace_run`, `test_result`, and the `investigations` queue). It is
   git-ignored but **rebuildable from committed generator + inputs** — never
   hand-edited.
2. **Committed artifacts are the durable evidence**: dossiers, snapshots,
   `decompiled/*.c`, contracts + fixtures, ABI/DIFF docs, `replacement-status.json`,
   trace manifests + committed example JSONLs/keyframe shots. `/tmp` and
   `tools/mcp/cache/` and `tools/observatory/out/` are disposable.
3. **`binary_sha256` of `SPORE/SporeBin/SporeApp.exe`** is computed once per
   session and pinned into every capture manifest, trace manifest, queue row, and
   build-sensitive node. A build flip (EP1) auto-invalidates caches and flags
   stale queue rows.
4. **Writers are separated from readers.** The MCP server is the only process that
   writes the KG; the viewer opens it `mode=ro` per request and cannot write by
   construction. The viewer never calls the MCP server.
5. **The queue and the KG are split by purpose** (SCHEMA-DELTA verdict): durable
   conclusions live in node/edge/field/test_result; mutable work state (stage,
   attempts, checkpoint, block_reason, implementer/adjudicator ids) lives in
   `investigations`. Bridge: queue `id` ↔ KG node names.

## 4. MCP tool surface

Hand-rolled **JSON-RPC 2.0 over stdio** (MCP 2025-06-19) in
`tools/mcp/server.py` — `initialize`/`tools/list`/`tools/call`/`ping`,
line-delimited JSON on stdio, logs on stderr, ≈300 LOC in `json` + `subprocess` +
`http.client` + `sqlite3`. The `mcp` SDK (pydantic venv) was considered and
rejected: it breaks the stdlib/CI-safe invariant and needs network to build; the
registry is transport-agnostic if a later migration is forced. Registered in
`opencode.json` as `{"openspore":{"type":"local","command":["python3",
"tools/mcp/server.py"],"enabled":true}}` (the `ghidra` entry stays). Env:
`OPENSPORE_ROOT` (default cwd), `OPENSPORE_GHIDRA` (default `http://127.0.0.1:8089`).

Layout: `server.py`, `registry.py` (21 schemas + handler table), `ghidra_client.py`,
`cache.py`, `safety.py`, `config.py`; test `tests/mcp/test_server.py`.

| # | Tool | Class | Gate | Notes |
|---|------|-------|------|-------|
| 1 | `pipeline_state` | read | – | one "where are we"; always embeds `binary_sha256` |
| 2 | `target_select` | read | – | ranks uninvestigated targets; built-in dedup (never returns a target with an existing queue row/dossier at VERIFIED) |
| 3 | `kg_query` | read | – | label / name-substring / evidence filters |
| 4 | `kg_neighbors` | read | – | depth 1–2 |
| 5 | `kg_record` | write (git-ignored DB) | – | batch nodes+edges+test rows; needs `reason`; never writes status |
| 6 | `dossier_read` | read | – | missing topic → structured error listing topics |
| 7 | `dossier_regenerate` | write (deterministic) | – | byte-identical on re-run; returns unchanged/changed/created |
| 8 | `ghidra_decompile` | read | – | REST `/decompile_function`; **disk-cached** §D; `force=true` bypass |
| 9 | `ghidra_function` | read | – | metadata card: name/size/namespace/callers/callees + vtables.json join; memoized |
| 10 | `ghidra_search` | read | – | name-pattern search |
| 11 | `ghidra_snapshot_save` | write (deterministic) | – | THE capture script AGENTS.md says is missing; emits `ghidra_snapshot_<topic>.json` + `decompiled/*.c`, manifest pins `binary_sha256` |
| 12 | `asset_resolve` | read | – | metadata only — never payload bytes (clean-room) |
| 13 | `asset_scan` | read | – | package inventory / type histogram |
| 14 | `vtable_lookup` | read | – | vtables.json (3,081 candidates stay in the JSON — not bulk-imported) |
| 15 | `trace_run` | runtime | **HUMAN** | preconditions checked first (wineserver -k, display, xdotool); menu-walk precondition phase; ~30 s+ |
| 16 | `trace_analyze` | read | – | deterministic per-trace summary |
| 17 | `trace_status` | read | – | runs + manifests + fired/missed probes |
| 18 | `test_run` | validate | – | ctest subset; never cached — fresh measurement |
| 19 | `status_update` | write (committed) | **HUMAN** | the ONLY writer of `docs/replacement-status.json`; evidence pointer + 9-level vocab + evidence cap enforced server-side |
| 20 | `fixture_check` | validate | **HUMAN** if `rebuild=true` | identity mode never gated; rebuild requires double-run byte identity |
| 21 | `queue_op` | write (git-ignored DB) | – | `{op: list\|get\|insert\|update\|close}` over `investigations` (kg.py pattern; ORCHESTRATOR NEW item 2 — the 20-tool surface had no queue writer) |

Exactly **3 human-gated writes**: `trace_run`, `status_update`,
`fixture_check(rebuild=true)`. Gate mechanics: first call returns
`{"ok":false,"error":"approval_required","what":...,"cost":...,"requires":"human
approval"}`; the re-call with `approve=true` is valid **only** under
`OPENSPORE_MCP_TRUSTED=1` (default off) — a misconfigured session cannot
self-approve, and workers are never issued `approve=true` at all (only the
orchestrator, as the human's decision).

**Decompilation cache** (`cache.py`): key `(binary_sha256, rva, ghidra_version,
program_name)` → `tools/mcp/cache/decompiled/<binary12>/<rva>.c` + `.meta.json`.
Git-ignored; a lost cache is a cost, never evidence loss. Never cached:
`trace_run` (fresh measurement), `test_run`, `fixture_check`.

**Failure contract (uniform):** every result is `{"ok":true,...}` or
`{"ok":false,"error":"<code>","hint":...}`; codes `ghidra_offline`, `no_spo`
(degrade, never fail), `approval_required`, `machine_locked` (NEW, §6),
`not_implemented_gate`.

**CI-safety**: `tests/mcp/test_server.py` (stdlib unittest) spawns the server and
speaks the protocol over pipes — handshake, `tools/list` (21, schemas valid via a
40-LOC subset checker), pure tools end-to-end on committed data (incl. `no_spo`
degradation), `ghidra_decompile` against an in-test fake REST thread
(first call upstream, second a cache hit with no upstream request), gate
refusals without `OPENSPORE_MCP_TRUSTED`, garbage-line hygiene. No wine, no
SPORE/, no display, no network beyond loopback.

## 5. KG: target schema

Incremental delta on `knowledgegraph/schema.sql` (41 lines, 4 tables) — nothing
redesigned, nothing dropped; `kg.py` gains a `_migrate()` (PRAGMA-guarded
`ALTER TABLE`/`CREATE ... IF NOT EXISTS`, additive, re-runnable) so the live 80 KB
DB and fresh DBs converge on the same DDL.

- **`node` gains**: `evidence_level TEXT NOT NULL DEFAULT 'UNKNOWN'` (CHECK, 7-level),
  `updated_at` (upsert writes it; `created_at` stays = first-seen),
  `binary_sha256` (NULL = build-agnostic). `confidence REAL` stays as **derived
  display only** — `evidence_level` is the source of truth.
- **New table `field`** (the load-bearing delta): per-struct-field rows
  `(struct_id→node, offset, role, offset_evidence, meaning_evidence, value, source,
  binary_sha256)` — two 7-level evidence axes so "offset VERIFIED + meaning
  INFERRED on the same struct" is expressible. `UNIQUE(struct_id, offset)`.
  **Promotion rule becomes a column query**: a target is promotable
  `replaced-approx → replaced-verified` iff every `field` row's
  `offset_evidence` AND `meaning_evidence` ≥ `OBSERVED`.
- **New table `trace_run`**: 1 row per run
  `(binary_sha256, probes_sha256, wine_version, display_env, xdotool, captured_at,
  events_total, jsonl_path, screenshots{count,first,last,manifest_path}, outcome,
  replayable="input-logged, stage-deterministic, non-bit-exact")`; Observations
  back-reference via `run_id` attr.
- **New table `investigations`** — verbatim from ORCHESTRATOR §1 (see §6; the
  SCHEMA-DELTA §2.4 draft drifted from it — resolved in favor of ORCH, conflicts §C).
- **New labels** (closed enum; free prose in `label` is the data bug behind the 3
  mislabeled AssetRecord rows and is forbidden): `Class`, `Hypothesis`
  `{claim, evidence_refs, evidence_level, status∈ACTIVE|SUPERSEDED|REJECTED,
  asserted_by}`, `Adjudication` (I4 record: `origin` ≠ implementer).
  Generated import of the 306 SDK classes + 12 inheritance chains from
  `vtables.json`; the 3,081 candidates stay in the JSON.
- **New rels**: `memberOf` (Function→Class), `depends_on`. All 30 existing rels
  and 16 labels kept.
- **Indexes**: `idx_node_name`, `idx_node_evidence`, `idx_inv_status`,
  `idx_inv_dedup` (= the UNIQUE), `idx_field_struct`, `idx_trace_run_sha`.
  Adequacy at 100k: ~20 MB WAL; hot queries O(log n); infix `LIKE` is a bounded
  full scan <10 ms — no FTS needed.

**THE canonical 7-level evidence scale** (SCHEMA-DELTA decision: the dossier
vocabulary is the one scale; the other two are deprecated/mapped):

```python
# knowledgegraph/scale.py — single source of truth
EV = {  # level → confidence REAL (display only)
  "UNKNOWN":       0.0,
  "APPROXIMATION": 0.3,   # best-effort stand-in value
  "INFERRED":      0.5,   # reasoned, single source (absorbs old HYPOTHESIS 0.25)
  "SUPPORTED":     0.75,  # multiple consistent sources
  "OBSERVED":      0.85,  # byte-level / runtime evidence
  "CONFIRMED":     0.9,   # OBSERVED + independently corroborated
  "VERIFIED":      1.0,   # reproduced / differential / green test
}
```

Map A — 9-level replacement status → 7-level (generalized `STATUS2EV`, fixing the
stale 7-key dict that `KeyError`s on the current file):

```python
STATUS2EV = {"unknown":"UNKNOWN", "hypothesis":"INFERRED", "inferred":"INFERRED",
             "supported":"SUPPORTED", "verified":"VERIFIED",
             "approximated":"APPROXIMATION",     # ← was missing
             "replaced-stub":"SUPPORTED",
             "replaced-approx":"APPROXIMATION",  # ← was missing
             "replaced-verified":"VERIFIED"}
```

Map B — legacy 5-level KG strings → 7-level, read-only back-compat
(`HYPOTHESIS→INFERRED`, rest identity). New writes always use 7-level.

**Naming rule** (global uniqueness by construction; forward-only, the existing 96
names stay): `name = kind-prefix + stable key` — `fun:<va-8hex>` (image-base-
relative VA — the dedup key, names drift so VA+build is identity), `cls:<Name>`,
`struct:<Name>`, `asset:<type>:<group>:<instance>`, `sub:<name>`, `impl:<path>`,
`test:<name>`, `obs:<trace>:<probe>`, `dossier:<topic>`, `contract:<version>`,
`replace:<Symbol>`, `finding:<topic>:<slug>`, `hyp:<topic>:<slug>`,
`adj:<topic>:<build-short>`. SDK names are `attrs.sdk_name`, never IDs.

**Seed generator** (replaces `seed_sprint.py` literals; SCALABILITY row #5): emits
SQL via `kg.py` upserts from committed inputs — `seed-literals.json` (today's
96/115/14 extracted verbatim), `replacement-status.json` (18 subsystems +
`attrs.gate`), SDK import (1,670 `fun:<va>` functions + `investigations` rows),
dossier JSONs, `vtables.json` (306 classes + 12 chains only),
`REPLACEMENT-ABI.md` field tables (→ `field` rows), committed trace manifests.
Invariants pinned by test: byte-deterministic (sorted emit), idempotent,
reproduces 96/115/14 from `seed-literals.json` alone, every `evidence_level`
derived through §3 (no hand-typed confidence), all 9 statuses map without
`KeyError`.

## 6. Orchestrator & investigation lifecycle

**Queue**: `investigations` table in `spore.db` (dedicated table, not a node label —
it needs per-stage attempt counters + a checkpoint blob that must not flow through
the idempotent evidence-graph upsert). Canonical DDL (ORCHESTRATOR §1; conflicts
resolved in §C of the synthesis notes):

```sql
CREATE TABLE IF NOT EXISTS investigations (
  id             TEXT PRIMARY KEY,  -- 'fn:0x00e5b790:MovePlayerToMousePosition' | 'sub:resource-manager-full'
  kind           TEXT NOT NULL,     -- 'function' | 'subsystem'
  va             TEXT, name         TEXT, subsystem     TEXT,
  mode           TEXT NOT NULL,     -- 'replace' | 'understand'
  why_interesting TEXT NOT NULL,
  stage          TEXT NOT NULL,     -- §2 vocabulary; QUEUED when status='queued'
  status         TEXT NOT NULL,     -- 'queued'|'active'|'blocked'|'done'|'dropped'
  block_reason   TEXT,              -- 'approval_required:<tool>'|'escalated'|'ghidra_offline'|'no_spo'|'machine_locked'
  prerequisites  TEXT,              -- JSON: [task ids / gate keys]
  attempts       TEXT,              -- JSON {stage: count} — per-stage cap 3
  checkpoint     TEXT,              -- JSON §below
  evidence_refs  TEXT,              -- JSON [artifact paths + KG node names]
  implementer_id TEXT, adjudicator_id TEXT,
  created_at TEXT, updated_at TEXT,
  binary_sha256 TEXT NOT NULL
);
CREATE UNIQUE INDEX IF NOT EXISTS ix_inv_dedup ON investigations(kind, va, binary_sha256);
```

Invariants: one record per function per build; at most ONE row `active`
(re-checked at startup); only the orchestrator inserts (workers propose, §dedup);
`binary_sha256` ≠ current build ⇒ row **stale** — parked `queued`, never dropped
(dossier/snapshot must regenerate against the new build first; caches miss
automatically); `done`/`dropped` rows are never deleted — they are the dedup
memory. Seed: 1,670 SDK functions + 18 subsystems; the one completed case
(cell-movement) seeds `status='done', stage='RECORDED'`.

**The 9 legal stage edges (main path, in order):**

```
 1. QUEUED→SELECTED       orchestrator pick; deps done, binary match, not stale
 2. SELECTED→DOSSIER      dedup re-check passed
 3. DOSSIER→STATIC        dossier artifact written
 4. STATIC→RUNTIME        snapshot+decompiled committed; runtime gate present
 5. RUNTIME→ASSETS        manifest+analysis+Observation recorded (negative ok)
 6. ASSETS→CONTRACT       asset section resolved/rejected
 7. CONTRACT→REPLACE      contract+fixtures; dossier ∧ snapshot in evidence_refs
 8. REPLACE→VALIDATE      diff doc + impl + reference committed
 9. VALIDATE→RECORDED     adjudication by ≠implementer + status_update executed
```

Plus the legal off-path edges (all from ORCHESTRATOR §2; any other edge is
forbidden): `DOSSIER→RECORDED` (understand-only), `STATIC→ASSETS` (skip, only if
no runtime gate AND no existing trace covers the probes — a FAILED run does NOT
leave RUNTIME open: the negative result is recorded evidence), `RUNTIME→BLOCKED` /
`VALIDATE→BLOCKED` / `<stage>→BLOCKED` (approval / cap / `machine_locked` /
`no_spo` / `ghidra_offline`), `BLOCKED→<stage>` (human resolved; attempt counter
resets only on human escalation resolution), `<stage>→DROPPED` (explicit user
decision; record kept), `RECORDED`→terminal. No path reaches REPLACE without
DOSSIER+STATIC+CONTRACT artifacts; no `replace` task ends before VALIDATE.

**No self-verification (hard invariant I4).** No worker marks its own hypothesis
VERIFIED and no agent sets a replacement status. Three locks: (1) identity — the
queue row carries `implementer_id` and `adjudicator_id`; `VALIDATE→RECORDED`
refused unless they differ AND the KG `Adjudication` node's `origin` equals
`adjudicator_id`; (2) approval — workers never receive `approve=true` re-calls;
(3) evidence — `status_update` validates the evidence pointer server-side
(decompilation reference ⇒ max `replaced-approx`; no trace manifest ⇒ never
`replaced-verified`). A worker's "VERIFIED" claim is a proposition, never state.

**Recursion bound.** While investigating A, a worker may (a) call
`ghidra_function` on discovery B — metadata only, ONE call — and (b) ENQUEUE B
(`queue_op` insert + `depends_on` edge); it may NOT advance B's stages (B's body
may appear inside A's snapshot list — that is A's artifact; B's record stays
queued). Depth bound: one metadata level; discoveries-of-discoveries ride the
queue. Higher-priority discoveries are logged in `checkpoint.new_findings` and
take effect at the next stage boundary. Exactly ONE active task, by construction.

**Machine lock.** `flock` on `/tmp/openspore-machine.lock` (kernel-released on
process death — no stale lock). Acquirers: `trace_run` (observe.py),
`cell_stage --interactive`, GPU ctests. Non-blocking + poll 5 s / 90 s timeout →
`machine_locked` error code → park (no attempt burn). Documented human commands
are prefixed with the same `flock` so a human at the keyboard cannot desync a
running trace. Lock body `{pid,label,ts,task_id}` for diagnostics.

**Ranking (orchestrator pick).** (1) gate fan-out — #subsystems whose gate lists
this target's unlock artifact (the cell-mode trace unlocks ≥4:
`cell-movement-mouse-steering`, `resource-manager-full`, `utfwin-message-dispatch`,
`simulator-gameplay`); (2) cost `cheap < medium < operator-blocked` (machine-
readable `gate{unlock_artifact,cost,depends_on[]}` inside
`replacement-status.json`, read via `pipeline_state`); (3) dependency-ready;
tie-break oldest `created_at`. Intake capped at 5/loop, only with a real `why`.

**Overnight-park at approval gates.** Unattended-safe segments:
SELECTED→DOSSIER→STATIC; ASSETS→CONTRACT; REPLACE→VALIDATE. RUNTIME (approval +
real display + `wineserver -k`) and RECORDED (`status_update`) are human-only:
the orchestrator writes the park state (BLOCKED row + a STATE.md §6 note
"parked on <gate>, resume by <one action>"), flushes everything (KG, checkpoints,
committed artifacts), and idles — the queue resumes from cold start.

## 7. Evidence pipeline

How a claim becomes promoted — the chain every `replace` investigation walks:

```
decompile (ghidra_decompile, cached, EVIDENCE-NOT-TRUTH)
  → function card (MCP-DESIGN §F shape: every field sourced or null, never invented)
  → dossier (dossier_regenerate; hash-pinned sources[]; NOT OBTAINED, never fabricated)
  → contract + fixtures (docs/<TOPIC>-CONTRACT.md pattern; double-run byte-identity)
  → trace (where the gate demands live evidence; manifest + JSONL + Observations,
     negative results first-class)
  → adjudication (INDEPENDENT worker: test_run + fixture_check + trace_analyze where
     gated; writes KG Adjudication node with origin=adjudicator_id)
  → status_update (HUMAN approval; the only writer of replacement-status.json)
  → board (replacement-status.json + STATE.md + devlog)
```

Promotion caps (enforced at every step): decompilation reference ⇒ max
`replaced-approx`; `replaced-verified` requires the live oracle (original under
Wine, real bytes/trace) — `replacement-boundaries.md` §5.7; a green test against
our own fixtures proves determinism, not fidelity; APPROXIMATION values (e.g. the
plane constants) promote only on the runtime read; every stage exit writes its
artifact to the durable store AND appends it to `evidence_refs` before the
transition — a stage is done iff its artifact verifies on disk with the matching
`binary_sha256`. Briefings carry ALL prior artifacts (workers are stateless; the
artifacts are the memory).

## 8. GUI boundary & the cell trace

**Exactly ONE workflow justifies GUI automation — W1: menu-walk
main-menu → cell stage under Wine on `:0`.** It is GUI-genuinely-required because
the stage transition is driven by the game's own input handling and no
config/console/DLC path exists into cell (ModAPI detours would alter the behavior
under observation, violating the evidence contract). Everything else: W2 Ghidra
EP1 import = **MANUAL (HUMAN-ONLY)** — headless cannot open new programs (verified);
agent posts the 3-click steps, human clicks, agent verifies via
`list_project_files`/`get_metadata`, analysis is headless again. W3 vtable-labeling
pass = headless script (`run_script_inline` + `reanalyze` on the open program) with
GUI only if the script fails. W4/W5/W6/W7/W8 = headless REST, `gdb -batch`,
human eyes, `curl` the viewer API, `xrandr`+`xdotool` — no computer-use.

**The Xvfb trap.** The 8/9 boot stalls happened WITH real `:0` + direct rendering;
under Xvfb wined3d falls back to llvmpipe software GL and Spore's D3D bring-up may
never fire. Xvfb buys isolation from the human but likely loses the renderer.
`:0` + `xdotool` is the minimal unblock; Xvfb is a last-resort fallback with the
risk stated in the manifest (EXPERIMENTAL, §10).

**The committed script** `tools/observatory/menu_walk.sh` (+ ~60-LOC
`python3-xlib` overlay) is the entire automation surface — diff-reviewed like any
other file; an agent improvising clicks is never allowed ("if it isn't in the
committed script, it isn't happening"). Precondition phase of `trace_run`, same
approval gate. Generation discipline: every `wine` spawn is preceded by
`wineserver -k`; every attempt logs `wineserver -v` + PID (the 9-run precedent
operationalized). Window is pinned + maximized at walk start; geometry drift =
stop, not recover.

**Safety shell (7 boundaries):**
1. Approval gate unchanged (`trace_run` semantics).
2. Window confinement — allowlist of ONE: target only the discovered wine window
   id (`--window $WIN` on every event); terminal/plasmashell never touched.
3. No typing, period — fixed pre-declared key set `Return, Escape, arrows`;
   `xdotool type` is not used anywhere (code-reviewable invariant).
4. Visible **AGENT DRIVING** overlay (borderless, always-on-top, red frame +
   "press Ctrl+Alt+Backspace to stop"), created at walk start, destroyed at stop.
5. Emergency stop, human-side, works even if the agent hangs: the overlay
   `XGrabKey`s the combo globally; press → SIGTERM walker → SIGKILL wine →
   `wineserver -k` → `stopped_by_human` in manifest. The agent polls the overlay's
   stop-state file between every event.
6. File surface: writes only `tools/observatory/out/**` and `/tmp/openspore-walk/`;
   no installs mid-walk, no sudo.
7. Reviewability: one committed script + overlay, nothing else.

**3-level failure ladder (budgeted, never a loop):**

| Level | Trigger | Action |
|---|---|---|
| 1 | 1 no-op at a step | re-assert focus/resend `--window`; retry the step ONCE |
| 2 | 2nd no-op, or renderer marker absent (`+d3d` stderr: no `swapchain_resize_buffers` in 5 s) | `wineserver -k` + fresh boot, 1 attempt only |
| 3 | 3rd failure, any phase timeout (boot ≤60 s, step ≤10 s, total ≤180 s), or geometry drift | **STOP.** SIGKILL game; record the negative result first-class: manifest `outcome: boot-stall|input-no-response|geometry-drift`, partial JSONL (0 events is a valid file), KG `Observation` with `run_id`; park `approval_required` |

Detection signals (all cheap, all headless): `ps -o stat,wchan` (the 9-run
signature: 1 thread, 0 CPU, `ntsync_schedule`, poll 2 s); 0 trace events for 10 s;
the d3d marker; ≥3 identical window hashes after an input; geometry drift.

**Screenshots are annotation, never primary evidence.** The INT3 JSONL carries
nanosecond timestamps and is ground truth; a shot is *evidence* iff
hash-pinned + wall-clock timestamped + trace-t correlated AND its pixel delta
coincides with tracer activity in the same window — a shot with no events in its
window is junk (stored, never cited as a KG Observation). Stored under
`tools/observatory/out/shots/<run_id>/` (git-ignored) with a `shots.jsonl`
manifest; committed examples = a trimmed ≤5 keyframe set under
`tools/observatory/examples/shots_*/` (mirrors the committed-JSONL precedent).

**The ONE manual validation run that decides the design** (MANUAL, human
watching, before any unattended walk): fresh `wineserver -k` → boot on `:0` →
does `xdotool click/key --window $WIN` (XSendEvent, `send_event=true`) reach the
game under KWin + XWayland? KWin is a full compositor on top of XWayland; some
apps reject synthetic events — this is the single biggest unknown on the critical
path. If wine rejects them, the fallback is `windowactivate` + send per keystep;
if THAT fails, the negative result is recorded as the deliverable and the trace
is parked.

## 9. Viewer

`tools/viewer/server.py` — separate process, stdlib `http.server`
(ThreadingHTTPServer), binds **127.0.0.1:8787** (`--bind` refuses non-loopback —
no auth to add; single-machine local trust). Read-only **by construction**:
`sqlite3.connect("file:...spore.db?mode=ro", uri=True)` per request; the process
opens no file for write except its stderr log; byte-pinned by test §5.3. It does
NOT call the MCP server (viewer→stores, never viewer→MCP; if shared SQL is ever
needed, direction is MCP→`tools/viewer/query.py`).

Layout: `server.py` (~450 LOC), `query.py` (~350, all SQL/JSON in one importable
module), `static/` (`index.html` + `viewer.js` fetch+DOM only + `viewer.css` —
**no framework**: the repo has no `package.json`; a React build would need Node +
a build step + committed `dist/` that goes stale — two sources of truth for tables/
cards/chips/one tree; the MCP server made the identical consider-then-reject).

11 views (all hash-routed AND plain JSON endpoints — the UI is never the source of
truth): 1 Function card `#/f/<va>` (MCP-DESIGN §F shape verbatim + `missing[]`);
2 Inventory `#/inventory` (paginated, 58k fns from the in-memory vtables.json
parse); 3 Status board `#/status` (18-subsystem board + gate fan-out table — the
cell-trace-unlocks-4 fact must render as the widest row); 4 Investigations
`#/queue` (blocked-first: approvals, then escalations with inlined notes, then
active/done/dropped/queued); 5 Dossier `#/dossier/<topic>`; 6 Hypotheses
`#/hypotheses`; 7 Evidence timeline `#/timeline/<target>` (capture→observation→
contract→diff→adjudication→status, newest first, build-pinned); 8 Graph
`#/graph` (search + depth 1–2 drilldown tree); 9 Assets `#/assets` (incl. the 3
prose-in-label rows surfaced as a hygiene section; the rejected player-cell
building stands as a callout); 10 Runtime evidence `#/runtime` (manifests,
fired/missed per probe, `menu_transition` flagged "defined, never run");
11 Path to verification `#/verify/<target>` (the derived promotion checklist —
each unchecked item shows the action that clears it).

**"What's missing" derivation rule** — computed server-side per target, union
deduped, priority-ordered over 6 sources:
(1) GATE — `replacement-status.json` `gate`/`missing_evidence` bullets;
(2) DOSSIER — `replacement_readiness.missing_evidence[]` ∪ `known_unknowns[]` ∪
per-function open questions with level < VERIFIED;
(3) FIELDS — `field` rows with either evidence axis < OBSERVED (migrated only);
(4) RUNTIME — `runtime.obtained==false` + probe sets with no matching trace
manifest ("defined, never run");
(5) BLOCKED — `investigations` blocked rows (approvals first — human actions, not
knowledge gaps);
(6) ADJUDICATION — status in {replaced-approx, replaced-stub} with no
`Adjudication` node of `origin` ≠ implementer.
Every item carries `{text, source, clears}`; `next_action(T) = missing(T)[0].clears`
ordered by unlock fan-out — never free-form, so the card and the orchestrator can
never disagree. `missing(T)` empty ⇒ "gate open — promote". An investigated
absence (the 0-event menu retrace) renders struck-through with its evidence link —
resolved negative, not deleted. "NOT OBTAINED" always renders as a gray dashed gap
card, never red: an absence is a finding, not an error.

**FeatureProbe** at startup (`PRAGMA table_info(node)` + `sqlite_master`) → every
view degrades per-feature, never 500s: no DB → banner with seed hint, committed
files still render; unmigrated schema (today's live shape) → "not built"
placeholder cards + dossier-parsed evidence levels; no SPORE/ → same payloads
minus `resource_note.available`; the server never opens `SPORE/**` (test-grepped).

## 10. Classification — NOW / LATER / EXPERIMENTAL / MANUAL / AUTONOMOUS

NOW = this sprint; must be small enough to land in one pass and unblocks the cell
trace (or is infra the platform cannot function without).

| # | Capability / component | Class | Where | Why this class |
|---|---|---|---|---|
| 1 | Schema patch: `node` cols (`evidence_level`, `updated_at`, `binary_sha256`), tables `field`/`trace_run`/`investigations`, labels Class/Hypothesis/Adjudication, rels memberOf/depends_on, 6 indexes, `kg.py _migrate` | **NOW** | §5 | spine; additive, re-runnable, test-pinned |
| 2 | `knowledgegraph/scale.py` — canonical 7-level scale + 9→7 `STATUS2EV` (fixes the 2 missing keys) + Map B back-compat | **NOW** | §5 | the one scale; kills the 3-way prose translation |
| 3 | Seed generator (7 committed inputs; 1,670 SDK fns + 18 subsystems + `investigations` rows; replaces hand literals; reproduces 96/115/14) | **NOW** | §5 | kills hand-written state rot; fixes STATUS2EV |
| 4 | MCP server `tools/mcp/server.py` + registry (21 tools incl. `queue_op`) + `opencode.json` entry + `tests/mcp/test_server.py` | **NOW** | §4 | the single agent↔machine interface; CI-testable |
| 5 | Decompilation disk cache keyed on `(binary_sha256, rva, ghidra_version, program)` | **NOW** | §4 | makes #8/#11 cheap + deterministic; disposable |
| 6 | `binary_sha256` pinning (`config.py`; embedded in every manifest/queue row/node) | **NOW** | §3-4 | the anti-stale mechanism; EP1 flip handled |
| 7 | `investigations` queue + `queue_op` #21 + dedup key `(kind, va, binary_sha256)` | **NOW** | §6 | no re-investigation; the lifecycle the platform exists for |
| 8 | Machine lock: `flock /tmp/openspore-machine.lock` in observe.py + interactive/GPU ctest paths + human wrapper + `machine_locked` code | **NOW** | §6 | shared display + GPU; small, needed before any trace |
| 9 | Install `xdotool x11-utils maim python3-xlib` (one approval) | **NOW** | §8 | prerequisite for the walk |
| 10 | `menu_walk.sh` + AGENT DRIVING overlay + stop key + input log + shot manifest + 3-level ladder | **NOW** | §8 | the cell trace; the ONE justified GUI surface |
| 11 | Cell trace runs: `trace_run` (approval, human present) under `cell_movement.json` probes, walk ≥3×; record manifest + JSONL + committed keyframes + `trace_run` rows + KG Observations + `dossier_regenerate` | **NOW** | §7-8 | the highest-leverage blocked evidence in the repo |
| 12 | Independent adjudication + `status_update` (approval) — promote `cell-movement-mouse-steering` `replaced-approx`→`replaced-verified` where the trace supports | **NOW** | §7 | the promotion; closes the sprint's goal |
| 13 | Manual validation run: does wine accept `xdotool --window` XSendEvent under KWin/XWayland (human watching; decides the script design) | **MANUAL** | §8 | the single critical unknown; honest fallback recorded if negative |
| 14 | Viewer `tools/viewer/server.py` + 11 views + FeatureProbe + `tests/viewer/test_server.py` | **LATER** | §9 | high value once the base grows; not needed for the trace |
| 15 | Full orchestrator loop (ranking, overnight-park, escalation notes `docs/analysis/escalations/`) | **LATER** | §6 | after the first trace lands, in order |
| 16 | Per-target pipeline at scale (new investigations through ASSETS→CONTRACT→REPLACE→VALIDATE) | **LATER** | §7 | post-cell |
| 17 | Ghidra vtable-labeling pass (W3: `run_script_inline` + `reanalyze` on the open program) | **LATER** | §8 | class structure for `dispatch`; cheap, headless |
| 18 | Ghidra EP1 import (W2: agent prepares 3-click steps + verifies via REST) | **MANUAL** | §8 | headless cannot open new programs (verified) |
| 19 | EP1 differential work (new `binary_sha256`, stale-row handling exercised) | **LATER** | §3 | after #18 |
| 20 | Screenshot-driven loop for unknown/fragile UI residue (inside the same safety shell) | **EXPERIMENTAL** | §8 | only if the script derails; may be discarded |
| 21 | Xvfb fallback run (software-GL risk stated in manifest) | **EXPERIMENTAL** | §8 | last resort; the trap is documented |
| 22 | Overnight unattended runs (SELECTED→DOSSIER→STATIC; ASSETS→CONTRACT; REPLACE→VALIDATE; parks at gates) | **AUTONOMOUS** | §6 | safe segments only; resumable from cold start |
| 23 | General computer-use | **EXCLUDED** | §15 | no workflow requires it — do not build |
| 24 | Bulk-import 3,081 vtable candidates into the KG | **EXCLUDED** | §5 | stays in `vtables.json`; `vtable_lookup` reads it |

## 11. Build order (the sprint plan)

| Step | Do | Verification gate (must be true to proceed) |
|---|---|---|
| S0 | Precondition: kill the stale `SporeApp.exe` (PID 213519 at analysis time) + `wineserver -k`; install `xdotool x11-utils maim python3-xlib` (approval) | `xdotool version` runs; `wine --version` = wine-11.17; stale game process gone; `SPORE/` untouched |
| S1 | Schema patch + `scale.py` + seed generator (§5, items 1-3, 7) | `python3 -m unittest discover -s tests` green incl. new seed tests: 96/115/14 reproduced from `seed-literals.json`; byte-deterministic re-run; all 9 statuses of `replacement-status.json` seed without `KeyError`; KG shows 18 `Subsystem` nodes; `investigations` seeded (1,670 fn rows + 18 sub rows + 1 `done` cell row) |
| S2 | MCP server + 21 tools + decompile cache + `opencode.json` entry (items 4-6) | `tests/mcp/test_server.py` green end-to-end over pipes: handshake, 21 valid schemas, pure tools on committed data, `no_spo` degradation, fake-REST decompile cache hit (no second upstream call), gate refusals without `OPENSPORE_MCP_TRUSTED`; from opencode: `pipeline_state` answers and embeds `binary_sha256` |
| S3 | `menu_walk.sh` + overlay + stop key + input log + shot manifest + ladder + machine lock (items 8-10) | script + overlay committed and diff-reviewed; dry-run lists every step without issuing events; overlay appears/destroys cleanly; `Ctrl+Alt+Backspace` stop verified once by hand; lock acquired/released |
| S4 | **MANUAL validation run** (item 13): human watches; fresh `wineserver -k`; boot on `:0`; one `xdotool click --window $WIN` + one `key --window $WIN` | Documented verdict: (a) synthetic events reach the game → proceed as designed; (b) rejected → `windowactivate`+send fallback re-tested once; (c) both fail → **record the negative result as the deliverable**, park the trace, sprint ends at S3 with the evidence |
| S5 | Unattended walk ×3 + cell trace (item 11): `trace_run` under approval (human present) with the walk as precondition; probes = `cell_movement.json` | ≥1 run with ≥1 cell-stage probe event fired (positive); OR the level-3 stop: manifest `outcome` + partial JSONL + `Observation` recorded — the negative result IS a deliverable (9-run precedent). Either way: manifest + JSONL + committed keyframes + `trace_run` rows + dossier regenerated with the runtime section |
| S6 | Adjudication + `status_update` (item 12): independent worker runs `test_run` + `trace_analyze`; writes `Adjudication` (`origin` ≠ implementer); human signs off; `status_update` | `replacement-status.json` entry advanced with evidence pointers (trace manifest id, field rows ≥ OBSERVED for the promoted fields, adjudication node); STATE.md §6 updated; if the trace is negative/incomplete, status STAYS `replaced-approx` with the new evidence recorded — the cap is enforced, not negotiated |

LATER order (after the cell trace lands): #14 viewer → #15 orchestrator loop →
#16 per-target pipeline → #17 vtable pass → #18 EP1 import (MANUAL) → #19 EP1
work → #22 overnight runs → #20/#21 experiments only if cheap.

## 12. Verification & testing strategy

- **Python, stdlib `unittest` only** (`python3 -m unittest discover -s tests`):
  the MCP end-to-end pipe test (§4), the viewer suite (route crawl → 200 + JSON
  envelope; card↔dossier field match on `0xe5b790`; **read-only invariant** —
  sha256+mtime of the temp `spore.db` and every copied committed artifact
  byte-identical before/after a full crawl, no `-wal`/`-shm` left; no-DB and
  unmigrated-schema degradation; no-`SPORE/` with a grep of the server's file
  log proving `SPORE/**` is never opened; unknown-path 404 with the server alive),
  the seed-generator invariants (§5), the `scale.py` mapping (all 9 statuses,
  Map B back-compat).
- **CI-safe means CI-safe**: no wine, no `SPORE/`, no display, no network beyond
  loopback. Everything that needs the real environment is a documented operator
  step with its own record — it is never skipped silently in CI.
- **C++ side unchanged in mechanism**: `cmake -S . -B build && cmake --build
  build -j && ctest --test-dir build -V` (10 tests); `test_run` #18 is the
  agent-facing wrapper; `replace_diff_test` (64/64) and `sim_contract_test`
  (bit-exact fixtures, double-run determinism) are the adjudication's green-test
  inputs. Differential tests run the original under Wine (11) as an oracle only
  through the observatory — never as a build dependency.
- **Byte-identity as the universal staleness check**: fixtures (double-run before
  write), seed generator (sorted emit, deterministic), snapshot (no timestamps in
  body — meta carries the pin; regenerate over identical inputs is byte-identical),
  dossier (same inputs ⇒ same bytes), viewer (read-only pin).
- **Negative result is a deliverable.** A failed trace (stall / 0 events / rejected
  synthetic events) is recorded — manifest `outcome`, partial JSONL (0 events is a
  valid file), KG `Observation`, escalation note where budgeted — and is
  first-class evidence that drives the honest status. The 9-run record is the
  precedent; the ladder makes it mechanical.

## 13. Risks

| # | Risk | Mitigation |
|---|---|---|
| 1 | **KWin/XWayland synthetic-event unknown** — wine may reject `send_event=true` XSendEvent under the KWin compositor on top of XWayland; the whole cell trace depends on it | The ONE manual validation run (S4) before any unattended walk; documented `windowactivate`+send fallback; honest fallback: if both fail, the negative result is recorded as the deliverable and the trace is parked — the platform does not bluff |
| 2 | **wineserver generation stalls** — 8/9 boots stalled in `ntsync_schedule` (the stable 9-run signature); later boots on one generation stall or exit silently | Generation discipline: `wineserver -k` before EVERY spawn, PID + `wineserver -v` logged per attempt; the 3-level failure ladder is budgeted (never a loop); a stall is recorded, not retried forever |
| 3 | **Stale-state rot** — hand-written seed literals, the missing `ghidra_snapshot.py`, path-only dossier sources, EP1 binary drift invalidating every VERIFIED label silently | Seed generator from committed inputs; `ghidra_snapshot_save` with manifest; hash-pinned `sources[]`; `binary_sha256` in every capture/manifest/queue row/node — a build flip flags stale rows (parked, never dropped) and misses every cache automatically |
| 4 | **Scope creep into general computer-use** — the display is shared, the tools are tempting | Explicitly OUT (§15): exactly one committed script is the whole GUI surface; the screenshot loop is licensed only for the unknown/fragile residue inside the same 7-boundary shell; "do not build it" is a design decision, not an aspiration |
| 5 | **The human shares the display** — 2796×1290 streaming VM (Sunshine); a human click moves focus, a moved window mis-aims every click | AGENT DRIVING overlay + announcement before the walk; window pinned + maximized, geometry re-checked every step; drift = **stop, no retry**; `Ctrl+Alt+Backspace` global grab works even if the agent hangs |
| 6 | Ghidra headless server offline mid-sprint | `ghidra_offline` error code → park (no attempt burn); dossiers/snapshots keep working from committed artifacts; re-probe `pipeline_state` each loop |
| 7 | Decompilation cache / traces grow unbounded on `/tmp` and `out/` | Git-ignored by design; cache is binary-keyed and disposable (cost, not evidence); committed evidence is only manifests + ≤5 keyframes + example JSONLs |
| 8 | Viewer port 8787 taken / KWin focus-stealing during the walk | Open question §16; `--port` flag; the walk's geometry-drift stop is the backstop |

## 14. Rollback & safety

- **git is the last line.** Every committed artifact changes only through the
  documented path; the three gated writes are the ONLY writers of
  `replacement-status.json` / fixtures / (deterministic) docs; `git checkout`
  undoes any of them. The KG is git-ignored and **rebuilt** from the committed
  generator — a corrupt `spore.db` is deleted, not repaired.
- **Approval gates are the only write path for status changes.** A status can
  move only via `status_update` with human sign-off under
  `OPENSPORE_MCP_TRUSTED=1`, evidence pointer validated server-side, and (for
  promotion) an `Adjudication` node with `origin` ≠ implementer. There is no
  back-door: workers cannot call it, the orchestrator only executes the human's
  decision.
- **The flock** serializes the X display + GPU (kernel-released on death — no
  stale lock); human commands carry the same lock prefix.
- **The stop key** (`Ctrl+Alt+Backspace`, globally grabbed by the overlay)
  SIGTERMs the walker, SIGKILLs wine, runs `wineserver -k`, and writes
  `stopped_by_human` — effective even if the agent is hung.
- **Schema migration is additive and re-runnable** (`_migrate` guards every
  `ALTER`/`CREATE`); nothing is dropped or renamed; the 96 legacy names survive
  (forward-only rule).
- **Every trace run is bounded** (boot ≤60 s, step ≤10 s, total ≤180 s) and ends
  in a recorded state — positive or negative; the machine is left in a known
  state (`wineserver -k` at every stop).

## 15. What is explicitly OUT of scope

- **General computer-use / agent-driven clicking** — no workflow requires it; the
  one committed script is the ceiling.
- **Xvfb as the primary display** — software-GL trap; last-resort experiment at
  most.
- **Frameworks and dependency additions** — no `package.json`, no `mcp` SDK
  venv/pydantic, no React build step, no new Python packages; stdlib only.
- **1:1 binary parity** — the goal is behavior/contract match on a modern x64/
  Vulkan/SDL3 successor, not byte-identical code; bit-exact trace replay of the
  original is explicitly NOT claimed (input-logged, stage-deterministic,
  non-bit-exact).
- **Anything requiring proprietary assets in git** — no EA code, assets, models,
  textures, sounds; decompiled captures are EVIDENCE-NOT-TRUTH references;
  **asset payload bytes are never returned by any tool** (metadata only); no
  writes into `SPORE/`.
- **Live in-EXE injection as the day-to-day mechanism** — the inline-hook
  mechanism is proven on a native 32-bit synthetic; the Spore install step stays
  gated, and substitution happens at link time in-tree.
- **Bulk KG import of the 3,081 vtable candidates** — they stay in
  `vtables.json`, read by `vtable_lookup`.

## 16. Open questions

1. **Does wine accept XSendEvent (`send_event=true`) under KWin/XWayland on
   `:0`?** The single unknown on the critical path — answered (one way or the
   other) by the S4 manual validation run.
2. **Does the main-menu layout match the walk's assumed coordinates / key
   sequence?** The exact menu path main-menu → cell stage is not yet documented
   step-by-step; the validation run produces it (input log is the record).
3. **Is port 8787 free on this machine** (and stable across reboots) for the
   viewer?
4. **How many investigations fit one overnight window?** Determines the intake
   cap (currently 5/loop) once the orchestrator loop lands.
5. **Is `Ctrl+Alt+Backspace` unbound in the default Plasma/KWin config** on this
   box (the stop-key grab must not fight the compositor)?
6. **Can the boot-stall be made reproducible in the positive direction** (menu
   30 Hz loop was 1/9) — timing/`WINEDLLOVERRIDES`? The walk's level-2 ladder
   copes either way, but a warm, repeatable boot would halve the trace cost.
