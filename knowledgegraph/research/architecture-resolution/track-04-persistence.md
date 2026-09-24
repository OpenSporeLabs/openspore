# Track 4 — CONFLICT-PROPERTY-PERSISTENCE-CODEC

**Status:** `PARTIALLY_RESOLVED`  
**Campaign classification:** `profile/save persistent`  
**Allowed taxonomy:** `static asset/template` · `profile/save persistent` · `runtime transient` · `unknown`  
**Binary:** `SporeApp.exe` 3.1.0.22, read-only Ghidra program  
**Scope:** Property/PropertyList codec, ClassSerializer, ISimulatorSerializable, cCellSerializableData, cGamePersistenceManager, save headers/envelopes, transactions, references, versioning, migration, atomicity, nesting, and mode handoff.

## Resolution

The minimum persistence architecture is statically bounded:

```text
versioned saved-game header
  -> database/record stream
    -> ClassSerializer class/attribute envelope
      -> nested ISimulatorSerializable objects and stable references
        -> PropertyList local entries and typed Property values
```

The exact outer `.spo`/`.prop` envelope, complete object-reference table, all Property payloads, migration matrix, field survival, and universal crash atomicity remain unresolved.

Follow-up 06 confirms `FUN_00B28EC0` as the strongest save candidate and `FUN_00B279E0` as the strongest load candidate, with `0x00B275A0` as a header/file probe candidate. They use the database/stream and ClassSerializer spine, but membership in a named `cGamePersistenceManager` vtable is **not confirmed**. `.spo`/path and temp/recovery surfaces are confirmed; first bytes and record boundaries are not. `.prop` is name/path evidence in this pass, with no direct link from the recovered `.spo` body. `COM` strings are class metadata, not a confirmed byte envelope. Save-specific CRC/compression is not confirmed.

## Adversarial findings

1. **Authority firewall:** direct binary access/call shape outranks SDK names. No Ghidra mutation, runtime execution, `SPORE/`, or `spore.db` access occurred.
2. **Address separator:** `0x00692880 == 0x006928C0` is one setup/constructor body; `0x00693DD0 == 0x00693DE0` is one teardown body. Actual ClassSerializer Write/Read are `0x00692900` and `0x00693E10`.
3. **Layout versus meaning:** direct `+0x10/+0x12` Property accesses and a `0x18` map stride confirm a 20-byte runtime Property carrier. The imported 4-byte Property is a conflicting tail/metadata view, not a complete entry layout.
4. **Symmetry:** PropertyList Write/Read agree on signed count, uint32 ID, and typed value; Property writer/reader agree on type/flags and array count/size; ClassSerializer reader validates class/attribute identity.
5. **Envelope:** cSavedGameHeader (`0x68`) and cCellSerializableData (`0xec`) are not proven raw struct records. Their concrete methods construct ClassSerializer state and dispatch attributes.
6. **References:** PropertyList parent data is a three-word manager lookup, not recursive parent-pointer serialization. ClassSerializer resolves IDs before callbacks. Cell mode handoff is an in-memory copy/re-adoption, not a disk write.
7. **Versions:** header major/minor fields and serializer version surfaces exist; a save path materializes a value consistent with major `3`, minor `0x25`. Migration/downgrade policy is not recovered.
8. **Atomicity and recovery:** codec failures short-circuit without rollback. Selected paths write temp files, close, and use `.old`/replacement; recovery probes `old/complete`, `old/valid`, `dbreadinitiated`, `dbreadcompleted`, and `valid`. This is bounded replacement plus marker-based recovery, not universal crash atomicity.
9. **Architecture/runtime separation:** static evidence closes the minimum interfaces. Runtime is required to validate atomicity/failure behavior, migration defaults, field survival, and automatic mode persistence. Wire-byte-only questions (outer prefix, record boundary, compression/checksum wrapper) can instead be narrowed by a read-only artifact or concrete parser call edge; they are not automatically runtime questions.

## Confirmed save/load candidates and framing limits

