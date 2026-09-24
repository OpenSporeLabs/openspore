# UNKNOWN-HIGH resolution — adjudication report (triage-v6, snapshot f0e310e0)

Author: SA-6. Read-only analysis; no DB writes, no `SPORE/` access, nothing marked
OBSERVED/VERIFIED. All numbers below are reproducible from the committed artifacts
cited in §11. Binary sha256 `25d42a7a…d914e` (GOG 3.1.0.22, x86:LE:32, image base
0x400000). Snapshot `f0e310e0` (triage-v5) over 58,757 functions.

---

## 1. Scope & method

The 862 `UNKNOWN-HIGH` rows (from the §13 debt map: the `connectivity=high` subset of
the 48,296 UNKNOWN functions, all high call-type fan-in/fan-out, none with a decomp
file) were adjudicated in three sequential sub-agent passes:

- **SA-2 (adjudicate).** 5 starting hubs decompiled, then call-graph + vtable-neighbor
  expansion. 921 working rows = the 862 HIGH VAs + 59 adjacent; 44 of the 862 are
  Ghidra non-function addresses (no triage row — they appear only in this dataset).
- **SA-3 (propagate).** Category propagation to the remaining UNKNOWN functions whose
  callers share a *single* category. 7,955 rows; 7 regions were blocked (see §7).
- **SA-4 (attribute).** 180-region subsystem attribution map; the 7 misattributed
  regions are flagged `weak` + `review` and were blocked from propagation.

Evidence levels follow `docs/RE-DOSSIER-SCHEMA.md` (7-level scale). The strongest
available evidence per row is used; nothing is marked OBSERVED/VERIFIED.

## 2. Verdict / before–after

The UNKNOWN-HIGH tier is resolved from the top: **862 → 699 resolved / 163 parked
UNKNOWN**.

| | before | after |
|---|---|---|
| UNKNOWN-HIGH total | 862 | 0 (699 resolved + 163 parked) |
| Resolved (category assigned) | 0 | 699 |
| Parked (justified UNKNOWN) | 862 | 163 |
| Propagated neighbors (SA-3) | — | 7,955 |
| v6 non-UNKNOWN rows (whole binary) | 18,283 (v5) | 19,041 |

Whole-binary `by_category` after v6: ENGINE_IMPLEMENTATION 11,585 / ENGINE_INTERFACE
1,227 / GAMEPLAY_LOGIC 1,656 / GAMEPLAY_SUPPORT 493 / THIRD_PARTY_OR_RUNTIME 4,080 /
UNKNOWN 39,716 (sum 58,757 ✓). `by_evidence`: APPROX 1,500 / CONFIRMED 1,167 /
INFERRED 12,371 / SUPPORTED 3,836 / UNKNOWN 39,883 (sum 58,757 ✓). No OBSERVED/VERIFIED
rows exist anywhere.

## 3. Resolution breakdown (699 resolved)

By **category**: ENGINE_IMPLEMENTATION 396 / GAMEPLAY_LOGIC 194 / ENGINE_INTERFACE 61 /
GAMEPLAY_SUPPORT 45 / THIRD_PARTY_OR_RUNTIME 3 (sum 699 ✓).

By **evidence**: SUPPORTED 414 / INFERRED 285 (sum 699 ✓). None CONFIRMED — none of the
862 carries an SDK name, so name-level CONFIRMED is structurally impossible here.

By **ownership**: gameplay_affinity 614 / engine_runtime 83 / third_party_hint 2 (sum
699 ✓) — consistent with the 747 gameplay-affinity rows flagged in §13.

By **subsystem** (top): Simulator 171 / Unknown 299 / App 64 / Editor 44 / UTFWin 31 /
IO 24 / Terrain 16 / Math 14 / Clock 6 / Palettes 5 / Resource 5 / Sporepedia 5 /
ArgScript 4 / GameGlobal 3 / Runtime 3 / LocalizedString 1 / Space 1 / Pollinator 1.
(The 299 `Unknown`-subsystem rows are resolved *category*-wise via caller/vtable
evidence even though their subsystem label stayed `Unknown`.)

## 4. Parked breakdown (163 justified UNKNOWN)

All 163 parked rows share the single reason **`insufficient evidence`** — their
neighbors did not yield a single consistent category under the SA-3 rule, so no
classification is defensible. These are *clean* UNKNOWNs, not forced calls: each is
excluded from propagation and the v6 rows carry the parked rationale. This is the
non-fabrication outcome (see §9): 163 HIGH remain UNKNOWN *with* justification rather
than being stretched into a category.

