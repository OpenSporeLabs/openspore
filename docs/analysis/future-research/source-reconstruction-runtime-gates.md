# Source Reconstruction Runtime Gates

These gates do not block static reconstruction. Each item records the smallest original-process observation needed to replace an explicit `RE:` uncertainty with evidence. No experiment is authorized by this file. Human approval, the machine lock, a pinned executable/environment, and the repository observatory safety rules are required.

## Global accessor gates

### gate-simulator-global-slots

- **Affected functions:** `0x00b3d300`, `0x00b3d2a0`, `0x00b3d4f0`.
- **Hypotheses:** each function returns the value of its named global slot; slot owners are distinct service pointers; uninitialized slots are null or an engine sentinel.
- **Smallest experiment:** after a positive boot control, read the three slots at a single post-initialization point and record owner identity, value, and subsequent call-site use.
- **Expected evidence:** raw event contains slot addresses, read values, lifecycle timestamp, and one representative caller result.
- **Acceptance criterion:** static accessor bodies and slot ownership agree across repeated runs; null/sentinel behavior is explicit.
- **Affected types:** `OpaqueSimulatorGlobalAccessor`, service-handle types.
- **Affected edges:** `PKG-01` to `PKG-06`, `PKG-11`, and dependent singleton consumers.

## Cell state and lifecycle gates

### gate-cell-damage

- **Affected functions:** `0x00e7a7c0`, `0x00e7a4a0`.
- **Hypotheses:** health is reduced by a computed damage amount; zero health enters a death animation/event path; invulnerability and attack checks precede damage.
- **Smallest experiment:** after a Cell-positive control, correlate one controlled damage event with object fields, return/flag behavior, animation/effect calls, and resulting health.
- **Expected evidence:** pre/post field samples and ordered static call-path observations.
- **Acceptance criterion:** all branch conditions and field mutations are observed or explicitly rejected.
- **Affected types:** `OpaqueCellObjectData`, `CellDamageContext`.
- **Affected edges:** `PKG-06` to `PKG-09` presentation and `PKG-17` animation.

### gate-cell-reset

- **Affected function:** `0x00e7fd00`.
- **Hypotheses:** reset writes the observed global state and mode tables before dispatching manager/UI initialization.
- **Smallest experiment:** observe one reset/reinitialization with stable object identity and no unrelated input.
- **Expected evidence:** ordered global writes, mode values, and called manager results.
- **Acceptance criterion:** static write set and dispatch order match the trace or the difference is recorded as a bounded failure.
- **Affected types:** `OpaqueCellGameResetContext`, `CellModeContext`.
- **Affected edges:** `PKG-06` to `PKG-08`, `PKG-09`, and `PKG-11`.

### gate-cell-lifetime

- **Affected function:** `0x00e780a0`.
- **Hypotheses:** removal is conditional on object existence; optional animation/effect dispatch precedes registry deletion; callbacks observe a stable object identity.
- **Smallest experiment:** remove one controlled object and record pool membership, callback order, and registry state.
- **Expected evidence:** pre/post object identity and ordered lifecycle callbacks.
- **Acceptance criterion:** no unobserved release or callback is required to explain the static body.
- **Affected types:** `OpaqueCellObjectData`, `CellLifecycleContext`.
- **Affected edges:** `PKG-06` to `PKG-07`, `PKG-09`, and resource lifetime.

## Palette and editor gates

### gate-palette-factory

- **Affected function:** `0x005cb5a0`.
- **Hypotheses:** the stack contains four values despite five decompiler labels; factory callbacks return concrete palette/UI objects; vector growth preserves construction order.
- **Smallest experiment:** open the palette with a fixed empty project and record argument values, factory return identities, and collection writes.
- **Expected evidence:** call-entry bytes, factory/vtable calls, and resulting collection state.
- **Acceptance criterion:** the canonical prototype and source-like object ownership are supported by bytes and one runtime instance.
- **Affected types:** `OpaquePaletteConstructionContext`, `OpaquePaletteItem`.
- **Affected edges:** `PKG-15` to `PKG-18` UI shell.

