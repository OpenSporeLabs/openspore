# Track 11 — Anonymous Space Records (Conditional Resolution)

**Conflict:** `CONFLICT-ANONYMOUS-SPACE-RECORDS`  
**Status:** partial static resolution; architecture impact conditional; no runtime or implementation.

## Verdict

`0x00e39ab0` is a side-effecting builder for two **independent keyed entries** under one table owner:

- primary: key `0x0c`, **27 consecutive 32-bit slots** (`0x1b` slots, `0x6c` bytes), returned to the caller;
- sidecar: key `0x06`, **24 consecutive 32-bit slots** (`0x18` slots, `0x60` bytes), independently inserted and not returned;
- allocation anchor: `FUN_0067de90 -> DAT_015fd910`;
- construction: two separate `FUN_007ec160` plus `FUN_007eb820` operations;
- observed consumers: key-0x0c space-state keyed-table iteration and numeric dispatch, including `0x00e3a270`, `0x00e3d9e0`, `0x00e3f970`, and `0x00e39de0`;
- key `0x06`: producer-coupled sidecar semantics only; no direct consumer identity is established;
- release: table-owned raw storage released through `0x007eb950` / `0x007eb9e0`; a conditional generic App/Telemetry encoder can write and remove a selected key.

The entries are not a view, alias, or shared payload. They are a common producer family with coupled sidecar semantics, not an established `cCommEvent`, `StandardMessage`, `UTFWin::Message`, `AnimationMessage`, `cEditorAnimEvent`, or command/protocol carrier. External object-reference lifetime and runtime execution remain unknown. The conditional telemetry edge is not game persistence, resource serialization, network protocol, or a read-back ABI.

**Classification:** `unknown` under the four-value taxonomy (`required_for_semantics`, `runtime_compatibility_only`, `replaceable_infrastructure`, `unknown`). This is the single normalized campaign classification.

## Nine adversarial steps

| Step | Result |
|---|---|
| 1. Allocation/anchor | Supported: `DAT_015fd910` and the keyed table are the direct owner; key `0x0c` and key `0x06` are separate entries. |
| 2. Producer-coupled sidecar | Supported: sibling builders `0x00e394f0`, `0x00e39710`, `0x00e398e0`, `0x00e3c7c0` repeat the `0x0c/27 + 0x06/24` independent-entry pattern. |
| 3. cCommEvent variant | Rejected as established: cCommEvent is a 0xa0 serializable/refcounted object with two vtables; both entries are raw table storage. Same-caller co-production is not payload identity. |
| 4. App message | Rejected as established: no `IMessageManager`, `MessageSend/Post`, `AddEntry`, or `ProcessQueue` edge. `0x00884100` `ProcessQueue` separately walks 0x18-byte queue records. |
| 5. UTFWin/animation | Rejected as established: no `Window::SendMsg`, `IWinProc`, `AnimationMessage`, or `cEditorAnimEvent` constructor/dispatch edge. |
| 6. Command/protocol | Not established: no command grammar, `CommandLine`, pdtk, `Resource::IRecord`, `IStream`, or game-protocol codec edge. The positive byte-writing path is conditional App/Telemetry only. |
| 7. Construction→consumer | Performed statically for key `0x0c`; no direct key-`0x06` reader was found. Exact runtime instance order remains unknown. |
| 8. Ownership/release/serialization | The owner/table owns raw nodes and buffers only. External object-reference lifetime and runtime execution remain unknown. Conditional App/Telemetry encoding is not game persistence. |
| 9. Smallest separator/architecture | Performed at the table level: `0x00e39ab0 -> key-0x0c consumers -> 0x007eb950/0x007eb9e0`; key `0x06` remains producer-coupled with unresolved consumer identity. |

## Field boundaries

### Primary 27-slot record

| Offset | Count | Observed content |
|---:|---:|---|
| `0x00` | 1 | opaque object/event discriminator |
| `0x04` | 1 | explicit zero |
| `0x08` | 1 | `FUN_00b316c0()/1000` timestamp-like value |
| `0x0c` | 3 | supplied/derived position tuple |
| `0x18` | 3 | second supplied/derived position or cell-ID tuple |
| `0x24` | 2 | object `+0x84` IDs |
| `0x2c` | 1 | optional lookup-derived value |
| `0x30` | 1 | lookup-derived slot or `0x053DBCF2` (`87,932,146`) missing-lookup value |
| `0x34` | 3 | caller-supplied tuple |
| `0x40`–`0x54` | 6 | not written by this builder; zero-filled growth slots |
| `0x58` | 3 | caller-supplied tuple |
| `0x64`, `0x68` | 2 | caller-supplied scalars |

