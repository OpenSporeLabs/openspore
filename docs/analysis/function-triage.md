# Full-Function Triage — triage-v4 (snapshot `2540f2ca`)

Deterministic classification of **all 58,757 functions** in SporeApp.exe
(3.1.0.22, GOG). Classifier: `tools/triage/classify.py` (stdlib only) +
`tools/triage/rules-v4.json` (v1–v3 history kept alongside). All numbers below
were **verified live against `knowledgegraph/spore.db` on 2026-09-23**; live
DB is the source of truth, the committed JSON projections under
`knowledgegraph/triage/` are byte-reproducible exports of it.

Live counts (exact):

| Category | N | Priority | N | Evidence | N |
|---|---|---|---|---|---|
| GAMEPLAY_LOGIC | 117 | P0 (recon candidate) | 159 | CONFIRMED (SDK name) | 474 |
| GAMEPLAY_SUPPORT | 75 | P1 (vtable-impl backlog) | 5,759 | SUPPORTED (Ghidra-named) | 3,440 |
| ENGINE_INTERFACE | 302 | P2 (named game spillover) | 19 | INFERRED (vtable/heuristic) | 5,755 |
| ENGINE_IMPLEMENTATION | 5,759 | P3 (long tail) | 52,642 | UNKNOWN | 49,088 |
| THIRD_PARTY_OR_RUNTIME | 3,564 | IGNORE (thunk/ext/non-.text) | 178 | — | — |
| UNKNOWN | 48,940 | — | — | — | — |
| **total** | **58,757** | | **58,757** | | **58,757** |

DB: `triage` table, `classifier_version='triage-v4'`,
`snapshot_sha256=2540f2ca…45229c8`, `PRAGMA user_version=4`.
SDK rows: 477 (all with a decomp file). Decomp rows: 477. `FUN_` rows: 54,665.
`recon_candidate=1`: 159 (= P0 exactly). Tests: 408/408 unittest OK,
ctest 36/36 OK.

## 1. Taxonomy

**Categories** (first-match rule order in `rules-v4.json > notes.category_order`):

1. `THIRD_PARTY_OR_RUNTIME` (3,564) — thunk / external / non-.text / third-party
   name (Itanium `^_Z` symbols whose outermost class is a known game class are
   exempt; only 2 such ctors were rescued to gameplay, v2→v3).
2. `ENGINE_INTERFACE` (302) — SDK top-namespace in the engine set
   (App/UTFWin/Resource/IO/Graphics/…): the named engine surface we call into.
3. `GAMEPLAY_LOGIC` (117) — SDK top-namespace in the game set
   (Simulator/Editor/…) **with** a vtable slot, rescued game virtuals (34,
   v2→v3), or named game-namespace/game-global rows.
4. `GAMEPLAY_SUPPORT` (75) — singleton Get/Set/Property-pattern accessors and
   game-namespace virtuals of that shape (8 of the 34 rescued virtuals).
5. `ENGINE_IMPLEMENTATION` (5,759) — vtable-slot members with no SDK/game
   signal (5,755 are `FUN_` vtable-only) + 4 P1-with-game-evidence SUPPORTED rows.
6. `UNKNOWN` (48,940) — everything else resident in .text; includes 30
   `UNKNOWN`/`SUPPORTED` rows (Ghidra-named but unattributed — naming signal
   deliberately retained, not promoted).

**Priorities:** `P0` = sdk AND vtable AND decomp (159, all recon candidates,
all with decomp — zero P0 rows lack a decomp file); `P1` = sdk XOR
(vtable OR decomp), in practice all P1 is SDK-less vtable-only virtuals
(5,758) + 1 game-global row; `P2` = named non-SDK game rows (19);
`P3` = everything else in .text; `IGNORE` = thunk/external/non-.text (178).

**Evidence model** (7-level `scale.py`, triage uses 4):
`UNKNOWN < INFERRED < SUPPORTED < CONFIRMED`; never `OBSERVED`/`VERIFIED`
without `trace_run`/`test_result`. Mapping: `sdk_name` → CONFIRMED; named
non-SDK → SUPPORTED; `FUN_` with vtable slot or heuristic subsystem →
INFERRED; else UNKNOWN.

