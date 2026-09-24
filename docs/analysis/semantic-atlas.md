# Semantic Atlas

## Scope and policy

This atlas consolidates the pinned SporeApp.exe 3.1.0.22 research corpus for clean-room reconstruction planning. It contains all 58,757 canonical functions, all 223,704 reference edges, all 2,035 current Ghidra structure layouts, the 488 Ghidra-only external function entries, gameplay characterizations, dependencies, boundaries, packages, and unresolved questions.

All canonical function contracts remain `unknown`. Track C's `partial` labels describe static-contract evidence, not behavioral verification. SDK names, vtable links, decompilation, xrefs, current OpenSpore tests, and package assignments never substitute for original runtime evidence. Package candidates inferred from cluster scope are explicitly not ownership facts.

## Stable counts

| Measure | Count |
| --- | --- |
| Canonical functions | 58757 |
| Gameplay functions | 2149 |
| Ghidra manager entries | 59245 |
| Ghidra-only external functions | 488 |
| Reference edges | 223704 |
| External allowlist entries | 362 |
| Ghidra structures | 2035 |
| SDK structure names associated with functions | 264 |
| Reconstruction packages | 23 |
| Readiness queue rows | 368 |
| Runtime-validated functions | 0 |

The manager reconciliation is exact: 59,245 = 58,757 canonical iterator entries + 488 external-only entries. The three readiness rows outside the canonical universe remain in the queue report but are excluded from function-level atlas records.

## Category coverage

| Category | Functions | Persisted bodies | Coverage % |
| --- | --- | --- | --- |
| ENGINE_IMPLEMENTATION | 11585 | 0 | 0.0 |
| ENGINE_INTERFACE | 1227 | 302 | 24.6129 |
| GAMEPLAY_LOGIC | 1656 | 99 | 5.9783 |
| GAMEPLAY_SUPPORT | 493 | 73 | 14.8073 |
| THIRD_PARTY_OR_RUNTIME | 4080 | 3 | 0.0735 |
| UNKNOWN | 39716 | 1 | 0.0025 |

## Cluster coverage

| Cluster | Functions | Gameplay | Bodies | Confidence | Readiness |
| --- | --- | --- | --- | --- | --- |
| app-lifecycle | 1104 | 0 | 147 | high | ready |
| audio-input | 11 | 0 | 6 | low | blocked-on-identification |
| editor-core | 314 | 265 | 39 | high | ready |
| editor-support | 99 | 84 | 18 | medium | near-ready |
| gameglobal-misc | 39 | 35 | 0 | medium | blocked-on-identification |
| graphics-render | 86 | 0 | 20 | medium | near-ready |
| resource-io | 523 | 0 | 50 | high | ready |
| runtime-crt-stl | 4075 | 0 | 2 | high | out-of-scope |
| scripting-content | 84 | 0 | 10 | medium | ready |
| sim-cell | 26 | 26 | 26 | high | near-ready |
| sim-core-systems | 1628 | 1523 | 54 | high | ready |
| sim-creature-tribeciv | 11 | 11 | 11 | medium | near-ready |
| sim-space | 7 | 7 | 2 | medium | near-ready |
| sporepedia-online | 100 | 83 | 14 | high | ready |
| swarm-anim | 70 | 0 | 4 | low | blocked-on-identification |
| terrain-world | 112 | 102 | 5 | medium | near-ready |
| ui-shell | 13 | 13 | 3 | low | near-ready |
| unknown-fun-mass | 44978 | 0 | 1 | low | blocked-on-identification |
| unknown-vtable-impl | 4384 | 0 | 0 | medium | blocked-on-identification |
| utfwin-framework | 1093 | 0 | 66 | high | ready |

## Subsystem coverage

