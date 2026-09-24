# Blocker B — Primary investigation: forwarded state at `0x00b5b800`

**Program:** `SporeApp.exe` 3.1.0.22, `x86:LE:32:windows`, image base `0x00400000`
**Target:** `0x00b5b800`, receiver slot `DAT_0167eaec`, pointee field `receiver+0x20`
**Mode:** read-only Ghidra plus read-only repository/SDK evidence
**Scope boundary:** no source-code, `SPORE/`, Ghidra project, or canonical SQLite database changes. This is an isolated report only; it does not rewrite prior artifacts or the aggregate report.

## Executive verdict

The forwarding mechanics remain certain:

```text
0x00b5b800
  -> 0x00b3d320: MOV EAX,[0x0167eaec]
  -> null receiver: 0xffffffff
  -> non-null receiver: ECX = EAX; JMP 0x00a42730
  -> 0x00a42730: MOV EAX,[ECX+0x20]; RET
```

The new direct evidence materially narrows the physical interpretation:

1. The receiver object is **strongly `Simulator::cGameModeManager`-compatible**. The derived constructor at `0x00b1d870` installs the concrete vtable at `0x0145d7f0`, initializes `+0x20` and `+0x24` to `-1`, clears `+0x28` and `+0x29`, and matches the SDK `cGameModeManager` derived layout. The base constructor call at `0x00b5b960` matches `cStrategy`.
2. `receiver+0x20` is a **32-bit active game-mode ID**, not a forwarded interface pointer. The direct writer at `0x00b5f040` stores the normalized current mode ID there. The special writer at `0x00b28990` stores `0x01654c08`, which the SDK names `kLoadGameMode`.
3. `0xffffffff` is the SDK-compatible **no-manager/invalid-mode result**. The SDK `GetGameModeID()` source returns `-1` when `cGameModeManager::Get()` is null, and `FUN_00b5c9d0` explicitly normalizes invalid IDs, including `0x01654c03`, to `-1`.
4. The **global slot publication/aliasing chain remains unresolved**. `DAT_0167eaec` still has only one static read xref, at `0x00b3d320`, and no direct static writer. The object constructor and field writers do not prove which runtime path publishes the alternate slot or whether it is the same object as the canonical `DAT_0167eb2c` slot.

**Current classification:** the safe returned-value contract is `uint32_t current_game_mode_id`, with `0xffffffff` for absent/invalid mode. The receiver is a borrowed `cGameModeManager*`-compatible object. Do not expose the receiver as an owned pointer, and do not merge `DAT_0167eaec` with the canonical `DAT_0167eb2c` slot without a runtime/equality observation.

**Confidence:** mechanics **high**; receiver class/layout **high**; active-mode-ID interpretation **high**; exact global publication, aliasing, and runtime first-writer order **medium-low/unresolved**.

## Direct target evidence

### Root and helpers

| Address | Instruction/decompilation | Result |
|---|---|---|
| `0x00b5b800-0x00b5b813` | `CALL 0x00b3d320`; `TEST EAX,EAX`; `JZ`; `MOV ECX,EAX`; `JMP 0x00a42730`; `OR EAX,0xffffffff`; `RET` | Null-safe two-level read. |
| `0x00b3d320-0x00b3d325` | `MOV EAX,[0x0167eaec]; RET` | Reads one raw 32-bit global word. No callee. |
| `0x00a42730-0x00a42733` | `MOV EAX,dword ptr [ECX+0x20]; RET` | Reads one raw 32-bit pointee field. No callee. |

The target has two direct callees: `0x00b3d320` and `0x00a42730`. The root performs no allocation, mutation, lock, AddRef, Release, or ownership transfer.

### Xref and caller coverage

The full Ghidra xref/caller queries returned:

| Query | Result |
|---|---:|
| Direct call xrefs to `0x00b5b800` | 843 |
| Function caller records for `0x00b5b800` | 459 |
| Direct callees of `0x00b5b800` | 2 |
| Xrefs to `0x00b3d320` | 88 reference edges |
| Xrefs to `0x00a42730` | 59 reference edges, including data references |

The 843 direct call sites were investigated as a whole in the existing bounded caller census. The result is dominated by equality/range/branch/copy/index use; the prior census observed no strict returned-value dereference, indirect call, or indirect jump. Seven sites were bounded-ambiguous. The newly recovered writers do not change that caller-use result: the returned value is a mode discriminator, not a downstream object.

Decision-relevant direct consumers include `0x00b3d2c0`, `0x00b5e9a0`, `0x00b63510`, `0x00b5f040`, `0x00b5dbb0`, `0x00b783b0`, `0x00c099e0`, `0x00d2e4a0`, `0x00d2e580`, and `0x00d2e8a0`.

