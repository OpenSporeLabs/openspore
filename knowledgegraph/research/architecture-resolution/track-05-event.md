# Track 5 — Message Queue and Event ABI

## Resolution

**Campaign classification: `RESOLVED_SUPPORTED` at the architecture boundary; exact unresolved native/runtime details remain `INSUFFICIENT_EVIDENCE`.**

Program metadata: `SporeApp.exe` 3.1.0.22, language `x86:LE:32:default`, compiler `windows`, image base `0x00400000`.

The universal event ABI hypothesis does **not** survive. A field-wise prefix/base-subobject test—not record size alone—shows:

- `StandardMessage`: MultithreadObject vtable, refcount, parameters.
- `UTFWin::Message`: IWindow source, field_04, event type.
- `AnimationMessage`: numeric message ID, name pointer, creature pointer.
- `cCommEvent`: serializable vtable, IVirtual vtable, refcount, event type.
- Anonymous space pair: opaque discriminator, mode/derived scalar, timestamp-like value.

There is **no shared semantic ABI prefix or base subobject**. Incidental 32-bit pointer/scalar first words are not ABI evidence. Within the App family, the next separator is `IMessageManager::Entry` (**0x14 bytes**, persistent subscription metadata) versus the deferred queue record (**0x18 bytes**, one delivery snapshot).

The App transport is reusable, but payloads and event families are not one ABI. `StandardMessage`, `UTFWin::Message`, `AnimationMessage`/`cEditorAnimEvent`, `tDeferredEvent`, `cCommEvent`, Cell interaction records, and anonymous space records retain separate owners, callback/serialization contracts, and ordering rules. `cCommEvent` is a runtime communication-domain event whose serializable interface crosses into persistence; it is not persistence-only.

## Corrected message-manager view

Several historical SDK labels are interior or stale addresses:

| Historical label | Correct body/vtable anchor | Result |
|---|---|---|
| `AddUnmanagedListener @ 0x00883a90` | `0x008839a0` | Builds a 0x14 Entry and calls `AddEntry`; `0x00883a90` is adjacent code. |
| `AddListener @ 0x00883ad0` | `0x008839e0` | Sets refcounted Entry, optionally AddRefs listener, then registers. |
| `AddHandler @ 0x00883b20` | `0x00883a30` | Registers function/object/priority/refcount metadata. |
| `0x00884100` | `0x00884100..0x008841e9` | **Outer ProcessQueue entry**; bounded loop/timing wrapper calls vtable `+0x38`. |
| `0x008841f0` | `0x008841f0..0x00884258` | **Cleanup/storage walker**; traverses 0x18/0xc0 storage and releases pointers, with no dispatch branches. |
| `0x00884550` | `FUN_00884550` | **Queue record walker**; copies six words and advances the 0x18-stride/0xc0-block cursor. |
| `0x00847f0` | **`0x00884700..0x00884895`** | Historical interior address versus the **second processor** entry at `0x00884700`. |
| `MessageSend @ 0x008854a0` | body around `0x008853e7` | `0x008854a0` is the immediate listener/handler branch, not an entry. |
| `MessagePost @ 0x00885980` | `0x00885890` | `0x00885980` is the enqueue tail. |
| `MessagePostFunction @ 0x00885a20` | `0x00885930` | `0x00885a20` is inside a comparator/helper, not the callback-post body. |

`0x01427920` is the structurally identified concrete `cMessageManager` vtable, not merely a candidate: `0x00884a20` assigns it to `object+0`, `0x00884fb0` reassigns it during teardown, and slot `+0x00` points to the teardown thunk. Slot `+0x34` is outer ProcessQueue `0x00884100`; `+0x38` is second processor `0x00884700`. `0x008841f0` is absent, and `0x00884550` is an internal record walker. The `+0x14` word remains unresolved because Ghidra reports no function at `0x008853b0`.

## Resolved transport semantics

### Registration

`Entry` is:

| Offset | Field |
|---|---|
| `0x00` | listener or function |
| `0x04` | priority |
| `0x08` | refcounted flag |
| `0x0c` | handler |
| `0x10` | object/context |

`AddEntry` (`0x00884c80`) copies it into a 0x1c linked node under the message-ID list. New entries are ordered **priority descending**; equal priority is **newest-first**.

`RemoveEntry` (`0x008845d0`) matches listener or handler plus message ID and optional priority, optionally releases the registration, unlinks one node, and removes an empty list.

### Immediate versus deferred

- **MessageSend:** synchronous registry map/list traversal; no call to queue insertion `0x00885710`. An optional unmanaged listener selects a target; otherwise matching entries are invoked. The `bool HandleMessage` result is not used to stop traversal.
- **MessagePost:** builds the 0x18 record and enqueues a listener target.
- **MessagePostFunction:** builds the same 0x18 record and enqueues a handler/context target.

The queue record is:

| Offset | Field |
|---|---|
| `0x00` | message ID |
| `0x04` | payload |
| `0x08` | listener or zero |
| `0x0c` | integer ordering key |
| `0x10` | handler or zero |
| `0x14` | handler context or zero |

