# OpenSpore RE MCP Server — Design (Subagent 3)

Dense design for the smallest useful MCP surface that lets an agent + orchestrator
drive the sequential RE pipeline (docs/RE-WORKFLOW.md). Grounded in verified file
contents, 2026-09-22. Feeds the synthesis subagent.

**Verified environment facts used here**
- GhidraMCP headless server is UP at `127.0.0.1:8089`; `SporeApp.exe` is open
  (59,245 functions, image base `0x00400000`, PE32 i386, GOG 3.1.0.22).
  `GET /check_connection` → OK.
- **Wall correction:** headless *can* read/decompile the open program
  (`GET /decompile_function?address=0xe80980` returned the cCellModeStrategy::Update
  body). The wall is only **opening/importing NEW programs** (GUI required).
- GhidraMCP exposes ~100 REST endpoints (`/decompile_function`, `/search_functions`,
  `/list_functions`, `/analyze_function_complete`, `/get_function_by_address`, ...).
  Its Python bridge is `mcp>=1.28.1,<2` + pydantic under a uv venv
  (`uv run --no-sync --directory ~/apps/ghidra-mcp bridge-mcp-ghidra`).
- `opencode.json` registers MCP servers as `{"type":"local","command":[...],"enabled":true}`
  with two existing entries (`codegraph`, `ghidra`).
- ctest: 10 tests (triangle_smoke, asset_render, material_smoke, cell_stage,
  cell_stage_interactive_smoke, assets_synthetic, assets_real, sim_test,
  sim_contract_test, replace_diff_test).
- KG: 96 nodes / 115 edges / 14 test rows; labels incl. Function, Subsystem,
  Dossier, Finding, Observation, AssetRecord, Contract, ReplacementTarget.
- vtables.json: 5.6 MB, 3,081 candidates, 306 sdk_associations, 58,756 functions,
  meta.image_base `0x00400000`, 4.6M instructions scanned.
- Snapshot ref: `tools/re/data/ghidra_snapshot_cell_movement.json`
  (`ghidra-function-snapshot-1`, per-function decompiled_evidence + evidence_level).
- Dossier ref: `docs/analysis/dossiers/cell-movement.json` (`re-dossier-1`, 7-level
  evidence vocab, `runtime.obtained=false` when no trace — never fabricated).

---

## A. Scope

**In scope** — one stdlib-only Python MCP server (`tools/mcp/server.py`, stdio
transport) exposing ≤25 tools that wrap the *existing* pipeline:
target selection, dedup, dossier read/regen, Ghidra decompile (via headless REST),
asset resolution, vtable lookup, trace orchestration/analysis, tests, fixtures,
replacement status, KG read/write.

**Out of scope (do not duplicate)**
- Anything the `ghidra` MCP already serves generically (raw Ghidra CRUD). The new
  server calls the GhidraMCP *REST* API directly (http.client) and adds only
  OpenSpore framing: RVA↔VA math vs image base, binary-sha256 pinning, caching,
  snapshot capture, evidence labeling.
- No new parsing logic: every tool is a thin facade over an existing tested CLI
  (kg.py, dossier.py, asset_resolver.py, typescan.py, analyze.py, observe.py,
  gen_cell_fixtures.py, ctest) or a REST/SQLite/file read.
- No GUI Ghidra, no Neo4j, no web UI, no asset payload extraction (clean-room).
- No new Python dependencies (see B for the one considered-and-rejected option).

## B. Server architecture

**Transport: hand-rolled JSON-RPC 2.0 over stdio (MCP 2025-06-19). Recommended.**

The protocol surface a tool-only MCP server needs is tiny and stable:
`initialize` → `{protocolVersion, capabilities:{tools:{}}, serverInfo}`;
`notifications/initialized` (ignore); `tools/list` → `[{name,description,inputSchema}]`;
`tools/call` → `{content:[{type:"text",text:<json>}],isError}`; `ping`;
`notifications/cancelled` (ignore). Line-delimited JSON on stdin/stdout, logs on
stderr only. ≈300 LOC in `json`+`subprocess`+`http.client`+`sqlite3`.

**Considered alternative — `mcp` SDK (uv venv, `mcp>=1.28.1,<2`, pydantic v2):**
this is exactly the ghidra-mcp bridge pattern and gives schema validation for free.
Rejected for *this* repo because every other tool here is stdlib-only/CI-safe and
a venv with a dep tree (pydantic, anyio, httpx...) breaks that invariant and needs
network to build; the hand-rolled surface is pinned by an end-to-end unittest that
speaks the protocol over pipes. If opencode ever demands protocol features beyond
the surface above, migrate to the SDK (the tool registry is transport-agnostic).

