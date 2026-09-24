# Blocker C — Persistence reference/restore and mode-handoff graph

**Status:** `PARTIALLY_RESOLVED; CLEAN-ROOM IMPLEMENTATION MAY PROCEED, ORIGINAL-WIRE/ORIGINAL-RUNTIME PARITY REMAINS BLOCKED`
**Investigator scope:** primary Blocker C investigation
**Binary:** `SporeApp.exe` 3.1.0.22, `x86:LE:32:windows`, image base `0x00400000`
**Analysis mode:** static Ghidra/decompilation, xrefs, vtables, type layouts, local SDK/modding evidence, and prior architecture-resolution reports. No source implementation, `SPORE/` inspection, or canonical SQLite DB write was performed. No new original-process runtime trace was performed.

## 1. Executive conclusion

The smallest defensible persistence architecture is now bounded:

```text
versioned saved-game header
  -> database/stream context
    -> ClassSerializer class/attribute record
      -> object instance table and stable logical references
        -> ISimulatorSerializable object attributes
          -> PropertyList local entries and typed Property values

mode transition
  -> old mode exit
    -> active-mode publication and mode announcements
      -> new mode enter
        -> explicit persisted-DTO handoff, if requested
          -> fresh runtime object construction and deferred reference binding
```

The evidence supports a **callback/schema + stable-reference + deferred-association** model. It rejects a raw `cSavedGameHeader` block, raw host pointers, a single universal mode enum, and an assumption that Cell mode exit is an automatic save. It does not establish the exact `.spo`/database/COM outer envelope, complete attribute IDs and field coverage, cycle encoding, migration behavior, cross-file atomicity, or concrete `cGamePersistenceManager` membership for the strongest save/load candidates.

**Decision:** OpenSpore can proceed with a clean-room persistence seam using an explicit schema, logical object IDs, deferred references, a versioned header, a DTO handoff, and explicit transaction boundaries. It must not claim byte-compatible original save files, original field survival, original automatic mode save, or exact original restore order until the decisive observations below are collected.

## 2. Evidence boundary and source basis

The requested baseline documents were read first:

- `docs/analysis/semantic-blueprint.md:251-283,353-385,421-453,523-555,569-580`
- `docs/analysis/architecture-resolution.md:120-147,293-377`
- `docs/analysis/serialization-model.md:27-72,130-249,253-299,301-380,397-471,473-509`
- `docs/analysis/gameplay-state-machines.md:81-120,142-154,361-376`

Relevant prior reports were also read:

- `knowledgegraph/research/architecture-resolution/track-04-persistence.md:1-133`
- `knowledgegraph/research/architecture-resolution/track-03-mode.md:1-153`
- `knowledgegraph/research/architecture-resolution/followup-06-persistence.md:1-304`
- `knowledgegraph/research/architecture-resolution/track-05-event.md:1-156`
- `knowledgegraph/research/architecture-resolution/track-06-forwarded-state.md:1-119`
- `knowledgegraph/research/architecture-resolution/track-08-cell-lifecycle.md:1-92`
- `knowledgegraph/research/architecture-resolution/track-09-resource.md:1-127`
- `knowledgegraph/research/architecture-resolution/track-10-vtable-conditional.md:1-135`
- `knowledgegraph/research/architecture-resolution/followup-02-forwarded-state.md:1-172`
- `knowledgegraph/research/architecture-resolution/followup-04-cell-boundary.md:1-274`
- `knowledgegraph/research/root-closure/track-e-empire-chain.md:1-219`
- `knowledgegraph/research/runtime-oracle/candidate-experiments.md:356-447`
- `knowledgegraph/research/runtime-oracle/replacement-observability.md:317-328,652-682`
- `docs/analysis/future-research/03-architecture-blocker-3.md:1-55`
- `docs/analysis/architecture-decisions.md:85-112,148-170`
- `docs/analysis/event-message-map.md:46-52,76-92,122-152`
- `docs/analysis/simulator-shared-state-interface.md:203-323`

Fresh Ghidra queries targeted the open program `SporeApp.exe`. Ghidra type layouts, vtable bytes, xrefs, decompilation, and call graphs were used to separate direct binary evidence from imported SDK names. Where Ghidra did not create a function entry for an SDK-labelled address, the address is treated as a vtable/interior/raw-byte anchor rather than silently promoted to a confirmed body.

## 3. Static evidence map

### 3.1 Serializer and property surfaces

