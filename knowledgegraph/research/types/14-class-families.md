# Global class-family reconstruction

## Scope and result

Research-only reconstruction for `SporeApp.exe` 3.1.0.22 (`25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`). No implementation, `SPORE/`, binary/Ghidra mutation, or historical triage rewrite was performed. The live Ghidra bridge was checked read-only and had no open program, so this report uses the pinned local exports.

The reconstruction contains **1250** class/interface nodes, **33** with class-specific binary virtual-slot matches, **18** with SDK-association-only anchors, **1199** naming-only families, **278** ctor/dtor records, **18** factory candidates, and **2525** preserved contradictions.

## Evidence policy

- **High:** independent agreement among explicit SDK/header declarations, generated layouts, and address-bearing binary vtable/call evidence.
- **Medium:** several static sources agree, but identity or address boundaries remain inferential.
- **Low:** naming, layout, or repeated pointer data only.
- `SporeApp.exe` has no MSVC RTTI. SDK/header names are reference evidence, not original implementation truth.
- `Release`, `Dispose`, `Delete`, and similar methods are lifecycle methods, not destructors unless a destructor declaration/slot independently exists.
- Contradictions are preserved verbatim in meaning; no alias, duplicate, boundary, or layout disagreement is silently reconciled.

## Address-bearing family trees

These are header-inferred trees restricted to roots whose descendants have binary virtual-slot evidence. Addresses are vtable data addresses, not function entry addresses.

```text
App::Canvas [0x0141ca70, 0x0141cab8, 0x0141cb08, 0x01459c6c, 0x0146576c, 0x01471fdc, 0x01472040, 0x01473528, 0x01473590, 0x0149ad14]
```

```text
App::ICheatManager [no class-specific binary vtable]
└─ App::cCheatManager [0x01459b68, 0x01466c88, 0x01466d00, 0x0146a020, 0x0146a530, 0x0146c100, 0x01471458, 0x014714d0, 0x014727c8, 0x01472a08, 0x01474b54, 0x01474b98]
```

```text
App::IGameMode [no class-specific binary vtable]
├─ App::DefaultGameMode [no class-specific binary vtable]
├─ App::GameSpace [no class-specific binary vtable]
├─ App::cCellModeStrategy [0x01485550]
├─ App::cScenarioMode [no class-specific binary vtable]
├─ IGameModeObject [no class-specific binary vtable]
├─ cCreatureModeStrategy [no class-specific binary vtable]
└─ cEditor [no class-specific binary vtable]
```

```text
App::IPropManager [no class-specific binary vtable]
└─ App::cPropManager [0x014091a0, 0x014091e8]
```

```text
App::IUnmanagedMessageListener [no class-specific binary vtable]
├─ App::cCellModeStrategy [0x01485550]
├─ App::cScenarioMode [no class-specific binary vtable]
├─ App::cSporeApp [no class-specific binary vtable]
├─ Editors::EditorPlayMode [no class-specific binary vtable]
├─ Editors::cSpeciesManager [no class-specific binary vtable]
├─ IMessageListener [no class-specific binary vtable]
│  ├─ App::ICameraManager [no class-specific binary vtable]
│  │  └─ App::cCameraManager [0x014104a4, 0x014106a4]
│  ├─ App::cGameModeManager [no class-specific binary vtable]
│  ├─ App::cPropManager [0x014091a0, 0x014091e8]
│  ├─ DefaultMessageListener [no class-specific binary vtable]
│  │  ├─ ScheduledTaskListener [no class-specific binary vtable]
│  │  └─ UpdateMessageListener [no class-specific binary vtable]
│  └─ LambdaMessageListener [no class-specific binary vtable]
├─ ItemViewer [no class-specific binary vtable]
│  └─ Palettes::AdvancedItemViewer [0x013f9eb8, 0x01489aa0]
├─ Palettes::PaletteSubcategoriesUI [no class-specific binary vtable]
├─ Pollinator::cAchievementsManager [no class-specific binary vtable]
├─ Simulator::cGameDataUFO [no class-specific binary vtable]
├─ Simulator::cGameInputManager [no class-specific binary vtable]
├─ Simulator::cGameModeManager [no class-specific binary vtable]
├─ Simulator::cScenarioData [no class-specific binary vtable]
├─ Simulator::cSimulatorPlayerUFO [no class-specific binary vtable]
├─ Simulator::cSpaceInventoryItem [no class-specific binary vtable]
│  ├─ Simulator::cAnimalCargoInfo [no class-specific binary vtable]
│  ├─ Simulator::cObjectInstanceInventoryItem [no class-specific binary vtable]
│  ├─ Simulator::cPlantCargoInfo [no class-specific binary vtable]
│  └─ Simulator::cSpaceToolData [no class-specific binary vtable]
├─ Simulator::cToolManager [no class-specific binary vtable]
├─ Simulator::cTribeInputStrategy [no class-specific binary vtable]
├─ Skinner::cSkinPainterJobExtractTexture [no class-specific binary vtable]
├─ Thumbnail_cImportExport [no class-specific binary vtable]
├─ UI::GlobalUIUnkBase1 [no class-specific binary vtable]
│  └─ GlobalUI [no class-specific binary vtable]
└─ cScenarioPlayMode [no class-specific binary vtable]
```

```text
App::PropertyList [0x01408820, 0x01408870]
└─ App::DirectPropertyList [0x01408870]
```

```text
DefaultRefCounted [no class-specific binary vtable]
├─ Anim::IAnimWorld [no class-specific binary vtable]
├─ Anim::cAnimManagerImpl [no class-specific binary vtable]
├─ App::ICreatureModeActionHandler [no class-specific binary vtable]
├─ App::ITokenTranslator [no class-specific binary vtable]
│  ├─ App::cStringDetokenizer [no class-specific binary vtable]
│  └─ GlobalUI [no class-specific binary vtable]
├─ App::RefCountedString [no class-specific binary vtable]
├─ App::cLocaleManager [no class-specific binary vtable]
├─ App::cScenarioMode [no class-specific binary vtable]
├─ App::cSporeApp [no class-specific binary vtable]
├─ COMSerializer [no class-specific binary vtable]
├─ CinematicVignetteActionData [no class-specific binary vtable]
├─ DefaultItemFrameUI [no class-specific binary vtable]
│  ├─ OutfitterItemUI [no class-specific binary vtable]
│  └─ Palettes::cSPScenarioBrushItemUI [no class-specific binary vtable]
├─ DefaultWinProc [no class-specific binary vtable]
├─ EditorBaseHandle [no class-specific binary vtable]
├─ EditorRigblock [no class-specific binary vtable]
├─ EditorStateEditHistory [no class-specific binary vtable]
├─ EditorUI [no class-specific binary vtable]
├─ Editors::EditorAnimations [no class-specific binary vtable]
├─ Editors::EditorPlayMode [no class-specific binary vtable]
├─ Editors::EditorPlayModeBackground [no class-specific binary vtable]
├─ Editors::PlayAnimButton [no class-specific binary vtable]
├─ Editors::PlayAnimPanel [no class-specific binary vtable]
├─ Editors::PlayModeActor [no class-specific binary vtable]
├─ Editors::PlayModeUI [no class-specific binary vtable]
├─ Editors::WalkAction [no class-specific binary vtable]
├─ Editors::cEditorAnimEvent [no class-specific binary vtable]
├─ Editors::cEditorSkin [no class-specific binary vtable]
├─ Editors::cSPEditorVerbIcon [no class-specific binary vtable]
├─ Editors::cSPEditorVerbIconTray [no class-specific binary vtable]
├─ Editors::cSPVerbTrayCollection [no class-specific binary vtable]
│  └─ Editors::cSPEditorVerbTrayCollection [no class-specific binary vtable]
├─ GeneratedMesh [no class-specific binary vtable]
├─ Graphics::PlanetThumbnailRequest [no class-specific binary vtable]
├─ Graphics::cRenderTargetManager [no class-specific binary vtable]
├─ ItemViewer [no class-specific binary vtable]
│  └─ Palettes::AdvancedItemViewer [0x013f9eb8, 0x01489aa0]
├─ PageArrowsUI [no class-specific binary vtable]
├─ Palettes::ColorPickerUI [no class-specific binary vtable]
├─ Palettes::ColorSwatchUI [no class-specific binary vtable]
├─ Palettes::PaletteCategory [no class-specific binary vtable]
├─ Palettes::PaletteCategoryUI [no class-specific binary vtable]
├─ Palettes::PaletteItem [no class-specific binary vtable]
├─ Palettes::PaletteIterator [no class-specific binary vtable]
├─ Palettes::PaletteMain [no class-specific binary vtable]
├─ Palettes::PalettePage [no class-specific binary vtable]
├─ Palettes::PalettePageUI [no class-specific binary vtable]
├─ Palettes::PaletteSubcategoriesUI [no class-specific binary vtable]
├─ Palettes::PaletteUI [no class-specific binary vtable]
├─ Palettes::StandardItemUI [no class-specific binary vtable]
├─ SerializerDatabase [no class-specific binary vtable]
├─ Simulator::cBehaviorBase [no class-specific binary vtable]
├─ Simulator::cCreatureDisplayStrategy [no class-specific binary vtable]
├─ Simulator::cGameData [no class-specific binary vtable]
│  ├─ Simulator::cArtilleryProjectile [no class-specific binary vtable]
│  │  └─ Simulator::cSpear [no class-specific binary vtable]
│  ├─ Simulator::cBuilding [no class-specific binary vtable]
│  │  ├─ Simulator::cBuildingCityHall [no class-specific binary vtable]
│  │  ├─ Simulator::cBuildingEntertainment [no class-specific binary vtable]
│  │  ├─ Simulator::cBuildingHouse [no class-specific binary vtable]
│  │  ├─ Simulator::cBuildingIndustry [no class-specific binary vtable]
│  │  └─ Simulator::cBuildingScenario [no class-specific binary vtable]
│  ├─ Simulator::cCelestialBody [no class-specific binary vtable]
│  ├─ Simulator::cCityTerritory [no class-specific binary vtable]
│  ├─ Simulator::cCityWalls [no class-specific binary vtable]
│  ├─ Simulator::cCivilization [no class-specific binary vtable]
│  ├─ Simulator::cCommodityNode [no class-specific binary vtable]
│  ├─ Simulator::cCulturalProjectile [no class-specific binary vtable]
│  ├─ Simulator::cCulturalTarget [no class-specific binary vtable]
│  ├─ Simulator::cDefaultAoEArea [no class-specific binary vtable]
│  ├─ Simulator::cDefaultBeamProjectile [no class-specific binary vtable]
│  ├─ Simulator::cDefaultToolProjectile [no class-specific binary vtable]
│  │  └─ Simulator::cDeepSpaceProjectile [no class-specific binary vtable]
│  ├─ Simulator::cEgg [no class-specific binary vtable]
│  ├─ Simulator::cFlakProjectile [no class-specific binary vtable]
│  ├─ Simulator::cGameBundle [no class-specific binary vtable]
│  ├─ Simulator::cGameDataUFO [no class-specific binary vtable]
│  ├─ Simulator::cGamePlant [no class-specific binary vtable]
│  ├─ Simulator::cGameTerrainCursor [no class-specific binary vtable]
│  ├─ Simulator::cGameplayMarker [no class-specific binary vtable]
│  ├─ Simulator::cICBM [no class-specific binary vtable]
│  ├─ Simulator::cInterCityRoad [no class-specific binary vtable]
│  ├─ Simulator::cInteractableObject [no class-specific binary vtable]
│  │  └─ Simulator::cInteractiveOrnament [no class-specific binary vtable]
│  ├─ Simulator::cMovableDestructibleOrnament [no class-specific binary vtable]
│  │  ├─ Simulator::cPlanetaryArtifact [no class-specific binary vtable]
│  │  └─ Simulator::cToolObject [no class-specific binary vtable]
│  ├─ Simulator::cNest [no class-specific binary vtable]
│  ├─ Simulator::cObstacle [no class-specific binary vtable]
│  ├─ Simulator::cOrnament [no class-specific binary vtable]
│  │  └─ Simulator::cHitSphere [no class-specific binary vtable]
│  │     └─ Simulator::cSolarHitSphere [no class-specific binary vtable]
│  ├─ Simulator::cResourceProjectile [no class-specific binary vtable]
│  ├─ Simulator::cSpaceDefenseMissile [no class-specific binary vtable]
│  ├─ Simulator::cSpaceInventory [no class-specific binary vtable]
│  │  └─ Simulator::cPlayerInventory [no class-specific binary vtable]
│  ├─ Simulator::cStar [no class-specific binary vtable]
│  ├─ Simulator::cTotemPole [no class-specific binary vtable]
│  ├─ Simulator::cTribeFoodMat [no class-specific binary vtable]
│  ├─ Simulator::cTribeHut [no class-specific binary vtable]
│  ├─ Simulator::cTribeTool [no class-specific binary vtable]
│  ├─ Simulator::cTurret [no class-specific binary vtable]
│  ├─ Simulator::cVehicle [no class-specific binary vtable]
│  ├─ Simulator::cVisiblePlanet [no class-specific binary vtable]
│  ├─ cCommunity [no class-specific binary vtable]
│  │  ├─ cCity [no class-specific binary vtable]
│  │  └─ cTribe [no class-specific binary vtable]
│  ├─ cCreatureBase [no class-specific binary vtable]
│  │  ├─ Simulator::cCreatureAnimal [no class-specific binary vtable]
│  │  └─ Simulator::cCreatureCitizen [no class-specific binary vtable]
│  ├─ cGameBundleGroundContainer [no class-specific binary vtable]
│  ├─ cHerd [no class-specific binary vtable]
│  ├─ cMission [no class-specific binary vtable]
│  │  ├─ Simulator::cRaidEvent [no class-specific binary vtable]
│  │  └─ Simulator::cRaidPlunderEvent [no class-specific binary vtable]
│  ├─ cPlanet [no class-specific binary vtable]
│  └─ cPlayer [no class-specific binary vtable]
├─ Simulator::cGameInputManager [no class-specific binary vtable]
├─ Simulator::cGonzagoSimulator [no class-specific binary vtable]
│  ├─ Simulator::cBadgeManager [no class-specific binary vtable]
│  ├─ Simulator::cCombatSimulator [no class-specific binary vtable]
│  ├─ Simulator::cNpcTribeController [no class-specific binary vtable]
│  ├─ Simulator::cScenarioSimulator [no class-specific binary vtable]
│  ├─ Simulator::cSimPlanetHighLOD [no class-specific binary vtable]
│  ├─ Simulator::cSimulatorPlayerUFO [no class-specific binary vtable]
│  ├─ Simulator::cSimulatorSpaceGame [no class-specific binary vtable]
│  ├─ Simulator::cTimeOfDay [no class-specific binary vtable]
│  ├─ cMissionManager [no class-specific binary vtable]
│  ├─ cSimulatorUniverse [no class-specific binary vtable]
│  └─ cTribePlanner [no class-specific binary vtable]
├─ Simulator::cGonzagoTimer [no class-specific binary vtable]
├─ Simulator::cSavedGameHeader [no class-specific binary vtable]
├─ Simulator::cScenarioData [no class-specific binary vtable]
├─ Simulator::cScenarioEditModeDisplayStrategy [no class-specific binary vtable]
├─ Simulator::cScenarioTerraformMode [no class-specific binary vtable]
├─ Simulator::cSolarSystem [no class-specific binary vtable]
├─ Simulator::cSpaceInventoryItem [no class-specific binary vtable]
│  ├─ Simulator::cAnimalCargoInfo [no class-specific binary vtable]
│  ├─ Simulator::cObjectInstanceInventoryItem [no class-specific binary vtable]
│  ├─ Simulator::cPlantCargoInfo [no class-specific binary vtable]
│  └─ Simulator::cSpaceToolData [no class-specific binary vtable]
├─ Simulator::cToolStrategy [0x01416698, 0x014166c4, 0x0141677c, 0x014167a0, 0x014167ec, 0x014168a8, 0x014169bc, 0x014169f0, 0x0141a504, 0x014402c4, 0x01440fbc, 0x0144144c, 0x01441a2c, 0x01442324, 0x01442368, 0x01442490, 0x01442678, 0x01442984, 0x01443020, 0x014431c4, 0x01443570, 0x01443694, 0x014438e0, 0x01443e30, 0x01444068, 0x014441f0, 0x01444408, 0x014447c8, 0x01444c38, 0x01444e64, 0x014451d8, 0x014453ac, 0x01445640, 0x01445b40, 0x014463c4, 0x014529fc, 0x0145c6c0, 0x0145f93c, 0x014624d0, 0x01462510, 0x01462550, 0x01462590, 0x014625d0, 0x01462610, 0x01465fd0, 0x0147affc, 0x0148537c, 0x01489c2c, 0x0148aba8, 0x0148c008, 0x01495584, 0x014955d0, 0x01495654, 0x014956dc, 0x01499b0c, 0x0149b2e0, 0x0149b358, 0x0149b398, 0x0149b3d8, 0x0149b418, 0x0149b458, 0x0149b498, 0x0149b4d8]
│  ├─ Simulator::cArtilleryWeaponStrategy [no class-specific binary vtable]
│  ├─ Simulator::cDefaultAoETool [0x0149b8b4]
│  ├─ Simulator::cDefaultBeamTool [0x0149b810, 0x0149b8b4, 0x0149b900, 0x0149ba30]
│  │  ├─ Simulator::cAbductToolStrategy [no class-specific binary vtable]
│  │  ├─ Simulator::cDropCargoToolStrategy [no class-specific binary vtable]
│  │  ├─ Simulator::cMindEraseToolStrategy [no class-specific binary vtable]
│  │  └─ Simulator::cScanToolStrategy [no class-specific binary vtable]
│  ├─ Simulator::cDefaultProjectileWeapon [no class-specific binary vtable]
│  │  ├─ Simulator::cCropCirclesToolStrategy [no class-specific binary vtable]
│  │  ├─ Simulator::cDeepSpaceProjectileToolStrategy [no class-specific binary vtable]
│  │  ├─ Simulator::cGenesisDeviceToolStrategy [no class-specific binary vtable]
│  │  ├─ Simulator::cPlaceColonyToolStrategy [no class-specific binary vtable]
│  │  └─ Simulator::cPlaceObjectToolStrategy [no class-specific binary vtable]
│  ├─ Simulator::cDragInputProjectileToolStrategy [no class-specific binary vtable]
│  ├─ Simulator::cGetOutOfUFOToolStrategy [0x0149b8b4, 0x0149b900]
│  ├─ Simulator::cGlobalMindEraseToolStrategy [no class-specific binary vtable]
│  ├─ Simulator::cRallyCallToolStrategy [no class-specific binary vtable]
│  ├─ Simulator::cRepairAOEToolStrategy [no class-specific binary vtable]
│  ├─ Simulator::cRepairToolStrategy [no class-specific binary vtable]
│  │  └─ Simulator::cEnergyRepairToolStrategy [no class-specific binary vtable]
│  ├─ Simulator::cToggleToolStrategy [no class-specific binary vtable]
│  ├─ Simulator::cTurretDefenseMissileWeapon [no class-specific binary vtable]
│  └─ Simulator::cTurretFlakWeapon [no class-specific binary vtable]
├─ SporeStdDrawableImageInfo [no class-specific binary vtable]
├─ Sporepedia::OTDB::ISummarizer [no class-specific binary vtable]
├─ Terrain::cTerrainSphereDecal [no class-specific binary vtable]
├─ UI::AssetDiscoveryCard [no class-specific binary vtable]
├─ UI::CursorAttachment [no class-specific binary vtable]
│  └─ UI::CivCommCursorAttachment [no class-specific binary vtable]
├─ UI::EditorNamePanel [no class-specific binary vtable]
├─ UI::ITokenTranslator [no class-specific binary vtable]
├─ UI::Minimap [no class-specific binary vtable]
├─ UI::SpaceGameUI [no class-specific binary vtable]
├─ UI::cLayerManager [no class-specific binary vtable]
├─ UI::cSPAssetView [no class-specific binary vtable]
├─ UI::cSPUILayeredObject [no class-specific binary vtable]
├─ UI::cSPUITextZoom [no class-specific binary vtable]
├─ UILayoutObjects [no class-specific binary vtable]
├─ UTFWin::EventPropertyObject [no class-specific binary vtable]
│  └─ UTFWin::IEventTimeFunction [no class-specific binary vtable]
│     └─ EventTimeFunctionBase [no class-specific binary vtable]
│        ├─ BehaviourTimeOscillator [no class-specific binary vtable]
│        └─ UTFWin::BehaviourTimeRamp [no class-specific binary vtable]
│           └─ BehaviourTimeSmoothRamp [no class-specific binary vtable]
├─ UTFWin::UILayout [no class-specific binary vtable]
├─ VerbIconData [no class-specific binary vtable]
├─ cAssetViewManager [no class-specific binary vtable]
├─ cCollectableItems [no class-specific binary vtable]
├─ cEditor [no class-specific binary vtable]
├─ cEditorsThumbnailInfo [no class-specific binary vtable]
├─ cFeedbackEvent [no class-specific binary vtable]
├─ cGameThumbnailInfo [no class-specific binary vtable]
├─ cPaletteThumbnailInfo [no class-specific binary vtable]
├─ cSPAssetDataOTDB [no class-specific binary vtable]
├─ cSPUILargeAssetView [no class-specific binary vtable]
├─ cSPUIPropertyLayout [no class-specific binary vtable]
├─ cScenarioDataHistoryEntry [no class-specific binary vtable]
├─ cScenarioPlayMode [no class-specific binary vtable]
├─ cScenarioTerraformHistoryEntry [no class-specific binary vtable]
├─ cStarRecord [no class-specific binary vtable]
└─ unknownThumbnailInfo [no class-specific binary vtable]
```

