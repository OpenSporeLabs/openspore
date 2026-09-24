# Gameplay to render dependencies

## Purpose

This report answers which parts of OpenSpore gameplay genuinely depend on the original RenderWare/D3D/presentation boundary, which dependencies are only visual, and which hidden engine calls actually preserve gameplay semantics. The normalized record set is `knowledgegraph/research/render-boundary.json`; the broader architecture summary is `docs/analysis/render-engine-boundary.md`.

All conclusions are static archaeology. Decompilation, SDK names, xrefs, and current OpenSpore code do not substitute for an original Cell-mode, editor, vehicle, pose, or final-frame runtime trace.

## Dependency map

| Domain | Gameplay dependency | Engine-facing seam | Backend-only part | Canonical result |
|---|---|---|---|---|
| Camera | Ray origin/direction gates steering and picks | Camera manager, viewer, projection, layer | Viewport upload and D3D transform calls | `GAMEPLAY_SEMANTIC` plus `GAMEPLAY_RELEVANT_ENGINE_INTERFACE` |
| Input | Pointer/key events change selection, steering, and mode state | Mode callbacks, Cell query, UI state | Cursor pixels and overlay draw | `GAMEPLAY_SEMANTIC` |
| Transforms | Position, orientation, scale, and composition affect simulation and attachment | Entity transform and CellGFX view state | Global transform dirty state and stream binding | `GAMEPLAY_SEMANTIC` plus renderer infrastructure |
| Scene graph | Entity and mode identity require stable stage/layer membership | `cCellGFX`, `ILayer`, `IModelWorld`, shadow attachment | Model-world traversal and RW scene caches | `GAMEPLAY_RELEVANT_ENGINE_INTERFACE` |
| Models and meshes | Model key, topology, and shared ownership affect visible and animated entities | Model manager, model world, resource cache | RW mesh, index, stream, and D3D buffers | `GAMEPLAY_RELEVANT_ENGINE_INTERFACE` plus `RENDERER_INFRASTRUCTURE` |
| Materials/textures | Content identity and material intent determine which resources are used | Material and texture lookup | Raster upload, compiled shader, sampler state | `GAMEPLAY_SEMANTIC` and `GAMEPLAY_RELEVANT_ENGINE_INTERFACE` |
| Animation/pose | Clip, blend, loop, target, and time scale are stateful gameplay intent | `IAnimManager`, `AnimatedCreature`, `IAnimWorld` | RW skeleton, skin, morph, and pose buffers | `GAMEPLAY_SEMANTIC`; pose propagation is `UNKNOWN` |
| Lighting | Stage activation order matters | Lighting and shadow world wrappers | D3D fixed-function lighting and pixels | `PRESENTATION_ONLY` above the stage interface |
| Effects | A gameplay event may request a visual effect | CellGFX, `IEffectsWorld`, `IVisualEffect` | Particle update and draw | `GAMEPLAY_RELEVANT_ENGINE_INTERFACE`; instance appearance is `PRESENTATION_ONLY` |
| UI | Input and selection affect interaction; health events feed HUD | Mode input, Cell UI feedback, UTFWin callback order | Cursor, overlay, and HUD pixels | Mixed semantic and presentation-only |
| Resource lifetime | Views must retain content through use and detach without losing identity | Preload, shared handles, model-world membership | Backend retirement and RW object release | `GAMEPLAY_RELEVANT_ENGINE_INTERFACE`; retirement is `UNKNOWN` |
| Game mode | Active mode controls input, simulation, display, and teardown | `cGameModeManager` and `cCellModeStrategy` | Device shutdown and final frame | `GAMEPLAY_SEMANTIC` |
| Vehicle | Locomotion, velocity, and transform intent are simulation state | Model/model-world fields | Possible vehicle mesh or pose backend | `GAMEPLAY_SEMANTIC`; animation coupling is `UNKNOWN` |

## 1. Meaningful gameplay to RenderWare/D3D crossings

The meaningful boundary is the semantic transition immediately before raw rendering. The exact flow form used throughout this campaign is:

```text
gameplay -> original engine boundary -> semantic operation -> required OpenSpore abstraction
```

### Camera-to-movement flow

```text
Cell pointer input
  -> Graphics::IRenderer Layer / camera-origin helper / App::cViewer
  -> ray-plane intersection writes player target position, orientation, and moving flag
  -> ICameraRayProvider + IPlayerMovement
```

