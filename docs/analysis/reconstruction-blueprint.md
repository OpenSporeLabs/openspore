# OpenSpore Reconstruction Blueprint

This document is the package-level implementation specification. It is intentionally semantic: original class layouts, raw vtables, compiler artifacts, and platform/runtime internals are evidence or compatibility adapters, not gameplay contracts.

## Package taxonomy

- Move MessagePump and menu-to-stage message bridge from PKG-18 to PKG-10.
- PKG-11 into core services and tools/missions after ownership characterization
- PKG-17 into Cell animation and Swarm/pose/effects after event-to-pose evidence
- PKG-18 into UTFWin UI and ArgScript/configuration after message/parser characterization
- PKG-19 into audio and original input after independent device contracts
- PKG-10: Editor and Message Dispatch
- PKG-13: Creature, Tribe, City, Relationship, and Civilization Stage
- PKG-18: UTFWin and Scripting/Configuration Infrastructure
- PKG-20: GameGlobal Map and Miscellaneous State
- PKG-04 and PKG-09
- PKG-12 and PKG-14
- PKG-05 and cCellSerializableData/PKG-06
- PKG-12 empire/relationship state and Cell/generic cGameData
- PKG-21 unknown backlog

## PKG-00-EVIDENCE-VALIDATION — Evidence acquisition, provenance, and validation infrastructure

**Package:** PKG-00-EVIDENCE-VALIDATION

**Purpose:** Preserve identity, provenance, negative outcomes, and test results separately from game semantics.

**Subsystem owner:** Evidence, observatory, KG, dossier, and validation tooling.