```text
Editors::INameableEntity [no class-specific binary vtable]
├─ Editors::EditorModel [0x013f2194, 0x013f21d8, 0x013f276c, 0x013f2d68, 0x01458024, 0x01458788]
├─ Simulator::cCivilization [no class-specific binary vtable]
├─ Simulator::cScenarioData [no class-specific binary vtable]
├─ cCommunity [no class-specific binary vtable]
│  ├─ cCity [no class-specific binary vtable]
│  └─ cTribe [no class-specific binary vtable]
└─ cEditor [no class-specific binary vtable]
```

```text
IMessageManager [no class-specific binary vtable]
└─ App::cMessageManager [0x01445cb8]
```

```text
IO::EAIOZoneObject [no class-specific binary vtable]
├─ IO::SharedPointer [no class-specific binary vtable]
├─ Resource::Database [no class-specific binary vtable]
│  ├─ DatabasePackedFile [no class-specific binary vtable]
│  ├─ Resource::DatabaseDirectoryFiles [0x014084f0, 0x014086a8, 0x01409630, 0x0140a138, 0x01436700, 0x014367b0, 0x01482d38]
│  └─ SerializerDatabase [no class-specific binary vtable]
├─ Resource::PFIndexModifiable [0x01436878]
└─ Resource::ThreadedObject [no class-specific binary vtable]
   ├─ Resource::IRecord [no class-specific binary vtable]
   │  ├─ Resource::FakeRecord [no class-specific binary vtable]
   │  └─ Resource::PFRecordBase [no class-specific binary vtable]
   │     ├─ Resource::PFRecordRead [0x0140a328, 0x014368c4]
   │     └─ Resource::PFRecordWrite [0x0140a328, 0x014368c4, 0x01436954, 0x01481940]
   └─ Resource::IResourceFactory [no class-specific binary vtable]
      ├─ App::cPropManager [0x014091a0, 0x014091e8]
      └─ UTFWin::cCursorManager [no class-specific binary vtable]
```

```text
IO::IStream [no class-specific binary vtable]
├─ IO::FileStream [0x01436678, 0x0143ca40, 0x0143e670, 0x0143fe78]
├─ IO::FixedMemoryStream [0x0143eafc, 0x0143eb4c]
├─ IO::StreamBuffer [0x0143eaac]
├─ IO::StreamChild [0x0143eaac, 0x0143eafc]
├─ IO::StreamNull [no class-specific binary vtable]
├─ MemoryStream [no class-specific binary vtable]
├─ Resource::PFRecordRead [0x0140a328, 0x014368c4]
├─ Resource::PFRecordWrite [0x0140a328, 0x014368c4, 0x01436954, 0x01481940]
├─ StreamCompressionZLib [no class-specific binary vtable]
└─ StreamDecompressionZLib [no class-specific binary vtable]
```

```text
IO::XmlWriter [0x0143a1c0]
```

```text
IVirtual [no class-specific binary vtable]
├─ App::cCameraManager [0x014104a4, 0x014106a4]
├─ App::cCheatManager [0x01459b68, 0x01466c88, 0x01466d00, 0x0146a020, 0x0146a530, 0x0146c100, 0x01471458, 0x014714d0, 0x014727c8, 0x01472a08, 0x01474b54, 0x01474b98]
├─ App::cGameModeManager [no class-specific binary vtable]
├─ App::cMouseCamera [0x01412890]
├─ EditorRequest [no class-specific binary vtable]
├─ Editors::EditorCamera [0x013f69b4, 0x014105ac, 0x0146b420]
├─ Editors::EditorModel [0x013f2194, 0x013f21d8, 0x013f276c, 0x013f2d68, 0x01458024, 0x01458788]
├─ EffectDirectory [no class-specific binary vtable]
├─ EnterEditorMessage [no class-specific binary vtable]
├─ Graphics::cLayerGroup [no class-specific binary vtable]
├─ Graphics::cMeshData [no class-specific binary vtable]
├─ Graphics::cModelManager [no class-specific binary vtable]
├─ IO::SharedPointer [no class-specific binary vtable]
├─ PlayModeBackgrounds [no class-specific binary vtable]
├─ Simulator::cCommEvent [no class-specific binary vtable]
├─ Simulator::cSimulatorSystem [no class-specific binary vtable]
├─ Swarm::cEffectsManager [no class-specific binary vtable]
├─ Swarm::cEffectsWorld [no class-specific binary vtable]
├─ UnkItemFrameMessage [no class-specific binary vtable]
├─ cCommandParameterSet [no class-specific binary vtable]
├─ cMaterialManager [no class-specific binary vtable]
├─ cMessageCommandDispatcher [no class-specific binary vtable]
├─ cStrategy [no class-specific binary vtable]
│  ├─ Simulator::SubSystem::cLivingUniverse [no class-specific binary vtable]
│  ├─ Simulator::cAnimalSpeciesManager [no class-specific binary vtable]
│  ├─ Simulator::cBundleManager [no class-specific binary vtable]
│  ├─ Simulator::cGameBehaviorManager [no class-specific binary vtable]
│  ├─ Simulator::cGameInputManager [no class-specific binary vtable]
│  ├─ Simulator::cGameModeManager [no class-specific binary vtable]
│  ├─ Simulator::cGameNounManager [no class-specific binary vtable]
│  ├─ Simulator::cGameViewManager [no class-specific binary vtable]
│  ├─ Simulator::cObstacleManager [no class-specific binary vtable]
│  ├─ Simulator::cPlantSpeciesManager [no class-specific binary vtable]
│  ├─ Simulator::cSimTicker [no class-specific binary vtable]
│  ├─ Simulator::cSpaceGfx [no class-specific binary vtable]
│  ├─ Simulator::cTerraformingManager [no class-specific binary vtable]
│  ├─ Simulator::cToolManager [no class-specific binary vtable]
│  ├─ Simulator::cUIAssetDiscoveryManager [no class-specific binary vtable]
│  ├─ cCinematicManager [no class-specific binary vtable]
│  ├─ cCommManager [no class-specific binary vtable]
│  ├─ cGamePersistenceManager [no class-specific binary vtable]
│  ├─ cGameTimeManager [no class-specific binary vtable]
│  ├─ cPlanetModel [no class-specific binary vtable]
│  ├─ cSpaceTrading [no class-specific binary vtable]
│  ├─ cStarManager [no class-specific binary vtable]
│  └─ cUIEventLog [no class-specific binary vtable]
├─ cStringCommandGenerator [no class-specific binary vtable]
└─ cTextureManager [no class-specific binary vtable]
```

