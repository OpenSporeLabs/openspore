# Focused Research — Simulator Space stage, stars, planets, trade, and terraforming

Package: `PKG-12-SIM-SPACE`  
Readiness: `BLOCKED_BY_ARCHITECTURE`  
Research class: `BLOCKED_BY_RE`

## Exact question

What is the Space stage entry/state-owner graph and how do star lookup, cache, trade, and surface handoff interact?

## Competing hypotheses

- single Space session
- phase-specific sessions
- separate Space and terrain owners
- name-only stage projection

## Evidence currently available

- Lookup/cache consumer postconditions.
- Space entry/state-owner VAs and vtables.
- Star/trading service contracts under separate root ports.

## Smallest useful investigation

Inspect 0x00e5c780, 0x00ba9370, 0x01021300, cStarManager/cSpaceTrading families, and Space/Terrain joins; preserve lower-bound semantics.

Inspect exactly: 0x00e5c780, 0x00ba9370, 0x01021300, cStarManager, cSpaceTrading, Space/Terrain joins.

## Expected observations

- Pinned bytes/decompilation/xrefs or raw runtime events with explicit environment and outcome.

## Decision criterion

Entry, ownership, and bounded lookup/cache contracts are separated from runtime truth.

## Safety boundary

No exact-find, exact-cache, invalidation, or root-equality claim.
## Source records

- knowledgegraph/research/architecture-resolution.json
- docs/analysis/architecture-resolution.md
- docs/analysis/reconstruction-research-queue.md
- knowledgegraph/research/track-m-oracle-plan.json
- knowledgegraph/research/track-n-testability.json

