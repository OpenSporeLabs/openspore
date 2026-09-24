# Focused Research — UTFWin and scripting/configuration infrastructure

Package: `PKG-18-UI-SCRIPTING`  
Readiness: `BLOCKED_BY_RUNTIME`  
Research class: `BLOCKED_BY_RUNTIME`

## Exact question

Which immediate/deferred/UI message families are actually observed in a reachable transition?

## Competing hypotheses

- reachable UTFWin/message transition
- generic frames only
- resource-only activity
- unreachable UI

## Evidence currently available

- Boot and reachable UTFWin/message boundary.
- Immediate versus deferred message-family behavior.
- Input/message/resource/stage order.

## Smallest useful investigation

Run M5 after M0, record family-specific registration/delivery/payload observations, and keep queue timing separate from gameplay state.

Inspect exactly: registration/delivery records, queue/frame annotation separate from gameplay, no universal event ABI claim.

## Expected observations

- Pinned bytes/decompilation/xrefs or raw runtime events with explicit environment and outcome.

## Decision criterion

Selected UI/script transition has evidence-backed order or remains UNKNOWN.

## Safety boundary

No positive menu transition leaves boundary frozen and BLOCKED_BY_RUNTIME.
## Source records

- knowledgegraph/research/architecture-resolution.json
- docs/analysis/architecture-resolution.md
- docs/analysis/reconstruction-research-queue.md
- knowledgegraph/research/track-m-oracle-plan.json
- knowledgegraph/research/track-n-testability.json