This is the clearest case where a renderer-facing call carries no rendering semantics. The semantic operation is the gameplay mutation after obtaining the camera ray.

### Cell identity-to-view flow

```text
Pooled cCellObjectData
  -> CellGFXObjectData allocation and mGFXObjectIndex/mCellIndex association
  -> attach a replaceable model, animation, opacity, and visibility view
  -> stable EntityId + IEntityPresentationRegistry
```

Gameplay Cell identity must survive presentation detach. A failed visual rebuild can remove a view without destroying the simulation object.

### Content-to-resource flow

```text
Cell / Populate / effect-map content record
  -> cCellGFX preload and GetModelKeyForCellResource
  -> bind model, creature, texture, effect, and material identities before display
  -> IContentStore + IPresentationResourceCache
```

The crossing matters because stable content identity affects which model and material are used. The loaded RW or D3D object is not gameplay identity.

### Animation flow

```text
Cell state transition
  -> cCellObjectData clip and blend fields / animation dispatch
  -> preserve current clip, target clip, blend times, loop, mode, and time scale
  -> IAnimationController
```

The visible skeleton is downstream, but the state written before pose evaluation is gameplay-relevant.

### Transform and scene flow

```text
Gameplay position, orientation, scale, and visibility
  -> Transform composition, CellGFX attachment, model-world state, and render submission
  -> preserve coordinate order, view membership, and per-frame draw snapshot
  -> AffineTransform + IEntityView + ISceneStage + IRenderQueue
```

`Transform::PreTransformBy` is semantic value composition. `Graphics::GlobalState::SetTransform`, RW caches, and D3D stream state are backend mechanics.

### Material and mesh flow

```text
GMDL material ID, texture key, model key, and topology
  -> material/model lookup and mesh loading
  -> resolve content handles and bind ordered draw inputs
  -> IMaterialRegistry + IModelStore + IMeshDraw
```

Exact material-slot mapping, sampler policy, and pixel equivalence remain unresolved even though content identities are established.

### Mode lifecycle flow

```text
Active-mode selection
  -> cGameModeManager::SetActiveModeAt
  -> old mode exits, new mode enters, Cell display starts, updates run, then mode-owned state disposes
  -> IGameModeRegistry + IGameMode
```

Mode transition is not merely presentation plumbing; it changes which input, simulation, UI, and display are active.

## 2. Boundaries OpenSpore genuinely needs

The dependency set that crosses from gameplay into presentation is:

- **Camera state and ray query** — a coherent view/projection snapshot and pointer ray.
- **Movement-plane contract** — gameplay intersection and target mutation, not a renderer operation.
- **Mode input and pick state** — normalized events, consumed status, query handle, and selection transition.
- **Entity transform state** — authoritative position, orientation, scale, and composition order.
- **Content identity** — model, material, texture, effect, and creature keys.
- **Presentation association** — stable gameplay identity plus a detachable view handle.
- **Animation state** — clip, blend, loop, mode, time scale, and ordered transitions.
- **Stage membership** — world/layer/model-world attachment and display activation.
- **Shared resource lifetime** — preload readiness, handle retention, detach, and last-owner release.
- **Effect requests and instances** — typed requests with independently owned visual lifetimes.
- **Material and model content lookup** — stable handles separated from compiled/backend objects.
- **Ordered scene submission** — visible identity, transform, material, pass/layer, and draw order.
- **Game-mode lifecycle** — initialize, old-exit/new-enter, update, exit, and dispose.
- **Vehicle locomotion state** — transform, velocity, angular velocity, desired speed, and dirty state.

The dependency boundary should stop before culling, draw-list sorting, state caches, stream/index binding, device setup, present, and backend retirement.

## 3. Presentation-only boundaries

### Camera rendering state

View and projection are gameplay-relevant only when gameplay queries them. The viewer's internal matrices, render-update state, viewport records, and D3D transform upload are presentation mechanics.

### Scene culling

Frustum planes and world-bounds tests skip presentation work. No reviewed path shows them gating Cell movement, interaction, spawning, or other authoritative state.

### Lighting and shadows

The stage must activate the right lighting and shadow state in the right order. The light values, reset, shadow appearance, fixed-function lighting, and resulting pixels do not mutate gameplay under current evidence.

### HUD and cursor pixels

`ShowHealthRollover` receives gameplay health and creates an expiring visual record. Health remains semantic; the rollover record, scale, expiry display, and pixels are presentation. Likewise, selection is semantic while the cursor and overlay are not.