```text
Object [no class-specific binary vtable]
├─ App::ICamera [no class-specific binary vtable]
│  ├─ App::DefaultCamera [no class-specific binary vtable]
│  ├─ App::cMouseCamera [0x01412890]
│  └─ Editors::EditorCamera [0x013f69b4, 0x014105ac, 0x0146b420]
├─ App::IStateManager [no class-specific binary vtable]
├─ CinematicVignetteActionData [no class-specific binary vtable]
├─ DefaultObject [no class-specific binary vtable]
├─ EditorBaseHandle [no class-specific binary vtable]
├─ EditorRigblock [no class-specific binary vtable]
├─ Editors::EditorAnimations [no class-specific binary vtable]
├─ Editors::cEditorSkin [no class-specific binary vtable]
├─ IAsyncRequest [no class-specific binary vtable]
├─ ICOMSerializer [no class-specific binary vtable]
│  └─ COMSerializer [no class-specific binary vtable]
├─ ISerializerStream [no class-specific binary vtable]
│  ├─ ISerializerReadStream [no class-specific binary vtable]
│  └─ ISerializerWriteStream [no class-specific binary vtable]
├─ Palettes::ColorPickerUI [no class-specific binary vtable]
├─ Palettes::PaletteCategory [no class-specific binary vtable]
├─ Palettes::PaletteItem [no class-specific binary vtable]
├─ Palettes::PaletteIterator [no class-specific binary vtable]
├─ Palettes::PaletteMain [no class-specific binary vtable]
├─ Palettes::PalettePage [no class-specific binary vtable]
├─ RenderWare::IRwResource [no class-specific binary vtable]
├─ Resource::Database [no class-specific binary vtable]
│  ├─ DatabasePackedFile [no class-specific binary vtable]
│  ├─ Resource::DatabaseDirectoryFiles [0x014084f0, 0x014086a8, 0x01409630, 0x0140a138, 0x01436700, 0x014367b0, 0x01482d38]
│  └─ SerializerDatabase [no class-specific binary vtable]
├─ Resource::ResourceObject [no class-specific binary vtable]
│  ├─ CachedResourceObject [no class-specific binary vtable]
│  ├─ ConversationResource [no class-specific binary vtable]
│  ├─ Editors::cCreatureDataResource [no class-specific binary vtable]
│  ├─ Graphics::GmdlRenderAsset [no class-specific binary vtable]
│  ├─ Graphics::cRwDirectResource [no class-specific binary vtable]
│  ├─ ParameterResource [no class-specific binary vtable]
│  ├─ Pollinator::cAssetMetadata [no class-specific binary vtable]
│  ├─ RenderWare::RenderWareFile [no class-specific binary vtable]
│  ├─ Simulator::cConversation [no class-specific binary vtable]
│  ├─ Simulator::cScenarioResource [no class-specific binary vtable]
│  ├─ Swarm::CollectionResource [no class-specific binary vtable]
│  ├─ cCellResource [no class-specific binary vtable]
│  └─ cTerrainSphere [no class-specific binary vtable]
├─ Simulator::IScenarioEditHistoryEntry [no class-specific binary vtable]
│  ├─ cScenarioDataHistoryEntry [no class-specific binary vtable]
│  └─ cScenarioTerraformHistoryEntry [no class-specific binary vtable]
├─ Simulator::ISerializerDatabase [no class-specific binary vtable]
│  └─ SerializerDatabase [no class-specific binary vtable]
├─ Simulator::ISimulatorSerializable [no class-specific binary vtable]
│  ├─ ISimulatorSerializableRefCounted [no class-specific binary vtable]
│  │  ├─ Simulator::cCellSerializableData [no class-specific binary vtable]
│  │  └─ cEmpire [no class-specific binary vtable]
│  ├─ Simulator::ICityMusic [no class-specific binary vtable]
│  ├─ Simulator::cCommEvent [no class-specific binary vtable]
│  ├─ Simulator::cGameData [no class-specific binary vtable]
│  │  ├─ Simulator::cArtilleryProjectile [no class-specific binary vtable]
│  │  │  └─ Simulator::cSpear [no class-specific binary vtable]
│  │  ├─ Simulator::cBuilding [no class-specific binary vtable]
│  │  │  ├─ Simulator::cBuildingCityHall [no class-specific binary vtable]
│  │  │  ├─ Simulator::cBuildingEntertainment [no class-specific binary vtable]
│  │  │  ├─ Simulator::cBuildingHouse [no class-specific binary vtable]
│  │  │  ├─ Simulator::cBuildingIndustry [no class-specific binary vtable]
│  │  │  └─ Simulator::cBuildingScenario [no class-specific binary vtable]
│  │  ├─ Simulator::cCelestialBody [no class-specific binary vtable]
│  │  ├─ Simulator::cCityTerritory [no class-specific binary vtable]
│  │  ├─ Simulator::cCityWalls [no class-specific binary vtable]
│  │  ├─ Simulator::cCivilization [no class-specific binary vtable]
│  │  ├─ Simulator::cCommodityNode [no class-specific binary vtable]
│  │  ├─ Simulator::cCulturalProjectile [no class-specific binary vtable]
│  │  ├─ Simulator::cCulturalTarget [no class-specific binary vtable]
│  │  ├─ Simulator::cDefaultAoEArea [no class-specific binary vtable]
│  │  ├─ Simulator::cDefaultBeamProjectile [no class-specific binary vtable]
│  │  ├─ Simulator::cDefaultToolProjectile [no class-specific binary vtable]
│  │  │  └─ Simulator::cDeepSpaceProjectile [no class-specific binary vtable]
│  │  ├─ Simulator::cEgg [no class-specific binary vtable]
│  │  ├─ Simulator::cFlakProjectile [no class-specific binary vtable]
│  │  ├─ Simulator::cGameBundle [no class-specific binary vtable]
│  │  ├─ Simulator::cGameDataUFO [no class-specific binary vtable]
│  │  ├─ Simulator::cGamePlant [no class-specific binary vtable]
│  │  ├─ Simulator::cGameTerrainCursor [no class-specific binary vtable]
│  │  ├─ Simulator::cGameplayMarker [no class-specific binary vtable]
│  │  ├─ Simulator::cICBM [no class-specific binary vtable]
│  │  ├─ Simulator::cInterCityRoad [no class-specific binary vtable]
│  │  ├─ Simulator::cInteractableObject [no class-specific binary vtable]
│  │  │  └─ Simulator::cInteractiveOrnament [no class-specific binary vtable]
│  │  ├─ Simulator::cMovableDestructibleOrnament [no class-specific binary vtable]
│  │  │  ├─ Simulator::cPlanetaryArtifact [no class-specific binary vtable]
│  │  │  └─ Simulator::cToolObject [no class-specific binary vtable]
│  │  ├─ Simulator::cNest [no class-specific binary vtable]
│  │  ├─ Simulator::cObstacle [no class-specific binary vtable]
│  │  ├─ Simulator::cOrnament [no class-specific binary vtable]
│  │  │  └─ Simulator::cHitSphere [no class-specific binary vtable]
│  │  │     └─ Simulator::cSolarHitSphere [no class-specific binary vtable]
│  │  ├─ Simulator::cResourceProjectile [no class-specific binary vtable]
│  │  ├─ Simulator::cSpaceDefenseMissile [no class-specific binary vtable]
│  │  ├─ Simulator::cSpaceInventory [no class-specific binary vtable]
│  │  │  └─ Simulator::cPlayerInventory [no class-specific binary vtable]
│  │  ├─ Simulator::cStar [no class-specific binary vtable]
│  │  ├─ Simulator::cTotemPole [no class-specific binary vtable]
│  │  ├─ Simulator::cTribeFoodMat [no class-specific binary vtable]
│  │  ├─ Simulator::cTribeHut [no class-specific binary vtable]
│  │  ├─ Simulator::cTribeTool [no class-specific binary vtable]
│  │  ├─ Simulator::cTurret [no class-specific binary vtable]
│  │  ├─ Simulator::cVehicle [no class-specific binary vtable]
│  │  ├─ Simulator::cVisiblePlanet [no class-specific binary vtable]
│  │  ├─ cCommunity [no class-specific binary vtable]
│  │  │  ├─ cCity [no class-specific binary vtable]
│  │  │  └─ cTribe [no class-specific binary vtable]
│  │  ├─ cCreatureBase [no class-specific binary vtable]
│  │  │  ├─ Simulator::cCreatureAnimal [no class-specific binary vtable]
│  │  │  └─ Simulator::cCreatureCitizen [no class-specific binary vtable]
│  │  ├─ cGameBundleGroundContainer [no class-specific binary vtable]
│  │  ├─ cHerd [no class-specific binary vtable]
│  │  ├─ cMission [no class-specific binary vtable]
│  │  │  ├─ Simulator::cRaidEvent [no class-specific binary vtable]
│  │  │  └─ Simulator::cRaidPlunderEvent [no class-specific binary vtable]
│  │  ├─ cPlanet [no class-specific binary vtable]
│  │  └─ cPlayer [no class-specific binary vtable]
│  ├─ Simulator::cGonzagoSimulator [no class-specific binary vtable]
│  │  ├─ Simulator::cBadgeManager [no class-specific binary vtable]
│  │  ├─ Simulator::cCombatSimulator [no class-specific binary vtable]
│  │  ├─ Simulator::cNpcTribeController [no class-specific binary vtable]
│  │  ├─ Simulator::cScenarioSimulator [no class-specific binary vtable]
│  │  ├─ Simulator::cSimPlanetHighLOD [no class-specific binary vtable]
│  │  ├─ Simulator::cSimulatorPlayerUFO [no class-specific binary vtable]
│  │  ├─ Simulator::cSimulatorSpaceGame [no class-specific binary vtable]
│  │  ├─ Simulator::cTimeOfDay [no class-specific binary vtable]
│  │  ├─ cMissionManager [no class-specific binary vtable]
│  │  ├─ cSimulatorUniverse [no class-specific binary vtable]
│  │  └─ cTribePlanner [no class-specific binary vtable]
│  ├─ Simulator::cNPCStore [no class-specific binary vtable]
│  ├─ Simulator::cSavedGameHeader [no class-specific binary vtable]
│  ├─ Simulator::cShipBackgroundData [no class-specific binary vtable]
│  ├─ Simulator::cSolarSystem [no class-specific binary vtable]
│  ├─ Simulator::cSpaceInventoryItem [no class-specific binary vtable]
│  │  ├─ Simulator::cAnimalCargoInfo [no class-specific binary vtable]
│  │  ├─ Simulator::cObjectInstanceInventoryItem [no class-specific binary vtable]
│  │  ├─ Simulator::cPlantCargoInfo [no class-specific binary vtable]
│  │  └─ Simulator::cSpaceToolData [no class-specific binary vtable]
│  ├─ cCollectableItems [no class-specific binary vtable]
│  ├─ cGonzagoSubsystem [no class-specific binary vtable]
│  │  └─ cSpeciesRelationshipManager [no class-specific binary vtable]
│  ├─ cRelationshipManager [no class-specific binary vtable]
│  ├─ cSPAchievementSerializer [no class-specific binary vtable]
│  └─ cStarRecord [no class-specific binary vtable]
├─ Simulator::cBehaviorBase [no class-specific binary vtable]
├─ Simulator::cToolStrategy [0x01416698, 0x014166c4, 0x0141677c, 0x014167a0, 0x014167ec, 0x014168a8, 0x014169bc, 0x014169f0, 0x0141a504, 0x014402c4, 0x01440fbc, 0x0144144c, 0x01441a2c, 0x01442324, 0x01442368, 0x01442490, 0x01442678, 0x01442984, 0x01443020, 0x014431c4, 0x01443570, 0x01443694, 0x014438e0, 0x01443e30, 0x01444068, 0x014441f0, 0x01444408, 0x014447c8, 0x01444c38, 0x01444e64, 0x014451d8, 0x014453ac, 0x01445640, 0x01445b40, 0x014463c4, 0x014529fc, 0x0145c6c0, 0x0145f93c, 0x014624d0, 0x01462510, 0x01462550, 0x01462590, 0x014625d0, 0x01462610, 0x01465fd0, 0x0147affc, 0x0148537c, 0x01489c2c, 0x0148aba8, 0x0148c008, 0x01495584, 0x014955d0, 0x01495654, 0x014956dc, 0x01499b0c, 0x0149b2e0, 0x0149b358, 0x0149b398, 0x0149b3d8, 0x0149b418, 0x0149b458, 0x0149b498, 0x0149b4d8]
│  ├─ Simulator::cArtilleryWeaponStrategy [no class-specific binary vtable]
│  ├─ Simulator::cDefaultAoETool [0x0149b8b4]
│  ├─ Simulator::cDefaultBeamTool [0x0149b810, 0x0149b8b4, 0x0149b900, 0x0149ba30]
│  │  ├─ Simulator::cAbductToolStrategy [no class-specific binary vtable]
│  │  ├─ Simulator::cDropCargoToolStrategy [no class-specific binary vtable]
│  │  ├─ Simulator::cMindEraseToolStrategy [no class-specific binary vtable]
│  │  └─ Simulator::cScanToolStrategy [no class-specific binary vtable]
│  ├─ Simulator::cDefaultProjectileWeapon [no class-specific binary vtable]
│  │  ├─ Simulator::cCropCirclesToolStrategy [no class-specific binary vtable]
│  │  ├─ Simulator::cDeepSpaceProjectileToolStrategy [no class-specific binary vtable]
│  │  ├─ Simulator::cGenesisDeviceToolStrategy [no class-specific binary vtable]
│  │  ├─ Simulator::cPlaceColonyToolStrategy [no class-specific binary vtable]
│  │  └─ Simulator::cPlaceObjectToolStrategy [no class-specific binary vtable]
│  ├─ Simulator::cDragInputProjectileToolStrategy [no class-specific binary vtable]
│  ├─ Simulator::cGetOutOfUFOToolStrategy [0x0149b8b4, 0x0149b900]
│  ├─ Simulator::cGlobalMindEraseToolStrategy [no class-specific binary vtable]
│  ├─ Simulator::cRallyCallToolStrategy [no class-specific binary vtable]
│  ├─ Simulator::cRepairAOEToolStrategy [no class-specific binary vtable]
│  ├─ Simulator::cRepairToolStrategy [no class-specific binary vtable]
│  │  └─ Simulator::cEnergyRepairToolStrategy [no class-specific binary vtable]
│  ├─ Simulator::cToggleToolStrategy [no class-specific binary vtable]
│  ├─ Simulator::cTurretDefenseMissileWeapon [no class-specific binary vtable]
│  └─ Simulator::cTurretFlakWeapon [no class-specific binary vtable]
├─ UTFWin::IWinProc [no class-specific binary vtable]
│  ├─ DefaultWinProc [no class-specific binary vtable]
│  ├─ EditorUI [no class-specific binary vtable]
│  ├─ Editors::PlayModeUI [no class-specific binary vtable]
│  ├─ Editors::cSPEditorVerbIcon [no class-specific binary vtable]
│  ├─ Editors::cSPEditorVerbIconTray [no class-specific binary vtable]
│  ├─ Editors::cSPVerbTrayCollection [no class-specific binary vtable]
│  │  └─ Editors::cSPEditorVerbTrayCollection [no class-specific binary vtable]
│  ├─ GameCiv::GameCiv [no class-specific binary vtable]
│  ├─ IAdvancedItemUI [no class-specific binary vtable]
│  │  └─ DefaultItemFrameUI [no class-specific binary vtable]
│  │     ├─ OutfitterItemUI [no class-specific binary vtable]
│  │     └─ Palettes::cSPScenarioBrushItemUI [no class-specific binary vtable]
│  ├─ ItemViewer [no class-specific binary vtable]
│  │  └─ Palettes::AdvancedItemViewer [0x013f9eb8, 0x01489aa0]
│  ├─ LambdaProc [no class-specific binary vtable]
│  │  └─ LambdaFilterProc [no class-specific binary vtable]
│  ├─ PageArrowsUI [no class-specific binary vtable]
│  ├─ Palettes::ColorSwatchUI [no class-specific binary vtable]
│  ├─ Palettes::PaletteCategoryUI [no class-specific binary vtable]
│  ├─ Palettes::PalettePageUI [no class-specific binary vtable]
│  ├─ Palettes::PaletteSubcategoriesUI [no class-specific binary vtable]
│  ├─ Palettes::PaletteUI [no class-specific binary vtable]
│  ├─ Palettes::StandardItemUI [no class-specific binary vtable]
│  ├─ Simulator::cCreatureDisplayStrategy [no class-specific binary vtable]
│  ├─ Simulator::cScenarioEditModeDisplayStrategy [no class-specific binary vtable]
│  ├─ UI::CursorAttachment [no class-specific binary vtable]
│  │  └─ UI::CivCommCursorAttachment [no class-specific binary vtable]
│  ├─ UI::EditorNamePanel [no class-specific binary vtable]
│  ├─ UI::SpaceGameUI [no class-specific binary vtable]
│  ├─ UI::SpaceToolPanelUI [no class-specific binary vtable]
│  ├─ UI::cSPAssetView [no class-specific binary vtable]
│  ├─ UTFWin::InteractiveWinProc [no class-specific binary vtable]
│  │  ├─ Effect [no class-specific binary vtable]
│  │  │  ├─ BiStateEffect [no class-specific binary vtable]
│  │  │  │  ├─ GlideEffect [no class-specific binary vtable]
│  │  │  │  ├─ InflateEffect [no class-specific binary vtable]
│  │  │  │  ├─ ModulateEffect [no class-specific binary vtable]
│  │  │  │  ├─ RotateEffect [no class-specific binary vtable]
│  │  │  │  └─ UTFWin::FadeEffect [no class-specific binary vtable]
│  │  │  ├─ CascadeEffect [no class-specific binary vtable]
│  │  │  └─ PerspectiveEffect [no class-specific binary vtable]
│  │  ├─ SimpleLayout [no class-specific binary vtable]
│  │  ├─ SporeTooltipWinProc [no class-specific binary vtable]
│  │  └─ UTFWin::ProportionalLayout [0x014436f8]
│  ├─ cAssetViewManager [no class-specific binary vtable]
│  ├─ cSPUILargeAssetView [no class-specific binary vtable]
│  ├─ cSPUIPropertyLayout [no class-specific binary vtable]
│  └─ cUIEventLog [no class-specific binary vtable]
├─ UTFWin::LayoutReader [no class-specific binary vtable]
├─ UTFWin::UTFWinObject [0x013fa72c, 0x013fa794, 0x013fa7d8, 0x013fa810, 0x013fa8b0, 0x013fa8f0, 0x013fa974, 0x013fb2b8, 0x013fb2f8, 0x013fb408, 0x013fb448, 0x013fcc08, 0x013fcc48, 0x013fdc38, 0x013fec40, 0x013fef58, 0x013fef9c, 0x013fefe0, 0x013ff508, 0x0140b5e8, 0x014105ac, 0x01412b9c, 0x01414b10, 0x01414ce0, 0x01414fd0, 0x01415298, 0x014152dc, 0x014179b8, 0x01417a68, 0x01417bc0, 0x014184e4, 0x01418544, 0x01418838, 0x01418d00, 0x01418f00, 0x014191d0, 0x01419214, 0x01419408, 0x0141944c, 0x014196a8, 0x014196ec, 0x01419794, 0x01419a40, 0x01419c70, 0x01419fd0, 0x0141a024, 0x0141a068, 0x0141a538, 0x0141a57c, 0x0141a5c0, 0x0141a614, 0x0141a658, 0x0141a998, 0x0141ac90, 0x0141af08, 0x01440d88, 0x01441094, 0x01441240, 0x01441284, 0x014414b8, 0x01441890, 0x01441c18, 0x01441fd8, 0x0144203c, 0x014421c8, 0x014422a4, 0x01442324, 0x01442368, 0x01442584, 0x01442604, 0x01442648, 0x01442f10, 0x01443318, 0x0144335c, 0x0144347c, 0x014434fc, 0x01443540, 0x014436f8, 0x014437e8, 0x01443be8, 0x01443c4c, 0x01443d90, 0x01443f78, 0x014440d0, 0x01444220, 0x01444314, 0x01444364, 0x014443a4, 0x014446f0, 0x01444754, 0x01444b68, 0x01445060, 0x01445530, 0x014459c0, 0x01445e60, 0x01446078, 0x014462b0, 0x01446590, 0x01458024, 0x01458788, 0x0145d758, 0x014793e0, 0x01479424, 0x0147e9d0, 0x0147ea70, 0x0147f868, 0x0147f8ac, 0x0147fa30, 0x0147fce0, 0x014805b8, 0x014805fc, 0x014806b8, 0x014806f8, 0x014807dc, 0x01480820, 0x014808c0, 0x01480904, 0x014809d0, 0x01480a14, 0x01480ae0, 0x01480b24, 0x01480bf0, 0x01480c34, 0x01480d00, 0x01480d44, 0x01480e10, 0x01480e54, 0x014819b0, 0x01489738, 0x0148977c, 0x01489930, 0x0148998c, 0x01489d44, 0x01489d9c, 0x01489de0, 0x01495960, 0x014959b8, 0x01495a40]
│  ├─ IBiStateEffect [no class-specific binary vtable]
│  │  ├─ BiStateEffect [no class-specific binary vtable]
│  │  │  ├─ GlideEffect [no class-specific binary vtable]
│  │  │  ├─ InflateEffect [no class-specific binary vtable]
│  │  │  ├─ ModulateEffect [no class-specific binary vtable]
│  │  │  ├─ RotateEffect [no class-specific binary vtable]
│  │  │  └─ UTFWin::FadeEffect [no class-specific binary vtable]
│  │  └─ UTFWin::IGlideEffect [no class-specific binary vtable]
│  │     └─ GlideEffect [no class-specific binary vtable]
│  ├─ IButton [no class-specific binary vtable]
│  ├─ IButtonDrawable [no class-specific binary vtable]
│  │  ├─ UTFWin::ButtonDrawableRadio [0x0141785c, 0x01441094]
│  │  └─ UTFWin::ButtonDrawableStandard [no class-specific binary vtable]
│  ├─ IComboBox [no class-specific binary vtable]
│  ├─ IDialogDrawable [no class-specific binary vtable]
│  │  └─ DialogDrawable [no class-specific binary vtable]
│  ├─ IDrawable [no class-specific binary vtable]
│  │  ├─ ComboBoxDrawable [no class-specific binary vtable]
│  │  ├─ DefaultDrawable [no class-specific binary vtable]
│  │  ├─ DialogDrawable [no class-specific binary vtable]
│  │  ├─ FrameDrawable [no class-specific binary vtable]
│  │  ├─ ImageDrawable [no class-specific binary vtable]
│  │  ├─ ScrollbarDrawable [no class-specific binary vtable]
│  │  ├─ SliderDrawable [no class-specific binary vtable]
│  │  ├─ SpinnerDrawable [no class-specific binary vtable]
│  │  ├─ StdDrawable [no class-specific binary vtable]
│  │  │  └─ UTFWin::SporeStdDrawable [no class-specific binary vtable]
│  │  ├─ UTFWin::ButtonDrawableRadio [0x0141785c, 0x01441094]
│  │  ├─ UTFWin::ButtonDrawableStandard [no class-specific binary vtable]
│  │  └─ UTFWin::VariableWidthDrawable [no class-specific binary vtable]
│  ├─ IImageDrawable [no class-specific binary vtable]
│  │  └─ ImageDrawable [no class-specific binary vtable]
│  ├─ ILayoutElement [no class-specific binary vtable]
│  │  ├─ DefaultLayoutElement [no class-specific binary vtable]
│  │  │  ├─ ComboBoxDrawable [no class-specific binary vtable]
│  │  │  ├─ DialogDrawable [no class-specific binary vtable]
│  │  │  ├─ FrameDrawable [no class-specific binary vtable]
│  │  │  ├─ ImageDrawable [no class-specific binary vtable]
│  │  │  ├─ ScrollbarDrawable [no class-specific binary vtable]
│  │  │  ├─ SliderDrawable [no class-specific binary vtable]
│  │  │  ├─ SpinnerDrawable [no class-specific binary vtable]
│  │  │  ├─ StdDrawable [no class-specific binary vtable]
│  │  │  │  └─ UTFWin::SporeStdDrawable [no class-specific binary vtable]
│  │  │  ├─ UTFWin::ButtonDrawableRadio [0x0141785c, 0x01441094]
│  │  │  ├─ UTFWin::ButtonDrawableStandard [no class-specific binary vtable]
│  │  │  └─ UTFWin::VariableWidthDrawable [no class-specific binary vtable]
│  │  ├─ SporeStdDrawableImageInfo [no class-specific binary vtable]
│  │  ├─ TreeNode [no class-specific binary vtable]
│  │  ├─ UTFWin::EventPropertyObject [no class-specific binary vtable]
│  │  │  └─ UTFWin::IEventTimeFunction [no class-specific binary vtable]
│  │  │     └─ EventTimeFunctionBase [no class-specific binary vtable]
│  │  │        ├─ BehaviourTimeOscillator [no class-specific binary vtable]
│  │  │        └─ UTFWin::BehaviourTimeRamp [no class-specific binary vtable]
│  │  │           └─ BehaviourTimeSmoothRamp [no class-specific binary vtable]
│  │  ├─ UTFWin::Image [0x0141aa84, 0x014404cc]
│  │  ├─ UTFWin::InteractiveWinProc [no class-specific binary vtable]
│  │  │  ├─ Effect [no class-specific binary vtable]
│  │  │  │  ├─ BiStateEffect [no class-specific binary vtable]
│  │  │  │  │  ├─ GlideEffect [no class-specific binary vtable]
│  │  │  │  │  ├─ InflateEffect [no class-specific binary vtable]
│  │  │  │  │  ├─ ModulateEffect [no class-specific binary vtable]
│  │  │  │  │  ├─ RotateEffect [no class-specific binary vtable]
│  │  │  │  │  └─ UTFWin::FadeEffect [no class-specific binary vtable]
│  │  │  │  ├─ CascadeEffect [no class-specific binary vtable]
│  │  │  │  └─ PerspectiveEffect [no class-specific binary vtable]
│  │  │  ├─ SimpleLayout [no class-specific binary vtable]
│  │  │  ├─ SporeTooltipWinProc [no class-specific binary vtable]
│  │  │  └─ UTFWin::ProportionalLayout [0x014436f8]
│  │  └─ UTFWin::Window [0x013f57a4, 0x013fdb18, 0x013fdb6c, 0x013fdbe4, 0x0140f854, 0x01414b10, 0x01414bc0, 0x01414c14, 0x01414c8c, 0x01414ce0, 0x01414ed4, 0x01414f38, 0x01414f7c, 0x01415178, 0x014151cc, 0x01415244, 0x014186c4, 0x0141873c, 0x014187a0, 0x014187e4, 0x01418838, 0x01419040, 0x014190d4, 0x01419138, 0x0141917c, 0x01419278, 0x0141930c, 0x01419370, 0x014193b4, 0x01419518, 0x014195ac, 0x01419610, 0x01419654, 0x01419920, 0x01419974, 0x014199ec, 0x01419b50, 0x01419ba4, 0x01419c1c, 0x0141ab34, 0x0141ab94, 0x0141abf8, 0x0141ac3c, 0x01440448, 0x0144064c, 0x01440b1c, 0x014410b0, 0x01441144, 0x014411a8, 0x014411ec, 0x01441748, 0x01441794, 0x014417f8, 0x0144183c, 0x01441af8, 0x01441b4c, 0x01441bc4, 0x01441c18, 0x01441e48, 0x01441edc, 0x01441f40, 0x01441f84, 0x01442df0, 0x01442e44, 0x01442ebc, 0x014431f8, 0x0144324c, 0x014432c4, 0x01443318, 0x01443a58, 0x01443aec, 0x01443b50, 0x01443b94, 0x014445d0, 0x01444624, 0x0144469c, 0x01444a48, 0x01444a9c, 0x01444b14, 0x01444f40, 0x01444f94, 0x0144500c, 0x01445410, 0x01445464, 0x014454dc, 0x014458c4, 0x01445928, 0x0144596c, 0x01445cb8, 0x01445d40, 0x01445d94, 0x01445e0c, 0x01445f58, 0x01445fac, 0x01446024, 0x01446078, 0x0144618c, 0x014461e4, 0x0144625c, 0x014462b0, 0x01446470, 0x014464c4, 0x0144653c, 0x0145d638, 0x0145d68c, 0x0145d704, 0x0145d758, 0x014792c0, 0x01479314, 0x0147938c, 0x014793e0, 0x0147f6d8, 0x0147f76c, 0x0147f7d0, 0x0147f814, 0x0147f910, 0x0147f964, 0x0147f9dc, 0x0147fa30, 0x0147fb9c, 0x0147fbe4, 0x0147fc48, 0x0147fc8c]
│  │     ├─ UI::Minimap [no class-specific binary vtable]
│  │     ├─ UTFWin::InteractiveWindow [no class-specific binary vtable]
│  │     │  └─ UTFWin::WinTreeView [no class-specific binary vtable]
│  │     └─ UTFWin::SporeAnimatedIconWin [no class-specific binary vtable]
│  ├─ ITextEdit [no class-specific binary vtable]
│  ├─ IWindow [no class-specific binary vtable]
│  │  └─ UTFWin::Window [0x013f57a4, 0x013fdb18, 0x013fdb6c, 0x013fdbe4, 0x0140f854, 0x01414b10, 0x01414bc0, 0x01414c14, 0x01414c8c, 0x01414ce0, 0x01414ed4, 0x01414f38, 0x01414f7c, 0x01415178, 0x014151cc, 0x01415244, 0x014186c4, 0x0141873c, 0x014187a0, 0x014187e4, 0x01418838, 0x01419040, 0x014190d4, 0x01419138, 0x0141917c, 0x01419278, 0x0141930c, 0x01419370, 0x014193b4, 0x01419518, 0x014195ac, 0x01419610, 0x01419654, 0x01419920, 0x01419974, 0x014199ec, 0x01419b50, 0x01419ba4, 0x01419c1c, 0x0141ab34, 0x0141ab94, 0x0141abf8, 0x0141ac3c, 0x01440448, 0x0144064c, 0x01440b1c, 0x014410b0, 0x01441144, 0x014411a8, 0x014411ec, 0x01441748, 0x01441794, 0x014417f8, 0x0144183c, 0x01441af8, 0x01441b4c, 0x01441bc4, 0x01441c18, 0x01441e48, 0x01441edc, 0x01441f40, 0x01441f84, 0x01442df0, 0x01442e44, 0x01442ebc, 0x014431f8, 0x0144324c, 0x014432c4, 0x01443318, 0x01443a58, 0x01443aec, 0x01443b50, 0x01443b94, 0x014445d0, 0x01444624, 0x0144469c, 0x01444a48, 0x01444a9c, 0x01444b14, 0x01444f40, 0x01444f94, 0x0144500c, 0x01445410, 0x01445464, 0x014454dc, 0x014458c4, 0x01445928, 0x0144596c, 0x01445cb8, 0x01445d40, 0x01445d94, 0x01445e0c, 0x01445f58, 0x01445fac, 0x01446024, 0x01446078, 0x0144618c, 0x014461e4, 0x0144625c, 0x014462b0, 0x01446470, 0x014464c4, 0x0144653c, 0x0145d638, 0x0145d68c, 0x0145d704, 0x0145d758, 0x014792c0, 0x01479314, 0x0147938c, 0x014793e0, 0x0147f6d8, 0x0147f76c, 0x0147f7d0, 0x0147f814, 0x0147f910, 0x0147f964, 0x0147f9dc, 0x0147fa30, 0x0147fb9c, 0x0147fbe4, 0x0147fc48, 0x0147fc8c]
│  │     ├─ UI::Minimap [no class-specific binary vtable]
│  │     ├─ UTFWin::InteractiveWindow [no class-specific binary vtable]
│  │     │  └─ UTFWin::WinTreeView [no class-specific binary vtable]
│  │     └─ UTFWin::SporeAnimatedIconWin [no class-specific binary vtable]
│  ├─ UTFWin::ICascadeEffect [no class-specific binary vtable]
│  │  └─ CascadeEffect [no class-specific binary vtable]
│  ├─ UTFWin::IComboBoxDrawable [no class-specific binary vtable]
│  │  └─ ComboBoxDrawable [no class-specific binary vtable]
│  ├─ UTFWin::IDialog [no class-specific binary vtable]
│  ├─ UTFWin::IInflateEffect [no class-specific binary vtable]
│  │  └─ InflateEffect [no class-specific binary vtable]
│  ├─ UTFWin::ILayoutStyle [no class-specific binary vtable]
│  │  ├─ SimpleLayout [no class-specific binary vtable]
│  │  └─ UTFWin::ProportionalLayout [0x014436f8]
│  ├─ UTFWin::IModulateEffect [no class-specific binary vtable]
│  │  └─ ModulateEffect [no class-specific binary vtable]
│  ├─ UTFWin::IPerspectiveEffect [no class-specific binary vtable]
│  │  └─ PerspectiveEffect [no class-specific binary vtable]
│  ├─ UTFWin::IRotateEffect [no class-specific binary vtable]
│  │  └─ RotateEffect [no class-specific binary vtable]
│  ├─ UTFWin::IScrollbarDrawable [no class-specific binary vtable]
│  │  └─ ScrollbarDrawable [no class-specific binary vtable]
│  ├─ UTFWin::ISlider [no class-specific binary vtable]
│  ├─ UTFWin::ISliderDrawable [no class-specific binary vtable]
│  │  └─ SliderDrawable [no class-specific binary vtable]
│  ├─ UTFWin::ISpinnerDrawable [no class-specific binary vtable]
│  │  └─ SpinnerDrawable [no class-specific binary vtable]
│  ├─ UTFWin::IStdDrawable [no class-specific binary vtable]
│  │  └─ StdDrawable [no class-specific binary vtable]
│  │     └─ UTFWin::SporeStdDrawable [no class-specific binary vtable]
│  ├─ UTFWin::IText [no class-specific binary vtable]
│  └─ UTFWin::ITreeView [no class-specific binary vtable]
│     └─ UTFWin::WinTreeView [no class-specific binary vtable]
├─ VerbIconData [no class-specific binary vtable]
├─ cCommandParameterSet [no class-specific binary vtable]
├─ cMessageCommandDispatcher [no class-specific binary vtable]
├─ cObjectTemplateDB [no class-specific binary vtable]
├─ cSPAssetDataOTDB [no class-specific binary vtable]
└─ cStringCommandGenerator [no class-specific binary vtable]
```