This build's `MessagePost` body also stores an integer that the SDK prototype omits. The body is authoritative for the queue record; the prototype conflict is preserved.

### Ownership and dispatch

With manager option `+0xc4` enabled, deferred post paths:

1. AddRef the payload and target before enqueue.
2. Dispatch after dequeue.
3. Release listener/callback target.
4. Release payload last.

Without `+0xc4`, no cross-enqueue retain is established. `MessageSend` remains an unmanaged/borrowed surface.

`0x00884550` copies one record before callback. The second processor `0x00884700` branches among listener, handler/context, and untargeted MessageSend fallback, ignores listener return, and releases after callback. A callback cannot consume later App deliveries through its return value.

The second processor covers at least the records present when its pass starts. With manager `+0xc3`, it drains until empty, so callback-created posts can extend the same pass. Outer ProcessQueue `0x00884100` applies enable/count/time-like bounds; `0x008841f0` is only cleanup/storage walking.

Registration removal is not queued cancellation: queue records contain target snapshots, and no queued-record removal path is exposed in the examined manager surface.

## Nine-step adversarial result

| Step | Result |
|---|---|
| Semantic prefix/base | Rejected: the first two words have incompatible vtable/refcount/source/ID/discriminator semantics. |
| Entry versus queue | Decisive: 0x14 registration state and 0x18 delivery state are distinct. |
| Immediate/deferred | Resolved: Send traverses now; Post/PostFunction enqueue. |
| Subscriber ABI | Listener bool and void handler/context are distinct targets. |
| Ownership/release | Conditional retained mode is explicit; release follows callback. |
| Consume | Listener bool is ignored; no first-handler-wins behavior. |
| Priority/tie | Immediate descending/newest-first; deferred uses a separate ordering key. |
| Cancel/snapshot | Registry removal differs from queued delivery; snapshot and drain modes are distinct. |
| Family separator | Universal ABI rejected; bounded App transport plus family payloads survives. |

## Family, ownership, and order matrix

| Family | Classification | Owner/ABI | Ordering |
|---|---|---|---|
| App message manager | `transport` | 0x14 Entry, 0x18 queue record, tagged targets | Immediate priority desc/newest-first; deferred key queue |
| `StandardMessage` payloads | `domain` | 0x40 refcounted parameter record | Only when posted through App bus |
| UTFWin | `presentation` | 0x0c base plus UI payload; proc filters | Exact traversal/bubbling unresolved |
| Animation/editor | `presentation` | 0x18 `AnimationMessage`; 0x30 `cEditorAnimEvent` | Final delivery unresolved |
| `tDeferredEvent` | `domain` | 0x1c value in `cCity` vector | Epoch/same-time order unresolved |
| Cell interactions | `domain` | Pooled mode-specific record, released after dispatch | Separate from App queue |
| `cCommEvent` | `domain` | Runtime communication state with a serializable runtime→persistence boundary | Domain/presentation order unresolved |
| Anonymous space pair | `domain` | Two allocated, differently shaped records | Space SCC order unresolved |

No total order is recovered across these families.

## Minimum OpenSpore abstraction

Use:

- `MessageId` plus family-specific `PayloadView`/retained payload.
- `Registration`: target, priority, retained-registration policy.
- `QueuedDelivery`: ID, shared payload, target snapshot, ordering key, enqueue sequence.
- `dispatchNow(id, payload, optional_target)`.
- `post(id, shared_payload, key, target)`.
- `postFunction(id, shared_payload, key, callback, context)`.
- `process(..., drain_mode)`.

Guarantees:

1. Immediate callbacks complete before `dispatchNow` returns.
2. Immediate registrations use descending priority and newest-first equal-priority order.
3. Callback return does not consume later App delivery.
4. Deferred order is explicit and deterministic; do not assume registration priority and queue key are the same.
5. Normal processing covers the initial snapshot; drain mode may include callback-produced posts.
6. No ordering crosses event families.

Queued cancellation is excluded until directly evidenced.

## Freeze

Freeze the negative semantic-prefix/base-subobject result, family-separated architecture, exact processor roles (`0x00884100` outer ProcessQueue, `0x00884550` record walker, `0x008841f0` cleanup/storage walker, `0x00884700` second processor), 0x14/0x18 record split, immediate/deferred split, listener/handler ABI, conditional retain/release, no consume, immediate registration order, snapshot/drain distinction, and absence of a claimed cross-family order.

## Defer

Defer the operation of the concrete vtable's unresolved `+0x14` word (`0x008853b0`), queue-key units/signed-zero behavior, outer processor parameter meanings, thread/reentrancy policy, queued cancellation, runtime callback/release order, and all family-specific unknowns listed in the JSON.

No runtime trace was run because the static producer/processor separator already decides the architecture boundary.

Revision evidence: `followup-01-event-abi.json` and `followup-01-event-abi.md`; full predictions, evidence for/against, independence/repetition analysis, exact decisions, citations, and blockers are in `track-05-event.json`.
