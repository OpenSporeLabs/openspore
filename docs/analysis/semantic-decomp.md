# Semantic decompilation campaign report

## Scope and evidence basis

This report synthesizes the eight disjoint `semantic-decomp` worker artifacts and the canonical residual-priority material. It covers **32 unique VAs**, four targets per worker, with no duplicate ownership across groups. The binary evidence is the read-only `SporeApp.exe` analysis at image base `0x00400000`; the workers use Ghidra-targeted decompilation, disassembly, direct xrefs, structures, vtables, strings, siblings, and committed research artifacts.

Canonical priority sources:

- `knowledgegraph/research/residual-unknown-priority.json` — machine-readable ranking and normalized residual rows.
- `docs/analysis/residual-unknown-priority.md:1-22,94-122,252-267,269-343,345-399` — predicate, ranking method, unlock sets, and safety boundaries.

Worker sources, with the exact target evidence ranges used here:

| Group | Worker artifact and target evidence |
|---|---|
| Roots | `knowledgegraph/research/semantic-decomp/worker-00-roots.json:10-43,45-1084` |
| GameGlobal/resource | `knowledgegraph/research/semantic-decomp/worker-01-gameglobal.json:24-262` |
| Cell | `knowledgegraph/research/semantic-decomp/worker-02-cell.json:45-203,222-480` |
| Space | `knowledgegraph/research/semantic-decomp/worker-03-space.json:27-70,72-550` |
| Editor core | `knowledgegraph/research/semantic-decomp/worker-04-editor-core.json:52-1302` |
| UI shell | `knowledgegraph/research/semantic-decomp/worker-05-ui-shell.json:128-221,294-983` |
| Editor support | `knowledgegraph/research/semantic-decomp/worker-06-editor-support.json:42-184,186-745` |
| Sporepedia/events | `knowledgegraph/research/semantic-decomp/worker-07-sporepedia-events.json:25-45,47-839` |

This P0 resolution pass updates the guarded map reconstruction, its model test, the canonical audit/manifest, and the focused resolution record. No Ghidra program, canonical knowledge-graph database, `SPORE/` content, or unrelated source was modified.

## Methodology and evidence boundary

1. Treat direct decompiled bytes and disassembly as the primary evidence; use Ghidra layout, vtable, string, caller/callee, and sibling evidence to corroborate identity and boundaries.
2. Treat SDK names, package projections, candidate vtables, and contained function aliases as hypotheses. Reject an alias when it points inside a containing function or conflicts with the live body. There is no MSVC RTTI.
3. Keep presentation, simulation, persistent-content, engine, App, UI, and event families separate. A callback, service virtual, or `IAppSystem` call is not a queued message without queue-body evidence.
4. Distinguish **static mechanics** from **runtime-needed** lifetime, publication, timing, payload provenance, message delivery, and branch ordering. Static confidence is not runtime validation.
5. Preserve the workers' direct-endpoint counting rules. They are not one uniform metric: some report direct callers, some direct callees, some caller+callee endpoints, and some vtable/data surfaces. None is a transitive or runtime reachability claim.
6. Reject cross-family identity by default. In particular, local `cCommEvent`, anonymous keyed space records, `App::StandardMessage`, UTFWin messages, editor animation events, resource records, and game persistence are distinct carriers unless a dataflow edge joins them.
7. Use `NEEDS_RUNTIME` exactly for the 15 records represented as required gates in `docs/analysis/future-research/semantic-decomp-runtime-gates.md`. Do not promote records from confidence alone; preserve the explicit static bounded, structural, and unknown distinctions for the remaining records.

The harmonized labels below are campaign labels, not new canonical semantic status:

- **Strong**: core static mechanics, identity boundary, and ownership/state result are sufficiently closed for a typed implementation boundary; remaining questions are localized.
- **Bounded**: static behavior and family are supported, but arguments, payload names, service types, lifecycle, or runtime ordering remain open.
- **Structural**: ownership, layout, family, or propagation is strong, but the core semantic contract is still mostly a boundary/identity result.
- **Unknown**: the body is mechanically readable, but variant identity or payload semantics are not safe to promote.
- **NEEDS_RUNTIME**: static mechanics are closed, but a runtime observation is required to separate publication, aliasing, lifetime, or ordering hypotheses.

## Campaign totals

| Classification | Count | Meaning in this report |
|---|---:|---|
| Strong | 4 | Static result and boundary are ready for a typed contract, with only bounded secondary unknowns |
| Bounded | 8 | Supported static contract, but one or more material semantic/lifetime questions remain |
| Structural | 5 | Layout/family/ownership boundary is useful; exact gameplay or domain behavior is not promoted |
| Unknown | 0 | Local mechanics are safe, but variant identity or event meaning is not |
| NEEDS_RUNTIME | 15 | Static body is closed; runtime is required for slot publication, aliasing, or lifetime |
| **Total** | **32** | 8 groups × 4 disjoint targets |

Evidence availability is uniform but bounded:

- **Targeted live decompilation/disassembly:** 32/32 targets.
- **Canonical persisted decompilation:** 0/32 in this residual campaign; the priority material explicitly distinguishes targeted static observation from persisted canonical text.
- **Runtime validation:** 0/32.
- **Direct caller/callee and structural evidence:** present for all groups, with vtable-only targets retaining unresolved direct-caller boundaries.

## Target groups

