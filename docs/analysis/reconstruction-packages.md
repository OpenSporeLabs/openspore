# Reconstruction Packages

## Policy

Track O defines 23 semantic reconstruction packages. A function is an explicit package anchor only when Track O lists it as a package function or a single-VA package root. Broader cluster matches in the semantic atlas are marked `TRACK_O_SCOPE_PLUS_TRIAGE_CLUSTER_INFERRED`; they are research candidates, not ownership facts.

All function contracts remain `unknown`. Package confidence describes static evidence and current OpenSpore correspondence, not original runtime verification.

## Package index

| Package | Name | Confidence | Interface | Explicit anchors | Candidate functions | Prerequisites |
| --- | --- | --- | --- | --- | --- | --- |
| PKG-00-EVIDENCE-VALIDATION | Evidence acquisition, provenance, and validation infrastructure | SUPPORTED | EXISTING_INFRASTRUCTURE | 0 | 0 | 3 |
| PKG-01-SHARED-STATE-ROOTS | Simulator shared-state roots and interface freeze | INFERRED | NOT_DEFINED | 16 | 1631 | 4 |
| PKG-02-APP-LIFECYCLE | Application bootstrap and system lifecycle | SUPPORTED | NOT_DEFINED | 5 | 1105 | 3 |
| PKG-03-RESOURCE-IO | Resource manager, DBPF/QFS I/O, and property substrate | SUPPORTED | EXISTING_REPLACEMENT_SEAM | 3 | 523 | 3 |
| PKG-04-ASSET-GEOMETRY-TEXTURE | GMDL/RW4/raster geometry and texture decode | SUPPORTED | EXISTING_REPLACEMENT_SEAM | 0 | 86 | 3 |
| PKG-05-CELL-CONTENT | Cell content and resource record semantics | SUPPORTED | PARTIAL_EXISTING_CONTRACT | 2 | 27 | 3 |
| PKG-06-CELL-STATE | Cell game state, pool, query, advect, and combat rules | SUPPORTED | PARTIAL_EXISTING_CONTRACT | 3 | 27 | 3 |
| PKG-07-CELL-MOVEMENT | Cell movement and mouse-steering replacement | SUPPORTED | CONTRACT_DEFINED; REAL_INSTALL_UNVALIDATED | 8 | 33 | 4 |
| PKG-08-CELL-MODE | Cell mode lifecycle and input routing | SUPPORTED | EXISTING_CLEAN_ROOM_INTERFACE | 6 | 45 | 3 |
| PKG-09-CELL-PRESENTATION | Cell GFX, HUD, scene assembly, and renderer boundary | SUPPORTED | EXISTING_REPLACEMENT_SEAMS | 7 | 112 | 3 |
| PKG-10-EDITOR-DISPATCH | Editor and UTFWin message/input dispatch | SUPPORTED | UNRESOLVED | 6 | 1409 | 3 |
| PKG-11-SIM-CORE | Simulator core managers, tools, and missions | INFERRED | UNRESOLVED | 6 | 1628 | 3 |
| PKG-12-SIM-SPACE | Simulator Space stage | INFERRED | UNRESOLVED | 2 | 8 | 3 |
| PKG-13-SIM-CREATURE-TRIBECIV | Simulator creature, tribe, and civilization stage | UNKNOWN | UNRESOLVED | 0 | 11 | 3 |
| PKG-14-TERRAIN-WORLD | Terrain, planet surface, and world rendering | UNKNOWN | UNRESOLVED | 0 | 112 | 3 |
| PKG-15-EDITOR-SUPPORT | Palettes, Skinner, and editor support | INFERRED | UNRESOLVED | 3 | 100 | 3 |
| PKG-16-SPOREPEDIA-ONLINE | Sporepedia asset data and online boundary | INFERRED | NOT_IMPLEMENTED | 5 | 100 | 3 |
| PKG-17-ANIMATION-SWARM | Cell animation and swarm/creature animation boundary | INFERRED | PARTIAL_EXISTING_CONTRACT | 1 | 96 | 3 |
| PKG-18-UI-SCRIPTING | UTFWin UI shell and scripting/content boundary | INFERRED | UNRESOLVED | 1 | 1191 | 3 |
| PKG-19-AUDIO-INPUT | Audio and original input marshalling | UNKNOWN | UNRESOLVED | 0 | 11 | 3 |
| PKG-20-GAMEGLOBAL | GameGlobal miscellaneous state | UNKNOWN | UNRESOLVED | 1 | 39 | 3 |
| PKG-21-UNKNOWN-ROUTING | Unknown vtable implementations and unknown function mass | UNKNOWN | UNRESOLVED | 1 | 49363 | 3 |
| PKG-22-RUNTIME-CRT-STL | Runtime, CRT, STL, and third-party wrappers | SUPPORTED | OUT_OF_SCOPE | 0 | 4075 | 3 |

## Cross-package contracts

| ID | Contract | Pass condition | Requirements |
| --- | --- | --- | --- |
| C-PROV | Trace provenance | A result cannot be confused with a historical example or another build. | binary_sha256; probe-set path/hash; image base/address convention; Wine/display/input environment; raw JSONL path/events; exact outcome |
| C-NEG | Negative-result semantics | No semantic/status promotion from uncorrelated or zero-event runs. | zero events remain zero events; boot stall and clean exit are distinct; generic frame is not Cell evidence; screenshots do not substitute for events |
| C-ORDER | Lifecycle/event ordering | Static lifecycle claims are corroborated or explicitly rejected. | Initialize/OnEnter/Update/OnExit/Dispose order where claimed; mode-manager correlation; stable or explained object identity |
| C-STATE | Shared state ownership | Gameplay, engine, and transient state are distinguished. | sCellGame pointer and fields; pool index versus resolved entity; state words; pool/GFX handle lifetimes |
| C-ABI | Replacement ABI | Only then can a live trace contribute to replacement promotion. | VA/bytes/linked address/stack; pool lookup; lock/plane/camera/UI gates; omitted callees; target/orientation/moving stores |
| C-REPLACEMENT | Replacement promotion | 64/64 decomp-only result remains replaced-approx. | hash-pinned live trace; field meanings/offsets meet gate; original/replacement observable comparison; independent adjudication/human approval |

## Track-F empire/economy ownership matrix

This matrix assigns the Track-F long-tail research questions to the existing package set; it does not promote static field maps to implementation readiness. Each owner must stop at the named unresolved boundary until the required ownership, event, and observable contracts are established.

| Track-F concern | Primary package owner | Contract scope | Unresolved stopping condition |
| --- | --- | --- | --- |
| Empire money | PKG-11-SIM-CORE | `cEmpire` money balance, credits, mutation, rollback, and mission interaction | Stop before semantic promotion or replacement design until the owning object, numeric representation, mutation/rollback rules, and correlated runtime events are characterized. |
| Space trade | PKG-12-SIM-SPACE | `cSpaceTrading` requests, offers, acceptance, inventory/value effects, and failure paths | Stop until the service owner, trade state machine, stage reachability, atomicity/failure behavior, and original/replacement observables are established. |
| Missions | PKG-11-SIM-CORE | Mission manager registration, activation, objectives, completion, rewards, and teardown | Stop until lifecycle ownership, event ordering, reward/money coupling, persistence, and stage-specific runtime reachability are correlated. |
| Tribes | PKG-13-SIM-CREATURE-TRIBECIV | Tribe/civilization records, relationships, diplomacy, and creature-stage integration | Stop until VAs/vtables, state ownership, event order, relationship mutations, and runtime stage evidence are adjudicated. |
| Planets | PKG-12-SIM-SPACE | Planet models, ownership, population/economy, terraforming, and Space-to-terrain state handoff | Stop until owner identity, field meanings, stage-transition contract, mutation rules, and Space/terrain runtime correlation are established. |
| Stars and systems | PKG-12-SIM-SPACE | Star/system records, ownership, relationships, and navigation/economy links | Stop until object identity, lifecycle, relationship/event order, stage reachability, and observable selection/persistence behavior are characterized. |
| Empire/economy serialization | PKG-11-SIM-CORE, with PKG-12/PKG-13 stage-specific field handoffs | Shared record schema, field order/versions, money/trade/mission persistence, and stage-owned planet/tribe records | Stop before any replacement interface or semantic promotion until schema ownership, version/default behavior, save/load coverage, round-trip observables, and cross-stage handoffs are mapped. |

## Package details

## PKG-00-EVIDENCE-VALIDATION — Evidence acquisition, provenance, and validation infrastructure

**Scope:** Cross-cutting infrastructure that preserves evidence versus implementation behavior; it is not a game-runtime package.

**Confidence:** `SUPPORTED`; basis: Current source and tests, Track B, Track M, Track N. Unresolved: No live Cell Stage trace exists in the current evidence set.

**Membership:** 0 explicit function/root anchors; 0 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=committed test artifacts, Ghidra/SDK exports, pinned SporeApp.exe; downstream=all semantic packages. Boundary rule: Never convert a generic frame, name, vtable association, or empty trace into a gameplay claim.

**Replacement interface:** `EXISTING_INFRASTRUCTURE` — Evidence and validation interface. Keep identity, provenance, negative outcomes, and test results separate from semantic conclusions. No game replacement interface is defined here. Target: None

**Prerequisites:** Hash-pin any future runtime artifact; Keep SPORE read-only; Preserve approval and machine-lock gates

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | fixture_check/test_run | Fixture identity and test orchestration | OBSERVED |
|  | kg_record/queue_op | Record evidence and investigation state | OBSERVED |
|  | observe.py launch/trace/analyze | Approved bounded observation | OBSERVED |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  |  | Cross-tool evidence and test memory | OBSERVED |
|  |  | Bounded function-entry observation | OBSERVED |
|  |  | Evidence dossier generation | OBSERVED |
|  |  | Read-only triage projection | OBSERVED |

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |
| Evidence record | Provenance, evidence level, identity, and test outcome | OBSERVED | knowledgegraph/schema.sql |
| Trace manifest | Runtime environment and outcome identity | OBSERVED | tools/observatory/out/ |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| decompile_provenance | Binary, VA, mode, and artifact identity | OBSERVED |
| function_entry | Tracer mechanics only | OBSERVED |
| test_outcome | Test result with environment and identity | OBSERVED |
| zero_event | Retain as negative; never promote | OBSERVED_NEGATIVE |

