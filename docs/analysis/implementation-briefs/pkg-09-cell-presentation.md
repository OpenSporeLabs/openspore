# Implementation Brief — Cell GFX, HUD, scene assembly, and renderer boundary

Package: `PKG-09-CELL-PRESENTATION`  
Readiness: `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`  
Evidence: `SUPPORTED`

## Purpose

Compose CellGFX, HUD, scene entities, and renderer submission without claiming original pixels or placement.

## Authoritative semantic specification

["Authoritative: stable Cell/presentation associations, world/layer membership, preload readiness, display/HUD", "Runtime: cCellGFX, cCellUI, GFX/model/effect/texture handles, scene", "Persistent: none", "Invariant: presentation does not own gameplay/save state"]

## Source evidence

- docs/analysis/reconstruction-packages.md:704-777
- docs/analysis/render-engine-boundary.md:120-137
- knowledgegraph/research/render-boundary.json:574-727
- knowledgegraph/research/render-boundary/05-scene-entity.json
- knowledgegraph/research/render-boundary/07-resource-lifetime.json
- knowledgegraph/research/types/09-asset-content.json

## Relevant original functions and structures

- 0x00e54270 cCellUI::Load
- 0x00e55120 StartDisplay
- 0x00e5dba0 cCellGFX::Initialize
- 0x00e62340 ShowHealthRollover
- 0x00e663b0 PreloadCellResource
- 0x00e665c0 PreloadPopulateResource
- 0x00e666f0 PreloadResources
- CellGFXObjectData: cell/model/creature/effect links
- EntityPresentationRegistry: EntityId/PresentationHandle/rebuild/detach
- SceneEntity: ID/transform/model/material/visibility
- cCellGFX: worlds/layers/preloads/effects/display
- cCellUI/Rollover: vectors/constants/zoom/selection/0.5s timer

## Exact interfaces to implement

- ISceneStage.initialize/preload/display/stop/shutdown
- IEntityPresentationRegistry.attach/detach/rebuild
- IEntityView.set_transform/set_visibility
- IEffectPresenter.spawn/release
- IRenderQueue.submit(commands)

## Dependencies and prerequisites

- M0/M1
- PKG-03
- PKG-04
- PKG-05
- PKG-08
- matched render capture
- material/light/pixel oracle
- placement fixture

## Tests required

- asset_driven
- cellgfx/cellui/scene tests
- deterministic_unit
- fixture_comparison
- integration
- original_binary_oracle
- scene.json
- test_cellstage.py

## Acceptance criteria

- All required interface operations have explicit success, unsupported, and failure results.
- The listed invariants are covered by deterministic tests or explicit static tests.
- No original runtime behavior is claimed from host fixtures or decompilation alone.
- The package can integrate through the listed engine ports without importing raw original layouts.
- Unknowns and divergences remain visible in code/test documentation and the evidence register.

## Known limitations and unresolved assumptions

- GPU retirement
- HUD timing/drawing
- Material slots
- No original material/animation/pose execution
- Placement
- Pose upload
- Preload order/timeout
- Scene positions fixture choices
- Vulkan pixels/fixed lighting not original

## Validation boundary

Use STATIC_ONLY, DECOMP_DIFFERENTIAL, FIXTURE, INTEGRATION, or REPLACEMENT_HOOK only as specified. ORIGINAL_RUNTIME_ORACLE is required before an original-compatibility claim; a synthetic hook or generated fixture is not an original oracle.
