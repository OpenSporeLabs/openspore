# SCHEMA-DELTA — KG extensions for the scaled platform

**Subagent 5 deliverable.** Every line is an *incremental* delta on
`knowledgegraph/schema.sql` (41 lines, 4 tables) — nothing is redesigned.
Grounding: live `spore.db` (96 nodes / 115 edges / 14 tests), `schema.sql`,
`kg.py`, `seed_sprint.py`, `docs/KNOWLEDGE-GRAPH.md`, and the sibling analyses
(`SCALABILITY.md`, `MCP-DESIGN.md`, `ORCHESTRATOR.md`, `RE-DOSSIER-SCHEMA.md`,
`REPLACEMENT-ABI.md`, `replacement-status.json`, `dossiers/cell-movement.json`).

Scope: ~58k functions (1,670 SDK-named + 54,666 `FUN_*` + 3,081 vtable
candidates), ~3k vtable candidates, ~4,209 asset records, 18 subsystems,
N dossiers. The KG stays the **single shared source of truth** (AGENTS.md hard
rule) — it only needs to *address* that scale, not store every raw record.

---

## 1. VERDICT per entity

Legend — **Δ schema** = column/table/index; **Δ data** = seed/label fix;
**Δ code** = kg.py / generator; **—** = no change (works at scale).

