# Cell Stage Completion — Reconstruction Campaign

**Status: PROPOSAL.** Generated from static evidence only; no runtime trace is
required to build. Evidence vocabulary per `docs/RE-DOSSIER-SCHEMA.md`
(UNKNOWN < APPROXIMATION < INFERRED < SUPPORTED < OBSERVED < CONFIRMED < VERIFIED).
Build: SporeApp.exe **3.1.0.22** (GOG), image base `0x00400000`.

**Wave 1 (static decode unblockers): COMPLETE 2026-09-23.** CS-01, CS-02, CS-03,
CS-04 all DONE and verified against the binary (differential tests pass; KG records
`cs01_plane_constants`, `cs02_worldobj_header`/`cs02_worldobj_entries`,
`cs03_cellserializer_core`/`cs03_globals_record`, `cs04_rw4_port` = pass).
Next: Wave 2 (cell resource decodes CS-05…CS-12, all build on CS-03).

---

## 1. Objective

Promote the existing cell-stage slice (`src/sim/` + `src/apps/cell_stage.cpp` +
`src/replace/`) from an approximated stand-in scene to a real, playable cell stage
with genuine assets and decompiled-faithful behavior.

**Definition of done** (all static-evidence based):
1. Movement plane constants read from the binary — no APPROXIMATION left in steering.
2. Scene content (placement, cell models, background) sourced from decoded game
   records, not hard-coded tables.
3. Player cell identity resolved from records (the rejected building stand-in is gone).
4. Sim core (cell game state, pool, object creation, advect, damage, attack rules)
   implemented per decompilation, replayed by the frozen contract
   (`cell-sim-contract/2`).
5. Mode-strategy lifecycle + input mapping formalized for reuse by creature/space
   stages.
6. Every decode differential-verified against its python oracle; every sim behavior
   against the contract fixtures; double-run byte-identical.

**Not done** (explicitly out of scope, gated): S5 human-watched runtime trace and the
`replaced-approx` → `replaced-verified` promotion it unlocks (CS-32).

---

## 2. Current state (what exists and is proven)

| Piece | Location | Status |
|---|---|---|
| Deterministic sim (thrust/eat-flee/scripted replay) | `src/sim/Sim.cpp` (356 L) + `Sim.hpp` (254 L) | replaced-approx (movement), contract `cell-sim-contract/2` (plane constants now VERIFIED from the binary, CS-01) |
| Contract tests | `src/sim/tests/{contract_scenarios.hpp,sim_contract_test.cpp,sim_test.cpp}`, `tests/test_sim.py`, `tests/fixtures/cell/` | CI-safe, deterministic (byte-identical PPMs) |
| Scene app | `src/apps/cell_stage.cpp` (1,201 L) | real gmdl + DXT5 backdrop; **positions + player identity + clear color are APPROXIMATIONS** (hard-coded table at :101–114) |
| Replacement hook | `src/replace/{Replace.hpp,Reference.cpp,CellGameView.hpp}` + `tests/diff_test.cpp` | 64/64 differential match (`docs/REPLACEMENT-DIFF.md`) |
| Asset readers | `src/assets/{Dbpf,Gmdl,Texture,Dxt5,Mesh}.cpp` | Dbpf/Gmdl replaced-verified; raster supported |
| Decoders | `tools/spore/{dbpf,gmdl,raster,dxt5}/` + `rw4/rw4.py` (detection only) + `asset_resolver.py` + `types/{type,group}names.json` | python oracles for C++ porting |
| Knowledge | KG `knowledgegraph/spore.db` (65,461 nodes); 37 decompiled Cell functions in `.spore-analysis/ghidra-exports/decompiled_sdk/`; 13 SDK headers in `~/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/Cell/` + `App/cCellModeStrategy.h`; dossier `docs/analysis/dossiers/cell-movement.md` | complete for static work |

---

## 3. Evidence base (all addresses verified against `functions.tsv`, 3.1.0.22)

### 3.1 Decompiled functions (37 Cell files)

