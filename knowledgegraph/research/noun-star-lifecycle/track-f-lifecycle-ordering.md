# Track F — Noun/Star lifecycle ordering

**Status:** complete static report; runtime gaps remain explicitly unresolved.  
**Scope:** initialization → manager availability → publication → lookup → materialization → consumer use → cache/invalidation → teardown, with constructors/destructors, app startup/shutdown, mode enter/exit, scenario switching, world/planet transitions, persistence restore candidates, and reset paths.  
**Binary:** `SporeApp.exe` 3.1.0.22, x86 LE 32-bit, image base `0x00400000`, SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`.  
**Method:** read-only Ghidra decompilation, disassembly, xrefs, data-table inspection, and committed KG/docs. No runtime trace, source implementation, `SPORE/` access, or artifact mutation was performed.

## Executive result

The strongest proven local ordering is:

```text
cGameNounManager allocation
  -> cGameNounManager constructor
  -> noun-manager virtual initialization
  -> noun-manager registration append
  -> cStarManager allocation
  -> cStarManager constructor
  -> star-manager virtual initialization
  -> star-manager registration append
  -> later alternate star-root read
```

The noun-manager construction and initialization occur before star-manager construction in the same `0x00b60d80` linear body. The star-root accessor is read only after the star-manager initialization sequence. This proves construction/initialization order, not global-root publication: the direct publication writes for the noun and star root words remain unresolved.

The proven consumer/materialization order is separate:

```text
SpacePlayerData empire ID/cache
  -> cStarManager empire-map lower-bound lookup
  -> AddRef/store/release cache replacement
  -> cGameNounManager GetData
  -> lower-bound noun-vector lookup/materialization
  -> filter/add dispatch
  -> consumer scan, for example political-ID matching
```

The lookup contracts are successor-tolerant lower bounds, not exact finds. The noun and star caches have independent owners and independent invalidation paths. No proven single chain joins noun-record invalidation, star-map erase, global-root unpublication, and consumer-cache teardown.

## Evidence rules and notation

- `PROVEN` means a direct instruction, decompilation body, vtable/data entry, or corroborated call path establishes the local order.
- `SUPPORTED` means multiple static surfaces agree, but the complete runtime or owner relation is not closed.
- `HYPOTHESIS` means a sequencing model consistent with the evidence but not directly proven.
- `UNRESOLVED` means the inspected static surface does not establish the relation.
- `→` denotes a direct call, direct data dependency, or direct local field operation; it is not a transitive caller-graph inference.
- SDK declarations are used for layout and interface contracts only. A stale SDK address is not merged with a different current binary body.

## 1. Application bootstrap and manager initialization entry

### 1.1 App bootstrap order

The only positive original-process order in the corpus is the bounded main-menu path:

```text
entry
  -> App::cAppSystem::InitPlugins
  -> App::cAppSystem::Init
  -> App::cAppSystem::Startup
  -> repeated App::IAppSystem::Get
