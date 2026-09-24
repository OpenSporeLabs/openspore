# 04 — World / Planet Archaeology

## Scope and method

This partition covers the persistent and live world model: `cStarRecord`, `cPlanetRecord`, `cStar`, `cSolarSystem`, `cCelestialBody`, `cPlanet`, `cVisiblePlanet`, `cPlanetGfx`, `cStarManager`, `cPlanetModel`, orbital data, universe simulation, terrain sphere/quads/maps/state/weather, terraforming, and related navigation/event consumers. It is documentation only; no implementation, SPORE/ access, binary/Ghidra mutation, or triage rewrite was performed.

Evidence labels are intentionally constrained to `OBSERVED`, `SUPPORTED`, `INFERRED`, and `UNKNOWN`. Decompiler output is mechanics evidence, not class truth; SDK names are imported vocabulary; no MSVC RTTI is present. Source-specific conflicts are retained rather than reconciled.

**Scope evidence — SUPPORTED; high confidence.** `docs/RE-DOSSIER-SCHEMA.md:9-29`, `docs/RECON-3.1.0.22.md:83-89`, `knowledgegraph/research/global-campaign-2026/track-f-empire-economy.json:913-921`.

## Executive model

The strongest reconstruction is a two-layer graph:

1. **Persistent records:** `cStarRecord` owns generated `cPlanetRecord` references; the records carry identity, orbital parameters, planet suitability scores, species, commodities, civ/tribe state, and generated resource keys.
2. **Live objects:** `cStar` links a `cSolarSystem`; the system owns live `cPlanet` and `cCelestialBody` collections. `cPlanet` links its persistent record, visible representation, hit sphere, low-LOD simulation, models, and effects.
3. **Surface join:** singleton `cPlanetModel` holds both intrusive and raw `ITerrain` pointers and exposes height, water, gravity, orientation, and surface conversion operations.
4. **Terrain join:** `cTerrainSphere` owns maps, quads, texture/RTT state, `cTerrainStateMgr`, and `cWeatherManager`; `cTerrainSphereQuad` owns mesh buffers, transforms, and land/water index ranges.

**Model evidence — SUPPORTED; high confidence.** SDK field exports at `.spore-analysis/ghidra-exports/structs_fields.tsv:11141-11315`, `:11644-11682`, `:11188-11283`, and `:12158-12178`.

The important reconstruction order is therefore data before behavior: records/identity, live system graph, orbit and surface geometry, climate/terraforming, then space consumers and presentation. **Order evidence — SUPPORTED; high confidence.** `knowledgegraph/research/global-campaign-2026/track-o-packages-testability.json:336-381`, `knowledgegraph/research/global-campaign-2026/track-f-empire-economy.json:849-879`.

## Recovered types

### `cPlanetRecord` — 432 bytes

Persistent/generated planet definition and runtime data carrier. The record begins with `ResourceObject` rather than `ISimulatorSerializable`, carries a 104-byte `cEllipticalOrbit` at `+0x30`, planet scores, species/commodity/civ/tribe collections, `PlanetID`, `TechLevel`, and generated terrain/spice resource keys.

| Range | Material fields/meaning | Evidence |
|---|---|---|
| `0x00-0x18` | `ResourceObject` vtable, `mnRefCount`, `mNameKey`, final-release callback, `mName` | **SUPPORTED**, high; SDK field export `.spore-analysis/ghidra-exports/structs_fields.tsv:11141-11145` |
| `0x28-0x38` | `mType: PlanetType`, `mFlags`, `mOrbit: cEllipticalOrbit` | **SUPPORTED**, high; `:11146-11148`, SDK enum `spore_sdk.xml:10407-10416` |
| `0x9c-0xb8` | rotation axis/period/ring, `mAtmosphereScore`, `mTemperatureScore`, `mWaterScore` | **SUPPORTED**, high; `:11153-11161` |
| `0xbc-0x148` | plant/animal species, commodities, unnamed int collections, defender/reinforcement timers, home flag, planet objects, terrain stamps | **SUPPORTED**, high; `:11162-11176` |
| `0x15c-0x1ac` | `mCivData`, `mTribeData`, `mKey: PlanetID`, `field_188: ResourceKey`, `mTechLevel`, `mSpiceGen`, `mGeneratedTerrainKey` | **SUPPORTED**, high; `:11177-11183` |