| Address | Function | Size (B) |
|---|---|---|
| 00e4ce20 | `Simulator::Cell::GetGlobalsData` | 18 |
| 00e51010 | `App::cCellModeStrategy::OnMouseMove` | 26 |
| 00e54270 | `Simulator::Cell::cCellUI::Load` | 1548 |
| 00e55120 | `Simulator::Cell::cCellGFX::StartDisplay` | 463 |
| 00e552f0 | `App::cCellModeStrategy::OnEnter` | 170 |
| 00e57340 | `Simulator::Cell::GetScaleDifferenceWithPlayer` | 156 |
| 00e57460 | `Simulator::Cell::ShouldNotAttack` | 251 |
| 00e58980 | `Simulator::Cell::GetDamageAmount` | 303 |
| 00e58e30 | `Simulator::Cell::GetNextAdvectID` | 186 |
| 00e58ef0 | `Simulator::Cell::GetCurrentAdvectInfo` | 286 |
| 00e5b790 | `Simulator::Cell::MovePlayerToMousePosition` | 626 |
| 00e5c0f0 | `App::cCellModeStrategy::OnMouseUp` | 161 |
| 00e5dba0 | `Simulator::Cell::cCellGFX::Initialize` | 1809 |
| 00e62340 | `Simulator::Cell::cCellUI::ShowHealthRollover` | 62 |
| 00e63560 | `Simulator::Cell::cCellGFX::LoadEffectMap` | 1114 |
| 00e64980 | `Simulator::Cell::cCellGFX::PreloadCreature` | 122 |
| 00e653a0 | `Simulator::Cell::cCellGFX::AddPreloadedModel2` | 109 |
| 00e65410 | `Simulator::Cell::cCellGFX::AddPreloadedModel` | 110 |
| 00e65640 | `Simulator::Cell::GetModelKeyForCellResource` | 234 |
| 00e65970 | `Simulator::Cell::cCellGFX::AddPreloadedTexture` | 133 |
| 00e66280 | `Simulator::Cell::cCellGFX::AddPreloadedEffect` | 289 |
| 00e663b0 | `Simulator::Cell::cCellGFX::PreloadCellResource` | 515 |
| 00e665c0 | `Simulator::Cell::cCellGFX::PreloadPopulateResource` | 285 |
| 00e666f0 | `Simulator::Cell::cCellGFX::PreloadResources` | 330 |
| 00e66840 | `Simulator::Cell::cCellGFX::InstanceEffectOnCell` | 314 |
| 00e6c860 | `App::cCellModeStrategy::OnMouseDown` | 397 |
| 00e6d200 | `Simulator::Cell::PlayAnimation` | 317 |
| 00e74a20 | `Simulator::Cell::CreateCellObject` | 1689 |
| 00e7d660 | `App::cCellModeStrategy::OnMouseWheel` | 183 |
| 00e7fc00 | `App::cCellModeStrategy::OnExit` | 251 |
| 00e80980 | `App::cCellModeStrategy::Update` | 29 |
| 00e80ba0 | `Simulator::Cell::cCellGame::Initialize` | 1399 |
| 00e818f0 | `App::cCellModeStrategy::OnKeyDown` | 182 |
| 00e81cf0 | `App::cCellModeStrategy::Initialize` | 564 |
| 00e81f30 | `App::cCellModeStrategy::Dispose` | 497 |
| 00e82340 | `Simulator::Cell::cCellDataReference_::Create` | 107 |

(Plus `App::cCellModeStrategy::AddRef`, `Dispose`, and `cCellDataReference_::Create`
variants — 37 decompilation files total on disk.)

### 3.2 KG nodes (verified present in `knowledgegraph/spore.db`)

- Functions: `fun:00e5b790` (id 1912), `fun:00e80ba0` (1935), `fun:00e74a20`
  (1930), `fun:00e5dba0` (1914), `fun:00e666f0` (1926), `fun:00e806b0` (1933),
  `fun:00e54270` (1904), `fun:00e55120` (1905), `fun:00e80980` (1934),
  `fun:00e4ce40` (34972).
- Structures (60+): `struct:/Spore/Simulator/Cell/cCellGame` (61901),
  `cCellObjectData` (61892), `cCellGFX` (61910), `cCellCellResource` (61869),
  `cCellWorldResource` (61864) + `cAdvectEntry`/`cLevelEntry` (61863/61862),
  `cCellPopulateResource` (61860) + `cMarker` (61859), `cCellStructureResource`
  (61856) + `cSPAttachment` (61855), `cCellLootTableResource` (61871) +
  `cLootTableEntry` (61870), `cCellGlobalsResource` (61885),
  `cCellEffectMapResource` (61880) + `cEffectMapEntry` (61879),
  `cCellBackgroundMapResource` (61883) + `cBackgroundMapEntry` (61882),
  `cCellLookTableResource` (61874), `cCellLookAlgorithmResource` (61877),
  `cCellRandomCreatureResource` (61853), `cCellPowersResource` (61850),
  `cCellSerializableData` (61843), `cCellDataReference_` (61848),
  `cObjectPool<cCellObjectData>` (61897), `cCellQueryLinkedPool` (61895) +
  `cCellQueryLinkedPoolData` (61894) + `cCellQueryEntry` (61893),
  `cCellScaleInfo` (62333), `cCellAnimDefinition` (61888), `cCellUI` (61915) +
  `cCellUIRollover` (61912) + `cObjectPool<cCellUIRollover>` (61914),
  `App/cCellModeStrategy` (61796), plus all `cCellDataReference<T>` instantiations.