### Transitions

| From | To | Status |
| --- | --- | --- |
| artifact | semantic package claim | SUPPORTED only after package-specific adjudication |
| pinned evidence | provenance-bearing artifact | OBSERVED |
| zero-event or failed boot | negative result | OBSERVED_NEGATIVE |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| tests/mcp/ | Ghidra, KG, queue, safety, and protocol behavior | COVERED |
| tests/test_dossier.py | Dossier schema and negative-runtime contract | COVERED |
| tests/test_kg_schema.py | SQLite schema and constraints | COVERED |
| tests/test_kg_seed.py | Deterministic seed and queue contracts | COVERED |
| tools/observatory/test/m32target.c | Native tracer plumbing only | NOT_ORIGINAL_EVIDENCE |

## PKG-01-SHARED-STATE-ROOTS — Simulator shared-state roots and interface freeze

**Scope:** The high-fan-in roots that gate most Simulator gameplay. This is an interface-freeze package, not an implementation package.

**Confidence:** `INFERRED`; basis: Named getter bodies, Readiness audit, Static fan-in. Unresolved: Dependent event/state contract, Return identities and semantics of unnamed roots.

**Membership:** 16 explicit function/root anchors; 1631 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=binary globals, Ghidra xrefs, SDK name-level symbols, PKG-20 characterization of `map_int_whatever_find`/`0x00e5c780`; downstream=PKG-06, PKG-07, PKG-08, PKG-10, PKG-11, PKG-12, PKG-13, PKG-20. Boundary rule: Characterize service interfaces and the map container contract before implementing dependents; never infer an unnamed root's type from fan-in.

**Replacement interface:** `NOT_DEFINED` — Typed service-access interface freeze. The safe boundary is a typed service-handle accessor contract, not an implementation of any FUN_* root. Return type, lifetime, initialization, and invalid-handle behavior remain prerequisites. Target: None

**Prerequisites:** Export/decompile the ten unnamed roots; Decompile/adjudicate `map_int_whatever_find`/`0x00e5c780` and freeze its map type, key/value, owner, mutation, and caller contracts; Freeze caller contracts; Resolve returned globals and layouts

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |
| 0x00401090 | Editors::cSpeciesManager::Get | Named singleton accessor | SUPPORTED |
| 0x00b3d350 | Simulator::cGameInputManager::Get | Return DAT_0167eaf8 | CONFIRMED_NAME_AND_BODY |
| 0x00b3d3c0 | Simulator::cRelationshipManager::Get | Named singleton accessor | SUPPORTED |
| 0x00b3d420 | Simulator::cGameModeManager::Get | Named singleton accessor | SUPPORTED |
| 0x00b3d4d0 | Simulator::cSpaceTrading::Get | Named singleton accessor | SUPPORTED |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
| 0x00b1fdb0 | FUN_00b1fdb0 | Unnamed high-fan-in root | UNRESOLVED |
| 0x00b21340 | FUN_00b21340 | Unnamed high-fan-in root | UNRESOLVED |
| 0x00b25fb0 | FUN_00b25fb0 | Unnamed high-fan-in root | UNRESOLVED |
| 0x00b3d2a0 | FUN_00b3d2a0 | Unnamed high-fan-in root | UNRESOLVED |
| 0x00b3d300 | FUN_00b3d300 | Largest root: 1,097 total / 252 gameplay callers | UNRESOLVED |
| 0x00b5b800 | FUN_00b5b800 | Unnamed high-fan-in root | UNRESOLVED |
| 0x00ba9370 | FUN_00ba9370 | Unnamed high-fan-in root | UNRESOLVED |
| 0x00e5c780 | map_int_whatever_find | High-fan-in map lookup candidate | NEEDS_RE |
| 0x01021080 | FUN_01021080 | Unnamed high-fan-in root | UNRESOLVED |
| 0x01021260 | FUN_01021260 | Unnamed high-fan-in root | UNRESOLVED |
| 0x01021300 | FUN_01021300 | Unnamed high-fan-in root | UNRESOLVED |

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |
| Simulator::cGameInputManager | Named singleton return | CONFIRMED_NAME_ONLY |  |
| Simulator::cGameModeManager | Named singleton return | CONFIRMED_NAME_ONLY |  |
| Simulator::cRelationshipManager | Named singleton return | CONFIRMED_NAME_ONLY |  |
| Simulator::cSpaceTrading | Named singleton return | CONFIRMED_NAME_ONLY |  |
| Unnamed shared-state layout | Object layout for unnamed roots | UNRESOLVED |  |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| service_handle_use | No event or state meaning assigned | UNRESOLVED |
| singleton_get | Return-value contract only | SUPPORTED for named accessors; UNRESOLVED for unnamed roots |

### Transitions

| From | To | Status |
| --- | --- | --- |
| named getter | global service pointer | SUPPORTED for decompiled named accessors |
| shared root | dependent Simulator/editor caller | SUPPORTED structurally; semantics UNRESOLVED |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| knowledgegraph/research/21-decompilation-coverage.json | Persisted decompilation availability | READ_ONLY_EVIDENCE |
| knowledgegraph/triage/reconstruction-readiness-f0e310e0.json | Foundation ranking and unresolved roots | READ_ONLY_EVIDENCE |
| knowledgegraph/triage/xrefs-2540f2ca.tsv | Caller/callee relationships | READ_ONLY_EVIDENCE |

## PKG-02-APP-LIFECYCLE — Application bootstrap and system lifecycle

**Scope:** Original process bootstrap, app-system initialization, and stage-transition observation. No original lifecycle reimplementation is claimed.

**Confidence:** `SUPPORTED`; basis: Byte-verified probes, Current negative record, Historical main-menu trace. Unresolved: Boot exit trigger, Complete state-machine order, Menu-to-stage transition.

**Membership:** 5 explicit function/root anchors; 1105 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=display/Wine environment, PE entry bytes, SDK app-system symbols; downstream=PKG-03, PKG-10, PKG-11, PKG-18. Boundary rule: Boot control is not evidence of a stage transition.

**Replacement interface:** `NOT_DEFINED` — Application lifecycle observation boundary. A future replacement may expose lifecycle events only after a repeatable original trace establishes initialization order and stage handoff. Target: None

**Prerequisites:** Fresh wineserver generation; Human approval and normal display/Wine/lock gates; Positive boot control

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | cAppSystem::Init | Initialize system | SUPPORTED |
|  | cAppSystem::InitPlugins | Initialize plugins | SUPPORTED |
|  | cAppSystem::Startup | Start subsystems | SUPPORTED |
|  | IAppSystem::Get | Retrieve service | SUPPORTED |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
| 0x0067dcc0 | IAppSystem::Get | Global system accessor | OBSERVED_HISTORICAL |
| 0x007e67a0 | cAppSystem::Startup | Subsystem startup | OBSERVED_HISTORICAL |
| 0x007e8ba0 | cAppSystem::Init | System initialization | OBSERVED_HISTORICAL |
| 0x007e93d0 | cAppSystem::InitPlugins | Plugin initialization | OBSERVED_HISTORICAL |
| 0x00e20860 | stateMachine | Bootstrap state machine | STATIC; NOT_REACHED |
| 0x11e11a0 | entry | PE bootstrap control | OBSERVED |
| 0xde13d0 | local_main | Adjacent bootstrap main | STATIC; NOT_REACHED |

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |
| App::cAppSystem | Lifecycle object | CONFIRMED_NAME |  |
| App::IAppSystem | System accessor | CONFIRMED_NAME |  |
| Resource::cResourceManager | Resource bring-up | CONFIRMED_NAME |  |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| app_system_get | Capped accessor | OBSERVED_HISTORICAL |
| bootstrap_entry | Entry once | OBSERVED_HISTORICAL |
| init | Startup order | OBSERVED_HISTORICAL |
| init_plugins | Startup order | OBSERVED_HISTORICAL |
| startup | Startup order | OBSERVED_HISTORICAL |

### Transitions

| From | To | Status |
| --- | --- | --- |
| Startup | IAppSystem::Get | OBSERVED_HISTORICAL |
| Startup | local_main/stateMachine | UNRESOLVED |
| entry | InitPlugins/Init/Startup | OBSERVED_HISTORICAL |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| tests/test_cell_trace.py | Trace gates and dry-run contracts | COVERED |
| tools/observatory/examples/obs_main_menu_example.jsonl | Historical positive startup order | HISTORICAL_POSITIVE |
| tools/observatory/out/obs_main_menu.jsonl | Current output | EMPTY_NEGATIVE |
| tools/observatory/probes/main_menu.json | Byte-checked bootstrap probes | FIXTURE_AVAILABLE |

## PKG-03-RESOURCE-IO — Resource manager, DBPF/QFS I/O, and property substrate

**Scope:** Original resource/IO boundary plus the clean-room DBPF reader. Full multi-package load order and property serialization remain unresolved.

**Confidence:** `SUPPORTED`; basis: B1 seam/tests, Byte-verified DBPF/QFS, Python oracle. Unresolved: Multi-package priority/cache, Original load order, Property serialization.

**Membership:** 3 explicit function/root anchors; 523 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=DBPF/QFS evidence, SPORE package bytes; downstream=PKG-04, PKG-05, PKG-09, PKG-10. Boundary rule: Keep package details behind B1; do not claim original multi-package registry/cache/load-order behavior.

