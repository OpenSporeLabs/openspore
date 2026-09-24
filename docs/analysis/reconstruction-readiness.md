# Reconstruction Readiness Audit — snapshot `f0e310e0`, triage-v6 baseline

Ground truth: `/tmp/opencode/audit/00-dataset.json` (triage-v6 `5fd07ad1…` + queue-v6 `3592f667…` + xrefs `89e74b8a…`), `01-population.json`, `02-queue.json`, `03-dependency.json`. Machine-readable companion: `knowledgegraph/triage/reconstruction-readiness-f0e310e0.json` (deterministic, no wall-clock fields).

Test baseline: python 408/408 + ctest 36/36.

---

## 1. Executive summary

1. **How many of the 2,149 gameplay functions have usable decompilation?**
   172 (8.0%) — decompilation files exist only for the SDK-named subset; all 172 carry real SDK names.
2. **How many of the 368 queued candidates are READY?**
   6 — all decomp-backed (11–20 lines), concrete category, zero external callees: `004ae250` Editors::EditorModel::SetColor; `005c8bc0` Palettes::PalettePage::Load; `00641400`/`00641770`/`006417c0` Sporepedia::cSPAssetDataOTDB::IsEditable/HasName/GetAssetID; `00c8b6b0` Simulator::IsNotStarOrBinaryStar.
3. **How many are READY_WITH_LOCAL_CONTEXT?**
   29 (all decomp-backed; zero in-scope dependencies; local context only).
4. **How many are DEPENDENCY_FIRST?**
   24 — all decomp-backed, gated on their callees: each calls queued-gameplay callees plus a long tail of unknown `FUN_*` callees (worst: `00591fa0` Editors::cEditor::HandleMessage — gl_fan_out=31, 31 queued-gameplay callees + 100 unknown `FUN_*` callees).
5. **How many are ENGINE_BOUNDARY?**
   23 — value gated on crossing an engine interface (mostly the app-lifecycle (16) and resource-io (5) clusters); not reconstructed as gameplay, treated as boundary stubs the rebuilt code calls across. All 23 have decompilation files, so their interface is characterizable from the oracle.
6. **How many are NEEDS_RE?**
   101 — none of the 101 have a decompilation file, so their bodies are unknown (a name alone can never justify READY).
7. **How many are LIKELY_INFRASTRUCTURE?**
   185 — excluded from reconstruction scope; stubbed (102 of the 185 do have decomp files).
8. **How many meaningful dependency components exist?**
   1 dominant connected component of 1,761 functions (81.9%) + 21 small components covering 58 functions + 330 isolated singletons (55 of them decomp-backed). Total: 22 non-trivial components plus 330 isolated leaves.
9. **What are the key subsystem/foundation functions?**
   Top foundations by global fan-in: `00b3d300` FUN_00b3d300 (gl_fan_in=252, scc=1, fan_out_all=0, LIKELY_INFRASTRUCTURE); `00b3d2a0` (101); `00b3d350` Simulator::cGameInputManager::Get (80, decomp `return DAT_0167eaf8;`, CONFIRMED); `00b5b800` (80); `01021260` (68); `00b1fdb0` (68); `00b21340` (50); `00e5c780` map_int_whatever_find (49, NEEDS_RE); `01021300` (47); `01021080` (38); `00b25fb0` (36); `00ba9370` (35). They are overwhelmingly shared-state singleton accessors in the Simulator core — the whole Simulator (~1,300 fns) hangs off ~10 such accessors (e.g. 1,097 total callers of `00b3d300`). Only map_int_whatever_find is a genuine algorithm.
10. **Individual functions or semantic components?**
    Hybrid D: subsystem-first on the decomp-covered clusters, dependency-first on the shared-state roots (RE them before their dependents), isolated singletons as independent parallel work packages, skip LIKELY_INFRASTRUCTURE + ENGINE_BOUNDARY entirely. Why not A: 82% of gameplay sits in ONE connected component and only 172/2,149 (8.0%) have decomp files — per-function reconstruction is order-blind and untestable for the other 92%.