### 3.3 SDK headers (Spore-ModAPI, GPL — semantics only, never copied)

`Simulator/Cell/`: `cCellResource.h` (815 L — all resource types, TYPE constants,
full field offsets), `cCellGame.h` (class layout: pool @1Ch, `mpCellQuery` @40FCh,
`mpCellQueryBackground` @4100h, `mpCurrentWorld` @4114h, `mpCurrentWorldBackground`
@4118h), `cCellObjectData.h` (per-cell fields + `IsCreature`/`IsPlayer`/
`GetPosition`), `CellFunctions.h` (free-function API incl. `GetPlayerCell`,
`GetCurrentAdvectInfo`, `CreateCellObject`, `MovePlayerToMousePosition`,
`ShouldNotAttack` with documented conditions), `cCellGFX.h` (WorldIDs enum,
world interfaces), `cCellUI.h`, `cCellScaleInfo.h`, `cCellSerializableData.h`,
`cCellQueryLinkedPool.h`, `CellAnimations.h`, `cCellResource.h`.

### 3.4 Record census (measured from DBPF indexes, all 12 packages)

| Type (sporemol name) | TYPE | Records | Location |
|---|---|---|---|
| `cell` | 0xDFAD9F51 | 489 (43 base, all exactly 0x31C=796 B) | `Spore_EP1_Data.package` (base) + expansion packages |
| `world` | 0x9B8E862F | 37 (16–544 B) | base + expansions |
| `populate` | 0xDA141C1B | 20 (16–3436 B) | base |
| `structure` | 0x4B9EF6DC | 38 | base |
| `globals` | 0x2A3CE5B7 | 1 (276 B) | base |
| `lootTable` | 0xD92AF091 | 9 (64–288 B) | base |
| `randomCreature` | 0xF9C3D770 | 22 | base + expansions |
| `look_table` | 0x8C042499 | 20 | base + expansions |
| `effectMap` | 0x433FB70C | 2 | base |
| `backgroundMap` | 0x612B3191 | 2 | base |
| `look_algorithm` | 0xDBA35AE2 | 2 | base |
| `powers` | 0x754BE343 | 2 | base |
| **UNKNOWN 0x0f43029a** | — | **1,365** (553–6,878 B) | `Spore_Content.package` (1,022) + `Spore_EP1_Content_01.package` (343); groups 0x40612200/0x40616200/0x40626200/0x40636200 |
| `rw4` | 0x2F4E681B | 1,131 | `Spore_Content.package` |
| real cell GMDL family | group 0x40616201/02 | 88 records / 44 instances | measured (KG node) |

Key observations:
- The base-game cell content lives in `SPORE/DataEP1/Spore_EP1_Data.package` in the
  GOG layout (the `SPORE/Data/*.package` set is expansion content); `Spore_Content`
  carries the world-object records.
- `cell` records are exactly 0x31C bytes = the `cCellCellResource` struct size from
  the SDK header — strong layout confirmation.
- 0x0f43029a is **not** in the 40 known sporemol type names; sample header shows
  serializer-style counts (`09 00 00 00 0b 00 00 00 08 00 00 00 09 00 00 00 47 00`)
  → INFERRED to be CellSerializer-based scene/world objects. Format is the campaign's
  central decode problem.

---

## 4. Gap analysis

What stands between today's slice and a playable cell stage:

| # | Gap | Blocks | Unblocked by |
|---|---|---|---|
| G1 | Movement plane constants unread (Sim.hpp:108-109 APPROXIMATION) | faithful steering | static read of `.rdata` |
| G2 | 0x0f43029a world-object format undecoded | scene placement, player-cell identity | pure format work |
| G3 | No name↔instance map (player cell is a REJECTED building stand-in) | real scene | G2 + cell-resource decode |
| G4 | Cell resources not decoded in C++ | sim data, UI data | serializer decode |
| G5 | RW4 container C++ walker not ported | materials beyond DXT5, animation | oracle port |
| G6 | Sim lacks original state model (cCellGame/pool/query/advect/damage) | decompiled-faithful behavior | implementation |
| G7 | Mode-strategy lifecycle not formalized | reuse for creature/space | implementation |

---

## 5. Targets

Format per target: **ID — name** · *original* (address/evidence) · *semantics* ·
*OpenSpore mapping* · *test* · *value* · *status*.

### Wave 1 — Static decode unblockers (no in-tree C++ dependency)

**CS-01 — Pin movement-plane constants from the static binary**
· *original*: `MovePlayerToMousePosition` @ 00e5b790 reads `DAT_015a7c40/44/48`
  (plane normal) and `DAT_016b3c28/2c/30` (plane point); decompilation OBSERVED;
  KG fun:00e5b790.
