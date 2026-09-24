# Follow-up 05 — Anonymous Space Pair

**Program:** `SporeApp.exe`  
**Mode:** read-only, explicit-program Ghidra observation  
**Status:** physical entry boundary resolved; 24-slot semantic role remains blocked by one missing key-6 consumer/instance trace.

## Verdict

`0x00e39ab0` creates two **independent keyed entries**, not a pointer view:

| Value | Key | Size | Returned? | Observed consumer |
|---|---:|---:|---|---|
| Primary | `0x0c` | 27 × 4-byte slots (`0x6c`) | Yes | Key-0x0c state enumeration, raw-slot access, numeric dispatch |
| Companion/sidecar | `0x06` | 24 × 4-byte slots (`0x60`) | No | No direct key-0x06 reader found |

The 24-slot value is **producer-coupled** to the 27-slot value: both are created in the same builder from the same discriminator, timestamp, object, position, and scalar sources. It is not established as a separately dispatched event. The precise conclusion is:

> **Independent physical entries with coupled companion/sidecar semantics; not an alias/view, and not an independently proven event.**

The missing-lookup value written by the target is raw `0x053DBCF2` (`87,932,146`), not `-10`.

## Exact construction path

1. `0x0067de90` returns `DAT_015fd910`.
2. `0x0067e0b0` installs the owner pointer into `DAT_015fd910` during owner setup.
3. `0x007ec0a0` constructs the owner and installs its vtables and embedded bucket fields.
4. `0x007ebf40` initializes the owner’s embedded keyed container.
5. `0x00e39ab0` calls `FUN_007ec160(0x0c, 0)` and `FUN_007eb820(0x1b)`, creating/writing the primary value.
6. It calls `FUN_007ec160(0x06, 0)` and `FUN_007eb820(0x18)`, creating/writing the companion value.
7. The function returns only the primary handle. The companion handle is local and is not passed onward.

There is no assignment of the primary payload pointer, primary handle, or key-0x0c node into key `0x06`, and no reverse assignment. The two records therefore cannot be a pointer view.

## Repeated family evidence

The same 0x0c/27 plus 0x06/24 construction pattern appears in:

- `0x00e394f0`
- `0x00e39710`
- `0x00e398e0`
- `0x00e3c7c0`

These builders share the same initializer, timestamp, lookup, and position/object sources. This is strong evidence for a common producer family, but it does not prove that the two values are one logical object or that key `0x06` has a consumer.

## Consumer census

### Key-0x0c state/table consumers

The observed primary consumer family is:

- `0x00e3ea00` / `0x00e3d9e0`: keyed-table iteration and record updates.
- `0x00e3f970`: key-0x0c orchestration and space-state processing.
- `0x00e3b5d0`, `0x00e3b630`: key-0x0c lookup/token checks.
- `0x00e3f2a0`, `0x00e3f7a0`: key-0x0c lookup plus property/object processing.
- `0x00cd6130`: key-0x0c presence/check logic.
- `0x00e3a270`: numeric-token dispatch over raw record slots.
- `0x00e39420`, `0x00e393e0`, `0x00e39de0`: raw triple read/write/update.

These are space-state/keyed-table consumers, not a universal event ABI.

### Downstream consumers

- `0x00e3cf60` reads primary-record IDs, triples, lookup values, and scalars and performs property/resource/UI-space work.
- `0x00e47930` consumes primary-record fields for presentation/property setup.
- `0x00e48fa0` reads slot `0x10` and uses the result for space/UI placement.
- `0x00e3b390` reads slot `0x0d` and drives a UI/animation-adjacent action.

These are downstream consumers of primary state, not evidence that the 27/24 carrier itself is a UI, resource, Cell, or animation record.

### Key-0x06 consumer result

No direct `FUN_007eb100(6)` consumer was found. The callers of `FUN_007eb100` use key `0x0c`; the generic `FUN_00668c80` path receives keys `7`, `8`, `9`, `10`, or `11` from `FUN_00668d90`, not key `6`.

Therefore:

- Key `0x0c` has a demonstrated consumer family.
- Key `0x06` has construction and generic container serialization/lifetime, but no demonstrated semantic consumer.
- The sidecar may be dormant, a compatibility representation, or consumed by an undiscovered indirect path.

## Family hypotheses

### H1: view/alias — rejected

**Prediction:** shared payload/node, one handle, writes aliasing, no independent key.

**Evidence for:** same builder and common input provenance.

**Evidence against:** separate keys, separate value handles, distinct lengths, local-only companion handle, no pointer assignment, and no cross-key read.

### H2: separate event — not established

**Prediction:** returned/dispatched independently, own consumer, own lifetime and release.

**Evidence for:** separate key, value node, and storage.

**Evidence against:** always constructed as a side effect of the key-0x0c builder; not returned; no key-0x06 dispatch, queue insertion, or consumer found.

### H3: independent entry with coupled companion semantics — supported

**Prediction:** separate keys/nodes/sizes; common producer inputs; primary consumers; companion may be dormant; generic owner serialization/release.

**Evidence for:** exact target behavior, four repeated sibling builders, key-0x0c consumer census, and common keyed-container infrastructure.

**Limit:** producer coupling does not prove a semantic view or a separate event.

### H4: cCommEvent/universal event family — rejected as established

`cCommEvent` is a 0xa0 object with two vtable pointers, `mnRefCount`, intrusive pointers, and vectors. `FUN_00aeb160` allocates 0xa0, constructs the object, inserts it into a cCommManager vector, and performs virtual AddRef/Release operations. The target constructs raw 27/24 slot values with no record-local vtable or refcount.

