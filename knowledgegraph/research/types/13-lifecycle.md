# SporeApp global object lifecycle research

## Scope

This is a clean-room, reverse-engineering-only characterization of lifecycle boundaries in `SPORE/SporeBin/SporeApp.exe` (Spore 3.1.0.22, x86:LE:32:windows). It records allocation, initialization, registration, reuse, cleanup, and teardown evidence without reproducing proprietary EA code or assets.

This document deliberately separates:

- direct static lifecycle evidence;
- SDK structure/function/vtable associations;
- canonical call topology;
- OpenSpore clean-room projections; and
- unresolved ownership or runtime boundaries.

No runtime trace was obtained. SDK names, vtable membership, and graph edges are not ownership proof by themselves.

## Evidence baseline

| Item | Value |
|---|---|
| Binary | `SPORE/SporeBin/SporeApp.exe` |
| Binary SHA-256 | `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e` |
| Image base | `0x00400000` |
| Triage snapshot | `f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b` |
| Xref snapshot | `2540f2ca7cd361a72b559448fa5cf247eff3cee20d375b14ed0dd256c45229c8` |
| Xref edges | 223,704 |
| Xref edge SHA-256 | `89e74b8a03c4db38a1927f8c95c38db507bf99cb8a11de6b6eb6a9484d8c79cb` |
| SDK commit | `cbf9206b9a823f0911cd9be0217104a49d72380b` |
| SDK SHA-256 | `5d894677c1835082da0392e8b794f3c93a0251733898c3c5b81cf7945f458f09` |
| Runtime evidence | none |

### Evidence scale

The scale is `UNKNOWN`, `APPROXIMATION`, `INFERRED`, `SUPPORTED`, `OBSERVED`, `CONFIRMED`, `VERIFIED`.

- `SUPPORTED` means a static contract is supported by decompilation plus structure, field, or dossier evidence.
- `OBSERVED` means a literal or operation is present in a targeted body, while semantic identity may remain incomplete.
- `VERIFIED` is reserved for facts directly read from the binary or pinned canonical artifacts.
- No lifecycle claim is runtime-verified because no runtime evidence is recorded.

## Source register

| ID | Source | Use |
|---|---|---|
| s01 | `.spore-analysis/ghidra-exports/sdk_functions.tsv` | SDK function anchors and names |
| s02 | `.spore-analysis/ghidra-exports/structs.tsv` | SDK object sizes |
| s03 | `.spore-analysis/ghidra-exports/structs_fields.tsv` | Vtable slots, fields, intrusive pointers |
| s04 | `.spore-analysis/ghidra-exports/vtables.json` | Vtable family evidence |
| s05 | `knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json` | Shared accessors and globals |
| s06 | `knowledgegraph/triage/xrefs-2540f2ca.tsv` | Canonical xref topology |
| s07–s12 | `knowledgegraph/research/decomp-gap/sim-core-*.json`, `sim-space-00.json` | Targeted static gap reviews |
| s13 | `knowledgegraph/research/decomp-gap/ui-shell-00.json` | Editor/UI lifecycle observations |
| s14 | `knowledgegraph/research/decomp-gap/editor-core-00.json` | Editor and species-profile observations |
| s15 | `docs/analysis/dossiers/unknown-high/cell-object-pool-lifecycle.json` | Cell pool replacement sequence |
| s16 | `docs/analysis/dossiers/unknown-high/message-handler-registration.json` | Message registration |
| s17 | `docs/analysis/dossiers/unknown-high/star-system-regen.json` | Star regeneration |
| s18–s29 | `src/sim/*`, `src/apps/*` | Current OpenSpore projections |

## Lifecycle map

### Application and game modes

`App::cGameModeManager` is a 52-byte SDK object with intrusive mode entries, an active index, a camera manager, and a viewer. SDK exports associate:

