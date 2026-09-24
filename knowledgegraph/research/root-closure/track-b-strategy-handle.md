# Track B — Strategy handle / forwarded state value

**Status:** complete with static ambiguity  
**Scope:** `0x00b5b800` (`FUN_00b5b800`), `0x00b3d320`, `0x00a42730`, `0x00b3d350`, `0x00b3d420`  
**Evidence:** static committed artifacts plus read-only disassembly of the pinned `SporeApp.exe`; no Wine/runtime.

## Adjudication

- `FUN_00b5b800` is a no-argument EAX wrapper:
  - calls `FUN_00b3d320` to read global `DAT_0167eaec`;
  - if non-null, moves the value to ECX and tail-jumps to `FUN_00a42730`;
  - `FUN_00a42730` is exactly `mov eax,[ecx+0x20]; ret`;
  - if the global is null, returns `0xffffffff`.
- The return should remain a 32-bit opaque/address-like state value. It is not safe to type as a normal pointer, enum, or current-mode ID.
- The root null sentinel (`0xffffffff`) and the consumer sentinel family (`0x01654c00`–`0x01654c06`) are separate domains. The latter are address-like constants used as scalar branch discriminators, not dereferenced objects in the committed named consumers.
- `+0x20` is a field read, not a vtable load and not an interface call. There is no evidence that it is an object/interface pointer.
- Only the subsystem family is supported: a Simulator shared-state/strategy-state forwarding boundary. No concrete receiver class is proven.
- No allocation, mutation, lock, `AddRef`, or `Release` occurs in the root or forwarding path. The global receiver is borrowed; the returned value carries no ownership transfer.

**Confidence:** mechanics and `+0x20` read **HIGH**; opaque/sentinel value domain **HIGH**; exact receiver class **LOW**; `ISimulatorStrategy` identity **LOW**; borrowed ownership **MEDIUM-HIGH**; mode relationship **MEDIUM**.

## Root contract

| item | result |
|---|---|
| root | `0x00b5b800`, 20 bytes |
| arguments | none |
| return | raw 32-bit value from forwarded receiver `+0x20` |
| null path | `0xffffffff` |
| receiver source | `0x00b3d320` → `DAT_0167eaec` |
| field reader | `0x00a42730` → `[ECX+0x20]` |
| writes / allocation / lock | none / none / none |
| ownership | borrowed read-through; no reference operation |
| Phase-0 action | keep type-open; expose only the opaque forwarding contract |

Evidence: `docs/analysis/simulator-shared-state-interface.md:66-79`, `knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json:945-1018`, `.spore-analysis/ghidra-exports/functions.tsv:20751,23966,24280`, and pinned disassembly at `0x00a42730`, `0x00b3d320`, `0x00b5b800`.

## Forwarding path

```text
0x00b3d320
    └─ DAT_0167eaec
0x00b5b800
    ├─ null ───────────────> 0xffffffff
    └─ non-null ECX ──────> 0x00a42730
                              └─ EAX = DWORD [ECX+0x20]
```

`0x00ad12a0` is decisive corroboration: it directly calls `0x00b3d320` + `0x00a42730`, compares the result with `0x01654c05`, then in the alternate path calls `0x00b5b800` and compares with `0x01654c04`. The two paths set different downstream state bits. This supports “same forwarded field, null-safe wrapper” rather than a separate object factory.

## Consumer metrics

Canonical xref export: `knowledgegraph/triage/xrefs-2540f2ca.tsv`; baseline count: 459 direct callers / 80 gameplay callers.

| metric | value |
|---|---:|
| direct-call edges to `0x00b5b800` | 701 |
| distinct callers | 459 |
| callers with multiple call sites | 124 |
| edges with adjacent EAX compare to `0x01654c00..06` | 373 |
| distinct callers in that sentinel pattern | 251 |
| direct adjacent EAX compare to `0xffffffff` | 1 |
| callers also calling `0x00b3d350` | 64 |
| callers also calling `0x00b3d420` | 2 |
| callers also calling `0x00b3d320` | 17 |
| callers also calling `0x00a42730` | 2 |
| callers also calling `0x00b3d300` | 142 |
| callers also calling `0x00b3d2a0` | 30 |

Sentinel compare distribution across the 701 direct edges:

| immediate | edges |
|---:|---:|
| `0x01654c00` | 14 |
| `0x01654c01` | 45 |
| `0x01654c02` | 60 |
| `0x01654c04` | 66 |
| `0x01654c05` | 187 |
| `0x01654c06` | 1 |

