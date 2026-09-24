# PKG-07 canonical-address report

> This report is a pre-repair investigation snapshot. Its BLOCKED and stale findings describe the pre-repair tree and are superseded for current disposition by `docs/analysis/future-research/pkg07-runtime-preflight-repair.md`.

**Date:** 2026-09-24  
**Scope:** static adjudication of the stale Cell probe operand `0x116B3C04`  
**Status:** **RESOLVED STATICALLY; RUNTIME REMAINS NOT RUN / BLOCKED**  
**Canonical replacement:** `0x016B3C04` (`Simulator::Cell::sCellGame`, preferred linked VA)  
**Canonical probe/function:** `Simulator::Cell::MovePlayerToMousePosition`, tracer field `rva = 0x00E5B790` (actually a linked VA), PE RVA `0x00A5B790`

## Executive conclusion

`0x116B3C04` is not a Cell probe entry, function address, alias, or recoverable address in the current Ghidra image. It is an older, incorrect operand transcription in repository prose. The current five-byte target instruction and current Ghidra symbol/xref graph independently identify:

- target function: `Simulator::Cell::MovePlayerToMousePosition` at linked VA `0x00E5B790`;
- target entry: `a1 04 3c 6b 01` = `mov eax, dword ptr [0x016B3C04]`;
- global: `Simulator::Cell::sCellGame` at preferred linked VA `0x016B3C04`;
- global PE RVA: `0x012B3C04`;
- future runtime formula: `module_load_base + 0x012B3C04`, after approved module identity/mapping checks;
- sole current direct call xref: `0x00E8083B` in `FUN_00E806B0`, continuation `0x00E80840`.

The canonical global address is therefore recoverable with **very high static confidence**. The old value is not recoverable as an address in this image: current Ghidra has no symbol, no xref, no containing memory block, and cannot read memory at that address. The static conflict should be closed, but this report does not establish a live relocated address, Cell reachability, field values, M0/M1/M2 success, or installation readiness.

## Exact address identities

| item | canonical value | convention / meaning |
|---|---:|---|
| binary | `SporeApp.exe` 3.1.0.22 | current Ghidra program and hash-pinned repository artifact |
| PE image base | `0x00400000` | preferred linked base |
| function | `Simulator::Cell::MovePlayerToMousePosition` | current Ghidra symbol |
| function linked VA | `0x00E5B790` | `image_base + PE RVA` |
| function PE RVA | `0x00A5B790` | `0x00E5B790 - 0x00400000` |
| function file offset | `0x00A5AB90` | `.text` section mapping; repository static preflight |
| probe JSON target field | `0x00E5B790` | current tracer's `rva` field is a linked VA, not a PE RVA |
| global linked VA | **`0x016B3C04`** | preferred-image address encoded by the target instruction |
| global PE RVA | **`0x012B3C04`** | `0x016B3C04 - 0x00400000` |
| global runtime address | not observed | future value must be `module_load_base + 0x012B3C04` |
| direct call site | `0x00E8083B` | one current Ghidra direct xref |
| direct-call continuation | `0x00E80840` | next instruction after five-byte call |

`docs/analysis/future-research/pkg07-runtime-gates.md:13-19`, `docs/REPLACEMENT-ABI.md:13-33`, and `knowledgegraph/research/runtime-oracle.json:372-436` already contain the canonical function/global identity. The live module mapping and live state remain separate unobserved gates.

## Current Ghidra evidence

### 1. Function identity and entry bytes

Current Ghidra reports:

```text
Simulator::Cell::MovePlayerToMousePosition
address:      0x00e5b790
signature:    void Simulator::Cell::MovePlayerToMousePosition(float deltaTime)
body:         0x00e5b790..0x00e5ba01
```

Static bytes at the entry are:

```text
e5b790: a1 04 3c 6b 01 83 ec 38 83 b8 58 51 00 00 00 0f
        mov eax,[0x016b3c04]
        sub esp,0x38
        cmp dword ptr [eax+0x5158],0
```