```text
Resource::IResourceManager [no class-specific binary vtable]
└─ Resource::cResourceManager [0x01436ae8]
```

```text
Window_intrusive_list_node [no class-specific binary vtable]
└─ IWindow [no class-specific binary vtable]
   └─ UTFWin::Window [0x013f57a4, 0x013fdb18, 0x013fdb6c, 0x013fdbe4, 0x0140f854, 0x01414b10, 0x01414bc0, 0x01414c14, 0x01414c8c, 0x01414ce0, 0x01414ed4, 0x01414f38, 0x01414f7c, 0x01415178, 0x014151cc, 0x01415244, 0x014186c4, 0x0141873c, 0x014187a0, 0x014187e4, 0x01418838, 0x01419040, 0x014190d4, 0x01419138, 0x0141917c, 0x01419278, 0x0141930c, 0x01419370, 0x014193b4, 0x01419518, 0x014195ac, 0x01419610, 0x01419654, 0x01419920, 0x01419974, 0x014199ec, 0x01419b50, 0x01419ba4, 0x01419c1c, 0x0141ab34, 0x0141ab94, 0x0141abf8, 0x0141ac3c, 0x01440448, 0x0144064c, 0x01440b1c, 0x014410b0, 0x01441144, 0x014411a8, 0x014411ec, 0x01441748, 0x01441794, 0x014417f8, 0x0144183c, 0x01441af8, 0x01441b4c, 0x01441bc4, 0x01441c18, 0x01441e48, 0x01441edc, 0x01441f40, 0x01441f84, 0x01442df0, 0x01442e44, 0x01442ebc, 0x014431f8, 0x0144324c, 0x014432c4, 0x01443318, 0x01443a58, 0x01443aec, 0x01443b50, 0x01443b94, 0x014445d0, 0x01444624, 0x0144469c, 0x01444a48, 0x01444a9c, 0x01444b14, 0x01444f40, 0x01444f94, 0x0144500c, 0x01445410, 0x01445464, 0x014454dc, 0x014458c4, 0x01445928, 0x0144596c, 0x01445cb8, 0x01445d40, 0x01445d94, 0x01445e0c, 0x01445f58, 0x01445fac, 0x01446024, 0x01446078, 0x0144618c, 0x014461e4, 0x0144625c, 0x014462b0, 0x01446470, 0x014464c4, 0x0144653c, 0x0145d638, 0x0145d68c, 0x0145d704, 0x0145d758, 0x014792c0, 0x01479314, 0x0147938c, 0x014793e0, 0x0147f6d8, 0x0147f76c, 0x0147f7d0, 0x0147f814, 0x0147f910, 0x0147f964, 0x0147f9dc, 0x0147fa30, 0x0147fb9c, 0x0147fbe4, 0x0147fc48, 0x0147fc8c]
      ├─ UI::Minimap [no class-specific binary vtable]
      ├─ UTFWin::InteractiveWindow [no class-specific binary vtable]
      │  └─ UTFWin::WinTreeView [no class-specific binary vtable]
      └─ UTFWin::SporeAnimatedIconWin [no class-specific binary vtable]
```