- `007d8120` with `cGameModeManager::Initialize`;
- `007d8d40` with `SetActiveModeAt`;
- `007d90b0` with `RemoveGameMode`;
- `007d91e0` with `Dispose`;
- `007d9320` with `AddGameMode`.

The `IGameMode` vtable establishes `AddRef`, `Release`, virtual destructor, `Initialize`, `Dispose`, `OnEnter`, `OnExit`, and `Update` slots. The exact original mode constructor, duplicate handling, dispose body, and shutdown order remain unresolved.

`App::cCellModeStrategy` is the Cell mode boundary. The original is associated with:

- `00e81cf0` — `Initialize`;
- `00e552f0` — `OnEnter`;
- `00e80980` — update adapter;
- `00e7fc00` — `OnExit`;
- `00e81f30` — `Dispose`;
- `00dd3ca0` — `AddRef`.

The current source owns `CellGfx` and `CellUI` as value members. Its `initialize` calls `mUI.load()` and `mGfx.initialize()`, and its `dispose` clears the current projection. This is a host lifecycle shell, not an original global-singleton bootstrap.

### CellGame and pools

`Simulator::Cell::sCellGame` is the 20,964-byte global Cell state object. The current source records its address as `0x16b3c04`. It contains the main `cObjectPool<cCellObjectData>`, query-pool handles, current world references, and the avatar cell index.

The SDK `cObjectPool<T>` descriptor is 28 bytes:

- `mpData` at `+0x00`;
- `mNextAvailableIndex` at `+0x04`;
- `mObjectPoolIdentifier` at `+0x08`;
- `mNumObjects` at `+0x0c`;
- `mNumAllocatedObjects` at `+0x10`;
- `mObjectSize` at `+0x14`;
- trailing field at `+0x18`.

`cCellObjectData` is 920 bytes. Its first object word is used as the free-list link while free and as the object index while allocated. The main Cell pool has observed capacity 4096.

`FUN_00b72160` is a high-fan-in bulk initialization/reset body. `FUN_00b72260` is associated with pool creation in the available static review. SDK labels are anchored nearby, but the addresses are not identical: `Initialize` is commonly associated with `00b72190`, and `CreateObject` with `00b72270`. The address drift is preserved as unresolved.

`FUN_00e780a0` establishes the Cell GFX replacement sequence:

1. Clear `sCellGame+0x411c` when it matches the input object index.
2. Release the old GFX object.
3. Destroy the associated object.
4. Rebuild if stage scale changed.
5. Create a replacement pooled object.

The individual GFX release/rebuild callees are not fully characterized. The original pool destructor and null/exhaustion behavior are also unresolved.

### CellGFX and CellUI

`cCellGFX` owns preloaded models, textures, creatures, an object pool, lighting/beach/background/model/anim/effect world pointers, effect instances, and audio-track state. SDK and campaign evidence associate:

- `00e5dba0` with `cCellGFX::Initialize`;
- `00e666f0` with `PreloadResources`;
- `00e55120` with `StartDisplay`;
- `00e66840` with `InstanceEffectOnCell`.

The original builds skybox, background, beach, main-model, effects, and foreground worlds. The current source records integer world tokens and resource-key vectors instead of equivalent render resources.

`cCellUI` contains global UI layout state, a progress bar, a rollover pool, zoom state, and hover text. The SDK structure exposes a 28-byte rollover pool and 56-byte rollover records. `00e62340` is associated with `ShowHealthRollover`: a missing GFX index returns no rollover; otherwise a rollover is created with health-derived and disappearance fields. The current source returns a vector position, not the original pool index.

The original `cCellUI` update/expiry path and complete pool destruction are unresolved.

### Shared accessors and cached state

Accessor-like functions around `0x00b3d240..0x00b3d380` read a storage block beginning at `0x0167eac0`. Observed offsets include `+0x04`, `+0x20`, `+0x24`, and `+0x44`. The storage and accessor shape are established, but concrete singleton identities are not.

