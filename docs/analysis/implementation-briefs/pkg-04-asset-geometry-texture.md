# Implementation Brief — GMDL/RW4/raster geometry and texture decode

Package: `PKG-04-ASSET-GEOMETRY-TEXTURE`  
Readiness: `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`  
Evidence: `SUPPORTED`

## Purpose

Decode bounded static geometry/model/texture/container formats into host values.

## Authoritative semantic specification

["Authoritative: supported decoded fields/topology/mips", "Runtime: host mesh/texture handles", "Persistent: source records only", "Invariant: host output is not original RW/material/pixel behavior"]

## Source evidence

- docs/analysis/reconstruction-packages.md:338-407
- docs/analysis/render-engine-boundary.md:54-96
- knowledgegraph/research/render-boundary/01-renderware-objects.json
- knowledgegraph/research/render-boundary/02-material-textures.json
- knowledgegraph/research/render-boundary/06-d3d-platform.json
- knowledgegraph/research/types/09-asset-content.json

## Relevant original functions and structures

- decodeRasterMips/decodeDxt5Mip
- parseGmdl/meshFromGmdl
- parseRw4 structural walk without payload execution
- GmdlModel: version/bounds/topology/material refs
- ImageRGBA: mip dimensions/RGBA8/provenance
- Mesh: vertices/indices/bounds/limitations
- RW4 manifest: sections/offsets/validation

## Exact interfaces to implement

- IModelStore.load(ResourceKey) -> ModelRecord
- IMeshSource.build(ModelRecord) -> Mesh
- IMaterialRegistry.resolve(material slots)
- ITextureStore.upload(ImageRecord) -> TextureHandle

## Dependencies and prerequisites

- B2/B3 consumers
- PKG-03
- Package records
- Python oracles
- full differential
- malformed fixtures
- unsupported versions explicit

## Tests required

- asset_driven
- decomp_differential
- deterministic_unit
- fixture_comparison
- integration
- mini.gmdl
- mini_rw4.rw4
- test_formats.py
- test_rw4.py
- test_textures.py

## Acceptance criteria

- All required interface operations have explicit success, unsupported, and failure results.
- The listed invariants are covered by deterministic tests or explicit static tests.
- No original runtime behavior is claimed from host fixtures or decompilation alone.
- The package can integrate through the listed engine ports without importing raw original layouts.
- Unknowns and divergences remain visible in code/test documentation and the evidence register.

## Known limitations and unresolved assumptions

- GMDL v8 narrower than format family
- GMDL v9
- Host mesh/texture is not full RenderWare
- Mip/sampler
- Pixel fidelity
- RW4 material/animation
- Raster words 0x10/0x18
- Vulkan pixels not original

## Validation boundary

Use STATIC_ONLY, DECOMP_DIFFERENTIAL, FIXTURE, INTEGRATION, or REPLACEMENT_HOOK only as specified. ORIGINAL_RUNTIME_ORACLE is required before an original-compatibility claim; a synthetic hook or generated fixture is not an original oracle.
