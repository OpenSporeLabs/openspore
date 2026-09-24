# Follow-up 01 — Event ABI and Queue-Surface Resolution

## Scope

Read-only focused Ghidra observation against the explicitly selected `SporeApp.exe` (`x86:LE:32:windows`, image base `0x00400000`). I used decompilation, disassembly, function-boundary queries, xrefs, raw memory, and structure queries only. No Ghidra mutation, save, re-analysis, implementation, `SPORE/` access, `spore.db` access, or historical-artifact edit was performed.

## Result

The four requested addresses are not four interchangeable `ProcessQueue` bodies:

| Address | Exact Ghidra boundary | Static role | Surface decision |
|---|---:|---|---|
| `0x00884100` | `0x00884100..0x008841e9` | Bounded outer processor wrapper; calls `[vtable+0x38]` | **ProcessQueue entry** |
| `0x008841f0` | `0x008841f0..0x00884258` | Walks `0x18`/`0xc0` queue storage and releases four-byte storage/object pointers | **Not the observed dispatch entry; teardown/storage cleanup walker** |
| `0x00884700` | `0x00884700..0x00884895` | Dequeues and dispatches listener, handler/context, or owner-fallback deliveries | **Second queue surface / ProcessQueue2** |
| `0x01427920` | Data, not a function | Candidate concrete `cMessageManager` vtable | `+0x34 -> 0x00884100`; `+0x38 -> 0x00884700`; `0x008841f0` absent |

The actual six-word queue-record dequeue/copy helper is `0x00884550`, which is separate from the mislabeled `0x008841f0` body.

## Address observations

### `0x00884100` — outer ProcessQueue entry

- Ghidra reports function `FUN_00884100`, body `0x00884100..0x008841e9`.
- Direct callers: none. Its data xref is the candidate vtable word at `0x01427954`, slot `+0x34`.
- Direct callees: `FUN_0093a560`, `FUN_0093a480`, and `QueryPerformanceCounter`.
- The body checks the manager byte at `object+0xc2`, computes a queue-count-like expression containing `0x18` division, loops to a supplied bound, and calls the indirect target at `[vtable+0x38]`.
- The raw indirect call at `0x00884199` reaches the candidate table's `+0x38` word, `0x00884700`.
- The stack-supplied parameter meanings and timing policy remain unresolved.

### `0x008841f0` — stale `ProcessQueue` label, not dispatch

- Ghidra function boundary: `0x008841f0..0x00884258`.
- Direct caller: `FUN_00884fb0`; the tail transfer is at `0x00885002`.
- Direct callee: `FUN_00f47380`.
- The body walks the same `0x18` record stride and `0xc0` block range seen in the queue implementation, then releases non-null pointers in the `object+0x14..object+0x24` storage and the object pointer at `object+0x00`.
- It does not copy the six queue-record words, invoke listener/handler callbacks, or branch through the `0x00884700` dispatch paths.
- The Ghidra name `App::cMessageManager::ProcessQueue` is therefore not sufficient evidence that this address is the processor entry. The body and its destructor caller support teardown/storage-cleanup classification.

### `0x00884700` — second queue surface

- Ghidra function boundary: `0x00884700..0x00884895`.
- Direct callers: none. Its data xref is the candidate vtable word at `0x01427958`, slot `+0x38`.
- Callees: `FUN_00884550`, `FUN_009221b0`, and `FUN_00922270`.
- It calls `0x00884550` for a six-word dequeue/copy, increments the counters at `object+0x68` and `object+0x6c`, and dispatches through three observed target shapes: listener, handler/context, or untargeted owner fallback.
- With the `+0xc4` option set, it releases the target and then the payload after callback. The `+0xc3` state participates in the bounded initial-pass versus drain-until-empty loop.
- This is the actual second queue/dispatch surface in the focused path.

## Candidate vtable at `0x01427920`

Raw memory shows 19 consecutive pointer-like words from `0x01427920` through `0x01427968`; strings begin around `0x0142796c`. The selected slots are:

| Slot | Word |
|---:|---:|
| `+0x00` | `0x00885390` |
| `+0x08` | `0x00884ae0` |
| `+0x14` | `0x008853b0` |
| `+0x18` | `0x00885890` |
| `+0x1c` | `0x00885930` |
| `+0x20` | `0x008839e0` |
| `+0x24` | `0x008839a0` |
| `+0x28` | `0x00883a30` |
| `+0x34` | `0x00884100` |
| `+0x38` | `0x00884700` |
| `+0x44` | `0x00884c80` |
| `+0x48` | `0x008845d0` |

Ownership evidence is structural, not RTTI-confirmed: `0x00884a20` writes `0x01427920` to `object+0x00`, and `0x00884fb0` writes the same pointer before its teardown path. The first table word points to `0x00885390`, whose body calls `0x00884fb0`, consistent with a destructor slot.

The `+0x14` word is `0x008853b0`. Current Ghidra reports no function at that address, so it is not repaired or named from this table. This is an explicit unresolved pointer/function-boundary issue.

## Queue-record layout and storage

The deferred record is exactly six 4-byte words, stride `0x18`:

| Offset | Field | Evidence |
|---:|---|---|
| `0x00` | Message ID | Copied by `0x00884550`; passed to listener/handler/owner dispatch. |
| `0x04` | Payload pointer | Set by `0x00885890`/`0x00885930`; passed to callbacks and conditionally released by `0x00884700`. |
| `0x08` | Listener target or zero | Set by the listener producer; selected by the processor's listener branch. |
| `0x0c` | Integer ordering key | Compared by `0x00885710` during insertion; not used as a dispatch target by `0x00884700`. |
| `0x10` | Handler or zero | Set by the function producer; selected by the handler branch. |
| `0x14` | Handler context or zero | Passed to the handler when present. |