### Pure visual effects

Effect-map records, placement, particle appearance, and effect-instance lifetime are presentation. The gameplay event or effect-pool state that causes a request must be analyzed separately.

### Model-world traversal and draw lists

Membership, transform, visibility, material identity, and draw order enter as semantic inputs. Sort keys, batch encoding, traversal caches, and GPU queues are renderer-owned.

## 4. Third-party infrastructure to ignore

The replacement does not need to reproduce:

- RenderWare `Mesh`, `Raster`, `CompiledState`, `VertexDescriptionBase`, `Skeleton`, `KeyframeAnim`, `AnimationSkin`, `BlendShape`, or model-world object layouts.
- RenderWare stream/index caches, index-scope checks, unmanaged raster lists, or D3D vertex descriptor lists.
- `MaterialShader` linked-list and cache globals; only the stable material-ID-to-definition contract survives.
- Precompiled D3D9 shader object containers and the unused D3DX import.
- Raw `IDirect3D9` and `IDirect3DDevice9` vtables, D3D present parameters, HRESULT objects, and device globals.
- UTFWin window, message-manager, drawable, and pdtk implementation details.
- Win32 message IDs, `HWND`/`HDC` layouts, and QueryPerformanceCounter implementation.

The binary evidence supports this split: `docs/RENDERWARE-RESEARCH.md:15-25` identifies static RenderWare over D3D9, while `:151-173` shows that the semantically relevant draw behavior is ordered material, stream, index, and primitive state rather than RW object identity.

## 5. Gameplay semantics hidden behind engine interfaces

### Camera and movement

`Graphics::IRenderer::Get` is a service accessor, but the complete operation mutates target position, travel orientation, and moving state. Classifying the whole crossing as renderer infrastructure would erase the dependency.

### Cell content identity

`GetModelKeyForCellResource` does not draw a model. It selects a stable ResourceKey from gameplay content records. The model handle is acquired later.

### Animation transition state

`PlayAnimation` crosses Anim and model-world wrappers, but its Cell object writes are semantic. The final pose may be presentation, but clip and blend state are not.

### Entity-to-view association

`mGFXObjectIndex` and `CellGFXObjectData::mCellIndex` bridge pooled gameplay identity to replaceable visual state. Their removal must not destroy the gameplay object.

### Input and selection

Mode callbacks call renderer layers and camera helpers, but their outputs select entities, update hover, and gate simulation. Renderer layer lookup is a dependency, not the semantic operation.

### Vehicle locomotion

Vehicle model fields sit near position, orientation, velocity, desired speed, and transform-dirty state. The latter are simulation semantics; the model is a presentation binding.

### Mode lifecycle

Selecting a mode changes active input and simulation ownership, then starts and stops presentation. Treating `StartDisplay` alone as the whole boundary misses the gameplay transition.

### Editor creature state

Editor controllers own target/current position, angle, and animation-event intent. Their pose backend and shadow propagation are downstream.

## 6. Animation and pose findings

### Static findings

- Cell clip selection and blend-time calculation are directly supported by `Simulator__Cell__PlayAnimation.c:22-58`.
- `PlayAnimation` mutates current-animation and related Cell fields; the body does not directly upload a pose.
- Missing model identity or `mGFXObjectIndex` suppresses the call.
- `AnimatedCreature` and `IAnimWorld` expose clip, loop, mode, update, and creature wrappers, but most implementation bodies are unavailable.
- Editor creature target position and angle are directly visible.
- Vehicle locomotion and transform-dirty fields are established; no vehicle animation binding is established.
- RW4 assets contain animation, skeleton, skin, morph, and blend-shape sections, but section presence does not establish evaluator semantics.

### Missing links

```text
gameplay event
  -> UNKNOWN event/message transport
  -> known Cell clip and blend state
  -> UNKNOWN IAnimWorld phase order
  -> UNKNOWN model, skeleton, pose, and morph propagation
  -> renderer mesh submission
```

The middle links must not be inferred from current OpenSpore event names or test-only animation helpers.

### Required distinction

- **Gameplay-owned:** clip IDs, current/target selection, blend policy, loop, mode, time scale, editor target transform, event intent, vehicle locomotion.
- **Presentation-derived:** bone matrices, morph buffers, deformed vertices, skin pose, rendered transform.
- **Third-party implementation:** RW skeleton, keyframe, skin, blend-shape, and model-instance object layout.

