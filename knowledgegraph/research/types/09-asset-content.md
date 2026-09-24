# 09 — Asset and content types archaeology

## Scope and evidence policy

This partition is a read-only reconstruction study of the resource and content path in `SporeApp.exe` 3.1.0.22. It covers package records, graphics containers, models, textures, cell content, effect and material data, audio handles, planet/terrain objects, properties, descriptors, handles, nested reference graphs, vtable associations, lifecycle anchors, consumers, and reconstruction relevance. It does not implement code, modify `SPORE/`, change Ghidra, write the knowledge graph, or promote static evidence to original runtime behavior.

The evidence scale is `UNKNOWN < APPROXIMATION < INFERRED < SUPPORTED < OBSERVED < CONFIRMED < VERIFIED`. Current OpenSpore observations establish current behavior only. SDK names, Ghidra structures, vtable candidates, xrefs, decompilation, real-record decoders, and tests are bounded evidence. A named class or function is retained only with a binary VA, binary structure association, pinned type/section identity, or an explicit unresolved alias. SporeApp.exe has no MSVC RTTI, so no class hierarchy is inferred from names alone.

The machine-readable record is [`09-asset-content.json`](09-asset-content.json). It contains the full type table, layouts, descriptor contracts, handle records, vtable associations, lifecycle phases, consumer graph, serialization boundaries, contradictions, open questions, and source provenance.

## Partition result

The content boundary is centered on the numeric `ResourceKey` triple `(instance, type, group)`. DBPF v3 stores the same identity as `(type, group, instance)` in index rows. The identity is the stable gameplay-facing contract; package paths, QFS, factories, caches, and the original manager's container objects are replaceable infrastructure.

| Area | Recovered contract | Evidence |
|---|---|---|
| Package | DBPF v3 96-byte header, index rows, stored/memory extents, QFS flag and decompressed-size check | `VERIFIED`, real records and independent decoder |
| Graphics container | RW4 header, manifest, SectionTypes table, 24-byte SectionInfo records, data arena, BaseResource relative addressing | `SUPPORTED` to `VERIFIED` for structure |
| Model | GMDL v8 referenced-file keys, bounds, index/vertex buffers, descriptors, meshes, material IDs, texture-set refs, trailer | `VERIFIED` for bounded v8 prefix |
| Texture | 32-byte raster envelope, DXT5 mip chain, layer headers, Graphics::Texture handle and flags | `VERIFIED` for DXT5; envelope words unresolved |
| Image sources | `jpeg`, `png`, `bmp`, `tga`, `gif`, `dds` type IDs and provider-level image inputs | `SUPPORTED` type vocabulary; full current decode path unresolved |
| Cell content | globals, cell, world, populate, effectMap, backgroundMap, random creature, powers, look tables, look algorithm, loot, structure | `VERIFIED` for tested serialized layouts |
| Advect | 32-byte runtime resource with 128×128 vector-map claim; no current decoder | `SUPPORTED` name/structure, `UNKNOWN` payload |
| Model families | `crt`, `bld`, `vcl`, `cll`, `ufo`, `flr`, `bem`, `smt`, `gmsh` type IDs and SDK-associated groups | `SUPPORTED`; composition ownership not universally decoded |
| Effects/materials | `effdir`, RW4 MeshCompiledStateLink, shader/material groups, effect worlds and visual-effect vtables | `SUPPORTED` structural; payload semantics unresolved |
| Audio | `AudioSystem`, `AudioTrack`, play/procedural/stop/property surface, cell sound field | `SUPPORTED` service surface, low-confidence content format |
| Planet/terrain | `ITerrain`, `cTerrainSphere`, `cPlanet`, `cPlanetModel`, `cPlanetRecord`, high-LOD structures and async asset lifecycle | `SUPPORTED` SDK/Ghidra layout; no runtime trace |
| Property | `PropertyList`/`DirectPropertyList` vtables and Read/Write anchors | `SUPPORTED` interface; round trip unresolved |
| Metadata | Sporepedia/Pollinator asset metadata and local query surface | `SUPPORTED`; network behavior unresolved |

## Record and container topology

