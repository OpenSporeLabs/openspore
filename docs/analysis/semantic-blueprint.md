# OpenSpore Semantic Blueprint

## Freeze status

This is a static, evidence-backed semantic specification for SporeApp.exe 3.1.0.22. It does not claim original runtime compatibility, modify the executable, or promote static evidence to runtime truth.

## Executive counts

- 14 semantic subsystems frozen.
- 23 reconstruction packages frozen.
- 58,757 canonical functions accounted for; 2,149 gameplay functions have records.
- 411 bounded non-verified semantic consolidations; 173 partial static semantic characterizations; 1,976 gameplay functions semantically not established.
- 0 original functions runtime-validated; 1,671 functions require targeted decompilation; 124 require runtime evidence.
- 8 packages are implementable with explicitly bounded local unknowns; 0 are fully implementation-ready for original behavior.
- 3 architecture-changing blocker clusters remain open.

## Evidence policy

- VERIFIED/OBSERVED is reserved for direct binary, static control-flow, concrete structure/vtable, repository verification, or recorded runtime evidence.
- SUPPORTED means multiple bounded sources converge without proving runtime behavior.
- INFERRED is a strong interpretation that remains provisional.
- UNKNOWN is insufficient evidence; absence is not negative semantic proof.
- Static, SDK, vtable, current-source, fixture, and decompiler evidence never silently becomes original runtime behavior.

## Corpus and scope

- Binary: SporeApp.exe 3.1.0.22, x86:LE:32, image base 0x00400000.
- Canonical snapshot: f0e310e0.
- Canonical executable denominator: 58,757; historical manager denominator: 59,245; the 488-row delta is external-only and not a missing executable function set.
- Canonical xrefs: 223,704 unique rows. The atlas/TSV ordering discrepancy is ordering-only; set equality and type totals control.
- The final package list has 23 records, including evidence and runtime-boundary packages that are explicitly not gameplay implementations.

## Semantic subsystems

### SS-00-EVIDENCE — Evidence, provenance, and validation

Evidence: SUPPORTED

Boundary: Evidence and validation tooling owns provenance, tests, fixtures, and negative outcomes; it owns no game state.

Axes: identity, provenance, negative result, validation gate

### SS-01-APP-LIFECYCLE — Application lifecycle and mode registry

Evidence: SUPPORTED

Boundary: App owns bootstrap, service publication, frame/update, stop, and shutdown; downstream gameplay remains separate.

Axes: initialized, running, update, stop requested, shutdown

### SS-02-SHARED-STATE — Shared-state root substrate

Evidence: SUPPORTED

Boundary: Service slots and receiver-typed accessors are independent ports; no unified singleton is asserted.

Axes: noun registry, star manager, input manager, opaque state, space data, receiver identity

### SS-03-RESOURCE-CONTENT — Resource manager, formats, and content graph

Evidence: SUPPORTED

Boundary: Resource manager and typed records own content identity and bounded payloads; runtime/presentation handles are downstream.

Axes: TGI, DBPF, QFS, typed Cell record, lazy reference

### SS-04-CELL-RUNTIME — Cell gameplay runtime

Evidence: SUPPORTED

Boundary: Cell state owns live entity and selected rule projections; content, GFX/UI, and save candidates remain separate.

Axes: pool identity, query, movement, health/death, advect, interaction

### SS-05-CELL-PRESENTATION — Cell mode and presentation

Evidence: SUPPORTED

Boundary: Cell mode/presentation stage owns display, preload, GFX/UI, effects, scene membership, and draw, not gameplay state.

Axes: preload, display, HUD, scene/layer, handle, draw

### SS-06-SIMULATOR-CORE — Simulator core, tools, missions, and timing

Evidence: INFERRED

Boundary: Simulator core owns managers, tools, missions, timing, and communication; it must split from Cell and persistence.

Axes: manager, tool, mission, strategy, time, communication

### SS-07-SPACE-EMPIRE — Space, Empire, stars, planets, and terrain handoff

Evidence: INFERRED

Boundary: Space/Empire own navigation, stars/planets, political identity, trade, terraforming, and surface handoff; they are not Cell state.

Axes: SpaceContext, active planet/star, empire cache, star record, planet record, trade, terraforming

### SS-08-CREATURE-TRIBE-CIV — Creature, tribe, city, relationship, and civilization

Evidence: UNKNOWN

Boundary: Creature, tribe, city, relationship, and civilization state require independent ownership and stage evidence.

Axes: creature progression, tribe/city planning, relationship, mission/economy

### SS-09-TERRAIN-WORLD — Planet surface and terrain rendering

Evidence: UNKNOWN

Boundary: Terrain/world rendering owns surface/quad/weather/draw state; generated planet data and gameplay remain upstream.

Axes: planet surface, terrain sphere, quad, weather, draw

### SS-10-EDITOR-UI-EVENTS — Editor, UI, messages, and scripting

Evidence: SUPPORTED

Boundary: Editor, UTFWin, scripting, and App messages own distinct dispatch surfaces; no universal event ABI is asserted.

Axes: editor lifecycle, editor submode, input, immediate message, deferred message, UI callback

### SS-11-AUDIO-INPUT — Original audio and input marshalling

Evidence: UNKNOWN

Boundary: Original input/audio are separate from host SDL, CellInput, timing, and DSOUND behavior.

Axes: device event, normalized input, mode route, audio request, backend failure

### SS-12-UNKNOWN-ROUTING — Unknown routing and ownership backlog

Evidence: UNKNOWN

Boundary: Unknown rows remain characterization-only until identity, ownership, and reachability are adjudicated.

Axes: unknown function, vtable candidate, owner debt, reachability

### SS-13-RUNTIME-BOUNDARY — Runtime, CRT, STL, and third-party boundary

Evidence: SUPPORTED

Boundary: CRT, STL, platform, third-party, and imports are attribution boundaries and receive only narrow host adapters.

Axes: allocation, strings, clock, platform, wrapper

## Package freeze

### PKG-00-EVIDENCE-VALIDATION — Evidence acquisition, provenance, and validation infrastructure

Readiness: `INFRASTRUCTURE_REPLACEMENT`; evidence: `SUPPORTED`; current gate: `SUPPORTED`.

Semantics: Preserve identity, provenance, negative outcomes, and test results separately from game semantics.

Owner: Evidence, observatory, KG, dossier, and validation tooling.

Authoritative/runtime/persistent state: ["Authoritative: evidence records, manifests, fixtures, outcomes, queue state", "Runtime: no game state; bounded observation only", "Persistent: read-only artifacts and test records", "Invariant: no uncorrelated trace changes semantic status"]

Structures and fields: ["EvidenceRecord: binary/VA, tier, environment, outcome, negative reason", "TraceManifest: binary/probe hashes, image base, Wine/display/input, raw JSONL, events_total"]

Functions and contracts: ["observe.py launch/trace/analyze: approved bounded observation", "fixture_check/test_run: fixture identity and tests", "kg_record/queue_op: evidence/queue state without promotion"]

State machines and events: ["artifact -> provenance record -> package claim only after adjudication", "zero-event/failed-boot -> negative result"]; ["function_entry", "decompile_provenance", "test_outcome", "zero_event"]

Data/assets and serialization: ["Fixtures, probe manifests, raw JSONL, dossiers", "No game assets"]; ["Deterministic evidence JSON/JSONL", "Identity/provenance/outcome round-trip required"]

Engine interfaces: ["Read-only Ghidra/SDK", "Observatory approval/trace", "KG sidecar"]

Invariants: ["Generic frames and empty traces are negative/incomplete", "Screenshots do not substitute for events", "No implicit repository/KG write"]

Failure semantics: ["Zero events remains zero events", "Failed boot and clean exit are distinct", "Missing provenance is not success"]

Initialization/update/cleanup: ["Init: pin artifact/environment", "Tick: capture bounded events/outcome", "Shutdown: preserve artifacts and negative result"]

Validation: ["provenance_negative", "deterministic_unit", "integration", "tests/test_dossier.py", "tests/test_kg_schema.py", "tests/test_kg_seed.py", "tests/mcp/"]

Known divergences: ["Infrastructure is not a game replacement", "Tracer plumbing is not original evidence"]

Unknowns: ["No positive original Cell trace", "Future artifacts require C-PROV"]

Implementation status: ["Original: infrastructure exists", "OpenSpore: tests/tools exist", "Replacement: not a game interface", "Promotion: not applicable"]

### PKG-01-SHARED-STATE-ROOTS — Simulator shared-state roots and interface freeze

Readiness: `BLOCKED_BY_ARCHITECTURE`; evidence: `INFERRED`; current gate: `INFERRED; P0-characterize roots and map contract`.

Semantics: Characterize high-fan-in service roots and freeze typed service contracts before dependent reconstruction.

Owner: Simulator service composition and shared-state access.

Authoritative/runtime/persistent state: ["Authoritative: characterized accessor/service contract", "Runtime: packed globals, service pointers, map lookups", "Persistent: none", "Invariant: fan-in and FUN names do not establish types"]

Structures and fields: ["Simulator service block: 0x0167eaf0/af8/eb0c/eb14/eb2c/eb50 and unresolved slots", "Unnamed layout: owner/global/lifetime/mutation/invalid handle", "map_int_whatever_find: owner/key/value/mutation"]

Functions and contracts: ["0x00b3d350 cGameInputManager::Get returns DAT_0167eaf8", "0x00b3d4d0 cSpaceTrading::Get returns service", "0x00b3d3c0 cRelationshipManager::Get returns service", "0x00b3d420 cGameModeManager::Get returns service", "0x00e5c780 map lookup requires RE"]

State machines and events: ["root_unresolved -> named_getter -> typed_service_handle"]; ["singleton_get", "service_handle_use"]

Data/assets and serialization: ["Global service slots", "No persistent assets"]; ["None established"]

Engine interfaces: ["Typed service locator", "Player identity", "Object registry", "World state", "ID map", "Event router"]

Invariants: ["Accessor bodies are not service implementations", "Raw globals are not modern API", "Lifetime/init are explicit"]

Failure semantics: ["Invalid/uninitialized handle unresolved", "Missing key vs null unresolved"]

