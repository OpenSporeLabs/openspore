# Track C — `FUN_00b1fdb0` opaque owner closure

Status: **complete with surviving static ambiguities**. No runtime, no `SPORE/` access, and no source, historical artifact, or Phase-0 interface change.

## Decision

`FUN_00b1fdb0` returns a **raw 32-bit object pointer**, not an integer ID, tagged value, or union. The strongest committed interpretation is:

```text
cGameNounManager::mpAvatar
  +0x54: eastl::intrusive_ptr<cCreatureAnimal>
       |
       +-- FUN_00b1fdb0 returns the contained raw address
           (consumers use it as cCreatureBase / cCreatureAnimal)
```

The accessor is probably a current-avatar getter. Its receiver is ECX and the exact formal calling-convention label remains decompiler-dependent: the held record labels the decompiler signature `__fastcall`, while the four-byte, no-explicit-stack-argument body is thiscall-like. The root itself only reads `receiver+0x54`; it allocates, locks, mutates, AddRef, or Release nothing.

The old `gamemode-state-player-id` interpretation is rejected. The apparent mixed scalar/pointer use reconciles as ordinary pointer equality/null checking plus direct object dereferences.

## Evidence identity

- Binary SHA-256: `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`.
- Analysis snapshot: `f0e310e0`; canonical xrefs: `2540f2ca`.
- Root export: four bytes at `0x00b1fdb0` (`.spore-analysis/ghidra-exports/functions.tsv:23579`).
- Committed root decompiler record: `return *(param_1 + 0x54)` (`docs/analysis/dossiers/unknown-high/gamemode-state-player-id.json:23-33`).
- Held characterization: `knowledgegraph/research/decomp-gap/hold-infrastructure.json:17279-17289`.
- Canonical xref hash: `89e74b8a03c4db38a1927f8c95c38db507bf99cb8a11de6b6eb6a9484d8c79cb` (`knowledgegraph/research/00-baseline-inventory.json:8940-89442`).
- SDK XML hash: `5d894677c1835082da0392e8b794f3c93a0251733898c3c5b81cf7945f458f09` (`knowledgegraph/research/00-baseline-inventory.json:8540-85442`).

## Owner match

The SDK exports one exact, behaviorally coherent owner field at the root's receiver offset:

| owner candidate | offset | field | width | evidence |
|---|---:|---|---:|---|
| `cGameNounManager` | `+0x54` | `mpAvatar` | 4 | `eastl::intrusive_ptr<Simulator::cCreatureAnimal>` (`.spore-analysis/ghidra-exports/structs_fields.tsv:10610`) |

Corroboration:

1. `cGameNounManager::Get` returns singleton global `DAT_0167eb60` (`.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cGameNounManager__Get.c:8-12`).
2. The SDK declares `cGameNounManager::SetAvatar(cCreatureAnimal*)` and `EnsurePlayer` (`spore_sdk.xml:23404-23421`), consistent with a manager-owned avatar.
3. The root's returned object independently matches `cCreatureBase` at multiple exact offsets and vtable slots, as detailed below.
4. The high-information consumers are current-creature game-data/mode-strategy functions, not player-ID registries.

Limit: the selected persisted decompilers do not preserve the final ECX dataflow at the root call sites. Therefore the `cGameNounManager` receiver identity is a very strong layout/type match, not a directly observed `DAT_0167eb60 -> ECX -> call 00b1fdb0` chain. The result-as-pointer decision itself is high confidence.

## Selected high-information call sites

Only six persisted decompiler bodies are included; xref-only callers are intentionally not enumerated.

### `0x00d2e380` — `GetEvoPointsToNextBrainLevel`

- Root call: `0x00d2e399` (`knowledgegraph/triage/xrefs-2540f2ca.tsv:137558`).
- On `currentLevel == -1`, it calls the root, reads `*(result+0x00)` as a vtable, and calls slot `+0xd8` (`.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cCreatureGameData__GetEvoPointsToNextBrainLevel.c:13-17`).
- SDK maps `cCreatureBase__vftable+0xd8` to `GetCurrentBrainLevel` (`spore_sdk.xml:18827-18835`; `structs_fields.tsv:6205`).

This is decisive pointer and polymorphic-object evidence. It also corrects `+0xd8`: it is a vtable slot, not a result-object field.

### `0x00d2e4a0` — `SetAbilityMode`

- Root call: `0x00d2e4c1` (`xrefs-2540f2ca.tsv:137564`).
- It dereferences the result's vtable slot `+0x84` and reads byte `result+0xb5c` (`Simulator__cCreatureGameData__SetAbilityMode.c:17-23`).
- SDK maps slot `+0x84` to `SetCreatureTarget` and `result+0xb5c` to `cCreatureBase::field_B5C:bool` (`spore_sdk.xml:18812`; `structs_fields.tsv:6184,6416`).