| Group | Package projection | Exact VAs |
|---|---|---|
| Roots | `PKG-11-SIM-CORE`, `PKG-01-SHARED-STATE-ROOTS` | `0x00b21340`, `0x00b3d2a0`, `0x00b3d300`, `0x01021300` |
| GameGlobal/resource | `PKG-20-GAMEGLOBAL` | `0x00e5c780`, `0x006a25a0`, `0x00576650`, `0x00b3d4f0` |
| Cell | `PKG-06-CELL-STATE`, `PKG-08-CELL-MODE`, `PKG-09-CELL-PRESENTATION`, `PKG-05-CELL-CONTENT` | `0x00e7a7c0`, `0x00e7a4a0`, `0x00e7fd00`, `0x00e780a0` |
| Space | `PKG-12-SIM-SPACE`, `PKG-11-SIM-CORE`, `PKG-13-SIM-CREATURE-TRIBECIV` | `0x00606880`, `0x00aeb720`, `0x00c877f0`, `0x00de9fc0` |
| Editor core | `PKG-10-EDITOR-DISPATCH`, `PKG-15-EDITOR-SUPPORT`, persistence boundary | `0x00b28ec0`, `0x005e0000`, `0x004c5200`, `0x0062c550` |
| UI shell | `PKG-18-UI-SCRIPTING` | `0x01073700`, `0x00834fa0`, `0x005bf9d0`, `0x005c0380` |
| Editor support | `PKG-15-EDITOR-SUPPORT`, `PKG-10-EDITOR-DISPATCH` | `0x005cb5a0`, `0x005cb240`, `0x005c53c0`, `0x005c9230` |
| Sporepedia/events | `PKG-16-SPOREPEDIA-ONLINE` as a local-boundary projection; scenario/editor edges are not promoted to online semantics | `0x005dda30`, `0x00ff3f00`, `0x00dd0e10`, `0x0102d1b0` |

## All 32 targets: role, classification, confidence, propagation

Propagation values are copied from the worker's counting rule. They are static direct endpoints, not transitive or runtime reachability.