**Replacement interface:** `EXISTING_REPLACEMENT_SEAM` — B1 IResourceProvider. fetch(type, group, instance) returns record bytes plus explicit error. This does not replace original cResourceManager orchestration; property serialization is outside this seam. Target: src/compat/ResourceProvider.hpp:24

**Prerequisites:** Malformed/truncated DBPF/QFS fixtures; Menu transition trace; Property fixture and round-trip contract

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | cResourceManager::Initialize | Original bring-up | NOT_RUNTIME_OBSERVED |
|  | extractDbpfRecord | Extract record | OBSERVED_CURRENT |
|  | parseDbpfIndex | Parse package index | OBSERVED_CURRENT |
|  | qfsDecompress | QFS decompression | OBSERVED_CURRENT |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
| 0x008d84f0 | DatabasePackedFile::Lock | DBPF package lock | STATIC; MID_BODY_PROBE |
| 0x008dbcc0 | PFIndexModifiable::Read | Package index read | STATIC; MID_BODY_PROBE |
| 0x008de530 | cResourceManager::Initialize | Resource bring-up | STATIC_ANCHOR |

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |
| DatabasePackedFile | Packed package | CONFIRMED_NAME |  |
| DBPF v3 header/index | Record identity and extent | VERIFIED_BOUNDED | tools/spore/dbpf/dbpf.py; src/assets/Dbpf.cpp |
| PFIndexModifiable | Package index | CONFIRMED_NAME |  |
| Property serialization record | Persistence boundary | UNRESOLVED |  |
| ResourceKey | Resource identity | CONFIRMED_NAME |  |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| index_read | Menu transition | PROPOSED; NOT_OBSERVED |
| package_lock | Menu transition | PROPOSED; NOT_OBSERVED |
| property_load | No fixture or trace | UNRESOLVED |
| record_fetch | B1 provider | OBSERVED_CURRENT_INTERFACE |

### Transitions

| From | To | Status |
| --- | --- | --- |
| property bytes | runtime property object | UNRESOLVED |
| record identity | record bytes | VERIFIED_BOUNDED |
| resource initialization | DBPF lock/index read | INFERRED; not runtime-confirmed |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| src/assets/tests/real_asset_test.cpp | Real-package checks | SKIPS_WITHOUT_SPORE |
| tests/fixtures/mini_package.dbpf | Synthetic DBPF v3/QFS/raw records | COMMITTED_FIXTURE |
| tests/test_formats.py | Header, index, extraction, decompression | COVERED |
| tools/observatory/probes/menu_transition.json | Resource transition probes | DEFINED_NOT_RUN |

## PKG-04-ASSET-GEOMETRY-TEXTURE — GMDL/RW4/raster geometry and texture decode

**Scope:** Host-side geometry, model, texture, and container decoding. Renderer fidelity, animation, and unsupported versions remain separate or unresolved.

**Confidence:** `SUPPORTED`; basis: Independent oracles, Parser tests, Synthetic and real-record decode. Unresolved: GMDL v9/animation, Original pixels, Raster words 0x10/0x18, RW4 material/animation.

**Membership:** 0 explicit function/root anchors; 86 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=GOG package records, PKG-03, Python oracles; downstream=B2 IMeshSource, B3 IRenderer, PKG-09. Boundary rule: Do not treat host conversion or accepted opaque trailers as complete RenderWare behavior.

**Replacement interface:** `EXISTING_REPLACEMENT_SEAM` — B2 IMeshSource and texture input. Expose provider-independent Mesh and host texture inputs. No promise of original materials, animation, lighting, or pixels. Target: src/compat/MeshSource.hpp:26; src/renderer/Renderer.hpp:46

**Prerequisites:** Full C++/Python field differential; Keep v9/animation/unknown raster fields unsupported; Malformed/truncated fixtures

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | decodeDxt5Mip | DXT5 decode | VERIFIED_BOUNDED |
|  | decodeRasterMips | Raster decode | VERIFIED_BOUNDED |
|  | meshFromGmdl | Geometry/bounds | VERIFIED_BOUNDED |
|  | parseGmdl | GMDL walk | VERIFIED_BOUNDED |
|  | parseRw4 | RW4 section walk | SUPPORTED |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | GMDL v8/static records | Models/material IDs | VERIFIED_BOUNDED |
|  | raster records | Raster/DXT5 | VERIFIED_BOUNDED |
|  | RW4 records | Graphics containers | VERIFIED_BOUNDED |

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |
| GmdlModel | Versioned model | OBSERVED_CURRENT | src/assets/Gmdl.hpp |
| ImageRGBA | Decoded mips | OBSERVED_CURRENT | src/assets/Texture.hpp |
| Mesh | Host mesh/bounds | OBSERVED_CURRENT | src/assets/Mesh.hpp |
| RenderWare material/animation payload | Original graphics behavior | UNRESOLVED |  |
| RW4 section manifest/types | Container sections | SUPPORTED | src/assets/Rw4.cpp |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| gmdl_decoded | v8/static only | OBSERVED_CURRENT |
| mesh_built | Host conversion | OBSERVED_CURRENT |
| record_extracted | B1 | OBSERVED_CURRENT_INTERFACE |
| rw4_section_observed | Structure only | OBSERVED_CURRENT |
| texture_decoded | Raster/DXT5 only | OBSERVED_CURRENT |

### Transitions

| From | To | Status |
| --- | --- | --- |
| DBPF identity | GMDL/RW4/raster bytes | VERIFIED_BOUNDED |
| GMDL bytes | Mesh/renderer layout | SUPPORTED |
| RW4 section | original material/animation | UNRESOLVED |
| raster bytes | RGBA8 mips | SUPPORTED |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| tests/fixtures/mini.gmdl | Synthetic GMDL v8/BE refCount | COMMITTED_FIXTURE |
| tests/fixtures/mini_rw4.rw4 | Synthetic RW4 sections | COMMITTED_FIXTURE |
| tests/test_formats.py | GMDL/RW4/DBPF snapshots | COVERED |
| tests/test_rw4.py | 1,131-record C++/Python differential | ENVIRONMENT_DEPENDENT |
| tests/test_textures.py | DXT5/raster oracles | COVERED_OR_OPT_IN |

## PKG-05-CELL-CONTENT — Cell content and resource record semantics

**Scope:** Typed decoding of CellSerializer-derived and cell-stage resource records, separate from runtime state consumption.

**Confidence:** `SUPPORTED`; basis: Python/C++ decoders, Real-package census, SDK layouts. Unresolved: Full cross-language parity, Runtime use of fields, World-object placement/ownership, `0x00e82340`/`0x00e82420` alias and body identity.

**Membership:** 2 explicit function/root anchors; 27 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=Cell packages, PKG-03, SDK layouts; downstream=PKG-06, PKG-09. Boundary rule: Decode and validate records here; do not infer runtime selection, placement, damage, or AI behavior from names.

**Replacement interface:** `PARTIAL_EXISTING_CONTRACT` — Typed Cell resource value boundary. Expose typed records with type IDs, byte accounting, and reference validation. Runtime selection and original effects remain outside the guarantee. Target: src/assets/CellResource.hpp

**Prerequisites:** Automated C++/Python field differential; Canonical record manifest; Malformed/reference-negative fixtures

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | parseCellCellResource | Cell decode | OBSERVED_CURRENT |
|  | parseCellEffectMapResource | Effect map decode | OBSERVED_CURRENT |
|  | parseCellLootTableResource | Loot decode | OBSERVED_CURRENT |
|  | parseCellPopulateResource | Marker decode | OBSERVED_CURRENT |
|  | parseCellStructureResource | Structure decode | OBSERVED_CURRENT |
|  | parseCellWorldResource | World decode | OBSERVED_CURRENT |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
| 0x00e4ce20 | GetGlobalsData | Cell globals lookup | SUPPORTED |
| 0x00e82340 | FUN_00e82340 (possible `cCellDataReference_::Create` body) | Data-reference body candidate; SDK-associated function is at `0x00e82420` | ALIAS_AND_IDENTITY_UNRESOLVED |
|  | cCellCellResource | Cell family | VERIFIED_BOUNDED |
|  | cCellGlobalsResource | Stage tuning | VERIFIED_BOUNDED |
|  | cCellPopulateResource | Markers | VERIFIED_BOUNDED |
|  | cCellWorldResource | World/advect | VERIFIED_BOUNDED |

**Unresolved alias note:** `0x00e82340` remains `FUN_00e82340` static-body evidence only. The SDK association for `cCellDataReference_::Create` is `0x00e82420`; the relationship between the two addresses is unresolved. Do not treat `0x00e82340` as a fully supported `cCellDataReference_::Create` function or resource-structure identity until an alias/adjacent-function adjudication is committed.

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |
| cCellCellResource | Cell definition/references | VERIFIED_BOUNDED |  |
| cCellEffectMap/cCellBackgroundMap | Effects/background | VERIFIED_BOUNDED |  |
| cCellLook/cCellRandomCreature/cCellPowers | Look/spawn/powers | VERIFIED_BOUNDED |  |
| cCellPopulateResource | Marker/distribution | VERIFIED_BOUNDED |  |
| cCellSerializableData | Serialization metadata | SUPPORTED |  |
| cCellStructureResource/cCellLootTableResource | Structure/loot | VERIFIED_BOUNDED |  |
| cCellWorldResource | Level/advect entries | VERIFIED_BOUNDED |  |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| record_reference_checked | Hard references only | OBSERVED_CURRENT |
| resource_consumed_by_runtime | No original stage trace | UNRESOLVED |
| resource_decoded | Typed output | OBSERVED_CURRENT |

### Transitions

