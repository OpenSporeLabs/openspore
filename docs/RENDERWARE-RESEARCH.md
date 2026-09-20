# OpenSpore — RenderWare / Rendering Research Report

- **Date**: 2026-09-20
- **Target**: Spore 3.1.0.22 (GOG), `SporeApp.exe` (PE32 i386, MSVC v9, 20.4 MB)
- **Method**: Clean-room analysis only — Ghidra (MCP), Spore-ModAPI SDK headers (GPL, reference-only),
  SporeModder-FX sources (GPL, reference-only), direct binary/asset inspection with our own Python tools,
  web research. **No proprietary code, no decompiled EA source is copied.**
- **Companion data**: `knowledgegraph/spore.db` entries (see §17); asset parsers in `/tmp/opencode/spore/`
  (`dbpf.py`, `rw4.py`, `typescan.py`) — promote to `tools/` before Phase 1.

---

## 1. Executive summary

Spore's renderer is **RenderWare 3 statically linked into `SporeApp.exe`** behind a Maxis `Graphics::`
abstraction, rendering to **Direct3D 9** (raw `IDirect3D9`/`IDirect3DDevice9` calls, plus a thin
`RenderUtils` device wrapper). All 3D content ships in **RW4 containers** (`rw4` type `0x2F4E681B`)
inside DBPF v3 `.package` archives; the game also emits **gmdl** (runtime model) and **raster**
(game-generated texture) containers. Shaders are **pre-compiled D3D9 bytecode** — the binary imports
`d3dx9_27.dll` but contains **zero D3DX calls** (dead import); there is no runtime HLSL.

For OpenSpore we **replace the RW3 device layer with a modern Vulkan/GL backend** while preserving:
(1) the RW4/gmdl asset contract, (2) the D3D9-era visual semantics (fixed-function lighting, per-material
D3D9 PS1.1/VS1.1 class shaders, DXT5 mip chains), and (3) the `Graphics::` manager API surface as the
semantic compatibility boundary. The open-source references are **librw (MIT — usable as code or
reference)** and **re3 (unlicensed — reference only, DMCA-takedown history)**.

---

## 2. Scope & methodology

| Track | Tool | Result |
|---|---|---|
| Binary structure | Ghidra 12.1.2 headless, MCP `127.0.0.1:8089`, project `~/ghidra-spore-project/SporeProject` | 58,757 funcs; 1,670 SDK-named (from `SporeGhidra_march2017.xml`); no MSVC RTTI |
| Runtime semantics | Spore-ModAPI SDK headers (GPL-3.0, reference-only) | Manager interfaces, struct layouts |
| Asset formats | Own Python parsers (`/tmp/opencode/spore/`), cross-checked vs SporeModder-FX (GPL, reference-only) | RW4, gmdl, DBPF v3 + QFS all decoded from real files |
| Type-ID vocabulary | Spore-ModAPI `TypeIDs` enum + in-game prop map `0x1C7AC81` | Full type table (§14) |
| Open source | Web research | librw (MIT), re3/reVC (unlicensed) |

**Clean-room rules applied**: Spore-ModAPI and SporeModder-FX used for *semantics* (layouts, enums,
field order) only. No code copied from GPL/unlicensed sources into the MIT OpenSpore tree.

---

## 3. Rendering stack overview