Ownership is ref-counted and exposed through intrusive pointers in `cStarRecord` and `cPlanet`; `cPlanetRecord::Create` is `0x00ba6300`. **Ownership evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs.tsv:987-999`, `.spore-analysis/ghidra-exports/sdk_functions.tsv:1276`.

The direct `cPlanetRecord` body export is empty/incomplete, so creation mechanics are not recovered. **Creation evidence — UNKNOWN; low confidence.** `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cPlanetRecord__Create.c:8-13`.

### `cPlanet` — 456 bytes

Live game-data planet object with transform, selection state, record/key, low-LOD simulation, visible/solar representations, effects, colony timer, parent link, and spice color.

- `0x00-0x70`: `cSpatialObject` vtable, position/orientation, bounds, flags/material, radii/scale/camera distance, selection/in-view flags. **SUPPORTED**, high; `.spore-analysis/ghidra-exports/structs_fields.tsv:11188-11212`.
- `0x90-0xc0`: model key, model, model world, pinned/transform/presentation state, integer vector. **SUPPORTED**, high; `:11221-11234`.
- `0xd4-0x1bc`: `cGameData` and `DefaultRefCounted` bases, IDs/political ID, `mpPlanetRecord`, `mPlanetKey`, starter world, orbited-planet position, `mpPlanetSim`, representation mode, impostor/effects/scale, `mpSolarHitSphere`, `mpVisiblePlanet`, colony timer, planet flags, parent, and spice color. **SUPPORTED**, high; `:11235-11283`.

`cPlanet` is ref-counted and list-linked, but it is not `ISimulatorSerializable` in the exported layout; persistence belongs to the record/enclosing save state. **Serialization evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:11235-11237`, `:11141`.

### `cVisiblePlanet` and `cPlanetGfx`

`cVisiblePlanet` is a separate 268-byte presentation/selection object with the same spatial/game-data family of fields and an intrusive `mpPlanet` link at `+0x108`. **SUPPORTED**, high; `.spore-analysis/ghidra-exports/structs.tsv:965`, `.spore-analysis/ghidra-exports/structs_fields.tsv:10764-10827`.

`cPlanetGfx` is a 104-byte `IGameDataView`/list-node object with spatial object, combatant, planet, effect, and presentation collections. **SUPPORTED**, high; `.spore-analysis/ghidra-exports/structs.tsv:967`, `.spore-analysis/ghidra-exports/structs_fields.tsv:10833-10854`.

The planet/visible-planet pointers form a relationship, but destruction and copy order are not established. **Lifecycle evidence — INFERRED; medium confidence.** `:10763-10827`, `:11266-11267`.

### `cStarRecord` — 176 bytes

Persistent star definition, ownership, saved-game, and generated-planet carrier. It explicitly begins with `ISimulatorSerializable` and `DefaultRefCounted` bases.

- `0x00-0x24`: serializable/ref-count bases, `mLastObservedTime`, saved-game version/timestamp. **SUPPORTED**, high; `.spore-analysis/ghidra-exports/structs_fields.tsv:11289-11295`.
- `0x3c-0x70`: position, `StarType`, `TechLevel`, flags, empire ID, starter world ID, name, `StarID`. **SUPPORTED**, high; `:11296-11307`, `spore_sdk.xml:10417-10430`.
- `0x74-0xac`: citizen species key, species profile, generated planet-record vector, second unnamed planet vector, `mPlanetCount`. **SUPPORTED**, high; `:11308-11312`.

