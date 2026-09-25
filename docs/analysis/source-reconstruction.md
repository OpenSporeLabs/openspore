# Source Reconstruction Swarm

This document is the human-readable control plane for the source-reconstruction campaign. The canonical machine-readable record is `knowledgegraph/research/source-reconstruction-manifest.json`; runtime hypotheses are in `docs/analysis/future-research/source-reconstruction-runtime-gates.md`.

## Objective

Convert live Ghidra evidence and the existing semantic/state artifacts into progressively integrated C++ source. Existing OpenSpore code is a comparison seam, not evidence for original semantics. No target executable or canonical Ghidra analysis is modified.

## Current campaign state

- Binary: `SporeApp.exe` 3.1.0.22, SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`.
- Indexed functions: 58,757.
- Function records: 65, including 60 reviewed/integrated bodies and 5 blocked seeded records.
- Integrated and reviewed source bodies: 60 across `PKG-01-SHARED-STATE-ROOTS`, `PKG-06-CELL-STATE`, `PKG-06A-CELL-AI-SELECTION`, `PKG-10-EDITOR-DISPATCH`, `PKG-11-SIM-CORE`, `PKG-12-SIM-SPACE`, `PKG-13-CREATURE-ACCESSOR`, `PKG-13-SIM-CREATURE-TRIBECIV`, `PKG-13-SIM-DIPLOMACY-PREDICATE`, `PKG-13-SIM-DIPLOMACY-PRIMITIVES`, `PKG-13-SIM-DIPLOMACY-TRANSITIONS`, `PKG-16-SPOREPEDIA-ONLINE`, `PKG-18-UI-SCRIPTING`, `PKG-18-UI-SPACE`, `PKG-20-PROPERTY-ADAPTER`, `PKG-20-RESOURCE-ADAPTER`, `PKG-20-PERSISTENCE-BOUNDARY`, and `PKG-20-GAMEGLOBAL`; all 60 retain runtime gates.
- Historical audit: 10 functions; P0=0, P1=9, P2=1, P3=0; repairs=1; clean findings=10; runtime-gated findings=10; `runtime_validated=0`. The PKG-20 map P0 contradiction is statically resolved as a fixed guarded-hybrid lower-bound contract without changing the historical 10-function audit count.
- Current checks: x86-32 package syntax=22, source-wave5 focused model tests=2, CTest=42, Python=427, CMake build=1, JSON validation, and modified Google formatting for all 60 source-wave2/source-wave3/source-wave4/source-wave5 canonical files passed.
- Blocked seeded records: 5 — four PKG-15 palette records and one PKG-20 GameGlobal record have no reviewed staging source and are not assigned fabricated canonical paths.
- Runtime-validated functions: 0. The historical Cell run is negative and does not promote semantics; repository, syntax, and model-test success does not claim original-binary compatibility.
- Package state: 21 complete, 1 in progress. PKG-20 GameGlobal retains seeded `0x00dd0e10` as blocked. Target-ABI sources remain under `src/reconstruction/` and are intentionally excluded from the normal 64-bit CMake build.
- Repository validation: normal CMake build, 42/42 CTest, and 427/427 Python tests passed.
- Reconstruction validation: 22 x86-32 packages and 20 source-wave2/source-wave3/source-wave4/source-wave5 focused models passed with `-Werror`; all 60 source-wave2/source-wave3/source-wave4/source-wave5 canonical files pass modified Google formatting; manifest, source-wave5 metadata, source-wave5 handoff JSON, recorded hashes, and `git diff --check` passed.

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
- `pkg10-editor-dispatch`: mode transition mechanics, raw/formal SetColor ABI separation, and EditorUI command routing, kept separate from UTFWin/UI ownership.
- `pkg11-sim-core`: constant star predicate, noun projection callbacks, and guarded-hybrid empire lookup, with concrete map allocation and callback ownership kept gated.
- `pkg12-space`: communication state mechanics, player-empire cache refresh, and the private cCommEvent create/dispatch wrapper, kept separate from local Sporepedia metadata.
- `pkg13-creature-state`: creature progression globals, brain-level threshold dispatch, and a bounded tribe purchased-tool predicate; imported receiver identities are not accepted without layout and caller evidence.
- `pkg13-creature-accessor`: exact ECX-only 32-bit noun-manager field load from receiver `+0x54`; concrete field type, ownership, and runtime availability remain gated.
- `pkg13-diplomacy-predicate`: alliance predicate with current-empire substitution and directed identity ordering; shared map helpers remain opaque dependencies.
- `pkg13-diplomacy-primitives`: relationship lookup conversion and map selector with exact fallback, high-bit, stride, and cleanup mechanics; tree/vector helper bodies remain opaque.
- `pkg13-diplomacy-transitions`: four directed relationship transition bodies with reviewed pair ordering, event-carrier layout, root callback receiver chains, and fused array stack carry; all service, event, root, and relationship owners remain opaque runtime gates.
- `pkg16-sporepedia`: three local asset-data access bodies with exact raw instruction semantics; SDK bool/name/asset-ID aliases remain separate from observed full-word, vtable-tail, and x87-constant behavior.
- `pkg18-ui-scripting`: three shell message, enable-state, and owner-route bodies with explicit shell/service/vtable boundaries; runtime message identity and callback ownership remain gated.
- `pkg18-ui-space`: two Space UI bodies, including text-zoom rebinding, with opaque object/vtable/resource ownership and unresolved downstream services.
- `pkg20-property-adapter`: direct property-list boolean lookup with stack-local Property, opaque list tail, materializer fallback, and cleanup callback boundaries.
- `pkg20-resource-adapter`: texture-pointer replacement with exact refcount acquire/store/release/clamp order and opaque owner/concurrency semantics.
- `pkg20-persistence-boundary`: paint-job preparation and bake-submission boundary with explicit allocator, property, service, and cleanup ports.
- `pkg20-gameglobal`: fixed guarded-hybrid ordered-map search and insertion with immutable map/node mechanics; generic value payload, allocator, and runtime root publication remain gated.

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
