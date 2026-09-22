# VIEWER — Local KG/Research Viewer (Subagent 6)

Dense build spec for a local, read-only web viewer over the same stores the
MCP server reads (`knowledgegraph/spore.db` + committed artifacts). Optimized
for exactly four questions per target: **what do we know, why do we believe
it, what is missing, what to investigate next.** No graphics beyond tables,
cards, chips, and one drilldown tree. Grounding verified 2026-09-22:

- Live `spore.db`: 96 nodes / 115 edges / 14 tests; **legacy 41-line schema —
  NO `evidence_level` column, NO `investigations`/`field`/`trace_run` tables**
  (SCHEMA-DELTA §6 migration is designed, not applied). 3 rows carry prose in
  `label` (the hygiene bug); `confidence` is the only live evidence column.
- `docs/replacement-status.json`: 18 subsystems (KG has 17 `Subsystem` nodes —
  the divergence), 9-level vocab, per-entry `status/gate/evidence/commits/note`.
- `docs/analysis/dossiers/`: exactly one dossier, `cell-movement.{json,md}`
  (`re-dossier-1`, 7-level vocab, `runtime.obtained=false`, 5 `hypotheses[]`,
  5 `known_unknowns[]`, `replacement_readiness.missing_evidence[3]`).
- `docs/analysis/vtables.json`: 5.6 MB, 58,756 fns, 3,081 candidates, 306
  sdk_associations, `meta.image_base 0x00400000`.
- `tools/observatory/`: `probes/{cell_movement,main_menu,menu_transition}.json`
  (menu_transition defined, never run), `out/{obs_m32,obs_main_menu}.jsonl`,
  `examples/*.jsonl` (committed). `docs/analysis/escalations/` does not exist yet.
- No `package.json` in repo; Python tooling is stdlib-only, CI =
  `python3 -m unittest discover -s tests` + ctest. Machine has X `:0`.

---

## 1. Architecture decision

**Decision: a separate local web app — `tools/viewer/server.py` — NOT part of
the MCP server.**

Justification:

1. **Process ownership.** The MCP server (`tools/mcp/server.py`, Subagent 3)
   is a long-lived stdio process spawned and owned by opencode; embedding an
   HTTP listener inside it couples human browsing to agent-session lifetime
   (viewer dies when opencode exits; a port bind in a stdio-protocol process
   risks interleaving log traffic with the line-delimited protocol).
2. **Separation of writers and readers.** The MCP server *writes* the KG
   (`kg_record`) and owns approval gates. The viewer must be **structurally
   incapable of writing** — a separate process opened against `spore.db` with
   `sqlite3.connect("file:<root>/knowledgegraph/spore.db?mode=ro", uri=True)`
   per request is that guarantee. One codebase, two processes, opposite
   privileges; no shared mutable state.
3. **Human one-command lifecycle, CI-testable.** A human starts it on the
   machine that has `:0`; it is a plain `http.server` and is testable with
   stdlib `unittest` + `urllib` in CI (no wine, no SPORE/, no display).

The viewer is a *parallel reader* of the same stores — it does **not** call
the MCP server (no stdio client, no `ghidra` REST). If the MCP server later
wants shared queries, it may import `tools/viewer/query.py` (the viewer keeps
its SQL in one importable module); the dependency direction is viewer→stores,
never viewer→MCP.

**Layout (3 files, one test file — single-worker, one sprint):**

```
tools/viewer/server.py     # ~450 LOC: argparse, ThreadingHTTPServer, route table,
                           #   JSON envelope, static serving, /health, degradation
tools/viewer/query.py      # ~350 LOC: open_ro(root), FeatureProbe, all SQL/JSON reads
tools/viewer/static/       # index.html (~120 lines, nav + main), viewer.js (~350 lines,
                           #   fetch+DOM only), viewer.css (~150 lines, no framework)
tests/viewer/test_server.py# unittest, §5
```

**Start command (repo root):**

```
python3 tools/viewer/server.py --port 8787
# → viewer on http://127.0.0.1:8787  (db: 96 nodes / 115 edges, 18 subsystems, 1 dossier)
```