Initialization/update/cleanup: ["Init: characterize/publish handles", "Tick: consumers request handles", "Shutdown: release after consumers stop"]

Validation: ["decomp_differential", "not_yet_testable", "triage readiness", "xref TSV", "21-decompilation-coverage.json"]

Known divergences: ["OpenSpore injected services are not original singleton block", "No implementation from fan-in"]

Unknowns: ["Ten root identities", "Map type", "Initialization writers", "Side effects/lifetime"]

Implementation status: ["Original: not implemented", "OpenSpore: partial local services", "Replacement: NOT_DEFINED", "Promotion: blocked"]

### PKG-02-APP-LIFECYCLE — Application bootstrap and system lifecycle

Readiness: `BLOCKED_BY_RUNTIME`; evidence: `SUPPORTED`; current gate: `SUPPORTED; blocked on M0 positive boot and C-PROV/C-BOOT`.

Semantics: Describe original bootstrap, AppSystem initialization, update, and shutdown without claiming complete reconstruction.

Owner: App bootstrap, AppSystem services, frame/update, and shutdown.

Authoritative/runtime/persistent state: ["Authoritative: cSporeApp flags, service publication, listener registration", "Runtime: AppSystem/mode/message/renderer/resource services", "Persistent: configuration candidates unresolved", "Invariant: boot control is not stage transition"]

Structures and fields: ["cSporeApp: mHasInitialized +0x0c, mIsRunning +0x0d, timing +0x10/+0x14", "cAppSystem: InitPlugins, Init, Startup, Update +0x78, func7Ch +0x7c, PostUpdate +0x80, PreShutdown", "IAppSystem: service/update/shutdown interfaces"]

Functions and contracts: ["0x0067dcc0 IAppSystem::Get returns DAT_015fd890", "0x007e93d0 InitPlugins walks command/plugin setup", "0x007e67a0 Startup starts subsystems", "0x00f47b10 handles app update 0x01ee100a and stop 0x0153c326", "0x00f47930 measures/paces and calls update/func7Ch/PostUpdate"]

State machines and events: ["uninitialized -> initialized -> running -> stop_requested -> shutdown", "message_received -> delta_measured -> optional pacing -> updated -> post_updated"]; ["bootstrap_entry", "init_plugins", "init", "startup", "app_update 0x01ee100a", "stop 0x0153c326", "shutdown"]

Data/assets and serialization: ["PE/app configuration", "Service publication", "No game asset semantics"]; ["Configuration/property boundary separate", "No autosave or whole-save claim"]

Engine interfaces: ["IAppHost", "IGameModeRegistry", "IMessageManager", "IResourceProvider", "IGameServices", "IPlatformHost"]

Invariants: ["mHasInitialized gates updates", "mIsRunning gates running", "Frame heartbeat is not fixed-step proof", "Historical startup cannot promote Cell"]

Failure semantics: ["Boot stall, clean exit, and stop distinct", "Failed init not running", "Pacing failure not fixed-step failure"]

Initialization/update/cleanup: ["Init: entry -> InitPlugins -> Init -> Startup", "Tick: app update -> frame -> callbacks -> PostUpdate", "Shutdown: stop -> PreShutdown -> teardown"]

Validation: ["original_binary_oracle", "provenance_negative", "not_yet_testable", "main_menu probe", "historical JSONL", "tests/test_cell_trace.py"]

Known divergences: ["Cell executable is not AppSystem bootstrap", "SDL host is not original input", "Fixed simulation is not observed original pacing"]

Unknowns: ["Boot exit trigger", "Complete bootstrap order", "Menu-to-stage", "Global shutdown"]

Implementation status: ["Original: partial static/historical", "OpenSpore: host shell only", "Replacement: NOT_DEFINED", "Promotion: not authorized"]

### PKG-03-RESOURCE-IO — Resource manager, DBPF/QFS I/O, and property substrate

Readiness: `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`; evidence: `SUPPORTED`; current gate: `SUPPORTED; blocked on property round-trip, menu trace, multi-package semantics`.

Semantics: Provide bounded clean-room content bytes and original resource/property boundary.

Owner: Resource manager, packed files, stream/record I/O, property substrate.

Authoritative/runtime/persistent state: ["Authoritative: ResourceKey, DBPF metadata/bytes, typed payloads, bounded property entries", "Runtime: registries/databases/factories/cache/handles", "Persistent: packages and property/config streams", "Invariant: handles/caches are not gameplay entities"]

Structures and fields: ["ResourceKey: type/group/instance", "DatabasePackedFile: index/extents/holes/allocator", "PFIndexModifiable: index read/write", "RecordInfo: offset/sizes/flags/saved state", "PropertyList: local entries/parent/counter/Read/Write"]

Functions and contracts: ["0x008de530 cResourceManager::Initialize", "parseDbpfIndex/extractDbpfRecord/qfsDecompress", "PropertyList::Read/Write local typed entries with first-failure behavior"]

State machines and events: ["uninitialized -> configured -> cache_miss -> cache_hit/unavailable -> disposed"]; ["package_lock", "index_read", "record_fetch", "property_load", "resource_cache_hit/miss"]

Data/assets and serialization: ["DBPF v3/QFS records", "ResourceKeys", "Property streams", "Read-only GOG package bytes"]; ["DBPF/QFS verified bounded", "Property/class serializer framing unresolved"]

Engine interfaces: ["B1 IResourceProvider", "IContentStore", "IRecordCodec", "IStream", "IPropertyStore", "IConfigCodec"]

Invariants: ["Complete key required", "Extents bounded", "QFS/malformed explicit", "Local-first property lookup with bounded parent fallback"]

Failure semantics: ["Missing record/malformed index/bad extent/unsupported compression/property failure distinct", "Cache bypass/async unresolved"]

Initialization/update/cleanup: ["Init: mount/index registries", "Tick: fetch/decode/cache", "Shutdown: close/release"]

Validation: ["deterministic_unit", "fixture_comparison", "asset_driven", "integration", "original_binary_oracle", "mini_package.dbpf", "tests/test_formats.py", "real_asset_test.cpp"]

Known divergences: ["B1 one-package provider is not original multi-package manager", "Typed readers are not general property persistence"]

Unknowns: ["Priority", "Directory semantics", "Cache eviction", "Async scheduling", "QFS call site", "Property wire format"]

Implementation status: ["Original: static anchors", "OpenSpore: DBPF/QFS seam exists", "Replacement: EXISTING_REPLACEMENT_SEAM", "Promotion: partial"]

### PKG-04-ASSET-GEOMETRY-TEXTURE — GMDL/RW4/raster geometry and texture decode

Readiness: `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`; evidence: `SUPPORTED`; current gate: `SUPPORTED; blocked on differential and pixel oracle beyond seam`.

Semantics: Decode bounded static geometry/model/texture/container formats into host values.

Owner: Asset/format decoding and host mesh/texture production.

Authoritative/runtime/persistent state: ["Authoritative: supported decoded fields/topology/mips", "Runtime: host mesh/texture handles", "Persistent: source records only", "Invariant: host output is not original RW/material/pixel behavior"]

Structures and fields: ["GmdlModel: version/bounds/topology/material refs", "Mesh: vertices/indices/bounds/limitations", "RW4 manifest: sections/offsets/validation", "ImageRGBA: mip dimensions/RGBA8/provenance"]

Functions and contracts: ["parseGmdl/meshFromGmdl", "decodeRasterMips/decodeDxt5Mip", "parseRw4 structural walk without payload execution"]

State machines and events: ["record_selected -> validated -> decoded -> host_handle or unsupported/error"]; ["record_extracted", "gmdl_decoded", "mesh_built", "texture_decoded", "rw4_section_observed"]

Data/assets and serialization: ["GMDL v8", "RW4 envelope", "raster/DXT5", "Host Mesh/ImageRGBA"]; ["Read-only static parse", "No writer/load round-trip"]

Engine interfaces: ["B2 IMeshSource", "IRenderer input", "IMaterialRegistry", "ITextureStore"]

Invariants: ["Bounds/index checks", "Unsupported versions/sections explicit", "Opaque trailers not complete RW", "RW internals stay behind seam"]

Failure semantics: ["Truncation/bounds/version/compression/source failures distinct", "Opaque payload is not execution success"]

Initialization/update/cleanup: ["Init: mount/decoder tables", "Tick: decode/publish immutable values", "Shutdown: release without source mutation"]

Validation: ["deterministic_unit", "fixture_comparison", "asset_driven", "integration", "decomp_differential", "mini.gmdl", "mini_rw4.rw4", "test_formats.py", "test_textures.py", "test_rw4.py"]

Known divergences: ["Host mesh/texture is not full RenderWare", "GMDL v8 narrower than format family", "Vulkan pixels not original"]

Unknowns: ["GMDL v9", "RW4 material/animation", "Raster words 0x10/0x18", "Mip/sampler", "Pixel fidelity"]

Implementation status: ["Original: bounded static decode", "OpenSpore: B2/host decode exists", "Replacement: EXISTING_REPLACEMENT_SEAM", "Promotion: bounded only"]

### PKG-05-CELL-CONTENT — Cell content and resource record semantics

Readiness: `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`; evidence: `SUPPORTED`; current gate: `SUPPORTED; blocked on runtime use and cross-language parity`.

Semantics: Decode direct Cell content records/references while separating static content from live gameplay and save state.

Owner: Cell static content/resource records and typed references.

Authoritative/runtime/persistent state: ["Authoritative: direct Cell layouts and hard references", "Runtime: lazy cCellDataReference handles", "Persistent: direct records only", "Invariant: direct record is not live Cell/GFX/save record"]

Structures and fields: ["cCellCellResource TypeID 0xDFAD9F51, 796 bytes", "cCellGlobalsResource TypeID 0x2A3CE5B7, 276 bytes/69 fields", "cCellWorldResource TypeID 0x9B8E862F, 16+12N+24N", "cCellPopulateResource TypeID 0xDA141C1B, 16+76N", "cCellStructureResource TypeID 0x4B9EF6DC, 28+40N", "cCellLootTableResource TypeID 0xD92AF091, 36+28N", "cCellEffectMapResource TypeID 0x433FB70C, 8+28N"]