`Simulator::sSpacePlayerData` has an ID field at `+0x18` with `-1` as a sentinel and a cached empire pointer at `+0x1c`. The cache is revalidated through `FUN_00ba9370`. One dossier describes old-object destruction through vtable slot `+4`; shared-state evidence describes AddRef/Release-style management. The replacement semantics remain unresolved.

### Space inventory, trading, and communication

`cSpaceInventoryItem` is a refcounted, message-listening object with item metadata, cargo, `PropertyList`, localized strings, a resource key, and listener fields. `00c877f0` is constructor-like property initialization: it manages `PropertyList` ownership, writes localized fields, conditionally writes item position, and calls a receiver virtual slot.

The targeted cleanup path releases the ResourceObject and owned vectors through virtual operations. Exact message-listener registration/removal pairing is unresolved.

`cSpaceTrading` owns refcounted strategy state, spice vectors, NPC stores, intrusive object vectors, and rare-data maps. The targeted acquisition path obtains a trading/inventory result, appends the acquired object, and releases a temporary acquired reference. The previous resource is released before a new resource is stored. The exact top-level manager disposal is unresolved.

`FUN_00aeb160` allocates and initializes a `0xa0` communication event and appends it to `cCommManager+0x28`. Wrapper `FUN_00aeb720` passes the event to `FUN_00aebe90`. The SDK association to `CreateSpaceCommEvent` versus `HandleSpaceCommAction` is contested and must not be used as an unqualified identity.

### Stars and regeneration

`cStarRecord` contains observation time, version, timestamp, position/type/technology, empire identity, species profile, and intrusive planet vectors. `FUN_00bb4af0` observes a star with no planets, checks timing, updates `mLastObservedTime`, removes the star from pending state, resets manager state, and calls `GeneratePlanetsForStar`. This sequence is the strongest recovered regeneration lifecycle. The planet-generation body and complete record destruction are outside the recovered contract.

### Message and service registration

`cMessageManager` contains a mutex, listener hash map, and entry records with listener, priority, handler, object, and a reference-count flag. SDK exports expose `AddListener`, `AddUnmanagedListener`, `AddHandler`, `RemoveHandler`, `RemoveEntry`, `ProcessQueue`, and `Dispose`.

`FUN_00b21340` performs an ID-map lookup, registers through the mapped handler when found, or resolves a name and traverses a `0x0c`-stride fallback list. The callback contracts, duplicate behavior, and removal pairing are unresolved.

`FUN_005bfd40` is an `EditorNamePanel`-associated initialization body. It stores initialization inputs, release-before-assigns layout/entity-related members, creates a `0x18`-byte Editor object, and invokes app graphics/message service paths. The concrete Editor type, service collection owner, and whether four service calls are registrations or operations remain unresolved.

### Animation and presentation boundary

Static evidence supports `PlayAnimation` blend behavior, effect-map slot selection, and event/effect mapping. The current `CellAnim` source reproduces blend special cases, a three-slot effect-map selection, and deterministic value-level event/effect mapping.

The critical `SimEvent -> CellAnim -> stage/renderer/pose` relation remains **UNRESOLVED**. There is no provenance-bearing runtime or complete static trace establishing event order, pose ownership, renderer submission, or effect-instance release timing. Current `EffectInstance` values must not be treated as original renderer-owned objects.

### Editor models and species profiles

`FUN_004ad6f0` is SDK-associated with `Editors::EditorModel::Dispose`; the targeted body iterates model/part data, transforms bounding boxes, and applies transforms, but ownership and semantic identity are not established.

`FUN_004df550` performs a keyed lookup/validation path, falls back to fields at `+0xa4`, `+0xa8`, and `+0xac`, and may allocate a `0xa18`-byte object labeled `cSpeciesProfile`. Allocation is observed; cache, transfer, and destruction ownership are not.

## Lifecycle stages

