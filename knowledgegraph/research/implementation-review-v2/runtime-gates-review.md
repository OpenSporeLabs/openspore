# Independent implementation review v2 — runtime gates

**Scope reviewed:** current `tools/observatory/pkg07_preflight.py`, `tools/observatory/probes/cell_movement.json`, `tools/observatory/probes/main_menu.json`, `docs/analysis/future-research/pkg07-runtime-gates.md`, `docs/analysis/runtime-experiments.md`, `docs/analysis/runtime-oracle-plan.md`, `knowledgegraph/research/runtime-oracle/*.md`, current test registrations, and `docs/STATE.md` status wording. No runtime launch, input, debugger action, process-memory read/write, implementation, test, CMake, status, or canonical-KG edit was performed.

## Evidence classification

- **HOST_IMPLEMENTED:** A static/dry-run preflight helper exists at `tools/observatory/pkg07_preflight.py`; the current script reports `runtime_launched=false`, `process_memory_read=false`, and `process_memory_written=false` at lines 240-245.
- **RUNTIME_VERIFIED:** None. The current preflight result is `BLOCKED`; `pkg07-runtime-gates.md:137-149` says M0/M1/M2 are `NOT_RUN / BLOCKED`, and the runtime plan remains `PROPOSED / DESIGN_ONLY` at `docs/analysis/runtime-oracle-plan.md:1-21`.
- **ORIGINAL_COMPATIBLE:** None established. No original target call, return, state, write, or external-effect comparison is present.
- **CHARACTERIZED_ONLY:** Binary hash/size, PE mapping, target/call bytes, static caller/continuation, historical startup evidence, and the known address conflict are static/design records only. The probe manifest still contains the stale global operand at `tools/observatory/probes/cell_movement.json:1-3,31-38`.

## Findings

### GATE-01 — Important — confidence 97 — the Cell probe manifest remains intentionally blocked

**Evidence:** The committed probe description and notes still say `sCellGame` is at `0x116b3c04` at `tools/observatory/probes/cell_movement.json:1-3,31-38`, while the current preflight checks the canonical bytes decode `0x016B3C04` at `tools/observatory/pkg07_preflight.py:178-182`. The observed preflight result marks `cell_probe_manifest` as `BLOCKED`, and `pkg07-runtime-gates.md:43,81,137` explicitly keeps the conflict open.

**Finding:** The address conflict is not silently normalized, and the runtime gate correctly refuses to treat the Cell probe set as ready.

**Impact:** No current M1/M2 result can be interpreted until the probe/address record is reconciled. Treating the probe set as hash-pinned and ready would make a future trace target the wrong global or produce an invalid Cell-reachability classification.

**Recommendation:** Keep the gate blocked. Reconcile the manifest and current binary operand through a reviewed static adjudication, then rerun the complete preflight; do not edit the stale value into a passing alias.

### GATE-02 — Important — confidence 94 — manifest validation is name/count based, not identity/hash pinned

**Evidence:** `pkg07_preflight.py:87-121` parses probe names and numeric values, checks duplicates and a required-name subset, and returns the current file hash. It has no expected manifest hash constants and no expected name-to-address map. The main and Cell checks at lines 186-201 request only five and four names respectively, while the manifests contain seven and twelve probes. The target/call expected values are hard-coded separately at lines 14-21, but are not compared with the Cell manifest’s `values`.

**Finding:** A modified probe manifest can pass the name/count checks if it retains the required names and avoids the stale text, even if a required probe’s address is wrong or the manifest is not the reviewed pinned artifact. The emitted hash is a report, not a comparison against a trusted expected hash.

**Impact:** Once the stale text is removed, the preflight could report `PASS` for an incorrectly addressed Cell probe set and authorize a run with misleading coverage. This undermines the stated hash-pinned and fail-closed gate contract.

**Recommendation:** Pin and compare the exact approved manifest hashes, require the complete expected name set, and compare every expected probe value, including the target, call site, and control addresses. Reject unknown, missing, duplicate, or altered entries.