- `FUN_00B28EC0` is the strongest concrete save candidate: it materializes a header-shaped object with values `3` and `0x25`, opens a temporary database/stream, serializes the header, optionally dispatches Cell state, closes, replaces, and can branch to `stars.db` writing.
- `FUN_00B279E0` is the strongest concrete load candidate: it probes/read-validates a header, uses a read database/stream and ClassSerializer, dispatches restoration operations, and closes.
- `FUN_00B275A0` is a header/file probe or validation candidate, not a named `LoadGame` body.
- `FUN_00B28990` and `FUN_00B294C0` are adjacent mode/save wrappers, but no concrete `cGamePersistenceManager` vtable instance binds these candidates to named manager members.
- `.spo`, `*.spo`, `snapshot.spo`, temp/old/replacement, and recovery marker surfaces are confirmed. First bytes, record boundaries, and whether the file is a direct stream or wrapper remain unknown.
- `.prop` is filename/path evidence in this pass only; no direct `.prop` write/read link from the recovered `.spo` body is established.
- `SP_Simulator/.../COM` strings are allocation/class metadata. They do not prove a standalone COM byte envelope.
- CRC/compression strings belong to generic routines not observed in the recovered save/load path; save-specific CRC/compression remains unconfirmed.

## Layout versus semantics

| Subject | Binary certainty | Semantic certainty | Classification |
|---|---|---|---|
| `App::Property` | 0x14 runtime carrier; flags `+0x10`, type `+0x12`; map stride `0x18` | Type tags/flags supported; all payload branches bounded | `unknown` |
| `App::PropertyList` | Local map, parent pointer, counter; signed stream count | Local transfer supported; parent wire order and recursive persistence open | `unknown` |
| `ClassSerializer` | `0xA14`, 128 attributes, counts, class ID, object/attribute pointers | Callback/class/attribute architecture supported; wire table labels open | `runtime transient` |
| `ISimulatorSerializable` | Interface slots and concrete vtable dispatch | Eligibility/nesting supported; subtype coverage open | `unknown` |
| `cSavedGameHeader` | `0x68`; version/map/timestamp/mode/snapshot/planet layout | ClassSerializer-backed versioned header supported | `profile/save persistent` |
| `cGamePersistenceManager` | SDK view `0x4c` is incomplete; direct offsets reach `+0x1b8f2c` and beyond | Runtime service/mode lifecycle supported; concrete save/load body open | `runtime transient` |
| `cCellSerializableData` / `CellSaveGame` | `0xec`, vtable/refcount, `CellSaveGame/COM` factory, held at `cCellGame+0x5190` | Confirmed layout, vtable write/read eligibility, and save-candidate semantics; exact field emission/survival is unconfirmed | `profile/save persistent` (object candidate only) |
| Save transaction | Temp/close/backup/replace visible for selected paths | Replacement supported; full crash/cross-file atomicity open | `runtime transient` |

## Persistent versus transient

**Persistence candidates:** cSavedGameHeader; the confirmed `0xec` `cCellSerializableData`/`CellSaveGame` object as a save candidate; local PropertyList entries; ClassSerializer field values; stable ResourceKey identities; nested serializable objects and their references. The Cell object classification does **not** assert that its SDK-named fields are emitted or survive; field emission is a separate callback/runtime question.

**Transient/runtime-only:** PropertyList parent pointer, operation counter, DirectPropertyList fast slots/temporary Property, ClassSerializer/Attribute descriptors, cGamePersistenceManager service state, cCellGame live pool/query/world/GFX/UI/display state, host pointers, intrusive ownership state, resolved resource pointers, use counters, and temporary transaction paths.

## Runtime requirement split

- **Wire-byte-only, runtime not inherently required:** outer `.spo`/`.prop` prefix and record boundary, database header/index, and compression/checksum wrapper. A read-only original artifact or concrete parser/call edge can narrow these.
- **Field survival, runtime required:** which cCellSerializableData fields are emitted/restored, whether header/Cell fields survive a round trip, and whether mode transitions save automatically. Static callback recovery can narrow the field list, but survival and automatic persistence need a save/load or mode oracle.
- **Atomicity/recovery, runtime required:** callback-failure cleanup, crash behavior at temp/old/replace boundaries, cross-artifact commit order, and manifest/journal recovery. Replacement code alone is insufficient.
- **Migration, runtime required for behavior:** upgrade/downgrade defaults and absent-field behavior need an old-save fixture/load trace; a concrete migration branch can narrow implementation statically.
- **Reference graph, runtime not required for wire architecture:** object-table order, ID scope, and cycles can be narrowed statically; runtime is needed only to validate observed graph behavior.

## Minimum OpenSpore decisions

- Use an explicit record/stream lifecycle: open, good-state check, close, release.
- Represent Property as a 0x14 carrier; encode type and flags before typed payload; use 0x18 local map entries.
- Keep PropertyList local data separate from parent/reference resolution.
- Use a class/attribute registry with field sizes and callbacks; never serialize host pointers.
- Use stable object IDs and deferred reference resolution for nested objects.
- Use cSavedGameHeader as a versioned schema object and cCellSerializableData only as a confirmed `0xec` Cell save-candidate envelope; do not freeze its named fields as an emitted schema until callback/runtime coverage is proven.
- Commit through temp path, close/check, and replacement; add manifest/journal recovery before claiming multi-artifact atomicity.
- Reject or migrate unsupported schema versions explicitly; preserve unknown fields only under a declared policy.