Use: any browser on `:0` → `http://127.0.0.1:8787`. Stop: `Ctrl-C`
(`SIGINT` → `ThreadingHTTPServer.shutdown()`). Flags: `--port` (default 8787),
`--root` (repo root; default cwd; env `OPENSPORE_VIEWER_ROOT` also honored —
this is what the test harness uses to point at a temp tree; `kg.py` hardcodes
its DB path, so the test copies `knowledgegraph/{kg.py,schema.sql}` into the
temp root and seeds there — no change to `kg.py`).

**FeatureProbe (the load-bearing robustness mechanism).** At startup the
viewer runs `PRAGMA table_info(node)` and `SELECT name FROM sqlite_master`
once, and caches a capability set:

```
{db: present|absent,
 ev_col: node.evidence_level exists?,
 inv: investigations table?, field: field table?, trace: trace_run table?,
 idx_name: idx_node_name exists?,
 status: replacement-status.json present?, dossiers: [topics],
 probes: [probe file names], out: [manifest/jsonl names],
 escalations: [note files]}
```

Every view degrades per-feature, **never 500s**:

- `spore.db` absent → all KG endpoints return `{"ok":false,"error":"no_db",
  "hint":"python3 knowledgegraph/kg.py init && python3 knowledgegraph/seed_sprint.py init"}`;
  the SPA shows a top banner with that hint and still renders `/status`,
  `/dossier/*`, `/runtime` from committed files.
- `db` present but **unmigrated** (today's reality) → `investigations`/`field`/
  `trace_run`-backed sections render as explicit "not built (ORCH §1 /
  SCHEMA-DELTA §2.4 — not migrated)" placeholder cards; per-claim evidence
  levels come from the dossier JSON's own `evidence_level` strings (parsed with
  the 7-level regex, §3 of SCHEMA-DELTA) and from `confidence` as a fallback
  bar. The viewer therefore works on day one against the live 96-node DB.
- `SPORE/` absent → asset/runtime endpoints return the same payloads they do
  with `SPORE/` present, minus `resource_note.available` (mirrors the MCP
  `no_spo` degrade-never-fail contract). The viewer never opens anything under
  `SPORE/` (boundary §7).

## 2. Views

All views are routes on one SPA (`index.html` + `viewer.js` hash-routing,
`#/f/...`, `#/inventory`, ...) served from `static/`; every view is also a
plain JSON endpoint so the UI is never the source of truth. Uniform envelope:
`{"ok":true,...}` / `{"ok":false,"error":"<code>","hint":"..."}`.
Colors: one 7-level scale, monotonic light→dark (UNKNOWN gray → VERIFIED
green), same mapping as `knowledgegraph/scale.py` Map A (9→7 collapse).
"NOT OBTAINED" is always rendered as a **gray dashed gap card, never red** —
an absence is a finding, not an error.

