# Cell Stage Recon (Obj14)

Evidence labels: CONFIRMED (bytes/assets seen) / INFERRED (multiple sources) /
APPROXIMATION (unobserved, guessed). GOG layout note: assets live in `SPORE/Data/`,
**not** `SPORE/SporeBin/` (exes only). GhidraMCP headless was down → SDK symbol
evidence taken from `SporeGhidra_march2017.xml` + `docs/analysis/vtables.json`.

## 1. Asset inventory

| Package | Size | Role | Cell-stage content |
|---|---|---|---|
| `Data/Spore_Content.package` | 995 MB, 17119 rec | models + textures + creature DB | 4209 gmdl, 2954 raster, 1131 PNG32, 1709 bem, 1631 summary, 1641 pollen_metadata, 1162 prop, 1022 world-obj (0x0f43029a) |
| `Data/Spore_Game.package` | 20 MB, 11529 rec | configs, sporemols, anim DBs | 47 sporemol `crt` (base creatures), 1 `flr` sporemol, cell anim DB (rec 544, 0x9b8e862f), 2091 0xee17c6ad configs, 47 anim `crt`-family |
| `Data/Spore_Graphics.package` | 943 MB, 24707 rec | UI | 8360 png, 2422 `gmsh`, 394 0x0250fe9a — no cell assets found |
| `Data/Spore_Pack_03.package` | 9.6 MB | booster pack | 46 gmsh, 24 bem — not cell |
| `DataEP1/*` | EP1 | 317 gmdl etc. | not needed for slice |