The `ISimulatorSerializable` slots are `AddRef +0x00`, `Release +0x04`, destructor `+0x08`, `Cast +0x0c`, `Write +0x10`, `Read +0x14`, extra slot `+0x18`, `WriteToXML +0x1c`, and `GetNounID +0x20`. The interface is known; the concrete save keys/order are not. **Serialization evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:1191-1200`.

The star-system regeneration dossier observes: `mPlanetCount == 0` plus a timing check, write `mLastObservedTime`, erase from pending list, reset manager state, then call `GeneratePlanetsForStar`. **Regeneration evidence — OBSERVED; high confidence.** `docs/analysis/dossiers/unknown-high/star-system-regen.md:18-48`.

### `cStar` — 80 bytes

Live game-data star with `cGameData`/`DefaultRefCounted` bases, primary/secondary `StarType`, activation/capture flags, `mpSolarSystem`, `mpStarRecord`, and key. **Layout evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:11654-11682`.

`cStar` and `cSolarSystem` form a pointer cycle at the type level; final destruction order is unknown. **Lifecycle evidence — SUPPORTED for pointer links / INFERRED for cycle consequence; medium confidence.** `:11644-11682`.

### `cCelestialBody` — 204 bytes

Generic live body for stars, comets, and other celestial bodies. It contains game-data identity, `cCelestialBodyType`, `cEllipticalOrbit`, position, rotation rate, name, visual effect, and hit sphere. **Layout evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:11608-11631`, `spore_sdk.xml:10432-10436`.

`Write`, `Read`, and `WriteToXML` are named at `0x00bd6380`, `0x00bd63f0`, and `0x00bd6630`; exact field order is unresolved. **Serialization evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/sdk_functions.tsv:1297-1300`.

### `cSolarSystem` — 84 bytes

Ref-counted serializable live container with `mpOwnerStar`, `mPlanets`, `mCelestialBodies`, `mpStar1`, `mpStar2`, and a model vector. **Layout evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:11644-11652`.

`ISimulatorSerializable` is explicit at `+0x08`, making the system a direct persistence candidate. **Serialization evidence — SUPPORTED; high confidence.** `:11644-11646`, `:1191-1200`.

`Load`, `LoadBinaryStar`, `LoadAsteroids`, `GenerateCelestialBodiesEffects`, and `GenerateGraphics` are named consumers. The committed `GenerateGraphics` body iterates body/model ranges and calls graphics helpers. **Mechanics evidence — OBSERVED; high confidence.** `.spore-analysis/ghidra-exports/sdk_functions.tsv:1337-1349`, `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cSolarSystem__GenerateGraphics.c:15-28`.

### `cStarManager` — 556 bytes

Singleton-backed strategy/service root. It embeds `ISimulatorStrategy`, `IVirtual`, ref-count, and `IMessageListener` relations and owns:

- state maps/vectors and live planet vector (`0x00-0x50`);
- starter worlds, message-listener data, star grid, starter/saved/black-hole/possible-start records, empire home-star map, Sol/temp star, and empires (`0xa0-0x150`);
- solar-system and galactic-constants property lists, generation scores/probabilities, political ID, scenario star, trade routes, relationship manager, transaction log, collectible items, and planet-record databases (`0x1a0-0x21c`).

**Layout evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:11458-11514`.

`cStarManager::Get` is `0x00b3d3a0`, returning `DAT_0167eb0c`. **Root evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/sdk_functions.tsv:1243`, `knowledgegraph/research/global-campaign-2026/track-f-empire-economy.json:162-170`.

The manager is the central generation seam: `CalculatePlanetScores`, `GenerateEllipticalOrbit`, `FindClosestStar`, `FindStars`, `GenerateSolSystem`, `GeneratePlanetsForStar`, `RequirePlanetsForStar`, `RecordToPlanet`, and `StarGenerationMessageHandler`. **Consumer evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/sdk_functions.tsv:1277-1289`.

It has no direct `ISimulatorSerializable` pointer, but owns saved-game star records, property lists, and databases; save persistence is an enclosing manager/database contract. **Serialization evidence — SUPPORTED; medium confidence.** `:11458-11514`, `knowledgegraph/research/global-campaign-2026/track-f-empire-economy.json:515-522`.

### `cEllipticalOrbit` — 104 bytes

