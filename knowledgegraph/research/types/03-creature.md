# 03 — Creature, editable model, creature data, parts, decorations, and evolution

Status: research only. This artifact records static evidence for `SporeApp.exe` 3.1.0.22 (`x86:LE:32`, image base `0x00400000`). It does not claim runtime behavior, rewrite triage, mutate Ghidra, or provide proprietary assets or source.

## Scope

The partition covers:

- creature simulation state and the `cCreatureAnimal` subtype;
- `cCreatureGameData`, ability, evolution, and herd progression surfaces;
- species profiles and registry data;
- editor models, rigblocks, resources, and creature-data serialization;
- animated creature blocks, controllers, and the editor animation world;
- ornaments/decorations, collectables, and related data containers.

Current OpenSpore code is not used as evidence for original-game layouts or semantics. No live Ghidra program was open during this task.

## Evidence policy

SDK XML, SDK headers, Ghidra structure exports, repaired SDK boundaries, triage projections, and committed decomp-gap records are static evidence. Confidence applies only to the bounded claim made by an item. Vtable candidates are structural observations only because the binary has no MSVC RTTI. Conflicts are preserved rather than normalized.

## Type registry

| Type | Size | Role | Confidence |
|---|---:|---|---|
| `Simulator::cCreatureBase` | `0xfc0` / 4032 | Base creature simulation object | SUPPORTED layout; INFERRED mechanics |
| `Simulator::cCreatureAnimal` | `0x16a0` / 5792 | Animal creature subtype | SUPPORTED layout; INFERRED mechanics |
| `Simulator::cCreatureGameData` | `0x4c` / 76 | Brain level, avatar scale, ability, evolution, glide state | SUPPORTED; SDK size conflict |
| `Simulator::cCreatureAbility` | `0x13c` / 316 | Ability metadata and progression cost | SUPPORTED layout; INFERRED mechanics |
| `Simulator::cSpeciesProfile` | `0xeec` / 3820 | Species profile record | SUPPORTED identity; CONTESTED layout |
| `Editors::EditorModel` | `0xe0` / 224 | Editable model and rigblock collection | SUPPORTED |
| `Editors::EditorRigblock` | `0xe08` / 3592 | Editable rigblock | SUPPORTED layout; INFERRED mechanics |
| `Editors::cEditorResource` | `0xac` / 172 | Editor resource base | SUPPORTED layout |
| `Editors::cEditorResourceBlock` | `0x1d8` / 472 | Serialized editor block | SUPPORTED layout |
| `Editors::cCreatureDataResource` | `0x128` / 296 | Creature-data resource and serialization payload | SUPPORTED layout |
| `Anim::CreatureBlock` | `0x468` / 1128 | Animated creature block | SUPPORTED layout |
| `Anim::AnimatedCreature` | `0x19c` / 412 | Runtime animated creature | SUPPORTED layout |
| `Editors::EditorCreatureController` | `0x88` / 136 | Target/current editor animation state | SUPPORTED |
| `Editors::cEditorAnimWorld` | `0x48` / 72 | Creature-ID controller registry owner | SUPPORTED |
| `Editors::cEditor` | `0x600` / 1536 | Editor orchestrator | SUPPORTED |
| `Editors::cSpeciesManager` | `0xe4` / 228 | Species profile registry | SUPPORTED |
| `Simulator::cOrnament` | `0x238` / 568 | Decoration/ornament object | SUPPORTED layout; INFERRED mechanics |
| `Simulator::cOrnamentData` | `0x34` / 52 | Ornament definition data | SUPPORTED layout |
| `Simulator::cHerd` | `0x220` / 544 | Herd/evolution threshold state | SUPPORTED layout |
| `Simulator::cCollectableItems` | `0x6dac` / 28076 | Collectable-item registry | SUPPORTED layout |
| `App::cCreatureModeStrategy` | partial | Evolution/UI and part-unlock strategy | SUPPORTED identity; PARTIAL layout |

Primary evidence is in `.spore-analysis/ghidra-exports/structs.tsv`, `structs_fields.tsv`, and `functions.tsv`, with SDK structure definitions in `/home/juanr/apps/Spore-ModAPI/SDKtoGhidra/SporeGhidra_march2017.xml`.

## Representative fields

The JSON artifact carries the complete bounded field records. The most reconstruction-relevant fields are:

