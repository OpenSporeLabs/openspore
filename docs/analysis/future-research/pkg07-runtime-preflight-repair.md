# PKG-07 Runtime Preflight Repair Record

**Record ID:** `PKG-07-RUNTIME-PREFLIGHT-REPAIR`  
**Date:** 2026-09-24  
**Status:** `STATIC_ARTIFACT_READY / RUNTIME_BLOCKED`  
**Scope:** Static Cell probe identity and PKG-07 preflight repair. This record does not authorize a launch or establish runtime behavior.

## Repair conclusion

The stale source was Obj32 prose and three Cell manifest fields. The three stale global fields were the root `description`, the `Simulator::Cell::MovePlayerToMousePosition` note, and the `cell_per_frame_FUN_00e5b2e0` note. They contained `0x116B3C04`; the current global is **`0x016B3C04`**.

The current target is **`Simulator::Cell::MovePlayerToMousePosition` at linked VA `0x00E5B790` / PE RVA `0x00A5B790`**. The probe field `rva` remains a linked-VA value of `0xe5b790`; the probe did not move and was not changed to the global operand. The global value is a data operand, not a probe breakpoint target.

The independent stale camera-mode operand `0x115A758C` was corrected to **`0x015A758C`**. The old `0x116B3C04` value is rejected by the preflight and is not an alias: it is distinct from `0x016B3C04`, has no current image xref, is outside the current image blocks, and is not accepted as a fallback or alternate mapping.

## Final manifest identity

| File | Final SHA-256 | Exact content disposition |
|---|---|---|
| `tools/observatory/probes/main_menu.json` | `aa99f627f995e5e0c2bf53f139d8fc9d2c30c0acf688a6ef239f76b66082a286` | 7 probes; exact approved name-to-linked-VA map; current headless Ghidra provenance; `InitPlugins` is a function at `0x007E93D0` with body `0x007E93D0..0x007E9440` |
| `tools/observatory/probes/cell_movement.json` | `1c379af6d28c8bd9651473cfb7c5762a96345824a98ae6c94c8004c7af6199b3` | 12 probes; target field remains linked VA `0xe5b790`; all three Obj32 `0x116b3c04` fields corrected; independent `0x115a758c` corrected; historical negative prose and generic-helper classification retained with bounded wording |

The canonical executable used by the preflight is `SPORE/SporeBin/SporeApp.exe`, size `20454960`, SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`, PE32/i386, image base `0x00400000`.

## Exact records represented by the repair

The following files and records are the current repair set represented by this record. Creating this record did not modify any of them:

- `tools/observatory/probes/cell_movement.json`: root description; `MovePlayerToMousePosition` note; `cell_per_frame_FUN_00e5b2e0` note; `cam_mode_getter_FUN_00e4ce40` note; generic `face_travel_orient_FUN_0069b600` classification; and historical bootstrap-control note.
- `tools/observatory/probes/main_menu.json`: static provenance description and `App::cAppSystem::InitPlugins` boundary note. Probe values and count were preserved.
- `tools/observatory/pkg07_preflight.py`: current/stale operand constants, exact approved manifest hashes, complete name-to-linked-VA maps, duplicate/value/stale-sentinel checks, `pkg07-preflight-2` schema, separate static/runtime fields, `STATIC_ASSERTED` ABI/caller evidence levels, advisory-standalone enforcement label, and explicit safety flags.
- `tests/test_pkg07_preflight.py`: side-effect-free synthetic PE/manifest tests covering the repaired identity contract, both stale sentinels, malformed inputs, exact maps, approved hashes, and the no-runtime boundary.

The exact repaired manifest records are therefore not limited to changing a probe address: they include stale prose, independent operand provenance, generic Cell-marker classification, and current Ghidra provenance. The `rva` fields and probe count were not changed.

## Preflight and test result

The current command was run as a static/file-only check:

```text
PYTHONDONTWRITEBYTECODE=1 python3 tools/observatory/pkg07_preflight.py --json
```

Canonical result:

- schema: `pkg07-preflight-2`
- `static_overall`: `PASS`
- `runtime_status`: `NOT_RUN`
- `preflight_enforcement`: `ADVISORY_STANDALONE`
- M0/M1/M2 static artifact checks: `PASS`, artifact readiness `READY`
- M0/M1/M2 full preflight: `BLOCKED`
- M0/M1/M2 runtime evidence: `NOT_RUN`
- ABI and caller continuation are reported as `STATIC_ASSERTED`, not independently runtime-verified
- `runtime_launched`, `process_memory_read`, `process_memory_written`, and `canonical_kg_written`: `false`

The focused test command was:

```text
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest tests.test_pkg07_preflight -v
```

Result: **10/10 tests passed**.

Static identity readiness is not runtime readiness. The repaired binary, target, call, manifest, map, hash, PE, and note checks all pass statically. M0 and M1 remain blocked for full/runtime preflight because current M0 evidence, human authorization, disposable containment, current environment/provenance, and M1 navigation/profile prerequisites are absent. M2 remains blocked because M1 is absent and the current entry-only tracer lacks return/continuation pairing, owner-qualified state capture, exact write coverage, and omitted-callee/external-effect coverage.

## Remaining human-only gates

1. Explicit approval for the named gate, binary hash, probe-manifest hash, disposable run root, display/window target, scope, stop condition, and operator.
2. Human-present execution on the shared display, physical emergency-stop readiness, and supervised process/Wine/tracer teardown.
3. A fresh disposable Wine generation, profile, save root, run directory, and confirmation that canonical executable, `SPORE/`, profiles/saves, and the canonical knowledge graph are out of scope for writes.
4. A legitimate human-prepared registration/profile handoff without credential logging, fixed focused-window geometry, explicit key/input allowlist, and human navigation supervision for M1.
5. Human review of any boot, renderer, window, registration, process, timeout, or Cell-reachability negative before interpretation or retry.
6. Human approval and a reviewed adapter for M2 attachment, bounded reads, breakpoint/watchpoint use, owner-qualified state boundaries, and restoration evidence.
7. Independent review of raw artifacts and human approval before any status or `replaced-approx` promotion.

## Historical and safety boundary

`docs/analysis/CELL-RUNTIME-OBSERVATION.md`, the historical S5 runtime artifacts, devlogs, raw decompiler captures, and other raw runtime observations remain unchanged. Their historical negative results and provenance wording are not current runtime verification and were not back-edited.

No runtime verification is claimed by this record. No game launch, attachment, input, breakpoint, process-memory read/write, binary modification, `SPORE/` modification, replacement installation, or canonical knowledge-graph write was performed as part of creating these two records. All safety and runtime-action flags are false.

## Sources read

- `docs/analysis/future-research/pkg07-research-consistency-report.md`
- `docs/analysis/future-research/pkg07-manifest-provenance-report.md`
- `docs/analysis/future-research/pkg07-canonical-address-report.md`
- `docs/analysis/future-research/pkg07-runtime-oracle-consistency-report.md`
- `docs/analysis/future-research/pkg07-preflight-audit-report.md`
- `tools/observatory/pkg07_preflight.py`
- `tests/test_pkg07_preflight.py`
- `docs/REPLACEMENT-ABI.md`
- `docs/analysis/future-research/pkg07-runtime-gates.md`
- `tools/observatory/probes/cell_movement.json`
- `tools/observatory/probes/main_menu.json`