### Binary shared-prefix trees

```text
0x3fa974 <ambiguous owner>
  └─ 0x3fa794 <ambiguous owner> (+9 slots; prefix 21)
  └─ 0x3fef9c <ambiguous owner> (+3 slots; prefix 21)
  └─ 0x41a024 <ambiguous owner> (+5 slots; prefix 21)
  └─ 0x442324 Simulator::cToolStrategy (+7 slots; prefix 21)
  └─ 0x442604 <ambiguous owner> (+3 slots; prefix 21)
  └─ 0x4434fc <ambiguous owner> (+3 slots; prefix 21)
0x419794 <ambiguous owner>
  └─ 0x3fa794 <ambiguous owner> (+9 slots; prefix 21)
  └─ 0x3fef9c <ambiguous owner> (+3 slots; prefix 21)
  └─ 0x41a024 <ambiguous owner> (+5 slots; prefix 21)
  └─ 0x442324 Simulator::cToolStrategy (+7 slots; prefix 21)
  └─ 0x442604 <ambiguous owner> (+3 slots; prefix 21)
  └─ 0x4434fc <ambiguous owner> (+3 slots; prefix 21)
```

## Common bases

| Base | Role | Explicit derived | Binary evidence | Confidence |
|---|---|---:|---|---|
| `Anim::IAnimManager` | interface_or_abstract_base | 1 | — | high |
| `App::IAppSystem` | interface_or_abstract_base | 1 | — | high |
| `App::ICamera` | interface_or_abstract_base | 3 | — | high |
| `App::ICameraManager` | interface_or_abstract_base | 1 | — | high |
| `App::ICheatManager` | interface_or_abstract_base | 1 | — | high |
| `App::IConfigManager` | interface_or_abstract_base | 1 | — | high |
| `App::IGameMode` | interface_or_abstract_base | 7 | — | high |
| `App::IMessageRC` | interface_or_abstract_base | 2 | — | high |
| `App::IPropManager` | interface_or_abstract_base | 1 | — | high |
| `App::ISPClassFactory` | interface_or_abstract_base | 1 | — | high |
| `App::ITokenTranslator` | interface_or_abstract_base | 2 | — | high |
| `App::IUnmanagedMessageListener` | interface_or_abstract_base | 21 | — | high |
| `App::PropertyList` | interface_or_abstract_base | 1 | 0x01408820, 0x01408870 | high |
| `ArgScript::IParser` | interface_or_abstract_base | 4 | — | high |
| `BiStateEffect` | common_concrete_base | 5 | — | medium |
| `DefaultItemFrameUI` | common_concrete_base | 2 | — | medium |
| `DefaultLayoutElement` | common_concrete_base | 11 | — | medium |
| `DefaultMessageListener` | common_concrete_base | 2 | — | medium |
| `DefaultRefCounted` | interface_or_abstract_base | 92 | — | high |
| `Editors::IEditorLimits` | interface_or_abstract_base | 3 | — | high |
| `Editors::INameableEntity` | interface_or_abstract_base | 5 | — | high |
| `Editors::IRefCounted` | interface_or_abstract_base | 1 | — | high |
| `Editors::_EditorUI_interface` | interface_or_abstract_base | 1 | — | high |
| `Editors::cEditorSkinMeshBase` | common_concrete_base | 1 | — | high |
| `Editors::cSPVerbTrayCollection` | common_concrete_base | 1 | — | medium |
| `Effect` | common_concrete_base | 3 | — | medium |
| `EventTimeFunctionBase` | common_concrete_base | 2 | — | medium |
| `GlobalUIUnkBase2` | common_concrete_base | 1 | — | medium |
| `Graphics::IAmbientOccluder` | interface_or_abstract_base | 2 | — | high |
| `Graphics::ILayer` | interface_or_abstract_base | 10 | — | high |
| `Graphics::MaterialShader` | common_concrete_base | 2 | — | high |
| `Graphics::cImageData` | interface_or_abstract_base | 1 | — | high |
| `IAdvancedItemUI` | interface_or_abstract_base | 1 | — | medium |
| `IBiStateEffect` | common_concrete_base | 2 | — | medium |
| `IButtonDrawable` | common_concrete_base | 2 | — | medium |
| `ICOMSerializer` | common_concrete_base | 1 | — | medium |
| `IComponent` | common_concrete_base | 1 | — | medium |
| `ICoreAllocator` | interface_or_abstract_base | 1 | — | high |
| `IDialogDrawable` | common_concrete_base | 1 | — | medium |
| `IDrawable` | common_concrete_base | 12 | — | medium |
| `IEffectDirectory` | common_concrete_base | 1 | — | medium |
| `IEffectsWorld` | common_concrete_base | 1 | — | medium |
| `IGameModeManager` | common_concrete_base | 1 | — | medium |
| `IGonzagoSubsystem` | common_concrete_base | 1 | — | medium |
| `IImageDrawable` | common_concrete_base | 1 | — | medium |
| `ILayoutElement` | common_concrete_base | 7 | — | medium |
| `IMaterialManager` | common_concrete_base | 1 | — | medium |
| `IMessageListener` | common_concrete_base | 5 | — | medium |
| `IMessageManager` | common_concrete_base | 1 | — | medium |
| `IMessageParameters` | common_concrete_base | 1 | — | medium |
| `IModelManager` | common_concrete_base | 1 | — | medium |
| `IModelWorld` | common_concrete_base | 1 | — | medium |
| `IO::EAIOZoneObject` | interface_or_abstract_base | 4 | — | high |
| `IO::IStream` | interface_or_abstract_base | 10 | — | high |
| `IRenderTargetManager` | common_concrete_base | 1 | — | medium |
| `ISerializerStream` | interface_or_abstract_base | 2 | — | medium |
| `ISimulatorSerializableRefCounted` | interface_or_abstract_base | 2 | — | medium |
| `ITextureManager` | common_concrete_base | 1 | — | medium |
| `ITextureParticleStreamer` | common_concrete_base | 1 | — | medium |
| `IThumbnailManager` | common_concrete_base | 1 | — | medium |
| `IVirtual` | interface_or_abstract_base | 25 | — | high |
| `IVisualEffect` | common_concrete_base | 1 | — | medium |
| `IWindow` | common_concrete_base | 1 | — | medium |
| `ItemViewer` | common_concrete_base | 1 | — | medium |
| `LambdaProc` | common_concrete_base | 1 | — | medium |
| `Model` | common_concrete_base | 1 | — | medium |
| `MultithreadObject` | interface_or_abstract_base | 1 | — | high |
| `Object` | interface_or_abstract_base | 34 | — | high |
| `Palettes::IItemFrameUI` | interface_or_abstract_base | 1 | — | high |
| `RefCountTemplate` | interface_or_abstract_base | 19 | — | high |
| `RefCountTemplateAtomic` | interface_or_abstract_base | 5 | — | high |
| `RenderWare::Mesh` | common_concrete_base | 1 | — | high |
| `RenderWare::MeshCompiledStateLink` | common_concrete_base | 1 | — | high |
| `Resource::Database` | interface_or_abstract_base | 3 | — | high |
| `Resource::IKeyFilter` | interface_or_abstract_base | 1 | — | high |
| `Resource::IRecord` | interface_or_abstract_base | 2 | — | high |
| `Resource::IResourceFactory` | interface_or_abstract_base | 2 | — | high |
| `Resource::IResourceManager` | interface_or_abstract_base | 1 | — | high |
| `Resource::PFRecordBase` | interface_or_abstract_base | 2 | — | high |
| `Resource::ResourceObject` | interface_or_abstract_base | 13 | — | high |
| `Resource::ThreadedObject` | interface_or_abstract_base | 2 | — | high |
| `Simulator::CinematicActionUnkBase` | common_concrete_base | 1 | — | medium |
| `Simulator::IGameDataView` | interface_or_abstract_base | 1 | — | high |
| `Simulator::IScenarioEditHistoryEntry` | interface_or_abstract_base | 2 | — | high |
| `Simulator::ISerializerDatabase` | common_concrete_base | 1 | — | medium |
| `Simulator::ISimulatorSerializable` | interface_or_abstract_base | 15 | — | high |
| `Simulator::ISimulatorStrategy` | interface_or_abstract_base | 1 | — | high |
| `Simulator::UnknownCreatureClass` | interface_or_abstract_base | 2 | — | high |
| `Simulator::UnknownManagerSuperclass` | interface_or_abstract_base | 1 | — | high |
| `Simulator::cArtilleryProjectile` | common_concrete_base | 1 | — | high |
| `Simulator::cBaseDisplayStrategy` | interface_or_abstract_base | 1 | — | high |
| `Simulator::cBaseSimulatorInputStrategy` | common_concrete_base | 1 | — | medium |
| `Simulator::cBehaviorAgent` | interface_or_abstract_base | 5 | — | high |
| `Simulator::cBehaviorList` | interface_or_abstract_base | 15 | — | high |
| `Simulator::cBuilding` | interface_or_abstract_base | 5 | — | high |
| `Simulator::cCombatant` | interface_or_abstract_base | 15 | — | high |
| `Simulator::cDefaultBeamTool` | interface_or_abstract_base | 4 | 0x0149b810, 0x0149b8b4, 0x0149b900, 0x0149ba30 | high |
| `Simulator::cDefaultProjectileWeapon` | common_concrete_base | 5 | — | high |
| `Simulator::cDefaultToolProjectile` | interface_or_abstract_base | 1 | — | high |
| `Simulator::cGameData` | interface_or_abstract_base | 44 | — | high |
| `Simulator::cGonzagoSimulator` | interface_or_abstract_base | 11 | — | high |
| `Simulator::cHitSphere` | common_concrete_base | 1 | — | high |
| `Simulator::cInteractableObject` | common_concrete_base | 1 | — | high |
| `Simulator::cMovableDestructibleOrnament` | common_concrete_base | 2 | — | medium |
| `Simulator::cObjectPoolClass` | common_concrete_base | 5 | — | high |
| `Simulator::cOrnament` | common_concrete_base | 1 | — | high |
| `Simulator::cPlaceableStructure` | interface_or_abstract_base | 3 | — | high |
| `Simulator::cProjectile` | interface_or_abstract_base | 9 | — | high |
| `Simulator::cRepairToolStrategy` | common_concrete_base | 1 | — | high |
| `Simulator::cScenarioPowerup` | interface_or_abstract_base | 2 | — | high |
| `Simulator::cSpaceInventory` | interface_or_abstract_base | 1 | — | high |
| `Simulator::cSpaceInventoryItem` | interface_or_abstract_base | 4 | — | high |
| `Simulator::cSpatialObject` | interface_or_abstract_base | 24 | — | high |
| `Simulator::cToolStrategy` | interface_or_abstract_base | 13 | 0x01416698, 0x014166c4, 0x0141677c, 0x014167a0, 0x014167ec, 0x014168a8, 0x014169bc, 0x014169f0 | high |
| `Skinner::cSkinPainterJob` | interface_or_abstract_base | 8 | — | high |
| `Sporepedia::IAssetData` | interface_or_abstract_base | 1 | — | high |
| `Sporepedia::ISPUILargeAssetView` | common_concrete_base | 1 | — | medium |
| `Sporepedia::cSPUILargeAssetViewSmh` | common_concrete_base | 1 | — | medium |
| `StdDrawable` | common_concrete_base | 1 | — | medium |
| `Swarm::IEffectMap` | interface_or_abstract_base | 1 | — | high |
| `Swarm::IEffectsManager` | interface_or_abstract_base | 1 | — | high |
| `Swarm::IModelParticleStreamer` | interface_or_abstract_base | 1 | — | high |
| `Swarm::cDescription` | common_concrete_base | 6 | — | high |
| `Terrain::ITerrain` | interface_or_abstract_base | 1 | — | high |
| `Terrain::UnkWeatherManager` | interface_or_abstract_base | 1 | — | high |
| `Terrain::cTerrainDecal` | common_concrete_base | 1 | — | medium |
| `Terrain::cTerrainMap` | interface_or_abstract_base | 2 | — | high |
| `Texture` | common_concrete_base | 1 | — | medium |
| `UI::CursorAttachment` | interface_or_abstract_base | 1 | — | high |
| `UI::GlobalUIUnkBase1` | interface_or_abstract_base | 1 | — | high |
| `UI::IHintConditioner` | interface_or_abstract_base | 1 | — | high |
| `UTFWin::BehaviourTimeRamp` | common_concrete_base | 1 | — | high |
| `UTFWin::EventPropertyObject` | common_concrete_base | 1 | — | high |
| `UTFWin::ICascadeEffect` | interface_or_abstract_base | 1 | — | high |
| `UTFWin::IComboBoxDrawable` | interface_or_abstract_base | 1 | — | high |
| `UTFWin::IEventTimeFunction` | interface_or_abstract_base | 1 | — | high |
| `UTFWin::IGlideEffect` | interface_or_abstract_base | 1 | — | high |
| `UTFWin::IInflateEffect` | interface_or_abstract_base | 1 | — | high |
| `UTFWin::ILayoutStyle` | interface_or_abstract_base | 2 | — | high |
| `UTFWin::IModulateEffect` | interface_or_abstract_base | 1 | — | high |
| `UTFWin::IPerspectiveEffect` | interface_or_abstract_base | 1 | — | high |
| `UTFWin::IRotateEffect` | interface_or_abstract_base | 1 | — | high |
| `UTFWin::IScrollbarDrawable` | interface_or_abstract_base | 1 | — | high |
| `UTFWin::ISliderDrawable` | interface_or_abstract_base | 1 | — | high |
| `UTFWin::ISpinnerDrawable` | interface_or_abstract_base | 1 | — | high |
| `UTFWin::IStdDrawable` | interface_or_abstract_base | 1 | — | high |
| `UTFWin::ITreeNode` | interface_or_abstract_base | 1 | — | high |
| `UTFWin::ITreeView` | interface_or_abstract_base | 1 | — | high |
| `UTFWin::IWinProc` | interface_or_abstract_base | 29 | — | high |
| `UTFWin::InteractiveWinProc` | interface_or_abstract_base | 4 | — | high |
| `UTFWin::InteractiveWindow` | interface_or_abstract_base | 1 | — | high |
| `UTFWin::LayoutObjectsContainer` | common_concrete_base | 1 | — | high |
| `UTFWin::MessageBoxCallback` | interface_or_abstract_base | 2 | — | high |
| `UTFWin::UTFWinObject` | common_concrete_base | 25 | — | high |
| `UTFWin::Window` | interface_or_abstract_base | 3 | 0x013f57a4, 0x013fdb18, 0x013fdb6c, 0x013fdbe4, 0x0140f854, 0x01414b10, 0x01414bc0, 0x01414c14 | high |
| `UnkItemFrameMessage_` | common_concrete_base | 1 | — | medium |
| `UnkPageArrowsUI` | common_concrete_base | 1 | — | medium |
| `Vector4` | common_concrete_base | 1 | — | medium |
| `VertexDescriptionBase` | common_concrete_base | 1 | — | medium |
| `Window_intrusive_list_node` | common_concrete_base | 1 | — | medium |
| `cCellDataReference_` | common_concrete_base | 1 | — | medium |
| `cCommunity` | common_concrete_base | 2 | — | medium |
| `cComponentBase` | common_concrete_base | 6 | — | medium |
| `cCreatureBase` | common_concrete_base | 2 | — | medium |
| `cGameBundleContainer` | common_concrete_base | 3 | — | medium |
| `cGonzagoSubsystem` | common_concrete_base | 1 | — | medium |
| `cIdentityColorable` | common_concrete_base | 3 | — | medium |
| `cLocomotiveObject` | common_concrete_base | 13 | — | medium |
| `cLocomotiveObject_superclass` | common_concrete_base | 1 | — | medium |
| `cMission` | common_concrete_base | 2 | — | medium |
| `cObjectPool_` | common_concrete_base | 1 | — | medium |
| `cSpatialObjectView` | common_concrete_base | 1 | — | medium |
| `cSpeciesRelationshipManagerDispose` | common_concrete_base | 1 | — | medium |
| `cStrategy` | common_concrete_base | 23 | — | medium |
| `013fa974` | binary_prefix_base | None | 0x013fa974 | medium |
| `01419794` | binary_prefix_base | None | 0x01419794 | medium |