· *semantics*: the plane the player cell is steered across; 6 floats in `.rdata`.
· *mapping*: read at VA (image base 0x400000 → section file offset) from
  `SPORE/SporeBin/SporeApp.exe`; pin in `src/sim/Sim.hpp` `MovementPlane`; delete
  the APPROXIMATION comments at :108-109.
· *test*: unit test asserting loaded values; re-run the 64-sample differential
  (`docs/REPLACEMENT-DIFF.md`) and the contract (now `cell-sim-contract/2`).
· *value*: kills G1; unblocks CS-14.
· *status*: **DONE (2026-09-23, CS-01).** Normal read from the static binary:
  `.data`, image `0x015a7c40/44/48` (file `0x11a6640`) = `{0,0,1}` — VERIFIED,
  the swim plane is the horizontal z=0 plane. The point's addresses
  (`0x016b3c28/2c/30`) are in BSS (zero in the image, runtime-written per-world):
  load-time `{0,0,0}`. `MovementPlane` defaults pinned to the read values in
  `src/sim/Sim.hpp`; new `plane_constants_test` (ctest) asserts them; the
  mouse-steering fixtures changed, so the contract was bumped
  `cell-sim-contract/1 → /2` and the fixtures regenerated (double-run
  byte-identical). Full ctest 11/11 green; python suite 407 OK; the 64-sample
  differential re-run is 64/64 MATCH (it feeds both sides an explicit plane, so
  the table is unchanged). KG `cs01_plane_constants` = pass.

 **CS-02 — Decode 0x0f43029a world-object records**  *(DONE 2026-09-23: header +
   structural body decode + C++ port + test)*
 · *original*: 1,365 records in the `*Models` groups (CreatureModels 937,
   FloraModels 317, PaletteModels 67, CellModels 44). **NOT CellSerializer-based** —
   those are separate types (world 0x9B8E862F, cell 0xDFAD9F51, …). This is a
   distinct model/scene-placement format.
 · *header (20 B, LE, VERIFIED across all 1365)*: `magic 0xABB455B7` + `version`
   (9 = base 1022 recs / 10 = EP1 343) + `count_c` (primary entry count 2..100,
   scales monotonically with size) + `count_d` (5..71) + `count_e` (0..254).
 · *body (STRUCTURAL MODEL, R²=0.9997, mean residual −0.2 B)*: `size − 20 ≈
   count_c·141 + count_d·5 + count_e·12 + 50`. `count_e` entries are 12-byte
   vector3s; `count_d` are ~5-byte values; `count_c` are ~141-byte main entries
   carrying the concatenated **lowercase part-name strings** (spine/eye/sense/spin/
   limb/foot/mvcl/…) — the variable-length residual. **Limitation (documented):**
   the per-field byte ORDER *within* a c-entry is not derivable from cross-record
   consistency (no decompiled loader references the type; vector3 arrays sit at no
   fixed preamble); the decoder extracts the semantic content and proves full byte
   accounting rather than a field-by-field grammar.
 · *semantics*: model/scene objects for the cell stage — placement, ownership,
   part identity (the names are the meaningful placement identity).
 · *mapping*: python oracle **`tools/spore/worldobj/worldobj.py`
   (validate / histogram / dump / decode / decode-all)**; C++ reader
   **`src/assets/WorldObject.{hpp,cpp}`** (parseWorldObject → WorldObject);
   per-record `decode_status` into the manifest (CS-22).
 · *test*: `worldobj.py validate` → **0 invariant violations of 1365**;
   `decode-all` → **1365/1365 records fully byte-accounted** (6,152 names +
   vector3s). C++ **`ctest assets_worldobj` PASS**: 1365 records, magic/version/
   count_c invariants + every byte of every record accounted for. Full suite green
   (ctest 12/12; unittest 407, 1 pre-existing flaky timing test). No differential
   vs original (no runtime) — oracle + invariants only. KG `cs02_worldobj_entries`=pass.
 · *value*: CRITICAL PATH — kills G2, unblocks CS-13/CS-23. *status*: DONE.

 **CS-03 — CellSerializer core + `cCellGlobalsResource` decode**
 · *original*: `cCellSerializableData` (struct 61843; `CellSerializerField`
   mpName/mID/field_8), `GetGlobalsData` @ 00e4ce20; 1 `globals` record (276 B).
 · *semantics*: the name/ID-field serialization envelope every cell resource uses;
   globals = stage-wide tuning values.
 · *mapping*: oracle `tools/spore/cellres/` → C++ `src/assets/CellResource.{hpp,cpp}`
   (serializer walk + `cCellGlobalsResource` fields per header @642: TYPE 0x2A3CE5B7).
 · *test*: globals record decodes; field sanity; double-run byte-identical.
 · *value*: foundation for CS-05…CS-12.
 · **DONE (2026-09-23).** The globals record (276 B, `Spore_EP1_Data.package`,
   group 0 / inst 0xa426730b) is a **direct field-by-field serialization of the
   runtime struct `cCellGlobalsResource`** (Ghidra 61843 family, 276 B) — NOT
   wrapped in a name/ID envelope. All 69 fields decode by offset/kind to clean
   hand-authored values (round floats: flowMultiplier 5, npcSpeed 0.5, densities
   80/50/7/3; small enums controlMethod 0 / editorMethod 1 / tutorialMethod 2 /
   endingMethod 1 / eyeMethod 0; u32 resource-reference keys). Last field ends
   exactly at byte 276. Oracle `tools/spore/cellres/cellres.py` (validate/dump) +
   C++ `src/assets/CellResource.{hpp,cpp}` + `ctest assets_cellres` ALL PASS.
   KG `cs03_cellserializer_core` + `cs03_globals_record` = pass.

 **CS-04 — Port RW4 container walker to C++**  *(DONE 2026-09-23: 1131/1131 records
   byte-identical vs oracle; ctest `assets_rw4` + unittest `test_rw4` pass)*
