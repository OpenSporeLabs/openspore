# Focused Research — Unknown routing and ownership backlog

Package: `PKG-21-UNKNOWN-ROUTING`  
Readiness: `BLOCKED_BY_RE`  
Research class: `BLOCKED_BY_RE`

## Exact question

Which bounded unknown/vtable cohort can be admitted to a semantic package without speculation?

## Competing hypotheses

- constructor/vtable owner
- SDK/static family owner
- unknown routing only
- infrastructure wrapper

## Evidence currently available

- Bounded UNKNOWN-HIGH/vtable adjudication cohort.
- Dependency order and runtime reachability.
- Unique constructor, vtable owner, and package evidence per admitted row.

## Smallest useful investigation

Inspect debtmap/triage-v6, candidate vtable installation/destructor resets, direct callers/callees, and SDK associations; admit/reject/defer row by row.

Inspect exactly: debtmap, triage-v6, vtable installation/destructor resets, direct callers/callees and SDK associations.

## Expected observations

- Pinned bytes/decompilation/xrefs or raw runtime events with explicit environment and outcome.

## Decision criterion

No row enters implementation solely from fan-in, proximity, FUN_* naming, or scanner grouping.

## Safety boundary

Keep rows unknown and outside implementation/promotion.
## Source records

- knowledgegraph/research/architecture-resolution.json
- docs/analysis/architecture-resolution.md
- docs/analysis/reconstruction-research-queue.md
- knowledgegraph/research/track-m-oracle-plan.json
- knowledgegraph/research/track-n-testability.json