The strongest binary common-base signal is the 21-slot prefix shared by tables rooted at `0x013fa974` and `0x01419794`. The prefix is byte-identical, but no RTTI evidence decides whether these are duplicate subobject identities or scan artifacts.

## Constructors, destructors, and lifecycle boundaries

278 classes have a constructor and/or destructor declaration. Address availability is sparse; vtable destructor slots are not equated with `Release`/`Dispose`.

| Family | Constructors | Destructors | Binary vtables | Pair status |
|---|---:|---:|---|---|
| `ColorRGBA` | 4 | 0 | 0 | incomplete_declaration |
| `PlaneEquation` | 4 | 0 | 0 | incomplete_declaration |
| `SerializerReadStreamPrivate` | 3 | 1 | 0 | declared_pair |
| `SerializerWriteStreamPrivate` | 3 | 1 | 0 | declared_pair |
| `ColorRGB` | 3 | 0 | 0 | incomplete_declaration |
| `CoreAllocatorAdapter` | 3 | 0 | 0 | incomplete_declaration |
| `IO::IniFile` | 2 | 1 | 0 | declared_pair |
| `LocalizedString` | 2 | 1 | 0 | declared_pair |
| `MemoryStream` | 2 | 1 | 0 | declared_pair |
| `Point` | 3 | 0 | 0 | incomplete_declaration |
| `Resource::PFRecordWrite` | 2 | 1 | 4 | declared_pair |
| `ResourceKey` | 3 | 0 | 0 | incomplete_declaration |
| `Simulator::cGonzagoTimer` | 2 | 1 | 0 | declared_pair |
| `SporeStdDrawableImageInfo` | 2 | 1 | 0 | declared_pair |
| `SporeTooltipWinProc` | 2 | 1 | 0 | declared_pair |
| `Vector2` | 3 | 0 | 0 | incomplete_declaration |
| `App::cArithmeticaResource` | 1 | 1 | 0 | declared_pair |
| `ArgScript::LambdaParser` | 2 | 0 | 0 | incomplete_declaration |
| `Attribute` | 2 | 0 | 0 | incomplete_declaration |
| `BehaviourTimeOscillator` | 1 | 1 | 0 | declared_pair |
| `BehaviourTimeSmoothRamp` | 1 | 1 | 0 | declared_pair |
| `BoundingBox` | 2 | 0 | 0 | incomplete_declaration |
| `CinematicVignetteActionData` | 1 | 1 | 0 | declared_pair |
| `ColorHSV` | 2 | 0 | 0 | incomplete_declaration |
| `DatabasePackedFile` | 1 | 1 | 0 | declared_pair |
| `DialogDrawable` | 1 | 1 | 0 | declared_pair |
| `Dimensions` | 2 | 0 | 0 | incomplete_declaration |
| `EnterEditorMessage` | 1 | 1 | 0 | declared_pair |
| `FrameDrawable` | 1 | 1 | 0 | declared_pair |
| `IO::FileStream` | 1 | 1 | 4 | declared_pair |
| `IntDimensions` | 2 | 0 | 0 | incomplete_declaration |
| `IntRectangle` | 2 | 0 | 0 | incomplete_declaration |
| `ItemViewer` | 1 | 1 | 0 | declared_pair |
| `LambdaMessageListener` | 1 | 1 | 0 | declared_pair |
| `LambdaProc` | 2 | 0 | 0 | incomplete_declaration |
| `Line` | 2 | 0 | 0 | incomplete_declaration |
| `Math::Color` | 2 | 0 | 0 | incomplete_declaration |
| `Mutex` | 1 | 1 | 0 | declared_pair |
| `PageArrowsUI` | 1 | 1 | 0 | declared_pair |
| `Palettes::ColorSwatchUI` | 1 | 1 | 0 | declared_pair |
| `Palettes::IItemFrameUI` | 1 | 1 | 0 | declared_pair |
| `Palettes::PaletteCategoryUI` | 1 | 1 | 0 | declared_pair |
| `Palettes::PaletteItem` | 1 | 1 | 0 | declared_pair |
| `Palettes::PaletteMain` | 1 | 1 | 0 | declared_pair |
| `Palettes::PalettePage` | 1 | 1 | 0 | declared_pair |
| `Palettes::PalettePageUI` | 1 | 1 | 0 | declared_pair |
| `Property` | 1 | 1 | 0 | declared_pair |
| `Quaternion` | 2 | 0 | 0 | incomplete_declaration |
| `RenderWare::Raster` | 1 | 1 | 0 | declared_pair |
| `RenderWare::TextureSlot` | 1 | 1 | 0 | declared_pair |
| `Resource::DatabaseDirectoryFiles` | 1 | 1 | 7 | declared_pair |
| `Resource::PFRecordRead` | 1 | 1 | 0 | declared_pair |
| `SimpleLayout` | 1 | 1 | 0 | declared_pair |
| `Simulator::cGameData` | 1 | 1 | 0 | declared_pair |
| `Skeleton` | 2 | 0 | 0 | incomplete_declaration |
| `Sporepedia::IAssetData` | 1 | 1 | 0 | declared_pair |
| `StandardMessage` | 1 | 1 | 0 | declared_pair |
| `TreeNode` | 1 | 1 | 0 | declared_pair |
| `UI::EditorNamePanel` | 1 | 1 | 0 | declared_pair |
| `UTFWin::FrameStyle` | 2 | 0 | 0 | incomplete_declaration |
| `UTFWin::Image` | 1 | 1 | 2 | declared_pair |
| `UTFWin::ProportionalLayout` | 1 | 1 | 1 | declared_pair |
| `UTFWin::SporeStdDrawable` | 1 | 1 | 0 | declared_pair |
| `UTFWin::Window` | 1 | 1 | 123 | declared_pair |
| `Vector3` | 2 | 0 | 0 | incomplete_declaration |
| `Vector4` | 2 | 0 | 0 | incomplete_declaration |
| `VertexElement` | 2 | 0 | 0 | incomplete_declaration |
| `cEditorResource` | 1 | 1 | 0 | declared_pair |
| `cObjectPool_` | 1 | 1 | 0 | declared_pair |
| `cSPAssetDataOTDB` | 1 | 1 | 0 | declared_pair |
| `cTerrainMapSet` | 1 | 1 | 0 | declared_pair |
| `Anim::AnimatedCreature` | 0 | 1 | 0 | incomplete_declaration |
| `Anim::IAnimManager` | 0 | 1 | 0 | incomplete_declaration |
| `App::Canvas` | 0 | 1 | 10 | incomplete_declaration |
| `App::CommandLine` | 0 | 1 | 0 | incomplete_declaration |
| `App::DefaultGameMode` | 0 | 1 | 0 | incomplete_declaration |
| `App::DirectPropertyList` | 0 | 1 | 1 | incomplete_declaration |
| `App::FileDropMessage` | 0 | 1 | 0 | incomplete_declaration |
| `App::IAppSystem` | 0 | 1 | 0 | incomplete_declaration |
| `App::ICameraManager` | 0 | 1 | 0 | incomplete_declaration |
| `App::ICheatManager` | 0 | 1 | 0 | incomplete_declaration |
| `App::IConfigManager` | 0 | 1 | 0 | incomplete_declaration |
| `App::IGameMode` | 0 | 1 | 0 | incomplete_declaration |
| `App::IMessageRC` | 0 | 1 | 0 | incomplete_declaration |
| `App::ISPClassFactory` | 0 | 1 | 0 | incomplete_declaration |
| `App::IUnmanagedMessageListener` | 0 | 1 | 0 | incomplete_declaration |
| `App::PropertyList` | 0 | 1 | 2 | incomplete_declaration |
| `App::cCheatManager` | 0 | 1 | 12 | incomplete_declaration |
| `App::cGameModeManager` | 0 | 1 | 0 | incomplete_declaration |
| `App::cIDGenerator` | 0 | 1 | 0 | incomplete_declaration |
| `App::cPropManager` | 0 | 1 | 2 | incomplete_declaration |
| `ArgScript::IBlock` | 0 | 1 | 0 | incomplete_declaration |
| `ArgScript::ICommand` | 0 | 1 | 0 | incomplete_declaration |
| `ArgScript::ISpecialBlock` | 0 | 1 | 0 | incomplete_declaration |
| `ArgScript::ITraceStream` | 0 | 1 | 0 | incomplete_declaration |
| `BasicLockRefCounted` | 0 | 1 | 0 | incomplete_declaration |
| `CascadeEffect` | 0 | 1 | 0 | incomplete_declaration |
| `CinematicAction` | 0 | 1 | 0 | incomplete_declaration |
| `ClassSerializer` | 1 | 0 | 0 | incomplete_declaration |
| `Clock` | 1 | 0 | 0 | incomplete_declaration |

## Factory and call patterns

18 methods match a conservative `Create`/`Factory`/`Alloc`/`new_`/`Make`/`New` naming or signature pattern. Static callers are evidence of call topology, not proof of returned dynamic type.

| Family | Method | Address | Return | Inbound | Confidence |
|---|---|---|---|---:|---|
| `App::cAppSystem` | `Create` | `0x007e8a00` | `cAppSystem *` | 0 | medium |
| `FixedPoolAllocator` | `Alloc` | `0x00926100` | `void *` | 1 | high |
| `FixedPoolAllocator` | `Alloc` | `0x00926100` | `void *` | 1 | high |
| `FixedPoolAllocator` | `Alloc_` | `0x00926220` | `void *` | 0 | medium |
| `GeneralAllocator` | `new_` | `0x00f47240` | `void *` | 0 | medium |
| `IO::Directory` | `Create` | `0x00932930` | `bool` | 0 | medium |
| `IO::EAIOZoneObject` | `new_` | `0x00926270` | `void *` | 0 | medium |
| `RenderWare::Raster` | `Create` | `0x011efbb0` | `void` | 0 | medium |
| `Simulator::Cell::cCellDataReference_` | `Create` | `0x00e82420` | `cCellDataReference_ *` | 2 | high |
| `Simulator::cCreatureAnimal` | `Create` | `0x00c09b40` | `cCreatureAnimal *` | 0 | medium |
| `Simulator::cObjectPool_` | `CreateObject` | `0x00b72270` | `cObjectPoolIndex` | 0 | medium |
| `Simulator::cPlanetRecord` | `Create` | `0x00ba6300` | `void` | 2 | high |
| `Simulator::cSimulatorSystem` | `Create` | `0x00b5e160` | `cSimulatorSystem *` | 0 | medium |
| `Terrain::cTerrainSphere` | `Create` | `0x00fa2350` | `cTerrainSphere *` | 0 | medium |
| `UI::ScrollFrameVertical` | `Create` | `0x008076f0` | `IWindow *` | 5 | high |
| `UTFWin::IButton` | `Create` | `0x009670a0` | `IButton *` | 0 | medium |
| `UTFWin::ITextEdit` | `Create` | `0x0098caa0` | `ITextEdit *` | 0 | medium |
| `UTFWin::UTFWinObject` | `new_` | `0x00951230` | `UTFWinObject *` | 0 | medium |

## Shared field layouts

The SDK supplies 1895 structures and 251 generated vftable layouts. There are 40 non-trivial exact field-layout groups. Equality is structural evidence, not inheritance proof.