The DBPF package is the root. A package index yields typed record bytes after optional QFS decompression. The original `Resource::cResourceManager` and `DatabasePackedFile` are SDK-associated classes with the following relevant binary anchors:

- `Resource::cResourceManager::Initialize` at `0x008DE530`.
- `DatabasePackedFile::Lock` SDK anchor at `0x008D84F0`, with repaired/live-body evidence around `0x008D84D0`.
- `PFIndexModifiable::Read` SDK anchor at `0x008DBCC0`, with repaired/live-body evidence around `0x008DBC20`.
- `PFRecordRead` family associated with the 26-slot record-read vtable at `0x0140A328`.

The exact original multi-package priority, directory mapping, cache behavior, async request behavior, and name-to-instance mapping are not recovered. The replacement boundary must retain the key triple and explicit missing/error results while hiding package mechanics.

RW4 is a nested container rather than a flat asset list. Its manifest points to SectionTypes, external arenas, subreferences, and atoms. Each SectionInfo has `pData`, flags, size, alignment, type-code index, and type code. BaseResource data pointers are relative to `pBufferData`; other section data pointers are absolute. Known section type codes include BaseResource, manifest/type/arena/subreference/atom sections, Raster, IndexBuffer, TextureOverride, Mesh, MeshCompiledStateLink, BlendShapeBuffer, KeyframeAnim, Skeleton, AnimationSkin, TriangleKDTreeProcedural, BBox, MorphHandle, Animations, and BlendShape. Spore-specific `0x2000B` and `0x7000B` remain unknown; their payloads must not be assigned a semantic name without further evidence.

GMDL v8 has a renderable prefix followed by a variable animation/trailer family. The prefix contains file-key references, mesh count, bounds/radius, index buffers, D3D-style vertex descriptors, vertex buffers, mesh references, material IDs, and material information. Texture-set ID `0x20D` contains sampler/opaque data and instance/group references. Shader-data IDs are skipped only when a documented size exists; unknown IDs fail in the current reader. Version 9 is unvalidated. Real cell-family records carry a larger opaque baked-deform trailer, so animation execution and exact trailer framing remain separate gaps.

The `0x0F43029A` world-object record is a separate model/scene-part format, not a CellSerializer record. Its 20-byte header carries magic `0xABB455B7`, version 9 or 10, and three counts. The body contains part-name strings such as spine/eye/sense/limb/foot, plausible vectors, and opaque data. The walker accounts for all bytes but cannot establish the field order or original placement ownership.

## Descriptors and nested reference graphs

The core descriptor contracts are:

- `ResourceKey`: 12 bytes, `instanceID`, `typeID`, `groupID`; wildcard is `0xFFFFFFFF`.
- GMDL vertex element: 12 bytes, stream, offset, declaration type/method/usage/index, and type code; stride is the maximum decoded element end.
- GMDL material texture set: 28-byte material-info entry structure followed by texture-set entries of 24 bytes; each entry carries sampler/opaque bytes and instance/group identity.
- RW4 SectionInfo: 24 bytes, with the data pointer rule above.
- CellSerializer nested records: count-driven arrays embedded after fixed headers, with pointer-shaped serialized words and dead pointer slots. These are decoded as resource IDs, not host pointers.
- Cell reference graph: globals → world → populate/advect; populate → cell; cell → structure, break, pieces, leak, expel, explosion table, loot, poison and AI outputs; structure → attachment structure/random-creature/effect; globals → effectMap/backgroundMap/lookAlgorithm.

The `cCellGlobalsResource` is a 276-byte, 69-field tuning/reference record. The `cCellCellResource` is a direct 796-byte serialization with a 164-byte localized name, three 180-byte AI blocks, a 12-byte eat block, behavior flags, sizes, and typed reference words. The world, populate, effect, background, random-creature, powers, look, loot, and structure records use explicit fixed headers and count-span validation. This gives a strong content graph even where the original consumer behavior is unknown.

## Handles, containers, and vtables