Functions and contracts: ["parseCellCellResource", "parseCellWorldResource", "parseCellPopulateResource", "parseCellStructureResource", "parseCellLootTableResource", "parseCellEffectMapResource", "0x00e82340 candidate is not merged with 0x00e82420 Create"]

State machines and events: ["identity -> bounded bytes -> decode -> reference check -> publish", "unresolved reference -> loaded -> use-counted -> released"]; ["resource_decoded", "record_reference_checked", "resource_consumed_by_runtime"]

Data/assets and serialization: ["Twelve direct Cell TypeID records", "ResourceKeys", "World/populate/advect templates", "Cell package records"]; ["Direct typed records", "No generic CellSerializer envelope", "Decode-only"]

Engine interfaces: ["IContentStore", "IRecordCodec", "IReferenceResolver", "IPresentationResourceCache"]

Invariants: ["TypeID/extent checked", "Hard references validated", "Markers are not live coordinates", "Direct records separate from serializable state"]

Failure semantics: ["Unknown TypeID/truncation/count/extent/reference explicit", "Soft references not promoted to placement"]

Initialization/update/cleanup: ["Init: manifest/decode", "Tick: lazy reference resolution", "Shutdown: release cache/handles"]

Validation: ["deterministic_unit", "fixture_comparison", "asset_driven", "integration", "decomp_differential", "cell_* tests", "tools/spore/cellres/"]

Known divergences: ["Decoders do not execute world/AI/loot", "cCellSerializableData not a direct record", "GFX associations separate"]

Unknowns: ["Runtime use", "World placement", "Loot settlement", "Soft-ID selection", "0x00e82340/0x00e82420 alias"]

Implementation status: ["Original: bounded static records", "OpenSpore: typed decoders exist", "Replacement: PARTIAL_EXISTING_CONTRACT", "Promotion: decode-only"]

### PKG-06-CELL-STATE — Cell game state, pool, query, advect, and combat rules

Readiness: `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`; evidence: `SUPPORTED`; current gate: `SUPPORTED; blocked on M1, roots, C-STATE/C-SIDE`.

Semantics: Reconstruct selected pure Cell state/pool/query/advect/combat rules without claiming the complete live machine.

Owner: Simulator Cell runtime state and selected gameplay rules.

Authoritative/runtime/persistent state: ["Authoritative: static cCellGame/pool/object/query/combat transitions", "Runtime: cCellGame, pool, object, query, avatar, health, behavior", "Persistent: cCellSerializableData separate candidate", "Invariant: pure rules/CellSim are not original singleton runtime"]

Structures and fields: ["cCellGame: pool +0x1c, queries +0x40fc/+0x4100, world +0x4114/+0x4118, avatar +0x411c, serializable +0x5190, lock +0x5158, update +0x515c, state +0x51e0", "cCellObjectData: 920 bytes, pool link, target/orientation/transform, model/resource, animation, health/GFX/scale/query", "cObjectPool: 4096 capacity, 920 stride", "cCellQueryEntry: position/size/next/index", "cAdvectEntry/ScaleDifference: bucket/strength/variance/period/ID"]

Functions and contracts: ["0x00e80ba0 cCellGame::Initialize", "0x00e74a20 CreateCellObject", "0x00e780a0 pool lifecycle/rebuild", "CellPool allocate/release", "CellQuery::queryNear", "getCurrentAdvectInfo/getNextAdvectID", "getScaleDifference/getDamage/shouldNotAttack"]

State machines and events: ["free -> allocated_live -> dying/despawning -> rebuild -> free", "attack gate -> health positive/zero/death/flee/chase", "world -> scale bucket -> current/next advect"]; ["cell_game_initialized", "pool_allocated", "cell_created", "near_query", "attack_gate_decided", "cell_damage_resolved"]

Data/assets and serialization: ["PKG-05 Cell records", "Pooled cCellObjectData", "Query entries", "World/advect", "Health/behavior"]; ["cCellSerializableData/serializer separate", "No live-object save claim"]

Engine interfaces: ["ICellGameState", "IEntityPool", "ICellQuery", "IAdvectState", "ICombatRules", "IAnimationIntent"]

Invariants: ["Pool index distinct from pointer", "Capacity 4096", "Query links stable indices", "Health clamps zero"]

Failure semantics: ["Pool exhaustion invariant candidate", "Missing avatar/query invalid", "Invalid scale/advect explicit", "Omitted side effects not modeled"]

Initialization/update/cleanup: ["Init: reset/pools/queries", "Tick: create/query/move/damage/advect", "Shutdown: release/reset stage"]

Validation: ["deterministic_unit", "fixture_comparison", "decomp_differential", "original_binary_oracle", "sim tests", "generated fixtures labeled non-original"]

Known divergences: ["CellSim not original cCellGame", "Entity not byte-compatible", "No original timing claim"]

Unknowns: ["Complete pool effects", "Free-list sentinel", "AI/effect/query integration", "Runtime gates", "Live-object save"]

Implementation status: ["Original: selected static/pure mechanics", "OpenSpore: deterministic components/tests", "Replacement: PARTIAL_EXISTING_CONTRACT", "Promotion: not runtime promoted"]

### PKG-07-CELL-MOVEMENT — Cell movement and mouse-steering replacement

Readiness: `BLOCKED_BY_RUNTIME`; evidence: `SUPPORTED`; current gate: `SUPPORTED; blocked on M0/M1/M2/C-REPLACEMENT`.

Semantics: Reconstruct camera-ray/plane to Cell target/orientation/moving state with a bounded hook seam.

Owner: Cell movement rule and read-only camera/input boundary.

Authoritative/runtime/persistent state: ["Authoritative: target, orientation, moving flag after guards", "Runtime: avatar/lock gates, object target/current transform, camera ray", "Persistent: none", "Invariant: renderer does not own result"]

Structures and fields: ["sCellGame: avatar +0x411c, lock +0x5158, moving +0x5190+0xe0", "cCellObjectData: target +0x08, orientation +0x14", "MovementPlane: normal (0,0,1), load point (0,0,0), runtime point unresolved", "CameraState/Ray: origin/direction/pointer/gates"]

Functions and contracts: ["0x00e5b790 MovePlayerToMousePosition: lock/player/camera guards, ray-plane, target/orientation/moving writes", "0x00e5b2e0 per-frame UI/plane target update", "0x007c4900 camera/light source candidate", "0x00b721d0 player lookup candidate", "reference and replacement functions: evidence/regression only"]

State machines and events: ["input -> gates -> player -> ray-plane -> target mutation/no-op"]; ["mouse_move", "key_down", "movement_target_written", "moving_flag_set", "orientation_written"]

Data/assets and serialization: ["Camera/pointer state", "Movement plane", "Player identity", "No persistent movement data"]; ["None"]

Engine interfaces: ["ICameraRayProvider", "ICameraService", "IPlayerMovement", "IInputRouter", "IEntityPool"]

Invariants: ["Guard failure no-op", "Distance/denominator checked", "Pool index resolves player", "Stack balanced", "Decomp 64/64 not runtime proof"]

Failure semantics: ["Lock/camera/UI/invalid player/parallel plane/negative distance no-op", "Omitted callees separate", "Missing real install fails validation"]

Initialization/update/cleanup: ["Init: pin target/plane/camera/resolver", "Tick: consume input/camera and mutate target", "Shutdown: restore hook/release frame state"]

Validation: ["decomp_differential", "replacement_hook", "deterministic_unit", "original_binary_oracle", "diff_test.cpp", "cell_movement probe", "synthetic hook"]

Known divergences: ["64/64 is decomp-only", "Hook not installed", "Host camera/input approximate"]

Unknowns: ["Live behavior", "Runtime plane", "Pool pointer identity", "Gate meanings", "Omitted effects"]

Implementation status: ["Original: static body/target bytes", "OpenSpore: replacement seam/regression", "Replacement: CONTRACT_DEFINED_REAL_INSTALL_UNVALIDATED", "Promotion: replaced-approx only"]

### PKG-08-CELL-MODE — Cell mode lifecycle and input routing

Readiness: `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`; evidence: `SUPPORTED`; current gate: `SUPPORTED; blocked on M1/C-ORDER/C-EVENT`.

Semantics: Define original cCellModeStrategy lifecycle and clean-room IGameMode boundary without GFX/UI/movement ownership.

Owner: App mode registry, Cell mode lifecycle, and mode input routing.

Authoritative/runtime/persistent state: ["Authoritative: active index, lifecycle flags, input callbacks, mode handles", "Runtime: App cGameModeManager, cCellModeStrategy, input callbacks, Cell services", "Persistent: none; exit does not imply save", "Invariant: IGameMode is host seam"]

Structures and fields: ["cGameModeManager: ModeEntry +0x14, active +0x28, init +0x10", "cCellModeStrategy: 27-slot candidate, lifecycle, input, update", "IGameMode: lifecycle/input/update host interface"]

Functions and contracts: ["0x007d8d40 SetActiveModeAt boundary", "0x00e81cf0 Initialize", "0x00e552f0 OnEnter", "0x00e80980 Update", "0x00e7fc00 OnExit", "0x00e81f30 Dispose", "0x00e51010 OnMouseMove"]

State machines and events: ["uninitialized -> initialized -> active -> exited -> disposed", "old mode OnExit -> active index/message -> new OnEnter/message"]; ["mode_initialize", "mode_enter", "input_event", "mode_update", "mode_exit", "mode_dispose"]

Data/assets and serialization: ["Mode IDs/names/entries", "No persistent mode data"]; ["None established", "No mode persistence claim"]

Engine interfaces: ["IGameMode", "IGameModeRegistry", "IInputRouter", "IMessageManager", "IAppHost"]

Invariants: ["Distinct valid index exits old before entering new", "Same index no-op", "Invalid index rejected", "Dispose after exit", "Input mode-owned"]

Failure semantics: ["Invalid request rejected", "Partial init not display-ready", "Entry/dispose failures incomplete", "Input consume/default unresolved"]

Initialization/update/cleanup: ["Init: register/initialize", "Tick: input/update", "Shutdown: exit/stop/dispose"]