## 5. Hubs investigated & dossiers

5 starting hubs were decompiled and expanded (all UNKNOWN, P3, gameplay_affinity, high
connectivity). 15 per-hub dossiers landed in `docs/analysis/dossiers/unknown-high/`:

| VA | purpose (adjudicated) | category / evidence |
|---|---|---|
| 00c32cd0 | cEmpire ID-color pick: most-distinguishable of 12 palette colors vs other empires' cached colors | GAMEPLAY_LOGIC / SUPPORTED |
| 00e780a0 | Cell object-pool lifecycle: detach avatar ref, release old GFX+assoc, rebuild on stage-scale change, `cObjectPool_::CreateObject` | GAMEPLAY_LOGIC / SUPPORTED |
| 00e39ab0 | Space event record-pair builder: 2 records {object, cellIDs, ms timestamp, −10 slot sentinel, IDs, float3s}; positions from cTribe | GAMEPLAY_LOGIC / INFERRED |
| 00a4e9c0 | UTFWin pdtk text-widget sync: wrap text, size widget, drive pdtk commands (text_new/select/focus/icursor), blue/black selection | ENGINE_IMPLEMENTATION / SUPPORTED |
| 00bb4af0 | cStarManager star-system regen: no-planet + timing check → record time, erase from pending list, reset state, `GeneratePlanetsForStar` | GAMEPLAY_LOGIC / SUPPORTED |

Supporting dossiers (accessor/family members): 4 `sim-singleton-accessors` (15-member
4-byte global block @0x167eac0+), 3 `space-player-data-accessors` (sSpacePlayerData
+0x4/+0x10/+0x18 id +0x1c cached-pointer validator), `sim-object-lookup-strategy`
(−1 sentinel), `gamemode-state-player-id` (+0x54 field accessor), `message-handler-registration`
(5 code pointers, 0xC-stride linked list). Every dossier records purpose, state
read/write, struct fields, decomp snippet, callers, key callees, vtable relationship,
and the single real gap. All are `replacement: partial`; none is marked
implemented/replacement-tested/runtime-validated.

## 6. Propagation (SA-3) — bounded & correct

SA-3 propagates a category to a remaining UNKNOWN function **only when all of its
callers share a single category** (single-category caller rule). 7,955 rows propagated;
87 carry a `propagated_blocked` flag and 7 regions were fully blocked (their callers
span multiple categories). This keeps propagation conservative: a row is never given a
category on the strength of a mixed caller set. v6 records `propagated=7,868`
(7,955 adjudicated-side minus the blocked/already-resolved overlap).

## 7. Region attribution (SA-4) — 180 regions, 7 review

SA-4 produced a 180-region subsystem map (each ~4KB-aligned code region → subsystem +
adjudicated/propagated member counts). 7 regions are flagged `review` because their
members were misattributed (callers span multiple subsystems): `0x438000, 0x488000,
0x4a6000, 0x4df000, 0x550000, 0xc24000, 0xc32000`. These are marked `weak` and were
**blocked from propagation**, so no misattribution leaked into the resolved set. The
`0xc32000` region is the cEmpire ID-color hub (§5); `0xc24000` is adjacent Simulator
gameplay.

## 8. Evidence-priority application

Every resolved row was classified using the strongest rung of the ladder that fired:
(1) SDK association → none (no SDK names in the 862); (2) vtable membership; (3) known
structure ownership (cEmpire 344B, cCellObjectData 920B, cCellGame 20964B, cTribe
6624B, cStarRecord, sSpacePlayerData); (4) caller/callee relations (the main driver of
the 299 `Unknown`-subsystem resolutions); (5) repeated neighborhoods (the 15-member
accessor block, the sSpacePlayerData family); (6) strings/constants (pdtk command
grammar); (8) decomp semantics. Where no rung above heuristic fired, the row was parked
(§4). No single weak heuristic was ever used alone to assign a category.

## 9. Non-fabrication / justified-UNKNOWN policy

A clean justified UNKNOWN is preferred over a forced classification. Concretely: the
163 parked rows are reported as UNKNOWN *with* the "insufficient evidence" rationale
rather than being stretched; the 285 INFERRED and 414 SUPPORTED rows each carry the
evidence that justifies their ceiling. No row was marked CONFIRMED/OBSERVED/VERIFIED
(no SDK name, no runtime evidence exists). This is the intended, auditable outcome.

