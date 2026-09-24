# Follow-up 06 — Persistence Architecture Observation

**Status:** `PARTIALLY_RESOLVED`  
**Program:** `SporeApp.exe` 3.1.0.22, read-only Ghidra/static-artifact pass  
**Date:** 2026-09-24  
**Runtime:** not executed; no runtime claim is made.

## Firewall

- Explicit target was `SporeApp.exe`.
- No Ghidra mutation, re-analysis, save, or program modification was requested.
- No `SPORE/` filesystem inspection and no `spore.db` access occurred.
- No implementation or historical artifact was edited.
- Existing persistence research was read for context only; it is not counted as independent binary evidence.
- Address/call-shape observations outrank imported SDK names. A class name or a `COM` string is not treated as proof of a complete wire envelope.

## Executive conclusion

The static architecture is now bounded as:

```text
save path / .spo candidate
  -> write database/stream context
    -> cSavedGameHeader class serialization
      -> ClassSerializer class/attribute framing
        -> object identity and attribute callbacks
    -> mode/service object dispatch
    -> CellSaveGame / cCellSerializableData callbacks when applicable
  -> close stream
  -> temp/old/replace boundary
  -> optional stars.db.tmp -> stars.db replacement
  -> marker-based recovery checks
```

The strongest concrete save body is `FUN_00b28ec0`; the strongest concrete load body is `FUN_00b279e0`. They are operation candidates in the persistence subsystem, not confirmed `cGamePersistenceManager` members: the explicit manager vtable instance and this-pointer binding were not recovered.

The exact outer `.spo`/`.prop` envelope, complete COM/database record framing, save-specific CRC/compression, exact object-reference wire table, migration policy, and universal crash atomicity remain unresolved.

## Concrete operation bodies

### Save candidate: `FUN_00b28ec0` (`0x00b28ec0`)

Confirmed binary behavior:

- Takes a save path and a second mode/snapshot argument through the recovered `RET 0x8` boundary.
- Builds a header-shaped object with adjacent values `3` and `0x25`.
- Fills a nine-word local time array, current mode, snapshot state, and a three-word current-planet-like value.
- Builds a `.tmp` path and opens a write stream through the database/stream setup path.
- Serializes the header through `FUN_00b268a0` and the common `ClassSerializer` writer.
- Dispatches a service vtable operation and conditionally serializes Cell mode state.
- Closes the stream before calling replacement helper `FUN_006891f0`.
- Branches to `FUN_00bb4ba0` or `FUN_00bb66f0` for `stars.db` persistence.

Semantic status: **strong operation candidate; manager membership inferred, not confirmed**.

### Load candidate: `FUN_00b279e0` (`0x00b279e0`)

Confirmed binary behavior:

- Calls `FUN_00b275a0` as a preliminary file/header probe.
- Builds a read database/stream context.
- Initializes a header class serializer with descriptor `0x01568b08` and class ID `0x01a80d26`.
- Reads the header, combines read values into a mode/version value, and dispatches service vtable operations.
- Passes the save path to a service operation and conditionally invokes Cell save-state handling for the Cell mode marker.
- Closes the database context after the load path.

`FUN_00b28990` calls this body and changes the current mode marker to the load state. That makes it a concrete load-path candidate, but not proof that it is the manager's vtable `LoadGame` member.

### Header probe candidate: `FUN_00b275a0` (`0x00b275a0`)

The function builds a path, performs a file operation, opens a read database context on its nonzero branch, reads a cSavedGameHeader-like class object through `ClassSerializer`, closes the context, and compares consumed/available state with `0x20`. Its intended operation name is not recovered; it is treated as a header/file probe or validation candidate, not as a named `LoadGame` body.

## cSavedGameHeader

### Construction and class identity

A concrete body at `0x00b274e0` was observed by disassembly:

- Pushes the size `0x68`.
- Passes `SP_Simulator/cSavedGameHeader/COM` (`0x0145fb0c`) to allocation.
- Installs vtable data `0x0145faa8`.
- Initializes a self/container pointer and zeroed header fields.