- **8 bytes / 2 fields:** `Resource::IResourceFactory`, `UTFWin::cCursorManager`
- **8 bytes / 2 fields:** `App::ITokenTranslator`, `UI::ITokenTranslator`
- **8 bytes / 2 fields:** `RefCountTemplate`, `Swarm::cDescription`
- **8 bytes / 2 fields:** `Editors::cEditorSkinMeshBase::UnkStruct2`, `Resource::PFHoleTable::HoleRecord`
- **8 bytes / 2 fields:** `UTFWin::Window_intrusive_list_node`, `eastl::intrusive_list_node`
- **8 bytes / 2 fields:** `Math::Point`, `Math::Vector2`
- **12 bytes / 3 fields:** `UTFWin::Effect`, `UTFWin::InteractiveWinProc`
- **12 bytes / 3 fields:** `Simulator::cAbductToolStrategy`, `Simulator::cDefaultBeamTool`, `Simulator::cDropCargoToolStrategy`, `Simulator::cMindEraseToolStrategy`, `Simulator::cScanToolStrategy`
- **12 bytes / 3 fields:** `Simulator::cArtilleryWeaponStrategy`, `Simulator::cCropCirclesToolStrategy`, `Simulator::cDeepSpaceProjectileToolStrategy`, `Simulator::cDefaultProjectileWeapon`, `Simulator::cDragInputProjectileToolStrategy`, `Simulator::cEnergyRepairToolStrategy`, `Simulator::cGenesisDeviceToolStrategy`, `Simulator::cGetOutOfUFOToolStrategy`, `Simulator::cGlobalMindEraseToolStrategy`, `Simulator::cPlaceColonyToolStrategy`, `Simulator::cPlaceObjectToolStrategy`, `Simulator::cRallyCallToolStrategy`, `Simulator::cRepairAOEToolStrategy`, `Simulator::cRepairToolStrategy`, `Simulator::cToggleToolStrategy`, `Simulator::cToolStrategy`, `Simulator::cTurretDefenseMissileWeapon`, `Simulator::cTurretFlakWeapon`
- **12 bytes / 3 fields:** `eastl::list<App::IMessageListener *>`, `eastl::list<Resource::ICache *>`, `eastl::list<Resource::IResourceFactory *>`, `eastl::list<Simulator::MissionManagerTimerEntry>`, `eastl::list<Simulator::cCollectableItemID>`, `eastl::list<eastl::intrusive_ptr<Object>>`, `eastl::list<eastl::intrusive_ptr<Resource::IRecord>>`, `eastl::list<eastl::intrusive_ptr<Resource::ResourceObject>>`, `eastl::list<eastl::intrusive_ptr<Simulator::ISimulatorUIGraphic>>`, `eastl::list<eastl::intrusive_ptr<Simulator::cGameData>>`, `eastl::list<eastl::intrusive_ptr<Simulator::cGonzagoSimulator>>`, `eastl::list<int>`, `eastl::list<unsigned int>`
- **12 bytes / 3 fields:** `Direct3D::D3DVECTOR`, `Math::Vector3`
- **16 bytes / 4 fields:** `ArgScript::ICommand`, `ArgScript::IParser`
- **16 bytes / 4 fields:** `Skinner::cSkinPainterJob`, `Skinner::cSkinPainterJobAmbientOcclusion`, `Skinner::cSkinPainterJobBumpToNormal`, `Skinner::cSkinPainterJobCopyTex1AlphaToTex0`
- **16 bytes / 4 fields:** `RECT`, `tagRECT`
- **16 bytes / 4 fields:** `Simulator::Cell::cCellDataReference<Simulator::Cell::cCellBackgroundMapResource>`, `Simulator::Cell::cCellDataReference<Simulator::Cell::cCellCellResource>`, `Simulator::Cell::cCellDataReference<Simulator::Cell::cCellEffectMapResource>`, `Simulator::Cell::cCellDataReference<Simulator::Cell::cCellGlobalsResource>`, `Simulator::Cell::cCellDataReference<Simulator::Cell::cCellLookAlgorithmResource>`, `Simulator::Cell::cCellDataReference<Simulator::Cell::cCellLookTableResource>`, `Simulator::Cell::cCellDataReference<Simulator::Cell::cCellLootTableResource>`, `Simulator::Cell::cCellDataReference<Simulator::Cell::cCellPopulateResource>`, `Simulator::Cell::cCellDataReference<Simulator::Cell::cCellPowersResource>`, `Simulator::Cell::cCellDataReference<Simulator::Cell::cCellRandomCreatureResource>`, `Simulator::Cell::cCellDataReference<Simulator::Cell::cCellStructureResource>`, `Simulator::Cell::cCellDataReference<Simulator::Cell::cCellWorldResource>`, `Simulator::Cell::cCellDataReference_`
- **16 bytes / 4 fields:** `GeneralAllocator::Chunk`, `GeneralAllocator::SkipListChunk`
- **16 bytes / 4 fields:** `eastl::string`, `eastl::string8`
- **16 bytes / 4 fields:** `Direct3D::D3DCOLORVALUE`, `Math::ColorRGBA`
- **16 bytes / 4 fields:** `Math::Quaternion`, `Math::Vector4`
- **20 bytes / 5 fields:** `Direct3D::IDirect3DPixelShader9::IDirect3DPixelShader9__vftable`, `Direct3D::IDirect3DVertexShader9::IDirect3DVertexShader9__vftable`
- **20 bytes / 5 fields:** `eastl::vector<char *>`, `eastl::vector<const char *>`
- **24 bytes / 6 fields:** `UTFWin::IButtonDrawable::IButtonDrawable__vftable`, `UTFWin::IComboBoxDrawable::IComboBoxDrawable__vftable`, `UTFWin::IScrollbarDrawable::IScrollbarDrawable__vftable`, `UTFWin::ISliderDrawable::ISliderDrawable__vftable`, `UTFWin::ISpinnerDrawable::ISpinnerDrawable__vftable`
- **24 bytes / 6 fields:** `App::ITokenTranslator::ITokenTranslator__vftable`, `UI::ITokenTranslator::ITokenTranslator__vftable`
- **28 bytes / 7 fields:** `Simulator::SubSystem::cLivingUniverse`, `Simulator::cAnimalSpeciesManager`, `Simulator::cStrategy`
- **28 bytes / 4 fields:** `eastl::map<ResourceKey, unsigned int>`, `eastl::map<Simulator::BadgeManagerEvent, int>`, `eastl::map<Simulator::Cell::cCellDataReference_ *, int>`, `eastl::map<Simulator::PlanetID, unsigned int>`, `eastl::map<Simulator::TimeManagerPause, int>`, `eastl::map<eastl::intrusive_ptr<Simulator::cCity>, float>`, `eastl::map<eastl::pair<unsigned int, unsigned int>, Simulator::cRelationshipData>`, `eastl::map<eastl::string, eastl::intrusive_ptr<ArgScript::IParser>>`, `eastl::map<int, LocalizedString>`, `eastl::map<int, Simulator::cSpacePlayerWarData>`, `eastl::map<int, Simulator::cTradeRouteData>`, `eastl::map<int, eastl::intrusive_ptr<Editors::EditorCreatureController>>`, `eastl::map<int, eastl::intrusive_ptr<Object>>`, `eastl::map<int, eastl::pair<int, int>>`, `eastl::map<int, eastl::string16>`, `eastl::map<int, float>`, `eastl::map<int, int>`, `eastl::map<unsigned int, App::Property>`, `eastl::map<unsigned int, ResourceKey>`, `eastl::map<unsigned int, Simulator::CnvAnimation>`, `eastl::map<unsigned int, Simulator::CnvAnimationVariation>`, `eastl::map<unsigned int, Simulator::CnvDialog>`, `eastl::map<unsigned int, Simulator::CnvEventLog>`, `eastl::map<unsigned int, Simulator::MissionState>`, `eastl::map<unsigned int, Simulator::tGameDataVectorT<Simulator::cGameData>>`, `eastl::map<unsigned int, eastl::intrusive_ptr<Anim::SPAnimation>>`, `eastl::map<unsigned int, eastl::intrusive_ptr<App::PropertyList>>`, `eastl::map<unsigned int, eastl::intrusive_ptr<Graphics::IModelWorld>>`, `eastl::map<unsigned int, eastl::intrusive_ptr<Simulator::cEmpire>>`, `eastl::map<unsigned int, eastl::intrusive_ptr<Simulator::cFeedbackEvent>>`, `eastl::map<unsigned int, eastl::intrusive_ptr<Simulator::cStarRecord>>`, `eastl::map<unsigned int, float>`, `eastl::map<unsigned int, int>`, `eastl::map<unsigned int, unsigned int>`, `eastl::map<wchar16, int>`, `eastl::set<Resource::PFHoleTable::HoleRecord>`, `eastl::set<eastl::intrusive_ptr<Object>>`, `eastl::set<eastl::intrusive_ptr<Simulator::cSpatialObject>>`, `eastl::set<eastl::string>`
- **28 bytes / 7 fields:** `Simulator::cObjectPool<Simulator::Cell::cCellGFX::CellGFXObjectData>`, `Simulator::cObjectPool<Simulator::Cell::cCellObjectData>`, `Simulator::cObjectPool<Simulator::Cell::cCellUIRollover>`, `Simulator::cObjectPool_`
- **32 bytes / 8 fields:** `eastl::hash_map<RenderWare::CompiledState *, unsigned int>`, `eastl::hash_map<ResourceID, eastl::intrusive_ptr<App::PropertyList>>`, `eastl::hash_map<ResourceID, unsigned int>`, `eastl::hash_map<ResourceKey, Graphics::TextureContainer *>`, `eastl::hash_map<ResourceKey, Simulator::cSpeciesProfile>`, `eastl::hash_map<Simulator::cCollectableItemID, Simulator::cCollectableItems::UnlockableItem>`, `eastl::hash_map<Simulator::cCollectableItemID, unsigned char>`, `eastl::hash_map<Simulator::cGameData *, int>`, `eastl::hash_map<eastl::string, ArgScript::IFunction *>`, `eastl::hash_map<eastl::string, eastl::intrusive_ptr<ArgScript::IParser>>`, `eastl::hash_map<eastl::string, eastl::string>`, `eastl::hash_map<eastl::string, int>`, `eastl::hash_map<eastl::string, unsigned int>`, `eastl::hash_map<eastl::string16, int>`, `eastl::hash_map<int, Simulator::cCommunityLayout>`, `eastl::hash_map<int, eastl::deque<eastl::intrusive_ptr<Object>>>`, `eastl::hash_map<int, eastl::intrusive_ptr<Simulator::cGameData>>`, `eastl::hash_map<int, int>`, `eastl::hash_map<unsigned int, App::ICamera *(*)(App::PropertyList *)>`, `eastl::hash_map<unsigned int, Graphics::Material>`, `eastl::hash_map<unsigned int, Simulator::cGameData *(*)()>`, `eastl::hash_map<unsigned int, eastl::intrusive_ptr<Graphics::ShaderBuilder>>`, `eastl::hash_map<unsigned int, eastl::intrusive_ptr<Graphics::StandardShader>>`, `eastl::hash_map<unsigned int, eastl::intrusive_ptr<Simulator::cToolStrategy>>`, `eastl::hash_map<unsigned int, eastl::intrusive_ptr<Swarm::IEffectsWorld>>`, `eastl::hash_map<unsigned int, eastl::intrusive_ptr<UI::SpaceToolPanelUI>>`, `eastl::hash_map<unsigned int, eastl::list<App::IMessageListener *>>`, `eastl::hash_map<unsigned int, eastl::string>`, `eastl::hash_map<unsigned int, eastl::vector<unsigned int>>`, `eastl::hash_map<unsigned int, int>`, `eastl::hash_map<unsigned int, unsigned int>`, `eastl::hash_set<unsigned int>`
- **32 bytes / 4 fields:** `eastl::map<ResourceKey, int, eastl::less<ResourceKey>, CoreAllocatorAdapter<FixedPoolAllocator>>`, `eastl::map<eastl::string16, unsigned int, eastl::less<eastl::string16>, CoreAllocatorAdapter<FixedPoolAllocator>>`
- **32 bytes / 4 fields:** `eastl::map<ResourceKey, Resource::IRecord *, eastl::less<ResourceKey>, CoreAllocatorAdapter<ICoreAllocator>>`, `eastl::map<ResourceKey, Resource::PFRecordBase *, eastl::less<ResourceKey>, CoreAllocatorAdapter<ICoreAllocator>>`, `eastl::map<int, int, eastl::less<ResourceKey>, CoreAllocatorAdapter<ICoreAllocator>>`
- **36 bytes / 9 fields:** `UTFWin::ButtonDrawableRadio::ButtonDrawableRadio__vftable`, `UTFWin::ButtonDrawableStandard::ButtonDrawableStandard__vftable`
- **36 bytes / 8 fields:** `eastl::hash_map<ResourceKey, Resource::RecordInfo, int, int, CoreAllocatorAdapter<ICoreAllocator>>`, `eastl::hash_map<uint, eastl::string16, int, int, CoreAllocatorAdapter<ICoreAllocator>>`, `eastl::hash_map<uint, eastl::vector<eastl::pair<eastl::intrusive_ptr<Resource::IResourceFactory>, unsigned int>>, int, int, CoreAllocatorAdapter<ICoreAllocator>>`, `eastl::hash_map<uint, eastl::vector<unsigned int>, int, int, CoreAllocatorAdapter<ICoreAllocator>>`, `eastl::hash_map<uint, uint, int, int, CoreAllocatorAdapter<ICoreAllocator>>`
- **56 bytes / 14 fields:** `Direct3D::IDirect3DIndexBuffer9::IDirect3DIndexBuffer9__vftable`, `Direct3D::IDirect3DVertexBuffer9::IDirect3DVertexBuffer9__vftable`
- **64 bytes / 7 fields:** `App::OnModeEnterMessage`, `App::OnModeExitMessage`, `App::SetGameModeMessage`, `App::StandardMessage`, `Editors::ColorChangedMessage`, `Palettes::SubcategoryChangedMessage`, `Simulator::CombatantKilledMessage`, `Simulator::GameNounStatusChangedMessage`, `Simulator::MissionUpdateMessage`, `Simulator::PlayerEmpireAlliedMessage`, `Simulator::PlayerEmpireLostAllianceMessage`, `Simulator::ScenarioCreatureHealedMessage`, `Simulator::SpaceRareFoundMessage`, `Simulator::ToolOnHitMessage`
- **72 bytes / 20 fields:** `UTFWin::BehaviourTimeRamp`, `UTFWin::BehaviourTimeSmoothRamp`, `UTFWin::EventTimeFunctionBase`
- **80 bytes / 20 fields:** `Simulator::cDefaultAoETool::cDefaultAoETool__vftable`, `Simulator::cDefaultBeamTool::cDefaultBeamTool__vftable`
- **96 bytes / 19 fields:** `UTFWin::BiStateEffect`, `UTFWin::FadeEffect`
- **524 bytes / 41 fields:** `UTFWin::SporeAnimatedIconWin`, `UTFWin::Window`
- **592 bytes / 108 fields:** `Simulator::cHitSphere`, `Simulator::cSolarHitSphere`
- **832 bytes / 111 fields:** `Simulator::cBuilding`, `Simulator::cBuildingEntertainment`, `Simulator::cBuildingHouse`, `Simulator::cBuildingIndustry`
- **1520 bytes / 127 fields:** `Simulator::cDeepSpaceProjectile`, `Simulator::cDefaultToolProjectile`

## Overrides

The JSON records 1253 header-declared or slot-aligned override records. Slot-aligned records require the same method name in base and derived generated vftable layouts; header-only overrides remain lower confidence when no binary slot match exists.

## Aliases and duplicate identities

- SDK duplicate addresses: **3**
- Triage function aliases: **115**
- Exact duplicate vtable-pointer sequences: **107**
- Static SDK functions associated with vtable data: **1**

All rows, including complete function-pointer sequences for duplicate vtables, are in the JSON. The canonical same-address SDK conflicts remain split: `0x0093b630`, `0x0093c360`, and `0x00dde930`.

## Families supported only by naming/layout

1199 families have SDK/header naming or layout evidence but no class-specific binary virtual-slot match. They remain low confidence and are listed completely in JSON.

