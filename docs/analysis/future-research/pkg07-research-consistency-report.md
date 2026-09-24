# PKG-07 Research-Artifact Consistency Audit

> This report is a pre-repair investigation snapshot. Its BLOCKED and stale findings describe the pre-repair tree and are superseded for current disposition by `docs/analysis/future-research/pkg07-runtime-preflight-repair.md`.

**Audit date:** 2026-09-24
**Scope:** PKG-07 Cell movement, runtime-oracle research, Cell probe manifests, JSON records, decompilation/dossier references, and related documentation for `0x116B3C04`, `0x016B3C04`, `Simulator::Cell::MovePlayerToMousePosition`, and the Cell probe address set.
**Mode:** read-only audit. The only write made by this task is this report.
**Runtime boundary:** no game launch, attachment, instrumentation, input, process-memory read/write, binary modification, `SPORE/` modification, or canonical knowledge-graph write was performed.

## Executive conclusion

The repository is **not internally consistent yet**, but the inconsistency is localized and fail-closed:

1. The canonical executable bytes and current read-only static Ghidra analysis identify the target global operand as **`0x016B3C04`**. The current Ghidra image has 1,121 xrefs to that address and no xrefs to `0x116B3C04`; the latter is outside the current image blocks.
2. The active Cell probe manifest still contains the older literal **`0x116B3C04` in three places** and an independent stale helper-note operand **`0x115A758C`** at line 53. The preflight currently rejects only the former, so it correctly returns `overall=BLOCKED` for `cell_probe_manifest` and `runtime_status`, but it would not catch the second typo after only the first three literals were corrected.
3. The static address question is now **statically resolved in this audit**, but the repository's active manifest and status artifacts have not been reconciled. The old value is not an alias and must not be retained as an accepted fallback. Existing historical and pre-correction review records should remain as history; current status/conflict fields require a new dated reconciliation after the manifest is corrected.
4. A second, separate consistency defect remains in several active research records: the physical movement write is flattened as `sCellGame+0x5270`, while the current static disassembly contract is **`byte [u32[sCellGame+0x5190]+0xE0]`**. The raw decompiler capture and dated dossier are historical evidence and should not be rewritten; active plans, ABI records, and derived research records need a coordinated correction/regeneration.
5. The target identity and address arithmetic are otherwise consistent: linked VA `0x00E5B790`, true PE RVA `0x00A5B790`, file offset `0x00A5AB90`, entry bytes `a1 04 3c 6b 01`, direct call site `0x00E8083B`, continuation `0x00E80840`, and known direct caller `FUN_00E806B0`. The current Ghidra static function body also confirms `FUN_00E4CE40` reads `0x015A758C`, not `0x115A758C`.

**Disposition:** PKG-07 remains `NOT_RUN / BLOCKED`; the static address is resolved, but the active manifest, preflight identity contract, and dependent current records are not yet reconciled. No runtime, ABI, Cell-reachability, field-ownership, or original-compatibility claim is supported by this audit.

## 1. Audit inputs and method

The audit searched the current repository tree for:

- `0x116B3C04` / `116b3c04` in all relevant Markdown, JSON, Python, manifest, and probe records;
- `0x016B3C04` / `016b3c04`;
- `Simulator::Cell::MovePlayerToMousePosition`, `0xE5B790`, `0xA5B790`, `0xA5AB90`;
- related Cell probe functions `FUN_00E806B0`, `FUN_00E5B2E0`, `FUN_007C4900`, `FUN_00B721D0`, `FUN_00E4CE40`, and `FUN_0069B600`;
- `sCellGame` fields `+0x411C`, `+0x5158`, `+0x5190`, `+0x515C`, `+0x51E0`, and the disputed moving-field forms `+0x5270` and `+0x5190+0xE0`;
- the main and Cell probe manifests, preflight helper, runtime-oracle JSON/Markdown synthesis, implementation reviews, PKG-07 future-research documents, static dossier/decompiler records, and current replacement/reconstruction records;
- the independent helper operand `0x115A758C` and current static Ghidra disassembly of `FUN_00E4CE40`;
- current static Ghidra program state and xrefs for `0x016B3C04`, `0x116B3C04`, `0x015A758C`, `MovePlayerToMousePosition`, and `App::cAppSystem::InitPlugins`.

CodeGraph was consulted first as required, but reported that its watcher was disabled and its index was stale. All conclusions below were therefore verified against the current on-disk files and read-only static Ghidra. The current CodeGraph state must not be used as evidence for this report.