· *original*: 1,131 `rw4` records (0x2F4E681B); python oracle `tools/spore/rw4.py`
  (detection + section scoping); 114 Graphics structs + 19 decompilations;
  `docs/RENDERWARE-RESEARCH.md`.
· *semantics*: sectioned binary container (meshes, vertex buffers, skeletons,
  keyframe anims, compiled states).
· *mapping*: `src/assets/Rw4.{hpp,cpp}` port of the oracle.
 · *test*: differential vs oracle on all 1,131 records (byte-identical section walk).
 · *value*: kills G5; unblocks CS-31 (anim/effects) + materials.
 · **DONE (2026-09-23).** C++ `src/assets/Rw4.{hpp,cpp}`: 28-B magic + header
   (ftype/objCount/sectionCount/pSectionInfo/pBufferData/bufSize) +
   SectionManifest(0x10004)→SectionTypes(0x10005, n typecodes) + 24-B section
   infos (pData/f04/size/align/tcIdx/tc; adjusted data = pData+pBufferData for
   BaseResource 0x10030). Well-formedness is structural (in-bounds data,
   non-negative size); the SMFX tc map (RENDERWARE-RESEARCH §7.5) is used only to
   count *undocumented* codes (Spore adds 0x7000c/0x7000f — soft, not gated).
   Differential: C++ `rw4_test --dump` == python oracle `describe()` on
   **1131/1131** Spore_Content records (byte-identical); `ctest assets_rw4` PASS +
   `unittest tests/test_rw4.py` PASS. KG `cs04_rw4_port` = pass.

### Wave 2 — Cell resource decodes (all build on CS-03)

Each target: decode oracle → C++ reader; test = all records decode + field sanity
from SDK-enum domains + double-run byte-identical. *status*: implementable now.

**CS-05 — `cCellCellResource` (489 records)** — struct 61869 + `cAIData` (61866) +
`cEatData` (61868) + `cLocalizedString` (61867); TYPE 0xDFAD9F51; size 0x31C
(matches measured 796 B exactly); fields: structure/name/hp/fixedOrientation/flags/
`cellType`(1–4)/`unlockType`(2–10)/`density`(0–4)/break_/pieces/leak/expel/
explosionTable/loot/poison/ai triple/friendGroup/wontAttackPlayer(WhenSmall)/
size[2]/eat/triggersEscapeMission. Base: 43 records, group 0.

**CS-06 — `cCellWorldResource` (37 records)** — struct 61864 + `cAdvectEntry`
(61863) + `cLevelEntry` (61862); TYPE 0x9B8E862F; feeds the advect system (CS-20)
and background world.

**CS-07 — `cCellPopulateResource` (20 records)** — struct 61860 + `cMarker` (61859);
TYPE 0xDA141C1B; scene spawners.

**CS-08 — `cCellStructureResource` (38 records)** — struct 61856 + `cSPAttachment`
(61855); TYPE 0x4B9EF6DC; referenced by `cCellCellResource.structure` (CS-05).

**CS-09 — `cCellLootTableResource` (9 records)** — struct 61871 + `cLootTableEntry`
(61870: type Cell/Table/Nothing, weight, count); TYPE 0xD92AF091; eat rewards.

**CS-10 — `cCellLookTableResource` (20) + `cCellLookAlgorithmResource` (2)** —
structs 61874/61873, 61877/61876; TYPEs 0x8C042499 / 0xDBA35AE2; look/variant
assignment.