| # | VA | Recovered role / family | Campaign class | Confidence | Static propagation or unlock | Exact evidence path |
|---:|---|---|---|---|---:|---|
| 1 | `0x00b21340` | `cGameNounManager::GetData`; typed noun vector, guarded exact-result selection, dirty rebuild | Strong | `0.97`; mechanics/purpose high | 254 direct callers; 254 semantic downstream | `worker-00-roots.json:45-364` |
| 2 | `0x00b3d2a0` | Alternate global `cStarManager` pointer accessor | NEEDS_RUNTIME | `0.93`; mechanics `1.0` | 314 direct callers | `worker-00-roots.json:365-571` |
| 3 | `0x00b3d300` | Alternate global `cGameNounManager` pointer accessor | NEEDS_RUNTIME | `0.94`; mechanics `1.0` | 1,097 direct callers | `worker-00-roots.json:572-775` |
| 4 | `0x01021300` | `SpacePlayerData` lazy current-player `cEmpire` cache | Strong | `0.99`; mechanics/purpose high | 182 direct callers | `worker-00-roots.json:776-1066` |
| 5 | `0x00e5c780` | Generic unsigned ordered-map guarded-lower-bound lookup with exact-candidate acceptance | Bounded | `0.96`; mechanics `0.99` | 239 unique direct caller functions | `worker-01-gameglobal.json:24-151` |
| 6 | `0x006a25a0` | `App::DirectPropertyList::GetDirectBool` | Strong | `0.95`; mechanics `0.99` | 99 unique direct caller functions | `worker-01-gameglobal.json:152-190` |
| 7 | `0x00576650` | `TexturePtr` intrusive assignment with atomic refcount | Strong | `0.97`; mechanics `0.99` | 67 unique direct caller functions | `worker-01-gameglobal.json:191-225` |
| 8 | `0x00b3d4f0` | Opaque UI mission-log manager accessor | NEEDS_RUNTIME | `0.82`; mechanics `0.99`, lifetime `0.35` | 22 unique direct caller functions | `worker-01-gameglobal.json:226-260` |
| 9 | `0x00e7a7c0` | Cell damage resolver, health clamp, damage effect, death routing | NEEDS_RUNTIME | `SUPPORTED`; runtime order unresolved | 18 direct endpoints: 2 callers / 16 callees | `worker-02-cell.json:223-307` |
| 10 | `0x00e7a4a0` | Non-player/player death transition and pooled event creation | NEEDS_RUNTIME | `SUPPORTED`; event payload meaning unresolved | 21 direct endpoints: 4 callers / 17 callees | `worker-02-cell.json:308-362` |
| 11 | `0x00e7fd00` | Cell stage drain, world/progression restore, population and hatch setup | NEEDS_RUNTIME | `SUPPORTED`; arguments/runtime order unresolved | 36 direct endpoints: 4 callers / 32 callees | `worker-02-cell.json:363-421` |
| 12 | `0x00e780a0` | Identity-destructive Cell despawn with optional scale replacement | NEEDS_RUNTIME | `SUPPORTED`; static result strong, replacement policy unresolved | 36 direct endpoints: 23 callers / 13 callees | `worker-02-cell.json:422-478` |
| 13 | `0x00606880` | Shared `0x24` value/range copy infrastructure | Structural | `0.96`; infrastructure identity high, Space semantics rejected | 19 direct endpoints: 18 callers / 1 callee | `worker-03-space.json:72-186` |
| 14 | `0x00aeb720` | `cCommManager` create-and-dispatch Space communication wrapper | Bounded | `0.90`; mechanics `0.99`, public identity `0.68` | 15 direct endpoints: 13 callers / 2 callees | `worker-03-space.json:188-306` |
| 15 | `0x00c877f0` | `cSpaceInventoryItem` PropertyList application mutator | Bounded | `0.94`; mechanics/structure high, constructor identity rejected | 8 direct endpoints: 6 callers / 2 callees | `worker-03-space.json:308-425` |
| 16 | `0x00de9fc0` | Galaxy/game-entry UI and game-mode bootstrap sub-initializer | Structural | `0.86`; mechanics `0.98`, exact SDK entry rejected | 10 direct endpoints: 1 caller / 9 callees | `worker-03-space.json:427-549` |
| 17 | `0x00b28ec0` | Profile save, header serialization, stream close, temporary replacement | Structural | Mechanics high; operation identity/manager ownership inferred | 42 direct callee endpoints; 1 caller | `worker-04-editor-core.json:52-404` |
| 18 | `0x005e0000` | `EditorUI::HandleUIMessage` containing command dispatcher | Bounded | High static dispatch; payload ABI medium | 17 direct callee endpoints; 0 direct callers, vtable-mediated | `worker-04-editor-core.json:405-697` |
| 19 | `0x004c5200` | `cEditorSkin` paint-job preparation and `IBakeManager` submission | Bounded | High paint mechanics; argument/job type medium | 17 direct callee endpoints; 5 callers | `worker-04-editor-core.json:698-998` |
| 20 | `0x0062c550` | `EditorPlayMode` per-frame module/actor/background/UI update | Bounded | High update mechanics; module/actor semantics medium | 21 direct callee endpoints; 1 caller | `worker-04-editor-core.json:999-1302` |
| 21 | `0x01073700` | `SpaceGameUI` construction/load/setup orchestrator | Bounded | Medium-high; mechanics high, contained Load alias limited | 55 direct endpoints: 4 callers / 51 callees; 215 depth-2 edges | `worker-05-ui-shell.json:294-474` |
| 22 | `0x00834fa0` | `cSPUITextZoom` presentation initialization/rebinding/invalidation | Structural | Medium-high mechanics; exact ABI and service ownership open | 18 direct endpoints: 7 callers / 11 callees; 26 depth-2 edges | `worker-05-ui-shell.json:476-641` |
| 23 | `0x005bf9d0` | `EditorNamePanel` four-ID managed-message handler | Structural | Medium-high; dispatch mechanics high, payload/service names open | 5 direct callee endpoints; 0 direct callers; 10 depth-2 edges | `worker-05-ui-shell.json:642-826` |
| 24 | `0x005c0380` | `EditorNamePanel` basic/extended state transition | Bounded | Medium-high; exact state mechanics high, literal/service meaning open | 8 direct callee endpoints; 0 direct callers; 17 depth-2 edges | `worker-05-ui-shell.json:828-982` |
| 25 | `0x005cb5a0` | `PaletteUI` load, category construction, layout/helper setup | NEEDS_RUNTIME | High; load mechanics supported, prototypes/runtime order open | 24 direct endpoints: 3 callers / 21 callees | `worker-06-editor-support.json:186-340` |
| 26 | `0x005cb240` | `PaletteUI` active-category setter and page/message update | NEEDS_RUNTIME | High; range/state mechanics supported, message payload open | 12 direct endpoints: 4 callers / 8 callees | `worker-06-editor-support.json:341-438` |
| 27 | `0x005c53c0` | `PaletteCategoryUI` load, page children, swatch and service binding | NEEDS_RUNTIME | Medium-high; layout support strong, hidden ABI open | 35 direct endpoints: 3 callers / 32 callees | `worker-06-editor-support.json:439-550` |
| 28 | `0x005c9230` | `PalettePageUI` load, dimensions, standard/advanced item construction | NEEDS_RUNTIME | High; page-load mechanics supported, return/type cases open | 27 direct endpoints: 1 caller / 26 callees | `worker-06-editor-support.json:552-657` |
| 29 | `0x005dda30` | Editor mode request, `cEditor::SetActiveMode`, window lifecycle | NEEDS_RUNTIME | `0.90`; state transition high, event timing medium | 10 direct callee endpoints; 4 callers | `worker-07-sporepedia-events.json:47-240` |
| 30 | `0x00ff3f00` | Timeline-event command-line pointer accessor | NEEDS_RUNTIME | `0.84`; field lifecycle medium, subtype unknown | 27 direct consumer endpoints; 2 vtable surfaces | `worker-07-sporepedia-events.json:241-423` |
| 31 | `0x00dd0e10` | Local timeline-event variant handler | NEEDS_RUNTIME | `0.83`; body high, variant semantics low-medium | 15 direct callee endpoints; 1 virtual surface, 0 direct callers | `worker-07-sporepedia-events.json:424-622` |
| 32 | `0x0102d1b0` | Local scenario surrender orchestrator and communication side effects | NEEDS_RUNTIME | `0.87`; surrender role medium, carrier separation high | 53 direct callee endpoints; 1 caller; 2 named carrier surfaces | `worker-07-sporepedia-events.json:623-839` |

## Recovered structures and fields