| # | Entity | Exists? | Missing at scale? | Exact delta | Consumer(s) |
|---|--------|---------|-------------------|-------------|-------------|
| 1 | **Function** | ✅ label `Function` (19 today) | per-function state is nowhere; name is SDK-drift-prone | Δ data: canonical `fun:<va>` name + `sdk_name` attr. Δ schema: cross-cut cols §2. | `ghidra_function`#9, `target_select`#2, `investigations.va` |
| 2 | **Class/struct** | ⚠️ `Structure` (10, C-structs only); C++ classes misfiled under `Function` (e.g. `App::cCellModeStrategy` is a class, stored as a Function) | Function→Class membership; 306 SDK classes + 12 chains not in KG | Δ schema: new label `Class`, new rel `memberOf`. Δ data: generated import of 306+12 from `vtables.json`; **do NOT** bulk-import 3,081. | `vtable_lookup`#14, function-card `dispatch`#F, `ghidra_function`#9 |
| 3 | **Field** (per-field evidence) | ❌ nowhere — free text in `attrs_json` / decompiled `.c` | **The load-bearing gap.** One scalar/node can't say "offset VERIFIED + meaning INFERRED" on the same struct | Δ schema: **new `field` table** w/ two evidence cols (§2). Δ code: promotion rule queries it. | replacement record #8, dossier per-field, VALIDATE |
| 4 | **Asset/resource** | ✅ `AssetRecord` (6) | label hygiene: 3 rows carry prose in `label` → invisible to `query --label AssetRecord` | Δ data: 3 rows `label='AssetRecord'`, prose→`note`. Δ schema: cross-cut cols. | `asset_resolve`#12, dossier `resource_refs` |
| 5 | **System/subsystem** | ✅ `Subsystem` (17); `replacement-status.json` has **18** (divergence) | machine-readable gate; seed is hand-literal | Δ data: generate from JSON (18). Δ schema: structured `attrs.gate{unlock_artifact,cost,depends_on[]}`. | `pipeline_state`#1, `target_select`#2 |
| 6 | **Dossier** | ✅ `Dossier` (1) | hash-pinned `sources[]`; readiness not queryable | Δ data: `attrs.sources=[{path,sha256}]`, `readiness`(9-lvl), `binary_sha256`, `generated_at`. KG-embedded snapshot in JSON stays a *derived view*. | `dossier_read`#6, `pipeline_state`#1, function-card `investigation` |
| 7 | **Evidence** (claim→evidence) | ❌ as a link — claims cite file paths / prose | claim must point at its evidence; hash-pinned | **Not a node.** Δ code: `evidence_refs=[{node?,path?,sha256?}]` field on claim records + reuse edges (`verifiedBy`/`observedVia`/`documentedIn`) to existing Test/Observation nodes. | `kg_query --evidence`#3, I4 evidence lock, dossier per-claim |
| 8 | **Observation** | ✅ `Observation` (11, incl. negative traces) | run **manifest** `{binary_sha256,probes_sha,wine,display,captured_at,events}` — today per-probe attrs only, no pin | Δ schema: **new `trace_run` table** (1 row/run) + `run_id` back-ref on Observation. Δ code: negative results stay first-class. | `trace_status`#17, `trace_analyze`#16, dossier `runtime`, staleness Q3 |
| 9 | **Contract** | ✅ `Contract` (1, name embeds version `cell-sim-contract/1`) | `binary_sha256` pin; version-as-staleness-key not queryable | Δ data: `version` in name (kept) + `binary_sha256` attr. New version string = new node (old = history). | `fixture_check`#20, replacement record, staleness Q11 |
| 10 | **Replacement target** | ✅ `ReplacementTarget` (1) | per-target record as *one* record (5 prose artifacts today) | Δ schema: node + `field` rows(#3) + `diff_summary{cases,fields,mismatches,tolerance}` + `binary_sha256`. ABI doc + POD view **generated** from it. | VALIDATE #18/#20, `status_update`#19, `pipeline_state`#1, dossier `replacement_readiness` |
| 11 | **Validation result** | ✅ `test_result` (14) + `Test` (8) | I4 no-self-verification record; per-run build pin | Δ schema: new label `Adjudication` (origin≠implementer); `test_result.binary_sha256` (created_at already there). | I4 lock (ORCH §4), `test_run`#18, `status_update`#19 |
| 12 | **Hypothesis** | ❌ nowhere (dossier `hypotheses[]` = 5 free-text strings) | full lifecycle record | Δ schema: new label `Hypothesis` `{claim,evidence_refs,evidence_level,status∈{ACTIVE,SUPERSEDED,REJECTED},asserted_by}`. | function-card `investigation`, adjudication, dossier `hypotheses` |
| 13 | **Investigation task** | ⚠️ `investigations` designed in ORCH §1, **not built** | — (split confirmed below) | Δ schema: **new `investigations` table** (ORCH §1 DDL). | orchestrator loop, `queue_op`#21, `target_select`#2 |
| 14 | **Provenance/version** | ⚠️ `created_at` on node+test_result ONLY | `updated_at` on node; `binary_sha256`; (SCALABILITY Q4.4 "no timestamps" is **half-wrong**) | Δ schema: `node.updated_at`, `node.binary_sha256`, `test_result.binary_sha256` (§2). | staleness Q3, VERIFIED-label drift |

**Confirmed split (queue vs KG):** durable **conclusions** (Function/Observation/
Finding/ReplacementTarget/Adjudication) live in node/edge/field/test_result.
Mutable **work state** (stage, attempts, checkpoint, block_reason,
implementer/adjudicator id) lives in `investigations`. Rationale: queue has its
own `UNIQUE(kind,va,binary_sha256)` key (not `label,name`), churning attempt
counters + a checkpoint blob that must *not* flow through the idempotent
evidence-graph upsert. Bridge: queue `id`→KG node names; node `attrs` may carry
an `investigation` ref.

---

## 2. Exact SQL delta

`schema.sql` is the source of truth for a **fresh** DB (`CREATE TABLE IF NOT
EXISTS`, full columns). For the **existing** 80 KB `spore.db`, SQLite has no
`ADD COLUMN IF NOT EXISTS` → apply the guarded migration in §6. Both produce the
identical final DDL.

### 2.1 Columns added to `node`
```sql
ALTER TABLE node ADD COLUMN evidence_level TEXT
    NOT NULL DEFAULT 'UNKNOWN'
    CHECK (evidence_level IN ('UNKNOWN','APPROXIMATION','INFERRED',
        'SUPPORTED','OBSERVED','CONFIRMED','VERIFIED'));
ALTER TABLE node ADD COLUMN updated_at   TEXT NOT NULL DEFAULT (datetime('now'));
ALTER TABLE node ADD COLUMN binary_sha256 TEXT;   -- NULL = build-agnostic
```
`confidence REAL` **stays** (derived display, §3). `created_at` stays untouched —
the `kg.py` upsert `ON CONFLICT(label,name) DO UPDATE` never writes it, so
`created_at` = first-seen, `updated_at` = last-changed (kg.py adds
`updated_at=datetime('now')` to the UPDATE branch only).

### 2.2 New table `field`  (entity #3 — the load-bearing delta)
```sql
CREATE TABLE IF NOT EXISTS field (
  id            INTEGER PRIMARY KEY,
  struct_id     INTEGER NOT NULL REFERENCES node(id) ON DELETE CASCADE, -- Class/Structure node
  offset        TEXT    NOT NULL,            -- '0x4C' / '0x4C..0x4F'
  role          TEXT    NOT NULL,            -- 'cellPos'
  offset_evidence  TEXT NOT NULL DEFAULT 'UNKNOWN' CHECK (offset_evidence  IN (/*7-lvl*/ 'UNKNOWN','APPROXIMATION','INFERRED','SUPPORTED','OBSERVED','CONFIRMED','VERIFIED')),
  meaning_evidence TEXT NOT NULL DEFAULT 'UNKNOWN' CHECK (meaning_evidence IN (/*7-lvl*/ 'UNKNOWN','APPROXIMATION','INFERRED','SUPPORTED','OBSERVED','CONFIRMED','VERIFIED')),
  value         TEXT,                        -- current known/assumed value
  source        TEXT,                        -- hash-pinned provenance
  binary_sha256 TEXT,
  created_at    TEXT NOT NULL DEFAULT (datetime('now')),
  updated_at    TEXT NOT NULL DEFAULT (datetime('now')),
  UNIQUE (struct_id, offset)
);
```
Two evidence axes encode the REPLACEMENT-ABI load-bearing case directly:
`offset_evidence=VERIFIED` + `meaning_evidence=INFERRED` on the *same* struct.

### 2.3 New table `trace_run`  (entity #8 — manifest per run, not per probe)
```sql
CREATE TABLE IF NOT EXISTS trace_run (
  id            INTEGER PRIMARY KEY,
  binary_sha256 TEXT NOT NULL,
  probes_sha256 TEXT,                        -- hash of the probe set file
  wine_version  TEXT,  display_env TEXT,  xdotool TEXT,
  captured_at   TEXT NOT NULL DEFAULT (datetime('now')),
  events_total  INTEGER,  jsonl_path TEXT    -- committed trace archive (SCALABILITY Q10)
);
-- Observation gains a back-ref:  node attrs `run_id` (no schema col needed; it's a link)
```
One run = 1 row; N probes → N `Observation` nodes each carry `run_id`. No 8×
denormalization; `trace_status`#17 lists runs + manifests cleanly.

### 2.4 New table `investigations`  (entity #13 — verbatim from ORCH §1)
```sql
CREATE TABLE IF NOT EXISTS investigations (
  id            INTEGER PRIMARY KEY,
  kind          TEXT    NOT NULL,            -- 'function' | 'struct' | 'asset' | 'subsystem'
  va            TEXT    NOT NULL,
  binary_sha256 TEXT    NOT NULL,
  stage         TEXT    NOT NULL DEFAULT 'TRIAGE'
      CHECK (stage IN ('TRIAGE','EXTRACT','HYPOTHESIZE','REPLACE','VALIDATE','SUPERSEDE')),
  status        TEXT    NOT NULL DEFAULT 'queued'
      CHECK (status IN ('queued','active','blocked','done','superseded')),
  attempts      INTEGER NOT NULL DEFAULT 0,
  block_reason  TEXT,
  checkpoint    TEXT,                        -- JSON blob (worker-local resume)
  implementer_id TEXT,  adjudicator_id TEXT, -- I4: must differ
  evidence_refs TEXT,                        -- JSON array → KG node names + hash-pinned paths
  created_at    TEXT NOT NULL DEFAULT (datetime('now')),
  updated_at    TEXT NOT NULL DEFAULT (datetime('now')),
  UNIQUE (kind, va, binary_sha256)
);
```

### 2.5 New labels (closed enum) + rels
Add to the node-`label` vocabulary: **`Class`**, **`Hypothesis`**,
**`Adjudication`**. (Existing 16 labels unchanged.) Free prose in `label` is
**forbidden** — that is the data bug behind the 3 AssetRecord rows.

Add rels: **`memberOf`** (Function→Class; the vtable-slot / class membership that
powers the function-card `dispatch` field), **`depends_on`**
(Function/Investigation→Function — "must be understood first"). All 30 existing
rels are **kept** (`observes`, `missed`, `storedIn`, `decodesWith`, `walksAs`,
`readBy`, `parsedBy`, `renderedBy`, `testedBy`, `verifies`, `implementedBy`,
`boundedBy`, `verifiedBy`, `gatedBy`, `gates`, `observedVia`, `contains`,
`references`, …).

### 2.6 Indexes
```sql
CREATE INDEX IF NOT EXISTS idx_node_name      ON node(name);            -- kg_query --name-substring (prefix), ghidra_function, target_select
CREATE INDEX IF NOT EXISTS idx_node_evidence  ON node(evidence_level);  -- kg_query --evidence
CREATE INDEX IF NOT EXISTS idx_inv_status     ON investigations(status, stage); -- orchestrator loop: WHERE status='queued'/'blocked'
CREATE INDEX IF NOT EXISTS idx_inv_dedup      ON investigations(kind, va, binary_sha256); -- = the UNIQUE, made explicit for planner
CREATE INDEX IF NOT EXISTS idx_field_struct   ON field(struct_id);       -- promotion rule scans a struct's fields
CREATE INDEX IF NOT EXISTS idx_trace_run_sha  ON trace_run(binary_sha256); -- staleness filter
```
Kept: `idx_node_label`, `idx_edge_src`, `idx_edge_dst`, `UNIQUE(label,name)`,
`UNIQUE(src,dst,rel)`. **`edge` is unchanged** — structural edges are
build-agnostic; the build pin lives on the claim-carrying *nodes*.

**Adequacy at 100k:** ~100k nodes × ~200 B ≈ 20 MB in WAL mode. Every hot query
is O(log n) via the indexes above; `--name-substring` *infix* `LIKE '%x%'` is a
bounded full scan (<10 ms at 100k) — acceptable, no FTS/partitioning needed.

---

## 3. Canonical confidence/evidence scale + in-code mapping

**Decision: ONE canonical 7-level vocabulary** = the dossier schema's
(`docs/RE-DOSSIER-SCHEMA.md`). It is the richest of the three overlapping scales
and already used by the one real dossier. `confidence REAL` is a **derived
display value only**; `evidence_level TEXT` is the source of truth.

Canonical order (monotonic, least→most) and its numeric display:
```python
# knowledgegraph/scale.py  (single source of truth)
EV = {  # canonical 7-level → confidence REAL (display only)
    "UNKNOWN":       0.0,
    "APPROXIMATION": 0.3,   # NEW — best-effort stand-in value
    "INFERRED":      0.5,   # (reasoned, single source) — `hypothesis` status lands here
    "SUPPORTED":     0.75,  # (multiple consistent sources)
    "OBSERVED":      0.85,  # NEW — byte-level / runtime evidence
    "CONFIRMED":     0.9,   # NEW — OBSERVED + independently corroborated
    "VERIFIED":      1.0,   # (reproduced / differential / green test)
}
EV_ORDER = list(EV)   # for "promotable iff every field >= X" checks
```
Original 5-level anchors (INFERRED 0.5 / SUPPORTED 0.75 / VERIFIED 1.0) are
**preserved** so the existing 96 nodes' stored `confidence` barely shifts on
re-seed; the `HYPOTHESIS` (0.25) tier is *collapsed into INFERRED*; the 3 new
tiers (APPROXIMATION, OBSERVED, CONFIRMED) are inserted.

### Map A — 9-level `replacement-status.json` → 7-level evidence
The current `seed_sprint.py:STATUS2EV` is **stale**: it has 7 keys and is
**missing `approximated` and `replaced-approx`** — both now present in
`replacement-status.json` (e.g. `cell-stage-scene-assembly=approximated`,
`cell-movement-mouse-steering=replaced-approx`). Re-seeding the *current* status
file through the old dict would `KeyError`. Generalized (all 9 covered):
```python
STATUS2EV = {
    "unknown":           "UNKNOWN",
    "hypothesis":        "INFERRED",       # reasoned, single source, untested
    "inferred":          "INFERRED",
    "supported":         "SUPPORTED",
    "verified":          "VERIFIED",
    "approximated":      "APPROXIMATION",   # ← was missing (KeyError)
    "replaced-stub":     "SUPPORTED",       # code exists + in-tree substitutability; gate open
    "replaced-approx":   "APPROXIMATION",   # ← was missing (KeyError)
    "replaced-verified": "VERIFIED",        # gate tests green on real bytes
}
```
`confidence = EV[STATUS2EV[status]]`. A target is promotable
`replaced-approx → replaced-verified` **iff every `field` row's
`offset_evidence` and `meaning_evidence` ≥ `OBSERVED`** (SCALABILITY Q8) — a
column query on `field`, not a JSON parse.

### Map B — 5-level old-KG display → 7-level (back-compat, read-only)
Used only when *reading* legacy rows that stored the old 5-level strings:
`{UNKNOWN:UNKNOWN, HYPOTHESIS:INFERRED, INFERRED:INFERRED, SUPPORTED:SUPPORTED,
VERIFIED:VERIFIED}`. New writes always use the 7-level `evidence_level`.

---

## 4. Name-collision rule

`name` is the **global** unique key: `kg.py:_node_id` resolves by `name` *only*
(line 43); the DB constraint is `UNIQUE(label,name)` but the CLI never keys on
`label`. Rule (forward-only; all 96 existing names stay valid):

1. **`name` = kind-prefix + stable key; `label` = the closed kind enum.**
   | Kind | `label` | `name` pattern | stable key |
   |---|---|---|---|
   | Function | `Function` | `fun:<va-8hex>` | image-base-relative VA |
   | Class | `Class` | `cls:<ClassName>` | class name |
   | Struct | `Structure` | `struct:<Name>` | struct name |
   | AssetRecord | `AssetRecord` | `asset:<type>:<group>:<instance>` | resolver identity |
   | Subsystem | `Subsystem` | `sub:<name>` | subsystem name |
   | Implementation | `Implementation` | `impl:<src-path>` | file path |
   | Test | `Test` | `test:<name>` | test name |
   | Observation | `Observation` | `obs:<trace>:<probe>` | run manifest probe |
   | Dossier | `Dossier` | `dossier:<topic>` | topic |
   | Contract | `Contract` | `contract:<version>` | version string |
   | ReplacementTarget | `ReplacementTarget` | `replace:<Symbol>` | symbol |
   | Finding | `Finding` | `finding:<topic>:<slug>` | claim slug |
   | Hypothesis | `Hypothesis` | `hyp:<topic>:<slug>` | claim slug |
   | Adjudication | `Adjudication` | `adj:<topic>:<build-short>` | build |

2. **SDK names are attributes, not IDs.** A function's SDK name goes in
   `attrs.sdk_name`, the Ghidra autogen in `attrs.ghidra_name` — *not* in `name`.
   This makes `name` stable across SDK-import drift (a re-import that renames the
   SDK symbol touches an attr, never the identity → no silent merge/split).

3. **Prefixes make global uniqueness true by construction** — the same function
   addressed three ways (SDK / `obs:` / `FUN_*`) collapses to one
   `fun:<va>` node. Legacy SDK-named nodes (e.g. `App::cAppSystem::Init`) are
   **not** migrated; the rule is forward-only for generated nodes.

---

## 5. Seed-generator spec (replaces `seed_sprint.py` literals — SCALABILITY Q4.1)

The 96/115/14 literals become the **first generated output**, consumed from a
committed input file so re-running is byte-deterministic. Generator emits SQL
(via the `kg.py` upserts) — **no new Python list literals**.

**Inputs (committed, hash-pinned where they cite evidence):**
| Input | Produces |
|---|---|
| `knowledgegraph/seed-literals.json` *(= today's 96/115/14, extracted verbatim)* | legacy nodes/edges/tests (no data loss) |
| `docs/replacement-status.json` (18 subsystems, 9-lvl) | `Subsystem` nodes + `attrs.gate` + `Hypothesis`/`Finding` per open question |
| ModAPI SDK XML via `tools/ghidra/ImportSporeSDK.java` (1,670 addrs) | `Function` nodes `fun:<va>` + `investigations` rows (`kind='function'`) |
| `docs/analysis/dossiers/*.json` | `Dossier` + `Hypothesis`/`Finding` + `covers`/`documentedIn` edges |
| `docs/analysis/vtables.json` → `sdk_associations`(306) + `inheritance_chains`(12) | `Class` nodes + `memberOf` edges. **3,081 `candidates` stay in the JSON** (read by `vtable_lookup`#14) |
| `REPLACEMENT-ABI.md` field tables + replacement-status per-target | `ReplacementTarget` nodes + `field` rows + `diff_summary` |
| committed trace manifests | `trace_run` rows + `Observation` nodes (`run_id`) |

**Invariants (pinned by a test):** (1) byte-deterministic — sort nodes/edges
before emit; (2) idempotent — same upsert semantics as today (node by
`(label,name)`, edge `INSERT OR IGNORE`, seed-owned test rows delete+reinsert);
(3) reproduces the current 96/115/14 exactly from `seed-literals.json` alone;
(4) every `evidence_level`/`confidence` derived through §3 (no hand-typed
confidence).

---

## 6. Migration for the existing `spore.db` (IF-NOT-EXISTS-safe)

SQLite lacks `ADD COLUMN IF NOT EXISTS`. `kg.py` gains a `_migrate()` run before
any command: for each new column, `PRAGMA table_info(node)`; `ALTER TABLE … ADD
COLUMN` only if absent; `CREATE TABLE IF NOT EXISTS` for `field`/`trace_run`/
`investigations`; `CREATE INDEX IF NOT EXISTS` for the six indexes. All
additive, non-destructive, re-runnable. Fresh DBs go straight through
`schema.sql`.

---

## 7. What explicitly does NOT change

- **Core 3-table shape** (`node`/`edge`/`test_result`) — only columns + new
  tables added; nothing dropped or renamed.
- **Identity contracts** — `UNIQUE(label,name)` on node, `UNIQUE(src,dst,rel)`
  on edge.
- **`kg.py` upsert semantics** — `ON CONFLICT(label,name) DO UPDATE`;
  `created_at` preserved (now `updated_at` added to the UPDATE branch).
- **`created_at`** on node + test_result — already present (correction to
  SCALABILITY Q4.4, which claimed "no timestamps").
- **`confidence REAL`** — kept as derived display.
- **vtables.json as the full-candidate store** (3,081) — *not* bulk-imported.
- **The 30 working rels** and the 16 working labels — all kept; only 3 labels +
  2 rels added.
- **The 96 existing node names** — no migration (collision rule is forward-only).
- **The fixture/contract pattern** (SCALABILITY Q11) — unchanged at any scale.
- **`spore.db` git-ignored** (AGENTS.md) — the *generator + inputs* are committed,
  the DB is rebuilt (SCALABILITY Q4.5).