| Subsystem | Functions | Gameplay | Bodies | Coverage % |
| --- | --- | --- | --- | --- |
| Anim | 1 | 0 | 1 | 100.0 |
| App | 1000 | 0 | 147 | 14.7 |
| ArgScript | 84 | 0 | 10 | 11.9048 |
| Audio | 7 | 0 | 4 | 57.1429 |
| Clock | 104 | 0 | 0 | 0.0 |
| Editor | 314 | 265 | 39 | 12.4204 |
| GameGlobal | 36 | 35 | 0 | 0.0 |
| GameInput | 4 | 0 | 2 | 50.0 |
| Graphics | 61 | 0 | 14 | 22.9508 |
| IO | 323 | 0 | 22 | 6.8111 |
| LocalizedString | 3 | 0 | 0 | 0.0 |
| Math | 67 | 0 | 2 | 2.9851 |
| Palettes | 75 | 60 | 10 | 13.3333 |
| Pollinator | 10 | 10 | 2 | 20.0 |
| RenderWare | 23 | 0 | 5 | 21.7391 |
| Resource | 200 | 0 | 28 | 14.0 |
| Runtime | 4075 | 0 | 2 | 0.0491 |
| Simulator | 1669 | 1564 | 93 | 5.5722 |
| Skinner | 24 | 24 | 8 | 33.3333 |
| Space | 3 | 3 | 0 | 0.0 |
| Sporepedia | 90 | 73 | 12 | 13.3333 |
| Swarm | 2 | 0 | 1 | 50.0 |
| Terrain | 112 | 102 | 5 | 4.4643 |
| Transform | 2 | 0 | 1 | 50.0 |
| UI | 13 | 13 | 3 | 23.0769 |
| UTFWin | 1093 | 0 | 66 | 6.0384 |
| Unknown | 49362 | 0 | 1 | 0.002 |

## Gameplay characterization

Track C covers 2,149 gameplay rows: 173 partial static characterizations and 1,976 not established. Only 172 gameplay functions have persisted bodies. Every gameplay contract status remains `unknown`.

These are distinct, potentially overlapping populations and must be compared with their own denominators:

| Population | Count | Denominator | Interpretation |
| --- | --- | --- | --- |
| `unknown-needs-investigation` gameplay rows | 1,598 | 2,149 gameplay functions | Category-level investigation backlog; 1,598/2,149 = 74.36%. |
| Semantic-not-established gameplay rows | 1,976 | 2,149 gameplay functions | Rows without an established semantic characterization; 1,976/2,149 = 91.95%. |
| Gameplay rows without a persisted body | 1,977 | 2,149 gameplay functions | 1,977/2,149 = 92.00%; 1,977 = 2,149 − 172 persisted-body rows. |

The 1,598 count is not a fraction of the 58,757-function canonical universe. The three counts are not interchangeable, may overlap, and must not be combined into one unresolved backlog. Persisted absence is uncaptured evidence, not inability to decompile. Evidence: `knowledgegraph/research/global-campaign-2026/verify-semantic.json:221-247` (F-007), `knowledgegraph/research/global-campaign-2026/verify-machine.json:508-512`, and `knowledgegraph/research/semantic-atlas.json`.

| Readiness | Queue rows | With body | Canonical | Outside canonical |
| --- | --- | --- | --- | --- |
| DEPENDENCY_FIRST | 24 | 24 | 24 | 0 |
| ENGINE_BOUNDARY | 23 | 23 | 23 | 0 |
| LIKELY_INFRASTRUCTURE | 185 | 102 | 182 | 3 |
| NEEDS_RE | 101 | 0 | 101 | 0 |
| READY | 6 | 6 | 6 | 0 |
| READY_WITH_LOCAL_CONTEXT | 29 | 29 | 29 | 0 |

## Dependency foundations

