# SDK boundary repairs (snapshot 2540f2ca)

Worker report: adjudication of the **1186 SDK VAs with no function entry**
(unique-address basis: 1663 distinct SDK VAs = 477 present + 1186 missing;
the manifest's "1188" was a raw-line double-count of dupe `0093b630`).

No Ghidra state was modified: read-only REST on `SporeApp.exe`
(`get_function_by_address` / `get_xrefs_to` / `read_memory`, plus
`disassemble_function` on thunk entries only — zero thunk containers were
found, so it was never called). No functions created, no re-analysis.
Method script: `tools/triage/repair_sdk_boundaries.py` (stdlib only;
per-VA probes cached under `/tmp/opencode/sdk-repair/probes/`).

## Artifacts

- `knowledgegraph/triage/sdk-boundary-repairs-2540f2ca.json` — full records
  (deterministic sort by `sdk_va`; `repairs_sha256`
  `0ecf6e18b00e2b2adc5db70de4a39d207d23242edd8851545126e92c1c031d81`
  covers adjudication records only; `generated_at`-style timestamps excluded).
- `knowledgegraph/triage/sdk-boundary-repairs-2540f2ca.tsv` — compact rows.
- Provenance: binary `25d42a7a…d914e`, snapshot
  `2540f2ca7cd3…45229c8`.

## Counts

| verdict | n | conf H/M/L |
|---|---|---|
| repaired-contained (mid-function SDK label → container entry) | 848 | 0 / 848 / 0 |
| repaired-thunk-alias | 0 | — |
| repaired-prologue-recoverable (defensible new boundary at VA) | 2 | 0 / 1 / 1 |
| adjudicated-tail-alias (epilogue/tail bytes, NULL) | 141 | 0 / 141 / 0 |
| adjudicated-data/vtable-slot-not-code (NULL) | 2 | 1 / 1 / 0 |
| adjudicated-dead-address (NULL) | 193 | 0 / 0 / 193 |
| **total** | **1186** | 1 / 992 / 193 |

Validation: 1186 adjudicated exactly once, no duplicate VAs, 1186 + 477 =
1663 distinct SDK addresses. All `xrefs_to` probes succeeded (zero errors).

## Would change triage classification: 800

Hypothetical reclassification under the frozen triage-v4 rules (attach the
SDK name to the repaired VA's row; new row for prologue-recoverable):

- `UNKNOWN|P3|UNKNOWN → GAMEPLAY_LOGIC|P1|CONFIRMED`: 293 (FUN_ + game-ns SDK)
- `UNKNOWN|P3|UNKNOWN → ENGINE_INTERFACE|P1|CONFIRMED`: 277
- `ENGINE_IMPLEMENTATION|P1|INFERRED → ENGINE_INTERFACE|P3|CONFIRMED`: 174
  (note the v4 XOR quirk: sdk AND vtable without decomp falls to P3 —
  triage-v5 rule question, not a repair error)
- `ENGINE_IMPLEMENTATION|P1|INFERRED → GAMEPLAY_LOGIC|P3|CONFIRMED`: 40
- `… → GAMEPLAY_SUPPORT|P3|CONFIRMED`: 10, plus 4 singletons/misc
- `adds-row` (prologue-recoverable new functions): 2
- 48 repaired-contained are classification-stable (container already
  SDK-named — 4 with the *same* name, 48 total unchanged).

**52 containers already carry a *different* SDK name** (e.g. SDK VA
`006c0580 Resource::PFRecordWrite::Write` inside container `006c0550`
`Resource::PFRecordWrite::Flush`). Attaching the missing name would
overwrite — triage-v5 needs an alias/multi-name policy before applying.

## Top evidence patterns

1. **Mid-function Property/Getter labels** (848 contained, offsets 16–5120,
   median 80; top containers hold 3–5 SDK labels each, e.g. `00830b30`,
   `00847bb0`, `008dc600`, `00b182f0`). Zero direct callers to the SDK VA in
   all 848 cases — callers target the container entry. Confidence medium
   (interior + code bytes, no independent callers).
2. **Shared epilogues** (141 tail): VA within 16 B of container end, typically
   `mov esp,ebp / pop ebp / ret` fragments (`8be55dc3…`), `ret N` (`c20400`),
   or padding runs. Conservative NULL — no triage change.
3. **Orphaned code with no container** (193 dead, all low): readable bytes but
   no function body, no callers, no prologue. Top namespaces: Simulator 42,
   UTFWin 41, App 40 (incl. an `Editors::EditorCamera` virtual cluster
   `005a21xx–005a2fxx` with SSE code bytes but no function entries —
   recommend batch review in triage-v5). `bytes=0101…` runs are alignment
   fill; unreadable/unmapped cases folded here at medium.
4. **Vtable slot that is data** (1 high): `00e62700
   App::cCellModeStrategy::HandleMessage` = vtable-ptr at `01485550`, no
   container. Plus `00fb6ca0` (float-table bytes, one data-xref).
5. **Missed functions with prologues** (2): `01056c80
   Simulator::cRepairToolStrategy::Update` (strong `57 53 8b f1` thiscall
   prologue, medium) and `00fcc1d0 App::Canvas::GetStyle` (weak single-push,
   low) — both container-less; defensible new boundaries for triage-v5 to
   create, not this worker.
6. **Dupe SDK VAs in the missing set** (2 of the 3 known dupes):
   `0093c360` (dead) and `00dde930` (contained in `00dde900`); both names
   preserved in the record. (`0093b630` has a function entry — not in scope.)

## Handoff notes for the triage-v5 worker

1. Apply the 848 `repaired-contained` SDK-name attachments first (800 change
   classification, 48 stable no-ops) — but resolve the **52 name conflicts**
   (alias policy) before overwriting any container's existing `sdk_name`.
2. Review the v4 XOR priority quirk exposed by 224 ex-`ENGINE_IMPLEMENTATION`
   rows landing at P3 despite gaining SDK names; decide whether sdk AND
   vtable (no decomp) deserves P1.
3. Create-or-reject the 2 `repaired-prologue-recoverable` boundaries
   (`01056c80` strong, `00fcc1d0` weak); creation adds triage rows.
4. Batch-review the dead `EditorCamera`/`Simulator`/`UTFWin` clusters — several
   have code-like bytes (SSE, frameless) that a prologue-scanning creation
   pass could recover; keep the 141 tail-alias and 2 data verdicts as NULL
   unless new evidence appears.
5. Re-run `tools/triage/repair_sdk_boundaries.py --no-probe` to reproduce
   byte-identical TSV/JSON from cached probes (delete
   `/tmp/opencode/sdk-repair/probes/` to force a live re-probe).
