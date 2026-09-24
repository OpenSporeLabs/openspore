# Focused Research — Simulator core services, tools, and missions

Package: `PKG-11-SIM-CORE`  
Readiness: `BLOCKED_BY_RE`  
Research class: `BLOCKED_BY_RE`

## Exact question

Which manager, tool, mission, and pool functions are semantic gameplay boundaries rather than wrappers?

## Competing hypotheses

- manager-owned gameplay services
- tool strategy gameplay
- mission gameplay
- runtime/wrapper infrastructure

## Evidence currently available

- Exact unresolved callees of named tool functions.
- Gameplay versus wrapper/infrastructure classification.
- Manager/tool/mission/object-pool ownership.

## Smallest useful investigation

Inspect the named tool anchors, cObjectPool_::DeleteObject, IsNotStarOrBinaryStar, and their unresolved callees; produce a leaf-to-orchestrator map.

Inspect exactly: cToolStrategy, cDefaultAoETool/cDefaultBeamTool, cObjectPool_::DeleteObject, IsNotStarOrBinaryStar, manager/vtable queue rows.

## Expected observations

- Pinned bytes/decompilation/xrefs or raw runtime events with explicit environment and outcome.

## Decision criterion

Explicit callee/ownership contracts without merging tool, mission, and manager semantics.

## Safety boundary

Keep unresolved callees BLOCKED_BY_RE or STATIC_ONLY.
## Source records

- knowledgegraph/research/architecture-resolution.json
- docs/analysis/architecture-resolution.md
- docs/analysis/reconstruction-research-queue.md
- knowledgegraph/research/track-m-oracle-plan.json
- knowledgegraph/research/track-n-testability.json