**DBPF group scheme (CONFIRMED, byte-level):** content family = upper 16 bits
(0x4061–0x406b observed); within a family, sub-block `+0x0000` = metadata
(prop/summary/pollen/bem), `+0x0001..0x0003` = gmdl variants, `+0x2900..0x2902` =
textures; **same instance ID across all of them** (e.g. gmdl 0x40666202/0x40666203,
raster 0x40662900/0x40662901, all inst 0xd1b4bb56). Resource paths do NOT exist in
DBPF — only build paths inside animation configs (`Data\Creatures\Animations\_final\cell\...`)
and the opaque group IDs. 131 Spore_Game config records reference `_final\cell\`.

## 2. Geometry (full survey of 4209 Spore_Content gmdl)

- All parseable gmdl are **version 8, u16 indices** (2699 parsed; 1510 fail the walk;
  1273 fully clean under the current v8/static/single-stream/trilist-only criteria;
  0 with 32-bit indices, 0 with refs>1... except the finding below).
- Clean set spans 32–21,279 verts / 20–13,748 tris (scan: `/tmp/cellstage/gmdl_scan.jsonl`).
- **NEW FORMAT QUIRK (CONFIRMED):** GMDL header `refCount` is **big-endian u32**.
  gmdl rec 12 (0x40627100, 175 KB, 6000 tris): LE read → 0x05000000 (garbage); BE read
  → 5 refs, all to 0x2f4e681b (PNG32), and the walk lands exactly on meshCount.
  `tools/spore/gmdl/gmdl.py` (and `src/assets/Gmdl.cpp`) assume LE → mis-parse any
  gmdl with refs>0 (the 1510 "bad" rows are mostly this + v9).
- Candidates that decode cleanly today:
  - rec 15/16 (0x40666202/03, inst 0xd1b4bb56): 1059 v/2169 tri and 750 v/1458 tri,
    material 0xd7be35f9, 2-sampler texset → **KG says these are heightfield patches**
    (grid topology) = environment terrain, NOT a creature.
  - rec 16594 (0x40637e03) — the Obj8 ASSET-PATH model, already rendered to pixels.
  - rec 12 (0x40627100): 6000 tris, 5 PNG32 refs — the largest clean creature-scale mesh found.
- **Player-cell model identity: UNRESOLVED** (no name↔group map exists in assets).
  INFERRED: cell creatures are assembled from *blocks* via sporemol XML (see §4); the
  default player cell is one such assembly, its exact group unknown.

## 3. Textures / materials

- `raster` (0x2f4e681c, 2954): envelope `ver=1, w, h, mipCount, nLayers, [layer recs]`
  (~64–88 B header) wrapping **DXT5 blocks** — 512×512/10 mips = 349,616 B exact
  (CONFIRMED by size math + first block valid DXT5: alpha bytes 0x85 0x00, c0/c1 0x00);
  1024×1024 variant = 1,398,164 B.
- `0x2f4e681b` (1131): **RW4 (Ravenwood) containers** — NOT raw PNG. First 16 B are
  the RW4 magic (`89 52 57 34 77 33 32 00 0D 0A 1A 0A 00 20 04 00`), ftype
  `0xCAFED00D` ("SPECIAL"), SkinsInK section. Zero of 60 sampled records are raw PNG
  (the earlier "PNG signature" was RW4 magic bytes 8–11). Decoding needs the RW4
  container — out of Obj15 scope.
- `png` (0x2f7d0004, 1642 in Content, 8360 in Graphics): UI.
- Materials: gmdl `materialID` + `materialInfos` (shader 0x210 = 20 B ShaderData,
  texset 0x20D with per-sampler {inst,grp} texture refs). No runtime HLSL (RW9 fixed
  function) — CONFIRMED from RENDERWARE-RESEARCH. Channel layout needed: DXT5→RGBA8
  (A8R8G8B8) and PNG RGBA.

## 4. Scene / environment

- **No scene/level files found** (no `.gmdl` scenes, no "cell world" package entries;
  "cell" appears only in anim configs) — INFERRED: environment is code-generated.
- 1022 binary world-object records (type 0x0f43029a, 1.8–24 KB each: counts, GUIDs,
  3×vectors, floats, 0x1234 seed) — CONFIRMED they exist; INFERRED they are the
  cell-soup object placement/population data.
- 1 `flr` + 47 `crt` records = **sporemol XML** (`<sporemodel>`: blockrefs with
  blockid group/inst, transforms, muscle scales, skin colors; e.g. `paintBuddy`
  references blocks 0x40666000/0xf80fc958 + 0x40626000/0xa077208c) — CONFIRMED:
  creatures are block-assembled, not monolithic meshes.
- Heightfield patches (gmdl 0x4066620x family, 153 per sub-block × 4 sub-blocks)
  CONFIRMED = the soup's terrain/water surface pieces.
- SDK resources for the stage (CONFIRMED names in SDK XML): `Simulator::Cell::
  cCell{World,BackgroundMap,Populate,LootTable,LookTable,LookAlgorithm,EffectMap,
  Powers,Structure,RandomCreature,Globals}Resource` + `cCellGame/cCellGFX/cCellUI/
  cCellMission/cCellObjectData/cCellSerializableData/cCellScaleInfo` — the stage is
  data-driven off these resources (their binary records not yet located).

## 5. Behavior (evidence-backed)

- `App::cCellModeStrategy` — 11 fns, vtable @0x01485550 (CONFIRMED via vtables.json):
  Initialize/Dispose/OnEnter/OnExit/OnKeyDown/OnMouseMove/OnMouseDown/OnMouseUp/
  OnMouseWheel/Update → input: keyboard + mouse incl. wheel (INFERRED: orbit/zoom camera).
- `App::cCameraManager` — 3 fns: HandleMessage, SetActiveCameraByID, SetViewer (CONFIRMED names).
- Cell anim state DB (Spore_Game rec 544, CONFIRMED text): ~73 states —
  move: `Cell_mov_cil(_big|_mad|_scared)`, `Cell_mov_flg...`, `Cell_move_jet(_blink)`,
  `cilia_movement`, `jet_movement`, `Flagella`; eat: `Cell_eat_{filter,mand,prob,whole}
  (_fail|_npc|...)`; damage: `Cell_takedmg_{elec,poison,stab}`, `Cell_dmgsolid_{death,mand,spike}`;
  defense: `Cell_{glance,puncture}_spike`, `Cell_roar`; death: `Cell_death_{eaten,Player,npc}`;
  mood: `Cell_{idle,npc_mad,npc_scared,poked,bubblepop,grow,hatch}`;
  channels `EyeCell`, `MoveCell`, `MouthCell`, `cell_electro` (CONFIRMED in anim configs).
- Movement model (speeds, cilia vs jet dynamics): **APPROXIMATION** — never traced;
  RECON marks `Simulator::Cell` (26 fns) HYPOTHESIS (names only, no decompilation).
- Eating/interaction: anim + `cCellLootTableResource` + `cCellPopulateResource` names
  CONFIRMED; mechanics INFERRED (eat smaller, flee bigger; no observed numbers).

## 6. Output model

```
Cell Stage slice needs:
    Asset A  gmdl rec 16594 (Spore_Content 0x40637e03/0x067a07f0)  — decodes+renders today (Obj8)
    Asset B  gmdl rec 15/16 (0x40666202/03, 0xd1b4bb56) heightfield patches — decodes today
    Asset C  gmdl rec 12 (0x40627100, 6000 tri, 5 PNG32 refs) — decodes after refCount BE fix
    Asset D  player-cell stand-in model — UNRESOLVED identity; any clean rounded gmdl (see §2)
    Material M  id 0xd7be35f9 / 0x407dfddb, shader 0x210 (20B ShaderData, fixed-function) — INFERRED params
    Texture T1  raster 0x40662900/01 (512^2 DXT5, 10 mips) — needs DXT5 decoder + envelope RE
    Texture T2  0x2f4e681b (rec 12 refs; 4.9–7 KB) — RW4 container, NOT raw PNG; needs RW4 decode (out of Obj15 scope)
    World W   2–3 x 0x0f43029a records (object placement) — INFERRED layout
    Camera C  orbit + follow, mouse-wheel zoom — INFERRED (cCellModeStrategy OnMouseWheel; no trace)
    Movement M  3D swim, cilia/jet states — APPROXIMATION (no observed values)
    Interaction I  eat smaller / flee bigger — INFERRED (anim states + loot/populate resources)
