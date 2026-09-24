# Render engine boundary archaeology

## Scope and evidence stance

This report synthesizes the nine isolated boundary studies under `knowledgegraph/research/render-boundary/`. It separates gameplay-owned semantics from the engine wrappers used to express them, renderer-owned mechanics, third-party implementation, platform runtime, and unresolved questions.

The evidence is static: SDK names, decompilation, exported structures, xrefs, and existing campaign documents. **No positive original Cell-mode trace or final-frame pixel oracle is available**, so none of the findings below is runtime validation. Current OpenSpore behavior is treated as a clean-room comparison point, not as proof of the original.

Canonical data: `knowledgegraph/research/render-boundary.json`.

The report uses the exact flow form: `gameplay -> original engine boundary -> semantic operation -> required OpenSpore abstraction`.

## Classification summary

| Classification | Records | Meaning |
|---|---:|---|
| `GAMEPLAY_SEMANTIC` | 9 | Authoritative simulation, entity, input, animation-intent, vehicle, or mode state changes |
| `GAMEPLAY_RELEVANT_ENGINE_INTERFACE` | 11 | Typed wrappers required to express gameplay intent or query shared engine state |
| `PRESENTATION_ONLY` | 5 | Visual results with no demonstrated gameplay-state transition |
| `RENDERER_INFRASTRUCTURE` | 7 | Passes, device, traversal, upload, state, and draw mechanics owned below gameplay |
| `THIRD_PARTY_IMPLEMENTATION` | 5 | RenderWare, compiled-object, and replaceable legacy shell internals |
| `PLATFORM_RUNTIME` | 2 | Direct3D 9 and Win32 host details |
| `UNKNOWN` | 9 | Event, pose, vehicle, Swarm, ownership, LOD, mapping, and runtime questions not closed by static evidence |

A `Graphics::`, `Anim::`, or `Swarm::` name is not itself a classification. A gameplay-facing wrapper remains a gameplay-relevant engine interface even when it eventually reaches a third-party backend.

## 1. Meaningful gameplay to RenderWare/D3D crossings

The meaningful crossings are not calls to `IDirect3DDevice9`; they are the gameplay operations whose inputs come from camera, content, scene, animation, resource, or mode state maintained behind engine interfaces.

### Camera and movement

```text
Cell pointer input
  -> Graphics::IRenderer Layer / App::cViewer / camera-origin helper
  -> intersect camera ray with gameplay movement plane
  -> Cell target position, travel orientation, and moving state
  -> ICameraRayProvider + IPlayerMovement
```

The boundary is meaningful because `MovePlayerToMousePosition` writes gameplay state. The renderer accessor and camera service are wrappers; the ray-plane result and target mutation are semantics.

### Gameplay entity to presentation identity

```text
Pooled Cell identity
  -> cCellGFX CellGFXObjectData allocation and reciprocal links
  -> bind rebuildable model or creature presentation handle
  -> EntityId with optional replaceable PresentationHandle
```

This is a gameplay-owned identity association. Visual representation may be detached or rebuilt without destroying the gameplay entity.

### Content identity to visual resources

```text
Cell / Populate / effect-map record
  -> cCellGFX preload traversal and GetModelKeyForCellResource
  -> acquire model, creature, texture, effect, and material identity for the stage
  -> IContentStore + IModelKeyResolver + IPresentationResourceCache
```

Resource keys are semantic content identity. The RW model, raster, compiled state, and D3D texture are replaceable handles obtained later.

### Animation intent

```text
Cell interaction or entity transition
  -> cCellObjectData current clip and blend writes / animation dispatch
  -> preserve current clip, target clip, blend policy, and phase
  -> IAnimationController
```

The visible skeleton is downstream, but clip and transition state live on the gameplay object and are required semantics.

### Scene graph and transforms

```text
Gameplay position, orientation, scale, and visibility
  -> cCellGFX world/layer attachment, IModelWorld state, and renderer submission
  -> preserve stable scene membership and ordered draw snapshot
  -> ISceneStage + IEntityView + IRenderQueue
```

`Transform::PreTransformBy` is semantic value composition. `Graphics::GlobalState::SetTransform`, RW stream caches, and D3D transforms are renderer state.

### Material and texture intent

```text
GMDL material ID and texture reference
  -> material manager / texture manager / preloader
  -> resolve material definition and immutable texture asset
  -> IMaterialRegistry + ITextureStore + IMaterialBindings
```

Stable IDs, texture keys, material-slot meaning, and draw ordering matter. RW compiled shaders, raster pointers, and D3D sampler internals do not belong to gameplay.