| Surface | Direct binary evidence | Type/vtable evidence | Safe claim |
|---|---|---|---|
| `PropertyList` | `App__PropertyList__Write @ 0x006A1540`; `App__PropertyList__Read @ 0x006A2F60` | Ghidra `PropertyList` size `0x38`: map at `+0x18`, parent at `+0x30`, operations at `+0x34` | Local entries and typed-property stream transfer are supported; exact wire bytes and parent encoding remain open. |
| `Property` | PropertyList map stride is `0x18`; typed value writer/reader are called at `0x00693390` / `0x00694440` | Ghidra imported `Property` is `4` bytes, while direct runtime evidence and the community SDK describe a `0x14` carrier with flags/type | A typed `Property` abstraction is required; the imported four-byte type must not become the OpenSpore wire/runtime contract. |
| `ClassSerializer` setup | `FUN_00692880`; `FUN_00692F90` wraps setup | Ghidra layout `0xA14`: 128 attribute pointers, count `+0xA00`, serialized count `+0xA04`, class ID `+0xA08`, object `+0xA0C`, attributes `+0xA10` | Callback schema and class/attribute identity are supported; concrete tables and field order remain unknown. |
| `ClassSerializer::Write` | `FUN_00692900` | Calls stream/attribute callbacks, records per-attribute success and size, then performs final framing/status operations | A callback-based binary/text attribute writer is supported. Exact stream words and failure rollback are not fully recovered. |
| `ClassSerializer::Read` | `FUN_00693E10` | Reads framing, validates class/count/attribute identity, calls `FUN_00E0E9F0`, then invokes attribute callbacks and stream status checks | Class/attribute mismatch and callback/stream failure are explicit rejection paths. |
| `Attribute` | Used by `FUN_00692880`, `FUN_00692900`, `FUN_00693E10`, `FUN_00695770` | Ghidra `Attribute` size `0x3C`, callbacks at `+0x24..+0x30`, current object at `+0x18` | Ordered, callback-backed field descriptors are supported. |
| `ISimulatorSerializable` | Interfaces are used by serializable owners and Cell/header vtables | Ghidra interface is a four-byte vtable; community SDK declares `Write`, `Read`, `WriteToXML`, `GetNounID` at `+0x10,+0x14,+0x1C,+0x20` | Eligibility and subtype-specific serialization are supported; eligibility does not prove complete field coverage. |
| Serialization database/stream | `FUN_00693D60` / `FUN_00693CD0` construct write/read contexts; `FUN_00693AA0` / `FUN_006939B0` open; `FUN_00693900` closes/releases | Community SDK declares `ISerializerDatabase`, read/write streams, object pointers, simulator pointers, properties, raw data, class objects, and version operations | Database/stream lifecycle is a required architectural boundary. Exact record envelope and class-object database layout remain open. |

### 3.2 Header and Cell serializable owners

| Owner | Direct binary evidence | Type/vtable evidence | Safe claim |
|---|---|---|---|
| `cSavedGameHeader` | `FUN_00B274E0` is the historical constructor anchor from the saved-game path; `FUN_00B268A0` calls `FUN_00692F90(&DAT_01568B08, 0x01A80D26)` then `FUN_00692900` | Ghidra `cSavedGameHeader` size `0x68`: versions `+0x0C/+0x10`, object-count map `+0x14`, timestamp `+0x30`, mode `+0x54`, snapshot `+0x58`, current planet `+0x5C`; vtable data at `0x0145FAA8` | A ClassSerializer-backed versioned header is supported; it is not a raw 0x68-byte file block. |
| `cCellSerializableData` | `FUN_00E61550` allocates `0xEC`, installs vtables, initializes fields; `FUN_00E63D10` swaps/copies a serializable object; `FUN_00E627A0` copies the value fields | Ghidra size `0xEC`; vtable data `0x01485598`, refcount table `0x014188C0`; vtable contains `0x00E51300` and `0x00E51370` at observed callback positions | This is the explicit Cell mode-state/save candidate. Named fields are not proven to be emitted merely because they exist. |
| `cGameData` | `FUN_00B21340` maps/materializes noun data; `FUN_00B25FB0` bridges current empire to a noun/civilization candidate | Ghidra `cGameData` size `0x34`; owner pointer `+0x2C`, political ID `+0x30`; `ISimulatorSerializable` vtable | A noun/game-data registry is a likely object materialization source, not proof of the serializer class-object table. |
| `cEmpire` | `0x01021300` validates/replaces the current empire cache; `0x00BA9370` performs lower-bound map lookup | Ghidra size `0x158`, political ID `+0x84`, intrusive star/ally/enemy vectors | Political ID and reference-managed object relationships are supported; exact cross-save remapping is not. |
| `cMission` | Serializable vtable and owner/target/planet fields in Ghidra layout | Ghidra size `0x1F0`; `mpOwnerEmpire`, `mpTargetEmpire`, `mpSourcePlanet`, `mpParentMission`, `mpPropList`, `mpGalaxyCommEvent` | Mission object/reference graph is structurally recoverable, but callback field coverage and restore order are not. |
| `cCommEvent` | Communication object is serializable/refcounted and can contain mission/planet/city/civilization references | Ghidra size `0xA0`; `ISimulatorSerializable` plus `IVirtual`; source/target city/civilization, mission, planet | A serializable domain event exists; it is not a universal persistence event or a universal App message. |
| `cStarRecord` | `0x00BB4BA0` writes star/planet state through ClassSerializer; `0x00BB66F0` selects the branch | Ghidra size `0xB0`; saved-game version/timestamp, `mPlanets`, `mEmpireID`, `mKey` | Star/planet persistence is a real owner-specific path, not proof of a general profile transaction. |

### 3.3 Mode and service surfaces

| Surface | Direct binary evidence | Interpretation |
|---|---|---|
| App mode registry | `0x007D8C80` validates an index; `0x007D85B0` performs old `OnExit`, active-index write, `0x0212D3E7` send, new `OnEnter`, `0x022D1ADC` send | App mode lifecycle order is direct. Same-index is a no-op; invalid index is rejected. |
| Simulator strategy bridge | `0x00B5B960` initializes separate committed/pending slots; prior direct disassembly resolves `0x00B5B880/8A0/8C0/8E0`; `0x00B63510` recognizes the two mode IDs, normalizes payload words, and dispatches commit/transition effects | Simulator strategy state is separate from App active state and uses a first-request-wins pending path. Listener timing remains unknown. |
| Cell mode | `0x00E81CF0` initializes CellGame/GFX/UI; `0x00E552F0` enters; `0x00E7FC00` exits; `0x00E81F30` disposes; `0x00E80BA0` initializes/rebuilds CellGame; `0x00E7FD00` drains/rebuilds world | Mode lifecycle, Cell simulation, presentation, and serializable state are separate owners. OnExit/Dispose do not directly show a file or serializer write. |
| `cGamePersistenceManager` | `Simulator::cGamePersistenceManager::Get @ 0x00B3D440` returns `DAT_0167EB34`; Ghidra global has one read xref in this focused pass. `0x00B32B20` obtains the service and calls the large service teardown `0x00B0C190`; `0x00B2E940` and `0x00C7F060` also consume the service | A runtime message-aware strategy service exists. Its concrete `LoadGame` body and binding to `0x00B28EC0`/`0x00B279E0` are not established. |
| Save/load operation candidates | `0x00B28EC0` and `0x00B279E0` perform database/stream, ClassSerializer, service, Cell-specific, close, and replacement work | These are strong operation candidates, not confirmed `cGamePersistenceManager` members. |

