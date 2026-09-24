# PKG-07 Cell Probe Manifest Provenance Report

> This report is a pre-repair investigation snapshot. Its BLOCKED and stale findings describe the pre-repair tree and are superseded for current disposition by `docs/analysis/future-research/pkg07-runtime-preflight-repair.md`.

**Report scope:** read-only investigation of the PKG-07 runtime-oracle Cell probe manifest and the stale address `0x116B3C04`.

**Repository state:** the working tree was already dirty before this investigation. The initial `git status --short --branch` showed branch `main` with pre-existing modified and untracked files unrelated to this report. No Spore process was launched or attached, no input was issued, no breakpoint or instrumentation was installed, no process memory was accessed, and no `SPORE/`, executable, canonical knowledge-graph file, or other repository source was modified.

## Executive finding

The authoritative Cell probe manifest is:

- `tools/observatory/probes/cell_movement.json` — the static probe definition consumed by the observatory and referenced by `tools/observatory/cell_trace.sh`.
- It has 12 probe records: 11 Cell-related candidates and one bootstrap control. The manifest has `image_base` `0x400000` and its `probes[*].rva` fields are tracer addresses in linked-VA convention, despite the field name `rva`; this is documented at `tools/observatory/probes/cell_movement.json:2-3`, `tools/observatory/probes/cell_movement.json:31-32`, and `docs/analysis/runtime-experiments.md:38`.

The stale value is **not present in any manifest `probes[*].rva` value**. It occurs in three textual fields:

1. root `description`: `tools/observatory/probes/cell_movement.json:2`.
2. `probes[name="Simulator::Cell::MovePlayerToMousePosition"].note`: `tools/observatory/probes/cell_movement.json:31-34`, specifically line 33.
3. `probes[name="cell_per_frame_FUN_00e5b2e0"].note`: `tools/observatory/probes/cell_movement.json:36-39`, specifically line 38.

The current static operand independently recorded by the PKG-07 preflight is `0x016B3C04`; see `tools/observatory/pkg07_preflight.py:23-24` and the independent target-byte interpretation check at `tools/observatory/pkg07_preflight.py:178-182`. The replacement ABI records the same current bytes and operand at `docs/REPLACEMENT-ABI.md:25-33`. The values are therefore not aliases. The current gate contract explicitly keeps the conflict blocking at `docs/analysis/future-research/pkg07-runtime-gates.md:13`, `:43`, and `:81`.

The immediate source correction is consequently limited to replacing the stale textual operand with the reviewed current operand in the three manifest fields above. The probe addresses, probe count, probe names, image base, and runtime execution plan must not be changed as part of that correction. A later gate-status update is conditional on an explicitly reviewed adjudication and a fresh preflight; simply deleting the stale string is not sufficient to promote the gate because the current validator does not pin an approved manifest hash or a complete name-to-address map (`knowledgegraph/research/implementation-review-v2/runtime-gates-review.md:24-32`).

## Manifest identity and fields

### Static probe manifest

| File/field | Current value or meaning | Provenance/role |
|---|---|---|
| `tools/observatory/probes/cell_movement.json:image_base` | `0x400000` | PE-linked image-base convention; line 3. |
| `tools/observatory/probes/cell_movement.json:probes` | 12 records | Eleven Cell-related candidates plus `entry (bootstrap control)`; lines 4-64. |
| `probes[*].rva` | Existing tracer address, effectively linked VA | The manifest itself says all values are PE-linked VAs at image base `0x400000`; line 2. The current target probe value is `0xe5b790` at line 31. This is not a true PE RVA (`0x00A5B790`). |
| `probes[*].name` | Probe identity | The target name is at line 32; the bootstrap control is at lines 61-63. |
| `probes[*].note` | Static evidence and explanatory provenance | The target and per-frame notes carry the stale global literal at lines 33 and 38. |
| root `description` | Scope, address convention, evidence claims, and runtime status | Carries the stale global literal at line 2. |

The current target record is therefore:

- probe address field: `rva: "0xe5b790"` at line 31;
- name: `Simulator::Cell::MovePlayerToMousePosition` at line 32;
- target note containing the stale operand: line 33;
- correct current linked address/RVA/offset facts are independently recorded in `docs/analysis/future-research/pkg07-runtime-gates.md:13` and `docs/REPLACEMENT-ABI.md:19-33`.

