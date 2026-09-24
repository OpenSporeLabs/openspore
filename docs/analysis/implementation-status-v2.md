# Implementation Status v2 — PKG-07 and PKG-16

**Campaign date:** 2026-09-24
**Owner scope:** final documentation synthesis only
**Overall disposition:** PKG-07 is `HOST_IMPLEMENTED`; PKG-16 remains `CHARACTERIZED_ONLY / NOT_IMPLEMENTED`.

## Scope and evidence policy

This status is derived from the current final on-disk PKG-07 implementation and tests, the PKG-07 runtime-gate contract, the PKG-16 unknowns contract, and the three isolated implementation-review artifacts. The review artifacts are [PKG-07](../../knowledgegraph/research/implementation-review-v2/pkg07-review.md), [PKG-16](../../knowledgegraph/research/implementation-review-v2/pkg16-review.md), and [runtime gates](../../knowledgegraph/research/implementation-review-v2/runtime-gates-review.md). The synthesis is in [implementation-review-v2.md](./implementation-review-v2.md).

Host compilation, unit tests, fixtures, and decompilation-reference comparisons establish only the tested host/reference boundary. They do not establish live original behavior, field meanings, original ABI execution, original compatibility, or status promotion. Decompilation remains evidence, not runtime truth. The canonical executable and `SPORE/` were inspected only through the static preflight; no process was launched, attached, read, modified, or instrumented.

The working tree contained numerous pre-existing modified and untracked files across unrelated packages. This campaign does not attribute those dirty-tree files to PKG-07, PKG-16, or this documentation update. Validation below is a snapshot of the current tree, not a clean-worktree provenance claim. No commit was created.

## PKG-07 — status and semantic contract

| Classification | Current status |
| --- | --- |
| `HOST_IMPLEMENTED` | **Yes**, for the `CellGame` pool-backed host movement seam in `src/sim/CellMovement.*`, integrated through `src/sim/CellGame.*` and registered by `src/sim/tests/cellmovement_test.cpp`. |
| `RUNTIME_VERIFIED` | **Not established.** M0, M1, and M2 are `NOT_RUN / BLOCKED`. |
| `ORIGINAL_COMPATIBLE` | **Not established.** The existing replacement boundary remains `replaced-approx`. |
| `CHARACTERIZED_ONLY` | Original movement semantics, the physical moving store, exact call ordering, omitted callees, and original gates remain static/decompilation-bounded. |

The implemented host contract is:

1. Validate finite, nonzero camera direction and plane normal; compute the exact dot-product denominator without an epsilon.
2. Return `parallel` only for `denominator == 0.0F`; reject non-finite results, return `behind` for `t < 0`, and do not partially write the output buffer on failure.
3. On a hit, resolve orientation before committing any target, orientation, or lifecycle state.
4. Require a finite, nonzero orientation, then atomically store the target position, resolved orientation, `moving = true`, and the pool `ownerIndex` in `CellGame::mMovementState`.
5. Reject invalid or freed pool indices and unavailable router input without mutating target or lifecycle state.
6. Reset movement ownership through `CellGame` initialization/reset.

The host test covers valid and oblique intersections, the below-epsilon exact/legacy boundary, parallel and behind rays, invalid/non-finite inputs, atomic orientation failures, invalid/freed pool indices, routing, `CellGame` integration, reset, and uninitialized routing.

This contract is not yet the production application path. `CellGame::applyCellMovement` and `CellGame::routeCellMovement` are exercised by the host test, but the current playable `Sim` path does not drive them. The exact intersection helper and the existing epsilon-based `Sim::rayPlaneHit` remain separate contracts. The host orientation check requires finite nonzero values, not a unit quaternion; that convention remains to be specified.

## Original ABI and decompilation-differential boundary

Static evidence identifies the original target as linked VA `0x00E5B790`, PE RVA `0x00A5B790`, file offset `0x00A5AB90`, entry bytes `a1 04 3c 6b 01`; the bounded direct call site is `0x00E8083B`, bytes `e8 50 af fd ff`, with continuation `0x00E80840`. The static ABI record is x86-32 cdecl `void(float)`, with `deltaTime` at `[ESP+4]`, zero stack delta, preserved `EBX/EBP/ESI/EDI`, and plain `RET` at `0x00E5BA01`. The complete dynamic caller set is unknown.

