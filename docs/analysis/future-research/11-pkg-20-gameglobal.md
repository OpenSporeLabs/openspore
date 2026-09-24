# Focused Research — GameGlobal map and miscellaneous state

Package: `PKG-20-GAMEGLOBAL`  
Readiness: `BLOCKED_BY_RE`  
Research class: `BLOCKED_BY_RE`

## Exact question

What is the exact map helper contract for 0x00e5c780?

## Competing hypotheses

- lower-bound/successor map
- exact-find map
- opaque map bridge
- different owner or value type

## Evidence currently available

- Body and exact map contract for 0x00e5c780.
- Caller postconditions and invalidation.
- Container, key, value, owner, ordering, and mutation rules.

## Smallest useful investigation

Inspect direct/computed writers and consumers 0x00b21340, 0x00ba9370, 0x01021300; return a typed adapter proposal or smallest opaque contract.

Inspect exactly: 0x00e5c780, 0x00b21340, 0x00ba9370, 0x01021300, computed writers.

## Expected observations

- Pinned bytes/decompilation/xrefs or raw runtime events with explicit environment and outcome.

## Decision criterion

Map contract is mechanics/caller supported, not name-only.

## Safety boundary

Expose smallest opaque contract and remain BLOCKED_BY_RE if owner is unknown.
## Source records

- knowledgegraph/research/architecture-resolution.json
- docs/analysis/architecture-resolution.md
- docs/analysis/reconstruction-research-queue.md
- knowledgegraph/research/track-m-oracle-plan.json
- knowledgegraph/research/track-n-testability.json