11. **What should the next autonomous reconstruction prompt ingest first?**
    The 35 READY/READY_WITH_LOCAL_CONTEXT queue functions plus the ~11 shared-state root accessors to characterize/stub first as a Phase-0 interface freeze. Machine-readable: `knowledgegraph/triage/reconstruction-readiness-f0e310e0.json` (`queue.per_function` + `dependency.prerequisites_first`).

## 2. Breakdown of the 2,149 gameplay population

Headline metrics (from `01-population.json`):

| metric | count |
|---|---:|
| total gameplay functions | 2,149 |
| with decomp file | 172 |
| strong evidence (CONFIRMED) | 642 |
| useful xrefs | 2,109 |
| SDK vtable boundary | 153 |
| reconstructable without prereqs | 127 |
| depend on prereqs | 207 |
| wrapper dispatchers | 25 |

By population category:

| category | count | share |
|---|---:|---:|
| unknown-needs-investigation | 1,598 | 74.4% |
| core-gameplay-logic | 247 | 11.5% |
| resource-content | 146 | 6.8% |
| world-system | 33 | 1.5% |
| state-management | 30 | 1.4% |
| wrapper-dispatcher | 27 | 1.3% |
| ui-gameplay-interaction | 15 | 0.7% |
| engine-facing-glue | 13 | 0.6% |
| event-callback-dispatch | 13 | 0.6% |
| entity-component | 12 | 0.6% |
| progression-economy | 12 | 0.6% |
| serialization-persistence | 2 | 0.1% |
| ai-decision | 1 | 0.05% |

The long tail is the problem: 1,598 functions (74.4%) are `unknown-needs-investigation`, i.e. region-inferred only, and 1,951 of the 4,048 unnamed `FUN_*` placeholders in the binary live in this set.

## 3. Decompilation coverage

Only 172 of 2,149 (8.0%) have a decompilation file. The decomp export (`decompiled_sdk/*.c`) exists only for the SDK-named function subset: 1,671 SDK-named fns were imported via `ImportSporeSDK.java` and their decomp was exported; the 4,048 unnamed `FUN_*` placeholders (incl. 1,951 in this gameplay set) were never exported. All 172 decomp fns carry a real SDK name (172 of the 198 real-name fns), so **decomp coverage is a strict subset of name-provenance coverage** — a function with a name but no decomp file (e.g. the 10 unnamed shared-state roots) has a body that is simply unknown.

## 4. Readiness breakdown of the 368 queue

Source: `queue-f0e310e0-v6` (368 queued reconstruction candidates; 184 of them decomp-backed).

| readiness | count | share |
|---|---:|---:|
| LIKELY_INFRASTRUCTURE | 185 | 50.3% |
| NEEDS_RE | 101 | 27.4% |
| READY_WITH_LOCAL_CONTEXT | 29 | 7.9% |
| DEPENDENCY_FIRST | 24 | 6.5% |
| ENGINE_BOUNDARY | 23 | 6.2% |
| READY | 6 | 1.6% |

Role flags (per function, non-exclusive): wrapper/dispatcher 40, event callback 22, state management 25, serialization/resource 96, engine glue 141, foundation root 10.

By queue category: GAMEPLAY_LOGIC 196, ENGINE_INTERFACE 125, GAMEPLAY_SUPPORT 43, ENGINE_IMPLEMENTATION 4 (P3).

READY list (6):

| VA | Name | Category | Cluster | Decomp L |
|---|---|---|---|---:|
| 004ae250 | Editors::EditorModel::SetColor | GAMEPLAY_SUPPORT | editor-core | 13 |
| 005c8bc0 | Palettes::PalettePage::Load | GAMEPLAY_LOGIC | editor-support | 20 |
| 00641400 | Sporepedia::cSPAssetDataOTDB::IsEditable | GAMEPLAY_LOGIC | sporepedia-online | 19 |
| 00641770 | Sporepedia::cSPAssetDataOTDB::HasName | GAMEPLAY_LOGIC | sporepedia-online | 15 |
| 006417c0 | Sporepedia::cSPAssetDataOTDB::GetAssetID | GAMEPLAY_SUPPORT | sporepedia-online | 15 |
| 00c8b6b0 | Simulator::IsNotStarOrBinaryStar | GAMEPLAY_LOGIC | sim-core-systems | 11 |