## 4. Serializer reference graph

The graph below is the minimum graph required by the evidence. Solid edges are direct binary bodies, vtable entries, or direct xrefs. Dashed edges are safe semantic requirements whose exact original implementation remains unresolved.

```text
DBPF/resource records
  [type/group/instance bytes]
       |
       |  content identity only; not profile pointers
       v
Resource manager/database/cache
       |
       +--> live resource/runtime objects (transient)
       +--> direct Cell content records (static content)

mode-specific persistent DTOs
  cSavedGameHeader
  cCellSerializableData
  cEmpire / cMission / cCommEvent / cStarRecord / other cGameData owners
       |
       |  ISimulatorSerializable eligibility
       v
ClassSerializer
  0x00692880 / 0x00692F90 setup
  0x00692900 write dispatcher
  0x00693E10 read dispatcher
       |
       +--> Attribute IDs / ordered descriptor table
       |      +--> read callback
       |      +--> write callback
       |      +--> text callbacks / metadata
       |
       +--> SerializerDatabase / read/write stream
              0x00693D60 / 0x00693CD0
              0x00693AA0 / 0x006939B0
              0x00693900 close/release

ClassSerializer object graph
  class ID + instance/logical object ID
       |
       v
serializer class/instance registry
  stable association record, 0x00695140
  registration/association helper, 0x00695B40
  attribute/object dispatch, 0x00695770
       |
       +--> object already present: reuse/link association
       +--> object absent: create/associate, then fill attributes
       +--> forward/backward/cyclic reference: deferred token
             [exact cycle encoding and load-immediately policy unknown]

PropertyList
  local uint32 property ID -> typed Property map
  parent overlay / operation counter
       |
       v
Property codec
  type/flags + primitive/string/key/array/transform-like values
       |
       v
restored DTO / new runtime owner
  bind object references
  bind ResourceKey/political/noun identities to domain registries
  construct fresh live owners
  rebuild Cell/Space/presentation state outside the saved pointer graph
```

### 4.1 `ClassSerializer` mechanics

`FUN_00692880` initializes a `ClassSerializer` with an object, an attribute array, and a class ID. It copies up to 128 entries whose read/write callbacks are present into a 20-byte descriptor-pointer stride. The resulting fields are consistent with the Ghidra layout: count, serialized count, class ID, current object, and attribute table.

`FUN_00692900` writes the class ID and framing words, iterates the class attributes, invokes the attribute write callback, records callback success and size, and then performs a final stream/status operation. The callback path is not a memory copy of the whole source object. This rejects a raw-struct assumption for the header and Cell candidate.

`FUN_00693E10` reads the class framing, compares stored identity/count, reads attribute identities, resolves them through `FUN_00E0E9F0`, invokes read callbacks, and checks stream state. The resolver at `FUN_00E0E9F0` is a bounded binary-search/lower-bound operation over 20-byte attribute records. A missing/mismatched attribute is not equivalent to an unknown value with a default; the read body has a failure/rejection path.

`FUN_00695140` creates a `0x74`-byte association record when the logical object is absent, links it into manager-owned vectors, and stores backlinks. `FUN_00695B40` either links an existing association or creates one and initializes a ClassSerializer before dispatching attributes. These are strong static reasons to keep an object registry and deferred association in the clean-room model. They do not establish the exact class-object table bytes, whether all references are lazy, or how cycles are encoded.

### 4.2 `PropertyList` mechanics and parent handling

`FUN_006A1540` computes the local entry count from the map extent, writes the count, then writes each local `uint32` property ID followed by a typed-property payload. It stops on the first failed stream/value operation.

`FUN_006A2F60` reads a signed count. A negative branch reads three words, resolves a parent/list manager, and replaces the parent. The normal branch resizes the local map and reads each local ID and typed value, stopping on the first failure.

The safe model is therefore:

```text
local entries: persistable stream data
parent pointer: runtime overlay/reference state unless a future artifact proves its wire form
operation counter: runtime mutation bookkeeping, not an assumed persisted field
```

The Ghidra imported `Property` type is four bytes, but the direct map stride and value writer/reader establish a larger runtime carrier. The community SDK describes `Property` as `0x14` bytes and exposes type/flags. This remains a type/byte conflict; the implementation must use a typed property value model, not a four-byte struct assumption.

### 4.3 Header and Cell vtable evidence

`cSavedGameHeader` has a concrete vtable at `0x0145FAA8`; the table is followed by the UTF-16 class name. Its observed callback entries include the ClassSerializer-backed header wrappers around `0x00B26800`, `0x00B26840`, `0x00B268A0`, and `0x00B268E0`. The concrete body at `0x00B268A0` calls the setup and write dispatchers with descriptor `0x01568B08` and class ID `0x01A80D26`.

`cCellSerializableData` has primary vtable data at `0x01485598` and a secondary refcount vtable at `0x014188C0`. The primary table includes raw method pointers `0x00E51300` and `0x00E51370`; raw-byte inspection shows both initialize a ClassSerializer with class ID `0x01A80D26` and descriptor `0x015A7E38`, then call `0x00692900` or `0x00693E10`. Ghidra did not expose those two addresses as separate function entries, so the method identity is based on the installed vtable and raw body, not an SDK address label alone.