### Effects and presentation

```text
Gameplay effect request
  -> cCellGFX effect-map slot and IEffectsWorld
  -> create, place, update, replace, and release a visual instance
  -> IEffectPresenter
```

The request may be gameplay-relevant; the effect instance and its particles are presentation-only until evidence proves a gameplay read.

### Mode lifecycle

```text
Game-mode selection
  -> cGameModeManager::SetActiveModeAt
  -> old mode exit, new mode enter, display activation, update, exit, dispose
  -> IGameModeRegistry + IGameMode lifecycle
```

Mode selection changes active gameplay and therefore is semantic. Stage display and resource teardown must follow that lifecycle.

## 2. Boundaries OpenSpore genuinely needs

The minimal required set is:

1. **Stable content identity** — `ResourceKey`, `ModelKey`, `MaterialId`, and `TextureKey`, distinct from loaded handles.
2. **Shared resource lifetime** — model, mesh, texture, material, pose, and effect handles with explicit retain/detach/retire stages.
3. **Camera state and ray queries** — one coherent view/projection/viewport snapshot used by both movement picking and rendering.
4. **Cell mode lifecycle** — initialize, old-exit/new-enter, update, stop display, detach views, and dispose in order.
5. **Cell presentation stage** — mode-owned world/layer membership, preload readiness, activation, and teardown.
6. **Entity presentation association** — a replaceable view handle tied to stable gameplay entity identity.
7. **Animation controller** — current clip, target clip, blend policy, loop, and time scale independent of the pose evaluator.
8. **Material and texture content lookup** — stable content definitions and assets, with missing/unsupported results.
9. **Effect presenter** — typed effect requests and independently owned visual instances.
10. **Ordered render submission** — visible mesh/effect identity, world transform, material, layer/pass, and draw order.
11. **Input and pick state** — pointer-to-Camera and Cell-query results that can gate gameplay without exposing renderer layers.
12. **Vehicle locomotion state** — position, orientation, velocity, speed, and model-transform intent.

These are not RenderWare replacements. They are the semantic seams needed to keep gameplay deterministic while the presentation backend changes.

## 3. Presentation-only boundaries

### Cursor and overlay

Cursor IDs, drop icons, z-order, and screen overlays are visual feedback after a selection or hover transition. They do not select entities or change simulation.

### HUD rollover pixels

`cCellUI::ShowHealthRollover` consumes gameplay health and creates an expiring HUD record. Health and damage are semantic; rollover scale, timer, layout, and pixels are presentation-only. Its no-GFX early-out is a presentation-association dependency, not evidence that the health value is renderer-owned.

### Lighting and shadows

`StartDisplay` activates lighting worlds and resets shadows after the stage is built. Ordering matters, but light color, shadow appearance, fog, and fixed-function pixel behavior do not mutate gameplay under current evidence.

### Frustum culling

Cell and renderer paths update frustum state per frame, but no reviewed consumer gates movement, interaction, spawning, or other gameplay transitions. Render culling remains presentation-only unless a gameplay visibility consumer is proven.

### Visual effect instances

Effect-map selection, placement, update, and release are visual. The gameplay effect event that triggers them may have its own semantic state; the effect instance does not inherit that status merely because Swarm or RW implements its particles.

## 4. Third-party infrastructure to ignore for reconstruction

### RenderWare object and cache internals

Do not reproduce RenderWare mesh, raster, compiled-state, skeleton, blend-shape, model-world, stream-cache, index-scope, or unmanaged-list layouts. Preserve only stable content identity, mesh topology, material and texture slots, state order, draw result, and resource lifetime.

### Compiled D3D9 shader objects

The binary contains precompiled D3D9 shader bytecode. The `d3dx9_27.dll` import has no observed call sites. Shader containers, raster lists, vertex declarations, and backend vtables are replaceable implementation; material IDs and per-draw semantics remain above them.

### Direct3D 9

Raw `IDirect3D9` and `IDirect3DDevice9` calls are platform runtime. The statically linked RenderWare DX9 target is third-party implementation. Gameplay and mode code do not need D3D object identity or HRESULT plumbing.

### Win32 and UTFWin

Win32 message IDs, QPC implementation, UTFWin window hierarchy, message-manager storage, drawable implementation, and pdtk grammar are host/shell compatibility details. Normalized event order, window dimensions, monotonic time, UI selection, and mode requests are the retained contracts.

### RW skeleton/pose objects