```

Evidence:

- The committed startup record labels `InitPlugins` at `0x007e93d0`, `Init` at the probe address `0x007e8ba0`, and `Startup` at `0x007e67a0`: `knowledgegraph/research/state-machines/app-lifecycle.json:146-218`.
- The live table around `0x01413aec` contains the corresponding callback addresses. `0x007e93d0` is the `InitPlugins` entry, `0x007e8ba0` is the probed `Init` entry, and `0x007e67a0` is the `Startup` entry. The exact `Init` function boundary is not recovered by Ghidra, so its internal order is not claimed.
- `FUN_007e93d0` decompiles to command-line string traversal and helper calls; it does not expose a complete plugin registry order: `knowledgegraph/research/state-machines/app-lifecycle.json:191-218`.
- `FUN_007e67a0` directly allocates and replaces application services, loads configuration, initializes graphics, and calls renderer/service virtuals. Its decompilation is available at Ghidra `0x007e67a0`; it does not directly call `0x00b60d80`.

The positive trace is startup-only. It does not establish a gameplay-mode or persistence order. The current `docs/analysis/future-research/02-pkg-02-app-lifecycle.md:7-39` explicitly leaves the broader boot/shutdown experiment runtime-blocked.

### 1.2 Direct static manager-initialization entry

`0x00b60d80` is a large simulator/service initialization body. Its direct xrefs are:

- `0x00b634d1`, inside the data-referenced `0x00b634d0` entry.
- `0x00b6364d`, inside the data-referenced `0x00b63510` mode-listener entry.

The `0x01462830` data reference points to `0x00b634d0`; the `0x0146281c` data reference points to `0x00b63510`. The mode-listener body handles the mode-exit message ID `0x0212d3e7`; when the forwarded mode IDs differ and its owner flag is clear, it calls `0x00b60d80` at `0x00b6364d`. The exact owner/event provenance of the data-referenced entry is not fully identified, so this is a static call path, not a complete event chronology.

`0x00b60d80` begins with a one-shot guard: if `receiver+0x0d` is nonzero, it returns immediately; otherwise it sets that byte before continuing. This proves a per-owner initialization gate, not whether the owner is the application, a simulator service, or a mode-specific object. The direct call sites and gate are visible in the live decompilation of `0x00b60d80`.

## 2. Noun-manager and star-manager construction order

### 2.1 Noun-manager construction

Within `0x00b60d80`, the relevant linear addresses are:

1. `0x00b61bd8`: allocate `0x11c` bytes.
2. `0x00b61beb`: call `0x00b232b0`, the noun-manager-shaped constructor.
3. `0x00b61bf4`–`0x00b61bff`: read the object’s secondary vtable and call slot `+0x08`.
4. `0x00b61c00`–`0x00b61c52`: append the initialized object to the registration container.

The constructor at `0x00b232b0` is mechanically identified as the noun-manager family by its `0x11c` allocation, the SDK noun-manager layout, and its field initialization:

- Base strategy initialization is called first.
- The object vtable is set to the noun-manager family vtable at `0x0145ef10`; the secondary vtable is set at `0x0145eec0`.
- The constructor initializes the intrusive noun list at `+0x78`, the noun map at `+0x98`, and the object list at `+0x10c`, matching the SDK layout: `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/SubSystem/GameNounManager.h:129-152`.
- The fields at `+0x54` and nearby avatar/player slots are initialized to null.
- The linked object-size assertion is `ASSERT_SIZE(cGameNounManager, 0x11C)`: SDK `GameNounManager.h:151-152`.

The virtual slot `+0x08` resolves through the secondary vtable to `0x00b25e80`. Its direct body performs noun-family initialization:

1. `0x00b25cd0` initializes type/message registration state and registers several noun types.
2. `0x00b215a0` performs noun/owner relationship setup using the manager receiver.
3. `0x00b25e80` writes listener fields and registers three handlers through the message manager.

The body has no direct reference to either noun-root global (`DAT_0167eae0` or `DAT_0167eb60`). Therefore, constructor plus virtual initialization is proven; noun-root publication is not.

### 2.2 Star-manager construction

The star-manager sequence is later in the same `0x00b60d80` linear body:

1. `0x00b61ce0`–`0x00b61cee`: allocate `0x22c` bytes.
2. `0x00b61cfc`: call `0x00bae490`, the star-manager constructor.
3. `0x00b61d05`–`0x00b61d0f`: invoke the object’s virtual slot `+0x08`.
4. `0x00b61d11`–`0x00b61d62`: append the initialized object to the registration container.

`0x00bae490` initializes the star-manager base strategy, star-record/planet vectors and maps, `mNextPoliticalID+0x1d4`, the empire map beginning at `+0x150`, and `mpRelationshipManager+0x204` to null. The layout and `0x22c` size agree with SDK `StarManager.h:129-331`.

The virtual `+0x08` entry is `0x00bb6a30`. Its live body creates and initializes the relationship manager, replaces `manager+0x204` with the new intrusive reference, releases the old non-null value, and then installs star-manager listener/configuration state. The `+0x204` ownership and initialization/shutdown contract are also recorded in `knowledgegraph/research/architecture-resolution/track-02-star.md:82-91,174-182`.

The star manager is therefore constructed and initialized after the noun manager within the same owner body. This is a direct instruction order, not an ordering inferred from the names `cGameNounManager` and `cStarManager`.

### 2.3 Post-construction star-root read

After the manager construction/registration region, `0x00b60d80` reaches:

```text
0x00b634ab: call 0x00b3d2a0
0x00b634b0: move returned pointer to ECX
0x00b634b2: call 0x00c2e4e0
```

`0x00b3d2a0` is a raw load of `DAT_0167eae4`; `0x00c2e4e0` is an empty/no-op body in the live decompilation. This proves that an alternate star-root read occurs after the star-manager construction region. It does not prove that the returned pointer is the object just constructed, because no direct writer for the root was found.

The noun and star root words are physically distinct. The complete bounded scans recovered direct readers but no direct writer, equality operation, or concrete target store:

- Noun alternate: `0x00b3d300`.
- Noun canonical: `0x00b3d400`.
- Star alternate: `0x00b3d2a0`, with `0x00b3d2c0` as a state-selected relationship bridge.
- Star canonical: `0x00b3d3a0`.

Evidence: `knowledgegraph/research/architecture-resolution/followup-03-root-publication.md:15-33,67-82,107-117`.

**Proven:** noun construction/init → star construction/init → alternate star-root read.  
**Unresolved:** the point at which either root becomes non-null, whether the noun and star roots are value-equal, and whether the two roots are phase-rebound or independently published.

## 3. Noun lookup, materialization, and invalidation

### 3.1 `0x00b21340` GetData/materialization order

The current implementation body at `0x00b21340` has this local order:

1. Read the receiver’s noun map at `+0x98` and call `0x00e5c780` for an unsigned lower-bound search using the requested noun ID.
2. If the iterator is the end sentinel, invoke the create callback, then invoke `0x00ba8420` to insert the key/value pair.
3. Otherwise, load the map payload at node `+0x14`; no exact-key equality comparison follows.
4. If the returned vector’s update marker is nonzero, invoke the clear callback.
5. Walk the receiver’s noun list at `+0x78`; invoke the filter callback `(object, nounID)`, and invoke the add callback for matches.
6. Clear the returned vector’s update marker and return the raw vector pointer.

This is the strongest direct noun lookup/materialization chain. The current binary body is `0x00b21340`; the SDK-associated `0x00b212d0` is a separate/boundary-contaminated entry and is not merged with the live body. Evidence: `knowledgegraph/research/architecture-resolution/track-01-noun.md:57-68`; `knowledgegraph/research/conflicts/track-a-type-signature.json:667-689`.

The map is therefore a noun-ID lower-bound plus materialization cache, not a proven exact-find map. A missing noun ID can produce a greater successor vector. The materialization path and the refresh path are conditional on the update marker and callbacks.

### 3.2 Noun record erase and owner clearing

`0x00b21410` is the bounded noun-record/map eraser:

1. Ask the object for its ID through virtual slot `+0x4c`.
2. Search the noun map with `0x00e5c780`.
3. If a node is found and its payload is the same object, call `0x01045590` to unlink, release the payload, and free the node.
4. If the object matches the manager’s `+0x70` owner slot, clear that slot and release the old owner.

This is record-level invalidation. It does not write either noun-root global. The direct erase body and its callers are recorded in `knowledgegraph/research/architecture-resolution/track-01-noun.md:70-78` and the live Ghidra decompilation of `0x00b21410`.

### 3.3 Noun cleanup/materialization pass

`0x00b25fe0` is a noun-family cleanup pass. Its direct order includes:

1. `0x00b22960`.
2. Cleanup calls for several noun IDs, including `0x18eb45e`, `0x2c9cc91`, `0x2e96892`, `0x1be418e`, and other IDs.
3. Clear/release the manager’s `+0x58` field.
4. Materialize a selected noun vector through `0x00b21340`.
5. Iterate and release the resulting object collection.
6. Run additional noun cleanup and release loops.

It is a noun/map/object cleanup boundary, not proof of noun-root publication or unpublication. Its direct callers include mode/simulator cleanup paths; the report does not infer a single owner teardown order from fan-in.

## 4. Star lookup, current-empire cache, and consumer use

### 4.1 Star empire lookup

`0x00ba9370` is the star-manager empire lookup wrapper:

```text
if request == UINT32_MAX: return null
node = lower_bound(mEmpires at receiver+0x150, request)
if node == end: return null
return node payload at node+0x14
```

`0x00e5c780` returns the first unsigned key not less than the request. `0x00ba9370` checks only the end sentinel; it does not compare the returned key to the request. The result is borrowed and no reference operation occurs in the wrapper.

Therefore:

- Exact key: returns the matching empire.
- Missing key with a greater key: returns the greater successor.
- Missing key with no greater key: returns null.
- Null manager receiver: no null guard is visible; the wrapper is unsafe if the manager root is null.

The direct mechanics are recorded in `knowledgegraph/research/architecture-resolution/track-02-star.md:105-123` and verified by the live decompilation of `0x00ba9370` and `0x00e5c780`.

### 4.2 Current-player cache order

`0x01021300` is the `SpacePlayerData+0x18/+0x1c` current-player cache. Its exact local order is:

1. Read requested empire ID at `SpacePlayerData+0x18`.
2. If the request is `UINT32_MAX`, return null without changing the old cache.
3. If the cached pointer is non-null and its `cEmpire+0x84` equals the request, return the borrowed hit.
4. On miss or identity mismatch, read the alternate star manager through `0x00b3d2a0`.
5. Call `0x00ba9370` with the requested political ID.
6. If the result is non-null and differs from the old pointer, AddRef the new object.
7. Store the new pointer in `SpacePlayerData+0x1c`.
8. Release the old non-null pointer after the store.
9. Return the new pointer.

The live body and the committed cache contract agree on this order: `knowledgegraph/research/architecture-resolution/track-02-star.md:125-170`.

The cache is identity-validating but not membership- or generation-validating. A lower-bound successor can be cached and returned even when its political ID differs from the request. A cached empire erased from the star map can remain alive because the cache owns a reference; the cache can continue to hit on the unchanged ID.

### 4.3 Noun/star consumer bridge

The most direct noun/star consumer chain is:

```text
0x00b25fb0
  -> 0x01021300
  -> 0x00b3d2a0
  -> 0x00ba9370
  -> cached cEmpire
  -> 0x00b25f40
  -> 0x00b21340(kCivilization)
  -> vector scan by cGameData::GetPoliticalID