`0x00885710` performs the six-word copy and ordered insertion. The walker `0x00884550` advances by `0x18`, and when a range is exhausted it advances a four-byte block cursor, loads the next block, and sets its usable end to `block+0xc0`. The same `0x18`/`0xc0` traversal appears in `0x008841f0`, but that body uses it for cleanup rather than dispatch.

The `+0x0c` word is an observed ordering key for this insertion algorithm. Its native name, units, signed-zero behavior, and relationship to registration priority remain unresolved.

## Common-prefix test

**Result: no common prefix at the semantic/field-wise ABI level.**

| Family | Live size | Prefix observation |
|---|---:|---|
| `StandardMessage` | `0x40` | `+0x00` vtable pointer, `+0x04` refcount, `+0x08` five parameters, `+0x30` ID. |
| `UTFWin::Message` | `0x0c` | Ghidra type search returns `/Spore/UTFWin/Message` at 12 bytes; read-only field context identifies a window source, a field at `+0x04`, and event type at `+0x08`, followed by type-specific anonymous payload data. |
| `AnimationMessage` | `0x18` | `+0x00` message ID, `+0x04` name pointer, `+0x08` creature pointer. |
| `cCommEvent` | `0xa0` | `+0x00` serializable vtable pointer, `+0x04` virtual vtable pointer, `+0x08` refcount, `+0x0c` event type. |
| Anonymous space pair | `0x6c` / `0x60` | Raw 27-slot and 24-slot arrays beginning with opaque discriminators and timestamp-like values; no vtable/refcount prefix. |

There are incidental 32-bit pointer/scalar words at offset zero, but they do not form a common base record. `StandardMessage` and `cCommEvent` have different vtable interfaces and place refcount at different offsets; `UTFWin::Message` uses its first word as a window source; `AnimationMessage` and the anonymous space records begin with different scalar/discriminator roles.

The App manager's `0x18` record is a generic transport snapshot. It can carry a payload pointer and message ID, but that does not make these payload families share a base prefix or callback/ownership ABI.

## What this closes

- Exact Ghidra boundaries for `0x00884100`, `0x008841f0`, and `0x00884700`.
- The processor map: outer entry `0x00884100`, dequeue/copy walker `0x00884550`, second dispatch surface `0x00884700`, and cleanup/storage walker `0x008841f0`.
- The candidate vtable ownership of the two live processor entries and the absence of `0x008841f0` from that table.
- The `0x18` six-word queue layout and the observed `+0x0c` insertion-key role.
- The negative common-prefix result across the requested families.
- The separation between generic App transport state and family-specific payload/owner contracts.

## What remains unresolved

- The `+0x14` vtable word `0x008853b0`, which is not a Ghidra function in the current program.
- Exact queue-key units and signed ordering behavior.
- Exact meanings of the outer `0x00884100` parameters, timing policy, thread affinity, and recursion behavior.
- The exact names/roles of all cMessageManager cursor/range fields around the `0x18`/`0xc0` blocks.
- A category-safe live field layout for UTFWin: the generic `get_struct_layout("Message")` resolver selected an unrelated duplicate `Message` type. The live type-path/size lookup is still reliable, while field labels are retained as historical context rather than promoted as a fresh generic-layout result.
- Any indirect family-to-family adapter not present in the focused paths. No such adapter is inferred from shared vocabulary or co-location.

## Citations

- Ghidra: `ghidra://SporeApp.exe@0x00884100` — boundary, queue-count arithmetic, gate, indirect `+0x38` call, timing check.
- Ghidra: `ghidra://SporeApp.exe@0x008841f0` — boundary, `0x18`/`0xc0` walk, pointer releases, destructor caller, no dispatch branches.
- Ghidra: `ghidra://SporeApp.exe@0x00884700` — boundary, dequeue/dispatch, target branches, counters, conditional release, snapshot/drain loop.
- Ghidra: `ghidra://SporeApp.exe@0x00884550` — six-word copy and stride/block transition.
- Ghidra: `ghidra://SporeApp.exe@0x00885710` — six-word insertion and `+0x0c` comparison.
- Ghidra: `ghidra://SporeApp.exe@0x00885890` and `ghidra://SporeApp.exe@0x00885930` — listener and handler/context queue producers.
- Ghidra: `ghidra://SporeApp.exe@0x00884a20`, `ghidra://SporeApp.exe@0x00884fb0`, `ghidra://SporeApp.exe@0x01427920` — vtable assignment, teardown, and candidate table words.
- Ghidra structures: `StandardMessage`, `AnimationMessage`, `cCommEvent`, `UTFWin/Message`, and `App/IMessageManager/Entry`.
- Ghidra: `ghidra://SporeApp.exe@0x00e39ab0`, `0x00e39420`, `0x00e39450`, `0x00e3d9e0`, and `0x00e3a270` — anonymous space allocation, raw slot writes, keyed iteration, and numeric dispatch.
- Read-only artifact: `knowledgegraph/research/architecture-resolution/track-05-event.md:18-29,55-83` — prior address correction, queue layout, and processor context.
- Read-only artifact: `knowledgegraph/research/architecture-resolution/track-11-space-records-conditional.md:6-19,35-90` — anonymous space pair construction, ownership, and family separation.
- Read-only artifact: `knowledgegraph/research/types/07-event-message.md:295-324,428-464,495-534` — UTFWin, animation, cCommEvent, and anonymous-space layout context.