| From | To | Status |
| --- | --- | --- |
| hard reference | resolved record identity | SUPPORTED |
| record bytes | typed resource | VERIFIED_BOUNDED |
| typed resource | original gameplay action | UNRESOLVED |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| src/assets/tests/cell_cell_test.cpp | Cell records and double-decode | ENVIRONMENT_DEPENDENT |
| src/assets/tests/cell_look_test.cpp | Look data | ENVIRONMENT_DEPENDENT |
| src/assets/tests/cell_loot_test.cpp | Loot references | ENVIRONMENT_DEPENDENT |
| src/assets/tests/cell_populate_test.cpp | Markers/references | ENVIRONMENT_DEPENDENT |
| src/assets/tests/cell_structure_test.cpp | Structure references | ENVIRONMENT_DEPENDENT |
| src/assets/tests/cell_world_test.cpp | World/advect | ENVIRONMENT_DEPENDENT |
| src/assets/tests/cellres_test.cpp | Globals | ENVIRONMENT_DEPENDENT |
| tools/spore/cellres/ | Independent Python oracles | FULL_CPP_PYTHON_DIFF_INCOMPLETE |

## PKG-06-CELL-STATE — Cell game state, pool, query, advect, and combat rules

**Scope:** Static and pure reconstructions of selected Cell runtime state/rule functions. The original live state machine and timing are not claimed.

**Confidence:** `SUPPORTED`; basis: Decompilation, Focused unit tests, SDK layouts, Static constants. Unresolved: Field meanings beyond static offsets, Full pool side effects, Original timing/order.

**Membership:** 3 explicit function/root anchors; 27 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=Ghidra/SDK layouts, PKG-01, PKG-05; downstream=PKG-07, PKG-08, PKG-09. Boundary rule: Keep pure state/rule functions separate from approximate CellSim and original live ownership.

**Replacement interface:** `PARTIAL_EXISTING_CONTRACT` — Typed Cell state host. Expose deterministic state transitions and pure predicates. No original singleton, event queue, or live object owner is implied. Target: src/sim/CellGame.hpp; CellPool.hpp; CellQuery.hpp; Advect.hpp; Combat.hpp

**Prerequisites:** Keep generated fixtures labeled non-original; Original pre/post state observation; Resolve shared roots

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | CellGame::createCellObject | Create cell | SUPPORTED_STATIC |
|  | CellGame::Initialize | Static state | OBSERVED_CURRENT |
|  | CellPool allocate/release | Pool | OBSERVED_CURRENT |
|  | CellQuery::queryNear | Near predicate | OBSERVED_CURRENT |
|  | getCurrentAdvectInfo/getNextAdvectID | Advect lookup | SUPPORTED_STATIC |
|  | getScaleDifference/getDamage/shouldNotAttack | Combat rules | SUPPORTED_STATIC |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
| 0x00e74a20 | CreateCellObject | Pool allocation/state fill | SUPPORTED_STATIC |
| 0x00e780a0 | FUN_00e780a0 | Object-pool lifecycle candidate | UNRESOLVED |
| 0x00e80ba0 | cCellGame::Initialize | State initialization | SUPPORTED_STATIC |
|  | cCellQueryLinkedPool | Spatial query | SUPPORTED_STATIC |

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |
| cAdvectEntry/ScaleDifference | Advect/combat types | SUPPORTED_STATIC |  |
| cCellGame | World/pool/avatar/query state | SUPPORTED_STATIC |  |
| cCellObjectData | Per-cell state | SUPPORTED_STATIC |  |
| cCellQueryEntry | Position query node | SUPPORTED_STATIC |  |
| cObjectPool<cCellObjectData> | 4096-cell free list | VERIFIED_BOUNDED |  |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| attack_gate_decided | No runtime event trace | INFERRED |
| cell_created | Resource/state fill | SUPPORTED_STATIC |
| cell_game_initialized | Static writes | OBSERVED_CURRENT |
| near_query | Spatial predicate | SUPPORTED_STATIC |
| pool_allocated | Capacity/free list | SUPPORTED_STATIC |

### Transitions

| From | To | Status |
| --- | --- | --- |
| initialized CellGame | populated pool | SUPPORTED_STATIC |
| player and target | attack decision | INFERRED |
| resource plus scale | cell state | SUPPORTED_STATIC |
| world/advect | current/next advect | SUPPORTED_STATIC |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| src/sim/tests/advect_test.cpp | Buckets/fallback | COVERED |
| src/sim/tests/cellgame_test.cpp | Initialization | COVERED |
| src/sim/tests/cellpool_test.cpp | 4096 capacity/exhaustion/refill | COVERED |
| src/sim/tests/cellquery_test.cpp | Near boundaries | COVERED |
| src/sim/tests/combat_test.cpp | Combat tables | COVERED |
| src/sim/tests/createcell_test.cpp | Size/state fill | COVERED |
| tests/fixtures/cell/fixtures.json | Generated OpenSpore contract | REGRESSION_ONLY |

## PKG-07-CELL-MOVEMENT — Cell movement and mouse-steering replacement

**Scope:** The narrow movement seam centered on MovePlayerToMousePosition, input/camera dependencies, and the clean-room replacement interface.

**Confidence:** `SUPPORTED`; basis: 64/64 reference differential, Byte-verified target, Static decompilation, Synthetic hook. Unresolved: Field meanings/omitted side effects, Live Cell behavior, Pool index versus pointer, Runtime plane point.

**Membership:** 8 explicit function/root anchors; 33 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=camera/UI boundary, PKG-01, PKG-06, PKG-08; downstream=PKG-09, replacement promotion. Boundary rule: Ray-plane structure is supported; lock, pool lookup, runtime plane point, camera/UI gates, omitted callees, and field meanings remain unresolved.

**Replacement interface:** `CONTRACT_DEFINED; REAL_INSTALL_UNVALIDATED` — MovePlayerToMousePosition inline seam. void(float), inherited cdecl frame, balanced stack, documented sCellGame/player fields, target/orientation/moving effects. Mechanism is 5-byte E9 rel32; no Spore patch is installed by this artifact. Target: 0x00e5b790

**Prerequisites:** Independent adjudication; M0 boot control; M1 Cell reachability; M2 read-only ABI observation

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |
| 0x00e51010 | OnMouseMove | Mouse input | STATIC; RUNTIME_UNOBSERVED |
| 0x00e818f0 | OnKeyDown | Key input | STATIC; RUNTIME_UNOBSERVED |
|  | CellSim::update | OpenSpore contract sim | APPROXIMATION |
|  | reference_MovePlayerToMousePosition | Decompiler reference | EVIDENCE_NOT_TRUTH |
|  | replacement_MovePlayerToMousePosition | Replacement | OBSERVED_CURRENT |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
| 0x007c4900 | cam_light_origin_FUN_007c4900 | Ray source | STATIC |
| 0x00b721d0 | player_getter_FUN_00b721d0 | Player lookup | STATIC |
| 0x00e5b2e0 | cell_per_frame_FUN_00e5b2e0 | Update callee | STATIC |
| 0x00e5b790 | MovePlayerToMousePosition | Camera-ray/plane steering | CONFIRMED_NAME; STATIC_BODY |
| 0x00e806b0 | cell_update_body_FUN_00e806b0 | Cell update body | SUPPORTED_STATIC |
| 0x00e80980 | cCellModeStrategy::Update | Per-frame entry | STATIC |

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |
| Camera/light view ray | Movement input | INFERRED |  |
| cCellObjectData | Target/orientation/current | SUPPORTED_STATIC |  |
| MovementPlane | Normal {0,0,1}; load-time point {0,0,0} | NORMAL_VERIFIED; RUNTIME_POINT_UNRESOLVED |  |
| sCellGame | Gameplay state/player index | CONFIRMED_GLOBAL; MEANINGS_INFERRED |  |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| key_down | Input | STATIC; RUNTIME_UNOBSERVED |
| mouse_move | Input | STATIC; RUNTIME_UNOBSERVED |
| movement_target_written | Ray-plane stores | SUPPORTED_STATIC |
| moving_flag_set | sCellGame candidate | SUPPORTED_STATIC; MEANING_INFERRED |
| orientation_written | Player stores | SUPPORTED_STATIC; MEANING_INFERRED |

### Transitions

| From | To | Status |
| --- | --- | --- |
| input to original event attribution | observed behavior | UNRESOLVED |
| mouse/camera input | ray-plane target | SUPPORTED_STATIC |
| target/current | orientation helper | SUPPORTED_STATIC |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| src/replace/Reference.cpp | Decompiler reference with omission boundary | EVIDENCE_NOT_TRUTH |
| src/replace/tests/diff_test.cpp | 8 cases x 8 fields; recorded 64/64 match | DECOMP_REFERENCE_ONLY |
| src/sim/tests/sim_contract_test.cpp | OpenSpore movement replay | REGRESSION_ONLY |
| tools/observatory/probes/cell_movement.json | Byte-verified 12-probe set | DEFINED; CELL_EVENTS_ABSENT |
| tools/replace/synthetic/ | Native 32-bit hook mechanism | MECHANISM_ONLY |

## PKG-08-CELL-MODE — Cell mode lifecycle and input routing

**Scope:** The original cCellModeStrategy vtable-shaped lifecycle and clean-room IGameMode host boundary. It does not own GFX/UI presentation or the movement body.

**Confidence:** `SUPPORTED`; basis: Mode tests, SDK vtable names, Static decompilation. Unresolved: Input timing, Original dispatch order, Other stage modes.

**Membership:** 6 explicit function/root anchors; 45 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=PKG-01, PKG-02, PKG-18; downstream=future modes, PKG-07, PKG-09. Boundary rule: IGameMode is a host-side reuse seam, not proof of original app-system behavior.

**Replacement interface:** `EXISTING_CLEAN_ROOM_INTERFACE` — IGameMode lifecycle manager. Initialize -> OnEnter -> Update* -> OnExit -> Dispose with table-driven input. This is host-side reuse; original transition claims require a trace. Target: src/apps/IGameMode.hpp:28; src/apps/CellModeStrategy.cpp

