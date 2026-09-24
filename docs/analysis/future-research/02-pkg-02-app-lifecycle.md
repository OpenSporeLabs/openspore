# Focused Research — Application bootstrap and system lifecycle

Package: `PKG-02-APP-LIFECYCLE`  
Readiness: `BLOCKED_BY_RUNTIME`  
Research class: `BLOCKED_BY_RUNTIME`

## Exact question

Does the current approved runtime produce a reproducible positive boot and ordered App lifecycle?

## Competing hypotheses

- positive boot
- clean stop
- stall/failed boot
- renderer failure

## Evidence currently available

- Current executable/tracer identity.
- Fresh-generation boot, module discovery, startup sequence, renderer marker, and exact outcome.

## Smallest useful investigation

Run only the approved M0 control with pinned binary/probe/environment identity; record raw JSONL, event count, and exact negative reason.

Inspect exactly: binary/probe hashes, Wine/display/xdotool/window/lock identity, raw JSONL and exact event count.

## Expected observations

- Pinned bytes/decompilation/xrefs or raw runtime events with explicit environment and outcome.

## Decision criterion

Entry, InitPlugins, Init, Startup, and IAppSystem::Get order is reproducibly observed.

## Safety boundary

Zero events, clean exit, renderer failure, and stall remain distinct negatives.
## Source records

- knowledgegraph/research/architecture-resolution.json
- docs/analysis/architecture-resolution.md
- docs/analysis/reconstruction-research-queue.md
- knowledgegraph/research/track-m-oracle-plan.json
- knowledgegraph/research/track-n-testability.json

