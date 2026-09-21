# 003 — Renderware research

**2026-09-20, late afternoon.** A few hours after the recon was committed
(`36e704a` is this chapter's commit, 17:29; the recon was `4927122`, 15:58), the
binary was mapped end to end — 58,757 functions, the no-RTTI fact, the singleton
spine, the bootstrap state machine, the dead services ([chapter 002](002-ghidra-foundation.md)).
What that map did *not* answer is what "reimplement Spore" actually means in practice,
and the answer to that is: it is ~80% rendering and assets. The game is one statically
linked blob whose visible surface is a planet renderer over a mountain of `.package`
content; if we cannot name the renderer and cannot read the assets, we cannot replace
either. So the afternoon went to one question — **what is the rendering stack, and what
does it load?** — and to decoding the container formats it loads. The method was
clean-room analysis only: Ghidra decompilation, Spore-ModAPI SDK *semantics*, our own
Python parsers run on extracted assets, and web research; **no proprietary code and no
decompiled EA source was copied.**

## What the renderer actually is

The headline, first: **RenderWare 3 is statically linked into `SporeApp.exe`.** It is
not a DLL. `SporeBin/` ships only `msvcr90.dll` and `steam_api.dll` — there is no
`RenderWare*.dll`, no `rw*.dll`, nothing. The proof is not inference; it is an embedded
build artifact. The binary carries its own source-path strings, and one of them is the
smoking gun for where the DX9 device target came from:

```
\Spore\SporeEP1ML\Core\RenderWare\platform\src\graphics\core\device\target\dx9\rwgdrvgraph.cpp
```

That path tells us two things at once. `SporeEP1ML` is Maxis' "Middle Layer" over
RenderWare — the namespace the game's own code calls `Graphics::` — and the `.../
device/target/dx9/` segment is RenderWare's internal platform layer. So the game ships
its *own* RW3 build (with the DX9 device target) plus the standard `rwt*`-level C++
classes re-implemented under the `RenderWare::` namespace. **VERIFIED** (the string is
present in the binary; the DLL absence is observable).

The consequence that follows: **Direct3D 9 is driven from *inside* RenderWare, not from
game code.** The PE import table contains `d3d9.dll` (`Direct3DCreate9`), but a scan of
the EXE's code finds **zero call-site xrefs to `Direct3DCreate9`** from outside the RW
device target. The raw `IDirect3D9`/`IDirect3DDevice9` calls are all in RW's `dx9`
platform code. **SUPPORTED** (import present, call xrefs absent — the two together, not
either alone).

Above that sits the Maxis `Graphics::` abstraction — the singletons and managers the
game actually talks to:

| `Graphics::` object | Role |
|---|---|
| `IRenderer` / `ITextureManager` / `IMaterialManager` / `ILightingManager` | Free `X::Get()` singletons (the same spine pattern as the app managers) |
| `Renderer` | Owns the device; `Init`/`Resize` |
| `RenderUtils` | Device wrapper: `sD3D`, `sDevice`, `sPresentParams`, `CreateDevice`, `SetPresentationParameters` |
| `ActiveState` | Current-frame state cache: `sShader`, `SetTexture`, `SetShaderData` |
| `MaterialShader` | Global id-keyed linked list; `GetMaterialShader(shaderID)` |
| `CompiledState` | Per-material `Load` / `GetRaster` / `SetRaster` |

One correction to an obvious assumption: **`RenderUtils::sDevice` is not the raw
`IDirect3DDevice9`.** Its vtable slots at `+0x144` / `+0x1a0` / `+0x190` do not line up
with the ID3D9 interface layout — it is the Maxis/RW *wrapper* around the raw device.
**SUPPORTED** (slot offsets decompiled; the mismatch is what rules out the raw interface).

Then the finding that removes an entire class of work: **there is no runtime HLSL.** The
PE imports `d3dx9_27.dll` (the `D3DXCompileShader` et al. symbols are in the IAT), which
on its own would suggest runtime shader compilation. A full scan of all **4.6 M
instructions** found **zero D3DX call sites** — the import is dead. The shaders ship
**pre-compiled as D3D9 bytecode** inside the packages (groups `0x40212001` CompiledStates,
`0x40212002` ShaderFragments, `0x40212004` Shaders). This scan is recorded in the KG as
test outcome `d3dx_usage_scan` ("0 of 4.6M instructions — dead import"). **VERIFIED.**

The draw path, decompiled (`RenderWare::Mesh::Render`, the "SetIndexBuffer" body at
`0x011f9710`):

```
shader = ActiveState::sShader
decl   = shader->vtbl[3]()            # active shader's vertex declaration
for each stream in decl:
    read (buffer, stride); if the (stride,buffer,stream) triple changed:
        sDevice+0x190(stream,stride,buffer)     # SetStreamSource
    stale streams beyond the current count are explicitly zeroed   # unbind
if *pIndexBuf != cached  and  sDevice+0x1a0(...)  # IsIndicesInScope check
        sDevice+0x144(...)                         # SetIndices
caller issues DrawIndexedPrimitive
```

The device init chain is the decompiled `RenderUtils::CreateDevice` (`0x011f8680`),
reached from `Renderer::Init`/`Resize` (`0x0075e900` / `0x0075f030`):
`IDirect3D9::CheckAdapterFormat` (`+0x38`) → `CreateDevice` (`+0x40`) → main color RTT
(type 1) + main depth RTT (type 2) → an **8-function subsystem init chain** (render
states, samplers, default shaders/materials; each must succeed or the init aborts) → on
success a **state flag `= 2` (ready)** and a `QueryPerformanceCounter` timestamp. Those
last two — the "ready" flag and the QPC stamp — are the only *externally observable*
behaviors of init worth preserving; the rest is internal plumbing.

Finally, the world model: the planet is a **sphere** (`Terrain::cTerrainSphere`)
subdivided into quads, and each visible `cTerrainSphereQuad` runs the pass set
`RenderLand` / `RenderSeabedAsLand` / `RenderWater` / `RenderAtmosphere` / `RenderDecals`
(`0x00fb66a0` region); LOD is `Graphics::cModelWorld::UpdateWithLODMeshes`. **SUPPORTED.**

## The asset formats, decoded and validated

This is where the `/tmp` parsers were born. Everything below was developed as throwaway
analysis code under `/tmp/opencode/spore/` — `dbpf.py` (DBPF + QFS), `rw4.py`,
`typescan.py`, `gmdl.py` — cross-checked against SporeModder-FX (GPL, **reference-only**)
semantics, and validated by parsing real extracted assets all the way to the **exact file
size**. They were *not yet in the repo* at this moment; the promotion to `tools/` is
[chapter 004](004-format-tooling.md).

**DBPF v3** (the outer archive, ~5 GB across 7 `.package` files): a 96-byte header
(`major=3, minor=0, idxMinor=3`), **no name table**, 32-bit binary record IDs (FNV-1a
hashes of the resource names), index records `{instance, group, type, offset, size}`, and
payload that is **often QFS-compressed**.

**QFS / RefPack** (the payload compressor): a 5-byte header — magic `0x10FB`/`0x50FB`
plus a 3-byte *big-endian* size — followed by LZ-style control-byte data. It is **not
zlib** (the framing and the control bytes are a different algorithm), which is why a naive
`zlib.decompress` fails on it.

**RW4 container** (type `0x2F4E681B` — the 3D content). The 28-byte magic, exactly:

```
89 52 57 34 77 33 32 00 0D 0A 1A 0A 00 20 04 00 22 34 35 34 00 22 00 00 00 22 6E 75 6C 6C 34
```

i.e. `\x89RW4w32\0\r\n\x1a\x0a` (a PNG-like `0x89`-prefixed marker) plus 16 bytes of
`"454"` + `"null4"` section markers. The little-endian u32 header that follows:

| Off | Field | Notes |
|---|---|---|
| `0x1C` | `type` | `1`=MODEL, `0x04000000`=TEXTURE, `0xCAFED00D`=SPECIAL (in-game marker) |
| `0x20` / `0x24` | `objectCount` / `sectionCount` | sections ≈ objects |
| `0x30` | `pSectionInfo` | absolute offset of the 24-byte-per-row section-info table |
| `0x34` | `field` | 16 for models, 4 for textures |
| `0x44` | `pBufferData` | absolute offset of the data arena |
| `0x4C` | `buffersSize` | size of the data arena |
| `0x98` | **manifest** | first object (type-code `0x10004`, then 4 sub-object offsets) |

Each 24-byte section-info row is `{pData, flag, size, align, typeCodeIndex, typeCode}`
(`pData` is relative to `pBufferData` for BaseResource, absolute otherwise). The
object type-code map (from SMFX, all confirmed present in the real files) covers
BaseResource / Raster / VertexDescription / VertexBuffer / IndexBuffer / Mesh /
TextureOverride / MeshCompiledStateLink / BlendShapeBuffer / KeyframeAnim / Skeleton /
AnimationSkin / TriangleKDTree / BBox / MorphHandle / Animations / BlendShape. Two codes
— **`0x2000b` and `0x7000b`** — appear in real Spore files but are **undocumented** (we
hypothesize a blend-shape-weight / Spore-internal section; **OPEN**, to be dumped and
classified).

Validated on real extracted samples from `Spore_Graphics.package`:

- **`rw4_11`** = a MODEL, 20 sections — KeyframeAnim ×2, Skeleton ×3, BBox (19,760 B),
  TriangleKDTreeProcedural (19,760 B), VertexDescription, IndexBuffer (72 B),
  BaseResource ×2 (2,784 + 43,704 B), Mesh, BlendShape, BlendShapeBuffer (143,936 B),
  Raster, plus one `0x2000b` and one `0x7000b`. A morph-heavy creature part.
- **`rw4_7` / `rw4_12`** = TEXTURE, identical — 128×128, DXT5, 8 mips, a single
  BaseResource (21,968 B).

Both parsed to the exact file size (recorded in the KG as `rw4_parser_validation`, pass).

**gmdl / GameModelResource** (type `0x00E6BCE5` — runtime model). Top-level layout,
little-endian, cross-checked against SMFX `GameModelResource.java`: `version` (≤ 9),
`referencedFiles` `{instanceID, groupID, typeID}` keys, `meshCount`, bounding box
(7 floats: min/max xyz + 2) + `boundingRadius`, `indexBuffers[]` (primitiveType, count,
16-bit, size), `vertexDescriptors[]`, `vertexBuffers[]`, `meshes[]`, `materialInfos[]`,
`boneRanges[]`, `animDatas[]`. Decoded **`gmdl_156`** (from `Spore_Content`, group
`0x40666203` = FloraModels): version 8, 0 refs, 1 mesh, **153 u16 indices (306 B)**
forming a grid of quads — i.e. a **terrain/heightfield patch (flora ground), not a
character model**. Recorded as `gmdl_parser_validation`, pass.

The texture landscape, from `typescan.py` over the real packages: `Spore_Graphics` holds
**8,360 `png`** + **9,368 `rw4`** records; `Spore_Content` holds **2,954 game-generated
`raster`** records. The full type-ID vocabulary comes from the SDK `TypeIDs` enum merged
with the in-game prop map record `0x1C7AC81`; it includes **undocumented** IDs we have
not yet classified — `0x250FE9A2` ×394 (likely EP material/variant data), `0x02393756`
×136, `0x497767B9` ×120, `0x03E421ED` ×76. RW4 TEXTURE containers wrap DXT-compressed
rasters (DXT5 8-mip chains); for OpenSpore the plan is to decode `png`/`tga`/`dds` once
at load into a texture atlas and keep DXT5 as the on-disk contract, uploaded as BC3.

## Licensing landscape

The analysis leans on existing open-source RE material, and the license boundaries are
explicit — they are the difference between "informed by" and "derived from" (first raised
in [chapter 001](001-repository-audit.md)):

| Project | License | Use here | Notes |
|---|---|---|---|
| **librw** (`aap/librw`) | **MIT** | Usable as code *or* reference | RW3 re-impl (DFF/TXD); D3D8/9 + GL3 + GLES2 backends; `Driver`/`Device` abstraction |
| **re3 / reVC** (`GTAmodding/re3` + forks) | **None** ("not in a position to give a license") | **Reference only** | Full GTA III/VC reverse; `src/fakerw/fake.cpp` = Rw*/Rp* → librw shim; original repo DMCA'd by Take-Two (2021-02), forks remain |
| Spore-ModAPI | GPL-3.0 | Reference only (SDK semantics) | 1,670 functions + 1,895 structs in the Ghidra XML |
| SporeModder-FX | GPL-3.0 | Reference only (format parsers) | RW4/gmdl/DBPF/QFS Java reference impls — the cross-check target for our Python |

The policy, exactly as enforced: **copy code only from MIT, with attribution; everything
else is semantics-only.** re3's `fakerw` shim is worth studying as a *pattern* — keeping
RW-style call signatures over a modern backend — and we intend to **replicate the pattern,
not the code.**

## The plan for the OpenSpore renderer

Digest of §15 of the report. The single governing decision: **replace the RW3 device
layer with a modern Vulkan backend (GL as a fallback), and keep the `Graphics::` API
surface as the semantic compatibility boundary.** The asset contract (RW4/gmdl), the
D3D9-era visual semantics (fixed-function lighting, PS1.1-class shaders, DXT5 mip chains),
and the manager API all stay; only the device target underneath changes. Subsystem
classification, compressed:

| Class | Subsystems |
|---|---|
| **MUST** | `IRenderer` (+ `Renderer`), device wrapper (`IGpuDevice`, Vulkan primary/GL fallback), main color+depth RTT, `ActiveState`, `MaterialShader`, `CompiledState`, mesh draw path, RW4/gmdl/raster loaders |
| **SHOULD** | D3D9 fixed-function lighting → SPIR-V (per-vertex N·L, fog, TCB), DXT5→BC3, MeshCompiledStateLink, terrain sphere-quad passes, `cSkinnerTexturePainter`, `cModelWorld` LOD |
| **REPLACE** | D3D9-specific quirks (unmanaged-raster list, `D3D9VertexDescriptorAddToList`); RTTI-less vtable dispatch → normal C++17 vtables |
| **DEFER** | Steam/DINPUT8/DSOUND + config plumbing (Phase 3+); `0x2000b`/`0x7000b` sections; undocumented type IDs |

The four **differential invariants** (oracles = the original running under Wine):
(1) same asset → byte-identical drawn geometry after our loader; (2) same material-state
sequence → pixels within tolerance; (3) device-init observable flags (state==2, QPC
stamp) preserved; (4) RW4/gmdl field-level round trip — our decoded sections match SMFX's
field by field. These are the acceptance criteria; they become the regression tests in
[chapter 005](005-deterministic-tests.md) and the first real frame in
[chapter 011](011-vulkan-skeleton.md).

## Knowledge graph

Everything above that is durable — formats, functions, and the test outcomes — was recorded
in the SQLite sidecar `knowledgegraph/spore.db`. As of this moment: **10 nodes / 9 edges /
3 recorded test outcomes**. Nodes: `RW4Container`, `GameModelResource`, `DBPFv3`,
`QFSCompression`, `MaterialShader`, `CompiledState`, `RenderWare_Mesh_SetIndexBuffer_Draw`,
`RenderUtils_CreateDevice`, `TerrainSphereQuad`, `SporeGraphicsDevice`. Edges:
`DBPFv3—compressesWith→QFS`, `DBPFv3—contains→RW4Container`/`GameModelResource`,
`RW4Container—references→CompiledState`, `MaterialShader—binds→CompiledState`,
`RenderWare_Mesh_Draw—uses→SporeGraphicsDevice`, `—reads→MaterialShader`,
`RenderUtils_CreateDevice—creates→SporeGraphicsDevice`,
`TerrainSphereQuad—dispatches→RenderWare_Mesh_Draw`. The three test outcomes:
`rw4_parser_validation` (pass), `gmdl_parser_validation` (pass), `d3dx_usage_scan` (pass,
"0 of 4.6M instructions — dead import").

Why a sidecar at all: Ghidra is the analysis graph and codegraph is the source graph, and
both are already their own stores; what is *not* in either is the cross-tool residue —
what we proved, what we decided, how one format maps onto the next. That residue is
**shared memory for every agent** (and for a human reading this years later): it is a
single, version-controlled, queryable file, not a graph database. Cypher buys nothing
here; `kg.py dump` does. This is the project's shared memory, and it is deliberately
small.

## Cross-links

- Back: [002 — Ghidra foundation](002-ghidra-foundation.md) (the recon; its static-link
  inventory and no-RTTI fact are the entry point into this chapter).
- Forward: [004 — Format tooling](004-format-tooling.md) (the `/tmp/opencode/spore/`
  parsers promoted into `tools/` and validated).
- Forward: [005 — Deterministic tests](005-deterministic-tests.md) (the four differential
  invariants above become the regression suite).
- Forward: [011 — Vulkan skeleton](011-vulkan-skeleton.md) (the renderer plan, first C++).

### Outcome

| Proven | Open |
|---|---|
| RW3 **statically linked** (embedded `rwgdrvgraph.cpp` build path; no RW DLL in `SporeBin`); D3D9 driven inside RW (d3d9 IAT present, zero `Direct3DCreate9` call xrefs) | `Graphics::` device wrapper is *not* raw ID3D9 — the wrapper's exact contract is inferred from slot offsets, not a full interface dump |
| **No runtime HLSL** — `d3dx9_27.dll` is a dead import (0 of 4.6M instructions); shaders ship as pre-compiled D3D9 bytecode | D3D9 fixed-function / PS1.1-class shader fidelity — needs a reference implementation before the lighting is re-implemented |
| **RW4 + gmdl + DBPF v3 + QFS decoded and validated on real extracted files, to the exact size** (KG test outcomes all pass) | **`0x2000b` / `0x7000b`** RW sections undocumented (dump + classify from all 9,368 models) |
| License policy fixed: **copy code only from MIT (librw), with attribution**; re3/SMFX/SMFX = semantics-only; re3 `fakerw` as a *pattern* reference | **Undocumented type IDs** (`0x250FE9A2` ×394, `0x02393756`, `0x497767B9`, `0x03E421ED`) unclassified |
| Renderer plan set: Vulkan device layer over the `Graphics::` semantic boundary; 4 differential invariants | **Wine oracle stability** for a deterministic headless frame capture (must be proven before Phase 2) |
| | **SDK label offset drift** — several Ghidra addresses land a few bytes inside a function; verify via xrefs before trusting |