| Type | Offset | Field | Meaning/evidence |
|---|---:|---|---|
| `cCreatureGameData` | `0x00` | `mCurrentBrainLevel` | Current brain level; `00d2e380` |
| `cCreatureGameData` | `0x04` | `mAvatarNormalizingScale` | Avatar scale; `00d2e720`, `00d2e800` |
| `cCreatureGameData` | `0x24` | `mAbilityMode` | Ability mode; `00d2e490`, `00d2e4a0` |
| `cCreatureGameData` | `0x28` | `mEvolutionPoints` | Evolution state; `00d2e350`, `00d2e480`, `00d2e8a0` |
| `cCreatureGameData` | `0x2c` | `DEPRECATED_mLearnedAbilities` | Legacy packed ability state |
| `cCreatureGameData` | `0x34` | `mLearnedAbilities` | Three ability slots/levels |
| `cCreatureGameData` | `0x40` | `mGlideStartPosition` | Glide transition state; `00d2e580` |
| `cCreatureAbility` | `0x48` | `mAnimationIDs` | Ability animation vector; `004d3d20`, `004d92b0` |
| `cCreatureAbility` | `0x10c` | `mDNAPoints` | Ability progression cost |
| `EditorModel` | `0x0c` | `mKey` | Editable model key; `004ae250` |
| `EditorModel` | `0x18` | `mRigblocks` | Editable rigblock vector |
| `EditorModel` | `0x5c` | `mName` | Model name; `004ae260` |
| `EditorModel` | `0xa4` | `mColors` | Model colors; `004ae250` |
| `EditorRigblock` | `0x28` | `mpEditorModel` | Associated editor model; `0043ac40` |
| `cCreatureDataResource` | `0x98` | `mRigblocks` | Serialized rigblock records; Read/Write boundaries |
| `cCreatureDataResource` | `0xac` | `mCapabilityIDs` | Capability tags |
| `cCreatureDataResource` | `0xd4` | `mAnimationIDs` | Serialized animation IDs |
| `CreatureBlock` | `0x104` | `instanceID` | Block instance ID; `00e64980` |
| `CreatureBlock` | `0x108` | `groupID` | Block group ID |
| `CreatureBlock` | `0x150` | `capabilities` | Capability record |
| `CreatureBlock` | `0x1f8` | `pParent` | Hierarchy link |
| `EditorCreatureController` | `0x20` | `mTargetPosition` | Target position; `0059b0f0`, `0059cf00` |
| `EditorCreatureController` | `0x44` | `mTargetAngle` | Target angle; `0059cea0` |
| `cEditorAnimWorld` | `0x08` | `mCreatures` | Creature-ID to controller map; `0059c6e0`, `0059cac0` |
| `cSpeciesManager` | `0x04` | `mSpeciesProfiles` | Species profile registry; `00401090`, `004df550` |
| `cHerd` | `0x94` | `mDNAEvolutionThreshold` | Herd evolution threshold |
| `cHerd` | `0x120` | `mActivateBrainLevel` | Activation brain level |
| `cHerd` | `0x124` | `mDeactivateBrainLevel` | Deactivation brain level |
| `cOrnament` | `0x24` | `mID` | Ornament identity |
| `cOrnament` | `0x64` | `mHasBeenThrown` | Throw-state flag |
| `cOrnament` | `0x74` | `mPosition` | Spatial position |
| `cOrnament` | `0x100` | `mModelKey` | Ornament model key |

## Vtables and inheritance

### vtable surfaces

- `cCreatureBase__vftable` is SDK-derived as 232 bytes and 58 slots. The candidate base `0x0146a5f0` is structural only. The inherited serialization/object prefix is approximately slots `0x00`–`0x1c`; brain-level method positions at `0xd8` and `0xdc` are SDK-order hypotheses.
- `cCreatureAnimal` has candidate `0x0146a0e0`; its object export begins with a `cCreatureBase__vftable*` at `+0x00`.
- `cEditor` has candidate `0x013f57f8`; this is a vtable-family association, not RTTI identity.
- `EditorModel` begins with two vtable pointers at `+0x00` and `+0x04`. Triage references include `0x013ef110` and several related candidates. `SetColor` at `0x004ae250` is associated with the family, but the complete slot vector is unresolved.
- `AnimatedCreature__vftable` is SDK-derived as 128 bytes and 32 slots.
- Ability, species-manager, resource, controller, and editor-world structures have object-start vtable pointers, but no complete binary slot map is committed for them.