| Rank | VA | Name | Dependencies | Global fan-in | Reconstructable now | Why |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 00b3d300 | FUN_00b3d300 | 0 | gl_fan_in=252, scc=1, fan_out_all=0 | no | evidence=SUPPORTED, decomp=False(0L), readiness=LIKELY_INFRASTRUCTURE |
| 2 | 00b3d2a0 | FUN_00b3d2a0 | 0 | gl_fan_in=101, scc=1, fan_out_all=0 | no | evidence=SUPPORTED, decomp=False(0L), readiness=LIKELY_INFRASTRUCTURE |
| 3 | 00b3d350 | Simulator::cGameInputManager::Get | 0 | gl_fan_in=80, scc=1, fan_out_all=0 | no | evidence=CONFIRMED, decomp=True(13L), readiness=not-queued |
| 4 | 00b5b800 | FUN_00b5b800 | 1 | gl_fan_in=80, scc=1, fan_out_all=2 | no | evidence=SUPPORTED, decomp=False(0L), readiness=LIKELY_INFRASTRUCTURE |
| 5 | 01021260 | FUN_01021260 | 0 | gl_fan_in=68, scc=1, fan_out_all=0 | no | evidence=SUPPORTED, decomp=False(0L), readiness=LIKELY_INFRASTRUCTURE |
| 6 | 00b1fdb0 | FUN_00b1fdb0 | 0 | gl_fan_in=68, scc=1, fan_out_all=0 | no | evidence=SUPPORTED, decomp=False(0L), readiness=LIKELY_INFRASTRUCTURE |
| 7 | 00b21340 | FUN_00b21340 | 1 | gl_fan_in=50, scc=1, fan_out_all=2 | no | evidence=SUPPORTED, decomp=False(0L), readiness=LIKELY_INFRASTRUCTURE |
| 8 | 00e5c780 | map_int_whatever_find | 0 | gl_fan_in=49, scc=1, fan_out_all=0 | no | evidence=SUPPORTED, decomp=False(0L), readiness=NEEDS_RE |
| 9 | 01021300 | FUN_01021300 | 2 | gl_fan_in=47, scc=1, fan_out_all=2 | no | evidence=SUPPORTED, decomp=False(0L), readiness=LIKELY_INFRASTRUCTURE |
| 10 | 01021080 | FUN_01021080 | 0 | gl_fan_in=38, scc=1, fan_out_all=0 | no | evidence=SUPPORTED, decomp=False(0L), readiness=LIKELY_INFRASTRUCTURE |
| 11 | 00b25fb0 | FUN_00b25fb0 | 2 | gl_fan_in=36, scc=1, fan_out_all=2 | no | evidence=SUPPORTED, decomp=False(0L), readiness=LIKELY_INFRASTRUCTURE |
| 12 | 00ba9370 | FUN_00ba9370 | 1 | gl_fan_in=35, scc=1, fan_out_all=1 | no | evidence=SUPPORTED, decomp=False(0L), readiness=LIKELY_INFRASTRUCTURE |

The dependency graph contains one dominant gameplay component of 1,761 functions, 21 small components totaling 58 functions, and 330 isolated functions. This is why package and interface work should precede broad per-function implementation.

## Engine boundaries

