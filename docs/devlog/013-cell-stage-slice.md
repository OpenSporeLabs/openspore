# 013 — Cell Stage slice: from one rendered asset to a living window

## 2026-09-21, midday (commit `e0d6230`, 12:05)

State of play: the journal's last chapter on disk ended at the first real *Spore*
asset drawn through the full pipeline — commit `3a52600` (Obj 8), one gmdl record,
27,685 pixels, offscreen. Everything between that commit and this chapter happened
in one working day, 2026-09-21, between 12:05 and 18:41.

The midday commit is small and unglamorous: `e0d6230`, "Obj13: repo sanitation".
Verbose-gated map logging in the tracer, traces defaulting to `/tmp` instead of the
repo, `*.ppm` ignored. Sixteen lines. It matters because the sprint that followed
generated many megabytes of traces and hundreds of test frames, and the repository
had to stay clean while it did.

## Recon: three format findings that shaped everything (`docs/CELLSTAGE-RECON.md`, in `855254b`)

The cell-stage recon surveyed the full 4,209-record gmdl population of
`Spore_Content.package` plus the raster/PNG32/world-object populations, and the
verdict was "decodable today" — with three findings that turned out to be load-bearing:

1. **GMDL `refCount` is big-endian.** gmdl record 12 (group `0x40627100`, 175 KB,
   6,000 tris) read with a little-endian count gives `0x05000000` and the walk flies
   off the record; read big-endian it is 5 refs — all to `0x2f4e681b` — and the walk
   lands exactly on `meshCount`. A 40-record strided sample showed 13/13 with
   `refLE == refBE << 24` and 0 violations. This one field explains most of the 1,510
   records that failed the v8 walk. (VERIFIED: byte-level, two independent reads.)
2. **The raster envelope is a 32-byte header** (`ver, w, h, mipCount`, a `DXT5`
   FOURCC, then per-layer 16-byte headers + raw DXT5 mip chains), with the layer
   count *derived* from the record size — `512² / 10 mips = 349,616 B` divides exact.
   Two header words (`0x10`, `0x18`) are constant across every sample and remain
   semantically unresolved; the decoder ignores them on purpose.
3. **`0x2f4e681b` — the "PNG32" records — are RW4 containers, not raw PNG.** All 1131
   records of that DBPF type begin with the RW4 magic (`89 52 57 34 77 33 32 00 0D 0A
   1A 0A 00 20 04 00`), ftype `0xCAFED00D` ("SPECIAL"), SkinsInK section; zero of 60
   sampled records contain a PNG signature. The earlier "PNG signature" reading was the
   RW4 magic bytes 8–11 mis-read. Consequence: no PNG decoder, no ZLIB dependency — a
   scope line drawn from bytes, not from convenience.

The recon also pinned the **DBPF group scheme** (content family = upper 16 bits
`0x4061–0x406b`; sub-block `+0x0000` metadata, `+0x0001..3` gmdl variants,
`+0x2900..2` textures; *the same instance ID across the whole family* — e.g. gmdl
`0x40666202/03` and raster `0x40662900/01` all share instance `0xd1b4bb56`), the
~73-state **cell animation DB** (`Spore_Game` record 544: `Cell_mov_cil*`,
`Cell_move_jet*`, `Cell_eat_{filter,mand,prob,whole}`, `Cell_death_Player`, mood
states), the SDK names `cCellModeStrategy` (11 functions, vtable @ `0x01485550`) and
`cCameraManager`, and 1,022 undecoded binary world-object records (`0x0f43029a`).

One finding stayed a gap, and it stayed a gap all sprint: **the player-cell model's
identity is UNRESOLVED**. No name↔group map exists in the assets; creatures are
sporemol block assemblies (47 `crt` + 1 `flr` XML records, blockrefs with
group/instance/transform), so the default player cell is one such assembly whose
exact blocks we cannot point at. The slice uses a roundish-bbox stand-in
(`0x40637E02/0x067A0801`, 244 verts) and labels it APPROXIMATION everywhere.

