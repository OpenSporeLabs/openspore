# PKG-07 preflight audit report

> This report is a pre-repair investigation snapshot. Its BLOCKED and stale findings describe the pre-repair tree and are superseded for current disposition by `docs/analysis/future-research/pkg07-runtime-preflight-repair.md`.

**Audit date:** 2026-09-24
**Scope:** `tools/observatory/pkg07_preflight.py`, its Python/shell contracts, all direct and indirect callers, both PKG-07 probe manifests, the preflight JSON schema surface, the M0/M1/M2 gate contract, and current status/research records.
**Mode:** read-only except for this report. No Spore/Wine/tracer launch, attachment, input, breakpoint, process-memory access, binary modification, `SPORE/` modification, instrumentation change, or shared canonical-file update was performed.

## Executive conclusion

`pkg07_preflight.py` is a useful static smoke check, but it is not yet a fail-closed preflight gate and its current output does not distinguish static readiness from runtime-not-run state.

The tool does **not** embed the known stale target address as its expected target: its target, call-site, continuation, and `sCellGame` constants match the current canonical executable and current Ghidra graph (`tools/observatory/pkg07_preflight.py:11-24`). `STALE_GLOBAL_OPERAND = 0x116B3C04` is intentionally a rejection sentinel, not an accepted alias.

The tool nevertheless has five material defects:

1. The probe manifests are not actually hash-pinned. It computes a digest and prints it, but compares it to no approved digest (`tools/observatory/pkg07_preflight.py:115-121,186-203`).
2. It validates only a subset of names and no name-to-address values. A manifest with the required names at arbitrary addresses passes (`tools/observatory/pkg07_preflight.py:95-112,186-201`).
3. Its stale-data sentinel covers only `0x116B3C04`. The Cell manifest also contains stale `0x115A758C`; current disassembly decodes `0x015A758C` (`tools/observatory/probes/cell_movement.json:51-54`; current Ghidra disassembly of `FUN_00e4ce40`).
4. `static_abi` and `caller_continuation` are unconditional `PASS` assertions, not checks derived from parsed instructions or a pinned evidence artifact (`tools/observatory/pkg07_preflight.py:183-184`).
5. The script is advisory: no runtime caller runs it. `observe.py`, MCP `trace_run`, and `cell_trace.sh` load or launch from the manifests directly (`tools/observatory/observe.py:40-63,66-90`; `tools/mcp/runtime_tools.py:254-370`; `tools/observatory/cell_trace.sh:445-462,534-629`).

The exact repair is therefore:

- correct the Cell manifest, including both stale operands and obsolete prose;
- make preflight compare the same bytes it hashes, require exact complete name/value maps, reject unknown/missing/duplicate entries, and compare approved manifest digests;
- replace hard-coded `PASS` claims with independently checked or honestly labeled `STATIC_ASSERTED` records;
- add direct unit tests against synthetic PE/manifest fixtures;
- separate `static_overall` from `runtime_status` in a versioned schema;
- invoke the static-only preflight from real M0/M1 entry points and fail closed on its exit code.

After that repair, **M0 static preflight can be ready without human execution**; running M0 still cannot. **M1 static manifest/contract checks can be ready without execution, but M1 itself cannot be fully preflight-ready** because it depends on a current M0 positive result, a legitimate human-prepared disposable profile/registration handoff, emergency-stop readiness, and approved runtime execution. **M2 cannot be preflight-ready without human execution** because M1 is absent and the current entry-only tracer cannot produce return pairing, owner-qualified state, write coverage, or omitted-callee evidence.

## Current execution flow and ownership

### Standalone preflight