| Family | Structure and fields recovered | Static contract / limit |
|---|---|---|
| Noun/star roots | `cGameNounManager.mNouns +0x78`, `mNounMap +0x98`, map end `+0x9c`; `tGameDataVectorT` dirty flag `+0x00`, begin/end/capacity `+0x04/+0x08/+0x0c`; `cStarManager.mEmpires +0x150`, end `+0x154`, relationship manager `+0x204` | Borrowed manager/record pointers; map-node payload and typed projection are clear, but root publication/teardown and key invariants are not. `worker-00-roots.json:293-349,502-557,712-760` |
| Space player/empire cache | `SpacePlayerData.mPlayerEmpireID +0x18`, `mpPlayerEmpire +0x1c`; `cEmpire` political identity `+0x84`; `sSpacePlayerData` at `0x016dda8c`; vtable refcount slots `+0x00/+0x04` | AddRef-new, store-new, Release-old ordering is direct. The alternate star root remains a separate runtime-lifetime port. `worker-00-roots.json:777-1050` |
| Ordered maps | Map end `+0x04`, root `+0x0c`, node key `+0x10`, payload `+0x14`; `cGameNounManager +0x98`; `cStarManager +0x150` | `0x00e5c780` performs a lower-bound-shaped walk but rejects a greater successor in the final comparison; it is a fixed hybrid guarded-lower-bound lookup. `docs/analysis/map-semantics-resolution.md`; `worker-01-gameglobal.json:81-96` |
| Direct properties | `DirectPropertyList` map `+0x18/+0x1c`, fast count `+0x38`, values `+0x3c`, temporary `Property +0x40`; `Property` flags `+0x10`, type `+0x12` | The imported Ghidra `Property` is only a 4-byte stub while the body requires offsets through `+0x12`; repair type metadata before typed adoption. `worker-01-gameglobal.json:160-189` |
| Texture/resource lifetime | `Texture` refcount `+0x08`, resource key `+0x10`; `TexturePtr` is a one-word intrusive pointer | Assignment is static-ready; object population, deletion beyond the observed clamp, and concurrent publication remain external. `worker-01-gameglobal.json:199-225` |
| Cell object | `cCellObjectData`: model `+0x0fc`, resource `+0x108`, role/death gates `+0x110..+0x113`, guard `+0x17c`, flee/chase state `+0x21c..+0x230`, health `+0x244`, GFX association `+0x248`, scale `+0x358`, query `+0x35c`, child relation `+0x370` | Health, death, detach, and old-identity release are strong; several gate/child names and replacement semantics remain opaque. `worker-02-cell.json:53-74,255-306,428-477` |
| Cell game/stage | `cCellGame` pools `+0x01c/+0x038/+0x054`, queries `+0x40fc/+0x4100`, worlds `+0x4114/+0x4118`, avatar `+0x411c`, scale/time `+0x514c/+0x5150`, lock/mode `+0x5158/+0x5169`, serializable pointer `+0x5190`, pending event `+0x5194`, reload `+0x51d8..+0x51da` | Drain-before-create ordering is direct; exact world/hatch branch meanings and runtime setup success are not. `worker-02-cell.json:78-141,364-420` |
| Cell serializable state | `cCellSerializableData`: progression `+0x1c/+0x20/+0x24/+0x28`, kill/death `+0x6c/+0x70`, time `+0x74`, difficulty `+0x80`, mode/activity flags `+0xe0..+0xe2` | These are in-memory save-candidate fields. No disk serializer is proven by these targets. `worker-02-cell.json:124-141,317-347,388-401` |
| Cell presentation | `cCellGFX.mCellGFXObjects +0x168`, world handles `+0x161bc/+0x161ac/+0x161c8`, effects `+0x161e0`, reset state `+0x16258`; `cCellDataReference_` instance/resource fields `+0x00..+0x0c` | Presentation lifetime is separate from Cell identity and simulation state. `worker-02-cell.json:102-121,444-452` |
| Space value/container | Anonymous `0x24` value; `+0x10` range with `0x24` stride; range helper allocates `count*0x24` and copies | Cross-domain infrastructure, not a Space rule. Concrete element type and alias/deep-copy rule remain unresolved. `worker-03-space.json:142-165` |
| Communication event | `cCommEvent` is `0xa0` bytes; fields include source `+0x18`, planet key `+0x34`, file `+0x38`, dialog `+0x3c`, mission `+0x40`, priority `+0x44`, duration `+0x48`; manager storage observed around `+0x28/+0x2c` | The wrapper forwards six arguments plus zero duration and then dispatches. Public SDK identity and manager field naming remain bounded. `worker-03-space.json:253-261,276-305` |
| Space inventory | `cSpaceInventoryItem` size `0x7c`; `mItemPosition +0x24`, `mpPropList +0x30`, description `+0x34`, detail `+0x48`, item ID `+0x5c`; vtable `+0x4c=ParseProp`, `+0x44=IsAvailableInCurrentPlanet` | This is post-allocation property application, not a constructor. Property IDs and `+0x4c` semantics remain opaque. `worker-03-space.json:375-383,396-424` |
| Editor UI | `EditorUI` size 300; editor owner `+0x5c`, mode `+0x60`, control state `+0xcc`, opaque state `+0x108`, message references `+0x114/+0x118` | Dispatch mechanics are supported; message payload, complete table extent, and queue timing are not. `worker-04-editor-core.json:447-468,470-519` |
| Editor skin | `cEditorSkin` size 136; editor/model/world `+0x0c/+0x10/+0x14`, painter job `+0x5c`, material/texture `+0x60/+0x64`, feature gate `+0x84`; job is `0x84` bytes | Job and input types are not fully recovered; `IBakeManager +0x64` is the concrete submission boundary. `worker-04-editor-core.json:746-828,888-982` |
| Editor PlayMode | `EditorPlayMode` size 22,416; UI `+0x0c`, actor range `+0x7c/+0x80`, four module slots `+0xc8`, environment `+0x36d0..`, UI sequence `+0x36f0..+0x3708` | Per-frame callback order is strong; concrete module/actor types and installed vtable are not. `worker-04-editor-core.json:1048-1132,1233-1300` |
| UI shell | `SpaceGameUI` size 1,708; roots/resources at `+0x224..`, active palette `+0x23c`, field `+0x2f8`, listener block `+0x56c..+0x57c`, fight button `+0x580`, optional Simulator object `+0x694`; `cSPUITextZoom` size 120 with key/state `+0x48..+0x74` | The live writes separate `field_2F8=-1` from `mActivePaletteID=0`; contained SDK aliases are not standalone entries. `worker-05-ui-shell.json:351-430,547-567` |
| Editor name panel | `EditorNamePanel` size 56; refcount `+0x0c`, extended state `+0x10`, support gate `+0x11`, layout `+0x18`, nameable entity `+0x1c`, random-name type `+0x20`; live table `0x013f7b54` places targets at `+0x30/+0x58` | Imported vtable projection is only `0x20` bytes; exact inherited slot ownership is unresolved. `worker-05-ui-shell.json:702-727,882-904` |
| Palette UI | `PaletteUI` size 108; palette `+0x2c`, info `+0x30`, categories `+0x34`, active category `+0x64`; `PaletteCategoryUI` size 252; `PalettePageUI` size 72 | Layout/field ownership is strong. SDK `Load` aliases are interior; `GetSelectedRigblockPaint` does not name the live setter body. `worker-06-editor-support.json:69-151,186-216,342-366` |
| Timeline event data | `UI/TimelineEventSporepediaData`-like object; command-line pointer `+0x8c`, adjacent object `+0x90`, discriminators `+0x84/+0x88`, payload `+0x9c`, vtable at `+0x10`; variants allocate `0x9c/0xb0` | Local timeline/UI family; not `cSPAssetDataOTDB`, network state, or a universal event payload. `worker-07-sporepedia-events.json:267-317,471-510` |