`ResourceObject` is a 20-byte reference-counted object with a `ResourceKey`; `CachedResourceObject` adds a final-release callback. `cCellDataReference_` is 16 bytes: instance ID, serializer, intrusive resource, and counter. The SDK-associated `Create` anchor is `0x00E82420`; `0x00E82340` has a static `FUN_00E82340` body and must remain an unresolved adjacent/alias candidate. The two addresses are not merged.

`Graphics::Texture` is a 32-byte handle-like object containing a raster pointer, loading/force-load/LOD/modified flags, reference count, resource key, and direct raster resource pointer. `AudioTrack` is an `int` index created and destroyed through the audio service. Model, animation, lighting, and effect worlds are interface pointers; `cCellGFX` stores preloaded vectors, world/layer handles, an effect-instance vector, a 256-object GFX pool, and three audio tracks.

Relevant vtable evidence is name/structure associated, not RTTI:

| Class/interface | Slots/address | Binary or SDK anchor |
|---|---:|---|
| `IResourceManager` | 38 / `0x01436AE8` | SDK association at `0x008DE450` |
| `DatabaseDirectoryFiles` | 23 / `0x014084F0` | SDK Resource association |
| `DatabasePackedFile` | 37 vtable slots; 904-byte object | SDK Resource family around `0x008D84D0` |
| `PFIndexModifiable` | 18 vtable slots; 76-byte object | SDK Resource family around `0x008DBC20` |
| `PFRecordRead` | 26 / `0x0140A328` | SDK Resource association around `0x008DC600` |
| `PropertyList` | 19 / `0x01408820` | SDK PropertyList association |
| `DirectPropertyList` | 19 / `0x01408870` | SDK DirectPropertyList association |
| `ITextureManager` | 31 | SDK association `0x0067DD20` |
| `IModelManager` | 15 | SDK association `0x0067DD40` |
| `IModelWorld` | 96 | SDK association `0x0074B760` |
| `cCellModeStrategy` | 27 / `0x01485550` | SDK Cell-mode vtable association |
| `AudioSystem` | 1 vtable slot | SDK association `0x00A20670` |
| `ITerrain` | 75 | SDK interface layout |
| `cTerrainSphere` | 40-slot candidate `0x01490BE8` | Terrain/Sporepedia candidate; inherited interface layout remains 75 slots |
| `IEffectsManager` | 50 | SDK association `0x0067DD90` |
| `IEffectsWorld` | 22 | Ghidra vtable structure |
| `IVisualEffect` | 26 | Ghidra vtable structure |
| `cSPAssetDataOTDB` | 40 / `0x013FF648` | Sporepedia SDK/vtable association |

The Ghidra vtable scan found 3,081 candidates, but only 20 labeled candidates. Candidate slots and namespace associations are evidence, not proof of exact class identity. The `cTerrainSphere` candidate must remain bounded because the class inherits `ITerrain` and has a larger interface layout.

## Lifecycle archaeology

The static lifecycle can be stated without claiming runtime observation:

1. `cResourceManager::Initialize` builds resource-name/database maps.
2. A database is registered or locked; its header/index is read through `DatabasePackedFile`/`PFIndexModifiable`.
3. A record is opened as a stream, read or written, then closed. OpenSpore currently implements the bounded DBPF/QFS read path only.
4. A factory decodes bytes into a `ResourceObject` or `CachedResourceObject`; the original manager supports synchronous and async lookup, reload, write, factory registration, database registration, cache lookup, and cache flush, but their exact ordering is unresolved.
5. Cell records resolve through `cCellDataReference_`/serializer data and become typed content values. The unresolved `0x00E82340`/`0x00E82420` relationship blocks exact ownership claims.
6. `cCellGFX::Initialize` at `0x00E5DBA0` creates the world/layer handle table. `PreloadResources` at `0x00E666F0` binds model/populate/content identities. `PreloadCellResource` at `0x00E663B0`, `PreloadPopulateResource` at `0x00E665C0`, and `PreloadCreature` at `0x00E64980` are SDK-associated preload stages.
7. `StartDisplay` at `0x00E55120` enables lighting/world layers and invokes named audio/effect hooks. `LoadEffectMap` at `0x00E63560` and `InstanceEffectOnCell` at `0x00E66840` provide static effect consumers.
8. Terrain `ITerrain` exposes property parsing, seed retrieval, async load completion, asset load/unload, render attach/detach, update, and dispose. `cTerrainSphere` owns terrain maps, texture/RTT groups, model keys/transforms/models, ambient effects/sounds, and player/model modifications.
9. Cell mode teardown is anchored by `OnExit` `0x00E7FC00` and `Dispose` `0x00E81F30`; exact original ordering is vtable/static evidence only.