| ID | Boundary | Classification | Priority | Modern interface | OpenSpore gap |
| --- | --- | --- | --- | --- | --- |
| B-K-01 | Application bootstrap and game-mode lifecycle | required_for_semantics | P0 | IAppHost + IGameModeRegistry | The current host is a Cell executable, not a replacement for AppSystem/plugin bootstrap or the complete mode-manager service registry. |
| B-K-02 | Game services, input, camera, behavior, and frame clock | required_for_semantics | P0 | IGameServices | OpenSpore has input, camera, and fixed simulation time, but not the original behavior, persistence, or service-root contracts. |
| B-K-03 | Cell world state, entity pool, movement, and interaction | required_for_semantics | P0 | ICellGameState + IEntityPool + ICameraRayProvider + IPlayerMovement | The current pieces are not wired into a complete original-equivalent per-frame state machine. The current replacement status is replaced-approx and requires live Cell-mode evidence for promotion. |
| B-K-04 | Cell resource identity and content loading | required_for_semantics | P0 | IContentStore + IRecordCodec | B1 currently serves one package image and reparses its index. The original multi-package search, cache/registry behavior, directory semantics, and load order remain unresolved. |
| B-K-05 | Cell presentation world, layers, models, effects, and UI handles | required_for_semantics | P0 | ICellPresentation | The current CellGfx records world IDs and a main-model binding, but it does not reproduce the original world/layer/effect lifecycle or a live material/frame oracle. |
| B-K-06 | RenderWare draw state and graphics device implementation | renderware_third_party | P1 | IMeshDraw + IMaterialBindings + IGraphicsDevice | The current IRenderer has flat/textured mesh submission and a material approximation, but no full original shader/material/texture-slot contract or pixel oracle. |
| B-K-07 | Camera and input semantics at the stage boundary | required_for_semantics | P0 | ICameraService + IInputRouter | The current camera ray/plane model and input table are clean-room approximations; no successful original Cell trace has pinned camera state, pointer causality, or event ordering. |
| B-K-08 | UI message dispatch and editor shell | runtime_compatibility_only | P1 | IEventLoop + IStageEventRouter | The current interactive path consumes SDL events directly and has no traced original menu-to-mode bridge. |
| B-K-09 | Property, configuration, and script data | required_for_semantics | P1 | IPropertyStore + IConfigCodec | OpenSpore has typed Cell record readers but no general property serialization or .prop round-trip. |
| B-K-10 | Windows, CRT, input/audio device, and timing runtime | os_runtime | P1 | IPlatformHost + IAudioSink | The current runtime path supports SDL3 presentation and deterministic fixed-step simulation, but original timing, audio, and input-device semantics are not live-observed. |
| B-K-11 | Unnamed high-fan-in Simulator shared-state roots | unknown | P0-characterize | blocked interface freeze | This is the first reverse-engineering blocker before broader Simulator gameplay reconstruction. It is intentionally a characterization target, not an implementation boundary. |

## Reusable current components

| Piece | Location | Original correspondence | Boundary | Confidence |
| --- | --- | --- | --- | --- |
| Bounds-checked Reader | src/assets/Stream.hpp:13-109 | SUPPORTED | Low-level byte access only; format-specific interpretation remains in callers. | high |
| DBPF v3 and QFS reader | src/assets/Dbpf.hpp:28-47; src/assets/Dbpf.cpp:37-235 | SUPPORTED | One borrowed package image per provider; not the original multi-package manager. | high |
| GMDL v8 static walker and mesh conversion | src/assets/Gmdl.hpp:1-83; src/assets/Gmdl.cpp:95-271; src/assets/Mesh.cpp:49-248 | SUPPORTED | v8, static, stream 0, triangle list, u16 indices only. | high |
| RW4 structural walker | src/assets/Rw4.hpp:31-88; src/assets/Rw4.cpp:66-220 | SUPPORTED | Structural validation only; no complete section payload, animation, skeleton, or material execution. | high |
| DXT5 and raster envelope decoders | src/assets/Texture.hpp:19-49; src/assets/Texture.cpp:26-113; src/assets/Dxt5.cpp:42-127 | SUPPORTED | Verified DXT5 envelope only; unsupported FourCCs fail explicitly. | high |
| Cell resource value objects and parsers | src/assets/CellResource.hpp:32-500; src/assets/CellResource.cpp:1-1297 | SUPPORTED | Decoding and validation are reusable; original runtime consumption is incomplete. | high |
| WorldObject structural walker | src/assets/WorldObject.hpp:31-71; src/assets/WorldObject.cpp:23-112 | SUPPORTED | Field order and placement semantics are not derived; not a scene executor. | medium |
| Compatibility seams B1/B2/B3 | src/compat/ResourceProvider.hpp:21-90; src/compat/MeshSource.hpp:24-80; src/renderer/Renderer.hpp:53-87 | SUPPORTED | Narrow host-side seams; they do not reproduce original managers or APIs. | high |
| Deterministic CellSim and scripted input | src/sim/Sim.hpp:222-284; src/sim/Sim.cpp:99-356 | INFERRED | Original runtime state, AI, damage, and resource-driven behavior are outside this core. | high |
| Static Cell state and rule components | src/sim/CellGame.cpp:22-152; src/sim/CellPool.hpp:66-162; src/sim/CellQuery.hpp:27-82; src/sim/Advect.hpp:29-106; src/sim/Combat.hpp:14-128 | SUPPORTED | Pure selected-function components; not a wired original gameplay loop. | high |
| Vulkan renderer and IRenderer | src/renderer/Renderer.hpp:46-87; src/renderer/VulkanRenderer.hpp:15-70; src/renderer/VulkanRenderer.cpp:230-383 | SUPPORTED | Modern fixed-function approximation; no original material cache, D3D bytecode, or full RenderWare state model. | high |
| Cell mode, GFX, UI, input, and animation shell | src/apps/IGameMode.hpp:28-52; src/apps/CellModeStrategy.cpp:7-91; src/apps/CellGfx.cpp:5-44; src/apps/CellUI.cpp:5-25; src/apps/CellInput.cpp:5-95; src/apps/CellAnim.cpp:7-83 | SUPPORTED | Records and switches state; it is not the original application system or full Cell runtime. | high |
| Replacement POD views and function pair | src/replace/CellGameView.hpp:20-62; src/replace/Replace.cpp:25-68; src/replace/Reference.cpp:41-94 | SUPPORTED | Installed replacement still needs real 32-bit pool lookup and runtime verification. | high |
| Python format oracles and asset resolver | tools/spore/README.md:17-87; tools/spore/dbpf/dbpf.py; tools/spore/rw4/rw4.py; tools/spore/gmdl/gmdl.py; tools/spore/raster/raster.py; tools/spore/dxt5/dxt5.py; tools/spore/asset_resolver.py:1-225 | SUPPORTED | Research/oracle tools; they are not linked runtime dependencies. | high |
| MCP, observatory, KG, and viewer infrastructure | tools/mcp/server.py:70-257; tools/mcp/registry.py:97-391; tools/observatory/probe_tracer.cpp:376-477; tools/viewer/server.py:31-216; knowledgegraph/schema.sql:1-172 | INFERRED | Workflow infrastructure; must retain read-only, approval, and lock boundaries. | high |