**Registration** (`opencode.json`, added entry):
```json
"openspore": { "type": "local",
  "command": ["python3", "tools/mcp/server.py"], "enabled": true }
```
No venv; opencode spawns it with cwd = repo root. `OPENSPORE_ROOT` env (default:
cwd) resolves all paths; `OPENSPORE_GHIDRA` (default `http://127.0.0.1:8089`).

**Layout**
```
tools/mcp/server.py        # protocol surface + dispatch loop
tools/mcp/registry.py      # 20 tool schemas (JSON Schema) + handler table
tools/mcp/ghidra_client.py # http.client → 8089 REST; timeouts; offline errors
tools/mcp/cache.py         # decompile/snapshot disk cache (Section D)
tools/mcp/safety.py        # approval gates (Section E)
tools/mcp/config.py        # paths, sha256 pinning, env overrides
tests/mcp/test_server.py   # unittest: spawn server, speak protocol over pipes
```

**Process model:** single process, long-lived per opencode session. One shared
SQLite handle for the KG (WAL), one in-memory parsed vtables.json, one computed
binary_sha256. Handlers are synchronous; long work (trace_run) runs in a thread
and the server keeps answering (protocol stays responsive).

**Failure contract (uniform):** every tool result is JSON with
`{"ok":true,...}` or `{"ok":false,"error":"<code>","hint":"..."}`.
Codes: `ghidra_offline` (hint: start headless server; snapshot fallback noted),
`no_spo` (SPORE/ absent — degrade, never fail), `approval_required` (Section E),
`not_implemented_gate` (target locked behind an unmet gate).

## C. Tool surface (20 tools, grouped by pipeline stage)