The `0x015A7E38` table is runtime-populated in the static image. This is why the Cell object can be a confirmed serializer candidate while its exact field IDs, names, offsets, and emission order remain unknown.

## 5. Save/load transaction sequence

### 5.1 Save candidate: `FUN_00B28EC0`

The strongest concrete save seam is `0x00B28EC0`. Its direct operation order is:

1. Validate a non-null path and normalize the path.
2. Perform mode/Space/context preparation. It reads the opaque `FUN_00B5B800` value and branches on observed `0x01654C00`, `0x01654C01`, `0x01654C02`, `0x01654C04`, and `0x01654C05` comparison values. This is a mode-dependent operation selection, not proof that the opaque value is a mode ID or enum.
3. Build a `cSavedGameHeader`-shaped object. The local setup includes file version values `3` and `0x25`, a nine-word timestamp, current mode/snapshot state, and a three-word current-planet-like value.
4. Build a `.tmp` path.
5. Open a serializer/database write context through `FUN_00688FA0`, `FUN_00693D60`, and `FUN_00693AA0`.
6. Serialize the header through `FUN_00B268A0` -> `FUN_00692F90` -> `FUN_00692900`.
7. Dispatch a service vtable operation through the result of `FUN_00B3D230`, then invoke serializer-facing object/database operations through `FUN_00675250` and `FUN_006755C0`.
8. For one observed mode branch, call `FUN_00E5C4D0` as a Cell-specific serialization/restore-facing operation.
9. Close/release the stream through `FUN_00693900`.
10. Replace target and temporary paths through `FUN_006891F0`.
11. For the non-empty path branch, optionally write `stars.db.tmp` and replace `stars.db` through `FUN_00BB4BA0` or `FUN_00BB66F0`.

`FUN_006891F0` constructs an `.old` path, removes an existing old path, moves/copies target and temporary paths, and removes the old path afterward. This is bounded temp/backup/replacement behavior. It is not proof of crash atomicity.

### 5.2 Header/file probe: `FUN_00B275A0`

`FUN_00B275A0` builds a path, attempts a file operation, constructs a read database/stream context, initializes the header serializer with `0x01568B08` and class ID `0x01A80D26`, reads the header, closes the context, and compares consumed/available state with `0x20`. It is a header/file probe or validation candidate, not a confirmed named `LoadGame` body.

### 5.3 Load candidate: `FUN_00B279E0`

The strongest concrete load seam is `FUN_00B279E0`. Its direct operation order is:

1. Call `FUN_00B275A0` as a preliminary file/header probe.
2. Normalize/copy the load path.
3. Construct the read-side serializer/database context and allocate a `0x388` helper object through the same database/stream family.
4. Open the read stream through `FUN_00693CD0` and `FUN_006939B0`.
5. Initialize the header ClassSerializer with `0x01568B08` and class ID `0x01A80D26`.
6. Read the header through `FUN_00693E10`.
7. Combine the read values into mode/version state and dispatch service operations.
8. For the Cell mode branch, call `FUN_00E61510`, which clears/adopts the Cell serializable pointer and dispatches the following service path. This is a mode-specific handoff/initialization seam; it is not itself a complete field-by-field load trace.
9. Close/release the database/stream context through `FUN_00693900` and release the service-side read objects.

`FUN_00B28990` calls `FUN_00B279E0` and then changes a forwarded mode/load marker to `&DAT_01654C08`. `FUN_00B294C0` is a path-normalizing wrapper that calls `FUN_00B28EC0` and conditionally checks `FUN_00B28750` after a save. These wrappers make the operation candidates reachable from mode/save orchestration, but they do not bind either candidate to a named `cGamePersistenceManager` vtable member.

### 5.4 Secondary star database and recovery

`FUN_00BB4BA0` writes a star/planet database through `stars.db.tmp`, serializes header/class records, closes, and replaces `stars.db`. `FUN_00BB66F0` sets a branch flag and delegates to the same writer.

Recovery/probe helpers are separate:

- `FUN_00B28070` checks `old/complete` and `old/valid` markers.
- `FUN_00B282E0` checks a set of old artifacts including `planetRecords.pkp`, `planetscripts.pld`, `stars.db`, `GGEUserData.dat`, `*.spo`, and `valid`.
- `FUN_00B28750` checks `old/complete`.
- `FUN_00B289E0` creates/removes `dbreadinitiated` and `dbreadcompleted` markers around an old-directory/database read path.

The evidence supports marker-based recovery surfaces and independent artifact replacement. It does not establish a journal or manifest spanning `.spo` and `stars.db`, nor universal rollback after a serializer callback failure.

## 6. Object identity and restoration rules

### 6.1 Rules supported by the binary and SDK architecture