The vtable data at `0x0145faa8` contains ten slots followed by the UTF-16 class name `cSavedGameHeader`. Relevant slots include `0x00b26800`, `0x00b26840`, `0x00b26860`, and `0x00b26880`.

### Serialization wrappers

The vtable-adjacent bodies at `0x00b26800` and `0x00b26840`:

- pass class ID `0x01a80d26`;
- pass descriptor/table `0x01568ac8` to `FUN_00692f90`;
- call `FUN_00692900` for write or `FUN_00693e10` for read.

Separate bodies at `0x00b268a0` and `0x00b268e0` use descriptor/table `0x01568b08` with the same class ID and the same writer/reader pair. These are concrete callback-serialized header paths, not raw 0x68-byte file blocks.

The primary save body materializes version values `3` and `0x25`; the secondary `stars.db` writer materializes packed `0x250003`. The field labels and complete emission order are not fully recovered.

## Outer framing: `.spo`, `.prop`, database, COM, CRC

| Layer | Confirmed | Still unknown |
|---|---|---|
| `.spo` | `.spo`, `*.spo`, and `snapshot.spo` strings; save path construction; temp/replace path; recovery enumeration | First bytes, record boundary, whether the file is a direct stream or wrapper |
| `.prop` | `.prop` filename templates and property-style path generation in other binary code | No direct `.prop` write/read link from the recovered `.spo` body; relationship to save stream unknown |
| Database | `FUN_00693d60`/`FUN_00693cd0` construct write/read contexts; `FUN_00693aa0`/`FUN_006939b0` open through stream callbacks; `FUN_00693900` closes/releases | Concrete database record header, index layout, compression, checksum |
| COM | `SP_Simulator/cSavedGameHeader/COM` and `SP_Simulator/CellSaveGame/COM` are class-name metadata passed to allocation | No standalone COM byte header or complete class table recovered |
| CRC | `header crc mismatch` and `CRC error` are referenced by generic compression/deflate code at `0x00868e90` and `0x008732d0` | No save-specific CRC placement, algorithm, or coverage; those functions are not in the recovered save/load path |

The `COM` observations are therefore evidence for class metadata/type identity, not evidence of a complete outer COM envelope.

## ClassSerializer and object references

`FUN_00692880` initializes a class serializer:

- stores a descriptor/table pointer and class ID;
- builds up to `0x80` attribute entries;
- uses a `0x14`-byte entry stride.

`FUN_00692900` confirms write-side callback framing:

- emits framing words;
- iterates attributes;
- invokes each attribute callback;
- records per-attribute success/size state;
- performs a final status operation.

`FUN_00693e10` confirms read-side identity/framing:

- consumes framing words;
- checks stored class identity/count;
- resolves attribute IDs through `FUN_00e0e9f0`;
- invokes read callbacks;
- rejects mismatch or callback failure.

`FUN_00695140` performs a stable identity lookup, allocates a `0x74`-byte association/object record when absent, and stores it in manager-owned vectors. `FUN_00695b40` initializes serializer state and dispatches resolved attributes. This supports an ID-mediated, deferred object-association architecture.

Not recovered: exact object-table record size/order, global versus local ID scope, cycles, duplicate IDs, missing IDs, or whether every Cell field uses this path.

## Cell save object and serializer vtable

The 0xEC object is constructed by `FUN_00e61550` and by a separate concrete factory body at `0x00e61a50`.

Confirmed vtable facts:

- allocation size: `0xec`;
- primary vtable data: `0x01485598`;
- secondary reference-count vtable: `0x014188c0`;
- `0x00e61a50` passes `SP_Simulator/CellSaveGame/COM` to allocation;
- vtable slots include write `0x00e51300` and read `0x00e51370`.

`FUN_00e51300` and `FUN_00e51370` both pass class ID `0x01a80d26` and table/descriptor `0x015a7e38` to common `ClassSerializer` write/read operations. A nearby body at `0x00e51250` uses `0x015a7d48` and iterates six serializer emissions.

The static image contains zero bytes at `0x015a7e38`; the table is runtime-populated. Therefore the vtable path and callback boundary are confirmed, but exact Cell field IDs, names, offsets, and order are not.

## Transactions, commit, rollback, and recovery