The first five bytes are one complete x86 instruction. Its little-endian displacement is unambiguously `04 3c 6b 01` = `0x016B3C04`. This agrees with `docs/REPLACEMENT-ABI.md:25-38`, `docs/analysis/future-research/pkg07-runtime-gates.md:13-17`, and the read-only preflight result below.

The current decompiler resolves the loaded pointer as the current symbol `Simulator__Cell__sCellGame`. Within the movement function, current Ghidra has two direct reads of that global:

- `0x00E5B790`: entry load;
- `0x00E5B983`: reload before reading `sCellGame+0x5190` and storing the one-byte moving state through that pointer.

The second read is visible in the function disassembly at `0x00E5B983`; it is not evidence for `0x116B3C04`.

### 2. Global symbol and xrefs

Current Ghidra's global listing reports:

```text
Simulator::Cell::sCellGame @ 016b3c04 [Label] (undefined4) xrefs=1121
```

The full current xref query returned exactly 1,121 references:

- 1,119 reads;
- 2 writes;
- 378 functions represented;
- 15 references whose source instructions were not attributed to a containing function by Ghidra.

Selected direct references independently connect the canonical slot to the Cell lifecycle:

| source function | current xrefs | evidence role |
|---|---:|---|
| `Simulator::Cell::MovePlayerToMousePosition` | 2 reads | movement target path |
| `FUN_00e5b2e0` | 5 reads | per-frame Cell movement helper |
| `FUN_00e806b0` | 3 reads | real Cell per-frame update body |
| `App::cCellModeStrategy::Initialize` | 2 writes, 3 reads | global construction/lifecycle |
| `Simulator::Cell::cCellGame::Initialize` | 46 reads | extensive Cell-game state initialization |

The two writes are the strongest ownership evidence:

```text
0x00E81D63: MOV [0x016B3C04],EAX
0x00E81D6A: MOV dword ptr [0x016B3C04],EBX
```

`App::cCellModeStrategy::Initialize` first obtains the Cell-game object through `FUN_00E646D0`; it stores the returned pointer at `0x016B3C04`, or stores zero when the relevant service lookup fails. The following instructions reload that same slot to initialize fields. This is direct static proof of the slot's role, not merely a symbol-name association.

The other per-frame and update-body reads show the same numeric operand in independent functions. A systematic one-digit legacy error in prose therefore cannot explain 1,119 code references, and the current slot is not an isolated interpretation of the movement entry.

### 3. Memory placement and stale-address rejection

Current Ghidra memory blocks relevant to this issue are:

- `.text`: `0x00401000..0x013CBFFF`;
- `.rdata`: `0x013CC000..0x0150B5FF`;
- `.data`: `0x0150C000..0x0171E763`;
- `.reloc`: `0x017EF000..0x018D17FF`;
- next explicit block: `tdb` at `0xFFDFF000`.

`0x016B3C04` lies inside `.data`. A static memory read there returns zeroed initialized image bytes, consistent with a global pointer slot before live initialization.

`0x116B3C04` lies in the unmapped gap after `.reloc` and before `tdb`. Current operations show:

- `get_xrefs_to(0x116B3C04)` → 0 references;
- no global/list-data symbol at that address;
- `read_memory(0x116B3C04)` → unmapped/unreadable;
- no containing Ghidra memory block.

The numeric difference is also not a legitimate rebasing operation:

```text
0x116B3C04 - 0x016B3C04 = 0x10000000
0x116B3C04 - 0x00400000 = 0x112B3C04  (not a valid RVA of this image)
```

It is therefore not the result of applying the image base, ASLR load base, or the tracer's historical `+0x100000` snapshot convention. It is best classified as a transcription/prefix error in old prose.

### 4. Call graph and probe placement

Current Ghidra reports exactly one direct function xref to `MovePlayerToMousePosition`:

```text
0x00E8083B  UNCONDITIONAL_CALL  from FUN_00E806B0
```

Raw call bytes are:

```text
e8 50 af fd ff
```