```

`0x00b25fb0` first calls `0x01021300`. If the current empire is null, it returns the caller-supplied fallback word unchanged. If the current empire is non-null, it reads `cEmpire+0x84` and calls `0x00b25f40`.

`0x00b25f40` calls `0x00b21340` with the civilization noun ID, then scans the returned vector and returns the first `cGameData` whose political ID matches. The return is a borrowed pointer into the noun-manager-owned vector.

This chain is a proven local consumer path, but it does not prove that the noun manager and star manager are the same object. Their root slots are physically distinct and their publication/value equality remains unresolved. Evidence: `knowledgegraph/research/root-closure/cross-root-relationships.md:96-108,178-210`.

## 5. Mode enter/exit ordering

### 5.1 App mode registry

The concrete manager vtable is at `0x01412598`. The validated indexed activation wrapper is `0x007d8c80`; it range-checks the requested index and delegates to `0x007d85b0`. The helper’s direct order is:

```text
old IGameMode::OnExit
  -> write new active index at cGameModeManager+0x28
  -> send mode-exit message 0x0212d3e7
  -> new IGameMode::OnEnter
  -> send mode-enter message 0x022d1adc
```

This order is `CONFIRMED` for the concrete helper-local instruction/message order. Same-index requests are no-ops in the helper contract, and out-of-range requests are rejected by the wrapper. The message payload words, immediate-versus-queued timing, listener priority, and producer of the main-menu mode request remain unresolved.

Evidence:

- `knowledgegraph/research/state-machines/app-lifecycle.json:55-120`.
- `docs/analysis/event-message-map.md:46-50,84-92`.
- `docs/analysis/gameplay-transition-map.md:59-75`.
- SDK interface declarations: `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/App/IGameModeManager.h:121-195` and `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/App/IGameMode.h:31-76`.

There is an address contradiction that must not be hidden. The SDK-labeled `0x007d8d40` body in the current binary is a teardown-shaped body: it rewrites base vtables, tears down temporary/manager state, and calls `0x007d8cc0`; it is not the concrete activation body. The activation path is `0x007d8c80 -> 0x007d85b0`. The same contradiction is recorded in `docs/analysis/event-message-map.md:122-126` and `knowledgegraph/research/state-machines/app-lifecycle.json:79-99`.

### 5.2 Simulator mode-announcement consumer

`0x00b63510` is data-referenced as a simulator mode listener. It handles the exit/enter announcement IDs, reads payload words at `+0x08/+0x10`, normalizes them, and selects the last/current strategy commit behavior. It is a separate consumer of App mode announcements, not proof that App’s active index and Simulator’s `cStrategy` mode fields are the same state.

The ordering relationship is:

```text
App helper writes active index
  -> sends exit announcement
  -> sends enter announcement after new OnEnter
  -> listener may commit Simulator strategy mode state
