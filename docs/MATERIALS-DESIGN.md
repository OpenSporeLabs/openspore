# Materials / Textures — Obj15 DESIGN (no C++ implementation)

Scope: GMDL refCount-BE fix, raster-envelope parse, DXT5→RGBA8,
texture upload + sampler + basic material state, textured + normal-lit indexed
mesh. Out: full Spore material system, all shader families, swapchain, PNG32
(records are RW4 containers, §2 — not raw PNG, so no PNG decoder is built).
Asset set (orchestrator-fixed): gmdl 16594 (0x40637e03), heightfield
0x40666202/03, DXT5 raster 0x40662900/01, stand-in player-cell.

## 1. Raster envelope header (byte-pinned on real records)

Confirmed from `/tmp/cellstage/raster_6947_40662900.bin` (512² DXT5) +
`raster_ap_5552`/`raster_0` (same layout) + `raster_6948` (fmt 0x15, 256²):
all fields u32 LE.

| off | 6947 value | meaning |
|-----|-----------|---------|
| 0x00 | 1 | version |
| 0x04 / 0x08 | 512 / 512 | width / height |
| 0x0c | 10 | mipCount |
| 0x10 | 8 | **unresolved** (=8 every sample; decoder must NOT rely on it) |
| 0x14 | 0x35545844 | format FOURCC `"DXT5"` (0x15 = luminance records, not DXT5) |
| 0x18 | 0x00040000 | **unresolved** (same in every sample) |
| 0x1c | 0x0000ffff | format-specific (float 1.0 in 0x15 records) |

Envelope = 32 bytes. Then per-layer 16-byte record headers (observed `name[4]`
+ 3 u32, e.g. `"e9D1"`; unresolved) immediately followed by raw DXT5 mip chains. **nPresentLayers is derived, not stored**: `n = (size - 32) / (16 +
chainSize)` where `chainSize = Σ_m ceil(w_m/4)·ceil(h_m/4)·8`, `w_m = max(1,
w>>m)`. Must divide evenly; `payloadOff = 32 + n·16`. Verified on all three 512
DXT5 records: `n=2`, `payloadOff=0x40`, `first block = 20 00 02 00 65 39 00 00`
(valid DXT5: a0=0x20 a1=0x00, c0=0x02 c1=0x6539>>). The 1024² records
(`raster_1`/`_2`) are format 0x15 (luminance, not DXT5) — out of scope.

## 2. Decode plan (python oracle → C++ port)

- **Oracle first** (extend `tools/spore/`): `raster.py` (envelope + nLayers +
  per-mip slice) and `dxt5.py` (2-bit alpha/texel, 6-grad ramp, 5-bit c0/c1,
  4-color pal) already authored against 6947. C++ ports must match the python
  oracle byte-for-byte on the same records.
- **C++ port**: `src/assets/Dxt5.{hpp,cpp}` (pure `decodeDxt5Mip→RGBA8` +
  `dxt5ChainSize`); `src/assets/Texture.{hpp,cpp}` (`parseRaster→ImageRGBA`,
  envelope + nLayers + per-layer decode, picks layer 0).
- **PNG32 (0x2f4e681b) — OUT OF SCOPE for Obj15**: all 1131 records of this DBPF
  type are **RW4 (Ravenwood) containers**, NOT raw PNG. Their first 16 bytes are
  the RW4 magic (`89 52 57 34 77 33 32 00 0D 0A 1A 0A 00 20 04 00`) with ftype
  `0xCAFED00D` ("SPECIAL") and a SkinsInK section (0x70001) — **zero** of 60
  sampled records are raw PNG. The earlier "PNG signature" reading was a
  mis-read of RW4 magic bytes 8–11. Decoding them needs the RW4 container (out
  of Obj15 scope), so `Png32.{hpp,cpp}` is NOT built and **no `find_package(ZLIB)`**
  is required.

## 3. GMDL refCount-BE verification (≥3 records)

Command (reproducible; `dbpf.py` reader + BE/LE at +4): scan `Spore_Content`
gmdl (0x00E6BCE5, ver 8), read `refLE=u32LE@+4`, `refBE=u32BE@+4`.
A record carries refs iff `refLE == (refBE << 24)` (count lives in the high
byte only). Result on the package: **1510 records** match; deterministic 40-rec
strided sample = **13/13 with `refLE==refBE<<24`, 0 violations**; LE walk
breaks on every one (count `0xNN000000` walks off the buffer end). The 3
designated records:

| rec | group/inst | refBE | refLE | walk |
|-----|-----------|-------|-------|------|
| 12  | 0x40627100 / 0x067b0fbc | 5 | 0x05000000 | LE off-end; BE→5×12 refs→meshCount=1 |
| 115 | 0x40646200 / 0x62a5e270 | 9 | 0x09000000 | LE off-end; BE→9×12 refs→meshCount=2 |
| 177 | 0x40656203 / 0x24a7c08a | 2 | 0x02000000 | LE off-end; BE→2×12 refs→meshCount=2 |