### gate-palette-selection

- **Affected function:** `0x005cb240`.
- **Hypotheses:** invalid indices are rejected; old selection deactivates before new selection activates; vtable `+0x28` drives both transitions.
- **Smallest experiment:** select invalid, same, and distinct palette entries in a fixed project.
- **Expected evidence:** ordered deactivation/activation calls and UI state.
- **Acceptance criterion:** branch and side-effect order match the static body for all three cases.
- **Affected types:** `OpaquePaletteSelectionContext`.
- **Affected edges:** `PKG-15` to editor dispatch.

### gate-palette-setup

- **Affected function:** `0x005c53c0`.
- **Hypotheses:** resource-ID replacement occurs before UI setup; app-system and swatch-manager lookups return the objects used by callbacks.
- **Smallest experiment:** initialize a fixed palette and record resource lookup, replacement, and callback order.
- **Expected evidence:** object identities and ordered calls.
- **Acceptance criterion:** static construction order and resource provenance are corroborated.
- **Affected types:** `OpaquePaletteApplicationContext`.
- **Affected edges:** `PKG-15` to `PKG-03` resource boundary.

### gate-palette-layout

- **Affected function:** `0x005c9230`.
- **Hypotheses:** the function has five stack arguments; layout values determine page-item allocation and collection writes.
- **Smallest experiment:** render one fixed palette page with deterministic layout input.
- **Expected evidence:** call-entry argument values, layout service results, item collection, and failure path if any.
- **Acceptance criterion:** the ABI and page-item loop are independently supported.
- **Affected types:** `OpaquePalettePageContext`, `OpaquePaletteItem`.
- **Affected edges:** `PKG-15` to `PKG-18` and `PKG-09`.

### gate-editor-mode

- **Affected function:** `0x005dda30`.
- **Hypotheses:** mode values `0`, `1`, and `2` are distinct; the guard suppresses redundant transitions; vtable `+0x7c` is the mode-specific action.
- **Smallest experiment:** request each mode and a repeated mode in a fixed editor session.
- **Expected evidence:** field transition, manager lookup, deactivation, and callback order.
- **Acceptance criterion:** all four requests match the static state machine.
- **Affected types:** `OpaqueEditor`, `OpaqueEditorModeManager`.
- **Affected edges:** `PKG-10` to `PKG-15` and `PKG-18`.

## Indirect dispatch and Space gates

### gate-indirect-cell-state

- **Affected function:** `0x00ff3f00`.
- **Hypotheses:** `0x00ff3f00` is a local timeline-event command-line pointer accessor on `OpaqueTimelineEventData`; its `+0x8c` field is a raw pointer/word and has no Cell-owner or online-network classification.
- **Smallest experiment:** identify a local timeline-event object and sample `+0x8c` before/after a stable local operation.
- **Expected evidence:** object identity, `+0x8c` value, local timeline-event ownership, and the absence of a network edge.
- **Acceptance criterion:** local timeline-event ownership and field behavior are corroborated or the function remains opaque; online semantics are not assigned without evidence.
- **Affected types:** `OpaqueTimelineEventData`.
- **Affected edges:** `PKG-01` to local timeline-event consumers; no online/network edge is established.

### gate-gameglobal-dispatch

- **Affected function:** `0x00dd0e10`.
- **Hypotheses:** vtable `+0x0c` is a precondition/dispatch operation; switch cases 1, 2, 4, and 5 select distinct service paths.
- **Smallest experiment:** obtain one object and exercise each reachable state while recording `+0x84` and `+0x88`.
- **Expected evidence:** object identity, field samples, vtable call, switch case, and returned object.
- **Acceptance criterion:** all reachable cases and return ownership are identified.
- **Affected types:** `OpaqueGameObject`.
- **Affected edges:** `PKG-20` to `PKG-10`, `PKG-11`, and `PKG-12`.