1. `main()` parses only `--json` and calls `run_checks()` (`tools/observatory/pkg07_preflight.py:232-259`).
2. `run_checks()` reads the canonical executable as a static file, hashes it, parses the PE headers, maps two true PE RVAs, reads exact target/call bytes, decodes the global operand and relative call, and emits static records (`tools/observatory/pkg07_preflight.py:125-184`).
3. It reads both manifests with `read_manifest()`, checks only `image_base`, exact count, object/name shape, duplicate names, and a required-name subset, then reports each manifest's current digest (`tools/observatory/pkg07_preflight.py:87-122,185-203`).
4. It compiles three Python test sources but does not execute them; it searches shell text for tokens but does not execute shell behavior (`tools/observatory/pkg07_preflight.py:204-227`).
5. It always appends `runtime_status=BLOCKED`, then computes `overall=BLOCKED` whenever no `FAIL` exists (`tools/observatory/pkg07_preflight.py:228-255`).

There are no production callers of `run_checks()`, `read_manifest()`, or the CLI. Documentation and status files invoke the CLI manually.

### Actual manifest consumer

`probe_tracer.cpp` has its own minimal JSON parser. It reads `image_base` and each probe's `rva`, then resolves `module_base + (rva - image_base)` (`tools/observatory/probe_tracer.cpp:460-500`). It does not enforce names, counts, duplicate addresses, expected digests, executable alignment, or all-probe active coverage. The field named `rva` is therefore a **legacy linked-VA convention**, not a true PE RVA.

`observe.py` passes `probes/<scenario>.json` directly to the tracer and acquires a machine lock, but direct invocation is not approval-equivalent to MCP (`tools/observatory/observe.py:40-63,66-90`). MCP `trace_run` supplies the human gate but still does not invoke `pkg07_preflight.py`; it checks existence and broad environment prerequisites, then launches `observe.py` (`tools/mcp/runtime_tools.py:254-370`).

`cell_trace.sh` passes `probes/cell_movement.json` directly to `probe_tracer` (`tools/observatory/cell_trace.sh:445-462`). Its own `preflight()` checks only `DISPLAY`, executable existence, `xdotool`, `maim`, and tracer build (`tools/observatory/cell_trace.sh:534-547`). It never runs PKG-07 preflight and uses a non-atomic check/start/sleep machine-lock handoff (`tools/observatory/cell_trace.sh:611-629`).

## Stale and historical data audit

### Current constants in `pkg07_preflight.py`

The following are current, not stale, according to the canonical file checks and current Ghidra graph:

- executable size `20454960` and SHA-256 `25d42a...d914e` (`tools/observatory/pkg07_preflight.py:11-12`);
- image base `0x00400000` (`tools/observatory/pkg07_preflight.py:13`);
- target linked VA/RVA/offset and bytes (`tools/observatory/pkg07_preflight.py:14-17`);
- call-site linked VA/RVA/offset and bytes (`tools/observatory/pkg07_preflight.py:18-21`);
- continuation `0x00E80840` (`tools/observatory/pkg07_preflight.py:22`);
- current global operand `0x016B3C04` (`tools/observatory/pkg07_preflight.py:23`).

The executable is currently hashed, parsed, and byte-checked by the preflight; it is not merely copied from prose. Current Ghidra disassembly independently confirms the target entry, call site, continuation, direct caller xref, target epilogue, and referenced globals.

### Stale data in `probes/cell_movement.json`

Required factual corrections:

| Record | Current text | Current static evidence | Required repair |
|---|---:|---:|---|
| Root `description` | `sCellGame global 0x116b3c04` | `0x016B3C04` | Replace and describe address convention explicitly. |
| `Simulator::Cell::MovePlayerToMousePosition.note` | `mov eax,[0x116b3c04]` | `mov eax,[0x016b3c04]` | Replace. |
| `cell_per_frame_FUN_00e5b2e0.note` | `mov eax,[0x116b3c04]` | `mov eax,[0x016b3c04]` | Replace. |
| `cam_mode_getter_FUN_00e4ce40.note` | `mov ecx,[0x115a758c]` | `mov ecx,[0x015a758c]` | Replace; add a second preflight sentinel/check. |