Orbit values are embedded by value in `cPlanetRecord` and `cCelestialBody`, not separately allocated in the recovered layouts. **Ownership evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:11148`, `:11625`.

Fields are `mbNullOrbit`, `mPlaneNormal`, `mEccentricity`, `mPerihelion`, `mPeriod`, and `OrbitCache`. The cache stores squared axes, foci, eccentricity square, normalized perihelion, descending node, and focus. **Layout evidence — SUPPORTED; high confidence.** `:10996-11015`.

`cStarManager::GenerateEllipticalOrbit` is the named producer; formulas and update cadence remain unknown. **Evidence — SUPPORTED for function presence, UNKNOWN for formula; high/low confidence respectively.** `.spore-analysis/ghidra-exports/sdk_functions.tsv:1281`.

### `cPlanetModel` — 92 bytes

Explicit Space-to-Terrain join. It embeds `IMessageListener`, `ISimulatorStrategy`, and `IVirtual`, stores last/current game mode, an intrusive `ITerrain`, a raw `ITerrain`, a planet `ResourceKey`, name/listener state, and A*/obstacle/ribbon pointers. **Layout evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:12158-12178`.

`cPlanetModel::Get` is `0x00b3d450`, returning `DAT_0167eb38`. **Root evidence — OBSERVED; high confidence.** `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cPlanetModel__Get.c:8-13`.

The named surface/geography contract is `IsInWater`, `GetGravity`, `GetHeightAt`, `GetOrientation`, `ToSurface`, and `GetNearestCity`. **Function evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/sdk_functions.tsv:1269-1274`.

`ToSurface` shows length checks, zero-vector handling, trigonometric/vector transforms, quaternion-to-matrix conversion, normalization, and return writes. Ghidra’s field typing is noisy, so the displayed vtable-like writes are not promoted as actual vtable data. **Mechanics evidence — OBSERVED; medium confidence.** `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cPlanetModel__ToSurface.c:38-91`.

## Terrain, climate, and geography

### `ITerrain` interface

The SDK names the `ITerrain` slots from `AddRef/Release` through property/map/state/weather access, display/load lifecycle, modifications, planet info, render/visibility, underwater/grass, raycast, orientation, dispose, parse, camera/sun, and load operations. **Interface evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:12081-12156`.

`cPlanetModel` holds both intrusive and raw terrain pointers; `cTerrainSphere` is the concrete surface. The alias/lifetime relationship is unresolved. **Ownership evidence — SUPPORTED; high confidence.** `:12167-12168`, `:17534-17543`.

### `cTerrainSphere` — 2640 bytes

Concrete sphere surface implementing `ITerrain`, `ILayer`, `IMessageListener`, `IAmbientOccluder`, and `ResourceObject` relations. It holds:

- property list and map set (`+0x28/+0x2c`);
- texture containers, loader/on-load callback, generation mode/time limit;
- full/low-resolution quad arrays and normal/height/control texture arrays;
- land rendering chunks, seed, LOD/cull radii;
- raw `cTerrainStateMgr` and intrusive `cWeatherManager`;
- camera position/direction, sun direction, and munging scales.

**Layout evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:17534-17605`.

Renderer research identifies the world pass as sphere → visible quads → land/seabed/water/atmosphere/decals, with LOD through `cModelWorld::UpdateWithLODMeshes`. **Pass evidence — SUPPORTED; high confidence.** `docs/RENDERWARE-RESEARCH.md:320-325`.

### `cTerrainSphereQuad` — 440 bytes

Per-quad surface unit with parent sphere, LOD/index/transform/bounds state, `TerrainQuadMesh`, land/water index counts and ranges, update flags, and `mAboveBelowMap`. **Layout evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:17437-17480`.

The quad pass family is `Draw`, `LoadTerrainTransform`, `UpdateIndexBuffer`, `Initialize`, `UpdateVertexBuffer`, `RenderLand`, `RenderWater`, `RenderAtmosphere`, and `RenderSeabedAsLand`. **Function evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/sdk_functions.tsv:1504-1513`.

The exported `Draw` body is useful for cleanup/state-reset mechanics but is not a complete draw algorithm. **Mechanics evidence — OBSERVED; low/medium confidence.** `.spore-analysis/ghidra-exports/decompiled_sdk/Terrain__cTerrainSphereQuad__Draw.c:8-33`.

### Maps and state

`cTerrainMapSet` is 92 bytes with eleven intrusive maps, planet radius, altitude range, water level, gradient limits, scalar parameters, and height ranges. **Layout evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:11721-11734`.

