# Focused Research — Editor and message dispatch

Package: `PKG-10-EDITOR-DISPATCH`  
Readiness: `BLOCKED_BY_RUNTIME`  
Research class: `BLOCKED_BY_RUNTIME`

## Exact question

Does a fixed UI action produce attributable message/editor/resource/frame ordering?

## Competing hypotheses

- correlated UI transition
- generic frame only
- resource-only activity
- unreachable menu

## Evidence currently available

- Message pump, editor callback, frame, resource, DBPF lock, and index order.
- Stable boot and logged fixed input.

## Smallest useful investigation

Run M5 after M0 with pinned window and pre-issuance input; correlate callbacks and DBPF/resource events, not screenshots.

Inspect exactly: pre-issuance input and pinned window, timestamped callback/event order, UI/resource causality versus frame activity.

## Expected observations

- Pinned bytes/decompilation/xrefs or raw runtime events with explicit environment and outcome.

## Decision criterion

UI action correlates with dispatch/resource order without screenshot inference.

## Safety boundary

Frame or visible response without correlated callbacks remains negative.
## Source records

- knowledgegraph/research/architecture-resolution.json
- docs/analysis/architecture-resolution.md
- docs/analysis/reconstruction-research-queue.md
- knowledgegraph/research/track-m-oracle-plan.json
- knowledgegraph/research/track-n-testability.json