## Receiver and constructor evidence

### Global storage

`DAT_0167eaec` is a four-byte, writable `.data` slot:

- Segment: `.data`, `0x0150c000..0x0171e763`, writable.
- Ghidra type: `undefined4`; size: 4 bytes; alignment: 4.
- Loaded image value: zero at the target and in the queried surrounding range `0x0167eae0..0x0167eaff`.
- `get_xrefs_to(0x0167eaec)`: one `READ` at `0x00b3d320`.
- `get_xrefs_from(0x0167eaec)`: none.
- Full instruction address-operand scan: one absolute read, no absolute write.
- Exact little-endian address-byte search: one hit at `0x00b3d321`, belonging to the read instruction at `0x00b3d320`.

The zero value is a loaded-image fact, not a runtime null observation. The direct-static negative remains valid for the **global slot**; it must not be misreported as “the receiver is never published” or “the pointee has no writers.”

### Matching derived constructor

`0x00b1d870` is a direct constructor-shaped body:

- `0x00b1d873`: calls `0x00b5b960`, the base `cStrategy` constructor.
- `0x00b1d87f`: installs vtable `0x0145d7f0`.
- `0x00b1d885`: installs the secondary vtable/base pointer at `+0x04`.
- `0x00b1d88c`: installs the secondary vtable at `+0x1c`.
- `0x00b1d896`: stores `0xffffffff` at `receiver+0x20`.
- `0x00b1d899`: stores `0xffffffff` at `receiver+0x24`.
- `0x00b1d89e-0x00b1d8a1`: clears `+0x28` and `+0x29`.
- `0x00b1d8a4` onward: clears the remaining derived fields through `+0x98`.

The SDK declares the same derived object as `Simulator::cGameModeManager`, size `0x9C`, inheriting `cStrategy`, with:

- `mActiveModeID` at `+0x20`.
- `field_24` at `+0x24`, documented as a previous-mode candidate.
- `field_28` and `field_29` at `+0x28/+0x29`.
- `cStrategy` base fields at `+0x0c/+0x10/+0x14/+0x18`.

The vtable and constructor are independent binary evidence; the SDK layout is corroboration, not a substitute for the instructions.

### Allocation and destruction paths

The constructor is reached from a real allocation helper:

```text
0x00b60d80
  -> 0x00f473a0(..., 0x9c, ...)
  -> 0x00b1d870 at 0x00b61d80
  -> stores the new object in an owner field and registers it in an owner vector
```

`0x00b60d80` is a large initialization/registration body. It uses a `0x9c` allocation and the derived constructor at `0x00b61d80`; its exact owner/global-publication role is not yet bound to `DAT_0167eaec`.

The matching teardown path is present:

- `0x00b1d970` restores the base/derived vtable state, releases the derived pointer/vector entries, restores `+0x1c`, and calls the base destructor tail.
- `0x00b1dc40` wraps `0x00b1d970` and optionally frees the object.

This establishes an object construction/destruction family, but not the static publication of the alternate global slot.

## `+0x20` writers and mode transitions

### Initialization writer

The first recovered field writer is the constructor:

```text
0x00b1d870: MOV [ESI+0x20],0xffffffff
```

This is the initialization value for the `cGameModeManager::mActiveModeID` field. It is not evidence that `DAT_0167eaec` itself is written at this address; it is a write to the allocated pointee.

### Special load-mode writer

`0x00b28990` is a direct mode-state writer:

```text
0x00b2899f: CALL 0x00b5b800       ; capture the current forwarded mode
0x00b289a6: CALL 0x00b3d320       ; obtain the alternate manager receiver
0x00b289ac: MOV [EAX+0x20],0x1654c08
0x00b289b3: CALL 0x00b3d320
0x00b289ba: CALL 0x00b1e410
```

`0x01654c08` is `GameModeIDs::kLoadGameMode` in the SDK. The function is called from `0x00b335d0` at `0x00b3377a` when the requested/destination mode is the load mode. It is the earliest recovered non-initializing mode-value store by address, but address order is not runtime order; the actual first non-sentinel write remains an event-order question.

### Normal transition writer

`0x00b5f040` is the normal transition writer:

```text
0x00b5f040: PUSH EBX, EBP, ESI, EDI
0x00b5f046: CALL 0x00b3d320
0x00b5f04b: MOV EBP,[ESP+0x14]    ; first stack argument
0x00b5f04f: MOV ESI,[ESP+0x18]    ; second stack argument
0x00b5f053: MOV [EAX+0x24],EBP
0x00b5f056: MOV [EAX+0x20],ESI
0x00b5f059: MOV byte ptr [EAX+0x28],0
0x00b5f05d: MOV byte ptr [0x01686af0],0
```