Validation: ["deterministic_unit", "decomp_differential", "integration", "original_binary_oracle", "cellmode/input tests", "cell/menu probes"]

Known divergences: ["Current mode is host shell", "IGameMode omits original slots/metadata", "SDL bypasses callbacks"]

Unknowns: ["Other modes", "Input timing", "Queue timing", "Registration/camera ownership"]

Implementation status: ["Original: static lifecycle/input", "OpenSpore: clean-room manager", "Replacement: EXISTING_CLEAN_ROOM_INTERFACE", "Promotion: host seam only"]

### PKG-09-CELL-PRESENTATION — Cell GFX, HUD, scene assembly, and renderer boundary

Readiness: `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`; evidence: `SUPPORTED`; current gate: `SUPPORTED; blocked on M1/C-BOUNDARY/matched capture`.

Semantics: Compose CellGFX, HUD, scene entities, and renderer submission without claiming original pixels or placement.

Owner: Mode-owned Cell presentation stage and host renderer boundary.

Authoritative/runtime/persistent state: ["Authoritative: stable Cell/presentation associations, world/layer membership, preload readiness, display/HUD", "Runtime: cCellGFX, cCellUI, GFX/model/effect/texture handles, scene", "Persistent: none", "Invariant: presentation does not own gameplay/save state"]

Structures and fields: ["cCellGFX: worlds/layers/preloads/effects/display", "CellGFXObjectData: cell/model/creature/effect links", "cCellUI/Rollover: vectors/constants/zoom/selection/0.5s timer", "SceneEntity: ID/transform/model/material/visibility", "EntityPresentationRegistry: EntityId/PresentationHandle/rebuild/detach"]

Functions and contracts: ["0x00e5dba0 cCellGFX::Initialize", "0x00e666f0 PreloadResources", "0x00e663b0 PreloadCellResource", "0x00e665c0 PreloadPopulateResource", "0x00e55120 StartDisplay", "0x00e54270 cCellUI::Load", "0x00e62340 ShowHealthRollover"]

State machines and events: ["uninitialized -> preloading -> ready -> display_started -> stopped -> disposed", "detached -> attached -> rebuildable -> released"]; ["gfx_initialized", "resource_preloaded", "display_started", "hud_loaded", "health_rollover_shown", "frame_drawn"]

Data/assets and serialization: ["Cell/Populate/effect/model/material/texture keys", "Scene/world/layer identities", "Decoded packaged assets"]; ["No presentation serialization", "Stable identity/lifecycle only"]

Engine interfaces: ["B1/B2/B3", "IContentStore", "IPresentationResourceCache", "ISceneStage", "IEntityPresentationRegistry", "IEntityView", "IMaterialRegistry", "ITextureStore", "IEffectPresenter", "IRenderQueue", "IRenderer"]

Invariants: ["EntityId stable across rebuild", "Preload precedes display", "Handles release before stage", "HUD cannot mutate health", "Renderer not gameplay"]

Failure semantics: ["Missing model/GFX no-op presentation", "Missing/unsupported asset explicit", "Partial preload not ready", "Missing view non-fatal"]

Initialization/update/cleanup: ["Init: create stage/world/layers", "Tick: preload/views/effects/draws", "Shutdown: stop/detach/release"]

Validation: ["deterministic_unit", "fixture_comparison", "asset_driven", "integration", "original_binary_oracle", "cellgfx/cellui/scene tests", "scene.json", "test_cellstage.py"]

Known divergences: ["Vulkan pixels/fixed lighting not original", "Scene positions fixture choices", "No original material/animation/pose execution"]

Unknowns: ["Placement", "Preload order/timeout", "Material slots", "HUD timing/drawing", "Pose upload", "GPU retirement"]

Implementation status: ["Original: static GFX/UI/resource anchors", "OpenSpore: vertical slice", "Replacement: EXISTING_REPLACEMENT_SEAMS", "Promotion: not pixel promoted"]

### PKG-10-EDITOR-DISPATCH — Editor and message dispatch

Readiness: `BLOCKED_BY_RUNTIME`; evidence: `SUPPORTED`; current gate: `SUPPORTED; blocked on C-EVENT/C-ORDER/M0/M5/dependencies`.

Semantics: Own editor lifecycle/input/message dispatch and original menu-to-stage message route.

Owner: Editors::cEditor, editor mode/history/tool dispatch, and message/input handoff.

Authoritative/runtime/persistent state: ["Authoritative: editor active/mode/history/manipulator/tool/model/message state", "Runtime: cEditor, EditorModel, history, tools, listeners, input", "Persistent: authored assets separate; history survival unknown", "Invariant: pump/screenshot/frame cannot establish stage transition"]

Structures and fields: ["cEditor: interfaces, active +0x2b0, mode +0x31c, history +0x188, manipulator +0x148", "EditorModel: ResourceKey/rigblocks/names/colors/bounds/vtable alternatives", "EditorStateEditHistory: paired records/index/bounds", "cEditorAnimWorld: creature map/events/controllers"]

Functions and contracts: ["0x00584300 Initialize", "0x00588570 OnMouseDown", "0x0058ac10 OnKeyDown", "0x0058be50 Update", "0x00591fa0 HandleMessage", "0x00586410 CommitEditHistory", "0x00848210 MessagePump::PeekDispatch"]

State machines and events: ["editor uninitialized -> initialized -> entering -> active -> exited -> disposed", "idle -> hover -> drag/selection -> committed -> undo/redo", "pump -> message queued -> dispatch -> resource/mode request -> stage observed"]; ["editor_update", "input_event", "message_pump", "editor_mode_enter/exit", "edit_commit/undo/redo", "resource_transition"]

Data/assets and serialization: ["Editor model/rigblock/resource records", "Message IDs/payloads where mapped", "Editor resources"]; ["Editor asset/property save separate from profile persistence", "File grammar/history survival unresolved"]

Engine interfaces: ["IEventLoop", "IStageEventRouter", "IMessageManager", "IInputRouter", "IEditorView", "IAnimationEventSink"]

Invariants: ["Invalid/equal mode no-op", "History bounded", "Old mode before new", "Payloads not inferred from constants", "Tool/editor separated"]

Failure semantics: ["Invalid mode/history/tool bounded no-op/failure", "Missing renderer/model partial setup", "Message priority/tie/consume unknown"]

Initialization/update/cleanup: ["Init: services/listeners", "Tick: input/message/editor/actor/animation", "Shutdown: release selection/manipulator/model/skin/play mode/animation/world"]

Validation: ["deterministic_unit", "decomp_differential", "integration", "original_binary_oracle", "menu_walk", "menu_transition probe", "historical startup"]

Known divergences: ["No original editor/UTFWin in current tree", "SDL bypasses cEditor", "Current scene/animation shell not original editor"]

Unknowns: ["Message IDs/payloads", "Priority/tie", "Tool/actor semantics", "Menu-to-stage causality", "History save"]

Implementation status: ["Original: dependency-first static roots", "OpenSpore: observation shell/Cell host", "Replacement: UNRESOLVED", "Promotion: not authorized"]

### PKG-11-SIM-CORE — Simulator core services, tools, and missions

Readiness: `BLOCKED_BY_RE`; evidence: `INFERRED`; current gate: `INFERRED; blocked on manager roots, C-ORDER/C-EVENT, split adjudication`.

Semantics: Characterize Simulator manager composition, tool strategies, missions, and support services; proposed split required before implementation.

Owner: Simulator composition, tool registry/strategies, and mission lifecycle.

Authoritative/runtime/persistent state: ["Authoritative: manager ownership, tool state, mission state where direct", "Runtime: cSimulatorSystem, tools, missions, communication/services", "Persistent: mission/inventory/property/cGameData candidates", "Invariant: managers/tools/missions/Cell are distinct"]

Structures and fields: ["cSimulatorSystem: strategy vector +0x5c, UI graphics +0x20", "cToolManager/cToolStrategy: tool map +0x38, 18-slot contract", "cMission: ID/time/state/owner/target/rewards/costs/unlocks/property/comm", "cMissionManager: tracked/recent/tutorial/config/gaps", "cGameData: ID/definition/owner/political structural family"]

Functions and contracts: ["0x00b72370 cObjectPool_::DeleteObject", "0x00c8b6b0 IsNotStarOrBinaryStar", "0x01052f90 cDefaultAoETool::OnMouseDown", "0x01053790 cToolStrategy::OnSelect", "0x01053db0 cDefaultBeamTool::func4Ch", "Mission state SDK contract with unresolved reward order"]

State machines and events: ["uncomposed -> registered -> active -> updated -> disposed", "unselected -> selected -> aiming -> firing -> hit -> updated", "unaccepted -> accepted -> active -> completed/finished or failed/aborted/rejected"]; ["tool_input", "tool_selected", "object_deleted", "mission_update"]

Data/assets and serialization: ["Tool resources", "Mission/inventory records", "Property lists", "Game resources"]; ["ISimulatorSerializable/PropertyList/ClassSerializer", "Mission/inventory field coverage and remapping unresolved"]

Engine interfaces: ["IGameServices", "IBehavior", "IToolRegistry", "IMissionService", "IPropertyStore", "IEventRouter"]

Invariants: ["Typed service lifetime", "Shared tool strategy contract", "Mission callback order not assumed", "cGameData prefix not universal inheritance"]

Failure semantics: ["Invalid tool behavior variant-specific", "Mission failure routes incomplete", "Unknown side effects not promoted"]

Initialization/update/cleanup: ["Init: managers/register strategies", "Tick: services/tools/missions in evidenced order", "Shutdown: unregister/release/persist explicit data"]

Validation: ["decomp_differential", "deterministic_unit", "original_binary_oracle", "triage queue", "simulator-core state JSON", "split/serialization/trace gates"]

Known divergences: ["No broad OpenSpore implementation", "CellSim not Simulator core", "SDK vtable families not unique classes"]

Unknowns: ["Manager order", "Tool ownership/events", "Mission rewards", "Cross-stage handoff", "Serialization coverage"]