## Materials: the 5-line fix and the lit pipeline (commit `855254b`, 16:10)

The BE fix was the ~5-line change the recon predicted: `Gmdl.cpp` reads the refCount
big-endian, `tools/spore/gmdl/gmdl.py` mirrors it. That unlocked record 12 and, in
aggregate, the 1,510 mis-parses.

Then `src/assets/Dxt5.{hpp,cpp}` (pure `decodeDxt5Mip→RGBA8` + `dxt5ChainSize`) and
`src/assets/Texture.{hpp,cpp}` (`parseRasterEnvelope` + derived `rasterLayerCount` +
`decodeRasterMips`), each ported byte-for-byte from its python oracle in
`tools/spore/dxt5` and `tools/spore/raster`. The C++ decode of the real
`0x40662900` record matches the oracle's sha256 prefix `a7bad32bd7ef8210` —
VERIFIED-DIFFERENTIAL on real bytes.

The renderer grew a *second* pipeline (the untextured `triangle`/`asset` path stays
byte-identical — regression safety over elegance): `lit.{vert,frag}`,
NEAREST/CLAMP, mip 0 only, `c = texel · (ambient + max(dot(N,L),0))` with alpha
blending. `material_smoke` renders the real mesh with the real texture and asserts
non-uniform colored pixels *and* that the frame checksum differs from the flat
baseline.

The honest part: the "texture" is not a texture. The real `0x40662900` raster is a
near-black RGB **alpha mask** (exactly 2 distinct RGB values; mip0 corners
`(0,0,0,0)`/`(0,0,0,85)`, center `(8,0,0,154)`). What looks like a backdrop in the
render is that mask compositing over a teal soup clear — and the clear color is
itself an APPROXIMATION, not game data. The light values in `MaterialState`
(dir `0,0.7071,0.7071`, ambient `0.35`) are likewise APPROXIMATION: no material
light record was decoded, and RW9 is fixed-function only.

## Scene, sim, window (commits `b5e96f0` 16:36, `cf7147a` 17:06, `8cedc60` 18:23)

**Scene (Obj16).** `src/apps/cell_stage.cpp` assembles the smallest playable-cell
scene entirely from real `SPORE/Data` records: two heightfield backdrop patches
(`0x40666202/03`, 1,059/750 verts, textured), the stand-in player cell, two food
objects and one prey (`0x40637E03` family, 79/435/248 verts), an orbit camera
(yaw 35°, pitch 15°, dist 16) whose full view-clip is baked CPU-side per vertex into
NDC — the renderer has no matrix uniforms — and a soup clear. Output: a 512×512 PPM
plus a `CELLSTAGE-MANIFEST v1` block on stdout; two runs must print byte-identical
manifests.

**Sim (Obj17a).** `src/sim/` is a static library with no `time()`, no `rand()`:
fixed dt 1/60 s, `Entity`/`PlayerState`/`CameraState`/`InputFrame`, a named
`MovementParams` struct (all five constants APPROXIMATION — the movement model was
never traced; `OnKeyDown` confirms thrust-style input only), eat-on-proximity
(`dist < 3.5` → food dies, `growMeter += 1`) and flee (`dist < 4.0` → face away,
thrust + boost) as INFERRED semantics from the anim states and the
`cCellLootTableResource`/`cCellPopulateResource` names, and a `ScriptedInputSource`
that replays JSON-lines. `cell_stage --input script.jsonl` re-renders per frame with
the follow camera and prints a `CELLSTAGE-SIMMANIFEST v1`; `sim_test` is pure C++
and checks movement, the eat/flee rules, replay, and two-run byte-identity.