**Prerequisites:** Correlate SetActiveModeAt with callbacks; M1 Cell reachability; Separate host tests from original claims

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | GameModeManager::setActiveModeAt | Clean-room switch | OBSERVED_CURRENT |
|  | Initialize/OnEnter/Update/OnExit/Dispose | Lifecycle surface | SUPPORTED_STATIC |
|  | OnKeyDown/OnMouseMove/OnMouseDown/OnMouseUp/OnMouseWheel | Input surface | SUPPORTED_STATIC |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
| 0x007d8d40 | SetActiveModeAt | Mode manager | STATIC |
| 0x00e552f0 | OnEnter | Mode entry | STATIC |
| 0x00e7fc00 | OnExit | Mode exit | STATIC |
| 0x00e80980 | Update | Per-frame update | STATIC |
| 0x00e81cf0 | cCellModeStrategy::Initialize | Mode init | STATIC |
| 0x00e81f30 | Dispose | Teardown | STATIC |

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |
| App::cCellModeStrategy | 27-slot vtable-shaped object | SUPPORTED_STATIC |  |
| cGameModeManager | Active mode | SUPPORTED_STATIC |  |
| IGameMode | Clean-room lifecycle/input | OBSERVED_CURRENT | src/apps/IGameMode.hpp:28 |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| input_event | Original input | STATIC; RUNTIME_UNOBSERVED |
| mode_enter | Lifecycle | SUPPORTED_STATIC |
| mode_exit | Lifecycle | SUPPORTED_STATIC |
| mode_initialize | Lifecycle | SUPPORTED_STATIC |
| mode_update | Per-frame dispatch | STATIC; RUNTIME_UNOBSERVED |

### Transitions

| From | To | Status |
| --- | --- | --- |
| Initialize | OnEnter | STATIC_VTABLE_CONTRACT |
| OnEnter | Update* | STATIC_VTABLE_CONTRACT |
| SetActiveModeAt | old OnExit/new OnEnter | INFERRED; runtime unresolved |
| Update* | OnExit/Dispose | STATIC_VTABLE_CONTRACT |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| src/apps/cellinput_test.cpp | Key/action/toggle | COVERED_CURRENT |
| src/apps/cellmode_test.cpp | Lifecycle/mode switch | COVERED_CURRENT |
| tools/observatory/probes/cell_movement.json | Lifecycle/input probes | DEFINED; EVENTS_ABSENT |
| tools/observatory/probes/menu_transition.json | Mode/editor transition | DEFINED_NOT_RUN |

## PKG-09-CELL-PRESENTATION — Cell GFX, HUD, scene assembly, and renderer boundary

**Scope:** The current vertical-slice presentation path and original cCellGFX/cCellUI/resource-preload anchors. Pixel fidelity and original placement remain unresolved.

**Confidence:** `SUPPORTED`; basis: Asset/scene tests, Deterministic vertical slice, Static GFX/UI anchors. Unresolved: HUD timing/drawing, Original placement, Preload order, Renderer/material/light.

**Membership:** 7 explicit function/root anchors; 112 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=PKG-03, PKG-04, PKG-05, PKG-08; downstream=B3 IRenderer, interactive presentation, original renderer oracle. Boundary rule: Do not promote Vulkan pixels, fixed lighting, or scene positions to original semantics.

**Replacement interface:** `EXISTING_REPLACEMENT_SEAMS` — B1/B2/B3 composition seam. Compose provider bytes, provider-independent meshes, and renderer submission. Original placement, material/light behavior, and HUD rendering remain outside the guarantee. Target: src/compat/ResourceProvider.hpp:24; MeshSource.hpp:26; Renderer.hpp:46

**Prerequisites:** Decoded placement fixture; M0/M1 Cell trace; Matched original render capture

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | CellGfx::initialize | World table | OBSERVED_CURRENT |
|  | CellGfx::preloadResources | Record preload | OBSERVED_CURRENT |
|  | CellUI::load/showHealthRollover | HUD | SUPPORTED_STATIC |
|  | loadSceneConfig | Checked-in scene | OBSERVED_CURRENT |
|  | submitMeshSource/beginPresentFrame/draw | Host submission | OBSERVED_CURRENT |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
| 0x00e54270 | cCellUI::Load | HUD load | SUPPORTED_STATIC |
| 0x00e55120 | StartDisplay | Display activation | SUPPORTED_STATIC |
| 0x00e5dba0 | cCellGFX::Initialize | GFX worlds/layers | SUPPORTED_STATIC |
| 0x00e62340 | ShowHealthRollover | Health rollover | SUPPORTED_STATIC |
| 0x00e663b0 | PreloadCellResource | Cell preload | SUPPORTED_STATIC |
| 0x00e665c0 | PreloadPopulateResource | Populate preload | SUPPORTED_STATIC |
| 0x00e666f0 | PreloadResources | Resource preload | SUPPORTED_STATIC |

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |
| cCellGFX | World/layer/preload state | SUPPORTED_STATIC |  |
| cCellUI/cCellUIRollover | HUD/health | SUPPORTED_STATIC |  |
| SceneEntity | OpenSpore scene contract | OBSERVED_CURRENT | src/apps/SceneConfig.hpp |
| World-object records | Model/scene data | PARTIAL; PLACEMENT_UNRESOLVED |  |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| display_started | StartDisplay | SUPPORTED_STATIC |
| frame_drawn | OpenSpore Vulkan frame | OBSERVED_CURRENT |
| gfx_initialized | World table | SUPPORTED_STATIC |
| health_rollover_shown | Rollover formula | SUPPORTED_STATIC; TIMING_UNOBSERVED |
| hud_loaded | HUD constants | SUPPORTED_STATIC |
| resource_preloaded | Record/handle state | SUPPORTED_STATIC; ORDER_UNOBSERVED |

### Transitions

| From | To | Status |
| --- | --- | --- |
| decoded records | GFX preload/scene | SUPPORTED_BOUNDED |
| host draw | original rendered frame | UNRESOLVED |
| scene entities | host draw submission | OBSERVED_CURRENT |
| world/populate | original x/y placement | UNRESOLVED |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| src/apps/cellgfx_test.cpp | World IDs/handles/layers | COVERED |
| src/apps/cellui_test.cpp | HUD/rollover | COVERED |
| src/apps/scene.json | Six entities | FIXTURE; PLACEMENT_UNRESOLVED |
| src/apps/scene_config_test.cpp | Scene round-trip/provenance | COVERED_CURRENT |
| tests/test_cellstage.py | Manifest determinism | ENVIRONMENT_DEPENDENT |

## PKG-10-EDITOR-DISPATCH — Editor and UTFWin message/input dispatch

**Scope:** Editor lifecycle and message-pump boundary needed before claiming menu-to-stage or UI-driven resource behavior.

**Confidence:** `SUPPORTED`; basis: Defined probe set, Historical startup only, SDK names, Static decompilation. Unresolved: Menu-to-stage transition, Message order, UI-to-resource causality.

**Membership:** 6 explicit function/root anchors; 1409 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=PKG-02, PKG-03, PKG-18; downstream=PKG-11, PKG-12, PKG-13, PKG-15. Boundary rule: Do not infer a stage or resource transition from screenshots or a generic frame callback.

**Replacement interface:** `UNRESOLVED` — Message/input dispatch boundary. A future interface needs timestamped message/input events and a stage-transition callback. Existing host mode/input interfaces do not define original UTFWin behavior. Target: None

**Prerequisites:** Approved focused input; Correlated input/message/resource/frame events; M0 positive boot

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | HandleMessage | Message dispatch | SUPPORTED_STATIC |
|  | OnMouseDown/OnKeyDown | Input callbacks | SUPPORTED_STATIC |
|  | SetActiveMode/SetEditorModel | Editor state | SUPPORTED_STATIC |
|  | Update | Per-frame editor | SUPPORTED_STATIC |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
| 0x00588570 | cEditor::OnMouseDown | Mouse event | SUPPORTED_STATIC |
| 0x0058ac10 | cEditor::OnKeyDown | Key event | SUPPORTED_STATIC |
| 0x0058be50 | cEditor::Update | Per-frame update | SUPPORTED_STATIC |
| 0x00591fa0 | cEditor::HandleMessage | Message dispatch | SUPPORTED_STATIC |
| 0x00848210 | MessagePump::PeekDispatch | Message pump | STATIC |
| 0x00b63980 | Frame::TimeAtStartOfFrame | Frame annotation | STATIC |

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |
| Editors::cEditor | Message/input handlers | CONFIRMED_NAME |  |
| UTFWin::UTFWinObject | UI hierarchy | CONFIRMED_NAME |  |
| UTFWin::Window | Window/message | CONFIRMED_NAME |  |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| editor_update | Frame callback | STATIC; NOT_OBSERVED |
| input_event | UI callback | STATIC; ATTRIBUTION_UNRESOLVED |
| message_pump | Dispatch boundary | STATIC; NOT_OBSERVED |
| resource_transition | Input/message/resource correlation | PROPOSED; NOT_OBSERVED |

### Transitions

| From | To | Status |
| --- | --- | --- |
| editor update | frame heartbeat | ANNOTATION_ONLY |
| input event | message/cEditor callback | INFERRED |
| message dispatch | resource load | UNRESOLVED |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| tests/test_menu_walk.py | Safety/input allowlist | MECHANISM_ONLY |
| tools/observatory/examples/obs_main_menu_example.jsonl | Startup control | HISTORICAL_NOT_TRANSITION |
| tools/observatory/probes/menu_transition.json | Message/editor/resource/frame probes | DEFINED_NOT_RUN |

## PKG-11-SIM-CORE — Simulator core managers, tools, and missions

