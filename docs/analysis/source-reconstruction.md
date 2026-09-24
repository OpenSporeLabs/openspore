# Source Reconstruction Swarm

This document is the human-readable control plane for the source-reconstruction campaign. The canonical machine-readable record is `knowledgegraph/research/source-reconstruction-manifest.json`; runtime hypotheses are in `docs/analysis/future-research/source-reconstruction-runtime-gates.md`.

## Objective

Convert live Ghidra evidence and the existing semantic/state artifacts into progressively integrated C++ source. Existing OpenSpore code is a comparison seam, not evidence for original semantics. No target executable or canonical Ghidra analysis is modified.

## Current campaign state

- Binary: `SporeApp.exe` 3.1.0.22, SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`.
- Indexed functions: 58,757.
- Seeded high-priority records: 15, all with current decompilation/disassembly evidence.
- Integrated and reviewed source bodies: 10 across `PKG-01-SHARED-STATE-ROOTS`, `PKG-06-CELL-STATE`, `PKG-10-EDITOR-DISPATCH`, and `PKG-12-SIM-SPACE`; all 10 retain their runtime gates.
- Completed audit: 10 functions; P0=1, P1=9, P2=1, P3=0; repairs=1; clean findings=9; runtime-gated findings=10; `runtime_validated=0`. Severity counts include propagation/document boundaries, and repaired PKG-12 is clean after semantic and ABI re-review.
- Post-audit checks: package syntax=4, editor model=1, Python=427, CTest=42, CMake build=1, format=1, JSON validation=2, and `git diff --check`=1. The detailed report is `docs/analysis/source-reconstruction-audit.md`.
- Blocked seeded records: 5 — four PKG-15 palette records and one PKG-20 GameGlobal record have no reviewed staging source and are not assigned fabricated canonical paths.
- Runtime-validated functions: 0. The historical Cell run is negative and does not promote semantics; repository, syntax, formatting, and model-test success does not claim original-binary compatibility.
- Package state: 4 complete, 0 in progress. Target-ABI sources remain under `src/reconstruction/` and are intentionally excluded from the normal 64-bit CMake build.
- Repository validation: Python 427 passed, CTest 42 passed, and the normal CMake build passed.
- Reconstruction validation: Google formatting passed for all 10 integrated files; x86-32 syntax passed for all four packages; the editor dispatch model test passed; manifest and handoff JSON validation passed; `git diff --check` passed.

## Evidence and reconstruction rules

1. Live Ghidra decompilation/disassembly outranks all other evidence.
2. Caller/callee and xref evidence establishes dependencies and dispatch boundaries, not names by itself.
3. Live structure, field-offset, and vtable evidence outranks SDK aliases and existing source.
4. Strings, constants, globals, and data references constrain concrete mechanics.
5. Persisted semantic contracts and state/event archaeology refine static reconstruction but do not replace it.
6. Existing OpenSpore code is a comparison/reference only.
7. SDK/imported names are accepted only when corroborated by bytes or direct evidence.
8. A static body is still reconstructed when runtime state is gated; the gate is recorded per function and per material guess.
9. Runtime experiments require explicit human approval, the repository machine lock, a pinned binary/environment, and a smallest observable experiment.
10. Local differential checks compare modeled behavior against a decompilation reference; they do not prove original binary compatibility.

## Package workflow

### Phase 1: types and signatures

A package worker owns disjoint source files under `reconstruction/staging/<package>/`. The worker resolves canonical local types, explicit opaque types, calling conventions, return widths, `this` ownership, vtable boundaries, and field offsets. Shared types are not integrated until the integrator resolves collisions.

### Phase 2: bodies

After the local skeleton is available, workers inspect the live body, assembly, callers, callees, relevant structures, and vtables. Bodies preserve branch ordering, allocation/release order, integer widths, pointer/value semantics, error/null behavior, sentinels, and virtual dispatch boundaries. Material uncertainty uses explicit `RE:` annotations and a manifest unresolved-question entry.

### Phase 3: review

Each batch receives independent semantic and ABI/type reviews. Reviewers report findings tied to a function and evidence; they do not rewrite an entire package without a concrete defect.

### Phase 4: integration

The integrator owns shared headers, CMake registration, canonical manifest updates, and KG reconciliation. Integration requires formatting/build/CTest/Python validation and a clean diff review. A package is integrated only when its tests pass; no tests are weakened to obtain green status.

## Scheduling policy

The scheduler ranks executable work by shared-state centrality, dependency unlock value, caller fan-in, callee fan-out, architecture relevance, evidence confidence, runtime-gate locality, and package readiness. `LIKELY_INFRASTRUCTURE` is characterized or stubbed only; it is not silently treated as gameplay source.

The first wave is deliberately split by ownership:

- `pkg01-roots`: accessor and service-slot mechanics; no invented manager types.
- `pkg06-cell-state`: damage, reset, and removal state transitions with opaque cell fields.
- `pkg10-editor-dispatch`: mode transition mechanics, kept separate from UTFWin/UI ownership.
- `pkg12-space`: communication state mechanics, kept separate from local Sporepedia metadata.

Workers may write only their assigned staging files and return a handoff containing changed files, reconstructed functions, types, tests, evidence, unresolved questions, and blockers. The integrator copies or merges only after review.

## Metrics and deltas

After each integrated batch, update manifest metrics with totals and deltas for signatures, bodies, reviews, integrations, runtime validation, runtime gates, deferred work, blockers, tests, and package completion. A negative runtime result remains a negative result.

## Validation baseline

Repository validation commands are:

```text
cmake -S . -B build
cmake --build build -j
ctest --test-dir build -V
python3 -m unittest discover -s tests -t . -v
git diff --check
```

Optional real-asset checks require the local `SPORE/` install and are not part of the hermetic baseline.