The caller is `0x00b63510` at `0x00b63664`, in the mode-exit-announcement branch for message ID `0x0212d3e7`. `0x00b63510` reads payload words at `+0x08` and `+0x10`, normalizes both through `0x00b5c9d0`, suppresses equal normalized IDs, and passes the two normalized values to `0x00b5f040`.

The SDK `OnModeExitMessage` contract identifies the two payload words as current mode ID and previous mode ID. The raw call/store order is:

```text
payload/current  -> +0x20 (mActiveModeID)
payload/previous -> +0x24
```

The function also resets `+0x28` and a separate global flag, then performs transition/listener work. It is a state mutation and mode-routing boundary, not an ownership transfer of the returned mode ID.

The corresponding enter-side body is `0x00b5dbb0`, called by `0x00b63510` for the other mode-announcement path. It performs transition effects and mode-name dispatch but does not invalidate the `+0x20` active-mode conclusion.

## Sentinel and ID normalization

`0x00b5c9d0` is a mode-ID normalizer, not a pointer recognizer. Its exact behavior is:

| Input | Output/meaning |
|---|---|
| `0x01654c00` | `kGameCell`, preserved |
| `0x01654c01` | `kGameCreature`, preserved |
| `0x01654c02` | `kGameTribe`, preserved |
| `0x01654c03` | invalid, returns `0xffffffff` |
| `0x01654c04` | `kGameCiv`, preserved |
| `0x01654c05` | `kGameSpace`, preserved |
| `0x01654c06` | `kGameEditMode`, preserved |
| `0x01654c07` | invalid, returns `0xffffffff` |
| `0x01654c08` | `kLoadGameMode`, preserved |
| `0x01654c10` | `kScenarioMode`, preserved |
| `0x00dbdba1` | `kEditorMode`, preserved |
| `0x02ccd1d2` | `kGGEMode`, preserved |
| `0x8916f92d` | maps to `0x01654c11` |
| invalid/unsupported values | `0xffffffff` |

The SDK `CommonIDs.h` defines the same ID family. This resolves the prior “C03 unknown” question in a narrower way: `0x01654c03` is not a valid active mode in this normalizer and is explicitly collapsed to `-1`; it is not evidence for a missing enum member. Other values outside the requested `C00..C06` set, including `C08`, `C10`, editor, GGE, and cinematics, are also valid or special in the surrounding bridge.

The root's own null path is consistent with the SDK helper:

```cpp
uint32_t GetGameModeID() {
    auto mgr = cGameModeManager::Get();
    return mgr == nullptr ? -1 : mgr->GetActiveModeID();
}
```

The exact `-1` result therefore means no usable active mode/invalid normalized mode, not a dereferenceable pointer sentinel.

## Ownership, lifetime, and aliasing

### Ownership of the returned value

The returned `uint32_t` is copied by value. The root path does not retain the manager, AddRef it, Release it, allocate memory, lock, or transfer ownership. The `cGameModeManager` object is a borrowed service object for the duration of the read.

The mode ID itself is not a reference. A consumer can compare it, branch on it, pass it, or store it as a value; it does not own the manager or any mode object.

### Manager lifetime

The constructor/destructor pair establishes a refcounted/managed object family, but no static path connects the global slot `DAT_0167eaec` to an AddRef/Release or clear operation. The direct global xref surface remains one read only. Therefore:

- pointee construction: supported by `0x00b1d870` and its `0x00b60d80` allocation path;
- pointee destruction: supported by `0x00b1d970`/`0x00b1dc40`;
- global slot publication: unresolved;
- global slot unpublication/teardown: unresolved;
- semantic freshness of the alternate slot: unresolved.

### Alternate versus canonical manager slot

`0x00b3d420` is Ghidra/SDK-named `Simulator::cGameModeManager::Get` and returns the distinct slot `DAT_0167eb2c`. The target helper `0x00b3d320` returns `DAT_0167eaec`. They are distinct four-byte words, and no direct equality operation or common direct writer was found in this investigation.

The target's constructor/field evidence establishes `cGameModeManager` compatibility for the object reached through `DAT_0167eaec`; it does not establish pointer equality with the canonical `DAT_0167eb2c` object. The correct architecture boundary is two manager access ports until runtime equality or a common publication/clear chain is observed.

## Competing hypotheses