```

## 7. Feasibility verdict

Decodable with existing tooling **today**: all 1273 clean gmdl (incl. A/B above),
DBPF+QFS, the Obj8 render path.

Gaps blocking a textured, populated slice (in effort order):
1. GMDL `refCount` big-endian fix — oracle `gmdl.py` + `src/assets/Gmdl.cpp` (~5 lines;
   unlocks the 1510 mis-parses, rec 12 included).
2. DXT5 decoder → RGBA8 (~50 LOC) + raster envelope header (~80 B RE; 2 samples suffice).
3. `0x2f4e681b` decode — found to be **RW4 containers, not raw PNG** (out of Obj15
   scope); needs the RW4 container reader first.
4. World-object record layout (0x0f43029a) — needed for placement; optional for a
   minimal slice (hard-code 3 positions as APPROXIMATION).
5. 32-bit indices / v9 / skins — **none observed in content** (0 records); no gap.

**Recommended minimal asset set for the slice:** A + B + T1 (DXT5) + stand-in D +
hard-coded placement. This renders a cell-shaped model in a soup terrain with a real
texture, all from clean-room-decoded game data.

## Orchestrator decisions
1. **Player-cell model identity** — no asset↔name map exists; pick a clean rounded
   gmdl as stand-in (or spend a trace session on `cCellModeStrategy::OnEnter` to get it).
2. **Do we take the 5 gaps in order** (§7), i.e. is DXT5+PNG decode in scope for Obj15?
3. **Behavior source**: Wine trace of cell mode (blocked per STATE.md §5: no Xvfb,
   menu_transition never run) vs. APPROXIMATION movement now + trace later.
4. Confirm gmdl refCount BE (single-package evidence; cheap to re-verify on 2 more
   records before changing the C++ walker).
