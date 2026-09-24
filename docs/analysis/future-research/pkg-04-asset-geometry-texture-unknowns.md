# PKG-04 Asset Geometry Texture Unknowns

Package: `PKG-04-ASSET-GEOMETRY-TEXTURE`  
Status: `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`  
Scope: bounded model, mesh, material, RW4, raster, and host texture contracts.

## Implemented contract

- `ModelStore` consumes `IContentStore` with complete `ResourceKey` values. It accepts GMDL and RW4 type IDs only, returns owned `ModelRecord` values, and maps source, version, format, material, key, and provider failures to explicit `ModelLoadCode` results.
- GMDL v8 static geometry is decoded through the existing `parseGmdl` and `meshFromGmdl` seams. `ModelRecord::animation` records an opaque trailer and `loadAnimation` returns `unsupported_animation`.
- RW4 records receive the existing structural walk only. Their section manifest is retained; RenderWare payload execution and model/material construction are not performed.
- `IMeshSource` keeps its existing indexed provider seam and gains a non-breaking `build(ModelRecord, ...)` path. `ModelStoreMeshSource` adapts a model key to a host mesh. A non-GMDL record fails with an explicit unsupported message.
- `MaterialRegistry` resolves only caller-registered `MaterialDefinition` values. Unregistered IDs and incomplete texture keys fail explicitly; no default material or RenderWare material is synthesized. `materialSlotsFromGmdl` preserves ordered GMDL material IDs without inventing texture-slot association.
- `TextureStore` reads raster type `0x2F4E681C`, delegates to the existing DXT5/raster decoder, validates decoded mips, and uploads mip zero through the existing `IRenderer::createTexture` host contract. `release` delegates handle destruction to the renderer. Mip count is retained, but no sampler or mip-selection policy is invented.
- No source mutation, writer, cache, original RenderWare object adoption, or original renderer backend behavior is added.

## Evidence classes

### BLUEPRINT_BACKED

- The package requires `IModelStore::load(ResourceKey)`, `IMeshSource` model-to-mesh adaptation, `IMaterialRegistry::resolve(material slots)`, and `ITextureStore::upload(ImageRecord)`.
- Stable complete type/group/instance identity is supplied by PKG-03 `ResourceKey` and `IContentStore`.
- GMDL v8 bounds, index buffers, vertex buffers, material IDs, texture-set references, and static mesh topology are the bounded decoded fields.
- RW4 is a section/container walk; section presence is not permission to execute RenderWare payloads.
- Raster/DXT5 decoding produces row-major RGBA8 `ImageRGBA` mips and the renderer host already accepts a single `ImageRGBA` texture upload.
- Host mesh, texture, and material values are not original RenderWare/material/pixel behavior.

### EXISTING_OPENSPORE_BEHAVIOR

- `parseGmdl`, `meshFromGmdl`, `parseRw4`, `decodeRasterMips`, and `decodeDxt5Mip` are reused rather than replaced.
- `IContentStore::read` is the package boundary; the B1 provider adapter remains read-only and its unsupported locator behavior is not changed.
- The existing `IMeshSource::loadMesh` and `GmdlMeshSource` behavior remains available. The added `build` overload only adapts the new `ModelRecord` value.
- The existing `IRenderer::createTexture` accepts one image and has no sampler or mip-chain upload operation.
- The host `MaterialState` type is the current renderer material input; it is not a recovered original shader definition.

### BOUNDED_INFERENCE

- GMDL and RW4 are routed by the established type IDs `0x00E6BCE5` and `0x2F4E681B`; all other types return `unsupported_type` at this package boundary.
- A successfully parsed GMDL v8 record is marked `opaque_trailer` for animation because the parser validates the static prefix but does not execute or interpret its animation/trailer semantics.
- A successfully parsed RW4 record with no recognized animation section is marked `none`; one with a recognized animation-related section is marked `unsupported`. This does not interpret any section payload.
- Material IDs are treated as stable host lookup tokens. A caller must register the material definition; missing definitions are unsupported rather than replaced by a guessed material.
- GMDL texture references remain raw `GmdlTextureRef` values. No association is invented between their order and individual material slots.
- `TextureStore` uploads mip zero because the existing renderer host has a single-image upload operation. The complete decoded mip vector remains in `ImageRecord` for later integration.
- Decode failures do not publish partial records. Material resolution is all-or-nothing for the requested slot vector.
- `TextureStore::release` is an explicit handle operation. It does not infer a shared cache, reference count, eviction policy, or GPU retirement order.
- The result enums and host structs are clean-room package contracts derived from the required success/unsupported/failure distinction; they do not reproduce an original ABI.

### PROVISIONAL