### GATE-03 — Important — confidence 91 — ABI and caller facts are asserted rather than independently checked

**Evidence:** `pkg07_preflight.py:183-184` emits `static_abi PASS` and `caller_continuation PASS` from hard-coded strings. The script independently decodes the target global operand and call displacement at lines 168-182, but it does not parse the terminal `RET`, stack-frame use, callee-saved behavior, caller xrefs, or the stated `FUN_00E806B0`/continuation relationship.

**Finding:** The preflight verifies bytes and call arithmetic, but labels ABI and caller/continuation records as passed without deriving those facts from an evidence manifest or disassembler.

**Impact:** If the static evidence, binary, or script constants diverge, the preflight can continue to emit reassuring `PASS` records for unverified ABI/caller claims. The result is a useful partial check, not a complete static gate.

**Recommendation:** Source these records from a checked evidence artifact or add explicit byte/stack/xref checks with a test that mutates each required field. Label the current records `STATIC_ASSERTED` until independently derived.

### GATE-04 — Moderate — confidence 90 — test evidence is compile-only and token-presence-only

**Evidence:** `pkg07_preflight.py:204-213` compiles three Python files without executing them. The dry-run check at lines 214-227 only searches shell text for required tokens and explicitly reports that it did not execute them. The current preflight therefore does not run the focused approval/dry-run tests that the runtime audit describes.

**Finding:** The preflight’s `python_test_sources PASS` and `dry_run_contracts PASS` records are not behavioral test results.

**Impact:** A syntax-valid but semantically broken shell or Python contract can still produce a preflight pass. This is especially important because the runtime audit identifies process supervision, lock, classifier, and manifest gaps that token checks cannot detect.

**Recommendation:** Either run the side-effect-free contract suite and record exact command/results, or rename these checks to `COMPILE_ONLY` and `TOKEN_PRESENT_ONLY`. Add direct tests for the preflight’s malformed-manifest, wrong-address, duplicate-name, and hash-mismatch cases.

### GATE-05 — Important — confidence 94 — current test/status inventory is stale for the new movement test

**Evidence:** `src/sim/CMakeLists.txt:93-98` adds `cellmovement_test`, but the current `ctest --test-dir build -N` inventory lists 37 tests and does not list `cellmovement_test`; the corresponding binary is absent. `docs/STATE.md:3` still states `ctest 36/36`, while the new source registration is not represented in the current build inventory.

**Finding:** The source-level test registration exists, but the current on-disk build was not reconfigured/built to include it. The status text therefore cannot be used as evidence that the new test passed.

**Impact:** A reviewer or agent may report a green movement test or a current test count based on stale build metadata. The new PKG-07 seam has no current executable test result in this tree.

**Recommendation:** Reconfigure and build a clean/current build directory, run `cellmovement_test` and the relevant suite, and record the result separately. Do not change status based on the current stale build inventory.

## Runtime status and ownership review

The runtime documents are conservative where they state `PROPOSED`, `UNVERIFIED`, `NOT_RUN`, or `BLOCKED`: `runtime-experiments.md:9-24`, `runtime-oracle-plan.md:44-80`, and `pkg07-runtime-gates.md:55-61,95-105,135-149`. The existing `cell_trace.sh` gaps are also explicitly recorded in `knowledgegraph/research/runtime-oracle/automation-audit.md:156-217`; this review found no basis to promote them.

The static/dry-run helper is not an original runtime oracle. It performs no process launch, input, breakpoint, memory read, or memory write, and it correctly reports those facts. It is nevertheless not sufficient to open the runtime gate until the manifest identity and independent ABI/caller checks above are fixed and the stale address conflict is adjudicated.

## Review disposition

**Runtime gate remains blocked.** The artifacts are honest about the current negative/unverified state, but the preflight has meaningful fail-open validation gaps if the current blocking text conflict is removed. No `RUNTIME_VERIFIED` or `ORIGINAL_COMPATIBLE` claim is supported.