**CS-11 — `cCellRandomCreatureResource` (22) + `cCellPowersResource` (2)** —
structs 61853/61852, 61850; TYPEs 0xF9C3D770 / 0x754BE343; spawn + power tables.

**CS-12 — `cCellEffectMapResource` (2) + `cCellBackgroundMapResource` (2)** —
structs 61880/61879, 61883/61882; TYPEs 0x433FB70C / 0x612B3191; feeds CS-25/CS-31.

**CS-13 — Resolve player-cell identity**
· *original*: `GetPlayerCell` (CellFunctions.h); 43 base `cell` records; 13 `cll`
  compositions at group 0x40616200; KG finding node
  "player-cell stand-in (building-cat 0x63, stage 0x7E; identity REJECTED)".
· *semantics*: which `cell` record is the default player cell (and which are food/
  prey).
· *mapping*: `semantic_owner` column in the manifest (CS-22); `cell_stage.cpp`
  player entity uses the decoded record; stand-in table removed.
· *test*: manifest row labeled with evidence level (VERIFIED only if the record
  self-identifies — e.g. via a name field; otherwise INFERRED with reasoning).
· *value*: kills G3. *status*: implementable after CS-05 + CS-02.

### Wave 3 — Sim core (in-tree C++ against decompilation)

**CS-14 — Ray-plane steering with pinned constants**
· *original*: 00e5b790 (screen ray from camera eye + normalized dir → plane hit →
  `mTargetPosition`; cell oriented toward travel dir); decompilation OBSERVED;
  dossier `docs/analysis/dossiers/cell-movement.md`; 64/64 diff match.
· *mapping*: `src/sim/Sim.cpp` — replace the APPROXIMATION plane (CS-01) in the
  existing steering; contract fields unchanged.
· *test*: `sim_contract_test` replay + 64-sample differential re-run.
· *value*: faithful steering. *status*: implementable after CS-01.

**CS-15 — `cCellGame` state object**
· *original*: struct 61901; `Initialize` @ 00e80ba0 (1,399 B: time scale, flag
  resets, pool alloc via thunk_FUN_00bbb400(0x1000,0x1000)); singleton `sCellGame`
  @ 0x16b3c04 (VERIFIED address).
· *mapping*: `src/sim/CellGame.{hpp,cpp}` — state object hosting pool, query,
  background query, `mpCurrentWorld`/`mpCurrentWorldBackground` (cCellDataReference
  @ 61861/61881).
· *test*: Initialize-sequence unit test (time scale, flags); contract scenarios
  exercising world switching.

**CS-16 — Object pool `cObjectPool<cCellObjectData>`**
· *original*: struct 61897; capacity 4,096 (0x1000); allocation call in Initialize
  decompilation.
· *mapping*: `src/sim/CellPool.hpp` fixed pool with matching capacity/alloc
  semantics.
· *test*: allocation + exhaustion behavior unit test.

**CS-17 — Per-cell state layout (`cCellObjectData`)**
· *original*: struct 61892: `mIsIdle` 04h, `mTargetPosition` 08h,
  `mTargetOrientation` 14h, `mTransform` 48h, `mRelativeElevation` 80h, `mOpacity`
  A0h, `mTargetOpacity` A4h, `mTargetSize` B4h, field_B8/BC (speed);
  `IsCreature`/`IsPlayer`/`GetPosition`.
· *mapping*: extend `Sim.hpp` `Entity` with the original field set as a superset;
  contract-visible fields kept byte-exact for float32 replay.
· *test*: contract replay (float32 exact).

**CS-18 — `CreateCellObject`**
· *original*: @ 00e74a20 (1,689 B — largest cell function): pool alloc + state fill
  from `cCellCellResource` + query + scale level/size factor.
· *mapping*: `src/sim/CellGame.cpp::createCellObject` mirroring the decompiled steps.
· *test*: fixture-driven: given resource + position + scale, produced state matches
  contract snapshot.

**CS-19 — Cell query (`cCellQueryLinkedPool`)**
· *original*: structs 61895/61894/61893; position queries over the pool, foreground
  + background; consumed by steering and attack logic.
· *mapping*: `src/sim/CellQuery.hpp`.
· *test*: query results against fixture worlds (from CS-05/CS-06 data).

**CS-20 — Advect system**
· *original*: `GetCurrentAdvectInfo` @ 00e58ef0 (286 B), `GetNextAdvectID` @
  00e58e30 (186 B); `cAdvectEntry` (61863) inside world resources (CS-06); current
  + next advect state in `cCellGame`.
· *mapping*: advect state + info lookup in the sim; drives background world changes.
· *test*: advect ID sequence from decoded world records matches decompiled logic.

