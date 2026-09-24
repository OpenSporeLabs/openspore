# Persistence and Serialization Types Archaeology

## Scope and evidence policy

This partition documents the original Spore persistence, resource database, property, simulator serialization, saved-game, and related caller/vtable evidence for `SporeApp.exe` 3.1.0.22. It is static archaeology only. No original save/load trace, `.prop`/`.spo` round-trip, or fresh Ghidra decompilation is included.

Claims are separated as:

- **OBSERVED**: directly present in a committed binary, record, field, or byte-level artifact.
- **SUPPORTED**: supported by multiple committed artifacts, but not runtime-validated.
- **INFERRED**: a bounded hypothesis; not an original-runtime fact.
- **UNKNOWN**: insufficient evidence.

SDK names and Ghidra labels are imported names, not proof of runtime contracts. Vtable candidates are structural evidence only. Current OpenSpore code is clean-room comparison material, never original source or proof of original wire format.

## Binary baseline

| Field | Value |
|---|---|
| Binary | `SporeApp.exe` |
| Version | `3.1.0.22` |
| SHA-256 | `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e` |
| Language | `x86:LE:32:windows` |
| Canonical functions | 58,757 |
| Canonical xrefs | 223,704 |
| Vtable candidates | 3,081 |
| Vtable-reference edges | 11,898 |
| Data-reference edges | 4,049 |

The live Ghidra bridge was reachable, but no `SporeApp.exe` program was open for a fresh read. Therefore no new decompilation, byte read, or vtable mutation is claimed.

## Evidence map

The primary committed sources are:

- `docs/RECON-3.1.0.22.md`: binary inventory, SDK import, address map, provenance.
- `docs/analysis/semantic-atlas.md`: canonical coverage counts and evidence policy.
- `docs/BOUNDARIES.md`: replacement boundaries and unresolved property serialization.
- `docs/ASSET-PATH.md`: DBPF/resource decode path.
- `docs/RENDERWARE-RESEARCH.md`: RW4/GMDL field and container evidence.
- `knowledgegraph/triage/xrefs-2540f2ca.summary.json` and `.tsv`: xref closure and per-function edges.
- `knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl`: SDK labels, categories, structures, vtable candidates, priorities.
- `docs/analysis/vtables.json`: vtable candidates and structural references.
- `knowledgegraph/research/decomp-gap/sim-core-00.json`: `ClassSerializer` and simulator persistence records.
- `knowledgegraph/research/decomp-gap/sim-core-04.json`: persistence-manager caller records.
- `knowledgegraph/research/decomp-gap/gameglobal-misc-00.json`: `Editor_Save` and serialization-resource gap records.
- SDK headers and `SporeGhidra_march2017.xml`: imported interfaces, layouts, names, and TypeIDs.
- `src/assets/*` and `src/compat/ResourceProvider.hpp`: current clean-room comparison code.

## Function map

| Original/imported name | VA | Status | Evidence boundary |
|---|---:|---|---|
| `App::PropertyList::Read` | `0x006A2F60` | Confirmed SDK-name mapping | Body unavailable; no wire format |
| `App::PropertyList::Write` | `0x006A1540` | Confirmed SDK-name mapping | Body unavailable; no wire format |
| `Resource::cResourceManager::Initialize` | `0x008DE530` | Confirmed SDK-name mapping | Body unavailable |
| `Resource::DatabasePackedFile::Lock` | `0x008D84D0` | Confirmed SDK-name mapping | Body unavailable |
| `Simulator::cGamePersistenceManager::Get` | `0x00B3D440` | Confirmed for committed GOG triage | SDK also lists `0x00B3D2A0` |
| `Simulator::ClassSerializer::Write` | `0x00692880` | Confirmed SDK-name mapping | Body unavailable |
| `Simulator::ClassSerializer::Read` | `0x00693DD0` | Confirmed SDK-name mapping | Body unavailable |

The decomp-gap ledger records direct calls into `ClassSerializer::Write` from `0x00692F90` at `0x00692F9F` and `0x00695B40` at `0x00695BA1`. It records a call into `ClassSerializer::Read` from `0x0120D030` at `0x0120D033`. These are static graph edges, not runtime sequence evidence.

`cGamePersistenceManager::Get` has recorded callsites including `0x00B2E9DA`, `0x00B2EB1D`, `0x00B32BC8`, and `0x00C7F109`. The surrounding bodies and save/load order remain unavailable.

## Resource and record architecture

The SDK establishes a layered resource model:

- `Resource::Database` owns database lifecycle, access, key enumeration, and record open/close.
- `Resource::IRecord` provides a `ResourceKey`, underlying `IO::IStream`, owning database, and record open/close.
- `Resource::RecordInfo` is a declared `0x10` structure containing:

| Offset | Field | Type | Declared meaning |
|---:|---|---|---|
| `0x00` | `chunkOffset` | `size_t` | Record data offset in package |
| `0x04` | `compressedSize` | `size_t` | Stored size |
| `0x08` | `memorySize` | `size_t` | Uncompressed size |
| `0x0C` | `flags` | `short` | `0` uncompressed; `0xFFFF` compressed |
| `0x0E` | `isSaved` | `bool` | Whether the record was written |