1. **Logical identity, not host address.** A `ClassSerializer` class ID, attribute ID, and serializer object/instance identity are distinct from a host pointer, pool index, or cache handle. The class-object/association helpers at `0x00695140` and `0x00695B40` make a stable registry necessary.
2. **Class identity before field dispatch.** The read dispatcher validates class/count/attribute identity before invoking field callbacks. A load implementation must reject a mismatched class or attribute rather than reinterpret arbitrary bytes as a field.
3. **Deferred association.** A reference can be read before its target object is fully populated. The clean-room contract is a logical reference token, an optional immediate-load request, and a later bind step. The original wire encoding, cycle rule, and duplicate/missing-ID behavior are unresolved.
4. **Separate ID domains.** `ResourceKey` is a content identity; `cGameData` political ID and noun ID identify game-data/noun objects; serializer class/instance IDs identify persistence objects; Cell pool indices identify live Cell allocations. They are not globally interchangeable.
5. **Reference-counted owner links are runtime ownership.** `cGameData` has an intrusive owner pointer and political ID; `cEmpire`, `cMission`, and `cCommEvent` expose intrusive/reference-counted fields. AddRef/Release must be paired when an implementation retains an object. A serialized reference is a logical link, not a raw pointer or a retained borrow.
6. **Noun/game-data materialization is a separate registry.** `FUN_00B21340` materializes a `tGameDataVectorT<cGameData>` from a noun map and clears `needsUpdate`; the root-closure report places the map at `cGameNounManager+0x98` (`knowledgegraph/research/root-closure/track-e-empire-chain.md:15-44,85-117`). This registry can supply a restored object/factory, but its exact bridge to the serializer class-object table is not recovered.
7. **Parent PropertyList references are not ordinary local entries.** The negative-count read branch reads three words and resolves/replaces a parent. The implementation should keep parent lookup separate from local property persistence and expose an explicit parent-reference policy if compatibility is required.
8. **Pool identity is transient.** `cCellGame+0x411C`, `cCellObjectData` pool indices, GFX associations, and live service pointers must not become durable object IDs by accident. A restore may allocate a new pool slot and bind it to a logical entity ID.

### 6.2 Rules that cannot yet be frozen

- Whether object references are always class/instance pairs, or may use class-specific IDs/pointers.
- Whether forward references, cycles, duplicate IDs, missing objects, and failed callbacks are repaired, rejected, or partially retained.
- The exact `COMSerializer` class-object table and map order. The community SDK declares `mClassIDMapForWriting`, `mClassIDMap`, instance counts, and `onSetSPSerializable` / `onGetSPSerializable` helpers (`Serialization.h:221-283`), but this is a community declaration, not a recovered byte table.
- Whether every `ISimulatorSerializable` subtype is written through `ClassSerializer` or through another stream operation.
- Whether the noun/game-data registry is the factory used for all saved object reconstruction.
- Exact field survival and version/default behavior for `cCellSerializableData`, `cEmpire`, `cMission`, and other owners.

## 7. Mode transition handoff and state transfer

### 7.1 App and Simulator mode axes

The App mode helper at `0x007D85B0` has direct local order:

```text
old mode OnExit
  -> write cGameModeManager+0x28 active index
    -> send mode-exit announcement 0x0212D3E7
      -> new mode OnEnter
        -> send mode-enter announcement 0x022D1ADC
```

`0x007D8C80` validates the requested index and delegates to the helper. The same-index request is a no-op. This is an App lifecycle transition, not a persistence call.

`0x00B63510` recognizes the two announcement IDs, reads payload words at `+0x08/+0x10`, normalizes them through `0x00B5C9D0`, suppresses equal normalized IDs, and selects exit/enter transition bodies. The message transport may be immediate or deferred; the helper-local send order is confirmed, listener execution timing is not.

The Simulator strategy constructor `0x00B5B960` initializes committed and pending mode slots to `-1` and request path `0`. Prior direct disassembly resolves the first-request-wins guards at `0x00B5B880/0x00B5B8A0` and commit helpers at `0x00B5B8C0/0x00B5B8E0`. This is a separate strategy channel from App active index.

### 7.2 Cell mode and serializable DTO

`cCellModeStrategy::Initialize @ 0x00E81CF0` creates `sCellGame`, `sCellGFX`, and `sCellUI`. `OnEnter @ 0x00E552F0` resets flags, starts GFX display, and performs setup. `OnExit @ 0x00E7FC00` restores display globals, drains transient interaction/UI state, and releases presentation/service work. `Dispose @ 0x00E81F30` releases CellGame, GFX, and UI owners separately.

The direct OnExit and Dispose bodies do not call `FUN_00B28EC0`, `FUN_00B279E0`, `FUN_00692900`, `FUN_00693E10`, or a file-replacement helper. This rejects a static claim that ordinary mode exit is itself a durable save. It does not prove that no other caller can autosave.

`FUN_00E63D10` allocates a new `0xEC` `cCellSerializableData`, replaces the global serializable slot when different, releases the old refcounted object, and calls `FUN_00E627A0` to copy the value fields. `FUN_00E627A0` copies the progression/parts/counters/mission/telemetry ranges from the source object into the destination, excluding the vtable/refcount prefix. This is a concrete in-memory DTO/copy seam.

`FUN_00E819B0` can adopt the `cCellGame+0x5190` serializable pointer into the global serializable slot and then runs Cell initialization. `FUN_00E80BA0` allocates or adopts `cCellGame+0x5190`, sets the `+0x51DA` presence flag when a serializable object is present, clears the global serializable slot, and invokes world/scale rebuild work. `FUN_00E7FD00` drains old Cell pool/GFX/query/UI state and rebuilds the world; it is a runtime reset/rebuild, not a disk load.

The safe handoff model is:

```text
old mode
  -> OnExit / service cleanup
    -> explicit handoff DTO if the transition requests persistence
      -> new mode Initialize / fresh owner construction
        -> bind DTO fields and object references
          -> rebuild presentation and live pools separately
```

The exact original owner of cross-mode transfer, whether a save is automatically requested by some higher-level caller, and whether a live Cell object ever crosses the boundary remain unresolved.

### 7.3 Events and state machine boundary

The mode announcements are App transport events, not serializer records. The mode transition and persistence candidates are separate call surfaces. The minimum OpenSpore state machine should therefore model:

```text
mode_requested
  -> old_mode_exit
    -> active_mode_published
      -> exit_announcement_emitted
        -> new_mode_enter
          -> enter_announcement_emitted
            -> handoff_requested? -> DTO committed
              -> new runtime owner bound
```

