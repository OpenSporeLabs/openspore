# Cell Stage (Obj 16) — smallest playable-cell scene

Offscreen Vulkan scene: soup-water backdrop (two real heightfield patches
with the real DXT5 backdrop raster), a stand-in player cell, and
food/prey objects, from one fixed orbit camera.

## What runs

`build/src/cell_stage SPORE/Data/Spore_Content.package [--input FILE]`

- 512x512 offscreen, no swapchain, no input, deterministic.
- `--input FILE` switches to sim mode (Obj17, see Simulation below).
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

## Simulation (Obj17 part A)

`src/sim/` (static lib `openspore_sim`): a deterministic fixed-dt (1/60 s)
cell simulation — player-cell movement + one interaction + scripted input.
No `time()`, no `rand()`: same entities + input sequence ⇒ same state.

- `Entity` {role, group/inst, pos[3], targetSpan, alive}
- `PlayerState` {pos[3], heading (yaw), vel[3], growMeter}
- `CameraState` — orbit around the player (INFERRED from
  `cCameraManager::SetViewer`; recon §5). `eye = target + dist·(sin yaw·cos
  pitch, sin pitch, cos yaw·cos pitch)`, `dist = baseDist·zoom`.
- `InputFrame` {thrust left/right/forward/back, boost, camera yaw/pitch/zoom}
  + `ScriptedInputSource`: replays a JSON-lines file, one object per line
  `{"frame": N, "keys": ["forward","right","boost"], "yaw": 0.6, "pitch": 0.2,
  "zoom": 0.8}` (hand-rolled parser for this fixed shape, no deps).

### Movement — APPROXIMATION

Constants live in the named `MovementParams` struct (replaceable without
touching the update code). None are observed values (recon §5: movement model
never traced; `cCellModeStrategy::OnKeyDown` confirms thrust-style input only):

| param | value | label |
|---|---|---|
| forwardSpeed | 4.0 u/s | APPROXIMATION |
| strafeSpeed | 2.0 u/s | APPROXIMATION |
| boostMul | 2.0 | APPROXIMATION |
| turnRate | 1.5 rad/s | APPROXIMATION |
| damping | 6.0 (vel → target, exponential, per-frame `1−e` factor) | APPROXIMATION |

Heading convention: `forward = (sin h, 0, cos h)`; h=0 faces +Z, increasing h
turns toward +X. Left/right thrust rotate the heading; target velocity =
forward·fwdSpeed ± right·strafeSpeed (boost scales both); vel damps toward
the target; pos integrates.

### Interactions — INFERRED

Evidence: anim-state DB (recon §5) `Cell_eat_{filter,mand,prob,whole}` and
`Cell_mov_cil(_scared)` + `cCellLootTableResource`/`cCellPopulateResource`
names; mechanics and all numbers INFERRED ("eat smaller, flee bigger").

- **EAT**: live food with `dist(player, food) < eatRadius (3.5)` →
  `food.alive = false`, `growMeter += 1`, event `{frame, "eat", food}`.
- **FLEE**: live prey with `dist < fleeRadius (4.0)` → the player faces
  directly away, thrusts forward (implicit, the "scared" swim states) and
  boosts for that frame; event `{frame, "flee", prey}`.

Dead entities are culled from the render.

### Running it

    build/src/cell_stage SPORE/Data/Spore_Content.package --input script.jsonl

Per frame the scene re-renders (player at its sim position, dead food culled,
camera following); the final frame is written to `cell_stage.ppm` and a
`CELLSTAGE-SIMMANIFEST v1` block is printed: frames, per-frame events, final
player state, camera, clear, pixel stats. Without `--input` the Obj16
fixed-frame behavior is unchanged (regression-safe).

Determinism oracles: CTest `sim_test` (pure C++, CI-safe) and
`tests/test_sim.py` (skip without `SPORE/`): forward thrust moves +Z, zero
input does not move, the eat script emits `eat`/growMeter=1 with the final
PPM differing from a no-eat baseline, and two runs are byte-identical.

## Verification

- CTest `cell_stage` (package as arg, build-dir CWD): all checks +
  calibrated pixel window `content in [60000,115000]` on RADV.
- `tests/test_cellstage.py`: runs the binary twice, asserts the manifest
  is identical; skips without `SPORE/`.
- CTest `sim_test` (pure C++, no package/GPU): movement, eat/flee rules,
  input replay, determinism.
- `tests/test_sim.py`: sim-mode replay determinism + eat/move behavior;
  skips without `SPORE/`.
- Frame sanity: backdrop floor across mid-frame, cell at center,
  food/prey scattered, clear visible in gaps (ASCII downsample).