- The exact API spelling and payload layout of `ModelRecord`, `ImageRecord`, `MaterialDefinition`, and their result structs are host integration decisions until the renderer/presentation package consumes them.
- `MaterialDefinition::state` is a host-side renderer approximation. The package does not establish a mapping from the recovered material ID to the original RenderWare shader or compiled state.
- The mapping from `GmdlTextureRef` to material slots remains unresolved and is intentionally left empty by `materialSlotsFromGmdl`.
- Raster envelope fields `field10`, `field18`, and `field1c` remain ignored because the existing decoder does not have evidence for their semantics.
- DXT5 is the only supported raster FourCC. Other FourCC values, including source image types, remain unsupported.
- The renderer receives mip zero without a sampler, LOD selection, anisotropic setting, or original mip-generation policy.
- Host texture pixels and host lighting are not an original-pixel or original-renderer oracle.

## Intentional deviations and non-claims

- GMDL v9 and future GMDL versions are explicit unsupported results.
- Unknown GMDL shader/material information is not guessed or silently skipped; the package maps the parser's material/shader diagnostic to `unsupported_material`.
- GMDL animation, baked-deform, skeleton, pose, and blend-shape behavior is not executed. Static geometry remains usable where the existing mesh conversion succeeds.
- RW4 material, compiled-state, animation, skeleton, skin, blend-shape, and other payload semantics are not reconstructed. RW4 load success means structural validation only.
- A RW4 record cannot be built into a host mesh through `IMeshSource`; the adapter returns an explicit unsupported result.
- Non-DXT5 raster records and renderer upload rejection return typed failure results.
- No material default, RenderWare object import, compiled shader, sampler policy, async load, multi-package priority, cache eviction, or original resource-manager behavior is added.
- The renderer backend is not expanded. Presentation concerns remain outside this package.
- No original-runtime equivalence, original pixel fidelity, original material behavior, or original animation behavior is claimed.

## Bounded unknowns

| Unknown | Affected code | Current bounded behavior | Blast radius | Future evidence required |
|---|---|---|---|---|
| GMDL v9 and later layout | `ModelStore::load`, `Gmdl.cpp` | `unsupported_version`; no partial record | Any future model key routed to a new GMDL version | Recovered v9 field layout and fixture/differential coverage |
| GMDL trailer and animation semantics | `ModelRecord::animation`, `ModelStore::loadAnimation`, `MeshSource` | Static prefix can build; animation reports unsupported | Model animation, skinning, pose, blend shape, and presentation timing | Direct trailer/evaluator evidence and controlled model fixtures |
| RW4 material/compiled-state payload | `ModelStore::load`, `ModelRecord::rw4` | Container sections validate; payload remains opaque | Model material binding, shader state, texture slot interpretation | Direct RW4 section semantics and material fixture differential |
| RW4 animation sections | `ModelRecord::animation`, `MeshSource` | Recognized animation sections are marked unsupported; no build | Animation and skinned mesh presentation | Section payload/evaluator evidence and runtime trace |
| Raster fields `0x10`, `0x18`, `0x1c` | `ImageRecord::envelope`, `TextureStore::load` | Retained but not interpreted | Sampler, mip policy, raster metadata interpretation | Field-level raster evidence or independent decoder contract |
| Material-slot association | `MaterialRegistry`, `materialSlotsFromGmdl` | IDs remain ordered; texture associations are empty | Texture binding and per-draw material state | GMDL material-info/slot evidence plus fixture comparison |
| Material definition and shader state | `MaterialDefinition`, `MaterialRegistry` | Registered host definitions only; missing IDs unsupported | Lit appearance and any future material cache | Original material definition and per-draw state evidence |
| Mip and sampler policy | `TextureStore::upload`, renderer host | Mip zero uploaded; mip vector retained; no sampler selection | Texture filtering, LOD, anisotropic behavior, backend upload path | Renderer-host mip API and original sampling/runtime evidence |
| Texture pixel fidelity | `Dxt5`, `ImageRGBA`, `TextureStore` | Existing DXT5 oracle output is preserved; no new claim | Any pixel comparison or presentation substitution | Original texture capture plus controlled runtime/pixel oracle |
| Handle ownership and retirement | `TextureStore::release` | Explicit renderer destroy operation, no cache policy | Cache hits, shared texture lifetime, GPU retirement | Original resource/cache lifecycle evidence and renderer host contract |
| Original resource-manager integration | `ModelStore`, `TextureStore` | Synchronous one-store reads through `IContentStore` | Priority, async, cache, multi-package, reload behavior | Original manager trace and package-provider policy evidence |

## Validation performed

- Aggregate CMake build completed successfully.
- `ctest --test-dir /tmp/opencode/openspore-build --output-on-failure -R '^(assets_pkg04|assets_synthetic|assets_real|assets_cellgmdl|assets_worldobj|assets_rw4)$'`
- Python format/texture differential tests passed.
- `git diff --check`: pass.
- No original-runtime oracle was used.
