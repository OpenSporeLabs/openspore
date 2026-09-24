# Xref resolution + UNKNOWN debt map (snapshots 2540f2ca / f0e310e0)

Worker report: closure of the xref/unknown-resolution phase. Read-only
analysis on the headless Ghidra instance (`127.0.0.1:8089`, program
`SporeApp.exe`, analyzed — no re-analysis, no re-import, no state writes);
all artifacts regenerated locally from committed inputs. Provenance:
binary `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`,
xref snapshot `2540f2ca7cd3…45229c8`, triage snapshot
`f0e310e0c83f…dbf8b54b`. Live program reports 59,245 functions (drift +488
thunk/external entries elsewhere); all 58,757 pinned VAs still resolve
(`pinned_missing_at_address=0`) and the frozen universe stays pinned to
58,757.

## xref export v1 (append-only addendum)

- Raw MCP export (223,760 rows) canonicalized by
  `tools/triage/export_xrefs.py` (sort by caller/callee/callsite + triple
  dedupe, 56 removed) → **223,704 edges** + 362-external allowlist.
- By reference type: direct-call 197,461 · vtable-ref 11,898 · external
  5,481 · data-ref 4,049 · thunk 4,074 · computed-call 741.
- Coverage (call-type edges only, distinct endpoints): 69.83 % of the 58,757
  pinned functions have ≥1 callee, 57.26 % have ≥1 caller.
- Closure: all callers pinned; all callees pinned-or-allowlisted
  (vtable allowlist 3,081; external allowlist 362).
- DB ingest already recorded in the summary: 50,204 triage rows updated,
  0 NULLs remaining, 17,106 zero-filled cells, 223,704 xref rows.

## Triage v5 closure (58,757 functions)

| category | v4 | v5 |
|---|---|---|
| GAMEPLAY_LOGIC | 117 | **493** |
| GAMEPLAY_SUPPORT | 75 | 85 |
| ENGINE_INTERFACE | 302 | 680 |
| ENGINE_IMPLEMENTATION | 5,759 | 5,496 |
| THIRD_PARTY_OR_RUNTIME | 3,564 | 3,707 |
| UNKNOWN | 48,940 | **48,296** |
| total | 58,757 | 58,757 |

Priority: P0 159 · P1 6,261 (v4 5,759) · P2 19 · P3 52,140 · IGNORE 178.
Evidence: CONFIRMED 1,168 · INFERRED 5,706 · SUPPORTED 3,438 · UNKNOWN
48,445.

v5 mechanisms (all deterministic, `tools/triage/classify.py` +
`rules-v5.json`): alias policy 850 records applied (694 assigned, 79
multi-name, 36 redundant, 2 skipped non-fn); vtable inheritance chains
over 3,081 vtable candidates → 5,563 FUN_ pool rows attributed to 36
families (71 gameplay, 1,430 engine-kept, 4,447 anonymous-family residual
debt); middleware absent (no DirectX — GOG build is RenderWare; no
EASTL); 811 MSVCR90 direct callers with 143 zero-callee CRT wrappers;
321 SCC members >1; 192 vtable-backed priority fixes (P3→P1).

## Queue v5 (288 rows) — integrity verified

- 207 v4 rows preserved **verbatim** (all 14 fields diffed, zero diffs):
  queued 153, candidate 19, implemented 35.
- +81 v5 promotions, all `candidate`: Sporepedia 42, Editor 27, Simulator
  11, Terrain 1. Every one is a v5 GAMEPLAY_LOGIC row with a named
  vtable_family + `v5-promotion` rationale; disjoint from v4 VAs; ranked by
  family distinct-SDK-func count desc, then VA.
- Total 288 == 153 + 100 + 35; no orphan VAs (all resolve inside the
  58,757 universe); all 207 v4 rows match `investigations.triage_status`
  1:1 (1,686 function rows in DB: 1,632 queued / 19 candidate / 35
  implemented). The 81 promoted rows are **projection-only by documented
  design** (handoff: DB still holds triage-v4 rows; opt-in ingest is
  `classify.py --rules rules-v5.json --db knowledgegraph/spore.db`).
  No mass queueing of new discoveries: the only new rows are the 81
  family-backed candidates above.

## UNKNOWN debt map (new: `knowledgegraph/triage/debtmap-f0e310e0.json`)

Generator: `tools/triage/debt_map.py` (stdlib only; two runs byte-identical;
sha256 `b5b98edee96e230eea41136d7cc93d1694ca0f101380d8d2cffaa7c8ac0968fa`).
Covers all 48,296 UNKNOWN rows; per-VA record: connectivity degrees
(call-type edges, distinct endpoints), ownership, scc, score, tier.
Thresholds are absolute (documented in the tool's header and echoed in the
JSON `thresholds` block) — no percentage cutoffs.

