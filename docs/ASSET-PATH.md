# Asset Path 8a — First Real Geometry in OpenSpore

## Chosen asset

| Field | Value |
|---|---|
| Package | `SPORE/Data/Spore_Content.package` (git-ignored; read at test time only) |
| Record index | 16594 (lookup is by identity, not index) |
| Type / group / instance | `0x00E6BCE5` (gmdl) / `0x40637E03` / `0x067A07F0` |
| Stored / decompressed | 794 bytes QFS-compressed / 1156 bytes |
| GMDL version | 8, `meshCount` 1 |
| Geometry | 32 vertices (stride 24), 60 u16 indices = 20 triangles, `primType` 4 (triangle list) |
| Vertex layout | `POSITION/FLOAT3 @0`, `NORMAL/UBYTE4 @12`, `TEXCOORD0/FLOAT2 @16` |
| Material | id `0x407DFDDB`; trailer holds a 3-sampler texture set + shader `0x210` |
| File bbox / radius | min `(-6.5094, -3.3870, 0.0813)`, max `(3.2452, 6.4511, 11.8162)`, r `13.7738` |
| Vertex-derived bbox | min `(-2.0701, 0.1391, 0.0813)`, max `(-0.3715, 2.1643, 5.3262)` |

Why this one: it is the **smallest geometry-bearing** gmdl in `Spore_Content`
(1156 bytes decompressed). The only smaller gmdl (index 1006, 80 bytes — the
subject of `tests/expected/real_gmdl_1006.json`) has `meshCount` 0 and no
buffers at all, so it cannot yield geometry. The chosen record's full decode
path uses only documented codes (declTypes 2/5/1, usages 0/3/5, prim 4,
shader ids `0x20D` + `0x210`), parses end-to-end (`finalOffset == fileSize`),
and is self-contained: one mesh, no bone ranges, no anim data, and no
texture is needed to show the shape (see the color mapping below).

## Stage-by-stage decode

1. **DBPF v3 index** (`src/assets/Dbpf.cpp:parseDbpfIndex`): 96-byte header
   (`DBPF`, major 3, index count/offset at `0x24`/`0x40`), flags word, then
   28-byte rows `{type, group, instance, offset, storedSize&0x7FFFFFFF,
   memSize, comp, saved, pad}`. The row is found by
   `(type, group, instance)` identity.
2. **QFS decompress** (`qfsDecompress`): `10FB` magic + 3-byte big-endian
   decompressed size, then LZ control-byte tokens (literals + back-refs).
   Output must equal the index `memSize` (1156), else the record is rejected.
3. **GMDL walk** (`src/assets/Gmdl.cpp:parseGmdl`): version → refs (0) →
   `meshCount`, bbox, radius → index buffers → vertex descriptors (12-byte
   D3DVERTEXELEMENT entries) → vertex buffers → mesh refs + material IDs →
   material-info trailer (texture set `0x20D` decoded, other shader ids
   skipped by size table) → bone ranges (0) → anim datas (0) →
   `unknownKey`. The parse **fails** unless the final offset equals the
   record size.
4. **Mesh extract** (`src/assets/Mesh.cpp:meshFromGmdl`): stride =
   max(end offsets) = 24; positions copied as `FLOAT3`, normals as
   `UBYTE4/255`, uvs as `FLOAT2`; u16 indices widened to u32 and
   range-checked against the vertex count. Only stream 0, trilist, and the
   three element kinds above are accepted — anything else is an error.
5. **Bounds** (`computeMeshBounds`): bbox from positions; radius = max
   distance from the bbox center.
6. **Renderer verts** (`toRendererMesh`): `Vertex{pos, color}` per vertex,
   indices passed through as u32.

## Color mapping (visualization choice, not original behavior)

- Normals present (this asset): `color = normalBytes / 255`. The UBYTE4
  normal encoding semantics are *not* claimed — the bytes are shown
  uninterpreted so the mesh renders unlit with deterministic per-vertex
  color (e.g. first vertex `(230,107,59) → (0.902, 0.420, 0.231)`).
- No normals (synthetic path): deterministic height ramp over Y
  (low = steel blue `(0.15,0.30,0.65)`, high = ember `(0.90,0.55,0.20)`).

## Evidence level per stage

| Stage | Level | Basis |
|---|---|---|
| DBPF header/index/extent | VERIFIED | C++ parse of the real package index finds the row with stored 794 / mem 1156; synthetic 2-row fixture test |
| QFS decompression | VERIFIED | C++ output is 1156 bytes and parses end-to-end; synthetic `ABCD` literal-run round-trip + determinism check |
| GMDL field walk | VERIFIED | `consumed == 1156`, version 8, counts and material id asserted against the real record; synthetic triangle fixture |
| Vertex/index arrays | VERIFIED | 32×24 = 768 and 60×2 = 120 byte extents; index range 0..31; first-vertex spot check |
| File bbox/radius values | VERIFIED | Asserted to 1e-3 against the real record (metadata, see note) |
| Computed bounds | SUPPORTED | Derived deterministically from decoded verts; asserted to 1e-3. NOTE: the geometry bbox is *tighter* than the file bbox (file box likely covers LOD/morph range, not just these 32 verts) |
| Normal→color mapping | INFERRED | UBYTE4 shown as-is; true normal decode (signed? scaled?) unknown — visualization only |
| Texture set / material | SUPPORTED | Skipped over by size (framing validated by end-offset match); sampler contents not interpreted |

## Gaps (NOT understood, left for later)

- What group `0x40637E03` names (FloraModels-adjacent by survey, unconfirmed).
- True UBYTE4 normal encoding (raw vs. biased/scaled).
- The file bbox being larger than the vertex bbox (LOD headroom vs. morph targets — undecided).
- GMDL version 9 framing, 32-bit index buffers, non-trilist prims, non-zero
  streams: all rejected by the walker, none observed in this asset.
- Full RW4 container walking: out of scope — this asset is a flat gmdl
  record and needs no RW4 section walk.

## Stage 7 — render (Objective 8b, `src/apps/asset_view.cpp`, ctest `asset_render`)

- **Transform (CPU-side, not push constants):** the pipeline is a fixed
  passthrough shader with no uniforms, so the orthographic fit is baked
  into the uploaded vertices — zero Vulkan-code change vs. adding a
  push-constant layout + shader recompile. From the runtime geometry
  bbox (spanX 1.6985, spanY 2.0251, spanZ 5.2448): uniform scale
  `s = 1/max(spanX,spanY) = 0.4938`, center `(cx,cy) = (-1.2208,1.1517)`;
  `ndcX = (x-cx)*s`, `ndcY = -((y-cy)*s)` (Y-flip so model +Y is
  screen-up), `ndcZ = ((z-minZ)/spanZ)*0.5` (depth order kept, inside
  `[0,1)`). Largest screen span is 1.0 NDC = 50% of the viewport.
- **Viewport/evidence (512×512, clear black, RADV/NAVI31):** 27685 drawn
  pixels (`r+g+b > 24`) vs 234459 background; drawn bbox 214×256 px at
  x 149–362 / y 128–383; center-of-mass (241.3, 245.7); drawn mean
  (154.6, 112.5, 37.7), background mean (0, 0, 0); bit-identical across
  runs. No C++ vs Python oracle mismatch (first-vertex pos + color
  re-asserted at runtime).
- **Asserts:** 32 verts / 60 idx re-checked at runtime; drawn count must
  lie in [19380, 35990] (measured ±30%). Skips gracefully when `SPORE/`
  is absent. `asset.ppm` is written to the build dir only — no images in git.
