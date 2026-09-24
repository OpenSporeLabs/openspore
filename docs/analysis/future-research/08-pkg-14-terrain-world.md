# Focused Research — Terrain, planet surface, and world rendering

Package: `PKG-14-TERRAIN-WORLD`  
Readiness: `BLOCKED_BY_RE`  
Research class: `BLOCKED_BY_RE`

## Exact question

What is the planet-surface/terrain draw boundary and where does gameplay state end?

## Competing hypotheses

- terrain state owner
- presentation-only terrain
- Space-to-surface handoff
- raw vtable ABI projection

## Evidence currently available

- Gameplay state versus rendering handle separation.
- Planet-to-terrain transition.
- Terrain draw/update identities and vtable ownership.

## Smallest useful investigation

Inspect cTerrainSphere render trio, Quad::Draw, cPlanetModel, and Space-to-surface callers; separate state from draw handles.

Inspect exactly: cTerrainSphere render trio, Quad::Draw, cPlanetModel, Space-to-surface callers.

## Expected observations

- Pinned bytes/decompilation/xrefs or raw runtime events with explicit environment and outcome.

## Decision criterion

Concrete terrain/world surface and draw boundary without name-based gameplay promotion.

## Safety boundary

Unresolved vtable dimensions and draw functions stay deferred.
## Source records

- knowledgegraph/research/architecture-resolution.json
- docs/analysis/architecture-resolution.md
- docs/analysis/reconstruction-research-queue.md
- knowledgegraph/research/track-m-oracle-plan.json
- knowledgegraph/research/track-n-testability.json