The signed rel32 decodes from `0x00E8083B + 5` to `0x00E5B790`; continuation is `0x00E80840`. This agrees with the repository's direct-call record at `docs/analysis/future-research/pkg07-runtime-gates.md:15` and `knowledgegraph/research/runtime-oracle.json:391-397`.

The current static chain is:

```text
App::cCellModeStrategy::Update @ 0x00E80980
  -> FUN_00E806B0 @ 0x00E806B0
       -> Simulator::Cell::MovePlayerToMousePosition @ 0x00E5B790
```

Additional current Ghidra evidence supersedes the old dossier wording “no static callers” for `Update`: `Update` now has a data xref from `0x01485594`, in the cCellModeStrategy vtable. Its direct caller is `FUN_00E806B0` via `0x00E80992`. The movement target itself still has one static direct caller; dynamic/indirect callers remain unobserved.

Crucially, no probe entry in `tools/observatory/probes/cell_movement.json` has `rva = 0x116B3C04`. The target probe is already `rva = 0xe5b790` at lines 31-33. The stale number occurs only in description/note text. Therefore the correct update is **not** to move a probe breakpoint from `0x116B3C04` to another function address; it is to correct the prose operand to `0x016b3c04` while leaving the probe target unchanged.

## Repository artifact assessment

### 1. Current read-only preflight

`python3 tools/observatory/pkg07_preflight.py --json` was run as a static/file-only check. It reported:

- binary size/hash: PASS;
- PE identity/image base: PASS;
- PE section mapping: PASS;
- target bytes: PASS;
- call decode: PASS;
- binary interpretation: `mov eax,[0x016b3c04]; stale 0x116b3c04 not accepted`: PASS;
- main-menu manifest: PASS;
- Cell manifest: BLOCKED because its text contains `0x116b3c04`;
- runtime status: BLOCKED, M0/M1/M2 not run;
- `runtime_launched=false`, `process_memory_read=false`, `process_memory_written=false`, `canonical_kg_written=false`.

The blocking implementation is at `tools/observatory/pkg07_preflight.py:14-24`, `tools/observatory/pkg07_preflight.py:163-184`, and `tools/observatory/pkg07_preflight.py:193-201`. The current script already treats `0x016B3C04` as the only accepted static operand.

### 2. Cell manifest occurrences

`tools/observatory/probes/cell_movement.json` contains three stale spellings of the requested address:

- line 2: description says `sCellGame global 0x116b3c04`;
- line 33: movement note says `mov eax,[0x116b3c04]`;
- line 38: per-frame note says `mov eax,[0x116b3c04]`.

The same current Ghidra disassembly proves the first and third replacement sites use `0x016b3c04`.

A separate manifest typo exists at line 53: `cam_mode_getter_FUN_00e4ce40` says `[0x115a758C]`. Current Ghidra proves:

```text
0x00E4CE44: MOV ECX,dword ptr [0x015A758C]
```

`0x115A758C` is likewise outside the image blocks, while `0x015A758C` lies in `.rdata`. The current preflight only rejects the `0x116B3C04` spelling, so correcting only the requested conflict would clear `cell_probe_manifest` while leaving this independent note error. The exact record update should correct both in the same review.

### 3. Documentation consistency

Current/correct records already include:

- `docs/REPLACEMENT-ABI.md:19-33,40-43`: linked VA, RVA, file offset, entry bytes, and numeric global `0x16b3c04` (the same value as `0x016B3C04`);
- `docs/analysis/dossiers/cell-movement.md:46-52,97`: movement body and global fields;
- `docs/analysis/future-research/pkg07-runtime-gates.md:13-19`: canonical static target/global, direct call, and ABI;
- `knowledgegraph/research/runtime-oracle.json:380-436`: canonical function/global and rejection of the old alias;
- `knowledgegraph/research/runtime-oracle/replacement-observability.md:28-40,52-83`: canonical target manifest.

Records still describing the values as an open conflict include:

- `docs/analysis/original-exe-replacement.md:54-68,108-117`;
- `docs/analysis/implementation-status-v2.md:43-51`;
- `docs/analysis/future-research/pkg07-runtime-gates.md:43,75,81,121,137` (these are fail-closed guard texts, not affirmative stale interpretations);
- `knowledgegraph/research/runtime-oracle.json:155-162,332-338,432-436`;
- `knowledgegraph/research/semantic-blueprint.json:506-511`;
- `knowledgegraph/research/runtime-oracle/input-synthesis.md:85-87`;
- `knowledgegraph/research/runtime-oracle/replacement-observability.md:40,92`;
- `knowledgegraph/research/implementation-review-v2/runtime-gates-review.md:16`.

`docs/analysis/CELL-RUNTIME-OBSERVATION.md:35-40` contains the historical bad transcription. Its run outcomes remain valid, but the address text should be annotated as superseded rather than silently treated as original byte evidence.

## Recoverability assessment

### Canonical target/global: recoverable

The canonical identity is recoverable statically and redundantly:

1. The complete entry instruction bytes decode to `0x016B3C04`.
2. Current Ghidra names that address `Simulator::Cell::sCellGame`.
3. Current Ghidra reports 1,121 direct xrefs to it.
4. The only two direct writes are lifecycle initialization stores to the same address.
5. The movement function, per-frame helper, real update body, and Cell initialization paths independently reference it.
6. The repository preflight independently decodes the same operand from the hash-pinned file.

The linked-VA/RVA pair is also deterministic:

```text
global linked VA 0x016B3C04
global PE RVA    0x012B3C04
```

A live relocated address is not recoverable from this task because no process/module map was read. That limitation is a runtime-gate issue, not evidence that the static preferred-image address remains ambiguous.

### Stale `0x116B3C04`: not recoverable as a current address

There is no defensible mapping that turns `0x116B3C04` into the current target while preserving an address convention:

- no current Ghidra xref or symbol;
- no mapped block;
- unreadable address;
- invalid image RVA;
- delta is `+0x10000000`, unrelated to image/load-base rebasing;
- current bytes, symbol, writer, and 1,121-reference graph all select `0x016B3C04`.

It is recoverable only as historical error provenance: replace the leading `1` with `0` in the three manifest notes. It must not be retained as an alias, compatibility fallback, or “older base.”

## Confidence

| conclusion | confidence | evidence strength |
|---|---|---|
| Current global preferred linked VA is `0x016B3C04` | **Very high** | instruction bytes + current symbol + writers + 1,121 xrefs + independent preflight |
| Stale `0x116B3C04` is not an address in the current image | **Very high** | zero xrefs + no symbol + unmapped + memory read failure + invalid RVA |
| Current target function is `MovePlayerToMousePosition @ 0x00E5B790` | **Very high** | current Ghidra symbol/signature/body + repository SDK/static records |
| One direct caller exists at `0x00E8083B` | **High for current static xrefs** | exact Ghidra xref + bytes/rel32 decode; dynamic callers remain unknown |
| `sCellGame` is initialized by `App::cCellModeStrategy::Initialize` | **High** | two direct stores plus immediate reload/use sequence |
| Future runtime global address equals `load_base + 0x012B3C04` | **High conditionally** | canonical PE mapping rule; actual load base not observed in this task |
| Cell reachability, field meanings, or runtime state | **Unknown** | M0/M1/M2 remain not run; static analysis only |

## Exact record update recommendation

A maintainer should apply the following after review; this report does not apply those shared-file changes.

### A. Minimal required manifest correction

In `tools/observatory/probes/cell_movement.json`:

1. Line 2, replace:

```text
sCellGame global 0x116b3c04
```

with:

```text
sCellGame global 0x016b3c04
```

2. Line 33, replace:

```text
mov eax,[0x116b3c04]
```

with:

```text
mov eax,[0x016b3c04]
```

3. Line 38, replace:

```text
mov eax,[0x116b3c04]
```

with:

```text
mov eax,[0x016b3c04]
```

4. In the same correction pass, line 53, replace:

```text
[0x115a758C]
```