The compare counts are a lower bound from the first instruction after each canonical call edge; they are not an arbitrary caller inventory.

## Compact caller-use matrix

| pattern | representative evidence | result use | object dereference | conclusion |
|---|---|---|---|---|
| Null-owner sentinel | root disassembly; one adjacent `cmp eax,0xffffffff` | `0xffffffff` on absent global | No | Preserve separate null-owner result |
| Address-like state sentinels | 373 edges / 251 callers; `0x01654c00..06` | EAX equality branch | No in named SDK consumers | Dominant scalar/encoded state pattern |
| Direct forwarding plus wrapper | `0x00ad12a0` | Direct `b3d320+a42730` branch vs `b5b800` branch; downstream flag bits | No | `b5b800` is a null-safe wrapper around the forwarded read |
| Creature-state gating | `0x00c099e0`, `0x00d2e4a0`, `0x00d2e580`, `0x00d2e8a0` | Compare `0x01654c01/02/10`; proceed through other roots | No for the b5 result | Consumer domain is creature state, not proof of receiver identity |
| Input/mode co-use | 64 callers co-call `b3d350`; two co-call `b3d420` | Same subsystem routines | Not established by co-call | Shared subsystem path, not aliasing |
| Engine/dispatch bridge | `0x00e02580`, `0x00c1a3c0`, `0x00c07480`, `0x00d130d0`, `0x00bcece0` | Representative dependency bridge callers | Not established | Supports infrastructure role only |

## Selected consumers

### `0x00ad12a0` — strongest forwarding corroboration

Pinned disassembly at `0x00ad1f3e`–`0x00ad1f7f`:

1. `call 0x00b3d320`;
2. `mov ecx,eax`;
3. `call 0x00a42730`;
4. `cmp eax,0x01654c05`;
5. if not equal, call `0x00b5b800` and `cmp eax,0x01654c04`;
6. set different `object+0x5fc` bits.

The forwarded result is a branch value. The object receiving the flag update is obtained through a different receiver path; no ownership relation to the b5 value is shown.

### `0x00c099e0` — `Simulator::cCreatureAnimal::Create`

The committed dependency projection names this function and records direct joins to `cSpeciesManager`, `cGameTimeManager`, `cGameInputManager`, `00b3d300`, and `00b5b800`. Pinned disassembly shows b5 results compared with `0x01654c01`, `0x01654c02`, and `0x01654c10` to select state/event paths. This proves creature initialization consumes the handle; it does not prove the b5 receiver is `cCreatureAnimal`.

Source: `knowledgegraph/research/global-campaign-2026/track-j-dependency-graph.json:750-752,865-867`, `knowledgegraph/research/decomp-gap/sim-core-02.json`, and pinned disassembly at `0x00c09b52`, `0x00c09b6a`, `0x00c09ca2`.

### `0x00d2e4a0`, `0x00d2e580`, `0x00d2e8a0` — committed SDK decompilers

- `cCreatureGameData::SetAbilityMode`: compares b5 result to `0x01654c01`; any later virtual dispatch is on the object returned by `00d37cb0`, not on the b5 result (`.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cCreatureGameData__SetAbilityMode.c:31-35`).
- `cCreatureGameData::AfterGlideFinish`: compares b5 result to `0x01654c10`; the following dereferences use the separate `00b1fdb0` result (`.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cCreatureGameData__AfterGlideFinish.c:41-63`).
- `cCreatureGameData::AddEvolutionPoints`: compares b5 result to `0x01654c10` before calling `00d38840`, `00b3d300`, and `00b1fdb0` (`.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cCreatureGameData__AddEvolutionPoints.c:30-39`).

These are high-confidence scalar-gate uses, not object-return uses.

## Mode, strategy, and input comparison

### `cGameInputManager::Get` — `0x00b3d350`

- SDK return: `cGameInputManager*`.
- Body: `return DAT_0167eaf8;`.
- Relevant SDK fields: `mLastGameMode +0x18`, `mCurrentGameMode +0x1c`, `field_14 +0x20`, then input maps/regions/mouse fields.
- This is a separate global (`0x0167eaf8`) from b5’s receiver (`0x0167eaec`).
- Accessor ownership is not established; the raw return is treated as borrowed.

Source: `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cGameInputManager__Get.c:8-12`, `.spore-analysis/ghidra-exports/spore_sdk.xml:15956-16012`, baseline `docs/analysis/simulator-shared-state-interface.md:81-94`.

### `cGameModeManager::Get` — `0x00b3d420`