Readiness by cluster (full matrix in `02-queue.md` §6):

| Cluster | Total | READY | READY_WITH_LOCAL | DEPENDENCY_FIRST | ENGINE_BOUNDARY | NEEDS_RE | LIKELY_INFRA |
|---|---:|---:|---:|---:|---:|---:|---:|
| unknown-fun-mass | 79 | 0 | 0 | 0 | 0 | 0 | 79 |
| app-lifecycle | 58 | 0 | 0 | 0 | 16 | 0 | 42 |
| sporepedia-online | 51 | 3 | 6 | 0 | 0 | 42 | 0 |
| utfwin-framework | 44 | 0 | 0 | 0 | 2 | 0 | 42 |
| editor-core | 42 | 1 | 6 | 8 | 0 | 27 | 0 |
| sim-cell | 25 | 0 | 11 | 14 | 0 | 0 | 0 |
| gameglobal-misc | 19 | 0 | 0 | 0 | 0 | 18 | 1 |
| sim-core-systems | 18 | 1 | 4 | 1 | 0 | 12 | 0 |
| resource-io | 17 | 0 | 0 | 0 | 5 | 0 | 12 |
| scripting-content | 6 | 0 | 0 | 0 | 0 | 0 | 6 |
| unknown-vtable-impl | 3 | 0 | 0 | 0 | 0 | 0 | 3 |
| editor-support | 3 | 1 | 1 | 1 | 0 | 0 | 0 |
| terrain-world | 2 | 0 | 1 | 0 | 0 | 1 | 0 |
| ui-shell | 1 | 0 | 0 | 0 | 0 | 1 | 0 |

## 5. Dependency / component analysis

Connected components (undirected, gameplay-only call edges; verified from the xrefs TSV — size histogram exactly `[1761, 5,5, 4, 3×8, 2×10, 1×330]`):

| component | nodes | share of 2,149 |
|---|---:|---:|
| ONE dominant core | 1,761 | 81.9% |
| small clusters (size 2–5) | 58 across 21 components | 2.7% |
| isolated singletons (no gameplay edge) | 330 | 15.4% |

The dominant core is overwhelmingly **Simulator**: 1,319/1,761 nodes, then Editor 226, Terrain 67, Palettes 48, GameGlobal 31, Sporepedia 29, Skinner 22. Of the 1,761 core nodes only **115 have a decomp file** and only 134 carry a real name — the other ~1,600 are unnamed `FUN_*` placeholders never decomp-exported.

High fan-in (shared-state managers / subsystem roots; fan-in = all callers, gl_fan_in = gameplay callers):

| va | name | fan-in | gl-fan-in | decomp | evidence |
|---|---|---:|---:|---:|---|
| 00b3d300 | FUN_00b3d300 ⚠ | 1,097 | 252 | 0 | SUPPORTED |
| 00b3d2a0 | FUN_00b3d2a0 ⚠ | 314 | 101 | 0 | SUPPORTED |
| 00b5b800 | FUN_00b5b800 ⚠ | 459 | 80 | 0 | SUPPORTED |
| 00b3d350 | Simulator::cGameInputManager::Get | 614 | 80 | 13L | CONFIRMED |
| 01021260 | FUN_01021260 ⚠ | 262 | 68 | 0 | SUPPORTED |
| 00b1fdb0 | FUN_00b1fdb0 ⚠ | 303 | 68 | 0 | SUPPORTED |
| 00b21340 | FUN_00b21340 ⚠ | 254 | 50 | 0 | SUPPORTED |
| 00e5c780 | map_int_whatever_find | 239 | 49 | 0 | SUPPORTED |
| 01021300 | FUN_01021300 ⚠ | 182 | 47 | 0 | SUPPORTED |
| 01021080 | FUN_01021080 ⚠ | 175 | 38 | 0 | SUPPORTED |
| 00b25fb0 | FUN_00b25fb0 ⚠ | 100 | 36 | 0 | SUPPORTED |
| 00ba9370 | FUN_00ba9370 ⚠ | 136 | 35 | 0 | SUPPORTED |
| 00743b50 | FUN_00743b50 ⚠ | 134 | 35 | 0 | SUPPORTED |
| 00ce6950 | FUN_00ce6950 ⚠ | 112 | 33 | 0 | SUPPORTED |
| 005c65e0 | FUN_005c65e0 ⚠ | 140 | 32 | 0 | SUPPORTED |