```

The listener’s queue timing and the exact runtime value of each mode ID are unresolved. The listener also contains the conditional `0x00b60d80` initialization path for an owner whose flag is clear; that call is not a proven consequence of every mode transition.

## 6. Scenario mode ordering and reset

### 6.1 Scenario construction, entry, and teardown

The current scenario object has a direct ctor at `0x00ef02f0`:

1. Install the scenario-mode vtables.
2. Initialize its fields to null/zero, with the mode field initially set to `0`.
3. Publish the object through `App__sScenarioMode`.
4. Return the object.

The direct destructor at `0x00ef0400`:

1. Restores base vtables.
2. Clears `App__sScenarioMode`.
3. Releases scenario fields in a direct sequence.
4. Restores base state.

The SDK layout places `cScenarioMode::mMode` at `+0xcc` and defines `UnkMode=0`, `EditMode=1`, `PlayMode=2`: `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/App/ScenarioMode.h:41-55,68-101`.

The scenario primary vtable at `0x0148b058` places the SDK `IGameMode` entry/leave slots at `+0x18/+0x1c`; the corresponding current bodies are `0x00ef25a0` and `0x00ef1660` in the inspected vtable data. `0x00ef25a0` performs setup through space-trading, properties, timing, and scenario helpers, then calls `0x00ef1ca0`. `0x00ef1660` is not recovered as a Ghidra function boundary, but its disassembly is direct and branch-complete:

```text
read scenario mMode at +0xcc
  -> if EditMode (1): call 0x00ef0c80
  -> if PlayMode (2): call 0x00ef10c0
  -> call the common message/dispatcher virtual at +0x98
```

`0x00ef0c80` is the edit-side cleanup path. It calls display/input/scene cleanup helpers, `0x00f039a0(0)`, and decrements the owning manager counter at `+0x110`.

`0x00ef10c0` is the play-side cleanup path. It explicitly calls `Simulator::cGameNounManager::Get()` and then `0x00e180d0`, followed by additional simulator/resource/avatar cleanup. This is a direct scenario-play teardown → noun-family cleanup edge. It is not a global noun-root unpublication path.

### 6.2 Scenario internal Edit/Play switch

`0x00ef12d0` is the direct scenario mode switch body. Its ordering is exact:

```text
current EditMode (1) -> requested PlayMode (2)
  1. call 0x00ef0c80
  2. write scenario mMode = 2
  3. call 0x00f45fd0(2, 0, 0)
  4. call 0x00ef0ee0

current PlayMode (2) -> requested EditMode (1)
  1. call 0x00ef10c0
  2. write scenario mMode = 1
  3. call 0x00f45fd0(1, 0, 0)
  4. call 0x00ef0a70(0)

otherwise
  write scenario mMode = requested value
```

This is a proven local scenario reset/switch order. It is separate from the App `SetActiveModeAt` helper and from `SpaceContext`. The live `0x00ef10c0` body’s noun-manager call is the strongest direct evidence that scenario play teardown can invalidate or clean noun-owned state before the new scenario mode entry.

The helper at `0x00ef1ca0`, called by scenario OnEnter, clears local scenario state words, invokes `0x00ef1c40`, copies/updates scenario collection state, releases several vectors, and clears auxiliary scenario state. It is a reset-like entry helper by mechanics; no `ResetScenario` name is promoted because no such direct symbol/body was found.

### 6.3 Reset-like simulator paths

`0x00b32b20` and `0x00b32ce0` share a direct reset tail:

```text
0x01022460
  -> 0x01021960(-1)
  -> 0x010219b0(0, 0)
  -> additional simulator/service reset calls