These are current-code facts or bounded reconstructions. They are not claims that the original internals or runtime behavior have been reproduced.

## Historical status wording

Earlier campaign language describing Cell work as complete, an original pipeline, integrated animation, or ready for promotion is historical context only, not current semantic or runtime evidence. It must not be read as a promotion gate. Current evidence remains negative for original Cell gameplay and has no function-level runtime validation; the decompilation-only 64/64 result remains `replaced-approx`. Replacement promotion still requires the complete C-REPLACEMENT gate, including a hash-pinned live original trace, field-offset and meaning evidence, an original/replacement comparison, independent adjudication, and human status approval. Evidence: `knowledgegraph/research/global-campaign-2026/verify-semantic.json:53-78,113-138,249-275`, `knowledgegraph/research/global-campaign-2026/verify-machine.json:508-523`, and `docs/analysis/reconstruction-research-queue.md:32-47`.

## Replacement packages

| Package | Name | Confidence | Interface status | Explicit anchors | Candidate functions | Prerequisites |
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

See `docs/analysis/reconstruction-packages.md` for the complete package contracts and `docs/analysis/reconstruction-research-queue.md` for the full 368-row queue.

## Structure anchors

| SDK structure | Associated functions | Ghidra fields | Evidence |
| --- | --- | --- | --- |
| /Spore/App/Property | 68 | 2 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/UTFWin/Window | 43 | 41 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/ArgScript/FormatParser | 25 | 31 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/App/cPropManager | 23 | 27 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/App/Canvas | 21 | 41 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/Editors/cEditor | 21 | 316 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/Resource/cResourceManager | 21 | 14 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/Resource/DatabasePackedFile | 20 | 44 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/App/PropertyList | 15 | 7 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/Palettes/AdvancedItemViewer | 15 | 86 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/App/cAppSystem | 14 | 9 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/App/cViewer | 14 | 12 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/App/DirectPropertyList | 14 | 10 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/Simulator/Cell/cCellGFX | 14 | 39 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/Terrain/cTerrainSphere | 14 | 136 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/App/cCheatManager | 13 | 8 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/Resource/DatabaseDirectoryFiles | 13 | 18 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/Sporepedia/cSPAssetDataOTDB | 13 | 20 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/App/cCellModeStrategy | 12 | 5 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/App/cMessageManager | 12 | 8 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/IO/FileStream | 12 | 10 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/Simulator/cStarManager | 12 | 51 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/App/cCameraManager | 11 | 13 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/IO/MemoryStream | 11 | 10 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/Simulator/cRelationshipManager | 11 | 28 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/Resource/PFIndexModifiable | 10 | 4 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/Simulator/cCreatureBase | 10 | 281 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/Simulator/cCreatureGameData | 10 | 16 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/Simulator/cScenarioPowerup | 10 | 13 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |
| /Spore/UTFWin/StdDrawable | 10 | 11 | SDK_NAME_OR_VTABLE_ASSOCIATION_ONLY |