The per-frame record is:

- probe address field: `rva: "0xe5b2e0"` at line 36;
- name: `cell_per_frame_FUN_00e5b2e0` at line 37;
- stale global operand in its explanatory note at line 38.

### Separate run-output manifest

`tools/observatory/cell_trace.sh` also creates a per-run output manifest named `manifest.json`. That is not the static probe manifest and does not contain the stale address. Its schema and fields are defined at `tools/observatory/cell_trace.sh:142-187`:

- `schema: "observatory-s5-celltrace-1"` at line 171;
- `run_id` at line 172;
- `scenario: "cell_movement"` at line 173;
- `outcome` at line 174;
- window geometry at line 175;
- `trace.probe_set`, JSONL path, duration, `cell_stage_reached`, and sorted per-probe event counts at lines 176-182;
- machine-lock status and replay/provenance flags at lines 183-185.

The run manifest only names the probe set and counts events. It does not carry probe addresses or the stale global literal, so it requires no stale-address correction. Its historical output records must not be rewritten to imply a new runtime result.

### Separate startup manifest

`tools/observatory/probes/main_menu.json` is a separate seven-probe startup/bootstrap manifest. Its schema and address convention are at lines 1-4 and its probe records are at lines 5-20. It contains no `0x116B3C04` reference. The PKG-07 preflight reads it independently at `tools/observatory/pkg07_preflight.py:185-192`; it is not the Cell manifest and requires no update for this issue.

## Why the preflight blocks

`tools/observatory/pkg07_preflight.py` treats the manifest as blocked if either a parsed probe value equals the stale operand or the stale literal appears anywhere in the manifest text:

- the current and stale constants are `GLOBAL_OPERAND = 0x016B3C04` and `STALE_GLOBAL_OPERAND = 0x116B3C04` at `tools/observatory/pkg07_preflight.py:23-24`;
- the manifest parser returns both parsed address values and a `stale_global_operand` boolean at `tools/observatory/pkg07_preflight.py:87-122`;
- the Cell check reads exactly `tools/observatory/probes/cell_movement.json` and requires 12 probes at `tools/observatory/pkg07_preflight.py:193-201`;
- the current binary interpretation is checked independently at lines 178-182.

Because `0x116B3C04` is absent from the parsed `rva` values, the current block is caused by the text scan hitting the three manifest prose fields. That is intentional fail-closed behavior, not evidence that a probe breakpoint is planted at `0x116B3C04`.

The validator also has a separate identity weakness: it reports the manifest hash but does not compare it to an approved expected hash, and it checks a required-name subset rather than the complete approved name-to-address map (`tools/observatory/pkg07_preflight.py:87-121`; `knowledgegraph/research/implementation-review-v2/runtime-gates-review.md:24-32`). A stale-text removal alone must therefore be followed by a new hash/address contract or a separately approved adjudication record.

## Git and history provenance

### Timeline

1. **Pre-existing analysis snapshot:** the parent of the Obj32 commit contains `tools/re/data/ghidra_snapshot_cell_movement.json` with `image_base` `0x01100000` and a note saying `RVA = address - image_base` at lines 1-5 of the parent revision. The current revision corrected that snapshot metadata to `image_base` `0x400000` and explicitly documents the correction at `tools/re/data/ghidra_snapshot_cell_movement.json:1-5` and `:190`. The parent snapshot does not contain the literal `0x116B3C04`.

2. **Obj32 introduction:** commit `1c3035b5afae8afa930d5cf89d5613e14a545595`, authored 2026-09-21 21:22:52 +0200, titled `Obj32: Cell Stage runtime observation + address-mapping correction`, introduced `tools/observatory/probes/cell_movement.json` as a new 66-line file. The commit diff shows all three stale occurrences in the file at the time of introduction. `git blame` assigns lines 2, 33, and 38 to this commit.

3. **Same Obj32 historical report:** the same commit introduced `docs/analysis/CELL-RUNTIME-OBSERVATION.md`. Its address-mapping section says the old snapshot base and RVA arithmetic were wrong at lines 21-33, but its body still records `mov eax,[0x116b3c04]` at lines 35-40. This is the origin of the historical record’s stale claim; the commit corrected function-address mapping but did not correct the global operand in the newly created manifest or historical report.