### inheritance relationships

- `cCreatureAnimal` extends `cCreatureBase`; the exported field prefix and sizes corroborate the relationship.
- `cCreatureBase` contains an embedded `cLocomotiveObject`-style vtable/spatial/movement region.
- SDK headers declare `cInteractiveOrnament` as derived from `cOrnament`, and `cMovableDestructibleOrnament` as derived from `cInteractiveOrnament`.
- `EditorModel` contains an `INameableEntity`/`IVirtual`-like pair of vtable pointers.
- `cCreatureDataResource` and `cEditorResource` begin with a `ResourceObject`-like resource vtable/count/key prefix.
- `cSpeciesManager` begins with an `IUnmanagedMessageListener`-like vtable pointer.

## Lifecycle evidence

1. `cEditor::AddCreature` at `0x00582fe0` and `cEditor::SetEditorModel` at `0x00586b00` bound editor model/creature setup.
2. `cEditorAnimWorld` stores `map<int, EditorCreatureControllerPtr>` at `+0x08`; `GetCreatureController` is `0x0059cac0`.
3. `DestroyCreature` at `0x0059c6e0` releases the controller and erases the creature-ID map entry in committed decomp-gap evidence.
4. `EditorCreatureController::SetTargetPosition` at `0x0059b0f0` and `Update` at `0x0059b4b0` operate on target/current position and angle state.
5. `EditorModel::Dispose` at `0x004ad6f0` is a repaired SDK boundary; `cCreatureDataResource::Read` is `0x004bf770` and `Write` is `0x004bfc40`.
6. `cCreatureGameData::AddEvolutionPoints` at `0x00d2e8a0` performs bounded evolution/UI/strategy state mutation; the exact formula and all side effects remain unresolved.
7. Ornament layouts contain throw, scenario, spatial, combat, and model state, but no dedicated persisted ornament lifecycle body was established here.

## Method anchors

| VA | Method | Evidence status |
|---|---|---|
| `00d2e340` | `cCreatureGameData::Get` | SUPPORTED |
| `00d2e350` | `cCreatureGameData::GetEvolutionPoints` | SUPPORTED |
| `00d2e380` | `cCreatureGameData::GetEvoPointsToNextBrainLevel` | SUPPORTED |
| `00d2e480` | `cCreatureGameData::SetEvolutionPoints` | SUPPORTED |
| `00d2e490` | `cCreatureGameData::GetAbilityMode` | SUPPORTED |
| `00d2e4a0` | `cCreatureGameData::SetAbilityMode` | SUPPORTED |
| `00d2e580` | `cCreatureGameData::AfterGlideFinish` | SUPPORTED |
| `00d2e720` | `cCreatureGameData::CalculateAvatarNormalizingScale` | SUPPORTED |
| `00d2e800` | `cCreatureGameData::GetAvatarNormalizingScale` | SUPPORTED |
| `00d2e8a0` | `cCreatureGameData::AddEvolutionPoints` | SUPPORTED |
| `00573970` | `cEditor::SetCreatureToNeutralPose` | SUPPORTED |
| `00582fe0` | `cEditor::AddCreature` | SUPPORTED |
| `00586b00` | `cEditor::SetEditorModel` | SUPPORTED |
| `00401090` | `cSpeciesManager::Get` | SUPPORTED |
| `004df550` | `cSpeciesManager::GetSpeciesProfile` | SUPPORTED repaired boundary |
| `004ae250` | `EditorModel::SetColor` | SUPPORTED |
| `004ad6f0` | `EditorModel::Dispose` | SUPPORTED repaired boundary |
| `0043ac40` | `EditorRigblock::SetShadedDisplay` | SUPPORTED repaired boundary |
| `004bf770` | `cCreatureDataResource::Read` | SUPPORTED repaired boundary |
| `004bfc40` | `cCreatureDataResource::Write` | SUPPORTED repaired boundary |
| `004d92b0` | `cCreatureAbility::Parse` | SUPPORTED repaired boundary; body unavailable |
| `0059cac0` | `cEditorAnimWorld::GetCreatureController` | SUPPORTED |
| `0059ca70` | `cEditorAnimWorld::GetAnimatedCreature` | SUPPORTED |
| `0059c6e0` | `cEditorAnimWorld::DestroyCreature` | SUPPORTED |
| `0059cf00` | `cEditorAnimWorld::SetTargetPosition` | SUPPORTED |
| `0059cea0` | `cEditorAnimWorld::SetTargetAngle` | SUPPORTED |
| `0059b0f0` | `EditorCreatureController::SetTargetPosition` | SUPPORTED |
| `0059b4b0` | `EditorCreatureController::Update` | SUPPORTED |
| `00e64980` | `Cell::cCellGFX::PreloadCreature` | SUPPORTED named consumer |