### gate-space-communication

- **Affected function:** `0x0102d1b0`.
- **Hypotheses:** distance comparison and negative interval/seed value select communication states; cleanup and event creation occur in the observed order.
- **Smallest experiment:** execute one controlled communication path with fixed nearby/far object positions.
- **Expected evidence:** pre/post object fields, distance result, cleanup events, created event, and achievement-manager result.
- **Acceptance criterion:** the state machine and event payload ownership are independently observed.
- **Affected types:** `OpaqueSpaceContext`, `OpaqueSpaceEvent`.
- **Affected edges:** `PKG-12` to `PKG-11`, `PKG-16`, and achievement services.

## Collection and editor gates

### gate-map-root-publication-and-caller-fault-paths

- **Affected function:** `0x00e5c780`; dependent exact-find consumers include `0x00b21340`, `0x00ba9370`, and `0x01021300`.
- **Hypotheses:** live maps use the recovered 16-byte node, 20-byte keyed-entry, and 28-byte map layout; roots are published before caller use; the fixed guarded-hybrid contract does not change under normal single-threaded access.
- **Smallest experiment:** observe one known exact-find call with a stable map and record root, anchor, query, retained candidate, and returned sentinel/node.
- **Expected evidence:** pre/post map identity, node keys, result pointer, and one caller acceptance/rejection branch.
- **Acceptance criterion:** observed traversal and final exact-key guard match the resolved static contract; fault behavior is recorded without generalizing malformed inputs.
- **Affected types:** `OrderedMap`, `OrderedMapNode`, `OrderedMapEntry`.
- **Affected edges:** `PKG-20` to `PKG-11` and `PKG-12`.

### gate-editor-model-setcolor-symbol-mapping

- **Affected function:** `0x004ae250`.
- **Hypotheses:** the ECX-only executable entry is intentionally empty or the SDK address mapping is incomplete; direct callers do not supply the imported formal index/color frame.
- **Smallest experiment:** capture one direct table-mediated call and its receiver, ESP argument area, and post-call register state.
- **Expected evidence:** call-site pushes, ECX receiver, entry bytes, and observed EAX preservation.
- **Acceptance criterion:** the raw ECX-only and formal adapter boundaries are confirmed without assigning setter semantics unsupported by bytes.
- **Affected types:** `OpaqueEditorModel`, `EditorModelColor`.
- **Affected edges:** `PKG-10` to editor model and UI callback owners.

### gate-editor-ui-command-dispatch

- **Affected function:** `0x005e0000`.
- **Hypotheses:** the installed IMessageListener vtable entry is reachable; command hashes and payload variants map to the recovered routes; the producer `0x70218642` remains unable to enter the live mode-2 branch.
- **Smallest experiment:** deliver one readiness-gated component command with a known hash and record branch order through the terminal callback.
- **Expected evidence:** readiness flags, message fields, vtable slots, helper calls, saved dispatch bit, and boolean return.
- **Acceptance criterion:** the selected static route and return match; the mode-2 contradiction remains explicit if reproduced.
- **Affected types:** `OpaqueEditorUI`, `OpaqueUiMessage`, `OpaqueDispatchTarget`, `OpaquePreferenceQuery`.
- **Affected edges:** `PKG-10` to `PKG-15`, `PKG-18`, and editor services.

## Simulator core and Sporepedia gates

### gate-star-predicate-function-table

- **Affected function:** `0x00c8b6b0`.
- **Hypotheses:** the function-pointer slot at `0x014739b0` is invoked with a four-byte `StarType` word; consumers test the full EAX word or only AL.
- **Smallest experiment:** identify one indirect consumer and record its argument, full EAX result, and branch width.
- **Expected evidence:** table owner, target signature, argument value, result bits, and caller test.
- **Acceptance criterion:** the constant `0x0355c93a` return and ignored argument are observed without normalizing it to canonical bool.
- **Affected types:** `StarType`.
- **Affected edges:** `PKG-11` to star/function-table consumers.