`App::PropertyList` is a `Resource::CachedResourceObject` with a `vector_map<uint32_t, Property>` at `0x18`, a parent pointer at `0x30`, and an operation counter at `0x34`. Parent lookup is recursive. The SDK declares `Read(IO::IStream*)`, `Write(IO::IStream*)`, and `SaveToDatabase(PropertyList*, Resource::Database*, bool)`.

This proves the architectural boundary, not the original PROP byte order, count encoding, compression, or version negotiation. `.prop` serialization is `UNKNOWN`.

## Property system

`App::Property` declares a `uint16_t` type tag and a flags/value model. Declared type IDs include:

- `Bool=0x01`, `Int32=0x09`, `UInt32=0x0a`, `Float=0x0d`
- `String8=0x12`, `String16=0x13`, `Key=0x20`, `Text=0x22`
- `Vector2=0x30`, `Vector3=0x31`, `ColorRGB=0x32`, `Vector4=0x33`, `ColorRGBA=0x34`
- `Transform=0x38`, `BBox=0x39`

Flags include cleanup, pointer-owned, and skip-deallocation behavior. `IPropManager` exposes property name/ID lookup, group name/ID lookup, property-list lookup, property-definition lookup, and property-list registration/removal.

The SDK header asserts a `Property` size of `0x14`, with flags at `0x10` and type at `0x12`. The imported Ghidra XML models a four-byte `Property` with flags at `0x0` and type at `0x2`. This is an unresolved layout contradiction and must not be used as a binary contract without direct field evidence.

## Simulator serializer interfaces

The SDK declares `ISerializerDatabase`, `ISerializerReadStream`, and `ISerializerWriteStream` around database records and `ResourceKey`s. The declared operations include:

- Open/close read or write streams for a resource key.
- Access the underlying record and database.
- Read/write raw data.
- Read/write properties, including deprecated property-ID variants.
- Read/write object pointers.
- Read/write simulator-serializable pointers.
- Read/write class objects.
- Read/write serialization version.
- Track percentage completion.

`ISimulatorSerializable` declares virtual `Write`, `Read`, an opaque function, `WriteToXML`, and `GetNounID` slots.

`SerializationTypes.h` gives a strong architectural model for declared primitive codecs:

| Type | Declared representation |
|---|---|
| `bool` | `IO::ReadBool8` / `WriteBool8` |
| `int32_t` | `IO::ReadInt32` / `WriteInt32` |
| `uint32_t` | `IO::ReadUInt32` / `WriteUInt32` |
| `float` | `IO::ReadFloat` / `WriteFloat` |
| `string8` | `uint32` count followed by count bytes |
| `string16` | `uint32` count followed by little-endian `int16` values |
| `ResourceKey` | `groupID`, `typeID`, `instanceID`, each `uint32` |
| `vector<T>` | `int32` count followed by serialized elements |
| object pointer | Serializer pointer operation |

These are SDK-declared operations, not observed original bytes. The concrete database, stream, pointer-table, CRC, and class-object encodings remain `UNKNOWN`.

## Class attributes and registries

`Simulator::Attribute` is a declared `0x3C` structure containing:

- name at `0x00`
- numeric ID at `0x04`
- object offset at `0x08`
- current object at `0x18`
- offset, binary read, binary write, text read, and text write callbacks from `0x20` through `0x30`

`Simulator::ClassSerializer` is a declared `0xA14` structure with 128 `AttributePointer` entries. Each pointer contains an attribute ID, data size, serialized flag, binder context, and attribute pointer. The SDK says attributes must be ordered because they are searched with binary search. The default class ID is `0x1A80D26`.

`XmlSerializer::AttributesToXml` and the binary `ClassSerializer::Read`/`Write` bodies are not present in the committed decompilation ledger. The table is a supported structural description, not a recovered wire schema.

`IPropManager` is a separate property-definition and property-list registry. The SDK declares name/ID and group/ID lookup, but the original property-definition text files and exact mapping from names to IDs are not reconstructed here.

## Saved-game state

`cSavedGameHeader` is declared as size `0x68` and contains:

| Offset | Field | Type |
|---:|---|---|
| `0x0C` | `mFileVersionMajor` | `uint32_t` |
| `0x10` | `mFileVersionMinor` | `uint32_t` |
| `0x14` | `mObjectCountMap` | `map<uint32_t, int>` |
| `0x30` | `mTimeStamp` | `int[9]` |
| `0x54` | `mGameMode` | `uint32_t` |
| `0x58` | `mbSnapshot` | `bool` |
| `0x5C` | `mCurrentPlanetKey` | `ResourceKey` |

`GameLoadParameters` is declared as size `0xB4`; the SDK itself marks this size as uncertain. It includes `.spo` game name, star name, creature/profile references, star ID, difficulty, game mode, and unknown fields.