| ID | Hypothesis | Predictions | Evidence for | Contradictions/limits | Status |
|---|---|---|---|---|---|
| H1 | **Normal receiver object plus scalar mode field** | Constructor, vtable, `+0x20` store, mode-ID normalization, and no returned-value dereference | `0x00b1d870` layout/vtable; `0x00b5f040`; `0x00b28990`; `0x00b5c9d0`; caller scalar use | Global slot publication and canonical-slot alias remain unresolved | **Supported/high** |
| H2 | **Current-object state** | `+0x20` is a current active mode ID and changes at mode events | `cGameModeManager::mActiveModeID` at `+0x20`; load-mode and transition writers; `GetGameModeID()` source | The current object is a manager; the returned value is not an object pointer | **Supported for field meaning; not a pointer hypothesis** |
| H3 | **Handle or pointer** | Returned value is dereferenced, virtually called, retained, or used as a receiver | Receiver is mechanically a pointer and the result is copied as a word | Mode IDs are exact enum values; `0x00b5c9d0` normalizes them; no returned-value pointer use | **Rejected as the returned-value interpretation** |
| H4 | **Tagged value** | Values are tagged/encoded and need a tag decoder or opaque tagged type | Address-like constants and historical conservatism | Direct enum constants, direct stores, direct normalizer, and SDK field contract explain the values without a tag layer | **Low confidence / unnecessary** |
| H5 | **Forwarded interface** | `+0x20` is an interface/vtable pointer and callers retain/dispatch it | The receiver itself is object-based and has a vtable | `+0x20` is a data field written with mode IDs; no returned-value interface dispatch; `0x00a42730` is a plain load | **Rejected for the returned field** |
| H6 | **First writer is b28990** | The first non-initializing store is always the load-mode writer | It is the earliest direct mode-value store and writes `kLoadGameMode` | `b5f040` is another direct writer; event scheduling and receiver availability determine runtime order | **Earliest static candidate, not proven temporal first** |
| H7 | **Lifecycle/publication is already closed** | A direct writer, constructor, clear, and teardown bind `DAT_0167eaec` | `cGameModeManager` constructor/destructor exists | Global slot has one read xref and no direct writer; only the pointee lifecycle is connected | **Rejected for the global slot; unresolved** |

## Smallest decisive observation

Static evidence now identifies the field and writers, but cannot decide global-slot publication or alternate/canonical identity. The smallest decisive runtime observation is one naturally reachable mode transition, preferably entering or leaving the load mode, with read-only watches on:

1. `DAT_0167eaec` and the return from `0x00b3d320`;
2. `0x00b1d870`, `0x00b1d970`, and the allocation at `0x00b61d80`;
3. `[manager+0x20]`, `[manager+0x24]`, `[manager+0x28]`, and `[manager+0x29]`;
4. `0x00b63510`, `0x00b5c9d0`, `0x00b5f040`, `0x00b28990`, and `0x00b335d0`;
5. the canonical return from `0x00b3d420` and the alternate return from `0x00b3d320` at the same timestamp.

Record only pointer identity, mode IDs, message ID, payload words, normalized values, and object lifecycle events. Do not write the slot, inject messages, manufacture a receiver, or patch the binary.

This single trace decides:

- whether `DAT_0167eaec` is published during subsystem initialization;
- whether the alternate and canonical slots are equal during the transition;
- whether the first non-`-1` field writer is `0x00b28990` or `0x00b5f040`;
- whether the alternate slot is cleared/replaced on teardown;
- whether `-1` is observed as absent manager, invalid mode, or both.

If no natural transition is reachable, retain the static result and leave the global-publication/aliasing question open.

## Cross-checks against existing research

### Prior forwarded-state reports

The prior reports correctly froze the forwarding mechanics and correctly found no direct writer to the **global slot** `DAT_0167eaec`:

- `knowledgegraph/research/architecture-resolution/followup-02-forwarded-state.md:18-43`
- `knowledgegraph/research/architecture-resolution/followup-02-forwarded-state.json:59-111`
- `knowledgegraph/research/architecture-resolution/track-06-forwarded-state.json:139-183`

Their “no `+0x20` writer” wording is too broad for the current evidence. The new binary pass found direct stores to the pointee field at `0x00b289ac` and `0x00b5f056`, plus constructor initialization at `0x00b1d896`. The old negative remains valid only for direct absolute writes to `DAT_0167eaec` and for the bounded global-slot xref search.

The prior caller census remains useful and is not contradicted: the returned value is used as a scalar mode discriminator, while the pointer-backed receiver is a separate object.

### Semantic blueprint and architecture resolution

The semantic blueprint's interim boundary was:

- `knowledgegraph/research/semantic-blueprint.json:61-92`

It called the result a borrowed opaque `uint32` pending first-writer/type resolution. This report narrows that boundary: the return is now statically supported as an active mode ID, while publication, aliasing, and lifecycle remain open. The blueprint itself is not modified by this report.

The architecture register classified Blocker B as architecture-changing at:

- `knowledgegraph/research/architecture-resolution.json:204-210`

That classification remains appropriate for global publication, aliasing, teardown, and exact compatibility. The mode-ID representation itself is no longer an unresolved pointer-versus-handle choice.

### SDK and modding evidence

The SDK evidence used here is local read-only evidence from Spore-ModAPI:

- `Spore/CommonIDs.h:82-98`: `GameModeIDs` values, including `kGameCell`, `kGameCreature`, `kGameTribe`, `kGameCiv`, `kGameSpace`, `kGameEditMode`, `kLoadGameMode`, `kScenarioMode`, editor, and GGE IDs.
- `Spore/Simulator/SubSystem/cStrategy.h:30-54`: `ISimulatorStrategy` interface and mode-related virtuals.
- `Spore/Simulator/SubSystem/cStrategy.h:56-90`: `cStrategy` fields at `+0x0c/+0x10/+0x14/+0x18`.
- `Spore/Simulator/SubSystem/GameModeManager.h:37-80`: `cGameModeManager` inheritance and `mActiveModeID` at `+0x20`.
- `SourceCode/Simulator/GameModeManager.cpp:26-33`: `GetGameModeID()` returns `mActiveModeID`, or `-1` for a null manager.
- `Spore/App/IGameModeManager.h:42-83`: mode-exit/enter message IDs and current/previous payload contract.
- `Documentation/GameModes.md:35-41`: modding-facing statement that one mode is active and mode changes use IDs.

These are SDK/modding contracts, not original runtime observations. They are strong corroboration because the binary writes and normalizes the exact same values.

### State and event reports

The state/event corpus is consistent with this result:

- `docs/analysis/gameplay-state-machines.md:81-120`: App mode lifecycle and separate Simulator strategy pending/committed state.
- `docs/analysis/event-message-map.md:46-50`: mode-exit/enter announcement order, with queue timing unresolved.
- `docs/analysis/event-message-map.md:122-126`: `0x00b63510` reads announcement payload words and selects mode commit behavior.

The mode ID returned by `0x00b5b800` is therefore a routing/discriminator value in the mode event system, not a forwarded interface. The event transport's queue timing remains separate and unresolved.

### Serialization and data reports

No serialization evidence connects `DAT_0167eaec` or `receiver+0x20` to a save field. The relevant reports keep runtime mode state separate from persistence candidates:

- `docs/analysis/serialization-model.md:184-205`: serializer architecture is separate from runtime ownership and does not prove field coverage.
- `docs/analysis/serialization-model.md:222-251`: `cCellSerializableData` has a separate `mGameMode` candidate at `+0x0c`; this is not the `cGameModeManager+0x20` field.
- `docs/analysis/serialization-model.md:294-323`: runtime services and persistent/save candidates are separate classes.
- `docs/analysis/gameplay-data-model.md:294-355`: mode and runtime state are not assumed to survive mode transitions merely because they are present in memory.

Therefore this report does not authorize serializing the active mode manager field, does not claim mode exit autosave, and does not merge the active mode ID with `cSavedGameHeader.mGameMode` or `cCellSerializableData.mGameMode`.

## Final confidence and remaining ambiguity

- **Root mechanics:** very high.
- **`+0x20` is a scalar active game-mode ID:** high.
- **Receiver is `cGameModeManager`-compatible:** high, based on the derived constructor, vtable, field layout, and mode writers.
- **`-1` is the absent/invalid mode result:** high, based on the root and SDK source.
- **First field initializer:** `0x00b1d870`, high.
- **First non-sentinel static mode writer candidate:** `0x00b28990`, medium; `0x00b5f040` is a second direct writer and runtime order is unresolved.
- **Global `DAT_0167eaec` publication, ownership, and teardown:** unresolved.
- **Alias/equality with canonical `DAT_0167eb2c`:** unresolved.
- **Original runtime timing and queue behavior:** unresolved.

The smallest safe architecture contract is therefore:

```text
read_active_game_mode_id() -> uint32_t
  no usable manager or invalid normalized mode: 0xffffffff
  otherwise: cGameModeManager-compatible receiver->mActiveModeID
```

Keep the receiver borrowed and keep the alternate and canonical manager slots separate until a runtime publisher/equality observation closes that boundary.