```
SporeApp.exe (single static binary)
├── App / Simulator / Terrain / Graphics / RenderWare namespaces (C++ classes, no RTTI)
│   ├── Graphics::  — Maxis abstraction layer
│   │   ├── IRenderer / IMaterialManager / ITextureManager / ILightingManager (singletons)
│   │   ├── Renderer (device owner; Init/Resize @ ~0x0075e900)
│   │   ├── RenderUtils (sD3D, sDevice, sPresentParams, CreateDevice, SetPresentationParameters)
│   │   ├── ActiveState (sShader, SetTexture, SetShaderData — current-frame state cache)
│   │   ├── MaterialShader (global linked list keyed by shaderID; ctor @ ~0x011f4440)
│   │   └── CompiledState (Load / GetRaster / SetRaster @ ~0x011ee700-8c0)
│   └── RenderWare:: — ported RW3 C++ objects (Mesh, Raster, RWHeader, VertexDescriptionBase, ...)
│       └── RenderWare::Mesh::Render / SetIndexBuffer (draw path, §6.3)
├── Terrain::cTerrainSphere / cTerrainSphereQuad — the main world (RenderLand/RenderWater/
│   RenderAtmosphere/RenderDecals/RenderSeabedAsLand per quad)
├── Skinner::cSkinnerTexturePainter — editor paint path (StartRender/EndRender)
└── Imports: d3d9.dll (Direct3DCreate9), d3dx9_27.dll (NEVER CALLED), DINPUT8, DSOUND,
    steam_api.dll (ordinal import table), msvcr90.dll
```

Key facts:
- **No RenderWare DLL** in `SporeBin/` (only `msvcr90.dll`, `steam_api.dll`). RW is statically
  linked — proven by embedded source-path strings, e.g.
  `\Spore\SporeEP1ML\Core\RenderWare\platform\src\graphics\core\device\target\dx9\rwgdrvgraph.cpp`.
- `SporeEP1ML` = Maxis' "Middle Layer" over RW. Spore ships its own RW build (with the DX9 device
  target) plus the standard `rwt*`-level C++ classes re-implemented in the `RenderWare::` namespace.
