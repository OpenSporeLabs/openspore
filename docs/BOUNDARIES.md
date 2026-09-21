# Compatibility / Replacement Boundaries (Objective 9, reviewed Obj18)

How OpenSpore subsystems replace original ones piecemeal. Rule:
`original implementation ↔ compatibility boundary ↔ OpenSpore implementation`.
Each boundary below covers only what we have **evidence** for (traced startup
slice, parsed asset path, working renderer). Everything else is an explicit
non-boundary (§5).

Replacement mechanics, stated honestly:

- **Today: independent reimplementation + differential comparison.** OpenSpore
  code never runs inside the original process. "Replacement" means our side
  reproduces observable behavior (bytes, pixels, event order) checked against
  the original as an oracle (Wine runs, package bytes, probe traces).
- **Future: substitution.** Once a boundary is `replaced-verified`
  (see `docs/replacement-status.json`), a caller can link against either side
  without change — proven in-tree by running the same consumer against the
  real provider and a stub (see `testCompatBoundaries`). Live
  DLL-injection-style replacement of code inside `SporeApp.exe` is **NOT**
  the current mechanism and is not planned: the binary is a static EXE with
  no engine DLLs (RECON §4).

## The replacement pattern (applied per subsystem)

Every subsystem goes through the same five steps before its boundary (if any)
is drawn, and `docs/replacement-status.json` tracks where it stands:

1. **Original behavior** — what the original does (SDK names, decompiled
   signatures, asset layout).
2. **Observed semantics** — what we actually saw: probe traces, real record
   bytes, oracle measurements. No trace → labeled INFERRED/APPROXIMATION.
3. **OpenSpore implementation** — clean-room code behind a `docs/BOUNDARIES.md`
   seam (or no seam, while unobserved).
4. **Validation** — differential evidence: oracle byte-match, CTest/Python
   tests, pixel stats. Recorded in the status file's `evidence`/`commits`.
5. **Replaceable subsystem** — the status (`replaced-verified` /
   `replaced-stub` / `approximated` / …) that says whether the seam may be
   trusted for substitution.

Worked example — raster texture: (1) `raster` record type 0x2F4E681C
(RECON/RENDERWARE-RESEARCH §9) → (2) 32-byte envelope + DXT5 blocks confirmed
on 3 real records (MATERIALS-DESIGN §1) → (3) `decodeRasterMips`/`Dxt5` behind
B1 (fetch) and B3 (`createTexture`) → (4) C++ output sha256-prefix-matches the
independent python oracle (`a7bad32bd7ef8210`); the real 0x40662900 is a
near-black alpha mask → (5) `replaced-verified` for decode; the lit pipeline's
light values stay `approximated` (no light data observed).

## B1 — Resource access: `IResourceProvider`

- **File:** `src/compat/ResourceProvider.hpp` (~90 lines, header-only).
- **Semantic responsibility:** fetch record bytes by `(type, group, instance)`
  identity. Nothing about files, compression, or the original resource
  manager leaks through.
- **Original-side evidence:** DBPF v3 layout derived from the 7 real packages
  (`docs/ASSET-PATH.md` stage 1, VERIFIED); `Resource::cResourceManager` +
  `IO` SDK namespace as the load path (RECON §3/§8, INFERRED); probe targets
  `Res::cResourceManager::Initialize` / `DatabasePackedFile::Lock` /
  `PFIndexModifiable::Read` (`tools/observatory/probes/menu_transition.json`,
  defined but not yet traced).
- **OpenSpore status: EXISTS.**
  Producer `DbpfResourceProvider` adapts `src/assets/Dbpf.*`
  (`parseDbpfIndex` + `extractDbpfRecord`, QFS included); stub producer
  `MemoryResourceProvider` stands in for the original side.
  Consumer: `fetchGmdlModel` (`src/compat/MeshSource.hpp`) and the
  `testCompatBoundaries` substitutability loop (same fetch through package
  and stub, byte-identical result).
- **Scope limit:** one package image per provider instance; no cross-package
  priority, no `ResourceManager` caching/registry semantics (those need the
  menu_transition trace — see non-boundary N1).

## B2 — Static mesh supply: `IMeshSource`

- **File:** `src/compat/MeshSource.hpp` (~85 lines, header-only).
- **Semantic responsibility:** parsed model → host `Mesh` (positions, optional
  normals/uvs, indices, bounds) by mesh index. Version quirks, vertex
  declarations, and index widths stay behind the seam.
- **Original-side evidence:** GMDL v8 record walk end-to-end
  (`consumed == 1156` on the real chosen asset, `docs/ASSET-PATH.md`
  stages 3–5, VERIFIED); `RenderWare::Mesh` / `VertexDescription` SDK anchors
  as the original draw-side vocabulary (RENDERWARE-RESEARCH §4/§6, SUPPORTED).
- **OpenSpore status: EXISTS.**
  Producer `GmdlMeshSource` wraps `meshFromGmdl`; models arrive via the B1
  seam (`fetchGmdlModel`), so package-vs-stub is the provider's business.
  Consumer: `submitMeshSource` and the test path stub → model → mesh.
