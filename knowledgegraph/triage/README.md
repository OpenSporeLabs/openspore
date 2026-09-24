# knowledgegraph/triage — committed triage projections (snapshot 2540f2ca)

Deterministic full-function triage over all 58,757 functions.
Classifier: `tools/triage/classify.py` (stdlib only) + `tools/triage/rules-vN.json`.
No incremental mode: every run classifies all functions and rewrites the
current projections; refresh = rerun.

## Current files (classifier triage-v4, DB user_version 4)

- `triage-2540f2ca.jsonl` — one row per VA (58757, closure asserted).
- `summary-2540f2ca.json` — category/priority/evidence/subsystem counts, P0 list.
- `clusters-2540f2ca.json` — 20 DB-grounded subsystem clusters (sum 58757).
- `queue-2540f2ca.json` — 207-row reconstruction queue.

## xref export (snapshot 2540f2ca, DB user_version 4 + xref table)

- `xrefs-2540f2ca.tsv` — 223704 canonical edges
  (caller_va, callee_va, reference_type, callsite_va, source,
  snapshot_sha256), sorted, triple-deduped, closure-validated against the
  pinned 58757-VA universe + EXT/VT allowlists.
- `xrefs-2540f2ca.externals.tsv` — 362 external/import dests
  (`EXT:<library>::<name>` allowlist).
- `xrefs-2540f2ca.summary.json` — counts by type, coverage, sha256 of the
  edges TSV, provenance (live program stats, method). `generated_at`-style
  timestamps are excluded from all hashes.
- Exporter: `tools/ghidra/ExportXrefs.java` (read-only GhidraScript, run via
  Ghidra MCP `run_script_inline` on analyzed SporeApp.exe — no re-analysis).
  Canonicalizer/validator/ingest: `tools/triage/export_xrefs.py --ingest`
  (loads `xref` rows, refreshes `triage.caller_count/callee_count`; NULL
  counts are backfilled to 0 only on a proven full-universe scan).
- `reference_type`: direct-call | thunk | external | computed-call
  (call-type; feed the triage counts) + vtable-ref | data-ref (kept, not
  counted). Dest-less indirect calls are never fabricated (counted, skipped).

## Frozen history (do NOT edit, do NOT delete)

- `*.triage-v2.json[l]` — byte-frozen triage-v2-era projections, kept so the
  v2->v3->v4 deltas stay auditable without rerunning old classifiers.
  Current tooling never reads them; `classify.py` only writes the un-suffixed
  names above.

## Reproducibility

- `snapshot_sha256` covers committed export bytes only
  (`load_inputs`: functions/sdk/structs/vtables + decomp filenames).
- `generated_at` timestamps (queue top-level + per-row provenance) are
  informational and excluded from all hashes.
- `queue.counts` is derived from queue rows; `total` must equal row count.

## Queue vocabulary (triage-v4)

- Per-row `queue_state`: one of `candidate | queued | analyzing | understood |
  implemented | replacement-tested | runtime-validated`.
  (`db_triage_status` is kept per row as the legacy UPPERCASE alias;
  post-DB-v4 the lowercase value IS the DB value.)
- `db_mapping.map` covers all 7 states with legacy aliases.
- `replacement-tested` / `runtime-validated` are never assigned yet:
  test_result passes are oracle/contract differentials and trace_run
  outcomes are NULL — see queue `scope_notes`.

## Evidence caveat

`sdk_name => CONFIRMED` is name-level provenance only: the community
Spore-ModAPI SDK is reverse-engineered headers, not EA source. P0 targets
additionally require structural links (vtable slot + decomp file), so no
reconstruction target rests on name evidence alone. Never OBSERVED/VERIFIED
without trace_run/test_result. (Full note: `rules-v4.json` >
`notes.sdk_confirmed_provenance`.)