| Stage | Original evidence | Current projection | Status |
|---|---|---|---|
| Construct | SDK types, pool buffers, event/profile allocation, property initialization | Typed values and vectors | Partial |
| Initialize | Mode, CellGame, CellGFX, CellUI, and service initialization paths | `CellModeStrategy`, `CellGame`, `CellGfx`, `CellUI` | Partial |
| Register | Message map/list, editor services, inventory listener fields | No general message manager counterpart | Partial |
| Enter/update | OnEnter/OnExit, update adapter, fixed-step simulation | `CellModeStrategy::onEnter/update`; `CellSim::update` | Host projection |
| Replace/reuse | Pool free list, GFX rebuild, intrusive release-before-replace | `cObjectPool`, `CellGfx`, `CellUI` vectors | Partial |
| Exit | Cell mode OnExit; exact service deregistration unresolved | Flag/display state reset | Partial |
| Dispose/destroy | Mode Dispose, inventory cleanup, pool/service disposal at mixed confidence | `CellModeStrategy::dispose`; vector clearing | Partial |

## Factories

| Product | Creator or wrapper | Consumer | Status |
|---|---|---|---|
| Cell pooled object | `cCellGame::CreateCellObject` at `00e74a20` | movement/query/GFX/combat | Supported |
| Communication event | `FUN_00aeb160`; wrapper `FUN_00aeb720` | `cCommManager` and `FUN_00aebe90` | Observed |
| Inventory item | caller allocation plus `00c877f0` property initialization | trading/inventory/tool paths | Observed |
| Species profile candidate | `FUN_004df550` | species manager callers | Observed, ownership unresolved |
| Editor object | `FUN_005bfd40` inside an already allocated panel context | editor/UI service paths | Observed, type unresolved |

## Pools and reuse

### Main Cell pool

- Descriptor: 28 bytes.
- Element: `cCellObjectData`, 920 bytes.
- Capacity: 4096 in the current source and campaign evidence.
- Free list: first element word links to the next free index; allocated elements store their own index.
- Allocation: `00e74a20` / SDK-associated pool creation.
- Reuse: `FUN_00e780a0` releases dependent GFX state and recreates a pooled object.
- Destruction: exact original pool buffer destruction unresolved.

### CellGFX pool

`cCellGFX::mCellGFXObjects` is a 28-byte pool descriptor. Its complete element layout and capacity are not required for the lifecycle contract, but the pool participates in GFX object replacement. The complete teardown and allocation behavior remain unresolved.

### CellUI rollover pool

The SDK descriptor is 28 bytes and `cCellUIRollover` is 56 bytes. `ShowHealthRollover` creates a rollover only when a GFX object exists. Original free-list reuse, expiry/removal, and destruction are unresolved; the current vector implementation is a behavior projection.

## Manager ownership

| Manager | Owned state | Creation/activation | Cleanup |
|---|---|---|---|
| `cGameModeManager` | Intrusive mode entries and active index | `AddGameMode`; `SetActiveModeAt` | `RemoveGameMode`; `Dispose` |
| `cMessageManager` | Listener map and entries | AddListener/AddHandler APIs | RemoveHandler/RemoveEntry/Dispose |
| `cSpaceTrading` | NPC/object/resource collections | Acquisition/resource paths | Temporary release and resource replacement; top-level Dispose unresolved |
| `cCommManager` | Intrusive event list at `+0x28` | `FUN_00aeb160`/wrapper | Event completion/removal unresolved |

## Registration and deregistration

- `FUN_00b21340`: ID lookup, handler registration, or fallback `0x0c`-stride traversal.
- `FUN_005bfd40`: EditorNamePanel service registration path; exact operation and removal are unresolved.
- `cSpaceInventoryItem`: SDK layout exposes message manager/listener and message-ID array fields; exact registration and removal pairing is unresolved.
- SDK `cMessageManager` exports provide the named removal operations, but matching behavior is not fully recovered.

## Cleanup and exception paths