Implementation status: ["Original: inferred/static partial", "OpenSpore: no broad implementation", "Replacement: UNRESOLVED", "Promotion: blocked"]

### PKG-12-SIM-SPACE — Simulator Space stage, stars, planets, trade, and terraforming

Readiness: `BLOCKED_BY_ARCHITECTURE`; evidence: `INFERRED`; current gate: `INFERRED; blocked on Space trace/VAs/PKG-01/C-ORDER/C-EVENT`.

Semantics: Characterize Space context, star/planet records, trade, empire economy, terraforming, and Space-to-terrain handoff.

Owner: Space stage and star/planet/trade/empire records.

Authoritative/runtime/persistent state: ["Authoritative: SpacePlayerData, star/planet/trade/relationship state where fields confirmed", "Runtime: StarManager, Trading, SolarSystem, PlanetModel, empire/session", "Persistent: StarRecord, PlanetRecord, Empire, Mission, Inventory, trade routes", "Invariant: generated data not terrain; trade not Cell"]

Structures and fields: ["SpacePlayerData: active planet/star/context/player ID/empire cache/colonies", "cStarManager: grids/starter/saved/empire homes/relationship/trade/databases/collectables", "cStarRecord: version/time/position/type/empire/species/planets/count", "cPlanetRecord: orbit/scores/species/commodity/civ/tribe/tech/terrain/spice with offsets conflict", "cEmpire: political/money/relationships/home/culture/keys", "cSpaceTrading: spices/NPC/rare maps/groups/commodities", "cSolarSystem/cPlanetModel/cTerrainSphere: live surface/graphics"]

Functions and contracts: ["0x00b3d4d0 cSpaceTrading::Get", "0x00c8b6b0 IsNotStarOrBinaryStar", "0x01021960 context setter", "0x00bb4af0 regeneration check", "0x00bb4100 planet record generation", "0x00bb5b50 RecordToPlanet", "Trade/terraforming requests/failures unresolved"]

State machines and events: ["none -> planet -> solar_system -> galaxy", "star_not_generated -> counted -> materialized -> solar_loaded -> graphics_requested/destroyed", "trade request -> offer -> accepted/rejected -> inventory/value or failure", "terraform idle -> requested -> active -> completed/failed"]; ["space_stage_enter", "space_context_request", "star_planets_generated", "planet_surface_transition", "trade_action", "space_rare_discovered 0x06779f04"]

Data/assets and serialization: ["Star/planet records", "Species/commodity/civ/tribe", "Trade/inventory/rare", "Terrain/spice keys", "stars.db/stars.db.tmp"]; ["ISimulatorSerializable/PropertyList/star database", "Database replacement is not general save transaction"]

Engine interfaces: ["IGameServices", "IContentStore", "IWorldState", "IStarPlanetRepository", "ITradeService", "IPlanetSurfaceTransition", "ISceneStage"]

Invariants: ["Count/vector not interchangeable", "Context explicit", "Political-ID relationships", "Currencies not collapsed", "Handoff explicit"]

Failure semantics: ["Missing/invalid records unresolved", "Database rollback unknown", "Rare notification only on transition to found"]

Initialization/update/cleanup: ["Init: services/databases/context/session", "Tick: navigation/generation/trade/mission/relationship/presentation", "Shutdown: persist characterized records/release session/graphics/restore mode"]

Validation: ["decomp_differential", "asset_driven", "original_binary_oracle", "Space cluster", "state-machine world/empire JSON", "Space trace/round-trip/failure gates"]

Known divergences: ["No current Space implementation", "Cell resources not economy", "Current render not Space graphics"]

Unknowns: ["Stage entry", "Generation formulas", "Trade pricing/atomicity", "Terraforming", "Rewards", "Serialization", "Surface handoff"]

Implementation status: ["Original: static predicate/state", "OpenSpore: not implemented", "Replacement: UNRESOLVED", "Promotion: blocked"]

### PKG-13-SIM-CREATURE-TRIBECIV — Creature, tribe, city, relationship, and civilization stage

Readiness: `BLOCKED_BY_RE`; evidence: `UNKNOWN`; current gate: `UNKNOWN; blocked on VAs/stage trace/PKG-01/C-ORDER/C-EVENT`.

Semantics: Characterize creature/city/tribe/civilization state and relationship/progression boundaries separately from Cell and Space.

Owner: Creature-stage entities, tribe/city planning, civilization relationships, progression support.

Authoritative/runtime/persistent state: ["Authoritative: confirmed progression/relationship flags and static tribe/city fields", "Runtime: CreatureGameData/Base, Tribe/Planner, City/Building, Relationship/Comm/Collectable", "Persistent: cGameData/mission/inventory/property/collectable candidates", "Invariant: evolution/growMeter/money/relationship/rewards are distinct"]

Structures and fields: ["cCreatureGameData: brain +0x00, ability +0x24, evolution +0x28, abilities, glide", "cCreatureBase/Animal/Citizen: shared prefix only", "cTribe/Planner/Plan: political ID, population/food, position, plan state/check/food, members/tools", "cCity/Building/LayoutSlot: ownership/layout/placement/processing", "cRelationshipManager/Data: political map, value/flags/events, war bit 0/alliance bit 1"]

Functions and contracts: ["0x00d2e480 SetEvolutionPoints", "0x00d2e8a0 AddEvolutionPoints", "0x00d065a0 DeclareWar", "0x00d06920 DeclareAlliance", "0x00d01e30 BreakAlliance", "cMission::SetState SDK contract"]

State machines and events: ["attack/social/same", "unchanged/increased/capped", "absent/neutral/allied/war", "tribe waiting/check/food/requirements/executing"]; ["ability_mode_change", "creature_evolution_points_added", "relationship_war_peace_alliance", "player_empire_allied 0x04445d43", "lost_alliance 0x04445d44", "tribe_city_update"]

Data/assets and serialization: ["Creature data/rigblocks", "Tribe/city records", "Collectables", "Relationships", "Species/keys"]; ["ISimulatorSerializable/PropertyList/mission/collectables", "Cell/cross-stage sync unresolved"]

Engine interfaces: ["IGameServices", "IBehavior", "IRelationshipService", "IProgressionService", "IInventory", "IContentStore", "IEventRouter"]

Invariants: ["Ability bounded Attack/Social", "Evolution cap not level transition", "Political-ID flags", "Relationship score not money/progression", "Plan type not state enum"]

Failure semantics: ["Out-of-domain ability not rejected by setter", "Relationship guards partial", "Planner failures unresolved", "Payloads not inferred from IDs"]

Initialization/update/cleanup: ["Init: services/stage data", "Tick: progression/relationships/planners/cities/comm/presentation", "Shutdown: persist characterized/release live entities"]

Validation: ["decomp_differential", "deterministic_unit", "original_binary_oracle", "triage cluster/queue", "Track F state/events", "type families", "stage/planner/round-trip gates"]

Known divergences: ["growMeter not evolution points", "No current creature/tribe/city", "Prefix not proven inheritance"]

Unknowns: ["Stage entry", "Planner/herd/growth", "Mission/economy coupling", "Payloads", "Cross-stage save"]

Implementation status: ["Original: SDK/static fields and selected bodies", "OpenSpore: not implemented", "Replacement: UNRESOLVED", "Promotion: blocked"]

### PKG-14-TERRAIN-WORLD — Terrain, planet surface, and world rendering

Readiness: `BLOCKED_BY_RE`; evidence: `UNKNOWN`; current gate: `UNKNOWN; blocked on Space trace/terrain VAs/matched frame/C-BOUNDARY`.

Semantics: Characterize terrain/planet surface and world rendering separately from generated planet data and gameplay state.

Owner: Terrain/planet surface runtime and renderer-facing presentation.

Authoritative/runtime/persistent state: ["Authoritative: terrain surface/quad/weather/render state where static", "Runtime: PlanetModel, TerrainSphere, quads, weather, graphics, edit state", "Persistent: generated planet/terrain key separate; live edits not save", "Invariant: rendering is not generation or gameplay"]

Structures and fields: ["cPlanetModel: active binding/surface/graphics handoff", "cTerrainSphere: structural interfaces/surface/quad/weather/vtable conflict", "Quad: terrain surface/draw/material/texture", "TerrainModification: live edit/dirty/footprint/commit unknown"]

Functions and contracts: ["cTerrainSphere Land/Atmosphere/Decals static anchors", "Quad::Draw terrain submission", "cPlanetModel surface handoff binds generated record to terrain"]

State machines and events: ["raw phase/countdown/guard/terminal request", "planet_bound -> surface_loading -> graphics_attached -> active -> detached -> disposed"]; ["atmosphere_update", "planet_surface_transition", "terrain_draw", "terrain_edit_dirty"]

Data/assets and serialization: ["Planet/terrain keys", "Terrain/weather/atmosphere", "Terrain packages"]; ["Planet record/property boundary", "Live terrain persistence unresolved"]

Engine interfaces: ["ISceneStage", "IRenderer", "IMaterialRegistry", "ITextureStore", "IWorldState", "IPlanetSurfaceTransition"]

Invariants: ["Surface rendering does not redefine generated data", "Terrain graphics do not own gameplay", "ITerrain/interface/table counts separate", "World flags remain raw until owner identified"]

Failure semantics: ["Missing terrain/model/material presentation failure", "Surface attach/load paths unresolved", "No original pixel claim"]

Initialization/update/cleanup: ["Init: bind planet/terrain/create graphics", "Tick: surface/weather/terrain/pass submission", "Shutdown: detach/destroy graphics/restore mode"]

Validation: ["asset_driven", "integration", "original_binary_oracle", "render-boundary studies", "triage terrain cluster", "matched frame/Space trace"]

Known divergences: ["No current terrain implementation", "Current renderer not original terrain/RW", "Data/presentation split"]

Unknowns: ["Transition owner", "Terrain machine", "Weather", "Placement", "Material/light/pixels", "Persistence"]

Implementation status: ["Original: SDK/static render anchors", "OpenSpore: not implemented", "Replacement: UNRESOLVED", "Promotion: blocked"]

### PKG-15-EDITOR-SUPPORT — Palettes, Skinner, and editor support assets