## State and event contracts

The labels in this table are analytical contracts derived from static state writes and call edges. They do not assert listener execution or a message ABI unless the worker observed the carrier directly.

| Family | Static inference | Runtime-needed separator |
|---|---|---|
| Noun projection | `0x00b21340` transitions absent/end to dirty record, dirty to rebuilt record, clean to borrowed return; callbacks are create/clear/add/filter. `0x01021300` transitions ID `-1`, cached identity hit, exact-result refresh, and null lookup with explicit reference order. | Root slot publication/equality/teardown and callback reentrancy remain open. A successor is rejected by `0x00e5c780`; see `docs/analysis/map-semantics-resolution.md`. |
| Current empire | `0x01021300` owns one intrusive reference in `SpacePlayerData.mpPlayerEmpire`; registry erase and player-data teardown are independent. | Which path writes the player empire ID, and whether an alternate star slot can be null during a valid ID. |
| Cell combat/death | `0x00e7a7c0` rejects attack/invulnerability gates, subtracts and clamps health, optionally requests rollover, then selects non-player/player death or damage presentation. `0x00e7a4a0` sets `field_113=1`, chooses scale-dependent effects, may increment serializable `mKillCount`, and creates pooled type-6 death work. | Damage argument meanings, `field_112/+0x113/+0x17c` roles, type-6 completion, killer context, and exact ordering of AI/UI/animation/effect/death calls. |
| Cell stage/despawn | `0x00e7fd00` drains interactions, old Cells, GFX/UI/service state, restores world/progression, then creates the player and hatch presentation. `0x00e780a0` clears avatar/query/GFX/child state and always releases the old Cell after optional replacement work. | Which callers request scale replacement, whether replacement resources are consumed after old release, and whether GFX retirement is asynchronous. |
| Space communication | `0x00aeb720` creates a `0xa0` communication event, appends it through the creator, and dispatches it. It is a local in-process communication path. | Public SDK name, manager field ownership, cancellation/current-event selection, and exact event/UI timing. No network boundary is claimed. |
| Space inventory/bootstrap | `0x00c877f0` replaces `PropertyList`, extracts three opaque properties, conditionally writes `mItemPosition`, then calls `ParseProp`; `0x00de9fc0` filters service descriptors and initializes matching GGE/game-mode state. | Property names, `+0x4c` hook meaning, descriptor type, and Galaxy-entry service/UI effects. |
| Editor persistence | `0x00b28ec0` validates a path, writes a header-shaped record, closes a database/stream context, replaces the old/temp path, and conditionally updates `stars.db`. | Manager membership, second caller argument, exact rollback/atomicity, and whether the outer save envelope is part of this body. No game-save wire format is claimed. |
| Editor command/mode | `0x005e0000` routes mode, Undo, and Redo command hashes; `0x005dda30` suppresses equal mode, requests `cEditor::SetActiveMode`, performs window hooks, and stores requested mode. | Message producer/return ABI, receiver identity, exact mode window classes, and whether downstream editor animation events are synchronous or posted. |
| Editor paint/play | `0x004c5200` creates/replaces an `0x84` paint job and submits through `IBakeManager +0x64`; `0x0062c550` updates four modules, actor range, environment reactions, background/UI, and long-sequence state. | Paint input/job type, bake queueing, module/actor concrete types, and runtime callback order. |
| UI setup/text | `0x01073700` replaces UI resources, writes `field_2F8=-1`, configures listener-shaped data, and conditionally creates Simulator UI support. `0x00834fa0` has a same-binding no-op path and otherwise tears down/rebinds text/context/layout objects. | Meaning of `field_2F8`, the 25-entry registration block, `0x01074393` indirect tail, text-zoom seven-argument ABI, and service owner `0x626e3b8`. |
| Editor name panel | `0x005bf9d0` dispatches four IDs with exact payload guards and service/list callbacks. `0x005c0380` has a closed `field_10` basic/extended state machine with enable/disable literals. | Producer and payload matrix for all four IDs, `0067caa0 +0x44` ownership, seven service keys, and whether `IAppSystem +0x14` is a command, registration, or message dispatch. |
| Palette | `0x005cb5a0` loads palette definitions and constructs categories; `0x005cb240` validates and swaps active category, updates controls/page state, and emits app message `0x44ef2b8`; `0x005c53c0` and `0x005c9230` load category/page children and items. | Category/page/item records, message payload and delivery, selected paint identity, advanced item type constructors, and partial-load behavior. |
| Timeline/surrender | `0x005dda30` is local editor mode state. `0x00ff3f00` reads a local command-line-shaped pointer. `0x00dd0e10` dispatches local timeline variants and labels such as `~Epic`/`~MiniBoss`. `0x0102d1b0` coordinates surrender state, anonymous keyed space entries, achievements, and a separate `cCommEvent`. | Variant discriminators and payload ownership; first writer/release of `+0x8c`; surrender selector; exact keyed-entry consumers; listener/UI ordering. No online Sporepedia/Pollinator/network request is claimed. |

