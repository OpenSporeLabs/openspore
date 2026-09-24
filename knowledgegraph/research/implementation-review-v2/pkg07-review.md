# Independent implementation review v2 — PKG-07 re-review

**Scope reviewed:** final on-disk `src/sim/CellMovement.hpp`, `src/sim/CellMovement.cpp`, `src/sim/tests/cellmovement_test.cpp`, `src/sim/CellGame.hpp`, `src/sim/CellGame.cpp`, `src/sim/CMakeLists.txt`, and the existing `Sim` movement path. I also verified the current build registration and ran `build/src/sim/cellmovement_test` plus `ctest --test-dir build -R '^cellmovement_test$'`; both passed. No implementation or other file was modified.

## Evidence classification

- **HOST_IMPLEMENTED:** The pool-backed helper is now integrated into the `CellGame` API through `mMovementState`, `CellGame::applyCellMovement`, and `CellGame::routeCellMovement` (`src/sim/CellGame.hpp:85-89,175-181`; `src/sim/CellGame.cpp:172-192`). It is still not the original ABI.
- **RUNTIME_VERIFIED:** None. M0/M1/M2 remain `NOT_RUN / BLOCKED` in `docs/analysis/future-research/pkg07-runtime-gates.md:137-149`.
- **ORIGINAL_COMPATIBLE:** None established. The existing replacement boundary remains `replaced-approx`; the new host lifecycle is not evidence of the original serializable moving byte or original call ordering.
- **CHARACTERIZED_ONLY:** Static ray/plane and target/orientation/moving-field shape remains bounded by `docs/analysis/dossiers/cell-movement.md:46-59`; exact-vs-epsilon behavior is now an explicit host boundary, not original runtime evidence.

## Prior findings

### PKG07-01 — Important — **PARTIALLY RESOLVED / OPEN** — CellGame integration is present, application integration is not

**Prior finding:** The helper was not wired into the Cell host path and was exercised only by its standalone test.

**Current evidence:** `CellGame` now owns `mMovementState` and delegates to the pool-backed helper (`src/sim/CellGame.hpp:85-89,175-181`; `src/sim/CellGame.cpp:172-192`). The integration test creates a `CellGame`, allocates a pool-backed target, routes input, and checks target/orientation/lifecycle updates (`src/sim/tests/cellmovement_test.cpp:366-410`). However, repository search still finds `CellGame::applyCellMovement`/`routeCellMovement` calls only in that test; `cell_stage` and `CellSim::update` remain the actual playable path (`src/sim/Sim.cpp:103-260`).

**Impact:** The CellGame host boundary is real and tested, but the application/update pipeline still does not invoke it. End-to-end PKG-07 host behavior remains unproven.

**Recommendation:** Keep this finding open until a production mode/update caller drives `CellGame::routeCellMovement` and an integration test covers that caller. Do not count the CellGame wrapper test as `cell_stage` coverage.

### PKG07-02 — Important — **RESOLVED for host scope / OPEN for original compatibility** — explicit movement lifecycle added

**Prior finding:** The helper omitted the moving state and owner.

**Current evidence:** `CellMovementLifecycle` now has `moving` and `ownerIndex` (`src/sim/CellMovement.hpp:41-44`); successful movement commits both only after valid orientation (`src/sim/CellMovement.cpp:129-141`). `CellGame::initialize` resets the lifecycle (`src/sim/CellGame.cpp:29-31`), and the test checks owner assignment, failure preservation, and reset clearing (`src/sim/tests/cellmovement_test.cpp:91-108,269-307,400-404`).

**Impact:** The host seam no longer loses the moving state or leaves ownership ambiguous. This does not establish the original `[serializable pointer + 0xE0] = 1` write, clearing rule, or runtime ordering; those remain `CHARACTERIZED_ONLY`/unverified.

**Recommendation:** Close the host-lifecycle portion only. Keep original moving-byte compatibility open until a runtime oracle or equivalent approved evidence resolves its owner and lifecycle.

### PKG07-03 — Important — **OPEN** — exact and epsilon geometry remain separate contracts

**Prior finding:** Duplicate movement implementations had divergent parallel behavior and state ownership.