| # | Tool | Wraps | Notes |
|---|------|-------|-------|
| 1 | `pipeline_state` | replacement-status.json + KG counts + dossier inventory + fixture/trace inventory | One "where are we" read: per-subsystem status/gate/evidence, open gates (`gatedBy`), dossiers with readiness, tests last green, traces captured. Always embeds `binary_sha256`. |
| 2 | `target_select` | #1 + KG | Ranks uninvestigated targets: subsystems with status < supported lacking a dossier, open gates and their missing artifacts, findings marked `next_action`. Returns top-N with reason + suggested first action. Dedup: never re-suggests a target with an existing dossier at VERIFIED readiness. |
| 3 | `kg_query` | kg.py query | label / name-substring / evidence / confidence filters; returns rows with attrs. |
| 4 | `kg_neighbors` | kg.py neighbors | depth 1–2 traversal by name (names are globally unique by construction). |
| 5 | `kg_record` | kg.py add-node/add-edge/record-test | Batch write (nodes+edges+test rows in one call) with evidence + origin. Writes the git-ignored spore.db (rebuildable from seed_sprint.py) → **no approval**; but must carry a `reason` string. Status *promotion* is NOT here — that is #19. |
| 6 | `dossier_read` | dossiers/<topic>.json | Returns machine dossier (+ optional `md=true`). `topic` missing → structured error listing available topics (dedup aid). |
| 7 | `dossier_regenerate` | tools/re/dossier.py | Deterministic, idempotent (byte-identical on re-run by schema contract) → **no approval** even though it writes docs/analysis/dossiers/. Returns diff status (unchanged/changed/created) + new readiness. |
| 8 | `ghidra_decompile` | REST /decompile_function | By `rva` (auto +image_base) or name. **Disk-cached** (Section D). Returns C text + `evidence_note` ("decompiler output = evidence, not truth; no RTTI"). |
| 9 | `ghidra_function` | REST /get_function_by_address + /analyze_function_complete | Metadata only: name, address/rva, size, namespace, signature, callers, callees, vtable dispatch (joined from vtables.json). In-memory memo. |
| 10 | `ghidra_search` | REST /search_functions | Name-pattern search (SDK prefix, `FUN_`, subsystem). |
| 11 | `ghidra_snapshot_save` | REST decompile+metadata for a function list | THE capture script AGENTS.md says is missing: emits `tools/re/data/ghidra_snapshot_<topic>.json` in `ghidra-function-snapshot-1` shape; meta pins binary_sha256 + Ghidra version + program + source REST. Deterministic (no timestamps in body) → no approval. Offline fallback: dossiers keep working from committed snapshots. |
| 12 | `asset_resolve` | asset_resolver.py --json | (type,group,instance)→record metadata (names, size, offset, qfs). **Metadata only — never payload bytes** (clean-room). |
| 13 | `asset_scan` | dbpf.py list + typescan.py | Package inventory / per-type histogram with decoded type+group names; `package` optional (defaults to all SPORE/*.package). |
| 14 | `vtable_lookup` | vtables.json | By address / namespace / SDK subsystem → candidates, slot funcs, sdk_associations, labels. File parsed once per session. |
| 15 | `trace_run` | observe.py | **APPROVAL-GATED.** Runs the planted-probe trace: preconditions checked first (wineserver -k, X display, xdotool, wine present) and reported; ~30 s+ wall clock. Emits run manifest (Section D) + JSONL path. Never auto-runs. |
| 16 | `trace_analyze` | analyze.py | Deterministic per-trace summary (fired/missed probes, per-function counts, tid histogram, rate spikes). Pure read of out/*.jsonl. |
| 17 | `trace_status` | out/ manifests | Which traces exist, their manifests, which probes fired/missed — feeds #1 and #2. |
| 18 | `test_run` | ctest (build/) | All or named subset; structured results per test (pass/fail/skip + reason, e.g. `assets_real` skips without SPORE/). Never cached — each run is a fresh measurement. |
| 19 | `status_update` | docs/replacement-status.json | **APPROVAL-GATED.** The only writer of a committed status file. Requires: `evidence` pointer (trace manifest / green test names / dossier ref) and enforces the 9-level vocabulary + the evidence rule (decompiler guesses never promote above `inferred`; AI inference is never `verified`). |
| 20 | `fixture_check` | gen_cell_fixtures.py (verify mode) + sha256 of tests/fixtures/cell/fixtures.json | Identity verification only (no `--rebuild`): recomputes, compares, reports. `rebuild=true` is a separate invocation and **APPROVAL-GATED** (double-run byte-identity required before write). |

Cuts considered: `diff_real` (tests/diff_real.py) stays CLI-only — it is an
operator action, not an agent-loop need; `pipeline_state` absorbs replacement-status
and dossier inventory reads; `trace_status` is 6 lines of manifest listing and is
worth keeping because #2 depends on it.

## D. Determinism & caching policy

**Identity pinning (from SCALABILITY.md):**
- `binary_sha256` of `SPORE/SporeBin/SporeApp.exe` computed once per session
  (~50 ms for 20 MB) and embedded in #1, #8–#11, #15 outputs. EP1 differential work
  flips the key → all caches miss automatically.
- Trace run manifest: `{binary_sha256, probes_file_sha256, wine_version,
  xdotool:bool, captured_at, events_total, jsonl_path}`.
- Decomp cache key: `(binary_sha256, rva, ghidra_version, program_name)`.

**Per-tool class:**
- *Pure (no disk cache; in-session memo OK):* #1,3,4,6,7(read),12,13,14,16,17,19(read),20.
- *Disk-cached:* #8 → `tools/mcp/cache/decompiled/<binary12>/<rva>.c` + `.meta.json`
  (key fields + ghidra version + captured_at). `force=true` bypasses. #11 output is
  deterministic (no timestamps in body; meta carries the pin) — regenerating over an
  identical snapshot is byte-identical.
- *Never cached:* #15 (fresh measurement), #18 (ctest), #20 (recomputed each call).
- `tools/mcp/cache/` is git-ignored (add to .gitignore: `tools/mcp/cache/`);
  committed artifacts (snapshots, dossiers) stay in git.

## E. Safety policy

- **Approval-gated (server refuses until `approve=true` re-call after human sign-off):**
  1. `trace_run` — wine + `wineserver -k` + real X display + xdotool; stateful
     environment, ~30 s+.
  2. `status_update` — writes committed `docs/replacement-status.json`.
  3. `fixture_check` with `rebuild=true` — `--rebuild` double-run, overwrites
     committed fixtures.
  Gate mechanics: first call returns `{"ok":false,"error":"approval_required",
  "what":..., "cost":..., "requires":"human approval"}`; orchestrator surfaces it;
  re-call with `approve=true` (only valid when `OPENSPORE_MCP_TRUSTED=1` is set in
  the session env — otherwise the server rejects even approved calls, so a
  misconfigured session cannot self-approve). Documented escape hatch for trusted
  batch runs; default off.
- **No approval (deterministic/idempotent writes):** `dossier_regenerate`,
  `ghidra_snapshot_save` (byte-identotent on pinned inputs; new topics = new file,
  orchestrator commits), `kg_record` (git-ignored DB, rebuildable from
  `seed_sprint.py` — never hand-edit spore.db; seed is source of truth).
- **Clean-room invariant:** no tool returns SPORE/ payload bytes; asset tools are
  metadata-only; traces are event counts, never memory dumps. Server never writes
  into `SPORE/`.
- **Read-only default:** every tool that mutates a committed file is one of the
  three above; all others are pure reads.

## F. Function card (headline read shape)

`ghidra_function` (or `dossier_read` cross-ref) composes the per-function card —
the single most-used artifact for subagent 4. Aggregation only; no new data:
KG nodes + dossier functions + vtables join + trace manifests.

```json
{
  "va": "0x00e806b0", "rva": "0xa806b0", "name": "FUN_00e806b0",
  "sdk_name": null, "sdk_type": null,
  "size_bytes": 1234, "namespace": null,
  "dispatch": null,
  "callers": ["App::cCellModeStrategy::Update"],
  "callees": ["Simulator::Cell::MovePlayerToMousePosition", "..."],
  "subsystem": "sub:cell-movement",
  "investigation": {
    "dossier": "docs/analysis/dossiers/cell-movement.json",
    "evidence_levels": {"role": "INFERRED",
                        "calls MovePlayerToMousePosition": "OBSERVED"},
    "trace": {"captured": false, "fired": null},
    "open_questions": ["plane normal/point constants unread",
                        "game-state word at sCellGame+20960 unconfirmed"]
  },
  "gate": {"subsystem": "sub:simulator-gameplay", "status": "hypothesis",
            "missing_evidence": ["cell trace of MovePlayerToMousePosition"]},
  "next_action": "trace_run(cell) after wineserver -k; then trace_analyze + dossier_regenerate"
}
```

Rules: every field is either sourced (file + section cited) or `null` — never
invented; `evidence_levels` uses only the 7-level dossier vocabulary;
`next_action` is derived from the gate's `missing_evidence`, never free-form.

## G. Testing & rollout

- `tests/mcp/test_server.py` (unittest, stdlib-only, CI-safe, no wine/SPORE/):
  spawn `server.py` as subprocess; speak the protocol over pipes:
  1. `initialize` handshake (version, capabilities, serverInfo).
  2. `tools/list` → exactly 20 tools, all inputSchemas valid JSON Schema
     (validate with a 40-LOC stdlib subset checker: types/required/enum only).
  3. Pure tools end-to-end on committed data: `pipeline_state` (embeds
     binary_sha256 when SPORE/ present, degrades cleanly when absent), `kg_query`,
     `dossier_read` (cell-movement), `vtable_lookup`, `asset_scan` on synthetic
     fixture package, `trace_status`, `fixture_check`.
  4. `ghidra_decompile` against an in-test fake REST (stdlib `http.server` thread)
     → first call hits upstream, second is a cache hit (no upstream request).
  5. Safety: `trace_run` without `OPENSPORE_MCP_TRUSTED` → `approval_required` even
     with `approve=true`; same for `status_update`.
  6. Protocol hygiene: garbage line → JSON-RPC error object, server stays up.
- Rollout: add `opencode.json` entry + `tools/mcp/` + test; verify from opencode by
  calling `pipeline_state`; delete nothing existing (the `ghidra` MCP entry stays).

## Final table (20 tools)

| Tool | Class | Gate | Expensive |
|------|-------|------|-----------|
| pipeline_state | read | – | – |
| target_select | read | – | – |
| kg_query | read | – | – |
| kg_neighbors | read | – | – |
| kg_record | write (git-ignored) | – | – |
| dossier_read | read | – | – |
| dossier_regenerate | write (deterministic) | – | – |
| ghidra_decompile | read | – | REST ~1–3 s; disk-cached |
| ghidra_function | read | – | REST ~0.5 s; memoized |
| ghidra_search | read | – | REST ~0.5 s |
| ghidra_snapshot_save | write (deterministic) | – | N×decompile; one-shot per topic |
| asset_resolve | read | – | – |
| asset_scan | read | – | – |
| vtable_lookup | read | – | – |
| trace_run | runtime | **HUMAN** | ~30 s+ |
| trace_analyze | read | – | – |
| trace_status | read | – | – |
| test_run | validate | – | ctest ~10 s |
| status_update | write (committed) | **HUMAN** | – |
| fixture_check | validate | **HUMAN** if rebuild=true | – |