`cTerrainStateMgr` is 3136 bytes with raw terrain/map pointers, `TerrainMaterial` (748 B), `TerrainTextures` (696 B), material properties, atmosphere/water types, water/wave state, effects, and large state buffers. **Layout evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:1054-1056`, `:11910-11945`.

`TerrainState` is 320 bytes of sun direction, water color, camera/sphere/illumination/fog parameters, day/night/dusk light and shadow colors, dusk/dawn range, and view transform. **Layout evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:1064`, `:12055-12080`.

### Weather and climate

`cWeatherManager` is 416 bytes with effect-world/effect pointers, atmospheric/storm/ambient/local-storm IDs, rain ramp/darkness, evaporation/freeze effects, typed weather `PropertyContainer<int>`/`PropertyContainer<bool>`, terrain/state/map pointers, cloud colors/ID, effects vector, RNG, property list, and tuning scalars. **Layout evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:1059-1063`, `:11947-12054`.

Climate is therefore two-layered: persistent planet scores (`mAtmosphereScore`, `mTemperatureScore`, `mWaterScore`) and runtime terrain/material/weather state. **Climate claim — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:11159-11161`, `:11740-11945`, `:12050-12054`.

Weather property IDs, transition equations, and runtime values are not recovered. **Climate unknown — UNKNOWN; high confidence that the gap exists.** `knowledgegraph/research/global-campaign-2026/track-f-empire-economy.json:887-900`.

## Orbit, space context, and simulation

`SpacePlayerData` is 52 bytes: update time, active planet, active star, relationship manager, `SpaceContext`, rotation factor, player empire ID/pointer, and colony vector. **Layout evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:11683-11691`, `spore_sdk.xml:10393-10398`.

`cSimulatorUniverse` is a 440-byte serializable simulation root with tuning properties, event timing, player death, disaster timing, grob/empire awareness thresholds, and awareness maps. **Layout evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:15040-15077`.

`IUniverseRoutine` names `GetProbability`, `Execute`, and `GetID`; the exact event order and star/planet coupling remain unknown. **Simulation evidence — SUPPORTED for interfaces/state, UNKNOWN for event order; high/low confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:15026-15030`, `:15054-15075`.

`cTimeOfDay` is a serializable 40-byte object with a float vector and `mDayDuration`; `SetDayDuration`, `SetSpeedMultiplier`, `SetTimeOfDay`, and `Get` are named operations. **Evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:14083-14091`, `.spore-analysis/ghidra-exports/sdk_functions.tsv:1293-1296`.

## Serialization and persistence

Direct serializable relations are explicit for `cStarRecord`, `cSolarSystem`, `cSimulatorUniverse`, `cTimeOfDay`, and `cCelestialBody`. `cPlanetRecord` is `ResourceObject`-backed; `cPlanet`, `cVisiblePlanet`, and `cPlanetGfx` are live projections. Terrain/weather carry property lists and resource keys but no direct serializable vtable in the consulted layouts. **Serialization claim — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:11141`, `:11289-11315`, `:11644-11652`, `:15040-15042`, `:14083-14085`, `:17542`, `:12049`.

The recovered property spine is `PropertyList::Read`, `Write`, `GetProperty`, `SetProperty`, and `AddPropertiesFrom`. `cStarManager`, `cWeatherManager`, `cTerrainStateMgr`, `cPlanetModel`, and terraforming-related records expose property/field seams, but exact planet/save keys are unknown. **Serialization evidence — SUPPORTED; high confidence.** `knowledgegraph/research/global-campaign-2026/track-f-empire-economy.json:505-526`, `.spore-analysis/ghidra-exports/structs_fields.tsv:11490-11491`, `:12049-12050`.

Resource-key relationships are strong: `cPlanetRecord.mGeneratedTerrainKey`, `mSpiceGen`, and `field_188`; `cStarRecord.mCitizenSpeciesKey`; and live model/planet identity links. **Resource evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:11180-11183`, `:11308`, `:11221-11223`, `:11629-11631`.