The JSON atlas contains every Ghidra structure and field layout, every SDK-associated function structure, and source-specific structure claims.

## Ghidra-only external entries

| External entry | Name | Allowlist DLLs | Canonical external xrefs |
| --- | --- | --- | --- |
| external:00000001 | timeEndPeriod | WINMM.DLL | 2 |
| external:00000002 | timeBeginPeriod | WINMM.DLL | 2 |
| external:00000003 | timeGetTime | WINMM.DLL | 7 |
| external:00000004 | Ordinal_19 | WSOCK32.DLL | 1 |
| external:00000005 | Ordinal_13 |  | 0 |
| external:00000006 | Ordinal_4 | WSOCK32.DLL | 1 |
| external:00000007 | Ordinal_1 | WSOCK32.DLL | 1 |
| external:00000008 | Ordinal_6 |  | 0 |
| external:00000009 | Ordinal_7 | WSOCK32.DLL | 8 |
| external:0000000a | Ordinal_151 |  | 0 |
| external:0000000b | Ordinal_18 |  | 0 |
| external:0000000c | Ordinal_16 | WSOCK32.DLL | 1 |
| external:0000000d | Ordinal_10 | WSOCK32.DLL | 2 |
| external:0000000e | Ordinal_52 | WSOCK32.DLL | 1 |
| external:0000000f | Ordinal_3 | WSOCK32.DLL | 2 |
| external:00000010 | Ordinal_115 |  | 0 |
| external:00000011 | Ordinal_116 | WSOCK32.DLL | 2 |
| external:00000012 | Ordinal_111 | WSOCK32.DLL | 19 |
| external:00000013 | Ordinal_20 |  | 0 |
| external:00000014 | Ordinal_17 |  | 0 |
| external:00000015 | Ordinal_12 |  | 0 |
| external:00000016 | Ordinal_23 | WSOCK32.DLL | 1 |
| external:00000017 | Ordinal_2 |  | 0 |
| external:00000018 | Ordinal_22 | WSOCK32.DLL | 2 |
| external:00000019 | Ordinal_5 | WSOCK32.DLL | 1 |
| external:0000001a | Ordinal_21 |  | 0 |
| external:0000001b | GetModuleInformation |  | 0 |
| external:0000001c | SteamApps | STEAM_API.DLL | 1 |
| external:0000001d | SteamAPI_Shutdown |  | 0 |
| external:0000001e | SteamAPI_Init |  | 0 |

The table shows the first 30 of 488; all entries are in the JSON atlas. They remain outside canonical accounting and are treated as runtime/third-party package candidates only.

## Issues and contradictions