The current OpenSpore path is a comparison, not an original oracle: `ResourceProvider` fetches one package image, `GmdlMeshSource` parses static GMDL, `CellGfx` records preloaded keys and world handles, and `cell_stage` decodes real assets. The original Cell trace is absent, and current helper-level animation/effect tests do not prove stage integration.

## Consumers and reconstruction targets

The primary consumers are:

- `IResourceProvider`: provider-independent fetch by `(type, group, instance)`; current B1 is one package image and reparses its index.
- `GmdlMeshSource`: provider bytes → GMDL → host mesh/bounds → transient renderer handle; current B2.
- `IRenderer`/modern renderer: mesh, material, texture-slot, and draw-state seam; original D3D/RenderWare implementation is replaceable.
- `cCellGFX`: world IDs, model/populate/effect preload, effect-map loading, display start/stop, and teardown.
- `CellStage`: scene records, real GMDL/raster bytes, decoded meshes, and deterministic frame manifests; positions remain inferred where no original placement is known.
- Terrain renderer: property-driven planet/terrain state, normal/height/control maps, water/reflection/refraction targets, model/effect arrays, and render passes.
- Editors/Skinner and Sporepedia/Pollinator: editor model/material/save operations, texture painting, local asset metadata, and online-boundary consumers.

The reconstruction should preserve the numeric key, nested record reference graph, static GMDL/RW4/raster byte contracts, material/texture slot semantics, world/layer association, preload/display/teardown ordering, planet async lifecycle, and normalized audio cue/track behavior. It should replace DBPF/QFS, original resource-manager storage, RenderWare/D3D9 object graphs, DSOUND, Win32, and CRT plumbing. It should defer GMDL v9, complete animation/baked-deform execution, unknown RW4 sections, per-instance naming, multi-package priority/cache, original material pixels, effect payload semantics, property round-trip, and all untraced planet/audio/placement behavior.

## Open questions and stopping conditions

The partition retains thirteen explicit questions in the JSON. The highest-value blockers are:

- Original multi-package load order, name mapping, cache, async, and reload behavior.
- GMDL v9 and complete animation/baked-deform schema.
- Unknown RW4 `0x2000B`/`0x7000B` and material/animation payloads.
- Raster envelope words and non-DXT5 paths.
- Effect-map and background-map scalar semantics.
- The `0x00E82340` versus `0x00E82420` reference alias.
- World-object field order and procedural placement.
- Original planet generation, weather, model modifications, asset unload, and rendering order.
- Audio record formats, cue identity, channel ownership, and event order.
- `.prop` stream round trip and save/load field handoffs.
- Material shader bytes, texture slots, and pixel output.
- Original scene placement and role identity.

No question is closed by names, vtable proximity, static decompilation, current source, or a zero-event trace. Positive original Cell/Space/Terrain/Audio observations, matched resource/frame events, and human review are required before runtime promotion.

## Provenance

Primary evidence is the pinned binary hash, `knowledgegraph/research/semantic-atlas.json`, the semantic atlas narrative, the xref snapshot `2540f2ca`, `docs/analysis/vtables.json`, the global campaign `track-k-engine-boundaries.json`, `track-o-packages-testability.json`, `track-p-coverage.json`, decomp-gap partitions, the SDK headers under `Spore-ModAPI/`, and the bounded current asset readers under `src/assets/`. The xref export covers 223,704 canonical rows; the atlas records 2,035 Ghidra structures and no MSVC RTTI. The current source is used only as corroborated comparison. No proprietary payload or SPORE data is included.

Ghidra was not open during this partition. No Ghidra, binary, SPORE, or history state was modified.