The exact boundary between the second and third groups is still partially unknown because pose propagation and gameplay-read policy are not established.

## 7. Minimal modern interfaces

A minimal dependency-facing surface is:

| Interface concept | Gameplay-visible contract |
|---|---|
| `ICameraService` / `ICameraRayProvider` | Coherent camera frame, origin/direction, explicit unavailable result |
| `IPlayerMovement` | Movement-plane intersection and authoritative target mutation |
| `IInputRouter` / `ICellPickQuery` | Ordered events, consumed status, stable query handle, no renderer object |
| `IContentStore` | Stable key to owned content or explicit error |
| `IPresentationResourceCache` | Shared preload handles and readiness, independent of entity lifetime |
| `IEntityPresentationRegistry` / `IEntityView` | Replaceable presentation association and immutable per-frame snapshot |
| `IAnimationController` | Clip, blend, loop, mode, time scale, and transition state |
| `IPoseEvaluator` | Provider-neutral pose snapshot; its required gameplay contract is not yet proven |
| `ISceneStage` / `ISceneAttachment` | World/layer/model-world membership, display activation, and teardown order |
| `IMaterialRegistry` / `ITextureStore` | Stable material and texture content handles |
| `IMaterialBindings` | Per-draw slot and constant order, not a gameplay API |
| `IEffectPresenter` | Typed effect request, instance handle, update/stop/release |
| `IRenderQueue` | Ordered visible mesh/effect submission with transform and material identity |
| `IGameModeRegistry` / `IGameMode` | Old-exit/new-enter and mode-owned teardown ordering |
| Shared resource handles | Semantic retain/detach/release separated from backend retirement |

This is deliberately smaller than the original manager graph. It preserves operations that alter or determine gameplay state and hides mechanics that only produce a frame.

## 8. Unresolved dependencies

| Dependency | Affected records | Why it matters |
|---|---|---|
| Camera follow and exact unprojection | `camera-follow-unprojection`, `camera-ray-movement-plane-result`, `camera-service` | Wrong eye, target timing, handedness, or ray changes movement and picking |
| Cell event-to-animation transport | `animation-clip-transition-state`, `cell-event-animation-transport`, `effect-presenter` | Known clip writes have no proven gameplay cause |
| Pose propagation and update phase order | `animation-service-controller`, `cell-entity-view-propagation`, `pose-propagation`, `render-queue-submission` | Correct clip state can still render the wrong pose or frame |
| Vehicle animation coupling | `vehicle-locomotion-state`, `vehicle-animation-coupling`, `pose-propagation` | Vehicle movement does not reveal wheel, suspension, or body pose behavior |
| Swarm ownership | `swarm-animation-ownership`, `cell-event-animation-transport` | Swarm cannot safely be assigned to gameplay or presentation |
| Material-slot mapping | `content-resource-model-identity`, `material-texture-content-lookup`, `material-slot-mapping`, `render-state-cache` | Correct IDs can still bind the wrong textures or shader data |
| Mip and sampler policy | `texture-gpu-upload`, `mip-sampler-policy`, `render-state-cache` | Decoded mips do not establish runtime selection or filtering |
| Model-world LOD/background load | `mesh-model-world-interface`, `model-world-lod-semantics`, `renderware-model-world-internals` | SDK names do not establish thresholds, order, or failures |
| Teardown and GPU retirement | `shared-resource-handle-lifetime`, `cell-presentation-stage`, `teardown-gpu-retirement` | Logical release can precede GPU use if retirement is not explicit |
| Original runtime oracle | Multiple | No positive Cell, editor, vehicle, pose, teardown, or final-pixel trace closes static uncertainty |

The canonical file records 12 unresolved dependencies. Confidence in their existence is high where a source explicitly lacks a body or runtime trace; confidence in any guessed answer is low.

## 9. Functions that looked like RenderWare but actually carry gameplay semantics

### `Simulator::Cell::MovePlayerToMousePosition`

The function calls `Graphics::IRenderer::Get` and a camera-origin helper. Its semantic result is a gameplay ray-plane hit and mutation of target position, orientation, and moving state. Required abstraction: `ICameraRayProvider + IPlayerMovement`.

### `Simulator::Cell::GetModelKeyForCellResource`

This looks like model loading because it returns model identity. It actually selects a stable content key before a graphics object exists. Required abstraction: `IModelKeyResolver` and `IContentStore`.