If no handoff is requested, the state machine still exits/disposes the old mode and enters a fresh runtime. If an explicit save is requested, the transaction is a separate child operation. The original event queue timing and listener callbacks should not be treated as persistence ordering.

## 8. Minimum semantic model required by OpenSpore

OpenSpore needs the following model to implement safely without claiming original bytes:

### 8.1 Value and schema layer

- `PropertyValue`: typed value with type, flags, scalar/string/key/array/aggregate payload, and deterministic codec behavior.
- `PropertyListData`: local property ID/value entries, explicit parent-reference policy, and runtime operation counter separated from persisted data.
- `AttributeDescriptor`: stable attribute ID, optional name, logical offset/size metadata, read callback, write callback, and optional text callback.
- `ClassSchema`: class ID, ordered attributes, version, and migration/default policy.
- `SerializableContract`: `Write`, `Read`, optional `WriteToXML`, and logical noun/object identity. The contract is capability, not proof of full field coverage.

### 8.2 Object graph layer

- `ObjectId`: class ID plus logical instance ID, with domain-specific political/noun/ResourceKey fields kept separate.
- `ObjectRegistry`: create-or-resolve association, class/instance validation, owner/refcount tracking, and pending-reference list.
- `ObjectReference`: logical target plus resolution state; never a host address.
- `DeferredBindQueue`: forward/backward/cyclic references are bound after required owners exist, or fail deterministically according to the selected policy.
- `NounFactoryPort`: a clean-room adapter from logical noun/definition/political identity to a newly created runtime object. Exact original factory mapping remains replaceable.

### 8.3 Persistence document and transaction layer

- `SaveHeader`: major/minor version, object counts, timestamp, mode, snapshot flag, current planet/resource key, and explicit unknown-field policy.
- `SaveDocument`: header, class-object table, serializable records, property records, references, and migration metadata.
- `SerializerDatabase`: open read/write stream, load/save class objects, close/release, and explicit good-state checks.
- `SaveTransaction`: stage to temporary path, close/check, replace target, and record bounded recovery markers.
- `MultiArtifactPolicy`: if `.spo` and `stars.db` must be one compatible transaction, add a manifest/journal; otherwise expose independent replacement explicitly. No universal crash atomicity may be claimed from the observed temp/old/replace helpers.
- `FailurePolicy`: first stream/callback failure short-circuits; cleanup, partial target handling, and retry behavior are explicit and testable.

### 8.4 Mode handoff layer

- `ModeCoordinator`: App active-index lifecycle separate from Simulator strategy/input/SpaceContext/scenario axes.
- `ModeExit`: old mode service cleanup, with no implicit durable write unless an explicit policy requests one.
- `ModeEnter`: fresh runtime service construction, then DTO binding and presentation rebuild.
- `CellSaveData`: a bounded DTO contract. Do not serialize live `cCellGame`, pool indices, GFX/UI handles, or host pointers.
- `StateTransfer`: copy/adopt the DTO under an explicit transaction/request boundary; do not assume the original pointer survives mode exit.

This is enough to proceed with implementation seams and deterministic tests. It is not enough to claim compatibility with an original save file.

## 9. Competing hypotheses and adversarial evidence

| ID | Competing hypothesis | Prediction if true | Evidence for | Contradictory/limiting evidence | Decision |
|---|---|---|---|---|---|
| H1 | Callback/class-object graph with stable IDs and deferred references | Stream contains class/attribute IDs; load resolves IDs before callbacks; raw pointers are not emitted | `0x00692900`, `0x00693E10`, `0x00692880`, `0x00695140`, `0x00695B40`, SDK `ISerializerReadStream::ReadPointer` / `ICOMSerializer` declarations | Exact object-table bytes, cycle encoding, and all subtype factories remain unknown | **Supported architecture; wire details open** |
| H2 | Raw `cSavedGameHeader`/Cell struct stream | Save/load would copy fixed structs and would not need class/attribute callbacks | Object sizes are known | Header wrapper calls ClassSerializer; Cell vtable methods call ClassSerializer; `COM` strings are class metadata, not a proven envelope | **Rejected as the general model** |
| H3 | `PropertyList` is the exact `.spo` outer format | Save body would directly open/write a PropertyList and its parent pointer would be the saved owner | `.prop` strings and `PropertyList` are locally declared | No direct `.spo` -> PropertyList link; negative parent branch and outer framing remain open | **Not established** |
| H4 | `cGamePersistenceManager` directly owns `0x00B28EC0/0x00B279E0` | Save/load bodies would receive `DAT_0167EB34` or call its `LoadGame` vtable slot | SDK declares `LoadGame` at `+0x10`; `Get` returns `DAT_0167EB34` | Save/load candidates call `0x00B3D230`, not `0x00B3D440`; no concrete manager this/vtable binding recovered | **Unconfirmed; preserve operation/service ports separately** |
| H5 | Cell `OnExit`/`Dispose` automatically saves or transfers the live Cell graph | Teardown would call serializer/file helpers and preserve live `cCellGame`/pool/GFX state | `cCellSerializableData` is held at `+0x5190`; handoff/copy helpers exist | Direct OnExit/Dispose bodies show cleanup only; `0x00E627A0` is field copy; `0x00E7FD00` drains/rebuilds old pool identity | **No static autosave; explicit DTO handoff supported, runtime unknown** |
| H6 | One universal mode/owner object carries all handoff state | All mode axes would share one enum/pointer and lifecycle | Repeated manager accessors and opaque forwarded state | App, Simulator, input, SpaceContext, Cell axes have distinct fields/bodies; `0x00B5B800` remains opaque by-value | **Rejected; keep axes separate** |
| H7 | Cross-file atomic transaction is already guaranteed | A manifest/journal would cover `.spo` and `stars.db`, and failures would roll back | Temp/old/replace and recovery marker surfaces exist | `0x006891F0` and `0x00BB4BA0` are separate; no journal/manifest binding recovered | **Bounded replacement only** |
| H8 | Host addresses/pool indices are durable object identity | Load would compare/serialize raw addresses and restore same pointers | Some fields are pointer-shaped | Class IDs/attribute IDs, cGameData political IDs, ResourceKey, refcounted owners, and DTO copy boundary contradict universal raw identity | **Rejected; logical IDs required** |
| H9 | Direct Cell resource records are profile state | Cell content TypeIDs would use the same generic save envelope | Both are Cell-related | Direct Cell records are fixed TypeID layouts; `cCellSerializableData` is a separate `0xEC` runtime object with its own vtable | **Rejected; content and save state separate** |
| H10 | `COM` class-name strings define a complete outer binary envelope | Save bytes would contain a standalone COM record header | `SP_Simulator/cSavedGameHeader/COM` and `CellSaveGame/COM` strings exist | Strings are passed to allocation/class metadata while descriptor/class IDs and database streams are separate arguments | **Type metadata supported; envelope unresolved** |