| Path | Behavior | Status |
|---|---|---|
| Pool exhaustion | Current source returns `nullptr`; original failure return is unresolved | Partial |
| Missing GFX rollover | No rollover; return `-1` in the current projection | Supported |
| Equal pointer replacement | No replacement in the observed `FUN_00c70110` path | Supported |
| Null resource/property | Guarded release/replace path; exact status is unresolved | Partial |
| Species profile fallback | Fallback fields used; allocation ownership unresolved | Observed |
| Pointer slot calls | `FUN_00c70110` calls old pointee slots `+0xbc` and `+0xc0`; meanings unknown | Supported mechanics, low identity |
| Cell GFX rebuild | Clear avatar reference, release dependent state, conditional rebuild, create replacement | Supported |

## OpenSpore comparison

### Pool

Original evidence describes a 28-byte pool descriptor, bulk initialization, free-list reuse, and CellGame ownership. `src/sim/CellPool.hpp` preallocates typed objects, builds a free list, and returns typed pointers through `allocate`/`deallocate`. This is a partial clean-room projection, not proof of original failure behavior or pool destruction.

### Mode lifecycle

Original evidence uses SDK-backed mode slots, global Cell services, and an AddRef/Release interface. `CellModeStrategy.cpp` owns CellGFX and CellUI value members, loads/initializes them, clears them on dispose, and switches with OnExit/OnEnter. It does not reproduce global attach/detach, manager refcounting, or the original per-frame orchestrator.

### GFX

Original `cCellGFX` owns render/world and resource pointers. `CellGfx.cpp` records integer world tokens, resource-key vectors, and `displayActive`; it does not create equivalent render resources.

### UI

Original `cCellUI` owns a rollover pool and layout state. `CellUI.cpp` stores constants and vector values; vector position is not the original pool index.

### Simulation

`Sim.cpp` is a fixed-step deterministic behavior contract with camera-plane steering, eat/flee events, and vector state. It is not the original simulator object graph or service runtime.

## Contradictions and unresolved identities

1. **Pool address drift:** recovered bodies `00b72160` and `00b72260` are near, but not equal to, SDK-associated labels `00b72190` and `00b72270`.
2. **Cached empire pointer:** one source describes destruction through vtable `+4`; another describes AddRef/Release. The old cached-object operation is unresolved.
3. **CreateCellObject:** `00b184c0` is observed to allocate a new `0x28` object, while `00b22190` is reported as a pool-returning path. `00b1fda0` only returns its argument.
4. **CellDataReference:** `00e82340` and SDK-associated `00e82420` are kept separate pending identity adjudication.
5. **Communication thunk:** `00aeb720` has a creation-wrapper body but conflicting SDK/triage identity.
6. **EditorNamePanel:** the SDK label at `005bfe40` is contained in the body beginning at `005bfd40`, not an exact entry.
7. **cSPUITextZoom:** the targeted body has a wider ABI and accesses fields beyond the named SDK padding.

## Unresolved questions

- What is the exact original pool destructor and failure contract?
- What is the original global shutdown order for mode, CellGame, CellGFX, CellUI, message, resource, and editor services?
- Which exact listener registration corresponds to each removal path?
- Who owns a `cSpeciesProfile` returned or cached by `FUN_004df550`?
- Is `FUN_004ad6f0` actually `EditorModel::Dispose`?
- What is the complete `SimEvent -> CellAnim -> stage/renderer/pose` ownership and submission order?
- What resource/acquisition/release chain closes the Track-F ownership boundary?
- What are the full `cCellObjectData` field semantics from `+0x100` through `+0x358`?

## Validation

The machine-readable artifact is `knowledgegraph/research/types/13-lifecycle.json`.

Validation required for the final worktree:

- parse the JSON as one object;
- verify stable, timestamp-free key and array ordering;
- verify every relation has `evidence`, `provenance`, `confidence`, and `evidence_level`;
- confirm only the two requested files are changed;
- run the repository's available lint, typecheck, and test commands;
- do not modify source, binary, Ghidra, or knowledge-graph state.