### gate-noun-projection-callbacks-and-map-ownership

- **Affected function:** `0x00b21340`.
- **Hypotheses:** create, clear, filter, and add callbacks are non-null for live noun maps; insertion helper ownership and returned vector lifetime match the observed order.
- **Smallest experiment:** refresh one dirty noun projection with a fixed noun ID and record map result, callback order, dirty-byte transition, and later destruction.
- **Expected evidence:** map node identity, callback receivers, list nodes, mutation timing, and ownership lifetime.
- **Acceptance criterion:** all callback calls and the final dirty clear match; no inserted null guard or second key check is required.
- **Affected types:** `NounProjection`, `NounProjectionVector`, `NounListNode`.
- **Affected edges:** `PKG-11` to noun data containers and map allocation.

### gate-star-manager-and-empire-map-lifecycle

- **Affected function:** `0x00ba9370`.
- **Hypotheses:** the alternate star root at `0x0167eae4` is a valid empire-map owner; map keys remain synchronized with payload identity; returned empire pointers remain valid while borrowed.
- **Smallest experiment:** perform one non-`0xffffffff` lookup through the alternate root and record manager, map, key, payload, and later replacement.
- **Expected evidence:** root value, `+0x150` map, helper result, `+0x14` payload, and lifetime across one controlled replacement.
- **Acceptance criterion:** hit, successor-shadow rejection, and payload lifetime match without assuming a successor-tolerant lower bound.
- **Affected types:** empire-map entry and bounded star-manager prefix.
- **Affected edges:** `PKG-11` to `PKG-12` current-player cache.

### gate-sporepedia-editable-vtable

- **Affected function:** `0x00641400`.
- **Hypotheses:** stored pointers select a concrete vtable owner whose slot `+0x60` returns the editable byte consumed by the callback.
- **Smallest experiment:** invoke one table-mediated asset-data pointer with a valid vtable and record the slot target and AL result.
- **Expected evidence:** receiver identity, vtable identity, slot target, return bytes, and caller use.
- **Acceptance criterion:** the exact tail transfer and return width are observed; null and empty-object faults remain explicit.
- **Affected types:** `Pkg16AssetData`, `Pkg16EditableSlot`.
- **Affected edges:** `PKG-16` to local Sporepedia asset-data owners.

### gate-sporepedia-metadata-word-callers

- **Affected function:** `0x00641770`.
- **Hypotheses:** the full word at receiver `+0x28` is a metadata pointer/raw carrier; callers test the complete EAX value despite the SDK `HasName` alias.
- **Smallest experiment:** call one direct caller with two valid metadata objects and record the producer, returned word, and branch width.
- **Expected evidence:** `+0x28` value, full EAX result, comparison mask, and selected object identity.
- **Acceptance criterion:** all 32 bits are consumed unchanged or the caller-specific projection is documented.
- **Affected types:** `Pkg16MetadataWord`, `Pkg16AssetData`.
- **Affected edges:** `PKG-16` to local Sporepedia metadata consumers.

### gate-sporepedia-x87-address-mapping

- **Affected function:** `0x006417c0`; adjacent contract candidate `0x006417d0` remains outside this batch.
- **Hypotheses:** the SDK GetAssetID address mapping is shifted; `0x006417c0` intentionally returns x87 `-1.0`, while `0x006417d0` owns the bool/uint64 destination-shaped body.
- **Smallest experiment:** identify the two stored vtable slots and record which address each concrete owner dispatches.
- **Expected evidence:** receiver, vtable slot, selected address, x87 or AL/result behavior, and destination mutation.
- **Acceptance criterion:** address identity and behavior are separated; no bool destination write is attributed to `0x006417c0`.
- **Affected types:** `Pkg16AssetData`, global raw float at `0x013eb1bc`.
- **Affected edges:** `PKG-16` to SDK address mapping and concrete vtables.

## Space player and communication gates