4. **Correct static ABI record:** commit `9734cc39dd383ba855d3a91fb25537a13dbff3b9`, authored 2026-09-21 23:16:02 +0200, added `docs/REPLACEMENT-ABI.md`. It records the entry bytes and decodes `mov eax,[0x016b3c04]` at lines 25-33 and identifies `sCellGame` at `0x16b3c04` at lines 40-43. This is the later static record that disagrees with the Obj32 prose.

5. **Historical S5 run:** commit `50dc470865cf9c3e4d684efb09d68145f0c8bd5f`, authored 2026-09-22, added the S5 runtime evidence and `cell_trace.sh`; it did not modify the Cell probe manifest. Its run reports are historical negative evidence, not a correction of the static manifest.

6. **Current HEAD:** `ef597af7737b8e2f080f5b20ad163f13513a0703` is current `HEAD`. `git log --follow` shows no later commit editing `tools/observatory/probes/cell_movement.json`; the only manifest history is the Obj32 introduction. The current preflight and the current `pkg07-runtime-gates.md` are untracked working-tree artifacts, so they have no independent git history.

### Root cause of staleness

The proven fact is that the stale literal entered the repository in the Obj32 manifest introduction and was never corrected there. The commit’s surrounding text indicates that the stale value came from the older, internally inconsistent address-mapping/decompilation narrative, but the repository does not contain a direct patch or a surviving parent revision that proves the exact hand-transcription path. In particular:

- the parent snapshot has the bad `0x01100000` base but does not contain `0x116B3C04`;
- the committed decompiler capture `tools/re/data/decompiled/MovePlayerToMousePosition.c:1-17` uses the symbolic `Simulator__Cell__sCellGame` and does not contain the stale literal;
- the corrected current snapshot contains no stale literal;
- therefore the stale value cannot be attributed to a currently reproducible `rva` field or a surviving machine-generated global-address field. It is a stale hand-authored/prose value introduced during Obj32’s address-mapping work.

The value is not a runtime relocation, module-base alias, or alternate PE RVA in the current records. The current gate and replacement records explicitly prohibit treating it as an alias (`docs/analysis/future-research/pkg07-runtime-gates.md:13`, `docs/analysis/original-exe-replacement.md:66`, and `knowledgegraph/research/runtime-oracle.json:155-162`).

## Exact records requiring update

### A. Required source-manifest correction

These are the only records that must change to remove the stale literal from the authoritative probe manifest:

| Record | Current location | Required correction |
|---|---|---|
| Root description | `tools/observatory/probes/cell_movement.json:2` | Replace the textual `0x116b3c04` with the reviewed current static operand `0x016B3C04`, while preserving the evidence/historical wording as appropriate. |
| Target probe note | `tools/observatory/probes/cell_movement.json:31-34` | Replace the textual operand in the `mov eax,[...]` explanation; do not change the probe’s `rva` value. |
| Per-frame probe note | `tools/observatory/probes/cell_movement.json:36-39` | Replace the textual operand in the `mov eax,[...]` explanation; do not change the probe’s `rva` value. |

Do **not** change:

- `image_base` at `tools/observatory/probes/cell_movement.json:3`;
- the target probe’s `rva` at line 31;
- the per-frame probe’s `rva` at line 36;
- the 12-probe count or any probe name;
- the separate `main_menu.json` or generated S5 run-manifest schema.

After a source correction, the manifest must be reviewed as a new content artifact. The current helper’s emitted hash must be recorded and compared to an explicitly approved expected hash; the current code does not provide that approved pin.

### B. Conditional current synthesis/status records

These records currently state that the manifest is stale or that the gate is blocked. They should be updated only after the source correction is reviewed and a fresh static preflight is actually rerun:

- `docs/analysis/future-research/pkg07-runtime-gates.md:13`, `:43`, `:75`, `:81`, and `:121` — replace the conflict/blocked wording with the approved adjudication result, without deleting the rule that old historical material is not an alias.
- `docs/analysis/implementation-status-v2.md:47-51` — update the M0 blocking fact and preflight result only after the new preflight result exists.
- `docs/analysis/implementation-review-v2.md:35-45` and `:123` — update GATE-01 and the validation disposition after the corrected manifest is reviewed.
- `knowledgegraph/research/implementation-review-v2/runtime-gates-review.md:14-22` and `:68-72` — revise GATE-01/disposition from intentionally blocked to the result of the reviewed correction; retain GATE-02 because the hash/address-pinning weakness is independent of the stale literal.
- `docs/analysis/original-exe-replacement.md:66` and `:112` — update the unresolved-conflict language only after the adjudication record identifies the current bytes/module mapping as the resolution.
- `docs/analysis/runtime-experiments.md:38` and `:691` — update the current conflict/status summary; preserve the statement that runtime reachability is absent.
- `docs/analysis/runtime-oracle-plan.md:110` and `:635` — replace the active unresolved-conflict requirement/rejection condition with the reviewed static adjudication result; do not convert the negative runtime plan into a pass.
- `knowledgegraph/research/semantic-blueprint.json:507` — update only the explicit-resolution record if the adjudication is formally promoted; preserve the historical value as a provenance field rather than deleting it.
- `knowledgegraph/research/runtime-oracle.json:155-162`, `:331-337`, `:432-436`, and `:1705` — these are structured current records for the conflict, missing adjudication, static-global conflict rule, and phase requirements. Update their status/rule/requirement fields together only after the adjudication is accepted. A suitable preservation model is: current value `0x016B3C04` = resolved current static operand; older value `0x116B3C04` = retained historical artifact, not an alias.
- `knowledgegraph/research/runtime-oracle/input-synthesis.md:87` and `:288` — update the current conflict summary/requirement after adjudication while retaining the historical-source distinction.
- `knowledgegraph/research/runtime-oracle/replacement-observability.md:40`, `:92`, and `:823` — update the current status/rule records after adjudication; retain a historical-source note if the provenance ledger requires it.

The generated per-run `manifest.json` schema at `tools/observatory/cell_trace.sh:170-187` does not require an address update. Historical run outputs should not be edited; new runs, if ever authorized, would receive a new run ID and manifest.

### C. Historical artifacts that should be preserved, not silently rewritten

- `docs/analysis/CELL-RUNTIME-OBSERVATION.md:35-40` is the historical Obj32 runtime record. Its `0x116b3c04` text is historically attributable to the commit that created it. Preserve the old record and, if needed, add a separate erratum/provenance record; do not retrofit the historical run report into current canonical truth.
- `docs/analysis/CELL-RUNTIME-OBSERVATION.md:42-99` and `docs/devlog/018-s5-cell-runtime-evidence.md` are historical runtime evidence. They establish negative reachability under recorded conditions, not a current manifest identity.
- `tools/re/data/ghidra_snapshot_cell_movement.json:1-5` and `:190` are the corrected current snapshot metadata. They already say the PE/Ghidra base is `0x400000` and do not contain the stale literal; no stale-address update is needed.
- `tools/re/data/decompiled/MovePlayerToMousePosition.c:1-17` is a decompiler-reference artifact. It contains the symbolic global name but not the stale literal; it should remain evidence-only and unchanged.
- `docs/analysis/dossiers/cell-movement.md:46-52` and the current runtime-oracle records already describe the global/field evidence without accepting `0x116B3C04` as an alias. They should not be bulk-replaced merely because the old literal appears in the manifest.
- The corrected replacement ABI at `docs/REPLACEMENT-ABI.md:25-43` is current canonical static evidence for the target and operand. It is not stale and requires no correction for this issue.

## Final classification

- **Current canonical static truth:** `0x016B3C04` as encoded by the current target bytes and recorded in `docs/REPLACEMENT-ABI.md:25-43`, `docs/analysis/future-research/pkg07-runtime-gates.md:13`, and `tools/observatory/pkg07_preflight.py:178-182`.
- **Current canonical manifest with a stale field:** `tools/observatory/probes/cell_movement.json`, specifically root `description` and two `note` fields at lines 2, 33, and 38.
- **Historical artifact with the same stale literal:** `docs/analysis/CELL-RUNTIME-OBSERVATION.md:35-40`, introduced in Obj32; preserve as historical provenance.
- **Current dependent records:** gate/review/status/structured-oracle records listed in section B; update only after an approved static adjudication and fresh preflight.
- **Separate manifests:** `main_menu.json` and the S5 generated run manifest are not stale-address targets.
- **Safe next action:** review and change the three manifest prose fields, record the new manifest hash and complete name-to-address contract, rerun only the non-runtime preflight after authorization to do so, then update the dependent current status records. No runtime evidence is produced by this report and no gate is promoted here.