A likely lifecycle is:

1. Resolve a `.spo` database record from a game name or key.
2. Open the record and create serializer read streams.
3. Load class objects and version information.
4. Read serializable simulator objects and property values.
5. Restore saved-game header metadata.

This sequence is `INFERRED`. No function-body or runtime trace confirms its order.

## Cell state versus Cell resources

`cCellSerializableData` is a declared `0xEC` `ISimulatorSerializable` state object. It includes game mode, player creature key, progression counters, 13 unlocked parts, play counters, game time, game ID, difficulty, six mission entries, and telemetry-like flags.

Committed Cell resource dossier evidence describes direct field serialization without a name or ID envelope. These are different layers:

- `cCellSerializableData` is runtime serializable simulator state.
- Cell resource records are asset/data records with their own direct field layout.

Do not serialize the SDK `cCellSerializableData` structure as a Cell resource record without independent evidence.

## Current OpenSpore comparison

| Area | Current source | Assessment |
|---|---|---|
| DBPF | `src/assets/Dbpf.cpp` | Partial match: tested DBPF v3 index and QFS path |
| GMDL | `src/assets/Gmdl.cpp` | Match for tested version-8 path |
| RW4 | `src/assets/Rw4.cpp` | Partial structural match |
| WorldObject | `src/assets/WorldObject.cpp` | Partial structural/heuristic match |
| Resource seam | `src/compat/ResourceProvider.hpp` | Read-only identity-to-bytes boundary |
| Simulator persistence | Current simulator/configuration state | Not equivalent to original `.prop`/`.spo` wire behavior |

The current DBPF parser uses a 96-byte header, index count at `0x24`, index offset at `0x40`, 28-byte index rows, and QFS decompression. The current GMDL parser accepts version 8, reads `refCount` with an explicit big-endian read, and treats later tested words as little-endian. The current RW4 parser validates the magic, header, manifest, type-code table, and section bounds. The current WorldObject parser validates versions 9/10 and uses bounded name/vector heuristics.

These implementations are independent clean-room code. They do not prove the original resource manager's complete behavior and do not add original save-game support.

## Contradictions retained

1. **Property layout:** SDK header versus imported Ghidra XML disagree on size and offsets. `UNRESOLVED`.
2. **Persistence manager address:** SDK lists `0x00B3D2A0` and `0x00B3D440`; committed GOG triage uses `0x00B3D440`. `PARTIALLY_RESOLVED_FOR_GOG_TRIAGE`.
3. **cAdvectEntry types:** committed file evidence describes strength, variance, and period as `f32`; SDK declarations are integer-like. `UNRESOLVED`.
4. **GMDL refCount endianness:** historical LE parsing failed for tested records; current code uses BE for the version-8 `refCount`. `RESOLVED_FOR_CURRENT_TESTED_PATH`.
5. **Cell layers:** Cell resource records and `cCellSerializableData` are not interchangeable. `RESOLVED_AS_DIFFERENT_LAYERS`.
6. **Ghidra state:** bridge reachable, but no open program. `LIMITATION_RECORDED`.

## Unknowns and hypotheses

### Unknowns

- Exact `.prop` byte format.
- Exact `.spo` container, record ordering, checksum, and version framing.
- Serializer stream framing and object-pointer table encoding.
- Concrete class-object registry and class serializer implementation.
- `PropertyList::Read`/`Write` bodies and runtime field order.
- `cGamePersistenceManager::LoadGame` body and save/load ordering.
- Original runtime ownership of vtable candidates.
- Any original-process save/load trace.

### Bounded hypotheses

- Saved-game load probably resolves a `.spo` record, opens serializer streams, loads class objects, then restores serializable simulator state.
- `PropertyList` persistence probably encodes property IDs and type-dependent values, while parent relationships are primarily a runtime lookup layer.
- `ClassSerializer` may use attribute IDs and serialized flags as a compact field-description table, with binary callbacks for fields and text callbacks for XML/text output.
- Database record streams may layer simulator objects and properties over `Resource::IRecord` streams, with database-specific class-object records.

These require decompilation, captured files, or an original-process trace.

## Next actions

1. Open the committed `SporeApp.exe` Ghidra project read-only and decompile `0x006A2F60`, `0x006A1540`, `0x00692880`, `0x00693DD0`, `0x00B3D440`, and the persistence `LoadGame` implementation.
2. Capture and decode one original `.prop` and one `.spo`, recording field offsets and version gates.
3. Identify concrete serializer database and COM serializer implementations from vtable candidates and callers.
4. Keep current clean-room DBPF/GMDL/RW4/WorldObject behavior separate from original persistence claims until oracle evidence exists.

## Bottom line

The original architecture clearly connects `ResourceKey`/`Database`/`IRecord` streams with simulator serializer databases, class/object serialization, property lists, and game persistence. The exact persisted wire formats and runtime call order remain unproven. This partition supports evidence planning and architecture comparison, not an original save-game implementation.