**Authoritative state:** ["Authoritative: evidence records, manifests, fixtures, outcomes, queue state", "Runtime: no game state; bounded observation only", "Persistent: read-only artifacts and test records", "Invariant: no uncorrelated trace changes semantic status"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["EvidenceRecord: binary/VA, tier, environment, outcome, negative reason", "TraceManifest: binary/probe hashes, image base, Wine/display/input, raw JSONL, events_total"]

**Functions:** ["observe.py launch/trace/analyze: approved bounded observation", "fixture_check/test_run: fixture identity and tests", "kg_record/queue_op: evidence/queue state without promotion"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["pinned SporeApp.exe", "Ghidra/SDK exports", "committed tests", "approval and lock gates", "SPORE read-only"]

**State machines:** ["artifact -> provenance record -> package claim only after adjudication", "zero-event/failed-boot -> negative result"]

**Events/messages:** ["function_entry", "decompile_provenance", "test_outcome", "zero_event"]

**Data/assets:** ["Fixtures, probe manifests, raw JSONL, dossiers", "No game assets"]

**Serialization:** ["Deterministic evidence JSON/JSONL", "Identity/provenance/outcome round-trip required"]

**Engine interfaces:** ["Read-only Ghidra/SDK", "Observatory approval/trace", "KG sidecar"]

**Invariants:** ["Generic frames and empty traces are negative/incomplete", "Screenshots do not substitute for events", "No implicit repository/KG write"]

**Error/failure semantics:** ["Zero events remains zero events", "Failed boot and clean exit are distinct", "Missing provenance is not success"]

**Initialization:** Init: pin artifact/environment

**Update/tick:** Tick: capture bounded events/outcome

**Shutdown/cleanup:** Shutdown: preserve artifacts and negative result

**Validation strategy:** ["provenance_negative", "deterministic_unit", "integration", "tests/test_dossier.py", "tests/test_kg_schema.py", "tests/test_kg_seed.py", "tests/mcp/"]

**Known divergences:** ["Infrastructure is not a game replacement", "Tracer plumbing is not original evidence"]

**Unknowns:** ["No positive original Cell trace", "Future artifacts require C-PROV"]

**Implementation status:** `INFRASTRUCTURE_REPLACEMENT`. This is a replacement boundary or evidence tool, not a gameplay semantic package.

## PKG-01-SHARED-STATE-ROOTS — Simulator shared-state roots and interface freeze

**Package:** PKG-01-SHARED-STATE-ROOTS

**Purpose:** Characterize high-fan-in service roots and freeze typed service contracts before dependent reconstruction.

**Subsystem owner:** Simulator service composition and shared-state access.

**Authoritative state:** ["Authoritative: characterized accessor/service contract", "Runtime: packed globals, service pointers, map lookups", "Persistent: none", "Invariant: fan-in and FUN names do not establish types"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["Simulator service block: 0x0167eaf0/af8/eb0c/eb14/eb2c/eb50 and unresolved slots", "Unnamed layout: owner/global/lifetime/mutation/invalid handle", "map_int_whatever_find: owner/key/value/mutation"]

**Functions:** ["0x00b3d350 cGameInputManager::Get returns DAT_0167eaf8", "0x00b3d4d0 cSpaceTrading::Get returns service", "0x00b3d3c0 cRelationshipManager::Get returns service", "0x00b3d420 cGameModeManager::Get returns service", "0x00e5c780 map lookup requires RE"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["binary globals/xrefs", "SDK symbols", "PKG-20 map characterization", "PKG-02 bootstrap", "decompile ten roots and freeze invalid-handle/caller contracts"]

**State machines:** ["root_unresolved -> named_getter -> typed_service_handle"]

**Events/messages:** ["singleton_get", "service_handle_use"]

**Data/assets:** ["Global service slots", "No persistent assets"]

**Serialization:** ["None established"]

**Engine interfaces:** ["Typed service locator", "Player identity", "Object registry", "World state", "ID map", "Event router"]

**Invariants:** ["Accessor bodies are not service implementations", "Raw globals are not modern API", "Lifetime/init are explicit"]

**Error/failure semantics:** ["Invalid/uninitialized handle unresolved", "Missing key vs null unresolved"]

**Initialization:** Init: characterize/publish handles

**Update/tick:** Tick: consumers request handles

**Shutdown/cleanup:** Shutdown: release after consumers stop

**Validation strategy:** ["decomp_differential", "not_yet_testable", "triage readiness", "xref TSV", "21-decompilation-coverage.json"]

**Known divergences:** ["OpenSpore injected services are not original singleton block", "No implementation from fan-in"]

**Unknowns:** ["Ten root identities", "Map type", "Initialization writers", "Side effects/lifetime"]

**Implementation status:** `BLOCKED_BY_ARCHITECTURE`. An open architecture blocker can change the package boundary or owner graph even though interim ports are safe.

## PKG-02-APP-LIFECYCLE — Application bootstrap and system lifecycle

**Package:** PKG-02-APP-LIFECYCLE

**Purpose:** Describe original bootstrap, AppSystem initialization, update, and shutdown without claiming complete reconstruction.

**Subsystem owner:** App bootstrap, AppSystem services, frame/update, and shutdown.

**Authoritative state:** ["Authoritative: cSporeApp flags, service publication, listener registration", "Runtime: AppSystem/mode/message/renderer/resource services", "Persistent: configuration candidates unresolved", "Invariant: boot control is not stage transition"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["cSporeApp: mHasInitialized +0x0c, mIsRunning +0x0d, timing +0x10/+0x14", "cAppSystem: InitPlugins, Init, Startup, Update +0x78, func7Ch +0x7c, PostUpdate +0x80, PreShutdown", "IAppSystem: service/update/shutdown interfaces"]

**Functions:** ["0x0067dcc0 IAppSystem::Get returns DAT_015fd890", "0x007e93d0 InitPlugins walks command/plugin setup", "0x007e67a0 Startup starts subsystems", "0x00f47b10 handles app update 0x01ee100a and stop 0x0153c326", "0x00f47930 measures/paces and calls update/func7Ch/PostUpdate"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["PE/app symbols", "Wine/display environment", "fresh wineserver", "positive boot", "human approval/lock gates"]

**State machines:** ["uninitialized -> initialized -> running -> stop_requested -> shutdown", "message_received -> delta_measured -> optional pacing -> updated -> post_updated"]

**Events/messages:** ["bootstrap_entry", "init_plugins", "init", "startup", "app_update 0x01ee100a", "stop 0x0153c326", "shutdown"]

**Data/assets:** ["PE/app configuration", "Service publication", "No game asset semantics"]

**Serialization:** ["Configuration/property boundary separate", "No autosave or whole-save claim"]

**Engine interfaces:** ["IAppHost", "IGameModeRegistry", "IMessageManager", "IResourceProvider", "IGameServices", "IPlatformHost"]

**Invariants:** ["mHasInitialized gates updates", "mIsRunning gates running", "Frame heartbeat is not fixed-step proof", "Historical startup cannot promote Cell"]

**Error/failure semantics:** ["Boot stall, clean exit, and stop distinct", "Failed init not running", "Pacing failure not fixed-step failure"]

**Initialization:** Init: entry -> InitPlugins -> Init -> Startup

**Update/tick:** Tick: app update -> frame -> callbacks -> PostUpdate

**Shutdown/cleanup:** Shutdown: stop -> PreShutdown -> teardown

**Validation strategy:** ["original_binary_oracle", "provenance_negative", "not_yet_testable", "main_menu probe", "historical JSONL", "tests/test_cell_trace.py"]

**Known divergences:** ["Cell executable is not AppSystem bootstrap", "SDL host is not original input", "Fixed simulation is not observed original pacing"]

**Unknowns:** ["Boot exit trigger", "Complete bootstrap order", "Menu-to-stage", "Global shutdown"]

**Implementation status:** `BLOCKED_BY_RUNTIME`. A host seam exists, but the original lifecycle, reachability, or observable behavior is not runtime-validated.

## PKG-03-RESOURCE-IO — Resource manager, DBPF/QFS I/O, and property substrate

**Package:** PKG-03-RESOURCE-IO

**Purpose:** Provide bounded clean-room content bytes and original resource/property boundary.

**Subsystem owner:** Resource manager, packed files, stream/record I/O, property substrate.

**Authoritative state:** ["Authoritative: ResourceKey, DBPF metadata/bytes, typed payloads, bounded property entries", "Runtime: registries/databases/factories/cache/handles", "Persistent: packages and property/config streams", "Invariant: handles/caches are not gameplay entities"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["ResourceKey: type/group/instance", "DatabasePackedFile: index/extents/holes/allocator", "PFIndexModifiable: index read/write", "RecordInfo: offset/sizes/flags/saved state", "PropertyList: local entries/parent/counter/Read/Write"]

**Functions:** ["0x008de530 cResourceManager::Initialize", "parseDbpfIndex/extractDbpfRecord/qfsDecompress", "PropertyList::Read/Write local typed entries with first-failure behavior"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["SPORE package bytes", "DBPF/QFS evidence", "PKG-04 codecs", "PKG-05 readers", "malformed fixtures", "menu trace", "property round-trip"]

**State machines:** ["uninitialized -> configured -> cache_miss -> cache_hit/unavailable -> disposed"]

**Events/messages:** ["package_lock", "index_read", "record_fetch", "property_load", "resource_cache_hit/miss"]

**Data/assets:** ["DBPF v3/QFS records", "ResourceKeys", "Property streams", "Read-only GOG package bytes"]

**Serialization:** ["DBPF/QFS verified bounded", "Property/class serializer framing unresolved"]

**Engine interfaces:** ["B1 IResourceProvider", "IContentStore", "IRecordCodec", "IStream", "IPropertyStore", "IConfigCodec"]

**Invariants:** ["Complete key required", "Extents bounded", "QFS/malformed explicit", "Local-first property lookup with bounded parent fallback"]

**Error/failure semantics:** ["Missing record/malformed index/bad extent/unsupported compression/property failure distinct", "Cache bypass/async unresolved"]

**Initialization:** Init: mount/index registries

**Update/tick:** Tick: fetch/decode/cache

**Shutdown/cleanup:** Shutdown: close/release

**Validation strategy:** ["deterministic_unit", "fixture_comparison", "asset_driven", "integration", "original_binary_oracle", "mini_package.dbpf", "tests/test_formats.py", "real_asset_test.cpp"]

**Known divergences:** ["B1 one-package provider is not original multi-package manager", "Typed readers are not general property persistence"]

**Unknowns:** ["Priority", "Directory semantics", "Cache eviction", "Async scheduling", "QFS call site", "Property wire format"]

**Implementation status:** `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`. A bounded clean-room seam can be implemented while explicitly retaining local unknowns and blocking original-compatibility claims.

## PKG-04-ASSET-GEOMETRY-TEXTURE — GMDL/RW4/raster geometry and texture decode

**Package:** PKG-04-ASSET-GEOMETRY-TEXTURE

**Purpose:** Decode bounded static geometry/model/texture/container formats into host values.

**Subsystem owner:** Asset/format decoding and host mesh/texture production.

**Authoritative state:** ["Authoritative: supported decoded fields/topology/mips", "Runtime: host mesh/texture handles", "Persistent: source records only", "Invariant: host output is not original RW/material/pixel behavior"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["GmdlModel: version/bounds/topology/material refs", "Mesh: vertices/indices/bounds/limitations", "RW4 manifest: sections/offsets/validation", "ImageRGBA: mip dimensions/RGBA8/provenance"]

**Functions:** ["parseGmdl/meshFromGmdl", "decodeRasterMips/decodeDxt5Mip", "parseRw4 structural walk without payload execution"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["PKG-03", "Package records", "Python oracles", "B2/B3 consumers", "malformed fixtures", "full differential", "unsupported versions explicit"]

**State machines:** ["record_selected -> validated -> decoded -> host_handle or unsupported/error"]

**Events/messages:** ["record_extracted", "gmdl_decoded", "mesh_built", "texture_decoded", "rw4_section_observed"]

**Data/assets:** ["GMDL v8", "RW4 envelope", "raster/DXT5", "Host Mesh/ImageRGBA"]

**Serialization:** ["Read-only static parse", "No writer/load round-trip"]

**Engine interfaces:** ["B2 IMeshSource", "IRenderer input", "IMaterialRegistry", "ITextureStore"]

**Invariants:** ["Bounds/index checks", "Unsupported versions/sections explicit", "Opaque trailers not complete RW", "RW internals stay behind seam"]

**Error/failure semantics:** ["Truncation/bounds/version/compression/source failures distinct", "Opaque payload is not execution success"]

**Initialization:** Init: mount/decoder tables

**Update/tick:** Tick: decode/publish immutable values

**Shutdown/cleanup:** Shutdown: release without source mutation

**Validation strategy:** ["deterministic_unit", "fixture_comparison", "asset_driven", "integration", "decomp_differential", "mini.gmdl", "mini_rw4.rw4", "test_formats.py", "test_textures.py", "test_rw4.py"]

**Known divergences:** ["Host mesh/texture is not full RenderWare", "GMDL v8 narrower than format family", "Vulkan pixels not original"]

**Unknowns:** ["GMDL v9", "RW4 material/animation", "Raster words 0x10/0x18", "Mip/sampler", "Pixel fidelity"]

**Implementation status:** `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`. A bounded clean-room seam can be implemented while explicitly retaining local unknowns and blocking original-compatibility claims.

## PKG-05-CELL-CONTENT — Cell content and resource record semantics

**Package:** PKG-05-CELL-CONTENT

**Purpose:** Decode direct Cell content records/references while separating static content from live gameplay and save state.

**Subsystem owner:** Cell static content/resource records and typed references.

**Authoritative state:** ["Authoritative: direct Cell layouts and hard references", "Runtime: lazy cCellDataReference handles", "Persistent: direct records only", "Invariant: direct record is not live Cell/GFX/save record"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["cCellCellResource TypeID 0xDFAD9F51, 796 bytes", "cCellGlobalsResource TypeID 0x2A3CE5B7, 276 bytes/69 fields", "cCellWorldResource TypeID 0x9B8E862F, 16+12N+24N", "cCellPopulateResource TypeID 0xDA141C1B, 16+76N", "cCellStructureResource TypeID 0x4B9EF6DC, 28+40N", "cCellLootTableResource TypeID 0xD92AF091, 36+28N", "cCellEffectMapResource TypeID 0x433FB70C, 8+28N"]

**Functions:** ["parseCellCellResource", "parseCellWorldResource", "parseCellPopulateResource", "parseCellStructureResource", "parseCellLootTableResource", "parseCellEffectMapResource", "0x00e82340 candidate is not merged with 0x00e82420 Create"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["PKG-03", "Cell packages", "SDK layouts", "PKG-04", "canonical manifest", "C++/Python differential", "negative reference fixtures", "alias adjudication"]

**State machines:** ["identity -> bounded bytes -> decode -> reference check -> publish", "unresolved reference -> loaded -> use-counted -> released"]

**Events/messages:** ["resource_decoded", "record_reference_checked", "resource_consumed_by_runtime"]

**Data/assets:** ["Twelve direct Cell TypeID records", "ResourceKeys", "World/populate/advect templates", "Cell package records"]

**Serialization:** ["Direct typed records", "No generic CellSerializer envelope", "Decode-only"]

**Engine interfaces:** ["IContentStore", "IRecordCodec", "IReferenceResolver", "IPresentationResourceCache"]

**Invariants:** ["TypeID/extent checked", "Hard references validated", "Markers are not live coordinates", "Direct records separate from serializable state"]

**Error/failure semantics:** ["Unknown TypeID/truncation/count/extent/reference explicit", "Soft references not promoted to placement"]

**Initialization:** Init: manifest/decode

**Update/tick:** Tick: lazy reference resolution

**Shutdown/cleanup:** Shutdown: release cache/handles

**Validation strategy:** ["deterministic_unit", "fixture_comparison", "asset_driven", "integration", "decomp_differential", "cell_* tests", "tools/spore/cellres/"]

**Known divergences:** ["Decoders do not execute world/AI/loot", "cCellSerializableData not a direct record", "GFX associations separate"]

**Unknowns:** ["Runtime use", "World placement", "Loot settlement", "Soft-ID selection", "0x00e82340/0x00e82420 alias"]

**Implementation status:** `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`. A bounded clean-room seam can be implemented while explicitly retaining local unknowns and blocking original-compatibility claims.

## PKG-06-CELL-STATE — Cell game state, pool, query, advect, and combat rules

**Package:** PKG-06-CELL-STATE

**Purpose:** Reconstruct selected pure Cell state/pool/query/advect/combat rules without claiming the complete live machine.

**Subsystem owner:** Simulator Cell runtime state and selected gameplay rules.

**Authoritative state:** ["Authoritative: static cCellGame/pool/object/query/combat transitions", "Runtime: cCellGame, pool, object, query, avatar, health, behavior", "Persistent: cCellSerializableData separate candidate", "Invariant: pure rules/CellSim are not original singleton runtime"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["cCellGame: pool +0x1c, queries +0x40fc/+0x4100, world +0x4114/+0x4118, avatar +0x411c, serializable +0x5190, lock +0x5158, update +0x515c, state +0x51e0", "cCellObjectData: 920 bytes, pool link, target/orientation/transform, model/resource, animation, health/GFX/scale/query", "cObjectPool: 4096 capacity, 920 stride", "cCellQueryEntry: position/size/next/index", "cAdvectEntry/ScaleDifference: bucket/strength/variance/period/ID"]

**Functions:** ["0x00e80ba0 cCellGame::Initialize", "0x00e74a20 CreateCellObject", "0x00e780a0 pool lifecycle/rebuild", "CellPool allocate/release", "CellQuery::queryNear", "getCurrentAdvectInfo/getNextAdvectID", "getScaleDifference/getDamage/shouldNotAttack"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["PKG-01", "PKG-05", "SDK layouts", "PKG-08", "root resolution", "pre/post state", "pool identity/exhaustion validation", "non-original fixture label"]

**State machines:** ["free -> allocated_live -> dying/despawning -> rebuild -> free", "attack gate -> health positive/zero/death/flee/chase", "world -> scale bucket -> current/next advect"]

**Events/messages:** ["cell_game_initialized", "pool_allocated", "cell_created", "near_query", "attack_gate_decided", "cell_damage_resolved"]

**Data/assets:** ["PKG-05 Cell records", "Pooled cCellObjectData", "Query entries", "World/advect", "Health/behavior"]

**Serialization:** ["cCellSerializableData/serializer separate", "No live-object save claim"]

**Engine interfaces:** ["ICellGameState", "IEntityPool", "ICellQuery", "IAdvectState", "ICombatRules", "IAnimationIntent"]

**Invariants:** ["Pool index distinct from pointer", "Capacity 4096", "Query links stable indices", "Health clamps zero"]

**Error/failure semantics:** ["Pool exhaustion invariant candidate", "Missing avatar/query invalid", "Invalid scale/advect explicit", "Omitted side effects not modeled"]

**Initialization:** Init: reset/pools/queries

**Update/tick:** Tick: create/query/move/damage/advect

**Shutdown/cleanup:** Shutdown: release/reset stage

**Validation strategy:** ["deterministic_unit", "fixture_comparison", "decomp_differential", "original_binary_oracle", "sim tests", "generated fixtures labeled non-original"]

**Known divergences:** ["CellSim not original cCellGame", "Entity not byte-compatible", "No original timing claim"]

**Unknowns:** ["Complete pool effects", "Free-list sentinel", "AI/effect/query integration", "Runtime gates", "Live-object save"]

**Implementation status:** `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`. A bounded clean-room seam can be implemented while explicitly retaining local unknowns and blocking original-compatibility claims.

## PKG-07-CELL-MOVEMENT — Cell movement and mouse-steering replacement

**Package:** PKG-07-CELL-MOVEMENT

**Purpose:** Reconstruct camera-ray/plane to Cell target/orientation/moving state with a bounded hook seam.

**Subsystem owner:** Cell movement rule and read-only camera/input boundary.

**Authoritative state:** ["Authoritative: target, orientation, moving flag after guards", "Runtime: avatar/lock gates, object target/current transform, camera ray", "Persistent: none", "Invariant: renderer does not own result"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["sCellGame: avatar +0x411c, lock +0x5158, moving +0x5190+0xe0", "cCellObjectData: target +0x08, orientation +0x14", "MovementPlane: normal (0,0,1), load point (0,0,0), runtime point unresolved", "CameraState/Ray: origin/direction/pointer/gates"]

**Functions:** ["0x00e5b790 MovePlayerToMousePosition: lock/player/camera guards, ray-plane, target/orientation/moving writes", "0x00e5b2e0 per-frame UI/plane target update", "0x007c4900 camera/light source candidate", "0x00b721d0 player lookup candidate", "reference and replacement functions: evidence/regression only"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["PKG-01", "PKG-06", "PKG-08", "camera/UI boundary", "M0", "M1", "M2", "C-MOUSE", "C-ABI"]

**State machines:** ["input -> gates -> player -> ray-plane -> target mutation/no-op"]

**Events/messages:** ["mouse_move", "key_down", "movement_target_written", "moving_flag_set", "orientation_written"]

**Data/assets:** ["Camera/pointer state", "Movement plane", "Player identity", "No persistent movement data"]

**Serialization:** ["None"]

**Engine interfaces:** ["ICameraRayProvider", "ICameraService", "IPlayerMovement", "IInputRouter", "IEntityPool"]

**Invariants:** ["Guard failure no-op", "Distance/denominator checked", "Pool index resolves player", "Stack balanced", "Decomp 64/64 not runtime proof"]

**Error/failure semantics:** ["Lock/camera/UI/invalid player/parallel plane/negative distance no-op", "Omitted callees separate", "Missing real install fails validation"]

**Initialization:** Init: pin target/plane/camera/resolver

**Update/tick:** Tick: consume input/camera and mutate target

**Shutdown/cleanup:** Shutdown: restore hook/release frame state

**Validation strategy:** ["decomp_differential", "replacement_hook", "deterministic_unit", "original_binary_oracle", "diff_test.cpp", "cell_movement probe", "synthetic hook"]

**Known divergences:** ["64/64 is decomp-only", "Hook not installed", "Host camera/input approximate"]

**Unknowns:** ["Live behavior", "Runtime plane", "Pool pointer identity", "Gate meanings", "Omitted effects"]

**Implementation status:** `BLOCKED_BY_RUNTIME`. A host seam exists, but the original lifecycle, reachability, or observable behavior is not runtime-validated.

## PKG-08-CELL-MODE — Cell mode lifecycle and input routing

**Package:** PKG-08-CELL-MODE

**Purpose:** Define original cCellModeStrategy lifecycle and clean-room IGameMode boundary without GFX/UI/movement ownership.

**Subsystem owner:** App mode registry, Cell mode lifecycle, and mode input routing.

**Authoritative state:** ["Authoritative: active index, lifecycle flags, input callbacks, mode handles", "Runtime: App cGameModeManager, cCellModeStrategy, input callbacks, Cell services", "Persistent: none; exit does not imply save", "Invariant: IGameMode is host seam"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["cGameModeManager: ModeEntry +0x14, active +0x28, init +0x10", "cCellModeStrategy: 27-slot candidate, lifecycle, input, update", "IGameMode: lifecycle/input/update host interface"]

**Functions:** ["0x007d8d40 SetActiveModeAt boundary", "0x00e81cf0 Initialize", "0x00e552f0 OnEnter", "0x00e80980 Update", "0x00e7fc00 OnExit", "0x00e81f30 Dispose", "0x00e51010 OnMouseMove"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["PKG-01", "PKG-02", "PKG-18", "M1", "SetActiveModeAt correlation", "message/input trace"]

**State machines:** ["uninitialized -> initialized -> active -> exited -> disposed", "old mode OnExit -> active index/message -> new OnEnter/message"]

**Events/messages:** ["mode_initialize", "mode_enter", "input_event", "mode_update", "mode_exit", "mode_dispose"]

**Data/assets:** ["Mode IDs/names/entries", "No persistent mode data"]

**Serialization:** ["None established", "No mode persistence claim"]

**Engine interfaces:** ["IGameMode", "IGameModeRegistry", "IInputRouter", "IMessageManager", "IAppHost"]

**Invariants:** ["Distinct valid index exits old before entering new", "Same index no-op", "Invalid index rejected", "Dispose after exit", "Input mode-owned"]

**Error/failure semantics:** ["Invalid request rejected", "Partial init not display-ready", "Entry/dispose failures incomplete", "Input consume/default unresolved"]

**Initialization:** Init: register/initialize

**Update/tick:** Tick: input/update

**Shutdown/cleanup:** Shutdown: exit/stop/dispose

**Validation strategy:** ["deterministic_unit", "decomp_differential", "integration", "original_binary_oracle", "cellmode/input tests", "cell/menu probes"]

**Known divergences:** ["Current mode is host shell", "IGameMode omits original slots/metadata", "SDL bypasses callbacks"]

**Unknowns:** ["Other modes", "Input timing", "Queue timing", "Registration/camera ownership"]

**Implementation status:** `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`. A bounded clean-room seam can be implemented while explicitly retaining local unknowns and blocking original-compatibility claims.

## PKG-09-CELL-PRESENTATION — Cell GFX, HUD, scene assembly, and renderer boundary

**Package:** PKG-09-CELL-PRESENTATION

**Purpose:** Compose CellGFX, HUD, scene entities, and renderer submission without claiming original pixels or placement.

**Subsystem owner:** Mode-owned Cell presentation stage and host renderer boundary.

**Authoritative state:** ["Authoritative: stable Cell/presentation associations, world/layer membership, preload readiness, display/HUD", "Runtime: cCellGFX, cCellUI, GFX/model/effect/texture handles, scene", "Persistent: none", "Invariant: presentation does not own gameplay/save state"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["cCellGFX: worlds/layers/preloads/effects/display", "CellGFXObjectData: cell/model/creature/effect links", "cCellUI/Rollover: vectors/constants/zoom/selection/0.5s timer", "SceneEntity: ID/transform/model/material/visibility", "EntityPresentationRegistry: EntityId/PresentationHandle/rebuild/detach"]

**Functions:** ["0x00e5dba0 cCellGFX::Initialize", "0x00e666f0 PreloadResources", "0x00e663b0 PreloadCellResource", "0x00e665c0 PreloadPopulateResource", "0x00e55120 StartDisplay", "0x00e54270 cCellUI::Load", "0x00e62340 ShowHealthRollover"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["PKG-03", "PKG-04", "PKG-05", "PKG-08", "placement fixture", "M0/M1", "matched render capture", "material/light/pixel oracle"]

**State machines:** ["uninitialized -> preloading -> ready -> display_started -> stopped -> disposed", "detached -> attached -> rebuildable -> released"]

**Events/messages:** ["gfx_initialized", "resource_preloaded", "display_started", "hud_loaded", "health_rollover_shown", "frame_drawn"]

**Data/assets:** ["Cell/Populate/effect/model/material/texture keys", "Scene/world/layer identities", "Decoded packaged assets"]

**Serialization:** ["No presentation serialization", "Stable identity/lifecycle only"]

**Engine interfaces:** ["B1/B2/B3", "IContentStore", "IPresentationResourceCache", "ISceneStage", "IEntityPresentationRegistry", "IEntityView", "IMaterialRegistry", "ITextureStore", "IEffectPresenter", "IRenderQueue", "IRenderer"]

**Invariants:** ["EntityId stable across rebuild", "Preload precedes display", "Handles release before stage", "HUD cannot mutate health", "Renderer not gameplay"]

**Error/failure semantics:** ["Missing model/GFX no-op presentation", "Missing/unsupported asset explicit", "Partial preload not ready", "Missing view non-fatal"]

**Initialization:** Init: create stage/world/layers

**Update/tick:** Tick: preload/views/effects/draws

**Shutdown/cleanup:** Shutdown: stop/detach/release

**Validation strategy:** ["deterministic_unit", "fixture_comparison", "asset_driven", "integration", "original_binary_oracle", "cellgfx/cellui/scene tests", "scene.json", "test_cellstage.py"]

**Known divergences:** ["Vulkan pixels/fixed lighting not original", "Scene positions fixture choices", "No original material/animation/pose execution"]

**Unknowns:** ["Placement", "Preload order/timeout", "Material slots", "HUD timing/drawing", "Pose upload", "GPU retirement"]

**Implementation status:** `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`. A bounded clean-room seam can be implemented while explicitly retaining local unknowns and blocking original-compatibility claims.

## PKG-10-EDITOR-DISPATCH — Editor and message dispatch

**Package:** PKG-10-EDITOR-DISPATCH

**Purpose:** Own editor lifecycle/input/message dispatch and original menu-to-stage message route.

**Subsystem owner:** Editors::cEditor, editor mode/history/tool dispatch, and message/input handoff.

**Authoritative state:** ["Authoritative: editor active/mode/history/manipulator/tool/model/message state", "Runtime: cEditor, EditorModel, history, tools, listeners, input", "Persistent: authored assets separate; history survival unknown", "Invariant: pump/screenshot/frame cannot establish stage transition"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["cEditor: interfaces, active +0x2b0, mode +0x31c, history +0x188, manipulator +0x148", "EditorModel: ResourceKey/rigblocks/names/colors/bounds/vtable alternatives", "EditorStateEditHistory: paired records/index/bounds", "cEditorAnimWorld: creature map/events/controllers"]

**Functions:** ["0x00584300 Initialize", "0x00588570 OnMouseDown", "0x0058ac10 OnKeyDown", "0x0058be50 Update", "0x00591fa0 HandleMessage", "0x00586410 CommitEditHistory", "0x00848210 MessagePump::PeekDispatch"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["PKG-02", "PKG-03", "PKG-18", "renderer layer", "approved input", "M0", "correlated input/message/resource/frame events", "message catalog", "typed cEditor/tool layouts"]

**State machines:** ["editor uninitialized -> initialized -> entering -> active -> exited -> disposed", "idle -> hover -> drag/selection -> committed -> undo/redo", "pump -> message queued -> dispatch -> resource/mode request -> stage observed"]

**Events/messages:** ["editor_update", "input_event", "message_pump", "editor_mode_enter/exit", "edit_commit/undo/redo", "resource_transition"]

**Data/assets:** ["Editor model/rigblock/resource records", "Message IDs/payloads where mapped", "Editor resources"]

**Serialization:** ["Editor asset/property save separate from profile persistence", "File grammar/history survival unresolved"]

**Engine interfaces:** ["IEventLoop", "IStageEventRouter", "IMessageManager", "IInputRouter", "IEditorView", "IAnimationEventSink"]

**Invariants:** ["Invalid/equal mode no-op", "History bounded", "Old mode before new", "Payloads not inferred from constants", "Tool/editor separated"]

**Error/failure semantics:** ["Invalid mode/history/tool bounded no-op/failure", "Missing renderer/model partial setup", "Message priority/tie/consume unknown"]

**Initialization:** Init: services/listeners

**Update/tick:** Tick: input/message/editor/actor/animation

**Shutdown/cleanup:** Shutdown: release selection/manipulator/model/skin/play mode/animation/world

**Validation strategy:** ["deterministic_unit", "decomp_differential", "integration", "original_binary_oracle", "menu_walk", "menu_transition probe", "historical startup"]

**Known divergences:** ["No original editor/UTFWin in current tree", "SDL bypasses cEditor", "Current scene/animation shell not original editor"]

**Unknowns:** ["Message IDs/payloads", "Priority/tie", "Tool/actor semantics", "Menu-to-stage causality", "History save"]

**Implementation status:** `BLOCKED_BY_RUNTIME`. A host seam exists, but the original lifecycle, reachability, or observable behavior is not runtime-validated.

## PKG-11-SIM-CORE — Simulator core services, tools, and missions

**Package:** PKG-11-SIM-CORE

**Purpose:** Characterize Simulator manager composition, tool strategies, missions, and support services; proposed split required before implementation.

**Subsystem owner:** Simulator composition, tool registry/strategies, and mission lifecycle.

**Authoritative state:** ["Authoritative: manager ownership, tool state, mission state where direct", "Runtime: cSimulatorSystem, tools, missions, communication/services", "Persistent: mission/inventory/property/cGameData candidates", "Invariant: managers/tools/missions/Cell are distinct"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["cSimulatorSystem: strategy vector +0x5c, UI graphics +0x20", "cToolManager/cToolStrategy: tool map +0x38, 18-slot contract", "cMission: ID/time/state/owner/target/rewards/costs/unlocks/property/comm", "cMissionManager: tracked/recent/tutorial/config/gaps", "cGameData: ID/definition/owner/political structural family"]

**Functions:** ["0x00b72370 cObjectPool_::DeleteObject", "0x00c8b6b0 IsNotStarOrBinaryStar", "0x01052f90 cDefaultAoETool::OnMouseDown", "0x01053790 cToolStrategy::OnSelect", "0x01053db0 cDefaultBeamTool::func4Ch", "Mission state SDK contract with unresolved reward order"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["PKG-01", "PKG-02", "PKG-03", "PKG-10", "manager roots", "tool registry", "mission callbacks/persistence", "stage trace", "split core/tools-missions"]

**State machines:** ["uncomposed -> registered -> active -> updated -> disposed", "unselected -> selected -> aiming -> firing -> hit -> updated", "unaccepted -> accepted -> active -> completed/finished or failed/aborted/rejected"]

**Events/messages:** ["tool_input", "tool_selected", "object_deleted", "mission_update"]

**Data/assets:** ["Tool resources", "Mission/inventory records", "Property lists", "Game resources"]

**Serialization:** ["ISimulatorSerializable/PropertyList/ClassSerializer", "Mission/inventory field coverage and remapping unresolved"]

**Engine interfaces:** ["IGameServices", "IBehavior", "IToolRegistry", "IMissionService", "IPropertyStore", "IEventRouter"]

**Invariants:** ["Typed service lifetime", "Shared tool strategy contract", "Mission callback order not assumed", "cGameData prefix not universal inheritance"]

**Error/failure semantics:** ["Invalid tool behavior variant-specific", "Mission failure routes incomplete", "Unknown side effects not promoted"]

**Initialization:** Init: managers/register strategies

**Update/tick:** Tick: services/tools/missions in evidenced order

**Shutdown/cleanup:** Shutdown: unregister/release/persist explicit data

**Validation strategy:** ["decomp_differential", "deterministic_unit", "original_binary_oracle", "triage queue", "simulator-core state JSON", "split/serialization/trace gates"]

**Known divergences:** ["No broad OpenSpore implementation", "CellSim not Simulator core", "SDK vtable families not unique classes"]

**Unknowns:** ["Manager order", "Tool ownership/events", "Mission rewards", "Cross-stage handoff", "Serialization coverage"]

**Implementation status:** `BLOCKED_BY_RE`. The package still needs a bounded static contract, owner, or function-family characterization before implementation can be authoritative.

## PKG-12-SIM-SPACE — Simulator Space stage, stars, planets, trade, and terraforming

**Package:** PKG-12-SIM-SPACE

**Purpose:** Characterize Space context, star/planet records, trade, empire economy, terraforming, and Space-to-terrain handoff.

**Subsystem owner:** Space stage and star/planet/trade/empire records.

**Authoritative state:** ["Authoritative: SpacePlayerData, star/planet/trade/relationship state where fields confirmed", "Runtime: StarManager, Trading, SolarSystem, PlanetModel, empire/session", "Persistent: StarRecord, PlanetRecord, Empire, Mission, Inventory, trade routes", "Invariant: generated data not terrain; trade not Cell"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["SpacePlayerData: active planet/star/context/player ID/empire cache/colonies", "cStarManager: grids/starter/saved/empire homes/relationship/trade/databases/collectables", "cStarRecord: version/time/position/type/empire/species/planets/count", "cPlanetRecord: orbit/scores/species/commodity/civ/tribe/tech/terrain/spice with offsets conflict", "cEmpire: political/money/relationships/home/culture/keys", "cSpaceTrading: spices/NPC/rare maps/groups/commodities", "cSolarSystem/cPlanetModel/cTerrainSphere: live surface/graphics"]

**Functions:** ["0x00b3d4d0 cSpaceTrading::Get", "0x00c8b6b0 IsNotStarOrBinaryStar", "0x01021960 context setter", "0x00bb4af0 regeneration check", "0x00bb4100 planet record generation", "0x00bb5b50 RecordToPlanet", "Trade/terraforming requests/failures unresolved"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["PKG-01", "PKG-03", "PKG-11", "PKG-14", "Space VAs/vtables", "Space trace", "service roots", "persistence/defaults", "Space-terrain handoff"]

**State machines:** ["none -> planet -> solar_system -> galaxy", "star_not_generated -> counted -> materialized -> solar_loaded -> graphics_requested/destroyed", "trade request -> offer -> accepted/rejected -> inventory/value or failure", "terraform idle -> requested -> active -> completed/failed"]

**Events/messages:** ["space_stage_enter", "space_context_request", "star_planets_generated", "planet_surface_transition", "trade_action", "space_rare_discovered 0x06779f04"]

**Data/assets:** ["Star/planet records", "Species/commodity/civ/tribe", "Trade/inventory/rare", "Terrain/spice keys", "stars.db/stars.db.tmp"]

**Serialization:** ["ISimulatorSerializable/PropertyList/star database", "Database replacement is not general save transaction"]

**Engine interfaces:** ["IGameServices", "IContentStore", "IWorldState", "IStarPlanetRepository", "ITradeService", "IPlanetSurfaceTransition", "ISceneStage"]

**Invariants:** ["Count/vector not interchangeable", "Context explicit", "Political-ID relationships", "Currencies not collapsed", "Handoff explicit"]

**Error/failure semantics:** ["Missing/invalid records unresolved", "Database rollback unknown", "Rare notification only on transition to found"]

**Initialization:** Init: services/databases/context/session

**Update/tick:** Tick: navigation/generation/trade/mission/relationship/presentation

**Shutdown/cleanup:** Shutdown: persist characterized records/release session/graphics/restore mode

**Validation strategy:** ["decomp_differential", "asset_driven", "original_binary_oracle", "Space cluster", "state-machine world/empire JSON", "Space trace/round-trip/failure gates"]

**Known divergences:** ["No current Space implementation", "Cell resources not economy", "Current render not Space graphics"]

**Unknowns:** ["Stage entry", "Generation formulas", "Trade pricing/atomicity", "Terraforming", "Rewards", "Serialization", "Surface handoff"]

**Implementation status:** `BLOCKED_BY_ARCHITECTURE`. An open architecture blocker can change the package boundary or owner graph even though interim ports are safe.

## PKG-13-SIM-CREATURE-TRIBECIV — Creature, tribe, city, relationship, and civilization stage

**Package:** PKG-13-SIM-CREATURE-TRIBECIV

**Purpose:** Characterize creature/city/tribe/civilization state and relationship/progression boundaries separately from Cell and Space.

**Subsystem owner:** Creature-stage entities, tribe/city planning, civilization relationships, progression support.

**Authoritative state:** ["Authoritative: confirmed progression/relationship flags and static tribe/city fields", "Runtime: CreatureGameData/Base, Tribe/Planner, City/Building, Relationship/Comm/Collectable", "Persistent: cGameData/mission/inventory/property/collectable candidates", "Invariant: evolution/growMeter/money/relationship/rewards are distinct"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["cCreatureGameData: brain +0x00, ability +0x24, evolution +0x28, abilities, glide", "cCreatureBase/Animal/Citizen: shared prefix only", "cTribe/Planner/Plan: political ID, population/food, position, plan state/check/food, members/tools", "cCity/Building/LayoutSlot: ownership/layout/placement/processing", "cRelationshipManager/Data: political map, value/flags/events, war bit 0/alliance bit 1"]

**Functions:** ["0x00d2e480 SetEvolutionPoints", "0x00d2e8a0 AddEvolutionPoints", "0x00d065a0 DeclareWar", "0x00d06920 DeclareAlliance", "0x00d01e30 BreakAlliance", "cMission::SetState SDK contract"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["PKG-01", "PKG-03", "PKG-11", "PKG-12", "PKG-14", "creature/tribe/city VAs/vtables", "stage trace", "planner/growth bodies", "relationship owner"]

**State machines:** ["attack/social/same", "unchanged/increased/capped", "absent/neutral/allied/war", "tribe waiting/check/food/requirements/executing"]

**Events/messages:** ["ability_mode_change", "creature_evolution_points_added", "relationship_war_peace_alliance", "player_empire_allied 0x04445d43", "lost_alliance 0x04445d44", "tribe_city_update"]

**Data/assets:** ["Creature data/rigblocks", "Tribe/city records", "Collectables", "Relationships", "Species/keys"]

**Serialization:** ["ISimulatorSerializable/PropertyList/mission/collectables", "Cell/cross-stage sync unresolved"]

**Engine interfaces:** ["IGameServices", "IBehavior", "IRelationshipService", "IProgressionService", "IInventory", "IContentStore", "IEventRouter"]

**Invariants:** ["Ability bounded Attack/Social", "Evolution cap not level transition", "Political-ID flags", "Relationship score not money/progression", "Plan type not state enum"]

**Error/failure semantics:** ["Out-of-domain ability not rejected by setter", "Relationship guards partial", "Planner failures unresolved", "Payloads not inferred from IDs"]

**Initialization:** Init: services/stage data

**Update/tick:** Tick: progression/relationships/planners/cities/comm/presentation

**Shutdown/cleanup:** Shutdown: persist characterized/release live entities

**Validation strategy:** ["decomp_differential", "deterministic_unit", "original_binary_oracle", "triage cluster/queue", "Track F state/events", "type families", "stage/planner/round-trip gates"]

**Known divergences:** ["growMeter not evolution points", "No current creature/tribe/city", "Prefix not proven inheritance"]

**Unknowns:** ["Stage entry", "Planner/herd/growth", "Mission/economy coupling", "Payloads", "Cross-stage save"]

**Implementation status:** `BLOCKED_BY_RE`. The package still needs a bounded static contract, owner, or function-family characterization before implementation can be authoritative.

## PKG-14-TERRAIN-WORLD — Terrain, planet surface, and world rendering

**Package:** PKG-14-TERRAIN-WORLD

**Purpose:** Characterize terrain/planet surface and world rendering separately from generated planet data and gameplay state.

**Subsystem owner:** Terrain/planet surface runtime and renderer-facing presentation.

**Authoritative state:** ["Authoritative: terrain surface/quad/weather/render state where static", "Runtime: PlanetModel, TerrainSphere, quads, weather, graphics, edit state", "Persistent: generated planet/terrain key separate; live edits not save", "Invariant: rendering is not generation or gameplay"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["cPlanetModel: active binding/surface/graphics handoff", "cTerrainSphere: structural interfaces/surface/quad/weather/vtable conflict", "Quad: terrain surface/draw/material/texture", "TerrainModification: live edit/dirty/footprint/commit unknown"]

**Functions:** ["cTerrainSphere Land/Atmosphere/Decals static anchors", "Quad::Draw terrain submission", "cPlanetModel surface handoff binds generated record to terrain"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["PKG-04", "PKG-12", "graphics boundary", "terrain VAs", "Space trace", "matched frame", "ITerrain slot adjudication"]

**State machines:** ["raw phase/countdown/guard/terminal request", "planet_bound -> surface_loading -> graphics_attached -> active -> detached -> disposed"]

**Events/messages:** ["atmosphere_update", "planet_surface_transition", "terrain_draw", "terrain_edit_dirty"]

**Data/assets:** ["Planet/terrain keys", "Terrain/weather/atmosphere", "Terrain packages"]

**Serialization:** ["Planet record/property boundary", "Live terrain persistence unresolved"]

**Engine interfaces:** ["ISceneStage", "IRenderer", "IMaterialRegistry", "ITextureStore", "IWorldState", "IPlanetSurfaceTransition"]

**Invariants:** ["Surface rendering does not redefine generated data", "Terrain graphics do not own gameplay", "ITerrain/interface/table counts separate", "World flags remain raw until owner identified"]

**Error/failure semantics:** ["Missing terrain/model/material presentation failure", "Surface attach/load paths unresolved", "No original pixel claim"]

**Initialization:** Init: bind planet/terrain/create graphics

**Update/tick:** Tick: surface/weather/terrain/pass submission

**Shutdown/cleanup:** Shutdown: detach/destroy graphics/restore mode

**Validation strategy:** ["asset_driven", "integration", "original_binary_oracle", "render-boundary studies", "triage terrain cluster", "matched frame/Space trace"]

**Known divergences:** ["No current terrain implementation", "Current renderer not original terrain/RW", "Data/presentation split"]

**Unknowns:** ["Transition owner", "Terrain machine", "Weather", "Placement", "Material/light/pixels", "Persistence"]

**Implementation status:** `BLOCKED_BY_RE`. The package still needs a bounded static contract, owner, or function-family characterization before implementation can be authoritative.

## PKG-15-EDITOR-SUPPORT — Palettes, Skinner, and editor support assets

**Package:** PKG-15-EDITOR-SUPPORT

**Purpose:** Characterize palette/viewer/texture-paint support without merging into editor command or gameplay semantics.

**Subsystem owner:** Palettes, AdvancedItemViewer, Skinner texture-paint, editor support models.

**Authoritative state:** ["Authoritative: direct palette/viewer/support state only", "Runtime: pages/categories/viewer/painter/model handles", "Persistent: authored resources separate", "Invariant: support operations need producer/consumer path"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["PalettePage: identity/load/category", "AdvancedItemViewer: vtable/item/page/category/draw", "cSkinnerTexturePainter: paint/start/end", "EditorModel: ResourceKey/rigblocks/names/colors/bounds"]

**Functions:** ["0x004ae250 EditorModel::SetColor", "0x005c8bc0 PalettePage::Load", "0x005f4750 AdvancedItemViewer::func40h", "cSkinnerTexturePainter PaintRegion/StartRender/EndRender"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["PKG-03", "PKG-04", "PKG-10", "renderer/editor boundary", "support VAs/vtables", "editor/graphics dependencies"]

**State machines:** ["unloaded -> loaded -> category_selected -> viewer_updated"]

**Events/messages:** ["editor_model_color_set", "palette_loaded", "texture_paint_start_end"]

**Data/assets:** ["Palette pages", "Viewer item/category", "Texture-paint resources", "Editor resources"]

**Serialization:** ["Support/resource formats not established", "No round-trip"]

**Engine interfaces:** ["IEditorView", "IRenderer", "IContentStore", "IMaterialRegistry", "ITextureStore"]

**Invariants:** ["Palette separate from editor mode", "Viewer/paint cannot mutate gameplay", "Static readiness not runtime"]

**Error/failure semantics:** ["Missing palette/resource and viewer/paint failures unresolved", "Ownership required before authority"]

**Initialization:** Init: load support/init viewer/palette

**Update/tick:** Tick: update viewer/paint

**Shutdown/cleanup:** Shutdown: release support handles

**Validation strategy:** ["deterministic_unit", "fixture_comparison", "decomp_differential", "not_yet_testable", "Palette/EditorModel queue rows", "AdvancedItemViewer evidence"]

**Known divergences:** ["No original palette/viewer/paint implementation", "Names do not prove command ownership"]

**Unknowns:** ["Viewer lifecycle", "Paint state", "Categories", "Runtime order"]

**Implementation status:** `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`. A bounded clean-room seam can be implemented while explicitly retaining local unknowns and blocking original-compatibility claims.

## PKG-16-SPOREPEDIA-ONLINE — Sporepedia asset metadata and online boundary

**Package:** PKG-16-SPOREPEDIA-ONLINE

**Purpose:** Characterize local Sporepedia metadata while treating online/Pollinator behavior as a network-disabled boundary.

**Subsystem owner:** Sporepedia local metadata and future online service boundary.

**Authoritative state:** ["Authoritative: local asset ID/name/editability metadata", "Runtime: cSPAssetDataOTDB and local request/response", "Persistent: none established", "Invariant: local predicate is not online request/service"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["cSPAssetDataOTDB: ID/name/editability/author/tags/time/local-online", "Request/response: identity/network lifecycle unresolved"]

**Functions:** ["0x00641400 IsEditable", "0x00641770 HasName", "0x006417c0 GetAssetID", "0x00641460/0x006417b0 asset virtuals unresolved"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["PKG-03", "PKG-18", "network blocked/faked", "caller/event characterization", "local fixture", "no-network contract"]

**State machines:** ["asset_unavailable -> loaded -> queried -> result", "online service not_initialized -> request -> response/failure unresolved"]

**Events/messages:** ["asset_metadata_query", "editability_result", "online_request"]

**Data/assets:** ["Local asset metadata", "No network assets"]

**Serialization:** ["Asset metadata/online payload unresolved", "No round-trip"]

**Engine interfaces:** ["IContentStore", "IAssetMetadata", "IStubbedOnlineService"]

**Invariants:** ["Local metadata does not imply network", "Unknown virtuals not named API", "Network remains stubbed"]

**Error/failure semantics:** ["Missing local asset/unsupported virtual distinct", "Network failure not gameplay reconstruction"]

**Initialization:** Init: metadata or no-network stub

**Update/tick:** Tick: local metadata only

**Shutdown/cleanup:** Shutdown: release local/stub state

**Validation strategy:** ["deterministic_unit", "fixture_comparison", "decomp_differential", "not_yet_testable", "Sporepedia queue rows", "no-network negative"]

**Known divergences:** ["No current Sporepedia implementation", "Local predicates not online client", "Pollinator non-goal"]

**Unknowns:** ["Caller order", "Full asset semantics", "Request/response", "Online errors"]

**Implementation status:** `BLOCKED_BY_RE`. The package still needs a bounded static contract, owner, or function-family characterization before implementation can be authoritative.

## PKG-17-ANIMATION-SWARM — Cell animation and Swarm/creature animation boundary

**Package:** PKG-17-ANIMATION-SWARM

**Purpose:** Separate gameplay-owned Cell animation intent from pose evaluation, Swarm effects, and unresolved animation implementation.

**Subsystem owner:** Cell animation state and animation/effect boundary; Swarm unresolved.

**Authoritative state:** ["Authoritative: Cell clip/blend state when direct", "Runtime: cCellObjectData animation, manager/world, pose/effect instances", "Persistent: none established", "Invariant: intent gameplay; skeleton/pose/particles backend"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["cCellObjectData: current animation +0x1b0, blend +0x1b4/+0x1b8, GFX +0x248", "cCellAnimDefinition name-level", "IAnimationController: current/target clip/blend/loop/time/phase", "IEffectPresenter: definition/instance/transform/lifecycle", "Swarm animation/effect state unresolved"]

**Functions:** ["0x00e6d200 PlayAnimation", "0x00e63560 LoadEffectMap", "0x00e66840 InstanceEffectOnCell", "CellAnim host mapping only", "Swarm functions unresolved"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["PKG-05", "PKG-09", "render/material boundary", "event source", "event-to-animation trace", "event-to-pose trace", "Swarm identity", "pose policy"]

**State machines:** ["detached -> clip_active -> transition -> complete/interrupted", "undefined -> created -> running -> paused/hidden -> stopped -> released", "Swarm unidentified"]

**Events/messages:** ["animation_event", "animation_played", "effect_instance", "swarm_animation_event"]

**Data/assets:** ["Cell animation/effect definitions", "RW4 animation/skeleton static sections", "Cell/RW4 resources"]

**Serialization:** ["Asset codecs bounded", "Pose persistence not established"]

**Engine interfaces:** ["IAnimationService", "IAnimationController", "IAnimationWorld", "IPoseEvaluator", "IEffectPresenter", "IEntityView"]

**Invariants:** ["Missing model/GFX no-op", "Intent before visible pose", "Effect subordinate to entity/stage", "RW internals not gameplay"]

**Error/failure semantics:** ["Missing model/GFX/effect/invalid clip/pose failure distinct", "Event source/callback failure unknown", "Helper tests do not prove renderer integration"]

**Initialization:** Init: animation service/world/clip

**Update/tick:** Tick: intent/update/snapshot/submit

**Shutdown/cleanup:** Shutdown: stop effects/release animation/pose/detach

**Validation strategy:** ["deterministic_unit", "decomp_differential", "integration", "original_binary_oracle", "cellanim_test", "effectmap_test", "event-to-pose/Swarm gates"]

**Known divergences:** ["CellAnim not wired to cell_stage", "No skeleton/pose upload", "Swarm unresolved"]

**Unknowns:** ["Event producer", "Blend completion", "Pose order", "Vehicle coupling", "Swarm ownership"]

**Implementation status:** `IMPLEMENTABLE_WITH_LOCAL_UNKNOWN`. A bounded clean-room seam can be implemented while explicitly retaining local unknowns and blocking original-compatibility claims.

## PKG-18-UI-SCRIPTING — UTFWin and scripting/configuration infrastructure

**Package:** PKG-18-UI-SCRIPTING

**Purpose:** Keep UTFWin/UI and ArgScript/config parsing as replaceable infrastructure and observation boundaries.

**Subsystem owner:** UTFWin window/proc/message infrastructure and ArgScript parser/configuration content.

**Authoritative state:** ["Authoritative: window/proc/message structure and parser state where direct", "Runtime: UTFWin hierarchy/routing, script scopes, config/property", "Persistent: config/script files separate", "Invariant: UI/script/editor/gameplay records distinct"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["UTFWinObject: allocator/hierarchy/duplicate 21-slot bases", "Window: parent/children, WinProc +0x64, area/cursor/state/caption/font", "FormatParser: definitions/variables/blocks/scope", "pdtk widget: command/cursor/selection/focus/layout"]

**Functions:** ["0x00848210 MessagePump::PeekDispatch", "0x00960250 Window::SendMsg", "FormatParser ParseFloat/ParseUInt/SetFlag/CreateDefinitionSafe", "EditorNamePanel button-select bridge"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["PKG-02", "PKG-03", "PKG-10", "approved fixed input", "M0", "stage/message/resource trace", "pdtk grammar", "message catalog"]

**State machines:** ["os_event -> window_message -> proc_filter -> handler -> consumed/bubbled", "uninitialized -> scope_open -> nested -> closed -> disposed", "ui_event -> message -> mode request -> stage unknown"]

**Events/messages:** ["ui_message", "script_parse", "content_load", "resource_transition"]

**Data/assets:** ["UTFWin records", "ArgScript/config bytes", "pdtk commands", "UI content"]

**Serialization:** ["ArgScript/config/property streams", "pdtk grammar/whole UI persistence unresolved"]

**Engine interfaces:** ["IEventLoop", "IStageEventRouter", "IMessageManager", "IConfigCodec", "IPropertyStore", "IWindowCompatibility"]

**Invariants:** ["Registration separate from emission", "No universal UI/App ABI", "Scope nesting balances", "pdtk strings bounded commands"]

**Error/failure semantics:** ["Priority/tie/consume unresolved", "Script lifecycle failures unresolved", "UI-to-stage causality unknown"]

**Initialization:** Init: parser/window/message

**Update/tick:** Tick: poll/route/parse

**Shutdown/cleanup:** Shutdown: listeners/scopes/windows/UI/script release

**Validation strategy:** ["deterministic_unit", "integration", "original_binary_oracle", "agent_overlay", "menu_walk", "M0/M5/UI grammar"]

**Known divergences:** ["No current UTFWin", "SDL direct path", "Observation shell not UI reconstruction"]

**Unknowns:** ["Dispatch order", "Priority/tie/return", "pdtk grammar", "UI-stage order", "Script format"]

**Implementation status:** `BLOCKED_BY_RUNTIME`. A host seam exists, but the original lifecycle, reachability, or observable behavior is not runtime-validated.

## PKG-19-AUDIO-INPUT — Audio and original input marshalling

**Package:** PKG-19-AUDIO-INPUT

**Purpose:** Identify original audio/input-device boundaries before replacement; keep them separate from host SDL/DSOUND/CellInput.

**Subsystem owner:** Original audio service and platform input marshalling.

**Authoritative state:** ["Authoritative: none established", "Runtime: unknown audio/input event/device state", "Persistent: none", "Invariant: host adapters are not original device semantics"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["Audio service candidate: handle/cue/voice", "Original input: device event/normalized values/mode routing", "Both name-level/unresolved"]

**Functions:** ["0x00571f80 PlayProceduralAudio", "GameInput OnKeyDown/OnKeyUp candidate", "No service ownership established"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["PKG-01", "PKG-02", "PKG-18", "bounded original trace", "negative no-audio/no-input contract", "VA mapping"]

**State machines:** ["device_event -> normalized -> mode_route -> consumed/default unresolved", "audio request -> backend -> started/failed unresolved"]

**Events/messages:** ["audio_event", "input_marshalling_event"]

**Data/assets:** ["Candidate audio/input identities", "No persistent assets"]

**Serialization:** ["None established"]

**Engine interfaces:** ["IPlatformHost", "IAudioSink", "IInputRouter"]

**Invariants:** ["Host device implementation not original", "No CellInput ownership from low evidence"]

**Error/failure semantics:** ["No-audio/no-input remains negative", "Device/service errors unresolved"]

**Initialization:** Init: identify/provision boundary

**Update/tick:** Tick: marshal/dispatch only after evidence

**Shutdown/cleanup:** Shutdown: release handles

**Validation strategy:** ["provenance_negative", "original_binary_oracle", "not_yet_testable", "cell_trace", "cell_movement probes", "bounded trace"]

**Known divergences:** ["Host SDL/DSOUND not original", "Current CellInput is clean-room contract"]

**Unknowns:** ["Function ownership", "Input routing", "Audio ownership", "Device behavior"]

**Implementation status:** `BLOCKED_BY_RE`. The package still needs a bounded static contract, owner, or function-family characterization before implementation can be authoritative.

## PKG-20-GAMEGLOBAL — GameGlobal map and miscellaneous state

**Package:** PKG-20-GAMEGLOBAL

**Purpose:** Characterize the high-fan-in GameGlobal map lookup without assigning manager or gameplay meaning.

**Subsystem owner:** GameGlobal map/lookup state pending characterization.

**Authoritative state:** ["Authoritative: none established", "Runtime: candidate global map/callers; owner/mutation/lifetime unresolved", "Persistent: none", "Invariant: high fan-in is not manager identity"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["GameGlobal state: owner/map type/key/value/mutation/consumers", "map_int_whatever_find: body/key/value/absence semantics"]

**Functions:** ["0x00e5c780 map_int_whatever_find lookup candidate; body absent and requires RE"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["Ghidra xrefs", "PKG-01", "decompile map", "identify owner/offsets", "freeze key/value/mutation/caller contract"]

**State machines:** ["owner_unresolved -> key_unresolved -> lookup_result -> consumer_unresolved"]

**Events/messages:** ["global_map_lookup"]

**Data/assets:** ["Candidate map identity", "No persistent assets"]

**Serialization:** ["Unknown", "No round-trip"]

**Engine interfaces:** ["Candidate IIdMap only after characterization"]

**Invariants:** ["No IIdMap promotion before owner/key/value evidence", "Fan-in does not establish semantics"]

**Error/failure semantics:** ["Missing key/null owner/invalid key unresolved"]

**Initialization:** Init: identify owner/init after contract

**Update/tick:** Tick: lookup/read/write after mutation contract

**Shutdown/cleanup:** Shutdown: release map state

**Validation strategy:** ["decomp_differential", "not_yet_testable", "readiness foundation", "xref TSV", "map decomp/field/consumer tests"]

**Known divergences:** ["Current map assumptions are not original"]

**Unknowns:** ["Map type", "Owner", "Key domain", "Value", "Mutation/persistence"]

**Implementation status:** `BLOCKED_BY_RE`. The package still needs a bounded static contract, owner, or function-family characterization before implementation can be authoritative.

## PKG-21-UNKNOWN-ROUTING — Unknown routing and ownership backlog

**Package:** PKG-21-UNKNOWN-ROUTING

**Purpose:** Record unresolved routing/ownership debt without inventing semantic subsystems from fan-in or vtable proximity.

**Subsystem owner:** Unresolved cross-domain backlog; no implementation owner.

**Authoritative state:** ["Authoritative: none", "Runtime: unresolved functions/vtable families only", "Persistent: none", "Invariant: unknown rows stay outside implementation scope"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["Anonymous unresolved functions", "Unresolved vtable families", "UNKNOWN-HIGH debt rows"]

**Functions:** ["0x00e780a0 cross-listed lifecycle candidate", "Unknown-vtable implementations", "Unknown-fun mass; ownership and contracts unresolved"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["debt map", "Ghidra decompilation capacity", "triage-v6", "xrefs", "decompile/adjudicate UNKNOWN-HIGH", "resolve vtable ownership"]

**State machines:** ["unknown function -> typed package only after evidence", "unresolved vtable -> class/interface only after evidence"]

**Events/messages:** ["ownership_transition", "semantic_event_model"]

**Data/assets:** ["Debt map", "No game assets"]

**Serialization:** ["None"]

**Engine interfaces:** ["None until ownership is established"]

**Invariants:** ["No fan-in/namespace/vtable-proximity semantic promotion", "No speculative per-region split"]

**Error/failure semantics:** ["Unknown ownership remains explicit", "Missing body is uncaptured evidence, not failure"]

**Initialization:** Init: none

**Update/tick:** Tick: triage/characterize only

**Shutdown/cleanup:** Shutdown: none

**Validation strategy:** ["provenance_negative", "decomp_differential", "not_yet_testable", "triage/readiness/debt artifacts"]

**Known divergences:** ["No current implementation correspondence"]

**Unknowns:** ["1,598 unknown gameplay rows", "39,716 unknown canonical rows", "All ownership/events"]

**Implementation status:** `BLOCKED_BY_RE`. The package still needs a bounded static contract, owner, or function-family characterization before implementation can be authoritative.

## PKG-22-RUNTIME-CRT-STL — Runtime, CRT, STL, and third-party wrappers

**Package:** PKG-22-RUNTIME-CRT-STL

**Purpose:** Account for runtime/third-party ancestry and exclude semantic reconstruction unless a gameplay boundary needs a narrow stub.

**Subsystem owner:** CRT/STL/runtime imports and third-party wrappers.

**Authoritative state:** ["Authoritative: attribution boundary only", "Runtime: platform/allocator/import wrappers", "Persistent: none", "Invariant: runtime wrappers are not gameplay"]

**Runtime/transient state:** Owned by the package boundary; distinguish from persistent records and presentation/runtime handles.

**Persistent state:** Only claims explicitly identified as serialized/database/profile records; exact framing remains open where noted.

**Core structures and important fields:** ["MSVCR90/import ancestry", "Runtime/allocator/stream wrappers", "No semantic game structures"]

**Functions:** ["MSVCR90 wrapper rows: platform/runtime calls only", "No package function anchors"]

**Function contracts:** Reads/writes, side effects, error behavior, persistence impact, and validation remain bounded by the evidence register in the JSON artifact; unresolved bodies are explicitly listed as unknowns.

**Dependencies and prerequisites:** ["Attribution triage", "Concrete gameplay boundary", "Boundary stub contract", "No semantic promotion"]

**State machines:** ["Gameplay call -> runtime/CRT implementation -> out of scope"]

**Events/messages:** ["runtime_wrapper_event"]

**Data/assets:** ["No game assets"]

**Serialization:** ["None"]

**Engine interfaces:** ["IPlatformHost", "IAudioSink", "Bounded stream/device adapters"]

**Invariants:** ["No gameplay semantics from wrapper names", "Stub only at explicit boundary"]

**Error/failure semantics:** ["Runtime errors remain platform-level", "No original gameplay error claim"]

**Initialization:** Init: runtime services

**Update/tick:** Tick: platform services

**Shutdown/cleanup:** Shutdown: release runtime services

**Validation strategy:** ["deterministic_unit", "attribution audit", "not_yet_testable", "track-b accounting", "attribution JSON"]

**Known divergences:** ["Current SDL/Vulkan/host runtime is modern replacement", "No original runtime reconstruction"]

**Unknowns:** ["Only any concrete gameplay dependency is relevant"]

**Implementation status:** `INFRASTRUCTURE_REPLACEMENT`. This is a replacement boundary or evidence tool, not a gameplay semantic package.

## OpenSpore Implementation Swarm v1 status

The following eight packages are implemented as bounded clean-room host contracts. This status does not promote any package to original-runtime compatibility or byte-level equivalence.

| Package | Derived status | Evidence boundary |
|---|---|---|
| PKG-03-RESOURCE-IO | `IMPLEMENTED_WITH_LOCAL_UNKNOWN` | BLUEPRINT_BACKED resource/property seam; host wire behavior remains bounded |
| PKG-04-ASSET-GEOMETRY-TEXTURE | `IMPLEMENTED_WITH_LOCAL_UNKNOWN` | BLUEPRINT_BACKED bounded GMDL/RW4/raster decode; host rendering is not original pixels |
| PKG-05-CELL-CONTENT | `IMPLEMENTED_WITH_LOCAL_UNKNOWN` | BLUEPRINT_BACKED direct Cell records; runtime use and placement remain bounded |
| PKG-08-CELL-MODE | `IMPLEMENTED_WITH_LOCAL_UNKNOWN` | BLUEPRINT_BACKED clean-room lifecycle/input seam; original timing remains bounded |
| PKG-06-CELL-STATE | `IMPLEMENTED_WITH_LOCAL_UNKNOWN` | BLUEPRINT_BACKED pure Cell rules; live singleton/runtime equivalence remains unpromoted |
| PKG-09-CELL-PRESENTATION | `IMPLEMENTED_WITH_LOCAL_UNKNOWN` | BLUEPRINT_BACKED host presentation stage; original placement/pixel/GPU behavior remains unpromoted |
| PKG-17-ANIMATION-SWARM | `IMPLEMENTED_WITH_LOCAL_UNKNOWN` | BLUEPRINT_BACKED animation-intent seam; pose/Swarm runtime behavior remains unpromoted |
| PKG-15-EDITOR-SUPPORT | `IMPLEMENTED_WITH_LOCAL_UNKNOWN` | BLUEPRINT_BACKED support seam; original editor runtime behavior remains unpromoted |

Remaining bounded assumptions are recorded in `docs/analysis/future-research/implementation-unknowns.md` and package-specific research briefs. No speculative semantic claim or evidence-level promotion is made by this status update.

## Package acceptance boundary

A future implementation agent may use this document for bounded clean-room interfaces, but must return to the JSON evidence register for exact function records, evidence citations, unknowns, and validation gates. No package brief authorizes a raw original ABI implementation or claims original behavior without the listed oracle.
