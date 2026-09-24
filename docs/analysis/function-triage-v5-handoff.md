# Full-function triage v5 (2026-09-23) — handoff

Classifier `triage-v5` (tools/triage/classify.py, rules tools/triage/rules-v5.json)
re-runs the v4 rule chain over the frozen snapshot 2540f2ca (58,757 functions) with
three new evidence layers, then post-processes. v1–v4 rules files are untouched;
v5 is a superset. **No DB writes by default** (`--db` opts in); projections only.

## Projections (knowledgegraph/triage/, snap8 f0e310e0)

| file | content |
|---|---|
| `triage-f0e310e0.jsonl` | 58,757 rows, v5 fields (aliases, vtable_family, scc_size, import_families, v5 rationale tokens) |
| `summary-f0e310e0.json` | category/priority/evidence/subsystem counts + `v5` block |
| `clusters-f0e310e0.json` | v4 20-cluster inventory recomputed per-row (sum 58,757 ✓) + vtable-family + middleware sections |
| `queue-f0e310e0.json` | 207 v4 rows verbatim (state/rank/db mapping preserved) + 81 v5-promoted `candidate` rows = 288 |
| `attribution-f0e310e0.json` | 5,600-row FUN_ vtable pool per family namespace + middleware rationale examples |

Determinism: 3 consecutive full runs byte-identical (sha256 per file); v4 dry-run
regression still matches `summary-2540f2ca.json` exactly; 408/408 unittest OK;
2540f2ca artifacts verified unchanged. No wall-clock in any projection.

## v4 → v5 deltas

| metric | v4 | v5 | Δ | explanation |
|---|---|---|---|---|
| ENGINE_IMPLEMENTATION | 5759 | 5496 | −263 | 71 →GAMEPLAY via vtable families; 192 →P1; 430 alias-attributed rows re-cut by v4 rules |
| ENGINE_INTERFACE | 302 | 680 | +378 | alias-assigned SDK names (694) re-cut by v4 namespace rules |
| GAMEPLAY_LOGIC | 117 | 493 | +376 | 71 vtable-family flips + 305 alias-driven |
| GAMEPLAY_SUPPORT | 75 | 85 | +10 | alias-driven |
| THIRD_PARTY_OR_RUNTIME | 3564 | 3707 | +143 | CRT-wrapper rescue (MSVCR90-import-only, 0 internal callees, UNKNOWN-only) |
| UNKNOWN | 48940 | 48296 | −644 | 71 + 143 + 430 out of UNKNOWN |
| P1 | 5759 | 6261 | +502 | 192 priority-quirk fix + 310 alias-driven |
| CONFIRMED | 474 | 1168 | +694 | exactly the alias-assigned count |
| P0 / P2 / IGNORE / recon | 159 / 19 / 178 / 159 | same | 0 | untouched by design |

## v5 evidence layers (all deterministic, all from frozen inputs)

1. **SDK contained-alias policy** — 850 repair records (verdicts: contained,
   prologue, tail-alias) applied; names aggregate per repaired target across
   records (79 targets carry ≥2 distinct SDK slot names, resolved by majority
   namespace then lexicographically smallest; 36 targets redundant with the
   canonical SDK name; 2 skipped non-function targets). 694 rows gain an SDK name
   → 694 new CONFIRMED rows. Alias names kept on the row (`aliases` field).
2. **Vtable family attribution** — union-find over 16,107 pair-clusters + 12
   inheritance chains over the 3,081 vtable candidates; 1,501 functions land in a
   labeled family. Family with ≥2 distinct SDK slot funcs in a game namespace
   (App/Editors/Sporepedia/Palettes/Simulator/Terrain) → its ENGINE_IMPLEMENTATION
   members flip to GAMEPLAY_LOGIC (71 rows, all INFERRED→kept INFERRED — family is
   structural evidence, not name provenance). 1,430 family members kept as engine
   (UTFWin 698, Resource 87, IO 23, ArgScript 22, Palettes 12…); subsystem filled
   from family namespace for all of them (rows leave "Unknown").
3. **Middleware identification** — MSVCR90 import ancestry over the 362 frozen
   external dests: 811 functions call MSVCR90 directly; 143 zero-callee wrappers
   rescued out of UNKNOWN. RenderWare: 19 SDK-named functions (5 function entries)
   + family slots; statically linked (no RW import dests). **DirectX absent**
   (zero D3D/IDirect names, zero d3dx/D3DX dests — GOG build links RenderWare).
   **EASTL absent** (zero ea::/EASTL symbols anywhere in the frozen exports).
   Steam: SteamAPI_* thunks via v4 name regex.
4. **Priority quirk fix** — 192 rows with SDK name + vtable slot but no decomp
   move P3→P1 (v4 had parked them P3 on the decomp check alone). Rationale token
   `v5-priority-fix` marks them; v4 P1 set is a strict subset of v5 P1.
5. **Graph metadata** (informational, no category effect): per-function callees/
   callers from the 223,704-edge xref export, import families, SCC sizes
   (321 members of SCCs >1, largest 3 — mutual-recursion debt), vtable dispatch
   caller counts per candidate.

## Vtable pool (5,600 FUN_ rows with vtable slots) per namespace

UTFWin 698 (all engine), anonymous 4,398 (4,384 engine / 14 gameplay — the debt),
Resource 87, Simulator 75 (57/18), Sporepedia 60 (17/43), Editors 73 (46/27),
App 137, IO 23, ArgScript 22, Palettes 18, Terrain 9.

## Queue v5 (288 rows)

- 207 v4 rows preserved verbatim (rank, state, db_mapping): queued 153,
  candidate 19, implemented 35.
- +81 v5 promotions (candidate): Sporepedia 42, Editor 27, Simulator 11,
  Terrain 1 — all family-backed GAMEPLAY_LOGIC with slot evidence, ranked by
  family distinct-SDK-func count desc then VA. `db_triage_status: candidate`
  (same DB mapping as v4 candidates). Ambiguous/anonymous vtable rows stay
  UNKNOWN debt and are deliberately not queued.

## Notes for the next worker

- **Ingest**: v5 projections are new files; the DB still holds triage-v4 rows
  (`classifier_version` column). To adopt v5: `python3 tools/triage/classify.py
  --rules tools/triage/rules-v5.json --db knowledgegraph/spore.db` (upsert
  58,757 rows; v4 rows overwritten in place). Until then, treat v5 as
  projection-only.
- **Validation**: dry-run twice and diff `summary-f0e310e0.json` hashes
  (a5d0… run2 / 63ef… run4 — both stable across 3 runs post-final-edit);
  verify `clusters` `cluster_sum_check == 58757` and queue `total == 288`.
- **Debt-map input**: `attribution-f0e310e0.json` `pool_by_family_ns` is the
  ready-made per-namespace reconstruction surface; the 4,398 anonymous-family
  rows are the residual unknown-vtable-impl debt (needs deeper vtable work, not
  more rules).
- **Docs**: this file supersedes the v4 numbers in `docs/STATE.md` §11 (v4
  section left in place for the audit trail; mark it superseded when merging).
- **Known limitation**: alias resolution is name-level (SDK slot names), not
  EA-source provenance; "CONFIRMED" means "SDK symbol at this VA", nothing more.