**SDK-CONFIRMED caveat (load-bearing):** `sdk_name` comes from the community
Spore-ModAPI SDK (reverse-engineered headers,
`SDKtoGhidra/SporeGhidra_march2017.xml`), **not** EA source. CONFIRMED is
**name-level provenance only** (VA pinned to an SDK symbol by the defensive
`ImportSporeSDK` pass). No reconstruction target rests on name evidence alone:
P0 additionally requires structural links (vtable slot + decomp file).
3 of the 477 SDK rows carry UNKNOWN evidence (not CONFIRMED):
`App::DirectPropertyList::Read/Write` and `App::cAppSystem::HookWindows`
— all three are IGNORE (non-.text/thunk-adjacent), so they affect no queue.

## 2. Cluster taxonomy (20 clusters, `clusters-2540f2ca.json`, sum 58,757 ✓)

| Cluster | N | P0 | SDK / decomp | Recon | Readiness |
|---|---|---|---|---|---|
| utfwin-framework (UTFWin UI) | 71 | 44 | 66 / 66 | 44 | ready |
| app-lifecycle (bootstrap) | 148 | 58 | 147 / 147 | 58 | ready |
| resource-io (Resource + IO) | 50 | 17 | 50 / 50 | 17 | ready |
| sim-cell (Simulator::Cell::%) | 26 | 0 | 26 / 26 | 0 | reference (35 Cell rows already `implemented` in queue) |
| sim-space (stars/planets/trade) | 15 | 1 | 15 / 15 | 1 | ready |
| sim-creature-tribeciv | 22 | 0 | 22 / 22 | 0 | ready |
| sim-core-systems (modes/tools/missions) | 30 | 5 | 30 / 30 | 5 | ready |
| editor-core (creature/building/vehicle) | 39 | 15 | 39 / 39 | 15 | ready |
| editor-support (Palettes + Skinner) | 18 | 3 | 18 / 18 | 3 | ready |
| sporepedia-online (+Pollinator) | 14 | 9 | 14 / 14 | 9 | ready |
| terrain-world | 5 | 1 | 5 / 5 | 1 | ready |
| graphics-render (+RenderWare/Transform) | 20 | 0 | 20 / 20 | 0 | ready (interface-only) |
| ui-shell | 4 | 0 | 3 / 3 | 0 | ready |
| scripting-content (ArgScript) | 10 | 6 | 10 / 10 | 6 | ready |
| swarm-anim (Swarm/Anim/Math) | 4 | 0 | 4 / 4 | 0 | ready |
| audio-input (Audio/GameInput) | 6 | 0 | 6 / 6 | 0 | ready |
| gameglobal-misc (namespace-less) | 19 | 0 | 0 / 0 | 0 | P2 backlog |
| runtime-crt-stl (do-not-reconstruct) | 3,557 | 0 | 2 / 2 | 0 | never (P3 3,387 + IGNORE 169) |
| unknown-vtable-impl (FUN_ virtuals) | 5,758 | 0 | 0 / 0 | 0 | P1 backlog — carve via pair-clusters |
| unknown-fun-mass (long tail) | 48,941 | 0 | 0 / 0 | 0 | blocked on xref export |

Named-gameplay total: 192 rows (117 + 75) across sim/editor/sporepedia/
terrain/ui-shell/gameglobal slices. The two `unknown-*` clusters hold 54,699
rows (93.1%) — that is the measured size of the remaining work, not a
classification failure.

## 3. Confidence model

Per-cluster `confidence`/`readiness` in `clusters-*.json`: `ready` = SDK +
decomp + vtable structure present (all 16 named clusters except
gameglobal-misc); P1/P3-unknown clusters are explicitly not-ready with a named
unblocker (pair-cluster carving / xref export). Per-row `rationale` in the
JSONL states the exact rule path. Structural claims (vtable/struct links) are
`INFERRED` at best — no MSVC RTTI exists in SporeApp.exe. Runtime claims need
a trace (S5, currently NEGATIVE per devlog 018) and stay unmade.

## 4. Classifier determinism / rerun / limits