## Vtables and inheritance

SDK layouts establish the following base-interface relations:

- `cPlanet`: `+0x00 cSpatialObject`, `+0xd4 cGameData`, `+0xd8 DefaultRefCounted`.
- `cStar`: `+0x00 cGameData`, `+0x04 DefaultRefCounted`.
- `cSolarSystem`: `+0x00 DefaultRefCounted`, `+0x08 ISimulatorSerializable`.
- `cStarRecord`: `+0x00 ISimulatorSerializable`, `+0x04 DefaultRefCounted`.
- `cPlanetModel`: `+0x00 IMessageListener`, `+0x04 ISimulatorStrategy`, `+0x08 IVirtual`.
- `cTerrainSphere`: `+0x00 ITerrain`, `+0x04 ILayer`, `+0x08 IMessageListener`, `+0x0c IAmbientOccluder`, `+0x10 ResourceObject`.
- `cWeatherManager`: `+0x00 UnkWeatherManager`, `+0x08 IMessageListener`.

**Relation evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:11188-11237`, `:11289-11291`, `:11644-11656`, `:12158-12161`, `:17534-17539`, `:11963-11966`.

Concrete candidate tables are not class labels:

- `0x01490be8`, 40-slot Terrain candidate, slot 37 associated with `Terrain::cTerrainSphere::GetSimDataRTT` at `0x00f968b0`.
- `0x01490c7c`, 40-slot Terrain candidate, slot 0 associated with the same function.
- `0x01473990`, 24-slot Simulator candidate, slot 8 associated with `Simulator::IsNotStarOrBinaryStar`; this does not prove a cStar or cPlanet vtable.
- `0x01473558`, related space-inventory candidate from the sim-space gap; it is not a planet vtable.

**Candidate evidence — SUPPORTED; medium confidence.** `.spore-analysis/ghidra-exports/vtables.json`, `docs/analysis/vtables.json`, `knowledgegraph/research/decomp-gap/sim-space-00.json:183-247`.

The SDK `ITerrain` interface names 74 slots through `+0x128`, while the atlas candidates are 40 slots. This is an unresolved atlas/layout discrepancy, not a reason to shorten the interface. **Conflict — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:12081-12156`, `.spore-analysis/ghidra-exports/vtables.json`.

## Ownership and lifecycle

Intrusive pointers make many links explicit: `cStarRecord.mPlanets`, `cStar.mpSolarSystem`, `cStar.mpStarRecord`, `cSolarSystem.mPlanets/mCelestialBodies`, `cPlanet.mpPlanetRecord/mpVisiblePlanet/mpSolarHitSphere/mpPlanetSim`, and `cVisiblePlanet.mpPlanet`. **Ownership evidence — SUPPORTED; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:11256-11283`, `:11310`, `:11647-11651`, `:10763-10827`.

Raw pointers remain ambiguous: `cPlanetModel.mpTerrain2`, `cTerrainStateMgr.mpTerrain/mpMapSet`, `cStarRecord.mpSpeciesProfile`, A*/obstacle/ribbon pointers, and several `cWeatherManager` service pointers. **Ownership evidence — SUPPORTED; high confidence for raw-pointer presence, UNKNOWN for ownership; medium confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:12167-12178`, `:11910-12023`, `:11309`, `:17587-17589`.

The manager roots recovered in this partition are `cStarManager::Get` (`0x00b3d3a0`, global `0x0167eb0c`), `cPlanetModel::Get` (`0x00b3d450`, global `0x0167eb38`), `cTerraformingManager::Get` (`0x00b3d530`, global value not recovered), and adjacent `cSpaceTrading::Get` (`0x00b3d4d0`, global `0x0167eb50`). **Root evidence — SUPPORTED/OBSERVED; high confidence where stated.** `.spore-analysis/ghidra-exports/sdk_functions.tsv:1243-1255`, `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cPlanetModel__Get.c:8-13`, `knowledgegraph/research/global-campaign-2026/track-f-empire-economy.json:150-170`.