Bone, morph, and deformation buffers have not been shown to be read by gameplay. Replace RW evaluator internals with a provider-neutral pose path, but do not claim its exact timing, fallback, or memory policy from section headers alone.

## 5. Gameplay semantics hidden behind engine interfaces

The highest-risk cases are:

- **Camera-to-movement:** a Graphics layer lookup and camera helper lead to target position, orientation, and moving state.
- **Animation transition state:** `PlayAnimation` writes Cell clip and blend fields before any pose is visible.
- **Presentation association:** `mGFXObjectIndex` and reciprocal CellGFX links bridge stable gameplay identity to replaceable visual state.
- **Content remapping:** nested Cell resources select model, material, texture, and effect identity before preload.
- **Input selection:** pointer events query camera and Cell space, then write selection and hover state used by later interaction.
- **Mode transitions:** changing the active mode changes input routing, simulation singleton ownership, display activation, and teardown order.
- **Vehicle state:** position, orientation, velocity, desired speed, and transform-dirty state are gameplay even when model fields appear in the same structure.
- **Editor creature state:** target position, angle, clip, and event intent belong to editor semantics, not to pose evaluation internals.

The classification boundary follows the semantic operation, not the namespace of the original function.

## 6. Animation and pose findings

### Established

- `Simulator::Cell::PlayAnimation` computes blend-in and blend-out values and writes `cCellObjectData` current-animation and transition fields.
- Missing model identity or Cell GFX association suppresses the operation.
- `AnimatedCreature` and `IAnimWorld` expose clip, loop, mode, creature, and update-phase wrappers.
- RW4 content contains KeyframeAnim, Skeleton, AnimationSkin, BlendShape, and BlendShapeBuffer sections.
- Editor creature controllers directly maintain target/current position and angle and dispatch animation events.
- Vehicle locomotion state is established independently of any proven animation binding.

### Not established

- The original gameplay event ID and delivery path into `PlayAnimation`.
- The complete `cCellObjectData` transform to model, skeleton, pose, morph, and draw path.
- The order of gameplay update, `IAnimWorld::Update`, `UpdateCreatures`, `PostUpdateCreatures`, pose evaluation, visibility, and draw.
- Blend completion, interruption, loop exhaustion, transition callbacks, and bind-pose fallback.
- Vehicle-to-animation coupling.
- Swarm animation ownership and event semantics.
- Whether any gameplay system reads bones, morphs, or pose buffers.

Current OpenSpore animation/effect helpers reproduce isolated deterministic calculations. They do not establish the missing original event-to-pose integration.

## 7. Minimal modern interfaces

These are boundary concepts, not an implementation plan:

| Concept | Required operations or state |
|---|---|
| `IContentStore` | fetch stable resource identity as owned bytes or explicit error |
| `IPresentationResourceCache` | preload/deduplicate model, creature, texture, and effect handles; publish readiness |
| `ICameraService` / `ICameraRayProvider` | active camera, coherent view/projection snapshot, pointer ray, explicit unavailable result |
| `IPlayerMovement` | consume ray, intersect movement plane, mutate target position/orientation/moving state |
| `ISceneStage` | create world/layer graph, preload, start/stop display, shutdown idempotently |
| `IEntityPresentationRegistry` | attach/rebuild/detach a replaceable view without changing EntityId |
| `IEntityView` | snapshot transform, opacity, animation, model, and visibility without mutating gameplay |
| `IAnimationController` | current/target clip, blend, loop, mode, time scale, and ordered updates |
| `IPoseEvaluator` | evaluate an explicit animation state into a provider-neutral pose snapshot |
| `IMaterialRegistry` / `ITextureStore` | resolve stable material and texture content into shared handles |
| `IMaterialBindings` | bind material, texture slots, constants, and pipeline state in explicit order |
| `IEffectPresenter` | create, place, update, stop, and release effect instances |
| `IRenderQueue` | submit mesh/effect identity, transform, material, layer, and pass order |
| `IGameMode` / `IGameModeRegistry` | initialize, old-exit/new-enter, update, exit, and dispose mode-owned state |
| shared resource handles | retain, detach, last-owner release, and backend retirement separated |

The crucial split is between a stable resource identity, a shared resource handle, an entity's presentation view, and a backend draw object.

## 8. Unresolved dependencies

The canonical synthesis has 12 unresolved dependency records. The most consequential are:

1. **Camera follow and unprojection** — movement can be wrong even with a correct ray-plane implementation.
2. **Event-to-animation transport** — known clip writes have no proven gameplay event cause.
3. **Pose propagation and phase order** — animation intent does not establish rendered pose or frame timing.
4. **Vehicle animation coupling** — locomotion does not reveal wheel, suspension, or body pose behavior.
5. **Swarm ownership** — no caller, state machine, or event lifetime is established.
6. **Material-slot mapping** — content IDs and texture references do not prove exact backend slot equivalence.
7. **Mip and sampler policy** — decoded mips do not establish runtime selection or filtering.
8. **Teardown and GPU retirement** — logical ownership does not establish safe backend destruction timing.
9. **Model-world LOD and background load** — SDK names alone do not establish thresholds, ordering, or failure behavior.
10. **Runtime validation** — no positive Cell, editor, vehicle, pose, teardown, or pixel trace closes the static-to-runtime gap.

Until these are characterized, modern code must label assumptions rather than treating current approximations as recovered contracts.

## 9. Functions that looked like RenderWare but carry gameplay semantics

| Function family | Why it looked renderer-related | Actual semantic boundary |
|---|---|---|
| `MovePlayerToMousePosition` | Calls `Graphics::IRenderer::Get`, Layer, and a camera-origin helper | Camera ray to movement-plane result and player target mutation |
| `GetModelKeyForCellResource` | Returns a model identity used by Cell GFX | Stable content-to-model identity selection |
| `cCellGFX::Initialize` / `PreloadResources` / `StartDisplay` | Creates Graphics worlds, layers, effects, and models | Mode-owned stage lifecycle and presentation associations required by gameplay |
| `cCellGFX::InstanceEffectOnCell` | Creates a Swarm visual effect | Typed effect request and entity-scoped presentation instance |
| `Simulator::Cell::PlayAnimation` | Dispatches through Anim and model-world interfaces | Cell clip, blend, and transition state |
| `Transform::PreTransformBy` | Feeds render matrices | Gameplay/entity transform composition and coordinate order |
| `cVehicle` model and locomotion fields | Co-located with Graphics model handles | Vehicle simulation and locomotion state |
| Cell mode `OnMouseDown` / `OnMouseUp` | Uses renderer Layer and camera queries | Input consumption, pick result, and UI selection transition |
| `cGameModeManager::SetActiveModeAt` | Activates display-backed modes | Gameplay mode identity and lifecycle semantics |
| Editor creature controller | Updates AnimatedCreature and shadow world | Editor motion, angle, clip, and event intent |

The inverse mistake also matters: `RenderWare::Mesh`, `CompiledState`, raster, stream, model-world, and skeleton functions are backend even when nearby gameplay code supplies their content and transforms.

## Topic coverage

| Requested topic | Primary coverage |
|---|---|
| Meaningful gameplay crossings | Section 1 |
| Boundaries OpenSpore needs | Section 2 |
| Presentation-only boundaries | Section 3 |
| Third-party infrastructure to ignore | Section 4 |
| Hidden gameplay semantics | Section 5 |
| Animation and pose findings | Section 6 |
| Minimal modern interfaces | Section 7 |
| Unresolved dependencies | Section 8 |
| Misleading RenderWare-looking functions | Section 9 |

## Primary artifacts and corroborating sources

Worker artifacts:

- `knowledgegraph/research/render-boundary/01-renderware-objects.json`
- `knowledgegraph/research/render-boundary/02-material-textures.json`
- `knowledgegraph/research/render-boundary/03-camera-transforms.json`
- `knowledgegraph/research/render-boundary/04-animation-pose.json`
- `knowledgegraph/research/render-boundary/05-scene-entity.json`
- `knowledgegraph/research/render-boundary/06-d3d-platform.json`
- `knowledgegraph/research/render-boundary/07-resource-lifetime.json`
- `knowledgegraph/research/render-boundary/08-gameplay-renderer.json`
- `knowledgegraph/research/render-boundary/09-ui-presentation.json`

Key corroborating sources:

- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__MovePlayerToMousePosition.c:30-61`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__PlayAnimation.c:22-58`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__Initialize.c:34-235`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__PreloadResources.c:22-175`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__StartDisplay.c:16-88`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__InstanceEffectOnCell.c:24-101`
- `docs/RENDERWARE-RESEARCH.md:15-25,113-173,271-325`
- `docs/replacement-boundaries.md:93-121`
- `docs/analysis/dossiers/cell-movement.md:8-10,46-55,99-101,133-151`
- `docs/MATERIALS-DESIGN.md:10-42,72-117,131-145`
- `docs/analysis/campaigns/cell-stage-campaign.md:455-519`