Connectivity: **isolated 8,362** (in=out=0) · low 26,450 (max degree 1–3)
· high 13,484 (max degree ≥4).

Likely ownership (first match wins): **gameplay_affinity 2,950** (≥1 call
edge to a v5 GAMEPLAY_LOGIC row, or a named game-class stem: cStar,
cPlanet, cEmpire, cScenario, cSpace, cModelObject, cPlayer, cCreature,
cTribe, cCiv) · engine_runtime 8,789 (call edge to v5 ENGINE_*) ·
third_party_hint 786 (import families only) · genuinely_unknown 35,771
(no graph/name/import signal at all — these are the rows that genuinely
need manual decompilation first).

Evidence-score tiers: **UNKNOWN-HIGH 862** (score ≥4; 747 of them carry
gameplay affinity) · UNKNOWN-MEDIUM 6,400 (2–3) · UNKNOWN-LOW 41,034 (≤1).
Score: +2 in-degree ≥8, +1 in-degree 4–7, +1 out-degree ≥8, +2 gameplay
affinity, +1 engine affinity, +1 scc>1, +1 named, +1 import families.

Lists (in the JSON): `high_gameplay_affinity` 2,950 ·
`likely_engine_runtime` 8,789 · `manual_decomp_required` 862 (all
UNKNOWN-HIGH rows have no decomp file — decompilation never ran on
non-SDK-named functions, so the whole HIGH tier needs a fresh decompile
pass before reconstruction).

Note: zero UNKNOWN rows sit in a vtable slot (every vtable-member row
resolved to a category in v5); the 4,398-row anonymous-family pool is
ENGINE_IMPLEMENTATION (4,384) + GAMEPLAY_LOGIC (14) debt, tracked in
`attribution-f0e310e0.json`, not in the debt map.

## Validation log (all PASS)

1. Frozen artifact hashes re-verified: all 2540f2ca artifacts + v5
   projections match the recorded sha256 values (including
   `xrefs-2540f2ca.tsv` `89e74b8a…`).
2. `export_xrefs.py` re-run from the cached raw MCP TSV
   (`/tmp/opencode/xref-job/full.tsv`, 223,760 raw rows, `--ingest` against a
   DB copy) reproduces edges + externals TSV **byte-identical** and the
   summary identical in every data field; the only deltas are the
   outdir-relative `files.*` path display and `zero_filled_cells`
   (17,106 → 0 — a first-ingest historical statistic: the committed DB's
   NULL cells are already filled, so a re-ingest zero-fills nothing).
3. `classify.py --rules rules-v5.json` full re-run reproduces all five
   f0e310e0 projections **byte-identical**; v4 dry-run summary matches
   committed `summary-2540f2ca.json`.
4. Closure: 58,757 rows, 58,757 unique VAs, zero duplicates (triage JSONL
   and functions universe agree).
5. Clusters: 20 clusters sum to 58,757, zero duplicate VAs, every
   `function_count` matches recomputation via the shared `_row_cluster`;
   debt-map `by_cluster` equals per-cluster UNKNOWN counts (sum 48,296).
6. Queue: as above (207 verbatim / 35 implemented / 288 total / no orphans
   / no unbacked mass queueing).
7. KG: `python3 -m unittest discover -s tests -t .` → **408 tests OK**
   (projection-only v5 state is consistent with the committed DB).
8. C++: `cmake -S . -B build && cmake --build build` → clean;
   `ctest --test-dir build` → all suites pass.
9. Tracked files: `git status` shows only the documented modifications
   (docs/STATE.md §13 append, kg.py, schema.sql, two test files) — no
   other tracked file touched; no SPORE/ writes; no game launch.

## Open items for the next worker

1. **Opt-in v5 ingest** (handoff step): `classify.py --rules
   tools/triage/rules-v5.json --db knowledgegraph/spore.db` (upserts
   58,757 rows over v4) — then the 81 promoted candidates land in the DB
   and `investigations.triage_status` aligns 1:1 with the v5 queue.
2. **Decompile pass over the 862 UNKNOWN-HIGH rows** (list in the debt
   map): no decomp files exist for them; the 747 gameplay-affinity rows
   are the first targets.
3. **Anonymous-family vtable debt** (4,398 rows, 4,384 engine / 14
   gameplay in `attribution-f0e310e0.json`): needs deeper vtable work
   (inheritance chains over the 3,081-candidate pool), not more rules.
4. 35,771 genuinely-unknown isolated/low-debt rows: leave as debt; do not
   queue.