## Consumers and reconstruction value

The central consumers are:

1. `cStarManager` generation/lookup and `cStarRecord` planet access.
2. `cSolarSystem` lifecycle and graphics generation.
3. `cPlanetModel` surface/geography queries.
4. Terrain sphere/quad land-water-atmosphere passes.
5. Empire home-star/home-planet paths, `cSpaceTrading`, missions, terraforming, and space events.

**Consumer evidence — SUPPORTED except space-event payload details; high/medium confidence.** `.spore-analysis/ghidra-exports/sdk_functions.tsv:1277-1292`, `:1333-1357`, `:1484-1513`, `docs/RENDERWARE-RESEARCH.md:320-325`, `knowledgegraph/research/global-campaign-2026/track-f-empire-economy.json:229-234`, `:473-526`.

The recommended packages are:

1. **Persistent records:** freeze Star/Planet IDs, record layouts, orbit, resource keys, scores, and collections.
2. **Live graph:** cStar/cSolarSystem/cCelestialBody/cPlanet/cVisiblePlanet/SpacePlayerData.
3. **Orbit and surface geometry:** orbit cache, position updates, map radius/altitude/gradient, sphere/quad topology.
4. **Climate/terraforming:** planet scores, TerrainMaterial, TerrainState, weather, time-of-day, TScore.
5. **Space consumers:** cSpaceTrading, cPlanetGfx, solar graphics, missions, events, empire home paths.

**Reconstruction-value evidence — SUPPORTED; high confidence.** `knowledgegraph/research/global-campaign-2026/track-o-packages-testability.json:336-381`, `knowledgegraph/research/global-campaign-2026/track-f-empire-economy.json:849-879`, `docs/SPORE-RECONSTRUCTION-ROADMAP.md:94-99`.

No package is implementation-ready or runtime-validated. **Readiness claim — SUPPORTED; high confidence.** `knowledgegraph/research/global-campaign-2026/track-o-packages-testability.json:336-381`, `knowledgegraph/research/global-campaign-2026/track-f-empire-economy.json:901-924`.

## Current OpenSpore comparison

- `src/sim/CellGame.hpp:60-157` projects Cell current-world references and per-world state, not the global planet/star graph. **OBSERVED; high confidence.**
- `src/assets/CellResource.hpp:183-197` decodes `cCellWorldResource` as a 16-byte header plus populate/advect arrays; it is not `cPlanetRecord`. **OBSERVED; high confidence.**
- `src/assets/WorldObject.hpp:1-71` classifies `0x0F43029A` as a separate model-group format. `src/apps/SceneConfig.hpp:1-18` explicitly records that it is not per-entity scene placement. **OBSERVED; high confidence.**
- `src/apps/CellGfx.hpp:41-76` projects render-world/layer tokens, not `cPlanetModel`, `ITerrain`, weather, orbit, or climate. **OBSERVED; high confidence.**
- `src/sim/Advect.hpp:1-106` is Cell-world advection, not planet climate or orbital simulation. **OBSERVED; high confidence.**
- No current source counterpart exists for `cStarManager`, `cPlanetRecord`, `cSolarSystem`, `cPlanetModel`, `cTerrainSphere`, `cWeatherManager`, or `cTerraformingManager`. **SUPPORTED; high confidence.** `knowledgegraph/research/global-campaign-2026/track-f-empire-economy.json:573-615`.

## Conflicts retained