```

`0x00b33350` also calls `0x01022460`, conditionally calls `0x01021960(-1)` and `0x010219b0(0,0)` for the relevant mode-ID range, then invokes star-manager state setup through `0x00b3d2a0` and a manager virtual at `+0x50`.

These bodies are reset-like transitions, not proof of a single named `ResetScenario` operation. Their direct ordering is stronger than any historical name-based ordering.

## 7. World/planet transitions and runtime materialization

### 7.1 `SpacePlayerData` lifetime

`0x01021d40` is the direct `SpacePlayerData` allocator/initializer:

1. Allocate `0x34` bytes.
2. Clear active planet `+0x04`, active star `+0x08`, relationship manager `+0x0c`, current empire cache `+0x1c`, and colony vector words.
3. Set `mCurrentContext+0x10` to `None (-1)`.
4. Set `mPlayerEmpireID+0x18` to `UINT32_MAX`.
5. Set `mfRotationRateFactor+0x14` to `1.0`.
6. Publish the allocation in `Simulator::sSpacePlayerData`.

The live body does not release an old global object or free the whole object. Whole-object teardown and final global clearing remain unresolved.

`0x01022460` is the direct field teardown path:

1. Clear the one-shot activation flags.
2. Clear/release active planet `+0x04`.
3. Clear/release active star `+0x08`.
4. Clear/release the relationship manager `+0x0c`.
5. Clear/release current empire cache `+0x1c`.
6. Release the colony vector.
7. Reset `mPlayerEmpireID+0x18` to `UINT32_MAX`.

It does not write `mCurrentContext+0x10` and does not clear the global `sSpacePlayerData` pointer. The complete field contract and whole-object limitation are in `knowledgegraph/research/root-closure/followup-space-lifecycle.md:64-91,117-128,180-191`.

### 7.2 Context writer and active binding

`0x01021960` is a conditional `mCurrentContext` writer:

1. Read `SpacePlayerData+0x10`.
2. If unchanged, do nothing.
3. If changed, store the requested context.
4. If the new value is `2` (`Galaxy`) and active star `+0x08` plus `0x00ffbe50()` are non-null, call `0x00c8b360` and then `0x01001360`.

The context write precedes the Galaxy-only follow-up. The setter does not write the active planet or star.

`0x010219b0` is the active star/planet binding path:

1. Derive the active star through `0x00b3d2a0` and `0x00bb3750`.
2. Replace `SpacePlayerData+0x08` with the new star using AddRef/store/Release.
3. If a secondary object is present and is not the same player object, derive the planet through `0x00b3d2a0` and `0x00bb59b0`.
4. Replace `SpacePlayerData+0x04` using AddRef/store/Release.
5. If no secondary object is supplied, clear/release the planet slot.

`0x010221f0` is a second active-reference replacement path. It creates/initializes an auxiliary object, conditionally clears the active planet, obtains the active star through `0x00b3d2a0` and `0x00bb6700`, obtains an empire through `0x00bb1340`, writes the player empire ID, replaces the active star and planet, and performs additional mode/space initialization. It is not safe to reduce this body to the two-field `0x010219b0` contract.

`0x01022580` is a one-shot first-activation path:

1. If the one-shot flag is clear, set it.
2. If active star is null, obtain an ID through the alternate star manager and call `0x00bb9950`, then call `0x010221f0`.
3. If current context is non-zero, write `0` directly.

It is a direct context-normalization/active-star initialization path, not a proven generic mode transition.

### 7.3 Concrete context callers

The direct context writer has the following call paths:

| Caller | Requested context | Direct local order/condition |
|---|---:|---|
| `0x00b32b20` | `-1` | `0x01022460` first, then `0x01021960(-1)`, then `0x010219b0(0,0)`. |
| `0x00b32ce0` | `-1` | Same reset tail. |
| `0x00b33350` | `-1` conditionally | `0x01022460`; then context reset and active-reference clear only for the relevant mode-ID range. |
| `0x00fda9f0` | `-1` after non-None context work | Context-specific work first, then `0x01021960(-1)`, then `0x010219b0(0,0)`. |
| `0x00fdf5f0` | `0` | Planet-context setup, including `0x01021960(0)`. |
| `0x01003490` | `2` | Galaxy setup, including `0x01021960(2)`. |
| `0x01003690` | `0` | Planet setup, including `0x01021960(0)`. |
| `0x01003a50` | `1` | Solar-system setup, including `0x01021960(1)`. |
| `0x0100a960` | `-1` | Larger teardown body, including `0x01021960(-1)`. |

These are direct calls and arguments. Actual context stores remain conditional in `0x01021960` when the old value already equals the request.

### 7.4 World-transition branches

`0x00fda9f0` gives the clearest direct world/planet transition order:

```text
if parent+0x15c is non-null:
  current context 0:
    call 0x00f010a960
  current context 1:
    call 0x00f01009470(0, 0, 1)
    call 0x00f010039c0(...)
  current context 2:
    call 0x00f01009470(0, 0, 1)
    call 0x00f01003620()
  current context None:
    skip the common reset
for non-None current contexts:
  0x01021960(-1)
  0x010219b0(0, 0)
