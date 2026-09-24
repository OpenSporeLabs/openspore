# Focused Research — Simulator shared-state roots and interface freeze

Package: `PKG-01-SHARED-STATE-ROOTS`  
Readiness: `BLOCKED_BY_ARCHITECTURE`  
Research class: `BLOCKED_BY_RE`

## Exact question

Are alternate and canonical noun/star slots the same owner, phase-specific owners, stale, or independent ports?

## Competing hypotheses

- shared singleton owner
- phase-specific owners
- stale or stale-transition owners
- independent owner ports

## Evidence currently available

- Caller-visible contract without fan-in ownership inference.
- Exact bodies and persisted contracts for unnamed high-fan-in roots.
- Returned global, receiver, field, and forwarded-state mechanics.

## Smallest useful investigation

Use the exact 11-root closure, direct writer scans, bounded computed/table xrefs, and one lifecycle trace; do not infer ownership from fan-in.

Inspect exactly: 0x00b3d300, 0x00b3d2a0, 0x00b5b800, 0x01021260, 0x00b1fdb0, 0x00b21340, 0x01021300, 0x01021080, 0x00b25fb0, 0x00ba9370.

## Expected observations

- Pinned bytes/decompilation/xrefs or raw runtime events with explicit environment and outcome.

## Decision criterion

Each root has a bounded contract and explicit unknowns; no SDK-name/fan-in promotion.

## Safety boundary

Retain opaque contracts; bounded negatives are non-exhaustive.
## Source records

- knowledgegraph/research/architecture-resolution.json
- docs/analysis/architecture-resolution.md
- docs/analysis/reconstruction-research-queue.md
- knowledgegraph/research/track-m-oracle-plan.json
- knowledgegraph/research/track-n-testability.json

