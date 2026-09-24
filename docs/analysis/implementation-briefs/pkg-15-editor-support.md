# Implementation Brief — Palettes, Skinner, and editor support assets

Package: `PKG-15-EDITOR-SUPPORT`  
Readiness: `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`  
Evidence: `INFERRED`

## Purpose

Characterize palette/viewer/texture-paint support without merging into editor command or gameplay semantics.

## Authoritative semantic specification

["Authoritative: direct palette/viewer/support state only", "Runtime: pages/categories/viewer/painter/model handles", "Persistent: authored resources separate", "Invariant: support operations need producer/consumer path"]

## Source evidence

- docs/analysis/class-family-map.md:597-611
- docs/analysis/reconstruction-packages.md:1090-1150
- docs/analysis/render-engine-boundary.md:120-137
- knowledgegraph/research/types/06-editor-ui.json
- knowledgegraph/research/types/09-asset-content.json
- knowledgegraph/triage/queue-f0e310e0-v6.json

## Relevant original functions and structures

- 0x004ae250 EditorModel::SetColor
- 0x005c8bc0 PalettePage::Load
- 0x005f4750 AdvancedItemViewer::func40h
- cSkinnerTexturePainter PaintRegion/StartRender/EndRender
- AdvancedItemViewer: vtable/item/page/category/draw
- EditorModel: ResourceKey/rigblocks/names/colors/bounds
- PalettePage: identity/load/category
- cSkinnerTexturePainter: paint/start/end

## Exact interfaces to implement

- IEditorSupportAssets.load(ResourceKey)
- IPaletteCatalog.query(filter)
- IViewerModel.open/close
- IEditorSupportWriter.save(model) with explicit unsupported boundary

## Dependencies and prerequisites

- PKG-03
- PKG-04
- PKG-10
- editor/graphics dependencies
- renderer/editor boundary
- support VAs/vtables

## Tests required

- AdvancedItemViewer evidence
- Palette/EditorModel queue rows
- decomp_differential
- deterministic_unit
- fixture_comparison
- not_yet_testable

## Acceptance criteria

- All required interface operations have explicit success, unsupported, and failure results.
- The listed invariants are covered by deterministic tests or explicit static tests.
- No original runtime behavior is claimed from host fixtures or decompilation alone.
- The package can integrate through the listed engine ports without importing raw original layouts.
- Unknowns and divergences remain visible in code/test documentation and the evidence register.

## Known limitations and unresolved assumptions

- Categories
- Names do not prove command ownership
- No original palette/viewer/paint implementation
- Paint state
- Runtime order
- Viewer lifecycle

## Validation boundary

Use STATIC_ONLY, DECOMP_DIFFERENTIAL, FIXTURE, INTEGRATION, or REPLACEMENT_HOOK only as specified. ORIGINAL_RUNTIME_ORACLE is required before an original-compatibility claim; a synthetic hook or generated fixture is not an original oracle.