| # | View (route) | Data source (exact reads) | Answers | Layout |
|---|---|---|---|---|
| 1 | **Function card** `#/f/<va>` (`/api/f/<va>`) | `va` normalized to 8-hex (accepts `0xe5b790` or `fun:00e5b790`); linked VA = `rva + image_base` from `vtables.json` `meta`. Join: (a) `vtables.json` fn entry (name, sdk flag, size, namespace, vtable candidates); (b) KG `Function` node by `name='fun:<va>'` **or** legacy name with `attrs` (tolerant lookup: name = VA, or attrs contains the VA) → edges `calls/memberOf/covers`; (c) **every** committed dossier's `functions[]` entry matching `address` → `role_inferred`, `key_constants`, per-function `evidence_level` strings, `decompiled_evidence` (linked to `tools/re/data/decompiled/*.c`); (d) `ReplacementTarget` node whose `attrs.va` matches → `status/hook/differential/gate`; (e) `replacement-status.json` subsystem whose gate/`evidence` references the VA or its dossier topic → `gate{status,missing_evidence}`; (f) `investigations` row if `FeatureProbe.inv` (stage/status/block_reason/attempts/checkpoint); (g) probe coverage: probes files whose `rva` list contains the VA + `out/`/`trace_run` rows → `trace{captured,fired/missed}` | **what do we know** (role, constants, diff result); **why do we believe it** (per-claim evidence chips + origin + sources); **what's missing** (the §3 gap list, computed server-side and embedded as `missing[]`); **next** (`next_action`, derived, never free-form) | Single card, MCP-DESIGN §F shape **verbatim** (va, rva, name, sdk_name, sdk_type, size_bytes, namespace, dispatch, callers, callees, subsystem, `investigation{dossier,evidence_levels,trace,open_questions}`, `gate`, `next_action`, + `missing[]` from §3). Evidence chips colored on the 7-level scale; nulls rendered as `—` (never invented — the §F rule). `decompiled_evidence` in a collapsed `<details>`. |
| 2 | **Inventory** `#/inventory` | Server-side over the in-memory `vtables.json` parse (58,756 fns parsed once at startup, ~1 s, 5.6 MB — fine for a local tool; NOT shipped as a DOM): default rows = 1,670 SDK-named fns (sdk flag / `sdk_associations` join) + 3,081 vtable candidates marked; `?all=1` adds the rest. Per row: `va, name, sdk_type` (namespace), `subsystem` (dossier `covers` edges / `ReplacementTarget` join / null), `investigation` (from `investigations` if present: none/queued/active/blocked/done + `block_reason`; else "—"), `top_evidence` (dossier fn `evidence_level` max, else `confidence`→7-lvl, else UNKNOWN), dossier link. Filters `?subsystem=&status=&ev=`; `?page=&page_size=100` (default 100, max 500) — **paginated JSON `/api/inventory`**, server sorts+filters, response carries `total` for the pager. | Which of the 58k functions has been looked at at all, and at what confidence | Plain table, sticky header, client-side page controls; row click → function card. No virtualization needed at 100 rows/page. |
| 3 | **Status board** `#/status` | `docs/replacement-status.json` (18 entries, authoritative over the 17 KG nodes — the viewer *shows* the divergence: a footnote listing subsystems present in one but not the other, from `SELECT name FROM node WHERE label='Subsystem'`). Board columns = the 9-level vocab. Gate fan-out table: for each distinct unlock artifact (post-migration: `attrs.gate.unlock_artifact` per SCHEMA-DELTA #5; pre-migration: keyword table `{"cell-mode trace": ["cell-movement-mouse-steering","cell-sim-movement-interaction","simulator-gameplay","cell-stage-scene-assembly"], "menu transition": ["resource-manager-full","utfwin-message-dispatch"], "stage-transition trace": ["simulator-gameplay"], ".prop round-trip": ["property-serialization"]}` matched against the `gate` strings) → row: artifact | # subsystems unlocked | cost class. | Where the whole project stands; the **cell-trace-unlocks-4 fact must render as the widest row** of that table | Two-part page: (top) the machine-readable gate table with the fan-out counts; (below) the board: columns per 9-level, card per subsystem showing `status` chip (7-lvl color), `gate` text, `missing_evidence`/gate bullets, `evidence[]` as links, `commits[]` as monospace chips, `note` collapsed. |
| 4 | **Investigations** `#/queue` | `investigations` table if `FeatureProbe.inv` — `SELECT * ORDER BY` the ORCH §10 surface order: **blocked first** (sorted: `block_reason LIKE 'approval_required%'` first, then `block_reason='escalated'` (each card inlines `docs/analysis/escalations/<task-id>.md` if present, else "note missing"), then `ghidra_offline/no_spo/machine_locked`), then active (stage + `checkpoint` JSON pretty-printed: last_action / next_action / new_findings / worker_id / attempts), then done (the dedup memory — one row per completed target), then dropped, then queued (count + top-10 by ORCH §10 rank: fan-out → cost → deps → oldest). If not migrated: placeholder card "queue not built (ORCH §1, SCHEMA-DELTA §2.4)" + a derived preview: the one `done` case (cell-movement, from the `ReplacementTarget` node) + the seeded 1,670 as "queued (seeded by generator)". | **what to investigate next** + what is parked and **why** (the escalation-note contents are the human action list) | Vertical stack of sections with counts; blocked cards carry the `what/cost/requires` triple; escalation notes in a bordered block. |
| 5 | **Dossier** `#/dossier/<topic>` | `docs/analysis/dossiers/<topic>.json` verbatim (committed, hash-pinned by its `sources[]` when present — the viewer recomputes sha256 of listed sources and flags drift inline; "run seed" hint if file absent: `python3 tools/re/dossier.py <topic>`). | the full record of one topic — every claim, its evidence level, its sources | Sections in dossier order: `evidence_summary` (lead paragraph), `functions[]` (table, per-row `evidence_level` parsed to chips; each row links `#/f/<va>`), `constants[]`/`globals[]`/`vtables[]`, `runtime` (**if `obtained=false`: the gray dashed NOT-OBTAINED gap card with `reason` + `traces_scanned` counts — styled as a gap, never an error**), `resource_refs[]` (→ asset view links), `hypotheses[]` (→ `/hypotheses` anchors), `known_unknowns[]` (each becomes a §3 gap item), `replacement_readiness` (status chip + gate + `missing_evidence`), `openspore_counterpart`. |
| 6 | **Hypotheses** `#/hypotheses` | Post-migration: `SELECT ... WHERE label='Hypothesis'` (claim/evidence_level/status/asserted_by from attrs). Fallback (today): union over committed dossiers of `hypotheses[]` strings, parsed with the 7-level regex; `status` inferred (`ACTIVE` default; `REJECTED` if a `Finding` node's claim refutes it — the player-cell case); `asserted_by` = dossier `snapshot_source` generator. | **why do we believe it** — the registry of every reasoned claim, with its evidence level and its lifecycle | One table: claim | evidence_level chip | status | asserted_by | source dossier (link). |
| 7 | **Evidence timeline** `#/timeline/<target>` | For one target (VA or subsystem): newest-first vertical merge of: `trace_run` rows (if table: binary_sha, probes_sha, wine, display, events, captured_at) + `Observation` nodes touching it (incl. **negative** results — `missed` edges, 0-event notes like `obs:cell_mode_untraced`; negative rows get the gray gap style, they are first-class) + `test_result` rows (pass/fail + binary_sha256 if migrated) + `Adjudication` nodes (origin ≠ implementer shown explicitly) + `Contract` node (version + invariants) + `ReplacementTarget.diff_summary` (64/64, mismatches, tolerance) + `status_update` markers (from `replacement-status.json` `commits[]` + STATE.md §2 SHA references, linked). Order by `captured_at`/`created_at` desc (fallback: insertion order). | the evidence *chain* — capture → observation → contract → diff → adjudication → status; each row is one link with its timestamp and build pin | Vertical list, newest first; each item: kind icon (text label), one-line summary, evidence chip, source link, build pin. |
| 8 | **Graph exploration** `#/graph` | Search box → `SELECT id,label,name FROM node WHERE name LIKE ?` (infix; `idx_node_name` if present, else full scan — <10 ms at 100k per SCHEMA-DELTA §2.6, trivial at 96). Pick node → `/api/neighbors?name=&depth=` (default 1, max 2; BFS over `edge`, rel labels on edges, `memberOf`/`depends_on` rendered distinctly) as a JSON tree the JS renders as an **indented, clickable tree** (click row → expand one level). | local structure around any entity — what touches what | Two-pane: left = search results list, right = drilldown tree (depth 1–2 only). |
| 9 | **Assets** `#/assets` | `SELECT ... WHERE label='AssetRecord'` (the 6 good rows) **plus** a "label hygiene" section listing the 3 prose-in-label rows (the known data bug, surfaced not hidden); `Finding` nodes with `name LIKE 'finding:asset:%'` rendered as callout cards (**the rejected building stand-in** `finding:asset:player-cell-identity-rejected` — claim + evidence, the legal "rejection is a result" outcome); dossier `resource_refs[]` joined by (type,group,instance) → resolved names, purpose, status chip; edges `references/usesTexture/decodesWith/storedIn/readBy` → "referenced by" function links (`#/f/...`). | which real records exist, what they are, what was rejected and why | Table (type/group/instance | resolved | status | referenced-by) + callout cards on top. Metadata only — no payload bytes (§7). |
| 10 | **Runtime evidence** `#/runtime` | `trace_run` table if present (binary sha, probes sha, wine_version, display_env, xdotool, captured_at, events_total, jsonl_path — manifest table); per-run probe fire/miss: `Observation` nodes with `run_id` (attrs) + `observes`/`missed` edges grouped by probe; **pre-migration fallback**: `ls tools/observatory/out/*.jsonl` + `tools/observatory/examples/*.jsonl` (committed links) + probe definitions `probes/*.json` with a **defined-but-never-run** flag computed as "no out/ manifest cites this probe set" (`menu_transition` must flag red-flag-free: amber "defined, never run"); `wine_version` read from the manifest or `wine --version` **once at startup** (cached; never per-request). | what has actually been run, with what build, and what was never run | Manifest table + per-run probe chips (fired green / missed gray-gap) + the never-run probe sets as gap cards. |
| 11 | **Path to verification** `#/verify/<target>` | For a target with a 9-level status (subsystem from `replacement-status.json` or `ReplacementTarget` node): current status → next status; checklist items **derived** (SCHEMA-DELTA §3 Map A + §2.2 + ORCH §4/§9): (a) each `gate.missing_evidence` item → checkbox, done iff a `trace_run` row with matching binary_sha covers it / a green `test_result` names it; (b) `field` rows with `offset_evidence` or `meaning_evidence` < OBSERVED → "field <role>@<offset>: <levels>" (post-migration only; pre-migration: the dossier's "addresses OBSERVED, values INFERRED" lines stand in); (c) `adjudication by implementer ≠` → done iff an `Adjudication` node with `origin` ≠ `implementer_id` exists; (d) `status_update executed` → done iff the status column advanced. Example output for `cell-movement-mouse-steering`: `replaced-approx → replaced-verified` requires [ ] cell trace manifest covering probes of `cell_movement.json` [ ] plane normal/point constants read at runtime [ ] all field rows ≥ OBSERVED [ ] adjudication by ≠implementer [ ] status_update. | the explicit promotion path — each box shows *what action* clears it | Checklist card; each unchecked item has its clearing action (the same text that lands in the function card's `next_action`). |

**No-framework justification (against a React build, for THIS repo):** (1) the
repo invariant is stdlib-only / CI-safe with no `package.json` — a React build
needs Node + a build step + committed `dist/` artifacts that go stale against
hand-written `static/` (two sources of truth), and would make the "one command"
lifecycle two commands. (2) The UI is tables, cards, chips, and one
depth-1–2 tree: zero canvas, zero reactive state machine — `fetch` +
`document.createElement` covers it in ~350 LOC, and the whole frontend is
inspectable with `cat`. (3) The MCP server made the identical
consider-then-reject decision (MCP-DESIGN §B); two build systems for one
evidence-pipeline repo is pure cost. Escalation path: if a view ever needs
real interactivity, it gets its own `static/<view>/` file — the constraint is
per-view, not architectural.

## 3. "What's missing" — derivation rule (the key feature)

Computed **server-side** per target T (function VA, subsystem, or
ReplacementTarget) and embedded in the function card as `missing[]`, in the
`/verify` checklist, and in dossier pages. Exact rule — union, de-duplicated
by normalized text, emitted in this priority order:

```
missing(T) =
  1. GATE:       replacement-status.json entry(T).gate / ReplacementTarget.attrs.gate
                 → each missing_evidence bullet as one item
  2. DOSSIER:    dossier(T).replacement_readiness.missing_evidence[]
                 ∪ known_unknowns[] ∪ per-function open_questions
                 (functions[].evidence_level strings whose level < VERIFIED
                  and that name a constant/word/semantics)
  3. FIELDS:     (migrated only) field rows where offset_evidence < OBSERVED
                 OR meaning_evidence < OBSERVED
                 → "field <role>@<offset>: offset=<lvl> meaning=<lvl>"
  4. RUNTIME:    dossier(T).runtime.obtained == false
                 → one item "runtime: <reason>" (per dossier)
                 + probe sets defined in tools/observatory/probes/*.json with no
                   matching trace_run/out manifest → "probe set <name>: defined, never run"
  5. BLOCKED:    investigations rows for T with status='blocked'
                 → "blocked at <stage>: <block_reason> (attempts <n>)"
                 (approvals first — these are human actions, not gaps in knowledge)
  6. ADJUDICATION: status in {replaced-approx, replaced-stub} and no
                 Adjudication node with origin ≠ implementer_id
                 → "independent adjudication not recorded"
```

Every item carries `{text, source, clears}` where `clears` is the derived
action (trace item → `trace_run(<scenario>)` after `wineserver -k`, then
`trace_analyze` + `dossier_regenerate`; field item → "read at runtime";
adjudication item → "spawn independent adjudicator"; status item →
"`status_update` (human approval)"). **`next_action(T) = missing(T)[0].clears`
ordered by unlock fan-out** (ORCH §10 rank: #subsystems whose gate lists the
unlock artifact → cost → deps → oldest). Never free-form — the same rule the
MCP §F `next_action` field uses, so the card and the orchestrator can never
disagree. `missing(T)` empty ⇒ the card shows "gate open — promote" (and the
`/verify` checklist is all-checked). An absence that was *investigated and
recorded* (e.g. the 0-event main_menu retrace) is rendered as a resolved
negative: item shown struck-through with its evidence link, not deleted —
"we know it was never reached" is knowledge.

## 4. (merged into §2) — see the view table above.

## 5. Testing — `tests/viewer/test_server.py` (stdlib `unittest`)

Harness: `tempfile.TemporaryDirectory` as a fake repo root; copy
`knowledgegraph/{kg.py,schema.sql}` + `docs/replacement-status.json` +
`docs/analysis/dossiers/cell-movement.{json,md}` + `tools/observatory/{probes,out,examples}`
into it; seed the temp DB via `python3 <tmp>/knowledgegraph/kg.py init` +
`seed_sprint.py init` (real committed seed — no hand literals); launch the
server with `--root <tmp> --port 0` (ephemeral port read from stdout line 1),
bound to `127.0.0.1`.

1. **Crawl:** every route in the §2 table (including `/api/f/0xe5b790`,
   `/api/inventory?all=1&page=3`, `/api/neighbors?name=...&depth=2`,
   `/api/health`) → HTTP 200 + `json.loads` succeeds + `ok` field present.
2. **Card↔dossier match:** `GET /api/f/0xe5b790` equals the dossier
   `cell-movement.json` `functions[]` entry for address `0x00e5b790` on every
   overlapping field (va, name, size_bytes 625, callees list, key_constants,
   `evidence_levels` parsed to the 7-level set, subsystem, `gate.missing_evidence`
   = the dossier's `replacement_readiness.missing_evidence[3]`).
3. **Read-only invariant:** sha256 + mtime of the temp `spore.db` **and** of
   every copied committed artifact, taken before and after a full crawl of all
   endpoints (including filter combos and depth=2 graph expansion) — byte-identical.
   (WAL mode: also assert no `spore.db-wal`/`-shm` files exist after.)
4. **Degradation A (no DB):** temp root with the docs but no `spore.db` →
   `/` serves the SPA (200), `/api/health` reports `db:absent` with the seed
   hint, `/status` and `/dossier/cell-movement` still 200, no 500 anywhere.
5. **Degradation B (unmigrated schema — today's live shape):** the seeded temp
   DB from step 1 is exactly legacy 41-line schema → `/queue` renders the
   "not built" placeholder (assert the string), function card `top_evidence`
   falls back to dossier-parsed levels, no exception.
6. **No SPORE/:** temp root has no `SPORE/` dir → `/assets` and `/runtime` 200
   with the degrade flags; assert no opened-file path in the request log ever
   contains `SPORE/` (the server logs every file it touches to stderr — the
   test greps it).
7. **Protocol hygiene:** GET on an unknown path → 404 JSON envelope; the
   server stays up (next request 200).

Run under `python3 -m unittest discover -s tests` (CI-safe: no wine, no
display, no SPORE/, no network beyond loopback).

## 6. What the viewer must NOT do (boundary)

1. **No writes, ever.** `spore.db` opened `mode=ro` per request; the process
   opens no file for write except its own stderr log; the test §5.3 pins this
   at byte level. The KG is written only via `kg.py`/MCP `kg_record`.
2. **No MCP tool calls, no Ghidra REST.** The viewer reads the same stores the
   MCP server reads; it is not an agent and needs no approval machinery.
3. **No SPORE/ payload display.** Asset/runtime views return metadata from the
   KG, dossiers, and committed manifests only; the server never opens
   `SPORE/**` (test §5.6 enforces). Clean-room boundary preserved.
4. **No auth beyond bind-127.0.0.1** (`--bind` refuses non-loopback with an
   error, since there is no auth to add). Single machine, local trust.
5. **No cache directory.** Unlike the MCP server (which disk-caches
   decompilation), the viewer has nothing expensive to cache — the one
   in-memory `vtables.json` parse at startup is the whole state.

**One-command lifecycle:** `python3 tools/viewer/server.py --port 8787`
(starts, prints the banner + feature status) → browser on `:0` to
`http://127.0.0.1:8787` → `Ctrl-C` (clean shutdown). That is the entire
operating procedure; the viewer should make reading STATE.md §6 by hand
unnecessary for the RE half of the milestone.