**Scope:** Broad Simulator gameplay-support surface outside Cell. Static named functions are preserved; tool behavior, missions, and state ownership are unresolved.

**Confidence:** `INFERRED`; basis: Dependency projections, SDK names, Static decompilation. Unresolved: Manager ownership/order, Mission lifecycle, Runtime semantics, Tool behavior.

**Membership:** 6 explicit function/root anchors; 1628 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=PKG-01, PKG-02, PKG-03, PKG-10; downstream=PKG-12, PKG-13, PKG-20. Boundary rule: Do not merge tool, mission, and manager semantics into Cell semantics.

**Replacement interface:** `UNRESOLVED` — Simulator tool/manager contract. No replacement interface is defined until manager roots, tool event ordering, and stage ownership are characterized. Target: None

**Prerequisites:** Characterize manager roots; Obtain stage-specific trace; Resolve decomp/unknown callees

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | cDefaultAoETool::OnMouseDown | Mouse action | SUPPORTED_STATIC |
|  | cDefaultBeamTool::func4Ch | Beam virtual | SUPPORTED_STATIC |
|  | cObjectPool_::DeleteObject | Deletion | SUPPORTED_STATIC |
|  | cToolStrategy::OnSelect | Selection | SUPPORTED_STATIC |
|  | IsNotStarOrBinaryStar | Predicate | SUPPORTED_STATIC |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
| 0x00b72370 | cObjectPool_::DeleteObject | Object deletion | SUPPORTED_STATIC |
| 0x00c8b6b0 | IsNotStarOrBinaryStar | Predicate | SUPPORTED_STATIC |
| 0x01052f90 | cDefaultAoETool::OnMouseDown | Tool input | SUPPORTED_STATIC |
| 0x01053790 | cToolStrategy::OnSelect | Tool selection | SUPPORTED_STATIC |
| 0x01053db0 | cDefaultBeamTool::func4Ch | Beam virtual | SUPPORTED_STATIC |
| 0x01054080 | cGetOutOfUFOToolStrategy::OnSelect | Special tool | SUPPORTED_STATIC |

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |
| cDefaultAoETool/cDefaultBeamTool/cGetOutOfUFOToolStrategy | Tool variants | CONFIRMED_NAME |  |
| cGameModeManager/cMissionManager/cGameData | Manager families | NAME_LEVEL_ONLY |  |
| cObjectPool_ | Generic pool | CONFIRMED_NAME |  |
| cToolStrategy | Tool hierarchy | CONFIRMED_NAME |  |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| mission_update | No mission event contract | UNRESOLVED |
| object_deleted | Pool | STATIC; RUNTIME_UNOBSERVED |
| tool_input | Mouse action | STATIC; RUNTIME_UNOBSERVED |
| tool_selected | Tool strategy | STATIC; RUNTIME_UNOBSERVED |

### Transitions

| From | To | Status |
| --- | --- | --- |
| allocation | object deletion | STATIC_CONTRACT; SIDE_EFFECTS_UNRESOLVED |
| tool selection | tool update/input | STATIC_VTABLE_CONTRACT; RUNTIME_UNOBSERVED |
| tool/input | gameplay state | UNRESOLVED |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| knowledgegraph/triage/queue-f0e310e0-v6.json | Named P0 tool functions/dependencies | READ_ONLY_EVIDENCE |
| knowledgegraph/triage/reconstruction-readiness-f0e310e0.json | Dependency-first classification | READ_ONLY_EVIDENCE |

## PKG-12-SIM-SPACE — Simulator Space stage

**Scope:** Space, stars, planets, trading, and terraforming. SDK names and one bounded predicate exist; no current implementation or runtime oracle exists.

**Confidence:** `INFERRED`; basis: One decomp-backed predicate, SDK namespace names, Triage cluster. Unresolved: All stage transitions, fields, events, and replacement behavior.

**Membership:** 2 explicit function/root anchors; 8 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=PKG-01, PKG-03, PKG-11, PKG-14; downstream=Space-specific contract. Boundary rule: Do not infer behavior from SDK class names or one predicate.

**Replacement interface:** `UNRESOLVED` — None. No replacement interface. First characterize entry, state ownership, and event vocabulary. Target: None

**Prerequisites:** Map Space VAs/vtables; Obtain Space-stage trace; Resolve roots

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | cStarManager/cSpaceTrading functions | SDK families | UNRESOLVED_VA_MAPPING |
|  | IsNotStarOrBinaryStar | Static predicate | SUPPORTED_STATIC |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
| 0x00b3d4d0 | cSpaceTrading::Get | Service root; owned by PKG-01 | SUPPORTED |
| 0x00c8b6b0 | IsNotStarOrBinaryStar | Space predicate | SUPPORTED_STATIC |
|  | cluster:sim-space | Space SDK slice | NEAR_READY_TRIAGE |

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |
| cSolarSystem/cPlanetModel/cStarRecord | System/planet records | NAME_LEVEL_ONLY |  |
| cStarManager/cSpaceTrading | Star/trading services | NAME_LEVEL_ONLY |  |
| cTerraformingManager/cScenarioTerraformMode | Terraforming | NAME_LEVEL_ONLY |  |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| space_stage_enter | No trace | UNRESOLVED |
| terraforming_update | No event contract | UNRESOLVED |
| trade_action | No event contract | UNRESOLVED |

### Transitions

| From | To | Status |
| --- | --- | --- |
| Space stage entry | star/planet state | UNRESOLVED |
| planet state | trade/terraform action | UNRESOLVED |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| knowledgegraph/triage/clusters-f0e310e0-v6.json | Space cluster | READ_ONLY_EVIDENCE |
| knowledgegraph/triage/queue-f0e310e0-v6.json | P0 predicate | READ_ONLY_EVIDENCE |

## PKG-13-SIM-CREATURE-TRIBECIV — Simulator creature, tribe, and civilization stage

**Scope:** Creature/city/tribe/civilization SDK surface. Static names exist, but the stage is unimplemented and untraced.

**Confidence:** `UNKNOWN`; basis: SDK names and triage category only. Unresolved: All stage semantics, events, transitions, fields, and replacement behavior.

**Membership:** 0 explicit function/root anchors; 11 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=PKG-01, PKG-03, PKG-11, PKG-14; downstream=Creature-specific contract. Boundary rule: Keep Creature/Tribe/Civ separate from Cell and resource decoding.

**Replacement interface:** `UNRESOLVED` — None. No interface until stage entry, entity ownership, and event order are characterized. Target: None

**Prerequisites:** Map VAs/structures; Obtain stage trace; Resolve roots and stage manager

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | cCreatureBase/cCreatureGameData/cCity functions | Creature/city family | UNRESOLVED |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | cCity functions | City state | UNRESOLVED_VA_MAPPING |
|  | cCreatureBase functions | Creature state | UNRESOLVED_VA_MAPPING |
|  | cluster:sim-creature-tribeciv | Creature/tribe/city slice | NEAR_READY_TRIAGE |

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |
| cCity/cTribeArchetype | City/tribe | NAME_LEVEL_ONLY |  |
| cCollectableItems/cCommManager/cRelationshipManager/cPlayerInventory | Support families | NAME_LEVEL_ONLY |  |
| cCreatureBase/cCreatureGameData | Creature data | NAME_LEVEL_ONLY |  |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| creature_stage_enter | No trace | UNRESOLVED |
| relationship/inventory change | No event contract | UNRESOLVED |
| tribe/city update | No event contract | UNRESOLVED |

### Transitions

| From | To | Status |
| --- | --- | --- |
| Creature stage entry | creature/city state | UNRESOLVED |
| creature state | tribe/civ action | UNRESOLVED |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| knowledgegraph/triage/clusters-f0e310e0-v6.json | Creature cluster/vtable guidance | READ_ONLY_EVIDENCE |
| knowledgegraph/triage/queue-f0e310e0-v6.json | SDK/decomp-backed functions | READ_ONLY_EVIDENCE |

## PKG-14-TERRAIN-WORLD — Terrain, planet surface, and world rendering

**Scope:** Terrain SDK/rendering boundary and its joint with Space. Gameplay semantics are not assigned here.

**Confidence:** `UNKNOWN`; basis: Cluster and SDK/render-boundary names. Unresolved: Terrain state, events, transitions, and rendering semantics.

**Membership:** 0 explicit function/root anchors; 112 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=graphics boundary, PKG-04, PKG-12; downstream=Space/planet presentation. Boundary rule: Keep terrain rendering separate from game state and modern Vulkan.

**Replacement interface:** `UNRESOLVED` — None. No terrain replacement interface; B3 can carry host mesh/frame data only. Target: None

**Prerequisites:** Capture matched original terrain frame; Map terrain/planet VAs; Obtain Space trace

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | cTerrainSphere::Land/Atmosphere/Decals | Terrain rendering | UNRESOLVED_VA_MAPPING |
|  | Quad::Draw | Terrain submission | UNRESOLVED_VA_MAPPING |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | cluster:terrain-world | Terrain/planet slice | NEAR_READY_TRIAGE |
|  | cTerrainSphere render trio | Land/atmosphere/decals | STATIC_NAME_ANCHOR |
|  | Quad::Draw | Terrain draw | STATIC_NAME_ANCHOR |

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |
| cPlanetModel | Space-surface joint | NAME_LEVEL_ONLY |  |
| cTerrainSphere | Terrain sphere | NAME_LEVEL_ONLY |  |
| Quad | Terrain surface | NAME_LEVEL_ONLY |  |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| atmosphere_update | No event contract | UNRESOLVED |
| planet_surface_transition | No stage trace | UNRESOLVED |
| terrain_draw | No matched original frame | UNRESOLVED |

### Transitions