### `Simulator::Cell::cCellGFX::Initialize`

The name, Graphics calls, and world handles resemble renderer initialization. The function establishes the mode-owned scene graph and presentation associations required by gameplay and mode lifecycle. Required abstraction: `ISceneStage`.

### `Simulator::Cell::cCellGFX::PreloadResources`

This traverses gameplay content and acquires presentation assets. Stable resource association, readiness, and ownership across preload-to-display are required semantics. Required abstraction: `IPresentationResourceCache + IContentStore`.

### `Simulator::Cell::cCellGFX::InstanceEffectOnCell`

This calls an effects world and visual-effect virtuals. The semantic operation is a typed effect request and entity-scoped visual instance; particle implementation remains presentation. Required abstraction: `IEffectPresenter`.

### `Simulator::Cell::PlayAnimation`

This crosses animation and model-world interfaces. It writes current clip and transition state on the Cell, so the operation is gameplay semantic even though pose output is not proven. Required abstraction: `IAnimationController`.

### `Transform::PreTransformBy`

This feeds renderer matrices but composes authoritative offset, rotation, scale, and order used by entities and editor controllers. Required abstraction: `AffineTransform`.

### `Simulator::cVehicle` locomotion fields

The struct co-locates model handles with position, orientation, velocity, and speed state. The locomotion fields are gameplay; only the model and possible pose representation are presentation. Required abstraction: `IVehicleState`.

### Cell mode pointer callbacks

These use renderer Layer and camera context, but they change input consumption, pick handles, hover, and selection. Required abstraction: `IInputRouter + ICellPickQuery`.

### `App::cGameModeManager::SetActiveModeAt`

The display activation is visible, but the semantic operation changes the active gameplay mode and orders old exit/new entry and teardown. Required abstraction: `IGameModeRegistry + IGameMode`.

### Editor creature controller and animation-event calls

These manipulate editor creatures, targets, angles, and event intent before any RW pose is evaluated. Required abstractions: `IEditorCreatureController` and `IAnimationEventSink`.

## Topic coverage

| Requested final-report topic | Section |
|---|---|
| Meaningful gameplay → RenderWare/D3D crossings | 1 |
| Boundaries OpenSpore genuinely needs | 2 |
| Presentation-only boundaries | 3 |
| Third-party infrastructure to ignore | 4 |
| Gameplay semantics hidden behind engine interfaces | 5 |
| Animation/pose findings | 6 |
| Minimal modern interfaces | 7 |
| Unresolved dependencies | 8 |
| Functions that looked like RenderWare but carry gameplay semantics | 9 |

## Evidence index

### Worker artifacts

- `knowledgegraph/research/render-boundary/01-renderware-objects.json`
- `knowledgegraph/research/render-boundary/02-material-textures.json`
- `knowledgegraph/research/render-boundary/03-camera-transforms.json`
- `knowledgegraph/research/render-boundary/04-animation-pose.json`
- `knowledgegraph/research/render-boundary/05-scene-entity.json`
- `knowledgegraph/research/render-boundary/06-d3d-platform.json`
- `knowledgegraph/research/render-boundary/07-resource-lifetime.json`
- `knowledgegraph/research/render-boundary/08-gameplay-renderer.json`
- `knowledgegraph/research/render-boundary/09-ui-presentation.json`

### Direct source references

- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__MovePlayerToMousePosition.c:30-61`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetModelKeyForCellResource.c:8-44`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__PlayAnimation.c:22-58`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__Initialize.c:34-235`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__PreloadResources.c:22-175`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__StartDisplay.c:16-88`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__InstanceEffectOnCell.c:24-101`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Transform__PreTransformBy.c:6-28`
- `.spore-analysis/ghidra-exports/decompiled_sdk/App__cGameModeManager__SetActiveModeAt.c:8-34`
- `.spore-analysis/ghidra-exports/structs_fields.tsv:1354-1367,1871-1909,3810-3865,5998,8288`
- `docs/RENDERWARE-RESEARCH.md:15-25,113-173,271-325`
- `docs/replacement-boundaries.md:93-121`
- `docs/analysis/dossiers/cell-movement.md:8-10,46-55,99-101,133-151`
- `docs/MATERIALS-DESIGN.md:10-42,72-117,131-145`
- `docs/analysis/campaigns/cell-stage-campaign.md:455-519`