- Graphics device object (`Graphics__RenderUtils__sDevice`) is **not** the raw `IDirect3DDevice9`
  (its vtable slots at +0x144/+0x1a0/+0x190 don't match ID3D9 layout) — it is the Maxis/RW device
  wrapper around the raw device.

---

## 4. Binary architecture

- PE32, i386, image base `0x00400000`, linked with MSVC v9, **no RTTI** (class hierarchy only via
  vtables + SDK structs).
- Import table (495 symbols): kernel32, user32, gdi32, advapi32, **d3d9**, **d3dx9_27** (dead),
  DINPUT8, DSOUND, ws2_32, dbghelp, **steam_api** (30+ ordinal imports).
- Named SDK anchors (13 render-related; addresses from `SporeGhidra_march2017.xml`):

| Symbol | Address |
|---|---|
| `Graphics::IRenderer::Get` | `0x0067dd10` |
| `Graphics::ITextureManager::Get` | `0x0067dd20` |
| `Graphics::IMaterialManager::Get` | `0x0067dd30` |
| `Graphics::ILightingManager::Get` | `0x0067dd50` |
| `Graphics::RenderUtils::SetPresentationParameters` | `0x011f7d30` |
| `Graphics::RenderUtils::CreateDevice` | `0x011f86b0` (fn body `0x011f8680`) |
| `Graphics::MaterialShader::Initialize` | `0x011f4470` (ctor fn `0x011f4440`) |
| `Graphics::MaterialShader::GetMaterialShader` | `0x011fa030` |
| `RenderWare::CompiledState::SetRaster / GetRaster / Load` | `0x011ee700` / `0x011ee8c0` / — |
| `RenderWare::Mesh::Render` | `0x011f9740` (draw fn body `0x011f9710`) |
| `RenderWare::Mesh::SetVertexBuffer / SetIndexBuffer / SetIndicesCount` | `0x011f96xx-7xx` |
| `RenderWare::Raster::Create / CreateRaster / Extract / Fill / Delete / D3D9AddToUnmanagedList` | `0x011f...` |
| `RenderWare::RWHeader::GetRWObject` | `0x011e2920` |
| `RenderWare::VertexDescriptionBase::LoadDeclaration / D3D9VertexDescriptorAddToList` | `0x011f2bf0` / `0x011f...` |
| `Graphics::ActiveState::SetTexture` / `SetShaderData` | `0x011f12a0` / `0x00777b50` |
| `Terrain::cTerrainSphereQuad::RenderLand` | `0x00fb66a0` |
| `Terrain::cTerrainSphere::MainRenderPass` | — |
| `Graphics::Model::Release` | `0x0040f360` |
| `Graphics::cModelWorld::UpdateWithLODMeshes` | — |

Caveat: SDK label addresses sometimes land a few bytes into a function (Ghidra's auto boundaries);
treat them as anchors, re-verify with xrefs.

---

## 5. Device init path (decompiled)

`RenderUtils::CreateDevice` (`0x011f8680`), called from `Renderer::Init/Resize` (`0x0075e900` and
`0x0075f030` — the two call sites are the normal and the "re-create" paths):

1. `(*sD3D + 0x38)` → **IDirect3D9::CheckAdapterFormat** (vtable slot 14 ✓).
2. `(*sD3D + 0x40)` → **IDirect3D9::CreateDevice** (slot 16 ✓) → wrapped into `sDevice`.
3. Presentation-flags computation from config: windowed/fullscreen + vsync bit (`0x40`/`0x50`),
   `0x80` path when a second flag is set, else `0x20` — i.e. a D3DPRESENT flags word built from
   config values (`DAT_01712470/74/78` + `Prop_GetPropValueBool(0x5dd4647)` fullscreen toggle).
4. `FUN_011efeb0(&sMainColorRTT, w, h, 0, 1, ...)` and `(..., 0, 2, DAT_016f8bc4)` — creates the
   **main color render target** (type=1) and **main depth RT** (type=2, format from `DAT_016f8bc4`).
5. `(*sDevice + 0x98)` (backbuffer query), `(*sDevice + 0xa0)` → **SetRenderTarget(&colorRT)**.
6. Subsystem init chain, each must succeed (else abort): `0x011f3990 → 0x011f2bb0 → 0x011f9f90 →
   0x011f5ac0 → 0x011f5220 → 0x011f6180 → 0x011f5a40 → 0x011f4630` (render states, samplers,
   default shaders/materials, etc.).
7. Success: state flag `= 2` (ready), `QueryPerformanceCounter` timestamp recorded
   (`DAT_016f9128`).

`Renderer::Init/Resize` additionally: reads resolution from config (`<0` → defaults from
`DAT_01712444` block), handles thumbnail manager (2048-entry buffer at `DAT_016fa5e8`), computes
aspect `fAspect = height / (width/height)` (note the inverted ratio stored at `+0x78`), and calls
`ConfigManager::ResetToDefaults` on change.

**OpenSpore mapping**: this whole chain becomes `Renderer::Init(backend, window, presentParams)` →
swapchain + main RT/depth views + per-subsystem `Init()`. The "state==2" flag and the QPC timestamp
are the only externally observable behaviors worth preserving.

---

## 6. Frame & draw path

### 6.1 World pass
`Terrain::cTerrainSphere` (the planet) → per visible `cTerrainSphereQuad` →
`RenderLand` / `RenderSeabedAsLand` / `RenderWater` / `RenderAtmosphere` / `RenderDecals`
(`0x00fb66a0` … `0x00fb6dd0`+). Callers of the land path: `0x00fb6f50`, `0x00fb6fb0`, `0x00fb71c0`
(the quad's main render dispatcher).

### 6.2 Mesh draw helper (decompiled, `0x00faef10`)
```
SetIndicesCount(mesh, count)
globalRenderState[0x1c] = 0; globalRenderState[0x20] = indexBuffer.usage
SetVertexBuffer(0, indexBuffer-associated VB); SetVertexBuffer(1, sSecondVB)
SetVertexCount(count)
RenderWare::Mesh::SetIndexBuffer(mesh, indexBuffer)   // = the draw call
```

### 6.3 `RenderWare::Mesh::SetIndexBuffer` = draw (decompiled, `0x011f9710`)
The "SetIndexBuffer" is really the RW3 `mesh->render` equivalent:

1. `shader = ActiveState::sShader; decl = shader->vtbl[3]()` — the **active shader's vertex declaration**.
2. For each stream in the declaration: read `(bufferPtr, stride)` from the declaration; if the
   binding triple `(stride, buffer, streamIdx)` changed since last frame →
   `(*sDevice + 0x190)(device, stream, stride, buffer, flag)` = **SetStreamSource** on the wrapper.
   Stale streams beyond the current count are explicitly zeroed (unbind).
3. Index buffer: if `*piIdxBuf != cached` and `(*sDevice + 0x1a0)` (IsIndicesInScope-equivalent)
   passes → `(*sDevice + 0x144)` = **SetIndices**.
4. The actual `DrawIndexedPrimitive` is issued by the caller (`Mesh::Render`, `0x011f9740`).

**Semantics to preserve**: per-material shader state (vertex declaration + constants + textures),
stream rebind only-on-change, explicit unbind of surplus streams, index-buffer scope check.

---

## 7. RW4 container format (validated on real files)

Verified with our parser (`/tmp/opencode/spore/rw4.py`) against extracted assets
(`out/rw4_7.bin`, `rw4_11.bin`, `rw4_12.bin` from `Spore_Graphics.package`).

### 7.1 Magic (28 bytes, exact)
```
89 52 57 34 77 33 32 00 0D 0A 1A 0A 00 20 04 00 22 34 35 34 00 22 00 00 00 22 6E 75 6C 6C 34
```
i.e. `\x89RW4w32\0\r\n\x1a\x0a` + 16 bytes `00 20 04 00 22 343534 00 22 00000000 22 6E756C6C34`
(`"454"` + `"null4"` markers).

### 7.2 Header (little-endian u32 fields)

| Off | Field | Notes |
|---|---|---|
| 0x00 | magic (28 B) | above |
| 0x1C | `type` | 1 = MODEL, `0x04000000` = TEXTURE, `0xCAFED00D` = SPECIAL (in-game marker) |
| 0x20 | objectCount | objects (sections) |
| 0x24 | sectionCount | usually == objectCount |
| 0x28..0x2F | reserved/version fields | |
| 0x30 | `pSectionInfo` | absolute file offset of the section-info table |
| 0x34 | `field` | 16 for models, 4 for textures |
| 0x44 | `pBufferData` | absolute offset of the data arena |
| 0x4C | `buffersSize` | size of data arena |
| 0x98 | **manifest** | first object (see 7.3) |

### 7.3 Manifest (at 0x98, 24 B)
`typeCode = 0x10004` (SectionManifest), then `4`, `12`, and 4 sub-object offsets:
SectionTypes, SectionExternalArenas, SectionSubReferences, SectionAtoms.

### 7.4 Section info table (24 B each, at `pSectionInfo`)
| Off | Field |
|---|---|
| 0x00 | `pData` — **relative to `pBufferData`** for BaseResource, absolute otherwise |
| 0x04 | `field_04` (often 1 / flags) |
| 0x08 | `size` |
| 0x0C | `alignment` |
| 0x10 | `typeCodeIndex` |
| 0x14 | `typeCode` |

### 7.5 Object type-code map (from SMFX, all confirmed present in real files)

| Code | Class | Code | Class |
|---|---|---|---|
| 0x10030 | BaseResource | 0x20007 | IndexBuffer |
| 0x10004 | SectionManifest | 0x20008 | TextureOverride |
| 0x10005 | SectionTypes | 0x20009 | Mesh |
| 0x10006 | SectionExternalArenas | 0x2001a | MeshCompiledStateLink |
| 0x10007 | SectionSubReferences | 0x200af | BlendShapeBuffer |
| 0x10008 | SectionAtoms | 0x70001 | KeyframeAnim |
| 0x20003 | Raster | 0x70002 | Skeleton |
| 0x20004 | VertexDescription | 0x70003 | AnimationSkin |
| 0x20005 | VertexBuffer | 0x80003 | TriangleKDTreeProcedural |
| 0x2000b | (Spore-specific, unmapped) | 0x80005 | BBox |
| 0x7000b | (Spore-specific, unmapped) | 0xff0000 / 0xff0001 / 0xff0002 | MorphHandle / Animations / BlendShape |

### 7.6 Sample: `rw4_11.bin` (MODEL, 20 sections)
KeyframeAnim ×2, Skeleton ×3, BBox (19,760 B), TriangleKDTreeProcedural (19,760 B),
VertexDescription, IndexBuffer (72 B), BaseResource ×2 (2,784 + 43,704 B), Mesh, BlendShape,
BlendShapeBuffer (143,936 B), Raster, + 0x2000b + 0x7000b.

### 7.7 Sample: `rw4_7.bin` / `rw4_12.bin` (TEXTURE, identical)
128×128, DXT5, 8 mips, single BaseResource (21,968 B).

---

## 8. gmdl / GameModelResource (validated on real files)

Extracted `out/gmdl_148.bin` (3,700 B) and `out/gmdl_156.bin` (2,254 B) from `Spore_Content.package`
(group `0x40666203` = FloraModels). Top-level layout (little-endian; cross-checked with SMFX
`GameModelResource.java`):

| Off | Field |
|---|---|
| 0x00 | `version` (≤ 9) |
| 0x04 | `referencedFiles` count, then {instanceID, groupID, typeID} keys |
| + | `meshCount` |
| + | bounding box (7 floats: min xyz, max xyz, + 2) |
| + | `boundingRadius` |
| + | indexBuffers[]: primitiveType, count, numBits (16), bufferSize |
| + | vertexDescriptors[] (RWVertexElement arrays) |
| + | vertexBuffers[] |
| + | meshes[] |
| + | materialInfos[] |
| + | boneRanges[] |
| + | animDatas[] (GameModelAnimData: baked deforms, bone ranges) |

`gmdl_156` decoded: version 8, 0 refs, 1 mesh, 153 u16 indices (306 B) forming a grid of quads
(0-1, 2-3… pattern), 16-bit indices — a **terrain/heightfield patch** (flora ground), not a
character model. The monotonic float grid earlier observed is the vertex positions.

---

## 9. Textures & rasters

- `Spore_Graphics.package` holds **8,360 png** + **9,368 rw4** records; `Spore_Content` holds
  2,954 `raster` (game-generated) records.
- RW4 TEXTURE containers wrap a DXT-compressed Raster (DXT5 8-mip chains seen; `Raster::Create`,
  `CreateRaster`, `Extract`, `Fill`, `D3D9AddToUnmanagedList` in the SDK).
- Type-ID table: `jpeg 0x2F7D0002, png 0x2F7D0004, bmp 0x2F7D0005, tga 0x2F7D0006, gif 0x2F7D0007,
  dds 0x17952E6C, raster 0x2F4E681C`.
- **OpenSpore**: decode png/tga/dds once at load into a texture atlas/texture array; keep DXT5 as the
  on-disk contract, upload as BC3 (Vulkan) / S3TC (GL). Mip count + DXT5 flag are the only
  observable properties the game logic touches.

---

## 10. Materials & shaders (no runtime HLSL)

- **Dead D3DX import**: the PE imports `d3dx9_27.dll` (D3DXCompileShader et al.) but a full
  instruction scan (4.6 M instructions) finds **zero D3DX call sites**. Shaders ship **pre-compiled**
  (D3D9 VS/PS bytecode) inside packages.
- Groups that hold them: `CompiledStatesLink 0x40212000`, `CompiledStates 0x40212001`,
  `ShaderFragments 0x40212002`, `Shaders 0x40212004` (CommonIDs.h).
- `MaterialShader`: global linked list, ctor fields `{id, data*, flag, texSlots (2B×3), 4B padding,
  next@+0x40}`; `GetMaterialShader(shaderID)` walks the list by `mID` and caches the hit in
  `DAT_017186d4`.
- `CompiledState` (per material): `Load`, `SetRaster`/`GetRaster` — binds raster to texture slots;
  the draw path reads `ActiveState::sShader`'s vtable slot 3 for the vertex declaration (§6.3).
- `RenderUtils::RegisterShaderData / GetShaderDataSize` — constant-bulk upload path for shader data.

**OpenSpore**: keep `MaterialShader` (id-keyed cache) + `CompiledState` (slot bindings) as the
semantic interface; replace the D3D9 bytecode with **glsl450/HLSL SPIR-V** implementing the same
lighting model (D3D9 fixed-function class: per-vertex N·L diffuse, fog, 8 texture slots with
MODULATE/ADD/TEXTURE_COMBINE semantics).

---

## 11. Animation

RW4 sections: `KeyframeAnim (0x70001)`, `Skeleton (0x70002)`, `AnimationSkin (0x70003)`,
`BlendShape (0xff0002)` + `BlendShapeBuffer (0x200af)`, `MorphHandle (0xff0000)`,
`Animations (0xff0001)` container. `GameModelAnimData` inside gmdl carries baked deforms +
bone ranges. `rw4_11` sample: 2 KeyframeAnims + 3 Skeletons + 143 KB BlendShapeBuffer — a
morph-heavy creature/creature-part model.

**OpenSpore**: standard skinning (bone matrices from Skeleton, weights in VB) + blend-shape
evaluation (morph target offsets). RW4 section payloads are the source of truth; the `0x7000b`
Spore-specific section must be dumped and classified (candidate: per-frame blend-shape weights).

---

## 12. World & terrain

`Terrain::cTerrainSphere` — the game world is a **sphere** subdivided into quads; per-quad passes:
`RenderLand`, `RenderSeabedAsLand`, `RenderWater`, `RenderAtmosphere`, `RenderDecals`
(`0x00fb66a0`-`0x00fb72xx` region). LOD via `Graphics::cModelWorld::UpdateWithLODMeshes`.
Flora/heightfield ground comes from gmdl height patches (§8) in group `0x40666203`.

---

## 13. Asset pipeline & container summary

- **DBPF v3**: 96-byte header (major=3, minor=0, idxMinor=3); no name table; 32-bit binary IDs
  (FNV-1a hashes of names); index records `{instance, group, type, offset, size}`; payload often
  QFS-compressed.
- **QFS/RefPack** (implemented in `dbpf.py:qfs_decompress`): 5-byte header `0x10FB`/`0x50FB` +
  3-byte big-endian size, then LZ-style control-byte data. Not zlib.
- **Type-ID vocabulary** (Spore-ModAPI `TypeIDs` enum + in-game map `0x1C7AC81`):

| Type | ID | Type | ID |
|---|---|---|---|
| rw4 | 0x2F4E681B | raster | 0x2F4E681C |
| gmdl | 0x00E6BCE5 | bem | 0x1A99B06B |
| gmsh | 0x01C135DA | smt | 0x0469A3F7 |
| prop | 0x00B1B104 | effdir | 0xEA5118B0 |
| animation | 0xEE17C6AD | pollen_metadata | 0x030BDEE3 |
| dds | 0x17952E6C | txt | 0x24A0E52 |
| jpeg/png/bmp/tga/gif | 0x2F7D0002-07 | crt/bld/vcl/cll/ufo/flr | 0x2B978C46 / 0x2399BE55 / 0x24682294 / 0x3D97A8E4 / 0x476A98C7 / 0x438F6347 |
| cmp/cnv | 0x04F684A4 / 0x055ADA24 | backgroundMap/effectMap/cell/globals | 0x612B3191 / 0x433FB70C / 0xDFAD9F51 / 0x2A3CE5B7 |
| look_algorithm/look_table/lootTable/populate/powers/random_creature/structure/world/advect/arth/adventure | see §13 (full list in SDK `TypeIDs` header) | | |

- `Spore_Graphics` top types: rw4 ×9368, png ×8360, prop ×3761, gmsh ×2422,
  **0x250FE9A2 ×394 (undocumented — likely EP material/variant data)**, 0x02393756 ×136,
  0x497767B9 ×120, 0x03E421ED ×76 (undocumented, EP1/EP2 additions), effdir ×18, smt ×12.

---

## 14. Open-source references & licenses

| Project | License | Use in OpenSpore | Notes |
|---|---|---|---|
| **librw** (`aap/librw`, 786★) | **MIT** | Usable as code *or* reference | RW3 re-impl (DFF/TXD), backends D3D8/9 + GL3 + GLES2; `Driver`/`Device` abstraction, integrated RpWorld; AUR `librw-git` |
| **re3 / reVC** (`GTAmodding/re3`, forks `nosro1`, `Cai1Hsu`) | **None** ("not in a position to give a license") | **Reference only** | Full GTA III/VC reverse; `src/fakerw/fake.cpp` = Rw*/Rp* → librw shim; original repo DMCA'd by Take-Two (2021-02); forks remain |
| Spore-ModAPI (`~/apps/Spore-ModAPI`) | GPL-3.0 | Reference only (SDK semantics) | 1,670 functions + 1,895 structs in Ghidra XML |
| SporeModder-FX (`Spore-Community/SporeModder-FX`) | GPL-3.0 | Reference only (format parsers) | RW4/gmdl/DBPF/QFS Java reference impls |
| reVC | same as re3 | Reference only | miami branch |

**Policy**: copy code only from MIT (librw, with attribution); everything else semantics-only.
re3's `fakerw` shim is the best *pattern* reference for keeping RW-style call signatures over a
modern backend — replicate the pattern, not the code.

---

## 15. Proposed modern renderer architecture (OpenSpore)

### 15.1 Subsystem classification

| Subsystem (Spore) | Class | OpenSpore treatment |
|---|---|---|
| `Graphics::IRenderer` + `Renderer` (init/resize/state) | **MUST** | Keep interface; reimplement over Vulkan |
| `RenderUtils` device wrapper (CreateDevice, SetPresentationParameters) | **MUST** | `IGpuDevice` abstraction (Vulkan primary, GL fallback) |
| Main color+depth RTT, SetRenderTarget | **MUST** | Swapchain + main renderpass/RT views |
| `ActiveState` (shader/texture state cache) | **MUST** | Keep the on-change rebind semantics (§6.3) |
| `MaterialShader` id-keyed cache + `GetMaterialShader` | **MUST** | Keep (it's the material↔shader contract) |
| `CompiledState` slot/raster binding | **MUST** | Keep; back with push constants + bind index |
| `RenderWare::Mesh::Render` draw path (streams, indices, counts) | **MUST** | Map to `vkCmdDrawIndexed` with per-material bindings |
| D3D9 fixed-function lighting / PS1.1-class shaders | **SHOULD** | Reimplement as SPIR-V (per-vertex N·L, fog, TCB) |
| DXT5 mip textures, raster group | **SHOULD** | BC3 upload; keep DXT5 on disk |
| RW4 container + gmdl + raster containers | **MUST** | Native loader (spec in §7/§8) |
| RW4 MeshCompiledStateLink (0x2001a) | **SHOULD** | Decode → our compiled-state object |
| Terrain sphere quad passes (land/water/atmosphere/decals) | **SHOULD** | Keep pass structure; reimplement shaders |
| `Skinner::cSkinnerTexturePainter` | **SHOULD** | Editor paint path over same RTs |
| `cModelWorld::UpdateWithLODMeshes` LOD | **SHOULD** | Screen-space LOD over same mesh data |
| D3D9-specific quirks (unmanaged raster list, `D3D9VertexDescriptorAddToList`, D3DKMT escape strings) | **REPLACE** | Drop; Vulkan equivalents |
| Steam API, DINPUT8, DSOUND, registry/config plumbing | **DEFER** | Phase 3+ (input/audio are separate tracks) |
| `0x2000b` / `0x7000b` RW sections, undocumented type IDs (0x250FE9A2…) | **DEFER** | Dump + classify before Phase 2 |
| VTable/RTTI-based class dispatch (no RTTI in binary) | **REPLACE** | Normal C++17 vtables in our tree |

### 15.2 Target shape

```
src/
├── core/        (memory, allocators, events, logging — Phase 1)
├── assets/      DBPFv3 + QFS + id table   [MUST — spec §13]
├── rw4/         container + section parsers [MUST — spec §7]
├── gmdl/        GameModelResource loader    [MUST — spec §8]
├── gfx/
│   ├── device/  IDevice, Vulkan + GL backends, present, RT views   [MUST]
│   ├── state/   ActiveState, MaterialShader, CompiledState          [MUST]
│   ├── mesh/    Mesh/Vertex/Index wrappers, draw dispatch           [MUST]
│   ├── shader/  SPIR-V fixed-function-class shaders (VF lighting, fog, TCB) [SHOULD]
│   └── texture/ png/tga/dds decode → BC3, mip chains, raster        [SHOULD]
├── terrain/     sphere quads, pass structure                        [SHOULD]
└── anim/        skeleton/skin/blendshape                            [SHOULD]
```

Semantic-compatibility invariants (differential-test oracles, Wine + original):
1. Same asset → same drawn geometry (VB/IB byte-identical after our loader).
2. Same material state sequence → same pixel output within tolerance (D3D9-class lighting).
3. Device init observable flags (state==2, QPC stamp) preserved.
4. RW4/gmdl byte-level round-trip: our parser's decoded sections match SMFX's field-by-field.

---

## 16. Risks & open questions

1. **No RTTI** — class hierarchy is inferred from vtables + SDK structs; vtable pass in Ghidra never
   ran headless (0 vtable labels). *Action*: run vtable detection before relying on class structure.
2. **`0x2000b` / `0x7000b`** RW sections undocumented — dump payloads from all 9,368 rw4 models and
   classify (likely blend-shape weights / Spore-internal).
3. **Undocumented type IDs** (0x250FE9A2 ×394 etc.) — content types, not render-critical; classify
   during Phase 1 asset work.
4. **SDK label offset drift** — several labels land inside neighboring functions; always verify via
   xrefs before trusting an address.
5. **D3D9 fixed-function fidelity** — the game's PS1.1-class shaders + TCB semantics need a
   reference implementation; re3/librw's GL paths are the closest public analog.
6. **Wine oracle stability** — differential tests need the original to run headless under Wine 11;
   verify a deterministic frame capture path before Phase 2.
7. **Legal**: GOG build only (no DRM); `SPORE/` stays git-ignored; no EA assets in the tree.

---

## 17. Knowledge-graph entries & next steps

Recorded in `knowledgegraph/spore.db` (nodes: `RW4Container`, `GameModelResource`, `DBPFv3`,
`QFSCompression`, `MaterialShader`, `CompiledState`, `TerrainSphereQuad`, `SporeGraphicsDevice`;
edges: `loads`/`contains`/`uses`); test outcomes recorded for the RW4/gmdl parser validations.

**Next steps (Phase 1 entry)**
1. Promote `/tmp/opencode/spore/{dbpf,rw4,typescan}.py` into `tools/` (C++ rewrites later).
2. CMake scaffold per §15.2 (C++17, clang-format modified-Google, `fmt`).
3. C++ port of DBPFv3+QFS with differential tests vs the Python reference.
4. C++ port of RW4 + gmdl loaders; field-by-field diff vs SMFX on the extracted samples.
5. Vulkan `IGpuDevice` + main RT; present a static quad to prove the device path.
6. Ghidra vtable detection pass; then classify `0x2000b`/`0x7000b`.