High fan-out (dispatchers; all in the core SCC, mostly Editor): `0102df20` (fan-out 104 / gl 55, scc 17), `010593e0` (86 / 33), `00591fa0` Editors::cEditor::HandleMessage (111 / 31), `00588570` cEditor::OnMouseDown (92 / 29), `01003690` (52 / 28), `00587270` cEditor::SetActiveMode (43 / 28), `01056160` (41 / 26), `0058be50` cEditor::Update (97 / 26), `0105a110` (50 / 24), `00586b00` cEditor::SetEditorModel (49 / 22).

Subsystem roots (named, decomp-backed `::Get` singletons):

| va | name | gl-fan-in | dependents |
|---|---|---:|---:|
| 00b3d350 | Simulator::cGameInputManager::Get | 80 | 80 |
| 00b3d4d0 | Simulator::cSpaceTrading::Get | 22 | 22 |
| 00b3d3c0 | Simulator::cRelationshipManager::Get | 20 | 20 |
| 00401090 | Editors::cSpeciesManager::Get | 17 | 17 |
| 00b3d420 | Simulator::cGameModeManager::Get | 16 | 16 |

Shared-state struct access (functions touching the struct): /Spore/Editors/cEditor (21 fns), Palettes/AdvancedItemViewer (15), Simulator/Cell/cCellGFX (14), Terrain/cTerrainSphere (14), Sporepedia/cSPAssetDataOTDB (13), Simulator/cStarManager (12), cRelationshipManager (11), cCreatureBase (10), cCreatureGameData (10), cScenarioPowerup (10), … (full table in `03-dependency.json`).