**CS-21 — Damage / scale / attack rules**
· *original*: `GetDamageAmount` @ 00e58980 (303 B),
  `GetScaleDifferenceWithPlayer` @ 00e57340 (156 B; `ScaleDifference` enum
  MuchSmaller=0…MuchLarger=4), `ShouldNotAttack` @ 00e57460 (251 B; conditions
  documented in CellFunctions.h).
· *mapping*: pure functions in `src/sim/`; align existing eat/flee thresholds with
  decompiled constants.
· *test*: table-driven unit tests from decompiled constants; contract events
  (eat/flee) unchanged.

### Wave 4 — Scene and rendering (real content)

**CS-22 — Canonical asset manifest v1**
· *original*: architecture in `docs/ASSET-IMPORT-ROADMAP.md` §3.1.
· *mapping*: `tools/spore/manifest/` (SQLite sidecar): one row per DBPF record —
  key (type, group, instance), type/group name, size, format_class, decode_status,
  semantic_owner, per-field evidence label; built idempotently.
· *test*: double-run byte-identical; 100% of index rows present.

**CS-23 — Scene placement from world-object records**
· *original*: CS-02 decode output; replaces the hard-coded table at
  `cell_stage.cpp:101–114` (positions are APPROXIMATIONS today).
· *mapping*: manifest-driven placement in `cell_stage.cpp`; backdrop gmdl
  0x40666202/0x40666203 kept.
· *test*: scene test asserts positions equal the decoded record values.

**CS-24 — Real cell GMDL family**
· *original*: 88 records / 44 instances at groups 0x40616201/02 (KG node
  "real cell-stage GMDL family"); `GetModelKeyForCellResource` @ 00e65640 (234 B)
  maps cell resource → model key; current stand-in `0x40637E03` is a BUILDING
  (identity REJECTED).
· *mapping*: player/food/prey entities load their decoded cell's gmdl.
· *test*: per-record vertex-count expectations via the GMDL walk (existing
  `real_asset_test.cpp` pattern).

**CS-25 — Background map + water composite**
· *original*: CS-12 decode; current clear color at `cell_stage.cpp:69` is
  APPROXIMATION (no cell background record decoded).
· *mapping*: real background composite in the scene.
· *test*: raster diff against decoded background texture.

**CS-26 — `cCellGFX` preload path**
· *original*: `Initialize` @ 00e5dba0 (1,809 B) → `PreloadResources` @ 00e666f0 →
  `PreloadCellResource` @ 00e663b0 / `PreloadPopulateResource` @ 00e665c0 /
  `PreloadCreature` @ 00e64980 → `StartDisplay` @ 00e55120; Add* helpers
  (00e653a0/00e65410/00e65970/00e66280); WorldIDs enum (cCellGFX.h, e.g.
  kCellModelWorldID=0x1010020).
· *mapping*: scene construction in `cell_stage.cpp` mirroring the decompiled preload
  order; GFX state object holding world handles.
· *test*: scene boots with real assets; Obj-15 raster sha256 checks preserved.

**CS-27 — `cCellUI` HUD**
· *original*: `Load` @ 00e54270 (1,548 B), `ShowHealthRollover` @ 00e62340 (62 B);
  structs 61915/61912 + rollover pool 61914.
· *mapping*: minimal HUD overlay (health, rollover) driven by sim state.
· *test*: screen diff against a fixture frame.

### Wave 5 — Mode strategy, animation, verification

**CS-28 — `cCellModeStrategy` lifecycle**
· *original*: `Initialize` @ 00e81cf0 (564 B), `OnEnter` @ 00e552f0 (170 B),
  `OnExit` @ 00e7fc00 (251 B), `Dispose` @ 00e81f30 (497 B), `Update` @ 00e80980
  (29 B); vtable-dispatched with no static callers (dossier "Callers"); stage entry
  via `cGameModeManager::SetActiveModeAt` @ 0x007d8d40 (decompiled).
· *mapping*: formalize the `cell_stage` app as an `IGameMode` host
  (Initialize→OnEnter→Update*→OnExit→Dispose) so creature/space stages reuse the
  pattern.
· *test*: lifecycle ordering test; state cleanup assertions after OnExit.

**CS-29 — Input mapping**
· *original*: `OnKeyDown` @ 00e818f0 (182 B), `OnMouseDown` @ 00e6c860 (397 B),
  `OnMouseMove` @ 00e51010 (26 B), `OnMouseUp` @ 00e5c0f0 (161 B),
  `OnMouseWheel` @ 00e7d660 (183 B).
· *mapping*: key→action table in the cell_stage app (thrust keys already in sim).
· *test*: table-driven key→action test.