Readiness: `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`; evidence: `INFERRED`; current gate: `INFERRED; blocked on VAs/vtables/editor boundary/order`.

Semantics: Characterize palette/viewer/texture-paint support without merging into editor command or gameplay semantics.

Owner: Palettes, AdvancedItemViewer, Skinner texture-paint, editor support models.

Authoritative/runtime/persistent state: ["Authoritative: direct palette/viewer/support state only", "Runtime: pages/categories/viewer/painter/model handles", "Persistent: authored resources separate", "Invariant: support operations need producer/consumer path"]

Structures and fields: ["PalettePage: identity/load/category", "AdvancedItemViewer: vtable/item/page/category/draw", "cSkinnerTexturePainter: paint/start/end", "EditorModel: ResourceKey/rigblocks/names/colors/bounds"]

Functions and contracts: ["0x004ae250 EditorModel::SetColor", "0x005c8bc0 PalettePage::Load", "0x005f4750 AdvancedItemViewer::func40h", "cSkinnerTexturePainter PaintRegion/StartRender/EndRender"]

State machines and events: ["unloaded -> loaded -> category_selected -> viewer_updated"]; ["editor_model_color_set", "palette_loaded", "texture_paint_start_end"]

Data/assets and serialization: ["Palette pages", "Viewer item/category", "Texture-paint resources", "Editor resources"]; ["Support/resource formats not established", "No round-trip"]

Engine interfaces: ["IEditorView", "IRenderer", "IContentStore", "IMaterialRegistry", "ITextureStore"]

Invariants: ["Palette separate from editor mode", "Viewer/paint cannot mutate gameplay", "Static readiness not runtime"]

Failure semantics: ["Missing palette/resource and viewer/paint failures unresolved", "Ownership required before authority"]

Initialization/update/cleanup: ["Init: load support/init viewer/palette", "Tick: update viewer/paint", "Shutdown: release support handles"]

Validation: ["deterministic_unit", "fixture_comparison", "decomp_differential", "not_yet_testable", "Palette/EditorModel queue rows", "AdvancedItemViewer evidence"]

Known divergences: ["No original palette/viewer/paint implementation", "Names do not prove command ownership"]

Unknowns: ["Viewer lifecycle", "Paint state", "Categories", "Runtime order"]

Implementation status: ["Original: inferred/static support", "OpenSpore: not implemented", "Replacement: UNRESOLVED", "Promotion: blocked"]

### PKG-16-SPOREPEDIA-ONLINE — Sporepedia asset metadata and online boundary

Readiness: `BLOCKED_BY_RE`; evidence: `INFERRED`; current gate: `INFERRED; blocked on local fixture/caller/no-network boundary`.

Semantics: Characterize local Sporepedia metadata while treating online/Pollinator behavior as a network-disabled boundary.

Owner: Sporepedia local metadata and future online service boundary.

Authoritative/runtime/persistent state: ["Authoritative: local asset ID/name/editability metadata", "Runtime: cSPAssetDataOTDB and local request/response", "Persistent: none established", "Invariant: local predicate is not online request/service"]

Structures and fields: ["cSPAssetDataOTDB: ID/name/editability/author/tags/time/local-online", "Request/response: identity/network lifecycle unresolved"]

Functions and contracts: ["0x00641400 IsEditable", "0x00641770 HasName", "0x006417c0 GetAssetID", "0x00641460/0x006417b0 asset virtuals unresolved"]

State machines and events: ["asset_unavailable -> loaded -> queried -> result", "online service not_initialized -> request -> response/failure unresolved"]; ["asset_metadata_query", "editability_result", "online_request"]

Data/assets and serialization: ["Local asset metadata", "No network assets"]; ["Asset metadata/online payload unresolved", "No round-trip"]

Engine interfaces: ["IContentStore", "IAssetMetadata", "IStubbedOnlineService"]

Invariants: ["Local metadata does not imply network", "Unknown virtuals not named API", "Network remains stubbed"]

Failure semantics: ["Missing local asset/unsupported virtual distinct", "Network failure not gameplay reconstruction"]

Initialization/update/cleanup: ["Init: metadata or no-network stub", "Tick: local metadata only", "Shutdown: release local/stub state"]

Validation: ["deterministic_unit", "fixture_comparison", "decomp_differential", "not_yet_testable", "Sporepedia queue rows", "no-network negative"]

Known divergences: ["No current Sporepedia implementation", "Local predicates not online client", "Pollinator non-goal"]

Unknowns: ["Caller order", "Full asset semantics", "Request/response", "Online errors"]

Implementation status: ["Original: local predicates/static metadata", "OpenSpore: not implemented", "Replacement: NOT_IMPLEMENTED", "Promotion: local metadata only"]

### PKG-17-ANIMATION-SWARM — Cell animation and Swarm/creature animation boundary

Readiness: `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`; evidence: `INFERRED`; current gate: `INFERRED; blocked on event-to-pose/Swarm/C-BOUNDARY`.

Semantics: Separate gameplay-owned Cell animation intent from pose evaluation, Swarm effects, and unresolved animation implementation.

Owner: Cell animation state and animation/effect boundary; Swarm unresolved.

Authoritative/runtime/persistent state: ["Authoritative: Cell clip/blend state when direct", "Runtime: cCellObjectData animation, manager/world, pose/effect instances", "Persistent: none established", "Invariant: intent gameplay; skeleton/pose/particles backend"]

Structures and fields: ["cCellObjectData: current animation +0x1b0, blend +0x1b4/+0x1b8, GFX +0x248", "cCellAnimDefinition name-level", "IAnimationController: current/target clip/blend/loop/time/phase", "IEffectPresenter: definition/instance/transform/lifecycle", "Swarm animation/effect state unresolved"]

Functions and contracts: ["0x00e6d200 PlayAnimation", "0x00e63560 LoadEffectMap", "0x00e66840 InstanceEffectOnCell", "CellAnim host mapping only", "Swarm functions unresolved"]

State machines and events: ["detached -> clip_active -> transition -> complete/interrupted", "undefined -> created -> running -> paused/hidden -> stopped -> released", "Swarm unidentified"]; ["animation_event", "animation_played", "effect_instance", "swarm_animation_event"]

Data/assets and serialization: ["Cell animation/effect definitions", "RW4 animation/skeleton static sections", "Cell/RW4 resources"]; ["Asset codecs bounded", "Pose persistence not established"]

Engine interfaces: ["IAnimationService", "IAnimationController", "IAnimationWorld", "IPoseEvaluator", "IEffectPresenter", "IEntityView"]

Invariants: ["Missing model/GFX no-op", "Intent before visible pose", "Effect subordinate to entity/stage", "RW internals not gameplay"]

Failure semantics: ["Missing model/GFX/effect/invalid clip/pose failure distinct", "Event source/callback failure unknown", "Helper tests do not prove renderer integration"]

Initialization/update/cleanup: ["Init: animation service/world/clip", "Tick: intent/update/snapshot/submit", "Shutdown: stop effects/release animation/pose/detach"]

Validation: ["deterministic_unit", "decomp_differential", "integration", "original_binary_oracle", "cellanim_test", "effectmap_test", "event-to-pose/Swarm gates"]

Known divergences: ["CellAnim not wired to cell_stage", "No skeleton/pose upload", "Swarm unresolved"]

Unknowns: ["Event producer", "Blend completion", "Pose order", "Vehicle coupling", "Swarm ownership"]

Implementation status: ["Original: static Cell intent", "OpenSpore: partial CellAnim", "Replacement: PARTIAL_EXISTING_CONTRACT", "Promotion: blocked by event-to-pose"]

### PKG-18-UI-SCRIPTING — UTFWin and scripting/configuration infrastructure

Readiness: `BLOCKED_BY_RUNTIME`; evidence: `INFERRED`; current gate: `INFERRED; blocked on M0/C-EVENT/C-ORDER/message/grammar`.

Semantics: Keep UTFWin/UI and ArgScript/config parsing as replaceable infrastructure and observation boundaries.

Owner: UTFWin window/proc/message infrastructure and ArgScript parser/configuration content.

Authoritative/runtime/persistent state: ["Authoritative: window/proc/message structure and parser state where direct", "Runtime: UTFWin hierarchy/routing, script scopes, config/property", "Persistent: config/script files separate", "Invariant: UI/script/editor/gameplay records distinct"]

Structures and fields: ["UTFWinObject: allocator/hierarchy/duplicate 21-slot bases", "Window: parent/children, WinProc +0x64, area/cursor/state/caption/font", "FormatParser: definitions/variables/blocks/scope", "pdtk widget: command/cursor/selection/focus/layout"]

Functions and contracts: ["0x00848210 MessagePump::PeekDispatch", "0x00960250 Window::SendMsg", "FormatParser ParseFloat/ParseUInt/SetFlag/CreateDefinitionSafe", "EditorNamePanel button-select bridge"]

State machines and events: ["os_event -> window_message -> proc_filter -> handler -> consumed/bubbled", "uninitialized -> scope_open -> nested -> closed -> disposed", "ui_event -> message -> mode request -> stage unknown"]; ["ui_message", "script_parse", "content_load", "resource_transition"]

Data/assets and serialization: ["UTFWin records", "ArgScript/config bytes", "pdtk commands", "UI content"]; ["ArgScript/config/property streams", "pdtk grammar/whole UI persistence unresolved"]

Engine interfaces: ["IEventLoop", "IStageEventRouter", "IMessageManager", "IConfigCodec", "IPropertyStore", "IWindowCompatibility"]

Invariants: ["Registration separate from emission", "No universal UI/App ABI", "Scope nesting balances", "pdtk strings bounded commands"]

Failure semantics: ["Priority/tie/consume unresolved", "Script lifecycle failures unresolved", "UI-to-stage causality unknown"]

Initialization/update/cleanup: ["Init: parser/window/message", "Tick: poll/route/parse", "Shutdown: listeners/scopes/windows/UI/script release"]

Validation: ["deterministic_unit", "integration", "original_binary_oracle", "agent_overlay", "menu_walk", "M0/M5/UI grammar"]

Known divergences: ["No current UTFWin", "SDL direct path", "Observation shell not UI reconstruction"]

