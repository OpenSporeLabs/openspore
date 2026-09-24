# Implementation Review v2 — PKG-07 and PKG-16

**Review date:** 2026-09-24
**Disposition:** PKG-07 is `HOST_IMPLEMENTED`, with runtime and original-compatibility gates open. PKG-16 remains `CHARACTERIZED_ONLY / NOT_IMPLEMENTED`.
**Status synthesis:** [implementation-status-v2.md](./implementation-status-v2.md)

## Evidence reviewed

- Final PKG-07 host files and focused tests: `src/sim/CellMovement.hpp`, `src/sim/CellMovement.cpp`, `src/sim/CellGame.hpp`, `src/sim/CellGame.cpp`, `src/sim/tests/cellmovement_test.cpp`, and `src/sim/CMakeLists.txt`.
- Replacement/reference boundary: `src/replace/Replace.*`, `src/replace/Reference.cpp`, `src/replace/CellGameView.hpp`, and `src/replace/tests/diff_test.cpp`.
- Gate/characterization contracts: `docs/analysis/future-research/pkg07-runtime-gates.md` and `docs/analysis/future-research/pkg16-unknowns.md`.
- Isolated reviews: [PKG-07 review](../../knowledgegraph/research/implementation-review-v2/pkg07-review.md), [PKG-16 review](../../knowledgegraph/research/implementation-review-v2/pkg16-review.md), and [runtime-gates review](../../knowledgegraph/research/implementation-review-v2/runtime-gates-review.md).
- Current validation: build, focused movement test, 64/64 decompilation-reference differential, Python 417/417, CTest 42/42, targeted CTest 1/1, `git diff --check`, static preflight, and formatting dry check.

The repository had numerous pre-existing modified and untracked files across unrelated packages. Those dirty-tree files are not attributed to PKG-07, PKG-16, or this documentation campaign. The test results describe the current tree, not a clean-worktree provenance claim.

## Critical

No critical implementation defect was established in the reviewed host/test scope. This does not reduce the Important runtime and evidence gates below.

## Important — open

### PKG07-01 — application-level integration remains open

The pool-backed seam is integrated into `CellGame` and tested there, but `CellGame::applyCellMovement`/`routeCellMovement` are not driven by the current playable application/update path. The `CellGame` test is not `cell_stage` coverage. This blocks an end-to-end host claim, but not the narrower `HOST_IMPLEMENTED` CellGame-seam status.