- **Scope limit:** version-8, single-stream, trilist, FLOAT3/UBYTE4/FLOAT2
  only — anything else is a hard error by design. RW4 containers, skins,
  blend shapes, and LOD are non-boundaries (N3).

## B3 — Render submit: `IRenderer` (referenced, NOT duplicated)

- **File:** `src/renderer/Renderer.hpp` (exists since Obj 7; this objective
  adds no new render interface).
- **Semantic responsibility:** lifecycle + upload-one-mesh + begin/draw/end +
  readback. The seam function `submitMeshSource` (MeshSource.hpp) is the only
  new code: transient handle per mesh, upload → draw → release.
- **Original-side evidence:** `Graphics::IRenderer::Get` + manager singletons
  (RENDERWARE-RESEARCH §4, SDK addresses); device-init observable behavior
  (state==2, QPC stamp, §5); per-mesh stream rebind draw path (§6.3);
  `triangle_smoke` + `asset_render` pixel evidence
  (`docs/RENDERER-DESIGN.md`, `docs/ASSET-PATH.md` stage 7).
- **OpenSpore status: EXISTS (stub scope).** Backend is offscreen + WSI
  present: Obj15 added the texture/lit path to the interface (purely
  additive — verified by diff: only new structs/virtuals, no existing method
  touched); Obj17b (8cedc60) added swapchain presentation to the *backend*
  only (`VulkanRenderer` present mode: `initPresent`/`beginPresentFrame`/
  `endPresentFrame`/`resizePresent`) — `IRenderer` itself stayed unchanged
  through the whole cell-stage work. Test consumer: `NullRenderer` in
  `src/assets/tests/assets_test.cpp` proves any `IRenderer` backend accepts
  any `IMeshSource` without Vulkan.
- **Scope limit:** no material or lighting contract in the interface (N2);
  light values live in `MaterialState` and are APPROXIMATION (no light data
  observed).

## What "done" means per boundary

| Boundary | Gate to `replaced-verified` |
|---|---|
| B1 | Real multi-package fetch (all 7 packages indexed, identities from gameplay traces) + `menu_transition` trace showing the original load path firing in the same order. |
| B2 | Second mesh family (version 9 or 32-bit-index asset) through the same seam without interface change; RW4 MODEL decode lands behind `IMeshSource` as a second producer. |
| B3 | Swapchain presentation (DONE, 8cedc60) + one material/lighting behavior matched pixel-wise against the original under Wine (open — no rendered original frame exists to compare). |

## Non-boundaries (UNKNOWN — no interface drawn)

1. **UTFWin message dispatch** (`cEditor::HandleMessage`, message pump
   `FUN_00848210`). Probes defined (`menu_transition.json`) but never run
   under the tracer. **Unlock:** a traced menu→next-screen transition showing
   dispatch order + which resource loads it triggers.
2. **Material / shader / texture contract** (`MaterialShader` id cache,
   `CompiledState` slot bindings, DXT5 rasters, pre-compiled D3D9 bytecode
   groups `0x40212001`–`04`). Researched (RENDERWARE-RESEARCH §9–§10) but no
   in-tree decode. **Unlock:** raster payload decode + one material's
   sampler/shader-id mapping pinned against real bytes.
3. **RW4 container + animation** (sections `0x2000b`/`0x7000b`, skeleton,
   blend shapes, `GameModelAnimData`). Python-oracle only, no C++ port.
   **Unlock:** C++ section walker field-matching the Python oracle on the
   `rw4_11` sample.
4. **Simulator / gameplay systems** (`cSimulatorSystem` + ~16 manager
   singletons, Cell/creature/space stages, `cGameModeManager`). Names only
   (RECON §3/§6). **Unlock:** behavioral trace of a stage transition (mode
   manager calls + frame heartbeat correlation).
5. **Property serialization** (`App::Property*`, 81 SDK functions) and
   **audio/Havok/input** (DSOUND/DINPUT8, `hk*` classes). Names/strings
   only. **Unlock:** a `.prop`-record round-trip (serialize → deserialize →
   compare) for the former; any Wine-observed audio/input call sequence for
   the latter. Pollinator (online service) is additionally a **non-goal**:
   the service is defunct, it will be stubbed, never reimplemented.

## Files

- `src/compat/ResourceProvider.hpp` (new) — B1, used by `MeshSource.hpp`
  and `src/assets/tests/assets_test.cpp`.
- `src/compat/MeshSource.hpp` (new) — B2 + B3 seam, used by the same test
  (`fetchGmdlModel`, `GmdlMeshSource`, `submitMeshSource`).
- `src/assets/tests/assets_test.cpp` (modified) — `testCompatBoundaries` +
  `NullRenderer`: every interface has a producer and a consumer in-tree.
- `docs/replacement-status.json` (new) — machine-readable handoff to Obj 10.
  Obj18 added the cell-sim / interactive / cell-stage-scene entries and the
  `approximated` status; the replacement pattern (§above) governs them.
- `docs/CELLSTAGE-VALIDATION.md` (Obj18) — per-claim differential validation
  of the cell-stage slice, with the evidence labels this file's statuses
  rest on.