## 10. v6 clusters + queue (288 → 368)

- **Clusters** `clusters-f0e310e0-v6.json`: the 20-cluster v4 taxonomy recomputed from
  triage-v6 rows (cluster sum check = 58,757 ✓) + the 180-region attribution map. 5
  named clusters carry the resolved hubs.
- **Queue** `queue-f0e310e0-v6.json`: **368 rows** = 207 v4 verbatim + 81 v5-promoted
  + 80 new v6 unknown-high reconstruction candidates. Counts: candidate 180 /
  implemented 35 / queued 153. Ordering (frozen): queued(P0-rescued, P0-engine,
  P1-supported) > candidate(P2) > implemented(Cell reference) > v5-promoted (family
  distinct-sdk-func count desc, then va) > v6 unknown-high candidates
  (`replacement_candidate yes` first, then in_degree desc, then va).
- `new_reconstruction_candidates=80`, `new_gameplay_candidates=1570` (v6 adds 1,570
  gameplay rows across the whole binary, 80 of which enter the reconstruction queue).

## 11. Artifacts & provenance

Authoritative inputs (read-only): `triage-f0e310e0.jsonl` (58,757 rows),
`debtmap-f0e310e0.json` (48,296 UNKNOWN; 862 HIGH), `xrefs-2540f2ca.tsv` (223,704
edges). Outputs (this phase):

- `knowledgegraph/triage/unknown-high-investigation-f0e310e0.json` — 862 rows,
  `clusters_resolved` (180), 7 `flagged_review_regions`, 5 `hubs_investigated`,
  `resolved_breakdown`/`parked_breakdown`, `new_reconstruction_candidates=80`.
- `knowledgegraph/triage/summary-f0e310e0.triage-v6.json` — full v6 projections
  (`by_category`/`by_evidence`/`by_priority`/`by_subsystem`, `v6` block).
- `knowledgegraph/triage/clusters-f0e310e0-v6.json` — 20-cluster taxonomy (sum
  58,757) + 180-region map (7 review).
- `knowledgegraph/triage/queue-f0e310e0-v6.json` — 368-row queue, rank 1 =
  `005737d0 Editors::cEditor::OnMouseMove` (P0, CONFIRMED, cluster `editor-core`).
- 15 dossiers in `docs/analysis/dossiers/unknown-high/`.

Snapshot sha256 `f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b`;
binary sha256 `25d42a7a48431d37524656d669354108272047e7e507391c686299122c1d914e`.
Generators are stdlib-only and deterministic. No v4/v5 file was modified; no DB write.

## 12. Self-assessment (6 questions)

1. **Completeness — were all 862 UNKNOWN-HIGH VAs adjudicated?** **Yes.** 862 =
   699 resolved + 163 parked; zero left unclassified. (44 of the 862 are
   Ghidra non-function addresses, tracked in the dataset only.)
2. **Evidence discipline — is every resolved row capped at its strongest available
   level, with nothing OBSERVED/VERIFIED?** **Yes.** 414 SUPPORTED + 285 INFERRED
   only; 0 CONFIRMED (structurally impossible — no SDK names), 0 OBSERVED, 0 VERIFIED.
3. **Non-fabrication — are the 163 parked rows cleanly justified, not forced calls?**
   **Yes.** All 163 carry the single `insufficient evidence` rationale and are excluded
   from propagation; none was stretched into a category.
4. **Propagation soundness — is SA-3 bounded and were misattributions blocked?**
   **Yes.** Single-category caller rule only (7,955 rows); 87 blocked-flag rows + 7
   `review` regions were excluded from propagation so no mixed-caller set leaked.
5. **Traceability — is every number reproducible from committed artifacts?** **Yes.**
   All §2/§3/§4 figures sum-check against the v6 summary and the investigation JSON;
   cluster sum = 58,757; queue = 368 (207+81+80); shas pinned in §11.
6. **Downstream readiness — does rank-1 of the v6 queue correctly consume the
   resolution for the next campaign?** **Yes.** `queue-f0e310e0-v6.json` rank 1 is
   `005737d0 Editors::cEditor::OnMouseMove` (P0/CONFIRMED/`editor-core`), the entry
   point for the mass semantic reconstruction campaign (a separate, not-yet-started
   task). The 163 parked and 7 `review` regions are the open residuals.