**CS-30 — Contract fixture expansion + determinism**
· *original*: `tests/fixtures/cell/fixtures.json` (frozen); contract version
  `cell-sim-contract/1` (bump when behavior changes intentionally).
· *mapping*: add scenarios: background-world switch, advect, multi-cell combat,
  scale change; keep float32 exact + byte-identical PPMs.
· *test*: `sim_contract_test` replay; double-run determinism.

**CS-31 — Animation + effects** *(depends on CS-04)*
· *original*: `PlayAnimation` @ 00e6d200 (317 B); `cCellAnimDefinition` (61888);
  `InstanceEffectOnCell` @ 00e66840 (314 B) + `LoadEffectMap` @ 00e63560 (1,114 B)
  + CS-12 decode; RW4 KeyframeAnim sections.
· *mapping*: swim/eat anims on the player cell; eat/death effect instances.
· *test*: keyframe decode diff (vs CS-04 oracle); event→effect mapping from contract.
· *status*: CS-04 landed (2026-09-23) — unblocked; implementable when reached
   (roadmap target #4 territory — this campaign only consumes it).

**CS-32 — S5 runtime trace + status promotion** *(GATED — do not build on this)*
· *original*: human-watched cell-mode trace (real display + xdotool; pinned gate in
  `docs/RE-DOSSIER-SCHEMA.md` / roadmap §5).
· *mapping*: when approved: run trace, record artifacts in KG `trace_run`, pin
  `sCellGame` field semantics beyond decompilation, promote
  `replaced-approx` → `replaced-verified` in `docs/replacement-status.json`.
· *value*: verification only — the campaign is complete without it.

---

## 6. Wave plan and dependencies

```
Wave 1 (parallel, no in-tree deps):
  CS-01  CS-02  CS-03  CS-04
          |        |
Wave 2 (build on CS-03; CS-13 needs CS-02+CS-05):
  CS-05…CS-12  ──>  CS-13
                        |
Wave 3 (in-tree sim core; CS-14 needs CS-01):
  CS-14  CS-15  CS-16  CS-17  CS-18  CS-19  CS-20  CS-21
          |
Wave 4 (scene + assets; needs Wave 2 decodes + CS-22):
  CS-22  CS-23  CS-24  CS-25  CS-26  CS-27
          |
Wave 5 (hosting + verification):
  CS-28  CS-29  CS-30  CS-31(needs CS-04)  CS-32(GATED)
```

Suggested sequencing inside waves:
- Wave 1: **CS-01, CS-02, CS-03 DONE (2026-09-23).** CS-03 decoded the globals
  record as a direct 69-field struct serialization (no envelope) + C++ port +
  `ctest assets_cellres`. Remaining: **CS-04 (RW4 port) — the last Wave-1
  item**; it unblocks Wave-2 CS-31 (anim/effects) + materials.
- Wave 3: CS-15/16/17 (state model) → CS-18/19 (creation + query) → CS-20/21 (rules).
- Wave 4: CS-22 first (every other target reports into it).
- Wave 5: CS-30 (fixtures) before CS-31; CS-32 only on explicit approval.

Estimated campaign size: ~32 targets; Waves 1–2 are decode work (python oracle +
C++ port each), Waves 3–5 are in-tree implementation.

---

## 7. Explicit non-goals

- Creature stage, space stage, editors, terrain, UTFWin (roadmap targets #4–#8).
- Any behavior whose only evidence is the S5 trace (CS-32 gated; nothing built on
  trace assumptions).
- Pollinator (defunct service — stub only, never reimplemented).
- Copying Spore-ModAPI code (GPL, semantics-only reference).
- GMDL v9 layout (1,510 walk-fails — separate work; not needed for the cell family).

---

## 8. Risks

| Risk | Mitigation |
|---|---|
| 0x0f43029a is *not* CellSerializer-based (header guess wrong) | RESOLVED (CS-02): distinct model/scene-placement format with a 20-B header + part-name identity strings (spine/eye/sense/…). Carries creature part identity directly, so player identity does NOT depend on CS-05 alone. Documented limitation: per-field byte order within a c-entry not byte-exact derivable (no loader references the type); decoder uses full byte accounting + semantic extraction. |
| Plane constants are per-world (change with advect) | CS-01 reads both address sites; CS-20 advect system covers world-dependent values; contract test pins the observed behavior |
| Player identity is INFERRED, not VERIFIED | Manifest labels it INFERRED with reasoning; scene remains playable; CS-32 can later confirm |
| float32 contract drift when constants change | Contract version bump (`cell-sim-contract/1` → `/2`) with fixture regeneration, same discipline as before |
| 796 B `cell` record layout assumption (0x31C) | CS-05 verifies field-by-field against the SDK header; any mismatch is recorded as `needs-deeper-look`, never silently patched |
