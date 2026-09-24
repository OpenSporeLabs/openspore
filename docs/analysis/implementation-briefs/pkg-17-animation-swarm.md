# Implementation Brief — Cell animation and Swarm/creature animation boundary

Package: `PKG-17-ANIMATION-SWARM`  
Readiness: `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`  
Evidence: `INFERRED`

## Purpose

Separate gameplay-owned Cell animation intent from pose evaluation, Swarm effects, and unresolved animation implementation.

## Authoritative semantic specification

["Authoritative: Cell clip/blend state when direct", "Runtime: cCellObjectData animation, manager/world, pose/effect instances", "Persistent: none established", "Invariant: intent gameplay; skeleton/pose/particles backend"]

## Source evidence

- docs/analysis/reconstruction-packages.md:1214-1278
- docs/analysis/render-engine-boundary.md:198-219
- knowledgegraph/research/global-campaign-2026/track-g-editor-ui-input.json:349-393
- knowledgegraph/research/render-boundary.json:35-80
- knowledgegraph/research/render-boundary/04-animation-pose.json
- knowledgegraph/research/types/03-creature.json

## Relevant original functions and structures

- 0x00e63560 LoadEffectMap
- 0x00e66840 InstanceEffectOnCell
- 0x00e6d200 PlayAnimation
- CellAnim host mapping only
- Swarm functions unresolved
- IAnimationController: current/target clip/blend/loop/time/phase
- IEffectPresenter: definition/instance/transform/lifecycle
- Swarm animation/effect state unresolved
- cCellAnimDefinition name-level
- cCellObjectData: current animation +0x1b0, blend +0x1b4/+0x1b8, GFX +0x248

## Exact interfaces to implement

- IAnimationController.request(clip, blend, loop, time_scale)
- IAnimationWorld.tick(delta) / current_and_target
- IPoseEvaluator.evaluate(PoseSnapshot)
- IEffectPresenter.bind(entity, effect) / unbind

## Dependencies and prerequisites

- PKG-05
- PKG-09
- Swarm identity
- event source
- event-to-animation trace
- event-to-pose trace
- pose policy
- render/material boundary

## Tests required

- cellanim_test
- decomp_differential
- deterministic_unit
- effectmap_test
- event-to-pose/Swarm gates
- integration
- original_binary_oracle

## Acceptance criteria

- All required interface operations have explicit success, unsupported, and failure results.
- The listed invariants are covered by deterministic tests or explicit static tests.
- No original runtime behavior is claimed from host fixtures or decompilation alone.
- The package can integrate through the listed engine ports without importing raw original layouts.
- Unknowns and divergences remain visible in code/test documentation and the evidence register.

## Known limitations and unresolved assumptions

- Blend completion
- CellAnim not wired to cell_stage
- Event producer
- No skeleton/pose upload
- Pose order
- Swarm ownership
- Swarm unresolved
- Vehicle coupling

## Validation boundary

Use STATIC_ONLY, DECOMP_DIFFERENTIAL, FIXTURE, INTEGRATION, or REPLACEMENT_HOOK only as specified. ORIGINAL_RUNTIME_ORACLE is required before an original-compatibility claim; a synthetic hook or generated fixture is not an original oracle.