Vtable families (SDK class → # functions implementing slots): Sporepedia::cSPAssetDataOTDB 55, Editors::cEditor 24, Simulator::cDefaultAoETool 15, Editors::EditorModel 12, Palettes::AdvancedItemViewer 8, Editors::EditorCamera 5, Simulator::cToolStrategy 4, Simulator::cDefaultBeamTool 3, Simulator::IsNotStarOrBinaryStar 2, UTFWin::Window 1.

## 6. Foundation functions

Ranked by structural importance (from `03-dependency.json` `foundations_ranked`):

| # | va | name | metric | depends-on (gameplay) | reconstructable now | evidence |
|---:|---|---|---|---:|---|---|
| 1 | 00b3d300 | FUN_00b3d300 | gl_fan_in=252, scc=1, fan_out_all=0 | 0 | no | SUPPORTED, decomp 0L, LIKELY_INFRASTRUCTURE |
| 2 | 00b3d2a0 | FUN_00b3d2a0 | gl_fan_in=101, scc=1, fan_out_all=0 | 0 | no | SUPPORTED, decomp 0L, LIKELY_INFRASTRUCTURE |
| 3 | 00b3d350 | Simulator::cGameInputManager::Get | gl_fan_in=80, scc=1, fan_out_all=0 | 0 | no | CONFIRMED, decomp 13L, not-queued |
| 4 | 00b5b800 | FUN_00b5b800 | gl_fan_in=80, scc=1, fan_out_all=2 | 2 | no | SUPPORTED, decomp 0L, LIKELY_INFRASTRUCTURE |
| 5 | 01021260 | FUN_01021260 | gl_fan_in=68, scc=1, fan_out_all=0 | 0 | no | SUPPORTED, decomp 0L, LIKELY_INFRASTRUCTURE |
| 6 | 00b1fdb0 | FUN_00b1fdb0 | gl_fan_in=68, scc=1, fan_out_all=0 | 0 | no | SUPPORTED, decomp 0L, LIKELY_INFRASTRUCTURE |
| 7 | 00b21340 | FUN_00b21340 | gl_fan_in=50, scc=1, fan_out_all=2 | 2 | no | SUPPORTED, decomp 0L, LIKELY_INFRASTRUCTURE |
| 8 | 00e5c780 | map_int_whatever_find | gl_fan_in=49, scc=1, fan_out_all=0 | 0 | no | SUPPORTED, decomp 0L, NEEDS_RE |
| 9 | 01021300 | FUN_01021300 | gl_fan_in=47, scc=1, fan_out_all=2 | 2 | no | SUPPORTED, decomp 0L, LIKELY_INFRASTRUCTURE |
| 10 | 01021080 | FUN_01021080 | gl_fan_in=38, scc=1, fan_out_all=0 | 0 | no | SUPPORTED, decomp 0L, LIKELY_INFRASTRUCTURE |
| 11 | 00b25fb0 | FUN_00b25fb0 | gl_fan_in=36, scc=1, fan_out_all=2 | 2 | no | SUPPORTED, decomp 0L, LIKELY_INFRASTRUCTURE |
| 12 | 00ba9370 | FUN_00ba9370 | gl_fan_in=35, scc=1, fan_out_all=1 | 1 | no | SUPPORTED, decomp 0L, LIKELY_INFRASTRUCTURE |

All 12 are scc=1 (leaf-like) with zero or near-zero gameplay dependents-of — i.e. they sit at the bottom of the dependency graph. 11 of the 12 are shared-state singleton accessors (the named one, `cGameInputManager::Get`, decompiles to `return DAT_0167eaf8;`; `cSpaceTrading::Get` to `return DAT_0167eb50;`); only `map_int_whatever_find` is a genuine algorithm. None is reconstructable now — their job in the next campaign is **interface characterization** (name the singleton each returns; decomp-export them), not implementation.

Queue-level foundation roots (high queue fan-in): `00b1fbf0` (123 callers, editor-core, NEEDS_RE), `0068f9b0` App::cJob::Continuation (35, decomp), `00c6a960` (34, NEEDS_RE), `00644b10` SporepediaRequest_dtor (25, NEEDS_RE), `00e6d200` Simulator::Cell::PlayAnimation (38, DEPENDENCY_FIRST, decomp), `00e57340` GetScaleDifferenceWithPlayer (20, READY_WITH_LOCAL_CONTEXT, decomp), `007b86e0` (16, NEEDS_RE), `0059d960` cEditorAnimEvent__ctor (13, NEEDS_RE), `009317b0` IO::FileStream::SetPathCString (10, decomp), `00e58980` GetDamageAmount (5, READY_WITH_LOCAL_CONTEXT, decomp).

## 7. Key blockers

- **The 10 unnamed shared-state roots have no decomp.** `00b3d300` (252 gl-fan-in, 1,097 total callers), `00b3d2a0`, `00b5b800`, `01021260`, `00b1fdb0`, `00b21340`, `01021300`, `01021080`, `00b25fb0`, `00ba9370` — the whole Simulator core hangs off them, their bodies are unknown, and nothing above them is testable until each singleton is characterized. This is the single largest blocker.
- **`map_int_whatever_find` (`00e5c780`)** — the only high-fan-in function outside the accessor family; a map-lookup helper on GameGlobal state, NEEDS_RE, no decomp. Genuine RE prerequisite for all GameGlobal work (31 fns in the core).
- **DEPENDENCY_FIRST (24)** — decomp present but gated on callees; each also calls a long tail of unknown `FUN_*` callees that must be understood first (e.g. `00591fa0` cEditor::HandleMessage: 31 queued-gameplay + 100 unknown callees; `00588570` cEditor::OnMouseDown: 29 + 87; `0058be50` cEditor::Update: 26 + 90).
- **NEEDS_RE (101)** — no decomp file at all, so the body is unknown; by population category: resource-content 56, core-gameplay-logic 27, state-management 6, engine-facing-glue 3, entity-component 3, ui-gameplay-interaction 3, serialization-persistence 1, event-callback-dispatch 1, world-system 1.
- **No runtime oracle yet.** No function is marked OBSERVED/VERIFIED (no trace_run / test_result exist yet); the Wine differential oracle is blocked on boot-stability (the exit-trigger is unknown).
- **Open v6 regions.** 163 functions parked + 7 regions under review from the UNKNOWN-HIGH adjudication (triage-v6) remain unresolved.

## 8. Recommended reconstruction ordering

Strategy **D — hybrid** (rationale in `03-dependency.json`):

- **Phase 0 — interface freeze (first).** Characterize the ~11 shared-state roots before any dependent work: `00b3d300`, `00b3d2a0`, `00b5b800`, `01021260`, `00b1fdb0`, `00b21340`, `01021300`, `01021080`, `00b25fb0`, `00ba9370` (name the singleton each returns; decomp-export them) and `00e5c780` map_int_whatever_find. Output: interface stubs + names, **not** implementations. Also fold in the 5 decomp-backed named accessors (`cGameInputManager::Get` et al.).
- **Phase 1 — the 35 ready functions.** The 6 READY + 29 READY_WITH_LOCAL_CONTEXT queue functions (all decomp-backed, all leaf-like: zero in-scope dependencies, no vtable). These are the first real reconstructed gameplay code and the first differential-test targets once the Wine oracle stabilizes.
- **Phase 2 — subsystem-first on decomp-covered clusters.** sim-cell (25 fns: 11 READY_WITH_LOCAL_CONTEXT + 14 DEPENDENCY_FIRST), editor-core (42: 1 READY + 6 READY_WITH_LOCAL + 8 DEPENDENCY_FIRST), sporepedia-online (51: 3 READY + 6 READY_WITH_LOCAL), plus the 21 small components (58 nodes) as self-contained units.
- **Phase 3 — isolated singletons as parallel work packages.** 330 isolated functions, 55 of them decomp-backed; genuinely independent (no in-scope edges).
- **Excluded throughout.** 185 LIKELY_INFRASTRUCTURE + 23 ENGINE_BOUNDARY functions (interface stubs only — e.g. `01001210`/`01001200` string/allocator helpers with 121–125 fan-out).

## 9. Explicit unknowns and uncertainties

- `sdk_name => CONFIRMED` is **name-level provenance only** (community RE headers, not EA source); a name alone can never justify READY.
- No function is marked OBSERVED/VERIFIED — no trace_run / test_result exist yet; all readiness calls are static.
- 1,598 functions (74.4%) are `unknown-needs-investigation` with region inference only; the ~1,600 unnamed `FUN_*` in the dominant core have no oracle of any kind.
- The ~10 unnamed shared-state roots return singletons whose type/layout is not yet characterized; only the 5 named `::Get` accessors have decomp evidence.
- Decomp callees are counted from the exported SDK decompilation; `unknown FUN_*` callees are the long tail that must be understood before a DEPENDENCY_FIRST target is tractable — their count per function is an estimate from the TSV, not a completeness guarantee.
- The 330 isolated functions are independent **by construction** (no in-scope gameplay edges); they may still call engine functions or shared-state roots, in which case they are not truly standalone.
- The Wine differential oracle's boot-stability exit-trigger is unknown; until it is pinned down, Phase-1 verification is unit-test-only.
- 163 parked functions + 7 review regions from triage-v6 adjudication remain open; their resolution can change the population categories above.
- The "21 small components / 58 nodes" histogram was re-derived from the xrefs TSV and **supersedes** CONTEXT.md's earlier "26 small (size 3–5)" figure.
- **Source-data note (inherited, not fabricated):** 3 queue VAs — `00e3a400`, `00e7b6c0`, `00e7d2c0` — appear in the authoritative `queue-f0e310e0-v6.json` but are **absent from the pinned 58,757-function universe** (triage-v6 jsonl) and from `functions.tsv`. They are carried through verbatim from the v6 source (a pre-existing source/queue inconsistency, likely addresses Ghidra no longer treats as functions); no caller→callee edge is attached to them and no xref was invented. They should be re-adjudicated when the v6 queue is next refreshed.