Source: [PKG-07 review, PKG07-01](../../knowledgegraph/research/implementation-review-v2/pkg07-review.md#prior-findings)

### PKG07-03 — duplicate production geometry contracts remain open

The exact `denominator == 0.0F` helper and the legacy epsilon-based `Sim::rayPlaneHit` coexist, with a tested disagreement below the epsilon boundary. Selection between the two contracts is not defined for production callers. The boundary regression is useful; it does not resolve ownership.

Source: [PKG-07 review, PKG07-03](../../knowledgegraph/research/implementation-review-v2/pkg07-review.md#prior-findings)

### GATE-01 — Cell probe address conflict remains open

`tools/observatory/probes/cell_movement.json` retains `0x116B3C04`, while the current target bytes decode `0x016B3C04`. Preflight correctly reports `cell_probe_manifest=BLOCKED`; the values must not be silently aliased. This keeps M0/M1/M2 blocked.

Source: [runtime-gates review, GATE-01](../../knowledgegraph/research/implementation-review-v2/runtime-gates-review.md#gates)

### GATE-02 — manifest identity/address validation is incomplete

Preflight validates names, counts, duplicates, and required names, and reports a hash, but it does not compare an approved expected hash or the complete expected name-to-address map. The review identifies fail-open risk if the stale text is removed without a stronger identity check.

Source: [runtime-gates review, GATE-02](../../knowledgegraph/research/implementation-review-v2/runtime-gates-review.md#gates)

### GATE-03 — ABI and caller facts are asserted, not independently derived

Target bytes, the global operand, and direct call arithmetic are checked. The terminal `RET`, stack behavior, callee-saved behavior, caller xrefs, and dynamic-caller boundary are represented by static records rather than fully independent checks. The current preflight output therefore overstates the strength of `static_abi` and `caller_continuation` as standalone gate evidence.

Source: [runtime-gates review, GATE-03](../../knowledgegraph/research/implementation-review-v2/runtime-gates-review.md#gates)

### PKG16-01 — no PKG-16 implementation exists

The package is correctly `CHARACTERIZED_ONLY / NOT_IMPLEMENTED`. There is no projection type, fixture, provider, disabled seam, or package-specific test surface. Promotion to `HOST_IMPLEMENTED` or `ORIGINAL_COMPATIBLE` is unsupported.

Source: [PKG-16 review, PKG16-01](../../knowledgegraph/research/implementation-review-v2/pkg16-review.md#findings)

## Moderate — open

### PKG07-06 — orientation invariant is unspecified

The host accepts any finite orientation with positive squared norm, including the test's non-unit `{1,2,3,4}`. If the field is intended to be a rotation quaternion, the current result can represent a non-rotation transform. The host convention must be documented or enforced; this is not an original-compatibility finding.

Source: [PKG-07 review, PKG07-06](../../knowledgegraph/research/implementation-review-v2/pkg07-review.md#new-bounded-observation)

### GATE-04 — preflight labels compile/token checks as tests

`python_test_sources` compiles three files without executing them, and `dry_run_contracts` checks token presence without behavior. The current full Python suite executes the contract tests, but the preflight helper itself still lacks negative tests for malformed manifests, wrong addresses, duplicate names, and hash mismatch.

Source: [runtime-gates review, GATE-04](../../knowledgegraph/research/implementation-review-v2/runtime-gates-review.md#gates)

### PKG16-02 — blueprint terminology can imply an unestablished protocol

Blueprint wording around “local request/response” and an online request/response lifecycle is stronger than the characterization allows. No protocol, transport, request identity, response schema, or online state machine is established. The characterization's no-protocol/no-network boundary controls.

Source: [PKG-16 review, PKG16-02](../../knowledgegraph/research/implementation-review-v2/pkg16-review.md#findings)

### PKG16-03 — future test matrix is not instantiated

The required incomplete/wildcard key, optional asset-ID, caller-isolation, error-category, no-network, and fixture-boundary checks are specified but not executable. This is correctly an open implementation prerequisite, not a current defect in a host implementation.

Source: [PKG-16 review, PKG16-03](../../knowledgegraph/research/implementation-review-v2/pkg16-review.md#findings)

### Formatting — current check is not clean or canonical

An explicit `clang-format --dry-run --Werror --style=Google` check over the reviewed C++ files reports violations. The repository has no tracked `.clang-format`, so this check is non-authoritative and formatting status is `NOT ESTABLISHED`; no source formatting change was made by this documentation-only campaign.

## Resolved or closed in the reviewed scope

### PKG07-02 — host movement lifecycle ownership

`CellMovementLifecycle` records `moving` and `ownerIndex`; successful movement commits both after orientation validation, while `CellGame` initialization/reset clears ownership. This resolves the host-lifecycle gap only. The original serializable moving-byte location, clear timing, and owner remain open.

Source: [PKG-07 review, PKG07-02](../../knowledgegraph/research/implementation-review-v2/pkg07-review.md#prior-findings)

### PKG07-04 — orientation failure is atomic

Orientation is resolved and validated before target, orientation, or lifecycle writes. Unresolved, invalid, non-finite, and zero orientation cases preserve prior state. `targetHit` can describe geometry without implying a committed update.

Source: [PKG-07 review, PKG07-04](../../knowledgegraph/research/implementation-review-v2/pkg07-review.md#prior-findings)

### PKG07-05 — focused test and registration gaps are closed

The focused test now covers invalid inputs, geometry boundaries, orientation failures, pool/router guards, lifecycle, integration, reset, and uninitialized routing. The current build includes `cellmovement_test`; direct execution and targeted CTest pass.

Source: [PKG-07 review, PKG07-05](../../knowledgegraph/research/implementation-review-v2/pkg07-review.md#prior-findings)

### GATE-05 — current stale-build manifestation is closed, not the underlying gate

The isolated runtime review found that `cellmovement_test` was absent from the then-current build inventory. The current tree has been rebuilt and registered: focused CTest is 1/1 and the full suite is 42/42. This resolves the stale-build observation for this validation run; it does not resolve M0/M1/M2.

Source: [runtime-gates review, GATE-05](../../knowledgegraph/research/implementation-review-v2/runtime-gates-review.md#gates)

## Validation disposition

- `cmake --build build -j`: **PASS**.
- `python3 -m unittest discover -s tests -t . -v`: **PASS**, 417 tests, `OK`.
- `ctest --test-dir build --output-on-failure`: **PASS**, 42/42.
- `ctest --test-dir build -R '^cellmovement_test$' --output-on-failure`: **PASS**, 1/1.
- `build/src/replace/replace_diff_test`: **PASS**, 64/64 against decompilation reference, 0 mismatches, not live runtime.
- `git diff --check`: **PASS**.
- `python3 tools/observatory/pkg07_preflight.py --json`: **BLOCKED**, stale `0x116B3C04` in the Cell manifest; no launch, input, breakpoint, or process-memory operation.
- Formatting: **NOT ESTABLISHED / non-authoritative Google-style dry check failed**.

Green host and reference tests do not close the Important runtime, application-integration, protocol, or human-approval findings. PKG-07 remains `HOST_IMPLEMENTED` with `RUNTIME_VERIFIED` and `ORIGINAL_COMPATIBLE` explicitly unestablished; PKG-16 remains `CHARACTERIZED_ONLY / NOT_IMPLEMENTED`.