### gate-space-player-data-and-empire-lookup

- **Affected function:** `0x01021300`.
- **Hypotheses:** `Simulator::sSpacePlayerData` and the alternate star root are published; the cached empire identity fast path and distinct-pointer AddRef/store/Release sequence are live.
- **Smallest experiment:** refresh one current-player empire with the same ID and then with a distinct valid ID.
- **Expected evidence:** global state, `+0x18` ID, cached pointer, `+0x84` identity, root/find calls, vtable reference calls, and resulting cache.
- **Acceptance criterion:** borrowed return, no-op identity path, and replacement order match; no post-lookup identity check is invented.
- **Affected types:** `SpacePlayerCache`, `EmpireLookup`, `Empire`.
- **Affected edges:** `PKG-12` to `PKG-11` empire lookup and intrusive ownership.

### gate-space-comm-event-lifecycle

- **Affected functions:** `0x00aeb160`, `0x00aea250`, `0x00aea5d0`, `0x00aea230`, and the existing wrapper `0x00aeb720`.
- **Hypotheses:** callers provide a live `cCommManager`; creator `0x00aeb160` queues a `cCommEvent`, `0x00aea250` establishes the fixed event prefix, `0x00aea5d0` performs ref-aware vector insertion, `0x00aea230` assigns the manager string range, and dispatcher `0x00aebe90` consumes the wrapper result.
- **Smallest experiment:** deliver one controlled six-word communication payload and record creator writes, vector insertion/growth, string assignment, queue insertion, current-event replacement, and release order.
- **Expected evidence:** manager identity, payload fields, event type, vector storage, creator result, dispatch target, and final ownership state.
- **Acceptance criterion:** creation precedes dispatch, all six words remain opaque, vector growth and release order match, and the wrapper adds no reference operation or guard.
- **Affected types:** `cCommManager`, `cCommEvent`, `cCommVector`, `cCommStringRange`, `OpaqueWord`.
- **Affected edges:** `PKG-12` to communication creator, dispatcher, vector, string, and event consumers.

### gate-editor-query-helpers

- **Affected function:** `0x005dfd00`.
- **Hypotheses:** the query context, service, material manager, transition callbacks, and app-properties pointer are live objects; command IDs and material constants are stable.
- **Smallest experiment:** issue one known editor query command with deterministic material and transition services.
- **Expected evidence:** context fields, command branch, material registration, callback order, and final active state.
- **Acceptance criterion:** the selected dispatch branch, material fallback, state writes, and unresolved callback boundaries match the static body.
- **Affected types:** `OpaqueEditorQueryContext`, `OpaqueService`, `OpaqueMaterialManager`, `OpaqueAppProperties`.
- **Affected edges:** `PKG-10` to editor services and `PKG-18` UI callbacks.

### gate-editor-query-property-callback

- **Affected function:** `0x005dd750`.
- **Hypotheses:** the property setter callback is live and the query flag words have stable ownership.
- **Smallest experiment:** reset one property-backed preference and record callback arguments, flag writes, and returned query identity.
- **Expected evidence:** callback receiver, property value, write order, and caller use.
- **Acceptance criterion:** clear-before-callback order and query return width are observed.
- **Affected types:** `OpaquePreferenceQuery`, `OpaquePropertyValue`.
- **Affected edges:** `PKG-10` to property and editor preference owners.

### gate-editor-query-global-callback

- **Affected function:** `0x0093db80`.
- **Hypotheses:** global callback `0x0154eb48` is non-null and flag bits select callback and clear paths.
- **Smallest experiment:** call the function with each observed flag combination and record callback presence, arguments, and resulting flags.
- **Expected evidence:** callback target, six argument words, flag mask, and null-path return.
- **Acceptance criterion:** callback-before-clear ordering and all observed bit cases are confirmed.
- **Affected types:** `OpaquePreferenceQuery`, `OpaqueQueryCallback`.
- **Affected edges:** `PKG-10` to the global callback owner and all 194 direct callers.