The unrequested `+0xb5c` check is an independent exact-layout corroboration.

### `0x00d2e580` — `AfterGlideFinish`

- Root call: `0x00d2e58b` (`xrefs-2540f2ca.tsv:137579`).
- It reads `result+0xb20` as a pointer, switches on that pointee's `+0x61c`, and later reads `result+0xc0` as another subobject pointer before a virtual call (`Simulator__cCreatureGameData__AfterGlideFinish.c:20-22,46-51`).
- SDK maps `cCreatureBase+0xb20` to `cSpeciesProfile*`, `cCreatureBase+0xc0` to `cLocomotiveObject__vftable*`, and the latter vtable's `+0x2c` to `GetPosition` (`spore_sdk.xml:18865-18867,18997-18999`; `structs_fields.tsv:5143,6242,6406`).

This supplies the strongest direct nested-pointer evidence.

### `0x00d2e720` — `CalculateAvatarNormalizingScale`

- Root call: `0x00d2e751` (`xrefs-2540f2ca.tsv:137585`).
- The root result is discarded. The following `+0x55c` float read is on `iVar2`, which was returned by `FUN_004df420` before the root call (`Simulator__cCreatureGameData__CalculateAvatarNormalizingScale.c:20-25`).
- In the SDK, `cCreatureBase+0x550` is `fixed_vector<int,4>`; `+0x55c` is its final four-byte slot if that other pointer is creature-derived (`structs_fields.tsv:6342`).

This rejects the prior claim that `result+0x55c` is root-result evidence. The exact type of the `FUN_004df420` result remains open.

### `0x00d2e8a0` — `AddEvolutionPoints`

- Root call: `0x00d2e93e` (`xrefs-2540f2ca.tsv:137592`).
- It stores the returned address in `local_18`, passes `&local_18` to `cCreatureModeStrategy::ExecuteAction`, and stores the point amount at `local_18+0x0c` (`Simulator__cCreatureGameData__AddEvolutionPoints.c:33-38`).

This proves that the returned word is usable as an address and becomes the first dword of a target-bearing action record.

### `0x00d39360` — `cCreatureModeStrategy::ExecuteAction`

- Five root calls: `0x00d393cf`, `0x00d39459`, `0x00d394e3`, `0x00d39509`, `0x00d395cc` (`xrefs-2540f2ca.tsv:138483-138487`).
- It compares the root result with `*(int32_t*)recordPointer` (the decompiler variable is `actionID`); related paths also test the result for nonzero and check that the object at `recordPointer+4` reports ObjectTYPE `kCreatureAnimal` (`App__cCreatureModeStrategy__ExecuteAction.c:50-62,75-94,107-145`).
- SDK value `0x18eb45e` is `kCreatureAnimal` (`spore_sdk.xml:10332`).

The scalar-looking sites are raw pointer equality, null, and type checks. They do not use signed/unsigned numeric ID semantics, arithmetic, maps, formatting, or range comparisons.

## Field-offset map

| path | width | decoded meaning | evidence / use |
|---|---:|---|---|
| `owner+0x54` | 4 | probable `cGameNounManager::mpAvatar`, `intrusive_ptr<cCreatureAnimal>` storage | root's sole read |
| `result+0x00` | 4 | `cCreatureBase__vftable*` | virtual dispatch |
| `result+0xc0` | 4 | `cLocomotiveObject__vftable*` / `cLocomotiveObject` subobject pointer | virtual `GetPosition` at `+0x2c` |
| `result` vtable `+0xd8` | 4-byte slot | `GetCurrentBrainLevel` | fallback current brain level; **not a field** |
| `result+0x55c` | not established | prior root association rejected | root result is discarded in the only persisted SDK sample |
| `result+0xb20` | 4 | `cSpeciesProfile*` | dereferenced to `profile+0x61c` |
| `result+0xb20 -> +0x61c` | 4 | unnamed species-profile scalar | exact switch cases 1..5; default zero |
| `result+0xb5c` | 1 | `cCreatureBase::field_B5C:bool` | argument before `SetCreatureTarget` dispatch |

`cSpeciesProfile+0x61c` lies inside the SDK's opaque `char[2584]` prefix (`spore_sdk.xml:16181-16183`), so no SDK name is available. The 1..5 switch supports only "4-byte categorical scalar", not a semantic enum name.

## Scalar, pointer, tag, and union assessment