- **Deterministic:** inputs sorted, JSON separators/`sort_keys` fixed, no
  wall-clock in projections (`classified_at` lives only in the DB row).
  Verified 2026-09-23: two `--dry-run` runs → identical sha256
  (`4cd8b052…85423`).
- **Rerun = refresh:** `python3 tools/triage/classify.py [--exports DIR]
  [--db PATH] [--rules PATH]`; `--dry-run` classifies + prints summary,
  writes nothing. **No incremental mode**: every run classifies all 58,757
  functions and upserts the table (idempotent); projections
  `triage-<snap8>.jsonl` / `summary-` / `clusters-` / `queue-` are rewritten.
- **`snapshot_sha256` covers committed export bytes only** (functions / sdk /
  structs / vtables + decomp filenames via `load_inputs`); `generated_at`
  timestamps are informational and excluded from all hashes.
- **Frozen history:** `*.triage-v2.json[l]` are byte-frozen v2-era projections,
  never read by tooling — the v2→v3→v4 deltas stay auditable without rerunning
  old classifiers.
- **Fixes baked into v4:** CHECK migration + backfill (DB user_version 4, see
  §5), `GetTickCount_0` @011ec830 Win32-suffix regex
  (GAMEPLAY_SUPPORT→THIRD_PARTY_OR_RUNTIME; category counts 76→75 /
  3563→3564, recon unchanged), duplicate-VA guard (3 SDK VAs with two symbols
  each — `0093b630`, `0093b360`, `00dde930` — deterministic last-wins in
  committed file order, logged by the loader).

## 5. Queue lifecycle

`queue-2540f2ca.json`: **207 rows** — `queued` 153, `candidate` 19,
`implemented` 35, rest 0. Ordering: `queued` (P0-rescued → P0-engine →
P1-supported) → `candidate` (P2) → `implemented` (Cell reference).
Composition: 149 P0-queued (159 P0 minus 10 Cell lifecycle/input rows that
carry `implemented` evidence and rank in Section C, evidence supersedes,
forward-only) + 4 P1-with-game-evidence SUPPORTED rows + 35 implemented Cell
reference rows + 19 P2 candidates. `replacement-tested` / `runtime-validated`
are never assigned yet (test passes are oracle/contract differentials;
`trace_run` outcomes are NULL; S5 NEGATIVE).

**7 states + DB mapping** (DB user_version 4: `investigations.triage_status`
CHECK accepts the 7 lowercase states directly; the lowercase `queue_state` IS
the DB value; UPPERCASE `db_triage_status` per row is a retired compat alias):

| queue_state | legacy alias | meaning / advance condition |
|---|---|---|
| `candidate` | RECON_CANDIDATE | P2 row nominated; advance by opening an investigation |
| `queued` | QUEUED | accepted target, awaiting analysis |
| `analyzing` | ASSIGNED | investigation open (dossier/decomp read) |
| `understood` | DONE | semantics pinned to dossier + evidence |
| `implemented` | DONE | clean-room C++ behind a `src/compat/` seam |
| `replacement-tested` | DONE | differential vs decomp oracle passes |
| `runtime-validated` | DONE | live trace manifest gates it (S5) — ungated promotion is refused by tooling |

**Projection vs full investigations (reviewer note):** live DB
`investigations` holds `queued`=**1665** / `done`=39 — that is the *full
investigation ledger* (subsystem rows, triage bookkeeping, cell-campaign
rows). The 207-row queue JSON is the *reconstruction projection* over it
(P0/P1-evidenced/P2 + Cell reference), not a count mismatch. Do not "fix" one
to equal the other.

## 6. Coverage report

- **How many known:** 58,757 functions enumerated (closure asserted: every
  input VA gets exactly one triage row).
- **Classified:** 58,757 (100%).
- **Gameplay:** 192 (117 LOGIC + 75 SUPPORT), of which 159 P0 have
  sdk+vtable+decomp; 19 P2 await nomination; 14 P3 Cell/creature rows carry
  evidence but no recon slot (deliberate — Cell is the `implemented`
  reference, not a fresh target).
- **Engine interface:** 302 named rows, all 302 with SDK+vtable+decomp links
  (minus the 2 runtime-crt-stl ENGINE_INTERFACE rows, which are CRT leftovers).
