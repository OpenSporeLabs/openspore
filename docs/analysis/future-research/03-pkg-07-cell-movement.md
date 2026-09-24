# Focused Research — Cell movement and mouse-steering replacement

Package: `PKG-07-CELL-MOVEMENT`  
Readiness: `BLOCKED_BY_RUNTIME`  
Research class: `BLOCKED_BY_RUNTIME`

## Exact question

Does the original movement function have the expected ABI, guards, side effects, and input causality?

## Competing hypotheses

- reachable original movement
- unreachable target
- different target/ABI
- replacement-only stand-in

## Evidence currently available

- Mouse waypoint causality.
- Plane point, lock, camera/UI gates, omitted callees, and movement stores.
- Pool index versus entity identity.
- Positive boot and Cell reachability.
- Read-only entry/return and pre/post scalar/vector observations.

## Smallest useful investigation

Run M1/M2/M3 only after M0; record linked VA, stack/return, pre/post state, pool identity, camera/input order, and no writes beyond approved observations.

Inspect exactly: target bytes, linked VA/RVA, ABI frame and return path, hash-pinned trace, caller/thread/input/pre-post table, no memory writes or proprietary dumps.

## Expected observations

- Pinned bytes/decompilation/xrefs or raw runtime events with explicit environment and outcome.

## Decision criterion

Attributable original observation supports observable comparison.

## Safety boundary

Entry-only or unreachable results remain replaced-approx and BLOCKED_BY_RUNTIME.
## Source records

- knowledgegraph/research/architecture-resolution.json
- docs/analysis/architecture-resolution.md
- docs/analysis/reconstruction-research-queue.md
- knowledgegraph/research/track-m-oracle-plan.json
- knowledgegraph/research/track-n-testability.json