### gate-editor-query-service-slot

- **Affected function:** `0x005ca960`.
- **Hypotheses:** the supplied service is live and vtable slot `+0x0c` accepts literal `0x8ed27e7a`.
- **Smallest experiment:** call the accessor with null and one live service whose slot target is observable.
- **Expected evidence:** null return, vtable target, literal argument, and returned service identity.
- **Acceptance criterion:** cdecl stack ABI and null behavior match the observed body.
- **Affected types:** `OpaqueService`.
- **Affected edges:** `PKG-10` to service dispatch and downstream service owners.

### gate-ui-scripting-message-routes

- **Affected functions:** `0x005bf9d0` and `0x005c0100`.
- **Hypotheses:** message IDs, subtype checks, owner IDs, shell callbacks, and linked service traversal are stable.
- **Smallest experiment:** deliver one message for each observed type/subtype/owner route with a deterministic shell and service graph.
- **Expected evidence:** selected branch, payload words, callback order, fallback route, and return value.
- **Acceptance criterion:** route priority, owner fallback, and callback order match the static bodies.
- **Affected types:** `OpaqueUiShell`, `OpaqueUiMessage`, `OpaqueUiObject`, `OpaqueUiVtable`.
- **Affected edges:** `PKG-18` to editor, service, and presentation owners.

### gate-ui-scripting-registration-state

- **Affected function:** `0x005c0380`.
- **Hypotheses:** the enable byte, three-word text range, text provider, and application-system IDs have stable ownership.
- **Smallest experiment:** toggle the shell through unchanged, enabled, and disabled states with a bounded text provider.
- **Expected evidence:** state write, provider callback, range writes, application-system result, and conditional release.
- **Acceptance criterion:** state-first ordering and provider/release branches match the static body.
- **Affected types:** `OpaqueUiShell`, `OpaqueUiObject`.
- **Affected edges:** `PKG-18` to UI registration and text services.

### gate-space-comm-string-assignment

- **Affected function:** `0x00aea230`.
- **Hypotheses:** manager `+0x64` owns a string range and the downstream assignment preserves self-range and allocator behavior.
- **Smallest experiment:** assign a self-range and one distinct bounded range.
- **Expected evidence:** target range, self-range bypass, begin/end forwarding, and resulting storage.
- **Acceptance criterion:** pointer and capacity ownership are identified without assuming string semantics.
- **Affected types:** `cCommManager`, `cCommStringRange`.
- **Affected edges:** `PKG-12` to communication string ownership.

### gate-space-inventory-entry

- **Affected functions:** `0x00c877f0` and `0x00de9fc0`.
- **Hypotheses:** property lists, property records, game-entry ranges, behavior cleanup, and allocator services are live and correctly owned.
- **Smallest experiment:** construct one inventory item and execute one bounded game-entry record path with deterministic property and cleanup services.
- **Expected evidence:** list AddRef/store/Release order, text reads, record append, descriptor loop, mode initialization, cleanup, and final ownership.
- **Acceptance criterion:** field offsets, record order, null paths, and cleanup/free order match the static bodies.
- **Affected types:** `InventoryItem`, `InventoryEntryContext`, `PropertyRecord`, `GameEntryRange`, `InventoryEntryServices`.
- **Affected edges:** `PKG-12` to property, game-entry, mode, behavior, and allocator services.

### gate-map-insertion

- **Affected functions:** `0x00ba8420` and `0x00ba83a0`.
- **Hypotheses:** predecessor handoff, duplicate detection, node allocation, rebalance, and map-size updates are stable.
- **Smallest experiment:** insert one absent key, one duplicate key, and one key requiring each observed side decision.
- **Expected evidence:** predecessor walk, duplicate sentinel, allocation result, node links, rebalance call, size, and inserted flag.
- **Acceptance criterion:** unsigned-key order, malformed-tree boundary, allocator failure, and output ownership remain explicit.
- **Affected types:** `OrderedMap`, `OrderedMapEntry`, `MapInsertPair`, `MapInsertResult`.
- **Affected edges:** `PKG-20` to map callers and allocator ownership.

