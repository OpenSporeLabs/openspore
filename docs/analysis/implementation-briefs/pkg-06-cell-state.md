# Implementation Brief — Cell game state, pool, query, advect, and combat rules

Package: `PKG-06-CELL-STATE`  
Readiness: `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`  
Evidence: `SUPPORTED`

## Purpose

Reconstruct selected pure Cell state/pool/query/advect/combat rules without claiming the complete live machine.

## Authoritative semantic specification

["Authoritative: static cCellGame/pool/object/query/combat transitions", "Runtime: cCellGame, pool, object, query, avatar, health, behavior", "Persistent: cCellSerializableData separate candidate", "Invariant: pure rules/CellSim are not original singleton runtime"]

## Source evidence

- docs/analysis/class-family-map.md:546-577
- docs/analysis/gameplay-state-machines.md:156-210
- docs/analysis/reconstruction-packages.md:488-560
- knowledgegraph/research/global-campaign-2026/track-d-sim-cell.json:227-337
- knowledgegraph/research/types/02-gameplay-entity.json

## Relevant original functions and structures

- 0x00e74a20 CreateCellObject
- 0x00e780a0 pool lifecycle/rebuild
- 0x00e80ba0 cCellGame::Initialize
- CellPool allocate/release
- CellQuery::queryNear
- getCurrentAdvectInfo/getNextAdvectID
- getScaleDifference/getDamage/shouldNotAttack
- cAdvectEntry/ScaleDifference: bucket/strength/variance/period/ID
- cCellGame: pool +0x1c, queries +0x40fc/+0x4100, world +0x4114/+0x4118, avatar +0x411c, serializable +0x5190, lock +0x5158, update +0x515c, state +0x51e0
- cCellObjectData: 920 bytes, pool link, target/orientation/transform, model/resource, animation, health/GFX/scale/query
- cCellQueryEntry: position/size/next/index
- cObjectPool: 4096 capacity, 920 stride

## Exact interfaces to implement

- ICellGameState.initialize(config) / tick(delta) / reset()
- IEntityPool.allocate/release/lookup
- ICellQuery.query_near(predicate)
- IAdvectState.current/next
- ICombatRules.damage/eat/flee
- IAnimationIntent.request(clip)

## Dependencies and prerequisites

- PKG-01
- PKG-05
- PKG-08
- SDK layouts
- non-original fixture label
- pool identity/exhaustion validation
- pre/post state
- root resolution

## Tests required

- decomp_differential
- deterministic_unit
- fixture_comparison
- generated fixtures labeled non-original
- original_binary_oracle
- sim tests

## Acceptance criteria

- All required interface operations have explicit success, unsupported, and failure results.
- The listed invariants are covered by deterministic tests or explicit static tests.
- No original runtime behavior is claimed from host fixtures or decompilation alone.
- The package can integrate through the listed engine ports without importing raw original layouts.
- Unknowns and divergences remain visible in code/test documentation and the evidence register.

## Known limitations and unresolved assumptions

- AI/effect/query integration
- CellSim not original cCellGame
- Complete pool effects
- Entity not byte-compatible
- Free-list sentinel
- Live-object save
- No original timing claim
- Runtime gates

## Validation boundary

Use STATIC_ONLY, DECOMP_DIFFERENTIAL, FIXTURE, INTEGRATION, or REPLACEMENT_HOOK only as specified. ORIGINAL_RUNTIME_ORACLE is required before an original-compatibility claim; a synthetic hook or generated fixture is not an original oracle.