`build/src/replace/replace_diff_test` reports **8 cases × 8 fields = 64/64 matches, 0 mismatches** against a decompilation-derived reference. That comparison deliberately omits or stands in for the per-frame environment updates, camera/UI gates, real pool-index resolution, live global state, and other external effects. The orientation and field meanings are inferred, and plane values were never read from a live Cell process. The result is `APPROXIMATION`/reference evidence and remains `replaced-approx`; it cannot substitute for M2 or `C-REPLACEMENT`.

## PKG-07 runtime gates

| Gate | Exact current status | Blocking facts |
| --- | --- | --- |
| M0 | `NOT_RUN / BLOCKED` | No current hash-pinned positive boot control. The Cell manifest still contains stale `0x116B3C04` text while the binary decodes `0x016B3C04`; manifest reconciliation is required. |
| M1 | `NOT_RUN / BLOCKED` | M0 is not complete; no current attributable Cell-specific lifecycle/target-path capture exists. Registration/profile handoff and the manifest conflict remain unresolved. |
| M2 | `NOT_RUN / BLOCKED` | M1 is absent; no original target call or paired entry/return observation exists. The current entry-only tracer is not sufficient for strict return, post-state, write, and omitted-callee coverage. |

`python3 tools/observatory/pkg07_preflight.py --json` returned `overall=BLOCKED`. Canonical executable size/hash, PE identity/mapping, target/call bytes, call decoding, current global interpretation, and main-menu manifest checks passed. `cell_probe_manifest` was `BLOCKED` because `tools/observatory/probes/cell_movement.json` contains stale `0x116b3c04`; `runtime_status` was also `BLOCKED`. The report states `runtime_launched=false`, `process_memory_read=false`, `process_memory_written=false`, and `canonical_kg_written=false`.

The helper's `static_abi` and `caller_continuation` records are static assertions, not independently derived runtime or complete disassembly evidence. Its Python check compiles three contract files without executing them, and its dry-run check is token-presence-only. The separate full Python suite executed those tests, but the preflight labels themselves remain open review findings.

## Current validation results

Commands were run on 2026-09-24 from the repository root against the current dirty tree.

| Command | Result |
| --- | --- |
| `cmake --build build -j` | **PASS**; all configured targets built with the project’s `-Wall -Wextra -Werror` flags. |
| `build/src/sim/cellmovement_test` | **PASS**; `cellmovement_test: ALL PASS`. |
| `ctest --test-dir build -R '^cellmovement_test$' --output-on-failure` | **PASS**; 1/1. |
| `build/src/replace/replace_diff_test` | **PASS**; 64/64 decompilation-reference field comparisons, 0 mismatches; not live runtime verification. |
| `python3 -m unittest discover -s tests -t . -v` | **PASS**; **417 tests**, `OK`, 87.551 seconds. ResourceWarnings were emitted by existing tests but did not fail the suite. |
| `ctest --test-dir build --output-on-failure` | **PASS**; **42/42**, 100%, 9.10 seconds. |
| `git diff --check` | **PASS**; no whitespace errors reported. |
| `clang-format --dry-run --Werror --style=Google src/sim/CellMovement.hpp src/sim/CellMovement.cpp src/sim/CellGame.hpp src/sim/CellGame.cpp src/sim/tests/cellmovement_test.cpp src/replace/Replace.hpp src/replace/Replace.cpp src/replace/Reference.cpp src/replace/CellGameView.hpp src/replace/tests/diff_test.cpp` | **FAIL / NOT AUTHORITATIVE**; violations were reported. The repository has no tracked `.clang-format`, so explicit Google style is only an ad hoc check and canonical formatting remains unestablished. |

## Bounded unknowns