### Sidecar key `0x06` record (24 independent slots)

| Offset | Count | Observed content |
|---:|---:|---|
| `0x00` | 1 | opaque object/event discriminator |
| `0x04` | 1 | mode/derived scalar |
| `0x08` | 1 | timestamp-like value |
| `0x0c`–`0x18` | 4 | two lookup-derived 2-word tuples |
| `0x1c`–`0x20` | 2 | object `+0x84` IDs |
| `0x24` | 1 | optional lookup-derived value |
| `0x28` | 1 | slot value or `0x053DBCF2` (`87,932,146`) missing-lookup value |
| `0x2c`–`0x48` | 8 | not written by this builder; zero-filled growth slots |
| `0x4c` | 1 | not written by this builder; zero-filled growth slot |
| `0x50`–`0x58` | 3 | caller-supplied tuple |
| `0x5c` | 1 | caller-supplied scalar |

The key-`0x06` entry is an independent table value, not a view or pointer projection of the key-`0x0c` entry. The raw field boundaries above do not promote any slot to a named semantic field.

## Family/ownership/serialization matrix

| Family | Carrier/owner | Serialization | Relation to space pair |
|---|---|---|---|
| Anonymous keyed entries | key `0x0c` 27-slot primary and key `0x06` 24-slot independent sidecar in `DAT_015fd910` | conditional generic App/Telemetry dump; no game-persistence or read-back ABI | independent physical entries with producer-coupled sidecar semantics; key-`0x06` consumer unresolved |
| `cCommEvent` | 0xa0 serializable/refcounted cCommManager object | `ISimulatorSerializable`; codec unresolved | co-produced in some space callers; no payload identity |
| `StandardMessage` / `IMessageManager` | 0x40 message object; `0x00884100` `ProcessQueue` handles 0x18 queue records | runtime queue | separate; no manager edge |
| `UTFWin::Message` | Window WinProc/IWinProc dispatch | transient UI value | separate; no Window edge |
| `AnimationMessage` / `cEditorAnimEvent` | 0x18 animation value; 0x30 refcounted editor event | runtime animation/editor record | separate; no animation edge |
| Command/protocol records | parser/resource/command owner unresolved | not established | no direct edge; telemetry bytes are not protocol bytes |

## Serialization finding

A positive edge is conditional and generic: when the keyed table exceeds its count threshold, `FUN_007ec160 -> FUN_007ebce0 -> FUN_007ebba0 -> FUN_0093ab10/FUN_0093aa70 -> FUN_007eb600` can write the selected key's raw 4-byte slots to an `App/Telemetry` `MemoryStream`, byte-swapping 32-bit values, then remove the selected key. The owner telemetry flag defaults to zero and no read-back path was found. This is not game persistence, Resource IO, network protocol, or a read-back ABI.

## Conditional architecture conclusion

1. **Event transport:** model separate key-`0x0c` state dispatch and key-`0x06` sidecar storage. The key-`0x0c` consumer family is supported; no key-`0x06` consumer identity is established.
2. **Resource IO:** object IDs may resolve downstream, but no `ResourceKey`, `IRecord`, `IStream`, or resource-manager edge is established. External object-reference lifetime is unknown.
3. **Asset/geometry:** positions and object references may feed presentation or space logic, but neither entry is an asset/geometry record.
4. **Cell content/presentation:** Cell lifecycle functions share the teardown neighborhood, while the table owns only raw storage. Use a downstream adapter; do not reinterpret either entry as `cCellGame`, GFX, UI, or Cell content records.
5. **Persistence:** conditional App/Telemetry encoding exists for selected keys, but game persistence, resource serialization, network protocol, and read-back semantics are not established.
6. **Decision rule:** merge either entry with another family only after matching a direct consumer/owner/serialization edge—not from shared callers or generic “event” terminology.

## Minimum safe semantics

- Preserve two independent opaque keyed entries: key `0x0c` with 27 primary slots and key `0x06` with 24 sidecar slots.
- Preserve producer-side association only; do not model key `0x06` as a view or independently dispatched event without new evidence.
- Freeze only table-owned raw storage. External object-reference lifetime and runtime execution remain unknown.
- Preserve raw discriminators, timestamp-like values, position/ID tuples, optional lookup values, and `0x053DBCF2` (`87,932,146`).
- Do not name unknown slots, add a vtable, add message parameters, or add record-local refcounting.
- Do not route through `IMessageManager` by default.
- Represent conditional App/Telemetry output as a generic container side effect, not game persistence, resource serialization, network protocol, or a read-back ABI.
- Add explicit adapters for App, UTFWin, animation, cCommEvent, Resource IO, Cell, and presentation if a modern interface needs them.