Required prose corrections in the same root `description`:

- Remove the obsolete claim that the legacy probe `rva` is a dossier RVA plus `0x100000`. State the actual legacy-tracer convention: the field contains a preferred linked VA and the tracer computes `load_base + (field - image_base)`.
- Remove “Cell stage is UNREACHABLE headless” and “these probes are expected to record 0 cell events.” Historical runs did not reach Cell Stage; that is not a timeless property. The current environment has `xdotool`, and the runtime gate explicitly allows a human-watched focused-window path.
- Label prior zero-event evidence as historical and environment-bound. It cannot be a gate expectation.
- The entry-control note should label the cited 2026 run as historical. It must not be treated as current M0 evidence (`tools/observatory/probes/cell_movement.json:61-63`).

### Stale provenance in `probes/main_menu.json`

The addresses are currently plausible and all seven linked values map as expected, but the description is stale:

- It says headless GhidraMCP cannot open programs and the set is not live-Ghidra-verified (`tools/observatory/probes/main_menu.json:3`). The current headless Ghidra project is open and provides current function/xref/disassembly evidence.
- It says `InitPlugins` at `0x7e93d0` is about 384 bytes inside an init body and only instruction-aligned (`tools/observatory/probes/main_menu.json:16-17`). Current Ghidra recognizes a function at that exact address. Re-adjudicate the label and record the current source rather than preserving the old “inside body” interpretation.
- The history of an incorrect first `entry` value may remain only when clearly labeled as migration history, not current provenance.

The preflight currently accepts this manifest despite these provenance problems because it does not pin or compare its full contents.

### Historical data used as a live assertion

`static_abi` and `caller_continuation` are not historical values, but they are static assertions with no checked evidence source. Their current claims happen to match current Ghidra evidence:

- the target pushes/pops only `ESI`/`EDI`, allocates `0x38`, and ends in plain `RET`, so the x86-32 cdecl `void(float)` record is statically supported;
- `FUN_00e806b0` has the one direct call at `0x00E8083B`; continuation is `0x00E80840`;
- current Ghidra reports one direct xref to the target and one direct xref from the Update thunk to `FUN_00e806b0`.

The defect is provenance and drift resistance, not the current numeric truth. Preflight must not call these unconditional strings standalone `PASS`.

## Manifest schema and loader defects

### No formal schema

The output has a version string, `pkg07-preflight-1`, but no JSON Schema file or formal status enum (`tools/observatory/pkg07_preflight.py:240-248`). No test references the schema string. The current output mixes static checks and the intentionally unrun runtime state under one `overall`, so a genuinely static pass is impossible: `runtime_status=BLOCKED` always forces exit 2.

Recommended replacement schema ID: `pkg07-preflight-2`.

Minimum top-level fields:

```json
{
  "schema": "pkg07-preflight-2",
  "static_overall": "PASS | FAIL | BLOCKED",
  "runtime_status": "NOT_RUN",
  "gates": {
    "m0": {"static_preflight": "PASS | FAIL | BLOCKED", "runtime_evidence": "NOT_RUN"},
    "m1": {"static_preflight": "PASS | FAIL | BLOCKED", "runtime_evidence": "NOT_RUN"},
    "m2": {"static_preflight": "PASS | FAIL | BLOCKED", "runtime_evidence": "NOT_RUN"}
  },
  "runtime_launched": false,
  "process_memory_read": false,
  "process_memory_written": false,
  "canonical_kg_written": false,
  "checks": []
}
```

Each check should include `id`, `status`, `evidence_level`, `source`, `expected`, and `observed`; status semantics should distinguish `PASS`, `FAIL`, `BLOCKED`, `STATIC_ASSERTED`, `COMPILE_ONLY`, and `TOKEN_PRESENT_ONLY`. `FAIL` should mean an approved contract is contradicted; `BLOCKED` should mean a prerequisite/evidence source is absent.

### `read_manifest()` is fail-open for identity