Fix (the ~5-line change): `Gmdl.cpp:113` `readU32()` → read the refCount as
big-endian; `gmdl.py` oracle mirrors it. This unblocks the 1510 mis-parses
incl. rec 12 (5 PNG32 refs).

## 4. C++ design (files + IRenderer/B3 seam)

New: `src/assets/Dxt5.{hpp,cpp}`, `Texture.{hpp,cpp}` (responsibilities as §2;
`Png32` dropped — §2). Modify `Gmdl.cpp` (§3). `src/renderer/Renderer.hpp`
gains a textured vertex + texture/material API; `VulkanRenderer` implements it.
`src/assets/Mesh.cpp` gains `toRendererTexMesh` (pos+normal+uv).

**Vertex layout** — new struct (existing `Vertex` left untouched for the
triangle/asset path):
```cpp
struct TexVertex { float pos[3]; float normal[3]; float uv[2]; }; // 32 B
```
Normals/uv present "where present" (GMDL NORMAL/UBYTE4 + TEXCOORD/FLOAT2,
already decoded into `Mesh`); missing normal → (0,0,1), missing uv → (0,0).

**Extend `IRenderer` (B3); do NOT fork a second interface** — B3 is the single
documented backend seam ("referenced, not duplicated"); the textured path is the
same backend, so its upload/draw belongs on the seam, and `NullRenderer` (test
stub) implements the new methods as no-ops (producer + consumer in-tree).
Additive; existing methods unchanged:
```cpp
using TextureHandle = uint32_t;
TextureHandle createTexture(const ImageRGBA &img);      // R8G8B8A8, layer 0
void destroyTexture(TextureHandle t);
MeshHandle createTexMesh(const TexVertex *v, size_t vc, const uint32_t *i, size_t ic);
void drawTextured(MeshHandle m, TextureHandle t, const MaterialState &mat);
```
`MaterialState` is the clean-room descendant of the original `MaterialShader`
id-cache + `CompiledState` slot-binding (RENDERWARE-RESEARCH §9–10; BOUNDARIES
non-boundary N2), re-expressed in OpenSpore terms; a small fixed-function value
(no runtime HLSL — RW9 fixed function):
```cpp
struct MaterialState { uint32_t shaderId; float lightDir[3]; float ambient; };
```

## 5. Shader plan (textured + normal-lit)

**Two pipelines, not one with a flag** — the untextured `triangle`/`asset` path
keeps its `{pos[3],color[3]}` layout + pipeline byte-identical (regression
safety); the textured path needs a different layout that a uniform flag cannot
unify without touching that path. One extra `VkPipeline` + `VkSampler` is the
minimal delta. New GLSL `src/renderer/shaders/lit.{vert,frag}` (build-time
SPIR-V via the existing `glslangValidator` + `embed_spv.py`; `NEAREST`/`CLAMP`,
mip 0 only): vert passes `uv`+`normal` through (CPU-side ortho-fit, as
`asset_view`); frag `c = texture(sampler,uv)·(ambient + max(dot(N,L),0))`,
alpha-blend when `a<255` (the 0x40662900 texture is a black alpha-mask, §6).

## 6. Test plan

- **(a) DXT5 oracle** — python `dxt5_test`: decode 6947 layer0 mip0, assert
  texels `(0,0)=(0,0,0,0)`, `(511,0)=(0,0,0,85)`, `(0,511)=(0,0,0,2)`,
  `(300,200)=(8,0,0,154)`, `sha256[:16]=a7bad32bd7ef8210`, distinct-RGB=2.
- **(b) refCount-BE oracle** — python scan (§3): assert the 3 records'
  `refLE==refBE<<24`, 40-rec sample has 0 violations.
- **(c) `material_smoke` app** — render rec 16594 (or 0x40666202) with its DXT5
  texture → offscreen PPM; assert non-uniform colored pixels AND that the
  textured frame's checksum differs from the flat-shaded `asset_render` baseline.
- **(d) Regression** — `triangle_smoke` + `asset_render` stay green.

## 7. Risks (≤5)

1. **Envelope fields 0x10/0x18/0x1c unresolved** — mitigated: decoder derives
   nLayers from record size (validated on 3 records) and skips the 16-byte layer
   headers; never trusts the unknown words.
2. **DXT5 alpha-palette edge cases** (a0<a1 reverse ramp, 15/14 sentinels,
   non-power-of-2 tail) — mitigated by the byte-for-byte python oracle (§6a).
3. **PNG32 mis-read as raw PNG** — resolved: all 1131 records of type
   0x2f4e681b are RW4 containers, not raw PNG (§2); dropped from Obj15 scope, so
   no PNG decoder / `ZLIB` dependency is built.
4. **Vulkan sampler/pipeline divergence across drivers** — mitigated: `NEAREST`/
   `CLAMP`, mip 0 only; `material_smoke` uses checksums + drawn-count windows,
   not exact pixels, and skips (not fails) when `SPORE/` is absent.
5. **refCount-BE fix regressing the 1273 clean (refs==0) records** — mitigated:
   refs==0 reads identically LE/BE; `assets_real` + `real_asset_test` cover it.