```

The function therefore performs context-specific world work before setting `None` and clearing active star/planet references. This is a direct ordering, not a semantic projection from the mode registry.

The three high-information setup bodies have the following direct context writes:

- `0x01003690` (Planet): reads active planet, performs star-manager lookup work, then calls `0x01021960(0)` before the later world/graphics/persistence-related setup. It later obtains the solar-system object through `0x00c8b770` and calls `0x00c86c70(1)`.
- `0x01003a50` (SolarSystem): disposes/rebuilds model worlds, then calls `0x01021960(1)` before `0x00c8b770`/`0x00c86c70` and later lighting/strategy calls.
- `0x01003490` (Galaxy): performs the Galaxy setup path and calls `0x01021960(2)` before later space/lighting calls.

The exact semantic names of all helper calls are retained as opaque where the current body does not prove them. These functions are direct consumers of `SpaceContext`, not proof that `SpaceContext` equals App mode, `cScenarioMode::mMode`, or input mode.

### 7.5 Persistent record generation → runtime materialization → graphics

These are separate transitions and must not be collapsed:

1. **Planet-record generation:** `0x00bb4af0` checks `cStarRecord+0xac == 0` and a timing condition from `0x00c8b520`. If both pass, it records minutes at `cStarRecord+0x0c`, searches the pending list, removes the star, resets manager state through `0x00bb3800`/`0x00bb9ad0`/`0x00bb9b00`/`0x00bba500`, then calls `0x00bb4100`.
2. **Planet-record creation:** `0x00bb4100` derives planet parameters, creates a planet record through `0x00ba61b0`, initializes its fields through `0x00ba64a0`, and increments `cStarRecord+0x0ac` for each created record. The live body also performs filtering/position/score logic. The SDK states that generation changes the count and does not necessarily append every planet to the star’s record vector: `StarManager.h:245-259`.
3. **Record-to-runtime boundary:** `0x00bb5b50` is the SDK-confirmed `RecordToPlanet` boundary. Its live body delegates to `0x00bb1560`; that helper first checks the existing runtime-planet cache with `0x00ba95f0` and falls back to `0x00baf820` when no matching runtime object is found. Exact representation/allocation ownership is not fully recovered.
4. **Solar-system materialization:** `0x00c8b700` lazily allocates a `0x54`-byte `cSolarSystem` at owner `+0x40`, replaces the old pointer, and calls `0x00c86760`. `0x00c86760` stores the owner at `+0x0c`, creates/updates celestial bodies, iterates the planet-record collection, and appends planet runtime pointers with intrusive reference operations.
5. **Graphics generation:** `0x00c86e00` is a separate `GenerateGraphics` body. It calls each body’s virtual `+0x16c` operation and then iterates the planet collection through `0x00c719d0`. Its call relationship to `0x00c86760` is not a proven single synchronous chain in the inspected body.

The runtime timing/lifetime conditions are therefore:

```text
no cached runtime planet
  -> record lookup/fallback materialization
  -> append/AddRef runtime planet
  -> later graphics generation
```

The report does not claim that persistence restore performs this sequence, because the concrete `LoadGame` body and restore callbacks were not recovered.

## 8. Persistence and restore boundaries

### 8.1 Service contract

`0x00b3d440` is a direct raw getter:

```text
return DAT_0167eb34
```

The SDK declares `LoadGame(const GameLoadParameters&)` at vtable slot `+0x10`, and requires the player noun to exist before loading: `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/SubSystem/GamePersistenceManager.h:33-46`.

The current corpus has no recovered concrete `LoadGame` body. The service getter, SDK vtable declaration, and parameter layout do not establish the restore order, file transaction, strategy iteration order, or post-load callbacks. The KG explicitly retains this as `SDK-name-only`/`UNRESOLVED`: `docs/analysis/event-message-map.md:84-92,148-152`; `docs/analysis/serialization-model.md:253-299`.

### 8.2 Star database checkpoint

`0x00bb4ba0` is a direct star-database checkpoint body. Its proven local order is:

1. Return unless the manager’s checkpoint flag at `+0x21c` is set.
2. Run star/planet preparation helpers.
3. Resolve the current empire through `0x01021300`.
4. Update the current scenario-star timestamp/version fields and remove the current star from a pending list when applicable.
5. Open/create `stars.db.tmp`.
6. Serialize star/planet/class data through the serializer callbacks.
7. Close the temporary stream/context.
8. Replace `stars.db.tmp` with `stars.db`.

The body contains a direct `FUN_00b3d2a0`/`FUN_01021300` chain and a direct serializer write path. It proves a star-database checkpoint after live manager state exists; it does not prove the inverse restore path.

`0x00b28ec0` is a coarse serialization/profile orchestration candidate. It builds temporary paths, calls serializer/database helpers, and conditionally calls `0x00bb4ba0` or another star-related path. It is not proven to be `cGamePersistenceManager::LoadGame`.

`0x00b294c0` is a profile/load orchestration candidate. It probes profile data through `0x00b282e0`, conditionally materializes a Civilization noun vector through `0x00b21340`, changes star-manager setup state, and calls `0x00b28ec0`. The Civilization materialization is conditional and is not proof that a game load restores all noun types or star records.

### 8.3 Restore sequence status

The following are **hypotheses, not proven order**:

```text
LoadGame request
  -> persistence manager availability
  -> saved header/parameter consumption
  -> class/object record restore
  -> noun-manager rehydration/materialization
  -> star-record restore
  -> active planet/star rebinding
  -> runtime solar-system/graphics materialization
```

The only directly proven pieces are the existence of the persistence vtable contract, serializer callbacks, `stars.db` checkpoint mechanics, and separate noun/star materialization functions. No direct path from the concrete `LoadGame` target to `0x00b21340`, `0x00ba9370`, `0x00bb5b50`, or `0x00c8b700` was recovered.

`cSavedGameHeader` contains a mode field and current-planet key, while `GameLoadParameters` contains game/star names, creature/species data, star ID, difficulty, and mode. These are authoritative layout contracts, not evidence of field-consumption order: `docs/analysis/serialization-model.md:253-268`.

## 9. Cache and invalidation ordering

### 9.1 Noun map cache

`0x00b21340` owns the noun-map materialization/refresh sequence. On a refresh it clears the vector before filtering and adding, then clears the update marker. `0x00b21410` invalidates a matching map node and releases the payload. `0x00b25fe0` performs broader noun cleanup. None of these inspected paths writes the noun-root global or unpublishes the noun manager.

### 9.2 Star empire map and player cache

The star map owns intrusive references to `cEmpire` objects. `0x00bad7a0` erases the lower-bound-selected node and releases its payload, but it does not clear `SpacePlayerData+0x1c`. The player cache is an independent owner and is cleared only by `0x01022460` in the recovered field-teardown path.

The direct contradiction is:

```text
star map erase
  -> releases map reference
  -> does not clear player cache