Current behavior:

- validates exact list length but not exact name set;
- validates required-name membership only;
- converts every `rva` to an integer but compares none of the values;
- computes a hash after separately rereading the file for output, allowing a parse/hash race;
- checks duplicate names but not duplicate addresses or unexpected extras;
- accepts missing/invalid types in ways that do not match the C++ loader;
- does not require hex-string representation;
- does not compare approved digests;
- checks only one stale address.

The C++ loader is weaker still: malformed probe entries can be skipped, and an empty active set is not a launch refusal (`tools/observatory/probe_tracer.cpp:460-500,874-970`).

### Missing call check

When `call_actual != CALL_BYTES`, `call_bytes=FAIL` is appended, but no `call_decode` record is appended (`tools/observatory/pkg07_preflight.py:168-177`). A mutated call can therefore produce a less complete report than intended.

### Possible crash after target-byte failure

After a target-byte mismatch, the script unconditionally performs `struct.unpack_from("<I", target_actual, 1)` (`tools/observatory/pkg07_preflight.py:163-180`). A short or malformed slice can raise an uncaught `struct.error`. Binary-negative tests are required.

### Stale detection is too narrow

Only `0x116B3C04` is rejected (`tools/observatory/pkg07_preflight.py:24,113-121,198-201`). Both `0x116B3C04` and `0x115A758C` need explicit current/stale pairs. The preflight should also validate every manifest note's declared global values, not merely search one sentinel string.

## Required exact manifest identity

The legacy field `rva` below is a linked VA. The corresponding true PE RVA is linked VA minus `0x00400000`.

### `main_menu.json` exact seven-name map

| Probe name | Legacy field (`linked_va`) | True PE RVA |
|---|---:|---:|
| `entry` | `0x011E11A0` | `0x00DE11A0` |
| `App::Bootstrap::local_main` | `0x00DE13D0` | `0x009E13D0` |
| `App::Bootstrap::stateMachine` | `0x00E20860` | `0x00A20860` |
| `App::cAppSystem::Init` | `0x007E8BA0` | `0x003E8BA0` |
| `App::cAppSystem::Startup` | `0x007E67A0` | `0x003E67A0` |
| `App::cAppSystem::InitPlugins` | `0x007E93D0` | `0x003E93D0` |
| `App::IAppSystem::Get` | `0x0067DCC0` | `0x0027DCC0` |

### `cell_movement.json` exact twelve-name map

| Probe name | Legacy field (`linked_va`) | True PE RVA |
|---|---:|---:|
| `App::cCellModeStrategy::Update` | `0x00E80980` | `0x00A80980` |
| `cell_update_body_FUN_00e806b0` | `0x00E806B0` | `0x00A806B0` |
| `App::cCellModeStrategy::OnKeyDown` | `0x00E818F0` | `0x00A818F0` |
| `App::cCellModeStrategy::OnMouseMove` | `0x00E51010` | `0x00A51010` |
| `App::cCellModeStrategy::OnMouseWheel` | `0x00E7D660` | `0x00A7D660` |
| `Simulator::Cell::MovePlayerToMousePosition` | `0x00E5B790` | `0x00A5B790` |
| `cell_per_frame_FUN_00e5b2e0` | `0x00E5B2E0` | `0x00A5B2E0` |
| `cam_light_origin_FUN_007c4900` | `0x007C4900` | `0x003C4900` |
| `player_getter_FUN_00b721d0` | `0x00B721D0` | `0x007721D0` |
| `cam_mode_getter_FUN_00e4ce40` | `0x00E4CE40` | `0x00A4CE40` |
| `face_travel_orient_FUN_0069b600` | `0x0069B600` | `0x00296B600` |
| `entry (bootstrap control)` | `0x011E11A0` | `0x00DE11A0` |

Preflight must compare these exact maps. It must not compare the Cell manifest's `0x00E5B790` legacy value directly to the target's true `TARGET_RVA=0x00A5B790`; it must first apply the documented address conversion.