| # | ID/kind | Severity | Finding | Source |
| --- | --- | --- | --- | --- |
| 1 | all-function-contracts-unknown | blocking | All 58,757 canonical function contract statuses remain unknown; Track C partial understanding is static characterization, not promotion. | knowledgegraph/research/track-b-function-accounting.jsonl |
| 2 | cluster-package-membership | medium | Package candidates inferred from cluster scope are not ownership facts. Only explicit Track O functions/roots are anchors. | knowledgegraph/research/global-campaign-2026/track-o-packages-testability.json |
| 3 | duplicate-normalized-names | high | The canonical universe contains 92 duplicate normalized-name groups across 190 rows. Address identity must remain authoritative. | knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl |
| 4 | global-campaign-json-count | informational | The global-campaign source set contains 11 primary input JSONs; verification and synthesis outputs are additional. Related JSONL, TSV, triage, and older Track I/M/N artifacts are listed separately in provenance. | knowledgegraph/research/global-campaign-2026 |
| 5 | no-msvc-rtti | high | SporeApp.exe has no MSVC RTTI. Class identity must not be inferred from an RTTI hierarchy; vtable and SDK anchors remain name-level evidence. | docs/STATE.md |
| 6 | persisted-vs-live-decompilation | blocking | Only 478 persisted bodies exist, but live probes successfully decompiled 996/996 sampled unavailable functions and 99/99 sampled unavailable gameplay functions. Persisted absence means uncaptured evidence, not inability to decompile. | knowledgegraph/research/global-campaign-2026/track-p-coverage.json |
| 7 | queue-outside-canonical | high | Three readiness rows are outside the canonical universe: 00e3a400, 00e7b6c0, and 00e7d2c0. They remain in the queue report but are excluded from per-function canonical records. | knowledgegraph/triage/reconstruction-readiness-f0e310e0.json |
| 8 | runtime-negative | blocking | No original Cell gameplay trace or function-level runtime validation exists. Current evidence is startup/menu historical positive plus stable reachability negatives. | knowledgegraph/research/track-m-oracle-plan.json |
| 9 | track-o-stale-unknown-count | medium | Track O cites 48,296 UNKNOWN debt rows, while the pinned triage-v6 category count is 39,716 and Track B debt ownership reports 35,771 genuinely_unknown. These are different or stale populations; use triage-v6 for category coverage and retain the debt distinction. | knowledgegraph/research/global-campaign-2026/track-o-packages-testability.json |
| 10 | SOURCE_DISCREPANCY | documented | {"evidence":["The same summary reports pinned_missing_at_address as 0.","The vtable artifact reports meta.functions as 58756.","xrefs-2540f2ca.summary.json pins the canonical universe at 58757."],"finding":"The frozen canonical triage universe is 58757 unique VAs while the live Ghidra function count is 59245.","id":"canonical-universe-vs-ghidra","interpretation":"Treat the difference as scope and snapshot drift, not as an unresolved missing-row defect.","remaining_gap":"No row-level diff between the live Ghidra function set and the canonical ledger was performed in this inventory.","status":"documented"} | knowledgegraph/research/global-campaign-2026/00-source-inventory.json |
| 11 | DOCUMENT_CONFLICT | documented | {"finding":"Older prose says xdotool/Xvfb are absent, while the current read-only command check finds xdotool and the committed S5 artifacts use it.","handling":"Treat current command availability and S5 artifacts as current for gate planning; retain older prose as historical context only.","id":"CONFLICT-01","sources":["docs/analysis/CELL-RUNTIME-OBSERVATION.md:8-19","docs/devlog/018-s5-cell-runtime-evidence.md:17-23","docs/STATE.md:87-91","read-only environment check performed for this assessment"]} | knowledgegraph/research/track-m-oracle-plan.json |
| 12 | DOCUMENT_CONFLICT | documented | {"finding":"The campaign text says S5 was not run, while devlog 018 and raw S5 directories record a three-run S5 attempt.","handling":"Use devlog 018 plus raw artifacts as the historical S5 record. The campaign CS-32 status is not a reason to rerun blindly; its runtime gate remains open and negative.","id":"CONFLICT-02","sources":["docs/analysis/campaigns/cell-stage-campaign.md:511-519","docs/devlog/018-s5-cell-runtime-evidence.md:1-8","tools/observatory/out/cell/S5-20260922T212936Z-396838/manifest.json:1-23"]} | knowledgegraph/research/track-m-oracle-plan.json |
| 13 | EDITOR_UI_EVIDENCE_INCONSISTENCY | documented | {"details":"Live GhidraMCP read-only program info reported 59,245 functions; committed docs/triage use 58,757 for snapshot f0e310e0. This artifact uses committed triage counts for readiness and records the live count only as an unresolved snapshot boundary.","issue":"function_count drift"} | knowledgegraph/research/global-campaign-2026/track-g-editor-ui-input.json |
| 14 | EDITOR_UI_EVIDENCE_INCONSISTENCY | documented | {"details":"Many editor/message/camera SDK decompilations carry unknown calling-convention warnings. Field offsets, vtable names and call structure are used as evidence; local parameter type guesses are not promoted to exact semantics.","issue":"decompiler calling-convention warnings"} | knowledgegraph/research/global-campaign-2026/track-g-editor-ui-input.json |
| 15 | EDITOR_UI_EVIDENCE_INCONSISTENCY | documented | {"details":"Static artifacts are strong enough to identify roots and interfaces, but the original cell-stage trace is recorded as negative and editor/UI runtime behavior has no committed positive trace.","issue":"runtime gap"} | knowledgegraph/research/global-campaign-2026/track-g-editor-ui-input.json |
| 16 | SOURCE_DISCREPANCY | documented | {"finding":"Older reports mention 96 KG nodes, 115 edges, and 14 tests, while the current read-only database contains 65461 nodes, 20397 edges, and 28 test results.","id":"legacy-knowledge-graph-counts","interpretation":"The older figures describe an earlier phase and must not be used as current database counts.","status":"documented"} | knowledgegraph/research/global-campaign-2026/00-source-inventory.json |
| 17 | SOURCE_DISCREPANCY | documented | {"finding":"Older reports record 1895 structures, while current analysis reports 2035.","id":"structure-counts","interpretation":"Retain the phase-specific provenance for each structure count.","status":"documented"} | knowledgegraph/research/global-campaign-2026/00-source-inventory.json |
| 18 | SOURCE_DISCREPANCY | documented | {"finding":"SDK import reports 1666 rows and 1663 unique addresses, while narrative reports refer to 1670/1671 functions; older missing-entry reports refer to 1188, while the repaired adjudication reports 1186 after duplicate correction.","id":"sdk-boundary-counts","interpretation":"Preserve both raw import counts and repaired adjudication counts; do not collapse them into one number.","status":"documented"} | knowledgegraph/research/global-campaign-2026/00-source-inventory.json |
| 19 | SOURCE_DISCREPANCY | documented | {"finding":"The canonical body set contains 478 addresses, while manifest and file counts contain 477 decompiler exports plus one annotated capture; one SDK-address duplicate explains the manifest/file difference.","id":"decompilation-manifest","interpretation":"Use canonical address sets for coverage accounting and retain file-level provenance separately.","status":"documented"} | knowledgegraph/research/global-campaign-2026/00-source-inventory.json |
| 20 | SOURCE_DISCREPANCY | documented | {"finding":"The triage-v6 JSONL filename and summary identify triage-v6, but row classifier_version fields remain triage-v5.","id":"triage-classifier-version","interpretation":"Use the artifact version and row metadata as separate evidence; do not silently normalize them.","status":"documented"} | knowledgegraph/research/global-campaign-2026/00-source-inventory.json |

Canonical normalized-name duplicates: 92 groups across 190 rows (7 named groups and 85 autogenerated `FUN_*` groups). Address identity is authoritative.

## Unresolved work

The machine atlas carries 92 consolidated unresolved-question rows. The highest-value blockers are:

1. Establish a positive boot control before attempting Cell navigation.
2. Reach Cell with correlated entry, lifecycle, state, and per-frame events.
3. Characterize the unnamed shared-state roots and returned globals.
4. Resolve pool-index versus entity-pointer identity and live movement side effects.
5. Correlate mouse/camera events with movement targets.
6. Map message/resource/frame order at stage transition.
7. Keep RenderWare, D3D, Win32, CRT, and platform wrappers behind replacement boundaries.

## Provenance

The machine-readable source manifest contains 23 repository source-manifest entries and no separate output collection. The generated artifact contains no generation timestamp. `SPORE/` and proprietary source/assets were not copied or modified.