### gate-property-direct-bool

- **Affected function:** `0x006a25a0`.
- **Hypotheses:** the live temporary `Property` is stack-local, list bytes at `+0x40` remain opaque, materialization and cleanup operate on the local object, and the direct callback receives `(1, Property*, 0, 0, 0, 0)` when flags contain `0x04`.
- **Smallest experiment:** read one fast property and one exact-key map property with a deterministic callback and record the temporary address, list-tail bytes, normalized result, and callback arguments.
- **Expected evidence:** fast/map branch identity, local Property address, unchanged `+0x40` bytes, materializer/normalizer order, and callback order.
- **Acceptance criterion:** static stack-local lifetime, opaque tail isolation, flags/type normalization, and cleanup ordering are observed.
- **Affected types:** `DirectPropertyList`, `Property`, `PropertyAdapterServices`.
- **Affected edges:** `PKG-20-PROPERTY-ADAPTER` to `0x006a19b0`, `0x00542b80`, `0x0093db80`, and the global callback boundary.

### gate-texture-ptr-refcount

- **Affected function:** `0x00576650`.
- **Hypotheses:** the receiver slot stores an opaque texture pointer, refcount is at `+0x08`, equality is a no-op, rhs is acquired before publication, old is released after publication, and the below-one path adds one without deleting.
- **Smallest experiment:** replace one slot with null, the same pointer, and a distinct valid opaque texture while recording refcount and publication order.
- **Expected evidence:** receiver/rhs register and stack values, refcount writes, clamp path, and absence of a delete call.
- **Acceptance criterion:** exact x86-32 thiscall ABI and all refcount/order outcomes are observed; concrete Texture ownership remains opaque.
- **Affected types:** `TexturePtr`, `OpaqueTexture`.
- **Affected edges:** `PKG-20-RESOURCE-ADAPTER` to texture producers and intrusive lifetime owners.

## Source-wave5 creature and diplomacy gates

### gate-creature-accessor-field

- **Affected function:** `0x00b1fdb0`.
- **Hypotheses:** the ECX receiver is noun-manager-compatible, the returned word at `+0x54` is unchanged, and callers consume it without the accessor adding ownership or mutation.
- **Smallest experiment:** at one naturally reachable noun-manager consumer, record receiver identity, the raw `+0x54` word, EAX, and the first consumer operation.
- **Expected evidence:** matching receiver pointer, raw field bits, returned bits, consumer identity, and a stable object identity when the word is independently proven pointer-like.
- **Acceptance criterion:** load and return equality are observed for representative caller families without promoting the SDK `mpAvatar` name or ownership without independent evidence.
- **Affected types:** `OpaqueNounManager`, `OpaqueNounManagerField`.
- **Affected edges:** `PKG-13-CREATURE-ACCESSOR` to `PKG-13-SIM-CREATURE-TRIBECIV` and the broad noun-manager consumer set.

### gate-diplomacy-transition-00d01e30

- **Affected function:** `0x00d01e30`.
- **Hypotheses:** the normalized current-player record drives the conditional event path, forward and reverse relationship entries clear bit `0x02`, and c32830 pair calls use first/second ECX-plus-stack order.
- **Smallest experiment:** observe one naturally reachable directed relationship transition with a stable current-player record and capture both directed entries, pair receiver/stack order, event id, and cleanup order.
- **Expected evidence:** current-player identity, selected map identities, lookup results, flag samples before/after, pair order, event carrier fields, and c31c50 cleanup.
- **Acceptance criterion:** the observed branch, bit mutations, pair order, event id `0x4445D44`, and cleanup order match without inventing a concrete relationship owner.
- **Affected types:** `OpaqueRelationshipManager`, `OpaqueTransitionRecord`, `OpaqueEventRecord`, `DiplomacyTransitionPorts`.
- **Affected edges:** `PKG-13-SIM-DIPLOMACY-TRANSITIONS` to PKG-12 current-player cache and PKG-13 relationship/event services.