## Exact repair plan

### 1. Correct the manifests

Required file: `tools/observatory/probes/cell_movement.json`.

- Replace both `0x116B3C04` records with `0x016B3C04`.
- Replace `0x115A758C` with `0x015A758C`.
- Rewrite the root address-convention description.
- Remove “Cell stage is UNREACHABLE headless” and zero-event expectation.
- Mark old run/event observations as historical and non-gating.
- Identify `face_travel_orient_FUN_0069b600` as generic/non-Cell-specific in metadata so future classification cannot use any non-control event as a Cell marker.
- Preserve all twelve names and linked-VA values listed above.

Required file: `tools/observatory/probes/main_menu.json`.

- Refresh Ghidra provenance to current headless Ghidra evidence.
- Remove the obsolete “not live-Ghidra-verified” reason.
- Re-adjudicate and record the current `InitPlugins` function boundary.
- Preserve the seven linked-VA values unless a new static review rejects one.

After final byte formatting/content is settled, compute and record new approved SHA-256 digests. Current digests are baseline evidence only:

- `main_menu.json`: `5236c7f9a5be37ba0c775f34dcd4537c2b414eda4b72df34220c19bea42e025c`
- `cell_movement.json`: `02e60089e831f89c750c3d2c7180185147d7cebd4590dbc50343947eb47d8977`

Those current digests must not be blindly promoted as approved digests because the manifests still require correction.

### 2. Make manifest validation exact and race-free

Required file: `tools/observatory/pkg07_preflight.py`.

Replace subset/count/hash-printing validation with:

- read manifest bytes once;
- parse and hash those same bytes;
- require approved expected SHA-256;
- require exact complete name set, exact complete name-to-value map, and no extras;
- require canonical lowercase `0x` hex strings for `rva` and `image_base`;
- reject duplicate names and duplicate values unless the contract explicitly allows them;
- reject both stale/current global text mismatches;
- compare every expected value after the documented linked-VA conversion;
- include a normalized `name=value` list in the report so a reviewer can inspect what was trusted.

The approved manifest digest and semantic map may live in the preflight module for this focused tool, or in a versioned static-evidence JSON checked by the preflight. A separate evidence artifact is preferable if it records source/provenance and remains generated independently of the manifest itself.

### 3. Stop labeling assertions as independently verified checks

Required file: `tools/observatory/pkg07_preflight.py`.

- Keep `call_decode=PASS` only for bytes and arithmetic actually decoded by the script.
- Until the epilogue and caller xref are independently derived, emit `caller_continuation=STATIC_ASSERTED` and `static_abi=STATIC_ASSERTED`, not `PASS`.
- Add a checked static-evidence artifact containing the target/caller/continuation, instruction boundaries, plain `RET`, stack delta, callee-saved register behavior, and bounded direct xref. Preflight must compare that artifact's identity and byte anchors to the canonical executable.
- Explicitly state that the complete dynamic caller set is unknown.

The current Ghidra graph is valid static evidence, but a hand-authored prose statement is not a durable executable gate without an artifact identity and byte-anchor checks.

### 4. Make failures total and deterministic

Required file: `tools/observatory/pkg07_preflight.py`.

- Handle short target/call slices and all malformed PE/manifest inputs as structured `FAIL` records, not traceback.
- Always append a `call_decode` result, including `not_checked_due_to_bad_bytes` when call bytes mismatch.
- Bound PE header/section-table reads and validate section raw ranges.
- Separate static and runtime aggregation so `runtime_status=NOT_RUN` does not force static `BLOCKED`.
- Preserve explicit safety booleans.

### 5. Add a real schema and tests

Required new files:

- `tools/observatory/pkg07_preflight.schema.json`
- `tests/test_pkg07_preflight.py`

The unit test should import the module and use temporary synthetic PE/manifest byte fixtures. It must not execute or require Spore.