- **Engine internals:** 5,759 ENGINE_IMPLEMENTATION, of which only 4 have any
  game evidence (the P1 SUPPORTED rows in the queue); 5,755 FUN_ vtable-only
  rows are unattributable without xrefs.
- **Third-party/runtime:** 3,564 (CRT/STL/Eastl/OS imports) — do-not-reconstruct.
- **Unknown:** 48,940 category-UNKNOWN (+ 48,941 in the mass cluster counting
  the 1 GAMEPLAY_SUPPORT spillover row) — zero SDK, zero decomp, zero vtable.
- **Largest-value clusters:** app-lifecycle (58 recon), utfwin-framework (44),
  editor-core (15), resource-io (17), sporepedia-online (9) — the first
  reconstruction campaign lives here (152 of 159 P0).
- **Evidence coverage:** SDK 477/58,757 (0.8%), decomp 477/58,757 (0.8%,
  same 477 rows — every SDK row has decomp, zero SDK rows lack it),
  P0 decomp 159/159 (100%), vtable associations 247/306 in UTFWin alone.
- **Largest gaps:** caller/callee NULL on all 58,757 rows (no xref export);
  1,186 SDK VAs with no function entry (need function-boundary repair);
  5,755 FUN_ vtable-only rows stay P1; 315 sdk+decomp-no-vtable rows stay P3
  deliberately (name+decomp without a structural slot link is not promotion
  evidence — moving them would mint recon candidates on name evidence alone);
  48,940 UNKNOWN need the xref pass before any mass claim.

## 7. Recommended reconstruction strategy (next campaign)

Next campaign = **mass semantic reconstruction of the selected gameplay
surface** — no further inventory phase needed; the queue *is* the work list.

1. **Wave 1 — framework:** `utfwin-framework` (44 P0: UTFWinObject new_/
   allocator + message-dispatch vtable roots at 0x013fa974 +21-slot base) then
   `app-lifecycle` (58 P0: bootstrap/system lifecycle). These are every other
   cluster's dependencies.
2. **Wave 2 — substrate:** `resource-io` (17 P0: ResManager/IO streams) then
   `sim-core-systems` (5 P0: game data, modes, tools/weapons, missions).
3. **Wave 3 — gameplay:** `editor-core` (15) + `editor-support` (3) +
   `sporepedia-online` (9) + `scripting-content` (6) + `terrain-world` (1) +
   `sim-space` (1).
4. **Wave 4 — carve `unknown-vtable-impl`:** use the vtable pair-clusters
   (211/300 pairs sharing SDK funcs in UTFWin; per-cluster
   `major_vtables.pair_clusters_sharing_sdk_funcs`) to attribute FUN_ virtuals
   to game classes, promoting P1→queued one pair-cluster at a time.
5. **Prerequisite for `unknown-fun-mass`:** an **xref export** (caller/callee
   counts are NULL everywhere today). Until it lands, no mass promotion out
   of UNKNOWN — attribution without call edges would be guessing.

**Exact entry point (no re-inventory):** open
`knowledgegraph/triage/queue-2540f2ca.json`, take rank 1
(`005737d0 Editors::cEditor::OnMouseMove`, queued, P0, cluster `editor-core`,
dependencies listed per row), or start Wave 1 at the top `queued` UTFWin row;
advance `queue_state` per §5 as each gate passes. Seed data for the first
dossiers is in the row's `decomp_path` + `vtable_addrs` + `kg_node_id`.

## 8. File index

- `tools/triage/classify.py`, `tools/triage/rules-v{1,2,3,4}.json`
- `knowledgegraph/triage/triage-2540f2ca.jsonl` (58,757 rows),
  `summary-2540f2ca.json`, `clusters-2540f2ca.json` (20),
  `queue-2540f2ca.json` (207), `README.md` (projection vocab + caveat)
- Rerun: `python3 tools/triage/classify.py --dry-run` (verify) without `--dry-run` (commit)
- Integrity: `counts` derived from queue rows (`total == row count`); cluster
  `function_count` sum == 58,757; JSONL row count == 58,757