`0x0102d1b0` and `0x0102df20` co-call the target and `j_Sim_cCommManager_CreateSpaceCommEvent`, but no pointer or slot dataflow joins the two objects. This is co-production, not payload identity.

### H5: command/network/resource protocol — not established

No direct `CommandLine`, pdtk, `Resource::IRecord`, network, parser, or protocol-codec edge is present. The first slot and numeric IDs are merely structurally compatible with a tagged record; that is insufficient.

## `DAT_015fd910` ownership

The observed owner is the object returned by `FUN_0067de90`, not a raw slot array. Its embedded keyed container owns the value nodes and their slot buffers.

Release boundaries:

- `FUN_007eb950`: frees all bucket nodes and attached value/payload storage.
- `FUN_007eb9e0`: removes a matching key and frees its value nodes.
- `FUN_007ebb60`: wrapper for all-entry clearing or one-key removal.
- `FUN_007ebe70`: owner destructor/clear path.
- `FUN_00e3c760`: explicitly removes the key-0x0c value; no key-0x06-specific teardown was found.

The 27/24 records have no record-local AddRef/Release path. Treat the keyed owner as the storage/lifetime boundary and retain object-ID/scalar slots as opaque data.

## Serialization finding

A positive serialization edge exists, but it is telemetry-specific and conditional.

`FUN_007ec160` checks:

```text
FUN_007eb090() * 0x20 > 0x2800
```

That is a count threshold above 640. When crossed, it calls `FUN_007ebce0` with the current key. The path is:

```text
FUN_007ec160
  -> FUN_007ebce0
  -> FUN_007ebba0
  -> FUN_0093ab10 / FUN_0093aa70
  -> FUN_007eb600
```

`FUN_007ebce0` creates a `MemoryStream` named `App/Telemetry`. `FUN_007ebba0` writes selected-key metadata, an entry identifier, and the raw 4-byte slot array. `FUN_0093aa70` byte-swaps 32-bit values before writing. After serialization, `FUN_007ebba0` removes the selected key with `FUN_007eb9e0`.

`FUN_007eb600` may write `telemetry.dat`, but only when the owner telemetry flag at `owner+0x38` is enabled. `FUN_007ec0a0` initializes that flag to zero.

This establishes an **App/Telemetry encoding edge** for the keyed values, including whichever key is flushed. It does not establish game save persistence, resource serialization, network protocol framing, or a read-back ABI.

## Protocol boundary

No command/protocol relation is established. The positive byte-writing path is the conditional `App/Telemetry` MemoryStream path; the observed consumers are keyed state enumeration, raw-slot access, numeric dispatch, and downstream property/presentation work.

A protocol relation would require a direct key-0x06 reader, parser, codec, or protocol owner. None is present in the focused static path.

## Smallest remaining blocker

**B1:** There is no direct key-0x06 consumer or runtime instance trace, so the semantic role of the 24-slot sidecar remains unresolved.

The smallest next observation is one trace that records:

1. owner pointer;
2. key `0x0c` and key `0x06` value-node identities;
3. both payload pointers and lengths;
4. any later key lookup/consumer;
5. telemetry or release event.

This blocker **can force semantic redesign** if it reveals a distinct dispatch/protocol path or a runtime alias. It **does not force redesign under current evidence**: the safe minimum is two opaque independent entries with an explicit producer-side association.

## Freeze

- `0x00e39ab0` creates key-0x0c/27-slot and key-0x06/24-slot values.
- The 24-slot value is not a pointer view.
- The 24-slot value is producer-coupled but not proven to be a separate event.
- Key `0x0c` has the observed space-state consumer family.
- `DAT_015fd910` is the observed owner and keyed-container release boundary.
- A conditional `App/Telemetry` serializer exists; no protocol or game-persistence ABI is established.
- The missing-lookup constant is `0x053DBCF2` (`87,932,146`), not `-10`.

## Deferred

- Key-0x06 consumer, runtime order, and exact sidecar role.
- Semantic names/types for raw slots.
- Concrete owner class/name.
- Telemetry read-back or external compatibility contract.
- Any indirect command, resource, network, or persistence bridge.

## Ghidra evidence

`0x00e39ab0`, `0x0067de90`, `0x0067e0b0`, `0x007ec0a0`, `0x007ebf40`, `0x007ec160`, `0x007eb820`, `0x007eb100`, `0x00e39420`, `0x00e39450`, `0x00e393e0`, `0x00e39de0`, `0x00e3a270`, `0x00e3d9e0`, `0x00e3ea00`, `0x00e3f970`, `0x00e3b5d0`, `0x00e3b630`, `0x00e3f2a0`, `0x00e3f7a0`, `0x00e3cf60`, `0x00e47930`, `0x00e48fa0`, `0x00e3b390`, `0x00e394f0`, `0x00e39710`, `0x00e398e0`, `0x00e3c7c0`, `0x007eb950`, `0x007eb9e0`, `0x007ebb60`, `0x007ebe70`, `0x00e3c760`, `0x007ebce0`, `0x007ebba0`, `0x0093aa70`, `0x007eb600`, `cCommEvent`, `0x00aeb160`, `0x00aeb720`, `0x0102d1b0`, `0x0102df20`.

No `SPORE/` traversal, `spore.db` access, implementation, runtime trace, or historical edit was performed.