- **Integer ID:** rejected. The value is repeatedly dereferenced and matches exact pointer/vtable layouts.
- **Raw pointer:** selected. The return width is 32 bits and consumers use it as an address.
- **Opaque handle:** the ABI is raw-pointer-like, but retaining a separate opaque-handle category is unnecessary. It exposes a typed `cCreatureBase` object surface.
- **Tagged value:** no masking, low-bit tests, tag extraction, or alternate interpretation appears.
- **Union/variant:** no discriminator or coherent alternative storage interpretation appears; all accesses align with one `cCreatureBase` layout.
- **Scalar comparisons:** present, but they are pointer equality/null/type checks, not player-ID comparisons.

## Ownership and lifetime

If the strong owner match is accepted, `cGameNounManager+0x54` is reference-managed storage. The root returns the stored raw address and does not call `AddRef` or `Release`; consumers therefore receive a **borrowed current-avatar pointer**.

`cCreatureBase` exposes `AddRef`, `Release`, and its virtual destructor in vtable slots `+0x00`, `+0x04`, and `+0x08` (`spore_sdk.xml:18778-18782`). This supports reference-counted object lifetime, not caller ownership of the raw result. No reliable constructor body was available in the selected committed artifacts.

Available lifecycle evidence is incomplete:

- SDK declares `SetAvatar(cCreatureAnimal*)`, but the imported address `0x00b1fca0` is adjudicated a dead address (`knowledgegraph/triage/sdk-boundary-repairs-2540f2ca.json:23295-23315`).
- SDK `EnsurePlayer` was repaired into containing function `0x00b20ee0`, but the committed decomp-gap record says its body and field writes are unavailable (`sim-core-00.json:33086-33109,33231-33305`).
- No selected root call site releases or replaces the avatar.
- One `ExecuteAction` branch checks for a null return; others dereference without a local null guard. A universal non-null contract is not established.

## Shared callers with other roots

- All six selected callers also call `0x00b3d300` (`xrefs-2540f2ca.tsv:137558-137593,138483-138492`).
- `0x00d2e4a0`, `0x00d2e580`, and `0x00d2e8a0` also call `0x00b5b800` (`xrefs-2540f2ca.tsv:137567,137581,137595`).
- `0x00d2e4a0` also calls `0x00b3d4c0` and `0x00ba4350` around mode state (`xrefs-2540f2ca.tsv:137566,137568`).
- `0x00d2e8a0` calls `0x00d39360`, passing an action record whose first dword is the returned avatar address (`xrefs-2540f2ca.tsv:137598`).

These are shared-current-state consumers. They do not imply that `0x00b1fdb0` and `0x00b3d300` return the same kind of object.

## Preserved contradictions and corrections

1. **Old player-ID meaning:** rejected by direct dereference and exact `cCreatureBase` layout.
2. **Mixed scalar/pointer meaning:** reconciled as pointer equality/null/type checks.
3. **`result+0x55c`:** rejected for the selected committed sample; the root return is discarded.
4. **`result+0xd8`:** corrected to vtable slot `GetCurrentBrainLevel`.
5. **Owner identity:** strongly mapped to `cGameNounManager`, but direct ECX provenance at the selected call sites is still absent.

## Smallest next experiments

| surviving ambiguity | smallest static experiment | expected resolution |
|---|---|---|
| Exact receiver provenance | Disassemble only the six selected windows and `0x00b1fdb0`; trace the last ECX definition across `call 0x00b3d300`. One chain to `DAT_0167eb60` confirms `cGameNounManager*` and the thiscall-like prototype. | Confirms owner/global and formal ABI. |
| Avatar replacement/lifetime | From `0x00b20ee0` and the repaired dead `SetAvatar` neighborhood, find the first store to `receiver+0x54` and nearby AddRef/Release calls. If absent, follow the first direct `+0x54` store from a `0x00b3d400` caller. | Establishes initialization, replacement, and release path. |
| `cSpeciesProfile+0x61c` meaning | Find one writer and one additional reader; compare constants with the existing 1..5 switch. | Names the categorical field without guessing from range. |
| Other-pointer `+0x55c` | Decompile/type only `FUN_004df420` and its immediate callers; identify whether it returns `cCreatureBase*`, a profile pointer, or another object. | Determines whether `+0x55c` is any root-adjacent map entry at all. |
| Null contract | Classify the 303 canonical direct-call sites only by whether zero is tested before the first dereference; begin with the six selected functions. | Establishes the minimum precondition without runtime. |

## Source boundary

Committed baseline inventory, canonical xrefs, triage and decomp-gap records, function/struct/SDK exports, and persisted SDK decompiler snapshots were used. Runtime traces, Wine, live Ghidra mutation, `SPORE/` binary access, source changes, historical-artifact changes, and Phase-0 interface changes were not used.