## Semantic subsystems

### Creature simulation

`cCreatureBase` and `cCreatureAnimal` expose identity, ownership, behavior, spatial transform, locomotion, model, and editor/presentation state. The layout supports a clean separation between simulation state and animation presentation; it does not establish runtime behavior.

### Evolution and ability progression

`cCreatureGameData` is the primary bounded state contract. `cCreatureAbility` supplies animation/effect/cost metadata, including `mDNAPoints`. `cHerd` supplies DNA and brain-level thresholds, while `cCreatureModeStrategy` exposes evolution-button and part-unlock state.

### Creature editor and editable model

`cEditor` orchestrates creature insertion and model binding. `EditorModel`, `EditorRigblock`, `cEditorResource`, `cEditorResourceBlock`, and `cCreatureDataResource` form the authored-data/serialization surface. Nested rigblock, capability, animation, effect, property, and paint records should not be flattened without further evidence.

### Creature animation

`CreatureBlock` carries hierarchy and transform/capability data. `AnimatedCreature`, `EditorCreatureController`, and `cEditorAnimWorld` connect the block/model data to editor animation lookup, target interpolation, update, and destruction.

### Ornaments and collectables

`cOrnament` and `cOrnamentData` provide static decoration/ornament data surfaces. `cHerd` and `cCollectableItems` provide progression-related registries. Exact ownership, collection, and destruction semantics remain unresolved.

## Reconstruction relevance

- **P0 — evolution state:** start with `cCreatureGameData` fields and named accessors; do not invent formulas or unobserved side effects.
- **P0 — editor ownership:** use the `cEditorAnimWorld +0x08` map and controller state as the clearest bounded creation/lookup/update/destruction seam; preserve map erasure.
- **P1 — model serialization:** retain nested `EditorModel`, `cEditorResourceBlock`, and `cCreatureDataResource` structure rather than treating the 0x128 resource as a flat model.
- **P1 — animation:** keep hierarchy links, capability data, and target/current interpolation state distinct.
- **P2 — species/herd/collectables:** use these as secondary registry/progression prerequisites until the profile layout conflict and missing lifecycle bodies are resolved.

## Unresolved questions

1. Which `cSpeciesProfile` layout is authoritative? Export is `0xeec` with `mSpeciesKey` at `0xa18`; the SDK header asserts `0xa18` and different field ordering.
2. Why does `cCreatureGameData` differ by four bytes between export (`0x4c`) and SDK header (`0x50`)?
3. What are the exact binary vtable method addresses for creature, editor, and ornament candidates?
4. What is the exact serialization order for `cCreatureDataResource`, `EditorModel`, and nested block records?
5. Which methods own or release ornament, herd, and collectable objects?
6. What persisted bodies are available for `cCreatureDataResource::Read`, `Write`, `cCreatureAbility::Parse`, and the repaired containing-function aliases?

## Provenance

- `.spore-analysis/ghidra-exports/structs.tsv`
- `.spore-analysis/ghidra-exports/structs_fields.tsv`
- `.spore-analysis/ghidra-exports/functions.tsv`
- `.spore-analysis/ghidra-exports/decompiled_sdk/`
- `/home/juanr/apps/Spore-ModAPI/SDKtoGhidra/SporeGhidra_march2017.xml`
- `knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl`
- `knowledgegraph/triage/triage-2540f2ca.triage-v2.jsonl`
- `knowledgegraph/triage/sdk-boundary-repairs-2540f2ca.tsv`
- `knowledgegraph/triage/xrefs-2540f2ca.tsv`
- `knowledgegraph/research/decomp-gap/editor-core-00.json`
- `knowledgegraph/research/decomp-gap/sim-core-00.json`
- `knowledgegraph/research/decomp-gap/sim-core-01.json`
- `knowledgegraph/research/decomp-gap/sim-core-03.json`
- `docs/analysis/vtables.json`
- `docs/RECON-3.1.0.22.md`
- `AGENTS.md`