## 1a. Independent static Ghidra adjudication

The open static program is `SporeApp.exe` with image base `0x00400000`. Read-only Ghidra queries were used only for static image evidence; no process was attached and no process memory was accessed.

- `Simulator::Cell::MovePlayerToMousePosition` is a current function at `0x00E5B790`, body ending at `0x00E5BA01`.
- Its entry instruction bytes decode to `mov eax, dword ptr [0x016B3C04]`.
- `0x016B3C04` has 1,121 current Ghidra xrefs; `0x116B3C04` has zero current Ghidra xrefs.
- The current image blocks place `0x016B3C04` in `.data`; `0x116B3C04` is outside the listed current image blocks.
- `FUN_00E4CE40` is a current function at `0x00E4CE40`. Its instruction at `0x00E4CE44` is `MOV ECX, dword ptr [0x015A758C]`; the manifest's `0x115A758C` is a separate stale transcription.
- `App::cAppSystem::InitPlugins` is a current function at `0x007E93D0` with body `0x007E93D0..0x007E9440`; the main-menu note claiming that the address is approximately 384 bytes inside an unrelated body is no longer current static provenance.
- `entry` is a current static function at `0x011E11A0`, consistent with the legacy linked-VA probe field and true PE entry RVA `0x00DE11A0`.

These queries make the static adjudication high confidence, but they do not establish a live relocated address, module load base, Cell reachability, field values, or runtime behavior.

## 2. Verified target identity and arithmetic

