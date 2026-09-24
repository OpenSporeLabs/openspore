# PKG-07 Runtime-Oracle Experiment-Consistency Audit

> This report is a pre-repair investigation snapshot. Its BLOCKED and stale findings describe the pre-repair tree and are superseded for current disposition by `docs/analysis/future-research/pkg07-runtime-preflight-repair.md`.

**Audit date:** 2026-09-24  
**Scope:** PKG-07 M0/M1/M2 experiment specifications, gates, manifests, reports, static evidence, and historical runtime evidence  
**Mode:** read-only audit; no Spore launch, attachment, input, instrumentation, process-memory read/write, `SPORE/` access for mutation, binary modification, canonical KG write, or shared canonical-file edit  
**Report isolation:** this file is the only file this audit is authorized to create or modify

## 1. Executive determination

### 1.1 Metadata-only answer

Replacing the stale Cell probe metadata with the current statically decoded operand `0x016B3C04` would remove the **specific stale-text blocker** currently emitted by `pkg07_preflight.py`. It would not, by itself, make M0, M1, or M2 technically preflight-ready.

| Milestone | Current status | After stale metadata is corrected | Technical-preflight-ready now? | Runtime-verifiable now? |
|---|---|---|---|---|
| M0 boot/attach control | `NOT_RUN / BLOCKED` | The stale-manifest blocker would clear, but the manifest-identity, complete-static-check, ABI/caller-evidence, and human/runtime prerequisites remain | **No** — at most a partial static candidate | **No** |
| M1 Cell reachability/lifecycle | `NOT_RUN / BLOCKED` | M0 remains unrun; the Cell manifest would still lack trusted hash/value validation; GUI/runtime safety and registration/profile gates remain unresolved | **No** | **No** |
| M2 ABI/side effects | `NOT_RUN / BLOCKED` | M1 remains absent; the current tracer still lacks return, post-state, exact write, and omitted-callee coverage; ABI/caller facts are asserted rather than independently derived | **No** | **No** |

**Conclusion:** stale metadata correction is a prerequisite cleanup, not a gate pass. No milestone may be described as runtime-verified from this audit or from static evidence.

### 1.2 Current static-preflight result

The side-effect-free command was run from the repository root:

```text
PYTHONDONTWRITEBYTECODE=1 python3 tools/observatory/pkg07_preflight.py --json
```

Result:

- `overall`: `BLOCKED`
- `canonical_executable`: `PASS` for size `20454960`
- `binary_hash`: `PASS` for SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`
- `pe_identity`: `PASS` for PE32/i386 and image base `0x00400000`
- `pe_mapping`, `target_bytes`, `call_decode`, and `binary_interpretation`: `PASS`
- `main_menu_probe_manifest`: `PASS`, count `7`, current reported hash `5236c7f9a5be37ba0c775f34dcd4537c2b414eda4b72df34220c19bea42e025c`
- `cell_probe_manifest`: `BLOCKED`, count `12`, current reported hash `02e60089e831f89c750c3d2c7180185147d7cebd4590dbc50343947eb47d8977`, because the file contains `0x116B3C04`
- `python_test_sources`: `PASS`, but only means three files compile
- `dry_run_contracts`: `PASS`, but only means required tokens are present
- `runtime_status`: `BLOCKED`, explicitly `M0/M1/M2 NOT_RUN`
- `runtime_launched`: `false`
- `process_memory_read`: `false`
- `process_memory_written`: `false`
- `canonical_kg_written`: `false`

These are static, file-level checks only. None is a runtime observation of the original process.

### 1.3 Runtime-evidence ceiling

The repository's evidence ceiling remains:

- Historical startup/menu evidence exists, but it is not a current M0 result.
- The S5 Cell attempts are historical negatives: no positive non-control Cell event, no target call, no return, no state, no write, and no external-effect oracle.
- The native tracer self-test is mechanics-only evidence on `m32target`, not Spore evidence.
- Host simulation, OpenSpore fixtures, decompilation, SDK names, static bytes, screenshots, and the 64/64 decompilation-reference differential are not original-runtime verification.
- `RUNTIME_VERIFIED` for PKG-07 is therefore **none**, and the replacement ceiling remains `replaced-approx`.

## 2. Source and evidence audit

### 2.1 Active PKG-07 gate contract

`docs/analysis/future-research/pkg07-runtime-gates.md` is the most specific active M0/M1/M2 contract. It states:

- M0 is a bounded, human-approved, no-input boot control, not a Cell/gameplay/ABI result (`:27-57`).
- M1 requires M0 or an explicit decision to investigate an M0 negative, a legitimate disposable profile, fixed navigation, complete Cell probe accounting, and a real Cell-specific event (`:67-105`).
- M2 requires M1 positive reachability, a return-capable observation adapter, owner-qualified state, declared write coverage, omitted-callee coverage, external-effect horizon, process lifecycle, and restoration evidence (`:107-145`).
- The document says static preflight does not authorize a launch and that all original-process actions remain human-gated (`:21-23`, `:149`).

The contract is conservative and correctly keeps M0/M1/M2 at `NOT_RUN / BLOCKED` while the address conflict, missing current positive controls, and missing M2 capability remain unresolved.

### 2.2 Package-level research specification

`docs/analysis/future-research/03-pkg-07-cell-movement.md` has stale/overbroad evidence prose at `:18-24`: it lists “positive boot and Cell reachability” and “read-only entry/return and pre/post scalar/vector observations” as currently available. The active evidence ledger does not support a positive current Cell result or a current M2 observation. This is a documentation-consistency defect, not evidence of a missed runtime result. It should be corrected to distinguish:

- static target/body/probe identity;
- historical startup evidence;
- historical Cell reachability negatives;
- no current M0/M1/M2 result; and
- no runtime ABI/state/write evidence.

The package’s decision criterion at `:36-42` is otherwise appropriate: attributable original observation is required, and entry-only/unreachable results remain `replaced-approx` and `BLOCKED_BY_RUNTIME`.

### 2.3 Preflight implementation

`tools/observatory/pkg07_preflight.py` currently provides a useful but incomplete static helper.

What it actually checks:

- executable size and SHA-256 (`:125-140`);
- PE machine/image base and section-to-file mapping (`:142-162`);
- target and call bytes and call displacement (`:163-177`);
- the absolute global operand (`:178-182`);
- manifest syntax, image base, count, duplicate names, required-name subset, stale operand text, and emitted file hash (`:87-122`);
- Python compilation and token presence (`:204-227`).

Why it is not a complete fail-closed technical preflight:

1. **No trusted manifest hashes.** `read_manifest` emits a hash but compares it to no approved expected hash (`:115-121`).
2. **Incomplete required names.** The main-menu check requests five names although the manifest contains seven; the Cell check requests four names although the manifest contains twelve (`:186-197`).
3. **No name-to-address contract.** The script parses `rva` values into a report but does not compare every expected probe value, including target, call, and control addresses (`:97-121`).
4. **ABI and caller facts are hard-coded `PASS`.** The script emits `static_abi` and `caller_continuation` from strings at `:183-184`; it does not independently parse the terminal `RET`, stack-frame use, callee-saved behavior, direct xrefs, or the caller/continuation relationship.
5. **Test checks are not behavioral tests.** `compile(...)` and token search do not execute the contract suite or validate malformed/wrong-address/duplicate/hash-mismatch cases (`:204-227`).

Therefore, after removing the stale text, the script could emit `PASS` for a modified-but-name-compatible manifest and for asserted ABI/caller fields. That is a fail-open gap, not a pass of the stated gate contract.

### 2.4 Runtime-plan and observability contracts

`docs/analysis/runtime-oracle-plan.md` correctly separates static preflight, native ABI fixture tests, read-only runtime identity, positive control, original Cell baseline, and replacement policies (`:148-162`, `:203-253`, `:255-339`). It also correctly prohibits screenshots, clean exits, generic frames, and decompilation-only 64/64 from substituting for runtime evidence (`:626-645`).

`knowledgegraph/research/runtime-oracle/replacement-observability.md` correctly requires a complete Phase-A static contract, including exact guard windows, terminal `RET`, bounded direct xrefs, direct writes, called callees, page boundaries, and complete check lists (`:85-100`). It correctly states that the current Cell probe set has no positive Cell events and that the existing observatory cannot provide return/state/write coverage (`:24`, `:42-45`).

These are design requirements, not current results. They are not satisfied merely by changing a JSON description string.

## 3. Milestone-by-milestone audit

## M0 — Fresh-generation boot and attach control

### Specification and current evidence

M0’s active contract is `pkg07-runtime-gates.md:27-65` and the canonical experiment description is `docs/analysis/runtime-experiments.md:70-121` / `knowledgegraph/research/runtime-oracle/candidate-experiments.md:31-76`.

Required positive M0 evidence is a current, hash-pinned, no-input run with:

- exact binary and probe identity;
- fresh Wine generation;
- module host PID/path/load base and mapping;
- attributable startup sequence (`entry`, `InitPlugins`, `Init`, `Startup`, recurring `App::IAppSystem::Get`);
- pinned window/renderer identity;
- active/skipped/retired/dropped probe accounting;
- bounded process outcome and exact negative reason if negative; and
- cleanup/restoration evidence.

The historical startup capture and S5 run-1 are not current M0 results. `docs/analysis/CELL-RUNTIME-OBSERVATION.md:44-84` and `docs/devlog/018-s5-cell-runtime-evidence.md:31-63` contain historical outcomes, including a menu/render observation, self-exit, and zero Cell events. They cannot be promoted into M0 success.

### Does stale metadata make M0 preflight-ready?

**No.** M0’s specified startup probe is `main_menu.json`, so the Cell global address conflict is not logically an M0 boot identity. However, the current `pkg07_preflight.py` treats the Cell manifest as part of the overall PKG-07 preflight, so correcting the stale text would clear one script-level blocker. The following remain:

- no approved expected manifest hash comparison;
- incomplete name validation and no complete value validation for the seven startup probes;
- ABI and caller/continuation facts emitted as asserted `PASS` rather than independently derived static checks;
- missing guard/terminal-`RET`/bounded-xref checks required by the static plan;
- no current run artifact with `C-PROV`, `C-BOOT`, and `C-NEG` fields.

M0 is therefore **partial static preparation only after metadata correction, not technically preflight-ready under the full contract**.

### M0 human-only gates

Every item below remains human-only:

1. Explicit approval naming the gate, binary hash, probe hash, disposable run root, display/window target, scope, stop condition, and operator.
2. Trusted runtime approval (`approve=true` plus `OPENSPORE_MCP_TRUSTED=1` where the reviewed surface requires it); direct `observe.py` is not approval-equivalent.
3. Human-presence execution on the shared display and human confirmation of the pinned window/geometry.
4. Human-established fresh Wine generation without disrupting unrelated services.
5. Human physical emergency-stop readiness; a synthetic stop event is not equivalent.
6. Human-supervised launch and process/tree teardown, including exact exit/signal/time classification.
7. Human review of any boot negative and any decision to investigate it rather than proceed to Cell claims.
8. Human approval before any breakpoint placement or process attachment, if the selected supervisor uses temporary instrumentation.

M0 cannot pass merely because the canonical executable hashes correctly.

## M1 — Cell reachability and lifecycle control

### Specification and current evidence

M1 is defined by `pkg07-runtime-gates.md:67-105`, `docs/analysis/runtime-experiments.md:47-66` and `candidate-experiments.md:217-262`.

The positive vector requires a bootstrap `entry` control followed by a non-control Cell-specific event or an explicitly attributable target-path event, stable module-host/load-base identity, complete probe accounting, monotonic event order, renderer/window identity, and survival through the declared observation.

Historical evidence is negative:

- the older nine-run record had zero Cell-stage probe events;
- the only menu render run showed `FUN_0069b600` at roughly 30 Hz, which is explicitly a generic menu/frame helper;
- S5 run 1 fired only `entry` and self-exited after about 12.7 seconds;
- S5 runs 2 and 3 produced no window/events; and
- the registration form visibly required email, screen name, and password, while the automation allowlist intentionally permits no letters, digits, free-form text, or `xdotool type`.

These facts classify historical reachability/boot outcomes. They do not prove that Cell behavior is absent, inert, or equal to OpenSpore.

### Does stale metadata make M1 preflight-ready?

**No.** Removing the stale `0x116B3C04` text would remove a manifest blocker, but M1 still has all of the following blockers:

- M0 is not a current positive result;
- the Cell manifest lacks approved hash pinning and full name/value validation;
- the preflight helper’s current 12-probe check accepts only a four-name subset and does not verify the complete set or exact values;
- `cell_trace.sh` has known process-supervision, manifest-on-failure, atomic-lock, window-identity, classifier, screenshot-correlation, coverage-count, and provenance gaps documented in `knowledgegraph/research/runtime-oracle/automation-audit.md:142-211`;
- registration/profile handoff is not implemented;
- the current tracer’s entry-only event schema is not sufficient for M2 but may only be used as a bounded reachability control after the M1 prerequisites are fixed.

M1 remains **not preflight-ready and not runnable by an unattended worker**.

### M1 human-only gates

1. M0 positive result, or an explicit human decision to investigate a documented M0 negative without making Cell claims.
2. Human-prepared legitimate disposable profile/registration state, with no credential logging.
3. Explicit approval for the focused-window navigation path and the six-key allowlist: `Return`, `Escape`, `Up`, `Down`, `Left`, `Right`.
4. Human confirmation of window identity, geometry, renderer marker, and emergency-stop readiness.
5. Human-supervised process launch, navigation, stop, and teardown.
6. Human review of a negative outcome and its exact phase; no retry/input escalation may manufacture a transition.
7. Human approval for any process-memory instrumentation used for M1 reachability.
8. Human decision to continue to M2 only after a positive, attributable Cell control.

A changed screenshot, registration validation text, menu frame, generic orientation helper, or installed-but-unfired target probe is not M1.

## M2 — Read-only ABI and side-effect characterization

### Specification and current evidence

M2 is defined by `pkg07-runtime-gates.md:107-145`, `docs/analysis/runtime-experiments.md:59-66`, and the detailed observability contract in `replacement-observability.md:279-393`.

M2 requires paired entry/return observations, exact stack and callee-saved behavior, exact return form, owner-qualified state, pool-index versus resolved-object separation, direct-write coverage or explicit partial coverage, omitted-callee coverage, external-effect horizon, process lifecycle, and restore/detach evidence.

The current repository has none of that original-process evidence. The current `probe_tracer` is entry-only and does not provide:

- return or continuation observations;
- `RET`/`RET N` verification;
- callee-saved comparison;
- before/after state;
- exact write/watchpoint evidence; or
- a positive Cell-stage trace.

The 64/64 comparison is a host/decompilation-reference differential, not a live ABI or state oracle.

### Does stale metadata make M2 preflight-ready?

**No.** Stale metadata correction cannot supply the missing runtime capability or its prerequisite M1 result. M2 remains blocked by:

- absent M1 positive Cell reachability;
- no original target call;
- no return/continuation oracle;
- no state oracle;
- no exact write oracle;
- no omitted-callee/external-effect coverage;
- asserted rather than independently derived ABI/caller checks in the current helper; and
- no current M2 run manifest or paired raw records.

M2 is **not technically preflight-ready**. This is a capability gap, not a metadata problem.

### M2 human-only gates

1. M1 positive Cell reachability and target-path evidence.
2. Explicit approval for a read-only runtime observation adapter.
3. Human approval for any software breakpoints, debugger attachment, bounded process-memory reads, or hardware-watchpoint use.
4. A reviewed adapter with entry/continuation pairing and restoration responsibility; software breakpoint process-memory modification must be disclosed and restored.
5. Human confirmation of page/debugger ownership, safe pointers, owner-qualified state boundaries, capture horizon, and stop conditions.
6. Human-supervised teardown and verification that the disposable copy, canonical executable, `SPORE/`, canonical profiles/saves, and canonical KG remain unchanged.
7. Independent adjudication of raw artifacts and partial/negative coverage.
8. Human status approval before any `replaced-approx` to `replaced-verified` change.

M2 must remain `PARTIAL` or `FAIL`, never `PASS`, for entry-only events, unpaired returns, pointer/index conflation, snapshot deltas presented as exact writes, incomplete callee coverage, unsafe reads, failed restoration, or unknown field meaning.

## 4. Complete human-only gate inventory

The following are not removable by metadata correction and remain human-only or human-approved:

### A. Authorization and operator presence

- Original-process launch approval for M0/M1/M2.
- Trusted approval flag where required; a direct script invocation is not equivalent.
- Human presence on the shared display.
- Human operator identity and emergency-stop responsibility.
- Physical `Ctrl+Alt+Backspace` verification; synthetic stop injection is insufficient.

### B. Disposable containment and environment

- Human-authorized disposable copy and disposable run root.
- Fresh disposable Wine prefix/profile/save root.
- Human-established Wine generation discipline.
- Pinned display, compositor/session, output, window ID, WM_CLASS, renderer marker, and geometry.
- Human confirmation that canonical executable, `SPORE/`, canonical profiles/saves, and canonical KG are out of scope for writes.

### C. Input and registration

- Human-prepared legitimate profile or separately approved non-secret registration state.
- Human-supervised focused-window navigation.
- Human approval of the exact key allowlist and pre-issue input manifest.
- No letters, digits, free-form text, clicks, `xdotool type`, credentials, or credential logging.

### D. Runtime supervision and stop decisions

- Human-supervised tracer, Wine host, shell, and all child processes.
- Human decision on boot failure, renderer failure, window failure, registration failure, process exit, or timeout.
- Human stop and teardown at the declared boundary.
- Human verification of exact process/signal/exit/time outcome and bounded capture horizon.

### E. Instrumentation and M2 observation

- Human approval for attachment, breakpoint placement, software breakpoints, debugger reads, and hardware watchpoints.
- Human-approved adapter selection and owner of the byte/debug/watchpoint transaction.
- Human decision to stop on unsafe address, owner change, unpaired return, page/debug conflict, or target instability.
- Human verification of restoration/detach for any temporary instrumentation.

### F. Interpretation and promotion

- Human review of raw JSONL/manifests and exact negative reasons.
- Human-approved independent adjudication distinct from the implementer.
- Human status-update approval through the existing status workflow.
- No promotion to `replaced-verified` from static evidence, host tests, a screenshot, a clean exit, a zero-event trace, or the 64/64 decompilation reference.

## 5. Exact files and records requiring updates

The following is the required update ledger. These are recommendations for the responsible owner; this audit did not edit them.

### 5.1 Direct stale-address cleanup

| File/record | Current inconsistency | Required update |
|---|---|---|
| `tools/observatory/probes/cell_movement.json:2` | Description says `sCellGame` is `0x116b3c04` and claims no Xvfb/xdotool; both are stale or historical in the current repository context | Change the current description to the statically decoded `0x016B3C04`; separately label the old address as historical conflict. Do not silently delete the conflict history from all reports. |
| `tools/observatory/probes/cell_movement.json:33` | Target note says `mov eax,[0x116b3c04]` | Replace the active target note with `mov eax,[0x016B3C04]` and retain “dynamic callers unknown.” |
| `tools/observatory/probes/cell_movement.json:38` | Callee note repeats `0x116b3c04` | Correct the current note to `0x016B3C04`; update the semantic boundary if needed. |
| `tools/observatory/probes/main_menu.json:3` | Says headless GhidraMCP cannot open programs, conflicting with the current documented headless Ghidra setup | Update provenance wording only; do not turn an objdump/static probe definition into a live-runtime claim. |
| `docs/analysis/future-research/pkg07-runtime-gates.md:13,43,57,75,81,97,121,137,149` | Active gate text treats the Cell address conflict as unresolved | After an independently reviewed correction, mark the active manifest conflict resolved while retaining the historical conflict record. Keep overall status `NOT_RUN / BLOCKED` until the remaining technical and human gates pass. |
| `knowledgegraph/research/implementation-review-v2/runtime-gates-review.md:14-32` | GATE-01 records the stale conflict as open and identifies the fail-open validator | Add a follow-up resolution record after the manifest correction and a re-review. Do not rewrite the historical finding as if it never existed. |
| `docs/analysis/implementation-status-v2.md:43-53` | Reports the preflight as blocked by the stale Cell manifest and describes the asserted checks | Update the current preflight result and unresolved review findings after the actual rerun. Preserve `M0/M1/M2 = NOT_RUN / BLOCKED`. |

### 5.2 Preflight implementation and tests

| File/record | Current gap | Required update |
|---|---|---|
| `tools/observatory/pkg07_preflight.py:87-121` | Manifest hash is emitted but not compared; required names are incomplete; values are not compared to an approved map | Add approved expected SHA-256s, complete expected name sets, exact name-to-linked-VA maps, duplicate/unknown/missing checks, and explicit target/call/control comparisons. Keep unknown values fail-closed. |
| `tools/observatory/pkg07_preflight.py:183-184` | ABI/caller facts are hard-coded `PASS` | Derive from checked static evidence, or label `STATIC_ASSERTED` and keep the gate blocked until a parser/disassembly/xref check exists. Verify terminal `RET`, stack-frame use, callee-saved behavior, bounded direct xrefs, and caller/continuation. |
| `tools/observatory/pkg07_preflight.py:204-227` | Compile-only and token-presence-only results are presented as `PASS` | Rename to `COMPILE_ONLY`/`TOKEN_PRESENT_ONLY`, or execute the side-effect-free focused tests and record exact results. A preflight must not imply runtime execution. |
| New focused preflight test record, preferably `tests/test_pkg07_preflight.py` | No direct tests cover wrong manifest hash, wrong address, duplicate name, missing name, stale text, altered ABI evidence, or malformed manifest | Add side-effect-free unit tests for all fail-closed cases and a regression test proving no runtime flags flip. This is a missing record, not a current passing test. |
| `knowledgegraph/research/implementation-review-v2/runtime-gates-review.md:44-62` | Current test inventory is stale and labels compile/token checks as evidence | Record the actual current test/build inventory only after it is rerun; do not use stale `docs/STATE.md` counts as current evidence. |

### 5.3 M1 runtime supervisor and manifest records

`knowledgegraph/research/runtime-oracle/automation-audit.md:156-211` identifies the current implementation defects. The existing `tools/observatory/cell_trace.sh` and `tools/observatory/probe_tracer.cpp` require these future updates before M1 can be considered technically ready:

- atomic inherited lock acquisition rather than check-then-start;
- full child/process-tree supervision and exact exit/signal/time classification;
- output opened successfully before breakpoint planting;
- always-written final manifest through one cleanup path;
- malformed JSONL distinguished from zero events;
- active/skipped/retired/dropped probe counts emitted and enforced;
- all expected probes accounted for before calling a run successful;
- window bound to module-host PID where possible, otherwise require stronger `WM_CLASS`/renderer-generation/geometry evidence;
- Cell-specific classifier excluding `FUN_0069b600`;
- real monotonic-time screenshot correlation or removal of `trace_t_nearest`;
- per-step and whole-run deadlines;
- complete binary/probe/harness/tool/environment/geometry/input/log provenance; and
- explicit human handoff for registration/profile preparation.

Existing historical S5 manifests must be preserved as historical negatives, not overwritten or relabeled as M0/M1 passes.

### 5.4 M2 observation capability

`tools/observatory/probe_tracer.cpp` is not an M2 implementation. The repository needs a separately reviewed read-only M2 adapter/debugger capability, or a deliberate extension with all of the following represented in its manifest schema:

- entry frame and direct-call continuation/return pairing;
- exact registers, flags, stack words, float raw bits, and callee-saved comparison;
- owner-qualified state before/after;
- guard windows;
- exact write source or explicit partial coverage;
- called-callee and omitted-effect horizon;
- event/input/mode/object/save/process separation;
- restore/detach evidence.

The existing entry-only tracer may remain a bounded M1 control, but it must not be relabeled M2. The current decompilation-derived 64/64 record cannot fill this gap.

### 5.5 Status/synthesis records that are currently stale or overbroad

| File/record | Required update |
|---|---|
| `docs/analysis/future-research/03-pkg-07-cell-movement.md:18-24` | Replace the “positive boot/Cell reachability/read-only entry-return” wording with the current evidence split: static identity, historical startup, historical Cell negatives, no current M0/M1/M2. |
| `docs/analysis/CELL-RUNTIME-OBSERVATION.md:8-19,35-40` | Preserve as a historical record. Add a current reconciliation/supersession note for the old “xdotool absent” and `0x116B3C04` statements rather than rewriting the historical experiment. |
| `docs/STATE.md:3,89,94,127,185` | Reconcile current state with devlog 018 and the 2026-09-24 audit. In particular, distinguish historical S5 runs from “S5 not started,” and distinguish current CTest inventory from stale `36/36` text. Preserve historical S4 facts and explicit non-results. |
| `docs/analysis/campaigns/cell-stage-campaign.md:511-519` | CS-32 says S5 was not run and that approval alone would promote entries. Update to the historical S5 negative record and state that promotion requires the complete `C-REPLACEMENT` gate, independent adjudication, and human approval. |
| `knowledgegraph/research/runtime-oracle.json:166-176` | `static_preflight_validator` is `NOT_IMPLEMENTED` although a static helper now exists. Change to a qualified status such as `AVAILABLE_PARTIAL_STATIC_ONLY` and list its fail-open gaps; do not mark it complete. |
| `knowledgegraph/research/runtime-oracle.json:155-162` | Update the address-conflict record only after the active manifest is corrected and re-reviewed. Preserve the historical conflict and current decoded candidate as separate records. |
| `knowledgegraph/research/runtime-oracle/replacement-observability.md:38-40,85-100` | Update current conflict status after the manifest correction, while retaining the explicit static-vs-runtime boundary and complete Phase-A requirements. |
| `knowledgegraph/research/runtime-oracle/input-synthesis.md:85-87,280-289` | Mark the current address-conflict disposition accurately after reconciliation; retain the requirement for loaded-module mapping and do not convert it into runtime field verification. |
| `docs/analysis/runtime-oracle-plan.md:107-115,148-162,207-220` | Update capability wording from “no static validator” to “partial static validator with known gaps,” and preserve the no-launch/no-process-write boundary. |

### 5.6 Records that should not be changed into positive runtime claims

These sources are already conservative or intentionally historical and should be retained with their evidence boundaries:

- `docs/analysis/runtime-experiments.md:9-24` — clearly says the experiments are proposed/unverified.
- `knowledgegraph/research/runtime-oracle/candidate-experiments.md:1-13` — clearly says no experiment in the document was executed and no positive Cell result exists.
- `knowledgegraph/research/runtime-oracle/automation-audit.md:14-20,142-211,245-278` — accurately records the human gates and automation blockers.
- `docs/devlog/018-s5-cell-runtime-evidence.md:48-76` — historical S5 negative and explicit non-claims; do not overwrite.
- `knowledgegraph/research/track-m-oracle-plan.json:25-35,37-168,254-320` — correctly separates historical observations, proposed experiments, negative results, and promotion gates.
- `knowledgegraph/research/global-campaign-2026/verify-machine-final5.json:137` — correctly reports runtime-verified count `0`.
- `docs/analysis/implementation-review-v2/pkg07-review.md:5-10,74-76` — correctly reports host implementation only and no runtime verification.

## 6. Final gate matrix

### 6.1 Technical preflight readiness

| Gate | Metadata correction result | Full technical result | Reason |
|---|---|---|---|
| M0 | Stale conflict can be cleared; main-menu file check can remain green | **Not ready** | Trusted manifest identity, complete value checks, independent ABI/caller checks, guard/RET/xref checks, and current run provenance are missing |
| M1 | Manifest can become text-clean | **Not ready** | M0 absent; GUI supervisor, manifest, lock, classifier, registration/profile, and coverage gates unresolved |
| M2 | Address candidate can be text-clean | **Not ready** | M1 absent and current tracer lacks the required return/state/write/callee oracle |

### 6.2 Runtime evidence

| Gate | Current runtime result | Permitted conclusion |
|---|---|---|
| M0 | `NOT_RUN / BLOCKED` | No current boot/attach result; historical startup is historical only |
| M1 | `NOT_RUN / BLOCKED` | No current Cell reachability result; historical zero-event records are bounded negatives |
| M2 | `NOT_RUN / BLOCKED` | No original ABI, return, state, write, or external-effect result |

**No runtime verification may be claimed from static evidence.** In particular, static bytes, PE mapping, decompilation, SDK names, host tests, generated fixtures, screenshots, zero-event traces, clean exits, generic frame callbacks, and the 64/64 decompilation-reference differential cannot satisfy M0, M1, M2, `C-ABI`, `C-SIDE`, `C-STATE`, or `C-REPLACEMENT`.

## 7. Read-only hygiene

- This audit did not launch or attach to Spore.
- This audit did not issue input.
- This audit did not place instrumentation or breakpoints.
- This audit did not read or write a running process’s memory.
- This audit did not modify `SPORE/`, a binary, a profile, a save, a canonical probe manifest, or the canonical KG.
- The only execution was the repository’s static preflight and JSON inspection; its explicit runtime flags remained false.
- The working tree was already dirty before this audit. The report was isolated to `docs/analysis/future-research/pkg07-runtime-oracle-consistency-report.md`; the final git-status check must compare against that pre-existing dirty state, not against an assumed clean tree.
- Post-audit `git status --short --branch` showed the initial dirty entries plus two additional untracked PKG-07 reports not present in the initial snapshot: `docs/analysis/future-research/pkg07-canonical-address-report.md` and `docs/analysis/future-research/pkg07-manifest-provenance-report.md`. A third concurrent report, `docs/analysis/future-research/pkg07-preflight-audit-report.md`, appeared during the final check. None was created, read, edited, or deleted by this audit; their appearance indicates concurrent work in the shared worktree. This report is the only file intentionally written by this audit.