## Family exploitation

| Family | Reusable result | Required non-merge boundary |
|---|---|---|
| Root/map spine | Typed map adapter, dual alternate/canonical root ports, noun projection dirty-state, current-empire cache | `0x00e5c780` is a fixed guarded-lower-bound lookup: it rejects a greater successor and returns the end sentinel. Do not implement successor behavior or collapse alternate and canonical root slots. |
| Cell lifecycle | Damage/death split, health clamp, stage drain-before-create, identity-destructive despawn, separate GFX lifecycle | Do not let GFX/UI/effect records become Cell identity; do not call serializable candidate fields disk persistence. |
| Space local services | Communication create/dispatch wrapper, inventory PropertyList mutator, shared `0x24` infrastructure, game-entry descriptor bootstrap | Do not merge anonymous keyed space records with `cCommEvent`, App messages, or resource records. |
| Editor command and persistence | UI command routing, mode transition boundary, profile save transaction candidate, PlayMode update dispatcher | Keep transient UI/history/play state separate from profile persistence; manager membership of `0x00b28ec0` remains unconfirmed. |
| Editor derived support | Paint-job adapter, palette/category/page construction and selection | Keep UTFWin presentation and selected paint/model data separate from gameplay authority; do not use the stale `GetSelectedRigblockPaint` alias for `0x005cb240`. |
| UI shell | Space UI setup, text-zoom rebinding, EditorNamePanel message/state adapters | Service keys, IAppSystem literals, and listener-shaped blocks are not universal event ABIs; no direct gameplay authority is inferred. |
| Sporepedia/events | Local timeline-event variant/accessor boundary and local surrender orchestration | Keep `UI/TimelineEventSporepediaData`, `cSPAssetDataOTDB`, `cCommEvent`, anonymous keyed records, network services, and persistence separate. |

The priority report's U1–U9 sets are consistent with this exploitation: the root/map spine is the first cross-package prerequisite; Space and UI are small bounded sets; editor support depends on command/mode boundaries; and Sporepedia should be implemented as a local, no-network boundary only. Evidence: `docs/analysis/residual-unknown-priority.md:252-267,309-323`.

## Chokepoint propagation and package impact

The largest static fan-in is the alternate noun root `0x00b3d300` (1,097 direct callers), followed by the alternate star root `0x00b3d2a0` (314) and noun projection `0x00b21340` (254). This makes publication and root-lifetime experiments high leverage, but it does not make every caller semantically understood. The largest bounded fan-out surfaces are `0x01073700` (51 direct callees, 215 depth-2 edges), `0x0102d1b0` (53 callees), and `0x00de9fc0` (9 callees spanning storage, service enumeration, game-mode setup, and cleanup).

