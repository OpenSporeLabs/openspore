# Cell Stage (Obj 16) — smallest playable-cell scene

Offscreen Vulkan scene: soup-water backdrop (two real heightfield patches
with the real DXT5 backdrop raster), a stand-in player cell, and
food/prey objects, from one fixed orbit camera.

## What runs

`build/src/cell_stage SPORE/Data/Spore_Content.package`

- 512x512 offscreen, no swapchain, no input, deterministic.
- Writes `cell_stage.ppm` next to the CWD and a
  `CELLSTAGE-MANIFEST v1` block on stdout (entities, camera, clear,
  pixel stats). Two runs must print byte-identical manifests.
- Skips (exit 0, `cell_stage: SKIP ...`) when the package is absent.

## Entities (all real `SPORE/Data` records; see `docs/CELLSTAGE-RECON.md`)

| role        | group / inst       | verts | notes |
|-------------|--------------------|-------|-------|
| backdrop_a  | 0x40666202 / 0xD1B4BB56 | 1059 | textured |
| backdrop_b  | 0x40666203 / 0xD1B4BB56 | 750  | textured |
| player_cell | 0x40637E02 / 0x067A0801 | 244  | flat stand-in (APPROXIMATION) |
| food_a      | 0x40637E03 / 0x067CEDE8 | 79   | flat |
| food_b      | 0x40637E03 / 0x067CEDEA | 435  | flat |
| prey_c      | 0x40637E03 / 0x067CEDFB | 248  | flat |

Backdrop raster `0x40662900/0xD1B4BB56`: 512x512 DXT5, near-black RGB +
alpha mask; the lit pipeline's alpha blend composites it over the teal
clear (soup water `(26,89,107)` — APPROXIMATION, not game data).

## Camera / projection

Orbit: yaw 35 deg, pitch 15 deg, dist 16, target (0,-1,0), fov 60 deg,
near 0.5, far 100. The renderer has no matrix uniforms, so the full
view-clip is baked CPU-side per vertex into NDC ([0,1] depth, w-divide
applied; w<=0 pushed past depth range).

## Verification

- CTest `cell_stage` (package as arg, build-dir CWD): all checks +
  calibrated pixel window `content in [60000,115000]` on RADV.
- `tests/test_cellstage.py`: runs the binary twice, asserts the manifest
  is identical; skips without `SPORE/`.
- Frame sanity: backdrop floor across mid-frame, cell at center,
  food/prey scattered, clear visible in gaps (ASCII downsample).