Unknowns: ["Dispatch order", "Priority/tie/return", "pdtk grammar", "UI-stage order", "Script format"]

Implementation status: ["Original: static framework/parser", "OpenSpore: observation shell", "Replacement: UNRESOLVED", "Promotion: blocked"]

### PKG-19-AUDIO-INPUT — Audio and original input marshalling

Readiness: `BLOCKED_BY_RE`; evidence: `UNKNOWN`; current gate: `UNKNOWN; blocked on cluster/trace/negative device contract`.

Semantics: Identify original audio/input-device boundaries before replacement; keep them separate from host SDL/DSOUND/CellInput.

Owner: Original audio service and platform input marshalling.

Authoritative/runtime/persistent state: ["Authoritative: none established", "Runtime: unknown audio/input event/device state", "Persistent: none", "Invariant: host adapters are not original device semantics"]

Structures and fields: ["Audio service candidate: handle/cue/voice", "Original input: device event/normalized values/mode routing", "Both name-level/unresolved"]

Functions and contracts: ["0x00571f80 PlayProceduralAudio", "GameInput OnKeyDown/OnKeyUp candidate", "No service ownership established"]

State machines and events: ["device_event -> normalized -> mode_route -> consumed/default unresolved", "audio request -> backend -> started/failed unresolved"]; ["audio_event", "input_marshalling_event"]

Data/assets and serialization: ["Candidate audio/input identities", "No persistent assets"]; ["None established"]

Engine interfaces: ["IPlatformHost", "IAudioSink", "IInputRouter"]

Invariants: ["Host device implementation not original", "No CellInput ownership from low evidence"]

Failure semantics: ["No-audio/no-input remains negative", "Device/service errors unresolved"]

Initialization/update/cleanup: ["Init: identify/provision boundary", "Tick: marshal/dispatch only after evidence", "Shutdown: release handles"]

Validation: ["provenance_negative", "original_binary_oracle", "not_yet_testable", "cell_trace", "cell_movement probes", "bounded trace"]

Known divergences: ["Host SDL/DSOUND not original", "Current CellInput is clean-room contract"]

Unknowns: ["Function ownership", "Input routing", "Audio ownership", "Device behavior"]

Implementation status: ["Original: blocked on identification", "OpenSpore: host adapter", "Replacement: UNRESOLVED", "Promotion: blocked"]

### PKG-20-GAMEGLOBAL — GameGlobal map and miscellaneous state

Readiness: `BLOCKED_BY_RE`; evidence: `UNKNOWN`; current gate: `UNKNOWN; blocked on map decompilation and owner/key/value contract`.

Semantics: Characterize the high-fan-in GameGlobal map lookup without assigning manager or gameplay meaning.

Owner: GameGlobal map/lookup state pending characterization.

Authoritative/runtime/persistent state: ["Authoritative: none established", "Runtime: candidate global map/callers; owner/mutation/lifetime unresolved", "Persistent: none", "Invariant: high fan-in is not manager identity"]

Structures and fields: ["GameGlobal state: owner/map type/key/value/mutation/consumers", "map_int_whatever_find: body/key/value/absence semantics"]

Functions and contracts: ["0x00e5c780 map_int_whatever_find lookup candidate; body absent and requires RE"]

State machines and events: ["owner_unresolved -> key_unresolved -> lookup_result -> consumer_unresolved"]; ["global_map_lookup"]

Data/assets and serialization: ["Candidate map identity", "No persistent assets"]; ["Unknown", "No round-trip"]

Engine interfaces: ["Candidate IIdMap only after characterization"]

Invariants: ["No IIdMap promotion before owner/key/value evidence", "Fan-in does not establish semantics"]

Failure semantics: ["Missing key/null owner/invalid key unresolved"]

Initialization/update/cleanup: ["Init: identify owner/init after contract", "Tick: lookup/read/write after mutation contract", "Shutdown: release map state"]

Validation: ["decomp_differential", "not_yet_testable", "readiness foundation", "xref TSV", "map decomp/field/consumer tests"]

Known divergences: ["Current map assumptions are not original"]

Unknowns: ["Map type", "Owner", "Key domain", "Value", "Mutation/persistence"]

Implementation status: ["Original: unknown", "OpenSpore: no contract", "Replacement: UNRESOLVED", "Promotion: blocked"]

### PKG-21-UNKNOWN-ROUTING — Unknown routing and ownership backlog

Readiness: `BLOCKED_BY_RE`; evidence: `UNKNOWN`; current gate: `UNKNOWN; characterization-only`.

Semantics: Record unresolved routing/ownership debt without inventing semantic subsystems from fan-in or vtable proximity.

Owner: Unresolved cross-domain backlog; no implementation owner.

Authoritative/runtime/persistent state: ["Authoritative: none", "Runtime: unresolved functions/vtable families only", "Persistent: none", "Invariant: unknown rows stay outside implementation scope"]

Structures and fields: ["Anonymous unresolved functions", "Unresolved vtable families", "UNKNOWN-HIGH debt rows"]

Functions and contracts: ["0x00e780a0 cross-listed lifecycle candidate", "Unknown-vtable implementations", "Unknown-fun mass; ownership and contracts unresolved"]

State machines and events: ["unknown function -> typed package only after evidence", "unresolved vtable -> class/interface only after evidence"]; ["ownership_transition", "semantic_event_model"]

Data/assets and serialization: ["Debt map", "No game assets"]; ["None"]

Engine interfaces: ["None until ownership is established"]

Invariants: ["No fan-in/namespace/vtable-proximity semantic promotion", "No speculative per-region split"]

Failure semantics: ["Unknown ownership remains explicit", "Missing body is uncaptured evidence, not failure"]

Initialization/update/cleanup: ["Init: none", "Tick: triage/characterize only", "Shutdown: none"]

Validation: ["provenance_negative", "decomp_differential", "not_yet_testable", "triage/readiness/debt artifacts"]

Known divergences: ["No current implementation correspondence"]

Unknowns: ["1,598 unknown gameplay rows", "39,716 unknown canonical rows", "All ownership/events"]

Implementation status: ["Original: unknown", "OpenSpore: backlog only", "Replacement: UNRESOLVED", "Promotion: prohibited"]

### PKG-22-RUNTIME-CRT-STL — Runtime, CRT, STL, and third-party wrappers

Readiness: `INFRASTRUCTURE_REPLACEMENT`; evidence: `SUPPORTED`; current gate: `SUPPORTED as out-of-scope attribution`.

Semantics: Account for runtime/third-party ancestry and exclude semantic reconstruction unless a gameplay boundary needs a narrow stub.

Owner: CRT/STL/runtime imports and third-party wrappers.

Authoritative/runtime/persistent state: ["Authoritative: attribution boundary only", "Runtime: platform/allocator/import wrappers", "Persistent: none", "Invariant: runtime wrappers are not gameplay"]

Structures and fields: ["MSVCR90/import ancestry", "Runtime/allocator/stream wrappers", "No semantic game structures"]

Functions and contracts: ["MSVCR90 wrapper rows: platform/runtime calls only", "No package function anchors"]

State machines and events: ["Gameplay call -> runtime/CRT implementation -> out of scope"]; ["runtime_wrapper_event"]

Data/assets and serialization: ["No game assets"]; ["None"]

Engine interfaces: ["IPlatformHost", "IAudioSink", "Bounded stream/device adapters"]

Invariants: ["No gameplay semantics from wrapper names", "Stub only at explicit boundary"]

Failure semantics: ["Runtime errors remain platform-level", "No original gameplay error claim"]

Initialization/update/cleanup: ["Init: runtime services", "Tick: platform services", "Shutdown: release runtime services"]

Validation: ["deterministic_unit", "attribution audit", "not_yet_testable", "track-b accounting", "attribution JSON"]

Known divergences: ["Current SDL/Vulkan/host runtime is modern replacement", "No original runtime reconstruction"]

Unknowns: ["Only any concrete gameplay dependency is relevant"]

Implementation status: ["Original: out of scope", "OpenSpore: host runtime exists", "Replacement: OUT_OF_SCOPE", "Promotion: prohibited"]

## Function consolidation

The 2,149 gameplay records are retained in semantic-blueprint.json with the requested fields: VA, name, subsystem, role, ABI/signature, inputs, outputs, reads, writes, structures, fields, events, transitions, dependencies, engine calls, side effects, invariants, failure, persistence, package, evidence, confidence, validation, and next action.

- Strong runtime-verified semantic contracts: 0.
- Bounded non-verified semantic consolidations: 411.
- Partial static semantic characterizations: 173.
- Semantically not established: 1,976.
- No persisted gameplay body: 1,977; this population overlaps the semantic populations and is not additive.
- Unknown-needs-investigation: 1,598; this population is distinct but potentially overlapping.
- Next actions: 1,671 TARGETED_DECOMP, 221 TYPE_RECOVERY, 124 RUNTIME_ORACLE, 62 SAFE_TO_DEFER, 36 STATE_ANALYSIS, 28 CALLEE_ANALYSIS, 6 CALLER_ANALYSIS, 1 DATA_ANALYSIS.

## State, events, and chokepoints

The state machine records retain App lifecycle, mode activation, Cell lifecycle/death/rebuild/pool, relationship flags, evolution/mission, time/pause, persistence, resource lifecycle, SpaceContext, star/planet generation, editor modes, and raw phase states. Mode axes remain distinct: App active mode, Simulator strategy, input mode, SpaceContext, scenario mode, editor submode, and Cell lifecycle.

Event families remain family-specific. App immediate/deferred transport, UTFWin input/UI, standard messages, Cell interactions, editor animation, and deferred domain events are not a universal event ABI.