| From | To | Status |
| --- | --- | --- |
| planet model | terrain sphere | UNRESOLVED |
| terrain sphere | original surface | UNRESOLVED |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| docs/RENDERWARE-RESEARCH.md | Graphics research | SECONDARY_REFERENCE |
| knowledgegraph/triage/clusters-f0e310e0-v6.json | Terrain cluster/join | READ_ONLY_EVIDENCE |

## PKG-15-EDITOR-SUPPORT — Palettes, Skinner, and editor support

**Scope:** Editor support families adjacent to editor/graphics boundaries; static functions are not merged into the editor command model.

**Confidence:** `INFERRED`; basis: Queue readiness, SDK names, Static decompilation. Unresolved: Editor boundary, Runtime order, Texture-paint semantics.

**Membership:** 3 explicit function/root anchors; 100 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=PKG-03, PKG-04, PKG-10; downstream=Editor replacement/tool contracts. Boundary rule: Do not assign gameplay or stage transitions to support functions.

**Replacement interface:** `UNRESOLVED` — None. No interface until editor/viewer boundaries are characterized. Target: None

**Prerequisites:** Add focused static contracts; Map support VAs/vtables; Resolve editor/graphics dependencies

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |
| 0x004ae250 | EditorModel::SetColor | Color update | READY_STATIC |
|  | AdvancedItemViewer::func40h | Viewer virtual | SUPPORTED_STATIC |
|  | cSkinnerTexturePainter::PaintRegion/StartRender/EndRender | Texture-paint bridge | UNRESOLVED_VA_MAPPING |
|  | PalettePage::Load | Palette load | READY_STATIC |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
| 0x005c8bc0 | PalettePage::Load | Palette load | READY_STATIC |
| 0x005f4750 | AdvancedItemViewer::func40h | Viewer virtual | SUPPORTED_STATIC |
|  | cSkinnerTexturePainter | Texture-paint bridge | NEAR_READY_TRIAGE |

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |
| AdvancedItemViewer | Viewer | CONFIRMED_NAME |  |
| cSkinnerTexturePainter | Texture painter | NAME_LEVEL_ONLY |  |
| EditorModel | Editor model | CONFIRMED_NAME |  |
| PalettePage | Palette page | CONFIRMED_NAME |  |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| editor_model_color_set | Model state | READY_STATIC; RUNTIME_UNOBSERVED |
| palette_loaded | Support | STATIC; RUNTIME_UNOBSERVED |
| texture_paint_start_end | No event contract | UNRESOLVED |

### Transitions

| From | To | Status |
| --- | --- | --- |
| palette/editor data | viewer/model state | INFERRED_FROM_NAMES; ORDER_UNRESOLVED |
| texture-paint input | editor texture | UNRESOLVED |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| knowledgegraph/triage/queue-f0e310e0-v6.json | Palette/editor support P0/vtable evidence | READ_ONLY_EVIDENCE |
| knowledgegraph/triage/reconstruction-readiness-f0e310e0.json | READY support functions | READ_ONLY_EVIDENCE |

## PKG-16-SPOREPEDIA-ONLINE — Sporepedia asset data and online boundary

**Scope:** Sporepedia asset metadata and any online/Pollinator boundary. Online behavior is not a first-pass reconstruction target without a no-network contract.

**Confidence:** `INFERRED`; basis: Queue readiness, SDK names, Static decompilation. Unresolved: Caller order, Full asset object semantics, Online behavior.

**Membership:** 5 explicit function/root anchors; 100 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=PKG-03, PKG-18; downstream=Future Sporepedia boundary. Boundary rule: Keep network behavior stubbed or observation-only until a non-network contract exists.

**Replacement interface:** `NOT_IMPLEMENTED` — Asset metadata read boundary. A local interface may expose editability, name presence, and asset ID. Online request/response behavior remains unresolved and out of scope. Target: None

**Prerequisites:** Blocked/faked network paths; Caller/event characterization; Minimum local asset-data fixture

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | func7Ch/func3Ch | Asset data virtuals | SUPPORTED_STATIC |
|  | GetAssetID | Asset ID | READY_STATIC |
|  | HasName | Name presence | READY_STATIC |
|  | IsEditable | Editability | READY_STATIC |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
| 0x00641400 | cSPAssetDataOTDB::IsEditable | Editability predicate | READY_STATIC |
| 0x00641460 | cSPAssetDataOTDB::func7Ch | Asset virtual | SUPPORTED_STATIC |
| 0x00641770 | HasName | Name predicate | READY_STATIC |
| 0x006417b0 | func3Ch | Asset virtual | SUPPORTED_STATIC |
| 0x006417c0 | GetAssetID | Asset ID | READY_STATIC |

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |
| Sporepedia request/response structures | Online boundary | UNRESOLVED |  |
| Sporepedia::cSPAssetDataOTDB | Asset data object | CONFIRMED_NAME |  |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| asset_metadata_query | Local data | STATIC; RUNTIME_UNOBSERVED |
| editability_result | Function return | READY_STATIC; RUNTIME_UNOBSERVED |
| online_request | No network oracle | UNRESOLVED |

### Transitions

| From | To | Status |
| --- | --- | --- |
| asset data | metadata result | STATIC_FUNCTION_CONTRACT; CALLER_UNRESOLVED |
| local metadata | online service | UNRESOLVED |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| knowledgegraph/triage/clusters-f0e310e0-v6.json | Sporepedia/Pollinator cluster/vtable | READ_ONLY_EVIDENCE |
| knowledgegraph/triage/queue-f0e310e0-v6.json | Sporepedia READY functions | READ_ONLY_EVIDENCE |

## PKG-17-ANIMATION-SWARM — Cell animation and swarm/creature animation boundary

**Scope:** Animation state/effect mapping evidenced by Cell animation records and selected functions; swarm semantics remain unresolved.

**Confidence:** `INFERRED`; basis: Cell animation names, CellAnim tests, Static decompilation. Unresolved: All swarm semantics, Blend/effect timing, Event order, CellAnim-to-stage/renderer/pose integration and pose-state policy.

**Membership:** 1 explicit function/root anchors; 96 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=graphics/material boundary, PKG-05, PKG-09; downstream=Cell/creature visual contracts. Boundary rule: Animation names and host constants do not establish original timing, blend, or swarm semantics.

**Replacement interface:** `PARTIAL_EXISTING_CONTRACT` — Animation event/effect boundary. Expose animation selection, effect lookup, and effect instance events as a host contract. Original timing/blend and swarm semantics remain unresolved. Target: src/apps/CellAnim.cpp

**Prerequisites:** Matched visual/state trace; Original animation callback/event source; Demonstrate the `SimEvent` → `CellAnim` → stage/renderer/pose path and pose upload/state policy; Swarm identity

**Unresolved question:** What original event path connects `CellAnim` selection/effect state to the Cell stage, renderer, skeleton, or uploaded pose? **Stopping condition:** Keep this package partial/static until a provenance-bearing event-to-pose/render trace establishes ownership, ordering, pose lifecycle, and renderer submission; unit-tested `CellAnim` helpers alone do not satisfy the gate.

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | CellAnim blend/event/effect mapping | Host contract | OBSERVED_CURRENT |
|  | PlayAnimation | Cell animation | SUPPORTED_STATIC |
|  | Swarm animation functions | Swarm family | UNRESOLVED_VA_MAPPING |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
| 0x00e6d200 | PlayAnimation | Cell animation | SUPPORTED_STATIC |
|  | cCellAnimDefinition | Cell animation state | NAME_LEVEL_ONLY |
|  | cluster:swarm-anim | Swarm animation slice | BLOCKED_ON_IDENTIFICATION |

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |
| cCellAnimDefinition | Cell animation | NAME_LEVEL_ONLY |  |
| cCellEffectMapResource | Effect mapping | VERIFIED_AS_RECORD |  |
| Swarm animation structures | Swarm state | UNRESOLVED |  |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| animation_event | No trace | INFERRED_FROM_STATE_NAMES |
| animation_played | Cell | STATIC; RUNTIME_UNOBSERVED |
| effect_instance | Host mapping | OBSERVED_CURRENT |
| swarm_animation_event | No semantics | UNRESOLVED |

### Transitions

| From | To | Status |
| --- | --- | --- |
| animation event | original visual state | UNRESOLVED |
| animation/effect record | Cell effect | SUPPORTED_BOUNDED |
| swarm state | swarm animation | UNRESOLVED |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| docs/CELLSTAGE-RECON.md | Cell animation state names | SECONDARY_EVIDENCE |
| src/apps/cellanim_test.cpp | Blend/effect/event mapping | COVERED_CURRENT |
| src/assets/tests/effectmap_test.cpp | Effect map decode | ENVIRONMENT_DEPENDENT |

## PKG-18-UI-SCRIPTING — UTFWin UI shell and scripting/content boundary

**Scope:** Broad UTFWin/UI/scripting infrastructure cluster. Only bounded anchors and the safe observation shell exist; no UI shell reconstruction is proposed.

**Confidence:** `INFERRED`; basis: Message-pump anchor, Safety shell, SDK names, Triage cluster. Unresolved: Scripting semantics, UI-to-stage order, UTFWin behavior.

**Membership:** 1 explicit function/root anchors; 1191 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=PKG-02, PKG-03, PKG-10; downstream=PKG-11, PKG-12, PKG-13, PKG-16. Boundary rule: Treat UI/scripting as infrastructure until an event trace establishes gameplay role.

**Replacement interface:** `UNRESOLVED` — UI/message boundary. No replacement interface. The safe menu-walk shell is an observation tool, not a UI reimplementation. Target: None