| Package/boundary | Improvement and readiness | Prerequisite before implementation | Interface, test, and ordering impact |
|---|---|---|---|
| `PKG-01-SHARED-STATE-ROOTS` / `PKG-11-SIM-CORE` | Static-ready for opaque borrowed manager/root adapters; current-empire cache is strong; alternate root slots remain runtime-gated. | Publisher/equality/teardown matrix for `0x0167eae0`, `0x0167eae4`, and canonical siblings; preserve the resolved guarded map contract. | Define separate root ports and borrowed ownership. Test exact hit, guarded successor rejection, end hit, null, and dual-slot phase changes. Order: map primitive → root publication/lifetime → manager projection → high-fan-in consumers. |
| `PKG-20-GAMEGLOBAL` | `DirectPropertyList` boolean and `TexturePtr` assignment are strong static adapters; mission-log manager remains opaque. | Repair the 0x54-byte `Property`/`PropertyType` layout; type a real property producer and manager publication path. | Expose normalized bool and intrusive TexturePtr operations. Test fast/slow property paths, wrong types, scratch cleanup, equal pointers, and refcount order. Order: property/resource type repair before renderer/UI consumers. |
| `PKG-06-CELL-STATE` | Strongest cell boundary is health/death/despawn; package can model health, terminal state, and old-identity release. | Resolve `field_112/+0x113/+0x17c`, `FUN_00e771d0`, and event type 6 completion. | Separate simulation health/identity from GFX/UI. Test rejected, nonlethal, lethal player, lethal non-player, invalid index, and release ordering. Order: damage gate → health mutation → death event → despawn/replacement. |
| `PKG-08-CELL-MODE` / `PKG-09-CELL-PRESENTATION` | Stage rebuild and presentation separation are statically strong at the boundary level. | Trace worldMode/worldModeValue/hatchBranch, player creation, GFX attachment, and UI/effect cleanup. | Test drain-before-create, progression writes, avatar reset, world restore, and hatch branch. Order: drain old state → restore world/progression → create/populate → presentation. |
| `PKG-12-SIM-SPACE` | Local communication, inventory-property, and bootstrap adapters are reusable. | Resolve manager layout, PropertyList property names, `ParseProp`, and descriptor/service types. | Keep `cCommEvent` ownership separate from anonymous keyed records. Test event field mapping, null PropertyList, virtual hook, descriptor filtering, and cleanup. Order: creator/layout → ownership/field contract → dispatch/consumer. |
| `PKG-10-EDITOR-DISPATCH` | Mode and command mechanics are bounded and sufficient for a local UI adapter; payload and history lifetime remain open. | Producer matrix for command hashes, `0x00587270`, `0x00591fa0`, and history/model transitions. | Return a consumption/result code without claiming a universal message ABI. Test Build/Paint/Play, Undo/Redo, unknown hash, and no-op mode. Order: command decode → mode/history request → per-frame PlayMode update. |
| `PKG-15-EDITOR-SUPPORT` | Palette load/selection/page contracts and paint submission are static-ready as local editor-support boundaries. | Type PaletteMain/PaletteInfo/PalettePage/PaletteItem, seven service keys, `0x44ef2b8`, and advanced item constructors. | Test category load, valid/invalid selection, page layout failure, standard/advanced item cases, and IBakeManager rejection. Order: page/category resources → UI construction → active category → selected-paint synchronization. |
| `PKG-18-UI-SCRIPTING` | UI shell is bounded/structural, with no direct gameplay authority. | Producer/registration matrix for four EditorNamePanel IDs; service owner/type recovery; `cSPUITextZoom` argument and `field_2F8` semantics. | Use service ports, not a universal event ABI. Test setup field separation, same-binding text zoom, four message IDs, extended no-op/enable/disable, and teardown. Order: type/vtable boundary → registration → state transition → presentation refresh. |
| `PKG-16-SPOREPEDIA-ONLINE` as local projection | Timeline and surrender functions provide a local/no-network boundary; two event contracts remain unknown. | Recover timeline discriminators and surrender carrier consumers; retain the cSPAssetDataOTDB rejection. | Test null/successor timeline field lifecycle, Epic/MiniBoss branch, keyed-pair/cCommEvent separation, and diplomacy branch. No online client or network ABI is ready. |
| Persistence boundary (`PKG-PERSIST-01`; worker Cell evidence also names `PKG-11-PERSISTENCE`) | `0x00b28ec0` is a strong candidate for path/header/stream/replacement sequencing, not a proven manager member. | Bind manager membership, exact second argument, serializer failure behavior, outer envelope, and separate `stars.db` transaction. | Test empty path, close-before-replace, missing old file, serializer failure, and conditional star database branch. Order: service binding → stream/header → close → replace → optional star database. |

Recommended implementation ordering is therefore: **(1)** preserve the resolved guarded map contract and resolve dual-slot lifecycle; **(2)** type Cell/Space state and ownership boundaries; **(3)** type editor command/mode/history and persistence; **(4)** type palette/UI service adapters; **(5)** keep Sporepedia local and resolve only the two unknown event families; **(6)** run only narrowly approved runtime separators for the remaining lifetime and timing questions.

## Contradictions and adjudications