player cache teardown
  -> clears/releases cache reference
  -> does not erase map node
```

A cached empire can therefore remain allocated after map erase. It can continue to hit on political-ID equality even though it is no longer a current map member.

### 9.3 Manager and root teardown

`0x00bb7250` is the recovered star-manager shutdown path. Its direct order includes:

1. Star/map setup cleanup.
2. Clear/release property-list fields at `+0x1a0/+0x1a4`.
3. Repeated unpause/cleanup virtual calls.
4. Clear the manager listener at `+0xb4`.
5. Clear/release `SpacePlayerData+0x08` active star if present.
6. Shrink/release star-record vector regions.
7. Invoke relationship-manager teardown through `+0x204`, then clear/release that field.
8. Recursively clear manager-owned maps through `0x00d0c930`.
9. Clear additional manager globals/loops.

The star-manager destructor path through `0x00babe70` releases the manager-owned relationship field, star/planet record collections, and map payloads. It does not write `DAT_0167eae4` or `DAT_0167eb0c`.

The noun cleanup path `0x00b25fe0` and noun record erase path `0x00b21410` likewise do not write noun-root globals. `App::cGameSystem` application teardown at `0x00f47700` releases application service pointers and shutdown callbacks, but the direct body does not establish a single global order for noun, star, player cache, and root unpublication.

The app stop message path at `0x00f47b10` writes the stop result and clears the application initialized byte at `param_1+0x0d`. The teardown body at `0x00f47700` clears the app state, invokes `AppShutdown`, pauses services, releases service pointers, and tears down configuration/job services. The `PreShutdown` body at `0x00c7e6470` is also interface-oriented and emits the same numeric mode-exit ID in a shutdown context. The relative order of `cGameModeManager::Dispose`, star/noun manager teardown, player-cache teardown, and any hidden root unpublication is unresolved.

## 10. Proven order versus sequence hypotheses

| Boundary | Status | Exact conclusion |
|---|---|---|
| App startup | **PROVEN for bounded main-menu trace** | `InitPlugins -> Init -> Startup`; internal `Init` and full service order unresolved. |
| Noun constructor before star constructor | **PROVEN** | `0x00b232b0` call at `0x00b61beb` precedes `0x00bae490` at `0x00b61cfc`. |
| Noun initialization before star initialization | **PROVEN** | Noun slot `+0x08` call at `0x00b61bff` precedes star slot `+0x08` call at `0x00b61d0f`. |
| Service registration append after each virtual initialization | **PROVEN locally** | The linear registration body appends each initialized object after its slot call. |
| Alternate star-root read after construction region | **PROVEN** | `0x00b3d2a0` is called at `0x00b634ab`. |
| Root publication before the read | **UNRESOLVED** | No direct writer for noun/star root words was found; the read may be null or depend on opaque/runtime publication. |
| Noun GetData materialization | **PROVEN locally** | Lower-bound → create/insert on end → clear/filter/add on update → clear marker. |
| Noun exact lookup | **REJECTED** | The body does not compare the returned map key to the requested noun ID. |
| Star empire exact lookup | **REJECTED** | `0x00ba9370` returns a lower-bound successor when the exact key is absent. |
| Player cache replacement | **PROVEN locally** | AddRef new, store, Release old; no membership/generation validation. |
| Star map erase invalidates player cache | **REJECTED** | Erase path does not write `SpacePlayerData+0x1c`. |
| Noun record erase invalidates noun root | **REJECTED for inspected path** | Erase path has no noun-root global write. |
| App mode transition order | **PROVEN for concrete helper** | `0x007d85b0`: old `OnExit` → active index → exit message → new `OnEnter` → enter message. |
| SDK-labeled `0x007d8d40` as activation body | **REJECTED** | Current body is teardown-shaped; concrete activation is `0x007d8c80 -> 0x007d85b0`. |
| Scenario Edit↔Play switch order | **PROVEN locally** | `0x00ef12d0` performs old-side cleanup, writes `mMode`, calls `0x00f45fd0`, then new-side entry. |
| Scenario play teardown reaches noun cleanup | **PROVEN locally** | `0x00ef10c0` calls `cGameNounManager::Get` and `0x00e180d0`. |
| `SpaceContext` equals App/scenario/input mode | **REJECTED** | Separate owners/fields/enums; numeric overlap is coincidental. |
| No-planet star regeneration order | **PROVEN locally** | Guard → timestamp → pending erase → manager reset → `0x00bb4100` generation. |
| Persistent record → runtime planet → graphics is one call chain | **UNSUPPORTED** | `0x00bb4af0`, `0x00bb4100`, `0x00bb5b50`, `0x00c8b700`, and `0x00c86e00` are separate boundaries. |
| `LoadGame` restores noun then star then materializes planets | **HYPOTHESIS only** | Concrete `LoadGame` body and restore callback order are not recovered. |
| Manager, cache, and global-root teardown have one total order | **UNRESOLVED** | Owner-local cleanup is proven; relative global and cache teardown is not. |

## 11. Timing, lifetime, and contradiction notes

1. **One-shot gates:** `0x00b60d80` checks owner `+0x0d`; `0x01022580` checks a separate activation byte; `0x00bb4ba0` checks manager checkpoint flag `+0x21c`. These gates make later calls no-ops or changes conditional; they are not global lifecycle barriers.
2. **Same-value suppression:** `0x01021960` suppresses context writes and the Galaxy follow-up when the requested value equals the old value.
3. **Raw manager pointers:** `0x00b3d2a0` and `0x00b3d3a0` are raw borrowed loads. They do not AddRef, validate, lock, or establish ownership. A pointer obtained from them must not survive owner teardown without a separate guarantee.
4. **Noun map ownership:** `0x00b21340` returns a manager-owned vector pointer. `0x00b25f40` returns a borrowed `cGameData*` from that vector. Consumer lifetime depends on the noun manager/vector owner.
5. **Empire cache lifetime:** `SpacePlayerData+0x1c` owns one intrusive empire reference. Map erase releases only the map reference, so stale membership can remain alive through the cache.
6. **Relationship lifetime:** `cStarManager+0x204` is manager-owned. `0x00bb6a30` replaces it, `0x00bb7250` tears it down and clears it, and `0x00babe70` releases it through the manager destructor path. The separate canonical relationship global `DAT_0167eb14` has no proven equality relation.
7. **Physical versus value aliasing:** noun roots and star roots are physically distinct, but runtime value equality is unresolved. Separate root words cannot be merged merely because SDK names use singleton terminology.
8. **Lookup identity:** noun and star ordered-map paths are lower bounds. Any report or implementation that calls them exact-find is contradicted by direct control flow.
9. **Mode-state axes:** App active index, Simulator `cStrategy` last/current mode, `SpaceContext`, `cScenarioMode::mMode`, and input/game-mode fields are separate state owners. The App helper order is proven; the handoff timing and mode-ID semantics are not.
10. **Persistence:** `cGamePersistenceManager::Get` proves service access, not restore order. `stars.db` replacement proves a narrow checkpoint, not whole-save atomicity or restore. No `SaveGame` body or complete `.spo` transaction is established.
11. **No runtime evidence:** the positive original-process trace reaches only bounded application startup/service access. There is no positive original trace for empire, noun, scenario, world/planet, persistence restore, or teardown ordering. All lifecycle claims above are static unless explicitly marked runtime/observed from the existing startup record.

## Primary references

### Ghidra live anchors

- App startup/data: `0x007e67a0`, `0x007e8ba0`, `0x007e93d0`, vtable data around `0x01413aec`.
- Service initialization: `0x00b60d80`, `0x00b634d0`, `0x00b63510`.
- Noun manager: `0x00b232b0`, `0x00b25e80`, `0x00b21340`, `0x00b21410`, `0x00b25fe0`, roots `0x0167eae0` and `0x0167eb60`, accessors `0x00b3d300` and `0x00b3d400`.
- Star manager: `0x00bae490`, `0x00bb6a30`, `0x00bb7250`, `0x00babe70`, `0x00ba9370`, `0x00bad7a0`, roots `0x0167eae4` and `0x0167eb0c`, accessors `0x00b3d2a0` and `0x00b3d3a0`.
- Cache/consumer bridge: `0x01021300`, `0x00b25f40`, `0x00b25fb0`.
- Mode manager: concrete vtable `0x01412598`, wrapper `0x007d8c80`, helper `0x007d85b0`, stale/conflicting SDK body `0x007d8d40`, listener `0x00b63510`.
- Scenario mode: ctor `0x00ef02f0`, vtable data around `0x0148b058`, entry `0x00ef25a0`, exit disassembly `0x00ef1660`, internal switch `0x00ef12d0`, destructor `0x00ef0400`, play cleanup `0x00ef10c0`.
- Space/world: `0x01021d40`, `0x01022460`, `0x01021960`, `0x010219b0`, `0x010221f0`, `0x01022580`, `0x01003690`, `0x01003a50`, `0x01003490`, `0x00fda9f0`.
- Generation/materialization: `0x00bb4af0`, `0x00bb4100`, `0x00bb5b50`, `0x00bb1560`, `0x00c8b700`, `0x00c8b770`, `0x00c86760`, `0x00c86e00`.
- Persistence/teardown: `0x00b3d440`, `0x00bb4ba0`, `0x00b28ec0`, `0x00b294c0`, `0x00f47b10`, `0x00f47700`.

### Committed KG/docs

- `knowledgegraph/research/architecture-resolution/track-01-noun.md:57-88`
- `knowledgegraph/research/architecture-resolution/track-02-star.md:82-182,195-257`
- `knowledgegraph/research/architecture-resolution/followup-03-root-publication.md:15-33,67-117`
- `knowledgegraph/research/root-closure/followup-space-lifecycle.md:64-191`
- `knowledgegraph/research/root-closure/track-f-space-context.md:90-168,195-221,263-340`
- `knowledgegraph/research/root-closure/cross-root-relationships.md:73-108,178-210`
- `knowledgegraph/research/state-machines/app-lifecycle.json:55-120,146-218`
- `knowledgegraph/research/state-machines/global-events.json:170-196`
- `knowledgegraph/research/state-machines/persistence.json:1322-1398,2280-2318,2439-2513`
- `docs/analysis/event-message-map.md:46-50,82-92,122-152`
- `docs/analysis/gameplay-transition-map.md:59-81,131-151,171-189`
- `docs/analysis/serialization-model.md:253-299,365-410`
- `docs/analysis/architecture-resolution.md:94-118,120-145`
- `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/App/IGameMode.h:31-76`
- `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/App/IGameModeManager.h:121-195`
- `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/SubSystem/GameNounManager.h:36-152`
- `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/SubSystem/StarManager.h:102-331`
- `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/SubSystem/GamePersistenceManager.h:12-62`
- `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/SubSystem/cStrategy.h:30-90`
- `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/App/ScenarioMode.h:41-101`