Minimum test matrix:

1. valid minimal PE32/i386 with one section and exact target/call bytes;
2. bad MZ, bad PE signature, non-PE32, wrong machine, wrong image base, truncated headers;
3. RVA outside sections, section mapping, target/call boundary and short-slice negatives;
4. exact target/global/call decode;
5. call-byte mutation and call-displacement mutation;
6. valid exact seven-name main map and exact twelve-name Cell map;
7. missing name, extra name, duplicate name, wrong value, duplicate value, wrong count;
8. missing/invalid `rva`, non-hex representation, non-string type;
9. approved-hash success and every one-byte hash mismatch;
10. stale `0x116B3C04` and stale `0x115A758C` rejection;
11. same-byte parse/hash behavior, eliminating parse/hash TOCTOU;
12. schema-valid output and `static_overall` independent of `runtime_status=NOT_RUN`;
13. exit-code contract: `0` for static pass with runtime not run, `2` for blocked, `1` for failed;
14. no subprocess, Wine, `/proc/<pid>/mem`, `ptrace`, or `SPORE/` access from unit fixtures.

Relabel existing checks rather than overstating them:

- `python_test_sources` -> `COMPILE_ONLY`;
- `dry_run_contracts` -> `TOKEN_PRESENT_ONLY`.

Behavioral contract execution belongs in the test command/CI, not as a token claim. Do not make the preflight recursively execute a suite that imports the preflight.

### 6. Wire static preflight into real entry points

Required caller files if preflight is to be enforcing rather than advisory:

- `tools/observatory/cell_trace.sh`: invoke a static-only preflight before its real path; require exit 0 and reject `FAIL`/`BLOCKED`.
- `tools/observatory/observe.py`: for `main_menu` and `cell_movement`, invoke the same static-only validator before tracer launch. This also reduces direct-script bypass for manifest identity, though it does not replace the human approval boundary.
- `tools/mcp/runtime_tools.py`: record the static preflight result and digest in `trace_run`; do not treat MCP approval as evidence that static validation passed.
- `tools/observatory/probe_tracer.cpp`: independently reject empty/partial probe activation before planting; open output before breakpoint ownership if this behavior is later repaired.

Preflight integration is not sufficient to fix the independent `cell_trace.sh` supervision, atomic lock, always-written negative manifest, profile handoff, or Cell-marker classification gaps documented in `knowledgegraph/research/runtime-oracle/automation-audit.md:142-211`.

## M0/M1/M2 readiness determination

### M0

**Static preflight: repairable without human execution. Runtime execution: no.**

Static M0 needs exact executable identity, PE mapping, main-menu manifest digest/full map, current startup provenance, and static preflight integration. Those are all testable from files and synthetic/side-effect-free tests. Historical startup events may be cited as historical context but cannot satisfy current M0.

After the repair, the schema can report `m0.static_preflight=PASS` and `m0.runtime_evidence=NOT_RUN`. The actual M0 positive/negative result still requires the explicitly approved, human-watched, disposable no-input process described in `docs/analysis/future-research/pkg07-runtime-gates.md:27-65`.

### M1

**Static artifact readiness: repairable. Full M1 preflight readiness: not currently possible without human execution or current M0 evidence.**

The manifest and shell dry-run can be made fully tested without Spore. Full M1 remains dependent on:

- a current M0 positive result or an explicitly reviewed M0-negative investigation decision;
- a legitimate, human-prepared disposable profile/registration handoff;
- physical emergency-stop readiness;
- approved human-watched focused-window execution;
- current Cell-specific positive-marker classification, not “any non-control event” (`tools/observatory/cell_trace.sh:415-433`).

The historical no-Cell-event result must remain a historical negative, not a predicted outcome.

### M2

**Not preflight-ready.**