with:

```text
[0x015a758c]
```

5. Do **not** change any probe `rva` value. In particular, keep `Simulator::Cell::MovePlayerToMousePosition` at tracer field `0xe5b790`; keep its real PE RVA `0xa5b790` in any new explicit `pe_rva` field. Do not add `0x016b3c04` as a breakpoint probe merely because it is the global operand; it is a data slot, not the movement function entry.

6. After the text correction, `cell_probe_manifest` should become PASS while `runtime_status` and overall preflight must remain BLOCKED because M0/M1/M2 are not run. The address correction must not be reported as runtime verification.

### B. Current canonical research/status records

1. In `knowledgegraph/research/runtime-oracle.json`:
   - change the `sCellGame` conflict record at lines 155-162 from `UNRESOLVED_CONFLICT` to a status such as `RESOLVED_STATIC`;
   - record the resolution: current bytes/Ghidra xrefs select `0x016B3C04`; `0x116B3C04` is unmapped, has zero xrefs, and is not an alias;
   - change `MISS-07` at lines 332-338 from a static-address blocker to `RESOLVED_STATIC`;
   - preserve a separate future item for “runtime module mapping not observed,” because the loaded address remains unverified.

2. In `knowledgegraph/research/semantic-blueprint.json:506-511`, change `BOUNDARY-CELL-ADDRESS` from `open_conflict` to a resolved-static boundary. The explicit resolution should cite current bytes and current Ghidra, not merely defer to installation.

3. In `docs/analysis/original-exe-replacement.md:66,112`, replace “unresolved conflict” wording with “statically adjudicated to `0x016B3C04`; old value rejected.” Keep the requirement for future runtime module-map verification as a separate prerequisite.

4. In `docs/analysis/future-research/pkg07-runtime-gates.md`, retain fail-closed runtime gates but change statements that describe the numeric address conflict itself as unresolved. A suitable rule is: “require current bytes to decode `0x016B3C04`; reject `0x116B3C04`; verify the future runtime slot as `load_base + 0x012B3C04`.” The document must continue to state `NOT_RUN / BLOCKED`.

5. In `docs/analysis/implementation-status-v2.md:47-51`, update the Cell-manifest blocker only after the manifest correction is actually applied. Do not retroactively claim that correction from this report.

6. Add a short erratum to `docs/analysis/CELL-RUNTIME-OBSERVATION.md:38`: the historical document transcribed `0x116b3c04`, while current Ghidra and the original entry bytes decode `0x016b3c04`. Preserve the historical run counts and reachability conclusion.

7. Do not silently rewrite historical review snapshots such as `knowledgegraph/research/implementation-review-v2/runtime-gates-review.md`. Mark them superseded by this report and by the corrected manifest; otherwise their line-16 finding accurately describes the pre-correction tree.

### C. Preflight hardening

`tools/observatory/pkg07_preflight.py:23-24,113-121,178-182` already has the correct canonical and rejected values. For future review, consider validating the manifest's expected names **and exact target values** instead of checking only required-name presence and the one stale literal. The current preflight does not compare manifest values with the canonical function/call identity, and it does not reject the separate `0x115a758c` typo. This is a recommendation only; no preflight source was changed in this task.

## Constraint and integrity statement

- No Spore process was launched, attached, instrumented, or sampled.
- No original process memory was read.
- No input, breakpoint, detour, or replacement action occurred.
- `SPORE/`, executable binaries, instrumentation, shared canonical records, and knowledge-graph data were not modified.
- The only repository write performed by this worker is this report.
- The pre-existing dirty working tree was not cleaned, staged, reverted, or otherwise changed.
- Baseline/final status comparison found two additional untracked reports, `pkg07-manifest-provenance-report.md` and `pkg07-runtime-oracle-consistency-report.md`, that were absent from the initial status and appeared during this investigation. They were created concurrently and were not created, read for modification, or changed by this worker. Accordingly, this worker can assert that its own write set contains only this report, but cannot claim that the concurrently changing global worktree contains only this report.