**Window (Obj17b).** `--interactive` opens a real SDL3 + Vulkan window: a vsynced
FIFO swapchain with a present render pass, the same scene, the sim stepped once per
presented frame, scancode-polled keys (WASD/arrows, Shift boost, wheel zoom, ESC).
Measured at 60 fps on the `:0` XWayland session; the KHRONOS validation layer
reported **zero errors** across a 120-frame run. One environmental scar: SDL's
default video-driver auto-probe failed with an *empty* error in this shell even
though a backend worked, so init now tries `default → wayland → x11` and reports the
driver that succeeded. No display → exit 0 with a notice, never a crash (pinned by
`cell_stage_interactive_smoke` with every backend forced to fail).

## Validation and the honest failures (commit `b939cb7`, 18:41)

Obj18 ran the differential pass over the slice (`docs/CELLSTAGE-VALIDATION.md`):
asset identity of every scene record is MATCH-ASSET-BYTES; geometry matches the gmdl
oracle (backdrop 1,059 v / 723 tri, 750 v / 486 tri; the recon's "2169 tri" was the
*index* count); the backdrop raster is VERIFIED-DIFFERENTIAL; the BE refCount claim
is verified on the whole population. Camera, movement, interaction, placement,
light values, and the interactive window itself stay INFERRED / APPROXIMATION /
UNOBSERVED — and the boundary review found **no seam changes needed**: B1–B3 held,
and `replacement-status.json` gained `cell-stage-scene-assembly` (approximated),
`cell-sim-movement-interaction` (approximated) and `interactive-presentation`
(replaced-stub, no differential oracle exists).

Three failures, stated plainly:

- **The Wine oracle yielded 0 events this sprint.** The Obj18 retrace attached
  cleanly (module base `0x400000`, 7 breakpoints, 33.7 s, clean detach, analyzer ran)
  — the pipeline is proven — but the game never reached the main menu inside the
  window, so no probe fired. The latest positive oracle remains `6a41c66` (1,004
  events). Cell-mode traces were never run at all: headless menu navigation is not
  possible (no Xvfb, no synthetic input).
- **SDL3's driver auto-probe is flaky in this shell** (empty error, working backend
  available) — hence the fallback ladder above.
- **Pixel-level rendering is not differentially verified.** No original rendered
  frame exists to compare against; the calibrated content window
  `[60000, 115000]` was measured on our own RADV render and is self-referential.

### Outcome

| | |
|---|---|
| **Proven** | First interactive vertical slice: real gmdl + real DXT5 backdrop + stand-in cell + food/prey, live 60 fps window, keyboard-driven, 0 validation errors |
| | GMDL refCount-BE: 5-line fix, verified on 3 named records + 40-record sample (0 violations), explains the 1,510 walk-fails |
| | Raster 32B envelope + DXT5 decode: VERIFIED-DIFFERENTIAL vs python oracle on real bytes (sha256 `a7bad32bd7ef8210`) |
| | PNG32 = RW4 containers (60/60 sampled) — scope line drawn from bytes, no ZLIB dependency |
| | DBPF group scheme (family/sub-block/same-instance) confirmed byte-level |
| | Determinism: two runs byte-identical (manifest + PPM); `sim_test` pure-C++ and CI-safe |
| | Boundaries B1–B3 held unchanged across the slice (Obj18 review) |
| **Open** | Player-cell identity UNRESOLVED (no name↔group map; sporemol block assembly only) |
| | Movement dynamics UNOBSERVED — all five `MovementParams` constants APPROXIMATION; no trace exists |
| | Raster header words `0x10`/`0x18` semantically unresolved (constant, safely ignored) |
| | 1,022 world-object records (`0x0f43029a`) undecoded → placement hard-coded |
| | Cell-mode runtime trace never run; Wine retrace 0 events; `menu_transition` probes never run |
| | 0 gmdl records with 32-bit indices or v9 observed; v9 layout not decoded |

Next: the second vertical slice — creature-creator block assembly (sporemol XML →
block gmdl placement) or a cell-mode runtime trace via Xvfb, plus resolving
player-cell identity (`docs/STATE.md` §6). Back: [chapter 005](005-deterministic-tests.md)
(the last chapter on disk; chapters 006–012 exist in the index only).