M2 requires M1 positive reachability and a capability that can pair target entry with return/continuation, capture owner-qualified state before/after, prove direct writes or label partial coverage, and account for omitted callees. The current `probe_tracer` is entry-only; it emits no EFLAGS, stack pair, return observation, memory state, or write-site evidence. This is correctly documented in `docs/analysis/future-research/pkg07-runtime-gates.md:107-145`.

A static M2 capability contract can be designed and unit-tested without Spore, but that does not make M2 itself preflight-ready. M2 remains `NOT_RUN / BLOCKED`.

## Existing test commands and audit results

### Existing commands

Full Python suite, repository convention:

```bash
python3 -m unittest discover -s tests -t . -v
```

Focused side-effect-free observatory contracts:

```bash
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest \
  tests.test_menu_walk tests.test_cell_trace tests.test_lock -v
```

Current preflight command:

```bash
PYTHONDONTWRITEBYTECODE=1 python3 tools/observatory/pkg07_preflight.py --json
```

Current preflight command intentionally returns `2` while the gate is blocked.

Native 32-bit tracer mechanics without Wine/Spore, after building the tracer:

```bash
make -C tools/observatory
cd tools/observatory
./probe_tracer --launch ./test/m32target --launch-arg 400 \
  test/probes_m32.json /tmp/obs_m32.jsonl --duration 3 --module m32target
python3 analyze.py /tmp/obs_m32.jsonl
```

The tracer build and native test were not run in this audit because the requested write boundary excluded generated binary changes and the report scope was source/manifest audit.

### Commands run in this audit

```bash
PYTHONDONTWRITEBYTECODE=1 python3 tools/observatory/pkg07_preflight.py --json
```

Result: `BLOCKED` with the expected current binary/PE/target/call/main-menu passes, `cell_probe_manifest=BLOCKED` for `0x116B3C04`, and unconditional `runtime_status=BLOCKED`. The output does not detect the additional stale `0x115A758C` and labels asserted ABI/caller records as passes.

```bash
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest \
  tests.test_menu_walk tests.test_cell_trace -v
```

Result: **22 tests passed in 0.300s**. These tests verify dry-run/no-tool behavior, approval refusal, key allowlist, registration decision helper, and manifest helper determinism. They do not test `pkg07_preflight.py`, manifest identity, PE-negative behavior, or actual Cell reachability.

```bash
sha256sum tools/observatory/probes/main_menu.json \
          tools/observatory/probes/cell_movement.json
```

Result: the current digests recorded in the repair section above.

`tests.test_observe_lock` was not run because its lock-free test temporarily renames `tools/observatory/probe_tracer` inside the repository (`tests/test_observe_lock.py:50-67`), which conflicts with this audit's strict no-write boundary. It should be hardened to use a temporary tracer path/root before use in a preflight-focused suite.

## Exact files and records requiring update

### Required for code correctness and enforceability

1. `tools/observatory/probes/cell_movement.json` — correct both stale addresses, address convention, and historical zero-event prose.
2. `tools/observatory/probes/main_menu.json` — refresh stale Ghidra provenance and `InitPlugins` boundary record.
3. `tools/observatory/pkg07_preflight.py` — exact map/hash validation, second stale sentinel, total failure handling, evidence levels, static/runtime separation, and exit semantics.
4. `tools/observatory/pkg07_preflight.schema.json` — new versioned output schema.
5. `tests/test_pkg07_preflight.py` — new direct unit/negative suite using synthetic fixtures.
6. `tools/observatory/cell_trace.sh` — invoke static preflight before the real path; separately repair supervision/classification/lock issues before M1 claims.
7. `tools/observatory/observe.py` — enforce static manifest preflight for supported scenarios.
8. `tools/mcp/runtime_tools.py` — record and require static preflight evidence before runtime trace launch.
9. `tools/observatory/probe_tracer.cpp` — reject empty/partial active coverage and reconcile its permissive loader with the approved contract.

### Required status/provenance updates after the repair passes

