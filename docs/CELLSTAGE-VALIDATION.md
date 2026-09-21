# Cell Stage — Differential Validation (Obj18)

Validates the Cell Stage slice (Obj15–17, commits 855254b, b5e96f0, cf7147a,
8cedc60) against known original semantics. Status vocabulary:
VERIFIED-DIFFERENTIAL (C++ matches an independent oracle on real bytes) /
MATCH-ASSET-BYTES (decoded from the same real record bytes as the oracle) /
INFERRED-SEMANTICS (named original constructs, semantics reconstructed) /
APPROXIMATION (unobserved values, guessed) / UNOBSERVED (no evidence at all).

| claim | original evidence | OpenSpore impl | status |
|---|---|---|---|
| Asset identity of every scene record (6 gmdl + 1 raster group/inst in `cell_stage.cpp:99`) | CONFIRMED bytes: records extracted from `Spore_Content.package` index by (type, group, inst); recon §1–§2 (DBPF v3 layout VERIFIED) | `parseDbpfIndex` + `findDbpfEntry` + `extractDbpfRecord` (src/assets/Dbpf.cpp); manifest prints every identity | MATCH-ASSET-BYTES |
| Geometry: verts/tris of scene meshes vs gmdl oracle | python oracle `gmdl.py inspect` on extracted records: rec15 = 1059 v / 2169 16-bit indices (recon §2's "2169 tri" is the index count), rec16 = 750 v / 1458 idx | manifest: backdrop 1059 v/723 tri (=2169 idx/3), 750 v/486 tri (=1458 idx/3); player 244, food 79/435, prey 248 (cell_stage.cpp:99 `expectVerts`) | MATCH-ASSET-BYTES |
| Texture: 32B raster envelope + DXT5 decode of 0x40662900 | python oracle `tools/spore/raster` + `dxt5` (Obj15): 512²/10 mips, 2 layers; mip0 corners (0,0,0,0)/(0,0,0,85), center (8,0,0,154), 2 distinct RGB values — the real raster is a near-black RGB **alpha mask** | `decodeRasterMips` + `decodeDxt5Mip` (src/assets/Texture.cpp, Dxt5.cpp); cell_stage checks sha256[0:16]=`a7bad32bd7ef8210` == oracle | VERIFIED-DIFFERENTIAL |
| Lit-pipeline light values (dir 0,0.7071,0.7071; ambient 0.35) | NONE — no material light record decoded; RW9 fixed-function only (RENDERWARE-RESEARCH §10) | `MaterialState` (src/renderer/Renderer.hpp), lit.frag | APPROXIMATION |
| Camera semantics: orbit + follow + wheel zoom | INFERRED: `cCameraManager` (SetViewer/SetActiveCameraByID), `cCellModeStrategy::OnMouseWheel/OnMouseMove` names CONFIRMED (recon §5, vtables.json); no trace | `CameraState` orbit math (src/sim/Sim.hpp:51), follow in cell_stage.cpp:669/958; wheel zoom ±1.1 clamped [0.4,3.0] | INFERRED-SEMANTICS |
| Movement: thrust/strafe/boost/turn + exponential damping constants | NONE observed — recon §5: movement model never traced; `OnKeyDown` confirms thrust-style input only; cilia/jet anim states exist (`Cell_mov_cil*`, `Cell_move_jet*`) | `MovementParams` (Sim.hpp:79): 4.0 u/s fwd, 2.0 strafe, 2.0 boost, 1.5 rad/s, damping 6.0 — all named, replaceable | APPROXIMATION |
| Interaction: eat-on-proximity (radius 3.5) + growMeter; flee (radius 4.0) | INFERRED: `Cell_eat_{filter,mand,prob,whole}` states + `cCellLootTableResource`/`cCellPopulateResource` names CONFIRMED (recon §5); no observed values | `CellSim::update` eat/flee rules (src/sim/Sim.cpp); radii INFERRED, "eat smaller / flee bigger" | INFERRED-SEMANTICS |
| GMDL v8 record layout incl. **big-endian refCount** | VERIFIED on the 4209-record Spore_Content gmdl population (recon §2: 2699 parsed, 1273 fully clean, 1510 walk-fails = BE refCount + v9); 3 named BE records + strided 40-record sample, 0 LE/BE violations (tests/test_textures.py) | `parseGmdl` refCount BE (src/assets/Gmdl.cpp, Obj15) | VERIFIED-DIFFERENTIAL |
| Raster envelope 32B header | VERIFIED on 3 real records (MATERIALS-DESIGN §1: 512² DXT5 ×3; layout + `nLayers` derivation divide-exact). **Unresolved: word 0x10 (0x08 in all samples) and 0x18 (0x00040000 in all samples)** — decoder derives layer count from size and never trusts them | `parseRasterEnvelope`/`rasterLayerCount` (src/assets/Texture.cpp) | MATCH-ASSET-BYTES |
| Scene placement: entity positions, world layout | UNOBSERVED — 1022 world-object records (0x0f43029a) exist but are not decoded; no scene files found (recon §4) | hard-coded positions (cell_stage.cpp:99) | UNOBSERVED |
| Player-cell model identity | UNOBSERVED — no name↔group map exists in assets (recon §2: sporemol block-assembly only) | stand-in 0x40637E02/0x067A0801 (roundish bbox pick) | UNOBSERVED |
| Interactive presentation (live window, vsync, keyboard) | UNOBSERVED — no trace of original interactive behavior (no headless menu navigation) | SDL3+Vulkan swapchain (cell_stage.cpp:752); smoke: no-display exit 0, 0 validation-layer errors over 120 frames | UNOBSERVED |

## Runtime oracle status (this objective)

`probe_tracer --launch wine SporeApp.exe` (main_menu probes, --duration 30):
**COMPLETED, no stall** — tracer attached, found the module (base 0x400000),
set 7 breakpoints, ran 33.7 s, detached cleanly. **0 events recorded**: the
game did not reach the main-menu state inside the window, so no probe fired.
Latest positive oracle evidence remains Obj6.1's 1004-event main_menu trace
(6a41c66). Cell-mode traces were **never run** (no menu navigation possible
headless) — every camera/movement/interaction row above stays INFERRED/
APPROXIMATION until a trace session exists.

## Honest limitations

- **Wine oracle currently yields no events.** The 30 s window ended before the
  game reached the main menu (slow/failed boot in this session). Not chased
  further per objective scope; the pipeline itself is proven (attach, module
  discovery, breakpoints, clean detach, analyzer ran).
- **Cell mode is unobservable headless.** No Xvfb/menu path; original cell
  dynamics, camera values, eat/flee radii, and light/material params are all
  unobserved by construction.
- **Pixel-level rendering is not differentially verified.** No original
  rendered frame exists to pixel-match; the calibrated content window
  ([60000,115000]) is self-referential (measured on our own RADV render).
- **gmdl population:** the 1510 walk-failing records are explained in aggregate
  (BE refCount + v9), not record-by-record; v9 layout itself is not decoded.
- **Raster envelope:** header words 0x10 and 0x18 remain semantically
  unresolved (constant across samples; safely ignored by the decoder).
- **1022 world-object records (0x0f43029a)** are confirmed to exist but
  undecoded — scene placement stays hard-coded APPROXIMATION/UNOBSERVED.