1. `cPlanetRecord.mCivData/mTribeData`: SDK export says `+0x15c/+0x170`; campaign summary labels `+0x188/+0x1a0`. **SUPPORTED conflict; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:11177-11183`, `knowledgegraph/research/global-campaign-2026/track-f-empire-economy.json:420-423`.
2. `cStarManager` campaign offsets for starter worlds/star grid/starter records do not consistently match the SDK export. Both records are retained. **SUPPORTED conflict; high confidence.** `.spore-analysis/ghidra-exports/structs_fields.tsv:11476-11482`, `knowledgegraph/research/global-campaign-2026/track-f-empire-economy.json:391-396`.
3. Terrain vtable candidates are 40 slots while the SDK `ITerrain` interface has 74 named slots. **SUPPORTED conflict; high confidence.** `.spore-analysis/ghidra-exports/vtables.json`, `.spore-analysis/ghidra-exports/structs_fields.tsv:12081-12156`.
4. `Terrain::cTerrainSphereQuad::RenderAtmosphere @ 0x00fb6ca0` is an SDK/function-export anchor but the RE notes say the symbol is not a function. **SUPPORTED conflict; high confidence.** `docs/RECON-3.1.0.22.md:23`, `.spore-analysis/ghidra-exports/sdk_functions.tsv:1512`.
5. `cPlanetModel::ToSurface` decompiler writes through fields displayed as vtable pointers; these are noisy decompiler expressions, not evidence of mutable vtable data. **OBSERVED conflict; high confidence.** `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cPlanetModel__ToSurface.c:70-91`.
6. The sim-space gap contains contested `CreateSpaceCommEvent`/`HandleSpaceCommAction` identity; no planet ownership is inferred from it. **SUPPORTED conflict; high confidence.** `knowledgegraph/research/decomp-gap/sim-space-00.json:109-180`.

## Decomp-gap status

`terrain-world-00` contains 93 active gameplay-affinity rows in `0x0076b840..0x00feb0f0`, all with committed decompilation unavailable. The partition reconciles 112 cluster/range rows to 93 after excluding five persisted bodies. **Partition evidence — SUPPORTED; high confidence.** `knowledgegraph/research/decomp-gap/terrain-world-00.json:1-69`.

The 93 rows are mostly anonymous P3 candidates; a small set of SDK-named/render/visibility candidates exists, but no exact dossier directly matches the partition. **Gap status — SUPPORTED; high confidence.** `knowledgegraph/research/decomp-gap/terrain-world-00.json:27-30`, `:71-46484`.

`sim-space-00` contains five active targets and preserves targeted decompiler reviews of a shared copy helper, a contested comm-event wrapper, a property-list inventory constructor-like helper, a `0xbc` range destructor, and a descriptor/service initializer. These are shared space infrastructure or identity-contested candidates, not automatically planet gameplay. **Gap status — SUPPORTED; high confidence.** `knowledgegraph/research/decomp-gap/sim-space-00.json:1-180`.

## Runtime and unknowns

No committed original runtime trace reaches Space, planet generation, terraforming, or terrain gameplay. The existing Cell traces do not establish these systems. **Runtime evidence — UNKNOWN; high confidence.** `docs/analysis/dossiers/cell-movement.md:99-103`, `knowledgegraph/research/global-campaign-2026/track-f-empire-economy.json:901-909`.

Ghidra had no open program during this partition, so no live read was attempted. **Session evidence — OBSERVED; high confidence.** `tool://ghidra_list_open_programs`.

Material unknowns are concrete vtable installation, complete serialization field order/keys, generation formulas, raw-pointer ownership, the 93 terrain-gap semantics, weather property IDs/equations, complete space event records, and the original Space-stage entry/save/load sequence. **Unknown set — SUPPORTED as gaps; high confidence.** `knowledgegraph/research/global-campaign-2026/track-f-empire-economy.json:882-900`, `knowledgegraph/research/decomp-gap/terrain-world-00.json:1-69`, `knowledgegraph/research/decomp-gap/sim-space-00.json:30-180`.

## Final disposition

The world/planet partition is statically strong at the schema and boundary level, especially for `cStarRecord`, `cPlanetRecord`, `cStarManager`, `cSolarSystem`, `cEllipticalOrbit`, `cPlanetModel`, `cTerrainSphere`, `cTerrainMapSet`, and `cWeatherManager`. It is weak at algorithms, concrete vtable installation, ownership order, serialization round trips, and runtime transitions. The next evidence target is not implementation: resolve the named root methods and the exact vtable/installed-table paths, then persist read-only decompilation and property/round-trip evidence for the persistent records and space stage.

**Disposition — SUPPORTED; high confidence.** `docs/SPORE-RECONSTRUCTION-ROADMAP.md:94-99`, `knowledgegraph/research/global-campaign-2026/track-o-packages-testability.json:336-381`.
