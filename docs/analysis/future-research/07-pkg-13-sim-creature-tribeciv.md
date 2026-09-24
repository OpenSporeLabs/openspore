# Focused Research — Creature, tribe, city, relationship, and civilization stage

Package: `PKG-13-SIM-CREATURE-TRIBECIV`  
Readiness: `BLOCKED_BY_RE`  
Research class: `BLOCKED_BY_RE`

## Exact question

What are the canonical creature, tribe, city, relationship, and civilization owners and transitions?

## Competing hypotheses

- receiver-typed creature state
- tribe/city state owner
- relationship/event owner
- name-only SDK family projection

## Evidence currently available

- Creature/tribe/city/civilization identities.
- Receiver-typed current-creature selection and noun ownership.
- Stage manager/event/transition candidates.

## Smallest useful investigation

Inspect 0x00b1fdb0, 0x00b1fd50, creature/city/tribe structures, noun roots, and persistence joins; do not merge with Cell pool or presentation.

Inspect exactly: 0x00b1fdb0, 0x00b1fd50, cCreatureBase/cCreatureGameData, cCity/cTribeArchetype, noun-root and persistence joins.

## Expected observations

- Pinned bytes/decompilation/xrefs or raw runtime events with explicit environment and outcome.

## Decision criterion

Package is no longer name-level only and has an independently supported boundary.

## Safety boundary

Keep Cell pool, presentation, high-LOD planet, and current-creature paths separate when unconnected.
## Source records

- knowledgegraph/research/architecture-resolution.json
- docs/analysis/architecture-resolution.md
- docs/analysis/reconstruction-research-queue.md
- knowledgegraph/research/track-m-oracle-plan.json
- knowledgegraph/research/track-n-testability.json