Confirmed primary lifecycle:

1. Construct a save path and `.tmp` path.
2. Open the temporary stream.
3. Write header/class records.
4. Close/release the stream.
5. Call `FUN_006891f0`, which constructs an old path, moves/copies target and temporary paths, and removes the old path.

Confirmed secondary lifecycle:

- `FUN_00bb4ba0` writes `stars.db.tmp`, serializes header/class records, closes, and replaces `stars.db`.
- `FUN_00bb66f0` sets a branch flag and delegates to the same writer.

Confirmed recovery/marker surfaces:

- `old/complete`;
- `old/valid`;
- `dbreadinitiated`;
- `dbreadcompleted`;
- `valid`;
- `*.spo` enumeration;
- related checks for `planetRecords.pkp`, `planetscripts.pld`, `stars.db`, and `GGEUserData.dat`.

Not proven:

- atomic commit across `.spo` and `stars.db`;
- a journal or manifest spanning artifacts;
- rollback after a serializer callback failure;
- crash behavior at each move/remove boundary;
- universal use of the same lifecycle for every `.spo` variant.

The defensible claim is **bounded temp/backup/replacement plus marker-based recovery**, not universal crash atomicity.

## cGamePersistenceManager boundary

The imported `cGamePersistenceManager__vftable` is `0x24` bytes and declares:

- virtual destruction;
- `HandleMessage`;
- `AddRef`;
- `Release`;
- `LoadGame` at `+0x10`;
- three later opaque slots.

`cGamePersistenceManager::Get` at `0x00b3d440` is a two-instruction stub returning `DAT_0167eb34`. `DAT_0167eb34` is zero in the static image and has only the Get read xref in this focused pass.

This confirms an imported manager type and a declared load slot, but not a concrete manager instance or the binding of `FUN_00b279e0`/`FUN_00b28ec0` to named manager members. The report intentionally preserves that distinction.

## Hypotheses and adversarial evidence

### H01 — `.spo` is a class/attribute stream, not a raw header struct

- **Prediction:** write/load paths open a database context and call `ClassSerializer`; a raw 0x68 block would not explain callback descriptors.
- **For:** `0x00b28ec0`, `0x00b279e0`, `0x00b26800`, `0x00b26840`, `0x00692900`, `0x00693e10`.
- **Against:** no actual `.spo` bytes or complete database record header.
- **Status:** supported architecture with outer framing unresolved.

### H02 — cSavedGameHeader is a logical class object

- **Prediction:** 0x68 allocation, vtable, class ID, descriptor callbacks, version materialization.
- **For:** `0x00b274e0`, `0x0145faa8`, `0x00b26800`, `0x00b26840`, `0x00b28ec0`.
- **Against:** runtime descriptor contents and complete field order unavailable.
- **Status:** supported as ClassSerializer-backed header.

### H03 — `COM` names are metadata, not an outer binary marker

- **Prediction:** names are passed to allocation/registration and class IDs/tables are passed separately.
- **For:** `SP_Simulator/cSavedGameHeader/COM`, `SP_Simulator/CellSaveGame/COM`, separate `ClassSerializer` class ID arguments.
- **Against:** full class registration and possible outer COM record not recovered.
- **Status:** type metadata confirmed; envelope unresolved.

### H04 — references are stable IDs resolved after object creation

- **Prediction:** identity lookup, vector association, attribute ID resolution before callbacks.
- **For:** `0x00695140`, `0x00695b40`, `0x00695770`, `0x00693e10`.
- **Against:** pointer-table bytes, cycle rules, and ID scope unknown.
- **Status:** supported control flow, incomplete wire model.

### H05 — commit is bounded replacement, not universal atomicity

- **Prediction:** temp path, close, old path, target/temp move; separate stars db replacement.
- **For:** `0x00b28ec0`, `0x006891f0`, `0x00bb4ba0`.
- **Against:** no cross-file manifest/journal/crash trace.
- **Status:** supported bounded replacement only.

### H06 — recovery markers are a bounded compatibility/recovery protocol