## Freeze

- Property 20-byte layout and PropertyList 24-byte map-entry stride.
- Count/ID/typed-value local PropertyList framing.
- Type/flags order and array count/size branch.
- `0x00692900` / `0x00693E10` as concrete ClassSerializer Write/Read.
- Class/attribute identity and callback architecture.
- cSavedGameHeader as ClassSerializer-backed, not raw `0x68`.
- cCellSerializableData/CellSaveGame `0xec` object, vtable write/read boundary, and cCellGame+0x5190 ownership as save-candidate semantics; not its unproven field emission.
- cGamePersistenceManager as a larger runtime service, not a 0x4c persisted object.
- In-memory Cell handoff as distinct from disk persistence.
- `0x00B28EC0`/`0x00B279E0` as save/load operation seams, with manager membership unconfirmed.
- Temp/close/replace as a bounded transaction pattern.

## Defer

- Outer PROP/.spo record and database/COM envelope; `.prop` relationship to the save stream.
- Unknown Property payloads and default raw-type semantics.
- Three-word parent-reference order and ResourceKey serializer order.
- Attribute IDs, names, exact table layout, pointer tables, cycles, and remapping.
- Concrete cGamePersistenceManager LoadGame/SaveGame vtable binding.
- Complete cCellSerializableData field coverage and cross-stage behavior; the Cell object is only a confirmed save candidate.
- Migration/downgrade/unknown-field policy.
- Universal crash atomicity, journaling, cross-file recovery, and marker semantics.
- Save-specific CRC/compression wrapper.
- Automatic save on mode exit.
- Original runtime ordering of header, class objects, objects, properties, and references.

## Blockers

1. No positive original save/load trace or captured original `.prop`/`.spo` round trip.
2. Concrete database/COM serializer and CRC body not identified.
3. Parent-reference and ResourceKey wire order not semantically closed.
4. Complete class attribute tables and callback bodies not all recovered.
5. Historical runtime evidence did not reach Cell; this limits mode-transition runtime validation only.

## Key citations

- Property: `0x00422EB0`, `0x006A3890`, `0x00693390`, `0x00694440`.
- PropertyList: `0x006A1540`, `0x006A2F60`, `0x0093AA70/0x0093A780` (32-bit), `0x0093A9D0/0x0093A700` (16-bit).
- ClassSerializer: `0x00692880/0x006928C0`, `0x00692900`, `0x00693DD0/0x00693DE0`, `0x00693E10`, `0x00695140`, `0x00695B40`, `0x00695770`.
- Cell state: `0x00E51300`, `0x00E51370`, `0x00E61550`, `0x00E61A50`, `0x00E51250`, `0x00E627A0`, `0x00E63D10`, `0x00E80BA0`.
- Persistence service: `0x00B3D440`, `0x00B0C190`, `0x00B0C520`; save/load candidates `0x00B28EC0`, `0x00B279E0`, header probe `0x00B275A0`.
- Header/save lifecycle: `0x00B26800`, `0x00B26840`, `0x00B268A0`, `0x00B268E0`, `0x00B274E0`, `0x00B28EC0`, `0x00B279E0`, `0x00BB4BA0`, `0x00BB66F0`, `0x00693D60`, `0x00693CD0`, `0x00693900`, `0x006891F0`, `0x00B282E0`, `0x00B28070`, `0x00B28750`, `0x00B289E0`.
- SDK declarations: `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/ISimulatorSerializable.h`, `Serialization.h`, `SerializationTypes.h`, `SubSystem/GamePersistenceManager.h`, `SubSystem/cSavedGameHeader.h`, `App/Property.h`, `App/PropertyList.h`.
- Follow-up evidence: `knowledgegraph/research/architecture-resolution/followup-06-persistence.json`, `knowledgegraph/research/architecture-resolution/followup-06-persistence.md`.
- Historical evidence: `knowledgegraph/research/types/08-persistence-serialization.md`, `knowledgegraph/research/data-model/09-save-load-persistence.json`, `knowledgegraph/research/data-model/10-serialization.json`, `knowledgegraph/research/state-machines/persistence.json`, `knowledgegraph/research/conflicts/track-d-data-serialization.json`.
- Runtime limitation: `docs/devlog/018-s5-cell-runtime-evidence.md`, `docs/analysis/CELL-RUNTIME-OBSERVATION.md`.