### gate-diplomacy-transition-00d038e0

- **Affected function:** `0x00d038e0`.
- **Hypotheses:** the predicate gates all mutation, c327a0 uses first/second ECX-plus-stack order, and `0x00f67d90` consumes the b3d300 root in ECX before c78450 receives the returned follow-up owner in ECX and first on the stack.
- **Smallest experiment:** capture one predicate-false path and one predicate-true current-player path with stable root and callback identities.
- **Expected evidence:** predicate result, cleanup-only branch, directed flag clears, pair order, b3d300 root, root_followup ECX value and EAX result, c78450 receiver/stack record, and final cleanup.
- **Acceptance criterion:** both predicate outcomes and the complete root receiver/return/callback identity chain are observed or remain explicitly opaque.
- **Affected types:** `OpaqueRelationshipManager`, `OpaqueTransitionRecord`, `DiplomacyTransitionPorts`.
- **Affected edges:** `PKG-13-SIM-DIPLOMACY-TRANSITIONS` to PKG-12 cache, PKG-13 primitives, and root service callbacks.

### gate-diplomacy-transition-00d065a0

- **Affected function:** `0x00d065a0`.
- **Hypotheses:** a nonzero predicate returns without cleanup, directed entries set bit `0x01` and clear bit `0x02`, c7bd40 follows the explicit root-follow-up owner chain, and the array sequence carries selector/object stack words from `0x0067cb30` into `0x0060d860` with `RET 8`.
- **Smallest experiment:** observe one current-player branch and one distinct-record branch with stable roots, entries, array services, and apply callbacks.
- **Expected evidence:** predicate result, directed flag order, c345f0 receiver/stack order, root and follow-up owner identities, c30c80 receiver, stack words at both array calls, ESP before/after, and reverse/forward apply order.
- **Acceptance criterion:** branch order and every receiver/stack word match the reviewed static mechanics, including no cleanup by `0x0067cb30` and exactly eight-byte cleanup by `0x0060d860`.
- **Affected types:** `OpaqueRelationshipManager`, `OpaqueTransitionRecord`, `DiplomacyTransitionPorts`.
- **Affected edges:** `PKG-13-SIM-DIPLOMACY-TRANSITIONS` to PKG-13 relationship, root, array, and transition services.

### gate-diplomacy-transition-00d06920

- **Affected function:** `0x00d06920`.
- **Hypotheses:** the nested `0x00d038e0` result is followed by directed bit `0x02` updates, c34680 first/second ECX-plus-stack order, event `0x4445D43`, and a post-transition call gated by `0x00885c90` reading current-root `+0x1d8`.
- **Smallest experiment:** observe one nested transition with stable relationship, event, current-root, and post-transition service identities.
- **Expected evidence:** nested call order, directed entries and flags, pair receiver/stack order, event carrier offsets, current-root ECX value, `+0x1d8` result, first-record key comparison, selector `0x68B2938`, float `1.0`, and cleanup order.
- **Acceptance criterion:** nested/event/post order and the current-root receiver/member contract are observed without promoting the event, root, or post-transition owner.
- **Affected types:** `OpaqueRelationshipManager`, `OpaqueTransitionRecord`, `OpaqueEventRecord`, `OpaqueCurrentRoot`, `DiplomacyTransitionPorts`.
- **Affected edges:** `PKG-13-SIM-DIPLOMACY-TRANSITIONS` to PKG-12 current-root/player state, PKG-13 primitives, event, and post-transition services.

## Gate policy

A zero-event, failed-boot, uncorrelated, or provenance-incomplete run is a negative result. It cannot promote a semantic status, close an unresolved question, or establish original compatibility. When evidence arrives, update the function record first, then spawn only dependent re-review or body-reconstruction work.