1. **Exact find versus lower bound.** `0x00e5c780` is resolved as a fixed hybrid guarded-lower-bound lookup: the walk retains a lower-bound-shaped candidate, but the final unsigned check rejects a greater successor. `0x00b21340`, `0x00ba9370`, and `0x01021300` are exact-find dependent; `0x00b3d300` is independent. See `knowledgegraph/research/map-semantics-resolution.json` and `docs/analysis/map-semantics-resolution.md`.
2. **Alternate versus canonical roots.** `0x00b3d2a0`/`0x00b3d300` read `DAT_0167eae4`/`DAT_0167eae0`, while SDK-named siblings `0x00b3d3a0`/`0x00b3d400` read different slots. Physical separation is closed; publication, equality, and teardown are not. Evidence: `worker-00-roots.json:440-478,662-684`.
3. **SDK aliases versus live entries.** `SpaceGameUI::Load`, `EditorNamePanel::HandleMessage`, `EditorNamePanel::SetExtended`, `PaletteUI::Load`, `PaletteCategoryUI::Load`, and `PalettePageUI::Load` are interior aliases in several workers. Use the containing live body unless an independent entry or constructor proves otherwise. Evidence: `worker-05-ui-shell.json:295-300,477-482,643-647,828-833`; `worker-06-editor-support.json:188-203,342-351,440-451,553-562`.
4. **`GetSelectedRigblockPaint` versus the live palette setter.** The SDK alias at `0x005cb2a0` conflicts with the live `0x005cb240` body, which is an active-category setter. Do not promote the stale alias. Evidence: `worker-06-editor-support.json:342-358`.
5. **UI vtable projection versus live table.** Imported `EditorNamePanel` projection is `0x20` bytes, while live table `0x013f7b54` places `0x005bf9d0` at `+0x30` and `0x005c0380` at `+0x58`. Exact inherited slot ownership is unresolved. Evidence: `worker-05-ui-shell.json:719-727,896-904`.
6. **`cSPUITextZoom` ABI.** The target has seven stack arguments and `RET 0x1c`, while the contained SDK alias has six total parameters. Preserve the observed mechanics and do not assign the imported ABI. Evidence: `worker-05-ui-shell.json:477-525,568-578,613-625`.
7. **Sporepedia identity.** The 0x78-byte imported `cSPAssetDataOTDB` cannot own the observed `+0x84/+0x88/+0x9c` fields or 0x9c/0xb0 variants. The live allocation/vtable family is local `UI/TimelineEventSporepediaData`-like data. Evidence: `worker-07-sporepedia-events.json:241-251,301-317,501-510`.
8. **Local event versus online event.** No target has a direct network, socket, protocol, or online-request edge. `Pollinator`/Sporepedia names are local namespace/package labels, not network proof. Evidence: `worker-07-sporepedia-events.json:41-45,91-100,659-670`.
9. **Space carriers.** The anonymous keyed 0x0c/27-slot plus 0x06/24-slot pair and the 0xa0-byte `cCommEvent` are produced together in surrender paths but have different allocation, layout, and ownership graphs. Co-production is not payload identity. Evidence: `worker-07-sporepedia-events.json:672-699,717,782-813`.
10. **IAppSystem/UI events.** The workers observe `IAppSystem` vtable calls, listener-shaped blocks, and service callbacks, but not `MessageSend`, `MessagePost`, or `ProcessQueue`. Queue timing and universal message identity remain unresolved. Evidence: `worker-05-ui-shell.json:729-759,905-914`; `worker-06-editor-support.json:407-420`.
11. **Persistence ownership.** `0x00b28ec0` is assigned to the editor-core worker but its body is a save/profile transaction candidate. No `cGamePersistenceManager` member binding or outer envelope is established. Evidence: `worker-04-editor-core.json:116-149,222-244,344-361`.
12. **Cell field names.** Several imported Cell names are placeholders (`field_112`, `field_113`, `field_17c`, `field_370`); their offsets and transition behavior are stronger than their semantic names. Evidence: `worker-02-cell.json:53-74,344-360,428-477`.

## Highest-value remaining chokepoints and unresolved functions

| Priority | Chokepoint / unresolved set | Why it is highest value | Smallest useful next evidence |
|---:|---|---|---|
| 1 | `0x00e5c780` → `0x00b21340` → `0x00b3d300`/`0x01021300` map/root spine | The helper contract is statically resolved as guarded exact-result selection; the remaining gate is root publication/lifetime and callback behavior. | Preserve the guarded candidate implementation and add only the approved dual-slot publication/equality/teardown trace. |
| 2 | `0x00b3d2a0` and `0x00b3d300` with canonical `0x00b3d3a0`/`0x00b3d400` | Highest direct fan-in and the principal root-lifetime ambiguity. | Read-only dual-slot trace across initialization, mode transition, and teardown. |
| 3 | `0x00e7a7c0`/`0x00e7a4a0` damage/death and `0x00e780a0` despawn | Joins health, event, presentation, pool identity, and replacement semantics for Cell. | One permitted damage/death sequence and one despawn/replacement sequence; capture field writes and event/effect order. |
| 4 | `0x00e7fd00` stage rebuild | Determines drain order, world/progression restoration, player creation, and hatch branch across several packages. | One initial and one reload sequence with pool/UI/GFX/world/progression snapshots. |
| 5 | `0x005bf9d0`/`0x005c0380` with `0x005c0100` and `0x005bfd40` | EditorNamePanel is vtable/listener-dispatched, so direct-call counts understate its service and message surface. | Producer/registration/payload matrix for the four IDs and the extended-state literal/service sequence. |
| 6 | `0x00aeb720` → `0x00aeb160` → `0x00aebe90`, plus `0x00e39ab0` | Separates the `cCommEvent` and anonymous keyed-space carrier graphs used by surrender. | One local surrender trace with object identity, vtable, key, payload, list insertion, and release order. |
| 7 | `0x00b28ec0` persistence transaction | Separates profile save/stream/replacement from editor asset save and `stars.db`. | Manager binding, serializer failure/close order, and a bounded save/load round-trip only if required. |
| 8 | `0x00ff3f00`/`0x00dd0e10` timeline family | Two of the four Sporepedia targets remain unknown because field subtype and variant discriminators are not named. | Local non-null field lifecycle and one Epic/MiniBoss variant; keep the no-network boundary explicit. |
| 9 | `0x01073700`/`0x00834fa0` UI setup/text-zoom | High fan-out crosses resource, root, optional Simulator, and presentation services. | Resolve `field_2F8`, registration block, indirect tail, seven-argument ABI, and service `0x626e3b8`. |
| 10 | `0x00b3d4f0` mission-log manager | Opaque global service publication and null/lifetime window block UI mission-log consumers. | One watchpoint from first publication through first consumer and teardown/replacement. |

No runtime experiment was run for this report. The listed experiments are future evidence gates only; they do not authorize original-process execution, implementation, compatibility claims, or Ghidra/KG mutation.