- Production caller integration: no playable application/update path currently drives the `CellGame` movement seam.
- Geometry ownership: exact and epsilon-based movement paths remain separate and can disagree below `1e-6`.
- Orientation invariant: finite nonzero values are accepted; whether the host requires a unit quaternion is unspecified.
- Original ABI behavior: no current M0/M1/M2 original-process evidence.
- Original state ownership: live `sCellGame` values, player index-to-object resolution, moving-byte owner/clear timing, pool lifetime, and write ordering are unresolved.
- Camera, lock, and UI gates: original values and causal order are not runtime-confirmed.
- Movement-plane normal/point: static addresses are known; live values are not established.
- Omitted callees and external effects: camera/lighting, per-frame update, orientation helper, renderer, and environment side effects are not covered by the 64/64 reference comparison.
- Probe trust: manifest hashes are reported but not compared to approved expected hashes; complete name-to-address validation is absent.
- Dynamic callers: only the bounded direct caller relationship is established statically.
- PKG-16: caller identity, metadata schema/lifecycle, resource selection, optional-ID representation, error mapping, and any online protocol remain unknown.

## PKG-16 — characterization only

PKG-16 is `CHARACTERIZED_ONLY / NOT_IMPLEMENTED`; `HOST_IMPLEMENTED`, `RUNTIME_VERIFIED`, and `ORIGINAL_COMPATIBLE` are not established. No PKG-16 host type, fixture, provider, runtime adapter, network client, or enabled online seam exists.

The authorized future boundary is a caller-owned local projection over caller-supplied data:

- preserve a complete, non-wildcard PKG-03 `ResourceKey` exactly;
- project `hasName` and the local name when present;
- project `isEditable` as metadata only, not mutation authority;
- preserve an optional asset identifier as absent, present, or malformed without fabricating a value;
- borrow caller-owned metadata/resource dependencies without ownership, retention beyond the call, mutation, event publication, property writes, global-service registration, or host/network-handle allocation;
- keep the resource/content dependency outside PKG-16: PKG-16 does not open packages, mount providers, select package priority, or resolve directories.

The hard no-network invariant prohibits DNS, hostname resolution, sockets, HTTP/WebSocket clients, service discovery, proxy use, credentials, remote authentication, retries, queueing, caching, or remote fallback. An optional online seam may exist only as explicitly disabled, non-operational API shape; enabling it is a different package requiring separate evidence, authorization, and threat review.

Future local outcomes must distinguish `invalid_resource_key`, `metadata_unavailable`, `malformed_metadata`, `unsupported_metadata`, `resource_unavailable`, and `internal_failure` without claiming those categories are original error semantics. Current evidence is documentation-only: the full Python/CTest validation is not a PKG-16 behavioral oracle. The checklist in `docs/analysis/future-research/pkg16-unknowns.md` remains unimplemented.

## Human approval and remaining gates

No original-process launch, debugger attachment, breakpoint placement, input, process-memory read/write, replacement installation, M0/M1/M2 execution, or status promotion was performed. Any future such action requires explicit human approval identifying the gate, binary and probe-manifest hashes, disposable run root, display/window target, bounded scope, stop condition, and human operator. A disposable byte-identical copy, fresh Wine/profile/save roots, machine-lock ownership, cleanup, and restoration evidence are mandatory.

Replacement promotion additionally requires a hash-pinned live trace, owner-qualified state and field meanings, paired ABI evidence, an original/replacement observable comparison, independent adjudication, and human status approval. The 64/64 decompilation-only comparison and green host tests do not satisfy that gate.

## Next work unblocked without overclaiming

- **PKG-09 Cell Presentation:** the PKG-07 host target/orientation/lifecycle contract is available for bounded host integration and presentation tests. This does not establish original placement, pixels, timing, or runtime movement. PKG-08/application caller integration remains open.
- **PKG-17 Cell Animation:** after PKG-09 supplies the presentation contract, it may consume a bounded host pose/target intent, but it is not directly unblocked by PKG-07 alone and gains no original animation or movement-order evidence.
- **Future local Sporepedia projection:** PKG-16’s characterization permits a separately authorized local fixture-driven implementation design. It does not unblock an online service, authenticate a caller, or establish a numbered downstream package; the only documented downstream is a future Sporepedia boundary.
- **Not unblocked:** M0/M1/M2, replacement promotion, original compatibility, and any online PKG-16 behavior remain gated.