## Freeze / defer

### Freeze

- `FUN_0067de90` returns `DAT_015fd910`.
- `0x00e39ab0` inserts key `0x0c`/27 and key `0x06`/24 as independent raw table values; it returns only the key-`0x0c` handle.
- Key `0x0c` has the observed space-state/raw-slot/numeric-dispatch consumer family; no direct key-`0x06` consumer was found.
- The shared builder inputs establish producer-coupled sidecar semantics, not a view, alias, or independently proven event.
- The owner/table owns raw nodes and slot buffers; external object-reference lifetime and runtime execution are unknown.
- Generic container helpers release the values; conditional App/Telemetry encoding can write and remove a selected key.
- Neither entry is an established cCommEvent, App, UTFWin, animation, or protocol record.
- The missing-lookup raw value is `0x053DBCF2` (`87,932,146`), not `-10`.

### Defer

- Key-`0x06` consumer identity, runtime role, and any indirect consumer.
- External object-reference lifetime and runtime execution of both entries.
- Exact owner/class, unknown slot names/types, and zero-filled gaps.
- Telemetry read-back or external compatibility contract.
- Runtime producer/consumer/release ordering and dispatch priority.
- Any game-persistence, Resource IO, geometry, Cell-content, GFX, UI, command/protocol, network, or indirect codec bridge.
- Any relationship to cCommEvent beyond same-call-site co-occurrence.

## Caller-list drift

The current Ghidra query returns 16 distinct direct callers and 23 direct xref rows for `0x00e39ab0`. The older dossier lists a different 16-caller snapshot, including `0x00e36210..0x00e3a720` entries and omitting several current `0x0102..0x0105` callers. This is snapshot/export and function-boundary drift, not evidence of different producer families. The current direct-caller list is retained as the fresh static census; historical named contexts remain historical context only, and the lists are not merged.

## Blockers and limitations

- No narrow original-process trace was available; no runtime claim is made.
- Decompiler stack/calling-convention errors make the exact keyed teardown argument uncertain.
- Direct-negative evidence cannot exclude indirect ownership.
- Historical artifacts were read-only; no `SPORE/` directory or `knowledgegraph/spore.db` was accessed.
- Ghidra was queried read-only against explicit `SporeApp.exe`; no mutation or implementation occurred.

## Sources

- Ghidra: `0x00e39ab0`, `0x0067de90`, `DAT_015fd910`, `0x007ec160`, `0x007eb820`, `0x007eb950`, `0x007eb9e0`, `0x007ebb60`, `0x00e3c760`.
- Ghidra: `0x00e39420`, `0x00e39450`, `0x00e393e0`, `0x00e39de0`, `0x00e3a270`, `0x00e3d9e0`, `0x00e3f970`, `0x00e3cf60`, `0x00e47930`, `0x00e48fa0`.
- Ghidra contrast: `0x00aeb720`, `0x00aeb160`, `cCommEvent`, `0x00884100` `ProcessQueue`, `0x0098f4d0`, `0x00960250`, `StandardMessage`, `AnimationMessage`, `cEditorAnimEvent`.
- Follow-up: `knowledgegraph/research/architecture-resolution/followup-05-space-pair.json:18-25,35-49,227-257`; `knowledgegraph/research/architecture-resolution/followup-05-space-pair.md:7-20,22-43,45-78,130-174`.
- Historical: `docs/analysis/dossiers/unknown-high/space-event-record-pair.md:1-93`.
- Historical: `knowledgegraph/research/types/07-event-message.md:1-729`.
- Historical: `knowledgegraph/research/conflicts/00-corpus-inventory.json:1055-1086`.
- Historical: `knowledgegraph/research/conflicts/track-f-cross-domain-impact.json:1667-1849`.
- Historical: `knowledgegraph/research/types/08-persistence-serialization.md:99-143,199-220`.
- Historical: `knowledgegraph/research/architecture-resolution/track-08-cell-lifecycle.json:383-464`.
- Machine-readable report: `knowledgegraph/research/architecture-resolution/track-11-space-records-conditional.json`.