- **Prediction:** old/complete, old/valid, dbread markers, and `.spo` enumeration are consulted.
- **For:** `0x00b289e0`, `0x00b28070`, `0x00b282e0`, `0x00b28750`.
- **Against:** marker ordering and crash semantics unresolved.
- **Status:** supported recovery surface.

### H07 — CRC strings are generic compression, not proven save framing

- **Prediction:** CRC strings sit in compression state machines rather than the save path.
- **For:** `0x00868e90`, `0x008732d0`; no recovered call edge from `0x00b28ec0`/`0x00b279e0`.
- **Against:** a higher-level wrapper could still add an unseen checksum.
- **Status:** save CRC not confirmed.

### H08 — Cell save object has a concrete serializer vtable

- **Prediction:** 0xEC allocation, stable vtable pair, write/read wrappers, common ClassSerializer.
- **For:** `0x00e61550`, `0x00e61a50`, `0x01485598`, `0x00e51300`, `0x00e51370`.
- **Against:** runtime field descriptor table unavailable.
- **Status:** supported vtable/codec boundary.

### H09 — save/load bodies are persistence operations

- **Prediction:** save constructs/writes/replaces; load reads/validates and dispatches restoration; wrappers call them.
- **For:** `0x00b28ec0`, `0x00b279e0`, `0x00b28990`, `0x00b294c0`.
- **Against:** explicit manager vtable/this binding absent.
- **Status:** strong operation candidates, manager membership unconfirmed.

### H10 — manager vtable recovery could settle ownership

- **Prediction:** a manager vtable data reference binds the load slot and related persistence methods.
- **For:** imported `cGamePersistenceManager__vftable` declares `LoadGame` at `+0x10`.
- **Against:** static manager global is zero; no concrete vtable instance recovered.
- **Status:** open binding question.

## Smallest observations that could force major redesign

1. **One `.spo` byte prefix and first record boundary:** could replace the current stream-first model with an explicit outer-envelope parser.
2. **One cGamePersistenceManager vtable instance or direct LoadGame slot call:** could separate service orchestration from the current save/load operation bodies.
3. **Runtime contents of `0x01568ac8`, `0x01568b08`, and `0x015a7e38`:** could expand the fixed DTO model into a versioned schema registry with migration branches.
4. **One failure path from callback failure to cleanup/replacement:** could require journal/manifest and staged validation if replacement precedes a complete success check.
5. **One object table containing forward, backward, or cyclic IDs:** could force a graph/object-table redesign if raw addresses or non-ID links appear.
6. **A call edge from save/load into CRC or compression:** would add a separate checksum/compression layer to the framing design.
7. **The commit order/status of all related artifacts:** could force a multi-file transaction protocol if independent replacement is confirmed.

## Deliberately deferred

- Exact `.spo` and `.prop` byte reconstruction.
- Concrete cGamePersistenceManager member binding.
- Full header/Cell field emission order and migration matrix.
- Object-reference wire table and cycle behavior.
- Save-specific CRC, compression, or encryption.
- Universal crash atomicity and journal recovery.
- Any runtime reachability or round-trip claim.

## Key citations

- Primary bodies: `0x00b28ec0`, `0x00b279e0`, `0x00b275a0`, `0x00b274e0`.
- Header wrappers: `0x00b26800`, `0x00b26840`, `0x00b268a0`, `0x00b268e0`.
- Serializer: `0x00692880`, `0x00692900`, `0x00693e10`, `0x00e0e9f0`, `0x00695140`, `0x00695b40`, `0x00695770`.
- Stream/database: `0x00693d60`, `0x00693cd0`, `0x00693aa0`, `0x006939b0`, `0x00693900`.
- Replacement/recovery: `0x006891f0`, `0x00b289e0`, `0x00b28070`, `0x00b282e0`, `0x00b28750`, `0x00bb4ba0`.
- Cell: `0x00e61550`, `0x00e61a50`, `0x01485598`, `0x014188c0`, `0x00e51300`, `0x00e51370`, `0x00e51250`.
- Historical context only: `knowledgegraph/research/architecture-resolution/track-04-persistence.{json,md}`, `knowledgegraph/research/data-model/09-save-load-persistence.json`, `knowledgegraph/research/data-model/17-persistence-synthesis.json`.