- `Anim::AnimFunction` — ['AnimFunction']; no declared address
- `Anim::AnimatedCreature` — ['AnimatedCreature_virtual_dtor', 'GetAnimWorld', 'GetAnimationLength', 'GetCurrentAnimation', 'LoadAnimation', 'PlayAnimation']; no declared address
- `Anim::CreatureBlock` — []; no declared address
- `Anim::IAnimManager` — ['AddRef', 'ClearAnimationCache', 'CreateWorld', 'Dispose', 'Get', 'GetAnimGroup']; 0x0067cae0
- `Anim::IAnimWorld` — ['DestroyCreature', 'Dispose', 'GetCreatures', 'LoadCreature', 'LoadCreatureByName', 'PostUpdateCreatures']; no declared address
- `Anim::SPAnimationChannel` — []; no declared address
- `Anim::TlsaAnimation` — []; no declared address
- `Anim::anim_cid_unk` — []; no declared address
- `Anim::anim_csd` — []; no declared address
- `Anim::cAnimManagerImpl` — []; no declared address
- `Anim::model_unk` — []; no declared address
- `AnimReference` — []; no declared address
- `AnimationMessage` — []; no declared address
- `App::CameraFactoryFunction_t` — ['CameraFactoryFunction_t']; no declared address
- `App::CommandLine` — ['CommandLine_virtual_dtor', 'FindSwitch', 'Get']; 0x0092b420, 0x0092b570
- `App::DefaultCamera` — []; no declared address
- `App::DefaultGameMode` — []; no declared address
- `App::FileDropMessage` — ['AddRef', 'FileDropMessage_virtual_dtor', 'Release']; no declared address
- `App::GameSpace` — []; no declared address
- `App::IAppSystem` — ['AddRef', 'BoostBackgroundJobs', 'Configure', 'Demo', 'Get', 'GetPerfWarnings']; 0x0067dcc0
- `App::ICamera` — ['GetPropertyList', 'Initialize', 'OnAttach', 'OnDeattach', 'OnEnter', 'OnExit']; no declared address
- `App::ICameraManager` — ['AddCameraType', 'Dispose', 'GetActiveCamera', 'GetActiveCameraID', 'GetActiveCameraIndex', 'GetCamera']; no declared address
- `App::ICheatManager` — ['AddCheat', 'AddRef', 'Dispose', 'Get', 'GetArgScript', 'GetCheat']; 0x0067dde0
- `App::IClassManager` — ['AddFactory', 'Create', 'CreateCasted', 'Get', 'GetFactory', 'IClassManager_virtual_dtor']; 0x00920320
- `App::IConfigManager` — ['AddRef', 'Configure', 'Get', 'GetConfigString', 'GetNumScreenResolutions', 'GetOption']; 0x0067dcf0
- `App::ICreatureModeActionHandler` — ['ExecuteAction', 'func10h', 'func14h', 'func1Ch']; no declared address
- `App::IGameMode` — ['AddRef', 'Dispose', 'IGameMode_virtual_dtor', 'Initialize', 'OnEnter', 'OnExit']; no declared address
- `App::IGameModeManager` — ['AddGameMode', 'AddRef', 'ClearActiveMode', 'Dispose', 'Get', 'GetActiveMode']; 0x0067dcd0
- `App::IGameModeObject` — ['Cast']; no declared address
- `App::IJobManager` — ['CircularRef', 'CreateJob', 'CreateJobThread', 'DebugAddBackgroundScopes', 'DebugDumpDot', 'DebugDumpStatus']; 0x0068f490
- `App::IMessageListener` — ['AddRef', 'Release']; no declared address
- `App::IMessageManager` — ['AddEntry', 'AddHandler', 'AddListener', 'AddUnmanagedListener', 'Dispose', 'Get']; 0x0067dc80
- `App::IMessageManager::MessageHandler_t` — ['MessageHandler_t']; no declared address
- `App::IMessageRC` — ['AddRef', 'IMessageRC_virtual_dtor', 'Release']; no declared address
- `App::IPropManager` — ['AddPropertyList', 'AddRef', 'AreAnyPropertyListsReferenced', 'Dispose', 'Get', 'GetGlobalPropertyList']; 0x0067ddf0
- `App::ISPClassFactory` — ['Create', 'GetName', 'GetTypes', 'ISPClassFactory_virtual_dtor']; no declared address
- `App::IStateManager` — ['CurrentState', 'CurrentStateName', 'Get', 'Init', 'IsValidState', 'LoadConfigFile']; 0x0067dce0
- `App::ITokenTranslator` — ['TranslateToken', 'func14h']; no declared address
- `App::IUnmanagedMessageListener` — ['HandleMessage', 'IUnmanagedMessageListener_virtual_dtor']; no declared address
- `App::IUpdatable` — ['AddRef', 'Release', 'Update']; no declared address
- `App::MessageListenerData` — []; no declared address
- `App::ModeEntry` — []; no declared address
- `App::OperationDefinition` — []; no declared address
- `App::PngEncoder` — []; no declared address
- `App::Property` — ['Clear', 'GetArrayBool', 'GetArrayColorRGB', 'GetArrayFloat', 'GetArrayInt32', 'GetArrayKey']; 0x00407190, 0x0040cf10, 0x00410330, 0x0041e8e0, 0x0041e950, 0x0041e9c0
- `App::RefCountedString` — []; no declared address
- `App::Thumbnail_cImportExport` — ['FolderPathFromLocale', 'Get', 'GetFolderPath', 'ImportPNG', 'SavePNG']; 0x005f79c0, 0x005f92c0, 0x005f93a0, 0x005fa960, 0x005fc3c0
- `App::cArithmeticaResource` — ['ComputeAll', 'ComputeFunction', 'GetValue', 'Load', 'SetValue', 'func14h']; 0x007f2190, 0x007f2300, 0x007f25c0, 0x007f2650, 0x007f2680
- `App::cCreatureModeStrategy` — ['ExecuteAction']; 0x00d39360
- `App::cGameModeManager` — ['AddGameMode', 'ClearActiveMode', 'Dispose', 'GetActiveMode', 'GetActiveModeID', 'GetCameraManager']; 0x007d8120, 0x007d8240, 0x007d82b0, 0x007d82f0, 0x007d8330, 0x007d8380
- `App::cIDGenerator` — ['Generate', 'GenerateForGroup', 'Get', 'cIDGenerator_virtual_dtor']; 0x0067de20
- `App::cJobCallback` — ['cJobCallback']; no declared address
- `App::cJobThread` — []; no declared address
- `App::cJobVoidCallback` — ['cJobVoidCallback']; no declared address
- `App::cLocaleManager` — ['Get', 'GetActiveLanguage', 'GetActiveLanguageName', 'GetStringDetokenizer', 'SetLanguage', 'SetLanguageByName']; 0x0067de00
- `App::cScenarioMode` — []; no declared address
- `App::cSporeApp` — ['EAMain', 'Init', 'Run', 'Shutdown']; 0x00f47420, 0x00f475a0, 0x00f47e90, 0x00f48810
- `App::cStringDetokenizer` — ['AddTranslator', 'FindTokenTranslation', 'HasTokens', 'ProcessString', 'ProcessStringEx', 'RemoveTranslator']; no declared address
- `App::cViewer` — ['BeginUpdate', 'ClearScene', 'Dispose', 'EndUpdate', 'GetCameraMaterialLODs', 'GetCameraToMouse']; 0x007c3c70, 0x007c3ce0, 0x007c3cf0, 0x007c3d20, 0x007c3d60, 0x007c3d70
- `ArgScript` — ['CreateStream']; 0x008409a0
- `ArgScript::GetDescription_t` — ['GetDescription_t']; no declared address
- `ArgScript::IBlock` — ['AddParser', 'GetParser', 'OnBlockEnd']; 0x0083cad0, 0x0083cd00
- `ArgScript::ICommand` — []; no declared address
- `ArgScript::IFunction` — ['GetBool', 'GetDescription', 'GetFloat', 'GetInt']; no declared address
- `ArgScript::IParser` — ['AddRef', 'GetDescription', 'ParseLine', 'Release', 'SetData']; no declared address
- `ArgScript::ISpecialBlock` — ['OnEndReached', 'OnLine']; no declared address
- `ArgScript::ITraceStream` — ['AddRef', 'ITraceStream_virtual_dtor', 'Release']; no declared address
- `ArgScript::LambdaParser` — []; no declared address
- `ArgScript::Lexer` — ['AddFunction', 'ExpectChar', 'NextParameter', 'OptionalExpectChar']; 0x0083d310, 0x0083d360, 0x0083dcd0, 0x0083e050
- `ArgScript::Line` — ['FromString', 'GetArgumentAt', 'GetArguments', 'GetArgumentsCount', 'GetArgumentsRange', 'GetEnum']; 0x00838000, 0x00838010, 0x00838100, 0x00838190, 0x00838210, 0x00838400
- `ArgScript::LineOption` — []; no declared address
- `ArgScript::ParseLine_t` — ['ParseLine_t']; no declared address
- `ArgScript::PrintF_ptr` — ['PrintF_ptr']; no declared address
- `ArgScript::SetData_t` — ['SetData_t']; no declared address
- `ArithmeticaFunction` — []; no declared address
- `ArithmeticaState` — []; no declared address
- `Attribute` — []; no declared address
- `AttributePointer` — []; no declared address
- `Audio` — ['PlayAudio', 'PlayProceduralAudio', 'SetProperty', 'SetPropertyString', 'StopAudio']; 0x00436390, 0x00436400, 0x00571f80, 0x00572020, 0x00572070
- `Audio::AudioSystem` — ['CreateAudioTrack', 'Get']; 0x00a20670
- `AudioSystem` — []; no declared address
- `BasicLockRefCounted` — ['BasicLockRefCounted_virtual_dtor']; no declared address
- `BehaviourTimeOscillator` — []; no declared address
- `BehaviourTimeSmoothRamp` — []; no declared address
- `BiStateEffect` — []; no declared address
- `BoundingBox` — []; no declared address
- `COMSerializer` — []; no declared address
- `CachedResourceObject` — []; no declared address
- `Camera` — []; no declared address
- `Capabilities` — []; no declared address
- `CascadeEffect` — []; no declared address
- `CellGFXObjectData` — []; no declared address
- `Chunk` — []; no declared address
- `CinematicAction` — []; no declared address
- `CinematicVignetteActionData` — []; no declared address
- `ClassInfo` — []; no declared address
- `ClassSerializer` — []; no declared address
- `Clock` — ['GetElapsedTicks', 'GetElapsedTime', 'Pause', 'SetMode']; 0x0093a110, 0x0093a250, 0x0093a310, 0x0093a550
- `CnvAnimation` — []; no declared address
- `CnvAnimationVariation` — []; no declared address
- `CnvDialog` — []; no declared address
- `CnvDialogResponse` — []; no declared address
- `CnvEventLog` — []; no declared address
- `CnvText` — []; no declared address
- `CnvUnknown` — []; no declared address
- `ColorHSV` — []; no declared address
- `ColorRGB` — []; no declared address
- `ColorRGBA` — []; no declared address
- `CombatantKilledMessage` — []; no declared address
- `ComboBoxDrawable` — []; no declared address
- `CompiledState` — []; no declared address
- `ComponentSerialization` — []; no declared address
- `ConversationResource` — []; no declared address
- `CoreAllocatorAdapter` — []; no declared address
- `CoreDeleterAdapter` — []; no declared address
- `CreatureGamePartUnlocking` — []; no declared address
- `CreatureModeStrategies::Interact` — []; no declared address
- `CrossGameData` — []; no declared address
- `Data` — []; no declared address
- `DatabasePackedFile` — []; no declared address
- `DefaultDrawable` — []; no declared address
- `DefaultItemFrameUI` — []; no declared address
- `DefaultLayoutElement` — []; no declared address
- `DefaultMessageListener` — []; no declared address
- `DefaultObject` — []; no declared address
- `DefaultRefCounted` — ['AddRef', 'DefaultRefCounted_virtual_dtor', 'GetReferenceCount', 'Release']; no declared address
- `DefaultWinProc` — []; no declared address
- `Deform` — []; no declared address
- `Deforms` — []; no declared address
- `DialogDrawable` — []; no declared address
- `Dimensions` — []; no declared address
- `Direct3D::IDirect3D9` — ['CheckDepthStencilMatch', 'CheckDeviceFormat', 'CheckDeviceFormatConversion', 'CheckDeviceMultiSampleType', 'CheckDeviceType', 'CreateDevice']; no declared address
- `Direct3D::IDirect3DBaseTexture9` — ['GenerateMipSubLevels', 'GetAutoGenFilterType', 'GetLOD', 'GetLevelCount', 'SetAutoGenFilterType', 'SetLOD']; no declared address
- `Direct3D::IDirect3DCubeTexture9` — ['AddDirtyRect', 'GetCubeMapSurface', 'GetLevelDesc', 'LockRect', 'UnlockRect']; no declared address
- `Direct3D::IDirect3DDevice9` — ['BeginScene', 'BeginStateBlock', 'Clear', 'ColorFill', 'CreateAdditionalSwapChain', 'CreateCubeTexture']; no declared address
- `Direct3D::IDirect3DIndexBuffer9` — ['GetDesc', 'Lock', 'Unlock']; no declared address
- `Direct3D::IDirect3DPixelShader9` — ['GetDevice', 'GetFunction']; no declared address
- `Direct3D::IDirect3DQuery9` — ['GetData', 'GetDataSize', 'GetDevice', 'GetType', 'Issue']; no declared address
- `Direct3D::IDirect3DResource9` — ['FreePrivateData', 'GetDevice', 'GetPriority', 'GetPrivateData', 'GetType', 'PreLoad']; no declared address
- `Direct3D::IDirect3DStateBlock9` — ['Apply', 'Capture', 'GetDevice']; no declared address
- `Direct3D::IDirect3DSurface9` — ['GetContainer', 'GetDC', 'GetDesc', 'LockRect', 'ReleaseDC', 'UnlockRect']; no declared address
- `Direct3D::IDirect3DSwapChain9` — ['GetBackBuffer', 'GetDevice', 'GetDisplayMode', 'GetFrontBufferData', 'GetPresentParameters', 'GetRasterStatus']; no declared address
- `Direct3D::IDirect3DTexture9` — ['AddDirtyRect', 'GetLevelDesc', 'GetSurfaceLevel', 'LockRect', 'UnlockRect']; no declared address
- `Direct3D::IDirect3DVertexBuffer9` — ['GetDesc', 'Lock', 'Unlock']; no declared address
- `Direct3D::IDirect3DVertexDeclaration9` — ['GetDeclaration', 'GetDevice']; no declared address
- `Direct3D::IDirect3DVertexShader9` — ['GetDevice', 'GetFunction']; no declared address
- `Direct3D::IDirect3DVolume9` — ['FreePrivateData', 'GetContainer', 'GetDesc', 'GetDevice', 'GetPrivateData', 'LockBox']; no declared address
- `Direct3D::IDirect3DVolumeTexture9` — ['AddDirtyBox', 'GetLevelDesc', 'GetVolumeLevel', 'LockBox', 'UnlockBox']; no declared address
- `Direct3D::IUnknown` — ['AddRef', 'QueryInterface', 'Release']; no declared address
- `DirectionalLight` — []; no declared address

The JSON contains all 1199 naming-only families; this report shows the first 150 in stable order.

## Contradictions

All **2525** machine-detected contradictions are preserved in JSON. The principal classes are:

- `ambiguous_vtable_class_ownership`: 8
- `artifact_count_mismatch`: 1
- `base_layout_larger_than_derived`: 3
- `base_layout_prefix_mismatch`: 201
- `binary_function_count_mismatch`: 1
- `duplicate_inheritance_base_identity`: 2
- `duplicate_sdk_function_address`: 3
- `header_class_missing_xml_structure`: 532
- `historical_triage_reconciliation_conflicts`: 1
- `identical_vtable_slot_sequences`: 107
- `layout_size_mismatch`: 9
- `queue_addresses_outside_family_universe`: 1
- `sdk_address_absorbed_by_function`: 1188
- `sdk_address_partition_mismatch`: 1
- `sdk_boundary_repair_partition`: 1
- `secondary_vtable_track_preserved_limit`: 10
- `static_sdk_function_in_vtable_data`: 162
- `unresolved_header_base`: 67
- `virtual_methods_without_sdk_vftable_layout`: 227

No contradiction was removed by preferring the SDK, triage, header, layout, or binary source.

## Secondary dossier evidence

16 committed dossier JSON files were retained as bounded secondary context and are hash-pinned in JSON; dossiers without a vtable/class record remain explicitly marked as structural or call context.

- `docs/analysis/dossiers/cell-movement.json` — topic `cell-movement`, scope `vtable_and_class_records`, 1 vtable records, 6 retained function records
- `docs/analysis/dossiers/unknown-high/cell-object-pool-lifecycle.json` — topic `cell-object-pool-lifecycle`, scope `bounded_structural_or_call_context`, 0 vtable records, 0 retained function records
- `docs/analysis/dossiers/unknown-high/empire-idcolor-pick.json` — topic `empire-idcolor-pick`, scope `bounded_structural_or_call_context`, 0 vtable records, 0 retained function records
- `docs/analysis/dossiers/unknown-high/gamemode-state-player-id.json` — topic `gamemode-state-player-id`, scope `bounded_structural_or_call_context`, 0 vtable records, 0 retained function records
- `docs/analysis/dossiers/unknown-high/message-handler-registration.json` — topic `message-handler-registration`, scope `bounded_structural_or_call_context`, 0 vtable records, 0 retained function records
- `docs/analysis/dossiers/unknown-high/pdtk-text-widget.json` — topic `pdtk-text-widget`, scope `bounded_structural_or_call_context`, 0 vtable records, 0 retained function records
- `docs/analysis/dossiers/unknown-high/sim-object-lookup-strategy.json` — topic `sim-object-lookup-strategy`, scope `bounded_structural_or_call_context`, 0 vtable records, 0 retained function records
- `docs/analysis/dossiers/unknown-high/sim-singleton-accessors-2.json` — topic `sim-singleton-accessors-2`, scope `bounded_structural_or_call_context`, 0 vtable records, 0 retained function records
- `docs/analysis/dossiers/unknown-high/sim-singleton-accessors-3.json` — topic `sim-singleton-accessors-3`, scope `bounded_structural_or_call_context`, 0 vtable records, 0 retained function records
- `docs/analysis/dossiers/unknown-high/sim-singleton-accessors-4.json` — topic `sim-singleton-accessors-4`, scope `bounded_structural_or_call_context`, 0 vtable records, 0 retained function records
- `docs/analysis/dossiers/unknown-high/sim-singleton-accessors.json` — topic `sim-singleton-accessors`, scope `bounded_structural_or_call_context`, 0 vtable records, 0 retained function records
- `docs/analysis/dossiers/unknown-high/space-event-record-pair.json` — topic `space-event-record-pair`, scope `bounded_structural_or_call_context`, 0 vtable records, 0 retained function records
- `docs/analysis/dossiers/unknown-high/space-player-data-accessors-2.json` — topic `space-player-data-accessors-2`, scope `bounded_structural_or_call_context`, 0 vtable records, 0 retained function records
- `docs/analysis/dossiers/unknown-high/space-player-data-accessors-3.json` — topic `space-player-data-accessors-3`, scope `bounded_structural_or_call_context`, 0 vtable records, 0 retained function records
- `docs/analysis/dossiers/unknown-high/space-player-data-accessors.json` — topic `space-player-data-accessors`, scope `bounded_structural_or_call_context`, 0 vtable records, 0 retained function records
- `docs/analysis/dossiers/unknown-high/star-system-regen.json` — topic `star-system-regen`, scope `bounded_structural_or_call_context`, 0 vtable records, 0 retained function records

## Provenance and determinism

- JSON keys and every emitted array are stably sorted; no generation timestamp is included.
- The committed and export copies of `vtables.json` are byte-identical (`f4161d3d99441ca4e84a2dcae6de2f4d83b3d9d2df2872e45bee8ee8f8d7f96b`).
- The serialized vtable file contains 300 cluster records while its metadata says 16,107 clusters; both counts are retained.
- The read-only `knowledgegraph/spore.db` projection is included with node/edge counts and 12 `inheritsFrom` edges; it remains a sidecar projection, not binary truth.
- Community SDK/header material is GPL reference-only and no SDK source is copied into these artifacts.
- The machine-readable provenance section contains SHA-256 values and authority labels for every source class used.

## Unresolved

- Which exact concrete class owns each of the 2,775 vtable candidates without an SDK slot match?
- Are the identical 21-slot tables at 0x013fa974 and 0x01419794 duplicate subobjects, interface identity tables, or scan artifacts?
- Which SDK addresses absorbed into larger Ghidra functions correspond to independent logical methods rather than labels inside one body?
- Which static methods in long runs are allocation helpers rather than virtual slots?
- Which header-only classes have no binary implementation in this executable?
- Can live read-only Ghidra function/xref queries resolve remaining class candidates when a program is open?