- **app_mode_publication_handoff (T0, CONFIRMED)**: Record App callbacks, active-index publication, announcements, Simulator listener, payload words, and cStrategy writes in one trace. Boundary: App active-index state and Simulator strategy state are distinct.
- **app_transport_queue_timing (T0, SUPPORTED)**: Instrument immediate/deferred processors, queue keys, drain modes, callback-produced posts, and release timing. Boundary: Immediate/deferred, registration/delivery, snapshot/drain, and priority/key are separate.
- **opaque_forwarded_state (T0, SUPPORTED)**: Find first writer, receiver type, storage definition, consumer set, clear paths, freshness, and teardown. Boundary: Borrowed opaque uint32; absent source is 0xffffffff; no pointer or enum promotion.
- **persistence_mode_handoff (T0, UNKNOWN)**: Correlate mode lifecycle, serializer callbacks, temp/close/replace, restored identity, and cross-file behavior in an approved round trip. Boundary: Live runtime, presentation, serializable candidate, and restored identity remain separate.
- **receiver_typed_avatar_boundary (T0, SUPPORTED)**: Record receiver identity before every +0x54 read and compare replacement, Cell, GFX, and simulation identity. Boundary: A noun-layout receiver may expose a current gameplay creature; other receivers are not forced to match.
- **simulator_service_publication (T0, UNKNOWN)**: Run a read-only computed-publisher and teardown trace for each service slot without merging slots. Boundary: Global service handles are independent lifecycle ports; zero image values do not prove no writer.
- **state_identity_axis_blocker (T0, SUPPORTED)**: Record pre/post values by owner and mode phase; fail closed on cross-owner copying without direct evidence. Boundary: App, Simulator, input, scenario, SpaceContext, Cell, empire, avatar, and cache identities are owner-specific.
- **temporal_scheduler_blocker (T1, UNKNOWN)**: Recover pause, speed, scheduler epoch, same-time order, duplicate, expiry, and cancellation behavior. Boundary: Timing/deferred callbacks are a separate substrate; SDK names and queue placement do not establish order.
## Architecture decisions and blockers

Safe decisions are frozen in the JSON decision register. Provisional decisions remain explicit and are not reopened without contradictory evidence. The three architecture-changing blockers are noun/star root publication, DAT_0167eaec/0x00b5b800 state identity, and persistence object/reference/restore plus mode handoff.

### BLOCKER-A — Noun/star root publication, equality, and teardown

Impact: Noun-root and phase-specific star outcomes can change service ownership, entity lookup, mode teardown, save ownership, relationship graphs, rebind ordering, and cache invalidation.

Interim boundary: Keep four distinct opaque noun/star root ports with explicit publish, replace, invalidate, and unpublish hooks. Keep star lookup and cache mechanics owner-local.

Affected packages: PKG-01-SHARED-STATE-ROOTS, PKG-02-APP-LIFECYCLE, PKG-03-RESOURCE-IO, PKG-08-CELL-MODE, PKG-11-SIM-CORE, PKG-12-SIM-SPACE, PKG-13-SIM-CREATURE-TRIBECIV, PKG-20-GAMEGLOBAL, PKG-21-UNKNOWN-ROUTING

Decision criterion: Root identity, liveness, publication order, or teardown must be reproduced across modes, plugins, saves, or original ABI boundaries.

### BLOCKER-B — DAT_0167eaec/0x00b5b800 first writer, physical state identity, freshness, and downstream ownership

Impact: The first writer and physical type of forwarded receiver+0x20 determine whether routing is an opaque tagged read, scalar state machine, or object/reference ownership graph.

Interim boundary: Expose DAT_0167eaec and 0x00b5b800 only as a borrowed opaque uint32 with 0xffffffff for absent source and no ownership transfer.

Affected packages: PKG-01-SHARED-STATE-ROOTS, PKG-02-APP-LIFECYCLE, PKG-05-CELL-CONTENT, PKG-06-CELL-STATE, PKG-08-CELL-MODE, PKG-11-SIM-CORE, PKG-18-UI-SCRIPTING, PKG-19-AUDIO-INPUT, PKG-21-UNKNOWN-ROUTING

Decision criterion: The value must be treated as a mode, strategy, owner object, persistent state, or retained pointer.

### BLOCKER-C — Persistence object/reference/restore graph and mode-handoff boundary

Impact: The outer envelope, object/reference table, descriptor graph, field survival, migration policy, mode handoff, and transaction scope can force a schema registry, recovery protocol, or ownership-transfer design.

Interim boundary: Use schema/callback serialization, stable object references with deferred association, a versioned header, and explicit temp/close/replace boundaries while keeping live Cell, avatar, and presentation state transient.

Affected packages: PKG-03-PROPERTY-CONFIG, PKG-03-RESOURCE-IO, PKG-05-CELL-CONTENT, PKG-08-CELL-MODE, PKG-11-PERSISTENCE, PKG-11-SIM-CORE, PKG-12-SIM-SPACE, PKG-13-SIM-CREATURE-TRIBECIV, PKG-14-CROSS-MODE-OBJECT, PKG-20-GAMEGLOBAL

Decision criterion: Byte-compatible saves, exact migration, automatic mode-exit persistence, original pointer survival, or cross-file atomicity is required.

## OpenSpore abstraction extraction

- **App lifecycle ports**: replace Original AppSystem graph, Raw vtables, Pointer identity; preserve Bootstrap, Service publication, Mode lifecycle, Update, Shutdown; modern interfaces: IAppHost, IGameModeRegistry, IMessageManager, IResourceProvider, IGameServices.
- **Owner-qualified shared state**: replace Unified singleton, Global slot pointers, Cross-owner equality; preserve Owner-qualified reads, Borrowed/owned semantics, Publish/replace/invalidate/unpublish; modern interfaces: IPlayerIdentityPort, IObjectRegistryPort, IWorldStatePort, IIdMapPort, IEventRouterPort.
- **Content and records**: replace Manager cache layout, Original priority/async state, Path coupling; preserve Complete TGI, Bounded extent/decompression, Typed payload identity, Explicit errors; modern interfaces: IContentStore, IResourceProvider, IRecordCodec, IStream, IReferenceResolver.
- **Geometry and textures**: replace RenderWare layouts/caches, Raster object identity; preserve Topology, Content identity, Material/texture slots, Ordered draw; modern interfaces: IModelStore, IMeshSource, IMeshDraw, IMaterialRegistry, ITextureStore.
- **Camera and movement**: replace Renderer camera, Host stand-in ABI, Original raw function signature; preserve Ordered input/camera, Ray-plane target, Guards, Target/orientation/moving state; modern interfaces: ICameraRayProvider, ICameraService, IPlayerMovement, IInputRouter, IEntityPool.
- **Backend-neutral transforms**: replace D3D/RenderWare transform layouts, Object pointer identity; preserve Position, Orientation, Scale, Attachment, Composition order; modern interfaces: IEntityTransform, ICompositionService, IRenderMatrixConverter.
- **Cell state and pool**: replace cCellGame layout, cCellObjectData byte compatibility, CellSim as original runtime; preserve Pool index/entity separation, Health clamp, Bounded query/combat rules; modern interfaces: ICellGameState, IEntityPool, ICellQuery, IAdvectState, ICombatRules, IAnimationIntent.
- **Presentation stage**: replace Cell GFX graph, HUD widget graph, Original renderer/material state; preserve Preload/display/stop/shutdown, Detach/rebuild, Stable identity, Handle lifetime; modern interfaces: ISceneStage, IEntityPresentationRegistry, IEntityView, IEffectPresenter, IRenderQueue, IRenderer.
- **Animation and pose**: replace RenderWare skeleton/pose buffers, Unproven fallback and phase order; preserve Current/target clip, Blend, Loop, Time scale, Ordered transitions; modern interfaces: IAnimationController, IAnimationWorld, IPoseEvaluator, PoseSnapshot, IEffectPresenter.
- **Renderer command/state**: replace RenderWare caches, D3D9 COM vtables/device globals, Raw backend state; preserve Binding order, Topology, Visible state, Submission order, Device readiness/resize; modern interfaces: IRenderCommandEncoder, IRenderStateCache, IGpuDevice, IMaterialBindings, SamplerPolicy.
- **Platform/input/time/window**: replace Win32 handles/messages, SDL event identity, Original pump/polling; preserve Ordered events, Normalized input, Monotonic timing, Window lifecycle; modern interfaces: IPlatformHost, IEventLoop, IInputBackend, IMonotonicClock, IWindowHost, IOverlayStack.
- **Family-specific messages/UI**: replace Universal payload ABI, UTFWin graph, pdtk implementation, Raw message IDs as gameplay; preserve Immediate/deferred delivery, Registration/queue distinction, Listener/handler/context, UI semantic callbacks; modern interfaces: IMessageBus, IUiWindowHost, IEventLoop, IMessageManager, IStageEventRouter.
- **Persistence codec**: replace Exact .prop/.spo bytes, Raw pointer restoration, Automatic save, Unproven atomicity/migration; preserve Typed local codec, Attribute callbacks, Stable deferred references, Versioned header, Replace boundary; modern interfaces: IPropertyStore, IConfigCodec, IStream, IObjectIdentityGraph, IAtomicReplaceBoundary.
- **Audio/host runtime**: replace DSOUND/import identity, MSVCR90 ABI, Host device behavior as original; preserve Audio request boundary, Normalized input, Fallback semantics, Required clock behavior; modern interfaces: IAudioSink, IInputBackend, IPlatformHost, ICalendarClock, ITimeZoneProvider.
## Validation and readiness

Validation classes are STATIC_ONLY, DECOMP_DIFFERENTIAL, FIXTURE, ORIGINAL_RUNTIME_ORACLE, REPLACEMENT_HOOK, INTEGRATION, and NOT_YET_TESTABLE. Current strongest validation is deterministic host/fixture/decomp/synthetic-hook work. No positive original Cell or mode-specific runtime oracle exists.

Eight packages have bounded implementation seams with local unknowns: PKG-03, PKG-04, PKG-05, PKG-06, PKG-08, PKG-09, PKG-15, and PKG-17. Their briefs are in docs/analysis/implementation-briefs/. They must not be represented as original-compatible implementations.

## Dependency and research outputs

The implementation graph distinguishes hard, soft, optional, and runtime-validation edges and provides parallel waves. The focused research briefs in docs/analysis/future-research/ are minimal investigations, not a generic decompilation campaign.

## Integrity boundary

The synthesis does not rewrite historical triage artifacts, change SPORE/, patch the executable, or modify source implementation. Final live integrity checks are recorded in the verification section of the final response and the generated verification report.