## 10. Smallest decisive observations

The current static graph is sufficient for a clean-room seam but not for original compatibility. The smallest observations that would change or close the remaining claims are:

1. **Manager binding:** one direct call edge from a concrete `cGamePersistenceManager` instance/vtable to `0x00B28EC0` or `0x00B279E0`, or one runtime trace showing `DAT_0167EB34` entering the candidate with a matching `this` pointer and service vtable. This would settle operation ownership; without it, keep the operation and service ports separate.
2. **Object graph:** one disposable explicit save/load round trip containing a forward reference and, if naturally reachable, a cycle. Capture class/instance IDs, attribute IDs, callback order, bind order, refcount changes, and failure outcome. This distinguishes stable deferred IDs from raw pointers and reveals the actual cycle policy.
3. **Mode handoff:** one trace across Cell `OnExit`/`Dispose` with no manually invoked save, followed by explicit load/reopen. Record whether any serializer/file operation occurs during teardown, whether `0x00E63D10/0x00E627A0` are used, and whether a new live owner is created. This separates explicit DTO transfer from automatic mode save.
4. **Outer framing:** one read-only original `.spo` or equivalent database artifact with its first bytes and first record boundary, or a concrete parser call edge proving a database/COM/checksum wrapper. Static path strings alone are insufficient.
5. **Field survival:** one field-whitelist matrix across save, close, reopen, and restore for `cSavedGameHeader` and `cCellSerializableData`. A layout or vtable write/read wrapper alone cannot establish survival.
6. **Atomicity/recovery:** one approved interrupted/failing replacement and one successful multi-artifact update. Record file hashes, marker order, and whether `.spo` and `stars.db` can diverge. This is required before claiming crash atomicity.

The smallest observation set for a clean-room implementation is not any one of these: it is the existing static schema/callback boundary plus explicit local tests. The observations above are required only for original-wire or original-runtime claims.

## 11. Runtime plan (proposed, not executed)

The plan follows `knowledgegraph/research/runtime-oracle/candidate-experiments.md:356-447` and `replacement-observability.md:317-328,652-682`:

1. Preflight the pinned binary and environment; hash the target and record no-write status. Never use the original profile, `SPORE/`, or the canonical KG as an output location.
2. Obtain positive original Cell reachability before attempting Cell persistence. If Cell is unreachable, record a reachability negative; do not synthesize a save/load result.
3. Run one explicit save/reopen/load in a disposable profile. Record only bounded schema, object identity, field-whitelist, stream-open/close, callback, and failure observations. Do not retain proprietary payload bytes.
4. Run the C8 mode observation without an extra save: capture `0x00E7FC00`, `0x00E81F30`, `0x00E51300`, `0x00E51370`, `0x00E61550`, `0x00E63D10`, `0x00E627A0`, `0x00E80BA0`, `0x00B3D440`, `0x00B28EC0`, and `0x00B279E0` where reachable.
5. Exercise a failing stream or cyclic reference only on a disposable copy through a naturally reachable path. Do not inject a pointer, patch serializer code, or alter the target after the run.
6. Emit the bounded artifacts described by the existing observability plan: `calls.jsonl`, `writes.jsonl`, `events.jsonl`, `modes.jsonl`, `objects.jsonl`, and `save.jsonl`. Record missing categories as `not_observed_in_capture`, not as success.
7. Verify the disposable profile, source hash, `SPORE/` hash, and canonical KG are unchanged; release the lock and restore any temporary observation state.

No such runtime observation was performed for this report.

## 12. Local community and modding evidence

The local Spore-ModAPI tree is useful semantic corroboration, not original runtime proof:

- `ISimulatorSerializable.h:30-50` declares `Write`, `Read`, `WriteToXML`, `GetNounID`, and the refcounted serializable variant.
- `Serialization.h:26-114` declares database/stream open/close, object pointers, simulator pointers, properties, raw data, class objects, and serialization versions. `Serialization.h:147-201` defines `Attribute` and the 128-entry `ClassSerializer` architecture. `Serialization.h:221-283` declares `COMSerializer` class/instance maps, CRC helper, and object association helpers.
- `SerializationTypes.h:31-57` shows pointer serialization through serializer pointer operations, not raw address copying. `SerializationTypes.h:204-228` declares `ResourceKey` field order, while `Property.h:35-75` declares property type IDs and `Property.h:110-123` declares ownership/array flags. These declarations explain the architectural intent but do not settle binary bytes.
- `PropertyList.h:35-45,141-186` describes the `.prop` representation, local map, parent lookup, and Read/Write stream contract. The source comments explicitly distinguish local mutation from parent behavior; they do not prove outer save-file framing.
- `GamePersistenceManager.h:33-62` declares the message-listener/strategy manager and `LoadGame(GameLoadParameters)`, but its own `ASSERT_SIZE` comment marks the parameters size uncertain. This is name-level evidence for a load service, not a manager binding for `0x00B28EC0/0x00B279E0`.
- `cSavedGameHeader.h:8-22` and `cCellSerialiazibleData.h:21-52` corroborate the Ghidra field layouts, but the class names and field labels are community/SDK provenance.
- `cGameData.h:34-91` and `Object.h:46-85` corroborate noun/political-ID and intrusive ownership concepts, but not the serializer's exact restore factory.
- `docs/analysis/reconstruction-readiness.md:69-72,210-218` explicitly states that community RE headers provide name-level provenance and that a name alone cannot justify implementation readiness.
- `docs/analysis/track-01-noun.md:88-112` records the local policy that community documentation supports noun/registry concepts only, not ABI proof.
- `docs/RENDERWARE-RESEARCH.md:356-366` records Spore-ModAPI and SporeModder-FX as reference-only community projects; the format-parser evidence does not establish gameplay save/load behavior.

The local evidence therefore strengthens the minimum semantic model but cannot promote SDK names, class-name strings, or field declarations to original runtime/wire truth.

## 13. Final decision

**Implementation can proceed without exact resolution only under a clean-room, compatibility-excluded contract.** The safe contract is:

- schema/callback serialization with versioned descriptors;
- typed properties and explicit local/parent boundaries;
- stable logical object IDs and deferred reference binding;
- no host pointer or Cell pool-index persistence;
- explicit DTO handoff across mode boundaries;
- no implicit save on mode exit;
- temp/close/replace transaction boundaries with independent artifact policy;
- separate persistence service, serializer database, noun registry, resource registry, and live Cell pool owners.

The implementation must stop and reopen this blocker if any of the following becomes a requirement:

- byte-compatible original `.spo`/`.prop` files;
- exact original field order, descriptor table, object-reference table, or migration behavior;
- original field-survival guarantees;
- automatic save on Cell mode exit;
- original multi-file crash atomicity;
- original manager/vtable/object identity;
- original runtime restore ordering or cross-mode live-pointer handoff.

## 14. Essential citations

### Ghidra / binary

- PropertyList: `0x006A1540`, `0x006A2F60`, Ghidra `PropertyList` layout.
- ClassSerializer setup/write/read: `0x00692880`, `0x00692F90`, `0x00692900`, `0x00693E10`.
- Attribute identity resolver: `0x00E0E9F0`.
- Serializer object associations: `0x00695140`, `0x00695B40`, `0x00695770`.
- Serializer database/stream lifecycle: `0x00693D60`, `0x00693CD0`, `0x00693AA0`, `0x006939B0`, `0x00693900`.
- Saved-game header: `0x00B268A0`, vtable `0x0145FAA8`, descriptor `0x01568B08`, class ID `0x01A80D26`.
- Save/load candidates: `0x00B28EC0`, `0x00B279E0`, probe `0x00B275A0`, wrappers `0x00B28990`, `0x00B294C0`.
- Replacement/recovery: `0x006891F0`, `0x00BB4BA0`, `0x00BB66F0`, `0x00B28070`, `0x00B282E0`, `0x00B28750`, `0x00B289E0`.
- Cell serializable object: `0x00E61550`, `0x00E63D10`, `0x00E627A0`, vtable `0x01485598`, refcount vtable `0x014188C0`, raw vtable methods `0x00E51300/0x00E51370`.
- Cell mode/state: `0x00E81CF0`, `0x00E552F0`, `0x00E7FC00`, `0x00E81F30`, `0x00E80BA0`, `0x00E7FD00`.
- App mode transition: `0x007D8C80`, `0x007D85B0`; Simulator strategy `0x00B5B960`, `0x00B63510`; mode event IDs `0x0212D3E7`, `0x022D1ADC`.
- Persistence service accessor: `0x00B3D440`, global `0x0167EB34`; service consumer examples `0x00B2E940`, `0x00B32B20`, `0x00C7F060`.

### Local files

- `docs/analysis/serialization-model.md:130-249,253-299,301-380,397-471`
- `docs/analysis/gameplay-state-machines.md:361-376`
- `knowledgegraph/research/architecture-resolution/track-04-persistence.md:11-35,37-112`
- `knowledgegraph/research/architecture-resolution/followup-06-persistence.md:17-37,41-71,73-145,154-202,204-294`
- `knowledgegraph/research/architecture-resolution/track-03-mode.md:39-125`
- `knowledgegraph/research/architecture-resolution/track-08-cell-lifecycle.md:11-29,106-153,217-247`
- `knowledgegraph/research/architecture-resolution/track-05-event.md:123-156`
- `docs/analysis/event-message-map.md:46-52,76-92,122-152`
- `knowledgegraph/research/root-closure/track-e-empire-chain.md:15-44,55-117,190-199`
- `knowledgegraph/research/runtime-oracle/candidate-experiments.md:356-447`
- `knowledgegraph/research/runtime-oracle/replacement-observability.md:317-328,652-682`
- `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/ISimulatorSerializable.h:30-50`
- `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/Serialization.h:26-114,147-201,221-283`
- `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/SerializationTypes.h:31-57,204-228`
- `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/App/Property.h:35-75,110-123`
- `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/App/PropertyList.h:35-45,141-186`
- `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/SubSystem/GamePersistenceManager.h:33-62`
- `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/SubSystem/cSavedGameHeader.h:8-22`
- `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/Cell/cCellSerialiazibleData.h:21-52`
- `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/cGameData.h:34-91`