- SDK return: `cGameModeManager*`.
- Body: `return DAT_0167eb2c;`.
- Relevant fields: `mLastGameMode +0x0c`, `mCurrentGameMode +0x10`, `mActiveModeID +0x20`.
- This is another distinct global, not `DAT_0167eaec`.
- `+0x20` here is a scalar active-mode field, not evidence that b5’s `+0x20` is the same class or an interface pointer.

Source: `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cGameModeManager__Get.c:8-12`, `.spore-analysis/ghidra-exports/spore_sdk.xml:12979-13001`.

### `ISimulatorStrategy` interface

The SDK confirms a 20-slot strategy interface: vtable `+0x20` is the `GetCurrentGameMode` method slot. That is a vtable offset, not an object field offset. The SDK `cStrategy` object stores `mCurrentGameMode` at `+0x10`; `cGameModeManager` stores current mode at `+0x10` and active mode ID at `+0x20`.

Therefore:

- mode/strategy infrastructure is real and adjacent;
- b5’s result is not proven to be `ISimulatorStrategy*`;
- b5’s `+0x20` is not proven to be a current-mode field;
- the b5 consumer evidence favors an opaque state/sentinel value.

Source: `.spore-analysis/ghidra-exports/spore_sdk.xml:1967-2085`, `.spore-analysis/ghidra-exports/structs_fields.tsv:3935-3954`.

## Ownership and lifetime

- `0x00b3d320` reads a raw global pointer; no allocation or reference operation.
- `0x00a42730` reads one raw field; no reference operation.
- `0x00b5b800` does not mutate, retain, release, or lock.
- The returned value is a borrowed view of receiver state. It is valid only while the global receiver and its field remain live; the receiver’s allocator/owner/teardown are unknown.
- SDK manager types expose refcounted vtables, but no b5 consumer evidence transfers or manages a reference to the b5 result.
- `0xffffffff` must not be normalized to ordinary pointer null. The `0x01654c00..06` values are a separate encoded-state/sentinel domain.

## Contradictions and unresolved points

1. **Address-looking sentinels vs scalar contract:** the values look like addresses, but the helper only loads a field and the named consumers do not dereference. Resolution: opaque 32-bit state/handle, not a normal object pointer.
2. **Strategy hypothesis:** SDK strategy interfaces exist, but the b5 receiver global is not a named manager global and `0x00a42730` is a plain field load. Resolution: low-confidence family hypothesis only.
3. **Ghidra vtable label:** triage labels `0x00a42730` with a Resource vtable family. The pinned body is a generic `[ECX+0x20]` reader; detector metadata is not a concrete class identity.
4. **Mode co-use:** 64 input-root co-callers and two mode-root co-callers show shared subsystem routines, not direct aliasing or dataflow.
5. **Unresolved receiver:** exact class, owner, initialization/teardown, and physical type of the `+0x20` storage remain unknown.
6. **Uninspected callers:** the matrix captures the dominant sentinel and selected high-information patterns; it does not claim a semantic classification for every raw xref caller.

## Re-construction boundary

Expose only a no-argument opaque 32-bit forwarding contract with a `0xffffffff` null result and a documented `forwarded_object+0x20` read. Do not implement a concrete class, interface pointer, mode ID, object dereference, or reference-management behavior.

## Sources

- `docs/analysis/simulator-shared-state-interface.md`
- `knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json`
- `docs/analysis/dossiers/unknown-high/sim-object-lookup-strategy.md`
- `docs/analysis/dossiers/unknown-high/sim-object-lookup-strategy.json`
- `knowledgegraph/triage/xrefs-2540f2ca.tsv`
- `knowledgegraph/triage/xrefs-2540f2ca.summary.json`
- `.spore-analysis/ghidra-exports/functions.tsv`
- `.spore-analysis/ghidra-exports/sdk_functions.tsv`
- `.spore-analysis/ghidra-exports/spore_sdk.xml`
- `.spore-analysis/ghidra-exports/structs_fields.tsv`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cGameInputManager__Get.c`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cGameModeManager__Get.c`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cCreatureGameData__SetAbilityMode.c`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cCreatureGameData__AfterGlideFinish.c`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cCreatureGameData__AddEvolutionPoints.c`
- `knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl`
- `knowledgegraph/research/decomp-gap/sim-core-02.json`
- `knowledgegraph/research/global-campaign-2026/track-j-dependency-graph.json`
- Read-only disassembly of the pinned `SPORE/SporeBin/SporeApp.exe`