10. `docs/analysis/future-research/pkg07-runtime-gates.md` — revise M0/M1/M2 wording from unresolved manifest conflict to the repaired static state, while retaining runtime `NOT_RUN`.
11. `docs/analysis/implementation-status-v2.md:43-53` — replace the stale-manifest blocking result and static-assertion limitation with the new current result.
12. `docs/analysis/implementation-review-v2.md:35-50,67-70,123` — close or supersede GATE-01 through GATE-04 only after direct tests pass; do not promote runtime status.
13. `knowledgegraph/research/implementation-review-v2/runtime-gates-review.md:14-52` — preserve the historical review, then add a dated superseding audit rather than rewriting its evidence boundary.
14. `knowledgegraph/research/runtime-oracle.json:141-175,282-338` — update identity-conflict and `static_preflight_validator` status only after an independent review; this task did not modify the shared research record.
15. `docs/analysis/runtime-oracle-plan.md:148-163,207-220` — mark the static validator implemented only after its tests and caller integration are current; retain M0/M1/M2 runtime blocks.
16. `docs/analysis/CELL-RUNTIME-OBSERVATION.md:21-40,65-96` — add an erratum distinguishing historical environment facts from current static truth. In particular, correct the recorded `0x116b3c04` decode and the now-obsolete “xdotool absent/unreachable” conclusion.
17. `docs/STATE.md:66-90` and `tools/observatory/README.md:63-176` — update stale tooling/provenance statements (`xdotool absent`, headless Ghidra inability, preflight validator not integrated). Do not rewrite historical event counts.
18. `knowledgegraph/research/runtime-oracle/automation-audit.md:194-211,255-270` — append/supersede findings after the runtime-entry integration and tracer coverage repairs; do not erase the original audit.
19. `knowledgegraph/research/runtime-oracle/replacement-observability.md` and `knowledgegraph/research/runtime-oracle/input-synthesis.md` — update only the conflict/validator status after adjudication; preserve the rule that historical and live evidence are distinct.

Historical raw run artifacts and devlogs should remain immutable. Prose that intentionally records the old address or environment may remain if explicitly labeled `HISTORICAL_SUPERSEDED`; it must no longer be accepted as current preflight input.

## Final disposition

- **Current preflight:** useful static smoke check, advisory, and fail-open on manifest identity.
- **Current stale data:** present in both probe manifests, not in the accepted target constants of the preflight.
- **Exact tool repair:** manifests + full identity/hash validation + total error handling + evidence-level schema + direct tests + caller enforcement.
- **M0:** static preflight can be made ready without human execution; M0 result cannot.
- **M1:** static checks can be made ready; full gate readiness still requires current M0/human profile/runtime prerequisites.
- **M2:** cannot be preflight-ready; return/state/write capability and M1 evidence are absent.
- **Canonical/runtime status:** remains `NOT_RUN / BLOCKED`; no status promotion is supported by this audit.

## Git hygiene

A filtered `git status --porcelain=v1 --untracked-files=all` digest excluding this report was recorded immediately before writing:

`997420137df499d6a3b17e45195da98c7a512fc7057ba89868e6e0558c25896b`

The worktree already contained many unrelated modified and untracked files before this audit. The final digest excluding only this report changed to `9cba57702af21973e28ccfad9098825193e1986cac10edf38dd5bd6b42a70dd6` because three other PKG-07 reports were concurrently created by other workers:

- `docs/analysis/future-research/pkg07-canonical-address-report.md`
- `docs/analysis/future-research/pkg07-manifest-provenance-report.md`
- `docs/analysis/future-research/pkg07-runtime-oracle-consistency-report.md`

Excluding this report and those three concurrent paths reproduced the original digest `997420137df499d6a3b17e45195da98c7a512fc7057ba89868e6e0558c25896b` exactly. This audit created or modified only `docs/analysis/future-research/pkg07-preflight-audit-report.md`; it did not touch the concurrent reports or any pre-existing dirty-tree file.