**Prerequisites:** Approved fixed input; M0 positive boot; Stage/message/resource transition trace

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | ArgScript::FormatParser and related | Scripting | NAME_LEVEL_STATIC |
|  | ui-shell functions | UI shell | UNRESOLVED_VA_MAPPING |
|  | UTFWin object/message functions | UI framework | PARTIAL_STATIC_MAP |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
| 0x00848210 | MessagePump::PeekDispatch | Message pump anchor | STATIC; PACKAGE-10-DISPATCH-OWNER |
|  | cluster:scripting-content | 84 scripting/content functions | READY_TRIAGE |
|  | cluster:ui-shell | 13 UI functions | NEAR_READY_TRIAGE |
|  | cluster:utfwin-framework | 1,093 UI functions | READY_TRIAGE |

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |
| ArgScript runtime structures | Scripting/content | UNRESOLVED |  |
| UTFWin::UTFWinObject | UI hierarchy | CONFIRMED_NAME |  |
| UTFWin::Window | Window/message | CONFIRMED_NAME |  |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| content_load | No semantics | UNRESOLVED |
| script_parse | No fixture/trace | UNRESOLVED |
| ui_message | Input correlation | PROBE_ANCHOR; ORDER_UNRESOLVED |

### Transitions

| From | To | Status |
| --- | --- | --- |
| UI callback | stage/resource | UNRESOLVED |
| input/message pump | UI callback | INFERRED; trace required |
| script bytes | script state | UNRESOLVED |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| knowledgegraph/triage/clusters-f0e310e0-v6.json | Cluster/vtable signals | READ_ONLY_EVIDENCE |
| tests/test_agent_overlay.py | Overlay self-test | MECHANISM_ONLY |
| tests/test_menu_walk.py | Safe GUI walk/input allowlist | MECHANISM_ONLY |

## PKG-19-AUDIO-INPUT — Audio and original input marshalling

**Scope:** Low-evidence audio/input cluster. No semantic reconstruction is proposed from names alone.

**Confidence:** `UNKNOWN`; basis: Triage category only. Unresolved: All functions, structures, events, transitions, and replacement behavior.

**Membership:** 0 explicit function/root anchors; 11 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=PKG-01, PKG-18, runtime/display evidence; downstream=none. Boundary rule: Do not fold original audio/input behavior into CellInput or host SDL.

**Replacement interface:** `UNRESOLVED` — None. No interface. Identify the original function family and event contract first. Target: None

**Prerequisites:** Bounded original trace; Negative no-audio/no-input contract; Resolve cluster identity/VA mapping

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | cluster:audio-input | 11-function slice | BLOCKED_ON_IDENTIFICATION |

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| audio_event | No function map/trace | UNRESOLVED |
| input_marshalling_event | Original input unobserved | UNRESOLVED |

### Transitions

| From | To | Status |
| --- | --- | --- |
| audio request | audio backend | UNRESOLVED |
| original input | game input manager | UNRESOLVED |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| tests/test_cell_trace.py | Observation-shell input safety | MECHANISM_ONLY |
| tools/observatory/probes/cell_movement.json | Cell input callback probes only | DEFINED; EVENTS_ABSENT |

## PKG-20-GAMEGLOBAL — GameGlobal miscellaneous state

**Scope:** GameGlobal miscellaneous cluster centered on the high-fan-in map lookup candidate. No manager identity or map semantics is asserted.

**Confidence:** `UNKNOWN`; basis: Fan-in/triage classification only. Unresolved: Map type, ownership, events, transitions, and replacement behavior.

**Membership:** 1 explicit function/root anchors; 39 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=Ghidra xrefs, PKG-01; downstream=PKG-11, PKG-12, PKG-13. Boundary rule: Characterize map type/key/value contract before assigning it to gameplay.

**Replacement interface:** `UNRESOLVED` — None. No interface until type, key domain, mutation rules, and consumers are characterized. Target: None

**Prerequisites:** Add field/caller contract; Decompile map_int_whatever_find; Identify owner/offsets

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |
| 0x00e5c780 | map_int_whatever_find | Map lookup | NEEDS_RE |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
| 0x00e5c780 | map_int_whatever_find | Map lookup candidate | NEEDS_RE |
|  | cluster:gameglobal-misc | 39-function slice | BLOCKED_ON_IDENTIFICATION |

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |
| GameGlobal namespace/state | Shared global state | UNRESOLVED |  |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| global_map_lookup | Key/value/event meaning unknown | UNRESOLVED |

### Transitions

| From | To | Status |
| --- | --- | --- |
| GameGlobal state | map result | UNRESOLVED |
| map result | gameplay consumer | UNRESOLVED |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| knowledgegraph/triage/reconstruction-readiness-f0e310e0.json | NEEDS_RE/foundation ranking | READ_ONLY_EVIDENCE |
| knowledgegraph/triage/xrefs-2540f2ca.tsv | Caller/callee structure | READ_ONLY_EVIDENCE |

## PKG-21-UNKNOWN-ROUTING — Unknown vtable implementations and unknown function mass

**Scope:** Unresolved routing and ownership backlog. This package records unknowns rather than splitting the long tail into speculative subsystems.

**Confidence:** `UNKNOWN`; basis: Exact accounting of unknown rows, No package-specific bodies/runtime evidence. Unresolved: 1,598 unknown gameplay rows, 39,716 unknown canonical rows, All ownership/events here.

**Membership:** 1 explicit function/root anchors; 49363 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=debt map, Ghidra decompilation capacity, triage-v6, xref export; downstream=PKG-01, PKG-11, PKG-12, PKG-13, PKG-20. Boundary rule: Do not create per-region semantic packages from fan-in, namespace, vtable proximity, or FUN_* names alone.

**Replacement interface:** `UNRESOLVED` — None. No interface. Resolve identity/ownership first; unresolved rows stay outside implementation scope. Target: None

**Prerequisites:** Decompile/adjudicate UNKNOWN-HIGH roots; Keep unresolved rows out of promotion; Resolve vtable ownership

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | UNKNOWN-HIGH debt rows | Adjudication candidates | UNRESOLVED |
|  | unknown-vtable implementations | Class/slot ownership candidates | UNRESOLVED |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
| 0x00e780a0 | FUN_00e780a0 | Cross-listed object-pool lifecycle candidate | UNRESOLVED |
|  | cluster:unknown-fun-mass | 44,978 rows; 862 UNKNOWN-HIGH remain | BLOCKED_ON_IDENTIFICATION |
|  | cluster:unknown-vtable-impl | 4,384 unresolved implementation rows | BLOCKED_ON_IDENTIFICATION |

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |
| Unresolved anonymous gameplay functions | Function semantics not established | UNRESOLVED |  |
| Unresolved vtable families | Possible class implementations | UNRESOLVED |  |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| ownership_transition | No state ownership | UNRESOLVED |
| semantic_event_model | No event contract | UNRESOLVED |

### Transitions

| From | To | Status |
| --- | --- | --- |
| unknown function | typed semantic package | UNRESOLVED; requires evidence |
| unresolved vtable family | class/interface | UNRESOLVED; proximity is not ownership |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| knowledgegraph/research/track-b-function-accounting.json | Exact universe/decomp accounting | READ_ONLY_EVIDENCE |
| knowledgegraph/triage/debtmap-f0e310e0.json | 48,296 UNKNOWN debt rows | READ_ONLY_EVIDENCE |
| knowledgegraph/triage/reconstruction-readiness-f0e310e0.json | NEEDS_RE/dependencies | READ_ONLY_EVIDENCE |

## PKG-22-RUNTIME-CRT-STL — Runtime, CRT, STL, and third-party wrappers

**Scope:** Runtime support and imported/third-party ancestry. Explicitly out of semantic reconstruction scope unless a gameplay package proves a dependency.

**Confidence:** `SUPPORTED`; basis: Exact triage accounting, Third-party attribution. Unresolved: Any gameplay meaning is intentionally out of scope.

**Membership:** 0 explicit function/root anchors; 4075 total candidate functions after cluster-scope inference. Explicit Track O functions/roots are anchors. Broader cluster matches are INFERRED candidates and do not establish ownership.

**Dependencies:** upstream=MSVCR90/runtime imports, triage-v6; downstream=Gameplay packages only through explicit boundary stubs. Boundary rule: Do not reconstruct runtime wrappers as gameplay semantics.

**Replacement interface:** `OUT_OF_SCOPE` — None. No replacement interface. Classify as infrastructure or ignore unless a concrete gameplay boundary requires a stub. Target: None

**Prerequisites:** Boundary stub contract; Concrete gameplay dependency; No semantic promotion

### Explicit package functions

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | MSVCR90 wrapper rows | Runtime calls | OUT_OF_SCOPE |

### Package roots

| VA | Name | Role | Status |
| --- | --- | --- | --- |
|  | cluster:runtime-crt-stl | 4,075-function runtime slice | OUT_OF_SCOPE |
|  | MSVCR90 import ancestry | Runtime wrapper evidence | OBSERVED_ACCOUNTING |

### Structures

| Name | Role | Status | Reference |
| --- | --- | --- | --- |
| C runtime/import structures | Runtime support | OUT_OF_SCOPE |  |

### Events

| Event | Scope | Status |
| --- | --- | --- |
| runtime_wrapper_event | No semantic claim | OUT_OF_SCOPE |

### Transitions

| From | To | Status |
| --- | --- | --- |
| gameplay call | runtime/CRT implementation | OUT_OF_SCOPE; stub only at explicit gameplay boundary |

### Existing tests and fixtures

| Path | Coverage | Status |
| --- | --- | --- |
| knowledgegraph/research/track-b-function-accounting.md | Runtime/CRT accounting | READ_ONLY_EVIDENCE |
| knowledgegraph/triage/attribution-f0e310e0.json | Runtime/third-party attribution | READ_ONLY_EVIDENCE |



## Implementation boundary

No package authorizes direct reconstruction from decompiled source. A package becomes implementation-ready only after its prerequisites, contract evidence, and validation class are satisfied. Runtime, CRT/STL, RenderWare/D3D implementation, and broad unknown function mass remain infrastructure or characterization targets unless a concrete gameplay boundary requires a narrow adapter.