| Field | Current value | Assessment |
|---|---:|---|
| Binary | `SPORE/SporeBin/SporeApp.exe`, GOG 3.1.0.22 | `VERIFIED` by current preflight; SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`; size `20,454,960` |
| Architecture | x86-LE-32 PE32/i386 | `VERIFIED` |
| Preferred image base | `0x00400000` | `VERIFIED` |
| Target symbol | `Simulator::Cell::MovePlayerToMousePosition` | SDK name `CONFIRMED`; address/body evidence `SUPPORTED` |
| Target linked VA | `0x00E5B790` | `VERIFIED_STATIC` |
| True PE RVA | `0x00A5B790` | `0x00E5B790 - 0x00400000`; `VERIFIED` |
| File offset | `0x00A5AB90` | `.text` mapping; `VERIFIED` |
| Entry bytes | `a1 04 3c 6b 01` | `VERIFIED` by current preflight |
| Entry decode | `mov eax, dword ptr [0x016B3C04]` | `VERIFIED_STATIC`; little-endian operand bytes are `04 3c 6b 01` |
| Direct call site | linked `0x00E8083B`, PE RVA `0x00A8083B` | `VERIFIED_STATIC`; bytes `e8 50 af fd ff` decode to target |
| Continuation | `0x00E80840` | `VERIFIED_STATIC`; call displacement arithmetic passes |
| Known direct caller | `FUN_00E806B0` | `VERIFIED_STATIC` for the bounded direct xref; dynamic callers remain unknown |
| Static ABI | x86-32 cdecl `void(float)` | SDK return/parameter identity; stack/callee-saved/RET evidence is static, not live |
| Plain return | `0x00E5BA01` | `VERIFIED_STATIC` in the current replacement contract; preflight currently reports ABI as asserted rather than independently disassembled |

The old global value is numerically different from the current operand by `0x10000000`:

```text
0x116B3C04 != 0x016B3C04
```

The `0x16b3c04` spelling in `docs/REPLACEMENT-ABI.md:42` is only a leading-zero formatting variant of `0x016B3C04`; it is not the stale `0x116B3C04` value.

## 3. Cell probe manifest audit

### 3.1 `tools/observatory/probes/cell_movement.json`

**Status:** syntactically valid, 12 probes, `image_base` `0x400000`, current manifest SHA-256 `02e60089e831f89c750c3d2c7180185147d7cebd4590dbc50343947eb47d8977`.

**Blocking stale records:**

| Location | Current text | Required action |
|---|---|---|
| `tools/observatory/probes/cell_movement.json:2` | description says `sCellGame global 0x116b3c04` | Replace only after static adjudication/review; use the current candidate `0x016b3c04` if that adjudication approves the committed bytes. |
| `tools/observatory/probes/cell_movement.json:33` | movement probe note says `mov eax,[0x116b3c04]` | Same exact note update; do not treat as an alias. |
| `tools/observatory/probes/cell_movement.json:38` | per-frame helper note says `mov eax,[0x116b3c04]` | Same exact note update; preserve the function address `0xe5b2e0` and `+0x411C` meaning. |
| `tools/observatory/probes/cell_movement.json:53` | camera-mode helper note says `mov ecx,[0x115a758C]` | Correct to `mov ecx,[0x015a758c]`; this is an independent stale operand not currently rejected by the preflight. |

The current preflight output is:

```text
canonical_executable       PASS
binary_hash                PASS
pe_identity                PASS
pe_mapping                 PASS
target_bytes               PASS
call_bytes                 PASS
call_decode                PASS
binary_interpretation      PASS
static_abi                 PASS
caller_continuation        PASS
main_menu_probe_manifest   PASS
cell_probe_manifest        BLOCKED
python_test_sources        PASS (compile-only)
dry_run_contracts          PASS (token-presence-only)
runtime_status             BLOCKED
overall                    BLOCKED
runtime_launched           false
process_memory_read        false
process_memory_written     false
canonical_kg_written       false
```

**Important validator limitation:** `tools/observatory/pkg07_preflight.py:87-121` validates JSON shape, image base, probe count, duplicate names, and a required-name subset, then reports a hash. It does **not** compare an approved expected manifest hash or the complete name-to-address map. After the three literal corrections, a wrong probe value could still pass this helper. This is the existing `GATE-02` finding in `knowledgegraph/research/implementation-review-v2/runtime-gates-review.md:24-32`; it must not be mistaken for evidence that the corrected manifest is fully hash-pinned.

### 3.2 Probe-field convention and related addresses

The `cell_movement.json` field named `rva` is intentionally a **linked VA** for the legacy tracer, not a true PE RVA. The convention is consistent with:

- `tools/observatory/probes/main_menu.json:3-19`;
- `tools/observatory/probe_tracer.cpp:15-16`;
- `knowledgegraph/research/runtime-oracle.json:148-155`;
- `docs/analysis/runtime-oracle-plan.md:80-105`.

Under that convention, the Cell manifest values are internally coherent:

| Probe | Manifest `rva` field | True PE RVA | Result |
|---|---:|---:|---|
| `App::cCellModeStrategy::Update` | `0xE80980` | `0xA80980` | consistent linked-VA field |
| `cell_update_body_FUN_00e806b0` | `0xE806B0` | `0xA806B0` | consistent |
| `App::cCellModeStrategy::OnKeyDown` | `0xE818F0` | `0xA818F0` | consistent |
| `App::cCellModeStrategy::OnMouseMove` | `0xE51010` | `0xA51010` | consistent |
| `App::cCellModeStrategy::OnMouseWheel` | `0xE7D660` | `0xA7D660` | consistent |
| `MovePlayerToMousePosition` | `0xE5B790` | `0xA5B790` | consistent |
| `cell_per_frame_FUN_00e5b2e0` | `0xE5B2E0` | `0xA5B2E0` | consistent; note is stale only in its global literal |
| `cam_light_origin_FUN_007c4900` | `0x7C4900` | `0x3C4900` | consistent |
| `player_getter_FUN_00b721d0` | `0xB721D0` | `0x7721D0` | consistent |
| `cam_mode_getter_FUN_00e4ce40` | `0xE4CE40` | `0xA4CE40` | consistent |
| `face_travel_orient_FUN_0069b600` | `0x69B600` | `0x296B600` | consistent as a linked VA; not a Cell-specific marker |
| `entry (bootstrap control)` | `0x11E11A0` | `0xDE11A0` | consistent with `main_menu.json`; true PE entry point is `0xDE11A0` plus image base |

The main-menu manifest passes the current shape check with 7 probes and SHA-256 `5236c7f9a5be37ba0c775f34dcd4537c2b414eda4b72df34220c19bea42e025c`.

## 4. Exact active records to update in a future reviewed change

No files in this section were edited by this task. These are the active/current records that would need a coordinated update after a static adjudication, followed by regenerated hashes/reviews and a fresh preflight. They must not be updated piecemeal while leaving the conflict/gate records stale.

### 4.1 Manifest and primary replacement/ABI records

1. **`tools/observatory/probes/cell_movement.json:2,33,38,53`**
   - Replace the three stale `0x116b3c04` literals with the statically resolved `0x016b3c04`; replace the independent `0x115a758c` typo at line 53 with `0x015a758c`.
   - Revise the root description's obsolete environment/expectation prose: the historical zero-event result is environment-bound, the current gate is not a timeless “unreachable” prediction, and `FUN_0069b600` must remain explicitly generic/non-Cell-specific.
   - Do not change any probe `rva` value, the 12-probe count, the names, or the linked-VA/PE-RVA convention.
   - Recompute and record the manifest hash in the next approved gate record.

2. **`tools/observatory/probes/main_menu.json:3,16-17`**
   - Refresh the current static provenance: the headless Ghidra program is open, `App::cAppSystem::InitPlugins` is a function at `0x007E93D0`, and the current description's “not live-Ghidra-verified” / “inside init body” rationale is stale.
   - Preserve the seven linked-VA values unless a separate approved static review changes them. This is provenance maintenance, not a runtime result.

3. **`docs/REPLACEMENT-ABI.md:49,75`**
   - The current ABI table and behavioral contract still say the physical write is `sCellGame+0x5270`.
   - Update the current static contract to the explicit pointer-plus-byte form: `u32[sCellGame+0x5190]+0xE0`, one byte, semantic meaning still `INFERRED`.
   - Do not change the valid target/global address, function VA, or decompiler evidence classification in the same edit without a separate review.

4. **`docs/replacement-boundaries.md:104-112`**
   - `+0x5270` is used in the current promotion gate.
   - Update the gate to require reading the `+0x5190` pointer and the resolved `+0xE0` byte, not a four-byte field at `+0x5270`.

### 4.2 Current runtime-oracle and PKG-07 plan records

5. **`knowledgegraph/research/runtime-oracle/input-synthesis.md:95`**
   - Replace the flattened `sCellGame+0x5270` line with the explicit pointer-plus-byte expression and retain `INFERRED` semantic status.

6. **`knowledgegraph/research/track-m-oracle-plan.json:186,452`**
   - `STA-02.observation` currently says the decompiled capture writes `sCellGame+0x5270`.
   - `M2.probe_or_input_plan` currently samples `+0x5270`.
   - Update both to the physical `sCellGame+0x5190` pointer and resolved `+0xE0` byte, while retaining the historical decompiler expression as a separately labeled source if needed.

7. **`knowledgegraph/research/global-campaign-2026/track-d-sim-cell.json:173,259`**
   - The current function output and `sCellGame` field record use `0x5190+0xe0` without making the pointer indirection explicit.
   - Update the records to distinguish the `0x5190` pointer slot from the dereferenced `+0xE0` byte. Do not promote the semantic meaning beyond `INFERRED`.

8. **`docs/analysis/reconstruction-blueprint.md:386` and `docs/analysis/semantic-blueprint.md:397`**
   - The PKG-07 package summaries use `moving +0x5190+0xe0`; make the pointer/byte distinction explicit so these summaries do not re-flatten the field.

9. **`knowledgegraph/research/semantic-blueprint.json`**
   - The corresponding generated/current records occur around `:685118` (PKG-07 function outputs) and `:868982` (PKG-07 core-structure fields). Because this is a very large generated research artifact, update it through the repository's regeneration/source-of-truth path rather than hand-editing isolated copies if regeneration is available.

### 4.3 Current type/field research records

10. **`knowledgegraph/research/types/02-gameplay-entity.json:55` (`F008`)**
   - `0x5190 / 0x5270 nested` conflates the pointer slot with a flattened offset.
   - Change the record to `0x5190 pointer / resolved +0xE0 byte`, with pointer and byte evidence separate and movement meaning still `INFERRED`.

11. **`knowledgegraph/research/types/11-vtable-archaeology.json:147,925`**
    - The current Cell state comparison and movement field record list `+0x5270` as an original evidence offset.
    - Update to the explicit pointer-plus-byte path. The surrounding conclusion that these are static field anchors, not proof of a C++ vtable owner, remains valid.

12. **`knowledgegraph/research/types/12-field-archaeology.json:64,103,106`**
    - `CMP-MOVEMENT` still cites the flattened `+0x5270` current-source view and the ambiguous dossier expression.
    - `CELLGAME-STATE` still declares a `0x0000..0x5270` range, although the supported `cCellGame` size is `0x51E4` and the movement byte is nested through the `0x5190` pointer.
    - Update the range/records to distinguish the `cCellGame` object boundary from the nested serializable-object byte. Preserve the explicit note that `src/replace/CellGameView.hpp` is a current stand-in, not original ABI.

13. **`knowledgegraph/research/type-archaeology.json`**
    - This file contains derived copies of the same records, including the `F008`, `CMP-MOVEMENT`, `CELLGAME-STATE`, and current-comparison material (for example around `:683141`, `:939091`, `:1056003`, `:1359052`, `:1394373`, `:1738176`, `:1893811`, `:1907870`, and `:2093447`).
    - Regenerate or update the derived copies from the corrected source records. Do not hand-edit only one of the duplicated records and leave the type-archaeology index inconsistent.

15. **`docs/analysis/future-research/03-pkg-07-cell-movement.md:18-24`**
   - Correct the evidence summary so it distinguishes static identity, historical startup evidence, historical Cell negatives, and the absence of current M0/M1/M2 runtime observations. Do not turn the existing “positive boot/Cell reachability/read-only entry-return” wording into a current result.

16. **Current status/conflict fields after manifest correction**
   - Update the status fields in `knowledgegraph/research/runtime-oracle.json`, `knowledgegraph/research/semantic-blueprint.json`, `docs/analysis/original-exe-replacement.md`, `docs/analysis/runtime-oracle-plan.md`, `docs/analysis/runtime-experiments.md`, `docs/analysis/future-research/pkg07-runtime-gates.md`, `docs/analysis/implementation-status-v2.md`, and the two implementation-review artifacts only after the manifest is corrected and a fresh preflight exists.
   - Preserve the old value and old preflight result as historical/provenance fields, and preserve `NOT_RUN / BLOCKED`; do not promote runtime status.

## 5. Records that must remain unchanged as conflict/historical evidence

The following occurrences must preserve their historical/provenance text, but their **current status fields are not immutable truth**. The static adjudication in this audit means that after the manifest is corrected, current status/conflict fields should be reconciled with a new dated record. The old observations must not be deleted or silently rewritten as if the pre-correction tree had already passed.

### 5.1 Active conflict-preserving gate/review records

| File and locations | Why it remains |
|---|---|
| `tools/observatory/pkg07_preflight.py:24` | `STALE_GLOBAL_OPERAND` is an intentional sentinel used to block the manifest. It must remain until a reviewed replacement policy changes the validator. |
| `knowledgegraph/research/runtime-oracle.json:155-162,333-337,432-437,1702-1706` | Machine-readable preservation of `0x016B3C04` versus `0x116B3C04` and the required adjudication gate. |
| `knowledgegraph/research/runtime-oracle/input-synthesis.md:85-87,288` | Explicitly identifies the old value as non-equivalent and blocks installation/live sampling. |
| `knowledgegraph/research/runtime-oracle/replacement-observability.md:40,92,823` | Explicitly rejects `0x116B3C04` as an alias and requires current-byte/module-map resolution. |
| `docs/analysis/runtime-oracle-plan.md:107-115,626-644` | Verifies the current operand and prohibits aliasing or flattened physical-store claims. |
| `docs/analysis/runtime-experiments.md:38,687-735` | Preserves the unresolved conflict and defines the failure condition for a flattened moving field. |
| `docs/analysis/future-research/pkg07-runtime-gates.md:13,43,75,81,121` | Durable gate contract intentionally remains `NOT_RUN / BLOCKED` and says stale prose blocks runtime preparation. |
| `docs/analysis/original-exe-replacement.md:66,112` | Feasibility record explicitly requires adjudication before installation. |
| `knowledgegraph/research/semantic-blueprint.json:507-511` | `BOUNDARY-CELL-ADDRESS` records the current candidate versus older value as an open conflict. |
| `docs/analysis/implementation-status-v2.md:43-53` | Current dated status records the preflight result and the blocked stale manifest. Do not rewrite the historical result into a pass. |
| `docs/analysis/implementation-review-v2.md:35-49,123` | Independent review finding `GATE-01` and the observed blocked preflight result. |
| `knowledgegraph/research/implementation-review-v2/runtime-gates-review.md:10-32` | Independent runtime-gate finding that the conflict is intentionally blocked and that validator identity checks are incomplete. |

If the manifest is later corrected, these records should receive a new dated reconciliation/addendum or a regenerated current review; their old observations should not be back-edited into a result that did not occur. In particular, the current status/conflict fields in `runtime-oracle.json`, `semantic-blueprint.json`, `original-exe-replacement.md`, `runtime-oracle-plan.md`, `runtime-experiments.md`, `pkg07-runtime-gates.md`, `implementation-status-v2.md`, and the implementation reviews should be updated only after the corrected manifest and fresh preflight exist. Their old wording remains valid as a description of the pre-correction tree.

### 5.2 Historical raw evidence

| File and location | Treatment |
|---|---|
| `docs/analysis/CELL-RUNTIME-OBSERVATION.md:21-42,44-96` | Dated 2026-09-21 historical runtime record. It contains the old `0x116b3c04` wording and the nine-run negative. Preserve it as observed history. |
| `docs/analysis/dossiers/cell-movement.md:1-152` | Dated generated dossier. Preserve its decompiler-era expression and `runtime NOT OBTAINED` boundary; add a separate correction note if the current record needs a modern pointer/byte interpretation. |
| `tools/re/data/decompiled/MovePlayerToMousePosition.c:1-42` | Raw decompiler capture, explicitly evidence-not-truth. The flattened expression at line 35 must not be edited to masquerade as disassembly. Current direct disassembly is the higher-precedence physical-store record. |
| `tools/re/data/ghidra_snapshot_cell_movement.json:1-191` | Historical snapshot and dossier source. Its `address`/`rva` convention and 2026-09-21 provenance should remain unchanged. |
| `docs/devlog/018-s5-cell-runtime-evidence.md` and the referenced S5 raw artifacts | Historical boot/registration/exit negatives. No current runtime result may be inferred or overwritten. |
| `docs/analysis/dossiers/cell-movement.json` PKG-07 package record around `:1031-1034` | Historical/generated package record with unresolved live behavior, plane point, pool identity, and field meanings. Preserve the unresolved status. |

### 5.3 Intentional current-source stand-in records

- `src/replace/CellGameView.hpp:48-61`
- `src/replace/Replace.hpp:39-67`
- `src/replace/Reference.cpp:82`

These model a flattened `+0x5270` moving field and a four-argument host stand-in. They are explicitly current clean-room/approximation artifacts, not the original ABI. They must remain unchanged during this research-consistency audit; correcting them to the original pointer-plus-byte layout would be an implementation/design change, not a documentation reconciliation.

## 6. Related Cell field/function consistency conclusions

### 6.1 Consistent current static values

The following values are consistent across the current runtime-oracle and PKG-07 gate records:

- `sCellGame` global slot: `0x016B3C04` as the current instruction operand; semantic global name `sCellGame` is confirmed.
- `sCellGame+0x411C`: avatar/player pool index, passed to `FUN_00B721D0`; static interpretation only.
- `sCellGame+0x5158`: movement lock/guard word; static shape is observed, semantic label is inferred.
- `sCellGame+0x515C` and `+0x51E0`: per-frame update gates/state words; static interpretation only.
- `sCellGame+0x5190`: serializable-state pointer slot; this is not a player pointer and not itself the moving flag.
- Physical movement write: one byte at resolved `u32[sCellGame+0x5190]+0xE0`; meaning remains inferred.
- Player target: `+0x08/+0x0C/+0x10`; current position `+0x4C/+0x50/+0x54`; orientation `+0x14..+0x20`; static offsets/roles are bounded, not live-observed.
- Plane normal: `0x015A7C40/44/48`; plane point: `0x016B3C28/2C/30`; addresses are static, runtime values are not established by this audit.
- Cell UI slot: `0x016B3C0C` in the current M2 whitelist; runtime ownership/value remains open.
- `FUN_0069B600`: generic menu/frame helper in the historical record; it is not a valid Cell-stage marker.
- Direct movement call: `FUN_00E806B0` calls `MovePlayerToMousePosition`; the bounded direct call is at `0x00E8083B`, but dynamic caller coverage is unknown.

### 6.2 Current conflicts

**Conflict A — global operand:** current bytes and current static Ghidra xrefs select `0x016B3C04`; the older probe/decompilation prose contains `0x116B3C04`. The difference is not a formatting issue, and the old value is not a current image address. The static address question is resolved, but the active manifest and pre-correction status records are intentionally blocked until the manifest is corrected and a fresh preflight is recorded.

**Conflict B — physical moving field:** active/derived records variously say `sCellGame+0x5270`, `sCellGame+0x5190+0xE0`, or `sCellGame+0x5190` plus a resolved `+0xE0` byte. The current direct disassembly record in `knowledgegraph/research/runtime-oracle/replacement-observability.md:34-40,79-83,238-239,357-358,824-825` resolves the physical store as the pointer-plus-byte form. Semantic meaning, clearing behavior, owner, and runtime state remain unknown.

**Conflict C — raw decompiler versus disassembly:** the raw capture at `tools/re/data/decompiled/MovePlayerToMousePosition.c:35` is a flattened decompiler expression. It is evidence of source shape, not a byte-layout proof. The current direct disassembly and runtime-oracle synthesis should control the physical-store interpretation without rewriting the raw capture.

**Conflict D — preflight strength:** the preflight independently checks binary bytes, PE mapping, target/call arithmetic, and the stale manifest text, but `static_abi` and `caller_continuation` are hard-coded pass strings, and the manifest check is name/count based rather than full identity/hash pinned. This is an existing validator limitation, not evidence for runtime compatibility.

## 7. Runtime-oracle record consistency

| Artifact | Current status | Consistency conclusion |
|---|---|---|
| `knowledgegraph/research/runtime-oracle.json` | `TECHNICALLY_FEASIBLE_NOT_IMPLEMENTED`; positive startup history only; Cell runtime blocked | Correctly preserves the pre-correction conflict provenance, rejects the flattened moving store, and keeps M0/M1/M2 incomplete. Its current conflict status fields now need a post-adjudication update. |
| `knowledgegraph/research/runtime-oracle/input-synthesis.md` | `PROPOSED / NOT_RUN` synthesis | Correct on target identity and address discipline; line 95 is a stale moving-field projection requiring correction. |
| `knowledgegraph/research/runtime-oracle/replacement-observability.md` | Design-only, no runtime | Strongest current physical-store correction; correctly separates static evidence, historical negatives, and future gates. |
| `knowledgegraph/research/runtime-oracle/automation-audit.md` | Focused tests/dry-run inventory; no original Cell trace | Correctly reports no positive Cell trace and records automation/coverage gaps. It does not establish the target's live ABI. |
| `knowledgegraph/research/track-m-oracle-plan.json` | M0-M6 proposed | Target/call identity is consistent; lines 186 and 452 retain the flattened moving field and need coordinated correction. |
| `docs/analysis/runtime-oracle-plan.md` | `PROPOSED / DESIGN_ONLY` | Correctly rejects the global alias and flattened store; retain its conflict/prohibition language. |
| `docs/analysis/future-research/pkg07-runtime-gates.md` | `NOT_RUN / BLOCKED` | Correct current gate contract; it explicitly prevents using the stale manifest or launching without approval. |
| `docs/analysis/implementation-status-v2.md` | `HOST_IMPLEMENTED`; runtime/original compatibility unestablished | Correctly reports host status separately from blocked runtime status and records the stale manifest. |
| `docs/analysis/implementation-review-v2.md` / runtime-gates review | Independent findings open | Correctly records `GATE-01` through `GATE-04`; these reviews must not be treated as resolved by a documentation-only cleanup. |

## 8. Required future update order

The following sequence is recommended but was not executed:

1. Record and approve the static adjudication completed in this report: current bytes/Ghidra xrefs select `0x016B3C04`; `0x116B3C04` is not a current image address, alias, or accepted fallback. Keep runtime module-map verification as a separate future prerequisite.
2. Update the three `0x116b3c04` records, the independent `0x115a758c` note, and the stale environment/provenance prose in the Cell manifest; then recompute its hash.
3. Extend the preflight to compare an approved manifest hash and the complete expected name-to-address map, including target, call-site, helpers, and control entry.
4. Reconcile the active moving-field records in the primary ABI, runtime-oracle synthesis, Track M plan, Track D record, package summaries, and type/field research sources.
5. Regenerate derived research artifacts rather than hand-editing one copy of the large semantic/type-archaeology JSON files.
6. Re-run the static preflight and preserve its result. Do not turn a future static `PASS` into M0/M1/M2 runtime evidence.
7. Issue a new dated implementation/gate review. Preserve the existing blocked records and raw historical artifacts as history.
8. Only after explicit human approval and all containment gates may a future runtime experiment be considered. This audit does not authorize that experiment.

## 9. Confidence and evidence strength

| Conclusion | Confidence | Basis and boundary |
|---|---:|---|
| Current target VA/RVA/file offset/entry bytes | **0.99** | Current executable preflight passes all independent static identity/mapping/byte checks. |
| Current operand is `0x016B3C04` | **0.99** | Entry bytes decode directly, current preflight compares the operand, and current static Ghidra has 1,121 xrefs to the address. This is not a live module-map observation. |
| `0x116B3C04` is a distinct stale value and not a current image address | **0.99** | Exact numeric difference, zero current Ghidra xrefs, and current image-block layout; the manifest/preflight conflict is a repository consistency defect, not a live address. |
| `0x115A758C` is a separate stale helper-note operand | **0.99** | Current static Ghidra disassembly of `FUN_00E4CE40` reads `0x015A758C`; the manifest note says `0x115A758C`. |
| Cell manifest shape and 12-probe count | **0.99** | JSON parsed by current preflight; main-menu check also passes. |
| All Cell probe `rva` fields use linked-VA convention consistently | **0.95** | Values, tracer code, main manifest, and target arithmetic agree; full map validation is still absent. |
| Physical moving store is resolved `u32[sCellGame+0x5190]+0xE0` | **0.95** | Current direct-disassembly synthesis is explicit and repeated; raw decompiler capture is evidence-not-truth. Runtime ownership/value/clear behavior remain unknown. |
| Active `+0x5270` records require reconciliation | **0.95** | Exact grep inventory and conflict with current direct-disassembly record; generated-file scope creates additional duplication. |
| Historical negative Cell-reachability result should remain unchanged | **0.99** | Dated historical records and current runtime-oracle documents consistently preserve the negative boundary. |
| Runtime/original compatibility remains unestablished | **0.99** | No positive Cell trace, no M0/M1/M2 result, entry-only tracer limitation, and explicit `NOT_RUN/BLOCKED` contracts. |
| Complete manifest identity is currently hash-pinned and fail-closed | **0.10** | The helper reports a hash but does not compare it to an approved expected hash or validate every address; this is the open `GATE-02` risk. |

## 10. Concurrently appearing in-scope reports

After the initial status snapshot and after this report was first written, seven additional untracked in-scope artifacts appeared:

- `docs/analysis/future-research/pkg07-canonical-address-report.md`
- `docs/analysis/future-research/pkg07-manifest-provenance-report.md`
- `docs/analysis/future-research/pkg07-preflight-audit-report.md`
- `docs/analysis/future-research/pkg07-runtime-oracle-consistency-report.md`
- `docs/analysis/future-research/semantic-decomp-runtime-gates.md`
- `docs/analysis/semantic-decomp.md`
- `knowledgegraph/research/semantic-decomp.json`

They were not created or modified by this task. They were read read-only after appearing. The four PKG-07 reports added the independent `0x115A758C` manifest typo, the current static Ghidra availability, the manifest hash/identity weaknesses, and the need to keep M0/M1/M2 blocked after metadata cleanup. The three semantic-decomp artifacts are broader Cell/runtime research records: they are explicitly design/static (`runtime_performed=false`, `runtime_promoted=0`, and no original process run), and contain no competing `0x116B3C04` or `0x115A758C` record. The new `docs/analysis/semantic-decomp.md` explicitly reports 32 static targets, zero runtime validation, and keeps Cell death/rebuild/despawn runtime ordering separate from static mechanics. They do not change the PKG-07 conclusion.

One of those concurrent reports also identified an overbroad package statement in `docs/analysis/future-research/03-pkg-07-cell-movement.md:18-24`: it lists positive boot, positive Cell reachability, and read-only entry/return observations as currently available even though the current evidence ledger has only historical startup evidence and historical Cell negatives. That record should be corrected in the same future documentation reconciliation; it is not evidence that a runtime result was missed.

## 11. Worktree and safety verification

Before writing this report, `git status --short --branch` showed branch `main` and a pre-existing dirty worktree containing 103 short-status entries, including modified source/docs/tests and untracked research/build files. Those entries were not attributed to this task and were not modified.

The final post-write comparison showed the seven concurrent in-scope artifacts above plus this report as new relative to that initial snapshot. The concurrent files were not touched by this task. The only write performed by this task is:

```text
docs/analysis/future-research/pkg07-research-consistency-report.md
```

No `SPORE/` file, executable, binary, instrumentation source, shared canonical research record, or canonical knowledge-graph database was modified. No process was launched, attached, instrumented, or read. Read-only Ghidra queries were used for static image function/xref/mapping evidence only.

The final status comparison must therefore distinguish two facts: (a) this worker changed only its isolated report, and (b) the shared worktree concurrently gained four other untracked reports. No pre-existing source, manifest, canonical record, or binary was changed by this task.