**Current evidence:** `CellMovement` now exposes `intersectCameraRayWithMovementPlaneExact` with exact `denominator == 0.0F` handling and a local hit buffer (`src/sim/CellMovement.cpp:41-91`). The boundary test deliberately uses `5e-7F`, proving exact intersection returns a hit while the legacy `Sim::rayPlaneHit` epsilon rejects it (`src/sim/tests/cellmovement_test.cpp:145-178`). The production `Sim` path still uses the epsilon helper (`src/sim/Sim.hpp:139-164`; `src/sim/Sim.cpp:124-139`).

**Impact:** The exact-vs-epsilon boundary is now visible and tested, but the repository still has two movement contracts. A caller can observe different hit/miss behavior depending on which host path is used, and only the exact path is connected to CellGame.

**Recommendation:** Keep this open. Select one production geometry contract or explicitly retain both with non-overlapping ownership and a documented conversion/selection rule. The test should remain as a boundary regression.

### PKG07-04 — Important — **RESOLVED** — orientation failures are atomic

**Prior finding:** Unresolved orientation left a mutated target while returning failure.

**Current evidence:** `CellMovement.cpp:116-127` resolves and validates orientation before any target, orientation, or lifecycle write. The test covers unresolved status, invalid-input status, NaN components, zero quaternion, and preservation of the prior target/lifecycle (`src/sim/tests/cellmovement_test.cpp:251-307`).

**Impact:** A failed resolver no longer creates a target/orientation mismatch. `targetHit` may report the geometric hit, but `targetUpdated`, `orientationUpdated`, and `movingStateUpdated` remain false, so the result is explicitly non-committing.

**Recommendation:** No further remediation required for atomic host failure handling. Keep the result/status distinction documented so callers do not treat `targetHit` as a committed update.

### PKG07-05 — Moderate — **RESOLVED for current targeted test** — edge, pool, router, and registration coverage added

**Prior finding:** Tests omitted invalid inputs, orientation failures, pool/router cases, lifecycle coverage, and current registration evidence.

**Current evidence:** The test now covers invalid time/ray/plane values, zero geometry, exact parallel/behind isolation, unresolved/invalid/nonfinite/zero orientation, invalid and freed pool indices, router rejection, successful route commit, CellGame integration, reset, and uninitialized routing (`src/sim/tests/cellmovement_test.cpp:181-410`). `src/sim/CMakeLists.txt:93-98` registers `cellmovement_test`; the current binary exists, and both direct execution and targeted CTest pass.

**Impact:** The remediation closes the previously identified host-test gaps for this focused test. A full-suite result was not run in this re-review, so the finding is resolved for the targeted registration/test, not for unrelated regression coverage.

**Recommendation:** Retain this test and record the targeted command/result with the change evidence. Run the broader suite separately if a full project gate is required.

## New bounded observation

### PKG07-06 — Moderate — **OPEN / contract clarification** — orientation validation does not require a unit quaternion

**Evidence:** `validOrientation` only requires finite components and a positive squared norm (`src/sim/CellMovement.cpp:22-29`). The success test intentionally supplies `{1,2,3,4}` and accepts it (`src/sim/tests/cellmovement_test.cpp:63-69,91-103`).

**Impact:** If `mTargetOrientation` is required to be a normalized rotation quaternion, non-unit values can produce a non-rotation transform even though the result is `updated`. The current host contract does not state whether normalization is required, so this is not an original-compatibility claim.

**Recommendation:** Specify the host orientation invariant. If unit-length is required, validate or normalize it explicitly and add zero/non-unit/negative-scale cases; if arbitrary finite orientation values are intentional, rename/document the contract so the nonzero check is not mistaken for quaternion validation.

## Disposition

**PARTIALLY COMPLETE:** `HOST_IMPLEMENTED` for the CellGame pool-backed host seam, `RUNTIME_VERIFIED` none, `ORIGINAL_COMPATIBLE` none, `CHARACTERIZED_ONLY` for original movement semantics. Resolved: movement lifecycle ownership, atomic orientation failure, invalid pool/router handling, exact-vs-epsilon boundary coverage, and current targeted test registration/execution. Open: application-level caller integration, duplicated production geometry/state contracts, original moving-byte compatibility, and the unit-quaternion contract decision.
